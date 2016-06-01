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

Data::Data() : LQCycleBaseNTuple(), LQinput(true), k_inputmuons(0),  k_inputelectrons(0),  k_inputjets(0), k_inputgenjets(0),k_inputevent(0),k_inputtrigger(0),k_inputtruth(0)
  
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
   

   ///m_logger << INFO <<  fChain->LoadTree(entry) << LQLogger::endmsg;
   //m_logger << INFO << "Entry " << entry << " " << fChain->GetTree()->GetEntries() << LQLogger::endmsg; 
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;

   if (!fChain->InheritsFrom(TChain::Class()))  {
     return centry;
   }
   
   TChain *chain = (TChain*)fChain;
   //m_logger << INFO << chain->GetTreeNumber() << " " << fCurrent << LQLogger::endmsg;
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
  HLTFilterName = 0;
  passHcalLaserEventFilter=0;
  ElectronLooseshiftedEup=0;
  ElectronLooseshiftedEdown=0;
  ElectronLooseshiftedExup=0;
  ElectronLooseshiftedExdown=0;
  ElectronLooseshiftedEyup=0;
  ElectronLooseshiftedEydown=0;
  ElectronLooseGsfCtfCharge = 0;
  ElectronLooseGsfCtfScPixCharge = 0;
  ElectronLooseGsfScPixCharge = 0;
  ElectronLooseHLTDoubleEleMatched = 0;
  ElectronLooseHLTSingleEleMatched = 0;
  ElectronLooseHLTSingleEleMatched8 = 0;
  ElectronLooseHLTSingleEleMatched17 = 0;
  ElectronLooseHLTSingleEleWP80Matched = 0;
  ElectronLooseHLTEMuMatched8 = 0;
  ElectronLooseHLTEMuMatched17 = 0;
  ElectronLooseHasEcalDrivenSeed = 0;
  ElectronLooseHasMatchedConvPhot = 0;
  ElectronLooseHasTrackerDrivenSeed = 0;
  ElectronLooseIsEB = 0;
  ElectronLooseIsEE = 0;
  MuonLooseshiftedEup=0;
  MuonLooseshiftedEdown=0;
  MuonLooseshiftedExup=0;
  MuonLooseshiftedExdown=0;
  MuonLooseshiftedEyup=0;
  MuonLooseshiftedEydown=0;
  MuonLooseHLTSingleIsoMuonMatched = 0;
  MuonLooseHLTSingleMuonMatched = 0;
  MuonLooseHLTSingleMuonMatched5 = 0;
  MuonLooseHLTSingleMuonMatched8 = 0;
  MuonLooseHLTSingleMuonMatched12 = 0;
  MuonLooseHLTSingleMuonMatched17= 0;
  MuonLooseHLTSingleMuonMatched24 = 0;
  MuonLooseHLTDoubleMuonMatched = 0;
  MuonLooseHLTEMuMatched8 = 0;
  MuonLooseHLTEMuMatched17 = 0;
  PFJetPileupjetIDpassLooseWP = 0;
  PFJetPileupjetIDpassMediumWP = 0;
  PFJetPileupjetIDpassTightWP = 0;

   PhotonHasMatchedConvPhot = 0;
   PhotonHasMatchedPromptEle = 0;
   PhotonHasPixelSeed = 0;
   PhotonIsEBEEGap = 0;
   PhotonIsEBGap = 0;
   PhotonIsEEGap = 0;
   HLTInsideDatasetTriggerDecisions = 0;
   HLTOutsideDatasetTriggerDecisions = 0;
   VertexIsFake = 0;
   CaloJetEnergy = 0;
   CaloJetEta = 0;
   CaloJetPhi = 0;
   CaloJetPt = 0;

   CaloMET = 0;
   CaloMETPhi = 0;
   CaloSumET = 0;
   CaloMETPhiType1Cor = 0;
   CaloMETPhiUncorrType1Cor = 0;
   CaloMETType1Cor = 0;
   CaloMETUncorrType1Cor = 0;
   CaloSumETType1Cor = 0;
   CaloSumETUncorrType1Cor = 0;
   ElectronLooseBeamSpotDXY = 0;
   ElectronLooseBeamSpotDXYError = 0;
   ElectronLooseCaloEnergy = 0;
   ElectronLooseConvFitProb = 0;
   ElectronLooseDCotTheta = 0;
   ElectronLooseDeltaEtaTrkSC = 0;
   ElectronLooseDeltaPhiTrkSC = 0;
   ElectronLooseDist = 0;
   ElectronLooseE1x5OverE5x5 = 0;
   ElectronLooseE2x5OverE5x5 = 0;
   ElectronLooseESuperClusterOverP = 0;
   ElectronLooseEcalIsoDR03 = 0;
   ElectronLooseEcalIsoPAT = 0;
   ElectronLooseEnergy = 0;
   ElectronLooseEta = 0;
   ElectronLooseFbrem = 0;
   ElectronLooseHLTDoubleEleMatchEta = 0;
   ElectronLooseHLTDoubleEleMatchPhi = 0;
   ElectronLooseHLTDoubleEleMatchPt = 0;
   ElectronLooseHLTSingleEleMatchEta = 0;
   ElectronLooseHLTSingleEleMatchPhi = 0;
   ElectronLooseHLTSingleEleMatchPt = 0;
   ElectronLooseHLTSingleEleWP80MatchEta = 0;
   ElectronLooseHLTSingleEleWP80MatchPhi = 0;
   ElectronLooseHLTSingleEleWP80MatchPt = 0;
   ElectronLooseHcalIsoD1DR03 = 0;
   ElectronLooseHcalIsoD2DR03 = 0;
   ElectronLooseHcalIsoDR03 = 0;
   ElectronLooseHcalIsoDR03FullCone = 0;
   ElectronLooseHcalIsoPAT = 0;
   ElectronLooseHoE = 0;
   ElectronLooseLeadVtxDistXY = 0;
   ElectronLooseLeadVtxDistZ = 0;
   ElectronLooseMatchedGenParticleEta = 0;
   ElectronLooseMatchedGenParticlePhi = 0;
   ElectronLooseMatchedGenParticlePt = 0;
   ElectronLoosePFChargedHadronIso03 = 0;
   ElectronLoosePFChargedHadronIso04 = 0;
   ElectronLoosePFNeutralHadronIso03 = 0;
   ElectronLoosePFNeutralHadronIso04 = 0;
   ElectronLoosePFPhotonIso03 = 0;
   ElectronLoosePFPhotonIso04 = 0;
   ElectronLoosePhi = 0;
   ElectronLoosePrimaryVertexDXY = 0;
   ElectronLoosePrimaryVertexDXYError = 0;
   ElectronLoosePt = 0;
   ElectronLoosePx = 0;
   ElectronLoosePy = 0;
   ElectronLoosePtHeep = 0;
   ElectronLooseRelIsoPAT = 0;
   ElectronLooseSCEta = 0;
   ElectronLooseSCPhi = 0;
   ElectronLooseSCPt = 0;
   ElectronLooseSCRawEnergy = 0;
   ElectronLooseSigmaEtaEta = 0;
   ElectronLooseSigmaIEtaIEta = 0;
   ElectronLooseTrackPt = 0;
   ElectronLooseTrackValidFractionOfHits = 0;
   ElectronLooseTrackVx = 0;
   ElectronLooseTrackVy = 0;
   ElectronLooseTrackVz = 0;
   ElectronLooseTrkIsoDR03 = 0;
   ElectronLooseTrkIsoPAT = 0;
   ElectronLooseVtxDistXY = 0;
   ElectronLooseVtxDistZ = 0;
   ElectronLoosemvaNontrigV0 = 0;
   ElectronLoosemvatrigV0 = 0;
   ElectronLooseshiftedEdown = 0;
   ElectronLooseshiftedEup = 0;
   ElectronLooseshiftedExdown = 0;
   ElectronLooseshiftedExup = 0;
   ElectronLooseshiftedEydown = 0;
   ElectronLooseshiftedEyup = 0;
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
   MuonLooseBackToBackCompatibility = 0;
   MuonLooseBeamSpotDXY = 0;
   MuonLooseBeamSpotDXYError = 0;
   MuonLooseBestTrackVtxDistXY = 0;
   MuonLooseBestTrackVtxDistZ = 0;
   MuonLooseCocktailEta = 0;
   MuonLooseCocktailEtaError = 0;
   MuonLooseCocktailGlobalChi2 = 0;
   MuonLooseCocktailP = 0;
   MuonLooseCocktailPhi = 0;
   MuonLooseCocktailPhiError = 0;
   MuonLooseCocktailPt = 0;
   MuonLooseCocktailPtError = 0;
   MuonLooseCocktailQOverPError = 0;
   MuonLooseCocktailTrkD0 = 0;
   MuonLooseCocktailTrkD0Error = 0;
   MuonLooseCocktailTrkDz = 0;
   MuonLooseCocktailTrkDzError = 0;
   MuonLooseCocktailTrkValidFractionOfHits = 0;
   MuonLooseCosmicCompatibility = 0;
   MuonLooseCocktailTrkVtxDXY=0;
   MuonLooseCocktailTrkVtxDZ=0;
   MuonLooseEcalIso = 0;
   MuonLooseEcalVetoIso = 0;
   MuonLooseEnergy = 0;
   MuonLooseEta = 0;
   MuonLooseEtaError = 0;
   MuonLooseGlobalChi2 = 0;
   MuonLooseGlobalE = 0;
   MuonLooseGlobalEta = 0;
   MuonLooseGlobalPhi = 0;
   MuonLooseGlobalPt = 0;
   MuonLooseHLTSingleIsoMuonMatchEta = 0;
   MuonLooseHLTSingleIsoMuonMatchPhi = 0;
   MuonLooseHLTSingleIsoMuonMatchPt = 0;
   MuonLooseHLTSingleMuonMatchEta = 0;
   MuonLooseHLTSingleMuonMatchPhi = 0;
   MuonLooseHLTSingleMuonMatchPt = 0;
   MuonLooseHOIso = 0;
   MuonLooseHcalIso = 0;
   MuonLooseHcalVetoIso = 0;
   MuonLooseMatchedGenParticleEta = 0;
   MuonLooseMatchedGenParticlePhi = 0;
   MuonLooseMatchedGenParticlePt = 0;
   MuonLooseMuonSpecE = 0;
   MuonLooseMuonSpecEta = 0;
   MuonLooseMuonSpecPhi = 0;
   MuonLooseMuonSpecPt = 0;

   MuonLooseOverlapCompatibility = 0;
   MuonLooseP = 0;
   MuonLoosePFIsoR03ChargedHadron = 0;
   MuonLoosePFIsoR03ChargedParticle = 0;
   MuonLoosePFIsoR03NeutralHadron = 0;
   MuonLoosePFIsoR03NeutralHadronHT = 0;
   MuonLoosePFIsoR03PU = 0;
   MuonLoosePFIsoR03Photon = 0;
   MuonLoosePFIsoR03PhotonHT = 0;
   MuonLoosePFIsoR04ChargedHadron = 0;
   MuonLoosePFIsoR04ChargedParticle = 0;
   MuonLoosePFIsoR04NeutralHadron = 0;
   MuonLoosePFIsoR04NeutralHadronHT = 0;
   MuonLoosePFIsoR04PU = 0;
   MuonLoosePFIsoR04Photon = 0;
   MuonLoosePFIsoR04PhotonHT = 0;
   MuonLoosePhi = 0;
   MuonLoosePhiError = 0;
   MuonLoosePrimaryVertexDXY = 0;
   MuonLoosePrimaryVertexDXYError = 0;
   MuonLoosePt = 0;
   MuonLoosePx = 0;
   MuonLoosePy = 0;
   MuonLoosePtError = 0;
   MuonLooseQOverPError = 0;
   MuonLooseTimeCompatibility = 0;
   MuonLooseTrackChi2 = 0;
   MuonLooseTrackerIsoSumPT = 0;
   MuonLooseTrkD0 = 0;
   MuonLooseTrkD0Error = 0;
   MuonLooseTrkDz = 0;
   MuonLooseTrkDzError = 0;
   MuonLooseTrkEta = 0;
   MuonLooseTrkEtaError = 0;
   MuonLooseTrkIso = 0;
   MuonLooseTrkPhi = 0;
   MuonLooseTrkPhiError = 0;
   MuonLooseTrkPt = 0;
   MuonLooseTrkPtError = 0;
   MuonLooseTrkValidFractionOfHits = 0;
   MuonLooseTrkVx = 0;
   MuonLooseTrkVy = 0;
   MuonLooseTrkVz = 0;
   MuonLooseVtxDistXY = 0;
   MuonLooseVtxDistZ = 0;
   MuonLooseshiftedEdown = 0;
   MuonLooseshiftedEup = 0;
   MuonLooseshiftedExdown = 0;
   MuonLooseshiftedExup = 0;
   MuonLooseshiftedEydown = 0;
   MuonLooseshiftedEyup = 0;

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
   PFJetL5BottomJEC = 0;
   PFJetL5CharmJEC = 0;
   PFJetL5UDSJEC = 0;
   PFJetL5GluonJEC = 0;
   PFJetMuonEnergyFraction = 0;
   PFJetNeutralEmEnergyFraction = 0;
   PFJetNeutralHadronEnergyFraction = 0;
   PFJetPhi = 0;
   PFJetPhotonEnergyFraction = 0;
   PFJetPt = 0;
   PFJetPx = 0;
   PFJetPy = 0;
   PFJetPtRaw = 0;
   PFJetPxRaw = 0;
   PFJetPyRaw = 0;
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
   PFMETType01XYCorUnclusteredDown = 0;
   PFMETType01XYCorUnclusteredUp = 0;
   PFMETxType01XYCorUnclusteredDown = 0;
   PFMETxType01XYCorUnclusteredUp = 0;
   PFMETyType01XYCorUnclusteredDown = 0;
   PFMETyType01XYCorUnclusteredUp = 0;
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
   CaloJetPassLooseID = 0;
   CaloJetPassTightID = 0;

   ElectronLooseCharge = 0;
   ElectronLooseClassif = 0;
   ElectronLooseMissingHits = 0;
   ElectronLooseMissingHitsEG = 0;
   ElectronLooseNumberOfBrems = 0;
   ElectronLooseOverlaps = 0;
   ElectronLoosePassEGammaIDEoP = 0;
   ElectronLoosePassEGammaIDLoose = 0;
   ElectronLoosePassEGammaIDMedium = 0;
   ElectronLoosePassEGammaIDTight = 0;
   ElectronLoosePassEGammaIDTrigTight = 0;
   ElectronLoosePassEGammaIDTrigWP70 = 0;
   ElectronLoosePassEGammaIDVeto = 0;
   ElectronLoosePassId = 0;
   ElectronLoosePassIsoPAT = 0;
   ElectronLooseVtxIndex = 0;
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
   MuonLooseBestTrackVtxIndex = 0;
   MuonLooseCharge = 0;
   MuonLooseCocktailCharge = 0;
   MuonLooseCocktailRefitID = 0;
   MuonLooseCocktailTrkHits = 0;
   MuonLooseGlobalTrkValidHits = 0;
   MuonLooseIsGlobal = 0;
   MuonLooseIsPF = 0;
   MuonLooseIsTracker = 0;
   MuonLoosePassID = 0;
   MuonLoosePixelHits = 0;
   MuonLooseSegmentMatches = 0;
   MuonLooseStationMatches = 0;
   MuonLooseTrackLayersWithMeasurement = 0;
   MuonLooseTrkHits = 0;
   MuonLooseTrkHitsTrackerOnly = 0;
   MuonLooseTrkPixelHits = 0;
   MuonLooseVtxIndex = 0;
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
   PFJetJetPileupIdflag = 0;
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
   MuonLooseGlobalE = 0;
   MuonLooseGlobalEta = 0;
   MuonLooseGlobalPhi = 0;
   MuonLooseGlobalPt = 0;
   MuonLooseMuonSpecE = 0;
   MuonLooseMuonSpecEta = 0;
   MuonLooseMuonSpecPhi = 0;
   MuonLooseMuonSpecPt = 0;
   PFJetScaledDownEnergy = 0;
   PFJetScaledDownPt = 0;
   PFJetScaledDownPx = 0;
   PFJetScaledDownPy = 0;
   PFJetScaledUpEnergy = 0;
   PFJetScaledUpPt = 0;
   PFJetScaledUpPx = 0;
   PFJetScaledUpPy = 0;
   PFJetSmearedDownEnergy = 0;
   PFJetSmearedDownPt = 0;
   PFJetSmearedDownPx = 0;
   PFJetSmearedDownPy = 0;
   PFJetSmearedUpEnergy = 0;
   PFJetSmearedUpPt = 0;
   PFJetSmearedUpPx = 0;
   PFJetSmearedUpPy = 0;
   PFMETType01XYCorUnclusteredDown = 0;
   PFMETType01XYCorUnclusteredUp = 0;
   PFMETxType01XYCorUnclusteredDown = 0;
   PFMETxType01XYCorUnclusteredUp = 0;
   PFMETyType01XYCorUnclusteredDown = 0;
   PFMETyType01XYCorUnclusteredUp = 0;
   MuonLooseGlobalCharge = 0;
   MuonLooseMuonSpecCharge = 0;
   MuonLooseTrackerCharge = 0;

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
    //ConnectCaloJets();
    //ConnectPhotons();
    //ConnectTaus();
    ConnectTruth();
    ConnectTrigger();
    
    if(setall) ConnectAllBranches();
  }
  return;
}
void Data::ConnectEvent(){


  //fChain->SetBranchAddress("isData", &isData, &b_isData);
  //fChain->SetBranchStatus("isData",1);
  //fChain->AddBranchToCache( "isData", kTRUE );


  ConnectVariable("isData", isData, b_isData);


  ConnectVariable("ProcessID", ProcessID, b_ProcessID);
  
  ConnectVariable("run", run, b_run);
  ConnectVariable("ls", ls, b_ls);
  ConnectVariable("VertexNTracks", VertexNTracks, b_VertexNTracks);
  ConnectVariable("event", event, b_event);
  ConnectVariable("Weight", Weight, b_Weight);
  ConnectVariable("isPhysDeclared", isPhysDeclared, b_isPhysDeclared);
  ConnectVariable("isPrimaryVertex", isPrimaryVertex, b_isPrimaryVertex);
  
  ConnectVariable("isBeamScraping", isBeamScraping, b_isBeamScraping);
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
  
  ConnectVariable("LooseMuonHLTSingleIsoMuonMatched", MuonLooseHLTSingleIsoMuonMatched, b_MuonLooseHLTSingleIsoMuonMatched) ;
  ConnectVariable("LooseMuonHLTSingleMuonMatched", MuonLooseHLTSingleMuonMatched, b_MuonLooseHLTSingleMuonMatched);
  ConnectVariable("LooseMuonHLTSingleMuonMatched5", MuonLooseHLTSingleMuonMatched5, b_MuonLooseHLTSingleMuonMatched5);
  ConnectVariable("LooseMuonHLTSingleMuonMatched8", MuonLooseHLTSingleMuonMatched8, b_MuonLooseHLTSingleMuonMatched8);
  ConnectVariable("LooseMuonHLTSingleMuonMatched12", MuonLooseHLTSingleMuonMatched12, b_MuonLooseHLTSingleMuonMatched12);
  ConnectVariable("LooseMuonHLTSingleMuonMatched17", MuonLooseHLTSingleMuonMatched17, b_MuonLooseHLTSingleMuonMatched17);
  ConnectVariable("LooseMuonHLTSingleMuonMatched24", MuonLooseHLTSingleMuonMatched24, b_MuonLooseHLTSingleMuonMatched24);
  ConnectVariable("LooseMuonHLTDoubleMuonMatched", MuonLooseHLTDoubleMuonMatched, b_MuonLooseHLTDoubleMuonMatched);
  ConnectVariable("LooseMuonHLTEMuMatched8", MuonLooseHLTEMuMatched8,   b_MuonLooseHLTEMuMatched8);
  ConnectVariable("LooseMuonHLTEMuMatched17", MuonLooseHLTEMuMatched17, b_MuonLooseHLTEMuMatched17);
  ConnectVariable("LooseElectronHLTDoubleEleMatched", ElectronLooseHLTDoubleEleMatched, b_ElectronLooseHLTDoubleEleMatched);
  ConnectVariable("LooseElectronHLTSingleEleMatched", ElectronLooseHLTSingleEleMatched, b_ElectronLooseHLTSingleEleMatched);
  ConnectVariable("LooseElectronHLTSingleEleMatched8", ElectronLooseHLTSingleEleMatched8, b_ElectronLooseHLTSingleEleMatched8);
  ConnectVariable("LooseElectronHLTSingleEleMatched17", ElectronLooseHLTSingleEleMatched17, b_ElectronLooseHLTSingleEleMatched17);
  ConnectVariable("LooseElectronHLTSingleEleWP80Matched", ElectronLooseHLTSingleEleWP80Matched, b_ElectronLooseHLTSingleEleWP80Matched);
  ConnectVariable("LooseElectronHLTEMuMatched8",  ElectronLooseHLTEMuMatched8,   b_ElectronLooseHLTEMuMatched8);
  ConnectVariable("LooseElectronHLTEMuMatched17", ElectronLooseHLTEMuMatched17,  b_ElectronLooseHLTEMuMatched17);

  // Trigger
  /*ConnectVariable("HLTFilterObjEta", HLTFilterObjEta, b_HLTFilterObjEta);
  ConnectVariable("HLTFilterObjPhi", HLTFilterObjPhi, b_HLTFilterObjPhi);
  ConnectVariable("HLTFilterObjPt", HLTFilterObjPt, b_HLTFilterObjPt);
  ConnectVariable("HLTFilterName", HLTFilterName, b_HLTFilterName);
  ConnectVariable("HLTFilterObjId", HLTFilterObjId, b_HLTFilterObjId);*/

  
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
  
  //#####   MuonLoose branches
  ConnectVariable("LooseMuonEcalIso", MuonLooseEcalIso, b_MuonLooseEcalIso);
  ConnectVariable("LooseMuonEcalVetoIso", MuonLooseEcalVetoIso, b_MuonLooseEcalVetoIso);
  ConnectVariable("LooseMuonEnergy", MuonLooseEnergy, b_MuonLooseEnergy);
  ConnectVariable("LooseMuonEta", MuonLooseEta, b_MuonLooseEta);
  ConnectVariable("LooseMuonEtaError", MuonLooseEtaError, b_MuonLooseEtaError);
  ConnectVariable("LooseMuonGlobalChi2", MuonLooseGlobalChi2, b_MuonLooseGlobalChi2);
  ConnectVariable("LooseMuonHOIso", MuonLooseHOIso, b_MuonLooseHOIso);
  ConnectVariable("LooseMuonHcalIso", MuonLooseHcalIso, b_MuonLooseHcalIso);
  ConnectVariable("LooseMuonHcalVetoIso", MuonLooseHcalVetoIso, b_MuonLooseHcalVetoIso);
  ConnectVariable("LooseMuonMatchedGenParticleEta", MuonLooseMatchedGenParticleEta, b_MuonLooseMatchedGenParticleEta);
  ConnectVariable("LooseMuonMatchedGenParticlePhi", MuonLooseMatchedGenParticlePhi, b_MuonLooseMatchedGenParticlePhi);
  ConnectVariable("LooseMuonMatchedGenParticlePt", MuonLooseMatchedGenParticlePt, b_MuonLooseMatchedGenParticlePt);
  ConnectVariable("LooseMuonOverlapCompatibility", MuonLooseOverlapCompatibility, b_MuonLooseOverlapCompatibility);
  ConnectVariable("LooseMuonP", MuonLooseP, b_MuonLooseP);
  ConnectVariable("LooseMuonPFIsoR03ChargedHadron", MuonLoosePFIsoR03ChargedHadron, b_MuonLoosePFIsoR03ChargedHadron);
  ConnectVariable("LooseMuonPFIsoR03ChargedParticle", MuonLoosePFIsoR03ChargedParticle, b_MuonLoosePFIsoR03ChargedParticle);
  ConnectVariable("LooseMuonPFIsoR03NeutralHadron", MuonLoosePFIsoR03NeutralHadron, b_MuonLoosePFIsoR03NeutralHadron);
  ConnectVariable("LooseMuonPFIsoR03NeutralHadronHT", MuonLoosePFIsoR03NeutralHadronHT, b_MuonLoosePFIsoR03NeutralHadronHT);
  ConnectVariable("LooseMuonPFIsoR03PU", MuonLoosePFIsoR03PU, b_MuonLoosePFIsoR03PU);
  ConnectVariable("LooseMuonPFIsoR03Photon", MuonLoosePFIsoR03Photon, b_MuonLoosePFIsoR03Photon);
  ConnectVariable("LooseMuonPFIsoR03PhotonHT", MuonLoosePFIsoR03PhotonHT, b_MuonLoosePFIsoR03PhotonHT);
  ConnectVariable("LooseMuonPFIsoR04ChargedHadron", MuonLoosePFIsoR04ChargedHadron, b_MuonLoosePFIsoR04ChargedHadron);
  ConnectVariable("LooseMuonPFIsoR04ChargedParticle", MuonLoosePFIsoR04ChargedParticle, b_MuonLoosePFIsoR04ChargedParticle);
  ConnectVariable("LooseMuonPFIsoR04NeutralHadron", MuonLoosePFIsoR04NeutralHadron, b_MuonLoosePFIsoR04NeutralHadron);
  ConnectVariable("LooseMuonPFIsoR04NeutralHadronHT", MuonLoosePFIsoR04NeutralHadronHT, b_MuonLoosePFIsoR04NeutralHadronHT);
  ConnectVariable("LooseMuonPFIsoR04PU", MuonLoosePFIsoR04PU, b_MuonLoosePFIsoR04PU);
  ConnectVariable("LooseMuonPFIsoR04Photon", MuonLoosePFIsoR04Photon, b_MuonLoosePFIsoR04Photon);
  ConnectVariable("LooseMuonPFIsoR04PhotonHT", MuonLoosePFIsoR04PhotonHT, b_MuonLoosePFIsoR04PhotonHT);
  ConnectVariable("LooseMuonPhi", MuonLoosePhi, b_MuonLoosePhi);
  ConnectVariable("LooseMuonPhiError", MuonLoosePhiError, b_MuonLoosePhiError);
  ConnectVariable("LooseMuonPrimaryVertexDXY", MuonLoosePrimaryVertexDXY, b_MuonLoosePrimaryVertexDXY);
  ConnectVariable("LooseMuonPrimaryVertexDXYError", MuonLoosePrimaryVertexDXYError, b_MuonLoosePrimaryVertexDXYError);
  ConnectVariable("LooseMuonPt", MuonLoosePt, b_MuonLoosePt);
  ConnectVariable("LooseMuonPx", MuonLoosePx, b_MuonLoosePx);
  ConnectVariable("LooseMuonPy", MuonLoosePy, b_MuonLoosePy);
  ConnectVariable("LooseMuonPtError", MuonLoosePtError, b_MuonLoosePtError);
  ConnectVariable("LooseMuonQOverPError", MuonLooseQOverPError, b_MuonLooseQOverPError);
  ConnectVariable("LooseMuonTimeCompatibility", MuonLooseTimeCompatibility, b_MuonLooseTimeCompatibility);
  ConnectVariable("LooseMuonTrackChi2", MuonLooseTrackChi2, b_MuonLooseTrackChi2);
  ConnectVariable("LooseMuonTrackerIsoSumPT", MuonLooseTrackerIsoSumPT, b_MuonLooseTrackerIsoSumPT);
  ConnectVariable("LooseMuonBestTrackVtxDistXY", MuonLooseBestTrackVtxDistXY,b_MuonLooseBestTrackVtxDistXY);
  ConnectVariable("LooseMuonBestTrackVtxDistZ", MuonLooseBestTrackVtxDistZ, b_MuonLooseBestTrackVtxDistZ);
  ConnectVariable("LooseMuonTrkD0", MuonLooseTrkD0, b_MuonLooseTrkD0);
  ConnectVariable("LooseMuonTrkD0Error", MuonLooseTrkD0Error, b_MuonLooseTrkD0Error);
  ConnectVariable("LooseMuonTrkDz", MuonLooseTrkDz, b_MuonLooseTrkDz);
  ConnectVariable("LooseMuonTrkDzError", MuonLooseTrkDzError, b_MuonLooseTrkDzError);
  ConnectVariable("LooseMuonTrkEta", MuonLooseTrkEta, b_MuonLooseTrkEta);
  ConnectVariable("LooseMuonTrkEtaError", MuonLooseTrkEtaError, b_MuonLooseTrkEtaError);
  ConnectVariable("LooseMuonTrkIso", MuonLooseTrkIso, b_MuonLooseTrkIso);
  ConnectVariable("LooseMuonTrkPhi", MuonLooseTrkPhi, b_MuonLooseTrkPhi);
  ConnectVariable("LooseMuonTrkPhiError", MuonLooseTrkPhiError, b_MuonLooseTrkPhiError);
  ConnectVariable("LooseMuonTrkPt", MuonLooseTrkPt, b_MuonLooseTrkPt);
  ConnectVariable("LooseMuonTrkPtError", MuonLooseTrkPtError, b_MuonLooseTrkPtError);
  ConnectVariable("LooseMuonTrkValidFractionOfHits", MuonLooseTrkValidFractionOfHits, b_MuonLooseTrkValidFractionOfHits);
  ConnectVariable("LooseMuonTrkVx", MuonLooseTrkVx, b_MuonLooseTrkVx);
  ConnectVariable("LooseMuonTrkVy", MuonLooseTrkVy, b_MuonLooseTrkVy);
  ConnectVariable("LooseMuonTrkVz", MuonLooseTrkVz, b_MuonLooseTrkVz);
  ConnectVariable("LooseMuonVtxDistXY", MuonLooseVtxDistXY, b_MuonLooseVtxDistXY);
  ConnectVariable("LooseMuonVtxDistZ", MuonLooseVtxDistZ, b_MuonLooseVtxDistZ);
  ConnectVariable("LooseMuonCharge", MuonLooseCharge, b_MuonLooseCharge);
  ConnectVariable("LooseMuonGlobalTrkValidHits", MuonLooseGlobalTrkValidHits, b_MuonLooseGlobalTrkValidHits);
  ConnectVariable("LooseMuonIsGlobal", MuonLooseIsGlobal, b_MuonLooseIsGlobal);
  ConnectVariable("LooseMuonIsPF", MuonLooseIsPF, b_MuonLooseIsPF);
  ConnectVariable("LooseMuonIsTracker", MuonLooseIsTracker, b_MuonLooseIsTracker);
  ConnectVariable("LooseMuonPassID", MuonLoosePassID, b_MuonLoosePassID);
  ConnectVariable("LooseMuonPixelHits", MuonLoosePixelHits, b_MuonLoosePixelHits);
  ConnectVariable("LooseMuonSegmentMatches", MuonLooseSegmentMatches, b_MuonLooseSegmentMatches);
  ConnectVariable("LooseMuonStationMatches", MuonLooseStationMatches, b_MuonLooseStationMatches);
  ConnectVariable("LooseMuonTrackLayersWithMeasurement", MuonLooseTrackLayersWithMeasurement, b_MuonLooseTrackLayersWithMeasurement);
  ConnectVariable("LooseMuonTrkHits", MuonLooseTrkHits, b_MuonLooseTrkHits);
  ConnectVariable("LooseMuonTrkHitsTrackerOnly", MuonLooseTrkHitsTrackerOnly, b_MuonLooseTrkHitsTrackerOnly);
  ConnectVariable("LooseMuonTrkPixelHits", MuonLooseTrkPixelHits, b_MuonLooseTrkPixelHits);
  ConnectVariable("LooseMuonVtxIndex", MuonLooseVtxIndex, b_MuonLooseVtxIndex);
  ConnectVariable("LooseMuonBestTrackVtxIndex", MuonLooseBestTrackVtxIndex, b_MuonLooseBestTrackVtxIndex) ;


  /// New variables 2013/12/02
  ConnectVariable("LooseMuonGlobalE", MuonLooseGlobalE, b_MuonLooseGlobalE);
  ConnectVariable("LooseMuonGlobalEta", MuonLooseGlobalEta, b_MuonLooseGlobalEta);
  ConnectVariable("LooseMuonGlobalPhi", MuonLooseGlobalPhi, b_MuonLooseGlobalPhi);
  ConnectVariable("LooseMuonGlobalPt", MuonLooseGlobalPt, b_MuonLooseGlobalPt);
  ConnectVariable("LooseMuonMuonSpecE", MuonLooseMuonSpecE, b_MuonLooseMuonSpecE);
  ConnectVariable("LooseMuonMuonSpecEta", MuonLooseMuonSpecEta, b_MuonLooseMuonSpecEta);
  ConnectVariable("LooseMuonMuonSpecPhi", MuonLooseMuonSpecPhi, b_MuonLooseMuonSpecPhi);
  ConnectVariable("LooseMuonMuonSpecPt", MuonLooseMuonSpecPt, b_MuonLooseMuonSpecPt);
  ConnectVariable("LooseMuonGlobalCharge",MuonLooseGlobalCharge, b_MuonLooseGlobalCharge);
  ConnectVariable("LooseMuonMuonSpecCharge",MuonLooseMuonSpecCharge, b_MuonLooseMuonSpecCharge);
  ConnectVariable("LooseMuonTrackerCharge", MuonLooseTrackerCharge, b_MuonLooseTrackerCharge);


  ConnectVariable("LooseMuonCocktailCharge", MuonLooseCocktailCharge, b_MuonLooseCocktailCharge);
  ConnectVariable("LooseMuonCocktailPt", MuonLooseCocktailPt, b_MuonLooseCocktailPt);
  ConnectVariable("LooseMuonCocktailEta", MuonLooseCocktailEta, b_MuonLooseCocktailEta);
  ConnectVariable("LooseMuonCocktailPhi", MuonLooseCocktailPhi, b_MuonLooseCocktailPhi);
  ConnectVariable("LooseMuonCocktailTrkD0", MuonLooseCocktailTrkD0, b_MuonLooseCocktailTrkD0);
  ConnectVariable("LooseMuonCocktailTrkDz", MuonLooseCocktailTrkDz, b_MuonLooseCocktailTrkDz);
  ConnectVariable("LooseMuonCocktailGlobalChi2", MuonLooseCocktailGlobalChi2, b_MuonLooseCocktailGlobalChi2);

  ConnectVariable("LooseMuonCocktailTrkVtxDXY", MuonLooseCocktailTrkVtxDXY, b_MuonLooseCocktailTrkVtxDXY);
  ConnectVariable("LooseMuonCocktailTrkVtxDZ", MuonLooseCocktailTrkVtxDZ, b_MuonLooseCocktailTrkVtxDZ);

  ConnectVariable("LooseMuonshiftedEup",MuonLooseshiftedEup,b_MuonLooseshiftedEup);
  ConnectVariable("LooseMuonshiftedEdown",MuonLooseshiftedEdown,b_MuonLooseshiftedEdown);
  ConnectVariable("LooseMuonshiftedPxup",MuonLooseshiftedExup,b_MuonLooseshiftedExup);
  ConnectVariable("LooseMuonshiftedPxdown",MuonLooseshiftedExdown,b_MuonLooseshiftedExdown);

  ConnectVariable("LooseMuonshiftedPyup",MuonLooseshiftedEyup,b_MuonLooseshiftedEyup);
  ConnectVariable("LooseMuonshiftedPydown",MuonLooseshiftedEydown,b_MuonLooseshiftedEydown);



  
  return;}

