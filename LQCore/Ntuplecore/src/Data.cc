// $Id: Data.cxx
/***************************************************************************
 * @Project: LQAnalyzer
 * @Package: Core
 */

#ifndef DATA_cc
#define DATA_cc

#include "KMuon.h"
#include "KElectron.h"
#include "KPhoton.h"
#include "KJet.h"
#include "KGenJet.h"
#include "KEvent.h"
#include "KTrigger.h"
#include "KTruth.h"

// Local include(s):
#include "Data.h"
#include "SPointer.h"

// System include(s):  
#include <string.h>
#include <cxxabi.h>
#include <cstdlib>

// ROOT include(s): 
#include <TChain.h>
#include <TFile.h>
#include <TBranch.h>
#include <TList.h>
#include <TFriendElement.h>
#include <TVirtualIndex.h>
#include <TTreeCache.h>
//#include <iostream>

// STL include(s):                                                                                                      
#include <sstream>

Data::Data() : LQCycleBaseNTuple(), LQinput(true), k_inputmuons(0),  k_inputelectrons(0),k_inputphotons(0),  k_inputjets(0), k_inputgenjets(0),setting_ntuple_data(-1),TargetLumi(0.)
  
{

}

Data::~Data()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

TTree* Data::GetInputTree(){
  return fChain;
}

void Data::CheckCaching(){
  m_logger << INFO << fChain->GetCurrentFile()->GetBytesRead() << " bytes with calls: " << fChain->GetCurrentFile()->GetReadCalls() << LQLogger::endmsg;

}


void Data::GetEvent(Long64_t entry) throw( LQError )
{
  

  m_logger << DEBUG <<  "Number of branches =  " << m_inputbranches.size() << LQLogger::endmsg;

  if (!fChain)  throw LQError( "!!! Event is not Loaded", LQError::SkipCycle );
  m_logger << DEBUG <<  fChain << LQLogger::endmsg;
  fChain->LoadTree( entry );

  m_logger << DEBUG <<  fChain << LQLogger::endmsg;
  // Load the current entry for all the regular input variables:                              
  for( std::vector< TBranch* >::const_iterator it = m_inputbranches.begin();
       it != m_inputbranches.end(); ++it ) {
    m_logger << DEBUG <<  (*it) << LQLogger::endmsg;
    int nbytes =  ( *it )->GetEntry( entry,0);
    if(nbytes==0)  throw LQError( "!!! Event is not Loaded", LQError::SkipCycle );
  }
  
  return;
  
}

Int_t Data::GetEntry(Long64_t entry)
{
  // Read contents of entry.
   if (!fChain) return 0;
   m_logger << DEBUG << "Getting Entry " << entry << " in Data.cc " << fChain->GetEntry(entry,0)  << LQLogger::endmsg;
   int nbytes = fChain->GetEntry(entry,0);
   return nbytes;
}

Long64_t Data::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Data::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

  Reset();
  
  m_inputbranches.clear();
  
  // Set branch addresses and branch pointers                                                                                                                                 
  if (!tree) return;
  
  // do we need this at all now that we loop over the branches                                                                                                                
  // one-by-one?                                                                                                                                                              

  // Remove friends if any, for better performance                                                                                                                            
  bool skipFriends = true; // can be made configurable                                                                                                                        
  if( skipFriends ) {
    TList* flist = tree->GetListOfFriends();
    TIter nextf( flist );
    TFriendElement* fe = 0;
    while( ( fe = ( TFriendElement* ) nextf() ) ) {
      flist->Remove( fe );
      delete fe;
      fe = 0;
    }
  }

  bool deleteIndex = true; // can be made configurable                                                                                                                        
  if( deleteIndex ) {
    if( tree->GetTreeIndex() ) {
      tree->SetTreeIndex( 0 );
      delete tree->GetTreeIndex();
    }
  }

  fChain = tree;
  m_logger << INFO << "Chain entries = " << fChain->GetEntries() <<  " UseLQ ntuples =  " << LQinput<< LQLogger::endmsg;
  fCurrent = -1;
  if(LQinput)fChain->SetMakeClass(1);

  /// TESTS
  //fChain->SetMaxVirtualSize(100000000); 
  Int_t cachesize=100000000;
  fChain->SetCacheSize(cachesize);
  if(LQinput)fChain->SetBranchStatus("*",0);// disbles all branches                                                                                                                      
  if(setting_ntuple_data < 0) return;
  ConnectVariables(false, setting_ntuple_data); // -> false means not ALL branches are loaded

  //fChain->GetEntry(0,0);
  fChain->StopCacheLearningPhase();
  nentries = fChain->GetEntries();
  Notify();

  return;

}

Long64_t  Data::GetNEntries(){
  return nentries;
}

UInt_t Data::GetEventNumber(){
  if(LQinput)  return event;
  else return k_inputevent->EventNumber();
  return k_inputevent->EventNumber();

}

