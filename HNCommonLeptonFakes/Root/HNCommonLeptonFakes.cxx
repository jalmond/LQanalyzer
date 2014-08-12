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
  TFile* file_mc  = TFile::Open( (lqdir + "/data/rootfiles/FakeRateMC.root").c_str());
  CheckFile(file_mc);
    
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();

  _2DEfficiencyMap["real_eff_20"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("A"));
  _2DEfficiencyMap["real_eff_20_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009_0jet"))->Clone("AB"));
  _2DEfficiencyMap["real_eff_20_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009_1jet"))->Clone("AC"));
  _2DEfficiencyMap["real_eff_20_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009_2jet"))->Clone("AD"));
  _2DEfficiencyMap["real_eff_30"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("BB"));
  _2DEfficiencyMap["real_eff_40"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AA"));
  _2DEfficiencyMap["real_eff_40_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAB"));
  _2DEfficiencyMap["real_eff_40_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAC"));
  _2DEfficiencyMap["real_eff_40_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAD"));
  _2DEfficiencyMap["real_eff_30_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAB"));
  _2DEfficiencyMap["real_eff_30_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAC"));
  _2DEfficiencyMap["real_eff_30_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAD"));
  
  
  _2DEfficiencyMap["real_eff_20_0905_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAB"));
  _2DEfficiencyMap["real_eff_20_0905_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAC"));
  _2DEfficiencyMap["real_eff_20_0905_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAD"));
  
  _2DEfficiencyMap["real_eff_30_0905_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAB"));
  _2DEfficiencyMap["real_eff_30_0905_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAC"));
  _2DEfficiencyMap["real_eff_30_0905_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAD"));

  _2DEfficiencyMap["real_eff_40_0905_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAB"));
  _2DEfficiencyMap["real_eff_40_0905_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAC"));
  _2DEfficiencyMap["real_eff_40_0905_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAAD"));

  _2DEfficiencyMap["real_eff_mc_30_0jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAB"));
  _2DEfficiencyMap["real_eff_mc_30_1jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAC"));
  _2DEfficiencyMap["real_eff_mc_30_2jet"] = dynamic_cast<TH2F*>((file_fake->Get("RealEff_Loosedxy01_009_009"))->Clone("AAAD"));
    

  /*
  _2DEfficiencyMap["real_eff_tight"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Tight"))->Clone());
  _2DEfficiencyMap["real_eff_medium"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Medium"))->Clone());
  

  _2DEfficiencyMap["real_eff_dxy05"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy05"))->Clone());
  _2DEfficiencyMap["real_eff_dxy10"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy10"))->Clone());
  _2DEfficiencyMap["real_eff_dxy15"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy15"))->Clone());
  _2DEfficiencyMap["real_eff_dxy20"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy20"))->Clone());
  _2DEfficiencyMap["real_eff_dxy25"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy25"))->Clone());
  _2DEfficiencyMap["real_eff_dxy30"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_dxy30"))->Clone());

  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_100_100"))->Clone());
  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_009"))->Clone());
  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_008"))->Clone());
  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_007"))->Clone());
  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_006"))->Clone());
  _2DEfficiencyMap["real_eff_Loosedxy01_iso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_005"))->Clone());

  _2DEfficiencyMap["real_eff_NPiso_Loosedxy01_iso_b009_e009"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_009_np"))->Clone());
  _2DEfficiencyMap["real_eff_NPiso_Loosedxy01_iso_b009_e008"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_008_np"))->Clone());
  _2DEfficiencyMap["real_eff_NPiso_Loosedxy01_iso_b009_e007"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_007_np"))->Clone());
  _2DEfficiencyMap["real_eff_NPiso_Loosedxy01_iso_b009_e006"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_006_np"))->Clone());
  _2DEfficiencyMap["real_eff_NPiso_Loosedxy01_iso_b009_e005"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_Loosedxy01_009_005_np"))->Clone());

  _2DEfficiencyMap["real_eff_iso_b050_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E125_dr03"))->Clone());

  _2DEfficiencyMap["real_eff_iso_b100_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E050_dr03"))->Clone());

  _2DEfficiencyMap["real_eff_iso_b150_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E125_dr03"))->Clone());


  _2DEfficiencyMap["real_eff_iso_b150_e150"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E150_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b060_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B060_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b150_e150"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B150_E150_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b125_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B125_E125_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b100_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B100_E100_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b090_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B090_E090_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b080_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B080_E080_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b070_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B070_E070_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b060_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B060_E060_dr04"))->Clone());
  _2DEfficiencyMap["real_eff_iso_b050_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_iso_B050_E050_dr04"))->Clone());

  _2DEfficiencyMap["real_eff_NPFiso_b050_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b050_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b050_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b050_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b050_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b050_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B050_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b070_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B070_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b080_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B080_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b090_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B090_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b100_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B100_E125_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b125_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B125_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e050"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E050_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e060"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E060_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e070"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E070_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e080"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E080_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e090"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E090_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e100"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E100_dr03"))->Clone());
  _2DEfficiencyMap["real_eff_NPFiso_b150_e125"] = dynamic_cast<TH2F*>((file_fake_Opt->Get("RealEff_NPFiso_B150_E125_dr03"))->Clone());
  
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
  */

    _2DEfficiencyMap["fake_eff_ht_20" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_pt_ht"))->Clone());
  _2DEfficiencyMap["fake_eff_20" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_20_1jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_1jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_20_2jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_2jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_20_3jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_3jet_pt_eta"))->Clone());
  
  
  _2DEfficiencyMap["fake_eff_ht_40" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_pt_ht"))->Clone());
  _2DEfficiencyMap["fake_eff_40" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_1jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_1jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_2jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_2jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_3jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_3jet_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_60" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_60_pt_eta"))->Clone());


  _2DEfficiencyMap["fake_eff_30" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_30_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30_1jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_30_1jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30_2jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_30_2jet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30_3jet" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_30_3jet_pt_eta"))->Clone());
  
  _2DEfficiencyMap["fake_eff_0bjet_20" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_bjet_20" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_0bjet_40" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_bjet_40" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_0bjet_60" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_60_0bjet_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_bjet_60" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_60_bjet_pt_eta"))->Clone());

  

  _2DEfficiencyMap["fake_eff_20_0905" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_20_0905_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_30_0905" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_30_0905_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_40_0905" ] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_40_0905_pt_eta"))->Clone());

  _2DEfficiencyMap["fake_eff_mc_20"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_20_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_mc_30"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_30_pt_eta"))->Clone());
  _2DEfficiencyMap["fake_eff_mc_40"] = dynamic_cast<TH2F*>((file_mc->Get("MCEl_40_pt_eta"))->Clone());

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
  
  file_fake->Close();
  delete file_fake;
  
  file_mc->Close();
  delete file_mc;


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



