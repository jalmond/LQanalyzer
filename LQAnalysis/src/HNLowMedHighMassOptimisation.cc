// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNLowMedHighMassOptimisation Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNLowMedHighMassOptimisation.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNLowMedHighMassOptimisation);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNLowMedHighMassOptimisation::HNLowMedHighMassOptimisation() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNLowMedHighMassOptimisation");

  Message("In HNLowMedHighMassOptimisation constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  

}


void HNLowMedHighMassOptimisation::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HNLowMedHighMassOptimisation::ExecuteEvents()throw( LQError ){

  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  FillEventCutFlow("NoCut",1.);

  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  
  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// JETS
  // Jets needed now for electron loose and tight collection:
  /// veto electrons close to a bjet in loose+ tight samples
  /// 15-50 % of fake electrons in mc have close bjet while < 0.5 % of signal electrons do

  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  

  /// ELECTRONS
  std::vector<snu::KElectron> _electronAnalysisColl;
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronAnalysisColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl, false);
  
  /// Get Prompt electrons/CF 
  /// As of July 20:New cuts on tight electrons:
  //Remove electrons close to a jet that looks like a real jet.
  ///Use default isolation for 10-20 GeV electrons (0.07%)
  // Add non PF isolation (30% reduction in fakes: 3% reduction in signal)
  std::vector<snu::KElectron> electronAnalysisColl_temp =  GetTruePrompt(_electronAnalysisColl, false, false); // removes CF and fake in mc
  std::vector<snu::KElectron> electronAnalysisColl =ShiftElectronEnergy(electronAnalysisColl_temp, k_running_chargeflip);
  
  
  /// Electrons used for veto (LOOSEST IN ANALYSIS)
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  
  std::vector<snu::KElectron> _electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronLooseColl, false);
  /// Loose electron sample (tight  - iso + looseiso) this removes fake el from jet/photon
  std::vector<snu::KElectron>  electronLooseColl = GetTruePrompt(_electronLooseColl, false, false);
  
  
  std::vector<snu::KElectron>  electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  std::vector<snu::KElectron>  electronPtEtaNoCutColl;
  eventbase->GetElectronSel()->SetPt(20.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronPtEtaNoCutColl);


  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);

  

  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_lepveto_mva;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, muonNoCutColl, electronNoCutColl);
  // jetColl_lepveto have no pileup mva applied
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonVetoColl, electronLooseColl);
  /// Jets used in analysis
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto_mva, muonVetoColl, electronLooseColl);


  ///// count number of bjets in the event (using cvs medium WP)
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }

  // Remove overlapping particles only need electron overlap in ee channel
  for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
    for(std::vector<snu::KElectron>::iterator it2 = it+1; it2 != electronLooseColl.end(); it2++){
      if(it->DeltaR(*it2) < 0.5) return;
    }
  }
  
  
  /// Apply electron SFs for tight id
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt(), true);
    }
  }
  m_logger << DEBUG << "Analysis part: "<< LQLogger::endmsg;


  // Require now dilepton trigger passed
  if(!PassTrigger(triggerslist, prescale)) return;

  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale

  FillEventCutFlow("TriggerCut", 1.);
  
  /// Require 2 analysis electrons (20/15) GeV
  if(electronAnalysisColl.size() != 2 ) return;
  if(electronAnalysisColl.at(0).Pt() < 20.) return;
  if(electronAnalysisColl.at(1).Pt() < 10.) return;

  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(ee.M()  < 10.) return;
 
  
  /// For CF use OS data and weight using CF rates from sunny
  if(k_running_chargeflip) {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));

      weight *=  ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    else return;
  }// cf requirement
  else {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
  }
  
  
  /// Remove events with 3 veto leptons
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;  
  if(muonVetoColl.size() !=0) return;
  
  FillEventCutFlow("SS_lepveto",1.);
  
  float isoweight=weight;
  if(k_running_nonprompt){
    
    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, eventbase->GetEvent().JetRho());
    weight*= ee_weight;
    
    float ee_weight_0905 = Get_DataDrivenWeight_EE(electronAnalysisColl,  eventbase->GetEvent().JetRho());
    isoweight*= ee_weight_0905;
  }
  
  bool tight_endcapiso=true;
  if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)){
    if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt()) > 0.05)tight_endcapiso= false;
  }
  if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)){
    if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt()) > 0.05)tight_endcapiso= false;
  } 

  if(jetColl_lepveto_mva.size() < 2) return;
  

  bool do_optimisation=true;
  if(do_optimisation){
    std::vector<float> isocut;
    isocut.push_back(0.);
    isocut.push_back(1.);
    std::vector<float> ptmin;
    ptmin.push_back(10.);
    ptmin.push_back(15.);
    std::vector<float> ptmax;
    ptmax.push_back(20.);
    ptmax.push_back(25.);
    std::vector<float> eemin;
    eemin.push_back(10.);
    std::vector<float> eemax;
    eemax.push_back(60.);
    eemax.push_back(80.);
    eemax.push_back(100);
    eemax.push_back(150);
    eemax.push_back(1000.);
    std::vector<float> jjmin;
    jjmin.push_back(0.);
    jjmin.push_back(40.);
    std::vector<float> jjmax;
    //jjmax.push_back(100.);
    jjmax.push_back(120.);
    //jjmax.push_back(150.);
    std::vector<float> eejjmin;
    eejjmin.push_back(80.);
    eejjmin.push_back(90.);
    eejjmin.push_back(100.);
    eejjmin.push_back(110.);
    std::vector<float> eejjmax;
    eejjmax.push_back(180.);
    eejjmax.push_back(200.);
    eejjmax.push_back(220.);
    eejjmax.push_back(260.);
    eejjmax.push_back(300.);
    std::vector<float> e1jjmin;
    e1jjmin.push_back(0.);
    std::vector<float> e1jjmax;
    e1jjmax.push_back(1000.);
    std::vector<float> e2jjmin;
    e2jjmin.push_back(0.);
    std::vector<float>e2jjmax;
    //e2jjmax.push_back(125.);
    //e2jjmax.push_back(150.);
    //e2jjmax.push_back(175.);
    //e2jjmax.push_back(200.);
    e2jjmax.push_back(10000.);
    std::vector<float> metmax;
    metmax.push_back(30.);
    metmax.push_back(35.);
    metmax.push_back(40.);
    std::vector<float> mtmax;
    mtmax.push_back(50.);
    mtmax.push_back(60.);
    mtmax.push_back(70.);
    mtmax.push_back(10000.);
    std::vector<float> stmin;
    stmin.push_back(0.);
    std::vector<float> stmax;
    stmax.push_back(150.);
    stmax.push_back(200.);
    stmax.push_back(300.);
    stmax.push_back(10000.);
    std::vector<bool> removeZ;
    removeZ.push_back(true);
    removeZ.push_back(false);
    std::vector<bool> removedRej;
    //removedRej.push_back(true);
    removedRej.push_back(false);
    
    float ilmbin=0.;
    /*for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  ilmbin+=1.;
					  cout << "ilmbin = " << ilmbin << endl;
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    */
    ilmbin = 160000 ;

    FillHist("LowMassOptimise", ilmbin , weight, 0.,ilmbin,int(ilmbin));
    FillHist("LowMassOptimise_sig", ilmbin , 1., 0.,ilmbin,int(ilmbin));
    
    int icut=0;
    for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto, k_running_chargeflip, ptmin.at(ipt), ptmax.at(ipt2), eemin.at(iee),  eemax.at(iee2), jjmin.at(ijj), jjmax.at(ijj2), eejjmin.at(ieejj), eejjmax.at(ieejj2), e1jjmin.at(ie1jj), e1jjmax.at(ie1jj2), e2jjmin.at(ie2jj), e2jjmax.at(ie2jj2), metmax.at(imet),  mtmax.at(imt), stmin.at(istmin), stmax.at(istmax), removeZ.at(iZ), removedRej.at(iej))){
					    if(iiso==0){
					      FillHist("LowMassOptimise", icut , weight, 0.,ilmbin,int(ilmbin)); 
					      FillHist("LowMassOptimise_sig", icut , 1., 0.,ilmbin,int(ilmbin)); 
					    }
					    else{
					      if(!k_running_nonprompt){
						if(tight_endcapiso){
						  FillHist("LowMassOptimise", icut , weight, 0.,ilmbin,int(ilmbin));
						  FillHist("LowMassOptimise_sig", icut , 1., 0.,ilmbin,int(ilmbin));
						}
					      }
					      else{
						FillHist("LowMassOptimise", icut , isoweight, 0.,ilmbin,int(ilmbin));
						FillHist("LowMassOptimise_sig", icut , 1., 0.,ilmbin,int(ilmbin));
					      }
					    }
					  }
					  icut++;
					}
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    
  }// do optimisation
  

  bool do_optimisation2=true;
  if(do_optimisation2){
    std::vector<float> isocut;
    isocut.push_back(0.);
    isocut.push_back(1.);
    std::vector<float> ptmin;
    ptmin.push_back(10.);
    ptmin.push_back(15.);
    ptmin.push_back(20.);
    ptmin.push_back(25.);
    ptmin.push_back(30.);
    ptmin.push_back(35.);
    std::vector<float> ptmax;
    ptmax.push_back(20.);
    ptmax.push_back(25.);
    ptmax.push_back(30.);
    ptmax.push_back(35.);
    ptmax.push_back(40.);
    ptmax.push_back(50.);
    ptmax.push_back(70.);
    std::vector<float> eemin;
    eemin.push_back(15.);
    std::vector<float> eemax;
    //eemax.push_back(200);
    //eemax.push_back(250);
    //eemax.push_back(300);
    eemax.push_back(10000);
    std::vector<float> jjmin;
    jjmin.push_back(40.);
    jjmin.push_back(50.);
    std::vector<float> jjmax;
    jjmax.push_back(110.);
    jjmax.push_back(120.);
    std::vector<float> eejjmin;
    eejjmin.push_back(100.);
    eejjmin.push_back(125.);
    eejjmin.push_back(150.);
    eejjmin.push_back(175.);
    eejjmin.push_back(200.);
    eejjmin.push_back(250.);
    std::vector<float> eejjmax;
    eejjmax.push_back(300.);
    eejjmax.push_back(400.);
    eejjmax.push_back(500.);
    eejjmax.push_back(600.);
    eejjmax.push_back(10000.);
    std::vector<float> e1jjmin;
    e1jjmin.push_back(0.);
    std::vector<float> e1jjmax;
    //e1jjmax.push_back(300.);
    //e1jjmax.push_back(400.);
    //e1jjmax.push_back(500.);
    e1jjmax.push_back(10000.);
    std::vector<float> e2jjmin;
    e2jjmin.push_back(0.);
    std::vector<float> e2jjmax;
    //e2jjmax.push_back(200.);
    //e2jjmax.push_back(250.);
    //e2jjmax.push_back(300.);
    e2jjmax.push_back(10000.);
    std::vector<float> metmax;
    metmax.push_back(30.);
    metmax.push_back(35.);
    metmax.push_back(40.);
    std::vector<float> mtmax;
    mtmax.push_back(10000.);
    std::vector<float> stmin;
    stmin.push_back(80.);
    stmin.push_back(150.);
    stmin.push_back(200.);
    std::vector<float> stmax;
    stmax.push_back(200.);
    stmax.push_back(300.);
    stmax.push_back(400.);
    stmax.push_back(500.);
    stmax.push_back(600.);
    stmax.push_back(10000.);
    std::vector<bool> removeZ;
    removeZ.push_back(true);
    removeZ.push_back(false);
    std::vector<bool> removedRej;
    //removedRej.push_back(true);
    removedRej.push_back(false);
    
    int icut=0;
    float immbin=0.;
    /*  for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  immbin+=1.;
					}
				      }
				    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    */
    immbin = 1100000;
    
    FillHist("MidMassOptimise", immbin , weight, 0.,immbin,int(immbin));
    FillHist("MidMassOptimise_sig",immbin , 1., 0.,immbin,int(immbin));

    for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto, k_running_chargeflip, ptmin.at(ipt), ptmax.at(ipt2), eemin.at(iee),  eemax.at(iee2), jjmin.at(ijj), jjmax.at(ijj2), eejjmin.at(ieejj), eejjmax.at(ieejj2), e1jjmin.at(ie1jj), e1jjmax.at(ie1jj2), e2jjmin.at(ie2jj), e2jjmax.at(ie2jj2), metmax.at(imet),  mtmax.at(imt), stmin.at(istmin),  stmax.at(istmax), removeZ.at(iZ), removedRej.at(iej))){
					    if(iiso==0){
					      FillHist("MidMassOptimise", icut , weight, 0.,immbin,int(immbin));
					      FillHist("MidMassOptimise_sig", icut , 1., 0.,immbin,int(immbin));
					    }
					    else{
					      if(!k_running_nonprompt){
						if(tight_endcapiso){
						  FillHist("MidMassOptimise", icut , weight, 0.,immbin,int(immbin));
						  FillHist("MidMassOptimise_sig", icut , 1., 0.,immbin,int(immbin));
						}
					      }
					      else{
						FillHist("MidMassOptimise", icut , isoweight, 0.,immbin,int(immbin));
						FillHist("MidMassOptimise_sig", icut , 1., 0.,immbin,int(immbin));
					      }
					    }
					    
					  }
					  icut++;
					}
				      }
				    }
				  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    
  }// do optimisation

  bool do_optimisation3=true;
  if(do_optimisation3){

    std::vector<float> isocut;
    isocut.push_back(0.);
    isocut.push_back(1.);
    std::vector<float> ptmin;
    ptmin.push_back(25.);
    ptmin.push_back(30.);
    ptmin.push_back(35.);
    ptmin.push_back(40.);
    ptmin.push_back(45.);
    std::vector<float> ptmax;
    ptmax.push_back(40.);
    ptmax.push_back(50.);
    ptmax.push_back(60.);
    ptmax.push_back(70.);
    ptmax.push_back(80.);
    ptmax.push_back(90.);
    ptmax.push_back(100.);
    std::vector<float> eemin;
    eemin.push_back(15.);
    std::vector<float> eemax;
    eemax.push_back(10000);
    std::vector<float> jjmin;
    jjmin.push_back(50.);
    jjmin.push_back(60.);
    std::vector<float> jjmax;
    jjmax.push_back(110.);
    jjmax.push_back(120.);
    std::vector<float> eejjmin;
    eejjmin.push_back(180.);
    eejjmin.push_back(200.);
    eejjmin.push_back(225.);
    eejjmin.push_back(250.);
    eejjmin.push_back(275.);
    eejjmin.push_back(300.);
    std::vector<float> eejjmax;
    eejjmax.push_back(10000.);
    std::vector<float> e1jjmin;
    e1jjmin.push_back(0.);
    std::vector<float> e1jjmax;
    e1jjmax.push_back(10000.);
    std::vector<float> e2jjmin;
    e2jjmin.push_back(0.);
    std::vector<float> e2jjmax;
    //e2jjmax.push_back(600.);
    //e2jjmax.push_back(1000.);
    e2jjmax.push_back(10000.);
    std::vector<float> metmax;
    metmax.push_back(35.);
    metmax.push_back(40.);
    metmax.push_back(50.);
    std::vector<float> mtmax;
    mtmax.push_back(10000.);
    std::vector<float> stmin;
    stmin.push_back(0.);
    stmin.push_back(150.);
    stmin.push_back(200.);
    std::vector<float> stmax;
    stmax.push_back(500.);
    stmax.push_back(750.);
    stmax.push_back(1000.);
    stmax.push_back(10000.);
    std::vector<bool> removeZ;
    removeZ.push_back(true);
    removeZ.push_back(false);
    std::vector<bool> removedRej;
    //removedRej.push_back(true);
    removedRej.push_back(false);

    
    float ihmbin=0.;
    /*for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  ihmbin+=1.;
					}
				      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      }*/

    //  ihmbin += 1000;
    ihmbin= 1050000;
    FillHist("HighMassOptimise", ihmbin , weight, 0.,ihmbin,int(ihmbin));
    FillHist("HighMassOptimise_sig", ihmbin , 1., 0.,ihmbin,int(ihmbin));

    int icut=0;
    for(unsigned int iiso = 0; iiso<  isocut.size() ; iiso++){
      for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
	for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	  for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	    for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	      for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
		for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		  for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		    for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		      for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
			for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			  for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			    for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			      for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
				for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				  for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				    for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				      for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
					for(unsigned int iej =0; iej< removedRej.size(); iej++){
					  
					  if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto, k_running_chargeflip, ptmin.at(ipt), ptmax.at(ipt2), eemin.at(iee),  eemax.at(iee2), jjmin.at(ijj), jjmax.at(ijj2), eejjmin.at(ieejj), eejjmax.at(ieejj2), e1jjmin.at(ie1jj), e1jjmax.at(ie1jj2), e2jjmin.at(ie2jj), e2jjmax.at(ie2jj2), metmax.at(imet),  mtmax.at(imt),  stmin.at(istmin),  stmax.at(istmax), removeZ.at(iZ), removedRej.at(iej))){
					    if(iiso==0){
                                              FillHist("HighMassOptimise", icut , weight, 0.,ihmbin,int(ihmbin));
                                              FillHist("HighMassOptimise_sig", icut , 1., 0.,ihmbin,int(ihmbin));
                                            }
                                            else{
                                              if(!k_running_nonprompt){
                                                if(tight_endcapiso){
                                                  FillHist("HighMassOptimise", icut , weight, 0.,ihmbin,int(ihmbin));
                                                  FillHist("HighMassOptimise_sig", icut , 1., 0.,ihmbin,int(ihmbin));
                                                }
                                              }
                                              else{
                                                FillHist("HighMassOptimise", icut , isoweight, 0.,ihmbin,int(ihmbin));
                                                FillHist("HighMassOptimise_sig", icut , 1., 0.,ihmbin,int(ihmbin));
                                              }
                                            }
					  }
					  icut++;
					}
				      }
				    }
				  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  
  }// do optimisation


  
  
  return;
}// End of execute event loop

