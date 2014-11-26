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



void GetSigEfficiency(TString path){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  
  TFile * file = new TFile(path);
  
  TH1F* h_ref= (TH1F*)file->Get(("Efficiency/eff_electronRef"));
  TH1F* h_pteta =(TH1F*)file->Get(("Efficiency/eff_electronPtEtaCutColl"));
  TH1F* h_tight =(TH1F*)file->Get(("Efficiency/eff_electron_NoIsoCutColl"));
  TH1F* h_iso =(TH1F*)file->Get(("Efficiency/eff_electron_IsoCutColl"));
  TH1F* h_npfiso =(TH1F*)file->Get(("Efficiency/eff_electron_NPFIsoCutColl"));
  TH1F* h_analysis =(TH1F*)file->Get(("Efficiency/eff_electron_analysisCutColll"));
  TH1F* h_analysisnpf =(TH1F*)file->Get(("Efficiency/eff_electron_analysisNPFCutColll"));
  
  TH1F* h_DeltaEta =(TH1F*)file->Get(("Efficiency/eff_electron_DeltaEta"));
  TH1F* h_DeltaPhi =(TH1F*)file->Get(("Efficiency/eff_electron_DeltaPhi"));
  TH1F* h_SigmaIEta =(TH1F*)file->Get(("Efficiency/eff_electron_SigmaIEta"));
  TH1F* h_DZ =(TH1F*)file->Get(("Efficiency/eff_electron_DZ"));
  TH1F* h_HoverE =(TH1F*)file->Get(("Efficiency/eff_electron_HoverE"));
  TH1F* h_convfit =(TH1F*)file->Get(("Efficiency/eff_electron_convfit"));
  TH1F* h_ep =(TH1F*)file->Get(("Efficiency/eff_electron_ep"));
  TH1F* h_missinghit =(TH1F*)file->Get(("Efficiency/eff_electron_missinghit"));
  TH1F* h_convphoton =(TH1F*)file->Get(("Efficiency/eff_electron_convphoton"));
  TH1F* h_DXY =(TH1F*)file->Get(("Efficiency/eff_electron_DXY"));
  TH1F* h_chargeconst =(TH1F*)file->Get(("Efficiency/eff_electron_chargeconst"));
  TH1F* h_refd0 = (TH1F*)file->Get(("Efficiency/eff_electronTight_tightref"));
  
  TH1F* h_jetsel =(TH1F*)file->Get(("JetSelection"));
  TH1F* h_presel =(TH1F*)file->Get(("PreSelection"));
  TH1F* h_presel_npf =(TH1F*)file->Get(("PreSelectionNPF"));
  
  cout << "Pt Eta cut efficiency [%] = " <<100* h_pteta->Integral() / h_ref->Integral()<< endl;;
  cout << "ID cut efficiency [%] = " << 100* h_tight->Integral() / h_ref->Integral()<< endl;;
  cout << "DeltaEta cut efficiency [%] = " << 100* h_DeltaEta->Integral() / h_refd0->Integral()<< endl;;
  cout << "DeltaPhi cut efficiency [%] = " << 100* h_DeltaPhi->Integral() / h_refd0->Integral()<< endl;;
  cout << "SigmaIEta cut efficiency [%] = " << 100* h_SigmaIEta->Integral() / h_refd0->Integral()<< endl;;
  cout << "DZ  cut efficiency [%] = " <<100* h_DZ->Integral() / h_refd0->Integral()<< endl;;
  cout << "HoverE cut efficiency [%] = " << 100* h_HoverE->Integral() / h_refd0->Integral()<< endl;;
  cout << "convfit cut efficiency [%] = " <<  100* h_convfit->Integral() / h_refd0->Integral()<< endl;;
  cout << "ep cut efficiency [%] = " <<  100* h_ep->Integral() / h_refd0->Integral()<< endl;;
  cout << "missinghit cut efficiency [%] = " << 100* h_missinghit->Integral() / h_refd0->Integral()<< endl;;
  cout << "convphoton  cut efficiency [%] = " <<  100* h_convphoton->Integral() / h_refd0->Integral()<< endl;;
  cout << "DXY cut efficiency [%] = " << 100* h_DXY->Integral() / h_pteta->Integral()<< endl;;
  cout << "chargeconst cut efficiency [%] = " << 100*  h_chargeconst->Integral() / h_refd0->Integral()<< endl;;
  cout << "\n ------------ " << endl;

  
  cout << "Isolation cut efficiency [%] = " << 100* h_iso->Integral() / h_ref->Integral()<< endl;;
  cout << "Electron efficiency [%] = " << 100* h_analysis->Integral() / h_ref->Integral()<< endl;;
  cout << "Electron efficiency (npfiso) [%] = " <<100*  h_analysisnpf->Integral() / h_ref->Integral()<< endl;;
  
  cout << "\n ------------ " << endl;
  cout << "Jet Selection  efficiency [%] " << 100* h_jetsel->Integral() / h_ref->Integral()<< endl;;
  cout << "\n ------------ " <<endl;

  cout << "Total efficiency (SSee + 2 jets) " << 100* h_presel->Integral() / h_ref->Integral()<< endl;;
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




