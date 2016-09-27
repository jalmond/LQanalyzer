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
  fileMC_   = new TFile("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/MCPileUp2016.root", "READ");


  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  
  h_Data_ = 0;
  h_Data_ = dynamic_cast<TH1F*>((fileData_->Get("h_VertexNoReweight"))->Clone());;  
  
  h_MCmod_ = (TH1F*)fileMC_->Get("h_VertexNoReweight");
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

Reweight::~Reweight(){
  delete h_MCmod_;
  delete h_Data_;

}


double Reweight::GetWeight(Int_t nvtx){

  return h_Data_->GetBinContent( h_Data_->FindBin(nvtx)  );
  
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
