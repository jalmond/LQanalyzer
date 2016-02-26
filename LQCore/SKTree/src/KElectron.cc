#include "KElectron.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KElectron)

/**
 *Default constructor.
 */
KElectron::KElectron() :
KParticle()
{
  k_sceta=0;
  k_dxy=0;
  k_dz=0;
  k_gsf_ctscpix_charge=false;
  k_hasmatchconvphot=false; 
  k_pf_chargedhad_iso03=0.;
  k_pf_photon_iso03=0.;
  k_pf_neutral_iso03=0.;
  k_pf_chargedhad_iso04=0.;
  k_pf_photon_iso04=0.;
  k_pf_neutral_iso04=0.;
  k_rel_iso03=0.;
  k_rel_iso04=0.;
  k_abs_iso03=0.;
  k_abs_iso04=0.;
  k_pt_shifted_up=0.;
  k_pt_shifted_down=0.;
  pass_veto=false;
  pass_loose=false;
  pass_medium=false;
  pass_tight=false;
  pass_heep=false;
  pass_trigmva_medium=false;
  pass_trigmva_tight=false;
  pass_notrigmva_medium=false;
  pass_notrigmva_tight=false;
  k_mc_matched=false;
  k_isPF=false;
  k_istrigmvavalid=false;
  snu_id = -999;
  k_trkvx=0.;
  k_trkvy=0.;
  k_trkvz=0.;
  k_gsf_ctscpix_charge=false;
  k_trig_match="";
}

/**
 * Copy constructor.
 */
KElectron::KElectron(const KElectron& el) :
    KParticle(el)
{
  
  k_sceta= el.SCEta();
  k_dxy= el.dxy();
  k_dz= el.dz();
  k_gsf_ctscpix_charge= el.GsfCtfScPixChargeConsistency();
  k_hasmatchconvphot= el.HasMatchedConvPhot();
  k_pf_chargedhad_iso03= el.PFChargedHadronIso(0.3);
  k_pf_photon_iso03 = el.PFPhotonIso(0.3);
  k_pf_neutral_iso03= el.PFNeutralHadronIso(0.3);
  k_pf_chargedhad_iso04= el.PFChargedHadronIso(0.4);
  k_pf_photon_iso04= el.PFPhotonIso(0.4);
  k_pf_neutral_iso04= el.PFNeutralHadronIso(0.4);
  k_rel_iso03=el.PFRelIso(0.3);
  k_rel_iso04=el.PFRelIso(0.4);
  k_abs_iso03=el.PFAbsIso(0.3);
  k_abs_iso04=el.PFAbsIso(0.4);
  k_pt_shifted_up=el.PtShiftedUp();
  k_pt_shifted_down=el.PtShiftedDown();
  pass_veto=el.PassVeto();
  pass_loose=el.PassLoose();
  pass_medium=el.PassMedium();
  pass_tight=el.PassTight();
  pass_heep=el.PassHEEP();
  pass_trigmva_medium=el.PassTrigMVAMedium();
  pass_trigmva_tight=el.PassTrigMVATight(); 
  pass_notrigmva_medium=el.PassNotrigMVAMedium();
  pass_notrigmva_tight=el.PassNotrigMVATight();
  k_mc_matched=el.MCMatched();
  k_isPF=el.IsPF();
  k_istrigmvavalid=el.IsTrigMVAValid();
  snu_id = el.SNUID();
  k_trkvx= el.TrkVx();
  k_trkvy= el.TrkVy();
  k_trkvz= el.TrkVz();
  k_gsf_ctscpix_charge= el.GsfCtfScPixChargeConsistency();
  k_trig_match= el.TrigMatch();
}


KElectron::~KElectron()
{
}

void KElectron::Reset()
{
  KParticle::Reset();
  k_sceta=0;
  k_dxy=0;
  k_dz=0;
  k_gsf_ctscpix_charge=false;
  k_hasmatchconvphot=false;
  k_pf_chargedhad_iso03=0.;
  k_pf_photon_iso03=0.;
  k_pf_neutral_iso03=0.;
  k_pf_chargedhad_iso04=0.;
  k_pf_photon_iso04=0.;
  k_pf_neutral_iso04=0.;
  k_rel_iso03=0.;
  k_rel_iso04=0.;
  k_pt_shifted_up=0.;
  k_pt_shifted_down=0.;
  pass_veto=false;
  pass_loose=false;
  pass_medium=false;
  pass_tight=false;
  pass_heep=false;
  pass_trigmva_medium=false;
  pass_trigmva_tight=false;
  pass_notrigmva_medium=false;
  pass_notrigmva_tight=false;
  k_mc_matched=false;
  k_isPF=false;
  k_istrigmvavalid=false;
  snu_id = -999;
  k_trkvx=0.;
  k_trkvy=0.;
  k_trkvz=0.;
  k_abs_iso03=0.;
  k_abs_iso04=0.;
  k_gsf_ctscpix_charge=false;
  k_trig_match="";

}



