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

void FakeRatePlots_ewksub(){
  
  TString path= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/";


  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  vector<TString> plotname;
  plotname.push_back("_pt");
  
  
  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    
    vector<TString> hist_ptcut;
    hist_ptcut.push_back("40");
    
    for(vector<TString>::iterator it2 = hist_ptcut.begin(); it2!=hist_ptcut.end(); ++it2){
      int rebin=1;
      
      TH1F* h_pt_dxy_05_num= (TH1F*)fdata->Get(("Tight_dxy05_El"+ *it2+ *it ).Data());
      TH1F* h_pt_dxy_10_num= (TH1F*)fdata->Get(("Tight_dxy10_El"+ *it2+ *it ).Data());
      TH1F* h_pt_dxy_15_num= (TH1F*)fdata->Get(("Tight_dxy15_El"+ *it2+ *it ).Data());
      TH1F* h_pt_dxy_20_num= (TH1F*)fdata->Get(("Tight_dxy20_El"+ *it2+ *it ).Data());
      TH1F* h_pt_dxy_25_num= (TH1F*)fdata->Get(("Tight_dxy25_El"+ *it2+ *it ).Data());
      TH1F* h_pt_dxy_30_num= (TH1F*)fdata->Get(("Tight_dxy30_El"+ *it2+ *it ).Data());

      TH1F* h_pt_denom= (TH1F*)fdata->Get(("LooseEl"+ *it2+*it).Data());
      
      TH1F* h_mcpt_dxy_05_num= (TH1F*)fmc->Get(("Tight_dxy05_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_dxy_10_num= (TH1F*)fmc->Get(("Tight_dxy10_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_dxy_15_num= (TH1F*)fmc->Get(("Tight_dxy15_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_dxy_20_num= (TH1F*)fmc->Get(("Tight_dxy20_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_dxy_25_num= (TH1F*)fmc->Get(("Tight_dxy25_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_dxy_30_num= (TH1F*)fmc->Get(("Tight_dxy30_El"+ *it2+ *it ).Data());
      TH1F* h_mcpt_denom= (TH1F*)fmc->Get(("LooseEl"+*it2 +*it).Data());

      if(it->Contains("eta")){
	if(!it->Contains("pt") && !it->Contains("binned"))rebin=2;
      }
      
      cout << h_mcpt_dxy_05_num << " " << h_mcpt_denom << " " << h_pt_denom << " " << h_pt_dxy_25_num << endl;
      
      h_pt_dxy_05_num->Add(h_mcpt_dxy_05_num,-1);
      h_pt_dxy_10_num->Add(h_mcpt_dxy_10_num,-1);
      h_pt_dxy_15_num->Add(h_mcpt_dxy_15_num,-1);
      h_pt_dxy_20_num->Add(h_mcpt_dxy_20_num,-1);
      h_pt_dxy_25_num->Add(h_mcpt_dxy_25_num,-1);
      h_pt_dxy_30_num->Add(h_mcpt_dxy_30_num,-1);
      
      h_pt_denom->Add(h_mcpt_denom, -1.);
      
      h_pt_dxy_05_num->Divide(h_pt_denom);
      h_pt_dxy_10_num->Divide(h_pt_denom);
      h_pt_dxy_15_num->Divide(h_pt_denom);
      h_pt_dxy_20_num->Divide(h_pt_denom);
      h_pt_dxy_25_num->Divide(h_pt_denom);
      h_pt_dxy_30_num->Divide(h_pt_denom);
      

      cout << "\n -----------:  h_pt_dxy_05_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_05_num->GetNbinsX()+1; ibin++){
	cout << h_pt_dxy_05_num->GetBinContent(ibin) << " " <<  h_pt_dxy_05_num->GetBinError(ibin) << endl;
      }
      
      cout << "\n -----------:  h_pt_dxy_10_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_10_num->GetNbinsX()+1; ibin++){
        cout << h_pt_dxy_10_num->GetBinContent(ibin) << " " <<  h_pt_dxy_10_num->GetBinError(ibin) << endl;
      }

      cout << "\n -----------:  h_pt_dxy_15_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_15_num->GetNbinsX()+1; ibin++){
        cout << h_pt_dxy_15_num->GetBinContent(ibin) << " " <<  h_pt_dxy_15_num->GetBinError(ibin) << endl;
      }

      cout << "\n -----------:  h_pt_dxy_20_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_20_num->GetNbinsX()+1; ibin++){
        cout << h_pt_dxy_20_num->GetBinContent(ibin) << " " <<  h_pt_dxy_20_num->GetBinError(ibin) << endl;
      }

      cout << "\n -----------:  h_pt_dxy_25_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_25_num->GetNbinsX()+1; ibin++){
        cout << h_pt_dxy_25_num->GetBinContent(ibin) << " " <<  h_pt_dxy_25_num->GetBinError(ibin) << endl;
      }

      cout << "\n -----------:  h_pt_dxy_30_num" << endl;
      for(unsigned int ibin = 1; ibin < h_pt_dxy_30_num->GetNbinsX()+1; ibin++){
        cout << h_pt_dxy_30_num->GetBinContent(ibin) << " " <<  h_pt_dxy_30_num->GetBinError(ibin) << endl;
      }

      
      
    }
  }
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

