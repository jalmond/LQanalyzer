#include "TH2.h"
#include <iomanip>      // std::setprecision                                                                                                                                
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "TLine.h"
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

void MakeLeptonEffVsMassMuJet(){


  setTDRStyle();
  TString histname = "DiMuon_inclusivemm_eventcutflow_DoubleMuon";
  TString date="2017-12-11";

  TString analyzer="GetSignalEff";
  analyzer="HNDiLepton";
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
  //masslist[900] = "900";
  masslist[1000] = "1000";
  masslist[1200] = "1200";
  masslist[1300] = "1300";
  masslist[1400] = "1400";
  masslist[1500] = "1500";

  std::map<int, TString> masslistT;
  masslistT[300] = "300";
  masslistT[600] = "600";
  masslistT[800] = "800";
  masslistT[1000] = "1000";
  masslistT[1200] = "1200";
  masslistT[1500] = "1500";


  std::map<int,TString>::iterator mit;

  TString cantag= histname+"TL";

  int samplesize = masslist.size()+ masslistT.size();

  TCanvas* c1 = new TCanvas(cantag.Data(), cantag.Data(),800, 600); 


  //  c1->SetLogy();
  TH1F* h1 =  new TH1F("","",  samplesize, 0., float(samplesize));
  TH1F* h2 =  new TH1F("tmp2","tmp2",  samplesize, 0., float(samplesize));
  TH1F* h2a =  new TH1F("tmp22","tmp2a",  samplesize, 0., float(samplesize));
  TH1F* h2b =  new TH1F("tmp22b","tmp2b",  samplesize, 0., float(samplesize));
  TH1F* h2c =  new TH1F("tmp22c","tmp2c",  samplesize, 0., float(samplesize));

  TH1F* h3 =  new TH1F("tmp3","tmp3",  samplesize, 0., float(samplesize));
  TH1F* h4 =  new TH1F("tmp4","tmp4",  samplesize, 0., float(samplesize));
  TH1F* h5 =  new TH1F("tmp5","tmp5",  samplesize, 0., float(samplesize));
  TH1F* h6 =  new TH1F("tmp6","tmp6",  samplesize, 0., float(samplesize));
  TH1F* h7 =  new TH1F("tmp7","tmp7",  samplesize, 0., float(samplesize));

  TH1F* hT1 =  new TH1F("T","T",  samplesize, 0., float(samplesize));
  TH1F* hT2 =  new TH1F("Ttmp2","Ttmp2",  samplesize, 0., float(samplesize));
  TH1F* hT2a =  new TH1F("Ttmp2a","Ttmp2a",  samplesize, 0., float(samplesize));
  TH1F* hT3 =  new TH1F("Ttmp3","Ttmp3",  samplesize, 0., float(samplesize));
  TH1F* hT4 =  new TH1F("Ttmp4","Ttmp4",  samplesize, 0., float(samplesize));
  TH1F* hT5 =  new TH1F("Ttmp5","Ttmp5",  samplesize, 0., float(samplesize));
  TH1F* hT6 =  new TH1F("Ttmp6","Ttmp6",  samplesize, 0., float(samplesize));
  TH1F* hT7 =  new TH1F("Ttmp7","Ttmp7",  samplesize, 0., float(samplesize));
  
  int i=0;
  
  for( mit = masslist.begin(); mit !=masslist.end(); mit++,i++){
    h1->GetXaxis()->SetBinLabel(i+1, mit->second);
  }
  for( mit = masslistT.begin(); mit !=masslistT.end(); mit++,i++){
    h1->GetXaxis()->SetBinLabel(i+1, mit->second);
  }

  i=1;
  for( mit = masslist.begin(); mit !=masslist.end(); mit++,i++){

    TFile * fmc_ = new TFile( (path+"/"+analyzer+"_HNMuMu_"+mit->second+"_cat_v8-0-7.root" ).Data());
    
    TH1F* h_stat = (TH1F*)fmc_->Get("Hists/DiMuon_inclusive_StatBin");

    int nstat = h_stat->Integral();

    TString dirname="Hists/";
    if(histname.Contains("cutflow")){
      dirname="";
    }
    dirname="";
    bool norm=true;
    int rb=1;
    TH1F* hS1 = MakePlot(analyzer,date,"HNMuMu_"+mit->second+"_cat",dirname+histname,norm, fmc_,rb); 
    /*TH1F* hS2 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+"DiElectron_hn_looseipll_lowmass_flow",norm, fmc_,rb);
    TH1F* hS3 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+"DiElectron_hnv3ll_lowmass_flow",norm, fmc_,rb);
    TH1F* hS4 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+"DiElectron_mvatightll_lowmass_flow",norm, fmc_,rb);
    TH1F* hS5 = MakePlot(analyzer,date,"HNEE_"+mit->second+"_cat",dirname+"DiElectron_pogtight_ccll_lowmass_flow",norm, fmc_,rb);
    */

    float n_nocut = hS1->GetBinContent(1);
    float n_lep= hS1->GetBinContent(11); 
    float n_dijet= hS1->GetBinContent(12);
    float n_jet= hS1->GetBinContent(13);
    float n_jet1= hS1->GetBinContent(14);
    float n_jet2= hS1->GetBinContent(15);
    float n_jet3= hS1->GetBinContent(16);


    h1->SetBinContent(i,n_lep/n_nocut);
    float jet = 0.;
    if(i < 6)jet = n_jet1 + n_jet2;
    else jet = n_jet1 + n_jet3;

    float lm = 0.;
    if(i < 6)lm = hS1->GetBinContent(19) + hS1->GetBinContent(20);
    else lm = hS1->GetBinContent(19) ;
    float hm = 0.;
    if(i < 6)hm = hS1->GetBinContent(21);
    else hm = hS1->GetBinContent(21) + hS1->GetBinContent(22);

    h2a->SetBinContent(i,n_jet1/n_nocut);
    h2->SetBinContent(i,jet/n_nocut);
    h2b->SetBinContent(i,n_jet2/n_nocut);
    h2c->SetBinContent(i,n_jet3/n_nocut);

    h3->SetBinContent(i,jet/n_dijet);
    
    
    float err1 = hS1->GetBinError(11)/n_nocut;
    if(err1 < 0.001) err1=0.001;
    float err2 = hS1->GetBinError(13)/n_nocut;
    if(err2 < 0.001) err2=0.001;
    float err3 = sqrt(hS1->GetBinError(19)* hS1->GetBinError(19) +  hS1->GetBinError(20)* hS1->GetBinError(20))/n_nocut;
    if(err3 < 0.001) err3=0.001;
    float err4 = sqrt(hS1->GetBinError(21)* hS1->GetBinError(21) +  hS1->GetBinError(22)* hS1->GetBinError(22))/n_nocut;
    if(err4 < 0.001) err4=0.001;
    cout <<     std::setprecision (2) << mit->second << " & " << nstat<< " & "  << n_lep/n_nocut << " $\\pm$ " <<  err1 << " & "  ;
    cout  <<     std::setprecision (2) << hS1->GetBinContent(13)/n_nocut  << " $\\pm$ " << err2;
    cout  <<     std::setprecision (2) << " & " << (hS1->GetBinContent(19)+hS1->GetBinContent(20))/n_nocut ;
    cout  <<     std::setprecision (2) << " $\\pm$ " << err3;
    cout  <<     std::setprecision (2) <<" & " << (hS1->GetBinContent(21)+hS1->GetBinContent(22))/n_nocut <<   " $\\pm$ " <<  err3  << "\\\\" << endl;
    
    
  }
  
  for( mit = masslistT.begin(); mit !=masslistT.end(); mit++,i++){

    TFile * fmc_ = new TFile( (path+"/"+analyzer+"_HNDilepton_MuMu_Tchannel_M"+mit->second+"_cat_v8-0-7.root" ).Data());

    TH1F* h_stat = (TH1F*)fmc_->Get("Hists/DiMuon_inclusive_StatBin");
    int nstat = h_stat->Integral();


    TString dirname="Hists/";
    if(histname.Contains("cutflow")){
      dirname="";
    }
    dirname="";
    bool norm=true;
    int rb=1;
    TH1F* hS1 = MakePlot(analyzer,date,"_HNDilepton_MuMu_Tchannel_M"+mit->second+"_cat",dirname+histname,norm, fmc_,rb);

    float n_nocut = hS1->GetBinContent(1);
    float n_lep= hS1->GetBinContent(11);
    float n_dijet= hS1->GetBinContent(12);
    float n_jet= hS1->GetBinContent(13);
    float n_jet1= hS1->GetBinContent(14);
    float n_jet2= hS1->GetBinContent(15);
    float n_jet3= hS1->GetBinContent(16);
    h1->SetBinContent(i,n_lep/n_nocut);
    float jet = 0.;
    if(i < 6)jet = n_jet1 + n_jet2;
    else jet = n_jet1 + n_jet3;

    float lm = 0.;
    if(i < 6)lm = hS1->GetBinContent(19) + hS1->GetBinContent(20);
    else lm = hS1->GetBinContent(19) ;
    float hm = 0.;
    if(i < 6)hm = hS1->GetBinContent(21);
    else hm = hS1->GetBinContent(21) + hS1->GetBinContent(22);


    cout << mit->second << " " << n_lep/n_nocut <<" " <<  n_lep << " " << n_nocut << endl;
    h2a->SetBinContent(i,n_jet1/n_nocut);
    h2->SetBinContent(i,jet/n_nocut);
    h2b->SetBinContent(i,n_jet2/n_nocut);
    h2c->SetBinContent(i,n_jet3/n_nocut);


    h3->SetBinContent(i,jet/n_dijet);


    float err1 = hS1->GetBinError(11)/n_nocut;
    if(err1 < 0.001) err1=0.001;
    float err2 = hS1->GetBinError(13)/n_nocut;
    if(err2 < 0.001) err2=0.001;
    float err3 = sqrt(hS1->GetBinError(19)* hS1->GetBinError(19) +  hS1->GetBinError(20)* hS1->GetBinError(20))/n_nocut;
    if(err3 < 0.001) err3=0.001;
    float err4 = sqrt(hS1->GetBinError(21)* hS1->GetBinError(21) +  hS1->GetBinError(22)* hS1->GetBinError(22))/n_nocut;
    if(err4 < 0.001) err4=0.001;
    cout <<     std::setprecision (2) << mit->second << " & " << nstat<< " & "  << n_lep/n_nocut << " $\\pm$ " <<  err1 << " & "  ;
    cout  <<     std::setprecision (2) << hS1->GetBinContent(13)/n_nocut  << " $\\pm$ " << err2;
    cout  <<     std::setprecision (2) << " & " << (hS1->GetBinContent(19)+hS1->GetBinContent(20))/n_nocut ;
    cout  <<     std::setprecision (2) << " $\\pm$ " << err3;
    cout  <<     std::setprecision (2) <<" & " << (hS1->GetBinContent(21)+hS1->GetBinContent(22))/n_nocut <<   " $\\pm$ " <<  err3  << "\\\\" << endl;




  }

  h1->SetLineStyle(23);
  h1->SetLineWidth(2.0);
  h2->SetLineStyle(24);
  h2->SetLineWidth(2.0);
  h2a->SetLineStyle(2);
  h2a->SetLineWidth(2.0);
  h2a->SetLineStyle(2);
  h2b->SetLineStyle(2);
  h2c->SetLineStyle(2);

  hT1->SetLineStyle(23);
  hT1->SetLineWidth(2.0);
  hT2->SetLineStyle(24);
  hT2->SetLineWidth(2.0);

  h2a->SetLineColor(kGreen);
  h2b->SetLineColor(kOrange);
  h2c->SetLineColor(kBlue-2);


  h1->GetYaxis()->SetTitle("Selection eff. for #mu#mu channel.");
  h1->GetXaxis()->SetTitle("m_{N} (GeV)");
  h1->GetYaxis()->SetRangeUser(0.001,1.);
  h1->SetLineColor(kRed);

  h3->GetXaxis()->SetLabelSize(0.); ///
  h3->GetXaxis()->SetTitle("");
  
  h3->GetYaxis()->SetTitleSize(0.02); 

  h2->SetLineColor(kCyan+4);

  
  hT1->SetLineColor(kRed);
  hT2->SetLineColor(kCyan+4);

  hT2a->SetLineColor(kGreen);


  h1->Draw("l");
  h2->Draw("lsame");
  h2a->Draw("lsame");
  h2b->Draw("lsame");
  h2c->Draw("lsame");

  //hT1->Draw("lsame");
  //hT2->Draw("lsame");
  //hT2a->Draw("lsame");
  TLatex label;
  label.SetTextSize(0.025);
  label.SetTextColor(2);
  label.SetTextFont(42);
  label.SetNDC();
  label.SetTextColor(1);
  label.DrawLatex(0.2 ,0.24,"S-channel");
  label.DrawLatex(0.8 ,0.24,"T-channel");

  TLegend *legend = new TLegend(.2, 0.5, .5, 0.7);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.03);
  legend->AddEntry(h1,"SS2l","l");
  legend->AddEntry(h2a,"SS2l; >1 j_{AK4}","l");
  legend->AddEntry(h2b,"SS2l; 1 j_{AK4}","l");
  legend->AddEntry(h2c,"SS2l; > 0 j_{AK8}","l");
  legend->AddEntry(h2,"SS2l; SR1+SR2","l");



  TLine *devz = new TLine(h1->GetBinLowEdge(23),0,h1->GetBinLowEdge(23),1.  );
  devz->SetLineWidth(1.5);
  devz->SetLineStyle(1);
  devz->Draw("SAME");

  legend->Draw();


  // How large fraction that will be taken up by the data/MC ratio part
  double FIGURE2_RATIO = 0.25;
  double SUBFIGURE_MARGIN = 0.;
  c1->SetTopMargin(FIGURE2_RATIO);
  //TPad *p = new TPad( "p_test", "", 0, 0, 1, 1.0 - SUBFIGURE_MARGIN, 0, 0, 0);  // create new pad, fullsize to have equal font-sizes in both plots
  TPad *p = new TPad( "p_test", "", 0, 0, 1, 1.0 - SUBFIGURE_MARGIN, 0, 0, 0);  // create new pad, fullsize to have equal font-sizes in both plots
  p->SetBottomMargin(1-FIGURE2_RATIO);   // top-boundary (should be 1 - thePad->GetBottomMargin() )
  p->SetFillStyle(0);     // needs to be transparent
  p->Draw();
  p->cd();
  p->SetTicks(0,1);
  
  h3->GetYaxis()->SetNdivisions(5);

  //h3->SetMaximum(3.0);
  //h3->SetMinimum(0.0);
  //h3->GetXaxis()->SetTitle("m_{N} (GeV)");
  //  h3->SetTitleFontSize(0.3);
  h3->GetYaxis()->SetTitleSize(2.);
  h3->GetYaxis()->SetTitle("Ratio");
  //h3->SetFillColor(kOrange);
  h3->SetLineWidth(2.);
  h3->SetLineStyle(2);
  h3->SetLineColor(kRed);
  h3->Draw("l");
  


  TLegend *legend2 = new TLegend(.5, 0.8, .7, 0.9);
  legend2->SetFillColor(10);
  legend2->SetBorderSize(0);
  legend2->SetTextSize(0.03);
  legend2->AddEntry(h3,"#frac{SS2l; SR1+SR2 }{SS2l; >1 j_{AK4}}","l");
  legend2->Draw();

  c1->SaveAs(histname+"_eff.pdf");
    
  gSystem->Exec("scp "+histname+"_eff.pdf jalmond@lxplus022.cern.ch:~/www/SignalHN/");
  
  cout << "~/www/SignalHN/"+histname+"_eff.pdf" << endl;
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

  tdrStyle->SetLineStyle(20);

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
  tdrStyle->SetTitleFontSize(0.03);
  // tdrStyle->SetTitleH(0); // Set the height of the title box                                                                                                                                          
  // tdrStyle->SetTitleW(0); // Set the width of the title box                                                                                                                                           
  // tdrStyle->SetTitleX(0); // Set the position of the title box                                                                                                                                        
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box                                                                                                                                    
  // tdrStyle->SetTitleStyle(Style_t style = 1001);                                                                                                                                                      
  // tdrStyle->SetTitleBorderSize(2);                                                                                                                                                                    

  // For the axis titles:                                                                                                                                                                                

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.04, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?                                                                                                                       
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);                                                                                                                                                       
  tdrStyle->SetTitleXOffset(0.9);  tdrStyle->SetTitleYOffset(1.2);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset                                                                                                                                

   tdrStyle->  SetFillColorAlpha(45,0.35);

  // For the axis labels:                                                                                                                                                                                

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.04, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?                                                                                                                       
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);                                                                                                                                                       
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.2);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset                                                                                                                                

  // For the axis labels:                                                                                                                                                                                

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.04, "XYZ");

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
