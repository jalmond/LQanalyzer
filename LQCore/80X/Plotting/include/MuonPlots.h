#ifndef MuonPlots_h
#define MuonPlots_h

#include "StdPlots.h"
#include "KMuon.h"



class MuonPlots : public StdPlots{
 public:

  MuonPlots();
  MuonPlots(TString name);
  
  MuonPlots(const MuonPlots& mp);  ///Copy constructor
  ~MuonPlots();    /// Destructor
  MuonPlots& operator=(const MuonPlots& obj);

  void Fill(TString name, double value, double weight);
  
  inline std::map<TString, TH1*> GetMap() const{return map_muon;}
  
  //// SNU function
  void Fill(Double_t weight, std::vector<snu::KMuon> muons);
  void Write();
  
 private:
  std::map<TString, TH1*> map_muon; 
  
  

};

#endif
