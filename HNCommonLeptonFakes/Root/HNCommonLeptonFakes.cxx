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
  cout << "Accessing Fake Ntuple at " << path_to_root_files+"FakeRateDiLeptonHN.root" << endl;

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




float  HNCommonLeptonFakes::get_dilepton_ee_eventweight(std::vector<TLorentzVector> electrons, bool isel1tight, bool isel2tight){
  
  useGeV=true;

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
  if(!useGeV){    
    _el1_pt = _el1_pt/1000.;
    _el2_pt = _el2_pt/1000.;
  }
  
  if(_el1_pt > 100.) _el1_pt = 99.;
  if(_el2_pt > 100.) _el2_pt = 99.;


  float fr1(0.),fr2(0.),r1(0.),r2(0.);  

  if(_el1_pt< 25.) r1 = 0.88;
  else if(_el1_pt< 30.) r1 = 0.91;
  else if(_el1_pt< 40.) r1 = 0.93;
  else if(_el1_pt< 50.) r1 = 0.94;
  else  r1 = 0.99;

  if(_el2_pt< 25.) r2 = 0.88;
  else if(_el2_pt< 30.) r2 = 0.91;
  else if(_el2_pt< 40.) r2= 0.93;
  else if(_el2_pt< 50.) r2 = 0.94;
  else  r2 = 0.99;
  
  if(_el1_pt< 15.) fr1=0.25;
  else if(_el1_pt< 20) fr1=0.175;
  else if(_el1_pt< 25.) fr1=0.16;
  else if(_el1_pt< 35.) fr1=0.15;
  else  fr1=0.12;
  
  if(_el2_pt< 15.) fr2=0.25;
  else if(_el2_pt< 20) fr2=0.175;
  else if(_el2_pt< 25.) fr2=0.16;
  else if(_el2_pt< 35.) fr2=0.15;
  else  fr2=0.12;
  
  // Calculate event weight
  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, isel1tight, isel2tight);

  if(ev_weight!=ev_weight){
    cout << "(r1, r2, fr1, fr2) = (" << r1 << ", " << r2 << ", " <<  fr1 << ", " << fr2 << ")" << endl;
  }

  
  if(fabs(ev_weight) > 2.|| ev_weight == 0.&& r1!=1.){
    cout << "\n ---------------------------------  "<< endl;
    cout << "HNCommonLeptonFakes::Event Summary (ee) " << endl;
    cout << "weight = " << ev_weight << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "fr1 = " << fr1 << endl;    
    cout << "fr2 = " << fr2 << endl;

    cout << "lep1 (Tight)loose = " << isel1tight << endl;
    cout << "lep2 (Tight)loose = " << isel2tight << endl;

    cout << "el1 pT = " << _el1_pt << endl;
    cout << "el2 pT = " << _el2_pt << endl;
    cout << "el1 eta = " << _el1_eta << endl;
    cout << "el2 eta = " << _el2_eta << endl;
  }

  return ev_weight;

}

