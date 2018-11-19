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
#include "KFatJet.h"
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

Data::Data() : LQCycleBaseNTuple(), LQinput(true), k_inputmuons(0),  k_inputelectrons(0),k_inputphotons(0),  k_inputjets(0),k_inputfatjets(0), k_inputgenjets(0),k_inputevent(0),k_inputtrigger(0),k_inputtruth(0), setting_ntuple_data(-1),TargetLumi(0.),k_flags(0), k_cat_version(-1)
  
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
   m_logger << DEBUG << "LOADING TREE" << LQLogger::endmsg;
   Long64_t centry = fChain->LoadTree(entry);
   m_logger << DEBUG << "LOADING TREE 2" << LQLogger::endmsg;
   if (centry < 0) return centry;
   //if (!fChain->InheritsFrom(TChain::Class()))  return centry;
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

  //CatVersion = 0;
  pfMET_pt_shifts = 0;
  pfMET_phi_shifts = 0;
  pfMET_SumEt_shifts = 0;
  pfMET_Type1_pt_shifts = 0;
  pfMET_Type1_phi_shifts = 0;
  pfMET_Type1_SumEt_shifts = 0;
  pfMET_Type1_PhiCor_pt_shifts = 0;
  pfMET_Type1_PhiCor_phi_shifts = 0;
  pfMET_Type1_PhiCor_SumEt_shifts = 0;

  HLT_TriggerName = 0;

  jet_pt = 0;
  jet_eta = 0;
  jet_phi = 0;
  jet_charge = 0;
  jet_area = 0;
  jet_partonFlavour = 0;
  jet_hadronFlavour = 0;
  jet_CSVv2 = 0;
  jet_DeepCSV = 0;
  jet_CvsL = 0;
  jet_CvsB = 0;
  jet_DeepCvsL = 0;
  jet_DeepCvsB = 0;
  jet_chargedHadronEnergyFraction = 0;
  jet_neutralHadronEnergyFraction = 0;
  jet_neutralEmEnergyFraction = 0;
  jet_chargedEmEnergyFraction = 0;
  jet_chargedMultiplicity = 0;
  jet_neutralMultiplicity = 0;
  jet_tightJetID = 0;
  jet_tightLepVetoJetID = 0;
  jet_partonPdgId = 0;
  jet_m = 0;
  jet_energy = 0;
  jet_PileupJetId = 0;
  jet_shiftedEnUp = 0;
  jet_shiftedEnDown = 0;
  jet_smearedRes = 0;
  jet_smearedResUp = 0;
  jet_smearedResDown = 0;
  jet_JECL1FastJet = 0;
  jet_JECFull = 0;

  fatjet_pt = 0;
  fatjet_eta = 0;
  fatjet_phi = 0;
  fatjet_charge = 0;
  fatjet_area = 0;
  fatjet_partonFlavour = 0;
  fatjet_hadronFlavour = 0;
  fatjet_CSVv2 = 0;
  fatjet_tightJetID = 0;
  fatjet_tightLepVetoJetID = 0;
  fatjet_partonPdgId = 0;
  fatjet_m = 0;
  fatjet_energy = 0;
  fatjet_puppi_tau1 = 0;
  fatjet_puppi_tau2 = 0;
  fatjet_puppi_tau3 = 0;
  fatjet_puppi_tau4 = 0;
  fatjet_softdropmass = 0;
  fatjet_chargedHadronEnergyFraction = 0;
  fatjet_neutralHadronEnergyFraction = 0;
  fatjet_neutralEmEnergyFraction = 0;
  fatjet_chargedEmEnergyFraction = 0;
  fatjet_chargedMultiplicity = 0;
  fatjet_neutralMultiplicity = 0;
  fatjet_shiftedEnUp = 0;
  fatjet_shiftedEnDown = 0;
  fatjet_smearedRes = 0;
  fatjet_smearedResUp = 0;
  fatjet_smearedResDown = 0;

  electron_MVAIso = 0;
  electron_MVANoIso = 0;
  electron_Energy = 0;
  electron_Energy_Scale_Up = 0;
  electron_Energy_Scale_Down = 0;
  electron_Energy_Smear_Up = 0;
  electron_Energy_Smear_Down = 0;
  electron_pt = 0;
  electron_pt_Scale_Up = 0;
  electron_pt_Scale_Down = 0;
  electron_pt_Smear_Up = 0;
  electron_pt_Smear_Down = 0;
  electron_eta = 0;
  electron_phi = 0;
  electron_charge = 0;
  electron_gsfpt = 0;
  electron_gsfEta = 0;
  electron_gsfPhi = 0;
  electron_gsfCharge = 0;
  electron_scEta = 0;
  electron_scPhi = 0;
  electron_etaWidth = 0;
  electron_phiWidth = 0;
  electron_dEtaIn = 0;
  electron_dEtaInSeed = 0;
  electron_dPhiIn = 0;
  electron_sigmaIEtaIEta = 0;
  electron_Full5x5_SigmaIEtaIEta = 0;
  electron_HoverE = 0;
  electron_fbrem = 0;
  electron_eOverP = 0;
  electron_InvEminusInvP = 0;
  electron_dxyVTX = 0;
  electron_dxyerrVTX = 0;
  electron_dzVTX = 0;
  electron_dzerrVTX = 0;
  electron_3DIPVTX = 0;
  electron_3DIPerrVTX = 0 ;
  electron_dxy = 0;
  electron_sigdxy = 0;
  electron_dz = 0;
  electron_dxyBS = 0;
  electron_dzBS = 0;
  electron_chIso03 = 0;
  electron_nhIso03 = 0;
  electron_phIso03 = 0;
  electron_puChIso03 = 0;
  electron_RelPFIso_dBeta = 0;
  electron_RelPFIso_Rho = 0;
  electron_passConversionVeto = 0;
  electron_isGsfCtfScPixChargeConsistent = 0;
  electron_isGsfScPixChargeConsistent = 0;
  electron_isGsfCtfChargeConsistent = 0;
  electron_mHits = 0;
  electron_ecalDriven = 0;
  electron_r9 = 0;
  electron_scEnergy = 0;
  electron_scPreEnergy = 0;
  electron_scRawEnergy = 0;
  electron_scEt = 0;
  electron_E15 = 0;
  electron_E25 = 0;
  electron_E55 = 0;
  electron_IDBit = 0;
  electron_EnergyUnCorr = 0;
  electron_chMiniIso = 0;
  electron_nhMiniIso = 0;
  electron_phMiniIso = 0;

  muon_PfChargedHadronIsoR04 = 0;
  muon_PfNeutralHadronIsoR04 = 0;
  muon_PfGammaIsoR04 = 0;
  muon_PFSumPUIsoR04 = 0;
  muon_PfChargedHadronIsoR03 = 0;
  muon_PfNeutralHadronIsoR03 = 0;
  muon_PfGammaIsoR03 = 0;
  muon_PFSumPUIsoR03 = 0;
  muon_TypeBit = 0;
  muon_IDBit = 0;

  muon_dB = 0;
  muon_phi = 0;
  muon_eta = 0;
  muon_pt = 0;
  muon_mass = 0;
  muon_trkiso = 0;
  muon_hcaliso = 0;
  muon_ecaliso = 0;
  muon_trkisoR05 = 0;
  muon_hcalisoR05 = 0;
  muon_ecalisoR05 = 0;
  muon_charge = 0;
  muon_nChambers = 0;
  muon_matchedstations = 0;
  muon_stationMask = 0;
  muon_nSegments = 0;
  muon_normchi = 0;
  muon_validhits = 0;
  muon_trackerHits = 0;
  muon_qoverp = 0;
  muon_theta = 0;
  muon_lambda = 0;
  muon_dxy = 0;
  muon_d0 = 0;
  muon_dsz = 0;
  muon_dz = 0;
  muon_dxyBS = 0;
  muon_dzBS = 0;
  muon_dszBS = 0;
  muon_dxyVTX = 0;
  muon_dzVTX = 0;
  muon_dszVTX = 0;
  muon_vx = 0;
  muon_vy = 0;
  muon_vz = 0;
  muon_Best_pt = 0;
  muon_Best_ptError = 0;
  muon_Best_eta = 0;
  muon_Best_phi = 0;
  muon_Inner_pt = 0;
  muon_Inner_ptError = 0;
  muon_Inner_eta = 0;
  muon_Inner_phi = 0;
  muon_Outer_pt = 0;
  muon_Outer_ptError = 0;
  muon_Outer_eta = 0;
  muon_Outer_phi = 0;
  muon_GLB_pt = 0;
  muon_GLB_ptError = 0;
  muon_GLB_eta = 0;
  muon_GLB_phi = 0;
  muon_TuneP_pt = 0;
  muon_TuneP_ptError = 0;
  muon_TuneP_eta = 0;
  muon_TuneP_phi = 0;
  muon_roch_sf = 0;
  muon_roch_sf_up = 0;

  muon_PfChargedHadronMiniIso = 0;
  muon_PfNeutralHadronMiniIso = 0;
  muon_PfGammaMiniIso = 0;
  muon_PFSumPUMiniIso = 0;


  PDFWeights_Scale = 0;
  PDFWeights_Error = 0;
  PDFWeights_AlphaS = 0;

  gen_phi = 0;
  gen_eta = 0;
  gen_pt = 0;
  gen_mass = 0;
  gen_mother_PID = 0;
  gen_mother_pt = 0;
  gen_mother_index = 0;
  gen_charge = 0;
  gen_status = 0;
  gen_PID = 0;
  gen_isPrompt = 0;
  gen_isPromptFinalState = 0;
  gen_isTauDecayProduct = 0;
  gen_isPromptTauDecayProduct = 0;
  gen_isDirectPromptTauDecayProductFinalState = 0;
  gen_isHardProcess = 0;
  gen_isLastCopy = 0;
  gen_isLastCopyBeforeFSR = 0;
  gen_isPromptDecayed = 0;
  gen_isDecayedLeptonHadron = 0;
  gen_fromHardProcessBeforeFSR = 0;
  gen_fromHardProcessDecayed = 0;
  gen_fromHardProcessFinalState = 0;
  gen_isMostlyLikePythia6Status3 = 0;
  photon_pt = 0;
  photon_eta = 0;
  photon_phi = 0;
  photon_scEta = 0;
  photon_scPhi = 0;
  photon_HoverE = 0;
  photon_hasPixelSeed = 0;
  photon_Full5x5_SigmaIEtaIEta = 0;
  photon_ChIso = 0;
  photon_NhIso = 0;
  photon_PhIso = 0;
  photon_ChIsoWithEA = 0;
  photon_NhIsoWithEA = 0;
  photon_PhIsoWithEA = 0;
  photon_passMVAID_WP80 = 0;
  photon_passMVAID_WP90 = 0;
  photon_passLooseID = 0;
  photon_passMediumID = 0;
  photon_passTightID = 0;
  photon_ptUnCorr = 0;

 
}

