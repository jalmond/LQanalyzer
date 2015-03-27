#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void EMuSigEff(){

  TFile * file1 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNmue400_nocut_5_3_14.root");
  TFile * file2 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNemu400_nocut_5_3_14.root");
  
  TString cut = "SS_highmass_400";
  TString hist = (cut + "/h_Nelectrons_"+cut);
  cout << file1 << " " << file2 << endl;
  TH1* hnsig =   (TH1F*)file1->Get(("CutFlow/_eventcutflow"));
  TH1* hnsig2 =   (TH1F*)file2->Get(("CutFlow/_eventcutflow"));
  
  cout << hnsig << " " << hnsig2 << endl;
  float nsig = float(hnsig->GetBinContent(2));
  float nsig2= float(hnsig2->GetBinContent(2));
  
  
  TH1*  hpass = (TH1F*)file1->Get(hist);
  TH1*  hpass2 = (TH1F*)file2->Get(hist);
  
  cout << hpass->Integral() << " " << nsig << endl;
  cout << "mu eacceptance = " << hpass->Integral()/nsig << endl;
  cout << "emu acceptance = " << hpass2->Integral()/nsig2 << endl;
}