float  HNCommonLeptonFakes::get_dilepton_emu_eventweight(std::vector<TLorentzVector> muons,  std::vector<TLorentzVector> electrons, std::vector<TLorentzVector> jets,float met, bool ismutight, bool iseltight, bool is_muonHF,bool is_elconv, bool _el_primarytriggerpass, bool _el_secondarytriggerpass,bool _mu_primarytriggerpass,bool _mu_secondarytriggerpass, bool inGeV, bool use_kirill){

  useGeV=inGeV;
 
  float _mu_pt=muons.at(0).Pt();
  float _mu_eta=muons.at(0).Eta();
  
  float _el_pt= electrons.at(0).Pt();
  float _el_eta= electrons.at(0).Eta();
  

  bool _mu_triggerpass = (_mu_primarytriggerpass|| _mu_secondarytriggerpass);
  bool mujet_overlap=false;
  for(vector<TLorentzVector>::iterator it = jets.begin(); it!=jets.end();it++){
    if(muons.at(0).DeltaR(*it) < 0.4) mujet_overlap =true; 
  }
  
  int njets= jets.size();
  
  bool barrel = (fabs(_mu_eta ) < 1.05);
  
  TString etaCut  = fabs(_mu_eta)<0.75 ? "eta1" : (fabs(_mu_eta)<1.5 ? "eta2" : "eta3");

  TString trigname ="";
  TString isPASS ="";
  TString isBarrel ="";
  TString cut_r,cut_f;
  if(mujet_overlap){
    cut_f = TString("Fake_Rate_sm36__" )  +
      (is_muonHF     ? "HF_pt_close_"  : "LF_pt_close_" )  +
      (barrel   ? "barrel" : "endcap");
    
    cut_r = "Real_Eff_sm24OR36_pt_close";
  }
  else{
    cut_f = TString("Fake_Rate_sm24OR36__" )  +
      (is_muonHF     ? "HF_pt_"  : "LF_pt_" )  +
      (barrel   ? "barrel" : "endcap");
    
    cut_r = TString("Real_Eff_sm24OR36_ptnjets_") + etaCut;
  }
  
  


   
  if(!useGeV){    
    _mu_pt = _mu_pt/1000.;
    _el_pt = _el_pt/1000.;
  }
  
  //// Current electron histograms have pt max 200
  if(_el_pt > 200.) _el_pt = 199.;
  
 
  float fr1(0.),fr2(0.),r1(0.),r2(0.);  

  bool  is_lep1_tight(false);
  bool  is_lep2_tight(false);
  
  /// Check pt ordering
  if(muons.at(0).Pt() > electrons.at(0).Pt()) {
    
    is_lep1_tight = ismutight;
    is_lep2_tight = iseltight;

    r1 = getHSTEfficiency_sm(rsys, _mu_pt, njets, cut_r);
    fr1= getHSTFakeRate_sm(fsys, _mu_pt,mujet_overlap, cut_f);         ///////////////////
      
    if(use_kirill){      
      bool  _el_triggerpass = (_el_primarytriggerpass || _el_secondarytriggerpass);
      r2 = getEfficiency_electron_kirill(rsys, _el_pt, _el_eta, njets,_el_triggerpass);
      fr2= getFakeRate_electrons_kirill(fsys,_el_pt,_el_eta, njets, _el_triggerpass, is_elconv);         
    }
    else{
      if(!(_el_primarytriggerpass ||  _el_secondarytriggerpass || _mu_triggerpass )) return 0.;
      r2 = getEfficiency_electron_emu_lou(rsys, _mu_pt, _el_pt, _el_eta,_mu_triggerpass,_el_primarytriggerpass,_el_secondarytriggerpass);
      fr2 =getFakeRate_electrons_emu_lou (fsys,  _mu_pt, _el_pt, _el_eta, _mu_triggerpass, _el_primarytriggerpass,_el_secondarytriggerpass,is_elconv);
    }        
  }
  else {
    is_lep1_tight = iseltight;
    is_lep2_tight = ismutight;
    
    r2 = getHSTEfficiency_sm(rsys, _mu_pt, njets, cut_r);
    fr2= getHSTFakeRate_sm(fsys, _mu_pt,mujet_overlap, cut_f);


    if(use_kirill){      
      bool  _el_triggerpass = (_el_primarytriggerpass || _el_secondarytriggerpass);
      r1 = getEfficiency_electron_kirill(rsys, _el_pt, _el_eta, njets,_el_triggerpass);
      fr1= getFakeRate_electrons_kirill(fsys,_el_pt,_el_eta, njets, _el_triggerpass, is_elconv);         
    }
    else{
      if(!(_el_primarytriggerpass ||  _el_secondarytriggerpass || _mu_triggerpass )) return 0.;
      r1 = getEfficiency_electron_emu_lou(rsys, _mu_pt, _el_pt, _el_eta,_mu_triggerpass ,_el_primarytriggerpass,_el_secondarytriggerpass);
      fr1 =getFakeRate_electrons_emu_lou (fsys,  _mu_pt, _el_pt, _el_eta, _mu_triggerpass, _el_primarytriggerpass,_el_secondarytriggerpass,is_elconv);
    }          
  }
  
  
  
  if(double(CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight) ) != CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight)) {

    cout << "\n ---------------------------------------------------------------------- \n" << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    cout << fr1 << endl;
    cout << fr2 << endl;
    cout << "mu pt = " << _mu_pt << endl;
    cout << "mu eta = " << _mu_eta << endl;
    cout << "njets = " << njets << endl;
    cout << "MET = " << met << endl;
    cout << "el pt = " << _el_pt   << endl;
    cout << "el eta = " << _el_eta  << endl;
    cout << "el trigger = " << _el_primarytriggerpass << " " << _el_secondarytriggerpass << endl;
    cout << "mu trigger = " << _mu_triggerpass << endl;
    cout << "MET = " << met << endl;
    cout << "el1 conv = " << is_elconv << endl;
    
    cout << "muon isHF = " << is_muonHF << endl;
    cout << "njets = " << njets << endl;
    cout<< "close muon to jet = " << mujet_overlap << endl;    

    cout << "mu (Tight)loose = " << ismutight << endl;
    cout << "el (Tight)loose = " << iseltight << endl;
  }
  
  if(fabs(CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight)) > 2. || CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight) == 0. && r1!=1.){    
    cout << "\n ---------------------------------  "<< endl;
    cout << "HNCommonLeptonFakes::Event Summary (emu) " << endl;
    cout << "weight = " <<CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight)    << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "fr1 = " << fr1 << endl;
    cout << "fr2 = " << fr2 << endl;

    cout << "el pT = " << _el_pt << endl;
    cout << "mu pT = " << _mu_pt << endl;
    cout << "el eta = " << _el_eta << endl;
    cout << "mu eta = " << _mu_eta << endl;
    
    cout << "el trigger = " << _el_primarytriggerpass << " " << _el_secondarytriggerpass << endl;
    cout << "mu trigger = " << _mu_triggerpass << endl;
    cout << "MET = " << met << endl;
    cout << "el1 conv = " << is_elconv << endl;
    
    cout << "muon isHF = " << is_muonHF << endl;
    cout << "njets = " << njets << endl;
    cout<< "close muon to jet = " << mujet_overlap << endl;    

    cout << "mu (Tight)loose = " << ismutight << endl;
    cout << "el (Tight)loose = " << iseltight << endl;

  }
 
  
    // Calculate event weight  
  return CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismutight, iseltight);

}


float  HNCommonLeptonFakes::get_dilepton_mm_eventweight( std::vector<TLorentzVector> muons, std::vector<TLorentzVector> jets,bool ismu1tight, bool ismu2tight,bool isHF1, bool isHF2,bool inGeV, bool oldrates){
  
  useGeV=inGeV;
  if(muons.size()!=2) {
    cout << "DiLepton event weight requires 2 muons." << endl;
    return (0.);
  }
  
  float _mu1_pt=muons.at(0).Pt();
  float _mu1_eta=muons.at(0).Eta();
  float _mu2_pt=muons.at(1).Pt();
  float _mu2_eta=muons.at(1).Eta();

  bool mu1jet_overlap=false;
  bool mu2jet_overlap=false;
  for(vector<TLorentzVector>::iterator it = jets.begin(); it!=jets.end();it++){
    if(muons.at(0).DeltaR(*it) < 0.4) mu1jet_overlap =true; 
    if(muons.at(1).DeltaR(*it) < 0.4) mu2jet_overlap =true; 
  }
   
  int njets= jets.size();

  if(!useGeV){    
    _mu1_pt = _mu1_pt/1000.;
    _mu2_pt = _mu2_pt/1000.;
  }

  
  float fr1(0.),fr2(0.),r1(0.),r2(0.);  
  /// Get real efficiencies (pt max 200 set in function) uses tight zwindow: rsys sets systematic (0/1/-1)
  
  r1 = getEfficiency_muon(rsys,_mu1_pt, _mu1_eta,njets, "real_eff");
  r2 = getEfficiency_muon(rsys,_mu2_pt, _mu2_eta,njets, "real_eff");
 

  /// if using new rates (with fits) 
  fr1=getFakeRate_muons(fsys,isHF1,_mu1_pt, njets, _mu1_eta, mu1jet_overlap,"2mud0sigUB5_tight");
  fr2=getFakeRate_muons(fsys,isHF2,_mu2_pt, njets, _mu2_eta, mu2jet_overlap,"2mud0sigUB5_tight");    
  
  if(oldrates){
    fr1=getFakeRate_muonsold(fsys,isHF1,_mu1_pt, njets, _mu1_eta, mu1jet_overlap,"2mud0sigUB5_tight");
    fr2=getFakeRate_muonsold(fsys,isHF2,_mu2_pt, njets, _mu2_eta, mu2jet_overlap,"2mud0sigUB5_tight");      
  }
  

  float ev_weight = CalculateDiLepMMWeight(r1,fr1,r2,fr2, ismu1tight, ismu2tight);

  if(fabs(ev_weight) > 2.|| ev_weight == 0.){
    cout << "\n ---------------------------------  "<< endl;
    cout << "HNCommonLeptonFakes::Event Summary (mm) " << endl;
    cout << "weight = " << ev_weight << endl;
    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;
    cout << "fr1 = " << fr1 << endl;    
    cout << "fr2 = " << fr2 << endl;

    cout << "mu1 (Tight)loose = " << ismu1tight << endl;
    cout << "mu2 (Tight)loose = " << ismu2tight << endl;

    cout << "njets = " << jets.size() << endl;
    cout << "mu1 pT = " << _mu1_pt << endl;
    cout << "mu2 pT = " << _mu2_pt << endl;
    cout << "mu1 eta = " << _mu1_eta << endl;
    cout << "mu2 eta = " << _mu2_eta << endl;

  }

  return ev_weight;


}


