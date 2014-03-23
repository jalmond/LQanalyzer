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
  HLTKey = 0;
  HLTInsideDatasetTriggerNames = 0;
  HLTOutsideDatasetTriggerNames = 0;
  passHcalLaserEventFilter=0;
  ElectronGsfCtfCharge = 0;
  ElectronGsfCtfScPixCharge = 0;
  ElectronGsfScPixCharge = 0;
  ElectronHLTDoubleEleMatched = 0;
  ElectronHLTSingleEleMatched = 0;
  ElectronHLTSingleEleWP80Matched = 0;
  ElectronHasEcalDrivenSeed = 0;
  ElectronHasMatchedConvPhot = 0;
  ElectronHasTrackerDrivenSeed = 0;
  ElectronIsEB = 0;
  ElectronIsEE = 0;
  MuonHLTSingleIsoMuonMatched = 0;
  MuonHLTSingleMuonMatched = 0;
  MuonHLTDoubleMuonMatched = 0;
   PhotonHasMatchedConvPhot = 0;
   PhotonHasMatchedPromptEle = 0;
   PhotonHasPixelSeed = 0;
   PhotonIsEBEEGap = 0;
   PhotonIsEBGap = 0;
   PhotonIsEEGap = 0;
   HLTInsideDatasetTriggerDecisions = 0;
   HLTOutsideDatasetTriggerDecisions = 0;
   VertexIsFake = 0;
   CaloMET = 0;
   CaloMETPhi = 0;
   CaloSumET = 0;
   CaloMETPhiType1Cor = 0;
   CaloMETPhiUncorrType1Cor = 0;
   CaloMETType1Cor = 0;
   CaloMETUncorrType1Cor = 0;
   CaloSumETType1Cor = 0;
   CaloSumETUncorrType1Cor = 0;
   ElectronBeamSpotDXY = 0;
   ElectronBeamSpotDXYError = 0;
   ElectronCaloEnergy = 0;
   ElectronConvFitProb = 0;
   ElectronDCotTheta = 0;
   ElectronDeltaEtaTrkSC = 0;
   ElectronDeltaPhiTrkSC = 0;
   ElectronDist = 0;
   ElectronE1x5OverE5x5 = 0;
   ElectronE2x5OverE5x5 = 0;
   ElectronESuperClusterOverP = 0;
   ElectronEcalIsoDR03 = 0;
   ElectronEcalIsoPAT = 0;
   ElectronEnergy = 0;
   ElectronEta = 0;
   ElectronFbrem = 0;
   ElectronHLTDoubleEleMatchEta = 0;
   ElectronHLTDoubleEleMatchPhi = 0;
   ElectronHLTDoubleEleMatchPt = 0;
   ElectronHLTSingleEleMatchEta = 0;
   ElectronHLTSingleEleMatchPhi = 0;
   ElectronHLTSingleEleMatchPt = 0;
   ElectronHLTSingleEleWP80MatchEta = 0;
   ElectronHLTSingleEleWP80MatchPhi = 0;
   ElectronHLTSingleEleWP80MatchPt = 0;
   ElectronHcalIsoD1DR03 = 0;
   ElectronHcalIsoD2DR03 = 0;
   ElectronHcalIsoDR03 = 0;
   ElectronHcalIsoDR03FullCone = 0;
   ElectronHcalIsoPAT = 0;
   ElectronHoE = 0;
   ElectronLeadVtxDistXY = 0;
   ElectronLeadVtxDistZ = 0;
   ElectronMatchedGenParticleEta = 0;
   ElectronMatchedGenParticlePhi = 0;
   ElectronMatchedGenParticlePt = 0;
   ElectronPFChargedHadronIso03 = 0;
   ElectronPFChargedHadronIso04 = 0;
   ElectronPFNeutralHadronIso03 = 0;
   ElectronPFNeutralHadronIso04 = 0;
   ElectronPFPhotonIso03 = 0;
   ElectronPFPhotonIso04 = 0;
   ElectronPhi = 0;
   ElectronPrimaryVertexDXY = 0;
   ElectronPrimaryVertexDXYError = 0;
   ElectronPt = 0;
   ElectronPtHeep = 0;
   ElectronRelIsoPAT = 0;
   ElectronSCEta = 0;
   ElectronSCPhi = 0;
   ElectronSCPt = 0;
   ElectronSCRawEnergy = 0;
   ElectronSigmaEtaEta = 0;
   ElectronSigmaIEtaIEta = 0;
   ElectronTrackPt = 0;
   ElectronTrackValidFractionOfHits = 0;
   ElectronTrackVx = 0;
   ElectronTrackVy = 0;
   ElectronTrackVz = 0;
   ElectronTrkIsoDR03 = 0;
   ElectronTrkIsoPAT = 0;
   ElectronVtxDistXY = 0;
   ElectronVtxDistZ = 0;
   GenWElectronEnergy = 0;
   GenWElectronEta = 0;
   GenWElectronP = 0;
   GenWElectronPhi = 0;
   GenWElectronPt = 0;
   GenWElectronPx = 0;
   GenWElectronPy = 0;
   GenWElectronPz = 0;
   GenWElectronTauVisibleEta = 0;
   GenWElectronTauVisiblePhi = 0;
   GenWElectronTauVisiblePt = 0;
   GenWElectronVX = 0;
   GenWElectronVY = 0;
   GenWElectronVZ = 0;
   GenZElectronEnergy = 0;
   GenZElectronEta = 0;
   GenZElectronP = 0;
   GenZElectronPhi = 0;
   GenZElectronPt = 0;
   GenZElectronPx = 0;
   GenZElectronPy = 0;
   GenZElectronPz = 0;
   GenZElectronTauVisibleEta = 0;
   GenZElectronTauVisiblePhi = 0;
   GenZElectronTauVisiblePt = 0;
   GenZElectronVX = 0;
   GenZElectronVY = 0;
   GenZElectronVZ = 0;
   PDFCTEQWeights = 0;
   PDFMSTWWeights = 0;
   PDFNNPDFWeights = 0;
   GenJetEMF = 0;
   GenJetEnergy = 0;
   GenJetEta = 0;
   GenJetHADF = 0;
   GenJetP = 0;
   GenJetPhi = 0;
   GenJetPt = 0;
   GenMETCalo = 0;
   GenMETPhiCalo = 0;
   GenSumETCalo = 0;
   GenMETPhiTrue = 0;
   GenMETTrue = 0;
   GenSumETTrue = 0;
   GenWMuEnergy = 0;
   GenWMuEta = 0;
   GenWMuP = 0;
   GenWMuPhi = 0;
   GenWMuPt = 0;
   GenWMuPx = 0;
   GenWMuPy = 0;
   GenWMuPz = 0;
   GenWMuTauVisibleEta = 0;
   GenWMuTauVisiblePhi = 0;
   GenWMuTauVisiblePt = 0;
   GenWMuVX = 0;
   GenWMuVY = 0;
   GenWMuVZ = 0;
   GenZMuEnergy = 0;
   GenZMuEta = 0;
   GenZMuP = 0;
   GenZMuPhi = 0;
   GenZMuPt = 0;
   GenZMuPx = 0;
   GenZMuPy = 0;
   GenZMuPz = 0;
   GenZMuTauVisibleEta = 0;
   GenZMuTauVisiblePhi = 0;
   GenZMuTauVisiblePt = 0;
   GenZMuVX = 0;
   GenZMuVY = 0;
   GenZMuVZ = 0;
   GenParticleEnergy = 0;
   GenParticleEta = 0;
   GenParticleP = 0;
   GenParticlePhi = 0;
   GenParticlePt = 0;
   GenParticlePx = 0;
   GenParticlePy = 0;
   GenParticlePz = 0;
   GenParticleTauVisibleEta = 0;
   GenParticleTauVisiblePhi = 0;
   GenParticleTauVisiblePt = 0;
   GenParticleVX = 0;
   GenParticleVY = 0;
   GenParticleVZ = 0;
   GenWTauEnergy = 0;
   GenWTauEta = 0;
   GenWTauP = 0;
   GenWTauPhi = 0;
   GenWTauPt = 0;
   GenWTauPx = 0;
   GenWTauPy = 0;
   GenWTauPz = 0;
   GenWTauTauVisibleEta = 0;
   GenWTauTauVisiblePhi = 0;
   GenWTauTauVisiblePt = 0;
   GenWTauVX = 0;
   GenWTauVY = 0;
   GenWTauVZ = 0;
   GenZTauEnergy = 0;
   GenZTauEta = 0;
   GenZTauP = 0;
   GenZTauPhi = 0;
   GenZTauPt = 0;
   GenZTauPx = 0;
   GenZTauPy = 0;
   GenZTauPz = 0;
   GenZTauTauVisibleEta = 0;
   GenZTauTauVisiblePhi = 0;
   GenZTauTauVisiblePt = 0;
   GenZTauVX = 0;
   GenZTauVY = 0;
   GenZTauVZ = 0;
   HPSTauAgainstElectronDeadECALDiscr = 0;
   HPSTauAgainstElectronLooseDiscr = 0;
   HPSTauAgainstElectronLooseMVA2Discr = 0;
   HPSTauAgainstElectronLooseMVA3Discr = 0;
   HPSTauAgainstElectronMVA2categoryDiscr = 0;
   HPSTauAgainstElectronMVA2rawDiscr = 0;
   HPSTauAgainstElectronMVA3categoryDiscr = 0;
   HPSTauAgainstElectronMVA3rawDiscr = 0;
   HPSTauAgainstElectronMVADiscr = 0;
   HPSTauAgainstElectronMediumDiscr = 0;
   HPSTauAgainstElectronMediumMVA2Discr = 0;
   HPSTauAgainstElectronMediumMVA3Discr = 0;
   HPSTauAgainstElectronTightDiscr = 0;
   HPSTauAgainstElectronTightMVA2Discr = 0;
   HPSTauAgainstElectronTightMVA3Discr = 0;
   HPSTauAgainstElectronVLooseMVA2Discr = 0;
   HPSTauAgainstElectronVTightMVA3Discr = 0;
   HPSTauAgainstMuonLoose2Discr = 0;
   HPSTauAgainstMuonLooseDiscr = 0;
   HPSTauAgainstMuonMedium2Discr = 0;
   HPSTauAgainstMuonMediumDiscr = 0;
   HPSTauAgainstMuonTight2Discr = 0;
   HPSTauAgainstMuonTightDiscr = 0;
   HPSTauBremsRecoveryEOverPLead = 0;
   HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr = 0;
   HPSTauDecayModeFindingDiscr = 0;
   HPSTauEcalStripSumEOverPLead = 0;
   HPSTauEmFraction = 0;
   HPSTauEt = 0;
   HPSTauEta = 0;
   HPSTauEtaLeadCharged = 0;
   HPSTauEtaetaMoment = 0;
   HPSTauEtaphiMoment = 0;
   HPSTauHcal3x3OverPLead = 0;
   HPSTauHcalMaxOverPLead = 0;
   HPSTauHcalTotOverPLead = 0;
   HPSTauIsolationMVArawDiscr = 0;
   HPSTauIsolationPFChargedHadrCandsPtSum = 0;
   HPSTauIsolationPFGammaCandsEtSum = 0;
   HPSTauLeadPFChargedHadrCandsignedSipt = 0;
   HPSTauLeadVtxDistXY = 0;
   HPSTauLeadVtxDistZ = 0;
   HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr = 0;
   HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr = 0;
   HPSTauLooseIsolationDeltaBetaCorrDiscr = 0;
   HPSTauLooseIsolationDiscr = 0;
   HPSTauLooseIsolationMVA2Discr = 0;
   HPSTauLooseIsolationMVADiscr = 0;
   HPSTauMatchedGenJetEta = 0;
   HPSTauMatchedGenJetPhi = 0;
   HPSTauMatchedGenJetPt = 0;
   HPSTauMatchedGenParticleEta = 0;
   HPSTauMatchedGenParticlePhi = 0;
   HPSTauMatchedGenParticlePt = 0;
   HPSTauMaximumHCALPFClusterEt = 0;
   HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr = 0;
   HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr = 0;
   HPSTauMediumIsolationDeltaBetaCorrDiscr = 0;
   HPSTauMediumIsolationDiscr = 0;
   HPSTauMediumIsolationMVA2Discr = 0;
   HPSTauMediumIsolationMVADiscr = 0;
   HPSTauPhi = 0;
   HPSTauPhiLeadCharged = 0;
   HPSTauPhiphiMoment = 0;
   HPSTauPt = 0;
   HPSTauPtLeadCharged = 0;
   HPSTauSignalPFChargedHadrCandsCount = 0;
   HPSTauSignalPFChargedHadrCandsEta = 0;
   HPSTauSignalPFChargedHadrCandsPhi = 0;
   HPSTauSignalPFChargedHadrCandsPt = 0;
   HPSTauSignalPFGammaCandsCount = 0;
   HPSTauSignalPFGammaCandsEta = 0;
   HPSTauSignalPFGammaCandsPhi = 0;
   HPSTauSignalPFGammaCandsPt = 0;
   HPSTauSignalPFNeutrHadrCandsCount = 0;
   HPSTauSignalPFNeutrHadrCandsEta = 0;
   HPSTauSignalPFNeutrHadrCandsPhi = 0;
   HPSTauSignalPFNeutrHadrCandsPt = 0;
   HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr = 0;
   HPSTauTightCombinedIsolationDeltaBetaCorrDiscr = 0;
   HPSTauTightIsolationDeltaBetaCorrDiscr = 0;
   HPSTauTightIsolationDiscr = 0;
   HPSTauTightIsolationMVA2Discr = 0;
   HPSTauTightIsolationMVADiscr = 0;
   HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr = 0;
   HPSTauVLooseIsolationDeltaBetaCorrDiscr = 0;
   HPSTauVLooseIsolationDiscr = 0;
   HPSTauVtxDistXY = 0;
   HPSTauVtxDistZ = 0;
   MuonBackToBackCompatibility = 0;
   MuonBeamSpotDXY = 0;
   MuonBeamSpotDXYError = 0;
   MuonBestTrackVtxDistXY = 0;
   MuonBestTrackVtxDistZ = 0;
   MuonCocktailEta = 0;
   MuonCocktailEtaError = 0;
   MuonCocktailGlobalChi2 = 0;
   MuonCocktailP = 0;
   MuonCocktailPhi = 0;
   MuonCocktailPhiError = 0;
   MuonCocktailPt = 0;
   MuonCocktailPtError = 0;
   MuonCocktailQOverPError = 0;
   MuonCocktailTrkD0 = 0;
   MuonCocktailTrkD0Error = 0;
   MuonCocktailTrkDz = 0;
   MuonCocktailTrkDzError = 0;
   MuonCocktailTrkValidFractionOfHits = 0;
   MuonCosmicCompatibility = 0;
   MuonEcalIso = 0;
   MuonEcalVetoIso = 0;
   MuonEnergy = 0;
   MuonEta = 0;
   MuonEtaError = 0;
   MuonGlobalChi2 = 0;
   MuonHLTSingleIsoMuonMatchEta = 0;
   MuonHLTSingleIsoMuonMatchPhi = 0;
   MuonHLTSingleIsoMuonMatchPt = 0;
   MuonHLTSingleMuonMatchEta = 0;
   MuonHLTSingleMuonMatchPhi = 0;
   MuonHLTSingleMuonMatchPt = 0;
   MuonHOIso = 0;
   MuonHcalIso = 0;
   MuonHcalVetoIso = 0;
   MuonMatchedGenParticleEta = 0;
   MuonMatchedGenParticlePhi = 0;
   MuonMatchedGenParticlePt = 0;
   MuonOverlapCompatibility = 0;
   MuonP = 0;
   MuonPFIsoR03ChargedHadron = 0;
   MuonPFIsoR03ChargedParticle = 0;
   MuonPFIsoR03NeutralHadron = 0;
   MuonPFIsoR03NeutralHadronHT = 0;
   MuonPFIsoR03PU = 0;
   MuonPFIsoR03Photon = 0;
   MuonPFIsoR03PhotonHT = 0;
   MuonPFIsoR04ChargedHadron = 0;
   MuonPFIsoR04ChargedParticle = 0;
   MuonPFIsoR04NeutralHadron = 0;
   MuonPFIsoR04NeutralHadronHT = 0;
   MuonPFIsoR04PU = 0;
   MuonPFIsoR04Photon = 0;
   MuonPFIsoR04PhotonHT = 0;
   MuonPhi = 0;
   MuonPhiError = 0;
   MuonPrimaryVertexDXY = 0;
   MuonPrimaryVertexDXYError = 0;
   MuonPt = 0;
   MuonPtError = 0;
   MuonQOverPError = 0;
   MuonTimeCompatibility = 0;
   MuonTrackChi2 = 0;
   MuonTrackerIsoSumPT = 0;
   MuonTrkD0 = 0;
   MuonTrkD0Error = 0;
   MuonTrkDz = 0;
   MuonTrkDzError = 0;
   MuonTrkEta = 0;
   MuonTrkEtaError = 0;
   MuonTrkIso = 0;
   MuonTrkPhi = 0;
   MuonTrkPhiError = 0;
   MuonTrkPt = 0;
   MuonTrkPtError = 0;
   MuonTrkValidFractionOfHits = 0;
   MuonTrkVx = 0;
   MuonTrkVy = 0;
   MuonTrkVz = 0;
   MuonVtxDistXY = 0;
   MuonVtxDistZ = 0;
   PFCandEnergyLeptLink = 0;
   PFCandEtaLeptLink = 0;
   PFCandPhiLeptLink = 0;
   PFCandPtLeptLink = 0;
   PFJetBestVertexTrackAssociationFactor = 0;
   PFJetBeta = 0;
   PFJetBetaClassic = 0;
   PFJetBetaStar = 0;
   PFJetBetaStarClassic = 0;
   PFJetChargedEmEnergyFraction = 0;
   PFJetChargedHadronEnergyFraction = 0;
   PFJetChargedMuEnergyFraction = 0;
   PFJetClosestVertexWeighted3DSeparation = 0;
   PFJetClosestVertexWeightedXYSeparation = 0;
   PFJetClosestVertexWeightedZSeparation = 0;
   PFJetCombinedInclusiveSecondaryVertexBTag = 0;
   PFJetCombinedMVABTag = 0;
   PFJetCombinedSecondaryVertexBTag = 0;
   PFJetCombinedSecondaryVertexMVABTag = 0;
   PFJetElectronEnergyFraction = 0;
   PFJetEnergy = 0;
   PFJetEnergyRaw = 0;
   PFJetEta = 0;
   PFJetHFEMEnergyFraction = 0;
   PFJetHFHadronEnergyFraction = 0;
   PFJetJECUnc = 0;
   PFJetJetBProbabilityBTag = 0;
   PFJetJetProbabilityBTag = 0;
   PFJetL1FastJetJEC = 0;
   PFJetL2L3ResJEC = 0;
   PFJetL2RelJEC = 0;
   PFJetL3AbsJEC = 0;
   PFJetMuonEnergyFraction = 0;
   PFJetNeutralEmEnergyFraction = 0;
   PFJetNeutralHadronEnergyFraction = 0;
   PFJetPhi = 0;
   PFJetPhotonEnergyFraction = 0;
   PFJetPt = 0;
   PFJetPtRaw = 0;
   PFJetSimpleSecondaryVertexHighEffBTag = 0;
   PFJetSimpleSecondaryVertexHighPurBTag = 0;
   PFJetSoftElectronByIP3dBTag = 0;
   PFJetSoftElectronByPtBTag = 0;
   PFJetSoftMuonBTag = 0;
   PFJetSoftMuonByIP3dBTag = 0;
   PFJetSoftMuonByPtBTag = 0;
   PFJetTrackCountingHighEffBTag = 0;
   PFJetTrackCountingHighPurBTag = 0;
   PFMET = 0;
   PFMETPhi = 0;
   PFSumET = 0;
   PFMETPhiType01Cor = 0;
   PFMETType01Cor = 0;
   PFSumETType01Cor = 0;
   PFMETPhiType01XYCor = 0;
   PFMETType01XYCor = 0;
   PFSumETType01XYCor = 0;
   PFMETPhiType1Cor = 0;
   PFMETType1Cor = 0;
   PFSumETType1Cor = 0;
   PhotonAlpha = 0;
   PhotonChi2ConvPhot = 0;
   PhotonDPhiTracksAtVtxConvPhot = 0;
   PhotonDistOfMinApproachConvPhot = 0;
   PhotonE2OverE9 = 0;
   PhotonE3x3 = 0;
   PhotonE4SwissCross = 0;
   PhotonE5x5 = 0;
   PhotonEOverPConvPhot = 0;
   PhotonEcalIsoDR03 = 0;
   PhotonEcalIsoDR04 = 0;
   PhotonEnergy = 0;
   PhotonEta = 0;
   PhotonHcalIsoDR03 = 0;
   PhotonHcalIsoDR03FullCone = 0;
   PhotonHcalIsoDR04 = 0;
   PhotonHcalIsoDR04FullCone = 0;
   PhotonHoE = 0;
   PhotonNDofConvPhot = 0;
   PhotonPairCotThetaSeparationConvPhot = 0;
   PhotonPairInvariantMassConvPhot = 0;
   PhotonPairMomentumxConvPhot = 0;
   PhotonPairMomentumyConvPhot = 0;
   PhotonPairMomentumzConvPhot = 0;
   PhotonPhi = 0;
   PhotonPt = 0;
   PhotonSCenergy = 0;
   PhotonSCeta = 0;
   PhotonSCphi = 0;
   PhotonSCseedEnergy = 0;
   PhotonSEtaEta = 0;
   PhotonSEtaPhi = 0;
   PhotonSMajMaj = 0;
   PhotonSMinMin = 0;
   PhotonSPhiPhi = 0;
   PhotonSigmaIEtaIEta = 0;
   PhotonTimeSeed = 0;
   PhotonTrkIsoHollowDR03 = 0;
   PhotonTrkIsoHollowDR04 = 0;
   PhotonTrkIsoSolidDR03 = 0;
   PhotonTrkIsoSolidDR04 = 0;
   PhotonXVtxConvPhot = 0;
   PhotonYVtxConvPhot = 0;
   PhotonZVtxConvPhot = 0;
   TCMET = 0;
   TCMETPhi = 0;
   TCSumET = 0;
   VertexChi2 = 0;
   VertexNDF = 0;
   VertexRho = 0;
   VertexX = 0;
   VertexXErr = 0;
   VertexY = 0;
   VertexYErr = 0;
   VertexZ = 0;
   VertexZErr = 0;
   PileUpInteractionsTrue = 0;
   HLTFilterObjEta = 0;
   HLTFilterObjPhi = 0;
   HLTFilterObjPt = 0;
   ElectronCharge = 0;
   ElectronClassif = 0;
   ElectronMissingHits = 0;
   ElectronMissingHitsEG = 0;
   ElectronNumberOfBrems = 0;
   ElectronOverlaps = 0;
   ElectronPassEGammaIDEoP = 0;
   ElectronPassEGammaIDLoose = 0;
   ElectronPassEGammaIDMedium = 0;
   ElectronPassEGammaIDTight = 0;
   ElectronPassEGammaIDTrigTight = 0;
   ElectronPassEGammaIDTrigWP70 = 0;
   ElectronPassEGammaIDVeto = 0;
   ElectronPassId = 0;
   ElectronPassIsoPAT = 0;
   ElectronVtxIndex = 0;
   GenWElectronMotherIndex = 0;
   GenWElectronNumDaught = 0;
   GenWElectronPdgId = 0;
   GenWElectronStatus = 0;
   GenWElectronTauDecayMode = 0;
   GenZElectronMotherIndex = 0;
   GenZElectronNumDaught = 0;
   GenZElectronPdgId = 0;
   GenZElectronStatus = 0;
   GenZElectronTauDecayMode = 0;
   PileUpInteractions = 0;
   PileUpOriginBX = 0;
   GenWMuMotherIndex = 0;
   GenWMuNumDaught = 0;
   GenWMuPdgId = 0;
   GenWMuStatus = 0;
   GenWMuTauDecayMode = 0;
   GenZMuMotherIndex = 0;
   GenZMuNumDaught = 0;
   GenZMuPdgId = 0;
   GenZMuStatus = 0;
   GenZMuTauDecayMode = 0;
   GenParticleMotherIndex = 0;
   GenParticleNumDaught = 0;
   GenParticlePdgId = 0;
   GenParticleStatus = 0;
   GenParticleTauDecayMode = 0;
   GenWTauMotherIndex = 0;
   GenWTauNumDaught = 0;
   GenWTauPdgId = 0;
   GenWTauStatus = 0;
   GenWTauTauDecayMode = 0;
   GenZTauMotherIndex = 0;
   GenZTauNumDaught = 0;
   GenZTauPdgId = 0;
   GenZTauStatus = 0;
   GenZTauTauDecayMode = 0;
   HPSTauCharge = 0;
   HPSTauDecayMode = 0;
   HPSTauIsCaloTau = 0;
   HPSTauIsPFTau = 0;
   HPSTauVtxIndex = 0;
   MuonBestTrackVtxIndex = 0;
   MuonCharge = 0;
   MuonCocktailCharge = 0;
   MuonCocktailRefitID = 0;
   MuonCocktailTrkHits = 0;
   MuonGlobalTrkValidHits = 0;
   MuonIsGlobal = 0;
   MuonIsPF = 0;
   MuonIsTracker = 0;
   MuonPassID = 0;
   MuonPixelHits = 0;
   MuonSegmentMatches = 0;
   MuonStationMatches = 0;
   MuonTrackLayersWithMeasurement = 0;
   MuonTrkHits = 0;
   MuonTrkHitsTrackerOnly = 0;
   MuonTrkPixelHits = 0;
   MuonVtxIndex = 0;
   PFCandChargeLeptLink = 0;
   PFJetBestVertexTrackAssociationIndex = 0;
   PFJetChargedHadronMultiplicity = 0;
   PFJetChargedMultiplicity = 0;
   PFJetClosestVertex3DIndex = 0;
   PFJetClosestVertexXYIndex = 0;
   PFJetClosestVertexZIndex = 0;
   PFJetElectronMultiplicity = 0;
   PFJetHFEMMultiplicity = 0;
   PFJetHFHadronMultiplicity = 0;
   PFJetMuonMultiplicity = 0;
   PFJetNConstituents = 0;
   PFJetNeutralHadronMultiplicity = 0;
   PFJetNeutralMultiplicity = 0;
   PFJetPartonFlavour = 0;
   PFJetPassLooseID = 0;
   PFJetPassTightID = 0;
   PFJetPhotonMultiplicity = 0;
   PhotonNTracksConvPhot = 0;
   HLTInsideDatasetTriggerPrescales = 0;
   HLTOutsideDatasetTriggerPrescales = 0;
   L1PhysBits = 0;
   L1TechBits = 0;
   VertexNTracks = 0;
   VertexNTracksW05 = 0;
   HLTFilterObjId = 0;

   
   /// New variables 2013/12/02
   CaloJetEnergy = 0;
   CaloJetEta = 0;
   CaloJetPhi = 0;
   CaloJetPt = 0;
   CaloJetPassLooseID = 0;
   CaloJetPassTightID = 0;
   MuonGlobalE = 0;
   MuonGlobalEta = 0;
   MuonGlobalPhi = 0;
   MuonGlobalPt = 0;
   MuonMuonSpecE = 0;
   MuonMuonSpecEta = 0;
   MuonMuonSpecPhi = 0;
   MuonMuonSpecPt = 0;
   PFJetScaledDownEnergy = 0;
   PFJetScaledDownPt = 0;
   PFJetScaledUpEnergy = 0;
   PFJetScaledUpPt = 0;
   PFJetSmearedDownEnergy = 0;
   PFJetSmearedDownPt = 0;
   PFJetSmearedUpEnergy = 0;
   PFJetSmearedUpPt = 0;
   PFMETType01XYCorElectronEnDown = 0;
   PFMETType01XYCorElectronEnUp = 0;
   PFMETType01XYCorJetEnDown = 0;
   PFMETType01XYCorJetEnUp = 0;
   PFMETType01XYCorJetResDown = 0;
   PFMETType01XYCorJetResUp = 0;
   PFMETType01XYCorMuonEnDown = 0;
   PFMETType01XYCorMuonEnUp = 0;
   PFMETType01XYCorUnclusteredDown = 0;
   PFMETType01XYCorUnclusteredUp = 0;
   MuonGlobalCharge = 0;
   MuonMuonSpecCharge = 0;
   MuonTrackerCharge = 0;

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
    ConnectCaloJets();
    //ConnectPhotons();
    ConnectTaus();
    ConnectTruth();
    ConnectTrigger();
    
    if(setall) ConnectAllBranches();
  }
  return;
}
void Data::ConnectEvent(){

  ConnectVariable("isData", isData, b_isData);
  
  ConnectVariable("run", run, b_run);
  ConnectVariable("VertexNTracks", VertexNTracks, b_VertexNTracks);
  ConnectVariable("event", event, b_event);
  ConnectVariable("Weight", Weight, b_Weight);
  ConnectVariable("isPhysDeclared", isPhysDeclared, b_isPhysDeclared);
  ConnectVariable("isPrimaryVertex", isPrimaryVertex, b_isPrimaryVertex);

  ConnectVariable("isTrackingFailure", isTrackingFailure, b_isTrackingFailure);
  ConnectVariable("passHBHENoiseFilter", passHBHENoiseFilter, b_passHBHENoiseFilter);
  ConnectVariable("passBadEESupercrystalFilter", passBadEESupercrystalFilter, b_passBadEESupercrystalFilter);
  ConnectVariable("passBeamHaloFilterLoose", passBeamHaloFilterLoose, b_passBeamHaloFilterLoose);
  ConnectVariable("passEcalDeadCellBoundaryEnergyFilter", passEcalDeadCellBoundaryEnergyFilter, b_passEcalDeadCellBoundaryEnergyFilter);
  ConnectVariable("passEcalDeadCellTriggerPrimitiveFilter", passEcalDeadCellTriggerPrimitiveFilter, b_passEcalDeadCellTriggerPrimitiveFilter);
  ConnectVariable("passEcalLaserCorrFilter", passEcalLaserCorrFilter, b_passEcalLaserCorrFilter);
  ConnectVariable("passTrackingFailureFilter", passTrackingFailureFilter, b_passTrackingFailureFilter);
  ConnectVariable("passBeamHaloFilterTight", passBeamHaloFilterTight, b_passBeamHaloFilterTight);
  
  ConnectVariable("VertexIsFake", VertexIsFake, b_VertexIsFake);
  ConnectVariable("VertexChi2", VertexChi2, b_VertexChi2);
  ConnectVariable("VertexNDF", VertexNDF, b_VertexNDF);
  ConnectVariable("VertexRho", VertexRho, b_VertexRho);
  ConnectVariable("VertexX", VertexX, b_VertexX);
  ConnectVariable("VertexXErr", VertexXErr, b_VertexXErr);
  ConnectVariable("VertexY", VertexY, b_VertexY);
  ConnectVariable("VertexYErr", VertexYErr, b_VertexYErr);
  ConnectVariable("VertexZ", VertexZ, b_VertexZ);
  ConnectVariable("VertexZErr", VertexZErr, b_VertexZErr);
  ConnectVariable("PileUpInteractionsTrue", PileUpInteractionsTrue, b_PileUpInteractionsTrue);
  
  ConnectVariable("PDFCTEQWeights", PDFCTEQWeights, b_PDFCTEQWeights);
  ConnectVariable("PDFMSTWWeights", PDFMSTWWeights, b_PDFMSTWWeights);
  ConnectVariable("PDFNNPDFWeights", PDFNNPDFWeights, b_PDFNNPDFWeights);

  return;}


