#include "MuonSelection.h"

using namespace snu;

MuonSelection::MuonSelection(LQEvent ev) :
  BaseSelection()
{
  k_lqevent = ev;  
};

MuonSelection::~MuonSelection() {};



void MuonSelection::BasicSelection( std::vector<KMuon>& leptonColl, bool m_debug) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++)
    {

      if(muit->Pt() == 0.) continue;

      bool pass_selection = true;

      /// ONLY CUT ON PT/ETA/LOOSE ID
      if( muit->Pt() < pt_cut_min ) {
	pass_selection = false;
	if(m_debug) cout << "BasicSelection:: Muon Fails Pt cut " << endl; 
      }
      if( fabs(muit->Eta()) > eta_cut){
	pass_selection =false;
	if(m_debug) cout << "BasicSelection:: Muon Fails Eta cut " << endl; 
      }
      if(! (PassID(MUON_LOOSE, *muit, m_debug))){
	pass_selection =false;
	if(m_debug) cout << "BasicSelection:: Muon Fails Loose Selection" << endl;
      }
      
      if(pass_selection) leptonColl.push_back(*muit);
    }
  if(m_debug) cout << "BasicSelection::Number of muons = " << leptonColl.size() << endl;
  return;
}


void MuonSelection::SkimSelection( std::vector<KMuon>& leptonColl , bool m_debug) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++)
    {
      
      if(muit->Pt() == 0.) continue;

      bool pass_selection = true;
      
      /// ONLY CUT ON PT/ETA/LOOSE ID
      if( muit->Pt() < pt_cut_min ) {
        pass_selection = false;
        if(m_debug) cout << "SkimSelection:: Muon Fails Pt cut " << endl;
      }
      if( fabs(muit->Eta()) > eta_cut){
        pass_selection =false;
        if(m_debug) cout << "SkimSelection:: Muon Fails Eta cut " << endl;
      }
      if(! (PassID(MUON_LOOSE, *muit, m_debug))){
        pass_selection =false;
        if(m_debug) cout << "SkimSelection:: Muon Fails Loose Selection" << endl;
      }

      if (pass_selection) leptonColl.push_back(*muit);  
    }
  if(m_debug) cout << "SkimSelection::Number of muons = " << leptonColl.size() << endl;
  return;

}

void MuonSelection::Selection( std::vector<KMuon>& leptonColl, bool m_debug) {
  

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
      if(m_debug&&apply_relisocut && !( LeptonRelIso < relIso_cut))  cout << "Fails Selection::reliso cut " << endl;
      
      if(apply_ptcut && ! ( muit->Pt() > pt_cut_min )) pass_selection = false;
      if(m_debug&&apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) cout << "Fails Selection::pt cut " << endl;
      
      if(apply_etacut && !(fabs(muit->Eta()) < eta_cut)) pass_selection =false;
      if(m_debug&&apply_etacut && !(fabs(muit->Eta()) < eta_cut))  cout << "Fails Selection::eta cut " << endl;
  
      /// impact parameter cuts
      // Uses fabs(recoMu.muonBestTrack()->dxy(vertex->position())) as described in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon 
      // Also stores dB() on pat::Muon  as dxy_pat
      // Also stores D0 

      if(apply_dzcut && !(fabs(muit->dZ())<  dz_cut )) pass_selection = false;
      if(m_debug&&apply_dzcut && !(fabs(muit->dZ())<  dz_cut ))  cout << "Fails Selection::dz cut " << endl;
      if(apply_dxycut && !(fabs(muit->dXY())< dxy_cut )) pass_selection = false;
      if(m_debug&&apply_dxycut && !(fabs(muit->dXY())< dxy_cut ))cout << "Fails Selection::dxy cut " << endl;
      
      if(apply_ID && !PassID(k_id, *muit,m_debug)) pass_selection =false;
      if(m_debug&& apply_ID && !PassID(MUON_TIGHT, *muit)) cout << "Fails Selection::ID cut " << endl;
      
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
  

void MuonSelection::HNVetoMuonSelection(std::vector<KMuon>& leptonColl, bool m_debug) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  if(m_debug)cout << "Muon veto selection: Number of muons (no cuts) =" << allmuons.size() << endl;
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);
    if(muit->Pt() == 0.)   continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// VETO MUON SELECTION
    if(( muit->Pt() < 10. )) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail Pt cut" << endl;
    }
    else if(m_debug) cout << "muit->Pt() = " << muit->Pt() << endl;
    if(!(fabs(muit->Eta()) < 2.4)) {
      pass_selection =false;
      if(m_debug) cout << "HNVetoMuonSelection Fail Eta cut" << endl;
    }
    if(!( LeptonRelIso < 0.6)){
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail Isolation cut" << endl;
    }
    else if(m_debug) cout << "iso =  " << LeptonRelIso << endl;

    if(!(muit->GlobalChi2() < 500.)) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail chi2 cut" << endl;
    }
    else  if(m_debug) cout << "GlobalChi2 = " << muit->GlobalChi2()  << endl;
    if(!(fabs(muit->dZ())< 100.  )) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail dz cut" << endl;
    }
    else  if(m_debug) cout << "dZ = " << muit->dZ() << endl;
    if(!(fabs(muit->dXY())< 10.0 )) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail dxy cut" << endl;
    }
    if(!PassID(MUON_LOOSE, *muit,m_debug)) {
      pass_selection =false;
      if(m_debug) cout << "HNVetoMuonSelection Fail loose cut" << endl;
    }


    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < 600.0 &&
     muit->IsoEcalVeto() < 400.0 ) ? DepositVeto=true : DepositVeto=false;
    if(!DepositVeto) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoMuonSelection Fail deposit cut" << endl;
    }


    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);
  }
  return;
}

