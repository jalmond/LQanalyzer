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

void MuonSelection::Selection( std::vector<KMuon>& leptonColl, bool applyrochester, bool m_debug) {
  

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  int ilep(0);
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++, ilep++){ 

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

      TString MuID=GetString(k_id);
      if(apply_ID && !PassID(MuID, *muit)) pass_selection =false;
      if(m_debug && apply_ID && !PassID(MuID, *muit)) cout << "Fails Selection::ID cut " << endl;


      if(apply_ptcut && ! ( muit->Pt() > pt_cut_min )) pass_selection = false;
      if(m_debug && apply_ptcut && ! (muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max)) cout << "Fails Selection::pt cut " << endl;
      
      if(apply_etacut && !(fabs(muit->Eta()) < eta_cut)) pass_selection =false;
      if(m_debug && apply_etacut && !(fabs(muit->Eta()) < eta_cut))  cout << "Fails Selection::eta cut " << endl;


      //// Calculate PF isolation
      /// https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation
      //LeptonRelIso = (muit->RelIso04());
      if     (apply_relisocut && RelIsoType.Contains("Default"))    LeptonRelIso=muit->RelIso04();
      else if(apply_relisocut && RelIsoType.Contains("PFRelIso03")) LeptonRelIso=muit->RelIso03();
      else   LeptonRelIso=muit->RelIso04();
      
      if(apply_relisocut && !( LeptonRelIso < relIso_cut)) pass_selection = false;
      if(m_debug && apply_relisocut && !( LeptonRelIso < relIso_cut))  cout << "Fails Selection::reliso cut " << endl;
      
  
      /// impact parameter cuts
      // Uses fabs(recoMu.muonBestTrack()->dxy(vertex->position())) as described in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Tight_Muon 
      // Also stores dB() on pat::Muon  as dxy_pat
      // Also stores D0 
      if(apply_dzcut && !(fabs(muit->dZ())<  dz_cut )) pass_selection = false;
      if(m_debug && apply_dzcut && !(fabs(muit->dZ())<  dz_cut ))  cout << "Fails Selection::dz cut " << endl;

      if(apply_dxycut && !(fabs(muit->dXY())< dxy_cut )) pass_selection = false;
      if(m_debug && apply_dxycut && !(fabs(muit->dXY())< dxy_cut ))cout << "Fails Selection::dxy cut " << endl;

      if(apply_dxysigmin && !(fabs(muit->dXYSig()) >= dxySig_min )) pass_selection = false;
      if(m_debug && apply_dxysigmin && !(fabs(muit->dXYSig()) >= dxySig_min ))cout << "Fails Selection::dxySigMin cut " << endl;

      if(apply_dxysigmax && !(fabs(muit->dXYSig()) < dxySig_max )) pass_selection = false;
      if(m_debug && apply_dxysigmax && !(fabs(muit->dXYSig()) < dxySig_max ))cout << "Fails Selection::dxySigMin cut " << endl;

      
      if(apply_chi2cut && !( muit->GlobalChi2() < chiNdof_cut && muit->GlobalChi2() >= chiNdofMIN_cut )) pass_selection = false;
      if(m_debug&&apply_chi2cut && !( muit->GlobalChi2() <chiNdof_cut && muit->GlobalChi2()  >=chiNdofMIN_cut)) cout << "Fails chi2 cut " << endl;

      
      //// ADD EXTRA  cut on D0sig? or same vertex?     
      if(pass_selection) leptonColl.push_back(*muit);    

  }/// muon loop end

  BaseSelection::reset();
  return;
}  



bool MuonSelection::MuonPass(snu::KMuon muon, TString muid, float ptcut, float etacut){

  /// Method used by DD class
  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",muid);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",muid);
  bool pass_selection(true);
  if(muon.Pt() == 0.)  return  false;

  MuonID = PassUserID(muid, muon);
  if(!MuonID)  pass_selection = false;

  if(( muon.Pt() < ptcut )) pass_selection = false;
  if(!(fabs(muon.Eta()) < etacut)) pass_selection = false;

  return pass_selection;
}


bool MuonSelection::MuonPass(snu::KMuon muon, TString muid, vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf,  float ptcut, float etacut){

  int icut(0);
  if (ptcut == -999. || etacut == -999.){
    for(unsigned int iv=0; iv < vidf.size(); iv++){
      if(!Check(vidf[iv].second)) continue;
      if (vidf[iv].first =="ptmin") { icut++; if(ptcut == -999.)ptcut=vidf[iv].second;}
      if (vidf[iv].first =="|etamax|") {icut++;  if (etacut == -999.)etacut=vidf[iv].second;}
      if(icut ==2) break;
    }
  }
  
  bool pass_selection(true);
  if(muon.Pt() == 0.)  return  false;

  MuonID = PassUserID(muid, muon, vids, vidf);
  if(!MuonID)  pass_selection = false;

  if(( muon.Pt() < ptcut )) pass_selection = false;
  if(!(fabs(muon.Eta()) < etacut)) pass_selection = false;

  return pass_selection;
}


