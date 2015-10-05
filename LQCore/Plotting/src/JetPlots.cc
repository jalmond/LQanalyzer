#include "JetPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

JetPlots::JetPlots(TString name) : StdPlots(name) {


}

JetPlots::~JetPlots() {
  for(std::map<TString, TH1*>::iterator mit = map_jet.begin(); mit != map_jet.end() ; mit++){
    delete mit->second ;
  }
}


void JetPlots::Fill(Double_t weight, std::vector<snu::KJet> jets){

  int ijet(0);
  for(std::vector<snu::KJet>::iterator jit = jets.begin(); jit!=jets.end(); jit++,ijet++){
    StdPlots::Fill(weight, jets.size(), jit->Pt(), jit->Eta(), jit->Phi());
    

  }
}

void JetPlots::Write() {
  StdPlots::Write(); 
  for(map<TString, TH1*>::iterator it = map_jet.begin(); it != map_jet.end(); it++){
    it->second->Write();
  }
}


JetPlots::JetPlots() : StdPlots() {
}


/**
 * Copy constructor.
 */
JetPlots::JetPlots(const JetPlots& jp): StdPlots(jp)
{
  for(std::map<TString, TH1*>::iterator mit = map_jet.begin(); mit != map_jet.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = jp.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


JetPlots& JetPlots::operator= (const JetPlots& jp)
{
  if (this != &jp) {

    for(std::map<TString, TH1*>::iterator mit = map_jet.begin(); mit != map_jet.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = jp.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

void JetPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_jet.find(name);
  if(it!= map_jet.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_el" << endl;
  return;
}
