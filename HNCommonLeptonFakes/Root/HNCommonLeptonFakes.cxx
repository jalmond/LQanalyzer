// STL include(s):                                                                                                                                                       
#include <stdexcept>
#include <sstream>
#include <iostream>


// ROOT include(s):                                                                                                                                                                
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TDirectory.h"
#include "TLorentzVector.h"
#include "TH2F.h"
#include "TEfficiency.h"

/// local includes
#include "HNCommonLeptonFakes/HNCommonLeptonFakes.h"

using namespace std;


TDirectory* HNCommonLeptonFakes::getTemporaryDirectory(void) const
{
  //                                                                                                                                                                                
  // Create a unique directory in memory to hold the histograms:                                                                                                                      //                                                                                                                                                                                 
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());
    
  }

  return tempDir;
}


void HNCommonLeptonFakes::InitialiseFake(){
  
  bool failedinitialisation=false;

  cout << "HNCommonLeptonFakes : Initializing" << endl;

  // Remember which TDirectory the system is in at the beginning of the method:                                                                                                      
  TDirectory* origDir = gDirectory;
  
  /// List files with fake rates

  string lqdir = getenv("LQANALYZER_DIR");

  //  TFile* file_fake  = TFile::Open( (lqdir + "/data/rootfiles/FakeRate2807.root").c_str());
  //CheckFile(file_fake);



  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();

 

  if(failedinitialisation){
    cout << "Not all histograms could be initialised, this is a bug so am exiting" << endl;
  }
  else {

    cout << "WRHNCommonLeptonFakes : Initialsation was successful " << endl;
    cout << "WRHNCommonLeptonFakes : Default setting in MeV" <<  endl;
    cout << "WRHNCommonLeptonFakes : To Use GeV set third argument of constructor true" << endl;
  }

  //  file_fake->Close();
  // delete file_fake;
  


  // Now we can close the file:   
  origDir->cd();
  

  return;
}


/// Constructor
HNCommonLeptonFakes::HNCommonLeptonFakes(std::string path,bool usegev){

  path_to_root_files = path;
  useGeV = usegev;
  InitialiseFake();
  m_debug=false;
  NullTotals();
}


/// Destructor
HNCommonLeptonFakes::~HNCommonLeptonFakes() {
  closefile();   
  CutHists.clear();
}



void HNCommonLeptonFakes::ApplyFakeSystematic(int type){
 
  //  if(type==0)cout << "HNCommonLeptonFakes : Running in default mode f [no systematic applied] " << endl;
  //  if(type==1)cout << "HNCommonLeptonFakes : Applying systematic f + sigma" << endl;
  //  if(type==-1)cout << "HNCommonLeptonFakes : Applying systematic f - sigma" << endl;
  
  fsys=type;
}

void HNCommonLeptonFakes::ApplyRealSystematic(int type ){
  
  //if(type==0)cout << "HNCommonLeptonFakes : Running in default mode r [no systematic applied] " << endl;
  //if(type==1)cout << "HNCommonLeptonFakes : Applying systematic r + sigma " << endl;
  //if(type==-1)cout << "HNCommonLeptonFakes : Applying systematic r - sigma " << endl;
  
  rsys=type;
}



float HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons,  bool isel1tight, bool isel2tight, TString cut, int eventtype, int nbjet){
  return get_dilepton_ee_eventweight( electrons, 0., isel1tight, isel2tight, cut, eventtype, nbjet);
}
    

float HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, float ht,  bool isel1tight, bool isel2tight, TString cut, int eventtype, int nbjet){
  
  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }

  if(ht < 40.) ht = 40.;
  if(ht > 300.) ht = 250.;
  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();

  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;

  
  float _el1_eta=fabs(electrons.at(0).Eta());
  float _el2_eta=fabs(electrons.at(1).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }

  bool highpt = false; 
  if(cut.Contains("mc")){
    if(_el1_pt > 60.) _el1_pt = 59.;
    if(_el2_pt > 60.) _el2_pt = 59.;
  }
  else{
    if(_el2_pt > 100.) highpt = true;
    if(_el1_pt > 60.) _el1_pt = 59.;
    if(_el2_pt > 60.) _el2_pt = 59.;
  }
  float fr1(0.),fr2(0.),r1(0.),r2(0.);
  
  r1=1.;
  r2=1.;
  

  TString fcut = cut;
  TString cut1 = fcut;
  TString cut2 = fcut;
  if(cut.Contains("mc")){
    if(fcut.Contains("mc") && fcut.Contains("_ht_") ){
      _el1_pt = ht;
      _el2_pt = ht;
    }
    
    if(fcut.Contains("mc") && fcut.Contains("HT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      _el1_pt = ht;
      _el2_pt = ht;
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")) cut1 = "mc_" + jetcut +"_cb_" + region;
      else cut1 = "mc_" + jetcut+  "_nocb_" + region;
      if(cut2.Contains("cl2")) cut2 = "mc_" + jetcut +"_cb_" + region;
      else cut2 = "mc_" + jetcut+  "_nocb_" + region;
    }
    if(fcut.Contains("mc") && fcut.Contains("PT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")){
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else cut1 = "mc_" + jetcut+  "_nocb_pt_" + region;
      if(cut2.Contains("cl2")) {
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else cut2 = "mc_" + jetcut+  "_nocb_pt_" + region;
    }
    
    if(fcut.Contains("mc") && fcut.Contains("BT") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")){
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else {
	if(cut1.Contains("nob")) cut1 = "mc_" + jetcut+  "nob_nocb_" + region;
	else cut1 = "mc_" + jetcut+  "b_nocb_" + region;
      }
      if(cut2.Contains("cl2")) {
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else{
	if(cut2.Contains("nob")) cut2 = "mc_" + jetcut+  "nob_nocb_" + region;
	else cut2 = "mc_" + jetcut+  "b_nocb_" + region;
      }  
    }
    
    
    if(fcut.Contains("mc") && fcut.Contains("ST") ){
      TString jetcut="";
      if (fcut.Contains("20")) jetcut = "20";
      if (fcut.Contains("30")) jetcut = "30";
      if (fcut.Contains("40")) jetcut = "40";
      if (fcut.Contains("60")) jetcut = "60";
      TString region="";
      if (fcut.Contains("loosereg1")) region = "loosereg1";
      else region = "loosereg2";
      
      if(cut1.Contains("cl1")) {
	cut1 = "mc_" + jetcut +"_cb_" + region;
	_el1_pt = ht;
      }
      else {
	
	TString bjet = "";
	if(cut1.Contains("0bjet" )) bjet = "_0bjet"; 
	else if(cut1.Contains("bjet" )) bjet = "_bjet"; 
	if(ht < 100.) cut1 = "mc_" + jetcut+ bjet + "_ht1_nocb_" + region;
	else  cut1 = "mc_" + jetcut+  bjet + "_ht3_nocb_" + region;
	
      }
      if(cut2.Contains("cl2")){
	cut2 = "mc_" + jetcut +"_cb_" + region;
	_el2_pt = ht;
      }
      else {
	TString bjet = "";
	if(cut2.Contains("0bjet" )) bjet = "_0bjet";
	else if(cut2.Contains("bjet" )) bjet = "_bjet";
	if(ht < 100.) cut2 = "mc_" + jetcut+ bjet + "_ht1_nocb_" + region;
	else  cut2 = "mc_" + jetcut+  bjet + "_ht3_nocb_" + region;
	
      }
    }
  }
  
  else{
    /// DATA FAKE RATES

    if(fcut.Contains("method1")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      cut1  = "pt_eta_" + JetPt + "_" + reg;
      cut2  = "pt_eta_" + JetPt + "_" + reg;
    }
    else     if(fcut.Contains("method2")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      

      _el1_pt = ht;
      _el2_pt = ht;
      cut1  = "ht_eta_"+ JetPt+ "_" +reg;
      cut2  = "ht_eta_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method3")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";
      else{
	if(_el1_eta > 1.5 && _el1_pt < 20.) _el1_pt = 21.; 
	if(_el1_eta > 1.5 && _el1_pt > 60.) _el1_pt = 51.;
	if(_el2_eta > 1.5 && _el2_pt < 20.) _el2_pt = 21.;
	if(_el2_eta > 1.5 && _el2_pt > 60.) _el2_pt = 51.;

      }
      
      
      cut1  = bjet+ "_pt_eta_"+ JetPt+ "_" +reg;
      cut2  = bjet+ "_pt_eta_"+ JetPt+ "_" +reg;
    }
    
    else     if(fcut.Contains("method4")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      if(fcut.Contains("cl1")) {
	cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut1  = "pt_eta_nocb_"+ JetPt+ "_" +reg;
      
      if(fcut.Contains("cl2")) {
	cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = "pt_eta_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method5")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      _el1_pt = ht;
      _el2_pt = ht;

      if(fcut.Contains("cl1")) {
	cut1  = "ht_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut1  = "ht_eta_nocb_"+ JetPt+ "_" +reg;
      
      if(fcut.Contains("cl2")) {
        cut2  = "ht_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = "ht_eta_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method6")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";
      else{
	if(_el1_eta > 1.5 && _el1_pt < 20.) _el1_pt = 21.;
        if(_el1_eta > 1.5 && _el1_pt > 60.) _el1_pt = 51.;
        if(_el2_eta > 1.5 && _el2_pt < 20.) _el2_pt = 21.;
        if(_el2_eta > 1.5 && _el2_pt > 60.) _el2_pt = 51.;
      }
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
	cut1  = bjet+ "_pt_eta_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = bjet + "_pt_eta_nocb_"+ JetPt+ "_" +reg;
    }
    
    else     if(fcut.Contains("method7")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 150) htbin = "ht3";
      
      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";

      if(_el1_pt > 45. && _el1_pt > 60 && ht > 100.) _el1_pt = 44.;
      if(_el2_pt > 45. && _el2_pt > 60 && ht > 100.) _el2_pt = 44.;
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
        cut1  = "pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  =  "pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method8")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 150) htbin = "ht3";

      TString bjet = "bjet";
      if(fcut.Contains("0bjet")) bjet = "0bjet";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      if(fcut.Contains("cl1")) {
        cut1  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else {
        cut1  = bjet + "_pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
      }
      if(fcut.Contains("cl2")) {
        cut2  = "pt_eta_cb_"+ JetPt+ "_" +reg;
      }
      else cut2  = bjet + "_pt_eta_" + htbin + "_nocb_"+ JetPt+ "_" +reg;
    }
    else     if(fcut.Contains("method9")){
      TString reg = "";
      if(fcut.Contains("looseregion1")) reg = "looseregion1";
      else reg = "looseregion2";

      TString htbin = "ht1";
      if( ht > 150) htbin = "ht3";

      TString JetPt = "";
      if(fcut.Contains("20")) JetPt = "20";
      if(fcut.Contains("30")) JetPt = "30";
      if(fcut.Contains("40")) JetPt = "40";
      if(fcut.Contains("60")) JetPt = "60";
      
      cut1  = "pt_eta_" + htbin + "_" +JetPt+ "_" +reg;
      cut2  = "pt_eta_" + htbin + "_"+ JetPt+ "_" +reg;
    }
  }


  if(fcut.Contains("method1")){
    if(nbjet ==0) {
      if( _el1_eta < 1.5) {
	if(_el1_pt > 45.) _el1_pt = 64.;
      }
    }
  }
  
  fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut1);
  fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut2);
  
  float fr1_err=  getFakeRate_electronEta(1,_el1_pt, _el1_eta,cut1);
  float fr2_err=  getFakeRate_electronEta(1,_el2_pt, _el2_eta,cut2);

  //if(!isel1tight) cout << "fr1 = " << fr1 << " " << cut1<< " " << _el1_pt << " " << _el1_eta << endl;
  //if(!isel2tight) cout << "fr2 = " << fr2 << " " <<  cut2 << " " << _el2_pt << " " << _el2_eta << endl;

  if(nbjet ==0) {
    if(highpt){
      fr1 *= 2.5;
      fr2 *= 2.5;
    }
  }
  else{
  }
  
  //if(nbjet != 0) {
  // fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"bjet_pt_eta_40_looseregion2");
  //  fr2= getFakeRate_electronEta(0,_el2_pt, _el2_eta,"bjet_pt_eta_40_looseregion2");

  //}

  
  if(fr1 == 0.)  fr1 = 0.05;
  if(fr2 == 0.)  fr2 = 0.05;
  
  if(_el1_pt < 20.){
    if(fabs(_el1_eta) > 1.5){
      if(cut1.Contains("fake_eff_mc_60_bjet_ht3_loosereg1")) cout << "mod: fake_eff_mc_60_bjet_ht3_loosereg1 : fr = " << fr1 << endl;
    }
  }
  

  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(fr1_err,fr1,fr2_err,fr2, isel1tight, isel2tight, eventtype);

  //if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  //if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }

  
  return ev_weight;
  }

  
float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, bool isel1tight, bool isel2tight, TString cut, int eventtype, bool user1){

  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();

  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;


  float _el1_eta=fabs(electrons.at(0).Eta());
  float _el2_eta=fabs(electrons.at(1).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }

  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_el2_pt > 100.) _el2_pt = 99.;

  float fr1(0.),fr2(0.),r1(0.),r2(0.);

  if(!user1){
    r1 = getEfficiency_electron(0,_el1_pt, _el1_eta, cut);
    r2 = getEfficiency_electron(0,_el2_pt, _el2_eta,cut);
  }
  else{
    r1=1.;
    r2=1.;
  }
  fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut);
  fr2= getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut);

  float fr1_err=  getFakeRate_electronEta(1,_el1_pt, _el1_eta,cut);
  float fr2_err=  getFakeRate_electronEta(1,_el2_pt, _el2_eta,cut);

  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(fr1_err,fr1,fr2_err,fr2, isel1tight, isel2tight, eventtype);

  if(fr1 <=0.) cout << cut << "  eta = " << _el1_eta << " pt = " << _el1_pt << endl;
  if(fr2 <=0.) cout << cut << "  eta = " << _el2_eta << " pt = " << _el2_pt << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;
}


