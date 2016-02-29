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
  k_jet_energy_raw=0.;
  k_jet_pt_raw=0.;
  k_jet_csv2= 0.;
  k_jet_cmva2 = 0.;
  k_jet_jetprobbjet= 0.;
  k_vtx_mass= 0.;
  k_vtx_3dval= 0.;
  k_vtx_3dsig= 0.;
  k_vtx_ntrack= 0;
  k_jet_chargeEmEF=0.;
  k_jet_partonflavour=0;
  k_jet_hadronflavour=0;
  k_jet_partonpdgid=0;
  k_jet_error_jec=0.;
  k_jet_scaled_down_energy=0.;
  k_jet_scaled_up_energy=0.;
  k_jet_smeared_down_energy=0.;
  k_jet_smeared_up_energy=0.;
  k_jet_smeared_energy=0.;
  k_jet_passpileup_loose=false;
  k_jet_passpileup_medium=false;
  k_jet_passpileup_tight=false;
  k_jet_pileup_mva=0.;
  
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
  k_jet_smeared_down_energy= jet.SmearedDownEnergy();
  k_jet_smeared_up_energy= jet.SmearedUpEnergy();
  k_jet_smeared_energy= jet.SmearedEnergy();
  k_jet_passpileup_loose=jet.PileupJetIDLoose();
  k_jet_passpileup_medium=jet.PileupJetIDMedium();
  k_jet_passpileup_tight=jet.PileupJetIDTight();
  k_jet_pileup_mva= jet.PileupJetIDMVA();

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
    k_jet_energy_raw=0.;
    k_jet_pt_raw=0.;
    k_jet_csv2= 0.;
    k_jet_cmva2= 0.;
    k_jet_jetprobbjet = 0.;


    k_vtx_mass= 0.;
    k_vtx_3dval= 0.;
    k_vtx_3dsig= 0.;
    k_vtx_ntrack= 0;
    k_jet_chargeEmEF=0.;
    k_jet_partonflavour=0;
    k_jet_hadronflavour=0;
    k_jet_partonpdgid=0;
    k_jet_error_jec=0.;
    k_jet_scaled_down_energy=0.;
    k_jet_scaled_up_energy=0.;
    k_jet_smeared_down_energy=0.;
    k_jet_smeared_up_energy=0.;
    k_jet_smeared_energy=0.;
    k_jet_passpileup_loose=false;
    k_jet_passpileup_medium=false;
    k_jet_passpileup_tight=false;
    k_jet_pileup_mva=0.;

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
      k_jet_smeared_down_energy= p.SmearedDownEnergy();
      k_jet_smeared_up_energy= p.SmearedUpEnergy();
      k_jet_smeared_energy= p.SmearedEnergy();
      k_jet_passpileup_loose=p.PileupJetIDLoose();
      k_jet_passpileup_medium=p.PileupJetIDMedium();
      k_jet_passpileup_tight=p.PileupJetIDTight();
      k_jet_pileup_mva= p.PileupJetIDMVA();
      
    }

    return *this;
}