void HNLowMedHighMassOptimisation::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(electrons.size() != 2 ) return ;
  if(electrons.at(0).Pt() < 20.) return ;
  if(electrons.at(1).Pt() < 15.) return ;
  if(!SameCharge(electrons)) return ;
  if(jets.size() < 2) return ;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return ;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(eejj.M()  > 200.) return ;

  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return ;
  if(jj.M() < 40.) return ;

  if(ee.M() > 80.) return ;
  if(eventbase->GetEvent().PFMET() > 35.) return ;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return;

  if(name.Contains("iso_d0")) FillIsoCutFlow(name.Data(),w);
  else FillCutFlow(name.Data(),w);

}


 bool HNLowMedHighMassOptimisation::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip , float pt2, float pt1, float eemin, float eemax, float jjmin, float jjmax, float eejjmin, float eejjmax, float e1jjmin, float e1jjmax, float e2jjmin, float e2jjmax, float metmax, float mtmax, float stmin, float stmax, bool removeZ, bool removerej){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < pt1) return false;
  if(electrons.at(1).Pt() < pt2) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  if(mass < eemin) return false;
  if(mass > eemax) return false;
  if(removeZ) {
    if(fabs(mass-90.) < 10.) return false;
  }
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }

  // get dR el jet
  float drej1=1000.;
  float drej2=1000.;
  for(unsigned int ij=0; ij < jets.size(); ij++){
    if(jets.at(ij).DeltaR(electrons.at(0)) < drej1)  drej1 = jets.at(ij).DeltaR(electrons.at(0) );
    if(jets.at(ij).DeltaR(electrons.at(1)) < drej2)  drej2 = jets.at(ij).DeltaR(electrons.at(1) );
  }
  if(removerej){
    if(drej1 > 2.)return false;
    if(drej2 > 2.)return false;
  }

  float st=0.;
  for(unsigned int ij=0; ij < jets.size(); ij++){
    st+= jets.at(ij).Pt();
  }
  st+=electrons.at(0).Pt();
  st+=electrons.at(1).Pt();
  st+= eventbase->GetEvent().PFMET();

  if(st < stmin)  return false;
  if(st > stmax)  return false;

  
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > jjmax) return false;
  if(jj.M() < jjmin) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M()  > eejjmax) return false;
  if(eejj.M()  < eejjmin) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e1jj.M() > e1jjmax) return false;
  if(e1jj.M() < e1jjmin) return false;

  snu::KParticle e2jj = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e2jj.M() > e2jjmax) return false;;
  if(e2jj.M() < e2jjmin) return false;;
  
  if(eventbase->GetEvent().PFSumET() < 200.) return false;;
  if(eventbase->GetEvent().PFSumET() > 1500.) return false;;

  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;

  if(eventbase->GetEvent().PFMET() > metmax) return false;

  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));

  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > mtmax) return false;
  if(MT2 > mtmax) return false;


  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;

}

