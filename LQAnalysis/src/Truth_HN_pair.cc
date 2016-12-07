// $Id: Truth_HN_pair.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQTruth_HN_pair Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "Truth_HN_pair.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (Truth_HN_pair);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
Truth_HN_pair::Truth_HN_pair() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("Truth_HN_pair");
  
  Message("In Truth_HN_pair constructor", INFO);
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


void Truth_HN_pair::InitialiseAnalysis() throw( LQError ) {
  
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


void Truth_HN_pair::ExecuteEvents()throw( LQError ){

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
  
  //TString muon_id = "MUON_POG_TIGHT";
  //TString muon_id = "MUON_HN_VETO";
  TString muon_id = "MUON_NOCUT";
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
  
  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);
  
  std::vector<snu::KGenJet> genjets;
  eventbase->GetGenJetSel()->Selection(genjets);
  
  
  
  //cout << "Truth Coll" << endl;
  bool running_signal = true;
  int mu_1_index, mu_2_index;
  if(running_signal){
    //int mu_1_index, mu_2_index;
    bool mu_1_tf = false;
    bool mu_2_tf = false;
    for(int i = 0; i < truthColl.size(); i++){
      //cout << "Index : " << i << ", PdgId : " << truthColl.at(i).PdgId() << ", IndexMother : " << truthColl.at(i).IndexMother() << endl;
      int i_mother = truthColl.at(i).IndexMother();
      if(fabs( truthColl.at(i).PdgId() ) == 13 && truthColl.at(i_mother).PdgId() == 9900014 && !mu_1_tf){
	mu_1_index = i;
	mu_1_tf = true;
	continue;
      } 
      if(fabs( truthColl.at(i).PdgId() ) == 13 && truthColl.at(i_mother).PdgId() == 9900014 && !mu_2_tf && mu_1_tf){
	mu_2_index = i;
	mu_2_tf = true;
      }
    }//trutchcoll for loop 1st
    int mu_1_i_mother = truthColl.at(mu_1_index).IndexMother();
    int mu_2_i_mother = truthColl.at(mu_2_index).IndexMother();
    //cout << "mu_1 pdgid : " << truthColl.at(mu_1_index).PdgId() << ", Mother PdgId : " << truthColl.at(mu_1_i_mother).PdgId() << ", Mother index : " << mu_1_i_mother << endl;
    //cout << "mu_2 pdgid : " << truthColl.at(mu_2_index).PdgId() << ", Mother PdgId : " << truthColl.at(mu_2_i_mother).PdgId() << ", Mother index : " << mu_2_i_mother << endl;
    
    std::vector<int> HN_1_partons_i;
    std::vector<int> HN_2_partons_i;
    
    for(int i = 0; i < truthColl.size(); i++){
      if(truthColl.at(i).IndexMother() == mu_1_i_mother && fabs( truthColl.at(i).PdgId() ) != 13) HN_1_partons_i.push_back(i);
      if(truthColl.at(i).IndexMother() == mu_2_i_mother && fabs( truthColl.at(i).PdgId() ) != 13) HN_2_partons_i.push_back(i);
    }//trutchcoll for loop 2nd
    
    //cout << "N_HN_1_partons : " << HN_1_partons_i.size() << endl;
    //cout << "N_HN_2_partons : " << HN_2_partons_i.size() << endl;
    
    float HN_1_dR_jj = truthColl.at(HN_1_partons_i[0]).DeltaR( truthColl.at(HN_1_partons_i[1]) );
    float HN_2_dR_jj = truthColl.at(HN_2_partons_i[0]).DeltaR( truthColl.at(HN_2_partons_i[1]) );
    
    if(truthColl.at(mu_1_i_mother).Pt() > truthColl.at(mu_2_i_mother).Pt()){
      FillHist("dR_jj_HN_1_truth", HN_1_dR_jj, 1., 0., 10., 1000);
      FillHist("dR_jj_HN_2_truth", HN_2_dR_jj, 1., 0., 10., 1000);
    }
    if(truthColl.at(mu_1_i_mother).Pt() < truthColl.at(mu_2_i_mother).Pt()){
      FillHist("dR_jj_HN_1_truth", HN_2_dR_jj, 1., 0., 10., 1000);
      FillHist("dR_jj_HN_2_truth", HN_1_dR_jj, 1., 0., 10., 1000);
    }


    FillHist("dR_mu1_q1", truthColl.at(mu_1_index).DeltaR(truthColl.at(HN_1_partons_i[0])), 1., 0., 10., 1000);
    FillHist("dR_mu1_q2", truthColl.at(mu_1_index).DeltaR(truthColl.at(HN_1_partons_i[1])), 1., 0., 10., 1000);
    FillHist("dR_mu2_q1", truthColl.at(mu_2_index).DeltaR(truthColl.at(HN_2_partons_i[0])), 1., 0., 10., 1000);
    FillHist("dR_mu2_q2", truthColl.at(mu_2_index).DeltaR(truthColl.at(HN_2_partons_i[1])), 1., 0., 10., 1000);
    
    FillHist("q_1_pt_over_mu1_pt", truthColl.at(HN_1_partons_i[0]).Pt() /  truthColl.at(mu_1_index).Pt(), 1., 0., 2., 1000);
    FillHist("q_2_pt_over_mu1_pt", truthColl.at(HN_1_partons_i[1]).Pt() /  truthColl.at(mu_1_index).Pt(), 1., 0., 2., 1000);
    FillHist("q_1_pt_over_mu2_pt", truthColl.at(HN_1_partons_i[0]).Pt() /  truthColl.at(mu_2_index).Pt(), 1., 0., 2., 1000);
    FillHist("q_2_pt_over_mu2_pt", truthColl.at(HN_1_partons_i[1]).Pt() /  truthColl.at(mu_2_index).Pt(), 1., 0., 2., 1000);


    float mu_1_iso_truth = (truthColl.at(HN_1_partons_i[0]).Pt() + truthColl.at(HN_1_partons_i[1]).Pt()) / truthColl.at(mu_1_index).Pt();
    float mu_2_iso_truth = (truthColl.at(HN_2_partons_i[0]).Pt() + truthColl.at(HN_2_partons_i[1]).Pt()) / truthColl.at(mu_2_index).Pt();
    float mu_1_iso_truth_04 = 0.;
    float mu_2_iso_truth_04 = 0.;
    
    for(int i = 0; i < 2; i ++){
      if(truthColl.at(mu_1_index).DeltaR(truthColl.at(HN_1_partons_i[i])) < 0.4) mu_1_iso_truth_04 += truthColl.at(HN_1_partons_i[i]).Pt();
      if(truthColl.at(mu_2_index).DeltaR(truthColl.at(HN_2_partons_i[i])) < 0.4) mu_2_iso_truth_04 += truthColl.at(HN_2_partons_i[i]).Pt();
    }
    mu_1_iso_truth_04 =  mu_1_iso_truth_04 / truthColl.at(mu_1_index).Pt();
    mu_2_iso_truth_04 =  mu_2_iso_truth_04 / truthColl.at(mu_2_index).Pt();


    FillHist("mu_1_iso_truth", mu_1_iso_truth, 1., 0., 2., 10000);
    FillHist("mu_2_iso_truth", mu_2_iso_truth, 1., 0., 2., 10000);
    FillHist("mu_1_iso_truth_04", mu_1_iso_truth_04, 1., 0., 2., 10000);
    FillHist("mu_2_iso_truth_04", mu_2_iso_truth_04, 1., 0., 2., 10000);


    
  }//if running signal
  FillHist("eta_muon_1_truth", truthColl.at(mu_1_index).Eta(), 1., -5., 5., 1000);
  FillHist("eta_muon_2_truth", truthColl.at(mu_2_index).Eta(), 1., -5., 5., 1000);
  
  FillHist("pt_muon_1_truth", truthColl.at(mu_1_index).Pt(), 1., 0., 1000., 1000);
  FillHist("pt_muon_2_truth", truthColl.at(mu_2_index).Pt(), 1., 0., 1000., 1000);
  
  



  
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
  //weight for signal samples
  if(running_signal){
    current_weight = 1.;
    pileup_reweight = 1.;
  }//if running signal 2nd
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
  
  //OS+SS

  FillHist("Nmuons", muons.size(), 1., 0., 10., 10);
  FillHist("Nelectrons", electrons_veto.size(), 1., 0., 10., 10);
  
  if(muons.size() == 2 && electrons_veto.size() == 0) FillHist("signal_eff", 3., 1., 0., 10., 10);
  if(muons.size() == 2 && electrons_veto.size() == 0 && muons.at(1).Pt() > 20){
    
    //FillHist("mu_1_iso03_OS_SS", muons.at(0).RelIso03(), current_weight * pileup_reweight, 0., 1., 10000);
        
    FillHist("signal_eff", 4., 1., 0., 10., 10);
    FillHist("Ngenjets", genjets.size(), 1., 0., 20., 20);
    
    FillHist("pt_muon_1", muons.at(0).Pt(), 1., 0., 1000., 1000);
    FillHist("pt_muon_2", muons.at(1).Pt(), 1., 0., 1000., 1000);

    bool mu_1_match = false;
    bool mu_2_match = false;
    int mu1_truth_1_i, mu2_truth_2_i;
    
    float dR_mu1_truth_1 = muons.at(0).DeltaR( truthColl.at(mu_1_index) );
    float dR_mu1_truth_2 = muons.at(0).DeltaR( truthColl.at(mu_2_index) );
    float dR_mu2_truth_1 = muons.at(1).DeltaR( truthColl.at(mu_1_index) );
    float dR_mu2_truth_2 = muons.at(1).DeltaR( truthColl.at(mu_2_index) );
    
    if(dR_mu1_truth_1 < dR_mu1_truth_2){
      mu1_truth_1_i = 0;
      mu2_truth_2_i = 1;
    }
    if(dR_mu1_truth_1 > dR_mu1_truth_2){
      mu1_truth_1_i = 1;
      mu2_truth_2_i = 0;
    }
    
    if( truthColl.at(mu_1_index).DeltaR(muons.at(mu1_truth_1_i)) < 0.01) mu_1_match = true;
    if( truthColl.at(mu_2_index).DeltaR(muons.at(mu2_truth_2_i)) < 0.01) mu_2_match = true;
    
    if(mu_1_match && mu_2_match){
      FillHist("signal_eff", 5., 1., 0., 10., 10);
      
      FillHist("mu_1_iso03_OS_SS", muons.at(0).RelIso03(), current_weight * pileup_reweight, 0., 1., 10000);
      FillHist("mu_1_iso04_OS_SS", muons.at(0).RelIso04(), current_weight * pileup_reweight, 0., 1., 10000);
      FillHist("mu_2_iso03_OS_SS", muons.at(1).RelIso03(), current_weight * pileup_reweight, 0., 1., 10000);
      FillHist("mu_2_iso04_OS_SS", muons.at(1).RelIso04(), current_weight * pileup_reweight, 0., 1., 10000);
      
      if(genjets.size() > 3){
	float min_dR_jet_mu_1 = 9999.;
	float min_dR_jet_mu_2 = 9999.;
	
	for(int i = 0; i < genjets.size(); i++){
	  float current_dR_mu1 = muons.at(0).DeltaR(genjets.at(i));
	  float current_dR_mu2 = muons.at(1).DeltaR(genjets.at(i));
	  
	  if(current_dR_mu1 < min_dR_jet_mu_1) min_dR_jet_mu_1 = current_dR_mu1;
	  if(current_dR_mu2 < min_dR_jet_mu_2) min_dR_jet_mu_2 = current_dR_mu2;
	}//for loop for genjets
	
	FillHist("dR_vetomu1_genj_OS_SS_PU", min_dR_jet_mu_1, current_weight * pileup_reweight, 0., 10., 10000);
	FillHist("dR_vetomu2_genj_OS_SS_PU", min_dR_jet_mu_2, current_weight * pileup_reweight, 0., 10., 10000);
      }
      
    }//mu_1 & mu_2 matched
  }//OS + SS

  
  return;
}// End of execute event loop



void Truth_HN_pair::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void Truth_HN_pair::BeginCycle() throw( LQError ){
  
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

Truth_HN_pair::~Truth_HN_pair() {
  
  Message("In Truth_HN_pair Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void Truth_HN_pair::FillCutFlow(TString cut, float weight){

  
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


void Truth_HN_pair::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void Truth_HN_pair::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this Truth_HN_pairCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void Truth_HN_pair::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



