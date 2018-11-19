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

  //// General Selection
  void Selection(std::vector<snu::KMuon>& leptonColl, bool applyrochester=true, TString Option="");

  /// selection for treemaker
  void BasicSelection(std::vector<snu::KMuon>& leptonColl, bool m_debug = false);

  void SkimSelection( std::vector<snu::KMuon>& leptonColl, bool m_debug = false); 


  float IsoCutValue(snu::KMuon muon,TString elid, TString isotype);


  /// New function., calls custim id in SKTree classes                                                                                                                                                                                                             
  void SelectMuons(std::vector<snu::KMuon>& leptonColl, TString muid,  TString Option="", double ptcut=-999., double etacut=-999.);
  bool MuonPass(snu::KMuon mu, TString muid, double ptcut=-999., double etacut=-999.);


  //// ID custom functions used by Selection(std::vector<snu::KMuon>& leptonColl, TString Option) function                                                                                                                                                     
  bool PassID(TString id, snu::KMuon mu, bool checkdxy=true, bool checkdz=true, bool checkchi2=true, bool m_debug = false);



  
  //// General 
  void SetDeposits(Double_t ECalDeposit, Double_t HCalDeposit);
  void SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2);
  
};

#endif
