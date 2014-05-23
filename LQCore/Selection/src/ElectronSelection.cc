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
    
    if ( m_debug&& ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 )) cout << "BasicSelection::Fail EtaCrack" << endl;
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( m_debug&& ( el->CaloEnergy()==0 )) cout <<"BasicSelection::Fail Zero CaloE" <<endl;
    if ( el->CaloEnergy()==0 ) continue;
    
    
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
    
    if ( m_debug&& ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 )) cout <<"SkimSelection::Fail EtaCrack" <<endl;
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( m_debug&& ( el->CaloEnergy()==0 )) cout <<"SkimSelection::Fail Zero CaloE" <<endl;
    if ( el->CaloEnergy()==0 ) continue;
    
    if ( fabs(el->SCEta()) < eta_cut && el->Pt() >= pt_cut_min){
      leptonColl.push_back(*el);
    }
    else if(m_debug) {
      if( fabs(el->SCEta()) >= eta_cut )  cout <<"SKimSelection::Fail Eta Cut" <<endl;
      if( el->Pt() < pt_cut_min )  cout <<"SkimSelection::Fail Pt Cut" <<endl;
    }
  }
 
}

void ElectronSelection::HNVetoElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  double rho = k_lqevent.GetEvent().JetRho();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( el->CaloEnergy()==0 ) continue;

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_VETO, *el, rho);
    ///List of cuts
    if(!ElectronID){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail ID Cut" <<endl;
    }
    if(!(fabs(el->Eta()) < 2.4)) {
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

void ElectronSelection::HNLooseElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  double rho = k_lqevent.GetEvent().JetRho();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( el->CaloEnergy()==0 ) continue;

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_FAKELOOSE, *el, rho);
    
    ///List of cuts
    if(!ElectronID) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail ID Cut" <<endl; 
    }
    
    if(!(fabs(el->Eta()) < 2.4)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Eta Cut" <<endl;
    }
    if((el->Pt() < 10.)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Pt Cut" <<endl;
    }
    
    
    if((el->HasMatchedConvPhot() ||  (el->MissingHits() != 0)) ) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Conv Cut" <<endl;
      }
    
    if(!el->GsfCtfScPixChargeConsistency()) {
      pass_selection = false;
      if(m_debug) cout << "HNLooseElectronSelection:Fail Charge Cons. Cut" <<endl;
    }

    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;
}


void ElectronSelection::HNTightElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  double rho = k_lqevent.GetEvent().JetRho();
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( el->CaloEnergy()==0 ) continue;
    
    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_TIGHT, *el,rho);
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;

    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
    if(el->Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();
    else LeptonRelIsoDR03 = -999.;
    
    ///List of cuts
    if(!ElectronID) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail ID Cut" <<endl;
    }
    if((el->HasMatchedConvPhot() ||  (el->MissingHits() != 0)) ) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Conv Cut" <<endl;
    }
    if(!(LeptonRelIsoDR03 <  0.09)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut" <<endl;
    }
    if(!el->GsfCtfScPixChargeConsistency())  {
      pass_selection = false;
      if(m_debug) cout << "HNTightElectronSelection:Fail Charge Cons. Cut" <<endl;
    }
    if(!(fabs(el->Eta()) < 2.4)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Eta Cut" <<endl;
    }
    if(!(el->Pt() > 15.))        {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Pt Cut" <<endl;
    }
    
    if(!(fabs(el->dxy())< 0.01 ))    {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail dxy Cut" <<endl;
    }
    
    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop
  
  return;
}



