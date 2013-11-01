#include "MuonSelection.h"

using namespace snu;

MuonSel::MuonSel() {};

MuonSel::~MuonSel() {};


void MuonSel::MuonSelection( std::vector<KMuon>& leptonColl) {
  
  std::vector<KMuon> allmuons = k_event_base.GetBaseMuons();
  
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    if (muit->Pt() > 0.01)      LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    

    
    /// TIGHT MUON frmo muon POG
    (muit->IsPF()==1 && muit->IsGlobal()==1 && muit->validHits() >0 && muit->validPixHits()>0 && muit->validStations()>1 && muit->ActiveLayer() >5) ? individual = true :individual = false;
    
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && muit->IsoEcalVeto() < ECalDeposit_max && ( muit->IsoHcalVeto() >= HCalDeposit_min || muit->IsoEcalVeto() >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;
    ///// ETA and pt cut
    (fabs(muit->Eta()) < eta_cut && muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max && muit->PtError()/muit->Pt()<=0.10) ? etaPt=true : etaPt =false;

    
    (muit->GlobalChi2() <chiNdof_cut && LeptonRelIso < relIso_cut && fabs(muit->dZ())<dz_cut && fabs(muit->dXY())<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || muit->GlobalChi2()  >=chiNdofMIN_cut || fabs(muit->dXY())>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    
    if (etaPt  && DepositVeto && individual &&RelIsod0Chi2){
      leptonColl.push_back(*muit);    
    }
  }
    
}

void MuonSel::TightMuonSelection(std::vector<KMuon>& leptonColl) {
  
  std::vector<KMuon> allmuons = k_event_base.GetBaseMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    if (muit->Pt() > 0.01) LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    
    if (D0Error < 1E-6) D0Error = 1E-6;
    
    /// TIGHT MUON frmo muon POG
    (muit->IsPF()==1 && muit->IsGlobal()==1 && muit->validHits() >0 && muit->validPixHits()>0 && muit->validStations()>1 && muit->ActiveLayer() >5) ? individual = true :individual = false;
    
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && muit->IsoEcalVeto() < ECalDeposit_max && ( muit->IsoHcalVeto() >= HCalDeposit_min || muit->IsoEcalVeto() >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;
    ///// ETA and pt cut
    (fabs(muit->Eta()) < eta_cut && muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max && muit->PtError()/muit->Pt()<=0.10) ? etaPt=true : etaPt =false;

    
    (muit->GlobalChi2() <chiNdof_cut && LeptonRelIso < relIso_cut && fabs(muit->dZ())<dz_cut && fabs(muit->dXY())<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || muit->GlobalChi2()  >=chiNdofMIN_cut || fabs(muit->dXY())>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;

    if (etaPt  && DepositVeto && individual &&RelIsod0Chi2)
      leptonColl.push_back(*muit);    
  }
  
}


void MuonSel::SetDeposits(Double_t ECalDeposit , Double_t HCalDeposit) {
    ECalDeposit ? ECalDeposit_max = ECalDeposit : ECalDeposit_max=4.0;
    HCalDeposit ? HCalDeposit_max = HCalDeposit : HCalDeposit_max=6.0;
    ECalDeposit_min = 0.0;
    HCalDeposit_min = 0.0;
}

void MuonSel::SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2) {
    ECalDeposit1 ? ECalDeposit_min = ECalDeposit1 : ECalDeposit_min=0.0;
    HCalDeposit1 ? HCalDeposit_min = HCalDeposit1 : HCalDeposit_min=0.0;
    ECalDeposit2 ? ECalDeposit_max = ECalDeposit2 : ECalDeposit_max=4.0;
    HCalDeposit2 ? HCalDeposit_max = HCalDeposit2 : HCalDeposit_max=6.0;
}
