#include "Macro.h"
#include "CMS_lumi.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"


double GetError(TH1* h, bool up);

void CheckClosure(){
  
  TString path_ttbar = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/MC/HNDiElectron_nonprompt_SKttbar_dilep_5_3_14.root";
  TString path_qcd= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/MC/HNDiElectron_nonprompt_SKQCD_dilep_5_3_14.root";
  TString path_qcd2= "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/MC/HNDiElectron_nonprompt_SKQCDdiem_dilep_5_3_14.root";
  TString path_wjet = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/MC/HNDiElectron_nonprompt_SKWjets_dilep_5_3_14.root";

  
  TH1::SetDefaultSumw2(true);

  setTDRStyle();
  gStyle->SetPalette(1);
  
  TFile * fttbar = new TFile(path_ttbar);
  TFile * fqcd = new TFile(path_qcd);
  TFile * fqcd2 = new TFile(path_qcd2);
  TFile * fwjet = new TFile(path_wjet);


  vector<TString> jetpt;
  jetpt.push_back("20");
  jetpt.push_back("30");
  jetpt.push_back("40");
  jetpt.push_back("60");

 
  
  vector<TString> list_of_names;
  list_of_names.push_back("pteta");
  list_of_names.push_back("hteta");
  list_of_names.push_back("bteta");
  list_of_names.push_back("pteta_b");
  list_of_names.push_back("pteta_h");
  list_of_names.push_back("pteta_cb");
  list_of_names.push_back("pteta_ht");
  list_of_names.push_back("pteta_pht");
  list_of_names.push_back("pteta_ht_b");

  vector<TString> collection;
  collection.push_back("MCclosure/HNTightMCSSclosure");
  collection.push_back("MCclosure/HNTight_loosereg2MCSSclosure");



  for(unsigned int k = 0 ; k < collection.size() ; k ++){
    cout << "\n ---------------------------------- " << endl;
    cout << "Collection = " << collection.at(k) << endl;
    cout << "\n ---------------------------------- " << endl;
    cout << "\n ---------------------------------- " << endl;

    TH1F* h_qcd_measured= (TH1F*)fqcd->Get((collection.at(k) + "_fake_measured"));
    TH1F* h_qcd2_measured= (TH1F*)fqcd2->Get((collection.at(k) + "_fake_measured"));
    TH1F* h_tt_measured= (TH1F*)fttbar->Get((collection.at(k) + "_fake_measured"));
    TH1F* h_w_measured= (TH1F*)fwjet->Get((collection.at(k) + "_fake_measured"));

    TH1F* h_qcd_doubletosingle= (TH1F*)fqcd->Get((collection.at(k) + "_mcclosure_Doubletosingle"));

    double qcd_ds_err_up= GetError(h_qcd_doubletosingle, true);
    double qcd_ds_err_down= GetError(h_qcd_doubletosingle, false);

    TH1F* h_qcd2_doubletosingle= (TH1F*)fqcd2->Get((collection.at(k) + "_mcclosure_Doubletosingle"));
    double qcd2_ds_err_up= GetError(h_qcd2_doubletosingle, true);
    double qcd2_ds_err_down= GetError(h_qcd2_doubletosingle, false);

    double qcd_err(0.);
    double qcd2_err(0.);

    double ttbar_err(0.);
    double w_err(0.);
    float qcd_tt =   h_qcd_measured->IntegralAndError(0, h_qcd_measured->GetNbinsX(), qcd_err, "");
    float qcd2_tt = 0.;
    if(h_qcd2_measured) qcd2_tt= h_qcd2_measured->IntegralAndError(0, h_qcd2_measured->GetNbinsX(), qcd2_err, "");
    float ttbar_tt =   h_tt_measured->IntegralAndError(0, h_tt_measured->GetNbinsX(),ttbar_err, "");
    float w_tt =   h_w_measured->IntegralAndError(0, h_w_measured->GetNbinsX(),w_err, "");
    
    
    double qcd_err_up= GetError(h_qcd_measured, true);
    double qcd2_err_up= GetError(h_qcd2_measured, true);
    double ttbar_err_up = GetError(h_tt_measured, true);
    double w_err_up = GetError(h_w_measured, true);
    
    double qcd_err_down= GetError(h_qcd_measured, false);
    double qcd2_err_down= GetError(h_qcd2_measured, false);
    double ttbar_err_down = GetError(h_tt_measured, false);
    double w_err_down = GetError(h_w_measured, false);
    
    
    for(unsigned int i = 0; i < list_of_names.size(); i++){
      cout << "\n ---------------------------------- " << endl;
      cout << "Method: " << list_of_names.at(i) << endl;
      cout << "\n ---------------------------------- " << endl;
      for(unsigned int j = 0; j < jetpt.size(); j++){
	
	TH1F* h_qcd_p= (TH1F*)fqcd->Get((collection.at(k) + "_fake_predicted" + jetpt.at(j) + list_of_names.at(i)));
	TH1F* h_qcd2_p= (TH1F*)fqcd2->Get((collection.at(k) + "_fake_predicted" + jetpt.at(j) + list_of_names.at(i)));
	TH1F* h_ttbar_p= (TH1F*)fttbar->Get((collection.at(k) + "_fake_predicted" + jetpt.at(j) + list_of_names.at(i)));
	TH1F* h_w_p= (TH1F*)fwjet->Get((collection.at(k) + "_fake_predicted"+ jetpt.at(j) + list_of_names.at(i)));

	double qcd_p_err, qcd2_p_err, ttbar_p_err, w_p_err;
	double int_qcd_p = h_qcd_p->IntegralAndError(0, h_qcd_p->GetNbinsX(), qcd_p_err, "");
	double int_qcd2_p = h_qcd2_p->IntegralAndError(0, h_qcd2_p->GetNbinsX(), qcd2_p_err, "");
	double int_ttbar_p = h_ttbar_p->IntegralAndError(0, h_ttbar_p->GetNbinsX(), ttbar_p_err, "");
	double int_w_p = h_w_p->IntegralAndError(0, h_w_p->GetNbinsX(), w_p_err, "");
	
	cout << "\n ------- " << endl;
	
	cout << "QCD  : measured = " << qcd2_tt   << " + " << qcd2_err_up   << " - " <<  qcd2_err_down  << " : awayjet " << jetpt.at(j) << " = " << int_qcd2_p   << " + " << qcd2_p_err << " - " << qcd2_p_err << " : p-m/p = " << (h_qcd2_p->Integral() - qcd2_tt ) / h_qcd2_p->Integral()  << endl; 
	cout << "TTBAR : measured = " << ttbar_tt << " + " << ttbar_err_up << " - " << ttbar_err_down << " : awayjet " << jetpt.at(j) << " = " <<  int_ttbar_p<< " + " << ttbar_p_err << " - " << ttbar_p_err << " : p-m/p = " << (h_ttbar_p->Integral() - ttbar_tt ) / h_ttbar_p->Integral()  << endl; 
	cout << "w     : measured = " << w_tt     << " + " << w_err_up     << " - " << w_err_down     << "  : awayjet " << jetpt.at(j) << " = " <<   int_w_p   << " + " << w_p_err << " - " << w_p_err <<  " : p-m/p= " << (h_w_p->Integral() - w_tt ) / h_w_p->Integral()  << endl; 
      }
    }
    
    bool dodiel=true;
    
    
    if(dodiel){
      
      for(unsigned int ij = 0 ; ij  < jetpt.size(); ij++){
	TString jpt =  jetpt.at(ij);
	cout << "Using fr measured with away jet pt cut = " << jpt << endl;
	cout << (collection.at(k) + "_mcclosure" +jpt + "_single") << endl;
	TH1F* h_qcd_single= (TH1F*)fqcd2->Get((collection.at(k) + "_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_b= (TH1F*)fqcd2->Get((collection.at(k) + "_b_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_h= (TH1F*)fqcd2->Get((collection.at(k) + "_h_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_bt= (TH1F*)fqcd2->Get((collection.at(k) + "_bt_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_ht= (TH1F*)fqcd2->Get((collection.at(k) + "_ht_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_pt= (TH1F*)fqcd2->Get((collection.at(k) + "_pt_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_st= (TH1F*)fqcd2->Get((collection.at(k) + "_st_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_st2= (TH1F*)fqcd2->Get((collection.at(k) + "_st2_mcclosure" +jpt + "_single"));
	TH1F* h_qcd_single_st3= (TH1F*)fqcd2->Get((collection.at(k) + "_st3_mcclosure" +jpt + "_single"));
	
	
	double err_single, err_single_b, err_single_ht, err_single_pt, err_single_st, err_single_st2, err_single_st3, err_single_bt, err_single_h;
	
	double int_single =    h_qcd_single->IntegralAndError(0, h_qcd_single->GetNbinsX(), err_single,"");
	double int_single_b =  h_qcd_single_b->IntegralAndError(0, h_qcd_single_b->GetNbinsX(), err_single_b,"");
	double int_single_h =  h_qcd_single_h->IntegralAndError(0, h_qcd_single_h->GetNbinsX(), err_single_h,"");
	double int_single_ht = h_qcd_single_ht->IntegralAndError(0, h_qcd_single_ht->GetNbinsX(), err_single_ht,"");
	double int_single_pt = h_qcd_single_pt->IntegralAndError(0, h_qcd_single_pt->GetNbinsX(), err_single_pt,"");
	double int_single_bt = h_qcd_single_bt->IntegralAndError(0, h_qcd_single_bt->GetNbinsX(), err_single_bt,"");
	double int_single_st = h_qcd_single_st->IntegralAndError(0, h_qcd_single_st->GetNbinsX(), err_single_st,"");
	double int_single_st2 = h_qcd_single_st2->IntegralAndError(0, h_qcd_single_st2->GetNbinsX(), err_single_st2,"");
	double int_single_st3 = h_qcd_single_st3->IntegralAndError(0, h_qcd_single_st3->GetNbinsX(), err_single_st3,"");
	
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value = "  <<  int_single << " +- " << err_single << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value b = "  <<  int_single_b << " +- " << err_single_b << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value h = "  <<  int_single_h << " +- " << err_single_h << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value ht= "  <<  int_single_ht << " +- " << err_single_ht << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value pt= "  <<  int_single_pt << " +- " << err_single_pt << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value bt= "  <<  int_single_bt << " +- " << err_single_bt << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value st= "  <<  int_single_st << " +- " << err_single_st << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value st2= "  <<  int_single_st2 <<  " +- " << err_single_st2 << endl;
	cout << "QCD2   : double to single measured = " <<  h_qcd2_doubletosingle->Integral()   <<  " predicted value st3= "  <<  int_single_st3 <<  " +- " << err_single_st3 << endl;
      }
    }
    
						 
  }
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





