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
  

  void FillPreselection(int nfake, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  float ll_weight, std::vector<TString> trig,  float pt1, float pt2);

  
  bool Preselection(TString label, std::vector<snu::KMuon> muons, std::vector<snu::KMuon> muons_veto, std::vector<snu::KElectron> electrons,std::vector<snu::KJet> alljets, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, float ll_weight, std::vector<TString> trigs, float pt1, float pt2);

  float PreselWeight(float mmweight, std::vector<snu::KMuon> muons, TString id, bool passtrig);				
  
  float MMWeight(std::vector<snu::KMuon> muons,TString id, bool passtrig);
  float EEWeight( std::vector<snu::KElectron> electrons, TString id);
  float EMWeight( std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons,TString elid, TString muid);

  void counter(TString cut, float w);

 private:

  FUNC functionality ;


  std::map<TString, float> mapcounter;
 

  ClassDef ( HN_pair_all, 1);
};
#endif
