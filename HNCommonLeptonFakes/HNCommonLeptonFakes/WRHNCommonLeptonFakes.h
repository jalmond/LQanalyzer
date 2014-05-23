#ifndef HNCommonLeptonFakes_H
#define HNCommonLeptonFakes_H

// STL include(s):                                                                                                                                                                   
#include <vector>
#include <map>
#include <string>

// Forward declaration(s):                                                                                                                                                           

#include "TString.h"
#include <vector>
#include <map>
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TLorentzVector.h"

class HNCommonLeptonFakes {

 public:
  /// Destructor
  ~HNCommonLeptonFakes();

  /// constructor
  HNCommonLeptonFakes(std::string path = "../share/", bool usegev=false);

//Declaration of the function

  /// Function to return event weight with error

  /** get temporary directory                                                                                                                                                        
   *                                                                                                                                                                                
   */
  TDirectory*
    getTemporaryDirectory(void) const;



  float get_dilepton_mm_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> jets, bool isT1, bool isT2 ,bool isHF1, bool isHF2, bool useGeV, bool oldrates);

  float get_dilepton_emu_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electron, std::vector<TLorentzVector> jets,float met, bool isT1, bool isT2 ,bool isHF2, bool iselconv, bool _el1_primarytriggerpass, bool _el1_secondarytriggerpass,bool _mu1_primarytriggerpass,bool _mu1_secondaytriggerpass,bool useGeV, bool usekirill);

  float get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, bool isel1tight, bool isel2tight);
  

  float getFakeRate_muons(int sys, bool isHF,float pt, int njets, float eta, bool overlap, TString region, bool usefit = false);
  float getFakeRate_muonsold(int sys, bool isHF,float pt, int njets, float eta, bool overlap, TString region);
  float getFakeRate_electrons_kirill(int sys,float pt, float eta, int njet, bool triggerpass, bool isconversion);
  float getFakeRate_electrons_emu_lou(int sys, float muon_pt, float el_pt, float el_eta, bool muon_trigpass, bool primarytrigger_el,  bool secondarytrigger_el ,bool el_conv);

  std::pair<float,float> getFakeRate_electrons_ee_lou(int sys, float lep1_pt, float lep2_pt, float lep1_eta, float lep2_eta, bool primarytrigger_lep1,  bool primarytrigger_lep2, bool secondarytrigger_lep1, bool secondarytrigger_lep2, bool el1_conv, bool el2_conv);


  float getEfficiency_muon(int sys,float pt, float eta, int njets, TString region);
  float getEfficiency_electron_kirill(int sys, float pt,float eta, int njet, bool triggerpass);
  float getEfficiency_electron_emu_lou(int sys, float muon_pt, float el_pt, float el_eta, bool muon_trigmatch, bool primarytrigger_el, bool secondarytrigger_el);
  
  std::pair<float,float> getEfficiency_electron_ee_lou(int sys, float lep1_pt, float lep2_pt, float lep1_eta, float lep2_eta, bool primarytrigger_lep1,  bool primarytrigger_lep2, bool secondarytrigger_lep1, bool secondarytrigger_lep2);

 

  void APPLY_scalefactor(bool applysf) ;
  float GetFitfakeRate(float pt, TString histname);
  float getHSTEfficiency(int sys, float pt, float eta, int njets, TString region);
  //  float getHSTFakeRate(int sys, bool isHF,float pt,float eta, int njets, bool nearjet, TString region);
  float getHSTFakeRate(int isys, bool isHF,float pt,float eta, int njets, bool nearjet, TString region);

  float getHSTFakeRate_sm(int sys, float pt, bool isclose, TString cut);
  float HSTWeight_sm(int sys, float pt, bool close_to_jet,TString cut);
  
  float HSTWeight(int sys, TLorentzVector muons, std::vector<TLorentzVector> jets, bool isHF, TString region);

  float HSTWeightF(int sys, TLorentzVector muons, std::vector<TLorentzVector> jets, bool isHF, TString region);

  float HSTWeightR(int sys, TLorentzVector muons, std::vector<TLorentzVector> jets, TString region);

  float HSTWeight_Rsm(int sys, float pt, int njets, TString cut);
  float getHSTEfficiency_sm(int sys, float pt, int njets, TString cut);

  /// Function to calculate the event weight from the muon efficiencies
  float CalculateDiLepMMWeight(float r1, float f1, float r2, float f2, bool t1, bool t2 );
  
  //Incase we want single muon event weight
  double lepton_weight(bool loose, double r, double f);
  

  void CheckFile(TFile* file);
  /// Function to reset all variable in the class
  void ResetValues();
  void NullTotals();

  /// Function called to close root file used to read histograms
  void closefile();

  /// Maps for storing histograms in the rootfile
  std::map<TString,TH1*> _EfficiencyMap;
  std::map<TString,TH2*> _2DEfficiencyMap;
  std::map<TString,TEfficiency*> _TEEfficiencyMap;
  std::map<TString,TH1*> _EfficiencyMapHST;
  std::map<TString,TH2*> _2DEfficiencyMapHST;


  /// Function to fill maps , null variable and set up conditions for running algorithm
  void InitialiseFake();

  /// Function to exit code if tryng to access a  non existing histogram
  void NoHist(TString hist, TString function = "");

  /// Initialises histograms filled by FillHists
  void SetHists();
  void SetHists(TString hist);
 
  /// Fills histgrams with TLorentz vectors passed to tool and event weights calculated
  void prepFillHists(float w, float mu1pt, float mu2pt, bool tight1, bool tight2);
  void FillHists(TString cut);

  // Function to apply a systematic shift in fakes rates
  void ApplyFakeSystematic(int type);
  void ApplyRealSystematic(int type);
  void ApplySF(int type);

  // Function to return histograms filled in tool
  TH1* GetHist(bool weighted, TString cut);
 
  /// Adds event by event info to countes
  void AddToTotals(float w,std::pair<float,float> err, bool mu1tight, bool mu2tight);


 private:
  /// vector for storing FakeCR strings
  std::vector<TString> regions;
  std::vector<TString> ch_regions;
  
  /// path to root file
  std::string path_to_root_files;  
  
  /// class string for fake CR used as the central value
  TString defCR;
  
  /// bool to set output messsage level
  bool m_debug;

  /// bool to correctly set pt/ht to GeV needed to acces correct bin in root file
  bool useGeV;
  
  int fsys;
  int rsys;

  bool apply_scalefactor;

  bool dosystematic;

  /// Event counter
  int nevent;

  /// Map for calculating systematics
  std::map<TString,float> SystMap;
  
  ///Map for plotting cuts
  std::map<TString, std::pair<TH1*,TH1*> > CutHists;

  /// variables used to fill hists
  float _percentageFsys;
  float _percentageRsys;
};
#endif
