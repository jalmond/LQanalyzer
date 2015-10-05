#include "ElectronSelection.h"

using namespace snu;

ElectronSelection::ElectronSelection(LQEvent ev) : BaseSelection() {
  k_lqevent = ev;
};

ElectronSelection::~ElectronSelection() {};


void ElectronSelection::BasicSelection(std::vector<KElectron>& leptonColl , bool m_debug) {
  
  /// For filling SKTrees
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if ( m_debug&& ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 )) cout << "BasicSelection::Fail EtaCrack" << endl;
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;
    
    
    if ( fabs(el->SCEta()) < eta_cut && el->Pt() >= pt_cut_min ){
      leptonColl.push_back(*el);
    }
    else if(m_debug) {
      if( fabs(el->SCEta()) >= eta_cut )  cout <<"BasicSelection::Fail Eta Cut" <<endl;
      if( el->Pt() < pt_cut_min )  cout <<"BasicSelection::Fail Pt Cut" <<endl;
    }
  }
  
}

void ElectronSelection::SkimSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if ( m_debug&& ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 )) cout <<"SkimSelection::Fail EtaCrack" <<endl;
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;
    
    if ( fabs(el->SCEta()) < eta_cut && el->Pt() >= pt_cut_min){
      leptonColl.push_back(*el);
    }
    else if(m_debug) {
      if( fabs(el->SCEta()) >= eta_cut )  cout <<"SKimSelection::Fail Eta Cut" <<endl;
      if( el->Pt() < pt_cut_min )  cout <<"SkimSelection::Fail Pt Cut" <<endl;
    }
  }
 
}

void ElectronSelection::PogID(std::vector<KElectron>& leptonColl, TString ID){

  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;
    
    if(ID.Contains("Veto"))ElectronID = PassUserID(EGAMMA_VETO, *el,false);
    else     if(ID.Contains("Loose"))ElectronID = PassUserID(EGAMMA_LOOSE, *el,false);
    else     if(ID.Contains("Medium"))ElectronID = PassUserID(EGAMMA_MEDIUM, *el,false);
    else     if(ID.Contains("Tight"))ElectronID = PassUserID(EGAMMA_TIGHT, *el,false);
    
    bool pass_selection = true;

    if(!ElectronID) pass_selection = false;
    if(!(fabs(el->SCEta()) < 2.5))  pass_selection = false;
    if((el->Pt() < 10.))pass_selection = false;
    
    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;
}


void ElectronSelection::HNVetoElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_VETO, *el,false);
    ///List of cuts
    if(!ElectronID){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail ID Cut" <<endl;
    }
    if(!(fabs(el->SCEta()) < 2.5)) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail Eta Cut" <<endl;
    }
    if((el->Pt() < 10.)){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail Pt Cut" <<endl;
    }
    
    if(pass_selection){
      leptonColl.push_back(*el);
    }
    
  }// end of el loop
  
  return;
}



void ElectronSelection::HNLooseElectronSelection( std::vector<KElectron>& leptonColl,  bool m_debug) {
  
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  int iel(0);
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++, iel++){
    if(m_debug)  cout << "Electron (HNLooseElectronSelection) # " << iel << endl;

    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_FAKELOOSE, true, *el, 0.5, m_debug);
    
    ///List of cuts
    if(!ElectronID) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail ID Cut" <<endl; 
    }
    
    if(!(fabs(el->SCEta()) < 2.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Eta Cut" <<endl;
    }
    if((el->Pt() < 10.)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Pt Cut" <<endl;
    }
    
    
    if((el->HasMatchedConvPhot())) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Conv Cut" <<endl;
    }
    
    if(!el->GsfCtfScPixChargeConsistency()) {
      pass_selection = false;
      if(m_debug) cout << "HNLooseElectronSelection:Fail Charge Cons. Cut" <<endl;
    }
    /*if(!(fabs(el->dxy())< 0.01 )) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail dxy Cut: " << el->dxy() <<endl;
      }*/
    
    if(pass_selection){
      leptonColl.push_back(*el);
    }


  }// end of el loop

  return;
}


