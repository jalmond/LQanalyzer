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
#include "SampleMap.C"

// defined in boost/utility.hpp, by the way
template <typename Iter>
Iter next(Iter iter)
{
  return ++iter;
}

void MakeInputListForSubmitScript(){
  
  map<TString, TString> lqmap = GetLQMap();
  

  ofstream lumi_file;
  string lfile =  "list_all_mc.sh";
  
  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield); 
  lumi_file.precision(1);
  lumi_file << "#!/bin/sh" << endl;
  lumi_file << "" << endl;
  lumi_file << "########################" << endl;
  lumi_file << "### SAMPLE LIST ########## "  << endl;
  lumi_file << "#######################" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  
  lumi_file << " declare -a input_samples=('WZ_pythia8')" << endl;;
  lumi_file << "" << endl;
  lumi_file << " declare -a all_mc=('" ;
  

  for(std::map<TString, TString>::iterator mit =lqmap.begin(); mit != lqmap.end();++mit){

    cout << mit->first << " " << mit->second << endl;
    if(next(mit)!= lqmap.end()) lumi_file << mit->second << "' '"   ;
    else  lumi_file << mit->second ;
  }
    lumi_file << "') " << endl; 

  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a diboson_pythia=('WZ_pythia8' 'ZZ_pythia8' 'WW_pythia8')" << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a dy_mcatnlo=('DY10to50_MCatNLO' 'DY50plus_MCatNLO') " << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a qcd=('QCD_mu1000toINF_pythia8' 'QCD_em120to170_pythia8' 'QCD_mu120to170_pythia8' 'QCD_em170to300_pythia8' 'QCD_mu170to300_pythia8' 'QCD_em20to30_pythia8' 'QCD_mu20to30_pythia8' 'QCD_mu300to470_pythia8' 'QCD_em300toINF_pythia8' 'QCD_DoubleEM_30to40_pythia8' 'QCD_em30to50_pythia8' 'QCD_mu30to50_pythia8' 'QCD_DoubleEM_30toInf_pythia8' 'QCD_DoubleEM_40toInf_pythia8' 'QCD_mu470to600_pythia8' 'QCD_em50to80_pythia8' 'QCD_mu50to80_pythia8' 'QCD_mu600to800_pythia8' 'QCD_mu800to1000_pythia8' 'QCD_em80to120_pythia8' 'QCD_mu80to120_pythia8' 'QCD_170to250_bcToE_pythia8' 'QCD_20to30_bcToE_pythia8' 'QCD_250toInf_bcToE_pythia8' 'QCD_30to80_bcToE_pythia8' 'QCD_80to170_bcToE_pythia8' ) " << endl;

  lumi_file << "" << endl;
  lumi_file << "declare -a hn_mm=('WZ_pythia8' 'ZZ_pythia8' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu_MCatNLO' 'ttWJetsToQQ_MCatNLO' 'ttZToLLNuNu_MCatNLO' 'ttZToQQ_MCatNLO') " << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a hn_ee=('WZ_pythia8' 'ZZ_pythia8' 'WpWp_madgraph' 'WpWp_qcd_madgraph'  'ttWJetsToLNu_MCatNLO' 'ttWJetsToQQ_MCatNLO' 'ttZToLLNuNu_MCatNLO' 'ttZToQQ_MCatNLO' 'DY10to50_MCatNLO' 'DY50plus_MCatNLO') " << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a hn_fakeee=('DY10to50_MCatNLO' 'DY50plus_MCatNLO' 'WJets_MCatNLO'  'TT_MG5')" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "declare -a singletop=('singletop_s_MCatNLO' 'singletop_tbar_Powheg' 'singletop_t_Powheg' 'singletop_tbarW_Powheg' 'singletop_tW_Powheg') " << endl;

  string lfile2 =  "/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/list_all_mc.sh";

  gSystem->Exec(("cp " + lfile + "  /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/").c_str());
  gSystem->Exec(("mv " + lfile +" " + lfile2).c_str());


  return;
  
}
