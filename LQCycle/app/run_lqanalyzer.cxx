// STL include(s):
#include <string>
#include <iostream>
#include <fstream>

// ROOT include(s):
#include <TROOT.h>
#include "Analyzer.h"

// Declaration of function printing the usage of the executable
void usage( char** argv );
TChain* ChainMaker(std::string filelist);


int main( int argc, char** argv ) {
  
  std::string filename ="";
  if( (argc == 2 && std::string( argv[ 1 ] ) == "-h" ) ) {
    usage( argv );
    return 1;
  }
  if( (argc == 1)){
    filename = "/var/tmp/jalmond/periodAelectron_111638/Job_1/periodAelectron_1.txt";
  }

  std::cout << "START" << std::endl;
  std::getchar();
  TChain* chain = ChainMaker(filename);
  std::cout << "Made Chain" << std::endl;
  std::getchar();

  Analyzer* SNUanal= new Analyzer(Analyzer::ZTest);
  std::cout << "Called constructor" << std::endl;
  std::getchar();

  SNUanal->Init(chain);
  std::cout << "Called Init" << std::endl;
  std::getchar();
  SNUanal->SetName("periodAelectron",1,"/var/tmp/jalmond/periodAelectron_111638/output/");
  SNUanal->SetTargetLumi(1.);
  SNUanal->SetWeight(1., 1.);
  SNUanal->NEvents(100000);
  std::cout << "About to run cycle" << std::endl;
  std::getchar();
  SNUanal->Run();
  delete SNUanal;
}

void usage( char** argv ) {

  std::cout<< "Main executable to run an LQAnalyzer-based cycle analysis." << std::endl;

  std::cout << "\n\tUsage: " << argv[ 0 ] << " \'xml filename\'"
	    << std::endl;

  return;
}

TChain* ChainMaker(std::string filelist) {

  std::cout << "In ChainMaker\n";
  gROOT->Reset();
  
  std::ifstream fin(filelist.c_str());
  std::string word;

  std::cout << "root file .txt list: input file stream bad? " << fin.bad()<<endl;
  
  TChain* chain = new TChain("rootTupleTree/tree");
  
  if (!chain) std::cout << "\n\nTChain is null!\n\n";

  std::cout << "Making TChain object with:" << std::endl;
  if(fin.is_open()){
    
    while(getline (fin,word)){     
      std::cout << "- " << word << std::endl;
      chain->Add(word.c_str());
    }
    
    fin.close();
  }
  std::cout << "Input sample contains " << chain->GetEntries() << " events "<< std::endl;
  return chain;

}


