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
  plotname.push_back("_nbjet");
  //plotname.push_back("_njets");
  //plotname.push_back("_ptawayjet");
  //plotname.push_back("_ht");
  //plotname.push_back("_ht_noawayjet");
  //plotname.push_back("_ht_dijet");
  
  //  plotname.push_back("_eta");
  plotname.push_back("_ptbarrel");
  //plotname.push_back("_ptendcap");
  //plotname.push_back("_nvertices");

  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    
    vector<TString> hist_ptcut;
    hist_ptcut.push_back("60");
    hist_ptcut.push_back("40");
    hist_ptcut.push_back("30");
    
    for(vector<TString>::iterator it2 = hist_ptcut.begin(); it2!=hist_ptcut.end(); ++it2){
      int rebin=1;
      
      TH1F* h_pt_num= (TH1F*)fdata->Get(("TightEl"+ *it2+ *it ).Data());
      TH1F* h_pt_denom= (TH1F*)fdata->Get(("LooseEl"+ *it2+*it).Data());
      
      TH1F* h_mcpt_num= (TH1F*)fmc->Get(("TightEl"+*it2+ *it ).Data());
      TH1F* h_mcpt_denom= (TH1F*)fmc->Get(("LooseEl"+*it2 +*it).Data());

      if(it->Contains("eta")){
	if(!it->Contains("pt") && !it->Contains("binned"))rebin=2;
      }

      h_pt_num->Rebin(rebin);
      h_pt_denom->Rebin(rebin);
      h_mcpt_num->Rebin(rebin);
      h_mcpt_denom->Rebin(rebin);
      
      TH1F* h_pt_num_clone = (TH1F*)h_pt_num->Clone("");
      h_pt_num_clone->Add(h_mcpt_num,-1);

      TH1F* h_pt_num_up_clone = (TH1F*)h_pt_num->Clone("up");
      TH1F* h_pt_num_down_clone = (TH1F*)h_pt_num->Clone("down");
      h_pt_num_up_clone->Add(h_mcpt_num,-1.15);
      h_pt_num_down_clone->Add(h_mcpt_num,-0.85);

      TH1F* h_pt_denom_clone = (TH1F*)h_pt_denom->Clone("");
      TH1F* h_errorhist = (TH1F*)h_pt_denom->Clone("error");
      h_pt_denom_clone->Add(h_mcpt_denom,-1);
      
      
      TH1F* h_pt_denom_up_clone = (TH1F*)h_pt_denom->Clone("up");
      TH1F* h_pt_denom_down_clone = (TH1F*)h_pt_denom->Clone("down");
      
      h_pt_denom_up_clone->Add(h_mcpt_denom,-1.15);
      h_pt_denom_down_clone->Add(h_mcpt_denom,-0.85);

      cout << "Number of events in numerator (data) = " << h_pt_num->Integral() << endl;
      cout << "Number of events in denominator (data) = " << h_pt_denom->Integral() << endl;
      
      cout << "Number of events in numerator (mc) = " << h_mcpt_num->Integral() << endl;
      cout << "Number of events in denominator (mc) = " << h_mcpt_denom->Integral() << endl;
      
      cout << "Number of events in numerator (data-mc) = " << h_pt_num_clone->Integral() << endl;
      cout << "Number of events in denominator (data-mc) = " << h_pt_denom_clone->Integral() << endl;
      
      h_pt_num->Divide(h_pt_denom);
      h_pt_num_clone->Divide(h_pt_denom_clone);

      h_pt_num_up_clone->Divide(h_pt_denom_up_clone);
      h_pt_num_down_clone->Divide(h_pt_denom_down_clone);
      
      h_pt_num->SetMarkerStyle(20);
      h_pt_num->SetMarkerColor(kRed);
      h_pt_num->SetLineColor(kRed);
      
      h_pt_num_clone->SetMarkerStyle(21);
      h_pt_num_clone->SetMarkerColor(kBlue);
      h_pt_num_clone->SetLineColor(kBlue);
      
      
      
      for(unsigned int ibin = 1; ibin < h_pt_num_clone->GetNbinsX()+1; ibin++){
	float binerror = h_pt_num_clone->GetBinError(ibin);
	
	float error_up = h_pt_num_clone->GetBinContent(ibin)  -  h_pt_num_down_clone->GetBinContent(ibin) ;
	error_up = sqrt( error_up*error_up + binerror*binerror);
	
	float error_down = h_pt_num_clone->GetBinContent(ibin)  -  h_pt_num_up_clone->GetBinContent(ibin) ;
        error_down = sqrt( error_down*error_down + binerror*binerror);
	cout << h_pt_num_clone->GetBinContent(ibin)  << " " << error_up << " " << error_down << endl;
	
	h_errorhist->SetBinContent(ibin,  (h_pt_num_clone->GetBinContent(ibin)  + error_up - error_down));
	h_errorhist->SetBinError( ibin, (error_down + error_up) / 2.);
      }
      
      cout << "\n -----------" << endl;
      for(unsigned int ibin = 1; ibin <h_errorhist->GetNbinsX()+1; ibin++){
	cout << h_errorhist->GetBinContent(ibin) << " " <<  h_errorhist->GetBinError(ibin) << endl;
      }

      TCanvas* c1 = new TCanvas((("Plot")+*it2+*it).Data(), "Plot", 800, 600);
      
      if(it->Contains("pt")) h_pt_num->GetXaxis()->SetTitle("El p_{T} [GeV]");
      else if(it->Contains("njet")) h_pt_num->GetXaxis()->SetTitle("# jets");
      else if(it->Contains("ht")) h_pt_num->GetXaxis()->SetTitle("#Sigma jet p_{T} [GeV]");
      else  h_pt_num->GetXaxis()->SetTitle("El #eta");
      h_pt_num->GetYaxis()->SetTitle("#epsilon_{T/L}");
      
      h_pt_num->GetYaxis()->SetRangeUser(0.,0.5);
      h_pt_num->GetXaxis()->SetRangeUser(15.,59.);
      
      h_pt_num->Draw("p");

      h_pt_num_clone->Draw("psame");
      h_errorhist->SetFillStyle(3354);
      h_errorhist->SetFillColor(kBlue-8);
      h_errorhist->SetMarkerSize(0);
      h_errorhist->SetMarkerStyle(0);
      h_errorhist->SetLineColor(kWhite);
      h_errorhist->Draw("E2same");
      
      TLegend* legend= new TLegend(0.2,0.5,0.4,0.7);
      legend->SetFillColor(10);
      legend->SetBorderSize(0);
      legend->SetTextSize(0.04);
      
      legend->AddEntry(h_pt_num, "uncorrected", "lp");
      legend->AddEntry(h_pt_num_clone, "ewk corrected", "lp");
      
      legend->Draw("same");

      c1->SaveAs(("/home/jalmond/WebPlots/Fakes/FakeRateEWKSub" +  *it + ".pdf"));
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

