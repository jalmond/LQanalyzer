#ifndef FakeRateCalculator_h
#define FakeRateCalculator_h

#include "Analyzer.h"

class FRCalculator : public Analyzer {

  static const Bool_t debug = false;
  static const Int_t nintpT=9;
  static const Double_t minbin = 35.0;
  static const Double_t binwidh = 5.0;
  
  static const Int_t ninteta=4;
  //Double_t *arrayeta;
  
  TH1F *h_MT, *h_HT;
  TH2F *h_nEvents, *h_nEventsFO, *h_FOrate;
  UInt_t index;
  Double_t HT;
  MuonPlots *h_TLnum, *h_TLden;

 public:

  FRCalculator();
  ~FRCalculator();

  void LoopFR();
};

#endif
