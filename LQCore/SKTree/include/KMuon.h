
#ifndef _SKTree_KMuon_H__
#define _SKTree_KMuon_H__

/// Local includes
#include "KParticle.h"

// STD includes
#include <string>

namespace snu {
  
  class KMuon : public KParticle {
  public:

    enum MuonType{PROMPT=0,
		  FAKE=1,
		  CONV_CF=2,
		  CONV_NONECF=3,
		  CF=4
    };
    enum MuonMotherType{none=0,
			Z=1,
			W=2,
			ZorW=3,
			pion=4,
    };
    
    
    KMuon();
  
    ///Copy constructor
    KMuon(const KMuon& muon);
    
    ///Destructor    
    virtual ~KMuon() ;
    
    KMuon& operator= (const KMuon& obj);

    ///Return the type of this object, i.e. KMuon.h              
    virtual std::string Type() const;
    
    void SetRelIso(double cone, double reliso);
    void SetRelMiniIso( double relminiiso);


    void SetMCMatched(bool matched);

    void SetRochPt(double pt);
    void SetRochEta(double eta);
    void SetRochPhi(double phi);
    void SetRochM(double m);
    void SetRochE(double e);
    void Setdz(double dz);
    void Setdxy(double dxy);
    void Setdxy_sig(double dxysig);
    void SetGlobalchi2(double glob_chi2);
    void SetValidHits(int validhits);
    void SetPixelValidHits(int valid_pix_hits);
    void SetValidStations(int validstations);
    void SetLayersWithMeasurement(int layer_with_meas);
    void SetTrackVx(double vtx);
    void SetTrackVy(double vty);
    void SetTrackVz(double vtz);
    void SetISPF(bool ispf);
    void SetIsGlobal(bool isglobal);
    void SetIsTracker(bool istracker);
    void SetIsLoose(bool isLoose);
    void SetIsTight(bool isTight);
    void SetIsMedium(bool isMedium);

    void SetIsChargeFlip(Bool_t iscf);
    void SetIsPhotonConversion(Bool_t isconv);
    void SetIsFromTau(Bool_t istau);
    void SetMCMatchedPdgId(Int_t pg);
    void SetMotherPdgId(Int_t pg);
    void SetMotherTruthIndex(Int_t mindex);
    void SetMCTruthIndex(Int_t t_index);

    void SetIsSoft(bool isSoft);

    void SetShiftedEUp(double pt_up);
    void SetShiftedEDown(double pt_down);

    void SetTrigMatch(TString match);

    bool TriggerMatched(TString path);

    inline Bool_t IsPF() const {return k_muon_ispf;}
    inline Bool_t IsGlobal() const {return k_muon_isglobal;}
    inline Bool_t IsTracker() const {return k_muon_istracker;}
    inline Int_t validHits() const {return k_muon_valid_hits;}
    inline Int_t validPixHits() const {return k_muon_valid_pixhits;}
    inline Int_t validStations() const {return k_muon_valid_stations;}
    inline Int_t ActiveLayer() const {return k_muon_layer_with_meas;}
    inline Double_t muonVtx() const {return k_muonVtx;}
    inline Double_t muonVty() const {return k_muonVty;}
    inline Double_t muonVtz() const {return k_muonVtz;}

    inline Double_t dZ() const {return k_dz;}
    inline Double_t dXY() const {return k_dxy;}
    inline Double_t dXYSig() const {return k_dxy_sig;}
    
    inline Double_t GlobalChi2() const {return k_globmuon_chi2;}

    inline Bool_t   IsLoose () const {return k_isloose;}
    inline Bool_t   IsTight () const {return k_istight;}
    inline Bool_t   IsMedium () const {return k_ismedium;}
    inline Bool_t   IsSoft () const {return k_issoft;}
    inline Bool_t   MCMatched () const {return k_matched;}
    inline Bool_t MCIsCF() const{return k_is_cf;}
    inline Bool_t MCIsFromConversion() const{return k_is_conv;}

    inline Bool_t MCFromTau() const{return k_is_fromtau;}
    inline Bool_t MCIsPrompt() const{return k_matched;}
    inline Int_t MCMatchedPdgId() const{return k_mc_pdgid;}
    inline Int_t MotherPdgId() const{return k_mother_pdgid;}
    inline Int_t MotherTruthIndex() const{return k_mother_index;} 
    inline Int_t MCTruthIndex() const{return k_mc_index;}


    inline Double_t RelIso03()  const {return k_muon_reliso03;}
    inline Double_t RelIso04()  const {return k_muon_reliso04;}
    inline Double_t RelMiniIso()  const {return k_muon_relminiiso;}


    inline Double_t PtShiftedUp() const {return muon_pt_up;}
    inline Double_t PtShiftedDown() const {return muon_pt_down;}
    
    inline TString TrigMatch() const{return k_trig_match;}
    
    inline Double_t RochPt() const{return k_roch_pt;}
    inline Double_t RochPhi() const{return k_roch_phi;}
    inline Double_t RochEta() const{return k_roch_eta;}
    inline Double_t RochM() const{return k_roch_m;}
    inline Double_t RochE() const{return k_roch_e;}

    inline KMuon::MuonType GetParticleType() const{
      if(k_is_conv&&k_is_cf) return KMuon::CONV_CF;
      if(k_is_conv&&!k_is_cf)   return KMuon::CONV_NONECF;
      if(k_is_cf)  return KMuon::CF;
      if(k_matched) return KMuon::PROMPT;

      return KMuon::FAKE;
    }

    inline KMuon::MuonMotherType GetMotherType() const{
      if(k_mother_pdgid == 23) return KMuon::Z;
      if(fabs(k_mother_pdgid) == 24) return KMuon::W;
      if(k_mother_pdgid == -99999 ) return KMuon::ZorW;
      return  KMuon::pion;

    }

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
  
    Double_t k_dz, k_dxy ,k_dxy_sig,k_globmuon_chi2, k_muonVtx, k_muonVty, k_muonVtz;
    Int_t k_muon_valid_hits, k_muon_valid_pixhits, k_muon_valid_stations, k_muon_layer_with_meas;
    Bool_t k_muon_ispf, k_muon_isglobal, k_muon_istracker;
    
    Double_t muon_pt_up, muon_pt_down, k_muon_reliso03, k_muon_reliso04,k_muon_relminiiso;

    Double_t k_roch_pt,k_roch_phi,k_roch_eta,k_roch_m,k_roch_e;

    Bool_t k_isloose, k_istight, k_matched,k_is_cf,k_is_conv,k_is_fromtau,k_ismedium, k_issoft ;
    Int_t k_mother_pdgid, k_mc_pdgid,k_mother_index, k_mc_index;

    TString k_trig_match;
    
    ClassDef(KMuon,20)
  };   
}//namespace snu

#endif