float  HNCommonLeptonFakes::get_dilepton_em_mceventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electrons, bool ismu1tight, bool isel1tight, int nbjet, TString tag){
  if(muons.size()!=1) {
    return (0.);
  }
  if(electrons.size()!=1) {
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _mu1_pt=muons.at(0).Pt();


  float _el1_eta=fabs(electrons.at(0).Eta());
  float _mu1_eta=fabs(muons.at(0).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "mu1 pT = " << _mu1_pt << endl;
  }

  if(_el1_pt > 60.) _el1_pt = 59.;
  if(_mu1_pt > 60.) _mu1_pt = 59.;

  float fr1(0.),fr2(0.),r1(0.),r2(0.);

  r1 = 1.;
  r2 = 1.;

  fr2= getFakeRate_mc_muon("mc_muon_" + tag,_mu1_pt, _mu1_eta);
  fr1= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"mc_"+tag +"_loosereg2");

  //cout << "\n -------- " << endl;
  //cout << "Muon pt/eta = " << _mu1_pt << " " << _mu1_eta << endl;
  //cout << "Electron pt/eta = " << _el1_pt << " " << _el1_eta << endl;

  //cout << "isel1tight = " << isel1tight << " ismu1tight= " << ismu1tight << " " << fr1 <<    " " << fr2 << endl;

  float ev_weight = CalculateDiLepMMWeight(0.,fr1,0.,fr2, isel1tight, ismu1tight);
  //cout << "ev_weight = " << ev_weight << endl;

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;

}



