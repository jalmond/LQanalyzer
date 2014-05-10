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
#include "TLegend.h"


void FakeRatePlots_ewksub(TString path) {

  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_MC_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  gStyle->SetPaintTextFormat("4.2f");
  
  vector<TString> plotname;
  //plotname.push_back("40_pt");
  plotname.push_back("40_eta");
  
  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    
    int rebin=1;

    if(it->Contains("eta")) rebin=5;
    TH1F* h_pt_num= (TH1F*)fdata->Get(("TightEl"+ *it ).Data());
    TH1F* h_pt_denom= (TH1F*)fdata->Get(("LooseEl" +*it).Data());
    
    TH1F* h_mcpt_num= (TH1F*)fmc->Get(("TightEl"+ *it ).Data());
    TH1F* h_mcpt_denom= (TH1F*)fmc->Get(("LooseEl" +*it).Data());

    h_pt_num->Rebin(rebin);
    h_pt_denom->Rebin(rebin);
    h_mcpt_num->Rebin(rebin);
    h_mcpt_denom->Rebin(rebin);

    TH1F* h_pt_num_clone = (TH1F*)h_pt_num->Clone("");
    h_pt_num_clone->Add(h_mcpt_num,-1);

    TH1F* h_pt_denom_clone = (TH1F*)h_pt_denom->Clone("");
    h_pt_denom_clone->Add(h_mcpt_denom,-1);
    
    
    cout << "Number of events in numerator (data) = " << h_pt_num->Integral() << endl;
    cout << "Number of events in denominator (data) = " << h_pt_denom->Integral() << endl;
    
    cout << "Number of events in numerator (mc) = " << h_mcpt_num->Integral() << endl;
    cout << "Number of events in denominator (mc) = " << h_mcpt_denom->Integral() << endl;
    
    cout << "Number of events in numerator (data-mc) = " << h_pt_num_clone->Integral() << endl;
    cout << "Number of events in denominator (data-mc) = " << h_pt_denom_clone->Integral() << endl;

    h_pt_num->Divide(h_pt_denom);
    h_pt_num_clone->Divide(h_pt_denom_clone);

    h_pt_num->SetMarkerStyle(20);
    h_pt_num->SetMarkerColor(kRed);
    h_pt_num->SetLineColor(kRed);
    
    h_pt_num_clone->SetMarkerStyle(20);
    h_pt_num_clone->SetMarkerColor(kBlue);
    h_pt_num_clone->SetLineColor(kBlue);

    TCanvas* c1 = new TCanvas(("Plot"), "Plot", 800, 600);
    
    h_pt_num->GetXaxis()->SetTitle("El p_{T} [GeV]");
    h_pt_num->GetYaxis()->SetTitle("#epsilon_{T/L}");
    
    h_pt_num->GetYaxis()->SetRangeUser(0.,1.);
    //h_pt_num->GetXaxis()->SetRangeUser(20.,60.);
    
    h_pt_num->Draw("p");
    h_pt_num_clone->Draw("psame");
    
    TLegend* legend= new TLegend(0.2,0.5,0.4,0.7);
    legend->SetFillColor(10);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.04);

    legend->AddEntry(h_pt_num, "uncorrected", "lp");
    legend->AddEntry(h_pt_num_clone, "ewk corrected", "lp");
		     
    legend->Draw("same");

    c1->SaveAs(("/home/jalmond/WebPlots/Fakes/FakeRateEWKSub_" +  *it + ".pdf"));
  }

}
