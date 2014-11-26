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


Bool_t reject;

Double_t CrystalBall(Double_t *x,Double_t *par) {

  Double_t t = (x[0]-par[2])/par[3];
  if (par[0] < 0) t = -t;

  Double_t absAlpha = fabs((Double_t)par[0]);

  if (t >= -absAlpha) {
    return par[4]*exp(-0.5*t*t);
  }
  else {
    Double_t a =  TMath::Power(par[1]/absAlpha,par[1])*exp(-0.5*absAlpha*absAlpha);
    Double_t b= par[1]/absAlpha - absAlpha; 

    return par[4]*(a/TMath::Power(b - t, par[1]));
  }
}

//Exponential background excluding the signal area

Double_t Background(Double_t *x, Double_t *par)
{
  if (reject && x[0] > 71. && x[0] < 111.) {
    TF1::RejectPoint();
    return 0;
  }
  return exp(par[0] + (x[0]*par[1]));
}

void CalTPEfficiency_test(){


  TH1::SetDefaultSumw2(true);
  setTDRStyle();
  

  TString MCPath = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronSF/ElectronSF_SKDY50plus_5_3_14.root";
  TString DataPath = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronSF/ElectronSF_data_5_3_14.root";
  
  TFile *f_MC = new TFile(MCPath);    //! Drell-Yan MC sample Z-> ee
  TFile *f_Data = new TFile(DataPath);
  
  vector<TString> etaregion;
  etaregion.push_back("eta1");
  //etaregion.push_back("eta2");
  //etaregion.push_back("eta3");
  //etaregion.push_back("eta4");

  for(unsigned int ieta = 0; ieta < etaregion.size(); ieta++){
    
    TCanvas* c1 = new TCanvas(("Plot" + etaregion.at(ieta)), "Plot", 1600, 1200);
    c1->cd();

    
    TH1* h_mc_n = (TH1*)f_MC->Get("Num_" + etaregion.at(ieta) + "_pt");
    TH1* h_mc_d = (TH1*)f_MC->Get("Den_" + etaregion.at(ieta) + "_pt");
    
    
    h_mc_n->Divide(h_mc_d);
    
    TH1* h_data_eff = (TH1*)h_mc_n->Clone("DATA");
    
    vector<TString> ptregion;
    ptregion.push_back("pt1");
    /*ptregion.push_back("pt2");
    ptregion.push_back("pt3");
    ptregion.push_back("pt4");
    ptregion.push_back("pt5");
    ptregion.push_back("pt6");*/
    for(unsigned int ipt= 0; ipt < ptregion.size(); ipt++){
      TCanvas* cpt = new TCanvas(("Plot" + etaregion.at(ieta) + ptregion.at(ipt) ), "Plot", 1600, 1200);
      TCanvas* cpt2 = new TCanvas(("Plot2" + etaregion.at(ieta) + ptregion.at(ipt) ), "Plot", 1600, 1200);
      
      TH1* h_mc_pteta_n = (TH1*)f_MC->Get("Num_" + etaregion.at(ieta)+ "_" + ptregion.at(ipt) +  "_mass");
      TH1* h_mc_pteta_d = (TH1*)f_MC->Get("Den_" + etaregion.at(ieta) + "_"+ ptregion.at(ipt) + "_mass");
      
      TH1* h_data_pteta_n = (TH1*)f_Data->Get("Num_" + etaregion.at(ieta)+ "_" + ptregion.at(ipt) +  "_mass");
      TH1* h_data_pteta_d = (TH1*)f_Data->Get("Den_" + etaregion.at(ieta) + "_"+ ptregion.at(ipt) + "_mass");
      
      cpt->cd();
      TF1 *func = new TF1("func",Background,60,70,2);
      func->SetParameter(0,8.);
      func->SetParameter(1,-0.07);
      func->SetParNames("slope");
      func->SetParNames("slope2");
      
      reject = kTRUE;

      for(int i=0;i<100;i++)h_data_pteta_n->Fit("func");
      reject = kFALSE;
      return;
       
      TF1 *crystal = new TF1("crystal",CrystalBall,71.,111.,5);
      //crystal->SetParameters(1e8,1,91.,10.,h_data_pteta_n->GetBinContent(91));
      crystal->SetParameters(10.,10.,10.,10.,10.);
      crystal->SetParNames("#alpha","n","Mean","#sigma","N");
      
      for(int i=0;i<10000;i++) h_data_pteta_n->Fit(crystal,"RM");
      
      h_data_pteta_n->Draw();
      
      crystal->SetLineColor(kBlue);
      crystal->SetLineStyle(kDashed);
      func->Draw("same");

      crystal->Draw("same");


      cpt->SaveAs(("/home/jalmond/WebPlots/TandP/SF/numerator_"  + etaregion.at(ieta) +  ptregion.at(ipt) + ".pdf"));

      
    }

    h_mc_n->SetLineColor(kBlue-4);
    h_mc_n->SetFillColor(kBlue-4);
    h_mc_n->SetLineWidth(0.3);
    h_mc_n->SetMarkerStyle(22);

    h_mc_n->Draw("p");
    
    h_data_eff->Draw("same");
    
    TLegend* legendH = new TLegend(0.6, 0.7, 0.9, 0.9);
    legendH->SetFillColor(kWhite);
    legendH->SetTextFont(42);
    legendH->SetTextSize(0.03);

    legendH->AddEntry(h_mc_n, "Simulation DY: Tight", "fp");
    legendH->Draw();

    CMS_lumi( c1, 2, 11 );
    c1->Update();
    c1->RedrawAxis();
    
    
    c1->SaveAs(("/home/jalmond/WebPlots/TandP/SF/"  + etaregion.at(ieta)  + ".pdf"));
    
  }
}

