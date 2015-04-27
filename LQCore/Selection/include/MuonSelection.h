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
  
  bool PassID(ID id, snu::KMuon mu, bool m_debug = false);
  
  //// General Selection
  void Selection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false); 

  /// selection for treemaker
  void BasicSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);

  void SkimSelection( std::vector<snu::KMuon>& leptonColl, bool m_debug = false); 

  //// HN analysis selection
  bool HNIsTight(snu::KMuon muon,  bool m_debug = false);
  void HNTightHighPtMuonSelection(std::vector<snu::KMuon>& leptonColl) ;
  void HNTightMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void HNLooseMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void HNLooseMuonSelection03(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void HNLooseMuonSelection05(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void HNVetoMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);

  //// Top analysis selection
  void TopTightMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void TopLooseMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);
  void TopVetoMuonSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);


  
  //// General 
  void SetDeposits(Double_t ECalDeposit, Double_t HCalDeposit);
  void SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2);
  
};

#endif
