// $Id: Data.cxx
/***************************************************************************
 * @Project: LQAnalyzer
 * @Package: Core
 */

#ifndef DATA_cc
#define DATA_cc

#include "KMuon.h"
#include "KElectron.h"
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

Data::Data() : LQCycleBaseNTuple(), LQinput(true), k_inputmuons(0),  k_inputelectrons(0),  k_inputjets(0), k_inputgenjets(0)
  
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
  ConnectVariables(false); // -> false means not ALL branches are loaded

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

  gen_pt = 0;
  gen_eta = 0;
  gen_phi = 0;
  gen_energy = 0;
  gen_status = 0;
  gen_pdgid = 0;
  gen_motherindex = 0;
  pdfWeight = 0;
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
  jets_CVSInclV2 = 0;
  jets_energy = 0;
  jets_eta = 0;
  jets_isPFId = 0;
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
  jetsPuppi_CVSInclV2 = 0;
  jetsPuppi_eta = 0;
  jetsPuppi_hadronFlavour = 0;
  jetsPuppi_m = 0;
  jetsPuppi_partonFlavour = 0;
  jetsPuppi_phi = 0;
  jetsPuppi_pt = 0;
  jetsPuppi_vtx3DSig = 0;
  jetsPuppi_vtx3DVal = 0;
  jetsPuppi_vtxMass = 0;
  met_phi = 0;
  met_pt = 0;
  met_sumet = 0;
  metNoHF_phi = 0;
  metNoHF_pt = 0;
  metNoHF_sumet = 0;
  metPfMva_phi = 0;
  metPfMva_pt = 0;
  metPfMva_sumet = 0;
  metPuppi_phi = 0;
  metPuppi_pt = 0;
  metPuppi_sumet = 0;
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
  slimmedGenJets_energy = 0;
  slimmedGenJets_eta = 0;
  slimmedGenJets_m = 0;
  slimmedGenJets_phi = 0;
  slimmedGenJets_pt = 0;
  vertices_ndof = 0;
  vertices_x = 0;
  vertices_y = 0;
  vertices_z = 0;
  electrons_electronID_loose = 0;
  electrons_electronID_medium = 0;
  electrons_electronID_tight = 0;
  electrons_electronID_veto = 0;
  electrons_isPF = 0;
  electrons_mcMatched = 0;
  electrons_passConversionVeto = 0;
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
 
}

void Data::SetLQNtupleInputType(bool lq){
  LQinput= lq;
}



void Data::ConnectVariables(bool setall){

  /// set all controlls which cranches are set 
  //#####   EVENT branches

  if(!LQinput){
    k_inputmuons=0;
    k_inputelectrons=0;
    k_inputjets=0;
    k_inputgenjets=0;
    k_inputevent=0;
    k_inputtrigger=0;
    k_inputtruth=0;
    b_inputmuons=0;
    b_inputelectrons=0;
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
    ConnectVariable("KTrigger", k_inputtrigger, b_inputtrigger);
    ConnectVariable("KTruth" , k_inputtruth, b_inputtruth);
    
  }  
  else{
    ConnectEvent();
    ConnectMuons();
    ConnectMET();
    ConnectElectrons();
    ConnectPFJets();
    ConnectTruth();
    ConnectTrigger();
    
    if(setall) ConnectAllBranches();
  }
  return;
}
void Data::ConnectEvent(){

  ConnectVariable("run", run, b_run);
  ConnectVariable("lumi",lumi , b_lumi);
  ConnectVariable("event", event, b_event);

  ConnectVariable("nTrueInteraction", nTrueInteraction , b_nTrueInteraction);
 
  ConnectVariable("HNHENoiseFilter", HNHENoiseFilter, b_HNHENoiseFilter);
  ConnectVariable("csctighthaloFilter", csctighthaloFilter, b_csctighthaloFilter);
  ConnectVariable("ecalDCTRFilter", ecalDCTRFilter, b_ecalDCTRFilter);
  ConnectVariable("eeBadScFilter",eeBadScFilter , b_eeBadScFilter);
  ConnectVariable("goodVertices", goodVertices, b_goodVertices);
  
  ConnectVariable("nGoodPV", nGoodPV, b_nGoodPV);
  ConnectVariable("nPV", nPV, b_nPV);
  
  ConnectVariable("puWeight",puWeight, b_puWeight);
  ConnectVariable("puWeightUp",puWeightUp, b_puWeightUp);
  ConnectVariable("puWeightDn",puWeightDn, b_puWeightDn);

  ConnectVariable("vertices_ndof",vertices_ndof, b_vertices_ndof);
  ConnectVariable("vertices_x",vertices_x, b_vertices_x);
  ConnectVariable("vertices_y",vertices_y, b_vertices_y);
  ConnectVariable("vertices_z",vertices_z, b_vertices_z);
 
  return;}


