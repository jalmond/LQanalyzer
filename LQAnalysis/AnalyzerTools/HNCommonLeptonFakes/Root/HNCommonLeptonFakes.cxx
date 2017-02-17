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
#include "TH2D.h"
#include "TEfficiency.h"

/// local includes
#include "HNCommonLeptonFakes/HNCommonLeptonFakes.h"

using namespace std;


void HNCommonLeptonFakes::InitialiseFake(){
  
  bool failedinitialisation=false;

  cout << "HNCommonLeptonFakes : Initializing" << endl;

  // Remember which TDirectory the system is in at the beginning of the method:                                                                                                      
  TDirectory* origDir = gDirectory;
  
  /// List files with fake rates

  string lqdir = getenv("LQANALYZER_DIR");

  /// MUON FILES  POG + HN

  TFile* file_fake_muon  = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/Total_FRcorr40_1.root").c_str());
  CheckFile(file_fake_muon);
  
  TFile* file_fake_muon_hn  = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/Total_FRcorr40_2.root").c_str());
  CheckFile(file_fake_muon_hn);

  /// ELECRON FILES  (POG)
  TFile* file_fake  = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/FakeRate13TeV.root").c_str());
  CheckFile(file_fake);
  
  /// ELECTRON FILES  (many rates for optimising cuts)                                                                                                                                                          
  TFile* file_fakeopt  = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/FakeRate13TeV_2016_opt.root").c_str());
  CheckFile(file_fakeopt);


  //==== Trilep
  //==== Using Large dXYSig muons
  TFile* file_trilep_fake = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/Trilep_Muon_FakeRate_RunBCDEFGH_rereco.root").c_str());
  TFile* file_trilep_prompt = TFile::Open( (lqdir + "/data/Fake/"+getenv("yeartag")+"/Trilep_Muon_PromptRate_RunBCDEF_rereco.root").c_str());
  CheckFile(file_trilep_fake);
  CheckFile(file_trilep_prompt);



  ////// MAKE HISTS IN MAP
  TDirectory* tempDir1 = getTemporaryDirectory();
  tempDir1->cd();
  
  _2DEfficiencyMap["fake_Eff_muon_pog"] = dynamic_cast<TH2F*>((file_fake_muon->Get("h_FOrate3"))->Clone());

  _2DEfficiencyMap["fake_Eff_muon_hn"] = dynamic_cast<TH2F*>((file_fake_muon_hn->Get("h_FOrate3"))->Clone());

  std::vector <TString> region;
  region.push_back("looseregion1");

  std::vector <TString> datajetcut;
  datajetcut.push_back("40");
  
  std::vector <TString> cut;
  cut.push_back("pt_eta");

  std::vector <TString> opt;
  opt.push_back("b035_e035");
  opt.push_back("b035_e040");
  opt.push_back("b035_e045");
  opt.push_back("b035_e050");
  opt.push_back("b035_e055");
  opt.push_back("b035_e060");
  
  opt.push_back("b040_e035");
  opt.push_back("b040_e040");
  opt.push_back("b040_e045");
  opt.push_back("b040_e050");
  opt.push_back("b040_e055");
  opt.push_back("b040_e060");

  opt.push_back("b060_e035");
  opt.push_back("b060_e040");
  opt.push_back("b060_e045");
  opt.push_back("b060_e050");
  opt.push_back("b060_e055");
  opt.push_back("b060_e060");

  opt.push_back("b045_e035");
  opt.push_back("b045_e040");
  opt.push_back("b045_e045");
  opt.push_back("b045_e050");
  opt.push_back("b045_e055");
  opt.push_back("b045_e060");

  opt.push_back("b050_e035");
  opt.push_back("b050_e040");
  opt.push_back("b050_e045");
  opt.push_back("b050_e050");
  opt.push_back("b050_e055");
  opt.push_back("b050_e060");

  opt.push_back("b055_e035");
  opt.push_back("b055_e040");
  opt.push_back("b055_e045");
  opt.push_back("b055_e050");
  opt.push_back("b055_e055");
  opt.push_back("b055_e060");

  opt.push_back("dxy_b050_e100");
  opt.push_back("dxy_b050_e050");
  opt.push_back("dxy_b050_e040");
  opt.push_back("dxy_b050_e025");
  opt.push_back("dxy_b050_e020");
  opt.push_back("dxy_b050_e015");
  
  opt.push_back("dxy_b025_e100");
  opt.push_back("dxy_b025_e050");
  opt.push_back("dxy_b025_e040");
  opt.push_back("dxy_b025_e025");
  opt.push_back("dxy_b025_e020");
  opt.push_back("dxy_b025_e015");

  opt.push_back("dxy_b015_e100");
  opt.push_back("dxy_b015_e050");
  opt.push_back("dxy_b015_e040");
  opt.push_back("dxy_b015_e025");
  opt.push_back("dxy_b015_e020");
  opt.push_back("dxy_b015_e015");

  opt.push_back("dxy_b010_e100");
  opt.push_back("dxy_b010_e050");
  opt.push_back("dxy_b010_e040");
  opt.push_back("dxy_b010_e025");
  opt.push_back("dxy_b010_e020");
  opt.push_back("dxy_b010_e015");

  opt.push_back("dxy_b008_e100");
  opt.push_back("dxy_b008_e050");
  opt.push_back("dxy_b008_e040");
  opt.push_back("dxy_b008_e025");
  opt.push_back("dxy_b008_e020");
  opt.push_back("dxy_b008_e015");

  
  for(unsigned int fj = 0; fj < datajetcut.size() ; fj++){
    for(unsigned int fk = 0; fk < cut.size() ; fk++){
      _2DEfficiencyMap["fake_eff_" + cut.at(fk) +"_" + datajetcut.at(fj) +"_" + region.at(0)] = dynamic_cast<TH2F*>((file_fake->Get("FakeRate_" + datajetcut.at(fj) + "_" + cut.at(fk)))->Clone());
    }
  }

  for(unsigned int fj = 0; fj < datajetcut.size() ; fj++){
    for(unsigned int fk = 0; fk < cut.size() ; fk++){
      for(unsigned int fl = 0; fl < opt.size() ; fl++){
	_2DEfficiencyMap_Double["fake_eff_" + cut.at(fk) +"_" + opt.at(fl) +"_" + datajetcut.at(fj) +"_" + region.at(0)] = dynamic_cast<TH2D*>((file_fakeopt->Get("FakeRate_" + datajetcut.at(fj) + "_" + cut.at(fk) + opt.at(fl)))->Clone());

      }
    }
  }



  
  //==== Trilep
  //==== Using Large dXYSig muons

  const int N_dXYMin = 3, N_LooseRelIso = 6;
  double dXYMin[N_dXYMin] = {3.0, 4.0, 5.0};
  double LooseRelIso[N_LooseRelIso] = {0.2, 0.3, 0.4, 0.6, 0.8, 1.0};
  
  for(int i=0; i<N_dXYMin; i++){
    for(int j=0; j<N_LooseRelIso; j++){
      TString this_wp = DoubleToTString(dXYMin[i], LooseRelIso[j]);
      _2DEfficiencyMap_Double["MUON_FR_"+this_wp] = dynamic_cast<TH2D*>((file_trilep_fake->Get(this_wp+"_FR"))->Clone());
      _2DEfficiencyMap_Double["MUON_FR_QCD_"+this_wp] = dynamic_cast<TH2D*>((file_trilep_fake->Get(this_wp+"_FR_QCD"))->Clone()); 
      _2DEfficiencyMap_Double["MUON_FRSF_"+this_wp] = dynamic_cast<TH2D*>((file_trilep_fake->Get(this_wp+"_FRSF_QCD"))->Clone());
    }
  }
  _2DEfficiencyMap["MUON_PR_HN_TRI"] = dynamic_cast<TH2F*>((file_trilep_prompt->Get("PR_pt_abseta"))->Clone());

  //==== Large dXYSig muon definitions for systemtatics
  TH1D *hist_dXYMins = (TH1D*)file_trilep_fake->Get("hist_dXYMins");
  TH1D *hist_RelIsoMaxs = (TH1D*)file_trilep_fake->Get("hist_RelIsoMaxs");
  for(int i=1; i<=hist_dXYMins->GetXaxis()->GetNbins(); i++) dXYMins.push_back( hist_dXYMins->GetBinContent(i) );
  for(int i=1; i<=hist_RelIsoMaxs->GetXaxis()->GetNbins(); i++) RelIsoMaxs.push_back( hist_RelIsoMaxs->GetBinContent(i) );
  
  if(failedinitialisation){
    cout << "Not all histograms could be initialised, this is a bug so am exiting" << endl;
  }
  else {

    cout << "WRHNCommonLeptonFakes : Initialsation was successful " << endl;
    cout << "WRHNCommonLeptonFakes : Default setting in MeV" <<  endl;
    cout << "WRHNCommonLeptonFakes : To Use GeV set third argument of constructor true" << endl;
  }

  file_fake->Close();
  delete file_fake;
  
  file_fake_muon->Close();
  delete file_fake_muon;

  file_fake_muon_hn->Close();
  delete file_fake_muon_hn;


  /// Trilepton files
  file_trilep_fake->Close();
  delete file_trilep_fake;
  
  file_trilep_prompt->Close();
  delete file_trilep_prompt;

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
  Current_dXYSig = 4.0;
  Current_RelIso = 0.4;
  UseQCDFake = false; 
}


