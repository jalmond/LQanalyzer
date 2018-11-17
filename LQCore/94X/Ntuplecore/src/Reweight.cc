// LOCAL includes
#include "Reweight.h"

/// c++ std libraries
#include <sstream>
#include <iostream>
#include <stdio.h>

// ROOT include(s): 
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TH1F.h"

using namespace std;

Reweight::Reweight(TString filename){

  std::cout << "Initialising Reweight class " << std::endl;

  TDirectory* origDir = gDirectory;
  
  fileData_ = TFile::Open(filename, "READ");
  
  TString LQANALYZER_FILE_DIR = "/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2017/Pileup/";//getenv("LQANALYZER_FILE_DIR");                                                                         
  fileMC_   = new TFile(LQANALYZER_FILE_DIR +  "/MCPileUp2016Moriond.root", "READ");

  
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  
  h_Data_ = 0;
  
  h_Data_ = dynamic_cast<TH1D*>((fileData_->Get("Nvtx_nocut_data"))->Clone());;


  h_MCmod_ = (TH1D*)fileMC_->Get("Nvtx_nocut_mc");

  double int_MC_ = h_MCmod_->Integral();
  double int_Data_ = h_Data_->Integral();

  h_Data_->Divide(h_MCmod_);
  h_Data_->Scale(int_MC_ / int_Data_);

  
  fileData_->Close();
  delete fileData_;
  fileMC_->Close();
  delete fileMC_;


  origDir->cd();
  

}


Reweight::Reweight(std::vector< float > MC_distr, 
		   std::vector< float > Lumi_distr){
  
  std::cout << "Initialising Reweight class " << std::endl;

  Int_t NBins = MC_distr.size();
  
  TDirectory* origDir = gDirectory;
  
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  
  MC_distr_ = new TH1F("MC_distr","MC dist",NBins,0.0, float(NBins)) ;
  Data_distr_ = new TH1F("Data_distr","Data dist",NBins, 0.0, float(NBins)) ;
  weights_ =   new TH1F("luminumer","luminumer",NBins,0.0, float(NBins)) ;
  TH1* den = new TH1F("lumidenom","lumidenom",NBins,0.0, float(NBins)) ;
  for(int ibin = 1; ibin<NBins+1; ++ibin ) {
    weights_->SetBinContent(ibin, Lumi_distr[ibin-1]);
    Data_distr_->SetBinContent(ibin, Lumi_distr[ibin-1]);
    den->SetBinContent(ibin,MC_distr[ibin-1]);
    MC_distr_->SetBinContent(ibin,MC_distr[ibin-1]);
  }
  float deltaH = weights_->Integral();
  if(fabs(1.0 - deltaH) > 0.02 ) { //*OOPS*...
    weights_->Scale( 1.0/ weights_->Integral() );
    Data_distr_->Scale( 1.0/ Data_distr_->Integral() );
  }
  
  float deltaMC = den->Integral();
  if(fabs(1.0 - deltaMC) > 0.02 ) {
    den->Scale(1.0/ den->Integral());
    MC_distr_->Scale(1.0/ MC_distr_->Integral());
  }
  
  weights_->Divide( den );  // so now the average weight should be 1.0    
  
  
  
  origDir->cd();
}

Reweight::~Reweight(){
  delete h_MCmod_;
  delete h_Data_;

}


double Reweight::GetUserWeight(Int_t nvtx){
  return h_Data_->GetBinContent( h_Data_->FindBin(nvtx)  );


}

double Reweight::GetWeight(Int_t nvtx){

  int bin = weights_->GetXaxis()->FindBin( nvtx );
  return weights_->GetBinContent( bin );
  
}


TDirectory* Reweight::getTemporaryDirectory(void) const
{

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:                                                                                                                 
    std::stringstream dirname;
    dirname << "Reweight_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                                                                                                                          
    tempDir = gROOT->mkdir((dirname.str()).c_str());
    
  }
  
  return tempDir;
}
