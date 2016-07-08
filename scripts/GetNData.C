#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include <iomanip>
#include <sstream>
#include "TSystem.h"

#include <map>

#include "SampleMap.C"

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);
float GetSumWeights(std::string filename);

map<TString, Double_t> map_lumi;
map<TString, Double_t> neventmap;
map<TString, Double_t> n_w_eventmap;
void GetNData(TString version="") {
  

  TString def_version = TString(getenv("CATVERSION"));
  if(!version.Contains("v7") ) version = def_version;
  
  vector<int> v763; 
  vector<int> v765; 
  for(int i=0; i < 2; i++){
    
  
    TString dir = "ls /data4/DATA/FlatCatuples/Data/v7-6-3/DoubleEG/periodD/*.root > inputlist_efflumi.txt";
    if(i == 1) dir = "ls /data4/DATA/FlatCatuples/Data/v7-6-5/DoubleEG/periodD/*.root > inputlist_efflumi2.txt";
    
    bool use_sum_genweight(false);
    
    system(dir.Data());
    
    
    std::ifstream fin("inputlist_efflumi.txt");
    std::ifstream fin2("inputlist_efflumi2.txt");


    std::string word;
   
    float number_events_processed(0.);
    float number_events_processed2(0.);
    float number_events_passed(0.);
    float number_events_passed2(0.);
    float sum_of_weights(0.);

    if(i ==  0){
      while ( fin >> word ) {
	cout << word << endl;
	number_events_processed+= GetEventsProcessed(word);
	number_events_passed+= GetEventsPassed(word);
	cout << "number_events_processed = " << number_events_processed << "  number_events_passed " << number_events_passed << endl;
	v763.push_back(GetEventsPassed(word));
      }
    }
    else{
      int iv=0;
     while ( fin2 >> word ) {
        cout << word << endl;
        number_events_processed2+= GetEventsProcessed(word);
        number_events_passed2+= GetEventsPassed(word);
        cout << "v765:  number_events_processed = " << number_events_processed2 << "  number_events_passed2 " << number_events_passed << endl;
        if(GetEventsPassed(word) != v763.at(iv)) cout << "Number of events is differnet in file " << word << " " <<  GetEventsPassed(word) << " vs " << v763.at(iv) << endl; 
	iv++;
     }
     
    }

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

float GetSumWeights(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TDirectory * dir = (TDirectory*)file->Get(TString(filename) + ":/ntuple");
  TTree * tree;
  dir->GetObject("event",tree);
  
  float genWeight=0;
  TBranch        *b_genWeight; 
  
  tree->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
  
  float sum_weight=0.;
  Long64_t nentries = tree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tree->LoadTree(jentry);
    nb = tree->GetEntry(jentry);
    sum_weight += genWeight;
  }
  cout << "sum_weight = " << sum_weight << endl;
  return sum_weight;
}