void Data::SetFlags(std::vector<TString> flags){
  k_flags= flags;
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
    k_inputfatjets=0;
    k_inputgenjets=0;
    k_inputevent=0;
    k_inputtrigger=0;
    k_inputtruth=0;
    b_inputmuons=0;
    b_inputelectrons=0;
    b_inputphotons=0;
    b_inputjets=0;
    b_inputfatjets=0;
    b_inputgenjets=0;
    b_inputevent=0;
    b_inputtrigger=0;
    b_inputtruth=0;

    ConnectVariable("KEvent", k_inputevent, b_inputevent);
    ConnectVariable("KJets", k_inputjets,b_inputjets );
    ConnectVariable("KFatJets", k_inputfatjets,b_inputfatjets );
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
    ConnectPFFatJets();
    ConnectTruth(setting_data);
    ConnectTrigger();    
    if(setall) ConnectAllBranches();
  }
  return;
}

void Data::SetVersion(int ver){
  k_cat_version=ver; 
}

void Data::ConnectEvent(int setting_data){
  

  ConnectVariable("run", run, b_runNum);
  
  ConnectVariable("IsData", IsData, b_IsData);  
  ConnectVariable("lumi",lumi , b_lumiBlock);
  ConnectVariable("event", event, b_evtNum);

  ConnectVariable("PUweight",PUweight,b_PUweight);
  ConnectVariable("Flag_HBHENoiseFilter", Flag_HBHENoiseFilter, b_Flag_HBHENoiseFilter);
  ConnectVariable("Flag_HBHENoiseIsoFilter",Flag_HBHENoiseIsoFilter, b_Flag_HBHENoiseIsoFilter);
  ConnectVariable("Flag_globalSuperTightHalo2016Filter",Flag_globalSuperTightHalo2016Filter,b_Flag_globalSuperTightHalo2016Filter);
  ConnectVariable("Flag_eeBadScFilter",Flag_eeBadScFilter , b_Flag_eeBadScFilter);
  ConnectVariable("Flag_ecalBadCalibFilter",Flag_ecalBadCalibFilter , b_Flag_ecalBadCalibFilter);
  ConnectVariable("Flag_goodVertices", Flag_goodVertices, b_Flag_goodVertices);
  ConnectVariable("Flag_BadChargedCandidateFilter",Flag_BadChargedCandidateFilter,b_Flag_BadChargedCandidateFilter);
  ConnectVariable("Flag_BadPFMuonFilter",Flag_BadPFMuonFilter,b_Flag_BadPFMuonFilter);
  ConnectVariable("Flag_EcalDeadCellTriggerPrimitiveFilter",Flag_EcalDeadCellTriggerPrimitiveFilter,b_Flag_EcalDeadCellTriggerPrimitiveFilter);

  ConnectVariable("nPV", nPV, b_nPV);
  ConnectVariable("Rho", Rho, b_Rho);
  
  ConnectVariable("PVtrackSize", PVtrackSize, b_PVtrackSize);
  ConnectVariable("PVchi2", PVchi2, b_PVchi2);
  ConnectVariable("PVnormalizedChi2", PVnormalizedChi2, b_PVnormalizedChi2);
  ConnectVariable("PVndof", PVndof, b_PVndof);

  ConnectVariable("vertex_X",vertex_X, b_PVx);
  ConnectVariable("vertex_Y",vertex_Y, b_PVy);
  ConnectVariable("vertex_Z",vertex_Z, b_PVz);
  ConnectVariable("pileUpReweightIn", pileUpReweightIn, b_pileUpReweightIn);
  ConnectVariable("pileUpReweight", pileUpReweight, b_pileUpReweight);
  ConnectVariable("pileUpReweightPlus", pileUpReweightPlus, b_pileUpReweightPlus);
  ConnectVariable("pileUpReweightMinus", pileUpReweightMinus, b_pileUpReweightMinus);
  ConnectVariable("pileUpReweightInMuonPhys", pileUpReweightInMuonPhys, b_pileUpReweightInMuonPhys);
  ConnectVariable("pileUpReweightMuonPhys", pileUpReweightMuonPhys, b_pileUpReweightMuonPhys);
  ConnectVariable("pileUpReweightPlusMuonPhys", pileUpReweightPlusMuonPhys, b_pileUpReweightPlusMuonPhys);
  ConnectVariable("pileUpReweightMinusMuonPhys", pileUpReweightMinusMuonPhys, b_pileUpReweightMinusMuonPhys);


  return;
}


