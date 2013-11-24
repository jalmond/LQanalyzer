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
#include "AnalysisBase.h"
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
#include "Reweight.h"
#include "SNUTreeFiller.h"
#include "EventBase.h"
#include "LQEvent.h"


class Analyzer : public SNUTreeFiller {

 public:
  enum histtype  {muhist, elhist, jethist, sighist};
  enum jobtype {ZTest,HNee, HNmm, HNFakeBkgmm, HNFakeBkgee};

 private:
  static const Bool_t debug = false; 
  

 public:
  
  Double_t *****doubleFake; Double_t ***singleFake; Double_t *****doubleANDsingleFake;
  Double_t *finalbkg1, *finalbkgerror1, *finalbkg2, *finalbkgerror2, *realsingle, *realsingleerror, *realdouble, *realtotal, *doubletosingle, *errdoubletosingle;
  Double_t jets2mass, triggerweight;
  Int_t tempCharge, index;
  UInt_t dataType;
  Double_t Wcand_tmp, Wcand, METcut;

  Bool_t VETO, SINGLEFAKE, DOUBLEFAKE, b_found, muonbad , isData;

  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;

 public:
  static const Bool_t MC_pu = true; 

  EventBase* eventbase;
  
  Reweight *reweightPU;
  UInt_t numberVertices;
  TString completename;

  Bool_t *goodVerticiesB;
  TDirectory *Dir;
  
  map<TString, TH1*> maphist;
  TH2F* FRHist;

  Double_t target_lumi  ;//= 19762.501;
  TFile *outfile;
  
  Long64_t entrieslimit;
  Double_t METx, METy, MET, dr, MCweight, weight;
  Int_t prescale;
  
  double testdouble;

  //// Making cleaver hist maps
  map<TString, SignalPlots*> mapCLhistSig;
  map<TString, ElectronPlots*> mapCLhistEl;
  map<TString, MuonPlots*> mapCLhistMu;
  map<TString, JetPlots*> mapCLhistJet;

  //// constructors
  Analyzer();
  Analyzer(jobtype jtype);
  ~Analyzer();

  
  // special function

  /// Declare an output variable                                                                                                                                               
  template< class T >
     TBranch* DeclareVariable( T& obj, const char* name,
                               const char* treeName = 0 ) ;

  /// global variable to set in constructor to tell code which Loop to run and which variables to set.
  jobtype _jtype;
  
  /// Main Event Loops
  void Run(TTree* tree);
  void Run();
  void Loop();
  void CloseFiles();
  void TestLoop();
  void HNmmLoop();
  void ExecuteEvent();
  void InitialiseCycle();
  void EndCycle();
  void Initialise(jobtype jtype);
  TDirectory* GetTemporaryDirectory(void) const;
  void CheckFile(TFile* file);
  void ClearOutputVectors();
  //// Plotting
  TH1* GetHist(TString hname);
  void FillHist(TString histname, float value, float w );
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
  void SetName(TString name, Int_t versio, TString dir="NULL");
  void SetEvtN(Long64_t events);
  void NEvents(Long64_t n_events);
  bool PassBasicEventCuts();
  void OutPutEventInfo(int entry, int step);
  void SetUpEvent(int kentry);

};
#endif
