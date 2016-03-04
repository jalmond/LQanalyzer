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

void MakeDataInputFile(TString version=""){
  

  TString def_version = TString(getenv("CATVERSION"));
  if(!version.Contains("v7") ) version = def_version;

  ofstream lumi_file;
  string lfile =  "datasets_snu_CAT_data_" + string(version.Data()) + ".txt";
  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield);
  lumi_file.precision(1);
  
  lumi_file << "########################" << endl;
  lumi_file << "### CATTUPLES ##########" << endl;
  lumi_file << "########################" << endl;
  
  lumi_file << "\n" << endl;
  lumi_file << "#######################################################################################################################################" << endl;
  lumi_file << "# sample              Effective lumi    Path ##########################################################################################" << endl;
  lumi_file << "#######################################################################################################################################" << endl;
  
  
  vector<TString> samples;
  samples.push_back("SingleMuon");
  samples.push_back("SingleElectron");
  samples.push_back("DoubleMuon");
  samples.push_back("DoubleEG");
  samples.push_back("MuonEG");
  samples.push_back("SinglePhoton");
  vector<TString> samples_space;
  samples_space.push_back("    ");
  samples_space.push_back("");
  samples_space.push_back("    ");
  samples_space.push_back("      ");
  samples_space.push_back("        ");
  samples_space.push_back("  ");



  vector<TString> periods;
  periods.push_back("C");
  periods.push_back("D");
  
  TString output="/data2/DATA/cattoflat/Data/" + version + "/";
  
  for(unsigned int i = 0 ; i < samples.size() ; i++){
    for(unsigned int j = 0 ; j < periods.size() ; j++){
      lumi_file << samples.at(i)  << samples_space.at(i)<< "            " << periods.at(j) <<   "        " <<  output +  samples.at(i) << "/period" <<  periods.at(j) << "/" << endl;
    }
    //lumi_file << ""<< endl;
  }

  
  TString SKTreeOutput="/data2/CatNtuples/"+ version + "/SKTrees/Data/";
  

  lumi_file << ""<< endl;
  lumi_file << "#### Single lepton skims: SKTrees" << endl;
  lumi_file << ""<< endl;
  for(unsigned int i = 0 ; i < samples.size() ; i++){
    for(unsigned int j = 0 ; j < periods.size() ; j++){
      lumi_file << "SK" << samples.at(i)  << samples_space.at(i) << "            " << periods.at(j) <<   "        " <<  SKTreeOutput +  samples.at(i) << "/period" <<  periods.at(j) << "/" << endl;
    }
    //lumi_file << ""<< endl;
  }

  lumi_file << ""<< endl;
  lumi_file << "#### Single dilepton skims: SKTrees" << endl;
  lumi_file << ""<< endl;
  

  TString SKTreeOutputDiLep="/data2/CatNtuples/"+ version + "/SKTrees/DataDiLep/";
  
  for(unsigned int i = 0 ; i < samples.size() ; i++){
    for(unsigned int j = 0 ; j < periods.size() ; j++){
      lumi_file << "SK" << samples.at(i) << "_dilep"  << samples_space.at(i) <<"            " << periods.at(j) <<   "        " <<  SKTreeOutputDiLep +  samples.at(i) << "/period" <<  periods.at(j)<< "/" << endl;
    }
    //lumi_file << ""<< endl;
  }
  

  string lqdir = getenv("LQANALYZER_DIR");
  TString user = TString(getenv("USER"));

  string lfile2 =   lqdir+ "/LQRun/txt/datasets_snu_CAT_data_" + string(version.Data()) + ".txt";
  if(user.Contains("jalmond"))
    gSystem->Exec(("cp " + lfile + "  /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/").c_str());
  gSystem->Exec(("mv " + lfile +" " + lfile2).c_str());

    
  return;
  
}
