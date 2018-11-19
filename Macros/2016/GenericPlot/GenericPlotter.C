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

void setTDRStyle();
TH1F* MakePlot(TString analyzer,TString sample, TString hist, TString cut, TFile* f);

void GenericPlotter(){
 
  setTDRStyle();
  vector<TString> hists;
  hists.push_back("Matched_JJ_truth_highmass");
  hists.push_back("Matched_JJ_truth_lowmass");
  hists.push_back("PrunedMass");
  hists.push_back("Reco_centraljet_pt");
  //hists.push_back("Reco_eJ_dR");
  //hists.push_back("Reco_ee_dR");
  //hists.push_back("Reco_electron_1_eta");
  //hists.push_back("Reco_electron_1_pt");
  //hists.push_back("Reco_electron_2_eta");
  //hists.push_back("Reco_electron_2_pt");
  hists.push_back("Reco_fowardjet_pt");
  hists.push_back("Reco_jet_1_eta");
  hists.push_back("Reco_jet_1_pt");
  hists.push_back("Reco_jet_2_eta");
  hists.push_back("Reco_jet_2_pt");
  hists.push_back("Reco_jet_3_eta");
  hists.push_back("Reco_jet_3_pt");
  hists.push_back("Reco_jet_4_eta");
  hists.push_back("Reco_jet_4_pt");
  hists.push_back("Reco_met");
  hists.push_back("Reco_met2_st");
  hists.push_back("Reco_mjj_High");
  hists.push_back("Reco_mjj_Low");
  hists.push_back("Reco_mm_dR");
  hists.push_back("Reco_muJ_dR");
  hists.push_back("Reco_muon_1_eta");
  hists.push_back("Reco_muon_1_pt");
  hists.push_back("Reco_muon_2_eta");
  hists.push_back("Reco_muon_2_pt");
  //hists.push_back("Reco_nelectron_nocut");
  //hists.push_back("Reco_nelectron_tight");
  hists.push_back("Reco_nfatjet");
  hists.push_back("Reco_nfowardjet");
  hists.push_back("Reco_njets");
  hists.push_back("Reco_njets_10");
  hists.push_back("Reco_njets_20");
  hists.push_back("Reco_nmuon_nocut");
  hists.push_back("Reco_nmuon_tight");
  hists.push_back("SoftDropMass");
  hists.push_back("Truth_FowardJets_Eta");
  hists.push_back("Truth_FowardJets_Pt");
  hists.push_back("Truth_Jets_FromW_LowMass_Eta");
  hists.push_back("Truth_Jets_FromW_HighMass_Eta");
  hists.push_back("Truth_Jets_FromW_LowMass_Pt");
  hists.push_back("Truth_Lepton_FromN_Eta");
  hists.push_back("Truth_Lepton_FromN_Pt");
  hists.push_back("Truth_Lepton_FromN_Pt_lowpt");
  hists.push_back("Truth_Lepton_FromN_dR_closest_q");
  hists.push_back("Truth_Lepton_FromW_HighMass_Eta");
  hists.push_back("Truth_Lepton_FromW_HighMass_Pt");
  hists.push_back("Truth_Lepton_FromW_HighMass_Pt_lowpt");
  hists.push_back("Truth_Lepton_FromW_dRN");
  hists.push_back("Truth_Lepton_FromW_dR_lep2");
  hists.push_back("Truth_RecoMatched_FowardJets_Eta");
  hists.push_back("Truth_RecoMatched_FowardJets_Pt");
  hists.push_back("Truth_mjj");
  hists.push_back("tau21");

  hists.push_back("mm_eventcutflow_DoubleMuon");

  string indexname="STChannel_MM_Hists/Tchannel_index.html";
  ofstream ofile_tex;
  ofile_tex.open(indexname.c_str());
  ofile_tex.setf(ios::fixed,ios::floatfield);
  TString date="2017-10-02";

  TString analyzer="GetSignalEff";
  TString path="/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/"+analyzer+"/periodBtoH/"+ date +"/";

  TFile * fmc_t_100 = new TFile( (path+"/"+analyzer+"_HNMoriondLL_Tchannel_MupMup_100_cat_v8-0-7.root" ).Data());
  TFile * fmc_t_200 = new TFile( (path+"/"+analyzer+"_HNMoriondLL_Tchannel_MupMup_200_cat_v8-0-7.root" ).Data());
  TFile * fmc_t_500 = new TFile( (path+"/"+analyzer+"_HNMoriondLL_Tchannel_MupMup_500_cat_v8-0-7.root" ).Data());
  TFile * fmc_t_1100 = new TFile( (path+"/"+analyzer+"_HNMoriondLL_Tchannel_MupMup_1100_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_40 = new TFile( (path+"/"+analyzer+"_HNMupMup_40_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_50 = new TFile( (path+"/"+analyzer+"_HNMupMup_50_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_200 = new TFile( (path+"/"+analyzer+"_HNMupMup_200_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_500 = new TFile( (path+"/"+analyzer+"_HNMupMup_500_cat_v8-0-7.root" ).Data());
  TFile * fmc_s_1500 = new TFile( (path+"/"+analyzer+"_HNMupMup_1500_cat_v8-0-7.root" ).Data());
  for(unsigned int ihist= 0; ihist < hists.size() ; ihist++){
    TString htmlline= "<embed src=\""+hists[ihist]+".pdf\" width=\"800px\" height=\"700px\" />";

    //   ofile_tex << '<embed src="'+hists[ihist]+'.pdf" width="900px" height="1100px" />' << endl;
    cout << htmlline << endl;
    ofile_tex << htmlline << endl;

    for(unsigned int i=0; i < 2; i++){
      bool norm=true;
      if (i==0){
	norm=true;
      }
      if (i==1){
	norm=false;
      }
      
      TString dirname="Hists/";
      if(hists[ihist].Contains("cutflow")){
	dirname="";
      }
      TH1F* hT = MakePlot("GetSignalEff",date,"HNMoriondLL_Tchannel_MupMup_100_cat",dirname+hists[ihist], norm, fmc_t_100);
      TH1F* hT2 = MakePlot("GetSignalEff",date,"HNMoriondLL_Tchannel_MupMup_200_cat",dirname+hists[ihist],norm,fmc_t_200);
      TH1F* hT3 = MakePlot("GetSignalEff",date,"HNMoriondLL_Tchannel_MupMup_500_cat",dirname+hists[ihist],norm,fmc_t_500);
      TH1F* hT4= MakePlot("GetSignalEff",date,"HNMoriondLL_Tchannel_MupMup_1100_cat",dirname+hists[ihist],norm,fmc_t_1100);
      
      TH1F* hS = MakePlot("GetSignalEff",date,"HNMupMup_40_cat",dirname+hists[ihist],norm, fmc_s_40); 
      TH1F* hS2 = MakePlot("GetSignalEff",date,"HNMupMup_50_cat",dirname+hists[ihist],norm,fmc_s_50); 
      TH1F* hS3 = MakePlot("GetSignalEff",date,"HNMupMup_200_cat",dirname+hists[ihist],norm,fmc_s_200); 
      TH1F* hS4 = MakePlot("GetSignalEff",date,"HNMupMup_500_cat",dirname+hists[ihist],norm,fmc_s_500); 
      TH1F* hS5 = MakePlot("GetSignalEff",date,"HNMupMup_1500_cat",dirname+hists[ihist],norm,fmc_s_1500); 


      TString cantag= hists[ihist]+"TL";
      if(i==1) cantag=cantag+"nonorm";
      TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 
      
      
      TLegend *legend = new TLegend(.7, 0.7, .9, 0.95);
      legend->SetFillColor(10);
      legend->SetBorderSize(0);
      legend->SetTextSize(0.03);
      
      float maxT=hT->GetMaximum();
      if(hT2->GetMaximum() > maxT) maxT = hT2->GetMaximum();
      if(hT3->GetMaximum() > maxT) maxT = hT3->GetMaximum();
      if(hT4->GetMaximum() > maxT) maxT = hT4->GetMaximum();
      maxT=maxT*1.2;
      
      float maxS=hS->GetMaximum();
      if(hS2->GetMaximum() > maxS) maxS = hS2->GetMaximum();
      if(hS3->GetMaximum() > maxS) maxS = hS3->GetMaximum();
      if(hS4->GetMaximum() > maxS) maxS = hS4->GetMaximum();
      if(hS5->GetMaximum() > maxS) maxS = hS5->GetMaximum();
      maxS=maxS*1.2;
      


      hT->GetYaxis()->SetRangeUser(0.,maxT);
      hT->Draw("hist");
      hT2->Draw("histsame");
      hT3->Draw("histsame");
      hT4->Draw("histsame");
	
      legend->AddEntry(hT,"Tchann. MM m_{N}=100","l");
      legend->AddEntry(hT2,"Tchann. MM m_{N}=200","l");
      legend->AddEntry(hT3,"Tchann. MM m_{N}=500","l");
      legend->AddEntry(hT4,"Tchann. MM m_{N}=1100","l");
	
	
      legend->Draw();
      
      if (i==0){      
	TLatex label;
	label.SetTextSize(0.035);
	label.SetTextColor(2);
	label.SetTextFont(42);
	label.SetNDC();
	label.SetTextColor(1);
	label.DrawLatex(0.7,0.5,"Renormalised to 1.");
      }
      
      

      if(i==0){
	c1->SaveAs("STChannel_MM_Hists/"+hists[ihist]+".pdf(","pdf");
	TLegend *legendS = new TLegend(.7, 0.7, .9, 0.95);
	hS->GetYaxis()->SetRangeUser(0.,maxS);
	hS->Draw("hist");
	hS2->Draw("histsame");
	hS3->Draw("histsame");
	hS4->Draw("histsame");

	legendS->AddEntry(hS,"Schann. MM m_{N}=40","l");
	legendS->AddEntry(hS2,"Schann. MM m_{N}=50","l");
	legendS->AddEntry(hS3,"Schann. MM m_{N}=200","l");
	legendS->AddEntry(hS4,"Schann. MM m_{N}=500","l");
	legendS->AddEntry(hS5,"Schann. MM m_{N}=1500","l");


	legendS->Draw();
	c1->SaveAs("STChannel_MM_Hists/"+hists[ihist]+".pdf","pdf");
      }
      else {
	
	c1->SaveAs("STChannel_MM_Hists/"+hists[ihist]+".pdf","pdf");
	TLegend *legendS = new TLegend(.7, 0.7, .9, 0.95);
        hS->GetYaxis()->SetRangeUser(0.,maxS);
        hS->Draw("hist");
        hS2->Draw("histsame");
        hS3->Draw("histsame");
        hS4->Draw("histsame");

        legendS->AddEntry(hS,"Schann. MM m_{N}=40","l");
        legendS->AddEntry(hS2,"Schann. MM m_{N}=50","l");
        legendS->AddEntry(hS3,"Schann. MM m_{N}=200","l");
	legendS->AddEntry(hS4,"Schann. MM m_{N}=500","l");
	legendS->AddEntry(hS5,"Schann. MM m_{N}=1500","l");


        legendS->Draw();

	c1->SaveAs("STChannel_MM_Hists/"+hists[ihist]+".pdf)","pdf");

      }
	
    }
  }
  
  gSystem->Exec("scp STChannel_MM_Hists/* jalmond@lxplus074.cern.ch:~/www/SignalHN/");

}

TH1F* MakePlot(TString analyzer, TString date,TString sample, TString hist, bool renorm, TFile* fmc){

  TH1::SetDefaultSumw2();
  
  TH1F* h = (TH1F*)fmc->Get(hist);

  if(sample.Contains("_100_")) h->SetLineColor(kRed);
  if(sample.Contains("_40_")) h->SetLineColor(kRed);
  if(sample.Contains("_50_")) h->SetLineColor(kYellow);
  if(sample.Contains("_200_")) h->SetLineColor(kBlue);
  if(sample.Contains("_500_")) h->SetLineColor(kCyan);
  if(sample.Contains("_1100_")) h->SetLineColor(kOrange);
  if(sample.Contains("_1500_")) h->SetLineColor(kOrange);
 
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
