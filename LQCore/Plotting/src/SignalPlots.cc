#include "SignalPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SignalPlots::SignalPlots(TString name): StdPlots(name){

  TH1::SetDefaultSumw2(true);
  
  /// Mass plots
  map_sig["h_jjmass"]              =     new TH1F("h_dijetsmass_"        + name,"Invariant mass of the two leading jets",100,0.,500.);
  map_sig["h_leadjetmass"]         =     new TH1F("h_leadjetsmass_"      + name,"Invariant mass of the two leading jets",150,0.,750.);
  map_sig["h_eemass"]              =     new TH1F("h_eemass_"            + name,"Invariant mass of the two leading electrons",200,0,1000);
  map_sig["h_oseemass"]            =     new TH1F("h_oseemass_"            + name,"Invariant mass of the two leading os electrons",100,0,500);
  map_sig["h_e1jjmass"]            =     new TH1F("h_e1jjmass_"          + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_e2jjmass"]            =     new TH1F("h_e2jjmass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_l1jjmass"]            =     new TH1F("h_l1jjmass_"          + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_l2jjmass"]            =     new TH1F("h_l2jjmass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_l1jj_lowmass"]            =     new TH1F("h_l1jj_lowmass_"          + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_l2jj_lowmass"]            =     new TH1F("h_l2jj_lowmass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_eejjmass"]            =     new TH1F("h_eejjmass_"          + name,"Invariant mass of the four particles",200,0,2000);
  map_sig["h_eejmass"]            =     new TH1F("h_eejmass_"          + name,"Invariant mass of the four particles",200,0,2000);
  map_sig["h_emumass"]             =     new TH1F("h_emumass_"           + name,"Invariant mass of the two leading leptons",200,0,1000);
  map_sig["h_emujjmass"]           =     new TH1F("h_emujjmass_"         + name,"Invariant mass of the four particles",200,0,2000);
  map_sig["h_emujj_lowmass"]           =     new TH1F("h_emujj_lowmass_"         + name,"Invariant mass of the four particles",200,0,2000);
  map_sig["h_mujjmass"]           =     new TH1F("h_mujjmass_"         + name,"Invariant mass of the four particles",200,0,2000);

  map_sig["h_l1jj_central_mass"]            =     new TH1F("h_l1jj_central_mass_"          + name,"Invariant mass of the two leading jets and leading muon",100,0,1000);
  map_sig["h_l2jj_central_mass"]            =     new TH1F("h_l2jj_central_mass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);
  map_sig["h_lljj_central_mass"]            =     new TH1F("h_lljj_central_mass_"          + name,"Invariant mass of the two leading jets and second muon",100,0,1000);

  
  
  /// Electron plots  
  map_sig["h_ElectronPt"]          =     new TH1F("h_ElectronPt_"        + name,"leading electron pt",60,0,300);
  map_sig["h_ElectronPt_barrel"]          =     new TH1F("h_ElectronPt_barrel_"        + name,"leading electron pt",60,0,300);
  map_sig["h_ElectronPt_endcap"]          =     new TH1F("h_ElectronPt_endcap_"        + name,"leading electron pt",60,0,300);
  map_sig["h_leadingElectronPt"]   =     new TH1F("h_leadingElectronPt_" + name,"leading electron pt",100,0,500);
  map_sig["h_secondElectronPt"]    =     new TH1F("h_secondElectronPt_"  + name,"secondary electron pt",60,0,300);

  map_sig["h_LeptonEta"]  =     new TH1F("h_LeptonEta_"+ name,"leading electron eta",60,-3.,3.);
  map_sig["h_leadingElectronEta"]  =     new TH1F("h_leadingElectronEta_"+ name,"leading electron eta",60,-3.,3.);
  map_sig["h_secondElectronEta"]   =     new TH1F("h_secondElectronEta_" + name,"second electron eta",60,-3.,3.);

  
  map_sig["h_LeptonPt"]   =     new TH1F("h_LeptonPt_" + name,"lepton pt",100,0,500);
  map_sig["h_leadingLeptonPt"]   =     new TH1F("h_leadingLeptonPt_" + name,"leading electron pt",100,0,500);
  map_sig["h_secondLeptonPt"]    =     new TH1F("h_secondLeptonPt_"  + name,"secondary electron pt",60,0,300);
  
  map_sig["h_leadingLeptonEta"]  =     new TH1F("h_leadingLeptonEta_"+ name,"leading electron eta",60,-3.,3.);
  map_sig["h_secondLeptonEta"]   =     new TH1F("h_secondLeptonEta_" + name,"second electron eta",60,-3.,3.);
  map_sig["h_ElectronIso"]         =     new TH1F("h_ElectronIso_"       + name,"leading electron relIso",50,0,10.);
  map_sig["h_ElectronRelIso"]         =     new TH1F("h_ElectronRelIso_"       + name,"leading electron relIso",100,0,1.);
  map_sig["h_ElectronRelIso_nocorr"]         =     new TH1F("h_ElectronRelIso_nocorr_"       + name,"leading electron relIso",100,0,1.);
  map_sig["h_leadingTrkElectronIso"]  =     new TH1F("h_leadingTrkElectronIso_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondTrkElectronIso"]   =     new TH1F("h_secondtrkElectronIso_" + name,"secondary electron relIso",70,0,0.7);
  map_sig["h_leadingEcalElectronIso"]  =     new TH1F("h_leadingEcalElectronIso_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondEcalElectronIso"]   =     new TH1F("h_secondEcalElectronIso_" + name,"secondary electron relIso",70,0,0.7);
  map_sig["h_leadingHcalElectronIso"]  =     new TH1F("h_leadingHcalElectronIso_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondHcalElectronIso"]   =     new TH1F("h_secondHcalElectronIso_" + name,"secondary electron relIso",70,0,0.7);
  map_sig["h_leadingElectronIso"]  =     new TH1F("h_leadingElectronIso_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondElectronIso"]   =     new TH1F("h_secondElectronIso_" + name,"secondary electron relIso",70,0,0.7);
  map_sig["h_leadingElectronIso_barrel"]  =     new TH1F("h_leadingElectronIso_barrel_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondElectronIso_barrel"]   =     new TH1F("h_secondElectronIso_barrel_" + name,"secondary electron relIso",70,0,0.7);
  map_sig["h_leadingElectronIso_endcap"]  =     new TH1F("h_leadingElectronIso_endcap_"+ name,"leading electron relIso",70,0,0.7);
  map_sig["h_secondElectronIso_endcap"]   =     new TH1F("h_secondElectronIso_endcap_" + name,"secondary electron relIso",70,0,0.7);

  map_sig["h_ElectronDZ"]          =     new TH1F("h_ElectronDZ_"        + name," leading electron DZ", 400, -0.5 , 0.5);
  map_sig["h_ElectronD0"]          =     new TH1F("h_ElectronD0_"        + name," leading electron D0", 1000, -0.25 , 0.25);
  map_sig["h_ElectronDXY"]          =     new TH1F("h_ElectronDXY_"        + name," leading electron DXY", 1000, -0.25 , 0.25);
  map_sig["h_ElectronVDXY"]          =     new TH1F("h_ElectronVDXY_"        + name," leading electron DXY", 1000, -0.25 , 0.25);
  map_sig["h_ElectronLVDXY"]          =     new TH1F("h_ElectronLVDXY_"        + name," leading electron DXY", 1000, -0.25 , 0.25);
  map_sig["h_ElectronD0Sig"]       =     new TH1F("h_ElectronD0Sig_"     + name," leading electron SigD0", 100, -10. , 10.);
  map_sig["h_electrons_eta"]       =     new TH1F("h_electrons_eta_"     + name,"#eta distribution of the two electrons",60,-3,3);
  map_sig["h_electrons_sceta"]     =     new TH1F("h_electrons_sceta_"   + name,"#eta distribution of the two electrons",60,-3,3);
  map_sig["h_electrons_phi"]       =     new TH1F("h_electrons_phi_"     + name,"#phi distribution of the two electrons",140,-3.5,3.5);
  map_sig["h_electrons_scphi"]     =     new TH1F("h_electrons_scphi_"   + name,"#phi distribution of the two electrons",50,-3,3);

  /// jet bins
  map_sig["h_ElectronPt_0jets"]   =     new TH1F("h_ElectronPt_0jets_" + name,"electron pt",60,0,300);
  map_sig["h_ElectronPt_1jets"]   =     new TH1F("h_ElectronPt_1jets_" + name,"electron pt",60,0,300);
  map_sig["h_ElectronPt_2jets"]   =     new TH1F("h_ElectronPt_2jets_" + name,"lectron pt",60,0,300);
  map_sig["h_ElectronPt_3jets"]   =     new TH1F("h_ElectronPt_3jets_" + name,"electron pt",60,0,300);


  map_sig["h_ElectronEta_0jets"]   =     new TH1F("h_ElectronEta_0jets_" + name,"electron eta",60,-3.,3.);
  map_sig["h_ElectronEta_1jets"]   =     new TH1F("h_ElectronEta_1jets_" + name,"electron eta",60,-3.,3.);
  map_sig["h_ElectronEta_2jets"]   =     new TH1F("h_ElectronEta_2jets_" + name,"electron eta",60,-3.,3.);
  map_sig["h_ElectronEta_3jets"]   =     new TH1F("h_ElectronEta_3jets_" + name,"electron eta",60,-3.,3.);
  

  map_sig["h_Electron_fbrem"]      =     new TH1F("h_Electron_fbrem_"    + name, "",100, -1., 2.);
  map_sig["h_Electron_nbrem"]      =     new TH1F("h_Electron_nbrem_"    + name, "", 5,0., 5.);
  map_sig["h_Electron_dist"]       =     new TH1F("h_Electron_dist_"    + name, "",100, -5., 5.);
  map_sig["h_Electron_cottheta"]   =     new TH1F("h_Electron_cottheta_" + name,"",100,-1., 1.);
  map_sig["h_Electron_deltaeta_sctrk_barrel"]   =     new TH1F("h_Electron_deltaeta_sctrk_barrel_"  +name, "", 100, -0.01,.01);
  map_sig["h_Electron_deltaeta_sctrk_endcap"]   =     new TH1F("h_Electron_deltaeta_sctrk_endcap_"  +name, "", 100, -0.01,.01);
  
  map_sig["h_Electron_deltaphi_sctrk_barrel"]   =     new TH1F("h_Electron_deltaphi_sctrk_barrel_"  +name, "", 100, -0.05,.05);
  map_sig["h_Electron_deltaphi_sctrk_endcap"]   =     new TH1F("h_Electron_deltaphi_sctrk_endcap_"  +name, "", 100, -0.05,.05);
 
  map_sig["h_electron_hoe_barrel"] =     new TH1F("h_electron_hoe_barrel_" +name,"Hoe barrel",  50, 0., 0.5);
  map_sig["h_electron_hoe_endcap"] =     new TH1F("h_electron_hoe_endcap_" +name,"Hoe endcap",  50, 0., 0.5);
  
  map_sig["h_Electron_sigmaieta_barrel"] =      new TH1F("h_Electron_sigmaieta_barrel_"  +name, "sigmaieta", 50, 0., 0.1);
  map_sig["h_Electron_sigmaieta_endcap"] =      new TH1F("h_Electron_sigmaieta_endcap_"  +name, "sigmaieta", 50, 0., 0.1);
  
  map_sig["h_Electron_ep"] =    new TH1F("h_Electron_ep_"+name, "h_Electron_ep", 50, 0., 0.1);
  map_sig["h_Electron_convfitprob"] = new TH1F("h_Electron_convfitprob_"+name, "h_Electron_convfitprob", 50, 0., 1.);
  map_sig["h_Electron_missinghits"] = new TH1F("h_Electron_missinghits_"+name, "h_Electron_missinghits", 4, 0., 4.);
  map_sig["h_Electron_matchedconvphoton"] = new TH1F("h_Electron_matchedconvphoton_"+name, "h_Electron_matchedconvphoton", 2, 0., 2.);
  map_sig["h_Electron_chargeconsistency"] = new TH1F("h_Electron_chargeconsistency_"+name, "h_Electron_chargeconsistency", 2, 0.,2.);
  

  map_sig2["h_WandNmass"]          =     new TH2F("h_WandNmass_"         + name,"Invariant mass of the W and the N",100,0,2000,100,0,2000);
  map_sig3["h_3Dparm"]             =     new TH3F("h_3Dpar_"             + name,"m(lljj) and muon p_{T}_{1} and muon p_{T}_{2}",100,0,2000,30,0,300,30,0,300);
  
  /// Muon/Jet/Electron dR
  map_sig["h_njets_inrapgap"]           =     new TH1F("h_njets_inrapgap_" + name,"# jets in Y gap", 6, 0 , 6);
  map_sig["h_ElectronJetdR"]       =     new TH1F("h_ElectronJetdR_"     + name,"electron jet dR",50,0,5);
  map_sig["h_ElectronAwayJetdR"]   =     new TH1F("h_ElectronAwayJetdR_" + name, "away jet dr", 50,0,5);
  map_sig["h_leadElectrondR"]      =     new TH1F("h_leadElectrondR_"    + name,"leading electron dR",50,0,5);
  map_sig["h_leadElectrondPhi"]    =     new TH1F("h_leadElectrondPhi_"  + name,"leading electron dPhi",50,-5,5);
  map_sig["h_leadJetdR"]           =     new TH1F("h_leadJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetdPhi"]           =     new TH1F("h_leadJetdPhi_"         + name,"leading jet dPhi",50,-5,5);
  map_sig["h_ElectronMuondR"]      =     new TH1F("h_ElectronMuonR_"     + name,"leading jet dR",50,0,5);
  map_sig["h_dr_el_bjet"]      =     new TH1F("h_dr_el_bjet_"  + name, "", 50,0,5);

  map_sig["h_MuonPt"]          =     new TH1F("h_MuonPt_"        + name,"leading muon pt",60,0,300);
  map_sig["h_MuonEta"]          =     new TH1F("h_MuonEta_"        + name,"leading muon eta",50,-2.5,2.5);
  
  //// Jet Plots
  map_sig["h_leadingJetPt"]        =     new TH1F("h_leadingJetPt_"      + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"]         =     new TH1F("h_secondJetPt_"       + name,"secondary jet pt",60,0,300);
  map_sig["h_HT"]                  =     new TH1F("h_HT_"                + name,"sum jet pt",50,0,1000);
  map_sig["h_ST"]                  =     new TH1F("h_ST_"                + name,"sum event pt",50,0,1000);
  map_sig["h_jets_pt"]             =     new TH1F("h_jets_pt_"           + name,"jet pt",60,0,300);
  map_sig["h_el_jet_emfrac"]       =     new TH1F("h_el_jet_emfrac_"     + name, "jet_el_emfrac", 20, 0., 1.);
  map_sig["h_el_jet_dphi"]       =     new TH1F("h_el_jet_dphi_"        + name, "el_jet_emfrac" , 50, 0., 5.);
  map_sig["h_el_leadjet_emfrac"]       =     new TH1F("h_el_leadjet_emfrac_"     + name, "jet_el_emfrac", 20, 0., 1.);
  map_sig["h_el_awayjet_emfrac"]       =     new TH1F("h_el_awayjet_emfrac_"     + name, "jet_el_emfrac", 20, 0., 1.);
  map_sig["h_el_awayjet_pt"]       =     new TH1F("h_el_awayjet_pt_"  + name, "h_el_awayjet_pt", 50, 20., 270.);
  map_sig["h_jet_el_ptratio"]      =     new TH1F("h_jet_el_ptratio_"    + name, "jet_el_ptratio", 20, 0., 5.);
  map_sig["h_forward_jet_pt"]             =     new TH1F("h_forward_jet_pt_"                + name,"h_forward_jet_pt",60,0,300);
  map_sig["h_central_jet_pt"]             =     new TH1F("h_central_jet_pt_"                + name,"h_central_jet_pt",60,0,300);
  map_sig["h_forward_jet_eta"]             =     new TH1F("h_forward_jet_eta_"                + name,"h_forward_jet_eta",50,-2.5,2.5);
  map_sig["h_central_jet_eta"]             =     new TH1F("h_central_jet_eta_"                + name,"h_central_jet_eta",50,-2.5,2.5);



  /// dPhi/MT
  map_sig["h_MTelectron"]          =     new TH1F("h_MTelectron_"        + name,"Mt",100,0.0,500.0);
  map_sig["h_MTmuon"]          =     new TH1F("h_MTmuon_"        + name,"Mt",100,0.0,500.0);
  map_sig["h_dphi_METelectron"]    =     new TH1F("h_dphi_METelectron_"  + name , "METlepdphi", 50, -5., 5.);
  
  
  /// MET plots
  map_sig["h_MET"]                 =     new TH1F("h_MET_"               + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METraw"]              =     new TH1F("h_METraw_"            + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METtype1"]            =     new TH1F("h_METtype1_"          + name,"Missing Et",100,0.0,500.0);
  map_sig["h_METtype01"]           =     new TH1F("h_METtype01_"         + name,"Missing Et",100,0.0,500.0);
  map_sig["h_MET_phi"]             =     new TH1F("h_MET_phi_"           + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METraw_phi"]          =     new TH1F("h_METraw_phi_"        + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METtype1_phi"]        =     new TH1F("h_METtype1_phi_"      + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_METtype01_phi"]       =     new TH1F("h_METtype01_phi_"     + name,"Missing Et",140,-3.5,3.5);
  map_sig["h_SumET"]               =     new TH1F("h_SumET_"             + name,"Sum Et",100,0.0,2000.0);
  map_sig["h_nVertices"]           =     new TH1F("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  map_sig["h_samevertex"]          =     new TH1F("h_samevertex_"        + name,"same vertex", 2,0., 2.0); 
  map_sig["h_el_evvertexmatch"]    =     new TH1F("h_el_evvertexmatch_"  + name, "el vertex " , 2,0., 2.0);
  /// Charge plot
  map_sig["h_sumcharge"]           =     new TH1F("h_sumcharge_"         + name,"Charge of the lepton pair",6,-3,3);
  
  map_sig["h_jets_eta"]            =     new TH1F("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-3,3);
  map_sig["h_jets_phi"]            =     new TH1F("h_jets_phi_"          + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"]      =     new TH1F("h_pileupJetIDMVA_"    + name, "" ,100, -1.,1.);
  map_sig["h_bTag"]                =     new TH1F("h_bTag_"              + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"]               =     new TH1F("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]              =     new TH1F("h_Nbjets_"            + name,"number of b jets",5,0,5);

  /// Number of objects
  map_sig["h_Nelectrons"]          =     new TH1F("h_Nelectrons_"        + name,"number of el",5,0,5);


}



void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  
  Fill(ev, muons, electrons, jets, weight, 0.);
}

void SignalPlots::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight, Double_t weight_err) {
  

  //// Fills all hists (e/mu/jets/MET)
  bool debug =false;

  if(debug)cout<< "Plotting [1] " << endl;
  Fill("h_Nelectrons", electrons.size(), weight, weight_err);
  

  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);

  if(debug)cout<< "Plotting [1b] " << endl;

  float min_ejet_Dr=10000.;  
  float min_eleadawayjet_Dr= -10000.;
  bool leadjet_away=true;
  for(UInt_t i=0; i<electrons.size(); i++){ 
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =electrons[i].DeltaR(jets[emme]);
      float dphi = fabs(TVector2::Phi_mpi_pi(electrons[i].Phi()- jets[emme].Phi()));
      if(dR > 0.5) {
	if(dR > min_eleadawayjet_Dr) min_eleadawayjet_Dr=  dR;
      }
      Fill("h_el_jet_dphi", dphi, weight, weight_err);

      if(fabs(dphi) > 2.5) {
	if(leadjet_away){
	  Fill("h_el_awayjet_emfrac", (jets[emme].NeutralEMEnergyFraction() +jets[emme].ChargedEMEnergyFraction()) , weight, weight_err);
	  Fill("h_jet_el_ptratio", electrons.at(i).Pt()/ jets[emme].Pt(), weight, weight_err);
	  Fill("h_el_awayjet_pt", jets[emme].Pt(), weight, weight_err);
	}
	leadjet_away=false;
      }	
      
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;
      if(emme == 0)   Fill("h_el_leadjet_emfrac", (jets[emme].NeutralEMEnergyFraction() +jets[emme].ChargedEMEnergyFraction()) , weight, weight_err);
      Fill("h_el_jet_emfrac", (jets[emme].NeutralEMEnergyFraction() +jets[emme].ChargedEMEnergyFraction()) , weight, weight_err);
      
      if(jets[emme].CombinedSecVertexBtag() > 0.679)  Fill("h_dr_el_bjet", dR, weight, weight_err);
    }
  }
  
  if(debug)cout<< "Plotting [1c] " << endl;
  float min_emuon_Dr= 1000.;
  for(UInt_t i=0; i<electrons.size(); i++){
    for(UInt_t j=0; j<muons.size(); j++){
      float dR =electrons[i].DeltaR(muons[j]);
      if(dR < min_emuon_Dr) min_emuon_Dr = dR;

    }
  }
  if(debug)cout<< "Plotting [1d] " << endl;
    
  float min_ee_Dr=10000.;
  float min_ee_DPhi=10000.;
  for(UInt_t i=0; i<electrons.size(); i++){
    if(fabs(electrons.at(i).Eta()) < 1.447)Fill("h_electron_hoe_barrel", electrons.at(i).HoE(),weight, weight_err);
    else Fill("h_electron_hoe_endcap", electrons.at(i).HoE(),weight, weight_err);
    for(UInt_t j=0; j<electrons.size(); j++){
      if(i==j) continue;
      float dPhi = fabs(TVector2::Phi_mpi_pi(electrons[i].Phi() - electrons[j].Phi() ));
      float dR =electrons[i].DeltaR(electrons[j]);
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
  
  if(jets.size() > 2) {
    float Jet1Rap = jets.at(0).Rapidity();
    float Jet2Rap = jets.at(1).Rapidity();
    float ymax(0.);
    float ymin(0.);
    if(Jet1Rap > Jet2Rap ){
      ymax = Jet1Rap;
      ymin= Jet2Rap;
    }
    else{
      ymax = Jet1Rap;
      ymin= Jet2Rap;
    }
    int jet_in_gap(0);
    for(unsigned int ij = 2; ij < jets.size() ; ij++){
      if( (jets.at(ij).Rapidity() <  ymax) && (jets.at(ij).Rapidity()>  ymin)  ){
	jet_in_gap++;
      }
    }
    Fill("h_njets_inrapgap",jet_in_gap, weight, weight_err);
    
    
  }
  
  if(electrons.size()!=0)Fill("h_leadElectrondR",min_ee_Dr,weight, weight_err);
  if(electrons.size()!=0)Fill("h_leadElectrondPhi",min_ee_DPhi,weight, weight_err);
  if(electrons.size()!=0 && muons.size()!=0)Fill("h_ElectronMuondR",min_emuon_Dr,weight, weight_err);


  if(jets.size()!=0){
    if(electrons.size()!=0){
      Fill("h_ElectronJetdR",min_ejet_Dr,weight, weight_err);
      Fill("h_ElectronAwayJetdR",min_eleadawayjet_Dr,weight, weight_err);
    }
    if(jets.size() > 1)Fill("h_leadJetdR",min_jj_Dr,weight, weight_err);
    if(jets.size() > 1)Fill("h_leadJetdPhi",min_jj_DPhi,weight, weight_err);
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

  float low_leadjetmass=0.;
  int lm=0;
  int ln=0;
  if(electrons.size() == 1 && muons.size() == 1){
    float low_dijetmass_tmp=99999.9;
    float low_dijetmass=9999.9;
    for(UInt_t emme=0; emme<jets.size(); emme++){
      
      for(UInt_t enne=1; enne<jets.size(); enne++) {
	if(emme == enne) continue;
	low_dijetmass_tmp = (jets[emme]+jets[enne] + electrons[0]+ muons[0]).M();
	if(emme==0 && enne == 1) low_leadjetmass = low_dijetmass_tmp;
	if ( fabs(low_dijetmass_tmp-80.4) < fabs(low_dijetmass-80.4) ) {
	  low_dijetmass = low_dijetmass_tmp;
	  lm = emme;
	  ln = enne;
	}
      }
    }
  }
  
  if(leadjetmass != 0.)Fill("h_leadjetmass", leadjetmass,weight, weight_err);
  
  if(debug)cout<< "Plotting [3] " << endl;  

  
  if(electrons.size() == 1 && muons.size() == 1){
    
    Fill("h_emumass", ((electrons[0]+ muons[0]).M()), weight, weight_err);
    if(jets.size()>1){
      Fill("h_emujjmass", ((electrons[0]+ muons[0]+jets[m]+jets[n]).M()), weight, weight_err);
      Fill("h_mujjmass", ((muons[0]+jets[m]+jets[n]).M()), weight, weight_err);
    }
    Fill("h_MuonPt", muons[0].Pt(), weight, weight_err);
    Fill("h_MuonEta", muons[0].Eta(), weight,weight_err);
    if(debug)cout<< "Plotting [3aaa] " << endl;

    if(jets.size()>1){
      if(electrons.at(0).Pt() > muons.at(0).Pt()) {
	Fill("h_l1jjmass", ((electrons[0]+jets[m]+jets[n]).M()), weight, weight_err);
	Fill("h_l2jjmass", ((muons[0]+jets[m]+jets[n]).M()), weight, weight_err);
      }
      else{
	Fill("h_l2jjmass", ((electrons[0]+jets[m]+jets[n]).M()), weight, weight_err);
	Fill("h_l1jjmass", ((muons[0]+jets[m]+jets[n]).M()), weight, weight_err);
      }
      
      if(electrons.at(0).Pt() > muons.at(0).Pt()) {
	Fill("h_l1jj_lowmass", ((electrons[0]+jets[lm]+jets[ln]).M()), weight, weight_err);
	Fill("h_l2jj_lowmass", ((muons[0]+jets[lm]+jets[ln]).M()), weight, weight_err);
      }
      else{
	Fill("h_l2jj_lowmass", ((electrons[0]+jets[lm]+jets[ln]).M()), weight, weight_err);
	Fill("h_l1jj_lowmass", ((muons[0]+jets[lm]+jets[ln]).M()), weight, weight_err);
      }
      Fill("h_emujj_lowmass", ((electrons[0]+ muons[0]+jets[lm]+jets[ln]).M()), weight, weight_err);
    }
  }
  
  if(muons.size() > 1){
    if(jets.size()>3){
      int p_forward_jet(0), m_forward_jet(0);
      int index_f(-999), index_b(-999);
      vector<int> central_jets;
      float most_forward=0.;
      float most_backward=0.;

      for(unsigned int ij = 0 ; ij < jets.size(); ij++){
	if(jets[ij].Eta() > 1.5) {
	  if(jets[ij].Eta() > most_forward){
	    index_f= ij;
	    most_forward=jets[ij].Eta();
	  }
	  p_forward_jet++;
	  Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
	  Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);

	}
	else if(jets[ij].Eta() < -1.5) {
	  if(jets[ij].Eta() < most_backward){
	    index_b=ij;
	    most_backward=jets[ij].Eta();
	  }
	  m_forward_jet++;

	  Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
	  Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);
	}
	else{
	  Fill("h_central_jet_pt", jets[ij].Pt(),weight, weight_err);
	  Fill("h_central_jet_eta", jets[ij].Eta(),weight, weight_err);
	}
      }

      
      for(unsigned int ij = 0 ; ij < jets.size(); ij++){
	if(ij == index_b) continue;
	if(ij == index_f) continue;
	central_jets.push_back( ij);
      }
      if( (p_forward_jet >= 1) && (index_b >= 1)) {
	
	for(unsigned int ic = 0; ic < central_jets.size()-1; ic++){

	  for(unsigned int ic2 =ic+1; ic2 <central_jets.size(); ic2++){
	    Fill("h_l2jj_central_mass", (muons[1]+jets[ic]+jets[ic2]).M(),weight, weight_err);
	    Fill("h_lljj_central_mass", (muons[0] + muons[1]+jets[ic]+jets[ic2]).M(),weight, weight_err);
	    Fill("h_l1jj_central_mass", (muons[0]+jets[ic]+jets[ic2]).M(),weight, weight_err);
	  }
	}
      }
    }
  }


  if(debug)cout<< "Plotting [3B] " << endl;

  
  int sum_charge(0);
  
  if(electrons.size()>=2){
    Fill("h_eemass", (electrons[0]+electrons[1]).M(),weight, weight_err);
    if( jets.size()==1) Fill("h_eejmass", (electrons[0] + electrons[1]+jets[0]).M(),weight, weight_err);
    if(jets.size()>1){
      Fill("h_e2jjmass", (electrons[1]+jets[m]+jets[n]).M(),weight, weight_err);
      Fill("h_eejjmass", (electrons[0] + electrons[1]+jets[m]+jets[n]).M(),weight, weight_err);
      Fill("h_WandNmass", (electrons[0]+electrons[1]+jets[m]+jets[n]).M() , (electrons[1]+jets[m]+jets[n]).M(),weight, weight_err);      
      Fill("h_3Dparm", (electrons[0]+electrons[1]+jets[m]+jets[n]).M(), electrons[0].Pt(), electrons[1].Pt(), weight, weight_err); 
      
      if(jets.size()>3){
        int p_forward_jet(0), m_forward_jet(0);
        int index_f(-999), index_b(-999);
        vector<int> central_jets;
	float most_forward=0.;
	float most_backward=0.;

        for(unsigned int ij = 0 ; ij < jets.size(); ij++){
          if(jets[ij].Eta() > 1.5) { 
	    if(jets[ij].Eta() > most_forward){
	      index_f= ij;
	      most_forward=jets[ij].Eta();
	    }
	    p_forward_jet++;            
	    Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
	    Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);
	    
	  }
          else if(jets[ij].Eta() < -1.5) { 
	    if(jets[ij].Eta() < most_backward){
	      index_b=ij;
	      most_backward=jets[ij].Eta();
	    }
	    m_forward_jet++;
	    
	    Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
            Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);
	  }
	  else{
	    Fill("h_central_jet_pt", jets[ij].Pt(),weight, weight_err);
	    Fill("h_central_jet_eta", jets[ij].Eta(),weight, weight_err);
	  }
	}

	

	for(unsigned int ij = 0 ; ij < jets.size(); ij++){
	  if(ij == index_b) continue;
	  if(ij == index_f) continue;
	  central_jets.push_back( ij);
	}
        if( (p_forward_jet >= 1) && (index_b >= 1)) {
	  
          for(unsigned int ic = 0; ic < central_jets.size()-1; ic++){

            for(unsigned int ic2 =ic+1; ic2 <central_jets.size(); ic2++){
              Fill("h_l2jj_central_mass", (electrons[1]+jets[ic]+jets[ic2]).M(),weight, weight_err);
              Fill("h_lljj_central_mass", (electrons[0] + electrons[1]+jets[ic]+jets[ic2]).M(),weight, weight_err);
              Fill("h_l1jj_central_mass", (electrons[0]+jets[ic]+jets[ic2]).M(),weight, weight_err);
            }
          }
        }
      }
    }
    
    if(electrons.size()==1 && muons.size() == 1){
      if(jets.size()>1){

	if(jets.size()>3){
	  int p_forward_jet(0), m_forward_jet(0);
	  int index_f(-999), index_b(-999);
	  vector<int> central_jets;
	  float most_forward=0.;
	  float most_backward=0.;

	  for(unsigned int ij = 0 ; ij < jets.size(); ij++){
	    if(jets[ij].Eta() > 1.5) {
	      if(jets[ij].Eta() > most_forward){
		index_f= ij;
		most_forward=jets[ij].Eta();
	      }
	      p_forward_jet++;
	      Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
	      Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);

	    }
	    else if(jets[ij].Eta() < -1.5) {
	      if(jets[ij].Eta() < most_backward){
		index_b=ij;
		most_backward=jets[ij].Eta();
	      }
	      m_forward_jet++;

	      Fill("h_forward_jet_pt", jets[ij].Pt(),weight, weight_err);
	      Fill("h_forward_jet_eta", jets[ij].Eta(),weight, weight_err);
	    }
	    else{
	      Fill("h_central_jet_pt", jets[ij].Pt(),weight, weight_err);
	      Fill("h_central_jet_eta", jets[ij].Eta(),weight, weight_err);
	    }
	  }



	  for(unsigned int ij = 0 ; ij < jets.size(); ij++){
	    if(ij == index_b) continue;
	    if(ij == index_f) continue;
	    central_jets.push_back( ij);
	  }
	  if( (p_forward_jet >= 1) && (index_b >= 1)) {

	    for(unsigned int ic = 0; ic < central_jets.size()-1; ic++){

	      for(unsigned int ic2 =ic+1; ic2 <central_jets.size(); ic2++){
		Fill("h_l2jj_central_mass", (muons[0]+jets[ic]+jets[ic2]).M(),weight, weight_err);
		Fill("h_lljj_central_mass", (electrons[0] + muons[0]+jets[ic]+jets[ic2]).M(),weight, weight_err);
		Fill("h_l1jj_central_mass", (electrons[0]+jets[ic]+jets[ic2]).M(),weight, weight_err);
	      }
	    }
	  }
	}
      }
    }

    /// Triel plots
    if(electrons.size()>2){
      if(electrons[0].Charge() != electrons[1].Charge())   Fill("h_oseemass", (electrons[0]+electrons[1]).M(),weight, weight_err);
      if(electrons[0].Charge() != electrons[2].Charge())   Fill("h_oseemass", (electrons[0]+electrons[2]).M(),weight, weight_err);
      if(electrons[1].Charge() != electrons[2].Charge())   Fill("h_oseemass", (electrons[1]+electrons[2]).M(),weight, weight_err);
    }
  }
  
  if(electrons.size()>=1){
    if(jets.size()>1){
      Fill("h_e1jjmass", (electrons[0]+jets[m]+jets[n]).M(),weight, weight_err);
    }
  }


  for(unsigned int iel = 0 ; iel < electrons.size(); iel++){
    Fill("h_LeptonEta",electrons.at(iel).Eta(),weight, weight_err);
    Fill("h_LeptonPt", electrons.at(iel).Pt(),weight, weight_err);
  }
  for(unsigned int imu = 0 ; imu < muons.size(); imu++){
    Fill("h_LeptonEta",muons.at(imu).Eta(),weight, weight_err);
    Fill("h_LeptonPt", muons.at(imu).Pt(),weight, weight_err);
  }


  if(debug)cout<< "Plotting [4] " << endl;
  int iel(0);
  
  int samevertex=-999;
  int vid=0;
  int ev_elvertex=-999;
  for(std::vector<snu::KElectron>::iterator elit = electrons.begin(); elit != electrons.end(); elit++, iel++){
    if(iel == 0 ) vid= elit->VertexIndex() ;
    else{
      if(elit->VertexIndex() != vid) samevertex = 0;
      else {
	samevertex = 1;
	if(ev.VertexIndex() == elit->VertexIndex()) ev_elvertex = 1;
	else ev_elvertex = 0;
      }
    }
    
    Fill("h_electrons_phi",elit->Phi(),weight, weight_err);
    Fill("h_electrons_scphi",elit->SCPhi(),weight, weight_err);
    Fill("h_electrons_eta",elit->Eta(),weight, weight_err);
    Fill("h_electrons_sceta",elit->SCEta(),weight, weight_err);
    Fill("h_ElectronD0", elit->dxy(),weight, weight_err);
    Fill("h_ElectronDXY", elit->PrimaryVertexDXY(),weight, weight_err);
    Fill("h_ElectronVDXY", elit->VtxDistXY(),weight, weight_err);
    Fill("h_ElectronLVDXY", elit->LeadVtxDistXY(),weight, weight_err);
    Fill("h_ElectronDZ", elit->dz(),weight, weight_err);
    Fill("h_ElectronD0Sig", (elit->PrimaryVertexDXY()/ elit->PrimaryVertexDXYError()),weight, weight_err);
    
    float EA=GetElectronISOEA(elit->SCEta());
    float rho = ev.JetRho();
    float el_iso =  elit->PFChargedHadronIso03() + max( elit->PFNeutralHadronIso03() + elit->PFPhotonIso03() - rho * EA, 0.);
    float el_iso_noncorr =  elit->PFChargedHadronIso03() +  elit->PFNeutralHadronIso03() + elit->PFPhotonIso03() ;
    
    float trkiso = elit->TrkIsoDR03();
    float ecaliso = elit->ECalIsoDR03();
    float hcaliso = elit->HCalIsoDR03();
    Fill("h_Electron_fbrem", elit->FBrem(),weight, weight_err);
    Fill("h_Electron_nbrem", elit->NBrems() ,weight, weight_err);
    Fill("h_Electron_dist", elit->Dist() ,weight, weight_err);
    Fill("h_Electron_cottheta", elit->CotTheta() ,weight, weight_err);
    
    if(fabs(elit->Eta()) < 1.447){
      Fill("h_Electron_deltaeta_sctrk_barrel",  elit->DeltaEta(), weight, weight_err);
      Fill("h_Electron_deltaphi_sctrk_barrel",  elit->DeltaPhi(), weight, weight_err);
      Fill("h_Electron_sigmaieta_barrel", elit->SigmaIEtaIEta(), weight, weight_err);
    }
    else{
      Fill("h_Electron_deltaeta_sctrk_endcap",  elit->DeltaEta(), weight, weight_err);
      Fill("h_Electron_deltaphi_sctrk_endcap",  elit->DeltaPhi(), weight, weight_err);
      Fill("h_Electron_sigmaieta_endcap", elit->SigmaIEtaIEta(), weight, weight_err);
    }

    double egamma_e  = elit->CaloEnergy();
    double egamma_p  = elit->CaloEnergy() / elit->ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

    Fill("h_Electron_ep",egamma_ep, weight, weight_err);
    Fill("h_Electron_convfitprob",elit->ConvFitProb  (), weight, weight_err);
    Fill("h_Electron_missinghits",elit->MissingHits(), weight, weight_err);
    Fill("h_Electron_matchedconvphoton",elit->HasMatchedConvPhot(), weight, weight_err);
    Fill("h_Electron_chargeconsistency",elit->GsfCtfScPixChargeConsistency(), weight, weight_err);
    



    Fill("h_ElectronPt", elit->Pt(),weight, weight_err);

    if(fabs(elit->Eta()) < 1.5){
      Fill("h_ElectronPt_barrel", elit->Pt(),weight, weight_err);
    }
    else Fill("h_ElectronPt_endcap", elit->Pt(),weight, weight_err);
    
    
    Fill("h_ElectronIso", el_iso,weight, weight_err);
    Fill("h_ElectronRelIso", el_iso/elit->Pt(),weight, weight_err);
    Fill("h_ElectronRelIso_nocorr", el_iso_noncorr/elit->Pt(),weight, weight_err);
    if(iel==1){
      Fill("h_secondElectronPt", elit->Pt(),weight, weight_err);
      Fill("h_secondTrkElectronIso", trkiso/elit->Pt(),weight, weight_err);
      Fill("h_secondEcalElectronIso", ecaliso/elit->Pt(),weight, weight_err);
      Fill("h_secondHcalElectronIso", hcaliso/elit->Pt(),weight, weight_err);
      Fill("h_secondElectronIso", el_iso/elit->Pt(),weight, weight_err);
      if(fabs(elit->Eta()) < 1.5){
	Fill("h_secondElectronIso_barrel", el_iso/elit->Pt(),weight, weight_err);
      }
      else{
	Fill("h_secondElectronIso_endcap", el_iso/elit->Pt(),weight, weight_err);
      }
      Fill("h_secondElectronEta",elit->Eta(),weight, weight_err);
    }
    if(iel==0){
      Fill("h_leadingElectronEta",elit->Eta(),weight, weight_err);
      Fill("h_leadingTrkElectronIso",trkiso/elit->Pt() ,weight, weight_err);
      Fill("h_leadingEcalElectronIso", ecaliso/elit->Pt() ,weight, weight_err);
      Fill("h_leadingHcalElectronIso", hcaliso/elit->Pt() ,weight, weight_err);
      Fill("h_leadingElectronIso", el_iso/elit->Pt(),weight, weight_err);
      if(fabs(elit->Eta()) < 1.5){
	Fill("h_leadingElectronIso_barrel", el_iso/elit->Pt(),weight, weight_err);
      }
      else{
	Fill("h_leadingElectronIso_endcap", el_iso/elit->Pt(),weight, weight_err);
      }
      Fill("h_leadingElectronPt", elit->Pt(),weight, weight_err);
    }
    
    if(electrons.size() ==1 && muons.size() == 1){
      if(electrons.at(0).Pt()  > muons.at(0).Pt() ){
	Fill("h_leadingLeptonEta",electrons.at(0).Eta(),weight, weight_err);
	Fill("h_secondLeptonEta" ,muons.at(0).Eta(),weight, weight_err);
	
	Fill("h_leadingLeptonPt", electrons.at(0).Pt(),weight, weight_err);
	Fill("h_secondLeptonPt", muons.at(0).Pt(),weight, weight_err);
      }
      else{
	Fill("h_leadingLeptonEta",muons.at(0).Eta(),weight, weight_err);
        Fill("h_secondLeptonEta" ,electrons.at(0).Eta(),weight, weight_err);
	
        Fill("h_leadingLeptonPt", muons.at(0).Pt(),weight, weight_err);
        Fill("h_secondLeptonPt", electrons.at(0).Pt(),weight, weight_err);

      }
    }

    
    if(jets.size()==0){
      Fill("h_ElectronEta_0jets",elit->Eta(),weight, weight_err);
      Fill("h_ElectronPt_0jets", elit->Pt(),weight, weight_err);
    }
    if(jets.size()==1){
      Fill("h_ElectronEta_1jets",elit->Eta(),weight, weight_err);
      Fill("h_ElectronPt_1jets", elit->Pt(),weight, weight_err);
     
    } 
    if(jets.size()==2){
      Fill("h_ElectronEta_2jets",elit->Eta(),weight, weight_err);
      Fill("h_ElectronPt_2jets", elit->Pt(),weight, weight_err);
    } 
    if(jets.size() > 2.){
      Fill("h_ElectronEta_3jets",elit->Eta(),weight, weight_err);
      Fill("h_ElectronPt_3jets", elit->Pt(),weight, weight_err);
    } 
    
    sum_charge += elit->Charge();
  }
  
  Fill("h_sumcharge",sum_charge,weight, weight_err);
  
  
  //// Fillplots
  for(unsigned int i=0 ; i < electrons.size(); i++){
    float dphi = fabs(TVector2::Phi_mpi_pi(electrons.at(i).Phi()- ev.PFMETphi()));
    float MT = sqrt(2.* electrons.at(i).Et()*ev.PFMET() * (1 - cos( dphi)));
    Fill("h_MTelectron",MT, weight, weight_err);
    Fill("h_dphi_METelectron",dphi, weight, weight_err);
  }

  //// Fillplots
  for(unsigned int i=0 ; i < muons.size(); i++){
    float dphi = fabs(TVector2::Phi_mpi_pi(muons.at(i).Phi()- ev.PFMETphi()));
    float MT = sqrt(2.* muons.at(i).Et()*ev.PFMET() * (1 - cos( dphi)));
    Fill("h_MTmuon",MT, weight, weight_err);
  }



  if(debug)cout<< "Plotting [5] " << endl;

  Fill("h_MET",ev.PFMET(), weight, weight_err);
  Fill("h_METraw",ev.PFMETRaw(), weight, weight_err);
  Fill("h_METtype1",ev.PFMETType1(), weight, weight_err);
  Fill("h_METtype01",ev.PFMETType01(), weight, weight_err);
  Fill("h_MET_phi",ev.PFMETphi(), weight, weight_err);
  Fill("h_METraw_phi",ev.PFMETRawphi(), weight, weight_err);
  Fill("h_METtype1_phi",ev.PFMETType1phi(), weight, weight_err);
  Fill("h_METtype01_phi",ev.PFMETType01phi(), weight, weight_err);
  Fill("h_SumET",ev.PFSumET(), weight, weight_err);
  Fill("h_nVertices", ev.nVertices(), weight, weight_err);
  
  Fill("h_samevertex", samevertex, weight, weight_err);
  Fill("h_el_evvertexmatch" , ev_elvertex, weight, weight_err);


  
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight, weight_err); 
  }
  float ht=0.;
  for(UInt_t j=0; j < jets.size(); j++){ 
    ht+= jets[j].Pt();
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight, weight_err);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight, weight_err);
    Fill("h_jets_pt", jets[j].Pt(),weight, weight_err);
    Fill("h_jets_eta",jets[j].Eta(),weight, weight_err);
    Fill("h_PileupJetIDMVA", jets[j].PileupJetIDMVA(),weight, weight_err);
    Fill("h_jets_phi",jets[j].Phi(),weight, weight_err);
    Fill("h_bTag",jets[j].CombinedSecVertexBtag(),weight, weight_err);
    if(jets.at(j).CombinedSecVertexBtag() > 0.679) nbjet++; 
  }
  
  float st = ht + ev.PFMET();
  for(unsigned int i=0 ; i < electrons.size(); i++){
    st+= electrons.at(i).Pt();
  }
  
  Fill("h_HT", ht,weight, weight_err);
  Fill("h_ST", st,weight, weight_err);
  Fill("h_Nbjets",nbjet, weight, weight_err);
  Fill("h_Njets",jets.size(), weight, weight_err);
  
  if(debug)cout<< "Plotting [6] " << endl;
  return;
}/// End of Fill
  

  
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

void SignalPlots::Fill(TString name, double value, double w, Double_t w_err){
  
  if(w_err < 0.) w_err=w;
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end())   it->second->Fill(value, w);

  else cout << name << " not found in map_sig" << endl;
  return;
}
 
void SignalPlots::Fill(TString name, double value1, double value2, double w, Double_t w_err){
  if(w_err < 0.) w_err=w;
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) it->second->Fill(value1, value2, w);
   else cout << name << " not found in map_sig" << endl;
   return;
 }



void SignalPlots::Fill(TString name, double value1, double value2, double value3, double w, Double_t w_err){
  if(w_err < 0.) w_err=w;
  std::map<TString, TH3*>::iterator it = map_sig3.find(name);
  if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
  else cout << name << " not found in map_sig" << endl;
  return;
}




