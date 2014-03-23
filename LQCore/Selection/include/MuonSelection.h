#ifndef MuonSelection_h
#define MuonSelection_h

#include "BaseSelection.h"
#include "KMuon.h"

class MuonSelection : public BaseSelection {
  Double_t ECalDeposit_max, HCalDeposit_max, ECalDeposit_min, HCalDeposit_min;

  static const Double_t AreaTrackerMu[5];
  static const Double_t AreaEcalMu[5];
  static const Double_t AreaHcalMu[5];

 public:
  MuonSelection(LQEvent ev);
  ~MuonSelection();
  
  MuonSelection& operator= (const MuonSelection& obj);
  MuonSelection(const MuonSelection& bs);
  
  bool PassID(ID id, snu::KMuon mu);
  
  //// General Selection
  void Selection(std::vector<snu::KMuon>& leptonColl);

  /// selection for treemaker
  void BasicSelection(std::vector<snu::KMuon>& leptonColl);

  void SkimSelection( std::vector<snu::KMuon>& leptonColl); 
  //// HN analysis selection
  void HNTightMuonSelection(std::vector<snu::KMuon>& leptonColl) ;
  void HNLooseMuonSelection(std::vector<snu::KMuon>& leptonColl) ;
  void HNVetoMuonSelection(std::vector<snu::KMuon>& leptonColl) ;

  //// General 
  void SetDeposits(Double_t ECalDeposit, Double_t HCalDeposit);
  void SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2);
  
};

#endif
