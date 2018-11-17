#include "KFatJet.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KFatJet)

/**
 *Default constructor.
 */
KFatJet::KFatJet() :
KParticle()
{

  k_jet_passTightID=false;
  k_jet_passTightLepVetoID=false;

  k_jet_csv= -999.;

  k_jet_chargeEmEF=-999.;
  k_jet_neutralEmEF=-999.;
  k_jet_chargeHadEF=-999.;
  k_jet_neutralHadEF=-999.;
  k_jet_chargeMultiplicity=-999.;
  k_jet_neutralMultiplicity=-999.;

  k_jet_mass = -999.;

  k_jet_partonflavour=-999;
  k_jet_hadronflavour=-999;
  k_jet_partonpdgid=-999;
  k_jet_scaled_down_energy=-999.;
  k_jet_scaled_up_energy=-999.;
  k_jet_smeared_down_energy=-999.;
  k_jet_smeared_up_energy=-999.;
  k_jet_smeared_energy=-999.;

  k_ismcsmeared=false;
  k_l1jetcorr=-999.;
  k_fulljetcorr=-999.;
  k_jetarea=-999.;

  k_fatjet_tau1=-999.;
  k_fatjet_tau2=-999.;
  k_fatjet_tau3=-999.;
  k_fatjet_tau4=-999.;
  k_fatjet_prunedmass=-999.;
  k_fatjet_softdropmass=-999.;


}

/**
 * Copy constructor.
 */
KFatJet::KFatJet(const KFatJet& jet) :
    KParticle(jet)
{

  k_jet_passTightID=jet.PassTightID();
  k_jet_passTightLepVetoID=jet.PassTightLepVetoID();

  k_jet_csv= jet.BJetTaggerValue(CSVv2);

  k_jet_chargeEmEF=jet.ChargedEMEnergyFraction();
  k_jet_neutralEmEF=jet.NeutralEMEnergyFraction();
  k_jet_chargeHadEF=jet.ChargedHADEnergyFraction();
  k_jet_neutralHadEF=jet.NeutralHADEnergyFraction();
  k_jet_chargeMultiplicity=jet.ChargedMultiplicity();
  k_jet_neutralMultiplicity=jet.NeutralMultiplicity();
  k_jet_mass = jet.Mass();


  k_jet_partonflavour=jet.PartonFlavour();
  k_jet_hadronflavour= jet.HadronFlavour();
  k_jet_partonpdgid= jet.PartonPdgId();
  k_jet_scaled_down_energy= jet.ScaledDownEnergy();
  k_jet_scaled_up_energy=jet.ScaledUpEnergy();
  k_jet_smeared_down_energy= jet.SmearedResDown();
  k_jet_smeared_up_energy= jet.SmearedResUp();
  k_jet_smeared_energy= jet.SmearedRes();
  k_ismcsmeared=jet.IsMCSmeared();

  k_l1jetcorr=jet.L1JetCorr();
  k_fulljetcorr=jet.FullJetCorr();
  k_jetarea=jet.JetArea();

  k_fatjet_tau1=jet.Tau1();
  k_fatjet_tau2=jet.Tau2();
  k_fatjet_tau3=jet.Tau3();
  k_fatjet_tau4=jet.Tau4();
  k_fatjet_prunedmass=jet.PrunedMass();
  k_fatjet_softdropmass=jet.SoftDropMass();

}


KFatJet::~KFatJet()
{
}

void KFatJet::Reset()
{
    KParticle::Reset();


    k_jet_passTightID=false;
    k_jet_passTightLepVetoID=false;

    k_jet_csv= -999.;


    k_jet_chargeEmEF=-999.;
    k_jet_neutralEmEF=-999.;
    k_jet_chargeHadEF=-999.;
    k_jet_neutralHadEF=-999.;
    k_jet_chargeMultiplicity=-999.;
    k_jet_neutralMultiplicity=-999.;
    k_jet_mass = -999.;


    k_jet_partonflavour=-999;
    k_jet_hadronflavour=-999;
    k_jet_partonpdgid=-999;
    k_jet_scaled_down_energy=-999.;
    k_jet_scaled_up_energy=-999.;
    k_jet_smeared_down_energy=-999.;
    k_jet_smeared_up_energy=-999.;
    k_jet_smeared_energy=-999.;
    k_ismcsmeared=false;
    k_l1jetcorr=-999.;
    k_fulljetcorr=-999.;
    k_jetarea=-999.;


    k_fatjet_tau1=-999.;
    k_fatjet_tau2=-999.;
    k_fatjet_tau3=-999.;
    k_fatjet_tau4=-999.;
    k_fatjet_prunedmass=-999.;
    k_fatjet_softdropmass=-999.;


}