bool HNLowMedHighMassOptimisation::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(ee.M() > 150.) return false;
  
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	wmassjj = fabs(jjtmp.M() - 80.4);
	indexj1=ij;
	indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 150.) return false;
  if(jj.M() < 40.) return false;
  
  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M()  > 200.) return false;

  snu::KParticle eej1 = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(eej1.M() > 160.) return false;

  snu::KParticle eej2 = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(eej2.M() > 120.) return false;;

  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;
  if(jets.at(0).DeltaR(jets.at(1)) > 3.5) return false;
  
  if(eventbase->GetEvent().PFMET() > 40.) return false;
  
  
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
  
}

bool HNLowMedHighMassOptimisation::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 15.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 300.) return false;;
  if(eventbase->GetEvent().PFSumET() > 2000.) return false;;


  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
	indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);

  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;


  snu::KParticle e2jj = electrons.at(1) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e2jj.M() > 250.) return false;;
  
  


  if(electrons.at(0).DeltaR(electrons.at(1)) < 0.6) return false;
  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;

  if(jets.at(0).DeltaR(jets.at(1)) > 3.) return false;

  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));

  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > 100.) return false;
  if(MT2 > 100.) return false;

  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}


bool HNLowMedHighMassOptimisation::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 50.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 400.) return false;;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  if(eventbase->GetEvent().PFMET() > 40.) return false;
  if(jets.at(0).DeltaR(jets.at(1)) > 2.5) return false;

  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



