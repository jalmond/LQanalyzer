#include "SignalPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SignalPlots::SignalPlots(TString name): StdPlots(name){
  
  map_sig["h_jjmass"] =         new TH1F("h_dijetsmass_"    + name,"Invariant mass of the two leading jets",100,0,1000);
  map_sig["h_eemass"] =         new TH1F("h_eemass_"        + name,"Invariant mass of the two leading electrons",100,0,1000);
  map_sig["h_mumumass"] =         new TH1F("h_mumumass_"        + name,"Invariant mass of the two leading muons",100,0,1000);
  map_sig["h_emumass"] =         new TH1F("h_emumass_"        + name,"Invariant mass of the two leading leptons",100,0,1000);
  map_sig["h_l1jjmass"] =       new TH1F("h_l1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_l2jjmass"] =       new TH1F("h_l2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_lljjmass"] =       new TH1F("h_lljjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  map_sig2["h_WandNmass"] =      new TH2F("h_WandNmass_"     + name,"Invariant mass of the W and the N",200,0,2000,200,0,2000);
  map_sig3["h_3Dparm"] =         new TH3F("h_3Dpar_"         + name,"m(lljj) and muon p_{T}_{1} and muon p_{T}_{2}",200,0,2000,60,0,300,60,0,300);
  map_sig["h_MuonJetdR"] =  new TH1F("h_MuonJetdR_" + name,"leading muon pt",500,0,5);
  map_sig["h_ElectronJetdR"] =  new TH1F("h_ElectronJetdR_" + name,"leading muon pt",500,0,5);
  map_sig["h_leadingMuonPt"] =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
  map_sig["h_secondMuonPt"] =   new TH1F("h_secondMuonPt_"  + name,"secondary muon pt",60,0,300);
  map_sig["h_leadingElectronPt"] =  new TH1F("h_leadingElectronPt_" + name,"leading electron pt",60,0,300);
  map_sig["h_secondElectronPt"] =   new TH1F("h_secondElectronPt_"  + name,"secondary electron pt",60,0,300);
  map_sig["h_leadingJetPt"] =   new TH1F("h_leadingJetPt_"  + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"] =    new TH1F("h_secondJetPt_"   + name,"secondary jet pt",60,0,300);
  map_sig["h_leadingMuonIso"] = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
  map_sig["h_secondMuonIso"] =  new TH1F("h_secondMuonIso_" + name,"secondary muon relIso",40,0,0.4);
  map_sig["h_leadingElectronIso"] = new TH1F("h_leadingElectronIso_"+ name,"leading electron relIso",40,0,0.4);
  map_sig["h_secondElectronIso"] =  new TH1F("h_secondElectronIso_" + name,"secondary electron relIso",40,0,0.4);
  map_sig["h_MET"] =            new TH1F("h_MET_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_paircharge"] =     new TH1F("h_paircharge_"    + name,"Charge of the muon pair",5,-2,3);
  map_sig["h_muonseta"] =       new TH1F("h_muonseta_"      + name,"#eta distribution of the two muons",50,-3,3);
  map_sig["h_electronseta"] =       new TH1F("h_electronseta_"      + name,"#eta distribution of the two electrons",50,-3,3);
  map_sig["h_jetseta"] =        new TH1F("h_jetseta_"       + name,"#eta distribution of the two jets",50,-3,3);
  map_sig["h_bTag"] =           new TH1F("h_bTag_"          + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"] =          new TH1F("h_Njets_"         + name,"number of jets",10,0,10);
}


void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {

  //// Fills all hists (e/mu/jets/MET)
  
  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);
  

  float min_mujet_Dr=10000.;  
  for(UInt_t i=0; i<muons.size(); i++){  
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =muons[i].DeltaR(jets[emme]);
      if(dR< min_mujet_Dr) min_mujet_Dr=dR;
    }
  }

  float min_ejet_Dr=10000.;  
  for(UInt_t i=0; i<electrons.size(); i++){ 
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =electrons[i].DeltaR(jets[emme]);
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;
    }
  }
  Fill("h_MuonJetdR",min_mujet_Dr,weight);
  Fill("h_ElectronJetdR",min_ejet_Dr,weight);

  for(UInt_t emme=0; emme<jets.size(); emme++){
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if ( fabs(dijetmass_tmp-Mass_W) < fabs(dijetmass-Mass_W) ) {
	dijetmass = dijetmass_tmp;
	m = emme;
	n = enne;
      }
    }
  }


  if(muons.size()==2){     
    Fill("h_mumumass", (muons[0]+muons[1]).M(),weight);
    if(jets.size()>1){
      Fill("h_l1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
      Fill("h_l2jjmass", (muons[1]+jets[m]+jets[n]).M(),weight);      
      Fill("h_lljjmass", (muons[0]+muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (muons[0]+muons[1]+jets[m]+jets[n]).M() , (muons[1]+jets[m]+jets[n]).M(),weight);      
    }
    Fill("h_muonseta",muons[0].Eta(),weight);
    Fill("h_muonseta",muons[1].Eta(),weight);
    Fill("h_secondMuonPt", muons[1].Pt(),weight);
    Fill("h_leadingMuonPt", muons[0].Pt(),weight);
    Fill("h_leadingMuonIso", muons[0].RelIso(),weight);
    Fill("h_secondMuonIso", muons[1].RelIso(),weight);
  }

  if(electrons.size()==2){    
    Fill("h_eemass", (electrons[0]+electrons[1]).M(),weight);
    if(jets.size()>1){
      Fill("h_l1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
      Fill("h_l2jjmass", (electrons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_lljjmass", (electrons[0] + electrons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (electrons[0]+electrons[1]+jets[m]+jets[n]).M() , (electrons[1]+jets[m]+jets[n]).M(),weight);      
    }
    Fill("h_electronseta",electrons[0].Eta(),weight);
    Fill("h_electronseta",electrons[1].Eta(),weight);
    Fill("h_secondElectronPt", electrons[1].Pt(),weight);
    Fill("h_leadingElectronPt", electrons[0].Pt(),weight);     
  }
  
  
  if(muons.size()==1 && electrons.size()==1){
    Fill("h_eemumass", (electrons[0]+muons[0]).M(),weight);
    if(jets.size()>1)Fill("h_lljjmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M(),weight);
    Fill("h_muonseta",muons[0].Eta(),weight);
    Fill("h_electronseta",electrons[0].Eta(),weight);
    Fill("h_leadingMuonPt", muons[0].Pt(),weight);
    Fill("h_leadingElectronPt", electrons[0].Pt(),weight);
    if(jets.size()>1){
      if(muons[0].Pt() > electrons[0].Pt()){
	
	Fill("h_l1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_l2jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_WandNmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M() , (electrons[0]+jets[m]+jets[n]).M(),weight);      
      } 
      else{
	Fill("h_l1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_l2jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_WandNmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M() , (muons[0]+jets[m]+jets[n]).M(),weight);      
      }
    }
  }
  
  //// Fillplots
  Fill("h_MET",ev.MET(), weight);
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight); 
  }

  Fill("h_paircharge",muons[0].Charge(),weight);
  
  for(UInt_t j=0; j < jets.size(); j++){ 
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    Fill("h_jetseta",jets[j].Eta(),weight);
    Fill("h_bTag",jets[j].BtagProb(),weight);
  }
  Fill("h_Njets",jets.size(), weight);
  
  return;
}/// End of Fill


void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  
  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);
  float min_ejet_Dr=10000.;  
  for(UInt_t i=0; i<electrons.size(); i++){    for(UInt_t emme=0; emme<jets.size()-1; emme++){
      float dR =electrons[i].DeltaR(jets[emme]);
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;
    }
  }
  
  Fill("h_ElectronJetdR",min_ejet_Dr,weight);
  
  for(UInt_t i=0; i<electrons.size()-1; i++)
    for(UInt_t j=1; j<electrons.size(); j++) {
      for(UInt_t emme=0; emme<jets.size()-1; emme++)
	for(UInt_t enne=1; enne<jets.size(); enne++) {
	  dijetmass_tmp = (jets[emme]+jets[enne]).M();
	  if ( fabs(dijetmass_tmp-Mass_W) < fabs(dijetmass-Mass_W) ) {
	    dijetmass = dijetmass_tmp;
	    m = emme;
	    n = enne;
	  }
	}

      //// Fillplots
      Fill("h_MET",ev.MET(), weight);
      
      //// Mass plots
      Fill("h_jjmass", (jets[m]+jets[n]).M(),weight);
      Fill("h_llmass", (electrons[i]+electrons[j]).M(),weight);
      Fill("h_l1jjmass", (electrons[i]+jets[m]+jets[n]).M(),weight);
      Fill("h_l2jjmass", (electrons[j]+jets[m]+jets[n]).M(),weight);
      Fill("h_lljjmass", (electrons[i]+electrons[j]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (electrons[i]+electrons[j]+jets[m]+jets[n]).M() , (electrons[j]+jets[m]+jets[n]).M(),weight);

      Fill("h_3Dparm", (electrons[i]+electrons[j]+jets[m]+jets[n]).M(), electrons[i].Pt(), electrons[j].Pt(), weight); 
      Fill("h_leadingElectronPt", electrons[i].Pt(),weight);
      Fill("h_secondElectronPt", electrons[j].Pt(),weight);
      Fill("h_leadingJetPt", jets[m].Pt(),weight);
      Fill("h_secondJetPt", jets[n].Pt(),weight);
      //Fill("h_leadingElectronIso", electrons[i].RelIso(),weight);
      //Fill("h_secondElectronIso", electrons[j].RelIso(),weight);
      Fill("h_paircharge",electrons[i].Charge(),weight);
      Fill("h_electronseta",electrons[i].Eta(),weight);
      Fill("h_electronseta",electrons[j].Eta(),weight);
      Fill("h_jetseta",jets[m].Eta(),weight);
      Fill("h_jetseta",jets[n].Eta(),weight);
      Fill("h_bTag",jets[m].BtagProb(),weight);
      Fill("h_bTag",jets[n].BtagProb(),weight);
      Fill("h_cosTheta1",cos(electrons[i].Theta()),weight);
      Fill("h_cosTheta2",cos(electrons[j].Theta()),weight);
      Fill("h_Njets",jets.size(), weight);
      
      //nogoodW:
      ;
    }
  
  
  return;
}
  


void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KJet>& jets, Double_t weight){
  
   //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);

  float min_mujet_Dr=10000.;  
  for(UInt_t i=0; i<muons.size(); i++){    for(UInt_t emme=0; emme<jets.size()-1; emme++){
      float dR =muons[i].DeltaR(jets[emme]);
      if(dR< min_mujet_Dr) min_mujet_Dr=dR;
    }
  }

  Fill("h_MuonJetdR",min_mujet_Dr,weight);
  
  for(UInt_t i=0; i<muons.size()-1; i++)
    for(UInt_t j=1; j<muons.size(); j++) {
      for(UInt_t emme=0; emme<jets.size()-1; emme++)
	for(UInt_t enne=1; enne<jets.size(); enne++) {
	  dijetmass_tmp = (jets[emme]+jets[enne]).M();
	  if ( fabs(dijetmass_tmp-Mass_W) < fabs(dijetmass-Mass_W) ) {
	    dijetmass = dijetmass_tmp;
	    m = emme;
	    n = enne;
	  }
	}

      //// Fillplots
      Fill("h_MET",ev.MET(), weight);
      
      //// Mass plots
      Fill("h_jjmass", (jets[m]+jets[n]).M(),weight);
      Fill("h_llmass", (muons[i]+muons[j]).M(),weight);
      Fill("h_l1jjmass", (muons[i]+jets[m]+jets[n]).M(),weight);
      Fill("h_l2jjmass", (muons[j]+jets[m]+jets[n]).M(),weight);
      Fill("h_lljjmass", (muons[i]+muons[j]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (muons[i]+muons[j]+jets[m]+jets[n]).M() , (muons[j]+jets[m]+jets[n]).M(),weight);

      Fill("h_3Dparm", (muons[i]+muons[j]+jets[m]+jets[n]).M(), muons[i].Pt(), muons[j].Pt(), weight); 
      Fill("h_leadingMuonPt", muons[i].Pt(),weight);
      Fill("h_secondMuonPt", muons[j].Pt(),weight);
      Fill("h_leadingJetPt", jets[m].Pt(),weight);
      Fill("h_secondJetPt", jets[n].Pt(),weight);
      Fill("h_leadingMuonIso", muons[i].RelIso(),weight);
      Fill("h_secondMuonIso", muons[j].RelIso(),weight);
      Fill("h_paircharge",muons[i].Charge(),weight);
      Fill("h_muonseta",muons[i].Eta(),weight);
      Fill("h_muonseta",muons[j].Eta(),weight);
      Fill("h_jetseta",jets[m].Eta(),weight);
      Fill("h_jetseta",jets[n].Eta(),weight);
      Fill("h_bTag",jets[m].BtagProb(),weight);
      Fill("h_bTag",jets[n].BtagProb(),weight);
      Fill("h_cosTheta1",cos(muons[i].Theta()),weight);
      Fill("h_cosTheta2",cos(muons[j].Theta()),weight);
      Fill("h_Njets",jets.size(), weight);
          
      //nogoodW:
      ;
    }

  
  return;
}

void SignalPlots::Write() {
 
  for(map<TString, TH1*>::iterator it = map_sig.begin(); it != map_sig.end(); it++){
    it->second->Write();
  }

}


SignalPlots::SignalPlots(): StdPlots(){
}


/**
 * Copy constructor.
 */
SignalPlots::SignalPlots(const SignalPlots& sp): StdPlots(sp)
{
  for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
    std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
    mit->second = mit2->second;
  }
}


SignalPlots& SignalPlots::operator= (const SignalPlots& sp)
{
  if (this != &sp) {

    for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
      std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
      mit->second = mit2->second;
    }
  }
  return *this;
}

SignalPlots::~SignalPlots() {
   for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
     delete mit->second ;
  }

}

void SignalPlots::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end()) it->second->Fill(value, w);
  else cout << name << " not found in map_sig" << endl;
  return;
}
 
 void SignalPlots::Fill(TString name, double value1, double value2, double w){
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) it->second->Fill(value1, value2, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }



 void SignalPlots::Fill(TString name, double value1, double value2, double value3, double w){
   std::map<TString, TH3*>::iterator it = map_sig3.find(name);
   if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }




