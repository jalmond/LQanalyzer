#include "SignalPlotsMM.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SignalPlotsMM::SignalPlotsMM(TString name): StdPlots(name){

  TH1::SetDefaultSumw2(true);

 
  /// Mass plots
  map_sig["h_jjmass"]                 =     new TH1F("h_dijetsmass_"        + name,"Invariant mass of the two leading jets",100,0.,500.);
  map_sig["h_leadjetmass"]            =     new TH1F("h_leadjetsmass_"      + name,"Invariant mass of the two leading jets",150,0.,750.);
  map_sig["h_oseemass"]               =     new TH1F("h_osllmass_"          + name,"Invariant mass of the two leading os muons",100,0,500);
  map_sig["h_e1jjmass"]               =     new TH1F("h_l1jjmass_"          + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_e2jjmass"]               =     new TH1F("h_l2jjmass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_eemass"]                 =     new TH1F("h_llumass_"           + name,"Invariant mass of the two leading muons",200,0,1000);
  map_sig["h_eejjmass"]               =     new TH1F("h_lljjmass_"         + name,"Invariant mass of the four particles",200,0,2000);
  
  /// Muon plots  
  map_sig["h_MuonEta"]              =     new TH1F("h_LeptonEta_"         + name,"leading muon eta",60,-3.,3.);
  map_sig["h_MuonPt"]               =     new TH1F("h_LeptonPt_"          + name,"muon pt",100,0,500);
  map_sig["h_leadingMuonPt"]        =     new TH1F("h_leadingLeptonPt_"   + name,"leading muon pt",100,0,500);
  map_sig["h_secondMuonPt"]         =     new TH1F("h_secondLeptonPt_"    + name,"secondary muon pt",60,0,300);
  map_sig["h_leadingMuonEta"]       =     new TH1F("h_leadingLeptonEta_"  + name,"leading muon eta",60,-3.,3.);
  map_sig["h_secondMuonEta"]        =     new TH1F("h_secondLeptonEta_"   + name,"second muon eta",60,-3.,3.);
  map_sig["h_MuonIso"]              =     new TH1F("h_LeptonIso_"         + name,"leading muon relIso",50,0,10.);
  map_sig["h_MuonRelIso"]           =     new TH1F("h_LeptonRelIso_"      + name,"leading muon relIso",100,0,1.);
  map_sig["h_MuonDZ"]               =     new TH1F("h_LeptonDZ_"          + name," leading muon DZ", 400, -0.5 , 0.5);
  map_sig["h_MuonDXY"]              =     new TH1F("h_LeptonDXY_"         + name," leading muon DXY", 1000, -0.25 , 0.25);
  
  
  /// Muon/Jet/Muon dR
  map_sig["h_MuonJetdR"]            =     new TH1F("h_LeptonJetdR_"       + name,"muon jet dR",50,0,5);
  map_sig["h_MuonAwayJetdR"]        =     new TH1F("h_LeptonAwayJetdR_"   + name, "away jet dr", 50,0,5);
  map_sig["h_leadMuondR"]           =     new TH1F("h_leadLeptondR_"      + name,"leading lepton dR",50,0,5);
  map_sig["h_leadMuondPhi"]         =     new TH1F("h_leadLeptondPhi_"    + name,"leading muon dPhi",50,-5,5);
  map_sig["h_leadJetdR"]                =     new TH1F("h_leadJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetdPhi"]              =     new TH1F("h_leadJetdPhi_"       + name,"leading jet dPhi",50,-5,5);

  //// Jet Plots
  map_sig["h_leadingJetPt"]           =     new TH1F("h_leadingJetPt_"      + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"]            =     new TH1F("h_secondJetPt_"       + name,"secondary jet pt",60,0,300);
  map_sig["h_HT"]                     =     new TH1F("h_HT_"                + name,"sum jet pt",50,0,1000);
  map_sig["h_ST"]                     =     new TH1F("h_ST_"                + name,"sum event pt",50,0,1000);
  map_sig["h_jets_pt"]                =     new TH1F("h_jets_pt_"           + name,"jet pt",60,0,300);
  map_sig["h_jets_eta"]               =     new TH1F("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-3,3);
  map_sig["h_jets_phi"]               =     new TH1F("h_jets_phi_"          + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"]         =     new TH1F("h_pileupJetIDMVA_"    + name, "" ,100, -1.,1.);
  map_sig["h_bTag"]                   =     new TH1F("h_bTag_"              + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"]                  =     new TH1F("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]                 =     new TH1F("h_Nbjets_"            + name,"number of b jets",5,0,5);

  /// dPhi/MT
  map_sig["h_MTmuon"]               =     new TH1F("h_MTlepton_"        + name,"Mt",100,0.0,500.0);
  map_sig["h_dphi_METmuon"]         =     new TH1F("h_dphi_METlepton_"  + name , "METlepdphi", 50, -5., 5.);
 
  
  /// MET plots
  map_sig["h_PFMET"]                  =     new TH1F("h_PFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_PFMET_phi"]              =     new TH1F("h_PFMET_phi_"           + name,"Missing Et",100,0.0,500.0);

  map_sig["h_NoHFMET"]              =     new TH1F("h_NoHFMET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_NoHFMET_phi"]          =     new TH1F("h_NoHFMET_phi_"           + name,"Missing Et",100,0.0,500.0);


  map_sig["h_nVertices"]              =     new TH1F("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  /// Charge plot
  map_sig["h_sumcharge"]              =     new TH1F("h_sumcharge_"         + name,"Charge of the muon pair",6,-3,3);

  /// Number of objects
  map_sig["h_Nmuons"]                 =     new TH1F("h_Nmuons_"           + name,"number of mu",5,0,5);
  map_sig["h_Nelectrons"]             =     new TH1F("h_Nelectrons_"           + name,"number of el",5,0,5);


  map_sig["h_Nvtx"]                   =     new TH1F("h_Nvtx_"            + name,"number of vertices",40,0,40.);


}




void SignalPlotsMM::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  
  bool debug =false;
  if(debug)cout<< "Plotting [1] " << endl;
  Fill("h_Nelectrons", electrons.size(), weight);
  Fill("h_Nmuons", muons.size(), weight);
  

  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);
  
  float min_ejet_Dr=10000.;  
  float min_eleadawayjet_Dr= -10000.;
  for(UInt_t i=0; i<muons.size(); i++){ 
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =muons[i].DeltaR(jets[emme]);
      //float dphi = fabs(TVector2::Phi_mpi_pi(muons[i].Phi()- jets[emme].Phi()));
      if(dR > 0.5) {
	if(dR > min_eleadawayjet_Dr) min_eleadawayjet_Dr=  dR;
      }
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;

    }
  }
  
  

    
  float min_ee_Dr=10000.;
  float min_ee_DPhi=10000.;
  for(UInt_t i=0; i<muons.size(); i++){
     for(UInt_t j=0; j<muons.size(); j++){
      if(i==j) continue;
      float dPhi = fabs(TVector2::Phi_mpi_pi(muons[i].Phi() - muons[j].Phi() ));
      float dR =muons[i].DeltaR(muons[j]);
      if(dR < min_ee_Dr) min_ee_Dr = dR;
      if(dPhi < min_ee_DPhi) min_ee_DPhi = dPhi;
     }
  }

  
  float min_jj_Dr=10000.;
  float min_jj_DPhi=10000.;
  for(UInt_t i=0; i<jets.size(); i++){
    for(UInt_t j=0; j<jets.size(); j++){
      if(i==j) continue;
      float dR =jets[i].DeltaR(jets[j]);
      float dPhi = fabs(TVector2::Phi_mpi_pi(jets[i].Phi() - jets[j].Phi()));
      if(dR < min_jj_Dr) min_jj_Dr = dR;
      if(dR < min_jj_DPhi) min_jj_DPhi = dPhi;
    }
  }

  
  if(muons.size()!=0)Fill("h_leadMuondR",min_ee_Dr,weight);
  if(muons.size()!=0)Fill("h_leadMuondPhi",min_ee_DPhi,weight);


  if(jets.size()!=0){
    if(muons.size()!=0){
      Fill("h_MuonJetdR",min_ejet_Dr,weight);
      Fill("h_MuonAwayJetdR",min_eleadawayjet_Dr,weight);
    }
    if(jets.size() > 1)Fill("h_leadJetdR",min_jj_Dr,weight);
    if(jets.size() > 1)Fill("h_leadJetdPhi",min_jj_DPhi,weight);
  }

  if(debug)cout<< "Plotting [2] " << endl;  
  int nbjet=0;
  /// use CSVM https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
  float leadjetmass=0.;
  for(UInt_t emme=0; emme<jets.size(); emme++){
    
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if(emme==0 && enne == 1) leadjetmass = dijetmass_tmp;
      if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {
	dijetmass = dijetmass_tmp;
	m = emme;
	n = enne;
      }
    }
  }

  
  if(leadjetmass != 0.)Fill("h_leadjetmass", leadjetmass,weight);
  
  if(debug)cout<< "Plotting [3] " << endl;  

   int sum_charge(0);
   
  if(muons.size()>=2){
    Fill("h_llmass", (muons[0]+muons[1]).M(),weight);
    if( jets.size()==1) Fill("h_lljmass", (muons[0] + muons[1]+jets[0]).M(),weight);
    if(jets.size()>1){
      Fill("h_l2jjmass", (muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_lljjmass", (muons[0] + muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_l1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);

    }
  }
  if(muons.size()>=2){
      if(muons[0].Charge() != muons[1].Charge())   Fill("h_oseemass", (muons[0]+muons[1]).M(),weight);
  }
  
  int iel(0);
 
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit != muons.end(); muit++, iel++){
  
    Fill("h_MuonPt", muit->Pt(),weight);
    Fill("h_Muons_phi",muit->Phi(),weight);
    Fill("h_Muons_eta",muit->Eta(),weight);
    Fill("h_MuonDXY", muit->dXY(),weight);
    Fill("h_MuonDZ", muit->dZ(),weight);
     
    float mu_reliso_03 =  muit->RelIso03();
    
    
    Fill("h_MuonRelIso", mu_reliso_03,weight);
    if(iel==1){
      Fill("h_secondMuonPt", muit->Pt(),weight);
      Fill("h_secondMuonIso", mu_reliso_03,weight);
      Fill("h_secondMuonEta",muit->Eta(),weight);
    }
    if(iel==0){
      Fill("h_leadingMuonEta",muit->Eta(),weight);
      Fill("h_leadingMuonIso", mu_reliso_03,weight);
      Fill("h_leadingMuonPt", muit->Pt(),weight);
    }
    
    sum_charge += muit->Charge();
  }
  
  Fill("h_sumcharge",sum_charge,weight);
  
  //// Fillplots
  for(unsigned int i=0 ; i < muons.size(); i++){
    float dphi = fabs(TVector2::Phi_mpi_pi(muons.at(i).Phi()- ev.PFMETphi()));
    float MT = sqrt(2.* muons.at(i).Et()*ev.PFMET() * (1 - cos( dphi)));
    Fill("h_MTmuon",MT, weight);
    Fill("h_dphi_METmuon",dphi, weight);
  }

  if(debug)cout<< "Plotting [5] " << endl;

  Fill("h_PFMET",ev.PFMET(), weight);
  Fill("h_PFMET_phi",ev.PFMETphi(), weight);
  Fill("h_nVertices", ev.nVertices(), weight);
  

  Fill("h_NoHFMET",ev.NoHFMET(), weight);
  Fill("h_NoHFMET_phi",ev.NoHFMETphi(), weight);

  
  Fill("h_Nvtx",ev.nVertices(), weight);
  
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight); 
  }
  float ht=0.;
  for(UInt_t j=0; j < jets.size(); j++){ 
    ht+= jets[j].Pt();
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    Fill("h_jets_pt", jets[j].Pt(),weight);
    Fill("h_jets_eta",jets[j].Eta(),weight);
    Fill("h_PileupJetIDMVA", jets[j].PileupJetIDMVA(),weight);
    Fill("h_jets_phi",jets[j].Phi(),weight);
    Fill("h_bTag",jets[j].CVSInclV2(),weight);
    if(jets.at(j).CVSInclV2() > 0.89) nbjet++; 
  }
  
  float st = ht + ev.PFMET();
  for(unsigned int i=0 ; i < muons.size(); i++){
    st+= muons.at(i).Pt();
  }
  
  Fill("h_HT", ht,weight);
  Fill("h_ST", st,weight);
  Fill("h_Nbjets",nbjet, weight);
  Fill("h_Njets",jets.size(), weight);
  
  if(debug)cout<< "Plotting [6] " << endl;
  return;
}/// End of Fill



void SignalPlotsMM::Write() {
 
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


SignalPlotsMM::SignalPlotsMM(): StdPlots(){
}


/**
 * Copy constructor.
 */
SignalPlotsMM::SignalPlotsMM(const SignalPlotsMM& sp): StdPlots(sp)
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


SignalPlotsMM& SignalPlotsMM::operator= (const SignalPlotsMM& sp)
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

SignalPlotsMM::~SignalPlotsMM() {
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

void SignalPlotsMM::Fill(TString name, double value, double w){
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end())   it->second->Fill(value, w);

  else cout << name << " not found in map_sig" << endl;
  return;
}
 
void SignalPlotsMM::Fill(TString name, double value1, double value2, double w){
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) it->second->Fill(value1, value2, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }



void SignalPlotsMM::Fill(TString name, double value1, double value2, double value3, double w){
  std::map<TString, TH3*>::iterator it = map_sig3.find(name);
  if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
  else cout << name << " not found in map_sig" << endl;
  return;
}




