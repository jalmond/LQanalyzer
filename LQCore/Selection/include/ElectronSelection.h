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
  void HNTightElectronSelection(std::vector<snu::KElectron>& leptonColl,  bool m_debug= false);

  bool HNIsTight(snu::KElectron el,double rho, bool m_debug); /// Calls function below   
  // Main tight function
  bool HNIsTight(snu::KElectron el, double rho, double dxy, double biso, double eiso, bool usetight, bool m_debug= false);   

  void HNLooseElectronSelection(bool usetight,  bool usedxy, float isocut, std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void HNLooseElectronSelection(bool usetight, std::vector<snu::KElectron>& leptonColl,bool m_debug= false);
  void HNLooseElectronSelection(std::vector<snu::KElectron>& leptonColl,bool m_debug= false);
  void HNLooseElectronSelectionWithIPCut(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void HNLooseElectronSelectionWithDiffISO(float isocut, std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  
  void HNVetoElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  //// Top analysis selection
  void TopTightElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void TopLooseElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void TopVetoElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  void TopTightElectronSelectionv1(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void TopVetoElectronSelectionv1(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  bool EgammaPogIsTight(snu::KElectron el,  double rho);


  //// IDS
  bool PassUserID(ID id,snu::KElectron el,  double rho, bool applypog, bool m_debug= false);
  bool PassUserID(ID id,bool usetight,snu::KElectron el,double rho, float isocut, bool applypog, bool m_debug= false);
  bool PassUserID_EGamma2012 ( ID id, snu::KElectron el , double rho,  bool applypog,bool m_debug= false);
  bool PassUserID_ECALFiducial (snu::KElectron el);
  bool PassUserID_FakeLoose2012 (snu::KElectron el, bool usetight,double jetrho , float isocut, bool m_debug=false);

    
};
#endif
