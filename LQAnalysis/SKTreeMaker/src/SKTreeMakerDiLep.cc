
// $Id: SKTreeMakerDiLep.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeMakerDiLep.h"

//Core includes
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeMakerDiLep);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
SKTreeMakerDiLep::SKTreeMakerDiLep() :  AnalyzerCore(), out_muons(0), out_electrons(0),out_photons(0), out_jets(0), out_fatjets(0),out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMakerDiLep");
  
  
  
  
}

void SKTreeMakerDiLep::ExecuteEvents()throw( LQError ){
  

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  bool _singleEG =(k_channel.Contains("SingleElectron"));
  bool _singleMuon =(k_channel.Contains("SingleMuon"));
  TString analysis_trigger_eg="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
  TString analysis_trigger_muon="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v";
  TString analysis_trigger_tkmuon="HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v";

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  /// Apart from eta/pt muons are required to have a global OR tracker track    && be PF
  eventbase->GetMuonSel()->SetPt(5.); 
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree
  SetCorrectedMomentum(out_muons);

  Message("Skimming Muons", DEBUG);
  /// Selection for event skim
  /// Apart from eta/pt muons are required to have a global OR tracker track && be PF
  eventbase->GetMuonSel()->SetPt(5.);
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->SkimSelection(skim_muons, false);
  
  //####### PHOTONS
  //  std::vector<snu::KElectron> skim_photons;
  //eventbase->GetPhotonSel()->SetPt(20);
  //eventbase->GetPhotonSel()->SetEta(3.);
  //eventbase->GetPhotonSel()->BasicSelection(out_photons);


  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(10);
  eventbase->GetJetSel()->SetEta(5.);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  
  //###### JET SELECTION  ################                                                                                                                                      
  Message("Selecting fatjets", DEBUG);
  eventbase->GetFatJetSel()->SetPt(15);
  eventbase->GetFatJetSel()->SetEta(5.);
  eventbase->GetFatJetSel()->BasicSelection(out_fatjets);


  //###### GenJet Selection ##########
  //if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  std::vector<snu::KElectron> skim_electrons;
  eventbase->GetElectronSel()->SetPt(5.); 
  eventbase->GetElectronSel()->SetEta(3.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  eventbase->GetElectronSel()->SetPt(8.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SkimSelection(skim_electrons);

  int nlep = skim_electrons.size() + skim_muons.size();
    
  /// select events  with 2 leptons with pt > 15
  if(! ((nlep > 1) )) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
  
  bool pass15gev=false;
  
  if(skim_electrons.size() > 0 ) {
    if(skim_electrons.at(0).Pt() > 14.) pass15gev= true;
  }
  if(skim_muons.size() > 0){
    float mupt=skim_muons.at(0).Pt();
    if(skim_muons.at(0).RochPt() < skim_muons.at(0).Pt()) mupt=skim_muons.at(0).RochPt();
    if(skim_muons.at(0).RochPt() < 0.) mupt=skim_muons.at(0).Pt();

    if(mupt > 14.)  pass15gev= true;
  }
  if(!pass15gev) throw LQError( "Not Lepton Event",  LQError::SkipEvent );


  FillCutFlow("DiLep", 1);

  out_event   = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();
  //out_truth   = eventbase->GetTruth();
  
  return;
}// End of execute event loop



void SKTreeMakerDiLep::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void SKTreeMakerDiLep::BeginCycle() throw( LQError ){
  
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
    AddTriggerToList("HLT_TkMu5");
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
    AddTriggerToList("HLT_TkMu5");
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

SKTreeMakerDiLep::~SKTreeMakerDiLep() {
  
  Message("In Analyzer Destructor" , INFO);

}


void SKTreeMakerDiLep::FillCutFlow(TString cut, float weight){


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



void SKTreeMakerDiLep::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


void SKTreeMakerDiLep::ClearOutputVectors() throw (LQError){
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



