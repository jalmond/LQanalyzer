#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TString.h"
#include <iomanip>

#include <map>

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);

void GetEffectiveLuminosity() {
  

  map<TString, double> dirmap;
  // dir name  = xsec
  //dirmap["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 1.;
  dirmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 1.;//6024.2;


  for(map<TString, double>::iterator it = dirmap.begin(); it != dirmap.end();it++){
    
    
    TString dir = "ls /data2/DATA/cattoflat/MC/v7-4-2/" + it->first + "/*.root > inputlist.txt";
    //TString dir = "ls /data2/DATA/cattoflat/MC/v7-4-2/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/*.root > inputlist.txt";

    
    system(dir.Data());
    
  
    std::ifstream fin("inputlist.txt");
    std::string word;
    
    float number_events_processed(0.);
    float number_events_passed(0.);
    while ( fin >> word ) {
      number_events_processed+= GetEventsProcessed(word);
      number_events_passed+= GetEventsPassed(word);
    }
    fin.close();
    
    
   
    float lumi = number_events_processed / it->second;

    std::cout.precision(10);
    std::cout << it->first << "    " << lumi << std::endl;
    
    system("rm inputlist.txt");
  }    

    return;
    
}

float GetEventsProcessed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());
  //  cout << file << endl;
  TH1F*  EventCounter = (TH1F*) (file ->Get("ntuple/hNEvent"));
  
  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}

float GetEventsPassed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1F*  EventCounter = (TH1F*) (file ->Get("ntuple/hNEvent"));

  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}