void Data::ConnectTrigger(){
  
  //#####   Trigger branches
  ConnectVariable("HLT_TriggerName",HLT_TriggerName, b_HLT_TriggerName);
  
  return;
  
}


void Data::ConnectMuons(){
  
  //#####   Muon branches
  ConnectVariable("muon_PfChargedHadronIsoR04", muon_PfChargedHadronIsoR04, b_muon_PfChargedHadronIsoR04);
  ConnectVariable("muon_PfNeutralHadronIsoR04", muon_PfNeutralHadronIsoR04, b_muon_PfNeutralHadronIsoR04);
  ConnectVariable("muon_PfGammaIsoR04", muon_PfGammaIsoR04, b_muon_PfGammaIsoR04);
  ConnectVariable("muon_PFSumPUIsoR04", muon_PFSumPUIsoR04, b_muon_PFSumPUIsoR04);
  ConnectVariable("muon_PfChargedHadronIsoR03", muon_PfChargedHadronIsoR03, b_muon_PfChargedHadronIsoR03);
  ConnectVariable("muon_PfNeutralHadronIsoR03", muon_PfNeutralHadronIsoR03, b_muon_PfNeutralHadronIsoR03);
  ConnectVariable("muon_PfGammaIsoR03", muon_PfGammaIsoR03, b_muon_PfGammaIsoR03);
  ConnectVariable("muon_PFSumPUIsoR03", muon_PFSumPUIsoR03, b_muon_PFSumPUIsoR03);
  ConnectVariable("muon_TypeBit", muon_TypeBit, b_muon_TypeBit);
  ConnectVariable("muon_IDBit", muon_IDBit, b_muon_IDBit);

  ConnectVariable("muon_dB", muon_dB, b_muon_dB);
  ConnectVariable("muon_phi", muon_phi, b_muon_phi);
  ConnectVariable("muon_eta", muon_eta, b_muon_eta);
  ConnectVariable("muon_pt", muon_pt, b_muon_pt);
  ConnectVariable("muon_mass", muon_mass, b_muon_mass);
  ConnectVariable("muon_trkiso", muon_trkiso, b_muon_trkiso);
  ConnectVariable("muon_hcaliso", muon_hcaliso, b_muon_hcaliso);
  ConnectVariable("muon_ecaliso", muon_ecaliso, b_muon_ecaliso);
  ConnectVariable("muon_trkisoR05", muon_trkisoR05, b_muon_trkisoR05);
  ConnectVariable("muon_hcalisoR05", muon_hcalisoR05, b_muon_hcalisoR05);
  ConnectVariable("muon_ecalisoR05", muon_ecalisoR05, b_muon_ecalisoR05);
  ConnectVariable("muon_charge", muon_charge, b_muon_charge);
  ConnectVariable("muon_nChambers", muon_nChambers, b_muon_nChambers);
  ConnectVariable("muon_matchedstations", muon_matchedstations, b_muon_matchedstations);
  ConnectVariable("muon_stationMask", muon_stationMask, b_muon_stationMask);
  ConnectVariable("muon_nSegments", muon_nSegments, b_muon_nSegments);
  ConnectVariable("muon_normchi", muon_normchi, b_muon_normchi);
  ConnectVariable("muon_validhits", muon_validhits, b_muon_validhits);
  ConnectVariable("muon_trackerHits", muon_trackerHits, b_muon_trackerHits);
  ConnectVariable("muon_pixelHits", muon_pixelHits, b_muon_pixelHits);
  ConnectVariable("muon_validmuonhits", muon_validmuonhits, b_muon_validmuonhits);
  ConnectVariable("muon_trackerLayers", muon_trackerLayers, b_muon_trackerLayers);
  ConnectVariable("muon_qoverp", muon_qoverp, b_muon_qoverp);
  ConnectVariable("muon_theta", muon_theta, b_muon_theta);
  ConnectVariable("muon_lambda", muon_lambda, b_muon_lambda);
  ConnectVariable("muon_dxy", muon_dxy, b_muon_dxy);
  ConnectVariable("muon_d0", muon_d0, b_muon_d0);
  ConnectVariable("muon_dsz", muon_dsz, b_muon_dsz);
  ConnectVariable("muon_dz", muon_dz, b_muon_dz);
  ConnectVariable("muon_dxyBS", muon_dxyBS, b_muon_dxyBS);
  ConnectVariable("muon_dzBS", muon_dzBS, b_muon_dzBS);
  ConnectVariable("muon_dszBS", muon_dszBS, b_muon_dszBS);
  ConnectVariable("muon_dxyVTX", muon_dxyVTX, b_muon_dxyVTX);
  ConnectVariable("muon_dxyerrVTX", muon_dxyerrVTX, b_muon_dxyerrVTX);
  ConnectVariable("muon_dzVTX", muon_dzVTX, b_muon_dzVTX);
  ConnectVariable("muon_dzerrVTX", muon_dzerrVTX, b_muon_dzerrVTX);
  ConnectVariable("muon_3DIPVTX", muon_3DIPVTX, b_muon_3DIPVTX);
  ConnectVariable("muon_3DIPerrVTX", muon_3DIPerrVTX, b_muon_3DIPerrVTX);
  ConnectVariable("muon_dszVTX", muon_dszVTX, b_muon_dszVTX);

  ConnectVariable("muon_vx", muon_vx, b_muon_vx);
  ConnectVariable("muon_vy", muon_vy, b_muon_vy);
  ConnectVariable("muon_vz", muon_vz, b_muon_vz);
  ConnectVariable("muon_Best_pt", muon_Best_pt, b_muon_Best_pt);
  ConnectVariable("muon_Best_ptError", muon_Best_ptError, b_muon_Best_ptError);
  ConnectVariable("muon_Best_eta", muon_Best_eta, b_muon_Best_eta);
  ConnectVariable("muon_Best_phi", muon_Best_phi, b_muon_Best_phi);
  ConnectVariable("muon_Inner_pt", muon_Inner_pt, b_muon_Inner_pt);
  ConnectVariable("muon_Inner_ptError", muon_Inner_ptError, b_muon_Inner_ptError);
  ConnectVariable("muon_Inner_eta", muon_Inner_eta, b_muon_Inner_eta);
  ConnectVariable("muon_Inner_phi", muon_Inner_phi, b_muon_Inner_phi);
  ConnectVariable("muon_Outer_pt", muon_Outer_pt, b_muon_Outer_pt);
  ConnectVariable("muon_Outer_ptError", muon_Outer_ptError, b_muon_Outer_ptError);
  ConnectVariable("muon_Outer_eta", muon_Outer_eta, b_muon_Outer_eta);
  ConnectVariable("muon_Outer_phi", muon_Outer_phi, b_muon_Outer_phi);
  ConnectVariable("muon_GLB_pt", muon_GLB_pt, b_muon_GLB_pt);
  ConnectVariable("muon_GLB_ptError", muon_GLB_ptError, b_muon_GLB_ptError);
  ConnectVariable("muon_GLB_eta", muon_GLB_eta, b_muon_GLB_eta);
  ConnectVariable("muon_GLB_phi", muon_GLB_phi, b_muon_GLB_phi);
  ConnectVariable("muon_TuneP_pt", muon_TuneP_pt, b_muon_TuneP_pt);
  ConnectVariable("muon_TuneP_ptError", muon_TuneP_ptError, b_muon_TuneP_ptError);
  ConnectVariable("muon_TuneP_eta", muon_TuneP_eta, b_muon_TuneP_eta);
  ConnectVariable("muon_TuneP_phi", muon_TuneP_phi, b_muon_TuneP_phi);
  ConnectVariable("muon_roch_sf", muon_roch_sf, b_muon_roch_sf);
  ConnectVariable("muon_roch_sf_up", muon_roch_sf_up, b_muon_roch_sf_up);
  ConnectVariable("muon_PfChargedHadronMiniIso", muon_PfChargedHadronMiniIso, b_muon_PfChargedHadronMiniIso);
  ConnectVariable("muon_PfNeutralHadronMiniIso", muon_PfNeutralHadronMiniIso, b_muon_PfNeutralHadronMiniIso);
  ConnectVariable("muon_PfGammaMiniIso", muon_PfGammaMiniIso, b_muon_PfGammaMiniIso);
  ConnectVariable("muon_PFSumPUMiniIso", muon_PFSumPUMiniIso, b_muon_PFSumPUMiniIso);





  return;
}