void Data::Reset(){

  /// clear vectors

  // Set object pointer
  
  // kEvent
  //run=0;
  //isData=0;
  gen_pt = 0;
  gen_eta = 0;
  gen_phi = 0;
  gen_energy = 0;
  gen_status = 0;
  gen_pdgid = 0;
  gen_motherindex = 0;
  pdfWeight = 0;
  //  CatVersion="";
  //kElectron
  electrons_absIso03 = 0;
  electrons_absIso04 = 0;
  electrons_chIso03 = 0;
  electrons_chIso04 = 0;
  electrons_dxy = 0;
  electrons_dz = 0;
  electrons_energy = 0;
  electrons_eta = 0;
  electrons_isGsfCtfScPixChargeConsistent = 0;
  electrons_m = 0;
  electrons_nhIso03 = 0;
  electrons_nhIso04 = 0;
  electrons_phIso03 = 0;
  electrons_phIso04 = 0;
  electrons_phi = 0;
  electrons_pt = 0;
  electrons_puChIso03 = 0;
  electrons_puChIso04 = 0;
  electrons_q = 0;
  electrons_relIso03 = 0;
  electrons_relIso04 = 0;
  electrons_scEta = 0;
  electrons_shiftedEnDown = 0;
  electrons_shiftedEnUp = 0;
  electrons_x = 0;
  electrons_y = 0;
  electrons_z = 0;
  
  //Photons
  photons_pt = 0;
  photons_eta = 0;
  photons_phi = 0;
  photons_energy = 0;
  photons_chargedHadronIso = 0;
  photons_puChargedHadronIso = 0;
  photons_neutralHadronIso = 0;
  photons_photonIso = 0;
  photons_rhoIso = 0;
  photons_chargedHadronIsoWithEA = 0;
  photons_neutralHadronIsoWithEA = 0;
  photons_photonIsoWithEA = 0;
  photons_sigmaietaieta = 0;
  photons_r9 = 0;
  photons_hovere = 0;
  photons_sceta = 0;
  photons_scphi = 0;
  photons_scrawenergy = 0;
  photons_scpreshowerenergy = 0;

  // Jets
  jets_CSVInclV2 = 0;
  jets_JetProbBJet = 0;
  jets_CMVAV2 = 0;

  jets_chargedEmEnergyFraction = 0;
  jets_energy = 0;
  jets_eta = 0;
  jets_PileupJetId = 0;
  jets_m = 0;
  jets_phi = 0;
  jets_pt = 0;
  jets_shiftedEnDown = 0;
  jets_shiftedEnUp = 0;
  jets_smearedRes = 0;
  jets_smearedResDown = 0;
  jets_smearedResUp = 0;
  jets_vtx3DSig = 0;
  jets_vtx3DVal = 0;
  jets_vtxMass = 0;
  met_phi = 0;
  met_pt = 0;
  met_sumet = 0;
  metNoHF_phi = 0;
  metNoHF_pt = 0;
  metNoHF_sumet = 0;
  metPfMva_phi = 0;
  metPfMva_pt = 0;
  metPfMva_sumet = 0;
  //  metPuppi_phi = 0;
  //metPuppi_pt = 0;
  //metPuppi_sumet = 0;
  muon_dxy = 0;
  muon_dz = 0;
  muon_energy = 0;
  muon_eta = 0;
  muon_m = 0;
  muon_normchi = 0;
  muon_phi = 0;
  muon_pt = 0;
  muon_q = 0;
  muon_relIso03 = 0;
  muon_relIso04 = 0;
  muon_shiftedEdown = 0;
  muon_shiftedEup = 0;
  muon_x = 0;
  muon_y = 0;
  muon_z = 0;
  photons_chargedHadronIso = 0;
  photons_chargedHadronIsoWithEA = 0;
  photons_energy = 0;
  photons_eta = 0;
  photons_hovere = 0;
  photons_neutralHadronIso = 0;
  photons_neutralHadronIsoWithEA = 0;
  photons_phi = 0;
  photons_photonIso = 0;
  photons_photonIsoWithEA = 0;
  photons_pt = 0;
  photons_puChargedHadronIso = 0;
  photons_r9 = 0;
  photons_rhoIso = 0;
  photons_sceta = 0;
  photons_scphi = 0;
  photons_scpreshowerenergy = 0;
  photons_scrawenergy = 0;
  photons_sigmaietaieta = 0;

  genjet_pt = 0;
  genjet_eta = 0;
  genjet_phi = 0;
  genjet_energy = 0;
  genjet_emf = 0;
  genjet_hadf = 0;
  genjet_pdgid = 0;
  slimmedGenJets_energy = 0;
  slimmedGenJets_eta = 0;
  slimmedGenJets_phi = 0;
  slimmedGenJets_pt = 0;

  electrons_electronID_loose = 0;
  electrons_electronID_medium = 0;
  electrons_electronID_tight = 0;
  electrons_electronID_veto = 0;
  electrons_isPF = 0;
  electrons_isTrigMVAValid = 0;
  electrons_mcMatched = 0;
  electrons_passConversionVeto = 0;
  electrons_electronID_heep = 0;
  electrons_electronID_mva_medium = 0;
  electrons_electronID_mva_tight = 0;
  electrons_electronID_mva_trig_medium = 0;
  electrons_electronID_mva_trig_tight = 0;
  jets_isLoose = 0;
  jets_isTight = 0;
  jets_isTightLepVetoJetID = 0;
  muon_isGlobal = 0;
  muon_isLoose = 0;
  muon_isMedium = 0;
  muon_isPF = 0;
  muon_isSoft = 0;
  muon_isTight = 0;
  muon_isTracker = 0;
  muon_matched = 0;
  photons_haspixseed = 0;
  photons_mcMatched = 0;
  photons_passelectronveto = 0;
  photons_photonID_loose = 0;
  photons_photonID_medium = 0;
  photons_photonID_mva = 0;
  photons_photonID_tight = 0;
  electrons_electronID_snu = 0;
  jets_hadronFlavour = 0;
  jets_partonFlavour = 0;
  jets_partonPdgId = 0;
  jets_vtxNtracks = 0;
  muon_matchedstations = 0;
  muon_trackerlayers = 0;
  muon_validhits = 0;
  muon_validmuonhits = 0;
  muon_validpixhits = 0;
  vtrignames = 0;
  vtrigps = 0;
  muon_trigmatch = 0;
  electron_trigmatch = 0;
  
 
}

