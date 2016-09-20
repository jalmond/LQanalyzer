
// $Id: SKTreeMakerTriLep.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeMakerTriLep.h"

//Core includes
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeMakerTriLep);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
SKTreeMakerTriLep::SKTreeMakerTriLep() :  AnalyzerCore(), out_muons(0), out_electrons(0),out_photons(0), out_jets(0), out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMakerTriLep");
  
  
  
  
}

void SKTreeMakerTriLep::ExecuteEvents()throw( LQError ){
  


  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  /// Apart from eta/pt muons are required to have a global OR tracker track    && be PF
  eventbase->GetMuonSel()->SetPt(8.); 
  eventbase->GetMuonSel()->SetEta(3.);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree

  Message("Skimming Muons", DEBUG);
  /// Selection for event skim
  /// Apart from eta/pt muons are required to have a global OR tracker track && be PF
  eventbase->GetMuonSel()->SetPt(8.);
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->SkimSelection(skim_muons, false);

  //####### PHOTONS
  //  std::vector<snu::KElectron> skim_photons;
  //eventbase->GetPhotonSel()->SetPt(20);
  //eventbase->GetPhotonSel()->SetEta(3.);
  //eventbase->GetPhotonSel()->BasicSelection(out_photons);


  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(5.);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  
  //###### GenJet Selection ##########
  //if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  std::vector<snu::KElectron> skim_electrons;
  eventbase->GetElectronSel()->SetPt(8.); 
  eventbase->GetElectronSel()->SetEta(5.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  eventbase->GetElectronSel()->SetPt(8.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SkimSelection(skim_electrons);
  
  int nlep = skim_electrons.size() + skim_muons.size();
    
  /// select events  with 2 leptons with pt > 15
  
  if(nlep == 2){
    if(skim_electrons.size() == 2){
      if(skim_electrons.at(0).Charge() == skim_electrons.at(1).Charge()) nlep = 3;
    }
    if(skim_muons.size() == 2){
      if(skim_muons.at(0).Charge() == skim_muons.at(1).Charge()) nlep = 3;
    }
  }
  if(! ((nlep > 2) )) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
  
  bool pass15gev=false;
  
  if(skim_electrons.size() >0 ) {
    if(skim_electrons.at(0).Pt() > 12.) pass15gev= true;
  }
  if(skim_muons.size() > 0){
    if(skim_muons.at(0).Pt() > 12.)  pass15gev= true;
  }
  if(!pass15gev) throw LQError( "Not Lepton Event",  LQError::SkipEvent );


  FillCutFlow("TriLep", 1);

  out_event   = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();
  //out_truth   = eventbase->GetTruth();
  
  return;
}// End of execute event loop



void SKTreeMakerTriLep::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void SKTreeMakerTriLep::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);

  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "KElectrons", "LQTree");
  DeclareVariable(out_photons, "KPhotons");

  DeclareVariable(out_muons, "KMuons");
  DeclareVariable(out_jets, "KJets");
  DeclareVariable(out_genjets, "KGenJets");
  DeclareVariable(out_trigger, "KTrigger");
  DeclareVariable(out_event, "KEvent");
  DeclareVariable(out_truth, "KTruth");

  //// Set triggers available in sktree
  triggerlist.clear();
  
  
  if(k_isdata){
    if(k_channel.Contains("DoubleMuon")){
      AddTriggerToList("HLT_IsoMu");
      AddTriggerToList("HLT_Mu");
      AddTriggerToList("HLT_TkMu");
      AddTriggerToList("HLT_TripleMu");
      AddTriggerToList("HLT_DiMu");


    }
    if(k_channel.Contains("SingleMuon")){
      AddTriggerToList("HLT_IsoMu");
      AddTriggerToList("HLT_Mu");
      AddTriggerToList("HLT_TkMu");
      AddTriggerToList("HLT_TripleMu");
      AddTriggerToList("HLT_DiMu");


    }
    if(k_channel.Contains("SinglePhoton")){
      AddTriggerToList("HLT_Photon");
    }
    cout << "k_channel = " << k_channel << endl;
    if(k_channel.Contains("DoubleEG")){
      AddTriggerToList("HLT_DoubleEle");
      AddTriggerToList("HLT_Ele");
      AddTriggerToList("HLT_DoublePhoton");
    }
    
    if(k_channel.Contains("MuonEG")){
      AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
      AddTriggerToList("HLT_Ele16_Ele12");
      AddTriggerToList("HLT_Mu8_DiEle12");
    }
  }
  else {
    AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
    AddTriggerToList("HLT_DoubleEle");
    AddTriggerToList("HLT_DoublePhoton");
    AddTriggerToList("HLT_Ele17_Ele12_CaloIdL");
    AddTriggerToList("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    AddTriggerToList("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v");
    AddTriggerToList("HLT_Mu20_Mu10_SameSign_DZ");
    AddTriggerToList("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL");
    AddTriggerToList("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL");
    AddTriggerToList("HLT_Mu17_Mu8_SameSign_DZ");
    AddTriggerToList("HLT_Ele23_WpLoose");
    AddTriggerToList("HLT_TripleMu");
    AddTriggerToList("HLT_DiMu");
    AddTriggerToList("HLT_Ele16_Ele12");
    AddTriggerToList("HLT_Mu8_DiEle12");
  }

  
  
    

  return;
  
}

SKTreeMakerTriLep::~SKTreeMakerTriLep() {
  
  Message("In Analyzer Destructor" , INFO);

}


void SKTreeMakerTriLep::FillCutFlow(TString cut, float weight){


  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 4,0.,4.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"TriLep");
  }
}



void SKTreeMakerTriLep::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


void SKTreeMakerTriLep::ClearOutputVectors() throw (LQError){
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
  out_photons.clear();
  out_jets.clear();
  out_genjets.clear();
  out_truth.clear();

}



