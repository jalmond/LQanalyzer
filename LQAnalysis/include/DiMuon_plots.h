#ifndef DiMuon_plots_h
#define DiMuon_plots_h

#include "AnalyzerCore.h"
class DiMuon_plots : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  DiMuon_plots();
  ~DiMuon_plots();

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


  ClassDef ( DiMuon_plots, 1);
};
#endif