void HNLowMedHighMassOptimisation::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() ==2  && jets.size() > 1) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){

	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.4){
	      FillHist(("closejet" + name + "_ptdiff").Data(), (jets.at(ijet).Pt() - electrons.at(iel).Pt()) /  jets.at(ijet).Pt(), weight, -1. , 1., 50);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet").Data(), 1, weight, 0., 2., 2);
	      else FillHist(("closejet" + name + "_bjet").Data(), 0, weight, 0., 2., 2);
	      /// Jet usually vetoe
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);

	      
	    }
	    else{
	      FillHist(("awayjet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,   20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
              FillHist(("awayjet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);

	    }
	  }
	}
      }
    }
  }
  return;
}

void HNLowMedHighMassOptimisation::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void HNLowMedHighMassOptimisation::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");
  
  
  
  return;
  
}

HNLowMedHighMassOptimisation::~HNLowMedHighMassOptimisation() {
  
  Message("In HNLowMedHighMassOptimisation Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     

void HNLowMedHighMassOptimisation::FillEventCutFlow(TString cut, float weight){

  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",6,0.,6.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"SS_lepveto");
  }
  
}

     
void HNLowMedHighMassOptimisation::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",16,0.,16.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"SS_NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"SS_Tight");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"SS_Tight_convveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"SS_Tight_d0veto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"SS_Tight_reliso");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"SS_Medium_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"SS_Tight_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"SS_Tight_noclosejet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"SS_anal_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"Signal_anal");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"Signal_Tightlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"Signal_Mediumlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(13,"Signal_drcut1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(14,"Signal_drcut2");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(15,"Signal_anal_dr1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(16,"Signal_anal_dr2");
  }
}
     
     
void HNLowMedHighMassOptimisation::FillIsoCutFlow(TString cut, float weight){
       
  
  if(GetHist("isocutflow")) {
    GetHist("isocutflow")->Fill(cut,weight);
    
  }
  else{
    AnalyzerCore::MakeHistograms("isocutflow",36,0.,36.);
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(1,"iso_d0_03_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(2,"iso_d0_03_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(3,"iso_d0_03_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(4,"iso_d0_03_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(5,"iso_d0_03_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(6,"iso_d0_03_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(7,"iso_d0_03_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(8,"iso_d0_03_iso3_075");
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(10,"iso_d0_02_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(11,"iso_d0_02_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(12,"iso_d0_02_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(13,"iso_d0_02_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(14,"iso_d0_02_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(15,"iso_d0_02_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(16,"iso_d0_02_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(17,"iso_d0_02_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(19,"iso_d0_01_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(20,"iso_d0_01_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(21,"iso_d0_01_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(22,"iso_d0_01_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(23,"iso_d0_01_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(24,"iso_d0_01_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(25,"iso_d0_01_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(26,"iso_d0_01_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(28,"iso_d0_005_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(29,"iso_d0_005_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(30,"iso_d0_005_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(31,"iso_d0_005_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(32,"iso_d0_005_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(33,"iso_d0_005_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(34,"iso_d0_005_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(35,"iso_d0_005_iso3_075");

    
    
  }
}


void HNLowMedHighMassOptimisation::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNLowMedHighMassOptimisation::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNLowMedHighMassOptimisationCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNLowMedHighMassOptimisation::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



