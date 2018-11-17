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



bool ElectronSelection::ElectronPass(snu::KElectron el, TString elid, double ptcut, double etacut){

  //// This is not used now by GetElectron function in AnalyzerCore. Only used by DataDriven class which has no access to selection map

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


bool ElectronSelection::ElectronPass(snu::KElectron el, TString elid, TString el_id, bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b,double dzmax_e, double dxysigmax,double dxysigmin,double ptcut, double etacut){

  //// This is not used by any code but can be used by user IF they prefer
  /// This is Ferdinando style

  bool pass_selection = true;
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;;

  ElectronID = PassUserID(el ,elid, el_id, check_cc,check_cv, isomax_b,isomax03_e,dxymax_b,dxymax_e,dzmax_b,dzmax_e, dxysigmax,dxysigmin);
  if(!ElectronID)  pass_selection = false;

  if(!(fabs(el.SCEta()) < etacut)) pass_selection = false;
  if((el.Pt() < ptcut))   pass_selection = false;

  return pass_selection;
}


float ElectronSelection::IsoCutValue(snu::KElectron electron,TString elid){

  float isomax_b =AccessFloatMap("isomax03_b",elid);
  float isomax_ec = AccessFloatMap("isomax03_e",elid);
  if(fabs(electron.Eta()) < 1.5) return isomax_b;
  else return isomax_ec;
}



bool ElectronSelection::ElectronPass(snu::KElectron el, TString elid, vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf, double ptcut, double etacut){

  //// This is new function that inputs vector instead of searching in map
  ///  This saves time vs previous functions
  int icut(0);
  /// in case user has overwridden pt/eta cuts
  if (ptcut == -999. || etacut == -999.){
    for(unsigned int iv=0; iv < vidf.size(); iv++){
      if(!Check(vidf[iv].second)) continue;
      if (vidf[iv].first =="ptmin") { icut++; if(ptcut == -999.)ptcut=vidf[iv].second;}
      if (vidf[iv].first =="|etamax|") {icut++;  if (etacut == -999.)etacut=vidf[iv].second;}
      if(icut ==2) break;
    }
  }

  bool pass_selection = true;
  if ( fabs(el.SCEta())>1.4442 && fabs(el.SCEta())<1.566 ) return false;;

  ElectronID = PassUserID(elid, el ,vids, vidf);
  if(!ElectronID)  pass_selection = false;

  if(!(fabs(el.SCEta()) < etacut)) pass_selection = false;

  if((el.Pt() < ptcut))   pass_selection = false;
  
  return pass_selection;
}




void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, ID elid,TString el_id,bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b,double dzmax_e, double dxysigmax,double dxysigmin,double ptcut, double etacut){
  return SelectElectrons(leptonColl,GetString(elid),  el_id,check_cc,check_cv, isomax_b,isomax03_e,dxymax_b,dxymax_e,dzmax_b,dzmax_e, dxysigmax,dxysigmin, ptcut,etacut);
}
  
void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, TString elid, TString el_id,bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b,double dzmax_e, double dxysigmax,double dxysigmin,double ptcut, double etacut){
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if(ElectronPass(*el, elid, el_id,check_cc,check_cv, isomax_b,isomax03_e,dxymax_b,dxymax_e,dzmax_b,dzmax_e, dxysigmax,dxysigmin, ptcut,etacut) ) leptonColl.push_back(*el);


  }// end of el loop

  return;
}


void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, TString elid,vector<pair<TString, TString> > vids, vector<pair<TString, float> > vidf, double ptcut, double etacut){
  
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if(ElectronPass(*el, elid, vids,vidf, ptcut, etacut)) leptonColl.push_back(*el);

  }// end of el loop                                                                                                                                                                                                                                     

  return;
}


void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, TString elid,double ptcut, double etacut){

  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    if(elid=="MVA_W_ISO"){
      if(!el->PassMVAIso("mvaEleID-Fall17-iso-V2-wp80")) continue;
      if(!el->Pt() > ptcut) continue;
      if(!fabs(el->Eta()) > etacut) continue;
      
    
     leptonColl.push_back(*el);
    }

  }// end of el loop                                                                                                                                                                                                                                                            

  return;
}



