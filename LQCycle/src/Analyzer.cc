#include "Analyzer.h"

// STL include(s):
#include <stdio.h>  
#include <stdlib.h>     /* getenv */
#include <stdexcept>
#include <sstream>
#include <iostream>

// ROOT include(s): 
#include "TDirectory.h"

using namespace::snu;

Analyzer::Analyzer(jobtype jtype) {
  _jtype = jtype;
  std::getchar();
  Initialise(jtype);
  std::cout << "Initialised" << std::endl;
  std::getchar();
}


void Analyzer::Initialise(jobtype jtype){
    
  /// Initialise histograms
  MakeHistograms(jtype);

  std::cout << "Made histograms" << std::endl;
  std::getchar();
  if(jtype== ZTest){    
    cout << "Making clever hists for Z ->ll test code" << endl;
    //// Initialise Plotting class functions
    /// jtype sets which histograms to make    

    MakeCleverHistograms(muhist, "Zmuons");
    MakeCleverHistograms(elhist, "Zelectrons");
  }
  else if(jtype == HNmm){
    MakeCleverHistograms(muhist, "TightMuons");
    MakeCleverHistograms(jethist, "AnalysisJets");
    MakeCleverHistograms(sighist, "Signal");
  }
  else {
    cout << "No type set for histogram maker" << endl;
  }
  
  std::cout << "Made new hists" << std::endl;
  std::getchar();

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
  ///////////////////////////////////////////////////////////////////////
  ////  Inital settings for running on samples
  entrieslimit = -1; /// Set default to all events
  ///////////////////////////////////////////////////////////////////////

  return;
}


//////////////////////////////////////////////////////////////////////
//// List of several loops to call
////////////////////////////////////////////// ////////////////////////
/// Jobs set with enum jobtype:
/// enum jobtype {ZTest,HNee, HNmm, HNFakeBkgmm, HNFakeBkgee};
/// TestLoop runs basic Z->ee, Z->mm, Z->tautau code
/// HNmmLoop runs HN MM channel results
/// HNeeLoop runs HN MM channel results
/// HNFakeBkgee
/// HNFakeBkgmm
/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void Analyzer::Run(){

  /// Initialise event cycle :
  /// sets weight and loads all necessary rootfiles
  InitialiseCycle();
  std::cout << "Initialised cycle" << std::endl;
  std::getchar();

  /// Decide which Cycle to run
  if(_jtype == ZTest) TestLoop();
  else if(_jtype == HNmm) HNmmLoop();
  else cout << "Error in setting Job Type in Analyzer constructor; " << endl;

  
  EndCycle();
  
}


//  TEST loop for Z to mumu/ee/tautau 
void Analyzer::TestLoop() {  
  
  //vector<snu::KMuon> kmuons; 
  //TTree * tree = new TTree("SKTree","test");
  //  tree->Branch("TestMuons", "vector<snu::KMuon>" &kmuons);
  
  ///////////////////////////////////////////////////////////////////////                                                                                                   
  ///  START OF EVENT LOOP                                                                                                                                        
  ///////////////////////////////////////////////////////////////////////////        
    for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {    
      if(jentry ==0) std::cout << "setting up event Chain" << std::endl;
      if(jentry ==0) std::getchar();
      SetUpEvent(jentry);
      if(jentry ==0)std::cout << "Setup event" << std::endl;
      if(jentry ==0)std::getchar();
      ExecuteEvent();
      if(jentry ==0) std::cout << "executed event" << std::endl;
      if(jentry ==0)std::getchar();
      EndEvent();
      if(jentry ==0) std::cout << "finished event" << std::endl;
      if(jentry ==0)std::getchar();
      if(jentry ==50000)std::getchar();
      if(jentry ==100000)std::getchar();
      if(jentry ==200000)std::getchar();
  } 
}

