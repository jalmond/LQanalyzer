#ifndef ExampleAnalyzerElectronMuon_h
#define ExampleAnalyzerElectronMuon_h

#include "AnalyzerCore.h"


class ExampleAnalyzerElectronMuon : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  ExampleAnalyzerElectronMuon();
  ~ExampleAnalyzerElectronMuon();
  
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


  ClassDef (ExampleAnalyzerElectronMuon, 1);
};
#endif
