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
bool CheckFile(TFile* f);
bool CheckHist(TH2* h);


void MakeFRRootFile(){
  
  TString path= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/";


  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  
  vector<TString> hist_ptcut;

  hist_ptcut.push_back("Tight");
  hist_ptcut.push_back("Medium");
  hist_ptcut.push_back("Loosedxy01_100_100");
  hist_ptcut.push_back("Loosedxy01_009_009");
  hist_ptcut.push_back("Loosedxy01_009_008");
  hist_ptcut.push_back("Loosedxy01_009_007");
  hist_ptcut.push_back("Loosedxy01_009_006");
  hist_ptcut.push_back("Loosedxy01_009_005");
  
  hist_ptcut.push_back("Loosedxy01_009_009_np");
  hist_ptcut.push_back("Loosedxy01_009_008_np");
  hist_ptcut.push_back("Loosedxy01_009_007_np");
  hist_ptcut.push_back("Loosedxy01_009_006_np");
  hist_ptcut.push_back("Loosedxy01_009_005_np");
  
  hist_ptcut.push_back("dxy05");
  hist_ptcut.push_back("dxy10");
  hist_ptcut.push_back("dxy15");
  hist_ptcut.push_back("dxy20");
  hist_ptcut.push_back("dxy25");
  hist_ptcut.push_back("dxy30");

  hist_ptcut.push_back("iso_B050_E060_dr03");
  hist_ptcut.push_back("iso_B050_E070_dr03");
  hist_ptcut.push_back("iso_B050_E080_dr03");
  hist_ptcut.push_back("iso_B050_E090_dr03");
  hist_ptcut.push_back("iso_B050_E100_dr03");
  hist_ptcut.push_back("iso_B050_E125_dr03");
  hist_ptcut.push_back("iso_B070_E050_dr03");
  hist_ptcut.push_back("iso_B070_E060_dr03");
  hist_ptcut.push_back("iso_B070_E080_dr03");
  hist_ptcut.push_back("iso_B070_E090_dr03");
  hist_ptcut.push_back("iso_B070_E100_dr03");
  hist_ptcut.push_back("iso_B070_E125_dr03");
  hist_ptcut.push_back("iso_B080_E050_dr03");
  hist_ptcut.push_back("iso_B080_E060_dr03");
  hist_ptcut.push_back("iso_B080_E070_dr03");
  hist_ptcut.push_back("iso_B080_E090_dr03");
  hist_ptcut.push_back("iso_B080_E100_dr03");
  hist_ptcut.push_back("iso_B080_E125_dr03");
  hist_ptcut.push_back("iso_B090_E050_dr03");
  hist_ptcut.push_back("iso_B090_E060_dr03");
  hist_ptcut.push_back("iso_B090_E070_dr03");
  hist_ptcut.push_back("iso_B090_E080_dr03");
  hist_ptcut.push_back("iso_B090_E100_dr03");
  hist_ptcut.push_back("iso_B090_E125_dr03");
  hist_ptcut.push_back("iso_B100_E050_dr03");
  hist_ptcut.push_back("iso_B100_E060_dr03");
  hist_ptcut.push_back("iso_B100_E070_dr03");
  hist_ptcut.push_back("iso_B100_E080_dr03");
  hist_ptcut.push_back("iso_B100_E090_dr03");
  hist_ptcut.push_back("iso_B100_E125_dr03");
  hist_ptcut.push_back("iso_B125_E050_dr03");
  hist_ptcut.push_back("iso_B125_E060_dr03");
  hist_ptcut.push_back("iso_B125_E070_dr03");
  hist_ptcut.push_back("iso_B125_E080_dr03");
  hist_ptcut.push_back("iso_B125_E090_dr03");
  hist_ptcut.push_back("iso_B125_E100_dr03");
  hist_ptcut.push_back("iso_B150_E050_dr03");
  hist_ptcut.push_back("iso_B150_E060_dr03");
  hist_ptcut.push_back("iso_B150_E070_dr03");
  hist_ptcut.push_back("iso_B150_E080_dr03");
  hist_ptcut.push_back("iso_B150_E090_dr03");
  hist_ptcut.push_back("iso_B150_E100_dr03");
  hist_ptcut.push_back("iso_B150_E125_dr03");
    hist_ptcut.push_back("iso_B050_E050_dr04");
  hist_ptcut.push_back("iso_B060_E060_dr04");
  hist_ptcut.push_back("iso_B070_E070_dr04");
  hist_ptcut.push_back("iso_B080_E080_dr04");
  hist_ptcut.push_back("iso_B090_E090_dr04");
  hist_ptcut.push_back("iso_B100_E100_dr04");
  hist_ptcut.push_back("iso_B125_E125_dr04");
  hist_ptcut.push_back("iso_B150_E150_dr04");
  hist_ptcut.push_back("iso_B050_E050_dr03");
  hist_ptcut.push_back("iso_B060_E060_dr03");
  hist_ptcut.push_back("iso_B070_E070_dr03");
  hist_ptcut.push_back("iso_B080_E080_dr03");
  hist_ptcut.push_back("iso_B090_E090_dr03");
  hist_ptcut.push_back("iso_B100_E100_dr03");
  hist_ptcut.push_back("iso_B125_E125_dr03");
  hist_ptcut.push_back("iso_B150_E150_dr03");


  hist_ptcut.push_back("NPFiso_B050_E060_dr03");
  hist_ptcut.push_back("NPFiso_B050_E070_dr03");
  hist_ptcut.push_back("NPFiso_B050_E080_dr03");
  hist_ptcut.push_back("NPFiso_B050_E090_dr03");
  hist_ptcut.push_back("NPFiso_B050_E100_dr03");
  hist_ptcut.push_back("NPFiso_B050_E125_dr03");
  hist_ptcut.push_back("NPFiso_B070_E050_dr03");
  hist_ptcut.push_back("NPFiso_B070_E060_dr03");
  hist_ptcut.push_back("NPFiso_B070_E080_dr03");
  hist_ptcut.push_back("NPFiso_B070_E090_dr03");
  hist_ptcut.push_back("NPFiso_B070_E100_dr03");
  hist_ptcut.push_back("NPFiso_B070_E125_dr03");
  hist_ptcut.push_back("NPFiso_B080_E050_dr03");
  hist_ptcut.push_back("NPFiso_B080_E060_dr03");
  hist_ptcut.push_back("NPFiso_B080_E070_dr03");
  hist_ptcut.push_back("NPFiso_B080_E090_dr03");
  hist_ptcut.push_back("NPFiso_B080_E100_dr03");
  hist_ptcut.push_back("NPFiso_B080_E125_dr03");
  hist_ptcut.push_back("NPFiso_B090_E050_dr03");
  hist_ptcut.push_back("NPFiso_B090_E060_dr03");
  hist_ptcut.push_back("NPFiso_B090_E070_dr03");
  hist_ptcut.push_back("NPFiso_B090_E080_dr03");
  hist_ptcut.push_back("NPFiso_B090_E100_dr03");
  hist_ptcut.push_back("NPFiso_B090_E125_dr03");
  hist_ptcut.push_back("NPFiso_B100_E050_dr03");
  hist_ptcut.push_back("NPFiso_B100_E060_dr03");
  hist_ptcut.push_back("NPFiso_B100_E070_dr03");
  hist_ptcut.push_back("NPFiso_B100_E080_dr03");
  hist_ptcut.push_back("NPFiso_B100_E090_dr03");
  hist_ptcut.push_back("NPFiso_B100_E125_dr03");
  hist_ptcut.push_back("NPFiso_B125_E050_dr03");
  hist_ptcut.push_back("NPFiso_B125_E060_dr03");
  hist_ptcut.push_back("NPFiso_B125_E070_dr03");
  hist_ptcut.push_back("NPFiso_B125_E080_dr03");
  hist_ptcut.push_back("NPFiso_B125_E090_dr03");
  hist_ptcut.push_back("NPFiso_B125_E100_dr03");
  hist_ptcut.push_back("NPFiso_B150_E050_dr03");
  hist_ptcut.push_back("NPFiso_B150_E060_dr03");
  hist_ptcut.push_back("NPFiso_B150_E070_dr03");
  hist_ptcut.push_back("NPFiso_B150_E080_dr03");
  hist_ptcut.push_back("NPFiso_B150_E090_dr03");
  hist_ptcut.push_back("NPFiso_B150_E100_dr03");
  hist_ptcut.push_back("NPFiso_B150_E125_dr03");
  
  TString outfile = "FakeRateOpt.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  for(vector<TString>::iterator it2 = hist_ptcut.begin(); it2!=hist_ptcut.end(); ++it2){
      int rebin=1;
      cout << *it2 << endl;
      if(!CheckFile(fdata))return;      
      TH2F* h_pt_num= (TH2F*)fdata->Get(("h_promptrate_"+ *it2+ "_num_pt_eta").Data());
      TH2F* h_pt_denom= (TH2F*)fdata->Get(("h_promptrate_"+ *it2+"_denom_pt_eta").Data());
      CheckHist(h_pt_denom);
      CheckHist(h_pt_num);

      
      TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("RealEff_" + *it2 ).Data());
      TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
      
      
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      

      eff_rate->Write();

  }
	
  
  vector<TString> fakes;
  fakes.push_back("Tight_dxy05_El40_pt_eta");
  fakes.push_back("Tight_dxy10_El40_pt_eta");
  fakes.push_back("Tight_dxy15_El40_pt_eta");
  fakes.push_back("Tight_dxy20_El40_pt_eta");
  fakes.push_back("Tight_dxy25_El40_pt_eta");
  fakes.push_back("Tight_dxy30_El40_pt_eta");
  
  fakes.push_back("Tight_iso_dr3_b150_e150_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b060_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e050_pt_eta");

  fakes.push_back("Tight_iso_dr4_b150_e150_pt_eta");
  fakes.push_back("Tight_iso_dr4_b125_e125_pt_eta");
  fakes.push_back("Tight_iso_dr4_b100_e100_pt_eta");
  fakes.push_back("Tight_iso_dr4_b090_e090_pt_eta");
  fakes.push_back("Tight_iso_dr4_b080_e080_pt_eta");
  fakes.push_back("Tight_iso_dr4_b070_e070_pt_eta");
  fakes.push_back("Tight_iso_dr4_b060_e060_pt_eta");
  fakes.push_back("Tight_iso_dr4_b050_e050_pt_eta");

  fakes.push_back("Tight_iso_dr3_b150_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b150_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b125_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b100_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b090_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b080_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e060_pt_eta");
  fakes.push_back("Tight_iso_dr3_b070_e050_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e125_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e100_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e090_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e080_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e070_pt_eta");
  fakes.push_back("Tight_iso_dr3_b050_e060_pt_eta");

  fakes.push_back("Tight_tight_pt_eta");

  fakes.push_back("Tight_iso_NPFisodr3_b150_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b150_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b125_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b100_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b090_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b080_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e060_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b070_e050_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e125_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e100_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e090_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e080_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e070_pt_eta");
  fakes.push_back("Tight_iso_NPFisodr3_b050_e060_pt_eta");

  
  vector<TString> fakes2;
  fakes2.push_back("Tight_medium_pt_eta");
  for(vector<TString>::iterator it2 = fakes.begin(); it2!=fakes.end(); ++it2){
    cout << *it2 << endl;
    if(!CheckFile(fdata))return;
    if(!CheckFile(fmc))return;

    TString denom ="LooseOpt_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(it2->Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(it2->Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);
    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }


  for(vector<TString>::iterator it2 = fakes2.begin(); it2!=fakes2.end(); ++it2){
    cout << *it2 << endl;
    if(!CheckFile(fdata))return;
    if(!CheckFile(fmc))return;

    TString denom ="LooseOpt_medium_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(it2->Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(it2->Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);
    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }
  vector<TString> fakes3;
  fakes3.push_back("Tight_iso_dr3_b100_e100_pt_eta");
  fakes3.push_back("Tight_iso_dr3_b090_e090_pt_eta");
  fakes3.push_back("Tight_iso_dr3_b090_e080_pt_eta");
  fakes3.push_back("Tight_iso_dr3_b090_e070_pt_eta");
  fakes3.push_back("Tight_iso_dr3_b090_e060_pt_eta");
  fakes3.push_back("Tight_iso_dr3_b090_e050_pt_eta");
  fakes3.push_back("Tight_iso_NPFisodr3_b090_e080_pt_eta");
  fakes3.push_back("Tight_iso_NPFisodr3_b090_e070_pt_eta");
  fakes3.push_back("Tight_iso_NPFisodr3_b090_e060_pt_eta");
  fakes3.push_back("Tight_iso_NPFisodr3_b090_e050_pt_eta");
  

  for(vector<TString>::iterator it2 = fakes3.begin(); it2!=fakes3.end(); ++it2){
    cout << *it2 << endl;
    if(!CheckFile(fdata))return;
    if(!CheckFile(fmc))return;

    TString denom ="Loosedxy01_pt_eta";
    TH2F* h_pt_num= (TH2F*)fdata->Get(it2->Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(it2->Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);
    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_Loosedxy01_" + *it2).Data()); 
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }


  /// 
  std::vector<TString> fakes40;
  fakes40.push_back("_noclose_20_pt_eta");
  fakes40.push_back("_close_20_pt_eta");
  fakes40.push_back("_noclose_bjet_20_pt_eta");
  fakes40.push_back("_noclose_40_pt_eta");
  fakes40.push_back("_close_40_pt_eta");

  for(vector<TString>::iterator it2 = fakes40.begin(); it2!=fakes40.end(); ++it2){
    cout << *it2 << endl;
    if(!CheckFile(fdata))return;
    if(!CheckFile(fmc))return;

    TString denom ="LooseEl" + *it2;
    TString num ="TightEl" + *it2;
    TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
    TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());
    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
    TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());
    CheckHist(h_mcpt_denom);
    CheckHist(h_mcpt_num);

    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone((*it2 +"_denom").Data());
    eff_rate->Add(h_mcpt_num,-1.);
    hratedenom->Add(h_mcpt_denom, -1.);
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
    eff_rate->Write();
  }


  
}

  
bool CheckFile(TFile* f ){
    bool file_exist = true;
    if(!f){
      cout << "File " << f->GetName() << " does not exist. Exiting " << endl;
      file_exist = false;
    }
    
    return file_exist;
}

bool CheckHist(TH2* h ){
  bool hist_exist = true;
  if(!h){
    cout << "No histogram with name " << h->GetName() << endl;
    hist_exist= false;
  }
  return hist_exist;
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