void ElectronSelection::Selection(std::vector<KElectron>& leptonColl, TString Option){

  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();

  int  SystDir=0;
  bool Syst_ElEn=false, DebugPrint=false;
  if(Option.Contains("Debug")) DebugPrint=true;
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir   = 1;
    else if(Option.Contains("Down")) SystDir   =-1;
    if     (Option.Contains("ElEn")) Syst_ElEn = true;
  }

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    bool pass_selection = true;

    if     (Syst_ElEn && SystDir>0) *el *= el->PtScaleUp();
    else if(Syst_ElEn && SystDir<0) *el *= el->PtScaleDown();

    // ID cut
    if(apply_ID){
      if     (GetString(k_id).Contains("POG"))             ElectronID = PassID(*el, k_id);
      else if(GetString(k_id).Contains("HctoWA"))          ElectronID = PassID(*el, k_id);
      else if(GetString(k_id).Contains("ELECTRON_HN_MVA")) ElectronID = PassID(*el, k_id);
      else ElectronID = PassUserID( *el,GetString(k_id) , GetString(k_id), apply_chargeconst, apply_convcut,relIsoBarrel_max,relIsoEndcap_max,dxyBarrel_max,dxyEndcap_max,dzBarrel_max,dzEndcap_max, 999.,999.);

      if(!ElectronID) {
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail ID Cut" << endl;
      }
    }

    // HLT Emulation Cuts 
    //

    // SetRelIso. Default: PFRelIso03
    float reliso(0.);
    if     (apply_relisocut && RelIsoType.Contains("Default"))    reliso=el->PFRelIso(0.3); 
    else if(apply_relisocut && RelIsoType.Contains("PFRelIso04")) reliso=el->PFRelIso(0.4); 
    else                                                          reliso=el->PFRelIso(0.3); 

    if(apply_ptcut && !(el->Pt() >= pt_cut_min && el->Pt() < pt_cut_max)){
      pass_selection = false;
      if(DebugPrint) cout << "Selection: Fail Pt Cut" << endl;
    }
    if(apply_etacut && !(fabs(el->SCEta()) < eta_cut)) {
      pass_selection = false;
      if(DebugPrint) cout << "Selection: Fail Eta Cut" << endl;
    }

    //Whether to include EE-EBtransition region(Default: not)
    if(!apply_BETrRegIncl){
      if(fabs(el->SCEta())>1.4442 && fabs(el->SCEta())<1.566) pass_selection = false;
    }
    // Check charge consistancy between different detectors
    if(apply_chargeconst && !el->GsfCtfScPixChargeConsistency()){
      pass_selection = false;
      if(DebugPrint) cout << "Selection: Fail charge Cut" << endl;
    }
    // extra cut to reduce conversions
    // https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
    if(apply_convcut && (!el->PassesConvVeto()) ) {
      pass_selection = false;
      if(DebugPrint) cout << "Selection: Fail Conversion Cut" << endl;
    }

    //d0 Significance
    if(apply_dxysigmin && !(fabs(el->IP2D()) >= dxySig_min)) pass_selection = false;
    if(apply_dxysigmax && !(fabs(el->IP2D()) <  dxySig_max)) pass_selection = false;


    if(apply_BESepCut){
      if(fabs(el->SCEta())<1.479){
        if(apply_relisocut && !(reliso < relIsoBarrel_max && reliso >= relIsoBarrel_min)) pass_selection=false;
        if(apply_dxycut    && !(fabs(el->IP2D()) < dxyBarrel_max)) pass_selection=false;
        if(apply_dzcut     && !(fabs(el->dz()) < dzBarrel_max))   pass_selection=false;
      }
      else{
        if(apply_relisocut && !(reliso < relIsoEndcap_max && reliso >= relIsoEndcap_min)) pass_selection=false;
        if(apply_dxycut    && !(fabs(el->IP2D()) < dxyEndcap_max)) pass_selection=false;
        if(apply_dzcut     && !(fabs(el->dz()) < dzEndcap_max))   pass_selection=false;
      }
    }
    else{
      if(apply_relisocut   && !(reliso < relIso_cut && reliso >= relIsoMIN_cut)){
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail Isolation Cut" << endl;
      }
      if(apply_dzcut       && !(fabs(el->dz())<  dz_cut )) {
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail dZ Cut" << endl;
      }
      if(apply_dxycut      && !( fabs(el->IP2D())< dxy_cut )) {
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail dxy Cut" << endl;
      }
    }


    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  BaseSelection::reset();

  return;
}



bool ElectronSelection::PassUserID(TString id, snu::KElectron el, vector<pair<TString, TString> > vids , vector<pair<TString, float> > vidf ) {


  // NEED TO FILL
  return true;

}


bool ElectronSelection::PassUserID(TString id, snu::KElectron el){

  return true;
}

bool ElectronSelection::PassUserID(snu::KElectron el, TString id, TString el_id, bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b, double dzmax_e, double dxysigmax,double dxysigmin){


  return true;
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


  return pass_selection;

}
