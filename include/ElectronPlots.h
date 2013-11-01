#ifndef ElectronPlots_h
#define ElectronPlots_h

#include "StdPlots.h"
#include "Data.h"
#include "KElectron.h"


class ElectronPlots : public StdPlots{

 public:
  ElectronPlots();
  ElectronPlots(TString name);

  ElectronPlots(const ElectronPlots& ep);
  ~ElectronPlots();
  ElectronPlots& operator=(const ElectronPlots& obj);
  
  inline std::map<TString, TH1*> GetMap() const{return map_el;}

  void Fill(TString name, Double_t value, Double_t weight);
  void Fill(Double_t weight, std::vector<snu::KElectron> el, double rho);
  void Write();

 private:
  std::map<TString, TH1*> map_el; 

};

#endif
