#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"

#include "Macro.h"

void RealEfficiency_dxy() {

  TFile * fdata = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/FakeRateCalculator_El_data_5_3_14.root");
  if(!fdata)cout << "No Data" << endl;

  /// Set Plotting style
  setTDRStyle();
  gStyle->SetPalette(1);
    
  vector<TString> plotname;
  plotname.push_back("05");
  plotname.push_back("10");
  plotname.push_back("15");
  plotname.push_back("20");
  plotname.push_back("25");
  plotname.push_back("30");

  
  int ihist(0);
  for(vector<TString>::iterator it = plotname.begin(); it!=plotname.end(); ++it,ihist++){
    int rebin=1;
    
    TH1F* h_num= (TH1F*)fdata->Get(("h_promptrate_dxy"+ *it + "_num_pt").Data());
    TH1F* h_denom= (TH1F*)fdata->Get(("h_promptrate_dxy" + *it +"_denom_pt").Data());
    h_num->Divide(h_denom);
    
    cout << "\n -------- " << *it << endl;
    for(unsigned int i=1; i < h_num->GetNbinsX()+1; i++){
      cout << "Bin value = " << h_num->GetBinContent(i) << endl;
    }
  }
}