void Analyzer::ExecuteEvent(){
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts
    
  /// Trigger List (specific to muons channel)
  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Mu17_TkMu8_v");
  if(!PassTrigger(triggerslist, prescale)) return;
  /// Correct MC for pileup
  
  if (MC_pu&&!isData)  weight = reweightPU->GetWeight(int(PileUpInteractionsTrue->at(0)))*MCweight;
  numberVertices = eventbase->GetBaseEvent().nVertices();
  if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  
  if(eventbase->GetBaseEvent().MET() > 50) return;
  
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
  eventbase->GetMuonSel()->Selection(muonColl);
  
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
  

//  TEST loop for Z to mumu 
void Analyzer::HNmmLoop() {

  //// This is a loop for running over Drell Yan MC OR data events and plotting invariant mass of mass peak
  weight= SetEventWeight();  

  string analysisdir = getenv("FILEDIR");
  if(!isData)reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  ///////////////////////////////////////////////////////////////////////
  ///  START OF EVENT LOOP
  ///////////////////////////////////////////////////////////////////////////

  int i_dimu_evNmv(0), i_dimu(0), i_dimu_vertexmismatch(0), i_dimu_faild0sig(0), i_dimu_tight(0);
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {
    
    SetUpEvent(jentry); 

    if(!PassBasicEventCuts()) continue;     /// Initial event cuts
    
    /// Trigger List (specific to muons channel)
    std::vector<TString> triggerslist;
    triggerslist.push_back("HLT_Mu17_TkMu8_v");
    if(!PassTrigger(triggerslist, prescale)) continue;
      
    /// Correct MC for pileup
    if (MC_pu&&!isData)  weight = reweightPU->GetWeight(int(PileUpInteractionsTrue->at(0)))*MCweight;
    
    numberVertices = eventbase->GetBaseEvent().nVertices();
    if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) continue; //// Make cut on event wrt vertex

    ///  use selection code (which returns a similar class vector with selected cuts)     
    if(eventbase->GetBaseEvent().MET() > 50) continue;

    //// want to add more selection options ( )
    std::vector<snu::KMuon> muonColl;
    std::vector<snu::KMuon> muonCollIso;
    eventbase->GetMuonSel()->SetPt(20); 
    eventbase->GetMuonSel()->SetEta(2.4);
    eventbase->GetMuonSel()->Selection(muonColl);
    eventbase->GetMuonSel()->SetRelIso(1000.);
    eventbase->GetMuonSel()->SetChiNdof(1000); 
    eventbase->GetMuonSel()->SetBSdxy(0.01);
    eventbase->GetMuonSel()->SetBSdz(0.10);
    eventbase->GetMuonSel()->SetDeposits(40.0,60.00);    
    eventbase->GetMuonSel()->Selection(muonCollIso);


    std::vector<snu::KJet> jetColl;
    //// List of cuts                                                                                                                                                                
    eventbase->GetJetSel()->SetPt(20);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->Selection(jetColl);

    if(muonColl.size() ==2){
      if(muonColl.at(0).Charge() == muonColl.at(1).Charge()){
	i_dimu++;
	
	if(muonCollIso.size()==2) i_dimu_tight++;
	for(unsigned int m=0; m < muonColl.size() ; m++){
	  double minmujetdR=1000000.;
	  double jetpt = 0.;
	  int nclose=0;
	  for(unsigned int j=0; j < jetColl.size() ; j++){
	    if(muonColl.at(m).DeltaR(jetColl.at(j)) < 0.4){
	      if(muonColl.at(m).DeltaR(jetColl.at(j)) < minmujetdR ){
		minmujetdR = muonColl.at(m).DeltaR(jetColl.at(j));
		jetpt =  jetColl.at(j).Pt();
		nclose += 1;
	      }
	    }
	  }
	  if(nclose> 1){
	    cout << "Muon has " << nclose << " jets within 0.4 dR " << endl;
	    cout << "Muon " << m << " has dR with jet = " << minmujetdR << endl;
	    cout << "Muon pt = " << muonColl.at(m).Pt() << " jet pt = " <<  jetpt << endl;
	  }
	}
	  
	
	//cout << "muon 1 dxy = " << muonCollIso.at(0).dXY() <<  "  vertex dist =  " << muonCollIso.at(0).VertexDistXY()<<endl;
	//cout << "muon 2 dxy = " << muonCollIso.at(1).dXY() << "  vertex dist =  " << muonCollIso.at(1).VertexDistXY()<< endl;
	
	
	if(muonColl.at(0).MuonVertexIndex() != eventbase->GetBaseEvent().VertexIndex()) i_dimu_evNmv++;
	if(muonColl.at(0).MuonVertexIndex() != muonColl.at(1).MuonVertexIndex()){
	  
	  i_dimu_vertexmismatch++;
	  cout << "\n " << endl;
	  cout << "Event Summary " << endl;
	  cout << "Vertex Index = " << eventbase->GetBaseEvent().VertexIndex() << endl;
	  cout << "Vertex X = " << eventbase->GetBaseEvent().VertexX() << endl;
	  cout << "Vertex Y = " << eventbase->GetBaseEvent().VertexY() << endl;
	  cout << "Vertex Z = " << eventbase->GetBaseEvent().VertexZ() << endl;
	  
	  cout << "Muon 1 vertex Index = " << muonColl.at(0).MuonVertexIndex() << endl;
	  cout << "Muon 2 vertex Index = " << muonColl.at(1).MuonVertexIndex() << endl;
	}
	if((muonColl.at(0).dXY()/muonColl.at(0).D0Err()) > 3.0 || (muonColl.at(1).dXY()/muonColl.at(1).D0Err()) > 3.0) i_dimu_faild0sig++;
	
	
	cout << "Number of muon removed with tight vertex cut = " << i_dimu_tight << " " << i_dimu << endl;
	cout << "Number of muon removed with same vertex cut = " << i_dimu_vertexmismatch << " " << i_dimu << endl;
	cout << "Number of muon removed with d0sig cut = " << i_dimu_faild0sig  << " " << i_dimu << endl;
	cout << "Number of events where  muon vertex is not from event vertex = " << i_dimu_evNmv << " " << i_dimu << endl;
      }//    if(!event_info.IsPrimaryVertex()) cout << "NOT PRIMARY VERTEX" << endl;
    }
    
    
    std::vector<snu::KElectron> electronColl;
    eventbase->GetElectronSel()->SetPt(20); 
    eventbase->GetElectronSel()->SetEta(2.5); 
    eventbase->GetElectronSel()->SetRelIso(0.15); 
    eventbase->GetElectronSel()->SetBSdxy(0.02); 
    eventbase->GetElectronSel()->SetBSdz(0.10);
    eventbase->GetElectronSel()->Selection(electronColl); 

    
    
     ///// SOME STANDARD PLOTS /////
    if (muonColl.size() == 2) {      
      KParticle Z = muonColl.at(0) + muonColl.at(1);
      if(muonColl.at(0).Charge() == muonColl.at(1).Charge()){      
      } 
    }
    
    if (muonCollIso.size() == 2) {

      if(muonCollIso.at(0).Charge() == muonCollIso.at(1).Charge()){	
      }
    }
    
    
    EndEvent();
  }// End of event loop
  
  OpenPutputFile();  
  
  WriteHists();
  WriteCLHists();

  outfile->Close();

}


