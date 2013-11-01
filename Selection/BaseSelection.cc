#include "BaseSelection.h"

BaseSel::BaseSel() {}

BaseSel::~BaseSel() {}

void BaseSel::reset(EventBase evb){
  k_event_base = evb;
  dz_cut = 1000000.;
  pt_cut_max = 1000000.;
  pt_cut_min = 0.;
  eta_cut_min = -10.;
  eta_cut = 10.;
  relIso_cut  = 100000.;
  relIsoMIN_cut = 0.;
  chiNdof_cut = 10000.;
  chiNdofMIN_cut = 0.;
  dxy_cut = 100000.;
  dxyMIN_cut = -1000000.;
}

void BaseSel::SetPt(Double_t minPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void BaseSel::SetPt(Double_t minPt, Double_t maxPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void BaseSel::SetEta(Double_t Eta) {
  Eta ? eta_cut=Eta : eta_cut=3.0;
  eta_cut_min=0.0;
}

void BaseSel::SetEta(Double_t minEta, Double_t Eta) {
  minEta ? eta_cut_min=minEta : eta_cut_min=0.0;
  Eta ? eta_cut=Eta : eta_cut=3.0;
}

void BaseSel::SetRelIso(Double_t RelIso) {
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
  relIsoMIN_cut=0.0;
}

void BaseSel::SetRelIso(Double_t RelIsoMIN, Double_t RelIso) {
  RelIsoMIN ? relIsoMIN_cut=RelIsoMIN : relIsoMIN_cut=0.0;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
}

void BaseSel::SetChiNdof(Double_t ChiNdof) {
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
  chiNdofMIN_cut=0.0;
}

void BaseSel::SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof) {
  ChiNdofMIN ? chiNdofMIN_cut=ChiNdofMIN : chiNdofMIN_cut=0.0;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
}

void BaseSel::SetBSdxy(Double_t set_dxy) {
  set_dxy ? dxy_cut=set_dxy : dxy_cut=2.0;
  dxyMIN_cut=0.0;
}

void BaseSel::SetBSdxy(Double_t dxyMIN, Double_t set_dxy) {
   dxyMIN ? dxyMIN_cut=dxyMIN : dxyMIN_cut=0.0;
   set_dxy ? dxy_cut=dxy : dxy_cut=2.0;
}

void BaseSel::SetBSdz(Double_t set_dz) {
  set_dz ? dz_cut=set_dz : dz_cut=2.0;
}
