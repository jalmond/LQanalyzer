#ifndef KElectron_H__
#define KElectron_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
//#include "TLorentzVector.h"

namespace snu {
  
  class KElectron : public KParticle {
  public:


    enum ElectronType{PROMPT=0,
		      FAKE=1,
		      PHOTONFAKE=2,
		      CONV_CF=3,
		      CONV_NONECF=4,
		      CF=5,
    };
    enum ElectronMotherType{none=0,
			    Z=1,
			    W=2,
			    ZorW=3,
			    pion=4,
    };

    KElectron();
    
    ///Copy constructor
    KElectron(const KElectron& el);
    
    ///Destructor    
    virtual ~KElectron() ;

    KElectron& operator= (const KElectron& obj);
    
    

    // set kinematic variables
    void SetSCEta(Double_t sceta);
    void SetSCPhi(Double_t scphi);


    
    //##### NOTE charge/pt/eta/phi use tlv class
    
    /// MVA
    void SetMVAIso(double mva);
    void SetMVANonIso(double zzmva);

    //    void SetGSF(double pt, double eta, double phi, double m);
    


    void SetType(int eltype);

    void SetIP2D(Double_t d_ip2d);
    void SetIP3D(Double_t d_ip3d);
    void SetSIP3D(Double_t d_sip3d);

    void Setdz(Double_t d_z);
        
    void SetIDBit(Int_t id);
    
    void SetIsChargeFlip(Bool_t iscf);
    void SetIsPhotonConversion(Bool_t isconv);

    void SetIsFromTau(Bool_t istau);
    void SetIsMCMatched(Bool_t ismatch);
       void SetMCMatchedPdgId(Int_t pg);	void SetMotherPdgId(Int_t pg);
    void SetMotherTruthIndex(Int_t mindex);
    void SetMCTruthIndex(Int_t t_index);

    /// set ISO variables
    void SetPFChargedHadronIso(Double_t cone,Double_t pf_ch);
    void SetPFPhotonIso(Double_t cone,Double_t pf_ph);
    void SetPFNeutralHadronIso(Double_t cone,Double_t pf_ne);
    void SetPFRelIsoRho(Double_t cone, Double_t pf_rel);
    void SetPFRelIsoBeta(Double_t cone, Double_t pf_rel);
    void SetPFRelMiniIso( Double_t pf_rel);
  
    
    // set charge variables
    void SetGsfCtfScPixCharge(bool gsfctfscpix_ch);
    void SetGsfScPixCharge(bool gsfscpix_ch);
    void SetGsfCtfCharge(bool gsfctf_ch);


    /// set conversion variables
    void SetIsMCExternalConversion(Bool_t isconv);
    void SetHasMatchedConvPhot(Bool_t hasmatchConvPhot);
    void SetMissingHits(Int_t mhits);
    void SetEcalDriven(Int_t edriven);
    
    void SetEnUncorr(Double_t E);

    void SetScaleEUp(Double_t Eup);
    void SetScaleEDown(Double_t Edown);
    
    void SetSmearEUp(Double_t Eup);
    void SetSmearEDown(Double_t Edown);


    void SetIsPromptFlag(bool pflag);

    void SetElIDVariables(double  electron_Full5x5_SigmaIEtaIEta , double electron_dEtaInSeed ,double  k_electron_dPhiIn,double  k_electron_HoverE  ,double  k_electron_InvEminusInvP);

    ///// Functions to call class variables
    
    inline Int_t GetType()  const {
      return k_eltype;
    }
    inline Bool_t IsPromptFlag() const {return k_isprompt;}

    inline Double_t IsoMVA() const {return k_mva_iso;}
    inline Double_t NonIsoMVA() const {return k_mva_noniso;}


    inline Bool_t  IsEBFiducial() {return bool (fabs(SCEta()) < 1.442);}
    inline Bool_t  IsEB1() {return bool (fabs(SCEta()) < 0.8);}
    inline Bool_t  IsEB2() {return bool (fabs(SCEta()) < 1.479);}
    inline Bool_t  IsEE() {return bool (fabs(SCEta()) > 1.479 && fabs(SCEta()) < 2.50);}
    inline Bool_t  IsEEFiducial() {return bool (fabs(SCEta()) > 1.560 && fabs(SCEta()) < 2.50);}
      
    /// // Kinematic variables
    inline Double_t  SCEta() const {return k_sceta;}
    inline Double_t  SCPhi() const {return k_scphi;}
    
    
    inline Int_t MissingHits() const {return k_missing_hits;}
    inline Int_t EcalDriven() const {return k_ecaldriven;}

    inline Double_t PtScaleUp() const{ return k_pt_scale_up;}
    inline Double_t PtScaleDown() const{ return k_pt_scale_down;}
    inline Double_t PtSmearUp() const{ return k_pt_smear_up;}
    inline Double_t PtSmearDown() const{ return k_pt_smear_down;}

    
    // ID variables
    inline Int_t IDBit() const{ return k_idbit;}

