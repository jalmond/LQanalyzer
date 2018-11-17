#include "ElectronSelection.h"


using namespace snu;

ElectronSelection::ElectronSelection(LQEvent ev) :  BaseSelection() {
  k_lqevent = ev;
  ElectronID = ELECTRON_POG_TIGHT;

};

ElectronSelection::~ElectronSelection() {};

////////////////////////////////////////////////
////// FUNCTIONS FOR SKTREEMAKER
////////////////////////////////////////////////

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

////////////////////////////////////////////////                                                                                                                                                          
////// FUNCTIONS FOR ANALYSIS CODE
////////////////////////////////////////////////     


bool ElectronSelection::ElectronPass(snu::KElectron el, TString elid, double ptcut, double etacut){

  //// This is not used now by GetElectron function in AnalyzerCore. Only used by DataDriven class which has no access to selection map

  bool pass_selection = true;

  if (ptcut == -999.) ptcut = 10.;
  if (etacut == -999.) etacut = 2.5; 

  
  /// PassCustomID in KElectron
  if(!el.PassCustomID(elid)) pass_selection = false;

  // pt and eta cuts
  if (el.ElInCrackRegion()) pass_selection = false;
  if (el.AbsEta() > etacut) pass_selection = false;
  if (el.Pt() < ptcut)   pass_selection = false;

  return pass_selection;
}



