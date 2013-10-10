#include "JetPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

JetPlots::JetPlots(TString name) : StdPlots(name) {

  h_TCHPT              = new TH1F("h_"+name+"_TCHPT","Track Counting High Purity "+name,100,-3,5);
  h_JP                 = new TH1F("h_"+name+"_JP",name+" Jet Probability",100,0,3);
  h_CSV                = new TH1F("h_"+name+"_CSV",name+" Combined Seconday Vertex",100,-1,2);
  h_dxy                = new TH1F("h_"+name+"_dxy",name+" transverse IP",100,0.0,0.5);
  h_dz                 = new TH1F("h_"+name+"_dz",name+" longitudinal IP",100,0.0,1.0);
  h_threeD             = new TH1F("h_"+name+"_threeD",name+" threeD vertex distance",100,0.,1.0);
}

JetPlots::~JetPlots() {
  // ~StdPlots();
  delete h_TCHPT;
  delete h_JP;
  delete h_CSV;
  delete h_dxy;
  delete h_dz;
  delete h_threeD;
}

void JetPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi, Double_t TCHPT, Double_t JP, Double_t CSV, Double_t dxy, Double_t dz, Double_t threeD) {

 StdPlots::Fill(weight, N, pt, eta, phi);
 
  h_TCHPT->Fill(TCHPT, weight);
  h_JP->Fill(JP, weight);
  h_CSV->Fill(CSV, weight);
  h_dxy->Fill(dxy, weight);
  h_dz->Fill(dz, weight);
  h_threeD->Fill(threeD, weight);
}

void JetPlots::Write() {
  StdPlots::Write();
  h_TCHPT->Write();
  h_JP->Write();
  h_CSV->Write();
  h_dxy->Write();
  h_dz->Write();
  h_threeD->Write();
}

