#ifndef EfficiencyCalculator_h
#define EfficiencyCalculator_h

#include "Analyzer.h"
#include "MuonSelectionProbe.h"

class EffCalculator : public Analyzer {

  static const Bool_t debug = false;
  static const Int_t nintpT=6;
  static const Double_t minbin = 10.0;
  static const Double_t binwidh = 2.0;
  Double_t *arraypT;
  static const Int_t ninteta=4;
  //Double_t *arrayeta;
  
  TH1F *h_MT;
  TH2F *h_nEvents, *h_nEventsFO, *h_FOrate;
  UInt_t index;
  MuonPlots *h_TLnum, *h_TLden;
  MuonProbe Probe;

 public:

  EffCalculator();
  ~EffCalculator();

  void LoopEff();
};

#endif
