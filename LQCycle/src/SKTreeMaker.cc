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
SKTreeMaker::SKTreeMaker() :  AnalyzerCore(), out_muons(0), out_electrons(0), out_jets(0){

  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeMaker");

}

void SKTreeMaker::ExecuteEvents()throw( LQError ){
  
  if(!PassBasicEventCuts()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  std::vector<TString> triggerslist;
  triggerslist.clear(); /// PassTrigger will check ALL triggers if no entries are filled
  if(!PassTrigger(triggerslist, prescale)) throw LQError( "Fails trigger",  LQError::SkipEvent );
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Has no PV",  LQError::SkipEvent );
 
 
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  eventbase->GetMuonSel()->SetPt(15); 
  eventbase->GetMuonSel()->SetEta(2.4);
  eventbase->GetMuonSel()->Selection(out_muons);
    
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(out_jets);
  
  std::vector<snu::KElectron> electronColl;
  eventbase->GetElectronSel()->SetPt(15); 
  eventbase->GetElectronSel()->SetEta(2.5); 
  eventbase->GetElectronSel()->Selection(out_electrons); 

  out_event = eventbase->GetEvent();
  out_trigger = eventbase->GetTrigger();

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
  DeclareVariable(out_trigger, "KTrigger");
  DeclareVariable(out_event, "KEvent");

  
  return;
  
}

SKTreeMaker::~SKTreeMaker() {
  
  Message("In Analyzer Destructor" , INFO);
  
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

}



