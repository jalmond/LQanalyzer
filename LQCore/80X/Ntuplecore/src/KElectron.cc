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
  k_sceta=-999;
  k_dxy=-999;
  k_dxy_sig=-999;
  k_dxy_sig2D=-999;
  k_dxy_sig3D=-999;
  k_dz=-999;
  k_gsf_ctscpix_charge=false;
  k_gsf_scpix_charge=false; 
  k_gsf_ct_charge=false;
  k_hasmatchconvphot=false; 
  k_pf_chargedhad_iso03=-999;
  k_pf_photon_iso03=-999;
  k_pf_neutral_iso03=-999;
  k_pf_chargedhad_iso04=-999;
  k_pf_photon_iso04=-999;
  k_pf_neutral_iso04=-999;
  k_rel_iso03=-999;
  k_rel_iso04=-999;
  k_rel_miniiso=-999;
  k_electrons_minirelIsoBeta= -999.;
  k_electrons_minirelIsoRho= -999.;
  k_abs_iso03=-999;
  k_abs_iso04=-999;
  k_pt_shifted_up=-999;
  k_pt_shifted_down=-999;
  pass_veto=false;
  pass_loose=false;
  pass_medium=false;
  pass_tight=false;
  pass_hltid=false;
  pass_heep=false;
  pass_trigmva_medium=false;
  pass_trigmva_tight=false;
  pass_notrigmva_medium=false;
  pass_notrigmva_tight=false;
  pass_notrigmva_zz=false;
  k_mc_matched=false;
  k_is_cf=false;
  k_is_conv=false;
  k_is_fromtau=false;
  k_mother_pdgid=-1;
  k_mc_pdgid=-1;
  k_mother_index=-1;
  k_mc_index=-1;
  k_isPF=false;
  k_istrigmvavalid=false;
  snu_id = -999;
  k_trkvx=-999;
  k_trkvy=-999;
  k_trkvz=-999;
  k_gsf_ctscpix_charge=false;
  k_gsf_scpix_charge=false;
  k_gsf_ct_charge=false;
  k_trig_match="";
  k_eltype=-999;
  k_mva=-999;
  k_zzmva=-999;
  k_missing_hits=-999;
  k_smearfactor=-999.;
  k_in_conv=false;
  k_isprompt=false;
  
}

/**
 * Copy constructor.
 */
KElectron::KElectron(const KElectron& el) :
    KParticle(el)
{
  
  k_sceta= el.SCEta();
  k_dxy= el.dxy();
  k_dxy_sig= el.dxySig();
  k_dxy_sig2D= el.dxySig2D();
  k_dxy_sig3D= el.dxySig3D();
  k_dz= el.dz();
  k_gsf_ctscpix_charge= el.GsfCtfScPixChargeConsistency();
  k_gsf_scpix_charge= el.GsfScPixChargeConsistency();
  k_gsf_ct_charge= el.GsfCtfChargeConsistency();
  k_hasmatchconvphot= el.PassesConvVeto();
  k_pf_chargedhad_iso03= el.PFChargedHadronIso(0.3);
  k_pf_photon_iso03 = el.PFPhotonIso(0.3);
  k_pf_neutral_iso03= el.PFNeutralHadronIso(0.3);
  k_pf_chargedhad_iso04= el.PFChargedHadronIso(0.4);
  k_pf_photon_iso04= el.PFPhotonIso(0.4);
  k_pf_neutral_iso04= el.PFNeutralHadronIso(0.4);
  k_rel_iso03=el.PFRelIso(0.3);
  k_rel_iso04=el.PFRelIso(0.4);
  k_rel_miniiso=el.PFRelMiniIso();
  k_electrons_minirelIsoBeta=el.PFRelMiniIso(true);
  k_electrons_minirelIsoRho= el.PFRelMiniIso(false);
  k_abs_iso03=el.PFAbsIso(0.3);
  k_abs_iso04=el.PFAbsIso(0.4);
  k_pt_shifted_up=el.PtShiftedUp();
  k_pt_shifted_down=el.PtShiftedDown();
  pass_veto=el.PassVeto();
  pass_loose=el.PassLoose();
  pass_medium=el.PassMedium();
  pass_tight=el.PassTight();
  pass_hltid=el.PassHLTID();
  pass_heep=el.PassHEEP();
  pass_trigmva_medium=el.PassTrigMVAMedium();
  pass_trigmva_tight=el.PassTrigMVATight(); 
  pass_notrigmva_medium=el.PassNotrigMVAMedium();
  pass_notrigmva_tight=el.PassNotrigMVATight();
  pass_notrigmva_zz=el.PassMVAZZ();
  k_mc_matched=el.MCMatched();
  k_is_cf=el.MCIsCF();
  k_is_conv=el.MCIsFromConversion();
  k_is_fromtau=el.MCFromTau();
  k_mother_pdgid=el.MotherPdgId();
  k_mc_pdgid=el.MCMatchedPdgId();
  k_mother_index=el.MotherTruthIndex();
  k_mc_index=el.MCTruthIndex();
  k_isPF=el.IsPF();
  k_istrigmvavalid=el.IsTrigMVAValid();
  snu_id = el.SNUID();
  k_trkvx= el.TrkVx();
  k_trkvy= el.TrkVy();
  k_trkvz= el.TrkVz();

  k_gsf_ctscpix_charge= el.GsfCtfScPixChargeConsistency();
  k_gsf_scpix_charge= el.GsfScPixChargeConsistency();
  k_gsf_ct_charge= el.GsfCtfChargeConsistency();
  k_trig_match= el.TrigMatch();
  k_eltype=el.GetType();
  k_mva=el.MVA();
  k_zzmva=el.ZZMVA();
  k_missing_hits=el.MissingHits();
  k_smearfactor=el.SmearFactor();
  k_in_conv=el.MCIsExternalConversion();
  k_isprompt=el.IsPromptFlag();

}



