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
