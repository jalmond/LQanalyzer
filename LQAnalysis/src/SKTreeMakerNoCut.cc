// $Id: SKTreeMakerNoCut.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeMakerNoCut.h"

//Core includes
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeMakerNoCut);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
SKTreeMakerNoCut::SKTreeMakerNoCut() :  AnalyzerCore(), out_muons(0), out_electrons(0), out_jets(0), out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMakerNoCut");




}

void SKTreeMakerNoCut::ExecuteEvents()throw( LQError ){
  
  FillCutFlow("NoCut", 1);

  FillCutFlow("EventCut", 1);
  
  std::vector<TString> triggerslist;
  triggerslist.clear(); /// PassTrigger will check ALL triggers if no entries are filled


  FillCutFlow("VertexCut", 1);

 
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  eventbase->GetMuonSel()->SetPt(0.); 
  eventbase->GetMuonSel()->SetEta(5.);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree


  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(0.);
  eventbase->GetJetSel()->SetEta(5.2);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  
  //###### GenJet Selection ##########
  if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  eventbase->GetElectronSel()->SetPt(0.); 
  eventbase->GetElectronSel()->SetEta(5.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  
  FillCutFlow("DiLep", 1);

  out_event   = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();
  out_truth   = eventbase->GetTruth();
  
  return;
}// End of execute event loop
  


void SKTreeMakerNoCut::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void SKTreeMakerNoCut::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  cout << "MC CHANNEL = " << k_channel << endl;
  
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "KElectrons", "LQTree");
  DeclareVariable(out_muons, "KMuons");
  DeclareVariable(out_jets, "KJets");
  DeclareVariable(out_genjets, "KGenJets");
  DeclareVariable(out_trigger, "KTrigger");
  DeclareVariable(out_event, "KEvent");
  DeclareVariable(out_truth, "KTruth");

  //// Set triggers available in sktree
  triggerlist.clear();
  if(k_isdata){
    if(k_channel.Contains("SingleMuon")){
      AddTriggerToList("HLT_Mu5_v");
      AddTriggerToList("HLT_Mu8_v");
      AddTriggerToList("HLT_Mu12_v");
      AddTriggerToList("HLT_Mu17_v");
      AddTriggerToList("HLT_Mu24_v");
      AddTriggerToList("HLT_Mu24_v");
      AddTriggerToList("HLT_Mu40_eta2p1_v");
      AddTriggerToList("HLT_IsoMu24_eta2p1_v");
    }
    else if(k_channel.Contains("Muon")){
      AddTriggerToList("HLT_Mu40_eta2p1_v");
      AddTriggerToList("HLT_IsoMu24_eta2p1_v");
      AddTriggerToList("HLT_Mu17_TkMu8_v");
      AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFJet30_v");
      AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_v");
      AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_30_20_v");
      AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet45_35_25_v");
    }
    if(k_channel.Contains("Electron")){
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
      AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele27_WP80_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet45_35_25_v");
    }
    
    if(k_channel.Contains("EMu")){
      AddTriggerToList("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    }
  }
  else {
    AddTriggerToList("HLT_Mu5_v");
    AddTriggerToList("HLT_Mu8_v");
    AddTriggerToList("HLT_Mu12_v");
    AddTriggerToList("HLT_Mu17_v");
    AddTriggerToList("HLT_Mu24_v");
    AddTriggerToList("HLT_Mu24_v");
    AddTriggerToList("HLT_Mu40_eta2p1_v");
    AddTriggerToList("HLT_IsoMu24_eta2p1_v");
    AddTriggerToList("HLT_Mu40_eta2p1_v");
    AddTriggerToList("HLT_IsoMu24_eta2p1_v");
    AddTriggerToList("HLT_Mu17_TkMu8_v");
    AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFJet30_v");
    AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_v");
    AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_30_20_v");
    AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet45_35_25_v");
    AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
    AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
    AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    AddTriggerToList("HLT_Ele27_WP80_v");
    AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v");
    AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_v");
    AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20_v");
    AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet45_35_25_v");
    AddTriggerToList("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    AddTriggerToList("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  }



  return;
  
}

SKTreeMakerNoCut::~SKTreeMakerNoCut() {
  
  Message("In Analyzer Destructor" , INFO);

}


void SKTreeMakerNoCut::FillCutFlow(TString cut, float weight){


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



void SKTreeMakerNoCut::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


void SKTreeMakerNoCut::ClearOutputVectors() throw (LQError){
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
  out_jets.clear();
  out_genjets.clear();
  out_truth.clear();

}