bool ElectronSelection::HNIsTight(KElectron el, bool m_debug=true){

  // currently set to pog tight cuts

  float dxycut = -999.;
  float isocut= -999;
  if(fabs(el.SCEta())<1.566 ){
    dxycut = 0.0111;
    isocut = 0.0354;
  }
  else{
    dxycut = 0.0646;
    isocut = 0.0351;
  }
  /// from https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2
  
  //// DEFAULT cuts
  //// Require it is not in crack
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;
  
  bool pass_selection = true;
  
  float LeptonRelIsoDR03(0.);
  float LeptonRelIsoDR04(0.);
  ElectronID = PassUserID(EGAMMA_TIGHT, el, m_debug);
  
  
  LeptonRelIsoDR03 = el.PFRelIso03();
  LeptonRelIsoDR04 = el.PFRelIso04();
  

  ///List of cuts
  if(!ElectronID) {
    pass_selection = false;
    if(m_debug)  cout << "HNTightElectronSelection:Fail ID Cut" <<endl;
  }
  if((el.HasMatchedConvPhot() ) ) {
    pass_selection = false;
    if(m_debug)  cout << "HNTightElectronSelection:Fail Conv Cut" <<endl;
  }
  


  bool usedr3=true;
  if(usedr3){
    if(!(LeptonRelIsoDR03 <  isocut)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut: " << LeptonRelIsoDR03 <<endl;
    }
  }
  else{
    if(!(LeptonRelIsoDR04 <  isocut)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut: " << LeptonRelIsoDR03 <<endl;
    }
  }

  if(!el.GsfCtfScPixChargeConsistency()) {
    pass_selection = false;
    if(m_debug) cout << "HNTightElectronSelection:Fail Charge Cons. Cut" <<endl;
  }
  
  if(!(fabs(el.SCEta()) < 2.5)){
    pass_selection = false;
    if(m_debug)  cout << "HNTightElectronSelection:Fail Eta Cut" <<endl;
  }
  if(!(el.Pt() > 15.)) {
    pass_selection = false;
    if(m_debug)  cout << "HNTightElectronSelection:Fail Pt Cut" <<endl;
  }
  
  if(!(fabs(el.dxy())< dxycut )) {
    pass_selection = false;
    if(m_debug)  cout << "HNTightElectronSelection:Fail dxy Cut: " << el.dxy() <<endl;
  }

  return pass_selection;
  
}


void ElectronSelection::HNTightElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  int iel(0);
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++, iel++){
    if(m_debug)  cout << "Electron (HNTightElectronSelection) # " << iel << endl;
    if(HNIsTight(*el,  m_debug)){
      leptonColl.push_back(*el);
    }
    
  }// end of el loop
  
  return;
}




void ElectronSelection::TopVetoElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_VETO, *el,  true);

    ///List of cuts
    if(!ElectronID){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail ID Cut" <<endl;
    }
    if(!(fabs(el->SCEta()) < 2.5)) {
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail Eta Cut" <<endl;
    }
    if(!(el->Pt() > 20.)){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail Pt Cut" <<endl;
    }

    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;

}

void ElectronSelection::TopLooseElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {

  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack
    bool pass_selection = true;
    //ElectronID = PassUserID(EGAMMA_LOOSE, *el);

    ///List of cuts
    //if(!ElectronID) {
    //pass_selection = false;
    //if(m_debug)  cout << "HNLooseElectronSelection:Fail ID Cut" <<endl;
    //}

    if(!(fabs(el->SCEta()) < 2.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Eta Cut" <<endl;
    }
    if((el->Pt() <= 20.)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Pt Cut" <<endl;
    }
    float LeptonRelIsoDR03(0.);
    float LeptonRelIsoDR04(0.);
    LeptonRelIsoDR03 = el->PFRelIso03();
    LeptonRelIsoDR04 = el->PFRelIso04();

    if((el->HasMatchedConvPhot())){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Conv Cut" <<endl;
    }
    
    if(!(el->dxy()< 0.04 )) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail dZ Cut" <<endl;
    }

       //if(!(el->TrigMVA()< 0.5)){
       //pass_selection = false;
       //if(m_debug)  cout << "HNTightElectronSelection:Fail MVA Cut" <<endl;
       //}

    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;
}


void ElectronSelection::TopTightElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack

    // exclude EB-EE transition region
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;


    bool pass_selection = true;
    //ElectronID = PassUserID(EGAMMA_TIGHT, *el);

    if(!(el->Pt() > 30.)) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Pt Cut" <<endl;
    }

    if(!(fabs(el->SCEta()) < 2.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Eta Cut" <<endl;
    }
    float LeptonRelIsoDR03= el->PFRelIso03();

    ///List of cuts
    //              if(!ElectronID) {
    //      pass_selection = false;
    //      if(m_debug)  cout << "HNTightElectronSelection:Fail ID Cut" <<endl;
    //}

    if((el->HasMatchedConvPhot() )){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Conv Cut" <<endl;
    }
    if(!(LeptonRelIsoDR03 <  0.1)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut" <<endl;
    }
    //    if(!(el->TrigMVA()< 0.9)){
    //      pass_selection = false;
    //      if(m_debug)  cout << "HNTightElectronSelection:Fail MVA Cut" <<endl;
    //}
    
    if(!(el->dxy()< 0.02 )) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail dZ Cut" <<endl;
    }
    
    if(!(el->dz()<  0.10 )) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail dZ Cut" <<endl;
    }


    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;
}




