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

  Bool_t MuonID;

  MuonSelection(LQEvent ev);
  ~MuonSelection();
  
  MuonSelection& operator= (const MuonSelection& obj);
  MuonSelection(const MuonSelection& bs);

  void SelectMuons(std::vector<snu::KMuon>& leptonColl, ID muid,   float ptcut=-999., float etacut=-999.);
  void SelectMuons(std::vector<snu::KMuon>& leptonColl, TString muid, float ptcut=-999., float etacut=-999.);


  bool PassUserID(TString id, snu::KMuon mu, bool m_debug = false);

  bool PassID(snu::KMuon mu,
	      bool m_debug = false);

  void  UserIDConfig(TString id);
  
  //// General Selection
  void Selection(std::vector<snu::KMuon>& leptonColl, bool applyrochester=true, TString Option="");

  /// selection for treemaker
  void BasicSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);

  void SkimSelection( std::vector<snu::KMuon>& leptonColl, bool m_debug = false); 


  // Get iso cut for ptcone
  float IsoCutValue(snu::KMuon muon,TString muid);
  

  
  //// General 
  void SetDeposits(Double_t ECalDeposit, Double_t HCalDeposit);
  void SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2);
  
};

#endif
