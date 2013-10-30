#ifndef MuonSelection_h
#define MuonSelection_h

#include "BaseSelection.h"
#include "KMuon.h"

class MuonSel : public BaseSel {
  Int_t numVer, leptoni;
  Double_t ECalDeposit_max, HCalDeposit_max, ECalDeposit_min, HCalDeposit_min;

  static const Double_t AreaTrackerMu[5];
  static const Double_t AreaEcalMu[5];
  static const Double_t AreaHcalMu[5];

 public:
  MuonSel();
  ~MuonSel();

  
  void MuonSelection(std::vector<snu::KMuon>& leptonColl);
  void TightMuonSelection(std::vector<snu::KMuon>& leptonColl) ;


  void SetDeposits(Double_t ECalDeposit, Double_t HCalDeposit);
  void SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2);

};

#endif
