 #include "MuonSelection.h"

 using namespace snu;

 MuonSelection::MuonSelection(LQEvent ev) :
   BaseSelection()
 {
   k_lqevent = ev;  

 };


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
       if(! muit->IsLoose()){
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
       if(! muit->IsLoose()){
	 pass_selection =false;
	 if(m_debug) cout << "SkimSelection:: Muon Fails Loose Selection" << endl;
       }

       if (pass_selection) leptonColl.push_back(*muit);  
     }
   if(m_debug) cout << "SkimSelection::Number of muons = " << leptonColl.size() << endl;
   return;

 }

float MuonSelection::IsoCutValue(snu::KMuon muon,TString muid){ 
  
  UserIDConfig(muid);
  
  if(fabs(muon.Eta()) < 1.5) return relIsoBarrel_max;
  else return relIsoEndcap_max;
}



/// Method 1 to fill muons

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
	 float rochpt = muit->RochSF()*muit->Pt();
	 muit->SetPtEtaPhiM(muit->RochSF()*muit->Pt(), muit->Eta(), muit->Phi(), muit->M());
	 muit->SetRelIso(0.3, origreliso03*origpt/rochpt);
	 muit->SetRelIso(0.4, origreliso04*origpt/rochpt);
	 muit->SetIsRochesterCorrected(true);
       }

       //      if     (Syst_MuEn && SystDir>0) *muit *= muit->PtShiftedUp();
       //      else if(Syst_MuEn && SystDir<0) *muit *= muit->PtShiftedDown();


      TString MuID=GetString(k_id);
      if(apply_ID && !PassUserID(MuID,*muit)) pass_selection =false;
      if(DebugPrint && apply_ID && !PassUserID(MuID,*muit)) cout << "Fails Selection::ID cut " << endl;


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

      if(apply_dxycut && !(fabs(muit->IP2D())< dxy_cut )) pass_selection = false;
      if(DebugPrint && apply_dxycut && !(fabs(muit->IP2D())< dxy_cut ))cout << "Fails Selection::dxy cut " << endl;

      if(apply_dxysigmin && !(fabs(muit->SIP3D()) >= dxySig_min )) pass_selection = false;
      if(DebugPrint && apply_dxysigmin && !(fabs(muit->SIP3D()) >= dxySig_min ))cout << "Fails Selection::dxySigMin cut " << endl;

      if(apply_dxysigmax && !(fabs(muit->IP2D()) < dxySig_max )) pass_selection = false;
      if(DebugPrint && apply_dxysigmax && !(fabs(muit->SIP3D()) < dxySig_max ))cout << "Fails Selection::dxySigMin cut " << endl;

      
      if(apply_chi2cut && !( muit->GlobalChi2() < chiNdof_cut && muit->GlobalChi2() >= chiNdofMIN_cut )) pass_selection = false;
      if(DebugPrint && apply_chi2cut && !( muit->GlobalChi2() <chiNdof_cut && muit->GlobalChi2()  >=chiNdofMIN_cut)) cout << "Fails chi2 cut " << endl;

      
      //// ADD EXTRA  cut on D0sig? or same vertex?     
      if(pass_selection) leptonColl.push_back(*muit);    

  }/// muon loop end

  BaseSelection::reset();
  return;
}  



void MuonSelection::SelectMuons(std::vector<KMuon>& leptonColl, TString muid,float ptcut, float etacut){

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();


  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    bool pass_selection(true);
    
    if(( muit->Pt() < ptcut )) pass_selection = false;
    if(!(fabs(muit->Eta()) < etacut)) pass_selection = false;

    if(PassUserID(muid,*muit) && pass_selection) leptonColl.push_back(*muit);
  }
  return;
  
}

void  MuonSelection::UserIDConfig(TString id){
  
  if (id == "MUON_POG_LOOSE"){
    apply_id_loose=true;   // No additioonal cuts excpect POG ID cut based
  }
  if (id == "MUON_POG_MEDIUM"){
    apply_id_medium=true;   // No additioonal cuts excpect POG ID cut based                                                                                                                                
  }
  if (id == "MUON_POG_TIGHT"){
    apply_id_tight=true;   // No additioonal cuts excpect POG ID cut based                                                                                                                                
  }
  if (id == "MUON_HN_TIGHT"){
    apply_id_tight=true;
    SetEta(2.5);
  }
  
  /*
    SetRelIso(double);
    SetRelIsoBEMin(double);
    SetRelIsoBEMax(double);
    SetdxyBEMax(double);
    SetdzBEMax(double);
    
    SetRelIsoE(double);
  SetMiniRelIsoB(double);
  SetMiniRelIsoE(double);
  SetEta(double);
  SetPt(double);
  Set(double);
  SetPt(double);
  SetJetEta(double);
  SetJetPt(double);
  SetChiNdof(double);

  SetCheckCharge(bool);
  SetUseJetPileUp(bool );
  SetApplyConvVeto(bool);

  /// FIX 
  SetHLTSafeCut();
  */

}

bool MuonSelection::PassUserID(TString id, snu::KMuon mu,  bool m_debug){
  
  BaseSelection::reset();
  UserIDConfig(id);
  return PassID(mu,m_debug);
  
  
}




bool MuonSelection::PassID(snu::KMuon mu, bool m_debug){

  /// Taken from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonIdRun2
  bool passID(true);
  

  /// apply pog IDs
  if (apply_id_loose &&  !mu.IsLoose())       passID = false;
  if (apply_id_medium &&  !mu.IsMedium())       passID = false;
  if (apply_id_tight &&  !mu.IsTight())       passID = false;
  
  
  /*if (apply_ispf && (mu.IsPF() != 1  ) )  passID = false;
  if (apply_isglobal && (mu.IsGlobal() != 1)) {
    passID = false;
    if(m_debug)cout << "PassID: Fail isGlobal" << endl;
    }*/
  
  if(apply_BESepCut){
    if(fabs(mu.Eta()) < 1.5){
      
      /// Barrel
      // dxy
      if (apply_dxycut){
	if( fabs(mu.IP2D())    >= dxyBarrel_max) {
	  passID = false;
	  if(m_debug)cout << "PassID: Fail dXY" << endl;
	}
      }
      /// dz
      if (apply_dzcut){
	if( fabs(mu.dZ())    >= dzBarrel_max) {
	  passID = false;
	  if(m_debug)cout << "PassID: Fail dZ" << endl;
	}
      }
      
    }
    else{
    /// ENDCAP
    //dxy 
      if (apply_dxycut){
	if( fabs(mu.IP2D())    >= dxyEndcap_max) {
	  passID = false;
	  if(m_debug)cout << "PassID: Fail dXY" << endl;
	}
      }
      
      /// dz
      if (apply_dzcut){
	if( fabs(mu.IP2D())    >= dzEndcap_max) {
	  passID = false;
	  if(m_debug)cout << "PassID: Fail dZ" << endl;
	}
      }
    }
  }
  if(apply_chi2cut){
    if( mu.GlobalChi2() >=  chiNdof_cut){
      passID = false;
      if(m_debug) cout << "PassID: Fail  Chi2" << endl;
    }
    if( mu.GlobalChi2() <  chiNdofMIN_cut){
      passID = false;
      if(m_debug) cout << "PassID: Fail  Chi2" << endl;
    }
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

