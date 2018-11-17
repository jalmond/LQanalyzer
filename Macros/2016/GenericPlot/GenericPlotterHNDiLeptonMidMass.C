#include "TH2.h"mi
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

void setTDRStyle();
TH1F* MakePlot(TString analyzer,TString sample, TString hist, TString cut, TFile* f, int rb);
float Get90Xval(TH1* h);

void GenericPlotterHNDiLeptonMidMass(){

  setTDRStyle();
  vector<TString> hists;
  hists.push_back("DiMuon_NoFATll_highmasssig_window02_bin1");
  hists.push_back("DiMuon_inclusivell_highmasssig_bin1");
  hists.push_back("DiMuon_inclusive_Muon_From_N");
  hists.push_back("DiMuon_inclusive_Truth_Jets_FromW_Pt");
  hists.push_back("Truth_qq_fromW_dR");
  hists.push_back("Matched_JJ_truth_highmassDiMuon_inclusive");
  hists.push_back("Matched_JJ_ak8_truth_highmassDiMuon_inclusive");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Pt");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Eta");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_dR_closest_q");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_dR_recoLepton");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_Pt");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_dRN");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_dR_lep2");
  hists.push_back("DiMuon_inclusivejj_lm");
  hists.push_back("DiMuon_inclusivejj_matched_lm");
  hists.push_back("DiMuon_inclusivel1jj_HighMass");
  hists.push_back("DiMuon_inclusivel1jj_matched_HighMass");
  hists.push_back("DiMuon_inclusivel2jj_HighMass");
  hists.push_back("DiMuon_inclusivel2jj_matched_HighMass");
  hists.push_back("DiMuon_inclusivell_highmasssig_bin1");
  hists.push_back("DiMuon_inclusivelljj_HighMass");
  hists.push_back("DiMuon_inclusivelljj_matched_HighMass");
  hists.push_back("DiMuon_NoFATjj_lm");
  hists.push_back("DiMuon_NoFATjj_matched_lm");
  hists.push_back("DiMuon_NoFATl1jj_HighMass");
  hists.push_back("DiMuon_NoFATl1jj_matched_HighMass");
  hists.push_back("DiMuon_NoFATl2jj_HighMass");
  hists.push_back("DiMuon_NoFATl2jj_matched_HighMass");
  hists.push_back("DiMuon_NoFATll_highmasssig_bin1");
  hists.push_back("DiMuon_NoFATlljj_HighMass");
  hists.push_back("DiMuon_NoFATlljj_matched_HighMass");
  hists.push_back("DiMuon_inclusivellfj");
  hists.push_back("DiMuon_inclusivel1fj");
  hists.push_back("DiMuon_inclusivel2fj");
  hists.push_back("DiMuon_inclusivefj");
  hists.push_back("DiMuon_inclusivejj_lm");
  hists.push_back("DiMuon_inclusivejj_matched_lm");
  hists.push_back("DiMuon_inclusivel1jj_HighMass");
  hists.push_back("DiMuon_inclusivel1jj_matched_HighMass");
  hists.push_back("DiMuon_inclusivel2jj_HighMass");
  hists.push_back("DiMuon_inclusivel2jj_matched_HighMass");

  hists.push_back("DiMuon_inclusivelljj_HighMass");
  hists.push_back("DiMuon_inclusivelljj_matched_HighMass");



  string indexname="HNDiLeptonMidMass/MidMass_index.html";
  ofstream ofile_tex;
  ofile_tex.open(indexname.c_str());
  ofile_tex.setf(ios::fixed,ios::floatfield);
  TString date="2017-10-30";

  TString analyzer="GetSignalEff";
  analyzer="HNDiLepton";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";

  TFile * fmc_s_100 = new TFile( (path+"/"+analyzer+"_HNMuMu_100_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_125 = new TFile( (path+"/"+analyzer+"_HNMuMu_125_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_150 = new TFile( (path+"/"+analyzer+"_HNMuMu_150_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_200 = new TFile( (path+"/"+analyzer+"_HNMuMu_200_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_250 = new TFile( (path+"/"+analyzer+"_HNMuMu_250_cat_v8-0-7.root" ).Data());

  for(unsigned int ihist= 0; ihist < hists.size() ; ihist++){
    TString htmlline= "<embed src=\""+hists[ihist]+"Mid.pdf\" width=\"800px\" height=\"700px\" />";

    //   ofile_tex << '<embed src="'+hists[ihist]+'.pdf" width="900px" height="1100px" />' << endl;
    cout << htmlline << endl;
    ofile_tex << htmlline << endl;

    TString dirname="Hists/";
    if(hists[ihist].Contains("cutflow")){
      dirname="";
    }
    bool norm=true;
    int rb=1;
    if(hists[ihist].Contains("jj"))  rb=2;
    TH1F* hS = MakePlot(analyzer,date,"HNMuMu_100_cat",dirname+hists[ihist],norm, fmc_s_100,rb); 
    TH1F* hS2 = MakePlot(analyzer,date,"HNMuMu_125_cat",dirname+hists[ihist],norm,fmc_s_125,rb); 
    TH1F* hS3 = MakePlot(analyzer,date,"HNMuMu_150_cat",dirname+hists[ihist],norm,fmc_s_150,rb); 
    TH1F* hS4 = MakePlot(analyzer,date,"HNMuMu_200_cat",dirname+hists[ihist],norm,fmc_s_200,rb); 
    TH1F* hS5 = MakePlot(analyzer,date,"HNMuMu_250_cat",dirname+hists[ihist],norm,fmc_s_250,rb); 
    
    
    TString cantag= hists[ihist]+"TL";
    TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 
      
      
    TLegend *legend = new TLegend(.7, 0.65, .9, 0.9);
    legend->SetFillColor(10);
    legend->SetBorderSize(0);
    legend->SetTextSize(0.03);
    
    float maxS=hS->GetMaximum();
    if(hS2->GetMaximum() > maxS) maxS = hS2->GetMaximum();
    if(hS3->GetMaximum() > maxS) maxS = hS3->GetMaximum();
    if(hS4->GetMaximum() > maxS) maxS = hS4->GetMaximum();
    if(hS5->GetMaximum() > maxS) maxS = hS5->GetMaximum();
    maxS=maxS*1.2;
    

    
    
    TLegend *legendS = new TLegend(.7, 0.7, .9, 0.95);
    legendS->SetFillColor(10);
    legendS->SetBorderSize(0);
    legendS->SetTextSize(0.03);

    float x_range1 = Get90Xval(hS);
    float x_range2 = Get90Xval(hS2);
    float x_range3 = Get90Xval(hS3);
    float x_range4 = Get90Xval(hS4);
    float x_range5 = Get90Xval(hS5);
    float x_range=x_range1;
    if(x_range2 > x_range ) x_range=x_range2;
    if(x_range3 > x_range ) x_range=x_range3;
    if(x_range4 > x_range ) x_range=x_range4;
    if(x_range5 > x_range ) x_range=x_range5;

    x_range*= 1.3;
    cout << "x_range = " << x_range << endl;

    hS->GetYaxis()->SetRangeUser(0.,maxS);
    hS->GetXaxis()->SetRangeUser(0.1,x_range);
    if(hists[ihist].Contains("jj")) {
      hS->GetXaxis()->SetRangeUser(10,x_range);
      //if(!hists[ihist].Contains("matched"))       hS->GetYaxis()->SetRangeUser(0.,0.2);

    }
    if(hists[ihist].Contains("eta"))   hS->GetXaxis()->SetRangeUser(-1*x_range,x_range);
    
    hS->Draw("hist");
    hS2->Draw("histsame");
    hS3->Draw("histsame");
    hS4->Draw("histsame");
    hS5->Draw("histsame");
      
    legendS->AddEntry(hS,"Schann. MM m_{N}=100","l");
    legendS->AddEntry(hS2,"Schann. MM m_{N}=125","l");
    legendS->AddEntry(hS3,"Schann. MM m_{N}=150","l");
    legendS->AddEntry(hS4,"Schann. MM m_{N}=200","l");
    legendS->AddEntry(hS5,"Schann. MM m_{N}=250","l");
    
    
    legendS->Draw();
      
    c1->SaveAs("HNDiLeptonMidMass/"+hists[ihist]+"Mid.pdf","pdf");
    
      
  }
  
  gSystem->Exec("scp HNDiLeptonMidMass/* jalmond@lxplus102.cern.ch:~/www/SignalHN/MidMass/");
  cout << "https://jalmond.web.cern.ch/jalmond/SignalHN/MidMass/MidMass_index.html" << endl;

}

float Get90Xval(TH1* h){

  float integral=0.;
  for(unsigned int ib=0 ;ib < h->GetNbinsX()+1; ib++){
    integral+=  h->GetBinContent(ib);
  }
  float bin90p=integral*0.95;
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
  if(sample.Contains("_125_")) h->SetLineColor(kRed);
  if(sample.Contains("_150_")) h->SetLineColor(kGreen-2);
  if(sample.Contains("_200_")) h->SetLineColor(kCyan);
  if(sample.Contains("_250_")) h->SetLineColor(kOrange);
 

  h->SetLineWidth(2.);
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
  tdrStyle->SetTitleXOffset(0.9);  tdrStyle->SetTitleYOffset(1.4);
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
