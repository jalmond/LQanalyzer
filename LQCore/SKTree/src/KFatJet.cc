#include "KFatJet.h"

#include <iomanip>
#include <iostream>

#include <map>
#include <cmath>



using namespace std;
using namespace snu;

ClassImp(KFatJet)

/**
 *Default constructor.
 */
KFatJet::KFatJet() :
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

  k_fatjet_tau1=-999.;
  k_fatjet_tau2=-999.;
  k_fatjet_tau3=-999.;
  k_fatjet_prunedmass=-999.;
  k_fatjet_softdropmass=-999.;
  k_fatjet_puppi_tau1=-999.;
  k_fatjet_puppi_tau2=-999.;
  k_fatjet_puppi_tau3=-999.;
  k_fatjet_puppi_pt=-999.;
  k_fatjet_puppi_eta=-999.;
  k_fatjet_puppi_phi=-999.;
  k_fatjet_puppi_m=-999.;
  k_fatl1jetcorr=-999.;
  k_fatl2jetcorr=-999.;
  k_fatl3jetcorr=-999.;
  k_fatl2l3resjetcorr=-999.;
  k_fatjetarea=-999.;

}

/**
 * Copy constructor.
 */
KFatJet::KFatJet(const KFatJet& jet) :
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
  
  k_fatjet_tau1=jet.Tau1();
  k_fatjet_tau2=jet.Tau2();
  k_fatjet_tau3=jet.Tau3();
  k_fatjet_prunedmass=jet.PrunedMass();
  k_fatjet_softdropmass=jet.SoftDropMass();
  k_fatjet_puppi_tau1=jet.PuppiTau1();
  k_fatjet_puppi_tau2=jet.PuppiTau2();
  k_fatjet_puppi_tau3=jet.PuppiTau3();
  k_fatjet_puppi_pt=jet.PuppiPt();
  k_fatjet_puppi_eta=jet.PuppiEta();
  k_fatjet_puppi_phi=jet.PuppiPhi();
  k_fatjet_puppi_m=jet.PuppiM();

  k_fatl1jetcorr=jet.L1JetCorr();
  k_fatl2jetcorr=jet.L2JetCorr();
  k_fatl3jetcorr=jet.L3JetCorr();
  k_fatl2l3resjetcorr=jet.L2L3ResJetCorr();
  k_fatjetarea=jet.JetArea();
}


KFatJet::~KFatJet()
{
}

void KFatJet::Reset()
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

    k_fatjet_tau1=-999.;
    k_fatjet_tau2=-999.;
    k_fatjet_tau3=-999.;
    k_fatjet_prunedmass=-999.;
    k_fatjet_softdropmass=-999.;
    k_fatjet_puppi_tau1=-999.;
    k_fatjet_puppi_tau2=-999.;
    k_fatjet_puppi_tau3=-999.;
    k_fatjet_puppi_pt=-999.;
    k_fatjet_puppi_eta=-999.;
    k_fatjet_puppi_phi=-999.;
    k_fatjet_puppi_m=-999.;
    k_fatl1jetcorr=-999.;
    k_fatl2jetcorr=-999.;
    k_fatl3jetcorr=-999.;
    k_fatl2l3resjetcorr=-999.;
    k_fatjetarea=-999.;

}




KFatJet& KFatJet::operator= (const KFatJet& p)
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
      k_fatjet_tau1=p.Tau1();
      k_fatjet_tau2=p.Tau2();
      k_fatjet_tau3=p.Tau3();
      k_fatjet_prunedmass=p.PrunedMass();
      k_fatjet_softdropmass=p.SoftDropMass();
      k_fatjet_puppi_tau1=p.PuppiTau1();
      k_fatjet_puppi_tau2=p.PuppiTau2();
      k_fatjet_puppi_tau3=p.PuppiTau3();
      k_fatjet_puppi_pt=p.PuppiPt();
      k_fatjet_puppi_eta=p.PuppiEta();
      k_fatjet_puppi_phi=p.PuppiPhi();
      k_fatjet_puppi_m=p.PuppiM();
      k_fatl1jetcorr=p.L1JetCorr();
      k_fatl2jetcorr=p.L2JetCorr();
      k_fatl3jetcorr=p.L3JetCorr();
      k_fatl2l3resjetcorr=p.L2L3ResJetCorr();
      k_fatjetarea=p.JetArea();

    }

    return *this;
}