void Analyzer::EndCycle(){
  
  OpenPutputFile();
  WriteHists();/// writes all outputs in maphist
  WriteCLHists(); /// writes all hists set with MakeCleverHistograms       
  outfile->Close();
}

void Analyzer::InitialiseCycle(){
  
  cout << "Initilising Cycle : " << _jtype<< endl;
  weight= SetEventWeight();
  
  string analysisdir = getenv("FILEDIR");  
  if(!isData) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());

  return;
}


///  START OF HNmuon loop

void Analyzer::Loop() {
  
  
  return;

}


void Analyzer::Run(TTree* tree){

  Data* a= new Data();
  a->Init(tree);

  for(Long64_t i=0; i < 500000; i++){
    if (!(i % 1000))cout << "Entry "  << i << endl;
    a->GetEntry(i);
  }

  delete a;

  return;
}

Analyzer::~Analyzer() {

  for(map<TString, TH1*>::iterator it = maphist.begin(); it!= maphist.end(); it++){
    delete it->second;
  }
  maphist.clear();
  
  for(map<TString, MuonPlots*>::iterator it = mapCLhistMu.begin(); it != mapCLhistMu.end(); it++){
    delete it->second;
  }
  mapCLhistMu.clear();

  for(map<TString, JetPlots*>::iterator it = mapCLhistJet.begin(); it != mapCLhistJet.end(); it++){
    //delete it->second;
  }
  mapCLhistJet.clear();
  
  for(map<TString, ElectronPlots*>::iterator it = mapCLhistEl.begin(); it != mapCLhistEl.end(); it++){
    //delete it->second;
  }
  mapCLhistEl.clear();
  
  for(map<TString, SignalPlots*>::iterator it = mapCLhistSig.begin(); it != mapCLhistSig.end(); it++){
    //delete it->second;
  }
  mapCLhistSig.clear();
  
  if(!isData)delete reweightPU;
  delete outfile;

 }

