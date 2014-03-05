#include "ElectronPlots.h"
#include <iostream>

using namespace std;

ElectronPlots::ElectronPlots(TString name) : StdPlots(name) {
  
  map_el["h_charge"]             = new TH1F("h_"+name+"_charge","Charge of "+name,5,-2,3);
  map_el["h_dxy"]                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  map_el["h_dz"]                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
  map_el["h_valid_hit_frac"]     = new TH1F("h_"+name+"_valid_hit_frac",name+" TrackValidHitFraction",100,0.0,1.0);
  map_el["h_trackdriven_seed"]   = new TH1F("h_"+name+"_trackdriven_seed",name+" TrackerDrivenSeed",2,0.0,2.0);
  map_el["h_elecal_seed"]        = new TH1F("h_"+name+"_elecal_seed",name+" EcalDrivenSeed",2,0.0,2.0);
  map_el["h_deltaeta"]        = new TH1F("h_"+name+"_deltaeta",name+" ", 100 ,-0.02 ,0.02 );
  map_el["h_deltaphi"]        = new TH1F("h_"+name+"_deltaphi",name+" ", 100 , -1. , 1. );
  map_el["h_sigmaIetaIeta"]        = new TH1F("h_"+name+"_sigmaIetaIeta",name+" ",50 ,0. , 0.05 );
  map_el["h_hoe"]        = new TH1F("h_"+name+"_hoe",name+" ", 100 ,0. , 0.5);
  map_el["h_caloenergy"]        = new TH1F("h_"+name+"_caloenergy",name+" ", 100 , 0. ,200. );
  map_el["h_escoverp"]        = new TH1F("h_"+name+"_ecoverp",name+" ", 50 , -0.25 , 0.25);
  map_el["h_gsf_ct_pix_charecons"]        = new TH1F("h_"+name+"_chargeconst",name+" ",2 ,0. , 2.);
  map_el["h_missinghits"]        = new TH1F("h_"+name+"_missinghits",name+" ", 5 , 0. ,5. );
  map_el["h_convfitprob"]        = new TH1F("h_"+name+"_convfitprob",name+" ",20. , 0. ,1. );
  map_el["h_matched_convphot"]        = new TH1F("h_"+name+"_matchedcon_phot",name+" ",2 ,0. ,2. );
  map_el["h_nbrem"]        = new TH1F("h_"+name+"_nbrem",name+" ", 10,0. ,10. );
  map_el["h_fbrem"]        = new TH1F("h_"+name+"_fbrem",name+" ", 10,0. ,10. );

  
}

ElectronPlots::~ElectronPlots() {
  for(std::map<TString, TH1*>::iterator mit = map_el.begin(); mit != map_el.end() ; mit++){
     delete mit->second ;
  }
}

void ElectronPlots::Fill(Double_t weight, std::vector<snu::KElectron> el, double rho){

  int iel(0);
  for(std::vector<snu::KElectron>::iterator elit = el.begin(); elit!=el.end(); elit++,iel++){
    
    Fill("h_dxy",elit->dxy(), weight);
    Fill("h_dz",elit->dz(), weight);
    Fill("h_fbrem", elit->FBrem(), weight);
    Fill("h_nbrem", elit->NBrems(), weight);
    Fill("h_valid_hit_frac", elit->TrackValidHitFraction(), weight);
    Fill("h_trackdriven_seed", elit->TrackerDrivenSeed(), weight);
    Fill("h_elecal_seed", elit->EcalDrivenSeed(), weight);
    Fill("h_deltaeta", elit->DeltaEta(), weight);
    Fill("h_deltaphi", elit->DeltaPhi(), weight);
    Fill("h_sigmaIetaIeta", elit->SigmaIEtaIEta(), weight);
    Fill("h_hoe", elit->HoE(), weight);
    Fill("h_caloenergy", elit->CaloEnergy(), weight);
    
    double egamma_e  = elit->CaloEnergy();
    double egamma_p  = elit->CaloEnergy() / elit->ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

    Fill("h_escoverp", egamma_ep, weight);
    Fill("h_gsf_ct_pix_charecons", elit->GsfCtfScPixChargeConsistency(), weight);
    Fill("h_missinghits", elit->MissingHits(), weight);
    Fill("h_convfitprob", elit->ConvFitProb(), weight);
    Fill("h_matched_convphot", elit->HasMatchedConvPhot(), weight);
    
    
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
