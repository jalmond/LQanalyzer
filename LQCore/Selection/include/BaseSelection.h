#ifndef BaseSelection_h
#define BaseSelection_h

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
#include "AnalysisBase.h"
#include "LQEvent.h"

class BaseSelection {

 public:


  enum ID {
    ELECTRON_POG_VETO              = 0,
    ELECTRON_POG_LOOSE             = 1,
    ELECTRON_POG_MEDIUM            = 2,
    ELECTRON_POG_TIGHT             = 3,
    ELECTRON_POG_MVATrig           = 4,
    ELECTRON_POG_MVANonTrig        = 5,
    ELECTRON_ECAL_FIDUCIAL         = 6,
    ELECTRON_HN_VETO               = 7,
    ELECTRON_HN_TIGHT              = 8,
    ELECTRON_HN_FAKELOOSE           = 9,
    ELECTRON_HN_FAKELOOSE_NOD0      = 10,
    ELECTRON_TOP_VETO              = 11,
    ELECTRON_TOP_LOOSE             = 12,
    ELECTRON_TOP_TIGHT             = 13,
    ELECTRON_PTETA                 = 14,
    ELECTRON_NOCUT                 = 15,
    MUON_POG_LOOSE                 = 16,
    MUON_POG_MEDIUM                = 17,
    MUON_POG_TIGHT                 = 18,
    MUON_HN_VETO                   = 19,
    MUON_HN_FAKELOOSE              = 20,
    MUON_HN_TIGHT                  = 21,
    MUON_FAKELOOSE                 = 22,
    MUON_TOP_VETO                  = 23,
    MUON_TOP_LOOSE                 = 24,
    MUON_TOP_TIGHT                 = 25,
    MUON_PTETA                     = 26,
    MUON_NOCUT                     = 27,
    PFJET_LOOSE                    = 28,
    PFJET_MEDIUM                   = 29,
    PFJET_TIGHT                    = 30,
    JET_HN                         = 31,
    JET_HN_TChannel                = 32,
    JET_NOLEPTONVETO               = 33,
    JET_LOOSE                      = 34,
    JET_TIGHT                      = 35,
    PHOTON_POG_LOOSE               = 36, 
    PHOTON_POG_MEDIUM              = 37, 
    PHOTON_POG_TIGHT               = 38, 
  };

  Int_t ifid;
  
  //// Selection cuts
  Bool_t etaPt,RelIsod0Chi2,DepositVeto,individual,RelIsod0;//fiducial;//muonid,pTcut,isIso;

  //// variables to make cuts
  Double_t LeptonRelIso,dxy,dz,D0,D0Error,D0Significance,Vxy, Vz;
  Double_t LeptonchiNdof;
  Int_t numlep;
  Bool_t jetIsOK;

  /// variables to set cuts
  Double_t pt_cut_min, pt_cut_max, eta_cut_min, eta_cut, 
           jpt_cut_min, jpt_cut_max, jeta_cut_min, jeta_cut,
           relIso_cut, relIsoMIN_cut, chiNdof_cut, chiNdofMIN_cut, 
           dxy_cut, dxyMIN_cut, dz_cut;

  Int_t casediscriminator,simpleselection;

  /// LQEvent class object. Stores all vectors
  LQEvent k_lqevent;


  BaseSelection();
  BaseSelection& operator= (const BaseSelection& obj);
  BaseSelection(const BaseSelection& bs);

  ~BaseSelection();

  /// bools to tell selector to apply cuts
  Bool_t  apply_ptcut,apply_etacut, apply_jptcut,apply_jetacut, apply_relisocut, apply_chi2cut, apply_dxycut, apply_dzcut, apply_general, apply_deposit;
  Bool_t apply_ID, apply_convcut, apply_chargeconst, applypileuptool;
  
  ID k_id;
  
  /// SetCut functions
  void reset();
  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetJetPt(Double_t minPt);
  void SetEta(Double_t Eta);
  void SetUseJetPileUp(bool use);
  void SetJetEta(Double_t Eta);
  void SetEta(Double_t minEta, Double_t Eta);
  void SetRelIso(Double_t RelIso);
  void SetRelIso(Double_t RelIsoMIN, Double_t RelIso);
  void SetChiNdof(Double_t ChiNdof);
  void SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof);
  void SetBSdxy(Double_t dxy);
  void SetBSdxy(Double_t dxyMIN, Double_t dxy);
  void SetBSdz(Double_t dz);
  void SetID(ID  id);
  void SetCheckCharge(bool check);
  void SetApplyConvVeto(bool apply);
};

#endif
