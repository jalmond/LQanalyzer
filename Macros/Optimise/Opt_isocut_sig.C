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


void Opt_isocut(){
 
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  

  TCanvas* c1 = new TCanvas("Plot", "Plot", 800, 600);
			    
  TLegend *legend = new TLegend(.6, 0.7, .7, 0.9);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);

  
  TFile * sig60 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKHNee60_nocut_5_3_14.root");
  TFile * sig100 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKHNee100_nocut_5_3_14.root");
  TFile * sig200 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKHNee200_nocut_5_3_14.root");
  TFile * sig500 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronOpt/HNElectronOptimisation_SKHNee500_nocut_5_3_14.root");


  TH1F* h_sig60cutflow= (TH1F*)sig60->Get(("ISOcutflow"));
  TH1F* h_sig100cutflow= (TH1F*)sig100->Get(("ISOcutflow"));
  TH1F* h_sig200cutflow= (TH1F*)sig200->Get(("ISOcutflow"));
  TH1F* h_sig500cutflow= (TH1F*)sig500->Get(("ISOcutflow"));
 
  TH1F* h_sig60ref= (TH1F*)sig60->Get(("ISOREF"));
  TH1F* h_sig100ref= (TH1F*)sig100->Get(("ISOREF"));
  TH1F* h_sig200ref= (TH1F*)sig200->Get(("ISOREF"));
  TH1F* h_sig500ref= (TH1F*)sig500->Get(("ISOREF"));
  
  
  
  TH1F* h_sig60_isoopt = new TH1F(("isocut_opt_HN_sig60"),("isocut_opt_HN_sig60"), 16,0.,16.);
  h_sig60_isoopt->GetXaxis()->SetBinLabel(1,"dr03_150");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(2,"dr03_125");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(3,"dr03_100");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(4,"dr03_090");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(5,"dr03_080");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(6,"dr03_070");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(7,"dr03_060");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(8,"dr03_050");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(9,"dr03_150");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(10,"dr04_125");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(11,"dr04_100");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(12,"dr04_090");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(13,"dr04_080");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(14,"dr04_070");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(15,"dr04_060");
  h_sig60_isoopt->GetXaxis()->SetBinLabel(16,"dr04_050");


  TH1F* h_sig100_isoopt = new TH1F(("isocut_opt_HN_sig100"),("isocut_opt_HN_sig100"), 16,0.,16.);
  TH1F* h_sig200_isoopt = new TH1F(("isocut_opt_HN_sig200"),("isocut_opt_HN_sig200"), 16,0.,16.);
  TH1F* h_sig500_isoopt = new TH1F(("isocut_opt_HN_sig500"),("isocut_opt_HN_sig500"), 16,0.,16.);

  
  for(int i= 1; i < h_sig60cutflow->GetNbinsX()+1;i++){
    
    float tot_bkg = h_sig60cutflow->GetBinContent(i)/h_sig60ref->GetBinContent(1);
    float err_bkg =  h_sig60cutflow->GetBinError(i);
    h_sig60_isoopt->SetBinContent(i,tot_bkg);
    h_sig60_isoopt->SetBinError(i,err_bkg);
  } 
  
  for(int i= 1; i < h_sig100cutflow->GetNbinsX()+1;i++){

    float tot_bkg = h_sig100cutflow->GetBinContent(i)/h_sig100ref->GetBinContent(1);
    float err_bkg =  h_sig100cutflow->GetBinError(i);
    h_sig100_isoopt->SetBinContent(i,tot_bkg);
    h_sig100_isoopt->SetBinError(i,err_bkg);
  }


  for(int i= 1; i < h_sig200cutflow->GetNbinsX()+1;i++){

    float tot_bkg = h_sig200cutflow->GetBinContent(i)/h_sig200ref->GetBinContent(1);
    float err_bkg =  h_sig200cutflow->GetBinError(i);
    h_sig200_isoopt->SetBinContent(i,tot_bkg);
    h_sig200_isoopt->SetBinError(i,err_bkg);
  }


  for(int i= 1; i < h_sig500cutflow->GetNbinsX()+1;i++){

    float tot_bkg = h_sig500cutflow->GetBinContent(i)/h_sig500ref->GetBinContent(1);
    float err_bkg =  h_sig500cutflow->GetBinError(i);
    h_sig500_isoopt->SetBinContent(i,tot_bkg);
    h_sig500_isoopt->SetBinError(i,err_bkg);
  }

  
  
  h_sig60_isoopt->GetYaxis()->SetTitle("Cut Efficiency(%)"); 
  h_sig60_isoopt->GetXaxis()->SetTitle("PFiso/pt cut");
  
  h_sig60_isoopt->SetLineWidth(3.);
  h_sig100_isoopt->SetLineWidth(3.);
  h_sig200_isoopt->SetLineWidth(3.);
  h_sig500_isoopt->SetLineWidth(3.);
  h_sig60_isoopt->SetLineColor(kRed);
  h_sig60_isoopt->SetMarkerColor(kRed);
  
  h_sig100_isoopt->SetLineColor(kGreen );
  h_sig100_isoopt->SetMarkerColor(kGreen);
  
  h_sig200_isoopt->SetLineColor(kBlue);
  h_sig200_isoopt->SetMarkerColor(kBlue);
  
  h_sig500_isoopt->SetLineColor(kCyan);
  h_sig500_isoopt->SetMarkerColor(kCyan);

  h_sig60_isoopt->GetYaxis()->SetRangeUser(0.0, 1.5);
  
  h_sig60_isoopt->GetYaxis()->SetTitleSize(0.05);
  h_sig60_isoopt->GetYaxis()->SetTitleOffset(1.5);
  h_sig60_isoopt->GetYaxis()->SetLabelSize(0.04);
  
  h_sig60_isoopt->GetXaxis()->SetTitleSize(0.05);
  h_sig60_isoopt->GetXaxis()->SetLabelSize(0.04);
  
  
  h_sig60_isoopt->Draw("hist");
  h_sig100_isoopt->Draw("histsame");
  h_sig200_isoopt->Draw("histsame");
  h_sig500_isoopt->Draw("histsame");

  
  legend->AddEntry(h_sig60_isoopt,"m_{N} = 60 GeV", "l");
  legend->AddEntry(h_sig100_isoopt,"m_{N} = 100 GeV", "l");
  legend->AddEntry(h_sig200_isoopt,"m_{N} = 200 GeV", "l");
  legend->AddEntry(h_sig500_isoopt,"m_{N} = 500 GeV", "l");
  legend->Draw("same");
  c1->SaveAs(("/home/jalmond/WebPlots/Opt/isooptimise_sig.pdf"));
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




