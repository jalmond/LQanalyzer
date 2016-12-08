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
  
  void Selection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);		 
  void BasicSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void SkimSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  // POG 
  void PogID(std::vector<snu::KElectron>& leptonColl, ID elid);
  void SelectElectrons(std::vector<snu::KElectron>& leptonColl,ID id, float ptcut=-999., float etacut=-999.);
  void SelectElectrons(std::vector<snu::KElectron>& leptonColl,TString id, float ptcut=-999., float etacut=-999.);
  
  
  //// IDS
  bool PassUserID(TString id,snu::KElectron el);
  bool PassID(snu::KElectron el, ID id);
    
};
#endif
