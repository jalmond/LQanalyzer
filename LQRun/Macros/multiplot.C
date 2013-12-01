#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TLine.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "TGraphAsymmErrors.h"

#include "SinglePlot.h"
#include "Single2dPlot.h"

#include "loadHN.C"

//gStyle->SetPalette(1);

bool multiplot() {

  //const bool OVERLAY_SAMEFILE = true;
  
  TFile* file[40] = {};

  std::vector<TString> filename;
  std::vector<TString> legendname;
  std::vector<TString> plotlabel;
  std::vector<double> weight;
  std::vector<bool> blegend;
  std::vector<int> color;
  std::vector<int> linecol;
  std::vector<std::string> type;

  std::vector<SinglePlot> hist1d;
  std::vector<Single2dPlot> hist2d;

  // SinglePlot(std::string name, unsigned int rebin, bool log, bool normalize, double scaleXmax, bool overflowbin)
  // Single2dPlot(std::string name, std::string drawOption, unsigned int rebinX, unsigned int rebinY)

  //loadFR(filename, legendname, plotlabel, hist1d, hist2d, weight);
  loadCFO(filename, legendname, plotlabel, color, linecol, type, hist1d, hist2d, weight, blegend);

  cout << filename.size() <<" "<< legendname.size() <<" "<< plotlabel.size() <<" "<< color.size() <<" "<< linecol.size() <<" "<< type.size() <<" "<<
    weight.size() <<" "<< blegend.size() <<endl;

  TH1F* h_th1f[40][1500] = {}; // [nfiles][nplots]
  TH2F* h_th2f[40][1500] = {}; // [nfiles][nplots]
  
  //for normal use use the whole loop but for plotting the fakes (same file as DATA) put filename.size()-1
  for (unsigned int ifile=0; ifile < filename.size(); ++ifile) {
    file[ifile] = new TFile(filename[ifile],"READ");
    if (!file[ifile]) {cout << "File open error on " << filename[ifile] <<endl; return 1; }
    file[ifile]->cd();

    if (file[ifile]->IsOpen()) {
      for (unsigned int iplot = 0; iplot < hist1d.size(); ++iplot) {
	//uncomment for normal use
	
	TH1F* temp = (TH1F*)file[ifile]->Get( "WZcontrol/"+hist1d[iplot].name()+"WZcontrol" );
	if (!temp) {
          cout << "\n1D plot " << hist1d[iplot].name() << " in " << filename[ifile].Data()<< " invalid!"<<endl;
          return 1;
        }
	h_th1f[ifile][iplot] = (TH1F*)temp->Clone();
	/*
	//comment for normal use
	h_th1f[ifile][iplot] = (TH1F*)file[ifile]->Get( "Heavy_Neutrino/"+hist1d[iplot].name()+"signal" );
	//h_th1f[ifile][iplot] = (TH1F*)file[ifile]->Get( "TotalFakes/"+hist1d[iplot].name()+"tf" );
	if (type[ifile] == "data")
	  h_th1f[ifile+1][iplot] = (TH1F*)file[ifile]->Get( "TotalFakes/"+hist1d[iplot].name()+"tf" );
	//h_th1f[ifile+1][iplot] = (TH1F*)file[ifile]->Get( "Heavy_Neutrino/"+hist1d[iplot].name()+"s3" );
	//endcomment
	*/	
      }
      
      for (unsigned int i2dplot = 0; i2dplot < hist2d.size(); i2dplot++) {
        h_th2f[ifile][i2dplot] = (TH2F*)file[ifile]->Get( hist2d[i2dplot].name().c_str() );
        if (!h_th2f[ifile][i2dplot]) { cout << TString("\n2D plot ") + hist2d[i2dplot].name() +" in "
					    << filename[ifile].Data() << " invalid!" <<endl; return 1;}
      }
    } else { cout << "File not open!" <<endl; return 1;}
    
  }
  
  /////////// Canvas, color and style parameters on top of the TDR style /////////
  unsigned int outputWidth = 1600;
  unsigned int outputHeight = 1200;
  
  TCanvas* can;
  // can = new TCanvas("can",""); // inherit height, width of CMS style
  can = new TCanvas("can","",outputWidth,outputHeight);
  
  TPad*    upperPad = new TPad("upperPad", "upperPad", .010, .210, .990, .990);
  TPad*    lowerPad = new TPad("lowerPad", "lowerPad", .010, .010, .990, .200);
  upperPad->Draw();
  lowerPad->Draw();

  can->Draw();

  //Int_t MarkerStyle[] = {20, 25, 5, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28};
  //Int_t lineStyle[] = {1, 7, 4, 3, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  ////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////////////
  //                                              2D plots                                      //
  ////////////////////////////////////////////////////////////////////////////////////////////////
  can->SetRightMargin(0.14);
  gPad->SetLogz(1);
  for (unsigned int i2dplot = 0; i2dplot < hist2d.size(); i2dplot++) {

    for (unsigned int ifile=0; ifile < filename.size(); ++ifile) {

      if (hist2d[i2dplot].rebinX() != 1 || hist2d[i2dplot].rebinY() != 1) {
        h_th2f[ifile][i2dplot]->Rebin2D( hist2d[i2dplot].rebinX(), hist2d[i2dplot].rebinY() );

        //h_th2f[ifile][i2dplot]->SetMarkerColor( Color[ifile] );

      }

      if (hist2d[i2dplot].title() != "")
        h_th2f[ifile][i2dplot]->SetTitle( hist2d[i2dplot].title().c_str() );
      
      //h_th2f[ifile][i2dplot]->GetYaxis()->SetRangeUser( 0, 2.0 );
      h_th2f[ifile][i2dplot]->GetYaxis()->SetTitleOffset(1.6);
      h_th2f[ifile][i2dplot]->Draw( hist2d[i2dplot].drawOption().c_str() );
/*      
      TLine* linex1 = new TLine(4.,350.,25.,350.);
      TLine* linex2 = new TLine(4.,550.,25.,550.);
      TLine* liney1 = new TLine(4.,350.,4.,2000.);
      TLine* liney2 = new TLine(8.,350.,8.,2000.);

      linex1->SetLineColor(kBlack);
      //linex1->SetLineStyle(7);
      linex1->SetLineWidth(2);

      linex2->SetLineColor(kBlack);
      //linex2->SetLineStyle(7);
      linex2->SetLineWidth(2);

      liney1->SetLineColor(kBlack);
      //liney1->SetLineStyle(7);
      liney1->SetLineWidth(2);

      liney2->SetLineColor(kBlack);
      //liney2->SetLineStyle(7);
      liney2->SetLineWidth(2);

      TText *ttB = new TText(5.5,400,"B");
      ttB->Draw();
      TText *ttA = new TText(5.5,1400,"A");
      ttA->Draw();
      TText *ttC = new TText(20,400,"C");
      ttC->Draw();
      TText *ttD = new TText(20,1400,"D");
      ttD->Draw();

      linex1->Draw();
      linex2->Draw();
      liney1->Draw();
      liney2->Draw();
*/
      //can->WaitPrimitive();
      
      can->Print(TString("mplot/")+TString(hist2d[i2dplot].name()) + TString("_")+ plotlabel[ifile]+ ".eps");
    }

    //can->Print(TString("mplot/") + TString(hist2d[i2dplot].name()) + ".eps");

  } // 2D plots
  
  ////////////////////////////////////////////////////////////////////////////////////////////////
  //                                              1D plots                                      //
  ////////////////////////////////////////////////////////////////////////////////////////////////
  can->SetRightMargin(0.04);
  THStack *hstack;

  for (unsigned int iplot = 0; iplot < hist1d.size(); iplot++) {

    //////////////////////////////////////////////////////////////////////////////////////////////
    //                         Rebinning, rescaling, find global max                            //
    //////////////////////////////////////////////////////////////////////////////////////////////
    
    float max = 0., globalMax = 0.;
    
    for (unsigned int ifile=0; ifile < filename.size(); ++ifile) {
      
      h_th1f[ifile][iplot]->Scale( weight[ifile] );
      h_th1f[ifile][iplot]->SetTitle( hist1d[iplot].title() );
      h_th1f[ifile][iplot]->GetXaxis()->SetTitle( hist1d[iplot].Xtitle() );
      h_th1f[ifile][iplot]->GetXaxis()->SetTitleOffset(1.05);
      h_th1f[ifile][iplot]->GetXaxis()->SetTitleSize(0.06);
      h_th1f[ifile][iplot]->GetXaxis()->SetLabelSize(0.05);
      h_th1f[ifile][iplot]->GetYaxis()->SetTitle( hist1d[iplot].Ytitle() );
      h_th1f[ifile][iplot]->GetYaxis()->SetTitleOffset(1.0);
      h_th1f[ifile][iplot]->GetYaxis()->SetTitleSize(0.06);
      h_th1f[ifile][iplot]->GetYaxis()->SetLabelSize(0.05);
      
      // Rebinning
      if (hist1d[iplot].rebin() != 1) h_th1f[ifile][iplot]->Rebin( hist1d[iplot].rebin() );

      // Change last bin to equal itself plus overflow
      // Does not work if x-axis scaling is used
      if ( hist1d[iplot].overflow() ) { 
        Int_t nbins = h_th1f[ifile][iplot]->GetNbinsX();
        Double_t lastbin_value = h_th1f[ifile][iplot]->GetBinContent(nbins);
        Double_t overflow_value = h_th1f[ifile][iplot]->GetBinContent(nbins + 1);
        h_th1f[ifile][iplot]->SetBinContent(nbins, lastbin_value + overflow_value );
      }

      // Normalize histograms to unit area:
      Double_t norm = h_th1f[ifile][iplot]->Integral();
      if( hist1d[iplot].normalize() && norm > 0)
      {
        h_th1f[ifile][iplot]->Scale(1./norm);
      }

      // Normalize histos to first histogram:
      if ( hist1d[iplot].normToFirst() ) {

        Double_t normFirst = h_th1f[0][iplot]->Integral();
        Double_t normLatter = h_th1f[ifile][iplot]->Integral();

        if (normLatter > 0)
          h_th1f[ifile][iplot]->Scale(normFirst/normLatter);
      }

      // Get maximum value of this histogram to determine global max
      max = h_th1f[ifile][iplot]->GetBinContent( h_th1f[ifile][iplot]->GetMaximumBin() );
      if (max > globalMax) globalMax = max; //FIXME: this can be changed to set max to max of first file

      // Rescale X axis
      if ( hist1d[iplot].scaleXmax() != 1. ) {
        h_th1f[ifile][iplot]->GetXaxis()->SetRangeUser(
        //     h_th1f[ifile][iplot]->GetXaxis()->GetXmin() * hist1d[iplot].scaleXmax() ,
        //     h_th1f[ifile][iplot]->GetXaxis()->GetXmax() * hist1d[iplot].scaleXmax() );
             h_th1f[ifile][iplot]->GetXaxis()->GetXmin(),
             hist1d[iplot].scaleXmax() );
      }

      h_th1f[ifile][iplot]->SetLineColor(linecol[ifile]);

      if ( hist1d[iplot].normalize() )
        h_th1f[ifile][iplot]->SetLineColor( color[ifile] );

      if (type[ifile] == "signal") {
        //h_th1f[ifile][iplot]->SetLineColor( color[ifile] );        
        h_th1f[ifile][iplot]->SetLineStyle( 1 );
      }
      else if (type[ifile] == "data") {
        h_th1f[ifile][iplot]->SetMarkerStyle(20);
        h_th1f[ifile][iplot]->SetMarkerColor( color[ifile] );
      }
      else if (type[ifile] == "mc") {
        if ( hist1d[iplot].stack())
          h_th1f[ifile][iplot]->SetFillColor( color[ifile] );
        else 
	  h_th1f[ifile][iplot]->SetLineColor( color[ifile] );
      }

      if ( hist1d[iplot].log() ) upperPad->SetLogy(1);
      else upperPad->SetLogy(0);

    } // files

    /////////////////////////////////////////////////////////////////////////
    //       After modifing the histrograms create stack and total         //
    ////////////////////////////////////////////////////////////////////////

    TH1F* htotal = (TH1F*)h_th1f[0][iplot]->Clone("htotal");
    htotal->Reset();
    
    hstack = new THStack("hstack", h_th1f[0][iplot]->GetTitle());
    int nstack = 0;

    for (unsigned int ifile = 0; ifile < filename.size(); ifile++) {
      if (type[ifile] == "mc" && hist1d[iplot].stack()) {
        nstack++;
        hstack->Add(h_th1f[ifile][iplot]);
        htotal->Add(h_th1f[ifile][iplot]);
      }
    }

    if (nstack)
      if ( htotal->GetBinContent( htotal->GetMaximumBin() ) > globalMax )
        globalMax = htotal->GetBinContent( htotal->GetMaximumBin() );

    //////////////////////////////////////////////////////////
    //      Colors, markers, fills, labels, offsets         //
    //////////////////////////////////////////////////////////

    TString drawn = "9";
    upperPad->cd();
    for (unsigned int ifile = 0; ifile < filename.size(); ifile++) {

      if ( hist1d[iplot].log() ) {
        h_th1f[ifile][iplot]->SetMaximum(globalMax*1.5);
        h_th1f[ifile][iplot]->SetMinimum(0.1); //FIXME ad hoc
      }
      else { 
	h_th1f[ifile][iplot]->SetMaximum(globalMax*1.2);
	h_th1f[ifile][iplot]->SetMinimum(0.0); //FIXME ad hoc
      }

      if (type[ifile] == "mc" && !hist1d[iplot].stack()) {
        h_th1f[ifile][iplot]->Draw( (drawn+"hist").Data() );
	drawn = "9same";
      }

      if (type[ifile] == "signal" ) {
        h_th1f[ifile][iplot]->Draw( (drawn+"hist").Data() );
	drawn = "9same";
      }

      if ( type[ifile] == "data") {
	h_th1f[ifile][iplot]->Draw( (drawn+"pX0").Data() );
	drawn = "9same";
      }	       
	
    } // files
		       
    /////////////////////////////////////////////////////////////////////
    //                     Plot MC background stack                    //
    /////////////////////////////////////////////////////////////////////
    if (nstack) {
      hstack->Draw( (drawn+"hist").Data() );
    }

    nstack = 0;

    /////////////////////////////////////////////////////////////////////
    //            Plot Signal MC and Data again (and last)             //
    /////////////////////////////////////////////////////////////////////
    for (unsigned int ifile = 0; ifile < filename.size(); ifile++) {
      if (type[ifile] == "signal" ) {
	h_th1f[ifile][iplot]->SetLineWidth(2.0);
	h_th1f[ifile][iplot]->Draw( (drawn+"hist").Data());
      }
      if ( type[ifile] == "data") {
	const double alpha = 1 - 0.6827;
	TGraphAsymmErrors * g = new TGraphAsymmErrors(h_th1f[ifile][iplot]);
	for (int i = 0; i < g->GetN(); ++i) {
	  int N = g->GetY()[i];
	  double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
	  double U =  (N==0) ?  ( ROOT::Math::gamma_quantile_c(alpha,N+1,1) ) :
	    ( ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) );
	  if ( N!=0 ) {
	    g->SetPointEYlow(i, N-L );
	    g->SetPointEXlow(i, 0);
	    g->SetPointEYhigh(i, U-N );
	    g->SetPointEXhigh(i, 0);
	  }
	  else {
	    g->SetPointEYlow(i, 0.);
	    g->SetPointEXlow(i, 0);
	    g->SetPointEYhigh(i, 0.); 
 	    g->SetPointEXhigh(i, 0);
	  }
	}
	g->SetLineWidth(2.0);
	g->SetMarkerSize(0.);
	g->Draw( (drawn+"p").Data() );
      
	h_th1f[ifile][iplot]->SetMarkerStyle(20);
	h_th1f[ifile][iplot]->SetMarkerSize(2.3);
	h_th1f[ifile][iplot]->SetLineWidth(2.0);
	h_th1f[ifile][iplot]->Draw( (drawn+"pX0").Data() );
	//h_th1f[ifile][iplot]->Draw( "samep9X0" );
      }

    } //files

    ///////////////////////////////////////////////////////////////////////
    //                           Deviation                               //
    ///////////////////////////////////////////////////////////////////////
      
    lowerPad->cd();
    if (true) {
      Double_t *staterror;
      TH1F* hdev = (TH1F*)h_th1f[0][iplot]->Clone("hdev");
      TH1F* hdev_err = (TH1F*)h_th1f[0][iplot]->Clone("hdev_err");
      TH1F* hdev_err_stat = (TH1F*)h_th1f[0][iplot]->Clone("hdev_err_stat");
      //hdev->Reset();
      //hdev_err->Reset();
      //hdev_err_stat->Reset();
      staterror = new Double_t [hdev->GetNbinsX()+1];
      for (Int_t i=0;i<=hdev->GetNbinsX();i++)
	staterror[i]=0;

      for (unsigned int ifile = 0; ifile < filename.size(); ifile++)
	{
	  for (Int_t i=1;i<=hdev->GetNbinsX();i++) {
	    if ( ifile == filename.size()-1 ) {
	      hdev_err->SetBinContent(i, 1.0);
	      if (htotal->GetBinContent(i) > 0 && h_th1f[ifile][iplot]->GetBinContent(i) > 0) {
		hdev_err->SetBinError(i, 0.35*h_th1f[ifile][iplot]->GetBinContent(i)/htotal->GetBinContent(i));
	      }
	      else 
		hdev_err->SetBinError(i, 0.0);
	    }
	    if ( type[ifile] != "data" && type[ifile] != "signal" ) {
	      staterror[i] += pow(h_th1f[ifile][iplot]->GetBinError(i),2);
	    }
	    
	    if ( type[ifile] == "data") {
	      if (htotal->GetBinContent(i)>0 && h_th1f[ifile][iplot]->GetBinContent(i)>0) {
		//hdev->SetBinContent(i, (h_th1f[ifile][iplot]->GetBinContent(i)-htotal->GetBinContent(i))/sqrt(h_th1f[ifile][iplot]->GetBinContent(i)) );
		hdev->SetBinContent(i, h_th1f[ifile][iplot]->GetBinContent(i)/htotal->GetBinContent(i) );
		hdev->SetBinError(i, sqrt(h_th1f[ifile][iplot]->GetBinContent(i))/htotal->GetBinContent(i) );
	      }
	      else {
		hdev->SetBinContent(i, -99.0);
		hdev->SetBinError(i, 0.0);
	      }
	    }
	  }
	}
      for (Int_t i=1;i<=hdev->GetNbinsX();i++) {
	hdev_err_stat->SetBinContent(i,1);
	if (htotal->GetBinContent(i)>0)
	  hdev_err_stat->SetBinError(i, sqrt(pow(hdev_err->GetBinError(i)*htotal->GetBinContent(i),2)+staterror[i]) / htotal->GetBinContent(i) );
	//else
	//hdev_err_stat->SetBinError(i, 0.065);
      }
      //hdev->GetYaxis()->SetTitle( "#frac{Data-MC}{#sqrt{Data}}" );
      hdev->GetYaxis()->SetTitle( "#frac{Data}{MC}" );
      hdev->GetYaxis()->SetTitleSize(.15);
      hdev->GetYaxis()->SetTitleOffset(0.51);
      hdev->GetYaxis()->SetRangeUser(0.,+2.);
      hdev->GetYaxis()->SetLabelSize(.08);
      hdev->GetYaxis()->SetNdivisions(9);
      hdev->GetXaxis()->SetLabelSize(.08);
      hdev->GetXaxis()->SetTitle("");
      hdev->SetMarkerStyle(20);
      hdev->SetMarkerSize(2);
      hdev->SetLineColor(kBlack);
      hdev_err->SetFillColor(kRed);
      hdev_err->SetLineColor(kRed);
      hdev_err->SetFillStyle(3444);
      hdev_err_stat->SetFillColor(kOrange-9);
      hdev_err_stat->SetLineColor(kOrange-9);
      //    hdev_err_stat->SetFillStyle(3490);
      hdev->Draw("p9");
      hdev_err_stat->Draw("sameE4");
      hdev_err->Draw("sameE4");
      hdev->Draw("samep9");
      
      // delete hdev;
      // delete hdev_err;
      // delete hdev_err_stat;

      TLine *devp = new TLine(hdev->GetXaxis()->GetXmin(),3,hdev->GetXaxis()->GetXmax(),3);
      devp->SetLineWidth(1);
      devp->SetLineStyle(8);
      //	devp->Draw("SAME");
      TLine *devm = new TLine(hdev->GetXaxis()->GetXmin(),-3,hdev->GetXaxis()->GetXmax(),-3);
      devm->SetLineWidth(1);
      devm->SetLineStyle(8);
      //	devm->Draw("SAME");
      TLine *devz = new TLine(hdev->GetXaxis()->GetXmin(),1,hdev->GetXaxis()->GetXmax(),1);
      devz->SetLineWidth(1);
      devz->SetLineStyle(1);
      devz->Draw("SAME");	
    }

    if (false) {
      TH1F* hdev = (TH1F*)h_th1f[0][iplot]->Clone("hdev");
      for (unsigned int ifile = 1; ifile < filename.size(); ifile++)
	{
	  if ( type[ifile] == "signal") 
	    for (Int_t i=1;i<=hdev->GetNbinsX();i++) {
	      if (h_th1f[ifile][iplot]->Integral(i,hdev->GetNbinsX())+htotal->Integral(i,hdev->GetNbinsX()) > 0)
		hdev->SetBinContent(i,h_th1f[ifile][iplot]->Integral(i,hdev->GetNbinsX())/sqrt(h_th1f[ifile][iplot]->Integral(i,hdev->GetNbinsX())+htotal->Integral(i,hdev->GetNbinsX())+pow(h_th1f[filename.size()-1][iplot]->Integral(i,hdev->GetNbinsX())*0.35,2) ) );
	      //if (h_th1f[ifile][iplot]->Integral(1,i)+htotal->Integral(1,i) > 0)
		//hdev->SetBinContent(i,h_th1f[ifile][iplot]->Integral(1,i)/sqrt(h_th1f[ifile][iplot]->Integral(1,i)+htotal->Integral(1,i)+pow(h_th1f[filename.size()-1][iplot]->Integral(1,i)*0.35,2) ) );
	    }
	}
      hdev->SetLineColor(kBlack);
      hdev->GetYaxis()->SetTitle( "#frac{S}{#sqrt{S+B+(.35B_{fake})^{2}}}" );
      hdev->GetYaxis()->SetTitleOffset(0.7);
      hdev->GetYaxis()->SetTitleSize(0.10);
      hdev->GetYaxis()->SetLabelSize(0.05);
      hdev->GetYaxis()->SetRangeUser(0.,+1.5);
      hdev->Draw("L");
    }

    upperPad->cd();

       
    ///////////////////////////////////////////////////////////////////////
    //                             Legend                                //
    ///////////////////////////////////////////////////////////////////////

    //TPaveText* pave = new TPaveText(.3,0.95,0.9,0.98);
    // pave->AddText("#sqrt{7} TeV  CMS preliminary 2011   L=702 pb^{-1}");
    TLatex* text1 = new TLatex(3.570061,23.08044,"#sqrt{s}=8 TeV 2012 pp run L=19.8 fb^{-1}");
    text1->SetNDC();
    text1->SetTextAlign(13);
    text1->SetX(0.2);
    text1->SetY(0.995);
    text1->SetTextFont(42);
    text1->SetTextSizePixels(10);
    text1->SetTextSize(0.036);
 
    TLegend *legend = new TLegend(.65, 0.945 - 8*0.065, .93, 0.91); // xmin ymin xmax ymax (0.65, 0.945 - (size), 0.95, 945)
    for (int ileg = legendname.size() - 1; ileg >= 0; ileg--)
    {
      if (blegend[ileg])
      {
        //if (type[ileg] == "data")
        //  legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "lep");
        //if (type[ileg] == "signal")
        //  legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "l");
        if (type[ileg] == "mc")
          legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "fl");
      }
    }
    htotal->SetLineColor(0);
    //    legend->AddEntry(htotal, "Background Uncertainty", "f");
    for (unsigned int ileg = 0; ileg < legendname.size(); ileg++)
    {
      if (blegend[ileg])
      {
        if (type[ileg] == "data")
          legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "lpe");
        if (type[ileg] == "signal")
	  legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "l");
	  
        //if (type[ileg] == "mc")
        //  legend->AddEntry(h_th1f[ileg][iplot], legendname[ileg], "fl");
      }
    }

    /*
    TLine *taglioM = new TLine(0.679,0,0.679,30.);
    taglioM->SetLineColor(kMagenta);
    taglioM->SetLineWidth(2);
    taglioM->Draw("SAME");
    TLine *taglioL = new TLine(0.898,0,0.898,30.);
    taglioL->SetLineColor(kYellow);
    taglioL->SetLineWidth(2);
    taglioL->Draw("SAME");
    */
    legend->SetFillColor(kWhite);
    legend->SetLineColor(kBlack);
    legend->SetBorderSize(1);
    //legend->SetFillStyle(1001);
    legend->SetShadowColor(0); // 0 = transparent
    legend->SetEntrySeparation(0.3);
    gPad->RedrawAxis();
    legend->Draw("SAME");
    //text1->Draw("SAME");
    if (hist1d[iplot].normalize()) can->Print(TString("mplot/") + TString(hist1d[iplot].name()) + "norm.eps");
    else if (hist1d[iplot].log())  can->Print(TString("mplot/") + TString(hist1d[iplot].name()) + "log.eps");
    else                           can->Print(TString("mplot/") + TString(hist1d[iplot].name()) + ".eps");

    delete legend;
    delete hstack;
    delete htotal;
    
  } // 1D plots

  delete can;

  return 0;
}
