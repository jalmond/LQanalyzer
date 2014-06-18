// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNDiElectron);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiElectron::HNDiElectron() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiElectron");

  Message("In HNDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void HNDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   m_os_Z_nw = 0;
   m_os_Z = 0;
   m_ss_Z_nw = 0;
   m_ss_Z = 0;
   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){

  weight=1;
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  FillCutFlow("NoCut", weight);
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  FillCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
    
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillCutFlow("VertexCut", weight);

  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// ELECTRONS
  std::vector<snu::KElectron> _electronAnalysisColl;
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelection(_electronAnalysisColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl);


  for(int i =0; i < _electronAnalysisColl.size(); i++){
    // is the mother a tau
    int mother_pdgid=_electronAnalysisColl.at(i).MotherPdgId();
    if(fabs(mother_pdgid) == 15){
      FillHist("TauEl_d0",_electronAnalysisColl.at(i).PrimaryVertexDXY()  , weight, -3.,3.,600);
    }
  }
  
  /// Get Prompt electrons/CF
  std::vector<snu::KElectron> electronAnalysisColl =GetTruePrompt(_electronAnalysisColl);

  

  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  
  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl);
  
  std::vector<snu::KElectron> electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  
  std::vector<snu::KElectron> electronPtEtaCutColl;
  std::vector<snu::KElectron> electronMedium_chargeconst;
  std::vector<snu::KElectron> electronTight;

  std::vector<snu::KElectron> electronTight_convveto;
  std::vector<snu::KElectron> electronTight_d0veto;  
  std::vector<snu::KElectron> electronTight_reliso;
  std::vector<snu::KElectron> electronTight_chargeconst;

  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    
    if(electronNoCutColl[iel].Pt() < 20.) continue;
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;
    
    electronPtEtaCutColl.push_back(electronNoCutColl[iel]);
    
    double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
    double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
    double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
    double effective_area_03  = 0.0;
    
    for (int i = 0; i < 7; ++i ){
      double bin_minimum = effective_area_eta_minimums[i];
      double bin_maximum = effective_area_eta_maximums[i];
      if ( fabs(electronNoCutColl[iel].SCEta()) >= bin_minimum && fabs(electronNoCutColl[iel].SCEta()) < bin_maximum ) {
	effective_area_03 = effective_areas_03 [i];
      }
    }
   
    double egamma_pfiso_03 = electronNoCutColl[iel].PFChargedHadronIso03() + std::max ( electronNoCutColl[iel].PFPhotonIso03() + electronNoCutColl[iel].PFNeutralHadronIso03() - ( eventbase->GetEvent().JetRho() * effective_area_03 ), 0.0 );
    egamma_pfiso_03 /= electronNoCutColl[iel].Pt();
    
    
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );
    /// dEtaIn     cut
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.06){
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
	    if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ()) < 0.02){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
		if( egamma_ep          <= 0.05){
		  if(electronNoCutColl.at(iel).ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl.at(iel).MissingHits()    <=  1){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY())  <= 0.02){
			  if(egamma_pfiso_03    <=  0.15){
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			      electronMedium_chargeconst.push_back(electronNoCutColl.at(iel));
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
    else {
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.007){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03) {
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.02){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
		if( egamma_ep          <=0.05){
		  if(electronNoCutColl.at(iel).ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl.at(iel).MissingHits()    <=  1){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY())  <= 0.02){
			  if(egamma_pfiso_03    <=  0.15){
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                              electronMedium_chargeconst.push_back(electronNoCutColl.at(iel));
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
    /// TIGHT
    
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.02){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
		if( egamma_ep          <= 0.05){
		  electronTight.push_back(electronNoCutColl.at(iel));
		  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl[iel].MissingHits()    <=  0){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			electronTight_convveto.push_back(electronNoCutColl.at(iel));
			
			if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY())  <= 0.02){
			  electronTight_d0veto.push_back(electronNoCutColl.at(iel));
			  if(egamma_pfiso_03    <=  0.1){
			    electronTight_reliso.push_back(electronNoCutColl.at(iel));
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                              electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
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
    else {
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.02){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
		if( egamma_ep          <=0.05){
		  electronTight.push_back(electronNoCutColl.at(iel));
		  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl[iel].MissingHits()    <=  0){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			electronTight_convveto.push_back(electronNoCutColl.at(iel));
			if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY())  <= 0.02){
			  electronTight_d0veto.push_back(electronNoCutColl.at(iel));
			  if(egamma_pfiso_03    <=  0.1){
			    electronTight_reliso.push_back(electronNoCutColl.at(iel));
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                              electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
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
 
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);
  
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);
  
  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_reallepveto;
  std::vector<snu::KJet> jetColl_reallepvetov2;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.4);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonVetoColl, electronLooseColl);
  eventbase->GetJetSel()->JetSelectionRealLeptonVeto(jetColl_reallepveto, muonVetoColl, electronLooseColl);
  eventbase->GetJetSel()->JetSelectionRealLeptonVetoV2(jetColl_reallepvetov2, muonVetoColl, electronLooseColl);
  eventbase->GetJetSel()->Selection(jetColl);
 
 
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl, weight);
  
  if(SameCharge(electronNoCutColl))   FillCutFlow("SS_NoCut",weight);
  if(SameCharge(electronPtEtaCutColl)) FillCutFlow("SS_PtEta",weight);
  
  if(SameCharge(electronTight))   FillCutFlow("SS_Tight",weight);
  if(SameCharge(electronTight_convveto))  FillCutFlow("SS_Tight_convveto",weight);
  if(SameCharge(electronTight_d0veto)) FillCutFlow("SS_Tight_d0veto",weight);
  if(SameCharge(electronTight_reliso)) FillCutFlow("SS_Tight_reliso", weight);  
  if(SameCharge(electronTight_chargeconst)) FillCutFlow("SS_Tight_chargeconst", weight);
  if(SameCharge(electronMedium_chargeconst))  FillCutFlow("SS_Medium",weight);

  if(SameCharge(electronAnalysisColl)) FillCutFlow("SS_anal_el", weight);
  
  /// Make plot of jet energy fraction for close and away jets
  CheckJetsCloseToLeptons(electronMedium_chargeconst, jetColl, "Medium");
  CheckJetsCloseToLeptons(electronTight_chargeconst, jetColl, "Tight");
  
  
  bool jetclosetoel= false;
  for(unsigned int ijet =0; ijet < jetColl_reallepveto.size(); ijet++){
    for(unsigned int iel=0; iel <  electronTight_chargeconst.size(); iel++){
      if(jetColl_reallepveto.at(ijet).DeltaR(electronTight_chargeconst.at(iel)) < 0.4) {
	jetclosetoel=true;
      }
    }
  }

  
  bool jetclosetoel2= false;
  for(unsigned int ijet =0; ijet < jetColl_reallepvetov2.size(); ijet++){
    for(unsigned int iel=0; iel <  electronTight_chargeconst.size(); iel++){
      if(jetColl_reallepvetov2.at(ijet).DeltaR(electronTight_chargeconst.at(iel)) < 0.4) {
	jetclosetoel2=true;
	
      }
    }    
  }
  if(!jetclosetoel){
    if(SameCharge(electronTight_chargeconst)) FillCutFlow("SS_Tight_noclosejet", weight);
  }  


  
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;
  
  PassLowMassSignalRegion(electronAnalysisColl, jetColl_lepveto,"Signal_anal", weight) ;
  PassLowMassSignalRegion(electronTight_chargeconst, jetColl_lepveto,"Signal_Tightlooseiso_d0", weight) ;
  PassLowMassSignalRegion(electronMedium_chargeconst, jetColl_lepveto,"Signal_Mediumlooseiso_d0", weight) ;
  if(!jetclosetoel)CheckSignalRegion(electronTight_chargeconst, jetColl_lepveto,"Signal_drcut1", weight) ;
  if(!jetclosetoel2)CheckSignalRegion(electronTight_chargeconst, jetColl_lepveto,"Signal_drcut2", weight) ;

  
  bool analjetclosetoel= false;
  for(unsigned int ijet =0; ijet < jetColl_reallepveto.size(); ijet++){
    for(unsigned int iel=0; iel <  electronAnalysisColl.size(); iel++){
      if(jetColl_reallepveto.at(ijet).DeltaR(electronAnalysisColl.at(iel)) < 0.4) {
        analjetclosetoel=true;
      }
    }
  }

  
  bool analjetclosetoel2= false;
  for(unsigned int ijet =0; ijet < jetColl_reallepvetov2.size(); ijet++){
    for(unsigned int iel=0; iel <  electronAnalysisColl.size(); iel++){
      if(jetColl_reallepvetov2.at(ijet).DeltaR(electronAnalysisColl.at(iel)) < 0.4) {
        analjetclosetoel2=true;

      }
    }
  }
  if(!analjetclosetoel)CheckSignalRegion(electronAnalysisColl, jetColl_lepveto,"Signal_anal_dr1", weight) ;
  if(!analjetclosetoel2)CheckSignalRegion(electronAnalysisColl, jetColl_lepveto,"Signal_anal_dr2", weight) ;

  std::vector<snu::KElectron> el_d0_03_iso3_60;
  std::vector<snu::KElectron> el_d0_03_iso3_50;
  std::vector<snu::KElectron> el_d0_03_iso3_40;
  std::vector<snu::KElectron> el_d0_03_iso3_30;
  std::vector<snu::KElectron> el_d0_03_iso3_20;
  std::vector<snu::KElectron> el_d0_03_iso3_10;
  std::vector<snu::KElectron> el_d0_03_iso3_09;
  std::vector<snu::KElectron> el_d0_03_iso3_075;

  std::vector<snu::KElectron> el_d0_02_iso3_60;
  std::vector<snu::KElectron> el_d0_02_iso3_50;
  std::vector<snu::KElectron> el_d0_02_iso3_40;
  std::vector<snu::KElectron> el_d0_02_iso3_30;
  std::vector<snu::KElectron> el_d0_02_iso3_20;
  std::vector<snu::KElectron> el_d0_02_iso3_10;
  std::vector<snu::KElectron> el_d0_02_iso3_09;
  std::vector<snu::KElectron> el_d0_02_iso3_075;

  std::vector<snu::KElectron> el_d0_01_iso3_60;
  std::vector<snu::KElectron> el_d0_01_iso3_50;
  std::vector<snu::KElectron> el_d0_01_iso3_40;
  std::vector<snu::KElectron> el_d0_01_iso3_30;
  std::vector<snu::KElectron> el_d0_01_iso3_20;
  std::vector<snu::KElectron> el_d0_01_iso3_10;
  std::vector<snu::KElectron> el_d0_01_iso3_09;
  std::vector<snu::KElectron> el_d0_01_iso3_075;
  
  std::vector<snu::KElectron> el_d0_005_iso3_60;
  std::vector<snu::KElectron> el_d0_005_iso3_50;
  std::vector<snu::KElectron> el_d0_005_iso3_40;
  std::vector<snu::KElectron> el_d0_005_iso3_30;
  std::vector<snu::KElectron> el_d0_005_iso3_20;
  std::vector<snu::KElectron> el_d0_005_iso3_10;
  std::vector<snu::KElectron> el_d0_005_iso3_075;
  std::vector<snu::KElectron> el_d0_005_iso3_09;


  
  
  /// LOOK AT ISO/D0 cut to use
  for(int iel=0; iel < electronTight_convveto.size(); iel++){
    

    cout << "TEST" << endl;
    double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
    double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
    double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
    double effective_area_03  = 0.0;
    
    for (int i = 0; i < 7; ++i ){
      double bin_minimum = effective_area_eta_minimums[i];
      double bin_maximum = effective_area_eta_maximums[i];
      if ( fabs(electronTight_convveto[iel].SCEta()) >= bin_minimum && fabs(electronTight_convveto[iel].SCEta()) < bin_maximum ) {
        effective_area_03 = effective_areas_03 [i];
      }
    }

    double egamma_pfiso_03 = electronTight_convveto[iel].PFChargedHadronIso03() + std::max ( electronTight_convveto[iel].PFPhotonIso03() + electronTight_convveto[iel].PFNeutralHadronIso03() - ( eventbase->GetEvent().JetRho() * effective_area_03 ), 0.0 );
    egamma_pfiso_03 /= electronTight_convveto[iel].Pt();
    
    
    if(fabs(electronTight_convveto.at(iel).LeadVtxDistXY()) < 0.03 ){
      cout << "TEST2" << endl;
      if(egamma_pfiso_03 < 0.6 )el_d0_03_iso3_60.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.5 )el_d0_03_iso3_50.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.4 )el_d0_03_iso3_40.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.3 )el_d0_03_iso3_30.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.2 )el_d0_03_iso3_20.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.1 )el_d0_03_iso3_10.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.09 )el_d0_03_iso3_09.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.075 )el_d0_03_iso3_075.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.05 )el_d0_03_iso3_50.push_back(electronTight_convveto[iel]);
    }
    if(fabs(electronTight_convveto.at(iel).LeadVtxDistXY()) < 0.02 ){
      if(egamma_pfiso_03 < 0.6 )el_d0_02_iso3_60.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.5 )el_d0_02_iso3_50.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.4 )el_d0_02_iso3_40.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.3 )el_d0_02_iso3_30.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.2 )el_d0_02_iso3_20.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.1 )el_d0_02_iso3_10.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.09 )el_d0_02_iso3_09.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.075 )el_d0_02_iso3_075.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.05 )el_d0_02_iso3_50.push_back(electronTight_convveto[iel]);
    }
    
    if(fabs(electronTight_convveto.at(iel).LeadVtxDistXY()) < 0.01 ){
      if(egamma_pfiso_03 < 0.6 )el_d0_01_iso3_60.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.5 )el_d0_01_iso3_50.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.4 )el_d0_01_iso3_40.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.3 )el_d0_01_iso3_30.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.2 )el_d0_01_iso3_20.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.1 )el_d0_01_iso3_10.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.09 )el_d0_01_iso3_09.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.075 )el_d0_01_iso3_075.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.05 )el_d0_01_iso3_50.push_back(electronTight_convveto[iel]);
    }
    if(fabs(electronTight_convveto.at(iel).LeadVtxDistXY()) < 0.005 ){
      if(egamma_pfiso_03 < 0.6 )el_d0_005_iso3_60.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.5 )el_d0_005_iso3_50.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.4 )el_d0_005_iso3_40.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.3 )el_d0_005_iso3_30.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.2 )el_d0_005_iso3_20.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.1 )el_d0_005_iso3_10.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.09 )el_d0_005_iso3_09.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.075 )el_d0_005_iso3_075.push_back(electronTight_convveto[iel]);
      if(egamma_pfiso_03 < 0.05 )el_d0_005_iso3_50.push_back(electronTight_convveto[iel]);
    }
  }
  

  CheckSignalRegion(el_d0_005_iso3_60, jetColl_lepveto,"iso_d0_005_iso3_60", weight);
  CheckSignalRegion(el_d0_005_iso3_50, jetColl_lepveto,"iso_d0_005_iso3_50", weight);
  CheckSignalRegion(el_d0_005_iso3_40, jetColl_lepveto,"iso_d0_005_iso3_40", weight);
  CheckSignalRegion(el_d0_005_iso3_30, jetColl_lepveto,"iso_d0_005_iso3_30", weight);
  CheckSignalRegion(el_d0_005_iso3_20, jetColl_lepveto,"iso_d0_005_iso3_20", weight);
  CheckSignalRegion(el_d0_005_iso3_10, jetColl_lepveto,"iso_d0_005_iso3_10", weight);
  CheckSignalRegion(el_d0_005_iso3_09, jetColl_lepveto,"iso_d0_005_iso3_09", weight);
  CheckSignalRegion(el_d0_005_iso3_075, jetColl_lepveto,"iso_d0_005_iso3_075", weight);

  CheckSignalRegion(el_d0_01_iso3_60, jetColl_lepveto,"iso_d0_01_iso3_60", weight);
  CheckSignalRegion(el_d0_01_iso3_50, jetColl_lepveto,"iso_d0_01_iso3_50", weight);
  CheckSignalRegion(el_d0_01_iso3_40, jetColl_lepveto,"iso_d0_01_iso3_40", weight);
  CheckSignalRegion(el_d0_01_iso3_30, jetColl_lepveto,"iso_d0_01_iso3_30", weight);
  CheckSignalRegion(el_d0_01_iso3_20, jetColl_lepveto,"iso_d0_01_iso3_20", weight);
  CheckSignalRegion(el_d0_01_iso3_10, jetColl_lepveto,"iso_d0_01_iso3_10", weight);
  CheckSignalRegion(el_d0_01_iso3_09, jetColl_lepveto,"iso_d0_01_iso3_09", weight);
  CheckSignalRegion(el_d0_01_iso3_075, jetColl_lepveto,"iso_d0_01_iso3_075", weight);

  CheckSignalRegion(el_d0_02_iso3_60, jetColl_lepveto,"iso_d0_02_iso3_60", weight);
  CheckSignalRegion(el_d0_02_iso3_50, jetColl_lepveto,"iso_d0_02_iso3_50", weight);
  CheckSignalRegion(el_d0_02_iso3_40, jetColl_lepveto,"iso_d0_02_iso3_40", weight);
  CheckSignalRegion(el_d0_02_iso3_30, jetColl_lepveto,"iso_d0_02_iso3_30", weight);
  CheckSignalRegion(el_d0_02_iso3_20, jetColl_lepveto,"iso_d0_02_iso3_20", weight);
  CheckSignalRegion(el_d0_02_iso3_10, jetColl_lepveto,"iso_d0_02_iso3_10", weight);
  CheckSignalRegion(el_d0_02_iso3_09, jetColl_lepveto,"iso_d0_02_iso3_09", weight);
  CheckSignalRegion(el_d0_02_iso3_075, jetColl_lepveto,"iso_d0_02_iso3_075", weight);
  
  CheckSignalRegion(el_d0_03_iso3_60, jetColl_lepveto,"iso_d0_03_iso3_60", weight);
  CheckSignalRegion(el_d0_03_iso3_50, jetColl_lepveto,"iso_d0_03_iso3_50", weight);
  CheckSignalRegion(el_d0_03_iso3_40, jetColl_lepveto,"iso_d0_03_iso3_40", weight);
  CheckSignalRegion(el_d0_03_iso3_30, jetColl_lepveto,"iso_d0_03_iso3_30", weight);
  CheckSignalRegion(el_d0_03_iso3_20, jetColl_lepveto,"iso_d0_03_iso3_20", weight);
  CheckSignalRegion(el_d0_03_iso3_10, jetColl_lepveto,"iso_d0_03_iso3_10", weight);
  CheckSignalRegion(el_d0_03_iso3_09, jetColl_lepveto,"iso_d0_03_iso3_09", weight);
  CheckSignalRegion(el_d0_03_iso3_075, jetColl_lepveto,"iso_d0_03_iso3_075", weight);
  

  if(SameCharge(electronAnalysisColl))   FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  
  
  if(electronAnalysisColl.size() != 2 ) return;
  
  if(k_running_nonprompt){
    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto.size(), eventbase->GetEvent().JetRho());
    weight*= ee_weight;
  }
  
  if(electronAnalysisColl.at(0).Pt() < 20.) return;
  if(electronAnalysisColl.at(1).Pt() < 15.) return;
  
  
  if(Zcandidate(electronAnalysisColl, 15., false))  {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));
      
      float cfweight= weight;
      cfweight *= ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
      
      m_os_Z += cfweight;
      m_os_Z_nw +=1;
      
      FillHist("Z_os_mc_1pt",electronAnalysisColl.at(0).Pt()  , cfweight, 0.,200.,20);
      FillHist("Z_os_mc_1eta",electronAnalysisColl.at(0).Eta()  , cfweight, -2.5,2.5,10);
      FillHist("Z_os_mc_2pt",electronAnalysisColl.at(1).Pt()  , cfweight, 0.,200.,20);
      FillHist("Z_os_mc_2eta",electronAnalysisColl.at(1).Eta()  , cfweight, -2.5,2.5,10);
      
    }
    
    else{
      m_ss_Z += weight;
      m_ss_Z_nw += 1.;
      FillHist("Z_ss_mc_1pt",electronAnalysisColl.at(0).Pt()  , weight, 0.,200.,20);
      FillHist("Z_ss_mc_2pt",electronAnalysisColl.at(1).Pt()  , weight, 0.,200.,20);

      FillHist("Z_ss_mc_1eta",electronAnalysisColl.at(0).Eta()  , weight, -2.5,2.5,10);
      FillHist("Z_ss_mc_2eta",electronAnalysisColl.at(1).Eta()  , weight, -2.5,2.5,10);
    }
  }
  

  if(k_running_chargeflip) {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));
      
      weight *=  0.5* ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }
    else return;
  }
  else {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
  }
  
  
  FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
  FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);
  
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;
  
  FillCLHist(sighist, "SSee_trilepveto", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(ee.M()  < 15.) return;
  FillCLHist(sighist, "SSee_eegt15", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  for(unsigned int ijet =0 ; ijet < jetColl.size() ; ijet++){
    for(unsigned int iel=0 ; iel < electronLooseColl.size() ; iel++){
      if( electronLooseColl[iel].DeltaR(jetColl.at(ijet)) < 0.4){
	if(jetColl.at(ijet).BtagProb() > 0.679) cout << "Jet close to electron is btagged" <<  endl;
      }
    }
  }
  
  
  if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  else FillCLHist(sighist, "SSee_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(jetColl_lepveto.size() != 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_gt0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  }

  if(jetColl_lepveto.size() < 2) return;
  FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
 

  snu::KParticle Z = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(fabs( Z.M() - 90.)  < 10.){
    m_logger << INFO << "Event has mass close to Z" << LQLogger::endmsg;
    return;
  }
  FillCLHist(sighist, "SSeeJJ_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(eventbase->GetEvent().PFMET() > 50.) return;

  ///  FillCutFlow("SS_MET",weight);
  

  for(unsigned int ijet=0; ijet < jetColl_lepveto.size(); ijet++){
    
    FillHist("jet_NeutralEMEnergyFraction",jetColl_lepveto.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
    FillHist("jet_NeutralHadEnergyFraction",jetColl_lepveto.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_ChargedEMEnergyFraction",jetColl_lepveto.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_ChargedHadEnergyFraction",jetColl_lepveto.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_HFEMEnergyFraction",jetColl_lepveto.at(ijet).HFEMEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_HFHadEnergyFraction",jetColl_lepveto.at(ijet).HFHadEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_ChargedMuEnergyFraction",jetColl_lepveto.at(ijet).ChargedMuEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_MuonEnergyFraction",jetColl_lepveto.at(ijet).MuonEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_ElectronEnergyFraction",jetColl_lepveto.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
    FillHist("jet_PhotonEnergyFraction",jetColl_lepveto.at(ijet).PhotonEnergyFraction() , weight, 0.,1.,20);

  }

  
  return;
  bool prompt_prompt = false;
  bool prompt_nonprompt = false;
  bool nonprompt_nonprompt = false;
  bool prompt_chargeflip = false;

  m_logger << INFO << "Number of electrons == " << electronAnalysisColl.size() << LQLogger::endmsg;
  
  for(unsigned int iel = 0; iel < electronAnalysisColl.size(); iel++){
    m_logger << INFO << "El number:  " <<  iel+1  << LQLogger::endmsg;
    
    if(electronAnalysisColl[iel].Charge() == -1){
      
      if(electronAnalysisColl[iel].MatchedGenParticlePt() == -999)  m_logger << INFO << "El- pt/eta/phi = " << electronAnalysisColl[iel].Pt() << " / " << electronAnalysisColl[iel].Eta() << " / " << electronAnalysisColl[iel].Phi() << LQLogger::endmsg;
      else m_logger << INFO << "El- pt/eta/phi = " << electronAnalysisColl[iel].MatchedGenParticlePt() << " / " << electronAnalysisColl[iel].MatchedGenParticleEta() << " / " <<electronAnalysisColl[iel].MatchedGenParticlePhi() << LQLogger::endmsg;
    }
    else {
      if(electronAnalysisColl[iel].MatchedGenParticlePt() == -999)  m_logger << INFO << "El+ pt/eta/phi = " << electronAnalysisColl[iel].Pt() << " / " << electronAnalysisColl[iel].Eta() << " / " << electronAnalysisColl[iel].Phi() << LQLogger::endmsg;
      else m_logger << INFO << "El+ pt/eta/phi = " << electronAnalysisColl[iel].MatchedGenParticlePt() << " / " << electronAnalysisColl[iel].MatchedGenParticleEta() << " / " <<electronAnalysisColl[iel].MatchedGenParticlePhi() << LQLogger::endmsg;
      
    }
    
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      if( electronAnalysisColl[iel].DeltaR(eventbase->GetTruth().at(it)) < 0.2){
        if(eventbase->GetTruth().at(it).IndexMother()!= 1)  m_logger << INFO << "Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / "<< eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()   << " " << eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId() << LQLogger::endmsg;
      }
    }
    
    bool prompt = true;
    bool charge_flip = false;
    bool match_found=false;
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      
      if( electronAnalysisColl[iel].DeltaR(eventbase->GetTruth().at(it)) < 0.2){
	m_logger << INFO << "Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / " << eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()    << LQLogger::endmsg;
	
	match_found=true;
	
	if(eventbase->GetTruth().at(it).GenStatus() == 1){
	  if(fabs(eventbase->GetTruth().at(it).PdgId()) == 11){
	    for(unsigned int it2 = 0; it2 < eventbase->GetTruth().size() ; it2++){
	      if(eventbase->GetTruth().at(it2).PdgId() == 2212) continue;
	      if(eventbase->GetTruth().at(it2).GenStatus() == 3){
		if(eventbase->GetTruth().at(it).DeltaR(eventbase->GetTruth().at(it2)) < 0.1) {
		  m_logger << "PDGID of particle close to status 1 electron = " << eventbase->GetTruth().at(it2).PdgId() << LQLogger::endmsg;
		  m_logger << "Mother of  particle close to status 1 electron = " << eventbase->GetTruth().at(eventbase->GetTruth().at(it2).IndexMother()).PdgId() << LQLogger::endmsg;
		  if(fabs(eventbase->GetTruth().at(it2).PdgId()) == 15){
		    m_logger << INFO << "Electron  from Tau decay" << LQLogger::endmsg;
		    
		    if(eventbase->GetTruth().at(it2).PdgId() * electronAnalysisColl[iel].Charge() > 0.){
		      charge_flip= true;
		      prompt=true;
		      m_logger << INFO << "ELECTRON FROM CHARGELFIP" <<  LQLogger::endmsg;
		      break;
		      
		    }		  
		  }
		}
	      }
	    }
	  }
	}
	else if(eventbase->GetTruth().at(it).GenStatus() == 3){
	  
	  if(fabs(eventbase->GetTruth().at(it).PdgId()) == 11 && isPrompt(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId()))) prompt = true;
	  else prompt = false;
	  
	  if(electronAnalysisColl[iel].Charge() * eventbase->GetTruth().at(it).PdgId() > 0.)  charge_flip= true;
	}
      }
      
    } 
    if(!match_found)  {
      m_logger << INFO << "NOOOOO MATCHED  TRUTH PARTICLE FOUND" << LQLogger::endmsg;
      for(unsigned int jit = 0; jit < eventbase->GetGenJets().size(); jit++){
	m_logger<< INFO << "Matched Gen jet id = " << jit+1 << " pt = " <<  eventbase->GetGenJets().at(jit).Pt() << " eta= " << eventbase->GetGenJets().at(jit).Eta() << " phi = " << eventbase->GetGenJets().at(jit).Phi() << LQLogger::endmsg;
      }
      
      for(unsigned int ip=0; ip < PhotonEta->size() ; ip++){
	if(!PhotonHasMatchedPromptEle)m_logger<< INFO << "Photon pt/eta/phi = " << PhotonPt->at(ip) << " / " <<  PhotonEta->at(ip) << " / " << PhotonPhi->at(ip) << LQLogger::endmsg;
      }
    }


    if(iel==0){
      if(!prompt) {
	prompt_nonprompt = true;
	nonprompt_nonprompt = true;
	prompt_prompt = false;
      }
      else{
	if(charge_flip)  prompt_chargeflip = true;
	prompt_prompt = true;
	prompt_nonprompt = false;
	nonprompt_nonprompt = false;
      }
    }
    if(iel==1){
      if(!prompt) {
	if(nonprompt_nonprompt)nonprompt_nonprompt = true;
	else nonprompt_nonprompt = false;
	if(prompt_nonprompt) prompt_nonprompt = false;
	else prompt_nonprompt = true;
	prompt_prompt =false;
      }
      else {
	if(charge_flip)  prompt_chargeflip = true;
	nonprompt_nonprompt = false;
	if(prompt_prompt) prompt_prompt = true;
	else prompt_prompt =false;
	if(prompt_nonprompt) prompt_nonprompt = true;
	else  prompt_nonprompt = false;
      }
    }
  }
  
  if(prompt_chargeflip)  m_logger << INFO << "EVENT HAS CHARGEFLIP   "<<  LQLogger::endmsg;
  else   if (prompt_prompt) {
    m_logger << INFO << "EVENT IS PROMPT-PROMPT "<<  LQLogger::endmsg;
    cout << "WTF" << endl;
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      m_logger << INFO << "PP:Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / " << eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()    << LQLogger::endmsg;
      if( eventbase->GetTruth().at(it).IndexMother() != -1)m_logger << INFO <<   eventbase->GetTruth().at( eventbase->GetTruth().at(it).IndexMother()).PdgId()    << LQLogger::endmsg;
    }
    
  }
  else if (prompt_nonprompt) m_logger << INFO << "EVENT IS PROMPT-NONPROMPT "<<  LQLogger::endmsg;
  else if (nonprompt_nonprompt) m_logger << INFO << "EVENT IS NONPROMPT-NONPROMPT "<<  LQLogger::endmsg;
  m_logger << INFO << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  
  
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto.size(); ij++){
    if(jetColl_lepveto.at(ij).BtagProb() > 0.679) nbjet++;
  }
  
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(muonTightColl.size() ==2){
	if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  for(unsigned int ij=0; ij <jetColl.size(); ij++){
    for (unsigned int iel=0; iel < electronAnalysisColl.size(); iel++){
      float dR = electronAnalysisColl[iel].DeltaR(jetColl[ij]);
      if(dR< 0.4){
	//m_logger << INFO << " close jet to electron has pT diff = " << 100.*(electronAnalysisColl[iel].Pt() - jetColl[ij].Pt()) / electronAnalysisColl[iel].Pt() << LQLogger::endmsg;
	///m_logger << INFO << (electronAnalysisColl.at(iel).PrimaryVertexDXY()/ electronAnalysisColl.at(iel).PrimaryVertexDXYError())<< LQLogger::endmsg;
      }
    }    
  }
  /// count number of loose leptons
  int nloose_lep = muonVetoColl.size() + electronVetoColl.size();

  
  if(electronAnalysisColl.size() ==  3) {
       m_logger << INFO << "Number of jets in tri electron event = " << jetColl_lepveto.size() << LQLogger::endmsg;
     
       FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
     }
  if(electronAnalysisColl.size() ==  4)FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);


  
  bool no_emuoverlap = true;

  for(int i=0; i < electronAnalysisColl.size() ; i++){
    for(int j=0; j < muonTightColl.size() ; j++){
      float dR =  electronAnalysisColl[i].DeltaR(muonTightColl[j]);
      if(dR < 0.1) no_emuoverlap= false;
    }
  }
  
  if (electronAnalysisColl.size() == 2) {      

    if(electronAnalysisColl.at(0).Charge() == electronAnalysisColl.at(1).Charge()){      
      
      FillCutFlow("SS_t",weight);
      FillCLHist(sighist, "SSDiElectronTight", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
      
      if(nloose_lep == 2 && no_emuoverlap){
	FillCutFlow("SS_lvt_t",weight);
      
	if(jetColl_lepveto.size() > 1){
	  FillCutFlow("SS_dijet_t",weight);
	  FillCLHist(sighist, "SSDiElectronTight_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
	  
	  
	  if(SumPt(jetColl_lepveto)  > 80.){
	    if(! ( SumPt(jetColl_lepveto) < 500. && eventbase->GetEvent().PFMET() < 30.)){
	      FillCLHist(sighist, "SSSR0", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
	    }
	  }
	  
	    
	  
	  bool pass_same_vertex= (electronAnalysisColl.at(0).VertexIndex() == electronAnalysisColl.at(1).VertexIndex());
	  bool fail_conv = true;
	  bool fail_d0=false;
	  bool ecalseeded= true;
	  bool pass_charge_cons=true;
	  
	  for(unsigned int i= 0; i < electronAnalysisColl.size(); i++){
	    if(electronAnalysisColl.at(i).MissingHits() == 0) fail_conv = false;
	    if(electronAnalysisColl.at(i).HasMatchedConvPhot()) fail_conv = false; 
	    if((electronAnalysisColl.at(i).PrimaryVertexDXY()/ electronAnalysisColl.at(i).PrimaryVertexDXYError()) > 4.) {
	      fail_d0=true;
	    }
	    
	    if(!electronAnalysisColl.at(i).EcalDrivenSeed()) ecalseeded = false;
	    if(!electronAnalysisColl.at(i).GsfCtfScPixChargeConsistency()) pass_charge_cons=false;
	  }
	  
	  if(nbjet==0){
	    FillCutFlow("SS_0bj_t",weight);
	    if(pass_same_vertex) {
	      FillCutFlow("SS_sv_t",weight);
	      if(!fail_conv) {
		FillCutFlow("SS_noconv_t",weight);
		if(!fail_d0){
		  FillCutFlow("SS_d0_t",weight);
		  if(pass_charge_cons) FillCutFlow("SS_sc_t",weight);
		}
	      }
	    }
	  }
	}
      }
    }// SS 
  }

    
  /*
    /// Check all other el WPs
  if (electronMediumColl.size() == 2) {
    if(electronMediumColl.at(0).Charge() == electronMediumColl.at(1).Charge()){
      FillCLHist(sighist, "SSDiElectronMedium", eventbase->GetEvent(), muonTightColl,electronMediumColl,jetColl_lepveto, weight);    
      FillCLHist(elhist, "SSDiElectronMedium_Electrons", electronMediumColl, eventbase->GetEvent().JetRho(),weight);
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
	  FillCutFlow("SSDiEl_medium",weight);
        }
      } 
    }
  }

  if (electronMVAColl.size() == 2) {
    if(electronMVAColl.at(0).Charge() == electronMVAColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
	  FillCutFlow("SSDiEl_mva",weight);
	}
      }
    }
  }

      

  if (electronTrigTightColl.size() == 2) {
    if(electronTrigTightColl.at(0).Charge() == electronTrigTightColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
          FillCutFlow("SSDiEl_trigtight",weight);
        }
      }
    }
  }
  if (electronTrigWP70Coll.size() == 2) {
    if(electronTrigWP70Coll.at(0).Charge() == electronTrigWP70Coll.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
        if(nloose_lep == 2){
          FillCutFlow("SSDiEl_trigwp70",weight);
	}
      }
    }
  }
  
  if (electronEOPColl.size() == 2) {
    if(electronEOPColl.at(0).Charge() == electronEOPColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
        if(nloose_lep == 2){
          FillCutFlow("SSDiEl_eop",weight);
	}
      }
    }
  }
  
  */
  
  
  return;
}// End of execute event loop

void HNDiElectron::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(electrons.size() != 2 ) return;
  if(electrons.at(0).Pt() < 20.) return;
  if(electrons.at(1).Pt() < 20.) return;
  if(!SameCharge(electrons)) return;
  if(jets.size() < 2) return;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ; 
  if(eejj.M()  > 200.) return;
    
  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return;
  
  if(ee.M() > 80.) return;
  if(eventbase->GetEvent().PFMET() > 35.) return;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
  }
  if(nbjet > 0) return;

  if(name.Contains("iso_d0")) FillIsoCutFlow(name.Data(),w);
  else FillCutFlow(name.Data(),w);
  
}

void HNDiElectron::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() == 2) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){


	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.4){
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

void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void HNDiElectron::BeginCycle() throw( LQError ){
  
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

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     
     
void HNDiElectron::FillCutFlow(TString cut, float weight){

  
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
     
     
void HNDiElectron::FillIsoCutFlow(TString cut, float weight){
       
  
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


void HNDiElectron::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiElectron::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiElectronCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiElectron::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



