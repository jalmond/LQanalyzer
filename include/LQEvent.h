#ifndef LQEvent_h
#define LQEvent_h

#include <iostream>
using namespace std;

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "TLorentzVector.h"

#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"
#include "KTau.h"
#include "KEvent.h"

class LQEvent {

 public:
  LQEvent(std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el, std::vector<snu::KTau> taus, std::vector<snu::KJet> jets, snu::KEvent ev);

  ///Copy constructor
  LQEvent(const LQEvent& evb);

  LQEvent();
  LQEvent& operator= (const LQEvent& obj);

  ~LQEvent();
  
  inline std::vector<snu::KMuon> GetBaseMuons() const {return k_muons;}
  inline std::vector<snu::KElectron> GetBaseElectrons() const {return k_electrons;}
  inline std::vector<snu::KTau> GetBaseTaus() const {return k_taus;}
  inline std::vector<snu::KJet> GetBaseJets() const {return k_jets;}
  inline snu::KEvent GetBaseEvent() const {return k_event;}
  
  void reset();

 private:
  std::vector<snu::KMuon> k_muons;
  std::vector<snu::KElectron> k_electrons;
  std::vector<snu::KTau> k_taus;
  std::vector<snu::KJet> k_jets;
  snu::KEvent k_event;

};

#endif
