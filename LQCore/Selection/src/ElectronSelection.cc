#include "ElectronSelection.h"

/// classes that contain analysis specific code
#include "ElectronSelectionHN.h"

using namespace snu;

ElectronSelection::ElectronSelection(LQEvent ev) :  BaseSelection() {
  k_lqevent = ev;
  ElectronID = ELECTRON_POG_TIGHT;

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



///// NEW FUNCTION TO CALL ALL IDS IN CLASS 

void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, ID elid, float ptcut, float etacut){
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    //// DEFAULT cuts
    //// Require it is not in crack

    if ( fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566 ) continue;
    
    bool pass_selection = true;
    ElectronID = PassUserID(elid, *el);
    if(!ElectronID)  pass_selection = false;

    if(!(fabs(el->SCEta()) < etacut)) pass_selection = false;
    if((el->Pt() < ptcut))   pass_selection = false;

    if(pass_selection)  leptonColl.push_back(*el);

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
      ElectronID = PassUserID(k_id, *el);
      if(!ElectronID) {
	pass_selection = false;
	if(m_debug)cout << "Selection: Fail ID Cut" << endl;
      }
    }

    /// extra cut to reduce conversions
    /// https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
    if(apply_convcut && (!el->HasMatchedConvPhot()) ) {
      pass_selection = false; 
      if(m_debug)cout << "Selection: Fail Conversion Cut" << endl;
    }
    float LeptonRelIsoDR03(0.);
    float LeptonRelIsoDR04(0.);
    LeptonRelIsoDR03 = el->PFRelIso(0.3);
    LeptonRelIsoDR04 = el->PFRelIso(0.4);

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


  
bool ElectronSelection::PassUserID(ID id, snu::KElectron el){
  return PassUserID(id, el,true, 0.5);
}

bool ElectronSelection::PassUserID(ID id, snu::KElectron el, bool usetight,float looseisocut){
  
  if ( id == ELECTRON_POG_TIGHT         )  return  el.PassTight();
  else if ( id == ELECTRON_POG_MEDIUM   )  return  el.PassMedium();
  else if ( id == ELECTRON_POG_LOOSE    )  {return el.PassLoose();}
  else if ( id == ELECTRON_POG_VETO     )  return  el.PassVeto();
  else if ( id == ELECTRON_HN_TIGHT     )  {return  HNTightElectronSelection(el); }
  else if ( id == ELECTRON_HN_VETO      )  return  HNVetoElectronSelection(el);
  else if ( id == ELECTRON_HN_FAKELOOSE )  return  HNLooseElectronSelection(el,  usetight, looseisocut);
  else if ( id == ELECTRON_TOP_TIGHT     ) return  TopTightElectronSelection(el);
  else if ( id == ELECTRON_TOP_VETO      ) return  TopVetoElectronSelection(el);
  else if ( id == ELECTRON_TOP_LOOSE     ) return  TopLooseElectronSelection(el);

  else {
    cout << "Invalid ID set for electron selection" << endl;
    return false;
  }
  
}


ElectronSelection& ElectronSelection::operator= (const ElectronSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms); 
    k_lqevent = ms.k_lqevent;  
    ElectronID = ms.ElectronID;

  }
  return *this;
};

ElectronSelection::ElectronSelection(const ElectronSelection& ms): 
  BaseSelection(ms){
  k_lqevent = ms.k_lqevent;
  ElectronID = ms.ElectronID;

};

