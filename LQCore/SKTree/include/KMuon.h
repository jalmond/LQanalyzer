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

    ///Return the type of this object, i.e. KMuon.h              
    virtual std::string Type() const;
    
    void SetRelIso(double cone, double reliso);


    void SetMCMatched(bool matched);
    float ScaleFactor(const std::string& name, int sign) const ;

    void Setdz(double dz);
    void Setdxy(double dxy);
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


    inline Double_t GlobalChi2() const {return k_globmuon_chi2;}

    inline Bool_t   IsLoose () const {return k_isloose;}
    inline Bool_t   IsTight () const {return k_istight;}
    inline Bool_t   IsMedium () const {return k_ismedium;}
    inline Bool_t   IsSoft () const {return k_issoft;}
    inline Bool_t   MCMatched () const {return k_matched;}


    inline Double_t RelIso03()  const {return k_muon_reliso03;}
    inline Double_t RelIso04()  const {return k_muon_reliso04;}


    inline Double_t PtShiftedUp() const {return muon_pt_up;}
    inline Double_t PtShiftedDown() const {return muon_pt_down;}
    
    inline TString TrigMatch() const{return k_trig_match;}

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
  
    Double_t k_dz, k_dxy ,k_globmuon_chi2, k_muonVtx, k_muonVty, k_muonVtz;
    Int_t k_muon_valid_hits, k_muon_valid_pixhits, k_muon_valid_stations, k_muon_layer_with_meas;
    Bool_t k_muon_ispf, k_muon_isglobal, k_muon_istracker;

    Double_t muon_pt_up, muon_pt_down, k_muon_reliso03, k_muon_reliso04;

    Bool_t k_isloose, k_istight, k_matched,k_ismedium, k_issoft ;
    
    TString k_trig_match;
    
    ClassDef(KMuon,14)
  };   
}//namespace snu

#endif