CMS_lumi( TPad* pad, int iPeriod, int iPosX )
{
  bool outOfFrame    = false;
  if( iPosX/10==0 )
    {
      outOfFrame = true;
    }
  int alignY_=3;
  int alignX_=2;
  if( iPosX/10==0 ) alignX_=1;
  if( iPosX==0    ) alignY_=1;
  if( iPosX/10==1 ) alignX_=1;
  if( iPosX/10==2 ) alignX_=2;
  if( iPosX/10==3 ) alignX_=3;
  int align_ = 10*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  TString lumiText;
  if( iPeriod==1 )
    {
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==2 )
    {
      lumiText += " (8 TeV)";
    }
  else if( iPeriod==3 )
    {
      lumiText = lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
    }
  else if ( iPeriod==4 )
    {
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
    }
  else if ( iPeriod==7 )
    {
      if( outOfFrame ) lumiText += "#scale[0.85]{";
      lumiText += lumi_13TeV;
      lumiText += " (13 TeV)";
      lumiText += " + ";
      lumiText += lumi_8TeV;
      lumiText += " (8 TeV)";
      lumiText += " + ";
      lumiText += lumi_7TeV;
      lumiText += " (7 TeV)";
      if( outOfFrame) lumiText += "}";
    }
  else if ( iPeriod==12 )
    {
      lumiText += "8 TeV";
    }

  cout << lumiText << endl;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31);
  latex.SetTextSize(lumiTextSize*t);
  latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText);

  if( outOfFrame )
    {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextAlign(11);
      latex.SetTextSize(cmsTextSize*t);
      latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
    }
  pad->cd();

  float posX_;
  if( iPosX%10<=1 )
    {
      posX_ =   l + relPosX*(1-l-r);
    }
  else if( iPosX%10==2 )
    {
      posX_ =  l + 0.5*(1-l-r);
    }
  else if( iPosX%10==3 )
    {
      posX_ =  1-r - relPosX*(1-l-r);
    }
  float posY_ = 1-t - relPosY*(1-t-b);
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = 1-t - 0.045*(1-t-b);
          float xl_0 = posX_;
          float yl_0 = posY_ - 0.15;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, posY_, cmsText);
          if( writeExtraText )
            {
              latex.SetTextFont(extraTextFont);
              latex.SetTextAlign(align_);
              latex.SetTextSize(extraTextSize*t);
              latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
            }
        }
    }
  else if( writeExtraText )
    {
      if( iPosX==0)
        {
          posX_ =   l +  relPosX*(1-l-r);
          posY_ =   1-t+lumiTextOffset*t;
        }
      latex.SetTextFont(extraTextFont);
      latex.SetTextSize(extraTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, extraText);
    }
  return;
}