void Data::ConnectPhotons(){
  
  ConnectVariable("photon_pt", photon_pt, b_photon_pt);
  ConnectVariable("photon_eta", photon_eta, b_photon_eta);
  ConnectVariable("photon_phi", photon_phi, b_photon_phi);
  ConnectVariable("photon_scEta", photon_scEta, b_photon_scEta);
  ConnectVariable("photon_scPhi", photon_scPhi, b_photon_scPhi);
  ConnectVariable("photon_HoverE", photon_HoverE, b_photon_HoverE);
  ConnectVariable("photon_hasPixelSeed", photon_hasPixelSeed, b_photon_hasPixelSeed);
  ConnectVariable("photon_Full5x5_SigmaIEtaIEta", photon_Full5x5_SigmaIEtaIEta, b_photon_Full5x5_SigmaIEtaIEta);
  ConnectVariable("photon_ChIso", photon_ChIso, b_photon_ChIso);
  ConnectVariable("photon_NhIso", photon_NhIso, b_photon_NhIso);
  ConnectVariable("photon_PhIso", photon_PhIso, b_photon_PhIso);
  ConnectVariable("photon_ChIsoWithEA", photon_ChIsoWithEA, b_photon_ChIsoWithEA);
  ConnectVariable("photon_NhIsoWithEA", photon_NhIsoWithEA, b_photon_NhIsoWithEA);
  ConnectVariable("photon_PhIsoWithEA", photon_PhIsoWithEA, b_photon_PhIsoWithEA);
  ConnectVariable("photon_passMVAID_WP80", photon_passMVAID_WP80, b_photon_passMVAID_WP80);
  ConnectVariable("photon_passMVAID_WP90", photon_passMVAID_WP90, b_photon_passMVAID_WP90);
  ConnectVariable("photon_passLooseID", photon_passLooseID, b_photon_passLooseID);
  ConnectVariable("photon_passMediumID", photon_passMediumID, b_photon_passMediumID);
  ConnectVariable("photon_passTightID", photon_passTightID, b_photon_passTightID);
  ConnectVariable("photon_ptUnCorr", photon_ptUnCorr, b_photon_ptUnCorr);

  
 }

