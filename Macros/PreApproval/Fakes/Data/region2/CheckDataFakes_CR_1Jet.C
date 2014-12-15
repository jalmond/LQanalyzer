#include "Macro.h"
#include "CMS_lumi.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"


double GetError(TH1* h, bool up);

void CheckDataFakes_CR_1Jet(){
  
  TH1::SetDefaultSumw2(true);
  setTDRStyle();
  
  TString param = "SSee_1jet_m_";

  TH1F* data_presel_hist = new TH1F("mcclosure","mcclosure", 10,0.,10.);
  data_presel_hist->GetYaxis()->SetTitle("Event");
  float ymax = 250.;
  data_presel_hist->GetYaxis()->SetRangeUser(0., ymax);
  data_presel_hist->GetXaxis()->SetTitle("");
  data_presel_hist->GetXaxis()->SetBinLabel(1,"PtvsEta");
  data_presel_hist->GetXaxis()->SetBinLabel(2,"HtvsEta");
  data_presel_hist->GetXaxis()->SetBinLabel(3,"PtvsEta_nbjet");
  data_presel_hist->GetXaxis()->SetBinLabel(4,"HtvsEta_X");
  data_presel_hist->GetXaxis()->SetBinLabel(5,"PtvsEta_X");
  data_presel_hist->GetXaxis()->SetBinLabel(6,"PtvsEta_nbjet_X");
  data_presel_hist->GetXaxis()->SetBinLabel(7,"PtvsEta_HT_nbjet_X");
  data_presel_hist->GetXaxis()->SetBinLabel(8,"PtvsEta_HT_X");
  data_presel_hist->GetXaxis()->SetBinLabel(9,"PtvsEta_HT");
  
  
  TString path_data= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_data_5_3_14.root";
  TFile * fdata = new TFile(path_data);
  
  TH1F* h_data_presel= (TH1F*)fdata->Get(param + "20");
  double error_up_data = GetError(h_data_presel , true);
  double error_down_data = GetError(h_data_presel , false);
  
  
  
  TCanvas* c1 = new TCanvas(("Plot"), "Plot", 1600, 1200);
  c1->cd();

  data_presel_hist->GetYaxis()->SetTitle("Event");
  data_presel_hist->Draw();

  
  vector<TString> jetpt;
  jetpt.push_back("20");
  jetpt.push_back("30");
  jetpt.push_back("40");
  jetpt.push_back("60");

  
  TString path_mc= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_mc_5_3_14.root";
  TFile * fmc = new TFile(path_mc);


  TString path_cf= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKchargeflip_dilep_5_3_14.root";
  TFile * fcf = new TFile(path_cf);


  TString path_np= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/NP/REG2/HNDiElectron_SKnonprompt_dilep_5_3_14.root";
  TFile * fnp = new TFile(path_np);

  TLegend* legendH = new TLegend(0.6,0.6, 0.9,0.9);
  legendH->SetFillColor(kWhite);
  legendH->SetTextFont(42);
  
  //h_data_presel->Draw("histsame");

  double jx[9], jxerr[9];
  double jy[9], jyerrup[9], jyerrdown[9];
  float offset = 0.1; 
  for(unsigned int bin = 0; bin < h_data_presel->GetNbinsX(); bin++){
    
    jx[bin] = bin+ offset;  jxerr[bin] = 0.;
    jy[bin] = h_data_presel->GetBinContent(bin+1);
    jyerrup[bin] = error_up_data;
    jyerrdown[bin] = error_down_data;
  }

  TGraphAsymmErrors * gd = new TGraphAsymmErrors(9, jx, jy, jxerr, jxerr,  jyerrup,jyerrdown);
  gd->SetLineWidth(2.0);
  gd->SetMarkerSize(2.);

  gd->Draw( "9sameP" );
  

  TLine *line = new TLine( data_presel_hist->GetBinLowEdge(data_presel_hist->GetXaxis()->GetFirst()),h_data_presel->GetBinContent(1),data_presel_hist->GetBinLowEdge(data_presel_hist->GetXaxis()->GetLast()+1),h_data_presel->GetBinContent(1));

  line->SetLineColor(kBlack);
  line->SetLineWidth(2);
  line->Draw();
  
  float ymaxlb = ymax * 0.6;
  float ymaxhb = ymax ;
  for(unsigned int b = 1; b < data_presel_hist->GetNbinsX(); b++){
    //Bin dividers
    if( b < 4) ymax = ymaxlb;
    else ymax = ymaxhb;
    TLine *lineb = new TLine( float(b), 0., float(b), ymax);
    lineb->SetLineColor(kRed);
    lineb->SetLineWidth(2);
    lineb->Draw();
  }

  

  legendH->AddEntry(gd, "Observed" , "pl");
  for(unsigned int j= 0 ; j < jetpt.size() ; j++){
    TH1F* h_mc_presel= (TH1F*)fmc->Get(param+jetpt.at(j));
    TH1F* h_np_presel= (TH1F*)fnp->Get(param+jetpt.at(j));
    TH1F* h_cf_presel= (TH1F*)fcf->Get(param+jetpt.at(j));
    
    if(j == 0){
      h_mc_presel->SetLineColor(kOrange);
    }
    if(j ==1){
      h_mc_presel->SetFillColor(870);
    }
    if(j == 2){
      h_mc_presel->SetFillColor(391);
    }
    if(j==3){
      h_mc_presel->SetFillColor(kBlue-2);
    }
    
    for(unsigned int i=1; i < h_mc_presel->GetNbinsX()+1 ; i++){
      float binerror = sqrt( (h_mc_presel->GetBinError(i)*h_mc_presel->GetBinError(i)) + ((h_mc_presel->GetBinContent(i)*0.2)*(h_mc_presel->GetBinContent(i)*0.2)));
      h_mc_presel->SetBinError(i , binerror);
    }
    for(unsigned int i=1 ;i < h_cf_presel->GetNbinsX()+1 ; i++){
      float binerror = sqrt( (h_cf_presel->GetBinError(i)*h_cf_presel->GetBinError(i)) + ((h_cf_presel->GetBinContent(i)*0.2)*(h_cf_presel->GetBinContent(i)*0.2)));
      h_cf_presel->SetBinError(i , binerror);
    }
    for(unsigned int i=1 ;i < h_np_presel->GetNbinsX()+1 ; i++){
      float binerror = sqrt( (h_np_presel->GetBinError(i)*h_np_presel->GetBinError(i)) + ((h_np_presel->GetBinContent(i)*0.4)*(h_np_presel->GetBinContent(i)*0.4)));
      h_np_presel->SetBinError(i , binerror);
    }
    
    h_mc_presel->Add(h_np_presel);
    h_mc_presel->Add(h_cf_presel);
    
    double jx[9], jxerr[9];
    double jy[9], jyerr[9];
    for(unsigned int i=0 ;i < h_mc_presel->GetNbinsX() ; i++){
      jx[i] = i + 0.4 + (0.1*float(j));
      jy[i] = h_mc_presel->GetBinContent(i+1);
      jyerr[i] =  h_mc_presel->GetBinError(i+1);
      jxerr[i] = 0.;
    }
    
    
    TGraphAsymmErrors * g = new TGraphAsymmErrors(9, jx, jy, jxerr, jxerr, jyerr, jyerr);

    if(j ==0){
      g->SetLineColor(kOrange);
      g->SetMarkerColor(kOrange);
      g->SetMarkerStyle(21.);
    }
    if(j ==1){
      g->SetLineColor(870);
      g->SetMarkerColor(870);
      g->SetMarkerStyle(22.);
    }
    if(j ==2){
      g->SetLineColor(kCyan);
      g->SetMarkerColor(kCyan);
      g->SetMarkerStyle(23.);
    }
    if(j ==3){
      g->SetLineColor(kBlue-2);
      g->SetMarkerColor(kBlue-2);
      g->SetMarkerStyle(23.);
    }
   
    g->SetLineWidth(2.);
    g->SetMarkerSize(2.);

    g->Draw( "9sameP" );
    

    legendH->AddEntry(g , "Awayjet pt > " + jetpt.at(j) , "lp");
  }
  legendH->Draw();
  
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

  TString label = "#bf{Preselection}";
  TString label2 = "#bf{2 Electrons + 2 Jets; Zveto }"; 
  float l = c1->GetLeftMargin()+0.05;
  latex.DrawLatex(l, 0.75 ,label);
  latex.DrawLatex(l, 0.7 ,label2);

  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/DataFakes/Preselection" + param + "_looseregion2.pdf"));
    
}



double GetError(TH1* h, bool up){
  const double alpha = 1 - 0.6827;
  if(!h) return 0.;
  TGraphAsymmErrors * g = new TGraphAsymmErrors(h);
  for (int i = 0; i < g->GetN(); ++i) {
    int N = g->GetY()[i];
    double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
    double U =  (N==0) ?  ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) :
      ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
    if ( N!=0 ) {
      if(up) return U-N;
      else return N-L;
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







