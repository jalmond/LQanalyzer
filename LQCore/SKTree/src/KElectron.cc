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
  k_mc_matched=false;
  k_isPF=false;
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
  k_pf_chargedhad_iso03= el.PFChargedHadronIso03();
  k_pf_photon_iso03 = el.PFPhotonIso03();
  k_pf_neutral_iso03= el.PFNeutralHadronIso03();
  k_pf_chargedhad_iso04= el.PFChargedHadronIso04();
  k_pf_photon_iso04= el.PFPhotonIso04();
  k_pf_neutral_iso04= el.PFNeutralHadronIso04();
  k_rel_iso03=el.PFRelIso03();
  k_rel_iso04=el.PFRelIso04();
  k_abs_iso03=el.PFAbsIso03();
  k_abs_iso04=el.PFAbsIso04();
  k_pt_shifted_up=el.PtShiftedUp();
  k_pt_shifted_down=el.PtShiftedDown();
  pass_veto=el.PassVeto();
  pass_loose=el.PassLoose();
  pass_medium=el.PassMedium();
  pass_tight=el.PassTight();
  k_mc_matched=el.MCMatched();
  k_isPF=el.IsPF();
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
  k_mc_matched=false;
  k_isPF=false;
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
    k_pf_chargedhad_iso03= p.PFChargedHadronIso03();
    k_pf_photon_iso03 = p.PFPhotonIso03();
    k_pf_neutral_iso03= p.PFNeutralHadronIso03();
    k_pf_chargedhad_iso04= p.PFChargedHadronIso04();
    k_pf_photon_iso04= p.PFPhotonIso04();
    k_pf_neutral_iso04= p.PFNeutralHadronIso04();
    k_rel_iso03=p.PFRelIso03();
    k_rel_iso04=p.PFRelIso04();
    k_pt_shifted_up=p.PtShiftedUp();
    k_pt_shifted_down=p.PtShiftedDown();
    pass_veto=p.PassVeto();
    pass_loose=p.PassLoose();
    pass_medium=p.PassMedium();
    pass_tight=p.PassTight();
    k_mc_matched=p.MCMatched();
    k_isPF=p.IsPF();
    snu_id = p.SNUID();
    k_trkvx= p.TrkVx();
    k_trkvy= p.TrkVy();
    k_trkvz= p.TrkVz();
    k_abs_iso03=p.PFAbsIso03();
    k_abs_iso04=p.PFAbsIso04();
    k_trig_match= p.TrigMatch();
  }
  
  return *this;
}



bool KElectron::TriggerMatched(TString path){
  TString trig = k_trig_match;
  if(trig.Contains(path)) return true;
  return false;
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



void KElectron::SetPFChargedHadronIso03(Double_t pf_ch_03){
  k_pf_chargedhad_iso03= pf_ch_03;
}

void KElectron::SetPFPhotonIso03(Double_t pf_ph_03){
  k_pf_photon_iso03 = pf_ph_03;
}

void KElectron::SetPFNeutralHadronIso03(Double_t pf_ne_03){
  k_pf_neutral_iso03 = pf_ne_03;
}

void KElectron::SetPFChargedHadronIso04(Double_t pf_ch_03){
  k_pf_chargedhad_iso04 = pf_ch_03;
}

void KElectron::SetPFPhotonIso04(Double_t pf_ph_03){
  k_pf_photon_iso04= pf_ph_03;
}

void KElectron::SetPFNeutralHadronIso04(Double_t pf_ne_03){
  k_pf_neutral_iso04 = pf_ne_03;
}

void KElectron::SetPFRelIso03(Double_t reliso03){
  k_rel_iso03=reliso03;
}

void KElectron::SetPFRelIso04(Double_t reliso04){
  k_rel_iso04=reliso04;
}
void KElectron::SetPFAbsIso03(Double_t absiso03){
  k_abs_iso03=absiso03;
}

void KElectron::SetPFAbsIso04(Double_t absiso04){
  k_abs_iso04=absiso04;
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

void KElectron::SetIsPF(Bool_t isPF){
  k_isPF=isPF;
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
