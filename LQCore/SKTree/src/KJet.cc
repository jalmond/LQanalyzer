#include "KJet.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KJet)

/**
 *Default constructor.
 */
KJet::KJet() :
KParticle()
{
  k_jet_passLooseID=false;
  k_jet_passTightID=false;
  k_jet_passpileup_loose=false;
  k_jet_passpileup_medium=false;
  k_jet_passpileup_tight=false;
  k_jet_pileup_flag=0;
  k_jet_pileup_mva=0.;
  k_jet_chargeMult=0;
  k_jet_neutralMult=0;
  k_jet_chargeHadMult=0;
  k_jet_neutralHadMult=0;
  k_jet_muonMult=0;
  k_jet_elMult=0;
  k_jet_phMult=0;
  k_jet_hfemMult=0;
  k_jet_hfhadronMult=0;
  k_jet_SecVertBtag=0.;
  k_jet_TCHPT=0.;
  k_jet_JetProbBtag=0.;
  k_jet_neutralEmEF=0.;
  k_jet_neutralHEF=0.;
  k_jet_chargeEmEF=0.;
  k_jet_chargeHEF=0.;
  k_jet_hfemEF=0.;
  k_jet_hfhadronEF=0.;
  k_jet_chargedmuEF=0.;
  k_jet_muonEF=0.;
  k_jet_electronEF=0.;
  k_jet_photonEF=0.;
  k_jet_partonflavour=0.;
  k_jet_Nconst=0;
  k_jet_closest3Dsep=0.;
  k_jet_closestXYsep=0.;
  k_jet_closestZsep=0.;
  k_jet_bestvertexTrackAssociatedIndex=0.;
  k_jet_bestvertexTrackAssociatedFactor=0.;
  k_jet_l1fastjet_jec=0.;
  k_jet_l2l3res_jec=0.;
  k_jet_l2rel_jec=0.;
  k_jet_l3abs_jec=0.;
  k_jet_l5bottom_jec=0.;
  k_jet_l5charm_jec=0.;
  k_jet_l5uds_jec=0.;
  k_jet_l5gluon_jec=0.;
  k_jet_error_jec=0.;
  k_jet_scaled_down_energy=0.;
  k_jet_scaled_up_energy=0.;
  k_jet_scaled_down_pt=0.;
  k_jet_scaled_up_pt=0.;
  k_jet_smeared_down_energy=0.;
  k_jet_smeared_up_energy=0.;
  k_jet_smeared_down_pt=0.;
  k_jet_smeared_up_pt=0.;
  k_jet_energy_raw=0.;
  k_jet_pt_raw=0.;
  
}

/**
 * Copy constructor.
 */
