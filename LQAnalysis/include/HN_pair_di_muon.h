#ifndef HN_pair_di_muon_h
#define HN_pair_di_muon_h

#include "AnalyzerCore.h"
class HN_pair_di_muon : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HN_pair_di_muon();
  ~HN_pair_di_muon();

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


  ClassDef ( HN_pair_di_muon, 1);
};
#endif
