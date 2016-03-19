#ifndef StdPlots_h
#define StdPlots_h

#include <string>
#include "TH1F.h"
#include <map>


class StdPlots {

 public:

  enum Channel{ 
    ALL        =0,
    ee         =1,
    mumu       =2,
    emu        =3
  };
  

  const Double_t Mass_W;
    
 protected:
  StdPlots();
  StdPlots(TString name);
  
 private:
  StdPlots& operator= (const StdPlots& obj);
  
 public:
  virtual ~StdPlots();
  StdPlots(const StdPlots& p);
  
  void Fill();
  void Write();
  
};


#endif
