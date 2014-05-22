///#########################################################################
//#
// Author - John Almond
//#
// 
//
//#######################################################################

#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TFile.h>
#include "TCanvas.h"
#include <TStyle.h>
#include "TLatex.h"
#include "TImage.h"
#include "TLine.h"
#include "TColor.h"
#include "TROOT.h"
#include "TMath.h"
#include "TPostScript.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;


void MakeFakeRootFile(TString path, bool nosub);
void AtlasStyle();
TString slumi;

bool makenoEWsubtraction = true;
bool saveplots=true;
  
  

void setAtlasStyle() {
  AtlasStyle();
  return ;
}


void MakeFakeRootFile(TString path, bool nosub){
  AtlasStyle();
  TH1::SetDefaultSumw2();

  slumi = "4741";
  ofstream ofile;
  TString outfiletxt=  "FakeRates.txt";
  ofile.open(outfiletxt.Data());
  ofile.setf(ios::fixed,ios::floatfield);
  ofile.precision(3);


  /// Scales needed for MC due to runningf on grid 
  TString pathdata = path;

  TFile * fdata = new TFile(pathdata +"MMMuonFakes.data.Reco.root");
  TFile * fMC = new TFile(path +"MMMuonFakes.MCSub.Reco.root");

  /*
   *  Plot is Ereal : the rate of loose-tight muon passing isolation  
   *
   */
  
  TString outfile = "/var/tmp/john/FakeRateDiLeptonLFWRHN.root";
  if(!nosub)outfile = "/var/tmp/john/FakeRateDiLeptonNOSUBLFWRHN.root";

  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  
  bool plotEreal=true;
  if(plotEreal){    
    map<TString,TString> effhists;
    effhists["_eta"] = "#eta";
    effhists["_pt"] = "p_{T}";
    //effhists["_met"] = "MET GeV";
    //effhists["_njet"] = "jet multiplicity";
    //effhists["BF_pt"] = "p_{T}";
    //effhists["G_pt"] = "p_{T}";
    //effhists["HI_pt"] = "p_{T}";
    //effhists["JK_pt"] = "p_{T}";
    //effhists["L_pt"] = "p_{T}";
    //effhists["M_pt"] = "p_{T}";
    
    for(map<TString,TString>::iterator mit = effhists.begin(); mit!=effhists.end(); mit++){
      TString num = "h_efficiency" + mit->first + "_Tight";
      TString denom = "h_efficiency" + mit->first + "_all";
      TH1F* eff_all = (TH1F*)fdata->Get(denom.Data());
      TH1F* eff_passed = (TH1F*)fdata->Get(num.Data());    
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"Efficiency:: parameter " << mit->first << endl;
      ofile <<"Efficiency:: nbins=" << eff_all->GetNbinsX() << endl;
      TH1F* hratedenom = (TH1F*)eff_all->Clone(("hdenom"+mit->first).Data());
      TH1F* eff_rate = (TH1F*)eff_passed->Clone(("Efficiency"+mit->first).Data());
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      eff_rate->GetYaxis()->SetTitle("#epsilon_{real}");
      eff_rate->GetXaxis()->SetTitle((mit->second).Data());
      
      TH1F* errorhist = (TH1F*)eff_rate->Clone("error");
      eff_rate->GetYaxis()->SetRangeUser(0.0001,1.0);
      eff_rate->Draw();    
      errorhist->SetFillStyle(3354);
      errorhist->SetFillColor(kBlack);    
      errorhist->Draw("E2same");
      eff_rate->Write();
      

    }
  

    
    map<TString,TString> effhists2D;
    effhists2D["_ptnjets"] = "Njets";
    effhists2D["_ptnjetseta1"] = "Njets";
    effhists2D["_ptnjetseta2"] = "Njets";
    effhists2D["_ptnjetseta3"] = "Njets";

    for(map<TString,TString>::iterator mit = effhists2D.begin(); mit!=effhists2D.end(); mit++){
      TString num = "h_efficiency" + mit->first + "_Tight";
      TString denom = "h_efficiency" + mit->first + "_all";
      TH2F* eff_all = (TH2F*)fdata->Get(denom.Data());
      TH2F* eff_passed = (TH2F*)fdata->Get(num.Data());    
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"Efficiency:: parameter " << mit->first << endl;
      ofile <<"Efficiency:: nbins=" << eff_all->GetNbinsX() << endl;
      
      
      TH2F * eff_rate = (TH2F*)eff_passed->Clone(("Efficiency" + mit->first).Data());
      TH2F* hratedenom = (TH2F*)eff_all->Clone("hdenom");
      
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");	  
      eff_rate->GetYaxis()->SetTitle((mit->second).Data());
      eff_rate->GetXaxis()->SetTitle("p_{T} GeV");
      eff_rate->Write();     
      
    }
  }

  cout << "Running Fakes " << endl;
  map<TString,pair<TString,TString> > fakeeffhists;
  fakeeffhists["pt_barrel"] = make_pair("p_{T} GeV","#epsilon f");
  fakeeffhists["pt_endcap"] = make_pair("p_{T}FT GeV","#epsilon f");
  fakeeffhists["ptbarrel_heavyflavour"] = make_pair("HF p_{T} GeV","#epsilon f");
  fakeeffhists["ptbarrel_lightflavour"] = make_pair("LF p_{T} GeV","#epsilon f");
  fakeeffhists["ptendcap_heavyflavour"] = make_pair("HF p_{T}FT GeV","#epsilon f");
  fakeeffhists["ptendcap_lightflavour"] = make_pair("LF p_{T}FT GeV","#epsilon f");

  fakeeffhists["met"] = make_pair("MET GeV","#epsilon f");
  fakeeffhists["njets"] = make_pair("Jet multiplicity","#epsilon f");
  fakeeffhists["pt_periodBtoI"] = make_pair("p_{T} GeV","#epsilon f");
  fakeeffhists["pt_periodJtoM"] = make_pair("p_{T} GeV","#epsilon f");


  map<TString,pair<TString,TString> > fakeeffhists2D;
  fakeeffhists2D["ptnjets_barrel"] = make_pair("p_{T} GeV","Njets");
  fakeeffhists2D["ptnjets_endcap"] = make_pair("p_{T} GeV","Njets");
  fakeeffhists2D["BptHT_pt"] = make_pair("Barrel p_{T} GeV","HT/p_{T}");
  fakeeffhists2D["ECptHT_pt"] = make_pair("EndCap p_{T} GeV","HT/p_{T}");
  fakeeffhists2D["ptnjets_barrel_heavyflavour"] = make_pair("HF p_{T} GeV","Njets");
  fakeeffhists2D["ptnjets_endcap_heavyflavour"] = make_pair("HF p_{T} GeV","Njets");
  fakeeffhists2D["ptnjets_barrel_lightflavour"] = make_pair("LF p_{T} GeV","Njets");
  fakeeffhists2D["ptnjets_endcap_lightflavour"] = make_pair("LF p_{T} GeV","Njets");

  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////// Fake Rate Plots ////// 

  vector<TString> regions;
  regions.push_back("h_d0sigregionclose");
  regions.push_back("h_d0sig2regionclose");
  regions.push_back("h_d0sigSys1regionclose");
  regions.push_back("h_d0sigSys2regionclose");
  regions.push_back("h_d0sigSys3regionclose");  
  regions.push_back("h_btagregionclose");
  regions.push_back("h_did0sigregionclose");
  regions.push_back("h_d0sigregionnoclose");
  regions.push_back("h_did0sigregionnoclose");
  regions.push_back("h_d0sig2regionnoclose");
  regions.push_back("h_d0sigSys1regionnoclose");
  regions.push_back("h_d0sigSys2regionnoclose");
  regions.push_back("h_d0sigSys3regionnoclose");
  regions.push_back("h_btagregionnoclose");


  int i=0;
  for(vector<TString>::iterator it = regions.begin(); it!=regions.end();it++){

    TString region = *it;
    for(map<TString,pair<TString,TString> >::iterator mit = fakeeffhists.begin(); mit!=fakeeffhists.end(); mit++, i++){
            
      TString num = region + mit->first + "_passed";
      TString denom = region + mit->first + "_all";
      
      cout << "Numerator = " << num << endl;
      cout << "Denomerator = " << denom << endl;
      TString hname=mit->first;
      
      TH1F* eff_all = (TH1F*)fdata->Get(denom.Data());
      TH1F* eff_passed = (TH1F*)fdata->Get(num.Data());

      ///////////////////////////////////////////////////////////////////////////////////////
      ///
      /// Make plots with  W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////
      
      
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"Fake:: parameter " << mit->first << endl;
      ofile <<"Fake:: nbins=" << eff_all->GetNbinsX() << endl;
      
      ///  Setting up histograms for passed/all with different MCsub
           
      TH1* hMCdenom = (TH1F*)fMC->Get(denom)->Clone("MCdenom");
      TH1* hMCnum = (TH1F*)fMC->Get(num)->Clone("MCnum");
      if(nosub){
	eff_all->Add(hMCdenom,-0.9);
	eff_passed->Add(hMCnum,-0.9);
      }
      TH1* effallc = (TH1F*)fdata->Get(denom)->Clone("2denom");
      TH1* effpassedc = (TH1F*)fdata->Get(num)->Clone("2num");


      TH1F* eff_rate = (TH1F*)eff_passed->Clone((region+hname).Data());
      eff_rate->Divide(eff_rate,eff_all,1.,1.,"cl=0.683 b(1,1) mode");
      
      ////
      ///  Step 1 - is to check no negative bins are present due to MC subtraction [ if so try to merge with neighbouring bin ] 
      ///         - if still negative remove subtraction and set value with error = value
      ///

      
      for(int j=1; j< eff_rate->GetNbinsX()+1 ; j++ ){	
	float value = eff_rate->GetBinContent(j);	
	if(value < 0. || value > 1.) {
	  int bin;
	  if(eff_all->GetBinContent(j-1)!=0) bin = j-1;
	  else if(eff_all->GetBinContent(j+1)!=0) bin = j+1;
	  else bin = j;
	  eff_rate->SetBinContent(j,(eff_passed->GetBinContent(bin))/(eff_all->GetBinContent(bin)));	  
	  
	  if(eff_rate->GetBinContent(j)>1. || 		  eff_rate->GetBinContent(j)<= 0.){
	    eff_rate->SetBinContent(j,(effpassedc->GetBinContent(j))/(effallc->GetBinContent(j)));	  
	  }
	}
      }

      eff_rate->GetYaxis()->SetTitle(mit->second.second.Data());
      eff_rate->GetXaxis()->SetTitle((mit->second.first).Data());

      eff_rate->Write();

    }  

    cout << "Running 2D Fakes " << endl;

    for(map<TString,pair<TString,TString> >::iterator mit = fakeeffhists2D.begin(); mit!=fakeeffhists2D.end(); mit++){
      
      TString hname=mit->first;

      TString num = region + mit->first + "_passed";
      TString denom = region + mit->first + "_all";
      cout << "Numerator = " << num << endl;
      cout << "Denomerator = " << denom << endl;


      TH2F* eff_all = (TH2F*)fdata->Get(denom.Data());
      TH2F* eff_passed = (TH2F*)fdata->Get(num.Data());
      ofile << region << endl;
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"2D Fake:: parameter " << mit->first << endl;
      ofile <<"2D Fake:: nbins=" << eff_all->GetNbinsX() << endl;
         
      ///////////////////////////////////////////////////////////////////////////////////////
      ///
      /// Make plots with W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////

      
      TH2F* hMCdenom = (TH2F*)fMC->Get(denom)->Clone("mcdenom");
      TH2F* hMCnum = (TH2F*)fMC->Get(num)->Clone("mcnum");      

      // Standard rate plot
      TH2F* hall = (TH2F*)eff_all->Clone(("hall" + hname).Data());
      TH2F* hpass = (TH2F*)eff_passed->Clone(("hpassed"+hname).Data());
       

      if(nosub){
	eff_all->Add(hMCdenom,-1.);
	eff_passed->Add(hMCnum,-1.);
      }

      TH2F* eff_rate = (TH2F*)eff_passed->Clone((region+hname).Data());
      eff_rate->Divide(eff_rate,eff_all,1.,1.,"cl=0.683 b(1,1) mode");

      cout << hname << " " << region << " " << mit->first << endl;


      for(int j=1; j< eff_rate->GetNbinsX()+1 ; j++ ){
	for(int k=1; k< eff_rate->GetNbinsY()+1 ; k++ ){

	  float value = eff_rate->GetBinContent(j,k);
	  cout << "New Bin" << endl;
	  if(value < 0. || value >= 1.) {	    	    
	    int bin;
	    if(eff_all->GetBinContent(j-1,k)!=0) bin = j-1;
	    else if(eff_all->GetBinContent(j+1,k)!=0) bin = j+1;
	    else bin = j;
	    float newval=  ( eff_passed->GetBinContent(bin,k))/  ( eff_all->GetBinContent(bin,k));
	    if(newval < 0. || newval > 1.)newval=  (hpass->GetBinContent(j,k))/  (hall->GetBinContent(j,k) );
	   	    
	    cout << "Bin had value = " << eff_rate->GetBinContent(j,k) << endl;
	    eff_rate->SetBinContent(j,k,newval);
	    eff_rate->SetBinError(j,k,sqrt(newval));
	    cout << "Bin set new value = " << eff_rate->GetBinContent(j,k) <<  endl;
	  }

	  cout << mit->first << endl;
	  if(it->Contains("regionclose")){
	    if(mit->first.Contains("ptnjets_barrel_lightflavour")){
	      cout << mit->first << " FIXING BINS" << endl;
	      if(k==2){
		eff_rate->SetBinContent(j,k,eff_rate->GetBinContent(j,k+1));
	      }
	    }
	    if(mit->first.Contains("ptnjets_barrel_heavyflavour")){
	      if(k==2){
		eff_rate->SetBinContent(j,k,eff_rate->GetBinContent(j,k+1) );
	      }
	    }	    


	    if(mit->first.Contains("ptnjets_endcap_lightflavour")){
	      cout << mit->first << " FIXING BINS" << endl;
	      if(k==2){
		eff_rate->SetBinContent(j,k,eff_rate->GetBinContent(j,k+1));
	      }
	    }
	    if(mit->first.Contains("ptnjets_endcap_heavyflavour")){
	      if(k==1){
		if(eff_rate->GetBinContent(j,3)==0.)eff_rate->SetBinContent(j,3,eff_rate->GetBinContent(j,4) );
	      }
	      if(k==2){
		eff_rate->SetBinContent(j,k,eff_rate->GetBinContent(j,k+1) );
	      }
	    }
	  }
	  
   
	}	  
      }
      eff_rate->GetYaxis()->SetTitle(mit->second.second.Data());
      eff_rate->GetXaxis()->SetTitle((mit->second.first).Data());
      eff_rate->Write();
      
    }  
    
  }
  



  

  return;
}



void AtlasStyle(){
  
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color floa *all* objects
  
  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.16);
  atlasStyle->SetPadBottomMargin(0.16);
  atlasStyle->SetPadLeftMargin(0.16);
  
  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  atlasStyle->SetTextFont(font);
  
  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(0.03,"x");
  atlasStyle->SetTitleSize(tsize,"x");
  atlasStyle->SetLabelSize(0.03,"y");
  atlasStyle->SetTitleSize(tsize,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize,"z");
  
  // use bold lines and Lines
  atlasStyle->SetLineStyle(20);
  atlasStyle->SetMarkerSize(1.0);
  atlasStyle->SetHistLineWidth(2);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscr dashes
  
  // get rid of X error bars and y error bar caps
  //atlasStyle->SetErrorX(0.001);
  
  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);
   
  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);
  atlasStyle->SetPalette(1);
  atlasStyle->SetNumberContours(99);
  // reset plain style
  //gROOT->SetStyle("Plain");
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}
