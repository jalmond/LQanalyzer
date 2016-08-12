#include "MuonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void MuonPlots::Fill(Double_t weight, std::vector<snu::KMuon> muons){
  int imu(0);
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit!=muons.end(); muit++,imu++){

    Fill("h_charge",muit->Charge(), weight); 
    Fill("h_ispf",muit->IsPF() ,  weight);
    Fill("h_isglobal",muit->IsGlobal() ,  weight);
    Fill("h_istracker",muit->IsTracker() ,  weight);
    Fill("h_validhits",muit->validHits() ,  weight);
    Fill("h_validpixhits",muit->validPixHits() ,  weight);
    Fill("h_validstations",muit->validStations() ,  weight);
    Fill("h_activelayers",muit->ActiveLayer() ,  weight);
    Fill("h_muonvtx",muit->muonVtx() ,  weight);
    Fill("h_muonvty",muit->muonVty() ,  weight);
    Fill("h_muonvtz",muit->muonVtz() ,  weight);
    Fill("h_dz",muit->dZ() ,  weight);
    Fill("h_dxy",muit->dXY() ,  weight);
    Fill("h_sigdxy",muit->dXYSig() ,  weight);
    Fill("h_chi2",muit->GlobalChi2() ,  weight);
    Fill("h_isloose",muit->IsLoose() ,  weight);
    Fill("h_ismedium",muit->IsMedium() ,  weight);
    Fill("h_istight",muit->IsTight() ,  weight);
    Fill("h_issoft",muit->IsSoft() ,  weight);
    Fill("h_mcmatched",muit->MCMatched() ,  weight);
    Fill("h_mciscf",muit->MCIsCF() ,  weight);
    Fill("h_mcisconv",muit->MCIsFromConversion() ,  weight);
    Fill("h_mcfromtau",muit->MCFromTau() ,  weight);
    Fill("h_mcisprompt",muit->MCIsPrompt() ,  weight);
    Fill("h_mcmatched_pdgid",muit->MCMatchedPdgId() ,  weight);
    Fill("h_mother_pdgid",muit->MotherPdgId() ,  weight);
    Fill("h_mother_index",muit->MotherTruthIndex() ,  weight);
    Fill("h_mc_index",muit->MCTruthIndex() ,  weight);
    Fill("h_reliso03",muit->RelIso03() ,  weight);
    Fill("h_reliso04",muit->RelIso04() ,  weight);
    Fill("h_ptshifted_up",muit->Pt()*1.05 ,  weight);
    Fill("h_ptshifted_down",muit->Pt()/1.05 ,  weight);
    Fill("h_particle_type",muit->GetParticleType() ,  weight);
    Fill("h_mother_type",muit->GetMotherType() ,  weight);
    Fill("h_pt",muit->Pt() ,  weight);
    Fill("h_eta",muit->Eta() ,  weight);
    Fill("h_phi",muit->Phi() ,  weight);
    Fill("h_energy",muit->Energy() ,  weight);
    Fill("h_mass",muit->M() ,  weight);
  }
}


void MuonPlots::Write() {
  
  StdPlots::Write();
  for(map<TString, TH1*>::iterator it = map_muon.begin(); it != map_muon.end(); it++){
    it->second->Write();
  }

}

