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
  
  MakeCleverHistograms(sighist, "DiLooseEl");
  MakeCleverHistograms(sighist, "ZDiLooseEl");
  MakeCleverHistograms(sighist, "DiTightEl");
  MakeCleverHistograms(sighist, "SingleLooseEl");
  MakeCleverHistograms(sighist, "SingleTightEl");
  MakeCleverHistograms(sighist, "LooseEl20");
  MakeCleverHistograms(sighist, "TightEl20");
  MakeCleverHistograms(sighist, "LooseEl40");
  MakeCleverHistograms(sighist, "TightEl40");
  MakeCleverHistograms(sighist, "LooseEl60");
  MakeCleverHistograms(sighist, "TightEl60");

  return;
}


void FakeRateCalculator_El::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
    
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
  /// Single Trigger List 
  std::vector<TString> triggerslist17;
  triggerslist17.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist17.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  std::vector<TString> triggerslist8;
  triggerslist8.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist8.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");

  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
  }
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl);
  
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
    
  
  //// SELECT EVENTS WITH NO MUONS
  if(muonLooseColl.size() > 0) return;

  
  /// Get p rate
  
  if(PassTrigger(triggerslist_diel, prescale)){
    if(electronLooseColl.size() == 2){
      FillCLHist(sighist, "DiLooseEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      snu::KParticle Z = electronLooseColl.at(0) + electronLooseColl.at(1);
      
      if(Z.M() > 86. && Z.M() < 96.){
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
  
  
  /// REMOVE Z like events
  if(electronVetoColl.size() == 2) {
    if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
      snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
      if(Z.M() > 76. && Z.M() < 106.) return;
    }
  }
  
  
  if(!(PassTrigger(triggerslist8, prescale)  ||  PassTrigger(triggerslist17, prescale))) return;
  
  float prescale_trigger8  = (3.55+ 4.86) / 19789 ;
  float prescale_trigger17 = (16.95 + 24.18) / 19789 ;
  
  if(electronLooseColl.at(0).Pt() < 20.){
    if(!(PassTrigger(triggerslist8, prescale))) return;
  }
  else {
    if(!(PassTrigger(triggerslist17, prescale))) return;
  }
  
  if(!k_isdata && PassTrigger(triggerslist8, prescale)) {
    if(electronLooseColl.at(0).Pt() < 20.){
      weight *= prescale_trigger8;
    }
  }
  if(!k_isdata && PassTrigger(triggerslist17, prescale)){
    if(electronLooseColl.at(0).Pt() >= 20.){
      weight *= prescale_trigger17;
    }
  }

  /// Z and W veto
  Double_t MT=0;
  Double_t METdphi=0;
  
  
  if (electronLooseColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "SingleLooseEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight); 
  if (electronLooseColl.size() == 1  && jetColl_lepveto20.size() >= 1 && electronTightColl.size() == 1)FillCLHist(sighist, "SingleTightEl", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight); 
  
  
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    /// ONLY INCLUDE ELECTRONS FROM W/Z
    if(electronLooseColl.at(0).GetType() != 1) return;
  }


  for(unsigned int w = 0; w < electronLooseColl.size();  w++){
    MT = sqrt(2.* electronLooseColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( electronLooseColl.at(w).Phi()- eventbase->GetEvent().PFMETphi())) );
    METdphi = TVector2::Phi_mpi_pi(electronLooseColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
  }
  
  
  if(! (eventbase->GetEvent().PFMET() < 20)) return;
  if(!(MT < 25.)) return;
 
  if(fabs(METdphi) > 0.5) return;
  
  bool useevent20= false;
  bool useevent40= false;
  bool useevent60= false;
  /// Fake Rates

  if (electronLooseColl.size() == 1  && jetColl_lepveto20.size() >= 1){
    for (int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for( int ij=0; ij < jetColl_lepveto20.size(); ij++){
	
        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto20.at(ij));
	if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.8) return;
	if( (jetColl_lepveto20.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 1.) useevent20 = true;
      }
    }
  }

  if (electronLooseColl.size() == 1  && jetColl_lepveto40.size() >= 1){
    for (int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for( int ij=0; ij < jetColl_lepveto40.size(); ij++){

        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto40.at(ij));
        if( (jetColl_lepveto40.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto40.at(ij).ChargedEMEnergyFraction()) > 0.8) return;
        if( (jetColl_lepveto40.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 1.) useevent40 = true;
      }
    }
  }



  if (electronLooseColl.size() == 1  && jetColl_lepveto60.size() >= 1){
    for (int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for( int ij=0; ij < jetColl_lepveto60.size(); ij++){

        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto60.at(ij));
        if( (jetColl_lepveto60.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto60.at(ij).ChargedEMEnergyFraction()) > 0.8) return;
        if( (jetColl_lepveto60.at(ij).Pt() / electronLooseColl.at(ielT).Pt()) < 1.) continue;
        if(dr > 1.) useevent60 = true;
      }
    }
  }
  
  Float_t ptbins[7] = { 15.,20.,25.,30.,35., 40.,60.};
  
  
  if(useevent20){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1){
      FillHist("TightEl20_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50); 
      FillHist("TightEl20_pt", electronTightColl.at(0).Pt(), weight, ptbins, 6);     
      FillHist("TightEl20_njets", jetColl_lepveto20.size(), weight, 0.,5.,5); 
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl20_pt_eta1", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl20_pt_eta2", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl20_pt_eta3", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl20_pt_eta4", electronTightColl.at(0).Pt(), weight, ptbins, 6);
	 
      FillCLHist(sighist, "TightEl20", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    }
    
    if (electronLooseColl.size() == 1 &&jetColl_lepveto20.size() >= 1){
      FillHist("LooseEl20_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl20_pt", electronLooseColl.at(0).Pt(), weight,  ptbins, 6);
      FillHist("LooseEl20_njets", jetColl_lepveto20.size(), weight, 0.,5.,5); 
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl20_pt_eta1", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl20_pt_eta2", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl20_pt_eta3", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl20_pt_eta4", electronLooseColl.at(0).Pt(), weight, ptbins, 6);

      FillCLHist(sighist, "LooseEl20", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
    }
  }    

  if(useevent40){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto40.size() >= 1){
      FillHist("TightEl40_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("TightEl40_pt", electronTightColl.at(0).Pt(), weight,  ptbins, 6);
      FillHist("TightEl40_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl40_pt_eta1", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl40_pt_eta2", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl40_pt_eta3", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl40_pt_eta4", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      FillCLHist(sighist, "TightEl40", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    }

    if (electronLooseColl.size() == 1 &&jetColl_lepveto40.size() >= 1){
      FillHist("LooseEl40_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl40_pt", electronLooseColl.at(0).Pt(), weight,  ptbins, 6);
      FillHist("LooseEl40_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl40_pt_eta1", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl40_pt_eta2", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl40_pt_eta3", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl40_pt_eta4", electronLooseColl.at(0).Pt(), weight, ptbins, 6);

      FillCLHist(sighist, "LooseEl40", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    }
  }

  if(useevent60){
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto60.size() >= 1){
      FillHist("TightEl60_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("TightEl60_pt", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      FillHist("TightEl60_njets", jetColl_lepveto60.size(), weight, 0.,5.,5);
      if(fabs( electronTightColl.at(0).Eta() < 1.)) FillHist("TightEl60_pt_eta1", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 1.479))FillHist("TightEl60_pt_eta2", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.)) FillHist("TightEl60_pt_eta3", electronTightColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronTightColl.at(0).Eta() < 2.5))FillHist("TightEl60_pt_eta4", electronTightColl.at(0).Pt(), weight, ptbins, 6);

      FillCLHist(sighist, "TightEl60", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto60, weight);
    }

    if (electronLooseColl.size() == 1 &&jetColl_lepveto60.size() >= 1){
      FillHist("LooseEl60_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("LooseEl60_pt", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      FillHist("LooseEl60_njets", jetColl_lepveto60.size(), weight, 0.,5.,5);
      if(fabs( electronLooseColl.at(0).Eta() < 1.)) FillHist("LooseEl60_pt_eta1", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 1.479))FillHist("LooseEl60_pt_eta2", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.)) FillHist("LooseEl60_pt_eta3", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      else if(fabs( electronLooseColl.at(0).Eta() < 2.5))FillHist("LooseEl60_pt_eta4", electronLooseColl.at(0).Pt(), weight, ptbins, 6);
      FillCLHist(sighist, "LooseEl60", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto60, weight);
    }
  }
  
  
  return;
}// End of execute event loop



void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}

