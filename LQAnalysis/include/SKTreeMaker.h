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
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );


 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
  std::vector<snu::KJet> out_jets;
  snu::KEvent out_event;
  snu::KTrigger out_trigger;


  ClassDef ( SKTreeMaker, 1);
};
#endif
