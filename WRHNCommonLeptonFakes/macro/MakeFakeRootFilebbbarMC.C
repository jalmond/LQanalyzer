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


void MakeFakeRootFile(TString path);
void AtlasStyle();
TString slumi;

bool makenoEWsubtraction = false;
bool saveplots=false;
  
  

void setAtlasStyle() {
  AtlasStyle();
  return ;
}


void MakeFakeRootFile(TString path){
  AtlasStyle();
  TH1::SetDefaultSumw2();

  slumi = "4741";

  TPostScript ps("Efficiencies_Fakes_Real_WRHN.ps",111);
  
  ofstream ofile;
  TString outfiletxt=  "FakeRates.txt";
  ofile.open(outfiletxt.Data());
  ofile.setf(ios::fixed,ios::floatfield);
  ofile.precision(3);


  /// Scales needed for MC due to runningf on grid 
  TString pathdata = path;

  vector<TFile*> vFileW;
  vector<TFile*> vFileZ;
  vector<TFile*> vFilettbar;
  
  TFile * fdata = new TFile(pathdata +"MMMuonFakes.Z.Reco.root");
  TFile * fbbbar = new TFile(pathdata +"MMMuonFakes.bbbar.Reco.root");

  //////  Hists for picking up all efficiencies for single pt barrel ( as comparison)

  
  TString outfile = "FakeRateDiLeptonWRHNbbbar.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  
  bool plotEreal=true;
  if(plotEreal){

    map<TString,TString> effhists;
    effhists["_eta"] = "#eta";
    effhists["_pt"] = "p_{T}";
    //    effhists["_met"] = "MET GeV";
    effhists["_njet"] = "jet multiplicity";
    effhists["BF_pt"] = "p_{T}";
    effhists["G_pt"] = "p_{T}";
    effhists["HI_pt"] = "p_{T}";
    effhists["JK_pt"] = "p_{T}";
    effhists["L_pt"] = "p_{T}";
    effhists["M_pt"] = "p_{T}";
    
    for(map<TString,TString>::iterator mit = effhists.begin(); mit!=effhists.end(); mit++){
      TString num = "h_efficiency" + mit->first + "_Tight";
      TString denom = "h_efficiency" + mit->first + "_all";
      TH1F* eff_all = (TH1F*)fdata->Get(denom.Data());
      TH1F* eff_passed = (TH1F*)fdata->Get(num.Data());    
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"Efficiency:: parameter " << mit->first << endl;
      ofile <<"Efficiency:: nbins=" << eff_all->GetNbinsX() << endl;
      
      TCanvas* c1 = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
      c1->Divide(1,2);        
      c1->cd(1);
      c1->SetLogx();
      TH1F* hratedenom = (TH1F*)eff_all->Clone(("hdenom"+mit->first).Data());
      TH1F* eff_rate = (TH1F*)eff_passed->Clone(("Efficiency"+mit->first).Data());
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      eff_rate->GetYaxis()->SetTitle("#epsilon_{real}");
      eff_rate->GetXaxis()->SetTitle((mit->second).Data());
      TH1F* errorhist = (TH1F*)eff_rate->Clone("error");
      eff_rate->GetYaxis()->SetRangeUser(0.0001,1.0);
      //      eff_rate->Draw();    
      errorhist->SetFillStyle(3354);
      errorhist->SetFillColor(kBlack);    
      //      errorhist->Draw("E2same");
      eff_rate->Write();
      
      TH1F * err_rate = (TH1F*)eff_rate->Clone(("Err_Efficiency" + mit->first).Data() );
      for(int ierrx=1 ; ierrx < err_rate->GetNbinsX()+1; ierrx++){
	double err = err_rate->GetBinError(ierrx);
	err_rate->SetBinContent(ierrx,err);
	ofile << "Bin : range ::Value : statistics " << ierrx << " : " <<  err_rate->GetBinLowEdge(ierrx) << "-" << eff_rate->GetBinLowEdge(ierrx+1) << " = " << eff_rate->GetBinContent(ierrx) << " +- " << err_rate->GetBinContent(ierrx) <<" : "  <<eff_all->GetBinContent(ierrx) <<  endl;
      }
      
      err_rate->Write();

      c1->cd(2);    
      eff_all->GetYaxis()->SetTitle("Entries");
      eff_all->GetXaxis()->SetTitle((mit->second).Data());
      //      eff_all->Draw("HIST");
      eff_passed->SetFillColor(kYellow);
      //      eff_passed->Draw("HISTsame");         
    
      TLegend* legend= new TLegend(0.60,0.7,0.70,0.9);
      legend->SetFillColor(10);
      legend->SetBorderSize(0);
      legend->SetTextSize(0.03);   
      legend->AddEntry(eff_all,"LooseMuons (Z window)","f");
      legend->AddEntry(eff_passed,"Tight LooseMuons (Z window)","f");
      TLatex lat;
      double max = eff_all->GetMaximum();
      lat.DrawLatex(100., max*.8, "#int Lumi = " + slumi + "pb^{-1}");    
      lat.Draw();
      legend->Draw("same");        
      
      if(saveplots)c1->SaveAs(("Efficiency_" +mit->first + "_lumi"+slumi+".pdf").Data());          
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
      
      
      TCanvas* c1 = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
      c1->Divide(1,2);        	
      c1->cd(1);
      c1->SetLogx();
      c1->SetLogy();
      TH2F * eff_rate = (TH2F*)eff_passed->Clone(("Efficiency" + mit->first).Data());
      TH2F* hratedenom = (TH2F*)eff_all->Clone("hdenom");
      
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");	  
      eff_rate->GetYaxis()->SetTitle((mit->second).Data());
      eff_rate->GetXaxis()->SetTitle("p_{T} GeV");
      eff_rate->Write();     
      //      eff_rate->Draw("colz");
     
      c1->cd(2);  	     
      
      TH2F * err_rate = (TH2F*)eff_rate->Clone(("Error_Efficiency" + mit->first).Data());
      for(int ierrx=1 ; ierrx < err_rate->GetNbinsX()+1; ierrx++){
	for(int ierry=1 ; ierry < err_rate->GetNbinsY()+1; ierry++){
	  double err = err_rate->GetBinError(ierrx,ierry);
	  err_rate->SetBinContent(ierrx,ierry,err);
	  ofile << "Bin : range : Value : statistics " << ierrx << "," << ierry  << " : "  << err_rate->GetXaxis()->GetBinLowEdge(ierrx) << " - " << err_rate->GetXaxis()->GetBinLowEdge(ierrx+1) << " , " << err_rate->GetYaxis()->GetBinLowEdge(ierry) << " - " << err_rate->GetYaxis()->GetBinLowEdge(ierry+1) << "=  " << eff_rate->GetBinContent(ierrx,ierry) <<  " +-" << err << " : "  <<eff_all->GetBinContent(ierrx, ierry) << endl;           
	}
      }
      //      err_rate->Draw("colztext");
      err_rate->Write();
        
      if(saveplots)c1->SaveAs(("Efficiency2D" +mit->first + "_lumi"+slumi+".pdf").Data());          
    }
  }

  


  cout << "Running Fakes " << endl;
  map<TString,pair<TString,TString> > fakeeffhists;
  fakeeffhists["ptbarrel_lightflavour"] = make_pair("p_{T} GeV","#epsilon f");
  fakeeffhists["ptbarrel_heavyflavour"] = make_pair("p_{T} GeV","#epsilon f");
  fakeeffhists["ptendcap_heavyflavour"] = make_pair("p_{T} GeV","#epsilon f");
  fakeeffhists["ptendcap_lightflavour"] = make_pair("p_{T} GeV","#epsilon f");



  //fakeeffhists["met"] = make_pair("MET GeV","#epsilon f");
    //fakeeffhists["eta"] = make_pair("#eta","#epsilon f");  // until run MC
  //fakeeffhists["njets"] = make_pair("Jet multiplicity","#epsilon f");
  //fakeeffhists["pt_periodBtoI"] = make_pair("p_{T} GeV","#epsilon f");
  //fakeeffhists["pt_periodJtoM"] = make_pair("p_{T} GeV","#epsilon f");


  map<TString,pair<TString,TString> > fakeeffhists2D;
  //fakeeffhists2D["ptnjets_barrel"] = make_pair("p_{T} GeV","Njets");
  //  fakeeffhists2D["ptnjets_endcap"] = make_pair("p_{T} GeV","Njets");
  //fakeeffhists2D["ptHT"] = make_pair("p_{T} GeV","HT GeV");
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////// Fake Rate Plots ////// 

  vector<TString> regions;
  regions.push_back("h_d0sig2regionclose");
  regions.push_back("h_truthregionclose");
  //regions.push_back("h_btagregionclose");
  //regions.push_back("h_btagMTregionclose");

   regions.push_back("h_truthregionnoclose");
   regions.push_back("h_d0sig2regionnoclose");
  //regions.push_back("h_btagregionnoclose");
  //regions.push_back("h_btagMTregionnoclose");
  int i=0;
  for(vector<TString>::iterator it = regions.begin(); it!=regions.end();it++){

    TString region = *it;
    for(map<TString,pair<TString,TString> >::iterator mit = fakeeffhists.begin(); mit!=fakeeffhists.end(); mit++, i++){
      
      TString num = region + mit->first + "_passed";
      TString denom = region + mit->first + "_all";

      cout << "Numerator = " << num << endl;
      cout << "Denomerator = " << denom << endl;
      TString hname=mit->first;
      
      TH1F* eff_all = (TH1F*)fbbbar->Get(denom.Data());
      TH1F* eff_passed = (TH1F*)fbbbar->Get(num.Data());



      ///////////////////////////////////////////////////////////////////////////////////////
      ///
      /// Make plots with no W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////

      if(makenoEWsubtraction){
	TCanvas* cnomcsub = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
	cnomcsub->Divide(1,2);
	cnomcsub->cd(1);
	if(mit->first.Contains("pt"))cnomcsub->SetLogx();
	TH1F* hratedenomnomcsub = (TH1F*)eff_all->Clone(("hdenomnomcsub" + hname).Data());
	TH1F* eff_ratenomcsub = (TH1F*)eff_passed->Clone((region+hname+"_nomcsub").Data());
	eff_ratenomcsub->Divide(eff_ratenomcsub,hratedenomnomcsub,1.,1.,"cl=0.683 b(1,1) mode");
	eff_ratenomcsub->GetYaxis()->SetTitle(mit->second.second.Data());
	eff_ratenomcsub->GetXaxis()->SetTitle((mit->second.first).Data());
	TH1F* errorhistnomcsub = (TH1F*)eff_ratenomcsub->Clone("error");
	eff_ratenomcsub->Write();
	//	eff_ratenomcsub->Draw();
	errorhistnomcsub->SetFillStyle(3354);
	errorhistnomcsub->SetFillColor(kBlack);
	//	errorhistnomcsub->Draw("E2same");
	
	cnomcsub->cd(2);
	
	TH1F * err_ratenomcsub = (TH1F*)eff_ratenomcsub->Clone(("Err_" + region + mit->first+"_nomcsub").Data() );
	for(int ierrx=1 ; ierrx < err_ratenomcsub->GetNbinsX()+1; ierrx++){
	  double err = err_ratenomcsub->GetBinError(ierrx);
	  err_ratenomcsub->SetBinContent(ierrx,err);
	  ofile << "Bin Error nomcsub " << ierrx << " : " <<  err_ratenomcsub->GetBinLowEdge(ierrx) << "-" << eff_ratenomcsub->GetBinLowEdge(ierrx+1) << " = " << err_ratenomcsub->GetBinContent(ierrx) << endl;
	}
	eff_ratenomcsub->GetYaxis()->SetRangeUser(0.,0.1);
	err_ratenomcsub->Write();
	//	err_ratenomcsub->Draw();
	if(saveplots)cnomcsub->SaveAs(); 
	  
      }
      ///////////////////////////////////////////////////////////////////////////////////////
      ///
      /// Make plots with  W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////
      
      
      ofile << "--------------------------------------------------------------" << endl;
      ofile <<"Fake:: parameter " << mit->first << endl;
      ofile <<"Fake:: nbins=" << eff_all->GetNbinsX() << endl;
      
      
      TCanvas* c1 = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
      c1->Divide(1,2);
      c1->cd(1);
      if(mit->first.Contains("pt"))c1->SetLogx();
      TH1F* hratedenom = (TH1F*)eff_all->Clone(("hdenom" + hname).Data());
      TH1F* eff_rate = (TH1F*)eff_passed->Clone((region+hname).Data());
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      eff_rate->GetYaxis()->SetTitle(mit->second.second.Data());
      eff_rate->GetXaxis()->SetTitle((mit->second.first).Data());
      TH1F* errorhist = (TH1F*)eff_rate->Clone("error");
      eff_rate->Write();
      //      eff_rate->Draw();
      errorhist->SetFillStyle(3354);
      errorhist->SetFillColor(kBlack);
      //      errorhist->Draw("E2same");
      
      c1->cd(2);
      
      TH1F * err_rate = (TH1F*)eff_rate->Clone(("Err_" + region + mit->first).Data() );
      for(int ierrx=1 ; ierrx < err_rate->GetNbinsX()+1; ierrx++){
	double err = err_rate->GetBinError(ierrx);
	err_rate->SetBinContent(ierrx,err);
	ofile << "Bin Error " << ierrx << " : " <<  err_rate->GetBinLowEdge(ierrx) << "-" << eff_rate->GetBinLowEdge(ierrx+1) << " = " << err_rate->GetBinContent(ierrx) << endl;
      }
      eff_rate->GetYaxis()->SetRangeUser(0.,0.1);
      err_rate->Write();
      //      err_rate->Draw();
    }  
    
    cout << "Running 2D Fakes " << endl;


    for(map<TString,pair<TString,TString> >::iterator mit = fakeeffhists2D.begin(); mit!=fakeeffhists2D.end(); mit++){
      

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
      /// Make plots with no W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////

      if(makenoEWsubtraction){
	TCanvas* c2Dnomcsub = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
	c2Dnomcsub->Divide(1,2);
	c2Dnomcsub->cd(1);
	c2Dnomcsub->SetLogx();
	TH2F* hratedenom = (TH2F*)eff_all->Clone(("hdenom"+mit->first).Data());
	TH2F* eff_rate = (TH2F*)eff_passed->Clone((region+mit->first+"_nomcsub").Data());
	eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
	eff_rate->GetYaxis()->SetTitle(mit->second.second.Data());
	eff_rate->GetXaxis()->SetTitle((mit->second.first).Data());
	eff_rate->Write();
	//	eff_rate->Draw("colz");
	
	c2Dnomcsub->cd(2);
	
	TH2F * err_rate = (TH2F*)eff_rate->Clone(("Err_" + region + mit->first+"nomcsub").Data() );
	for(int ierrx=1 ; ierrx < err_rate->GetNbinsX()+1; ierrx++){
	  for(int ierry=1 ; ierry < err_rate->GetNbinsY()+1; ierry++){
	    double err = err_rate->GetBinError(ierrx,ierry);
	    err_rate->SetBinContent(ierrx,ierry,err);
	    ofile << "Bin Error " << ierrx << "," << ierry << " : = " << eff_rate->GetBinContent(ierrx,ierry) << ":"  <<  err_rate->GetBinContent(ierrx,ierry) << endl;
	  }
	}
	eff_rate->GetYaxis()->SetRangeUser(0.,0.1);
	//	err_rate->Draw("colz text");
	err_rate->Write();
      } 
   
      

      ///////////////////////////////////////////////////////////////////////////////////////
      ///
      /// Make plots with W/Z/ttbar subtraction
      ///
      ///////////////////////////////////////////////////////////////////////////////////////


      TH2F* testhratedenom = (TH2F*)eff_all->Clone(("testhdenom"+mit->first).Data());
      TH2F* testeff_rate = (TH2F*)eff_passed->Clone(("test" +region+mit->first).Data());
      testeff_rate->Divide(testeff_rate,testhratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      vector<float> effs;
      for(int x=1; x< testeff_rate->GetNbinsX()+1 ; x++ ){
	for(int y=1; y< testeff_rate->GetYaxis()->GetNbins()+1 ; y++ ){
	  effs.push_back(testeff_rate->GetBinContent(x,y));	  
	}
      }
      
      for(int x=1; x< eff_all->GetNbinsX()+1 ; x++ ){
	for(int y=1; y< eff_all->GetYaxis()->GetNbins()+1 ; y++ ){
	  float value_all = eff_all->GetBinContent(x,y);
	  float value_passed = eff_passed->GetBinContent(x,y);
	  float eff = value_passed/value_all;
	  
	  if(value_passed<0 || value_all < 0){
	    value_all += eff_all->GetBinContent(x+1,y);
	    value_all += eff_all->GetBinContent(x,y+1);
	    value_all=value_all/3.;
	    
	    value_passed += eff_passed->GetBinContent(x+1,y);
	    value_passed += eff_passed->GetBinContent(x,y+1);
	    value_passed = value_passed/3.;
	    
	    eff_all->SetBinContent(x,y,value_all);
	    eff_passed->SetBinContent(x,y,value_passed);
	  }
	  
	  ofile << "With MC subtraction :Bin " << x << "," << y << "  " <<eff_all->GetXaxis()->GetBinLowEdge(x) << "-"<< eff_all->GetXaxis()->GetBinLowEdge(x+1) <<"  : "  << eff_all->GetYaxis()->GetBinLowEdge(y) << "-"<< eff_all->GetYaxis()->GetBinLowEdge(y+1) <<   ":  Content =  " <<  eff << endl;
	}
      }
      
      
      TH2F* testmcshratedenom = (TH2F*)eff_all->Clone(("testmcshdenom"+mit->first).Data());
      TH2F* testmcseff_rate = (TH2F*)eff_passed->Clone(("testmcs" +region+mit->first).Data());
      testmcseff_rate->Divide(testmcseff_rate,testmcshratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      
      int n=0;
      for(int x=1; x< testmcseff_rate->GetNbinsX()+1 ; x++){
	for(int y=1; y< testmcseff_rate->GetYaxis()->GetNbins()+1 ; y++,n++ ){
	  ofile << x << " , " << y <<  " " << effs.at(n)  << " -> " <<  testmcseff_rate->GetBinContent(x,y) <<endl;
	}
      }
      

      TCanvas* c1 = new TCanvas(("Plot"+ mit->first).Data(), "Plot", 600, 600);
      c1->Divide(1,2);
      c1->cd(1);
      c1->SetLogx();
      TH2F* hratedenom = (TH2F*)eff_all->Clone(("hdenom"+mit->first).Data());
      TH2F* eff_rate = (TH2F*)eff_passed->Clone((region+mit->first).Data());
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      eff_rate->GetYaxis()->SetTitle(mit->second.second.Data());
      eff_rate->GetXaxis()->SetTitle((mit->second.first).Data());
      eff_rate->Write();
      //      eff_rate->Draw("colz");
      
      c1->cd(2);
      
      TH2F * err_rate = (TH2F*)eff_rate->Clone(("Err_" + region + mit->first).Data() );
      for(int ierrx=1 ; ierrx < err_rate->GetNbinsX()+1; ierrx++){
	for(int ierry=1 ; ierry < err_rate->GetNbinsY()+1; ierry++){
	  double err = err_rate->GetBinError(ierrx,ierry);
	  err_rate->SetBinContent(ierrx,ierry,err);
	  ofile << "Bin Error " << ierrx << "," << ierry << " : = " << eff_rate->GetBinContent(ierrx,ierry) << ":"  <<  err_rate->GetBinContent(ierrx,ierry) << endl;
	}
      }
      eff_rate->GetYaxis()->SetRangeUser(0.,0.1);
      //      err_rate->Draw("colz text");
      err_rate->Write();
    }  
    
  }
  
  ps.Close();    
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
