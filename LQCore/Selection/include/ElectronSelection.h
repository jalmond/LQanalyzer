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
  
  //// HN analysis selection
  void HNTightElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void HNLooseElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void HNVetoElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  

  //// IDS
  bool PassUserID(ID id,snu::KElectron el,  double rho, bool m_debug= false);
  bool PassUserID_EGamma2012 ( ID id, snu::KElectron el , double rho, bool m_debug= false);
  bool PassUserID_ECALFiducial (snu::KElectron el);
  bool PassUserID_MVA (snu::KElectron el, bool trig);
  bool PassUserID_FakeLoose2012 (snu::KElectron el, double jetrho , bool m_debug=false);

    
};
#endif