KElectron::~KElectron()
{
}

void KElectron::Reset()
{
  KParticle::Reset();
  k_sceta=-999;
  k_dxy=-999;
  k_dxy_sig=-999;
  k_dxy_sig2D=-999;
  k_dxy_sig3D=-999;
  k_dz=0;
  k_gsf_ctscpix_charge=false;
  k_gsf_scpix_charge=false;
  k_gsf_ct_charge=false;
  k_hasmatchconvphot=false;
  k_pf_chargedhad_iso03=-999;
  k_pf_photon_iso03=-999;
  k_pf_neutral_iso03=-999;
  k_pf_chargedhad_iso04=-999;
  k_pf_photon_iso04=-999;
  k_pf_neutral_iso04=-999;
  k_rel_iso03=-999;
  k_rel_iso04=-999;
  k_pt_shifted_up=-999;
  k_pt_shifted_down=-999;
  pass_veto=false;
  pass_loose=false;
  pass_medium=false;
  pass_tight=false;
  pass_hltid=false;
  pass_heep=false;
  pass_trigmva_medium=false;
  pass_trigmva_tight=false;
  pass_notrigmva_medium=false;
  pass_notrigmva_tight=false;
  pass_notrigmva_zz=false;
  k_mc_matched=false;
  k_is_cf=false;
  k_is_conv=false;
  k_is_fromtau=false;
  k_mother_pdgid=-1;
  k_mc_pdgid=1;
  k_mother_index=-1;
  k_mc_index=-1;
  k_isPF=false;
  k_istrigmvavalid=false;
  snu_id = -999;
  k_trkvx=-999;
  k_trkvy=-999;
  k_trkvz=-999;
  k_abs_iso03=-999;
  k_abs_iso04=-999;
  k_trig_match="";
  k_eltype=-999;
  k_mva=-999;
  k_zzmva=-999;
  k_missing_hits=-999;
  k_smearfactor=-999.;
  k_in_conv=false;
  k_isprompt=false;
  
}



