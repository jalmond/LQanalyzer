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
  bool IsTight(snu::KElectron el,  double jetrho , double dxy, double biso, double eiso,  bool usetight);

  void GetRealEfficiency(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, std::vector<snu::KMuon> muons, double w, float interval,TString tag, double dxy, double biso, double eiso,  bool usetight);

  void GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag, float w);
  void GetHSTRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag);
 private:
  
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

  int n_17_pass;
  int n_17_17_jet_pass;
  int n_17_jet_pass;
  
  ClassDef ( FakeRateCalculator_El, 1);
};
#endif
