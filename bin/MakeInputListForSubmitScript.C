#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include <iomanip>
#include <sstream>
#include "TSystem.h"

#include <map>

map<TString, TString> lqmap;

void MakeInputListForSubmitScript(){
  
  lqmap.clear();


  
  lqmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY50plus_MCatNLO";
  lqmap["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY10to50_MCatNLO";
  lqmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = "DY50plus_madgraph";
  lqmap["ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbar_Powheg";
  lqmap["ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_t_Powheg";
  lqmap["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbarW_Powheg";
  lqmap["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tW_Powheg";
  lqmap["ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"] = "singletop_s_MCatNLO";
  lqmap["ttHTobb_M125_13TeV_powheg_pythia8"] ="ttHtobb_Powheg";
  lqmap["ttHToNonbb_M125_13TeV_powheg_pythia8"] ="ttHnobb_Powheg";
  lqmap["GluGlu_HToMuMu_M125_13TeV_powheg_pythia8"] ="ggHtomm_Powheg";
  lqmap["VBF_HToMuMu_M125_13TeV_powheg_pythia8"] ="vhf_Htomm_Powheg";
  lqmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] ="TT_MCatNLO";
  lqmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaleup-pythia8"] = "TT_scaleup_MCatNLO";
  lqmap["TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] ="TT_MG5";
  lqmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaledown-pythia8"] = "TT_scaledown_MCatNLO";
  lqmap["TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8"] = "TT_scaleup_powheg";
  lqmap["TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8"]= "TT_scaledown_powheg";
  lqmap["TT_TuneCUETP8M1_13TeV-powheg-pythi8"]=  "TT_powheg";
  lqmap["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] ="ttWJetsToLNu_MCatNLO";
  lqmap["TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] ="ttWJetsToQQ_MCatNLO";
  lqmap["TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] ="ttZToLLNuNu_MCatNLO";
  lqmap["TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] ="ttZToQQ_MCatNLO";
  lqmap["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] ="WJets_MCatNLO";
  lqmap["WW_TuneCUETP8M1_13TeV-pythia8"] ="WW_pythia8";
  lqmap["WZ_TuneCUETP8M1_13TeV-pythia8"] ="WZ_pythia8";
  lqmap["ZZ_TuneCUETP8M1_13TeV-pythia8"] ="ZZ_pythia8";
  lqmap["QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu20to30_pythia8";
  lqmap["QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu30to50_pythia8";
  lqmap["QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu50to80_pythia8";
  lqmap["QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu80to120_pythia8";
  lqmap["QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu120to170_pythia8";
  lqmap["QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu170to300_pythia8";
  lqmap["QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu300to470_pythia8";
  lqmap["QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu470to600_pythia8";
  lqmap["QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu600to800_pythia8";
  lqmap["QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu800to1000_pythia8";
  lqmap["QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"]= "QCD_mu1000toINF_pythia8";
  lqmap["QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em20to30_pythia8";
  lqmap["QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em30to50_pythia8";
  lqmap["QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em50to80_pythia8";
  lqmap["QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em80to120_pythia8";
  lqmap["QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em120to170_pythia8";
  lqmap["QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em170to300_pythia8";
  lqmap["QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em300toINF_pythia8";
  lqmap["ZZTo4L_13TeV_powheg_pythia8"] = "ZZ_llll_powheg";
  lqmap["ZZTo4L_13TeV-amcatnloFXFX-pythia8"] = "ZZ_llll_MCatNLO";
  lqmap["ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8"] = "ZZ_llqq_MCatNLO";
  lqmap["ZZTo2L2Nu_13TeV_powheg_pythia8"] = "ZZ_lllnu_powheg";
  lqmap["WWTo2L2Nu_13TeV-powheg"] = "WW_llnn_powheg";
  lqmap["WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8"] = "WZ_llqq_MCatNLO";
  lqmap["WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8"] = "WN_lllnu_powheg";
  lqmap["WZJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "WZ_lllnu_MCatNLO";
  lqmap["WpWpJJ_EWK_TuneCUETP8M1_13TeV-madgraph-pythia8"] = "WpWp_madgraph";
  lqmap["WpWpJJ_QCD_TuneCUETP8M1_13TeV-madgraph-pythia8"] = "WpWp_qcd_madgraph";
  
  lqmap["WW_DoubleScattering_13TeV-pythia8"] = "WW_doublescattering";
  lqmap["WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = "WZZ_MCatNLO";
  lqmap["GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] = "GJet_20to40_pythia8";
  lqmap["GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] = "GJet_40plus_pythia8";
  lqmap["TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] = "TTG_MCatNLO";
  lqmap["WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = "WG_lnuG_madgraph";
  lqmap["ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "ZG_llG_MCatNLO";
  lqmap["QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] = "QCD_DoubleEM_40toInf_pythia8";
  lqmap["QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8"] ="QCD_DoubleEM_30toInf_pythia8";
  lqmap["QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] ="QCD_DoubleEM_30to40_pythia8";
  lqmap["QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8"] ="QCD_20to30_bcToE_pythia8";
  lqmap["QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8"] ="QCD_80to170_bcToE_pythia8";
  lqmap["QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8"] ="QCD_170to250_bcToE_pythia8";
  lqmap["QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8"] ="QCD_250toInf_bcToE_pythia8";
  lqmap["QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8"] = "QCD_30to80_bcToE_pythia8";


  
  ofstream lumi_file;
  string lfile =  "list_all_mc.txt";
  
  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield); 
  lumi_file.precision(1);
  
  lumi_file << "########################" << endl;
  lumi_file << "### SAMPLE LIST ########## "  << endl;
  lumi_file << "#######################" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  
  lumi_file << " declare -a input_samples=('" ;
  
  for(std::map<TString, TString>::iterator mit =lqmap.begin(); mit != lqmap.end();++mit){
    lumi_file << mit->second << "' '"   ;
  }
  lumi_file << "') " << endl; 


  return;
  
}
