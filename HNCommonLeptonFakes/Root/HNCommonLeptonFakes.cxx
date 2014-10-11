// STL include(s):                                                                                                                                                       
#include <stdexcept>
#include <sstream>
#include <iostream>


// ROOT include(s):                                                                                                                                                                
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TDirectory.h"
#include "TLorentzVector.h"
#include "TH2F.h"
#include "TEfficiency.h"

/// local includes
#include "HNCommonLeptonFakes/HNCommonLeptonFakes.h"

using namespace std;


TDirectory* HNCommonLeptonFakes::getTemporaryDirectory(void) const
{
  //                                                                                                                                                                                
  // Create a unique directory in memory to hold the histograms:                                                                                                                      //                                                                                                                                                                                 
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;
}


void HNCommonLeptonFakes::InitialiseFake(){
  
  bool failedinitialisation=false;

  cout << "HNCommonLeptonFakes : Initializing" << endl;

  // Remember which TDirectory the system is in at the beginning of the method:                                                                                                      
  TDirectory* origDir = gDirectory;
  
  /// List files with fake rates

  string lqdir = getenv("LQANALYZER_DIR");
  TFile* file_fake_Opt  = TFile::Open( (lqdir + "/data/rootfiles/FakeRateOpt.root").c_str());
  CheckFile(file_fake_Opt);
  TFile* file_fake  = TFile::Open( (lqdir + "/data/rootfiles/FakeRate2807.root").c_str());
  CheckFile(file_fake);

  TFile* file_mc  = TFile::Open( (lqdir + "/data/rootfiles/FakeRate_0110.root").c_str());
  CheckFile(file_mc);
  
  TFile* file_fake_Opt2  = TFile::Open( (lqdir + "/data/rootfiles/FakeRate0309.root").c_str());
  CheckFile(file_fake_Opt2);

  TFile* file_fake_data  = TFile::Open( (lqdir + "/data/rootfiles/FakeRate_dataoct.root").c_str());
  CheckFile(file_fake_data);

  TFile* file_fake_med  = TFile::Open( (lqdir + "/data/rootfiles/FakeRateMedium.root").c_str());
  CheckFile(file_fake_med);

  TFile* file_fake_dxy =  TFile::Open( (lqdir + "/data/rootfiles/FakeRatedxy.root").c_str());
  CheckFile(file_fake_dxy);

  TFile* file_muon = TFile::Open( (lqdir + "/data/rootfiles/Total_FRcorr40_130.root").c_str());
  CheckFile(file_muon);

  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();

    

  /*  
  _2DEfficiencyMap["fake_eff_dxy05"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy05_El40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_dxy10"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy10_El40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_dxy15"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy15_El40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_dxy20"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy20_El40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_dxy25"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy25_El40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_dxy30"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_dxy30_El40_pt_eta"))->Clone());
  
  _2DEfficiencyMap["fake_eff_medium"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_medium_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_tight"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_tight_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b100_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b090_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b090_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b090_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b090_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_iso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_dr3_b090_e050_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_Loosedxy01_NPFiso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_NPFisodr3_b090_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_NPFiso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_NPFisodr3_b090_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_NPFiso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_NPFisodr3_b090_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_Loosedxy01_NPFiso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Loosedxy01_Tight_iso_NPFisodr3_b090_e050_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_iso_b050_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b150_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e125_pt_eta"))->Clone());

  
  _2DEfficiencyMap["fake_eff_iso_b150_e150"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e150_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b060_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b060_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e050_pt_eta"))->Clone());

  
  _2DEfficiencyMap["fake_eff_iso_b150_e150"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b150_e150_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b125_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b125_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b100_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b090_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b080_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b080_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b070_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b070_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b060_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b060_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_iso_b050_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_dr3_b050_e050_pt_eta"))->Clone());
  

  _2DEfficiencyMap["fake_eff_NPFiso_b050_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b050_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b050_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b050_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b050_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b050_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b050_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b070_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b070_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b080_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b080_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b090_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b090_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b100_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b100_e125_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b125_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b125_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e050_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e060_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e070_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e080_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e090_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e100_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_NPFiso_b150_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate_Tight_iso_NPFisodr3_b150_e125_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_close_40" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__close_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_40" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_bjet_40" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_bjet_40_pt_eta"))->Clone());
  
  _2DEfficiencyMap["fake_eff_close_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__close_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_bjet_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_bjet_20_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_noclose_ht1_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_ht1_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_ht2_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_ht2_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_noclose_ht3_20" ] = dynamic_cast<TH2F*>((file_fake_Opt->Get("FakeRate__noclose_ht3_20_pt_eta"))->Clone());
  

  _2DEfficiencyMap["fake_eff_20" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40old" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_susy" ] = dynamic_cast<TH2F*>((file_fake_med->Get("FakeRate_40_medium_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_60" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_60_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_30_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_20_loosereg2" ] = dynamic_cast<TH2F*>((file_fake_dxy->Get("FakeRate_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_loosereg2" ] = dynamic_cast<TH2F*>((file_fake_dxy->Get("FakeRate_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_60_loosereg2" ] = dynamic_cast<TH2F*>((file_fake_dxy->Get("FakeRate_60_pt_eta"))->Clone());


  _2DEfficiencyMap["fake_eff_20_nobjet" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_20_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_nobjet" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_40_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_60_nobjet" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_60_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30_nobjet" ] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_30_0bjet_pt_eta"))->Clone());
  */
  cout << "Pt/eta depenance " << endl;
  /// pt vs eta 
  
  std::vector<TString> jetcut;
  jetcut.push_back("20");
  jetcut.push_back("30");
  jetcut.push_back("40");
  jetcut.push_back("60");
  for(unsigned int ij = 0 ; ij < jetcut.size() ; ij++){
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_pt_eta"))->Clone());
    /// add bjet dep
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"b_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_bjet_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"b_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_bjet_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"nob_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_0bjet_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"nob_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_0bjet_pt_eta_nocb"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"b_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_bjet_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"b_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_bjet_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"nob_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_0bjet_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"nob_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_0bjet_pt_eta"))->Clone());

    
    cout << "Ht depenance and Pt " << endl;
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht1_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht2_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht3_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht3_pt_eta_nocb"))->Clone());
    
    cout << "Ht depenance and Pt: bjet " << endl;
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht1_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_0bjet_ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht2_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_0bjet_ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht3_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_0bjet_ht3_pt_eta_nocb"))->Clone());
    
    cout << "Ht depenance and Pt: bjet " << endl;
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht1_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_bjet_ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht2_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_bjet_ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht3_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_bjet_ht3_pt_eta_nocb"))->Clone());
    cout << "Ht depenance and Pt " << endl;
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht1_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht2_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht3_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht3_pt_eta_nocb"))->Clone());

    cout << "Ht depenance and Pt: bjet " << endl;
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht1_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_0bjet_ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht2_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_0bjet_ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_0bjet_ht3_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_0bjet_ht3_pt_eta_nocb"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht1_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_bjet_ht1_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht2_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_bjet_ht2_pt_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_bjet_ht3_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_bjet_ht3_pt_eta_nocb"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht1_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht1_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht2_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht2_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht3_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"ht3_pt_eta"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht1_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht1_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht2_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht2_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht3_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"ht3_pt_eta"))->Clone());
    
    
    cout << "Ht depenance: close bjet " << endl;
    
    /// ht dependance
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_cb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_ht_eta_cb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_nocb_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_ht_eta_nocb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_cb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_ht_eta_cb"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_nocb_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_ht_eta_nocb"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_"+ jetcut.at(ij)+"_ht_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_ht_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_relaxed_ipcut"+ jetcut.at(ij)+"_ht_eta"))->Clone());
    cout << "Pt depenance: close bjet " << endl;
    // pt dependance
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_cb_pt_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_closebjet_"+ jetcut.at(ij)+"_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_nocb_pt_loosereg1"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_noclosebjet_"+ jetcut.at(ij)+"_pt_eta"))->Clone());

    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_cb_pt_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_closebjet_relaxed_ipcut"+ jetcut.at(ij)+"_pt_eta"))->Clone());
    _2DEfficiencyMap["fake_eff_mc_"+ jetcut.at(ij)+"_nocb_pt_loosereg2"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_noclosebjet_relaxed_ipcut"+ jetcut.at(ij)+"_pt_eta"))->Clone());
  }  
  
  _2DEfficiencyMap["fake_eff_muon"] = dynamic_cast<TH2F*>((file_muon->Get("h_FOrate3"))->Clone());
 
  _2DEfficiencyMap["fake_eff_100_100_detiso"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_100_detiso"))->Clone());
  _2DEfficiencyMap["fake_eff_090_090_detiso"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_090_detiso"))->Clone());
  _2DEfficiencyMap["fake_eff_090_050_detiso"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_b090_e050_detiso"))->Clone());
  _2DEfficiencyMap["fake_eff_100_100"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_b100_e100"))->Clone());
  _2DEfficiencyMap["fake_eff_090_090"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_b090_e090"))->Clone());
  _2DEfficiencyMap["fake_eff_090_050"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_b090_e050"))->Clone());
  
  _2DEfficiencyMap["fake_eff_medium"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_medium"))->Clone());
  _2DEfficiencyMap["fake_eff_tight"] = dynamic_cast<TH2F*>((file_fake_Opt2->Get("FakeRate_tight"))->Clone());

  std::vector <TString> datajetcut;
  datajetcut.push_back("20");
  datajetcut.push_back("30");
  datajetcut.push_back("40");
  datajetcut.push_back("60");

  std::vector <TString> region;
  region.push_back("looseregion1");
  region.push_back("looseregion2");

  std::vector <TString> cut;
  cut.push_back("pt_eta");
  cut.push_back("ht_eta");
  cut.push_back("bjet_pt_eta");
  cut.push_back("0bjet_pt_eta");
  cut.push_back("ht_eta_cb");
  cut.push_back("pt_eta_cb");
  cut.push_back("ht_eta_nocb");
  cut.push_back("pt_eta_nocb");
  cut.push_back("pt_eta_ht1_nocb");
  cut.push_back("pt_eta_ht3_nocb");
  //cut.push_back("pt_eta_ht1");
  //cut.push_back("pt_eta_ht3");
  cut.push_back("bjet_pt_eta_ht1_nocb");
  cut.push_back("bjet_pt_eta_ht3_nocb");
  cut.push_back("0bjet_pt_eta_ht1_nocb");
  cut.push_back("0bjet_pt_eta_ht3_nocb");
  cut.push_back("bjet_pt_eta_nocb");
  cut.push_back("0bjet_pt_eta_nocb");
  
  for(unsigned int fi = 0; fi < region.size() ; fi++){
    for(unsigned int fj = 0; fj < datajetcut.size() ; fj++){
      for(unsigned int fk = 0; fk < cut.size() ; fk++){
	if( region.at(fi).Contains("2"))
	  _2DEfficiencyMap["fake_eff_" + cut.at(fk) +"_" + datajetcut.at(fj) +"_" + region.at(fi)] = dynamic_cast<TH2F*>((file_fake_data->Get("FakeRate_HNTight_relaxedip" + datajetcut.at(fj) + "_" + cut.at(fk))));
	else
	  _2DEfficiencyMap["fake_eff_" + cut.at(fk) +"_" + datajetcut.at(fj) +"_" + region.at(fi)] = dynamic_cast<TH2F*>((file_fake_data->Get("FakeRate_HNTight_" + datajetcut.at(fj) + "_" + cut.at(fk))));
      }
    }
  }

  std::vector <TString> cut2;
  cut2.push_back("40_pt_eta");

  

  std::vector <TString> region2;
  for(unsigned int fi = 0; fi < region2.size() ; fi++){
    for(unsigned int fk = 0; fk < cut2.size() ; fk++){
      
    }
  }


  cout << "HNCommonLeptonFakes : Initializing" << endl;
  for(map<TString, TH2F*>::iterator mit = _2DEfficiencyMap.begin(); mit != _2DEfficiencyMap.end(); mit++){
    if(!mit->second){
      cout << "Failed " << mit->first << endl;
      failedinitialisation=true;
    }
  }

  if(failedinitialisation){
    cout << "Not all histograms could be initialised, this is a bug so am exiting" << endl;
  }
  else {

    cout << "WRHNCommonLeptonFakes : Initialsation was successful " << endl;
    cout << "WRHNCommonLeptonFakes : Default setting in MeV" <<  endl;
    cout << "WRHNCommonLeptonFakes : To Use GeV set third argument of constructor true" << endl;
  }
  file_fake_Opt->Close();
  delete file_fake_Opt;
  
  file_fake_data->Close();
  delete file_fake_data;

  file_fake_dxy->Close();
  delete file_fake_dxy;
  file_fake->Close();
  delete file_fake;
  
  file_mc->Close();
  delete file_mc;

  file_fake_med->Close();
  delete file_fake_med;

  // Now we can close the file:   
  origDir->cd();
  

  return;
}


/// Constructor
HNCommonLeptonFakes::HNCommonLeptonFakes(std::string path,bool usegev){

  path_to_root_files = path;
  useGeV = usegev;
  InitialiseFake();
  m_debug=false;
  NullTotals();
}


/// Destructor
HNCommonLeptonFakes::~HNCommonLeptonFakes() {
  closefile();   
  CutHists.clear();
}



void HNCommonLeptonFakes::ApplyFakeSystematic(int type){
 
  //  if(type==0)cout << "HNCommonLeptonFakes : Running in default mode f [no systematic applied] " << endl;
  //  if(type==1)cout << "HNCommonLeptonFakes : Applying systematic f + sigma" << endl;
  //  if(type==-1)cout << "HNCommonLeptonFakes : Applying systematic f - sigma" << endl;
  
  fsys=type;
}

void HNCommonLeptonFakes::ApplyRealSystematic(int type ){
  
  //if(type==0)cout << "HNCommonLeptonFakes : Running in default mode r [no systematic applied] " << endl;
  //if(type==1)cout << "HNCommonLeptonFakes : Applying systematic r + sigma " << endl;
  //if(type==-1)cout << "HNCommonLeptonFakes : Applying systematic r - sigma " << endl;
  
  rsys=type;
}



float HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons,  bool isel1tight, bool isel2tight, TString cut, int eventtype){
  return get_dilepton_ee_eventweight( electrons, 0., isel1tight, isel2tight, cut, eventtype);
}
    

float HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, float ht,  bool isel1tight, bool isel2tight, TString cut, int eventtype){

  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();

  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;


  float _el1_eta=fabs(electrons.at(0).Eta());
  float _el2_eta=fabs(electrons.at(1).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }

  if(cut.Contains("mc")){
    if(_el1_pt > 60.) _el1_pt = 59.;
    if(_el2_pt > 60.) _el2_pt = 59.;
  }
  else{
    if(_el1_pt > 100.) _el1_pt = 99.;
    if(_el2_pt > 100.) _el2_pt = 99.;
  }
  float fr1(0.),fr2(0.),r1(0.),r2(0.);
  
  r1=1.;
  r2=1.;
  

  TString fcut = cut;
  TString cut1 = fcut;
  TString cut2 = fcut;
  if(cut.Contains("mc")){
    if(fcut.Contains("mc") && fcut.Contains("_ht_") ){
      _el1_pt = ht;
      _el2_pt = ht;
    }
    
    if(fcut.Contains("mc") && fcut.Contains("HT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      _el1_pt = ht;
      _el2_pt = ht;
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")) cut1 = "mc_" + jetcut +"_cb_" + region;
      else cut1 = "mc_" + jetcut+  "_nocb_" + region;
      if(cut2.Contains("cl2")) cut2 = "mc_" + jetcut +"_cb_" + region;
      else cut2 = "mc_" + jetcut+  "_nocb_" + region;
    }
    if(fcut.Contains("mc") && fcut.Contains("PT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")){
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else cut1 = "mc_" + jetcut+  "_nocb_pt_" + region;
      if(cut2.Contains("cl2")) {
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else cut2 = "mc_" + jetcut+  "_nocb_pt_" + region;
    }
    
    if(fcut.Contains("mc") && fcut.Contains("BT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")){
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else {
	if(cut1.Contains("nob")) cut1 = "mc_" + jetcut+  "nob_nocb_" + region;
	else cut1 = "mc_" + jetcut+  "b_nocb_" + region;
      }
      if(cut2.Contains("cl2")) {
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else{
	if(cut2.Contains("nob")) cut2 = "mc_" + jetcut+  "nob_nocb_" + region;
	else cut2 = "mc_" + jetcut+  "b_nocb_" + region;
      }  
    }
    
    
    if(fcut.Contains("mc") && fcut.Contains("ST") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")) {
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else {
	
	TString bjet = "";
	if(cut1.Contains("0bjet" )) bjet = "_0bjet"; 
	else if(cut1.Contains("bjet" )) bjet = "_bjet"; 
	if(ht < 100.) cut1 = "mc_" + jetcut+ bjet + "_ht1_nocb_" + region;
	else  cut1 = "mc_" + jetcut+  bjet + "_ht3_nocb_" + region;
	
      }
      if(cut2.Contains("cl2")){
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else {
	TString bjet = "";
	if(cut2.Contains("0bjet" )) bjet = "_0bjet";
	else if(cut2.Contains("bjet" )) bjet = "_bjet";
	if(ht < 100.) cut2 = "mc_" + jetcut+ bjet + "_ht1_nocb_" + region;
	else  cut2 = "mc_" + jetcut+  bjet + "_ht3_nocb_" + region;
	
      }
    }
  }
  
  else{
    /// DATA FAKE RATES

    if(fcut.Contains("method1")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      cut1  = "pt_eta_" + JetPt + "_" + reg;
      cut2  = "pt_eta_" + JetPt + "_" + reg;
    }
    else     if(fcut.Contains("method2")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      _el1_pt = ht;
      _el2_pt = ht;
      cut1  = "ht_eta_"+ JetPt+ "_" +reg;
      cut2  = "ht_eta_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method3")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";

      
      cut1  = bjet+ "_pt_eta_"+ JetPt+ "_" +reg;
      cut2  = bjet+ "_pt_eta_"+ JetPt+ "_" +reg;
    }
    
    else     if(fcut.Contains("method4")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      if(fcut.Contains("cl1")) {
	cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut1  = "pt_eta_nocb_"+ JetPt+ "_" +reg;
      
      if(fcut.Contains("cl2")) {
	cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = "pt_eta_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method5")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      _el1_pt = ht;
      _el2_pt = ht;

      if(fcut.Contains("cl1")) {
	cut1  = "ht_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut1  = "ht_eta_nocb_"+ JetPt+ "_" +reg;
      
      if(fcut.Contains("cl2")) {
        cut2  = "ht_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = "ht_eta_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method6")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
	cut1  = bjet+ "_pt_eta_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = bjet + "_ht_eta_nocb_"+ JetPt+ "_" +reg;
    }
    
    else     if(fcut.Contains("method7")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 100) htbin = "ht3";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
        cut1  = "pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  =  "pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method8")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 100) htbin = "ht3";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
        cut1  = bjet + "_pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = bjet + "_pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method9")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 100) htbin = "ht3";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      
      cut1  = "pt_eta_" + htbin + JetPt+ "_" +reg;
      cut2  = "pt_eta_" + htbin + JetPt+ "_" +reg;
    }
  }
  
    
  fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut1);
  fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut2);
  
  //if(!isel1tight) cout << "fr1 = " << fr1 << " " << cut1<< " " << _el1_pt << " " << _el1_eta << endl;
  //if(!isel2tight) cout << "fr2 = " << fr2 << " " <<  cut2 << " " << _el2_pt << " " << _el2_eta << endl;
  
  
  if(fr1 == 0.)  fr1 = 0.05;
  if(fr2 == 0.)  fr2 = 0.05;
  
  if(_el1_pt < 20.){
    if(fabs(_el1_eta) > 1.5){
      if(cut1.Contains("fake_eff_mc_60_bjet_ht3_loosereg1")) cout << "mod: fake_eff_mc_60_bjet_ht3_loosereg1 : fr = " << fr1 << endl;
    }
  }


  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight, eventtype);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }

  
  return ev_weight;
  }

  
float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, bool isel1tight, bool isel2tight, TString cut, int eventtype, bool user1){

  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();

  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;


  float _el1_eta=fabs(electrons.at(0).Eta());
  float _el2_eta=fabs(electrons.at(1).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }

  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_el2_pt > 100.) _el2_pt = 99.;

  float fr1(0.),fr2(0.),r1(0.),r2(0.);

  if(!user1){
    r1 = getEfficiency_electron(0,_el1_pt, _el1_eta, cut);
    r2 = getEfficiency_electron(0,_el2_pt, _el2_eta,cut);
  }
  else{
    r1=1.;
    r2=1.;
  }
  fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut);
  fr2= getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut);

  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight, eventtype);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;
}



