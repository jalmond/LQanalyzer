#include "MCDataCorrections.h"

// std includes
#include <iostream>
#include <vector>
#include <string>

// ROOT includes
#include <TFile.h>

/// local includes
#include "Reweight.h"


using namespace snu;
using namespace std;

MCDataCorrections::MCDataCorrections() {
  
  corr_isdata=false;
  k_mcperiod=-1;

  string lqdir = getenv("LQANALYZER_DIR");
  rc =  new RoccoR(lqdir + "/data/rochester/80X/rcdata.2016.v3");  


  CorrectionMap.clear();
  CorrectionMapGraph.clear();
  
  string pileupdir = getenv("PILEUPFILEDIR");

  FillCorrectionHists();
  reweightPU = new Reweight((pileupdir + "/" + getenv("PUFILE")).c_str());       
}


MCDataCorrections::MCDataCorrections(bool isdata) {
  corr_isdata=isdata;
  MCDataCorrections();
}
  


MCDataCorrections::~MCDataCorrections(){
  delete rc;
  delete reweightPU;
  CorrectionMap.clear();
  CorrectionMapGraph.clear();
}


void MCDataCorrections::SetMCPeriod(int mcperiod){
  k_mcperiod=mcperiod;
}

void MCDataCorrections::SetIsData(bool isdata){
  corr_isdata=isdata;
}

void MCDataCorrections::PrintSummary(){
  //// summarize results
}




void MCDataCorrections::FillCorrectionHists(){

  string file = string(getenv("LQANALYZER_DIR")) + "/CATConfig/CattupleConfig/corrections_"+string(getenv("CATVERSION"))+".txt" ;
  cout << "Correction file = " << file << endl;
  ifstream corr_file(file.c_str());
  string sline;
  while(getline(corr_file,sline) ){
    std::istringstream is( sline );
    if(sline.find("###")!=string::npos) {  
      string tmp;
      is >> tmp;
      string label;
      is >> label;
      string dirname;
      is >> dirname;
      string filename;
      is >> filename;
      string histsname;
      is >> histsname;
      string histtype;
      is >> histtype;
      FillCorrectionHist(label,dirname,filename,histsname,histtype);
    }
    if(sline=="#END") break;
  }
}

void MCDataCorrections::FillCorrectionHist(string label, string dirname, string filename, string histsname, string histtype){

  TDirectory* origDir = gDirectory;

  if(TString(histtype).Contains("TGraphAsymmErrors")) {
    TFile *infile_sf = TFile::Open((string(getenv(dirname.c_str()))+ "/" + filename).c_str());
    CheckFile(infile_sf);
    TDirectory* tempDir = getTemporaryDirectory();
    tempDir->cd();
    TGraphAsymmErrors* tmp = (TGraphAsymmErrors*)infile_sf->Get(histsname.c_str())->Clone();
    CorrectionMapGraph[label] = tmp;
    infile_sf->Close();
    delete infile_sf;
    origDir->cd();
  }

  if(!TString(histtype).Contains("TH2")) return;
  TFile *infile_sf = TFile::Open((string(getenv(dirname.c_str()))+ "/" + filename).c_str());
  CheckFile(infile_sf);
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
  TH2F* tmp =  dynamic_cast<TH2F*> (( infile_sf->Get(histsname.c_str()))->Clone());
  CorrectionMap[label] = tmp;
  cout << "CorrectionMap["<<label <<"] = " << histsname << " (from " << getenv(dirname.c_str())<< "/" << filename<<")" << endl;
  infile_sf->Close();
  delete infile_sf;
  origDir->cd();
}


double MCDataCorrections::MuonTrackingEffScaleFactor(vector<snu::KMuon> mu){
  float sf= 1.;
  if(corr_isdata) return 1.;
  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    float mueta=itmu->Eta();
    if(CheckCorrectionGraph("TRACKING_EFF")){
      sf*= GetCorrectionGraph("TRACKING_EFF")->Eval(mueta);
    }
  }
  return sf;
}