void Data::ConnectTrigger(){
  
  //#####   Trigger branches
  ConnectVariable("HLTInsideDatasetTriggerNames", HLTInsideDatasetTriggerNames, b_HLTInsideDatasetTriggerNames);
  ConnectVariable("HLTInsideDatasetTriggerDecisions", HLTInsideDatasetTriggerDecisions, b_HLTInsideDatasetTriggerDecisions);
  ConnectVariable("HLTInsideDatasetTriggerPrescales", HLTInsideDatasetTriggerPrescales, b_HLTInsideDatasetTriggerPrescales);
  ConnectVariable("HLTOutsideDatasetTriggerPrescales", HLTOutsideDatasetTriggerPrescales, b_HLTOutsideDatasetTriggerPrescales);  
  
  ConnectVariable("MuonHLTSingleIsoMuonMatched", MuonHLTSingleIsoMuonMatched, b_MuonHLTSingleIsoMuonMatched) ;
  ConnectVariable("MuonHLTSingleMuonMatched", MuonHLTSingleMuonMatched, b_MuonHLTSingleMuonMatched);
  ConnectVariable("MuonHLTDoubleMuonMatched", MuonHLTDoubleMuonMatched, b_MuonHLTDoubleMuonMatched);
  ConnectVariable("ElectronHLTDoubleEleMatched", ElectronHLTDoubleEleMatched, b_ElectronHLTDoubleEleMatched);
  ConnectVariable("ElectronHLTSingleEleMatched", ElectronHLTSingleEleMatched, b_ElectronHLTSingleEleMatched);
  ConnectVariable("ElectronHLTSingleEleWP80Matched", ElectronHLTSingleEleWP80Matched, b_ElectronHLTSingleEleWP80Matched);

  return;
}