void MuonSelection::HNLooseMuonSelection(std::vector<KMuon>& leptonColl , bool m_debug) {
  
  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();  
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
    //// Muon Loose selection
    if(( muit->Pt() < 15. )) {
      pass_selection = false;
      if(m_debug) cout << "HNLooseMuonSelection Fail chi2 cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit, m_debug)) pass_selection =false;
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


void MuonSelection::HNLooseMuonSelection03(std::vector<KMuon>& leptonColl , bool m_debug) {

  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// Muon Loose selection
    if(( muit->Pt() < 15. )) {
      pass_selection = false;
      if(m_debug) cout << "HNLooseMuonSelection Fail chi2 cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit, m_debug)) pass_selection =false;
    if(!( LeptonRelIso < 0.3)) pass_selection = false;
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




void MuonSelection::HNLooseMuonSelection05(std::vector<KMuon>& leptonColl , bool m_debug) {

  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// Muon Loose selection
    if(( muit->Pt() < 15. )) {
      pass_selection = false;
      if(m_debug) cout << "HNLooseMuonSelection Fail chi2 cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit, m_debug)) pass_selection =false;
    if(!( LeptonRelIso < 0.5)) pass_selection = false;
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



bool MuonSelection::HNIsTight(KMuon muon, bool m_debug){
  
  bool pass_selection(true);
  
  if(muon.Pt() == 0.) return false;

  if (muon.Pt() > 0.01)      LeptonRelIso = (muon.SumIsoCHDR03() + std::max(0.0, muon.SumIsoNHDR03() + muon.SumIsoPHDR03() - 0.5* muon.SumPUIsoR03()))/muon.Pt() ;
  else LeptonRelIso = 9999.;
  if (LeptonRelIso<0) LeptonRelIso=0.0001;
  
  
  /// TIGHT MUON SELECTION
  if(( muon.Pt() < 15. )) {
    pass_selection = false;
    if(m_debug) cout << "Muon fails Tight pt cut " << endl;
  }
  if(!(fabs(muon.Eta()) < 2.4)) {
    pass_selection =false;
    if(m_debug) cout << "Muon fails Tight eta cut " <<endl;
  }
  if(!( LeptonRelIso < 0.05)) {
    pass_selection = false;
    if(m_debug) cout << "Muon fails Tight  reliso cut " <<endl;
  }
  if(!(fabs(muon.dZ())< 0.10  )) {
    pass_selection = false;
    if(m_debug) cout << "Muon fails Tight dZ cut (" << fabs(muon.dZ()) << ")" <<endl;
  }
  if(!(fabs(muon.dXY())< 0.005 )){
    pass_selection = false;
    if(m_debug) cout << "Muon fails Tight dXY " <<endl;
  }
  

  /// TIGHT MUON from muon POG
  if(!PassID(MUON_TIGHT, muon, m_debug)) pass_selection =false;

  /// ENERGY DEPOSIT
  /// ENERGY DEPOSIT
  (muon.IsoHcalVeto() < 6.0 &&
   muon.IsoEcalVeto() < 4.0 ) ? DepositVeto=true : DepositVeto=false;
  if(!DepositVeto){
    pass_selection = false;
    if(m_debug) cout << "Muon fails Tight deposit cut" <<endl;
  }
  
  return pass_selection;
}

void MuonSelection::HNTightHighPtMuonSelection(std::vector<snu::KMuon>& leptonColl) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    if(muit->Pt() > 200.){
      muit->SetPtEtaPhiM(muit->MuonCocktailPt(), muit->MuonCocktailEta(), muit->MuonCocktailPhi(), muit->M());
      muit->SetCharge(muit->MuonCocktailCharge());
      muit->Setdxy(muit->MuonCocktailTrkD0());
      muit->Setdz(muit->MuonCocktailTrkDz());
      muit->SetGlobalchi2(muit->MuonCocktailGlobalChi2());
      if(HNIsTight(*muit, false)) leptonColl.push_back(*muit);
    }
    else if(HNIsTight(*muit, false)) leptonColl.push_back(*muit);
  }
  return;
}

void MuonSelection::HNTightMuonSelection(std::vector<KMuon>& leptonColl, bool m_debug) {
  
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    if(HNIsTight(*muit, m_debug)) leptonColl.push_back(*muit);    
  }
  
  return;
}


////////// PREDEFINED MUON SELECTIONS FOR TOP ANALYSIS

void MuonSelection::TopVetoMuonSelection(std::vector<KMuon>& leptonColl, bool m_debug) {
  
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);
    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// VETO MUON SELECTION
    if(( muit->Pt() < 10. )) {
      pass_selection = false;
      if(m_debug) cout << "TopVetoMuonSelection Fail Pt cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.5)) {
      pass_selection =false;
      if(m_debug) cout << "TopVetoMuonSelection Fail Eta cut" << endl;
    }
    if(!( LeptonRelIso < 0.2)){
      pass_selection = false;
      if(m_debug) cout << "TopVetoMuonSelection Fail Isolation cut" << endl;
    }

    if(!PassID(MUON_LOOSE, *muit,m_debug)) {
      pass_selection =false;
      if(m_debug) cout << "TopVetoMuonSelection Fail loose cut" << endl;
    }

    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);
  }
  return;
}

