#ifndef ElectronSelection_h
#define ElectronSelection_h

#include "KElectron.h"
#include "LQEvent.h"
#include "BaseSelection.h" 

class ElectronSelection : public BaseSelection {
  
  Bool_t ElectronID;
  Double_t PHONH[7];

 public:
  ElectronSelection(LQEvent ev);
  ~ElectronSelection();

  ElectronSelection& operator= (const ElectronSelection& obj);
  ElectronSelection(const ElectronSelection& bs);
  
  void Selection(std::vector<snu::KElectron>& leptonColl);

  
  //  const Double_t ElectronSel::AreaTrackerEle[2] = {0., 0.};         //   barrel/endcap
  //const Double_t ElectronSel::AreaEcalEle[2]    = {0.101, 0.046};   //   barrel/endcap
  //const Double_t ElectronSel::AreaHcalEle[2]    = {0.021 , 0.040};  //   barrel/endcap
  //const Double_t ElectronSel::PHONH[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};

};
#endif
