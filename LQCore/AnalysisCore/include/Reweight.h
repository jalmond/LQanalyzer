#ifndef Reweight_h
#define Reweight_h

#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"


class Reweight {

 public:
  
  //// constructors
  Reweight(TString filename);
  ~Reweight();
  
  double GetWeight(int nvtx);
  TDirectory* getTemporaryDirectory(void) const;

 private:

  TFile* fileData_;

  TH1D* h_MCmod_;
  TH1D* h_Data_;

};

#endif

