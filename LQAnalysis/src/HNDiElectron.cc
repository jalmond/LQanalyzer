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
  
  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_njet=0, k_ht=0.;
  k_nbjet_l=-1;
  k_nbjet_m=-1;
  k_nbjet_t=-1;
  k_weight=0.;
  k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  
  
  // Signal plots
  MakeCleverHistograms(sighist,"NoCut");
  MakeCleverHistograms(sighist,"NoCutPtEta");
  MakeCleverHistograms(sighist,"Fake");
  
  // Diboson CR
  MakeCleverHistograms(sighist,"TriElCR");
  MakeCleverHistograms(sighist,"TriEl");
  MakeCleverHistograms(sighist,"TriEl_jetmva_inclusive");
  MakeCleverHistograms(sighist,"ZZ");
  
  ///  OS
  MakeCleverHistograms(sighist,"OSee");
  
  MakeCleverHistograms(sighist,"SSloose");
  MakeCleverHistograms(sighist,"SSee");
  MakeCleverHistograms(sighist,"SSee_Z");
  MakeCleverHistograms(sighist,"SSee_0jet_Z");
  MakeCleverHistograms(sighist,"SSee_1jet_Z");
  MakeCleverHistograms(sighist,"SSee_gt0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet");
  MakeCleverHistograms(sighist,"SSee_DiJet");
  
  MakeCleverHistograms(sighist,"SSee_DiJet_20_nor");
  MakeCleverHistograms(sighist,"SSee_DiJet_40_nor");

  MakeCleverHistograms(sighist,"SSee_1jet_20_nor");
  MakeCleverHistograms(sighist,"SSee_1jet_40_nor");
  
  MakeCleverHistograms(sighist,"LowMassRegion");
  MakeCleverHistograms(sighist,"MediumMassRegion");
  MakeCleverHistograms(sighist,"HighMassRegion");
  MakeCleverHistograms(sighist,"LowMassRegion_0905");
  MakeCleverHistograms(sighist,"MediumMassRegion_0905");
  MakeCleverHistograms(sighist,"HighMassRegion_0905");

  MakeCleverHistograms(sighist,"40MassRegion");
  MakeCleverHistograms(sighist,"50MassRegion");
  MakeCleverHistograms(sighist,"60MassRegion");
  MakeCleverHistograms(sighist,"70MassRegion");
  MakeCleverHistograms(sighist,"80MassRegion");
  MakeCleverHistograms(sighist,"90MassRegion");
  MakeCleverHistograms(sighist,"100MassRegion");
  MakeCleverHistograms(sighist,"125MassRegion");
  MakeCleverHistograms(sighist,"150MassRegion");
  MakeCleverHistograms(sighist,"175MassRegion");
  MakeCleverHistograms(sighist,"200MassRegion");
  MakeCleverHistograms(sighist,"225MassRegion");
  MakeCleverHistograms(sighist,"250MassRegion");
  MakeCleverHistograms(sighist,"275MassRegion");
  MakeCleverHistograms(sighist,"300MassRegion");
  MakeCleverHistograms(sighist,"325MassRegion");
  MakeCleverHistograms(sighist,"350MassRegion");
  MakeCleverHistograms(sighist,"375MassRegion");
  MakeCleverHistograms(sighist,"400MassRegion");
  MakeCleverHistograms(sighist,"500MassRegion");
  MakeCleverHistograms(sighist,"600MassRegion");
  MakeCleverHistograms(sighist,"700MassRegion");


  MakeCleverHistograms(sighist,"SSee_noZ");
  MakeCleverHistograms(sighist,"SSee_0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet_noZ");

  MakeCleverHistograms(sighist,"BJetCR");
  MakeCleverHistograms(sighist,"BJetCR_20_nor");
  MakeCleverHistograms(sighist,"BJetCR_40_nor");
  
  MakeCleverHistograms(sighist,"HighMETCR");
  MakeCleverHistograms(sighist,"HighMETCR_20_nor");
  MakeCleverHistograms(sighist,"HighMETCR_40_nor");
  MakeCleverHistograms(sighist,"HighMETBJetCR");

  /// Single lepton
  MakeCleverHistograms(sighist,"SingleEl_CR");
  MakeCleverHistograms(sighist,"SingleEl_bjetCR");
  MakeCleverHistograms(sighist,"SingleElTight_CR");
  MakeCleverHistograms(sighist,"SingleElTight_bjetCR");
  MakeCleverHistograms(sighist,"SingleElLoose_CR");
  MakeCleverHistograms(sighist,"SingleElLoose_bjetCR");
  MakeCleverHistograms(sighist,"SingleEl_promptCR");
  MakeCleverHistograms(sighist,"SingleEl_promptbjetCR");
}


void HNDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){

  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_njet=0, k_ht=0.;
  k_weight=0.;
  k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  k_nbjet_l=-1,k_nbjet_m=-1,k_nbjet_t=-1;
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  


  FillEventCutFlow("NoCut_w",weight);
  FillEventCutFlow("NoCut",1.);

  //if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FillEventCutFlow("EventCut", 1.);
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  //if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  //FillEventCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
  //if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FillEventCutFlow("VertexCut", 1.);
  
  
  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// JETS
  // Jets needed now for electron loose and tight collection:
  /// veto electrons close to a bjet in loose+ tight samples
  /// 15-50 % of fake electrons in mc have close bjet while < 0.5 % of signal electrons do

  std::vector<snu::KJet> jetColl;
  std::vector<snu::KJet> jetColl_dummy;  
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  eventbase->GetJetSel()->SetPt(2000.);
  eventbase->GetJetSel()->Selection(jetColl_dummy);
  
  
  /// ELECTRONS
  std::vector<snu::KElectron> _electronAnalysisColl;
  std::vector<snu::KElectron> _electronAnalysisColl_dummy;

  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronAnalysisColl, jetColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl, jetColl, false);
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronAnalysisColl_dummy, jetColl_dummy);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl_dummy, jetColl_dummy, false);
  


  /// Get Prompt electrons/CF 
  /// As of July 20:New cuts on tight electrons:
  //Remove electrons close to a jet that looks like a real jet.
  ///Use default isolation for 10-20 GeV electrons (0.07%)
  // Add non PF isolation (30% reduction in fakes: 3% reduction in signal)
  std::vector<snu::KElectron> electronAnalysisColl_temp =  GetTruePrompt(_electronAnalysisColl, false, false); // removes CF and fake in mc
  std::vector<snu::KElectron> electronAnalysisColl =ShiftElectronEnergy(electronAnalysisColl_temp, k_running_chargeflip);
  
  /// Check effect of close jet cut
  std::vector<snu::KElectron> electronAnalysisColl_dummy =  GetTruePrompt(_electronAnalysisColl_dummy, false, false);
  
  /// Electrons used for veto (LOOSEST IN ANALYSIS)
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);

  std::vector<snu::KElectron> _electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronLooseColl, jetColl, false);
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
   
  if(k_running_nonprompt){
    weight= 1.;
  }
  float mcclosure_weight = weight;

  
  /// MC CLOSURE
  if(!isData){
    if(k_running_nonprompt){

      std::vector<snu::KElectron> electronAnalysisColl_mcclosure =  GetTruePrompt(_electronAnalysisColl, false, true); // removes CF and fake in mc
      
      if(electronAnalysisColl_mcclosure.size() == 2){

	if(SameCharge(electronAnalysisColl_mcclosure)){
	  
	  if(electronAnalysisColl_mcclosure.at(1).Pt() > 15.){
	    cout << "SS: size of mc el collection for closure = " << electronAnalysisColl_mcclosure.size() << endl;
	    cout << "njets = " << jetColl_lepveto_mva.size() << endl;
	    
	    bool lept1_fromW=false;
	    if( electronAnalysisColl_mcclosure.at(0).GetType() == 0 || electronAnalysisColl_mcclosure.at(0).GetType() == 7)lept1_fromW=true;
	    bool lept2_fromW=false;
	    if(electronAnalysisColl_mcclosure.at(1).GetType() ==0 || electronAnalysisColl_mcclosure.at(1).GetType() == 7)lept2_fromW=true;
	    cout << "lep1 from W = " << lept1_fromW << "lep2 from W = " <<lept2_fromW << endl;
	    cout << electronAnalysisColl_mcclosure.at(0).GetType()  << " " <<  electronAnalysisColl_mcclosure.at(1).GetType() << endl;
	    if(!(lept1_fromW&&lept2_fromW)){
	      float fake_weight20 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09  ,0.05,true,false,  true ,"mc_20");
	      float fake_weight40 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.05,true,false,   true ,"mc_40");
	      float fake_weight60 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.05,true,false,true ,"mc_60");
	      
	      if(IsTight(electronAnalysisColl_mcclosure.at(0),  jetColl, eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl_mcclosure.at(1),  jetColl, eventbase->GetEvent().JetRho()) ){
		FillHist(("MCSSclosure_fake_measured"), electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 100., 10);
		if(jetColl_lepveto_mva.size() > 2)  FillHist(("MCSSclosure_fake_2jet_measured"), electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 100., 10);
	      }
	      else cout << "NOT TT " << endl;	      
	      if(IsTight(electronAnalysisColl_mcclosure.at(0),  jetColl, eventbase->GetEvent().JetRho()) || IsTight(electronAnalysisColl_mcclosure.at(1),  jetColl, eventbase->GetEvent().JetRho()) ){
		
		FillHist(("MCSSclosure_fake_predicted20"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight20, 0. , 100., 10);
		FillHist(("MCSSclosure_fake_predicted40"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight40, 0. , 100., 10);
		FillHist(("MCSSclosure_fake_predicted60"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight60, 0. , 100., 10);
		FillHist(("MCSSclosure_fake_predicted_now"),  electronAnalysisColl_mcclosure.at(1).Pt(), weight, 0. , 100., 10);
		if(jetColl_lepveto_mva.size() > 2) {
		  FillHist(("MCSSclosure_fake_2jet_predicted20"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight20, 0. , 100., 10);
		  FillHist(("MCSSclosure_fake_2jet_predicted40"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight40, 0. , 100., 10);
		  FillHist(("MCSSclosure_fake_2jet_predicted60"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight60, 0. , 100., 10);
		  FillHist(("MCSSclosure_fake_2jet_predicted_now"),  electronAnalysisColl_mcclosure.at(1).Pt(), weight, 0. , 100., 10);
		}
	      }
	    }
	  }
	}
	
	if(electronAnalysisColl_mcclosure.at(1).Pt() > 15.){
	  
	  bool lept1_fromW=false;
	  if( electronAnalysisColl_mcclosure.at(0).GetType() == 0 || electronAnalysisColl_mcclosure.at(0).GetType() == 7)lept1_fromW=true;
	  bool lept2_fromW=false;
	  if(electronAnalysisColl_mcclosure.at(1).GetType() ==0 || electronAnalysisColl_mcclosure.at(1).GetType() == 7)lept2_fromW=true;
	  
	  cout << "lep1 from W = " << lept1_fromW << "lep2 from W = " <<lept2_fromW << endl;
	  cout << electronAnalysisColl_mcclosure.at(0).GetType()  << " " <<  electronAnalysisColl_mcclosure.at(1).GetType() << endl;
	  
	  if(!(lept1_fromW&&lept2_fromW)){
	    float fake_weight20 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true,false,  true ,"mc_20");
	    float fake_weight40 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true,false,   true ,"mc_40");
	    float fake_weight60 = weight* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.05,true,false,true ,"mc_60");
	    
	    if(IsTight(electronAnalysisColl_mcclosure.at(0),  jetColl, eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl_mcclosure.at(1),  jetColl, eventbase->GetEvent().JetRho()) ){
	      FillHist(("MCclosure_fake_measured"), electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 100., 10);
	      if(jetColl_lepveto_mva.size() > 2)  FillHist(("MCclosure_fake_2jet_measured"), electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 100., 10);
	    }
	    else cout << "NOT TT " << endl;
	    if(IsTight(electronAnalysisColl_mcclosure.at(0),  jetColl, eventbase->GetEvent().JetRho()) || IsTight(electronAnalysisColl_mcclosure.at(1),  jetColl, eventbase->GetEvent().JetRho()) ){
	      
	      FillHist(("MCclosure_fake_predicted20"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight20, 0. , 100., 10);
	      FillHist(("MCclosure_fake_predicted40"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight40, 0. , 100., 10);
	      FillHist(("MCclosure_fake_predicted60"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight60, 0. , 100., 10);
	      FillHist(("MCclosure_fake_predicted_now"),  electronAnalysisColl_mcclosure.at(1).Pt(), weight, 0. , 100., 10);
	      if(jetColl_lepveto_mva.size() > 2)  {
		FillHist(("MCclosure_fake_2jet_predicted20"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight20, 0. , 100., 10);
		FillHist(("MCclosure_fake_2jet_predicted40"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight40, 0. , 100., 10);
		FillHist(("MCclosure_fake_2jet_predicted60"),  electronAnalysisColl_mcclosure.at(1).Pt(), fake_weight60, 0. , 100., 10);
		FillHist(("MCclosure_fake_2jet_predicted_now"),  electronAnalysisColl_mcclosure.at(1).Pt(), weight, 0. , 100., 10);
		
	      }
	    }
	    else{
	      FillHist(("MCclosure_fake_looseloose"),  electronAnalysisColl_mcclosure.at(1).Pt(), weight, 0. , 100., 10);
	    }
	  }
	}
      }
    }
  }
  


  
  // Loos at d0 and isolation of electrons that are really photons mis reconstructed
  std::vector<snu::KElectron>  fakeElectronSample;
  if(SameCharge(electronNoCutColl)){
    if(!(electronNoCutColl.at(0).GetType()== 0 || electronNoCutColl.at(0).GetType()== 7 )) {
      if(isData) {
	if(electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(0));
      }
      else fakeElectronSample.push_back(electronNoCutColl.at(0));
      
      if(electronNoCutColl.at(0).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()), weight  , 0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(0).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else {
      FillHist("W_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt())  ,weight  , 0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(0).dxy())  ,weight  ,0., 0.1, 100);
    }

    if(!(electronNoCutColl.at(1).GetType()== 0 || electronNoCutColl.at(1).GetType()==7 )) {
      if(isData) {
        if(electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(1));
      } 
      else fakeElectronSample.push_back(electronNoCutColl.at(1));
      if(electronNoCutColl.at(1).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else{
      FillHist("W_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
    }
  }


  ///// count number of bjets in the event (using cvs medium WP)
  int nbjet_l=0;
  int nbjet_m=0;
  int nbjet_t=0;
  
  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.898) nbjet_t++;
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet_m++;
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.244) nbjet_l++;
  }
  /// nbjet is variable used in analysis
  int nbjet = nbjet_m;;
  
  /// Check the jets close to the electrons we will use
  CheckJetsCloseToLeptons(electronVetoColl, jetColl, "vetoel");
  CheckJetsCloseToLeptons(electronLooseColl, jetColl, "looseel");
  CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel");


  /// makes full set of plots for el/mu/jets/met with no cuts applied on objects 
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl, weight);
  
  if(jetColl_lepveto_mva.size() >1) FillCLHist(sighist, "NoCutPtEta",  eventbase->GetEvent(), muonNoCutColl, electronPtEtaNoCutColl,jetColl_lepveto_mva, weight);
  FillCLHist(sighist, "Fake", eventbase->GetEvent(), muonNoCutColl,fakeElectronSample,jetColl, weight);
 

  //// CHECK EFFICIENCY OF CUTS
  std::vector<snu::KElectron>  electronPtEtaCutColl;
  
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;

    electronPtEtaCutColl.push_back(electronNoCutColl[iel]);
  }

  /// Tight ID eff
  std::vector<snu::KElectron>  electronTight_NoIsoCutColl;
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
                if( egamma_ep          <= 0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
                          if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                            electronTight_NoIsoCutColl.push_back(electronNoCutColl.at(iel));
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
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
                if( egamma_ep          <=0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
                          if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                            electronTight_NoIsoCutColl.push_back(electronNoCutColl.at(iel));
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

  // oital efficiency + tight brekdownd
  std::vector<snu::KElectron>  electron_analysisCutColl;
  std::vector<snu::KElectron>  electron_analysisNPFCutColl;
  std::vector<snu::KElectron>   electronTight_DeltaEta;
  std::vector<snu::KElectron>   electronTight_DeltaPhi;
  std::vector<snu::KElectron>   electronTight_SigmaIEta;
  std::vector<snu::KElectron>   electronTight_DZ;
  std::vector<snu::KElectron>   electronTight_HoverE;
  std::vector<snu::KElectron>   electronTight_convfit;
  std::vector<snu::KElectron>   electronTight_ep;
  std::vector<snu::KElectron>   electronTight_missinghit;
  std::vector<snu::KElectron>   electronTight_convphoton;
  std::vector<snu::KElectron>   electronTight_DXY;
  std::vector<snu::KElectron>   electronTight_chargeconst;
  std::vector<snu::KElectron>   electronTight_tightref;
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;
    
    
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_tightref.push_back(electronNoCutColl.at(iel));
	if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
	  electronTight_DeltaEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
	  electronTight_DeltaPhi.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
	  electronTight_SigmaIEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	  electronTight_DZ.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
	  electronTight_HoverE.push_back(electronNoCutColl.at(iel));
	}
	if( egamma_ep          <= 0.05){
	  electronTight_ep.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
	  electronTight_convfit.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].MissingHits()    <=  0){
	  electronTight_missinghit.push_back(electronNoCutColl.at(iel));
	}
	if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
	  electronTight_convphoton.push_back(electronNoCutColl.at(iel));
	}
	
	if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
          electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
        }
      }
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_DXY.push_back(electronNoCutColl.at(iel));
      }	
      
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
                if( egamma_ep          <= 0.05){
		  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl[iel].MissingHits()    <=  0){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			    
			    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
			    int ifid=0;
			    if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
			    else ifid = 6;

			    float LeptonRelIsoDR03(0.);
			    float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);

			    if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
			    else LeptonRelIsoDR03 = -999.;

			    float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
			    float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
			    float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
			    bool passNPFiso = true;
			    if(trkiso > 0.1) passNPFiso = false;
			    if(ecaliso > 0.25) passNPFiso = false;
			    if(hcaliso > 0.2)  passNPFiso = false;

			    float isocut= 0.09;
			    if(fabs(electronNoCutColl.at(iel).Eta() > 1.5) )isocut = 0.05;
			    else   if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
			    if(LeptonRelIsoDR03 < isocut){
			      electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
			      if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
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
      if(iel ==0){
	if(electronNoCutColl[iel].Pt() < 20.) continue;
      }
      else{
	if(electronNoCutColl[iel].Pt() < 15.) continue;
      }
      if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;

      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_tightref.push_back(electronNoCutColl.at(iel));

	if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	  electronTight_DeltaEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
	  electronTight_DeltaPhi.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
	  electronTight_SigmaIEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	  electronTight_DZ.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
	  electronTight_HoverE.push_back(electronNoCutColl.at(iel));
	}
	if( egamma_ep          <=0.05){
	  electronTight_ep.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
	  electronTight_convfit.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].MissingHits()    <=  0){
	  electronTight_missinghit.push_back(electronNoCutColl.at(iel));
	}
	if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
	  electronTight_convphoton.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
	  electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
	}
      }
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_DXY.push_back(electronNoCutColl.at(iel));
      }

      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
                if( egamma_ep          <=0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){

                            Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
                            int ifid=0;
                            if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
                            else ifid = 6;

                            float LeptonRelIsoDR03(0.);
                            float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);

                            if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
                            else LeptonRelIsoDR03 = -999.;

                            float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
                            float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
                            float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
                            bool passNPFiso = true;
                            if(trkiso > 0.1) passNPFiso = false;
                            if(ecaliso > 0.25) passNPFiso = false;
                            if(hcaliso > 0.2)  passNPFiso = false;

			    float isocut= 0.09;
                            if(fabs(electronNoCutColl.at(iel).Eta() > 1.5) )isocut = 0.05;
                            else   if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
                            if(LeptonRelIsoDR03 < isocut){
                              electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
                              if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
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
  std::vector<snu::KElectron>  electron_IsoCutColl;
  std::vector<snu::KElectron>  electron_NPFIsoCutColl;
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid=0;
    if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
    else ifid = 6;

    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);
    
    if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
    else LeptonRelIsoDR03 = -999.;

    float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
    float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
    float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
    bool passNPFiso = true;
    if(trkiso > 0.1) passNPFiso = false;
    if(ecaliso > 0.2) passNPFiso = false;
    if(hcaliso > 0.1)  passNPFiso = false;
    
    float isocut= 0.09;
    if(fabs(electronNoCutColl.at(iel).Eta() > 1.5) )isocut = 0.05;
    else  if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
    if(LeptonRelIsoDR03 < isocut){
      electron_IsoCutColl.push_back(electronNoCutColl.at(iel));
      if(passNPFiso)       electron_NPFIsoCutColl.push_back(electronNoCutColl.at(iel));
      
    }
  }
  
  FillHist("electronRef", 1.,weight, 0.,2.,2);
  if(SameCharge(electronPtEtaCutColl))   FillHist("electronPtEtaCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electronTight_NoIsoCutColl))   FillHist("electron_NoIsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_IsoCutColl))   FillHist("electron_IsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_NPFIsoCutColl))   FillHist("electron_NPFIsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl))   FillHist("electron_analysisCutColll", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisNPFCutColl))   FillHist("electron_analysisNPFCutColll", 1.,weight, 0.,2.,2);
  if(jetColl_lepveto_mva.size()  > 1) FillHist("JetSelection", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl) && jetColl_lepveto_mva.size()  > 1)  FillHist("PreSelection", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisNPFCutColl) && jetColl_lepveto_mva.size()  > 1)  FillHist("PreSelectionNPF", 1.,weight, 0.,2.,2);
  
  if(SameCharge(electronTight_tightref)){
    FillHist("electronTight_tightref", 1., weight, 0.,2.,2);
    if(SameCharge(electronTight_DeltaEta))   FillHist("electron_DeltaEta", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DeltaPhi))   FillHist("electron_DeltaPhi", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_SigmaIEta))   FillHist("electron_SigmaIEta", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DZ))   FillHist("electron_DZ", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_HoverE))   FillHist("electron_HoverE", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_convfit))   FillHist("electron_convfit", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_ep))   FillHist("electron_ep", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_missinghit))   FillHist("electron_missinghit", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_convphoton))   FillHist("electron_convphoton", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DXY))   FillHist("electron_DXY", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_chargeconst))   FillHist("electron_chargeconst", 1.,weight, 0.,2.,2);
  }


  /// Apply electron SFs for tight id
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }
  m_logger << DEBUG << "Analysis part: "<< LQLogger::endmsg;


  //// WZ/ZZ CR : validate our main prompt bkgs      
  if(PassTrigger(triggerslist, prescale)){
    ///_electronAnalysisColl  has no truth matching applied (since we have no fake bkg estimate for trilepton events)
    if(_electronAnalysisColl.size() ==  3 && (muonVetoColl.size()== 0)) {
      
      float charge1 = _electronAnalysisColl.at(0).Charge();
      float charge2 = _electronAnalysisColl.at(1).Charge();
      float charge3 = _electronAnalysisColl.at(2).Charge();
      
      /// Find os pair
      snu::KParticle osee;
      if(charge1 != charge2) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(1);
      if(charge1 != charge3) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(2);
      if(charge2 != charge3) osee= _electronAnalysisColl.at(1) + _electronAnalysisColl.at(2);
      
      if(jetColl_lepveto_mva.size() > 1){
	if(eventbase->GetEvent().PFMET() > 30){
	  if(fabs(osee.M() - 90.) < 10) FillCLHist(sighist, "TriElCR", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
      
      if(fabs(osee.M() - 90.) < 10){
	if(jetColl_lepveto_mva.size() > 0){
	  FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
      
      if(jetColl_lepveto_mva.size() > 1){
        if(eventbase->GetEvent().PFMET() > 30){
	  FillCLHist(sighist, "TriEl_jetmva_inclusive", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
    }
    if(_electronAnalysisColl.size() ==  4 && (muonVetoColl.size()== 0))FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
  }

  
  /// single lepton CR
  if(electronAnalysisColl.size() ==1){
    std::vector<TString> triggerslist17jet;
    triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

    std::vector<TString> triggerslist8jet;
    triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    
    bool pass_eljettrig= false;
    float prescale_trigger = 0.;
    if(electronAnalysisColl.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger = (16.95) / 19789 ; //// 20 + GeV bins
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger = (3.546650) / 19789 ;
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    
    if(k_isdata) prescale_trigger=1.;

    bool Zveto=false;
    if(electronVetoColl.size() == 2) {
      if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
	snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
        if(Z.M() > 76. && Z.M() < 106.) Zveto=true;
      }
    }
    if(!Zveto && pass_eljettrig){
      Double_t MT=0;
      Double_t METdphi=0;
      for(unsigned int w = 0; w < electronAnalysisColl.size() ;  w++){
	METdphi = TVector2::Phi_mpi_pi(electronAnalysisColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
	MT = sqrt(2.* electronAnalysisColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
      }
      
      float weight_pu=weight;
      if(k_running_nonprompt){
	
	bool closebjet=false;
	bool closenoejet=false;
	bool closephjet=false;
	for(unsigned int ijet =0 ; ijet <jetColl.size() ; ijet++){
	  for(unsigned int iel=0 ; iel < electronAnalysisColl.size() ; iel++){

	    float dphi =fabs(TVector2::Phi_mpi_pi(electronAnalysisColl.at(iel).Phi()- jetColl.at(ijet).Phi()));
	    if( dphi < 0.4){
	      if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	    }
	    if( electronAnalysisColl[iel].DeltaR(jetColl.at(ijet)) < 0.4){
	      if(jetColl.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	      if(jetColl.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	    }
	  }
	}
	
	TString cut="20";

	float ee_weight =  Get_DataDrivenWeight_E(electronAnalysisColl, jetColl,jetColl_lepveto_mva, jetColl_lepveto_mva.size(),nbjet, eventbase->GetEvent().JetRho(),  0.01,0.09,0.05,true,true,true,cut, false);
	float ee_weight_pucorr =  Get_DataDrivenWeight_E(electronAnalysisColl, jetColl, jetColl_lepveto_mva, jetColl_lepveto_mva.size(),nbjet, eventbase->GetEvent().JetRho(),  0.01,0.09,0.05,true,true,true,cut, true);
	weight=ee_weight;
	weight_pu = ee_weight_pucorr;
	
      }

      if(eventbase->GetEvent().PFMET() < 20.){
	if(jetColl_lepveto_mva.size() > 0){
	  FillCLHist(sighist, "SingleEl_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(nbjet > 0)  FillCLHist(sighist, "SingleEl_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(IsTight(electronAnalysisColl.at(0),  jetColl, eventbase->GetEvent().JetRho())) {
	    FillCLHist(sighist, "SingleElTight_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	    if(nbjet > 0)  FillCLHist(sighist, "SingleElTight_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	  else{
	    FillCLHist(sighist, "SingleElLoose_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
            if(nbjet > 0)  FillCLHist(sighist, "SingleElLoose_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	}/// NON INCLUSIVE JET
      }/// LOW MET SCR
      
      if(jetColl_lepveto_mva.size() > 0){
	if(eventbase->GetEvent().PFMET() > 30.){
	  float dphiel = TVector2::Phi_mpi_pi(electronAnalysisColl.at(0).Phi()- eventbase->GetEvent().PFMETphi());
	  float MTel = sqrt(2.* electronAnalysisColl.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphiel)));
	  if((MTel < 100.) && (MTel  > 60.)){
	    FillCLHist(sighist, "SingleEl_promptCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	    if(nbjet > 0)  FillCLHist(sighist, "SingleEl_promptbjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  }
	}
      }
    }
  }

  // Require now dilepton trigger passed
  //if(!PassTrigger(triggerslist, prescale)) return;
  if(!PassTrigger(triggerslist, prescale))  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale

  FillEventCutFlow("TriggerCut", 1.);
  
  if(jetColl_lepveto_mva.size() > 2){
    if(SameCharge(electron_analysisCutColl)) FillHist("TightSelection", 0 , weight, 0.,3.,3);
    if(SameCharge(electronAnalysisColl))  FillHist("TightSelection", 1 , weight, 0.,3.,3);
    if(SameCharge(electronAnalysisColl_dummy))  FillHist("TightSelection", 2 , weight, 0.,3.,3);
    

    if(LowMassCheckSignalRegion(electron_analysisCutColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionLM", 0 , weight, 0.,3.,3);
    if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionLM",1,  weight, 0.,3.,3);
    if(LowMassCheckSignalRegion(electronAnalysisColl_dummy, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionLM",2,  weight, 0.,3.,3);
    
    if(MidMassCheckSignalRegion(electron_analysisCutColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionMM", 0 , weight, 0.,3.,3);
    if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionMM",1,  weight, 0.,3.,3);
    if(MidMassCheckSignalRegion(electronAnalysisColl_dummy, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionMM",2,  weight, 0.,3.,3);
    
    if(HighMassCheckSignalRegion(electron_analysisCutColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionHM", 0 , weight, 0.,3.,3);
    if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionHM",1,  weight, 0.,3.,3);
    if(HighMassCheckSignalRegion(electronAnalysisColl_dummy, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionHM",2,  weight, 0.,3.,3);
    
  }

  /// Require 2 analysis electrons (20/15) GeV
  //if(electronAnalysisColl.size() != 2 ) return;
  //if(electronAnalysisColl.at(0).Pt() < 20.) return;
  //if(electronAnalysisColl.at(1).Pt() < 15.) return;
  
  if(electronAnalysisColl.size() != 2 ) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  if(electronAnalysisColl.at(0).Pt() < 20.)throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  if(electronAnalysisColl.at(1).Pt() < 15.)throw LQError( "Fails basic cuts",  LQError::SkipEvent );


  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  //if(ee.M()  < 10.) return;
  if(ee.M()  < 10.) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  FillEventCutFlow("DiEl",1.);
  
  // Remove overlapping particles only need electron overlap in ee channel                                                                                     
  for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
    for(std::vector<snu::KElectron>::iterator it2 = it+1; it2 != electronLooseColl.end(); it2++){
      //if(it->DeltaR(*it2) < 0.5) return;
      if(it->DeltaR(*it2) < 0.5) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
    }
  }
  FillEventCutFlow("eedR", 1.);

 
  // TOP Control region os/SS    
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(electronAnalysisColl.size() ==2){
	if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  
  /// For CF use OS data and weight using CF rates from sunny
  if(k_running_chargeflip) {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));

      weight *=  ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    //else return;
    else throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }// cf requirement
  else {
    if ((electronVetoColl.size() + muonVetoColl.size()) == 2){
      if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    
    //if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }
  


  
  ///// NOW OS event is weighted for CF sample

  FillEventCutFlow("SSDiEl",1.);
  FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
  FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);

  /// Remove events with 3 veto leptons
  //if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;  
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) throw LQError( "Fails basic cuts",  LQError::SkipEvent );  
  //if(muonVetoColl.size() !=0) return;
  if(muonVetoColl.size() !=0) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  if(muonTightColl.size() != 0) {
    cout << "Number of muons (tight = " << muonTightColl.size() << endl;
    cout << "Number of muons veto = " << muonVetoColl.size() << endl;
    cout << "Number of el veto = " << electronVetoColl.size() << endl;
    cout << "Number of el tight = " << electronAnalysisColl.size() << endl;
  }
  FillEventCutFlow("SS_lepveto",1.);
  
  //if(electronAnalysisColl.at(0).VertexIndex() != electronAnalysisColl.at(1).VertexIndex()) return;
  if(electronAnalysisColl.at(0).VertexIndex() != electronAnalysisColl.at(1).VertexIndex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  FillEventCutFlow("SS_samevertex",1.);
  
  FillCLHist(sighist, "SSloose", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  float ee_weight_20_nor= weight;
  float ee_weight_40_nor= weight;
  
  float ee_weight_30_0905_nor= weight;


  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt){
    
    if(SameCharge(electronAnalysisColl)){
      if(nbjet==0){
	if(jetColl_lepveto_mva.size() > 1) {
	  for(unsigned int ilooseel=0; ilooseel < electronAnalysisColl.size(); ilooseel++){
	    bool awayjet=false;
	    bool closebjet =false;
	    if(!IsTight(electronAnalysisColl.at(ilooseel), jetColl, eventbase->GetEvent().JetRho())){
	      for(unsigned int ijet=0; ijet < jetColl.size(); ijet++){
		if( electronAnalysisColl.at(ilooseel).DeltaR(jetColl.at(ijet)) < 0.4){
		  /// Jet usually vetoe
		  FillHist(("closejet_looseobject_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ptdiff"),(jetColl.at(ijet).Pt() - electronAnalysisColl.at(ilooseel).Pt())/ jetColl.at(ijet).Pt() , weight, -1.,1.,50);
		  
		}
		float dphielloose = TVector2::Phi_mpi_pi(electronAnalysisColl.at(0).Phi()- jetColl.at(ijet).Phi());
		if(fabs(dphielloose) > 2.5) {
		  if(!awayjet)  FillHist(("awayjet_looseobject_pt"),jetColl.at(ijet).Pt(),  weight, 0.,100.,20);
		  awayjet=true;
		}
		if( electronAnalysisColl.at(ilooseel).DeltaR(jetColl.at(ijet)) < 0.4){
		  if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
		}
	      }//jetcoll
	      if(closebjet)  FillHist(("closebjet_looseobject"), 1 ,  weight, 0.,2.,2);
	      else  FillHist(("closebjet_looseobject"), 0 ,  weight, 0.,2.,2);
	      if(!awayjet) FillHist(("awayjet_looseobject_pt"), 0. ,  weight, 0.,100.,20);
	    }//is loose
	  }// ell loose
	}
      }
    }
    
    
    ee_weight_20_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01, 0.09, 0.05, "20");
    

    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(),  0.01, 0.09, 0.05, "40");

    ee_weight_40_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(),  0.01, 0.09, 0.05, "60");

    ee_weight_30_0905_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01, 0.09, 0.05,"30_0905");
    
    weight*= ee_weight;
    
    /// END of NP bkg loop
    if(jetColl_lepveto_mva.size() == 0){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    if(jetColl_lepveto_mva.size() == 1){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    if(jetColl_lepveto_mva.size() > 1){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    
  }
    
  FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  else FillCLHist(sighist, "SSee_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

  if(jetColl_lepveto_mva.size() == 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_0jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  if(jetColl_lepveto_mva.size() == 1){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_1jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_1jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(jetColl_lepveto_mva.size() > 1){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_gt0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(ee.M() > 100.){
    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet_20_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_20_nor);
    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet_40_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_40_nor);
  }
  
  //if(jetColl_lepveto_mva.size() < 2) return;
  if(jetColl_lepveto_mva.size() < 2) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FillEventCutFlow("Preselection",1.);


  /// btag SF
  int jetFlavour=0;
  bool b_found = false;
  bool b_foundEffDown(false), b_foundEffUp(false) ,b_foundMissDown(false), b_foundMissUp(false);
  std::vector<snu::KTruth> genBColl;
  for(int ig=0; ig < eventbase->GetTruth().size(); ig++){
    if(eventbase->GetTruth().at(ig).Pt() < 10.) continue;
    if(fabs(eventbase->GetTruth().at(ig).Eta()) > 3.) continue;
    genBColl.push_back(eventbase->GetTruth().at(ig));
  }
  
  if(!isData){

    for(unsigned int ij=0; ij < jetColl_lepveto_mva.size(); ij++){
      for(int ig=0; ig < genBColl.size(); ig++){
	if(jetColl_lepveto_mva.at(ij).DeltaR(genBColl.at(ig)) < 0.4 ){
	  jetFlavour = fabs(genBColl[ig].PdgId());
	  break;
	}
	else{
	  jetFlavour = 21;
	}
      }
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour, jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) )
	b_found = true;
      
      if (jetFlavour==4 || jetFlavour==5) {
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), -1) )
	  b_foundEffDown = true;
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), +1) )
	  b_foundEffUp = true;
      }
      else
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) ) {
	  b_foundEffDown = true;
	  b_foundEffUp = true;
	}
      
      if (jetFlavour==1 || jetFlavour==2 || jetFlavour==3 || jetFlavour==21) {
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), -1) )
	  b_foundMissDown = true;
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), +1) )
	  b_foundMissUp = true;
      }
      else
	if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) ) {
	  b_foundMissDown = true;
	  b_foundMissUp = true;
	}
    }
  }


  if(nbjet_m==0)   FillEventCutFlow("Preselection_bjetm",1.);
  if(nbjet==0)   FillEventCutFlow("Preselection_bjett",1.);

  FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

  bool store_opt_var=true;
  if(store_opt_var){
    k_nbjet_l = nbjet_l;
    k_nbjet_m = nbjet_m;
    k_nbjet_t = nbjet_t;
    k_el1pt= electronAnalysisColl.at(0).Pt();
    k_el2pt= electronAnalysisColl.at(1).Pt();
    k_j1pt = jetColl_lepveto_mva.at(0).Pt();
    k_eemass = ee.M();
    float wmassjj= 100000.;
    int indexj1=0;
    int indexj2=0;
    for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
      for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2) ;
	if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	  wmassjj = fabs(jjtmp.M() - 80.4);
	  indexj1=ij;
	  indexj2=ij2;
	}
      }
    }
    snu::KParticle jj = jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2);
    k_jjmass = jj.M();
    snu::KParticle eejj = electronAnalysisColl.at(0) + electronAnalysisColl.at(1)+ jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
    snu::KParticle e1jj = electronAnalysisColl.at(0) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
    snu::KParticle e2jj = electronAnalysisColl.at(1) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
    k_eejjmass = eejj.M();
    k_e1jjmass = e1jj.M();
    k_e2jjmass = e2jj.M();
    k_njet=jetColl_lepveto_mva.size();
    
    
    float st=0.;
    for(unsigned int ij=0; ij < jetColl_lepveto_mva.size(); ij++){
      st+= jetColl_lepveto_mva.at(ij).Pt();
    }
    for(unsigned int ie=0; ie < electronAnalysisColl.size(); ie++){
      st+= electronAnalysisColl.at(ie).Pt();
    }
    k_ht = st;
    st+= eventbase->GetEvent().PFMET();
    k_st = st;
    k_met = eventbase->GetEvent().PFMET();
    k_weight = weight;
  }
  
  FillCLHist(sighist, "SSee_DiJet_20_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_20_nor);
  FillCLHist(sighist, "SSee_DiJet_40_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_40_nor);

  float event_met = eventbase->GetEvent().PFMET();
  float event_met_jesup = eventbase->GetEvent().PFMET_Jet_EnUp() ;
  float event_met_jesdown = eventbase->GetEvent().PFMET_Jet_EnDown() ;
  
  float event_met_jresup = eventbase->GetEvent().PFMET_Jet_ResUp();
  float event_met_jresdown = eventbase->GetEvent().PFMET_Jet_ResDown();
    
  float event_met_unclustup = eventbase->GetEvent().PFMET_Unclust_Up();
  float event_met_unclustdown = eventbase->GetEvent().PFMET_Unclust_Down();
  std::vector<snu::KJet> jetColl_jetE_up;
  std::vector<snu::KJet> jetColl_jetE_down;
  std::vector<snu::KJet> jetColl_jetRes_up;
  std::vector<snu::KJet> jetColl_jetRes_down;
  
  for(unsigned int ij=0; ij < jetColl_lepveto_mva.size(); ij++){
    snu::KJet jetEup = jetColl_lepveto_mva.at(ij);
    snu::KJet jetEdown = jetColl_lepveto_mva.at(ij);
    snu::KJet jetResup = jetColl_lepveto_mva.at(ij);
    snu::KJet jetResdown = jetColl_lepveto_mva.at(ij);
    if(jetEup.ScaledUpPt() > 20. )jetEup.SetPtEtaPhiE(jetEup.ScaledUpPt(), jetEup.Eta(), jetEup.Phi(), jetEup.ScaledUpEnergy());
    if(jetEdown.ScaledDownPt() > 20. ) jetEdown.SetPtEtaPhiE(jetEdown.ScaledDownPt(), jetEdown.Eta(), jetEdown.Phi(), jetEdown.ScaledDownEnergy());
    if(jetResup.SmearedUpPt() > 20. ) jetResup.SetPtEtaPhiE(jetResup.SmearedUpPt(), jetResup.Eta(), jetResup.Phi(), jetResup.SmearedUpEnergy());
    if(jetResdown.SmearedDownPt() > 20. )  jetResdown.SetPtEtaPhiE(jetResdown.SmearedDownPt(), jetResdown.Eta(), jetResdown.Phi(), jetResdown.SmearedDownEnergy());
    
    if(jetEup.ScaledUpPt() > 20. )jetColl_jetE_up.push_back(jetEup);
    if(jetEdown.ScaledDownPt() > 20. ) jetColl_jetE_down.push_back(jetEdown);
    if(jetResup.SmearedUpPt() > 20. )jetColl_jetRes_up.push_back(jetResup);
    if(jetResdown.SmearedDownPt() > 20. ) jetColl_jetRes_down.push_back(jetResdown);
  }
 
  std::vector<float> masscuts40;
  masscuts40.push_back(20.);  masscuts40.push_back(15.);   /// pt1 / pt2
  masscuts40.push_back(10.);  masscuts40.push_back(10000.);   /// m(ee)
  masscuts40.push_back(0.);   masscuts40.push_back(120.);  /// m(jj)
  masscuts40.push_back(80.);  masscuts40.push_back(155.);  /// m(eejj)
  masscuts40.push_back(30.);                               /// MET  
  masscuts40.push_back(20.);                               /// jet 1 pt
  masscuts40.push_back(40.);  masscuts40.push_back(120.);  /// m(e2jj)

  std::vector<float> masscuts50;
  masscuts50.push_back(20.);  masscuts50.push_back(15.);   
  masscuts50.push_back(10.);  masscuts50.push_back(10000.);
  masscuts50.push_back(0.);   masscuts50.push_back(120.);
  masscuts50.push_back(80.);  masscuts50.push_back(155.);
  masscuts50.push_back(30.); 
  masscuts50.push_back(20.);
  masscuts50.push_back(40.);  masscuts50.push_back(120.); 

  std::vector<float> masscuts60;
  masscuts60.push_back(20.);  masscuts60.push_back(15.);
  masscuts60.push_back(10.);  masscuts60.push_back(100000.);
  masscuts60.push_back(0.);   masscuts60.push_back(120.);  
  masscuts60.push_back(80.);  masscuts60.push_back(155.);
  masscuts60.push_back(30.);
  masscuts60.push_back(20.);
  masscuts60.push_back(40.);  masscuts60.push_back(120.);  

  std::vector<float> masscuts70;
  masscuts70.push_back(20.);  masscuts70.push_back(15.);
  masscuts70.push_back(10.);  masscuts70.push_back(10000.);
  masscuts70.push_back(0.);   masscuts70.push_back(120.);
  masscuts70.push_back(80.);  masscuts70.push_back(155.);
  masscuts70.push_back(30.);
  masscuts70.push_back(20.);
  masscuts70.push_back(40.);  masscuts70.push_back(120.);

  std::vector<float> masscuts80;
  masscuts80.push_back(20.);  masscuts80.push_back(15.);
  masscuts80.push_back(10.);  masscuts80.push_back(10000.);
  masscuts80.push_back(0.);   masscuts80.push_back(120.);
  masscuts80.push_back(80.);  masscuts80.push_back(155.);
  masscuts80.push_back(30.);
  masscuts80.push_back(20.);
  masscuts80.push_back(60.);  masscuts80.push_back(120.);
  
  
  vector<int> btagsyst;
  if(!b_foundMissDown) btagsyst.push_back(7);
  if(!b_foundMissUp) btagsyst.push_back(8);
  if(!b_foundEffDown) btagsyst.push_back(9);
  if(!b_foundEffUp) btagsyst.push_back(10);


  std::vector<float> masscuts90;
  masscuts90.push_back(20.);  masscuts90.push_back(15.);
  masscuts90.push_back(20.);  masscuts90.push_back(10000.);
  masscuts90.push_back(50.);   masscuts90.push_back(110.);
  masscuts90.push_back(110.);  masscuts90.push_back(20000.);
  masscuts90.push_back(35.);
  masscuts90.push_back(30.);
  masscuts90.push_back(60.);  masscuts90.push_back(120.);

  std::vector<float> masscuts100;
  masscuts100.push_back(20.);  masscuts100.push_back(15.);
  masscuts100.push_back(20.);  masscuts100.push_back(10000.);
  masscuts100.push_back(50.);  masscuts100.push_back(110.);
  masscuts100.push_back(120.); masscuts100.push_back(10000.);
  masscuts100.push_back(35.);
  masscuts100.push_back(30.);
  masscuts100.push_back(80.);  masscuts100.push_back(120.);

  std::vector<float> masscuts125;
  masscuts125.push_back(30.);  masscuts125.push_back(20.);
  masscuts125.push_back(20.);  masscuts125.push_back(10000.);
  masscuts125.push_back(50.);  masscuts125.push_back(110.);
  masscuts125.push_back(140.); masscuts125.push_back(10000.);
  masscuts125.push_back(35.);
  masscuts125.push_back(30.);
  masscuts125.push_back(90.);  masscuts125.push_back(150.);

  std::vector<float> masscuts150;
  masscuts150.push_back(40.);  masscuts150.push_back(25.);
  masscuts150.push_back(20.);  masscuts150.push_back(10000.);
  masscuts150.push_back(50.);  masscuts150.push_back(110.);
  masscuts150.push_back(170.); masscuts150.push_back(10000.);
  masscuts150.push_back(35.);
  masscuts150.push_back(30.);
  masscuts150.push_back(120.);  masscuts150.push_back(185.);

  std::vector<float> masscuts175;
  masscuts175.push_back(45.);  masscuts175.push_back(30.);
  masscuts175.push_back(20.);  masscuts175.push_back(10000.);
  masscuts175.push_back(50.);  masscuts175.push_back(110.);
  masscuts175.push_back(230.); masscuts175.push_back(10000.);
  masscuts175.push_back(35.);
  masscuts175.push_back(30.);
  masscuts175.push_back(120.);  masscuts175.push_back(230.);

  std::vector<float> masscuts200;
  masscuts200.push_back(65.);  masscuts200.push_back(15.);
  masscuts200.push_back(20.);  masscuts200.push_back(10000.);
  masscuts200.push_back(50.);  masscuts200.push_back(110.);
  masscuts200.push_back(230.); masscuts200.push_back(10000.);
  masscuts200.push_back(35.);
  masscuts200.push_back(30.);
  masscuts200.push_back(120.);  masscuts200.push_back(260.);

  std::vector<float> masscuts225;
  masscuts225.push_back(70.);  masscuts225.push_back(45.);
  masscuts225.push_back(20.);  masscuts225.push_back(10000.);
  masscuts225.push_back(50.);  masscuts225.push_back(110.);
  masscuts225.push_back(290.); masscuts225.push_back(10000.);
  masscuts225.push_back(35.);
  masscuts225.push_back(40.);
  masscuts225.push_back(0.);  masscuts225.push_back(10000.);

  std::vector<float> masscuts250;
  masscuts250.push_back(70.);  masscuts250.push_back(45.);
  masscuts250.push_back(20.);  masscuts250.push_back(10000.);
  masscuts250.push_back(50.);  masscuts250.push_back(110.);
  masscuts250.push_back(300.); masscuts250.push_back(10000.);
  masscuts250.push_back(35.);
  masscuts250.push_back(40.);
  masscuts250.push_back(0.);  masscuts250.push_back(10000.);

  std::vector<float> masscuts275;
  masscuts275.push_back(70.);  masscuts275.push_back(45.);
  masscuts275.push_back(20.);  masscuts275.push_back(10000.);
  masscuts275.push_back(50.);  masscuts275.push_back(110.);
  masscuts275.push_back(320.); masscuts275.push_back(10000.);
  masscuts275.push_back(35.);
  masscuts275.push_back(40.);
  masscuts275.push_back(0.);  masscuts275.push_back(10000.);

  std::vector<float> masscuts300;
  masscuts300.push_back(120);  masscuts300.push_back(25.);
  masscuts300.push_back(20.);  masscuts300.push_back(10000.);
  masscuts300.push_back(50.);  masscuts300.push_back(110.);
  masscuts300.push_back(350.); masscuts300.push_back(10000.);
  masscuts300.push_back(35.);
  masscuts300.push_back(40.);
  masscuts300.push_back(0.);  masscuts300.push_back(10000.);

  std::vector<float> masscuts325;
  masscuts325.push_back(120);  masscuts325.push_back(25.);
  masscuts325.push_back(20.);  masscuts325.push_back(10000.);
  masscuts325.push_back(50.);  masscuts325.push_back(110.);
  masscuts325.push_back(350.); masscuts325.push_back(10000.);
  masscuts325.push_back(35.);
  masscuts325.push_back(40.);
  masscuts325.push_back(0.);  masscuts325.push_back(10000.);

  std::vector<float> masscuts350;
  masscuts350.push_back(120);  masscuts350.push_back(25.);
  masscuts350.push_back(20.);  masscuts350.push_back(10000.);
  masscuts350.push_back(50.);  masscuts350.push_back(110.);
  masscuts350.push_back(350.); masscuts350.push_back(10000.);
  masscuts350.push_back(35.);
  masscuts350.push_back(40.);
  masscuts350.push_back(0.);  masscuts350.push_back(10000.);

  std::vector<float> masscuts375;
  masscuts375.push_back(120);  masscuts375.push_back(25.);
  masscuts375.push_back(20.);  masscuts375.push_back(10000.);
  masscuts375.push_back(50.);  masscuts375.push_back(110.);
  masscuts375.push_back(350.); masscuts375.push_back(10000.);
  masscuts375.push_back(35.);
  masscuts375.push_back(40.);
  masscuts375.push_back(0.);  masscuts375.push_back(10000.);

  std::vector<float> masscuts400;
  masscuts400.push_back(125);  masscuts400.push_back(25.);
  masscuts400.push_back(20.);  masscuts400.push_back(10000.);
  masscuts400.push_back(50.);  masscuts400.push_back(110.);
  masscuts400.push_back(350.); masscuts400.push_back(10000.);
  masscuts400.push_back(35.);
  masscuts400.push_back(40.);
  masscuts400.push_back(0.);  masscuts400.push_back(10000.);

  std::vector<float> masscuts500;
  masscuts500.push_back(130);  masscuts500.push_back(25.);
  masscuts500.push_back(20.);  masscuts500.push_back(10000.);
  masscuts500.push_back(50.);  masscuts500.push_back(110.);
  masscuts500.push_back(350.); masscuts500.push_back(10000.);
  masscuts500.push_back(35.);
  masscuts500.push_back(40.);
  masscuts500.push_back(0.);  masscuts500.push_back(10000.);

  std::vector<float> masscuts600;
  masscuts600.push_back(125);  masscuts600.push_back(25.);
  masscuts600.push_back(20.);  masscuts600.push_back(10000.);
  masscuts600.push_back(50.);  masscuts600.push_back(110.);
  masscuts600.push_back(350.); masscuts600.push_back(10000.);
  masscuts600.push_back(35.);
  masscuts600.push_back(40.);
  masscuts600.push_back(0.);  masscuts600.push_back(10000.);
  std::vector<float> masscuts700;
  masscuts700.push_back(125);  masscuts700.push_back(25.);
  masscuts700.push_back(20.);  masscuts700.push_back(10000.);
  masscuts700.push_back(50.);  masscuts700.push_back(110.);
  masscuts700.push_back(350.); masscuts700.push_back(10000.);
  masscuts700.push_back(35.);
  masscuts700.push_back(40.);
  masscuts700.push_back(0.);  masscuts700.push_back(10000.);


  std::map<TString, std::vector<float> > sysymap;
  sysymap["40"] =  masscuts40;  sysymap["50"] =  masscuts50;
  sysymap["60"] =  masscuts60;  sysymap["70"] =  masscuts70;
  sysymap["80"] =  masscuts80;  sysymap["90"] =  masscuts90;
  sysymap["100"] =  masscuts100; sysymap["125"] =  masscuts125;
  sysymap["150"] =  masscuts150; sysymap["175"] =  masscuts175;
  sysymap["200"] =  masscuts200;  sysymap["225"] =  masscuts225;
  sysymap["250"] =  masscuts250;  sysymap["275"] =  masscuts275;
  sysymap["300"] =  masscuts300;  sysymap["325"] =  masscuts325;
  sysymap["350"] =  masscuts350;  sysymap["375"] =  masscuts375;
  sysymap["400"] =  masscuts400;  sysymap["500"] =  masscuts500;
  sysymap["600"] =  masscuts700;  sysymap["700"] =  masscuts700;

  for( std::map<TString, std::vector<float> >::iterator mapit = sysymap.begin(); mapit != sysymap.end(); mapit++){
    
    /// Low Mass                       pt2, pt1  ,eemin, max, jjmin,max, eejjmin,max, STmin,max, j1  , e2jjmin, ej22max, njet
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva,event_met, k_running_chargeflip , mapit->second)){

      FillCLHist(sighist, (mapit->first +"MassRegion").Data(), eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
      FillHist((mapit->first + "MassRegion_syst").Data(), 0, weight , 0., 15.,15);
      FillHist((mapit->first + "MassRegion_nentries").Data(), 0, weight , 0., 2.,2);
      FillHist((mapit->first + "MassRegion_nentries").Data(), 1, 1. , 0., 2.,2);
    }

    /// JET SYST
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_jetE_up ,event_met_jesup, k_running_chargeflip , mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 1, weight , 0., 15.,15);
    
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_jetE_down ,event_met_jesdown, k_running_chargeflip , mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 2, weight , 0., 15.,15);
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_jetRes_up ,event_met_jresup, k_running_chargeflip , mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 3 , weight , 0., 15.,15);
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_jetRes_down ,event_met_jresdown, k_running_chargeflip ,  mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 4  , weight , 0., 15.,15);
    
    /// MET
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva ,event_met_unclustup, k_running_chargeflip ,  mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 5,  weight , 0., 15.,15); 
    
    if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second))
      FillHist((mapit->first + "MassRegion_syst").Data(), 6,  weight , 0., 15.,15);

    ///Btag syst : 5 -8
    for(unsigned int ib = 0; ib < btagsyst.size(); ib++){
      if(OptMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva,event_met, k_running_chargeflip ,  mapit->second))
	FillHist((mapit->first + "MassRegion_syst").Data(),btagsyst.at(ib), weight , 0., 15.,15);
    }
  }



  //// Low Mass Signal region
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) {
    FillCLHist(sighist, "LowMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    
    if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
      FillHist("LowMass_TT", electronAnalysisColl.at(0).Pt() , 1.,  0. , 100., 20);
      FillHist("LowMass_TT_w",electronAnalysisColl.at(0).Pt() , weight,  0. , 100., 20);
      FillHist("LowMass_TT", electronAnalysisColl.at(1).Pt() , 1.,  0. , 100., 20);
      FillHist("LowMass_TT_w",electronAnalysisColl.at(1).Pt() , weight,  0. , 100., 20);
      
    }
    if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
      FillHist("LowMass_TL", electronAnalysisColl.at(0).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_TL_w", electronAnalysisColl.at(0).Pt() , weight,  0. , 100., 20);
      FillHist("LowMass_TL", electronAnalysisColl.at(1).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_TL_w", electronAnalysisColl.at(1).Pt() , weight,  0. , 100., 20);

    }
    if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
      FillHist("LowMass_LT", electronAnalysisColl.at(0).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_LT_w", electronAnalysisColl.at(0).Pt() , weight,  0. , 100., 20);
      FillHist("LowMass_LT", electronAnalysisColl.at(1).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_LT_w", electronAnalysisColl.at(1).Pt() , weight,  0. , 100., 20);
    }
    if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
      FillHist("LowMass_LL",   electronAnalysisColl.at(0).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_LL_w",electronAnalysisColl.at(0).Pt() , weight,  0. , 100., 20);
      FillHist("LowMass_LL",   electronAnalysisColl.at(1).Pt() ,1.,  0. , 100., 20);
      FillHist("LowMass_LL_w",electronAnalysisColl.at(1).Pt() , weight,  0. , 100., 20);
    }


    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso) FillCLHist(sighist, "LowMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_30_0905_nor);
    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "lowmass");
  }
  
  if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    FillCLHist(sighist, "MediumMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    
    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso)  FillCLHist(sighist, "MediumMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_30_0905_nor);
    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "midmass");
  }
  if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    FillCLHist(sighist, "HighMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso)FillCLHist(sighist, "HighMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,ee_weight_30_0905_nor);

    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "highmass");
  }
  
  
  if((nbjet!=0))   {
    FillCLHist(sighist, "BJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    FillCLHist(sighist, "BJetCR_20_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,  ee_weight_20_nor);
    FillCLHist(sighist, "BJetCR_40_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,  ee_weight_40_nor);
  }

  if((nbjet==0) && (eventbase->GetEvent().PFMET() > 50.)) {
    FillCLHist(sighist, "HighMETCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    FillCLHist(sighist, "HighMETCR_20_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,   ee_weight_20_nor);
    FillCLHist(sighist, "HighMETCR_40_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,   ee_weight_40_nor);
  }

  if((nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)) FillCLHist(sighist, "HighMETBJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  
  
  bool no_emuoverlap= true;
  for(unsigned int i=0; i < electronAnalysisColl.size() ; i++){
    for(unsigned int j=0; j < muonTightColl.size() ; j++){
      float dR =  electronAnalysisColl[i].DeltaR(muonTightColl[j]);
      if(dR < 0.1) no_emuoverlap= false;
    }
  }
  
  
  
  return;
}// End of execute event loop

void HNDiElectron::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
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


bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < cuts.at(0)) return false;
  if(electrons.at(1).Pt() < cuts.at(1)) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;

  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  if(mass < cuts.at(2)) return false;
  if(mass > cuts.at(3)) return false;
  if(fabs(mass-90.) < 10.) return false;

  if(jets.at(0).Pt() < cuts.at(9)) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;

  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }


  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > cuts.at(5)) return false;
  if(jj.M() < cuts.at(4)) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;

  if(eejj.M()  > cuts.at(7)) return false;
  if(eejj.M()  < cuts.at(6)) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(e1jj.M() > e1jjmax) return false;
  //if(e1jj.M() < e1jjmin) return false;

  snu::KParticle e2jj = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;

  if(e2jj.M() > cuts.at(11)) return false;
  if(e2jj.M() < cuts.at(10)) return false;
  
  if(evmet > cuts.at(8)) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }

  if(nbjet > 0) return false;

  return true;

}

