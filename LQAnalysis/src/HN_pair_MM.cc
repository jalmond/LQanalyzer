// $Id: HN_pair_MM.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHN_pair_MM Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HN_pair_MM.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HN_pair_MM);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
HN_pair_MM::HN_pair_MM() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("HN_pair_MM");
  
  Message("In HN_pair_MM constructor", INFO);
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


void HN_pair_MM::InitialiseAnalysis() throw( LQError ) {
  
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

void HN_pair_MM::ExecuteEvents()throw( LQError ){
  
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

  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);
  
  cout << "truth " << truthColl.size() << endl;

  bool trig_pass = PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float current_weight(1.);
  float temp_pileup_reweight(1.);
  float pileup_reweight(1.);
  
  if(!isData){
    CorrectMuonMomentum(muons);
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
  
  float MET = eventbase->GetEvent().PFMET();
  bool prompt_match = false;
  int n_bjet = NBJet(jets);
  
  if(trig_pass) FillHist("signal_eff", 2., 1., 0., 10., 10); 
  
  FillCLHist(hnpairmm,"basic_PU", eventbase->GetEvent(), muons, electrons, jets, current_weight * pileup_reweight, n_bjet);
  FillCLHist(hnpairmm,"basic_tempPU", eventbase->GetEvent(), muons, electrons,jets, current_weight * temp_pileup_reweight, n_bjet);
  
  if(jets.size() > 3 && MET > 75){
    FillCLHist(hnpairmm,"CR_1_PU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
    FillCLHist(hnpairmm,"CR_1_tempPU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
  }
  if(jets.size() > 2 && muons.size() > 0){
    if(muons.at(0).Pt() < 50){
      FillCLHist(hnpairmm,"CR_2_PU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
      FillCLHist(hnpairmm,"CR_2_tempPU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
    }
  }
  if(muons.size() > 0){
    if(muons.at(0).Pt() < 50){
      FillCLHist(hnpairmm,"CR_3_PU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
      FillCLHist(hnpairmm,"CR_3_tempPU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
    }
  }
  if(muons.size() > 1){
    snu::KParticle Z = muons.at(0) + muons.at(1);
    if(Z.M() > 80 && Z.M() < 100){
      FillCLHist(hnpairmm,"CR_4_PU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
      FillCLHist(hnpairmm,"CR_4_tempPU", eventbase->GetEvent(), muons, electrons,jets, current_weight * pileup_reweight, n_bjet);
    }
  }

  

  return;
}// End of execute event loop



void HN_pair_MM::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void HN_pair_MM::BeginCycle() throw( LQError ){
  
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

HN_pair_MM::~HN_pair_MM() {
  
  Message("In HN_pair_MM Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void HN_pair_MM::FillCutFlow(TString cut, float weight){

  
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


void HN_pair_MM::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void HN_pair_MM::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HN_pair_MMCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HN_pair_MM::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



