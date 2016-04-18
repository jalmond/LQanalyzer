#include "Macro.h"
#include "CMS_lumi.h"
#include "TGraphAsymmErrors.h"


TH1F* makeHist(TString m, TString hist, int col, int style);
TH1F* makeRefHist(TString m);
TH1F* makehist(TString hist);
TH1F* makenpHist(TString hist,  int col, int style);
TH1F* makecfHist(TString hist,  int col, int style);
TH1F* makemcHist(TString hist,  int col, int style);
void MakeCutEffHist(TCanvas* c, TString hist, TH1F* thist, TH1F* thist_presel);


void MakeNPunziMedMass_id(){
  
  setTDRStyle();
  gStyle->SetPalette(1);

  TH1F* tight_anal1 = makehist("");
  TH1F* tight_anal2 = makehist("1");
  
  
  TLegend* legendH = new TLegend(0.6, 0.7, 0.9, 0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextSize(0.03);

  
  tight_anal1->GetXaxis()->SetTitle("m_{N} GeV");
  tight_anal1->GetYaxis()->SetTitle("Efficiency");
 
  tight_anal1->SetMarkerColor(kBlue);
  tight_anal1->SetMarkerStyle(20.);
  tight_anal2->SetMarkerColor(kRed);
  tight_anal2->SetMarkerStyle(21.);


  legendH->AddEntry(tight_anal1, "no m(e2jj) cut", "p");
  legendH->AddEntry(tight_anal2, "m(e2jj) cut", "p");

  tight_anal1->GetYaxis()->SetRangeUser(0., 0.04);
  tight_anal1->Draw("p");
  tight_anal2->Draw("psame");


  legendH->Draw();

  TGraphAsymmErrors * g = new TGraphAsymmErrors(heff);
  g->SetLineWidth(2.0);
  g->SetMarkerSize(2.);
  //  g->Draw( "9pXsame" );
  
  
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();
  
  
  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/SignalPlots/Punzi_presel_midmass.pdf" ));
  return;
  
}

void MakeCutEffHist(TCanvas* c, TString hist, TH1F* thist, TH1F* thist_presel){
  
  TH1F* h_zveto_eff = (TH1F*)thist->Clone(hist);
  h_zveto_eff->Divide(thist_presel);
  h_zveto_eff->GetYaxis()->SetTitle("Cut efficiency");
  h_zveto_eff->Draw("p");
  
  c->SaveAs(("/home/jalmond/WebPlots/PreApproval/SignalPlots/Punzi_" + hist + ".pdf" ));
  
  
}


TH1F* makehist(TString hist){



  //TH1F* hn_90 = makeHist("90","PreSelection_highmass" + hist + "2", 414,0);
  TH1F* hn_100 = makeHist("100","PreSelection_highmass" + hist + "1",402,0);
  TH1F* hn_125 = makeHist("125","PreSelection_highmass" + hist + "2",616,0);
  TH1F* hn_150 = makeHist("150","PreSelection_highmass" + hist + "3",432,0);
  TH1F* hn_175 = makeHist("175","PreSelection_highmass" + hist + "4",600,0);
  TH1F* hn_200 = makeHist("200","PreSelection_highmass" + hist + "5",600,0);
  TH1F* hn_250 = makeHist("250","PreSelection_highmass" + hist + "6",600,0);
  TH1F* hn_300 = makeHist("300","PreSelection_highmass" + hist + "7",600,0);
  TH1F* hn_400 = makeHist("400","PreSelection_highmass" + hist + "7",600,0);
  TH1F* hn_500 = makeHist("500","PreSelection_highmass" + hist + "9",600,0);

  //TH1F* href_90 = makeRefHist("90");
  TH1F* href_100 = makeRefHist("100");
  TH1F* href_125 = makeRefHist("125");
  TH1F* href_150 = makeRefHist("150");
  TH1F* href_175 = makeRefHist("175");
  TH1F* href_200 = makeRefHist("200");
  TH1F* href_250 = makeRefHist("250");
  TH1F* href_300 = makeRefHist("300");
  TH1F* href_400 = makeRefHist("400");
  TH1F* href_500 = makeRefHist("500");

  
  
  //TH1F* np_90 = makenpHist("PreSelection_highmass" + hist + "2",600,0);
  TH1F* np_100 = makenpHist("PreSelection_highmass" + hist + "3",600,0);
  TH1F* np_125= makenpHist("PreSelection_highmass" + hist + "4",600,0);
  TH1F* np_150 = makenpHist("PreSelection_highmass" + hist + "5",600,0);
  TH1F* np_175 = makenpHist("PreSelection_highmass" + hist + "6",600,0);
  TH1F* np_200 = makenpHist("PreSelection_highmass" + hist + "7",600,0);
  TH1F* np_250 = makenpHist("PreSelection_highmass" + hist + "8",600,0);
  TH1F* np_300 = makenpHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* np_400 = makenpHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* np_500 = makenpHist("PreSelection_highmass" + hist + "9",600,0);

  
  //TH1F* cf_90 = makecfHist("PreSelection_highmass" + hist + "2", 414,0);
  TH1F* cf_100 = makecfHist("PreSelection_highmass" + hist + "3",402,0);
  TH1F* cf_125 = makecfHist("PreSelection_highmass" + hist + "4",616,0);
  TH1F* cf_150 = makecfHist("PreSelection_highmass" + hist + "5",432,0);
  TH1F* cf_175 = makecfHist("PreSelection_highmass" + hist + "6",600,0);
  TH1F* cf_200 = makecfHist("PreSelection_highmass" + hist + "7",600,0);
  TH1F* cf_250 = makecfHist("PreSelection_highmass" + hist + "8",600,0);
  TH1F* cf_300 = makecfHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* cf_400 = makecfHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* cf_500 = makecfHist("PreSelection_highmass" + hist + "9",600,0);
  
  //TH1F* mc_90 = makemcHist("PreSelection_highmass" + hist + "2", 414,0);
  TH1F* mc_100 = makemcHist("PreSelection_highmass" + hist + "3",402,0);
  TH1F* mc_125 = makemcHist("PreSelection_highmass" + hist + "4",616,0);
  TH1F* mc_150 = makemcHist("PreSelection_highmass" + hist + "5",432,0);
  TH1F* mc_175 = makemcHist("PreSelection_highmass" + hist + "6",600,0);
  TH1F* mc_200 = makemcHist("PreSelection_highmass" + hist + "7",600,0);
  TH1F* mc_250 = makemcHist("PreSelection_highmass" + hist + "8",600,0);
  TH1F* mc_300 = makemcHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* mc_400 = makemcHist("PreSelection_highmass" + hist + "9",600,0);
  TH1F* mc_500 = makemcHist("PreSelection_highmass" + hist + "9",600,0);
  
    
  TH1F* heff = new TH1F("heff","heff", 15, 0., 15.);

  // cout << hn_90 << "  " << href_90 << " " << np_90  << " " <<  mc_90 << " " << cf_90 << endl;
  //heff->SetBinContent(1, (hn_90->GetBinContent(2)/href_90->GetBinContent(2))/ (1 + sqrt(np_90->GetBinContent(2) + cf_90->GetBinContent(2) + mc_90->GetBinContent(2)+ (0.28*np_90->GetBinContent(2))*(0.28*np_90->GetBinContent(2)))));
  heff->SetBinContent(2, (hn_100->GetBinContent(2)/href_100->GetBinContent(2))/ (1 + sqrt(np_100->GetBinContent(2) + cf_100->GetBinContent(2) + mc_100->GetBinContent(2)+ (0.28*np_100->GetBinContent(2))*(0.28*np_100->GetBinContent(2)))));
  heff->SetBinContent(3, (hn_125->GetBinContent(2)/href_125->GetBinContent(2))/ (1 + sqrt(np_125->GetBinContent(2) + cf_125->GetBinContent(2) + mc_125->GetBinContent(2)+ (0.28*np_125->GetBinContent(2))*(0.28*np_125->GetBinContent(2)))));
  heff->SetBinContent(4, (hn_150->GetBinContent(2)/href_150->GetBinContent(2))/ (1 + sqrt(np_150->GetBinContent(2) + cf_150->GetBinContent(2) + mc_150->GetBinContent(2)+ (0.28*np_150->GetBinContent(2))*(0.28*np_150->GetBinContent(2)))));
  heff->SetBinContent(5, (hn_175->GetBinContent(2)/href_175->GetBinContent(2))/ (1 + sqrt(np_175->GetBinContent(2) + cf_175->GetBinContent(2) + mc_175->GetBinContent(2)+ (0.28*np_175->GetBinContent(2))*(0.28*np_175->GetBinContent(2)))));
  heff->SetBinContent(6, (hn_200->GetBinContent(2)/href_200->GetBinContent(2))/ (1 + sqrt(np_200->GetBinContent(2) + cf_200->GetBinContent(2) + mc_200->GetBinContent(2)+ (0.28*np_200->GetBinContent(2))*(0.28*np_200->GetBinContent(2)))));
  heff->SetBinContent(6, (hn_250->GetBinContent(2)/href_250->GetBinContent(2))/ (1 + sqrt(np_250->GetBinContent(2) + cf_250->GetBinContent(2) + mc_250->GetBinContent(2)+ (0.28*np_250->GetBinContent(2))*(0.28*np_250->GetBinContent(2)))));
  heff->SetBinContent(6, (hn_300->GetBinContent(2)/href_300->GetBinContent(2))/ (1 + sqrt(np_300->GetBinContent(2) + cf_300->GetBinContent(2) + mc_300->GetBinContent(2)+ (0.28*np_300->GetBinContent(2))*(0.28*np_300->GetBinContent(2)))));
  
  heff->SetBinContent(6, (hn_400->GetBinContent(2)/href_400->GetBinContent(2))/ (1 + sqrt(np_400->GetBinContent(2) + cf_400->GetBinContent(2) + mc_400->GetBinContent(2)+ (0.28*np_400->GetBinContent(2))*(0.28*np_400->GetBinContent(2)))));
  heff->SetBinContent(6, (hn_500->GetBinContent(2)/href_500->GetBinContent(2))/ (1 + sqrt(np_500->GetBinContent(2) + cf_500->GetBinContent(2) + mc_500->GetBinContent(2)+ (0.28*np_500->GetBinContent(2))*(0.28*np_500->GetBinContent(2)))));


  //  heff->GetXaxis()->SetBinLabel(1,"90");
  heff->GetXaxis()->SetBinLabel(2,"100");
  heff->GetXaxis()->SetBinLabel(3,"125");
  heff->GetXaxis()->SetBinLabel(4,"150");
  heff->GetXaxis()->SetBinLabel(5,"175");
  heff->GetXaxis()->SetBinLabel(6,"200");
  heff->GetXaxis()->SetBinLabel(7,"250");
  heff->GetXaxis()->SetBinLabel(8,"300");
  heff->GetXaxis()->SetBinLabel(9,"400");
  heff->GetXaxis()->SetBinLabel(10,"500");

  
  return heff;
}





TH1F* makecfHist(TString hist,  int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKchargeflip_dilep_5_3_14.root";

  cout << hist << endl;
  TFile* file = new TFile(path);
  TH1F* h = (TH1F*)file->Get(hist);

  cout << h << endl;
  return h;

}

TH1F* makemcHist(TString hist,  int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_mc_5_3_14.root";

  cout << hist << endl;
  TFile* file = new TFile(path);
  TH1F* h = (TH1F*)file->Get(hist);

  cout << h << endl;
  return h;

}


TH1F* makenpHist(TString hist,  int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKnonprompt_dilep_5_3_14.root";

  cout << hist << endl;
  TFile* file = new TFile(path);
  TH1F* h = (TH1F*)file->Get(hist);

  cout << h << endl;
  return h;

}

TH1F* makeHist(TString m, TString hist,  int col, int style){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + m + "_nocut_5_3_14.root";

  cout << hist << endl;
  TFile* file = new TFile(path);
  TH1F* h = (TH1F*)file->Get(hist);

  cout << h << endl;
  return h;
}


TH1F* makeRefHist(TString m){
  TString  path = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee" + m + "_nocut_5_3_14.root";
  
  TFile* file = new TFile(path);
  TH1F* h = (TH1F*)file->Get("Efficiency/eff_electronRef");
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







