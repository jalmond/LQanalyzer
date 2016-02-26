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
  dirmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 6025.2;
  dirmap["ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =80.95*0.322;
  dirmap["ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =136.02*0.322;
  dirmap["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =35.6;
  dirmap["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] =35.6;
  dirmap["ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"] = 3.36;
  
  dirmap["ttHTobb_M125_13TeV_powheg_pythia8"] =0.5058;
  dirmap["ttHToNonbb_M125_13TeV_powheg_pythia8"] =0.5058;
  dirmap["GluGlu_HToMuMu_M125_13TeV_powheg_pythia8"] =0.00970632;   
  dirmap["VBF_HToMuMu_M125_13TeV_powheg_pythia8"] =0.000828308;
  
  dirmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] =831.76;
  dirmap["TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] =831.76 ;
  dirmap["TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] =0.2043;
  dirmap["TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] =0.4062;
  dirmap["TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] =0.2529 ;
  dirmap["TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] =0.5297;
  
  dirmap["WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] =61526.7;

  dirmap["WW_TuneCUETP8M1_13TeV-pythia8"] =113.826;
  dirmap["WZ_TuneCUETP8M1_13TeV-pythia8"] =47.13;
  dirmap["ZZ_TuneCUETP8M1_13TeV-pythia8"] =16.91;

  dirmap["ZZTo4L_13TeV_powheg_pythia8"] = 1.256;
  dirmap["ZZTo4L_13TeV-amcatnloFXFX-pythia8"] =1.212 ;
  dirmap["ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8"] = 3.22;
  dirmap["ZZTo2L2Nu_13TeV_powheg_pythia8"] = 0.564;
  dirmap["WWTo2L2Nu_13TeV-powheg"] = 12.178;
  dirmap["WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8"] = 5.595;
  dirmap["WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8"] = 4.42965;
  dirmap["WZJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 5.26;
  dirmap["WpWpJJ_EWK_TuneCUETP8M1_13TeV-madgraph-pythia8"] = 0.02064;
  dirmap["WpWpJJ_QCD_TuneCUETP8M1_13TeV-madgraph-pythia8"] = 0.01538;
  dirmap["WW_DoubleScattering_13TeV-pythia8"] = 1.64;
  dirmap["WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8"] = 0.05565;
  
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
  dirmap["QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] =54120000*0.002;
  dirmap["QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8"] =162060000*0.0016;
  dirmap["QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] =108000000*0.000225 ;
  dirmap["QCD_Pt_20to30_bcToE_TuneCUETP8M1_13TeV_pythia8"] =557627000*0.00059;
  dirmap["QCD_Pt_30to80_bcToE_TuneCUETP8M1_13TeV_pythia8"] =159068000*0.00255;
  dirmap["QCD_Pt_80to170_bcToE_TuneCUETP8M1_13TeV_pythia8"] =3221000*0.01183;
  dirmap["QCD_Pt_170to250_bcToE_TuneCUETP8M1_13TeV_pythia8"] =105771*0.02492;
  dirmap["QCD_Pt_250toInf_bcToE_TuneCUETP8M1_13TeV_pythia8"] =21094.1*0.03375;

  dirmap["GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] = 137751*0.001587;
  dirmap["GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8"] = 16792*0.0514;
  dirmap["TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8"] = 3.697;
  dirmap["WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = 405.271 ;
  dirmap["ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = 117.864 ;
  dirmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaleup-pythia8"] = 831.76;
  dirmap["TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-scaledown-pythia8"] = 831.76;
  dirmap["TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8"]=831.76;
  dirmap["TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8"]=831.76;
  dirmap["TT_TuneCUETP8M1_13TeV-powheg-pythi8"]=831.76;

  
  lqmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY50plus_MCatNLO";
  lqmap["DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8"] = "DY10to50_MCatNLO";
  lqmap["DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"] = "DY50plus_madgraph";
  lqmap["ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbar_Powheg";
  lqmap["ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_t_Powheg";
  lqmap["ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tbarW_Powheg";
  lqmap["ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1"] ="singletop_tW_Powheg";
  lqmap["ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1"] = "singletop_s_mcatnlo";
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
    
    if(number_events_processed ==0 ) continue;
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
    lumi_file <<  "SK" << mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " /data2/CatNtuples/" + string(version.Data()) +"/SKTrees/MC/" << mit2->second << "/" <<endl;
  }

  
  lumi_file << "" << endl;
  lumi_file << "" << endl;
  lumi_file << "#### Single lepton skims: SKTrees" << endl;
  for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
    std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
    std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
    lumi_file <<  "SK" << mit2->second << "_dilep  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " /data2/CatNtuples/" + string(version.Data()) +"/SKTrees/MCDiLep/" <<  mit2->second << "/" <<endl;
  }
  
  string lfile2 =  "/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_" + string(version.Data()) + ".txt";
  TSystem* g;
  //  int test = g->Exec(("mv " + lfile + " > " + lfile2).c_str());

  cout << "mv " + lfile + " > " + lfile2 << endl;
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