float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut, int nbjet, float ht, bool closejet1, bool closejet2){

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
  
  TString cut1, cut2;
  cut1 = "Loosedxy01_iso_b090_e090" ;
  cut2 = "Loosedxy01_iso_b090_e090" ;

  
  //r1 = getEfficiency_electron(0,_el1_pt, _el1_eta, cut1);
  //r2 = getEfficiency_electron(0,_el2_pt, _el2_eta,cut2);
  fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut1);
  fr2= getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut2);
  
  r1=1.;
  r2=1.;

  
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;
}

float HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut, int nbjet, float ht, bool user, bool useht, bool usenjet ){

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
  
  TString rcut = cut;
  if(njets == 0) rcut += "_0jet";
  if(njets == 1) rcut += "_1jet";
  if(njets > 1) rcut += "_2jet";

  //r1 = getEfficiency_electron(0,_el1_pt,  _el1_eta , rcut);
  //r2 = getEfficiency_electron(0,_el2_pt,  _el2_eta , rcut);
  //if(!user){
  r1=1.;
  r2=1.;
  //}

  TString fcut = cut;
  if(njets == 1) fcut += "_1jet";
  if(njets == 2) fcut += "_2jet";
  if(njets > 2) fcut += "_3jet";
  if(useht){
    if(ht < 20.) ht=21.;
    fr1=  getFakeRate_electron(0,_el1_pt, ht,cut);
    fr2=  getFakeRate_electron(0,_el2_pt, ht,cut);
  }
  else{
    if(usenjet){
      fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,fcut);
      fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,fcut);
    }
    else{
      if(user){
	if(nbjet==0) cut = "0bjet_" + cut ;
	else cut = "bjet_" + cut ;
      }
      fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut);
      fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut);
      
      if(cut.Contains("20")){

	if(_el1_eta > 1.5){
	  if(_el1_pt > 15. && _el1_pt < 20.)  fr1= 0.175;
	}
	if(_el2_eta > 1.5){
	  if(_el2_pt > 15. && _el2_pt < 20.)  fr2= 0.175;
	} 
	
	//if(nbjet > 0){
	//fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,fcut);
	// fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,fcut);
	//}
      }
    }
  }

  
  /*
  if(_el1_eta < 1.5){
    if(ht < 20 ) {
      if(_el1_pt < 15.) fr1*= 1.5;
      if(_el1_pt > 15. && _el1_pt < 25.) fr1*= 1.3;
    }
    else if( ht < 30.) {
      if(_el1_pt > 10. && _el1_pt < 20.) fr1*= 1.5;
    }
    else if(ht < 60){
      if(_el1_pt > 15. && _el1_pt < 20.)  fr1*= 1.3;
    }
    else if(ht < 80) {
      if(_el1_pt < 15) fr1*= 1.5;
    }
    else{
      if(_el1_pt < 15) fr1/= 1.2;
      if(_el1_pt > 20. && _el1_pt < 35.) fr1*= 1.5;
    }
  }
  else{
    if(ht < 20 ) {
      if( _el1_pt < 30.) fr1*= 1.5;
    }
    else if( ht < 30.) {
      if(_el1_pt > 15. && _el1_pt < 20.)  fr1*= 1.5;
    }
    else if(ht < 60){
      if(_el1_pt > 10. && _el1_pt < 20.)  fr1*= 1.5;
    }
    else if(ht < 80) {
      if(_el1_pt < 30) fr1*= 1.5;
      if(el1_pt > 15. && _el1_pt < 30) fr1*= 1.3;
    }
    else{
      if(_el1_pt > 15. && _el1_pt < 20.)  fr1*= 1.5;
    }
  }
  


  if(_el2_eta < 1.5){
    if(ht < 20 ) {
      if(_el2_pt < 15.) fr2*= 1.5;
      if(_el2_pt > 15. && _el2_pt < 25.) fr2*= 1.3;
    }
    else if( ht < 30.) {
      if(_el2_pt > 10. && _el2_pt < 20.) fr2*= 1.5;
    }
    else if(ht < 60){
      if(_el2_pt > 15. && _el2_pt < 20.)  fr2*= 1.3;
    }
    else if(ht < 80) {
      if(_el2_pt < 15) fr2*= 1.5;
    }
    else{
      if(_el2_pt < 15) fr2/= 1.2;
      if(_el2_pt > 20. && _el2_pt < 35.) fr2*= 1.5;
    }
  }
  else{
    if(ht < 20 ) {
      if( _el2_pt < 30.) fr2*= 1.5;
    }
    else if( ht < 30.) {
      if(_el2_pt > 15. && _el2_pt < 20.)  fr2*= 1.5;
    }
    else if(ht < 60){
      if(_el2_pt > 10. && _el2_pt < 20.)  fr2*= 1.5;
    }
    else if(ht < 80) {
      if(_el2_pt < 30) fr2*= 1.5;
      if(el2_pt > 15. && _el2_pt < 30) fr2*= 1.3;
    }
    else{
      if(_el2_pt > 15. && _el2_pt < 20.)  fr2*= 1.5;
    }
  }
  */
  

  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;
}