void Analyzer::NEvents(Long64_t n_events){
  entrieslimit =  n_events;
  return;
}


void Analyzer::CheckFile(TFile* file){
  
  if(file) cout << "Analyzer: File " << file->GetName() << " was found." << endl;
  else cout << "Analyzer  " << file->GetName()  << "  : ERROR Rootfile failed to open." << endl;
  
  if(!file) exit(0);
  return;
}

bool Analyzer::PassTrigger(vector<TString> list, int& prescaler){
  
  return TriggerSelector(list, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler);
  
}

TDirectory* Analyzer::GetTemporaryDirectory(void) const
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
  


void Analyzer::SetName(TString name, Int_t version, TString dir) {

  string out_dir = getenv("LQANALYZER_OUTPUT_PATH");
  if(!dir.Contains("NULL")) out_dir = dir;
  completename = TString(out_dir) + name + "_";
  completename += version;
  completename += ".root";
  
  return;
}

void Analyzer::OpenPutputFile(){
  outfile = new TFile(completename,"RECREATE");
  outfile->cd();
  cout << "Opening output root file " << completename << endl;
}

void Analyzer::SetEffectiveLumi(Double_t efflumi){
  MCweight = target_lumi / efflumi;
  return;
}
void Analyzer::SetTargetLumi(Double_t lumi ){
  target_lumi = lumi;
}


void Analyzer::SetWeight(Double_t CrossSection, Double_t nevents) {

  MCweight = target_lumi * CrossSection / nevents;
  cout << "Analyser::SetWeight ||  Running on MC: \nAnalyser::SetWeight ||  weight = (lumi *  cs(pb) * gen filter efficiency) / MCevents " << endl;  
  cout<<"Analyser::SetWeight ||  mc weight = "<<MCweight<<endl;
 
}

void Analyzer::SetEvtN(Long64_t events) {
  events ? entrieslimit=events :  entrieslimit=-1;
  cout<<"Analyser::Loop || events "<<events<<endl<<"entrieslimit "<<entrieslimit<<endl;
}


