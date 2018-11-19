// STL include(s):
#include <string>
#include <iostream>
#include <fstream>

// ROOT include(s):
#include <TROOT.h>

//Local
#include "SNUController.h"
#include "SNUError.h"
#include "SNULogger.h"


// Global logging object
static SNULogger g_logger( "run_lqanalyzer" );

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
  
  g_logger << VERBOSE << "Setting up job" << SNULogger::endmsg;

  SNUController analysis; 
  analysis.SetJobName("Ztoll_ExampleCycle");
  analysis.AddLibraries("libSKTree.so");
  analysis.AddLibraries("libcore.so");
  analysis.AddLibraries("libAnalysisCore.so");
  analysis.AddLibraries("libSelection.so");
  analysis.AddLibraries("libPlotting.so");
  analysis.AddLibraries("libHist.so");
  analysis.AddLibraries("libSNUCycle.so");
  g_logger << VERBOSE << "Added up libaries" << SNULogger::endmsg;
  analysis.SetInputList(TString(filename));
  analysis.SetTreeName("rootTupleTree/tree");
  analysis.SetCycleName("Analyzer");
  g_logger << VERBOSE << "Setting up tree" << SNULogger::endmsg;
  try {
    g_logger << VERBOSE << "About to initialize" << SNULogger::endmsg;
    analysis.SetEffectiveLuminosity(1.);
    analysis.SetTargetLuminosity(1.);
    analysis.SetLogLevel("INFO");
    //analysis.SetNEventsToProcess(200000);
    analysis.SetName("TEST",1,"./");
    

    ///// Run cycle
    analysis.Initialize();
    analysis.ExecuteCycle();

  }
  catch( const SNUError& error ) {
    g_logger << FATAL << "SNUError exception caught" << SNULogger::endmsg;
    g_logger << FATAL << "Message: " << error.what() << SNULogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << SNULogger::endmsg;
    return 1;

  } catch( const std::exception& error ) {
    g_logger << FATAL << "STD exception caught" << SNULogger::endmsg;
    g_logger << FATAL << "Message: " << error.what() << SNULogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << SNULogger::endmsg;
    return 1;

  } catch( ... ) {

    g_logger << FATAL << "Some unknown exception caught" << SNULogger::endmsg;
    g_logger << FATAL << "--> Stopping execution" << SNULogger::endmsg;
    return 1;

  }
  return 0;
}

    

void usage( char** argv ) {

  std::cout<< "Main executable to run an SNUAnalyzer-based cycle analysis." << std::endl;

  std::cout << "\n\tUsage: " << argv[ 0 ] << " \'xml filename\'"
	    << std::endl;

  return;
}

