#include "GenJetSelection.h"
#include <iostream>

using namespace snu;

GenJetSelection::GenJetSelection(LQEvent ev) :BaseSelection() {
  k_lqevent = ev;
}

GenJetSelection::~GenJetSelection() {}

//// This code is used to make selection cuts to vectors of KJets


void GenJetSelection::BasicSelection(std::vector<KGenJet>& jetColl) {
  
  //// This is a basic set of cuts on jets

  std::vector<KGenJet> alljets = k_lqevent.GetGenJets();
  
  for (std::vector<KGenJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    if( jit->Pt() > 10. &&  fabs(jit->Eta() < 4.)){
      jetColl.push_back(*jit);
    }
  }
}

  

void GenJetSelection::Selection(std::vector<KGenJet>& jetColl) {
  
  //// This is a basic set of cuts on jets
 
  std::vector<KGenJet> alljets = k_lqevent.GetGenJets();
  
  for (std::vector<KGenJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    if( jit->Pt() > 10. &&  fabs(jit->Eta() < 4.)){
      jetColl.push_back(*jit);
    }
  }
}





GenJetSelection& GenJetSelection::operator= (const GenJetSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms);
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

GenJetSelection::GenJetSelection(const GenJetSelection& ms):
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;  
};



