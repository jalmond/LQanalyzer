#include "../include/LQEvent.h"

using namespace snu;
using namespace std;


LQEvent::LQEvent(std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el, std::vector<snu::KTau> taus, std::vector<snu::KJet> jets,  std::vector<snu::KTruth> truth, snu::KEvent ev) {

  k_muons = muons;
  k_electrons = el;
  k_jets = jets;
  k_taus = taus;
  k_truth = truth;
  k_event= ev;
  
}

LQEvent::LQEvent() {
  k_muons.clear();
  k_electrons.clear();
  k_jets.clear();
  k_taus.clear();
  k_truth.clear();
  k_event.Reset();
  
}

LQEvent::~LQEvent() {}

void LQEvent::reset(){
  k_muons.clear();
  k_electrons.clear();
  k_jets.clear();
  k_taus.clear();
  k_truth.clear();
  k_event.Reset();
}


LQEvent::LQEvent(const LQEvent& evb){ 
  
  k_muons = evb.GetBaseMuons();
  k_electrons = evb.GetBaseElectrons();
  k_jets = evb.GetBaseJets();
  k_taus = evb.GetBaseTaus();
  k_truth = evb.GetBaseTruth();
  k_event = evb.GetBaseEvent();
}


LQEvent& LQEvent::operator= (const LQEvent& evb)
{
  if (this != &evb) {
    k_muons = evb.GetBaseMuons();
    k_electrons = evb.GetBaseElectrons();
    k_jets = evb.GetBaseJets();
    k_taus = evb.GetBaseTaus();
    k_truth = evb.GetBaseTruth();
    k_event = evb.GetBaseEvent();
  }  
  return *this;
}
