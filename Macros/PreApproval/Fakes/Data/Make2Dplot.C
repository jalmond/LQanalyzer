#include "Macro.h"
#include "CMS_lumi.h"

void Make2Dplot(){
  

  TString path= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/";

  TFile * fdata = new TFile(path + "FakeRateCalculator_El_data_5_3_14.root");
  TFile * fmc = new TFile(path + "FakeRateCalculator_El_mc_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;
  TCanvas* c1 = new TCanvas(("Plot"), "Plot", 1600, 1200);
  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);

  ///
  std::vector<TString> fakes40;
  fakes40.push_back("40_pt_eta");

  std::vector<TString> fakes;
  fakes.push_back("HNTight_relaxedip_");

  for(vector<TString>::iterator it2 = fakes40.begin(); it2!=fakes40.end(); ++it2){
    for(vector<TString>::iterator it = fakes.begin(); it!=fakes.end(); ++it){
      cout << *it2 << endl;

      TString denom ="LooseEl" + *it + *it2;
      TString num ="TightEl" + *it + *it2;
      TH2F* h_pt_num= (TH2F*)fdata->Get(num.Data());
      TH2F* h_pt_denom= (TH2F*)fdata->Get(denom.Data());

      TH2F* h_mcpt_num= (TH2F*)fmc->Get(num.Data());
      TH2F* h_mcpt_denom= (TH2F*)fmc->Get(denom.Data());

      for(unsigned int j = 1; j < h_pt_num->GetNbinsY()+1; j++){
	float newcontent = h_pt_num->GetBinContent(7, j) + h_pt_num->GetBinContent(8, j) ;
	float newerror =   h_pt_num->GetBinError(7, j)*h_pt_num->GetBinError(7, j) + h_pt_num->GetBinError(8, j)*h_pt_num->GetBinError(8, j) ;
	h_pt_num->SetBinError(7, j, sqrt(newerror));
	h_pt_num->SetBinContent(7, j, newcontent);
      }
      for(unsigned int j = 1; j < h_pt_denom->GetNbinsY()+1; j++){
        float newcontent = h_pt_denom->GetBinContent(7, j) + h_pt_denom->GetBinContent(8, j) ;
        float newerror =   h_pt_denom->GetBinError(7, j)*h_pt_denom->GetBinError(7, j) + h_pt_denom->GetBinError(8, j)*h_pt_denom->GetBinError(8, j) ;
	h_pt_denom->SetBinError(7, j, sqrt(newerror));
	h_pt_denom->SetBinContent(7, j, newcontent);
      } 



      for(unsigned int j = 1; j < h_mcpt_num->GetNbinsY()+1; j++){
        float newcontent = h_mcpt_num->GetBinContent(7, j) + h_mcpt_num->GetBinContent(8, j) ;
        float newerror =   h_mcpt_num->GetBinError(7, j)*h_mcpt_num->GetBinError(7, j) + h_mcpt_num->GetBinError(8, j)*h_mcpt_num->GetBinError(8, j) ;
	h_mcpt_num->SetBinError(7, j, sqrt(newerror));
	h_mcpt_num->SetBinContent(7, j, newcontent);
      } 


      for(unsigned int j = 1; j < h_mcpt_denom->GetNbinsY()+1; j++){
        float newcontent = h_mcpt_denom->GetBinContent(7, j) + h_mcpt_denom->GetBinContent(8, j) ;
        float newerror =   h_mcpt_denom->GetBinError(7, j)*h_mcpt_denom->GetBinError(7, j) + h_mcpt_denom->GetBinError(8, j)*h_mcpt_denom->GetBinError(8, j) ;
	h_mcpt_denom->SetBinError(7, j, sqrt(newerror));
	h_mcpt_denom->SetBinContent(7, j, newcontent);
      } 



      TH2F* eff_rate = (TH2F*)h_pt_num->Clone(("FakeRate_" + *it2).Data());
      cout << h_pt_denom << " " << h_mcpt_num  <<endl;
      TString tmp = (*it2 +"_denom");
      TH2F* hratedenom = (TH2F*)h_pt_denom->Clone(tmp.Data());
      //eff_rate->Add(h_mcpt_num,-1.);
      //hratedenom->Add(h_mcpt_denom, -1.);
      eff_rate->Divide(eff_rate,hratedenom,1.,1.,"cl=0.683 b(1,1) mode");
      
      eff_rate->GetYaxis()->SetTitle("#eta" );
      eff_rate->GetXaxis()->SetTitle("p_{T} (GeV)");
      eff_rate->GetXaxis()->SetRangeUser(15.,59.);
      
      for(unsigned int i = 1; i < eff_rate->GetNbinsX()+1; i++){
	for(unsigned int j = 1; j < eff_rate->GetNbinsY()+1; j++){
	  cout <<"Bin " << i << ":"<< j << " has content= " <<eff_rate->GetBinContent(i,j) << endl;
	} 
      }
      
	
      eff_rate->Draw("colztextE");
      c1->Update();
      
      c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Fakes/FakeRatePtEta.pdf"));
    }
    
  }
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






//  LocalWords:  newcontent