void Data::ConnectTaus(){

  //#####   Tau branches
  ConnectVariable("HPSTauPt", HPSTauPt, b_HPSTauPt);
  ConnectVariable("HPSTauPhi", HPSTauPhi, b_HPSTauPhi);
  ConnectVariable("HPSTauEt", HPSTauEt, b_HPSTauEt);
  ConnectVariable("HPSTauEta", HPSTauEta, b_HPSTauEta);
  ConnectVariable("HPSTauCharge", HPSTauCharge, b_HPSTauCharge);
  ConnectVariable("HPSTauIsPFTau", HPSTauIsPFTau, b_HPSTauIsPFTau);
  return;}

void Data::ConnectMuons(){
  
  //#####   Muon branches
  ConnectVariable("MuonEcalIso", MuonEcalIso, b_MuonEcalIso);
  ConnectVariable("MuonEcalVetoIso", MuonEcalVetoIso, b_MuonEcalVetoIso);
  ConnectVariable("MuonEnergy", MuonEnergy, b_MuonEnergy);
  ConnectVariable("MuonEta", MuonEta, b_MuonEta);
  ConnectVariable("MuonEtaError", MuonEtaError, b_MuonEtaError);
  ConnectVariable("MuonGlobalChi2", MuonGlobalChi2, b_MuonGlobalChi2);
  ConnectVariable("MuonHOIso", MuonHOIso, b_MuonHOIso);
  ConnectVariable("MuonHcalIso", MuonHcalIso, b_MuonHcalIso);
  ConnectVariable("MuonHcalVetoIso", MuonHcalVetoIso, b_MuonHcalVetoIso);
  ConnectVariable("MuonMatchedGenParticleEta", MuonMatchedGenParticleEta, b_MuonMatchedGenParticleEta);
  ConnectVariable("MuonMatchedGenParticlePhi", MuonMatchedGenParticlePhi, b_MuonMatchedGenParticlePhi);
  ConnectVariable("MuonMatchedGenParticlePt", MuonMatchedGenParticlePt, b_MuonMatchedGenParticlePt);
  ConnectVariable("MuonOverlapCompatibility", MuonOverlapCompatibility, b_MuonOverlapCompatibility);
  ConnectVariable("MuonP", MuonP, b_MuonP);
  ConnectVariable("MuonPFIsoR03ChargedHadron", MuonPFIsoR03ChargedHadron, b_MuonPFIsoR03ChargedHadron);
  ConnectVariable("MuonPFIsoR03ChargedParticle", MuonPFIsoR03ChargedParticle, b_MuonPFIsoR03ChargedParticle);
  ConnectVariable("MuonPFIsoR03NeutralHadron", MuonPFIsoR03NeutralHadron, b_MuonPFIsoR03NeutralHadron);
  ConnectVariable("MuonPFIsoR03NeutralHadronHT", MuonPFIsoR03NeutralHadronHT, b_MuonPFIsoR03NeutralHadronHT);
  ConnectVariable("MuonPFIsoR03PU", MuonPFIsoR03PU, b_MuonPFIsoR03PU);
  ConnectVariable("MuonPFIsoR03Photon", MuonPFIsoR03Photon, b_MuonPFIsoR03Photon);
  ConnectVariable("MuonPFIsoR03PhotonHT", MuonPFIsoR03PhotonHT, b_MuonPFIsoR03PhotonHT);
  ConnectVariable("MuonPFIsoR04ChargedHadron", MuonPFIsoR04ChargedHadron, b_MuonPFIsoR04ChargedHadron);
  ConnectVariable("MuonPFIsoR04ChargedParticle", MuonPFIsoR04ChargedParticle, b_MuonPFIsoR04ChargedParticle);
  ConnectVariable("MuonPFIsoR04NeutralHadron", MuonPFIsoR04NeutralHadron, b_MuonPFIsoR04NeutralHadron);
  ConnectVariable("MuonPFIsoR04NeutralHadronHT", MuonPFIsoR04NeutralHadronHT, b_MuonPFIsoR04NeutralHadronHT);
  ConnectVariable("MuonPFIsoR04PU", MuonPFIsoR04PU, b_MuonPFIsoR04PU);
  ConnectVariable("MuonPFIsoR04Photon", MuonPFIsoR04Photon, b_MuonPFIsoR04Photon);
  ConnectVariable("MuonPFIsoR04PhotonHT", MuonPFIsoR04PhotonHT, b_MuonPFIsoR04PhotonHT);
  ConnectVariable("MuonPhi", MuonPhi, b_MuonPhi);
  ConnectVariable("MuonPhiError", MuonPhiError, b_MuonPhiError);
  ConnectVariable("MuonPrimaryVertexDXY", MuonPrimaryVertexDXY, b_MuonPrimaryVertexDXY);
  ConnectVariable("MuonPrimaryVertexDXYError", MuonPrimaryVertexDXYError, b_MuonPrimaryVertexDXYError);
  ConnectVariable("MuonPt", MuonPt, b_MuonPt);
  ConnectVariable("MuonPtError", MuonPtError, b_MuonPtError);
  ConnectVariable("MuonQOverPError", MuonQOverPError, b_MuonQOverPError);
  ConnectVariable("MuonTimeCompatibility", MuonTimeCompatibility, b_MuonTimeCompatibility);
  ConnectVariable("MuonTrackChi2", MuonTrackChi2, b_MuonTrackChi2);
  ConnectVariable("MuonTrackerIsoSumPT", MuonTrackerIsoSumPT, b_MuonTrackerIsoSumPT);
  ConnectVariable("MuonBestTrackVtxDistXY", MuonBestTrackVtxDistXY,b_MuonBestTrackVtxDistXY);
  ConnectVariable("MuonBestTrackVtxDistZ", MuonBestTrackVtxDistZ, b_MuonBestTrackVtxDistZ);
  ConnectVariable("MuonTrkD0", MuonTrkD0, b_MuonTrkD0);
  ConnectVariable("MuonTrkD0Error", MuonTrkD0Error, b_MuonTrkD0Error);
  ConnectVariable("MuonTrkDz", MuonTrkDz, b_MuonTrkDz);
  ConnectVariable("MuonTrkDzError", MuonTrkDzError, b_MuonTrkDzError);
  ConnectVariable("MuonTrkEta", MuonTrkEta, b_MuonTrkEta);
  ConnectVariable("MuonTrkEtaError", MuonTrkEtaError, b_MuonTrkEtaError);
  ConnectVariable("MuonTrkIso", MuonTrkIso, b_MuonTrkIso);
  ConnectVariable("MuonTrkPhi", MuonTrkPhi, b_MuonTrkPhi);
  ConnectVariable("MuonTrkPhiError", MuonTrkPhiError, b_MuonTrkPhiError);
  ConnectVariable("MuonTrkPt", MuonTrkPt, b_MuonTrkPt);
  ConnectVariable("MuonTrkPtError", MuonTrkPtError, b_MuonTrkPtError);
  ConnectVariable("MuonTrkValidFractionOfHits", MuonTrkValidFractionOfHits, b_MuonTrkValidFractionOfHits);
  ConnectVariable("MuonTrkVx", MuonTrkVx, b_MuonTrkVx);
  ConnectVariable("MuonTrkVy", MuonTrkVy, b_MuonTrkVy);
  ConnectVariable("MuonTrkVz", MuonTrkVz, b_MuonTrkVz);
  ConnectVariable("MuonVtxDistXY", MuonVtxDistXY, b_MuonVtxDistXY);
  ConnectVariable("MuonVtxDistZ", MuonVtxDistZ, b_MuonVtxDistZ);
  ConnectVariable("MuonCharge", MuonCharge, b_MuonCharge);
  ConnectVariable("MuonGlobalTrkValidHits", MuonGlobalTrkValidHits, b_MuonGlobalTrkValidHits);
  ConnectVariable("MuonIsGlobal", MuonIsGlobal, b_MuonIsGlobal);
  ConnectVariable("MuonIsPF", MuonIsPF, b_MuonIsPF);
  ConnectVariable("MuonIsTracker", MuonIsTracker, b_MuonIsTracker);
  ConnectVariable("MuonPassID", MuonPassID, b_MuonPassID);
  ConnectVariable("MuonPixelHits", MuonPixelHits, b_MuonPixelHits);
  ConnectVariable("MuonSegmentMatches", MuonSegmentMatches, b_MuonSegmentMatches);
  ConnectVariable("MuonStationMatches", MuonStationMatches, b_MuonStationMatches);
  ConnectVariable("MuonTrackLayersWithMeasurement", MuonTrackLayersWithMeasurement, b_MuonTrackLayersWithMeasurement);
  ConnectVariable("MuonTrkHits", MuonTrkHits, b_MuonTrkHits);
  ConnectVariable("MuonTrkHitsTrackerOnly", MuonTrkHitsTrackerOnly, b_MuonTrkHitsTrackerOnly);
  ConnectVariable("MuonTrkPixelHits", MuonTrkPixelHits, b_MuonTrkPixelHits);
  ConnectVariable("MuonVtxIndex", MuonVtxIndex, b_MuonVtxIndex);
  ConnectVariable("MuonBestTrackVtxIndex", MuonBestTrackVtxIndex, b_MuonBestTrackVtxIndex) ;


  /// New variables 2013/12/02
  ConnectVariable("MuonGlobalE", MuonGlobalE, b_MuonGlobalE);
  ConnectVariable("MuonGlobalEta", MuonGlobalEta, b_MuonGlobalEta);
  ConnectVariable("MuonGlobalPhi", MuonGlobalPhi, b_MuonGlobalPhi);
  ConnectVariable("MuonGlobalPt", MuonGlobalPt, b_MuonGlobalPt);
  ConnectVariable("MuonMuonSpecE", MuonMuonSpecE, b_MuonMuonSpecE);
  ConnectVariable("MuonMuonSpecEta", MuonMuonSpecEta, b_MuonMuonSpecEta);
  ConnectVariable("MuonMuonSpecPhi", MuonMuonSpecPhi, b_MuonMuonSpecPhi);
  ConnectVariable("MuonMuonSpecPt", MuonMuonSpecPt, b_MuonMuonSpecPt);
  ConnectVariable("MuonGlobalCharge",MuonGlobalCharge, b_MuonGlobalCharge);
  ConnectVariable("MuonMuonSpecCharge",MuonMuonSpecCharge, b_MuonMuonSpecCharge);
  ConnectVariable("MuonTrackerCharge", MuonTrackerCharge, b_MuonTrackerCharge);


  return;}

