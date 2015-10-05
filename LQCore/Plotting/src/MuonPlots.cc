#include "MuonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void MuonPlots::Fill(Double_t weight, std::vector<snu::KMuon> muons){
  int imu(0);
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit!=muons.end(); muit++,imu++){

    StdPlots::Fill(weight, muons.size(), muit->Pt(), muit->Eta(), muit->Phi());
    
    Fill("h_charge",muit->Charge(), weight); 
    
  }
}


void MuonPlots::Write() {
  
  StdPlots::Write();
  for(map<TString, TH1*>::iterator it = map_muon.begin(); it != map_muon.end(); it++){
    it->second->Write();
  }

}

MuonPlots::MuonPlots(TString name) : StdPlots(name) {
  
}



MuonPlots::MuonPlots() : StdPlots() {
}

/**
 * Copy constructor.
 */
MuonPlots::MuonPlots(const MuonPlots& mp): StdPlots(mp)
{
  for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = mp.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


MuonPlots& MuonPlots::operator= (const MuonPlots& mp)
{
  if (this != &mp) {

    for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = mp.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

MuonPlots::~MuonPlots() {
   for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
     delete mit->second ;
  }

}

void MuonPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_muon.find(name);
  if(it!= map_muon.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_muon" << endl;
  return;
}