// Intended use for di-lepton channel
void MuonSelection::TopLooseMuonSelection(std::vector<KMuon>& leptonColl , bool m_debug) {

  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// Muon Loose selection
    if(( muit->Pt() < 20. )) {
      pass_selection = false;
      if(m_debug) cout << "TopLooseMuonSelection Fail pT cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit, m_debug)) pass_selection =false;
    if(!( LeptonRelIso < 0.2)) pass_selection = false;


    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);
  }
  return;
}

void MuonSelection::TopLooseAIsoMuonSelection(std::vector<KMuon>& leptonColl , bool m_debug) {

  //### THIS SELECTION IS USED FOR MUON FAKES STUDIES
  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;
    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;

    //// Muon Loose selection
    if(( muit->Pt() < 20. )) {
      pass_selection = false;
      if(m_debug) cout << "TopLooseMuonSelection Fail pT cut" << endl;
    }
    if(!(fabs(muit->Eta()) < 2.4)) pass_selection =false;
    if(!PassID(MUON_LOOSE, *muit, m_debug)) pass_selection =false;
    if(!( LeptonRelIso > 0.2)) pass_selection = false;


    //// Make Loose selection
    if(pass_selection)leptonColl.push_back(*muit);
  }
  return;
}

void MuonSelection::TopTightMuonSelection(std::vector<KMuon>& leptonColl, bool m_debug) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;

    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    

    /// TIGHT MUON SELECTION
    if(( muit->Pt() < 26. )) {
      pass_selection = false;
      if(m_debug) cout << "Muon fails TopTight pt cut " << endl;
    }
    if(!(fabs(muit->Eta()) < 2.1)) {
      pass_selection =false;
      if(m_debug) cout << "Muon fails Tight eta cut " <<endl;
    }
    if(!( LeptonRelIso < 0.12)) {
		pass_selection = false;
		if(m_debug) cout << "Muon fails Tight  reliso cut " <<endl;
    }

    /// TIGHT MUON from muon POG
    if(!PassID(MUON_TIGHT, *muit, m_debug)) pass_selection =false;

    if(pass_selection)  leptonColl.push_back(*muit);
  }

  return;
}

