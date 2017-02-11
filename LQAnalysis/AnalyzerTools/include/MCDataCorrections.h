#ifndef MCDataCorrections_h
#define MCDataCorrections_h

#include <vector>
#include <string>
#include <map>
#include <sstream>  
#include <fstream>      // std::ifstream
#include <iostream> 

class TString;
class Reweight;

/// SNU codes
#include "KMuon.h"
#include "KElectron.h"
#include "KPhoton.h"
#include "KGenJet.h"
#include "KJet.h"
#include "KFatJet.h"
#include "KTruth.h"
#include "KTrigger.h"
#include "KEvent.h"

/// rochester corrections
#include "rochcor2016/RoccoR.h"

// ROOT 
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TGraphAsymmErrors.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
class MCDataCorrections{

 public:
    
  MCDataCorrections();
  MCDataCorrections(bool isdata);
  ~MCDataCorrections();

  void SetMCPeriod(int mcperiod);
  void SetIsData(bool isdata);
  void PrintSummary();


  TH2F* GetCorrectionHist(TString label);
  bool CheckCorrectionHist(TString label);
  TGraphAsymmErrors* GetCorrectionGraph(TString label);
  bool CheckCorrectionGraph(TString label);
  void FillCorrectionHist(std::string label, std::string dirname, std::string filename, std::string histsname, std::string histtype);
  void FillCorrectionHists();
  void CheckFile(TFile* file);
  TDirectory*   getTemporaryDirectory(void) const;


  /// Lepton Scale Factors
  double ElectronScaleFactor( TString  elid, std::vector<snu::KElectron> el, int sys=0);
  double ElectronRecoScaleFactor(std::vector<snu::KElectron> el);
  double MuonScaleFactor(TString  muid, std::vector<snu::KMuon> mu, int sys=0);
  double MuonISOScaleFactor(TString muid, std::vector<snu::KMuon> mu,int sys=0);
  double MuonTrackingEffScaleFactor(std::vector<snu::KMuon> mu);  

  /// Trigger 
  double TriggerScaleFactor( std::vector<snu::KElectron> el, std::vector<snu::KMuon> mu, TString trigname, int direction=0);


  /// Other corrections
  float PileupWeightByPeriod(snu::KEvent ev);
  float UserPileupWeight(snu::KEvent ev);
  float CatPileupWeight(snu::KEvent ev, int syst=0);
  void CorrectMuonMomentum(std::vector<snu::KMuon>& k_muons, float genpt= -999.);

  std::vector<TLorentzVector> MakeTLorentz( std::vector<snu::KElectron> el);
  std::vector<TLorentzVector> MakeTLorentz( std::vector<snu::KMuon> mu);
  std::vector<TLorentzVector> MakeTLorentz( std::vector<snu::KJet> jet);
  std::vector<TLorentzVector> MakeTLorentz( std::vector<snu::KFatJet> jet);

 private:
  
  bool corr_isdata;
  double k_mcperiod;

  std::map<TString, TH2F*>  CorrectionMap;
  std::map<TString, TGraphAsymmErrors*>  CorrectionMapGraph;
  Reweight *reweightPU;
  RoccoR *rc;

};
#endif
