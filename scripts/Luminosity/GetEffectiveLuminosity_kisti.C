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

#include <algorithm>


#include <unistd.h>

using namespace std;

#include <map>

#include "SampleMap_kisti.C"

float GetEventsProcessed(std::string file);
float GetEventsPassed(std::string file);
float GetSumWeights(std::string filename);

map<TString, Double_t> map_lumi;
map<TString, Double_t> neventmap;
map<TString, Double_t> n_w_eventmap;
void GetEffectiveLuminosity_kisti(TString path_of_list,  TString tag,TString version="") {
  
  bool debug = true;
  map_lumi.clear();
  neventmap.clear();
  n_w_eventmap.clear();
  std::vector<TString> missing_samples;
  std::vector<TString> missing_samples2;

  cout << "path_of_list = " << path_of_list << endl;
  cout << "tag =  " << tag << endl;
  cout << "version = " << version << endl;
  
  
  bool NewList(true);
  if (path_of_list.Contains(string(getenv("LQANALYZER_DATASET_DIR")) +"/ca")) NewList=false;

  if (NewList) cout << "Not a new list " << endl;
  else cout <<"New list" << endl;

  if(CheckMaps(path_of_list)) return;
  TString def_version = TString(getenv("CATVERSION"));
  if(!version.Contains("v8") ) version = def_version;

  map<TString, TString> missing_map;
  vector<TString> vec_available ;
  if(!NewList){
    missing_map= GetMissingMap(version,path_of_list);
    vec_available = GetAvailableMap(version,path_of_list);
  }

  cout << "GetEffectiveLuminosity: Using file: " << path_of_list << " @ " << endl;
  map<TString, TString> datasets =  GetDatasetNames(version,path_of_list);
  
  
  map<TString, Double_t> dirmap = GetXSecMap2016(path_of_list); 
  map<TString, TString> lqmap = GetLQMap2016(path_of_list);
  map<TString, TString> trilepmap = GetTriLepMap2016(path_of_list);
  
  TString analysisdir = TString(getenv("HOSTNAME"));
  bool cluster = false;
  
  if(analysisdir.Contains("cmscluster.snu.ac.kr")) cluster=true;
  
  for(std::map<TString, Double_t>::iterator mit =dirmap.begin(); mit != dirmap.end();++mit){

    TString path_file="/xrootd/store/user/jalmond/cattoflat/MC/";

    ///   IF NEED LATER TO REDICE DISK SPACE CAN MAKE GENSKIM TO REPLACE CATTUPLE
    //    if(mit->first.Contains("amcatnlo")) path_file="/data2/DATA/cattoflat/genskim/";
      
    TString dir = "ls "+path_file + version + "/"+ mit->first + "/*.root > inputlist_efflumi.txt";
      
    bool use_sum_genweight(false);
    cout << "Checking " << mit->first << endl;
    if(mit->first.Contains("amcatnlo")) use_sum_genweight=true;
    else if(mit->first.Contains("_Schannel_")){
      if(mit->first.Contains("HN")|| mit->first.Contains("HeavyNeutrino") || mit->first.Contains("Majorana")|| mit->first.Contains("WR") )  use_sum_genweight=true;
    }
    else if(mit->first.Contains("Zprime")){
      if(mit->first.Contains("HN")|| mit->first.Contains("HeavyNeutrino") || mit->first.Contains("Majorana")|| mit->first.Contains("WR") )  use_sum_genweight=true;
    }
    else if(mit->first.Contains("_Tchannel_")){
      if(mit->first.Contains("HeavyNeutrino") || mit->first.Contains("HNDilepton")  || mit->first.Contains("HN") || mit->first.Contains("Majorana") || mit->first.Contains("WR") )  use_sum_genweight=true;
      
    }

    else if(mit->first.Contains("eavyNeutrino_trilepton")){
      use_sum_genweight=true;
    }
    else if (mit->first.Contains("HeavyNeutrino")){
      use_sum_genweight=true;
    }
    else use_sum_genweight=false;
    
    if(use_sum_genweight) cout << "use_sum_genweight = true" << endl;
    cout << "Running " << dir << endl;
    system(dir.Data());
    
    cout << "Finished Running " << dir << endl;

    system("python fix_list.py -x inputlist_efflumi.txt");
    std::ifstream fin("inputlist_efflumi.txt");
    std::ifstream finbatch("inputlist_efflumi_batch.txt");
    std::string word;
    
    float number_events_processed(0.);
    float number_events_passed(0.);
    float sum_of_weights(0.);
    
    if(!use_sum_genweight)  continue;

    if(use_sum_genweight) {
      std::vector<std::string> filelist;
      while ( finbatch >> word ) {
	number_events_processed+= GetEventsProcessed(word);;
        number_events_passed+= GetEventsPassed(word);
	filelist.push_back(word);
      }
      if(number_events_processed ==0 ) {
	missing_samples.push_back(mit->first);
	missing_samples2.push_back(mit->second);
	continue;
      }
      
      
      TString command1 = "rm -r /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/" + mit->first;
      TString command2 = "mkdir /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first;
      TString command2b = "mkdir /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first + "/output/";
      
      cout << "Running " << command1.Data() << endl;
      system(command1.Data());
      cout << "Running " << command2.Data() << endl;

      system(command2.Data());
      cout << "Running " << command2b.Data() << endl;
      system(command2b.Data());
      
      if (mit->first.Contains("DY") || mit->first.Contains("TT")  || mit->first.Contains("WJetsToLNu")){
	for(unsigned int i=0; i < filelist.size(); i++){
	  std::string istr;
	  std::stringstream out;
	  out << i;
	  istr = out.str();
	  
	  string lqdir = getenv("LQANALYZER_DIR");
	  
	  ofstream outputFileSH;
	  cout << istr << endl;
	  if (i < 10){
	    outputFileSH.open(("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_00"+TString(istr)+".sh"));
	    cout << "/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_00"+TString(istr)+".sh" <<endl;
	  }
	  else if (i < 100){
	    outputFileSH.open(("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_0"+TString(istr)+".sh"));
	    cout << "/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_0"+TString(istr)+".sh" <<endl;
	  }
	  else{
	    outputFileSH.open(("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_"+TString(istr)+".sh"));
	    
	  }
	  outputFileSH << "root -l -b -q \'CountGenWeights.C(\"/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first+ "\",\""+ filelist.at(i)+"\",\""+ "hist" + TString(istr) +".root\")\' \n"  << endl;
	  
	}
      }
      else{
	ofstream outputFileSH;

	outputFileSH.open(("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_000.sh"));
	cout << "/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/RunJob_000.sh" <<endl;

	TString batchpath_file="root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/jalmond/cattoflat/MC/";

	TString filedir=batchpath_file + version + "/"+ mit->first;
	outputFileSH << "root -l -b -q \'CountGenWeights_sig.C(\"/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first+ "\",\""+ filedir +"\", "+filelist.size()+",\""+ "hist0.root\")\' \n"  << endl;
	
      }
    
      
      TString command4b="cp CountGenWeights*.C /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first ;
      system(command4b.Data());

      system("python make_batchfile.py -x /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/");
      
      
     
      
      ofstream outputFileJDS;
      outputFileJDS.open(("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/Run_submit.jds"));
      outputFileJDS << "executable = RunJob.sh"<< endl;
      outputFileJDS << "universe   = vanilla"<< endl;
      outputFileJDS << "arguments  = $(Process)"<< endl;
      outputFileJDS << "log = condor.log"<< endl;
      outputFileJDS << "getenv     = True"<< endl;
      outputFileJDS << "should_transfer_files = YES"<< endl;
      outputFileJDS << "when_to_transfer_output = ON_EXIT"<< endl;
      outputFileJDS << "output = job_$(Process).log"<< endl;
      outputFileJDS << "error = job_$(Process).err"<< endl;
      outputFileJDS << "accounting_group=group_cms"<< endl;
      outputFileJDS << "+SingularityImage = \"/cvmfs/singularity.opensciencegrid.org/opensciencegrid/osgvo-el6:latest\""<< endl;
      outputFileJDS << "+SingularityBind = \"/cvmfs, /cms, /share\""<< endl;
      outputFileJDS << "transfer_input_files = /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/"+TString(getenv("USER")) + "/"+mit->first+"/runFile.tar.gz"<< endl;
      outputFileJDS << "use_x509userproxy = true"<< endl;
      outputFileJDS << "transfer_output_remaps = \"hists.root = /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/"+TString(getenv("USER")) + "/"+mit->first+"/hists_$(Process).root\""<< endl;
      if (mit->first.Contains("DY") || mit->first.Contains("TT")|| mit->first.Contains("WJetsToLNu")){
	outputFileJDS << "queue "<< filelist.size()<< endl;
      }else{
	outputFileJDS << "queue 1" << endl;

      }
    
      


      system("python run_kisti_lumi.py -x /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/");

    }
  }
  for(std::map<TString, Double_t>::iterator mit =dirmap.begin(); mit != dirmap.end();++mit){

    TString path_file="/xrootd/store/user/jalmond/cattoflat/MC/";

    ///   IF NEED LATER TO REDICE DISK SPACE CAN MAKE GENSKIM TO REPLACE CATTUPLE                                                                                                                           
    //    if(mit->first.Contains("amcatnlo")) path_file="/data2/DATA/cattoflat/genskim/";                                                                                                                   

    TString dir = "ls "+path_file + version + "/"+ mit->first + "/*.root > inputlist_efflumi.txt";

    bool use_sum_genweight(false);
    cout << "Checking " << mit->first << endl;
    if(mit->first.Contains("amcatnlo")) use_sum_genweight=true;
    else if(mit->first.Contains("_Schannel_")){
      if(mit->first.Contains("HN")|| mit->first.Contains("HeavyNeutrino") || mit->first.Contains("Majorana")|| mit->first.Contains("WR") )  use_sum_genweight=true;
    }
    else if(mit->first.Contains("Zprime")){
      if(mit->first.Contains("HN")|| mit->first.Contains("HeavyNeutrino") || mit->first.Contains("Majorana")|| mit->first.Contains("WR") )  use_sum_genweight=true;
    }
    else if(mit->first.Contains("_Tchannel_")){
      if(mit->first.Contains("HeavyNeutrino") || mit->first.Contains("HNDilepton")  || mit->first.Contains("HN") || mit->first.Contains("Majorana") || mit->first.Contains("WR") )  use_sum_genweight=true;

    }

    else if(mit->first.Contains("eavyNeutrino_trilepton")){
      use_sum_genweight=true;
    }
    else if (mit->first.Contains("HeavyNeutrino")){
      use_sum_genweight=true;
    }
    else use_sum_genweight=false;

    if(use_sum_genweight) cout << "use_sum_genweight = true" << endl;
    cout << "Running " << dir << endl;
    system(dir.Data());

    cout << "Finished Running " << dir << endl;

    system("python fix_list.py -x inputlist_efflumi.txt");
    std::ifstream fin("inputlist_efflumi.txt");
    std::ifstream finbatch("inputlist_efflumi_batch.txt");
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
      while ( finbatch >> word ) {
        number_events_processed+= GetEventsProcessed(word);;
        number_events_passed+= GetEventsPassed(word);
        filelist.push_back(word);
      }
      if(number_events_processed ==0 ) {
        missing_samples.push_back(mit->first);
        missing_samples2.push_back(mit->second);
        continue;
      }

      if (mit->first.Contains("DY") || mit->first.Contains("TT")|| mit->first.Contains("WJetsToLNu")){

	cout << "Checking if job is complete...." << endl;
	bool jobComplete=false;
	int nsubmits=0;
	bool submit_override=false;
	while (!jobComplete){
	  jobComplete=true;
	  for(unsigned int i=0; i < filelist.size(); i++){
	    std::string istr;
	    std::stringstream out;
	    out << i;
	    
	    istr = out.str();
	    cout << "Checking /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist" + TString(istr) +".root" << endl;
	    std::ifstream infile("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist" + TString(istr) +".root");
	    if(!infile.good()) {
	      jobComplete=false;
	      if(nsubmits>100){
		cout << "File /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist" + TString(istr) +".root does not exist" << endl;  
		
		system("root -l -b -q \'CountGenWeights.C(\"/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first+ "\",\""+filelist.at(i)+"\",\""+ "hist" + TString(istr) +".root\")\'");
		submit_override=true;
	      }
	      sleep(5);
	      nsubmits++;
	      break;
	    }
	  }
	}
	
	if(submit_override)system("python check_kisti_lumi.py -x /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/");
      }
      else{
	for(unsigned int i=0; i < 1; i++){
          cout << "Checking if job is complete...." << endl;
          bool jobComplete=false;
          int nsubmits=0;
	  bool submit_override=false;
          while (!jobComplete){
            jobComplete=true;
	    for(unsigned int i=0; i < 1; i++){
	      std::string istr;
	      std::stringstream out;
              out << i;
	      
              istr = out.str();
              cout << "Checking /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist0.root" << endl;
	      std::ifstream infile("/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist0.root");
              if(!infile.good()) {
                jobComplete=false;
                if(nsubmits>100){
		  cout << "File /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first +"/output/hist" + TString(istr) +".root does not exist" << endl;
		  
		  
		  TString batchpath_file="root://cms-xrdr.sdfarm.kr:1094///xrd/store/user/jalmond/cattoflat/MC/";

		  TString filedir=batchpath_file + version + "/"+ mit->first;

                  system("root -l -b -q \'CountGenWeights_sig.C(\"/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first+ "\",\""+ filedir +"\", "+filelist.size()+"\",\""+ "hist0.root\")\' \n");
		  submit_override=true;
                }
                sleep(5);
                nsubmits++;
                break;
              }
            }
          }

          if(submit_override) system("python check_kisti_lumi.py -x /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+ mit->first+"/");

	}
      }// end of fast process  
    
      cout << "Job complete" << endl;

      
      TString command4 = "rm log/checkoutput.txt";
      TString command5= "ls   "+path_file + version + "/"+  mit->first + "/  > log/checkoutput.txt";
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
      if(debug){
	cout << "Number of files in "+path_file + version + "/"+  mit->first + "/ = " << counter << endl;

      }
      bool JobDone=false;
      while (JobDone==false){
	TString command6= "ls   /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"  +  mit->first + "/output/ > log/checkcounted.txt";
	system(command6.Data());
	
	TString filename_counted = "log/checkcounted.txt";
	ifstream name_countedfile(filename_counted.Data());
	int counter_counted=0;
	while(!name_countedfile.eof()) {
	  string filen;
	  name_countedfile >> filen;
	  if(TString(filen).Contains(".root"))counter_counted++;
	}
	if (mit->first.Contains("DY") || mit->first.Contains("TT")|| mit->first.Contains("WJetsToLNu")){
	  if(counter_counted == counter) JobDone=true;
	}
	else JobDone=true;
      }
      TString haddcommand = "hadd   /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first + "/output/Output.root  /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first + "/output/*.root ";
      if (mit->first.Contains("DY") || mit->first.Contains("TT")|| mit->first.Contains("WJetsToLNu")){
	system(haddcommand.Data());
      }
      else{
	system("mv /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first + "/output/hist0.root /cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first + "/output/Output.root");
      }
      TFile* file = TFile::Open(( "/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first + "/output/Output.root").Data());
      TH1F*  SumWCounter = (TH1F*) (file ->Get("sumweight"));
      sum_of_weights = SumWCounter->Integral();
    }

    if(number_events_processed ==0 ) continue;
    fin.close();
       
    float lumi = number_events_processed / mit->second;
    if(use_sum_genweight) lumi = sum_of_weights / mit->second;
    

    std::cout.precision(10);
    
    //if(debug){
      std::cout << "/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/Lumi/" + TString(getenv("USER")) + "/"+mit->first << "    nevents =  " << number_events_processed << " sum of weights =  " << sum_of_weights << " eff lumi = " << lumi <<std::endl;
      //}

    system("rm inputlist_efflumi.txt");
    
    map_lumi[ mit->first] = lumi;
    neventmap[ mit->first]=number_events_processed;
    n_w_eventmap[mit->first]=sum_of_weights;
  } 

  
  ofstream lumi_file;
  string lfile =  "datasets_snu_CAT_mc_" + string(version.Data()) + string(tag)+".txt";
  
  cout << "Updating " << lfile << endl;
  if(cluster) lfile =  "datasets_snu_cluster_CAT_mc_" + string(version.Data()) + ".txt";

  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield); 
  lumi_file.precision(5);


  if(!NewList){
    lumi_file << "########################" << endl;
    lumi_file << "### CATTUPLES ########## "  << endl;
    lumi_file << "#######################" << endl;
    lumi_file << "" << endl;
    lumi_file << "" << endl;
    lumi_file << "kisti_cat /xrootd/store/user/jalmond/" << endl;
    lumi_file << "tamsa_cat /data7/DATA/" << endl;
  

    lumi_file << "#######################################################################################################################################" << endl;
    lumi_file << "# sample     Nevents  Sum(GenWeights)  xsec*Eff   Effective lumi    LocalPath #####################################################################################" << endl;
    lumi_file << "#######################################################################################################################################" << endl;
    lumi_file << "" << endl;
    lumi_file << "" << endl;
    lumi_file << "#### CATTuples" << endl;
    for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
      std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);    
      std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);    
      std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);    
      std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);    
      lumi_file <<  mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << "  cattoflat/MC/" << version <<"/"  << mit->first << "/" <<endl;      
    }
    
    lumi_file << "" << endl;
    lumi_file << "" << endl;
    lumi_file << "#### Single_lepton_skims:_SKTrees" << endl;
    for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
      std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
     lumi_file <<  "SK" << mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " CatNtuples/" + string(version.Data()) +"/SKTrees/MC/" << mit2->second << "/" <<endl;
      
    }

    lumi_file << "" << endl;
    lumi_file << "##################################################################" << endl;
    lumi_file << "#### Missing/Not produced samples in this version are listed below " << endl;
    lumi_file << "#### Missing : means miniAOD not available " << endl;
    lumi_file << "#### Available: means miniAOD/catuples available but no flatcatuples/sktree made. " << endl;
    lumi_file << "##################################################################" << endl;
    
    for(map<TString, TString>::iterator it = missing_map.begin(); it!= missing_map.end(); it++){
      lumi_file << "Missing: " << it->first << "   " << it->second << endl;
    }
    for(vector<TString>::iterator it= vec_available.begin(); it!= vec_available.end(); it++){
      lumi_file <<"Available[not produced]: " << *it << endl;
    }
    
    
    lumi_file << "" << endl;
    lumi_file << "##################################################################" << endl;
    lumi_file << "#### FULL Name of MINIAODS " << endl;
    lumi_file << "##################################################################" << endl;
    
    for(map<TString, TString>::iterator it = datasets.begin(); it!= datasets.end(); it++){
      lumi_file << "DATASET: " << it->first << "   " << it->second << endl;
    }
    
    lumi_file << "################################################################ " << endl;
    lumi_file << "#### Private produced samples : Not made in batch at kisti" << endl;
    lumi_file << "##################################################################" << endl;
  }
  else{
    for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
      std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
      lumi_file <<  mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << "  cattoflat/MC/" << version <<"/"  << mit->first << "/" <<endl;
      
    }

    for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
      std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);
      lumi_file <<  "SK" << mit2->second << "  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " CatNtuples/" + string(version.Data()) +"/SKTrees/MC/" << mit2->second << "/" <<endl;

    }
    for(std::map<TString, Double_t>::iterator mit =map_lumi.begin(); mit != map_lumi.end();++mit){
      std::map<TString, TString>::iterator mit2 = lqmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit3 = dirmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit4 = neventmap.find(mit->first);
      std::map<TString, Double_t>::iterator mit5 = n_w_eventmap.find(mit->first);

      lumi_file <<  "SK" << mit2->second << "_dilep  " << mit4->second << " " << mit5->second << " " <<  mit3->second <<" "  << mit->second << " CatNtuples/" + string(version.Data()) +"/SKTrees/MCDiLep/" <<  mit2->second << "/" <<endl;
    }
  }

  string lqdir = getenv("LQANALYZER_DIR");
  string lfile2 =  lqdir + "/LQRun/txt/datasets_snu_CAT_mc_" + string(version.Data()) + ".txt";


  if(cluster) lfile2 =  lqdir + "/LQRun/txt/Cluster/datasets_snu_cluster_CAT_mc_" + string(version.Data()) + ".txt";

  TString user = TString(getenv("USER"));
  if(!cluster)gSystem->Exec(("cp " + lfile + "  " + getenv("LQANALYZER_DATASETFILE_DIR")+ "/").c_str()); 
  else gSystem->Exec(("cp " + lfile + "  /data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/").c_str());

  //gSystem->Exec(("mv " + lfile +" " + lfile2).c_str());

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

  //cout << "GetSumWeights :: " << endl;
  TDirectory * dir = (TDirectory*)file->Get("ntuple");
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
  //cout << "sum_weight = " << sum_weight << endl;
  return sum_weight;
}