void Data::ConnectElectrons(){

  //#####   Electron branches

  ConnectVariable("electron_MVAIso", electron_MVAIso, b_electron_MVAIso);
  ConnectVariable("electron_MVANoIso", electron_MVANoIso, b_electron_MVANoIso);
  ConnectVariable("electron_Energy", electron_Energy, b_electron_Energy);
  ConnectVariable("electron_Energy_Scale_Up", electron_Energy_Scale_Up, b_electron_Energy_Scale_Up);
  ConnectVariable("electron_Energy_Scale_Down", electron_Energy_Scale_Down, b_electron_Energy_Scale_Down);
  ConnectVariable("electron_Energy_Smear_Up", electron_Energy_Smear_Up, b_electron_Energy_Smear_Up);
  ConnectVariable("electron_Energy_Smear_Down", electron_Energy_Smear_Down, b_electron_Energy_Smear_Down);
  ConnectVariable("electron_pt", electron_pt, b_electron_pt);
  ConnectVariable("electron_pt_Scale_Up", electron_pt_Scale_Up, b_electron_pt_Scale_Up);
  ConnectVariable("electron_pt_Scale_Down", electron_pt_Scale_Down, b_electron_pt_Scale_Down);
  ConnectVariable("electron_pt_Smear_Up", electron_pt_Smear_Up, b_electron_pt_Smear_Up);
  ConnectVariable("electron_pt_Smear_Down", electron_pt_Smear_Down, b_electron_pt_Smear_Down);
  ConnectVariable("electron_eta", electron_eta, b_electron_eta);
  ConnectVariable("electron_phi", electron_phi, b_electron_phi);
  ConnectVariable("electron_charge", electron_charge, b_electron_charge);
  ConnectVariable("electron_gsfpt", electron_gsfpt, b_electron_gsfpt);
  ConnectVariable("electron_gsfEta", electron_gsfEta, b_electron_gsfEta);
  ConnectVariable("electron_gsfPhi", electron_gsfPhi, b_electron_gsfPhi);
  ConnectVariable("electron_gsfCharge", electron_gsfCharge, b_electron_gsfCharge);
  ConnectVariable("electron_scEta", electron_scEta, b_electron_scEta);
  ConnectVariable("electron_scPhi", electron_scPhi, b_electron_scPhi);
  ConnectVariable("electron_etaWidth", electron_etaWidth, b_electron_etaWidth);
  ConnectVariable("electron_phiWidth", electron_phiWidth, b_electron_phiWidth);
  ConnectVariable("electron_dEtaIn", electron_dEtaIn, b_electron_dEtaIn);
  ConnectVariable("electron_dEtaInSeed", electron_dEtaInSeed, b_electron_dEtaInSeed);
  ConnectVariable("electron_dPhiIn", electron_dPhiIn, b_electron_dPhiIn);
  ConnectVariable("electron_sigmaIEtaIEta", electron_sigmaIEtaIEta, b_electron_sigmaIEtaIEta);
  ConnectVariable("electron_Full5x5_SigmaIEtaIEta", electron_Full5x5_SigmaIEtaIEta, b_electron_Full5x5_SigmaIEtaIEta);
  ConnectVariable("electron_HoverE", electron_HoverE, b_electron_HoverE);
  ConnectVariable("electron_fbrem", electron_fbrem, b_electron_fbrem);
  ConnectVariable("electron_eOverP", electron_eOverP, b_electron_eOverP);
  ConnectVariable("electron_InvEminusInvP", electron_InvEminusInvP, b_electron_InvEminusInvP);
  ConnectVariable("electron_dxyVTX", electron_dxyVTX, b_electron_dxyVTX);
  ConnectVariable("electron_dxyerrVTX", electron_dxyerrVTX, b_electron_dxyerrVTX);
  ConnectVariable("electron_dzVTX", electron_dzVTX, b_electron_dzVTX);
  ConnectVariable("electron_dzerrVTX", electron_dzerrVTX, b_electron_dzerrVTX);
  ConnectVariable("electron_3DIPVTX", electron_3DIPVTX, b_electron_3DIPVTX);
  ConnectVariable("electron_3DIPerrVTX", electron_3DIPerrVTX, b_electron_3DIPerrVTX);
  ConnectVariable("electron_dxy", electron_dxy, b_electron_dxy);
  ConnectVariable("electron_sigdxy", electron_sigdxy, b_electron_sigdxy);
  ConnectVariable("electron_dz", electron_dz, b_electron_dz);
  ConnectVariable("electron_dxyBS", electron_dxyBS, b_electron_dxyBS);
  ConnectVariable("electron_dzBS", electron_dzBS, b_electron_dzBS);

  ConnectVariable("electron_chIso03", electron_chIso03, b_electron_chIso03);
  ConnectVariable("electron_nhIso03", electron_nhIso03, b_electron_nhIso03);
  ConnectVariable("electron_phIso03", electron_phIso03, b_electron_phIso03);
  ConnectVariable("electron_puChIso03", electron_puChIso03, b_electron_puChIso03);

  ConnectVariable("electron_passConversionVeto", electron_passConversionVeto, b_electron_passConversionVeto);
  ConnectVariable("electron_isGsfCtfScPixChargeConsistent", electron_isGsfCtfScPixChargeConsistent, b_electron_isGsfCtfScPixChargeConsistent);
  ConnectVariable("electron_isGsfScPixChargeConsistent", electron_isGsfScPixChargeConsistent, b_electron_isGsfScPixChargeConsistent);
  ConnectVariable("electron_isGsfCtfChargeConsistent", electron_isGsfCtfChargeConsistent, b_electron_isGsfCtfChargeConsistent);
  ConnectVariable("electron_mHits", electron_mHits, b_electron_mHits);
  ConnectVariable("electron_ecalDriven", electron_ecalDriven, b_electron_ecalDriven);
  ConnectVariable("electron_r9", electron_r9, b_electron_r9);
  ConnectVariable("electron_scEnergy", electron_scEnergy, b_electron_scEnergy);
  ConnectVariable("electron_scPreEnergy", electron_scPreEnergy, b_electron_scPreEnergy);
  ConnectVariable("electron_scRawEnergy", electron_scRawEnergy, b_electron_scRawEnergy);
  ConnectVariable("electron_scEt", electron_scEt, b_electron_scEt);
  ConnectVariable("electron_E15", electron_E15, b_electron_E15);
  ConnectVariable("electron_E25", electron_E25, b_electron_E25);
  ConnectVariable("electron_E55", electron_E55, b_electron_E55);
  ConnectVariable("electron_RelPFIso_dBeta", electron_RelPFIso_dBeta, b_electron_RelPFIso_dBeta);
  ConnectVariable("electron_RelPFIso_Rho", electron_RelPFIso_Rho, b_electron_RelPFIso_Rho);
  ConnectVariable("electron_IDBit", electron_IDBit, b_electron_IDBit);

  ConnectVariable("electron_EnergyUnCorr", electron_EnergyUnCorr, b_electron_EnergyUnCorr);
  ConnectVariable("electron_chMiniIso", electron_chMiniIso, b_electron_chMiniIso);
  ConnectVariable("electron_nhMiniIso", electron_nhMiniIso, b_electron_nhMiniIso);
  ConnectVariable("electron_phMiniIso", electron_phMiniIso, b_electron_phMiniIso);
  ConnectVariable("electron_puChMiniIso", electron_puChMiniIso, b_electron_puChMiniIso);


  return;
}

