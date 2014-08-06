#ifndef HNDiElectron_h
#define HNDiElectron_h

#include "AnalyzerCore.h"


class HNDiElectron : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HNDiElectron();
  ~HNDiElectron();

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
  
  void CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w);
  bool LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip , float pt2, float pt1, float eemin, float eemax, float jjmin, float jjmax, float eejjmin, float eejjmax, float e1jjmin, float e1jjmax, float e2jjmin, float e2jjmax, float metmax, float mtmax, float stmin, float stmax, bool removeZ, bool removeej);
  bool MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  
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

  ClassDef ( HNDiElectron, 1);
};
#endif
