#ifndef Analyzer_h
#define Analyzer_h

#include "AnalyzerCore.h"


class Analyzer : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  Analyzer();
  ~Analyzer();

  /// Functions from core
  virtual void BeginCycle(TString filename) throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndEvent()throw( LQError );
  virtual void EndCycle()throw( LQError );

  void InitialiseAnalysis() throw( LQError );
  void ClearOutputVectors();
  void MakeHistograms();

 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;


  ClassDef ( Analyzer, 0);
};
#endif
