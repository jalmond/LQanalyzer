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

  k_jet_passTightID=false;
  k_jet_passTightLepVetoID=false;

  k_jet_csv= -999.;
  k_jet_cc_vs_lt=-999.;
  k_jet_cc_vs_bt=-999.;
  k_jet_deepcc_vs_lt=-999.;
  k_jet_deepcc_vs_bt=-999.;

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
  k_jet_passpileup_loose=false;
  k_jet_passpileup_medium=false;
  k_jet_passpileup_tight=false;
  k_jet_pileup_mva=-999.;
  k_ismcsmeared=false;
  k_l1jetcorr=-999.;
  k_fulljetcorr=-999.;
  k_jetarea=-999.;

}

/**
 * Copy constructor.
 */
KJet::KJet(const KJet& jet) :
    KParticle(jet)
{

  k_jet_passTightID=jet.PassTightID();
  k_jet_passTightLepVetoID=jet.PassTightLepVetoID();

  k_jet_csv= jet.BJetTaggerValue(CSVv2);
  k_jet_deepcsv= jet.BJetTaggerValue(DeepCSV);

  k_jet_cc_vs_lt=jet.CJetTaggerValue(CCvsLT);
  k_jet_cc_vs_bt=jet.CJetTaggerValue(CCvsBT);
  k_jet_deepcc_vs_lt=jet.CJetTaggerValue(DeepCCvsLT);
  k_jet_deepcc_vs_bt=jet.CJetTaggerValue(DeepCCvsBT);

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
  k_jet_passpileup_loose=jet.PileupJetIDLoose();
  k_jet_passpileup_medium=jet.PileupJetIDMedium();
  k_jet_passpileup_tight=jet.PileupJetIDTight();
  k_jet_pileup_mva= jet.PileupJetIDMVA();
  k_ismcsmeared=jet.IsMCSmeared();

  k_l1jetcorr=jet.L1JetCorr();
  k_fulljetcorr=jet.FullJetCorr();
  k_jetarea=jet.JetArea();
}


KJet::~KJet()
{
}

void KJet::Reset()
{
    KParticle::Reset();


    k_jet_passTightID=false;
    k_jet_passTightLepVetoID=false;

    k_jet_csv= -999.;
    k_jet_deepcsv= -999.;
    k_jet_cc_vs_lt=999.;
    k_jet_cc_vs_bt=-999.;
    k_jet_deepcc_vs_lt=999.;
    k_jet_deepcc_vs_bt=-999.;


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
    k_jet_passpileup_loose=false;
    k_jet_passpileup_medium=false;
    k_jet_passpileup_tight=false;
    k_jet_pileup_mva=-999.;
    k_ismcsmeared=false;
    k_l1jetcorr=-999.;
    k_fulljetcorr=-999.;
    k_jetarea=-999.;


}




KJet& KJet::operator= (const KJet& p)
{
    if (this != &p) {
      KParticle::operator=(p);

      k_jet_passTightID=p.PassTightID();
      k_jet_passTightLepVetoID=p.PassTightLepVetoID();

      k_jet_csv= p.BJetTaggerValue(CSVv2);
      k_jet_deepcsv= p.BJetTaggerValue(DeepCSV);
      k_jet_cc_vs_lt=p.BJetTaggerValue(CCvsLT);
      k_jet_cc_vs_bt=p.BJetTaggerValue(CCvsBT);
      k_jet_deepcc_vs_lt=p.BJetTaggerValue(DeepCCvsLT);
      k_jet_deepcc_vs_bt=p.BJetTaggerValue(DeepCCvsBT);

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
      k_jet_passpileup_loose=p.PileupJetIDLoose();
      k_jet_passpileup_medium=p.PileupJetIDMedium();
      k_jet_passpileup_tight=p.PileupJetIDTight();
      k_jet_pileup_mva= p.PileupJetIDMVA();
      k_ismcsmeared=p.IsMCSmeared();
      k_l1jetcorr=p.L1JetCorr();
      k_fulljetcorr=p.FullJetCorr();
      k_jetarea=p.JetArea();
    }

    return *this;
}


