#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TChain.h"
#include "TString.h"

TChain* ChainMaker(std::string filelist) {

  std::cout << "In ChainMaker\n";

  std::ifstream fin(filelist.c_str());
  std::string word;

  std::cout << "root file .txt list: input file stream bad? " << fin.bad()<<endl;

  TChain* chain = new TChain("rootTupleTree/tree");

  if (!chain) std::cout << "\n\nTChain is null!\n\n";

  while ( fin >> word ) {
    //std::cout << word << std::endl;
    chain->Add( word.c_str() );
  }
  fin.close();

  //std::cout << "#events = " << chain->GetEntries() << std::endl;
  return chain;

}