/// Destructor
HNCommonLeptonFakes::~HNCommonLeptonFakes() {
  closefile();   
  CutHists.clear();
}



float HNCommonLeptonFakes::get_dilepton_ee_eventweight(bool geterr, std::vector<TLorentzVector> electrons, bool isel1tight, bool isel2tight ){ 


  // geterr = true : function returns error not event weight
  // electrons are loose electrons defined in analysis code
  // ID defines which id is used for tight leptons              (currently only "POGTight" for electrons)  
  // method defines the techinique used to measure fake rates   (currently only "dijet" for electrons)
  // @@@@@ CURRENTLY ONLY  POG ID IS USED HERE
  // 
 
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

  if(_el1_pt > 60.) _el1_pt = 59.;
  if(_el2_pt > 60.) _el2_pt = 59.;


  float fr1(0.),fr2(0.),r1(0.),r2(0.);
  
  // Need to create this function in HNCommonFakes
  r1=1.;
  r2=1.;
  

  /// Currenty  using pt/eta dependant rates, using 40 GeV away jet and looseregion 1 means relaxing dxy
  TString cut  = "pt_eta_40_looseregion1";


  fr1=  getFakeRate_electronEta(0,_el1_pt, _el1_eta,cut);
  fr2=  getFakeRate_electronEta(0,_el2_pt, _el2_eta,cut);
  if(_el1_pt < 20.)cout <<fr1 << " " << "_el1_eta" << cut << endl;
  if(_el2_pt < 20.)cout <<fr2 << " " << "_el2_eta" << cut << endl;

  float fr1_err=  getFakeRate_electronEta(1,_el1_pt, _el1_eta,cut);
  float fr2_err=  getFakeRate_electronEta(1,_el2_pt, _el2_eta,cut);

  if(fr1 == 0.)  fr1 = 0.05;
  if(fr2 == 0.)  fr2 = 0.05;
  
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(fr1_err,fr1,fr2_err,fr2, isel1tight, isel2tight, 0);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }

  
  return ev_weight;
}

 

