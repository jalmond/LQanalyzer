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
    
  TString outfile = "FakeRate2015.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();

  /// 
  std::vector<TString> type;
  type.push_back("HNTight_");
  type.push_back("HNTight_relaxedip_");
    

  std::vector<TString> fakes40;
  fakes40.push_back("20_pt_eta");
  fakes40.push_back("30_pt_eta");
  fakes40.push_back("60_pt_eta");
  fakes40.push_back("40_pt_eta");
  fakes40.push_back("20_ht_eta");
  fakes40.push_back("30_ht_eta");
  fakes40.push_back("60_ht_eta");
  fakes40.push_back("40_ht_eta");

  fakes40.push_back("20_bjet_pt_eta");
  fakes40.push_back("30_bjet_pt_eta");
  fakes40.push_back("60_bjet_pt_eta");
  fakes40.push_back("40_bjet_pt_eta");
  fakes40.push_back("20_0bjet_pt_eta");
  fakes40.push_back("30_0bjet_pt_eta");
  fakes40.push_back("60_0bjet_pt_eta");
  fakes40.push_back("40_0bjet_pt_eta");
  fakes40.push_back("20_pt_eta_ht1");
  fakes40.push_back("20_pt_eta_ht3");
  fakes40.push_back("30_pt_eta_ht1");
  fakes40.push_back("30_pt_eta_ht3");
  fakes40.push_back("40_pt_eta_ht1");
  fakes40.push_back("40_pt_eta_ht3");
  fakes40.push_back("60_pt_eta_ht1");
  fakes40.push_back("60_pt_eta_ht3");

  for(vector<TString>::iterator it = type.begin(); it!=type.end(); ++it){
    for(vector<TString>::iterator it2 = fakes40.begin(); it2!=fakes40.end(); ++it2){
      cout << *it << endl;
      cout << *it2 << endl;
      if(!CheckFile(fdata))return;
      if(!CheckFile(fmc))return;
      
      TString denom ="LooseEl" + *it+ *it2;
      TString num ="TightEl" + *it + *it2;
      cout  <<num << endl;
      TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
      TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

      cout << h_pt_num << " " << h_pt_denom << endl;
      CheckHist(h_pt_denom);
      CheckHist(h_pt_num);
      TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
      TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
      CheckHist(h_mcpt_denom);
      CheckHist(h_mcpt_num);
      
      TString tag = *it + *it2;
      TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + tag).Data());
      TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((tag +"_denom").Data());
      eff_rate->Add(h_mcpt_num,-1.);
      hratedenom->Add(h_mcpt_denom, -1.);
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      eff_rate->Write();
    }
  }
  bool cb= true;
  if(cb){
    
    std::vector<TString> fakescb;
    fakescb.push_back("20_ht_eta");
    fakescb.push_back("30_ht_eta");
    fakescb.push_back("60_ht_eta");
    fakescb.push_back("40_ht_eta");
    fakescb.push_back("20_pt_eta");
    fakescb.push_back("30_pt_eta");
    fakescb.push_back("60_pt_eta");
    fakescb.push_back("40_pt_eta");

    for(vector<TString>::iterator it = type.begin(); it!=type.end(); ++it){
      for(vector<TString>::iterator it2 = fakescb.begin(); it2!=fakescb.end(); ++it2){
	
	if(!CheckFile(fdata))return;
	if(!CheckFile(fmc))return;
	
	TString denom ="LooseEl_cb" + *it+ *it2;
	TString num ="TightEl_cb" + *it + *it2;
	TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
	TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
	
	cout << h_pt_num << " " << h_pt_denom << endl;
	CheckHist(h_pt_denom);
	CheckHist(h_pt_num);
	TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
	TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
	CheckHist(h_mcpt_denom);
	CheckHist(h_mcpt_num);
	
	TString tag = *it + *it2 +"_cb";
	TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + tag).Data());
	TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((tag +"_denom").Data());
	
	eff_rate->Add(h_mcpt_num,-1.);
	hratedenom->Add(h_mcpt_denom, -1.);
	eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
	eff_rate->Write();
      }
      
    }
  }
  
  
  bool nocb=true;
  if(nocb){
    
    std::vector<TString> fakescb;
    fakescb.push_back("20_ht_eta");
    fakescb.push_back("30_ht_eta");
    fakescb.push_back("60_ht_eta");
    fakescb.push_back("40_ht_eta");
    fakescb.push_back("20_pt_eta");
    fakescb.push_back("30_pt_eta");
    fakescb.push_back("60_pt_eta");
    fakescb.push_back("40_pt_eta");
    fakescb.push_back("20_pt_eta_ht1");
    fakescb.push_back("20_pt_eta_ht3");
    fakescb.push_back("30_pt_eta_ht1");
    fakescb.push_back("30_pt_eta_ht3");
    fakescb.push_back("40_pt_eta_ht1");
    fakescb.push_back("40_pt_eta_ht3");
    fakescb.push_back("60_pt_eta_ht1");
    fakescb.push_back("60_pt_eta_ht3");
    
    fakescb.push_back("20_bjet_pt_eta_ht1");
    fakescb.push_back("20_bjet_pt_eta_ht3");
    fakescb.push_back("30_bjet_pt_eta_ht1");
    fakescb.push_back("30_bjet_pt_eta_ht3");
    fakescb.push_back("40_bjet_pt_eta_ht1");
    fakescb.push_back("40_bjet_pt_eta_ht3");
    fakescb.push_back("60_bjet_pt_eta_ht1");
    fakescb.push_back("60_bjet_pt_eta_ht3");
    fakescb.push_back("20_0bjet_pt_eta_ht1");
    fakescb.push_back("20_0bjet_pt_eta_ht3");
    fakescb.push_back("30_0bjet_pt_eta_ht1");
    fakescb.push_back("30_0bjet_pt_eta_ht3");
    fakescb.push_back("40_0bjet_pt_eta_ht1");
    fakescb.push_back("40_0bjet_pt_eta_ht3");
    fakescb.push_back("60_0bjet_pt_eta_ht1");
    fakescb.push_back("60_0bjet_pt_eta_ht3");

    fakescb.push_back("20_bjet_pt_eta");
    fakescb.push_back("30_bjet_pt_eta");
    fakescb.push_back("60_bjet_pt_eta");
    fakescb.push_back("40_bjet_pt_eta");
    fakescb.push_back("20_0bjet_pt_eta");
    fakescb.push_back("30_0bjet_pt_eta");
    fakescb.push_back("60_0bjet_pt_eta");
    fakescb.push_back("40_0bjet_pt_eta");    
    
    for(vector<TString>::iterator it = type.begin(); it!=type.end(); ++it){
      for(vector<TString>::iterator it2 = fakescb.begin(); it2!=fakescb.end(); ++it2){
	
	if(!CheckFile(fdata))return;
	if(!CheckFile(fmc))return;
	
	TString denom ="LooseEl_nocb" + *it+ *it2;
	TString num ="TightEl_nocb" + *it + *it2;
	TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
	TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
	cout << denom << " " << num << endl;
	cout << h_pt_num << " " << h_pt_denom << endl;
	CheckHist(h_pt_denom);
	CheckHist(h_pt_num);
	TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
	TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
	CheckHist(h_mcpt_denom);
	CheckHist(h_mcpt_num);
	
	TString tag = *it + *it2 + "_nocb";
	TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + tag).Data());
	TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((tag +"_denom").Data());
	eff_rate->Add(h_mcpt_num,-1.);
	hratedenom->Add(h_mcpt_denom, -1.);
	eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
	eff_rate->Write();
      }
      
    }
  }
  
  
  bool extra=true;
  if(extra){
  
    std::vector<TString> type2;
    type2.push_back("HNTight_iso05");
    type2.push_back("HNTight_iso07");
    type2.push_back("susy_pog");
    type2.push_back("medium_pog");
    type2.push_back("tight_pog");
    
    type2.push_back("electronTightColl_dr03_b150_e150");
    type2.push_back("electronTightColl_dr03_b150_e125"); 
    type2.push_back("electronTightColl_dr03_b150_e10");  
    type2.push_back("electronTightColl_dr03_b150_e09");  
    type2.push_back("electronTightColl_dr03_b150_e08");  
    type2.push_back("electronTightColl_dr03_b150_e07");  
    type2.push_back("electronTightColl_dr03_b150_e06");  
    type2.push_back("electronTightColl_dr03_b150_e05");  
    
    type2.push_back("electronTightColl_dr03_b125_e125"); 
    type2.push_back("electronTightColl_dr03_b125_e10");  
    type2.push_back("electronTightColl_dr03_b125_e09");  
    type2.push_back("electronTightColl_dr03_b125_e08");  
    type2.push_back("electronTightColl_dr03_b125_e07");  
    type2.push_back("electronTightColl_dr03_b125_e06");  
    type2.push_back("electronTightColl_dr03_b125_e05");  
    
    type2.push_back("electronTightColl_dr03_b10_e125");
    type2.push_back("electronTightColl_dr03_b10_e10"); 
    type2.push_back("electronTightColl_dr03_b10_e09"); 
    type2.push_back("electronTightColl_dr03_b10_e08"); 
    type2.push_back("electronTightColl_dr03_b10_e07"); 
    type2.push_back("electronTightColl_dr03_b10_e06"); 
    type2.push_back("electronTightColl_dr03_b10_e05"); 
    
    type2.push_back("electronTightColl_dr03_b09_e125");
    type2.push_back("electronTightColl_dr03_b09_e10"); 
    type2.push_back("electronTightColl_dr03_b09_e09"); 
    type2.push_back("electronTightColl_dr03_b09_e08"); 
    type2.push_back("electronTightColl_dr03_b09_e07"); 
    type2.push_back("electronTightColl_dr03_b09_e06"); 
    type2.push_back("electronTightColl_dr03_b09_e05"); 
    
    type2.push_back("electronTightColl_dr03_b08_e125");
    type2.push_back("electronTightColl_dr03_b08_e10"); 
    type2.push_back("electronTightColl_dr03_b08_e09"); 
    type2.push_back("electronTightColl_dr03_b08_e08"); 
    type2.push_back("electronTightColl_dr03_b08_e07"); 
    type2.push_back("electronTightColl_dr03_b08_e06"); 
    type2.push_back("electronTightColl_dr03_b08_e05"); 
    
    type2.push_back("electronTightColl_dr03_b07_e125");
    type2.push_back("electronTightColl_dr03_b07_e10"); 
    type2.push_back("electronTightColl_dr03_b07_e09"); 
    type2.push_back("electronTightColl_dr03_b07_e08"); 
    type2.push_back("electronTightColl_dr03_b07_e07"); 
    type2.push_back("electronTightColl_dr03_b07_e06"); 
    type2.push_back("electronTightColl_dr03_b07_e05"); 
    
    type2.push_back("electronTightColl_dr03_b06_e125");
    type2.push_back("electronTightColl_dr03_b06_e10"); 
    type2.push_back("electronTightColl_dr03_b06_e09"); 
    type2.push_back("electronTightColl_dr03_b06_e08"); 
    type2.push_back("electronTightColl_dr03_b06_e07"); 
    type2.push_back("electronTightColl_dr03_b06_e06"); 
    type2.push_back("electronTightColl_dr03_b06_e05"); 
    
    type2.push_back("electronTightColl_dr03_b05_e125");
    type2.push_back("electronTightColl_dr03_b05_e10"); 
    type2.push_back("electronTightColl_dr03_b05_e09"); 
    type2.push_back("electronTightColl_dr03_b05_e08"); 
    type2.push_back("electronTightColl_dr03_b05_e07"); 
    type2.push_back("electronTightColl_dr03_b05_e06"); 
    type2.push_back("electronTightColl_dr03_b05_e05"); 
    
    
    std::vector<TString> fakes40;
    fakes40.push_back("_40_pt_eta");
    
    for(vector<TString>::iterator it = type2.begin(); it!=type2.end(); ++it){
      for(vector<TString>::iterator it2 = fakes40.begin(); it2!=fakes40.end(); ++it2){
	cout << *it << endl;
	cout << *it2 << endl;
	if(!CheckFile(fdata))return;
	if(!CheckFile(fmc))return;

	TString denom ="LooseEl" + *it+ *it2;
	TString num ="TightEl" + *it + *it2;
	cout  <<num << endl;
	TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
	TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
	
	cout << h_pt_num << " " << h_pt_denom << endl;
	CheckHist(h_pt_denom);
	CheckHist(h_pt_num);
	TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
	TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
	cout << h_mcpt_denom << " " << h_mcpt_num << endl;

	CheckHist(h_mcpt_denom);
	CheckHist(h_mcpt_num);

	TString tag = *it + *it2;
	TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + tag).Data());
	cout << eff_rate << endl;
	TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((tag +"_denom").Data());
	cout << h_mcpt_denom << " " << h_mcpt_num << endl;
	eff_rate->Add(h_mcpt_num,-1.);
	hratedenom->Add(h_mcpt_denom, -1.);
	eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
	eff_rate->Write();
      }
    }
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

