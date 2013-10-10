#include "SNUTreeMuonFiller.h"

using namespace snu;

SNUTreeMuonFiller::SNUTreeMuonFiller() {};


SNUTreeMuonFiller::~SNUTreeMuonFiller() {};

std::vector<KMuon> SNUTreeMuonFiller::GetAllMuons(){
  
  std::vector<KMuon> muons;
  
  
  for (UInt_t ilep=0; ilep< MuonEta->size(); ilep++) {
    KMuon muon;
    muon.SetPtEtaPhiE(MuonPt->at(ilep),MuonEta->at(ilep),MuonPhi->at(ilep),MuonEnergy->at(ilep));
    muons.push_back(muon);
    }
  
  return muons;
}