float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut){

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

  TString rcut = cut;
  if(njets == 0) rcut += "_0jet";
  if(njets == 1) rcut += "_1jet";
  if(njets > 1) rcut += "_2jet";
  //r1 = getEfficiency_electron(0,_el1_pt,  _el1_eta , rcut);
  //  r2 = getEfficiency_electron(0,_el2_pt,  _el2_eta , rcut);
  r1=1.;
  r2=1.;
  fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut);
  fr2= getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut);

  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;
}



float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight, TString cut, int eventtype, bool user1){

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


float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight){
  
  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }
  
  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();
  
  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;

 
  float _el1_eta=electrons.at(0).Eta();
  float _el2_eta=electrons.at(1).Eta();

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }
  
  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_el2_pt > 100.) _el2_pt = 99.;


  float fr1(0.),fr2(0.),r1(0.),r2(0.);  

  r1 = getEfficiency_electron(0,_el1_pt, _el1_eta);
  r2 = getEfficiency_electron(0,_el2_pt, _el2_eta);
  
  fr1= getFakeRate_electron(0,_el1_pt, _el1_eta); 
  fr2= getFakeRate_electron(0,_el2_pt, _el2_eta); 
  
  if(njets==0) fr1 = fr1*1.45;
  if(njets==0) fr2 = fr2*1.45;

  
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;

}




