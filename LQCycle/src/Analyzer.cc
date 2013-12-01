// $Id: Analyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "Analyzer.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (Analyzer);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
Analyzer::Analyzer() :  AnalyzerCore(), out_muons(0), out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("Analyzer");

  Message("In Analyzer constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void Analyzer::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();
  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

  Message("Making clever hists for Z ->ll test code", INFO);
  
  //// Initialise Plotting class functions
  /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
  MakeCleverHistograms(muhist, "Zmuons");
  MakeCleverHistograms(elhist, "Zelectrons");
    
  return;
}


void Analyzer::ExecuteEvents()throw( LQError ){
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts
  
  /// Trigger List (specific to muons channel)
  std::vector<TString> triggerslist;
  //triggerslist.push_back("HLT_Mu17_TkMu8_v");
  //if(!PassTrigger(triggerslist, prescale)) return;
  /// Correct MC for pileup
  if (MC_pu&&!k_isdata)  weight = weight*reweightPU->GetWeight(int(PileUpInteractionsTrue->at(0)))* MCweight;
  numberVertices = eventbase->GetBaseEvent().nVertices();

  if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
 
 
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  std::vector<snu::KMuon> muonColl;
  eventbase->GetMuonSel()->SetPt(20); 
  eventbase->GetMuonSel()->SetEta(2.4);
  //eventbase->GetMuonSel().SetRelIso(1000.);
  //eventbase->GetMuonSel().SetChiNdof(1000); 
  //eventbase->GetMuonSel().SetBSdxy(0.01);
  //eventbase->GetMuonSel().SetBSdz(0.10);
  //eventbase->GetMuonSel().SetDeposits(40.0,60.00);    
  eventbase->GetMuonSel()->Selection(out_muons);
    
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  
  std::vector<snu::KElectron> electronColl;
  eventbase->GetElectronSel()->SetPt(20); 
  eventbase->GetElectronSel()->SetEta(2.5); 
  eventbase->GetElectronSel()->SetRelIso(0.15); 
  eventbase->GetElectronSel()->SetBSdxy(0.02); 
  eventbase->GetElectronSel()->SetBSdz(0.10);
  eventbase->GetElectronSel()->Selection(out_electrons); 
  eventbase->GetElectronSel()->Selection(electronColl); 

  ///// SOME STANDARD PLOTS /////
  ////  Z-> mumu            //////
  

  if (muonColl.size() == 2) {      
    snu::KParticle Z = muonColl.at(0) + muonColl.at(1);
    if(muonColl.at(0).Charge() != muonColl.at(1).Charge()){      
      FillHist("zpeak_mumu", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(muhist, "Zmuons", muonColl, weight);
    } 
  }
  

  ///// SOME STANDARD PLOTS /////
  ////  Z-> ee              //////
  if (electronColl.size() == 2) {      
    snu::KParticle Z = electronColl.at(0) + electronColl.at(1);
    if(electronColl.at(0).Charge() != electronColl.at(1).Charge()){      

      FillHist("zpeak_ee", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(elhist, "Zelectrons", electronColl, eventbase->GetBaseEvent().JetRho(), weight);
    } 
  }
  
  return;
}// End of execute event loop
  


void Analyzer::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  //
  // This function opens output root file and saves output trees
  //

  SaveOutputTrees(m_outputFile);
  
  m_logger<< INFO << "Opening output root file " << m_outputFile->GetName() << LQLogger::endmsg;
  //
  // All histograms are output into m_outputFile
  //
  WriteHists();/// writes all outputs in maphist
  WriteCLHists(); /// writes all hists set with MakeCleverHistograms       

}


void Analyzer::BeginCycle(TString output_file_name) throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  //
  // To clear output variables if running multiple cycles
  //
  ClearOutputVectors();

  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());

  //
  // Open the out put file if any output Tree variables are  specified
  //
  MakeOutPutFile(output_file_name); 
  /// can specify output tree by chaging line to  MakeOutPutFile(output_file_name, treename); This will change default name for DeclareVariable()
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

Analyzer::~Analyzer() {
  
  Message("In Analyzer Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}



void Analyzer::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);
  ClearOutputVectors();

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void Analyzer::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this AnalyzerCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void Analyzer::ClearOutputVectors(){
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