KElectron& KElectron::operator= (const KElectron& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_sceta= p.SCEta();
    k_dxy= p.dxy();
    k_dxy_sig= p.dxySig();
    k_dxy_sig2D= p.dxySig2D();
    k_dxy_sig3D= p.dxySig3D();

    k_dz= p.dz();
    k_gsf_ctscpix_charge= p.GsfCtfScPixChargeConsistency();
    k_hasmatchconvphot= p.PassesConvVeto();
    k_pf_chargedhad_iso03= p.PFChargedHadronIso(0.3);
    k_pf_photon_iso03 = p.PFPhotonIso(0.3);
    k_pf_neutral_iso03= p.PFNeutralHadronIso(0.3);
    k_pf_chargedhad_iso04= p.PFChargedHadronIso(0.4);
    k_pf_photon_iso04= p.PFPhotonIso(0.4);
    k_pf_neutral_iso04= p.PFNeutralHadronIso(0.4);
    k_rel_iso03=p.PFRelIso(0.3);
    k_rel_iso04=p.PFRelIso(0.4);
    k_rel_miniiso=p.PFRelMiniIso();
    k_electrons_minirelIsoBeta=p.PFRelMiniIso(true);
    k_electrons_minirelIsoRho= p.PFRelMiniIso(false);
    k_pt_shifted_up=p.PtShiftedUp();
    k_pt_shifted_down=p.PtShiftedDown();
    pass_veto=p.PassVeto();
    pass_loose=p.PassLoose();
    pass_medium=p.PassMedium();
    pass_tight=p.PassTight();
    pass_hltid=p.PassHLTID();
    pass_heep=p.PassHEEP();
    pass_trigmva_medium=p.PassTrigMVAMedium();
    pass_trigmva_tight=p.PassTrigMVATight();
    pass_notrigmva_medium=p.PassNotrigMVAMedium();
    pass_notrigmva_tight=p.PassNotrigMVATight();
    pass_notrigmva_zz=p.PassMVAZZ();
    k_mc_matched=p.MCMatched();
    k_is_cf =p.MCIsCF();
    k_is_conv =p.MCIsFromConversion();
    k_is_fromtau=p.MCFromTau();
    k_mother_pdgid=p.MotherPdgId();
    k_mc_pdgid=p.MCMatchedPdgId();
    k_mother_index=p.MotherTruthIndex();
    k_mc_index=p.MCTruthIndex();
    k_isPF=p.IsPF();
    k_istrigmvavalid=p.IsTrigMVAValid();
    snu_id = p.SNUID();
    k_trkvx= p.TrkVx();
    k_trkvy= p.TrkVy();
    k_trkvz= p.TrkVz();
    k_abs_iso03=p.PFAbsIso(0.3);
    k_abs_iso04=p.PFAbsIso(0.4);
    k_trig_match= p.TrigMatch();
    k_eltype=p.GetType();
    k_mva=p.MVA();
    k_zzmva=p.ZZMVA();
    k_missing_hits=p.MissingHits();
    k_smearfactor=p.SmearFactor();
    k_in_conv=p.MCIsExternalConversion();
    k_isprompt=p.IsPromptFlag();
  }
  
  return *this;
}


void KElectron::SetIsMCExternalConversion(bool isconv){
  k_in_conv=isconv;
}


void KElectron::SetIsPromptFlag(bool ispromptflag){
  k_isprompt=ispromptflag;
}

void KElectron::SetSmearFactor(double smeare){
  k_smearfactor=smeare;

}

void KElectron::SetMissingHits(int mhits){
  k_missing_hits=mhits;
}

void KElectron::SetMVA(double mva){
  k_mva=mva;
}

void KElectron::SetZZMVA(double zzmva){
  k_zzmva=zzmva;
}


void  KElectron::SetType(int type){
  k_eltype= type;
}

bool KElectron::TriggerMatched(TString path){
  TString trig = k_trig_match;
  if(trig.Contains(path)) return true;
  return false;
}


Bool_t KElectron::PassTrigMVAHNTight() const{
  if(this->Pt() < 50.) {
    if(k_mva > 0.95) return true;
  }
  else {
    if((fabs(this->SCEta()) < 0.8) && k_mva > 0.76) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.72) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.70) return true;
  }
  return false;

}


Bool_t KElectron::PassTrigMVAHNTightv3() const{
  
  float mva_cut=0.85;
  if(fabs(this->SCEta()) > 1.479) mva_cut=0.9;
  if(this->Pt() < 40.) {
    if(k_mva > mva_cut) return true;
  }
  else if (this->Pt() < 50.){
    float mvacut_1 = mva_cut - (((mva_cut - 0.76) / 10.) * ( this->Pt() - 25.));
    float mvacut_2 = mva_cut - (((mva_cut - 0.72) / 10.) * ( this->Pt() - 25.));
    float mvacut_3 = mva_cut - (((mva_cut - 0.70) / 10.) * ( this->Pt() - 25.));

    if((fabs(this->SCEta()) < 0.8) && k_mva > mvacut_1) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > mvacut_2) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > mvacut_3) return true;
  }
  else {
    if((fabs(this->SCEta()) < 0.8) && k_mva > 0.76) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.72) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.70) return true;
  }
  return false;

}

Bool_t KElectron::PassTrigMVAHNTightvX(float c1) const{

  float mva_cut=c1;
  if(fabs(this->SCEta()) > 1.479) mva_cut=c1;
  else if(fabs(this->SCEta()) > 0.8) mva_cut=c1;
  else mva_cut=c1;

  if(k_mva > mva_cut) return true;
  return false;

}

