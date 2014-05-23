// $Id: AnalyzerCore.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes 
#include  "AnalyzerCore.h"
#include "EventBase.h"

//Plotting                                                      
#include "MuonPlots.h"
#include "ElectronPlots.h"
#include "JetPlots.h"
#include "SignalPlots.h"

//ROOT includes
#include <TFile.h>


AnalyzerCore::AnalyzerCore() : LQCycleBase(), MCweight(-999.) {

  TH1::SetDefaultSumw2(true);  
  /// clear list of triggers stored in KTrigger
  triggerlist.clear();
  // If running on LQNtuples this is not important.
  // If creating an SKTree ntuple this controls what triggers are accessible
  AddTriggerToList("HLT_Mu17_TkMu8_v");
  AddTriggerToList("HLT_Mu5_v");
  AddTriggerToList("HLT_Mu8_v");
  AddTriggerToList("HLT_Mu12_v");
  AddTriggerToList("HLT_Mu17_v");
  AddTriggerToList("HLT_Mu24_v");
  AddTriggerToList("HLT_Mu40_eta2p1_v");
  AddTriggerToList("HLT_IsoMu24_eta2p1_v");
  AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  AddTriggerToList("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  AddTriggerToList("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  AddTriggerToList("HLT_Ele27_WP80_v");
  AddTriggerToList("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  AddTriggerToList("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v");
  AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_v");
  AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20_v");
  AddTriggerToList("HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet45_35_25_v");
  AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFJet30_v");
  AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_v");
  AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet30_30_20_v");
  AddTriggerToList("HLT_IsoMu17_eta2p1_TriCentralPFNoPUJet45_35_25_v");
  // To have the correct name in the log:                                                                                                                            
  SetLogName("AnalyzerCore");

  Message("In AnalyzerCore constructor", INFO);
  
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
  
  FRHist = dynamic_cast<TH2F*> (( infile->Get("h_FOrate3"))->Clone());
  infile->Close();
  delete infile;
  origDir->cd();
  
  string lqdir = getenv("LQANALYZER_DIR");
  
  m_fakeobj = new HNCommonLeptonFakes(lqdir+"/HNCommonLeptonFakes/share/");
}

double AnalyzerCore::ElectronScaleFactor( double eta, double pt){
  
  ///https://twiki.cern.ch/twiki/bin/view/Main/EGammaScaleFactors2012
  double sf = 0.;
  
  /// tight working point
  bool medium_electron=false;
  bool tight_electron=true;
  
  if(tight_electron){
    if(fabs(eta) < 0.8 ) {
      if( pt < 15.) sf = 0.827;
      else if( pt < 20.) sf = 0.924;
      else if( pt < 30.) sf = 0.960;
      else if( pt < 40.) sf = 0.978;
      else if( pt < 50.) sf = 0.981;
      else sf = 0.982;
    }
    else  if(fabs(eta) <  1.442){
      
      if( pt < 15.) sf = 0.948;
      else if( pt < 20.) sf = 0.932;
      else if( pt < 30.) sf = 0.936;
      else if( pt < 40.) sf = 0.958;
      else if( pt < 50.) sf = 0.969;
      else sf = 0.969;
    }
    else  if(fabs(eta) <1.556){
      if( pt < 15.) sf = 1.073;
      else if( pt < 20.) sf = 0.808;
      else if( pt < 30.) sf = 0.933;
      else if( pt < 40.) sf = 0.907;
      else if( pt < 50.) sf = 0.904;
      else sf = 0.926;
    }
    else if(fabs(eta) <2.0){
      
      if( pt < 15.) sf = 0.854;
      else if( pt < 20.) sf = 0.853;
      else if( pt < 30.) sf = 0.879;
      else if( pt < 40.) sf = 0.909;
      else if( pt < 50.) sf = 0.942;
      else sf = 0.957;
    }
    else{
      if( pt < 15.) sf = 1.007;
      else if( pt < 20.) sf = 0.903;
      else if( pt < 30.) sf = 0.974;
      else if( pt < 40.) sf = 0.987;
      else if( pt < 50.) sf = 0.991;
      else sf = 0.999;
    }
    return sf;
  }
  if(medium_electron){
    /// medium working point
    if(fabs(eta) < 0.8 ) {
      if( pt < 15.) sf = 0.865;
      else if( pt < 20.) sf = 0.958;
      else if( pt < 30.) sf = 0.988;
      else if( pt < 40.) sf = 1.002;
      else if( pt < 50.) sf = 1.005;
      else sf = 1.005;
    }
    else  if(fabs(eta) <  1.442){
      
      if( pt < 15.) sf = 0.967;
      else if( pt < 20.) sf = 0.971;
      else if( pt < 30.) sf = 0.965;
      else if( pt < 40.) sf = 0.985;
      else if( pt < 50.) sf = 0.989;
      else sf = 0.989;
    }
    else  if(fabs(eta) <1.556){
      if( pt < 15.) sf = 1.064;
      else if( pt < 20.) sf = 0.902;
      else if( pt < 30.) sf = 0.990;
      else if( pt < 40.) sf = 0.966;
      else if( pt < 50.) sf = 0.971;
      else sf = 0.980;
    }
    else if(fabs(eta) <2.0){
      
      if( pt < 15.) sf = 0.939;
      else if( pt < 20.) sf = 0.897;
      else if( pt < 30.) sf = 0.953;
      else if( pt < 40.) sf = 0.980;
      else if( pt < 50.) sf = 0.999;
      else sf = 1.004;
    }
    else{
      if( pt < 15.) sf = 1.050;
      else if( pt < 20.) sf = 0.941;
      else if( pt < 30.) sf = 1.017;
      else if( pt < 40.) sf = 1.019;
      else if( pt < 50.) sf = 1.019;
      else sf = 1.023;
      
    }
    return sf;

  }
  return sf;
  /// From higgs note Z->llll
  /// reconstruction scale factors
  if(fabs(eta) < 0.8 ) {
    if( pt < 15.) sf *= 0.967;
    else if( pt < 20.) sf *= 0.997;
    else if( pt < 30.) sf *= 0.982;
    else if( pt < 40.) sf *= 0.988;
    else sf *= 0.990;
  }
  else if (fabs(eta) < 1.4442 ) {
    if( pt < 15.) sf *= 0.967;
    else if( pt < 20.) sf *= 0.997;
    else if( pt < 30.) sf *= 0.993;
    else if( pt < 40.) sf *= 0.993;
    else sf *= 0.992;
  }
  else if (fabs(eta) < 1.566 ) {
    if( pt < 15.) sf *= 1.126;
    else if( pt < 20.) sf *= 0.955;
    else if( pt < 30.) sf *= 1.015;
    else if( pt < 40.) sf *= 0.985;
    else sf *= 0.985;
  }
  else if (fabs(eta) < 2. ) {
    if( pt < 15.) sf *= 1.097;
    else if( pt < 20.) sf *= 1.012;
    else if( pt < 30.) sf *= 0.988;
    else if( pt < 40.) sf *= 0.992;
    else sf *= 0.991;
  }
  else{
    if( pt < 15.) sf *= 1.097;
    else if( pt < 20.) sf *= 1.012;
    else if( pt < 30.) sf *= 1.002;
    else if( pt < 40.) sf *= 1.004;
    else sf *= 1.004;
  }

    
}

void AnalyzerCore::AddTriggerToList(TString triggername){
  
  triggerlist.push_back(triggername);
}

AnalyzerCore::~AnalyzerCore(){
  
  Message("In AnalyzerCore Destructor" , INFO);
  if(FRHist) delete FRHist;

  for(map<TString, TH1*>::iterator it = maphist.begin(); it!= maphist.end(); it++){
    delete it->second;
  }
  maphist.clear();

  for(map<TString, TH2*>::iterator it = maphist2D.begin(); it!= maphist2D.end(); it++){
    delete it->second;
  }
  maphist2D.clear();



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
  
  }

//###
//###   IMPORTANT BASE FUNCTION: SETS UP EVENT FOR ALL CYCLES
//###

void AnalyzerCore::SetUpEvent(Long64_t entry, float ev_weight) throw( LQError ) {


  Message("In SetUpEvent(Long64_t entry) " , DEBUG);
  m_logger << DEBUG << "This is entry " << entry << LQLogger::endmsg;
  if (!fChain) throw LQError( "Chain is not initialized",  LQError::SkipCycle );     
  
  if(LQinput){
    m_logger << DEBUG << "k_isdata = " << k_isdata << " and isData = " << isData << LQLogger::endmsg;
    if(k_isdata != isData) throw LQError( "!!! Event is confused. It does not know if it is data or MC", LQError::SkipCycle );
  }
  else isData = k_isdata;
  
  if (!(entry % output_interval)) {
    m_logger << INFO <<  "Processing entry " << entry <<  "/" << nentries << LQLogger::endmsg;

  }

  snu::KEvent eventinfo = GetEventInfo();
  
  if(k_isdata){
    if(ev_weight!=1.) Message("ERROR in setting weights. This is Data...", INFO);
    MCweight=1.;
    weight = 1.;
  }
  else {
    MCweight = eventinfo.MCWeight(); //Get MC weight here FIX ME                                                              
    weight= ev_weight; 
  }
  
  //
  // creates object that stores all SKTree classes	
  //                                                                                                        

  snu::KTrigger triggerinfo = GetTriggerInfo(triggerlist);

  std::vector<snu::KJet> skjets= GetAllJets();
  std::vector<snu::KGenJet> skgenjets=GetAllGenJets();
  
  LQEvent lqevent(GetAllMuons(), GetAllElectrons(), GetAllTaus(), skjets, skgenjets,GetTruthParticles(), triggerinfo,eventinfo);
  
  //  eventbase is master class to use in analysis 
  //
  
  eventbase = new EventBase(lqevent);
  
}

float AnalyzerCore::SumPt( std::vector<snu::KJet> particles){

  float sumpt=0.;
  
  for(std::vector<snu::KJet>::iterator it = particles.begin(); it != particles.end(); it++){
    sumpt += it->Pt();
  }
  return sumpt;
}
  


bool AnalyzerCore::isPrompt(long pdgid) {
  /// mother pdgid
  pdgid = abs(pdgid);
  if (pdgid == 24) return true; // Z
  else if (pdgid == 23) return true; // W
  else if (pdgid == 15) return true; // taus
  else if (pdgid == 90) return true; // N
  else return false;
}


float  AnalyzerCore::JetResCorr(snu::KJet jet, std::vector<KGenJet> genjets){
  
  /// This function is not needed when smeaing is already applied to LQNtuples in production stage
  return 1.;
  
  float genpt= -999.;
  for(std::vector<KGenJet>::iterator it = genjets.begin(); it != genjets.end(); it++){
    if(it->DeltaR(jet) < 0.3){
      genpt = it->Pt();
    }
  }
  
  double fabs_eta = fabs ( jet.Eta() );
  float c(0.);
  if      ( fabs_eta > 0.0 && fabs_eta <= 0.5 ) c= 1.052;
  else if ( fabs_eta > 0.5 && fabs_eta <= 1.1 ) c= 1.057;
  else if ( fabs_eta > 1.1 && fabs_eta <= 1.7 ) c= 1.096;
  else if ( fabs_eta > 1.7 && fabs_eta <= 2.3 ) c= 1.134;
  else                                          c= 1.288;
  
  float newpt = std::max(0., genpt + c*(jet.Pt() - genpt));
  if(genpt < 0.) newpt = jet.Pt();
  
  return newpt;
}

void AnalyzerCore::EndEvent()throw( LQError ){

  delete eventbase;                                                                                                            

}
  
void AnalyzerCore::CheckFile(TFile* file)throw( LQError ){

  if(file) m_logger << INFO << "Analyzer: File " << file->GetName() << " was found." << LQLogger::endmsg;
  else m_logger  << INFO <<"Analyzer  " << file->GetName()  << "  : ERROR Rootfile failed to open." << LQLogger::endmsg;

  if(!file)  throw LQError( "!!! File is not found", LQError::SkipCycle);
  return;
}

bool AnalyzerCore::PassTrigger(vector<TString> list, int& prescaler){

  return TriggerSelector(list, eventbase->GetTrigger().GetHLTInsideDatasetTriggerNames(), eventbase->GetTrigger().GetHLTInsideDatasetTriggerDecisions(), eventbase->GetTrigger().GetHLTInsideDatasetTriggerPrescales(), prescaler);

}

TDirectory* AnalyzerCore::GetTemporaryDirectory(void) const
{
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
  if(type==sighist)  mapCLhistSig[clhistname] = new SignalPlots(clhistname);
      
  return;
}

void AnalyzerCore::MakeHistograms(){
  //// Additional plots to make                                                                                
  maphist.clear();
  maphist2D.clear();

    
}

void AnalyzerCore::MakeHistograms(TString hname, int nbins, float xbins[]){
  maphist[hname] =  new TH1F(hname.Data(),hname.Data(),nbins,xbins);
}

void AnalyzerCore::MakeHistograms(TString hname, int nbins, float xmin, float xmax){

  maphist[hname] =  new TH1F(hname.Data(),hname.Data(),nbins,xmin,xmax);
}

void AnalyzerCore::MakeHistograms2D(TString hname, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax) {

  maphist2D[hname] =  new TH2F(hname.Data(),hname.Data(),nbinsx,xmin,xmax, nbinsy,ymin,ymax);
}

bool AnalyzerCore::PassBasicEventCuts(){
  
  bool pass (true);
  
  ///https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
  /// The recommendations of the MET group regarding noise cleaning are summarized in the talk https://indico.cern.ch/getFile.py/access?subContId=1&contribId=4&resId=0&materialId=slides&confId=172431
  
  //CSC tight beam halo filter
  if (!eventbase->GetEvent().PassBeamHaloFilterTight()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassBeamHaloFilterTight " << LQLogger::endmsg;
  }
  //if (!eventbase->GetEvent().PassBeamHaloFilterLoose()) pass = false;
  //HBHE noise filter with isolated noise rejection
  if (!eventbase->GetEvent().PassHBHENoiseFilter()) {
    pass = false; 
    m_logger << DEBUG << "Event Fails PassHBHENoiseFilter " << LQLogger::endmsg;
  }
  //HCAL laser filter (post-ICHEP: updated to reduce over-tagging rate in channels with low Bias Voltage)
  
  //ECAL dead cell trigger primitive (TP) filter
  if(eventbase->GetEvent().PassEcalDeadCellTriggerPrimitiveFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalDeadCellTriggerPrimitiveFilter" << LQLogger::endmsg;
  }
  if(  eventbase->GetEvent().PassEcalDeadCellBoundaryEnergyFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalDeadCellBoundaryEnergyFilter" << LQLogger::endmsg;
  }
  //Tracking failure filter
  if (eventbase->GetEvent().IsTrackingFailure()) {
    pass = false;
    m_logger << DEBUG << "Event Fails IsTrackingFailure" << LQLogger::endmsg; 
  }
  //Bad EE Supercrystal filter (post-ICHEP: extend to include an additional problematic SC --only for 2012)
  if (eventbase->GetEvent().PassBadEESupercrystalFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassBadEESupercrystalFilter" << LQLogger::endmsg;
  }
  //ECAL Laser correction filter (only mandatory for 53X rereco of 2012A+B, i.e., Jul13 rereco; An optional filter for 2012C prompt reco Mandatory for Jan2013 ReReco)
  if(eventbase->GetEvent().PassEcalLaserCorrFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalLaserCorrFilter" << LQLogger::endmsg;
  }
  //Tracking POG filters (new. Only work on AOD >=53X)
  if(eventbase->GetEvent().PassTrackingFailureFilter()){
    m_logger << DEBUG << "Event Fails PassTrackingFailureFilter" << LQLogger::endmsg;
    pass = false;
  }
  return pass;
}



void AnalyzerCore::FillHist(TString histname, float value, float w, float xbins[], int nbins){
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  
  else{
    if (nbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms(histname, nbins, xbins);
    if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  }

}

void AnalyzerCore::FillHist(TString histname, float value, float w, float xmin, float xmax, int nbins){
  
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  
  else{
    if (nbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms(histname, nbins, xmin, xmax);
    if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  }
  
}

void AnalyzerCore::FillHist(TString histname, float value1, float value2, float w, float xmin, float xmax, int nbinsx, float ymin, float ymax, int nbinsy){

  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist2D(histname)) GetHist2D(histname)->Fill(value1,value2, w);
  else{
    if (nbinsx < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms2D(histname, nbinsx, xmin, xmax,nbinsy, ymin, ymax );
    if(GetHist2D(histname)) GetHist2D(histname)->Fill(value1,value2, w);
  }

}


void AnalyzerCore::FillHist(TString histname, float value, float w){

  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  /// Plots Z peak                                   
  else m_logger << INFO << histname << " was NOT found. Will add the histogram to the hist map on first event." << LQLogger::endmsg;
  
  
  return;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KMuon> muons, double w){

  if(type==muhist){
    map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.find(hist);
    if(mupit != mapCLhistMu.end()) mupit->second->Fill(w,muons);
    else m_logger << INFO  << hist << " not found in mapCLhistMu" << LQLogger::endmsg;
  }
  else  m_logger << INFO  << "Type not set to muhist, is this a mistake?" << LQLogger::endmsg;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KElectron> electrons, double rho, double w){

  if(type==elhist){
    map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.find(hist);
    if(elpit !=mapCLhistEl.end()) elpit->second->Fill(w,electrons,rho);
    else m_logger << INFO  << hist << " not found in mapCLhistEl" <<LQLogger::endmsg;
  }
  else  m_logger << INFO  << "Type not set to elhist, is this a mistake?" << LQLogger::endmsg;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KJet> jets, double w){

  if(type==jethist){
    map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.find(hist);
    if(jetpit !=mapCLhistJet.end()) jetpit->second->Fill(w,jets);
    else m_logger << INFO  << hist << " not found in mapCLhistJet" <<LQLogger::endmsg;
  }
  else  m_logger << INFO  <<"Type not set to jethist, is this a mistake?" << LQLogger::endmsg;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, muons, electrons, jets,w);
    else {
      mapCLhistSig[hist] = new SignalPlots(hist);
      sigpit = mapCLhistSig.find(hist);
      sigpit->second->Fill(ev, muons, electrons, jets,w);
    }
  }
  else  m_logger << INFO  <<"Type not set to sighist, is this a mistake?" << LQLogger::endmsg;
}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, electrons, jets, w);
    else {
      mapCLhistSig[hist] = new SignalPlots(hist);
      sigpit = mapCLhistSig.find(hist);
      sigpit->second->Fill(ev, electrons, jets, w);
    }
  }
  else  m_logger << INFO  <<"Type not set to sighist, is this a mistake?" << LQLogger::endmsg;
}


