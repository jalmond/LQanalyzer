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
  k_scphi=-999;
  k_ip2D=-999;
  k_ip3D=-999;
  k_sip3D=-999;
  k_dz=-999;
  k_gsf_ctscpix_charge=false;
  k_gsf_scpix_charge=false; 
  k_gsf_ct_charge=false;
  k_hasmatchconvphot=false; 
  k_pf_chargedhad_iso03=-999;
  k_pf_photon_iso03=-999;
  k_pf_neutral_iso03=-999;
  k_electron_relIsoBeta03 = -999.;
  k_electron_relIsoRho03 = -999.;
  k_rel_miniiso=-999;
  k_en_uncorr = -999.;
  k_pt_scale_up = -999.;
  k_pt_scale_down = -999.;
  k_pt_smear_up = -999.;
  k_pt_smear_down = -999.;
  k_idbit = -999;
  k_mc_matched=false;
  k_is_cf=false;
  k_is_conv=false;
  k_is_fromtau=false;
  k_mother_pdgid=-1;
  k_mc_pdgid=-1;
  k_mother_index=-1;
  k_mc_index=-1;
  k_eltype=-999;
  k_mva_iso=-999;
  k_mva_noniso=-999;
  k_missing_hits=-999;
  k_ecaldriven= -999;
  k_is_conv=false;
  k_isprompt=false;

  k_electron_Full5x5_SigmaIEtaIEta=-999; 
  k_electron_dEtaInSeed=-999;
  k_electron_dPhiIn=-999; 
  k_electron_HoverE=-999;
  k_electron_InvEminusInvP  =-999;
}

/**
 * Copy constructor.
 */
KElectron::KElectron(const KElectron& el) :
    KParticle(el)
{
  

  k_sceta= el.SCEta();
  k_scphi= el.SCPhi();
  k_ip2D= el.IP2D();
  k_ip3D= el.IP3D();
  k_sip3D= el.SIP3D();
  k_dz= el.dz();
  k_gsf_ctscpix_charge= el.GsfCtfScPixChargeConsistency();
  k_gsf_scpix_charge= el.GsfScPixChargeConsistency();
  k_gsf_ct_charge= el.GsfCtfChargeConsistency();
  k_hasmatchconvphot= el.PassesConvVeto();
  k_pf_chargedhad_iso03= el.PFChargedHadronIso(0.3);
  k_pf_photon_iso03 = el.PFPhotonIso(0.3);
  k_pf_neutral_iso03= el.PFNeutralHadronIso(0.3);
  k_electron_relIsoBeta03 = el.PFRelIsoBeta(0.3);
  k_electron_relIsoRho03 = el.PFRelIsoRho(0.3);
  k_rel_miniiso=el.PFRelMiniIso();
  k_pt_scale_up = el.PtScaleUp();
  k_pt_scale_down = el.PtScaleDown();
  k_pt_smear_up = el.PtSmearUp();
  k_pt_smear_down =el.PtSmearDown();
  k_idbit = el.IDBit();
  
  k_mc_matched=el.MCMatched();
  k_is_cf=el.MCIsCF();
  k_is_conv=el.MCIsFromConversion();
  k_is_fromtau=el.MCFromTau();
  k_mother_pdgid=el.MotherPdgId();
  k_mc_pdgid=el.MCMatchedPdgId();
  k_mother_index=el.MotherTruthIndex();
  k_mc_index=el.MCTruthIndex();

  k_eltype=el.GetType();
  k_mva_iso = el.MVAIso();
  k_mva_noniso = el.MVANonIso();
  k_missing_hits=el.MissingHits();
  k_ecaldriven = el.EcalDriven();
  k_is_conv=el.MCIsExternalConversion();
  k_isprompt=el.IsPromptFlag();
  k_electron_Full5x5_SigmaIEtaIEta=el.Full5x5_SigmaIEtaIEta();
  k_electron_dEtaInSeed=el.dEtaInSeed();
  k_electron_dPhiIn=el.dPhiIn();
  k_electron_HoverE=el.HoverE();
  k_electron_InvEminusInvP  =el.InvEminusInvP();

}



