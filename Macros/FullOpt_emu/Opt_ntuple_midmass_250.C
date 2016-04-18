#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void Opt_ntuple_midmass_250(){

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetHistLineWidth(2);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111);

  TChain * f_chain = new TChain("MyTree");
  f_chain->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKnonprompt_dilep_5_3_14.root");
  f_chain->LoadTree(0) ;
  
  TChain * f_chainmc = new TChain("MyTree");
  f_chainmc->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_mc_5_3_14.root");
  f_chainmc->LoadTree(0) ;

  TChain * f_chainsig = new TChain("MyTree");
  f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNmue250_nocut_5_3_14.root");
  f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNemu250_nocut_5_3_14.root");
  TFile * file1 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNmue250_nocut_5_3_14.root");
  TFile * file2 = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectronMuon/HNEMu_SKHNemu250_nocut_5_3_14.root");

  float  k_met=0., k_emumass=0., k_emujjmass=0., k_l1jjmass=0., k_l2jjmass=0.;
  float k_weight=0.;
  int k_njet, k_nbjet_m;
  float k_l1pt=0., k_l2pt=0., k_j1pt=0., k_jjmass=0., k_l1eta=0., k_l2eta=0.;

  

  f_chain->SetBranchAddress("met", &k_met);
  f_chain->SetBranchAddress("emu_mass", &k_emumass);
  f_chain->SetBranchAddress("emujj_mass", &k_emujjmass);
  f_chain->SetBranchAddress("l2jj_mass", &k_l2jjmass);
  f_chain->SetBranchAddress("jj_mass", &k_jjmass);
  f_chain->SetBranchAddress("nbjet_m", &k_nbjet_m);
  f_chain->SetBranchAddress("l1_pt", &k_l1pt);
  f_chain->SetBranchAddress("l2_pt", &k_l2pt);
  f_chain->SetBranchAddress("jet1_pt", &k_j1pt);
  f_chain->SetBranchAddress("weight", &k_weight);
    

  f_chainmc->SetBranchAddress("met", &k_met);
  f_chainmc->SetBranchAddress("emu_mass", &k_emumass);
  f_chainmc->SetBranchAddress("emujj_mass", &k_emujjmass);
  f_chainmc->SetBranchAddress("l2jj_mass", &k_l2jjmass);
  f_chainmc->SetBranchAddress("jj_mass", &k_jjmass);
  f_chainmc->SetBranchAddress("l1_pt", &k_l1pt);
  f_chainmc->SetBranchAddress("l2_pt", &k_l2pt);
  f_chainmc->SetBranchAddress("jet1_pt", &k_j1pt);
  f_chainmc->SetBranchAddress("weight", &k_weight);
  f_chainmc->SetBranchAddress("nbjet_m", &k_nbjet_m);


  f_chainsig->SetBranchAddress("met", &k_met);
  f_chainsig->SetBranchAddress("emu_mass", &k_emumass);
  f_chainsig->SetBranchAddress("emujj_mass", &k_emujjmass);
  f_chainsig->SetBranchAddress("l2jj_mass", &k_l2jjmass);
  f_chainsig->SetBranchAddress("jj_mass", &k_jjmass);
  f_chainsig->SetBranchAddress("l1_pt", &k_l1pt);
  f_chainsig->SetBranchAddress("l2_pt", &k_l2pt);
  f_chainsig->SetBranchAddress("jet1_pt", &k_j1pt);
  f_chainsig->SetBranchAddress("weight", &k_weight);
  f_chainsig->SetBranchAddress("nbjet_m", &k_nbjet_m);


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
  

  std::vector<float> METcut;
  //  METcut.push_back(100000.);
  METcut.push_back(35.);
  
  int imet_opt=0;
  float imemujjmin_opt=0.;
  float imemujjmax_opt=0.;
  float ipt1_opt=0.;
  float ipt2_opt=0.;

  float sig_eff_opt=0.;
  float sig_eff_opt_presel=0.;
  float cut_sum_opt=0.;
  float opt_cut_sb=0.;
  float iemumin_opt=0.;
  float iemumax_opt=0.;
  float il2jjmin_opt=0.;
  float il2jjmax_opt=0.;

  float ijetpt_opt=0.;
  int injet_opt=0.;

  TH1* hnsig =   (TH1F*)file1->Get(("CutFlow/_eventcutflow"));
  TH1* hnsig2 =   (TH1F*)file2->Get(("CutFlow/_eventcutflow"));
  
  float nsig = float(hnsig->GetBinContent(2)+hnsig2->GetBinContent(2));
  float nsig_now = float(hnsig->GetBinContent(1) + hnsig2->GetBinContent(1));

  
  cout << "Number of signal events before any cut = " << nsig << endl; 
  
  int iemujj_min_k = 8;
  int iemujj_max_k = 1;
  int iemu_min_k = 1;
  int iemu_max_k = 1;
  int i_pt1_k = 10;
  int i_pt2_k =7;
  int i_ljj_min_k = 1;
  int i_ljj_max_k = 1;
  int i_jet_k = 3;
  
  int nit_tot = iemujj_min_k* iemujj_max_k * iemu_min_k*iemu_max_k*i_pt1_k*i_pt2_k*i_ljj_min_k*i_ljj_max_k*i_jet_k;
  int nit=0;
  for(unsigned int imet=0; imet < METcut.size(); imet++){
    float met_cut = METcut.at(imet);

    for(int imemujjmin= 0; imemujjmin < iemujj_min_k ; imemujjmin++){
      float memujjmin_cut = 190. + float(imemujjmin) * 10.;
      for(int imemujjmax= 0; imemujjmax < iemujj_max_k ; imemujjmax++){
	float memujjmax_cut = 100000.+ float(imemujjmax)*5.;

	for(int ipt1= 0; ipt1 < i_pt1_k ; ipt1++){
	  float pt1_cut =  50. + float(ipt1)*5.;
	  for(int ipt2= 0; ipt2 < i_pt2_k ; ipt2++){
	    float pt2_cut =  30. + float(ipt2)*5.;
	    if(pt2_cut > pt1_cut) continue;
	    
	    for(int iemumin =0 ; iemumin < iemu_min_k; iemumin++){
		float emumin_cut =  20. + float(iemumin)* 10.;
		if(iemumin == 7) emumin_cut = 100.;
		
		for(int iemumax =0 ; iemumax <iemu_max_k ; iemumax++){
		  float emumax_cut =  50. + float(iemumax) * 25. ;
		  if(iemumax == 0) emumax_cut = 100000.;
		  cout << emumin_cut << " <  emu < " <<   emumax_cut << endl;
	  
		  for(int il2jjmin =0 ; il2jjmin < i_ljj_min_k ; il2jjmin++){
		    float l2jjmin_cut = 0. + float(il2jjmin)* 10.;
		      
		      for(int il2jjmax =0 ; il2jjmax < i_ljj_max_k ; il2jjmax++){
			float l2jjmax_cut =  150. + float(il2jjmax)* 10.;
			if(il2jjmax == 0) l2jjmax_cut = 10000.;
				
			for(int ijpt =0 ; ijpt <i_jet_k ; ijpt++){
			  nit++; 
			  float jetpt_cut = 30. + float(ijpt)*5.;
			  cout << "it : " << nit << " / " << nit_tot << endl; 
			  /// Optmise cuts:
			  float cut_sum=0.;
			  float np_sum=0.;
			  int n_mc=0;
			  for(Int_t i = 0; i < f_chain->GetEntries(); i++){
			    f_chain->GetEntry(i) ;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    if(k_nbjet_m !=0) continue;
			    if(k_l2jjmass < l2jjmin_cut) continue;
			    if(k_l2jjmass > l2jjmax_cut) continue;
			    if(k_emumass < emumin_cut) continue;
			    if(k_emumass > emumax_cut) continue;
			    if(k_met > met_cut) continue;
			    if(k_emujjmass < memujjmin_cut) continue;
			    if(k_emujjmass > memujjmax_cut) continue;
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_l1pt < pt1_cut) continue;
			    if(k_l2pt < pt2_cut) continue;
			    
			    cut_sum+=k_weight;
			    np_sum+=k_weight;
			  }
			  
			  for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
			    f_chainmc->GetEntry(i) ;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
                            if(k_nbjet_m !=0) continue;

                            if(k_l2jjmass < l2jjmin_cut) continue;
                            if(k_l2jjmass > l2jjmax_cut) continue;
                            if(k_emumass < emumin_cut) continue;
                            if(k_emumass > emumax_cut) continue;
                            if(k_met > met_cut) continue;
                            if(k_emujjmass < memujjmin_cut) continue;
                            if(k_emujjmass > memujjmax_cut) continue;
                            if(k_j1pt < jetpt_cut) continue;
                            if(k_l1pt < pt1_cut) continue;
                            if(k_l2pt < pt2_cut) continue;

			    n_mc += 1;
			    cut_sum+=k_weight;
			  }
			  
			  float cut_sum_sig=0.;
			  float cut_sum_sig_now=0.;
			  for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
			    f_chainsig->GetEntry(i) ;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
                            if(k_nbjet_m !=0) continue;

                            if(k_l2jjmass < l2jjmin_cut) continue;
                            if(k_l2jjmass > l2jjmax_cut) continue;
                            if(k_emumass < emumin_cut) continue;
                            if(k_emumass > emumax_cut) continue;
                            if(k_met > met_cut) continue;
                            if(k_emujjmass < memujjmin_cut) continue;
                            if(k_emujjmass > memujjmax_cut) continue;
                            if(k_j1pt < jetpt_cut) continue;
                            if(k_l1pt < pt1_cut) continue;
                            if(k_l2pt < pt2_cut) continue;
			    
			    
			    cut_sum_sig+=k_weight;
			    cut_sum_sig_now+=1;
			  }
				      
			  float sig_eff = cut_sum_sig /nsig ;
			  float sig_eff_now = cut_sum_sig_now /nsig_now ;
			  float total_bkg = cut_sum;
			  float bkgtmp = total_bkg + (0.28* np_sum)* (0.4* np_sum);
			  float denom = 1. + sqrt(bkgtmp);
			  float punzi = sig_eff / denom;
			  cout << "punzi = " << punzi << " " << sig_eff << " " << denom << endl;
			  
			  cout << "NSIG after cuts = " << cut_sum_sig_now  << " weighted = " << cut_sum_sig << endl;
			  cout << "SIG EF NOW =  " << sig_eff_now << " weighted = " << sig_eff << endl;
			  
			  cout << cut_sum_sig / sum_sigevent << endl;
			  
			  if( (punzi) > opt_cut_sb){
			    opt_cut_sb = punzi;
			    imet_opt = imet;
			    imemujjmin_opt = memujjmin_cut;
			    imemujjmax_opt = memujjmax_cut;
			    ipt1_opt=  pt1_cut;
			    ipt2_opt=  pt2_cut;
			    iemumin_opt =  emumin_cut;
			    iemumax_opt =  emumax_cut;
			    il2jjmin_opt = l2jjmin_cut;
			    il2jjmax_opt = l2jjmax_cut;
			    ijetpt_opt = jetpt_cut;
			    sig_eff_opt = sig_eff;
			    
			    sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
			    cut_sum_opt= cut_sum;
			    cout << "Max punzi = " << punzi << " : nbkg = " << total_bkg <<  " : %sig = " << sig_eff_opt_presel*100. << endl;
			    
			  }
			}
		      }//stmax
		  }//stmin
		}//e2jjmax
	    }//eemax
	  }//eemin
	}//pt2
      }//pt1
    }// meejjmax
  }/// meejjmin

  //Opt cut
  cout << "Opt punzi = " << opt_cut_sb << endl;
  cout << "Opt cut : MET <  " << METcut.at(imet_opt) << endl;
  cout << "Opt cut : " << imemujjmin_opt << " < M(emujj) <  " << imemujjmax_opt << endl;
  cout << "Opt cut : " << il2jjmin_opt << " < M(l2jj) <  " << il2jjmax_opt << endl;
  cout << "Opt cut : " << iemumin_opt << " < M(emu) < " << iemumax_opt<< endl;
  
  cout << "Number of mc = " << n_mc << endl;

  cout << "Opt pt1 = " << ipt1_opt << endl;
  cout << "Opt pt2 = " << ipt2_opt << endl;

  cout << "Opt jet1pt = " << ijetpt_opt << endl;
  cout << "Cut (opt) eff. bkg = " << cut_sum_opt/sum_event  <<  " nbkg = " << cut_sum_opt << endl;
  cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
  
  
}
