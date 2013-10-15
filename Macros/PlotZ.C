{

  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1);


  string maindir = getenv("MAINDIR");

  TFile * file_data = new TFile ((maindir + "/output/DoubleMu_periodA_1.root").c_str());
  TFile * file_DY_highmass = new TFile ((maindir + "/output/DYhighMass_1.root").c_str());
  TFile * file_DY_lowmass = new TFile ((maindir + "/output/DYLowMass_1.root").c_str());
  TH1* h_data = (TH1*)file_data->Get("h_zpeak");
  TH1* h_dy_lowmass = (TH1*)file_DY_lowmass->Get("h_zpeak");
  TH1* h_dy_highmass = (TH1*)file_DY_highmass->Get("h_zpeak");

  TCanvas * c = new TCanvas("","",800,600);
  c->cd();
  c->SetLogy();
  h_data->GetYaxis()->SetRangeUser(1.,60000.);
  h_data->GetXaxis()->SetTitle("m(#mu#mu) [GeV]");
  h_data->Rebin(5);
  h_data->Draw();

  h_dy_lowmass->SetLineColor(kRed);
  h_dy_lowmass->SetLineWidth(2.5);
  h_dy_lowmass->Add(h_dy_highmass);
  h_dy_lowmass->Rebin(5);
  h_dy_lowmass->Draw("HISTSAME");
  c->SaveAs("./Ztomumu.pdf");
  
}
