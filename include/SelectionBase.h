#ifndef SelectionBase_h
#define SelectionBase_h

#include <iostream>
using namespace std;


#include "TLorentzVector.h"
#include <vector>
#include "EventBase.h"
#include "MuonSelection.h"
#include "ElectronSelection.h"
#include "TauSelection.h"
#include "JetSelection.h"
#include "EventSelection.h"
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"

class  SelectionBase {

 public:
  SelectionBase();
  SelectionBase(EventBase evbase);
  SelectionBase(SelectionBase& evbase);
  ~SelectionBase();
  
  inline MuonSel GetMuonSel() const {return k_muonsel;}
  inline ElectronSel GetElectronSel() const {return k_electronsel;}
  inline JJ GetJetSel() const {return k_jetsel;}
  inline TauSel GetTauSel() const {return k_tausel;}
  inline EventSel GetEventSel() const {return k_eventsel;}

  inline std::vector<snu::KMuon> GetBaseMuons() const {return k_event_base.GetBaseMuons();}
  inline std::vector<snu::KElectron> GetBaseElectrons() const {return k_event_base.GetBaseElectrons();}
  inline std::vector<snu::KJet> GetBaseJets() const {return k_event_base.GetBaseJets();}
  inline snu::KEvent GetBaseEvent() const {return k_event_base.GetBaseEvent();}

  ///Copy constructor
  SelectionBase(const SelectionBase& sb);

  inline EventBase GetEventBase() const {return k_event_base;}
  
  EventBase k_event_base;
  MuonSel k_muonsel;
  ElectronSel k_electronsel;
  JJ k_jetsel;
  TauSel k_tausel;
  EventSel k_eventsel;
  
 
};

#endif
