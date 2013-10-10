#include "include/LeptonPlots.h"

LeptonPlots::LeptonPlots(TString name) : StdPlots(name) {
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_charge",name.Data());
  sprintf(h_title,"Charge of %s",name.Data());
  h_charge = new TH1F(h_name,h_title,5,-2,3);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_HCalIso",name.Data());
  sprintf(h_title,"%s HCal Iso",name.Data());
  h_HCalIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_ECalIso",name.Data());
  sprintf(h_title,"%s ECal Iso",name.Data());
  h_ECalIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_TrkIso",name.Data());
  sprintf(h_title,"%s Tracker Iso",name.Data());
  h_TrkIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_Detector_RelIso",name.Data());
  sprintf(h_title,"%s Detector_RelIso",name.Data());
  h_Detector_RelIso = new TH1F(h_name,h_title,100,0.,1.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_photonIso",name.Data());
  sprintf(h_title,"%s photon Iso",name.Data());
  h_photonIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_chargedHadronIso",name.Data());
  sprintf(h_title,"%s charged Hadron Iso",name.Data());
  h_chargedHadronIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_neutralHadronIso",name.Data());
  sprintf(h_title,"%s neutral Hadron Iso",name.Data());
  h_neutralHadronIso = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_PF_RelIso",name.Data());
  sprintf(h_title,"%s Particle Flow RelIso",name.Data());
  h_PF_RelIso = new TH1F(h_name,h_title,100,0.,1.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_HCalIsoDeposit",name.Data());
  sprintf(h_title,"%s HCal Iso Deposit",name.Data());
  h_HCalIsoDeposit = new TH1F(h_name,h_title,100,0.,10.);
  strcpy(h_name,""); strcpy(h_title,""); 
  sprintf(h_name,"h_%s_ECalIsoDeposit",name.Data());
  sprintf(h_title,"%s ECal Iso Deposit",name.Data());
  h_ECalIsoDeposit = new TH1F(h_name,h_title,100,0.,10.);
}

LeptonPlots::~LeptonPlots() {
  //StdPlots::~StdPlots();
  delete h_charge;
  delete h_HCalIso;
  delete h_ECalIso;
  delete h_TrkIso;
  delete h_Detector_RelIso;
  delete h_HCalIsoDeposit;
  delete h_ECalIsoDeposit;  
  delete h_photonIso;
  delete h_chargedHadronIso;
  delete h_neutralHadronIso;
  delete h_PF_RelIso;
}

void LeptonPlots::Fill(Int_t &N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso) { 
  StdPlots::Fill(1, N, pt, eta, phi);
  h_charge->Fill(charge);
  h_HCalIso->Fill(hCalIso);
  h_ECalIso->Fill(eCalIso);
  h_TrkIso->Fill(trkIso);
  h_photonIso->Fill(photonIso);
  h_chargedHadronIso->Fill(chargedHadronIso);
  h_neutralHadronIso->Fill(neutralHadronIso);
  h_PF_RelIso->Fill( (photonIso+chargedHadronIso+neutralHadronIso)/ pt );
  if (pt>0.01)
    h_Detector_RelIso->Fill( (hCalIso+eCalIso+trkIso) / max(pt,20.0) );
  else
    h_Detector_RelIso->Fill(999.9);
  h_HCalIsoDeposit->Fill(hCalIsoDeposit);
  h_ECalIsoDeposit->Fill(eCalIsoDeposit);
}

void LeptonPlots::Write() {
  StdPlots::Write();
  h_charge->Write();
  h_HCalIso->Write();
  h_ECalIso->Write();
  h_TrkIso->Write();
  h_Detector_RelIso->Write();
  h_HCalIsoDeposit->Write();
  h_ECalIsoDeposit->Write();
  h_photonIso->Write();
  h_chargedHadronIso->Write();
  h_neutralHadronIso->Write();
  h_PF_RelIso->Write();
}
