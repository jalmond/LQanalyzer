#include "SignalPlotsEE.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


/// Style
#include "TStyle.h"

using namespace std;



SignalPlotsEE::SignalPlotsEE(TString name, int nel): StdPlots(name){

  TH1::SetDefaultSumw2(true);
  
  
  bool singleel = (nel < 0)  ?   true : (nel == 1);
  bool doubleel = (nel < 0)  ?   true : (nel == 2);
  bool triel = (nel < 0)  ?   true : (nel == 3);
  bool quadel = (nel < 0)  ?   true : (nel == 4);

  if(doubleel){
    map_sig["h_llmass"]                 = SetupHist("h_llmass_"           + name,"Invariant mass of the two leading electrons",1000,0,1000,"M_{ll} GeV");
    map_sig["h_llpt"]                 = SetupHist("h_llpt_"           + name,"Invariant pt of the two leading electrons",500,0,1000,"P_T (ll) GeV");
    map_sig["h_lljjmass"]               = SetupHist("h_lljjmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{lljj} GeV");
    map_sig["h_llfjmass"]               = SetupHist("h_llfjmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{lljj} GeV");
    map_sig["h_lljmass"]                = SetupHist("h_lljmass_"         + name,"Invariant mass of the four particles",200,0,2000,"M_{llj} GeV");
  }
  
  map_sig["h_jjmass"]                 = SetupHist("h_dijetsmass_"        + name,"Invariant mass of the two leading jets",500,0.,500.,"M_{jj} GeV");
  map_sig["h_fjmass"]                 = SetupHist("h_fatjetsmass_"        + name,"Invariant mass of the two leading jets",500,0.,500.,"M_{jj} GeV");

  /// ALL Lepton plots  
  map_sig["h_LeptonEta"]              = SetupHist("h_LeptonEta_"         + name,"leading lepton eta",60,-3.,3., "#eta_{l}");
  map_sig["h_LeptonPhi"]              = SetupHist("h_LeptonPhi_"         + name,"leading lepton phi",64,-3.2,3.2);
  map_sig["h_LeptonPt"]               = SetupHist("h_LeptonPt_"          + name,"lepton pt",250,0,1000);
  map_sig["h_LeptonPt_B"]               = SetupHist("h_LeptonPt_B_"          + name,"lepton pt",250,0,1000);
  map_sig["h_LeptonPt_EC"]               = SetupHist("h_LeptonPt_EC_"          + name,"lepton pt",250,0,1000);
  map_sig["h_LeptonEnergy"]           = SetupHist("h_LeptonEnergy_"          + name,"lepton e",500,0,500);
  map_sig["h_leadingLeptonPt"]        = SetupHist("h_leadingLeptonPt_"   + name,"leading lepton pt",100,0,500);

  if(nel > 1 || nel < 0) {
    map_sig["h_secondLeptonPt"]         = SetupHist("h_secondLeptonPt_"    + name,"secondary lepton pt",60,0,300);
    map_sig["h_secondLeptonEta"]        = SetupHist("h_secondLeptonEta_"   + name,"second lepton eta",60,-3.,3.);    
    map_sig["h_secondLeptonRelIso_b"]     = SetupHist("h_secondLeptonRelIso_b_"      + name,"leading lepton relIso",1000,0,10.);
    map_sig["h_secondLeptonRelIso_ec"]     = SetupHist("h_secondLeptonRelIso_ec_"      + name,"leading lepton relIso",1000,0,10.);
    map_sig["h_secondLeptonMiniRelIso"]     = SetupHist("h_secondLeptonMiniRelIso_"      + name,"leading lepton mini relIso",100,0,1.);  
  }
  map_sig["h_leadingLeptonEta"]       = SetupHist("h_leadingLeptonEta_"  + name,"leading lepton eta",60,-3.,3.);
  
  map_sig["h_LeptonIso"]              = SetupHist("h_LeptonIso_"         + name,"leading lepton relIso",50,0,10.);
  map_sig["h_LeptonRelIso"]           = SetupHist("h_LeptonRelIso_"      + name,"leading lepton relIso",1000,0,10.);
  map_sig["h_LeptonDXY"]              = SetupHist("h_LeptonDXY_"         + name," leading lepton DXY", 1000, -0.25 , 0.25);
  map_sig["h_LeptonDXYSig"]              = SetupHist("h_LeptonDXYSig_"         + name," leading lepton DXYSig", 1000, -10. , 10.);
  
  /// Lepton/Jet/Lepton dR
  map_sig["h_LeptonJetdR"]            = SetupHist("h_LeptonJetdR_"       + name,"lepton jet dR",50,0,5);
  map_sig["h_LeptonAwayJetdR"]        = SetupHist("h_LeptonAwayJetdR_"   + name, "away jet dr", 50,0,5);
  map_sig["h_leadLeptondR"]           = SetupHist("h_leadLeptondR_"      + name,"leading lepton dR",50,0,5);
  map_sig["h_leadLeptondPhi"]         = SetupHist("h_leadLeptondPhi_"    + name,"leading lepton dPhi",50,-5,5);
  map_sig["h_leadJetdR"]                = SetupHist("h_leadJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetdPhi"]              = SetupHist("h_leadJetdPhi_"       + name,"leading jet dPhi",50,-5,5);
  map_sig["h_leadJetFatJetdR"]                = SetupHist("h_leadJetFatJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetFatJetdPhi"]              = SetupHist("h_leadJetFatJetdPhi_"       + name,"leading jet dPhi",50,-5,5);


  //// Jet Plots

  map_sig["h_FatJetPt"]             = SetupHist("h_FatJetPt_"      + name,"leading jet pt",100,0,1000);
  map_sig["h_FatJetEta"]            = SetupHist("h_FatJetEta_"      + name,"leading jet pt",120,-5,5);
  map_sig["h_FatJetPhi"]            = SetupHist("h_FatJetPhi_"      + name,"leading jet pt",64,-3.2,3.2);

  map_sig["h_leadingJetPt"]           = SetupHist("h_leadingJetPt_"      + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"]            = SetupHist("h_secondJetPt_"       + name,"secondary jet pt",60,0,300);
  map_sig["h_HT"]                     = SetupHist("h_HT_"                + name,"sum jet pt",50,0,1000);
  map_sig["h_ST"]                     = SetupHist("h_ST_"                + name,"sum event pt",50,0,1000);
  map_sig["h_jets_pt"]                = SetupHist("h_jets_pt_"           + name,"jet pt",60,0,300);
  map_sig["h_jets_eta"]               = SetupHist("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-3,3);
  map_sig["h_jets_phi"]               = SetupHist("h_jets_phi_"          + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"]         = SetupHist("h_pileupJetIDMVA_"    + name, "" ,100, -1.,1.);
  map_sig["h_bTag"]                   = SetupHist("h_bTag_"              + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"]                  = SetupHist("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nfatjets"]                  = SetupHist("h_Nfatjets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]                 = SetupHist("h_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_lep_jet_dphi"]           =      SetupHist("h_lep_jet_dphi_"            + name,"dphi lepton jets", 50, 0., 5.);
  map_sig["h_massdrop"]                     = SetupHist("h_massdrop_"            + name,"number of b jets", 50, 0., 50);


  map_sig["h_leading_jets_eta"]               = SetupHist("h_leading_jets_eta_"          + name,"#eta distribution of the two leading_jets",120,-5,5);
  map_sig["h_second_jets_eta"]               = SetupHist("h_second_jets_eta_"          + name,"#eta distribution of the two second_jets",120,-5,5);
  map_sig["h_third_jets_eta"]               = SetupHist("h_third_jets_eta_"          + name,"#eta distribution of the two third_jets",120,-5,5);
  map_sig["h_fourth_jets_eta"]               = SetupHist("h_fourth_jets_eta_"          + name,"#eta distribution of the two fourth_jets",120,-5,5);

  /// dPhi/MT
  map_sig["h_contraMTlepton"]               = SetupHist("h_contraMTlepton_"        + name,"Mt",100,0.0,500.0);
  map_sig["h_MTlepton"]               = SetupHist("h_MTlepton_"        + name,"Mt",100,0.0,500.0);
  map_sig["h_dphi_METlepton"]         = SetupHist("h_dphi_METlepton_"  + name , "METlepdphi", 50, -5., 5.);
 
  /// MET plots
  map_sig["h_PFMET"]                  = SetupHist("h_PFMET_"               + name,"Missing Et",100,0.0,500.0);

  map_sig["h_nVertices"]              = SetupHist("h_nVertices_"         + name,"number of even vertices",60,0.0,60.0);

  /// Charge plot
  map_sig["h_sumcharge"]              = SetupHist("h_sumcharge_"         + name,"Charge of the lepton pair",6,-3,3);

  /// Number of objects
  map_sig["h_Nmuons"]                 = SetupHist("h_Nmuons_"           + name,"number of mu",5,0,5);

  map_sig["h_Nelectrons"]   = SetupHist("h_Nelectrons_"           + name,"number of el",5,0,5, "N_{electrons}");

  map_sig["h_Nvtx"]                   = SetupHist("h_Nvtx_"            + name,"number of vertices",40,0,40.);


}

TH1D* SignalPlotsEE::SetupHist(TString hname, TString alabel, int nbin, double xmin, double xmax, TString xtitle ){

  TH1D* htmp= new TH1D(hname,alabel,nbin,xmin,xmax);
  htmp->GetXaxis()->SetTitle(xtitle);
  return htmp;
}

TH2D* SignalPlotsEE::SetupHist2(TString hname, TString alabel, int nbinx, double xmin, double xmax, int nbiny, double ymin, double ymax, TString xtitle , TString ytitle){

  TH2D* htmp= new TH2D(hname,alabel,nbinx,xmin,xmax, nbiny, ymin, ymax);
  htmp->GetXaxis()->SetTitle(xtitle);
  htmp->GetYaxis()->SetTitle(ytitle);
  return htmp;
}

void SignalPlotsEE::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets, Double_t weight) {
  std::vector<snu::KFatJet> fatjets;
  std::vector<snu::KJet> alljets;
  Fill(ev,muons, electrons, jets,alljets, fatjets,  weight);
}

void SignalPlotsEE::Fill(snu::KEvent ev, std::vector<snu::KMuon>& muons, std::vector<snu::KElectron>& electrons, std::vector<snu::KJet>& jets,  std::vector<snu::KJet>& alljets,  std::vector<snu::KFatJet>& fatjets, Double_t weight) {
  
  bool debug =false;
  if(debug)cout<< "Plotting [1] " << endl;
  Fill("h_Nelectrons", electrons.size(), weight, "N_{electrons}");
  Fill("h_Nmuons", muons.size(), weight, "N_{muons}");
  
  

  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);
  
  float min_ejet_Dr=10000.;  
  float min_eleadawayjet_Dr= -10000.;


  for(UInt_t i=0; i<electrons.size(); i++){ 
    for(UInt_t emme=0; emme<jets.size(); emme++){
      float dR =electrons[i].DeltaR(jets[emme]);
      //float dphi = fabs(TVector2::Phi_mpi_pi(electrons[i].Phi()- jets[emme].Phi()));
      if(dR > 0.5) {
	if(dR > min_eleadawayjet_Dr) min_eleadawayjet_Dr=  dR;
      }
      if(dR< min_ejet_Dr) min_ejet_Dr=dR;

    }
  }
  
  snu::KParticle closejet;
  float minejdR=0.7;
  float ptrel(0.);  float ptratio(0.);
  float massdrop(0.);
  for(UInt_t i=0; i<electrons.size(); i++){
    for(UInt_t emme=0; emme<alljets.size(); emme++){
      if(alljets[emme].Pt() != alljets[emme].Pt()) continue;
      float dR =electrons[i].DeltaR(alljets[emme]);
      if(dR < minejdR){
        closejet = alljets[emme];//GetCorrectedJetCloseToLepton(electrons[i], jets[emme]);
	minejdR= dR;

	TVector3 el3=  electrons[i].Vect();
	TVector3 jet3= closejet.Vect();
	TVector3 lepjetrel = jet3-el3;
        ptrel = (lepjetrel.Cross(el3)).Mag()/ lepjetrel.Mag();
	ptratio = electrons[i].Pt() / closejet.Pt();
	snu::KParticle lj = closejet+electrons[i];

	massdrop = (lj.M() - closejet.M());
      }
    }
  }
  
  
  Fill("h_relpt_lepjet", ptrel,weight);
  Fill("h_ratiopt_lepjet", ptratio,weight);
  Fill("h_massdrop", massdrop,weight);

    
  float min_ee_Dr=10000.;
  float min_ee_DPhi=10000.;
  for(UInt_t i=0; i<electrons.size(); i++){
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
      if(dPhi < min_jj_DPhi) min_jj_DPhi = dPhi;
    }
  }

  
  
  if(electrons.size()!=0)Fill("h_leadLeptondR",min_ee_Dr,weight);
  if(electrons.size()!=0)Fill("h_leadLeptondPhi",min_ee_DPhi,weight);


  if(jets.size()!=0){
    if(electrons.size()!=0){
      Fill("h_LeptonJetdR",min_ejet_Dr,weight);
      Fill("h_LeptonAwayJetdR",min_eleadawayjet_Dr,weight);
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
      if(jets.size() > 1)Fill("h_leadJetFatJetdR",min_jj_Dr,weight);
      if(jets.size() > 1)Fill("h_leadJetFatJetdPhi",min_jj_DPhi,weight);
    }
  }
  

  if(debug)cout<< "Plotting [2] " << endl;  
  int nbjetl=0;
  int nbjetm=0;
  int nbjett=0;
  /// use CSVM https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagPerformanceOP
  float contramass(-999.);
  int jet_eta1=0;
  int jet_eta2=0;
  for(UInt_t emme=0; emme<jets.size(); emme++){
    
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
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

  if((jets.size()>3) && (electrons.size() == 2)){
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
      }
      else if(jets[ij].Eta() < -1.5) {
	if(jets[ij].Eta() < most_backward){
	  index_b=ij;
	  most_backward=jets[ij].Eta();
	}
	m_forward_jet++;

      }
      else{
      }
    }
    
    for(unsigned int ij = 0 ; ij < jets.size(); ij++){
      if(ij == unsigned(index_b)) continue;
      if(ij == unsigned(index_f)) continue;
      central_jets.push_back( ij);
    }
    
    for(unsigned int ij = 0 ; ij < jets.size(); ij++){
      if(ij == unsigned(index_b)) continue;
      if(ij == unsigned(index_f)) continue;
      central_jets.push_back( ij);
    }
    float ce_dijetmass=9999.9;
    float ce_dijetmass_tmp=9999.9;
    

    int c_m(0), c_n(0);
    for(UInt_t emme=0; emme<central_jets.size(); emme++){
      for(UInt_t enne=1; enne<central_jets.size(); enne++) {
	if(emme == enne) continue;
	ce_dijetmass_tmp = (jets[central_jets[emme]] + jets[central_jets[enne]]).M();
	if ( fabs(ce_dijetmass_tmp-80.4) < fabs(ce_dijetmass-80.4) ) {
	  ce_dijetmass = ce_dijetmass_tmp;
	  c_m = central_jets[emme];
	  c_n = central_jets[enne];

	}
      }
    }
   

  }

  
  float lljjmass=0.;
  if(electrons.size() ==2 ){
    Fill("h_llmass", (electrons[0]+electrons[1]).M(),weight);
    Fill("h_llpt", (electrons[0]+electrons[1]).Pt(),weight);
    if(jets.size() >= 2){
      Fill("h_l1jjmass", (electrons[0] + jets[m] + jets[n]).M(),weight);
      Fill("h_l2jjmass", (electrons[1] + jets[m] + jets[n]).M(),weight);
      float l1jjmass= (electrons[0] + jets[m] + jets[n]).M();
      float l2jjmass= (electrons[1] + jets[m] + jets[n]).M();

      
      lljjmass= (electrons[0] +electrons[1] + jets[m] + jets[n]).M();
      Fill("h_lljjmass", (electrons[0] +electrons[1] + jets[m] + jets[n]).M(),weight);
    }
    if(fatjets.size() > 0){
      Fill("h_l1fjmass", (electrons[0] + fatjets[ifn]).M(),weight);
      Fill("h_l2fjmass", (electrons[1] + fatjets[ifn]).M(),weight);
      Fill("h_llfjmass", (electrons[0] +electrons[1] + fatjets[ifn]).M(),weight);
    } 
    
  }



  if(debug)cout<< "Plotting [3] " << endl;  
  
  int sum_charge(0);
  float osmass_closeZ(100000.);
  int nos(0.);
  if(electrons.size()>=2){
    for(unsigned int iel1 = 0 ; iel1< electrons.size()-1; iel1++){
      for(unsigned int iel2 = iel1+1 ; iel2< electrons.size(); iel2++){
	if(electrons[iel1].Charge() != electrons[iel2].Charge())  {
	  nos++;
	  if( fabs( (electrons[iel1]+electrons[iel2]).M() - 91.1) < fabs(osmass_closeZ - 91.1) ){
	    osmass_closeZ = (electrons[iel1]+electrons[iel2]).M();
	   }
	 }
      }
    }
  }
  int iel(0);
 
  for(std::vector<snu::KElectron>::iterator elit = electrons.begin(); elit != electrons.end(); elit++, iel++){
  
    Fill("h_LeptonPt", elit->Pt(),weight);
    if(fabs(elit->Eta()) < 1.5)      Fill("h_LeptonPt_B", elit->Pt(),weight);
    else Fill("h_LeptonPt_EC", elit->Pt(),weight);

    Fill("h_LeptonEnergy", elit->Energy(),weight);
    Fill("h_LeptonPhi",elit->Phi(),weight);
    Fill("h_LeptonEta",elit->Eta(),weight);




    Fill("h_LeptonDXY", elit->dxy(),weight);
    Fill("h_LeptonDXYSig", elit->dxySig2D() ,weight);

     
    float el_reliso_03 =  elit->PFRelIso(0.3);
    float el_iso_03 = elit->PFAbsIso(0.3);
    float el_minireliso = elit->PFRelMiniIso(true);
    
    Fill("h_LeptonIso", el_iso_03,weight);
    Fill("h_LeptonRelIso", el_reliso_03,weight);

    if(iel==1){
      Fill("h_secondLeptonPt", elit->Pt(),weight);

      Fill("h_secondLeptonMiniRelIso", el_minireliso,weight);
      Fill("h_secondLeptonEta",elit->Eta(),weight);
    }
    if(iel==0){
      Fill("h_leadingLeptonEta",elit->Eta(),weight);
      Fill("h_leadingLeptonMiniRelIso", el_minireliso,weight);
      Fill("h_leadingLeptonPt", elit->Pt(),weight);
    }
    
    sum_charge += elit->Charge();
  }
  
  Fill("h_sumcharge",sum_charge,weight);
  
  //// Fillplots
  for(unsigned int i=0 ; i < electrons.size(); i++){
    float dphi = fabs(TVector2::Phi_mpi_pi(electrons.at(i).Phi()- ev.METPhi(snu::KEvent::pfmet)));
    float MT = sqrt(2.* electrons.at(i).Et()*ev.PFMET() * (1 - cos( dphi)));
    Fill("h_MTlepton",MT, weight);
    Fill("h_dphi_METlepton",dphi, weight);
  }

  if(debug)cout<< "Plotting [5] " << endl;

  Fill("h_PFMET",ev.PFMET(), weight);
  Fill("h_nVertices", ev.nVertices(), weight);
  
  
  Fill("h_Nvtx",ev.PileUpInteractionsTrue(), weight);
  
  //// Mass plots
  if(jets.size()>1){
    Fill("h_jjmass", (jets[m]+jets[n]).M(),weight); 
  }
  if(fatjets.size()> 0){
    Fill("h_fjmass", (fatjets[ifn]).M(),weight);
  }

  float ht=0.;
  if(fatjets.size()> 0){
    Fill("h_FatJetPt", fatjets[ifn].Pt(),weight);
    Fill("h_FatJetEta", fatjets[ifn].Eta(),weight);
    Fill("h_FatJetPhi", fatjets[ifn].Phi(),weight);
    for(UInt_t j=0; j < fatjets.size(); j++){
      ht+= fatjets[j].Pt(); 
    }
  }


  vector<snu::KJet> central_jets;
  vector<snu::KJet> forward_jets;

  float max_deta=0.;
  snu::KParticle fjets;
  float htall=0.;
  for(UInt_t j=0; j < alljets.size(); j++){
    htall+= alljets[j].Pt();
  }
  for(UInt_t j=0; j < jets.size(); j++){ 

    if(fabs(jets[j].Eta()) < 1.5) central_jets.push_back(jets[j]);
    else forward_jets.push_back(jets[j]);
    ht+= jets[j].Pt(); 
    if(j==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(j==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    Fill("h_jets_pt", jets[j].Pt(),weight);
    Fill("h_jets_eta",jets[j].Eta(),weight);
    if(j==0)     Fill("h_leading_jets_eta",jets[j].Eta(),weight);
    if(j==1)     Fill("h_second_jets_eta",jets[j].Eta(),weight);
    if(j==2)     Fill("h_third_jets_eta",jets[j].Eta(),weight);
    if(j==3)     Fill("h_fourth_jets_eta",jets[j].Eta(),weight);

    Fill("h_PileupJetIDMVA", jets[j].PileupJetIDMVA(),weight);
    Fill("h_jets_phi",jets[j].Phi(),weight);
    Fill("h_bTag",jets[j].CSVInclV2(),weight);
    
    for(UInt_t i=0; i < jets.size(); i++){
      if(i==j) continue;
      float deta = fabs(jets[j].Eta() - jets[i].Eta() );
      if(deta > max_deta){
	max_deta=deta;
	fjets=jets[j]+jets[i];
      }
    }

    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Loose)) nbjetl++; 
    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Medium)) nbjetm++; 
    if(jets.at(j).IsBTagged(KJet::CSVv2, KJet::Tight)) nbjett++; 
    for(unsigned int iel2=0 ; iel2 < electrons.size(); iel2++){
      float dphi =fabs(TVector2::Phi_mpi_pi(electrons.at(iel2).Phi()- jets.at(j).Phi()));
      Fill("h_lep_jet_dphi", dphi,weight);
    }
  }
  

  float st = ht + ev.PFMET();
  float stall = htall + ev.PFMET();
  for(unsigned int i=0 ; i < electrons.size(); i++){
    st+= electrons.at(i).Pt();
  }

  
  Fill("h_HT", ht,weight);
  Fill("h_ST", st,weight);
  Fill("h_Nbjets_l",nbjetl, weight);
  Fill("h_Nbjets_m",nbjetm, weight);
  Fill("h_Nbjets_t",nbjett, weight);
  Fill("h_Njets",jets.size(), weight);
  Fill("h_Nfatjets",fatjets.size(), weight);

  if(debug)cout<< "Plotting [6] " << endl;
  return;
}/// End of Fill



