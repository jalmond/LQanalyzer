#ifndef _SKTree_KElectron_H__
#define _SKTree_KElectron_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KElectron : public KParticle {
  public:
    KElectron();
    
    ///Copy constructor
    KElectron(const KElectron& el);
    
    ///Destructor    
    virtual ~KElectron() ;

    KElectron& operator= (const KElectron& obj);
    
    
    // set kinematic variables
    void SetSCEta(Double_t sceta);
    
    //##### NOTE charge/pt/eta/phi use tlv class
    
    /// Trigger matching
    
    
    //// set   vertex variables
    void Setdxy(Double_t d_xy);
    void Setdz(Double_t d_z);
    
    void SetSNUID(int id);
    void SetPassVeto(Bool_t pass);
    void SetPassLoose(Bool_t pass);
    void SetPassMedium(Bool_t pass);
    void SetPassTight(Bool_t pass);
    
    void SetIsPF(Bool_t ispf);
    void SetIsMCMatched(Bool_t ismatch);

    
    /// set ISO variables
    void SetPFChargedHadronIso03(Double_t pf_ch_03);
    void SetPFPhotonIso03(Double_t pf_ph_03);
    void SetPFNeutralHadronIso03(Double_t pf_ne_03);
    void SetPFChargedHadronIso04(Double_t pf_ch_03);
    void SetPFPhotonIso04(Double_t pf_ph_03);
    void SetPFNeutralHadronIso04(Double_t pf_ne_03);
    
    void SetPFRelIso03(Double_t pf_rel_03);
    void SetPFRelIso04(Double_t pf_rel_04);
    
    void SetPFAbsIso03(Double_t pf_abs_03);
    void SetPFAbsIso04(Double_t pf_abs_04);

    
    // set charge variables
    
    void SetGsfCtfScPixCharge(bool gsfctfscpix_ch);
    
    /// set conversion variables
    void SetHasMatchedConvPhot(Bool_t hasmatchConvPhot);

    
    void SetShiftedEUp(Double_t Eup);
    void SetShiftedEDown(Double_t Edown);

    void SetTrkVx(Double_t trkvx);
    void SetTrkVy(Double_t trkvy);
    void SetTrkVz(Double_t trkvz);

    ///// Functions to call class variables
    
    inline Bool_t  IsEBFiducial() {return bool (fabs(SCEta()) < 1.442);}
    inline Bool_t  IsEEFiducial() {return bool (fabs(SCEta()) > 1.560 && fabs(SCEta()) < 2.50);}
      
    /// // Kinematic variables
    inline Double_t  SCEta() const {return k_sceta;}


    inline Double_t PtShiftedUp() const{ return k_pt_shifted_up;}
    inline Double_t PtShiftedDown() const{ return k_pt_shifted_down;}

    /// Trigger matching
    
    // ID variables
    inline Bool_t PassVeto() const{return pass_veto;}
    inline Bool_t PassLoose() const{return pass_loose;}
    inline Bool_t PassMedium() const{return pass_medium;}
    inline Bool_t PassTight() const{return pass_tight;}
    
    inline Bool_t IsPF() const{return k_isPF;}
    inline Bool_t MCMatched() const{return k_mc_matched;}
    inline Int_t SNUID() const{return snu_id;}

    // charge variables
    
    inline Bool_t GsfCtfScPixChargeConsistency()  const {return k_gsf_ctscpix_charge;}
    
    // Conversion variables
    inline Bool_t HasMatchedConvPhot() const {return k_hasmatchconvphot;}
    
    
    // Isolation Variables
    inline Double_t PFChargedHadronIso03() const {return k_pf_chargedhad_iso03;}
    inline Double_t PFPhotonIso03() const {return k_pf_photon_iso03;}
    inline Double_t PFNeutralHadronIso03() const {return k_pf_neutral_iso03;}
    inline Double_t PFChargedHadronIso04() const {return k_pf_chargedhad_iso04;}
    inline Double_t PFPhotonIso04() const {return k_pf_photon_iso04;}
    inline Double_t PFNeutralHadronIso04() const {return k_pf_neutral_iso04;}
			
    inline Double_t PFRelIso03() const {return k_rel_iso03;}
    inline Double_t PFRelIso04() const {return k_rel_iso04;}
    inline Double_t PFAbsIso03() const {return k_abs_iso03;}
    inline Double_t PFAbsIso04() const {return k_abs_iso04;}

    
    /// VtxDist with vertex chosen to be primary   
    inline Double_t  dxy() const {return  k_dxy;}
    inline Double_t  dz() const {return  k_dz;}
    

    inline Double_t  TrkVx() const {return  k_trkvx;}
    inline Double_t  TrkVy() const {return  k_trkvy;}
    inline Double_t  TrkVz() const {return  k_trkvz;}
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions

    Double_t k_pf_chargedhad_iso03, k_pf_photon_iso03, k_pf_neutral_iso03, k_pf_chargedhad_iso04, k_pf_photon_iso04, k_pf_neutral_iso04, k_rel_iso03, k_rel_iso04;
    Double_t k_abs_iso03, k_abs_iso04;
    Double_t k_dxy, k_dz,k_trkvx,  k_trkvy,  k_trkvz;
    Double_t k_sceta;
    
    Bool_t k_gsf_ctscpix_charge,pass_tight, pass_veto, pass_medium, pass_loose, k_mc_matched, k_isPF,k_hasmatchconvphot;
    
    Double_t k_pt_shifted_up, k_pt_shifted_down;
    Int_t snu_id;
    

    ClassDef(KElectron,16);
  }; 
  
}//namespace snu

#endif
