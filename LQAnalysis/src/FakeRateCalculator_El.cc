// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQFakeRateCalculator_El Frame - ROOT-based analysis framework for Korea SNU
OB * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/


/// Local includes
#include "FakeRateCalculator_El.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (FakeRateCalculator_El);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
FakeRateCalculator_El::FakeRateCalculator_El() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("FakeRateCalculator_El");

  Message("In FakeRateCalculator_El constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void FakeRateCalculator_El::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  return;
}


void FakeRateCalculator_El::ExecuteEvents()throw( LQError ){
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   
  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  

  //////
  //////
  ////// Code will get fake rates for:
  //////
  ////// 1) Medium POG ID
  ////// 2) Tight POG ID
  ////// 3) M/T with 0.01 -> 0.06 IP cuts
  ////// 4) M/T with numerous isolations 
  //////
  ////// 5) MC fake rates 
  ////// 6) fake rates varying loose sample 
  ////// 7) HST
  //////
  //////
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  
  /// Loose collection for analysis (dxy cut < 0.01)

  std::vector<snu::KElectron> electronLooseColl_tight = GetElectrons(false, true, "loose");
  
  /// Loose collection for analysis (dxy cut < 0.01)
  std::vector<snu::KElectron> electronLooseColl_medium = GetElectrons(false,true,"loose_mediumID");
  std::vector<snu::KElectron> electronLooseColl_susy   = GetElectrons(false,true,"loose_susy");
  
  /// For systematics run with diferent loose samples
  std::vector<snu::KElectron> electronLooseColl_iso05,electronLooseColl_iso07;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.4,electronLooseColl_iso05);
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.6,electronLooseColl_iso07);
  std::vector<snu::KElectron> electronLooseColl_tight_relaxed_ipcut = GetElectrons(true, true, "loose_relaxipcut");

  
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronLooseColl_tight.begin(); it != electronLooseColl_tight.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt(), true);
    }
  }
  
  std::vector<snu::KElectron> electronTightColl = GetElectrons(false,true,"HNTight");
  
  map<TString, vector<snu::KElectron> > elcollmap;
  if(false){
    elcollmap["dxy_05_tight"] = GetElectrons(false,true,"dxy_05_tight");  
    elcollmap["dxy_10_tight"] = GetElectrons(false,true,"dxy_10_tight");  
    elcollmap["dxy_15_tight"] = GetElectrons(false,true,"dxy_15_tight");  
    elcollmap["dxy_20_tight"] = GetElectrons(false,true,"dxy_20_tight");  
    elcollmap["dxy_25_tight"] = GetElectrons(false,true,"dxy_25_tight");  
    elcollmap["dxy_30_tight"] = GetElectrons(false,true,"dxy_30_tight");  
    
    elcollmap["medium_pog"] =  GetElectrons(false,true,"id_medium");
    elcollmap["tight_pog"]  =  GetElectrons(false,true,"id_tight");
    elcollmap["susy_pog"]   =  GetElectrons(false,true,"id_susy");
    
    elcollmap["electronTightColl_dr03_b150_e150"] = GetElectrons(false,true,"tight_iso_b150_e150");
    elcollmap["electronTightColl_dr03_b150_e125"] = GetElectrons(false,true,"tight_iso_b150_e125");
    elcollmap["electronTightColl_dr03_b150_e10"]  = GetElectrons(false,true,"tight_iso_b150_e10");
    elcollmap["electronTightColl_dr03_b150_e09"]  = GetElectrons(false,true,"tight_iso_b150_e09");
    elcollmap["electronTightColl_dr03_b150_e08"]  = GetElectrons(false,true,"tight_iso_b150_e08");
    elcollmap["electronTightColl_dr03_b150_e07"]  = GetElectrons(false,true,"tight_iso_b150_e07");
    elcollmap["electronTightColl_dr03_b150_e06"]  = GetElectrons(false,true,"tight_iso_b150_e06");
    elcollmap["electronTightColl_dr03_b150_e05"]  = GetElectrons(false,true,"tight_iso_b150_e05");
    
    elcollmap["electronTightColl_dr03_b125_e125"] = GetElectrons(false,true,"tight_iso_b125_e125");
    elcollmap["electronTightColl_dr03_b125_e10"]  = GetElectrons(false,true,"tight_iso_b125_e10");
    elcollmap["electronTightColl_dr03_b125_e09"]  = GetElectrons(false,true,"tight_iso_b125_e09");
    elcollmap["electronTightColl_dr03_b125_e08"]  = GetElectrons(false,true,"tight_iso_b125_e08");
    elcollmap["electronTightColl_dr03_b125_e07"]  = GetElectrons(false,true,"tight_iso_b125_e07");
    elcollmap["electronTightColl_dr03_b125_e06"]  = GetElectrons(false,true,"tight_iso_b125_e06");
    elcollmap["electronTightColl_dr03_b125_e05"]  = GetElectrons(false,true,"tight_iso_b125_e05");
    
    elcollmap["electronTightColl_dr03_b10_e125"] = GetElectrons(false,true,"tight_iso_b10_e125");
    elcollmap["electronTightColl_dr03_b10_e10"]  = GetElectrons(false,true,"tight_iso_b10_e10");
    elcollmap["electronTightColl_dr03_b10_e09"]  = GetElectrons(false,true,"tight_iso_b10_e09");
    elcollmap["electronTightColl_dr03_b10_e08"]  = GetElectrons(false,true,"tight_iso_b10_e08");
    elcollmap["electronTightColl_dr03_b10_e07"]  = GetElectrons(false,true,"tight_iso_b10_e07");
    elcollmap["electronTightColl_dr03_b10_e06"]  = GetElectrons(false,true,"tight_iso_b10_e06");
    elcollmap["electronTightColl_dr03_b10_e05"]  = GetElectrons(false,true,"tight_iso_b10_e05");
    
    elcollmap["electronTightColl_dr03_b09_e125"] = GetElectrons(false,true,"tight_iso_b09_e125");
    elcollmap["electronTightColl_dr03_b09_e10"]  = GetElectrons(false,true,"tight_iso_b09_e10");
    elcollmap["electronTightColl_dr03_b09_e09"]  = GetElectrons(false,true,"tight_iso_b09_e09");
    elcollmap["electronTightColl_dr03_b09_e08"]  = GetElectrons(false,true,"tight_iso_b09_e08");
    elcollmap["electronTightColl_dr03_b09_e07"]  = GetElectrons(false,true,"tight_iso_b09_e07");
    elcollmap["electronTightColl_dr03_b09_e06"]  = GetElectrons(false,true,"tight_iso_b09_e06");
    elcollmap["electronTightColl_dr03_b09_e05"]  = GetElectrons(false,true,"tight_iso_b09_e05");
    
    elcollmap["electronTightColl_dr03_b08_e125"] = GetElectrons(false,true,"tight_iso_b08_e125");
    elcollmap["electronTightColl_dr03_b08_e10"]  = GetElectrons(false,true,"tight_iso_b08_e10");
    elcollmap["electronTightColl_dr03_b08_e09"]  = GetElectrons(false,true,"tight_iso_b08_e09");
    elcollmap["electronTightColl_dr03_b08_e08"]  = GetElectrons(false,true,"tight_iso_b08_e08");
    elcollmap["electronTightColl_dr03_b08_e07"]  = GetElectrons(false,true,"tight_iso_b08_e07");
    elcollmap["electronTightColl_dr03_b08_e06"]  = GetElectrons(false,true,"tight_iso_b08_e06");
    elcollmap["electronTightColl_dr03_b08_e05"]  = GetElectrons(false,true,"tight_iso_b08_e05");
    
    elcollmap["electronTightColl_dr03_b07_e125"] = GetElectrons(false,true,"tight_iso_b07_e125");
    elcollmap["electronTightColl_dr03_b07_e10"]  = GetElectrons(false,true,"tight_iso_b07_e10");
    elcollmap["electronTightColl_dr03_b07_e09"]  = GetElectrons(false,true,"tight_iso_b07_e09");
    elcollmap["electronTightColl_dr03_b07_e08"]  = GetElectrons(false,true,"tight_iso_b07_e08");
    elcollmap["electronTightColl_dr03_b07_e07"]  = GetElectrons(false,true,"tight_iso_b07_e07");
    elcollmap["electronTightColl_dr03_b07_e06"]  = GetElectrons(false,true,"tight_iso_b07_e06");
    elcollmap["electronTightColl_dr03_b07_e05"]  = GetElectrons(false,true,"tight_iso_b07_e05");
    
    elcollmap["electronTightColl_dr03_b06_e125"] = GetElectrons(false,true,"tight_iso_b06_e125");
    elcollmap["electronTightColl_dr03_b06_e10"]  = GetElectrons(false,true,"tight_iso_b06_e10");
    elcollmap["electronTightColl_dr03_b06_e09"]  = GetElectrons(false,true,"tight_iso_b06_e09");
    elcollmap["electronTightColl_dr03_b06_e08"]  = GetElectrons(false,true,"tight_iso_b06_e08");
    elcollmap["electronTightColl_dr03_b06_e07"]  = GetElectrons(false,true,"tight_iso_b06_e07");
    elcollmap["electronTightColl_dr03_b06_e06"]  = GetElectrons(false,true,"tight_iso_b06_e06");
    elcollmap["electronTightColl_dr03_b06_e05"]  = GetElectrons(false,true,"tight_iso_b06_e05");
    
    elcollmap["electronTightColl_dr03_b05_e125"] = GetElectrons(false,true,"tight_iso_b05_e125");
    elcollmap["electronTightColl_dr03_b05_e10"]  = GetElectrons(false,true,"tight_iso_b05_e10");
    elcollmap["electronTightColl_dr03_b05_e09"]  = GetElectrons(false,true,"tight_iso_b05_e09");
    elcollmap["electronTightColl_dr03_b05_e08"]  = GetElectrons(false,true,"tight_iso_b05_e08");
    elcollmap["electronTightColl_dr03_b05_e07"]  = GetElectrons(false,true,"tight_iso_b05_e07");
    elcollmap["electronTightColl_dr03_b05_e06"]  = GetElectrons(false,true,"tight_iso_b05_e06");
    elcollmap["electronTightColl_dr03_b05_e05"]  = GetElectrons(false,true,"tight_iso_b05_e05");
  }
  
  std::vector<snu::KMuon> muonLooseColl = GetMuons("loose");
  std::vector<snu::KMuon> muonTightColl = GetMuons("tight");
  
  if(muonLooseColl.size() > 0) return;
  
  std::vector<snu::KElectron> electronVetoColl = GetElectrons(false, false, "veto");
  
  std::vector<snu::KJet> jetColl_lepveto20 = GetJets("ApplyPileUpID");
  std::vector<snu::KJet> jetColl_lepveto = GetJets("ApplyLeptonVeto");
  std::vector<snu::KJet> jetColl           = GetJets("NoLeptonVeto");

  std::vector<snu::KJet> jetColl_loose           = GetJets("loosest");
  

  std::vector<snu::KGenJet> genBColl;
  for(unsigned int ig=0; ig < eventbase->GetGenJets().size(); ig++){
    if(eventbase->GetGenJets().at(ig).Pt() < 10.) continue;
    if(fabs(eventbase->GetGenJets().at(ig).Eta()) > 3.) continue;
    genBColl.push_back(eventbase->GetGenJets().at(ig));
  }
  
  
  /// MAKE JET PLOT
  FillHist(("N_loose_el"), electronLooseColl_tight_relaxed_ipcut.size(), 1., 0.,3.,3);
  FillHist(("N_tight_el"), electronTightColl.size(), 1., 0.,3.,3);
  if(electronLooseColl_tight_relaxed_ipcut.size() == 2)  FillHist(("N_2ltight_el"), electronTightColl.size(), 1., 0.,3.,3);


  if(jetColl_lepveto.size() > 1){
    FillHist(("N_loose_dijet_el"), electronLooseColl_tight_relaxed_ipcut.size(), 1., 0.,4.,4);
    FillHist(("N_tight_dijet_el"), electronTightColl.size(), 1., 0.,4.,4);
    if(electronLooseColl_tight_relaxed_ipcut.size() == 2)     FillHist(("N_2l_tight_dijet_el"), electronTightColl.size(), 1., 0.,2.,2);
 
  }
  

  if(electronLooseColl_tight_relaxed_ipcut.size() == 2) {
    if(jetColl_lepveto.size() > 1){
      if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	FillHist(("LNTPt_fakeobject"), electronLooseColl_tight_relaxed_ipcut.at(1).Pt(), 1., 0.,200.,100);
	FillHist(("N_not_tight_el"), 1, 1., 0.,2.,2);
	for(unsigned int ig=0; ig < jetColl_loose.size(); ig++){
	  if(electronLooseColl_tight_relaxed_ipcut.at(1).DeltaR(jetColl_loose.at(ig)) < 0.3){
	    FillHist(("N_not_tight_closejet_el"), 1, 1., 0.,2.,2);
	    FillHist(("JetPt_fakeobject"), jetColl_loose.at(ig).Pt(), 1., 0.,200.,100);
	  }
	}
      }
      if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	FillHist(("N_not_tight_el"), 1, 1., 0.,2.,2);
	FillHist(("LNTPt_fakeobject"), electronLooseColl_tight_relaxed_ipcut.at(0).Pt(), 1., 0.,200.,100);
	for(unsigned int ig=0; ig < jetColl_loose.size(); ig++){
	  if(electronLooseColl_tight_relaxed_ipcut.at(0).DeltaR(jetColl_loose.at(ig)) < 0.3){
	    FillHist(("N_not_tight_closejet_el"), 1, 1., 0.,2.,2);
	    FillHist(("JetPt_fakeobject"), jetColl_loose.at(ig).Pt(), 1., 0.,200.,100);
	  }
	}
      }
    }
  }
  
  if(electronLooseColl_tight_relaxed_ipcut.size() > 1) {
    if(electronLooseColl_tight_relaxed_ipcut.at(0).Pt() > 10.){
      if(jetColl_lepveto.size() > 0){
	if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	  for(unsigned int ig=0; ig < genBColl.size(); ig++){
	    if(electronLooseColl_tight_relaxed_ipcut.at(1).DeltaR(genBColl.at(ig)) < 0.3){
	      FillHist(("GenJetPt_fakeobject"), genBColl.at(ig).Pt(), 1., 0.,200.,100);
	    }
	  }
	}
	if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	  for(unsigned int ig=0; ig < genBColl.size(); ig++){
	    if(electronLooseColl_tight_relaxed_ipcut.at(0).DeltaR(genBColl.at(ig)) < 0.3){
	      FillHist(("GenJetPt_fakeobject"), genBColl.at(ig).Pt(), 1., 0.,200.,100);
	    }
	  }
	}
      }
    }
  }


  if(k_sample_name.Contains("QCD") || k_sample_name.Contains("W")|| (k_sample_name.Contains("tt") && SameCharge(electronLooseColl_tight_relaxed_ipcut))){
    if(electronLooseColl_tight_relaxed_ipcut.size() == 2){
      if(electronLooseColl_tight_relaxed_ipcut.at(0).Pt() > 10.){
	if(jetColl_lepveto.size() >= 1){
	  if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	    for(unsigned int ig=0; ig <  genBColl.size(); ig++){
	      if(electronLooseColl_tight_relaxed_ipcut.at(0).DeltaR( genBColl.at(ig)) < 0.3){
		FillHist(("GenJetPt_fakeobject_sig"),  genBColl.at(ig).Pt(), 1., 0.,200.,100);
	      }
	    }
	  }
	  
	  if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	    for(unsigned int ig=0; ig <  genBColl.size(); ig++){
              if(electronLooseColl_tight_relaxed_ipcut.at(1).DeltaR( genBColl.at(ig)) < 0.3){
		FillHist(("GenJetPt_fakeobject_sig"),  genBColl.at(ig).Pt(), 1., 0.,200.,100);
	      }
	    }
	  }
	}
      }
    }
  }
  if(k_sample_name.Contains("QCD") || k_sample_name.Contains("W")|| (k_sample_name.Contains("tt") && SameCharge(electronLooseColl_tight_relaxed_ipcut))){
    if(electronLooseColl_tight_relaxed_ipcut.size() == 2){
      if(electronLooseColl_tight_relaxed_ipcut.at(0).Pt() > 10.){
        if(jetColl_lepveto.size() >= 1){
          if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
            for(unsigned int ig=0; ig < jetColl_loose.size(); ig++){
              if(electronLooseColl_tight_relaxed_ipcut.at(0).DeltaR(jetColl_loose.at(ig)) < 0.3){
                FillHist(("JetPt_fakeobject_sig"), jetColl_loose.at(ig).Pt(), 1., 0.,200.,100);
              }
            }
          }

          if(!IsTight(electronLooseColl_tight_relaxed_ipcut.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
            for(unsigned int ig=0; ig < jetColl_loose.size(); ig++){
              if(electronLooseColl_tight_relaxed_ipcut.at(1).DeltaR(jetColl_loose.at(ig)) < 0.3){
                FillHist(("JetPt_fakeobject_sig"), jetColl_loose.at(ig).Pt(), 1., 0.,200.,100);
              }
            }
          }
        }
      }
    }
  }

  return; 
  
  

  std::vector<TString> triggerslist17jet;
  triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  std::vector<TString> triggerslist8jet;
  triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  
  int nbjetmc(0);
  for(unsigned int ij =0 ; ij < jetColl_lepveto20.size() ; ij++){
    if(jetColl_lepveto20.at(ij).CombinedSecVertexBtag() > 0.679) nbjetmc++;
  }
    
  
  if(!k_isdata){
    
    /// Make rate plots for closure test on use QCD

    bool triggerpass = (PassTrigger(triggerslist17jet, prescale) ||  (PassTrigger(triggerslist8jet, prescale)));
    MakeMCFakeratePlots("", triggerpass,electronLooseColl_tight , jetColl_lepveto20, jetColl, weight);      
    MakeMCFakeratePlots("relaxed_ipcut",triggerpass,electronLooseColl_tight_relaxed_ipcut , jetColl_lepveto20, jetColl, weight);      
    
    /// Makes rate plot for all MC;  
    if(PassTrigger(triggerslist17jet, prescale) ||  (PassTrigger(triggerslist8jet, prescale))){
      if(electronLooseColl_tight.size() == 1)MakeMCPlots("Singlelep",electronLooseColl_tight.at(0), jetColl_lepveto20, jetColl, weight);      
      if(electronLooseColl_tight_relaxed_ipcut.size() == 1)MakeMCPlots("Singlelep_relaxedd0",electronLooseColl_tight_relaxed_ipcut.at(0), jetColl_lepveto20, jetColl, weight);     
      if(electronLooseColl_tight.size() == 1)MakeMCPlots("Singlelep_photon",electronLooseColl_tight.at(0), jetColl_lepveto20, jetColl, weight);
      if(electronLooseColl_tight_relaxed_ipcut.size() == 1)MakeMCPlots("Singlelep_relaxedd0_photon",electronLooseColl_tight_relaxed_ipcut.at(0), jetColl_lepveto20, jetColl, weight);

      
      if(electronLooseColl_tight_relaxed_ipcut.size() >1 ){
	MakeMCPlots("Dilep_relaxedd0",electronLooseColl_tight_relaxed_ipcut.at(0), jetColl_lepveto20, jetColl, weight);      
	MakeMCPlots("Dilep_relaxedd0",electronLooseColl_tight_relaxed_ipcut.at(1), jetColl_lepveto20, jetColl, weight);
      }
      if(electronLooseColl_tight.size() >1){
	MakeMCPlots("Dilep",electronLooseColl_tight.at(0), jetColl_lepveto20, jetColl, weight);      
	MakeMCPlots("Dilep",electronLooseColl_tight.at(1), jetColl_lepveto20, jetColl, weight);      
	
	MakeMCPlots("Dilep_photon",electronLooseColl_tight.at(0), jetColl_lepveto20, jetColl, weight);
        MakeMCPlots("Dilep_photon",electronLooseColl_tight.at(1), jetColl_lepveto20, jetColl, weight);
	if(k_sample_name.Contains("QCD") || (electronLooseColl_tight.at(0).Charge() == electronLooseColl_tight.at(1).Charge())){
	  if(jetColl_lepveto20.size() > 1){
	    if(electronLooseColl_tight.at(0).GetType() == 0 || electronLooseColl_tight.at(0).GetType() == 7 || electronLooseColl_tight.at(1).GetType() == 0 || electronLooseColl_tight.at(1).GetType() == 7 ){
	      std::vector<snu::KElectron> fakelep;
	      if(!(electronLooseColl_tight.at(0).GetType() == 0 || electronLooseColl_tight.at(0).GetType() == 7 )) fakelep.push_back(electronLooseColl_tight.at(0));
	      if(!(electronLooseColl_tight.at(1).GetType() == 0 || electronLooseColl_tight.at(1).GetType() == 7 )) fakelep.push_back(electronLooseColl_tight.at(1));
	      FillCLHist(sighist, "SingleElFake", eventbase->GetEvent(), muonLooseColl,fakelep,jetColl_lepveto20, weight);
	      FillCLHist(sighist, "SingleElFake_alllep", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
	    }
	    else 
	      FillCLHist(sighist, "DoubleElFake", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
	  }
	}
      }
    }
  }
  
  
  // Dilepton CR
  if(PassTrigger(triggerslist_diel, prescale)){
    if(electronTightColl.size() ==2){
      if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge()){
	if(jetColl_lepveto.size() > 0){
	  FillCLHist(sighist, "DoubleEl", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto, weight);
	}
      }
    }
    if(electronLooseColl_tight.size() == 2){
      if(electronLooseColl_tight.at(0).Charge() != electronLooseColl_tight.at(1).Charge()){
        if(jetColl_lepveto.size() > 0){
          FillCLHist(sighist, "DoubleEl_loose", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto, weight);
        }
      }
    }
  }

 
  if(electronLooseColl_medium.size() == 0 && electronLooseColl_tight_relaxed_ipcut.size() ==0) return;
  /// Calcalate prescale weights
  float prescale_trigger =  GetPrescale(electronLooseColl_tight, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale)); 
  float prescale_trigger_iso05 =  GetPrescale(electronLooseColl_iso05, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale)); 
  float prescale_trigger_iso07 =  GetPrescale(electronLooseColl_iso07, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale)); 
  float prescale_trigger_relaxed_ipcut =  GetPrescale(electronLooseColl_tight_relaxed_ipcut, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale)); 
  float prescale_trigger_medium =  GetPrescale(electronLooseColl_medium, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale));
  float prescale_trigger_susy =  GetPrescale(electronLooseColl_susy, PassTrigger(triggerslist8jet, prescale), PassTrigger(triggerslist17jet, prescale));
  
  if(electronVetoColl.size() <= 1) {
    
    MakeFakeRatePlots("HNTight", electronTightColl, electronLooseColl_tight,  jetColl_lepveto20, jetColl,  prescale_trigger, weight);
    MakeFakeRatePlots("HNTight_relaxedip", electronTightColl, electronLooseColl_tight_relaxed_ipcut,  jetColl_lepveto20, jetColl,prescale_trigger_relaxed_ipcut, weight);
    MakeFakeRatePlots("HNTight_iso05", electronTightColl, electronLooseColl_iso05, jetColl_lepveto20, jetColl, prescale_trigger_iso05, weight);
    MakeFakeRatePlots("HNTight_iso07", electronTightColl, electronLooseColl_iso07, jetColl_lepveto20, jetColl,prescale_trigger_iso07, weight);
    
    
    for(map<TString, vector<snu::KElectron> >::iterator mapit  = elcollmap.begin(); mapit !=  elcollmap.end(); mapit++){
      
      if(mapit->first.Contains("medium_pog"))MakeFakeRatePlots(mapit->first, mapit->second, electronLooseColl_medium,  jetColl_lepveto20, jetColl,prescale_trigger_medium, weight);
      else if(mapit->first.Contains("susy_pog"))MakeFakeRatePlots(mapit->first, mapit->second, electronLooseColl_susy,jetColl_lepveto20, jetColl, prescale_trigger_susy, weight);
      else  {
	MakeFakeRatePlots(mapit->first, mapit->second, electronLooseColl_tight, jetColl_lepveto20, jetColl, prescale_trigger, weight);
	MakeFakeRatePlots(mapit->first + "_relaxedip", mapit->second, electronLooseColl_tight_relaxed_ipcut, jetColl_lepveto20, jetColl, prescale_trigger, weight);
      }
      
    }
  }
    
  
  if(prescale_trigger == 0.) return;

  weight *= prescale_trigger;
  
  // Dilepton CR
  if(electronTightColl.size() ==2){
    if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 0){
	FillCLHist(sighist, "DoubleEl_strig", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto, weight);
      }
    }
  }
  if(electronLooseColl_tight.size() == 2){
    if(electronLooseColl_tight.at(0).Charge() != electronLooseColl_tight.at(1).Charge()){
      if(jetColl_lepveto.size() > 0){
	FillCLHist(sighist, "DoubleEl_loose_strig", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto, weight);
      }
    }
  }
 
  if(electronVetoColl.size() > 1) return;

  bool truth_match=false;
  
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    if(electronLooseColl_tight.size() > 0){
      /// ONLY INCLUDE ELECTRONS FROM W/Z
      if((electronLooseColl_tight.at(0).GetType() == 0) || (electronLooseColl_tight.at(0).GetType() ==7))  truth_match=true;
    }
    else truth_match = true;
  }
  else truth_match=true;
  
  if(truth_match){
    if (jetColl_lepveto20.size() >= 1 ){
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
	FillCLHist(sighist, "SingleLooseElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }
    
    if (electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
	FillCLHist(sighist, "SingleTightElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }
  }
  
  if(true){
    if (jetColl_lepveto20.size() >= 1 ){
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
        FillCLHist(sighist, "SingleLooseElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }

    if (electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
        FillCLHist(sighist, "SingleTightElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }
  }
  
  m_logger << DEBUG << "making cuts to remove prompt leptons" << LQLogger::endmsg;
  m_logger << DEBUG << "Selecting region to calculate MC SFs " << LQLogger::endmsg;
  

  Double_t MT=0;
  Double_t METdphi=0;
  for(unsigned int w = 0; w < electronLooseColl_tight.size();  w++){
    METdphi = TVector2::Phi_mpi_pi(electronLooseColl_tight.at(w).Phi()- eventbase->GetEvent().PFMETphi());
    MT = sqrt(2.* electronLooseColl_tight.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
  }
  
  if(eventbase->GetEvent().PFMET() > 40 && (60. < MT)  &&(MT < 100.) &&truth_match){
    
    if(electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
	FillCLHist(sighist, "SingleTightElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      }
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
	FillCLHist(sighist, "SingleTightElJet40_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }
    if(jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
        FillCLHist(sighist, "SingleLooseElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      }
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
        FillCLHist(sighist, "SingleLooseElJet40_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      }
    }
  }
  
  bool useevent40        = UseEvent(electronLooseColl_tight , jetColl_lepveto20, 40., weight, weight);
  bool useevent40_allmt  = UseEventAllMT(electronLooseColl_tight , jetColl_lepveto20, 40., weight, weight);
  

  if(useevent40){
    if ( electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "TightEl30_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    if (jetColl_lepveto20.size() >= 1) FillCLHist(sighist, "LooseEl30_notm", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
    
    if(truth_match){
      if ( electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "TightEl30", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      if (jetColl_lepveto20.size() >= 1) FillCLHist(sighist, "LooseEl30", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      
    }
  }
  
  if(useevent40_allmt){
    if ( electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "TightEl30_allmt_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    if (jetColl_lepveto20.size() >= 1) FillCLHist(sighist, "LooseEl30_allmt_notm", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);

    if(truth_match){
      if ( electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "TightEl30_allmt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      if (jetColl_lepveto20.size() >= 1) FillCLHist(sighist, "LooseEl30_allmt", eventbase->GetEvent(), muonLooseColl,electronLooseColl_tight,jetColl_lepveto20, weight);
      
    }
  }
  
  
  
  return;
}// End of execute event loop


void FakeRateCalculator_El::GetHSTRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag){

  Float_t htbins[14] = { 20.,22.5, 25.,27.5, 30.,35.,40.,45.,50.,60.,80.,100.,200., 1000.};

  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
      if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  if( tight_el.size() == 1 && jets.size() >= 1){
    FillHist(("MeasuredEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("MeasuredEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("MeasuredEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("MeasuredEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);
  }
  
  if( loose_el.size() == 1 && jets.size() >= 1){
    FillHist(("HSTLooseEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("HSTLooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("HSTLooseEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("HSTLooseEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);    
    
    float hstweight= m_fakeobj->getFakeRate_electronEta(0, loose_el.at(0).Pt(),loose_el.at(0).Eta(), tag);
    FillHist(("PredictedEl" + tag + "_njets").Data(), jets.size(), hstweight, 0.,5.,5);
    FillHist(("PredictedEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), hstweight, 0., 30., 30);
    FillHist(("PredictedEl" + tag + "_ht").Data(), SumPt(jets), hstweight, htbins, 13);
    FillHist(("PredictedEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);

  }  
}


void FakeRateCalculator_El::GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString tag, double w){

  Float_t ptbins[10] = { 10., 15.,20.,25.,30.,35.,45.,60.,100., 200.};
  Float_t ptbinsb[8] = { 10., 15.,20.,30.,45.,60.,100., 200.};
  Float_t etabin[2] = { 0.,  2.5};
  Float_t etabins[3] = { 0., 1.479,  2.5};
  Float_t etabins2[5] = { 0.,0.8,  1.479, 2.,  2.5};
  Float_t htbins[6] = { 20., 40., 75., 100., 200., 400.};
  Float_t htbinscb[3] = { 20., 100., 400.};

  int nbjet(0);
  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
    if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  bool closebjet = false;
  float awayjetpt = 0.;
  for(unsigned int ij =0 ; ij < alljets.size() ; ij++){
    if(loose_el.at(0).DeltaR(alljets.at(ij)) < 0.5) {
      if(alljets.at(ij).CombinedSecVertexBtag() > 0.679) closebjet = true;
    }     
    float dphi =fabs(TVector2::Phi_mpi_pi(loose_el.at(0).Phi()- alljets.at(ij).Phi()));
    if(dphi > 2.5) awayjetpt = alljets.at(ij).Pt();
    
  }
  
  if( tight_el.size() == 1 && jets.size() >= 1){
    float el_pt = tight_el.at(0).Pt();
    
    // 1D FakeRates
    FillHist(("TightEl" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
    FillHist(("TightEl" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
    if(fabs(tight_el.at(0).Eta()) < 1.5)     FillHist(("TightEl" + tag + "_pt_barrel").Data(),el_pt, w,  ptbins, 9);
    else FillHist(("TightEl" + tag + "_pt_endcap").Data(),el_pt, w,  ptbins, 9);
    
    FillHist(("TightEl" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
    FillHist(("TightEl" + tag + "_eta_binned").Data(),fabs(tight_el.at(0).Eta()), w, etabins, 2);
    FillHist(("TightEl" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    if(fabs(tight_el.at(0).Eta()) < 1.5) FillHist(("TightEl" + tag + "_barrel_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    else FillHist(("TightEl" + tag + "_endcap_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    FillHist(("TightEl" + tag + "_ht_morebins").Data(), SumPt(jets) - awayjetpt, w, 0., 1000., 50);
    FillHist(("TightEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 30., 30);
    FillHist(("TightEl" + tag + "_nbjet").Data(), nbjet, w, 0., 4.,4); 
    
    FillHist(("TightEl" + tag + "_ht_eta").Data(),  SumPt(jets) - awayjetpt,fabs(tight_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
    FillHist(("TightEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets) - awayjetpt, w, ptbins, 9 , htbins, 5);
    FillHist(("TightEl" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
    

    if(nbjet > 0){
      FillHist(("TightEl" + tag + "_bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("TightEl" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("TightEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbinsb, 7 , etabins, 2);
    }
    else{
      FillHist(("TightEl" + tag + "_0bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins,9);
      FillHist(("TightEl" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("TightEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);

    }
    
    if(!closebjet){
      if(nbjet > 0){
	FillHist(("TightEl_nocb" + tag + "_bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("TightEl_nocb" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("TightEl_nocb" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbinsb, 7 , etabins, 2);
      }
      else{
	FillHist(("TightEl_nocb" + tag + "_0bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("TightEl_nocb" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("TightEl_nocb" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
	
      }
    }
    
    float ht = SumPt(jets) - awayjetpt;
    if(closebjet){
      FillHist(("TightEl_cb" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl_cb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("TightEl_cb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("TightEl_cb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("TightEl_cb" + tag + "_ht_eta").Data(),  SumPt(jets) - awayjetpt,fabs(tight_el.at(0).Eta()), w, htbinscb, 2 , etabins, 2);
      FillHist(("TightEl_cb" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    }
    else{
      FillHist(("TightEl_nocb" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl_nocb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("TightEl_nocb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("TightEl_nocb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("TightEl_nocb" + tag + "_ht_eta").Data(),  SumPt(jets)-awayjetpt,fabs(tight_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
      FillHist(("TightEl_nocb" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);

      if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);

      if(nbjet == 0){
	if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
	if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
	if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      }
      else{
	if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
	if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
	if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);

      }
    }

    if( ht > 20 && ht < 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 40 && ht < 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    
  }
  
  
  if(jets.size() >= 1){
    float el_pt = loose_el.at(0).Pt();
    
    if(!isData){
      if(!IsTight(loose_el.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	for(unsigned int k = 0 ; k <  alljets.size(); k++){
	  if(loose_el.at(0).DeltaR(alljets.at(k)) < 0.3){
	    FillHist((("JetPt_fakeobject_fakerate" + tag).Data()), alljets.at(k).Pt(), w, 0.,200.,100);
	  }
	}
      }
      for(unsigned int k = 0 ; k <  alljets.size(); k++){
	for(unsigned int k = 0 ; k <  alljets.size(); k++){
	  if(loose_el.at(0).DeltaR(alljets.at(k)) < 0.3){
	    FillHist((("JetPt_fakeobject_fakerate_all_" + tag).Data()), alljets.at(k).Pt(), w, 0.,200.,100);
	  }
	}
      }
    }
    
    if(!isData){
      if(!IsTight(loose_el.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
        for(unsigned int k = 0 ; k <  eventbase->GetGenJets().size(); k++){
          if(loose_el.at(0).DeltaR(eventbase->GetGenJets().at(k)) < 0.3){
            FillHist((("GenJetPt_fakeobject_fakerate" + tag).Data()), eventbase->GetGenJets().at(k).Pt(), w, 0.,200.,100);
          }
        }
      }
      for(unsigned int k = 0 ; k <  alljets.size(); k++){
	for(unsigned int k = 0 ; k <  eventbase->GetGenJets().size(); k++){
	  if(loose_el.at(0).DeltaR(eventbase->GetGenJets().at(k)) < 0.3){
	    FillHist((("GenJetPt_fakeobject_fakerate_all_" + tag).Data()), eventbase->GetGenJets().at(k).Pt(), w, 0.,200.,100);
	  }
	}
      }
    }

    
    FillHist(("LooseEl" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
    FillHist(("LooseEl" + tag + "_pt").Data(), el_pt, w,  ptbins, 9);
    if(fabs(loose_el.at(0).Eta()) < 1.5)     FillHist(("LooseEl" + tag + "_pt_barrel").Data(),el_pt, w,  ptbins, 9);
    else FillHist(("LooseEl" + tag + "_pt_endcap").Data(),el_pt, w,  ptbins, 9);

    FillHist(("LooseEl" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
    FillHist(("LooseEl" + tag + "_eta_binned").Data(),fabs(loose_el.at(0).Eta()), w, etabins, 2);
    FillHist(("LooseEl" + tag + "_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
    FillHist(("LooseEl" + tag + "_ht_morebins").Data(), SumPt(jets) - awayjetpt, w, 0., 1000., 50);

    if(fabs(loose_el.at(0).Eta()) < 1.5) FillHist(("LooseEl" + tag + "_barrel_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    else FillHist(("LooseEl" + tag + "_endcap_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);


    FillHist(("LooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 30., 30);
    FillHist(("LooseEl" + tag + "_nbjet").Data(), nbjet, w, 0., 4.,4);
    
    FillHist(("LooseEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets)-awayjetpt, w, ptbins, 9 , htbins, 5);
    FillHist(("LooseEl" + tag + "_ht_eta").Data(), SumPt(jets) - awayjetpt,fabs(loose_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
    FillHist(("LooseEl" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);

    if( ( SumPt(jets)-awayjetpt ) < 0. ) cout << "ht is = " << ( SumPt(jets)-awayjetpt ) << endl;

    if(nbjet > 0){
      FillHist(("LooseEl" + tag + "_bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("LooseEl" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbinsb,7 , etabins, 2);
    }
    else{
      FillHist(("LooseEl" + tag + "_0bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("LooseEl" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
    }
    
    if(!closebjet){
      if(nbjet > 0){
	FillHist(("LooseEl_nocb" + tag + "_bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("LooseEl_nocb" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("LooseEl_nocb" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbinsb,7 , etabins, 2);
      }
      else{
	FillHist(("LooseEl_nocb" + tag + "_0bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("LooseEl_nocb" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("LooseEl_nocb" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
      }
    }

    float ht = SumPt(jets) - awayjetpt;
    if(closebjet){
      FillHist(("LooseEl_cb" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl_cb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("LooseEl_cb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("LooseEl_cb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("LooseEl_cb" + tag + "_ht_eta").Data(),  SumPt(jets)-awayjetpt,fabs(loose_el.at(0).Eta()), w, htbinscb, 2 , etabins, 2);
      FillHist(("LooseEl_cb" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    }
    else{
      FillHist(("LooseEl_nocb" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl_nocb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("LooseEl_nocb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("LooseEl_nocb" + tag + "_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl_nocb" + tag + "_ht_eta").Data(), SumPt(jets)-awayjetpt,fabs(loose_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
      FillHist(("LooseEl_nocb" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);


      if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9, etabins, 2);
      if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);

      if(nbjet == 0){
	if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
	if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins,9 , etabins, 2);
        if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      } 
      else{
	if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
        if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
        if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);

      } 
    }
    
    if( ht > 20 && ht < 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 40 && ht < 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9, etabins, 2);



  }
  
  return;
}



void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger<< INFO << "Number of events that pass 17 GeV trigger = " << n_17_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV + jet trigger = " << n_17_jet_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV || jet trigger = " << n_17_17_jet_pass  << LQLogger::endmsg;

}

bool FakeRateCalculator_El::IsTight(snu::KElectron el, double jetrho , double dxy, double biso, double eiso,bool usetight){
  
  return eventbase->GetElectronSel()->HNIsTight(el, jetrho, dxy, biso, eiso,  usetight, false);

}



void FakeRateCalculator_El::BeginCycle() throw( LQError ){
  
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

  n_17_jet_pass=0;
  n_17_17_jet_pass=0;
  n_17_pass=0;

  
  return;
  
}

FakeRateCalculator_El::~FakeRateCalculator_El() {
  
  Message("In FakeRateCalculator_El Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}



void FakeRateCalculator_El::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void FakeRateCalculator_El::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this FakeRateCalculator_ElCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void FakeRateCalculator_El::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}


bool FakeRateCalculator_El::UseEvent(std::vector<snu::KElectron> electrons,  std::vector< snu::KJet> jets, float awayjetcut, float precale_weight, float wt){
  
  if(wt < 0.) return false;
  bool useevent = false;
  if(precale_weight != 0.){
    
    /// Z and W veto
    Double_t MT=0;
    Double_t METdphi=0;
    for(unsigned int w = 0; w < electrons.size();  w++){
      METdphi = TVector2::Phi_mpi_pi(electrons.at(w).Phi()- eventbase->GetEvent().PFMETphi());
      MT = sqrt(2.* electrons.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
      
      if(( (eventbase->GetEvent().PFMET() < 20) && (MT < 25.)) ) {
	
        for (unsigned int ielT=0; ielT < electrons.size(); ielT++){
          for(unsigned int ij=0; ij < jets.size(); ij++){
            if(jets.at(ij).Pt() < awayjetcut) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electrons.at(ielT).Phi()- jets.at(ij).Phi()));
            if( (jets.at(ij).NeutralEMEnergyFraction() +jets.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	    if(dphi > 2.5) useevent = true;
          }
        }
      }
    }
  }
  return useevent;
}

bool FakeRateCalculator_El::UseEventAllMT(std::vector<snu::KElectron> electrons,  std::vector< snu::KJet> jets, float awayjetcut, float precale_weight, float wt){
  if(wt < 0.) return false;

  bool useevent = false;
  if(precale_weight != 0.){

    for(unsigned int w = 0; w < electrons.size();  w++){

      for (unsigned int ielT=0; ielT < electrons.size(); ielT++){
	for(unsigned int ij=0; ij < jets.size(); ij++){
	  if(jets.at(ij).Pt() < awayjetcut) continue;
	  float dphi =fabs(TVector2::Phi_mpi_pi(electrons.at(ielT).Phi()- jets.at(ij).Phi()));
	  if( (jets.at(ij).NeutralEMEnergyFraction() +jets.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	  if(dphi > 2.5) useevent = true;
	}
      }
    }
  }
  return useevent;
}



void FakeRateCalculator_El::MakeFakeRatePlots(TString label, std::vector<snu::KElectron> electrons_tight, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, float prescale_w, float w){
  
  if(electrons.size() == 0 ) return;
  if(prescale_w==0.) return;
  
  bool useevent20 = UseEvent(electrons , jets, 20., prescale_w, w); 
  bool useevent30 = UseEvent(electrons , jets, 30., prescale_w, w); 
  bool useevent40 = UseEvent(electrons , jets, 40., prescale_w, w); 
  bool useevent60 = UseEvent(electrons , jets, 60., prescale_w, w); 

  bool truth_match= false;
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    if(electrons.size() > 0){
      /// ONLY INCLUDE ELECTRONS FROM W/Z
      if((electrons.at(0).GetType() == 0) || (electrons.at(0).GetType() ==7))  truth_match=true;
    }
    else truth_match = true;
  }
  else truth_match=true;
  
  
  if(jets.size() >= 1){
    if(useevent20)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_20", (prescale_w * w));
    if(useevent30)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_30", (prescale_w * w));
    if(useevent40)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_40", (prescale_w * w));
    if(useevent60)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_60", (prescale_w * w));
  }

  if(truth_match){

    if(jets.size() >= 1){
      if(useevent20)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_20", (prescale_w * w));
      if(useevent30)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_30", (prescale_w * w));
      if(useevent40)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_40", (prescale_w * w));
      if(useevent60)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_60", (prescale_w * w));
    }
  }
}

float FakeRateCalculator_El::GetPrescale( std::vector<snu::KElectron> electrons, bool passlow, bool passhigh){
  
  float prescale_trigger= 0.;
  if(electrons.size() ==1){
    if(electrons.at(0).Pt() >= 20.){

      if(passhigh){
        prescale_trigger = (16.95) / 19789 ; //// 20 + GeV bins
      }
      else prescale_trigger = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(passlow){
        prescale_trigger = (3.546650) / 19789 ;
      }
      else prescale_trigger = 0.;
    }
  }

  if(prescale_trigger == 0.) return 0.;
  if(k_isdata) return 1.;
  
  return prescale_trigger;
}

void FakeRateCalculator_El::MakeMCFakeratePlots(TString label, bool pass_single_trigger, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, double w){
  
  if(pass_single_trigger && (jets.size() > 0)){
    if(electrons.size()==1){
      MakePlotsMCAwaJetPt(label+"20", 20., electrons, jets ,  alljets, w);
      MakePlotsMCAwaJetPt(label+"30", 30., electrons, jets ,  alljets, w);
      MakePlotsMCAwaJetPt(label+"40", 50., electrons, jets ,  alljets, w);
      MakePlotsMCAwaJetPt(label+"60", 60., electrons, jets ,  alljets, w);
      MakePlotsMCAwaJetPt(label+"80", 80., electrons, jets ,  alljets, w);
      MakePlotsMCAwaJetPt(label+"100",100.,electrons, jets ,  alljets, w);
      
    }
  }
  
}

void FakeRateCalculator_El::MakePlotsMCAwaJetPt(TString label,float awayjetptcut, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets , std::vector<snu::KJet> alljets, double w){
  
  Float_t ptbins[7]   = { 10.,15.,20.,25.,30.,40.,60.};
  Float_t htbins[6]   = { 20., 40., 75., 100., 200., 400.};
  Float_t etabinsmc[3] = { 0.,  1.479, 2.5};
  
  bool useevent=false;
  bool closebjet= false;
  float ptawayjet = 0.;
  for(unsigned int ijet = 0; ijet < alljets.size(); ijet++){
    float dphi =fabs(TVector2::Phi_mpi_pi(electrons.at(0).Phi()- alljets.at(ijet).Phi()));
    
    if(dphi > 2.5) {
      if(alljets.at(ijet).Pt() > awayjetptcut)  useevent=true;
      ptawayjet = alljets.at(ijet).Pt();
    }
    if(electrons.at(0).DeltaR(alljets.at(ijet)) < 0.5){
      if(alljets.at(ijet).CombinedSecVertexBtag() > 0.679)  closebjet = true;
    }
  }
  
  int nbjetmc(0);
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjetmc++;
  }


  if(!useevent) return;
  
  float ht =  (SumPt(jets) - ptawayjet);
  FillHist("MCLooseEl_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  FillHist("MCLooseEl_" +label + "_ht_eta", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins,5 , etabinsmc, 2);
    
  if(!closebjet){
    if(ht > 20. && ht < 100.)   FillHist("MCLooseEl_" +label + "ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    if(ht > 40. && ht < 100.)   FillHist("MCLooseEl_" +label + "ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    if(ht > 100.)   FillHist("MCLooseEl_" +label + "ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);

    if(nbjetmc == 0){
      if(ht > 20. && ht < 100.)   FillHist("MCLooseEl_" +label + "_0bjet_ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 40. && ht < 100.)   FillHist("MCLooseEl_" +label + "_0bjet_ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 100.)   FillHist("MCLooseEl_" +label + "_0bjet_ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    }
    else{
      if(ht > 20. && ht < 100.)   FillHist("MCLooseEl_" +label + "_bjet_ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 40. && ht < 100.)   FillHist("MCLooseEl_" +label + "_bjet_ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 100.)   FillHist("MCLooseEl_" +label + "_bjet_ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    }
  }

  if(ht > 20. && ht < 100.)   FillHist("MCLooseEl_" +label + "ht1_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  if(ht > 40. && ht < 100.)   FillHist("MCLooseEl_" +label + "ht2_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  if(ht > 100.)   FillHist("MCLooseEl_" +label + "ht3_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);


  if(nbjetmc == 0)
    FillHist("MCLooseEl_" +label + "_0bjet_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  else
    FillHist("MCLooseEl_" +label + "_bjet_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  
  if(!closebjet){
    if(nbjetmc == 0)
      FillHist("MCLooseEl_" +label + "_0bjet_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    else
      FillHist("MCLooseEl_" +label + "_bjet_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  }
    
  if(closebjet)
    FillHist("MCLooseEl_" +label + "_ht_eta_cb", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins,5 , etabinsmc, 2);
  else 
    FillHist("MCLooseEl_" +label + "_ht_eta_nocb", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins,5 , etabinsmc, 2);
  
  if(closebjet)
    FillHist("MCLooseEl_closebjet_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  else
    FillHist("MCLooseEl_noclosebjet_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
  
  
  if(IsTight(electrons.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){

    FillHist("MCTightEl_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    FillHist("MCTightEl_" +label + "_ht_eta", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins, 5, etabinsmc, 2);

    if(nbjetmc ==0)
      FillHist("MCTightEl_" +label + "_0bjet_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    else
      FillHist("MCTightEl_" +label + "_bjet_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    
    if(!closebjet){
      if(nbjetmc == 0)
	FillHist("MCTightEl_" +label + "_0bjet_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      else
	FillHist("MCTightEl_" +label + "_bjet_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      
    }
    if(closebjet)
      FillHist("MCTightEl_" +label + "_ht_eta_cb", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins,5 , etabinsmc, 2);
    else
      FillHist("MCTightEl_" +label + "_ht_eta_nocb", (SumPt(jets) - ptawayjet), fabs(electrons.at(0).Eta()), w,  htbins,5 , etabinsmc, 2);


    if(closebjet)
      FillHist("MCTightEl_closebjet_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    else
      FillHist("MCTightEl_noclosebjet_" +label + "_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    

    if(ht > 20. && ht < 100.)   FillHist("MCTightEl_" +label + "ht1_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    if(ht > 40. && ht < 100.)   FillHist("MCTightEl_" +label + "ht2_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
    if(ht > 100.)   FillHist("MCTightEl_" +label + "ht3_pt_eta", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);

    if(!closebjet){
      if(ht > 20. && ht < 100.)   FillHist("MCTightEl_" +label + "ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 40. && ht < 100.)   FillHist("MCTightEl_" +label + "ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      if(ht > 100.)   FillHist("MCTightEl_" +label + "ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);

      if(nbjetmc == 0){
	if(ht > 20. && ht < 100.)   FillHist("MCTightEl_" +label + "_0bjet_ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
	if(ht > 40. && ht < 100.)   FillHist("MCTightEl_" +label + "_0bjet_ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
	if(ht > 100.)   FillHist("MCTightEl_" +label + "_0bjet_ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      }
      else{
	if(ht > 20. && ht < 100.)   FillHist("MCTightEl_" +label + "_bjet_ht1_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
	if(ht > 40. && ht < 100.)   FillHist("MCTightEl_" +label + "_bjet_ht2_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
	if(ht > 100.)   FillHist("MCTightEl_" +label + "_bjet_ht3_pt_eta_nocb", electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), w,  ptbins, 6, etabinsmc, 2);
      }

    }
  }
  
}


void FakeRateCalculator_El::MakeMCPlots(TString label, snu::KElectron electron, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, double w){
  
  Float_t ptbins[8] = { 10., 15.,20.,25.,30.,35.,40.,60.};
  Float_t htptbins[7] = {10., 15.,20.,25.,30.,40.,60.};
  Float_t htbins[7] = { 20., 40., 75., 100., 200., 400., 1000.};
  Float_t stbins[9] = { 35., 50., 75., 100., 150.,200., 250., 300, 400.};

  int nbjetmc(0);
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjetmc++;
  }
  
  bool dilep_event = false;
  if(label.Contains("Dilep"))dilep_event = true;
  
  bool fake_lep= false;
  if(label.Contains("photon")){
    if((electron.GetType() == 6 )) fake_lep = true;
  }
  else  if((electron.GetType() == 1  || electron.GetType() == 2 || electron.GetType() ==  3)) fake_lep = true;

  if(fake_lep){
    
    if(jets.size() > 0){
      if(electron.Pt() > 15.){
	bool awayjet=false;
	bool closebjet=false;
	float ptawayjet(0.);
	/// plot FR if away jet is btagged
	for(unsigned int ijet =0 ; ijet < alljets.size() ; ijet++){

	  float dphi =fabs(TVector2::Phi_mpi_pi(electron.Phi()- alljets.at(ijet).Phi()));
	  
	  if( dphi > 2.5){
	    if(!awayjet) ptawayjet=alljets.at(ijet).Pt();
	    if(alljets.at(ijet).Pt() > 40.) awayjet=true;
	  }
	  if( electron.DeltaR(alljets.at(ijet)) < 0.5){
	    if(alljets.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	  }
	}
	
	if( (!dilep_event) && !awayjet) return;
	
	FillHist(label + "_MCLooseEl_closebjet",   closebjet, w, 0.,2., 2);
	FillHist(label + "_MCLooseEl_awayjet_pt", ptawayjet, w, 0., 100., 20);
	
	if(!(closebjet ))   {
	  FillHist(label + "_MCLooseEl_noclosejet_nbjet", nbjetmc, w, 0.,4.,4);
	}
	else   FillHist(label + "_MCLooseEl_noclosejet_nbjet" , -1, w, 0.,4.,4);
	
	if(dilep_event) ptawayjet = 0.;
	FillHist(label + "_MCLooseEl_eta", electron.Eta(), w, -2.5, 2.5,50);
	FillHist(label + "_MCLooseEl_pt", electron.Pt() , w, ptbins, 7);
	FillHist(label + "_MCLooseEl_njets", jets.size(), w, 0.,10.,10);
	FillHist(label + "_MCLooseEl_ht", SumPt(jets) - ptawayjet, w, htbins, 6);
	
	if(fabs(electron.Eta()) < 1.47) FillHist(label + "_MCLooseEl_ht_barrel", SumPt(jets) - ptawayjet, w, htbins, 6);
	else FillHist(label + "_MCLooseEl_ht_endcap", SumPt(jets) - ptawayjet, w, htbins, 6);
	FillHist(label + "_MCLooseEl_finebins_ht", SumPt(jets) - ptawayjet, w, 0., 1000., 20);
	FillHist(label + "_MCLooseEl_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	FillHist(label + "_MCLooseEl_nbjet", nbjetmc, w, 0.,6.,6);

	if(!(closebjet )) {
	  if(nbjetmc > 0 ) { 
	    FillHist(label + "_MCLooseEl_bjet_eta", electron.Eta(), w, -2.5, 2.5,50);
	    FillHist(label + "_MCLooseEl_bjet_pt", electron.Pt() , w, ptbins, 7);
	    FillHist(label + "_MCLooseEl_bjet_njets", jets.size(), w, 0.,10.,10);
	    FillHist(label + "_MCLooseEl_bjet_ht", SumPt(jets) - ptawayjet, w, htbins, 6);
	  }
	}
	
	if(closebjet){
	  FillHist(label + "_MCLooseEl_cb_eta", electron.Eta(), w, -2.5, 2.5,50);
	  FillHist(label + "_MCLooseEl_cb_pt",electron.Pt() , w, ptbins, 7);
	  FillHist(label + "_MCLooseEl_cb_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	  FillHist(label + "_MCLooseEl_cb_ht", (SumPt(jets)- ptawayjet), w, htbins, 6);
	}
	else{
	  FillHist(label + "_MCLooseEl_nocb_eta", electron.Eta(), w, -2.5, 2.5,50);
          FillHist(label + "_MCLooseEl_nocb_pt",electron.Pt() , w, ptbins, 7);
	  FillHist(label + "_MCLooseEl_nocb_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	  FillHist(label + "_MCLooseEl_nocb_ht", (SumPt(jets)- ptawayjet), w, htbins, 6);

	  
	  if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_eta_ht3", fabs(electron.Eta()), w, 0., 3.,2);
	  else {
	    if((SumPt(jets) -ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_eta_ht2", fabs(electron.Eta()), w, 0., 3.,2);
	    if((SumPt(jets) -ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_eta_ht1", fabs(electron.Eta()), w, 0., 3.,2);
	  }
	  
	  
	  if(fabs(electron.Eta()) < 1.5){
	    if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_barrel_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	    else {
	      if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_barrel_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
	      if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_barrel_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	    }
	  }
	  else{
	    if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_endcap_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	    else {
	      if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_endcap_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
	      if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_endcap_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	    }
	  }
	  
	  if(nbjetmc  > 0 ) {
	    if(fabs(electron.Eta()) < 1.5){
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_barrel_bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_barrel_bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_barrel_bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }
	    
	    else{
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_endcap_bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_endcap_bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_endcap_bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }
	  }
	  else{
	    if(fabs(electron.Eta()) < 1.5){
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_barrel_0bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_barrel_0bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_barrel_0bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }
	    else{
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCLooseEl_nocb_endcap_0bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCLooseEl_nocb_endcap_0bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCLooseEl_nocb_endcap_0bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }
	    
	  }
	}
	
	if(IsTight(electron, eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true)){
	  
	  FillHist(label + "_MCTightEl_closebjet",   closebjet, w, 0.,2., 2);
	  FillHist(label + "_MCTightEl_awayjet_pt", ptawayjet, w, 0., 100., 20);

	  if(!(closebjet )) {
	    FillHist(label + "_MCTightEl_closejet",   0, w, 0.,2., 2);
	    FillHist(label + "_MCTightEl_noclosejet_nbjet", nbjetmc, w, 0.,4.,4);
	  }
	  else FillHist(label + "_MCTightEl_closejet",   1, w, 0.,2., 2);

	  FillHist(label + "_MCTightEl_eta", electron.Eta(), w, -2.5, 2.5,50);
	  FillHist(label + "_MCTightEl_pt", electron.Pt(), w, ptbins, 7);
	  FillHist(label + "_MCTightEl_njets", jets.size(), w, 0.,10.,10);
	  FillHist(label + "_MCTightEl_finebins_ht", SumPt(jets) - ptawayjet, w, 0., 1000., 20);
	  FillHist(label + "_MCTightEl_ht", SumPt(jets) - ptawayjet, w, htbins, 6);
	  if(fabs(electron.Eta()) < 1.47)FillHist(label + "_MCTightEl_ht_barrel", SumPt(jets) - ptawayjet, w, htbins, 6);
	  else FillHist(label + "_MCTightEl_ht_endcap", SumPt(jets) - ptawayjet, w, htbins, 6);
	  FillHist(label + "_MCTightEl_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	  FillHist(label + "_MCTightEl_nbjet", nbjetmc, w, 0.,6.,6);

	  if(!closebjet){
	    if(nbjetmc > 0 ) {
	      FillHist(label + "_MCTightEl_bjet_eta", electron.Eta(), w, -2.5, 2.5,50);
	      FillHist(label + "_MCTightEl_bjet_pt", electron.Pt() , w, ptbins, 7);
	      FillHist(label + "_MCTightEl_bjet_njets", jets.size(), w, 0.,10.,10);
	      FillHist(label + "_MCTightEl_bjet_ht", SumPt(jets) - ptawayjet, w, htbins, 6);
	    }
	  }
	  if(closebjet){
	    FillHist(label + "_MCTightEl_cb_eta", electron.Eta(), w, -2.5, 2.5,50);
	    FillHist(label + "_MCTightEl_cb_pt",electron.Pt() , w, ptbins, 7);
	    FillHist(label + "_MCTightEl_cb_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	    FillHist(label + "_MCTightEl_cb_ht", (SumPt(jets) - ptawayjet), w, htbins, 6);

	  }
	  else{
	    FillHist(label + "_MCTightEl_nocb_eta", electron.Eta(), w, -2.5, 2.5,50);
	    FillHist(label + "_MCTightEl_nocb_pt",electron.Pt() , w, ptbins, 7);
	    FillHist(label + "_MCTightEl_nocb_st", (SumPt(jets) + electron.Pt()), w, stbins, 8);
	    FillHist(label + "_MCTightEl_nocb_ht", (SumPt(jets)- ptawayjet ), w, htbins, 6);
	    
	    if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_eta_ht3", fabs(electron.Eta()), w, 0., 3.,2);
	    else {
	      if((SumPt(jets) -ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_eta_ht2", fabs(electron.Eta()), w, 0., 3.,2);
	      if((SumPt(jets) -ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_eta_ht1", fabs(electron.Eta()), w, 0., 3.,2);
	    }

	    if(fabs(electron.Eta()) < 1.5){
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_barrel_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_barrel_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_barrel_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }
	    else{
	      if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_endcap_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
	      else{
		if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_endcap_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_endcap_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
	      }
	    }

	    if(nbjetmc  > 0 ) {
	      if(fabs(electron.Eta()) < 1.5){
		if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_barrel_bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
		else{
		  if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_barrel_bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		  if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_barrel_bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
		} 
	      }
	      else{
		if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_endcap_bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
		else{
		  if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_endcap_bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
		  if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_endcap_bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
		} 
	      }
	    }
	    else{
	      if(fabs(electron.Eta()) < 1.5){
		if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_barrel_0bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
		else{
                  if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_barrel_0bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
                  if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_barrel_0bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
                }
              }
              else{
                if((SumPt(jets) - ptawayjet) > 100 )           FillHist(label + "_MCTightEl_nocb_endcap_0bjet_pt_ht3", fabs(electron.Pt()), w, htptbins, 6);
		else{
                  if((SumPt(jets) - ptawayjet) > 40 )           FillHist(label + "_MCTightEl_nocb_endcap_0bjet_pt_ht2", fabs(electron.Pt()), w, htptbins, 6);
                  if((SumPt(jets) - ptawayjet) > 20 )           FillHist(label + "_MCTightEl_nocb_endcap_0bjet_pt_ht1", fabs(electron.Pt()), w, htptbins, 6);
		}
              }

	    }

	  }
	}
      }
    }
  }
}
