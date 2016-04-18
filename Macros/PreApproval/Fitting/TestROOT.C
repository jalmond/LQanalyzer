#include "Macro.h"
#include "CMS_lumi.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TFitResult.h"
#include <iostream>
#include "TMath.h"
#include "Riostream.h"
#include <math.h>
#include "TStyle.h"
#include "TCanvas.h"
#include <TROOT.h>

using std::endl;
using std::cout;
using std::string;

Double_t FuncMC(Double_t *x, Double_t *par);
Double_t FuncZ(Double_t *x, Double_t *par);
Double_t FuncZ2(Double_t *x, Double_t *par);
Double_t FunBkg1(Double_t *x, Double_t *par);
Double_t FunBkg2(Double_t *x, Double_t *par);
Double_t FunBkg(Double_t *x, Double_t *par);
Double_t FunTot(Double_t *x, Double_t *par);

void TestROOT(){
  
  //ROOT::Math::MinimizerOptions::SetMaxFunctionCalls(100);
  //ROOT::Math::MinimizerOptions::SetMaxIterations(100);

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  
  //----------------------------------------------------
  // Open file
  //----------------------------------------------------
  TString DataPath = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronSF/ElectronSF_data_5_3_14.root";
  TString MCPath = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronSF/ElectronSF_SKDY50plus_5_3_14.root ";

  TFile *f = new TFile(DataPath);
  TFile *fmc = new TFile(DataPath);
  TH1F *histo = (TH1F*) f->Get("Den_eta1_pt1_mass"); 
  TH1F *histoMC = (TH1F*) fmc->Get("Den_eta1_pt1_mass"); 
  TCanvas *c = new TCanvas("c","c",20,20,600,600);
  //----------------------------------------------------
  // Fit the invariant mass spectrum // with a Crystal Ball function
  //+ double exponential
  
  //----------------------------------------------------
  Double_t FitMin==80., FitMax=100.; 
  TF1 *func_mc = new TF1("funcmc",FuncMC,FitMin,FitMax,5);
  
  func_mc->SetParameter(0,histoMC->GetBinContent(histoMC->FindBin(91.))); // Z normalization                                      
  func_mc->SetParameter(1,91.);       // Z mass position                        
  func_mc->SetParameter(2,3.);        // Z width                             
  func_mc->SetParameter(3,0.5);        // Crystal Ball tails                             
  func_mc->SetParameter(4,0.5);         // Crystal Ball tails      
 
  for(int i=0; i < 100; i++) histoMC->Fit(func_mc,"RIWLM");
  histoMC->Draw("e");
  
  c->SaveAs("FitMC.pdf");

  return;
  //TF1 *functot = new TF1("functot",FuncTot,FitMin,FitMax,9);
  TF1 *functot = new TF1("functot",FuncTot,60., 120.,9);
  functot->SetParameter(0,5.425808);   // background parameters
  functot->SetParameter(1,-1.282635);   // background parameters
  functot->SetParameter(2,6.466449);    // background parameters
  functot->SetParameter(3,-0.559789);   // background parameters
  functot->SetParameter(4,histo->GetBinContent(histo->FindBin(91.))); // Z normalization
  functot->SetParameter(5,91.);       // Z mass position
  functot->SetParameter(6,func_mc->GetParameter(2));        // Z width
  functot->SetParameter(7,func_mc->GetParameter(3));        // Crystal Ball tails
  functot->SetParameter(8,func_mc->GetParameter(4));         // Crystal Ball tails
  functot->SetLineColor(kBlue);
  functot->SetLineWidth(2);
  
  //  for(int i=0; i < 100; i++)histo->Fit(functot,"RILSM");

  TFitResultPtr r = histo->Fit(functot,"RILSM");
  cout << "Status = " << int(r) << endl;
  
  TMatrixDSym cov = r->GetCovarianceMatrix();
  Double_t *fullmat;
  fullmat = cov.GetMatrixArray();
  Double_t psimat[25];
  for(Int_t i=0;i<5;i++){
    for(Int_t j=0;j<5;j++) psimat[5*i+j]=fullmat[40+j+9*i];
  }
  
  histo->GetXaxis()->SetRangeUser(60.,120.);
  histo->SetMinimum(1.);
  //gPad->SetLogy(1);
  histo->Draw("e");
  histo->SetMarkerStyle(20);
  histo->SetMarkerColor(2);
  histo->SetMarkerSize(0.7);
  
  TF1 *psifix = new TF1("psifix",FuncZ,60.,120.,9);

  for(int i=0;i<9;i++) psifix->SetParameter(i,functot->GetParameter(i));
  psifix->SetLineColor(kGreen);
  psifix->Draw("same");
  Double_t binWidth= histo->GetBinWidth(1);
  Double_t NZ=psifix->Integral(60.,120.)/binWidth;
  
  TF1 *psifix2 = new TF1("psifix2",FuncZ2,0.,5.,5); 

  for(int  i=0;i<5;i++) psifix2->SetParameter(i,functot->GetParameter(i+4));
  Double_t psipar[5];
  for(int i=0;i<5;i++) psipar[i]=functot->GetParameter(4+i);
  Double_t ErrPsiCorrParam = psifix2->IntegralError(0.,5.,psipar,psimat)/binWidth;
  
  cout << "N_{Z} = " << NZ << endl;

  c->SaveAs("Fit.pdf");
}