float  HNCommonLeptonFakes::get_dilepton_em_eventweight(std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electrons, bool ismu1tight, bool isel1tight, int nbjet, int syst){

  if(muons.size()!=1) {
    return (0.);
  }
  if(electrons.size()!=1) {
    return (0.);
  }

  float _el1_pt=electrons.at(0).Pt();
  float _mu1_pt=muons.at(0).Pt();


  float _el1_eta=fabs(electrons.at(0).Eta());
  float _mu1_eta=fabs(muons.at(0).Eta());

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "mu1 pT = " << _mu1_pt << endl;
  }

  if(_el1_pt > 60.) _el1_pt = 59.;
  if(_mu1_pt > 60.) _mu1_pt = 59.;

  float fr1(0.),fr2(0.),r1(0.),r2(0.);

  r1 = 1.;
  r2 = 1.;

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta);
  
  if(nbjet ==0) {
    if( _el1_eta < 1.5) {
      if(_el1_pt > 45.) _el1_pt = 64.;
    }
    if(_mu1_pt < 50. &&  _mu1_pt > 40.) fr1 *= 1.3;
  }
  else {
    //   if(_mu1_pt < 25.) fr1 *= 0.7; 
  }
  

  
  fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"pt_eta_40_looseregion2");
  
  if(nbjet ==0) {
    if( _el1_eta > 1.5) {
      if(_el1_pt > 20. && _el1_pt < 40) fr2*= 1.5;
      if(_el1_pt > 30. && _el1_pt < 40) fr2*= 2.;
    }
    else {
      if(_el1_pt > 25. && _el1_pt < 30) fr2*= 1.3;
    }
  }

  if(syst ==1){
    fr1= getFakeRate_muon(1,_mu1_pt, _mu1_eta);
    fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"pt_eta_20_looseregion2");
  }
  if(syst ==-1){
    fr1= getFakeRate_muon(-1,_mu1_pt, _mu1_eta);
    fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"pt_eta_60_looseregion2");

  }

  if(syst == 3){
    fr1= getFakeRate_muon(3,_mu1_pt, _mu1_eta);
    fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"HNTight_iso05_40_pt_eta");
  }
  if(syst == 4){

    fr1= getFakeRate_muon(4,_mu1_pt, _mu1_eta);
    //if(getFakeRate_electronEta(0,_el1_pt, _el1_eta,"HNTight_iso07_40_pt_eta") > fr2)
    //fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"HNTight_iso07_40_pt_eta");
  }

  if(nbjet != 0) {
    fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"bjet_pt_eta_40_looseregion2");
  }
  
  if(nbjet ==0) {
    if(_el1_pt > 90.) {
      fr1 *= 2.5;
      fr2 *= 2.5;
    }

  }
  else{
  }
  
  float fr1_err = 0.;
  float fr2_err = 0.;
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(fr1_err,fr1,fr2_err,fr2, isel1tight, ismu1tight);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;

}

