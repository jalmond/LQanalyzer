#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"
#include "TROOT.h"

using namespace std;

TChain* ChainMaker(std::string filelist) {
  

  gROOT->Reset();
  std::cout << "In ChainMaker\n";
    
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