KJet::KJet(const KJet& jet) :
    KParticle(jet)
{
  k_jet_passLooseID= jet.PassLooseID();
  k_jet_passTightID= jet.PassTightID();
  k_jet_passpileup_loose= jet.PileupJetIDLoose();
  k_jet_passpileup_medium= jet.PileupJetIDMedium();
  k_jet_passpileup_tight=jet.PileupJetIDTight();
  k_jet_pileup_flag=jet.PileupJetIDFlag();
  k_jet_pileup_mva= jet.PileupJetIDMVA();
  k_jet_chargeMult=jet.ChargedMultiplicity();
  k_jet_neutralMult=jet.NeutralMultiplicity();
  k_jet_chargeHadMult=jet.ChargedHadronMultiplicity();
  k_jet_neutralHadMult=jet.NeutralHadronMultiplicity();
  k_jet_muonMult=jet.MuonMultiplicity();
  k_jet_elMult=jet.ElectronMultiplicity();
  k_jet_phMult=jet.PhotonMultiplicity();
  k_jet_hfemMult=jet.HFEMMultiplicity();
  k_jet_hfhadronMult=jet.HFHadronMultiplicity();
  k_jet_SecVertBtag=jet.CombinedSecVertexBtag() ;
  k_jet_TCHPT=jet.PFJetTrackCountingHighPurBTag();
  k_jet_JetProbBtag=jet.BtagProb();
  k_jet_neutralEmEF=jet.NeutralEMEnergyFraction();
  k_jet_neutralHEF=jet.NeutralHadEnergyFraction();
  k_jet_chargeEmEF=jet.ChargedEMEnergyFraction();
  k_jet_chargeHEF=jet.ChargedHadEnergyFraction();
  k_jet_hfemEF=jet.HFEMEnergyFraction();
  k_jet_hfhadronEF=jet.HFHadEnergyFraction();
  k_jet_chargedmuEF=jet.ChargedMuEnergyFraction();
  k_jet_muonEF=jet.MuonEnergyFraction();
  k_jet_electronEF=jet.ElectronEnergyFraction();
  k_jet_photonEF=jet.PhotonEnergyFraction();
  k_jet_partonflavour=jet.PartonFlavour();
  k_jet_Nconst=jet.Nconstituents();
  k_jet_closest3Dsep=jet.JetRho();
  k_jet_closestXYsep=jet.ClosestXYsep();
  k_jet_closestZsep=jet.ClosestZsep();
  k_jet_bestvertexTrackAssociatedIndex=jet.BestVertexTrackAssociationIndex();
  k_jet_bestvertexTrackAssociatedFactor=jet.BestVertexTrackAssociationFactor();
  k_jet_l1fastjet_jec=jet.L1FastJetJEC();
  k_jet_l2l3res_jec=jet.L2L3ResJEC();
  k_jet_l2rel_jec=jet.L2RelJEC();
  k_jet_l3abs_jec=jet.L3AbsJEC();
  k_jet_l5bottom_jec=jet.L5BottomJEC();
  k_jet_l5charm_jec=jet.L5CharmJEC();
  k_jet_l5uds_jec=jet.L5UDSJEC();
  k_jet_l5gluon_jec=jet.L5GluonJEC();
  k_jet_error_jec=jet.JECUncertainty();
  k_jet_scaled_down_energy=jet.ScaledDownEnergy();
  k_jet_scaled_up_energy=jet.ScaledUpEnergy();
  k_jet_scaled_down_pt=jet.ScaledDownPt();
  k_jet_scaled_up_pt=jet.ScaledUpPt();
  k_jet_smeared_down_energy=jet.SmearedDownEnergy();
  k_jet_smeared_up_energy=jet.SmearedUpEnergy();
  k_jet_smeared_down_pt=jet.SmearedDownPt();
  k_jet_smeared_up_pt=jet.SmearedUpPt();
  k_jet_energy_raw=jet.RawE();
  k_jet_pt_raw = jet.RawPt();

  
}


KJet::~KJet()
{
}

void KJet::Reset()
{
    KParticle::Reset();
    k_jet_passLooseID=false;
    k_jet_passTightID=false;
    k_jet_passpileup_loose=false;
    k_jet_passpileup_medium=false;
    k_jet_passpileup_tight=false;
    k_jet_pileup_flag=0;
    k_jet_pileup_mva=0.;
    k_jet_chargeMult=0;
    k_jet_neutralMult=0;
    k_jet_chargeHadMult=0;
    k_jet_neutralHadMult=0;
    k_jet_muonMult=0;
    k_jet_elMult=0;
    k_jet_phMult=0;
    k_jet_hfemMult=0;
    k_jet_hfhadronMult=0;
    k_jet_SecVertBtag=0.;
    k_jet_TCHPT=0.;
    k_jet_JetProbBtag=0.;
    k_jet_neutralEmEF=0.;
    k_jet_neutralHEF=0.;
    k_jet_chargeEmEF=0.;
    k_jet_chargeHEF=0.;
    k_jet_hfemEF=0.;
    k_jet_hfhadronEF=0.;
    k_jet_chargedmuEF=0.;
    k_jet_muonEF=0.;
    k_jet_electronEF=0.;
    k_jet_photonEF=0.;
    k_jet_partonflavour=0.;
    k_jet_Nconst=0;
    k_jet_closest3Dsep=0.;
    k_jet_closestXYsep=0.;
    k_jet_closestZsep=0.;
    k_jet_bestvertexTrackAssociatedIndex=0.;
    k_jet_bestvertexTrackAssociatedFactor=0.;
    k_jet_l1fastjet_jec=0.;
    k_jet_l2l3res_jec=0.;
    k_jet_l2rel_jec=0.;
    k_jet_l3abs_jec=0.;
    k_jet_l5bottom_jec=0.;
    k_jet_l5charm_jec=0.;
    k_jet_l5uds_jec=0.;
    k_jet_l5gluon_jec=0.;
    k_jet_error_jec=0.;
    k_jet_scaled_down_energy=0.;
    k_jet_scaled_up_energy=0.;
    k_jet_scaled_down_pt=0.;
    k_jet_scaled_up_pt=0.;
    k_jet_smeared_down_energy=0.;
    k_jet_smeared_up_energy=0.;
    k_jet_smeared_down_pt=0.;
    k_jet_smeared_up_pt=0.;
    k_jet_energy_raw=0.;
    k_jet_pt_raw = 0.;


}


