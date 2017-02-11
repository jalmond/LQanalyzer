#include "ElectronSelection.h"


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


    if ( fabs(el->SCEta()) < eta_cut && el->Pt() >= pt_cut_min){
      leptonColl.push_back(*el);
    }
    else if(m_debug) {
      if( fabs(el->SCEta()) >= eta_cut )  cout <<"SKimSelection::Fail Eta Cut" <<endl;
      if( el->Pt() < pt_cut_min )  cout <<"SkimSelection::Fail Pt Cut" <<endl;
    }
  }
 
}



bool ElectronSelection::ElectronPass(snu::KElectron el, TString elid, float ptcut, float etacut){

  bool pass_selection = true;

  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",elid);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",elid);
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;;

  ElectronID = PassUserID(elid, el);
  if(!ElectronID)  pass_selection = false;

  if(!(fabs(el.SCEta()) < etacut)) pass_selection = false;
  if((el.Pt() < ptcut))   pass_selection = false;

  return pass_selection;
}

void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, ID elid, float ptcut, float etacut){
  return SelectElectrons(leptonColl,GetString(elid), ptcut,etacut);
}
  
void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, TString elid, float ptcut, float etacut){
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if(ElectronPass(*el, elid, ptcut,etacut)) leptonColl.push_back(*el);


  }// end of el loop

  return;
}

void ElectronSelection::Selection(std::vector<KElectron>& leptonColl , bool m_debug) {

  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    /// DEFAULT cuts
    bool pass_selection = true;

    /// ID cut : need to optimise cuts
    if(apply_ID){
      if(GetString(k_id).Contains("POG")) ElectronID = PassID(*el, k_id);
      else ElectronID = PassUserID(k_id, *el);

      if(!ElectronID) {
        pass_selection = false;
        if(m_debug)cout << "Selection: Fail ID Cut" << endl;
      }
    }

    //SetRelIso. Default: PFRelIso03
    float reliso(0.);
    if     (apply_relisocut && RelIsoType.Contains("Default"))    reliso=el->PFRelIso(0.3); 
    else if(apply_relisocut && RelIsoType.Contains("PFRelIso04")) reliso=el->PFRelIso(0.4); 

    if(apply_ptcut && !(el->Pt() >= pt_cut_min && el->Pt() < pt_cut_max)){
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Pt Cut" << endl;
    }
    if(apply_etacut && !(fabs(el->SCEta()) < eta_cut)) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Eta Cut" << endl;
    }

    //Whether to include EE-EBtransition region(Default: not)
    if(!apply_BETrRegIncl){
      if(fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566) pass_selection = false;
    }
    //// Check charge consistancy between different detectors
    if(apply_chargeconst && !el->GsfCtfScPixChargeConsistency()){
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail charge Cut" << endl;
    }
    /// extra cut to reduce conversions
    /// https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
    if(apply_convcut && (!el->PassesConvVeto()) ) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Conversion Cut" << endl;
    }



    if(apply_BESepCut){
      if(fabs(el->SCEta())<1.479){
        if(apply_relisocut && !(reliso < relIsoBarrel_max && reliso >= relIsoBarrel_min)) pass_selection=false;
        if(apply_dxycut    && !(fabs(el->dxy()) < dxyBarrel_max)) pass_selection=false;
        if(apply_dzcut     && !(fabs(el->dz()) < dzBarrel_max))   pass_selection=false;
      }
      else{
        if(apply_relisocut && !(reliso < relIsoEndcap_max && reliso >= relIsoEndcap_min)) pass_selection=false;
        if(apply_dxycut    && !(fabs(el->dxy()) < dxyEndcap_max)) pass_selection=false;
        if(apply_dzcut     && !(fabs(el->dz()) < dzEndcap_max))   pass_selection=false;
      }
    }
    else{
      if(apply_relisocut   && !(reliso < relIso_cut && reliso >= relIsoMIN_cut)){
        pass_selection = false;
        if(m_debug)cout << "Selection: Fail Isolation Cut" << endl;
      }
      if(apply_dzcut       && !(fabs(el->dz())<  dz_cut )) {
        pass_selection = false;
        if(m_debug)cout << "Selection: Fail dZ Cut" << endl;
      }
      if(apply_dxycut      && !( fabs(el->dxy())< dxy_cut )) {
        pass_selection = false;
        if(m_debug)cout << "Selection: Fail dxy Cut" << endl;
      }
    }


    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  BaseSelection::reset();

  return;
}



