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



void GetNMCEvents(){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  TString path ="/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_mc_5_3_14.root";
  TFile * file = new TFile(path);
  
  TString fakepath ="/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKnonprompt_dilep_5_3_14.root";
  TFile * filefake = new TFile(fakepath);
  
  TString cfpath ="/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKchargeflip_dilep_5_3_14.root";
  TFile * filecf = new TFile(cfpath);
  cout << file << " " << filefake << " " << filecf << endl;
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
  masses.push_back("600");
  masses.push_back("700");

  
  for(unsigned int i=0; i < masses.size(); i++){
    
    TString tag = masses.at(i);
    cout << tag << endl;
    TH1* hnmc =   (TH1F*)file->Get((tag + "MassRegion_nentries").Data());
    cout << hnmc << endl;
    TH1* hnnp =   (TH1F*)filefake->Get((tag + "MassRegion_syst").Data());
    cout << hnnp << endl;
    TH1* hncf =   (TH1F*)filecf->Get((tag + "MassRegion_syst").Data());
    cout << hncf << endl;

    float staterr = sqrt( hnmc->GetBinError(1)*hnmc->GetBinError(1) +  hnnp->GetBinError(1)*hnnp->GetBinError(1) + hncf->GetBinError(1)*hncf->GetBinError(1));

   TString sigpath ="/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + masses.at(i) + "_nocut_5_3_14.root";
    TFile * file_sig = new TFile(sigpath);
    TH1* hn_sig_mc  = (TH1F*)file_sig->Get((tag + "MassRegion_nentries").Data());
    
    
    float sig_nom = hn_sig_mc->GetBinContent(1);
    
    TH1* hn_sig_syst  = (TH1F*)file_sig->Get((tag + "MassRegion_syst").Data());
    
    float diff_jet_Eup = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(2))/hn_sig_syst->GetBinContent(1);;
    float diff_jet_Edown = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(3))/hn_sig_syst->GetBinContent(1);
    
    float diff_jet_Rup = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(4))/hn_sig_syst->GetBinContent(1);
    float diff_jet_Rdown = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(5))/hn_sig_syst->GetBinContent(1);
    
    float diff_met_clup = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(6))/hn_sig_syst->GetBinContent(1);
    float diff_met_cldown = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(7))/hn_sig_syst->GetBinContent(1);

    float diff_btag_1 = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(8))/hn_sig_syst->GetBinContent(1);
    float diff_btag_2 = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(9))/hn_sig_syst->GetBinContent(1);
    float diff_btag_3 = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(10))/hn_sig_syst->GetBinContent(1);
    float diff_btag_4 = fabs(hn_sig_syst->GetBinContent(1)- hn_sig_syst->GetBinContent(11))/hn_sig_syst->GetBinContent(1);
    
    float jetE = diff_jet_Eup;
    if(diff_jet_Eup < diff_jet_Edown) jetE= diff_jet_Edown;
    cout << "jet error = " << jetE << endl;

    float jetR =diff_jet_Edown;
    if(diff_jet_Rup < diff_jet_Rdown ) jetR = diff_jet_Rdown;
    cout << "jet res error = " << jetR << endl;
    
    float metE= diff_met_clup;
    if(diff_met_clup < diff_met_cldown) metE = diff_met_cldown;
    cout << "Met error = " << metE << endl;
    float btag = sqrt(diff_btag_1*diff_btag_1 + diff_btag_2*diff_btag_2 + diff_btag_3*diff_btag_3 + diff_btag_4 *diff_btag_4);
    
    cout << "Btag error = " << btag << endl;
    float err = sqrt(0.1*0.1 + 0.035*0.035  + jetE*jetE + jetR*jetR + metE*metE + btag*btag + 0.07*0.07);
    
    
    float mc_nom = hnmc->GetBinContent(1);
    float mc_nom_no_weight = hnmc->GetBinContent(2);
    
    float np_nom = hnnp->GetBinContent(1);
    float cf_nom = hncf->GetBinContent(1);

    
    
    float total_bkg = mc_nom + np_nom + cf_nom;


    cout << "Mass point : " << masses.at(i) << endl;
    cout << "Nsig = " << sig_nom << endl;
    cout << "Total bkg = " << total_bkg << endl;
    cout << "Total fakes = " << np_nom << endl;
    cout << "Stat err = " << staterr << endl;
    cout << "Total err = " << err << endl;
   
    cout << "TOTAL number of CF = " << cf_nom << endl;

    cout <<"Number of MC events (weighted) passing mass region: " <<tag  <<  " = " << mc_nom << endl;
    cout <<"Number of MC events passing mass region: " <<tag  <<  " = " << mc_nom_no_weight << endl;
    
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




