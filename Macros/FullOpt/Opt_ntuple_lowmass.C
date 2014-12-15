#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void Opt_ntuple_lowmass(){

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetHistLineWidth(2);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111);


  vector<TString> masses;
  masses.push_back("40");
  masses.push_back("50");
  masses.push_back("60");
  masses.push_back("70");
  masses.push_back("80");
  masses.push_back("90");

  for(unsigned int imass = 0; imass < masses.size(); imass++){
    
    TChain * f_chain = new TChain("MyTree");
    f_chain->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKnonprompt_dilep_5_3_14.root");
    f_chain->LoadTree(0) ;
    
    TChain * f_chainmc = new TChain("MyTree");
    f_chainmc->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_mc_5_3_14.root");
    f_chainmc->LoadTree(0) ;
    
    TChain * f_chainsig = new TChain("MyTree");
    
    f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee" + masses.at(imass) + "_nocut_5_3_14.root");
    TFile * file = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee" + masses.at(imass) +"_nocut_5_3_14.root");

    float  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_ht;
    float k_weight=0.;
    int k_njet, k_nbjet_m;
    float k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0., k_el1eta=0., k_el2eta=0.;
    bool k_cl1bjet,k_cl2bjet,k_cll1bjet,k_cll2bjet;
    
    
    f_chain->SetBranchAddress("met", &k_met);
    f_chain->SetBranchAddress("ee_mass", &k_eemass);
    f_chain->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chain->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chain->SetBranchAddress("jj_mass", &k_jjmass);
    f_chain->SetBranchAddress("nbjet_m", &k_nbjet_m);
    f_chain->SetBranchAddress("el1_pt", &k_el1pt);
    f_chain->SetBranchAddress("el2_pt", &k_el2pt);
    f_chain->SetBranchAddress("weight", &k_weight);
    
    f_chainmc->SetBranchAddress("met", &k_met);
    f_chainmc->SetBranchAddress("ee_mass", &k_eemass);
    f_chainmc->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chainmc->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chainmc->SetBranchAddress("jj_mass", &k_jjmass);
    f_chainmc->SetBranchAddress("nbjet_m", &k_nbjet_m);
    f_chainmc->SetBranchAddress("el1_pt", &k_el1pt);
    f_chainmc->SetBranchAddress("el2_pt", &k_el2pt);
    f_chainmc->SetBranchAddress("weight", &k_weight);
    
    f_chainsig->SetBranchAddress("met", &k_met);
    f_chainsig->SetBranchAddress("ee_mass", &k_eemass);
    f_chainsig->SetBranchAddress("eejj_mass", &k_eejjmass);
    f_chainsig->SetBranchAddress("e2jj_mass", &k_e2jjmass);
    f_chainsig->SetBranchAddress("jj_mass", &k_jjmass);
    f_chainsig->SetBranchAddress("nbjet_m", &k_nbjet_m);
    f_chainsig->SetBranchAddress("el1_pt", &k_el1pt);
    f_chainsig->SetBranchAddress("el2_pt", &k_el2pt);
    f_chainsig->SetBranchAddress("weight", &k_weight);


  float sum_event =0.;
  for(Int_t i = 0; i < f_chain->GetEntries(); i++){
    f_chain->GetEntry(i) ;
    
    sum_event+= k_weight;
  }
  
  for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
    f_chainmc->GetEntry(i) ;

    sum_event+= k_weight;
  }

  
  float sum_sigevent =0.;
  for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
    f_chainsig->GetEntry(i) ;

    sum_sigevent+=k_weight;
  }


  std::vector<float> METcut;
  
  METcut.push_back(30.);
  
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


  TH1* hnsig =   (TH1F*)file->Get(("eventcutflow"));

  float nsig = float(hnsig->GetBinContent(2));

  for(unsigned int imet=0; imet < METcut.size(); imet++){
    float met_cut = METcut.at(imet);
    for(int imeejjmin= 0; imeejjmin < 1. ; imeejjmin++){
      float meejjmin_cut = 80.;
      for(int imeejjmax= 0; imeejjmax <1. ; imeejjmax++){
	float meejjmax_cut = 10000 ;
	for(int ipt1= 0; ipt1 <1. ; ipt1++){
	  float pt1_cut =  20. + float(ipt1)*5.;
	  
	  for(int ipt2= 0; ipt2 < 1. ; ipt2++){
	    float pt2_cut =  15. + float(ipt2)*5.;
	    if(pt2_cut > pt1_cut) continue;
	    
	    for(int ieemin =0 ; ieemin < 1; ieemin++){
	      float eemin_cut =  10. + float(ieemin)* 5.;
		
	      for(int ieemax =0 ; ieemax <1 ; ieemax++){
		float eemax_cut =  10000. + float(ieemax) * 10. ;
		if(ieemax == 3) eemax_cut = 100000.;

		    for(int ie2jjmin =0 ; ie2jjmin < 1 ; ie2jjmin++){
		      float e2jjmin_cut = 0.;
		      
		      for(int ie2jjmax =0 ; ie2jjmax < 1 ; ie2jjmax++){
			float e2jjmax_cut =  10000000.;
			
			/// Optmise cuts:
			float cut_sum=0.;
			float np_sum=0.;
			int n_mc=0;
			for(Int_t i = 0; i < f_chain->GetEntries(); i++){
			  f_chain->GetEntry(i) ;
			  if(k_eemass > 80. && k_eemass < 100) continue;
			  if(k_jjmass > 120.) continue;
			  if(k_nbjet_m !=0) continue;
	
			  if(k_e2jjmass < e2jjmin_cut) continue;
			  if(k_e2jjmass > e2jjmax_cut) continue;
			  if(k_eemass < eemin_cut) continue;
			  if(k_eemass > eemax_cut) continue;
			  if(k_met > met_cut) continue;
			  if(k_eejjmass < meejjmin_cut) continue;
			  if(k_eejjmass > meejjmax_cut) continue;
			  if(k_el1pt < pt1_cut) continue;
			  if(k_el2pt < pt2_cut) continue;

			  cut_sum+=k_weight;
			  np_sum+=k_weight;
			}
			
			for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
			  f_chainmc->GetEntry(i) ;
			  if(k_jjmass > 120.) continue;
			  if(k_eemass > 80. && k_eemass < 100) continue;
			  if(k_eemass < eemin_cut) continue;
			  if(k_eemass > eemax_cut) continue;
			  
			  if(k_nbjet_m !=0) continue;
			  if(k_e2jjmass < e2jjmin_cut) continue;
			  if(k_e2jjmass > e2jjmax_cut) continue;
			  if(k_met > met_cut) continue;
			  if(k_eejjmass < meejjmin_cut) continue;
			  if(k_eejjmass > meejjmax_cut) continue;
			  if(k_el1pt < pt1_cut) continue;
			  if(k_el2pt < pt2_cut) continue;
			  n_mc += 1;
			  cut_sum+=k_weight;
			}
			
			float cut_sum_sig=0.;
			for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
			  f_chainsig->GetEntry(i) ;
			  if(k_eemass > 80. && k_eemass < 100) continue;
			  if(k_jjmass > 120.) continue;
			  
			  if(k_e2jjmass < e2jjmin_cut) continue;
			  if(k_e2jjmass > e2jjmax_cut) continue;
			  
			  //if(k_nbjet_m !=0) continue;
			  if(k_eemass < eemin_cut) continue;
			  if(k_eemass > eemax_cut) continue;
			  
			  if(k_met > met_cut)continue;
			  
			  if(k_eejjmass < meejjmin_cut) continue;
			  if(k_eejjmass > meejjmax_cut) continue;
			  
			  if(k_el1pt < pt1_cut) continue;
			  if(k_el2pt < pt2_cut) continue;
			  
			  
			  cut_sum_sig+=k_weight;
			}
			
			float sig_eff = cut_sum_sig /nsig ;
			float total_bkg = cut_sum;
			float bkgtmp = total_bkg + (0.35* np_sum)* (0.35* np_sum);
			float denom = 1. + sqrt(bkgtmp);
			float punzi = sig_eff / denom;
			
			
			//if( (cut_sum_sig / sum_sigevent) < 0.5) continue;
			
			
			if( (punzi) > opt_cut_sb){
			  opt_cut_sb = punzi;
			  imet_opt = imet;

			  imeejjmin_opt = meejjmin_cut;
			  imeejjmax_opt = meejjmax_cut;
			  ipt1_opt=  pt1_cut;
			  ipt2_opt=  pt2_cut;
			  			  
			  ieemin_opt =  eemin_cut;
			  ieemax_opt =  eemax_cut;
			  ie2jjmin_opt = e2jjmin_cut;
			  ie2jjmax_opt = e2jjmax_cut;
			  sig_eff_opt = sig_eff;
			  
			  sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
			  cut_sum_opt= cut_sum;
			  
			}
		      }
		    }
		    
	      }//jetpt
	    }
	  }
	}/// meejjmin
      }/// MET 
    }
  }
  
  //Opt cut
  cout << "\n ------ " << endl;
  cout << "Mass = " << masses.at(imass) << endl;

  cout << "Opt cut : MET <  " << METcut.at(imet_opt) << endl;
  cout << "Opt cut : " << imeejjmin_opt << " < M(eejj) <  " << imeejjmax_opt << endl;
  cout << "Opt cut : " << ie2jjmin_opt << " < M(e2jj) <  " << ie2jjmax_opt << endl;
  cout << "Opt cut : " << ieemin_opt << " < M(ee) < " << ieemax_opt<< endl;

  cout << "Number of mc = " << n_mc << endl;

  cout << "Opt pt1 = " << ipt1_opt << endl;
  cout << "Opt pt2 = " << ipt2_opt << endl;


  cout << "Opt punzi = " << opt_cut_sb << endl;
  cout << "Cut (opt) nbkg = " << cut_sum_opt << endl;
  cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
  cout << "\n ------ " << endl;
  }
  
}