bool ElectronSelection::PassUserID(TString id, snu::KElectron el){


  float isomax_b = AccessFloatMap("isomax03_b",id);
  float isomax_e = AccessFloatMap("isomax03_e",id);
  float dxymax_b = AccessFloatMap("|dxymax_b|",id);
  float dxymax_e = AccessFloatMap("|dxymax_e|",id);
  float dzmax_b = AccessFloatMap("|dzmax_b|",id);
  float dzmax_e = AccessFloatMap("|dzmax_e|",id);

  bool checkisloose= (CheckCutString("IsLoose(POG)",id));
  bool checkisveto = (CheckCutString("IsVeto(POG)",id));
  bool checkismedium = (CheckCutString("IsMedium(POG)",id));
  bool checkistight  = (CheckCutString("IsTight(POG)",id));

  bool checkchargeconsy = (CheckCutString("GsfCtfScPix",id));
  bool convveto = (CheckCutString("convveto",id));
  

  LeptonRelIso = el.PFRelIso(0.3);
  bool pass_selection=true;

  int snuid = el.SNUID();
  bool pass_veto_noiso = false;
  bool pass_loose_noiso = false;
  bool pass_medium_noiso = false;
  bool pass_tight_noiso = false;
  if(snuid >= 1000){
    pass_tight_noiso = true;
    snuid = snuid - 1000;
  }
  if(snuid >= 100){
    pass_medium_noiso= true;
    snuid = snuid-100;
  }
  if(snuid >= 10){
    pass_loose_noiso=true;
    snuid = snuid-10;
  }    
  if(snuid >= 1){
    pass_veto_noiso=true;
  }


  bool debug=false;
  //  if(id.Contains("VETO")) debug=true;
  if(checkisveto && !pass_veto_noiso)  {pass_selection = false;if(debug){ cout << "Failveto " << endl;}}
  if(checkisloose && !pass_loose_noiso)  {pass_selection = false;if(debug){ cout << "Failloose " << endl;}}
  if(checkismedium && !pass_medium_noiso)  {pass_selection = false;if(debug){ cout << "Fail medium" << endl;}}
  if(checkistight && !pass_tight_noiso)  {pass_selection = false;if(debug){ cout << "Fail tight" << endl;}}
  
  if(convveto&& (!el.PassesConvVeto()) ){pass_selection = false;if(debug){ cout << "Fail convveto" << endl;}}
  if(checkchargeconsy &&  !el.GsfCtfScPixChargeConsistency()) {pass_selection = false;if(debug){ cout << "Fail charge" << endl;}}

  if(fabs(el.SCEta())<1.479 ){  

    if((LeptonRelIso > isomax_b))  {pass_selection = false;if(debug){ cout << "Fail iso: " << LeptonRelIso << " " << isomax_b << endl;}}
    if(fabs(el.dxy()) > dxymax_b) {pass_selection = false;if(debug){ cout << "Faildxy " << endl;}}
    if(fabs(el.dz()) > dzmax_b) {pass_selection = false;if(debug){ cout << "Fail dz" << endl;}}
  }
  else{
    if((LeptonRelIso > isomax_e))  {pass_selection = false;if(debug){ cout << "Fail iso" << LeptonRelIso << " " << isomax_b << endl;}}
    if(fabs(el.dxy()) > dxymax_e) {pass_selection = false;if(debug){ cout << "Fail dxy" << endl;}}
    if(fabs(el.dz()) > dzmax_e) {pass_selection = false;if(debug){ cout << "Fail dz" << endl;}}
  }
  
  return pass_selection;
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

bool ElectronSelection::PassID(snu::KElectron el, ID id){

  bool pass_selection=true;  bool debug=false;

  int  snuid = el.SNUID();
  bool pass_tight_noiso  = false;
  bool pass_medium_noiso = false;
  bool pass_loose_noiso  = false;
  bool pass_veto_noiso   = false;

  if     (snuid >= 1000) pass_tight_noiso  = true;
  else if(snuid >= 100 ) pass_medium_noiso = true;
  else if(snuid >= 10  ) pass_loose_noiso  = true;
  else if(snuid >= 1   ) pass_veto_noiso   = true;


  if(id == ELECTRON_POG_VETO   && !pass_veto_noiso)   {pass_selection = false; if(debug){ cout << "Failveto " << endl;}}
  if(id == ELECTRON_POG_LOOSE  && !pass_loose_noiso)  {pass_selection = false; if(debug){ cout << "Failloose " << endl;}}
  if(id == ELECTRON_POG_MEDIUM && !pass_medium_noiso) {pass_selection = false; if(debug){ cout << "Fail medium" << endl;}}
  if(id == ELECTRON_POG_TIGHT  && !pass_tight_noiso)  {pass_selection = false; if(debug){ cout << "Fail tight" << endl;}}

  return pass_selection;
}
