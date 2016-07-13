// $Id: SKTreeMaker.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeMaker.h"

//Core includes
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeMaker);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
SKTreeMaker::SKTreeMaker() :  AnalyzerCore(), out_muons(0), out_electrons(0),  out_photons(0),out_jets(0), out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMaker");




}

void SKTreeMaker::ExecuteEvents()throw( LQError ){

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  //if(isData&& (! eventbase->GetEvent().LumiMask(lumimask))) throw LQError( "Not Lepton Event",  LQError::SkipEvent );

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

  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(5.);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  
  //###### GenJet Selection ##########
  if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  std::vector<snu::KElectron> skim_electrons;
  eventbase->GetElectronSel()->SetPt(8.); 
  eventbase->GetElectronSel()->SetEta(3.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  eventbase->GetElectronSel()->SetPt(8.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SkimSelection(skim_electrons);
  
  
  std::vector<snu::KElectron> skim_photons;
  eventbase->GetPhotonSel()->SetPt(15);
  eventbase->GetPhotonSel()->SetEta(3.);
  eventbase->GetPhotonSel()->BasicSelection(out_photons);

  int nlep = skim_electrons.size() + skim_muons.size();
  bool pass15gevlep = false;
  if(skim_electrons.size() > 0){
    if(skim_electrons.at(0).Pt()> 10. ) pass15gevlep = true;
  }
  if(skim_muons.size() > 0){
    if(skim_muons.at(0).Pt()> 10. ) pass15gevlep = true;
  }
  /// select events with either 1 lepton with pt > 15  gev or 2 leptons with pt > 15
  if(! ((nlep > 1) || ( nlep ==1 && pass15gevlep))) {
    throw LQError( "Not Lepton Event",  LQError::SkipEvent );
  }

  out_event   = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();

  
  out_truth   = eventbase->GetTruth();

   return;
}// End of execute event loop
  


void SKTreeMaker::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void SKTreeMaker::BeginCycle() throw( LQError ){
  
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
    cout << " k_channel = " << k_channel << endl;

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
    if(k_channel.Contains("SingleElectron")){
      AddTriggerToList("HLT_Ele");
    }
    if(k_channel.Contains("MuonEG")){
      AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
      AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
      AddTriggerToList("HLT_Mu8_DiEle12");
      AddTriggerToList("HLT_Ele16_Ele12");
    }
  }
  else {
    AddTriggerToList("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
    AddTriggerToList("HLT_IsoMu17");
    AddTriggerToList("HLT_IsoMu18");
    AddTriggerToList("HLT_IsoMu20");
    AddTriggerToList("HLT_IsoMu22");
    AddTriggerToList("HLT_IsoMu27_v");
    AddTriggerToList("HLT_Mu8");
    AddTriggerToList("HLT_Mu17");
    AddTriggerToList("HLT_Mu20");
    AddTriggerToList("HLT_DoubleEle24");
    AddTriggerToList("HLT_DoubleEle8");
    AddTriggerToList("HLT_DoubleEle33");
    AddTriggerToList("HLT_Ele8");
    AddTriggerToList("HLT_Ele12");
    AddTriggerToList("HLT_Ele17");
    AddTriggerToList("HLT_Ele18");
    AddTriggerToList("HLT_Ele23");
    AddTriggerToList("HLT_Ele33");
    AddTriggerToList("HLT_Ele32_eta2p1");
    AddTriggerToList("HLT_Ele27_eta2p1");
    AddTriggerToList("HLT_Ele22_eta2p1");
    AddTriggerToList("HLT_DoublePhoton");
    AddTriggerToList("HLT_Photon36_R9Id90");
    AddTriggerToList("HLT_Photon50_R9Id90");
    AddTriggerToList("HLT_Photon90_R9Id90");
    AddTriggerToList("HLT_TripleMu");
    AddTriggerToList("HLT_DiMu");

  }

  
  return;
}

SKTreeMaker::~SKTreeMaker() {
  
  Message("In Analyzer Destructor" , INFO);

}


void SKTreeMaker::FillCutFlow(TString cut, float weight){


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



void SKTreeMaker::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


void SKTreeMaker::ClearOutputVectors() throw (LQError){
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