void Data::ConnectElectrons(){

  //#####   Electron branches
  ConnectVariable("LooseElectronGsfCtfCharge", ElectronLooseGsfCtfCharge, b_ElectronLooseGsfCtfCharge);
  ConnectVariable("LooseElectronGsfScPixCharge", ElectronLooseGsfScPixCharge, b_ElectronLooseGsfScPixCharge);
  ConnectVariable("LooseElectronGsfCtfScPixCharge", ElectronLooseGsfCtfScPixCharge, b_ElectronLooseGsfCtfScPixCharge);
  ConnectVariable("LooseElectronHasEcalDrivenSeed", ElectronLooseHasEcalDrivenSeed, b_ElectronLooseHasEcalDrivenSeed);
  ConnectVariable("LooseElectronHasMatchedConvPhot", ElectronLooseHasMatchedConvPhot, b_ElectronLooseHasMatchedConvPhot);
  ConnectVariable("LooseElectronHasTrackerDrivenSeed", ElectronLooseHasTrackerDrivenSeed, b_ElectronLooseHasTrackerDrivenSeed);

  ConnectVariable("LooseElectronmvatrigV0", ElectronLoosemvatrigV0, b_ElectronLoosemvatrigV0); 
  ConnectVariable("LooseElectronmvaNontrigV0", ElectronLoosemvaNontrigV0, b_ElectronLoosemvaNontrigV0); 
  
  ConnectVariable("LooseElectronshiftedEup", ElectronLooseshiftedEup, b_ElectronLooseshiftedEup);
  ConnectVariable("LooseElectronshiftedEdown", ElectronLooseshiftedEdown, b_ElectronLooseshiftedEdown);
  ConnectVariable("LooseElectronshiftedPxup", ElectronLooseshiftedExup, b_ElectronLooseshiftedExup);
  ConnectVariable("LooseElectronshiftedPxdown", ElectronLooseshiftedExdown, b_ElectronLooseshiftedExdown);
  ConnectVariable("LooseElectronshiftedPyup", ElectronLooseshiftedEyup, b_ElectronLooseshiftedEyup);
  ConnectVariable("LooseElectronshiftedPydown", ElectronLooseshiftedEydown, b_ElectronLooseshiftedEydown);
  ConnectVariable("LooseElectronIsEB", ElectronLooseIsEB, b_ElectronLooseIsEB);
  ConnectVariable("LooseElectronIsEE", ElectronLooseIsEE, b_ElectronLooseIsEE);
  ConnectVariable("LooseElectronBeamSpotDXY", ElectronLooseBeamSpotDXY, b_ElectronLooseBeamSpotDXY);
  ConnectVariable("LooseElectronBeamSpotDXYError", ElectronLooseBeamSpotDXYError, b_ElectronLooseBeamSpotDXYError);
  ConnectVariable("LooseElectronCaloEnergy", ElectronLooseCaloEnergy, b_ElectronLooseCaloEnergy);
  ConnectVariable("LooseElectronConvFitProb", ElectronLooseConvFitProb, b_ElectronLooseConvFitProb);
  ConnectVariable("LooseElectronDCotTheta", ElectronLooseDCotTheta, b_ElectronLooseDCotTheta);
  ConnectVariable("LooseElectronDeltaEtaTrkSC", ElectronLooseDeltaEtaTrkSC, b_ElectronLooseDeltaEtaTrkSC);
  ConnectVariable("LooseElectronDeltaPhiTrkSC", ElectronLooseDeltaPhiTrkSC, b_ElectronLooseDeltaPhiTrkSC);
  ConnectVariable("LooseElectronDist", ElectronLooseDist, b_ElectronLooseDist);
  ConnectVariable("LooseElectronE1x5OverE5x5", ElectronLooseE1x5OverE5x5, b_ElectronLooseE1x5OverE5x5);
  ConnectVariable("LooseElectronE2x5OverE5x5", ElectronLooseE2x5OverE5x5, b_ElectronLooseE2x5OverE5x5);
  ConnectVariable("LooseElectronESuperClusterOverP", ElectronLooseESuperClusterOverP, b_ElectronLooseESuperClusterOverP);
  ConnectVariable("LooseElectronEcalIsoDR03", ElectronLooseEcalIsoDR03, b_ElectronLooseEcalIsoDR03);
  ConnectVariable("LooseElectronEcalIsoPAT", ElectronLooseEcalIsoPAT, b_ElectronLooseEcalIsoPAT);
  ConnectVariable("LooseElectronEnergy", ElectronLooseEnergy, b_ElectronLooseEnergy);
  ConnectVariable("LooseElectronEta", ElectronLooseEta, b_ElectronLooseEta);
  ConnectVariable("LooseElectronHoE", ElectronLooseHoE, b_ElectronLooseHoE);
  ConnectVariable("LooseElectronPFChargedHadronIso03", ElectronLoosePFChargedHadronIso03, b_ElectronLoosePFChargedHadronIso03);
  ConnectVariable("LooseElectronPFChargedHadronIso04", ElectronLoosePFChargedHadronIso04, b_ElectronLoosePFChargedHadronIso04);
  ConnectVariable("LooseElectronPFNeutralHadronIso03", ElectronLoosePFNeutralHadronIso03, b_ElectronLoosePFNeutralHadronIso03);
  ConnectVariable("LooseElectronPFNeutralHadronIso04", ElectronLoosePFNeutralHadronIso04, b_ElectronLoosePFNeutralHadronIso04);
  ConnectVariable("LooseElectronPFPhotonIso03", ElectronLoosePFPhotonIso03, b_ElectronLoosePFPhotonIso03);
  ConnectVariable("LooseElectronPFPhotonIso04", ElectronLoosePFPhotonIso04, b_ElectronLoosePFPhotonIso04);
  ConnectVariable("LooseElectronPhi", ElectronLoosePhi, b_ElectronLoosePhi);
  ConnectVariable("LooseElectronPrimaryVertexDXY", ElectronLoosePrimaryVertexDXY, b_ElectronLoosePrimaryVertexDXY);
  ConnectVariable("LooseElectronPrimaryVertexDXYError", ElectronLoosePrimaryVertexDXYError, b_ElectronLoosePrimaryVertexDXYError);
  ConnectVariable("LooseElectronPt", ElectronLoosePt, b_ElectronLoosePt);
  ConnectVariable("LooseElectronPx", ElectronLoosePx, b_ElectronLoosePx);
  ConnectVariable("LooseElectronPy", ElectronLoosePy, b_ElectronLoosePy);
  ConnectVariable("LooseElectronSCEta", ElectronLooseSCEta, b_ElectronLooseSCEta);
  ConnectVariable("LooseElectronSCPhi", ElectronLooseSCPhi, b_ElectronLooseSCPhi);
  ConnectVariable("LooseElectronSCPt", ElectronLooseSCPt, b_ElectronLooseSCPt);
  ConnectVariable("LooseElectronSCRawEnergy", ElectronLooseSCRawEnergy, b_ElectronLooseSCRawEnergy);
  ConnectVariable("LooseElectronSigmaEtaEta", ElectronLooseSigmaEtaEta, b_ElectronLooseSigmaEtaEta);
  ConnectVariable("LooseElectronSigmaIEtaIEta", ElectronLooseSigmaIEtaIEta, b_ElectronLooseSigmaIEtaIEta);
  ConnectVariable("LooseElectronTrackPt", ElectronLooseTrackPt, b_ElectronLooseTrackPt);
  ConnectVariable("LooseElectronTrackValidFractionOfHits", ElectronLooseTrackValidFractionOfHits, b_ElectronLooseTrackValidFractionOfHits);
  ConnectVariable("LooseElectronTrackVx", ElectronLooseTrackVx, b_ElectronLooseTrackVx);
  ConnectVariable("LooseElectronTrackVy", ElectronLooseTrackVy, b_ElectronLooseTrackVy);
  ConnectVariable("LooseElectronTrackVz", ElectronLooseTrackVz, b_ElectronLooseTrackVz);
  ConnectVariable("LooseElectronVtxDistXY", ElectronLooseVtxDistXY, b_ElectronLooseVtxDistXY);
  ConnectVariable("LooseElectronVtxDistZ", ElectronLooseVtxDistZ, b_ElectronLooseVtxDistZ);
  ConnectVariable("LooseElectronCharge", ElectronLooseCharge, b_ElectronLooseCharge);
  ConnectVariable("LooseElectronClassif", ElectronLooseClassif, b_ElectronLooseClassif);
  ConnectVariable("LooseElectronMissingHits", ElectronLooseMissingHits, b_ElectronLooseMissingHits);
  ConnectVariable("LooseElectronMissingHitsEG", ElectronLooseMissingHitsEG, b_ElectronLooseMissingHitsEG);
  ConnectVariable("LooseElectronNumberOfBrems", ElectronLooseNumberOfBrems, b_ElectronLooseNumberOfBrems);
  ConnectVariable("LooseElectronOverlaps", ElectronLooseOverlaps, b_ElectronLooseOverlaps);
  ConnectVariable("LooseElectronPassEGammaIDEoP", ElectronLoosePassEGammaIDEoP, b_ElectronLoosePassEGammaIDEoP);
  ConnectVariable("LooseElectronPassEGammaIDLoose", ElectronLoosePassEGammaIDLoose, b_ElectronLoosePassEGammaIDLoose);
  ConnectVariable("LooseElectronPassEGammaIDMedium", ElectronLoosePassEGammaIDMedium, b_ElectronLoosePassEGammaIDMedium);
  ConnectVariable("LooseElectronPassEGammaIDTight", ElectronLoosePassEGammaIDTight, b_ElectronLoosePassEGammaIDTight);
  ConnectVariable("LooseElectronPassEGammaIDTrigTight", ElectronLoosePassEGammaIDTrigTight, b_ElectronLoosePassEGammaIDTrigTight);
  ConnectVariable("LooseElectronPassEGammaIDTrigWP70", ElectronLoosePassEGammaIDTrigWP70, b_ElectronLoosePassEGammaIDTrigWP70);
  ConnectVariable("LooseElectronPassEGammaIDVeto", ElectronLoosePassEGammaIDVeto, b_ElectronLoosePassEGammaIDVeto);
  ConnectVariable("LooseElectronPassId", ElectronLoosePassId, b_ElectronLoosePassId);
  ConnectVariable("LooseElectronVtxIndex", ElectronLooseVtxIndex, b_ElectronLooseVtxIndex);
  ConnectVariable("LooseElectronTrkIsoDR03", ElectronLooseTrkIsoDR03, b_ElectronLooseTrkIsoDR03);
  ConnectVariable("LooseElectronFbrem", ElectronLooseFbrem, b_ElectronLooseFbrem);
  ConnectVariable("LooseElectronHcalIsoDR03", ElectronLooseHcalIsoDR03, b_ElectronLooseHcalIsoDR03);
  ConnectVariable("LooseElectronLeadVtxDistXY", ElectronLooseLeadVtxDistXY, b_ElectronLooseLeadVtxDistXY);
  ConnectVariable("LooseElectronLeadVtxDistZ", ElectronLooseLeadVtxDistZ, b_ElectronLooseLeadVtxDistZ);
  ConnectVariable("LooseElectronMatchedGenParticleEta", ElectronLooseMatchedGenParticleEta, b_ElectronLooseMatchedGenParticleEta);
  ConnectVariable("LooseElectronMatchedGenParticlePhi", ElectronLooseMatchedGenParticlePhi, b_ElectronLooseMatchedGenParticlePhi);
  ConnectVariable("LooseElectronMatchedGenParticlePt", ElectronLooseMatchedGenParticlePt, b_ElectronLooseMatchedGenParticlePt);
  ConnectVariable("LooseElectronHcalIsoPAT", ElectronLooseHcalIsoPAT, b_ElectronLooseHcalIsoPAT);
  ConnectVariable("LooseElectronTrkIsoPAT", ElectronLooseTrkIsoPAT, b_ElectronLooseTrkIsoPAT);
  
  /// NEW
  /*
    vector<double>  *ElectronR9;

  */
  return;
}