float  HNCommonLeptonFakes::get_dilepton_em_eventweight(bool geterr, std::vector<TLorentzVector> muons, std::vector<TLorentzVector> electrons, bool isel1tight, bool ismu1tight ){

  // geterr = true : function returns error not event weight                                                                                                                      
  // electrons are loose electrons defined in analysis code                                                                                                                       
  // ID defines which id is used for tight leptons              (currently only "POGTight" for electrons)                                                                        
  // method defines the techinique used to measure fake rates   (currently only "dijet" for electrons)                                                                           
  // @@@@@ CURRENTLY ONLY  POG ID IS USED HERE                                                                                                                                     

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


  //// WORK ON THIS
  r1 = 1.;
  r2 = 1.;

  fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta,"HN");
  fr2= getFakeRate_electronEta(0,_el1_pt, _el1_eta,"pt_eta_40_looseregion1");
  
  float fr1_err = 0.;
  float fr2_err = 0.;
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(fr1_err,fr1,fr2_err,fr2, isel1tight, ismu1tight);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }


  return ev_weight;

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
  /// Will update with eta dependance
  if(sys ==1) eff_real= 1.;
  if(sys ==-1) eff_real=0.9;
  
  //// NO PROMPT EFFICIENCIES MEASURED FOR MUONS 
     
  return eff_real;
}


