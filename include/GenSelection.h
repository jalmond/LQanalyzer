#ifndef GenSelection_h
#define MuonSelection_h

#include "GenParticle.h"
#include "BaseSelection.h"

class GenSel : BaseSel {
  Int_t numVer, leptoni;

  GenParticle::FakeType fakeType;
  GenParticle::LooseTight looseTight;
  GenParticle::LeptonType leptonType;


 public:
  GenSel();
  ~GenSel();

 void GenSelection(std::vector<Double_t> Eta, std::vector<Double_t> Pt, std::vector<Double_t> Px, std::vector<Double_t> Py, std::vector<Double_t> Pz, std::vector<Double_t> E, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Int_t> pdgId, std::vector<Int_t> status, std::vector<Int_t> ndaught, std::vector<Int_t> mother, std::vector<GenParticle>& genColl);

};
#endif
