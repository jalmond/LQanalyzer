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

  bool HNIsTight(snu::KElectron el, bool m_debug); /// Calls function below   
  // Main tight function

  void HNLooseElectronSelection( std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  
  void HNVetoElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);

  //// Top analysis selection
  void TopTightElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void TopLooseElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);
  void TopVetoElectronSelection(std::vector<snu::KElectron>& leptonColl, bool m_debug= false);


  //// IDS
  bool PassUserID(ID id,bool usetight,snu::KElectron el , float isocut, bool m_debug= false);
  bool PassUserID(ID id,snu::KElectron el, bool m_debug= false);
  bool PassUserID_FakeLoose2015 (snu::KElectron el, bool usetight, float isocut, bool m_debug=false);

    
};
#endif
