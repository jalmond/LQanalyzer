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
#include "TLatex.h"
#include <map>

//#include "Macro.h"
void setTDRStyle();



void NoteV2_unblind_limit_emu(){
  
  vector<TString> masses;
  masses.push_back("40");
  masses.push_back("50");
  masses.push_back("60");
  masses.push_back("70");
  masses.push_back("80");
  masses.push_back("90");
  masses.push_back("100");
  masses.push_back("125");
  masses.push_back("150");
  masses.push_back("175");
  masses.push_back("200");
  masses.push_back("225");
  masses.push_back("250");
  masses.push_back("275");
  masses.push_back("300");
  masses.push_back("325");
  masses.push_back("350");
  masses.push_back("375");
  masses.push_back("400");
  masses.push_back("500");
  
  TString outfile = "Limit_file_emu.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  
  TH1F* h_sigeff = new TH1F("h_sigeff","h_sigeff", 20,0.,20.);
  TH1F* h_sigefferr = new TH1F("h_sigefferr","h_sigefferr", 20,0.,20.);
  TH1F* h_nbkg = new TH1F("h_nbkg","h_nbkg", 20,0.,20.);
  TH1F* h_nfake =  new TH1F("h_nfake","h_nfake", 20,0.,20.);
  TH1F* h_staterr  =  new TH1F("h_staterr","h_staterr", 20,0.,20.);
  TH1F* h_bkgerr  =  new TH1F("h_bkgerr","h_bkgerr", 20,0.,20.);
  TH1F* h_xsec  =  new TH1F("h_xsec","h_xsec", 20,0.,20.);
  TH1F* h_obs  =  new TH1F("h_obs","h_obs", 20,0.,20.);
  TH1F* h_mass  =  new TH1F("h_mass","h_mass", 20,0.,20.);
  Double_t eff_alp[20];
  
  Double_t k_factor=1.34;
  Double_t mass[]     = {40.  , 50.   , 60.   , 70.   , 80.   , 90.   , 100.  , 125.  , 150.  , 175.   , 200.  ,  250.  , 300.   ,  350. , 400.  , 500. };
  Double_t xsec_alp[] = {1516  , 1071.1 , 607.7  , 211.96 , 19.07  , 7.1047 , 3.5618 , 1.0767 , 0.4594 , 0.23266 , 0.13127 , 0.050928  , 0.023214,  0.011705 , 0.006332 , 0.002154};
  
  Int_t result []     = {20,      20,     20,   20 ,     18,  76,  54, 33, 29, 17, 12,  10, 5, 4, 4, 4 };
  
  Double_t q2[] =   {0.1010,0.1005  , 0.0999 , 0.0989 , 0.0832 , 0.0658 , 0.0554 , 0.0362 , 0.0219 , 0.0107 , 0.0032 , 0.0132 , 0.0245,0.0329 , 0.0392 ,0.0463}; 
  
  Double_t bkg[]   = {20.9899, 20.9899, ,20.9899, 20.9899, 16.1391, 52.3638, 41.3618, 24.3814, 22.2361, 12.3094, 8.24415, 6.67987, 2.51467, 1.77983,1.65745, 1.65745};
  Double_t bkg_err[]  = {0.17, 0.17 , 0.17, 0.17 , 0.17 , 0.11 , 0.11 , 0.11 , 0.11 , 0.11  , 0.11  , 0.11    , 0.11  ,  0.11   , 0.11   , 0.11};
  Double_t fake[] = {19.5076, 19.5076, 19.5076, 19.5076, 11.9203, 33.3146, 23.1204, 10.4236, 9.47577, 4.59534, 2.85696, 2.38207, 0.865385, 0.700883, 0.705969, 0.705969};
  
  Double_t stat[] = {1.97337, 1.97337, 1.97337, 1.97337, 1.45513, 2.32347, 2.00438, 1.49532, 1.4189, 0.980255, 0.805, 0.741997, 0.450146, 0.40104, 0.396409,0.396409};
  
  Double_t sigeff_emu[] = {0.00302, 0.00419, 0.00342, 0.00127, 0.00479, 0.00655, 0.01788, 0.0538, 0.102, 0.108, 0.119, 0.154, 0.148, 0.148, 0.143, 0.119};
  Double_t sigeff_mue[] = {0.00371, 0.00388, 0.00321, 0.00194, 0.00472, 0.00636, 0.0178, 0.0552, 0.102, 0.108, 0.118, 0.156, 0.149, 0.145, 0.142, 0.119};
  Double_t sigeff_emu_err[] = {0.164, 0.162, 0.167, 0.134, 0.119, 0.084, 0.081, 0.068, 0.060, 0.055, 0.054, 0.054, 0.059, 0.064, 0.067, 0.071};
  
  Double_t cf[] = {0.0133166, 0.0133166, 0.0133166, 0.0133166, 0.0335849, 0.215327, 0.194034, 0.161814, 0.157921, 0.125483, 0.0971075, 0.0845456, 0.0410733, 0.0308207, 0.0283187, 0.0283187};
  
  Double_t efferr_alp[20];
  
  
  for(unsigned int i=0; i < 16; i++){
    cout << "Mass = " << mass[i] << endl;
    
    h_xsec->SetBinContent(i+1,xsec_alp[i]);
    h_obs->SetBinContent(i+1,result[i]);
    h_mass->SetBinContent(i+1,mass[i]);
    
    double staterr = stat[i];
    double total_bkg = bkg[i];
    
    h_sigeff->SetBinContent(i+1, (sigeff_emu[i] + sigeff_mue[i]));
    eff_alp[i] = (sigeff_emu[i] + sigeff_mue[i]);
    h_nbkg->SetBinContent(i+1, total_bkg);
    h_nfake->SetBinContent(i+1,fake[i]);
    h_staterr->SetBinContent(i+1,staterr);
    float mc = total_bkg - fake[i] - cf[i];
    
    float bkgerr = sqrt( pow(0.34*fake[i],2) + pow(bkg_err[i]* (mc),2)  +  pow(.15*(cf[i]),2) );
    h_bkgerr->SetBinContent(i+1,bkgerr);
    
    
    float err_sig_up = sigeff_emu_err[i];
    
    float err_sig_down = sigeff_emu_err[i];
    
    float err_sig = err_sig_up; 
    if(err_sig_up < err_sig_down) err_sig = err_sig_down;
    
    efferr_alp[i]  = err_sig * (sigeff_mue[i] +sigeff_emu[i]); ;
    
  }
    
  for(unsigned int i=0; i < masses.size(); i++){
    h_sigefferr->SetBinContent(i+1,efferr_alp[i]);
  }
  
  fout->cd();
  
  h_sigeff->Write();
  h_sigefferr->Write();
  h_nbkg->Write();
  h_nfake->Write();
  h_staterr->Write();
  h_bkgerr->Write();
  h_xsec->Write();
  h_obs->Write();
  h_mass->Write();
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




