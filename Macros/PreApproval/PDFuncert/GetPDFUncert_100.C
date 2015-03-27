#include "Macro.h"
#include "CMS_lumi.h"
#include "TGraphAsymmErrors.h"

void GetPDFUncert_100(){
  
  
  setTDRStyle();
  //gStyle->SetPalette(1);
  
  TString spath = "/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron/HNDiElectron_SKHNee100_nocut_5_3_14.root";
  
  TFile * _file = new TFile(spath);
  
  TH1* h_cteq_total = (TH1*)_file->Get("limithist/100_defaultMassRegion_limithist_cteq");
  TH1* h_cteq_sum =  (TH1*)_file->Get("sum_cteq");
  h_cteq_total->Divide(h_cteq_sum);
  
  TH1* h_mstw_total = (TH1*)_file->Get("limithist/100_defaultMassRegion_limithist_mstw");
  TH1* h_mstw_sum =  (TH1*)_file->Get("sum_mstw");
  h_mstw_total->Divide(h_mstw_sum);
  
  TH1* h_nnpdf_total = (TH1*)_file->Get("limithist/100_defaultMassRegion_limithist_nnpdf");
  TH1* h_nnpdf_sum =  (TH1*)_file->Get("sum_nnpdf");
  h_nnpdf_total->Divide(h_nnpdf_sum);

  TH1* h_nominal = (TH1*)_file->Get("limithist/100_defaultMassRegion_limithist");

  TH1F* h_ref= (TH1F*)_file->Get(("NoCut_sigeff"));
  float nom = h_nominal->GetBinContent(2)/h_ref->Integral();
  
  
  h_nnpdf_total->SetMarkerColor(kOrange);
  h_nnpdf_total->SetMarkerStyle(24);
  h_nnpdf_total->GetYaxis()->SetRangeUser(0.016, 0.024);
  h_nnpdf_total->GetYaxis()->SetTitle("Acc. #times Eff.");
  h_nnpdf_total->GetXaxis()->SetTitle("Errorset");
  h_nnpdf_total->Draw("phist");

  
  float err_nnpdf=0.;
  for(unsigned int ic = 2 ; ic < h_nnpdf_total->GetNbinsX()+1; ic++){
    err_nnpdf +=(h_nnpdf_total->GetBinContent(ic)- h_nnpdf_total->GetBinContent(1)) * (h_nnpdf_total->GetBinContent(ic)- h_nnpdf_total->GetBinContent(1));
  }
  err_nnpdf = sqrt(err_nnpdf/105.);
 
  TH1* h_nnpdf_band = h_nnpdf_total->Clone("nnpdf");
  for(unsigned int ic = 1; ic < h_nnpdf_total->GetNbinsX()+1; ic++){
    h_nnpdf_band->SetBinContent(ic, h_nnpdf_total->GetBinContent(1));
    h_nnpdf_band->SetBinError(ic, err_nnpdf);
  }
  h_nnpdf_band->SetMarkerSize(0.);
  h_nnpdf_band->GetYaxis()->SetTitle("Acc. #times Eff.");
  h_nnpdf_band->GetXaxis()->SetTitle("m_N (GeV)");

  
  h_nnpdf_band->SetFillColor(kOrange);
  h_nnpdf_band->SetFillStyle(3003);
  h_nnpdf_band->Draw("E2same");
  



  h_cteq_total->SetMarkerColor(kGreen);
  h_cteq_total->SetMarkerStyle(22);
  h_cteq_total->Draw("phistsame");
  
  float err_cteq=0.;
  for(unsigned int ic = 2 ; ic < h_cteq_total->GetNbinsX()+1; ic++){
    err_cteq += (h_cteq_total->GetBinContent(ic) - h_cteq_total->GetBinContent(1)) * (h_cteq_total->GetBinContent(ic)- h_cteq_total->GetBinContent(1));
  }
  err_cteq = sqrt(err_cteq)/2.;
  cout << "err_cteq = " << err_cteq << " " <<  nom<< " " << (err_cteq*100/nom) << endl;
  
  TH1* h_cteq_band = h_cteq_total->Clone("cteq");
  for(unsigned int ic = 1; ic < h_cteq_total->GetNbinsX()+1; ic++){
    h_cteq_band->SetBinContent(ic, h_cteq_total->GetBinContent(1));
    h_cteq_band->SetBinError(ic, err_cteq);
  }
  
  h_cteq_band->SetMarkerSize(0.);
  h_cteq_band->SetFillColor(kGreen);
  h_cteq_band->SetFillStyle(3004);
  h_cteq_band->Draw("E2same");
 

  h_mstw_total->SetMarkerColor(kBlue);
  h_mstw_total->SetMarkerStyle(23);
  h_mstw_total->Draw("phistsame");
  
  float err_mstw=0.;
  for(unsigned int ic = 2 ; ic < h_mstw_total->GetNbinsX()+1; ic++){
    err_mstw +=(h_mstw_total->GetBinContent(ic)- h_mstw_total->GetBinContent(1)) * (h_mstw_total->GetBinContent(ic)- h_mstw_total->GetBinContent(1));
  }
  err_mstw = sqrt(err_mstw)/2.;

  TH1* h_mstw_band = h_mstw_total->Clone("mstw");
  for(unsigned int ic = 1; ic < h_mstw_total->GetNbinsX()+1; ic++){
    h_mstw_band->SetBinContent(ic, h_mstw_total->GetBinContent(1));
    h_mstw_band->SetBinError(ic, err_mstw);
  }

  h_mstw_band->SetMarkerSize(0.); 
  h_mstw_band->SetFillColor(kBlue);
  h_mstw_band->SetFillStyle(3005);
  h_mstw_band->Draw("E2same");
  

  TLine *line = new TLine(h_cteq_total->GetBinLowEdge(h_cteq_total->GetXaxis()->GetFirst()),nom,h_nnpdf_total->GetBinLowEdge(h_nnpdf_total->GetXaxis()->GetLast()+1),nom);
  
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->SetLineColor(kRed);
  line->Draw();
  cout << "Nom = " << nom << endl;
  
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();

  
 
  TLegend* legendH = new TLegend(0.6,0.2,0.8,0.4);
  legendH->SetFillColor(kWhite);
  legendH->SetTextFont(42);
  legendH->AddEntry(line, "CTEQ6L", "l");
  legendH->AddEntry(h_cteq_total, "CT10", "p");
  legendH->AddEntry(h_mstw_total, "MSTW2008nlo68cl", "p");
  legendH->AddEntry(h_nnpdf_total, "NNPDF20", "p");
  legendH->Draw();
  
  c1->SaveAs(("/home/jalmond/WebPlots/PreApproval/PDFSyst/mN_100_acc_eff_pdf.pdf"));
  

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
  float posY_ = 1-t+lumiTextOffset*t;
  if( !outOfFrame )
    {
      if( drawLogo )
        {
          posX_ =   l + 0.045*(1-l-r)*W/H;
          posY_ = t;
          float xl_0 = posX_;
          float yl_0 = posY_ ;
          float xl_1 = posX_ + 0.15*H/W;
          float yl_1 = posY_;
          /*TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
          TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
          pad_logo->Draw();
          pad_logo->cd();
          CMS_logo->Draw("X");
          pad_logo->Modified();
          pad->cd();*/
        }
      else
        {
          latex.SetTextFont(cmsTextFont);
          latex.SetTextSize(cmsTextSize*t);
          latex.SetTextAlign(align_);
          latex.DrawLatex(posX_, 0.985  , cmsText);
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





