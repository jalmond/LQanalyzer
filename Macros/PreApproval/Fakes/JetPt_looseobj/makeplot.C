#include "Macro.h"
#include "CMS_lumi.h"

void makeplot(){
  
  TString path_ttbar = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes//MC/FakeRateCalculator_El_SKttbar_5_3_14.root";
  
  TString path_qcd= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_SKQCD_5_3_14.root";
  TString path_qcd2= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_SKQCDEl_5_3_14.root";
  
  TString path_wjet = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_SKWjets_5_3_14.root";

  
  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fttbar = new TFile(path_ttbar);
  TFile * fqcd = new TFile(path_qcd);
  TFile * fqcd2 = new TFile(path_qcd2);
  TFile * fwjet = new TFile(path_wjet);
  //  
  TCanvas* c1 = new TCanvas("Plot", "Plot", 1600, 1200);
  
  
  TH1F* h_ttbar= (TH1F*)fttbar->Get("JetPt_fakeobject_sig");
  TH1F* h_qcd = (TH1F*)fqcd->Get("JetPt_fakeobject");
  TH1F* h_qcd2 = (TH1F*)fqcd2->Get("GenJetPt_fakeobject");
  TH1F* h_wjet = (TH1F*)fwjet->Get("JetPt_fakeobject");

  h_ttbar->Rebin(4);
  h_qcd->Rebin(4);
  h_qcd2->Rebin(4);
  h_wjet->Rebin(4);

  TH1F * h_fake_20 = (TH1F*)fqcd->Get("JetPt_fakeobject_fakerateHNTight_relaxedip_allmc_20");
  TH1F * h_fake_40 = (TH1F*)fqcd->Get("JetPt_fakeobject_fakerateHNTight_relaxedip_allmc_40");
  TH1F * h_fake_60 = (TH1F*)fqcd->Get("JetPt_fakeobject_fakerateHNTight_relaxedip_allmc_60");
  h_fake_20->Rebin(4);
  h_fake_40->Rebin(4);
  h_fake_60->Rebin(4);


  cout << h_ttbar << " " << h_wjet << " " << h_qcd << " " << h_qcd2 << endl;

  h_fake_20->SetLineColor(kRed);
  h_fake_40->SetLineColor(kBlue);
  h_fake_60->SetLineColor(kGreen);

  h_fake_20->Scale(1. / h_fake_20->Integral());
  h_fake_40->Scale(1. / h_fake_40->Integral());
  h_fake_60->Scale(1. / h_fake_60->Integral());

  if(h_qcd){
    h_qcd->SetLineColor(kRed);
    h_qcd->SetMarkerColor(kRed);
    h_qcd->SetLineWidth(2.);
    h_qcd->SetFillStyle(3003);
    h_qcd->SetMarkerStyle(21);
    h_qcd->SetMarkerSize(2.);
  }

  if(h_qcd2){
    h_qcd2->SetLineColor(kRed);
    h_qcd2->SetMarkerColor(kRed-5);
    h_qcd2->SetLineWidth(2.);
    h_qcd2->SetFillStyle(3003);
    h_qcd2->SetMarkerStyle(21);
    h_qcd2->SetMarkerSize(2.);
  }


  if(h_ttbar){
    h_ttbar->SetLineColor(kCyan);
    h_ttbar->SetMarkerColor(kCyan);
    h_ttbar->SetLineWidth(2.);
    h_ttbar->SetFillStyle(3004);
    h_ttbar->SetMarkerStyle(21);
    h_ttbar->SetMarkerSize(2.);
  }
  if(h_wjet){
    h_wjet->SetLineColor(kOrange);
    h_wjet->SetMarkerColor(kOrange);
    h_wjet->SetFillStyle(3007);
    h_wjet->SetLineWidth(2.);
    h_wjet->SetMarkerStyle(21);
    h_wjet->SetMarkerSize(2.);
  }
  
  h_qcd->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h_qcd->GetYaxis()->SetTitle("Events / 8 GeV");
  
  h_qcd->GetYaxis()->SetRangeUser(0.,  h_qcd->GetMaximum()* 2.);
  
  cout << "Integral = " << h_qcd->Integral() << " " << h_ttbar->Integral() << " " << h_wjet->Integral() << endl; 
  h_qcd->Scale(1. / h_qcd->Integral());
  h_qcd2->Scale(1. / h_qcd2->Integral());
  h_ttbar->Scale(1. / h_ttbar->Integral());
  h_wjet->Scale(1. / h_wjet->Integral());
  
  h_qcd->GetYaxis()->SetRangeUser(0.,0.35);
  h_qcd->Draw("p");
  //h_qcd2->Draw("psame");
  h_ttbar->Draw("psame");
  h_wjet->Draw("psame");
  h_fake_20->Draw("histsame");
  h_fake_40->Draw("histsame");
  h_fake_60->Draw("histsame");
  
  
  cout << "Integral = " << h_qcd->Integral() << " " << h_ttbar->Integral() << " " << h_wjet->Integral() << endl; 
  
  TLegend* legendH = new TLegend(0.7, 0.75, 0.9, 0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextSize(0.03);
  legendH->SetTextFont(42);
  legendH->AddEntry(h_qcd, "QCD", "p");
  //legendH->AddEntry(h_qcd2, "QCD2", "p");
  legendH->AddEntry(h_ttbar, "t#bar{t}", "p");
  legendH->AddEntry(h_wjet, "W+jet", "p");
  legendH->AddEntry(h_fake_20, "FR 20", "l");
  legendH->AddEntry(h_fake_40, "FR 40", "l");
  legendH->AddEntry(h_fake_60, "FR 60", "l");
  legendH->Draw();
  
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();
  
  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Fakes/jetpt.pdf"));
  delete c1;
}
 
void CMS_lumi( TPad* pad, int iPeriod, int iPosX )
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





