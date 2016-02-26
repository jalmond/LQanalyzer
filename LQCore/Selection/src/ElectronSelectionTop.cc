#include "ElectronSelectionTop.h"
#include <iostream>
using namespace std;


bool TopVetoElectronSelection(KElectron el){

  bool pass_selection = el.PassVeto();

  ///List of cuts
  if(pass_selection)  return true;
  return false;

}



bool TopLooseElectronSelection(KElectron el){

  bool pass_selection = true;
  float LeptonRelIsoDR03(0.);
  float LeptonRelIsoDR04(0.);
  LeptonRelIsoDR03 = el.PFRelIso(0.3);
  LeptonRelIsoDR04 = el.PFRelIso(0.4);

  if((!el.HasMatchedConvPhot()))  pass_selection = false;
  if(!(el.dxy()< 0.04 ))  pass_selection = false;

  if(pass_selection)  return true;
  return false;
}



bool TopTightElectronSelection(KElectron el){

  bool pass_selection = true;
  // exclude EB-EE transition region
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;
  if((!el.HasMatchedConvPhot() )) pass_selection = false;
  float LeptonRelIsoDR03= el.PFRelIso(0.3);
  if(!(LeptonRelIsoDR03 <  0.1))  pass_selection = false;
  if(!(el.dxy()< 0.02 ))  pass_selection = false;
  if(!(el.dz()<  0.10 ))  pass_selection = false;
  if(pass_selection)  return true;
  return false;
}


