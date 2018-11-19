#include "ElectronPlots.h"
#include <iostream>

using namespace std;

ElectronPlots::ElectronPlots(TString name) : StdPlots(name) {
  
  TH1::SetDefaultSumw2(true);
  
  map_el["h_sceta"]   = new TH1D("h_sceta"+ name, "", 600,-3. ,3. );
  map_el["h_pt_shifted_up"]   = new TH1D("h_pt_shifted_up"+ name, "", 100,0. ,500. );
  map_el["h_pt_shifted_down"]   = new TH1D("h_pt_shifted_down"+ name, "",100 ,0. ,500. );
  map_el["h_pass_veto"]   = new TH1D("h_pass_veto"+ name, "",2 ,0. ,2. );
  map_el["h_pass_loose"]   = new TH1D("h_pass_loose"+ name, "",2 ,0. ,2. );
  map_el["h_pass_medium"]   = new TH1D("h_pass_medium"+ name, "",2 ,0. ,2. );
  map_el["h_pass_tight"]   = new TH1D("h_pass_tight"+ name, "",2 ,0. ,2. );
  map_el["h_pass_heep"]   = new TH1D("h_pass_heep"+ name, "",2 ,0. ,2. );
  map_el["h_pass_trigmva_medium"]   = new TH1D("h_pass_trigmva_medium"+ name, "",2 ,0. ,2. );
  map_el["h_pass_trigmva_tight"]   = new TH1D("h_pass_trigmva_tight"+ name, "",2 ,0. ,2. );
  map_el["h_mcmatched"]   = new TH1D("h_mcmatched"+ name, "",2 ,0. ,2. );
  map_el["h_mc_isprompt"]   = new TH1D("h_mc_isprompt"+ name, "",2 ,0. ,2. );
  map_el["h_mc_iscf"]   = new TH1D("h_mc_iscf"+ name, "",2 ,0. ,2. );
  map_el["h_mc_isconv"]   = new TH1D("h_mc_isconv"+ name, "",2 ,0. ,2. );
  map_el["h_mc_fromtau"]   = new TH1D("h_mc_fromtau"+ name, "",2 ,0. ,2. );
  map_el["h_mc_pdgid"]   = new TH1D("h_mc_pdgid"+ name, "",200 ,-100. ,100. );
  map_el["h_mother_pdgid"]   = new TH1D("h_mother_pdgid"+ name, "",200 ,-100. ,100. );
  map_el["h_mother_index"]   = new TH1D("h_mother_index"+ name, "",100 ,0. ,100. );
  map_el["h_mc_index"]   = new TH1D("h_mc_index"+ name, "",100 ,0. ,100. );
  map_el["h_particle_type"]   = new TH1D("h_particle_type"+ name, "",10 , 0., 10.);
  map_el["h_mother_type"]   = new TH1D("h_mother_type"+ name, "",10 , 0., 10.);
  map_el["h_gspctfscpix_samecharge"]   = new TH1D("h_gspctfscpix_samecharge"+ name, "",2 ,0. ,2. );
  map_el["h_pass_conv_veto"]   = new TH1D("h_pass_conv_veto"+ name, "",2 ,0. ,2. );
  map_el["h_istrig_mva_valid"]   = new TH1D("h_istrig_mva_valid"+ name, "", 2 ,0. ,2. );
  map_el["h_pf_charged_had_iso_03"]   = new TH1D("h_pf_charged_had_iso_03"+ name, "",200, 0., 10.);
  map_el["h_pf_photon_iso_03"]   = new TH1D("h_pf_photon_iso_03"+ name, "", 200, 0.,10.);
  map_el["h_pf_neutral_had_iso_03"]   = new TH1D("h_pf_neutral_had_iso_03"+ name, "",200, 0.,10.);
  map_el["h_pf_reliso_03"]   = new TH1D("h_pf_reliso_03"+ name, "", 200, 0.,1.);
  map_el["h_pf_absiso_03"]   = new TH1D("h_pf_absiso_03"+ name, "",2000, 0.,100.);
  map_el["h_pf_charged_had_iso_04"]   = new TH1D("h_pf_charged_had_iso_04"+ name, "",200, 0., 10.);
  map_el["h_pf_photon_iso_04"]   = new TH1D("h_pf_photon_iso_04"+ name, "", 200, 0.,10.);
  map_el["h_pf_neutral_had_iso_04"]   = new TH1D("h_pf_neutral_had_iso_04"+ name, "",200, 0.,10.);
  map_el["h_pf_reliso_04"]   = new TH1D("h_pf_reliso_04"+ name, "", 200, 0.,1.);
  map_el["h_pf_absiso_04"]   = new TH1D("h_pf_absiso_04"+ name, "",2000, 0.,100.);

  map_el["h_dz"]   = new TH1D("h_dz"+name , "", 1000, -1., 1.);

  map<TString, TString> titles;
  titles["h_sceta"]   ="SuperCluster #eta "; 
  titles["h_pt_shifted_up"] ="p_T shifted up (GeV)"; 
  titles["h_pt_shifted_down"] ="p_T shifted down (GeV)"; 
  titles["h_pass_veto"]   ="passVeto"; 
  titles["h_pass_loose"]   ="passLoose";
  titles["h_pass_medium"]   ="passMedium";
  titles["h_pass_tight"]   ="passTight";
  titles["h_pass_heep"]   ="passHEEP"; 
  titles["h_mcmatched"]   ="isMCMatched"; 
  titles["h_mc_isprompt"]   ="isPrompt"; 
  titles["h_mc_iscf"]   ="isChargeFlip"; 
  titles["h_mc_isconv"]   ="isConversion";
  titles["h_mc_fromtau"]   ="isFromTau";
  titles["h_mc_pdgid"]   ="mc PdgId"; 
  titles["h_mother_pdgid"]   ="mother PdgId";
  titles["h_mother_index"]   ="mother index";
  titles["h_mc_index"]   ="mc index"; 
  titles["h_particle_type"]   ="Particle Type"; 
  titles["h_mother_type"]   ="mother Type";
  titles["h_gspctfscpix_samecharge"]   ="Electron Charge Conistency";
  titles["h_pass_conv_veto"]   ="pass Conv. Veto"; 
  titles["h_istrig_mva_valid"]   ="isTrigMVA valid"; 
  titles["h_pf_charged_had_iso_03"]   ="PF Charge Hadron Iso. #DeltaR(0.3)";
  titles["h_pf_photon_iso_03"]   ="PF #gamma Iso. #DeltaR(0.3)"; 
  titles["h_pf_neutral_had_iso_03"]   ="PF Neutral Hadron Iso. #DeltaR(0.3)"; 
  titles["h_pf_reliso_03"]   ="PF Rel. Iso. #DeltaR(0.3)"; 
  titles["h_pf_absiso_03"]   ="PF Abs. Hadron Iso. #DeltaR(0.3)"; 
  titles["h_pf_charged_had_iso_04"]   ="PF Charge Hadron Iso. #DeltaR(0.4)";
  titles["h_pf_photon_iso_04"]   ="PF #gamma Iso. #DeltaR(0.4)"; 
  titles["h_pf_neutral_had_iso_04"]   ="PF Neutral Hadron Iso. #DeltaR(0.4)"; 
  titles["h_pf_reliso_04"]   ="PF Rel. Iso. #DeltaR(0.4)"; 
  titles["h_pf_absiso_04"]   ="PF Abs. Iso. #DeltaR(0.4)"; 
  titles["h_dz"]   ="d_{Z}"; 

  for( map<TString, TString>::iterator it = titles.begin(); it != titles.end(); it++){
    map<TString, TH1*>::iterator it2 = map_el.find(it->first);
    it2->second->GetXaxis()->SetTitle(it->second);
  }
}
 
