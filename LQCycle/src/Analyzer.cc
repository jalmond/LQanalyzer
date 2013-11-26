#include "Analyzer.h"

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


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (Analyzer);


Analyzer::Analyzer() :  AnalyzerCore() {
  
  Message("In Analyzer constructor", INFO);
  
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

  // To have the correct name in the log:
  SetLogName("Analyzer");
}


void Analyzer::InitialiseAnalysis() throw( LQError ) {
  
  jobtype jtype = ZTest;
  /// Initialise histograms
  MakeHistograms();
  
  Message("Made histograms", INFO);
  Message("Making clever hists for Z ->ll test code", INFO);
  
  //// Initialise Plotting class functions
  /// jtype sets which histograms to make    
  
  MakeCleverHistograms(muhist, "Zmuons");
  MakeCleverHistograms(elhist, "Zelectrons");
  

  TDirectory* origDir = gDirectory;
 
  ///////////////////////////////////////////////////////////////////////
  //////// For HN analysis  /////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //// FakeRate Input file
  //////////////////////////////////////////////////////////////////////
  string analysisdir = getenv("FILEDIR");  
  
  // Create a unique directory in memory to hold the histograms: 
  TFile *infile = TFile::Open((analysisdir+ "Total_FRcorr60_51_bis.root").c_str());
  CheckFile(infile);
  
  TDirectory* tempDir = GetTemporaryDirectory();
  tempDir->cd();  
  FRHist = dynamic_cast<TH2F*> (( infile->Get("h_FOrate3"))->Clone());  
  infile->Close();
  delete infile;
  origDir->cd();
  
  return;
}


void Analyzer::BeginEvent(float w)throw( LQError ) {  

  Message("In BeginEvent() " , INFO);
  //
  /// Set up weight for cycle (uses input luminosity or cross section if MC samples)
  //
  weight= SetEventWeight(w);
  ///
  // clear all output variable vectors
  //
  ClearOutputVectors();
}



void Analyzer::ExecuteEvents()throw( LQError ){
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts
  
  /// Trigger List (specific to muons channel)
  std::vector<TString> triggerslist;
  //triggerslist.push_back("HLT_Mu17_TkMu8_v");
  //if(!PassTrigger(triggerslist, prescale)) return;
  /// Correct MC for pileup
  if (MC_pu&&!isData)  weight = reweightPU->GetWeight(int(PileUpInteractionsTrue->at(0)))*MCweight;
  numberVertices = eventbase->GetBaseEvent().nVertices();

  if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
 
 
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  

  std::vector<snu::KMuon> muonColl;
  eventbase->GetMuonSel()->SetPt(20); 
  eventbase->GetMuonSel()->SetEta(2.4);
  //eventbase->GetMuonSel().SetRelIso(1000.);
  //eventbase->GetMuonSel().SetChiNdof(1000); 
  //eventbase->GetMuonSel().SetBSdxy(0.01);
  //eventbase->GetMuonSel().SetBSdz(0.10);
  //eventbase->GetMuonSel().SetDeposits(40.0,60.00);    
  eventbase->GetMuonSel()->Selection(out_muons);
    
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetPt(20);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  
  std::vector<snu::KElectron> electronColl;
  eventbase->GetElectronSel()->SetPt(20); 
  eventbase->GetElectronSel()->SetEta(2.5); 
  eventbase->GetElectronSel()->SetRelIso(0.15); 
  eventbase->GetElectronSel()->SetBSdxy(0.02); 
  eventbase->GetElectronSel()->SetBSdz(0.10);
  eventbase->GetElectronSel()->Selection(out_electrons); 
  eventbase->GetElectronSel()->Selection(electronColl); 

  ///// SOME STANDARD PLOTS /////
  ////  Z-> mumu            //////
  

  if (muonColl.size() == 2) {      
    KParticle Z = muonColl.at(0) + muonColl.at(1);
    if(muonColl.at(0).Charge() != muonColl.at(1).Charge()){      
      FillHist("zpeak_mumu", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(muhist, "Zmuons", muonColl, weight);
    } 
  }
  

  ///// SOME STANDARD PLOTS /////
  ////  Z-> ee              //////
  if (electronColl.size() == 2) {      
    KParticle Z = electronColl.at(0) + electronColl.at(1);
    if(electronColl.at(0).Charge() != electronColl.at(1).Charge()){      

      FillHist("zpeak_ee", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(elhist, "Zelectrons", electronColl, eventbase->GetBaseEvent().JetRho(), weight);
    } 
  }
  
  return;
}// End of execute event loop
  


void Analyzer::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  //
  // This function opens output root file and saves output trees
  //
  SaveOutputTrees(m_outputFile);
  m_outputFile->cd();
  m_logger<< INFO << "Opening output root file " << m_outputFile->GetName() << LQLogger::endmsg;
  //
  // All histograms are output into m_outputFile
  //
  WriteHists();/// writes all outputs in maphist
  WriteCLHists(); /// writes all hists set with MakeCleverHistograms       
  //
  // m_outputFile is closed and saved
  //
  CloseFiles();
}

void Analyzer::BeginCycle(TString output_file_name) throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  //
  // This function is called before the ExecuteEvents. It sets up necessary enviroment/root files
  //
  string analysisdir = getenv("FILEDIR");  
  if(!isData) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());

  //
  // Open the out put file if any output Tree variables are  specified
  //
  MakeOutPutFile(output_file_name, "LQTree");
  
  //DeclareVariable(out_muons, "Signal_Muons", "LQTree");
  m_logger << INFO << "Added Branch " << DeclareVariable(out_electrons, "Signal_Electrons", "LQTree") << LQLogger::endmsg;
  
  return;
  
}

