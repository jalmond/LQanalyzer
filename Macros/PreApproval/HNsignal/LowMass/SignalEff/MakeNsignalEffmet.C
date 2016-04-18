#include "Macro.h"
#include "CMS_lumi.h"
#include "TGraphAsymmErrors.h"


TH1* makeHist(TString m, TString hist, int col, int style);
TH1* makeRefHist(TString m);
TH1* makehist(TString hist);


void MakeNsignalEffmet(){
  
  setTDRStyle();
  gStyle->SetPalette(1);

  TH1* medium = makehist("PreSelection_medium_met");
  TH1* tight = makehist("PreSelection_tight_met");
  TH1* susy = makehist("PreSelection_susy_met");
  TH1* tight_dxy10 = makehist("PreSelection_iso_10_10_met");
  TH1* tight_anal = makehist("PreSelection_met");


  TLegend* legendH = new TLegend(0.7, 0.7, 0.9, 0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextSize(0.03);

  
  medium->GetXaxis()->SetTitle("m_{N} GeV");
  medium->GetYaxis()->SetTitle("ID efficiency");
  
  medium->SetMarkerColor(kRed);
  tight->SetMarkerColor(kRed);
  susy->SetMarkerColor(kRed);
  tight_dxy10->SetMarkerColor(kRed);
  tight_anal->SetMarkerColor(kRed);
  
  medium->SetMarkerStyle(20.);
  susy->SetMarkerStyle(24.);
  tight->SetMarkerStyle(21.);
  tight_dxy10->SetMarkerStyle(22.);
  tight_anal->SetMarkerStyle(23.);

  legendH->AddEntry(medium, "medium ID", "p");
  legendH->AddEntry(tight, "tight ID", "p");
  legendH->AddEntry(susy, "susy ID", "p");
  legendH->AddEntry(tight_dxy10, "tight+ dxy ", "p");
  legendH->AddEntry(tight_anal, "tight+ dxy+ iso ", "p");

  medium->Draw("p");
  tight->Draw("psame");
  susy->Draw("psame");
  tight_dxy10->Draw("psame");
  tight_anal->Draw("psame");
  legendH->Draw();

  TGraphAsymmErrors * g = new TGraphAsymmErrors(heff);
  g->SetLineWidth(2.0);
  g->SetMarkerSize(2.);
  //  g->Draw( "9pXsame" );
  
  
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();
  
  
  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/SignalPlots/SignalEff_presel_med_met.pdf" ));
}


TH1* makehist(TString hist){
  TH1* hn_40 = makeHist("40",hist, 414,0);
  TH1* hn_50 = makeHist("50",hist,402,0);
  TH1* hn_60 = makeHist("60",hist,616,0);
  TH1* hn_70 = makeHist("70",hist,432,0);
  TH1* hn_80 = makeHist("80",hist,600,0);
  /*TH1* hn_90 = makeHist("90",hist,600,0);
  TH1* hn_100 = makeHist("100",hist,600,0);
  TH1* hn_200 = makeHist("200",hist,600,0);
  TH1* hn_300 = makeHist("300",hist,600,0);
  TH1* hn_500 = makeHist("500",hist,600,0);*/

  TH1* href_40 = makeRefHist("40");
  TH1* href_50 = makeRefHist("50");
  TH1* href_60 = makeRefHist("60");
  TH1* href_70 = makeRefHist("70");
  TH1* href_80 = makeRefHist("80");
  /*  TH1* href_90 = makeRefHist("90");
  TH1* href_100 = makeRefHist("100");
  TH1* href_200 = makeRefHist("200");
  TH1* href_300 = makeRefHist("300");
  TH1* href_500 = makeRefHist("500");*/

  TH1F* heff = new TH1F("heff","heff", 10, 0., 10.);
  heff->SetBinContent(1, (hn_40->GetBinContent(2)/href_40->GetBinContent(2)));
  heff->SetBinContent(2, (hn_50->GetBinContent(2)/href_50->GetBinContent(2)));
  heff->SetBinContent(3, (hn_60->GetBinContent(2)/href_60->GetBinContent(2)));
  heff->SetBinContent(4, (hn_70->GetBinContent(2)/href_70->GetBinContent(2)));
  heff->SetBinContent(5, (hn_80->GetBinContent(2)/href_80->GetBinContent(2)));
  /*heff->SetBinContent(6, (hn_90->GetBinContent(2)/href_90->GetBinContent(2)));
  heff->SetBinContent(7, (hn_100->GetBinContent(2)/href_100->GetBinContent(2)));
  heff->SetBinContent(8, (hn_200->GetBinContent(2)/href_200->GetBinContent(2)));
  heff->SetBinContent(9, (hn_300->GetBinContent(2)/href_300->GetBinContent(2)));
  heff->SetBinContent(10, (hn_500->GetBinContent(2)/href_500->GetBinContent(2)));*/

  heff->GetXaxis()->SetBinLabel(1,"40");
  heff->GetXaxis()->SetBinLabel(2,"50");
  heff->GetXaxis()->SetBinLabel(3,"60");
  heff->GetXaxis()->SetBinLabel(4,"70");
  heff->GetXaxis()->SetBinLabel(5,"80");
  /*heff->GetXaxis()->SetBinLabel(6,"90");
  heff->GetXaxis()->SetBinLabel(7,"100");
  heff->GetXaxis()->SetBinLabel(8,"200");
  heff->GetXaxis()->SetBinLabel(9,"300");*/

  
  return heff;
}


TH1* makeHist(TString m, TString hist,  int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + m + "_nocut_5_3_14.root";

  cout << hist << endl;
  TFile* file = new TFile(path);
  TH1* h = (TH1*)file->Get(hist);

  cout << h << endl;
  return h;
}


TH1* makeRefHist(TString m){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + m + "_nocut_5_3_14.root";
  
  TFile* file = new TFile(path);
  TH1* h = (TH1*)file->Get("eff_electronRef");
  return h;
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