    enum Selector {
      POG_CB_VETO = 1<< 0,
      POG_CB_LOOSE = 1<< 1,
      POG_CB_MEDIUM = 1<< 2,
      POG_CB_TIGHT = 1<< 3,
      POG_MVA_ISO_WP80 = 1<< 4,
      POG_MVA_ISO_WP90 = 1<< 5,
      POG_MVA_ISO_WPHZZ = 1<< 6,
      POG_MVA_ISO_WPLOOSE = 1<< 7,
      POG_MVA_NOISO_WP80 = 1<< 8,
      POG_MVA_NOISO_WP90 = 1<< 9,
      POG_MVA_NOISO_WPLOOSE = 1<< 10,
      POG_HEEP = 1<< 11
    };

    inline bool PassSelector( unsigned int s ) const { return (k_idbit & s)==s; }
    inline bool passVetoID()   const {return PassSelector(POG_CB_VETO); }
    inline bool passLooseID()  const {return PassSelector(POG_CB_LOOSE); }
    inline bool passMediumID() const {return PassSelector(POG_CB_MEDIUM); }
    inline bool passTightID()  const {return PassSelector(POG_CB_TIGHT); }
    inline bool passMVAID_noIso_WP80() const {return PassSelector(POG_MVA_NOISO_WP80); }
    inline bool passMVAID_noIso_WP90() const {return PassSelector(POG_MVA_NOISO_WP90); }
    inline bool passMVAID_iso_WP80() const {return PassSelector(POG_MVA_ISO_WP80); }
    inline bool passMVAID_iso_WP90() const {return PassSelector(POG_MVA_ISO_WP90); }
    inline bool passHEEPID() const {return PassSelector(POG_HEEP); }

    // HEEP ID

    inline Bool_t PassMVAIso(TString id) const{
      //https://github.com/cms-sw/cmssw/blob/master/RecoEgamma/ElectronIdentification/python/Identification/mvaElectronID_Fall17_iso_V2_cff.py
      
      /*
egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wp90
egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wp80
egmGsfElectronIDs:mvaEleID-Fall17-noIso-V2-wpLoose
egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp90
egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp80
egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wpLoose
egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wpHZZ

      */
      if(k_mva_iso > GetCutValueMVA(id)) return true;
      else return false;
      
    }
    inline Bool_t PassMVANoIso(TString id) const{
      if(k_mva_noniso > GetCutValueMVA(id)) return true;
      else return false;

    }
    