KFatJet& KFatJet::operator= (const KFatJet& p)
{
    if (this != &p) {
      KParticle::operator=(p);

      k_jet_passTightID=p.PassTightID();
      k_jet_passTightLepVetoID=p.PassTightLepVetoID();

      k_jet_csv= p.BJetTaggerValue(CSVv2);

      k_jet_chargeEmEF=p.ChargedEMEnergyFraction();
      k_jet_neutralEmEF=p.NeutralEMEnergyFraction();
      k_jet_chargeHadEF=p.ChargedHADEnergyFraction();
      k_jet_neutralHadEF=p.NeutralHADEnergyFraction();
      k_jet_chargeMultiplicity=p.ChargedMultiplicity();
      k_jet_neutralMultiplicity=p.NeutralMultiplicity();

      k_jet_mass = p.Mass();

      k_jet_partonflavour=p.PartonFlavour();
      k_jet_hadronflavour= p.HadronFlavour();
      k_jet_partonpdgid= p.PartonPdgId();
      k_jet_scaled_down_energy= p.ScaledDownEnergy();
      k_jet_scaled_up_energy=p.ScaledUpEnergy();
      k_jet_smeared_down_energy= p.SmearedResDown();
      k_jet_smeared_up_energy= p.SmearedResUp();
      k_jet_smeared_energy= p.SmearedRes();
      k_ismcsmeared=p.IsMCSmeared();
      k_l1jetcorr=p.L1JetCorr();
      k_fulljetcorr=p.FullJetCorr();
      k_jetarea=p.JetArea();
      k_fatjet_tau1=p.Tau1();
      k_fatjet_tau2=p.Tau2();
      k_fatjet_tau3=p.Tau3();
      k_fatjet_prunedmass=p.PrunedMass();
      k_fatjet_softdropmass=p.SoftDropMass();

    }

    return *this;
}




double KFatJet::BJetTaggerValue(Tagger tag) const{
  if(tag == CSVv2) return k_jet_csv;

  return -999.;
}




float KFatJet::GetSmearedMassRes(int sys) const {
  //const double smear = CLHEP::RandGaussQ::shoot(rng_);
  float jet_resolution = 8.01;
  float fsys = 1.;
  if(sys==0) fsys=0.;
  if(sys < 0) fsys=-1;

  float jer_sf = 1.23 + fsys*0.18;
  double sigma = jet_resolution * std::sqrt(jer_sf * jer_sf - 1);

  double twopi = 8.0 * atan(1.0); // preferable to using M_PI
  double x =   rand()%10 , mu = 0.;
  double y = (1.0 / (sigma * sqrt(twopi))) *
    exp(-(x - mu)*(x - mu) / (2.0 * sigma * sigma));

  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetResolution#Smearing_procedures
  //https://github.com/cms-sw/cmssw/blob/CMSSW_8_0_25/PhysicsTools/PatUtils/interface/SmearedJetProducerT.h#L250

  return 1.+ y;

}


void KFatJet::SetL1JetCorr(double corr){
  k_l1jetcorr=corr;
}

void KFatJet::SetFullJetCorr(double corr){
  k_fulljetcorr=corr;
}

void KFatJet::SetJetArea(double area){
  k_jetarea=area;
}


void KFatJet::SetIsMCSmeared(bool issmeared){
  k_ismcsmeared = issmeared;
}

void KFatJet::SetJetPassTightID(int tightID){
  
  k_jet_passTightID = tightID;
}

void KFatJet::SetJetPassTightLepVetoID(int tightID){
  k_jet_passTightLepVetoID = tightID;
}


/// BTAG variables


void KFatJet::SetBTagInfo(Tagger tag, double value){
  if(tag == CSVv2)       k_jet_csv = value;

}

/// FatJet energy fractions

void KFatJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
}

void KFatJet::SetJetNeutralEmEF(double neutralEmEF){
  k_jet_neutralEmEF = neutralEmEF;
}

void KFatJet::SetJetChargedHadEF(double chargeHadEF){
  k_jet_chargeHadEF = chargeHadEF;
}

void KFatJet::SetJetNeutralHadEF(double neutralHadEF){
  k_jet_neutralHadEF = neutralHadEF;
}


void KFatJet::SetJetChargedMultiplicity(double chargeMultiplicity){
  k_jet_chargeMultiplicity = chargeMultiplicity;
}

void KFatJet::SetJetNeutralMultiplicity(double neutralMultiplicity){
  k_jet_neutralMultiplicity = neutralMultiplicity;
}

void KFatJet::SetJetMass(double mass){
  k_jet_mass = mass;
}



//flavour
void KFatJet::SetJetPartonFlavour(int pf){
  k_jet_partonflavour=pf;
}

void KFatJet::SetJetHadronFlavour(int hf){
  k_jet_hadronflavour=hf;
}


void KFatJet::SetJetPartonPdgId(int pdgid){
  k_jet_partonpdgid=pdgid;
}


void KFatJet::SetJetScaledDownEnergy(double jetscaleEdown){
  k_jet_scaled_down_energy=jetscaleEdown;
}
void KFatJet::SetJetScaledUpEnergy(double jetscaleEup){
  k_jet_scaled_up_energy=jetscaleEup;
}

void KFatJet::SetSmearedResDown(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KFatJet::SetSmearedResUp(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}

void KFatJet::SetSmearedRes(double jetsmearE){
  k_jet_smeared_energy=jetsmearE;
}



void KFatJet::SetTau1(double tau1){
  k_fatjet_tau1=tau1;
}

void KFatJet::SetTau2(double tau2){
  k_fatjet_tau2=tau2;
}

void KFatJet::SetTau3(double tau3){
  k_fatjet_tau3=tau3;
}
void KFatJet::SetTau4(double tau4){
  k_fatjet_tau4=tau4;
}

void KFatJet::SetSoftDropMass(double smass){

  k_fatjet_softdropmass=smass;
}
