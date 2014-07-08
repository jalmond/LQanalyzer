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
    
   
    //// Setting class variables

    // set kinematic variables
    void SetSCEta(Double_t sceta);
    void SetSCPhi(Double_t scphi);        
    void SetisEB(Bool_t isEB);
    void SetisEE(Bool_t isEE);
    void SetRawEnergy(Double_t rawE);
    
    //##### NOTE charge/pt/eta/phi use tlv class
    
    /// Trigger matching
    void SetHLTDoubleElMatched(bool match);
    void SetHLTSingleElMatched8(bool match);
    void SetHLTSingleElMatched17(bool match);
    void SetHLTEMuMatched8(bool match);
    void SetHLTEMuMatched17(bool match);
    void SetHLTSingleElWP80Matched(bool match);
     
    /// set ID variables
    void SetElectronMVA(Double_t mva);
    void SetElectronTrigMVA(Double_t trig_mva);
    void SetTrackerDrivenSeed(Bool_t trackdrivenseed);
    void SetEcalDrivenSeed(Bool_t ecaldrivenseed);
    void SetDeltaEtaTrkSC(Double_t delta_etatrkSC);
    void SetDeltaPhiTrkSC(Double_t delta_phitrkSC);
    void SetSigmaIEtaIEta(Double_t sigmaIEtaIEta);
    void SetHoE(Double_t hoe);
    void SetcaloEnergy(Double_t caloE);
    void SetESuperClusterOverP(Double_t E_cluster_over_p);
    
    
    //// set   vertex variables
    void SetVtxIndex (Int_t vtx_index);
    void SetVtxDistXY(Double_t vtx_dist_xy);
    void SetVtxDistZ(Double_t vtx_dist_z);
    void SetLeadVtxDistXY(Double_t vtx_dist_xy);
    void SetLeadVtxDistZ(Double_t vtx_dist_z);
    void Setdxy(Double_t d_xy);
    void Setdz(Double_t d_z);
    void SetPrimaryVertexDXY(Double_t pv_dist_xy);
    void SetPrimaryVertexDXYError(Double_t pv_dist_xy_error);
    
    
    /// set ISO variables
    void SetTrkIsoDR03(Double_t trkiso);
    void SetECalIsoDR03(Double_t ecaliso);  
    void SetHCalIsoDR03(Double_t hcaliso);
    
    void SetTrkIsoDR04(Double_t trkiso);
    void SetECalIsoDR04(Double_t ecaliso);
    void SetHCalIsoDR04(Double_t hcaliso);
    
    void SetPFChargedHadronIso03(Double_t pf_ch_03);
    void SetPFPhotonIso03(Double_t pf_ph_03);
    void SetPFNeutralHadronIso03(Double_t pf_ne_03);
    void SetPFChargedHadronIso04(Double_t pf_ch_03);
    void SetPFPhotonIso04(Double_t pf_ph_03);
    void SetPFNeutralHadronIso04(Double_t pf_ne_03);
    
    
    // set charge variables
    
    void SetGsfCtfScPixCharge(bool gsfctfscpix_ch);
    void SetGsfScPixCharge(bool gsfscpix_ch);
    void SetGsfCtfCharge(bool gsfctf_ch);
    
    
    /// set conversion variables
    void SetMissingHits(Int_t missinghits); 
    void SetMissingLostHits(Int_t missinglosthits); 
    void SetHasMatchedConvPhot(Bool_t hasmatchConvPhot);
    void SetConvFitProb(double conv_fit_prob);
    void SetNBrems(double nbrems);
    void SetFBrem(double fbrem);
    void SetElDist(double fbrem);
    void SetCotTheta(double fbrem);
    
    /// set GEN  macthing
    void SetElectronMatchedGenPt(Double_t pt);
    void SetElectronMatchedGenEta(Double_t eta);
    void SetElectronMatchedGenPhi(Double_t phi);

    /// set Track variables
    void SetTrackPt(Double_t pt);
    void SetTrackValidFractionOfHits(Double_t valid_frac_hits);
    void SetTrkVx(Double_t trkvx);
    void SetTrkVy(Double_t trkvy);
    void SetTrkVz(Double_t trkvz);

    
    ///// Functions to call class variables
    
    inline Bool_t  IsEBFiducial() {return bool (fabs(SCEta()) < 1.442);}
    inline Bool_t  IsEEFiducial() {return bool (fabs(SCEta()) > 1.560 && fabs(SCEta()) < 2.50);}
      
    /// // Kinematic variables
    inline Double_t  SCEta() const {return k_sceta;}
    inline Double_t  SCPhi() const {return k_scphi;}
    inline Double_t  RawEnergy() const {return k_rawenergy;}
    inline Bool_t isEB() const {return k_isEB;}
    inline Bool_t isEE() const {return k_isEE;}
    

    /// Trigger matching
    inline Bool_t MatchedDiElectronTrigger() const {return k_diel_trig_match;}
    inline Bool_t MatchedSingleElectronTrigger8() const {return k_el_trig_match8;}
    inline Bool_t MatchedSingleElectronTrigger17() const {return k_el_trig_match17;}
    inline Bool_t MatchedElectronMuonTrigger8() const {return k_emu_trig_match8;}
    inline Bool_t MatchedElectronMuonTrigger17() const {return k_emu_trig_match17;}
    inline Bool_t MatchedSingleElectronWP80Trigger() const {return k_elwp80_trig_match;}

    // Vertex variables
    inline Double_t PrimaryVertexDXY() const {return k_pv_dist_xy;}
    inline Double_t PrimaryVertexDXYError() const {return k_pv_dist_xy_error;}
    inline Int_t VertexIndex() const {return k_vertex_index;}

    /// Track variables
    inline Double_t TrackPt() const {return k_track_pt;}
    inline Double_t TrackValidHitFraction() const {return k_track_hitfrac;}

    
    // ID variables

    inline Double_t  MVA() const{return k_mva;}
    inline Double_t  TrigMVA() const{return k_trigmva;}
    inline Bool_t    TrackerDrivenSeed() const {return k_trackdrivenseed;}
    inline Bool_t    EcalDrivenSeed() const {return k_ecaldrivenseed;}
    inline Double_t  DeltaEta() const {return  k_delta_etatrkSC;}
    inline Double_t  DeltaPhi() const {return  k_delta_phitrkSC;}
    inline Double_t  SigmaIEtaIEta() const {return  k_sigmaIEtaIEta;}
    inline Double_t  HoE() const {return  k_hoe;}
    inline Double_t  CaloEnergy() const {return  k_caloE;}
    inline Double_t  ESuperClusterOverP() const {return  k_E_cluster_over_p;}
    
    
    /// method 1
    inline Double_t  TrkVx() const {return  k_trkvx;}
    inline Double_t  TrkVy() const {return  k_trkvy;}
    inline Double_t  TrkVz() const {return  k_trkvz;}
    /// method 2
    inline Double_t VtxDistXY() const {return k_vtx_xy;}
    inline Double_t VtxDistZ() const {return k_vtx_z;}
    ///
    inline Double_t LeadVtxDistXY() const {return k_lvtx_xy;}
    inline Double_t LeadVtxDistZ() const {return k_lvtx_z;}

    // charge variables
    inline Bool_t GsfCtfScPixChargeConsistency()  const {return k_gsf_ctscpix_charge;}
    inline Bool_t GsffScPixChargeConsistency()  const {return k_gsf_scpix_charge;}
    inline Bool_t GsfCtfChargeConsistency()  const {return k_gsf_ct_charge;}
    
    // Conversion variables
    inline Int_t MissingHits() const {return k_missinghits;}
    inline Int_t MissingLostHits() const {return k_missing_lost_hits;}
    inline Double_t ConvFitProb () const {return k_convFitProb;}
    inline Bool_t HasMatchedConvPhot() const {return k_hasmatchconvphot;}
    inline Double_t NBrems() const {return k_nbrems;}
    inline Double_t FBrem() const {return k_fbrem;}
    inline Double_t Dist() const {return k_eldist;}
    inline Double_t CotTheta() const {return k_cottheta;}
    
    
    // Isolation Variables
    inline Double_t  TrkIsoDR03() const {return   k_trkiso_03;}
    inline Double_t  ECalIsoDR03() const {return  k_ecaliso_03;}
    inline Double_t  HCalIsoDR03() const {return  k_hcaliso_03;}

    inline Double_t  TrkIsoDR04() const {return   k_trkiso_04;}
    inline Double_t  ECalIsoDR04() const {return  k_ecaliso_04;}
    inline Double_t  HCalIsoDR04() const {return  k_hcaliso_04;}

    inline Double_t PFChargedHadronIso03() const {return k_pf_chargedhad_iso03;}
    inline Double_t PFPhotonIso03() const {return k_pf_photon_iso03;}
    inline Double_t PFNeutralHadronIso03() const {return k_pf_neutral_iso03;}
    inline Double_t PFChargedHadronIso04() const {return k_pf_chargedhad_iso04;}
    inline Double_t PFPhotonIso04() const {return k_pf_photon_iso04;}
    inline Double_t PFNeutralHadronIso04() const {return k_pf_neutral_iso04;}

    
    /// GEN matching
    inline Double_t MatchedGenParticlePt() const {return k_matched_gen_pt;}
    inline Double_t MatchedGenParticleEta() const {return k_matched_gen_eta;}
    inline Double_t MatchedGenParticlePhi() const {return k_matched_gen_phi;}
    
    /// VtxDist with vertex chosen to be primary   
    inline Double_t  dxy() const {return  k_dxy;}
    inline Double_t  dz() const {return  k_dz;}

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions

    Bool_t k_isEB,k_isEE,k_trackdrivenseed,k_ecaldrivenseed,k_hasmatchconvphot;
    Int_t k_missinghits, k_missing_lost_hits;
    Double_t k_trkiso_03,k_ecaliso_03,k_hcaliso_03,k_trkiso_04,k_ecaliso_04,k_hcaliso_04, k_delta_etatrkSC,k_delta_phitrkSC ;
    Double_t k_pf_chargedhad_iso03, k_pf_photon_iso03, k_pf_neutral_iso03, k_pf_chargedhad_iso04, k_pf_photon_iso04, k_pf_neutral_iso04;
    Double_t k_sigmaIEtaIEta,k_hoe,k_caloE,  k_E_cluster_over_p,k_trkvx,  k_trkvy,  k_trkvz;
    Double_t k_matched_gen_pt, k_matched_gen_eta, k_matched_gen_phi;

    Bool_t k_diel_trig_match,k_el_trig_match8, k_el_trig_match17 , k_elwp80_trig_match, k_emu_trig_match8,k_emu_trig_match17;
    Double_t k_mva, k_trigmva;
    Double_t k_dxy, k_dz;
    Double_t k_sceta,k_scphi, k_rawenergy;
    
    Double_t k_vtx_xy, k_vtx_z, k_lvtx_xy, k_lvtx_z;
    Bool_t k_gsf_ctscpix_charge, k_gsf_scpix_charge, k_gsf_ct_charge;
    Double_t k_convFitProb, k_nbrems, k_fbrem;
    
    Double_t k_pv_dist_xy, k_pv_dist_xy_error, k_track_pt, k_track_hitfrac;
    Int_t k_vertex_index;
    Double_t k_eldist, k_cottheta;

    ClassDef(KElectron,10)
  }; 
  
}//namespace snu

#endif
