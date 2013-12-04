#include "MuonSelection.h"

using namespace snu;

MuonSelection::MuonSelection(LQEvent ev) :
  BaseSelection()
{
  k_lqevent = ev;  
};

MuonSelection::~MuonSelection() {};


void MuonSelection::Selection( std::vector<KMuon>& leptonColl) {
  
  bool m_debug = false;
  std::vector<KMuon> allmuons = k_lqevent.GetBaseMuons();
  
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    
    
    /// TIGHT MUON from muon POG
    (muit->IsPF()==1 && 
     muit->IsGlobal()==1 && 
     muit->validHits() >0 && 
     muit->validPixHits()>0 && 
     muit->validStations()>1 && 
     muit->ActiveLayer() >5) 
     ? individual = true :individual = false;

    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && 
     muit->IsoEcalVeto() < ECalDeposit_max && 
    (muit->IsoHcalVeto() >= HCalDeposit_min || 
     muit->IsoEcalVeto() >= ECalDeposit_min) ) 
     ? DepositVeto=true : DepositVeto=false;
    
    bool pass_selection(true);
    if(apply_general && !individual) pass_selection = false;
    if(m_debug&&apply_general && !individual) cout << "Fails individual " << endl;
    
    if(apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) pass_selection = false;
    if(m_debug&&apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) cout << "Fails pt cut " << endl;
    
 
    if(apply_etacut && !(fabs(muit->Eta()) < eta_cut)) pass_selection =false;
    if(m_debug&&apply_etacut && !(fabs(muit->Eta()) < eta_cut))  cout << "Fails eta cut " << endl;

    if(apply_deposit && !DepositVeto) pass_selection = false;
    if(m_debug&&apply_deposit && !DepositVeto) cout << "Fails DepositVeto " << endl;
    
    if(apply_chi2cut && !(muit->GlobalChi2() <chiNdof_cut) && !( muit->GlobalChi2()  >=chiNdofMIN_cut)) pass_selection = false;
    if(m_debug&&apply_chi2cut && !(muit->GlobalChi2() <chiNdof_cut) && !( muit->GlobalChi2()  >=chiNdofMIN_cut)) cout << "Fails chi2 cut " << endl;

    if(apply_relisocut && !(LeptonRelIso < relIso_cut) &&! ( LeptonRelIso >= relIsoMIN_cut)) pass_selection = false;
    if(m_debug&&apply_relisocut && !(LeptonRelIso < relIso_cut) &&! ( LeptonRelIso >= relIsoMIN_cut)) cout << "Fails iso cut " << endl;
    
    if(apply_dzcut && !(fabs(muit->dZ())<dz_cut)) pass_selection = false;
    if(m_debug&&apply_dzcut && !(fabs(muit->dZ())<dz_cut)) cout << "Fails  dz cut "<<  endl;

    if(apply_dxycut && !(fabs(muit->dXY())<dxy_cut)) pass_selection = false;
    if(m_debug&&apply_dxycut && !(fabs(muit->dXY())<dxy_cut)) cout << "Fails  dxy cut" <<  endl;

    if(pass_selection) leptonColl.push_back(*muit);    

  }/// muon loop end

  return;
}  
  

void MuonSelection::HNLooseMuonSelection(std::vector<KMuon>& leptonColl) {

  std::vector<KMuon> allmuons = k_lqevent.GetBaseMuons();  
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    //// Make Loose selection
    leptonColl.push_back(*muit);    
  }
  return;
}


void MuonSelection::HNTightMuonSelection(std::vector<KMuon>& leptonColl) {
  
  std::vector<KMuon> allmuons = k_lqevent.GetBaseMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    if (muit->Pt() > 0.01) LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    
    if (D0Error < 1E-6) D0Error = 1E-6;
    
    /// TIGHT MUON frmo muon POG
    (muit->IsPF()==1 && 
     muit->IsGlobal()==1 && 
     muit->validHits() >0 && 
     muit->validPixHits()>0 && 
     muit->validStations()>1 && 
     muit->ActiveLayer() >5) 
      ? individual = true :individual = false;
    
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && 
     muit->IsoEcalVeto() < ECalDeposit_max && 
     ( muit->IsoHcalVeto() >= HCalDeposit_min || muit->IsoEcalVeto() >= ECalDeposit_min) ) 
      ? DepositVeto=true : DepositVeto=false;

    ///// ETA and pt cut
    (fabs(muit->Eta()) < eta_cut && 
     muit->Pt() >= pt_cut_min && 
     muit->Pt() < pt_cut_max && 
     muit->PtError()/muit->Pt()<=0.10) 
      ? etaPt=true : etaPt =false;

    
    (muit->GlobalChi2() <chiNdof_cut && 
     LeptonRelIso < relIso_cut && 
     fabs(muit->dZ())<dz_cut && 
     fabs(muit->dXY())<dxy_cut && 
     ( LeptonRelIso >= relIsoMIN_cut || muit->GlobalChi2()  >=chiNdofMIN_cut || fabs(muit->dXY())>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;

    if (etaPt  && DepositVeto && individual &&RelIsod0Chi2)
      leptonColl.push_back(*muit);    
  }
  
  return;
}


void MuonSelection::SetDeposits(Double_t ECalDeposit , Double_t HCalDeposit) {
    ECalDeposit ? ECalDeposit_max = ECalDeposit : ECalDeposit_max=4.0;
    HCalDeposit ? HCalDeposit_max = HCalDeposit : HCalDeposit_max=6.0;
    ECalDeposit_min = 0.0;
    HCalDeposit_min = 0.0;
}

void MuonSelection::SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2) {
    ECalDeposit1 ? ECalDeposit_min = ECalDeposit1 : ECalDeposit_min=0.0;
    HCalDeposit1 ? HCalDeposit_min = HCalDeposit1 : HCalDeposit_min=0.0;
    ECalDeposit2 ? ECalDeposit_max = ECalDeposit2 : ECalDeposit_max=4.0;
    HCalDeposit2 ? HCalDeposit_max = HCalDeposit2 : HCalDeposit_max=6.0;
}


MuonSelection& MuonSelection::operator= (const MuonSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms);
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

MuonSelection::MuonSelection(const MuonSelection& ms):
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;  
};