//Int_t KJet::GetFlavourTruthLabel() const {
///return m_flavor_truth_label;
//}



KJet& KJet::operator= (const KJet& p)
{
    if (this != &p) {
      KParticle::operator=(p);
      k_jet_passLooseID= p.PassLooseID();
      k_jet_passTightID= p.PassTightID();
      k_jet_passpileup_loose= false;
      k_jet_passpileup_medium= false;
      k_jet_passpileup_tight= false;
      k_jet_pileup_flag=0;
      k_jet_pileup_mva= 0.;
      k_jet_chargeMult=p.ChargedMultiplicity();
      k_jet_neutralMult=p.NeutralMultiplicity();
      k_jet_chargeHadMult=p.ChargedHadronMultiplicity();
      k_jet_neutralHadMult=p.NeutralHadronMultiplicity();
      k_jet_muonMult=p.MuonMultiplicity();
      k_jet_elMult=p.ElectronMultiplicity();
      k_jet_phMult=p.PhotonMultiplicity();
      k_jet_hfemMult=p.HFEMMultiplicity();
      k_jet_hfhadronMult=p.HFHadronMultiplicity();
      k_jet_SecVertBtag=p.CombinedSecVertexBtag() ;
      k_jet_TCHPT=p.PFJetTrackCountingHighPurBTag();
      k_jet_JetProbBtag=p.BtagProb();
      k_jet_neutralEmEF=p.NeutralEMEnergyFraction();
      k_jet_neutralHEF=p.NeutralHadEnergyFraction();
      k_jet_chargeEmEF=p.ChargedEMEnergyFraction();
      k_jet_chargeHEF=p.ChargedHadEnergyFraction();
      k_jet_hfemEF=p.HFEMEnergyFraction();
      k_jet_hfhadronEF=p.HFHadEnergyFraction();
      k_jet_chargedmuEF=p.ChargedMuEnergyFraction();
      k_jet_muonEF=p.MuonEnergyFraction();
      k_jet_electronEF=p.ElectronEnergyFraction();
      k_jet_photonEF=p.PhotonEnergyFraction();
      k_jet_partonflavour=p.PartonFlavour();
      k_jet_Nconst=p.Nconstituents();
      k_jet_closest3Dsep=p.JetRho();
      k_jet_closestXYsep=p.ClosestXYsep();
      k_jet_closestZsep=p.ClosestZsep();
      k_jet_bestvertexTrackAssociatedIndex=p.BestVertexTrackAssociationIndex();
      k_jet_bestvertexTrackAssociatedFactor=p.BestVertexTrackAssociationFactor();
      k_jet_l1fastjet_jec=p.L1FastJetJEC();
      k_jet_l2l3res_jec=p.L2L3ResJEC();
      k_jet_l2rel_jec=p.L2RelJEC();
      k_jet_l3abs_jec=p.L3AbsJEC();
      k_jet_l5bottom_jec=p.L5BottomJEC();
      k_jet_l5charm_jec=p.L5CharmJEC();
      k_jet_l5uds_jec=p.L5UDSJEC();
      k_jet_l5gluon_jec=p.L5GluonJEC();
      k_jet_error_jec=p.JECUncertainty();
      k_jet_scaled_down_energy=p.ScaledDownEnergy();
      k_jet_scaled_up_energy=p.ScaledUpEnergy();
      k_jet_scaled_down_pt=p.ScaledDownPt();
      k_jet_scaled_up_pt=p.ScaledUpPt();
      k_jet_smeared_down_energy=p.SmearedDownEnergy();
      k_jet_smeared_up_energy=p.SmearedUpEnergy();
      k_jet_smeared_down_pt=p.SmearedDownPt();
      k_jet_smeared_up_pt=p.SmearedUpPt();
      k_jet_energy_raw=p.RawE();
      k_jet_pt_raw = p.RawPt();

    }

    return *this;
}


