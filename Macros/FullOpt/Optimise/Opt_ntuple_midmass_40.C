#include "Riostream.h"
#include "TGraph.h"
#include <vector>


void Opt_ntuple_midmass_40(){

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetHistLineWidth(2);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1111);

  TChain * f_chain = new TChain("MyTree");
  f_chain->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKnonprompt_dilep_5_3_14.root");
  f_chain->LoadTree(0) ;
  
  TChain * f_chainmc = new TChain("MyTree");
  f_chainmc->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_mc_5_3_14.root");
  f_chainmc->LoadTree(0) ;

  TChain * f_chainsig = new TChain("MyTree");
  f_chainsig->Add("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee40_nocut_5_3_14.root");
  TFile * file = new TFile("/home/jalmond/Analysis/LQanalyzer/data/output/SSElectron_ntup/HNDiElectron_basic_SKHNee40_nocut_5_3_14.root");
  cout << file << endl;
  float  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_ht;
  float k_weight=0.;
  int k_njet;
  float k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0., k_el1eta=0., k_el2eta=0.;

  bool k_cl1bjet,k_cl2bjet,k_cll1bjet,k_cll2bjet;
  
  
  f_chain->SetBranchAddress("met", &k_met);
  f_chain->SetBranchAddress("ee_mass", &k_eemass);
  f_chain->SetBranchAddress("eejj_mass", &k_eejjmass);
  f_chain->SetBranchAddress("e1jj_mass", &k_e1jjmass);
  f_chain->SetBranchAddress("e2jj_mass", &k_e2jjmass);
  f_chain->SetBranchAddress("jj_mass", &k_jjmass);
  f_chain->SetBranchAddress("st", &k_st);
  f_chain->SetBranchAddress("ht", &k_ht);
  f_chain->SetBranchAddress("njet", &k_njet);
  f_chain->SetBranchAddress("el1_eta", &k_el1eta);
  f_chain->SetBranchAddress("el2_eta", &k_el2eta);
  f_chain->SetBranchAddress("el1_pt", &k_el1pt);
  f_chain->SetBranchAddress("el2_pt", &k_el2pt);
  f_chain->SetBranchAddress("jet1_pt", &k_j1pt);
  f_chain->SetBranchAddress("el1_clbjet", &k_cl1bjet);
  f_chain->SetBranchAddress("el2_clbjet", &k_cl2bjet);
  f_chain->SetBranchAddress("el1_cllbjet", &k_cll1bjet);
  f_chain->SetBranchAddress("el2_cllbjet", &k_cll2bjet);
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
  f_chainmc->SetBranchAddress("el1_eta", &k_el1eta);
  f_chainmc->SetBranchAddress("el2_eta", &k_el2eta);
  f_chainmc->SetBranchAddress("el1_pt", &k_el1pt);
  f_chainmc->SetBranchAddress("el2_pt", &k_el2pt);
  f_chainmc->SetBranchAddress("jet1_pt", &k_j1pt);
  f_chainmc->SetBranchAddress("weight", &k_weight);
  f_chainmc->SetBranchAddress("el1_clbjet", &k_cl1bjet);
  f_chainmc->SetBranchAddress("el2_clbjet", &k_cl2bjet);
  f_chainmc->SetBranchAddress("el1_cllbjet", &k_cll1bjet);
  f_chainmc->SetBranchAddress("el2_cllbjet", &k_cll2bjet);

  f_chainsig->SetBranchAddress("met", &k_met);
  f_chainsig->SetBranchAddress("ee_mass", &k_eemass);
  f_chainsig->SetBranchAddress("eejj_mass", &k_eejjmass);
  f_chainsig->SetBranchAddress("e1jj_mass", &k_e1jjmass);
  f_chainsig->SetBranchAddress("e2jj_mass", &k_e2jjmass);
  f_chainsig->SetBranchAddress("jj_mass", &k_jjmass);
  f_chainsig->SetBranchAddress("st", &k_st);
  f_chainsig->SetBranchAddress("ht", &k_ht);
  f_chainsig->SetBranchAddress("njet", &k_njet);
  f_chainsig->SetBranchAddress("el1_eta", &k_el1eta);
  f_chainsig->SetBranchAddress("el2_eta", &k_el2eta);
  f_chainsig->SetBranchAddress("el1_pt", &k_el1pt);
  f_chainsig->SetBranchAddress("el2_pt", &k_el2pt);
  f_chainsig->SetBranchAddress("el1_clbjet", &k_cl1bjet);
  f_chainsig->SetBranchAddress("el2_clbjet", &k_cl2bjet);
  f_chainsig->SetBranchAddress("el1_cllbjet", &k_cll1bjet);
  f_chainsig->SetBranchAddress("el2_cllbjet", &k_cll2bjet);
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
    if(k_eemass > 80. && k_eemass < 100) continue;
    if(k_jjmass > 120.) continue;

    if( (i % 100000) == 0) cout << "Sig: N processing = " << i << endl;
    sum_sigevent+=k_weight;
  }

  cout << "Total bkg = " << sum_event  << endl;
  cout << "Total sig = " <<  sum_sigevent << endl;
  

  std::vector<float> METcut;
  METcut.push_back(30.);
  
  int imet_opt=0;
  float imeejjmin_opt=0.;
  float imeejjmax_opt=0.;
  float ipt1_opt=0.;
  float ipt2_opt=0.;
  float ipt3_opt=0.;
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
  bool clbjet_opt=false;
  TH1* hnsig =   (TH1F*)file->Get(("eventcutflow"));

  float nsig = float(hnsig->GetBinContent(2));
  cout << "Number of signal events before any cut = " << nsig << endl; 

  for(unsigned int imet=0; imet < METcut.size(); imet++){
    float met_cut = METcut.at(imet);
    cout << "MET : "<< met_cut << endl;
    for(int imeejjmin= 0; imeejjmin < 1. ; imeejjmin++){
      float meejjmin_cut = 80 .+ float(imeejjmin) * 10.;
      for(int imeejjmax= 0; imeejjmax < 1. ; imeejjmax++){
	float meejjmax_cut = 200.+ float(imeejjmax)*5.;
	cout << meejjmin_cut <<   "  < M(eejj) < "<< meejjmax_cut << endl;
	for(int ipt1= 0; ipt1 <1. ; ipt1++){
	  float pt1_cut =  20. + float(ipt1)*5.;
	  for(int ipt2= 0; ipt2 < 1. ; ipt2++){

	    float pt2_cut =  15. + float(ipt2)*5.;
	    if(pt2_cut > pt1_cut) continue;
	    cout << "pt1_cut = " << pt1_cut << " pt2_cut = " << pt2_cut << endl;
	    
	    for(int ipt3= 0; ipt3 < 1. ; ipt3++){
	      float pt3_cut = 15. + float(ipt3)*5.;

	    for(int ieemin =0 ; ieemin < 1 ; ieemin++){
	      float eemin_cut =  10. + float(ieemin)* 5.;
	      if(ieemin == 5) eemin_cut = 100.;
	      
	      for(int ieemax =0 ; ieemax <1 ; ieemax++){
		float eemax_cut =  100000.;
		for(int ie1jjmin =0 ; ie1jjmin < 1 ; ie1jjmin++){
                  float e1jjmin_cut = 0. + float(ie1jjmin)* 10.;
		  
                  for(int ie1jjmax =0 ; ie1jjmax < 1 ; ie1jjmax++){
                    float e1jjmax_cut =  10000. + float(ie1jjmax)* 20.;
		    
		    for(int ie2jjmin =0 ; ie2jjmin < 1 ; ie2jjmin++){

		      float e2jjmin_cut = 0. + float(ie2jjmin)* 5.;
		      
		      for(int ie2jjmax =0 ; ie2jjmax < 1 ; ie2jjmax++){
			float e2jjmax_cut =  10000. + float(ie2jjmax)* 5.;
			if(ie2jjmax == 10) e2jjmax_cut = 10000.;
			
			cout << e2jjmin_cut << " < e2jjmin_cut < " << e2jjmax_cut  << endl;
			for(int ihtmin =0 ; ihtmin < 1 ; ihtmin++){
			  float htmin_cut = 0. + float(ihtmin)*5.;
			  for(int ihtmax =16 ; ihtmax < 17 ; ihtmax++){
			    float htmax_cut =100000. + float(ihtmax)*25.;
			    for(int istmin =0; istmin < 1 ; istmin++){
			      float stmin_cut = float(istmin)*10.;  
			      for(int istmax =0 ; istmax < 1 ; istmax++){
				float stmax_cut =100000. + float(istmax) *10.;
				
				for(int ijpt =0 ; ijpt <1 ; ijpt++){
				  float jetpt_cut = 20. + float(ijpt)*5.;
				  
				  for(int injet = 10 ; injet< 11 ; injet ++){
				    
				    for(int iclj = 0 ; iclj< 1 ; iclj ++){
				     

				      cout << "Check closebjet = " << iclj << endl; 
				      bool check_closebjet = false;
				      if(iclj == 1) check_closebjet= true;
				      /// Optmise cuts:
				      float cut_sum=0.;
				      float np_sum=0.;

				      /*
				      for(Int_t i = 0; i < f_chain->GetEntries(); i++){
					f_chain->GetEntry(i) ;
					if(k_eemass > 80. && k_eemass < 100) continue;
					if(k_jjmass > 120.) continue;
				      
					if(check_closebjet){
					  if(k_cl1bjet || k_cl2bjet) continue; 
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
					if(fabs(k_el2eta) < 1.5){
					  if(k_el2pt < pt2_cut) continue;
					}
					else{
					  if(k_el2pt < pt3_cut) continue;
					}
					if(k_njet> injet) continue;
					cut_sum+=k_weight;
					np_sum+=k_weight;
				      }
				      */
				      
				      for(Int_t i = 0; i < f_chainmc->GetEntries(); i++){
					f_chainmc->GetEntry(i) ;
					if(k_jjmass > 120.) continue;
					if(k_eemass > 80. && k_eemass < 100) continue;
					if(k_eemass < eemin_cut) continue;
					if(k_eemass > eemax_cut) continue;
					if(check_closebjet){
					  if(k_cl1bjet ||k_cl2bjet) continue;
					}
					if(k_e1jjmass < e1jjmin_cut) continue;
					if(k_e1jjmass > e1jjmax_cut) continue;
					if(k_e2jjmass < e2jjmin_cut) continue;
					if(k_e2jjmass > e2jjmax_cut) continue;
					if(k_met > met_cut) continue;
					if(k_eejjmass < meejjmin_cut) continue;
					if(k_eejjmass > meejjmax_cut) continue;
					if(k_st <  stmin_cut) continue;
					if(k_st >  stmax_cut) continue;
					if(k_ht <  htmin_cut) continue;
					if(k_ht >  htmax_cut) continue;
					if(k_j1pt < jetpt_cut) continue;
					if(k_el1pt < pt1_cut) continue;
					if(fabs(k_el2eta)< 1.5){
					  if(k_el2pt < pt2_cut) continue;
					} 
					else{
					  if(k_el2pt < pt3_cut) continue;
					}
					if(k_njet> injet) continue;
					cut_sum+=k_weight;
				      }
				      
				      float cut_sum_sig=0.;
				      for(Int_t i = 0; i < f_chainsig->GetEntries(); i++){
					f_chainsig->GetEntry(i) ;
					if(k_eemass > 80. && k_eemass < 100) continue;
					if(k_jjmass > 120.) continue;
					if(k_e1jjmass < e1jjmin_cut) continue;
					if(k_e1jjmass > e1jjmax_cut) continue;
					if(k_e2jjmass < e2jjmin_cut) continue;
					if(k_e2jjmass > e2jjmax_cut) continue;
					if(check_closebjet){
					  if(k_cl1bjet ||k_cl2bjet) continue;
					}
					if(k_eemass < eemin_cut) continue;
					if(k_eemass > eemax_cut) continue;
					if(k_met > met_cut)continue;
					if(k_eejjmass < meejjmin_cut) continue;
					if(k_eejjmass > meejjmax_cut) continue;
					if(k_st <  stmin_cut) continue;
					if(k_st >  stmax_cut) continue;
					if(k_ht <  htmin_cut) continue;
					if(k_ht >  htmax_cut) continue;
					if(k_j1pt < jetpt_cut) continue;
					if(fabs(k_el2eta)< 1.5){
					  if(k_el2pt < pt2_cut) continue;
					}
					else{
					  if(k_el2pt < pt3_cut) continue;
					}
					if(k_el1pt < pt1_cut) continue;
					if(k_njet> injet) continue;
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
					injet_opt = injet;
					imeejjmin_opt = meejjmin_cut;
					imeejjmax_opt = meejjmax_cut;
					ipt1_opt=  pt1_cut;
					ipt2_opt=  pt2_cut;
					ipt3_opt=  pt3_cut;
					ieemin_opt =  eemin_cut;
					ieemax_opt =  eemax_cut;
					ie1jjmin_opt = e1jjmin_cut;
					ie1jjmax_opt = e1jjmax_cut;
					ie2jjmin_opt = e2jjmin_cut;
					ie2jjmax_opt = e2jjmax_cut;
					istmin_opt = stmin_cut;
					istmax_opt = stmax_cut;
					ihtmin_opt = htmin_cut;
					ihtmax_opt = htmax_cut;
					ijetpt_opt = jetpt_cut;
					sig_eff_opt = sig_eff;
					clbjet_opt = check_closebjet;
					sig_eff_opt_presel = cut_sum_sig / sum_sigevent;
					cut_sum_opt= cut_sum;
					cout << "Max punzi = " << punzi << " : nbkg = " << total_bkg <<  " : %sig = " << sig_eff_opt_presel*100. << endl;
					
				      }
				    }
				    
				  }//jetpt
				}
			      }
			    }
			  }
			}
		      }//stmax
		    }//stmin
		  }//e2jjmax
		}//eemax
	      }//eemin
	    }//pt2
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
  cout << "Opt cut : " << ie1jjmin_opt << " < M(e1jj) <  " << ie1jjmax_opt << endl;
  cout << "Opt cut : " << ie2jjmin_opt << " < M(e2jj) <  " << ie2jjmax_opt << endl;
  cout << "Opt cut : " << ieemin_opt << " < M(ee) < " << ieemax_opt<< endl;
  cout << "Opt cut : " << istmin_opt << " < ST < " << istmax_opt<< endl;
  cout << "Opt cut : " << ihtmin_opt << " < HT < " << ihtmax_opt<< endl;
  cout << "clbjet_opt = " << clbjet_opt << endl;

  cout << "Opt pt1 = " << ipt1_opt << endl;
  cout << "Opt pt2 = " << ipt2_opt << endl;
  cout << "Opt pt2 (endcap) = " << ipt3_opt << endl;
  cout << "Opt jet1pt = " << ijetpt_opt << endl;
  cout << "Cut (opt) eff. bkg = " << cut_sum_opt/sum_event  <<  " nbkg = " << cut_sum_opt << endl;
  cout << "Cut eff .sig = " <<  sig_eff_opt << " : wrt preselection "<< sig_eff_opt_presel*100 <<  endl;
  
  
}
