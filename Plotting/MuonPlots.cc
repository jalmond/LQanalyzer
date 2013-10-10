#include "MuonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



MuonPlots::MuonPlots(TString name) : StdPlots(name) {

  h_charge             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  h_HCalIso            = new TH1F("h_"+name+"_HCalIso",name+" HCal Iso",100,0.,10.);
  h_ECalIso            = new TH1F("h_"+name+"_ECalIso",name+" ECal Iso",100,0.,10.);
  h_TrkIso             = new TH1F("h_"+name+"_TrkIso",name+" Tracker Iso",100,0.,10.);
  h_Detector_RelIso    = new TH1F("h_"+name+"_Detector_RelIso",name+" Detector_RelIso",100,0.,1.);
  h_Detector_RelIsorho = new TH1F("h_"+name+"_Detector_RelIso_rho",name+" Detector_RelIso #rho corrected",100,0.,1.);
  h_photonIso          = new TH1F("h_"+name+"_photonIso",name+" photon Iso",100,0.,1.);
  h_chargedHadronIso   = new TH1F("h_"+name+"_chargedHadronIso",name+" charged Hadron Iso",100,0.,1.);
  h_neutralHadronIso   = new TH1F("h_"+name+"_neutralHadronIso",name+" neutral Hadron Iso",100,0.,1.);
  h_PF_RelIso          = new TH1F("h_"+name+"_PF_RelIso",name+" Particle Flow RelIso",100,0.,1.);
  h_PF_RelIso_beta     = new TH1F("h_"+name+"_PF_RelIso_beta",name+" Particle Flow RelIso #beta corrected",100,0.,1.);
  h_PUpt	       = new TH1F("h_"+name+"_PUpt",name+" Particle Flow pileup correction",100,0.,1.);
  h_HCalIsoDeposit     = new TH1F("h_"+name+"_HCalIsoDeposit",name+" HCal Iso Deposit",100,0.,10.);
  h_ECalIsoDeposit     = new TH1F("h_"+name+"_ECalIsoDeposit",name+" ECal Iso Deposit",100,0.,10.);
  h_GlbChi2            = new TH1F("h_"+name+"_GlbChi2",name+" Global #chi^{2} per #DoF",120,0.,12.);
  h_dxy                = new TH1F("h_"+name+"_dxy",name+" transverse IP",300,0.0,0.3);
  h_dz                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
}

MuonPlots::~MuonPlots() {
  // ~StdPlots();
  delete h_charge;
  delete h_HCalIso;
  delete h_ECalIso;
  delete h_TrkIso;
  delete h_Detector_RelIso;
  delete h_Detector_RelIsorho;
  delete h_HCalIsoDeposit;
  delete h_ECalIsoDeposit;  
  delete h_photonIso;
  delete h_chargedHadronIso;
  delete h_neutralHadronIso;
  delete h_PF_RelIso;
  delete h_PF_RelIso_beta;
  delete h_PUpt;
  delete h_GlbChi2;
  delete h_dxy;
  delete h_dz;
}

void MuonPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Int_t charge, Double_t trkIso, Double_t eCalIso, Double_t hCalIso, Double_t eCalIsoDeposit, Double_t hCalIsoDeposit, Double_t photonIso, Double_t chargedHadronIso, Double_t neutralHadronIso, Double_t Muon_GlobalChi2, Double_t dxy, Double_t dz, Double_t PUpt, Double_t rho) { 

  Double_t AreaTrackerMu[5] = {0., 0., 0., 0., 0.};                  //   barrel/endcap
  Double_t AreaEcalMu[5]    = {0.091, 0.077, 0.055, 0.034, 0.045};   //   barrel/endcap
  Double_t AreaHcalMu[5]    = {0.029, 0.027, 0.036, 0.040, 0.054};   //   barrel/endcap
  Int_t ifid;
  if (fabs(eta) < 0.5) ifid=0;
  else if (fabs(eta) >= 0.5 && fabs(eta) < 1.0) ifid=1;
  else if (fabs(eta) >= 1.0 && fabs(eta) < 1.5) ifid=2;
  else if (fabs(eta) >= 1.5 && fabs(eta) < 2.0) ifid=3;
  else if (fabs(eta) >= 2.0 && fabs(eta) < 2.5) ifid=4;
  else ifid=-1;
  Double_t MuTkIso   = trkIso  - AreaTrackerMu[ifid] * rho;
  Double_t MuEcalIso = eCalIso  - AreaEcalMu[ifid]  * rho;
  Double_t MuHcalIso = hCalIso - AreaHcalMu[ifid] * rho;

  StdPlots::Fill(weight, N, pt, eta, phi);
  h_charge->Fill(charge, weight);
  h_HCalIso->Fill(hCalIso, weight);
  h_ECalIso->Fill(eCalIso, weight);
  h_TrkIso->Fill(trkIso, weight);
  if (pt>0.01) {
    h_photonIso->Fill(photonIso/pt, weight);
    h_chargedHadronIso->Fill(chargedHadronIso/pt, weight);
    h_neutralHadronIso->Fill(neutralHadronIso/pt, weight);
    h_PUpt->Fill(PUpt/pt, weight);
  }
  if (pt>0.01) {
    h_PF_RelIso->Fill( (photonIso+chargedHadronIso+neutralHadronIso)/ pt , weight);
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) , weight);
    if ( (MuTkIso+MuEcalIso+MuHcalIso) < 0) 
      h_Detector_RelIsorho->Fill(0);
    else
      h_Detector_RelIsorho->Fill( (MuTkIso+MuEcalIso+MuHcalIso) / pt , weight);
    h_PF_RelIso_beta->Fill( (chargedHadronIso + max(0.0, neutralHadronIso + photonIso - 0.5*PUpt))/ pt , weight);
  }
  h_HCalIsoDeposit->Fill(hCalIsoDeposit, weight);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit, weight);
  h_GlbChi2->Fill(Muon_GlobalChi2, weight);
  h_dxy->Fill(dxy, weight);
  h_dz->Fill(dz, weight);
}

void MuonPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Int_t charge, Double_t trkIso, Double_t eCalIso, Double_t hCalIso, Double_t eCalIsoDeposit, Double_t hCalIsoDeposit, Double_t Muon_GlobalChi2) {
  StdPlots::Fill(weight, N, pt, eta, phi);
  h_charge->Fill(charge, weight);
  h_HCalIso->Fill(hCalIso, weight);
  h_ECalIso->Fill(eCalIso, weight);
  h_TrkIso->Fill(trkIso, weight);
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) , weight);
  h_HCalIsoDeposit->Fill(hCalIsoDeposit, weight);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit, weight);
  h_GlbChi2->Fill(Muon_GlobalChi2, weight);
}

void MuonPlots::Write() {
  StdPlots::Write();
  h_charge->Write();
  h_HCalIso->Write();
  h_ECalIso->Write();
  h_TrkIso->Write();
  h_Detector_RelIso->Write();
  h_Detector_RelIsorho->Write();
  h_HCalIsoDeposit->Write();
  h_ECalIsoDeposit->Write();
  h_photonIso->Write();
  h_chargedHadronIso->Write();
  h_neutralHadronIso->Write();
  h_PF_RelIso->Write();
  h_PF_RelIso_beta->Write();
  h_PUpt->Write();
  h_GlbChi2->Write();
  h_dxy->Write();
  h_dz->Write();
}
