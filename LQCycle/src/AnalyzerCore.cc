#include  "AnalyzerCore.h"


// System include(s):                                                                                                                                             
#include <cxxabi.h>
#include <cstdlib>

// STL include(s):                                                                                                                                                
#include <stdio.h>
#include <stdlib.h>     /* getenv */
#include <stdexcept>
#include <sstream>
#include <iostream>

// ROOT include(s):                                                                                                                                               

#include "TDirectory.h"
#include "TROOT.h"
#include "TClass.h"

/// Local includes                                                                                                                                                
//Plotting                                                                                                                                                        
#include "MuonPlots.h"
#include "ElectronPlots.h"
#include "JetPlots.h"
#include "SignalPlots.h"
//Core                                                                                                                                                            
#include "Reweight.h"
#include "EventBase.h"



using namespace snu;

AnalyzerCore::AnalyzerCore() : LQCycleBase(), MCweight(-999.) {

  Message("In AnalyzerCore constructor", INFO);
}

AnalyzerCore::~AnalyzerCore(){

}


  
void AnalyzerCore::CheckFile(TFile* file){

  if(file) cout << "Analyzer: File " << file->GetName() << " was found." << endl;
  else cout << "Analyzer  " << file->GetName()  << "  : ERROR Rootfile failed to open." << endl;

  if(!file) exit(0);
  return;
}

bool AnalyzerCore::PassTrigger(vector<TString> list, int& prescaler){

  return TriggerSelector(list, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler);

}

TDirectory* AnalyzerCore::GetTemporaryDirectory(void) const
{
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:                                              
    std::stringstream dirname;
    dirname << "WRHNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                                                       
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}

void AnalyzerCore::CloseFiles(){
  m_outputFile->SaveSelf( kTRUE );
  m_outputFile->Close();
  delete m_outputFile;
  m_outputFile = 0;
}



void AnalyzerCore::Message(TString message, LQMsgType type){
  m_logger <<  type << message << LQLogger::endmsg;
}


void AnalyzerCore::MakeCleverHistograms(histtype type, TString clhistname ){

  //// ELECTRON PLOTs                                                                                          
  if(type==elhist) mapCLhistEl[clhistname] = new ElectronPlots(clhistname);
  //// MUON PLOTs                                                                                              
  if(type==muhist) mapCLhistMu[clhistname] = new MuonPlots(clhistname);
  /// JET PLOTs                                                                                                
  if(type==jethist) mapCLhistJet[clhistname] = new JetPlots(clhistname);
  /// Signal plots                                                                                             
  if(type==sighist) mapCLhistSig[clhistname] = new SignalPlots(clhistname);

  return;
}

void AnalyzerCore::MakeHistograms(){
  //// Additional plots to make                                                                                
  maphist.clear();

  maphist["zpeak_mumu"] =  new TH1F("h_zpeak_mumu","Di-Muon Mass (GeV)",200,0,200);
  maphist["zpeak_ee"] =  new TH1F("h_zpeak_ee","Di-Muon Mass (GeV)",200,0,200);
  maphist["zpeak_tautau"] =  new TH1F("h_zpeak_tautau","Di-Muon Mass (GeV)",200,0,200);
  
}

bool AnalyzerCore::PassBasicEventCuts(){

  bool pass (true);

  if (isTrackingFailure || passTrackingFailureFilter) pass = false;
  if (!passBeamHaloFilterLoose) pass = false;
  if (passBadEESupercrystalFilter || passEcalDeadCellBoundaryEnergyFilter || passEcalDeadCellTriggerPrimitiveFilter || passEcalLaserCorrFilter) pass = false;
  if (!passHBHENoiseFilter) pass = false; // || passHcalLaserEventFilter) continue;                            
  return pass;
}

double AnalyzerCore::SetEventWeight(float w){

  //// IsData is only set temp here. In order to avoid making PUweight obj for data                            
  MCweight= w;
  if(MCweight == -999.) Message("ERROR IN EVENT WEIGHT", INFO);
  
  if (fChain == 0)  cout << "GoodBye!" << endl;

  /// Set number of events in runbackground.C                                                                  
  double e_weight = MCweight;
  return e_weight;
}

void AnalyzerCore::FillHist(TString histname, float value, float w ){

  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  /// Plots Z peak                                   
  else std::cout << histname << " was NOT found" << std::endl;
  return;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KMuon> muons, double w){

  if(type==muhist){
    map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.find(hist);
    if(mupit != mapCLhistMu.end()) mupit->second->Fill(w,muons);
    else cout << hist << " not found in mapCLhistMu" << endl;
  }
  else  cout << "Type not set to muhist, is this a mistake?" << endl;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KElectron> electrons, double rho, double w)\
{

  if(type==elhist){
    map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.find(hist);
    if(elpit !=mapCLhistEl.end()) elpit->second->Fill(w,electrons,rho);
    else cout << hist << " not found in mapCLhistEl" <<endl;
  }
  else  cout << "Type not set to elhist, is this a mistake?" << endl;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KJet> jets, double w){

  if(type==jethist){
    map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.find(hist);
    if(jetpit !=mapCLhistJet.end()) jetpit->second->Fill(w,jets);
    else cout << hist << " not found in mapCLhistJet" <<endl;
  }
  else  cout <<"Type not set to jethist, is this a mistake?" << endl;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, muons, electrons, jets,w);
    else cout << hist << " not found in mapCLhistSig" <<endl;
  }
  else  cout <<"Type not set to sighist, is this a mistake?" << endl;
}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, electrons, jets, w);
    else cout << hist << " not found in mapCLhistSig" <<endl;
  }
  else  cout <<"Type not set to sighist, is this a mistake?" << endl;
}



void AnalyzerCore::WriteCLHists(){

  for(map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.begin(); mupit != mapCLhistMu.end(); mupit++){
    Dir = m_outputFile->mkdir(mupit->first);
    m_outputFile->cd( Dir->GetName() );
    mupit->second->Write();
    m_outputFile->cd();
  }

  for(map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.begin(); elpit != mapCLhistEl.end(); elpit++)\
    {
      Dir = m_outputFile->mkdir(elpit->first);
      m_outputFile->cd( Dir->GetName() );
      elpit->second->Write();
      m_outputFile->cd();
    }

  for(map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.begin(); jetpit != mapCLhistJet.end(); jetpit++)\
    {
      Dir = m_outputFile->mkdir(jetpit->first);
      m_outputFile->cd( Dir->GetName() );
      jetpit->second->Write();
      m_outputFile->cd();
    }
  for(map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.begin(); sigpit != mapCLhistSig.end(); sigpit\
	++){
    Dir = m_outputFile->mkdir(sigpit->first);
    m_outputFile->cd( Dir->GetName() );
    sigpit->second->Write();
    m_outputFile->cd();
  }

  return;
}

void AnalyzerCore::WriteHists(){

  for(map<TString, TH1*>::iterator mapit = maphist.begin(); mapit != maphist.end(); mapit++){
    mapit->second->Write();
  }
  return;
}

TH1* AnalyzerCore::GetHist(TString hname){

  TH1* h = NULL;
  std::map<TString, TH1*>::iterator mapit = maphist.find(hname);
  if(mapit != maphist.end()) return mapit->second;
  else cout << hname << " was not found in map" << endl;

  return h;
}

void AnalyzerCore::OutPutEventInfo(int entry, int step){

  if (!(entry % step))  m_logger << INFO <<  "Processing entry " << entry << " weight = " << weight <<  LQLogger::endmsg;

  return;
}

