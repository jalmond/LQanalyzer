{
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetPalette(1);


  string maindir = getenv("LQANALYZER_DIR");

  TFile * file_data1 = new TFile ((maindir + "/data//output/Analyzer_muon_periodA.root").c_str());
  TFile * file_data2 = new TFile ((maindir + "/data//output/Analyzer_muon_periodB.root").c_str());
  TFile * file_data3 = new TFile ((maindir + "/data//output/Analyzer_muon_periodC.root").c_str());
  TFile * file_data4 = new TFile ((maindir + "/data//output/Analyzer_muon_periodD.root").c_str());
  TFile * file_DY_highmass = new TFile ((maindir + "/data/output/Analyzer_DY50plus.root").c_str());
  TFile * file_DY_lowmass = new TFile ((maindir + "/data/output/Analyzer_DY10to50.root").c_str());
  TH1* h_data = (TH1*)file_data1->Get("h_zpeak_mumu");
  TH1* h_data2 = (TH1*)file_data2->Get("h_zpeak_mumu");
  TH1* h_data3 = (TH1*)file_data3->Get("h_zpeak_mumu");
  TH1* h_data4 = (TH1*)file_data4->Get("h_zpeak_mumu");

  TH1* h_dy_lowmass = (TH1*)file_DY_lowmass->Get("h_zpeak_mumu");
  TH1* h_dy_highmass = (TH1*)file_DY_highmass->Get("h_zpeak_mumu");

  TCanvas * c = new TCanvas("","",800,600);
  c->cd();
  c->SetLogy();

  h_data->Add(h_data2);
  h_data->Add(h_data3);
  h_data->Add(h_data4);

  h_data->Rebin(5);
  h_data->GetXaxis()->SetRangeUser(15.,200.);
  h_data->GetYaxis()->SetRangeUser(1.,5000000.);
  h_data->GetYaxis()->SetTitle("Entries / 5 GeV");
  h_data->GetXaxis()->SetTitle("m(#mu#mu) [GeV]");
  h_data->SetMarkerStyle(20);
  h_data->SetMarkerSize(1.5);
  h_data->Draw("p9");

  h_dy_lowmass->SetLineColor(kRed);
  h_dy_lowmass->SetLineWidth(2.5);
  h_dy_lowmass->Add(h_dy_highmass);
  h_dy_lowmass->Rebin(5);
  h_dy_lowmass->Draw("HISTSAME");

  TLegend* legend =  new TLegend(0.6,0.7,0.9,0.9);
  legend->AddEntry(h_data, "Data", "p");
  legend->AddEntry(h_dy_lowmass, "Drell Yan", "l");
  legend->SetFillColor(kWhite);
  legend->SetLineColor(kBlack);
  legend->SetBorderSize(1);
  //legend->SetFillStyle(1001);                                                                                                                                                    
  legend->SetShadowColor(0); // 0 = transparent                                                                                                                                    
  legend->SetEntrySeparation(0.3);
  legend->Draw("same");

  c->SaveAs("./Ztomumu.pdf");
  
}
