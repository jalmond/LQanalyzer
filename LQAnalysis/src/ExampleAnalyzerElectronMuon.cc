// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzerDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzerElectronMuon.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzerElectronMuon);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ExampleAnalyzerElectronMuon::ExampleAnalyzerElectronMuon() :  AnalyzerCore() {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzerElectronMuon");

  Message("In ExampleAnalyzerElectronMuon constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void ExampleAnalyzerElectronMuon::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   MakeCleverHistograms(sighist, "ElectronMuonEvents");

   
   return;
}


void ExampleAnalyzerElectronMuon::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  
  /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
  /// The string cut must match a bin label in FillCutFlow function
  FillCutFlow("NoCut", weight);
  
  ///// Apply some general cuts on event to clean MET
  /// Taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
  /// These are applied in AnalyzerCore::PassBasicEventCuts
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  /// Trigger List 
  std::vector<TString> triggerslist;
  /// This is the analysis electron trigger 
  /// No Scale Factors are yet applied to correct MC
  triggerslist.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoV");
  //if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  FillCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
    
  FillCutFlow("VertexCut", weight);
  
  /// Use the number of vertices in the event to check effect of pileup reweighting
  numberVertices = eventbase->GetEvent().nVertices();   
    /// Correct MC for pileup   
  
  float pileup_reweight (1.);
  if (MC_pu&&!k_isdata) {
    pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
    
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// We want to select events with 2 medium electrons (we will also remove events with a looser third muon to show how it is done)
  /// We will use 4 different object collections
  /// 1) Tight Electrons  ||  eventbase->GetElectronSel()->HNTightElectronSelection
  /// 2) Tight Muons      || eventbase->GetMuonSel()->HNTightMuonSelection
  /// 3) Jets(with lepton veto)
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) TightElectrons                                                                                                                                                     
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);
  
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);
  
  std::vector<snu::KJet> jetColl_lepveto;
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto, muonTightColl, electronTightColl);
  
  
  if(electronTightColl.size()==1 && muonTightColl.size()==1){
    
    /// For MC reweight event to correct for ID efficiency in MC/DATA
    float id_scalefactor(1.);
    if(!isData){
      id_scalefactor *=  ElectronScaleFactor(electronTightColl.at(0).Eta(), electronTightColl.at(0).Pt());
    }
    
    // reconstruct dilepton system
    snu::KParticle Z = electronTightColl.at(0) + muonTightColl.at(0);
    
    if(electronTightColl.at(0).Charge() != muonTightColl.at(0).Charge()){      
      
      /// Fill Standardset of cuts forall objects with pileup reweighting applied
      FillCLHist(sighist, "ElectronMuonEvents", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));
      
    }
  }// OS 
    
  return;
}// End of execute event loop
  


void ExampleAnalyzerElectronMuon::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ExampleAnalyzerElectronMuon::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree


  
  return;
  
}

ExampleAnalyzerElectronMuon::~ExampleAnalyzerElectronMuon() {
  
  Message("In ExampleAnalyzerElectronMuon Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzerElectronMuon::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 5,0.,5.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"DiEl_tight");
   
    
  }
}


void ExampleAnalyzerElectronMuon::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ExampleAnalyzerElectronMuon::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerElectronMuonCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzerElectronMuon::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //

}



