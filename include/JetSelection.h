#ifndef JetSelection_h
#define JetSelection_h

#include <iostream>
using namespace std;


#include "TLorentzVector.h"
#include <vector>
#include "EventBase.h"
#include "KJet.h"
#include "KMuon.h"
#include "KElectron.h"
#include "BaseSelection.h"

class JJ : public BaseSel {

  TLorentzVector vJet;
  Bool_t jetIsOK;
  Double_t pt_cut_min, pt_cut_max, eta_cut;
  
 public:
  JJ();
  ~JJ();
 
  void JetSelection (std::vector<snu::KJet>& jetColl);
  void JetSelectionLeptonVeto(std::vector<snu::KJet>& jetColl, std::vector<snu::KMuon> muons, std::vector<snu::KElectron> electrons);
  
  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetEta(Double_t Eta);
 
};

#endif
