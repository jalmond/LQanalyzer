#include "JetPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

JetPlots::JetPlots(TString name) : StdPlots(name) {

  TH1::SetDefaultSumw2(true);
  map_sig["h_jjmass"]                 =     new TH1D("h_dijetsmass_"        + name,"Invariant mass of the two leading jets",500,0.,500.);
  map_sig["h_leadjetmass"]            =     new TH1D("h_leadjetsmass_"      + name,"Invariant mass of the two leading jets",150,0.,750.);
  map_sig["h_forward_jet_pt"]             =     new TH1D("h_forward_jet_pt_"                + name,"h_forward_jet_pt",60,0,300);
  map_sig["h_central_jet_pt"]             =     new TH1D("h_central_jet_pt_"                + name,"h_central_jet_pt",60,0,300);
  map_sig["h_forward_jet_eta"]             =     new TH1D("h_forward_jet_eta_"                + name,"h_forward_jet_eta",50,-2.5,2.5);
  map_sig["h_central_jet_eta"]             =     new TH1D("h_central_jet_eta_"                + name,"h_central_jet_eta",50,-2.5,2.5);
  //// Jet Plots
  map_sig["h_leadingJetPt"]           =     new TH1D("h_leadingJetPt_"      + name,"leading jet pt",60,0,300);
  map_sig["h_secondJetPt"]            =     new TH1D("h_secondJetPt_"       + name,"secondary jet pt",60,0,300);
  map_sig["h_HT"]                     =     new TH1D("h_HT_"                + name,"sum jet pt",50,0,1000);
  map_sig["h_ST"]                     =     new TH1D("h_ST_"                + name,"sum event pt",50,0,1000);
  map_sig["h_jets_pt"]                =     new TH1D("h_jets_pt_"           + name,"jet pt",60,0,300);
  map_sig["h_jets_eta"]               =     new TH1D("h_jets_eta_"          + name,"#eta distribution of the two jets",120,-3,3);
  map_sig["h_jets_phi"]               =     new TH1D("h_jets_phi_"          + name,"#phi distribution of the two jets",140,-3.5,3.5);
  map_sig["h_PileupJetIDMVA"]         =     new TH1D("h_pileupJetIDMVA_"    + name, "" ,100, -1.,1.);
  map_sig["h_bTag"]                   =     new TH1D("h_bTag_"              + name,"bTag discrimant",100,-1,3);
  map_sig["h_Njets"]                  =     new TH1D("h_Njets_"             + name,"number of jets",10,0,10);
  map_sig["h_Nbjets"]                 =     new TH1D("h_Nbjets_"            + name,"number of b jets",5,0,5);
  map_sig["h_lep_jet_dphi"]           =      new TH1D("h_lep_jet_dphi_"            + name,"dphi lepton jets", 50, 0., 5.);
  map_sig["h_awayjet_chargedem_frac"]         =      new TH1D("h_awayjet_chargedem_frac_"   + name,"charged em frac", 50, 0., 1.);

  map_sig["h_leading_jets_eta"]               =     new TH1D("h_leading_jets_eta_"          + name,"#eta distribution of the two leading_jets",120,-5,5);
  map_sig["h_second_jets_eta"]               =     new TH1D("h_second_jets_eta_"          + name,"#eta distribution of the two second_jets",120,-5,5);
  map_sig["h_third_jets_eta"]               =     new TH1D("h_third_jets_eta_"          + name,"#eta distribution of the two third_jets",120,-5,5);
  map_sig["h_fourth_jets_eta"]               =     new TH1D("h_fourth_jets_eta_"          + name,"#eta distribution of the two fourth_jets",120,-5,5);
  map_sig["h_rest_jets_eta"]               =     new TH1D("h_rest_jets_eta_"          + name,"#eta distribution of the two rest_jets",120,-5,5);
  map_sig["h_leadJetdR"]                =     new TH1D("h_leadJetdR_"         + name,"leading jet dR",50,0,5);
  map_sig["h_leadJetdPhi"]              =     new TH1D("h_leadJetdPhi_"       + name,"leading jet dPhi",50,-5,5);

}



void JetPlots::Fill(Double_t weight, std::vector<snu::KJet> jets){

  //// Jet mass variables
  dijetmass_tmp=dijetmass=9999.9;
  UInt_t m(0),n(0);



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
  if(jets.size()!=0){

    if(jets.size() > 1)Fill("h_leadJetdR",min_jj_Dr,weight);
    if(jets.size() > 1)Fill("h_leadJetdPhi",min_jj_DPhi,weight);
  }

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
  
  float ht=0.;
  int ijet(0);
  for(std::vector<snu::KJet>::iterator jit = jets.begin(); jit!=jets.end(); jit++,ijet++){
    ht+= jets[ijet].Pt();
    if(ijet==0)Fill("h_leadingJetPt", jets[0].Pt(),weight);
    if(ijet==1)Fill("h_secondJetPt", jets[1].Pt(),weight);
    Fill("h_jets_pt", jets[ijet].Pt(),weight);
    Fill("h_jets_eta",jets[ijet].Eta(),weight);
    if(ijet==0)     Fill("h_leading_jets_eta",jets[ijet].Eta(),weight);
    if(ijet==1)     Fill("h_second_jets_eta",jets[ijet].Eta(),weight);
    if(ijet==2)     Fill("h_third_jets_eta",jets[ijet].Eta(),weight);
    if(ijet==3)     Fill("h_fourth_jets_eta",jets[ijet].Eta(),weight);

    Fill("h_PileupJetIDMVA", jets[ijet].PileupJetIDMVA(),weight);
    Fill("h_jets_phi",jets[ijet].Phi(),weight);
    Fill("h_bTag",jets[ijet].CSVInclV2(),weight);
    if(jets.at(ijet).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) nbjet++;
  }
  
  Fill("h_HT", ht,weight);
  Fill("h_Nbjets",nbjet, weight);
  Fill("h_Njets",jets.size(), weight);
  

    
}


 void JetPlots::Write() {

   for(map<TString, TH1*>::iterator it = map_sig.begin(); it != map_sig.end(); it++){
     it->second->Write();
   }

 }



 JetPlots::JetPlots(): StdPlots(){
 }


 /**                                                                                                                                                                                                                                                                                                                                                                       
  * Copy constructor.                                                                                                                                                                                                                                                                                                                                                      
  */
 JetPlots::JetPlots(const JetPlots& sp): StdPlots(sp)
 {
   for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
     std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
     mit->second = mit2->second;
   }


 }


 JetPlots& JetPlots::operator= (const JetPlots& sp)
   {
     if (this != &sp) {

       for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
	 std::map<TString, TH1*>::iterator mit2 = sp.GetMap().find(mit->first);
	 mit->second = mit2->second;
       }

     }
     return *this;
   }

JetPlots::~JetPlots() {
  for(std::map<TString, TH1*>::iterator mit = map_sig.begin(); mit != map_sig.end() ; mit++){
    delete mit->second ;
  }
  
}
 

 void JetPlots::Fill(TString name, double value, double w){
   std::map<TString, TH1*>::iterator it = map_sig.find(name);
   if(it!= map_sig.end())   it->second->Fill(value, w);

   else cout << name << " not found in map_sig" << endl;
   return;
 }