void ElectronSelection::TopVetoElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  double rho = k_lqevent.GetEvent().JetRho();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack

    if ( el->CaloEnergy()==0 ) continue;

    bool pass_selection = true;
    ElectronID = PassUserID(EGAMMA_VETO, *el, rho);

    ///List of cuts
    if(!ElectronID){
      pass_selection = false;
      if(m_debug) cout << "HNVetoElectronSelection::Fail ID Cut" <<endl;
    }
    if(!(fabs(el->Eta()) < 2.5)) {
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
  double rho = k_lqevent.GetEvent().JetRho();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack
    if ( el->CaloEnergy()==0 ) continue;

    bool pass_selection = true;
    //ElectronID = PassUserID(EGAMMA_LOOSE, *el, rho);

    ///List of cuts
    //if(!ElectronID) {
    //pass_selection = false;
    //if(m_debug)  cout << "HNLooseElectronSelection:Fail ID Cut" <<endl;
    //}

    if(!(fabs(el->Eta()) < 2.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Eta Cut" <<endl;
    }
    if((el->Pt() <= 20.)){
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Pt Cut" <<endl;
    }

    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;


    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
    if(el->Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();
    else LeptonRelIsoDR03 = -999.;


    if(!(LeptonRelIsoDR03 <  0.15)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut" <<endl;
    }

    if((el->HasMatchedConvPhot() ||  (el->MissingHits() != 0)) ) {
      pass_selection = false;
      if(m_debug)  cout << "HNLooseElectronSelection:Fail Conv Cut" <<endl;
    }

    if(!(el->dxy()< 0.04 )) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail dZ Cut" <<endl;
    }

    if(!(el->TrigMVA()< 0.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail MVA Cut" <<endl;
    }

    if(pass_selection){
      leptonColl.push_back(*el);
    }

  }// end of el loop

  return;
}


void ElectronSelection::TopTightElectronSelection(std::vector<KElectron>& leptonColl, bool m_debug) {
  std::vector<KElectron> allelectrons = k_lqevent.GetElectrons();
  double rho = k_lqevent.GetEvent().JetRho();

  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){

    //// DEFAULT cuts
    //// Require it is not in crack

    // exclude EB-EE transition region
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;

    if ( el->CaloEnergy()==0 ) continue;


    bool pass_selection = true;
    //ElectronID = PassUserID(EGAMMA_TIGHT, *el,rho);

    if(!(el->Pt() > 30.)) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Pt Cut" <<endl;
    }

    if(!(fabs(el->Eta()) < 2.5)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Eta Cut" <<endl;
    }

    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;


    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
    if(el->Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();

    ///List of cuts
    //              if(!ElectronID) {
    //      pass_selection = false;
    //      if(m_debug)  cout << "HNTightElectronSelection:Fail ID Cut" <<endl;
    //}

    if((el->HasMatchedConvPhot() ||  (el->MissingHits() != 0)) ) {
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Conv Cut" <<endl;
    }
    if(!(LeptonRelIsoDR03 <  0.1)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail Isolation Cut" <<endl;
    }
    if(!(el->TrigMVA()< 0.9)){
      pass_selection = false;
      if(m_debug)  cout << "HNTightElectronSelection:Fail MVA Cut" <<endl;
    }
    
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
  double rho = k_lqevent.GetEvent().JetRho(); 
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    //// DEFAULT cuts
    //// Require it is not in crack
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( el->CaloEnergy()==0 ) continue;
    
    bool pass_selection = true;
    
    ////  ID cut : need to optimise cuts
    /// Default is medium
    if(apply_ID){
      ElectronID = PassUserID(k_id, *el, rho);
      if(!ElectronID) {
	pass_selection = false;
	if(m_debug)cout << "Selection: Fail ID Cut" << endl;
      }
    }
    /// extra cut to reduce conversions
    /// https://twiki.cern.ch/twiki/bin/view/CMS/ConversionTools
    if(apply_convcut && (el->HasMatchedConvPhot() ||  (el->MissingHits() != 0)) ) {
      pass_selection = false; 
      if(m_debug)cout << "Selection: Fail Conversion Cut" << endl;
    }

    /// PF ISOLATION DR 03 is default https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification  with 0.12 cut
    
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};

    //// ISOLATION (AREA CORERECTION)    
    //https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaEARhoCorrection

    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;
    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid], 0.);
    if(el->Pt() > 0.){
      LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();
    }else
      {
	LeptonRelIsoDR03 = -999.;
      }

    if(apply_relisocut && !(LeptonRelIsoDR03 < relIso_cut && LeptonRelIsoDR03 >= relIsoMIN_cut)){
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Isolation Cut" << endl;
    }

    //// Check charge consistancy between different detectors
    if(apply_chargeconst && !el->GsfCtfScPixChargeConsistency()) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail charge Cut" << endl;
    }
    
    if(apply_etacut && !(fabs(el->Eta()) < eta_cut)) {
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


bool ElectronSelection::PassUserID(ID id, snu::KElectron el, double jetrho, bool m_debug){

  
  if ( id == EGAMMA_TIGHT   ) return PassUserID_EGamma2012     ( EGAMMA_TIGHT, el, jetrho,m_debug);
  else if ( id == EGAMMA_MEDIUM  ) return PassUserID_EGamma2012     (EGAMMA_MEDIUM,el, jetrho,m_debug);
  else if ( id == EGAMMA_LOOSE   ) return PassUserID_EGamma2012     (EGAMMA_LOOSE,el, jetrho,m_debug);
  else if ( id == EGAMMA_VETO    ) return PassUserID_EGamma2012     (EGAMMA_VETO,el, jetrho,m_debug);
  else if ( id == EGAMMA_TRIGTIGHT ) return PassUserID_EGamma2012     (EGAMMA_TRIGTIGHT,el, jetrho,m_debug);
  else if ( id == EGAMMA_TRIGWP70 ) return PassUserID_EGamma2012     (EGAMMA_TRIGWP70,el, jetrho,m_debug);
  else if ( id == EGAMMA_EOP      ) return PassUserID_EGamma2012     (EGAMMA_EOP,el, jetrho,m_debug);
  else if ( id == MVATrig            ) return PassUserID_MVA     (el, true);
  else if ( id == MVANonTrig            ) return PassUserID_MVA     (el, false);
  else if ( id == ECAL_FIDUCIAL  ) return PassUserID_ECALFiducial     (el);
  else if ( id == EGAMMA_FAKELOOSE ) return PassUserID_FakeLoose2012( el, jetrho,m_debug);
  else {
    cout << "Invalid ID set for electron selection" << endl;
    return false;
  }
  
}

bool ElectronSelection::PassUserID_ECALFiducial (snu::KElectron el){
  if ( el.IsEBFiducial() || el.IsEEFiducial() ) return true;
  else return false;
}

bool ElectronSelection::PassUserID_FakeLoose2012 (snu::KElectron el, double jetrho , bool m_debug){

  //----------------------------------------------------------------------
  // Barrel electron cut values
  //----------------------------------------------------------------------

  double l_b_dEtaIn  = 0.004;
  double l_b_dPhiIn  = 0.03;
  double l_b_sieie   = 0.01;
  double l_b_hoe     = 0.12;
  double l_b_ep      = 0.05;
  double l_b_vtxProb = 1e-6;
  int    l_b_missHits = 0;
  double l_b_d0      = 100.; 
  double l_b_dZ      = 0.1; 
  double l_b_pfRelIso = 0.6;
  //----------------------------------------------------------------------
  // Endcap electron cut values
  //----------------------------------------------------------------------

  double l_e_dEtaIn  = 0.005; 
  double l_e_dPhiIn  = 0.02;
  double l_e_sieie   = 0.03;
  double l_e_hoe     = 0.10;
  double l_e_d0      = 100.0;
  double l_e_dZ      = 0.1;
  double l_e_ep      = 0.05;
  double l_e_vtxProb = 1e-6;
  int    l_e_missHits = 0;
  double l_e_pfRelIso = 0.6;
  //----------------------------------------------------------------------
  // Bools that depend on barrel vs. endcap
  //----------------------------------------------------------------------

  bool   pass_deltaEta      = false;
  bool   pass_deltaPhi      = false;
  bool   pass_sigmaIEtaIEta = false;
  bool   pass_hoe           = false;
  bool   pass_vtxDistXY     = false;
  bool   pass_vtxDistZ      = false;
  bool   pass_ep            = false;
  bool   pass_convFitProb   = false;
  bool   pass_missingHits   = false;
  bool   pass_pfIsolation   = false;
  
  //----------------------------------------------------------------------
  // Define EGamma ep parameter
  //----------------------------------------------------------------------

  double egamma_e  = el.CaloEnergy();
  double egamma_p  = el.CaloEnergy() / el.ESuperClusterOverP();
  double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

  //----------------------------------------------------------------------
  // Define PF Isolation
  //----------------------------------------------------------------------

  double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
  double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
  double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
  double effective_area_03  = 0.0;

  for (int i = 0; i < 7; ++i ){
    double bin_minimum = effective_area_eta_minimums[i];
    double bin_maximum = effective_area_eta_maximums[i];
    if ( fabs(el.SCEta()) >= bin_minimum && fabs(el.SCEta()) < bin_maximum ) {
      effective_area_03 = effective_areas_03 [i];
    }
  }

  double egamma_pfiso_03 = el.PFChargedHadronIso03() + std::max ( el.PFPhotonIso03() + el.PFNeutralHadronIso03() - ( jetrho * effective_area_03 ), 0.0 );


  egamma_pfiso_03 /= el.Pt();

  //----------------------------------------------------------------------
  // Barrel electron test
  //----------------------------------------------------------------------

  if ( fabs(el.SCEta()) < 1.479 ){
    
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_b_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_b_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_b_sieie   );
    pass_hoe           = bool ( el.HoE            ()  <= l_b_hoe     );
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_b_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_b_dZ  );
    pass_ep            = bool ( egamma_ep          <= l_b_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_b_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_b_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_b_pfRelIso);
  }
  
  
  //----------------------------------------------------------------------
  // Endcap electron test
  //----------------------------------------------------------------------
  
  else if ( fabs(el.SCEta()) > 1.479 && fabs(el.SCEta()) < 2.5 ){
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_e_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_e_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_e_sieie   ); 
    pass_hoe           = bool ( el.HoE            ()  <= l_e_hoe     ); 
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_e_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_e_dZ  ); 
    pass_ep            = bool ( egamma_ep          <= l_e_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_e_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_e_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_e_pfRelIso);
  } 
  bool decision = (
		   pass_deltaEta      &&
		   pass_deltaPhi      &&
		   pass_sigmaIEtaIEta &&
		   pass_hoe           &&
		   pass_vtxDistXY     &&
		   pass_vtxDistZ      &&
		   pass_ep            &&
		   pass_pfIsolation   &&
		   pass_convFitProb   &&
		   pass_missingHits   ) ;
		   
  
  if(m_debug){
    if(!pass_deltaEta) cout << "Fake ID Fail deltaEta" << endl;
    if(!pass_deltaPhi) cout << "Fake ID Fail deltaPhi" << endl;
    if(!pass_sigmaIEtaIEta) cout << "Fake ID Fail sigmaIEtaIEta" << endl;
    if(!pass_hoe) cout << "Fake ID Fail hoe" << endl;
    if(!pass_vtxDistXY) cout << "Fake ID Fail dxy" << endl;
    if(!pass_vtxDistZ) cout << "Fake ID Fail dz" << endl;
    if(!pass_pfIsolation) cout << "Fake ID Fail isolation" << endl;
  }
  
  return decision;
}