float HNCommonLeptonFakes::getEfficiency_electron_emu_lou(int sys, float muon_pt, float el_pt, float el_eta, bool muon_triggerpass, bool primarytrigger_el, bool secondarytrigger_el){
  
  
  float eff_real(-100000000000.);  
  map<TString,TH2*>::const_iterator mapit;  
  map<TString,TH1*>::const_iterator mapit1D;  
  
  bool el_leading(true);
  if(muon_pt > el_pt) el_leading = false;
  
  TString file_name = "nom_";
  if(sys ==1) file_name = "realup_";
  if(sys ==-1) file_name = "realdown_";
  
  
  TString trigger_type ="";
  TString rate_type ="";

  
  if(primarytrigger_el) {      
    trigger_type ="primary";
    rate_type = "Analysis";
  }
  else{ 
    if(secondarytrigger_el) {      
      trigger_type ="secondary";
      rate_type = "Analysis";    
    }
    else{      
      trigger_type ="either";
      rate_type = "Loose";    
    }
  }
  

 if(primarytrigger_el) {      
  TString hist_name = file_name+ trigger_type +  "_realEff" + rate_type + "Trig_A_AL_TM_pT_eta";  
  mapit = _2DEfficiencyMap.find(hist_name);
  
  if(mapit!=_2DEfficiencyMap.end()){    
    //int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(el_pt,el_eta);  	
    int binx =  mapit->second->FindBin(el_pt,el_eta);  	
    eff_real =  mapit->second->GetBinContent(binx);    
  }
  else NoHist(hist_name); 
  
  }
 else{ 
   if(secondarytrigger_el) {      
     TString hist_name = file_name+ trigger_type +  "_realEff" + rate_type + "Trig_A_AL_TM_eta";  
     mapit1D = _EfficiencyMap.find(hist_name);
     
     if(mapit1D!=_EfficiencyMap.end()){    
       //int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(el_eta);  	
       int binx =  mapit1D->second->FindBin(el_eta);  	
	eff_real =  mapit1D->second->GetBinContent(binx);    
      }
      else NoHist(hist_name); 
    }
    else{      
      TString hist_name = file_name+ trigger_type +  "_realEff" + rate_type + "Trig_A_AL_TM_pT_eta";  
      mapit = _2DEfficiencyMap.find(hist_name);
      
      if(mapit!=_2DEfficiencyMap.end()){    
	//int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(el_pt,el_eta);  	
	int binx =  mapit->second->FindBin(el_pt,el_eta);  	
	eff_real =  mapit->second->GetBinContent(binx);    
      }
      else NoHist(hist_name);       
    }
  }
 

  return eff_real;
  
}



