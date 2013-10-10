#ifndef Jet_h
#define Jet_h

#include "TLorentzVector.h"

class Jet {
  public:
    Jet(TLorentzVector& lorentzVec00, double& eta00, double& btag_disc00, double& threeD00, unsigned int jetIndex00)
      : lorentzVec_(lorentzVec00), eta_(eta00), btag_disc_(btag_disc00), threeD_(threeD00), jetIndex_(jetIndex00) {};

    ~Jet() {}

    //void set_btagged(bool btagged) { btagged_ = btagged; }

    TLorentzVector& lorentzVec() { return lorentzVec_; }
    double eta() {return eta_; }
    unsigned int ijet() { return jetIndex_; }
    double btag_disc() { return btag_disc_; }
    double threeD() {return threeD_; }


  private:
    TLorentzVector lorentzVec_;
    double eta_;
    double btag_disc_;
    double threeD_;
    unsigned int jetIndex_;
}; 

bool JetPTSorter(Jet jet1, Jet jet2) {
  return jet1.lorentzVec().Pt() > jet2.lorentzVec().Pt();
}

#endif