KElectron::~KElectron()
{
}

void KElectron::Reset()
{
  KParticle::Reset();
  k_sceta=-999;
  k_scphi=-999;
  k_ip2D=-999;
  k_ip3D=-999;
  k_sip3D=-999;
  k_dz=-999;
  k_gsf_ctscpix_charge=false;
  k_gsf_scpix_charge=false;
  k_gsf_ct_charge=false;
  k_hasmatchconvphot=false;
  k_pf_chargedhad_iso03=-999;
  k_pf_photon_iso03=-999;
  k_pf_neutral_iso03=-999;
  k_electron_relIsoBeta03 = -999.;
  k_electron_relIsoRho03 = -999.;
  k_rel_miniiso=-999;
  k_en_uncorr = -999.;
  k_pt_scale_up = -999.;
  k_pt_scale_down = -999.;
  k_pt_smear_up = -999.;
  k_pt_smear_down = -999.;
  k_idbit = -999;
  
  k_mc_matched=false;
  k_is_cf=false;
  k_is_conv=false;
  k_is_fromtau=false;
  k_mother_pdgid=-1;
  k_mc_pdgid=-1;
  k_mother_index=-1;
  k_mc_index=-1;
  k_eltype=-999;
  k_mva_iso=-999;
  k_mva_noniso=-999;
  k_missing_hits=-999;
  k_ecaldriven=-999;
  k_is_conv=false;
  k_isprompt=false;

  k_electron_Full5x5_SigmaIEtaIEta=-999;
  k_electron_dEtaInSeed=-999;
  k_electron_dPhiIn=-999;
  k_electron_HoverE=-999;
  k_electron_InvEminusInvP  =-999;

}



KElectron& KElectron::operator= (const KElectron& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_sceta= p.SCEta();
    k_scphi= p.SCPhi();
    k_ip2D= p.IP2D();
    k_ip3D= p.IP3D();
    k_sip3D= p.SIP3D();
    k_dz= p.dz();
    k_gsf_ctscpix_charge= p.GsfCtfScPixChargeConsistency();
    k_gsf_scpix_charge= p.GsfScPixChargeConsistency();
    k_gsf_ct_charge= p.GsfCtfChargeConsistency();
    k_hasmatchconvphot= p.PassesConvVeto();
    k_pf_chargedhad_iso03= p.PFChargedHadronIso(0.3);
    k_pf_photon_iso03 = p.PFPhotonIso(0.3);
    k_pf_neutral_iso03= p.PFNeutralHadronIso(0.3);
    k_electron_relIsoBeta03 = p.PFRelIsoBeta(0.3);
    k_electron_relIsoRho03 = p.PFRelIsoRho(0.3);
    k_rel_miniiso=p.PFRelMiniIso();
    k_pt_scale_up = p.PtScaleUp();
    k_pt_scale_down = p.PtScaleDown();
    k_pt_smear_up = p.PtSmearUp();
    k_pt_smear_down =p.PtSmearDown();
    k_idbit = p.IDBit();

    k_mc_matched=p.MCMatched();
    k_is_cf=p.MCIsCF();
    k_is_conv=p.MCIsFromConversion();
    k_is_fromtau=p.MCFromTau();
    k_mother_pdgid=p.MotherPdgId();
    k_mc_pdgid=p.MCMatchedPdgId();
    k_mother_index=p.MotherTruthIndex();
    k_mc_index=p.MCTruthIndex();
    k_eltype=p.GetType();
    k_mva_iso = p.MVAIso();
    k_mva_noniso = p.MVANonIso();
    k_missing_hits=p.MissingHits();
    k_ecaldriven = p.EcalDriven();
    k_is_conv=p.MCIsExternalConversion();
    k_isprompt=p.IsPromptFlag();
    k_electron_Full5x5_SigmaIEtaIEta=p.Full5x5_SigmaIEtaIEta();
    k_electron_dEtaInSeed=p.dEtaInSeed();
    k_electron_dPhiIn=p.dPhiIn();
    k_electron_HoverE=p.HoverE();
    k_electron_InvEminusInvP  =p.InvEminusInvP();

  }
  
  return *this;
}


