#ifndef GenJetSelection_h
#define GenJetSelection_h

#include <iostream>
using namespace std;


#include "TLorentzVector.h"
#include <vector>
#include "LQEvent.h"
#include "KGenJet.h"
#include "BaseSelection.h"

class GenJetSelection : public BaseSelection {

 public:
  GenJetSelection(LQEvent ev);
  ~GenJetSelection();

  GenJetSelection& operator= (const GenJetSelection& obj);
  GenJetSelection(const GenJetSelection& bs);

 
  void Selection (std::vector<snu::KGenJet>& jetColl);
  void BasicSelection (std::vector<snu::KGenJet>& jetColl);
 

   
};

#endif