float  HNCommonLeptonFakes::get_dilepton_em_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electrons, bool ismu1tight, bool isel1tight){

  if(muons.size()!=1) {
    return (0.);
  }
  if(electrons.size()!=1) {
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _mu1_pt=muons.at(0).Pt();


  float _el1_eta=electrons.at(0).Eta();
  float _mu1_eta=muons.at(0).Eta();

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "mu1 pT = " << _mu1_pt << endl;
  }

  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_mu1_pt > 60.) _mu1_pt = 59.;


  float fr1(0.),fr2(0.),r1(0.),r2(0.);

  r1 = 1.;
  r2 = 1.;

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta);
  fr2= getFakeRate_electron(0,_el1_pt, _el1_eta);


  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, ismu1tight);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;

}

float  HNCommonLeptonFakes::get_dilepton_mm_eventweight( std::vector<TLorentzVector> muons,bool ismu1tight, bool ismu2tight){
  
  if(muons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }
  
  float _mu1_pt=muons.at(0).Pt();
  float _mu1_eta=muons.at(0).Eta();
  float _mu2_pt=muons.at(1).Pt();
  float _mu2_eta=muons.at(1).Eta();

  
  float fr1(0.),fr2(0.),r1(0.),r2(0.);  
  /// Get real efficiencies (pt max 200 set in function) uses tight zwindow: rsys sets systematic (0/1/-1)
  
  r1 = getEfficiency_muon(0,_mu1_pt, _mu1_eta);
  r2 = getEfficiency_muon(0,_mu2_pt, _mu2_eta);

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta);
  fr2= getFakeRate_muon(0,_mu2_pt, _mu2_eta);
  
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismu1tight, ismu2tight);

  return ev_weight;

}


