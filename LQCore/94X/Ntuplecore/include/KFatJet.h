#ifndef KFatJet_H__
#define KFatJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {


  class KFatJet : public KParticle {
  public:


    enum Tagger{CSVv2=0};

    
    enum WORKING_POINT{Loose=0,
		       Medium,
		       Tight};
    
    enum syst_dir{none,
                  down,
                  up};

    KFatJet();
    
    ///Copy constructor
    KFatJet(const KFatJet& jet);
    
    ///Destructor    
    virtual ~KFatJet() ;

    ///Assignment operator                                                              
    KFatJet& operator= (const KFatJet& obj);
    
    /// ID cut on jet
    void SetJetPassTightID(int tightID);
    void SetJetPassTightLepVetoID(int tightID);
    
    void SetIsMCSmeared(bool issmeared);


    /// BTAG
    void SetBTagInfo(Tagger tag, double val);

    /// Energy fractions
    void SetJetChargedEmEF(double chargeEmEF);
    void SetJetNeutralEmEF(double neutralEmEF);
    void SetJetChargedHadEF(double chargeEmEF);
    void SetJetNeutralHadEF(double neutralEmEF);
    void SetJetChargedMultiplicity(double chargeEmEF);
    void SetJetNeutralMultiplicity(double neutralEmEF);


    //flavour
    void SetJetPartonFlavour(int pf);
    void SetJetHadronFlavour(int pf);
    void SetJetPartonPdgId(int pf);

    /// JET CORRECTIONS
    void SetJetScaledDownEnergy(double jetscaleEdown);
    void SetJetScaledUpEnergy(double jetscaleEup);
    void SetSmearedResDown(double jetsmearresdown);
    void SetSmearedResUp(double jetsmearresup);
    void SetSmearedRes(double jetsmearresup);
       
    

    void SetL1JetCorr(double jec);
    void SetFullJetCorr(double jec);
    void SetJetArea(double area);
    void SetJetMass(double mass);

    void SetTau1(double tau1);
    void SetTau2(double tau2);
    void SetTau3(double tau3);
    void SetTau4(double tau4);
    void SetSoftDropMass(double mass);
    

    
    /// JEC
    inline Double_t L1JetCorr() const{return k_l1jetcorr;}
    inline Double_t FullJetCorr() const{return k_fulljetcorr;}

    inline Double_t JetArea() const{return k_jetarea;}
    inline Double_t  MiniAODPt() const{return k_fatjet_miniaodpt;}

    inline Double_t Mass() const{return k_jet_mass;}


    /// ID
    inline Int_t PassTightID() const {return k_jet_passTightID;}
    inline Int_t PassTightLepVetoID() const {return k_jet_passTightLepVetoID;}
    inline Bool_t IsMCSmeared() const {return k_ismcsmeared;}

    /// BTAG variables
    Double_t BJetTaggerValue(Tagger tag) const;
    inline Double_t CSVInclV2() const {return BJetTaggerValue(CSVv2);}
    inline Bool_t IsBTagged(Tagger tag, WORKING_POINT  wp) const {

      return true;
    }


    /// Energy Fraction
    inline Double_t ChargedEMEnergyFraction() const {return k_jet_chargeEmEF;}
    inline Double_t NeutralEMEnergyFraction() const {return k_jet_neutralEmEF;}
    inline Double_t ChargedHADEnergyFraction() const {return k_jet_chargeHadEF;}
    inline Double_t NeutralHADEnergyFraction() const {return k_jet_neutralHadEF;}
    inline Double_t ChargedMultiplicity() const {return k_jet_chargeMultiplicity;}
    inline Double_t NeutralMultiplicity() const {return k_jet_neutralMultiplicity;}


    // flavour
    inline Int_t PartonFlavour() const {return k_jet_partonflavour;}
    inline Int_t HadronFlavour() const {return k_jet_hadronflavour;}
    inline Int_t PartonPdgId() const {return k_jet_partonpdgid;}


    // Errors
    inline Double_t ScaledDownEnergy() const {return k_jet_scaled_down_energy;}
    inline Double_t ScaledUpEnergy() const {return k_jet_scaled_up_energy;}
    inline Double_t SmearedResDown() const {return k_jet_smeared_down_energy;}
    inline Double_t SmearedResUp() const {return k_jet_smeared_up_energy;}
    inline Double_t SmearedRes() const {return k_jet_smeared_energy;}
    
    inline Double_t ScaledMassDown() const {return 1.- 0.023;}
    inline Double_t ScaledMassUp() const {return  1. + 0.023;}
    inline Double_t SmearedMassResDown() const {return  GetSmearedMassRes(-1);}
    inline Double_t SmearedMassResUp() const {return  GetSmearedMassRes(+1);}
    inline Double_t SmearedMassRes() const {return GetSmearedMassRes(0);}


    inline Double_t Tau1() const {return k_fatjet_tau1;}
    inline Double_t Tau2() const {return k_fatjet_tau2;}
    inline Double_t Tau3() const {return k_fatjet_tau3;}
    inline Double_t Tau4() const {return k_fatjet_tau4;}

    inline Double_t PrunedMass() const {return k_fatjet_prunedmass;}
    inline Double_t SoftDropMass() const {return k_fatjet_softdropmass;}
    
    float GetSmearedMassRes(int sys) const ;

  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    /// ID 
    Bool_t  k_jet_passTightID, k_jet_passTightLepVetoID;


    /// BTAG variables  
    Double_t k_jet_csv;

    /// Energy Fraction     
    Double_t k_jet_chargeEmEF,k_jet_neutralEmEF, k_jet_chargeHadEF, k_jet_neutralHadEF, k_jet_chargeMultiplicity, k_jet_neutralMultiplicity, k_jet_mass;
    

    Double_t k_fatjet_tau1, k_fatjet_tau2,k_fatjet_tau3,k_fatjet_tau4, k_fatjet_prunedmass, k_fatjet_softdropmass;
    // flavour          
    Int_t k_jet_partonflavour, k_jet_hadronflavour, k_jet_partonpdgid;
        
    // Errors
    Double_t  k_jet_scaled_down_energy,k_jet_scaled_up_energy,k_jet_smeared_down_energy,k_jet_smeared_up_energy, k_jet_smeared_energy;
    
    Bool_t k_ismcsmeared;

    Double_t k_l1jetcorr, k_fulljetcorr,k_jetarea;

    Double_t k_fatjet_miniaodpt;


    ClassDef(KFatJet,4)
  }; 
  

}//namespace snu

#endif