float HNCommonLeptonFakes::getFakeRate_electronEta(int sys,float pt, float eta, TString cut){
  
  float eff_fake(0.);

  if(fabs(eta) > 2.5) return -999999.;
  if(pt < 15) return -999999.;
  if(pt  > 45.) pt = 44.;

  if(fabs(eta) < 0.5){
    if(pt < 20.) return 0.15;
    if(pt < 25.) return 0.16;
    if(pt < 30.) return 0.19;
    if(pt < 35.) return 0.33;
    else return 0.44;
  }
  if(fabs(eta) < 1.5){
    if(pt < 20.) return 0.14;
    if(pt < 25.) return 0.13;
    if(pt < 30.) return 0.14;
    if(pt < 35.) return 0.24;
    else return 0.40;
  }
  
  if(fabs(eta) < 2.){
    if(pt < 20.) return 0.23;
    if(pt < 25.) return 0.21;
    if(pt < 30.) return 0.21;
    if(pt < 35.) return 0.40;
    else return 0.40;
  }
  else{
    if(pt < 20.) return 0.28;
    if(pt < 25.) return 0.28;
    if(pt < 30.) return 0.27;
    if(pt < 35.) return 0.45;
    else return 0.45;
  }

  map<TString,TH2F*>::const_iterator mapit;

  TString hist = "fake_eff_";
  hist += cut;
  
  cout << hist << endl;
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

float HNCommonLeptonFakes::getFakeRate_muon(int sys,float pt, float eta , TString ID){
  
  float eff_fake=0.;
  
  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 10) return -999999.;
  
  map<TString,TH2F*>::const_iterator mapit;

  TString label = "fake_Eff_muon_pog";
  if(ID.Contains("HN"))label="fake_Eff_muon_hn";
  mapit = _2DEfficiencyMap.find(label);

  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(fabs(eta), pt);
    eff_fake =  mapit->second->GetBinContent(binx);
  }
  else NoHist((label.Data()));

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


/// ====== START TRIMUON FUNCTIONALITY
void HNCommonLeptonFakes::APPLY_scalefactor(bool applysf) {
  apply_scalefactor = applysf;
}

TString HNCommonLeptonFakes::DoubleToTString(double this_dXYSig, double this_RelIso){
  
  int dXY_Digit1 = int(this_dXYSig);
  int dXY_Digit0p1 = 10*this_dXYSig-10*dXY_Digit1;
  TString str_dXYCut = "dXYSigMin_"+TString::Itoa(dXY_Digit1,10)+"p"+TString::Itoa(dXY_Digit0p1,10);
  
  int iso_Digit1 = int(this_RelIso);
  int iso_Digit0p1 = 10*this_RelIso-10*iso_Digit1;
  TString str_iso = "LooseRelIsoMax_"+TString::Itoa(iso_Digit1,10)+"p"+TString::Itoa(iso_Digit0p1,10);
  
  return str_dXYCut+"_"+str_iso;

}


void HNCommonLeptonFakes::SetTrilepWP(double this_dXYSig, double this_RelIso){
  
  Current_dXYSig = this_dXYSig;
  Current_RelIso = this_RelIso;
  
}

void HNCommonLeptonFakes::SetUseQCDFake(bool useit){
  UseQCDFake = useit;
}

float HNCommonLeptonFakes::getTrilepFakeRate_muon(bool geterr, float pt,  float eta, bool applysf){
  
  if(pt < 10.) pt = 11.;
  if(pt >= 60.) pt = 59.;
  if(fabs(eta) >= 2.5) eta = 2.4;

  TString wp = DoubleToTString(Current_dXYSig, Current_RelIso);
  if(UseQCDFake) wp = "QCD_"+wp; 
  
  //==== Get FR
  map<TString,TH2D*>::const_iterator mapit_FR = _2DEfficiencyMap_Double.find("MUON_FR_"+wp);
  map<TString,TH2D*>::const_iterator mapit_FRSF = _2DEfficiencyMap_Double.find("MUON_FRSF_"+wp);
  
  if(UseQCDFake){
    if( mapit_FR==_2DEfficiencyMap_Double.end()){
      NoHist("MUON_FR_"+DoubleToTString(Current_dXYSig, Current_RelIso));
      return 0.;
    }
    else{
      TDirectory* origDir = gDirectory;

      TDirectory* tempDir = getTemporaryDirectory();
      tempDir->cd();
      TH2D *hist_FR = (TH2D*)mapit_FR->second->Clone();

      origDir->cd();

      int binx = hist_FR->FindBin(pt, abs(eta));
      if(geterr) return hist_FR->GetBinError(binx);
      else return hist_FR->GetBinContent(binx);
    }
  }
  else{
    if( mapit_FR==_2DEfficiencyMap_Double.end() || mapit_FRSF==_2DEfficiencyMap_Double.end() ){
      NoHist("MUON_FR_"+DoubleToTString(Current_dXYSig, Current_RelIso));
      NoHist("MUON_FRSF_"+DoubleToTString(Current_dXYSig, Current_RelIso));
      return 0.;
    }
    else{
      TDirectory* origDir = gDirectory;

      TDirectory* tempDir = getTemporaryDirectory();
      tempDir->cd();
      TH2D *hist_FR = (TH2D*)mapit_FR->second->Clone();
      if(applysf) hist_FR->Multiply(mapit_FRSF->second); 

      origDir->cd();
      
      int binx = hist_FR->FindBin(pt, abs(eta));
      if(geterr) return hist_FR->GetBinError(binx);
      else return hist_FR->GetBinContent(binx);
    } 
    
  }
  return 0.;
  
}

float HNCommonLeptonFakes::getTrilepPromptRate_muon(bool geterr, float pt, float eta){

  if(pt < 5.) pt = 6.;
  if(pt >= 200.) pt = 199.;
  if(fabs(eta) >= 2.5) eta = 2.4;
  
  map<TString,TH2F*>::const_iterator mapit;
  mapit = _2DEfficiencyMap.find("MUON_PR_HN_TRI_TIGHT");
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt, abs(eta));
    if(geterr) return mapit->second->GetBinError(binx);
    else return mapit->second->GetBinContent(binx);
  }
  else{
    NoHist("MUON_PR_HN_TRI_TIGHT"+DoubleToTString(Current_dXYSig, Current_RelIso));
    return 0.;
  }
  return 0.;
}

std::vector<double> HNCommonLeptonFakes::GetdXYMins(){
  return dXYMins;
}

std::vector<double> HNCommonLeptonFakes::GetRelIsoMaxs(){
  return RelIsoMaxs;
}

int HNCommonLeptonFakes::GetNLooseNotTight(){

  return n_Loose_not_Tight;

}

/// ====== END  TRIMUON FUNCTIONALITY

/*############################################################### 
##      TRIMUON FAKE FUNCTIONS 
############################################################### */

