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
  bool IsTight(snu::KElectron el,  double jetrho , double dxy, double biso, double eiso,  bool usetight);


  void GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets,std::vector<snu::KJet> alljets, TString tag, double w);
  void GetHSTRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag);
  
  void MakeMCFakeratePlots(TString label, bool pass_single_trigger, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, double w);
  void MakePlotsMCAwaJetPt(TString label,float awayjetptcut, std::vector<snu::KElectron>, std::vector<snu::KJet> jets , std::vector<snu::KJet> alljets, double w);

  
  void MakeMCPlots(TString label, snu::KElectron electron, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, double w);
  float GetPrescale( std::vector<snu::KElectron> electrons, bool passlow, bool passhigh);
  bool  UseEvent(std::vector<snu::KElectron> electrons,  vector<snu::KJet> jets, float pcut,float precale_weight, float w);
  bool  UseEventAllMT(std::vector<snu::KElectron> electrons,  vector<snu::KJet> jets, float pcut,float precale_weight, float w);

  void MakeFakeRatePlots(TString label, std::vector<snu::KElectron> electrons_tight, std::vector<snu::KElectron> electrons,   std::vector <snu::KJet> jets, std::vector<snu::KJet> alljets,  float precale_w, float w);



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
