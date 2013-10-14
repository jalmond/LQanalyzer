#ifndef JetPlots_h
#define JetPlots_h

#include "StdPlots.h"
#include "KJet.h"


class JetPlots : public StdPlots{
 public:
  TH1F *h_energy, *h_TCHPT, *h_JP, *h_CSV, *h_dxy, *h_dz, *h_threeD;
  JetPlots(TString name);
  ~JetPlots();

  void Fill(Double_t weight, std::vector<snu::KJet> jets);
  void Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Double_t TCHPT, Double_t JP, Double_t CSV, Double_t dxy, Double_t dz, Double_t threeD);
  void Write();
};

#endif

