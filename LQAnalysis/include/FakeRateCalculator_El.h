#ifndef FakeRateCalculator_El_h
#define FakeRateCalculator_El_h

#include "AnalyzerCore.h"


class FakeRateCalculator_El : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  FakeRateCalculator_El();
  ~FakeRateCalculator_El();

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

  double pf_trk_qflip ; 
  double pf_ms_qflip ; 
  double pf_qflip ; 
  int cnt_trk_qflip ; 
  int cnt_ms_qflip ; 

  double tag_q1, tag_q2 ; 
  int cnt_tag, cnt_qflip ; 

  int tot_evt ; 
  int tot_mumu_evt ; 
  int tot_gold_evt ;

  double trk_qflip, ms_qflip ;
  double qflip_1, qflip_2, qflip ; 

  ClassDef ( FakeRateCalculator_El, 1);
};
#endif
