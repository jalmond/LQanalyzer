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

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);
float GetSumWeights(std::string filename);
map<TString, Double_t> dirmap;
map<TString, TString> lqmap;
map<TString, Double_t> map_lumi;
map<TString, Double_t> neventmap;
map<TString, Double_t> n_w_eventmap;
void GetEffectiveLuminosity(TString version="") {
  
  dirmap.clear();
  lqmap.clear();
  map_lumi.clear();
  neventmap.clear();
  n_w_eventmap.clear();
  dirmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 6024.2;
  dirmap["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 18610. ;
  dirmap["ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =80.95*0.322;
  dirmap["ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =136.02*0.322;
  dirmap["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =35.6;
  dirmap["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =35.6;
  dirmap["ttHTobb_M125_13TeV_powheg_pythia8"] =0.5058;
  dirmap["ttHToNonbb_M125_13TeV_powheg_pythia8"] =0.5058;
  dirmap["GluGlu_HToMuMu_M125_13TeV_powheg_pythia8"] =0.00970632;   
  dirmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] =831.76;
  dirmap["TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] =831.76 ;
  dirmap["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] =0.2043;
  dirmap["TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] =0.4062;
  dirmap["TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] =0.2529 ;
  dirmap["TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] =0.5297;
  dirmap["VBF_HToMuMu_M125_13TeV_powheg_pythia8"] =0.000828308;
  dirmap["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] =61526.7;
  dirmap["WW_TuneCUETP8M1_13TeV-pythia8"] =113.826;
  dirmap["WZ_TuneCUETP8M1_13TeV-pythia8"] =47.13;
  dirmap["ZZ_TuneCUETP8M1_13TeV-pythia8"] =16.91;
  dirmap["QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] = 558528000*0.0053; 
  dirmap["QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =139803000*0.01182;  
  dirmap["QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =19222500*0.02276;  
  dirmap["QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =2758420*0.03844;
  dirmap["QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =469797*0.05362;    
  dirmap["QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =117989*0.07335;  
  dirmap["QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =7820.25*0.10196;  
  dirmap["QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =645.528*0.12242;  
  dirmap["QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =187.109*0.13412;  
  dirmap["QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =32.3486*0.14552;  
  dirmap["QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] =10.4305*0.15544;  
  dirmap["QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =557600000*0.0096;
  dirmap["QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =136000000*0.073;  
  dirmap["QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =19800000*0.146 ;    
  dirmap["QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =2800000*0.125;    
  dirmap["QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =477000*0.132;    
  dirmap["QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =114000*0.165;  
  dirmap["QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] =9000*0.15;    


  lqmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY50plus";
  lqmap["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY10to50";
  lqmap["ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbar";
  lqmap["ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_t";
  lqmap["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbarW";
  lqmap["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tW";
  lqmap["ttHTobb_M125_13TeV_powheg_pythia8"] ="ttHtobb";
  lqmap["ttHToNonbb_M125_13TeV_powheg_pythia8"] ="ttHnobb";
  lqmap["GluGlu_HToMuMu_M125_13TeV_powheg_pythia8"] ="ggHtomm";
  lqmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] ="TTJets_MCatNLO";
  lqmap["TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] ="TTJets_MG5";
  lqmap["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] ="ttWJetsToLNu";
  lqmap["TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] ="ttWJetsToQQ";
  lqmap["TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] ="ttZToLLNuNu";
  lqmap["TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] ="ttZToQQ";
  lqmap["VBF_HToMuMu_M125_13TeV_powheg_pythia8"] ="vhf_Htomm";
  lqmap["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] ="WJets";
  lqmap["WW_TuneCUETP8M1_13TeV-pythia8"] ="WW";
  lqmap["WZ_TuneCUETP8M1_13TeV-pythia8"] ="WZ";
  lqmap["ZZ_TuneCUETP8M1_13TeV-pythia8"] ="ZZ";
  lqmap["QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu20to30";
  lqmap["QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu30to50";
  lqmap["QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu50to80";
  lqmap["QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu80to120";
  lqmap["QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu120to170";
  lqmap["QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu170to300";
  lqmap["QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu300to470";
  lqmap["QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu470to600";
  lqmap["QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu600to800";
  lqmap["QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"] ="QCD_mu800to1000";
  lqmap["QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8"]= "QCD_mu1000toINF";

  lqmap["QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em20to30";
  lqmap["QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em30to50";
  lqmap["QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em50to80";
  lqmap["QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em80to120";
  lqmap["QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em120to170";
  lqmap["QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em170to300";
  lqmap["QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8"] ="QCD_em300toINF";
  

  TString def_version = TString(getenv("CATVERSION"));  
  for(std::map<TString, Double_t>::iterator mit =dirmap.begin(); mit != dirmap.end();++mit){
    

    if(!version.Contains("v7") ) version = def_version;
    
    TString dir = "ls /data2/DATA/cattoflat/MC/" + version + "/"+ mit->first + "/*.root > inputlist.txt";
    
    bool use_sum_genweight(false);
    if(mit->first.Contains("amcatnlo")) use_sum_genweight=true;
    else use_sum_genweight=false;
    
    system(dir.Data());
    
    
    std::ifstream fin("inputlist.txt");
    std::string word;
   
    float number_events_processed(0.);
    float number_events_passed(0.);
    float sum_of_weights(0.);
    while ( fin >> word ) {
      number_events_processed+= GetEventsProcessed(word);
      number_events_passed+= GetEventsPassed(word);
      if(use_sum_genweight)sum_of_weights += GetSumWeights(word);
    }
    if(!use_sum_genweight) sum_of_weights = number_events_processed;

    fin.close();
       
    float lumi = number_events_processed / mit->second;
    if(use_sum_genweight) lumi = sum_of_weights / mit->second;
    
    std::cout.precision(10);
    std::cout <<mit->first << "    nevents =  " << number_events_processed << " sum of weights =  " << sum_of_weights << " eff lumi = " << lumi <<std::endl;
    
    system("rm inputlist.txt");

    map_lumi[mit->first] = lumi;
    neventmap[mit->first]=number_events_processed;
    n_w_eventmap[mit->first]=sum_of_weights;
  }    
  ofstream lumi_file;
  string lfile =  "dataset_list_mc_" + string(version.Data()) + ".txt";
  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield); 
  lumi_file.precision(1);

  lumi_file << "########################" << endl;
  lumi_file << "### CATTUPLES ########## "  << endl;
  lumi_file << "#######################" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "#######################################################################################################################################" << endl;
  lumi_file << "# sample     Nevents  Sum(GenWeights)  xsec*Eff   Effective lumi    LocalPath #####################################################################################" << endl;
  lumi_file << "#######################################################################################################################################" << endl;
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
    std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);    
    std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);    
    std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);    
    std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);    
    lumi_file <<  mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << "  /data2/DATA/cattoflat/MC/" << version <<"/"  << mit->first << "/" <<endl;
  }

  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "#### Single lepton skims: SKTrees" << endl;
  for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
    std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
    lumi_file <<  "SK" << mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " /data2/CatNtuples/" + string(version.Data()) +"/SKTrees/MC/" << version <<"/"  << mit2->second << "/" <<endl;
  }

  
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "#### Single lepton skims: SKTrees" << endl;
  for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
    std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
    lumi_file <<  "SK" << mit2->second << "_dilep  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " /data2/CatNtuples/" + string(version.Data()) +"/SKTrees/MCDiLep1510/" << version <<"/"  << mit2->second << "/" <<endl;
  }
  
  string lfile2 =  "/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_" + string(version.Data()) + ".txt";
  TSystem* g;
  int test = g->Exec(("mv " + lfile + " > " + lfile2).c_str());

  return;
  
}

float GetEventsProcessed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());
  //  cout << file << endl;
  TH1F*  EventCounter = (TH1F*) (file ->Get("ntuple/hNEvent"));
  
  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}

float GetEventsPassed(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TH1F*  EventCounter = (TH1F*) (file ->Get("ntuple/hNEvent"));

  float value = EventCounter->GetBinContent(1);
  file->Close();
  return value;
}

float GetSumWeights(std::string filename){
  TFile* file = TFile::Open(filename.c_str());

  TDirectory * dir = (TDirectory*)file->Get(TString(filename) + ":/ntuple");
  TTree * tree;
  dir->GetObject("event",tree);
  
  float genWeight=0;
  TBranch        *b_genWeight; 
  
  tree->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
  
  float sum_weight=0.;
  Long64_t nentries = tree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tree->LoadTree(jentry);
    nb = tree->GetEntry(jentry);
    sum_weight += genWeight;
  }
  cout << "sum_weight = " << sum_weight << endl;
  return sum_weight;
}