void AnalyzerCore::WriteHistograms() throw (LQError){
  // This function is called after the cycle is ran. It wrues all histograms to the output file. This function is not used by user. But by the contrioller code.
  WriteHists();
  WriteCLHists();
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
  for(map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.begin(); sigpit != mapCLhistSig.end(); sigpit++){
    
    Dir = m_outputFile->mkdir(sigpit->first);
    m_outputFile->cd( Dir->GetName() );
    sigpit->second->Write();
    m_outputFile->cd();
  }

  return;
}

void AnalyzerCore::WriteHists(){

  /// Open Output rootfile
  m_outputFile->cd();

  for(map<TString, TH1*>::iterator mapit = maphist.begin(); mapit != maphist.end(); mapit++){
    mapit->second->Write();
  }

  for(map<TString, TH2*>::iterator mapit = maphist2D.begin(); mapit != maphist2D.end(); mapit++){
    mapit->second->Write();
  }


  return;
}

TH1* AnalyzerCore::GetHist(TString hname){

  TH1* h = NULL;
  std::map<TString, TH1*>::iterator mapit = maphist.find(hname);
  if(mapit != maphist.end()) return mapit->second;
  else m_logger << INFO  << hname << " was not found in map" << LQLogger::endmsg;

  return h;
}



TH2* AnalyzerCore::GetHist2D(TString hname){

  TH2* h = NULL;
  std::map<TString, TH2*>::iterator mapit = maphist2D.find(hname);
  if(mapit != maphist2D.end()) return mapit->second;
  else m_logger << INFO  << hname << " was not found in map" << LQLogger::endmsg;

  return h;
}


