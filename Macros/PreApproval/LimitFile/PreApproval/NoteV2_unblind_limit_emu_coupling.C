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



void NoteV2_unblind_limit_emu_coupling(){
  
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
  
  TString outfile = "Limit_file_emu_coupling.root";
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
  
  Int_t result []     = {33,      33,    33,   33 ,     29,  25,  20, 17, 16, 11, 7,  7, 4, 4, 4, 4 };
  
  Double_t q2[] =   {0.1010,0.1005  , 0.0999 , 0.0989 , 0.0832 , 0.0658 , 0.0554 , 0.0362 , 0.0219 , 0.0107 , 0.0032 , 0.0132 , 0.0245,0.0329 , 0.0392 ,0.0463}; 
  
  Double_t bkg[]   = {33.7,33.7,33.7,33.7,25.5, 16.1391, 17.332, 13.5585, 11.6297, 12.9367, 8.50406, 5.54346, 4.31709, 2.09932, 1.53338, 1.55348, 1.55348};
  Double_t bkg_err[]  = {0.17, 0.17 , 0.17, 0.17 , 0.17 , 0.11 , 0.11 , 0.11 , 0.11 , 0.11  , 0.11  , 0.11    , 0.11  ,  0.11   , 0.11   , 0.11};
  Double_t fake[] = {30.6, 30.6,30.6,30.6,17.17 , 11.4446, 7.2872, 4.95979, 5.23113, 3.21979, 2.10034, 1.27898, 0.673133, 0.590882, 0.0277707, 0.0277707};
  
  Double_t stat[] = {2.99496,2.99496,2.99496,2.99496, 1.91, 1.33576, 1.11353, 1.0887, 1.09163, 0.810643, 0.659225, 0.567382, 0.420683, 0.382889, 0.389693, 0.389693};
  
  Double_t sigeff_emu[] = {0.00401305, 0.00426041, 0.00358092, 0.00127962, 0.00561703, 0.00529217, 0.0156041, 0.0482011, 0.0844905, 0.0968105, 0.102266, 0.13861, 0.133925, 0.133925, 0.133746,0.133746 };
  Double_t sigeff_mue[] = {0.00355829, 0.00465026, 0.00378657, 0.00141292, 0.00556388, 0.00511462, 0.0159325, 0.0465328, 0.0852958, 0.0958652, 0.105873, 0.134748, 0.133982,0.133982,  0.134823 , 0.110617};

  Double_t sigeff_emu_err[] = {0.164, 0.162, 0.167, 0.134, 0.119, 0.084, 0.081, 0.068, 0.060, 0.055, 0.054, 0.054, 0.059, 0.064, 0.067, 0.071};
  
  Double_t cf[] = {0.0133166, 0.0133166, 0.0133166, 0.0133166, 0.0335849, 0.0535586, 0.0471843, 0.0736801, 0.0920681, 0.0923246, 0.0707581, 0.0776031, 0.0385197, 0.0286589, 0.0277707, 0.0277707};
  
  Double_t efferr_alp[20];
  
  
  for(unsigned int i=0; i < 16; i++){
    cout << "Mass = " << mass[i] << endl;
    
    h_xsec->SetBinContent(i+1,2.*xsec_alp[i]); // set * 2 for combinatorics
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
    
    float mcerr = sqrt(0.15*0.15 +  pow(bkg_err[i],2));
    float bkgerr = sqrt( pow(0.34*fake[i],2) + pow(mcerr* (mc),2)  +  pow(.15*(cf[i]),2) );
    h_bkgerr->SetBinContent(i+1,bkgerr);
    
    
    ///Need recalculate thie because PDF uncertainty is wrong
    float err_sig_up = sqrt(sigeff_emu_err[i] *sigeff_emu_err[i] + 0.02*0.02);
    float err_sig_down = sqrt(sigeff_emu_err[i] *sigeff_emu_err[i] + 0.02*0.02);
    
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




