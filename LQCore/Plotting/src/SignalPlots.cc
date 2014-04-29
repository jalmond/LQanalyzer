#include "SignalPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SignalPlots::SignalPlots(TString name, Channel channel): StdPlots(name){
  
  map_sig["h_jjmass"] =         new TH1F("h_dijetsmass_"    + name,"Invariant mass of the two leading jets",250,0.,500.);
  map_sig["h_leadjetmass"] =         new TH1F("h_leadjetsmass_"    + name,"Invariant mass of the two leading jets",250,0.,500.);
  if(channel == ee ){
    map_sig["h_eemass"] =         new TH1F("h_eemass_"        + name,"Invariant mass of the two leading electrons",250,0.,500.);
    map_sig["h_e1jjmass"] =       new TH1F("h_e1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0.,1000.);
    map_sig["h_e2jjmass"] =       new TH1F("h_e2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0.,1000.);
    map_sig["h_eejjmass"] =       new TH1F("h_eejjmass_"      + name,"Invariant mass of the four particles",200,0.,2000.);
  }
  if(channel == mumu){
    map_sig["h_mumumass"] =         new TH1F("h_mumumass_"        + name,"Invariant mass of the two leading muons",250,0,500);
    map_sig["h_mu1jjmass"] =        new TH1F("h_mu1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
    map_sig["h_mu2jjmass"] =        new TH1F("h_mu2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
    map_sig["h_mumujjmass"] =       new TH1F("h_mumujjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  }
  if(channel == emu ){
    map_sig["h_emumass"] =         new TH1F("h_emumass_"        + name,"Invariant mass of the two leading leptons",250,0,500);
    map_sig["h_ejjmass"] =       new TH1F("h_e1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
    map_sig["h_mujjmass"] =       new TH1F("h_mu1jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
    map_sig["h_emujjmass"] =       new TH1F("h_emujjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
  }
  
  if(channel==ALL){
    map_sig["h_eemass"] =         new TH1F("h_eemass_"        + name,"Invariant mass of the two leading electrons",250,0,500);
    map_sig["h_e1jjmass"] =       new TH1F("h_e1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
    map_sig["h_e2jjmass"] =       new TH1F("h_e2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
    map_sig["h_eejjmass"] =       new TH1F("h_eejjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
    map_sig["h_mumumass"] =         new TH1F("h_mumumass_"        + name,"Invariant mass of the two leading muons",250,0,500);
    map_sig["h_mu1jjmass"] =        new TH1F("h_mu1jjmass_"      + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
    map_sig["h_mu2jjmass"] =        new TH1F("h_mu2jjmass_"      + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
    map_sig["h_mumujjmass"] =       new TH1F("h_mumujjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
    map_sig["h_emumass"] =         new TH1F("h_emumass_"        + name,"Invariant mass of the two leading leptons",250,0,500);
    map_sig["h_emujjmass"] =       new TH1F("h_emujjmass_"      + name,"Invariant mass of the four particles",200,0,2000);
    
    map_sig["h_leadingMuonPt"] =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
    map_sig["h_secondMuonPt"] =   new TH1F("h_secondMuonPt_"  + name,"secondary muon pt",60,0,300);
    map_sig["h_leadingMuonIso"] = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
    map_sig["h_secondMuonIso"] =  new TH1F("h_secondMuonIso_" + name,"secondary muon relIso",40,0,0.4);
    map_sig["h_MuonD0"] = new TH1F("h_MuonD0_" + name," muon D0", 400, -0.5 , 0.5);
    map_sig["h_MuonDxy"] = new TH1F("h_MuonDxy_" + name," muon D0", 400, -0.5 , 0.5);
    map_sig["h_MuonDz"] = new TH1F("h_MuonDz_" + name," muon D0", 400, -0.5 , 0.5);
    map_sig["h_MuonD0Sig"] = new TH1F("h_MuonD0Sig_" + name," muon SigD0", 100, -10. , 10.);
    map_sig["h_ElectronPt"] =  new TH1F("h_ElectronPt_" + name,"leading electron pt",60,0,300);
    map_sig["h_leadingElectronPt"] =  new TH1F("h_leadingElectronPt_" + name,"leading electron pt",60,0,300);
    map_sig["h_secondElectronPt"] =   new TH1F("h_secondElectronPt_"  + name,"secondary electron pt",60,0,300);
    map_sig["h_ElectronIso"] = new TH1F("h_ElectronIso_"+ name,"leading electron relIso",40,0,0.4);
    map_sig["h_leadingElectronIso"] = new TH1F("h_leadingElectronIso_"+ name,"leading electron relIso",40,0,0.4);
    map_sig["h_secondElectronIso"] =  new TH1F("h_secondElectronIso_" + name,"secondary electron relIso",40,0,0.4);
    map_sig["h_ElectronD0"] = new TH1F("h_ElectronD0_" + name," leading electron D0", 400, -0.5 , 0.5);
    map_sig["h_ElectronD0Sig"] = new TH1F("h_ElectronD0Sig_" + name," leading electron SigD0", 100, -10. , 10.);
    map_sig["h_ElectronD0Sig2"] = new TH1F("h_ElectronD0Sig2_" + name," leading electron SigD0", 100, -10. , 10.);
    map_sig["h_ElectronD0Sig2_2"] = new TH1F("h_ElectronD0Sig2_2" + name," leading electron SigD0_2", 100, -30. , 30.);
    map_sig["h_ElectronD0Sig3"] = new TH1F("h_ElectronD0Sig3_" + name," leading electron SigD0", 100, -10. , 10.);
    
    
  }
  
  map_sig2["h_WandNmass"] =      new TH2F("h_WandNmass_"     + name,"Invariant mass of the W and the N",200,0,2000,200,0,2000);
  map_sig3["h_3Dparm"] =         new TH3F("h_3Dpar_"         + name,"m(lljj) and muon p_{T}_{1} and muon p_{T}_{2}",200,0,2000,60,0,300,60,0,300);
  
  map_sig["h_MuonJetdR"] =  new TH1F("h_MuonJetdR_" + name,"muon jet dR",500,0,5);
  map_sig["h_ElectronJetdR"] =  new TH1F("h_ElectronJetdR_" + name,"electron jet dR",500,0,5);
  map_sig["h_leadMuondR"] =  new TH1F("h_leadMuondR_" + name,"leading muon dR",500,0,5);
  map_sig["h_leadElectrondR"] =  new TH1F("h_leadElectrondR_" + name,"leading electron dR",500,0,5);
  map_sig["h_leadJetdR"] =  new TH1F("h_leadJetdR_" + name,"leading jet dR",500,0,5);
  
  if(channel == mumu ){
    map_sig["h_leadingMuonPt"] =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
    map_sig["h_secondMuonPt"] =   new TH1F("h_secondMuonPt_"  + name,"secondary muon pt",60,0,300);
    map_sig["h_leadingMuonIso"] = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
    map_sig["h_secondMuonIso"] =  new TH1F("h_secondMuonIso_" + name,"secondary muon relIso",40,0,0.4);
    map_sig["h_MuonD0"] = new TH1F("h_MuonD0_" + name," muon D0", 400, -0.5 , 0.5);
    map_sig["h_MuonD0Sig"] = new TH1F("h_MuonD0Sig_" + name," muon SigD0", 100, -10. , 10.);
  }
  if(channel ==ee){
    map_sig["h_leadingElectronPt"] =  new TH1F("h_leadingElectronPt_" + name,"leading electron pt",60,0,300);
    map_sig["h_secondElectronPt"] =   new TH1F("h_secondElectronPt_"  + name,"secondary electron pt",60,0,300);
    map_sig["h_leadingElectronIso"] = new TH1F("h_leadingElectronIso_"+ name,"leading electron relIso",40,0,0.4);
    map_sig["h_secondElectronIso"] =  new TH1F("h_secondElectronIso_" + name,"secondary electron relIso",40,0,0.4);
    map_sig["h_ElectronD0"] = new TH1F("h_ElectronD0_" + name," leading electron D0", 400, -0.5 , 0.5);
    map_sig["h_ElectronD0Sig"] = new TH1F("h_ElectronD0Sig_" + name," leading electron SigD0", 100, -10. , 10.);
  }
  if(channel == emu) {
    map_sig["h_leadingMuonPt"] =  new TH1F("h_leadingMuonPt_" + name,"leading muon pt",60,0,300);
    map_sig["h_leadingElectronPt"] =  new TH1F("h_leadingElectronPt_" + name,"leading electron pt",60,0,300);
    map_sig["h_leadingMuonIso"] = new TH1F("h_leadingMuonIso_"+ name,"leading muon relIso",40,0,0.4);
    map_sig["h_leadingElectronIso"] = new TH1F("h_leadingElectronIso_"+ name,"leading electron relIso",40,0,0.4);
    map_sig["h_MuonD0"] = new TH1F("h_MuonD0_" + name," muon D0", 400, -0.5 , 0.5);
    map_sig["h_MuonD0Sig"] = new TH1F("h_MuonD0Sig_" + name," muon SigD0", 100, -10. , 10.);
    map_sig["h_ElectronD0"] = new TH1F("h_ElectronD0_" + name," leading electron D0", 400, -0.5 , 0.5);
    map_sig["h_ElectronD0Sig"] = new TH1F("h_ElectronD0Sig_" + name," leading electron SigD0", 100, -10. , 10.);
  }
  
  map_sig["h_leadingJetPt"] =   new TH1F("h_leadingJetPt_"  + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"] =    new TH1F("h_secondJetPt_"   + name,"secondary jet pt",60,0,300);
  
  
  map_sig["h_MTmuon"] =            new TH1F("h_MTmuon_"           + name,"Mt",100,0.0,500.0);
  map_sig["h_MTelectron"] =        new TH1F("h_MTelectron_"           + name,"Mt",100,0.0,500.0);
  map_sig["h_MET"] =               new TH1F("h_MET_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_caloMET"] =           new TH1F("h_caloMET_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_tcMET"] =            new TH1F("h_tcMET_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METraw"] =            new TH1F("h_METraw_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METtype1"] =            new TH1F("h_METtype1_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METtype01"] =            new TH1F("h_METtype01_"           + name,"Missing Et",100,0.0,500.0);
  map_sig["h_MET_phi"] =        new TH1F("h_MET_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_caloMET_phi"] =        new TH1F("h_caloMET_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METraw_phi"] =        new TH1F("h_METraw_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METtype1_phi"] =        new TH1F("h_METtype1_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METtype01_phi"] =        new TH1F("h_METtype01_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_SumET"] =          new TH1F("h_SumET_"           + name,"Sum Et",100,0.0,500.0);
  map_sig["h_nVertices"] =      new TH1F("h_nVertices_"           + name,"number of even vertices",60,0.0,60.0);
  

  map_sig["h_muoncharge"] =     new TH1F("h_muoncharge_"    + name,"Charge of the muon pair",5,-2,3);
  map_sig["h_electroncharge"] =     new TH1F("h_electroncharge_"    + name,"Charge of the muon pair",5,-2,3);

  map_sig["h_muons_eta"] =       new TH1F("h_muons_eta_"      + name,"#eta distribution of the two muons",50,-3,3);
  map_sig["h_electrons_eta"] =       new TH1F("h_electrons_eta_"      + name,"#eta distribution of the two electrons",50,-3,3);
  map_sig["h_electrons_sceta"] =       new TH1F("h_electrons_sceta_"      + name,"#eta distribution of the two electrons",50,-3,3);
  
  map_sig["h_muons_phi"] =       new TH1F("h_muons_phi_"      + name,"#phi distribution of the two muons",50,-3,3);
  map_sig["h_electrons_phi"] =       new TH1F("h_electrons_phi_"      + name,"#phi distribution of the two electrons",140,-3.5,3.5);
  map_sig["h_electrons_scphi"] =       new TH1F("h_electrons_scphi_"      + name,"#phi distribution of the two electrons",50,-3,3);
  
  map_sig["h_jets_eta"] =        new TH1F("h_jets_eta_"       + name,"#eta distribution of the two jets",120,-3,3);
  map_sig["h_jets_phi"] =        new TH1F("h_jets_phi_"       + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"] =        new TH1F("h_pileupJetIDMVA_"   + name, "" ,100., -1.,1.);
  map_sig["h_bTag"] =           new TH1F("h_bTag_"          + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"] =          new TH1F("h_Njets_"         + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"] =         new TH1F("h_Nbjets_"        + name,"number of b jets",5,0,5);
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
  

  float min_ee_Dr=10000.;
  for(UInt_t i=0; i<electrons.size(); i++){
    for(UInt_t j=0; j<electrons.size(); j++){
      if(i==j) continue;
      float dR =electrons[i].DeltaR(electrons[j]);
      if(dR < min_ee_Dr) min_ee_Dr = dR;
    }
  }

  float min_mm_Dr=10000.;
  for(UInt_t i=0; i<muons.size(); i++){
    for(UInt_t j=0; j<muons.size(); j++){
      if(i==j) continue;
      float dR =muons[i].DeltaR(muons[j]);
      if(dR < min_mm_Dr) min_mm_Dr = dR;
    }
  }
  
  float min_jj_Dr=10000.;
  for(UInt_t i=0; i<jets.size(); i++){
    for(UInt_t j=0; j<jets.size(); j++){
      if(i==j) continue;
      float dR =jets[i].DeltaR(jets[j]);
      if(dR < min_jj_Dr) min_jj_Dr = dR;
    }
  }
  
  if(jets.size()!=0){
    Fill("h_MuonJetdR",min_mujet_Dr,weight);
    Fill("h_ElectronJetdR",min_ejet_Dr,weight);
    Fill("h_leadElectrondR",min_ee_Dr,weight);
    Fill("h_leadMuondR",min_mm_Dr,weight);
    if(jets.size() > 1)Fill("h_leadJetdR",min_jj_Dr,weight);
  }
  
  int nbjet=0;
  /// use CSVM https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
  float leadjetmass=0.;
  for(UInt_t emme=0; emme<jets.size(); emme++){
    
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if(emme==0 && enne == 1) leadjetmass = dijetmass_tmp;
      if ( fabs(dijetmass_tmp-Mass_W) < fabs(dijetmass-Mass_W) ) {
	dijetmass = dijetmass_tmp;
	m = emme;
	n = enne;
      }
    }
  }
  
  if(leadjetmass != 0.)Fill("h_leadjetmass", leadjetmass,weight);
  
  

  if(muons.size()==2){     
    Fill("h_mumumass", (muons[0]+muons[1]).M(),weight);
    if(jets.size()>1){
      Fill("h_mu1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
      Fill("h_mu2jjmass", (muons[1]+jets[m]+jets[n]).M(),weight);      
      Fill("h_mumujjmass", (muons[0]+muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (muons[0]+muons[1]+jets[m]+jets[n]).M() , (muons[1]+jets[m]+jets[n]).M(),weight);      
    }
    Fill("h_3Dparm", (muons[0]+muons[1]+jets[m]+jets[n]).M(), muons[0].Pt(), muons[1].Pt(), weight); 
  }
  
  int imu(0);
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit != muons.end(); muit++, imu++){
    
    float mureliso = (muit->SumIsoCHDR03() + std::max(0.0, muit->SumIsoNHDR03() + muit->SumIsoPHDR03() - 0.5* muit->SumPUIsoR03()))/muit->Pt();
    
    Fill("h_MuonD0", muit->dXYPat(),weight);
    Fill("h_MuonDxy", muit->dXY(),weight);
    Fill("h_MuonDz", muit->dZ(),weight);
    Fill("h_MuonD0Sig", (muit->dXYPat()/ muit->D0Err()),weight);
    Fill("h_muons_eta",muit->Eta(),weight);
    Fill("h_muons_phi",muit->Phi(),weight);

    if(imu==1){
      Fill("h_secondMuonPt", muit->Pt(),weight);
      Fill("h_secondMuonIso", mureliso,weight);
    }
    if(imu==0){
      Fill("h_leadingMuonPt", muit->Pt(),weight);
      Fill("h_leadingMuonIso", mureliso,weight);
    }

    Fill("h_muoncharge",muit->Charge(),weight);
  }
  
    
  if(electrons.size()==2){
    Fill("h_eemass", (electrons[0]+electrons[1]).M(),weight);
    if(fabs(electrons[0].Charge()) !=  1.) std::cout << "Electron charge = " << electrons[0].Charge() << std::endl;
    Fill("h_electroncharge",electrons[0].Charge(),weight);
    if(jets.size()>1){
      Fill("h_e1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
      Fill("h_e2jjmass", (electrons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_eejjmass", (electrons[0] + electrons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_WandNmass", (electrons[0]+electrons[1]+jets[m]+jets[n]).M() , (electrons[1]+jets[m]+jets[n]).M(),weight);      
      Fill("h_3Dparm", (electrons[0]+electrons[1]+jets[m]+jets[n]).M(), electrons[0].Pt(), electrons[1].Pt(), weight); 
    }
  }
  int iel(0);
  for(std::vector<snu::KElectron>::iterator elit = electrons.begin(); elit != electrons.end(); elit++, iel++){
    Fill("h_electrons_phi",elit->Phi(),weight);
    Fill("h_electrons_scphi",elit->SCPhi(),weight);
    Fill("h_electrons_eta",elit->Eta(),weight);
    Fill("h_electrons_sceta",elit->SCEta(),weight);
    Fill("h_ElectronD0", elit->PrimaryVertexDXY(),weight);
    Fill("h_ElectronD0Sig", (elit->PrimaryVertexDXY()/ elit->PrimaryVertexDXYError()),weight);
    Fill("h_ElectronD0Sig2", (elit->LeadVtxDistXY()/ elit->PrimaryVertexDXYError()),weight);
    Fill("h_ElectronD0Sig2_2", (elit->LeadVtxDistXY()/ pow(elit->PrimaryVertexDXYError(), 2.)),weight);
    Fill("h_ElectronD0Sig3", (elit->dxy()/ elit->PrimaryVertexDXYError()),weight);

    

    float EA=GetElectronISOEA(elit->SCEta());
    float rho = ev.JetRho();
    float el_reliso =  elit->PFChargedHadronIso03() + max( elit->PFNeutralHadronIso03() + elit->PFPhotonIso03() - rho * EA, 0.);
    
    Fill("h_ElectronPt", elit->Pt(),weight);
    Fill("h_ElectronIso", el_reliso/elit->Pt(),weight);
    if(iel==1){
      Fill("h_secondElectronPt", elit->Pt(),weight);
      Fill("h_secondElectronIso", el_reliso/elit->Pt(),weight);
    }
    if(iel==0){
      Fill("h_leadingElectronPt", elit->Pt(),weight);
      Fill("h_leadingElectronIso", el_reliso/elit->Pt() ,weight);
    }

  }
  
  
  if(muons.size()==1 && electrons.size()==1){
    Fill("h_emumass", (electrons[0]+muons[0]).M(),weight);
    Fill("h_muoncharge",muons[0].Charge(),weight);
    Fill("h_electroncharge",electrons[0].Charge(),weight);
    if(jets.size()>1)Fill("h_emujjmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M(),weight);

    if(jets.size()>1){
      if(muons[0].Pt() > electrons[0].Pt()){
	Fill("h_emujjmass", (electrons[0] + muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_mu1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_e1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_WandNmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M() , (electrons[0]+jets[m]+jets[n]).M(),weight);      
      } 
      else{
	Fill("h_e1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_mu1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_emujjmass", (electrons[0] + muons[0]+jets[m]+jets[n]).M(),weight);
	Fill("h_WandNmass", (muons[0]+electrons[0]+jets[m]+jets[n]).M() , (muons[0]+jets[m]+jets[n]).M(),weight);      
      }
    }
  }
  
  //// Fillplots

  for(unsigned int i=0 ; i < electrons.size(); i++){
    float MT = sqrt(2.* electrons.at(i).Et()*ev.PFMET() * (1 - cos( electrons.at(i).Phi()- ev.PFMETphi())) );
    Fill("h_MTelectron",MT, weight);
  }
  for(unsigned int i=0 ; i < muons.size(); i++){
    float MT = sqrt(2.* muons.at(i).Et()*ev.PFMET() * (1 - cos( muons.at(i).Phi()- ev.PFMETphi())) );
    Fill("h_MTmuon",MT, weight);
  }

  Fill("h_MET",ev.PFMET(), weight);
  Fill("h_METraw",ev.PFMETRaw(), weight);
  Fill("h_METtype1",ev.PFMETType1(), weight);
  Fill("h_METtype01",ev.PFMETType01(), weight);
  Fill("h_caloMET",ev.CaloMET(), weight);
  Fill("h_tcMET",ev.TCMET(), weight);
  Fill("h_MET_phi",ev.PFMETphi(), weight);
  Fill("h_caloMET_phi",ev.CaloMETphi(), weight);
  Fill("h_METraw_phi",ev.PFMETRawphi(), weight);
  Fill("h_METtype1_phi",ev.PFMETType1phi(), weight);
  Fill("h_METtype01_phi",ev.PFMETType01phi(), weight);
  Fill("h_SumET",ev.PFSumET(), weight);
  Fill("h_nVertices", ev.nVertices(), weight);
  
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight); 
  }
  
  for(UInt_t j=0; j < jets.size(); j++){ 
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    Fill("h_jets_eta",jets[j].Eta(),weight);
    Fill("h_PileupJetIDMVA", jets[j].PileupJetIDMVA(),weight);
    Fill("h_jets_phi",jets[j].Phi(),weight);
    Fill("h_bTag",jets[j].BtagProb(),weight);
    if(jets.at(j).BtagProb() > 0.679) nbjet++; 
  }
  
  Fill("h_Nbjets",nbjet, weight);
  Fill("h_Njets",jets.size(), weight);
  
  return;
}/// End of Fill


void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  
  return;
}
  
float SignalPlots::GetElectronISOEA(float eta){

  Float_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
  int ifid=0;
  if (fabs(eta) < 1.0) ifid = 0;
  else if (fabs(eta) < 1.479) ifid = 1;
  else if (fabs(eta) < 2.0) ifid = 2;
  else if (fabs(eta) < 2.2) ifid = 3;
  else if (fabs(eta) < 2.3) ifid = 4;
  else if (fabs(eta) < 2.4) ifid = 5;
  else ifid = 6;
  
  return PHONH_03[ifid];
}
void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KJet>& jets, Double_t weight){
  
  return;
}

void SignalPlots::Write() {
 
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

  for(std::map<TString, TH2*>::iterator mit = map_sig2.begin(); mit != map_sig2.end() ; mit++){
    std::map<TString, TH2*>::iterator mit2 = sp.GetMap2().find(mit->first);
    mit->second = mit2->second;
  }

  for(std::map<TString, TH3*>::iterator mit = map_sig3.begin(); mit != map_sig3.end() ; mit++){
    std::map<TString, TH3*>::iterator mit2 = sp.GetMap3().find(mit->first);
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

SignalPlots::~SignalPlots() {
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