void Data::SetLQNtupleInputType(int dataflag){
  setting_ntuple_data= dataflag;
}


void Data::SetLQNtupleInputType(bool lq){
  LQinput= lq;
}

std::string  Data::GetCatVersion(bool runLQ){
  
  if(runLQ) {
    return CatVersion;
  }
  else return k_inputevent->CatVersion();
}

void Data::SetTargetLumi(float tlumi){
  TargetLumi=tlumi;
}

void Data::SetCatVersion(std::string cv){
  CatVersion=cv;
}


void Data::ConnectVariables(bool setall, int setting_data){

  /// set all controlls which cranches are set 
  //#####   EVENT branches

  if(!LQinput){
    k_inputmuons=0;
    k_inputelectrons=0;
    k_inputphotons=0;
    k_inputjets=0;
    k_inputgenjets=0;
    k_inputevent=0;
    k_inputtrigger=0;
    k_inputtruth=0;
    b_inputmuons=0;
    b_inputelectrons=0;
    b_inputphotons=0;
    b_inputjets=0;
    b_inputgenjets=0;
    b_inputevent=0;
    b_inputtrigger=0;
    b_inputtruth=0;

    ConnectVariable("KEvent", k_inputevent, b_inputevent);
    ConnectVariable("KJets", k_inputjets,b_inputjets );
    ConnectVariable("KGenJets", k_inputgenjets,b_inputgenjets );
    ConnectVariable("KMuons", k_inputmuons, b_inputmuons);
    ConnectVariable("KElectrons", k_inputelectrons, b_inputelectrons);
    ConnectVariable("KPhotons", k_inputphotons, b_inputphotons);
    ConnectVariable("KTrigger", k_inputtrigger, b_inputtrigger);
    ConnectVariable("KTruth" , k_inputtruth, b_inputtruth);
    
  }  
  else{
    ConnectEvent(setting_data);
    ConnectMuons();
    ConnectMET();
    ConnectElectrons();
    ConnectPhotons();
    ConnectPFJets();
    ConnectTruth(setting_data);
    ConnectTrigger();
    
    if(setall) ConnectAllBranches();
  }
  return;
}
void Data::ConnectEvent(int setting_data){

  ConnectVariable("run", run, b_run);
  ConnectVariable("IsData", isData, b_isData);  
  ConnectVariable("lumi",lumi , b_lumi);
  ConnectVariable("event", event, b_event);
  
  // new for v7-4-6
  if(!TString(CatVersion).Contains("v7-4")){
    if( (setting_data == 1) || (setting_data == 3)){
      ConnectVariable("lumiMaskGold", lumiMaskGold, b_lumiMaskGold);
      ConnectVariable("lumiMaskSilver", lumiMaskSilver, b_lumiMaskSilver);
    }
    if( (setting_data ==2) || (setting_data ==3)){
      ConnectVariable("puWeightGold",puWeightGold, b_puWeightGold);
      ConnectVariable("puWeightGoldUp",puWeightGoldUp, b_puWeightGoldUp);
      ConnectVariable("puWeightGoldDn",puWeightGoldDn, b_puWeightGoldDn);
      ConnectVariable("puWeightSilver",puWeightSilver, b_puWeightSilver);
      ConnectVariable("puWeightSilverUp",puWeightSilverUp, b_puWeightSilverUp);
      ConnectVariable("puWeightSilverDn",puWeightSilverDn, b_puWeightSilverDn);
    }
  }
  ConnectVariable("nTrueInteraction", nTrueInteraction , b_nTrueInteraction);
 
  ConnectVariable("HBHENoiseFilter", HBHENoiseFilter, b_HBHENoiseFilter);
  ConnectVariable("CSCTightHaloFilter", csctighthaloFilter, b_csctighthaloFilter);
  ConnectVariable("EcalDeadCellTriggerPrimitiveFilter", ecalDCTRFilter, b_ecalDCTRFilter);
  ConnectVariable("eeBadScFilter",eeBadScFilter , b_eeBadScFilter);
  ConnectVariable("goodVertices", goodVertices, b_goodVertices);
  
  ConnectVariable("nGoodPV", nGoodPV, b_nGoodPV);
  ConnectVariable("nPV", nPV, b_nPV);
  


  ConnectVariable("vertex_X",vertex_X, b_vertex_X);
  ConnectVariable("vertex_Y",vertex_Y, b_vertex_Y);
  ConnectVariable("vertex_Z",vertex_Z, b_vertex_Z);

  return;}


