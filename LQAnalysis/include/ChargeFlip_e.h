#ifndef ChargeFlip_e_h
#define ChargeFlip_e_h

#include "AnalyzerCore.h"
class ChargeFlip_e : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  ChargeFlip_e();
  ~ChargeFlip_e();

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


  ClassDef ( ChargeFlip_e, 1);
};
#endif
