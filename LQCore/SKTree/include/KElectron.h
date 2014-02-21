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
    void SetisRawEnergy(Double_t rawE);
    
    //##### NOTE charge/pt/eta/phi use tlv class
    
    ////

  void SetTrackerDrivenSeed(Bool_t trackdrivenseed);
  void SetEcalDrivenSeed(Bool_t ecaldrivenseed);
  void SetTrkIso(Double_t trkiso);
  void SetECalIso(Double_t ecaliso);  
  void SetHCalIso(Double_t hcaliso);
  void SetChargeConsistency(Bool_t chargeconsistency);
  void SetMissingHits(Int_t missinghits); 
  void SetHasMatchedConvPhot(Bool_t hasmatchConvPhot);
  void SetDeltaEtaTrkSC(Double_t delta_etatrkSC); 
  void SetDeltaPhiTrkSC(Double_t delta_phitrkSC);
  void SetSigmaIEtaIEta(Double_t sigmaIEtaIEta);
  void SetHoE(Double_t hoe);
  void SetcaloEnergy(Double_t caloE);
  void SetSuperClusterOverP(Double_t cluster_over_p);
  void SetTrkVx(Double_t trkvx);
  void SetTrkVy(Double_t trkvy);
  void SetTrkVz(Double_t trkvz);
  void Setdxy(Double_t d_xy);
  void Setdz(Double_t d_z);
  void SetElectronPassId(Int_t passid);
  

  inline Int_t MissingHits() const {return k_missinghits;}
  inline Int_t PassID() const {return k_passID;}
    
  inline Bool_t isEB() const {return k_isEB;}
  inline Bool_t isEE() const {return k_isEE;}
  inline Bool_t TrackerDrivenSeed() const {return k_trackdrivenseed;}
  inline Bool_t EcalDrivenSeed() const {return k_ecaldrivenseed;}
  inline Bool_t ChargeConsistency() const {return k_chargeconstistency;}
  inline Bool_t HasMatchedConvPhot() const {return k_hasmatchconvphot;}

  inline Double_t  TrkIso() const {return   k_trkiso;}
  inline Double_t  ECalIso() const {return  k_ecaliso;}
  inline Double_t  HCalIso() const {return  k_hcaliso;}
  inline Double_t  DeltaEtaTrkSC() const {return  k_delta_etatrkSC;}
  inline Double_t  DeltaPhiTrkSC() const {return  k_delta_phitrkSC;}
  inline Double_t  SigmaIEtaIEta() const {return  k_sigmaIEtaIEta;}
  inline Double_t  HoE() const {return  k_hoe;}
  inline Double_t  caloEnergy() const {return  k_caloE;}
  inline Double_t  SuperClusterOverP() const {return  k_cluster_over_p;}
  inline Double_t  TrkVx() const {return  k_trkvx;}
  inline Double_t  TrkVy() const {return  k_trkvy;}
  inline Double_t  TrkVz() const {return  k_trkvz;}
  inline Double_t  dxy() const {return  k_dxy;}
  inline Double_t  dz() const {return  k_dz;}

  
  
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions

    Bool_t k_isEB,k_isEE,k_trackdrivenseed,k_chargeconstistency,k_ecaldrivenseed,k_hasmatchconvphot;
    Int_t k_missinghits,k_passID ;
    Double_t k_trkiso,k_ecaliso,k_hcaliso,k_delta_etatrkSC,k_delta_phitrkSC ;
    Double_t k_sigmaIEtaIEta,k_hoe,k_caloE,  k_cluster_over_p,k_trkvx,  k_trkvy,  k_trkvz;
    Double_t k_dxy, k_dz;

    ClassDef(KElectron,2)
  }; 
  
}//namespace snu

#endif
