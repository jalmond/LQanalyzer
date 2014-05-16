#ifndef FakeRateCalculator_El_h
#define FakeRateCalculator_El_h

#include "AnalyzerCore.h"


class FakeRateCalculator_El : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  FakeRateCalculator_El();
  ~FakeRateCalculator_El();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillCutFlow(TString cut, float w);
  bool IsTight(snu::KElectron el, double jetrho );
 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

  int n_17_pass;
  int n_17_17_jet_pass;
  int n_17_jet_pass;
  
  ClassDef ( FakeRateCalculator_El, 1);
};
#endif
