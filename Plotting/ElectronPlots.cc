#include "ElectronPlots.h"
#include <iostream>


ElectronPlots::ElectronPlots(TString name) : StdPlots(name) {

  map_el["h_charge"]             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  map_el["h_HCalIso"]            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  map_el["h_ECalIso"]            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  map_el["h_TrkIso"]             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  map_el["h_Detector_RelIso"]    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  map_el["h_Detector_RelIsorho"] = new TH1F("h_"+name+"_Detector_RelIso_rho",name+" Detector_RelIso #rho corrected",100,0.,1.);
  map_el["h_dxy"]                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  map_el["h_dz"]                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
}

ElectronPlots::~ElectronPlots() {
  for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
     delete mit->second ;
  }
}

void ElectronPlots::Fill(Double_t weight, std::vector<snu::KElectron> el, double rho){

  Double_t AreaTrackerEle[2] = {0., 0.};         //   barrel/endcap
  Double_t AreaEcalEle[2]    = {0.101, 0.046};   //   barrel/endcap
  Double_t AreaHcalEle[2]    = {0.021 , 0.040};  //   barrel/endcap
  
  int iel(0);
  for(std::vector<snu::KElectron>::iterator elit = el.begin(); elit!=el.end(); elit++,iel++){

    Int_t ifid = (fabs(elit->Eta()) < 1.479) ? 0 : 1;
    Double_t ElTkIso   = elit->TrkIso() - AreaTrackerEle[ifid] * rho;
    Double_t ElEcalIso = elit->ECalIso() - AreaEcalEle[ifid]  * rho;
    Double_t ElHcalIso = elit->HCalIso() - AreaHcalEle[ifid] * rho;

    Fill("h_charge", elit->Charge(), weight);
    Fill("h_HCalIso",elit->HCalIso() , weight);
    Fill("h_ECalIso",elit->ECalIso() , weight);
    Fill("h_TrkIso",elit->TrkIso() , weight);
    if (elit->Pt()>0.01) {
      Fill("h_Detector_RelIso", (elit->HCalIso()+elit->ECalIso()+elit->TrkIso()) / max(elit->Pt(),20.0) , weight);
      Fill("h_Detector_RelIsorho", (ElTkIso+ElEcalIso+ElHcalIso) / elit->Pt() , weight);
    }
    else {
      Fill("h_Detector_RelIso",999.9,weight);
      Fill("h_Detector_RelIsorho",999.9, weight);
    }
    Fill("h_dxy",elit->dxy(), weight);
    Fill("h_dz",elit->dz(), weight);
  } // end of electron loop
  
  return;
}


void ElectronPlots::Write() {
  StdPlots::Write();

  for(map<TString, TH1*>::iterator it = map_el.begin(); it != map_el.end(); it++){
    it->second->Write();
  }
}

ElectronPlots::ElectronPlots() : StdPlots() {
}

/**
 * Copy constructor.
 */
ElectronPlots::ElectronPlots(const ElectronPlots& ep): StdPlots(ep)
{
  for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = ep.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


ElectronPlots& ElectronPlots::operator= (const ElectronPlots& ep)
{
  if (this != &ep) {

    for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = ep.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

void ElectronPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_el.find(name);
  if(it!= map_el.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_el" << endl;
  return;
}