void Data::ConnectPhotons(){

  ConnectVariable("PhotonEta", PhotonEta, b_PhotonEta);
  ConnectVariable("PhotonPhi" ,PhotonPhi, b_PhotonPhi);
  ConnectVariable("PhotonPt" ,PhotonPt, b_PhotonPt);
  ConnectVariable("PhotonHasMatchedConvPhot", PhotonHasMatchedConvPhot, b_PhotonHasMatchedConvPhot);
  ConnectVariable("PhotonHasMatchedPromptEle", PhotonHasMatchedPromptEle, b_PhotonHasMatchedPromptEle);
  ConnectVariable("PhotonHoE", PhotonHoE, b_PhotonHoE);
  ConnectVariable("PhotonSigmaIEtaIEta", PhotonSigmaIEtaIEta, b_PhotonSigmaIEtaIEta);
  ConnectVariable("PhotonHasPixelSeed", PhotonHasPixelSeed, b_PhotonHasPixelSeed);
  ConnectVariable("PhotonSCeta", PhotonSCeta, b_PhotonSCeta);
  ConnectVariable("PhotonTrkIsoHollowDR04", PhotonTrkIsoHollowDR04, b_PhotonTrkIsoHollowDR04);
  ConnectVariable("PhotonEcalIsoDR04", PhotonEcalIsoDR04, b_PhotonEcalIsoDR04);
  ConnectVariable("PhotonHcalIsoDR04", PhotonHcalIsoDR04, b_PhotonHcalIsoDR04);

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
  ConnectVariable("PFJetPx", PFJetPx, b_PFJetPx);
  ConnectVariable("PFJetPy", PFJetPy, b_PFJetPy);
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
  ConnectVariable("PFJetScaledDownPx",PFJetScaledDownPx,b_PFJetScaledDownPx);
  ConnectVariable("PFJetScaledDownPy",PFJetScaledDownPy,b_PFJetScaledDownPy);
  ConnectVariable("PFJetScaledUpEnergy",PFJetScaledUpEnergy,b_PFJetScaledUpEnergy);
  ConnectVariable("PFJetScaledUpPt",PFJetScaledUpPt,b_PFJetScaledUpPt);
  ConnectVariable("PFJetScaledUpPx",PFJetScaledUpPx,b_PFJetScaledUpPx);
  ConnectVariable("PFJetScaledUpPy",PFJetScaledUpPy,b_PFJetScaledUpPy);
  ConnectVariable("PFJetSmearedDownEnergy",PFJetSmearedDownEnergy,b_PFJetSmearedDownEnergy);
  ConnectVariable("PFJetSmearedDownPt",PFJetSmearedDownPt,b_PFJetSmearedDownPt);
  ConnectVariable("PFJetSmearedDownPx",PFJetSmearedDownPx,b_PFJetSmearedDownPx);
  ConnectVariable("PFJetSmearedDownPy",PFJetSmearedDownPy,b_PFJetSmearedDownPy);
  ConnectVariable("PFJetSmearedUpEnergy",PFJetSmearedUpEnergy,b_PFJetSmearedUpEnergy);
  ConnectVariable("PFJetSmearedUpPt",PFJetSmearedUpPt,b_PFJetSmearedUpPt);
  ConnectVariable("PFJetSmearedUpPx",PFJetSmearedUpPx,b_PFJetSmearedUpPx);
  ConnectVariable("PFJetSmearedUpPy",PFJetSmearedUpPy,b_PFJetSmearedUpPy);
  ConnectVariable("PFJetL1FastJetJEC", PFJetL1FastJetJEC, b_PFJetL1FastJetJEC);
  ConnectVariable("PFJetL2L3ResJEC", PFJetL2L3ResJEC, b_PFJetL2L3ResJEC);
  ConnectVariable("PFJetL2RelJEC", PFJetL2RelJEC, b_PFJetL2RelJEC);
  ConnectVariable("PFJetL3AbsJEC", PFJetL3AbsJEC, b_PFJetL3AbsJEC);
  ConnectVariable("PFJetL5BottomJEC", PFJetL5BottomJEC, b_PFJetL5BottomJEC);
  ConnectVariable("PFJetL5CharmJEC", PFJetL5CharmJEC, b_PFJetL5CharmJEC);
  ConnectVariable("PFJetL5UDSJEC", PFJetL5UDSJEC, b_PFJetL5UDSJEC);
  ConnectVariable("PFJetL5GluonJEC", PFJetL5GluonJEC, b_PFJetL5GluonJEC);
  ConnectVariable("PFJetPtRaw", PFJetPtRaw, b_PFJetPtRaw);
  ConnectVariable("PFJetPxRaw", PFJetPxRaw, b_PFJetPxRaw);
  ConnectVariable("PFJetPyRaw", PFJetPyRaw, b_PFJetPyRaw);
  
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
  ConnectVariable("PFMETPhi", PFMETPhi, b_PFMETPhi);
  ConnectVariable("PFSumET", PFSumET, b_PFSumET);
  ConnectVariable("PFMETPhiType01Cor", PFMETPhiType01Cor, b_PFMETPhiType01Cor);
  ConnectVariable("PFMETType01Cor", PFMETType01Cor, b_PFMETType01Cor);
  ConnectVariable("PFSumETType01Cor", PFSumETType01Cor, b_PFSumETType01Cor);
  ConnectVariable("PFMETPhiType01XYCor", PFMETPhiType01XYCor, b_PFMETPhiType01XYCor);
  ConnectVariable("PFMETType01XYCor", PFMETType01XYCor, b_PFMETType01XYCor);
  ConnectVariable("PFMETxType01XYCor", PFMETxType01XYCor, b_PFMETxType01XYCor);
  ConnectVariable("PFMETyType01XYCor", PFMETyType01XYCor, b_PFMETyType01XYCor);
  ConnectVariable("PFSumETType01XYCor", PFSumETType01XYCor, b_PFSumETType01XYCor);
  ConnectVariable("PFMETPhiType1Cor", PFMETPhiType1Cor, b_PFMETPhiType1Cor);
  ConnectVariable("PFMETType1Cor", PFMETType1Cor, b_PFMETType1Cor);
  ConnectVariable("PFSumETType1Cor", PFSumETType1Cor, b_PFSumETType1Cor);


  /// New variables 2013/12/02
  ConnectVariable("PFMETType01XYCorUnclusteredDown",PFMETType01XYCorUnclusteredDown,b_PFMETType01XYCorUnclusteredDown);
  ConnectVariable("PFMETType01XYCorUnclusteredUp",PFMETType01XYCorUnclusteredUp,b_PFMETType01XYCorUnclusteredUp);

  ConnectVariable("PFMET", PFMET, b_PFMET);
  ConnectVariable("PFMETx", PFMETx, b_PFMETx);
  ConnectVariable("PFMETy", PFMETy, b_PFMETy);
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
  ConnectVariable("GenParticleVX", GenParticleVX, b_GenParticleVX);
  ConnectVariable("GenParticleVY", GenParticleVY, b_GenParticleVX);
  ConnectVariable("GenParticleVZ", GenParticleVZ, b_GenParticleVZ);
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
  ConnectVariable("GenZMuVX", GenZMuVX, b_GenZMuVX);
  ConnectVariable("GenZMuVY", GenZMuVY, b_GenZMuVY);
  ConnectVariable("GenZMuVZ", GenZMuVZ, b_GenZMuVZ);
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
  ConnectVariable("GenZTauVX", GenZTauVX, b_GenZTauVX);
  ConnectVariable("GenZTauVY", GenZTauVY, b_GenZTauVY);
  ConnectVariable("GenZTauVZ", GenZTauVZ, b_GenZTauVZ);

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
  ConnectVariable("GenZElectronVX", GenZElectronVX, b_GenZElectronVX);
  ConnectVariable("GenZElectronVY", GenZElectronVY, b_GenZElectronVY);
  ConnectVariable("GenZElectronVZ", GenZElectronVZ, b_GenZElectronVZ);


  ConnectVariable("GenWMuEnergy", GenWMuEnergy, b_GenWMuEnergy);
  ConnectVariable("GenWMuEta", GenWMuEta, b_GenWMuEta);
  ConnectVariable("GenWMuP", GenWMuP, b_GenWMuP);
  ConnectVariable("GenWMuPhi", GenWMuPhi, b_GenWMuPhi);
  ConnectVariable("GenWMuPt", GenWMuPt, b_GenWMuPt);
  ConnectVariable("GenWMuPx", GenWMuPx, b_GenWMuPx);
  ConnectVariable("GenWMuPy", GenWMuPy, b_GenWMuPy);
  ConnectVariable("GenWMuPz", GenWMuPz, b_GenWMuPz);
  ConnectVariable("GenWMuVX", GenWMuVX, b_GenWMuVX);
  ConnectVariable("GenWMuVY", GenWMuVY, b_GenWMuVY);
  ConnectVariable("GenWMuVZ", GenWMuVZ, b_GenWMuVZ);
  ConnectVariable("GenWMuMotherIndex", GenWMuMotherIndex, b_GenWMuMotherIndex);
  ConnectVariable("GenWMuNumDaught", GenWMuNumDaught, b_GenWMuNumDaught);
  ConnectVariable("GenWMuPdgId", GenWMuPdgId, b_GenWMuPdgId);
  ConnectVariable("GenWMuStatus", GenWMuStatus, b_GenWMuStatus);
  ConnectVariable("GenWMuTauDecayMode", GenWMuTauDecayMode, b_GenWMuTauDecayMode);

  ConnectVariable("GenWTauMotherIndex", GenWTauMotherIndex, b_GenWTauMotherIndex);
  ConnectVariable("GenWTauNumDaught", GenWTauNumDaught, b_GenWTauNumDaught);
  ConnectVariable("GenWTauPdgId", GenWTauPdgId, b_GenWTauPdgId);
  ConnectVariable("GenWTauStatus", GenWTauStatus, b_GenWTauStatus);
  ConnectVariable("GenWTauTauDecayMode", GenWTauTauDecayMode, b_GenWTauTauDecayMode);
  ConnectVariable("GenWTauEnergy", GenWTauEnergy, b_GenWTauEnergy);
  ConnectVariable("GenWTauEta", GenWTauEta, b_GenWTauEta);
  ConnectVariable("GenWTauP", GenWTauP, b_GenWTauP);
  ConnectVariable("GenWTauPhi", GenWTauPhi, b_GenWTauPhi);
  ConnectVariable("GenWTauPt", GenWTauPt, b_GenWTauPt);
  ConnectVariable("GenWTauPx", GenWTauPx, b_GenWTauPx);
  ConnectVariable("GenWTauPy", GenWTauPy, b_GenWTauPy);
  ConnectVariable("GenWTauPz", GenWTauPz, b_GenWTauPz);
  ConnectVariable("GenWTauVX", GenWTauVX, b_GenWTauVX);
  ConnectVariable("GenWTauVY", GenWTauVY, b_GenWTauVY);
  ConnectVariable("GenWTauVZ", GenWTauVZ, b_GenWTauVZ);


  ConnectVariable("GenWElectronMotherIndex", GenWElectronMotherIndex, b_GenWElectronMotherIndex);
  ConnectVariable("GenWElectronNumDaught", GenWElectronNumDaught, b_GenWElectronNumDaught);
  ConnectVariable("GenWElectronPdgId", GenWElectronPdgId, b_GenWElectronPdgId);
  ConnectVariable("GenWElectronStatus", GenWElectronStatus, b_GenWElectronStatus);
  ConnectVariable("GenWElectronTauDecayMode", GenWElectronTauDecayMode, b_GenWElectronTauDecayMode);
  ConnectVariable("GenWElectronEnergy", GenWElectronEnergy, b_GenWElectronEnergy);
  ConnectVariable("GenWElectronEta", GenWElectronEta, b_GenWElectronEta);
  ConnectVariable("GenWElectronP", GenWElectronP, b_GenWElectronP);
  ConnectVariable("GenWElectronPhi", GenWElectronPhi, b_GenWElectronPhi);
  ConnectVariable("GenWElectronPt", GenWElectronPt, b_GenWElectronPt);
  ConnectVariable("GenWElectronPx", GenWElectronPx, b_GenWElectronPx);
  ConnectVariable("GenWElectronPy", GenWElectronPy, b_GenWElectronPy);
  ConnectVariable("GenWElectronPz", GenWElectronPz, b_GenWElectronPz);
  ConnectVariable("GenWElectronVX", GenWElectronVX, b_GenWElectronVX);
  ConnectVariable("GenWElectronVY", GenWElectronVY, b_GenWElectronVY);
  ConnectVariable("GenWElectronVZ", GenWElectronVZ, b_GenWElectronVZ);



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
  ConnectVariable("GenZElectronTauVisibleEta", GenZElectronTauVisibleEta);
  ConnectVariable("GenZElectronTauVisiblePhi", GenZElectronTauVisiblePhi);
  ConnectVariable("GenZElectronTauVisiblePt", GenZElectronTauVisiblePt);


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
  ConnectVariable("GenParticleTauVisibleEta", GenParticleTauVisibleEta);
  ConnectVariable("GenParticleTauVisiblePhi", GenParticleTauVisiblePhi);
  ConnectVariable("GenParticleTauVisiblePt", GenParticleTauVisiblePt);
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

  
  ConnectVariable("MuonCocktailRefitID", MuonCocktailRefitID);
  ConnectVariable("MuonCocktailTrkHits", MuonCocktailTrkHits);  
  ConnectVariable("MuonBackToBackCompatibility", MuonBackToBackCompatibility);
  ConnectVariable("MuonBeamSpotDXY", MuonBeamSpotDXY);
  ConnectVariable("MuonBeamSpotDXYError", MuonBeamSpotDXYError);
  ConnectVariable("MuonCocktailEtaError", MuonCocktailEtaError);
  ConnectVariable("MuonCocktailGlobalChi2", MuonCocktailGlobalChi2);
  ConnectVariable("MuonCocktailP", MuonCocktailP);
  ConnectVariable("MuonCocktailPhiError", MuonCocktailPhiError);
  ConnectVariable("MuonCocktailPtError", MuonCocktailPtError);
  ConnectVariable("MuonCocktailQOverPError", MuonCocktailQOverPError);
  ConnectVariable("MuonCocktailTrkD0Error", MuonCocktailTrkD0Error);
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

  m_logger << INFO << "ConnectVariable 1: " << branchName <<  LQLogger::endmsg;  

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
