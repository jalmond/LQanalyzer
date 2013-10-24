#ifndef LeptonSelection_h
#define LeptonSelection_h

#include <iostream>
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Lepton.h"
#include "OtherFunctions.h"

class Lep {

 public:
  Int_t ifid;
  Lepton::FakeType fakeType;
  Lepton::LooseTight looseTight;
  Lepton::LeptonType leptonType;
  TLorentzVector vLepton;
  Bool_t etaPt,RelIsod0Chi2,DepositVeto,individual,RelIsod0;//fiducial;//muonid,pTcut,isIso;
  Double_t LeptonRelIso,dxy,dz,D0,D0Error,D0Significance,Vxy, Vz;
  Int_t numlep;
  Double_t pt_cut_min, pt_cut_max, eta_cut_min, eta_cut, relIso_cut, relIsoMIN_cut, chiNdof_cut, chiNdofMIN_cut, dxy_cut, dxyMIN_cut, dz_cut;
  Int_t casediscriminator,simpleselection;

  Double_t LeptonchiNdof;
  Lep();
  ~Lep();

  void reset();
  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetEta(Double_t Eta);
  void SetEta(Double_t minEta, Double_t Eta);
  void SetRelIso(Double_t RelIso);
  void SetRelIso(Double_t RelIsoMIN, Double_t RelIso);
  void SetChiNdof(Double_t ChiNdof);
  void SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof);
  void SetBSdxy(Double_t dxy);
  void SetBSdxy(Double_t dxyMIN, Double_t dxy);
  void SetBSdz(Double_t dz);
};

#endif
