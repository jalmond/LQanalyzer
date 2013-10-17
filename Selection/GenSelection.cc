#include "GenSelection.h"

GenSel::GenSel() {};


GenSel::~GenSel() {};

void GenSel::GenSelection(std::vector<Double_t> Eta, std::vector<Double_t> Pt, std::vector<Double_t> Px, std::vector<Double_t> Py, std::vector<Double_t> Pz, std::vector<Double_t> E, std::vector<Double_t> Trkdx, std::vector<Double_t> Trkdy, std::vector<Double_t> Trkdz, Double_t Vertex_X, Double_t Vertex_Y, Double_t Vertex_Z, std::vector<Int_t> pdgId, std::vector<Int_t> status, std::vector<Int_t> ndaug, std::vector<Int_t> mother, std::vector<GenParticle>& genColl) {

  dz_cut=1.0;

  for (UInt_t ilep=0; ilep<Pt.size(); ilep++) {

    dz = fabs(Trkdz[ilep]-Vertex_Z);
    dxy = sqrt(pow(Trkdx[ilep]-Vertex_X,2)+pow(Trkdy[ilep]-Vertex_Y,2));
    D0 = 0.0;
    D0Error = 0.0;
    Int_t Charge = 0.0;
    Double_t TrkIso = 0.0;
    LeptonRelIso = 0.0;
    LeptonchiNdof = 0.0;
   
    vLepton.SetPxPyPzE(Px[ilep], Py[ilep], Pz[ilep], E[ilep]);

    if ( fabs(pdgId[ilep]==13) && fabs(pdgId[mother[ilep]])==24 || status[ilep]==3 || fabs(pdgId[mother[ilep]])==23 ) continue;
  //  cout << "idx "<< ilep << " pdgID  " << pdgId[ilep] << "  madre " << mother[ilep] << "  stato " << status[ilep]<< "  ndaug " <<ndaug[ilep]<<endl;
 
    if ( fabs(Eta[ilep]) < eta_cut && Pt[ilep] >= pt_cut_min && Pt[ilep] < pt_cut_max )
      genColl.push_back( GenParticle(leptonType, ilep, vLepton, Eta[ilep], LeptonchiNdof, D0, D0Error, dxy, dz, Charge, fakeType, looseTight, TrkIso, LeptonRelIso, pdgId[ilep], mother[ilep]) );
    
  }

  std::sort( genColl.begin(), genColl.end(), GenPTSorter );
  
}


