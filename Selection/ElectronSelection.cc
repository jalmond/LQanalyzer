#include "ElectronSelection.h"

using namespace snu;

ElectronSel::ElectronSel() {};

ElectronSel::~ElectronSel() {};


void ElectronSel::ElectronSelection(std::vector<KElectron> allelectrons, std::vector<KElectron>& leptonColl,  Double_t rho) {
  
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

void ElectronSel::ElectronSelection(std::vector<Bool_t> isEB, std::vector<Bool_t> isEE, std::vector<Bool_t> TrackerDrivenSeed, std::vector<Bool_t> EcalDrivenSeed, std::vector<Double_t> Eta, std::vector<Double_t> Phi, std::vector<Double_t> Pt, std::vector<Double_t> E, std::vector<Double_t> TrkIso, std::vector<Double_t> ECalIso, std::vector<Double_t> HCalIso, std::vector<Int_t> Charge, std::vector<Bool_t> ChargeConsistency, std::vector<Int_t> MissingHits, std::vector<Bool_t> HasMatchedConvPhot, std::vector<Double_t> DeltaEtaTrkSC, std::vector<Double_t> DeltaPhiTrkSC, std::vector<Double_t> SigmaIEtaIEta, std::vector<Double_t> HoE, std::vector<Double_t> caloEnergy, std::vector<Double_t> SuperClusterOverP, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, Double_t rho, std::vector<Lepton>& leptonColl) {

  D0=D0Error=0.;
   
  for (UInt_t ilep=0; ilep<Pt.size(); ilep++) {

    if ( fabs(Eta[ilep])>1.4442 && fabs(Eta[ilep])<1.566 ) continue;
    if ( caloEnergy[ilep]==0 ) continue;
    //// electron ID medium WP ////
    
    ElectronID = false;
    if (isEB[ilep]) {
      if (DeltaEtaTrkSC[ilep] < 0.004 &&
	  DeltaPhiTrkSC[ilep] < 0.06 &&
	  SigmaIEtaIEta[ilep] < 0.01 &&
	  HoE[ilep] < 0.12 &&
	  MissingHits[ilep] == 0 &&
	  fabs( (1 - SuperClusterOverP[ilep])/caloEnergy[ilep] ) < 0.05 &&
	  !HasMatchedConvPhot[ilep])
	ElectronID = true;
    }
    else if (isEE[ilep]) {
      if (DeltaEtaTrkSC[ilep] < 0.007 &&
	  DeltaPhiTrkSC[ilep] < 0.03 &&
	  SigmaIEtaIEta[ilep] < 0.03 &&
	  HoE[ilep] < 0.10 &&
	  MissingHits[ilep] == 0 &&
	  fabs( (1 - SuperClusterOverP[ilep])/caloEnergy[ilep] ) < 0.05 &&
	  !HasMatchedConvPhot[ilep])
	ElectronID = true;
    }
    else
      cout<< "something wrong with electron ID" <<endl;


    vLepton.SetPtEtaPhiE(Pt[ilep], Eta[ilep], Phi[ilep], E[ilep]);
    
    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    /*
    if ( isPrompt((long)Gen_Mother[ilep]) ) {
      if ( Charge[ilep]*Gen_Mother[ilep] == -24 || Charge[ilep]*Gen_Mother[ilep] == 15 ) 
	fakeType = Lepton::chargemisid;
      else
	fakeType = Lepton::notfake;
    }
    else {
      if ( nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 5 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 5 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 5)
        fakeType = Lepton::bjet;
	
      else if ( nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 4 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 4 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 4)
        fakeType = Lepton::cjet;
      
      else if (nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 1 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 1 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 1
            || nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 2 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 2 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 2
            || nthdigit( abs((long)Gen_Mother[ilep]),0 ) == 3 || nthdigit( abs((long)Gen_Mother[ilep]),1 ) == 3 || nthdigit( abs((long)Gen_Mother[ilep]),2 ) == 3 )
        fakeType = Lepton::jet;
    }
    */
    leptonType = Lepton::Electron;
/*
    ifid = (fabs(Eta[ilep]) < 1.479) ? 0 : 1;
    ElTkIso   = TrkIso[ilep] - AreaTrackerEle[ifid] * rho;
    ElEcalIso = ECalIso[ilep] - AreaEcalEle[ifid]  * rho;
    ElHcalIso = HCalIso[ilep] - AreaHcalEle[ifid] * rho;
*/
    if (fabs(Eta[ilep]) < 1.0) ifid = 0;
    else if (fabs(Eta[ilep]) < 1.479) ifid = 1;
    else if (fabs(Eta[ilep]) < 2.0) ifid = 2;
    else if (fabs(Eta[ilep]) < 2.2) ifid = 3;
    else if (fabs(Eta[ilep]) < 2.3) ifid = 4;
    else if (fabs(Eta[ilep]) < 2.4) ifid = 5;
    else ifid = 6;
    
    if (Pt[ilep] > 0.01)
      //LeptonRelIso =  (HCalIso[ilep] + ECalIso[ilep] + TrkIso[ilep]) / max(Pt[ilep], 20.);
      //LeptonRelIso  = (ElTkIso+ElEcalIso+ElHcalIso)/Pt[ilep];
      LeptonRelIso = ( HCalIso[ilep] + max( ECalIso[ilep] + TrkIso[ilep] - rho * PHONH[ifid], 0.) ) / Pt[ilep];
    else LeptonRelIso = 9999.;
    
    dz = fabs(Trkdz[ilep] - Vertex_Z);
    dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));

    (ChargeConsistency[ilep]) ? individual = true : individual = false;
 
    (fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min && Pt[ilep] < pt_cut_max) ? etaPt=true : etaPt =false;
    
    (dz<dz_cut && dxy<dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0=true : RelIsod0=false;
    
    if (ElectronID && individual && etaPt && RelIsod0 ) {
      leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge[ilep], fakeType, looseTight, TrkIso[ilep], LeptonRelIso) );
    }
    
  }
  
  std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
  
}