void MuonSelection::TopTightAIsoMuonSelection(std::vector<KMuon>& leptonColl, bool m_debug) {

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){

    bool pass_selection(true);

    if(muit->Pt() == 0.) continue;

    if (muit->Pt() > 0.01)      LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()))/muit->Pt() ;
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    

    /// TIGHT MUON SELECTION
    if(( muit->Pt() < 26. )) {
      pass_selection = false;
      if(m_debug) cout << "Muon fails TopTight pt cut " << endl;
    }
    if(!(fabs(muit->Eta()) < 2.1)) {
      pass_selection =false;
      if(m_debug) cout << "Muon fails Tight eta cut " <<endl;
    }
    if(!( LeptonRelIso > 0.12)) {
		pass_selection = false;
		if(m_debug) cout << "Anti-Iso Muon selection : Tight  reliso cut " <<endl;
    }

    /// TIGHT MUON from muon POG
    if(!PassID(MUON_TIGHT, *muit, m_debug)) pass_selection =false;

    if(pass_selection)  leptonColl.push_back(*muit);
  }

  return;
}

bool MuonSelection::PassID(ID id, snu::KMuon mu, bool m_debug){
  
  
  /// Taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
  bool passID(true);
  if (id == MUON_LOOSE) {
    if(!(mu.IsPF() == 1)) {
      passID = false;
      if(m_debug)cout << "PassID: Fail isPF" << endl;
    }
    if(!(mu.IsGlobal()==1 || mu.IsTracker() == 1 )){
      passID = false; 
      if(m_debug){
	cout << "PassID: Fail isGlobal||isTracker" << endl;
	cout << "PassID: mu.IsGlobal()=  " << mu.IsGlobal() << endl;
	cout << "PassID: mu.IsTracker()= " << mu.IsTracker() << endl;
      }
    }
  }


  else if (id == MUON_TIGHT) {
    if(!(mu.IsPF() == 1        )){
      passID = false;
      if(m_debug)cout << "PassID: Fail isPF" << endl;
    }
    if(!(mu.IsGlobal()==1      )) {
      passID = false;
      if(m_debug)cout << "PassID: Fail isGlobal" << endl;
    }
    if( mu.validHits() == 0     ) {
      passID = false;
      if(m_debug)cout << "PassID: Fail validHit" << endl;
    }
    if( mu.validPixHits() == 0) {
      passID = false;
      if(m_debug)cout << "PassID: Fail validPixelHit" << endl;
    }
    if( mu.validStations() <= 1 ) {
      passID = false;
      if(m_debug)cout << "PassID: Fail validStations" << endl;
    }
    if( mu.ActiveLayer() <= 5   ) {
      passID = false;
      if(m_debug)cout << "PassID: Fail ActiveLayer " << endl;
    }
    if( fabs(mu.dXY())    >= 0.2) {
      passID = false;
      if(m_debug)cout << "PassID: Fail dXY" << endl;
    }
    if( fabs(mu.dZ())    >= 0.5) {
      passID = false;
      if(m_debug)cout << "PassID: Fail dZ" << endl;
    }
    if( mu.GlobalChi2() >=  10.){
      passID = false;
      if(m_debug) cout << "PassID: Fail  Chi2" << endl;
    }
  }
  
  else{
    cout << "Invalid ID set for muon selection" << endl;
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

