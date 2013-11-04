#include "ElectronSelection.h"

using namespace snu;

ElectronSel::ElectronSel(LQEvent ev) {
  k_lqevent = ev;
};

ElectronSel::~ElectronSel() {};


void ElectronSel::ElectronSelection(std::vector<KElectron>& leptonColl) {
  
  std::vector<KElectron> allelectrons = k_lqevent.GetBaseElectrons();
  double rho = k_lqevent.GetBaseEvent().JetRho(); 
  
  for (std::vector<KElectron>::iterator el = allelectrons.begin(); el!=allelectrons.end(); el++){
    
    if ( fabs(el->Eta())>1.4442 && fabs(el->Eta())<1.566 ) continue;
    if ( el->caloEnergy()==0 ) continue;
    
    ElectronID = false;
    if (el->isEB()) {
      if (el->DeltaEtaTrkSC() < 0.004 &&
	  el->DeltaPhiTrkSC() < 0.06 &&
	  el->SigmaIEtaIEta() < 0.01 &&
	  el->HoE() < 0.12 &&
	  el->MissingHits() == 0 &&
	  fabs( (1 - el->SuperClusterOverP())/el->caloEnergy() ) < 0.05 &&
	  !el->HasMatchedConvPhot())
	ElectronID = true;
    }
    else if (el->isEE()) {
      if (el->DeltaEtaTrkSC() < 0.007 &&
	  el->DeltaPhiTrkSC() < 0.03 &&
	  el->SigmaIEtaIEta() < 0.03 &&
	  el->HoE() < 0.10 &&
	  el->MissingHits() == 0 &&
	  fabs( (1 - el->SuperClusterOverP())/el->caloEnergy() ) < 0.05 &&
	  !el->HasMatchedConvPhot())
	ElectronID = true;
    }
    else
      cout<< "something wrong with electron ID" <<endl;
    
    
    //// ISOLATION (AREA CORERECTION)
    if (fabs(el->Eta()) < 1.0) ifid = 0;
    else if (fabs(el->Eta()) < 1.479) ifid = 1;
    else if (fabs(el->Eta()) < 2.0) ifid = 2;
    else if (fabs(el->Eta()) < 2.2) ifid = 3;
    else if (fabs(el->Eta()) < 2.3) ifid = 4;
    else if (fabs(el->Eta()) < 2.4) ifid = 5;
    else ifid = 6;
    
    if (el->Pt() > 0.01)
      LeptonRelIso = ( el->HCalIso() + max( el->ECalIso() + el->TrkIso() - rho * PHONH[ifid], 0.) ) / el->Pt();
    else LeptonRelIso = 9999.;
    
    
    (el->ChargeConsistency()) ? individual = true : individual = false;
 
    (fabs(el->Eta()) < eta_cut && el->Pt() >= pt_cut_min && el->Pt() < pt_cut_max) ? etaPt=true : etaPt =false;
    
    (el->dz()<dz_cut && el->dxy() <dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0=true : RelIsod0=false;
    
    if (ElectronID && individual && etaPt && RelIsod0 ) {
      leptonColl.push_back(*el);
    }
    
  }// end of el loop
  
  return;
}



ElectronSel& ElectronSel::operator= (const ElectronSel& ms) {
  if(this != &ms){    
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

ElectronSel::ElectronSel(const ElectronSel& ms){
  k_lqevent = ms.k_lqevent;  
};