//// POG ID CUTS

void KJet::SetJetPassLooseID(int looseID){

  k_jet_passLooseID = looseID;
}

void KJet::SetJetPassTightID(int tightID){
  
  k_jet_passTightID = tightID;
}

void KJet::SetJetPileupIDLooseWP(bool pass){
  k_jet_passpileup_loose=pass;
}

void KJet::SetJetPileupIDMediumWP(bool pass){
  k_jet_passpileup_medium = pass;
}

void KJet::SetJetPileupIDTightWP(bool pass){
  k_jet_passpileup_tight=pass;
}

void KJet::SetJetPileupIDFlag(int flag){
  k_jet_pileup_flag=flag;
}

void KJet::SetJetPileupIDMVA(double mva){
  k_jet_pileup_mva=mva;
}



//// Multiplicities                                                                                                                                                    
void KJet::SetJetChargedMultiplicity(int chargeMult){
  k_jet_chargeMult = chargeMult;
}

void KJet::SetJetNeutralMultiplicity(int neutralMult){
  k_jet_neutralMult = neutralMult;
}

void KJet::SetJetChargedHadronMultiplicity(int chargeHadMult){
  k_jet_chargeHadMult = chargeHadMult;
}

void KJet::SetJetNeutralHadronMultiplicity(int neutralHadMult){
  k_jet_neutralHadMult = neutralHadMult;
}

void KJet::SetJetMuonMultiplicity(int jetmuonmult){
  k_jet_muonMult = jetmuonmult;
}

void KJet::SetJetElectronMultiplicity(int jetelmult){
  k_jet_elMult = jetelmult;
}

void KJet::SetJetPhotonMultiplicity(int jetphmult){
  k_jet_phMult = jetphmult;
}

void KJet::SetJetHFEMMultiplicity(int jethfemmult){
  k_jet_hfemMult = jethfemmult;
}

void KJet::SetJetHFHadronMultiplicity(int jethfhadmult){
  k_jet_hfhadronMult = jethfhadmult;
}


/// BTAG variables
void KJet::SetJetTrackCountingHighPurBTag(double TCHPT){
  k_jet_TCHPT = TCHPT;
}

void KJet::SetJetJetProbabilityBTag(double JP){
  k_jet_JetProbBtag = JP;
}

void KJet::SetJetSecVertBtag(double svbt){
  k_jet_SecVertBtag = svbt;
}

///Tracking variables
void KJet::SetJetClosestVertexWeightedXYSeparation(double cvxys){
  k_jet_closestXYsep = cvxys;
}

void KJet::SetJetClosestVertexWeightedZSeparation(double cvzs){
  k_jet_closestZsep = cvzs;
}

void KJet::SetJetNConstituents(int jetNconst){
  k_jet_Nconst = jetNconst;
}

void KJet::SetJetClosestVertW3DSep(double cv3ds){
  k_jet_closest3Dsep = cv3ds;
}


