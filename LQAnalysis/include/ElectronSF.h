#ifndef ElectronSF_h
#define ElectronSF_h

#include "AnalyzerCore.h"


class ElectronSF : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  ElectronSF();
  ~ElectronSF();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillCutFlow(TString cut, float w);
  void FillEventCutFlow(TString cut, float w);
  void FillIsoCutFlow(TString cut, float w);
  void CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name);
  
  bool LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts, TString opt);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int bjetwp, float evmet, bool runchargeflip , std::vector<float> cuts,  TString opt);
  bool MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w);

  void FillDenominator(snu::KElectron el, float mass, float w);
  void FillNumerator(snu::KElectron el, float mass,  float w);
  void FillPass(snu::KElectron el, float mass,  float w);
  void FillFail(snu::KElectron el, float mass,  float w);


  float WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip, bool useoldrates=false);  
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
  float k_weight, k_el1pt, k_el2pt, k_j1pt, k_jjmass;

  ClassDef ( ElectronSF, 1);
};
#endif
