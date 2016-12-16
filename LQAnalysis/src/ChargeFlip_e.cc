// $Id: ChargeFlip_e.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQChargeFlip_e Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ChargeFlip_e.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ChargeFlip_e);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
ChargeFlip_e::ChargeFlip_e() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("ChargeFlip_e");
  
  Message("In ChargeFlip_e constructor", INFO);
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
  MakeCleverHistograms(hnpairmm,"basic_PU");
  MakeCleverHistograms(hnpairmm,"basic_tempPU");
  MakeCleverHistograms(hnpairmm,"CR_1_PU");
  MakeCleverHistograms(hnpairmm,"CR_1_tempPU");
  MakeCleverHistograms(hnpairmm,"CR_2_PU");
  MakeCleverHistograms(hnpairmm,"CR_2_tempPU");
  MakeCleverHistograms(hnpairmm,"CR_3_PU");
  MakeCleverHistograms(hnpairmm,"CR_3_tempPU");
  MakeCleverHistograms(hnpairmm,"CR_4_PU");
  MakeCleverHistograms(hnpairmm,"CR_4_tempPU");

}


void ChargeFlip_e::InitialiseAnalysis() throw( LQError ) {
  
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

void ChargeFlip_e::ExecuteEvents()throw( LQError ){
  
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
  TString di_electron_trig1="";
  
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
  //std::vector<snu::KElectron> electrons = GetElectrons("ELECTRON_POG_TIGHT");
  std::vector<snu::KElectron> electrons = GetElectrons("ELECTRON_HN_TIGHT");
  std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
  
  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);
  
  

  if(electrons.size() != 2) return;
  if(muons.size() != 0) return;
  if(electrons.at(0).MotherPdgId() != 23 || electrons.at(1).MotherPdgId() != 23) return;
  snu::KParticle Z = electrons.at(0) + electrons.at(1);
  if(Z.M() > 100 || Z.M() < 80) return;
  if(electrons.at(0).Pt() < 25 || electrons.at(1).Pt() < 20) return;
  if(muons.size() != 0) return;
  
  float MET = eventbase->GetEvent().PFMET();
  if(MET > 30) return;
  
  
  //cout << "truthcoll " << truthColl.size() << endl;
  int mu_1_index, mu_2_index;
  
  bool mu_1_tf = false;
  bool mu_2_tf = false;
  for(int i = 0; i < truthColl.size(); i++){
    //cout << i << "\t" << truthColl.at(i).PdgId() << "\t" << truthColl.at(i).IndexMother() << endl;
    int i_mother = truthColl.at(i).IndexMother();
    if(fabs( truthColl.at(i).PdgId() ) == 11 && truthColl.at(i_mother).PdgId() == 23 && !mu_1_tf){
      mu_1_index = i;
      mu_1_tf = true;
      continue;
    }
    if(fabs( truthColl.at(i).PdgId() ) == 11 && truthColl.at(i_mother).PdgId() == 23 && !mu_2_tf && mu_1_tf){
      mu_2_index = i;
      mu_2_tf = true;
    }
  }
  //int mu_1_i_mother = truthColl.at(mu_1_index).IndexMother();
  //int mu_2_i_mother = truthColl.at(mu_2_index).IndexMother();
  //cout << "mu_1 pdgid : " << truthColl.at(mu_1_index).PdgId() << ", Mother PdgId : " << truthColl.at(mu_1_i_mother).PdgId() << ", Mother index : " << mu_1_i_mother << endl;
  //cout << "mu_2 pdgid : " << truthColl.at(mu_2_index).PdgId() << ", Mother PdgId : " << truthColl.at(mu_2_i_mother).PdgId() << ", Mother index : " << mu_2_i_mother << endl; 
  
  //bool trig_pass = PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  
    
  float min_dr = 0;
  int first_e_match_i, second_e_match_i;
  if(electrons.at(0).DeltaR(truthColl.at(mu_1_index)) < electrons.at(0).DeltaR(truthColl.at(mu_2_index))){
    first_e_match_i = mu_1_index;
    second_e_match_i = mu_2_index;
  }
  if(electrons.at(0).DeltaR(truthColl.at(mu_1_index)) > electrons.at(0).DeltaR(truthColl.at(mu_2_index))){
    first_e_match_i = mu_2_index;
    second_e_match_i =mu_1_index;
  }
  float dr_1st_e, dr_2nd_e;
  dr_1st_e = electrons.at(0).DeltaR(truthColl.at(first_e_match_i));
  dr_2nd_e = electrons.at(1).DeltaR(truthColl.at(second_e_match_i));
  
  if(dr_1st_e > 0.1 || dr_2nd_e > 0.1) return;
  /*
  cout << "1st " << electrons.at(0).Charge() << ", " << electrons.at(0).Pt() << ", truth : " << truthColl.at(first_e_match_i).PdgId() << ", " << truthColl.at(first_e_match_i).Pt() << endl;
  cout << "2nd " << electrons.at(1).Charge() <<", " <<electrons.at(1).Pt() <<", truth : " <<truthColl.at(second_e_match_i).PdgId() << ", " << truthColl.at(second_e_match_i).Pt() << endl;
  */
  
  //0.9, 1.4442, 1.556, 2.5
  
  //1st e
  if(electrons.at(0).Charge() * truthColl.at(first_e_match_i).PdgId() < 0){
    if(fabs(electrons.at(0).Eta()) < 0.9) FillHist("cf_true_B1", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(0).Eta()) > 0.9 && fabs(electrons.at(0).Eta()) < 1.4442)  FillHist("cf_true_B2", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(0).Eta()) > 1.556 && fabs(electrons.at(0).Eta()) < 2.5)  FillHist("cf_true_E", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_true_global_pt", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_true_global_eta", electrons.at(0).Eta(), 1., -3., 3., 12);
  }
  if(electrons.at(0).Charge() * truthColl.at(first_e_match_i).PdgId() > 0){
    if(fabs(electrons.at(0).Eta()) < 0.9) FillHist("cf_false_B1", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(0).Eta()) > 0.9 && fabs(electrons.at(0).Eta()) < 1.4442)  FillHist("cf_false_B2", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(0).Eta()) > 1.556 && fabs(electrons.at(0).Eta()) < 2.5)  FillHist("cf_false_E", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_false_global_pt", 1. / electrons.at(0).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_false_global_eta", electrons.at(0).Eta(), 1., -3., 3., 12);
    FillHist("which_false", 1.5, 1., 0., 5., 5);
  }
  //2nd e
  if(electrons.at(1).Charge() * truthColl.at(second_e_match_i).PdgId() < 0){
    if(fabs(electrons.at(1).Eta()) < 0.9) FillHist("cf_true_B1", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(1).Eta()) > 0.9 && fabs(electrons.at(1).Eta()) < 1.4442)  FillHist("cf_true_B2", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(1).Eta()) > 1.556 && fabs(electrons.at(1).Eta()) < 2.5)  FillHist("cf_true_E", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_true_global_pt", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_true_global_eta", electrons.at(1).Eta(), 1., -3., 3., 12);
  }
  if(electrons.at(1).Charge() * truthColl.at(second_e_match_i).Charge() > 0){
    if(fabs(electrons.at(1).Eta()) < 0.9) FillHist("cf_false_B1", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(1).Eta()) > 0.9 && fabs(electrons.at(1).Eta()) < 1.4442)  FillHist("cf_false_B2", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    if(fabs(electrons.at(1).Eta()) > 1.556 && fabs(electrons.at(1).Eta()) < 2.5)  FillHist("cf_false_E", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_false_global_pt", 1. / electrons.at(1).Pt(), 1., 0., 0.1, 100);
    FillHist("cf_false_global_eta", electrons.at(1).Eta(), 1., -3., 3., 12);
    FillHist("which_false", 2.5, 1., 0., 5., 5);

  }
  

  return;
}// End of execute event loop



void ChargeFlip_e::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ChargeFlip_e::BeginCycle() throw( LQError ){
  
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

ChargeFlip_e::~ChargeFlip_e() {
  
  Message("In ChargeFlip_e Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ChargeFlip_e::FillCutFlow(TString cut, float weight){

  
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


void ChargeFlip_e::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void ChargeFlip_e::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ChargeFlip_eCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ChargeFlip_e::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