pair<float,float> HNCommonLeptonFakes::getEfficiency_electron_ee_lou(int sys, float lep1_pt, float lep2_pt, float lep1_eta, float lep2_eta, bool primarytrigger_lep1,  bool secondarytrigger_lep1, bool primarytrigger_lep2, bool secondarytrigger_lep2){
  
  float eff_real1(-100000000000.);
  float eff_real2(-100000000000.);
  
  map<TString,TH2*>::const_iterator mapit;  
  map<TString,TH1*>::const_iterator mapit1D;  
  
  if(lep1_pt < lep2_pt) cout << "Check leading / sub-leading inputs for electrons in HNCommonLeptonFakes package" << endl;
  
  TString file_name = "nom_";
  if(sys ==1) file_name = "realup_";
  if(sys ==-1) file_name = "realdown_";
  

  TString trigger_type1 ="";
  TString rate_type1 ="";
  TString trigger_type2 ="";
  TString rate_type2 ="";

 
  if(primarytrigger_lep1) {      
    trigger_type1 ="primary";
    rate_type1 = "Analysis";
  }
  else{ 
    if(secondarytrigger_lep1) {      
      trigger_type1 ="secondary";
      rate_type1 = "Analysis";    
    }
    else{      
      trigger_type1 ="either";
      rate_type1 = "Loose";    
    }
  }
    
  if(primarytrigger_lep2) {
    trigger_type2 ="primary";
    rate_type2 = "Analysis";
  }
  else{
    if(secondarytrigger_lep2) {
      trigger_type2 ="secondary";
      rate_type2 = "Analysis";
    }
    else{
      trigger_type2 ="either";
      rate_type2 = "Loose";
    }
  }



  if(! (primarytrigger_lep1 || secondarytrigger_lep1)  && !(primarytrigger_lep2 || secondarytrigger_lep2) ) return make_pair(0.,0.);
  


 if(primarytrigger_lep1) {      
   TString hist_name = file_name+ trigger_type1 +  "_realEff" + rate_type1 + "Trig_A_AL_TM_pT_eta";  
   mapit = _2DEfficiencyMap.find(hist_name);
  
   if(mapit!=_2DEfficiencyMap.end()){    
     int binx =  mapit->second->FindBin(lep1_pt,lep1_eta);  	
     eff_real1 =  mapit->second->GetBinContent(binx);    
  }
  else NoHist(hist_name); 
  
  }
  else{ 
    if(secondarytrigger_lep1) {      
      TString hist_name = file_name+ trigger_type1 +  "_realEff" + rate_type1 + "Trig_A_AL_TM_eta";  
      mapit1D = _EfficiencyMap.find(hist_name);
      
      if(mapit1D!=_EfficiencyMap.end()){    
	int binx =  mapit1D->second->FindBin(lep1_eta);  	
	eff_real1 =  mapit1D->second->GetBinContent(binx);    
      }
      else NoHist(hist_name); 
    }
    else{      
      TString hist_name = file_name+ trigger_type1 +  "_realEff" + rate_type1 + "Trig_A_AL_TM_pT_eta";  
      mapit = _2DEfficiencyMap.find(hist_name);
      
      if(mapit!=_2DEfficiencyMap.end()){    
	int binx =  mapit->second->FindBin(lep1_pt,lep1_eta);  	
	eff_real1 =  mapit->second->GetBinContent(binx);    
      }
      else NoHist(hist_name);       
    }
  }
 
 
 if(primarytrigger_lep2) {      
   TString hist_name = file_name+ trigger_type2 +  "_realEff" + rate_type2 + "Trig_A_AL_TM_pT_eta";  
   mapit = _2DEfficiencyMap.find(hist_name);
   
   if(mapit!=_2DEfficiencyMap.end()){    
     //int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(lep2_pt,lep2_eta);  	
     int binx =  mapit->second->FindBin(lep2_pt,lep2_eta);  	
     eff_real2 =  mapit->second->GetBinContent(binx);    
   }
   else NoHist(hist_name); 
   
 }
 else{ 
   if(secondarytrigger_lep2) {      
     TString hist_name = file_name+ trigger_type2 +  "_realEff" + rate_type2 + "Trig_A_AL_TM_eta";  
     mapit1D = _EfficiencyMap.find(hist_name);
     
     if(mapit1D!=_EfficiencyMap.end()){    
       //int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(lep2_eta);  	
       int binx =  mapit1D->second->FindBin(lep2_eta);  	
       eff_real2 =  mapit1D->second->GetBinContent(binx);    
     }
     else NoHist(hist_name); 
   }
   else{      
     TString hist_name = file_name+ trigger_type2 +  "_realEff" + rate_type2 + "Trig_A_AL_TM_pT_eta";  
     mapit = _2DEfficiencyMap.find(hist_name);
     
     if(mapit!=_2DEfficiencyMap.end()){    
       //int binx =  ((TH2*)(mapit->second->GetTotalHistogram()))->FindBin(lep2_pt,lep2_eta);  	
       int binx =  mapit->second->FindBin(lep2_pt,lep2_eta);  	
       eff_real2 =  mapit->second->GetBinContent(binx);    
     }
     else NoHist(hist_name);       
   }
 }
 


 return make_pair(eff_real1,eff_real2 );
  
  //*
  //  EE channel: assuming only non conversion electrons.
  //
  // electron 1 TRIGGER CONF			    electron 2  TRIGGER CONF			      ROOTFILE / histogram                        ROOTFILE / histogram
  //  
  //  %%%% BOTH MATCH: Unbiased/Unbiased %%%%
  //  ANY       				   ANY      					      effUnbiasedTrig_A_AL_TM_pT                  effUnbiasedTrig_A_AL_TM_pT
  //  
  //  %%% Leading matched, sub-leading unmatched: Pass/Unbiased %%%%
  //  EF_e60_medium1 &&  EF_e24vhi_medium1      NEITHER                                            Both.root/effAnalysisTrig_A_AL_TM_pT        effUnbiasedTrig_A_AL_TM_pT
  //  EF_e60_medium1 && !EF_e24vhi_medium1      NEITHER                                            Secondary.root/effAnalysisTrig_A_AL_TM_pT   effUnbianedTrig_A_AL_TM_pT  
  //  !EF_e60_medium1 &&  EF_e24vhi_medium1      NEITHER                                            Primary.root/effAnalysisTrig_A_AL_TM_pT     effUnbiasedTrig_A_AL_TM_pT
  //  
  //  
  //  %%% Leading unmatched, sub-leading matched: Fail/Pass %%%
  //  NEITHER                                    EF_e60_medium1 &&  EF_e24vhi_medium1               Either.root/effLooseTrig_A_AL_TM_pT         Both.root/effAnalysisTrig_A_AL_TM_pT
  //  NEITHER                                    EF_e60_medium1 && !EF_e24vhi_medium1               Either.root/effLooseTrig_A_AL_TM_pT         Secondary.root/effAnalysisTrig_A_AL_TM_pT
  // NEITHER                                   !EF_e60_medium1 &&  EF_e24vhi_medium1               Either.root/effLooseTrig_A_AL_TM_pT         Primary.root/effAnalysisTrig_A_AL_TM_pT
  //  
  //  %%%% BOTH FAIL %%%%
  //  Not including these events
  // 
  //
  // *////////////////////

  
}


float HNCommonLeptonFakes::getEfficiency_electron_kirill(int sys, float pt, float eta, int njet, bool passtrigger){

  map<TString,TH2*>::const_iterator mapit;  
    
  double eff_real(0.);  
 
  TString hist ="real_eff_el_";
  if(passtrigger) hist +="pass_ptetajet";
  else hist += "fail_ptetajet";
  
  if(njet==0 )hist += "0";
  else  hist += "1";
  
  mapit = _2DEfficiencyMap.find(hist);
  
  if(mapit!=_2DEfficiencyMap.end()){
    int binx=mapit->second->FindBin(pt,eta);  	
    eff_real =  mapit->second->GetBinContent(binx);    
  }
  else NoHist(hist); 
  
  //// INITIAL METHOD OF SYSTEMATICS
  if(sys==1) eff_real*=1.05;
  if(sys==-1) eff_real*=0.95;

  if(eff_real==0){
    cout << hist << endl;
    cout << mapit->second->FindBin(pt,eta) << endl;
    cout << "pt,eta = " << pt << ", " << eta << endl;
  }

  return eff_real;
  
}


