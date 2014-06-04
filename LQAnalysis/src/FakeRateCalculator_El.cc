// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQFakeRateCalculator_El Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
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
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
 
  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl);
  
  if(electronLooseColl.size() ==0) return;
  
  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);

  std::vector<snu::KMuon> muonLooseColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonLooseColl);

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);

  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);


  std::vector<snu::KJet> jetColl_lepveto20;
  std::vector<snu::KJet> jetColl_lepveto40;
  std::vector<snu::KJet> jetColl_lepveto60;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto20, muonTightColl, electronTightColl);
  eventbase->GetJetSel()->SetPt(40.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto40, muonTightColl, electronTightColl);
  eventbase->GetJetSel()->SetPt(60.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto60, muonTightColl, electronTightColl);
    
  /// Single Trigger List
  std::vector<TString> triggerslist17;
  triggerslist17.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  std::vector<TString> triggerslist17jet;
  triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  
  /// Calcalate prescale weights
  float prescale_trigger17 = (16.95) / 19789 ;
  float prescale_trigger17jet = (24.18) / 19789 ;

  
  if(!k_isdata){
    Float_t ptbins[8] = { 15.,20.,25.,30.,35.,40.,60.,100.};
    float el_pt = electronLooseColl.at(0).Pt();
    if(electronLooseColl.at(0).GetType() >1 ) {
      if (electronLooseColl.size() == 1 &&jetColl_lepveto40.size() >= 1){
	FillHist("MCLooseEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	FillHist("MCLooseEl_pt",el_pt , weight, ptbins, 7);
	FillHist("MCLooseEl_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
	
	if(electronTightColl.size() == 1){
	  FillHist("MCTightEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	  FillHist("MCTightEl_pt", el_pt, weight, ptbins, 7);
	  FillHist("MCTightEl_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
	}
      }
    }
  }
  
  
  
  if(electronLooseColl.size()==1){
    if(electronLooseColl.at(0).Pt() < 20.){
      std::vector<TString> triggerslist8jet;
      triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
      bool pass_el8jettrig= false;
      if(PassTrigger(triggerslist8jet, prescale))pass_el8jettrig= true;
      float prescale_trigger8jet = (4.85) / 19789 ;
      if(k_isdata) prescale_trigger8jet=1.;
      if(pass_el8jettrig){
	if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLowPtLooseElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight*prescale_trigger8jet);
	if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleLowPtTightElJet", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight*prescale_trigger8jet);
      }
      
      /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
      if(!k_isdata) {
	/// ONLY INCLUDE ELECTRONS FROM W/Z
	if(electronLooseColl.at(0).GetType() >1 ) prescale_trigger8jet=0.;
      }
      
      if(pass_el8jettrig){
	if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLowPtLooseElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight*prescale_trigger8jet);
	if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleLowPtTightElJet_tm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight*prescale_trigger8jet);
      }
    }
  }
  
  if(electronLooseColl.size()==1&& electronLooseColl.at(0).Pt() < 20.) return;
  
  float weight_jet = weight;
  

  if(!k_isdata && (PassTrigger(triggerslist17jet, prescale) )){
    if(electronLooseColl.at(0).Pt() >= 20.){
      weight_jet *= prescale_trigger17jet;
    }
  }

  bool pass_el17jettrig= false;
  if(PassTrigger(triggerslist17jet, prescale)) FillCutFlow("Trigger_Ele17Jet", weight_jet);
  if(PassTrigger(triggerslist17jet, prescale))pass_el17jettrig= true;
  

  m_logger << DEBUG << "Running real efficiency code" << LQLogger::endmsg;
  
  if(PassTrigger(triggerslist_diel, prescale)){
    if(electronLooseColl.size() == 2){
      FillCLHist(sighist, "DiLooseEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      if(Zcandidate(electronLooseColl, 5.)){
	   FillCLHist(sighist, "ZDiLooseEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
	
	//// Electron 1 IS TAG
	if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho())  ){
	  
	  FillHist("h_promptrate_denom_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  FillHist("h_promptrate_denom_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	  FillHist("h_promptrate_denom_njets", jetColl_lepveto20.size(), weight, 0., 5.,5);
	  if(electronLooseColl.at(1).IsEBFiducial()){
	    FillHist("h_promptrate_denom_barrel_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  }
	  else if(electronLooseColl.at(1).IsEEFiducial()){
	    FillHist("h_promptrate_denom_endcap_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  }
	  
	  /// Electron 2 is probe
	  if(IsTight(electronLooseColl.at(1), eventbase->GetEvent().JetRho()) ){
	    FillHist("h_promptrate_num_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    FillHist("h_promptrate_num_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	    FillHist("h_promptrate_num_njets", jetColl_lepveto20.size(), weight, 0., 5.,5);
	    if(electronLooseColl.at(1).IsEBFiducial()){
	      FillHist("h_promptrate_num_barrel_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    }
	    else if(electronLooseColl.at(1).IsEEFiducial()){
	      FillHist("h_promptrate_num_endcap_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    }
	  }
	}
	
	//// Electron 2 IS TAG
	if(IsTight(electronLooseColl.at(1), eventbase->GetEvent().JetRho())){
	  
          FillHist("h_promptrate_denom_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          FillHist("h_promptrate_denom_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	  FillHist("h_promptrate_denom_njets", jetColl_lepveto20.size(), weight, 0., 5.,5);
	  if(electronLooseColl.at(0).IsEBFiducial()){
            FillHist("h_promptrate_denom_barrel_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          }
          else if(electronLooseColl.at(0).IsEEFiducial()){
            FillHist("h_promptrate_denom_endcap_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          }
	  
	  //// Electron 1 is probe
          if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho())){
            FillHist("h_promptrate_num_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
            FillHist("h_promptrate_num_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	    FillHist("h_promptrate_num_njets", jetColl_lepveto20.size(), weight, 0., 5.,5);
	    if(electronLooseColl.at(0).IsEBFiducial()){
	      FillHist("h_promptrate_num_barrel_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
	    }
	    else if(electronLooseColl.at(0).IsEEFiducial()){
	      FillHist("h_promptrate_num_endcap_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
	    }

          }
	}      	
      }
    }
    if(electronTightColl.size() == 2.)FillCLHist(sighist, "DiTightEl", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
  }
  
  if(electronLooseColl.size() != 1) return;

  FillCLHist(sighist, "SingleEl_nocut", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);


  m_logger << DEBUG << "Running fake efficiency code" << LQLogger::endmsg;
  if(pass_el17jettrig) FillCutFlow("Ele17Jet_single_el", weight_jet);
  

  if(pass_el17jettrig) FillCutFlow("Ele17Jet_gt1jet", weight_jet);
  
  if(muonLooseColl.size() > 0) return;

  if(pass_el17jettrig) FillCutFlow("Ele17Jet_muonveto", weight_jet);

  
  if(PassTrigger(triggerslist17jet, prescale)) n_17_jet_pass++;
  
  /// REMOVE Z like events
  if(electronVetoColl.size() == 2) {
    if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
      snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
      if(Z.M() > 76. && Z.M() < 106.) return;
    }
  }
  
  if(pass_el17jettrig) FillCutFlow("Ele17Jet_Zveto", weight_jet);

  
  /// Z and W veto
  Double_t MT=0;
  Double_t METdphi=0;
  
  m_logger << DEBUG << "Filling single lepton + 1 jet plots " << LQLogger::endmsg;
  
  if(pass_el17jettrig){
    if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
  }
    
  for(unsigned int w = 0; w < electronLooseColl.size();  w++){
    METdphi = TVector2::Phi_mpi_pi(electronLooseColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
    MT = sqrt(2.* electronLooseColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
  }

  bool truth_match=true;
 
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    /// ONLY INCLUDE ELECTRONS FROM W/Z
    if(electronLooseColl.at(0).GetType() > 1)  truth_match=false;
  }
  
  if(pass_el17jettrig&&truth_match){
    if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_tm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
  }
  
  
  m_logger << DEBUG << "making cuts to remove prompt leptons" << LQLogger::endmsg;
  m_logger << DEBUG << "Selecting region to calculate MC SFs " << LQLogger::endmsg;
  
  if(eventbase->GetEvent().PFMET() > 30 && (60. < MT)  &&(MT < 100.) &&truth_match){
    
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
    }
  }
  
  if(eventbase->GetEvent().PFMET() > 50 && (60. < MT)  &&(MT < 100.)&& truth_match){
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
    }
  }

  
  if( (eventbase->GetEvent().PFMET() < 20) && (MT < 20.) &&truth_match){
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_tight", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
      if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_tight", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
    }
  }
  
  if( (eventbase->GetEvent().PFMET() < 25) && (MT < 25.) &&truth_match ){
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_medium", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
      if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_medium", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
    }
  }
  
  if( (eventbase->GetEvent().PFMET() < 30) && MT < 30. &&truth_match){
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_loose", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
      if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_loose", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
    }
  }
  
  if( (eventbase->GetEvent().PFMET() < 40) && MT < 40. &&truth_match){
    if(pass_el17jettrig){
      if (electronLooseColl.size() == 1&& jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_vloose", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight_jet);
      if (electronLooseColl.size() == 1 && electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_vloose", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight_jet);
    }
  }
  
  
  if( !( (eventbase->GetEvent().PFMET() < 20) && (MT < 25.)) ) return;
  if(!pass_el17jettrig) return;
  weight =weight_jet;
  
  m_logger << DEBUG << "Making plots for fake rates with different jet cuts" << LQLogger::endmsg;

  bool useevent20= false;
  bool useevent40= false;
  bool useevent60= false;
  /// Fake Rates

  if (electronLooseColl.size() == 1  && jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	
        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto20.at(ij));
	if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65) continue;
	//if( (jetColl_lepveto20.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 2.) useevent20 = true;
      }
    }
  }

  if (electronLooseColl.size() == 1  && jetColl_lepveto40.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto40.size(); ij++){

        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto40.at(ij));
        if( (jetColl_lepveto40.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto40.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
        //if( (jetColl_lepveto40.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 2.) useevent40 = true;
      }
    }
  }



  if (electronLooseColl.size() == 1  && jetColl_lepveto60.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto60.size(); ij++){

        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto60.at(ij));
        if( (jetColl_lepveto60.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto60.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
        //if( (jetColl_lepveto60.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 2.) useevent60 = true;
      }
    }
  }
  
  Float_t ptbins[8] = { 15.,20.,25.,30.,35.,40.,60.,100.};
  
  float el_pt = electronLooseColl.at(0).Pt();
  if(electronLooseColl.at(0).Pt() > 100.) el_pt = 99.;
  
  
  if(useevent20&&truth_match){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1){
      FillHist("TightEl20_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50); 
      FillHist("TightEl20_pt",el_pt, weight, ptbins, 7);     
      FillHist("TightEl20_njets", jetColl_lepveto20.size(), weight, 0.,5.,5); 
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl20_pt_eta1",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl20_pt_eta2",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl20_pt_eta3",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl20_pt_eta4",el_pt, weight, ptbins, 7);
	 
      FillCLHist(sighist, "TightEl20", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    }
    
    if (electronLooseColl.size() == 1 &&jetColl_lepveto20.size() >= 1){
      FillHist("LooseEl20_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl20_pt", el_pt, weight,  ptbins, 7);
      FillHist("LooseEl20_njets", jetColl_lepveto20.size(), weight, 0.,5.,5); 
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl20_pt_eta1", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl20_pt_eta2", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl20_pt_eta3", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl20_pt_eta4", el_pt, weight, ptbins, 7);

      FillCLHist(sighist, "LooseEl20", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
    }
  }    

  if(useevent40){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "TightEl40_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    if (electronLooseColl.size() == 1 &&jetColl_lepveto40.size() >= 1) FillCLHist(sighist, "LooseEl40_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    
  }

  if(useevent40&&truth_match){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto40.size() >= 1){
      FillHist("TightEl40_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("TightEl40_pt",el_pt, weight,  ptbins, 7);
      FillHist("TightEl40_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl40_pt_eta1",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl40_pt_eta2",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl40_pt_eta3",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl40_pt_eta4",el_pt, weight, ptbins, 7);
      FillCLHist(sighist, "TightEl40", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    }

    if (electronLooseColl.size() == 1 &&jetColl_lepveto40.size() >= 1){
      FillHist("LooseEl40_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl40_pt", el_pt, weight,  ptbins, 7);
      FillHist("LooseEl40_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl40_pt_eta1", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl40_pt_eta2", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl40_pt_eta3", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl40_pt_eta4", el_pt, weight, ptbins, 7);

      FillCLHist(sighist, "LooseEl40", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    }
  }

  if(useevent60&&truth_match){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto60.size() >= 1){
      FillHist("TightEl60_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("TightEl60_pt",el_pt, weight, ptbins, 7);
      FillHist("TightEl60_njets", jetColl_lepveto60.size(), weight, 0.,5.,5);
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl60_pt_eta1",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl60_pt_eta2",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl60_pt_eta3",el_pt, weight, ptbins, 7);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl60_pt_eta4",el_pt, weight, ptbins, 7);

      FillCLHist(sighist, "TightEl60", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto60, weight);
    }

    if (electronLooseColl.size() == 1 &&jetColl_lepveto60.size() >= 1){
      FillHist("LooseEl60_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl60_pt", el_pt, weight, ptbins, 7);
      FillHist("LooseEl60_njets", jetColl_lepveto60.size(), weight, 0.,5.,5);
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl60_pt_eta1", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl60_pt_eta2", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl60_pt_eta3", el_pt, weight, ptbins, 7);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl60_pt_eta4", el_pt, weight, ptbins, 7);
      FillCLHist(sighist, "LooseEl60", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto60, weight);
    }
  }
  
  
  return;
}// End of execute event loop



void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger<< INFO << "Number of events that pass 17 GeV trigger = " << n_17_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV + jet trigger = " << n_17_jet_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV || jet trigger = " << n_17_17_jet_pass  << LQLogger::endmsg;

}

bool FakeRateCalculator_El::IsTight(snu::KElectron el, double jetrho ){
  
  return eventbase->GetElectronSel()->HNIsTight(el, jetrho,false);

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


void FakeRateCalculator_El::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",10,0.,10.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"Trigger_Ele17");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"Trigger_Ele17Jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"Ele17_single_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"Ele17Jet_single_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"Ele17_gt1jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"Ele17Jet_gt1jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"Ele17_muonveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"Ele17Jet_muonveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"Ele17_Zveto");	
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"Ele17Jet_Zveto");
  }
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



