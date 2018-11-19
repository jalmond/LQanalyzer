#ifndef KMuon_H__
#define KMuon_H__

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



    void SetTypeBit(unsigned int typebit);
    void SetIDBit(unsigned int idbit);

    enum Selector {
      CutBasedIdLoose        = 1UL<< 0,  
      CutBasedIdMedium       = 1UL<< 1,  
      CutBasedIdMediumPrompt = 1UL<< 2,  // medium with IP cuts
      CutBasedIdTight        = 1UL<< 3,  
      CutBasedIdGlobalHighPt = 1UL<< 4,  // high pt muon for Z',W' (better momentum resolution)
      CutBasedIdTrkHighPt    = 1UL<< 5,  // high pt muon for boosted Z (better efficiency)
      PFIsoVeryLoose         = 1UL<< 6,  // reliso<0.40
      PFIsoLoose             = 1UL<< 7,  // reliso<0.25
      PFIsoMedium            = 1UL<< 8,  // reliso<0.20
      PFIsoTight             = 1UL<< 9,  // reliso<0.15
      PFIsoVeryTight         = 1UL<<10,  // reliso<0.10
      TkIsoLoose             = 1UL<<11,  // reliso<0.10
      TkIsoTight             = 1UL<<12,  // reliso<0.05
      SoftCutBasedId         = 1UL<<13,  
      SoftMvaId              = 1UL<<14,  
      MvaLoose               = 1UL<<15,  
      MvaMedium              = 1UL<<16,  
      MvaTight               = 1UL<<17,
      MiniIsoLoose           = 1UL<<18,  // reliso<0.40
      MiniIsoMedium          = 1UL<<19,  // reliso<0.20
      MiniIsoTight           = 1UL<<20,  // reliso<0.10
      MiniIsoVeryTight       = 1UL<<21,  // reliso<0.05
      TriggerIdLoose         = 1UL<<22,  // robust selector for HLT
      InTimeMuon             = 1UL<<23,   
      PFIsoVeryVeryTight     = 1UL<<24,  // reliso<0.05
      MultiIsoLoose          = 1UL<<25,  // miniIso with ptRatio and ptRel 
      MultiIsoMedium         = 1UL<<26   // miniIso with ptRatio and ptRel 
    };

    enum Type {
      GlobalMuon     =  1<<1,
      TrackerMuon    =  1<<2,
      StandAloneMuon =  1<<3,
      CaloMuon =  1<<4,
      PFMuon =  1<<5,
      RPCMuon =  1<<6,
      GEMMuon =  1<<7,
    ME0Muon = 1<<8
    };

    inline bool PassSelector( unsigned int s ) const { return (j_IDBit & s)==s; }
    inline bool IsType( unsigned int t ) const { return (j_TypeBit & t); }


    inline bool isPOGTight() const {return PassSelector(CutBasedIdTight);}
    inline bool isPOGHighPt() const {return PassSelector(CutBasedIdGlobalHighPt);}
    inline bool isPOGMedium() const {return PassSelector(CutBasedIdMedium);}
    inline bool isPOGLoose() const {return PassSelector(CutBasedIdLoose);}
    
    inline UInt_t IDBit() const { return j_IDBit;}
    inline UInt_t TypeBit() const { return j_TypeBit;}

    //==== ID
    bool PassID(TString ID);
    bool Pass_POGTight();
    bool Pass_POGTightWithTightIso();
    bool Pass_POGHighPtWithLooseTrkIso();
    bool Pass_HNPairTight();
    bool Pass_HNPairLoose();
    bool Pass_HNPairVeto();
    bool Pass_HNWRTight();
    bool Pass_HNWRLoose();
    bool Pass_HNWRVeto();
    bool Pass_HNWRNoIso();
    bool Pass_TESTID();


    ///Return the type of this object, i.e. KMuon.h              
    virtual std::string Type() const;
    
    void SetTrkIso(double iso);
    void SetECalIso(double iso);
    void SetHCalIso(double iso);
    void SetRelIso(double cone, double reliso);
    void SetRelMiniIso( double relminiiso);
    void SetMiniAODRelIso (double cone, double reliso);
    void SetMiniAODPt(double maodpt);

    void SetIsRochesterCorrected(bool corr);
    void SetMCMatched(bool matched);

    void SetType(int mutype);
    void SetRochPt(double pt);
    void SetRochSF(double pt);
    void SetRochSFUp(double eta);
    void Setdz(double dz);
    void SetIP2D(double dxy);
    void SetIP3D(double dxy);
    void SetSIP3D(double dxy);

    void SetGlobalchi2(double glob_chi2);
    void SetValidHits(int validhits);
    void SetPixelValidHits(int valid_pix_hits);
    void SetValidStations(int validstations);
    void SetLayersWithMeasurement(int layer_with_meas);
    void SetTrackVx(double vtx);
    void SetTrackVy(double vty);
    void SetTrackVz(double vtz);


    void SetIsChargeFlip(Bool_t iscf);
    void SetIsPhotonConversion(Bool_t isconv);
    void SetIsFromTau(Bool_t istau);
    void SetMCMatchedPdgId(Int_t pg);
    void SetMotherPdgId(Int_t pg);
    void SetMotherTruthIndex(Int_t mindex);
    void SetMCTruthIndex(Int_t t_index);

    void SetIsPromptFlag(bool pflag);


    
    inline Bool_t IsPF() const {return k_muon_ispf;}
    inline Bool_t IsGlobal() const {return k_muon_isglobal;}
    inline Bool_t IsStandAlone() const {return k_muon_isstandalone;}
    inline Bool_t IsTracker() const {return k_muon_istracker;}
    inline Int_t validHits() const {return k_muon_valid_hits;}
    inline Int_t validPixHits() const {return k_muon_valid_pixhits;}
    inline Int_t validStations() const {return k_muon_valid_stations;}
    inline Int_t ActiveLayer() const {return k_muon_layer_with_meas;}
    inline Double_t muonVtx() const {return k_muonVtx;}
    inline Double_t muonVty() const {return k_muonVty;}
    inline Double_t muonVtz() const {return k_muonVtz;}


    inline Bool_t IsPromptFlag() const {return k_isprompt;}
    inline Double_t dZ() const {return k_dz;}
    inline Double_t IP2D() const {return k_ip2d;}
    inline Double_t IP3D() const {return k_ip3d;}
    inline Double_t SIP3D() const {return  k_sip3d;}


    inline Double_t GlobalChi2() const {return k_globmuon_chi2;}

    inline Bool_t   IsLoose () const {return k_muon_ispf && (k_muon_isglobal||k_muon_istracker);}
    inline Bool_t   IsTight () const {return k_istight;}
    inline Bool_t   IsMedium () const {return k_ismedium;}
    inline Bool_t   IsSoft () const {return k_issoft;}
    inline Bool_t   IsHighPt () const {return k_ishighpt;}

    inline Bool_t   MCMatched () const {
      if(k_is_fromtau) return true;
      return k_matched;
    }
    inline Bool_t MCIsCF() const{return k_is_cf;}
    inline Bool_t MCIsFromConversion() const{return k_is_conv;}
    inline Bool_t IsRochesterCorrected() const{return k_corrected_rc;}
    inline Bool_t MCFromTau() const{return k_is_fromtau;}
    inline Bool_t MCIsPrompt() const{return k_matched;}
    inline Int_t MCMatchedPdgId() const{return k_mc_pdgid;}
    inline Int_t MotherPdgId() const{return k_mother_pdgid;}
    inline Int_t MotherTruthIndex() const{return k_mother_index;} 
    inline Int_t MCTruthIndex() const{return k_mc_index;}

    inline Double_t PFRelIso(double cone) const {
      if(cone == 0.3)   return k_muon_reliso03;
      else  if(cone == 0.4)   return k_muon_reliso04;
      else return -999.;
    }
    
    inline Double_t PTCone(double cone, double iso=0.07){
      float ptcone= this->Pt() * (1.+ std::max(0., k_muon_reliso04 - iso));
      if(cone == 0.3)  ptcone= this->Pt() * (1.+ std::max(0., k_muon_reliso03 - iso));
      if(ptcone < 5.) return -1.;
      return ptcone;
    }
    
    inline Double_t RelIso03()  const {return k_muon_reliso03;}
    inline Double_t RelIso04()  const {return k_muon_reliso04;}
    inline Double_t RelMiniAODIso03()  const {return k_muon_maod_reliso03;}
    inline Double_t RelMiniAODIso04()  const {return k_muon_maod_reliso04;}

    inline Double_t RelMiniIso()  const {return k_muon_relminiiso;}
    inline Double_t PFRelMiniIso() const { return k_muon_relminiiso; }


    inline Double_t TrkIso()  const {return k_muon_trkiso;}
    inline Double_t EcalIso()  const {return k_muon_ecaliso;}
    inline Double_t HcalIso()  const {return k_muon_hcaliso;}


    inline Double_t MiniAODPt() const {return muon_maod_pt;}

    
    inline Double_t RochPt() const{return k_roch_pt;}
    inline Double_t RochSF() const{return k_roch_sf;}
    inline Double_t RochSFUp() const{return k_roch_sf_up;}

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
    inline Int_t GetType() const {return k_mctype;}

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
  

    unsigned int j_TypeBit, j_IDBit;

    Double_t k_dz, k_ip2d ,k_ip3d,  k_sip3d,k_globmuon_chi2, k_muonVtx, k_muonVty, k_muonVtz;
    Int_t k_muon_valid_hits, k_muon_valid_pixhits, k_muon_valid_stations, k_muon_layer_with_meas;
    Bool_t k_muon_ispf, k_muon_isglobal,k_muon_isstandalone, k_muon_istracker;

    Double_t muon_maod_pt,  k_muon_reliso03, k_muon_reliso04,k_muon_relminiiso,k_muon_maod_reliso03, k_muon_maod_reliso04, k_muon_trkiso, k_muon_ecaliso, k_muon_hcaliso ;

    Double_t k_roch_pt, k_roch_sf,k_roch_sf_up;

    Bool_t  k_istight, k_matched,k_is_cf,k_is_conv,k_is_fromtau,k_ismedium, k_issoft, k_ishighpt;
    Int_t k_mother_pdgid, k_mc_pdgid,k_mother_index, k_mc_index;


    Bool_t k_corrected_rc;
    
    Int_t k_mctype;
    Bool_t k_isprompt;
    ClassDef(KMuon,24)
  };   
}//namespace snu

#endif
