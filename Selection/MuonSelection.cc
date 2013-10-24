#include "MuonSelection.h"

using namespace snu;

MuonSel::MuonSel() {};

MuonSel::~MuonSel() {};

void MuonSel::MuonSelection(std::vector<KMuon> allmuons, std::vector<KMuon>& leptonColl) {
  
  //for (UInt_t ilep=0; ilep<allmuons.size(); ilep++) {
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    D0 = fabs( muit->D0());
    D0Error = muit->D0Err();
    
    if (muit->Pt() > 0.01)      LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    

    
    /// TIGHT MUON frmo muon POG
    (muit->IsPF()==1 && muit->IsGlobal()==1 && muit->validHits() >0 && muit->validPixHits()>0 && muit->validStations()>1 && muit->ActiveLayer() >5) ? individual = true :individual = false;
    
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && muit->IsoEcalVeto() < ECalDeposit_max && ( muit->IsoHcalVeto() >= HCalDeposit_min || muit->IsoEcalVeto() >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;
    ///// ETA and pt cut
    (fabs(muit->Eta()) < eta_cut && muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max && muit->PtError()/muit->Pt()<=0.10) ? etaPt=true : etaPt =false;

    
    (muit->GlobalChi2() <chiNdof_cut && LeptonRelIso < relIso_cut && fabs(muit->dZ())<dz_cut && fabs(muit->dXY())<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || muit->GlobalChi2()  >=chiNdofMIN_cut || fabs(muit->dXY())>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    
    if (etaPt  && DepositVeto && individual &&RelIsod0Chi2){
      leptonColl.push_back(*muit);    
    }
  }
    
}

void MuonSel::TightMuonSelection(std::vector<KMuon> allmuons, std::vector<KMuon>& leptonColl) {
  
  //for (UInt_t ilep=0; ilep<allmuons.size(); ilep++) {
  for (std::vector<KMuon>::iterator muit = allmuons.begin(); muit!=allmuons.end(); muit++){
    
    D0 = fabs( muit->D0());
    D0Error = muit->D0Err();
    
    if (muit->Pt() > 0.01)      
      LeptonRelIso = muit->IsoTerm()/muit->Pt();
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;    
    if (D0Error < 1E-6) D0Error = 1E-6;
    
    /// TIGHT MUON frmo muon POG
    (muit->IsPF()==1 && muit->IsGlobal()==1 && muit->validHits() >0 && muit->validPixHits()>0 && muit->validStations()>1 && muit->ActiveLayer() >5) ? individual = true :individual = false;
    
    /// ENERGY DEPOSIT
    (muit->IsoHcalVeto() < HCalDeposit_max && muit->IsoEcalVeto() < ECalDeposit_max && ( muit->IsoHcalVeto() >= HCalDeposit_min || muit->IsoEcalVeto() >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;
    ///// ETA and pt cut
    (fabs(muit->Eta()) < eta_cut && muit->Pt() >= pt_cut_min && muit->Pt() < pt_cut_max && muit->PtError()/muit->Pt()<=0.10) ? etaPt=true : etaPt =false;

    
    (muit->GlobalChi2() <chiNdof_cut && LeptonRelIso < relIso_cut && fabs(muit->dZ())<dz_cut && fabs(muit->dXY())<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || muit->GlobalChi2()  >=chiNdofMIN_cut || fabs(muit->dXY())>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;

    if (etaPt  && DepositVeto && individual &&RelIsod0Chi2)
      leptonColl.push_back(*muit);    
  }
  
}



void MuonSel::MuonSelection(std::vector<Int_t> IsPF, std::vector<Int_t> IsGlobal, std::vector<Double_t> Eta, std::vector<Double_t> Phi, std::vector<Double_t> Pt, std::vector<Double_t> PtErr, std::vector<Double_t> E, std::vector<Double_t> TrkIso, std::vector<Double_t> ECalIso, std::vector<Double_t> HCalIso, std::vector<Double_t> ECalIsoDeposit, std::vector<Double_t> HCalIsoDeposit, std::vector<Int_t> Charge, std::vector<Int_t> ValidHits, std::vector<Int_t> PixelValidHits, std::vector<Int_t> ValidStations, std::vector<Int_t> LayersWithMeasurement, std::vector<Double_t> GlobalChi2, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, std::vector<Double_t> TrkIPToolsIP, std::vector<Double_t> TrkIPToolsIPError, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Double_t> PUpt, std::vector<Lepton>& leptonColl) {

  for (UInt_t ilep=0; ilep<Pt.size(); ilep++) {

    LeptonchiNdof = GlobalChi2[ilep]; 

    dz = fabs(Trkdz[ilep]-Vertex_Z);
    dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));
    D0 = fabs( TrkIPToolsIP[ilep] );
    D0Error = TrkIPToolsIPError[ilep];
   
    // RHO
    // = (fabs(Muon_Eta[imuon]) < 1.479) ? 0 : 1;    //we distinguish beetwen EB and EE and HB and HE
/*
    if (fabs(Eta[ilep]) < 0.5) ifid=0;
    else if (fabs(Eta[ilep]) >= 0.5 && fabs(Eta[ilep]) < 1.0) ifid=1;
    else if (fabs(Eta[ilep]) >= 1.0 && fabs(Eta[ilep]) < 1.5) ifid=2;
    else if (fabs(Eta[ilep]) >= 1.5 && fabs(Eta[ilep]) < 2.0) ifid=3;
    else if (fabs(Eta[ilep]) >= 2.0 && fabs(Eta[ilep]) < 2.5) ifid=4;
    else ifid=-1;

    MuTkIso   = TrkIso[ilep] - AreaTrackerMu[ifid] * rho;
    MuEcalIso = ECalIso[ilep] - AreaEcalMu[ifid]  * rho;
    MuHcalIso = HCalIso[ilep] - AreaHcalMu[ifid] * rho;
*/  
    vLepton.SetPtEtaPhiE(Pt[ilep], Eta[ilep], Phi[ilep], E[ilep]);

    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    leptonType = Lepton::Muon;

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
    if (Pt[ilep] > 0.01)
      //LeptonRelIso = (HCalIso[ilep] + ECalIso[ilep] + TrkIso[ilep]) / std::max(Pt[ilep], 20.);
      //LeptonRelIso  = (MuTkIso+MuEcalIso+MuHcalIso)/Pt[ilep];
      LeptonRelIso = (TrkIso[ilep] + std::max(0.0, ECalIso[ilep] + HCalIso[ilep] - 0.5*PUpt[ilep]))/Pt[ilep];
//      LeptonRelIso = (TrkIso[ilep] + ECalIso[ilep] + HCalIso[ilep])/Pt[ilep];
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
    if (D0Error < 1E-6) D0Error = 1E-6;


    (IsPF[ilep]==1 && IsGlobal[ilep]==1 && ValidHits[ilep]>0 && PixelValidHits[ilep]>0 && ValidStations[ilep]>1 && LayersWithMeasurement[ilep]>5) ? individual = true :individual = false;

    (HCalIsoDeposit[ilep] < HCalDeposit_max && ECalIsoDeposit[ilep] < ECalDeposit_max && (HCalIsoDeposit[ilep] >= HCalDeposit_min || ECalIsoDeposit[ilep] >= ECalDeposit_min) ) ? DepositVeto=true : DepositVeto=false;

    (fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min && Pt[ilep] < pt_cut_max && PtErr[ilep]/Pt[ilep]<=0.10) ? etaPt=true : etaPt =false;

    (LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    //(LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    //(LeptonchiNdof<chiNdof_cut && dz<dz_cut && dxy<dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0Chi2=true : RelIsod0Chi2=false; 

    if (etaPt && RelIsod0Chi2 && DepositVeto && individual)
      leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge[ilep], fakeType, looseTight, TrkIso[ilep], LeptonRelIso) );
    
  }
  
  std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
  
}




void MuonSel::LooseMuonSelection(std::vector<Int_t> IsPF, std::vector<Int_t> IsTracker, vector<Int_t> IsGlobal, std::vector<Double_t> Eta, std::vector<Double_t> Phi, std::vector<Double_t> Pt, std::vector<Double_t> PtErr, std::vector<Double_t> E, std::vector<Double_t> TrkIso, std::vector<Double_t> ECalIso, std::vector<Double_t> HCalIso, std::vector<Double_t> ECalIsoDeposit, std::vector<Double_t> HCalIsoDeposit, std::vector<Int_t> Charge, std::vector<Int_t> ValidHits, std::vector<Int_t> PixelValidHits, std::vector<Int_t> ValidStations, std::vector<Int_t> LayersWithMeasurement, std::vector<Double_t> GlobalChi2, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, std::vector<Double_t> TrkIPToolsIP, std::vector<Double_t> TrkIPToolsIPError, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Double_t> PUpt, std::vector<Lepton>& leptonColl) {


  for (UInt_t ilep=0; ilep<Pt.size(); ilep++) {

 
    LeptonchiNdof = GlobalChi2[ilep]; 

    dz = fabs(Trkdz[ilep]-Vertex_Z);
    dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));
    D0 = fabs( TrkIPToolsIP[ilep] );
    D0Error = TrkIPToolsIPError[ilep];
     
    vLepton.SetPtEtaPhiE(Pt[ilep], Eta[ilep], Phi[ilep], E[ilep]);

    fakeType = Lepton::unknown;
    looseTight = Lepton::Other;
    leptonType = Lepton::Muon;
 
    if (Pt[ilep] > 0.01)
      LeptonRelIso = (TrkIso[ilep] + std::max(0.0, ECalIso[ilep] + HCalIso[ilep] - 0.5*PUpt[ilep]))/Pt[ilep];
    else LeptonRelIso = 9999.;
    if (LeptonRelIso<0) LeptonRelIso=0.0001;
    
    if (D0Error < 1E-6) D0Error = 1E-6;


    (IsPF[ilep] && (IsTracker[ilep]==1 || IsGlobal[ilep]==1) ) ? individual = true :individual = false;

    (fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min && Pt[ilep] < pt_cut_max) ? etaPt=true : etaPt =false;

    (LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || LeptonchiNdof>=chiNdofMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    //(LeptonchiNdof<chiNdof_cut && LeptonRelIso < relIso_cut && fabs(dz-Vz)<dz_cut && fabs(dxy-Vxy)<dxy_cut && ( LeptonRelIso >= relIsoMIN_cut || fabs(dxy-Vxy)>=dxyMIN_cut) ) ? RelIsod0Chi2=true : RelIsod0Chi2=false;
    //(LeptonchiNdof<chiNdof_cut && dz<dz_cut && dxy<dxy_cut && LeptonRelIso < relIso_cut && LeptonRelIso >= relIsoMIN_cut) ? RelIsod0Chi2=true : RelIsod0Chi2=false;

    if (etaPt && RelIsod0Chi2 && individual)
      leptonColl.push_back( Lepton(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge[ilep], fakeType, looseTight, TrkIso[ilep], LeptonRelIso) );
    
  }
  
  std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );

}

void MuonSel::SetDeposits(Double_t ECalDeposit , Double_t HCalDeposit) {
    ECalDeposit ? ECalDeposit_max = ECalDeposit : ECalDeposit_max=4.0;
    HCalDeposit ? HCalDeposit_max = HCalDeposit : HCalDeposit_max=6.0;
    ECalDeposit_min = 0.0;
    HCalDeposit_min = 0.0;
}

void MuonSel::SetDeposits(Double_t ECalDeposit1 , Double_t HCalDeposit1, Double_t ECalDeposit2 , Double_t HCalDeposit2) {
    ECalDeposit1 ? ECalDeposit_min = ECalDeposit1 : ECalDeposit_min=0.0;
    HCalDeposit1 ? HCalDeposit_min = HCalDeposit1 : HCalDeposit_min=0.0;
    ECalDeposit2 ? ECalDeposit_max = ECalDeposit2 : ECalDeposit_max=4.0;
    HCalDeposit2 ? HCalDeposit_max = HCalDeposit2 : HCalDeposit_max=6.0;
}
