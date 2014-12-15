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

#include "TString.h"

void setTDRStyle();
void SetHist(TH1F* hist, TH1F* hist2,  TString xtit, TString ytit, double xmin, double xmax);
void CheckHist(TH1* hist);
void SetApp(TH1* hist,Color_t col, Style_t sty, Width_t w);
void Rebin(TH1* h1, TH1* h2, int rb);
bool Norm(TH1* h, TH1* h2);
void GetFRFromSingleEl(){
  
  TString pathmc= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronSingleEl/HNDiElectron_mc_5_3_14.root";
  TString pathdata= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronSingleEl/HNDiElectron_data_5_3_14.root";
  TString pathnp= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronSingleEl/NP/HNDiElectron_SKnonprompt_5_3_14.root";

  TFile * fmc = new TFile(pathmc.Data());
  TFile * fdata = new TFile(pathdata.Data());
  TFile * fnp = new TFile(pathnp.Data());
  if(!fmc) return;
  /// Set Plotting style                                                                                                                              
  setTDRStyle();
  gStyle->SetPalette(1);


  TH1F* h_data_hist =  dynamic_cast<TH1F*>(fdata->Get("SingleEl_CR/h_leadingElectronPt_SingleEl_CR"));
  TH1F* h_mc = dynamic_cast<TH1F*>(fmc->Get("SingleEl_CR/h_leadingElectronPt_SingleEl_CR"));
  
  CheckHist(h_data_hist);
  CheckHist(h_mc);

  TCanvas* c1 = new TCanvas("GetFRFromSingleEl", "Plot", 800, 600);

  SetApp(h_data_hist, kRed, 1,3);
  SetApp(h_mc, kBlue, 1,3);

  Rebin(h_data_hist, h_mc, 1);

  SetHist(h_data_hist,  h_mc, "p_{T} [GeV]", "Events",  0., 100.);

  h_data_hist->Draw("hist");
  
  
  TH1* h_np =  dynamic_cast<TH1F*>(h_data_hist->Clone("clone"));
  
  for(int ibin=1; ibin < h_np->GetNbinsX()+1; ibin++){
    float npvalue = h_data_hist->GetBinContent(ibin) - h_mc->GetBinContent(ibin);
    h_np->SetBinContent(ibin, npvalue);
  }
  
  h_mc->Add(h_np,1.);
  h_mc->Draw("histsame");
  
  TLegend* legend= new TLegend(0.5,0.8,0.7,0.9);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);
  
  legend->AddEntry(h_data_hist,"data", "l");
  legend->AddEntry(h_mc,"bkg","l");
  legend->Draw("same");
  
  TH1F* h_loose = dynamic_cast<TH1F*>(fnp->Get("SingleElLoose_CR/h_leadingElectronPt_SingleElLoose_CR"));
  TH1F* h_tight = dynamic_cast<TH1F*>(fnp->Get("SingleElTight_CR/h_leadingElectronPt_SingleElTight_CR"));
  
  vector<double> r;
  r.push_back(0.80);
  r.push_back(0.81);
  r.push_back(0.855);
  r.push_back(0.878);
  r.push_back(0.90);
  r.push_back(0.92);
  r.push_back(0.94);
  r.push_back(0.95);
  r.push_back(0.96);
  r.push_back(0.97);
  r.push_back(0.99);
  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);
r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);
 r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);  r.push_back(0.99);

  for(int ibin=1; ibin < h_np->GetNbinsX()+1; ibin++){
    cout << "Number of fakes = " << h_np->GetBinContent(ibin) << " while number of loose = " << h_loose->GetBinContent(ibin) << " number pf tight = " <<  h_tight->GetBinContent(ibin) << endl;
    if(h_np->GetBinContent(ibin) > 0) {
      double fratio = h_np->GetBinContent(ibin) / h_loose->GetBinContent(ibin); 
      double fr = fratio/ (1.+fratio);
      cout << "(lowest bound on) Fake rate = " << fr << endl;
      
      double alpha = 1./(r.at(ibin-1) - fr);
      double ftight = h_tight->GetBinContent(ibin) *  alpha * fr * (1- r.at(ibin-1));
      
      fratio = (h_np->GetBinContent(ibin) + ftight  ) / h_loose->GetBinContent(ibin);
      fr = fratio/ (1.+fratio); 

      cout << "(1st it bound on) Fake rate = " << fr << endl;
      
      ftight = h_tight->GetBinContent(ibin) *  alpha * fr * (1- r.at(ibin-1));

      fratio = (h_np->GetBinContent(ibin) + ftight  ) / h_loose->GetBinContent(ibin);
      fr = fratio/ (1.+fratio);

      cout << "(2st it bound on) Fake rate = " << fr << endl;

      ftight = h_tight->GetBinContent(ibin) *  alpha * fr * (1- r.at(ibin-1));

      fratio = (h_np->GetBinContent(ibin) + ftight  ) / h_loose->GetBinContent(ibin);
      fr = fratio/ (1.+fratio);

      cout << "(3rd it bound on) Fake rate = " << fr << endl;

      ftight = h_tight->GetBinContent(ibin) *  alpha * fr * (1- r.at(ibin-1));

      fratio = (h_np->GetBinContent(ibin) + ftight  ) / h_loose->GetBinContent(ibin);
      fr = fratio/ (1.+fratio);

      cout << "(4th it bound on) Fake rate = " << fr << endl;


    }
    
  }
  
  c1->SaveAs(("GetFRFromSingleEl_pt.pdf"));
}

bool Norm(TH1* h, TH1* h2){

  cout << "Integral pf hist 1 = " << h->Integral() << endl;
  cout << "Integral pf hist 2 = " << h2->Integral() << endl;
  if(h->Integral() > (h2->Integral() * 1.5)) {
    h->Scale(1/h->Integral());
    h2->Scale(1/h2->Integral());
    return true;
  }
  if(h->Integral() < (h2->Integral() * 0.6)) {
    h->Scale(1/h->Integral());
    h2->Scale(1/h2->Integral());
    return true;
  }


  return false;
}



void Rebin(TH1* h1, TH1* h2, int rb){
  h1->Rebin(rb);
  h2->Rebin(rb);
}
void CheckHist(TH1* hist){

  if(!hist){
    cout << "Histogram not found " << endl;
  }
  return;
}


void SetHist(TH1F* hist, TH1F* hist2, TString xtitle, TString ytitle, double xmin, double xmax){


  hist->GetXaxis()->SetTitleOffset(1.05);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetLabelSize(0.04);
  hist->GetYaxis()->SetTitleOffset(1.05);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetLabelSize(0.04);

  Int_t nbins =hist->GetNbinsX();
  Double_t lastbin_value =hist->GetBinContent(nbins);
  Double_t overflow_value =hist->GetBinContent(nbins + 1);
  hist->SetBinContent(nbins, lastbin_value + overflow_value );

  hist->GetYaxis()->SetTitle(ytitle);
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetXaxis()->SetRangeUser(xmin,xmax);

  float max = hist->GetBinContent(hist->GetMaximumBin());
  float max2 = hist2->GetBinContent(hist2->GetMaximumBin());


  if(max2> max) max = max2;
  hist->GetYaxis()->SetRangeUser(0.00001,max*1.2);

}

void SetApp(TH1* hist,Color_t col, Style_t sty, Width_t w){

  hist->SetLineColor(col);
  hist->SetLineStyle(sty);
  hist->SetLineWidth(w);
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
  tdrStyle->SetGridColor(0); tdrStyle->SetGridStyle(3);
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
