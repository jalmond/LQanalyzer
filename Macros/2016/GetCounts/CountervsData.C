#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TTree.h"
#include "TMath.h"
#include "TKey.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"
#include "THStack.h"
#include "TLatex.h"


void CountervsData(TString path, TString pathNP, TString pathMC){
  TFile * fsig = new TFile(path);
  TFile * fNP = new TFile(pathNP);
  TFile * fMC = new TFile(pathMC);

  TH1* cut = (TH1*)fsig->Get("DiMuonll_lowmassopt_cutflow");
  TIter next(fsig->GetListOfKeys());
  TKey *key;
  
  while ((key = (TKey*)next())) {
    
    if(key->IsFolder()){
      TDirectory * d = (TDirectory*)(fsig->Get(key->GetName()));
      TIter nextDIR(d->GetListOfKeys());
      TKey *keyDIR;
      
      while ((keyDIR = (TKey*)nextDIR())) {
	TClass *cl = gROOT->GetClass(keyDIR->GetClassName());
	if (!cl->InheritsFrom("TH1D")) continue;
	TH1 *h = (TH1*)keyDIR->ReadObj();
	if (TString(keyDIR->GetName()).Contains("h_Nelectrons")){
	  if(!h->Integral()) continue;
	  string tmpname  = keyDIR->GetName();
	  TString ts_tmpname = TString(tmpname);
	  ts_tmpname=ts_tmpname.ReplaceAll("h_Nelectrons","");
	  double err(0.);
	  double integral = h->IntegralAndError(0, h->GetNbinsX()+1,err);

          string tmpname2  = key->GetName();

	  tmpname2=tmpname2+"/"+tmpname;
	  TH1* h2  = (TH1*)fNP->Get(tmpname2.c_str());
	  double  integral3(0.);
	  double err2(0.);
	  TH1* h3 =NULL;
	  if(pathMC.Contains("/data")){
	    h3 = (TH1*)fMC->Get(tmpname2.c_str());
	    integral3 = h3->IntegralAndError(0, h3->GetNbinsX()+1,err2);
	  }
	  double integral2 = h2->IntegralAndError(0, h2->GetNbinsX()+1,err2);

	  
	  double tot_bkg = integral2+integral3;
	  double fakeerr=integral2*0.3 + integral2*0.3;
	  float bkgtmp=fakeerr+tot_bkg;
	  if(bkgtmp>0){
	    float denom=1. + sqrt(bkgtmp);
	    if(denom>0){
	      float punzi=(integral/cut->GetBinContent(1)) / denom;
	      cout << ts_tmpname << "         =  " << integral/cut->GetBinContent(1) << " " << err  <<  " data = " <<  tot_bkg <<" punzi = " << punzi << " " <<  (integral/cut->GetBinContent(1)) / sqrt(tot_bkg) <<  " " << bkgtmp <<endl;
	    }
	  }
	  //if(h->Integral()> 0)cout <<  tmpname << " : " << h->Integral() << endl;
	}
      }
    }
  }
  

}
