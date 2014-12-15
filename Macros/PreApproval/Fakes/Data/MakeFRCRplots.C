#include "Macro.h"
#include "CMS_lumi.h"

void MakeFRCRplots(){
  
  TString path_Wjet = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_SKWjets_5_3_14.root";
  TString path_Z = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_SKDY50plus_5_3_14.root";
  TString path_top = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_SKttbar_5_3_14.root";
  TString path_data= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_data_5_3_14.root";
  

  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fdata = new TFile(path_data);
  TFile * fw = new TFile(path_Wjet);
  TFile * fz = new TFile(path_Z);
  TFile * ft = new TFile(path_top);
  
  vector<TString> list_of_names;
  list_of_names.push_back("_ht_morebins");
  

  vector<TString> xaxis_label;
  xaxis_label.push_back("H_{T} GeV");
    

  
  for(unsigned int i = 0; i < list_of_names.size(); i++){
    
    TCanvas* c1 = new TCanvas((("Plot")+ list_of_names.at(i)).Data(), "Plot", 1600, 1200);
    
    TH1F* h_data_tight= (TH1F*)fdata->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    
    h_data_tight->SetLineWidth(2.);
    h_data_tight->SetMarkerSize(2.);
    h_data_tight->SetMarkerStyle(20);

    TH1F* h_w_tight= (TH1F*)fw->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    TH1F* h_z_tight= (TH1F*)fz->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    TH1F* h_t_tight= (TH1F*)ft->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    
    h_w_tight->SetFillColor(kOrange);
    h_w_tight->SetLineColor(kOrange);

    h_t_tight->SetFillColor(kCyan);
    h_t_tight->SetLineColor(kCyan);

    
    h_z_tight->SetFillColor(kBlue-4);
    h_z_tight->SetLineColor(kBlue-4);
    

    THStack * st = new THStack();
    st->Add(h_w_tight);
    st->Add(h_z_tight);
    st->Add(h_t_tight);
    
    h_data_tight->GetYaxis()->SetTitle("Events");
    h_data_tight->GetXaxis()->SetRangeUser(1., 300.);
    h_data_tight->GetYaxis()->SetRangeUser(1., 10000.);
    h_data_tight->GetXaxis()->SetTitle(xaxis_label.at(i));
    h_data_tight->Draw("p");
    st->Draw("histsame");

    c1->SetLogy();
    
    TLegend* legendH = new TLegend(0.6, 0.7, 0.9, 0.9);
    legendH->SetFillColor(kWhite);
    legendH->SetTextFont(42);
    legendH->SetTextSize(0.03);
    
    
    legendH->AddEntry(h_data_tight, "Data: Tight", "lp");
    legendH->AddEntry(h_w_tight, "W MC: Tight", "f");
    legendH->AddEntry(h_z_tight, "Z MC: Tight", "f");
    legendH->AddEntry(h_t_tight, "Top MC: Tight", "f");

    legendH->Draw();
    
    CMS_lumi( c1, 2, 11 );
    c1->Update();
    c1->RedrawAxis();
    
    c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Fakes/Data/DataMCCRFake"+ list_of_names.at(i) + ".pdf").Data());
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





