#ifndef Analyzer_h
#define Analyzer_h

/// standard includes
#include <set>


/// local includes
// Selection
#include "ElectronSelection.h"
#include "MuonSelection.h"
#include "JetSelection.h"
#include "GenSelection.h"
#include "SelectionFunctions.h"

// Plotting
#include "OtherFunctions.h"
#include "ElectronPlots.h"
#include "MuonPlots.h"
#include "JetPlots.h"
#include "SignalPlots.h"

// SNUTree
#include "KParticle.h"
#include "KJet.h"
#include "KMuon.h"
#include "KEvent.h"

// other
#include "Reweight.cc"
#include "SNUTreeFiller.h"
#include "EventBase.h"
#include "LQEvent.h"


class Analyzer : public SNUTreeFiller {

 public:
  enum histtype  {muhist, elhist, jethist, sighist};
  enum jobtype {ZTest,HNee, HNmm, HNFakeBkgmm, HNFakeBkgee};

 private:
  static const Bool_t debug = false; 
  
  //  static const Double_t integratedlumi = 1.927196301; HLT_Mu5,8
  //  static const Double_t integratedlumi =  1.483873; HLT_Mu12
  //  static const Double_t integratedlumi = 22.945019; HLT_Mu17
  //  static const Double_t integratedlumi = 83.483; HLT_Mu24
  //  static const Double_t integratedlumi = 123.9391;
  const Double_t Mass_Z;
  const Double_t Mass_W;


 public:
  Double_t *****doubleFake; Double_t ***singleFake; Double_t *****doubleANDsingleFake;
  Double_t *finalbkg1, *finalbkgerror1, *finalbkg2, *finalbkgerror2, *realsingle, *realsingleerror, *realdouble, *realtotal, *doubletosingle, *errdoubletosingle;
  Double_t jets2mass, triggerweight;
  Int_t tempCharge, index;
  UInt_t dataType;
  Double_t Wcand_tmp, Wcand, METcut;

  Bool_t VETO, SINGLEFAKE, DOUBLEFAKE, b_found, muonbad , isData;

 public:
  static const Bool_t MC_pu = true; 

  EventBase* eventbase;
  
  ReweightPU *reweightPU;
  UInt_t numberVertices;
  TString completename;

  Bool_t *goodVerticiesB;
  TDirectory *Dir;
  
  map<TString, TH1*> maphist;
  TH1F* FRHist;

  Double_t target_lumi  ;//= 19762.501;
  TFile *outfile;
  
  Long64_t entrieslimit;
  Double_t METx, METy, MET, dr, MCweight, weight;
  Int_t prescale;
  


  //// Making cleaver hist maps
  map<TString, SignalPlots*> mapCLhistSig;
  map<TString, ElectronPlots*> mapCLhistEl;
  map<TString, MuonPlots*> mapCLhistMu;
  map<TString, JetPlots*> mapCLhistJet;

  //// constructors
  Analyzer();
  Analyzer(jobtype jtype);
  ~Analyzer();

  
  /// global variable to set in constructor to tell code which Loop to run and which variables to set.
  jobtype _jtype;
  
  /// Main Event Loops
  void Run();
  void Loop();
  void TestLoop();
  void HNmmLoop();
 
  //// Plotting
  TH1* GetHist(TString hname);
  //  TH2* Get2Hist(TString hname);
  void FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double weight);
  void FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KJet> jets,double weight);
  void FillCLHist(histtype type, TString hist, snu::KEvent ev, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double weight);
  void FillCLHist(histtype type, TString hist, vector<snu::KMuon> muons , double weight);
  void FillCLHist(histtype type, TString hist, vector<snu::KElectron> electrons , double rho, double weight);
  void FillCLHist(histtype type, TString hist, vector<snu::KJet> jets , double weight);  
  void MakeCleverHistograms(histtype type, TString clhistname );
  void MakeHistograms(jobtype jtype);

  /// File related
  void OpenPutputFile();
  void WriteHists();
  void WriteCLHists();

  //// Event related
  void EndEvent();
  double SetEventWeight();
  bool PassTrigger(std::vector<TString> list, int& prescale);
  void SetWeight(Double_t CrossSection, Double_t nevents);
  void SetTargetLumi(Double_t lumi);
  void SetEffectiveLumi(Double_t lumi);
  void SetName(TString name, Int_t version);
  void SetEvtN(Long64_t events);
  void NEvents(float n_events);
  bool PassBasicEventCuts();
  void OutPutEventInfo(int entry, int step);
  void SetUpEvent(int kentry);

};
#endif