void Data::ConnectElectrons(){

  //#####   Electron branches
  ConnectVariable("ElectronGsfCtfCharge", ElectronGsfCtfCharge, b_ElectronGsfCtfCharge);
  ConnectVariable("ElectronGsfScPixCharge", ElectronGsfScPixCharge, b_ElectronGsfScPixCharge);
  ConnectVariable("ElectronGsfCtfScPixCharge", ElectronGsfCtfScPixCharge, b_ElectronGsfCtfScPixCharge);
  ConnectVariable("ElectronHasEcalDrivenSeed", ElectronHasEcalDrivenSeed, b_ElectronHasEcalDrivenSeed);
  ConnectVariable("ElectronHasMatchedConvPhot", ElectronHasMatchedConvPhot, b_ElectronHasMatchedConvPhot);
  ConnectVariable("ElectronHasTrackerDrivenSeed", ElectronHasTrackerDrivenSeed, b_ElectronHasTrackerDrivenSeed);

  ConnectVariable("ElectronmvatrigV0", ElectronmvatrigV0, b_ElectronmvatrigV0); 
  ConnectVariable("ElectronmvaNontrigV0", ElectronmvaNontrigV0, b_ElectronmvaNontrigV0); 
  ConnectVariable("ElectronIsEB", ElectronIsEB, b_ElectronIsEB);
  ConnectVariable("ElectronIsEE", ElectronIsEE, b_ElectronIsEE);
  ConnectVariable("ElectronBeamSpotDXY", ElectronBeamSpotDXY, b_ElectronBeamSpotDXY);
  ConnectVariable("ElectronBeamSpotDXYError", ElectronBeamSpotDXYError, b_ElectronBeamSpotDXYError);
  ConnectVariable("ElectronCaloEnergy", ElectronCaloEnergy, b_ElectronCaloEnergy);
  ConnectVariable("ElectronConvFitProb", ElectronConvFitProb, b_ElectronConvFitProb);
  ConnectVariable("ElectronDCotTheta", ElectronDCotTheta, b_ElectronDCotTheta);
  ConnectVariable("ElectronDeltaEtaTrkSC", ElectronDeltaEtaTrkSC, b_ElectronDeltaEtaTrkSC);
  ConnectVariable("ElectronDeltaPhiTrkSC", ElectronDeltaPhiTrkSC, b_ElectronDeltaPhiTrkSC);
  ConnectVariable("ElectronDist", ElectronDist, b_ElectronDist);
  ConnectVariable("ElectronE1x5OverE5x5", ElectronE1x5OverE5x5, b_ElectronE1x5OverE5x5);
  ConnectVariable("ElectronE2x5OverE5x5", ElectronE2x5OverE5x5, b_ElectronE2x5OverE5x5);
  ConnectVariable("ElectronESuperClusterOverP", ElectronESuperClusterOverP, b_ElectronESuperClusterOverP);
  ConnectVariable("ElectronEcalIsoDR03", ElectronEcalIsoDR03, b_ElectronEcalIsoDR03);
  ConnectVariable("ElectronEcalIsoPAT", ElectronEcalIsoPAT, b_ElectronEcalIsoPAT);
  ConnectVariable("ElectronEnergy", ElectronEnergy, b_ElectronEnergy);
  ConnectVariable("ElectronEta", ElectronEta, b_ElectronEta);
  ConnectVariable("ElectronHoE", ElectronHoE, b_ElectronHoE);
  ConnectVariable("ElectronPFChargedHadronIso03", ElectronPFChargedHadronIso03, b_ElectronPFChargedHadronIso03);
  ConnectVariable("ElectronPFChargedHadronIso04", ElectronPFChargedHadronIso04, b_ElectronPFChargedHadronIso04);
  ConnectVariable("ElectronPFNeutralHadronIso03", ElectronPFNeutralHadronIso03, b_ElectronPFNeutralHadronIso03);
  ConnectVariable("ElectronPFNeutralHadronIso04", ElectronPFNeutralHadronIso04, b_ElectronPFNeutralHadronIso04);
  ConnectVariable("ElectronPFPhotonIso03", ElectronPFPhotonIso03, b_ElectronPFPhotonIso03);
  ConnectVariable("ElectronPFPhotonIso04", ElectronPFPhotonIso04, b_ElectronPFPhotonIso04);
  ConnectVariable("ElectronPhi", ElectronPhi, b_ElectronPhi);
  ConnectVariable("ElectronPrimaryVertexDXY", ElectronPrimaryVertexDXY, b_ElectronPrimaryVertexDXY);
  ConnectVariable("ElectronPrimaryVertexDXYError", ElectronPrimaryVertexDXYError, b_ElectronPrimaryVertexDXYError);
  ConnectVariable("ElectronPt", ElectronPt, b_ElectronPt);
  ConnectVariable("ElectronSCEta", ElectronSCEta, b_ElectronSCEta);
  ConnectVariable("ElectronSCPhi", ElectronSCPhi, b_ElectronSCPhi);
  ConnectVariable("ElectronSCPt", ElectronSCPt, b_ElectronSCPt);
  ConnectVariable("ElectronSCRawEnergy", ElectronSCRawEnergy, b_ElectronSCRawEnergy);
  ConnectVariable("ElectronSigmaEtaEta", ElectronSigmaEtaEta, b_ElectronSigmaEtaEta);
  ConnectVariable("ElectronSigmaIEtaIEta", ElectronSigmaIEtaIEta, b_ElectronSigmaIEtaIEta);
  ConnectVariable("ElectronTrackPt", ElectronTrackPt, b_ElectronTrackPt);
  ConnectVariable("ElectronTrackValidFractionOfHits", ElectronTrackValidFractionOfHits, b_ElectronTrackValidFractionOfHits);
  ConnectVariable("ElectronTrackVx", ElectronTrackVx, b_ElectronTrackVx);
  ConnectVariable("ElectronTrackVy", ElectronTrackVy, b_ElectronTrackVy);
  ConnectVariable("ElectronTrackVz", ElectronTrackVz, b_ElectronTrackVz);
  ConnectVariable("ElectronVtxDistXY", ElectronVtxDistXY, b_ElectronVtxDistXY);
  ConnectVariable("ElectronVtxDistZ", ElectronVtxDistZ, b_ElectronVtxDistZ);
  ConnectVariable("ElectronCharge", ElectronCharge, b_ElectronCharge);
  ConnectVariable("ElectronClassif", ElectronClassif, b_ElectronClassif);
  ConnectVariable("ElectronMissingHits", ElectronMissingHits, b_ElectronMissingHits);
  ConnectVariable("ElectronMissingHitsEG", ElectronMissingHitsEG, b_ElectronMissingHitsEG);
  ConnectVariable("ElectronNumberOfBrems", ElectronNumberOfBrems, b_ElectronNumberOfBrems);
  ConnectVariable("ElectronOverlaps", ElectronOverlaps, b_ElectronOverlaps);
  ConnectVariable("ElectronPassEGammaIDEoP", ElectronPassEGammaIDEoP, b_ElectronPassEGammaIDEoP);
  ConnectVariable("ElectronPassEGammaIDLoose", ElectronPassEGammaIDLoose, b_ElectronPassEGammaIDLoose);
  ConnectVariable("ElectronPassEGammaIDMedium", ElectronPassEGammaIDMedium, b_ElectronPassEGammaIDMedium);
  ConnectVariable("ElectronPassEGammaIDTight", ElectronPassEGammaIDTight, b_ElectronPassEGammaIDTight);
  ConnectVariable("ElectronPassEGammaIDTrigTight", ElectronPassEGammaIDTrigTight, b_ElectronPassEGammaIDTrigTight);
  ConnectVariable("ElectronPassEGammaIDTrigWP70", ElectronPassEGammaIDTrigWP70, b_ElectronPassEGammaIDTrigWP70);
  ConnectVariable("ElectronPassEGammaIDVeto", ElectronPassEGammaIDVeto, b_ElectronPassEGammaIDVeto);
  ConnectVariable("ElectronPassId", ElectronPassId, b_ElectronPassId);
  ConnectVariable("ElectronVtxIndex", ElectronVtxIndex, b_ElectronVtxIndex);
  ConnectVariable("ElectronTrkIsoDR03", ElectronTrkIsoDR03, b_ElectronTrkIsoDR03);
  ConnectVariable("ElectronFbrem", ElectronFbrem, b_ElectronFbrem);
  ConnectVariable("ElectronHcalIsoDR03", ElectronHcalIsoDR03, b_ElectronHcalIsoDR03);
  ConnectVariable("ElectronLeadVtxDistXY", ElectronLeadVtxDistXY, b_ElectronLeadVtxDistXY);
  ConnectVariable("ElectronLeadVtxDistZ", ElectronLeadVtxDistZ, b_ElectronLeadVtxDistZ);
  ConnectVariable("ElectronMatchedGenParticleEta", ElectronMatchedGenParticleEta, b_ElectronMatchedGenParticleEta);
  ConnectVariable("ElectronMatchedGenParticlePhi", ElectronMatchedGenParticlePhi, b_ElectronMatchedGenParticlePhi);
  ConnectVariable("ElectronMatchedGenParticlePt", ElectronMatchedGenParticlePt, b_ElectronMatchedGenParticlePt);
  ConnectVariable("ElectronHcalIsoPAT", ElectronHcalIsoPAT, b_ElectronHcalIsoPAT);
  ConnectVariable("ElectronTrkIsoPAT", ElectronTrkIsoPAT, b_ElectronTrkIsoPAT);
  
  /// NEW
  /*
    vector<double>  *ElectronR9;

  */
  return;
}

