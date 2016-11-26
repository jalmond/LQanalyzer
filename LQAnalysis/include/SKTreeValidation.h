#ifndef SKTreeValidation_h
#define SKTreeValidation_h

#include "AnalyzerCore.h"
class SKTreeValidation : public AnalyzerCore {

 public:
  //// constructors                                                                                                                                                             
  SKTreeValidation();
  ~SKTreeValidation();

  /// Functions from core
  virtual void BeginCycle() throw( LQError );
  virtual void BeginEvent()throw( LQError );
  virtual void ExecuteEvents()throw( LQError );
  virtual void EndCycle()throw( LQError );
  virtual void ClearOutputVectors()throw( LQError );
  
  void InitialiseAnalysis() throw( LQError );
  void MakeHistograms();
  void MakeDiMuonValidationPlots(TString muid, float w, float pu_weight,  std::vector<TString> trignames,TString elid, TString jetid, TString tag);
  void MakeMuonValidationPlots(TString muid, float w, float pu_weight,  std::vector<TString> trignames,TString elid, TString jetid, TString tag);
  void MakeElectronValidationPlots(TString elid, float w, float pu_weight,  std::vector<TString> trignames,TString muid, TString jetid, TString tag);
  
  void MakeDiElectronValidationPlots(TString elid, float w, float pu_weight,  std::vector<TString> trignames,TString muid, TString jetid, TString tag);
  
  void MakeElMuonValidationPlots(TString id, float w, float pu_weight,  std::vector<TString> trignames,TString elid, TString jetid, TString tag);
  

 private:
  
  //
  // The output variables 
  //
  /// Vectors for output objetcs
  std::vector<snu::KMuon> out_muons;
  std::vector<snu::KElectron> out_electrons;


  ClassDef ( SKTreeValidation, 1);
};
#endif
