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
  
  fileData_ = TFile::Open( filename, "READ");
  if (!fileData_) cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";

  string analysisdir = getenv("FILEDIR");

  TString filenamedown = analysisdir + "MyDataPileupHistogram_65930.root";
  TString filenameup = analysisdir + "MyDataPileupHistogram_72870.root";
  fileDataUP_ = TFile::Open(filenameup , "READ");
  if (!fileData_) cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";
  fileDataDOWN_ = TFile::Open( filenamedown, "READ");
  if (!fileData_) cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";

  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  
  h_Data_ = 0;
  h_Data_ = dynamic_cast<TH1D*>((fileData_->Get("pileup"))->Clone());;  
  h_Data_up_ = dynamic_cast<TH1D*>((fileDataUP_->Get("pileup"))->Clone());;  
  h_Data_down_ = dynamic_cast<TH1D*>((fileDataDOWN_->Get("pileup"))->Clone());;  
  
  
  h_MCmod_ = dynamic_cast<TH1D*>((h_Data_->Clone("h_MCmod_")));
  
  // Now we can close the file:
  fileData_->Close();
  delete fileData_;
  fileDataUP_->Close();
  delete fileDataUP_;
  fileDataDOWN_->Close();
  delete fileDataDOWN_;
  // Return to the directory we were in before the function call: 
  origDir->cd();
  
  Double_t Summer2012_S10[60] = {
    2.560E-06,
    5.239E-06,
    1.420E-05,
    5.005E-05,
    1.001E-04,
    2.705E-04,
    1.999E-03,
    6.097E-03,
    1.046E-02,
    1.383E-02,
    1.685E-02,
    2.055E-02,
    2.572E-02,
    3.262E-02,
    4.121E-02,
    4.977E-02,
    5.539E-02,
    5.725E-02,
    5.607E-02,
    5.312E-02,
    5.008E-02,
    4.763E-02,
    4.558E-02,
    4.363E-02,
    4.159E-02,
    3.933E-02,
    3.681E-02,
    3.406E-02,
    3.116E-02,
    2.818E-02,
    2.519E-02,
    2.226E-02,
    1.946E-02,
    1.682E-02,
    1.437E-02,
    1.215E-02,
    1.016E-02,
    8.400E-03,
    6.873E-03,
    5.564E-03,
    4.457E-03,
    3.533E-03,
    2.772E-03,
    2.154E-03,
    1.656E-03,
    1.261E-03,
    9.513E-04,
    7.107E-04,
    5.259E-04,
    3.856E-04,
    2.801E-04,
    2.017E-04,
    1.439E-04,
    1.017E-04,
    7.126E-05,
    4.948E-05,
    3.405E-05,
    2.322E-05,
    1.570E-05,
    5.005E-06
  };

  for (Int_t i = 1; i < 61; i++) {
    h_MCmod_->SetBinContent(i, Summer2012_S10[i-1]);
  }
  
  double int_MC_ = h_MCmod_->Integral();
  double int_Data_ = h_Data_->Integral();
  double int_Dataup_ = h_Data_up_->Integral();
  double int_Datadown_ = h_Data_down_->Integral();
  
  h_Data_->Divide(h_MCmod_);
  h_Data_->Scale(int_MC_ / int_Data_);
  
  h_Data_up_->Divide(h_MCmod_);
  h_Data_up_->Scale(int_MC_ / int_Dataup_);
  
  h_Data_down_->Divide(h_MCmod_);
  h_Data_down_->Scale(int_MC_ / int_Datadown_);

}

Reweight::~Reweight(){
}

double Reweight::GetWeight(int nvtx, int sys){
  if(sys==1) return h_Data_up_->GetBinContent( nvtx + 1 );
  else if(sys==-1) return h_Data_down_->GetBinContent( nvtx + 1 );
  
  return h_Data_->GetBinContent( nvtx + 1 );
  
}

double Reweight::GetWeight(int nvtx){
  return GetWeight(nvtx,0);
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