MuonPlots::MuonPlots(TString name) : StdPlots(name) {
  
  TH1::SetDefaultSumw2(true);
  map_muon["h_charge"] = new TH1F ("h_charge" + name , "",6, -3  , 3. );
  map_muon["h_ispf"] = new TH1F ("h_ispf" + name ,"",2,0.  , 2.);
  map_muon["h_isglobal"] = new TH1F ("h_isglobal" + name ,"",2,0.  ,2. );
  map_muon["h_istracker"] = new TH1F ("h_istracker" + name ,"", 2,0.,2. );
  map_muon["h_validhits"] = new TH1F ("h_validhits" + name ,"", 40,0.  ,40. );
  map_muon["h_validpixhits"] = new TH1F ("h_validpixhits" + name ,"",10,0.  ,10.);
  map_muon["h_validstations"] = new TH1F ("h_validstations" + name ,"",10,0. ,10. );
  map_muon["h_activelayers"] = new TH1F ("h_activelayers" + name ,"", 20,0.  , 20.);
  map_muon["h_muonvtx"] = new TH1F ("h_muonvtx" + name ,"",1000,-3.  ,3. );
  map_muon["h_muonvty"] = new TH1F ("h_muonvty" + name ,"",1000,-3.  , 3.);
  map_muon["h_muonvtz"] = new TH1F ("h_muonvtz" + name ,"",1000,-50.  ,50. );
  map_muon["h_dz"] = new TH1F ("h_dz" + name ,"",1000,-1.  ,1. );
  map_muon["h_dxy"] = new TH1F ("h_dxy" + name ,"",1000,-1.  ,1. );
  map_muon["h_sigdxy"] = new TH1F ("h_sigdxy" + name ,"",1000,-4.  ,4.  );
  map_muon["h_chi2"] = new TH1F ("h_chi2" + name ,"",500,0.  ,50. );
  map_muon["h_isloose"] = new TH1F ("h_isloose" + name ,"",2,0.  ,2. );
  map_muon["h_ismedium"] = new TH1F ("h_ismedium" + name ,"",2,0.  ,2.  );
  map_muon["h_istight"] = new TH1F ("h_istight" + name ,"",2,0.  ,2. );
  map_muon["h_issoft"] = new TH1F ("h_issoft" + name ,"",2,0.  ,2. );
  map_muon["h_mcmatched"] = new TH1F ("h_mcmatched" + name ,"",2,0.  ,2. );
  map_muon["h_mciscf"] = new TH1F ("h_mciscf" + name ,"",2,0.  ,2. );
  map_muon["h_mcisconv"] = new TH1F ("h_mcisconv" + name ,"",2,0.  ,2. );
  map_muon["h_mcfromtau"] = new TH1F ("h_mcfromtau" + name ,"",2,0.  , 2.  );
  map_muon["h_mcisprompt"] = new TH1F ("h_mcisprompt" + name ,"",2,0.  ,2. );
  map_muon["h_mcmatched_pdgid"] = new TH1F ("h_mcmatched_pdgid" + name ,"",200,-100.  ,100. );
  map_muon["h_mother_pdgid"] = new TH1F ("h_mother_pdgid" + name ,"", 200,-100.  ,100. );
  map_muon["h_mother_index"] = new TH1F ("h_mother_index" + name ,"",100,0.  ,100. );
  map_muon["h_mc_index"] = new TH1F ("h_mc_index" + name ,"",100,0.  ,100. );
  map_muon["h_reliso03"] = new TH1F ("h_reliso3" + name ,"",100,0.  ,1. );
  map_muon["h_reliso04"] = new TH1F ("h_reliso4" + name ,"",100,0.  ,1.);
  map_muon["h_ptshifted_up"] = new TH1F ("h_ptshifted_up" + name ,"",250,0.  ,500. );
  map_muon["h_ptshifted_down"] = new TH1F ("h_ptshifted_down" + name ,"",250,0.  , 500.  );
  map_muon["h_particle_type"] = new TH1F ("h_particle_type" + name ,"",10,0.  ,10. );
  map_muon["h_mother_type"] = new TH1F ("h_mother_type" + name ,"",10,0.  ,10  );
  map_muon["h_pt"] = new TH1F ("h_pt" + name ,"",250,0.  ,500. );
  map_muon["h_eta"] = new TH1F ("h_eta" + name ,"",60,-3.  ,3. );
  map_muon["h_phi"] = new TH1F ("h_phi" + name ,"",70,-3.5  ,3.5  );
  map_muon["h_energy"] = new TH1F ("h_energy" + name ,"",250,0.  ,500.  );
  map_muon["h_mass"] = new TH1F ("h_mass" + name ,"",250,0.  ,500.0 );

  map<TString, TString> titles;
  titles["h_charge"] = "Charge of muons";
  titles["h_ispf"] =  "Is Particle flow";
  titles["h_isglobal"] = "IsGlobal";
  titles["h_istracker"] = "IsTracker"; 
  titles["h_validhits"] = "Muon #valid hits";
  titles["h_validpixhits"] = "Muon #pixel hits";
  titles["h_validstations"] = "Muon #matched stations";
  titles["h_activelayers"] = "Muon #layers with measurements";
  titles["h_muonvtx"] = "Muon Vertex_{x}";
  titles["h_muonvty"] = "Muon Vertex_{y}";
  titles["h_muonvtz"] = "Muon Vertex_{z}";
  titles["h_dz"] =  "Muon d_{z}";
  titles["h_dxy"] =  "Muon d_{xy}";
  titles["h_sigdxy"] =  "Muon d_{xy}/#{sigma}_{xy}"; 
  titles["h_chi2"] = "Muon Global #Chi^{2}";
  titles["h_isloose"] = "Muon isLoose";
  titles["h_ismedium"] = "Muon isMedium";
  titles["h_istight"] =  "Muon isTight";
  titles["h_mcmatched"] = "isGenMatched"; 
  titles["h_mciscf"] = "isChargeFlip";
  titles["h_mcisconv"] = "isConversion";
  titles["h_mcfromtau"] = "isFromtau";
  titles["h_mcisprompt"] = "isPrompt";
  titles["h_mcmatched_pdgid"] = "PdgId of matched gen particle";
  titles["h_mother_pdgid"] =  "PdgId of mother";
  titles["h_mother_index"] = "Index of mother gen particle";
  titles["h_mc_index"] = "Index of matched gen particle";
  titles["h_reliso03"] = "Rel isolation (#deltaR=0.3)";
  titles["h_reliso04"] = "Rel isolation (#deltaR=0.4)";
  titles["h_ptshifted_up"] = "p_{T} shifted up (GeV)";
  titles["h_ptshifted_down"] = "p_{T} shifted down (GeV)";
  titles["h_particle_type"] = "KParticle::Type for muon";
  titles["h_mother_type"] = "KParticle::Type for mother";
  titles["h_pt"] = "p_{T} of muon (GeV)";
  titles["h_eta"] = "#eta of muon";
  titles["h_phi"] = "#phi of muon";
  titles["h_energy"] = "Energy of muon (GeV)";
  titles["h_mass"] = "mass (GeV)";


  for( map<TString, TString>::iterator it = titles.begin(); it != titles.end(); it++){
    map<TString, TH1*>::iterator it2 = map_muon.find(it->first);
    it2->second->GetXaxis()->SetTitle(it->second);
  }
    
}



MuonPlots::MuonPlots() : StdPlots() {
}

/**
 * Copy constructor.
 */
MuonPlots::MuonPlots(const MuonPlots& mp): StdPlots(mp)
{
  for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = mp.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


MuonPlots& MuonPlots::operator= (const MuonPlots& mp)
{
  if (this != &mp) {

    for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = mp.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

MuonPlots::~MuonPlots() {
   for(std::map<TString, TH1*>::iterator mit = map_muon.begin(); mit != map_muon.end() ; mit++){
     delete mit->second ;
  }

}

void MuonPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_muon.find(name);
  if(it!= map_muon.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_muon" << endl;
  return;
}
