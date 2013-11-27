#ifndef LQController_h
#define LQController_h

/// standard includes
#include <set>
#include <vector>

// Local include(s):
#include "LQLogger.h"
#include "LQError.h"
#include "SNUTreeFiller.h"

class LQController  {

 public:
  
  //// constructors
  LQController();
  virtual ~LQController();

  enum dataType {NOTSET, data, mc};

  /// Initialise the analysis from the configuration file
  virtual void Initialize() throw( LQError );  
  virtual void ExecuteCycle()throw( LQError );
  virtual void GetMemoryConsumption(TString label);


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
  void RunEvent(Long64_t ev);
  /// Other class functions
  std::pair< Double_t, Double_t> GetTotalEvents() throw(LQError);
  float CalculateWeight() throw (LQError);
  
 private:
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
  Int_t file_version;
  int nevents_to_process;

  bool m_isInitialized;
  int entrieslimit;
  int n_ev_to_skip;
  
  std::vector<TString> v_libnames;
  std::vector<Long64_t> list_to_run;
  Double_t total_events_beforeskim;
  Double_t total_events_afterskim;
};
#endif
