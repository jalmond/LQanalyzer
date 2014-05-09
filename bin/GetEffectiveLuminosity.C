#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1I.h"
#include "TString.h"
#include <iomanip>

#include <map>

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);

void GetEffectiveLuminosity() {
  

  map<TString, double> dirmap;
  // dir name  = xsec
  dirmap["DYJetsToLL_M-10To50_TuneZ2Star_8TeV-madgraph"] = 11050 ;
  dirmap["DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball"] = 3503.71 ;
  dirmap["DYToEE_M-20_CT10_TuneZ2star_8TeV-powheg-pythia6"] = 1. ;
  dirmap["DYToMuMu_M-20_CT10_TuneZ2star_8TeV-powheg-pythia6"] = 1. ;
  dirmap["DYToTauTau_M-20_CT10_TuneZ2star_8TeV-powheg-pythia6"] = 1. ;
  dirmap["GluGluToHToZZTo4L_M-125_8TeV-powheg-pythia6"] = 0.0524 ;
  dirmap["MajoranaNeutrinoToEE_M-100_TuneZ2star_8TeV-alpgen"] = 3.5618 ;
  dirmap["MajoranaNeutrinoToEE_M-125_TuneZ2star_8TeV-alpgen"] =  1.0767;
  dirmap["MajoranaNeutrinoToEE_M-150_TuneZ2star_8TeV-alpgen"] =  0.4594;
  dirmap["MajoranaNeutrinoToEE_M-175_TuneZ2star_8TeV-alpgen"] =  0.23266;
  dirmap["MajoranaNeutrinoToEE_M-200_TuneZ2star_8TeV-alpgen"] =  0.13127;
  dirmap["MajoranaNeutrinoToEE_M-225_TuneZ2star_8TeV-alpgen"] =  0.079661;
  dirmap["MajoranaNeutrinoToEE_M-250_TuneZ2star_8TeV-alpgen"] =  0.050928;
  dirmap["MajoranaNeutrinoToEE_M-275_TuneZ2star_8TeV-alpgen"] =  0.033857;
  dirmap["MajoranaNeutrinoToEE_M-300_TuneZ2star_8TeV-alpgen"] =  0.023214;
  dirmap["MajoranaNeutrinoToEE_M-325_TuneZ2star_8TeV-alpgen"] =  0.016317;
  dirmap["MajoranaNeutrinoToEE_M-350_TuneZ2star_8TeV-alpgen"] =  0.011705;
  dirmap["MajoranaNeutrinoToEE_M-375_TuneZ2star_8TeV-alpgen"] =  0.0085448;
  dirmap["MajoranaNeutrinoToEE_M-400_TuneZ2star_8TeV-alpgen"] =  0.0063324;
  dirmap["MajoranaNeutrinoToEE_M-40_TuneZ2star_8TeV-alpgen"] =  1516;
  dirmap["MajoranaNeutrinoToEE_M-500_TuneZ2star_8TeV-alpgen"] =  0.0021542;
  dirmap["MajoranaNeutrinoToEE_M-50_TuneZ2star_8TeV-alpgen"] =  1071.1;
  dirmap["MajoranaNeutrinoToEE_M-600_TuneZ2star_8TeV-alpgen"] =  0.0008545;
  dirmap["MajoranaNeutrinoToEE_M-60_TuneZ2star_8TeV-alpgen"] =  607.7;
  dirmap["MajoranaNeutrinoToEE_M-700_TuneZ2star_8TeV-alpgen"] =  0.00038312;
  dirmap["MajoranaNeutrinoToEE_M-70_TuneZ2star_8TeV-alpgen"] =  211.96;
  dirmap["MajoranaNeutrinoToEE_M-80_TuneZ2star_8TeV-alpgen"] =  19.07;
  dirmap["MajoranaNeutrinoToEE_M-90_TuneZ2star_8TeV-alpgen"] =  7.1047;
  dirmap["MajoranaNeutrinoToEMu_M-40_TuneZ2star_8TeV-alpgen"] =  1516;
  dirmap["MajoranaNeutrinoToEMu_M-60_TuneZ2star_8TeV-alpgen"] =  607.7;
  dirmap["MajoranaNeutrinoToEMu_M-70_TuneZ2star_8TeV-alpgen"] =  211.96;
  dirmap["MajoranaNeutrinoToEMu_M-80_TuneZ2star_8TeV-alpgen"] =  19.07;
  dirmap["MajoranaNeutrinoToEMu_M-90_TuneZ2star_8TeV-alpgen"] =  7.1047;
  dirmap["MajoranaNeutrinoToEMu_M-100_TuneZ2star_8TeV-alpgen"] =  3.5618;
  dirmap["MajoranaNeutrinoToEMu_M-125_TuneZ2star_8TeV-alpgen"] =  1.0767;
  dirmap["MajoranaNeutrinoToEMu_M-150_TuneZ2star_8TeV-alpgen"] =  0.4594;
  dirmap["MajoranaNeutrinoToEMu_M-175_TuneZ2star_8TeV-alpgen"] =  0.23266;
  dirmap["MajoranaNeutrinoToEMu_M-200_TuneZ2star_8TeV-alpgen"] =  0.13127;
  dirmap["MajoranaNeutrinoToEMu_M-225_TuneZ2star_8TeV-alpgen"] =  0.079661;
  dirmap["MajoranaNeutrinoToEMu_M-250_TuneZ2star_8TeV-alpgen"] =  0.050928;
  dirmap["MajoranaNeutrinoToEMu_M-275_TuneZ2star_8TeV-alpgen"] =  0.033857;
  dirmap["MajoranaNeutrinoToEMu_M-300_TuneZ2star_8TeV-alpgen"] =  0.023214;
  dirmap["MajoranaNeutrinoToEMu_M-325_TuneZ2star_8TeV-alpgen"] =  0.016317;
  dirmap["MajoranaNeutrinoToEMu_M-350_TuneZ2star_8TeV-alpgen"] =  0.011705;
  dirmap["MajoranaNeutrinoToEMu_M-375_TuneZ2star_8TeV-alpgen"] =  0.0085448;
  dirmap["MajoranaNeutrinoToEMu_M-400_TuneZ2star_8TeV-alpgen"] =  0.0063324;
  dirmap["MajoranaNeutrinoToEMu_M-500_TuneZ2star_8TeV-alpgen"] =  0.0021542;
  dirmap["MajoranaNeutrinoToEMu_M-50_TuneZ2star_8TeV-alpgen"] =  1071.1;
  dirmap["MajoranaNeutrinoToMuE_M-60_TuneZ2star_8TeV-alpgen"] =  607.7;
  dirmap["MajoranaNeutrinoToMuE_M-70_TuneZ2star_8TeV-alpgen"] =  211.96;
  dirmap["MajoranaNeutrinoToMuE_M-80_TuneZ2star_8TeV-alpgen"] =  19.07;
  dirmap["MajoranaNeutrinoToMuE_M-90_TuneZ2star_8TeV-alpgen"] =  7.1047;
  dirmap["MajoranaNeutrinoToMuE_M-100_TuneZ2star_8TeV-alpgen"] =  3.5618;
  dirmap["MajoranaNeutrinoToMuE_M-125_TuneZ2star_8TeV-alpgen"] =  1.0767;
  dirmap["MajoranaNeutrinoToMuE_M-150_TuneZ2star_8TeV-alpgen"] =  0.4594;
  dirmap["MajoranaNeutrinoToMuE_M-175_TuneZ2star_8TeV-alpgen"] =  0.23266;
  dirmap["MajoranaNeutrinoToMuE_M-200_TuneZ2star_8TeV-alpgen"] =  0.13127;
  dirmap["MajoranaNeutrinoToMuE_M-225_TuneZ2star_8TeV-alpgen"] =  0.079661;
  dirmap["MajoranaNeutrinoToMuE_M-250_TuneZ2star_8TeV-alpgen"] =  0.050928;
  dirmap["MajoranaNeutrinoToMuE_M-275_TuneZ2star_8TeV-alpgen"] =  0.033857;
  dirmap["MajoranaNeutrinoToMuE_M-300_TuneZ2star_8TeV-alpgen"] =  0.023214;
  dirmap["MajoranaNeutrinoToMuE_M-325_TuneZ2star_8TeV-alpgen"] =  0.016317;
  dirmap["MajoranaNeutrinoToMuE_M-350_TuneZ2star_8TeV-alpgen"] =  0.011705;
  dirmap["MajoranaNeutrinoToMuE_M-375_TuneZ2star_8TeV-alpgen"] =  0.0085448;
  dirmap["MajoranaNeutrinoToMuE_M-400_TuneZ2star_8TeV-alpgen"] =  0.0063324;
  dirmap["MajoranaNeutrinoToMuE_M-500_TuneZ2star_8TeV-alpgen"] =  0.0021542;
  dirmap["MajoranaNeutrinoToMuE_M-50_TuneZ2star_8TeV-alpgen"] =  1071.1;
  dirmap["MajoranaNeutrinoToMuMu_M-100_TuneZ2star_8TeV-alpgen"] =  3.5618;
  dirmap["MajoranaNeutrinoToMuMu_M-125_TuneZ2star_8TeV-alpgen"] =  1.0767;
  dirmap["MajoranaNeutrinoToMuMu_M-150_TuneZ2star_8TeV-alpgen"] =  0.4594;
  dirmap["MajoranaNeutrinoToMuMu_M-175_TuneZ2star_8TeV-alpgen"] =  0.23266;
  dirmap["MajoranaNeutrinoToMuMu_M-200_TuneZ2star_8TeV-alpgen"] =  0.13127;
  dirmap["MajoranaNeutrinoToMuMu_M-225_TuneZ2star_8TeV-alpgen"] =  0.079661;
  dirmap["MajoranaNeutrinoToMuMu_M-250_TuneZ2star_8TeV-alpgen"] =  0.050928;
  dirmap["MajoranaNeutrinoToMuMu_M-275_TuneZ2star_8TeV-alpgen"] =  0.033857;
  dirmap["MajoranaNeutrinoToMuMu_M-300_TuneZ2star_8TeV-alpgen"] =  0.023214;
  dirmap["MajoranaNeutrinoToMuMu_M-325_TuneZ2star_8TeV-alpgen"] =  0.016317;
  dirmap["MajoranaNeutrinoToMuMu_M-350_TuneZ2star_8TeV-alpgen"] =  0.011705;
  dirmap["MajoranaNeutrinoToMuMu_M-375_TuneZ2star_8TeV-alpgen"] =  0.0085448;
  dirmap["MajoranaNeutrinoToMuMu_M-400_TuneZ2star_8TeV-alpgen"] =  0.0063324;
  dirmap["MajoranaNeutrinoToMuMu_M-40_TuneZ2star_8TeV-alpgen"] =  1516;
  dirmap["MajoranaNeutrinoToMuMu_M-500_TuneZ2star_8TeV-alpgen"] =  0.0021542;
  dirmap["MajoranaNeutrinoToMuMu_M-50_TuneZ2star_8TeV-alpgen"] =  1071.1;
  dirmap["MajoranaNeutrinoToMuMu_M-600_TuneZ2star_8TeV-alpgen"] =  0.0008545;
  dirmap["MajoranaNeutrinoToMuMu_M-60_TuneZ2star_8TeV-alpgen"] =  607.7;
  dirmap["MajoranaNeutrinoToMuMu_M-700_TuneZ2star_8TeV-alpgen"] =  0.00038312;
  dirmap["MajoranaNeutrinoToMuMu_M-70_TuneZ2star_8TeV-alpgen"] =  211.96;
  dirmap["MajoranaNeutrinoToMuMu_M-80_TuneZ2star_8TeV-alpgen"] =  19.07;
  dirmap["MajoranaNeutrinoToMuMu_M-90_TuneZ2star_8TeV-alpgen"] =  7.1047;
  dirmap["QCD2MuMu_2MupPtEtaFilterFilter_8TeV-pythia6"] =  1.;
  dirmap["QCD_Pt_170_250_BCtoE_TuneZ2star_8TeV_pythia6"] =  631.99;
  dirmap["QCD_Pt_170_250_EMEnriched_TuneZ2star_8TeV_pythia6"] =  (30990*0.148);
  dirmap["QCD_Pt_20_30_BCtoE_TuneZ2star_8TeV_pythia6"] =  167388;
  dirmap["QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6"] =  (288600000*0.0101);
  dirmap["QCD_Pt_250_350_BCtoE_TuneZ2star_8TeV_pythia6"] =  103.27;
  dirmap["QCD_Pt_250_350_EMEnriched_TuneZ2star_8TeV_pythia6"] =  (4250*0.131);
  dirmap["QCD_Pt_30_80_BCtoE_TuneZ2star_8TeV_pythia6"] =  167040;
  dirmap["QCD_Pt_30_80_EMEnriched_TuneZ2star_8TeV_pythia6"] =  (74330000*0.0621);
  dirmap["QCD_Pt-30to40_doubleEMEnriched_TuneZ2star_8TeV-pythia6"] =  (51950000*0.000235);
  dirmap["QCD_Pt-40_doubleEMEnriched_TuneZ2star_8TeV-pythia6"] =  (51950000*0.002175);
  dirmap["QCD_Pt_80_170_BCtoE_TuneZ2star_8TeV_pythia6"] =  12982;
  dirmap["QCD_Pt_80_170_EMEnriched_TuneZ2star_8TeV_pythia6"] =  (1191000*0.1539);
  dirmap["TTGJets_8TeV-madgraph"] =  2.166;
  dirmap["TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola"] =  234.;
  dirmap["TTWJets_8TeV-madgraph"] =  0.232;
  dirmap["TTWWJets_8TeV-madgraph"] =  0.002037;
  dirmap["TTZJets_8TeV-madgraph_v2"] =0.174;
  dirmap["WbbJetsToLNu_Massive_TuneZ2star_8TeV-madgraph-pythia6_tauola"] =  39.9;
  dirmap["WGstarToLNu2E_TuneZ2star_8TeV-madgraph-tauola"] =  5.873;
  dirmap["WGstarToLNu2Mu_TuneZ2star_7TeV-madgraph-tauola"] =  1.914;
  dirmap["WGstarToLNu2Tau_TuneZ2star_7TeV-madgraph-tauola"] =  0.336;
  dirmap["WGToLNuG_TuneZ2star_8TeV-madgraph-tauola"] =  553.9;
  dirmap["WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola"] =  0.0177;
  dirmap["WH_ZH_TTH_HToWW_M-125_8TeV-pythia6"] =  0.2604;
  dirmap["WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6"] =  0.0320;
  dirmap["WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball"] = 37509.;
  dirmap["WmWmqq_8TeV-madgraph"] =  0.08888;
  dirmap["WpWpqq_8TeV-madgraph"] =  0.2482;
  dirmap["WW_DoubleScattering_8TeV-pythia8"] =0.5879  ;
  dirmap["WWJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola"] =  5.812;
  dirmap["WW_TuneZ2star_8TeV_pythia6_tauola"] =  54.838;
  dirmap["WWWJets_8TeV-madgraph"] =  0.0822;
  dirmap["WWZNoGstarJets_8TeV-madgraph"] =  0.0633;
  dirmap["WZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola"] =  2.206;
  dirmap["WZJetsTo2QLNu_8TeV-madgraph"] =  1.584;
  dirmap["WZJetsTo3LNu_TuneZ2_8TeV-madgraph-tauola"] =  1.058;
  dirmap["WZ_TuneZ2star_8TeV_pythia6_tauola"] =  33.21;
  dirmap["WZZNoGstarJets_8TeV-madgraph"] =  0.0192;
  dirmap["ZbbToLL_massive_M-50_TuneZ2star_8TeV-madgraph-pythia6_tauola"] =  94.1;
  dirmap["ZGToLLG_8TeV-madgraph"] =  132.6;
  dirmap["ZZJetsTo2L2Nu_TuneZ2star_8TeV-madgraph-tauola"] =  0.3648;
  dirmap["ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola"] =  2.449;
  dirmap["ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola"] =  0.177;
  dirmap["ZZTo2e2mu_8TeV-powheg-pythia6"] =  0.1767;
  dirmap["ZZTo2e2tau_8TeV-powheg-pythia6"] =  0.1767;
  dirmap["ZZTo2mu2tau_8TeV-powheg-pythia6"] =  0.1767;
  dirmap["ZZTo4e_8TeV-powheg-pythia6"] =  0.07691;
  dirmap["ZZTo4mu_8TeV-powheg-pythia6"] =  0.07691;
  dirmap["ZZTo4tau_8TeV-powheg-pythia6"] =  0.07691;
  dirmap["ZZ_TuneZ2star_8TeV_pythia6_tauola"] =  17.654;
  dirmap["ZZZNoGstarJets_8TeV-madgraph"] =  0.00459;
  dirmap["WWGJets_8TeV-madgraph"] =  0.528;
  
  for(map<TString, double>::iterator it = dirmap.begin(); it != dirmap.end();it++){
    
    
    TString dir = "ls /data1/DATA/LQNtuples_5_3_14_snu27/MC/" + it->first + "/*.root > inputlist.txt";
    system(dir.Data());
    
    
    std::ifstream fin("inputlist.txt");
    std::string word;
    
    float number_events_processed(0.);
    float number_events_passed(0.);
    while ( fin >> word ) {
      number_events_processed+= GetEventsProcessed(word);
      number_events_passed+= GetEventsPassed(word);
    }
    fin.close();
    
    
   
    float lumi = number_events_processed / it->second;

    std::cout.precision(10);
    std::cout << it->first << "    " << lumi << std::endl;
    
    system("rm inputlist.txt");
  }    

    return;
    
}

float GetEventsProcessed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1I*  EventCounter = (TH1I*) (file ->Get("LJFilter/EventCount/EventCounter"));  
  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}

float GetEventsPassed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1I*  EventCounter = (TH1I*) (file ->Get("LJFilter/EventCount/EventCounter"));

  float value = EventCounter->GetBinContent(2);
  file->Close();
  return value;
}
