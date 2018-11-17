#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TSystem.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include <sstream>      // std::stringstream
#include "CMS_lumi.h"


void setTDRStyle();
TH1F* MakePlot(TString analyzer,TString sample, TString hist, TString cut, bool norm, TFile* f, int rb);
float Get90Xval(TH1* h);

void  MakeElectron_opt_sigdxyEC(){

  setTDRStyle();

  TString date="2017-11-27";

  TString analyzer="GetSignalEff";
  analyzer="HNDiElectron";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";

  TFile * fmc_s_40 = new TFile( (path+"/"+analyzer+"_HNEpEp_100_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_200 = new TFile( (path+"/"+analyzer+"_HNEpEp_200_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_1000 = new TFile( (path+"/"+analyzer+"_HNEpEp_1000_cat_v8-0-7.root" ).Data());

  TString hist = "h_LeptonDXY_EC_DiElectron_mvatightSSLL_Preselection";
    
  bool norm=true;
  int rb=4;
  TH1F* hS = MakePlot(analyzer,date,"HNEpEp_40_cat","DiElectron_mvatightSSLL_Preselection/"+hist,norm, fmc_s_40,rb); 
  TH1F* hS2 = MakePlot(analyzer,date,"HNEpEp_200_cat","DiElectron_mvatightSSLL_Preselection/"+hist,norm, fmc_s_200,rb); 
  TH1F* hS3 = MakePlot(analyzer,date,"HNEpEp_1000_cat","DiElectron_mvatightSSLL_Preselection/"+hist,norm, fmc_s_1000,rb); 

    
    

  TString cantag= hist;
  TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 
    
      
  float maxS=hS->GetMaximum();
  if(hS2->GetMaximum() > maxS) maxS = hS2->GetMaximum();
  if(hS3->GetMaximum() > maxS) maxS = hS3->GetMaximum();
  maxS=maxS*1.5;
    

  float H = c1->GetWh();
  float W = c1->GetWw();
  float l = c1->GetLeftMargin();
  float t = c1->GetTopMargin();
  float r = c1->GetRightMargin();
  float b = c1->GetBottomMargin();
  
  
  TLegend *legendS = new TLegend(1-(r+ 0.35), 1-(t + 0.3), 1- (r+ 0.05),  1-(t + 0.1));
  legendS->SetFillColor(10);
  legendS->SetBorderSize(0);
  legendS->SetTextSize(0.03);
  
  float x_range = Get90Xval(hS);
  x_range*= 1.5;
  cout << "x_range = " << x_range << endl;

  hS->GetYaxis()->SetRangeUser(0.,maxS);
  hS->GetXaxis()->SetRangeUser(-0.05,0.05);
  hS->GetXaxis()->SetTitle("d_{xy}");
  
  hS->GetYaxis()->SetTitle("Events");
  hS->Draw("hist");
  hS2->Draw("histsame");
  hS3->Draw("histsame");
  CMS_lumi( c1, 4, 11 );    
  
  
  legendS->AddEntry(hS,"WN->ee m_{N}(40)","l");
  legendS->AddEntry(hS2,"WN->ee m_{N}(200)","l");
  legendS->AddEntry(hS3," WN->ee m_{N}(1000)","l");
  
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);
  
  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  
  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(11);
  latex.SetTextColor(kRed);
  latex.SetTextSize(cmsTextSize*t*.75);    
  latex.DrawLatex(1-(r+ 0.35), 1-(t + 0.05), "Normalised to unity");
  legendS->Draw();
  
  latex.DrawLatex((r+ 0.15), 1-(t + 0.05), "Additional cuts:");
  latex.DrawLatex((r+ 0.15), 1-(t + 0.1), "- d(xy) < 0.02/0.05 (B/EC)");
  latex.DrawLatex((r+ 0.15), 1-(t + 0.15),"- d_(z) < 0.1/0.2 (B/EC)");
  latex.DrawLatex((r+ 0.15), 1-(t + 0.2), "- tight-charge");
  latex.DrawLatex((r+ 0.15), 1-(t + 0.25), "- rel_iso < 0.05");


  c1->SaveAs("HNDiLepton/"+hist+".pdf","pdf");
  
  gSystem->Exec("scp HNDiLepton/"+hist+".pdf jalmond@lxplus067.cern.ch:~/www/SignalHN/");
  

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
  //  TH1F* h_norm = (TH1F*)fmc->Get("DiMuon_inclusive_pujetsmm_eventcutflow_DoubleMuon");
  //float n=h_norm->GetBinContent(1);
  if(sample.Contains("_40_")) h->SetLineColor(kBlue);
  if(sample.Contains("_200_")) h->SetLineColor(kRed);
  if(sample.Contains("_1000_")) h->SetLineColor(kGreen -2);
  if(sample.Contains("_70_")) h->SetLineColor(kCyan);
  if(sample.Contains("_80_")) h->SetLineColor(kOrange);
 

  h->SetLineWidth(2.);
  h->Rebin(rb);
  float sigeff=0.43;
  float bkg=30.24;
  
  if(sample.Contains("40"))    sigeff=0.88;
  if(sample.Contains("50"))    sigeff=1.;
  if(sample.Contains("60"))    sigeff=0.72;
  if(sample.Contains("70"))    sigeff=0.15;
  if(sample.Contains("80"))    sigeff=0.34;
  
  
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
  tdrStyle->SetPadLeftMargin(0.12);
  tdrStyle->SetPadRightMargin(0.06);

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
  tdrStyle->SetTitleYOffset(3.5);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset                                                                                                                                

  // For the axis labels:                                                                                                                                                                                

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelOffset(0.017, "Y");
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

void
CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  if(iPosX!=2) t*= 0.7;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV_2016_muon_BtoE;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV_2016_muon_BtoE;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  //if(iPosX==2)  latex.DrawLatex(1-r-0.22,1-t+lumiTextOffset*t*1.5, "low-mass s-channel,");
  //else  latex.DrawLatex(1-r-0.4,1-t+lumiTextOffset*t*1.5, "low-mass s-channel,");

  

  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(11);
  latex.SetTextSize(cmsTextSize*t);
  latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
  


  float posY_ = 1-t+lumiTextOffset*t;
  
  
  latex.SetTextAlign(11);
  float posX_ = l +  relPosX*(1-l-r) + 0.06;
  latex.SetTextFont(extraTextFont);
  latex.SetTextSize(extraTextSize*t);
  //latex.SetTextAlign(align_);
  latex.DrawLatex(posX_, posY_, extraText);

  return;
}