bool AnalyzerCore::Zcandidate(std::vector<snu::KElectron> electrons, float interval, bool require_os){
  
  if(electrons.size()!=2) return false;
  if(require_os&&SameCharge(electrons)) return false;
  
  KParticle Z = electrons.at(0) + electrons.at(1);
  if(fabs(Z.M() - 90.) <  interval) return true;
  else return false;
  
}
  
bool AnalyzerCore::SameCharge(std::vector<snu::KElectron> electrons){
  
  if(electrons.size()!=2) return false;
  if(electrons.at(0).Charge() == electrons.at(1).Charge()) return true;
  return false;
}

int AnalyzerCore::NBJet(std::vector<snu::KJet> jets){
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
  }
  return nbjet;
}


float AnalyzerCore::CFRate(snu::KElectron el){

  if(fabs(el.Eta()) < 1.){
    if(el.Pt() < 30.) return 0.00001511625;
    else if(el.Pt() < 40.) return 0.0000358564;
    else if(el.Pt() < 50.) return 0.00003;
    else if(el.Pt() < 60.) return 0.00003;
    else if(el.Pt() < 80.) return 0.000058;
    else return 0.00006;
  }
  else if(fabs(el.Eta() ) < 1.6){
    if(el.Pt() < 30.) return 0.000158954;
    else if(el.Pt() < 40.) return 0.0001273112;
    else if(el.Pt() < 50.) return 0.00000982577;
    else if(el.Pt() < 60.) return 0.000165563;
    else if(el.Pt() < 80.) return 0.000382288;
    else return 0.000587109;
  }

  else if(fabs(el.Eta() ) < 2.5){
    if(el.Pt() < 30.) return 0.00017;
    else if(el.Pt() < 40.) return 0.00026163;
    else if(el.Pt() < 50.) return 0.000311835;
    else if(el.Pt() < 60.) return 0.000509239;
    else if(el.Pt() < 80.) return 0.000907024;
    else return 0.00154662;
  }
  return 1.;
  
}