float HNCommonLeptonFakes::getEfficiency_electron(int sys, float pt, float eta, TString cut){
  
  float eff_real(1.);
  
  map<TString,TH2F*>::const_iterator mapit;
  
  TString hist = "real_eff_";
  hist += cut; 

  mapit = _2DEfficiencyMap.find(hist.Data());
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,eta);
    eff_real =  mapit->second->GetBinContent(binx);
  }
  else NoHist( hist.Data());

  if(eff_real==0.) eff_real=1.;
  return eff_real;
  
}




 float HNCommonLeptonFakes::getEfficiency_electron(int sys, float pt, float eta){

  float eff_real(1.);

  /// Will update with eta dependance 
  if(pt< 25.) eff_real = 0.88;
  else if(pt< 30.) eff_real = 0.91;
  else if(pt< 40.) eff_real = 0.93;
  else if(pt< 50.) eff_real = 0.94;
  else  eff_real = 0.99;

  
  
  if(sys ==1) eff_real= 1.;
  if(sys ==-1) eff_real*=0.9;
  
  return eff_real;
}
 
 
 
float HNCommonLeptonFakes::getEfficiency_muon(int sys, float pt, float eta){
   
   float eff_real(1.);

  if(sys ==1) eff_real= 1.;
  if(sys ==-1) eff_real=0.9;
  
  //// NO PROMPT EFFICIENCIES MEASURED FOR MUONS 
     
  return eff_real;
}