void Data::ConnectTrigger(){
  
  //#####   Trigger branches
  //  ConnectVariable("HLTInsideDatasetTriggerNames", HLTInsideDatasetTriggerNames, b_HLTInsideDatasetTriggerNames);
  ConnectVariable("hlt_2el33", hlt_2el33, b_hlt_2el33);
  ConnectVariable("hlt_el12", hlt_el12, b_hlt_el12);
  ConnectVariable("hlt_el16_el12_8" ,hlt_el16_el12_8, b_hlt_el16_el12_8);
  ConnectVariable("hlt_el17", hlt_el17, b_hlt_el17);
  ConnectVariable("hlt_el17_el12", hlt_el17_el12, b_hlt_el17_el12);
  ConnectVariable("hlt_el23_el12", hlt_el23_el12, b_hlt_el23_el12);
  ConnectVariable("hlt_el23_el12dz", hlt_el23_el12dz, b_hlt_el23_el12dz);
  ConnectVariable("hlt_ele27eta2p1", hlt_ele27eta2p1, b_hlt_ele27eta2p1);
  ConnectVariable("hlt_mu17_el12", hlt_mu17_el12, b_hlt_mu17_el12);
  ConnectVariable("hlt_mu17_mu8", hlt_mu17_mu8, b_hlt_mu17_mu8);
  ConnectVariable("hlt_mu17_tkmu8", hlt_mu17_tkmu8, b_hlt_mu17_tkmu8);
  ConnectVariable("hlt_mu8_el17", hlt_mu8_el17, b_hlt_mu8_el17);

  ConnectVariable("vtrignames",vtrignames, b_vtrignames);
  ConnectVariable("vtrigps",vtrigps,b_vtrigps);
  
  
  return;
  
}


void Data::ConnectMuons(){
  
  //#####   Muon branches
  //ConnectVariable("MuonshiftedEdown",MuonshiftedEdown,b_MuonshiftedEdown);

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
  ConnectVariable("electrons_energy", electrons_energy, b_electrons_energy);
  ConnectVariable("electrons_eta", electrons_eta, b_electrons_eta);
  ConnectVariable("electrons_isPF", electrons_isPF, b_electrons_isPF);
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

  m_logger << INFO << "ConnectPFJets : "<< LQLogger::endmsg;

  //#####   Jet branches
  //  ConnectVariable("rhoJets", rhoJets, b_rhoJets);
  /// TLV variables
  ConnectVariable("jets_CVSInclV2", jets_CVSInclV2, b_jets_CVSInclV2);
  ConnectVariable("jets_energy", jets_energy, b_jets_energy);
  m_logger << INFO << "jets_eta ="<<jets_eta<< LQLogger::endmsg;

  ConnectVariable("jets_eta",jets_eta,b_jets_eta);
  m_logger << INFO << "jets_eta ="<<jets_eta<< LQLogger::endmsg;
  
  ConnectVariable("jets_hadronFlavour",jets_hadronFlavour,b_jets_hadronFlavour);
  ConnectVariable("jets_isLoose",jets_isLoose,b_jets_isLoose);
  ConnectVariable("jets_isPFId",jets_isPFId, b_jets_isPFId);

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
  ConnectVariable("metPuppi_pt",metPuppi_pt , b_metPuppi_pt);
  ConnectVariable("metPuppi_phi",metPuppi_phi , b_metPuppi_phi);
  ConnectVariable("metPuppi_sumet", metPuppi_sumet , b_metPuppi_sumet);
  ConnectVariable("metNoHF_phi",metNoHF_phi , b_metNoHF_phi);
  ConnectVariable("metNoHF_pt", metNoHF_pt , b_metNoHF_pt);
  ConnectVariable("metNoHF_sumet", metNoHF_sumet , b_metNoHF_sumet);
  ConnectVariable("metPfMva_phi",metPfMva_phi , b_metPfMva_phi);
  ConnectVariable("metPfMva_pt", metPfMva_pt , b_metPfMva_pt);
  ConnectVariable("metPfMva_sumet", metPfMva_sumet , b_metPfMva_sumet);

  

  return;
}

void Data::ConnectTruth(){

  //#####   Truth branches

  //  ConnectVariable("GenSumETTrue", GenSumETTrue, b_GenSumETTrue);
  ConnectVariable("slimmedGenJets_eta", slimmedGenJets_eta,b_slimmedGenJets_eta);
  ConnectVariable("slimmedGenJets_pt", slimmedGenJets_pt,b_slimmedGenJets_pt);
  ConnectVariable("slimmedGenJets_phi", slimmedGenJets_phi,b_slimmedGenJets_phi);
  ConnectVariable("slimmedGenJets_energy", slimmedGenJets_energy,b_slimmedGenJets_energy);

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

  ConnectVariable("pdfWeight", pdfWeight, b_pdfWeight);
  
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
