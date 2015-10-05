#include "EventBase.h"

using namespace snu;

EventBase::EventBase() {
}

EventBase::EventBase(LQEvent kbase) {
  k_LQevent = new LQEvent(kbase);
  k_muonsel = new MuonSelection(kbase);
  k_jetsel = new JetSelection(kbase);
  k_genjetsel = new GenJetSelection(kbase);
  k_electronsel = new ElectronSelection(kbase);
  k_truthsel = new GenSelection(kbase);
  k_eventsel = new EventSelection();

}
EventBase::~EventBase() {
  delete k_LQevent;
  delete k_muonsel;
  delete k_jetsel;
  delete k_genjetsel;
  delete k_electronsel;
  delete k_truthsel;
  delete k_eventsel;

}

EventBase::EventBase(EventBase& b){
  k_LQevent = b.GetEventBase();
  k_muonsel = b.GetMuonSel();
  k_electronsel = b.GetElectronSel();
  k_truthsel = b.GetTruthSel();
  k_eventsel = b.GetEventSel();
  k_jetsel = b.GetJetSel();
  k_genjetsel = b.GetGenJetSel();
}

EventBase& EventBase::operator= (const EventBase& b){
  if(this != & b){
    k_LQevent = b.GetEventBase();
    k_muonsel = b.GetMuonSel();
    k_electronsel = b.GetElectronSel();
    k_truthsel = b.GetTruthSel();
    k_eventsel = b.GetEventSel();
    k_jetsel = b.GetJetSel();
    k_genjetsel = b.GetGenJetSel();
  }
  return *this;
}