float HNCommonLeptonFakes::getFakeRate_electrons_emu_lou(int sys, float muon_pt, float el_pt, float el_eta, bool muon_passtrigger, bool primarytrigger_el,  bool secondarytrigger_el, bool el_conv){

 float eff_fake(-100000000000.);
  
 map<TString,TH2*>::const_iterator mapit;  
 map<TString,TH1*>::const_iterator mapit1D;  
  
  bool el_leading(true);
  if(muon_pt > el_pt) el_leading = false;
  
  TString file_name = "nom_";
  if(sys ==1) file_name = "fakeup_";
  if(sys ==-1) file_name = "fakedown_";
  
  
  TString trigger_type ="";
  TString rate_type ="";

  if(primarytrigger_el) {      
    trigger_type ="primary";
    rate_type = "Analysis";
  }
  else{ 
    if(secondarytrigger_el) {      
      trigger_type ="secondary";
      rate_type = "Analysis";    
    }
    else{      
      trigger_type ="either";
      rate_type = "Loose";    
    }
  }
  

  
  if(primarytrigger_el) {     
    
    TString hist_name = file_name+ trigger_type +  "_eff" + rate_type + "Trig_A_AL_TM_pT_eta"; 
    if(el_conv) hist_name += "_Conv";
    mapit = _2DEfficiencyMap.find(hist_name);      
    if(mapit!=_2DEfficiencyMap.end()){
      int binx=mapit->second->FindBin(el_pt,el_eta);  	
      eff_fake =  mapit->second->GetBinContent(binx);                 
    }
    else NoHist(hist_name);     
    return eff_fake;
  }

  else{
    if(secondarytrigger_el) { 
      
      TString hist_name = file_name+ trigger_type +  "_eff" + rate_type + "Trig_A_AL_TM_eta";  
      if(el_conv) hist_name += "_Conv";
      mapit1D = _EfficiencyMap.find(hist_name);  
      if(mapit1D!=_EfficiencyMap.end()){
	int binx=mapit1D->second->FindBin(el_eta);  	
	eff_fake =  mapit1D->second->GetBinContent(binx);                 
      }
      else NoHist(hist_name);     
      return eff_fake;
    }
    else{
           
      TString hist_name = file_name+ trigger_type +  "_eff" + rate_type + "Trig_A_AL_TM_pT_eta";  
      if(el_conv) {
	hist_name += "_Conv";
	el_eta = fabs(el_eta);
      }
      mapit = _2DEfficiencyMap.find(hist_name);  
      if(mapit!=_2DEfficiencyMap.end()){
	int binx=mapit->second->FindBin(el_pt,el_eta);  	
	eff_fake =  mapit->second->GetBinContent(binx);                 
      }
      else NoHist(hist_name);     
      return eff_fake;            
    }
  }  

}


pair<float,float> HNCommonLeptonFakes::getFakeRate_electrons_ee_lou(int sys, float lep1_pt, float lep2_pt, float lep1_eta, float lep2_eta, bool primarytrigger_lep1,  bool secondarytrigger_lep1, bool primarytrigger_lep2, bool secondarytrigger_lep2, bool el1_conv, bool el2_conv){
  
  float eff_fake1(-100000000000.);
  float eff_fake2(-100000000000.);
  
  map<TString,TH2*>::const_iterator mapit;  
  map<TString,TH1*>::const_iterator mapit1D;  
  
  if(lep1_pt < lep2_pt) cout << "Check leading / sub-leading inputs for electrons in HNCommonLeptonFakes package" << endl;
  
  TString file_name = "nom_";
  if(sys ==1) file_name = "fakeup_";
  if(sys ==-1) file_name = "fakedown_";

  TString trigger_type1 ="";
  TString rate_type1 ="";
  TString trigger_type2 ="";
  TString rate_type2 ="";

  if(primarytrigger_lep1) {      
    trigger_type1 ="primary";
    rate_type1 = "Analysis";
  }
  else{ 
    if(secondarytrigger_lep1) {      
      trigger_type1 ="secondary";
      rate_type1 = "Analysis";    
    }
    else{      
      trigger_type1 ="either";
      rate_type1 = "Loose";    
    }
  }
  
  if(primarytrigger_lep2) {      
    trigger_type2 ="primary";
    rate_type2 = "Analysis";
  }
  else{ 
    if(secondarytrigger_lep2) {      
      trigger_type2 ="secondary";
      rate_type2 = "Analysis";    
    }
    else{      
      trigger_type2 ="either";
      rate_type2 = "Loose";    
    }
  }
  
  if(!(primarytrigger_lep1 || secondarytrigger_lep1 ) && !(primarytrigger_lep2 || secondarytrigger_lep2 )) return make_pair(0.,0.);
 

    
  if(primarytrigger_lep1) {      
    TString hist_name = file_name+ trigger_type1 +  "_eff" + rate_type1 + "Trig_A_AL_TM_pT_eta";
    if(el1_conv) hist_name += "_Conv";
    mapit = _2DEfficiencyMap.find(hist_name);
    
    if(mapit!=_2DEfficiencyMap.end()){
      int binx=mapit->second->FindBin(lep1_pt,lep1_eta);  	
      eff_fake1 =  mapit->second->GetBinContent(binx);    
    }
    else NoHist(hist_name); 
  }
  else{ 
    if(secondarytrigger_lep1) {      
      TString hist_name = file_name+ trigger_type1 +  "_eff" + rate_type1 + "Trig_A_AL_TM_eta";
      if(el1_conv) hist_name += "_Conv";
      mapit1D = _EfficiencyMap.find(hist_name);
      
      if(mapit1D!=_EfficiencyMap.end()){
	int binx=mapit1D->second->FindBin(lep1_eta);  	
	eff_fake1 =  mapit1D->second->GetBinContent(binx);    
      }
      else NoHist(hist_name); 
    }
    else{      
      TString hist_name = file_name+ trigger_type1 +  "_eff" + rate_type1 + "Trig_A_AL_TM_pT_eta";
      if(el1_conv) {
	hist_name += "_Conv";
	lep1_eta = fabs(lep1_eta);
      }
      mapit = _2DEfficiencyMap.find(hist_name);
      
      if(mapit!=_2DEfficiencyMap.end()){
	int binx=mapit->second->FindBin(lep1_pt, lep1_eta);  	
	eff_fake1 =  mapit->second->GetBinContent(binx);    
      }
      else NoHist(hist_name);  
    }
  }
 


   
  if(primarytrigger_lep2) {      
    TString hist_name = file_name+ trigger_type2 +  "_eff" + rate_type2 + "Trig_A_AL_TM_pT_eta";
    if(el2_conv) hist_name += "_Conv";
    mapit = _2DEfficiencyMap.find(hist_name);
    
    if(mapit!=_2DEfficiencyMap.end()){
      int binx=mapit->second->FindBin(lep2_pt,lep2_eta);  	
      eff_fake2 =  mapit->second->GetBinContent(binx);    
    }
    else NoHist(hist_name); 
  }
  else{ 
    if(secondarytrigger_lep2) {      
      TString hist_name = file_name+ trigger_type2 +  "_eff" + rate_type2 + "Trig_A_AL_TM_eta";
      if(el2_conv) hist_name += "_Conv";
      mapit1D = _EfficiencyMap.find(hist_name);
      
      if(mapit1D!=_EfficiencyMap.end()){
	int binx=mapit1D->second->FindBin(lep2_eta);  	
	eff_fake2 =  mapit1D->second->GetBinContent(binx);    
      }
      else NoHist(hist_name); 
    }
    else{      
      TString hist_name = file_name+ trigger_type2 +  "_eff" + rate_type2 + "Trig_A_AL_TM_pT_eta";
      if(el2_conv){
	hist_name += "_Conv";
	lep2_eta = fabs(lep2_eta);
      }
      mapit = _2DEfficiencyMap.find(hist_name);
      
      if(mapit!=_2DEfficiencyMap.end()){
	int binx=mapit->second->FindBin(lep2_pt, lep2_eta);  	
	eff_fake2 =  mapit->second->GetBinContent(binx);    
      }
      else NoHist(hist_name);  
    }
  }
 

  if(eff_fake1 < 0. || eff_fake1 ==0. || eff_fake1 > 0.7) {
    
    cout << eff_fake1 << endl;
    cout << "el1 pt = " << lep1_pt << endl;
    cout << "el1 eta = " << lep1_eta << endl;
    cout << "trigger = " << trigger_type1 << " " << rate_type1 << endl;
    cout << el1_conv << endl;
  }    
  if(eff_fake2 < 0. || eff_fake2 ==0. || eff_fake2 > 0.7) {
    cout << eff_fake2 << endl;
    cout << "el2 pt = " << lep2_pt << endl;
    cout << "el2 eta = " << lep2_eta << endl;
    cout << "trigger = " << trigger_type2 << " " << rate_type2 << endl;
    cout << el2_conv << endl;
  }    



  return make_pair(eff_fake1,eff_fake2 );

}

