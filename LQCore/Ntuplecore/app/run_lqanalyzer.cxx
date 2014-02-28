// STL include(s):
#include <string>
#include <iostream>
#include <fstream>

// ROOT include(s):
#include <TROOT.h>

//Local
#include "LQController.h"
#include "LQError.h"
#include "LQLogger.h"


// Global logging object
static LQLogger g_logger( "run_lqanalyzer" );

// Declaration of function printing the usage of the executable
void usage( char** argv );

int main( int argc, char** argv ) {
  
  std::string filename ="";
  if( (argc == 2 && std::string( argv[ 1 ] ) == "-h" ) ) {
    usage( argv );
    return 1;
  }
  if( (argc == 1)){
    
  }
  
  filename = "/var/tmp/jalmond/TestHNMuMu100.txt";
  gROOT->Reset();
  
  g_logger << VERBOSE << "Setting up job" << LQLogger::endmsg;

  LQController analysis; 
  analysis.SetJobName("Ztoll_ExampleCycle");
  analysis.AddLibraries("libSKTree.so");
  analysis.AddLibraries("libcore.so");
  analysis.AddLibraries("libAnalysisCore.so");
  analysis.AddLibraries("libSelection.so");
  analysis.AddLibraries("libPlotting.so");
  analysis.AddLibraries("libHist.so");
  analysis.AddLibraries("libLQCycle.so");
  g_logger << VERBOSE << "Added up libaries" << LQLogger::endmsg;
  analysis.SetInputList(TString(filename));
  analysis.SetTreeName("rootTupleTree/tree");
  analysis.SetCycleName("Analyzer");
  g_logger << VERBOSE << "Setting up tree" << LQLogger::endmsg;
  try {
    g_logger << VERBOSE << "About to initialize" << LQLogger::endmsg;
    analysis.SetEffectiveLuminosity(1.);
    analysis.SetTargetLuminosity(1.);
    analysis.SetLogLevel("INFO");
    //analysis.SetNEventsToProcess(200000);
    analysis.SetName("TEST",1,"./");
    

    ///// Run cycle
    analysis.Initialize();
    analysis.ExecuteCycle();

  }
  catch( const LQError& error ) {
    g_logger << FATAL << "LQError exception caught" << LQLogger::endmsg;
    g_logger << FATAL << "Message: " << error.what() << LQLogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << LQLogger::endmsg;
    return 1;

  } catch( const std::exception& error ) {
    g_logger << FATAL << "STD exception caught" << LQLogger::endmsg;
    g_logger << FATAL << "Message: " << error.what() << LQLogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << LQLogger::endmsg;
    return 1;

  } catch( ... ) {

    g_logger << FATAL << "Some unknown exception caught" << LQLogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << LQLogger::endmsg;
    return 1;

  }
  return 0;
}

    

void usage( char** argv ) {

  std::cout<< "Main executable to run an LQAnalyzer-based cycle analysis." << std::endl;

  std::cout << "\n\tUsage: " << argv[ 0 ] << " \'xml filename\'"
	    << std::endl;

  return;
}

