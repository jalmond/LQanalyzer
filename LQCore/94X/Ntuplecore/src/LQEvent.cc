#include "../include/LQEvent.h"

using namespace snu;
using namespace std;


LQEvent::LQEvent(std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el, std::vector<snu::KPhoton> ph,  std::vector<snu::KJet> jets,   std::vector<snu::KFatJet> fatjets, std::vector<snu::KGenJet> genjets,  std::vector<snu::KTruth> truth, snu::KTrigger tr, snu::KEvent ev) {

  k_muons = muons;
  k_electrons = el;
  k_photons = ph;
  k_jets = jets;
  k_fatjets = fatjets;
  k_genjets = genjets;
  k_truth = truth;
  k_trigger = tr;
  k_event= ev;
  
}

LQEvent::LQEvent() {
  k_muons.clear();
  k_electrons.clear();
  k_photons.clear();
  k_jets.clear();
  k_fatjets.clear();
  k_genjets.clear();
  k_truth.clear();
  k_trigger.Reset();
  k_event.Reset();
  
}

LQEvent::~LQEvent() {}

void LQEvent::reset(){
  k_muons.clear();
  k_electrons.clear();
  k_photons.clear();
  k_jets.clear();
  k_fatjets.clear();
  k_genjets.clear();
  k_truth.clear();
  k_trigger.Reset();
  k_event.Reset();
}


LQEvent::LQEvent(const LQEvent& evb){ 
  
  k_muons = evb.GetMuons();
  k_electrons = evb.GetElectrons();
  k_photons = evb.GetPhotons();
  k_jets = evb.GetJets();
  k_fatjets = evb.GetFatJets();
  k_genjets = evb.GetGenJets();
  k_truth = evb.GetTruth();
  k_trigger = evb.GetTrigger();
  k_event = evb.GetEvent();
}


LQEvent& LQEvent::operator= (const LQEvent& evb)
{
  if (this != &evb) {
    k_muons = evb.GetMuons();
    k_electrons = evb.GetElectrons();
    k_photons = evb.GetPhotons();
    k_genjets = evb.GetGenJets();
    k_jets = evb.GetJets();
    k_fatjets = evb.GetFatJets();
    k_truth = evb.GetTruth();
    k_trigger = evb.GetTrigger();
    k_event = evb.GetEvent();
  }  
  return *this;
}


void LQEvent::SetEvent(snu::KEvent ev){
  k_event=ev;
}
