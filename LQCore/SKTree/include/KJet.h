#ifndef _SKTree_KJet_H__
#define _SKTree_KJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KJet : public KParticle {
  public:
    KJet();
    
    ///Copy constructor
    KJet(const KJet& jet);
    
    ///Destructor    
    virtual ~KJet() ;

    ///Assignment operator                                                              
    KJet& operator= (const KJet& obj);
    
    /// ID cut on jet
    void SetJetPassLooseID(int looseID);
    void SetJetPassTightID(int tightID);
    void SetJetPassTightLepVetoID(int tightID);
    
    /// Pileup
    void SetJetPileupIDLooseWP(bool pass);
    void SetJetPileupIDMediumWP(bool pass);
    void SetJetPileupIDTightWP(bool pass);
    void SetJetPileupIDMVA(double mva);
    
    
    //Multiplicities
    //// Pileup MVA to be added
    
    /// BTAG
    void SetCVSInclV2(double btag);

    /// Tracking

    /// Energy fractions
    void SetJetChargedEmEF(double chargeEmEF);
    
    //flavour
    void SetJetPartonFlavour(int pf);

    /// JET CORRECTIONS
    void SetJetRawPt(double rawpt);
    void SetJetRawEnergy(double rawe);
    void SetJetJECUnc(double jecunc);
    void SetJetScaledDownEnergy(double jetscaleEdown);
    void SetJetScaledUpEnergy(double jetscaleEup);
    void SetJetSmearedDownEnergy(double jetsmearEdown);
    void SetJetSmearedUpEnergy(double jetsmearEup);
    
    
    /// ID
    inline Int_t PassLooseID() const {return k_jet_passLooseID;}
    inline Int_t PassTightID() const {return k_jet_passTightID;}
    inline Int_t PassTightLepVetoID() const {return k_jet_passTightLepVetoID;}

    // Pileup flags
    inline Bool_t PileupJetIDLoose() const {return k_jet_passpileup_loose;}
    inline Bool_t PileupJetIDMedium() const {return k_jet_passpileup_medium;}
    inline Bool_t PileupJetIDTight() const {return k_jet_passpileup_tight;}

    inline Int_t PileupJetIDFlag() const {return k_jet_pileup_flag;}
    inline Double_t PileupJetIDMVA() const {return k_jet_pileup_mva;}
    
   
    /// BTAG variables
    inline Double_t CVSInclV2() const {return k_jet_cvsv2;}
 
    /// Energy Fraction
    inline Double_t ChargedEMEnergyFraction() const {return k_jet_chargeEmEF;}
    // flavour
    inline Double_t PartonFlavour() const {return k_jet_partonflavour;}

    /// Tracking Variables
    

    // Errors
    inline Double_t JECUncertainty() const {return k_jet_error_jec;}

    inline Double_t ScaledDownEnergy() const {return k_jet_scaled_down_energy;}
    inline Double_t ScaledUpEnergy() const {return k_jet_scaled_up_energy;}
    inline Double_t SmearedDownEnergy() const {return k_jet_smeared_down_energy;}
    inline Double_t SmearedUpEnergy() const {return k_jet_smeared_up_energy;}

    inline Double_t RawPt() const {return k_jet_pt_raw;}
    inline Double_t RawE() const {return k_jet_energy_raw;}
    

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    /// ID 
    Bool_t  k_jet_passLooseID ,k_jet_passTightID, k_jet_passTightLepVetoID;
    /// Multiplicities  
    
    Double_t k_jet_pt_raw, k_jet_energy_raw;
    /// BTAG variables  
    Double_t k_jet_cvsv2;

    /// Energy Fraction     
    Double_t k_jet_chargeEmEF;
    
    // flavour          
    Double_t k_jet_partonflavour;
    
    /// Tracking Variables
    
    // Errors
    Double_t  k_jet_error_jec,k_jet_scaled_down_energy,k_jet_scaled_up_energy,k_jet_smeared_down_energy,k_jet_smeared_up_energy;
    
    Bool_t k_jet_passpileup_loose, k_jet_passpileup_medium ,k_jet_passpileup_tight;
    Int_t k_jet_pileup_flag;
    Double_t k_jet_pileup_mva;
   
    ClassDef(KJet,8)
  }; 
  

}//namespace snu

#endif
