#ifndef HNDiLepton_h
#define HNDiLepton_h

#include "AnalyzerCore.h"

class HNDiLepton : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HNDiLepton();
  ~HNDiLepton();

  enum FUNC {
    VALIDATION=0,
    ANALYSIS=1, 
    OPT=2,
    CUTFLOW=3
  };

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void DoCutFlow(float w);

  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillEventCutFlow(int cf,TString cut,  float weight);
  void FillEventCutFlow(TString cut, TString label , float weight);

  void MakeControlPlotsMM(int method, TString methodtag, float w)throw( LQError );
  void MakeControlPlotsEE(int method, TString methodtag, float w)throw( LQError );
  void MakeControlPlots(int method, TString methodtag, float w)throw( LQError );
  void MakeValidationPlots(float w);

  void RunAnalysis(TString plottag, TString tightelid, TString vetoelid, TString looseelid);

  float WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip);  
  float IsDiLep(std::vector<snu::KElectron> electrons);
  bool LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts, TString opt);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int bjetwp, float evmet, bool runchargeflip , std::vector<float> cuts,  TString opt);
  bool MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);

  bool CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons,  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets,  TString name, float w);


  void FillTriggerEfficiency(TString cut, float w, TString label,  std::vector<TString> list);
  void CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets);

  float GetTightWeight();
  float  GetMediumWeight();
  void GetSSSignalEfficiency(float w);
  void GetOSSignalEfficiency(float w);
  void GetTriggEfficiency();
  void SignalValidation();
  void RunAnalysis();
  void OptimiseID(bool isss);
  

  void counter(TString cut, float w);

 private:

  FUNC functionality ;
  bool _ee_channel;
  bool _mm_channel;


  float k_met;
  float k_met_st;
  float k_mumumass;
  float k_lljj_lowmass;
  float k_l1jj_lowmass;
  float k_l2jj_lowmass;
  float k_llj_lowmass;
  float k_jj_lowmass;
  float k_lljj_highmass;
  float k_l1jj_highmass;
  float k_l2jj_highmass;
  float k_llj_highmass;
  float k_jj_highmass;
  float k_st;
  float k_ht;
  float k_weight;
  float k_mu1pt;
  float k_mu2pt;
  float k_j1pt;
  float k_contramass_lowmass;
  float k_contramass_highmass;
  float k_lldr ;
  float k_minljdR;
  float k_awayjetminDR;
  float k_mindRjj;
  int k_njets;
  int k_nfatjets;
  int k_nbjet_l;
  int k_nbjet_m;
  int k_nbjet_t;


  std::map<TString, float> mapcounter;
  map<TString, pair<pair<TString,TString>, pair<float,TString> >  > fake_hists;
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
 

  ClassDef ( HNDiLepton, 1);
};
#endif
