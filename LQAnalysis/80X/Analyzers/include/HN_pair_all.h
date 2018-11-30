#ifndef HN_pair_all_h
#define HN_pair_all_h

#include "AnalyzerCore.h"

class HN_pair_all : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HN_pair_all();
  ~HN_pair_all();

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
  void InitialiseAnalysis() throw( LQError );

  
  //// analysis functions
  float MMWeight(TString syst_label, std::vector<snu::KMuon> muons,TString id, bool passtrig);
  float EEWeight(TString syst_label,  std::vector<snu::KElectron> electrons, TString id);
  float EMWeight(TString syst_label,  std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons,TString elid, TString muid);

  std::vector<snu::KParticle> RecoPairN(std::vector<KLepton> lepptrs, vector<snu::KFatJet> fatjets, vector<snu::KJet> jets);
  bool RemoveFlavourMixing();
  void ExecuteEventFromSyst(TString systlabel, TString el_syst, TString mu_syst, TString ak4_syst,  TString ak8syst);

  
  void MakeHistograms();
  void counter(TString cut, float w);

 private:

  FUNC functionality ;
  bool _ee_channel;
  bool _mm_channel;
  bool _m_channel;
  bool _e_channel;
  bool _em_channel;

  std::map<TString, float> mapcounter;
 

  ClassDef ( HN_pair_all, 1);
};
#endif