bool AnalyzerCore::IsTight(snu::KMuon muon){
  /// ADD TIGHT MUON REQUIREMENT
  
  return true;
}

bool AnalyzerCore::IsTight(snu::KElectron electron, double rho){
  bool istight= true;
  
  Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
  int ifid = 0;
  if (fabs(electron.SCEta()) < 1.0) ifid = 0;
  else if (fabs(electron.SCEta()) < 1.479) ifid = 1;
  else if (fabs(electron.SCEta()) < 2.0) ifid = 2;
  else if (fabs(electron.SCEta()) < 2.2) ifid = 3;
  else if (fabs(electron.SCEta()) < 2.3) ifid = 4;
  else if (fabs(electron.SCEta()) < 2.4) ifid = 5;
  else ifid = 6;

  float LeptonRelIsoDR03(0.);
  float ElectronIsoDR03 =  electron.PFChargedHadronIso03() + max( electron.PFNeutralHadronIso03() + electron.PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
  if(electron.Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electron.Pt();
  else LeptonRelIsoDR03 = -999.;

  
  /// assuming electron is loose
  if(LeptonRelIsoDR03 >  0.09) istight=false;
  if(fabs(electron.dxy()) > 0.01) istight=false;
  
  return istight;
  
}

vector<snu::KElectron> AnalyzerCore::GetTruePrompt(vector<snu::KElectron> electrons){
  
  vector<snu::KElectron> prompt_electrons;
  for(unsigned int i = 0; i < electrons.size(); i++){
    if(!k_isdata){
      if(!(electrons.at(i).GetType() == 3 || electrons.at(i).GetType() == 4 || electrons.at(i).GetType() == 5)) prompt_electrons.push_back(electrons.at(i));
    }
    else prompt_electrons.push_back(electrons.at(i));
  }
  return prompt_electrons;
}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons, double rho){
  
  float ee_weight = 0.;
  if(k_electrons.size()==2){
    
    bool is_el1_tight    = IsTight(k_electrons.at(0), rho);
    bool is_el2_tight    = IsTight(k_electrons.at(1), rho);
    
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, is_el1_tight,is_el2_tight);
    
  }
  
  return ee_weight;
}

vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KElectron> el){

  vector<TLorentzVector> tl_el;
  for(vector<KElectron>::iterator itel=el.begin(); itel!=el.end(); ++itel) {
    TLorentzVector tmp_em;
    tmp_em.SetPtEtaPhiM((*itel).Pt(),(*itel).Eta(),(*itel).Phi(),(*itel).M());
    tl_el.push_back(tmp_em);
  }
  return tl_el;
}




