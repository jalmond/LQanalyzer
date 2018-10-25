#ifndef SKTreeMaker_h
#define SKTreeMaker_h

#include "AnalyzerCore.h"
#include "KEvent.h"
#include "KTrigger.h"


class SKTreeMaker : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  SKTreeMaker();
  ~SKTreeMaker();

  /// Functions from core
   void BeginCycle() throw( LQError );
   void BeginEvent()throw( LQError );
   void ExecuteEvents()throw( LQError );
   void EndCycle()throw( LQError );
   void ClearOutputVectors()throw( LQError );

  void FillCutFlow(TString cut, float weight);
 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
  std::vector<snu::KPhoton> out_photons;
  std::vector<snu::KJet> out_jets;
  std::vector<snu::KFatJet> out_fatjets;
  std::vector<snu::KGenJet> out_genjets;
  std::vector<snu::KTruth> out_truth;
  snu::KEvent out_event;
  snu::KTrigger out_trigger;


  int nevents;
  int pass_eventcut;
  int pass_vertexcut;

  ClassDef ( SKTreeMaker, 3);
};
#endif