void Data::ConnectPFJets(){

  m_logger << DEBUG << "ConnectPFJets : "<< LQLogger::endmsg;

  //#####   Jet branches
  //  ConnectVariable("rhoJets", rhoJets, b_rhoJets);
  /// TLV variables

  ConnectVariable("jet_pt", jet_pt, b_jet_pt);
  ConnectVariable("jet_eta", jet_eta, b_jet_eta);
  ConnectVariable("jet_phi", jet_phi, b_jet_phi);
  ConnectVariable("jet_charge", jet_charge, b_jet_charge);
  ConnectVariable("jet_area", jet_area, b_jet_area);
  ConnectVariable("jet_partonFlavour", jet_partonFlavour, b_jet_partonFlavour);
  ConnectVariable("jet_hadronFlavour", jet_hadronFlavour, b_jet_hadronFlavour);
  ConnectVariable("jet_CSVv2", jet_CSVv2, b_jet_CSVv2);
  ConnectVariable("jet_DeepCSV", jet_DeepCSV, b_jet_DeepCSV);
  ConnectVariable("jet_CvsL", jet_CvsL, b_jet_CvsL);
  ConnectVariable("jet_CvsB", jet_CvsB, b_jet_CvsB);
  ConnectVariable("jet_DeepCvsL", jet_DeepCvsL, b_jet_DeepCvsL);
  ConnectVariable("jet_DeepCvsB", jet_DeepCvsB, b_jet_DeepCvsB);
  ConnectVariable("jet_DeepFlavour_b", jet_DeepFlavour_b, b_jet_DeepFlavour_b);
  ConnectVariable("jet_DeepFlavour_bb", jet_DeepFlavour_bb, b_jet_DeepFlavour_bb);
  ConnectVariable("jet_DeepFlavour_lepb", jet_DeepFlavour_lepb, b_jet_DeepFlavour_lepb);
  ConnectVariable("jet_DeepFlavour_c", jet_DeepFlavour_c, b_jet_DeepFlavour_c);
  ConnectVariable("jet_DeepFlavour_uds", jet_DeepFlavour_uds, b_jet_DeepFlavour_uds);
  ConnectVariable("jet_DeepFlavour_g", jet_DeepFlavour_g, b_jet_DeepFlavour_g);
  ConnectVariable("jet_chargedHadronEnergyFraction", jet_chargedHadronEnergyFraction, b_jet_chargedHadronEnergyFraction);
  ConnectVariable("jet_neutralHadronEnergyFraction", jet_neutralHadronEnergyFraction, b_jet_neutralHadronEnergyFraction);
  ConnectVariable("jet_neutralEmEnergyFraction", jet_neutralEmEnergyFraction, b_jet_neutralEmEnergyFraction);
  ConnectVariable("jet_chargedEmEnergyFraction", jet_chargedEmEnergyFraction, b_jet_chargedEmEnergyFraction);
  ConnectVariable("jet_chargedMultiplicity", jet_chargedMultiplicity, b_jet_chargedMultiplicity);
  ConnectVariable("jet_neutralMultiplicity", jet_neutralMultiplicity, b_jet_neutralMultiplicity);
  ConnectVariable("jet_tightJetID", jet_tightJetID, b_jet_tightJetID);
  ConnectVariable("jet_tightLepVetoJetID", jet_tightLepVetoJetID, b_jet_tightLepVetoJetID);
  ConnectVariable("jet_partonPdgId", jet_partonPdgId, b_jet_partonPdgId);
  ConnectVariable("jet_m", jet_m, b_jet_m);
  ConnectVariable("jet_energy", jet_energy, b_jet_energy);
  ConnectVariable("jet_PileupJetId", jet_PileupJetId, b_jet_PileupJetId);
  ConnectVariable("jet_shiftedEnUp", jet_shiftedEnUp, b_jet_shiftedEnUp);
  ConnectVariable("jet_shiftedEnDown", jet_shiftedEnDown, b_jet_shiftedEnDown);
  ConnectVariable("jet_smearedRes", jet_smearedRes, b_jet_smearedRes);
  ConnectVariable("jet_smearedResUp", jet_smearedResUp, b_jet_smearedResUp);
  ConnectVariable("jet_smearedResDown", jet_smearedResDown, b_jet_smearedResDown);
  ConnectVariable("jet_JECL1FastJet", jet_JECL1FastJet, b_jet_JECL1FastJet);
  ConnectVariable("jet_JECFull", jet_JECFull, b_jet_JECFull);


  return;}



