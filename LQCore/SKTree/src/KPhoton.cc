#include "KPhoton.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KPhoton)

/**
 *Default constructor.
 */
KPhoton::KPhoton() :
  KParticle()
{
  k_ph_chhadiso_noEA=0.; 
  k_ph_puchhadiso_noEA=0.; 
  k_ph_nhadiso_noEA=0.; 
  k_ph_phiso_noEA=0.; 
  k_ph_rhoiso=0.; 
  k_ph_chhadiso=0.; 
  k_ph_photoniso=0.; 
  k_ph_nhadiso=0.; 
  k_ph_sigietaieta=0.; 
  k_ph_r9=0.; 
  k_ph_hovere=0.; 
  k_ph_sceta=0.; 
  k_ph_scphi=0.; 
  k_ph_scrawe=0.; 
  k_ph_scpreshower_e=0.;
  k_ph_isloose=0; 
  k_ph_ismedium=0; 
  k_ph_istight=0; 
  k_ph_passmva=0; 
  k_mc_matched=0; 
  k_ph_haspixseed=0;
  k_ph_passelveto=0;
  
}

/**
 * Copy constructor.
 */
KPhoton::KPhoton(const KPhoton& ph) :
    KParticle(ph)
{
  k_ph_chhadiso_noEA=ph.ChargedHadIsoNoEA();
  k_ph_puchhadiso_noEA=ph.puChargedHadIsoNoEA();
  k_ph_nhadiso_noEA=ph.NeutalHadIsoNoEA();
  k_ph_phiso_noEA=ph.PhotonIsoNoEA();
  k_ph_rhoiso=ph.RhoIso();
  k_ph_chhadiso=ph.ChargedHadIso();
  k_ph_photoniso=ph.PhotonIso();
  k_ph_nhadiso=ph.NeutalHadIso();
  k_ph_sigietaieta=ph.SigmaIetaIeta();
  k_ph_r9=ph.R9();
  k_ph_hovere=ph.HoverE();
  k_ph_sceta=ph.SCEta();
  k_ph_scphi=ph.SCPhi();
  k_ph_scrawe=ph.SCRawE();
  k_ph_scpreshower_e= ph.SCPreShowerE();
  k_ph_isloose=ph.isLoose();
  k_ph_ismedium=ph.isMedium();
  k_ph_istight=ph.isTight();
  k_ph_passmva=ph.passMVA();
  k_mc_matched=ph.mcMatched();
  k_ph_haspixseed=ph.hasPixSeed();
  k_ph_passelveto=ph.passElVeto();

}


KPhoton::~KPhoton()
{
}

void KPhoton::Reset()
{
  KParticle::Reset();
  k_ph_chhadiso_noEA=0.;
  k_ph_puchhadiso_noEA=0.;
  k_ph_nhadiso_noEA=0.;
  k_ph_phiso_noEA=0.;
  k_ph_rhoiso=0.;
  k_ph_chhadiso=0.;
  k_ph_photoniso=0.;
  k_ph_nhadiso=0.;
  k_ph_sigietaieta=0.;
  k_ph_r9=0.;
  k_ph_hovere=0.;
  k_ph_sceta=0.;
  k_ph_scphi=0.;
  k_ph_scrawe=0.;
  k_ph_scpreshower_e=0.;
  k_ph_isloose=0;
  k_ph_ismedium=0;
  k_ph_istight=0;
  k_ph_passmva=0;
  k_mc_matched=0;
  k_ph_haspixseed=0;
  k_ph_passelveto=0;


}



KPhoton& KPhoton::operator= (const KPhoton& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_ph_chhadiso_noEA=p.ChargedHadIsoNoEA();
    k_ph_puchhadiso_noEA=p.puChargedHadIsoNoEA();
    k_ph_nhadiso_noEA=p.NeutalHadIsoNoEA();
    k_ph_phiso_noEA=p.PhotonIsoNoEA();
    k_ph_rhoiso=p.RhoIso();
    k_ph_chhadiso=p.ChargedHadIso();
    k_ph_photoniso=p.PhotonIso();
    k_ph_nhadiso=p.NeutalHadIso();
    k_ph_sigietaieta=p.SigmaIetaIeta();
    k_ph_r9=p.R9();
    k_ph_hovere=p.HoverE();
    k_ph_sceta=p.SCEta();
    k_ph_scphi=p.SCPhi();
    k_ph_scrawe=p.SCRawE();
    k_ph_scpreshower_e= p.SCPreShowerE();
    k_ph_isloose=p.isLoose();
    k_ph_ismedium=p.isMedium();
    k_ph_istight=p.isTight();
    k_ph_passmva=p.passMVA();
    k_mc_matched=p.mcMatched();
    k_ph_haspixseed=p.hasPixSeed();
    k_ph_passelveto=p.passElVeto();
    
  }
  
  return *this;
}

void KPhoton::SetIsLoose   (bool b){
  k_ph_isloose=b;
}
void KPhoton::SetIsMedium  (bool b){
  k_ph_ismedium=b;
}

void KPhoton::SetIsTight   (bool b){
  k_ph_istight=b;
}

void KPhoton::SetPassMVA   (bool b){
  k_ph_passmva=b;
}

void KPhoton::SetMCMatched (bool b){
  k_mc_matched=b;
}

void KPhoton::SetHasPixSeed(bool b){
  k_ph_haspixseed=b;
}

void KPhoton::SetPassElVeto(bool b){
  k_ph_passelveto=b;
}


// Double

void KPhoton::SetChargedHadIsoNoEA(double d){
  k_ph_chhadiso_noEA=d;
}

void KPhoton::SetpuChargedHadIsoNoEA(double d){
  k_ph_puchhadiso_noEA=d;
}

void KPhoton::SetNeutalHadIsoNoEA(double d){
  k_ph_nhadiso_noEA=d;
}

void KPhoton::SetPhotonIsoNoEA(double d){
  k_ph_phiso_noEA=d;
}

void KPhoton::SetRhoIso(double d){
  k_ph_rhoiso=d;
}

void KPhoton::SetChargedHadIso(double d){
  k_ph_chhadiso=d;
}

void KPhoton::SetPhotonIso(double d){
  k_ph_photoniso=d;
}

void KPhoton::SetNeutalHadIso(double d){
  k_ph_nhadiso=d;
}

void KPhoton::SetSigmaIetaIeta(double d){
  k_ph_sigietaieta=d;
}

void KPhoton::SetR9(double d){
  k_ph_r9=d;
}

void KPhoton::SetHoverE(double d){
  k_ph_hovere=d;
}

void KPhoton::SetSCEta(double d){
  k_ph_sceta=d;
}

void KPhoton::SetSCPhi(double d){
  k_ph_scphi=d;
}

void KPhoton::SetSCRawE(double d){
  k_ph_scrawe=d;
}

void KPhoton::SetSCPreShowerE(double d){
  k_ph_scpreshower_e=d;
}

