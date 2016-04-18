#include "Macro.h"
#include "CMS_lumi.h"

void MakeFRDATAall(){
  
  TString path_mc = "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_mc_5_3_14.root";
  TString path_data= "/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_data_5_3_14.root";
  

  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fdata = new TFile(path_data);
  TFile * fmc = new TFile(path_mc);
  
  vector<TString> list_of_names;
  list_of_names.push_back("_pt");
  list_of_names.push_back("_ht");
  list_of_names.push_back("_eta");
  list_of_names.push_back("_njets");
  list_of_names.push_back("_nbjet");
  

  vector<TString> xaxis_label;
  xaxis_label.push_back("P_{T} GeV");
  xaxis_label.push_back("H_{T} GeV");
  xaxis_label.push_back("#eta");
  xaxis_label.push_back("N_{jet}");
  xaxis_label.push_back("N_{bjet}");
  

  
  for(unsigned int i = 0; i < list_of_names.size(); i++){
    
    TCanvas* c1 = new TCanvas((("Plot")+ list_of_names.at(i)).Data(), "Plot", 1600, 1200);
    
    TH1F* h_data_loose= (TH1F*)fdata->Get(("LooseElHNTight_40"+list_of_names.at(i)).Data());
    TH1F* h_data_tight= (TH1F*)fdata->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    
    TH1F* h_mc_loose= (TH1F*)fmc->Get(("LooseElHNTight_40"+list_of_names.at(i)).Data());
    TH1F* h_mc_tight= (TH1F*)fmc->Get(("TightElHNTight_40"+list_of_names.at(i)).Data());
    
    int rb=1;
    if(list_of_names.at(i).Contains("eta")){
      rb = 5;
    }

    h_data_loose->Rebin(rb);
    h_data_tight->Rebin(rb);
    h_mc_loose->Rebin(rb);
    h_mc_tight->Rebin(rb);
    
    
    
    TH1F* heff = (TH1F*)h_data_tight->Clone("eff");
    
    TH1F* hdata_denom_up = (TH1F*)h_data_loose->Clone("up");
    TH1F* hdata_denom_down = (TH1F*)h_data_loose->Clone("down");
    TH1F* hdata_num_up = (TH1F*)h_data_tight->Clone("up");
    TH1F* hdata_num_down = (TH1F*)h_data_tight->Clone("down");
    
    TH1F* herr = (TH1F*)h_data_tight->Clone("err");
    
    heff->Add(h_mc_tight, -1.);
    h_data_loose->Add(h_mc_loose, -1.);
    
    hdata_denom_up->Add(h_mc_loose, -1.15);
    hdata_denom_down->Add(h_mc_loose, -0.85);
    hdata_num_up->Add(h_mc_tight, -1.15);
    hdata_num_down->Add(h_mc_tight, -0.85);
    
    h_data_tight->Divide(h_data_loose);
    heff->Divide(h_data_loose);
    hdata_num_up->Divide(hdata_denom_up);
    hdata_num_down->Divide(hdata_denom_down);
    
    h_data_tight->SetMarkerStyle(20);
    h_data_tight->SetMarkerColor(kOrange);
    h_data_tight->SetLineColor(kOrange);
    
    heff->SetMarkerStyle(21);
    heff->SetMarkerColor(kBlue-2);
    heff->SetLineColor(kBlue-2);
    
    heff->SetLineWidth(3.);
    h_data_tight->SetLineWidth(3.);
    
    for(unsigned int ibin = 1; ibin < herr->GetNbinsX()+1; ibin++){

      float binerror =  heff->GetBinError(ibin);
      float error_up = heff->GetBinContent(ibin)  - hdata_num_down->GetBinContent(ibin) ;
      error_up = sqrt( error_up*error_up + binerror*binerror);
      float error_down= heff->GetBinContent(ibin)  - hdata_num_up->GetBinContent(ibin) ;
      error_down = sqrt( error_down*error_down + binerror*binerror);

      herr->SetBinContent(ibin,  heff->GetBinContent(ibin) + error_up - error_down);
      herr->SetBinError(ibin,  (error_down + error_up) / 2.);


    }
    
    heff->GetYaxis()->SetTitle("#epsilon (Tight/Loose)" );
    heff->GetXaxis()->SetTitle(xaxis_label.at(i));
    
    heff->GetYaxis()->SetRangeUser(0., 0.5);
    heff->GetXaxis()->SetRangeUser(15., 59.);
    if(list_of_names.at(i).Contains("eta")){
      heff->GetXaxis()->SetRangeUser(-3., 3.);
    }
    if(list_of_names.at(i).Contains("_ht")){
      heff->GetXaxis()->SetRangeUser(0., 1000.);
    }

    heff->Draw("p");
    h_data_tight->Draw("psame");
    TLegend* legendH = new TLegend(0.6, 0.7, 0.9, 0.9);
    legendH->SetFillColor(kWhite);
    legendH->SetTextFont(42);
    legendH->SetTextSize(0.03);
    
    herr->SetFillStyle(3354);
    herr->SetFillColor(kBlue-8);
    herr->SetMarkerSize(0);
    herr->SetMarkerStyle(0);
    herr->SetLineColor(kWhite);
    herr->Draw("E2same");
    
    legendH->AddEntry(h_data_tight, "Non corrected FR", "lp");
    legendH->AddEntry(heff, "EW corrected FR", "lp");
    legendH->AddEntry(herr, "#sigma (stat. + syst)", "f");
    legendH->Draw();
    
    CMS_lumi( c1, 2, 11 );
    c1->Update();
    c1->RedrawAxis();
    
    c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/Fakes/Data/MCFake"+ list_of_names.at(i) + ".pdf").Data());
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





