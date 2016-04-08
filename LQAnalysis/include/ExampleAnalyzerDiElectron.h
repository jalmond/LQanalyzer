#ifndef ExampleAnalyzerDiElectron_h
#define ExampleAnalyzerDiElectron_h

#include "AnalyzerCore.h"


class ExampleAnalyzerDiElectron : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  ExampleAnalyzerDiElectron();
  ~ExampleAnalyzerDiElectron();

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
  
  int n_0;
  int n_1;
  int n_2;
  int n_3;
  int n_4;
  int n_5;
  int n_6a;
  int n_6b;
  int n_6c;
  int n_6d;
  int n_7;
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

  ClassDef ( ExampleAnalyzerDiElectron, 1);
};
#endif