void Data::ConnectPFFatJets(){

  m_logger << DEBUG << "ConnectPFJets : "<< LQLogger::endmsg;

  //#####   Jet branches                                                                                                                                                         
  //  ConnectVariable("rhoJets", rhoJets, b_rhoJets);                                                                                                                            
  /// TLV variables                                                                                                                                                              

  ConnectVariable("fatjet_pt", fatjet_pt, b_fatjet_pt);
  ConnectVariable("fatjet_eta", fatjet_eta, b_fatjet_eta);
  ConnectVariable("fatjet_phi", fatjet_phi, b_fatjet_phi);
  ConnectVariable("fatjet_charge", fatjet_charge, b_fatjet_charge);
  ConnectVariable("fatjet_area", fatjet_area, b_fatjet_area);
  ConnectVariable("fatjet_partonFlavour", fatjet_partonFlavour, b_fatjet_partonFlavour);
  ConnectVariable("fatjet_hadronFlavour", fatjet_hadronFlavour, b_fatjet_hadronFlavour);
  ConnectVariable("fatjet_CSVv2", fatjet_CSVv2, b_fatjet_CSVv2);

  ConnectVariable("fatjet_tightJetID", fatjet_tightJetID, b_fatjet_tightJetID);
  ConnectVariable("fatjet_tightLepVetoJetID", fatjet_tightLepVetoJetID, b_fatjet_tightLepVetoJetID);
  ConnectVariable("fatjet_partonPdgId", fatjet_partonPdgId, b_fatjet_partonPdgId);
  ConnectVariable("fatjet_m", fatjet_m, b_fatjet_m);
  ConnectVariable("fatjet_energy", fatjet_energy, b_fatjet_energy);
  ConnectVariable("fatjet_puppi_tau1", fatjet_puppi_tau1, b_fatjet_puppi_tau1);
  ConnectVariable("fatjet_puppi_tau2", fatjet_puppi_tau2, b_fatjet_puppi_tau2);
  ConnectVariable("fatjet_puppi_tau3", fatjet_puppi_tau3, b_fatjet_puppi_tau3);
  ConnectVariable("fatjet_puppi_tau4", fatjet_puppi_tau4, b_fatjet_puppi_tau4);
  ConnectVariable("fatjet_softdropmass", fatjet_softdropmass, b_fatjet_softdropmass);
  ConnectVariable("fatjet_chargedHadronEnergyFraction", fatjet_chargedHadronEnergyFraction, b_fatjet_chargedHadronEnergyFraction);
  ConnectVariable("fatjet_neutralHadronEnergyFraction", fatjet_neutralHadronEnergyFraction, b_fatjet_neutralHadronEnergyFraction);
  ConnectVariable("fatjet_neutralEmEnergyFraction", fatjet_neutralEmEnergyFraction, b_fatjet_neutralEmEnergyFraction);
  ConnectVariable("fatjet_chargedEmEnergyFraction", fatjet_chargedEmEnergyFraction, b_fatjet_chargedEmEnergyFraction);
  ConnectVariable("fatjet_chargedMultiplicity", fatjet_chargedMultiplicity, b_fatjet_chargedMultiplicity);
  ConnectVariable("fatjet_neutralMultiplicity", fatjet_neutralMultiplicity, b_fatjet_neutralMultiplicity);
  ConnectVariable("fatjet_shiftedEnUp", fatjet_shiftedEnUp, b_fatjet_shiftedEnUp);
  ConnectVariable("fatjet_shiftedEnDown", fatjet_shiftedEnDown, b_fatjet_shiftedEnDown);
  ConnectVariable("fatjet_smearedRes", fatjet_smearedRes, b_fatjet_smearedRes);
  ConnectVariable("fatjet_smearedResUp",fatjet_smearedResUp, b_fatjet_smearedResUp);
  ConnectVariable("fatjet_smearedResDown", fatjet_smearedResDown, b_fatjet_smearedResDown);

  return;
}


