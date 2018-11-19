
// $Id: SKTreeMakerHNDiLep.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeMakerHNDiLep.h"

//Core includes
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeMakerHNDiLep);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
SKTreeMakerHNDiLep::SKTreeMakerHNDiLep() :  AnalyzerCore(), out_muons(0), out_electrons(0),out_photons(0), out_jets(0), out_fatjets(0),out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMakerHNDiLep");
  
  
  
  
}

void SKTreeMakerHNDiLep::ExecuteEvents()throw( LQError ){
  

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

 
  bool _SiglEG =isData? k_channel.Contains("SingleElectron"):true;
  bool _SiglMu =isData? k_channel.Contains("SingleMuon")    :true;
  bool _DiMu   =isData? k_channel.Contains("DoubleMuon")    :true;
  bool _MuonEG =isData? k_channel.Contains("MuonEG")        :true;

  bool _PassRefTrig=false;
  if     (_SiglEG &&  PassTrigger("HLT_Ele27_WPTight_Gsf_v"))                             _PassRefTrig=true;
  else if(_SiglMu && (PassTrigger("HLT_IsoTkMu24_v")
                     ||PassTrigger("HLT_IsoMu24_v")))                                     _PassRefTrig=true;
  else if(_DiMu   && (PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v")
                     ||PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v")) )             _PassRefTrig=true;
  else if(_MuonEG && (PassTrigger("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v")
                     ||PassTrigger("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v")
                     ||PassTrigger("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v")) ) _PassRefTrig=true;

  if(!_PassRefTrig) throw LQError( "Remove events not passing reference trigger.", LQError::SkipEvent );
  
  
  float LeadLepPtCut = 0.;
  if     (_SiglEG) LeadLepPtCut = 27.;
  else if(_SiglMu) LeadLepPtCut = 24.;
  else if(_DiMu  ) LeadLepPtCut = 17.;
  else if(_MuonEG) LeadLepPtCut = 23.;

  if(!isData) LeadLepPtCut=17.;

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  eventbase->GetMuonSel()->SetPt(5.); 
  eventbase->GetMuonSel()->SetEta(3.);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree
  SetCorrectedMomentum(out_muons);

  Message("Skimming Muons", DEBUG);
  eventbase->GetMuonSel()->SetPt(5.);
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->SkimSelection(skim_muons, false);
  


  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(2.4);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  

  //###### GenJet Selection ##########
  //if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  std::vector<snu::KElectron> skim_electrons;
  eventbase->GetElectronSel()->SetPt(5.); 
  eventbase->GetElectronSel()->SetEta(3.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  eventbase->GetElectronSel()->SetPt(5.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SkimSelection(skim_electrons);

  int nlep = skim_electrons.size() + skim_muons.size();
    
  /// select events  with 2 leptons with pt > 15
  if(! ((nlep > 1) )) throw LQError( "Not enough leptons",  LQError::SkipEvent );
  
  bool PassLeadLepPtCut=false;
  
  if(skim_electrons.size() > 0 ) {
    if(skim_electrons.at(0).Pt() > LeadLepPtCut) PassLeadLepPtCut =true;
  }
  if(skim_muons.size() > 0){
    float mupt=skim_muons.at(0).Pt();
    if(skim_muons.at(0).RochPt() < skim_muons.at(0).Pt()) mupt=skim_muons.at(0).RochPt();
    if(skim_muons.at(0).RochPt() < 0.) mupt=skim_muons.at(0).Pt();

    if(mupt > LeadLepPtCut)  PassLeadLepPtCut=true;
  }
  if(!PassLeadLepPtCut) throw LQError( "Not passing lead pt cut",  LQError::SkipEvent );


  FillCutFlow("DiLep", 1);

  out_event   = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();
  //out_truth   = eventbase->GetTruth();
  
  return;
}// End of execute event loop



void SKTreeMakerHNDiLep::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void SKTreeMakerHNDiLep::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);

  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "KElectrons", "LQTree");
  DeclareVariable(out_photons, "KPhotons");

  DeclareVariable(out_muons, "KMuons");
  DeclareVariable(out_jets, "KJets");
  DeclareVariable(out_fatjets, "KFatJets");
  DeclareVariable(out_genjets, "KGenJets");
  DeclareVariable(out_trigger, "KTrigger");
  DeclareVariable(out_event, "KEvent");
  DeclareVariable(out_truth, "KTruth");

  //// Set triggers available in sktree
  triggerlist.clear();
  
  
  if(k_isdata){
    AddTriggerToList("HLT_IsoMu1");
    AddTriggerToList("HLT_IsoMu2");
    AddTriggerToList("HLT_IsoTkMu1");
    AddTriggerToList("HLT_IsoTkMu2");
    AddTriggerToList("HLT_Mu8");
    AddTriggerToList("HLT_Mu1");
    AddTriggerToList("HLT_Mu2");
    AddTriggerToList("HLT_Mu3");
    AddTriggerToList("HLT_Mu5");
    AddTriggerToList("HLT_DoubleEle2");
    AddTriggerToList("HLT_DoubleEle8");
    AddTriggerToList("HLT_DoubleEle3");
    AddTriggerToList("HLT_Ele8");
    AddTriggerToList("HLT_Ele1");//// 12-16-18                                                                                                                            
    AddTriggerToList("HLT_Ele2");
    AddTriggerToList("HLT_Ele3");
    AddTriggerToList("HLT_DoublePhoton");
    AddTriggerToList("HLT_Photon36_R9Id90");
    AddTriggerToList("HLT_Photon50_R9Id90");
    AddTriggerToList("HLT_Photon90_R9Id90");
    AddTriggerToList("HLT_TripleMu");
    AddTriggerToList("HLT_DiMu");

  }
  else {
    AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
    AddTriggerToList("HLT_IsoMu1");
    AddTriggerToList("HLT_IsoMu2");
    AddTriggerToList("HLT_IsoTkMu1");
    AddTriggerToList("HLT_IsoTkMu2");
    AddTriggerToList("HLT_Mu8");
    AddTriggerToList("HLT_Mu1");
    AddTriggerToList("HLT_Mu2");
    AddTriggerToList("HLT_Mu3");
    AddTriggerToList("HLT_Mu5");
    AddTriggerToList("HLT_DoubleEle2");
    AddTriggerToList("HLT_DoubleEle8");
    AddTriggerToList("HLT_DoubleEle3");
    AddTriggerToList("HLT_Ele8");
    AddTriggerToList("HLT_Ele1");//// 12-16-18                                                                                                                            
    AddTriggerToList("HLT_Ele2");
    AddTriggerToList("HLT_Ele3");
    AddTriggerToList("HLT_DoublePhoton");
    AddTriggerToList("HLT_Photon36_R9Id90");
    AddTriggerToList("HLT_Photon50_R9Id90");
    AddTriggerToList("HLT_Photon90_R9Id90");
    AddTriggerToList("HLT_TripleMu");
    AddTriggerToList("HLT_DiMu");

  }

  return;
  
}

SKTreeMakerHNDiLep::~SKTreeMakerHNDiLep() {
  
  Message("In Analyzer Destructor" , INFO);

}


void SKTreeMakerHNDiLep::FillCutFlow(TString cut, float weight){


  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 4,0.,4.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"DiLep");
  }
}



void SKTreeMakerHNDiLep::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


void SKTreeMakerHNDiLep::ClearOutputVectors() throw (LQError){
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
  out_photons.clear();
  out_jets.clear();
  out_fatjets.clear();
  out_genjets.clear();
  out_truth.clear();

}



