{
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1);


  string maindir = "/home/jalmond/LQanalyzer/data/output/ElectronFakes/";
  
  TFile * file_data = new TFile ((maindir + "FakeRateCalculator_El_periodAtoD_SKsingleegamma_5_3_8.root").c_str());

  TH1* h_loose_eta = (TH1*)file_data->Get("LooseEl_eta");
  TH1* h_loose_pt = (TH1*)file_data->Get("LooseEl_pt");
  TH1* h_loose_njets = (TH1*)file_data->Get("LooseEl_njets");

  TH1* h_tight_eta = (TH1*)file_data->Get("TightEl_eta");
  TH1* h_tight_pt = (TH1*)file_data->Get("TightEl_pt");
  TH1* h_tight_njets = (TH1*)file_data->Get("TightEl_njets");

  
  h_tight_eta->Divide(h_loose_eta);
  h_tight_pt->Divide(h_loose_pt);
  h_tight_njets->Divide(h_loose_njets);
  
  
  TCanvas * c = new TCanvas("","",800,600);
  c->cd();
  
  h_tight_eta->GetXaxis()->SetTitle("El #eta");
  h_tight_pt->GetXaxis()->SetTitle("El p_{T} [GeV]");
  h_tight_njets->GetXaxis()->SetTitle("njets");
  
  h_tight_eta->GetYaxis()->SetTitle("#epsilon_{fake}");
  h_tight_pt->GetYaxis()->SetTitle("#epsilon_{fake}");
  h_tight_njets->GetYaxis()->SetTitle("Entries");

  h_tight_eta->Draw("Hist");
  
  c->SaveAs("./FR_eta.png");
  
  h_tight_pt->Draw("Hist");
  h_tight_pt->Rebin(2);
  h_tight_pt->GetXaxis()->SetRangeUser(20.,100.);
  c->SaveAs("./FR_pt.png");

  h_tight_njets->Draw("Hist");
  c->SaveAs("./FR_njets.png");


  TH1* h_promptrate_denom_barrel_pt = (TH1*)file_data->Get("h_promptrate_denom_barrel_pt");
  TH1* h_promptrate_denom_endcap_pt = (TH1*)file_data->Get("h_promptrate_denom_endcap_pt");
  TH1* h_promptrate_denom_njets = (TH1*)file_data->Get("h_promptrate_denom_njets");
  TH1* h_promptrate_denom_eta = (TH1*)file_data->Get("h_promptrate_denom_eta");
  
  TH1* h_promptrate_num_barrel_pt = (TH1*)file_data->Get("h_promptrate_num_barrel_pt");
  TH1* h_promptrate_num_endcap_pt = (TH1*)file_data->Get("h_promptrate_num_endcap_pt");
  TH1* h_promptrate_num_njets = (TH1*)file_data->Get("h_promptrate_num_njets");
  TH1* h_promptrate_num_eta = (TH1*)file_data->Get("h_promptrate_num_eta");

  h_promptrate_num_barrel_pt->Divide(h_promptrate_denom_barrel_pt);
  h_promptrate_num_endcap_pt->Divide(h_promptrate_denom_endcap_pt);
  h_promptrate_num_njets->Divide(h_promptrate_denom_njets);
  h_promptrate_num_eta->Divide(h_promptrate_denom_eta);

  h_promptrate_num_barrel_pt->GetXaxis()->SetTitle("el p_{T} [GeV]");
  h_promptrate_num_endcap_pt->GetXaxis()->SetTitle("el p_{T} [GeV]");
  h_promptrate_num_njets->GetXaxis()->SetTitle("number of jets");
  h_promptrate_num_eta->GetXaxis()->SetTitle("el #eta");

  h_promptrate_num_barrel_pt->GetYaxis()->SetTitle("#epsilon_{prompt}");
  h_promptrate_num_endcap_pt->GetYaxis()->SetTitle("#epsilon_{prompt}");
  h_promptrate_num_njets->GetYaxis()->SetTitle("Entries");
  h_promptrate_num_eta->GetYaxis()->SetTitle("#epsilon_{prompt}");

  h_promptrate_num_barrel_pt->Draw("hist");
  
  c->SaveAs("./PR_barrel_pt.png");
  
  h_promptrate_num_endcap_pt->Draw("hist");
  c->SaveAs("./PR_endcap_pt.png");

  h_promptrate_num_njets->Draw("hist");
  c->SaveAs("./PR_njet.png");

  h_promptrate_num_eta->Draw("hist");
  c->SaveAs("./PR_eta.png");

}
