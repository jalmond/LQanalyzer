#include "MuonSelection.h"

using namespace snu;

MuonSelection::MuonSelection(LQEvent ev) :
  BaseSelection()
{
  k_lqevent = ev;  

};


////////////////////////////////////////////////                                                                                                                                                                                                                   
////// FUNCTIONS FOR SKTREEMAKER                                                                                                                                                                                                                                   
////////////////////////////////////////////////   

MuonSelection::~MuonSelection() {};

void MuonSelection::BasicSelection( std::vector<KMuon>& leptonColl,bool m_debug) {

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
      if(! (PassID("MUON_POG_LOOSE", *muit, m_debug))){
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
      if(! (PassID("MUON_POG_LOOSE", *muit, m_debug))){
        pass_selection =false;
        if(m_debug) cout << "SkimSelection:: Muon Fails Loose Selection" << endl;
      }

      if (pass_selection) leptonColl.push_back(*muit);  
    }
  if(m_debug) cout << "SkimSelection::Number of muons = " << leptonColl.size() << endl;
  return;

}


////////////////////////////////////////////////                                                                                                                                                                                                                   
////// FUNCTIONS FOR ANALYSIS CODE                                                                                                                                                                                                                                 
////////////////////////////////////////////////                                                                                                                                                                                                                   


void MuonSelection::SelectMuons(std::vector<KMuon>& leptonColl, TString muid, TString Option, double ptcut, double etacut){

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  int  SystDir=0;
  bool Syst_MuEn=false, DebugPrint=false;
  if(Option.Contains("Debug")) DebugPrint=true;
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir   = 1;
    else if(Option.Contains("Down")) SystDir   =-1;
    if     (Option.Contains("MuEn")) Syst_MuEn = true;
  }
  

  bool applyrochester = false;
  if(Option.Contains("roch")) applyrochester = true;
     
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    /// Check if roch corr is applied, and of not apply it to pt and iso
    if(applyrochester&&! muit->IsRochesterCorrected() && muit->Pt() < 200.) {
      float origpt = muit->Pt();
      float origreliso03=muit->RelIso03();
      float origreliso04=muit->RelIso04();
      muit->SetPtEtaPhiM(muit->RochPt(), muit->Eta(), muit->Phi(), muit->M());
      muit->SetRelIso(0.3, origreliso03*origpt/muit->RochPt());
      muit->SetRelIso(0.4, origreliso04*origpt/muit->RochPt());
      muit->SetIsRochesterCorrected(true);
    }

    if     (Syst_MuEn && SystDir>0) *muit *= muit->PtShiftedUp();
    else if(Syst_MuEn && SystDir<0) *muit *= muit->PtShiftedDown();

    

    if(MuonPass(*muit, muid, ptcut,etacut) ) leptonColl.push_back(*muit);

  }// end of el loop                                                                                                                                                                                                                                               

  return;
}



