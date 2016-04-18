//#include "Riostream.h"
//#include "TGraph.h"
//#include "TH1.h"
//#include <vector>


//void MET_punzii_opt(){
{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetHistLineWidth(2);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111);

  TChain * f_chain = new TChain("MyTree");
  f_chain->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_SKnonprompt_dilep_5_3_14.root");
  f_chain->LoadTree(0) ;
  
  TChain * f_chainmc = new TChain("MyTree");
  f_chainmc->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_mc_5_3_14.root");
  f_chainmc->LoadTree(0) ;
  

  const int imasses = 10;
  TString  masses[imasses] = {"40", "60", "80", "90", "100",  "150",  "200", "300", "400", "500"};
  int color[imasses] = {kOrange+8, kOrange - 7 , kRed + 1, kRed - 6,kSpring +2, kSpring -6, kCyan + 3, kCyan -8, kBlue+2, kBlue-6 };
  TGraph* graphs[imasses];
  
  for(int im = 0 ; im < imasses ; im++){
    TChain * f_chainsig = new TChain("MyTree");
    f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_SKHNee" + masses[im] + "_nocut_5_3_14.root");
    TFile * file = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_SKHNee" + masses[im] + "_nocut_5_3_14.root");
    cout << file << endl;
    float  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_ht;
    float k_weight=0.;
    int k_njet;
    float k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
    
    f_chain->SetBranchAddress("met", &k_met);
    f_chain->SetBranchAddress("ee_mass", &k_eemass);
    f_chain->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chain->SetBranchAddress("e1jj_mass", &k_e1jjmass);
    f_chain->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chain->SetBranchAddress("jj_mass", &k_jjmass);
    f_chain->SetBranchAddress("st", &k_st);
    f_chain->SetBranchAddress("ht", &k_ht);
    f_chain->SetBranchAddress("njet", &k_njet);
    f_chain->SetBranchAddress("el1_pt", &k_el1pt);
    f_chain->SetBranchAddress("el2_pt", &k_el2pt);
    f_chain->SetBranchAddress("jet1_pt", &k_j1pt);
    f_chain->SetBranchAddress("weight", &k_weight);
    
    f_chainmc->SetBranchAddress("met", &k_met);
    f_chainmc->SetBranchAddress("ee_mass", &k_eemass);
    f_chainmc->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chainmc->SetBranchAddress("e1jj_mass", &k_e1jjmass);
    f_chainmc->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chainmc->SetBranchAddress("jj_mass", &k_jjmass);
    f_chainmc->SetBranchAddress("st", &k_st);
    f_chainmc->SetBranchAddress("ht", &k_ht);
    f_chainmc->SetBranchAddress("njet", &k_njet);
    f_chainmc->SetBranchAddress("el1_pt", &k_el1pt);
    f_chainmc->SetBranchAddress("el2_pt", &k_el2pt);
    f_chainmc->SetBranchAddress("jet1_pt", &k_j1pt);
    f_chainmc->SetBranchAddress("weight", &k_weight);
    
    f_chainsig->SetBranchAddress("met", &k_met);
    f_chainsig->SetBranchAddress("ee_mass", &k_eemass);
    f_chainsig->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chainsig->SetBranchAddress("e1jj_mass", &k_e1jjmass);
    f_chainsig->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chainsig->SetBranchAddress("jj_mass", &k_jjmass);
    f_chainsig->SetBranchAddress("st", &k_st);
    f_chainsig->SetBranchAddress("ht", &k_ht);
    f_chainsig->SetBranchAddress("njet", &k_njet);
    f_chainsig->SetBranchAddress("el1_pt", &k_el1pt);
    f_chainsig->SetBranchAddress("el2_pt", &k_el2pt);
    f_chainsig->SetBranchAddress("jet1_pt", &k_j1pt);
    f_chainsig->SetBranchAddress("weight", &k_weight);
    
    
    
    float sum_event =0.;
    for(Int_t i = 0; i < f_chain->GetEntries(); i++){
      f_chain->GetEntry(i) ;
      
      if( (i % 100000) == 0) cout << "Bkg: N processing = " << i << endl;
      sum_event+= k_weight;
    }
    
    for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
      f_chainmc->GetEntry(i) ;
      
      if( (i % 100000) == 0) cout << "Bkg: N processing = " << i << endl;
      sum_event+= k_weight;
    }
    
    
    float sum_sigevent =0.;
    for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
      f_chainsig->GetEntry(i) ;
      
      if( (i % 100000) == 0) cout << "Sig: N processing = " << i << endl;
      sum_sigevent+=k_weight;
    }
    
    cout << "Total bkg = " << sum_event  << endl;
    cout << "Total sig = " <<  sum_sigevent << endl;
    
    const int nm = 50;
    float xaxis[nm];
    for(int pt =0; pt <nm; pt ++){
      float ptcut = 20. + float(pt)*5.;
      xaxis[pt] = ptcut;
    }
    
    float y_punzi[nm];
    
    int imet_opt=0;
    float imeejjmin_opt=0.;
    float imeejjmax_opt=0.;
    float ipt1_opt=0.;
    float ipt2_opt=0.;
    float sig_eff_opt=0.;
    float sig_eff_opt_presel=0.;
    float cut_sum_opt=0.;
    float opt_cut_sb=0.;
    float ieemin_opt=0.;
    float ieemax_opt=0.;
    float ie2jjmin_opt=0.;
    float ie2jjmax_opt=0.;
    float ie1jjmin_opt=0.;
    float ie1jjmax_opt=0.;
    float istmin_opt=0.;
    float istmax_opt=0.;
    float ihtmin_opt=0.;
    float ihtmax_opt=0.;
    float ijetpt_opt=0.;
    int injet_opt=0.;
    
    TH1* hnsig = (TH1F*)file->Get(("eventcutflow"));
    
    float nsig = float(hnsig->GetBinContent(2));
    cout << "Number of signal events before any cut = " << nsig << endl; 
    
    for(unsigned int ipt=0; ipt < nm; ipt++){
      float pt_cut = xaxis[ipt];
      cout << "PT : "<< pt_cut << endl;
      
      /// Optmise cuts:
      float cut_sum=0.;
      float np_sum=0.;
      for(Int_t i = 0; i < f_chain->GetEntries(); i++){
	f_chain->GetEntry(i) ;
	if(k_eemass > 80. && k_eemass < 100) continue;
	if(k_jjmass > 110.) continue;
	if(k_jjmass < 50.) continue;
	if(k_el1pt < pt_cut) continue;
	cut_sum+=k_weight;
	np_sum+=k_weight;
      }
      
      for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
	f_chainmc->GetEntry(i) ;
	if(k_jjmass > 110.) continue;
	if(k_jjmass < 50.) continue;
	if(k_eemass > 80. && k_eemass < 100) continue;
	if(k_el1pt < pt_cut) continue;
	
	cut_sum+=k_weight;
      }
      
      float cut_sum_sig=0.;
      for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
	f_chainsig->GetEntry(i) ;
	if(k_eemass > 80. && k_eemass < 100) continue;
	if(k_jjmass > 110.) continue;
	if(k_jjmass < 50.) continue;
	if(k_el1pt < pt_cut)continue;
	cut_sum_sig+=k_weight;
      }
      
      float sig_eff = cut_sum_sig /nsig ;
      float total_bkg = cut_sum;
      float bkgtmp = total_bkg + (0.28* np_sum)* (0.28* np_sum);
      float denom = 1. + sqrt(bkgtmp);
      float punzi = sig_eff / denom;
      y_punzi[ipt] = punzi;
      
      if((cut_sum_sig / sum_sigevent) < 0.4) continue;
      if( (punzi) > opt_cut_sb){
	opt_cut_sb = punzi;
	ipt_opt = ipt;
	sig_eff_opt = sig_eff;
	sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
	cut_sum_opt= cut_sum;
	cout << "Max punzi = " << punzi << " : nbkg = " << total_bkg <<  " : %sig = " << sig_eff_opt_presel*100. << endl;
	
      }
    }
    
    cout << "Opt punzi = " << opt_cut_sb << endl;
    cout << "Opt cut : PT <  " << xaxis[ipt_opt] << endl;
    cout << "Cut (opt) eff. bkg = " << cut_sum_opt/sum_event  <<  " nbkg = " << cut_sum_opt << endl;
    cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
    
    
    graphs[im] = new TGraph(nm, xaxis, y_punzi);
    graphs[im]->SetMarkerColor(color[im]);
    graphs[im]->SetLineColor(color[im]);
    
    graphs[im]->SetLineWidth(2);
    graphs[im]->SetNameTitle(masses[im] + " GeV" , masses[im] + " GeV");
  }
  
  

  TColor::CreateColorWheel();
  
  int W = 800;
  int H = 600;
  TCanvas* c1 = new TCanvas("c1", "c1",10,10,W,H);
  int H_ref = 600;
  int W_ref = 800;

  // references for T, B, L, R                                                  
  float T = 0.08*H_ref;
  float B = 0.15*H_ref;
  float L = 0.17*W_ref;
  float R = 0.04*W_ref;
  c1->SetFillColor(0);

  c1->SetBorderMode(0);
  c1->SetFrameFillStyle(0);
  c1->SetFrameBorderMode(0);
  c1->SetLeftMargin( L/W );
  c1->SetRightMargin( R/W );
  c1->SetTopMargin( T/H );
  c1->SetBottomMargin( B/H );
  c1->SetTickx(0);
  c1->SetTicky(0);

  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  gROOT->LoadMacro("CMS_lumi.C");
  TH1 *frame = new TH1F("frame","",1000,20,200);
  frame->SetMinimum(1e-5);
  frame->SetMaximum(10);
  frame->SetDirectory(0);
  frame->SetStats(0);
  frame->GetXaxis()->SetTitle("El_{1} P_{T} GeV");
  //frame->GetXaxis()->SetTitleSize(0.045);                                     
  frame->GetXaxis()->SetTitleOffset(1.05);
  //frame->GetXaxis()->SetTickLength(0.02);                                     
  //frame->GetXaxis()->SetLabelSize(0.04);                                      
  frame->GetXaxis()->SetRangeUser(20, 220);
  frame->GetYaxis()->SetTitle("Punzi");
  //frame->GetYaxis()->SetTitleSize(0.045);                                     
  //frame->GetYaxis()->SetTitleOffset(0.95);                                    
  //frame->GetYaxis()->SetLabelSize(0.04);                                      
  frame->GetYaxis()->SetRangeUser(0.0001,5.);
  frame->Draw(" ");
  c1->SetLogy();

  
  TLegend* leg = new TLegend(0.6, .60, .90, 0.85);
  for(int j=0; j < 10; j++){
    graphs[j]->Draw("plsame");
    leg->AddEntry(graphs[j], masses[j] + " GeV", "pl");
  }
  leg->SetFillColor(kWhite);
  leg->SetTextFont(42);

  leg->Draw();
  CMS_lumi( c1, 2, 11 );
  c1->Update();
  c1->RedrawAxis();
  
  c1->SaveAs("/home/jalmond/WebPlots/Opt/Punzi/PT1_punzi_optimisation.pdf");
}