double KFatJet::BJetTaggerValue(Tagger tag) const{
  if(tag == CSVv2) return k_jet_csv2;
  else if(tag == cMVAv2) return k_jet_cmva2;
  else if(tag == JETPROB) return k_jet_jetprobbjet;
  else if (tag == CCvsLT) return k_jet_cc_vs_lt;
  else if (tag == CCvsBT) return k_jet_cc_vs_bt;
  return -999.;
}

//// POG ID CUTS

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
  k_fatl1jetcorr=corr;
}

void KFatJet::SetL2JetCorr(double corr){
  k_fatl2jetcorr=corr;
}
void KFatJet::SetL3JetCorr(double corr){
  k_fatl3jetcorr=corr;
}
void KFatJet::SetL2L3ResJetCorr(double corr){
  k_fatl2l3resjetcorr=corr;
}

void KFatJet::SetJetArea(double area){
  k_fatjetarea=area;
}


void KFatJet::SetJetPassLooseID(int looseID){

  k_jet_passLooseID = looseID;
}

void KFatJet::SetJetPassTightID(int tightID){
  
  k_jet_passTightID = tightID;
}

void KFatJet::SetJetPassTightLepVetoID(int tightID){
  k_jet_passTightLepVetoID = tightID;
}

void KFatJet::SetJetPileupIDLooseWP(bool pass){
  k_jet_passpileup_loose=pass;
}

void KFatJet::SetJetPileupIDMediumWP(bool pass){
  k_jet_passpileup_medium = pass;
}

void KFatJet::SetJetPileupIDTightWP(bool pass){
  k_jet_passpileup_tight=pass;
}

void KFatJet::SetJetPileupIDMVA(double mva){
  k_jet_pileup_mva=mva;
}
/// BTAG variables


void KFatJet::SetBTagInfo(Tagger tag, double value){
  if(tag == CSVv2)       k_jet_csv2 = value;
  else if(tag == cMVAv2)      k_jet_cmva2 = value;
  else if(tag == JETPROB)    k_jet_jetprobbjet = value;
  else if (tag == CCvsLT)  k_jet_cc_vs_lt = value;
  else if (tag == CCvsBT)  k_jet_cc_vs_bt = value;
}
 
void KFatJet::SetCTagInfo(Tagger tag, double value){
  if (tag == CCvsLT)  k_jet_cc_vs_lt = value;
  else if (tag == CCvsBT)  k_jet_cc_vs_bt = value;
}

/// Jet energy fractions

void KFatJet::SetJetChargedEmEF(double chargeEmEF){
  k_jet_chargeEmEF = chargeEmEF;
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


//ERRORS
void KFatJet::SetJetRawPt(double rawpt){
  k_jet_pt_raw=rawpt;
}

void KFatJet::SetJetRawEnergy(double rawe){
  k_jet_energy_raw=rawe;
}

void KFatJet::SetJetJECUnc(double jecunc){
  k_jet_error_jec=jecunc;
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


void KFatJet::SetVtxMass(double mass){
  k_vtx_mass = mass;;
}

void KFatJet::SetVtx3DVal(double val){
  k_vtx_3dval = val;
}

void KFatJet::SetVtx3DSig(double sig){
  k_vtx_3dsig = sig;;
}

void KFatJet::SetVtxNTracks(int ntrk){
  k_vtx_ntrack = ntrk;
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

void KFatJet::SetPrunedMass(double pmass){

  k_fatjet_prunedmass=pmass;
}
void KFatJet::SetSoftDropMass(double smass){

  k_fatjet_softdropmass=smass;
}


void KFatJet::SetPuppiTau1(double tau1){
  k_fatjet_puppi_tau1=tau1;
}

void KFatJet::SetPuppiTau2(double tau2){
  k_fatjet_puppi_tau2=tau2;
}

void KFatJet::SetPuppiTau3(double tau3){
  k_fatjet_puppi_tau3=tau3;
}

void KFatJet::SetPuppiPt(double pt){
  k_fatjet_puppi_pt=pt;
}
void KFatJet::SetPuppiEta(double eta){
  k_fatjet_puppi_eta=eta;
}


void KFatJet::SetPuppiPhi(double phi){
  k_fatjet_puppi_phi=phi;
}


void KFatJet::SetPuppiM(double m){
  k_fatjet_puppi_m=m;
}