KElectron& KElectron::operator= (const KElectron& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_sceta= p.SCEta();
    k_dxy= p.dxy();
    k_dz= p.dz();
    k_gsf_ctscpix_charge= p.GsfCtfScPixChargeConsistency();
    k_hasmatchconvphot= p.HasMatchedConvPhot();
    k_pf_chargedhad_iso03= p.PFChargedHadronIso(0.3);
    k_pf_photon_iso03 = p.PFPhotonIso(0.3);
    k_pf_neutral_iso03= p.PFNeutralHadronIso(0.3);
    k_pf_chargedhad_iso04= p.PFChargedHadronIso(0.4);
    k_pf_photon_iso04= p.PFPhotonIso(0.4);
    k_pf_neutral_iso04= p.PFNeutralHadronIso(0.4);
    k_rel_iso03=p.PFRelIso(0.3);
    k_rel_iso04=p.PFRelIso(0.4);
    k_pt_shifted_up=p.PtShiftedUp();
    k_pt_shifted_down=p.PtShiftedDown();
    pass_veto=p.PassVeto();
    pass_loose=p.PassLoose();
    pass_medium=p.PassMedium();
    pass_tight=p.PassTight();
    pass_heep=p.PassHEEP();
    pass_trigmva_medium=p.PassTrigMVAMedium();
    pass_trigmva_tight=p.PassTrigMVATight();
    pass_notrigmva_medium=p.PassNotrigMVAMedium();
    pass_notrigmva_tight=p.PassNotrigMVATight();
    k_mc_matched=p.MCMatched();
    k_isPF=p.IsPF();
    k_istrigmvavalid=p.IsTrigMVAValid();
    snu_id = p.SNUID();
    k_trkvx= p.TrkVx();
    k_trkvy= p.TrkVy();
    k_trkvz= p.TrkVz();
    k_abs_iso03=p.PFAbsIso(0.3);
    k_abs_iso04=p.PFAbsIso(0.4);
    k_trig_match= p.TrigMatch();
  }
  
  return *this;
}



bool KElectron::TriggerMatched(TString path){
  TString trig = k_trig_match;
  if(trig.Contains(path)) return true;
  return false;
}


