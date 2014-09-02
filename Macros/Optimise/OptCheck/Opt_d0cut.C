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
#include "TLatex.h"

#include "Macro.h"

void Opt_d0cut(){
  
  
  
  setTDRStyle();
  gStyle->SetPalette(1);
  
  std::vector<TString> masses;
  masses.push_back("40");
  /*masses.push_back("50");
  masses.push_back("60");
  masses.push_back("70");
  masses.push_back("80");
  masses.push_back("90");
  masses.push_back("100");
  masses.push_back("125");
  masses.push_back("150");
  masses.push_back("175");
  masses.push_back("200");
  masses.push_back("225");
  masses.push_back("250");
  masses.push_back("275");
  masses.push_back("300");
  masses.push_back("325");
  masses.push_back("350");
  masses.push_back("375");
  masses.push_back("400");
  masses.push_back("500");
  masses.push_back("600");
  masses.push_back("700");*/
  
  TFile * fnp = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKnonprompt_dilep_5_3_14.root");
  TFile * fcf = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_cf_dilep_5_3_14.root");
  TFile * fmc = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_mc_dilep_5_3_14.root");

  TH1F* h_npcutflow= (TH1F*)fnp->Get(("d0cutflow"));
  TH1F* h_cfcutflow= (TH1F*)fcf->Get(("d0cutflow"));
  TH1F* h_mccutflow= (TH1F*)fmc->Get(("d0cutflow"));

  for(unsigned int im=0; im < masses.size(); im++){
    TFile * fsig = new TFile(("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKHNee" + masses.at(im) + "_nocut_5_3_14.root").Data());
    cout << "\n ----------------" << endl;
    cout <<  "New mass : " << masses.at(im) << endl;
    TH1F* h_cutflow= (TH1F*)fsig->Get(("d0cutflow"));

    for(int i=0; i < h_cutflow->GetNbinsX()+1; i++){
      cout << h_cutflow->GetBinContent(i) << endl;
    }

    TH1F* h_mass_d0opt = new TH1F(("d0cut_opt_HN"+ masses.at(im)).Data(),("d0cut_opt_HN"+ masses.at(im)).Data(), 6,0.,6.);
    h_mass_d0opt->GetXaxis()->SetBinLabel(1,"0.005");
    h_mass_d0opt->GetXaxis()->SetBinLabel(2,"0.01");
    h_mass_d0opt->GetXaxis()->SetBinLabel(3,"0.015");
    h_mass_d0opt->GetXaxis()->SetBinLabel(4,"0.02");
    h_mass_d0opt->GetXaxis()->SetBinLabel(5,"0.025");
    h_mass_d0opt->GetXaxis()->SetBinLabel(6,"0.03");
    
    for(int i= 0; i < 6;i++){
      float sig_eff = h_cutflow->GetBinContent(i+2)/ h_cutflow->GetBinContent(i+1);
      float tot_bkg = h_npcutflow->GetBinContent(i+2) + h_cfcutflow->GetBinContent(i+2)+ h_mccutflow->GetBinContent(i+2);
      float bkgtmp = tot_bkg + (0.28*h_npcutflow->GetBinContent(i+2))*(0.28*h_npcutflow->GetBinContent(i+2));
      float denom= 1. + sqrt(bkgtmp);
      
      float punzi = sig_eff/denom;
      h_mass_d0opt->SetBinContent(i+1,punzi);
    } 

    h_mass_d0opt->GetYaxis()->SetTitle("Punzi"); 
    h_mass_d0opt->GetXaxis()->SetTitle("d_{xy} cut");
    h_mass_d0opt->SetLineWidth(2.);
    h_mass_d0opt->SetLineColor(kRed);
    TCanvas* c1 = new TCanvas((("Plot")+ masses.at(im)).Data(), "Plot", 800, 600);

    h_mass_d0opt->Draw("hist");
    TLatex label;
    label.SetTextSize(0.04);
    label.SetTextColor(2);
    label.SetTextFont(42);
    label.SetNDC();
    label.SetTextColor(1);
    label.DrawLatex(0.7,0.8,("m_{N}=" +  masses.at(im)+ " GeV").Data());
    label.SetTextSize(0.045);
    
    c1->SaveAs(("/home/jalmond/WebPlots/Opt/d0optimise_" +   masses.at(im) + ".pdf"));
    
  }
}
