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

//#include "Macro.h"
void setTDRStyle();

float integrate_mc(TString sample);
float syst(TString sample, TString path,int sys1, int sys2);

float GetSyst(TString path, int sys1, int sys2);


void GetSystematics_MCBkg(){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
    
  float syst_jes = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 3,4);
  float syst_jer = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 5,6);
  float syst_met = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 7,8);
  float syst_btag1 = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 9,10);
  float syst_btag2 = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 11,12);
  float syst_btag = sqrt(syst_btag1*syst_btag1 + syst_btag2*syst_btag2);
  float syst_id = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 17,18);
  float syst_pileup = GetSyst("limithist/50_lm_lowmassMassRegion_limithist", 15,16);

  cout << "Low Mass JES = " << syst_jes << endl;
  cout << "Low Mass JER = " << syst_jer << endl;
  cout << "Low Mass MET = " << syst_met << endl;
  cout << "Low Mass btag = " << syst_btag << endl;
  cout << "Low Mass ID= " << syst_id << endl;
  cout << "Low Mass pileup = " << syst_pileup << endl;
  cout << "Low MAss total = " << sqrt (syst_jes*syst_jes + syst_jer*syst_jer + syst_met*syst_met + syst_btag*syst_btag + syst_id*syst_id + syst_pileup*syst_pileup + 6*6 + 15.*15. + 2.6*2.6) << endl;;
  

}


float GetSyst(TString path, int sys1, int sys2){

  float nwz = integrate_mc("WZ_py");
  float nzz = integrate_mc("ZZ_py");
  float nwwm = integrate_mc("SSWmWm");
  float nwwp = integrate_mc("SSWpWp");
  float nttz = integrate_mc("ttZ");
  float nttw = integrate_mc("ttW");

  float tot = nwz + nzz + nwwp + nwwm + nttw + nttz;
  
  float wz_percent = nwz / tot;
  float zz_percent = nzz / tot;
  float ssm_percent = nwwm / tot;
  float ssp_percent = nwwp / tot;
  float ttz_percent = nttz / tot;
  float ttw_percent = nttw / tot;
  cout << "% = " << wz_percent << " " << zz_percent << " " << ssm_percent << " "  << ssp_percent << " " << ttz_percent << " " << ttw_percent << " " << endl;
  cout <<  syst("WZ_py",path, sys1, sys2) << endl;


  float wz_syst = wz_percent* syst("WZ_py",path, sys1, sys2); 
  float zz_syst = zz_percent* syst("ZZ_py",path, sys1, sys2); 
  float ssm_syst = ssm_percent* syst("SSWmWm",path, sys1, sys2); 
  float ssp_syst = ssp_percent* syst("SSWpWp",path, sys1, sys2); 
  float ttz_syst = ttz_percent* syst("ttZ",path, sys1, sys2); 
  float ttw_syst = ttw_percent* syst("ttW",path, sys1, sys2); 
  
  cout << wz_syst << " " << zz_syst << " " << ssm_syst << " " << ssp_syst << " " << ttw_syst << " " << ttz_syst << endl;

  return  wz_syst + zz_syst + ssp_syst + ssm_syst + ttz_syst+ ttw_syst;
  
  
}

float syst(TString sample, TString path,int isys1, int isys2){

  TString spath = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SK" + sample  +"_dilep_5_3_14.root";

  TFile * file = new TFile(spath);

  TH1* hnsig = (TH1F*)file->Get(path);

  if(!hnsig) return 0.;
  float nom = hnsig->GetBinContent(2);
  float sys1 = hnsig->GetBinContent(isys1);
  float sys2 = hnsig->GetBinContent(isys2);
  
  cout << sys1 << " " << sys2   <<  " nom = " << nom << endl;
  sys1 = ((sys1 - nom) / nom) * 100.;
  sys2 = ((sys2 - nom) / nom) * 100.;
  float sys_final = fabs(sys1);
  if(fabs(sys2) > sys_final) sys_final = fabs(sys2);  

  return sys_final;
  
}

float integrate_mc(TString sample){

  TString path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SK" + sample  +"_dilep_5_3_14.root";
  TFile * file = new TFile(path);

  TH1* h = (TH1*)(TH1F*)file->Get(("LowMassRegion/h_Nelectrons_LowMassRegion"));

  float n = h->Integral();

  return n;

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




