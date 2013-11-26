#ifndef Analyzer_h
#define Analyzer_h

#include "AnalyzerCore.h"


class Analyzer : public AnalyzerCore {

 public:
  
  virtual void BeginCycle(TString filename) throw( LQError );
  virtual void BeginEvent(float w)throw( LQError );
  virtual void SetUpEvent(Long64_t entry)throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndEvent()throw( LQError );
  virtual void EndCycle()throw( LQError );

  void InitialiseAnalysis() throw( LQError );
 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

 public:

  //// constructors
  Analyzer();
  ~Analyzer();

  
  /// global variable to set in constructor to tell code which Loop to run and which variables to set.
  jobtype _jtype;

  void ClearOutputVectors();
  void MakeHistograms();

  ClassDef ( Analyzer, 0);
};
#endif
