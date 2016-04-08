#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void EMuSigEff(){

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

    
    TFile * file1 = new TFile(("/home/jalmond/HeavyNeutrino/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNmue" + im + "_nocut_5_3_14.root").Data());
    TFile * file2 = new TFile(("/home/jalmond/HeavyNeutrino/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNemu" + im + "_nocut_5_3_14.root").Data());
   
    TString cut = "SS_highmass_" + im;
    if(i < 5) cut = "SS_lowmass_" + im; 

    TString hist = (cut + "/h_Nelectrons_"+cut);
    
    TH1* hnsig =   (TH1F*)file1->Get(("CutFlow/_eventcutflow"));

    TH1* hnsig2 =   (TH1F*)file2->Get(("CutFlow/_eventcutflow"));

    float nsig = float(hnsig->GetBinContent(2));
    float nsig2= float(hnsig2->GetBinContent(2));
    
    TH1*  hpass = (TH1F*)file1->Get(hist);
    TH1*  hpass2 = (TH1F*)file2->Get(hist);
    

    float nsignow = float(hnsig->GetBinContent(1) + hnsig2->GetBinContent(1));;
    float nev_pass =  ( (hpass->Integral() + hpass2->Integral())/ (nsig+ nsig2))  * nsignow;

    float err = sqrt(nev_pass) / nev_pass;



    cout  << " \n ------- " << endl;
    cout  << " Mass = " << masses.at(i) << endl;
    cout << "mu eacceptance = " << hpass->Integral()/nsig << endl;
    cout << "emu acceptance = " << hpass2->Integral()/nsig2 << endl;
    
    hpass->Add(hpass2,1.);
    err *= (100.*hpass->Integral()/ (nsig+nsig2));

    hpass->IntegralAndError(1, hpass->GetNbinsX()+1, err    , "");
    cout << "Average = " << 100.*hpass->Integral()/(nsig + nsig2) << endl;
    cout << "%err = " <<err<< endl;; 

  }
}