float HNCommonLeptonFakes::getFakeRate_electron(int sys,float pt, float ht, TString cut){
   
   float eff_fake(0.);

   if(ht < 20.) ht = 21.;
   if(pt < 10) return -999999.;
  
   map<TString,TH2F*>::const_iterator mapit;
   
   TString hist = "fake_eff_ht_";
   hist += cut;

   mapit = _2DEfficiencyMap.find(hist.Data());

  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,ht);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((hist.Data()));
 

  return eff_fake;
}

float HNCommonLeptonFakes::getFakeRate_electronEta(int sys,float pt, float eta, TString cut){

  float eff_fake(0.);

  if(fabs(eta) > 2.5) return -999999.;
  if(pt < 15) return -999999.;

  map<TString,TH2F*>::const_iterator mapit;

  TString hist = "fake_eff_";
  hist += cut;
  
  mapit = _2DEfficiencyMap.find(hist.Data());
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,eta);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((hist.Data()));
  
  
  return eff_fake;
}




float HNCommonLeptonFakes::getFakeRate_electron(int sys,float pt, float eta ){
  float eff_fake=0.;

  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 10) return -999999.;
  

  if(pt< 20.) eff_fake=0.180564;
  else if(pt< 25) eff_fake=0.161576;
  else if(pt< 30.) eff_fake=0.141819;
  else if(pt< 35.) eff_fake=0.14412;
  else if(pt< 40.) eff_fake=0.143885;
  else if(pt< 60.) eff_fake=0.153494;
  else  eff_fake=0.125989;
  
  return eff_fake;
}