void Data::ConnectPFJets(){

  //#####   Jet branches
  ConnectVariable("rhoJets", rhoJets, b_rhoJets);
  /// TLV variables
  ConnectVariable("PFJetEnergy", PFJetEnergy, b_PFJetEnergy);
  ConnectVariable("PFJetEnergyRaw", PFJetEnergyRaw, b_PFJetEnergyRaw);
  ConnectVariable("PFJetEta", PFJetEta, b_PFJetEta);
  ConnectVariable("PFJetPhi", PFJetPhi, b_PFJetPhi);
  ConnectVariable("PFJetPt", PFJetPt, b_PFJetPt);
  ///Pileup
  ConnectVariable("PFJetPileupjetIDpassLooseWP", PFJetPileupjetIDpassLooseWP, b_PFJetPileupjetIDpassLooseWP);
  ConnectVariable("PFJetPileupjetIDpassMediumWP", PFJetPileupjetIDpassMediumWP, b_PFJetPileupjetIDpassMediumWP);
  ConnectVariable("PFJetPileupjetIDpassTightWP", PFJetPileupjetIDpassTightWP, b_PFJetPileupjetIDpassTightWP);
  ConnectVariable("PFJetJetPileupIdflag", PFJetJetPileupIdflag, b_PFJetJetPileupIdflag);
  ConnectVariable("PFJetJetPileupMVA", PFJetJetPileupMVA, b_PFJetJetPileupMVA);
  
  /// Jet Energy Fractions
  ConnectVariable("PFJetChargedEmEnergyFraction", PFJetChargedEmEnergyFraction, b_PFJetChargedEmEnergyFraction);
  ConnectVariable("PFJetChargedHadronEnergyFraction", PFJetChargedHadronEnergyFraction, b_PFJetChargedHadronEnergyFraction);
  ConnectVariable("PFJetChargedMuEnergyFraction", PFJetChargedMuEnergyFraction, b_PFJetChargedMuEnergyFraction);
  ConnectVariable("PFJetElectronEnergyFraction", PFJetElectronEnergyFraction, b_PFJetElectronEnergyFraction);
  ConnectVariable("PFJetHFEMEnergyFraction", PFJetHFEMEnergyFraction, b_PFJetHFEMEnergyFraction);
  ConnectVariable("PFJetHFHadronEnergyFraction", PFJetHFHadronEnergyFraction, b_PFJetHFHadronEnergyFraction);
  ConnectVariable("PFJetMuonEnergyFraction", PFJetMuonEnergyFraction, b_PFJetMuonEnergyFraction);
  ConnectVariable("PFJetNeutralEmEnergyFraction", PFJetNeutralEmEnergyFraction, b_PFJetNeutralEmEnergyFraction);
  ConnectVariable("PFJetNeutralHadronEnergyFraction", PFJetNeutralHadronEnergyFraction, b_PFJetNeutralHadronEnergyFraction);
  ConnectVariable("PFJetPhotonEnergyFraction", PFJetPhotonEnergyFraction, b_PFJetPhotonEnergyFraction);
  // Jet Track/Vertex Variables
  ConnectVariable("PFJetClosestVertexWeighted3DSeparation", PFJetClosestVertexWeighted3DSeparation, b_PFJetClosestVertexWeighted3DSeparation);
  ConnectVariable("PFJetClosestVertexWeightedXYSeparation", PFJetClosestVertexWeightedXYSeparation, b_PFJetClosestVertexWeightedXYSeparation);
  ConnectVariable("PFJetClosestVertexWeightedZSeparation", PFJetClosestVertexWeightedZSeparation, b_PFJetClosestVertexWeightedZSeparation);
  ConnectVariable("PFJetBestVertexTrackAssociationIndex", PFJetBestVertexTrackAssociationIndex, b_PFJetBestVertexTrackAssociationIndex);
  ConnectVariable("PFJetBestVertexTrackAssociationFactor", PFJetBestVertexTrackAssociationFactor, b_PFJetBestVertexTrackAssociationFactor);
  ConnectVariable("PFJetChargedHadronMultiplicity", PFJetChargedHadronMultiplicity, b_PFJetChargedHadronMultiplicity);
  ConnectVariable("PFJetChargedMultiplicity", PFJetChargedMultiplicity, b_PFJetChargedMultiplicity);
  ConnectVariable("PFJetClosestVertex3DIndex", PFJetClosestVertex3DIndex, b_PFJetClosestVertex3DIndex);
  ConnectVariable("PFJetClosestVertexXYIndex", PFJetClosestVertexXYIndex, b_PFJetClosestVertexXYIndex);
  ConnectVariable("PFJetClosestVertexZIndex", PFJetClosestVertexZIndex, b_PFJetClosestVertexZIndex);
  ConnectVariable("PFJetElectronMultiplicity", PFJetElectronMultiplicity, b_PFJetElectronMultiplicity);
  ConnectVariable("PFJetHFEMMultiplicity", PFJetHFEMMultiplicity, b_PFJetHFEMMultiplicity);
  ConnectVariable("PFJetHFHadronMultiplicity", PFJetHFHadronMultiplicity, b_PFJetHFHadronMultiplicity);
  ConnectVariable("PFJetMuonMultiplicity", PFJetMuonMultiplicity, b_PFJetMuonMultiplicity);
  ConnectVariable("PFJetNConstituents", PFJetNConstituents, b_PFJetNConstituents);
  ConnectVariable("PFJetNeutralHadronMultiplicity", PFJetNeutralHadronMultiplicity, b_PFJetNeutralHadronMultiplicity);
  ConnectVariable("PFJetNeutralMultiplicity", PFJetNeutralMultiplicity, b_PFJetNeutralMultiplicity);
  ConnectVariable("PFJetPhotonMultiplicity", PFJetPhotonMultiplicity, b_PFJetPhotonMultiplicity);
  
  /// BTAG variables
  ConnectVariable("PFJetCombinedSecondaryVertexBTag", PFJetCombinedSecondaryVertexBTag, b_PFJetCombinedSecondaryVertexBTag);
  ConnectVariable("PFJetJetBProbabilityBTag", PFJetJetBProbabilityBTag, b_PFJetJetBProbabilityBTag);
  ConnectVariable("PFJetJetProbabilityBTag", PFJetJetProbabilityBTag, b_PFJetJetProbabilityBTag);
  ConnectVariable("PFJetSoftMuonBTag", PFJetSoftMuonBTag, b_PFJetSoftMuonBTag);
  ConnectVariable("PFJetSoftMuonByIP3dBTag", PFJetSoftMuonByIP3dBTag, b_PFJetSoftMuonByIP3dBTag);
  ConnectVariable("PFJetSoftMuonByPtBTag", PFJetSoftMuonByPtBTag, b_PFJetSoftMuonByPtBTag);
  ConnectVariable("PFJetTrackCountingHighPurBTag", PFJetTrackCountingHighPurBTag, b_PFJetTrackCountingHighPurBTag);
  //ConnectVariable("PFJetCombinedInclusiveSecondaryVertexBTag", PFJetCombinedInclusiveSecondaryVertexBTag);
  //ConnectVariable("PFJetCombinedMVABTag", PFJetCombinedMVABTag);
  //ConnectVariable("PFJetCombinedSecondaryVertexMVABTag", PFJetCombinedSecondaryVertexMVABTag);
  //ConnectVariable("PFJetSimpleSecondaryVertexHighEffBTag", PFJetSimpleSecondaryVertexHighEffBTag);
  //ConnectVariable("PFJetSimpleSecondaryVertexHighPurBTag", PFJetSimpleSecondaryVertexHighPurBTag);
  //ConnectVariable("PFJetSoftElectronByIP3dBTag", PFJetSoftElectronByIP3dBTag);
  //ConnectVariable("PFJetSoftElectronByPtBTag", PFJetSoftElectronByPtBTag);
  //ConnectVariable("PFJetTrackCountingHighEffBTag", PFJetTrackCountingHighEffBTag);
  /// OTHERS
  ConnectVariable("PFCandChargeLeptLink", PFCandChargeLeptLink, b_PFCandChargeLeptLink);
  ConnectVariable("PFJetPartonFlavour", PFJetPartonFlavour, b_PFJetPartonFlavour);
  ConnectVariable("PFJetPassLooseID", PFJetPassLooseID, b_PFJetPassLooseID);
  ConnectVariable("PFJetPassTightID", PFJetPassTightID, b_PFJetPassTightID);


 
  /// Uncertainties                                                                                                                                          // New Variables 2013/12/02 
  ConnectVariable("PFJetJECUnc", PFJetJECUnc, b_PFJetJECUnc);
  ConnectVariable("PFJetScaledDownEnergy",PFJetScaledDownEnergy,b_PFJetScaledDownEnergy);
  ConnectVariable("PFJetScaledDownPt",PFJetScaledDownPt,b_PFJetScaledDownPt);
  ConnectVariable("PFJetScaledUpEnergy",PFJetScaledUpEnergy,b_PFJetScaledUpEnergy);
  ConnectVariable("PFJetScaledUpPt",PFJetScaledUpPt,b_PFJetScaledUpPt);
  ConnectVariable("PFJetSmearedDownEnergy",PFJetSmearedDownEnergy,b_PFJetSmearedDownEnergy);
  ConnectVariable("PFJetSmearedDownPt",PFJetSmearedDownPt,b_PFJetSmearedDownPt);
  ConnectVariable("PFJetSmearedUpEnergy",PFJetSmearedUpEnergy,b_PFJetSmearedUpEnergy);
  ConnectVariable("PFJetSmearedUpPt",PFJetSmearedUpPt,b_PFJetSmearedUpPt);
  ConnectVariable("PFJetL1FastJetJEC", PFJetL1FastJetJEC, b_PFJetL1FastJetJEC);
  ConnectVariable("PFJetL2L3ResJEC", PFJetL2L3ResJEC, b_PFJetL2L3ResJEC);
  ConnectVariable("PFJetL2RelJEC", PFJetL2RelJEC, b_PFJetL2RelJEC);
  ConnectVariable("PFJetL3AbsJEC", PFJetL3AbsJEC, b_PFJetL3AbsJEC);
  ConnectVariable("PFJetPtRaw", PFJetPtRaw, b_PFJetPtRaw);
  ConnectVariable("PFJetL2L3ResJEC", PFJetL2L3ResJEC, b_PFJetL2L3ResJEC); 
  ConnectVariable("PFJetL2RelJEC", PFJetL2RelJEC, b_PFJetL2RelJEC); 
  ConnectVariable("PFJetL3AbsJEC", PFJetL3AbsJEC, b_PFJetL3AbsJEC); 
  ConnectVariable("PFJetPtRaw", PFJetPtRaw, b_PFJetPtRaw);  
  
  //ConnectVariable("PFJetBeta", PFJetBeta); 
  //ConnectVariable("PFJetBetaClassic", PFJetBetaClassic);
  //ConnectVariable("PFJetBetaStar", PFJetBetaStar);
  //ConnectVariable("PFJetBetaStarClassic", PFJetBetaStarClassic);
  ConnectVariable("PFJetCombinedInclusiveSecondaryVertexBTag", PFJetCombinedInclusiveSecondaryVertexBTag, b_PFJetCombinedInclusiveSecondaryVertexBTag);
  ConnectVariable("PFJetCombinedMVABTag", PFJetCombinedMVABTag, b_PFJetCombinedMVABTag);
  ConnectVariable("PFJetCombinedSecondaryVertexMVABTag", PFJetCombinedSecondaryVertexMVABTag, b_PFJetCombinedSecondaryVertexMVABTag);
  ConnectVariable("PFJetSimpleSecondaryVertexHighEffBTag", PFJetSimpleSecondaryVertexHighEffBTag, b_PFJetSimpleSecondaryVertexHighEffBTag);
  ConnectVariable("PFJetSimpleSecondaryVertexHighPurBTag", PFJetSimpleSecondaryVertexHighPurBTag, b_PFJetSimpleSecondaryVertexHighPurBTag);
  ConnectVariable("PFJetSoftElectronByIP3dBTag", PFJetSoftElectronByIP3dBTag, b_PFJetSoftElectronByIP3dBTag);
  ConnectVariable("PFJetSoftElectronByPtBTag", PFJetSoftElectronByPtBTag, b_PFJetSoftElectronByPtBTag);
  ConnectVariable("PFJetTrackCountingHighEffBTag", PFJetTrackCountingHighEffBTag, b_PFJetTrackCountingHighEffBTag );  
  return;
}

void Data::ConnectCaloJets(){
  
  ConnectVariable("CaloJetEnergy", CaloJetEnergy, b_CaloJetEnergy);
  ConnectVariable("CaloJetEta", CaloJetEta, b_CaloJetEta);
  ConnectVariable("CaloJetPhi", CaloJetPhi, b_CaloJetPhi);
  ConnectVariable("CaloJetPt", CaloJetPt, b_CaloJetPt);
  ConnectVariable("CaloJetPassTightID", CaloJetPassTightID, b_CaloJetPassTightID);
  ConnectVariable("CaloJetPassLooseID", CaloJetPassLooseID, b_CaloJetPassLooseID);
  /* 
  <    vector<double>  *CaloJetEMF;
  <    vector<double>  *CaloJetEnergy;
  <    vector<double>  *CaloJetEnergyRaw;
  <    vector<double>  *CaloJetEta;
  <    vector<double>  *CaloJetHADF;
  <    vector<double>  *CaloJetJECUnc;
  <    vector<double>  *CaloJetJetBProbabilityBTag;
  <    vector<double>  *CaloJetJetProbabilityBTag;
  <    vector<double>  *CaloJetL1FastJetJEC;
  <    vector<double>  *CaloJetL2L3ResJEC;
  <    vector<double>  *CaloJetL2RelJEC;
  <    vector<double>  *CaloJetL3AbsJEC;
  <    vector<double>  *CaloJetPhi;
  <    vector<double>  *CaloJetPt;
  <    vector<double>  *CaloJetPtRaw;
  <    vector<double>  *CaloJetSigmaEta;
  <    vector<double>  *CaloJetSigmaPhi;
  <    vector<double>  *CaloJetSimpleSecondaryVertexHighEffBTag;
  <    vector<double>  *CaloJetSimpleSecondaryVertexHighPurBTag;
  <    vector<double>  *CaloJetTrackCountingHighEffBTag;
  <    vector<double>  *CaloJetTrackCountingHighPurBTag;
  <    vector<double>  *CaloJetfHPD;
  <    vector<double>  *CaloJetfRBX;
  <    vector<double>  *CaloJetresEMF;*/
  return;
}