float HNCommonLeptonFakes::get_trilepton_mmm_eventweight(bool geterr, std::vector<TLorentzVector> muons, bool isT1, bool isT2, bool isT3){

  if(muons.size()!=3) {
    cout << "TriLepton event weight requires 3 muons." << endl;
    return (0.);
  }

  float _mu1_pt=muons.at(0).Pt();
  float _mu1_eta=muons.at(0).Eta();
  float _mu2_pt=muons.at(1).Pt();
  float _mu2_eta=muons.at(1).Eta();
  float _mu3_pt=muons.at(2).Pt();
  float _mu3_eta=muons.at(2).Eta();

  float fr1(0.),fr2(0.),fr3(0.),r1(0.),r2(0.),r3(0.);
  float fr1_err(0.),fr2_err(0.),fr3_err(0.),r1_err(0.),r2_err(0.),r3_err(0.);

  r1 = getTrilepPromptRate_muon(false, _mu1_pt, _mu1_eta);
  r2 = getTrilepPromptRate_muon(false, _mu2_pt, _mu2_eta);
  r3 = getTrilepPromptRate_muon(false, _mu3_pt, _mu3_eta);
  fr1 = getTrilepFakeRate_muon(false, _mu1_pt, _mu1_eta, true);
  fr2 = getTrilepFakeRate_muon(false, _mu2_pt, _mu2_eta, true);
  fr3 = getTrilepFakeRate_muon(false, _mu3_pt, _mu3_eta, true);

  //==== let a == f/(1-f)

  double a1 = fr1/(1.-fr1);
  double a2 = fr2/(1.-fr2);
  double a3 = fr3/(1.-fr3);

  vector<double> fr_onlyLoose;
  if(!isT1) fr_onlyLoose.push_back(a1);
  if(!isT2) fr_onlyLoose.push_back(a2);
  if(!isT3) fr_onlyLoose.push_back(a3);

  //==== Initialise weight
  float this_weight=-999.;

  //==== 3T
  if(fr_onlyLoose.size()==0){
    this_weight = 0.;
  }
  //==== 2T1L
  else if(fr_onlyLoose.size()==1){
    this_weight = fr_onlyLoose.at(0);
  }
  //==== 1T2L
  else if(fr_onlyLoose.size()==2){
    this_weight = -1.*fr_onlyLoose.at(0)*fr_onlyLoose.at(1);
  }
  //==== 3L
  else if(fr_onlyLoose.size()==3){
    this_weight = fr_onlyLoose.at(0)*fr_onlyLoose.at(1)*fr_onlyLoose.at(2);
  }
  //==== ?
  else{

  }

  if(!geterr) return this_weight;

  r1_err = getTrilepPromptRate_muon(true, _mu1_pt, _mu1_eta);
  r2_err = getTrilepPromptRate_muon(true, _mu2_pt, _mu2_eta);
  r3_err = getTrilepPromptRate_muon(true, _mu3_pt, _mu3_eta);
  fr1_err = getTrilepFakeRate_muon(true, _mu1_pt, _mu1_eta, true);
  fr2_err = getTrilepFakeRate_muon(true, _mu2_pt, _mu2_eta, true);
  fr3_err = getTrilepFakeRate_muon(true, _mu3_pt, _mu3_eta, true);

  //==== d(a)/a = d(f)/f(1-f)
  //==== so, if w = a1*a2,
  //==== d(w)/w = d(a1)/a1 + d(a2)/a2

  double da1_over_a1 = fr1_err/(fr1*(1.-fr1));
  double da2_over_a2 = fr2_err/(fr2*(1.-fr2));
  double da3_over_a3 = fr3_err/(fr3*(1.-fr3));

  float this_weight_err = 0.;
  if(!isT1) this_weight_err += da1_over_a1*da1_over_a1;
  if(!isT2) this_weight_err += da2_over_a2*da2_over_a2;
  if(!isT3) this_weight_err += da3_over_a3*da3_over_a3;

  this_weight_err = sqrt(this_weight_err);
  this_weight_err = this_weight_err*fabs(this_weight);

  return this_weight_err;

}

/*###############################################################
##      DIMUON FAKE FUNCTIONS
############################################################### *
#
# fakerates = "dxy", "dijet"
#
#
################################################################ */
                                                                                                                 