float HNCommonLeptonFakes::getFakeRate_muon(int sys,float pt, float eta ){
  
  float eff_fake=0.;
  
  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 15) return -999999.;
  
  if(fabs(eta) < 0.8){
    if((pt < 20.))  eff_fake=0.052;
    else if(pt < 25) eff_fake= 0.050;
    else if(pt < 30) eff_fake= 0.044;
    else if(pt < 35) eff_fake= 0.044;
    else if(pt < 45) eff_fake= 0.067;
    else eff_fake= 0.076;
  }
  else if(fabs(eta) < 1.479){
    if((pt < 20.))  eff_fake=0.060;
    else if(pt < 25) eff_fake= 0.050;
    else if(pt < 30) eff_fake= 0.051;
    else if(pt < 35) eff_fake= 0.066;
    else if(pt < 45) eff_fake= 0.070;
    else eff_fake= 0.058;
  }
  else if(fabs(eta) < 2.){
    if((pt < 20.))  eff_fake=0.080;
    else if(pt < 25) eff_fake= 0.079;
    else if(pt < 30) eff_fake= 0.071;
    else if(pt < 35) eff_fake= 0.068;
    else if(pt < 45) eff_fake= 0.106;
    else eff_fake= 0.027;
  }
  else if(fabs(eta) < 2.5){
    if((pt < 20.))  eff_fake=0.089;
    else if(pt < 25) eff_fake= 0.070;
    else if(pt < 30) eff_fake= 0.091;
    else if(pt < 35) eff_fake= 0.080;
    else if(pt < 45) eff_fake= 0.077;
    else eff_fake= 0.231;
  }
  
  float up_down=1.;
  if(sys == -1) up_down = 1.;
  
  if(sys !=0) {
    float err=0.;
    if(fabs(eta) < 0.8){
      if((pt < 20.))  err=0.007;
      else if(pt < 25) err= 0.004;
      else if(pt < 30) err= 0.004;
      else if(pt < 35) err= 0.004;
      else if(pt < 45) err= 0.011;
      else err= 0.032;
    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  err=0.008;
      else if(pt < 25) err= 0.005;
      else if(pt < 30) err= 0.004;
      else if(pt < 35) err= 0.008;
      else if(pt < 45) err= 0.013;
      else err= 0.039;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  err=0.011;
      else if(pt < 25) err= 0.007;
      else if(pt < 30) err= 0.006;
      else if(pt < 35) err= 0.010;
      else if(pt < 45) err= 0.019;
      else err= 0.039;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  err=0.0047;
      else if(pt < 25) err= 0.012;
      else if(pt < 30) err= 0.013;
      else if(pt < 35) err= 0.019;
      else if(pt < 45) err= 0.031;
      else err= 0.117;
    }
  
    eff_fake = eff_fake + (up_down*err);
  }
  
  
  return eff_fake;
}