void KElectron::SetIsMCExternalConversion(bool isconv){
  k_is_conv=isconv;
}


void KElectron::SetIsPromptFlag(bool ispromptflag){
  k_isprompt=ispromptflag;
}

void KElectron::SetMissingHits(int mhits){
  k_missing_hits=mhits;
}

void KElectron::SetEcalDriven(int edriven){
  k_ecaldriven = edriven;
}

void KElectron::SetMVAIso(double mva){
  k_mva_iso=mva;
}

void KElectron::SetMVANonIso(double mva){
  k_mva_noniso=mva;
}


void  KElectron::SetType(int type){
  k_eltype= type;
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

void KElectron::SetSCPhi(Double_t scphi){
  k_scphi = scphi;
}




void KElectron::Setdz(double d_z){ 
  k_dz = d_z;
}

void KElectron::SetIP2D(double ip2D){ 
  k_ip2D = ip2D;
}


void KElectron::SetIP3D(double ip3D){
  k_ip3D = ip3D;
}

void KElectron::SetSIP3D(double sip3D){
  k_sip3D = sip3D;
}

 
void KElectron::SetPFChargedHadronIso(Double_t cone, Double_t pf_ch){
   if(cone == 0.3)  k_pf_chargedhad_iso03= pf_ch;
}

void KElectron::SetPFPhotonIso(Double_t cone,Double_t pf_ph){
  if(cone == 0.3)   k_pf_photon_iso03 = pf_ph;
}

void KElectron::SetPFNeutralHadronIso(Double_t cone,Double_t pf_ne){
  if(cone == 0.3)  k_pf_neutral_iso03 = pf_ne;
}

void KElectron::SetPFRelIsoBeta(double cone,Double_t reliso){
  if(cone == 0.3)  k_electron_relIsoBeta03 = reliso;

}


void KElectron::SetPFRelIsoRho(double cone,Double_t reliso){
  if(cone == 0.3)k_electron_relIsoRho03 = reliso;

}


void KElectron::SetPFRelMiniIso(Double_t reliso){
  k_rel_miniiso=reliso;
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


void KElectron::SetEnUncorr(Double_t Eun){
  k_en_uncorr =  Eun;
}

void KElectron::SetScaleEUp(Double_t Eup){
  k_pt_scale_up= Eup;
}

void KElectron::SetScaleEDown(Double_t Edown){
  k_pt_scale_down= Edown;
}

void KElectron::SetSmearEUp(Double_t Eup){
  k_pt_smear_up= Eup;
}

void KElectron::SetSmearEDown(Double_t Edown){
  k_pt_smear_down= Edown;
}



void KElectron::SetIDBit(Int_t id){
  k_idbit = id;
}


void KElectron::SetIsMCMatched(Bool_t matched){
  k_mc_matched = matched;
}



/*void KElectron::SetGSF(Double_t pt, Double_t eta, Double_t phi, Double_t m){
  
  k_gsp_pt = pt;
  k_gsp_eta = eta;
  k_gsp_phi = phi;
  k_gsp_m = m;
  }*/


void KElectron::SetElIDVariables(double  electron_Full5x5_SigmaIEtaIEta , double electron_dEtaInSeed ,double  electron_dPhiIn,double  electron_HoverE  ,double  electron_InvEminusInvP){

  k_electron_Full5x5_SigmaIEtaIEta = electron_Full5x5_SigmaIEtaIEta;
  k_electron_dEtaInSeed  =electron_dEtaInSeed;
  k_electron_dPhiIn = electron_dPhiIn;
  k_electron_HoverE = electron_HoverE;
  k_electron_InvEminusInvP = electron_InvEminusInvP;
  
}
			       
