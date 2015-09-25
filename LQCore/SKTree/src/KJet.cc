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
  k_jet_passTightLepVetoID=false;
  k_jet_passpileup_loose=false;
  k_jet_passpileup_medium=false;
  k_jet_passpileup_tight=false;
  k_jet_pileup_mva=0.;
  k_jet_cvsv2= 0.;
  k_jet_chargeEmEF=0.;
  k_jet_partonflavour=0.;
  k_jet_scaled_down_energy=0.;
  k_jet_scaled_up_energy=0.;
  k_jet_smeared_down_energy=0.;
  k_jet_smeared_up_energy=0.;
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
  k_jet_passTightLepVetoID= jet.PassTightLepVetoID();
  k_jet_passpileup_loose= jet.PileupJetIDLoose();
  k_jet_passpileup_medium= jet.PileupJetIDMedium();
  k_jet_passpileup_tight=jet.PileupJetIDTight();
  k_jet_pileup_flag=jet.PileupJetIDFlag();
  k_jet_pileup_mva= jet.PileupJetIDMVA();
  k_jet_cvsv2 = jet.CVSInclV2();
  k_jet_chargeEmEF=jet.ChargedEMEnergyFraction();
  k_jet_partonflavour=jet.PartonFlavour();
  k_jet_error_jec=jet.JECUncertainty();
  k_jet_scaled_down_energy=jet.ScaledDownEnergy();
  k_jet_scaled_up_energy=jet.ScaledUpEnergy();
  k_jet_smeared_down_energy=jet.SmearedDownEnergy();
  k_jet_smeared_up_energy=jet.SmearedUpEnergy();
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
    k_jet_passTightLepVetoID=false;
    k_jet_passpileup_loose=false;
    k_jet_passpileup_medium=false;
    k_jet_passpileup_tight=false;
    k_jet_pileup_flag=0;
    k_jet_pileup_mva=0.;
    k_jet_cvsv2 =0;
    k_jet_chargeEmEF=0.;
    k_jet_partonflavour=0.;
    k_jet_error_jec=0.;
    k_jet_scaled_down_energy=0.;
    k_jet_scaled_up_energy=0.;
    k_jet_smeared_down_energy=0.;
    k_jet_smeared_up_energy=0.;
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
      k_jet_passTightLepVetoID= p.PassTightLepVetoID();
      k_jet_passpileup_loose= p.PileupJetIDLoose();
      k_jet_passpileup_medium= p.PileupJetIDMedium();
      k_jet_passpileup_tight=  p.PileupJetIDTight();
      k_jet_pileup_mva= p.PileupJetIDMVA();
      k_jet_cvsv2 =p.CVSInclV2();
      k_jet_chargeEmEF=p.ChargedEMEnergyFraction();
      k_jet_partonflavour=p.PartonFlavour();
      k_jet_error_jec=p.JECUncertainty();
      k_jet_scaled_down_energy=p.ScaledDownEnergy();
      k_jet_scaled_up_energy=p.ScaledUpEnergy();
      k_jet_smeared_down_energy=p.SmearedDownEnergy();
      k_jet_smeared_up_energy=p.SmearedUpEnergy();
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

void KJet::SetJetPassTightLepVetoID(int tightID){
  k_jet_passTightLepVetoID = tightID;
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

void KJet::SetJetPileupIDMVA(double mva){
  k_jet_pileup_mva=mva;
}



//// Multiplicities                                                                                                                                                    


/// BTAG variables

void KJet::SetCVSInclV2(double btag){
  k_jet_cvsv2 = btag;
}


 
/// Jet energy fractions

void KJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
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

void KJet::SetJetJECUnc(double jecunc){
  k_jet_error_jec=jecunc;
}
void KJet::SetJetScaledDownEnergy(double jetscaleEdown){
  k_jet_scaled_down_energy=jetscaleEdown;
}
void KJet::SetJetScaledUpEnergy(double jetscaleEup){
  k_jet_scaled_up_energy=jetscaleEup;
}

void KJet::SetJetSmearedDownEnergy(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KJet::SetJetSmearedUpEnergy(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}
