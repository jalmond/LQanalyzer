#ifndef HNEMu_h
#define HNEMu_h

#include "AnalyzerCore.h"


class HNEMu : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HNEMu();
  ~HNEMu();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillCutFlow(TString cut, float w);
  void FillEventCutFlow(TString cut, TString label, float w);
  void FillIsoCutFlow(TString cut, float w);
  void CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name);
  

  float WeightCFEvent(std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons,  bool runchargeflip, bool useoldrates=false);  
  float IsDiLep(std::vector<snu::KElectron> electrons);

 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
  float m_os_Z_nw;
  float m_ss_Z_nw;
  float m_os_Z;
  float m_ss_Z;


  float k_met, k_eemass, k_eejjmass, k_e1jjmass, k_e2jjmass,  k_st, k_ht;
  int k_njet, k_nbjet_l, k_nbjet_m, k_nbjet_t;
  float  k_el1eta, k_el2eta;
  float k_weight, k_el1pt, k_el2pt, k_j1pt, k_jjmass;
  bool k_cl1bjet, k_cl2bjet,k_cll1bjet, k_cll2bjet; 

  ClassDef ( HNEMu, 1);
};
#endif