void Data::ConnectTrigger(){
  
  //#####   Trigger branches
  ConnectVariable("vtrignames",vtrignames, b_vtrignames);
  ConnectVariable("vtrigps",vtrigps,b_vtrigps);
  ConnectVariable("muon_trigmatch", muon_trigmatch, b_muon_trigmatch);
  ConnectVariable("electron_trigmatch", electron_trigmatch, b_electron_trigmatch);
  
  return;
  
}


void Data::ConnectMuons(){
  
  //#####   Muon branches
  ConnectVariable("muon_isPF", muon_isPF , b_muon_isPF);
  ConnectVariable("muon_pt"  , muon_pt, b_muon_pt);
  ConnectVariable("muon_eta" , muon_eta , b_muon_eta);
  ConnectVariable("muon_isGlobal",muon_isGlobal , b_muon_isGlobal);

  
  ConnectVariable("muon_dxy",muon_dxy , b_muon_dxy);
  ConnectVariable("muon_dz",muon_dz , b_muon_dz);
  ConnectVariable("muon_energy",muon_energy , b_muon_energy);
  ConnectVariable("muon_isLoose",muon_isLoose , b_muon_isLoose);
  ConnectVariable("muon_isMedium", muon_isMedium, b_muon_isMedium);
  ConnectVariable("muon_isTight", muon_isTight, b_muon_isTight);
  ConnectVariable("muon_isSoft", muon_isSoft, b_muon_isSoft);
  ConnectVariable("muon_isTracker",muon_isTracker , b_muon_isTracker);
  ConnectVariable("muon_m",muon_m , b_muon_m);
  ConnectVariable("muon_matched",muon_matched , b_muon_matched);
  ConnectVariable("muon_matchedstations",muon_matchedstations , b_muon_matchedstations);
  ConnectVariable("muon_normchi", muon_normchi, b_muon_normchi);
  ConnectVariable("muon_phi",muon_phi , b_muon_phi);
  ConnectVariable("muon_q",muon_q , b_muon_q);
  ConnectVariable("muon_relIso03", muon_relIso03, b_muon_relIso03);
  ConnectVariable("muon_relIso04", muon_relIso04, b_muon_relIso04);
  ConnectVariable("muon_shiftedEdown", muon_shiftedEdown, b_muon_shiftedEdown);
  ConnectVariable("muon_shiftedEup",muon_shiftedEup , b_muon_shiftedEup);
  ConnectVariable("muon_trackerlayers", muon_trackerlayers, b_muon_trackerlayers);
  ConnectVariable("muon_validhits", muon_validhits, b_muon_validhits);
  ConnectVariable("muon_validmuonhits", muon_validmuonhits, b_muon_validmuonhits);
  ConnectVariable("muon_validpixhits", muon_validpixhits, b_muon_validpixhits);
  ConnectVariable("muon_x", muon_x, b_muon_x);
  ConnectVariable("muon_y", muon_y, b_muon_y);
  ConnectVariable("muon_z", muon_z, b_muon_z);
  return;}


