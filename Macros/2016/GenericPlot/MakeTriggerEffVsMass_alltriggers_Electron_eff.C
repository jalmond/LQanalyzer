#include "TH2.h"
#include "TH1F.h"
#include "TLine.h"
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

void MakeTriggerEffVsMass_alltriggers_Electron_eff(TString ptcut){
 
  setTDRStyle();
  TString histname = "TriggerEfficiency_numerator_dimuon_pt_"+ptcut;
  TString histname2 = "TriggerEfficiency_denominator_nojet_"+ptcut;
  TString date="2017-11-06";
  
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

  c1->Draw();
  c1->SetLogy();
  TPad *c1_up;
  TPad *c1_down;
  c1_up = new TPad("c1", "", 0, 0.25, 1, 1);
  c1_down = new TPad("c1_down", "", 0, 0, 1, 0.25);

  c1_up->SetTopMargin( 0.07 );
  c1_up->SetBottomMargin( 0.02 );
  c1_up->SetLeftMargin( 0.15 );
  c1_up->SetRightMargin( 0.03 );

  c1_down->SetTopMargin( 0.03 );
  c1_down->SetBottomMargin( 0.4 );
  c1_down->SetLeftMargin( 0.15 );
  c1_down->SetRightMargin( 0.03 );

  c1->SetTopMargin( 0.05 );
  c1->SetBottomMargin( 0.13 );
  c1->SetRightMargin( 0.05 );
  c1->SetLeftMargin( 0.16 );
  //===============================================
  //==== Draw empty pads first
  //===============================================

  c1_up->Draw();
  c1_down->Draw();
  c1_up->cd();
  c1->SetLogy();
  
  TH1F* h1 =  new TH1F("","",  masslist.size(), 0., float(masslist.size()));
  TH1F* h2 =  new TH1F("tmp2","tmp2",  masslist.size(), 0., float(masslist.size()));
  TH1F* h3 =  new TH1F("tmp3","tmp3",  masslist.size(), 0., float(masslist.size()));
  TH1F* h4 =  new TH1F("tmp4","tmp4",  masslist.size(), 0., float(masslist.size()));


  c1_down->cd();

  int i=0;
  
  for( mit = masslist.begin(); mit !=masslist.end(); mit++,i++){

    TFile * fmc_ = new TFile( (path+"/"+analyzer+"_HNEE_"+mit->second+"_cat_v8-0-7.root" ).Data());
    cout << mit->second << endl;
    TString dirname="Hists/";
    if(histname.Contains("cutflow")){
      dirname="";
    }
    bool norm=false;
    int rb=1;
    TH1F* hS1 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+histname,norm, fmc_,rb); 
    TH1F* hS2 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+histname2,norm, fmc_,rb); 
    
    cout << hS1 << " " << hS2 << endl;
    hS1->Divide(hS2);
    h1->GetXaxis()->SetBinLabel(i+1, mit->second);
    h4->GetXaxis()->SetBinLabel(i+1, mit->second);
  
    h1->SetBinContent(i+1, hS1->GetBinContent(2));
    h2->SetBinContent(i+1, hS1->GetBinContent(7));
    h4->SetBinContent(i+1,  hS1->GetBinContent(7) /  hS1->GetBinContent(2));    
  }
  

  h1->SetMarkerStyle(23);
  h1->SetMarkerSize(1);
  h1->SetMarkerColor(kRed);
  h2->SetMarkerStyle(23);
  h2->SetMarkerColor(kBlue);
  h2->SetMarkerSize(1.);
  h3->SetMarkerStyle(23);
  h3->SetMarkerSize(1.);
  h3->SetMarkerColor(kGreen-2);

  h4->SetLineColor(kBlue);


  c1_down->cd();

  TLine *devz = new TLine(h4->GetBinLowEdge(h4->GetXaxis()->GetFirst()),1.0,h4->GetBinLowEdge(h4->GetXaxis()->GetLast()+1),1.0  );
  devz->SetLineWidth(1);
  devz->SetLineStyle(1);
  

  h4->SetMaximum(1.2);
  h4->SetMinimum(0.8);
  h4->SetTitle("");
  h4->GetXaxis()->SetLabelSize(0.10);
  h4->GetXaxis()->SetTitleSize(0.15);
  h4->GetYaxis()->SetLabelSize(0.08);
  h4->GetYaxis()->SetTitleSize(0.12);
  h4->GetYaxis()->SetTitleOffset(0.5);
  //  h4->SetFillColorAlpha(45,0.35);
  h4->GetYaxis()->SetTitle("ratio (eff)");
  h4->GetXaxis()->SetTitle("m_{N} (GeV)");
  h4->Draw("l");
  h4->SetLineWidth(2.);
  h4->SetLineWidth(2.);

  //==== Bottom plot legend
  devz->Draw("SAME");
  TLegend *lg_ratio = new TLegend(0.2, 0.8, 0.6, 0.9);
  lg_ratio->SetFillStyle(0);
  lg_ratio->SetBorderSize(0);
  lg_ratio->SetNColumns(3);
  lg_ratio->AddEntry(h4,"OR Ele27","l");
  lg_ratio->Draw();
  
  c1_up->cd();
  c1_up->SetLogy();
  h1->GetYaxis()->SetTitle("Trigger efficiency");
  h1->GetXaxis()->SetTitle("m_{N} (GeV)");
  h1->GetYaxis()->SetRangeUser(0.01,1.);
  h1->SetMarkerColor(kRed);
  h2->SetMarkerColor(kCyan+4);
  h3->SetMarkerColor(kBlue);
  h4->SetMarkerColor(kGreen+2);


  h1->GetYaxis()->SetLabelSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.07);
  h1->GetYaxis()->SetTitleOffset(1.02);
  //==== hide x-axis for top plot
  h1->GetXaxis()->SetLabelSize(0);
  h1->Draw("p");
  h2->Draw("psame");

  TLegend *legend = new TLegend(.6, 0.15, .85, 0.4);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.03);
  legend->AddEntry(h1,"Ele23Ele12","p");
  legend->AddEntry(h2,"Ele23Ele12||Ele27","p");

  legend->Draw();

  c1->SaveAs("HNDiLeptonHighMass/Trigger_electronor_all_"+ptcut+"electron.pdf","pdf");
    
  gSystem->Exec("scp HNDiLeptonHighMass/Trigger_electronor_all_"+ptcut+"electron.pdf jalmond@lxplus102.cern.ch:~/www/SignalHN/HighMass/");
  
  cout << "~/www/SignalHN/HighMass/Trigger_electronor_all_"+ptcut+"electron.pdf" << endl;
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
  
  cout << h << hist << endl;
  if(sample.Contains("_40_")){
    h->SetMarkerStyle(23);
    h->SetMarkerSize(2.);
  }
  
  if(sample.Contains("_50_")){
    h->SetMarkerStyle(24);
    h->SetMarkerSize(2.);
  }
  
  if(sample.Contains("_60_")){
    h->SetMarkerStyle(28);
    h->SetMarkerSize(2.);
  }
  
  if(sample.Contains("_70_")){
    h->SetMarkerStyle(23);
    h->SetMarkerSize(2.);
    h->SetMarkerColor(kRed);
  }
  
  if(sample.Contains("_80_")){
    h->SetMarkerStyle(23);
    h->SetMarkerSize(2.);
    h->SetMarkerColor(kBlue);
  }
  

  h->Rebin(rb);
  if(renorm)h->Scale(1./h->Integral());

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
  tdrStyle->SetTitleSize(0.1, "XYZ");
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
  tdrStyle->SetLabelSize(0.15, "XYZ");

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