bool FakeRateCalculator_El::IsTight(snu::KElectron el, double jetrho ){
  //----------------------------------------------------------------------
  // Barrel electron cut values
  //----------------------------------------------------------------------

  double l_b_dEtaIn  = 0.004;
  double l_b_dPhiIn  = 0.03;
  double l_b_sieie   = 0.01;
  double l_b_hoe     = 0.12;
  double l_b_d0      = 0.1;
  double l_b_dZ      = 0.1;
  double l_b_ep      = 0.05;
  double l_b_pfRelIso =0.1;
  double l_b_vtxProb = 1e-6;
  int    l_b_missHits = 0;
  //----------------------------------------------------------------------
  // Endcap electron cut values
  //----------------------------------------------------------------------

  double l_e_dEtaIn  = 0.005;
  double l_e_dPhiIn  = 0.02;
  double l_e_sieie   = 0.03;
  double l_e_hoe     = 0.10;
  double l_e_d0      = 0.02;
  double l_e_dZ      = 0.1;
  double l_e_ep      = 0.05;
  double l_e_vtxProb = 1e-6;
  int    l_e_missHits = 0;
  double l_e_pfRelIso = 0.1;
  //----------------------------------------------------------------------
  // Bools that depend on barrel vs. endcap
  //----------------------------------------------------------------------

  bool   pass_deltaEta      = false;
  bool   pass_deltaPhi      = false;
  bool   pass_sigmaIEtaIEta = false;
  bool   pass_hoe           = false;
  bool   pass_vtxDistXY     = false;
  bool   pass_vtxDistZ      = false;
  bool   pass_ep            = false;
  bool   pass_convFitProb   = false;
  bool   pass_missingHits   = false;
  bool   pass_pfIsolation   = false;



  //----------------------------------------------------------------------
  // Define EGamma ep parameter
  //----------------------------------------------------------------------

  double egamma_e  = el.CaloEnergy();
  double egamma_p  = el.CaloEnergy() / el.ESuperClusterOverP();
  double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

  //----------------------------------------------------------------------
  // Define PF Isolation
  //----------------------------------------------------------------------

  double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
  double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
  double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
  double effective_area_03  = 0.0;


  for (int i = 0; i < 7; ++i ){
    double bin_minimum = effective_area_eta_minimums[i];
    double bin_maximum = effective_area_eta_maximums[i];
    if ( fabs(el.SCEta()) >= bin_minimum && fabs(el.SCEta()) < bin_maximum ) {
      effective_area_03 = effective_areas_03 [i];
    }
  }

  double egamma_pfiso_03 = el.PFChargedHadronIso03() + std::max ( el.PFPhotonIso03() + el.PFNeutralHadronIso03() - ( jetrho * effective_area_03 ), 0.0 );


  egamma_pfiso_03 /= el.Pt();

  //----------------------------------------------------------------------
  // Barrel electron test
  //----------------------------------------------------------------------

  if ( fabs(el.SCEta()) < 1.479 ){

    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_b_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_b_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_b_sieie   );
    pass_hoe           = bool ( el.HoE            ()  <= l_b_hoe     );
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_b_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_b_dZ  );
    pass_ep            = bool ( egamma_ep          <= l_b_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_b_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_b_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_b_pfRelIso);
  }

  else if ( fabs(el.SCEta()) > 1.479 && fabs(el.SCEta()) < 2.5 ){
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_e_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_e_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_e_sieie   );
    pass_hoe           = bool ( el.HoE            ()  <= l_e_hoe     );
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_e_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_e_dZ  );
    pass_ep            = bool ( egamma_ep          <= l_e_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_e_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_e_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_e_pfRelIso);

  }  bool decision = (
                      pass_deltaEta      &&
		      pass_deltaPhi      &&
		      pass_sigmaIEtaIEta &&
		      pass_hoe           &&
		      pass_vtxDistXY     &&
		      pass_vtxDistZ      &&
                       pass_ep            &&
		      pass_pfIsolation   &&
		      pass_convFitProb   &&
		      pass_missingHits   ) ;
  
  return decision;
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
    AnalyzerCore::MakeHistograms("cutflow",13,0.,13.);


    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"SSDiEl_medium");
    
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