bool KJet::PassPileUpMVA(TString puwp){

  bool pass(true);
  //https://indico.cern.ch/event/559594/contributions/2257924/attachments/1317046/1973307/PUID_JMAR_2016_07_26_v1.pdf

  if(puwp== "Tight"){
    if(fabs(this->Eta()) < 2.5){
      if(this->Pt() < 30){
	if(k_jet_pileup_mva < 0.69) pass=false;
      }
      else {
	if(k_jet_pileup_mva < 0.86) pass=false;
      }
    }
    else if(fabs(this->Eta()) < 2.75){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.35) pass=false;
      }
      else {
	if(k_jet_pileup_mva < -0.1) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 3.0){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.26) pass=false;
      }   
      else {
        if(k_jet_pileup_mva < -0.05) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 5.){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.21) pass=false;
      }   
      else {
        if(k_jet_pileup_mva < -0.01) pass=false;
      }
    }
  }
  else  if(puwp== "Medium"){
    if(fabs(this->Eta()) < 2.5){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < 0.18) pass=false;
      }
      else {
        if(k_jet_pileup_mva < 0.61) pass=false;
      }
    }
    else if(fabs(this->Eta()) < 2.75){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.55) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.35) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 3.0){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.42) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.23) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 5.){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.36) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.17) pass=false;
      }
    }
  }

  else  if(puwp== "Loose"){
    if(fabs(this->Eta()) < 2.5){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.97) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.89) pass=false;
      }
    }
    else if(fabs(this->Eta()) < 2.75){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.68) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.52) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 3.0){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.53) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.38) pass=false;
      }
    }

    else if(fabs(this->Eta()) < 5.){
      if(this->Pt() < 30){
        if(k_jet_pileup_mva < -0.47) pass=false;
      }
      else {
        if(k_jet_pileup_mva < -0.30) pass=false;
      }
    }
  }
  else return true;
  /// if wring string is input the function returns false


  return pass;
}
    



double KJet::BJetTaggerValue(Tagger tag) const{
  if(tag == CSVv2) return k_jet_csv;
  else if(tag == DeepCSV) return k_jet_deepcsv;
  else if (tag == CCvsLT) return k_jet_cc_vs_lt;
  else if (tag == CCvsBT) return k_jet_cc_vs_bt;
  else if (tag == DeepCCvsLT) return k_jet_deepcc_vs_lt;
  else if (tag == DeepCCvsBT) return k_jet_deepcc_vs_bt;
  return -999.;
}


double KJet::CJetTaggerValue(Tagger tag) const{
  if (tag == CCvsLT) return k_jet_cc_vs_lt;
  else if (tag == CCvsBT) return k_jet_cc_vs_bt;
  else if (tag == DeepCCvsLT) return k_jet_deepcc_vs_lt;
  else if (tag == DeepCCvsBT) return k_jet_deepcc_vs_bt;
  return -999.;
}

//// POG ID CUTS

void KJet::SetL1JetCorr(double corr){
  k_l1jetcorr=corr;
}

void KJet::SetFullJetCorr(double corr){
  k_fulljetcorr=corr;
}

void KJet::SetJetArea(double area){
  k_jetarea=area;
}


void KJet::SetIsMCSmeared(bool issmeared){
  k_ismcsmeared = issmeared;
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
/// BTAG variables


void KJet::SetBTagInfo(Tagger tag, double value){
  if(tag == CSVv2)       k_jet_csv = value;
  else if(tag == DeepCSV)   k_jet_deepcsv = value;

}
 
void KJet::SetCTagInfo(Tagger tag, double value){
  if (tag == CCvsLT)  k_jet_cc_vs_lt = value;
  else if (tag == CCvsBT)  k_jet_cc_vs_bt = value;
  else if (tag == DeepCCvsLT)  k_jet_deepcc_vs_lt = value;
  else if (tag == DeepCCvsBT)  k_jet_deepcc_vs_bt = value;

}

/// Jet energy fractions

void KJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
}

void KJet::SetJetNeutralEmEF(double neutralEmEF){
  k_jet_neutralEmEF = neutralEmEF;
}

void KJet::SetJetChargedHadEF(double chargeHadEF){
  k_jet_chargeHadEF = chargeHadEF;
}

void KJet::SetJetNeutralHadEF(double neutralHadEF){
  k_jet_neutralHadEF = neutralHadEF;
}


void KJet::SetJetChargedMultiplicity(double chargeMultiplicity){
  k_jet_chargeMultiplicity = chargeMultiplicity;
}

void KJet::SetJetNeutralMultiplicity(double neutralMultiplicity){
  k_jet_neutralMultiplicity = neutralMultiplicity;
}

void KJet::SetJetMass(double mass){
  k_jet_mass = mass;
}



//flavour
void KJet::SetJetPartonFlavour(int pf){
  k_jet_partonflavour=pf;
}

void KJet::SetJetHadronFlavour(int hf){
  k_jet_hadronflavour=hf;
}


void KJet::SetJetPartonPdgId(int pdgid){
  k_jet_partonpdgid=pdgid;
}


void KJet::SetJetScaledDownEnergy(double jetscaleEdown){
  k_jet_scaled_down_energy=jetscaleEdown;
}
void KJet::SetJetScaledUpEnergy(double jetscaleEup){
  k_jet_scaled_up_energy=jetscaleEup;
}

void KJet::SetSmearedResDown(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KJet::SetSmearedResUp(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}

void KJet::SetSmearedRes(double jetsmearE){
  k_jet_smeared_energy=jetsmearE;
}