void MuonSelection::Selection( std::vector<KMuon>& leptonColl, bool applyrochester, TString Option){

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();

  int  SystDir=0;
  bool Syst_MuEn=false, DebugPrint=false;
  if(Option.Contains("Debug")) DebugPrint=true;
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir   = 1;
    else if(Option.Contains("Down")) SystDir   =-1;
    if     (Option.Contains("MuEn")) Syst_MuEn = true;
  }

  for(std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){ 

      bool pass_selection(true);      
      if(muit->Pt() == 0.) continue;

      if(applyrochester&&! muit->IsRochesterCorrected()) {
	float origpt = muit->Pt();
	float origreliso03=muit->RelIso03();
	float origreliso04=muit->RelIso04();
	muit->SetPtEtaPhiM(muit->RochPt(), muit->Eta(), muit->Phi(), muit->M());
	muit->SetRelIso(0.3, origreliso03*origpt/muit->RochPt());
	muit->SetRelIso(0.4, origreliso04*origpt/muit->RochPt());
	muit->SetIsRochesterCorrected(true);
      }

      if     (Syst_MuEn && SystDir>0) *muit *= muit->PtShiftedUp();
      else if(Syst_MuEn && SystDir<0) *muit *= muit->PtShiftedDown();


      TString MuID=GetString(k_id);
      if(apply_ID && !PassID(MuID, *muit)) pass_selection =false;
      if(DebugPrint && apply_ID && !PassID(MuID, *muit)) cout << "Fails Selection::ID cut " << endl;


      if(apply_ptcut && ! ( muit->Pt() > pt_cut_min )) pass_selection = false;
      if(DebugPrint && apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) cout << "Fails Selection::pt cut " << endl;
      
      if(apply_etacut && !(fabs(muit->Eta()) < eta_cut)) pass_selection =false;
      if(DebugPrint && apply_etacut && !(fabs(muit->Eta()) < eta_cut))  cout << "Fails Selection::eta cut " << endl;


      //// Calculate PF isolation
      /// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation
      if     (apply_relisocut && RelIsoType.Contains("Default"))    LeptonRelIso=muit->RelIso04();
      else if(apply_relisocut && RelIsoType.Contains("PFRelIso03")) LeptonRelIso=muit->RelIso03();
      else   LeptonRelIso=muit->RelIso04();
      
      if(apply_relisocut && !( LeptonRelIso < relIso_cut)) pass_selection = false;
      if(DebugPrint && apply_relisocut && !( LeptonRelIso < relIso_cut))  cout << "Fails Selection::reliso cut " << endl;
      
  
      /// impact parameter cuts
      // Uses fabs(recoMu.muonBestTrack()->dxy(vertex->position())) as described in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon 
      // Also stores dB() on pat::Muon  as dxy_pat, Also stores D0 
      if(apply_dzcut && !(fabs(muit->dZ())<  dz_cut )) pass_selection = false;
      if(DebugPrint && apply_dzcut && !(fabs(muit->dZ())<  dz_cut ))  cout << "Fails Selection::dz cut " << endl;

      if(apply_dxycut && !(fabs(muit->dXY())< dxy_cut )) pass_selection = false;
      if(DebugPrint && apply_dxycut && !(fabs(muit->dXY())< dxy_cut ))cout << "Fails Selection::dxy cut " << endl;

      if(apply_dxysigmin && !(fabs(muit->dXYSig2D()) >= dxySig_min )) pass_selection = false;
      if(DebugPrint && apply_dxysigmin && !(fabs(muit->dXYSig2D()) >= dxySig_min ))cout << "Fails Selection::dxySigMin cut " << endl;

      if(apply_dxysigmax && !(fabs(muit->dXYSig2D()) < dxySig_max )) pass_selection = false;
      if(DebugPrint && apply_dxysigmax && !(fabs(muit->dXYSig2D()) < dxySig_max ))cout << "Fails Selection::dxySigMin cut " << endl;

      
      if(apply_IP3Dmin && !(fabs(muit->dXYSig3D()) >= IP3D_min )) pass_selection = false;

      if(apply_IP3Dmax && !(fabs(muit->dXYSig3D()) < IP3D_max )) pass_selection = false;


      if(apply_chi2cut && !( muit->GlobalChi2() < chiNdof_cut && muit->GlobalChi2() >= chiNdofMIN_cut )) pass_selection = false;
      if(DebugPrint && apply_chi2cut && !( muit->GlobalChi2() <chiNdof_cut && muit->GlobalChi2()  >=chiNdofMIN_cut)) cout << "Fails chi2 cut " << endl;

      
      //// ADD EXTRA  cut on D0sig? or same vertex?     
      if(pass_selection) leptonColl.push_back(*muit);    

  }/// muon loop end

  BaseSelection::reset();
  return;
}  


float MuonSelection::IsoCutValue(snu::KMuon muon,TString muid, TString isotype){
  
  // This function is useful for ptcone varaiable to make sure correct isolation cut is applied to ID and ptcone value                                                                                                                                             
  return float(muon.GetIDIso(muid, isotype));

}

bool MuonSelection::MuonPass(snu::KMuon muon, TString muid, double ptcut, double etacut){

  /// Method used by DD class

  bool pass_selection = true;

  if (ptcut == -999.) ptcut = 10.;
  if (etacut == -999.) etacut = 2.5;


  /// PassCustomID in KMuon                                                                                                                                                                                                           
  if(!muon.PassCustomID(muid)) pass_selection = false;

  // pt and eta cuts                                                                                                                                                                                                                                               
  if(!(muon.AbsEta() < etacut)) pass_selection = false;
  if((muon.Pt() < ptcut))   pass_selection = false;

  return pass_selection;
}





////////// PREDEFINED MUON SELECTIONS FOR TOP ANALYSIS




/// NO LONGER NEEDED
bool MuonSelection::PassID(TString id, snu::KMuon mu, bool cutondxy, bool cutondz, bool cutonchi2, bool m_debug){

  /// Taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonIdRun2
  bool passID(true);
  if (id == "MUON_POG_LOOSE") {
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

  else if (id == "MUON_POG_MEDIUM") {
    if(!(mu.IsMedium())) passID=false;//IF ID var for med. is saved this could be changed.
  }

  else if (id == "MUON_POG_TIGHT") {
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
    if (cutondxy){
      if( fabs(mu.dXY())    >= 0.2) {
        passID = false;
        if(m_debug)cout << "PassID: Fail dXY" << endl;
      }
    }
    if(cutondz){
      if( fabs(mu.dZ())    >= 0.5) {
        passID = false;
        if(m_debug)cout << "PassID: Fail dZ" << endl;
      }
    }
    if(cutonchi2){
      if( mu.GlobalChi2() >=  10.){
        passID = false;
        if(m_debug) cout << "PassID: Fail  Chi2" << endl;
      }
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