double MCDataCorrections::MuonISOScaleFactor(TString muid, vector<snu::KMuon> mu,int sys){
  float sf= 1.;
  float sferr=1.;
  if(corr_isdata) return 1.;


  // ref https://indico.cern.ch/event/595070/contributions/2405098/attachments/1388788/2114715/TnPIso12Dic2016.pdf 

  TString tag = "";
  if(k_mcperiod < 6) tag = "_BCDEF";
  else tag = "_GH";



  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    float mupt=itmu->Pt();
    if(itmu->Pt() >120. )mupt=119.;
    if(itmu->Pt() < 20.) mupt=21.;


    if(CheckCorrectionHist("ISO"+tag +"_"+ muid)){

      sferr = double(sys)*GetCorrectionHist("ISO"+tag +"_"+ muid)->GetBinError( GetCorrectionHist("ISO"+tag +"_"+ muid)->FindBin( fabs(itmu->Eta()), mupt) );
      
      sf*= (1. + sferr)*GetCorrectionHist("ISO"+tag +"_"+ muid)->GetBinContent( GetCorrectionHist("ISO"+tag +"_"+ muid)->FindBin( fabs(itmu->Eta()), mupt) );
    }
  }

  return sf;
}

double MCDataCorrections::MuonScaleFactor(TString muid, vector<snu::KMuon> mu,int sys){
  float sf= 1.;
  float sferr=1.;
  if(corr_isdata) return 1.;
  
  // ref https://indico.cern.ch/event/595070/contributions/2405095/attachments/1388822/2114847/MC_12_12_2016.pdf

  TString tag = "";
  if(k_mcperiod < 6) tag = "_BCDEF";
  else tag = "_GH";



  double min_pt = 20., max_pt = 120.;
  if(muid=="MUON_HN_TRI_TIGHT"){
    min_pt = 5.;
    max_pt = 200.;
  }
  
  if(mu.size() == 0) return 1.;
  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    float mupt=itmu->Pt();

    if(itmu->Pt() < min_pt) mupt = min_pt+1.;
    if(itmu->Pt() > max_pt) mupt = max_pt-1.;

    if(CheckCorrectionHist("ID" +tag+ "_"+ muid)){
      sferr = double(sys)*GetCorrectionHist("ID" +tag+ "_"+ muid)->GetBinError( GetCorrectionHist("ID" +tag+ "_"+ muid)->FindBin( fabs(itmu->Eta()), mupt) );
      
      sf*=  (1. + sferr)* GetCorrectionHist("ID" +tag+ "_"+ muid)->GetBinContent( GetCorrectionHist("ID" +tag+ "_"+ muid)->FindBin( fabs(itmu->Eta()), mupt) );
    }
  }

  return sf;
}



double MCDataCorrections::TriggerScaleFactor( vector<snu::KElectron> el, vector<snu::KMuon> mu,  TString trigname, int direction){

  /// Currently only muon scale factors (single) are added by pog
  
  if(corr_isdata) return 1.;
  if(mu.size() == 1){

    TString s_ptthreshold="";
    float f1_ptthreshold=-999.;
    float f2_ptthreshold=-999.;

    
    TString tag = "";
    if(k_mcperiod < 6) tag = "_BCDEF";
    else tag = "_GH";
    
    if (trigname.Contains("HLT_IsoMu") || trigname.Contains("HLT_IsoTkMu"))  {
      if (trigname.Contains("24")){
	  s_ptthreshold = "24";
	  f1_ptthreshold = 24.;
	  f2_ptthreshold = 500.;
      }      
      else if (trigname.Contains("50")){
	s_ptthreshold= "50";
	f1_ptthreshold= 50.;
	f2_ptthreshold= 800.;
      }

      // G+H    https://twiki.cern.ch/twiki/pub/CMS/MuonWorkInProgressAndPagResults/2016.12.14_MuonPOGTriggerSF_KPLee_v1.pdf 
      // BtoF https://indico.cern.ch/event/608200/contributions/2452382/attachments/1401679/2156728/2017.02.05_MuonPOGTriggerSF_KPLee_v1.pdf 
      
      float mupt=mu.at(0).Pt();
      if(mupt >  f2_ptthreshold) mupt = (f2_ptthreshold-1.);
      if(mupt < f1_ptthreshold) mupt = (f1_ptthreshold - 1.);
      if(CheckCorrectionHist(("MUON_MU"+s_ptthreshold+"_TRIGGER"+tag).Data())){
	float sferr = double(direction)*GetCorrectionHist(("MUON_MU"+s_ptthreshold+"_TRIGGER"+tag).Data())->GetBinError(GetCorrectionHist(("MUON_MU"+s_ptthreshold+"_TRIGGER"+tag).Data())->FindBin( fabs(mu.at(0).Eta()), mupt) );
	return  (1. + sferr)*GetCorrectionHist(("MUON_MU"+s_ptthreshold+"_TRIGGER"+tag).Data())->GetBinContent( GetCorrectionHist(("MUON_MU"+s_ptthreshold+"_TRIGGER"+tag).Data())->FindBin(  fabs(mu.at(0).Eta()), mupt) );
      }
    }
  }
  return 1.;
}

