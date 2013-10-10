#ifndef JetSelection_h
#define JetSelection_h

#include <iostream>
using namespace std;

#include "TLorentzVector.h"
#include <vector>
#include "Jet.h"
#include "Lepton.h"

class JJ {

  TLorentzVector vJet;
  Bool_t jetIsOK;
  Double_t pt_cut_min, pt_cut_max, eta_cut;
  
 public:
  JJ();
  ~JJ();
 
  void JetSelection(std::vector<Int_t> Jet_Id_loose, std::vector<Double_t> Jet_Eta, std::vector<Double_t> Jet_Phi, std::vector<Double_t> Jet_Pt, std::vector<Double_t> Jet_E, std::vector<Double_t> Jet_neutralEmEnergyFraction, std::vector<Double_t> Jet_neutralHadronEnergyFraction, std::vector<Double_t> Jet_chargedEmEnergyFraction, std::vector<Double_t> Jet_chargedHadronEnergyFraction, std::vector<Int_t> Jet_chargedMultiplicity, std::vector<Int_t> Jet_NConstituents, std::vector<Double_t> Jet_BTag, std::vector<Double_t> Jet_threeD, std::vector<Jet>& jetColl);
  
  void JetSelectionLeptonVeto(std::vector<Int_t> Jet_Id_loose, std::vector<Double_t> Jet_Eta, std::vector<Double_t> Jet_Phi, std::vector<Double_t> Jet_Pt, std::vector<Double_t> Jet_E, std::vector<Double_t> Jet_neutralEmEnergyFraction, std::vector<Double_t> Jet_neutralHadronEnergyFraction, std::vector<Double_t> Jet_chargedEmEnergyFraction, std::vector<Double_t> Jet_chargedHadronEnergyFraction, std::vector<Int_t> Jet_chargedMultiplicity, std::vector<Int_t> Jet_NConstituents, std::vector<Double_t> Jet_BTag, std::vector<Double_t> Jet_threeD, std::vector<Lepton>& leptonColl1, std::vector<Lepton>& leptonColl2, std::vector<Jet>& jetColl);

  void SetPt(Double_t minPt, Double_t maxPt);
  void SetPt(Double_t minPt);
  void SetEta(Double_t Eta);
 
};

#endif