float KJet::scaleFactor(Tagger tag, WORKING_POINT cutType, syst_dir syst) const {
  if (std::abs(this->Eta()) > 2.4 ) return -1; // reject jets out of eta range
  //based on https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation74X50ns
  const double pt = this->Pt();
  if ( pt < 20 || pt > 1000 ) return -1;

  /// currently only CSVv2 scalefactors are coded

  if(tag==CSVv2){
    int flav = 2;
    if (std::abs(this->PartonFlavour()) == 5) flav = 0;
    if (std::abs(this->PartonFlavour()) == 4) flav = 1;
  
    if (cutType == 0 && syst == 0 && flav == 1 && pt >= 30 && pt < 670 ) return 0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))));
    if (cutType == 0 && syst == 0 && flav == 0 && pt >= 30 && pt < 670 ) return 0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))));
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 30 && pt < 50 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.044655226171016693);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 50 && pt < 70 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.030660966411232948);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 70 && pt < 100 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.048987984657287598);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 100 && pt < 140 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.041866477578878403);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 140 && pt < 200 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.058439217507839203);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 200 && pt < 300 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.079142965376377106);
    if (cutType == 0 && syst == -1 && flav == 1 && pt >= 300 && pt < 670 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.094659518897533417);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 30 && pt < 50 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.022327613085508347);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 50 && pt < 70 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.015330483205616474);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 70 && pt < 100 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.024493992328643799);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 100 && pt < 140 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.020933238789439201);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 140 && pt < 200 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.029219608753919601);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 200 && pt < 300 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.039571482688188553);
    if (cutType == 0 && syst == -1 && flav == 0 && pt >= 300 && pt < 670 ) return 0.908299+((2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144)))))))-0.047329759448766708);
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 30 && pt < 50 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.044655226171016693;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 50 && pt < 70 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.030660966411232948;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 70 && pt < 100 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.048987984657287598;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 100 && pt < 140 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.041866477578878403;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 140 && pt < 200 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.058439217507839203;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 200 && pt < 300 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.079142965376377106;
    if (cutType == 0 && syst == +1 && flav == 1 && pt >= 300 && pt < 670 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.094659518897533417;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 30 && pt < 50 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.022327613085508347;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 50 && pt < 70 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.015330483205616474;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 70 && pt < 100 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.024493992328643799;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 100 && pt < 140 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.020933238789439201;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 140 && pt < 200 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.029219608753919601;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 200 && pt < 300 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.039571482688188553;
    if (cutType == 0 && syst == +1 && flav == 0 && pt >= 300 && pt < 670 ) return (0.908299+(2.70877e-06*(log(pt+370.144)*(log(pt+370.144)*(3-(-(104.614*log(pt+370.144))))))))+0.047329759448766708;
    if (cutType == 1 && syst == 0 && flav == 1 && pt >= 30 && pt < 670 ) return -(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))));
    if (cutType == 1 && syst == 0 && flav == 0 && pt >= 30 && pt < 670 ) return -(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))));
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 30 && pt < 50 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.063294470310211182);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 50 && pt < 70 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.043231822550296783);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 70 && pt < 100 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.065539278090000153);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 100 && pt < 140 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.04837958887219429);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 140 && pt < 200 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.087311208248138428);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 200 && pt < 300 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.12093273550271988);
    if (cutType == 1 && syst == -1 && flav == 1 && pt >= 300 && pt < 670 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.129528530836105347);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 30 && pt < 50 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.031647235155105591);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 50 && pt < 70 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.021615911275148392);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 70 && pt < 100 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.032769639045000076);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 100 && pt < 140 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.024189794436097145);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 140 && pt < 200 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.043655604124069214);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 200 && pt < 300 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.06046636775135994);
    if (cutType == 1 && syst == -1 && flav == 0 && pt >= 300 && pt < 670 ) return -(0.0443172)+((0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85)))))))-0.064764265418052673);
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 30 && pt < 50 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.063294470310211182;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 50 && pt < 70 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.043231822550296783;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 70 && pt < 100 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.065539278090000153;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 100 && pt < 140 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.04837958887219429;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 140 && pt < 200 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.087311208248138428;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 200 && pt < 300 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.12093273550271988;
    if (cutType == 1 && syst == +1 && flav == 1 && pt >= 300 && pt < 670 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.129528530836105347;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 30 && pt < 50 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.031647235155105591;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 50 && pt < 70 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.021615911275148392;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 70 && pt < 100 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.032769639045000076;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 100 && pt < 140 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.024189794436097145;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 140 && pt < 200 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.043655604124069214;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 200 && pt < 300 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.06046636775135994;
    if (cutType == 1 && syst == +1 && flav == 0 && pt >= 300 && pt < 670 ) return (-(0.0443172)+(0.00496634*(log(pt+1267.85)*(log(pt+1267.85)*(3-(-(0.110428*log(pt+1267.85))))))))+0.064764265418052673;
    if (cutType == 2 && syst == 0 && flav == 1 && pt >= 30 && pt < 670 ) return -(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))));
    if (cutType == 2 && syst == 0 && flav == 0 && pt >= 30 && pt < 670 ) return -(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))));
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 30 && pt < 50 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.063704296946525574);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 50 && pt < 70 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.047892197966575623);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 70 && pt < 100 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.077270857989788055);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 100 && pt < 140 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.062878459692001343);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 140 && pt < 200 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.098963312804698944);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 200 && pt < 300 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.14805065095424652);
    if (cutType == 2 && syst == -1 && flav == 1 && pt >= 300 && pt < 670 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.149765393555164337);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 30 && pt < 50 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.031852148473262787);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 50 && pt < 70 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.023946098983287811);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 70 && pt < 100 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.038635428994894028);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 100 && pt < 140 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.031439229846000671);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 140 && pt < 200 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.049481656402349472);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 200 && pt < 300 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.07402532547712326);
    if (cutType == 2 && syst == -1 && flav == 0 && pt >= 300 && pt < 670 ) return -(5.1345)+((0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1)))))))-0.074882696777582169);
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 30 && pt < 50 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.063704296946525574;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 50 && pt < 70 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.047892197966575623;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 70 && pt < 100 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.077270857989788055;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 100 && pt < 140 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.062878459692001343;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 140 && pt < 200 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.098963312804698944;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 200 && pt < 300 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.14805065095424652;
    if (cutType == 2 && syst == +1 && flav == 1 && pt >= 300 && pt < 670 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.149765393555164337;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 30 && pt < 50 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.031852148473262787;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 50 && pt < 70 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.023946098983287811;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 70 && pt < 100 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.038635428994894028;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 100 && pt < 140 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.031439229846000671;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 140 && pt < 200 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.049481656402349472;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 200 && pt < 300 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.07402532547712326;
    if (cutType == 2 && syst == +1 && flav == 0 && pt >= 300 && pt < 670 ) return (-(5.1345)+(0.000820101*(log(pt+11518.1)*(log(pt+11518.1)*(3-(-(8.66128*log(pt+11518.1))))))))+0.074882696777582169;
    if (cutType == 0 && syst == 0 && flav == 2 && pt >= 20 && pt < 1000 ) return ((1.07278+(0.000535714*pt))+(-1.14886e-06*(pt*pt)))+(7.0636e-10*(pt*(pt*pt)));
    if (cutType == 0 && syst == -1 && flav == 2 && pt >= 20 && pt < 1000 ) return ((1.01637+(0.000265653*pt))+(-4.22531e-07*(pt*pt)))+(2.23396e-10*(pt*(pt*pt)));
    if (cutType == 0 && syst == +1 && flav == 2 && pt >= 20 && pt < 1000 ) return ((1.12921+(0.000804962*pt))+(-1.87332e-06*(pt*pt)))+(1.18864e-09*(pt*(pt*pt)));
    if (cutType == 1 && syst == 0 && flav == 2 && pt >= 20 && pt < 1000 ) return 1.14022;
    if (cutType == 1 && syst == -1 && flav == 2 && pt >= 20 && pt < 1000 ) return 0.94022;
    if (cutType == 1 && syst == +1 && flav == 2 && pt >= 20 && pt < 1000 ) return 1.34022;
    if (cutType == 2 && syst == 0 && flav == 2 && pt >= 20 && pt < 1000 ) return 0.907317;
    if (cutType == 2 && syst == -1 && flav == 2 && pt >= 20 && pt < 1000 ) return 0.557317;
    if (cutType == 2 && syst == +1 && flav == 2 && pt >= 20 && pt < 1000 ) return 1.257317;
    return -1;
  }
  
  return 1.;
}



double KJet::BJetTaggerValue(Tagger tag) const{
  if(tag == CSVv2) return k_jet_csv2;
  if(tag == cMVAv2) return k_jet_cmva2;
  if(tag == JETPROB) return k_jet_jetprobbjet;
  return -999.;
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
/// BTAG variables


void KJet::SetBTagInfo(Tagger tag, float value){
  if(tag == CSVv2)       k_jet_csv2 = value;
  if(tag == cMVAv2)      k_jet_cmva2 = value;
  if(tag == JETPROB)    k_jet_jetprobbjet = value;
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

void KJet::SetJetSmearedDownEnergy(double jetsmearEdown){
  k_jet_smeared_down_energy=jetsmearEdown;
}
void KJet::SetJetSmearedUpEnergy(double jetsmearEup){
  k_jet_smeared_up_energy=jetsmearEup;
}

void KJet::SetJetSmearedEnergy(double jetsmearE){
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