void Data::ConnectPhotons(){
  
  if(!TString(CatVersion).Contains("v7-4")){
    ConnectVariable("photons_pt",photons_pt , b_photons_pt);
    ConnectVariable("photons_eta",photons_eta , b_photons_eta);
    ConnectVariable("photons_phi",photons_phi , b_photons_phi);
    ConnectVariable("photons_energy",photons_energy , b_photons_energy);
    ConnectVariable("photons_chargedHadronIso", photons_chargedHadronIso , b_photons_chargedHadronIso);
    ConnectVariable("photons_puChargedHadronIso", photons_puChargedHadronIso, b_photons_puChargedHadronIso);
    ConnectVariable("photons_neutralHadronIso", photons_neutralHadronIso, b_photons_neutralHadronIso);
    ConnectVariable("photons_photonIso", photons_photonIso, b_photons_photonIso);
    ConnectVariable("photons_rhoIso", photons_rhoIso, b_photons_rhoIso);
    ConnectVariable("photons_chargedHadronIsoWithEA", photons_chargedHadronIsoWithEA, b_photons_chargedHadronIsoWithEA);
    ConnectVariable("photons_neutralHadronIsoWithEA", photons_neutralHadronIsoWithEA, b_photons_neutralHadronIsoWithEA);
    ConnectVariable("photons_photonIsoWithEA", photons_photonIsoWithEA, b_photons_photonIsoWithEA);
    ConnectVariable("photons_sigmaietaieta", photons_sigmaietaieta, b_photons_sigmaietaieta);
    ConnectVariable("photons_r9", photons_r9, b_photons_r9);
    ConnectVariable("photons_hovere", photons_hovere, b_photons_hovere);
    ConnectVariable("photons_sceta", photons_sceta, b_photons_sceta);
    ConnectVariable("photons_scphi", photons_scphi, b_photons_scphi);
    ConnectVariable("photons_scrawenergy", photons_scrawenergy, b_photons_scrawenergy);
    ConnectVariable("photons_scpreshowerenergy", photons_scpreshowerenergy, b_photons_scpreshowerenergy);
    ConnectVariable("photons_photonID_loose", photons_photonID_loose, b_photons_photonID_loose);
    ConnectVariable("photons_photonID_medium", photons_photonID_medium, b_photons_photonID_medium);
    ConnectVariable("photons_photonID_tight", photons_photonID_tight, b_photons_photonID_tight);
    ConnectVariable("photons_photonID_mva", photons_photonID_mva, b_photons_photonID_mva);
    ConnectVariable("photons_mcMatched", photons_mcMatched, b_photons_mcMatched);
    ConnectVariable("photons_haspixseed", photons_haspixseed, b_photons_haspixseed);
    ConnectVariable("photons_passelectronveto",photons_passelectronveto , b_photons_passelectronveto);
  }
  
 }

void Data::ConnectElectrons(){

  //#####   Electron branches
  ConnectVariable("electrons_absIso03", electrons_absIso03, b_electrons_absIso03);
  ConnectVariable("electrons_absIso04", electrons_absIso04, b_electrons_absIso04);

  ConnectVariable("electrons_chIso03", electrons_chIso03, b_electrons_chIso03);
  ConnectVariable("electrons_chIso04", electrons_chIso04, b_electrons_chIso04);
  ConnectVariable("electrons_dxy", electrons_dxy, b_electrons_dxy);
  ConnectVariable("electrons_dz", electrons_dz, b_electrons_dz);
  ConnectVariable("electrons_electronID_loose", electrons_electronID_loose, b_electrons_electronID_loose);
  ConnectVariable("electrons_electronID_medium", electrons_electronID_medium, b_electrons_electronID_medium);
  ConnectVariable("electrons_electronID_veto", electrons_electronID_veto, b_electrons_electronID_veto);
  ConnectVariable("electrons_electronID_tight", electrons_electronID_tight, b_electrons_electronID_tight);
  ConnectVariable("electrons_electronID_snu", electrons_electronID_snu, b_electrons_electronID_snu);
  ConnectVariable("electrons_electronID_heep", electrons_electronID_heep ,b_electrons_electronID_heep);
  ConnectVariable("electrons_electronID_mva_medium",electrons_electronID_mva_medium,b_electrons_electronID_mva_medium);
  ConnectVariable("electrons_electronID_mva_tight",electrons_electronID_mva_tight,b_electrons_electronID_mva_tight);
  ConnectVariable("electrons_electronID_mva_trig_medium",electrons_electronID_mva_trig_medium,b_electrons_electronID_mva_trig_medium);
  ConnectVariable("electrons_electronID_mva_trig_tight",electrons_electronID_mva_trig_tight,b_electrons_electronID_mva_trig_tight);
  ConnectVariable("electrons_energy", electrons_energy, b_electrons_energy);
  ConnectVariable("electrons_eta", electrons_eta, b_electrons_eta);
  ConnectVariable("electrons_isPF", electrons_isPF, b_electrons_isPF);
  if(!TString(CatVersion).Contains("v7-4"))  ConnectVariable("electrons_isTrigMVAValid", electrons_isTrigMVAValid, b_electrons_isTrigMVAValid);
  ConnectVariable("electrons_m", electrons_m, b_electrons_m);
  ConnectVariable("electrons_mcMatched", electrons_mcMatched, b_electrons_mcMatched);
  ConnectVariable("electrons_nhIso03", electrons_nhIso03, b_electrons_nhIso03);
  ConnectVariable("electrons_nhIso04", electrons_nhIso04, b_electrons_nhIso04);
  ConnectVariable("electrons_passConversionVeto", electrons_passConversionVeto, b_electrons_passConversionVeto);
  ConnectVariable("electrons_phIso03", electrons_phIso03, b_electrons_phIso03);
  ConnectVariable("electrons_phIso04", electrons_phIso04, b_electrons_phIso04);
  ConnectVariable("electrons_phi", electrons_phi, b_electrons_phi);
  ConnectVariable("electrons_pt", electrons_pt, b_electrons_pt);
  ConnectVariable("electrons_puChIso03", electrons_puChIso03, b_electrons_puChIso03);
  ConnectVariable("electrons_puChIso04", electrons_puChIso04, b_electrons_puChIso04);
  ConnectVariable("electrons_q", electrons_q, b_electrons_q);
  ConnectVariable("electrons_relIso03", electrons_relIso03, b_electrons_relIso03);
  ConnectVariable("electrons_relIso04", electrons_relIso04, b_electrons_relIso04);
  ConnectVariable("electrons_scEta", electrons_scEta, b_electrons_scEta);
  ConnectVariable("electrons_shiftedEnDown", electrons_shiftedEnDown, b_electrons_shiftedEnDown);
  ConnectVariable("electrons_shiftedEnUp", electrons_shiftedEnUp, b_electrons_shiftedEnUp);
  ConnectVariable("electrons_x", electrons_x, b_electrons_x);
  ConnectVariable("electrons_y", electrons_y, b_electrons_y);
  ConnectVariable("electrons_z", electrons_z, b_electrons_z);
  ConnectVariable("electrons_isGsfCtfScPixChargeConsistent" , electrons_isGsfCtfScPixChargeConsistent, b_electrons_isGsfCtfScPixChargeConsistent);
  return;
}

