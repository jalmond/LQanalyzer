#include "SignalPlotsMM.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

SignalPlotsMM::SignalPlotsMM(TString name, int nmu): StdPlots(name){

  TH1::SetDefaultSumw2(true);


  bool singlemu = (nmu < 0)  ?   true : (nmu == 1);
  bool doublemu = (nmu < 0)  ?   true : (nmu == 2);
  bool trimu = (nmu < 0)  ?   true : (nmu == 3);
  bool quadmu = (nmu < 0)  ?   true : (nmu == 4);

  /// Mass plots                                                                                                                                                                                           

  
  if(doublemu){
    map_sig["h_llmass"]                 = SetupHist("h_llmass_"           + name,"Invariant mass of the two leading muectrons",1000,0,1000,"M_{ll} GeV");
    map_sig["h_llpt"]                 = SetupHist("h_llpt_"           + name,"Invariant pt of the two leading muectrons",500,0,1000,"P_T (ll) GeV");
    map_sig["h_lljjmass"]               = SetupHist("h_lljjmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{lljj} GeV");

    map_sig["h_llj1mass"]                = SetupHist("h_llj1mass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{llj} GeV");
    map_sig["h_llj2mass"]                = SetupHist("h_ll21mass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{llj} GeV");
    map_sig["h_l1jmass"]                = SetupHist("h_l1jmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{llj} GeV");
    map_sig["h_l2jmass"]                = SetupHist("h_l2jmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{llj} GeV");

  }

 
  map_sig["h_jjmass"]                 = SetupHist("h_dijetsmass_"        + name,"Invariant mass of the two leading jets",500,0.,500.,"M_{jj} GeV");
  map_sig["h_deltaRjj"]                 = SetupHist("h_deltaRjj_" + name, "DeltaR between jets", 100, 0., 10., "#Delta R (jj)");
  map_sig["h_fjsdmass"]                 = SetupHist("h_fatjetsoftdropmass_"        + name,"Invariant mass of the two leading jets",500,0.,500.,"M_{jj} GeV");

  map_sig["h_l1jjmass"]               = SetupHist("h_l1jjmass_"          + name,"Invariant mass of the two leading jets and leading muectron",100,0,1000,"M_{l1jj} GeV");
  if(nmu > 1 || nmu < 0) map_sig["h_l2jjmass"]               = SetupHist("h_l2jjmass_"          + name,"Invariant mass of the two leading jets and second muectron",100,0,1000,"M_{l2jj} GeV");


  map_sig["h_LeptonEta"]              = SetupHist("h_LeptonEta_"         + name,"leading lepton eta",60,-3.,3., "#eta_{l}");
  map_sig["h_LeptonPhi"]              = SetupHist("h_LeptonPhi_"         + name,"leading lepton phi",64,-3.2,3.2);
  map_sig["h_LeptonPt"]               = SetupHist("h_LeptonPt_"          + name,"lepton pt",250,0,500);
  map_sig["h_LeptonE"]               = SetupHist("h_LeptonE_"          + name,"lepton e",500,0,500);
  map_sig["h_leadingLeptonPt"]        = SetupHist("h_leadingLeptonPt_"   + name,"leading lepton pt",100,0,500);

  map_sig2["h_LeptonRelIso_pt"]           = SetupHist2("h_LeptonRelIso_pt_"      + name,"leading lepton relIso",100., 0., 500., 50,0.,100.,"lep P_{T} (GeV)", "Iso (GeV");

  if(nmu > 1 || nmu < 0) {
    map_sig["h_secondLeptonPt"]         = SetupHist("h_secondLeptonPt_"    + name,"secondary lepton pt",60,0,300, "lep_{2} P_{T} (GeV)");
    map_sig["h_secondLeptonEta"]        = SetupHist("h_secondLeptonEta_"   + name,"second lepton eta",60,-3.,3., "lep_{2} #eta");
    map_sig["h_secondLeptonMiniRelIso"]     = SetupHist("h_secondLeptonMiniRelIso_"      + name,"leading lepton mini relIso",100,0,1.);
  }
  map_sig["h_leadingLeptonEta"]       = SetupHist("h_leadingLeptonEta_"  + name,"leading lepton eta",60,-3.,3.,  "lep_{1} #eta");

  map_sig["h_LeptonIso"]              = SetupHist("h_LeptonIso_"         + name,"leading lepton relIso",50,0,10., "Iso (GeV");
  map_sig["h_LeptonRelIso"]           = SetupHist("h_LeptonRelIso_"      + name,"leading lepton relIso",100,-1.,1., "Iso (GeV");

  map_sig["h_LeptonDXY"]              = SetupHist("h_LeptonDXY_"         + name," leading lepton DXY", 1000, -1. , 1.25,"d_{XY}");
  map_sig["h_LeptonDXYSig"]              = SetupHist("h_LeptonDXYSig_"         + name," leading lepton DXYSig", 1000, -50. , 50.,"SIP");


  /// Lepton/Jet/Lepton dR                                                                                                                                                                                                                                                                                                                    
  map_sig["h_LeptonJetdR"]            = SetupHist("h_LeptonJetdR_"       + name,"lepton jet dR",50,0,5, "#Delta R(l,j)");
  map_sig["h_LeptonAwayJetdR"]        = SetupHist("h_LeptonAwayJetdR_"   + name, "away jet dr", 50,0,5,"#Delta R(l,away(j))");
  map_sig["h_leadLeptonAwayJetRatio"]        = SetupHist("h_leadLeptonAwayJetRatio_"   + name, "away jet / lepton", 100,0,5,"P_{T}(J)/P_{T}(l)");
  map_sig["h_secondLeptonAwayJetRatio"]        = SetupHist("h_secondLeptonAwayJetRatio_"   + name, "away jet / lepton", 100,0,5,"P_{T}(J)/P_{T}(l)");
  map_sig["h_LeptondR"]           = SetupHist("h_LeptondR_"      + name,"leading lepton dR",50,0,5, "#Delta R(l,l)");
  map_sig["h_leadLeptondR"]           = SetupHist("h_leadLeptondR_"      + name,"leading lepton dR",50,0,5, "#Delta R(l,l)");
  map_sig["h_secondLeptondR"]           = SetupHist("h_secondLeptondR_"      + name,"leading lepton dR",50,0,5, "#Delta R(l,l)");
  map_sig["h_leadLeptondPhi"]         = SetupHist("h_leadLeptondPhi_"    + name,"leading lepton dPhi",50,-5,5);
  map_sig["h_leadJetdR"]                = SetupHist("h_leadJetdR_"         + name,"leading jet dR",50,0,5, "#Delta R(j,j)");
  map_sig["h_leadJetdPhi"]              = SetupHist("h_leadJetdPhi_"       + name,"leading jet dPhi",50,-5,5, "#Delta R(fj,fj)");
  map_sig["h_leadJetFatJetdR"]                = SetupHist("h_leadJetFatJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetFatJetdPhi"]              = SetupHist("h_leadJetFatJetdPhi_"       + name,"leading jet dPhi",50,-5,5);

  //// Jet Plots                                                                                                                                                                

  map_sig["h_FatJetPt"]             = SetupHist("h_FatJetPt_"      + name,"leading jet pt",100,0,1000,"FatJet P_{T} (GeV)");
  map_sig["h_FatJetEta"]            = SetupHist("h_FatJetEta_"      + name,"leading jet pt",120,-5,5,"FatJet #eta");
  map_sig["h_FatJetPhi"]            = SetupHist("h_FatJetPhi_"      + name,"leading jet pt",64,-3.2,3.2);
  map_sig["h_FatJetM"]            = SetupHist("h_FatJetM_"      + name,"jet M",200,0.,400.);
  map_sig["h_FatJetTau21"]            = SetupHist("h_FatJetTau21_"      + name,"leading tau21",50,0.,2.);

  map_sig["h_FatJetPuppiPt"]             = SetupHist("h_FatJetPuppiPt_"      + name,"leading jet pt",100,0,1000,"FatJet P_{T} (GeV)");
  map_sig["h_FatJetPuppiEta"]            = SetupHist("h_FatJetPuppiEta_"      + name,"leading jet pt",120,-5,5,"FatJet #eta");
  map_sig["h_FatJetPuppiPhi"]            = SetupHist("h_FatJetPuppiPhi_"      + name,"leading jet pt",64,-3.2,3.2);
  map_sig["h_FatJetPuppiTau21"]            = SetupHist("h_FatJetPuppiTau21_"      + name,"leading tau21",50,0.,2.);


  map_sig["h_leadingJetPt"]           = SetupHist("h_leadingJetPt_"      + name,"leading jet pt",60,0,300,"j_{1} P_{T} (GeV)");
  map_sig["h_secondJetPt"]            = SetupHist("h_secondJetPt_"       + name,"secondary jet pt",60,0,300,"j_{2} P_{T} (GeV)");
  map_sig["h_HT"]                     = SetupHist("h_HT_"                + name,"sum jet pt",50,0,1000, "H_{T} (GeV)");
  map_sig["h_ST"]                     = SetupHist("h_ST_"                + name,"sum event pt",50,0,1500,"S_{T} (GeV)");
  map_sig["h_jets_pt"]                = SetupHist("h_jets_pt_"           + name,"jet pt",60,0,300,"Jet P_{T} (GeV)");
  map_sig["h_jets_eta"]               = SetupHist("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-5,5,"jet #eta" );
  map_sig["h_jets_phi"]               = SetupHist("h_jets_phi_"          + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"]         = SetupHist("h_pileupJetIDMVA_"    + name, "" ,100, -1.,1.);
  map_sig["h_bTag"]                   = SetupHist("h_bTag_"              + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"]                  = SetupHist("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nfatjets"]                  = SetupHist("h_Nfatjets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets_l"]                 = SetupHist("h_Nbjets_l_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nbjets_m"]                 = SetupHist("h_Nbjets_m_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nbjets_t"]                 = SetupHist("h_Nbjets_t_"            + name,"number of b jets",5,0,5);

  map_sig["h_Nbjets_all_l"]                 = SetupHist("h_Nbjets_all_l_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nbjets_all_m"]                 = SetupHist("h_Nbjets_all_m_"            + name,"number of b jets",5,0,5);
  map_sig["h_Nbjets_all_t"]                 = SetupHist("h_Nbjets_all_t_"            + name,"number of b jets",5,0,5);

  map_sig["h_lep_jet_dphi"]           =      SetupHist("h_lep_jet_dphi_"            + name,"dphi lepton jets", 50, 0., 5.);
  map_sig["h_leading_jets_eta"]               = SetupHist("h_leading_jets_eta_"          + name,"#eta distribution of the two leading_jets",120,-5,5);
  map_sig["h_second_jets_eta"]               = SetupHist("h_second_jets_eta_"          + name,"#eta distribution of the two second_jets",120,-5,5);
  map_sig["h_third_jets_eta"]               = SetupHist("h_third_jets_eta_"          + name,"#eta distribution of the two third_jets",120,-5,5);
  map_sig["h_fourth_jets_eta"]               = SetupHist("h_fourth_jets_eta_"          + name,"#eta distribution of the two fourth_jets",120,-5,5);

  /// dPhi/MT                                                                                                                                                                                                                                                                                                                                 
  map_sig["h_MTlepton"]               = SetupHist("h_MTlepton_"        + name,"Mt",100,0.0,500.0, "M_{T} (GeV)");
  map_sig["h_dphi_METlepton"]         = SetupHist("h_dphi_METlepton_"  + name , "METlepdphi", 50, -5., 5.);

  map_sig["h_contraMTlepton"]               = SetupHist("h_contraMTlepton_"        + name,"Mt",100,0.0,500.0);

  /// MET plots                                                                                                                                                                                                                                                                                                                               
  map_sig["h_PFMET"]                  = SetupHist("h_PFMET_"               + name,"Missing Et",100,0.0,500.0,"slash{E}_{T}^{miss} (GeV)");
  map_sig["h_PFMET_phi"]              = SetupHist("h_PFMET_phi_"           + name,"Missing Et",100,-3.2,3.2);


  map_sig["h_nVertices"]              = SetupHist("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);
  /// Charge plot                                                                                                                                                                                                                                                                                                                             
  map_sig["h_sumcharge"]              = SetupHist("h_sumcharge_"         + name,"Charge of the lepton pair",6,-3,3);

  /// Number of objects                                                                                                                                                                                                                                                                                                                       
  map_sig["h_Nmuons"]                 = SetupHist("h_Nmuons_"           + name,"number of mu",5,0,5);

  map_sig["h_Nelectrons"]   = SetupHist("h_Nelectrons_"           + name,"number of el",5,0,5, "N_{electrons}");

  map_sig["h_Nvtx"]                   = SetupHist("h_Nvtx_"            + name,"number of vertices",40,0,40.);


}





void SignalPlotsMM::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  std::vector<snu::KFatJet> fatjets;
  std::vector<snu::KJet> alljets;
  Fill(ev,muons, electrons, jets, alljets, fatjets,  weight);
}

void SignalPlotsMM::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, std::vector<snu::KJet>& alljets,std::vector<snu::KFatJet>& fatjets, Double_t weight) {
  
  bool debug =false;
  if(debug)cout<< "Plotting [1] " << endl;
  Fill("h_Nelectrons", electrons.size(), weight);
  Fill("h_Nmuons", muons.size(), weight);
  

  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  float lldijetmass_tmp=-9999.;
  UInt_t m(0),n(0);
  float leadawayjetratio = -9999.;
  float secondawayjetratio = -9999.;
  float min_ejet_Dr=10000.;  
  float min_eleadawayjet_Dr= -10000.;
  for(UInt_t i=0; i<muons.size(); i++){ 
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =muons[i].DeltaR(jets[emme]);
      //float dphi = fabs(TVector2::Phi_mpi_pi(muons[i].Phi()- jets[emme].Phi()));
      if(dR > 0.5) {
	if(dR > min_eleadawayjet_Dr) {
	  min_eleadawayjet_Dr=  dR;
	  if(i==0)leadawayjetratio = jets[emme].Pt() / muons[i].Pt();
	  if(i==1)secondawayjetratio = jets[emme].Pt() / muons[i].Pt();
	}	
      }
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;

    }
  }
  
  float min_lep0jet_Dr = 10000.;
  if(muons.size() > 0){
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =muons[0].DeltaR(jets[emme]);
      if(dR< min_lep0jet_Dr) min_lep0jet_Dr=dR;
    }
  }
  float min_lep1jet_Dr = 10000.;
  if(muons.size() > 1){
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =muons[1].DeltaR(jets[emme]);
      if(dR< min_lep1jet_Dr) min_lep1jet_Dr=dR;
    }
  }
    
  float min_ll_Dr=10000.;
  float min_ll_DPhi=10000.;
  for(UInt_t i=0; i<muons.size(); i++){
     for(UInt_t j=0; j<muons.size(); j++){
      if(i==j) continue;
      float dPhi = fabs(TVector2::Phi_mpi_pi(muons[i].Phi() - muons[j].Phi() ));
      float dR =muons[i].DeltaR(muons[j]);
      if(dR < min_ll_Dr) min_ll_Dr = dR;
      if(dPhi < min_ll_DPhi) min_ll_DPhi = dPhi;
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



  if(muons.size()!=0)Fill("h_LeptondR",min_ll_Dr,weight);
  if(muons.size()!=0)Fill("h_leadLeptondR",min_lep0jet_Dr,weight);
  if(muons.size()>1)Fill("h_secondLeptondR",min_lep1jet_Dr,weight);
  if(muons.size()!=0)Fill("h_leadLeptondPhi",min_ll_DPhi,weight);


  if(jets.size()!=0){
    if(muons.size()!=0){
      Fill("h_LeptonJetdR",min_ejet_Dr,weight);
      Fill("h_LeptonAwayJetdR",min_eleadawayjet_Dr,weight);
      Fill("h_leadLeptonAwayJetRatio",leadawayjetratio,weight);
      Fill("h_secondLeptonAwayJetRatio",secondawayjetratio,weight);
    }
    if(jets.size() > 1)Fill("h_leadJetdR",min_jj_Dr,weight);
    if(jets.size() > 1)Fill("h_leadJetdPhi",min_jj_DPhi,weight);
  }

  float min_jfj_Dr=10000.;
  float min_jfj_DPhi=10000.;
  for(UInt_t i=0; i<jets.size(); i++){
    for(UInt_t j=0; j<fatjets.size(); j++){
      float dR =jets[i].DeltaR(fatjets[j]);
      float dPhi = fabs(TVector2::Phi_mpi_pi(jets[i].Phi() - fatjets[j].Phi()));
      if(dR < min_jfj_Dr) min_jfj_Dr = dR;
      if(dR < min_jfj_DPhi) min_jfj_DPhi = dPhi;
    }
  }

  if(jets.size()!=0){
    if(fatjets.size()!=0){
      if(jets.size() > 1)Fill("h_leadJetFatJetdR",min_jfj_Dr,weight);
      if(jets.size() > 1)Fill("h_leadJetFatJetdPhi",min_jfj_DPhi,weight);
      
    }
  }


  if(debug)cout<< "Plotting [2] " << endl;  
  int nbjetl=0;
  int nbjetm=0;
  int nbjett=0;
  int nbjetl_all=0;
  int nbjetm_all=0;
  int nbjett_all=0;

  /// use CSVM https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
  float leadjetmass=0.;
  float contramass(-9999.);
  int jet_eta1=0;
  int jet_eta2=0;
  float lldijetmass=-9999.;
  int mlm(0);
  int nlm(0);
  for(UInt_t emme=0; emme<jets.size(); emme++){
    
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if(emme==0 && enne == 1) leadjetmass = dijetmass_tmp;
      if(muons.size() ==2){
	lldijetmass_tmp= (jets[emme]+jets[enne]+muons[0]+muons[1]).M();
	if ( fabs(lldijetmass_tmp-80.4) < fabs(lldijetmass-80.4) ) {
	  lldijetmass = lldijetmass_tmp;
	  mlm = emme;
	  nlm = enne;
	}
      }
      if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {
	dijetmass = dijetmass_tmp;
	m = emme;
	n = enne;

	if(jets[m].Eta() < -2.1){
          jet_eta1=1;
        }
        else  if(jets[m].Eta() < -1.5){
          jet_eta1=2;
        }
        else  if(jets[m].Eta() < -0.8){
          jet_eta1=3;
	}
        else  if(jets[m].Eta() < 0.){
          jet_eta1=4;
        }
        else  if(jets[m].Eta() < 0.8){
          jet_eta1=5;
        }
	else  if(jets[m].Eta() < 1.5){
          jet_eta1=6;
        }
        else  if(jets[m].Eta() < 2.1){
          jet_eta1=7;
        }
	else  jet_eta1=8;

	if(jets[n].Eta() < -2.1){
          jet_eta2=1;
        }
        else  if(jets[n].Eta() < -1.5){
          jet_eta2=2;
        }
	else  if(jets[n].Eta() < -0.8){
          jet_eta2=3;
        }
        else  if(jets[n].Eta() < 0.){
          jet_eta2=4;
        }
        else  if(jets[n].Eta() < 0.8){
          jet_eta2=5;
        }
	else  if(jets[n].Eta() < 1.5){
          jet_eta2=6;
        }
        else  if(jets[n].Eta() < 2.1){
          jet_eta2=7;
        }
        else  jet_eta2=8;

        float dPhi = fabs(TVector2::Phi_mpi_pi(jets[emme].Phi() - jets[enne].Phi()));
        contramass=2*jets[emme].Pt()*jets[enne].Pt()*(1+cos(dPhi));
        contramass=sqrt(contramass);

      }
      }
    }
  if(jets.size() > 1)  Fill("h_contraMTlepton",contramass, weight);
  float fmass = 9999.;
  int ifn=-999;
  for(UInt_t ifj =0; ifj < fatjets.size(); ifj++){
    float fmass_tmp=fatjets[ifj].PrunedMass();
    if(fabs(fmass_tmp - 80.4) <  fabs(fmass - 80.4)){
      fmass=fmass_tmp;
      ifn=ifj;
    }
  }

  
  float lljjmass=0.;
  float lmeanjjmass=0.;
  float ldiffmeanjjmass=0.;

  if(muons.size() ==2 ){
    Fill("h_llmass", (muons[0]+muons[1]).M(),weight);
    Fill("h_llpt", (muons[0]+muons[1]).Pt(),weight);
    if(jets.size() >= 2){
      Fill("h_l1jjmass", (muons[0] + jets[m] + jets[n]).M(),weight);
      Fill("h_l2jjmass", (muons[1] + jets[m] + jets[n]).M(),weight);
      
      lljjmass = (muons[0] +muons[1] + jets[m] + jets[n]).M();
      lmeanjjmass = ((muons[0] + jets[m] + jets[n]).M() +  (muons[1] + jets[m] + jets[n]).M()) / 2.;
      ldiffmeanjjmass = ((muons[0] + jets[m] + jets[n]).M() -  (muons[1] + jets[m] + jets[n]).M()) / 2.;
      Fill("h_lljjmass", (muons[0] +muons[1] + jets[m] + jets[n]).M(),weight);
    }

  }

  
  
  if(debug)cout<< "Plotting [3] " << endl;  

   
  int sum_charge(0);
  int imu(0);


  
  if(muons.size()==2&& jets.size() > 1){

    if( jets.size()>=1) Fill("h_llj1mass", (muons[0] + muons[1]+jets[0]).M(),weight);
    if( jets.size()>=1) Fill("h_llj2mass", (muons[0] + muons[1]+jets[1]).M(),weight);
    if( jets.size()>=1) Fill("h_l1jmass", (muons[0]+jets[0]).M(),weight);
    if( jets.size()>=1) Fill("h_l2jmass", ( muons[1]+jets[0]).M(),weight);
    if(jets.size()>1){
      Fill("h_l2jjmass", (muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_lljjmass", (muons[0] + muons[1]+jets[m]+jets[n]).M(),weight);
      Fill("h_l1jjmass", (muons[0]+jets[m]+jets[n]).M(),weight);

    }
  }
  
  int iel(0);
  
  for(std::vector<snu::KMuon>::iterator muit = muons.begin(); muit != muons.end(); muit++, iel++){
    
    
    Fill("h_LeptonPt", muit->Pt(),weight);
    Fill("h_LeptonE", muit->Energy(),weight);
    Fill("h_LeptonPhi",muit->Phi(),weight);
    Fill("h_LeptonEta",muit->Eta(),weight);
    Fill("h_LeptonDXY", muit->dXY(),weight);
    Fill("h_LeptonDXYSig", muit->dXYSig2D() ,weight);
   
    float mu_reliso_04 =  muit->RelIso04();
    float mu_minireliso = muit->PFRelMiniIsoBeta();
    
    Fill("h_LeptonIso", muit->RelIso04(),weight);

    Fill("h_LeptonRelIso", mu_reliso_04,weight);
    Fill("h_LeptonRelIso_pt", muit->Pt(), mu_reliso_04*muit->Pt(),weight);
    if(iel==2){
      Fill("h_thirdLeptonPt", muit->Pt(),weight);
      Fill("h_thirdLeptonRelIso", mu_reliso_04,weight);
      Fill("h_thirdLeptonMiniRelIso", mu_minireliso,weight);
      Fill("h_thirdLeptonEta",muit->Eta(),weight);
    }
    if(iel==3){
      Fill("h_fourthLeptonPt", muit->Pt(),weight);
      Fill("h_fourthLeptonRelIso", mu_reliso_04,weight);
      Fill("h_fourthLeptonMiniRelIso", mu_minireliso,weight);
      Fill("h_fourthLeptonEta",muit->Eta(),weight);
    }

    if(iel==1){
      Fill("h_secondLeptonPt", muit->Pt(),weight);
      Fill("h_secondLeptonEta",muit->Eta(),weight);
      Fill("h_secondLeptonMiniRelIso", mu_minireliso,weight);
    }
    if(iel==0){
      Fill("h_leadingLeptonEta",muit->Eta(),weight);
      Fill("h_leadingLeptonPt", muit->Pt(),weight);

    }
    
    sum_charge += muit->Charge();
  }
  
  Fill("h_sumcharge",sum_charge,weight);
  
  //// Fillplots
  for(unsigned int i=0 ; i < muons.size(); i++){
    float dphi = fabs(TVector2::Phi_mpi_pi(muons.at(i).Phi()- ev.METPhi(snu::KEvent::pfmet)));
    float MT = sqrt(2.* muons.at(i).Et()*ev.PFMET() * (1 - cos( dphi)));
    Fill("h_MTlepton",MT, weight);
    Fill("h_dphi_METlepton",dphi, weight);
  }


  if(debug)cout<< "Plotting [5] " << endl;

  Fill("h_PFMET",ev.PFMET(), weight);

  Fill("h_nVertices", ev.nVertices(), weight); 
  

  
  Fill("h_Nvtx",ev.nVertices(), weight);
  
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight); 
    Fill("h_deltaRjj", jets[m].DeltaR(jets[n]),weight);
  }

  if(fatjets.size()> 0){
    Fill("h_fjsdmass", (fatjets[ifn]).SoftDropMass(),weight);
  }
  
  float ht=0.;
  float htall=0.;

  if(fatjets.size()> 0){
    Fill("h_FatJetPt", fatjets[ifn].Pt(),weight);
    Fill("h_FatJetEta", fatjets[ifn].Eta(),weight);
    Fill("h_FatJetPhi", fatjets[ifn].Phi(),weight);
    Fill("h_FatJetM", fatjets[ifn].PrunedMass(),weight);
    Fill("h_FatJetTau21", (fatjets[ifn].Tau2()/fatjets[ifn].Tau1()),weight);
    Fill("h_FatJetPuppiPt", fatjets[ifn].PuppiPt(),weight);
    Fill("h_FatJetPuppiEta", fatjets[ifn].PuppiEta(),weight);
    Fill("h_FatJetPuppiPhi", fatjets[ifn].PuppiPhi(),weight);
    Fill("h_FatJetPuppiTau21", (fatjets[ifn].PuppiTau2()/fatjets[ifn].PuppiTau1()),weight);

    
    for(UInt_t j=0; j < fatjets.size(); j++){
      ht+= fatjets[j].Pt();
    }
  }
  

  float max_deta=0.;
  
  for(UInt_t j=0; j < alljets.size(); j++){ 
    htall+= alljets[j].Pt();
  }

  for(UInt_t j=0; j < jets.size(); j++){ 


    ht+= jets[j].Pt();
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    if(j==0)     Fill("h_leading_jets_eta",jets[j].Eta(),weight);
    if(j==1)     Fill("h_second_jets_eta",jets[j].Eta(),weight);
    if(j==2)     Fill("h_third_jets_eta",jets[j].Eta(),weight);
    if(j==3)     Fill("h_fourth_jets_eta",jets[j].Eta(),weight);
    Fill("h_jets_pt", jets[j].Pt(),weight);
    Fill("h_jets_eta",jets[j].Eta(),weight);
    Fill("h_PileupJetIDMVA", jets[j].PileupJetIDMVA(),weight);
    Fill("h_jets_phi",jets[j].Phi(),weight);
    Fill("h_bTag",jets[j].CSVInclV2(),weight);
    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Loose)) nbjetl++;
    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Medium)) nbjetm++;
    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Tight)) nbjett++;
  }
  
  for(UInt_t j=0; j < alljets.size(); j++){
    if(alljets.at(j).IsBTagged(KJet::CSVv2, KJet::Loose)) nbjetl_all++;
    if(alljets.at(j).IsBTagged(KJet::CSVv2, KJet::Medium)) nbjetm_all++;
    if(alljets.at(j).IsBTagged(KJet::CSVv2, KJet::Tight)) nbjett_all++;

  }

    

  float st = ht + ev.PFMET();
  float stall = htall + ev.PFMET();
  for(unsigned int i=0 ; i < muons.size(); i++){
    st+= muons.at(i).Pt();
    stall+= muons.at(i).Pt();
  }
  
  Fill("h_HT", ht,weight);
  Fill("h_ST", st,weight);
  Fill("h_Nbjets_l",nbjetl, weight);
  Fill("h_Nbjets_m",nbjetm, weight);
  Fill("h_Nbjets_t",nbjett, weight);
  Fill("h_Nbjets_all_l",nbjetl_all, weight);
  Fill("h_Nbjets_all_m",nbjetm_all, weight);
  Fill("h_Nbjets_all_t",nbjett_all, weight);

  Fill("h_Njets",jets.size(), weight);
  Fill("h_Nfatjets",fatjets.size(), weight);

  
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


TH1D* SignalPlotsMM::SetupHist(TString hname, TString alabel, int nbin, double xmin, double xmax, TString xtitle ){

  TH1D* htmp= new TH1D(hname,alabel,nbin,xmin,xmax);
  htmp->GetXaxis()->SetTitle(xtitle);
  return htmp;
}


TH2D* SignalPlotsMM::SetupHist2(TString hname, TString alabel, int nbinx, double xmin, double xmax, int nbiny, double ymin, double ymax, TString xtitle , TString ytitle){

  TH2D* htmp= new TH2D(hname,alabel,nbinx,xmin,xmax, nbiny, ymin, ymax);
  htmp->GetXaxis()->SetTitle(xtitle);
  htmp->GetYaxis()->SetTitle(ytitle);
  return htmp;
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