Bool_t KElectron::PassTrigMVAHNTightv4() const{

  float mva_cut=0.5;
  if(fabs(this->SCEta()) > 1.479) mva_cut=0.5;
  else if(fabs(this->SCEta()) > 0.8) mva_cut=0.825;
  else mva_cut=0.9;

  if(k_mva > mva_cut) return true;
  return false;

}



Bool_t KElectron::PassTrigMVAHNTightv2(float pt1, float pt2, float mva_cut, float mva_cut_ec) const{

  if(fabs(this->SCEta()) > 1.479) mva_cut=mva_cut_ec;
  if(this->Pt() < pt1) {
    if(k_mva > mva_cut) return true;
    else return false;
  }
  else if (this->Pt() < pt2){
    float mvacut_1 = mva_cut - (((mva_cut - 0.76) / 10.) * ( this->Pt() - 25.));
    float mvacut_2 = mva_cut - (((mva_cut - 0.72) / 10.) * ( this->Pt() - 25.));
    float mvacut_3 = mva_cut - (((mva_cut - 0.70) / 10.) * ( this->Pt() - 25.));

    if((fabs(this->SCEta())  < 0.8) && k_mva > mvacut_1) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > mvacut_2) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > mvacut_3) return true;
  }
  else {
    if((fabs(this->SCEta()) < 0.8) && k_mva > 0.76) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.72) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.70) return true;
  }
  return false;

}


Bool_t KElectron::PassTrigMVAGENTTight() const{

  if(this->Pt() < 15.) {
    if((fabs(this->SCEta()) < 0.8) && k_mva > 0.77) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.56) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.48) return true;

  }
  else if (this->Pt() < 25.){
    float mvacut_1 = 0.77 - (((0.77 - 0.52) / 10.) * ( this->Pt() - 15.)); 
    float mvacut_2 = 0.56 - (((0.56 - 0.11) / 10.) * ( this->Pt() - 15.)); 
    float mvacut_3 = 0.48 - (((0.48 + 0.01) / 10.) * ( this->Pt() - 15.)); 
    
    if((fabs(this->SCEta()) < 0.8) && k_mva > mvacut_1) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > mvacut_2) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > mvacut_3) return true;
  }
  else {
    if((fabs(this->SCEta()) < 0.8) && k_mva > 0.52) return true;
    if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.11) return true;
    if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > -0.01) return true;
  }
  return false;

}

Bool_t KElectron::PassTrigMVAHNLoose() const{
/*
  //==== ELECTRON_HN_FAKELOOSE
  if((fabs(this->SCEta()) < 0.8) && k_mva > -0.02) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > -0.52) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > -0.52) return true;
*/

/*
  //==== ELECTRON_HN_FAKELOOSEv1 opti
  //==== Iso 0.6 Opti
  //==== Based on light-haevy min diff
  if((fabs(this->SCEta()) < 0.8) && k_mva > -0.08) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > -0.08) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.56) return true;
*/
/*
  //==== ELECTRON_HN_FAKELOOSEv1_LoosenSIP opti
  //==== Iso 0.6 Opti
  //==== Based on light-haevy min diff
  if((fabs(this->SCEta()) < 0.8) && k_mva > -0.35) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > -0.36) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.37) return true;
*/

  //==== ELECTRON_HN_FAKELOOSEv7 opti
  //==== Iso 0.6 Opti
  //==== Based on light-haevy min diff
  if((fabs(this->SCEta()) < 0.8) && k_mva > -0.1) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.1) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > -0.1) return true;

/*
  //==== ELECTRON_HN_FAKELOOSEv2 opti
  //==== Iso 0.4 Opti
  //==== Based on light-haevy min diff
  if((fabs(this->SCEta()) < 0.8) && k_mva > 0.15) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.11) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.63) return true;
*/
/*
  //==== ELECTRON_HN_FAKELOOSEv2 (old)
  //==== Iso 0.4 Opti, but Ghent pt binning
  //==== Based on light-haevy min diff

  if((fabs(this->SCEta()) < 0.8) && k_mva > 0.50) return true; // 0.2 is the optmized one, but let's try 0.50
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > 0.13) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > 0.64) return true;
*/

  return false;
}

Bool_t KElectron::PassTrigMVAGENTLoose() const{
  if((fabs(this->SCEta()) < 0.8) && k_mva > -0.02) return true;
  if((fabs(this->SCEta())  > 0.8) &&(fabs(this->SCEta())  < 1.479)  && k_mva > -0.52) return true;
  if((fabs(this->SCEta())  < 2.5) &&(fabs(this->SCEta())  > 1.479) && k_mva > -0.52) return true;

  return false;
}


///// SETTING CLASS VARIABLES

