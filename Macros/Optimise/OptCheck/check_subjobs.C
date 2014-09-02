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

void Opt_d0cut(){
  
  
  
  setTDRStyle();
  gStyle->SetPalette(1);
  
  std::vector<TString> masses;
  masses.push_back("1");
  masses.push_back("2");
  masses.push_back("3");
  masses.push_back("4");
  masses.push_back("5");
  masses.push_back("6");
  masses.push_back("7");
  masses.push_back("8");
  masses.push_back("9");
  masses.push_back("10");
  masses.push_back("11");
  masses.push_back("12");
  masses.push_back("13");
  masses.push_back("14");
  masses.push_back("15");
  masses.push_back("16");
  masses.push_back("17");
  masses.push_back("18");
  masses.push_back("19");
  masses.push_back("20");
  masses.push_back("21");
  masses.push_back("22");
  masses.push_back("23");
  masses.push_back("24");
  masses.push_back("25");
  masses.push_back("26");
  masses.push_back("27");
  masses.push_back("28");
  masses.push_back("29");
  masses.push_back("30");

  for(unsigned int im=0; im < masses.size(); im++){
    TFile * fsig = new TFile(("/home/jalmond/LQ_SKTreeOutput/SKHNee40_nocut_75036/output/SKHNee40_nocut_5_3_14_"+masses.at(im) +".root").Data());
    cout << "\n ----------------" << endl;
    cout <<  "New mass : " << masses.at(im) << endl;
    TH1F* h_cutflow= (TH1F*)fsig->Get(("isocutflow"));

    for(int i=0; i < h_cutflow->GetNbinsX()+1; i++){
      cout << h_cutflow->GetBinContent(i) << endl;
    }
    cout << "d0 0.05 eff = " << h_cutflow->GetBinContent(2)/ h_cutflow->GetBinContent(1) << endl;
    cout << "d0 0.10 eff = " << h_cutflow->GetBinContent(3)/ h_cutflow->GetBinContent(1) << endl;
    cout << "d0 0.15 eff = " << h_cutflow->GetBinContent(4)/ h_cutflow->GetBinContent(1) << endl;
    cout << "d0 0.20 eff = " << h_cutflow->GetBinContent(5)/ h_cutflow->GetBinContent(1) << endl;
    cout << "d0 0.25 eff = " << h_cutflow->GetBinContent(6)/ h_cutflow->GetBinContent(1) << endl;
    cout << "d0 0.30 eff = " << h_cutflow->GetBinContent(7)/ h_cutflow->GetBinContent(1) << endl;
    
  }
  //TCanvas* c1 = new TCanvas((("Plot")+*it).Data(), "Plot", 800, 600);
  ///c1->SaveAs(("/home/jalmond/WebPlots/Fakes/RealRff_" +  *it + ".pdf"));
  
}