    inline Double_t GetCutValueMVA(TString id) const{
      //https://github.com/cms-sw/cmssw/blob/master/RecoEgamma/ElectronIdentification/python/Identification/mvaElectronID_Fall17_iso_V2_cff.py                                                                                                                                  
      if(regMVA() == 1 && id== "mvaEleID-Fall17-iso-V2-wp80") return 3.53495358797 - exp(-this->Pt()/ 3.07272325141) * 9.94262764352;
      if(regMVA() == 2 && id== "mvaEleID-Fall17-iso-V2-wp80") return 3.06015605623 - exp(-this->Pt() / 1.95572234114) * 14.3091184421;
      if(regMVA() == 3 && id== "mvaEleID-Fall17-iso-V2-wp80") return 3.02052519639 - exp(-this->Pt() / 1.59784164742) * 28.719380105;
      if(regMVA() == 4 && id== "mvaEleID-Fall17-iso-V2-wp80") return 7.35752275071 - exp(-this->Pt() / 15.87907864) * 7.61288809226;
      if(regMVA() == 5 && id== "mvaEleID-Fall17-iso-V2-wp80") return 6.41811074032 - exp(-this->Pt() / 14.730562874) * 6.96387331587;
      if(regMVA() == 6 && id== "mvaEleID-Fall17-iso-V2-wp80") return 5.64936312428 - exp(-this->Pt() / 16.3664949747) * 7.19607610311;
      
      if(regMVA() == 1 && id== "mvaEleID-Fall17-iso-V2-wp90") return 2.84704783417 - exp(-this->Pt() / 3.32529515837) * 9.38050947827 ;
      if(regMVA() == 2 && id== "mvaEleID-Fall17-iso-V2-wp90") return 2.03833922005 - exp(-this->Pt() / 1.93288758682) * 15.364588247 ;
      if(regMVA() == 3 && id== "mvaEleID-Fall17-iso-V2-wp90") return 1.82704158461 - exp(-this->Pt() / 1.89796754399) * 19.1236071158 ;
      if(regMVA() == 4 && id== "mvaEleID-Fall17-iso-V2-wp90") return 6.12931925263 - exp(-this->Pt() / 13.281753835) * 8.71138432196 ;
      if(regMVA() == 5 && id== "mvaEleID-Fall17-iso-V2-wp90") return 5.26289004857 - exp(-this->Pt() / 13.2154971491) * 8.0997882835 ;
      if(regMVA() == 6 && id== "mvaEleID-Fall17-iso-V2-wp90") return 4.37338792902 - exp(-this->Pt() / 14.0776094696) * 8.48513324496 ;
      
      
      if(regMVA() == 1 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 3.26449620468 - exp(-this->Pt() / 3.32657149223) * 8.84669783568;
      if(regMVA() == 2 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 2.83557838497 - exp(-this->Pt() / 2.15150487651) * 11.0978016567;
      if(regMVA() == 3 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 2.91994945177 - exp(-this->Pt() / 1.69875477522) * 24.024807824;
      if(regMVA() == 4 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 7.1336238874 - exp(-this->Pt() / 16.5605268797) * 8.22531222391;
      if(regMVA() == 5 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 6.18638275782 - exp(-this->Pt() / 15.2694634284) * 7.49764565324;
      if(regMVA() == 6 && id== "mvaEleID-Fall17-noiso-V2-wp80") return 5.43175865738 - exp(-this->Pt() / 15.4290075949) * 7.56899692285;

      if(regMVA() == 1 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 2.77072387339 - exp(-this->Pt() / 3.81500912145) * 8.16304860178;
      if(regMVA() == 2 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 1.85602317813 - exp(-this->Pt() / 2.18697654938) * 11.8568936824;
      if(regMVA() == 3 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 1.73489307814 - exp(-this->Pt() / 2.0163211971) * 17.013880078;
      if(regMVA() == 4 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 5.9175992258 - exp(-this->Pt() / 13.4807294538) * 9.31966232685;
      if(regMVA() == 5 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 5.01598837255 - exp(-this->Pt() / 13.1280451502) * 8.79418193765;
      if(regMVA() == 6 && id== "mvaEleID-Fall17-noiso-V2-wp90") return 4.16921343208 - exp(-this->Pt() / 13.2017224621) * 9.00720913211;

      return 1000.;
    }

  
    inline Int_t regMVA() const{

      /*                                                                                                                                                                                                                                                                        
    "pt < 10. && abs(superCluster.eta) < 0.800", # EB1_5                                                                                                                                                                                                                        
     "pt < 10. && abs(superCluster.eta) >= 0.800 && abs(superCluster.eta) < 1.479", # EB2_5                                                                                                                                                                                     
     "pt < 10. && abs(superCluster.eta) >= 1.479", # EE_5                                                                                                                                                                                                                       
     "pt >= 10. && abs(superCluster.eta) < 0.800", # EB1_10                                                                                                                                                                                                                     
     "pt >= 10. && abs(superCluster.eta) >= 0.800 && abs(superCluster.eta) < 1.479", # EB2_10                                                                                                                                                                                   
     "pt >= 10. && abs(superCluster.eta) >= 1.479", # EE_10                                                                                                                                                                                                                     
      */
      if(this->Pt() < 10.){
	if(fabs(this->SCEta()) < 0.8)  return 1;
	else if (fabs(this->SCEta()) < 1.479)  return 2;
	else return 3;

      }
      else{
	if(fabs(this->SCEta()) < 0.8)  return 4;
        else if(fabs(this->SCEta()) < 1.479)  return 5;
	else return 6;

      }

    }
    
    inline Bool_t MCMatched() const{
      if(k_is_fromtau) return true;
      return k_mc_matched;
    }

    

    inline Bool_t MCIsPrompt() const{return k_mc_matched;}
    inline Bool_t MCIsCF() const{return k_is_cf;}
    inline Bool_t MCIsFromConversion() const{return k_is_conv;}
    inline Bool_t MCIsExternalConversion() const{return k_is_conv;}
    inline Bool_t MCFromTau() const{return k_is_fromtau;}
    inline Int_t MCMatchedPdgId() const{return k_mc_pdgid;}
    inline Int_t MotherPdgId() const{return k_mother_pdgid;}
    inline Int_t MotherTruthIndex() const{return k_mother_index;}
    inline Int_t MCTruthIndex() const{return k_mc_index;}

    inline KElectron::ElectronType GetParticleType() const{ 
      if(k_is_conv&&k_is_cf) return KElectron::CONV_CF;
      if(k_is_conv&&!k_is_cf)   return KElectron::CONV_NONECF; 
      if(k_is_cf)  return KElectron::CF;
      if(k_mc_matched) return KElectron::PROMPT;
      if(k_mc_pdgid==22) return KElectron::PHOTONFAKE;
      return KElectron::FAKE;

    }

    inline KElectron::ElectronMotherType GetMotherType() const{
      if(k_mother_pdgid == 23) return KElectron::Z;
      if(fabs(k_mother_pdgid) == 24) return KElectron::W;
      if(k_mother_pdgid == -99999 ) return KElectron::ZorW;
      return  KElectron::pion;

    }
    // charge variables
    
    inline Bool_t GsfCtfScPixChargeConsistency()  const {return k_gsf_ctscpix_charge;}
    inline Bool_t GsfScPixChargeConsistency()  const {return k_gsf_scpix_charge;}
    inline Bool_t GsfCtfChargeConsistency()  const {return k_gsf_ct_charge;}

    
    // Conversion variables
    inline Bool_t PassesConvVeto() const {return k_hasmatchconvphot;}
    

    
    // Isolation Variables
    inline Double_t PFChargedHadronIso(double cone) const {
      if(cone == 0.3)   return k_pf_chargedhad_iso03;
      else return -999.;
    }
    
    inline Double_t PFPhotonIso(double cone) const {
      if(cone == 0.3)   return k_pf_photon_iso03;
      else return -999.;
    }
    
    inline Double_t PFNeutralHadronIso(double cone) const {
      if(cone == 0.3)   return k_pf_neutral_iso03;
      else return -999.;
    }
    
		
    inline Double_t PTCone(double iso=0.08){
      float ptcone= this->Pt() * (1.+ std::max(0., k_rel_iso03 - iso));

      if(ptcone< 10.) return -1.;
      return ptcone;
    }


    inline Double_t PFRelMiniIso() const { return k_rel_miniiso; }


    inline Double_t PFRelIsoBeta(double cone ) const {
      if(cone == 0.3)   return k_electron_relIsoBeta03;
      else return -999.;
    }
    inline Double_t PFRelIsoRho(double cone ) const {
      if(cone == 0.3)   return k_electron_relIsoRho03;
      else return -999.;
    }

    inline Double_t PFRelIso(double cone ) const {
      return  PFRelIsoRho(cone);

    }

    inline Double_t PFAbsIsoBeta(double cone) const {
      if(cone == 0.3)   return k_electron_relIsoBeta03 * this->Pt();
      else return -999.;
    }

    
    inline Double_t PFAbsIsoRho(double cone) const {
      if(cone == 0.3)   return k_electron_relIsoRho03 * this->Pt();
      else return -999.;
    }

    /// VtxDist with vertex chosen to be primary   
    inline Double_t  IP2D() const {return  k_ip2D;}
    inline Double_t  IP3D() const {return  k_ip3D;}
    inline Double_t  SIP3D() const {return  k_sip3D;}

    inline Double_t  dz() const {return  k_dz;}
    

    inline Double_t  MVAIso() const {return  k_mva_iso;}
    inline Double_t  MVANonIso() const {return  k_mva_noniso;}


    inline Double_t  Full5x5_SigmaIEtaIEta() const {return  k_electron_Full5x5_SigmaIEtaIEta;}
    inline Double_t  dEtaInSeed() const {return  k_electron_dEtaInSeed;}
    inline Double_t  dPhiIn() const {return  k_electron_dPhiIn;}
    inline Double_t  HoverE() const {return  k_electron_HoverE;}
    inline Double_t  InvEminusInvP() const {return  k_electron_InvEminusInvP;}



  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions

    Double_t k_pf_chargedhad_iso03, k_pf_photon_iso03, k_pf_neutral_iso03, k_rel_iso03, k_rel_miniiso;

    Double_t k_ip2D, k_ip3D, k_sip3D, k_dz;


    Double_t  k_electron_relIsoBeta03, k_electron_relIsoRho03;

    
    Bool_t k_gsf_ctscpix_charge, k_gsf_scpix_charge, k_gsf_ct_charge;

    Int_t k_idbit;
    Bool_t k_mc_matched,  k_is_cf,k_is_conv, k_is_fromtau,k_hasmatchconvphot;
    
    Double_t k_pt_scale_up, k_pt_scale_down, k_pt_smear_up, k_pt_smear_down;
  
  Int_t snu_id,k_mother_pdgid, k_mc_pdgid,k_mother_index, k_mc_index;

    Int_t k_eltype;
    
    Double_t k_mva_iso, k_mva_noniso;

    Int_t k_missing_hits, k_ecaldriven;

    Double_t  k_smear_up, k_smear_down,k_scale_up, k_scale_down,k_en_uncorr;
 
    //    Double_t k_gsf_pt, k_gsf_eta, k_gsf_phi, k_gsf_charge;

    Double_t k_sceta, k_scphi;


    Bool_t k_isprompt;


    Double_t k_electron_Full5x5_SigmaIEtaIEta, k_electron_dEtaInSeed, k_electron_dPhiIn , k_electron_HoverE, k_electron_InvEminusInvP;

    ClassDef(KElectron,33);
  }; 
  
}//namespace snu

#endif
