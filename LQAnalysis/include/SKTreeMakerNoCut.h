#ifndef SKTreeMakerNoCut_h
#define SKTreeMakerNoCut_h

#include "AnalyzerCore.h"
#include "KEvent.h"
#include "KTrigger.h"


class SKTreeMakerNoCut : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  SKTreeMakerNoCut();
  ~SKTreeMakerNoCut();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );

  void FillCutFlow(TString cut, float weight);
 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
  std::vector<snu::KJet> out_jets;
  std::vector<snu::KGenJet> out_genjets;
  std::vector<snu::KTruth> out_truth;
  snu::KEvent out_event;
  snu::KTrigger out_trigger;

  int pass_eventcut;
  int nevents;
  int pass_vertexcut;

  ClassDef ( SKTreeMakerNoCut, 1);
};
#endif
