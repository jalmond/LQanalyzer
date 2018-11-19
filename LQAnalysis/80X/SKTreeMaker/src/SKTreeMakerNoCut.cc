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
SKTreeMakerNoCut::SKTreeMakerNoCut() :  AnalyzerCore(), out_muons(0), out_electrons(0),  out_photons(0),out_jets(0),out_fatjets(0), out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMakerNoCut");




}

void SKTreeMakerNoCut::ExecuteEvents()throw( LQError ){

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  /// Apart from eta/pt muons are required to have a global OR tracker track    && be PF
  eventbase->GetMuonSel()->SetPt(0.); 
  eventbase->GetMuonSel()->SetEta(5.);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree
  SetCorrectedMomentum(out_muons);


  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetPt(0.);
  eventbase->GetJetSel()->SetEta(5.2);
  eventbase->GetJetSel()->BasicSelection(out_jets);


  //###### FATJET SELECTION  ################                                                                                                                                       
  Message("Selecting fat jets", DEBUG);
  eventbase->GetFatJetSel()->SetPt(0);
  eventbase->GetFatJetSel()->SetEta(5.2);
  eventbase->GetFatJetSel()->BasicSelection(out_fatjets);


  //###### GenJet Selection ##########
  if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);

  eventbase->GetElectronSel()->SetPt(0.); 
  eventbase->GetElectronSel()->SetEta(5.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 

  eventbase->GetPhotonSel()->SetPt(10);
  eventbase->GetPhotonSel()->SetEta(3.);
  eventbase->GetPhotonSel()->BasicSelection(out_photons);


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
    //AddTriggerToList("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
    AddTriggerToList("HLT_Mu30_Ele30_CaloIdL_GsfTrkIdVL");
    AddTriggerToList("HLT_IsoMu1");
    AddTriggerToList("HLT_IsoMu2");
    AddTriggerToList("HLT_IsoTkMu1");
    AddTriggerToList("HLT_IsoTkMu2");
    AddTriggerToList("HLT_Mu8");
    AddTriggerToList("HLT_Mu1");
    AddTriggerToList("HLT_Mu2");
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
  out_photons.clear();
  out_jets.clear();
  out_fatjets.clear();
  out_genjets.clear();
  out_truth.clear();

}