void HNCommonLeptonFakes::NoHist(TString hist, TString function){
  
  cout << function << ": No Histogram found for string " << hist << endl;

  cout << "Possible _EfficiencyMap hists are : " << endl;
  for(map<TString, TH1*>::iterator mit = _EfficiencyMap.begin(); mit != _EfficiencyMap.end(); mit++){
    cout << mit->first << endl;  
  }
  

  cout << "Possible _2DEfficiencyMap hists are : " << endl;
  for(map<TString, TH2F*>::iterator mit = _2DEfficiencyMap.begin(); mit != _2DEfficiencyMap.end(); mit++){
    cout << mit->first <<" " << mit->second << endl;    
  }  
  
  cout << "Possible _EfficiencyMapHST hists are : " << endl;
  for(map<TString, TH1*>::iterator mit = _EfficiencyMapHST.begin(); mit != _EfficiencyMapHST.end(); mit++){
    cout << mit->first << endl;  
  }

  cout << "Possible _2DEfficiencyMapHST hists are : " << endl;
  for(map<TString, TH2F*>::iterator mit = _2DEfficiencyMapHST.begin(); mit != _2DEfficiencyMapHST.end(); mit++){
    cout << mit->first << " " << mit->second << endl;    
  }  

  exit(1);
}

void HNCommonLeptonFakes::NullTotals(){
  fsys=0;
  rsys=0;
  
}


