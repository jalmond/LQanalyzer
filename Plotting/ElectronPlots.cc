#include "include/ElectronPlots.h"

ElectronPlots::ElectronPlots(TString name) : StdPlots(name) {

  h_charge             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  h_HCalIso            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  h_ECalIso            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  h_TrkIso             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  h_Detector_RelIso    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  h_Detector_RelIsorho = new TH1F("h_"+name+"_Detector_RelIso_rho",name+" Detector_RelIso #rho corrected",100,0.,1.);
  h_dxy                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  h_dz                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
  h_photonIso          = new TH1F("h_"+name+"_photonIso",name+" photon Iso",100,0.,10.);
  h_chargedHadronIso   = new TH1F("h_"+name+"_chargedHadronIso",name+" charged Hadron Iso",100,0.,10.);
  h_neutralHadronIso   = new TH1F("h_"+name+"_neutralHadronIso",name+" neutral Hadron Iso",100,0.,10.);
  h_PF_RelIso          = new TH1F("h_"+name+"_PF_RelIso",name+" Particle Flow RelIso",100,0.,1.);
}

ElectronPlots::~ElectronPlots() {
  //StdPlots::~StdPlots();
  delete h_charge;
  delete h_HCalIso;
  delete h_ECalIso;
  delete h_TrkIso;
  delete h_Detector_RelIso;
  delete h_Detector_RelIsorho;
  delete h_dxy;
  delete h_dz; 
  delete h_photonIso;
  delete h_chargedHadronIso;
  delete h_neutralHadronIso;
  delete h_PF_RelIso;
}

void ElectronPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Double_t charge, Double_t trkIso, Double_t eCalIso, Double_t hCalIso, Double_t photonIso, Double_t chargedHadronIso, Double_t neutralHadronIso, Double_t dxy, Double_t dz, Double_t rho) { 
  StdPlots::Fill(weight, N, pt, eta, phi);
  
  Double_t AreaTrackerEle[2] = {0., 0.};         //   barrel/endcap
  Double_t AreaEcalEle[2]    = {0.101, 0.046};   //   barrel/endcap
  Double_t AreaHcalEle[2]    = {0.021 , 0.040};  //   barrel/endcap

  Int_t ifid = (fabs(eta) < 1.479) ? 0 : 1;
  Double_t ElTkIso   = trkIso - AreaTrackerEle[ifid] * rho;
  Double_t ElEcalIso = eCalIso - AreaEcalEle[ifid]  * rho;
  Double_t ElHcalIso = hCalIso - AreaHcalEle[ifid] * rho;

  h_charge->Fill(charge, weight);
  h_HCalIso->Fill(hCalIso, weight);
  h_ECalIso->Fill(eCalIso, weight);
  h_TrkIso->Fill(trkIso, weight);
  h_photonIso->Fill(photonIso, weight);
  h_chargedHadronIso->Fill(chargedHadronIso, weight);
  h_neutralHadronIso->Fill(neutralHadronIso, weight);
  if (pt>0.01) {
    h_PF_RelIso->Fill( (photonIso+chargedHadronIso+neutralHadronIso)/ pt , weight);
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) , weight);
    h_Detector_RelIsorho->Fill( (ElTkIso+ElEcalIso+ElHcalIso) / pt , weight);
  }
  else {
    h_Detector_RelIso->Fill(999.9);
    h_PF_RelIso->Fill(999.9);
    h_Detector_RelIsorho->Fill(999.9);
  }
  h_dxy->Fill(dxy, weight);
  h_dz->Fill(dz, weight);
}

void ElectronPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Double_t charge, Double_t trkIso, Double_t eCalIso, Double_t hCalIso, Double_t dxy, Double_t dz, Double_t rho) {
  StdPlots::Fill(weight, N, pt, eta, phi);
  h_charge->Fill(charge, weight);
  h_HCalIso->Fill(hCalIso, weight);
  h_ECalIso->Fill(eCalIso, weight);
  h_TrkIso->Fill(trkIso, weight);
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) , weight);
  else
    h_Detector_RelIso->Fill(999.9);
  h_dxy->Fill(dxy, weight);
  h_dz->Fill(dz, weight);
}


void ElectronPlots::Write() {
  StdPlots::Write();
  h_charge->Write();
  h_HCalIso->Write();
  h_ECalIso->Write();
  h_TrkIso->Write();
  h_Detector_RelIso->Write();
  h_Detector_RelIsorho->Write();
  h_dxy->Write();
  h_dz->Write();
  h_photonIso->Write();
  h_chargedHadronIso->Write();
  h_neutralHadronIso->Write();
  h_PF_RelIso->Write();
}
