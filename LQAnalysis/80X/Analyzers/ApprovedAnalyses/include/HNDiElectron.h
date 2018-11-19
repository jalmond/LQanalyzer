#ifndef HNDiElectron_h
#define HNDiElectron_h

#include "AnalyzerCore.h"

class HNDiElectron : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  HNDiElectron();
  ~HNDiElectron();

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

  void FillIDEff(snu::KElectron el, TString label);

  int MatchedLeptonJets(std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, std::vector<snu::KElectron> electrons, TString label , std::vector<int> ijets );
  vector<int>   FillTruthPlots(std::vector<snu::KJet> jets, std::vector<snu::KElectron> electrons, TString label);
  vector<int>  GetTruthJets();
  void FillEfficiency(TString label, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, float w);

  void FillLowMassBins(bool fill, int mode, TString label, vector<snu::KElectron> els,  vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  int nbjet_m, float ll_weight, std::vector<TString> trig,float pt1, float pt2);
		       
  void FillHighMassBins(bool fill, int mode, TString label, vector<snu::KElectron> els, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  int nbjet_m,  float ll_weight, std::vector<TString> trig,float pt1, float pt2);
			

  void FillLowMass(bool fill, int mode, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, std::vector<TString> trig , float pt1, float pt2);
		   
  
  void FillHighMass(bool fill, int mode, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, std::vector<TString> trig , float pt1, float pt2);



  void RunEE(int mode , TString label, std::vector<snu::KElectron> electrons, std::vector<snu::KElectron> electrons_veto,std::vector<snu::KMuon> mu, std::vector<snu::KJet> alljets, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, std::vector<snu::KJet> tjets,float ee_weight ,std::vector<TString> ee_trig, float pt1, float pt2);
  void RunLL(int mode,TString channel, TString label, std::vector<snu::KMuon> muons, std::vector<snu::KMuon> muons_veto,std::vector<snu::KElectron> el, std::vector<snu::KElectron> el_veto, std::vector<snu::KJet> alljets, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, std::vector<snu::KJet> tjets,float ll_weight ,std::vector<TString> ll_trig, float pt1, float pt2);
			 

  void GetOptimisationID( std::vector<snu::KElectron> electrons_veto, std::vector<snu::KMuon> muons, std::vector<snu::KJet> alljets, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, std::vector<TString> trig,  float pt1, float pt2);
			  
  void FillMCFakes(TString label,vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,   std::vector<TString> trig, float ll_weight, TString looseID,  TString tightID);

  void FillPreselection(int nfake, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electron_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  float ll_weight, std::vector<TString> trig,  float pt1, float pt2);
			

  float PreselWeight(float mmweight, std::vector<snu::KElectron> el, TString id, bool passtrig);

  bool Preselection(TString label, std::vector<snu::KElectron> electrons, std::vector<snu::KElectron> electrons_veto, std::vector<snu::KMuon> muons,std::vector<snu::KJet> alljets, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fatjets, float ll_weight, std::vector<TString> trigs, float pt1, float pt2);
		    
  

  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void FillEventCutFlow(int cf,TString cut,  float weight, TString label);
  void FillEventCutFlow(TString cut, TString label , float weight);

  float WeightCFEvent(std::vector<snu::KElectron> electrons, bool iscf);  
  float IsDiLep(std::vector<snu::KElectron> electrons);
  bool LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts, TString opt);
  bool OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int bjetwp, float evmet, bool runchargeflip , std::vector<float> cuts,  TString opt);
  bool MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);
  bool HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runcf);

  bool CheckSignalRegion( bool isss,  std::vector<snu::KElectron> electrons,  std::vector<snu::KElectron> electrons_veto, std::vector<snu::KJet> jets,  std::vector<snu::KFatJet> fjets, std::vector<snu::KJet> alljets,  TString name, float w, int mode);



  bool PassLowMassBin1(float pt1max, float pt2max,  float mjjmax,float mlljjmin, float mlljjmax, float ml1jjmax, float ml2jjmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet);
  bool PassLowMassBin2(float pt1max, float pt2max, float mlljmax, float ml1jmax, float ml2jmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet);

  bool PassHighMassBin1(float pt1max, float pt2max, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st, bool deb=false);

  bool PassHighMassBin2(float pt1max, float pt2max, float ml2fjmin, float ml2fjmax,   float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets,std::vector<snu::KFatJet> fjets, int nbjet, float met2_st);			  
				      
  bool PassHighMassBin2(float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st);
  bool PassHighMassBin1Window(float pt1min, float pt2min, float ml2jjmax, float ml2jjmin, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st);
			      

  bool PassHighMassBin2Window(float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KElectron> electron,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st);			    
			      

  void FillTriggerEfficiency(TString ptlab,TString cut, float w, TString label,  std::vector<TString> list);
  void CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets);

  float GetTightWeight();
  float  GetMediumWeight();
  void GetSSSignalEfficiency(float w);
  void GetOSSignalEfficiency(float w);
  void GetTriggEfficiency(float ptcut, TString label);
  void SignalValidation();
  void RunAnalysis();
  void OptimiseID(bool isss);

  float MMWeight(std::vector<snu::KMuon> muons,TString id, bool passtrig);
  float EEWeight( std::vector<snu::KElectron> electrons, TString id);
  float EMWeight( std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons,TString elid, TString muid);

  void counter(TString cut, float w);

 private:

  FUNC functionality ;
  bool _ee_channel;
  bool _mm_channel;
  bool _m_channel;
  bool _e_channel;
  bool _em_channel;

  TString _m_tightid;
  TString _m_looseid;
  TString _e_tightid;
  TString _e_looseid;

  float _mm_mll_presel_cut;
  float _ee_mll_presel_cut;
  float _em_mll_presel_cut;

  float _mm_met_presel_cut;
  float _ee_met_presel_cut;
  float _em_met_presel_cut; 


  std::map<TString, float> mapcounter;
  map<TString, pair<pair<TString,TString>, pair<float,TString> >  > fake_hists;
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;
 

  ClassDef ( HNDiElectron, 1);
};
#endif
