#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void Opt_ntuple_midmass_150(){

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

  TChain * f_chainsig = new TChain("MyTree");
  f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_SKHNee150_nocut_5_3_14.root");
  TFile * file = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_SKHNee150_nocut_5_3_14.root");
  cout << file << endl;
  float  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0.;
  float k_weight=0.;
  float k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  
  f_chain->SetBranchAddress("met", &k_met);
  f_chain->SetBranchAddress("ee_mass", &k_eemass);
  f_chain->SetBranchAddress("eejj_mass", &k_eejjmass);
  f_chain->SetBranchAddress("e1jj_mass", &k_e1jjmass);
  f_chain->SetBranchAddress("e2jj_mass", &k_e2jjmass);
  f_chain->SetBranchAddress("jj_mass", &k_jjmass);
  f_chain->SetBranchAddress("st", &k_st);
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
  

  std::vector<float> METcut;
  METcut.push_back(35.);
  
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
  float istmin_opt=0.;
  float istmax_opt=0.;
  float ijetpt_opt=0.;

  TH1* hnsig =   (TH1F*)file->Get(("eventcutflow"));

  float nsig = float(hnsig->GetBinContent(2));
  cout << "Number of signal events before any cut = " << nsig << endl; 

  for(unsigned int imet=0; imet < METcut.size(); imet++){
    float met_cut = METcut.at(imet);
    cout << "MET : "<< met_cut << endl;
    for(int imeejjmin= 12; imeejjmin < 16. ; imeejjmin++){
      float meejjmin_cut = float(imeejjmin) * 10.;
      for(int imeejjmax= 0; imeejjmax <1. ; imeejjmax++){
	float meejjmax_cut = 10000.;
	cout << meejjmin_cut <<   "  < M(eejj) < "<< meejjmax_cut << endl;
	for(int ipt1= 1; ipt1 < 6. ; ipt1++){
	  float pt1_cut =  20. + float(ipt1)*5.;
	  for(int ipt2= 1; ipt2 < 4. ; ipt2++){
	    float pt2_cut =  15. + float(ipt2)*5.;
	    if(pt2_cut > pt1_cut) continue;
	    cout << "pt1_cut = " << pt1_cut << " pt2_cut = " << pt2_cut << endl;
	    for(int ieemin =0 ; ieemin < 5 ; ieemin++){
	      float eemin_cut =  10. + float(ieemin)* 10.;
	      if(ieemin == 4) eemin_cut = 100.;
	      
	      for(int ieemax =0 ; ieemax <1 ; ieemax++){
		float eemax_cut =  1000000.;
		
		for(int ie2jjmin =0 ; ie2jjmin < 5 ; ie2jjmin++){
		  float e2jjmin_cut = 60. + float(ie2jjmin)* 20.;
		  
		  for(int ie2jjmax =0 ; ie2jjmax < 10 ; ie2jjmax++){
		    float e2jjmax_cut =  120. + float(ie2jjmax)* 10.;
		    if(ie2jjmax == 9) e2jjmax_cut = 10000.;
		    
		    for(int istmin =7 ; istmin < 13 ; istmin++){
		      float stmin_cut = float(istmin)*20.;  
		      for(int istmax =0 ; istmax < 1 ; istmax++){
			float stmax_cut = 10000.;
			
			for(int ijpt =0 ; ijpt < 3 ; ijpt++){
			  float jetpt_cut = 20. + float(ijpt)*5.;
			  /// Optmise cuts:
			  float cut_sum=0.;
			  float np_sum=0.;
			  for(Int_t i = 0; i < f_chain->GetEntries(); i++){
			    f_chain->GetEntry(i) ;
			    if(k_eemass > 80. && k_eemass < 100) continue;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    if(k_eemass < eemin_cut) continue;
			    if(k_eemass > eemax_cut) continue;
			    if(k_met > met_cut) continue;
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    if(k_st <  stmin_cut) continue;
			    if(k_st >  stmax_cut) continue;
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_el1pt < pt1_cut) continue;
			    if(k_el2pt < pt2_cut) continue;
			    cut_sum+=k_weight;
			    np_sum+=k_weight;
			  }
			  for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
			    f_chainmc->GetEntry(i) ;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    if(k_eemass > 80. && k_eemass < 100) continue;
			    if(k_eemass < eemin_cut) continue;
			    if(k_eemass > eemax_cut) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    if(k_met > met_cut) continue;
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    if(k_st <  stmin_cut) continue;
			    if(k_st >  stmax_cut) continue;
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_el1pt < pt1_cut) continue;
			    if(k_el2pt < pt2_cut) continue;
			    
			    cut_sum+=k_weight;
			  }
			  
			  float cut_sum_sig=0.;
			  for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
			    f_chainsig->GetEntry(i) ;
			    if(k_eemass > 80. && k_eemass < 100) continue;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    if(k_eemass < eemin_cut) continue;
			    if(k_eemass > eemax_cut) continue;
			    if(k_met > met_cut)continue;
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    if(k_st <  stmin_cut) continue;
			    if(k_st >  stmax_cut) continue;
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_el1pt < pt1_cut) continue;
			    if(k_el2pt < pt2_cut) continue;
			    cut_sum_sig+=k_weight;
			  }
			  
			  float sig_eff = cut_sum_sig /nsig ;
			  float total_bkg = cut_sum;
			  float bkgtmp = total_bkg + (0.28* np_sum)* (0.28* np_sum);
			  float denom = 1. + sqrt(bkgtmp);
			  float punzi = sig_eff / denom;
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
			    istmin_opt = stmin_cut;
			    istmax_opt = stmax_cut;
			    ijetpt_opt = jetpt_cut;
			    sig_eff_opt = sig_eff;
			    
			    sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
			    cut_sum_opt= cut_sum;
                            cout << "Max punzi = " << punzi << " : nbkg = " << total_bkg <<  " : %sig = " << sig_eff_opt_presel*100. << endl;
			    
			  }
			  
			}//jetpt
			
		      }//stmax
		    }//stmin
		  }//e2jjmax
		}//eemax
	      }//eemin
	    }//pt2
	  }//pt1
	}// meejjmax
      }/// meejjmin
    }/// MET 
  }
  //Opt cut
  cout << "Opt punzi = " << opt_cut_sb << endl;
  cout << "Opt cut : MET <  " << METcut.at(imet_opt) << endl;
  cout << "Opt cut : " << imeejjmin_opt << " < M(eejj) <  " << imeejjmax_opt << endl;
  cout << "Opt cut : " << ie2jjmin_opt << " < M(e2jj) <  " << ie2jjmax_opt << endl;
  cout << "Opt cut : " << ieemin_opt << " < M(ee) < " << ieemax_opt<< endl;
  cout << "Opt cut : " << istmin_opt << " < ST < " << istmax_opt<< endl;
  
  cout << "Opt pt1 = " << ipt1_opt << endl;
  cout << "Opt pt2 = " << ipt2_opt << endl;
  cout << "Opt jet1pt = " << ijetpt_opt << endl;
  cout << "Cut (opt) eff. bkg = " << cut_sum_opt/sum_event  <<  " nbkg = " << cut_sum_opt << endl;
  cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
  
  
}