void Data::ConnectPFJets(){

  m_logger << DEBUG << "ConnectPFJets : "<< LQLogger::endmsg;

  //#####   Jet branches
  //  ConnectVariable("rhoJets", rhoJets, b_rhoJets);
  /// TLV variables

  if(!TString(CatVersion).Contains("v7-4")){
    ConnectVariable("jets_CSVInclV2", jets_CSVInclV2, b_jets_CSVInclV2);
    ConnectVariable("jets_CMVAV2", jets_CMVAV2, b_jets_CMVAV2);
    ConnectVariable("jets_JetProbBJet", jets_JetProbBJet, b_jets_JetProbBJet);
  }
  else{
    ConnectVariable("jets_CVSInclV2", jets_CSVInclV2, b_jets_CSVInclV2);
  }

  ConnectVariable("jets_chargedEmEnergyFraction",jets_chargedEmEnergyFraction,b_jets_chargedEmEnergyFraction);
  ConnectVariable("jets_energy", jets_energy, b_jets_energy);

  ConnectVariable("jets_eta",jets_eta,b_jets_eta);
  ConnectVariable("jets_hadronFlavour",jets_hadronFlavour,b_jets_hadronFlavour);
  ConnectVariable("jets_isLoose",jets_isLoose,b_jets_isLoose);
  ConnectVariable("jets_PileupJetId",jets_PileupJetId, b_jets_PileupJetId);

  ConnectVariable("jets_isTight",jets_isTight,b_jets_isTight);
  ConnectVariable("jets_isTightLepVetoJetID",jets_isTightLepVetoJetID,b_jets_isTightLepVetoJetID);
  ConnectVariable("jets_m",jets_m,b_jets_m);
  ConnectVariable("jets_partonFlavour",jets_partonFlavour,b_jets_partonFlavour);
  ConnectVariable("jets_partonPdgId",jets_partonPdgId,b_jets_partonPdgId);
  ConnectVariable("jets_phi",jets_phi,b_jets_phi);
  ConnectVariable("jets_pt",jets_pt,b_jets_pt);
  ConnectVariable("jets_shiftedEnDown",jets_shiftedEnDown,b_jets_shiftedEnDown);
  ConnectVariable("jets_shiftedEnUp",jets_shiftedEnUp,b_jets_shiftedEnUp);
  ConnectVariable("jets_smearedRes",jets_smearedRes,b_jets_smearedRes);
  ConnectVariable("jets_smearedResDown",jets_smearedResDown,b_jets_smearedResDown);
  ConnectVariable("jets_smearedResUp",jets_smearedResUp,b_jets_smearedResUp);
  ConnectVariable("jets_vtxMass",jets_vtxMass,b_jets_vtxMass);
  ConnectVariable("jets_vtx3DVal", jets_vtx3DVal, b_jets_vtx3DVal);
  ConnectVariable("jets_vtx3DSig", jets_vtx3DSig, b_jets_vtx3DSig);
  ConnectVariable("jets_vtxNtracks", jets_vtxNtracks, b_jets_vtxNtracks);
  return;
}


