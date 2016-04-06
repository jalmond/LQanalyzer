#include "BaseSelection.h"

BaseSelection::BaseSelection() {
 
  dz_cut = 1000000.;
  pt_cut_max = 1000000.;
  pt_cut_min = 0.;
  eta_cut_min = -100.;
  eta_cut = 100.;
  jpt_cut_max = 1000000.;
  jpt_cut_min = 0.;
  jeta_cut_min = -100.;
  jeta_cut = 100.;
  relIso_cut  = 10000000.;
  relIsoMIN_cut = 0.;
  chiNdof_cut = 10000.;
  chiNdofMIN_cut = 0.;
  dxy_cut = 100000.;
  dxyMIN_cut = -1000000.;
  k_id = ELECTRON_HN_TIGHT;
  
  apply_ptcut=false;
  apply_etacut=false;
  apply_jptcut=false;
  applypileuptool= false;
  apply_jetacut=false;
  apply_relisocut=false;
  apply_chi2cut=false;
  apply_dxycut=false;
  apply_dzcut=false;
  apply_general=false;
  apply_deposit=false;
  
  apply_ID= false;
  apply_convcut= false;
  apply_chargeconst = false;

}

BaseSelection& BaseSelection::operator= (const BaseSelection& bs) 
{
  if(this != &bs){
    dz_cut = bs.dz_cut;
    pt_cut_max = bs.pt_cut_max;  
    pt_cut_min = bs.pt_cut_min; 
    eta_cut_min = bs.eta_cut_min; 
    eta_cut = bs.eta_cut; 
    jpt_cut_max = bs.jpt_cut_max;
    jpt_cut_min = bs.jpt_cut_min;
    jeta_cut_min = bs.jeta_cut_min; 
    jeta_cut = bs.jeta_cut; 
    relIso_cut  = bs.relIso_cut; 
    relIsoMIN_cut = bs.relIsoMIN_cut;
    chiNdof_cut = bs.chiNdof_cut; 
    chiNdofMIN_cut = bs.chiNdofMIN_cut;
    dxy_cut = bs.dxy_cut; 
    dxyMIN_cut = bs.dxyMIN_cut;
    k_id = bs.k_id;
    applypileuptool=bs.applypileuptool;
    apply_ptcut= bs.apply_ptcut;
    apply_etacut= bs.apply_etacut;
    apply_jptcut= bs.apply_jptcut;
    apply_jetacut= bs.apply_jetacut;
    apply_relisocut= bs.apply_relisocut;
    apply_chi2cut= bs.apply_chi2cut;
    apply_dxycut= bs.apply_dxycut;
    apply_dzcut= bs.apply_dzcut;
    apply_general= bs.apply_general;
    apply_deposit= bs.apply_deposit;
    apply_ID= bs.apply_ID;
    apply_convcut= bs.apply_convcut;
    apply_chargeconst = bs.apply_chargeconst;
  
  }
  return *this;
}


BaseSelection::BaseSelection(const BaseSelection& bs) {
  dz_cut = bs.dz_cut;
  pt_cut_max = bs.pt_cut_max;  
  pt_cut_min = bs.pt_cut_min; 
  eta_cut_min = bs.eta_cut_min; 
  eta_cut = bs.eta_cut; 
  jpt_cut_max = bs.jpt_cut_max;
  jpt_cut_min = bs.jpt_cut_min;
  jeta_cut_min = bs.jeta_cut_min; 
  jeta_cut = bs.jeta_cut; 
  relIso_cut  = bs.relIso_cut; 
  relIsoMIN_cut = bs.relIsoMIN_cut;
  chiNdof_cut = bs.chiNdof_cut; 
  chiNdofMIN_cut = bs.chiNdofMIN_cut;
  dxy_cut = bs.dxy_cut; 
  dxyMIN_cut = bs.dxyMIN_cut;
  k_id = bs.k_id;
  applypileuptool=bs.applypileuptool;
  apply_ptcut= bs.apply_ptcut;
  apply_etacut= bs.apply_etacut;
  apply_jptcut= bs.apply_jptcut;
  apply_jetacut= bs.apply_jetacut;
  apply_relisocut= bs.apply_relisocut;
  apply_chi2cut= bs.apply_chi2cut;
  apply_dxycut= bs.apply_dxycut;
  apply_dzcut= bs.apply_dzcut;
  apply_general= bs.apply_general;
  apply_deposit= bs.apply_deposit;
  apply_ID= bs.apply_ID;
  apply_convcut= bs.apply_convcut;
  apply_chargeconst = bs.apply_chargeconst;
  

}



