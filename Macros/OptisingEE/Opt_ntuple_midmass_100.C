#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void Opt_ntuple_midmass_100(){

  // Initialise Fake file
  TChain * f_chain = new TChain("MyTree");
  f_chain->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKnonprompt_dilep_5_3_14.root");
  f_chain->LoadTree(0) ;
  
  // Initialise MC file
  TChain * f_chainmc = new TChain("MyTree");
  f_chainmc->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_mc_5_3_14.root");
  f_chainmc->LoadTree(0) ;

  // Initialise SIG file
  TChain * f_chainsig = new TChain("MyTree");
  f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee100_nocut_5_3_14.root");
  TFile * file = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee100_nocut_5_3_14.root");


  // set all opt/ variables to 0.
  float  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.;
  float k_weight=0.;
  float k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  
  /// Set branch address
  f_chain->SetBranchAddress("met", &k_met);
  f_chain->SetBranchAddress("ee_mass", &k_eemass);
  f_chain->SetBranchAddress("eejj_mass", &k_eejjmass);
  f_chain->SetBranchAddress("e1jj_mass", &k_e1jjmass);
  f_chain->SetBranchAddress("e2jj_mass", &k_e2jjmass);
  f_chain->SetBranchAddress("jj_mass", &k_jjmass);
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
  
  /// Optimise MET cut
  std::vector<float> METcut;
  //  METcut.push_back(30.);
  METcut.push_back(35.);
  //METcut.push_back(40.);
  
  /// List of optimiised variables
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
  float ijetpt_opt=0.;

  /// Get signal histogram for efficiency
  TH1* hnsig =   (TH1F*)file->Get(("eventcutflow"));
  float nsig = float(hnsig->GetBinContent(2));
  
  for(unsigned int imet=0; imet < METcut.size(); imet++){
    float met_cut = METcut.at(imet);
    cout << "MET : "<< met_cut << endl;
    
    /// Change imeejjmin < 10 to vary optimising limits
    for(int imeejjmin= 0; imeejjmin <12 ; imeejjmin++){
      float meejjmin_cut = 140. + float(imeejjmin) * 5.;
      
      for(int imeejjmax= 0; imeejjmax <1. ; imeejjmax++){
	float meejjmax_cut = 10000.+ float(imeejjmax)*5.;
	cout << meejjmin_cut <<   "  < M(eejj) < "<< meejjmax_cut << endl;
	
	for(int ipt1= 0; ipt1 <5. ; ipt1++){
	  float pt1_cut =  20. + float(ipt1)*5.;
	  
	  for(int ipt2= 0; ipt2 < 5. ; ipt2++){
	    float pt2_cut =  15. + float(ipt2)*5.;
	    if(pt2_cut > pt1_cut) continue;
	    
	    cout << "pt1_cut = " << pt1_cut << " pt2_cut = " << pt2_cut << endl;
	    
	    for(int ieemin =0 ; ieemin < 1; ieemin++){
	      float eemin_cut =  15. + float(ieemin)* 5.;
		
	      for(int ieemax =0 ; ieemax <1 ; ieemax++){
		float eemax_cut =  100000. + float(ieemax) * 20. ;
		
		cout << eemin_cut << " <  ee < " <<   eemax_cut << endl;
		
		// not used
		for(int ie1jjmin =0 ; ie1jjmin < 1 ; ie1jjmin++){
		  float e1jjmin_cut = 0. + float(ie1jjmin)* 10.;
		  
		  for(int ie1jjmax =0 ; ie1jjmax < 1 ; ie1jjmax++){
		    float e1jjmax_cut =  1000000. + float(ie1jjmax)* 20.;
		    
		    for(int ie2jjmin =0; ie2jjmin < 10 ; ie2jjmin++){
		      float e2jjmin_cut = 60. + float(ie2jjmin)* 5.;
		      
		      for(int ie2jjmax =1; ie2jjmax < 11 ; ie2jjmax++){
			float e2jjmax_cut =  120. + float(ie2jjmax)* 5.;
			if(ie2jjmax == 10) e2jjmax_cut = 10000.;
			
			for(int ijpt =0 ; ijpt <6 ; ijpt++){
			  float jetpt_cut = 20. + float(ijpt)*5.;
			  
			  /// Optmise cuts:
			  float cut_sum=0.;
			  float np_sum=0.;
			  int n_mc=0;
			  for(Int_t i = 0; i < f_chain->GetEntries(); i++){
			    f_chain->GetEntry(i) ;
			    if(k_eemass > 80. && k_eemass < 100) continue;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    if(k_nbjet_m !=0) continue;
			    if(check_closebjet){
			      if(k_cl1bjet ||k_cl2bjet) continue;
			    }
			    if(k_e1jjmass < e1jjmin_cut) continue;
			    if(k_e1jjmass > e1jjmax_cut) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    if(k_eemass < eemin_cut) continue;
			    if(k_eemass > eemax_cut) continue;
			    if(k_met > met_cut) continue;
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    if(k_st <  stmin_cut) continue;
			    if(k_st >  stmax_cut) continue;
			    if(k_ht <  htmin_cut) continue;
			    if(k_ht >  htmax_cut) continue;
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
			    
			    if(k_e1jjmass < e1jjmin_cut) continue;
			    if(k_e1jjmass > e1jjmax_cut) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    if(k_met > met_cut) continue;
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_el1pt < pt1_cut) continue;
			    if(k_el2pt < pt2_cut) continue;

			    n_mc += 1;
			    cut_sum+=k_weight;
			  }
				      
			  float cut_sum_sig=0.;
			  for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
			    f_chainsig->GetEntry(i) ;
			    if(k_eemass > 80. && k_eemass < 100) continue;
			    if(k_jjmass > 110.) continue;
			    if(k_jjmass < 50.) continue;
			    
			    if(k_e1jjmass < e1jjmin_cut) continue;
			    if(k_e1jjmass > e1jjmax_cut) continue;
			    if(k_e2jjmass < e2jjmin_cut) continue;
			    if(k_e2jjmass > e2jjmax_cut) continue;
			    
			    if(k_eemass < eemin_cut) continue;
			    if(k_eemass > eemax_cut) continue;
			    
			    if(k_met > met_cut)continue;
			    
			    
			    if(k_eejjmass < meejjmin_cut) continue;
			    if(k_eejjmass > meejjmax_cut) continue;
			    
			    if(k_j1pt < jetpt_cut) continue;
			    if(k_el1pt < pt1_cut) continue;
			    if(k_el2pt < pt2_cut) continue;
			    
			    cut_sum_sig+=k_weight;
			  }
			  
			  float sig_eff = cut_sum_sig /nsig ;
			  float total_bkg = cut_sum;
			  float bkgtmp = total_bkg + (0.4* np_sum)* (0.4* np_sum);
			  float denom = 1. + sqrt(bkgtmp);
			  float punzi = sig_eff / denom;
			  
			  cout << cut_sum_sig / sum_sigevent << endl;
				      
			  if( (punzi) > opt_cut_sb){
			    opt_cut_sb = punzi;
			    imet_opt = imet;
			    imeejjmin_opt = meejjmin_cut;
			    imeejjmax_opt = meejjmax_cut;
			    ipt1_opt=  pt1_cut;
			    ipt2_opt=  pt2_cut;
			    ieemin_opt =  eemin_cut;
			    ieemax_opt =  eemax_cut;
			    ie1jjmin_opt = e1jjmin_cut;
			    ie1jjmax_opt = e1jjmax_cut;
			    ie2jjmin_opt = e2jjmin_cut;
			    ie2jjmax_opt = e2jjmax_cut;
			    ijetpt_opt = jetpt_cut;
			    sig_eff_opt = sig_eff;
			    
			    sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
			    cut_sum_opt= cut_sum;
			    cout << "Max punzi = " << punzi << " : nbkg = " << total_bkg <<  " : %sig = " << sig_eff_opt_presel*100. << endl;
			    
			  }
			}
		      }
		    }
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
  cout << "Opt cut : njet <  " << injet_opt<< endl;
  cout << "Opt cut : " << imeejjmin_opt << " < M(eejj) <  " << imeejjmax_opt << endl;
  cout << "Opt cut : " << ie2jjmin_opt << " < M(e2jj) <  " << ie2jjmax_opt << endl;
  cout << "Opt cut : " << ieemin_opt << " < M(ee) < " << ieemax_opt<< endl;
  
  cout << "Number of mc = " << n_mc << endl;

  cout << "Opt pt1 = " << ipt1_opt << endl;
  cout << "Opt pt2 = " << ipt2_opt << endl;

  cout << "Opt jet1pt = " << ijetpt_opt << endl;
  cout << "Cut (opt) eff. bkg = " << cut_sum_opt/sum_event  <<  " nbkg = " << cut_sum_opt << endl;
  cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
  
  
}
