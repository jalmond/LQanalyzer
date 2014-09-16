// $Id: AnalyzerCore.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes 
#include "AnalyzerCore.h"
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

  TFile *infile_sf = TFile::Open((analysisdir+ "HMN_FinalSFNoJets.root").c_str());
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
 
  MuonSF =  dynamic_cast<TH2F*> (( infile_sf->Get("etavspt"))->Clone());
  infile_sf->Close();
  delete infile_sf;
  origDir->cd();
  
  string lqdir = getenv("LQANALYZER_DIR");

  m_fakeobj = new HNCommonLeptonFakes(lqdir+"/HNCommonLeptonFakes/share/");
  rmcor = new rochcor2012();

}


TDirectory* AnalyzerCore::getTemporaryDirectory(void) const
{

  
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:               
    std::stringstream dirname;
    dirname << "AnalyzerCore_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                        
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;
}



double AnalyzerCore::MuonScaleFactor(double eta, double pt, int sys){
  
  double sf = 0.;
  if(fabs(eta) > 2.4) return 1.;
  if(pt < 15.) return 1.;
  int bin = MuonSF->FindBin(fabs(eta),pt);
  
  sf = MuonSF->GetBinContent(bin);

  if(sys==1) sf*= sqrt(1.02); 
  if(sys==-1) sf/= sqrt(1.02); 
  
  return sf;
  
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
  

std::vector<snu::KElectron> AnalyzerCore::ShiftElectronEnergy(std::vector<snu::KElectron> electrons, bool applyshift){
  
  std::vector<snu::KElectron> shiftedel;

  for(unsigned int iel=0; iel < electrons.size(); iel++){
    float scale =0.98;

    if(applyshift)electrons.at(iel).SetPtEtaPhiM(electrons.at(iel).Pt()*scale, electrons.at(iel).Eta(), electrons.at(iel).Phi(), 0.511e-3);
    shiftedel.push_back(electrons.at(iel));
  }    
  return shiftedel;
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

void AnalyzerCore::MakeHistograms2D(TString hname, int nbinsx,  float xbins[], int nbinsy,  float ybins[]) {

  maphist2D[hname] =  new TH2F(hname.Data(),hname.Data(),nbinsx , xbins, nbinsy,ybins);
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

void AnalyzerCore::FillHist(TString histname, float valuex, float valuey, float w, float xbins[], int nxbins, float ybins[], int nybins){
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist2D(histname)) GetHist2D(histname)->Fill(valuex,valuey, w);

  else{
    if (nxbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms2D(histname, nxbins, xbins, nybins, ybins );
    if(GetHist2D(histname)) GetHist2D(histname)->Fill(valuex, valuey, w);
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

    if(mapit->first.Contains("closejet")){
      if(!m_outputFile->GetDirectory( "closejet" )){
	Dir = m_outputFile->mkdir("closejet");
	m_outputFile->cd( Dir->GetName() );
      }
      else  m_outputFile->cd("closejet");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("awayjet")){
      if(!m_outputFile->GetDirectory("awayjet")){
	Dir = m_outputFile->mkdir("awayjet");
	m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("awayjet");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("FakeBkg")){
      if(!m_outputFile->GetDirectory("FakeBkg")){
	Dir = m_outputFile->mkdir("FakeBkg");
	m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("FakeBkg");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else     mapit->second->Write();
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
  else m_logger << DEBUG  << hname << " was not found in map" << LQLogger::endmsg;

  return h;
}



TH2* AnalyzerCore::GetHist2D(TString hname){

  TH2* h = NULL;
  std::map<TString, TH2*>::iterator mapit = maphist2D.find(hname);
  if(mapit != maphist2D.end()) return mapit->second;
  else m_logger << DEBUG  << hname << " was not found in map" << LQLogger::endmsg;

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
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  return nbjet;
}


double AnalyzerCore::MuonDYMassCorrection(std::vector<snu::KMuon> mu, double w){
  
  if(mu.size()< 2) return 0.;
  snu::KParticle Z = mu.at(0) + mu.at(1);
  
  double factor (1.);
  if(Z.M() > 90.){
    factor = 8.37401e-01 + 1.61277e-03*Z.M();
  }
  return w*factor;
}

float AnalyzerCore::CFRate(snu::KElectron el){
  
  Double_t frac = 0. ;
  float pt = el.Pt();
  Double_t p0 = 0. ;
  Double_t p1 = 0. ;

  Double_t scale_factor_EE = 1. ;
  Double_t scale_factor_BB = 1. ;


  if( fabs(el.Eta()) <= 1.4442 ) {
    scale_factor_BB = 1.29;
    //--region:  1/pt > 0.02
    p0 = 8.01e-05 ; p1 = -1.80e-03 ;
    frac = p0 + p1*(1./pt) ;
    
    if( (1./pt) <= 0.02 ) {
      p0 = 3.13e-04 ;  p1 = -1.43e-02 ;
      frac = max(p0 + p1*(1./pt), frac);
    }
    frac *= scale_factor_BB ;
    
  } else {  // fabs(eta) > 1.4
    
    
    scale_factor_EE = 1.40 ; //
    //--region:  1/pt > 0.02
    p0 = 4.91e-04 ; p1 = -0.952e-02 ;
    frac = p0 + p1*(1./pt) ;

    if( (1./pt) <= 0.02 ){
      p0 = 2.70e-03 ;  p1 = -1.21e-01 ;
      frac = max(p0 + p1*(1./pt), frac) ;
    }
    frac *= scale_factor_EE ;
  }
  
  return float(frac) ;
}

bool AnalyzerCore::IsTight(snu::KMuon muon){
  /// ADD TIGHT MUON REQUIREMENT
  float reliso=0.;
  if (muon.Pt() > 0.01)  reliso = (muon.SumIsoCHDR03() + std::max(0.0, muon.SumIsoNHDR03() + muon.SumIsoPHDR03() - 0.5* muon.SumPUIsoR03()))/muon.Pt() ;
  else reliso = 9999.;
  if (reliso<0) reliso=0.0001;
  

  if(( reliso >= 0.05)) return false;
  if(( muon.GlobalChi2() >= 10.)) return false;
 
  if(fabs(muon.dXY()) >= 0.005) return false; 
  return true;
}


bool AnalyzerCore::IsTight(snu::KElectron el, double jetrho , double dxy, double biso, double eiso, bool usedr3, bool usetrkiso, bool usetight){
  
  return eventbase->GetElectronSel()->HNIsTight(el, jetrho, dxy, biso, eiso, usedr3, usetrkiso, usetight, false);

}
  

bool AnalyzerCore::IsTight(snu::KElectron electron, double rho){

  return eventbase->GetElectronSel()->HNIsTight(electron, rho, false);
}

vector<snu::KElectron> AnalyzerCore::GetTruePrompt(vector<snu::KElectron> electrons, bool keep_chargeflip, bool keepfake){
  
  vector<int> toremove;
  if(!keepfake){
    toremove.push_back(1);
    toremove.push_back(2);
    toremove.push_back(3);
  }
  if(!keep_chargeflip){
    toremove.push_back(6);
    toremove.push_back(4);
    toremove.push_back(5);
  }

  toremove.push_back(8);
  toremove.push_back(9);
  
  vector<snu::KElectron> prompt_electrons;
  for(unsigned int i = 0; i < electrons.size(); i++){
    if(!k_isdata){
      bool remove_el=false;
      for(unsigned int j=0; j < toremove.size(); j++){
	if(electrons.at(i).GetType() == toremove.at(j)) remove_el=true;
      }
      if(!remove_el) prompt_electrons.push_back(electrons.at(i));
    }// Data
    else prompt_electrons.push_back(electrons.at(i));
  }/// loop
  
  return prompt_electrons;
}



void AnalyzerCore::CorrectMuonMomentum(vector<snu::KMuon>& k_muons){
  
  vector<TLorentzVector> tlv_muons = MakeTLorentz(k_muons);
  int imu(0);
  for(std::vector<snu::KMuon>::iterator it = k_muons.begin(); it != k_muons.end(); it++, imu++){
    float qter =1.; /// uncertainty
    if(k_isdata)rmcor->momcor_data(tlv_muons[imu], float(it->Charge()), 0, qter);
    else rmcor->momcor_mc(tlv_muons[imu], float(it->Charge()), 0, qter);
    it->SetPtEtaPhiM(tlv_muons[imu].Pt(),tlv_muons[imu].Eta(), tlv_muons[imu].Phi(), tlv_muons[imu].M());
  }
}


float AnalyzerCore::Get_DataDrivenWeight_EM(vector<snu::KMuon> k_muons, vector<snu::KElectron> k_electrons, double rho){

  float em_weight = 0.;
  if(k_muons.size()==1 && k_electrons.size()==1){

    bool is_mu1_tight    = IsTight(k_muons.at(0));
    bool is_el1_tight    = IsTight(k_electrons.at(0),rho);

    vector<TLorentzVector> muons=MakeTLorentz(k_muons);
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);


    em_weight =m_fakeobj->get_dilepton_em_eventweight(muons,electrons, is_mu1_tight,is_el1_tight);
  }

  return em_weight;
}

float AnalyzerCore::Get_DataDrivenWeight_MM(vector<snu::KMuon> k_muons){

  float mm_weight = 0.;
  if(k_muons.size()==2){
    
    bool is_mu1_tight    = IsTight(k_muons.at(0));
    bool is_mu2_tight    = IsTight(k_muons.at(1));

    vector<TLorentzVector> muons=MakeTLorentz(k_muons);

    mm_weight =m_fakeobj->get_dilepton_mm_eventweight(muons,  is_mu1_tight,is_mu2_tight);
  }

  return mm_weight;
}




float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons,  double rho){
  
  return Get_DataDrivenWeight_EE(k_electrons, rho, 0.01, 0.09, 0.05, "40"); /// dxy cut ,  biso, eciso, awayjet pt
}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons ,  double rho,bool usedr3, bool usetrkiso, bool usetight,  double dxy, double biso, double eiso, TString cut){

  float ee_weight = 0.;
  if(k_electrons.size()==2){
    
    bool is_el1_tight    = IsTight(k_electrons.at(0),  rho, dxy, biso, eiso, usedr3, usetrkiso, usetight);
    bool is_el2_tight    = IsTight(k_electrons.at(1),  rho, dxy, biso, eiso, usedr3, usetrkiso, usetight);

    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, is_el1_tight,is_el2_tight, cut);

  }
  return ee_weight;

}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons, double rho, double dxy, double biso, double eiso, TString cut){
  
  float ee_weight = 0.;
  if(k_electrons.size()==2){
    
    bool is_el1_tight    = IsTight(k_electrons.at(0),  rho, dxy, biso, eiso, true, false, true);
    bool is_el2_tight    = IsTight(k_electrons.at(1),  rho, dxy, biso, eiso, true, false, true);
    
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, is_el1_tight,is_el2_tight, cut);
    
  }
  return ee_weight;
}



float  AnalyzerCore::Get_DataDrivenWeight_E(vector<snu::KElectron> k_electrons, int njets, int nbjets, double rho, double dxy, double biso, double eiso, bool usedr3, bool usetrkiso, bool    usetight,TString cut, bool applypucorr){
  
  if(k_electrons.size()==1){
    bool is_el1_tight    = IsTight(k_electrons.at(0), rho, dxy, biso, eiso, usedr3, usetrkiso, usetight);
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    
    TString rcut = cut;
    
    float r = 1.;


    float f = m_fakeobj->getFakeRate_electronEta(0, k_electrons.at(0).Pt(), fabs(k_electrons.at(0).Eta()), cut);
    
    float w = m_fakeobj->lepton_weight(!is_el1_tight, r,f);
    return w;
  }
  return 0.;
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

vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KMuon> mu){
  
  vector<TLorentzVector> tl_mu;
  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    TLorentzVector tmp_mu;
    tmp_mu.SetPtEtaPhiM((*itmu).Pt(),(*itmu).Eta(),(*itmu).Phi(),(*itmu).M());
    tl_mu.push_back(tmp_mu);
  }
  return tl_mu;
}


vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiM((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).M());
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}