double MCDataCorrections::ElectronScaleFactor( TString elid, vector<snu::KElectron> el, int sys){
  float sf= 1.;
  if(corr_isdata) return 1.;
  
  /// http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/RECO/passingRECO/egammaEffi.txt_egammaPlots.pdf

  std::string sid= "";
  
  for(vector<KElectron>::iterator itel=el.begin(); itel!=el.end(); ++itel) {
    float elpt=itel->Pt();
    if(elpt > 500.) elpt= 499.;
    if(elpt < 25.) elpt= 25;
    
    if(CheckCorrectionHist("ID_" + elid)){
      int bin =  GetCorrectionHist("ID_" + elid)->FindBin(fabs(itel->SCEta()), elpt);
      sf *= GetCorrectionHist("ID_" + elid)->GetBinContent(bin);
    }
  }

 
  return sf;
}

double MCDataCorrections::ElectronRecoScaleFactor(vector<snu::KElectron> el){
  
  // https://indico.cern.ch/event/604907/contributions/2452907/attachments/1401460/2139067/RecoSF_ApprovalMoriond17_25Jan2017.pdf

  if(corr_isdata) return 1.;
  float sf= 1.;
  for(vector<KElectron>::iterator itel=el.begin(); itel!=el.end(); ++itel) {
    float elpt= itel->Pt() ;
    if(itel->Pt() > 500.) elpt=499.;
    if(itel->Pt() < 25.) elpt=25.;
    if(CheckCorrectionHist("EL_RECO")){
      int bin =  GetCorrectionHist("EL_RECO")->FindBin(fabs(itel->SCEta()), elpt);
      sf *= GetCorrectionHist("EL_RECO")->GetBinContent(bin);
    }
  }
  
  return sf;
}


float MCDataCorrections::UserPileupWeight(snu::KEvent ev){
  
  if(corr_isdata) return 1.;
  return reweightPU->GetWeight(ev.nVertices(),TString(getenv("CATVERSION")));
}


float MCDataCorrections::PileupWeightByPeriod(snu::KEvent ev){
  cout << "k_mcperiod = " << k_mcperiod << endl;
  return ev.PeriodPileUpWeight(k_mcperiod);
  
}

float MCDataCorrections::CatPileupWeight(snu::KEvent ev, int syst){
  snu::KEvent::syst_dir sdir= snu::KEvent::central;
  if(syst < 0) sdir = snu::KEvent::down;
  if(syst > 0) sdir = snu::KEvent::up;
  
  return ev.PileUpWeight(sdir);

}



void MCDataCorrections::CheckFile(TFile* file){

  if(!file) exit(EXIT_FAILURE);
  return;
}


bool MCDataCorrections::CheckCorrectionHist(TString label){
  map<TString, TH2F*>::iterator  mapit = CorrectionMap.find(label);
  if (mapit!= CorrectionMap.end()){
    return true;
  }
  else return false;
}
bool MCDataCorrections::CheckCorrectionGraph(TString label){
  map<TString, TGraphAsymmErrors*>::iterator  mapit = CorrectionMapGraph.find(label);
  if (mapit!= CorrectionMapGraph.end()){
    return true;
  }
  else return false;
}

