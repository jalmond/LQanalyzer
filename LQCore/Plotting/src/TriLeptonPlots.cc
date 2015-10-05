#include "TriLeptonPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

TriLeptonPlots::TriLeptonPlots(TString name): StdPlots(name){

  TH1::SetDefaultSumw2(true);
  map_sig["h_Njets"]                  =     new TH1F("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]                 =     new TH1F("h_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_jets_pt"]                =     new TH1F("h_jets_pt_"           + name,"jet pt",60,0,300);
  map_sig["h_jets_eta"]               =     new TH1F("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-3,3);

  map_sig["h_osllmass"]               =     new TH1F("h_osllmass_"          + name,"Invariant mass of the two leading os electrons",100,0,500);
  map_sig["h_lljjmass"]               =     new TH1F("h_lljjmass_"         + name,"Invariant mass of the four particles",200,0,2000);
  map_sig["h_l1jjmass"]               =     new TH1F("h_l1jjmass_"          + name,"Invariant mass of the two leading jets and leading electron",100,0,1000);
  map_sig["h_l2jjmass"]               =     new TH1F("h_l2jjmass_"          + name,"Invariant mass of the two leading jets and second electron",100,0,1000);

  map_sig["h_LeptonEta"]              =     new TH1F("h_LeptonEta_"         + name,"leading lepton eta",60,-3.,3.);
  map_sig["h_LeptonPt"]               =     new TH1F("h_LeptonPt_"          + name,"lepton pt",100,0,500);
  map_sig["h_leadingLeptonPt"]        =     new TH1F("h_leadingLeptonPt_"   + name,"leading lepton pt",100,0,500);
  map_sig["h_secondLeptonPt"]         =     new TH1F("h_secondLeptonPt_"    + name,"secondary lepton pt",60,0,300);
  map_sig["h_thirdLeptonPt"]         =     new TH1F("h_thirdLeptonPt_"    + name,"thirdary lepton pt",60,0,300);
  map_sig["h_leadingLeptonEta"]       =     new TH1F("h_leadingLeptonEta_"  + name,"leading lepton eta",60,-3.,3.);
  map_sig["h_secondLeptonEta"]        =     new TH1F("h_secondLeptonEta_"   + name,"second lepton eta",60,-3.,3.);
  map_sig["h_thirdLeptonEta"]        =     new TH1F("h_thirdLeptonEta_"   + name,"third lepton eta",60,-3.,3.);
  

  map_sig["h_PFMET"]                  =     new TH1F("h_PFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_PFMET_phi"]              =     new TH1F("h_PFMET_phi_"           + name,"Missing Et",100,0.0,500.0);

  map_sig["h_NoHFMET"]                =     new TH1F("h_NoHFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_NoHFMET_phi"]            =     new TH1F("h_NoHFMET_phi_"           + name,"Missing Et",100,0.0,500.0);

  map_sig["h_nVertices"]              =     new TH1F("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  /// Charge plot
  map_sig["h_sumcharge"]              =     new TH1F("h_sumcharge_"         + name,"Charge of the electron pair",6,-3,3);

  /// Number of objects
  map_sig["h_Nmuons"]                 =     new TH1F("h_Nmuons_"           + name,"number of mu",5,0,5);
  map_sig["h_Nelectrons"]             =     new TH1F("h_Nelectrons_"           + name,"number of el",5,0,5);




}




void TriLeptonPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  
  Fill("h_Nmuons" ,muons.size(), weight);
  Fill("h_Nelectrons" ,electrons.size(), weight);

  
  if(electrons.size()==2){
    if(electrons[0].Charge() != electrons[1].Charge())   Fill("h_osllmass", (electrons[0]+electrons[1]).M(),weight);
  }
  if(muons.size()==2){
    if(muons[0].Charge() != muons[1].Charge())   Fill("h_osllmass", (muons[0]+muons[1]).M(),weight);
  }
  if(electrons.size()==3){
    if(electrons[0].Charge() != electrons[1].Charge())    Fill("h_osllmass", (electrons[0]+electrons[1]).M(),weight);
    if(electrons[0].Charge() != electrons[2].Charge())    Fill("h_osllmass", (electrons[0]+electrons[2]).M(),weight);
    if(electrons[1].Charge() != electrons[2].Charge())    Fill("h_osllmass", (electrons[1]+electrons[2]).M(),weight);
    int iel=0;
    for(std::vector<snu::KElectron>::iterator elit = electrons.begin(); elit != electrons.end(); elit++, iel++){
      Fill("h_Lepton_Pt", elit->Pt(),weight);
      Fill("h_Lepton_eta",elit->Eta(),weight);
    }    
  }
  if(muons.size()==3){
    if(muons[0].Charge() != muons[1].Charge())    Fill("h_osllmass", (muons[0]+muons[1]).M(),weight);
    if(muons[0].Charge() != muons[2].Charge())    Fill("h_osllmass", (muons[0]+muons[2]).M(),weight);
    if(muons[1].Charge() != muons[2].Charge())    Fill("h_osllmass", (muons[1]+muons[2]).M(),weight);
    int imu=0;
    for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit != muons.end(); muit++, imu++){
      Fill("h_Lepton_Pt", muit->Pt(),weight);
      Fill("h_Lepton_eta",muit->Eta(),weight);
      if(imu ==0) {
	Fill("h_firstLepton_Pt", muit->Pt(),weight);
	Fill("h_firstLepton_eta",muit->Eta(),weight);
      }
      if(imu ==1) {
        Fill("h_secondLepton_Pt", muit->Pt(),weight);
        Fill("h_secondLepton_eta",muit->Eta(),weight);
      }
      if(imu ==2) {
        Fill("h_thirdLepton_Pt", muit->Pt(),weight);
        Fill("h_thirdLepton_eta",muit->Eta(),weight);
      }
      
    }   
  }

 
  Fill("h_Njets",jets.size(), weight);
  
  Fill("h_PFMET",ev.PFMET(), weight);
  Fill("h_PFMET_phi",ev.PFMETphi(), weight);
  Fill("h_nVertices", ev.nVertices(), weight);


  Fill("h_NoHFMET",ev.NoHFMET(), weight);
  Fill("h_NoHFMET_phi",ev.NoHFMETphi(), weight);
  
  for(UInt_t j=0; j < jets.size(); j++){
    Fill("h_jets_pt", jets[j].Pt(),weight);
    Fill("h_jets_eta",jets[j].Eta(),weight);
  }


  return;
}/// End of Fill



void TriLeptonPlots::Write() {
 
  for(map<TString, TH1*>::iterator it = map_sig.begin(); it != map_sig.end(); it++){
    it->second->Write();
  }

  for(map<TString, TH2*>::iterator it = map_sig2.begin(); it != map_sig2.end(); it++){
    it->second->Write();
  }


  for(map<TString, TH3*>::iterator it = map_sig3.begin(); it != map_sig3.end(); it++){
    it->second->Write();
  }

}


TriLeptonPlots::TriLeptonPlots(): StdPlots(){
}


/**
 * Copy constructor.
 */
TriLeptonPlots::TriLeptonPlots(const TriLeptonPlots& sp): StdPlots(sp)
{
  for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
    mit->second = mit2->second;
  }

  for(std::map<TString, TH2*>::iterator mit = map_sig2.begin(); mit != map_sig2.end() ; mit++){
    std::map<TString, TH2*>::iterator mit2 = sp.GetMap2().find(mit->first);
    mit->second = mit2->second;
  }

  for(std::map<TString, TH3*>::iterator mit = map_sig3.begin(); mit != map_sig3.end() ; mit++){
    std::map<TString, TH3*>::iterator mit2 = sp.GetMap3().find(mit->first);
    mit->second = mit2->second;
  }
  
}