void Analyzer::MakeCleverHistograms(histtype type, TString clhistname ){

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

void Analyzer::MakeHistograms(jobtype job){
  //// Additional plots to make
    
  maphist.clear();

  if(job==HNmm){
    maphist["h_nsignal"] = new TH1F("h_signal","number of signal events",5,-1,4);
    maphist["h_cutflow"] = new TH1F("h_cutflow","number of signal events in cut flow",4,0,4);
    maphist["h_singlefake"] = new TH2F("h_singlefake","number of single fakes",4,0,4,4,-1,3);
    maphist["h_doublefake"] = new TH2F("h_doublefake","number of double fakes",4,0,4,4,-1,3);
    maphist["h_MET"] = new TH1F("h_MET","Missing Et",300,0.0,300.0);
    maphist["h_MET"]->SetDefaultSumw2(true);
    maphist["h_METsign"] = new TH1F("h_METsign","Missing Et significance",50,0.0,50.0);
    maphist["h_MuonMissCharge"] = new TH1F("h_MuonMissCharge","Miss Charge for muons",6,0,6);
    maphist["h_EventFakeType"] = new TH1F("h_EventFakeType","Event fake type",3,0,3);
    maphist["h_LeptvsVert"] = new TH2I("h_LeptvsVert","Leptons per Vertex",50,0,50,5,0,5);
    maphist["h_dRvsbTag"] = new TH2F("h_dRvsbTag","#deltaR vs b-tag discriminant",100,0.0,10.0,100,-5,14);
    
    maphist["h_nVertex"]= new TH1F("h_nVertex","number of verteces",50,0,50);
    maphist["h_nVertex0"]= new TH1F("h_nVertex0","number of verteces t0",50,0,50);
    maphist["h_nVertex1"]= new TH1F("h_nVertex1","number of verteces t1",50,0,50);
    maphist["h_nVertex2"]= new TH1F("h_nVertex2","number of verteces t2",50,0,50);
    
    maphist["h_nvtx_norw"] = new TH1F("h_nvtx_norw","Nvtx per bunch crossing at BX = 0 noreweight",60,0.0,60.0);
    maphist["h_nvtx_rw"] = new TH1F("h_nvtx_rw","Nvtx per bunch crossing at BX = 0 reweight",60,0.0,60.0);
    maphist["h_RelIsoFR"] = new TH1F("h_RelIsoFR","RelIso FR weight",40,0,0.4);
  }
  else if(job == HNee) ;
  else if(job == HNFakeBkgmm);
  else if(job == HNFakeBkgee);
  else if(job == ZTest){
    maphist["zpeak_mumu"] =  new TH1F("h_zpeak_mumu","Di-Muon Mass (GeV)",200,0,200);
    maphist["zpeak_ee"] =  new TH1F("h_zpeak_ee","Di-Muon Mass (GeV)",200,0,200);
    maphist["zpeak_tautau"] =  new TH1F("h_zpeak_tautau","Di-Muon Mass (GeV)",200,0,200);
  }    
  return;
}


bool Analyzer::PassBasicEventCuts(){
  
  bool pass (true);
  if (isTrackingFailure || passTrackingFailureFilter) pass = false;
  if (!passBeamHaloFilterLoose) pass = false;
  if (passBadEESupercrystalFilter || passEcalDeadCellBoundaryEnergyFilter || passEcalDeadCellTriggerPrimitiveFilter || passEcalLaserCorrFilter) pass = false;
  if (!passHBHENoiseFilter) pass = false; // || passHcalLaserEventFilter) continue;
  return pass;
}


double Analyzer::SetEventWeight(){
  
  //// IsData is only set temp here. In order to avoid making PUweight obj for data
  
  /// Event weights :   
  if((MCweight ==1.&& target_lumi ==1.) || !MCweight) {
    MCweight=1.; 
    isData=true;
  }
  else isData=false;
  
  if(isData) cout << "Running on data" << endl;
  if (fChain == 0)  cout << "GoodBye!" << endl;
  
  if(!isData&&(entrieslimit!=-1)) MCweight *= (nentries/entrieslimit);
  if(!isData&&(entrieslimit!=-1)) cout << "Running over " << entrieslimit << "/" << nentries << endl;  
  cout << "Analyser::Loop || Total number of entries in sample = " <<nentries<<endl;
  
  /// Set number of events in runbackground.C
  if (entrieslimit != -1){
    if(entrieslimit < nentries) nentries=entrieslimit;
  }

  double e_weight = MCweight;
  return e_weight;
}


void Analyzer::FillHist(TString histname, float value, float w ){
  
  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  /// Plots Z peak    
  else std::cout << histname << " was NOT found" << std::endl;
  return;
}


void Analyzer::FillCLHist(histtype type, TString hist, vector<snu::KMuon> muons, double w){

  if(type==muhist){
    map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.find(hist);
    if(mupit != mapCLhistMu.end()) mupit->second->Fill(w,muons);
    else cout << hist << " not found in mapCLhistMu" << endl;
  }
  else  cout << "Type not set to muhist, is this a mistake?" << endl;
  
}


void Analyzer::FillCLHist(histtype type, TString hist, vector<snu::KElectron> electrons, double rho, double w){
  
  if(type==elhist){
    map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.find(hist);
    if(elpit !=mapCLhistEl.end()) elpit->second->Fill(w,electrons,rho);
    else cout << hist << " not found in mapCLhistEl" <<endl;
  }
  else  cout << "Type not set to elhist, is this a mistake?" << endl;
}

void Analyzer::FillCLHist(histtype type, TString hist, vector<snu::KJet> jets, double w){

  if(type==jethist){
    map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.find(hist);
    if(jetpit !=mapCLhistJet.end()) jetpit->second->Fill(w,jets);
    else cout << hist << " not found in mapCLhistJet" <<endl;
  } 
  else  cout <<"Type not set to jethist, is this a mistake?" << endl;
 
}


void Analyzer::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){
  
  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, muons, electrons, jets,w);
    else cout << hist << " not found in mapCLhistSig" <<endl;
  }
  else  cout <<"Type not set to sighist, is this a mistake?" << endl;
}

  
void Analyzer::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill( ev, muons,jets, w);
    else cout << hist << " not found in mapCLhistSig" <<endl;
  }
  else  cout <<"Type not set to sighist, is this a mistake?" << endl;
}


