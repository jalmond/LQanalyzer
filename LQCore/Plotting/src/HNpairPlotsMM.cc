#include "HNpairPlotsMM.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

HNpairPlotsMM::HNpairPlotsMM(TString name): StdPlots(name){
  
  TH1::SetDefaultSumw2(true);
  //N
  map_sig["h_Njets"]                  =     new TH1D("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]                 =     new TH1D("h_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nmuons"]                 =     new TH1D("h_Nmuons_"           + name,"number of mu",5,0,5);
  map_sig["h_Nelectrons"]             =     new TH1D("h_Nelectrons_"           + name,"number of el",5,0,5);
  map_sig["h_nVertices"]              =     new TH1D("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  
  //OS CR
  map_sig["h_llmass_OS"]              =     new TH1D("h_OS_llmass_"          + name,"Invariant mass of the two leading os leptons",100,0,500);
  map_sig["h_leadingLeptonPt_OS"]     =     new TH1D("h_OS_leadingLeptonPt_"   + name,"leading lepton pt",100,0,500);
  map_sig["h_secondLeptonPt_OS"]      =     new TH1D("h_OS_secondLeptonPt_"    + name,"secondary lepton pt",60,0,300);
  map_sig["h_leadingLeptonEta_OS"]    =     new TH1D("h_OS_leadingLeptonEta_"  + name,"leading lepton eta",60,-3.,3.);
  map_sig["h_secondLeptonEta_OS"]     =     new TH1D("h_OS_secondLeptonEta_"   + name,"second lepton eta",60,-3.,3.);
  map_sig["h_PFMET_OS"]               =     new TH1D("h_OS_PFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_PFMET_phi_OS"]           =     new TH1D("h_OS_PFMET_phi_"           + name,"Missing Et",100,-3.2,3.2);
  map_sig["h_Njets_OS"]               =     new TH1D("h_OS_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets_OS"]              =     new TH1D("h_OS_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nmuons_OS"]              =     new TH1D("h_OS_Nmuons_"           + name,"number of mu",5,0,5);
  map_sig["h_Nelectrons_OS"]          =     new TH1D("h_OS_Nelectrons_"           + name,"number of el",5,0,5);
  map_sig["h_nVertices_OS"]           =     new TH1D("h_OS_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  map_sig["h_leadingjet_pt_OS"]       =     new TH1D("h_OS_leadingjet_pt_"           + name,"leadingjet pt",60,0,300);
  map_sig["h_secondjet_pt_OS"]        =     new TH1D("h_OS_secondjet_pt_"           + name,"secondjet pt",60,0,300);
  map_sig["h_leadingjet_eta_OS"]      =     new TH1D("h_OS_leadingjet_eta_"          + name,"#eta distribution of leadingjet",120,-3,3);
  map_sig["h_secondjet_eta_OS"]       =     new TH1D("h_OS_secondjet_eta_"          + name,"#eta distribution of the secondjet",120,-3,3);
  
  //SS CR
  map_sig["h_llmass_SS"]              =     new TH1D("h_SS_llmass_"          + name,"Invariant mass of the two leading ss leptons",100,0,500);
  map_sig["h_leadingLeptonPt_SS"]     =     new TH1D("h_SS_leadingLeptonPt_"   + name,"leading lepton pt",100,0,500);
  map_sig["h_secondLeptonPt_SS"]      =     new TH1D("h_SS_secondLeptonPt_"    + name,"secondary lepton pt",60,0,300);
  map_sig["h_leadingLeptonEta_SS"]    =     new TH1D("h_SS_leadingLeptonEta_"  + name,"leading lepton eta",60,-3.,3.);
  map_sig["h_secondLeptonEta_SS"]     =     new TH1D("h_SS_secondLeptonEta_"   + name,"second lepton eta",60,-3.,3.);
  map_sig["h_PFMET_SS"]               =     new TH1D("h_SS_PFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_PFMET_phi_SS"]           =     new TH1D("h_SS_PFMET_phi_"           + name,"Missing Et",100,-3.2,3.2);
  map_sig["h_Njets_SS"]               =     new TH1D("h_SS_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets_SS"]              =     new TH1D("h_SS_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nmuons_SS"]              =     new TH1D("h_SS_Nmuons_"           + name,"number of mu",5,0,5);
  map_sig["h_Nelectrons_SS"]          =     new TH1D("h_SS_Nelectrons_"           + name,"number of el",5,0,5);
  map_sig["h_nVertices_SS"]           =     new TH1D("h_SS_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  map_sig["h_leadingjet_pt_SS"]       =     new TH1D("h_SS_leadingjet_pt_"           + name,"leadingjet pt",60,0,300);
  map_sig["h_secondjet_pt_SS"]        =     new TH1D("h_SS_secondjet_pt_"           + name,"secondjet pt",60,0,300);
  map_sig["h_leadingjet_eta_SS"]      =     new TH1D("h_SS_leadingjet_eta_"          + name,"#eta distribution of leadingjet",120,-3,3);
  map_sig["h_secondjet_eta_SS"]       =     new TH1D("h_SS_secondjet_eta_"          + name,"#eta distribution of the secondjet",120,-3,3);
  
  //OS SR
  map_sig["h_lljjjjmass_OS"]          =     new TH1D("h_OS_lljjjjmass_"          + name,"Invariant mass of di-lepton and leading four jets",5000,0,5000);
  map_sig["h_lljjjjpt_OS"]            =     new TH1D("h_OS_lljjjjpt_"          + name,"pt of di-lepton and leading four jets",5000,0,5000);
  map_sig["h_lljjjjeta_OS"]           =     new TH1D("h_OS_lljjjjeta_"          + name,"#eta distribution of di-lepton and leading four jets",120,-3,3);
  map_sig["h_leadingljjmass_OS"]      =     new TH1D("h_OS_leadingljjmass_"          + name,"Invariant mass of leading ljj",5000,0,5000);
  map_sig["h_secondljjmass_OS"]       =     new TH1D("h_OS_secondljjmass_"          + name,"Invariant mass of second ljj",5000,0,5000);
  map_sig["h_leadingljjpt_OS"]        =     new TH1D("h_OS_leadingljjpt_"          + name,"pt of leading ljj",5000,0,5000);
  map_sig["h_secondljjpt_OS"]         =     new TH1D("h_OS_secondljjpt_"          + name,"pt of second ljj",5000,0,5000);
  map_sig["h_leadingljjeta_OS"]       =     new TH1D("h_OS_leadingljjeta_"          + name,"#eta distribution of leading ljj",120,-3,3);
  map_sig["h_secondljjeta_OS"]        =     new TH1D("h_OS_secondljjeta_"          + name,"#eta distribution of second ljj",120,-3,3);
  
  //SS SR
  map_sig["h_lljjjjmass_SS"]          =     new TH1D("h_SS_lljjjjmass_"          + name,"Invariant mass of di-lepton and leading four jets",5000,0,5000);
  map_sig["h_lljjjjpt_SS"]            =     new TH1D("h_SS_lljjjjpt_"          + name,"pt of di-lepton and leading four jets",5000,0,5000);
  map_sig["h_lljjjjeta_SS"]           =     new TH1D("h_SS_lljjjjeta_"          + name,"#eta distribution of di-lepton and leading four jets",120,-3,3);
  map_sig["h_leadingljjmass_SS"]      =     new TH1D("h_SS_leadingljjmass_"          + name,"Invariant mass of leading ljj",5000,0,5000);
  map_sig["h_secondljjmass_SS"]       =     new TH1D("h_SS_secondljjmass_"          + name,"Invariant mass of second ljj",5000,0,5000);
  map_sig["h_leadingljjpt_SS"]        =     new TH1D("h_SS_leadingljjpt_"          + name,"pt of leading ljj",5000,0,5000);
  map_sig["h_secondljjpt_SS"]         =     new TH1D("h_SS_secondljjpt_"          + name,"pt of second ljj",5000,0,5000);
  map_sig["h_leadingljjeta_SS"]       =     new TH1D("h_SS_leadingljjeta_"          + name,"#eta distribution of leading ljj",120,-3,3);
  map_sig["h_secondljjeta_SS"]        =     new TH1D("h_SS_secondljjeta_"          + name,"#eta distribution of second ljj",120,-3,3);

  


  /// Charge plot
  map_sig["h_sumcharge"]              =     new TH1D("h_sumcharge_"         + name,"Charge of the electron pair",6,-3,3);


  
}


void HNpairPlotsMM::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight, int nbjet) {
  
  //int nbjet = NBJet(jets);
  Fill("h_Nmuons" ,muons.size(), weight);
  Fill("h_Nelectrons" ,electrons.size(), weight);
  Fill("h_nVertices", ev.nVertices(), weight);
  Fill("h_Nbjets", nbjet, weight);  
  Fill("h_Njets", jets.size(), weight);
  
  
  if(muons.size() != 2) return;
  if(electrons.size() != 0) return;

  snu::KParticle HN_1, HN_2;
  snu::KParticle leading_HN, second_HN;
  //reconstruct HN pair
  if(jets.size() > 3){
    float min_del_HNHN = 9999.;
    float min_del_R_mu1j = 9999.;
    float min_del_R_mu2j = 9999.;
    for(int j1 = 0; j1 < 4; j1 ++){
      if(muons[0].DeltaR(jets[j1]) < min_del_R_mu1j) min_del_R_mu1j = muons[0].DeltaR(jets[j1]);
      if(muons[1].DeltaR(jets[j1]) < min_del_R_mu2j) min_del_R_mu2j = muons[1].DeltaR(jets[j1]);
      
      for(int j2 = 0; j2 < 4; j2 ++){
	snu::KParticle all_jet = jets[0] + jets[1] + jets[2] + jets[3];
	snu::KParticle current_HN1 = muons[0] + jets[j1] + jets[j2];
	all_jet = all_jet - jets[j1] - jets[j2];
	snu::KParticle current_HN2 = muons[1] + all_jet;
	
	if(fabs(current_HN1.M() - current_HN2.M()) < min_del_HNHN && j1 != j2){
	  min_del_HNHN = fabs(current_HN1.M() - current_HN2.M());
	  HN_1 = current_HN1;
	  HN_2 = current_HN2;
	}
	current_HN1 = muons[0] + all_jet;
	current_HN2 = muons[1] + jets[j1] + jets[j2];
	if(fabs(current_HN1.M() - current_HN2.M()) < min_del_HNHN && j1 != j2){
	  min_del_HNHN = fabs(current_HN1.M() - current_HN2.M());
	  HN_1 = current_HN1;
	  HN_2 = current_HN2;
	}
      }
    }
  }
  if(HN_1.Pt() > HN_2.Pt()){
    leading_HN = HN_1;
    second_HN = HN_2;
  }
  if(HN_1.Pt() < HN_2.Pt()){
    leading_HN = HN_2;
    second_HN = HN_1;
  }
  
  //OS
  if(muons[0].Charge() != muons[1].Charge()){
    //CR
    Fill("h_llmass_OS", (muons[0]+muons[1]).M(), weight);    
    Fill("h_leadingLeptonPt_OS", muons[0].Pt(), weight);
    Fill("h_secondLeptonPt_OS", muons[1].Pt(), weight);
    Fill("h_leadingLeptonEta_OS", muons[0].Eta(), weight);
    Fill("h_secondLeptonEta_OS", muons[1].Eta(), weight);
    Fill("h_PFMET_OS", ev.PFMET(), weight);             
    Fill("h_PFMET_phi_OS", ev.METPhi(snu::KEvent::pfmet), weight);         
    Fill("h_Njets_OS", jets.size(), weight);             
    Fill("h_Nbjets_OS",nbjet, weight);             
    Fill("h_Nmuons_OS", muons.size(), weight);             
    Fill("h_Nelectrons_OS", electrons.size(), weight);         
    Fill("h_nVertices_OS", ev.nVertices(), weight);
    if(jets.size() > 0);{
      Fill("h_leadingjet_pt_OS", jets[0].Pt(), weight);      
      Fill("h_secondjet_pt_OS", jets[1].Pt(), weight); 
    }
    if(jets.size() > 1){
      Fill("h_leadingjet_eta_OS", jets[0].Eta(), weight);    
      Fill("h_secondjet_eta_OS", jets[1].Eta(), weight);      
    }
    //SR
    if(jets.size() > 3){
      snu::KParticle Zp = muons[0] + muons[1] + jets[0] + jets[1] + jets[2] + jets[3];
      Fill("h_lljjjjmass_OS", Zp.M(), weight);
      Fill("h_lljjjjpt_OS", Zp.Pt(), weight);
      Fill("h_lljjjjeta_SS", Zp.Eta(), weight);
      Fill("h_leadingljjmass_OS", leading_HN.M(), weight);    
      Fill("h_secondljjmass_OS", second_HN.M(), weight);
      Fill("h_leadingljjpt_OS", leading_HN.Pt(), weight); 
      Fill("h_secondljjpt_OS", second_HN.Pt(), weight);   
      Fill("h_leadingljjeta_OS", leading_HN.Eta(), weight); 
      Fill("h_secondljjeta_OS", second_HN.Eta(), weight);      
    }//if SR
  }//if OS
    
  //SS
  if(muons[0].Charge() == muons[1].Charge()){
    //CR
    Fill("h_llmass_SS", (muons[0]+muons[1]).M(), weight);
    Fill("h_leadingLeptonPt_SS", muons[0].Pt(), weight);
    Fill("h_secondLeptonPt_SS", muons[1].Pt(), weight);
    Fill("h_leadingLeptonEta_SS", muons[0].Eta(), weight);
    Fill("h_secondLeptonEta_SS", muons[1].Eta(), weight);
    Fill("h_PFMET_SS", ev.PFMET(), weight);
    Fill("h_PFMET_phi_SS", ev.METPhi(snu::KEvent::pfmet), weight);
    Fill("h_Njets_SS", jets.size(), weight);
    Fill("h_Nbjets_SS",nbjet, weight);
    Fill("h_Nmuons_SS", muons.size(), weight);
    Fill("h_Nelectrons_SS", electrons.size(), weight);
    Fill("h_nVertices_SS", ev.nVertices(), weight);
    if(jets.size() > 0){
      Fill("h_leadingjet_pt_SS", jets[0].Pt(), weight);
      Fill("h_secondjet_pt_SS", jets[1].Pt(), weight);
    }
    if(jets.size() > 1){
      Fill("h_leadingjet_eta_SS", jets[0].Eta(), weight);
      Fill("h_secondjet_eta_SS", jets[1].Eta(), weight);
    }
    //SR
    if(jets.size() > 3){
      snu::KParticle Zp = muons[0] + muons[1] + jets[0] + jets[1] + jets[2] + jets[3];
      Fill("h_lljjjjmass_SS", Zp.M(), weight);
      Fill("h_lljjjjpt_SS", Zp.Pt(), weight);
      Fill("h_lljjjjeta_SS", Zp.Eta(), weight);
      Fill("h_leadingljjmass_SS", leading_HN.M(), weight);
      Fill("h_secondljjmass_SS", second_HN.M(), weight);
      Fill("h_leadingljjpt_SS", leading_HN.Pt(), weight);
      Fill("h_secondljjpt_SS", second_HN.Pt(), weight);
      Fill("h_leadingljjeta_SS", leading_HN.Eta(), weight);
      Fill("h_secondljjeta_SS", second_HN.Eta(), weight);
    }//if SR
  }//if SS

  return;
}/// End of Fill



void HNpairPlotsMM::Write() {
 
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


HNpairPlotsMM::HNpairPlotsMM(): StdPlots(){
}


/**
 * Copy constructor.
 */
HNpairPlotsMM::HNpairPlotsMM(const HNpairPlotsMM& sp): StdPlots(sp)
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


HNpairPlotsMM& HNpairPlotsMM::operator= (const HNpairPlotsMM& sp)
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

HNpairPlotsMM::~HNpairPlotsMM() {
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

void HNpairPlotsMM::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end())   it->second->Fill(value, w);

  else cout << name << " not found in map_sig" << endl;
  return;
}
 
void HNpairPlotsMM::Fill(TString name, double value1, double value2, double w){
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) it->second->Fill(value1, value2, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }



void HNpairPlotsMM::Fill(TString name, double value1, double value2, double value3, double w){
  std::map<TString, TH3*>::iterator it = map_sig3.find(name);
  if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
  else cout << name << " not found in map_sig" << endl;
  return;
}