float HNCommonLeptonFakes::get_dilepton_mm_eventweight(bool geterr, std::vector<TLorentzVector> muons, bool isT1, bool isT2){
  return get_dilepton_mm_eventweight("dxy", geterr,  muons, isT1,isT2,"");
}

float HNCommonLeptonFakes::get_dilepton_mm_eventweight(TString fakerates, bool geterr, std::vector<TLorentzVector> muons, bool isT1, bool isT2, TString ID){

  if(muons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }

  float _mu1_pt=muons.at(0).Pt();
  float _mu1_eta=muons.at(0).Eta();
  float _mu2_pt=muons.at(1).Pt();
  float _mu2_eta=muons.at(1).Eta();

  float fr1(0.),fr2(0.),r1(0.),r2(0.);
  float fr1_err(0.),fr2_err(0.),r1_err(0.),r2_err(0.);

  if(fakerates == "dxy"){
    r1 = getTrilepPromptRate_muon(false, _mu1_pt, _mu1_eta);
    r2 = getTrilepPromptRate_muon(false, _mu2_pt, _mu2_eta);
    fr1 = getTrilepFakeRate_muon(false, _mu1_pt, _mu1_eta, true);
    fr2 = getTrilepFakeRate_muon(false, _mu2_pt, _mu2_eta, true);
  }
  else {
    r1 = getEfficiency_muon(0,_mu1_pt, _mu1_eta);
    r2 = getEfficiency_muon(0,_mu2_pt, _mu2_eta);

    fr1= getFakeRate_muon(0,_mu1_pt, _mu1_eta, ID);
    fr2= getFakeRate_muon(0,_mu2_pt, _mu2_eta, ID);
  
    float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isT1,isT2);
    
    return ev_weight;
    
  }
  //==== let a == f/(1-f)

  double a1 = fr1/(1.-fr1);
  double a2 = fr2/(1.-fr2);

  vector<double> fr_onlyLoose;
  if(!isT1) fr_onlyLoose.push_back(a1);
  if(!isT2) fr_onlyLoose.push_back(a2);

  //==== Initialise weight
  float this_weight=-999.;

  //==== 2T
  if(fr_onlyLoose.size()==0){
    this_weight = 0.;
  }
  //==== 1T1L
  else if(fr_onlyLoose.size()==1){
    this_weight = fr_onlyLoose.at(0);
  }
  //==== 2L
  else if(fr_onlyLoose.size()==2){
    this_weight = -1.*fr_onlyLoose.at(0)*fr_onlyLoose.at(1);
  }
  //==== ?
  else{

  }

  if(!geterr) return this_weight;

  r1_err = getTrilepPromptRate_muon(true, _mu1_pt, _mu1_eta);
  r2_err = getTrilepPromptRate_muon(true, _mu2_pt, _mu2_eta);
  fr1_err = getTrilepFakeRate_muon(true, _mu1_pt, _mu1_eta, true);
  fr2_err = getTrilepFakeRate_muon(true, _mu2_pt, _mu2_eta, true);

  //==== d(a)/a = d(f)/f(1-f)
  //==== so, if w = a1*a2,
  //==== d(w)/w = d(a1)/a1 + d(a2)/a2

  double da1_over_a1 = fr1_err/(fr1*(1.-fr1));
  double da2_over_a2 = fr2_err/(fr2*(1.-fr2));

  float this_weight_err = 0.;
  if(!isT1) this_weight_err += da1_over_a1*da1_over_a1;
  if(!isT2) this_weight_err += da2_over_a2*da2_over_a2;

  this_weight_err = sqrt(this_weight_err);
  this_weight_err = this_weight_err*fabs(this_weight);

  return this_weight_err;

}