void Data::ConnectMET(){

  //#####   MET branches
  ConnectVariable("CaloMET", CaloMET, b_CaloMET);
  ConnectVariable("CaloSumET", CaloSumET, b_CaloSumET);
  ConnectVariable("CaloMETPhiType1Cor", CaloMETPhiType1Cor, b_CaloMETPhiType1Cor);
  ConnectVariable("CaloMETPhiUncorrType1Cor", CaloMETPhiUncorrType1Cor, b_CaloMETPhiUncorrType1Cor);
  ConnectVariable("CaloMETType1Cor", CaloMETType1Cor, b_CaloMETType1Cor);
  ConnectVariable("CaloMETUncorrType1Cor", CaloMETUncorrType1Cor, b_CaloMETUncorrType1Cor);
  ConnectVariable("CaloSumETType1Cor", CaloSumETType1Cor, b_CaloSumETType1Cor);
  ConnectVariable("CaloSumETUncorrType1Cor", CaloSumETUncorrType1Cor, b_CaloSumETUncorrType1Cor);
  ConnectVariable("PFMETPhi", PFMETPhi, b_PFMETPhi);
  ConnectVariable("PFSumET", PFSumET, b_PFSumET);
  ConnectVariable("PFMETPhiType01Cor", PFMETPhiType01Cor, b_PFMETPhiType01Cor);
  ConnectVariable("PFMETType01Cor", PFMETType01Cor, b_PFMETType01Cor);
  ConnectVariable("PFSumETType01Cor", PFSumETType01Cor, b_PFSumETType01Cor);
  ConnectVariable("PFMETPhiType01XYCor", PFMETPhiType01XYCor, b_PFMETPhiType01XYCor);
  ConnectVariable("PFMETType01XYCor", PFMETType01XYCor, b_PFMETType01XYCor);
  ConnectVariable("PFSumETType01XYCor", PFSumETType01XYCor, b_PFSumETType01XYCor);
  ConnectVariable("PFMETPhiType1Cor", PFMETPhiType1Cor, b_PFMETPhiType1Cor);
  ConnectVariable("PFMETType1Cor", PFMETType1Cor, b_PFMETType1Cor);
  ConnectVariable("PFSumETType1Cor", PFSumETType1Cor, b_PFSumETType1Cor);


  /// New variables 2013/12/02
  ConnectVariable("PFMETType01XYCorElectronEnDown",PFMETType01XYCorElectronEnDown,b_PFMETType01XYCorElectronEnDown);
  ConnectVariable("PFMETType01XYCorElectronEnUp",PFMETType01XYCorElectronEnUp,b_PFMETType01XYCorElectronEnUp);
  ConnectVariable("PFMETType01XYCorJetEnDown",PFMETType01XYCorJetEnDown,b_PFMETType01XYCorJetEnDown);
  ConnectVariable("PFMETType01XYCorJetEnUp",PFMETType01XYCorJetEnUp,b_PFMETType01XYCorJetEnUp);
  ConnectVariable("PFMETType01XYCorJetResDown",PFMETType01XYCorJetResDown,b_PFMETType01XYCorJetResDown);
  ConnectVariable("PFMETType01XYCorJetResUp",PFMETType01XYCorJetResUp,b_PFMETType01XYCorJetResUp);
  ConnectVariable("PFMETType01XYCorMuonEnDown",PFMETType01XYCorMuonEnDown,b_PFMETType01XYCorMuonEnDown);
  ConnectVariable("PFMETType01XYCorMuonEnUp",PFMETType01XYCorMuonEnUp,b_PFMETType01XYCorMuonEnUp);
  ConnectVariable("PFMETType01XYCorUnclusteredDown",PFMETType01XYCorUnclusteredDown,b_PFMETType01XYCorUnclusteredDown);
  ConnectVariable("PFMETType01XYCorUnclusteredUp",PFMETType01XYCorUnclusteredUp,b_PFMETType01XYCorUnclusteredUp);

  return;
}

void Data::ConnectTruth(){

  //#####   Truth branches
  ConnectVariable("GenParticleEnergy", GenParticleEnergy, b_GenParticleEnergy);
  ConnectVariable("GenParticleEta", GenParticleEta, b_GenParticleEta);
  ConnectVariable("GenParticleP", GenParticleP, b_GenParticleP);
  ConnectVariable("GenParticlePhi", GenParticlePhi, b_GenParticlePhi);
  ConnectVariable("GenParticlePt", GenParticlePt, b_GenParticlePt);
  ConnectVariable("GenParticlePx", GenParticlePx, b_GenParticlePx);
  ConnectVariable("GenParticlePy", GenParticlePy, b_GenParticlePy);
  ConnectVariable("GenParticlePz", GenParticlePz, b_GenParticlePz);
  ConnectVariable("GenParticleMotherIndex", GenParticleMotherIndex, b_GenParticleMotherIndex);
  ConnectVariable("GenParticleNumDaught", GenParticleNumDaught, b_GenParticleNumDaught);
  ConnectVariable("GenParticlePdgId", GenParticlePdgId, b_GenParticlePdgId);
  ConnectVariable("GenParticleStatus", GenParticleStatus, b_GenParticleStatus);
  ConnectVariable("GenParticleTauDecayMode", GenParticleTauDecayMode, b_GenParticleTauDecayMode);
  

  ConnectVariable("GenZMuEnergy", GenZMuEnergy, b_GenZMuEnergy);
  ConnectVariable("GenZMuEta", GenZMuEta, b_GenZMuEta);
  ConnectVariable("GenZMuP", GenZMuP, b_GenZMuP);
  ConnectVariable("GenZMuPhi", GenZMuPhi, b_GenZMuPhi);
  ConnectVariable("GenZMuPt", GenZMuPt, b_GenZMuPt);
  ConnectVariable("GenZMuPx", GenZMuPx, b_GenZMuPx);
  ConnectVariable("GenZMuPy", GenZMuPy, b_GenZMuPy);
  ConnectVariable("GenZMuPz", GenZMuPz, b_GenZMuPz);
  ConnectVariable("GenZMuMotherIndex", GenZMuMotherIndex, b_GenZMuMotherIndex);                                                           
  ConnectVariable("GenZMuNumDaught", GenZMuNumDaught, b_GenZMuNumDaught);                                                                           
  ConnectVariable("GenZMuPdgId", GenZMuPdgId, b_GenZMuPdgId);                                                                                               
  ConnectVariable("GenZMuStatus", GenZMuStatus, b_GenZMuStatus);                                                                                         
  ConnectVariable("GenZMuTauDecayMode", GenZMuTauDecayMode, b_GenZMuTauDecayMode);

  ConnectVariable("GenZTauMotherIndex", GenZTauMotherIndex, b_GenZTauMotherIndex); 
  ConnectVariable("GenZTauNumDaught", GenZTauNumDaught, b_GenZTauNumDaught); 
  ConnectVariable("GenZTauPdgId", GenZTauPdgId, b_GenZTauPdgId); 
  ConnectVariable("GenZTauStatus", GenZTauStatus, b_GenZTauStatus);
  ConnectVariable("GenZTauTauDecayMode", GenZTauTauDecayMode, b_GenZTauTauDecayMode);
  ConnectVariable("GenZTauEnergy", GenZTauEnergy, b_GenZTauEnergy);
  ConnectVariable("GenZTauEta", GenZTauEta, b_GenZTauEta);
  ConnectVariable("GenZTauP", GenZTauP, b_GenZTauP);
  ConnectVariable("GenZTauPhi", GenZTauPhi, b_GenZTauPhi);
  ConnectVariable("GenZTauPt", GenZTauPt, b_GenZTauPt);
  ConnectVariable("GenZTauPx", GenZTauPx, b_GenZTauPx);
  ConnectVariable("GenZTauPy", GenZTauPy, b_GenZTauPy);
  ConnectVariable("GenZTauPz", GenZTauPz, b_GenZTauPz);

  ConnectVariable("GenZElectronMotherIndex", GenZElectronMotherIndex, b_GenZElectronMotherIndex);
  ConnectVariable("GenZElectronNumDaught", GenZElectronNumDaught, b_GenZElectronNumDaught);
  ConnectVariable("GenZElectronPdgId", GenZElectronPdgId, b_GenZElectronPdgId);
  ConnectVariable("GenZElectronStatus", GenZElectronStatus, b_GenZElectronStatus);
  ConnectVariable("GenZElectronTauDecayMode", GenZElectronTauDecayMode, b_GenZElectronTauDecayMode);
  ConnectVariable("GenZElectronEnergy", GenZElectronEnergy, b_GenZElectronEnergy);
  ConnectVariable("GenZElectronEta", GenZElectronEta, b_GenZElectronEta);
  ConnectVariable("GenZElectronP", GenZElectronP, b_GenZElectronP);
  ConnectVariable("GenZElectronPhi", GenZElectronPhi, b_GenZElectronPhi);
  ConnectVariable("GenZElectronPt", GenZElectronPt, b_GenZElectronPt);
  ConnectVariable("GenZElectronPx", GenZElectronPx, b_GenZElectronPx);
  ConnectVariable("GenZElectronPy", GenZElectronPy, b_GenZElectronPy);
  ConnectVariable("GenZElectronPz", GenZElectronPz, b_GenZElectronPz);
  
  ConnectVariable("GenJetEMF", GenJetEMF, b_GenJetEMF);
  ConnectVariable("GenJetEnergy", GenJetEnergy, b_GenJetEnergy);
  ConnectVariable("GenJetEta", GenJetEta, b_GenJetEta);
  ConnectVariable("GenJetHADF", GenJetHADF, b_GenJetHADF);
  ConnectVariable("GenJetP", GenJetP, b_GenJetP);
  ConnectVariable("GenJetPhi", GenJetPhi, b_GenJetPhi);
  ConnectVariable("GenJetPt", GenJetPt, b_GenJetPt);


  ConnectVariable("GenMETCalo", GenMETCalo, b_GenMETCalo);
  ConnectVariable("GenMETPhiCalo", GenMETPhiCalo, b_GenMETPhiCalo);
  ConnectVariable("GenSumETCalo", GenSumETCalo, b_GenSumETCalo);
  ConnectVariable("GenMETPhiTrue", GenMETPhiTrue, b_GenMETPhiTrue);
  ConnectVariable("GenMETTrue", GenMETTrue, b_GenMETTrue);
  ConnectVariable("GenSumETTrue", GenSumETTrue, b_GenSumETTrue);
  return;
}