void Data::ConnectMET(){

  //#####   MET branches

  ConnectVariable("met_phi",met_phi , b_met_phi);
  ConnectVariable("met_pt", met_pt , b_met_pt);
  ConnectVariable("met_sumet", met_sumet , b_met_sumet);

  //ConnectVariable("metPuppi_pt",metPuppi_pt , b_metPuppi_pt);
  //ConnectVariable("metPuppi_phi",metPuppi_phi , b_metPuppi_phi);
  //ConnectVariable("metPuppi_sumet", metPuppi_sumet , b_metPuppi_sumet);
  ConnectVariable("metNoHF_phi",metNoHF_phi , b_metNoHF_phi);
  ConnectVariable("metNoHF_pt", metNoHF_pt , b_metNoHF_pt);
  ConnectVariable("metNoHF_sumet", metNoHF_sumet , b_metNoHF_sumet);
  //ConnectVariable("metPfMva_phi",metPfMva_phi , b_metPfMva_phi);
  //ConnectVariable("metPfMva_pt", metPfMva_pt , b_metPfMva_pt);
  //ConnectVariable("metPfMva_sumet", metPfMva_sumet , b_metPfMva_sumet);

  if(!TString(CatVersion).Contains("v7-4")){
    ConnectVariable("met_muonEn_Px_up", met_muonEn_Px_up, b_met_muonEn_Px_up);
    ConnectVariable("met_muonEn_Py_up", met_muonEn_Py_up, b_met_muonEn_Py_up);
    ConnectVariable("met_muonEn_Px_down", met_muonEn_Px_down, b_met_muonEn_Px_down);
    ConnectVariable("met_muonEn_Py_down", met_muonEn_Py_down, b_met_muonEn_Py_down);
    ConnectVariable("met_electronEn_Px_up", met_electronEn_Px_up, b_met_electronEn_Px_up);
    ConnectVariable("met_electronEn_Py_up", met_electronEn_Py_up, b_met_electronEn_Py_up);
    ConnectVariable("met_electronEn_Px_down", met_electronEn_Px_down, b_met_electronEn_Px_down);
    ConnectVariable("met_electronEn_Py_down", met_electronEn_Py_down, b_met_electronEn_Py_down);
    ConnectVariable("met_unclusteredEn_Px_up", met_unclusteredEn_Px_up, b_met_unclusteredEn_Px_up);
    ConnectVariable("met_unclusteredEn_Py_up", met_unclusteredEn_Py_up, b_met_unclusteredEn_Py_up);
    ConnectVariable("met_unclusteredEn_Px_down", met_unclusteredEn_Px_down, b_met_unclusteredEn_Px_down);
    ConnectVariable("met_unclusteredEn_Py_down", met_unclusteredEn_Py_down, b_met_unclusteredEn_Py_down);
    ConnectVariable("met_unclusteredEn_SumEt_down", met_unclusteredEn_SumEt_down, b_met_unclusteredEn_SumEt_down);
    ConnectVariable("met_unclusteredEn_SumEt_up", met_unclusteredEn_SumEt_up, b_met_unclusteredEn_SumEt_up);
    ConnectVariable("met_jetEn_Px_up", met_jetEn_Px_up, b_met_jetEn_Px_up);
    ConnectVariable("met_jetEn_Py_up", met_jetEn_Py_up, b_met_jetEn_Py_up);
    ConnectVariable("met_jetEn_Px_down", met_jetEn_Px_down, b_met_jetEn_Px_down);
    ConnectVariable("met_jetEn_Py_down", met_jetEn_Py_down, b_met_jetEn_Py_down);
    ConnectVariable("met_jetEn_SumEt_down", met_jetEn_SumEt_down, b_met_jetEn_SumEt_down);
    ConnectVariable("met_jetEn_SumEt_up", met_jetEn_SumEt_up, b_met_jetEn_SumEt_up);
    ConnectVariable("met_jetRes_Px_up", met_jetRes_Px_up, b_met_jetRes_Px_up);
    ConnectVariable("met_jetRes_Py_up", met_jetRes_Py_up, b_met_jetRes_Py_up);
    ConnectVariable("met_jetRes_Px_down", met_jetRes_Px_down, b_met_jetRes_Px_down);
    ConnectVariable("met_jetRes_Py_down", met_jetRes_Py_down, b_met_jetRes_Py_down);
    ConnectVariable("met_jetRes_SumEt_down", met_jetRes_SumEt_down, b_met_jetRes_SumEt_down);
    ConnectVariable("met_jetRes_SumEt_up", met_jetRes_SumEt_up, b_met_jetRes_SumEt_up);
  }
  return;
}

