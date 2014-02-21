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
  k_isEB =false;
  k_isEE = false; 
  k_trackdrivenseed = false;
  k_chargeconstistency = false;
  k_ecaldrivenseed= false;
  k_hasmatchconvphot=false; 
  k_missinghits=0;
  k_trkiso=0.;
  k_ecaliso=0.;
  k_hcaliso=0.;
  k_delta_etatrkSC=0.;
  k_delta_phitrkSC=0.;
  k_sigmaIEtaIEta=0.;
  k_hoe=0.;
  k_caloE=0.; 
  k_cluster_over_p=0.;
  k_trkvx=0.;
  k_trkvy=0.;
  k_trkvz=0.;
  k_dxy=0;
  k_dz=0;
  k_passID=0;
}

/**
 * Copy constructor.
 */
KElectron::KElectron(const KElectron& el) :
    KParticle(el)
{
  k_isEB = el.isEB();
  k_isEE = el.isEE();
  k_trackdrivenseed = el.TrackerDrivenSeed();
  k_chargeconstistency = el.ChargeConsistency();
  k_ecaldrivenseed= el.EcalDrivenSeed();
  k_hasmatchconvphot=el.HasMatchedConvPhot();
  k_missinghits= el.MissingHits();
  k_trkiso=el.TrkIso();
  k_ecaliso=el.ECalIso();
  k_hcaliso=el.HCalIso();
  k_delta_etatrkSC=el.DeltaEtaTrkSC();
  k_delta_phitrkSC=el.DeltaPhiTrkSC();
  k_sigmaIEtaIEta=el.SigmaIEtaIEta();
  k_hoe=el.HoE();
  k_caloE=el.caloEnergy(); 
  k_cluster_over_p=el.SuperClusterOverP();
  k_trkvx=el.TrkVx();
  k_trkvy=el.TrkVy();
  k_trkvz=el.TrkVz();
  k_dxy=el.dxy();
  k_dz=el.dz();
  k_passID=el.PassID();
}


KElectron::~KElectron()
{
}

void KElectron::Reset()
{
  KParticle::Reset();
  k_isEB =false;
  k_isEE = false; 
  k_trackdrivenseed = false;
  k_chargeconstistency = false;
  k_ecaldrivenseed= false;
  k_hasmatchconvphot=false; 
  k_missinghits=0;
  k_trkiso=0.;
  k_ecaliso=0.;
  k_hcaliso=0.;
  k_delta_etatrkSC=0.;
  k_delta_phitrkSC=0.;
  k_sigmaIEtaIEta=0.;
  k_hoe=0.;
  k_caloE=0.; 
  k_cluster_over_p=0.;
  k_trkvx=0.;
  k_trkvy=0.;
  k_trkvz=0.;
  k_dxy=0;
  k_dz=0;
  k_passID=0;
}



KElectron& KElectron::operator= (const KElectron& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_isEB = p.isEB();
    k_isEE = p.isEE();
    k_trackdrivenseed = p.TrackerDrivenSeed();
    k_chargeconstistency = p.ChargeConsistency();
    k_ecaldrivenseed= p.EcalDrivenSeed();
    k_hasmatchconvphot=p.HasMatchedConvPhot();
    k_missinghits= p.MissingHits();
    k_trkiso=p.TrkIso();
    k_ecaliso=p.ECalIso();
    k_hcaliso=p.HCalIso();
    k_delta_etatrkSC=p.DeltaEtaTrkSC();
    k_delta_phitrkSC=p.DeltaPhiTrkSC();
    k_sigmaIEtaIEta=p.SigmaIEtaIEta();
    k_hoe=p.HoE();
    k_caloE=p.caloEnergy(); 
    k_cluster_over_p=p.SuperClusterOverP();
    k_trkvx=p.TrkVx();
    k_trkvy=p.TrkVy();
    k_trkvz=p.TrkVz();
    k_dxy= p.dxy();
    k_dz=p.dz();
    k_passID=p.PassID();
  }
    
    return *this;
}


void KElectron::Setdz(double d_z){ 
  k_dxy = d_z;
}

void KElectron::Setdxy(double d_xy){ 
  k_dxy = d_xy;
}

void KElectron::SetElectronPassId(Int_t passid){
  k_passID = passid;
}
  
void KElectron::SetisEB(Bool_t iseb){
  k_isEB = iseb;
}

void KElectron::SetisEE(Bool_t isee){
  k_isEE = isee;
}
void KElectron::SetTrackerDrivenSeed(Bool_t trackdrivenseed){
  k_trackdrivenseed = trackdrivenseed;
}
void KElectron::SetEcalDrivenSeed(Bool_t ecaldrivenseed){  
  k_ecaldrivenseed = ecaldrivenseed;
}

void KElectron::SetTrkIso(Double_t trkiso){  
  k_trkiso  = trkiso;
}
void KElectron::SetECalIso(Double_t ecaliso){  
  k_ecaliso = ecaliso;
}
void KElectron::SetHCalIso(Double_t hcaliso){  
  k_hcaliso = hcaliso;
}

void KElectron::SetChargeConsistency(Bool_t chargeconsistency){  
  k_chargeconstistency = chargeconsistency;
}

void KElectron::SetMissingHits(Int_t missinghits){  
  k_missinghits = missinghits;
}

void KElectron::SetHasMatchedConvPhot(Bool_t hasmatchConvPhot){  
  k_hasmatchconvphot = hasmatchConvPhot;
}
void KElectron::SetDeltaEtaTrkSC(Double_t delta_etatrkSC){  
  k_delta_etatrkSC = delta_etatrkSC;
}
void KElectron::SetDeltaPhiTrkSC(Double_t delta_phitrkSC){  
  k_delta_phitrkSC = delta_phitrkSC;
}
 
void KElectron::SetSigmaIEtaIEta(Double_t sigmaIEtaIEta){
  k_sigmaIEtaIEta = sigmaIEtaIEta;
}
void KElectron::SetHoE(Double_t hoe){  
  k_hoe = hoe;
}
void KElectron::SetcaloEnergy(Double_t caloE){  
  k_caloE = caloE;
}

void KElectron::SetSuperClusterOverP(Double_t cluster_over_p){  
  k_cluster_over_p = cluster_over_p;
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