float  HNCommonLeptonFakes::get_dilepton_mm_eventweight( std::vector<TLorentzVector> muons,bool ismu1tight, bool ismu2tight){
  
  if(muons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }
  
  float _mu1_pt=muons.at(0).Pt();
  float _mu1_eta=muons.at(0).Eta();
  float _mu2_pt=muons.at(1).Pt();
  float _mu2_eta=muons.at(1).Eta();

  
  float fr1(0.),fr2(0.),r1(0.),r2(0.);  
  /// Get real efficiencies (pt max 200 set in function) uses tight zwindow: rsys sets systematic (0/1/-1)
  
  r1 = getEfficiency_muon(0,_mu1_pt, _mu1_eta);
  r2 = getEfficiency_muon(0,_mu2_pt, _mu2_eta);

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta);
  fr2= getFakeRate_muon(0,_mu2_pt, _mu2_eta);
  
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismu1tight, ismu2tight);

  return ev_weight;

}


float HNCommonLeptonFakes::getEfficiency_electron(int sys, float pt, float eta, TString cut){
  
  float eff_real(1.);
  
  map<TString,TH2F*>::const_iterator mapit;
  
  TString hist = "real_eff_";
  hist += cut; 

  mapit = _2DEfficiencyMap.find(hist.Data());
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,eta);
    eff_real =  mapit->second->GetBinContent(binx);
  }
  else NoHist( hist.Data());

  if(eff_real==0.) eff_real=1.;
  return eff_real;
  
}




 float HNCommonLeptonFakes::getEfficiency_electron(int sys, float pt, float eta){

  float eff_real(1.);

  /// Will update with eta dependance 
  if(pt< 25.) eff_real = 0.88;
  else if(pt< 30.) eff_real = 0.91;
  else if(pt< 40.) eff_real = 0.93;
  else if(pt< 50.) eff_real = 0.94;
  else  eff_real = 0.99;

  
  
  if(sys ==1) eff_real= 1.;
  if(sys ==-1) eff_real*=0.9;
  
  return eff_real;
}
 
 
 
float HNCommonLeptonFakes::getEfficiency_muon(int sys, float pt, float eta){
   
   float eff_real(1.);

  if(sys ==1) eff_real= 1.;
  if(sys ==-1) eff_real=0.9;
  
  //// NO PROMPT EFFICIENCIES MEASURED FOR MUONS 
     
  return eff_real;
}



float HNCommonLeptonFakes::getFakeRate_mc_muon(TString tag, float pt, float eta){

  float eff_fake(0.);
  
  if(pt > 60) pt = 59.;
  
  map<TString,TH2F*>::const_iterator mapit;

  mapit = _2DEfficiencyMap.find(tag.Data());
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(fabs(eta), pt);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((tag.Data()));


  return eff_fake;

  
}

float HNCommonLeptonFakes::getFakeRate_electron(int sys,float pt, float ht, TString cut){
   
   float eff_fake(0.);

   if(ht < 20.) ht = 21.;
   if(pt < 10) return -999999.;
  
   map<TString,TH2F*>::const_iterator mapit;
   
   TString hist = "fake_eff_ht_";
   hist += cut;

   mapit = _2DEfficiencyMap.find(hist.Data());

  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,ht);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((hist.Data()));
 

  return eff_fake;
}

