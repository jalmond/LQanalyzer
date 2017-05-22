/***************************************************************************
 * @Project: LQFakeRateMC Frame - ROOT-based analysis framework for Korea SNU
OB * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/


/// Local includes
#include "FakeRateMC.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (FakeRateMC);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
FakeRateMC::FakeRateMC() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("FakeRateMC");

  Message("In FakeRateMC constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

}


void FakeRateMC::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

  return;
}


void FakeRateMC::ExecuteEvents()throw( LQError ){
    
  //// Initial event cuts
  /// MET FIleters 
  if(!PassMETFilter()) return;     
  
  /// Require good promary vertex 
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex  
  numberVertices = eventbase->GetEvent().nVertices();   
  
  ExecuteEventsMuon();
}


void FakeRateMC::ExecuteEventsMuon(){
  
  //  | ID              |  ptmin  | |etamax| |  isomin04   | isomax04 | IsTight(POG)  | IsMedium(POG)  | IsLoose(POG)   | |dxymax|  |  |dzmax|  | chi2max | |dxysigmin|  |  |dxysigmax|  | ApplyRoch |

  // | MUON_HN_FAKELOOSEST                 | 5.     | 2.5      |   0.        | 0.60     | true          | false          |  false         | 999.      | 0.5       | 50.     | 999.    | 999.         |  true      |


  std::vector<snu::KMuon> loosemuons = GetMuons("MUON_HN_LOOSE",true);
  
  for(unsigned int imu=0; imu < loosemuons.size(); imu++){
    FillHist("MuonType",loosemuons[imu].GetType(),weight, 0., 35., 35);
    if(PassID(loosemuons[imu], "MUON_HN_TIGHT"))     FillHist("MuonType_tight",loosemuons[imu].GetType(),weight, 0., 35., 35);

  }

}

void FakeRateMC::ExecuteEventsElectron(){

  
  std::vector<snu::KElectron> looseelectrons = GetElectrons(true,true,"ELECTRON_HN_LOOSE");

 for(unsigned int iel=0; iel < looseelectrons.size(); iel++){
   FillHist("ElectronType",looseelectrons[iel].GetType(),weight, 0., 35., 35);
   if(PassID(looseelectrons[iel], "ELECTRON_HN_TIGHT"))     FillHist("ElectronType_tight",looseelectrons[iel].GetType(),weight, 0., 35., 35);

 }

}



void FakeRateMC::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger<< INFO << "Number of events that pass 1 7GeV trigger = " << n_17_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV + jet trigger = " << n_17_jet_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV || jet trigger = " << n_17_17_jet_pass  << LQLogger::endmsg;

}

void FakeRateMC::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //DeclareVariable(out_muons, "Signal_Muons");

  n_17_jet_pass=0;
  n_17_17_jet_pass=0;
  n_17_pass=0;

  
  return;
  
}

FakeRateMC::~FakeRateMC() {
  
  Message("In FakeRateMC Destructor" , INFO);
  
}



void FakeRateMC::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void FakeRateMC::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this FakeRateMCCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void FakeRateMC::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}


