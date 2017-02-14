#ifndef JetSelection_h
#define JetSelection_h

#include <iostream>
using namespace std;


#include "TLorentzVector.h"
#include <vector>
#include "LQEvent.h"
#include "KJet.h"
#include "KMuon.h"
#include "KElectron.h"
#include "BaseSelection.h"

class JetSelection : public BaseSelection {

 public:
  JetSelection(LQEvent ev);
  ~JetSelection();

  JetSelection& operator= (const JetSelection& obj);
  JetSelection(const JetSelection& bs);

 
  void Selection (std::vector<snu::KJet>& jetColl);
  void Selection (std::vector<snu::KJet>& jetColl, bool LepVeto, std::vector<snu::KMuon>& muonColl, std::vector<snu::KElectron>& electronColl);
  void BasicSelection (std::vector<snu::KJet>& jetColl);
  
  bool PassUserID (ID id, snu::KJet jet);
  bool PassUserID (snu::KJet jet, TString ID);
  bool PassUserID_PFJetLoose( snu::KJet jet);
  bool PassUserID_PFJetMedium( snu::KJet jet);
  bool PassUserID_PFJetTight( snu::KJet jet);
  

  void SelectJets(std::vector<snu::KJet>& jetColl, std::vector<snu::KMuon> muonColl, std::vector<snu::KElectron> electronColl, TString ID,float ptcut=-999., float etacut=-999.);
  void SelectJets(std::vector<snu::KJet>& jetColl, TString ID,float ptcut=-999., float etacut=-999.);


};

#endif
