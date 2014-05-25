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
    
    /// Pileup
    void SetJetPileupIDLooseWP(bool pass);
    void SetJetPileupIDMediumWP(bool pass);
    void SetJetPileupIDTightWP(bool pass);
    void SetJetPileupIDFlag(int idflag);
    void SetJetPileupIDMVA(double mva);
    
    
    //Multiplicities
    void SetJetChargedMultiplicity(int chargeMult);    
    void SetJetNeutralMultiplicity(int neutralMult);
    void SetJetChargedHadronMultiplicity(int chargeHadMult);
    void SetJetNeutralHadronMultiplicity(int neutralHadMult);
    void SetJetElectronMultiplicity(int elMult);
    void SetJetHFEMMultiplicity(int hfemMult);
    void SetJetHFHadronMultiplicity(int hfhMult);
    void SetJetMuonMultiplicity(int muMult);
    void SetJetPhotonMultiplicity( int phMult);
    
    //// Pileup MVA to be added
    
    /// BTAG
    void SetJetSecVertBtag(double svbt);
    void SetJetTrackCountingHighPurBTag(double tchpt);
    void SetJetJetProbabilityBTag(double JP);    

    /// Tracking
    void SetJetNConstituents(int jetNconst);
    void SetJetClosestVertW3DSep(double cv3ds);
    void SetJetClosestVertexWeightedXYSeparation(double cvxys);
    void SetJetClosestVertexWeightedZSeparation(double cvzs);
    void SetJetBestVertexTrackAssociationIndex(double bvtai);
    void SetJetBestVertexTrackAssociationFactor(double bvtaf);

    /// Energy fractions
    void SetJetNeutralEmEF(double neutEmEF);
    void SetJetNeutralHEF(double neutHEF);
    void SetJetChargedEmEF(double chargeEmEF);
    void SetJetChargedHEF(double chargeHEF);
    void SetJetChargedMuEnergyFraction(double cmuef);
    void SetJetHFEMEnergyFraction(double hfemef);
    void SetJetHFHadronEnergyFraction(double hfhef);
    void SetJetMuonEnergyFraction(double muef);
    void SetJetPhotonEnergyFraction(double phef);
    void SetJetElectronEnergyFraction(double elef);
    
    //flavour
    void SetJetPartonFlavour(int pf);

    /// JET CORRECTIONS
    void SetJetRawPt(double rawpt);
    void SetJetRawEnergy(double rawe);
    void SetJetL1FastJetJEC(double L1FastJetJEC);
    void SetJetL2L3ResJEC(double L2L3ResJEC);
    void SetJetL2RelJEC(double JetL2RelJEC);
    void SetJetL3AbsJEC(double JetL3AbsJEC);
    void SetJetL5BottomJEC(double JetL5BottomJEC);
    void SetJetL5CharmJEC(double JetL5CharmJEC);
    void SetJetL5UDSJEC(double JetL5UDSJEC);
    void SetJetL5GluonJEC(double JetL5GluonJEC);
    void SetJetJECUnc(double jecunc);
    void SetJetScaledDownEnergy(double jetscaleEdown);
    void SetJetScaledUpEnergy(double jetscaleEup);
    void SetJetScaledDownPt(double jetscalePtdown);
    void SetJetScaledUpPt(double jetscalePtup);
    void SetJetSmearedDownEnergy(double jetsmearEdown);
    void SetJetSmearedUpEnergy(double jetsmearEup);
    void SetJetSmearedDownPt(double jetsmearPtdown);
    void SetJetSmearedUpPt(double jetsmearPtup);
    
    
    /// ID
    inline Int_t PassLooseID() const {return k_jet_passLooseID;}
    inline Int_t PassTightID() const {return k_jet_passTightID;}

    // Pileup flags
    inline Bool_t PileupJetIDLoose() const {return k_jet_passpileup_loose;}
    inline Bool_t PileupJetIDMedium() const {return k_jet_passpileup_medium;}
    inline Bool_t PileupJetIDTight() const {return k_jet_passpileup_tight;}

    inline Int_t PileupJetIDFlag() const {return k_jet_pileup_flag;}
    inline Double_t PileupJetIDMVA() const {return k_jet_pileup_mva;}
    
   
    
    /// Multiplicities 
    inline Int_t ChargedMultiplicity() const {return k_jet_chargeMult;}
    inline Int_t NeutralMultiplicity() const {return k_jet_neutralMult;}
    inline Int_t ChargedHadronMultiplicity() const {return k_jet_chargeHadMult;}
    inline Int_t NeutralHadronMultiplicity() const {return k_jet_neutralHadMult;}
    inline Int_t MuonMultiplicity() const {return k_jet_muonMult;}
    inline Int_t ElectronMultiplicity() const {return k_jet_elMult;}
    inline Int_t PhotonMultiplicity() const {return k_jet_phMult;}
    inline Int_t HFEMMultiplicity() const {return k_jet_hfemMult;}
    inline Int_t HFHadronMultiplicity() const {return k_jet_hfhadronMult;}
    
    /// BTAG variables
    inline Double_t CombinedSecVertexBtag() const {return k_jet_SecVertBtag;}
    inline Double_t PFJetTrackCountingHighPurBTag() const {return k_jet_TCHPT;}
    inline Double_t BtagProb() const {return k_jet_JetProbBtag;}
 
    /// Energy Fraction
    inline Double_t NeutralEMEnergyFraction() const {return k_jet_neutralEmEF;}
    inline Double_t NeutralHadEnergyFraction() const {return k_jet_neutralHEF;}
    inline Double_t ChargedEMEnergyFraction() const {return k_jet_chargeEmEF;}
    inline Double_t ChargedHadEnergyFraction() const {return k_jet_chargeHEF;}
    inline Double_t HFEMEnergyFraction() const {return k_jet_hfemEF;}
    inline Double_t HFHadEnergyFraction() const {return k_jet_hfhadronEF;}
    inline Double_t ChargedMuEnergyFraction() const {return k_jet_chargedmuEF;}
    inline Double_t MuonEnergyFraction() const {return k_jet_muonEF;}
    inline Double_t ElectronEnergyFraction() const {return k_jet_electronEF;}
    inline Double_t PhotonEnergyFraction() const {return k_jet_photonEF;}
    
    // flavour
    inline Double_t PartonFlavour() const {return k_jet_partonflavour;}

    /// Tracking Variables
    inline Int_t Nconstituents() const {return k_jet_Nconst;}
    inline Double_t JetRho() const {return k_jet_closest3Dsep;}    
    inline Double_t ClosestXYsep() const {return k_jet_closestXYsep;}
    inline Double_t ClosestZsep() const {return k_jet_closestZsep;}
    inline Double_t BestVertexTrackAssociationIndex() const {return k_jet_bestvertexTrackAssociatedIndex;}
    inline Double_t BestVertexTrackAssociationFactor() const {return k_jet_bestvertexTrackAssociatedFactor;}
    

    // Errors
    inline Double_t L1FastJetJEC() const {return k_jet_l1fastjet_jec;}
    inline Double_t L2L3ResJEC() const {return k_jet_l2l3res_jec;}
    inline Double_t L2RelJEC() const {return k_jet_l2rel_jec;}
    inline Double_t L3AbsJEC() const {return k_jet_l3abs_jec;}
    inline Double_t L5BottomJEC() const {return k_jet_l5bottom_jec;}
    inline Double_t L5CharmJEC() const {return k_jet_l5charm_jec;}
    inline Double_t L5UDSJEC() const {return k_jet_l5uds_jec;}
    inline Double_t L5GluonJEC() const {return k_jet_l5gluon_jec;}
    inline Double_t JECUncertainty() const {return k_jet_error_jec;}

    inline Double_t ScaledDownEnergy() const {return k_jet_scaled_down_energy;}
    inline Double_t ScaledUpEnergy() const {return k_jet_scaled_up_energy;}
    inline Double_t ScaledDownPt() const {return k_jet_scaled_down_pt;}
    inline Double_t ScaledUpPt() const {return k_jet_scaled_up_pt;}
    inline Double_t SmearedDownEnergy() const {return k_jet_smeared_down_energy;}
    inline Double_t SmearedUpEnergy() const {return k_jet_smeared_up_energy;}
    inline Double_t SmearedDownPt() const {return k_jet_smeared_down_pt;}
    inline Double_t SmearedUpPt() const {return k_jet_smeared_up_pt;}

    inline Double_t RawPt() const {return k_jet_pt_raw;}
    inline Double_t RawE() const {return k_jet_energy_raw;}
    

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    /// ID 
    Bool_t  k_jet_passLooseID ,k_jet_passTightID;
    /// Multiplicities  
    Int_t  k_jet_chargeMult,k_jet_neutralMult,k_jet_chargeHadMult,k_jet_neutralHadMult,k_jet_muonMult,k_jet_elMult,k_jet_phMult,k_jet_hfemMult,k_jet_hfhadronMult;
    
    Double_t k_jet_pt_raw, k_jet_energy_raw;
    /// BTAG variables  
    Double_t k_jet_SecVertBtag,k_jet_TCHPT,k_jet_JetProbBtag;

    /// Energy Fraction     
    Double_t k_jet_neutralEmEF,k_jet_neutralHEF, k_jet_chargeEmEF, k_jet_chargeHEF,k_jet_hfemEF,k_jet_hfhadronEF,k_jet_chargedmuEF,k_jet_muonEF,k_jet_electronEF,k_jet_photonEF;
    
    // flavour          
    Double_t k_jet_partonflavour;
    
    /// Tracking Variables
    Int_t k_jet_Nconst;
    Double_t k_jet_closest3Dsep,k_jet_closestXYsep,k_jet_closestZsep,k_jet_bestvertexTrackAssociatedIndex,k_jet_bestvertexTrackAssociatedFactor;
    
    // Errors
    Double_t k_jet_l1fastjet_jec,k_jet_l2l3res_jec,k_jet_l2rel_jec,k_jet_l3abs_jec, k_jet_l5bottom_jec, k_jet_l5charm_jec,k_jet_l5uds_jec,k_jet_l5gluon_jec, k_jet_error_jec,k_jet_scaled_down_energy,k_jet_scaled_up_energy,k_jet_scaled_down_pt,k_jet_scaled_up_pt,k_jet_smeared_down_energy,k_jet_smeared_up_energy,k_jet_smeared_down_pt,k_jet_smeared_up_pt;
    
    Bool_t k_jet_passpileup_loose, k_jet_passpileup_medium ,k_jet_passpileup_tight;
    Int_t k_jet_pileup_flag;
    Double_t k_jet_pileup_mva;
   
    ClassDef(KJet,5)
  }; 
  

}//namespace snu

#endif
