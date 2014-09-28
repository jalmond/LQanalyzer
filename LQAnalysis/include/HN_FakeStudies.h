#ifndef HN_FakeStudies_h
#define HN_FakeStudies_h

#include "AnalyzerCore.h"


class HN_FakeStudies : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HN_FakeStudies();
  ~HN_FakeStudies();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();


 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

  float k_met, k_eemass, k_eejjmass, k_e1jjmass, k_e2jjmass,  k_st, k_ht;
  int k_njet, k_nbjet_l, k_nbjet_m, k_nbjet_t;
  float k_weight, k_el1pt, k_el2pt, k_j1pt, k_jjmass;

  ClassDef ( HN_FakeStudies, 1);
};
#endif
