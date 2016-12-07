// $Id: ExampleAnalyzerDiMuon.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzerDiMuon Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzerDiMuon.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzerDiMuon);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
ExampleAnalyzerDiMuon::ExampleAnalyzerDiMuon() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzerDiMuon");
  
  Message("In ExampleAnalyzerDiMuon constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  MakeCleverHistograms(sighist_mm,"DiMuon");
  MakeCleverHistograms(sighist_mm,"DiMuon_BJet");
  MakeCleverHistograms(sighist_mm,"SSMuon");
  MakeCleverHistograms(trilephist,"TriMuon");
  MakeCleverHistograms(trilephist,"TriMuon_noB");
  MakeCleverHistograms(trilephist,"TriMuon_nomet");
  MakeCleverHistograms(trilephist,"TriMuonEl");

}


void ExampleAnalyzerDiMuon::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  Message("Making clever hists for Z ->ll test code", INFO);
  
  /// only available in v7-6-X branch and newer
  //// default lumimask is silver ////
  //// In v7-6-2-(current) the default is changed to gold (since METNoHF bug)
  ///When METNoHF isfixed the default will be back to silver
  /// set to gold if you want to use gold json in analysis
  /// To set uncomment the line below:


  return;
}


void ExampleAnalyzerDiMuon::ExecuteEvents()throw( LQError ){

  /// Apply the gen weight 
  if(!isData) weight*=MCweight;

  FillHist("signal_eff", 1., 1., 0., 10., 10);
  
  //return;
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  FillCutFlow("NoCut", weight);
    
  if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  
  ///#### CAT:::PassBasicEventCuts is updated: uses selections as described in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters: If you see this is out of date please comment
  if(!PassMETFilter()) return;     /// Initial event cuts :
  FillCutFlow("EventCut", weight);
  
  /// #### CAT::: triggers stored are all HLT_Ele/HLT_DoubleEle/HLT_Mu/HLT_TkMu/HLT_Photon/HLT_DoublePhoton

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
    
  TString dimuon_trigmuon_trig1="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v";
  
  vector<TString> trignames;
  trignames.push_back(dimuon_trigmuon_trig1);
        
  //if(!PassTrigger(triggerslist, prescale)) return;
  //FillCutFlow("TriggerCut", weight);
  
  //FillHist("signal_eff", 1., 1., 0., 10., 10);
  
  // Trigger matching is done using KMuon::TriggerMatched(TString) which returns a bool
  /* // #### CAT::: trigger matching information is stored for muons and electrons for:
  ///HLT_IsoMu24_eta2p1_v
  ///HLT_Mu17_Mu8_DZ_v
  ///HLT_Mu17_TkMu8_DZ_v
  ///HLT_IsoMu20
  ///HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v
  ///HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v
  ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v
  ///HLT_Ele12_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v
  ///HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v
  ///HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v
  ///HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v
  ///HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
  ///HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v
  ///HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v
  ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
  ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_
  ///HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v
  ///HLT_Ele27_eta2p1_WPLoose_Gsf_TriCentralPFJet30_v
  */
  
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
  std::vector<snu::KJet> jets =   GetJets("JET_HN");
  int nbjet = NBJet(GetJets("JET_HN"));
  FillHist("Njets", jets.size() ,weight, 0. , 5., 5);
  
  TString muon_id = "MUON_POG_TIGHT";
  BaseSelection::ID muid = BaseSelection::MUON_POG_TIGHT;
  //TString muid = "MUON_POG_TIGHT";
  if(k_running_nonprompt) {
    muid= BaseSelection::MUON_POG_LOOSE;
    muon_id = "MUON_POG_LOOSE";
  }
  //std::vector<snu::KMuon> muons = GetMuons("MUON_HN_TIGHT",false);
  std::vector<snu::KMuon> muons = GetMuons(muid,false);
  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",false);
  
  /// can call POGVeto/POGLoose/POGMedium/POGTight/ HNVeto/HNLoose/HNTight/NoCut/NoCutPtEta 
  std::vector<snu::KElectron> electrons = GetElectrons("ELECTRON_POG_TIGHT");
  std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
  
  bool trig_pass = PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float current_weight(1.);
  float temp_pileup_reweight(1.);
  float pileup_reweight(1.);
  
  if(!isData){
    id_iso_sf =   MuonScaleFactor(muon_id, muons,0);
    id_iso_sf *= MuonISOScaleFactor(muon_id, muons,0);
    id_iso_sf *= MuonTrackingEffScaleFactor(muons);
    
    pileup_reweight = eventbase->GetEvent().PileUpWeight();
    temp_pileup_reweight = TempPileupWeight(); 
    
    trigger_ps = WeightByTrigger(trignames, TargetLumi);
    trigger_sf = TriggerScaleFactor(electrons, muons, "HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    
    current_weight = weight * id_iso_sf * trigger_ps * trigger_sf;
    //current_weight = weight * id_iso_sf * trigger_sf;
    
  }
  if(!isData){
    CorrectMuonMomentum(muons);
  }
  //current_weight = 1.;
  //pileup_reweight = 1.;

  /*
    cout << "id_iso_sf : " << id_iso_sf << endl;
    cout << "muon tracking SF : " << MuonTrackingEffScaleFactor(muons) << endl;
    cout << "trigger_sf : " << trigger_sf << endl;
    cout << "trigger_ps : " << trigger_ps << endl;
    cout << "weight : " << weight << endl;
  */

  /*
  if(k_running_nonprompt){
    current_weight      *=  Get_DataDrivenWeight_MM(muons,"POGTIGHT");
  }
  */
  
  int njet = jets.size();
  FillHist("GenWeight_NJet" , njet*MCweight + MCweight*0.1, 1., -6. , 6., 12);
  
  int nvtx = eventbase->GetEvent().nVertices();
  
  numberVertices = eventbase->GetEvent().nVertices();   
  
  
  if (Zcandidate(muons, 20., true)){
    ////Make NVTX plotsfor reweighting
    if(isData) FillHist("Nvtx_data",  eventbase->GetEvent().nVertices() , current_weight, 0. , 50., 50);
    else  FillHist("Nvtx_mc",  eventbase->GetEvent().nVertices() , current_weight, 0. , 50., 50);
  }
  
  float MET = eventbase->GetEvent().PFMET();
  bool prompt_match = false;
  int n_bjet = NBJet(jets);
  
  if(trig_pass) FillHist("signal_eff", 2., 1., 0., 10., 10); 
  
  //OS
  if(muons.size() == 2 && muons_veto.size() == 2 && electrons_veto.size() == 0 && muons.at(0).Charge() != muons.at(1).Charge() && !k_running_nonprompt){          
    
    //FillHist("signal_eff", 3., 1., 0., 10., 10);
    
    snu::KParticle Z = muons.at(0) + muons.at(1);
    
    if(!isData){
      if( (muons.at(0).MotherPdgId() == 23 || (fabs(muons.at(0).MotherPdgId()) == 24 && muons.at(0).MotherPdgId()*muons.at(0).Charge() > 0))
	  && (muons.at(1).MotherPdgId() == 23 || (fabs(muons.at(1).MotherPdgId()) == 24 && muons.at(1).MotherPdgId()*muons.at(1).Charge() > 0)) )
	{
	  prompt_match = true;
	}
    }
    if(isData) prompt_match = true;
    
    if(muons.at(0).Pt() > 20 && muons.at(1).Pt() > 20. && Z.M() > 10 && trig_pass){
      
      FillHist("signal_eff", 3., 1., 0., 10., 10);

      /*
      cout << "id_iso_sf : " << id_iso_sf << endl;
      cout << "trigger_sf : " << trigger_sf << endl;
      cout << "trigger_ps : " << trigger_ps << endl;
      cout << "weight : " << weight << endl;
      */
      FillHist("id_iso_sf", id_iso_sf, 1., 0., 10., 1000);
      FillHist("trigger_sf", trigger_sf, 1., 0., 10., 1000);



      /*
	if(k_running_nonprompt){
	current_weight = 1.;
	current_weight *= Get_DataDrivenWeight_MM(muons, "POGTIGHT");
	}
      */
      /*
      FillHist("Njets_jets_OS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
      FillHist("Nvtx_jets_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
      FillHist("mass_mumu_jets_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
      FillHist("pt_mumu_jets_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
      FillHist("pt_1st_lepton_jets_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
      FillHist("pt_2nd_lepton_jets_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
      FillHist("eta_1st_lepton_jets_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
      FillHist("eta_2nd_lepton_jets_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
      FillHist("MET_jets_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

      FillHist("Njets_jets_OS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
      FillHist("Nvtx_jets_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
      FillHist("mass_mumu_jets_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
      FillHist("pt_mumu_jets_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
      FillHist("pt_1st_lepton_jets_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
      FillHist("pt_2nd_lepton_jets_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
      FillHist("eta_1st_lepton_jets_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
      FillHist("eta_2nd_lepton_jets_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
      FillHist("MET_jets_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      */

      if(jets.size() > 3 && MET > 75){//first CR
      
	FillHist("Njets_first_CR_OS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
	FillHist("Nvtx_first_CR_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
 	FillHist("mass_mumu_first_CR_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_first_CR_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_first_CR_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_first_CR_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_first_CR_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_first_CR_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_first_CR_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("Njets_first_CR_OS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
	FillHist("Nvtx_first_CR_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
	FillHist("mass_mumu_first_CR_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_first_CR_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_first_CR_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_first_CR_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_first_CR_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_first_CR_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("MET_first_CR_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }
      
      if(jets.size() > 2 && muons.at(0).Pt() < 50 && muons.at(1).Pt() < 50){//second CR
	
	FillHist("Njets_second_CR_OS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
        FillHist("Nvtx_second_CR_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_second_CR_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_second_CR_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_second_CR_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_second_CR_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_second_CR_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_second_CR_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("MET_second_CR_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

        FillHist("Njets_second_CR_OS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
        FillHist("Nvtx_second_CR_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_second_CR_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_second_CR_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_second_CR_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_second_CR_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_second_CR_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_second_CR_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_second_CR_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);

      }

      if(muons.at(0).Pt() < 50 && muons.at(1).Pt() < 50){//third CR
	
	FillHist("Njets_third_CR_OS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
        FillHist("Nvtx_third_CR_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_third_CR_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_third_CR_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_third_CR_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_third_CR_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_third_CR_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_third_CR_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("MET_third_CR_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

        FillHist("Njets_third_CR_OS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
        FillHist("Nvtx_third_CR_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_third_CR_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_third_CR_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_third_CR_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_third_CR_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_third_CR_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_third_CR_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_third_CR_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);

      }

      if(Z.M() > 80 && Z.M() < 100){//fourth CR 
	
        FillHist("Njets_fourth_CR_OS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
	FillHist("Nvtx_fourth_CR_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_fourth_CR_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_fourth_CR_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_fourth_CR_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_fourth_CR_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_fourth_CR_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_fourth_CR_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_fourth_CR_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("Njets_fourth_CR_OS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
	FillHist("Nvtx_fourth_CR_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_fourth_CR_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_fourth_CR_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_fourth_CR_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_fourth_CR_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_fourth_CR_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_fourth_CR_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_fourth_CR_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);

      }
      /*
      if(jets.size() == 0){
	FillHist("Nvtx_0jet_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
	FillHist("mass_mumu_0jet_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_0jet_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_0jet_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_0jet_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_0jet_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_0jet_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_0jet_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("Nvtx_0jet_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_0jet_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_0jet_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_0jet_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_0jet_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_0jet_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_0jet_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_0jet_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }// 0jet
      
      if(jets.size() == 1){
	FillHist("Nvtx_1jet_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
	FillHist("mass_mumu_1jet_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_1jet_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_1jet_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_1jet_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_1jet_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_1jet_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_1jet_OS_PU", jets.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_1jet_OS_PU", jets.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_1jet_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("Nvtx_1jet_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_1jet_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_1jet_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_1jet_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_1jet_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_1jet_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_1jet_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("pt_1st_jet_1jet_OS_tempPU", jets.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_jet_1jet_OS_tempPU", jets.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_1jet_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);

      }// 1jet
      
      int Njet = jets.size();
      
      //if(jets.size() > 1 && jets.at( jets.size() - 1 ).Pt() > 20){
      if(jets.size() > 1 && jets.size() < 4){   	 
	
	FillHist("Nvtx_2jet_OS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
	FillHist("mass_mumu_2jet_OS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_2jet_OS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_2jet_OS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_2jet_OS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_2jet_OS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_2jet_OS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_2jet_OS_PU", jets.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_jet_2jet_OS_PU", jets.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_2jet_OS_PU", jets.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_jet_2jet_OS_PU", jets.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	
	FillHist("Nvtx_2jet_OS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
	FillHist("mass_mumu_2jet_OS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_2jet_OS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_2jet_OS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_2jet_OS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_2jet_OS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_2jet_OS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_2jet_OS_tempPU", jets.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_jet_2jet_OS_tempPU", jets.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_2jet_OS_tempPU", jets.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_jet_2jet_OS_tempPU", jets.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	
	
	snu::KParticle W = jets.at(0) + jets.at(1);
	FillHist("mass_jj_2jet_OS_PU", W.M(), current_weight * pileup_reweight, 0., 5000., 5000);
	FillHist("mass_lljj_2jet_OS_PU", (W + Z).M(), current_weight * pileup_reweight, 0., 5000., 5000);
	FillHist("MET_2jet_OS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("mass_jj_2jet_OS_tempPU", W.M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);
	FillHist("mass_lljj_2jet_OS_tempPU", (W + Z).M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);
	FillHist("MET_2jet_OS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }// Njet > 1

      if(jets.size() > 3){
	snu::KParticle Zp = muons.at(0) + muons.at(1) + jets.at(0) + jets.at(1) +  jets.at(2) +  jets.at(3);
	FillHist("mass_lljjjj_4jet_OS_PU", Zp.M(), current_weight * pileup_reweight, 0., 5000., 5000);
	FillHist("mass_lljjjj_4jet_OS_tempPU", Zp.M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);
	FillHist("signal_eff", 4., 1., 0., 10., 10);
	
      }//Njet > 4
      */
    }//muon pt > 20
  }//N muon == 2 & OS
  
  prompt_match = false;
  //SS
  if(muons.size() == 2 && muons_veto.size() == 2 && electrons_veto.size() == 0 && muons.at(0).Charge() == muons.at(1).Charge() && trig_pass) {
    snu::KParticle Z = muons.at(0) + muons.at(1);
    
    if(!isData){
      if( (muons.at(0).MotherPdgId() == 23 || (fabs(muons.at(0).MotherPdgId()) == 24 && muons.at(0).MotherPdgId()*muons.at(0).Charge() > 0))
	  && (muons.at(1).MotherPdgId() == 23 || (fabs(muons.at(1).MotherPdgId()) == 24 && muons.at(1).MotherPdgId()*muons.at(1).Charge() > 0)) )
	{
	  prompt_match = true;
	}
    }
    if(isData) prompt_match = true;
    
    if(muons.at(1).Pt() > 20. && Z.M() > 10){
      
      if(k_running_nonprompt){
	current_weight = 1.;
	current_weight *= Get_DataDrivenWeight_MM(muons, "POGTIGHT");
      }
      /*
      FillHist("Njets_jets_SS_PU", jets.size() , current_weight * pileup_reweight, 0. , 10., 10);
      FillHist("Nvtx_jets_SS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
      FillHist("mass_mumu_jets_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
      FillHist("pt_mumu_jets_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
      FillHist("pt_1st_lepton_jets_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
      FillHist("pt_2nd_lepton_jets_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
      FillHist("eta_1st_lepton_jets_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
      FillHist("eta_2nd_lepton_jets_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
      FillHist("MET_jets_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

      FillHist("Njets_jets_SS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
      FillHist("Nvtx_jets_SS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
      FillHist("mass_mumu_jets_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
      FillHist("pt_mumu_jets_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
      FillHist("pt_1st_lepton_jets_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
      FillHist("pt_2nd_lepton_jets_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
      FillHist("eta_1st_lepton_jets_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
      FillHist("eta_2nd_lepton_jets_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
      FillHist("MET_jets_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      */
      if(jets.size() > 3 && MET > 75){//first CR
        FillHist("Njets_first_CR_SS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
	FillHist("Nvtx_first_CR_SS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_first_CR_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_first_CR_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_first_CR_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_first_CR_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_first_CR_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_first_CR_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("MET_first_CR_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
        FillHist("Njets_first_CR_SS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
	FillHist("Nvtx_first_CR_SS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_first_CR_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_first_CR_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_first_CR_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_first_CR_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_first_CR_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_first_CR_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_first_CR_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }
      
      if(jets.size() > 2 && muons.at(0).Pt() < 50){//second CR
        FillHist("Njets_second_CR_SS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
        FillHist("Nvtx_second_CR_SS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_second_CR_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_second_CR_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_second_CR_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_second_CR_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_second_CR_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_second_CR_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("MET_second_CR_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

        FillHist("Njets_second_CR_SS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
        FillHist("Nvtx_second_CR_SS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_second_CR_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_second_CR_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_second_CR_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_second_CR_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_second_CR_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_second_CR_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_second_CR_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }
      
      if(muons.at(0).Pt() < 50){//third CR
        FillHist("Njets_third_CR_SS_PU", jets.size() , current_weight * pileup_reweight , 0. , 10., 10);
	FillHist("Nvtx_third_CR_SS_PU", nvtx , current_weight * pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_third_CR_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_third_CR_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_third_CR_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_third_CR_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_third_CR_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_third_CR_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_third_CR_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);

        FillHist("Njets_third_CR_SS_tempPU", jets.size() , current_weight * temp_pileup_reweight, 0. , 10., 10);
	FillHist("Nvtx_third_CR_SS_tempPU", nvtx , current_weight * temp_pileup_reweight, 0. , 50., 50);
        FillHist("mass_mumu_third_CR_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_third_CR_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_third_CR_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_third_CR_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_third_CR_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_third_CR_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_third_CR_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }
      
      /*
      if(jets.size() == 0){
	FillHist("mass_mumu_0jet_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_0jet_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_0jet_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_0jet_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_0jet_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_0jet_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_0jet_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("mass_mumu_0jet_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_0jet_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_0jet_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_0jet_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_0jet_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_0jet_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_0jet_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }// 0jet       
      */
      /*
      if(jets.size() == 1){
	FillHist("mass_mumu_1jet_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_1jet_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_1jet_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_1jet_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_1jet_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_1jet_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_1jet_SS_PU", jets.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_1jet_SS_PU", jets.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_1jet_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("mass_mumu_1jet_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_1jet_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_1jet_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_1jet_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_1jet_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_1jet_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("pt_1st_jet_1jet_SS_tempPU", jets.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_jet_1jet_SS_tempPU", jets.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_1jet_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }// 1jet
      */
      /*
      if(n_bjet == 1){
	FillHist("mass_mumu_1bjet_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_1bjet_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_1bjet_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_1bjet_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_1bjet_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_1bjet_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_1bjet_SS_PU", jets.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_1bjet_SS_PU", jets.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("MET_1bjet_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("mass_mumu_1bjet_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_mumu_1bjet_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
        FillHist("pt_1st_lepton_1bjet_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("pt_2nd_lepton_1bjet_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_lepton_1bjet_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("eta_2nd_lepton_1bjet_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("pt_1st_jet_1bjet_SS_tempPU", jets.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
        FillHist("eta_1st_jet_1bjet_SS_tempPU", jets.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
        FillHist("MET_1bjet_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
      }
      */
      int Njet = jets.size();
      /*
      if(jets.size() > 1 && jets.size() < 4){

	FillHist("mass_mumu_2jet_SS_PU", fabs(Z.M()), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_2jet_SS_PU", Z.Pt(), current_weight * pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_2jet_SS_PU", muons.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_2jet_SS_PU", muons.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_2jet_SS_PU", muons.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_2jet_SS_PU", muons.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_2jet_SS_PU", jets.at(0).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_jet_2jet_SS_PU", jets.at(1).Pt() , current_weight * pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_2jet_SS_PU", jets.at(0).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_jet_2jet_SS_PU", jets.at(1).Eta() , current_weight * pileup_reweight, -5. , 5., 1000);
	
	FillHist("mass_mumu_2jet_SS_tempPU", fabs(Z.M()), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_mumu_2jet_SS_tempPU", Z.Pt(), current_weight * temp_pileup_reweight, 0., 1000., 1000);
	FillHist("pt_1st_lepton_2jet_SS_tempPU", muons.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_lepton_2jet_SS_tempPU", muons.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_lepton_2jet_SS_tempPU", muons.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_lepton_2jet_SS_tempPU", muons.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("pt_1st_jet_2jet_SS_tempPU", jets.at(0).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("pt_2nd_jet_2jet_SS_tempPU", jets.at(1).Pt() , current_weight * temp_pileup_reweight, 0. , 1000., 1000);
	FillHist("eta_1st_jet_2jet_SS_tempPU", jets.at(0).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	FillHist("eta_2nd_jet_2jet_SS_tempPU", jets.at(1).Eta() , current_weight * temp_pileup_reweight, -5. , 5., 1000);
	
	
	snu::KParticle W = jets.at(0) + jets.at(1);
	FillHist("mass_jj_2jet_SS_PU", W.M(), current_weight * pileup_reweight, 0., 5000., 5000);
	FillHist("mass_lljj_2jet_SS_PU", (W + Z).M(), current_weight * pileup_reweight, 0., 5000., 5000);
	FillHist("MET_2jet_SS_PU", MET, current_weight * pileup_reweight, 0., 1000., 1000);
	
	FillHist("mass_jj_2jet_SS_tempPU", W.M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);
	FillHist("mass_lljj_2jet_SS_tempPU", (W + Z).M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);
	FillHist("MET_2jet_SS_tempPU", MET, current_weight * temp_pileup_reweight, 0., 1000., 1000);
	
      }// Njet > 1

      if(jets.size() > 3){
	snu::KParticle Zp = muons.at(0) + muons.at(1) + jets.at(0) + jets.at(1) +  jets.at(2) +  jets.at(3);
	FillHist("mass_lljjjj_4jet_SS_PU", Zp.M(), current_weight * pileup_reweight, 0., 5000., 5000);
        FillHist("mass_lljjjj_4jet_SS_tempPU", Zp.M(), current_weight * temp_pileup_reweight, 0., 5000., 5000);

      }//Njet > 4
      */
    }//muon pt > 20
  }//N muon == 2 & SS
  
  
  return;
}// End of execute event loop



void ExampleAnalyzerDiMuon::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ExampleAnalyzerDiMuon::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) //reweightPU = new Reweight((analysisdir + "SNUCAT_Pileup.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

ExampleAnalyzerDiMuon::~ExampleAnalyzerDiMuon() {
  
  Message("In ExampleAnalyzerDiMuon Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzerDiMuon::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 5,0.,5.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"DiMu_tight");
   
    
  }
}


void ExampleAnalyzerDiMuon::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void ExampleAnalyzerDiMuon::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerDiMuonCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzerDiMuon::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



