#ifndef Scale_cf_h
#define Scale_cf_h

#include "AnalyzerCore.h"
class Scale_cf : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  Scale_cf();
  ~Scale_cf();

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


  ClassDef ( Scale_cf, 1);
};
#endif