float KElectron::ScaleFactor(const std::string& name, int sign) const {
  
  if (name == "mvaEleID-Spring15-25ns-Trig-V1-wp90"){
    
  }
  
  if (name == "cutBasedElectronID-Spring15-25ns-V1-standalone-tight"){
    if (this->Pt()>10. && this->Pt() <= 20.){
      if      ( this->Eta()>-2.5 && this->Eta() <= -2.0)      return (0.358/0.286) + sign*(0.02);
      else if ( this->Eta()>-2.0 && this->Eta() <= -1.566)    return (0.328/0.288)  + sign*(0.06);
      else if ( this->Eta()>-1.566 && this->Eta() <= -1.444 ) return (0.228/0.168)  + sign*(0.01);
      else if ( this->Eta()>-1.444 && this->Eta() <= -0.8)    return (0.397/0.303)  + sign*(0.01);
      else if ( this->Eta()>-0.800 && this->Eta() <= 0.)      return (0.408/0.339)  + sign*(0.01);
      else if ( this->Eta()>0.0 && this->Eta() <= 0.8)        return (0.407/0.344)  + sign*(0.02);
      else if ( this->Eta()>0.8 && this->Eta() <= 1.444)      return (0.391/0.298)  + sign*(0.02);
      else if ( this->Eta()>1.444 && this->Eta() <= 1.566)    return (0.244/0.164)  + sign*(0.02);
      else if ( this->Eta()>1.566 && this->Eta() <= 2.0)      return (0.308/0.284)  + sign*(0.02);
      else if ( this->Eta()>2.0 && this->Eta() <= 2.5)        return (0.344/0.293)  + sign*(0.01);
      else return 1.;
    }
    else  if (this->Pt()>15. && this->Pt() <= 25.){
      if      ( this->Eta()>-2.5 && this->Eta() <= -2.0)      return (0.506/0.478)  + sign*(0.02);
      else if ( this->Eta()>-2.0 && this->Eta() <= -1.566)    return (0.486/0.494)  + sign*(0.06);
      else if ( this->Eta()>-1.566 && this->Eta() <= -1.444 ) return (0.344/0.290)  + sign*(0.01);
      else if ( this->Eta()>-1.444 && this->Eta() <= -0.8)    return (0.523/0.498)  + sign*(0.01);
      else if ( this->Eta()>-0.800 && this->Eta() <= 0.)      return (0.541/0.531)  + sign*(0.01);
      else if ( this->Eta()>0.0 && this->Eta() <= 0.8)        return (0.532/0.535)  + sign*(0.02);
      else if ( this->Eta()>0.8 && this->Eta() <= 1.444)      return (0.522/0.494)  + sign*(0.02);
      else if ( this->Eta()>1.444 && this->Eta() <= 1.566)    return (0.300/0.283)  + sign*(0.02);
      else if ( this->Eta()>1.566 && this->Eta() <= 2.0)      return (0.499/0.488)  + sign*(0.02);
      else if ( this->Eta()>2.0 && this->Eta() <= 2.5)        return (0.509/0.482)  + sign*(0.01);
      else return 1.;
    }   
    else  if (this->Pt()>15. && this->Pt() <= 25.){
      if      ( this->Eta()>-2.5 && this->Eta() <= -2.0)      return (0.625/0.610)  + sign*(0.02);
      else if ( this->Eta()>-2.0 && this->Eta() <= -1.566)    return (0.617/0.637)  + sign*(0.06);
      else if ( this->Eta()>-1.566 && this->Eta() <= -1.444 ) return (0.469/0.462)  + sign*(0.01);
      else if ( this->Eta()>-1.444 && this->Eta() <= -0.8)    return (0.640/0.647)  + sign*(0.01);
      else if ( this->Eta()>-0.800 && this->Eta() <= 0.)      return (0.650/0.674)  + sign*(0.01);
      else if ( this->Eta()>0.0 && this->Eta() <= 0.8)        return (0.652/0.674)  + sign*(0.02);
      else if ( this->Eta()>0.8 && this->Eta() <= 1.444)      return (0.642/0.644)  + sign*(0.02);
      else if ( this->Eta()>1.444 && this->Eta() <= 1.566)    return (0.449/0.455)  + sign*(0.02);
      else if ( this->Eta()>1.566 && this->Eta() <= 2.0)      return (0.615/0.636)  + sign*(0.02);
      else if ( this->Eta()>2.0 && this->Eta() <= 2.5)        return (0.626/0.612)  + sign*(0.01);
      else return 1.;
    }   
    else  if (this->Pt()>15. && this->Pt() <= 25.){
      if      ( this->Eta()>-2.5 && this->Eta() <= -2.0)      return (0.698/0.691)  + sign*(0.02);
      else if ( this->Eta()>-2.0 && this->Eta() <= -1.566)    return (0.707/0.720)  + sign*(0.06);
      else if ( this->Eta()>-1.566 && this->Eta() <= -1.444 ) return (0.603/0.607)  + sign*(0.01);
      else if ( this->Eta()>-1.444 && this->Eta() <= -0.8)    return (0.721/0.743)  + sign*(0.01);
      else if ( this->Eta()>-0.800 && this->Eta() <= 0.)      return (0.725/0.758)  + sign*(0.01);
      else if ( this->Eta()>0.0 && this->Eta() <= 0.8)        return (0.729/0.758)  + sign*(0.02);
      else if ( this->Eta()>0.8 && this->Eta() <= 1.444)      return (0.720/0.740)  + sign*(0.02);
      else if ( this->Eta()>1.444 && this->Eta() <= 1.566)    return (0.576/0.602)  + sign*(0.02);
      else if ( this->Eta()>1.566 && this->Eta() <= 2.0)      return (0.709/0.720)  + sign*(0.02);
      else if ( this->Eta()>2.0 && this->Eta() <= 2.5)        return (0.694/0.691)  + sign*(0.01);
      else return 1.;
    }   
    else  if (this->Pt()>15. && this->Pt() <= 25.){
      if      ( this->Eta()>-2.5 && this->Eta() <= -2.0)      return (0.741/0.742)  + sign*(0.02);
      else if ( this->Eta()>-2.0 && this->Eta() <= -1.566)    return (0.757/0.772)  + sign*(0.06);
      else if ( this->Eta()>-1.566 && this->Eta() <= -1.444 ) return (0.617/0.653)  + sign*(0.01);
      else if ( this->Eta()>-1.444 && this->Eta() <= -0.8)    return (0.765/0.800)  + sign*(0.01);
      else if ( this->Eta()>-0.800 && this->Eta() <= 0.)      return (0.774/0.811)  + sign*(0.01);
      else if ( this->Eta()>0.0 && this->Eta() <= 0.8)        return (0.779/0.810)  + sign*(0.02);
      else if ( this->Eta()>0.8 && this->Eta() <= 1.444)      return (0.762/0.797)  + sign*(0.02);
      else if ( this->Eta()>1.444 && this->Eta() <= 1.566)    return (0.618/0.651)  + sign*(0.02);
      else if ( this->Eta()>1.566 && this->Eta() <= 2.0)      return (0.766/0.772)  + sign*(0.02);
      else if ( this->Eta()>2.0 && this->Eta() <= 2.5)        return (0.742/0.741)  + sign*(0.01);
      else return 1.;
    }   
  
    
  }
}



