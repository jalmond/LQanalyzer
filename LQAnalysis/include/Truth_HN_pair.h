#ifndef Truth_HN_pair_h
#define Truth_HN_pair_h

#include "AnalyzerCore.h"
class Truth_HN_pair : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  Truth_HN_pair();
  ~Truth_HN_pair();

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


  ClassDef ( Truth_HN_pair, 1);
};
#endif