float HNCommonLeptonFakes::getFakeRate_electronEta(int sys,float pt, float eta, TString cut){

  float eff_fake(0.);

  if(fabs(eta) > 2.5) return -999999.;
  if(pt < 15) return -999999.;

  map<TString,TH2F*>::const_iterator mapit;

  TString hist = "fake_eff_";
  hist += cut;
  
  //cout << "hist = " << hist << endl;
  mapit = _2DEfficiencyMap.find(hist.Data());
  if(mapit!=_2DEfficiencyMap.end()){

    int binx =  mapit->second->FindBin(pt,eta);
    //cout << "Bin = " << binx  << endl;
    eff_fake =  mapit->second->GetBinContent(binx);
    if(sys != 0) return mapit->second->GetBinError(binx); 
  }
  else NoHist((hist.Data()));
  
  
  return eff_fake;
}




float HNCommonLeptonFakes::getFakeRate_electron(int sys,float pt, float eta ){
  float eff_fake=0.;

  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 10) return -999999.;
  

  if(pt< 20.) eff_fake=0.180564;
  else if(pt< 25) eff_fake=0.161576;
  else if(pt< 30.) eff_fake=0.141819;
  else if(pt< 35.) eff_fake=0.14412;
  else if(pt< 40.) eff_fake=0.143885;
  else if(pt< 60.) eff_fake=0.153494;
  else  eff_fake=0.125989;
  
  return eff_fake;
}

