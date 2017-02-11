#include <utility>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>
#include <TStyle.h>
#include "TCanvas.h"
#include "TLegend.h"
#include <vector>
#include <fstream>
#include <iostream>     // std::cout
#include <sstream>  

using namespace std;

TH1F* MakeMonthHist(TString mon, int nday);

void CheckJobStatistics(){

  std::vector<std::pair<TString,TString> > monthyears;
  monthyears.reserve(2);
  std::pair<TString,TString> pair1= std::make_pair("2016","Nov");
  monthyears.push_back(pair1);
  
  for(std::vector<std::pair<TString,TString> >::iterator it = monthyears.begin(); it != monthyears.end(); it++){
    
    ifstream muonselconfig(("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/JobSummary"+it->second+"_"+ it->first+".txt").Data());
    if(!muonselconfig) {
      cerr << "Did not find, exiting ..." << endl;
      exit(EXIT_FAILURE);
    }
    
    TH1F * h_dec = MakeMonthHist("Dec",31);
    vector<TString> daylist;
    daylist = GetDays();

    string statline;
    vector<string> userlist;
    /// loop iver stat logger
    while(getline(muonselconfig,statline) ){
      if (!TString(statline).Contains("job_complete= True")) continue;
      /// remove inconplete jobs

      vector<string> splitline;
      std::istringstream is(statline);
      string tmp;
      while(is >> tmp){ 
	splitline.push_back(tmp);
      }
      /// Fill line into sep strings
      
      bool userexists=false;
      if (splitline.size() > 0){
	for(unsigned int j=0 ; j < userlist.size(); j++){
	  if (userlist.at(j) == splitline.at(0))  userexists=true;
	}
      }

      if (!userexists){
	userlist.push_back(splitline[0]);
      }
      if (splitline.size() != 39 ) cout <<  "Fail: " <<   statline << endl;
      
    }
    
    for(unsigned int i=0; i < userlist.size() ; i++){
      cout << "User = "<< userlist.at(i) << endl;
      vector<string> codelist;
      muonselconfig.clear();
      muonselconfig.seekg(0,muonselconfig.beg);
      while(getline(muonselconfig,statline) ){
	if (!TString(statline).Contains("job_complete= True")) continue;
	vector<string> splitline;
	std::istringstream is(statline);
	string tmp;
	while(is >> tmp){
	  splitline.push_back(tmp);
	}
	
	if (splitline.size() != 39 ) continue;
	
	bool correctuser=false; 
	if (userlist.at(i) == splitline.at(0))  correctuser=true;
	if (correctuser){
	  bool newcode=true;
	  string  codename=splitline.at(1);
	  for(unsigned int k=0; k < codelist.size() ; k++){
	    if(codelist.at(k) == splitline.at(1)) newcode=false;
	  }
	  if(newcode)codelist.push_back(codename);
	}
      }
      for(unsigned int k=0; k < codelist.size() ; k++){
	cout << "Name code = " << codelist.at(k) << endl;
	muonselconfig.clear();
	muonselconfig.seekg(0,muonselconfig.beg);
	while(getline(muonselconfig,statline) ){
	  if (!TString(statline).Contains("job_complete= True")) continue;
	  vector<string> splitline;
	  std::istringstream is(statline);
	  string tmp;
	  while(is >> tmp){
	    splitline.push_back(tmp);
	  }

	  if (splitline.size() != 39 ) continue;
	  if (userlist.at(i) == splitline.at(0)) {
	    if( codelist.at(k) == splitline.at(1)){
	      
	      
	    }
	  } 
	  
	  
	  
	}
	
      }
    }
  }
  return;
}

vector<TString> GetList(){

}


TH1F* MakeMonthHist(TString mon, int nday){
  
  TH1F* h = new TH1F* (mon.Data(), mon.Data(), nday, 0., float(nday));
  h->GetXaxis()->SetBinTitle(1,"1st");
  
  return h;
}




  



