#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void EMuSigEff_split(){

  vector <int> masses;
  masses.push_back(40);
  masses.push_back(50);
  masses.push_back(60);
  masses.push_back(70);
  masses.push_back(80);
  masses.push_back(90);
  masses.push_back(100);
  masses.push_back(125);
  masses.push_back(150);
  masses.push_back(175);
  masses.push_back(200);
  masses.push_back(250);
  masses.push_back(300);
  masses.push_back(350);
  masses.push_back(400);
  masses.push_back(500);

  vector <TString> smasses;
  smasses.push_back("40");
  smasses.push_back("50");
  smasses.push_back("60");
  smasses.push_back("70");
  smasses.push_back("80");
  smasses.push_back("90");
  smasses.push_back("100");
  smasses.push_back("125");
  smasses.push_back("150");
  smasses.push_back("175");
  smasses.push_back("200");
  smasses.push_back("250");
  smasses.push_back("300");
  smasses.push_back("350");
  smasses.push_back("400");
  smasses.push_back("500");


  for(unsigned int i = 0 ; i < masses.size(); ++i){

    TString im = smasses.at(i);

    TFile * file1 = new TFile(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNmue" + im + "_nocut_5_3_14.root").Data());
    TFile * file2 = new TFile(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNemu" + im + "_nocut_5_3_14.root").Data());
    

    TString cut = "SS_highmass_" + im;
    //cut = "SS_highmass";
    if(i < 5) cut = "SS_lowmass_" + im; 
    //if(i < 5) cut = "SS_lowmass_80_2";

    TString hist = (cut + "/h_Nelectrons_"+cut);
   
    TString histpt = ("eff_emu_pteta");
    TString histiso = ("eff_emu_iso");
    TString histdijet = ("eff_emu_dijet");
    TString histdilep = ("eff_emu_dilep");
    TString histpresel = ("eff_emu_presel");

    
    TH1* hnsig =   (TH1F*)file1->Get(("eff_emu_pteta_ref"));
    TH1* hnsig_tot =   (TH1F*)file1->Get(("CutFlow/_eventcutflow"));
    
    TH1* hnsig2 =   (TH1F*)file2->Get(("eff_emu_pteta_ref"));
    TH1* hnsig2_tot =   (TH1F*)file2->Get(("CutFlow/_eventcutflow"));
    
    float nsig_tot = float(hnsig_tot->GetBinContent(2));
    float nsig2_tot= float(hnsig2_tot->GetBinContent(2));
    
    float w = hnsig_tot->GetBinContent(2) / hnsig_tot->GetBinContent(1);

    float nsig = float(hnsig->Integral());
    float nsig2= float(hnsig2->Integral());    
    
    TH1*  hpass = (TH1F*)file1->Get(hist);
    TH1*  hpass2 = (TH1F*)file2->Get(hist);
    
    TH1*  hpass_pteta = (TH1F*)file1->Get(histpt);
    TH1*  hpass_iso = (TH1F*)file1->Get(histiso);
    TH1*  hpass_dilep = (TH1F*)file1->Get(histdilep);
    TH1*  hpass_dijet = (TH1F*)file1->Get(histdijet);
    TH1*  hpass_presel = (TH1F*)file1->Get(histpresel);

    TH1*  hpass_pteta2 = (TH1F*)file2->Get(histpt);
    TH1*  hpass_iso2 = (TH1F*)file2->Get(histiso);
    TH1*  hpass_dilep2 = (TH1F*)file2->Get(histdilep);
    TH1*  hpass_dijet2 = (TH1F*)file2->Get(histdijet);
    TH1*  hpass_presel2 = (TH1F*)file2->Get(histpresel);

    nsig2 = nsig2/100.;
    nsig = nsig/100.;


    nsig_tot = nsig_tot/100.;
    nsig2_tot = nsig2_tot/100.;
    
    cout  << " \n ------- " << endl;
    cout  << " Mass = " << masses.at(i) << endl;

    cout <<  hpass->Integral() << " " << nsig_tot << endl;
    cout << "mu e acceptance = " << (hpass->Integral()/nsig_tot +  hpass2->Integral()/nsig2_tot)/2.  << " +/- " << w*sqrt(  hpass->Integral()/w) /nsig_tot  << endl;
    
    cout << hpass_pteta->Integral() << " " << nsig << " " << hpass_pteta2->Integral() << " " << nsig2 << endl;
    cout << "mu e acceptance pt= " <<  (hpass_pteta->Integral()/nsig + hpass_pteta2->Integral()/nsig2)/2.  << " +/- " <<  sqrt(hpass_pteta->Integral())/ nsig << endl;
    cout << "mu e acceptance pt= " <<  (hpass_pteta->Integral()/nsig ) << " " <<  hpass_pteta2->Integral()/nsig2 << endl;
    cout << "mu e acceptance iso= " << (hpass_iso->Integral()/nsig + hpass_iso2->Integral()/nsig2)/2. << " +/- " <<  sqrt(hpass_iso->Integral())/nsig << endl;
    cout << "mu e acceptance 2lep= " <<  (hpass_dilep->Integral()/nsig + hpass_dilep2->Integral()/nsig2)/2.  << " +/- " <<  sqrt(hpass_dilep->Integral())/ nsig << endl;
    cout << "mu e acceptance 2jet= " << hpass_dijet->Integral()/nsig << " +/- " <<  sqrt(hpass_dijet->Integral())/ nsig<< endl;
    cout << "mu e acceptance full= " << hpass_presel->Integral()/nsig << " +/- " << sqrt(hpass_presel->Integral())/nsig << endl;
    cout << "N events = " << nsig*100. + nsig2*100 << endl;
  }
}
