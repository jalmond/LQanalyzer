#include "MuonSelection.h"

using namespace snu;

MuonSelection::MuonSelection(LQEvent ev) :
  BaseSelection()
{
  k_lqevent = ev;  
};

MuonSelection::~MuonSelection() {};



void MuonSelection::BasicSelection( std::vector<KMuon>& leptonColl) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++)
    {

      if(muit->Pt() == 0.) continue;

      bool pass_selection = true;

      /// ONLY CUT ON PT/ETA/LOOSE ID
      if( muit->Pt() < pt_cut_min ) pass_selection = false;
      if( fabs(muit->Eta()) > eta_cut) pass_selection =false;
 
     
      if(! (PassID(MUON_LOOSE, *muit))) pass_selection =false;
      

      if(pass_selection) leptonColl.push_back(*muit);
    }
}


void MuonSelection::SkimSelection( std::vector<KMuon>& leptonColl) {


  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++)
    {
      
      if(muit->Pt() == 0.) continue;

      bool pass_selection = true;
      
      /// ONLY CUT ON PT/ETA/LOOSE ID
      if( muit->Pt() < pt_cut_min ) pass_selection = false;
      if( fabs(muit->Eta()) > eta_cut) pass_selection =false;
      
      if(!PassID(MUON_LOOSE, *muit)) pass_selection =false;
      if (pass_selection) leptonColl.push_back(*muit);  
    }
  
}

void MuonSelection::Selection( std::vector<KMuon>& leptonColl) {
  
  bool m_debug = false;
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++)
    { 

      bool pass_selection(true);      
      if(muit->Pt() == 0.) continue;
      
      //// Calculate PF isolation
      /// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation
      if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
      else LeptonRelIso = 9999.;
      if (LeptonRelIso<0) LeptonRelIso=0.0001;    
      
      if(apply_relisocut && !( LeptonRelIso < relIso_cut)) pass_selection = false;

      
      if(apply_ptcut && ! ( muit->Pt() > pt_cut_min )) pass_selection = false;
      if(m_debug&&apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) cout << "Fails pt cut " << endl;
      
      if(apply_etacut && !(fabs(muit->Eta()) < eta_cut)) pass_selection =false;
      if(m_debug&&apply_etacut && !(fabs(muit->Eta()) < eta_cut))  cout << "Fails eta cut " << endl;
  
      /// impact parameter cuts
      // Uses fabs(recoMu.muonBestTrack()->dxy(vertex->position())) as described in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon 
      // Also stores dB() on pat::Muon  as dxy_pat
      // Also stores D0 

      if(apply_dzcut && !(muit->dZ()<  dz_cut )) pass_selection = false;
      if(apply_dxycut && !(muit->dXY()< dxy_cut )) pass_selection = false;

      if(apply_ID && !PassID(MUON_TIGHT, *muit)) pass_selection =false;
      
      
      /// ENERGY DEPOSIT
      (muit->IsoHcalVeto() < HCalDeposit_max && 
       muit->IsoEcalVeto() < ECalDeposit_max && 
       (muit->IsoHcalVeto() >= HCalDeposit_min || 
	muit->IsoEcalVeto() >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;
      
      if(apply_deposit && !DepositVeto) pass_selection = false;
      if(m_debug&&apply_deposit && !DepositVeto) cout << "Fails DepositVeto " << endl;
      
      
      if(apply_chi2cut && !(muit->GlobalChi2() <chiNdof_cut) && !( muit->GlobalChi2()  >=chiNdofMIN_cut)) pass_selection = false;
      if(m_debug&&apply_chi2cut && !(muit->GlobalChi2() <chiNdof_cut) && !( muit->GlobalChi2()  >=chiNdofMIN_cut)) cout << "Fails chi2 cut " << endl;
      
      //// ADD EXTRA  cut on D0sig? or same vertex?     
      if(pass_selection) leptonColl.push_back(*muit);    

  }/// muon loop end

  BaseSelection::reset();
  return;
}  


////////// PREDEFINED MUON SELECTIONS
  

void MuonSelection::HNVetoMuonSelection(std::vector<KMuon>& leptonColl) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);
    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// VETO MUON SELECTION
    if(!( muit->Pt() > 10. )) pass_selection = false;
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!( LeptonRelIso < 0.2)) pass_selection = false;
    if(!(muit->GlobalChi2() < 500.)) pass_selection = false;
    if(!(muit->dZ()< 100.  )) pass_selection = false;
    if(!(muit->dXY()< 20.0 )) pass_selection = false;
    if(!PassID(MUON_LOOSE, *muit)) pass_selection =false;

    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < 600.0 &&
     muit->IsoEcalVeto() < 400.0 ) ? DepositVeto=true : DepositVeto=false;
    if(!DepositVeto) pass_selection = false;


    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);
  }
  return;
}

