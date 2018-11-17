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
#include "KFatJet.h"
#include "KGenJet.h"
#include "KTruth.h"
#include "KTrigger.h"
#include "KEvent.h"
#include "KPhoton.h"

class LQEvent {

 public:
  LQEvent(std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KPhoton> photons, std::vector<snu::KJet> jets,  std::vector<snu::KFatJet> fatjets,  std::vector<snu::KGenJet> genjets,std::vector<snu::KTruth> truth, snu::KTrigger tr,  snu::KEvent ev);

  ///Copy constructor
  LQEvent(const LQEvent& evb);

  LQEvent();
  LQEvent& operator= (const LQEvent& obj);

  ~LQEvent();
  
  void SetEvent(snu::KEvent);

  inline std::vector<snu::KMuon> GetMuons() const {return k_muons;}
  inline std::vector<snu::KElectron> GetElectrons() const {return k_electrons;}
  inline std::vector<snu::KPhoton> GetPhotons() const {return k_photons;}
  inline std::vector<snu::KTruth> GetTruth() const {return k_truth;}
  inline std::vector<snu::KJet> GetJets() const {return k_jets;}
  inline std::vector<snu::KFatJet> GetFatJets() const {return k_fatjets;}
  inline std::vector<snu::KGenJet> GetGenJets() const {return k_genjets;}
  inline snu::KEvent GetEvent() const {return k_event;}
  inline snu::KTrigger GetTrigger() const {return k_trigger;}
  
  void reset();

 private:
  std::vector<snu::KMuon> k_muons;
  std::vector<snu::KElectron> k_electrons;
  std::vector<snu::KPhoton> k_photons;
  std::vector<snu::KTruth> k_truth;
  std::vector<snu::KJet> k_jets;
  std::vector<snu::KFatJet> k_fatjets;
  std::vector<snu::KGenJet> k_genjets;
  snu::KTrigger k_trigger;
  snu::KEvent k_event;

};

#endif
