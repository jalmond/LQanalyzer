#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <fstream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include <sstream>      // std::stringstream
#include <map>
#include "TSystem.h"


void setTDRStyle();
TH1F* MakePlot(TString analyzer,TString sample, TString hist, TString cut, bool norm, TFile* f, int rb);
float Get90Xval(TH1* h);

void MakeWZLepVetomass(float maxmass, TString mass){


  setTDRStyle();
  


  TString date="2017-11-06";
  
  TString histname =  "DiMuon_inclusiveTruth_WZ_SS_Zmass_lepveto";
  TString histname2 = "DiMuon_inclusiveTruth_WZ_SS_Zmass";
  TString analyzer="GetSignalEff";
  analyzer="HNDiLepton";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";
  
  
  TString cantag= histname+"TL";
  
  TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 
    
  TFile * fmc_1= new TFile( (path+"/"+analyzer+"_SKWZTo3LNu_powheg_cat_v8-0-7.root" ).Data());
  TFile * fmc_3= new TFile( (path+"/"+analyzer+"_SKWZTo3LNu_mllmin01_cat_v8-0-7.root" ).Data());
  TFile * fmc_4= new TFile( (path+"/"+analyzer+"_SKWGtoLNuG_cat_v8-0-7.root" ).Data());


  
  TString dirname = "Hists/";
  bool norm=false;
  int rb=2;
  TH1F* hS1 = MakePlot(analyzer,date,"WZ_all_cat",dirname+histname,norm, fmc_1,rb); 
  TH1F* hS3 = MakePlot(analyzer,date,"WZTo3LNu_mllmin01_cat",dirname+histname,norm, fmc_3,rb);
  TH1F* hS4 = MakePlot(analyzer,date,"WGtoLNuG_cat",dirname+histname,norm, fmc_3,rb);

  
  TH1F* hS12 = MakePlot(analyzer,date,"WZ_all_cat",dirname+histname2,norm, fmc_1,rb);
  TH1F* hS32 = MakePlot(analyzer,date,"WZTo3LNu_mllmin01_cat",dirname+histname2,norm, fmc_3,rb);
  TH1F* hS42 = MakePlot(analyzer,date,"WGtoLNuG_cat",dirname+histname2,norm, fmc_3,rb);

  hS1->Add(hS4);
  hS12->Add(hS42);
  hS1->Divide(hS12);
  hS3->Divide(hS32);

  hS1->SetLineColor(kRed);
  hS3->SetLineColor(kGreen-2);
  
  //hS1->Scale(0.97);
  //hS3->Scale(0.7);
  
  hS3->SetLineStyle(2);
  
  hS1->SetLineWidth(2.);
  hS3->SetLineWidth(2.);
  
  hS1->GetXaxis()->SetTitle("m_{ll} (GeV)");
  
  hS1->SetLineColor(kRed);
  hS3->SetLineColor(kBlue);
  //hS1->SetFillColor(kBlue-2);
  //hS1->SetFillStyle(3444);
  hS1->GetYaxis()->SetTitle("Efficiency of veto lepton cut");
  hS1->Draw("");

  hS3->SetFillColor(kOrange);
  hS3->SetFillStyle(3440);
  hS3->Draw("same");
  TLegend *legend = new TLegend(.25, 0.7, .45, 0.9);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.03);
  legend->AddEntry(hS1,"WZ powheg + WG","l");
  legend->AddEntry(hS3,"WZ powheg (m > 0.1) * 0.7","l");
  
  legend->Draw();
    
    
    
    c1->SaveAs("WZ/" + histname+"_"+mass+"lepvetoeff.pdf","pdf"); 
    
    
    gSystem->Exec("scp WZ/" + histname+"_"+mass+"lepvetoeff.pdf  jalmond@lxplus102.cern.ch:~/www/2016AN/");
    
    cout << "https://jalmond.web.cern.ch/jalmond/2016AN/"+histname+"_"+mass+"lepvetoeff.pdf" << endl;
    

}

float Get90Xval(TH1* h){

  float integral=0.;
  for(unsigned int ib=0 ;ib < h->GetNbinsX()+1; ib++){
    integral+=  h->GetBinContent(ib);
  }
  float bin90p=integral*0.99;
  float integral_check(0);
  for(unsigned int ib=0 ;ib < h->GetNbinsX()+1; ib++){
    integral_check+=h->GetBinContent(ib);
    if(integral_check > bin90p) return h->GetBinLowEdge(ib+1);
  }
}

TH1F* MakePlot(TString analyzer, TString date,TString sample, TString hist, bool renorm, TFile* fmc, int rb){

  TH1::SetDefaultSumw2();
  
  cout << fmc << " " << sample << " " << hist << endl;
  TH1F* h = (TH1F*)fmc->Get(hist);
  cout << h << endl;
  if(sample.Contains("WG")) h->SetLineColor(kBlue);
  if(sample.Contains("mcat")) h->SetLineColor(kGreen-2);
  if(sample.Contains("mll")) h->SetLineColor(kCyan);
  else  h->SetLineColor(kRed);

  h->SetLineWidth(2.);
  h->Rebin(rb);

  return h;
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
  tdrStyle->SetPadRightMargin(0.05);

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
  tdrStyle->SetTitleXOffset(0.9);  tdrStyle->SetTitleYOffset(1.2);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset                                                                                                                                

   tdrStyle->  SetFillColorAlpha(45,0.35);

  // For the axis labels:                                                                                                                                                                                

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?                                                                                                                       
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);                                                                                                                                                       
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.2);
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
