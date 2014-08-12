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
#include "TH2F.h"
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



  float get_dilepton_mm_eventweight(std::vector<TLorentzVector> muons, bool isT1, bool isT2);

  float get_dilepton_em_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electron,int njets, bool ismu1tight, bool isel1tight);

  float get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight);
  float get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut,int nbjet, float ht);
  float get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut);
  float get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut, int eventtype, bool user1);
  

  float getFakeRate_muon(int sys, float pt,  float eta);
  float getEfficiency_muon(int sys,float pt, float eta);

  float getFakeRate_electron(int sys, float pt,  float eta);
  float getEfficiency_electron(int sys,float pt, float eta);

  float getFakeRate_electron(int sys, float pt,  float eta, TString cut);
  float getEfficiency_electron(int sys,float pt, float eta, TString cut);
 

  void APPLY_scalefactor(bool applysf) ;


  /// Function to calculate the event weight from the muon efficiencies
  float CalculateDiLepMMWeight(float r1, float f1, float r2, float f2, bool t1, bool t2 );
  float CalculateDiLepMMWeight(float r1, float f1, float r2, float f2, bool t1, bool t2 , int eventtype);
  
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
  std::map<TString,TH2F*> _2DEfficiencyMap;
  std::map<TString,TEfficiency*> _TEEfficiencyMap;
  std::map<TString,TH1*> _EfficiencyMapHST;
  std::map<TString,TH2F*> _2DEfficiencyMapHST;


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