void ElectronPlots::Fill(Double_t weight, std::vector<snu::KElectron> electrons){
  for(std::vector<snu::KElectron>::iterator elit = electrons.begin(); elit!=electrons.end(); elit++){
    
    Fill("h_sceta",elit->SCEta() ,  weight);   
    Fill("h_pt_shifted_up",elit->Pt()*1.05 ,  weight);
    Fill("h_pt_shifted_down",elit->Pt()/1.05 ,  weight);
    Fill("h_pass_veto",elit->passVetoID() ,  weight);  
    Fill("h_pass_loose",elit->passLooseID(),  weight); 
    Fill("h_pass_medium",elit->passMediumID() ,  weight);
    Fill("h_pass_tight",elit->passTightID() ,  weight); 
    Fill("h_pass_heep",elit->passHEEPID() ,  weight);  
    Fill("h_mcmatched",elit->MCMatched() ,  weight);  
    Fill("h_mc_isprompt",elit->MCIsPrompt() ,  weight); 
    Fill("h_mc_iscf",elit->MCIsCF() ,  weight); 
    Fill("h_mc_isconv",elit->MCIsFromConversion() ,  weight);
    Fill("h_mc_fromtau",elit->MCFromTau() ,  weight);
    Fill("h_mc_pdgid",elit->MCMatchedPdgId() ,  weight);
    Fill("h_mother_pdgid",elit->MotherPdgId()  ,  weight);
    Fill("h_mother_index",elit->MotherTruthIndex() ,  weight);
    Fill("h_mc_index",elit->MCTruthIndex() ,  weight);
    Fill("h_particle_type",elit->GetParticleType() ,  weight);
    Fill("h_mother_type",elit->GetMotherType() ,  weight);
    Fill("h_gspctfscpix_samecharge",elit->GsfCtfScPixChargeConsistency() ,  weight);
    Fill("h_pass_conv_veto",elit->PassesConvVeto() ,  weight);  
    Fill("h_pf_charged_had_iso_03",elit->PFChargedHadronIso(0.3) ,  weight);
    Fill("h_pf_photon_iso_03",elit->PFPhotonIso(0.3) ,  weight); 
    Fill("h_pf_neutral_had_iso_03",elit->PFNeutralHadronIso(0.3) ,  weight);
    Fill("h_pf_reliso_03",elit->PFRelIso(0.3) ,  weight);  
    Fill("h_pf_charged_had_iso_04",elit->PFChargedHadronIso(0.3) ,  weight);
    Fill("h_pf_photon_iso_04",elit->PFPhotonIso(0.3) ,  weight);
    Fill("h_pf_neutral_had_iso_04",elit->PFNeutralHadronIso(0.3) ,  weight);
    Fill("h_pf_reliso_04",elit->PFRelIso(0.3) ,  weight);
    Fill("h_dz", elit->dz(), weight); 
    
  } // end of electron loop
  
  return;
}


void ElectronPlots::Write() {
  StdPlots::Write();

  for(map<TString, TH1*>::iterator it = map_el.begin(); it != map_el.end(); it++){
    it->second->Write();
  }
}

ElectronPlots::ElectronPlots() : StdPlots() {
}

/**
 * Copy constructor.
 */
ElectronPlots::ElectronPlots(const ElectronPlots& ep): StdPlots(ep)
{
  for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = ep.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


ElectronPlots& ElectronPlots::operator= (const ElectronPlots& ep)
{
  if (this != &ep) {

    for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = ep.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

void ElectronPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_el.find(name);
  if(it!= map_el.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_el" << endl;
  return;
}

ElectronPlots::~ElectronPlots() {
  for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
    delete mit->second ;
  }

}