void ElectronSelection::Selection(std::vector<KElectron>& leptonColl , bool m_debug) {
  
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;
    
    bool pass_selection = true;
    
    ////  ID cut : need to optimise cuts
    /// Default is medium
    if(apply_ID){
      ElectronID = PassUserID(k_id, *el,  false);
      if(!ElectronID) {
	pass_selection = false;
	if(m_debug)cout << "Selection: Fail ID Cut" << endl;
      }
    }

    /// extra cut to reduce conversions
    /// https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
    if(apply_convcut && (el->HasMatchedConvPhot()) ) {
      pass_selection = false; 
      if(m_debug)cout << "Selection: Fail Conversion Cut" << endl;
    }
    float LeptonRelIsoDR03(0.);
    float LeptonRelIsoDR04(0.);
    LeptonRelIsoDR03 = el->PFRelIso03();
    LeptonRelIsoDR04 = el->PFRelIso04();

    if(apply_relisocut && !(LeptonRelIsoDR03 < relIso_cut && LeptonRelIsoDR03 >= relIsoMIN_cut)){
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Isolation Cut" << endl;
    }

    //// Check charge consistancy between different detectors
    if(apply_chargeconst && !el->GsfCtfScPixChargeConsistency()) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail charge Cut" << endl;
    }
    
    if(apply_etacut && !(fabs(el->SCEta()) < eta_cut)) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Eta Cut" << endl;
    }

    if(apply_ptcut && ! (el->Pt() >= pt_cut_min && el->Pt() < pt_cut_max)) {
      pass_selection = false; 
      if(m_debug)cout << "Selection: Fail Pt Cut" << endl;
    }
    /// impact parameter cuts
    if(apply_dzcut && !(fabs(el->dz())<  dz_cut )) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail dZ Cut" << endl;
    }
    if(apply_dxycut && !( fabs(el->dxy())< dxy_cut )) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail dxy Cut" << endl;
    }
    
    if(pass_selection){
      leptonColl.push_back(*el);
    }
    
  }// end of el loop
  
  BaseSelection::reset();
  
  return;
}


  
bool ElectronSelection::PassUserID(ID id, snu::KElectron el, bool m_debug){
  return PassUserID(id, true, el, 0.6, m_debug);
}

bool ElectronSelection::PassUserID(ID id,bool usetight, snu::KElectron el, float looseisocut,  bool m_debug){

  
  if ( id == EGAMMA_TIGHT   ) return     el.PassTight();
  else if ( id == EGAMMA_MEDIUM  ) return  el.PassMedium();
  else if ( id == EGAMMA_LOOSE   ) return  el.PassLoose();
  else if ( id == EGAMMA_VETO    ) return  el.PassVeto();
  else if ( id == EGAMMA_FAKELOOSE ) return PassUserID_FakeLoose2015( el, usetight, looseisocut, m_debug);
  else {
    cout << "Invalid ID set for electron selection" << endl;
    return false;
  }
  
}


bool ElectronSelection::PassUserID_FakeLoose2015 (snu::KElectron el, bool usetight,  float looseisocut, bool m_debug){
  
  int id = el.SNUID();
  bool pass_veto_noiso = false;
  bool pass_loose_noiso = false;
  bool pass_medium_noiso = false;
  bool pass_tight_noiso = false;
  if(id >= 1000){
    pass_tight_noiso = true;
    id = id - 1000;
    if(id >= 100){
      pass_medium_noiso= true;
      id = id-100;

      if(id >= 10){
	pass_loose_noiso= true;
	id = id - 10;
	if(id >= 1)pass_veto_noiso= true; 
      }
    }
  }
  
  if(usetight){
    if(!pass_tight_noiso) return false;
  }
  else  if(!pass_medium_noiso) return false;
  if(!(fabs(el.SCEta()) < 2.5)) return false;
  
  if((el.Pt() < 10.)) return false;

  if( el.PFRelIso03() < looseisocut) return false;

  if(!(fabs(el.dxy())< 0.01 )) return false;

  return true;
}



ElectronSelection& ElectronSelection::operator= (const ElectronSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms); 
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

ElectronSelection::ElectronSelection(const ElectronSelection& ms): 
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;

};

