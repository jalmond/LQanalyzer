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

#include "TString.h"

void setTDRStyle();
bool CheckFile(TFile* f);
bool CheckHist(TH2* h);


void MakeFRRootFile(){
  
  TString path= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/";
  
  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;
  
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  TString outfile = "FakeRate0309.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  /// 
  std::vector<TString> fakes40;
  fakes40.push_back("20_pt_eta");
  fakes40.push_back("60_pt_eta");
  fakes40.push_back("40_pt_eta");
  fakes40.push_back("30_pt_eta");
  //fakes40.push_back("20_0bjet_pt_eta");
  //fakes40.push_back("60_0bjet_pt_eta");
  //fakes40.push_back("40_0bjet_pt_eta");
  //fakes40.push_back("30_0bjet_pt_eta");

  std::vector<TString> fakes;
  fakes.push_back("HNTight_");
  fakes.push_back("HNTight_relaxedip_");

  for(vector<TString>::iterator it2 = fakes40.begin(); it2!=fakes40.end(); ++it2){
    for(vector<TString>::iterator it = fakes.begin(); it!=fakes.end(); ++it){
      cout << *it2 << endl;
    if(!CheckFile(fdata))return;
    if(!CheckFile(fmc))return;

    TString denom ="LooseEl" + *it + *it2;
    TString num ="TightEl" + *it + *it2;
    TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

    cout << h_pt_num << " " << h_pt_denom << endl;
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);
    
    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    //eff_rate->Add(h_mcpt_num,-1.);
    //hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
    }
  }
  return;
  std::vector<TString> fakesopt;
  fakesopt.push_back("100_detiso");
  fakesopt.push_back("090_detiso");
  fakesopt.push_back("b090_e050_detiso");
  fakesopt.push_back("b100_e100");
  fakesopt.push_back("b090_e090");
  fakesopt.push_back("b090_e050");
  for(vector<TString>::iterator it2 = fakesopt.begin(); it2!=fakesopt.end(); ++it2){

    TString denom ="LooseOpt_pt_eta";
    TString num ="Tight_iso_dr3_"+ *it2 +"_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

    cout << num << endl;
    cout << h_pt_num << " " << h_pt_denom << endl;
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);

    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }


  bool runmedium = true;
  if(runmedium){
    TString denom ="LooseOpt_medium_pt_eta";
    TString num ="Tight_medium_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

    cout << num << endl;
    cout << h_pt_num << " " << h_pt_denom << endl;
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);

    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_medium"));
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone(("medium_denom"));
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }
  

  bool runtight=true;
  if(runtight){
    TString denom ="LooseOpt_tight_pt_eta";
    TString num ="Tight_tight_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

    cout << num << endl;
    cout << h_pt_num << " " << h_pt_denom << endl;
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);

    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_tight"));
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone(("tight_denom"));
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }


  
  bool runb=true;
  if(runb){
    TString denom ="LooseEl40_pt_1bjet";
    TString num ="TightEl40_pt_1bjet";
    TH1F* h_pt_num= (TH1F*)fdata->Get(num.Data());
    TH1F* h_pt_denom= (TH1F*)fdata->Get(denom.Data());

    cout << num << endl;
    cout << h_pt_num << " " << h_pt_denom << endl;
    TH1F* h_mcpt_num= (TH1F*)fmc->Get(num.Data());
    TH1F* h_mcpt_denom= (TH1F*)fmc->Get(denom.Data());

    TH1F* eff_rate = (TH1F*)h_pt_num->Clone(("FakeRate_40bjet"));
    TH1F* hratedenom = (TH1F*)h_pt_denom->Clone(("tight_denom"));
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }




  
}

  
bool CheckFile(TFile* f ){
    bool file_exist = true;
    if(!f){
      cout << "File " << f->GetName() << " does not exist. Exiting " << endl;
      file_exist = false;
    }
    
    return file_exist;
}

bool CheckHist(TH2* h ){
  bool hist_exist = true;
  if(!h){
    cout << "No histogram with name " << h->GetName() << endl;
    hist_exist= false;
  }
  return hist_exist;
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

