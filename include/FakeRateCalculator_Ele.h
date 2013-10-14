#ifndef FakeRateCalculator_Ele_h
#define FakeRateCalculator_Ele_h

#include "Analyzer_Ele.h"

class FRCalculator_Ele : public Analyzer_Ele {

  static const Bool_t debug = false;
  static const Int_t nintpT=9;
  static const Double_t minbin = 35.0;
  static const Double_t binwidh = 5.0;
  //Double_t *arraypT_fake_el;
  static const Int_t ninteta=4;
  //Double_t *arrayeta;
  
  TH1F *h_MT, *h_HT;
  TH2F *h_nEvents, *h_nEventsFO, *h_FOrate;
  UInt_t index;
  Double_t HT;
  ElectronPlots *h_TLnum, *h_TLden;

 public:

  FRCalculator_Ele();
  ~FRCalculator_Ele();

  void LoopFR();
};

#endif
