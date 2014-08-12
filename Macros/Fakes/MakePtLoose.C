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
#include "THStack.h"
#include "TLegend.h"

void setTDRStyle();


void MakePtLoose(TString path) {

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  
  /// ALL MC
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  
  
  if(!fdata){
    cout << "No Data file" << endl;
    return;
  }
  if(!fmc){
    cout << "No MC file" << endl;
    return;
  }
  
  TCanvas* c1 = new TCanvas(("Plot"), "Plot", 800, 600);
  
  /// Make Ptelectron_SingleLooseElJet plot
  TH1F* h_data= (TH1F*)fdata->Get(("SingleLooseElJet/h_leadingElectronPt_SingleLooseElJet"));

  TH1F* h_mc= (TH1F*)fmc->Get(("SingleLooseElJet/h_leadingElectronPt_SingleLooseElJet"));
  
  TH1F* h_QCD = (TH1F*)(h_data->Clone("QCD"));
  h_QCD->Add(h_mc, -1.);
  
  if(!h_data) {
    cout << "No data hist" << endl;
    return;
  }
  if(!h_mc) {
    cout << "No mc hist" << endl;
    return;
  }

  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(1.2);
  h_data->GetXaxis()->SetRangeUser(0.,100.);
  
  h_mc->SetLineColor(kRed);
  h_mc->SetFillColor(kRed);
  h_mc->SetLineWidth(2.);
  h_mc->SetFillStyle(3004);

  h_QCD->SetLineColor(kBlue);
  h_QCD->SetFillColor(kBlue);
  h_QCD->SetLineWidth(2.);
  h_QCD->SetFillStyle(3007);
  
  
  h_data->Draw("p");
  
  THStack* stack = new THStack();
  stack->Add(h_mc);
  stack->Add(h_QCD);
  stack->Draw("histsame");
  

  TLegend* legend= new TLegend(0.6,0.6,0.8,0.8);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);

  legend->AddEntry(h_QCD, "Non-prompt", "f");
  legend->AddEntry(h_mc, "prompt", "f");
  legend->Draw("same");
  
  double FIGURE2_RATIO = 0.35;
  double SUBFIGURE_MARGIN = 0.15;
  c1->SetBottomMargin(FIGURE2_RATIO);
  TPad *p = new TPad( "p_test", "", 0, 0, 1, 1.0 - SUBFIGURE_MARGIN, 0, 0, 0);  // create new pad, fullsize to have equal font-sizes in both plots
  p->SetTopMargin(1-FIGURE2_RATIO);   // top-boundary (should be 1 - thePad->GetBottomMargin() )
  p->SetFillStyle(0);     // needs to be transparent
  p->Draw();
  p->cd();
  
  TH1F* h_ratio = (TH1F*)(h_QCD->Clone("ratio"));
  
  float tot_p=0.;
  float tot_np=0.;
  for(int i=1; i < h_ratio->GetNbinsX()+1; i++){
    tot_p = h_mc->GetBinContent(i);
    tot_np = h_QCD->GetBinContent(i)  ;
    if((tot_p)!=0) h_ratio->SetBinContent(i, 100.* tot_p / (tot_p+tot_np) );
    else h_ratio->SetBinContent(i,0);
  }
  h_ratio->SetFillColor(kWhite);
  h_ratio->SetFillStyle(0);
  h_ratio->GetYaxis()->SetNdivisions(10204);
  h_ratio->GetYaxis()->SetRangeUser(0.0,100.0);
  h_ratio->GetXaxis()->SetRangeUser(0.0,100.0);
  h_ratio->GetYaxis()->SetTitle("%Non-Prompt/Bin");
  h_ratio->GetXaxis()->SetTitle("el P_{T} [GeV]");
  
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetLineStyle(2.);
  h_ratio->SetLineWidth(4);
  
  h_ratio->Draw("hist");
  
  c1->SaveAs(("/home/jalmond/WebPlots/Fakes/PT_loosesample.pdf"));
  

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
  tdrStyle->SetPadBottomMargin(0.12);
  tdrStyle->SetPadLeftMargin(0.12);
  tdrStyle->SetPadRightMargin(0.1);

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
