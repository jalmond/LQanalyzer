#include "include/StdPlots.h"

StdPlots::StdPlots(TString name) {  

  h_particles = new TH1F("h_N_"+name,      "Number of "+name,   50,0,50);
  h_pt        = new TH1F("h_"+name+"_pt",  name+" p_{t} (GeV)", 500,0,500);
  h_eta       = new TH1F("h_"+name+"_eta", name+" #eta",        100,-5,5);
  h_phi       = new TH1F("h_"+name+"_phi", name+" #phi",        100,-3.1415926535,3.1415926535);

}

StdPlots::~StdPlots() {
  delete h_particles;
  delete h_pt;
  delete h_eta;
  delete h_phi;
}

void StdPlots::Fill(Double_t weight, Int_t N, Double_t pt, Double_t eta, Double_t phi) {
  h_particles->Fill(N,weight/N);
  h_pt->Fill(pt,weight);
  h_eta->Fill(eta,weight);
  h_phi->Fill(phi,weight);
}

void StdPlots::Write() {
 h_particles->Write();
 h_pt->Write();
 h_eta->Write();
 h_phi->Write();
}

