#ifndef Closure_cf_h
#define Closure_cf_h

#include "AnalyzerCore.h"
class Closure_cf : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  Closure_cf();
  ~Closure_cf();

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


  ClassDef ( Closure_cf, 1);
};
#endif