void HNCommonLeptonFakes::CheckFile(TFile* file){

  if(file) cout << "HNCommonLeptonFakes: File " << file->GetName() << " was found." << endl;
  else cout << "HNCommonLeptonFakes  " << file->GetName()  << "  : ERROR Rootfile failed to open." << endl;
  
  if(!file) exit(0);
  return;
}



float HNCommonLeptonFakes::CalculateDiLepMMWeight(float r1, float fr1, float r2, float fr2, bool mu1Tight, bool mu2Tight){
 
  
  // Function calculates event weight given r/f of two muons in the event
  double alpha = 1./((1.- fr1)*(1.- fr2));

  // Initialise weight
  float w_mm=-999.;
    
  // Terms for RF and FR events from MM
  double termTT = 0.;
  double termTL = alpha*(fr2*(1.-fr1));
  double termLT = alpha*(fr1*(1.-fr2));
  double termLL = -2.*alpha*(fr2*(fr1));
  
  
  // Term for FF events
  termTT += 0.;
  termTL += 0.;
  termLT += 0.;
  termLL += alpha*(fr1*fr2);

  
  // decide which type of event we have so to return correct weight
  bool isLL = (!mu1Tight&&!mu2Tight);
  bool isLT = (!mu1Tight&&mu2Tight);
  bool isTL = (mu1Tight && !mu2Tight);
  bool isTT = (mu1Tight && mu2Tight);

  if(isLL)w_mm = termLL;
  if(isTL)w_mm = termTL;
  if(isLT)w_mm = termLT;
  if(isTT)w_mm=  termTT;  



  return w_mm;   
}