void MuonSelection::SelectMuons(std::vector<KMuon>& leptonColl, ID muid, vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf,float ptcut, float etacut){
  
  return SelectMuons(leptonColl, GetString(muid), vids, vidf, ptcut, etacut);
}

void MuonSelection::SelectMuons(std::vector<KMuon>& leptonColl, TString muid,vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf, float ptcut, float etacut){

  std::vector<KMuon> allmuons = k_lqevent.GetMuons();
  
  
  bool applyrochester(true);
  
  for(unsigned int iv=0; iv < vids.size(); iv++){
    if(vids[iv].first == "ApplyRoch") {
      applyrochester=vids[iv].second;
      break;
    }
  }

  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    if(applyrochester&&! muit->IsRochesterCorrected()) {
      float origpt = muit->Pt();
      float origreliso03=muit->RelIso03();
      float origreliso04=muit->RelIso04();

      muit->SetPtEtaPhiM(muit->RochPt(), muit->Eta(), muit->Phi(), muit->M());
      
      muit->SetRelIso(0.3, origreliso03*origpt/muit->RochPt());
      muit->SetRelIso(0.4, origreliso04*origpt/muit->RochPt());
      muit->SetIsRochesterCorrected(true);
    }
    
    if(MuonPass(*muit, muid,vids, vidf,  ptcut, etacut)) leptonColl.push_back(*muit);
  }
  return;
}



bool MuonSelection::PassUserID(TString id, snu::KMuon mu, vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf){

  if(mu.Pt() == 0.) return false;
  
  float dxymax(0.);
  float dzmax(0.);
  float chi2max(0.);

  bool checkdxymax(false);
  bool checkdzmax (false);
  bool checkchi2max(false);
  bool checkisloose (false);
  bool checkismedium (false);
  bool checkistight (false);

  for(unsigned int iel =0; iel < vids.size(); iel++){
    if(vids[iel].second == "false") continue;
    if(vids[iel].first == "IsTight(POG)") checkistight=true;
    if(vids[iel].first == "IsMedium(POG)") checkismedium=true;
    if(vids[iel].first == "IsLoose(POG)") checkisloose=true;
  }
  bool debug=false;
  if(debug) cout << "PassUserID(TString id, snu::KMuon mu, vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf" << endl;
  LeptonRelIso = (mu.RelIso04());
  if(id.Contains("miniiso")) LeptonRelIso= mu.RelMiniIso();
  
  for(unsigned int idel =0; idel < vidf.size(); idel++){
    if(!Check( vidf[idel].second)) continue;
    if(vidf[idel].first == "isomax04") {
      if(LeptonRelIso > vidf[idel].second) {if(debug){ cout << "Fail iso"  << endl; } return false;}
    }
    if(vidf[idel].first == "|dxymax|") {
      checkdxymax=true;
      dxymax=vidf[idel].second;
    }
    if(vidf[idel].first == "|dxysigmax|") {
      if(fabs(mu.dXYSig()) > vidf[idel].second) {if(debug){ cout << "Fail dsigmax"  << endl;} return false;}
    }
    if(vidf[idel].first == "|dxysigmin|") {
      if(fabs(mu.dXYSig()) < vidf[idel].second) {if(debug){ cout << "Fail dsigmin"  << endl;} return false;}
    }
    if(vidf[idel].first == "chi2max") {
      checkchi2max=true;
      chi2max=vidf[idel].second;
    }
    if(vidf[idel].first == "|dzmax|") {
      checkdzmax=true;
      dzmax=vidf[idel].second;
    }
  }


  if(checkdxymax || checkchi2max || checkdzmax) {
    if(checkistight && ! PassID("MUON_POG_TIGHT",mu, !checkdxymax,!checkdzmax,!checkchi2max)) {if(debug){ cout << "Fail pogtight"  << endl;} return false;}
    if(checkdxymax && (fabs(mu.dXY()) > dxymax)){ if(debug){ cout << "Fail dxy "  << endl;} return false;}
    if(checkdzmax && (fabs(mu.dZ()) > dzmax)){ if(debug){ cout << "Fail dZ"  << endl;}return false;}
    if(checkchi2max && (fabs(mu.GlobalChi2()) > chi2max)){ if(debug){ cout << "Fail GlobalChi2"  << endl;} return false;}
  }
  else  if(checkistight &&  ! mu.IsTight ()) { if(debug){ cout << "Fail tight"  << endl;} return false;}

  if(checkisloose && ! mu.IsLoose ()) { if(debug){ cout << "Fail isloose" << endl;} return false;}

  if(checkismedium && ! mu.IsMedium ()) {if(debug){ cout << "Fail ismedium"  << endl;} return false;}
  
  
  return true;
}
bool MuonSelection::PassUserID(TString id, snu::KMuon mu){

  if(mu.Pt() == 0.) return false;

  float isomax = AccessFloatMap("isomax04",id);
  float dxymax = AccessFloatMap("|dxymax|",id);
  float dxysigmax = AccessFloatMap("|dxysigmax|",id);
  float dxysigmin = AccessFloatMap("|dxysigmin|",id);

  float dzmax = AccessFloatMap("|dzmax|",id);
  float chi2max = AccessFloatMap("chi2max",id);

  bool checkisomax     = CheckCutFloat("isomax04",id);
  bool checkdxymax      = CheckCutFloat("|dxymax|",id);
  bool checkdzmax       = CheckCutFloat("|dzmax|",id);
  bool checkdxysigmin  = CheckCutFloat("|dxysigmin|",id);
  bool checkdxysigmax  = CheckCutFloat("|dxysigmax|",id);
  bool checkchi2max     = CheckCutFloat("chi2max",id);
  bool checkisloose  = (CheckCutString("IsLoose(POG)",id));
  bool checkismedium = (CheckCutString("IsMedium(POG)",id));
  bool checkistight  = (CheckCutString("IsTight(POG)",id));
  

  bool debug=false;
  //if(id.Contains("VETO")) debug=true;
  LeptonRelIso = (mu.RelIso04());
  if(id.Contains("miniiso")) LeptonRelIso= mu.RelMiniIso();

  bool pass_selection=true;
  if(checkisloose && ! mu.IsLoose ()) { pass_selection = false;if(debug){ cout << "Fail isloose" << endl;}}
  
  if(checkismedium && ! mu.IsMedium ()) { pass_selection = false;if(debug){ cout << "Fail ismedium"  << endl;}}

  if(checkdxymax || checkchi2max || checkdzmax) {
    if(checkistight && ! PassID("MUON_POG_TIGHT",mu, !checkdxymax,!checkdzmax,!checkchi2max)) { pass_selection = false;if(debug){ cout << "Fail pogtight"  << endl;}}
    if(checkdxymax && (fabs(mu.dXY()) > dxymax)){ pass_selection = false;if(debug){ cout << "Fail dxy "  << endl;}}
    if(checkdzmax && (fabs(mu.dZ()) > dzmax)){ pass_selection = false;if(debug){ cout << "Fail dZ"  << endl;}}
    if(checkchi2max && (fabs(mu.GlobalChi2()) > chi2max)){ pass_selection = false;if(debug){ cout << "Fail GlobalChi2"  << endl;}}
  }
  else  if(checkistight &&  ! mu.IsTight ()) { pass_selection = false;if(debug){ cout << "Fail tight"  << endl;}}


  if(checkisomax && (LeptonRelIso > isomax)) { pass_selection = false;if(debug){ cout << "Fail iso"  << endl;}}

  if(checkdxysigmin &&(fabs(mu.dXYSig()) < dxysigmin)) { pass_selection = false;if(debug){ cout << "Fail dsximin"  << endl;}}
  if(checkdxysigmax &&(fabs(mu.dXYSig()) > dxysigmax)) { pass_selection = false;if(debug){ cout << "Fail dsigmax"  << endl;}}

  
  vector<pair<TString, TString> > vids =GetStringList(id);
  vector<pair<TString, float> > vidf = GetFloatList(id);
  bool check2 = PassUserID(id, mu, vids, vidf);

  if(check2 != pass_selection) cout << "IDS ARE NOT SAME" << endl;

  return pass_selection;
    
}


