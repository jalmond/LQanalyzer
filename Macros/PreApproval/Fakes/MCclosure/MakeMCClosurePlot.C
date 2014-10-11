#include "Macro.h"
#include "CMS_lumi.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"


double GetError(TH1* h, bool up);

void MakeMCClosurePlot(){

  
  TH1::SetDefaultSumw2(true);
  setTDRStyle();


  TH1F* mcclosure_hist = new TH1F("mcclosure","mcclosure", 10,0.,10.);
  mcclosure_hist->GetYaxis()->SetTitle("Event");
  mcclosure_hist->GetYaxis()->SetRangeUser(0., 15.);
  mcclosure_hist->GetXaxis()->SetTitle("");
  mcclosure_hist->GetXaxis()->SetBinLabel(1,"PtvsEta");
  mcclosure_hist->GetXaxis()->SetBinLabel(2,"HtvsEta");
  mcclosure_hist->GetXaxis()->SetBinLabel(3,"PtvsEta_nbjet");
  mcclosure_hist->GetXaxis()->SetBinLabel(4,"HtvsEta_X");
  mcclosure_hist->GetXaxis()->SetBinLabel(5,"PtvsEta_X");
  mcclosure_hist->GetXaxis()->SetBinLabel(6,"PtvsEta_nbjet_X");
  mcclosure_hist->GetXaxis()->SetBinLabel(7,"PtvsEta_HT_nbjet_X");
  mcclosure_hist->GetXaxis()->SetBinLabel(8,"PtvsEta_HT_X");
  mcclosure_hist->GetXaxis()->SetBinLabel(9,"PtvsEta_HT");
  

  TString path_qcd2= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/MC/HNDiElectron_nonprompt_SKQCDdiem_dilep_5_3_14.root";
  TFile * fqcd2 = new TFile(path_qcd2);
  TH1F* h_qcd2_doubletosingle= (TH1F*)fqcd2->Get("MCclosure/HNTightMCSSclosure_mcclosure_Doubletosingle");
  
  TCanvas* c1 = new TCanvas(("Plot"), "Plot", 1600, 1200);
  c1->cd();

  mcclosure_hist->GetYaxis()->SetTitle("Event");
  mcclosure_hist->Draw();


  TLine *line = new TLine( mcclosure_hist->GetBinLowEdge(mcclosure_hist->GetXaxis()->GetFirst()),h_qcd2_doubletosingle->Integral(),mcclosure_hist->GetBinLowEdge(mcclosure_hist->GetXaxis()->GetLast()+1),h_qcd2_doubletosingle->Integral());
  
  line->SetLineStyle(2);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->Draw();
  
  
  vector<TString> list_of_names;
  list_of_names.push_back("_");
  list_of_names.push_back("_h_");
  list_of_names.push_back("_b_");
  list_of_names.push_back("_bt_");
  list_of_names.push_back("_ht_");
  list_of_names.push_back("_pt_");
  list_of_names.push_back("_st_");
  list_of_names.push_back("_st2_");
  list_of_names.push_back("_st3_");


  vector<TString> collection;
  collection.push_back("MCclosure/HNTightMCSSclosure");

  vector<TString> jetpt;
  jetpt.push_back("20");
  jetpt.push_back("30");
  jetpt.push_back("40");
  jetpt.push_back("60");


  TLegend* legendH = new TLegend(0.6,0.6, 0.9,0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextFont(42);
  legendH->AddEntry(line, "Observed" , "l");
  double jx[9], jxerr[9];
  double jy[9], jyerr[9];
  for(unsigned int j = 0; j < jetpt.size(); j++){
    float offset = 0.4 + (0.1* double(j));
    for(unsigned int k = 0 ; k < collection.size() ; k ++){
      for(unsigned int i = 0; i < list_of_names.size(); i++){
	TH1F* h_qcd_p= (TH1F*)fqcd2->Get((collection.at(k) + list_of_names.at(i) + "mcclosure" +jetpt.at(j) + "_single"));
	double qcd_p_err;
	double int_qcd_p = h_qcd_p->IntegralAndError(0, h_qcd_p->GetNbinsX(), qcd_p_err, "");
	int bin = -9;
	if(list_of_names.at(i).Contains("st2")) bin = 7;
	else if(list_of_names.at(i).Contains("st3")) bin= 8;
	else if(list_of_names.at(i).Contains("st")) bin= 6;
	else if(list_of_names.at(i).Contains("_bt_")) bin= 5;
	else if(list_of_names.at(i).Contains("_pt_")) bin= 4;
	else if(list_of_names.at(i).Contains("_ht_")) bin= 3;
	else if(list_of_names.at(i).Contains("_b_")) bin= 2;
	else if(list_of_names.at(i).Contains("_h_")) bin= 1;
	else if(list_of_names.at(i).Contains("_")) bin= 0;
	
	jx[bin] = bin+ offset;  jxerr[bin] = 0.;
	jy[bin] = int_qcd_p; jyerr[bin] = qcd_p_err;
	cout << int_qcd_p << " " << qcd_p_err << endl;
	cout<< (collection.at(k) + "_fake_predicted" + jetpt.at(j) + list_of_names.at(i)) << endl;
      }
    }
    
    TGraphAsymmErrors * g = new TGraphAsymmErrors(9, jx, jy, jxerr, jxerr,  jyerr,jyerr);
    g->SetLineWidth(2.0);
    if(j == 0){
      g->SetMarkerColor(kCyan);
      g->SetLineColor(kCyan);
    }
    if(j == 1){
      g->SetMarkerStyle(21);
      g->SetMarkerColor(kGreen);
      g->SetLineColor(kGreen);
    }
    if(j == 2){
      g->SetMarkerStyle(22);
      g->SetMarkerColor(kOrange);
      g->SetLineColor(kOrange);
    }
    if(j == 3){
      g->SetMarkerStyle(33);
      g->SetMarkerColor(kBlue-2);
      g->SetLineColor(kBlue-2);
    }
    g->SetMarkerSize(2.);
    g->Draw( "9sameP" );
    
    
    legendH->AddEntry(g, "Prediced: AwayJet " + jetpt.at(j) +" GeV" , "pl");
    legendH->Draw();
  }
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);

  latex.SetTextFont(42);
  //  latex.SetTextAlign(31);
  float t = c1->GetTopMargin();
  latex.SetTextSize(lumiTextSize*t);

  TString label = "#bf{QCD: Double Fakes #rightarrow Single Fakes}";
  TString label2 = "#bf{2 Electrons + 2 Jets}"; 
  float l = c1->GetLeftMargin()+0.05;
  latex.DrawLatex(l, 0.75 ,label);
  latex.DrawLatex(l, 0.7 ,label2);

  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/MCclosure/DoubleToSingle.pdf"));
  

  
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