void Data::ConnectAllBranches(){

  ///#############################################################################                                                                                              
  //   These are variabels not currenly set: or read: BUT are in ntuples                                                                                                        
  //##############################################################################    
  /*
  /// Trigger
  ConnectVariable("HLTKey", HLTKey);
  ConnectVariable("HLTOutsideDatasetTriggerNames", HLTOutsideDatasetTriggerNames);
  ConnectVariable("HLTFilterName", HLTFilterName);

  ConnectVariable("MuonHLTSingleIsoMuonMatchEta", MuonHLTSingleIsoMuonMatchEta, b_MuonHLTSingleIsoMuonMatchEta);
  ConnectVariable("MuonHLTSingleIsoMuonMatchPhi", MuonHLTSingleIsoMuonMatchPhi, b_MuonHLTSingleIsoMuonMatchPhi);
  ConnectVariable("MuonHLTSingleIsoMuonMatchPt", MuonHLTSingleIsoMuonMatchPt, b_MuonHLTSingleIsoMuonMatchPt);
  ConnectVariable("MuonHLTSingleMuonMatchEta", MuonHLTSingleMuonMatchEta, b_MuonHLTSingleMuonMatchEta);
  ConnectVariable("MuonHLTSingleMuonMatchPhi", MuonHLTSingleMuonMatchPhi, b_MuonHLTSingleMuonMatchPhi);
  ConnectVariable("MuonHLTSingleMuonMatchPt", MuonHLTSingleMuonMatchPt, b_MuonHLTSingleMuonMatchPt);

  /// Event
  ConnectVariable("isBPTX0", isBPTX0);
  ConnectVariable("isBSCBeamHalo", isBSCBeamHalo);
  ConnectVariable("isBSCMinBias", isBSCMinBias);
  ConnectVariable("isBeamScraping", isBeamScraping);
  
  ConnectVariable("passCaloBoundaryDRFilter", passCaloBoundaryDRFilter);
  ConnectVariable("passEcalMaskedCellDRFilter", passEcalMaskedCellDRFilter);
  ConnectVariable("passLogErrorTooManyClusters", passLogErrorTooManyClusters);
  ConnectVariable("passManyStripClus53X", passManyStripClus53X);
  ConnectVariable("passTooManyStripClus53X", passTooManyStripClus53X);
  ConnectVariable("hasVeryForwardPFMuon", hasVeryForwardPFMuon);
  ConnectVariable("hasJetWithBadUnc", hasJetWithBadUnc);

      
  /// Others
  ConnectVariable("PhotonHasMatchedConvPhot", PhotonHasMatchedConvPhot);
  ConnectVariable("PhotonHasMatchedPromptEle", PhotonHasMatchedPromptEle);
  ConnectVariable("PhotonHasPixelSeed", PhotonHasPixelSeed);
  ConnectVariable("PhotonIsEBEEGap", PhotonIsEBEEGap);
  ConnectVariable("PhotonIsEBGap", PhotonIsEBGap);
  ConnectVariable("PhotonIsEEGap", PhotonIsEEGap);
  ConnectVariable("HLTOutsideDatasetTriggerDecisions", HLTOutsideDatasetTriggerDecisions);
  ConnectVariable("rhoForHEEP", rhoForHEEP);
  ConnectVariable("rhoJetsCCPU", rhoJetsCCPU);
  ConnectVariable("rhoJetsCN", rhoJetsCN);
  ConnectVariable("rhoJetsCNT", rhoJetsCNT);
  ConnectVariable("time", time);
  ConnectVariable("PtHat", PtHat);


  /// Electron                                                                                                                                                                  
  ConnectVariable("ElectronHLTDoubleEleMatchEta", ElectronHLTDoubleEleMatchEta);
  ConnectVariable("ElectronHLTDoubleEleMatchPhi", ElectronHLTDoubleEleMatchPhi);
  ConnectVariable("ElectronHLTDoubleEleMatchPt", ElectronHLTDoubleEleMatchPt);
  ConnectVariable("ElectronHLTSingleEleMatchEta", ElectronHLTSingleEleMatchEta);
  ConnectVariable("ElectronHLTSingleEleMatchPhi", ElectronHLTSingleEleMatchPhi);
  ConnectVariable("ElectronHLTSingleEleMatchPt", ElectronHLTSingleEleMatchPt);
  ConnectVariable("ElectronHLTSingleEleWP80MatchEta", ElectronHLTSingleEleWP80MatchEta);
  ConnectVariable("ElectronHLTSingleEleWP80MatchPhi", ElectronHLTSingleEleWP80MatchPhi);
  ConnectVariable("ElectronHLTSingleEleWP80MatchPt", ElectronHLTSingleEleWP80MatchPt);
  ConnectVariable("ElectronHcalIsoD1DR03", ElectronHcalIsoD1DR03);
  ConnectVariable("ElectronHcalIsoD2DR03", ElectronHcalIsoD2DR03);
  ConnectVariable("ElectronHcalIsoDR03FullCone", ElectronHcalIsoDR03FullCone);
  ConnectVariable("ElectronPtHeep", ElectronPtHeep);
  ConnectVariable("ElectronRelIsoPAT", ElectronRelIsoPAT);
  
  // Truth
  ConnectVariable("GenWElectronEnergy", GenWElectronEnergy);
  ConnectVariable("GenWElectronEta", GenWElectronEta);
  ConnectVariable("GenWElectronP", GenWElectronP);
  ConnectVariable("GenWElectronPhi", GenWElectronPhi);
  ConnectVariable("GenWElectronPt", GenWElectronPt);
  ConnectVariable("GenWElectronPx", GenWElectronPx);
  ConnectVariable("GenWElectronPy", GenWElectronPy);
  ConnectVariable("GenWElectronPz", GenWElectronPz);
  ConnectVariable("GenWElectronTauVisibleEta", GenWElectronTauVisibleEta);
  ConnectVariable("GenWElectronTauVisiblePhi", GenWElectronTauVisiblePhi);
  ConnectVariable("GenWElectronTauVisiblePt", GenWElectronTauVisiblePt);
  ConnectVariable("GenWElectronVX", GenWElectronVX);
  ConnectVariable("GenWElectronVY", GenWElectronVY);
  ConnectVariable("GenWElectronVZ", GenWElectronVZ);
  ConnectVariable("GenZElectronEnergy", GenZElectronEnergy);
  ConnectVariable("GenZElectronEta", GenZElectronEta);
  ConnectVariable("GenZElectronP", GenZElectronP);
  ConnectVariable("GenZElectronPhi", GenZElectronPhi);
  ConnectVariable("GenZElectronPt", GenZElectronPt);
  ConnectVariable("GenZElectronPx", GenZElectronPx);
  ConnectVariable("GenZElectronPy", GenZElectronPy);
  ConnectVariable("GenZElectronPz", GenZElectronPz);
  ConnectVariable("GenZElectronTauVisibleEta", GenZElectronTauVisibleEta);
  ConnectVariable("GenZElectronTauVisiblePhi", GenZElectronTauVisiblePhi);
  ConnectVariable("GenZElectronTauVisiblePt", GenZElectronTauVisiblePt);
  ConnectVariable("GenZElectronVX", GenZElectronVX);
  ConnectVariable("GenZElectronVY", GenZElectronVY);
  ConnectVariable("GenZElectronVZ", GenZElectronVZ);


  ConnectVariable("GenWMuEnergy", GenWMuEnergy);
  ConnectVariable("GenWMuEta", GenWMuEta);
  ConnectVariable("GenWMuP", GenWMuP);
  ConnectVariable("GenWMuPhi", GenWMuPhi);
  ConnectVariable("GenWMuPt", GenWMuPt);
  ConnectVariable("GenWMuPx", GenWMuPx);
  ConnectVariable("GenWMuPy", GenWMuPy);
  ConnectVariable("GenWMuPz", GenWMuPz);
  ConnectVariable("GenWMuTauVisibleEta", GenWMuTauVisibleEta);
  ConnectVariable("GenWMuTauVisiblePhi", GenWMuTauVisiblePhi);
  ConnectVariable("GenWMuTauVisiblePt", GenWMuTauVisiblePt);
  ConnectVariable("GenWMuVX", GenWMuVX);
  ConnectVariable("GenWMuVY", GenWMuVY);
  ConnectVariable("GenWMuVZ", GenWMuVZ);
  ConnectVariable("GenZMuEnergy", GenZMuEnergy);
  ConnectVariable("GenZMuEta", GenZMuEta);
  ConnectVariable("GenZMuP", GenZMuP);
  ConnectVariable("GenZMuPhi", GenZMuPhi);
  ConnectVariable("GenZMuPt", GenZMuPt);
  ConnectVariable("GenZMuPx", GenZMuPx);
  ConnectVariable("GenZMuPy", GenZMuPy);
  ConnectVariable("GenZMuPz", GenZMuPz);
  ConnectVariable("GenZMuTauVisibleEta", GenZMuTauVisibleEta);
  ConnectVariable("GenZMuTauVisiblePhi", GenZMuTauVisiblePhi);
  ConnectVariable("GenZMuTauVisiblePt", GenZMuTauVisiblePt);
  ConnectVariable("GenZMuVX", GenZMuVX);
  ConnectVariable("GenZMuVY", GenZMuVY);
  ConnectVariable("GenZMuVZ", GenZMuVZ);
  ConnectVariable("GenParticleTauVisibleEta", GenParticleTauVisibleEta);
  ConnectVariable("GenParticleTauVisiblePhi", GenParticleTauVisiblePhi);
  ConnectVariable("GenParticleTauVisiblePt", GenParticleTauVisiblePt);
  ConnectVariable("GenParticleVX", GenParticleVX);
  ConnectVariable("GenParticleVY", GenParticleVY);
  ConnectVariable("GenParticleVZ", GenParticleVZ);
  ConnectVariable("GenWTauEnergy", GenWTauEnergy);
  ConnectVariable("GenWTauEta", GenWTauEta);
  ConnectVariable("GenWTauP", GenWTauP);
  ConnectVariable("GenWTauPhi", GenWTauPhi);
  ConnectVariable("GenWTauPt", GenWTauPt);
  ConnectVariable("GenWTauPx", GenWTauPx);
  ConnectVariable("GenWTauPy", GenWTauPy);
  ConnectVariable("GenWTauPz", GenWTauPz);
  ConnectVariable("GenWTauTauVisibleEta", GenWTauTauVisibleEta);
  ConnectVariable("GenWTauTauVisiblePhi", GenWTauTauVisiblePhi);
  ConnectVariable("GenWTauTauVisiblePt", GenWTauTauVisiblePt);
  ConnectVariable("GenWTauVX", GenWTauVX);
  ConnectVariable("GenWTauVY", GenWTauVY);
  ConnectVariable("GenWTauVZ", GenWTauVZ);
  ConnectVariable("GenZTauEnergy", GenZTauEnergy);
  ConnectVariable("GenZTauEta", GenZTauEta);
  ConnectVariable("GenZTauP", GenZTauP);
  ConnectVariable("GenZTauPhi", GenZTauPhi);
  ConnectVariable("GenZTauPt", GenZTauPt);
  ConnectVariable("GenZTauPx", GenZTauPx);
  ConnectVariable("GenZTauPy", GenZTauPy);
  ConnectVariable("GenZTauPz", GenZTauPz);
  ConnectVariable("GenZTauTauVisibleEta", GenZTauTauVisibleEta);
  ConnectVariable("GenZTauTauVisiblePhi", GenZTauTauVisiblePhi);
  ConnectVariable("GenZTauTauVisiblePt", GenZTauTauVisiblePt);
  ConnectVariable("GenZTauVX", GenZTauVX);
  ConnectVariable("GenZTauVY", GenZTauVY);
  ConnectVariable("GenZTauVZ", GenZTauVZ);
  
  // Tau
  ConnectVariable("HPSTauAgainstElectronDeadECALDiscr", HPSTauAgainstElectronDeadECALDiscr);
  ConnectVariable("HPSTauAgainstElectronLooseDiscr", HPSTauAgainstElectronLooseDiscr);
  ConnectVariable("HPSTauAgainstElectronLooseMVA2Discr", HPSTauAgainstElectronLooseMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronLooseMVA3Discr", HPSTauAgainstElectronLooseMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronMVA2categoryDiscr", HPSTauAgainstElectronMVA2categoryDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA2rawDiscr", HPSTauAgainstElectronMVA2rawDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA3categoryDiscr", HPSTauAgainstElectronMVA3categoryDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA3rawDiscr", HPSTauAgainstElectronMVA3rawDiscr);
  ConnectVariable("HPSTauAgainstElectronMVADiscr", HPSTauAgainstElectronMVADiscr);
  ConnectVariable("HPSTauAgainstElectronMediumDiscr", HPSTauAgainstElectronMediumDiscr);
  ConnectVariable("HPSTauAgainstElectronMediumMVA2Discr", HPSTauAgainstElectronMediumMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronMediumMVA3Discr", HPSTauAgainstElectronMediumMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronTightDiscr", HPSTauAgainstElectronTightDiscr);
  ConnectVariable("HPSTauAgainstElectronTightMVA2Discr", HPSTauAgainstElectronTightMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronTightMVA3Discr", HPSTauAgainstElectronTightMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronVLooseMVA2Discr", HPSTauAgainstElectronVLooseMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronVTightMVA3Discr", HPSTauAgainstElectronVTightMVA3Discr);
  ConnectVariable("HPSTauAgainstMuonLoose2Discr", HPSTauAgainstMuonLoose2Discr);
  ConnectVariable("HPSTauAgainstMuonLooseDiscr", HPSTauAgainstMuonLooseDiscr);
  ConnectVariable("HPSTauAgainstMuonMedium2Discr", HPSTauAgainstMuonMedium2Discr);
  ConnectVariable("HPSTauAgainstMuonMediumDiscr", HPSTauAgainstMuonMediumDiscr);
  ConnectVariable("HPSTauAgainstMuonTight2Discr", HPSTauAgainstMuonTight2Discr);
  ConnectVariable("HPSTauAgainstMuonTightDiscr", HPSTauAgainstMuonTightDiscr);
  ConnectVariable("HPSTauBremsRecoveryEOverPLead", HPSTauBremsRecoveryEOverPLead);
  ConnectVariable("HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauDecayModeFindingDiscr", HPSTauDecayModeFindingDiscr);
  ConnectVariable("HPSTauEcalStripSumEOverPLead", HPSTauEcalStripSumEOverPLead);
  ConnectVariable("HPSTauEmFraction", HPSTauEmFraction);
  ConnectVariable("HPSTauEtaLeadCharged", HPSTauEtaLeadCharged);
  ConnectVariable("HPSTauEtaetaMoment", HPSTauEtaetaMoment);
  ConnectVariable("HPSTauEtaphiMoment", HPSTauEtaphiMoment);
  ConnectVariable("HPSTauHcal3x3OverPLead", HPSTauHcal3x3OverPLead);
  ConnectVariable("HPSTauHcalMaxOverPLead", HPSTauHcalMaxOverPLead);
  ConnectVariable("HPSTauHcalTotOverPLead", HPSTauHcalTotOverPLead);
  ConnectVariable("HPSTauIsolationMVArawDiscr", HPSTauIsolationMVArawDiscr);
  ConnectVariable("HPSTauIsolationPFChargedHadrCandsPtSum", HPSTauIsolationPFChargedHadrCandsPtSum);
  ConnectVariable("HPSTauIsolationPFGammaCandsEtSum", HPSTauIsolationPFGammaCandsEtSum);
  ConnectVariable("HPSTauLeadPFChargedHadrCandsignedSipt", HPSTauLeadPFChargedHadrCandsignedSipt);
  ConnectVariable("HPSTauLeadVtxDistXY", HPSTauLeadVtxDistXY);
  ConnectVariable("HPSTauLeadVtxDistZ", HPSTauLeadVtxDistZ);
  ConnectVariable("HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr", HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauLooseIsolationDeltaBetaCorrDiscr", HPSTauLooseIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauLooseIsolationDiscr", HPSTauLooseIsolationDiscr);
  ConnectVariable("HPSTauLooseIsolationMVA2Discr", HPSTauLooseIsolationMVA2Discr);
  ConnectVariable("HPSTauLooseIsolationMVADiscr", HPSTauLooseIsolationMVADiscr);
  ConnectVariable("HPSTauMatchedGenJetEta", HPSTauMatchedGenJetEta);
  ConnectVariable("HPSTauMatchedGenJetPhi", HPSTauMatchedGenJetPhi);
  ConnectVariable("HPSTauMatchedGenJetPt", HPSTauMatchedGenJetPt);
  ConnectVariable("HPSTauMatchedGenParticleEta", HPSTauMatchedGenParticleEta);
  ConnectVariable("HPSTauMatchedGenParticlePhi", HPSTauMatchedGenParticlePhi);
  ConnectVariable("HPSTauMatchedGenParticlePt", HPSTauMatchedGenParticlePt);
  ConnectVariable("HPSTauMaximumHCALPFClusterEt", HPSTauMaximumHCALPFClusterEt);
  ConnectVariable("HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr", HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauMediumIsolationDeltaBetaCorrDiscr", HPSTauMediumIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauMediumIsolationDiscr", HPSTauMediumIsolationDiscr);
  ConnectVariable("HPSTauMediumIsolationMVA2Discr", HPSTauMediumIsolationMVA2Discr);
  ConnectVariable("HPSTauMediumIsolationMVADiscr", HPSTauMediumIsolationMVADiscr);
  ConnectVariable("HPSTauPhiLeadCharged", HPSTauPhiLeadCharged);
  ConnectVariable("HPSTauPhiphiMoment", HPSTauPhiphiMoment);  ConnectVariable("HPSTauPtLeadCharged", HPSTauPtLeadCharged);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsCount", HPSTauSignalPFChargedHadrCandsCount);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsEta", HPSTauSignalPFChargedHadrCandsEta);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsPhi", HPSTauSignalPFChargedHadrCandsPhi);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsPt", HPSTauSignalPFChargedHadrCandsPt);
  ConnectVariable("HPSTauSignalPFGammaCandsCount", HPSTauSignalPFGammaCandsCount);
  ConnectVariable("HPSTauSignalPFGammaCandsEta", HPSTauSignalPFGammaCandsEta);
  ConnectVariable("HPSTauSignalPFGammaCandsPhi", HPSTauSignalPFGammaCandsPhi);
  ConnectVariable("HPSTauSignalPFGammaCandsPt", HPSTauSignalPFGammaCandsPt);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsCount", HPSTauSignalPFNeutrHadrCandsCount);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsEta", HPSTauSignalPFNeutrHadrCandsEta);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsPhi", HPSTauSignalPFNeutrHadrCandsPhi);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsPt", HPSTauSignalPFNeutrHadrCandsPt);
  ConnectVariable("HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauTightCombinedIsolationDeltaBetaCorrDiscr", HPSTauTightCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauTightIsolationDeltaBetaCorrDiscr", HPSTauTightIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauTightIsolationDiscr", HPSTauTightIsolationDiscr);
  ConnectVariable("HPSTauTightIsolationMVA2Discr", HPSTauTightIsolationMVA2Discr);
  ConnectVariable("HPSTauTightIsolationMVADiscr", HPSTauTightIsolationMVADiscr);
  ConnectVariable("HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr", HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauVLooseIsolationDeltaBetaCorrDiscr", HPSTauVLooseIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauVLooseIsolationDiscr", HPSTauVLooseIsolationDiscr);
  ConnectVariable("HPSTauVtxDistXY", HPSTauVtxDistXY);
  ConnectVariable("HPSTauVtxDistZ", HPSTauVtxDistZ);
  
  // Muon

  ConnectVariable("MuonCocktailCharge", MuonCocktailCharge);
  ConnectVariable("MuonCocktailRefitID", MuonCocktailRefitID);
  ConnectVariable("MuonCocktailTrkHits", MuonCocktailTrkHits);  
  ConnectVariable("MuonBackToBackCompatibility", MuonBackToBackCompatibility);
  ConnectVariable("MuonBeamSpotDXY", MuonBeamSpotDXY);
  ConnectVariable("MuonBeamSpotDXYError", MuonBeamSpotDXYError);
  ConnectVariable("MuonBestTrackVtxDistXY", MuonBestTrackVtxDistXY);
  ConnectVariable("MuonBestTrackVtxDistZ", MuonBestTrackVtxDistZ);
  ConnectVariable("MuonCocktailEta", MuonCocktailEta);
  ConnectVariable("MuonCocktailEtaError", MuonCocktailEtaError);
  ConnectVariable("MuonCocktailGlobalChi2", MuonCocktailGlobalChi2);
  ConnectVariable("MuonCocktailP", MuonCocktailP);
  ConnectVariable("MuonCocktailPhi", MuonCocktailPhi);
  ConnectVariable("MuonCocktailPhiError", MuonCocktailPhiError);
  ConnectVariable("MuonCocktailPt", MuonCocktailPt);
  ConnectVariable("MuonCocktailPtError", MuonCocktailPtError);
  ConnectVariable("MuonCocktailQOverPError", MuonCocktailQOverPError);
  ConnectVariable("MuonCocktailTrkD0", MuonCocktailTrkD0);
  ConnectVariable("MuonCocktailTrkD0Error", MuonCocktailTrkD0Error);
  ConnectVariable("MuonCocktailTrkDz", MuonCocktailTrkDz);
  ConnectVariable("MuonCocktailTrkDzError", MuonCocktailTrkDzError);
  ConnectVariable("MuonCocktailTrkValidFractionOfHits", MuonCocktailTrkValidFractionOfHits);
  ConnectVariable("MuonCosmicCompatibility", MuonCosmicCompatibility);
  
  // PF
  ConnectVariable("PFCandEnergyLeptLink", PFCandEnergyLeptLink);
  ConnectVariable("PFCandEtaLeptLink", PFCandEtaLeptLink);
  ConnectVariable("PFCandPhiLeptLink", PFCandPhiLeptLink);
  ConnectVariable("PFCandPtLeptLink", PFCandPtLeptLink);

  ConnectVariable("PFJetBeta", PFJetBeta);
  ConnectVariable("PFJetBetaClassic", PFJetBetaClassic);
  ConnectVariable("PFJetBetaStar", PFJetBetaStar);
  ConnectVariable("PFJetBetaStarClassic", PFJetBetaStarClassic);
  ConnectVariable("PFJetCombinedInclusiveSecondaryVertexBTag", PFJetCombinedInclusiveSecondaryVertexBTag);
  ConnectVariable("PFJetCombinedMVABTag", PFJetCombinedMVABTag);
  ConnectVariable("PFJetCombinedSecondaryVertexMVABTag", PFJetCombinedSecondaryVertexMVABTag);
  ConnectVariable("PFJetSimpleSecondaryVertexHighEffBTag", PFJetSimpleSecondaryVertexHighEffBTag);
  ConnectVariable("PFJetSimpleSecondaryVertexHighPurBTag", PFJetSimpleSecondaryVertexHighPurBTag);
  ConnectVariable("PFJetSoftElectronByIP3dBTag", PFJetSoftElectronByIP3dBTag);
  ConnectVariable("PFJetSoftElectronByPtBTag", PFJetSoftElectronByPtBTag);
  ConnectVariable("PFJetTrackCountingHighEffBTag", PFJetTrackCountingHighEffBTag);


  /// Photon
  ConnectVariable("PhotonAlpha", PhotonAlpha);
  ConnectVariable("PhotonChi2ConvPhot", PhotonChi2ConvPhot);
  ConnectVariable("PhotonDPhiTracksAtVtxConvPhot", PhotonDPhiTracksAtVtxConvPhot);
  ConnectVariable("PhotonDistOfMinApproachConvPhot", PhotonDistOfMinApproachConvPhot);
  ConnectVariable("PhotonE2OverE9", PhotonE2OverE9);
  ConnectVariable("PhotonE3x3", PhotonE3x3);
  ConnectVariable("PhotonE4SwissCross", PhotonE4SwissCross);
  ConnectVariable("PhotonE5x5", PhotonE5x5);
  ConnectVariable("PhotonEOverPConvPhot", PhotonEOverPConvPhot);
  ConnectVariable("PhotonEcalIsoDR03", PhotonEcalIsoDR03);
  ConnectVariable("PhotonEcalIsoDR04", PhotonEcalIsoDR04);
  ConnectVariable("PhotonEnergy", PhotonEnergy);
  ConnectVariable("PhotonEta", PhotonEta);
  ConnectVariable("PhotonHcalIsoDR03", PhotonHcalIsoDR03);
  ConnectVariable("PhotonHcalIsoDR03FullCone", PhotonHcalIsoDR03FullCone);
  ConnectVariable("PhotonHcalIsoDR04", PhotonHcalIsoDR04);
  ConnectVariable("PhotonHcalIsoDR04FullCone", PhotonHcalIsoDR04FullCone);
  ConnectVariable("PhotonHoE", PhotonHoE);
  ConnectVariable("PhotonNDofConvPhot", PhotonNDofConvPhot);
  ConnectVariable("PhotonPairCotThetaSeparationConvPhot", PhotonPairCotThetaSeparationConvPhot);
  ConnectVariable("PhotonPairInvariantMassConvPhot", PhotonPairInvariantMassConvPhot);
  ConnectVariable("PhotonPairMomentumxConvPhot", PhotonPairMomentumxConvPhot);
  ConnectVariable("PhotonPairMomentumyConvPhot", PhotonPairMomentumyConvPhot);
  ConnectVariable("PhotonPairMomentumzConvPhot", PhotonPairMomentumzConvPhot);
  ConnectVariable("PhotonPhi", PhotonPhi);
  ConnectVariable("PhotonPt", PhotonPt);
  ConnectVariable("PhotonSCenergy", PhotonSCenergy);
  ConnectVariable("PhotonSCeta", PhotonSCeta);
  ConnectVariable("PhotonSCphi", PhotonSCphi);
  ConnectVariable("PhotonSCseedEnergy", PhotonSCseedEnergy);
  ConnectVariable("PhotonSEtaEta", PhotonSEtaEta);
  ConnectVariable("PhotonSEtaPhi", PhotonSEtaPhi);
  ConnectVariable("PhotonSMajMaj", PhotonSMajMaj);
  ConnectVariable("PhotonSMinMin", PhotonSMinMin);
  ConnectVariable("PhotonSPhiPhi", PhotonSPhiPhi);
  ConnectVariable("PhotonSigmaIEtaIEta", PhotonSigmaIEtaIEta);
  ConnectVariable("PhotonTimeSeed", PhotonTimeSeed);
  ConnectVariable("PhotonTrkIsoHollowDR03", PhotonTrkIsoHollowDR03);
  ConnectVariable("PhotonTrkIsoHollowDR04", PhotonTrkIsoHollowDR04);
  ConnectVariable("PhotonTrkIsoSolidDR03", PhotonTrkIsoSolidDR03);
  ConnectVariable("PhotonTrkIsoSolidDR04", PhotonTrkIsoSolidDR04);
  ConnectVariable("PhotonXVtxConvPhot", PhotonXVtxConvPhot);
  ConnectVariable("PhotonYVtxConvPhot", PhotonYVtxConvPhot);
  ConnectVariable("PhotonZVtxConvPhot", PhotonZVtxConvPhot);
  ConnectVariable("PhotonNTracksConvPhot", PhotonNTracksConvPhot);
  
  
  // Trigger
  ConnectVariable("HLTFilterObjEta", HLTFilterObjEta);
  ConnectVariable("HLTFilterObjPhi", HLTFilterObjPhi);
  ConnectVariable("HLTFilterObjPt", HLTFilterObjPt);
    
  
  // Truth
  
  ConnectVariable("GenWElectronMotherIndex", GenWElectronMotherIndex);
  ConnectVariable("GenWElectronNumDaught", GenWElectronNumDaught);
  ConnectVariable("GenWElectronPdgId", GenWElectronPdgId);
  ConnectVariable("GenWElectronStatus", GenWElectronStatus);
  ConnectVariable("GenWElectronTauDecayMode", GenWElectronTauDecayMode);
  ConnectVariable("GenZElectronMotherIndex", GenZElectronMotherIndex);
  ConnectVariable("GenZElectronNumDaught", GenZElectronNumDaught);  ConnectVariable("GenZElectronPdgId", GenZElectronPdgId);
  ConnectVariable("GenZElectronStatus", GenZElectronStatus);
  ConnectVariable("GenZElectronTauDecayMode", GenZElectronTauDecayMode);
  ConnectVariable("GenWMuMotherIndex", GenWMuMotherIndex);
  ConnectVariable("GenWMuNumDaught", GenWMuNumDaught);
  ConnectVariable("GenWMuPdgId", GenWMuPdgId);
  ConnectVariable("GenWMuStatus", GenWMuStatus);
  ConnectVariable("GenWMuTauDecayMode", GenWMuTauDecayMode);
  ConnectVariable("GenZMuMotherIndex", GenZMuMotherIndex);
  ConnectVariable("GenZMuNumDaught", GenZMuNumDaught);
  ConnectVariable("GenZMuPdgId", GenZMuPdgId);
  ConnectVariable("GenZMuStatus", GenZMuStatus);
  ConnectVariable("GenZMuTauDecayMode", GenZMuTauDecayMode);
  ConnectVariable("GenWTauMotherIndex", GenWTauMotherIndex);
  ConnectVariable("GenWTauNumDaught", GenWTauNumDaught);  ConnectVariable("GenWTauPdgId", GenWTauPdgId);
  ConnectVariable("GenWTauStatus", GenWTauStatus);
  ConnectVariable("GenWTauTauDecayMode", GenWTauTauDecayMode);
  ConnectVariable("GenZTauMotherIndex", GenZTauMotherIndex);
  ConnectVariable("GenZTauNumDaught", GenZTauNumDaught);
  ConnectVariable("GenZTauPdgId", GenZTauPdgId);
  ConnectVariable("GenZTauStatus", GenZTauStatus);
  ConnectVariable("GenZTauTauDecayMode", GenZTauTauDecayMode);
  ConnectVariable("HPSTauDecayMode", HPSTauDecayMode);
  ConnectVariable("HPSTauIsCaloTau", HPSTauIsCaloTau);
  ConnectVariable("HPSTauVtxIndex", HPSTauVtxIndex);

  
  // Event
  ConnectVariable("PFMET", PFMET);
  ConnectVariable("TCMET", TCMET);  
  ConnectVariable("TCMETPhi", TCMETPhi); 
  ConnectVariable("TCSumET", TCSumET); 
  ConnectVariable("PileUpInteractions", PileUpInteractions);                                                                                               
  ConnectVariable("PileUpOriginBX", PileUpOriginBX);     
  ConnectVariable("L1PhysBits", L1PhysBits);
  ConnectVariable("L1TechBits", L1TechBits);
  ConnectVariable("VertexNTracksW05", VertexNTracksW05);
  ConnectVariable("HLTFilterObjId", HLTFilterObjId);
  ConnectVariable("bunch", bunch);
  ConnectVariable("ls", ls);
  ConnectVariable("orbit", orbit);
  ConnectVariable("ProcessID", ProcessID);
  */

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