void Data::ConnectTruth(int setting_data){

  //#####   Truth branches

  //  ConnectVariable("GenSumETTrue", GenSumETTrue, b_GenSumETTrue);
  if(setting_data == 1) return;
  if(!TString(CatVersion).Contains("v7-4")){
    ConnectVariable("genjet_pt",genjet_pt ,b_genjet_pt);
    ConnectVariable("genjet_eta",genjet_eta ,b_genjet_eta);
    ConnectVariable("genjet_phi",genjet_phi ,b_genjet_phi);
    ConnectVariable("genjet_energy",genjet_energy ,b_genjet_energy);
    ConnectVariable("genjet_emf",genjet_emf ,b_genjet_emf);
    ConnectVariable("genjet_hadf",genjet_hadf ,b_genjet_hadf);
    ConnectVariable("genjet_pdgid",genjet_pdgid ,b_genjet_pdgid);
  }
  else{
    ConnectVariable("slimmedGenJets_eta", slimmedGenJets_eta,b_slimmedGenJets_eta);
    ConnectVariable("slimmedGenJets_pt", slimmedGenJets_pt,b_slimmedGenJets_pt);
    ConnectVariable("slimmedGenJets_phi", slimmedGenJets_phi,b_slimmedGenJets_phi);
    ConnectVariable("slimmedGenJets_energy", slimmedGenJets_energy,b_slimmedGenJets_energy);
  }
 
  ConnectVariable("genWeightQ",genWeightQ, b_genWeightQ);
  ConnectVariable("genWeightX1",genWeightX1, b_genWeightX1);
  ConnectVariable("genWeightX2",genWeightX2, b_genWeightX2);
  ConnectVariable("lheWeight",lheWeight, b_lheWeight);
  ConnectVariable("genWeight",genWeight, b_genWeight);
  ConnectVariable("genWeight_id1",genWeight_id1, b_genWeight_id1);
  ConnectVariable("genWeight_id2", genWeight_id2, b_genWeight_id2);
  ConnectVariable("gen_pt",gen_pt ,b_gen_pt );
  ConnectVariable("gen_eta",gen_eta ,b_gen_eta );
  ConnectVariable("gen_phi",gen_phi ,b_gen_phi );
  ConnectVariable("gen_energy",gen_energy ,b_gen_energy );
  ConnectVariable("gen_status",gen_status ,b_gen_status );
  ConnectVariable("gen_pdgid",gen_pdgid ,b_gen_pdgid );
  ConnectVariable("gen_motherindex",gen_motherindex ,b_gen_motherindex );

  //  ConnectVariable("pdfWeight", pdfWeight, b_pdfWeight);
  
  return;
}


void Data::ConnectAllBranches(){

  ///#############################################################################                                                                                              
  //   These are variabels not currenly set: or read: BUT are in ntuples                                                                                                        

  return;
}



template< typename T >
bool Data::ConnectVariable( const char* branchName,
			    T*& variable, TBranch* br){

  // Check if the branch actually exists:                                                                                                                                                                                                                                                             
  TBranch* branch_info;
  if( ! (branch_info = fChain->GetBranch( branchName ) ) ) {    
    m_logger << INFO << "Branch NOT FOUND " << branchName << LQLogger::endmsg;
    return false;
  }
  
  variable = new T();
  
  const char* type_name = typeid( *variable ).name();
  // The object pointers have to be initialised to zero before                                                                                                             
  // connecting them to the branches       
  delete variable; 
  if( strlen( type_name ) == 1 ) {

    throw LQError( "ConnectVariable(...) specialised for object pointers calle\
d "
		  "with a simple variable.", LQError::SkipCycle );

  } else {

    
    variable = 0;
    fChain->SetBranchStatus(TString(branchName)+ "*",1);
    fChain->SetBranchAddress(branchName, &variable, &br);
    //if(TString(branchName).Contains("Event")) br->SetMakeClass(1);

    m_inputVarPointers.push_back( new SPointer< T >( variable ) );
  }
  //br->SetAutoDelete(kTRUE);
  fChain->AddBranchToCache( branchName, kTRUE );
  

  return true;
}

template< typename T >
bool Data::ConnectVariable(  const char* branchName,
			     T& variable, TBranch* br){
  

  // Check if the branch actually exists:                                      
  TBranch* branch_info;
  if( ! (branch_info = fChain->GetBranch( branchName ) ) ) {    
    m_logger << INFO << "Branch NOT FOUND " << branchName << LQLogger::endmsg;
    return false;
  }


  fChain->SetBranchStatus(branchName,1);
  fChain->SetBranchAddress(branchName, &variable, &br);
  //br->SetAutoDelete(kTRUE);    
  fChain->AddBranchToCache( branchName, kTRUE );

  return true;
}

void Data::setBranchStatus(void) {

  fChain->SetBranchStatus("*",1);


}

Bool_t Data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t Data::Cut(Long64_t entry)
{
  fChain->GetEntry(entry);
  
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

#endif
