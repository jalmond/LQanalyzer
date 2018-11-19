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

void GenericPlotterHNDiLepton(){

  setTDRStyle();
  vector<TString> hists;
  hists.push_back("TReco_2matched_maxdRlN");
  hists.push_back("TReco_2matched_dRlN");
  hists.push_back("TReco_2matched_dRlNwrong");
  hists.push_back("TReco_mlljj_Low_onejDiMuon_inclusive");
  hists.push_back("TReco_ml1jj_Low_onejDiMuon_inclusive");
  hists.push_back("TReco_ml2jj_Low_onejDiMuon_inclusive");
  hists.push_back("TReco_2matched_dRlNonej");
  hists.push_back("TReco_2matched_dRlNonejwrong");
  hists.push_back("TReco_2matched_dRlNmix");
  hists.push_back("TReco_2matched_dRlNmixwrong");
  hists.push_back("TReco_mllj_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("TReco_ml1j_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("TReco_ml2j_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("TReco_mlljj_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("TReco_ml1jj_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("TReco_ml2jj_Low_nonmatchedDiMuon_inclusive");
  hists.push_back("DiMuon_inclusiveMl2j_highDR_matchedJ");
  hists.push_back("DiMuon_inclusiveMl2j_lowDR_matchedJ");
  hists.push_back("DiMuon_inclusiveMllj_highDR_matchedJ");
  hists.push_back("DiMuon_inclusiveMllj_lowDR_matchedJ");
  hists.push_back("DiMuon_inclusivedeltaR_matched_mu1");
  hists.push_back("DiMuon_inclusivedeltaR_matched_mu2");
  hists.push_back("DiMuon_inclusivedeltaR_nonmatched_mu1");
  hists.push_back("DiMuon_inclusivedeltaR_nonmatched_mu2");

  hists.push_back("DiMuon_inclusive_Muon_From_N");
  hists.push_back("DiMuon_inclusive_20_matched_jet_pt_nc");
  hists.push_back("DiMuon_inclusive_20_matched_jet_eta_nc");
  hists.push_back("DiMuon_inclusive_20_matched_jet_pt_pu");
  hists.push_back("DiMuon_inclusive_20_matched_jet_eta_pu");
  hists.push_back("DiMuon_inclusive_20_matched_jet_pt_tight");
  hists.push_back("DiMuon_inclusive_20_matched_jet_eta_tight");

  hists.push_back("DiMuon_inclusive_Truth_Jets_FromW_Pt");
  hists.push_back("DiMuon_inclusive_Truth_Jets_FromW_Eta");
  hists.push_back("DiMuon_inclusive_pujets_Truth_Jets_FromW_Eta");
  hists.push_back("DiMuon_inclusive_Truth_Jets_FromW_Eta_pt15");
  hists.push_back("DiMuon_inclusive_Truth_Jets_FromW_Eta_pt20");
  hists.push_back("Matched_JJ_truth_lowmassDiMuon_inclusive");
  hists.push_back("Matched_recoJJ_truth_lowmassDiMuon_inclusive");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Pt");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Eta");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Eta_pt10");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_Eta_pt15");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_dR_closest_q");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_dR_recoLepton");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_Pt");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_Eta_pt10");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_Eta_pt15");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_dRN");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_dR_lep2");
  hists.push_back("DiMuon_inclusivejj_lm");
  hists.push_back("DiMuon_inclusivejj_matched_lm");
  hists.push_back("DiMuon_inclusivel1jj_LowMass");
  hists.push_back("DiMuon_jets_pt15l1jj_LowMass");
  hists.push_back("DiMuon_jets_eta5l1jj_LowMass");
  hists.push_back("DiMuon_inclusivel1jj_matched_LowMass");
  hists.push_back("DiMuon_inclusivel2jj_LowMass");
  hists.push_back("DiMuon_inclusivel2jj_matched_LowMass");
  hists.push_back("DiMuon_inclusivell_lowmass_flow");
  hists.push_back("DiMuon_inclusivell_lowmasssig_bin1_2");
  hists.push_back("DiMuon_inclusivell_lowmasssig_bin1_culmbreakdown");
  hists.push_back("DiMuon_inclusivell_lowmasssig_bin2_breakdown");
  hists.push_back("DiMuon_inclusivell_lowmasssig_bin2_culmbreakdown");
  hists.push_back("DiMuon_inclusivelljj_LowMass");
  hists.push_back("DiMuon_inclusivellj");
  hists.push_back("DiMuon_inclusivel1j");
  hists.push_back("DiMuon_inclusivel2j");
  hists.push_back("DiMuon_inclusivelljj_matched_LowMass");
  hists.push_back("Truth_qq_fromW_dR");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromW_eff");
  hists.push_back("DiMuon_inclusive_Truth_Lepton_FromN_eff");
  hists.push_back("DiMuon_inclusive_drX_muon");
  hists.push_back("DiMuon_inclusive_drX_reco_muon");
  hists.push_back("DiMuon_inclusive_gen_matched_muon");
  hists.push_back("DiMuon_inclusive_lep1_lep2_dR");
  hists.push_back("DiMuon_inclusive_lep1_lep2_reco_dR");
  hists.push_back("DiMuon_inclusive_mll");
  hists.push_back("DiMuon_inclusive_mll_2010");
  hists.push_back("Matched_J_truth_lowmassDiMuon_inclusive");
  hists.push_back("TReco_mlljj_LowDiMuon_inclusive_pujets");  
  hists.push_back("TReco_ml1j_LowDiMuon_inclusive_pujets");  
  hists.push_back("TReco_ml2jj_LowDiMuon_inclusive_pujets");
  hists.push_back("TReco_jj_LowDiMuon_inclusive_pujets");
  hists.push_back("TReco_mllj_LowDiMuon_inclusive_pujets");
  hists.push_back("TReco_ml2j_LowDiMuon_inclusive_pujets");
  hists.push_back("TReco_ml1j_LowDiMuon_inclusive_pujets");
  hists.push_back("Matched_recomuon_recoJJ_truth_lowmassDiMuon_inclusive_pujets");
  hists.push_back("TightMatched_recomuon_recoJJ_truth_lowmassDiMuon_inclusive_pujets");
  hists.push_back("Tight40Matched_recomuon_recoJJ_truth_lowmassDiMuon_inclusive_pujets");
  hists.push_back("DiMuon_inclusive_pujets_Muon_From_N_2010");
  hists.push_back("DiMuon_inclusive_pujets_Muon_From_N");


  string indexname="HNDiLepton/LowMass_index.html";
  ofstream ofile_tex;
  ofile_tex.open(indexname.c_str());
  ofile_tex.setf(ios::fixed,ios::floatfield);
  TString date="2017-11-20";

  TString analyzer="GetSignalEff";
  analyzer="HNDiLepton";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";

  TFile * fmc_s_40 = new TFile( (path+"/"+analyzer+"_HNMuMu_40_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_50 = new TFile( (path+"/"+analyzer+"_HNMuMu_50_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_60 = new TFile( (path+"/"+analyzer+"_HNMuMu_60_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_70 = new TFile( (path+"/"+analyzer+"_HNMuMu_70_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_80 = new TFile( (path+"/"+analyzer+"_HNMuMu_80_cat_v8-0-7.root" ).Data());

  for(unsigned int ihist= 0; ihist < hists.size() ; ihist++){
    TString htmlline= "<embed src=\""+hists[ihist]+".pdf\" width=\"800px\" height=\"700px\" />";

    //   ofile_tex << '<embed src="'+hists[ihist]+'.pdf" width="900px" height="1100px" />' << endl;
    cout << htmlline << endl;
    ofile_tex << htmlline << endl;

    TString dirname="Hists/";
    if(hists[ihist].Contains("cutflow")){
      dirname="";
    }
    bool norm=true;
    int rb=1;
    if(hists[ihist].Contains("_lm"))  rb=4;
    TH1F* hS = MakePlot(analyzer,date,"HNMuMu_40_cat",dirname+hists[ihist],norm, fmc_s_40,rb); 
    TH1F* hS2 = MakePlot(analyzer,date,"HNMuMu_50_cat",dirname+hists[ihist],norm,fmc_s_50,rb); 
    TH1F* hS3 = MakePlot(analyzer,date,"HNMuMu_60_cat",dirname+hists[ihist],norm,fmc_s_60,rb); 
    TH1F* hS4 = MakePlot(analyzer,date,"HNMuMu_70_cat",dirname+hists[ihist],norm,fmc_s_70,rb); 
    TH1F* hS5 = MakePlot(analyzer,date,"HNMuMu_80_cat",dirname+hists[ihist],norm,fmc_s_80,rb); 
    
    
    TString cantag= hists[ihist]+"TL";
    TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 
      
      
    float maxS=hS->GetMaximum();
    if(hS2->GetMaximum() > maxS) maxS = hS2->GetMaximum();
    if(hS3->GetMaximum() > maxS) maxS = hS3->GetMaximum();
    if(hS4->GetMaximum() > maxS) maxS = hS4->GetMaximum();
    if(hS5->GetMaximum() > maxS) maxS = hS5->GetMaximum();
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
    x_range*= 1.3;
    cout << "x_range = " << x_range << endl;

    hS->GetYaxis()->SetRangeUser(0.,maxS);
    hS->GetXaxis()->SetRangeUser(0.1,x_range);
    if(hists[ihist].Contains("jj"))     hS->GetXaxis()->SetRangeUser(10,x_range);
    if(hists[ihist].Contains("eta"))   hS->GetXaxis()->SetRangeUser(-1*x_range,x_range);
    

    hS->GetYaxis()->SetTitle("Events/bin");
    hS->Draw("hist");
    hS2->Draw("histsame");
    hS3->Draw("histsame");
    hS4->Draw("histsame");
    hS5->Draw("histsame");
    CMS_lumi( c1, 4, 11 );    

    
    legendS->AddEntry(hS,"Schann. (ee) m_{N}(40)","l");
    legendS->AddEntry(hS2,"Schann. (ee) m_{N}(50)","l");
    legendS->AddEntry(hS3,"Schann. (ee) m_{N}(60)","l");
    legendS->AddEntry(hS4,"Schann. (ee) m_{N}(70)","l");
    legendS->AddEntry(hS5,"Schann. (ee) m_{N}(80)","l");
    
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
      
    c1->SaveAs("HNDiLepton/"+hists[ihist]+".pdf","pdf");
    
      
  }
  
  gSystem->Exec("scp HNDiLepton/* jalmond@lxplus067.cern.ch:~/www/SignalHN/");

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
  
  if(sample.Contains("_50_")) h->SetLineColor(kBlue);
  if(sample.Contains("_40_")) h->SetLineColor(kRed);
  if(sample.Contains("_60_")) h->SetLineColor(kGreen -2);
  if(sample.Contains("_70_")) h->SetLineColor(kCyan);
  if(sample.Contains("_80_")) h->SetLineColor(kOrange);
 

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

  if(iPosX==2)  latex.DrawLatex(1-r-0.22,1-t+lumiTextOffset*t*1.5, "low-mass s-channel,");
  else  latex.DrawLatex(1-r-0.4,1-t+lumiTextOffset*t*1.5, "low-mass s-channel,");

  

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



