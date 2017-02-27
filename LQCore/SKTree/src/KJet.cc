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
  k_jet_energy_raw=-999.;
  k_jet_pt_raw=-999.;
  k_jet_csv2= -999.;
  k_jet_cmva2 = -999.;
  k_jet_jetprobbjet= -999.;
  k_jet_cc_vs_lt=-999.;
  k_jet_cc_vs_bt=-999.;
  k_vtx_mass= -999.;
  k_vtx_3dval= -999.;
  k_vtx_3dsig= -999.;
  k_vtx_ntrack= -999;
  k_jet_chargeEmEF=-999.;
  k_jet_partonflavour=-999;
  k_jet_hadronflavour=-999;
  k_jet_partonpdgid=-999;
  k_jet_error_jec=-999.;
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
}

/**
 * Copy constructor.
 */
KJet::KJet(const KJet& jet) :
    KParticle(jet)
{

  k_jet_passLooseID=jet.PassLooseID();
  k_jet_passTightID=jet.PassTightID();
  k_jet_passTightLepVetoID=jet.PassTightLepVetoID();
  k_jet_energy_raw=jet.RawE();
  k_jet_pt_raw=jet.RawPt();
  k_jet_csv2= jet.BJetTaggerValue(CSVv2);
  k_jet_cmva2= jet.BJetTaggerValue(cMVAv2);
  k_jet_jetprobbjet = jet.BJetTaggerValue(JETPROB);
  k_jet_cc_vs_lt=jet.BJetTaggerValue(CCvsLT);
  k_jet_cc_vs_bt=jet.BJetTaggerValue(CCvsBT);

  k_vtx_mass= jet.VtxMass();
  k_vtx_3dval= jet.Vtx3DVal();
  k_vtx_3dsig= jet.Vtx3DSig();
  k_vtx_ntrack= jet.VtxNtrack();
  k_jet_chargeEmEF=jet.ChargedEMEnergyFraction();
  k_jet_partonflavour=jet.PartonFlavour();
  k_jet_hadronflavour= jet.HadronFlavour();
  k_jet_partonpdgid= jet.PartonPdgId();
  k_jet_error_jec= jet.JECUncertainty();
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
    k_jet_energy_raw=-999.;
    k_jet_pt_raw=-999.;
    k_jet_csv2= -999.;
    k_jet_cmva2= -999.;
    k_jet_jetprobbjet = -999.;
    k_jet_cc_vs_lt=999.;
    k_jet_cc_vs_bt=-999.;


    k_vtx_mass= -999.;
    k_vtx_3dval= -999.;
    k_vtx_3dsig= -999.;
    k_vtx_ntrack= -999;
    k_jet_chargeEmEF=-999.;
    k_jet_partonflavour=-999;
    k_jet_hadronflavour=-999;
    k_jet_partonpdgid=-999;
    k_jet_error_jec=-999.;
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
}




KJet& KJet::operator= (const KJet& p)
{
    if (this != &p) {
      KParticle::operator=(p);
      k_jet_passLooseID=p.PassLooseID();
      k_jet_passTightID=p.PassTightID();
      k_jet_passTightLepVetoID=p.PassTightLepVetoID();
      k_jet_energy_raw=p.RawE();
      k_jet_pt_raw=p.RawPt();
      k_jet_csv2= p.BJetTaggerValue(CSVv2);
      k_jet_cmva2= p.BJetTaggerValue(cMVAv2);
      k_jet_jetprobbjet =p.BJetTaggerValue(JETPROB);
      k_jet_cc_vs_lt=p.BJetTaggerValue(CCvsLT);
      k_jet_cc_vs_bt=p.BJetTaggerValue(CCvsBT);

      k_vtx_mass= p.VtxMass();
      k_vtx_3dval= p.Vtx3DVal();
      k_vtx_3dsig= p.Vtx3DSig();
      k_vtx_ntrack= p.VtxNtrack();
      k_jet_chargeEmEF=p.ChargedEMEnergyFraction();
      k_jet_partonflavour=p.PartonFlavour();
      k_jet_hadronflavour= p.HadronFlavour();
      k_jet_partonpdgid= p.PartonPdgId();
      k_jet_error_jec= p.JECUncertainty();
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
  if(tag == CSVv2) return k_jet_csv2;
  else if(tag == cMVAv2) return k_jet_cmva2;
  else if(tag == JETPROB) return k_jet_jetprobbjet;
  else if (tag == CCvsLT) return k_jet_cc_vs_lt;
  else if (tag == CCvsBT) return k_jet_cc_vs_bt;
  return -999.;
}

//// POG ID CUTS

void KJet::SetIsMCSmeared(bool issmeared){
  k_ismcsmeared = issmeared;
}

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
/// BTAG variables


void KJet::SetBTagInfo(Tagger tag, double value){
  if(tag == CSVv2)       k_jet_csv2 = value;
  else if(tag == cMVAv2)      k_jet_cmva2 = value;
  else if(tag == JETPROB)    k_jet_jetprobbjet = value;
  else if (tag == CCvsLT)  k_jet_cc_vs_lt = value;
  else if (tag == CCvsBT)  k_jet_cc_vs_bt = value;
}
 
void KJet::SetCTagInfo(Tagger tag, double value){
  if (tag == CCvsLT)  k_jet_cc_vs_lt = value;
  else if (tag == CCvsBT)  k_jet_cc_vs_bt = value;
}

/// Jet energy fractions

void KJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
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

void KJet::SetSmearedResDown(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KJet::SetSmearedResUp(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}

void KJet::SetSmearedRes(double jetsmearE){
  k_jet_smeared_energy=jetsmearE;
}


void KJet::SetVtxMass(double mass){
  k_vtx_mass = mass;;
}

void KJet::SetVtx3DVal(double val){
  k_vtx_3dval = val;
}

void KJet::SetVtx3DSig(double sig){
  k_vtx_3dsig = sig;;
}

void KJet::SetVtxNTracks(int ntrk){
  k_vtx_ntrack = ntrk;
}
