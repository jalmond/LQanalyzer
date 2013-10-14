#ifndef StdPlots_h
#define StdPlots_h

#include <string>
#include "TH1F.h"

class StdPlots {

 public:
  TH1F *h_particles, *h_pt, *h_eta, *h_phi;
 
  StdPlots(TString name);
  ~StdPlots();
  void Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi);
  void Write();

};


#endif
