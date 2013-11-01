#include "MuonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



void MuonPlots::Fill(Double_t weight, std::vector<snu::KMuon> muons){
  int imu(0);
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit!=muons.end(); muit++,imu++){
    StdPlots::Fill(weight, muons.size(), muit->Pt(), muit->Eta(), muit->Phi());
    
    Fill("h_charge",muit->Charge(), weight); 
    
    if (muit->Pt()>0.01) {
       Fill("h_photonIso",muit->IsoR03ph()/muit->Pt(), weight);
       Fill("h_chargedHadronIso",muit->IsoR03ch()/muit->Pt(), weight);
       Fill("h_neutralHadronIso",muit->IsoR03nh()/muit->Pt(), weight);
       Fill("h_PUpt",muit->PFPUIsoR03()/muit->Pt(), weight);
       Fill("h_PF_RelIso", (muit->IsoR03ch() + muit->IsoR03nh() + muit->IsoR03ph() )/ muit->Pt() , weight);
       Fill("h_PF_RelIso_beta", (muit->IsoR03ch() + max(0.0, muit->IsoR03nh() + muit->IsoR03ph())- 0.5*muit->PFPUIsoR03())/ muit->Pt() , weight);
    }

     Fill("h_HCalIsoDeposit",muit->IsoHcalVeto(), weight);
     Fill("h_ECalIsoDeposit",muit->IsoEcalVeto(), weight);
    
     Fill("h_GlbChi2",muit->GlobalChi2(), weight);
     Fill("h_dxy",muit->dXY(), weight);
     Fill("h_dz",muit->dZ(), weight);
     Fill("h_d0",muit->D0(),weight);
     Fill("h_d0sig2",(muit->D0()/pow(muit->D0Err(),2.)),weight);
     Fill("h_d0sig",(muit->D0()/muit->D0Err()),weight);
     Fill("h_dxysig",(muit->dXY()/muit->D0Err()),weight);
     Fill("h_dxypatsig",(muit->dXYPat()/muit->dXYErrPat()),weight);
  }
}


void MuonPlots::Write() {
  
  StdPlots::Write();
  for(map<TString, TH1*>::iterator it = map_muon.begin(); it != map_muon.end(); it++){
    it->second->Write();
  }

}

MuonPlots::MuonPlots(TString name) : StdPlots(name) {
  
  map_muon["h_charge"]             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  map_muon["h_HCalIso"]            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  map_muon["h_ECalIso"]            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  map_muon["h_TrkIso"]             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  map_muon["h_Detector_RelIso"]    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  map_muon["h_Detector_RelIsorho"] = new TH1F("h_"+name+"_Detector_RelIso_rho",name+" Detector_RelIso #rho corrected",100,0.,1.);
  map_muon["h_photonIso"]          = new TH1F("h_"+name+"_photonIso",name+" photon Iso",100,0.,1.);
  map_muon["h_chargedHadronIso"]   = new TH1F("h_"+name+"_chargedHadronIso",name+" charged Hadron Iso",100,0.,1.);
  map_muon["h_neutralHadronIso"]   = new TH1F("h_"+name+"_neutralHadronIso",name+" neutral Hadron Iso",100,0.,1.);
  map_muon["h_PF_RelIso"]          = new TH1F("h_"+name+"_PF_RelIso",name+" Particle Flow RelIso",100,0.,1.);
  map_muon["h_PF_RelIso_beta"]     = new TH1F("h_"+name+"_PF_RelIso_beta",name+" Particle Flow RelIso #beta corrected",100,0.,1.);
  map_muon["h_PUpt"]	       = new TH1F("h_"+name+"_PUpt",name+" Particle Flow pileup correction",100,0.,1.);
  map_muon["h_HCalIsoDeposit"]     = new TH1F("h_"+name+"_HCalIsoDeposit",name+" HCal Iso Deposit",100,0.,10.);
  map_muon["h_ECalIsoDeposit"]     = new TH1F("h_"+name+"_ECalIsoDeposit",name+" ECal Iso Deposit",100,0.,10.);
  map_muon["h_GlbChi2"]            = new TH1F("h_"+name+"_GlbChi2",name+" Global #chi^{2} per #DoF",120,0.,12.);
  map_muon["h_dxy"]                = new TH1F("h_"+name+"_dxy",name+" transverse IP",200,0.0,0.05);
  map_muon["h_dz"]                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
  map_muon["h_d0"]                 = new TH1F("h_"+name+"_d0",name+" d0 IP",100,0.0,0.2);
  map_muon["h_d0sig"]                 = new TH1F("h_"+name+"_d0sig",name+" d0sig IP",100,-10.,10.0);
  map_muon["h_d0sig2"]                 = new TH1F("h_"+name+"_d0sig2",name+" d0sig IP",100,-20000.,20000.0);
  map_muon["h_dxysig"]                 = new TH1F("h_"+name+"_dxysig",name+" d0sig IP",100,-10.,10.0);
  map_muon["h_dxypatsig"]                 = new TH1F("h_"+name+"_dxypatsig",name+" d0sig IP",100,-10.,10.0);
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
