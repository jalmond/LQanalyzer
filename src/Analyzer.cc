#include "Analyzer.h"
#include <stdio.h>  
#include <stdlib.h>     /* getenv */

using namespace::snu;

Analyzer::Analyzer() {

  if (debug) cout<<"inizio"<<endl;

  /// Initialise histograms
  MakeHistograms();
  MakeCleverHistograms();
  
  //// FakeRate Input file
  string analysisdir = getenv("FILEDIR");  
  TFile *infile = new TFile((analysisdir+ "Total_FRcorr60_51_bis.root").c_str());
  infile->cd();
  TDirectory *dir=gDirectory;             
  dir->GetObject("h_FOrate3",FRhisto);
  if (debug) cout<<"fine"<<endl;
    
  ////  Inital settings for running on sample
  entrieslimit = -1; /// Set default to all events
    
}


//// List of several loops to call

/// Test Loop runs basic Z->ee, Z->mm, Z->tautau code
/// HNmmLoop runs HN MM channel results
/// HNeeLoop runs HN MM channel results
/// FakeRateee
/// FakeRatem


//  TEST loop for Z to mumu 
void Analyzer::TestLoop() {

  //// This is a loop for running over Drell Yan MC OR data events and plotting invariant mass of mass peak
  cout << "In test loop " << endl;

  weight= SetEventWeight();  

  string analysisdir = getenv("FILEDIR");
  if(!isData)reweightPU = new ReweightPU((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  ///////////////////////////////////////////////////////////////////////
  ///  START OF EVENT LOOP
  ///////////////////////////////////////////////////////////////////////////

  int i_dimu_evNmv(0), i_dimu(0), i_dimu_vertexmismatch(0), i_dimu_faild0sig(0), i_dimu_tight(0);
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {
    
    SelectionBase eventbase = SetUpEvent(jentry); 

    if(!PassBasicEventCuts()) continue;     /// Initial event cuts
    
    /// Trigger List (specific to muons channel)
    std::vector<TString> triggerslist;
    triggerslist.push_back("HLT_Mu17_TkMu8_v");
    if(!PassTrigger(triggerslist, prescale)) continue;
      
    /// Correct MC for pileup
    if (MC_pu&&!isData)  weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;

    numberVertices = eventbase.GetBaseEvent().nVertices();
    if (!eventbase.GetBaseEvent().HasGoodPrimaryVertex()) continue; //// Make cut on event wrt vertex

    ///  use selection code (which returns a similar class vector with selected cuts)     
    if(eventbase.GetBaseEvent().MET() > 50) continue;

    //// want to add more selection options ( )
    std::vector<snu::KMuon> muonColl;
    std::vector<snu::KMuon> muonCollIso;
    eventbase.GetMuonSel().SetPt(20); 
    eventbase.GetMuonSel().SetEta(2.4);
    eventbase.GetMuonSel().MuonSelection(muonColl);
    eventbase.GetMuonSel().SetRelIso(1000.);
    eventbase.GetMuonSel().SetChiNdof(1000); 
    eventbase.GetMuonSel().SetBSdxy(0.01);
    eventbase.GetMuonSel().SetBSdz(0.10);
    eventbase.GetMuonSel().SetDeposits(40.0,60.00);    
    eventbase.GetMuonSel().MuonSelection(muonCollIso);


    std::vector<snu::KJet> jetColl;
    //// List of cuts                                                                                                                                                                
    eventbase.GetJetSel().SetPt(20);
    eventbase.GetJetSel().SetEta(2.5);
    eventbase.GetJetSel().JetSelection(jetColl);

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
	
	
	if(muonColl.at(0).MuonVertexIndex() != eventbase.GetBaseEvent().VertexIndex()) i_dimu_evNmv++;
	if(muonColl.at(0).MuonVertexIndex() != muonColl.at(1).MuonVertexIndex()){
	  
	  i_dimu_vertexmismatch++;
	  cout << "\n " << endl;
	  cout << "Event Summary " << endl;
	  cout << "Vertex Index = " << eventbase.GetBaseEvent().VertexIndex() << endl;
	  cout << "Vertex X = " << eventbase.GetBaseEvent().VertexX() << endl;
	  cout << "Vertex Y = " << eventbase.GetBaseEvent().VertexY() << endl;
	  cout << "Vertex Z = " << eventbase.GetBaseEvent().VertexZ() << endl;
	  
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
    eventbase.GetElectronSel().SetPt(20); 
    eventbase.GetElectronSel().SetEta(2.5); 
    eventbase.GetElectronSel().SetRelIso(0.15); 
    eventbase.GetElectronSel().SetBSdxy(0.02); 
    eventbase.GetElectronSel().SetBSdz(0.10);
    eventbase.GetElectronSel().ElectronSelection(electronColl); 

    
    
     ///// SOME STANDARD PLOTS /////
    if (muonColl.size() == 2) {      
      KParticle Z = muonColl.at(0) + muonColl.at(1);
      if(muonColl.at(0).Charge() == muonColl.at(1).Charge()){      
	h_zpeak->Fill(Z.M(), weight);	 /// Plots Z peak
	h_muonsLoose->Fill(weight, muonColl);      
	h_signal->Fill(eventbase.GetBaseEvent().MET(), muonColl, jetColl, weight, true, false);
      } 
    }
    
    if (muonCollIso.size() == 2) {

      if(muonCollIso.at(0).Charge() == muonCollIso.at(1).Charge()){	
	h_muons->Fill(weight, muonCollIso);
	h_jets->Fill(weight, jetColl);
      }
    }
    


  }// End of event loop
  
  OpenPutputFile();  
  
  h_zpeak->Write();  // FOR test only
  
  Dir = outfile->mkdir("Muons");
  outfile->cd( Dir->GetName() );
  h_muons->Write();
  outfile->cd();

  Dir = outfile->mkdir("MuonsLoose");
  outfile->cd( Dir->GetName() );
  h_muonsLoose->Write();
  outfile->cd();

  Dir = outfile->mkdir("Jets");
  outfile->cd( Dir->GetName() );
  h_jets->Write();
  outfile->cd();
  

  Dir = outfile->mkdir("Signal");
  outfile->cd( Dir->GetName() );
  h_signal->Write();
  outfile->cd();


  outfile->Close();

}


///  START OF HNmuon loop

void Analyzer::Loop() {
  
  return;

}


Analyzer::~Analyzer() {


  delete h_MET ;
  delete h_METsign;
  delete h_MuonMissCharge; 
  delete h_EventFakeType;
  delete h_LeptvsVert; 
  delete h_dRvsbTag; 

  delete h_nVertex;
  delete h_nVertex0;
  delete h_nVertex1;
  delete h_nVertex2;

  delete h_nvtx_norw;
  delete h_nvtx_rw; 

  delete h_zpeak; 
  delete h_RelIsoFR;

  delete h_electrons;
  delete h_electronsLoose;
  delete h_muons; 
  delete h_muonsLoose;
  delete h_LnotT; 


  delete h_jets;
  delete h_jets_veto;
  delete h_signal; 
  delete h_WZcontrol; 
  delete h_signalMET50;
  delete h_signalbTag;
  delete h_signalTOT; 
  delete h_singlefakes;
  delete h_doublefakes;
  delete h_totalfakes; 
  delete h_singlefakesMET50;
  delete h_doublefakesMET50;
  delete h_totalfakesMET50; 
  delete h_doublefakesbTag; 
  delete h_totalfakesbTag; 
  delete h_singlefakesTOT;
  delete h_doublefakesTOT;
  delete h_totalfakesTOT; 
  delete h_nsignal; 
  delete h_cutflow; 
  delete h_singlefake;
  delete h_doublefake;

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


void Analyzer::MakeCleverHistograms(){

//// ELECTRON PLOTs
  h_electrons = new ElectronPlots("electrons");
  h_electronsLoose = new ElectronPlots("loose electrons");
  
  //// MUON PLOTs
  h_muons = new MuonPlots("muons");
  h_muonsLoose = new MuonPlots("loose_muons");
  h_LnotT = new MuonPlots("loose_not_tight");
  

  /// JET PLOTs
  h_jets = new JetPlots("jets");
  h_jets_veto = new JetPlots("jets_w_veto");

  //// SIGNAL PLOTs
  h_signal = new SignalPlots("signal");
  h_WZcontrol = new SignalPlots("WZcontrol");
  h_signalMET50 = new SignalPlots("signal_MET50");
  h_signalbTag = new SignalPlots("signal_bTag");
  h_signalTOT = new SignalPlots("signal_TOT");
  h_singlefakes = new SignalPlots("sf");
  h_doublefakes = new SignalPlots("df");
  h_totalfakes = new SignalPlots("tf");
  h_singlefakesMET50 = new SignalPlots("sf_MET50");
  h_doublefakesMET50 = new SignalPlots("df_MET50");
  h_totalfakesMET50 = new SignalPlots("tf_MET50");
  h_singlefakesbTag = new SignalPlots("sf_bTag");
  h_doublefakesbTag = new SignalPlots("df_bTag");
  h_totalfakesbTag = new SignalPlots("tf_bTag");
  h_singlefakesTOT = new SignalPlots("sf_TOT");
  h_doublefakesTOT = new SignalPlots("df_TOT");
  h_totalfakesTOT = new SignalPlots("tf_TOT");
  
  return;
}

void Analyzer::MakeHistograms(){
 //// Additional plots to make
    h_nsignal = new TH1F("h_signal","number of signal events ",5,-1,4);
    h_cutflow = new TH1F("h_cutflow","number of signal events in cut flow",4,0,4);
    h_singlefake = new TH2F("h_singlefake","number of single fakes ",4,0,4,4,-1,3);
    h_doublefake = new TH2F("h_doublefake","number of double fakes ",4,0,4,4,-1,3);
    h_MET = new TH1F("h_MET","Missing Et",300,0.0,300.0);
    h_MET->SetDefaultSumw2(true);
    h_METsign = new TH1F("h_METsign","Missing Et significance",50,0.0,50.0);
    h_MuonMissCharge = new TH1F("h_MuonMissCharge","Miss Charge for muons",6,0,6);
    h_EventFakeType = new TH1F("h_EventFakeType","Event fake type",3,0,3);
    h_LeptvsVert = new TH2I("h_LeptvsVert","Leptons per Vertex",50,0,50,5,0,5);
    h_dRvsbTag = new TH2F("h_dRvsbTag","#deltaR vs b-tag discriminant",100,0.0,10.0,100,-5,14);

    h_nVertex= new TH1F("h_nVertex","number of verteces",50,0,50);
    h_nVertex0= new TH1F("h_nVertex0","number of verteces t0",50,0,50);
    h_nVertex1= new TH1F("h_nVertex1","number of verteces t1",50,0,50);
    h_nVertex2= new TH1F("h_nVertex2","number of verteces t2",50,0,50);
  
    h_nvtx_norw = new TH1F("h_nvtx_norw","Nvtx per bunch crossing at BX = 0 noreweight",60,0.0,60.0);
    h_nvtx_rw = new TH1F("h_nvtx_rw","Nvtx per bunch crossing at BX = 0 reweight",60,0.0,60.0);

    h_zpeak = new TH1F("h_zpeak","Di-Muon Mass (GeV)",200,0,200);
    h_RelIsoFR = new TH1F("h_RelIsoFR","RelIso FR weight",40,0,0.4);
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
  
  /// Event weights :   
  if((MCweight ==1.&& target_lumi ==1.) || !MCweight) {
    MCweight=1.; 
    isData=true;
  }
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

void Analyzer::OutPutEventInfo(int entry, int step){

  if (!(entry % step))  cout << "Processing entry " << entry << " weight = " << weight << endl;      
  
  return;
}

SelectionBase Analyzer::SetUpEvent(int kentry){

  OutPutEventInfo(kentry, 1000); /// output event info every X events wil running
  if (!fChain) cout<<"Problem with fChain"<<endl;
  fChain->GetEntry(kentry);
  
  snu::KEvent eventinfo = GetEventInfo();
  EventBase evb(GetAllMuons(), GetAllElectrons(), GetAllTaus(),GetAllJets(), eventinfo);
  
  SelectionBase sbase(evb);
  
  return sbase;
}
