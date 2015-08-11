#include "Macro.h"
#include "CMS_lumi.h"
#include "TGraphAsymmErrors.h"

void GetRes2(){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  
  TString spath_50 = "/home/jalmond/Analysis/LQanalyzer/data/output/Muon/ExampleAnalyzerDiMuon_SKHNmumu50_nocut_5_3_14.root";
  TString spath_60 = "/home/jalmond/Analysis/LQanalyzer/data/output/Muon/ExampleAnalyzerDiMuon_SKHNmumu60_nocut_5_3_14.root";
  TString spath_100 = "/home/jalmond/Analysis/LQanalyzer/data/output/Muon/ExampleAnalyzerDiMuon_SKHNmumu100_nocut_5_3_14.root";
  TString spath_300 = "/home/jalmond/Analysis/LQanalyzer/data/output/Muon/ExampleAnalyzerDiMuon_SKHNmumu300_nocut_5_3_14.root";

  
  TFile * _file_50 = new TFile(spath_50);
  TFile * _file_60 = new TFile(spath_60);
  TFile * _file_100 = new TFile(spath_100);
  TFile * _file_300 = new TFile(spath_300);
 
  TH1* h_res_50 = (TH1*)_file_50->Get("NMass_50");
  TH1* h_res_60 = (TH1*)_file_60->Get("NMass_60");
  TH1* h_res_100 = (TH1*)_file_100->Get("NMass_100");
  TH1* h_res_300 = (TH1*)_file_300->Get("NMass_300");

  h_res_50->Rebin(10);
  h_res_60->Rebin(10);
  h_res_100->Rebin(8);
  h_res_300->Rebin(8);
  h_res_50->SetLineColor(kRed);
  h_res_60->SetLineColor(kBlue);
  h_res_100->SetLineColor(kCyan);
  h_res_300->SetLineColor(kOrange);

  h_res_100->GetYaxis()->SetTitle("");
  h_res_100->GetXaxis()->SetTitle("m_{N} GeV");
  h_res_100->GetYaxis()->SetRangeUser(0., 0.2);
  h_res_100->Scale(1./ h_res_100->Integral());
  h_res_300->Scale(1./ h_res_300->Integral());


  h_res_100->GetYaxis()->SetRangeUser(0., 0.2);
  h_res_100->Draw("hist");
  h_res_300->Draw("histsame");

  
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();

 
 
  TLegend* legendH = new TLegend(0.6,0.2,0.8,0.4);
  legendH->SetFillColor(kWhite);
  legendH->SetTextFont(42);
  legendH->AddEntry(h_res_100, "m_N = 100 GeV", "l");
  legendH->AddEntry(h_res_300, "m_N = 300 GeV", "l");
  legendH->Draw();
  
  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Res/MuonHN_res_100_300.pdf"));
  

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
  float posY_ = 1-t+lumiTextOffset*t;
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = t;
          float xl_0 = posX_;
          float yl_0 = posY_ ;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          /*TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();*/
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, 0.985  , cmsText);
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