bool HNDiElectron::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 120.) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M() > 220.)return false;

  if(eventbase->GetEvent().PFMET() > 30.) return false;
  
  float st=0.;
  for(unsigned int ij=0; ij < jets.size(); ij++){
    st+= jets.at(ij).Pt();
  }
  for(unsigned int ie=0; ie < electrons.size(); ie++){
    st+= electrons.at(ie).Pt();
  }
  st+= eventbase->GetEvent().PFMET();
  if(st > 250.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    float emfrac = jets.at(ij).NeutralEMEnergyFraction() +jets.at(ij).ChargedEMEnergyFraction();
    //if(emfrac > 0.65) return false;
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  //  if(electrons.at(0).NBrems() > 3) return false;
  //  if(electrons.at(1).NBrems() > 3) return false;

  

  return true;
  
}

bool HNDiElectron::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 30.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(jets.at(0).Pt() < 30.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
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


  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    float emfrac = jets.at(ij).NeutralEMEnergyFraction() +jets.at(ij).ChargedEMEnergyFraction();
    //if(emfrac > 0.7) return false;
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  //if(electrons.at(0).NBrems() > 3) return false;
  //if(electrons.at(1).NBrems() > 3) return false;


  return true;
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
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

  if(eventbase->GetEvent().PFMET() > 35.) return false;
  //if(jets.at(0).DeltaR(jets.at(1)) > 2.5) return false;
  if(jets.at(0).Pt() < 45.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



void HNDiElectron::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
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
  if(!k_isdata)    fBTagSF = new BTagSFUtil("CSVM");
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  
  DeclareVariable(k_met, "met", "MyTree");
  DeclareVariable(k_eemass, "ee_mass", "MyTree");
  DeclareVariable(k_eejjmass, "eejj_mass", "MyTree");
  DeclareVariable(k_e1jjmass, "e1jj_mass", "MyTree");
  DeclareVariable(k_e2jjmass, "e2jj_mass", "MyTree");
  DeclareVariable(k_njet, "njet", "MyTree");
  DeclareVariable(k_nbjet_l , "nbjet_l",  "MyTree");
  DeclareVariable(k_nbjet_m , "nbjet_m",  "MyTree");
  DeclareVariable(k_nbjet_t , "nbjet_t",  "MyTree");
  DeclareVariable(k_jjmass, "jj_mass", "MyTree");
  DeclareVariable(k_st, "st", "MyTree");
  DeclareVariable(k_ht, "ht", "MyTree");
  DeclareVariable(k_el1pt, "el1_pt", "MyTree");
  DeclareVariable(k_el2pt, "el2_pt", "MyTree");
  DeclareVariable(k_j1pt, "jet1_pt", "MyTree");
  DeclareVariable(k_weight, "weight", "MyTree");
  return;
  
}

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  if(!k_isdata) delete fBTagSF;
  
 }
     

void HNDiElectron::FillEventCutFlow(TString cut, float weight){

  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",13,0.,13.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"NoCut_w");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"EventCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(7,"eedR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(8,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(9,"SS_lepveto");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(10,"SS_samevertex");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(11,"Preselection");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(12,"Preselection_bjetm");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(13,"Preselection_bjett");
  }
  
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




//  LocalWords:  masscuts jetResdown
