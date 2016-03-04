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

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);
float GetSumWeights(std::string filename);

map<TString, Double_t> map_lumi;
map<TString, Double_t> neventmap;
map<TString, Double_t> n_w_eventmap;
void GetEffectiveLuminosity(TString version="") {
  
  map_lumi.clear();
  neventmap.clear();
  n_w_eventmap.clear();
  std::vector<TString> missing_samples;
  std::vector<TString> missing_samples2;

  if(CheckMaps()) return;
  TString def_version = TString(getenv("CATVERSION"));
  if(!version.Contains("v7") ) version = def_version;
  
  map<TString, TString> missing_map= GetMissingMap(version);
  vector<TString> vec_available = GetAvailableMap(version);

  map<TString, TString> datasets =  GetDatasetNames(version);
 
    
  map<TString, Double_t> dirmap = GetXSecMap(); 
  map<TString, TString> lqmap = GetLQMap();
  

  for(std::map<TString, Double_t>::iterator mit =dirmap.begin(); mit != dirmap.end();++mit){
    

    
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
    
    if(!use_sum_genweight) {
      while ( fin >> word ) {
	number_events_processed+= GetEventsProcessed(word);
	number_events_passed+= GetEventsPassed(word);
      }
      sum_of_weights = number_events_processed;
      if(number_events_processed ==0 ) {
	missing_samples.push_back(mit->first);
	missing_samples2.push_back(mit->second);
	continue;
      }
    }
    else{
      std::vector<std::string> filelist;
      while ( fin >> word ) {
	number_events_processed+= GetEventsProcessed(word);
        number_events_passed+= GetEventsPassed(word);
	filelist.push_back(word);
      }
      if(number_events_processed ==0 ) {
	missing_samples.push_back(mit->first);
	missing_samples2.push_back(mit->second);
	continue;
      }
      TString command1 = "rm -r "+ mit->first;
      TString command2 = "mkdir "+ mit->first;
      TString command2b = "mkdir "+ mit->first + "/output/";

      system(command1.Data());
      system(command2.Data());
      system(command2b.Data());
      
      for(unsigned int i=0; i < filelist.size(); i++){
      std::string istr;
      std::stringstream out;
      out << i;
      istr = out.str();
      TString command3 = "root -l -b -q \'CountGenWeights.C(\""+mit->first+ "\",\""+filelist.at(i)+"\",\""+ "hist" + TString(istr) +".root\")\' &";
      TString command3b = "root -l -b -q \'CountGenWeights.C(\""+mit->first+ "\",\""+filelist.at(i)+"\",\""+ "hist" + TString(istr) +".root\")\' ";
	cout << command3 << endl;
	if(i==0) system(command3.Data());
	else if(i%10) system(command3.Data());
	else system(command3b.Data());
      }
      
      
      TString command4 = "rm log/checkoutput.txt";
      TString command5= "ls   /data2/DATA/cattoflat/MC/" + version + "/"+ mit->first + "/  > log/checkoutput.txt";
      system(command4.Data());
      system(command5.Data());
      TString filename_fs = "log/checkoutput.txt";
      ifstream name_file(filename_fs.Data());
      int counter=0;
      while(!name_file.eof()) {
	string filen;
	name_file >> filen;
	if(TString(filen).Contains(".root"))counter++;
      }
      cout << "Number of files in /data2/DATA/cattoflat/MC/" + version + "/"+ mit->first + "/ = " << counter << endl;
     
      bool JobDone=false;
      while (JobDone==false){
	TString command6= "ls  "  + mit->first + "/output/ > log/checkcounted.txt";
	system(command6.Data());
	
	TString filename_counted = "log/checkcounted.txt";
	ifstream name_countedfile(filename_counted.Data());
	int counter_counted=0;
	while(!name_countedfile.eof()) {
	  string filen;
	  name_countedfile >> filen;
	  if(TString(filen).Contains(".root"))counter_counted++;
	}
	if(counter_counted == counter) JobDone=true;
      }
      TString haddcommand = "hadd  " + mit->first + "/output/Output.root " +  mit->first + "/output/*.root ";
      system(haddcommand.Data());
      TFile* file = TFile::Open((mit->first + "/output/Output.root").Data());
      TH1F*  SumWCounter = (TH1F*) (file ->Get("sumweight"));
      sum_of_weights = SumWCounter->Integral();
    }

    if(number_events_processed ==0 ) continue;
    fin.close();
       
    float lumi = number_events_processed / mit->second;
    if(use_sum_genweight) lumi = sum_of_weights / mit->second;
    
    std::cout.precision(10);
    std::cout <<mit->first << "    nevents =  " << number_events_processed << " sum of weights =  " << sum_of_weights << " eff lumi = " << lumi <<std::endl;
    
    system("rm inputlist.txt");
    system(("rm -r " +  mit->first).Data());
    
    map_lumi[mit->first] = lumi;
    neventmap[mit->first]=number_events_processed;
    n_w_eventmap[mit->first]=sum_of_weights;
  } 

  
  ofstream lumi_file;
  string lfile =  "datasets_snu_CAT_mc_" + string(version.Data()) + ".txt";
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
  

  lumi_file << "" << endl;
  lumi_file << "##################################################################" << endl;
  lumi_file << "#### Missing/Not produced samples in this version are listed below " << endl;
  lumi_file << "#### Missing : means miniAOD not available " << endl;
  lumi_file << "#### Available: means miniAOD/catuples available but no sktree made. " << endl;
  lumi_file << "##################################################################" << endl;

  //map<TString, TString> missing_map= GetMissingMap();
  //vector<TString> vec_available = GetAvailableMap();

  for(map<TString, TString>::iterator it = missing_map.begin(); it!= missing_map.end(); it++){
    lumi_file << "Missing: " << it->first << "   " << it->second << endl;
  }
  for(vector<TString>::iterator it= vec_available.begin(); it!= vec_available.end(); it++){
    lumi_file <<"Available[not produced]: " << *it << endl;
  }
  

  lumi_file << "" << endl;
  lumi_file << "##################################################################" << endl;
  lumi_file << "#### FULL Name of MINIAODS 
  lumi_file << "##################################################################" << endl;

  for(map<TString, TString>::iterator it = datasets.begin(); it!= datasets.end(); it++){
    lumi_file << "DATASET: " << it->first << "   " << it->second << endl;
  }


  lumi_file << "################################################################ " << endl;
  lumi_file << "#### Private produced samples : Not made in batch at kisti" << endl;
  lumi_file << "##################################################################" << endl;
  

  string lqdir = getenv("LQANALYZER_DIR");
  string lfile2 =  lqdir + "/LQRun/txt/datasets_snu_CAT_mc_" + string(version.Data()) + ".txt";

  TString user = TString(getenv("USER"));
  if(user.Contains("jalmond"))  
    gSystem->Exec(("cp " + lfile + "  /data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/").c_str());


  gSystem->Exec(("mv " + lfile +" " + lfile2).c_str());

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