void Analyzer::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, electrons, jets, w);
    else cout << hist << " not found in mapCLhistSig" <<endl;
  }
  else  cout <<"Type not set to sighist, is this a mistake?" << endl;
}




void Analyzer::WriteCLHists(){
  
  for(map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.begin(); mupit != mapCLhistMu.end(); mupit++){
    Dir = outfile->mkdir(mupit->first);
    outfile->cd( Dir->GetName() );
    mupit->second->Write();
    outfile->cd();
  }

  for(map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.begin(); elpit != mapCLhistEl.end(); elpit++){
    Dir = outfile->mkdir(elpit->first);
    outfile->cd( Dir->GetName() );
    elpit->second->Write();
    outfile->cd();
  }
  
  for(map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.begin(); jetpit != mapCLhistJet.end(); jetpit++){
    Dir = outfile->mkdir(jetpit->first);
    outfile->cd( Dir->GetName() );
    jetpit->second->Write();
    outfile->cd();
  }

  for(map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.begin(); sigpit != mapCLhistSig.end(); sigpit++){
    Dir = outfile->mkdir(sigpit->first);
    outfile->cd( Dir->GetName() );
    sigpit->second->Write();
    outfile->cd();
  }

  return;
}

void Analyzer::WriteHists(){

  for(map<TString, TH1*>::iterator mapit = maphist.begin(); mapit != maphist.end(); mapit++){
    mapit->second->Write();
  }
  return;
}

TH1* Analyzer::GetHist(TString hname){

  TH1* h = NULL;
  std::map<TString, TH1*>::iterator mapit = maphist.find(hname);
  if(mapit != maphist.end()) return mapit->second;
  else cout << hname << " was not found in map" << endl;
  
  return h;
}

void Analyzer::OutPutEventInfo(int entry, int step){

  if (!(entry % step))  cout << "Processing entry " << entry << " weight = " << weight << endl;      
  
  return;
}

void Analyzer::EndEvent(){
  delete eventbase;

}

void Analyzer::SetUpEvent(int kentry){

  OutPutEventInfo(kentry, 1000); /// output event info every X events wil running
  if (!fChain) cout<<"Problem with fChain"<<endl;
  
  int nbytes = fChain->GetEntry(kentry,0);
  //cout << "Get Entry =  " << nbytes << endl;

  snu::KEvent eventinfo = GetEventInfo();  
  LQEvent lqevent(GetAllMuons(), GetAllElectrons(), GetAllTaus(),GetAllJets(), GetTruthParticles(), eventinfo);  
  isData = eventinfo.IsData();
  
  eventbase = new EventBase(lqevent); 

  return;
}


Analyzer::Analyzer() {

}
