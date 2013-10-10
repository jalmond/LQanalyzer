#include "LeptonSelection.h"

Lep::Lep() {}

Lep::~Lep() {}

void Lep::SetPt(Double_t minPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  pt_cut_max=10000.0;
}

void Lep::SetPt(Double_t minPt, Double_t maxPt) {
  minPt ? pt_cut_min=minPt : pt_cut_min=0.0;
  maxPt ? pt_cut_max=maxPt : pt_cut_max=10000.0;
}

void Lep::SetEta(Double_t Eta) {
  Eta ? eta_cut=Eta : eta_cut=3.0;
  eta_cut_min=0.0;
}

void Lep::SetEta(Double_t minEta, Double_t Eta) {
  minEta ? eta_cut_min=minEta : eta_cut_min=0.0;
  Eta ? eta_cut=Eta : eta_cut=3.0;
}

void Lep::SetRelIso(Double_t RelIso) {
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
  relIsoMIN_cut=0.0;
}

void Lep::SetRelIso(Double_t RelIsoMIN, Double_t RelIso) {
  RelIsoMIN ? relIsoMIN_cut=RelIsoMIN : relIsoMIN_cut=0.0;
  RelIso ? relIso_cut=RelIso : relIso_cut=10.0;
}

void Lep::SetChiNdof(Double_t ChiNdof) {
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
  chiNdofMIN_cut=0.0;
}

void Lep::SetChiNdof(Double_t ChiNdofMIN, Double_t ChiNdof) {
  ChiNdofMIN ? chiNdofMIN_cut=ChiNdofMIN : chiNdofMIN_cut=0.0;
  ChiNdof ? chiNdof_cut=ChiNdof : chiNdof_cut=100.0;
}

void Lep::SetBSdxy(Double_t set_dxy) {
  set_dxy ? dxy_cut=set_dxy : dxy_cut=2.0;
   dxyMIN_cut=0.0;
}

void Lep::SetBSdxy(Double_t dxyMIN, Double_t set_dxy) {
   dxyMIN ? dxyMIN_cut=dxyMIN : dxyMIN_cut=0.0;
   set_dxy ? dxy_cut=dxy : dxy_cut=2.0;
}

void Lep::SetBSdz(Double_t set_dz) {
  set_dz ? dz_cut=set_dz : dz_cut=2.0;
}
