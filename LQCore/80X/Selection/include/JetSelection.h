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
  void Selection (std::vector<snu::KJet>& jetColl, bool LepVeto, std::vector<snu::KMuon>& muonColl, std::vector<snu::KElectron>& electronColl, TString Option="");
  void BasicSelection (std::vector<snu::KJet>& jetColl);
  
  bool PassUserID (ID id, snu::KJet jet);
  
  void SelectJets(std::vector<snu::KJet>& jetColl, TString jetid, std::vector<snu::KMuon> muonColl, std::vector<snu::KElectron> electronColl, TString Option,  float ptcut=-999., float etacut=-999.);
  void SelectJets(std::vector<snu::KJet>& jetColl, TString jetid,std::vector<snu::KFatJet> fatjets , std::vector<snu::KMuon> muonColl,std::vector<snu::KElectron> electronColl, TString Option,  float ptcut=-999., float etacut=-999.);


};

#endif
