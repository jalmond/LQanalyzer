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



void Opt_mT(){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  
  
  TLegend *legend = new TLegend(.7, 0.7, .9, 0.9);
  legend->SetFillColor(10);
  legend->SetBorderSize(0);
  legend->SetTextSize(0.04);

  
  TFile * fnp = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKnonprompt_dilep_5_3_14.root");
  TFile * fcf = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKchargeflip_dilep_5_3_14.root");
  TFile * fmc = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_mc_5_3_14.root");
  TFile * fdata = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_data_5_3_14.root");

  TH1F* h_npcutflow= (TH1F*)fnp->Get(("LowMassOptimise"));
  TH1F* h_cfcutflow= (TH1F*)fcf->Get(("LowMassOptimise"));
  TH1F* h_mccutflow= (TH1F*)fmc->Get(("LowMassOptimise"));
  TH1F* h_datacutflow= (TH1F*)fdata->Get(("LowMassOptimise"));
  
  std::vector<TString> masses;
  masses.push_back("40");
  masses.push_back("50");
  masses.push_back("60");
  masses.push_back("70");
  masses.push_back("80");
  //masses.push_back("90");
  
  

  std::map<TString, TH1*> histmap;
  for(unsigned int imass=0; imass < masses.size(); imass++){
    TFile * fsig = new TFile(("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + masses.at(imass) + "_nocut_5_3_14.root").Data());
    TH1* hsig =  (TH1F*)fsig->Get(("LowMassOptimise_sig"));
    histmap[masses.at(imass)] =  hsig;
  }
  
  
  int i2=0;
  for(std::map<TString, TH1*>::iterator it = histmap.begin(); it != histmap.end(); it++, i2++){
    TCanvas* c1 = new TCanvas(("Plot"+masses.at(i2)).Data(), "Plot", 800, 600);
    TH1* h_mass_mtopt = (TH1*) h_mccutflow->Clone(("A"+masses.at(i2)).Data());
    
    float nsig=50000.;
    if(it->first.Contains("40")) nsig = 100000;
    if(it->first.Contains("60")) nsig = 100000;
    if(it->first.Contains("80")) nsig = 100000;

    for(int i=1; i <   h_npcutflow->GetNbinsX(); i++){
      float sig_cut = it->second->GetBinContent(i);
      
      float tot_bkg =  h_npcutflow->GetBinContent(i) + h_cfcutflow->GetBinContent(i)  + h_mccutflow->GetBinContent(i);
      
      float sig_eff = sig_cut/nsig;
      float bkgtmp = tot_bkg + (0.28*h_npcutflow->GetBinContent(i))* (0.28*h_npcutflow->GetBinContent(i));
      float denom= 1. + sqrt(bkgtmp);
      
      
      float punzi = 0.;
      if(bkgtmp > 0.) {
	if(denom != 0.) punzi= sig_eff/denom;
      }
      if(sig_eff < 0.0004) punzi=0.;
      //cout << i << " " << punzi << endl;
      h_mass_mtopt->SetBinContent(i,punzi);
      
      //if(tot_bkg > 1) cout << "bin = " << i << ": tot_bkg = " << tot_bkg << " and data  = " << h_datacutflow->GetBinContent(i)  << " signal eff = " << 100.* sig_eff<< endl;
      //cout << i << ": h_npcutflow->GetBinContent(i) = " <<  h_npcutflow->GetBinContent(i) << " h_cfcutflow->GetBinContent(i) = " << h_cfcutflow->GetBinContent(i) << " h_mccutflow->GetBinContent(i) = " << h_mccutflow->GetBinContent(i)  << " ...   data = " << h_datacutflow->GetBinContent(i) << endl;
    } 

    h_mass_mtopt->GetYaxis()->SetTitle("Punzi"); 
    h_mass_mtopt->GetXaxis()->SetTitle("cut");
    
    h_mass_mtopt->SetLineWidth(3.);
    
    //h_mass_d0opt->GetYaxis()->SetRangeUser(0.001, 0.005);
    h_mass_mtopt->GetYaxis()->SetTitleSize(0.05);
    h_mass_mtopt->GetYaxis()->SetTitleOffset(1.5);
    h_mass_mtopt->GetYaxis()->SetLabelSize(0.04);
    h_mass_mtopt->Draw("hist");
    
    int binmax=0;
    float max=0.;

    for(unsigned int ibin =1 ; ibin <h_mass_mtopt->GetNbinsX()+1; ibin++){
      
      if(h_mass_mtopt->GetBinContent(ibin) > max) {
	max = h_mass_mtopt->GetBinContent(ibin);
	binmax=ibin;
      }
    }
    cout << "Signal efficiency for max punzi = "<< it->second->GetBinContent(binmax) / nsig << endl;
    cout << "Total fakes = " << h_npcutflow->GetBinContent(binmax)<< endl;
    cout << "Total prompt = " << h_mccutflow->GetBinContent(binmax)<< endl;
    cout << "Total cf = " << h_cfcutflow->GetBinContent(binmax)<< endl;
    cout << "Total bkg = " << h_npcutflow->GetBinContent(binmax) + h_mccutflow->GetBinContent(binmax) + h_cfcutflow->GetBinContent(binmax) << endl;
    cout << "Total data = " <<  h_datacutflow->GetBinContent(binmax)  << endl;
    std::vector<TString> ptmin;
    ptmin.push_back("15");
    ptmin.push_back("20");
    std::vector<TString> ptmax;
    ptmax.push_back("20");
    ptmax.push_back("25");
    std::vector<TString> eemin;
    eemin.push_back("10");
    std::vector<TString> eemax;
    eemax.push_back("60");
    eemax.push_back("80");
    eemax.push_back("100");
    eemax.push_back("1000");
    std::vector<TString> jjmin;
    jjmin.push_back("20");
    jjmin.push_back("40");
    std::vector<TString> jjmax;
    jjmax.push_back("120");
    jjmax.push_back("140");
    jjmax.push_back("150");
    std::vector<TString> eejjmin;
    eejjmin.push_back("80");
    eejjmin.push_back("90");
    eejjmin.push_back("100");
    eejjmin.push_back("110");
    std::vector<TString> eejjmax;
    eejjmax.push_back("180");
    eejjmax.push_back("200");
    eejjmax.push_back("220");
    eejjmax.push_back("260");
    std::vector<TString> e1jjmin;
    e1jjmin.push_back("0.");
    std::vector<TString> e1jjmax;
    e1jjmax.push_back("1000.");
    std::vector<TString> e2jjmin;
    e2jjmin.push_back("0.");
    std::vector<TString> e2jjmax;
    e2jjmax.push_back("125.");
    e2jjmax.push_back("150.");
    e2jjmax.push_back("175.");
    e2jjmax.push_back("200.");
    e2jjmax.push_back("1000.");
    std::vector<TString> metmax;
    metmax.push_back("30.");
    metmax.push_back("35.");
    metmax.push_back("40.");
    std::vector<TString> mtmax;
    mtmax.push_back("50.");
    mtmax.push_back("60.");
    mtmax.push_back("70.");
    mtmax.push_back("1000.");

    std::vector<TString> stmin;
    stmin.push_back("0.");
    stmin.push_back("100.");
    stmin.push_back("150.");


    std::vector<TString> stmax;
    stmax.push_back("100.");
    stmax.push_back("150.");
    stmax.push_back("200.");

    std::vector<TString> removeZ;
    removeZ.push_back("true");
    removeZ.push_back("false");
    
    std::vector<TString> removedrej;
    removedrej.push_back("true");
    removedrej.push_back("false");


    int icut=0;
    
    for(unsigned int ipt = 0; ipt <  ptmin.size() ; ipt++){
      for(unsigned int ipt2 = 0; ipt2 <  ptmax.size() ; ipt2++){
	for(unsigned int iee = 0; iee <  eemin.size() ; iee++){
	  for(unsigned int iee2 = 0; iee2 <  eemax.size() ; iee2++){
	    for(unsigned int ijj = 0; ijj <  jjmin.size() ; ijj++){
	      for(unsigned int ijj2 = 0; ijj2 <  jjmax.size() ; ijj2++){
		for(unsigned int ieejj = 0; ieejj <  eejjmin.size() ; ieejj++){
		  for(unsigned int ieejj2 = 0; ieejj2 <  eejjmax.size() ; ieejj2++){
		    for(unsigned int ie1jj = 0; ie1jj <  e1jjmin.size() ; ie1jj++){
		      for(unsigned int ie1jj2 = 0; ie1jj2 <  e1jjmax.size() ; ie1jj2++){
			for(unsigned int ie2jj = 0; ie2jj <  e2jjmin.size() ; ie2jj++){
			  for(unsigned int ie2jj2 = 0; ie2jj2 <  e2jjmax.size() ; ie2jj2++){
			    for(unsigned int imet = 0; imet <  metmax.size() ; imet++){
			      for(unsigned int imt = 0; imt <  mtmax.size() ; imt++){
				for(unsigned int istmin = 0; istmin <  stmin.size() ; istmin++){
				  for(unsigned int istmax = 0; istmax <  stmax.size() ; istmax++){
				    for(unsigned int iZ =0; iZ< removeZ.size(); iZ++){
                                      for(unsigned int iej =0; iej< removedrej.size(); iej++){
					
					TString cut= "ptmin = " + ptmin.at(ipt)+ " ptmax = " + ptmax.at(ipt2)+ " eemin= "  +  eemin.at(iee)+ " eemax = " +  eemax.at(iee2)+  " jjmin= " + jjmin.at(ijj)+ "jjmax = " +  jjmax.at(ijj2)+ " eejjmin= " + eejjmin.at(ieejj)+ " eejjmax = " + eejjmax.at(ieejj2)+  "e1jjmin = " + e1jjmin.at(ie1jj)+ " e1jjmax = " + e1jjmax.at(ie1jj2)+ " e2jjmin = " + e2jjmin.at(ie2jj)+ " e2jjmax = " + e2jjmax.at(ie2jj2)+ " metmax = " +  metmax.at(imet)+ " mtmax = " +  mtmax.at(imt)+ " stmin = " + stmin.at(istmin) +  " stmax = " + stmax.at(istmax) + " removeZ peak = " + removeZ.at(iZ) + " remove dRej > 2. = " +  removedrej.at(iej) ;
					icut++;
					if(icut == binmax) cout << "Max punzi has cut = " << cut  << endl;
				      }
				    }
				  }
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    
    
    
    ///legend->AddEntry(h_mass_d0opt,("m_{N}= "+ masses.at(im)).Data(),"l");
    
    it->second->Scale(0.01);
    it->second->SetLineColor(kRed);
    it->second->Draw("histsame");
    
    //legend->Draw("same");
    c1->SaveAs(("/home/jalmond/WebPlots/Opt/LowMassoptimise_" + it->first + ".pdf").Data());

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




