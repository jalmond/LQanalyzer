#ifndef EventBase_h
#define EventBase_h

#include <iostream>
using namespace std;


#include "TLorentzVector.h"
#include <vector>
#include "LQEvent.h"

/// Selection codes
#include "MuonSelection.h"
#include "ElectronSelection.h"
#include "TauSelection.h"
#include "JetSelection.h"
#include "GenSelection.h"
#include "EventSelection.h"
/// SNU codes
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"
#include "KTruth.h"
#include "KTau.h"
#include "KTrigger.h"

class EventBase {

 public:
  EventBase();
  EventBase(LQEvent kbase);
  EventBase(EventBase& evbase);
  EventBase& operator= (const EventBase& obj);
  ~EventBase();
  
  inline MuonSelection* GetMuonSel() const {return k_muonsel;}
  inline ElectronSelection* GetElectronSel() const {return k_electronsel;}
  inline JetSelection* GetJetSel() const {return k_jetsel;}
  inline TauSelection* GetTauSel() const {return k_tausel;}
  inline GenSelection* GetTruthSel() const {return k_truthsel;}
  inline EventSelection* GetEventSel() const {return k_eventsel;}

  inline std::vector<snu::KMuon> GetMuons() const {return k_LQevent->GetMuons();}
  inline std::vector<snu::KElectron> GetElectrons() const {return k_LQevent->GetElectrons();}
  inline std::vector<snu::KJet> GetJets() const {return k_LQevent->GetJets();}
  inline std::vector<snu::KTau> GetTaus() const {return k_LQevent->GetTaus();}
  inline std::vector<snu::KTruth> GetTruth() const {return k_LQevent->GetTruth();}
  inline snu::KTrigger GetTrigger() const {return k_LQevent->GetTrigger();}
  inline snu::KEvent GetEvent() const {return k_LQevent->GetEvent();}

  
  ///Copy constructor
  EventBase(const EventBase& sb);
  
  LQEvent* GetEventBase() const {return k_LQevent;}

  LQEvent* k_LQevent;
  MuonSelection* k_muonsel;
  ElectronSelection* k_electronsel;
  JetSelection* k_jetsel;
  TauSelection* k_tausel;
  GenSelection* k_truthsel;
  EventSelection* k_eventsel;
  
 
};

#endif