Analyzer::~Analyzer() {
  
  delete FRHist;
 
  for(map<TString, TH1*>::iterator it = maphist.begin(); it!= maphist.end(); it++){
    delete it->second;
  }
  maphist.clear();
  
  for(map<TString, MuonPlots*>::iterator it = mapCLhistMu.begin(); it != mapCLhistMu.end(); it++){
    delete it->second;
  }
  mapCLhistMu.clear();

  for(map<TString, JetPlots*>::iterator it = mapCLhistJet.begin(); it != mapCLhistJet.end(); it++){
    delete it->second;
  }
  mapCLhistJet.clear();
  
  for(map<TString, ElectronPlots*>::iterator it = mapCLhistEl.begin(); it != mapCLhistEl.end(); it++){
    delete it->second;
  }
  mapCLhistEl.clear();
  
  for(map<TString, SignalPlots*>::iterator it = mapCLhistSig.begin(); it != mapCLhistSig.end(); it++){
    delete it->second;
  }
  mapCLhistSig.clear();
  
  if(!isData)delete reweightPU;

 }



void Analyzer::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  
  /**
   *  Remove//Overide this AnalyzerCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void Analyzer::EndEvent()throw( LQError ){

  FillOutTree();
  delete eventbase;

}

void Analyzer::ClearOutputVectors(){
  
  out_muons.clear();
  out_electrons.clear();
}


void Analyzer::SetUpEvent(Long64_t kentry)throw( LQError ){
  
  ClearOutputVectors();
  OutPutEventInfo(kentry, 10000); /// output event info every X events wil running
  if (!fChain) cout<<"Problem with fChain"<<endl;

  int nbytes = fChain->GetEntry(kentry,0); 

  snu::KEvent eventinfo = GetEventInfo(); 

  LQEvent lqevent(GetAllMuons(), GetAllElectrons(), GetAllTaus(),GetAllJets(), GetTruthParticles(), eventinfo);  
  isData = eventinfo.IsData();
  
  eventbase = new EventBase(lqevent); 

  return;
}