float HNCommonLeptonFakes::CalculateDiLepMMWeight(float r1, float fr1, float r2, float fr2, bool mu1Tight, bool mu2Tight, int eventtype){


  // Function calculates event weight given r/f of two muons in the event
  double alpha = 1./((r1- fr1)*(r2- fr2));
  
  // Initialise weight
  float w_mm=-999.;


  // Terms for RF and FR events from MM
  double termTT = 0.;
  double termTL = alpha*(fr2*(1.-fr1));
  double termLT = alpha*(fr1*(1.-fr2));
  double termLL = -2.*alpha*(fr2*(fr1));


  // Term for FF events
  termTT += 0.;
  termTL += 0.;
  termLT += 0.;
  termLL += alpha*(fr1*fr2);


  // decide which type of event we have so to return correct weight
  bool isLL = (!mu1Tight&&!mu2Tight);
  bool isLT = (!mu1Tight&&mu2Tight);
  bool isTL = (mu1Tight && !mu2Tight);
  bool isTT = (mu1Tight && mu2Tight);



  if(isLL)w_mm = termLL;
  if(isTL)w_mm = termTL;
  if(isLT)w_mm = termLT;
  if(isTT)w_mm=  termTT;


  return w_mm;
}



double HNCommonLeptonFakes::lepton_weight(bool loose, double r, double f) {
  // Function to get event weight for a single muon event
  double nl=loose ? 1 :0;
  double nt=!loose ? 1 :0;
  if(r==f) return 0.;
  double a=1./(r-f);
  float nf=a*f*r*nl;
  float nr=a*f*(r - 1.)*nt;
  return nf+nr;
}

void HNCommonLeptonFakes::APPLY_scalefactor(bool applysf) {
  apply_scalefactor = applysf;
}
