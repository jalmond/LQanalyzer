#include "SelectionBase.h"

using namespace snu;

SelectionBase::SelectionBase() {
}

SelectionBase::SelectionBase(EventBase kbase) {
  k_event_base = kbase;
  k_jetsel.reset(kbase); //// Reset called from BaseSelection class
  
}
SelectionBase::~SelectionBase() {}

SelectionBase::SelectionBase(SelectionBase& b){
  k_event_base = b.GetEventBase();
  k_muonsel = b.GetMuonSel();
  k_electronsel = b.GetElectronSel();
  k_tausel = b.GetTauSel();
  k_eventsel = b.GetEventSel();
  k_jetsel = b.GetJetSel();
}







