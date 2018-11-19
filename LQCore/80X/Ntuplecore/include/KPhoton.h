#ifndef KPhoton_H
#define KPhoton_H

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KPhoton : public KParticle {
  public:
    KPhoton();
    
    ///Copy constructor
    KPhoton(const KPhoton& el);
    
    ///Destructor    
    virtual ~KPhoton() ;

    KPhoton& operator= (const KPhoton& obj);
    
    
    
    //##### NOTE charge/pt/eta/phi use tlv class

    // Bool
    void SetIsLoose   (bool b);
    void SetIsMedium  (bool b);
    void SetIsTight   (bool b);
    void SetPassMVA   (bool b);
    void SetMCMatched (bool b);
    void SetHasPixSeed(bool b);
    void SetPassElVeto(bool b);

    // Double
    
    void SetChargedHadIsoNoEA(double d);
    void SetpuChargedHadIsoNoEA(double d);
    void SetNeutalHadIsoNoEA(double d);
    void SetPhotonIsoNoEA(double d);
    void SetRhoIso(double d);
    void SetChargedHadIso(double d); 
    void SetPhotonIso(double d);   
    void SetNeutalHadIso(double d);  
    void SetSigmaIetaIeta(double d);    
    void SetR9(double d);    
    void SetHoverE(double d);
    void SetSCEta(double d); 
    void SetSCPhi(double d); 
    void SetSCRawE(double d); 
    void SetSCPreShowerE(double d);
    
    ///////// ///////// ///////// ///////// ///////// ///////// ///////// 
    ///// Functions to call class variables
    ///////// ///////// ///////// ///////// ///////// ///////// ///////// 
    
    /// Bool
    inline Bool_t  isLoose()    const {return k_ph_isloose;}
    inline Bool_t  isMedium()   const {return k_ph_ismedium;}
    inline Bool_t  isTight()    const {return k_ph_istight;}
    inline Bool_t  passMVA()    const {return k_ph_passmva;}
    inline Bool_t  mcMatched()  const {return k_mc_matched;}
    inline Bool_t  hasPixSeed() const {return k_ph_haspixseed;}
    inline Bool_t  passElVeto() const {return k_ph_passelveto;}
    
    /// Double
    inline Double_t ChargedHadIsoNoEA()    const {return k_ph_chhadiso_noEA;}
    inline Double_t puChargedHadIsoNoEA()  const {return k_ph_puchhadiso_noEA;}
    inline Double_t NeutalHadIsoNoEA()     const {return k_ph_nhadiso_noEA;}
    inline Double_t PhotonIsoNoEA()        const {return k_ph_phiso_noEA;}
    inline Double_t RhoIso()               const {return k_ph_rhoiso;}
    inline Double_t ChargedHadIso()        const {return k_ph_chhadiso;}
    inline Double_t PhotonIso()            const {return k_ph_photoniso;}
    inline Double_t NeutalHadIso()         const {return k_ph_nhadiso;}
    inline Double_t SigmaIetaIeta()        const {return k_ph_sigietaieta;}
    inline Double_t R9()                   const {return k_ph_r9;}
    inline Double_t HoverE()               const {return k_ph_hovere;}
    inline Double_t SCEta()                const {return k_ph_sceta;}
    inline Double_t SCPhi()                const {return k_ph_scphi;}
    inline Double_t SCRawE()               const {return k_ph_scrawe;}
    inline Double_t SCPreShowerE()         const {return k_ph_scpreshower_e;}

    /// Int
    
    

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions

    Double_t k_ph_chhadiso_noEA, k_ph_puchhadiso_noEA, k_ph_nhadiso_noEA, k_ph_phiso_noEA, k_ph_rhoiso, k_ph_chhadiso, k_ph_photoniso, k_ph_nhadiso, k_ph_sigietaieta, k_ph_r9, k_ph_hovere, k_ph_sceta, k_ph_scphi, k_ph_scrawe, k_ph_scpreshower_e;
    
    Bool_t k_ph_isloose, k_ph_ismedium, k_ph_istight, k_ph_passmva, k_mc_matched, k_ph_haspixseed, k_ph_passelveto;
    

    ClassDef(KPhoton,3);
  }; 
  
}//namespace snu

#endif
