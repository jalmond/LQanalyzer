#ifndef HNElectronOptimisation_h
#define HNElectronOptimisation_h

#include "AnalyzerCore.h"


class HNElectronOptimisation : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HNElectronOptimisation();
  ~HNElectronOptimisation();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillCutFlow(TString cut, float w);
  void FillIsoCutFlow(TString cut, float w);
  void CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name);
  
  void CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w);
  bool LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets);
  bool MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets);
  bool HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets);
  
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

  ClassDef ( HNElectronOptimisation, 1);
};
#endif