Double_t FuncZ(Double_t *x, Double_t *par){  //Crystal Ball
  Double_t FitZ;
  Double_t t = (x[0]-par[5])/par[6];
  if (t > (-par[7])){
    FitZ = par[4]*TMath::Exp(-t*t/2.);
  } else if (t <= (-par[7])) {
    Double_t AA =
      TMath::Power(par[8]/TMath::Abs(par[7]),par[8])*TMath::Exp(-TMath::Abs(par[7])*TMath::Abs(par[7])/2.);
    
    Double_t BB = par[8]/TMath::Abs(par[7])-TMath::Abs(par[7]);
    if(TMath::Power((BB-t),par[8])!=0){
      FitZ = par[4]*AA/TMath::Power((BB-t),par[8]);
    } else   FitZ = 0;
  }     return FitZ;
}

Double_t FuncZ2(Double_t *x, Double_t *par){  //Crystal Ball
  Double_t FitZ2;
  Double_t t = (x[0]-par[1])/par[2];
  if (t > (-par[3])){
    FitZ2 = par[0]*TMath::Exp(-t*t/2.);
  } else if (t <= (-par[3])) {
    Double_t AA =
      TMath::Power(par[4]/TMath::Abs(par[3]),par[4])*TMath::Exp(-TMath::Abs(par[3])*TMath::Abs(par[3])/2.);
    
    Double_t BB = par[4]/TMath::Abs(par[3])-TMath::Abs(par[3]);
    if(TMath::Power((BB-t),par[4])!=0){
      FitZ2 = par[0]*AA/TMath::Power((BB-t),par[4]);
    } else   FitZ2 = 0;
  }     return FitZ2;
}

Double_t FuncBck1(Double_t *x, Double_t *par){  //exponential
  Double_t FitBck1 = exp(par[0]+par[1]*x[0]);
  return FitBck1;
}
Double_t FuncBck2(Double_t *x, Double_t *par){  //exponential
  Double_t FitBck2 = exp(par[2]+par[3]*x[0]);
  return FitBck2;
}

Double_t FuncBck(Double_t *x, Double_t *par){  //exponential
  return FuncBck1(x,par);//+FuncBck2(x,par);
}

Double_t FuncTot(Double_t *x, Double_t *par){  // total fit
  return FuncBck(x,par)+FuncZ(x,par);
}

Double_t FuncMC(Double_t *x, Double_t *par){  // total fit
  return FuncZ2(x,par);
}