float HNCommonLeptonFakes::getFakeRate_electrons_kirill(int sys, float pt, float eta, int njet, bool triggerpass, bool el_conv){


  map<TString,TH1*>::const_iterator mapit;  
    
  double eff_fake(0.);  
 
  TString hist = "h_pt_trig";
  if(triggerpass) hist +="pass_";
  else hist += "fail_";
  
  if(el_conv)hist += "conv";
  else {
    if(fabs(eta) < 1.05) hist += "nonconv_barrel";
    else hist += "nonconv_endcap";
  }
 
  
  mapit = _EfficiencyMap.find(hist);
  
  if(mapit!=_EfficiencyMap.end()){
    int binx=mapit->second->FindBin(pt);  	
    eff_fake =  mapit->second->GetBinContent(binx);    
  }
  else NoHist(hist); 


  //// INITIAL METHOD OF SYSTEMATICS UPDATE NEEDED
  if(sys==1) eff_fake*=1.1;
  if(sys==-1) eff_fake*=0.7;

  return eff_fake;
  
}

float HNCommonLeptonFakes::getEfficiency_muon(int sys, float pt, float eta, int njets, TString region){
  
  map<TString,TH2*>::const_iterator mapit;  
  
  float eff_real(0.);
  if(pt > 200.) pt = 199.;

  TString s_sys="";
  if(sys ==1) s_sys = "_up";
  if(sys ==-1) s_sys = "_down";
 
  TString s_njet = "";
  if(njets==0) s_njet = "_ptetajet0";
  else if(njets==1)s_njet = "_ptetajet1";
  else if(njets<4) s_njet = "_ptetajet23";
  else s_njet = "_ptetajet4";
  
  
  mapit = _2DEfficiencyMap.find((region+ s_njet + s_sys).Data()); 

  if(mapit!=_2DEfficiencyMap.end()){
    int binx =  mapit->second->FindBin(pt,eta);  
    eff_real =  mapit->second->GetBinContent(binx);
  }
  else NoHist((region+ s_njet + s_sys));
     
  return eff_real;
}



float HNCommonLeptonFakes::getFakeRate_muons(int sys, bool isHF,float pt, int njets, float eta, bool nearjet, TString region, bool usefit){
  
  map<TString,TH1*>::const_iterator mapit1D;  
  
  float ptmax = (usefit ? 65.:50.);

  //// pt for fakes goes up to 80 GeV (use up to 50)
  if(nearjet && (pt > 300.)) pt = 300;
  if(!nearjet && (pt > ptmax)) pt = ptmax-1.; 


  TString s_sys ="";
  if(sys==1) s_sys= "_up";
  if(sys==-1) s_sys= "_down";

  TString cut; 
  if(nearjet){
    cut="_pt_close";
  }
  else{
    if(fabs(eta) < 1.05){
      if(isHF&&njets==1) cut += "_pt_nj1_barrel";
      if(isHF&&njets>1) cut += "_pt_gtnj1_barrel";
      if(!isHF) cut += "_pt_gtnj0_barrel";
    }
    else{
      if(isHF&&njets==1) cut += "_pt_nj1_endcap";
      if(isHF&&njets>1) cut += "_pt_gtnj1_endcap";
      if(!isHF) cut += "_pt_gtnj0_endcap";
    }    
  }
  
  if(isHF)region+="HF";
  else region += "LF";

  if(m_debug) cout << "Calculating Fakes with 2D jet/pT parameterization" << endl;
  
  double eff_fake=0.;    
  mapit1D = _EfficiencyMap.find("h_" + region + cut + s_sys);
    
  if(nearjet){
    if(usefit)eff_fake= GetFitfakeRate(pt, (region + cut+s_sys));      
    else {
      if(mapit1D!=_EfficiencyMap.end()){
	int binx=mapit1D->second->FindBin(pt); 	  
	eff_fake =  mapit1D->second->GetBinContent(binx);       
      }
      else NoHist("h_" + region + cut+s_sys); 
    }
  }
  else{    
    
    if(pt > 30.){    
      /// Get fake rate from fit
      if(usefit)eff_fake= GetFitfakeRate(pt, (region + cut+s_sys));      
      else {
	if(mapit1D!=_EfficiencyMap.end()){
	  int binx=mapit1D->second->FindBin(pt); 	  
	  eff_fake =  mapit1D->second->GetBinContent(binx);       
	}
	else NoHist("h_" + region + cut+ s_sys); 	  
      }
    }
    else{
      if(mapit1D!=_EfficiencyMap.end()){
	int binx=mapit1D->second->FindBin(pt); 	  
	eff_fake =  mapit1D->second->GetBinContent(binx);       
      }
      else NoHist("h_" + region + cut+s_sys); 
    }
  }
  
  if(njets == 0) eff_fake*= 1.09; // <eff_fake>_njet=x / <eff_fake>
  if(njets == 1) eff_fake*= 0.97;
    
  return eff_fake;
}


