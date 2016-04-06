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
  void SelectElectrons(std::vector<snu::KElectron>& leptonColl,ID id, float ptcut, float etacut);
  
  //// HN analysis selection
  //void HNVetoElectronSelection(std::vector<snu::KElectron>& leptonColl);  
  //void HNLooseElectronSelection( std::vector<snu::KElectron>& leptonColl);
  //void HNTightElectronSelection(std::vector<snu::KElectron>& leptonColl,  bool m_debug= false);
  //bool HNIsTight(snu::KElectron el, bool m_debug); 
  


  //// Top analysis selection
  bool TopTightElectronSelection(snu::KElectron el);
  bool TopLooseElectronSelection(snu::KElectron el);
  bool TopVetoElectronSelection(snu::KElectron el);

  
  //// IDS
  bool PassUserID(ID id,snu::KElectron el ,bool usetight, bool loosend0, float isocut);
  bool PassUserID(ID id,snu::KElectron el);
  bool PassUserID_FakeLoose(snu::KElectron el, bool usetight, float isocut);
  bool PassHNVeto(snu::KElectron el);
    
};
#endif