float ElectronSelection::IsoCutValue(snu::KElectron electron,TString elid, TString isotype){

  // This function is useful for ptcone varaiable to make sure correct isolation cut is applied to ID and ptcone value
  return float(electron.GetIDIso(elid, isotype));
  
}

  
void ElectronSelection::SelectElectrons(std::vector<KElectron>& leptonColl, TString elid,  TString Option, double ptcut, double etacut){

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

    if     (Syst_ElEn && SystDir>0) *el *= el->PtShiftedUp();
    else if(Syst_ElEn && SystDir<0) *el *= el->PtShiftedDown();

    if(ElectronPass(*el, elid, ptcut,etacut) ) leptonColl.push_back(*el);
    
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

    if     (Syst_ElEn && SystDir>0) *el *= el->PtShiftedUp();
    else if(Syst_ElEn && SystDir<0) *el *= el->PtShiftedDown();

    // ID cut
    if(apply_ID){
      if     (GetString(k_id).Contains("POG"))             ElectronID = PassID(*el, k_id);
      else if(GetString(k_id).Contains("HctoWA"))          ElectronID = PassID(*el, k_id);
      else if(GetString(k_id).Contains("ELECTRON_HN_MVA")) ElectronID = PassID(*el, k_id);
      else ElectronID = PassUserID( *el,GetString(k_id) , GetString(k_id), apply_chargeconst, apply_convcut,relIsoBarrel_max,relIsoEndcap_max,dxyBarrel_max,dxyEndcap_max,dzBarrel_max,dzEndcap_max, 0., 0.,999.,999.);

      if(!ElectronID) {
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail ID Cut" << endl;
      }
    }

    // HLT Emulation Cuts 
    if(apply_HLTSafeCut){
      if     ( HLTSafeLevel.Contains("CaloIdL_TrackIdL_IsoVL") && (!el->IsTrigMVAValid()) ) pass_selection=false;
      else if( HLTSafeLevel.Contains("WPLoose")                && (!el->PassHLTID())      ) pass_selection=false;
    }

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
    if(apply_dxysigmin && !(fabs(el->dxySig2D()) >= dxySig_min)) pass_selection = false;
    if(apply_dxysigmax && !(fabs(el->dxySig2D()) <  dxySig_max)) pass_selection = false;

    if(apply_IP3Dmin && !(fabs(el->dxySig3D()) >= IP3D_min)) pass_selection = false;
    if(apply_IP3Dmax && !(fabs(el->dxySig3D()) <  IP3D_max)) pass_selection = false;



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
        if(DebugPrint) cout << "Selection: Fail Isolation Cut" << endl;
      }
      if(apply_dzcut       && !(fabs(el->dz())<  dz_cut )) {
        pass_selection = false;
        if(DebugPrint) cout << "Selection: Fail dZ Cut" << endl;
      }
      if(apply_dxycut      && !( fabs(el->dxy())< dxy_cut )) {
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


bool ElectronSelection::PassUserID(snu::KElectron el, TString id, TString el_id, bool check_cc,bool check_cv,double  isomax_b,double isomax03_e,double dxymax_b,double dxymax_e,double dzmax_b, double dzmax_e, double dxysigmax,double dxysigmin, double IP3Dmax, double IP3Dmin){

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
  


  bool pass_trigger_emulation=true;
  if(el.Pt() < 15.){
    /// special case that mva id not used as 15 GeV cut                                                                                                         
    /// use single electron HLT cuts which are tighter than mva for 10-15 GeV bin                                                                               
    if(!el.PassHLTID()) pass_trigger_emulation=false;
  }
  else {
    /// safe for DoubleEG triggers with CaloIdL_TrackIdL_IsoVL                                                                                                  
    //https://twiki.cern.ch/twiki/bin/view/CMS/ChangesEGMHLTAlgo2014                                                                                            
    if(!el.IsTrigMVAValid()) pass_trigger_emulation=false;
  }




  if((el_id =="IsTight(POG)") &&  !pass_tight_noiso)  {if(debug){ cout << "Fail tight" << endl;}return false;}
  if((el_id =="IsMedium(POG)") && !pass_medium_noiso)  {if(debug){ cout << "Fail medium" << endl;}return false;}
  if((el_id =="IsLoose(POG)") && !pass_loose_noiso)  {if(debug){ cout << "Failloose " << endl;}return false;}
  if((el_id =="IsVeto(POG)") && !pass_veto_noiso)  {if(debug){ cout << "Failveto " << endl;}return false;}
  if((el_id =="IsMedium(MVA)")){
    if(!pass_trigger_emulation)  {if(debug){cout << "Fail MVA medium" << endl;} return false;}
    if(!el.PassTrigMVAMedium()) {if(debug){cout << "Fail MVA medium" << endl;} return false;}
  }
  if(el_id == "IsTight(MVA)") {
    if(!pass_trigger_emulation)  {if(debug){cout << "Fail MVA tight" << endl;} return false;}
    if(!el.PassTrigMVATight()) {if(debug){cout << "Fail MVA tight" << endl;} return false;}
  }
  if(el_id == "IsHNTight(MVA)") {
    if(!pass_trigger_emulation)  {if(debug){cout << "Fail MVA tight" << endl;} return false;}
    if(!el.PassTrigMVAHNTightv4()) {if(debug){cout << "Fail MVA tight" << endl;} return false;}
  }
  if(el_id == "IsHNLoose(MVA)") {
    if(!pass_trigger_emulation)  {if(debug){cout << "Fail MVA tight" << endl;} return false;}
    if(!el.PassTrigMVAHNLoose()) {if(debug){cout << "Fail MVA tight" << endl;} return false;}
  }
  if(el_id == "IsGENTTight") {
    if(!pass_trigger_emulation)  {if(debug){cout << "Fail MVA tight" << endl;} return false;}
    if(!el.PassTrigMVAGENTTight()) {if(debug){cout << "Fail MVA tight" << endl;} return false;}
  }

  
  if( check_cc &&  !el.GsfCtfScPixChargeConsistency()) { if(debug){ cout << "Fail charge" << endl;} return false;}
  if( check_cv &&  (!el.PassesConvVeto()) ){ if(debug){ cout << "Fail convveto" << endl;}return false;}

  
  LeptonRelIso = el.PFRelIso(0.3);
  
  if(id.Contains("miniaod")){
    LeptonRelIso = el.PFRelMiniIso(false);
  }
  
  
  if(fabs(el.SCEta())<1.479 ){
    if(Check(isomax_b)){
      if((LeptonRelIso > isomax_b))  {if(debug){ cout << "Fail iso: " << LeptonRelIso << " " << isomax_b << endl;} return false;}
    }
    if(Check(dxymax_b)){
      if(fabs(el.dxy()) > dxymax_b) {if(debug){ cout << "Faildxy " << endl;}return false;}
    }
    if(Check(dzmax_b)){
      if(fabs(el.dz()) > dzmax_b) {if(debug){ cout << "Fail dz" << endl;}return false;}    
    }
  }
  else{
    if(Check(isomax03_e)){
      if((LeptonRelIso > isomax03_e))  {if(debug){ cout << "Fail iso" << LeptonRelIso << " " << isomax03_e << endl;} return false;}
    }
    if(Check(dxymax_e)){
      if(fabs(el.dxy()) > dxymax_e) {if(debug){ cout << "Fail dxy" << endl;}return false;}
    }
    if(Check(dzmax_e)){
      if(fabs(el.dz()) > dzmax_e) {if(debug){ cout << "Fail dz" << endl;}return false;}
    }
  }
  if(Check(dxysigmax)){
    if((fabs(el.dxySig2D()) > dxysigmax)) { if(debug){ cout << "Fail dsigmax"  << endl;}return false;}     
  }
  if(Check(dxysigmin)){
    if((fabs(el.dxySig2D()) < dxysigmin)) { if(debug){ cout << "Fail dsximin"  << endl;}return false;}
  }
  if(Check(IP3Dmax)){
    if((fabs(el.dxySig3D()) > IP3Dmax)) { if(debug){ cout << "Fail dsigmax"  << endl;}return false;}
  }
  if(Check(IP3Dmin)){
    if((fabs(el.dxySig3D()) < IP3Dmin)) { if(debug){ cout << "Fail dsximin"  << endl;}return false;}
  }

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

  //SNUID : CutbasedPOGID without Isolation requirements

  if     ( id == ELECTRON_POG_VETO   && el.SNUID()<1    ){pass_selection = false; if(debug){ cout << "Failveto "  << endl;}}
  else if( id == ELECTRON_POG_LOOSE  && el.SNUID()<10   ){pass_selection = false; if(debug){ cout << "Failloose " << endl;}}
  else if( id == ELECTRON_POG_MEDIUM && el.SNUID()<100  ){pass_selection = false; if(debug){ cout << "Fail medium"<< endl;}}
  else if( id == ELECTRON_POG_TIGHT  && el.SNUID()<1000 ){pass_selection = false; if(debug){ cout << "Fail tight" << endl;}}
  else if( id == ELECTRON_POG_MVA_WP90 && (!el.PassNotrigMVAMedium()) ){ pass_selection = false; }
  else if( id == ELECTRON_POG_MVA_WP80 && (!el.PassNotrigMVATight())  ){ pass_selection = false; }
  else if( id == ELECTRON_HN_MVA_LOOSE && (!el.PassTrigMVAHNLoose())  ){ pass_selection = false; }
  else if( id == ELECTRON_HN_MVA_TIGHT && (!el.PassTrigMVAHNTightv4())  ){ pass_selection = false; }
  else if( id == ELECTRON_HctoWA_FAKELOOSE ){
    if     ( fabs(el.Eta())<0.8   ){ if( el.MVA()<-0.92 ) pass_selection=false; }
    else if( fabs(el.Eta())<1.479 ){ if( el.MVA()<-0.85 ) pass_selection=false; }
    else if( fabs(el.Eta())<2.5   ){ if( el.MVA()<-0.76 ) pass_selection=false; }
  }

  return pass_selection;

}
