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

//#include "Macro.h"
void setTDRStyle();


void Opt_d0cut(){
 
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  

  TCanvas* c1 = new TCanvas("Plot", "Plot", 800, 600);
			    
  TLegend *legend = new TLegend(.6, 0.3, .7, 0.5);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);

  
  TFile * fcf = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_cf_dilep_5_3_14.root");
  TFile * fmc = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_mc_dilep_5_3_14.root");
  TFile * fnp = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKnonprompt_dilep_5_3_14.root");
  TH1F* h_cfcutflow= (TH1F*)fcf->Get(("d0cutflow"));
  TH1F* h_mccutflow= (TH1F*)fmc->Get(("d0cutflow"));
  TH1F* h_npcutflow= (TH1F*)fnp->Get(("d0cutflow"));
  
  //h_mccutflow->Add(h_cfcutflow,1.);
  
  TH1F* h_mc_d0opt = new TH1F(("d0cut_opt_HN_mc"),("d0cut_opt_HN_mc"), 6,0.,6.);
  h_mc_d0opt->GetXaxis()->SetBinLabel(1,"0.005");
  h_mc_d0opt->GetXaxis()->SetBinLabel(2,"0.01");
  h_mc_d0opt->GetXaxis()->SetBinLabel(3,"0.015");
  h_mc_d0opt->GetXaxis()->SetBinLabel(4,"0.02");
  h_mc_d0opt->GetXaxis()->SetBinLabel(5,"0.025");
  h_mc_d0opt->GetXaxis()->SetBinLabel(6,"0.03");
  
  for(int i= 0; i < 6;i++){
    
    float tot_bkg = h_mccutflow->GetBinContent(i+2);
    float err_bkg = h_mccutflow->GetBinError(i+2);
    h_mc_d0opt->SetBinContent(i+1,tot_bkg);
    h_mc_d0opt->SetBinError(i+1,err_bkg);
  } 

  TH1F* h_cf_d0opt = new TH1F(("d0cut_opt_HN_cf"),("d0cut_opt_HN_cf"), 6,0.,6.);
  h_cf_d0opt->GetXaxis()->SetBinLabel(1,"0.005");
  h_cf_d0opt->GetXaxis()->SetBinLabel(2,"0.01");
  h_cf_d0opt->GetXaxis()->SetBinLabel(3,"0.015");
  h_cf_d0opt->GetXaxis()->SetBinLabel(4,"0.02");
  h_cf_d0opt->GetXaxis()->SetBinLabel(5,"0.025");
  h_cf_d0opt->GetXaxis()->SetBinLabel(6,"0.03");

  for(int i= 0; i < 6;i++){

    float tot_bkg = h_cfcutflow->GetBinContent(i+2);
    float err_bkg = h_cfcutflow->GetBinError(i+2);
    h_cf_d0opt->SetBinContent(i+1,tot_bkg);
    h_cf_d0opt->SetBinError(i+1,err_bkg);
  }
  
  TH1F* h_np_d0opt = new TH1F(("d0cut_opt_HN_np"),("d0cut_opt_HN_np"), 6,0.,6.);
  h_np_d0opt->GetXaxis()->SetBinLabel(1,"0.005");
  h_np_d0opt->GetXaxis()->SetBinLabel(2,"0.01");
  h_np_d0opt->GetXaxis()->SetBinLabel(3,"0.015");
  h_np_d0opt->GetXaxis()->SetBinLabel(4,"0.02");
  h_np_d0opt->GetXaxis()->SetBinLabel(5,"0.025");
  h_np_d0opt->GetXaxis()->SetBinLabel(6,"0.03");

  for(int i= 0; i < 6;i++){

    float tot_bkg = h_npcutflow->GetBinContent(i+2);
    float err_bkg = h_npcutflow->GetBinError(i+2);
    h_np_d0opt->SetBinContent(i+1,tot_bkg);
    h_np_d0opt->SetBinError(i+1,err_bkg);
  }
  
  
  
  h_mc_d0opt->GetYaxis()->SetTitle("Events"); 
  h_mc_d0opt->GetXaxis()->SetTitle("d_{xy} cut");
  
  h_mc_d0opt->SetLineWidth(3.);
  h_mc_d0opt->SetLineColor(kRed);
  h_mc_d0opt->SetMarkerColor(kRed);
  
  h_cf_d0opt->SetLineColor(kGreen-4 );
  h_cf_d0opt->SetMarkerColor(kGreen-4);

  h_np_d0opt->SetLineColor(kBlue);
  h_np_d0opt->SetMarkerColor(kBlue);
  
  h_mc_d0opt->GetYaxis()->SetRangeUser(0., 100.);
  
  /*h_mass_d0opt->GetYaxis()->SetTitleSize(0.05);
    h_mass_d0opt->GetYaxis()->SetTitleOffset(1.5);
    h_mass_d0opt->GetYaxis()->SetLabelSize(0.04);
    
    h_mass_d0opt->GetXaxis()->SetTitleSize(0.05);
    h_mass_d0opt->GetXaxis()->SetLabelSize(0.04);
  */
  
  h_mc_d0opt->Draw("pEX0");
  h_cf_d0opt->Draw("pEX0same");
  h_np_d0opt->Draw("pEX0same");
  
  legend->AddEntry(h_mc_d0opt,("MC (truth matched)"), "lp");
  legend->AddEntry(h_cf_d0opt,("CF (truth matched)"), "lp");
  legend->AddEntry(h_np_d0opt,("NP (data driven)"), "lp");
  legend->Draw("same");
  c1->SaveAs(("/home/jalmond/WebPlots/Opt/d0optimise_mcbkg.pdf"));
}



void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);


  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);


  // For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
  tdrStyle->SetEndErrorSize(2);
  //  tdrStyle->SetErrorMarker(20);
  //  tdrStyle->SetErrorX(0.);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);

  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

  // For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);

  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.4);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset



  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.4);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();

}