void KElectron::SetIsFromTau(bool istau){
  k_is_fromtau=istau;
}

void KElectron::SetMotherPdgId(int type){
  k_mother_pdgid=type;
}

void KElectron::SetMCMatchedPdgId(int type){
  k_mc_pdgid=type;
}

void KElectron::SetMotherTruthIndex(int mindex){
  k_mother_index=mindex;
}

void KElectron::SetMCTruthIndex(int tindex){
  k_mc_index=tindex;
}



void KElectron::SetIsChargeFlip(bool iscf){
  k_is_cf=iscf;
}


void KElectron::SetIsPhotonConversion(bool isconv){
  k_is_conv=isconv;
}

void KElectron::SetSCEta(Double_t sceta){
  k_sceta = sceta;
}


void KElectron::Setdz(double d_z){ 
  k_dz = d_z;
}

void KElectron::Setdxy(double d_xy){ 
  k_dxy = d_xy;
}
void KElectron::Setdxy_sig2D(double d_xysig2D){
  k_dxy_sig2D = d_xysig2D;
}
void KElectron::Setdxy_sig3D(double d_xysig3D){
  k_dxy_sig3D = d_xysig3D;
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

void KElectron::SetPFRelMiniIsoBeta(Double_t reliso){
  k_electrons_minirelIsoBeta = reliso;

}


void KElectron::SetPFRelMiniIsoRho(Double_t reliso){
  k_electrons_minirelIsoRho = reliso;

}

void KElectron::SetPFAbsIso(Double_t cone,Double_t absiso){
  if(cone == 0.3) k_abs_iso03=absiso;
  else  if(cone == 0.4) k_abs_iso04=absiso;
}




void KElectron::SetGsfCtfScPixCharge(bool gsfctfscpix_ch){
  k_gsf_ctscpix_charge = gsfctfscpix_ch;
}

void KElectron::SetGsfScPixCharge(bool gsfscpix_ch){
  k_gsf_scpix_charge = gsfscpix_ch;
}

void KElectron::SetGsfCtfCharge(bool gsfctf_ch){
  k_gsf_ct_charge = gsfctf_ch;
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
void KElectron::SetPassHLT(Bool_t hlt){
  pass_hltid= hlt;
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

void KElectron::SetPassMVAZZ(Bool_t pass){
  pass_notrigmva_zz= pass;
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




bool KElectron::PassCustomID(TString IDlabel){
  
   bool pass=true;
   
   std::vector<TString> IDlist;

  // -- only basic cuts on pt/eta
   if(CheckIDList(IDlabel, "ELECTRON_PTETA",IDlist)){
    if(this->Pt() < 10)pass=false;
    if(this->AbsEta() > 2.5) pass=false;
    return pass;
  }

   // -- HN pair analyis loose
   else if (CheckIDList(IDlabel, "EL_HN_NN_Loose",IDlist)){
    IDlist.push_back("");
    if(!this->PassCustomID("ELECTRON_PTETA"))  pass=false;
    if(!this->PassHEEP()) pass=false;
    return pass;
  }
   
   // -- HN pair analyis tight
   
   else if (CheckIDList(IDlabel, "EL_HN_NN_Tight",IDlist)){
     
     if(!this->PassCustomID("EL_HN_NN_Loose"))  pass=false;
     if(!this->PassLoose()) pass=false;
     return pass;
  }
  //if(IsoValue("reliso_03") > GetIDIso(IDlabel,"reliso_03") )pass=false;  

   // -- return true if no ID is given
  if(IDlabel == "") return true;
  else   {
    
    std::cout  << "KElectron::PassCustomID(ID) " << IDlabel << "  wrong IDlabel."   <<  std::endl;
    std::cout  << "-------------------------------------------------------------------" <<  std::endl;
    std::cout  << "IDs allowed are:" <<  std::endl;
    std::cout  << "-------------------------------------------------------------------" <<  std::endl;
    for(unsigned int i= 0 ; i < IDlist.size(); i++){
      cout << IDlist.at(i) << endl;
    }
    exit(0);

  }

  return false;

  
}

Double_t KElectron::GetIDIso(TString IDlabel, TString isotype){
  
  ///cutstring can be reliso_03, reliso_04, miniiso_03, miniiso_04

  TString cutstring="";
  if(IDlabel == "ELECTRON_PTETA"){
    cutstring = "reliso_03";
    if (cutstring != isotype) return 10000000000.;
    if(this->IsEBFiducial())  return 1000.;
    else  return 1000.;
    
  }
  return 10000000000.;
  
}