TriLeptonPlots& TriLeptonPlots::operator= (const TriLeptonPlots& sp)
{
  if (this != &sp) {

    for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
    
    for(std::map<TString, TH2*>::iterator mit = map_sig2.begin(); mit != map_sig2.end() ; mit++){
      std::map<TString, TH2*>::iterator mit2 = sp.GetMap2().find(mit->first);
      mit->second = mit2->second;
    }

    for(std::map<TString, TH3*>::iterator mit = map_sig3.begin(); mit != map_sig3.end() ; mit++){
      std::map<TString, TH3*>::iterator mit2 = sp.GetMap3().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

TriLeptonPlots::~TriLeptonPlots() {
   for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
     delete mit->second ;
  }

   for(std::map<TString, TH2*>::iterator mit = map_sig2.begin(); mit != map_sig2.end() ; mit++){
     delete mit->second ;
   }

   for(std::map<TString, TH3*>::iterator mit = map_sig3.begin(); mit != map_sig3.end() ; mit++){
     delete mit->second ;
   }
   
}

void TriLeptonPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end())   it->second->Fill(value, w);

  else cout << name << " not found in map_sig" << endl;
  return;
}
 
void TriLeptonPlots::Fill(TString name, double value1, double value2, double w){
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) it->second->Fill(value1, value2, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }



void TriLeptonPlots::Fill(TString name, double value1, double value2, double value3, double w){
  std::map<TString, TH3*>::iterator it = map_sig3.find(name);
  if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
  else cout << name << " not found in map_sig" << endl;
  return;
}




