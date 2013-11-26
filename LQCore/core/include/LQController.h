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

  /// Initialise the analysis from the configuration file
  virtual void Initialize() throw( LQError );  
  virtual void ExecuteCycle()throw( LQError );
  
  void SetTreeName(TString treename);
  void SetCycleName(TString cyclename);
  void AddLibraries(TString libname);  
  void SetJobName(TString name);
  void SetInputList(TString list);
  
  void SetNEventsToProcess(int nevents);
  void SetLogLevel(TString level);
  void SetName(TString name, Int_t version, TString dir);
  void SetTargetLuminosity(float lumi);
  void SetEffectiveLuminosity(float lumi);
  float CalculateWeight();

  void SetMCCrossSection(float xsec);
  void SetTotalMCEvents(TString path);
  void SetTotalMCEvents(int total_mc_ev);
  
 private:

  TString outputLevelString;
  TString CycleName;
  TString jobName;
  TString treeName;
  TString filelist;
  TString completename;

  mutable LQLogger m_logger;
  
  int entrieslimit;
  
  float target_luminosity;
  float sample_crosssection;
  float effective_luminosity;

  int n_total_event;
  Int_t file_version;
  int nevents_to_process;

  bool m_isInitialized;
  std::vector<TString> v_libnames;
};
#endif