void KJet::SetJetBestVertexTrackAssociationIndex(double bvtai){
  k_jet_bestvertexTrackAssociatedIndex=bvtai;
}

void KJet::SetJetBestVertexTrackAssociationFactor(double bvtaf){
  k_jet_bestvertexTrackAssociatedFactor=bvtaf;
}

 
/// Jet energy fractions
void KJet::SetJetNeutralEmEF(double neutEmEF){  
  k_jet_neutralEmEF = neutEmEF;
}

void KJet::SetJetNeutralHEF(double neutHEF){
  k_jet_neutralHEF = neutHEF;
}

void KJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
}

void KJet::SetJetChargedHEF(double chargeHEF){
  k_jet_chargeHEF = chargeHEF;
}

void KJet::SetJetHFEMEnergyFraction(double hfemef){
  k_jet_hfemEF = hfemef;
}

void KJet::SetJetHFHadronEnergyFraction(double hfhef){
  k_jet_hfhadronEF = hfhef;
}

void KJet::SetJetChargedMuEnergyFraction(double cmuef){
  k_jet_chargedmuEF = cmuef;
}

void KJet::SetJetMuonEnergyFraction(double muef){
  k_jet_muonEF = muef;
}

void KJet::SetJetElectronEnergyFraction(double elef){
  k_jet_electronEF= elef;
}

void KJet::SetJetPhotonEnergyFraction(double phef){
  k_jet_photonEF= phef;
}



//flavour
void KJet::SetJetPartonFlavour(int pf){
  k_jet_partonflavour=pf;
}

//ERRORS
void KJet::SetJetRawPt(double rawpt){
  k_jet_pt_raw=rawpt;
}

void KJet::SetJetRawEnergy(double rawe){
  k_jet_energy_raw=rawe;
}
void KJet::SetJetL1FastJetJEC(double L1FastJetJEC){
  k_jet_l1fastjet_jec=L1FastJetJEC;
}
void KJet::SetJetL2L3ResJEC(double L2L3ResJEC){
  k_jet_l2l3res_jec=L2L3ResJEC;
}
void KJet::SetJetL2RelJEC(double JetL2RelJEC){
  k_jet_l2rel_jec=JetL2RelJEC;
}
void KJet::SetJetL3AbsJEC(double JetL3AbsJEC){
  k_jet_l3abs_jec=JetL3AbsJEC;
}

void KJet::SetJetL5BottomJEC(double JetL5BottomJEC){
  k_jet_l5bottom_jec=JetL5BottomJEC;
}

void KJet::SetJetL5CharmJEC(double JetL5CharmJEC){
  k_jet_l5charm_jec=JetL5CharmJEC;
}

void KJet::SetJetL5UDSJEC(double JetL5UDSJEC){
  k_jet_l5uds_jec=JetL5UDSJEC;
}

void KJet::SetJetL5GluonJEC(double JetL5GluonJEC){
  k_jet_l5gluon_jec=JetL5GluonJEC;
}


void KJet::SetJetJECUnc(double jecunc){
  k_jet_error_jec=jecunc;
}
void KJet::SetJetScaledDownEnergy(double jetscaleEdown){
  k_jet_scaled_down_energy=jetscaleEdown;
}
void KJet::SetJetScaledUpEnergy(double jetscaleEup){
  k_jet_scaled_up_energy=jetscaleEup;
}
void KJet::SetJetScaledDownPt(double jetscalePtdown){
  k_jet_scaled_down_pt=jetscalePtdown;
}
void KJet::SetJetScaledUpPt(double jetscalePtup){
  k_jet_scaled_up_pt=jetscalePtup;
}
void KJet::SetJetSmearedDownEnergy(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KJet::SetJetSmearedUpEnergy(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}
void KJet::SetJetSmearedDownPt(double jetsmearPtdown){
  k_jet_smeared_down_pt=jetsmearPtdown;
}
void KJet::SetJetSmearedUpPt(double jetsmearPtup){
  k_jet_smeared_up_pt=jetsmearPtup;
}