void Data::ConnectMET(){

  //#####   MET branches
  ConnectVariable("pfMET_pt", pfMET_pt, b_pfMET_pt);
  ConnectVariable("pfMET_phi", pfMET_phi, b_pfMET_phi);
  ConnectVariable("pfMET_SumEt", pfMET_SumEt, b_pfMET_SumEt);
  ConnectVariable("pfMET_Type1_pt", pfMET_Type1_pt, b_pfMET_Type1_pt);
  ConnectVariable("pfMET_Type1_phi", pfMET_Type1_phi, b_pfMET_Type1_phi);
  ConnectVariable("pfMET_Type1_SumEt", pfMET_Type1_SumEt, b_pfMET_Type1_SumEt);
  ConnectVariable("pfMET_Type1_PhiCor_pt", pfMET_Type1_PhiCor_pt, b_pfMET_Type1_PhiCor_pt);
  ConnectVariable("pfMET_Type1_PhiCor_phi", pfMET_Type1_PhiCor_phi, b_pfMET_Type1_PhiCor_phi);
  ConnectVariable("pfMET_Type1_PhiCor_SumEt", pfMET_Type1_PhiCor_SumEt, b_pfMET_Type1_PhiCor_SumEt);

  // shifts
  ConnectVariable("pfMET_pt_shifts", pfMET_pt_shifts, b_pfMET_pt_shifts);
  ConnectVariable("pfMET_phi_shifts", pfMET_phi_shifts, b_pfMET_phi_shifts);
  ConnectVariable("pfMET_SumEt_shifts", pfMET_SumEt_shifts, b_pfMET_SumEt_shifts);
  ConnectVariable("pfMET_Type1_pt_shifts", pfMET_Type1_pt_shifts, b_pfMET_Type1_pt_shifts);
  ConnectVariable("pfMET_Type1_phi_shifts", pfMET_Type1_phi_shifts, b_pfMET_Type1_phi_shifts);
  ConnectVariable("pfMET_Type1_SumEt_shifts", pfMET_Type1_SumEt_shifts, b_pfMET_Type1_SumEt_shifts);
  ConnectVariable("pfMET_Type1_PhiCor_pt_shifts", pfMET_Type1_PhiCor_pt_shifts, b_pfMET_Type1_PhiCor_pt_shifts);
  ConnectVariable("pfMET_Type1_PhiCor_phi_shifts", pfMET_Type1_PhiCor_phi_shifts, b_pfMET_Type1_PhiCor_phi_shifts);
  ConnectVariable("pfMET_Type1_PhiCor_SumEt_shifts", pfMET_Type1_PhiCor_SumEt_shifts, b_pfMET_Type1_PhiCor_SumEt_shifts);



  return;
}

void Data::ConnectTruth(int setting_data){

  //#####   Truth branches

  //  ConnectVariable("GenSumETTrue", GenSumETTrue, b_GenSumETTrue);
  if(setting_data == 1) return;


  ConnectVariable("PDFWeights_AlphaS" ,PDFWeights_AlphaS ,b_PDFWeights_AlphaS);
  ConnectVariable("PDFWeights_Error"  ,PDFWeights_Error  ,b_PDFWeights_Error);
  ConnectVariable("PDFWeights_Scale"  ,PDFWeights_Scale  ,b_PDFWeights_Scale);


  ConnectVariable("gen_phi", gen_phi, b_gen_phi);
  ConnectVariable("gen_eta", gen_eta, b_gen_eta);
  ConnectVariable("gen_pt", gen_pt, b_gen_pt);
  ConnectVariable("gen_mass", gen_mass, b_gen_mass);
  ConnectVariable("gen_mother_index", gen_mother_index, b_gen_mother_index);
  ConnectVariable("gen_charge", gen_charge, b_gen_charge);
  ConnectVariable("gen_status", gen_status, b_gen_status);
  ConnectVariable("gen_PID", gen_PID, b_gen_PID);
  ConnectVariable("gen_isPrompt", gen_isPrompt, b_gen_isPrompt);
  ConnectVariable("gen_isPromptFinalState", gen_isPromptFinalState, b_gen_isPromptFinalState);
  ConnectVariable("gen_isTauDecayProduct", gen_isTauDecayProduct, b_gen_isTauDecayProduct);
  ConnectVariable("gen_isPromptTauDecayProduct", gen_isPromptTauDecayProduct, b_gen_isPromptTauDecayProduct);
  ConnectVariable("gen_isDirectPromptTauDecayProductFinalState", gen_isDirectPromptTauDecayProductFinalState, b_gen_isDirectPromptTauDecayProductFinalState);
  ConnectVariable("gen_isHardProcess", gen_isHardProcess, b_gen_isHardProcess);
  ConnectVariable("gen_isLastCopy", gen_isLastCopy, b_gen_isLastCopy);
  ConnectVariable("gen_isLastCopyBeforeFSR", gen_isLastCopyBeforeFSR, b_gen_isLastCopyBeforeFSR);
  ConnectVariable("gen_isPromptDecayed", gen_isPromptDecayed, b_gen_isPromptDecayed);
  ConnectVariable("gen_isDecayedLeptonHadron", gen_isDecayedLeptonHadron, b_gen_isDecayedLeptonHadron);
  ConnectVariable("gen_fromHardProcessBeforeFSR", gen_fromHardProcessBeforeFSR, b_gen_fromHardProcessBeforeFSR);
  ConnectVariable("gen_fromHardProcessDecayed", gen_fromHardProcessDecayed, b_gen_fromHardProcessDecayed);
  ConnectVariable("gen_fromHardProcessFinalState", gen_fromHardProcessFinalState, b_gen_fromHardProcessFinalState);
  ConnectVariable("gen_isMostlyLikePythia6Status3", gen_isMostlyLikePythia6Status3, b_gen_isMostlyLikePythia6Status3);
  ConnectVariable("gen_weight", gen_weight, b_gen_weight);
  ConnectVariable("genWeight_Q", genWeight_Q, b_genWeight_Q);
  ConnectVariable("genWeight_X1", genWeight_X1, b_genWeight_X1);
  ConnectVariable("genWeight_X2", genWeight_X2, b_genWeight_X2);
  ConnectVariable("genWeight_id1", genWeight_id1, b_genWeight_id1);
  ConnectVariable("genWeight_id2", genWeight_id2, b_genWeight_id2);
  ConnectVariable("genWeight_alphaQCD", genWeight_alphaQCD, b_genWeight_alphaQCD);
  ConnectVariable("genWeight_alphaQED", genWeight_alphaQED, b_genWeight_alphaQED);

  
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
  
  m_logger << INFO << "ConnectVariable 1: " << branchName <<  LQLogger::endmsg;

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
