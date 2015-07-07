#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void EESigEff(){

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
  smasses.push_back("400");
  smasses.push_back("500");


  for(unsigned int i = 0 ; i < masses.size(); ++i){

    TString im = smasses.at(i);

    TFile * file1 = new TFile(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + im + "_nocut_5_3_14.root").Data());
    
    TString cut = im +"MassRegion";
    TString hist = (cut + "/h_Nelectrons_"+cut);
    
    TH1* hnsig =   (TH1F*)file1->Get(("CutFlow/_eventcutflow"));
    
    float nsig = float(hnsig->GetBinContent(2));
    
    
    TH1*  hpass = (TH1F*)file1->Get(hist);
    
    cout  << " \n ------- " << endl;
    cout  << " Mass = " << masses.at(i) << endl;
    cout << "mu eacceptance = " << hpass->Integral()/nsig << endl;
  }
}
