#ifndef _SKTree_KMuon_H__
#define _SKTree_KMuon_H__

/// Local includes
#include "KParticle.h"

// STD includes
#include <string>

namespace snu {
  
  class KMuon : public KParticle {
  public:
    
    KMuon();
    
    ///Copy constructor
    KMuon(const KMuon& muon);
    
    ///Destructor    
    virtual ~KMuon() ;
    
    KMuon& operator= (const KMuon& obj);
    
    void SetPtErr(double pterror);
    void SetEtaErr(double etaerror);
    void SetRelIso(double reliso);
    void SetISOR03ChargedHad(double isor03ch );
    void SetISOR03NeutralHad(double isor03n );
    void SetISOR03Photon(double isor03ph );
    void SetIsolationEcalVeto(double isoEcalveto );
    void SetIsolationHcalVeto(double isoHcalveto );
    void SetPileUp_R03(double pileupr03);
    void SetTrackVx(double vtx);
    void SetTrackVy(double vty);
    void SetTrackVz(double vtz);
    void Setdz(double dz);
    void Setdxy(double dxy);
    void Setdxy_pat(double dxypat);
    void Setdxyerr_pat(double dxyerrpat);
    void SetD0(double d0);
    void SetD0Error(double d0err);
    void SetGlobalchi2(double glob_chi2);
    void SetValidHits(int validhits);
    void SetPixelValidHits(int valid_pix_hits);
    void SetValidStations(int validstations);
    void SetLayersWithMeasurement(int layer_with_meas);
    void SetISPF(int ispf);
    void SetIsGlobal(int isglobal);
    void SetMuonMatchedGenParticlePt(double muonmatch_genpt);
    void SetMuonMatchedGenParticlePhi(double muonmatch_genphi);
    void SetMuonMatchedGenParticleEta(double muonmatch_geneta);
    void SetMuonVtxIndex(int ivertex);
    void SetVertexDistXY(double vdistxy);

  
    inline Int_t IsPF() const {return k_muon_ispf;}
    inline Int_t IsGlobal() const {return k_muon_isglobal;}
    inline Int_t validHits() const {return k_muon_valid_hits;}
    inline Int_t validPixHits() const {return k_muon_valid_pixhits;}
    inline Int_t validStations() const {return k_muon_valid_stations;}
    inline Int_t ActiveLayer() const {return k_muon_layer_with_meas;}
    
    //// Truth
    inline Double_t MuonMatchedGenParticlePt() const {return k_muongen_pt;}
    inline Double_t MuonMatchedGenParticleEta() const {return k_muongen_eta;}
    inline Double_t MuonMatchedGenParticlePhi() const {return k_muongen_phi;}
      
    inline Double_t RelIso() const {return k_reliso;}
    inline Double_t PtError() const {return k_pterror;}
    inline Double_t EtaError() const {return k_etaerror;}
    inline Double_t IsoR03ch() const {return k_isor03ch;} /// charged hadron
    inline Double_t IsoR03nh() const {return k_isor03n;} /// neutral hadron
    inline Double_t IsoR03ph() const {return k_isor03ph;} /// photon
    inline Double_t IsoEcalVeto() const {return k_isoEcalveto;}
    inline Double_t IsoHcalVeto() const {return k_isoHcalveto;}
    inline Double_t PFPUIsoR03() const {return k_MuonPFIsoR03PU;}
    inline Double_t muonVtx() const {return k_muonVtx;}
    inline Double_t muonVty() const {return k_muonVty;}
    inline Double_t muonVtz() const {return k_muonVtz;}
    inline Double_t dZ() const {return k_dz;}
    inline Double_t dXY() const {return k_dxy;}
    inline Double_t dXYPat() const {return k_dxy_pat;}
    inline Double_t dXYErrPat() const {return k_dxyerr_pat;}
    inline Double_t D0() const {return k_d0;}
    inline Double_t D0Err() const {return k_d0err;}
    inline Double_t GlobalChi2() const {return k_globmuon_chi2;}
    inline Double_t VertexDistXY() const {return k_vtxdistxy;}
    inline Int_t MuonVertexIndex() const {return i_muonVtx;}

    inline Double_t IsoTerm() const {return (k_isor03ch + std::max(0.0, k_isor03n + k_isor03ph - k_MuonPFIsoR03PU));}
    
    
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
  
    Double_t k_pterror, k_etaerror , k_isor03ch, k_isor03n, k_isor03ph;
    Double_t k_isoEcalveto , k_isoHcalveto , k_MuonPFIsoR03PU, k_muonVtx, k_muonVty, k_muonVtz,k_muongen_pt,k_muongen_eta,k_muongen_phi;
    Double_t k_dz, k_dxy , k_d0, k_d0err, k_globmuon_chi2,  k_dxy_pat,  k_dxyerr_pat,k_vtxdistxy,k_reliso;
    Int_t k_muon_valid_hits, k_muon_valid_pixhits, k_muon_valid_stations, k_muon_layer_with_meas;
    Int_t k_muon_ispf, k_muon_isglobal;
    Int_t i_muonVtx;

    ClassDef(KMuon,1)
  };   
}//namespace snu

#endif
