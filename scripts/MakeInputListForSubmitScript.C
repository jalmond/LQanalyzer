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

  lumi_file << "source ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh" << endl;
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

  lumi_file << "declare -a qcd=('" ;
  for(std::map<TString, TString>::iterator mit =lqmap.begin(); mit != lqmap.end();++mit){
    if(!mit->second.Contains("QCD")) continue;
    bool last=true;
    for(std::map<TString, TString>::iterator mit2 =next(mit); mit2 != lqmap.end();++mit2){
      if(mit2->second.Contains("QCD")) last=false;
    }
    if(!last)lumi_file << mit->second << "' '"   ;
    else  lumi_file << mit->second ;
  } lumi_file << "') " << endl;
  lumi_file << "" << endl;
  
  lumi_file << "declare -a qcd_mu=('" ;
  for(std::map<TString, TString>::iterator mit =lqmap.begin(); mit != lqmap.end();++mit){
    if(!mit->second.Contains("QCD_mu")) continue;
    bool last=true;
    for(std::map<TString, TString>::iterator mit2 =next(mit); mit2 != lqmap.end();++mit2){
      if(mit2->second.Contains("QCD_mu")) last=false;
    }   
    if(!last)lumi_file << mit->second << "' '"   ;
    else  lumi_file << mit->second ;
  } lumi_file << "') " << endl;
  lumi_file << "" << endl;
  
  lumi_file << "declare -a qcd_eg=('" ;
  for(std::map<TString, TString>::iterator mit =lqmap.begin(); mit != lqmap.end();++mit){
    if(!mit->second.Contains("QCD")) continue;
    if(mit->second.Contains("QCD_mu")) continue;
    bool last=true;
    for(std::map<TString, TString>::iterator mit2 =next(mit); mit2 != lqmap.end();++mit2){
      if(mit2->second.Contains("QCD")) {
	if(!mit->second.Contains("QCD_mu")) {
	  last=false;
	}
      }
    }
    if(!last)lumi_file << mit->second << "' '"   ;
    else  lumi_file << mit->second ;
  } lumi_file << "') " << endl;
  lumi_file << "" << endl;


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