float  HNCommonLeptonFakes::get_dilepton_em_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electrons, int njets, bool ismu1tight, bool isel1tight){

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

  r1 = getEfficiency_muon(0,_mu1_pt, _mu1_eta);
  r2 = getEfficiency_electron(0,_el1_pt, _el1_eta);

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta);
  fr2= getFakeRate_electron(0,_el1_pt, _el1_eta);

  if(njets==0) fr2 = fr2*1.45;

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
  if(pt < 10) return -999999.;

  map<TString,TH2F*>::const_iterator mapit;

  TString hist = "fake_eff_";
  hist += cut;

  mapit = _2DEfficiencyMap.find(hist.Data());

  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,eta);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((hist.Data()));

  if(eff_fake <0.) eff_fake=0.1;
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
  double alpha = 1./((r1- fr1)*(r2- fr2));

  // Initialise weight
  float w_mm=-999.;
    
  // Terms for RF and FR events from MM
  double termTT = alpha*(r1*fr2*(fr1-1.)*(1.-r2) + (fr1*r2*(r1-1.)*(1.-fr2)));
  double termTL = alpha*(r1*fr2*((1-fr1)*r2) + (fr1*r2*(1.-r1)*fr2));
  double termLT = alpha*(r1*fr2*(fr1*(1.-r2))+ (fr1*r2*(1.-fr2)*r1));
  double termLL = -2.*alpha*(r1*fr2*(fr1*r2));
  
  
  // Term for FF events
  termTT += alpha*fr1*fr2*((1.-r1)*(1.-r2));
  termTL += alpha*fr1*fr2*r2*(r1-1.);
  termLT += alpha*fr1*fr2*r1*(r2-1.);
  termLL += alpha*r1*r2*(fr1*fr2);

  
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
  double termTT_sf = alpha*(r1*fr2*(fr1-1.)*(1.-r2) + (fr1*r2*(r1-1.)*(1.-fr2)));
  double termTL_sf = alpha*(r1*fr2*((1-fr1)*r2) + (fr1*r2*(1.-r1)*fr2));
  double termLT_sf = alpha*(r1*fr2*(fr1*(1.-r2))+ (fr1*r2*(1.-fr2)*r1));
  double termLL_sf = -2.*alpha*(r1*fr2*(fr1*r2));

  
  // Term for FF events
  double termTT_df = alpha*fr1*fr2*((1.-r1)*(1.-r2));
  double termTL_df = alpha*fr1*fr2*r2*(r1-1.);
  double termLT_df = alpha*fr1*fr2*r1*(r2-1.);
  double termLL_df = alpha*r1*r2*(fr1*fr2);

  double termTT(0.);
  double termTL(0.);
  double termLT(0.);
  double termLL(0.);
  
  if(eventtype==0) {
    termTT = termTT_sf+ termTT_df;
    termTL = termTL_sf + termTL_df;
    termLT = termLT_sf + termLT_df;
    termLL = termLL_sf + termLL_df;    
  }
  else   if(eventtype==1) {
    termTT = termTT_sf;
    termTL = termTL_sf;
    termLT = termLT_sf;
    termLL = termLL_sf;
  }
  else if(eventtype==2) {
    termTT = termTT_df;
    termTL = termTL_df;
    termLT = termLT_df;
    termLL = termLL_df;
  }

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