TGraphAsymmErrors* MCDataCorrections::GetCorrectionGraph(TString label){
  map<TString, TGraphAsymmErrors*>::iterator mapit = CorrectionMapGraph.find(label);
  if (mapit!= CorrectionMapGraph.end()){
    return mapit->second;
  }
  else{
    exit(0);
  }
}

TH2F* MCDataCorrections::GetCorrectionHist(TString label){
  map<TString, TH2F*>::iterator mapit = CorrectionMap.find(label);
  if (mapit!= CorrectionMap.end()){
    return mapit->second;
  }
  else{
    exit(0);
  }
}



void MCDataCorrections::CorrectMuonMomentum(vector<snu::KMuon>& k_muons, float genpt){
  
  for(std::vector<snu::KMuon>::iterator it = k_muons.begin(); it != k_muons.end(); it++){
    double scalefactor = 1.;
    if (corr_isdata) scalefactor = rc->kScaleDT(float(it->Charge()), it->Pt(), it->Eta(), it->Phi(),0,0);
    else {
	double u1 = gRandom->Rndm();
	double u2 = gRandom->Rndm();
	if ( genpt> 0.)  scalefactor = rc->kScaleFromGenMC(float(it->Charge()), it->Pt(), it->Eta(), it->Phi(), it->ActiveLayer(), genpt, u1,0, 0);
	else scalefactor = rc->kScaleAndSmearMC(float(it->Charge()), it->Pt(), it->Eta(), it->Phi(), it->ActiveLayer(), u1, u2, 0,0);
    }
    it->SetPtEtaPhiM( (scalefactor*it->Pt() ), it->Eta(), it->Phi(), it->M());
  }  
  
  
  /*
    
    -------------------------------------------------------------------------------------
    Following variations are provided currently
    -------------------------------------------------------------------------------------
    set        members     comment
    Default  0          1           default, reference based on madgraph sample, with pt distribution reweighted to data in |Y| bins. 
    Stat     1          100         pre-generated stat. variations; can include more (e.g. 400). RMS over these would give stat. uncertainty
    Zpt      2          1           derived without reweighting reference to data. Difference wrt central can be taken as systematics
    Ewk      3          1           Ad-hoc weighting applied to reference to change sw2 and Zw. Use for x-check for now. Need to compare with Powheg (may become default). 
    CorDm    4          5           varied profile mass window; one can take maximum deviation as systematics
    FitDm    5          5           varied fitting mass window; one can take maximum deviation as systematics
    LHEw     6          0           (please ignore for now)
    Run      7          7           derived from B,C,D,E,F,G,H; for cross-check study. No dramatic run denendence observed. MC's should be split by lumi if applied this way. 
    AMCNLO   8          1           derived from limited stat. amcnlo sample; for cross-check study
    -------------------------------------------------------------------------------------
  */

}



vector<TLorentzVector> MCDataCorrections::MakeTLorentz(vector<snu::KElectron> el){

  vector<TLorentzVector> tl_el;
  for(vector<KElectron>::iterator itel=el.begin(); itel!=el.end(); ++itel) {
    TLorentzVector tmp_em;
    tmp_em.SetPtEtaPhiM((*itel).Pt(),(*itel).Eta(),(*itel).Phi(),(*itel).M());
    tl_el.push_back(tmp_em);
  }
  return tl_el;
}

vector<TLorentzVector> MCDataCorrections::MakeTLorentz(vector<snu::KMuon> mu){
  
  vector<TLorentzVector> tl_mu;
  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    TLorentzVector tmp_mu;
    tmp_mu.SetPtEtaPhiM((*itmu).Pt(),(*itmu).Eta(),(*itmu).Phi(),(*itmu).M());
    tl_mu.push_back(tmp_mu);
  }
  return tl_mu;
}


vector<TLorentzVector> MCDataCorrections::MakeTLorentz(vector<snu::KJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiM((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).M());
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}


vector<TLorentzVector> MCDataCorrections::MakeTLorentz(vector<snu::KFatJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KFatJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiM((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).M());
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}

TDirectory* MCDataCorrections::getTemporaryDirectory(void) const
{

  
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:               
    std::stringstream dirname;
    dirname << "MCDataCorrections_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                        
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;
}



