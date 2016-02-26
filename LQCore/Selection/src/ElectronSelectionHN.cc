#include "ElectronSelectionHN.h"
#include <iostream>
using namespace std;

bool HNVetoElectronSelection(snu::KElectron el){

  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;

  // VETO ID (pog:no dxy and no iso)
  int id = el.SNUID();
  if(id < 1) return false;

  if( el.PFRelIso(0.3) > 0.6) return false;
  if( el.dxy() > 1.) return false;

  return true;
}


bool HNLooseElectronSelection( KElectron el , bool usetight, float isocut) {
  
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;
  /// from https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2

  bool pass_selection = true;
  
  ///List of cuts
  if(!PassUserID_FakeLoose( el, usetight, isocut))  pass_selection = false; // No POG ID with no iso or dxy
  if((!el.HasMatchedConvPhot()))   pass_selection = false;
  if(!el.GsfCtfScPixChargeConsistency()) pass_selection = false;
  
  return pass_selection;
}


bool HNIsTight(KElectron el){

  // default: iso/dxy set to pog tight cuts
  float dxycut = -999.;  float isocut= -999;
  if(fabs(el.SCEta())<1.566 ){  dxycut = 0.0111;    isocut = 0.0354; }
  else{isocut = 0.0646;    dxycut = 0.0351; }

  return HNIsTight(el, dxycut , isocut, true);

}

bool HNIsTight(KElectron el, double dxycut, double isocut,  bool usetight){
  
  // currently set to pog tight cuts
  /// from https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2

  //// Require it is not in crack
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;
  
  bool pass_selection = true;
  
  float LeptonRelIsoDR03(0.);
  float LeptonRelIsoDR04(0.);
  bool id(false);
  if(usetight) id= el.PassTight();
  else id = el.PassMedium();
  
  LeptonRelIsoDR03 = el.PFRelIso(0.3);
  LeptonRelIsoDR04 = el.PFRelIso(0.4);
  
  ///List of cuts
  if(!id) pass_selection = false;  
  if((!el.HasMatchedConvPhot() ) )  pass_selection = false;
  
  bool usedr3=true;
  if(usedr3){
    if(!(LeptonRelIsoDR03 <  isocut)) pass_selection = false;  
  }
  else{
    if(!(LeptonRelIsoDR04 <  isocut)) pass_selection = false; 
  }
  if(!el.GsfCtfScPixChargeConsistency())   pass_selection = false;
  if(!(fabs(el.dxy())< dxycut ))  pass_selection = false;

  return pass_selection;
  
}


bool HNTightElectronSelection(KElectron el ){

  if(HNIsTight(el)) return true;
  else return false;

}


bool PassUserID_FakeLoose (snu::KElectron el, bool usetight,  float looseisocut){
  
  int id = el.SNUID();
  bool pass_medium_noiso = false;
  bool pass_tight_noiso = false;
  if(id >= 1000){
    pass_tight_noiso = true;
    id = id - 1000;
    if(id >= 100){
      pass_medium_noiso= true;
      id = id-100;
    }
  }
  
  if(usetight){
    if(!pass_tight_noiso) return false;
  }
  else  if(!pass_medium_noiso) return false;
  
  if( el.PFRelIso(0.3) > looseisocut) return false;   
  if(!(fabs(el.dxy())< 100.))  return false;

  return true;
}





