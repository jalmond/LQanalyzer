#ifndef LQController_h
#define LQController_h

/// standard includes
#include <set>
#include <vector>

// Local include(s):
#include "LQLogger.h"
#include "LQError.h"
#include "SNUTreeFiller.h"

//Forward declaration
class TH1F;
class TChain;

class LQController  {

 public:
  
  //// constructors
  LQController();
  virtual ~LQController();

  enum dataType {NOTSET, data, mc};

  /// Initialise the analysis from the configuration file
  void Initialize() throw( LQError );  
  void ExecuteCycle()throw( LQError );

  /// Useful for checking performance
  void GetMemoryConsumption(TString label);
  double GetVirtualMemoryConsumption();
  double GetPhysicalMemoryConsumption();
  void FillMemoryHists(std::string binname);

  /// List of functions to configure job
  void SetTreeName(TString treename);
  void SetCycleName(TString cyclename);
  void AddLibraries(TString libname);  
  void SetJobName(TString name);
  void SetInputList(TString list);
  void SetFullInputList(TString list);
  void SetDataType(TString settype);
  void SetLogLevel(TString level);
  void SetName(TString name, Int_t version, TString dir);
  void SetTargetLuminosity(float lumi);
  void SetEffectiveLuminosity(float lumi);
  void SetMCCrossSection(float xsec);
  void SetTotalMCEvents(int total_mc_ev);
  void SetNEventsToProcess(int nevents);
  void SkipEvents(int ev_to_skip);
  void SetOutPutStep( int step);
  void SetDataPeriod(TString period);
  void SetChannel(TString channel);
  void SetInputChain(TChain* ch);

  /// Other class functions
  void RunEvent(Long64_t ev);
  std::pair< Double_t, Double_t> GetTotalEvents() throw(LQError);
  float CalculateWeight() throw (LQError);
  
 private:
  TTree*  chain;
  dataType inputType;
  TString outputLevelString;
  TString CycleName;
  TString jobName;
  TString treeName;
  TString filelist;
  TString fullfilelist;
  TString completename;

  mutable LQLogger m_logger;
  
  float target_luminosity;
  float sample_crosssection;
  float effective_luminosity;
  double n_total_event;
  int nevents_to_process;
  bool m_isInitialized;
  int n_ev_to_skip;
  
  std::vector<TString> v_libnames;
  std::vector<Long64_t> list_to_run;
  Double_t total_events_beforeskim;
  Double_t total_events_afterskim;
  int output_step;
  TString channel;
  TString k_period;
  
  TH1F* h_timing_hist;
  TH1F* h_virtmemory_hist;
  TH1F* h_physicalmemory_hist;
};
#endif
