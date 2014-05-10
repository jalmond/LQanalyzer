#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"


void FakeRatePlots(TString path) {

  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  gStyle->SetPaintTextFormat("4.2f");
  
  vector<TString> plotname;
  plotname.push_back("20_pt");
  plotname.push_back("40_pt");
  plotname.push_back("60_pt");
  plotname.push_back("20_eta");
  plotname.push_back("40_eta");
  plotname.push_back("60_eta");
  plotname.push_back("20_njets");
  plotname.push_back("40_njets");
  plotname.push_back("60_njets");

  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    
    TH1F* h_pt_num= (TH1F*)fdata->Get(("TightEl"+ *it ).Data());
    TH1F* h_pt_denom= (TH1F*)fdata->Get(("LooseEl" +*it).Data());
    
    h_pt_num->Divide(h_pt_denom);

    h_pt_num->SetMarkerStyle(20);
    h_pt_num->SetMarkerColor(kRed);
    h_pt_num->SetLineColor(kRed);

    TCanvas* c1 = new TCanvas(("Plot"), "Plot", 800, 600);

    h_pt_num->GetXaxis()->SetTitle("El p_{T} [GeV]");
    h_pt_num->GetYaxis()->SetTitle("#epsilon_{T/L}");
    
    h_pt_num->GetYaxis()->SetRangeUser(0.,1.);
    //h_pt_num->GetXaxis()->SetRangeUser(20.,60.);
    
    h_pt_num->Draw("p");

    c1->SaveAs(("/home/jalmond/WebPlots/Fakes/FakeRate_" +  *it + ".pdf"));
  }

}