bool MuonSelection::HNTightMuonSelection(KMuon mu) {
  
  if(HNIsTight(mu))  return true;
  else return false;
}



////////// PREDEFINED MUON SELECTIONS FOR TOP ANALYSIS


bool MuonSelection::TopVetoMuonSelection(KMuon mu) {
  
  bool pass_selection(true);
  LeptonRelIso = (mu.RelIso03());
  
  if(!( LeptonRelIso < 0.2))     pass_selection = false;
  if(!PassID("MUON_POG_LOOSE", mu))      pass_selection =false;
  //// Make Loose selection
  
  return pass_selection;

}

// Intended use for di-lepton channel
bool MuonSelection::TopLooseMuonSelection(KMuon mu) {

  bool pass_selection(true);
  
  if(mu.Pt() == 0.) return false;
  LeptonRelIso = (mu.RelIso03());

  if(!PassID("MUON_POG_LOOSE", mu)) pass_selection =false;
  if(!( LeptonRelIso < 0.2)) pass_selection = false;

  
  return pass_selection;

}

bool MuonSelection::TopTightMuonSelection(KMuon mu) {

  bool pass_selection(true);
  
  if(mu.Pt() == 0.) return false;
  LeptonRelIso = (mu.RelIso03());
  
  if(!( LeptonRelIso < 0.1))    pass_selection = false;
  if(!(fabs(mu.dZ())< 0.10  ))  pass_selection = false;
  if(!(fabs(mu.dXY())< 0.005 ))   pass_selection = false;
  
  /// TIGHT MUON from muon POG
  if(!PassID("MUON_POG_TIGHT", mu)) pass_selection =false;
  if(mu.Pt() == 0.) return false;
  return pass_selection;

}


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