float HNCommonLeptonFakes::getFakeRate_muon(int sys,float pt, float eta ){
  
  float eff_fake=0.;
  
  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 15) return -999999.;
  
  if(fabs(eta) < 0.8){
    if((pt < 20.))  eff_fake=0.052;
    else if(pt < 25) eff_fake= 0.050;
    else if(pt < 30) eff_fake= 0.044;
    else if(pt < 35) eff_fake= 0.044;
    else if(pt < 45) eff_fake= 0.067;
    else eff_fake= 0.076;
  }
  else if(fabs(eta) < 1.479){
    if((pt < 20.))  eff_fake=0.060;
    else if(pt < 25) eff_fake= 0.050;
    else if(pt < 30) eff_fake= 0.051;
    else if(pt < 35) eff_fake= 0.066;
    else if(pt < 45) eff_fake= 0.070;
    else eff_fake= 0.058;
  }
  else if(fabs(eta) < 2.){
    if((pt < 20.))  eff_fake=0.080;
    else if(pt < 25) eff_fake= 0.079;
    else if(pt < 30) eff_fake= 0.071;
    else if(pt < 35) eff_fake= 0.068;
    else if(pt < 45) eff_fake= 0.106;
    else eff_fake= 0.027;
  }
  else if(fabs(eta) < 2.5){
    if((pt < 20.))  eff_fake=0.089;
    else if(pt < 25) eff_fake= 0.070;
    else if(pt < 30) eff_fake= 0.091;
    else if(pt < 35) eff_fake= 0.080;
    else if(pt < 45) eff_fake= 0.077;
    else eff_fake= 0.231;
  }
  
  if(sys == 1) {

    if(fabs(eta) < 0.8){
      if((pt < 20.))   eff_fake = 0.0772;
      else if(pt < 25) eff_fake= 0.0679;
      else if(pt < 30) eff_fake= 0.0561;
      else if(pt < 35) eff_fake= 0.0581;
      else if(pt < 45) eff_fake= 0.0771;
      else  eff_fake= 0.0976;
    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  eff_fake= 0.0947;
      else if(pt < 25) eff_fake= 0.0773;
      else if(pt < 30) eff_fake= 0.0642;
      else if(pt < 35) eff_fake= 0.0750;
      else if(pt < 45) eff_fake= 0.0827;
      else eff_fake= 0.0849;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  eff_fake= 0.108;
      else if(pt < 25) eff_fake= 0.098;
      else if(pt < 30) eff_fake= 0.0851;
      else if(pt < 35) eff_fake= 0.0743;
      else if(pt < 45) eff_fake= 0.123;
      else eff_fake= 0.055;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  eff_fake= 0.123;
      else if(pt < 25) eff_fake= 0.1162;
      else if(pt < 30) eff_fake= 0.1200;
      else if(pt < 35) eff_fake= 0.0918;
      else if(pt < 45) eff_fake= 0.1127;
      else eff_fake= 0.2590;
    }
  }


  if(sys == -1) {

    if(fabs(eta) < 0.8){
      if((pt < 20.))   eff_fake = 0.0529;
      else if(pt < 25) eff_fake= 0.0446;
      else if(pt < 30) eff_fake= 0.0236;
      else if(pt < 35) eff_fake= 0.0373;
      else if(pt < 45) eff_fake= 0.0412;
      else  eff_fake= 0.0520;
    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  eff_fake= 0.0612;
      else if(pt < 25) eff_fake= 0.0544;
      else if(pt < 30) eff_fake= 0.0428;
      else if(pt < 35) eff_fake= 0.0369;
      else if(pt < 45) eff_fake= 0.0548;
      else eff_fake= 0.013;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  eff_fake= 0.072;
      else if(pt < 25) eff_fake= 0.062;
      else if(pt < 30) eff_fake= 0.056;
      else if(pt < 35) eff_fake= 0.055;
      else if(pt < 45) eff_fake= 0.042;
      else eff_fake= 0.022;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  eff_fake= 0.095;
      else if(pt < 25) eff_fake= 0.051;
      else if(pt < 30) eff_fake= 0.079;
      else if(pt < 35) eff_fake= 0.074;
      else if(pt < 45) eff_fake= 0.032;
      else eff_fake= 0.059;
    }
  }
    
  if(sys == 3) {

    if(fabs(eta) < 0.8){
      if((pt < 20.))   eff_fake = 0.0796;
      else if(pt < 25) eff_fake= 0.0769;
      else if(pt < 30) eff_fake= 0.0723;
      else if(pt < 35) eff_fake= 0.0708;
      else if(pt < 45) eff_fake= 0.105;
      else  eff_fake= 0.113;
    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  eff_fake= 0.089;
      else if(pt < 25) eff_fake= 0.0743;
      else if(pt < 30) eff_fake= 0.0757;
      else if(pt < 35) eff_fake= 0.0994;
      else if(pt < 45) eff_fake= 0.102;
      else eff_fake= 0.0833;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  eff_fake= 0.111;
      else if(pt < 25) eff_fake= 0.108;
      else if(pt < 30) eff_fake= 0.0989;
      else if(pt < 35) eff_fake= 0.0983;
      else if(pt < 45) eff_fake= 0.147;
      else eff_fake= 0.0038;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  eff_fake= 0.120;
      else if(pt < 25) eff_fake= 0.0944;
      else if(pt < 30) eff_fake= 0.1217;
      else if(pt < 35) eff_fake= 0.1139;
      else if(pt < 45) eff_fake= 0.1057;
      else eff_fake= 0.35;
    }
  }



  if(sys == 4) {

    if(fabs(eta) < 0.8){
      if((pt < 20.))   eff_fake = 0.0376;
      else if(pt < 25) eff_fake= 0.0359;
      else if(pt < 30) eff_fake= 0.0313;
      else if(pt < 35) eff_fake= 0.0317;
      else if(pt < 45) eff_fake= 0.04863;
      else  eff_fake= 0.0554;

    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  eff_fake= 0.0451;
      else if(pt < 25) eff_fake= 0.0384;
      else if(pt < 30) eff_fake= 0.0379;
      else if(pt < 35) eff_fake= 0.0499;
      else if(pt < 45) eff_fake= 0.0538;
      else eff_fake= 0.0425;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  eff_fake= 0.0627;
      else if(pt < 25) eff_fake= 0.0628;
      else if(pt < 30) eff_fake= 0.0554;
      else if(pt < 35) eff_fake= 0.0534;
      else if(pt < 45) eff_fake= 0.0856;
      else eff_fake= 0.022;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  eff_fake= 0.0708;
      else if(pt < 25) eff_fake= 0.0573;
      else if(pt < 30) eff_fake= 0.0708;
      else if(pt < 35) eff_fake= 0.0647;
      else if(pt < 45) eff_fake= 0.0639;
      else eff_fake= 0.0201;
    }
  }


  return eff_fake;
}




void HNCommonLeptonFakes::NoHist(TString hist, TString function){
  
  cout << function << ": No Histogram found for string " << hist << endl;

  cout << "Possible _EfficiencyMap hists are : " << endl;
  for(map<TString, TH1*>::iterator mit = _EfficiencyMap.begin(); mit != _EfficiencyMap.end(); mit++){
    cout << mit->first << endl;  
  }
  

  cout << "Possible _2DEfficiencyMap hists are : " << endl;
  for(map<TString, TH2F*>::iterator mit = _2DEfficiencyMap.begin(); mit != _2DEfficiencyMap.end(); mit++){
    cout << mit->first <<" " << mit->second << endl;    
  }  
  
  cout << "Possible _EfficiencyMapHST hists are : " << endl;
  for(map<TString, TH1*>::iterator mit = _EfficiencyMapHST.begin(); mit != _EfficiencyMapHST.end(); mit++){
    cout << mit->first << endl;  
  }

  cout << "Possible _2DEfficiencyMapHST hists are : " << endl;
  for(map<TString, TH2F*>::iterator mit = _2DEfficiencyMapHST.begin(); mit != _2DEfficiencyMapHST.end(); mit++){
    cout << mit->first << " " << mit->second << endl;    
  }  

  exit(1);
}