TDirectory* HNCommonLeptonFakes::getTemporaryDirectory(void) const
{
  //                                                                                                                                                                                
  // Create a unique directory in memory to hold the histograms:                                                                                                                    
  //                                                                                                                                                                               
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

float HNCommonLeptonFakes::get_eventweight(bool geterr, std::vector<TLorentzVector> muons, TString muid, std::vector<TLorentzVector> electrons, TString elid, std::vector<bool> isT){

  unsigned int n_leptons = isT.size();

  vector<float> lep_pt, lep_eta;
  vector<bool> ismuon;
  for(unsigned int i=0; i<muons.size(); i++){
    lep_pt.push_back(muons.at(i).Pt());
    lep_eta.push_back(muons.at(i).Eta());
    ismuon.push_back(true);
  }
  for(unsigned int i=0; i<electrons.size(); i++){
    lep_pt.push_back(electrons.at(i).Pt());
    lep_eta.push_back(electrons.at(i).Eta());
    ismuon.push_back(false);
  }

  vector<float> fr, pr, fr_err, pr_err;

  for(unsigned int i=0; i<n_leptons; i++){
    //==== Muon
    if(ismuon.at(i)){
      //==== Large dXYSig Method
      if(muid == "MUON_HN_TRI_TIGHT"){
        fr.push_back( getTrilepFakeRate_muon(false, lep_pt.at(i), lep_eta.at(i), true) );
        pr.push_back( getTrilepPromptRate_muon(false, lep_pt.at(i), lep_eta.at(i))  );
        fr_err.push_back( getTrilepFakeRate_muon(true, lep_pt.at(i), lep_eta.at(i), true) );
        pr_err.push_back( getTrilepPromptRate_muon(true, lep_pt.at(i), lep_eta.at(i))  );
      }
      //==== Dijet topology Method
      else{
        fr.push_back( getFakeRate_muon(0, lep_pt.at(i), lep_eta.at(i), muid) );
        pr.push_back( getEfficiency_muon(0, lep_pt.at(i), lep_eta.at(i)) );
        fr_err.push_back( getFakeRate_muon(1, lep_pt.at(i), lep_eta.at(i), muid) );
        pr_err.push_back( getEfficiency_muon(1, lep_pt.at(i), lep_eta.at(i)) );
      }
    }
    //==== If not, it's an electron
    else{
      fr.push_back( getFakeRate_electronEta(0, lep_pt.at(i), lep_eta.at(i), elid) );
      pr.push_back( getEfficiency_electron(0, lep_pt.at(i), lep_eta.at(i), elid) );
      fr_err.push_back( getFakeRate_electronEta(1, lep_pt.at(i), lep_eta.at(i), elid) );
      pr_err.push_back( getEfficiency_electron(1, lep_pt.at(i), lep_eta.at(i), elid) );
    }
  }

  //==== let a == f/(1-f)

  vector<float> a, fr_onlyLoose;

  for(unsigned int i=0; i<n_leptons; i++) a.push_back( fr.at(i)/(1.-fr.at(i)) );
  for(unsigned int i=0; i<n_leptons; i++){
    if(!isT.at(i)) fr_onlyLoose.push_back( a.at(i) );
  }
  n_Loose_not_Tight = fr_onlyLoose.size();

  //==== Initialise weight
  float this_weight=-1.;

  for(unsigned int i=0; i<fr_onlyLoose.size(); i++){
    this_weight *= -fr_onlyLoose.at(i);
  }

  if(!geterr) return this_weight;

  //==== d(a)/a = d(f)/f(1-f)
  //==== so, if w = a1*a2,
  //==== d(w)/w = d(a1)/a1 + d(a2)/a2

  vector<float> da_over_a;
  for(unsigned int i=0; i<n_leptons; i++) da_over_a.push_back( fr_err.at(i) / ( fr.at(i)*(1.-fr.at(i)) ) );
  float this_weight_err = 0.;
  for(unsigned int i=0; i<n_leptons; i++){
    if(!isT.at(i)) this_weight_err += da_over_a.at(i)*da_over_a.at(i);
  }

  this_weight_err = sqrt(this_weight_err);
  this_weight_err = this_weight_err*fabs(this_weight);

  return this_weight_err;

}


