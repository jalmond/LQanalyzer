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

/// Style
#include "Macro.h"


void FakeRatePlots_ewksub(TString path) {
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);


  
  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  gStyle->SetPaintTextFormat("4.2f");
  
  vector<TString> plotname;
  plotname.push_back("_ptbarrel");
  plotname.push_back("_ptendcap");
  //plotname.push_back("_eta");
  //plotname.push_back("_pt_eta2");
  //plotname.push_back("_pt_eta3");
  //plotname.push_back("_pt_eta4");
 
  
  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    
    TCanvas* c1 = new TCanvas(("Plot"), "Plot", 800, 600);
    
    map<TString, TH1*> histmap;
    vector<TString> hist_ptcut;
    hist_ptcut.push_back("20");
    hist_ptcut.push_back("40");
    hist_ptcut.push_back("60");
    
    for(vector<TString>::iterator it2 = hist_ptcut.begin(); it2!=hist_ptcut.end(); ++it2){
      int rebin=1;
      
      TH1F* h_pt_num= (TH1F*)fdata->Get(("TightEl"+ *it2+ *it ).Data());
      TH1F* h_pt_denom= (TH1F*)fdata->Get(("LooseEl"+ *it2+*it).Data());
      
      TH1F* h_mcpt_num= (TH1F*)fmc->Get(("TightEl"+*it2+ *it ).Data());
      TH1F* h_mcpt_denom= (TH1F*)fmc->Get(("LooseEl"+*it2 +*it).Data());

      h_pt_num->Rebin(rebin);
      h_pt_denom->Rebin(rebin);
      h_mcpt_num->Rebin(rebin);
      h_mcpt_denom->Rebin(rebin);
      
      h_pt_num->Add(h_mcpt_num, -1);
      h_pt_denom->Add(h_mcpt_denom, -1);
      h_pt_num->Divide(h_pt_denom);
            
      h_pt_num->SetMarkerStyle(20);
      if(it2->Contains("20")){
	h_pt_num->SetMarkerColor(kRed);
	h_pt_num->SetLineColor(kRed);
	h_pt_num->SetLineStyle(20);
      }
      if(it2->Contains("40")){
        h_pt_num->SetMarkerColor(kBlue);
        h_pt_num->SetLineColor(kBlue);
	h_pt_num->SetLineStyle(21);

      }
      if(it2->Contains("60")){
        h_pt_num->SetMarkerColor(kCyan);
        h_pt_num->SetLineColor(kCyan);
	h_pt_num->SetLineStyle(22);

      }
      h_pt_num->SetLineWidth(0.3);
     
      h_pt_num->GetXaxis()->SetTitle("El p_{T} [GeV]");
      h_pt_num->GetYaxis()->SetTitle("#epsilon_{T/L}");
      
      h_pt_num->GetYaxis()->SetRangeUser(0.,.5);
      h_pt_num->GetXaxis()->SetRangeUser(15,59.);
      
      histmap[*it2] = h_pt_num;

      cout << "Hist : " << *it2 << endl;
      for(unsigned int ibin = 1; ibin < h_pt_num->GetNbinsX()+1; ibin++){
	cout << h_pt_num->GetBinContent(ibin) << " +/- "  << h_pt_num->GetBinError(ibin) << endl; 
      }
      
    }
    
      
    
    histmap.find("20")->second->Draw("p");
    histmap.find("40")->second->Draw("psame");
    histmap.find("60")->second->Draw("psame");
    
    histmap.find("40")->second->SetMarkerStyle(22);
    histmap.find("60")->second->SetMarkerStyle(21);
  
    TLegend* legend= new TLegend(0.2,0.7,0.4,0.9);
    legend->SetFillColor(10);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.04);
    
    legend->AddEntry(histmap.find("20")->second, "away jet pt >" +histmap.find("20")->first+ " GeV", "p");
    legend->AddEntry(histmap.find("40")->second, "away jet pt >" +histmap.find("40")->first+ " GeV", "p");
    legend->AddEntry(histmap.find("60")->second, "away jet pt >" +histmap.find("60")->first+ " GeV", "p");
    legend->Draw("same");



    
    
    c1->SaveAs(("/home/jalmond/WebPlots/Fakes/FakeRateEWKSub_jetcuts_" +  *it + ".pdf"));
  }
  
}
