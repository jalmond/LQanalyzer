#ifndef _SKTree_KJet_H__
#define _SKTree_KJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {


  // pfJetProbabilityBJetTags
  const double WP_BTAG_JPL = 0.245; // 0.275
  const double WP_BTAG_JPM = 0.515; // 0.545
  const double WP_BTAG_JPT = 0.760; // 0.790
  // pfCombinedInclusiveSecondaryVertexV2BJetTags
  const double WP_BTAG_CSVv2L = 0.460; // 0.605
  const double WP_BTAG_CSVv2M = 0.800; // 0.89
  const double WP_BTAG_CSVv2T = 0.935; // 0.97
  // pfCombinedMVAV2BJetTags
  const double WP_BTAG_cMVAv2L = -0.715; // -
  const double WP_BTAG_cMVAv2M =  0.185; // -
  const double WP_BTAG_cMVAv2T =  0.875; // -

  
  class KJet : public KParticle {
  public:


    enum Tagger{CSVv2=0,
		cMVAv2,
		JETPROB,
		CCvsLT,
		CCvsBT  };
    
    enum WORKING_POINT{Loose=0,
		       Medium,
		       Tight};
    
    enum syst_dir{none,
                  down,
                  up};

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
    void SetJetSmearedDownEnergy(double jetsmearEdown);
    void SetJetSmearedUpEnergy(double jetsmearEup);
    void SetJetSmearedEnergy(double jetsmearEup);
    
    
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
    Double_t BJetTaggerValue(Tagger tag) const; 
    inline Double_t CSVInclV2() const {return BJetTaggerValue(CSVv2);}
    inline Bool_t IsBTagged(Tagger tag, WORKING_POINT  wp) const {
      if(tag== CSVv2){
	if(wp==Loose) return (BJetTaggerValue(tag) > WP_BTAG_CSVv2L);
	if(wp==Medium) return (BJetTaggerValue(tag) > WP_BTAG_CSVv2M);
	if(wp==Tight) return (BJetTaggerValue(tag) > WP_BTAG_CSVv2T);
      }
      if(tag== cMVAv2){
	if(wp==Loose) return (BJetTaggerValue(tag) > WP_BTAG_cMVAv2L);
	if(wp==Medium) return (BJetTaggerValue(tag) > WP_BTAG_cMVAv2M);
	if(wp==Tight) return (BJetTaggerValue(tag) > WP_BTAG_cMVAv2T);
      }
      if(tag== JETPROB ){
	if(wp==Loose) return (BJetTaggerValue(tag) > WP_BTAG_JPL);
        if(wp==Medium) return (BJetTaggerValue(tag) > WP_BTAG_JPM);
        if(wp==Tight) return (BJetTaggerValue(tag) > WP_BTAG_JPT);
      }
      return true;
    }

    float scaleFactor(Tagger tag, WORKING_POINT wp, syst_dir systDir) const;

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
    inline Double_t SmearedDownEnergy() const {return k_jet_smeared_down_energy;}
    inline Double_t SmearedUpEnergy() const {return k_jet_smeared_up_energy;}
    inline Double_t SmearedEnergy() const {return k_jet_smeared_energy;}

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
   
    ClassDef(KJet,13)
  }; 
  

}//namespace snu

#endif
