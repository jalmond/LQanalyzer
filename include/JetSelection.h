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

class JJ : public BaseSel {

 public:
  JJ(LQEvent ev);
  ~JJ();

  JJ& operator= (const JJ& obj);
  JJ(const JJ& bs);

 
  void JetSelection (std::vector<snu::KJet>& jetColl);
  void JetSelectionLeptonVeto(std::vector<snu::KJet>& jetColl, std::vector<snu::KMuon> muons, std::vector<snu::KElectron> electrons);
   
};

#endif
