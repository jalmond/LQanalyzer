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

void EtaRemoval(){

  setTDRStyle();
  TString histname = "DiElectron_NoFATll_lowmass_flow";
  
  TString date="2017-11-27";

  TString analyzer="GetSignalEff";
  analyzer="HNDiElectron";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";

  
  std::map<int, TString> masslist;

  masslist[40] = "40";
  masslist[50] = "50";
  masslist[60] = "60";
  masslist[70] = "70";
  masslist[80] = "80";
  masslist[90] = "90";
  masslist[100] = "100";
  masslist[125] = "125";
  masslist[150] = "150";
  masslist[200] = "200";
  masslist[250] = "250";
  masslist[300] = "300";
  masslist[400] = "400";
  masslist[500] = "500";
  masslist[600] = "600";
  masslist[700] = "700";
  masslist[800] = "800";
  //  masslist[900] = "900";
  masslist[1000] = "1000";
  masslist[1200] = "1200";
  masslist[1300] = "1300";
  masslist[1400] = "1400";
  masslist[1500] = "1500";

  std::map<int,TString>::iterator mit;

  TString cantag= histname+"TL";

  TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 

  TH1F* h =  new TH1F("","",  masslist.size(), 0., float(masslist.size()));
  TH1F* h2 =  new TH1F("2","2",  masslist.size(), 0., float(masslist.size()));
  TH1F* h3 =  new TH1F("3","3",  masslist.size(), 0., float(masslist.size()));


  int i=0;
  
  for( mit = masslist.begin(); mit !=masslist.end(); mit++,i++){
    h->GetXaxis()->SetBinLabel(i+1, mit->second);
    h2->GetXaxis()->SetBinLabel(i+1, mit->second);
    h3->GetXaxis()->SetBinLabel(i+1, mit->second);
  }
  
  i=1;
  for( mit = masslist.begin(); mit !=masslist.end(); mit++,i++){

    TFile * fmc_ = new TFile( (path+"/"+analyzer+"_HNEpEp_"+mit->second+"_cat_v8-0-7.root" ).Data());
    
    TString dirname="Hists/";
    if(histname.Contains("cutflow")){
      dirname="";
    }
    bool norm=true;
    int rb=1;
    TH1F* hS = MakePlot(analyzer,date,"HNEpEp_"+mit->second+"_cat",dirname+histname,norm, fmc_,rb); 
    
    float n1 = hS->GetBinContent(10);
    float n2 = hS->GetBinContent(12);
    float n3 = hS->GetBinContent(13);
    float n4 = hS->GetBinContent(14);
    
    cout << mit->second << " " << n1 << " " << n2 << endl;
    h->SetBinContent(i,n2/n1);
    h2->SetBinContent(i,n3/n1);
    h3->SetBinContent(i,n4/n1);
  }
  h->SetMarkerStyle(23);
  h->SetMarkerColor(kRed);
  h2->SetMarkerColor(kBlue);
  h3->SetMarkerColor(kCyan);
  h->SetMarkerSize(0.8);
  h2->SetMarkerStyle(21);
  h2->SetMarkerSize(0.8);
  h3->SetMarkerStyle(22);
  h3->SetMarkerSize(0.8);
  h->GetYaxis()->SetTitle("Efficiency of EC veto");
  h->GetXaxis()->SetTitle("m_{N} (GeV)");
  h->GetYaxis()->SetRangeUser(0.5,1.);
  h->Draw("p");
  h2->Draw("psame");
  h3->Draw("psame");
  

  float H = c1->GetWh();
  float W = c1->GetWw();
  float l = c1->GetLeftMargin();
  float t = c1->GetTopMargin();
  float r = c1->GetRightMargin();
  float b = c1->GetBottomMargin();


  TLegend *legendS = new TLegend(1-(r+ 0.40), 1-(t + 0.7), 1- (r+ 0.1),  1-(t + 0.45));
  legendS->SetFillColor(10);
  legendS->SetBorderSize(0);
  legendS->SetTextSize(0.03);

  legendS->AddEntry(h,"Veto EC (pt<50)","p");
  legendS->AddEntry(h2,"Veto EC (pt<20)","p");
  legendS->AddEntry(h3,"Veto EC ALL","p");
  legendS->Draw();

  c1->SaveAs("HNDiLeptonHighMass/"+histname+"all.pdf","pdf");
    
  gSystem->Exec("scp HNDiLeptonHighMass/"+histname+"all.pdf jalmond@lxplus067.cern.ch:~/www/SignalHN/HighMass/");
  
  cout << "~/www/SignalHN/HighMass/"+histname+"all.pdf" << endl;
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
  
  TH1F* h = (TH1F*)fmc->Get(hist);
  
  if(sample.Contains("_100_")) h->SetLineColor(kBlue);
  if(sample.Contains("_200_")) h->SetLineColor(kRed);
  if(sample.Contains("_500_")) h->SetLineColor(kGreen-2);
  if(sample.Contains("_800_")) h->SetLineColor(kCyan);
  if(sample.Contains("_1000_")) h->SetLineColor(kOrange);
 

  h->SetLineWidth(2.);
  //h->Rebin(rb);
  //if(renorm)h->Scale(1./h->Integral());

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
  tdrStyle->SetTitleXOffset(0.9);  tdrStyle->SetTitleYOffset(1.2);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset                                                                                                                                



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
