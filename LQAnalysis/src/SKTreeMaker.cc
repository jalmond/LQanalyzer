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
SKTreeMaker::SKTreeMaker() :  AnalyzerCore(), out_muons(0), out_electrons(0), out_jets(0), out_genjets(0), out_truth(0), nevents(0),pass_eventcut(0), pass_vertexcut(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMaker");




}

void SKTreeMaker::ExecuteEvents()throw( LQError ){
  
  FillCutFlow("NoCut", 1);

  if(!PassBasicEventCuts()){
    m_logger << DEBUG << "Fail MET filter cuts" << LQLogger::endmsg;
    throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }  
  FillCutFlow("EventCut", 1);
  
  std::vector<TString> triggerslist;
  triggerslist.clear(); /// PassTrigger will check ALL triggers if no entries are filled

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()){
    m_logger <<  DEBUG << "Event FAILS HasGoodPrimaryVertex " << LQLogger::endmsg;
    throw LQError( "Has no PV",  LQError::SkipEvent );
  }
  FillCutFlow("VertexCut", 1);

 
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  //if(eventbase->GetEvent().EventNumber() == 28681993) cout << "JOHN : " << eventbase->GetEvent().LumiSection() << endl;

  //######   MUON SELECTION ###############
  Message("Selecting Muons", DEBUG);
  std::vector<snu::KMuon> skim_muons;
  /// Apart from eta/pt muons are required to have a global OR tracker track    && be PF
  eventbase->GetMuonSel()->SetPt(10); 
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->BasicSelection(out_muons, false); /// Muons For SKTree

  Message("Skimming Muons", DEBUG);
  /// Selection for event skim
  /// Apart from eta/pt muons are required to have a global OR tracker track && be PF
  eventbase->GetMuonSel()->SetPt(15);
  eventbase->GetMuonSel()->SetEta(2.5);
  eventbase->GetMuonSel()->SkimSelection(skim_muons, false);

  //###### JET SELECTION  ################
  Message("Selecting jets", DEBUG);
  eventbase->GetJetSel()->SetPt(10);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->BasicSelection(out_jets);
  
  //###### GenJet Selection ##########
  if(!k_isdata) eventbase->GetGenJetSel()->BasicSelection(out_genjets);
  
  //###### Electron Selection ########
  Message("Selecting electrons", DEBUG);
  std::vector<snu::KElectron> skim_electrons;
  eventbase->GetElectronSel()->SetPt(10); 
  eventbase->GetElectronSel()->SetEta(5.); 
  eventbase->GetElectronSel()->BasicSelection(out_electrons); 
  eventbase->GetElectronSel()->SetPt(10);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SkimSelection(skim_electrons);
  
  int nlep = skim_electrons.size() + skim_muons.size();
  bool pass15gevlep = false;
  if(skim_electrons.size() > 0){
    if(skim_electrons.at(0).Pt()> 15 ) pass15gevlep = true;
  }
  if(skim_muons.size() > 0){
    if(skim_muons.at(0).Pt()> 15 ) pass15gevlep = true;
  }
  
  /// select events with either 1 lepton with pt > 15  gev or 2 leptons with pt > 15
  if(! ((nlep > 1) || ( nlep ==1 && pass15gevlep))) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    

  FillCutFlow("DiLep", 1);

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
    if(k_channel.Contains("singleMuon")){
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
    cout << "k_channel = " << k_channel << endl;
    if(k_channel.Contains("Electron")){
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
      AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
      AddTriggerToList("HLT_Ele27_WP80_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20_v");
      AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet45_35_25_v");
      AddTriggerToList("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v");
      AddTriggerToList("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v");
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
    AddTriggerToList("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v");
    AddTriggerToList("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v");
    AddTriggerToList("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    AddTriggerToList("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
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
  out_jets.clear();
  out_genjets.clear();
  out_truth.clear();

}



