#include "Macro.h"
#include "CMS_lumi.h"

void MakeFR(){
  
  TString path_qcd= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_SKQCD_5_3_14.root";
 
  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fQCD = new TFile(path_qcd);

  vector<TString> hist;
  hist.push_back("_pt_eta");
  hist.push_back("_ht_eta");
  hist.push_back("_ht_eta_cb");
  hist.push_back("_ht_eta_nocb");
  hist.push_back("ht1_pt_eta_nocb");
  hist.push_back("ht2_pt_eta_nocb");
  hist.push_back("ht3_pt_eta_nocb");
  hist.push_back("_0bjet_pt_eta_nocb");
  hist.push_back("_bjet_pt_eta_nocb");
  hist.push_back("_0bjet_pt_eta");
  hist.push_back("_bjet_pt_eta");
  hist.push_back("_0bjet_ht1_pt_eta_nocb");
  hist.push_back("_0bjet_ht2_pt_eta_nocb");
  hist.push_back("_0bjet_ht3_pt_eta_nocb");
  hist.push_back("_bjet_ht1_pt_eta_nocb");
  hist.push_back("_bjet_ht2_pt_eta_nocb");
  hist.push_back("_bjet_ht3_pt_eta_nocb");
  hist.push_back("ht1_pt_eta");
  hist.push_back("ht2_pt_eta");
  hist.push_back("ht3_pt_eta");
  
  vector<TString> hist2;
  hist2.push_back("40");
  hist2.push_back("20");
  hist2.push_back("30");
  hist2.push_back("60");
  hist2.push_back("80");
  hist2.push_back("relaxed_ipcut40");
  hist2.push_back("relaxed_ipcut20");
  hist2.push_back("relaxed_ipcut30");
  hist2.push_back("relaxed_ipcut60");
  hist2.push_back("relaxed_ipcut80");

  TString outfile = "FakeRateMC.root";
  TFile* fout = new TFile(outfile.Data(),"RECREATE");
  fout->cd();
  for(vector<TString>::iterator it2 = hist.begin(); it2!=hist.end(); ++it2){
    for(vector<TString>::iterator it = hist2.begin(); it!=hist2.end(); ++it){
     

    int rebin=1;
    cout << *it << " " << *it2 << endl;

    TString add= "";
    if(it2->Contains("low")) add = "_nocb";
    if(it2->Contains("high")) add = "_nocb";
    if(!CheckFile(fQCD))return;
    TH2F* h_pt_num= (TH2F*)fQCD->Get(("MCTightEl_"+ *it + *it2).Data());
    TH2F* h_pt_denom= (TH2F*)fQCD->Get(("MCLooseEl_"+ *it +  *it2+add).Data());
    if(!h_pt_denom) h_pt_denom= (TH2F*)fQCD->Get(("MCLososeEl_"+ *it +  *it2+add).Data());

    CheckHist(h_pt_denom);
    CheckHist(h_pt_num);
    
    TH2F* h_QCDpt_num= (TH2F*)fQCD->Get(("MCTightEl_"+ *it +  *it2 ).Data());
    TH2F* h_QCDpt_denom= (TH2F*)fQCD->Get(("MCLooseEl_"+ *it+ *it2+add).Data());
    TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("MCEl_"+ *it+ *it2 ).Data());
    TH2F* hratedenom = (TH2F*)h_pt_denom->Clone(("MCEl_" +  *it + *it2 ).Data());
    
    eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");

    eff_rate->Write();

    }
  }


  vector<TString> hist3;
  hist3.push_back("closebjet_");
  hist3.push_back("noclosebjet_");


  for(vector<TString>::iterator it2 = hist3.begin(); it2!=hist3.end(); ++it2){
    for(vector<TString>::iterator it = hist2.begin(); it!=hist2.end(); ++it){


      int rebin=1;

      if(!CheckFile(fQCD))return;
      TH2F* h_pt_num= (TH2F*)fQCD->Get(("MCTightEl_"+ *it2 + *it + "_pt_eta" ).Data());
      TH2F* h_pt_denom= (TH2F*)fQCD->Get(("MCLooseEl_"+ *it2 +  *it + "_pt_eta").Data());
      CheckHist(h_pt_denom);
      CheckHist(h_pt_num);

      TH2F* h_QCDpt_num= (TH2F*)fQCD->Get(("MCTightEl_"+ *it2 +  *it + "_pt_eta").Data());
      TH2F* h_QCDpt_denom= (TH2F*)fQCD->Get(("MCLooseEl_"+ *it2+ *it + "_pt_eta").Data());
      TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("MCEl_"+ *it2+ *it + "_pt_eta" ).Data());
      TH2F* hratedenom = (TH2F*)h_pt_denom->Clone(("MCEl_" +  *it2 + *it + "_pt_eta" ).Data());

      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");

      eff_rate->Write();

    }
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