void HNCommonLeptonFakes::NullTotals(){
  fsys=0;
  rsys=0;
  
}


void HNCommonLeptonFakes::CheckFile(TFile* file){

  if(file) cout << "HNCommonLeptonFakes: File " << file->GetName() << " was found." << endl;
  else cout << "HNCommonLeptonFakes  " << file->GetName()  << "  : ERROR Rootfile failed to open." << endl;
  
  if(!file) exit(0);
  return;
}



float HNCommonLeptonFakes::CalculateDiLepMMWeight(float r1, float fr1, float r2, float fr2, bool mu1Tight, bool mu2Tight){
 
  
  // Function calculates event weight given r/f of two muons in the event
  double alpha = 1./((1.- fr1)*(1.- fr2));

  // Initialise weight
  float w_mm=-999.;
    
  // Terms for RF and FR events from MM
  double termTT = 0.;
  double termTL = alpha*(fr2*(1.-fr1));
  double termLT = alpha*(fr1*(1.-fr2));
  double termLL = -2.*alpha*(fr2*(fr1));
  
  
  // Term for FF events
  termTT += 0.;
  termTL += 0.;
  termLT += 0.;
  termLL += alpha*(fr1*fr2);

  
  // decide which type of event we have so to return correct weight
  bool isLL = (!mu1Tight&&!mu2Tight);
  bool isLT = (!mu1Tight&&mu2Tight);
  bool isTL = (mu1Tight && !mu2Tight);
  bool isTT = (mu1Tight && mu2Tight);

  if(isLL)w_mm = termLL;
  if(isTL)w_mm = termTL;
  if(isLT)w_mm = termLT;
  if(isTT)w_mm=  termTT;  



  return w_mm;   
}


float HNCommonLeptonFakes::CalculateDiLepMMWeight(float fr1_err, float fr1, float fr2_err, float fr2, bool mu1Tight, bool mu2Tight, int eventtype){


  // Function calculates event weight given r/f of two muons in the event
  double alpha = 1./((1.- fr1)*(1.- fr2));
  
  // Initialise weight
  float w_mm=-999.;


  // Terms for RF and FR events from MM
  double termTT = 0.;
  double termTL = alpha*(fr2*(1.-fr1));
  double termLT = alpha*(fr1*(1.-fr2));
  double termLL = -2.*alpha*(fr2*(fr1));

  if(eventtype == 0 || eventtype == 2){
    // Term for FF events
    termTT += 0.;
    termTL += 0.;
    termLT += 0.;
    termLL += alpha*(fr1*fr2);
  }

  if(eventtype == 2){
    // Term for FF events
    termTT = 0.;
    termTL = 0.;
    termLT = 0.;
    termLL = alpha*(fr1*fr2);
  }

  // decide which type of event we have so to return correct weight
  bool isLL = (!mu1Tight&&!mu2Tight);
  bool isLT = (!mu1Tight&&mu2Tight);
  bool isTL = (mu1Tight && !mu2Tight);
  bool isTT = (mu1Tight && mu2Tight);

  
  if(eventtype == 3) {
    // error onfake
    float error = 0.;
    if(isLL) {
      error = sqrt( pow(fr1_err*fr2*(1-fr2),2) + pow(fr2_err*fr1*(1-fr1),2) ) / pow((1-fr1)*(1-fr2),2);
    }
    if(isLT){
      error= fr1_err/pow(fr1-1,2);
    }
    if(isTL){
      error= fr2_err/pow(fr2-1,2);
    }
    return error;
  }
    
  if(isLL)w_mm = termLL;
  if(isTL)w_mm = termTL;
  if(isLT)w_mm = termLT;
  if(isTT)w_mm=  termTT;


  return w_mm;
}



double HNCommonLeptonFakes::lepton_weight(bool loose, double r, double f) {
  // Function to get event weight for a single muon event
  double nl=loose ? 1 :0;
  double nt=!loose ? 1 :0;
  if(r==f) return 0.;
  double a=1./(r-f);
  float nf=a*f*r*nl;
  float nr=a*f*(r - 1.)*nt;
  return nf+nr;
}

void HNCommonLeptonFakes::APPLY_scalefactor(bool applysf) {
  apply_scalefactor = applysf;
}
