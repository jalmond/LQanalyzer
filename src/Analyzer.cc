#include "Analyzer.h"
#include <stdio.h>  
#include <stdlib.h>     /* getenv */

using namespace::snu;


Analyzer::Analyzer(jobtype jtype): Mass_Z(91.1876), Mass_W(80.398) {
  
  _jtype = jtype;
  /// Initialise histograms
  MakeHistograms(jtype);
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

  ///////////////////////////////////////////////////////////////////////
  //////// For HN analysis  /////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////
  //// FakeRate Input file
  //////////////////////////////////////////////////////////////////////
  string analysisdir = getenv("FILEDIR");  
  TFile *infile = new TFile((analysisdir+ "Total_FRcorr60_51_bis.root").c_str());
  infile->cd();
  TDirectory *dir=gDirectory;             
  dir->GetObject("h_FOrate3",FRHist);
  if (debug) cout<<"fine"<<endl;


  ///////////////////////////////////////////////////////////////////////
  ////  Inital settings for running on samples
  entrieslimit = -1; /// Set default to all events
  ///////////////////////////////////////////////////////////////////////
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
  
  if(_jtype == ZTest) TestLoop();
  else if(_jtype == HNmm) HNmmLoop();
  else cout << "Error in setting Job Type in Analyzer constructor; " << endl;
}

