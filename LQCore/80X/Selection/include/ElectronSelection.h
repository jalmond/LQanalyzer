#ifndef ElectronSelection_h
#define ElectronSelection_h

#include "KElectron.h"
#include "LQEvent.h"
#include "BaseSelection.h" 

class ElectronSelection : public BaseSelection {

 public:
  
  Bool_t ElectronID;


  ElectronSelection(LQEvent ev);
  ~ElectronSelection();

  ElectronSelection& operator= (const ElectronSelection& obj);
  ElectronSelection(const ElectronSelection& bs);

  //// For Jiwhan and sktree maker
  void Selection(std::vector<snu::KElectron>& leptonColl, TString Option="");
  void BasicSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void SkimSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  float IsoCutValue(snu::KElectron electron,TString elid, TString isotype);

  
  /// New function., calls custim id in SKTree classes
  void SelectElectrons(std::vector<snu::KElectron>& leptonColl, TString elid,  TString Option, double ptcut, double etacut);
  bool ElectronPass(snu::KElectron el, TString elid, double ptcut=-999., double etacut=-999.);
  
  bool FillIDList(TString IDlabel, TString IDlabelref, std::vector<TString>& IDlist);

  //// ID custom functions used by Selection(std::vector<snu::KElectron>& leptonColl, TString Option) function
  bool PassUserID(snu::KElectron el,TString id, TString el_id, bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b, double dzmax_e, double dxysigmax,double dxysigmin, double IP3Dmax, double IP3Dmin);
  bool PassID(snu::KElectron el, ID id);
    
};
#endif