BaseSelection::~BaseSelection() {}

void BaseSelection::reset(){
  dz_cut = 1000000.;
  pt_cut_max = 1000000.;
  pt_cut_min = 0.;
  jpt_cut_max = 1000000.;
  jpt_cut_min = 0.;
  eta_cut_min = -100.;
  eta_cut = 100.;
  jeta_cut_min = -100.;
  jeta_cut = 100.;
  relIso_cut  = 10000000.;
  relIsoMIN_cut = 0.;
  chiNdof_cut = 10000.;
  chiNdofMIN_cut = 0.;
  dxy_cut = 100000.;
  dxyMIN_cut = -1000000.;
  k_id = ELECTRON_HN_TIGHT;
  applypileuptool=false;
  apply_ptcut=false;
  apply_etacut=false;
  apply_jptcut=false;
  apply_jetacut=false;
  apply_relisocut=false;
  apply_chi2cut=false;
  apply_dxycut=false;
  apply_dzcut=false;
  apply_ID= false;
  apply_convcut= false;
  apply_chargeconst = false;

}

void BaseSelection::SetPt(Double_t minPt) {
  apply_ptcut=true;
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;

}

void BaseSelection::SetPt(Double_t minPt, Double_t maxPt) {
  apply_ptcut=true;
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void BaseSelection::SetID(ID id){
  apply_ID = true;
  k_id = id;
}


void BaseSelection::SetCheckCharge(bool check){
  apply_chargeconst = check;
}
void BaseSelection::SetUseJetPileUp(bool use){
  applypileuptool=use;
}

void BaseSelection::SetApplyConvVeto(bool apply){
  apply_convcut=apply;
}

void BaseSelection::SetJetPt(Double_t minPt) {
  apply_jptcut=true;
  minPt ? jpt_cut_min=minPt : jpt_cut_min=0.0;
  jpt_cut_max=10000.0;
}



void BaseSelection::SetEta(Double_t Eta) {
  apply_etacut=true;
  Eta ? eta_cut=Eta : eta_cut=3.0;
  eta_cut_min=0.0;
  
}


void BaseSelection::SetJetEta(Double_t Eta) {
  apply_jetacut=true;
  Eta ? jeta_cut=Eta : jeta_cut=3.0;
  jeta_cut_min=0.0;
}

void BaseSelection::SetEta(Double_t minEta, Double_t Eta) {
  apply_etacut=true;
  minEta ? eta_cut_min=minEta : eta_cut_min=0.0;
  Eta ? eta_cut=Eta : eta_cut=3.0;
}

void BaseSelection::SetRelIso(Double_t RelIso) {
  apply_relisocut=true;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
  relIsoMIN_cut=0.0;
}

void BaseSelection::SetRelIso(Double_t RelIsoMIN, Double_t RelIso) {
  apply_relisocut=true;
  RelIsoMIN ? relIsoMIN_cut=RelIsoMIN : relIsoMIN_cut=0.0;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
}

void BaseSelection::SetChiNdof(Double_t ChiNdof) {
  apply_chi2cut=true;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
  chiNdofMIN_cut=0.0;
}

void BaseSelection::SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof) {
  apply_chi2cut=true;
  ChiNdofMIN ? chiNdofMIN_cut=ChiNdofMIN : chiNdofMIN_cut=0.0;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
}

void BaseSelection::SetBSdxy(Double_t set_dxy) {
  apply_dxycut=true;
  set_dxy ? dxy_cut=set_dxy : dxy_cut=2.0;
  dxyMIN_cut=0.0;
}

void BaseSelection::SetBSdxy(Double_t dxyMIN, Double_t set_dxy) {
  apply_dxycut=true;
   dxyMIN ? dxyMIN_cut=dxyMIN : dxyMIN_cut=0.0;
   set_dxy ? dxy_cut=dxy : dxy_cut=2.0;
}

void BaseSelection::SetBSdz(Double_t set_dz) {
  apply_dxycut=true;
  set_dz ? dz_cut=set_dz : dz_cut=2.0;
}
