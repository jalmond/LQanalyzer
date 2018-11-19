#ifndef PhotonSelection_h
#define PhotonSelection_h

#include "KPhoton.h"
#include "LQEvent.h"
#include "BaseSelection.h" 

class PhotonSelection : public BaseSelection {

 public:
  
  Bool_t PhotonID;

  PhotonSelection(LQEvent ev);
  ~PhotonSelection();

  PhotonSelection& operator= (const PhotonSelection& obj);
  PhotonSelection(const PhotonSelection& bs);
  
  void Selection(std::vector<snu::KPhoton>& leptonColl, bool m_debug= false);		 
  void BasicSelection(std::vector<snu::KPhoton>& leptonColl, bool m_debug= false);
  void SkimSelection(std::vector<snu::KPhoton>& leptonColl, bool m_debug= false);
  

  
  //// IDS
  void PogID(std::vector<snu::KPhoton>& leptonColl, TString ID);
  bool PassUserID(ID id,snu::KPhoton ph);
    
};
#endif