///// SETTING CLASS VARIABLES

void KElectron::SetSCEta(Double_t sceta){
  k_sceta = sceta;
}


void KElectron::Setdz(double d_z){ 
  k_dz = d_z;
}

void KElectron::Setdxy(double d_xy){ 
  k_dxy = d_xy;
}
 

 
void KElectron::SetPFChargedHadronIso(Double_t cone, Double_t pf_ch){
   if(cone == 0.3)  k_pf_chargedhad_iso03= pf_ch;
   else  if(cone == 0.4)  k_pf_chargedhad_iso04= pf_ch;
}

void KElectron::SetPFPhotonIso(Double_t cone,Double_t pf_ph){
  if(cone == 0.3)   k_pf_photon_iso03 = pf_ph;
  else  if(cone == 0.4) k_pf_photon_iso04 = pf_ph; 
}

void KElectron::SetPFNeutralHadronIso(Double_t cone,Double_t pf_ne){
  if(cone == 0.3)  k_pf_neutral_iso03 = pf_ne;
  else  if(cone == 0.4)k_pf_neutral_iso04 = pf_ne;

}


void KElectron::SetPFRelIso(Double_t cone,Double_t reliso){
  if(cone == 0.3)   k_rel_iso03=reliso;
  else  if(cone == 0.4) k_rel_iso04=reliso;
}

void KElectron::SetPFAbsIso(Double_t cone,Double_t absiso){
  if(cone == 0.3) k_abs_iso03=absiso;
  else  if(cone == 0.4) k_abs_iso04=absiso;
}




void KElectron::SetGsfCtfScPixCharge(bool gsfctfscpix_ch){
  k_gsf_ctscpix_charge = gsfctfscpix_ch;
}


void KElectron::SetHasMatchedConvPhot(Bool_t hasmatchConvPhot){  
  k_hasmatchconvphot = hasmatchConvPhot;
}

void KElectron::SetShiftedEUp(Double_t Eup){
  k_pt_shifted_up= Eup;
}

void KElectron::SetShiftedEDown(Double_t Edown){
  k_pt_shifted_down= Edown;
}

void KElectron::SetSNUID(Int_t snuid){
  snu_id=snuid;
}

void KElectron::SetPassVeto(Bool_t veto){
  pass_veto= veto;
}

void KElectron::SetPassLoose(Bool_t loose){
  pass_loose= loose;
}

void KElectron::SetPassMedium(Bool_t medium){
  pass_medium= medium;
}

void KElectron::SetPassTight(Bool_t tight){
  pass_tight= tight;
}

void KElectron::SetPassHEEP(Bool_t pass){
  pass_heep= pass;
}

void KElectron::SetPassMVATrigMedium(Bool_t pass){
  pass_trigmva_medium= pass;
}

void KElectron::SetPassMVATrigTight(Bool_t pass){
  pass_trigmva_tight= pass;
}

void KElectron::SetPassMVANoTrigMedium(Bool_t pass){
  pass_notrigmva_medium= pass;
}

void KElectron::SetPassMVANoTrigTight(Bool_t pass){
  pass_notrigmva_tight= pass;
}


void KElectron::SetIsPF(Bool_t isPF){
  k_isPF=isPF;
}

void KElectron::SetIsTrigMVAValid(Bool_t b){
  k_istrigmvavalid= b;
}

void KElectron::SetIsMCMatched(Bool_t matched){
  k_mc_matched = matched;
}

void KElectron::SetTrkVx(Double_t trkvx){  
  k_trkvx = trkvx;
}
void KElectron::SetTrkVy(Double_t trkvy){  
  k_trkvy = trkvy;
}
void KElectron::SetTrkVz(Double_t trkvz){  
  k_trkvz = trkvz;
}

void KElectron::SetTrigMatch(TString match){
  k_trig_match = match;
}