void MuonSelection::HNLooseMuonSelection(std::vector<KMuon>& leptonColl) {
  
  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();  
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
    //// Muon Loose selection
    if(!( muit->Pt() > 20. )) pass_selection = false;
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit)) pass_selection =false;
    if(!( LeptonRelIso < 0.4)) pass_selection = false;
    if(!(muit->IsGlobal()==1      )) pass_selection = false;
    if( muit->validHits() == 0     ) pass_selection = false;
    if( muit->validPixHits() == 0)   pass_selection = false;
    if( muit->validStations() <= 1 ) pass_selection = false;
    if( muit->ActiveLayer() <= 5   ) pass_selection = false;
    if( fabs(muit->dXY())    >= 0.2) pass_selection = false;
    if( fabs(muit->dZ())    >= 0.1)  pass_selection = false;
    if(!(muit->GlobalChi2() < 50.)) pass_selection = false;


    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < 6.0 &&
     muit->IsoEcalVeto() < 4.0 ) ? DepositVeto=true : DepositVeto=false;
    if(!DepositVeto) pass_selection = false;
  


    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);    
  }
  return;
}


void MuonSelection::HNTightMuonSelection(std::vector<KMuon>& leptonColl) {
  
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    

    /// TIGHT MUON SELECTION
    if(!( muit->Pt() > 20. )) pass_selection = false;
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!( LeptonRelIso < 0.2)) pass_selection = false;
    if(!(muit->dZ()< 0.10  )) pass_selection = false;
    if(!(muit->dXY()< 0.005 )) pass_selection = false;
    
    /// TIGHT MUON from muon POG
    if(!PassID(MUON_TIGHT, *muit)) pass_selection =false;

    /// ENERGY DEPOSIT
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < 6.0 &&
     muit->IsoEcalVeto() < 4.0 ) ? DepositVeto=true : DepositVeto=false;
    if(!DepositVeto) pass_selection = false;


    if(pass_selection)  leptonColl.push_back(*muit);    
  }
  
  return;
}

bool MuonSelection::PassID(ID id, snu::KMuon mu){
  
  
  /// Taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
  bool passID(true);
  if (id == MUON_LOOSE) {
    if(!(mu.IsPF() == 1)) passID = false;
    if(!(mu.IsGlobal()==1 || mu.IsTracker() ))passID = false; 
  }


  if (id == MUON_TIGHT) {
    if(!(mu.IsPF() == 1        )) passID = false;
    if(!(mu.IsGlobal()==1      )) passID = false;
    if( mu.validHits() == 0     ) passID = false;
    if( mu.validPixHits() == 0) passID = false;
    if( mu.validStations() <= 1 ) passID = false;
    if( mu.ActiveLayer() <= 5   ) passID = false;
    if( fabs(mu.dXY())    >= 0.2) passID = false;
    if( fabs(mu.dZ())    >= 0.5)  passID = false;
    if( mu.GlobalChi2() >=  10.)  passID = false;
  }
  
  return passID;
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