float HNCommonLeptonFakes::getFakeRate_muonsold(int sys, bool isHF,float pt, int njets,float eta, bool nearjet, TString region){
  
  map<TString,TH2*>::const_iterator mapit;  
  map<TString,TH1*>::const_iterator mapit1D;  
  
  if(nearjet && (pt > 300.)) pt = 300;
  if(!nearjet && (pt > 80.)) pt = 79;

  //// pt for fakes goes up to 80 GeV
  if((njets == 0) && (pt > 49.)) pt = 49.; /// 0 jet bin 50+ GeV has large contamination of real prompt muons. 
  if(njets > 6) njets=6; /// Only parameterise up to 6 jets (reduce ttbar)

  TString cut; 
  if(nearjet){
    cut="_pt_close";
  }

  if(!nearjet){
    cut="_ptnjets";
  }
  
  if(isHF) region+="HF";
  else region += "LF";

 
  if(m_debug) cout << "Calculating Fakes with 2D jet/pT parameterization" << endl;
  
  double eff_fake=0.;  
  
  mapit = _2DEfficiencyMap.find("h_" + region + cut);
  mapit1D = _EfficiencyMap.find("h_" + region + cut);
  
  if(nearjet){
    if(mapit1D!=_EfficiencyMap.end()){
      int binx=mapit1D->second->FindBin(pt);  	
      eff_fake =  mapit1D->second->GetBinContent(binx);    
    }
    else NoHist("h_" + region + cut); 
  }
  else{
    if(mapit!=_2DEfficiencyMap.end()){
      int binx=mapit->second->FindBin(pt,njets); 	  
      eff_fake =  mapit->second->GetBinContent(binx);       
    }
    else NoHist("h_" + region + cut); 
  }


  if(!isHF){
    if(pt < 20.){
      if(region.Contains("trigiso")) eff_fake*=1.2;
      else eff_fake*=1.4;
    }
    else if(pt< 35.){
      if(region.Contains("trigiso")) eff_fake*=1.2;
      else eff_fake*=1.4;
    }
    else if(pt < 50){      
      eff_fake*=1.1;
    }
  }
  else{ 
    if(region.Contains("trigiso")) eff_fake*=1.2;
    else eff_fake*=1.4;
  }
  



  if(sys==1) eff_fake*=1.3;
  if(sys==-1) eff_fake*=0.7;

  return eff_fake;
}



float HNCommonLeptonFakes::getHSTEfficiency_sm(int sys, float pt, int njets, TString cut){
  
  if(sys==1)  cut+="_ErrUp";
  if(sys==-1) cut+="_ErrDn";

  float eff_real = 0.0;
  
  if(!(cut.Contains("close"))){
    if(pt > 200.) pt = 199.;
    map<TString,TH2*>::const_iterator mapit;
    mapit = _2DEfficiencyMapHST.find(cut.Data());
    if(mapit!=_2DEfficiencyMapHST.end()){
      int binx =  mapit->second->FindBin(pt,njets);
      eff_real =  mapit->second->GetBinContent(binx);
    }
    else NoHist(cut, TString("getHSTEfficiency_sm (")+cut+")");
  }
  else{
    
    if(pt > 200.) pt = 199.;    
    map<TString,TH1*>::const_iterator mapit;
    mapit = _EfficiencyMapHST.find(cut.Data());
    if(mapit!=_EfficiencyMapHST.end()){
      int binx =  mapit->second->FindBin(pt);
      eff_real =  mapit->second->GetBinContent(binx);
    }
    else NoHist(cut, TString("getHSTEfficiency_sm (")+cut+")");
  }
  
  if(eff_real ==0.) {
    cout << cut << endl;
    cout << pt << " " << njets << endl;
  }

  return eff_real;
}

float HNCommonLeptonFakes::getHSTEfficiency(int isys, float pt, float eta, int njets, TString region){

  map<TString,TH2*>::const_iterator mapit;  
 
  float eff_real(0.);

  TString sys = "";
  if(isys==1) sys+="_HSTup";
  if(isys==-1) sys+="_HSTdown";
 
  if(njets==0) mapit = _2DEfficiencyMapHST.find((region+"_ptetajet0"+sys).Data());
  else if(njets==1) mapit = _2DEfficiencyMapHST.find((region+"_ptetajet1"+sys).Data());
  else if(njets<4) mapit = _2DEfficiencyMapHST.find((region +"_ptetajet23"+sys).Data());
  else  mapit = _2DEfficiencyMapHST.find((region+ "_ptetajet4"+sys).Data());        
  
  if(mapit!=_2DEfficiencyMapHST.end()){
    int binx =  mapit->second->FindBin(pt,eta);  
    eff_real =  mapit->second->GetBinContent(binx);
    

  }
  else NoHist("real_eff_pteta");
    

  
  return eff_real;

}




///////////  EMU function
float HNCommonLeptonFakes::getHSTFakeRate_sm(int sys, float pt, bool close_to_jet, TString cut){

  map<TString,TH1*>::const_iterator mapit;  
  if(!close_to_jet){
    if(pt > 50.) pt = 49.; /// 0 jet bin 50+ GeV has large contamination of real prompt muons. 
  }
  else{
    if(pt > 300.) pt = 299.; /// 0 jet bin 50+ GeV has large contamination of real prompt muons. 
  }
  
  if(sys==1)  cut = cut + "_ErrUp";
  if(sys==-1) cut = cut + "_ErrDn";
  
  mapit = _EfficiencyMapHST.find(cut);  
  
  float eff_fake = 0.0;
  if(mapit!=_EfficiencyMapHST.end()){
    int binx=mapit->second->FindBin(pt);  	
    eff_fake = mapit->second->GetBinContent(binx);
  }
  else NoHist(cut,"getHSTFakeRate_sm"); 

  return eff_fake;
}