bool ElectronSelection::PassUserID_EGamma2012 ( ID id, snu::KElectron el, double jetrho , bool m_debug){

  //----------------------------------------------------------------------
  // Barrel electron cut values
  //----------------------------------------------------------------------
  
  double l_b_dEtaIn  [4] = { 0.007 , 0.007, 0.004, 0.004 };
  double l_b_dPhiIn  [4] = { 0.8   , 0.15 , 0.06 , 0.03 };
  double l_b_sieie   [4] = { 0.01  , 0.01 , 0.01 , 0.01 };
  double l_b_hoe     [4] = { 0.15  , 0.12 , 0.12 , 0.12 };
  double l_b_d0      [4] = { 0.04  , 0.02 , 0.02 , 0.02 };
  double l_b_dZ      [4] = { 0.2   , 0.2  , 0.1  ,  0.1 };
  double l_b_ep      [4] = { 999.  , 0.05 , 0.05 , 0.05 };
  double l_b_pfRelIso[4] = { 0.15  , 0.15 , 0.15 , 0.10 };
  double l_b_vtxProb [4] = { 999.  , 1e-6 , 1e-6 , 1e-6 };
  int    l_b_missHits[4] = { 999   , 1    , 1    , 0 }; 

  //----------------------------------------------------------------------
  // Endcap electron cut values
  //----------------------------------------------------------------------
  
  double l_e_dEtaIn  [4] = { 0.01  , 0.009, 0.007, 0.005 };
  double l_e_dPhiIn  [4] = { 0.7   , 0.10 , 0.03 , 0.02 };
  double l_e_sieie   [4] = { 0.03  , 0.03 , 0.03 , 0.03 };
  double l_e_hoe     [4] = { 999.  , 0.10 , 0.10 , 0.10 };
  double l_e_d0      [4] = { 0.04  , 0.02 , 0.02 , 0.02 };
  double l_e_dZ      [4] = { 0.2   , 0.2  , 0.1  , 0.1 };
  double l_e_ep      [4] = { 999.  , 0.05 , 0.05 , 0.05 };
  double l_e_pfRelIso[4] = { 0.15  , 0.15 , 0.15 , 0.10 };
  double l_e_vtxProb [4] = { 999.  , 1e-6 , 1e-6 , 1e-6 };
  int    l_e_missHits[4] = { 999   , 1    , 1    , 0 };
  
  //----------------------------------------------------------------------
  // Bools that depend on barrel vs. endcap
  //----------------------------------------------------------------------

  bool   pass_deltaEta      = false;
  bool   pass_deltaPhi      = false;
  bool   pass_sigmaIEtaIEta = false;
  bool   pass_hoe           = false;
  bool   pass_vtxDistXY     = false;
  bool   pass_vtxDistZ      = false;
  bool   pass_ep            = false;
  bool   pass_pfIsolation   = false;
  bool   pass_convFitProb   = false;
  bool   pass_missingHits   = false;

  //----------------------------------------------------------------------
  // Define EGamma ep parameter
  //----------------------------------------------------------------------

  double egamma_e  = el.CaloEnergy();
  double egamma_p  = el.CaloEnergy() / el.ESuperClusterOverP();
  double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

  //----------------------------------------------------------------------
  // Define PF Isolation
  //----------------------------------------------------------------------

  double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
  double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
  double effective_areas_04             [7] = { 0.190, 0.250, 0.120, 0.210, 0.270, 0.440, 0.520 };
  double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
  double effective_area_03  = 0.0;
  double effective_area_04  = 0.0;
  
  for (int i = 0; i < 7; ++i ){ 
    double bin_minimum = effective_area_eta_minimums[i];
    double bin_maximum = effective_area_eta_maximums[i];
    if ( fabs(el.SCEta()) >= bin_minimum && fabs(el.SCEta()) < bin_maximum ) {
      effective_area_03 = effective_areas_03 [i];
      effective_area_04 = effective_areas_04 [i];
    }
  }
  
  double egamma_pfiso_03 = el.PFChargedHadronIso03() + std::max ( el.PFPhotonIso03() + el.PFNeutralHadronIso03() - ( jetrho * effective_area_03 ), 0.0 );
  double egamma_pfiso_04 = el.PFChargedHadronIso04() + std::max ( el.PFPhotonIso04() + el.PFNeutralHadronIso04() - ( jetrho * effective_area_04 ), 0.0 );
  

  egamma_pfiso_03 /= el.Pt();
  egamma_pfiso_04 /= el.Pt();
  
  //----------------------------------------------------------------------
  // Barrel electron test
  //----------------------------------------------------------------------
  
  int idx = 0;
  if ( fabs(el.SCEta()) < 1.479 ){
    idx=0;
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_b_dEtaIn  [ id ] ) ;
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_b_dPhiIn  [ id ] ) ;
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_b_sieie   [ id ] ) ;
    pass_hoe           = bool ( el.HoE            ()  <= l_b_hoe     [ id ] ) ;
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_b_d0      [ id ] ) ;
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_b_dZ      [ id ] ) ;
    pass_ep            = bool ( egamma_ep          <= l_b_ep      [ id ] ) ;
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_b_pfRelIso[ id ] ) ;
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_b_vtxProb [ id ] ) ;
    pass_missingHits   = bool ( el.MissingHits()    <= l_b_missHits[ id ] ) ;
    
  } 

  //----------------------------------------------------------------------
  // Endcap electron test
  //----------------------------------------------------------------------

  else if ( fabs(el.SCEta()) > 1.479 && fabs(el.SCEta()) < 2.5 ){ 
    
    idx=1;
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_e_dEtaIn  [ id ] ) ;
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_e_dPhiIn  [ id ] ) ;
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_e_sieie   [ id ] ) ;
    pass_hoe           = bool ( el.HoE          ()    <= l_e_hoe     [ id ] ) ;
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_e_d0      [ id ] ) ;
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_e_dZ      [ id ] ) ;
    pass_ep            = bool ( egamma_ep          <= l_e_ep      [ id ] ) ;
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_e_pfRelIso[ id ] ) ;
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_e_vtxProb [ id ] ) ;
    pass_missingHits   = bool ( el.MissingHits()    <= l_e_missHits[ id ] ) ;
  }

  bool decision = ( 
		      pass_deltaEta      && 
		         pass_deltaPhi      && 
		         pass_sigmaIEtaIEta && 
		         pass_hoe           && 
		         pass_vtxDistXY     && 
		         pass_vtxDistZ      && 
		         pass_ep            && 
		         pass_pfIsolation   && 
		         pass_convFitProb   && 
		      pass_missingHits   ) ;
  

  
  if( id == EGAMMA_TRIGTIGHT ){
    float cut_dEtaIn[2]         = {0.007, 0.009};
    float cut_dPhiIn[2]         = {0.15, 0.10};
    float cut_sigmaIEtaIEta[2]  = {0.01, 0.03};
    float cut_hoe[2]            = {0.12, 0.10};
    float cut_trackIso[2]       = {0.20, 0.20};
    float cut_ecalIso[2]        = {0.20, 0.20};
    float cut_hcalIso[2]        = {0.20, 0.20};
    if (fabs(el.DeltaEta()) > cut_dEtaIn[idx])             return false;
    if (fabs(el.DeltaPhi())> cut_dPhiIn[idx])             return false;
    if (el.SigmaIEtaIEta() > cut_sigmaIEtaIEta[idx])     return false;
    if (el.HoE          () > cut_hoe[idx])                         return false;

    if ( (el.TrkIsoDR03() /el.Pt() ) > cut_trackIso[idx])          return false;
    if ( (el.ECalIsoDR03() /el.Pt()) > cut_ecalIso[idx])            return false;
    if ( (el.HCalIsoDR03() /el.Pt()) > cut_hcalIso[idx])            return false;
  }
  
  if ( id == EGAMMA_TRIGWP70){
    float cut_dEtaIn[2]         = {0.004, 0.005};
    float cut_dPhiIn[2]         = {0.03, 0.02};
    float cut_sigmaIEtaIEta[2]  = {0.01, 0.03};
    float cut_hoe[2]            = {0.025, 0.025};
    float cut_trackIso[2]       = {0.10, 0.10};
    float cut_ecalIso[2]        = {0.10, 0.05};
    float cut_hcalIso[2]        = {0.05, 0.05};
    if (fabs(el.DeltaEta()) > cut_dEtaIn[idx])             return false;
    if (fabs(el.DeltaPhi())> cut_dPhiIn[idx])             return false;
    if (el.SigmaIEtaIEta() > cut_sigmaIEtaIEta[idx])     return false;
    if (el.HoE          () > cut_hoe[idx])                         return false;
    
    if ( (el.TrkIsoDR03() /el.Pt() ) > cut_trackIso[idx])          return false;
    if ( (el.ECalIsoDR03() /el.Pt()) > cut_ecalIso[idx])            return false;
    if ( (el.HCalIsoDR03() /el.Pt()) > cut_hcalIso[idx])            return false;

  }
  
  if( id == EGAMMA_EOP){
    if (el.FBrem() > 0.15)                           return true;
    else if (fabs(el.SCEta()) < 1.0 && el.ESuperClusterOverP() > 0.95)   return true;
    return false;
  }
  

  if(m_debug){
    if(!pass_deltaEta) cout << "ID " << id <<" Fail deltaEta" << endl;
    if(!pass_deltaPhi) cout << "ID " << id <<" Fail deltaPhi" << endl;
    if(!pass_sigmaIEtaIEta) cout << "ID " << id <<" Fail sigmaIEtaIEta" << endl;
    if(!pass_hoe) cout << "ID " << id <<" Fail hoe" << endl;
    if(!pass_vtxDistXY) cout << "ID " << id <<" Fail dxy" << endl;
    if(!pass_vtxDistZ) cout << "ID " << id <<" Fail dz" << endl;
    if(!pass_ep) cout << "ID " << id <<" Fail ep" << endl;
    if(!pass_convFitProb) cout << "ID " << id <<" Fail convFitProb" << endl;
    if(!pass_pfIsolation) cout << "ID " << id <<" Fail isolation" << endl;
    if(!pass_missingHits) cout << "ID " << id <<" Fail missinghit" << endl;
  }


  
  return decision;
  
}

bool ElectronSelection::PassUserID_MVA (snu::KElectron el, bool triggermva){
  
  int id =0 ; //el.PassID();
  
  int cut (0);
  if(triggermva) cut = 32;
  else cut =64;
  
  return (id >=  cut);
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

