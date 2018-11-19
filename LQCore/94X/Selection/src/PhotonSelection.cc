#include "PhotonSelection.h"

using namespace snu;

PhotonSelection::PhotonSelection(LQEvent ev) : BaseSelection() {
  k_lqevent = ev;
  PhotonID= PHOTON_POG_LOOSE;
};

PhotonSelection::~PhotonSelection() {};


void PhotonSelection::BasicSelection(std::vector<KPhoton>& photonColl , bool m_debug) {
  
  /// For filling SKTrees
  std::vector<snu::KPhoton> allphotons = k_lqevent.GetPhotons();

  for (std::vector<snu::KPhoton>::iterator ph = allphotons.begin(); ph!=allphotons.end(); ph++){
   
    if ( fabs(ph->SCEta()) < eta_cut && ph->Pt() >= pt_cut_min ){
      photonColl.push_back(*ph);
    }
    else if(m_debug) {
      if( fabs(ph->SCEta()) >= eta_cut )  cout <<"BasicSelection::Fail Eta Cut" <<endl;
      if( ph->Pt() < pt_cut_min )  cout <<"BasicSelection::Fail Pt Cut" <<endl;
    }
  }
  
}

void PhotonSelection::SkimSelection(std::vector<KPhoton>& photonColl, bool m_debug) {
  
  std::vector<KPhoton> allphotons = k_lqevent.GetPhotons();
  
  for (std::vector<KPhoton>::iterator ph = allphotons.begin(); ph!=allphotons.end(); ph++){
    
    if ( fabs(ph->SCEta()) < eta_cut && ph->Pt() >= pt_cut_min){
      photonColl.push_back(*ph);
    }
    else if(m_debug) {
      if( fabs(ph->SCEta()) >= eta_cut )  cout <<"SKimSelection::Fail Eta Cut" <<endl;
      if( ph->Pt() < pt_cut_min )  cout <<"SkimSelection::Fail Pt Cut" <<endl;
    }
  }
 
}

void PhotonSelection::PogID(std::vector<KPhoton>& photonColl, TString ID){

  std::vector<KPhoton> allphotons = k_lqevent.GetPhotons();

  for (std::vector<KPhoton>::iterator ph = allphotons.begin(); ph!=allphotons.end(); ph++){
    
    if(ID.Contains("Loose"))PhotonID = PassUserID(PHOTON_POG_LOOSE, *ph);
    else     if(ID.Contains("Medium"))PhotonID = PassUserID(PHOTON_POG_MEDIUM, *ph);
    else     if(ID.Contains("Tight"))PhotonID = PassUserID(PHOTON_POG_TIGHT, *ph);
    else {cout << "Photon ID " << ID<< " not found" << endl; exit(EXIT_FAILURE);}
    bool pass_selection = true;
    
    if(!PhotonID) pass_selection = false;
    if(!(fabs(ph->SCEta()) < 2.5))  pass_selection = false;
    if((ph->Pt() < 15.))pass_selection = false;
  
    if(pass_selection){
      photonColl.push_back(*ph);
    }

  }// end of el loop

  return;
}


void PhotonSelection::Selection(std::vector<KPhoton>& photonColl , bool m_debug) {
  
  std::vector<KPhoton> allphotons = k_lqevent.GetPhotons();
  
  for (std::vector<KPhoton>::iterator ph = allphotons.begin(); ph!=allphotons.end(); ph++){
    
    bool pass_selection = true;
    
    ////  ID cut : need to optimise cuts
    /// Default is medium
    if(apply_ID){
      PhotonID = PassUserID(k_id, *ph);
      if(!PhotonID) {
	pass_selection = false;
	if(m_debug)cout << "Selection: Fail ID Cut" << endl;
      }
    }
    
    if(apply_etacut && !(fabs(ph->SCEta()) < eta_cut)) {
      pass_selection = false;
      if(m_debug)cout << "Selection: Fail Eta Cut" << endl;
    }

    if(apply_ptcut && ! (ph->Pt() >= pt_cut_min && ph->Pt() < pt_cut_max)) {
      pass_selection = false; 
      if(m_debug)cout << "Selection: Fail Pt Cut" << endl;
    }

    if(pass_selection){
      photonColl.push_back(*ph);
    }
    
  }// end of ph loop
  
  BaseSelection::reset();
  
  return;
}


  
bool PhotonSelection::PassUserID(ID id, snu::KPhoton ph){
  
  if ( id == PHOTON_POG_TIGHT   ) return     ph.isTight();
  else if ( id == PHOTON_POG_MEDIUM  ) return  ph.isMedium();
  else if ( id == PHOTON_POG_LOOSE   ) return  ph.isLoose();
  else {
    cout << "Invalid ID set for photon selection" << endl;
    return false;
  }
  return true;
}



PhotonSelection& PhotonSelection::operator= (const PhotonSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms); 
    k_lqevent = ms.k_lqevent;  
    PhotonID= ms.PhotonID;
  }
  return *this;
};

PhotonSelection::PhotonSelection(const PhotonSelection& ms): 
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;
  PhotonID= ms.PhotonID;
};