void SignalPlotsEE::Write() {
 
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


SignalPlotsEE::SignalPlotsEE(): StdPlots(){
}


/**
 * Copy constructor.
 */
SignalPlotsEE::SignalPlotsEE(const SignalPlotsEE& sp): StdPlots(sp)
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


SignalPlotsEE& SignalPlotsEE::operator= (const SignalPlotsEE& sp)
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

SignalPlotsEE::~SignalPlotsEE() {
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


snu::KJet SignalPlotsEE::GetCorrectedJetCloseToLepton(snu::KElectron el, snu::KJet jet){
  //jet_LepAwareJECv2 = (raw_jet * L1 - lepton) * L2L3Res + lepton                                                                                                        
  float rawpt= jet.RawPt();
  float rawe= jet.RawE();

  float L1corr = jet.L1JetCorr();
  float l2l3res = jet.L2L3ResJetCorr();
  float leppt = el.Pt();
  float corr_pt = (rawpt*L1corr - leppt)*l2l3res + leppt;
  
  snu::KJet jet_corr(jet);
  return jet_corr;
  if(1){
    TLorentzVector v;
    v.SetPtEtaPhiM(jet.Pt(), jet.Eta(), jet.Phi(), jet.M());
    v=v*(corr_pt/jet.Pt());
    jet_corr.SetPtEtaPhiM(v.Pt(), v.Eta(), v.Phi(), v.M());
    return jet_corr;
  }
  return jet_corr;
}



void SignalPlotsEE::Fill(TString name, double value, double w, TString xlabel){
  std::map<TString, TH1*>::iterator it = map_sig.find(name);
  if(it!= map_sig.end())   {
    it->second->Fill(value, w);
    it->second->GetXaxis()->SetTitle(xlabel);
  }
  
  return;
}
 
void SignalPlotsEE::Fill(TString name, double value1, double value2, double w,  TString xlabel,  TString ylabel){
   std::map<TString, TH2*>::iterator it = map_sig2.find(name);
   if(it!= map_sig2.end()) {
     it->second->Fill(value1, value2, w);
     it->second->GetXaxis()->SetTitle(xlabel);
     it->second->GetYaxis()->SetTitle(ylabel);
     
   }
   return;
 }



void SignalPlotsEE::Fill(TString name, double value1, double value2, double value3, double w){
  std::map<TString, TH3*>::iterator it = map_sig3.find(name);
  if(it!= map_sig3.end()) it->second->Fill(value1, value2, value3, w);
  return;
}




