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
#include "TH2.h"
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
    
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  
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




float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, int njets, bool isel1tight, bool isel2tight){
  
  if(electrons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }
  
  float _el1_pt=electrons.at(0).Pt();
  float _el2_pt=electrons.at(1).Pt();
  
  //// vectors need to be ordered in pT
  if(_el1_pt < _el2_pt) return -100000000000.;

 
  float _el1_eta=electrons.at(0).Eta();
  float _el2_eta=electrons.at(1).Eta();

  if(m_debug){
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
  }
  
  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_el2_pt > 100.) _el2_pt = 99.;


  float fr1(0.),fr2(0.),r1(0.),r2(0.);  

  r1 = getEfficiency_electron(0,_el1_pt, _el1_eta);
  r2 = getEfficiency_electron(0,_el2_pt, _el2_eta);

  fr1= getFakeRate_electron(0,_el1_pt, _el1_eta); 
  fr2= getFakeRate_electron(0,_el2_pt, _el2_eta); 
  
  if(njets==0) fr1 = fr1*1.45;
  if(njets==0) fr2 = fr2*1.45;

  
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

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



float HNCommonLeptonFakes::getFakeRate_electron(int sys,float pt, float eta ){
  float eff_fake=0.;

  if(fabs(eta) > 2.5) return -9999999.;
  if(pt < 15) return -999999.;
  
  //// will add eta depeance soon
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
  
  float up_down=1.;
  if(sys == -1) up_down = 1.;
  
  if(sys !=0) {
    float err=0.;
    if(fabs(eta) < 0.8){
      if((pt < 20.))  err=0.007;
      else if(pt < 25) err= 0.004;
      else if(pt < 30) err= 0.004;
      else if(pt < 35) err= 0.004;
      else if(pt < 45) err= 0.011;
      else err= 0.032;
    }
    else if(fabs(eta) < 1.479){
      if((pt < 20.))  err=0.008;
      else if(pt < 25) err= 0.005;
      else if(pt < 30) err= 0.004;
      else if(pt < 35) err= 0.008;
      else if(pt < 45) err= 0.013;
      else err= 0.039;
    }
    else if(fabs(eta) < 2.){
      if((pt < 20.))  err=0.011;
      else if(pt < 25) err= 0.007;
      else if(pt < 30) err= 0.006;
      else if(pt < 35) err= 0.010;
      else if(pt < 45) err= 0.019;
      else err= 0.039;
    }
    else if(fabs(eta) < 2.5){
      if((pt < 20.))  err=0.0047;
      else if(pt < 25) err= 0.012;
      else if(pt < 30) err= 0.013;
      else if(pt < 35) err= 0.019;
      else if(pt < 45) err= 0.031;
      else err= 0.117;
    }
  
    eff_fake = eff_fake + (up_down*err);
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
  for(map<TString, TH2*>::iterator mit = _2DEfficiencyMap.begin(); mit != _2DEfficiencyMap.end(); mit++){
    cout << mit->first <<" " << mit->second << endl;    
  }  
  
  cout << "Possible _EfficiencyMapHST hists are : " << endl;
  for(map<TString, TH1*>::iterator mit = _EfficiencyMapHST.begin(); mit != _EfficiencyMapHST.end(); mit++){
    cout << mit->first << endl;  
  }

  cout << "Possible _2DEfficiencyMapHST hists are : " << endl;
  for(map<TString, TH2*>::iterator mit = _2DEfficiencyMapHST.begin(); mit != _2DEfficiencyMapHST.end(); mit++){
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
  double alpha = 1./((r1- fr1)*(r2- fr2));

  // Initialise weight
  float w_mm=-999.;
    
  // Terms for RF and FR events from MM
  double termTT = alpha*(r1*fr2*(fr1-1.)*(1.-r2) + (fr1*r2*(r1-1.)*(1.-fr2)));
  double termTL = alpha*(r1*fr2*((1-fr1)*r2) + (fr1*r2*(1.-r1)*fr2));
  double termLT = alpha*(r1*fr2*(fr1*(1.-r2))+ (fr1*r2*(1.-fr2)*r1));
  double termLL = -2.*alpha*(r1*fr2*(fr1*r2));
  
  
  // Term for FF events
  termTT += alpha*fr1*fr2*((1.-r1)*(1.-r2));
  termTL += alpha*fr1*fr2*r2*(r1-1.);
  termLT += alpha*fr1*fr2*r1*(r2-1.);
  termLL += alpha*r1*r2*(fr1*fr2);

  
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
