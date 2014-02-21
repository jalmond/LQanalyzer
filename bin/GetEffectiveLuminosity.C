#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1I.h"
#include "TString.h"

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);

void GetEffectiveLuminosity(std::string dir) {

  dir = "ls " + dir + "/*.root > inputlist.txt";
  system(dir.c_str());

    
  std::ifstream fin("inputlist.txt");
  std::string word;

  float number_events_processed(0.);
  float number_events_passed(0.);
  while ( fin >> word ) {
    std::cout << word << std::endl;    
    number_events_processed+= GetEventsProcessed(word);
    number_events_passed+= GetEventsPassed(word);
  }
  fin.close();
  

  std::cout << "Number of events processed = " << number_events_processed << std::endl;
  std::cout << "Number of events passed = " << number_events_passed << std::endl;

  return;

}

float GetEventsProcessed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1I*  EventCounter = (TH1I*) (file ->Get("LJFilter/EventCount/EventCounter"));  
  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}

float GetEventsPassed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1I*  EventCounter = (TH1I*) (file ->Get("LJFilter/EventCount/EventCounter"));

  float value = EventCounter->GetBinContent(2);
  file->Close();
  return value;
}
