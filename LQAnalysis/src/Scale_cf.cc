// $Id: Scale_cf.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQScale_cf Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "Scale_cf.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (Scale_cf);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
Scale_cf::Scale_cf() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("Scale_cf");
  
  Message("In Scale_cf constructor", INFO);
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


void Scale_cf::InitialiseAnalysis() throw( LQError ) {
  
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

void Scale_cf::ExecuteEvents()throw( LQError ){
  
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
  TString di_electron_trig1="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
  
  vector<TString> trignames;
  //trignames.push_back(dimuon_trigmuon_trig1);
  trignames.push_back(di_electron_trig1); 
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
  //if(electrons.at(0).MotherPdgId() != 23 || electrons.at(1).MotherPdgId() != 23) return;
  snu::KParticle Z = electrons.at(0) + electrons.at(1);
  if(Z.M() > 100 || Z.M() < 80) return;
  if(electrons.at(0).Pt() < 25 || electrons.at(1).Pt() < 20) return;
  if(muons.size() != 0) return;
  
  float MET = eventbase->GetEvent().PFMET();
  if(MET > 30) return;
  
  bool trig_pass = PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  
  if(electrons.at(0).Charge() == electrons.at(1).Charge() && trig_pass){
    FillHist("M(ee)_data_SS", Z.M(), 1., 0., 200., 200);
    if(jets.size() == 1){
      FillHist("M(ee)_data_SS_1jet", Z.M(), 1., 0., 200., 200);
    }
  }  
  bool e1_cf = electrons.at(0).MCIsCF();
  bool e2_cf = electrons.at(1).MCIsCF();
  
  if(electrons.at(0).Charge() == electrons.at(1).Charge() && trig_pass && !e1_cf && !e2_cf) FillHist("M(ee)_prompt", Z.M(), 1., 0., 200., 200);
  
  if(electrons.at(0).Charge() == electrons.at(1).Charge()) return;
  
  float cf_1 = 0, cf_2 = 0;
  float p0, p1;
  float pt_inv_e1 = 1. / electrons.at(0).Pt();
  float pt_inv_e2 = 1. / electrons.at(1).Pt();
  //cf_1
  if(fabs(electrons.at(0).Eta()) < 0.9){
    if(pt_inv_e1 < 0.02){
      p0 = 0.0001261;
      p1 = -0.005951;
    }
    if(pt_inv_e1 > 0.02){
      p0 = 0.00001584;
      p1 = 0.00005337;
    }
    cf_1 = p0 + p1 * pt_inv_e1;
  }
  if(fabs(electrons.at(0).Eta()) > 0.9 && fabs(electrons.at(0).Eta()) < 1.4442){
    if(pt_inv_e1 < 0.025){
      p0 = 0.00063;
      p1 = -0.01965;
    }
    if(pt_inv_e1 > 0.025){
      p0 = 0.00003946;
      p1 = 0.00008439;
    }
    cf_1 = p0 +p1 * pt_inv_e1;
  } 
  if(fabs(electrons.at(0).Eta()) > 1.556 && fabs(electrons.at(0).Eta()) < 2.5){
    if(pt_inv_e1 < 0.02){
      p0 = 0.006827;
      p1 = -0.2189;
    }
    if(pt_inv_e1 > 0.02){
      p0 = 0.003153;
      p1 = -0.03891;
    }
    cf_1 = p0 +p1 * pt_inv_e1;
  } 
  //cf_2
  if(fabs(electrons.at(1).Eta()) < 0.9){
    if(pt_inv_e1 < 0.02){
      p0 = 0.0001261;
      p1 = -0.005951;
    }
    if(pt_inv_e1 > 0.02){
      p0 = 0.00001584;
      p1 = 0.00005337;
    }
    cf_2 = p0 +p1 * pt_inv_e1;
  }
  if(fabs(electrons.at(1).Eta()) > 0.9 && fabs(electrons.at(1).Eta()) < 1.4442){
    if(pt_inv_e1 < 0.025){
      p0 = 0.00063;
      p1 = -0.01965;
    }
    if(pt_inv_e1 > 0.025){
      p0 = 0.00003946;
      p1 = 0.00008439;
    }
    cf_2 = p0 +p1 * pt_inv_e1;
  }
  if(fabs(electrons.at(1).Eta()) > 1.556 && fabs(electrons.at(1).Eta()) < 2.5){
    if(pt_inv_e1 < 0.02){
      p0 = 0.006827;
      p1 = -0.2189;
    }
    if(pt_inv_e1 > 0.02){
      p0 = 0.003153;
      p1 = -0.03891;
    }
    cf_2 = p0 +p1 * pt_inv_e1;
  }
  
  cout << "cf_1 : " << cf_1 << ", cf_2 : " << cf_2 << endl;
  
  if(electrons.at(0).Charge() != electrons.at(1).Charge() && trig_pass){
    FillHist("M(ee)_data_CF_pred", Z.M(), cf_1 + cf_2 - cf_1 * cf_2, 0., 200., 200);
    if(jets.size() == 1){
      FillHist("M(ee)_data_CF_pred_1jet", Z.M(), cf_1 + cf_2 - cf_1 * cf_2, 0., 200., 200);

    }
  }
  return;
}// End of execute event loop



void Scale_cf::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void Scale_cf::BeginCycle() throw( LQError ){
  
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

Scale_cf::~Scale_cf() {
  
  Message("In Scale_cf Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void Scale_cf::FillCutFlow(TString cut, float weight){

  
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


void Scale_cf::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void Scale_cf::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this Scale_cfCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void Scale_cf::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



