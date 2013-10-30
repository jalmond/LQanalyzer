#include "../include/EventBase.h"

using namespace snu;
using namespace std;


EventBase::EventBase(std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el, std::vector<snu::KTau> taus, std::vector<snu::KJet> jets, snu::KEvent ev) {

  k_muons = muons;
  k_electrons = el;
  k_jets = jets;
  k_taus = taus;
  k_event= ev;
  
}

EventBase::EventBase() {
  k_muons.clear();
  k_electrons.clear();
  k_jets.clear();
  k_taus.clear();
  k_event.Reset();
  
}

EventBase::~EventBase() {}

void EventBase::reset(){
  k_muons.clear();
  k_electrons.clear();
  k_jets.clear();
  k_taus.clear();
  k_event.Reset();
}


EventBase::EventBase(const EventBase& evb){ 
  
  k_muons = evb.GetBaseMuons();
  k_electrons = evb.GetBaseElectrons();
  k_jets = evb.GetBaseJets();
  k_taus = evb.GetBaseTaus();
  k_event = evb.GetBaseEvent();
}


EventBase& EventBase::operator= (const EventBase& evb)
{
  if (this != &evb) {
    k_muons = evb.GetBaseMuons();
    k_electrons = evb.GetBaseElectrons();
    k_jets = evb.GetBaseJets();
    k_taus = evb.GetBaseTaus();
    k_event = evb.GetBaseEvent();
  }  
  return *this;
}
