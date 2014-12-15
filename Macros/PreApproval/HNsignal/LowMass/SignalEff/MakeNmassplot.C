#include "Macro.h"
#include "CMS_lumi.h"

TH1* makeHist(TString m, TString hist, int col, int style);

void MakeNmassplot(){

  std::vector<TString> masses;
  masses.push_back("40");
  masses.push_back("50");
  masses.push_back("60");
  masses.push_back("70");
  masses.push_back("80");
  masses.push_back("90");
  
  setTDRStyle();
  gStyle->SetPalette(1);


  vector<TString> hists;
  hists.push_back("_N_mass");
  hists.push_back("_N1_mass");
  hists.push_back("_W1_mass");
  hists.push_back("_W2_mass");
  hists.push_back("_elN_eta");
  hists.push_back("_elN_pt");
  hists.push_back("_elW_eta");
  hists.push_back("_elW_pt");

  for(unsigned int ihist = 0 ; ihist  < hists.size(); ihist++){
    TString hist = hists.at(ihist);
    
    TH1* hn_40 = makeHist("40", hist,414,0);  
    TH1* hn_50 = makeHist("50", hist,402,0);  
    TH1* hn_60 = makeHist("60", hist,616,0);  
    TH1* hn_70 = makeHist("70", hist,432,0);  
    TH1* hn_80 = makeHist("80", hist,600,0);  
    TH1* hn_90 = makeHist("90", hist,400,0);  
    
    TCanvas* c1 = new TCanvas("Plot"+hist, "Plot"+hist, 1600, 1200);
    hn_40->GetYaxis()->SetTitle("Norm."); 
    hn_40->GetXaxis()->SetTitle("m_{N} GeV"); 
    if(hist.Contains("eta"))     hn_40->GetXaxis()->SetTitle("el_{N} #eta"); 
    if(hist.Contains("pt"))     hn_40->GetXaxis()->SetTitle("el_{N} p_{T} GeV"); 
    if(hist.Contains("W1"))     hn_40->GetXaxis()->SetTitle("m_{W1} GeV"); 
    if(hist.Contains("W2"))     hn_40->GetXaxis()->SetTitle("m_{W2} GeV"); 
    hn_40->GetXaxis()->SetRangeUser(0., 200.);
    if(hist.Contains("pt"))   hn_40->GetXaxis()->SetRangeUser(0., 70.);

    
    hn_40->Scale(1./hn_40->Integral());
    hn_50->Scale(1./hn_50->Integral());
    hn_60->Scale(1./hn_60->Integral());
    hn_70->Scale(1./hn_70->Integral());
    hn_80->Scale(1./hn_80->Integral());
    hn_90->Scale(1./hn_90->Integral());
    
    float ymax =  hn_40->GetMaximum();
    if(hn_50->GetMaximum() > ymax) ymax = hn_50->GetMaximum();
    if(hn_60->GetMaximum() > ymax) ymax = hn_60->GetMaximum();
    if(hn_70->GetMaximum() > ymax) ymax = hn_70->GetMaximum();
    if(hn_80->GetMaximum() > ymax) ymax = hn_80->GetMaximum();
    if(hn_90->GetMaximum() > ymax) ymax = hn_90->GetMaximum();
    
    
    hn_40->GetYaxis()->SetRangeUser(0., ymax*1.4);
    if(hist.Contains("eta")) hn_40->GetXaxis()->SetRangeUser(-10., 10.);
    hn_40->Draw("hist");
    hn_50->Draw("histsame");
    hn_60->Draw("histsame");
    hn_70->Draw("histsame");
    hn_80->Draw("histsame");
    hn_90->Draw("histsame");
    
    TLegend* legendH = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendH->SetFillColor(kWhite);
    legendH->SetTextSize(0.03);
    
    legendH->AddEntry(hn_40, "m_{N} = 40 GeV", "l");
    legendH->AddEntry(hn_50, "m_{N} = 50 GeV", "l");
    legendH->AddEntry(hn_60, "m_{N} = 60 GeV", "l");
    legendH->AddEntry(hn_70, "m_{N} = 70 GeV", "l");
    legendH->AddEntry(hn_80, "m_{N} = 80 GeV", "l");
    legendH->AddEntry(hn_90, "m_{N} = 90 GeV", "l");
    
    legendH->Draw();
    
    CMS_lumi( c1, 2, 11 );
    c1->Update();
    c1->RedrawAxis();
    
    
    c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/SignalPlots/Signal_" + hist + ".pdf" ).Data());
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







TH1* makeHist(TString m, TString hist, int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + m + "_nocut_5_3_14.root";

  TFile* file = new TFile(path);
  TH1* h = (TH1*)file->Get("Truth_signal" + m + hist);
  h->SetLineWidth(2.);
  h->SetLineColor(col);
  h->SetLineStyle(style);
  return h;
}
