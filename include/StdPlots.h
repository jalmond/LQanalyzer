#ifndef StdPlots_h
#define StdPlots_h

#include <string>
#include "TH1F.h"
#include <map>


class StdPlots {

 public:
  TH1F *h_particles, *h_pt, *h_eta, *h_phi;
  const Double_t Mass_W;
    
 protected:
  StdPlots();
  StdPlots(TString name);
  
 private:
  StdPlots& operator= (const StdPlots& obj);
  
 public:
  virtual ~StdPlots();
  StdPlots(const StdPlots& p);
  
  void Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi);
  void Write();
  
};


#endif