//  TEST loop for Z to mumu/ee/tautau 
void Analyzer::TestLoop() {

  //// This is a loop for running over Drell Yan MC OR data events and plotting invariant mass of mass peak
  weight= SetEventWeight();  
  
  string analysisdir = getenv("FILEDIR");
  if(!isData) reweightPU = new ReweightPU((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  ///////////////////////////////////////////////////////////////////////
  ///  START OF EVENT LOOP
  ///////////////////////////////////////////////////////////////////////////

  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {
    
    /// Class has all information for event
    SetUpEvent(jentry); 
    
    if(!PassBasicEventCuts()) continue;     /// Initial event cuts
    
    /// Trigger List (specific to muons channel)
    std::vector<TString> triggerslist;
    triggerslist.push_back("HLT_Mu17_TkMu8_v");
    if(!PassTrigger(triggerslist, prescale)) continue;
    /// Correct MC for pileup

    if (MC_pu&&!isData)  weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;
    
    numberVertices = eventbase->GetBaseEvent().nVertices();
    if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) continue; //// Make cut on event wrt vertex
    
    if(eventbase->GetBaseEvent().MET() > 50) continue;
    
    //// want to add more selection options ( )
    std::vector<snu::KMuon> muonColl;
    eventbase->GetMuonSel()->SetPt(20); 
    eventbase->GetMuonSel()->SetEta(2.4);
    //eventbase->GetMuonSel().SetRelIso(1000.);
    //eventbase->GetMuonSel().SetChiNdof(1000); 
    //eventbase->GetMuonSel().SetBSdxy(0.01);
    //eventbase->GetMuonSel().SetBSdz(0.10);
    //eventbase->GetMuonSel().SetDeposits(40.0,60.00);    
    eventbase->GetMuonSel()->MuonSelection(muonColl);
    std::vector<snu::KJet> jetColl;
    eventbase->GetJetSel()->SetPt(20);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->JetSelection(jetColl);

    
    std::vector<snu::KElectron> electronColl;
    eventbase->GetElectronSel()->SetPt(20); 
    eventbase->GetElectronSel()->SetEta(2.5); 
    eventbase->GetElectronSel()->SetRelIso(0.15); 
    eventbase->GetElectronSel()->SetBSdxy(0.02); 
    eventbase->GetElectronSel()->SetBSdz(0.10);
    eventbase->GetElectronSel()->ElectronSelection(electronColl); 
    
    
    for(vector<snu::KMuon>::iterator it = muonColl.begin(); it!= muonColl.end(); it++){
      cout <<  "Muon pt = " << it->Pt() << endl;
      cout << " Eta ="  << it->Eta() << " " << it->Phi() << endl;
      
      for(unsigned int g =0; g < GenParticleP->size(); g++){
	if( it->MuonMatchedGenParticleEta() != -999){
	  if((fabs(it->MuonMatchedGenParticleEta() - GenParticleEta->at(g)) < 0.1) && (fabs(it->MuonMatchedGenParticlePhi() -GenParticlePhi->at(g)) < 0.1)) {
	    cout << "Matched particle has pt = " << GenParticlePt->at(g) << " and has pdgid = " << GenParticlePdgId->at(g) << " and has mother with pdgid = " << GenParticlePdgId->at(GenParticleMotherIndex->at(g))<<  endl;	  
	  }
	}
	else{
	  if((fabs( GenParticleEta->at(g) - it->Eta() ) < 0.1) && (fabs(GenParticlePhi->at(g) - it->Phi() ) < 0.1)) {
	    cout << "particle has pt = " << GenParticlePt->at(g) << " and has pdgid = " << GenParticlePdgId->at(g) << endl;	  
	  }
	}
      }      
    }


    
    ///// SOME STANDARD PLOTS /////
    ////  Z-> mumu            //////

    if (muonColl.size() == 2) {      
      KParticle Z = muonColl.at(0) + muonColl.at(1);
      if(muonColl.at(0).Charge() != muonColl.at(1).Charge()){      
	GetHist("zpeak_mumu")->Fill(Z.M(), weight);	 /// Plots Z peak
	FillCLHist(muhist, "Zmuons", muonColl, weight);
      } 
    }

    
    ///// SOME STANDARD PLOTS /////
    ////  Z-> ee              //////
    if (electronColl.size() == 2) {      
      KParticle Z = electronColl.at(0) + electronColl.at(1);
      if(electronColl.at(0).Charge() != electronColl.at(1).Charge()){      
	GetHist("zpeak_ee")->Fill(Z.M(), weight);	 /// Plots Z peak
	FillCLHist(elhist, "Zelectrons", electronColl, eventbase->GetBaseEvent().JetRho(), weight);
      } 
    }

    EndEvent();
  }// End of event loop
  
  
  OpenPutputFile();  
  WriteHists();/// writes all outputs in maphist
  WriteCLHists(); /// writes all hists set with MakeCleverHistograms
  
  outfile->Close();

}

//  TEST loop for Z to mumu 
void Analyzer::HNmmLoop() {

  //// This is a loop for running over Drell Yan MC OR data events and plotting invariant mass of mass peak
  weight= SetEventWeight();  

  string analysisdir = getenv("FILEDIR");
  if(!isData)reweightPU = new ReweightPU((analysisdir + "MyDataPileupHistogram.root").c_str());
  
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
    if (MC_pu&&!isData)  weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;

    numberVertices = eventbase->GetBaseEvent().nVertices();
    if (!eventbase->GetBaseEvent().HasGoodPrimaryVertex()) continue; //// Make cut on event wrt vertex

    ///  use selection code (which returns a similar class vector with selected cuts)     
    if(eventbase->GetBaseEvent().MET() > 50) continue;

    //// want to add more selection options ( )
    std::vector<snu::KMuon> muonColl;
    std::vector<snu::KMuon> muonCollIso;
    eventbase->GetMuonSel()->SetPt(20); 
    eventbase->GetMuonSel()->SetEta(2.4);
    eventbase->GetMuonSel()->MuonSelection(muonColl);
    eventbase->GetMuonSel()->SetRelIso(1000.);
    eventbase->GetMuonSel()->SetChiNdof(1000); 
    eventbase->GetMuonSel()->SetBSdxy(0.01);
    eventbase->GetMuonSel()->SetBSdz(0.10);
    eventbase->GetMuonSel()->SetDeposits(40.0,60.00);    
    eventbase->GetMuonSel()->MuonSelection(muonCollIso);


    std::vector<snu::KJet> jetColl;
    //// List of cuts                                                                                                                                                                
    eventbase->GetJetSel()->SetPt(20);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->JetSelection(jetColl);

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
    eventbase->GetElectronSel()->ElectronSelection(electronColl); 

    
    
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



///  START OF HNmuon loop

void Analyzer::Loop() {
  
  
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
  
 }

void Analyzer::NEvents(float n_events){
  entrieslimit =  n_events;
  return;
}


bool Analyzer::PassTrigger(vector<TString> list, int& prescaler){
  
  return TriggerSelector(list, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler);
  
}



void Analyzer::SetName(TString name, Int_t version) {

  string out_dir = getenv("OUTDIR");
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
  fChain->GetEntry(kentry);
  
  snu::KEvent eventinfo = GetEventInfo();

  LQEvent lqevent(GetAllMuons(), GetAllElectrons(), GetAllTaus(),GetAllJets(), eventinfo);

  isData = eventinfo.IsData();
  eventbase = new EventBase(lqevent);
  
  return;
}


Analyzer::Analyzer(): Mass_Z(91.1876),Mass_W(80.398) {

}
