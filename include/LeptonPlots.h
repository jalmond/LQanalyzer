#ifndef LeptonPlots_h
#define LeptonPlots_h

#include "StdPlots.h"
#include "Data.h"

class LeptonPlots : public StdPlots{

 public:
  TH1F *h_charge, *h_HCalIso, *h_ECalIso, *h_TrkIso, *h_Detector_RelIso, *h_HCalIsoDeposit, *h_ECalIsoDeposit, *h_photonIso, *h_chargedHadronIso, *h_neutralHadronIso, *h_PF_RelIso;
  LeptonPlots(TString name);
  ~LeptonPlots();
  void Fill(Int_t &N, Double_t &pt, Double_t &eta, Double_t &phi, Double_t &charge, Double_t &trkIso, Double_t &eCalIso, Double_t &hCalIso, Double_t &eCalIsoDeposit, Double_t &hCalIsoDeposit, Double_t &photonIso, Double_t &chargedHadronIso, Double_t &neutralHadronIso);
  void Write();

};

#endif