///////////  MUMU function
float HNCommonLeptonFakes::getHSTFakeRate(int isys, bool isHF,float pt,float eta, int njets, bool nearjet, TString region){
  
  map<TString,TH1*>::const_iterator mapit1D;   
  
  TString sys = "";
  if(isys==1) sys+="_HSTup";
  if(isys==-1) sys+="_HSTdown";
  
  
  if(pt > 50.) pt = 49.; /// 0 jet bin 50+ GeV has large contamination of real prompt muons.
  if(njets > 6) njets=6; /// Only parameterise up to 6 jets (reduce ttbar)
  
  
  TString cut; 
  if(nearjet){
    cut="_pt_close";
  }
  else{
    if(fabs(eta) < 1.05){
      if(isHF&&njets==1) cut += "_pt_nj1_barrel"+sys;
      if(isHF&&njets>1) cut += "_pt_gtnj1_barrel"+sys;
      if(!isHF) cut += "_pt_gtnj0_barrel"+sys;
    }
    else{
        if(isHF&&njets==1) cut += "_pt_nj1_endcap"+sys;
        if(isHF&&njets>1) cut += "_pt_gtnj1_endcap"+sys;
        if(!isHF) cut += "_pt_gtnj0_endcap"+sys;
    }   
  }
  
  if(isHF)region+="HF";
  else region += "LF";
  
  double eff_fake=0.;   
  mapit1D = _EfficiencyMapHST.find("h_" + region + cut);
  
  if(mapit1D!=_EfficiencyMapHST.end()){
    int binx=mapit1D->second->FindBin(pt);       
    eff_fake =  mapit1D->second->GetBinContent(binx);       
  }
  else NoHist("h_" + region + cut); 
  
  if(njets == 0) eff_fake*= 1.09; // <eff_fake>_njet=x / <eff_fake>
  if(njets == 1) eff_fake*= 0.97;
   
  return eff_fake;
}



float HNCommonLeptonFakes::HSTWeightF(int sys, TLorentzVector muon, std::vector<TLorentzVector> jets, bool isHF, TString region){
  
  float _mu1_pt=muon.Pt();
  float _mu1_eta=muon.Eta();

  int njets= jets.size();
 
  _mu1_pt = _mu1_pt/1000.;  

  bool mu1jet_overlap=false;
  for(vector<TLorentzVector>::iterator it = jets.begin(); it!=jets.end();it++){
    if(muon.DeltaR(*it) < 0.4) mu1jet_overlap =true; 
  }
  float rateHST = getHSTFakeRate(sys, isHF,  _mu1_pt,_mu1_eta, njets, mu1jet_overlap, region);
  return rateHST;
}


float HNCommonLeptonFakes::HSTWeight_sm(int sys, float pt,bool isclose_tojet, TString cut){
  return getHSTFakeRate_sm(sys, pt, isclose_tojet,cut);
}


float HNCommonLeptonFakes::HSTWeight_Rsm(int sys, float pt_gev, int njets, TString cut){
  return getHSTEfficiency_sm(sys,pt_gev, njets, cut);
}

float HNCommonLeptonFakes::HSTWeightR(int sys, TLorentzVector muons, std::vector<TLorentzVector> jets, TString region){

  float _mu1_pt=muons.Pt();
  float _mu1_eta=muons.Eta();
  int njets= jets.size();

  _mu1_pt = _mu1_pt/1000.;
  
  float rateHST = getHSTEfficiency(sys,_mu1_pt, _mu1_eta,njets,region);

  return rateHST;
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

float HNCommonLeptonFakes::GetFitfakeRate(float pt, TString histname){


  float f(0.), p0(0.), p1(0.), p0err(0.), p1err(0.);
 

  if(histname.Contains("tightHF_pt_nj1_barrel")){
    p0 = -0.05218;
    p0err = 0.02854;
    p1 = 0.0031;
    p1err= 0.00094;
  }
  if(histname.Contains("tightHF_pt_nj1_endcap")){
    p0 = 0.013065;
    p0err = 0.027;
    p1 = 0.00148;
    p1err= 0.000872;
  }
  if(histname.Contains("tightHF_pt_gtnj1_barrel")){
    p0 = -0.04741;
    p0err =0.044;
    p1 = 0.00305;
    p1err= 0.00146;
  }
  if(histname.Contains("tightHF_pt_gtnj1_endcap")){
    p0 = 0.05375;
    p0err =0.0384;
    p1 = 0.000396;
    p1err= 0.00123;
  }
  if(histname.Contains("tightLF_pt_gtnj0_barrel")){
    p0 = -0.0932;
    p0err =0.0350;
    p1 = 0.00512;
    p1err= 0.00117;
  }  
  if(histname.Contains("tightLF_pt_gtnj0_endcap")){
    p0 = -0.0787;
    p0err = 0.0358;
    p1 = 0.00495;
    p1err= 0.00119;
  }
  if(histname.Contains("tightHF_pt_close")){
    p0 = -0.0783;
    p0err =0.0276;
    p1 = 0.00162;
    p1err= 0.000293;
  }  
  if(histname.Contains("tightLF_pt_close")){
    p0 = -0.005469;
    p0err =0.07090;
    p1 = 0.001478;
    p1err= 0.0007132;
  }
  
  

  if(histname.Contains("tight_trigisoHF_pt_nj1_barrel")){
    p0 = -0.105;
    p0err =0.0797;
    p1 = 0.00744;
    p1err= 0.00262;
  }
  if(histname.Contains("tight_trigisoHF_pt_nj1_endcap")){
    p0 = 0.0659;
    p0err =0.0685;
    p1 = 0.00279;
    p1err= 0.00221;
  }
  if(histname.Contains("tight_trigisoHF_pt_gtnj1_barrel")){
    p0 = 0.144;
    p0err =0.1504;
    p1 = 0.00744;
    p1err= 0.00262;
  }  
  if(histname.Contains("tight_trigisoHF_pt_gtnj1_endcap")){
    p0 = 0.157;
    p0err =0.0905;
    p1 = 0.000515;
    p1err= 0.00286;
  }  
  if(histname.Contains("tight_trigisoLF_pt_gtnj0_barrel")){
    p0 = -0.085;
    p0err = 0.089;
    p1 = 0.0085;
    p1err= 0.0029;
  }  
  if(histname.Contains("tight_trigisoLF_pt_gtnj0_endcap")){
    p0 = 0.0106;
    p0err =0.0798;
    p1 = 0.00539;
    p1err= 0.00263;
  }
  if(histname.Contains("tight_trigisoHF_pt_close")){
    p0 = -0.02932;
    p0err =0.2493;
    p1 = 0.001316;
    p1err= 0.002585;
  }
  if(histname.Contains("tight_trigisoLF_pt_close")){
    p0 = -0.3127;
    p0err =0.2683;
    p1 = 0.00419;
    p1err= 0.00258;
  }
     

  f = p0 + pt* p1;  

  return f;  
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
