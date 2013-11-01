#include "JetPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

JetPlots::JetPlots(TString name) : StdPlots(name) {

  map_jet["h_TCHPT"]              = new TH1F("h_"+name+"_TCHPT","Track Counting High Purity "+name,100,-3,5);
  map_jet["h_JP"]                 = new TH1F("h_"+name+"_JP",name+" Jet Probability",100,0,3);
  map_jet["h_CSV"]                = new TH1F("h_"+name+"_CSV",name+" Combined Seconday Vertex",100,-1,2);
  map_jet["h_dxy"]                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  map_jet["h_dz"]                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
  map_jet["h_threeD"]             = new TH1F("h_"+name+"_threeD",name+" threeD vertex distance",100,0.,1.0);
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
    
    Fill("h_TCHPT",jit->PFJetTrackCountingHighPurBTag(), weight);
    Fill("h_JP",jit->BtagProb(), weight);
    Fill("h_CSV",jit->CombinedSecVertexBtag() , weight);
    Fill("h_dxy",jit->ClosestXYsep(), weight);
    Fill("h_dz",jit->ClosestZsep(), weight);
    Fill("h_threeD",jit->JetRho(), weight);
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
