#include "Macro.h"
#include "CMS_lumi.h"

void MakePlotFakeDistMC(){
  
  TString path_ttbar = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes//MC/FakeRateCalculator_El_SKttbar_5_3_14.root";
  
  TString path_qcd= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_SKQCD_5_3_14.root";
  
  TString path_wjet = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_SKWjets_5_3_14.root";

  

  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fttbar = new TFile(path_ttbar);
  TFile * fqcd = new TFile(path_qcd);
  TFile * fwjet = new TFile(path_wjet);
  
  vector<TString> list_of_regions;
  list_of_regions.push_back("SingleElFake");
  list_of_regions.push_back("DoubleElFake");
 
  
  vector<TString> list_of_names;
  list_of_names.push_back("HT");
  list_of_names.push_back("eemass");
  list_of_names.push_back("MET");
  list_of_names.push_back("Njets");
  list_of_names.push_back("Nbjets");



  vector<TString> xaxis_label;
  xaxis_label.push_back("H_{T} GeV");
  xaxis_label.push_back("m(ee) GeV");
  xaxis_label.push_back("MET GeV");
  xaxis_label.push_back("N(jets)");
  xaxis_label.push_back("N(bjets)");

  vector<TString> yaxis_label;
  yaxis_label.push_back("Entries");
  yaxis_label.push_back("Entries");
  yaxis_label.push_back("Entries");
  yaxis_label.push_back("Entries");
  yaxis_label.push_back("Entries");
  
 
  for(unsigned int j = 0; j < list_of_regions.size(); j++){
    for(unsigned int i = 0; i < list_of_names.size(); i++){
      
      
      TCanvas* c1 = new TCanvas((("Plot")+ list_of_regions.at(j )+ "/" + list_of_names.at(i)).Data(), "Plot", 1600, 1200);
      
      cout << "Getting " << ("h_"+list_of_regions.at(j ) + "/"+  list_of_names.at(i) + "_" + list_of_regions.at(j ) ) << endl;
      TH1F* h_ttbar= (TH1F*)fttbar->Get(((list_of_regions.at(j ) + "/h_"+  list_of_names.at(i) + "_" + list_of_regions.at(j ) ).Data()));
      
      
      TH1F* h_qcd= (TH1F*)fqcd->Get(((list_of_regions.at(j ) + "/h_"+  list_of_names.at(i) + "_" + list_of_regions.at(j ) ).Data()));

      
      TH1F* h_wjet= (TH1F*)fwjet->Get(((list_of_regions.at(j ) + "/h_"+  list_of_names.at(i) + "_" + list_of_regions.at(j ) ).Data()));


      cout << h_qcd << endl;
      bool usew = (h_wjet);
      bool usetop = (h_ttbar);
      bool useqcd = (h_qcd);
      
      if(h_qcd){
	h_qcd->SetLineColor(kRed);
	h_qcd->SetFillColor(kRed);
	h_qcd->SetLineWidth(2.);
	h_qcd->SetFillStyle(3003);
      }
      if(usetop){
	h_ttbar->SetLineColor(kCyan);
	h_ttbar->SetFillColor(kCyan);
	h_ttbar->SetLineWidth(2.);
	h_ttbar->SetFillStyle(3004);
      }
      if(usew){
	h_wjet->SetLineColor(kOrange);
	h_wjet->SetFillColor(kOrange);
	h_wjet->SetFillStyle(3007);
	h_wjet->SetLineWidth(2.);
      }
      int nrebin = 1;
      if(list_of_names.at(i).Contains("HT")) nrebin= 5;
      if(list_of_names.at(i).Contains("MET")) nrebin= 2;
      if(list_of_names.at(i).Contains("eemass")) nrebin= 4;
      if(useqcd)h_qcd->Rebin(nrebin);
      if(usetop){
	h_ttbar->Rebin(nrebin);
      }
      if(usew){
	h_wjet->Rebin(nrebin);
      }
      
      if(useqcd){
	h_qcd->GetYaxis()->SetTitle(yaxis_label.at(i));
	h_qcd->GetXaxis()->SetTitle(xaxis_label.at(i));
	
	h_qcd->GetYaxis()->SetRangeUser(0.,  h_qcd->GetMaximum()* 1.1);
	h_qcd->Draw("hist");
	if(usetop)h_ttbar->Draw("histsame");
	if(usew)h_wjet->Draw("histsame");

      }
      else{
	if(usetop){
	  h_ttbar->GetYaxis()->SetTitle(yaxis_label.at(i));
	  h_ttbar->GetXaxis()->SetTitle(xaxis_label.at(i));
	  
	  float max =  h_ttbar->GetMaximum()* 1.1;
	  if(h_wjet->GetMaximum()* 1.1   > max) max = h_wjet->GetMaximum()* 1.1 ;
	  h_ttbar->GetYaxis()->SetRangeUser(0.,  max);
	  h_ttbar->Draw("hist");
	  if(usew)h_wjet->Draw("histsame");

	}
      }

      TLegend* legendH = new TLegend(0.7, 0.75, 0.9, 0.9);
      legendH->SetFillColor(kWhite);
      //legendH->SetTextFont(42);
      if(useqcd)legendH->AddEntry(h_qcd, "QCD", "f");
      if(usetop)legendH->AddEntry(h_ttbar, "t#bar{t}", "f");
      if(usew)legendH->AddEntry(h_wjet, "W+jet", "f");
      legendH->Draw();
            
      CMS_lumi( c1, 2, 11 );
      c1->Update();
      c1->RedrawAxis();
      
      c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Fakes/MCFakeDist_all_" + list_of_regions.at(j ) + "_" + list_of_names.at(i) + ".pdf").Data());
    }
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





