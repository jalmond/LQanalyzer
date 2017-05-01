#ifndef _SKTree_KFatJet_H__
#define _SKTree_KFatJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {


  class KFatJet : public KParticle {
  public:


    enum Tagger{CSVv2=0,
                cMVAv2,
                JETPROB,
                CCvsLT,
                CCvsBT  };
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
    void SetJetPassLooseID(int looseID);
    void SetJetPassTightID(int tightID);
    void SetJetPassTightLepVetoID(int tightID);
    
    /// Pileup
    void SetJetPileupIDLooseWP(bool pass);
    void SetJetPileupIDMediumWP(bool pass);
    void SetJetPileupIDTightWP(bool pass);
    void SetJetPileupIDMVA(double mva);
    
    void SetL1JetCorr(double jec);
    void SetL2JetCorr(double jec);
    void SetL3JetCorr(double jec);
    void SetL2L3ResJetCorr(double jec);

    void SetJetArea(double area);

    inline Double_t L1JetCorr() const{return k_fatl1jetcorr;}
    inline Double_t L2JetCorr() const{return k_fatl2jetcorr;}
    inline Double_t L3JetCorr() const{return k_fatl3jetcorr;}
    inline Double_t L2L3ResJetCorr() const{return k_fatl2l3resjetcorr;}

    inline Double_t JetArea() const{return k_fatjetarea;}

    //Multiplicities
    //// Pileup MVA to be added
    
    /// BTAG
    void SetBTagInfo(Tagger tag, double val);
    void SetCTagInfo(Tagger tag, double val);

    void SetVtxMass(double mass);
    void SetVtx3DVal(double val);
    void SetVtx3DSig(double sig);
    void SetVtxNTracks(int ntrk);
    /// Tracking

    /// Energy fractions
    void SetJetChargedEmEF(double chargeEmEF);
    
    //flavour
    void SetJetPartonFlavour(int pf);
    void SetJetHadronFlavour(int pf);
    void SetJetPartonPdgId(int pf);

    /// JET CORRECTIONS
    void SetJetRawPt(double rawpt);
    void SetJetRawEnergy(double rawe);
    void SetJetJECUnc(double jecunc);
    void SetJetScaledDownEnergy(double jetscaleEdown);
    void SetJetScaledUpEnergy(double jetscaleEup);
    void SetSmearedResDown(double jetsmearresdown);
    void SetSmearedResUp(double jetsmearresup);
    void SetSmearedRes(double jetsmearresup);
    
    
    void SetTau1(double tau1);
    void SetTau2(double tau2);
    void SetTau3(double tau3);
    void SetPrunedMass(double mass);
    void SetSoftDropMass(double mass);
    
    void SetPuppiTau1(double tau1);
    void SetPuppiTau2(double tau2);
    void SetPuppiTau3(double tau3);
    void SetPuppiPt(double pt);
    void SetPuppiEta(double eta);
    void SetPuppiPhi(double phi);   
    void SetPuppiM(double m);


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
    
    Double_t BJetTaggerValue(Tagger tag) const;
    inline Double_t CSVInclV2() const {return BJetTaggerValue(CSVv2);}


    /// Energy Fraction
    inline Double_t ChargedEMEnergyFraction() const {return k_jet_chargeEmEF;}
    // flavour
    inline Int_t PartonFlavour() const {return k_jet_partonflavour;}
    inline Int_t HadronFlavour() const {return k_jet_hadronflavour;}
    inline Int_t PartonPdgId() const {return k_jet_partonpdgid;}

    /// Tracking Variables
    
    inline Double_t VtxMass() const {return k_vtx_mass;}
    inline Double_t Vtx3DVal() const {return k_vtx_3dval;}
    inline Double_t Vtx3DSig() const {return k_vtx_3dsig;}
    inline Int_t VtxNtrack() const {return k_vtx_ntrack;}

    // Errors
    inline Double_t JECUncertainty() const {return k_jet_error_jec;}
    inline Double_t ScaledDownEnergy() const {return k_jet_scaled_down_energy;}
    inline Double_t ScaledUpEnergy() const {return k_jet_scaled_up_energy;}
    inline Double_t SmearedResDown() const {return k_jet_smeared_down_energy;}
    inline Double_t SmearedResUp() const {return k_jet_smeared_up_energy;}
    inline Double_t SmearedRes() const {return k_jet_smeared_energy;}

    inline Double_t RawPt() const {return k_jet_pt_raw;}
    inline Double_t RawE() const {return k_jet_energy_raw;}
    
    inline Double_t Tau1() const {return k_fatjet_tau1;}
    inline Double_t Tau2() const {return k_fatjet_tau2;}
    inline Double_t Tau3() const {return k_fatjet_tau3;}

    inline Double_t PrunedMass() const {return k_fatjet_prunedmass;}
    inline Double_t SoftDropMass() const {return k_fatjet_softdropmass;}
    inline Double_t PuppiTau1() const {return k_fatjet_puppi_tau1;}
    inline Double_t PuppiTau2() const {return k_fatjet_puppi_tau2;}
    inline Double_t PuppiTau3() const {return k_fatjet_puppi_tau3;}

    inline Double_t PuppiPt() const {return k_fatjet_puppi_pt;}
    inline Double_t PuppiEta() const {return k_fatjet_puppi_eta;}
    inline Double_t PuppiPhi() const {return k_fatjet_puppi_phi;}
    inline Double_t PuppiM() const {return k_fatjet_puppi_m;}
    


  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    /// ID 
    Bool_t  k_jet_passLooseID ,k_jet_passTightID, k_jet_passTightLepVetoID;
    /// Multiplicities  
    
    Double_t k_jet_pt_raw, k_jet_energy_raw;
    /// BTAG variables  
    Double_t k_jet_csv2 ,k_jet_cmva2, k_jet_jetprobbjet, k_jet_cc_vs_lt,k_jet_cc_vs_bt, k_vtx_mass, k_vtx_3dval,k_vtx_3dsig;
    
    Int_t k_vtx_ntrack;

    /// Energy Fraction     
    Double_t k_jet_chargeEmEF;
    
    // flavour          
    Int_t k_jet_partonflavour, k_jet_hadronflavour, k_jet_partonpdgid;
    
    /// Tracking Variables
    
    // Errors
    Double_t  k_jet_error_jec,k_jet_scaled_down_energy,k_jet_scaled_up_energy,k_jet_smeared_down_energy,k_jet_smeared_up_energy, k_jet_smeared_energy;
    
    Bool_t k_jet_passpileup_loose, k_jet_passpileup_medium ,k_jet_passpileup_tight;
    Int_t k_jet_pileup_flag;
    Double_t k_jet_pileup_mva;
   
    Double_t k_fatjet_tau1, k_fatjet_tau2,k_fatjet_tau3, k_fatjet_prunedmass, k_fatjet_softdropmass, k_fatjet_puppi_tau1, k_fatjet_puppi_tau2, k_fatjet_puppi_tau3, k_fatjet_puppi_pt, k_fatjet_puppi_eta, k_fatjet_puppi_phi, k_fatjet_puppi_m;

    Double_t k_fatl1jetcorr, k_fatl2jetcorr,k_fatl3jetcorr,k_fatl2l3resjetcorr,k_fatjetarea;

    ClassDef(KFatJet,2)
  }; 
  

}//namespace snu

#endif
