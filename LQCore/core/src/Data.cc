// $Id: Data.cxx
/***************************************************************************
 * @Project: LQAnalyzer
 * @Package: Core
 */

#ifndef DATA_cc
#define DATA_cc


// Local include(s):
#include "Data.h"

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
//#include <iostream>

// STL include(s):                                                                                                      
#include <sstream>

Data::Data() 
{

}

Data::~Data()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t Data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
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
  fCurrent = -1;
  fChain->SetMakeClass(1);

  /// TESTS
  //fChain->SetMaxVirtualSize(0);                                                                                                                                             
  //Int_t cachesize=10000000;
  //std::cout << "Cach size = " << fChain->GetCacheSize();
  //std::getchar();
  //fChain->SetCacheSize(cachesize);
  
  fChain->SetBranchStatus("*",0);// disbles all branches                                                                                                                      
  ConnectVariables(false); // -> false means not ALL branches are loaded
  //fChain->StopCacheLearningPhase();
  nentries = fChain->GetEntries();
  Notify();

  return;

}

Long64_t  Data::GetNEntries(){
  return nentries;
}
 
void Data::Reset(){

  /// clear vectors

  // Set object pointer
  HLTKey = 0;
  HLTInsideDatasetTriggerNames = 0;
  HLTOutsideDatasetTriggerNames = 0;
  HLTFilterName = 0;
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

}

void Data::ConnectVariables(bool setall){

  /// set all controlls which cranches are set 
  //#####   EVENT branches
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

  return;
}


void Data::ConnectTrigger(){
  
  //#####   Trigger branches
  ConnectVariable("HLTInsideDatasetTriggerNames", HLTInsideDatasetTriggerNames, b_HLTInsideDatasetTriggerNames);     
  ConnectVariable("HLTInsideDatasetTriggerDecisions", HLTInsideDatasetTriggerDecisions, b_HLTInsideDatasetTriggerDecisions);
  ConnectVariable("HLTInsideDatasetTriggerPrescales", HLTInsideDatasetTriggerPrescales, b_HLTInsideDatasetTriggerPrescales);
  ConnectVariable("HLTOutsideDatasetTriggerPrescales", HLTOutsideDatasetTriggerPrescales, b_HLTOutsideDatasetTriggerPrescales);
  
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


  return;
}

void Data::ConnectMuons(){
  
  //#####   Muon branches
  ConnectVariable("MuonEcalIso", MuonEcalIso, b_MuonEcalIso);
  ConnectVariable("MuonEcalVetoIso", MuonEcalVetoIso, b_MuonEcalVetoIso);
  ConnectVariable("MuonEnergy", MuonEnergy, b_MuonEnergy);
  ConnectVariable("MuonEta", MuonEta, b_MuonEta);
  ConnectVariable("MuonEtaError", MuonEtaError, b_MuonEtaError);
  ConnectVariable("MuonGlobalChi2", MuonGlobalChi2, b_MuonGlobalChi2);
  ConnectVariable("MuonHLTSingleIsoMuonMatchEta", MuonHLTSingleIsoMuonMatchEta, b_MuonHLTSingleIsoMuonMatchEta);
  ConnectVariable("MuonHLTSingleIsoMuonMatchPhi", MuonHLTSingleIsoMuonMatchPhi, b_MuonHLTSingleIsoMuonMatchPhi);
  ConnectVariable("MuonHLTSingleIsoMuonMatchPt", MuonHLTSingleIsoMuonMatchPt, b_MuonHLTSingleIsoMuonMatchPt);
  ConnectVariable("MuonHLTSingleMuonMatchEta", MuonHLTSingleMuonMatchEta, b_MuonHLTSingleMuonMatchEta);
  ConnectVariable("MuonHLTSingleMuonMatchPhi", MuonHLTSingleMuonMatchPhi, b_MuonHLTSingleMuonMatchPhi);
  ConnectVariable("MuonHLTSingleMuonMatchPt", MuonHLTSingleMuonMatchPt, b_MuonHLTSingleMuonMatchPt);
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
 

  return;
}

void Data::ConnectElectrons(){

  //#####   Electron branches
  ConnectVariable("ElectronGsfCtfCharge", ElectronGsfCtfCharge, b_ElectronGsfCtfCharge);
  ConnectVariable("ElectronGsfScPixCharge", ElectronGsfScPixCharge, b_ElectronGsfScPixCharge);
  ConnectVariable("ElectronGsfCtfScPixCharge", ElectronGsfCtfScPixCharge, b_ElectronGsfCtfScPixCharge);
  ConnectVariable("ElectronHasEcalDrivenSeed", ElectronHasEcalDrivenSeed, b_ElectronHasEcalDrivenSeed);
  ConnectVariable("ElectronHasMatchedConvPhot", ElectronHasMatchedConvPhot, b_ElectronHasMatchedConvPhot);
  ConnectVariable("ElectronHasTrackerDrivenSeed", ElectronHasTrackerDrivenSeed, b_ElectronHasTrackerDrivenSeed);
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
  ConnectVariable("ElectronPassIsoPAT", ElectronPassIsoPAT, b_ElectronPassIsoPAT);
  ConnectVariable("ElectronVtxIndex", ElectronVtxIndex, b_ElectronVtxIndex);
  

  return;
}

void Data::ConnectPFJets(){

  //#####   Jet branches
  ConnectVariable("rhoJets", rhoJets, b_rhoJets);
  ConnectVariable("PFJetChargedEmEnergyFraction", PFJetChargedEmEnergyFraction, b_PFJetChargedEmEnergyFraction);
  ConnectVariable("PFJetChargedHadronEnergyFraction", PFJetChargedHadronEnergyFraction, b_PFJetChargedHadronEnergyFraction);
  ConnectVariable("PFJetChargedMuEnergyFraction", PFJetChargedMuEnergyFraction, b_PFJetChargedMuEnergyFraction);
  ConnectVariable("PFJetClosestVertexWeighted3DSeparation", PFJetClosestVertexWeighted3DSeparation, b_PFJetClosestVertexWeighted3DSeparation);
  ConnectVariable("PFJetClosestVertexWeightedXYSeparation", PFJetClosestVertexWeightedXYSeparation, b_PFJetClosestVertexWeightedXYSeparation);
  ConnectVariable("PFJetClosestVertexWeightedZSeparation", PFJetClosestVertexWeightedZSeparation, b_PFJetClosestVertexWeightedZSeparation);
  ConnectVariable("PFJetCombinedSecondaryVertexBTag", PFJetCombinedSecondaryVertexBTag, b_PFJetCombinedSecondaryVertexBTag);
  ConnectVariable("PFJetElectronEnergyFraction", PFJetElectronEnergyFraction, b_PFJetElectronEnergyFraction);
  ConnectVariable("PFJetEnergy", PFJetEnergy, b_PFJetEnergy);
  ConnectVariable("PFJetEnergyRaw", PFJetEnergyRaw, b_PFJetEnergyRaw);
  ConnectVariable("PFJetEta", PFJetEta, b_PFJetEta);
  ConnectVariable("PFJetHFEMEnergyFraction", PFJetHFEMEnergyFraction, b_PFJetHFEMEnergyFraction);
  ConnectVariable("PFJetHFHadronEnergyFraction", PFJetHFHadronEnergyFraction, b_PFJetHFHadronEnergyFraction);
  ConnectVariable("PFJetJECUnc", PFJetJECUnc, b_PFJetJECUnc);
  ConnectVariable("PFJetJetBProbabilityBTag", PFJetJetBProbabilityBTag, b_PFJetJetBProbabilityBTag);
  ConnectVariable("PFJetJetProbabilityBTag", PFJetJetProbabilityBTag, b_PFJetJetProbabilityBTag);
  ConnectVariable("PFJetMuonEnergyFraction", PFJetMuonEnergyFraction, b_PFJetMuonEnergyFraction);
  ConnectVariable("PFJetNeutralEmEnergyFraction", PFJetNeutralEmEnergyFraction, b_PFJetNeutralEmEnergyFraction);
  ConnectVariable("PFJetNeutralHadronEnergyFraction", PFJetNeutralHadronEnergyFraction, b_PFJetNeutralHadronEnergyFraction);
  ConnectVariable("PFJetPhi", PFJetPhi, b_PFJetPhi);
  ConnectVariable("PFJetPhotonEnergyFraction", PFJetPhotonEnergyFraction, b_PFJetPhotonEnergyFraction);
  ConnectVariable("PFJetPt", PFJetPt, b_PFJetPt);
  ConnectVariable("PFJetSoftMuonBTag", PFJetSoftMuonBTag, b_PFJetSoftMuonBTag);
  ConnectVariable("PFJetSoftMuonByIP3dBTag", PFJetSoftMuonByIP3dBTag, b_PFJetSoftMuonByIP3dBTag);
  ConnectVariable("PFJetSoftMuonByPtBTag", PFJetSoftMuonByPtBTag, b_PFJetSoftMuonByPtBTag);
  ConnectVariable("PFJetTrackCountingHighPurBTag", PFJetTrackCountingHighPurBTag, b_PFJetTrackCountingHighPurBTag);
  ConnectVariable("PFCandChargeLeptLink", PFCandChargeLeptLink, b_PFCandChargeLeptLink);
  ConnectVariable("PFJetBestVertexTrackAssociationIndex", PFJetBestVertexTrackAssociationIndex, b_PFJetBestVertexTrackAssociationIndex);
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
  ConnectVariable("PFJetPartonFlavour", PFJetPartonFlavour, b_PFJetPartonFlavour);
  ConnectVariable("PFJetPassLooseID", PFJetPassLooseID, b_PFJetPassLooseID);
  ConnectVariable("PFJetPassTightID", PFJetPassTightID, b_PFJetPassTightID);
  ConnectVariable("PFJetPhotonMultiplicity", PFJetPhotonMultiplicity, b_PFJetPhotonMultiplicity);


  return;
}

void Data::ConnectCaloJets(){
  
  ConnectVariable("CaloJetEnergy", CaloJetEnergy, b_CaloJetEnergy);
  ConnectVariable("CaloJetEta", CaloJetEta, b_CaloJetEta);
  ConnectVariable("CaloJetPhi", CaloJetPhi, b_CaloJetPhi);
  ConnectVariable("CaloJetPt", CaloJetPt, b_CaloJetPt);
  ConnectVariable("CaloJetPassTightID", CaloJetPassTightID, b_CaloJetPassTightID);
  ConnectVariable("CaloJetPassLooseID", CaloJetPassLooseID, b_CaloJetPassLooseID);

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
  
  
  return;
}


void Data::ConnectAllBranches(){

  ///#############################################################################                                                                                              
  //   These are variabels not currenly set: or read: BUT are in ntuples                                                                                                        
  //##############################################################################    
  
  /// Trigger
  ConnectVariable("HLTKey", HLTKey, b_HLTKey);
  ConnectVariable("HLTOutsideDatasetTriggerNames", HLTOutsideDatasetTriggerNames, b_HLTOutsideDatasetTriggerNames);
  ConnectVariable("HLTFilterName", HLTFilterName, b_HLTFilterName);
  
  /// Event
  ConnectVariable("isBPTX0", isBPTX0, b_isBPTX0);  
  ConnectVariable("isBSCBeamHalo", isBSCBeamHalo, b_isBSCBeamHalo);
  ConnectVariable("isBSCMinBias", isBSCMinBias, b_isBSCMinBias);
  ConnectVariable("isBeamScraping", isBeamScraping, b_isBeamScraping);
  ConnectVariable("passBeamHaloFilterTight", passBeamHaloFilterTight, b_passBeamHaloFilterTight);
  ConnectVariable("passCaloBoundaryDRFilter", passCaloBoundaryDRFilter, b_passCaloBoundaryDRFilter);
  ConnectVariable("passEcalMaskedCellDRFilter", passEcalMaskedCellDRFilter, b_passEcalMaskedCellDRFilter);
  ConnectVariable("passLogErrorTooManyClusters", passLogErrorTooManyClusters, b_passLogErrorTooManyClusters);
  ConnectVariable("passManyStripClus53X", passManyStripClus53X, b_passManyStripClus53X);
  ConnectVariable("passTooManyStripClus53X", passTooManyStripClus53X, b_passTooManyStripClus53X);
  ConnectVariable("passTrackingFailureFilter", passTrackingFailureFilter, b_passTrackingFailureFilter);
  ConnectVariable("hasVeryForwardPFMuon", hasVeryForwardPFMuon, b_hasVeryForwardPFMuon);
  ConnectVariable("hasJetWithBadUnc", hasJetWithBadUnc, b_hasJetWithBadUnc);

      
  /// Others
  ConnectVariable("MuonHLTSingleIsoMuonMatched", MuonHLTSingleIsoMuonMatched, b_MuonHLTSingleIsoMuonMatched);
  ConnectVariable("MuonHLTSingleMuonMatched", MuonHLTSingleMuonMatched, b_MuonHLTSingleMuonMatched);
  ConnectVariable("PhotonHasMatchedConvPhot", PhotonHasMatchedConvPhot, b_PhotonHasMatchedConvPhot);
  ConnectVariable("PhotonHasMatchedPromptEle", PhotonHasMatchedPromptEle, b_PhotonHasMatchedPromptEle);
  ConnectVariable("PhotonHasPixelSeed", PhotonHasPixelSeed, b_PhotonHasPixelSeed);
  ConnectVariable("PhotonIsEBEEGap", PhotonIsEBEEGap, b_PhotonIsEBEEGap);
  ConnectVariable("PhotonIsEBGap", PhotonIsEBGap, b_PhotonIsEBGap);
  ConnectVariable("PhotonIsEEGap", PhotonIsEEGap, b_PhotonIsEEGap);
  ConnectVariable("HLTOutsideDatasetTriggerDecisions", HLTOutsideDatasetTriggerDecisions, b_HLTOutsideDatasetTriggerDecisions);     
  ConnectVariable("rhoForHEEP", rhoForHEEP, b_rhoForHEEP);
  ConnectVariable("rhoJetsCCPU", rhoJetsCCPU, b_rhoJetsCCPU);
  ConnectVariable("rhoJetsCN", rhoJetsCN, b_rhoJetsCN);
  ConnectVariable("rhoJetsCNT", rhoJetsCNT, b_rhoJetsCNT);
  ConnectVariable("time", time, b_time);
  ConnectVariable("PtHat", PtHat, b_PtHat);


  /// Electron                                                                                                                                                                  
  ConnectVariable("ElectronHLTDoubleEleMatched", ElectronHLTDoubleEleMatched, b_ElectronHLTDoubleEleMatched);
  ConnectVariable("ElectronHLTSingleEleMatched", ElectronHLTSingleEleMatched, b_ElectronHLTSingleEleMatched);
  ConnectVariable("ElectronHLTSingleEleWP80Matched", ElectronHLTSingleEleWP80Matched, b_ElectronHLTSingleEleWP80Matched);
  ConnectVariable("ElectronFbrem", ElectronFbrem, b_ElectronFbrem);
  ConnectVariable("ElectronHLTDoubleEleMatchEta", ElectronHLTDoubleEleMatchEta, b_ElectronHLTDoubleEleMatchEta);
  ConnectVariable("ElectronHLTDoubleEleMatchPhi", ElectronHLTDoubleEleMatchPhi, b_ElectronHLTDoubleEleMatchPhi);
  ConnectVariable("ElectronHLTDoubleEleMatchPt", ElectronHLTDoubleEleMatchPt, b_ElectronHLTDoubleEleMatchPt);
  ConnectVariable("ElectronHLTSingleEleMatchEta", ElectronHLTSingleEleMatchEta, b_ElectronHLTSingleEleMatchEta);
  ConnectVariable("ElectronHLTSingleEleMatchPhi", ElectronHLTSingleEleMatchPhi, b_ElectronHLTSingleEleMatchPhi);
  ConnectVariable("ElectronHLTSingleEleMatchPt", ElectronHLTSingleEleMatchPt, b_ElectronHLTSingleEleMatchPt);
  ConnectVariable("ElectronHLTSingleEleWP80MatchEta", ElectronHLTSingleEleWP80MatchEta, b_ElectronHLTSingleEleWP80MatchEta);
  ConnectVariable("ElectronHLTSingleEleWP80MatchPhi", ElectronHLTSingleEleWP80MatchPhi, b_ElectronHLTSingleEleWP80MatchPhi);
  ConnectVariable("ElectronHLTSingleEleWP80MatchPt", ElectronHLTSingleEleWP80MatchPt, b_ElectronHLTSingleEleWP80MatchPt);
  ConnectVariable("ElectronHcalIsoD1DR03", ElectronHcalIsoD1DR03, b_ElectronHcalIsoD1DR03);
  ConnectVariable("ElectronHcalIsoD2DR03", ElectronHcalIsoD2DR03, b_ElectronHcalIsoD2DR03);
  ConnectVariable("ElectronHcalIsoDR03", ElectronHcalIsoDR03, b_ElectronHcalIsoDR03);
  ConnectVariable("ElectronHcalIsoDR03FullCone", ElectronHcalIsoDR03FullCone, b_ElectronHcalIsoDR03FullCone);
  ConnectVariable("ElectronHcalIsoPAT", ElectronHcalIsoPAT, b_ElectronHcalIsoPAT);
  ConnectVariable("ElectronLeadVtxDistXY", ElectronLeadVtxDistXY, b_ElectronLeadVtxDistXY);
  ConnectVariable("ElectronLeadVtxDistZ", ElectronLeadVtxDistZ, b_ElectronLeadVtxDistZ);
  ConnectVariable("ElectronMatchedGenParticleEta", ElectronMatchedGenParticleEta, b_ElectronMatchedGenParticleEta);
  ConnectVariable("ElectronMatchedGenParticlePhi", ElectronMatchedGenParticlePhi, b_ElectronMatchedGenParticlePhi);
  ConnectVariable("ElectronMatchedGenParticlePt", ElectronMatchedGenParticlePt, b_ElectronMatchedGenParticlePt);
  ConnectVariable("ElectronPtHeep", ElectronPtHeep, b_ElectronPtHeep);
  ConnectVariable("ElectronRelIsoPAT", ElectronRelIsoPAT, b_ElectronRelIsoPAT);
  ConnectVariable("ElectronTrkIsoDR03", ElectronTrkIsoDR03, b_ElectronTrkIsoDR03);
  ConnectVariable("ElectronTrkIsoPAT", ElectronTrkIsoPAT, b_ElectronTrkIsoPAT);
  
  // Truth
  ConnectVariable("GenWElectronEnergy", GenWElectronEnergy, b_GenWElectronEnergy);
  ConnectVariable("GenWElectronEta", GenWElectronEta, b_GenWElectronEta);
  ConnectVariable("GenWElectronP", GenWElectronP, b_GenWElectronP);
  ConnectVariable("GenWElectronPhi", GenWElectronPhi, b_GenWElectronPhi);
  ConnectVariable("GenWElectronPt", GenWElectronPt, b_GenWElectronPt);
  ConnectVariable("GenWElectronPx", GenWElectronPx, b_GenWElectronPx);
  ConnectVariable("GenWElectronPy", GenWElectronPy, b_GenWElectronPy);
  ConnectVariable("GenWElectronPz", GenWElectronPz, b_GenWElectronPz);
  ConnectVariable("GenWElectronTauVisibleEta", GenWElectronTauVisibleEta, b_GenWElectronTauVisibleEta);
  ConnectVariable("GenWElectronTauVisiblePhi", GenWElectronTauVisiblePhi, b_GenWElectronTauVisiblePhi);
  ConnectVariable("GenWElectronTauVisiblePt", GenWElectronTauVisiblePt, b_GenWElectronTauVisiblePt);
  ConnectVariable("GenWElectronVX", GenWElectronVX, b_GenWElectronVX);
  ConnectVariable("GenWElectronVY", GenWElectronVY, b_GenWElectronVY);
  ConnectVariable("GenWElectronVZ", GenWElectronVZ, b_GenWElectronVZ);
  ConnectVariable("GenZElectronEnergy", GenZElectronEnergy, b_GenZElectronEnergy);
  ConnectVariable("GenZElectronEta", GenZElectronEta, b_GenZElectronEta);
  ConnectVariable("GenZElectronP", GenZElectronP, b_GenZElectronP);
  ConnectVariable("GenZElectronPhi", GenZElectronPhi, b_GenZElectronPhi);
  ConnectVariable("GenZElectronPt", GenZElectronPt, b_GenZElectronPt);
  ConnectVariable("GenZElectronPx", GenZElectronPx, b_GenZElectronPx);
  ConnectVariable("GenZElectronPy", GenZElectronPy, b_GenZElectronPy);
  ConnectVariable("GenZElectronPz", GenZElectronPz, b_GenZElectronPz);
  ConnectVariable("GenZElectronTauVisibleEta", GenZElectronTauVisibleEta, b_GenZElectronTauVisibleEta);
  ConnectVariable("GenZElectronTauVisiblePhi", GenZElectronTauVisiblePhi, b_GenZElectronTauVisiblePhi);
  ConnectVariable("GenZElectronTauVisiblePt", GenZElectronTauVisiblePt, b_GenZElectronTauVisiblePt);
  ConnectVariable("GenZElectronVX", GenZElectronVX, b_GenZElectronVX);
  ConnectVariable("GenZElectronVY", GenZElectronVY, b_GenZElectronVY);
  ConnectVariable("GenZElectronVZ", GenZElectronVZ, b_GenZElectronVZ);
  ConnectVariable("PDFCTEQWeights", PDFCTEQWeights, b_PDFCTEQWeights);
  ConnectVariable("PDFMSTWWeights", PDFMSTWWeights, b_PDFMSTWWeights);
  ConnectVariable("PDFNNPDFWeights", PDFNNPDFWeights, b_PDFNNPDFWeights);
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
  ConnectVariable("GenWMuEnergy", GenWMuEnergy, b_GenWMuEnergy);
  ConnectVariable("GenWMuEta", GenWMuEta, b_GenWMuEta);
  ConnectVariable("GenWMuP", GenWMuP, b_GenWMuP);
  ConnectVariable("GenWMuPhi", GenWMuPhi, b_GenWMuPhi);
  ConnectVariable("GenWMuPt", GenWMuPt, b_GenWMuPt);
  ConnectVariable("GenWMuPx", GenWMuPx, b_GenWMuPx);
  ConnectVariable("GenWMuPy", GenWMuPy, b_GenWMuPy);
  ConnectVariable("GenWMuPz", GenWMuPz, b_GenWMuPz);
  ConnectVariable("GenWMuTauVisibleEta", GenWMuTauVisibleEta, b_GenWMuTauVisibleEta);
  ConnectVariable("GenWMuTauVisiblePhi", GenWMuTauVisiblePhi, b_GenWMuTauVisiblePhi);
  ConnectVariable("GenWMuTauVisiblePt", GenWMuTauVisiblePt, b_GenWMuTauVisiblePt);
  ConnectVariable("GenWMuVX", GenWMuVX, b_GenWMuVX);
  ConnectVariable("GenWMuVY", GenWMuVY, b_GenWMuVY);
  ConnectVariable("GenWMuVZ", GenWMuVZ, b_GenWMuVZ);
  ConnectVariable("GenZMuEnergy", GenZMuEnergy, b_GenZMuEnergy);
  ConnectVariable("GenZMuEta", GenZMuEta, b_GenZMuEta);
  ConnectVariable("GenZMuP", GenZMuP, b_GenZMuP);
  ConnectVariable("GenZMuPhi", GenZMuPhi, b_GenZMuPhi);
  ConnectVariable("GenZMuPt", GenZMuPt, b_GenZMuPt);
  ConnectVariable("GenZMuPx", GenZMuPx, b_GenZMuPx);
  ConnectVariable("GenZMuPy", GenZMuPy, b_GenZMuPy);
  ConnectVariable("GenZMuPz", GenZMuPz, b_GenZMuPz);
  ConnectVariable("GenZMuTauVisibleEta", GenZMuTauVisibleEta, b_GenZMuTauVisibleEta);
  ConnectVariable("GenZMuTauVisiblePhi", GenZMuTauVisiblePhi, b_GenZMuTauVisiblePhi);
  ConnectVariable("GenZMuTauVisiblePt", GenZMuTauVisiblePt, b_GenZMuTauVisiblePt);
  ConnectVariable("GenZMuVX", GenZMuVX, b_GenZMuVX);
  ConnectVariable("GenZMuVY", GenZMuVY, b_GenZMuVY);
  ConnectVariable("GenZMuVZ", GenZMuVZ, b_GenZMuVZ);
  ConnectVariable("GenParticleTauVisibleEta", GenParticleTauVisibleEta, b_GenParticleTauVisibleEta);
  ConnectVariable("GenParticleTauVisiblePhi", GenParticleTauVisiblePhi, b_GenParticleTauVisiblePhi);
  ConnectVariable("GenParticleTauVisiblePt", GenParticleTauVisiblePt, b_GenParticleTauVisiblePt);
  ConnectVariable("GenParticleVX", GenParticleVX, b_GenParticleVX);
  ConnectVariable("GenParticleVY", GenParticleVY, b_GenParticleVY);
  ConnectVariable("GenParticleVZ", GenParticleVZ, b_GenParticleVZ);
  ConnectVariable("GenWTauEnergy", GenWTauEnergy, b_GenWTauEnergy);
  ConnectVariable("GenWTauEta", GenWTauEta, b_GenWTauEta);
  ConnectVariable("GenWTauP", GenWTauP, b_GenWTauP);
  ConnectVariable("GenWTauPhi", GenWTauPhi, b_GenWTauPhi);
  ConnectVariable("GenWTauPt", GenWTauPt, b_GenWTauPt);
  ConnectVariable("GenWTauPx", GenWTauPx, b_GenWTauPx);
  ConnectVariable("GenWTauPy", GenWTauPy, b_GenWTauPy);
  ConnectVariable("GenWTauPz", GenWTauPz, b_GenWTauPz);
  ConnectVariable("GenWTauTauVisibleEta", GenWTauTauVisibleEta, b_GenWTauTauVisibleEta);
  ConnectVariable("GenWTauTauVisiblePhi", GenWTauTauVisiblePhi, b_GenWTauTauVisiblePhi);
  ConnectVariable("GenWTauTauVisiblePt", GenWTauTauVisiblePt, b_GenWTauTauVisiblePt);
  ConnectVariable("GenWTauVX", GenWTauVX, b_GenWTauVX);
  ConnectVariable("GenWTauVY", GenWTauVY, b_GenWTauVY);
  ConnectVariable("GenWTauVZ", GenWTauVZ, b_GenWTauVZ);
  ConnectVariable("GenZTauEnergy", GenZTauEnergy, b_GenZTauEnergy);
  ConnectVariable("GenZTauEta", GenZTauEta, b_GenZTauEta);
  ConnectVariable("GenZTauP", GenZTauP, b_GenZTauP);
  ConnectVariable("GenZTauPhi", GenZTauPhi, b_GenZTauPhi);
  ConnectVariable("GenZTauPt", GenZTauPt, b_GenZTauPt);
  ConnectVariable("GenZTauPx", GenZTauPx, b_GenZTauPx);
  ConnectVariable("GenZTauPy", GenZTauPy, b_GenZTauPy);
  ConnectVariable("GenZTauPz", GenZTauPz, b_GenZTauPz);
  ConnectVariable("GenZTauTauVisibleEta", GenZTauTauVisibleEta, b_GenZTauTauVisibleEta);
  ConnectVariable("GenZTauTauVisiblePhi", GenZTauTauVisiblePhi, b_GenZTauTauVisiblePhi);
  ConnectVariable("GenZTauTauVisiblePt", GenZTauTauVisiblePt, b_GenZTauTauVisiblePt);
  ConnectVariable("GenZTauVX", GenZTauVX, b_GenZTauVX);
  ConnectVariable("GenZTauVY", GenZTauVY, b_GenZTauVY);
  ConnectVariable("GenZTauVZ", GenZTauVZ, b_GenZTauVZ);
  
  // Tau
  ConnectVariable("HPSTauAgainstElectronDeadECALDiscr", HPSTauAgainstElectronDeadECALDiscr, b_HPSTauAgainstElectronDeadECALDiscr);
  ConnectVariable("HPSTauAgainstElectronLooseDiscr", HPSTauAgainstElectronLooseDiscr, b_HPSTauAgainstElectronLooseDiscr);
  ConnectVariable("HPSTauAgainstElectronLooseMVA2Discr", HPSTauAgainstElectronLooseMVA2Discr, b_HPSTauAgainstElectronLooseMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronLooseMVA3Discr", HPSTauAgainstElectronLooseMVA3Discr, b_HPSTauAgainstElectronLooseMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronMVA2categoryDiscr", HPSTauAgainstElectronMVA2categoryDiscr, b_HPSTauAgainstElectronMVA2categoryDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA2rawDiscr", HPSTauAgainstElectronMVA2rawDiscr, b_HPSTauAgainstElectronMVA2rawDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA3categoryDiscr", HPSTauAgainstElectronMVA3categoryDiscr, b_HPSTauAgainstElectronMVA3categoryDiscr);
  ConnectVariable("HPSTauAgainstElectronMVA3rawDiscr", HPSTauAgainstElectronMVA3rawDiscr, b_HPSTauAgainstElectronMVA3rawDiscr);
  ConnectVariable("HPSTauAgainstElectronMVADiscr", HPSTauAgainstElectronMVADiscr, b_HPSTauAgainstElectronMVADiscr);
  ConnectVariable("HPSTauAgainstElectronMediumDiscr", HPSTauAgainstElectronMediumDiscr, b_HPSTauAgainstElectronMediumDiscr);
  ConnectVariable("HPSTauAgainstElectronMediumMVA2Discr", HPSTauAgainstElectronMediumMVA2Discr, b_HPSTauAgainstElectronMediumMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronMediumMVA3Discr", HPSTauAgainstElectronMediumMVA3Discr, b_HPSTauAgainstElectronMediumMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronTightDiscr", HPSTauAgainstElectronTightDiscr, b_HPSTauAgainstElectronTightDiscr);
  ConnectVariable("HPSTauAgainstElectronTightMVA2Discr", HPSTauAgainstElectronTightMVA2Discr, b_HPSTauAgainstElectronTightMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronTightMVA3Discr", HPSTauAgainstElectronTightMVA3Discr, b_HPSTauAgainstElectronTightMVA3Discr);
  ConnectVariable("HPSTauAgainstElectronVLooseMVA2Discr", HPSTauAgainstElectronVLooseMVA2Discr, b_HPSTauAgainstElectronVLooseMVA2Discr);
  ConnectVariable("HPSTauAgainstElectronVTightMVA3Discr", HPSTauAgainstElectronVTightMVA3Discr, b_HPSTauAgainstElectronVTightMVA3Discr);
  ConnectVariable("HPSTauAgainstMuonLoose2Discr", HPSTauAgainstMuonLoose2Discr, b_HPSTauAgainstMuonLoose2Discr);
  ConnectVariable("HPSTauAgainstMuonLooseDiscr", HPSTauAgainstMuonLooseDiscr, b_HPSTauAgainstMuonLooseDiscr);
  ConnectVariable("HPSTauAgainstMuonMedium2Discr", HPSTauAgainstMuonMedium2Discr, b_HPSTauAgainstMuonMedium2Discr);
  ConnectVariable("HPSTauAgainstMuonMediumDiscr", HPSTauAgainstMuonMediumDiscr, b_HPSTauAgainstMuonMediumDiscr);
  ConnectVariable("HPSTauAgainstMuonTight2Discr", HPSTauAgainstMuonTight2Discr, b_HPSTauAgainstMuonTight2Discr);
  ConnectVariable("HPSTauAgainstMuonTightDiscr", HPSTauAgainstMuonTightDiscr, b_HPSTauAgainstMuonTightDiscr);
  ConnectVariable("HPSTauBremsRecoveryEOverPLead", HPSTauBremsRecoveryEOverPLead, b_HPSTauBremsRecoveryEOverPLead);
  ConnectVariable("HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr, b_HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauDecayModeFindingDiscr", HPSTauDecayModeFindingDiscr, b_HPSTauDecayModeFindingDiscr);
  ConnectVariable("HPSTauEcalStripSumEOverPLead", HPSTauEcalStripSumEOverPLead, b_HPSTauEcalStripSumEOverPLead);
  ConnectVariable("HPSTauEmFraction", HPSTauEmFraction, b_HPSTauEmFraction);
  ConnectVariable("HPSTauEtaLeadCharged", HPSTauEtaLeadCharged, b_HPSTauEtaLeadCharged);
  ConnectVariable("HPSTauEtaetaMoment", HPSTauEtaetaMoment, b_HPSTauEtaetaMoment);
  ConnectVariable("HPSTauEtaphiMoment", HPSTauEtaphiMoment, b_HPSTauEtaphiMoment);
  ConnectVariable("HPSTauHcal3x3OverPLead", HPSTauHcal3x3OverPLead, b_HPSTauHcal3x3OverPLead);
  ConnectVariable("HPSTauHcalMaxOverPLead", HPSTauHcalMaxOverPLead, b_HPSTauHcalMaxOverPLead);
  ConnectVariable("HPSTauHcalTotOverPLead", HPSTauHcalTotOverPLead, b_HPSTauHcalTotOverPLead);
  ConnectVariable("HPSTauIsolationMVArawDiscr", HPSTauIsolationMVArawDiscr, b_HPSTauIsolationMVArawDiscr);
  ConnectVariable("HPSTauIsolationPFChargedHadrCandsPtSum", HPSTauIsolationPFChargedHadrCandsPtSum, b_HPSTauIsolationPFChargedHadrCandsPtSum);
  ConnectVariable("HPSTauIsolationPFGammaCandsEtSum", HPSTauIsolationPFGammaCandsEtSum, b_HPSTauIsolationPFGammaCandsEtSum);
  ConnectVariable("HPSTauLeadPFChargedHadrCandsignedSipt", HPSTauLeadPFChargedHadrCandsignedSipt, b_HPSTauLeadPFChargedHadrCandsignedSipt);
  ConnectVariable("HPSTauLeadVtxDistXY", HPSTauLeadVtxDistXY, b_HPSTauLeadVtxDistXY);
  ConnectVariable("HPSTauLeadVtxDistZ", HPSTauLeadVtxDistZ, b_HPSTauLeadVtxDistZ);
  ConnectVariable("HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr, b_HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr", HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr, b_HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauLooseIsolationDeltaBetaCorrDiscr", HPSTauLooseIsolationDeltaBetaCorrDiscr, b_HPSTauLooseIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauLooseIsolationDiscr", HPSTauLooseIsolationDiscr, b_HPSTauLooseIsolationDiscr);
  ConnectVariable("HPSTauLooseIsolationMVA2Discr", HPSTauLooseIsolationMVA2Discr, b_HPSTauLooseIsolationMVA2Discr);
  ConnectVariable("HPSTauLooseIsolationMVADiscr", HPSTauLooseIsolationMVADiscr, b_HPSTauLooseIsolationMVADiscr);
  ConnectVariable("HPSTauMatchedGenJetEta", HPSTauMatchedGenJetEta, b_HPSTauMatchedGenJetEta);
  ConnectVariable("HPSTauMatchedGenJetPhi", HPSTauMatchedGenJetPhi, b_HPSTauMatchedGenJetPhi);
  ConnectVariable("HPSTauMatchedGenJetPt", HPSTauMatchedGenJetPt, b_HPSTauMatchedGenJetPt);
  ConnectVariable("HPSTauMatchedGenParticleEta", HPSTauMatchedGenParticleEta, b_HPSTauMatchedGenParticleEta);
  ConnectVariable("HPSTauMatchedGenParticlePhi", HPSTauMatchedGenParticlePhi, b_HPSTauMatchedGenParticlePhi);
  ConnectVariable("HPSTauMatchedGenParticlePt", HPSTauMatchedGenParticlePt, b_HPSTauMatchedGenParticlePt);
  ConnectVariable("HPSTauMaximumHCALPFClusterEt", HPSTauMaximumHCALPFClusterEt, b_HPSTauMaximumHCALPFClusterEt);
  ConnectVariable("HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr, b_HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr", HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr, b_HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauMediumIsolationDeltaBetaCorrDiscr", HPSTauMediumIsolationDeltaBetaCorrDiscr, b_HPSTauMediumIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauMediumIsolationDiscr", HPSTauMediumIsolationDiscr, b_HPSTauMediumIsolationDiscr);
  ConnectVariable("HPSTauMediumIsolationMVA2Discr", HPSTauMediumIsolationMVA2Discr, b_HPSTauMediumIsolationMVA2Discr);
  ConnectVariable("HPSTauMediumIsolationMVADiscr", HPSTauMediumIsolationMVADiscr, b_HPSTauMediumIsolationMVADiscr);
  ConnectVariable("HPSTauPhiLeadCharged", HPSTauPhiLeadCharged, b_HPSTauPhiLeadCharged);
  ConnectVariable("HPSTauPhiphiMoment", HPSTauPhiphiMoment, b_HPSTauPhiphiMoment);
  ConnectVariable("HPSTauPtLeadCharged", HPSTauPtLeadCharged, b_HPSTauPtLeadCharged);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsCount", HPSTauSignalPFChargedHadrCandsCount, b_HPSTauSignalPFChargedHadrCandsCount);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsEta", HPSTauSignalPFChargedHadrCandsEta, b_HPSTauSignalPFChargedHadrCandsEta);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsPhi", HPSTauSignalPFChargedHadrCandsPhi, b_HPSTauSignalPFChargedHadrCandsPhi);
  ConnectVariable("HPSTauSignalPFChargedHadrCandsPt", HPSTauSignalPFChargedHadrCandsPt, b_HPSTauSignalPFChargedHadrCandsPt);
  ConnectVariable("HPSTauSignalPFGammaCandsCount", HPSTauSignalPFGammaCandsCount, b_HPSTauSignalPFGammaCandsCount);
  ConnectVariable("HPSTauSignalPFGammaCandsEta", HPSTauSignalPFGammaCandsEta, b_HPSTauSignalPFGammaCandsEta);
  ConnectVariable("HPSTauSignalPFGammaCandsPhi", HPSTauSignalPFGammaCandsPhi, b_HPSTauSignalPFGammaCandsPhi);
  ConnectVariable("HPSTauSignalPFGammaCandsPt", HPSTauSignalPFGammaCandsPt, b_HPSTauSignalPFGammaCandsPt);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsCount", HPSTauSignalPFNeutrHadrCandsCount, b_HPSTauSignalPFNeutrHadrCandsCount);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsEta", HPSTauSignalPFNeutrHadrCandsEta, b_HPSTauSignalPFNeutrHadrCandsEta);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsPhi", HPSTauSignalPFNeutrHadrCandsPhi, b_HPSTauSignalPFNeutrHadrCandsPhi);
  ConnectVariable("HPSTauSignalPFNeutrHadrCandsPt", HPSTauSignalPFNeutrHadrCandsPt, b_HPSTauSignalPFNeutrHadrCandsPt);
  ConnectVariable("HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr", HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr, b_HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr);
  ConnectVariable("HPSTauTightCombinedIsolationDeltaBetaCorrDiscr", HPSTauTightCombinedIsolationDeltaBetaCorrDiscr, b_HPSTauTightCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauTightIsolationDeltaBetaCorrDiscr", HPSTauTightIsolationDeltaBetaCorrDiscr, b_HPSTauTightIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauTightIsolationDiscr", HPSTauTightIsolationDiscr, b_HPSTauTightIsolationDiscr);
  ConnectVariable("HPSTauTightIsolationMVA2Discr", HPSTauTightIsolationMVA2Discr, b_HPSTauTightIsolationMVA2Discr);
  ConnectVariable("HPSTauTightIsolationMVADiscr", HPSTauTightIsolationMVADiscr, b_HPSTauTightIsolationMVADiscr);
  ConnectVariable("HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr", HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr, b_HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauVLooseIsolationDeltaBetaCorrDiscr", HPSTauVLooseIsolationDeltaBetaCorrDiscr, b_HPSTauVLooseIsolationDeltaBetaCorrDiscr);
  ConnectVariable("HPSTauVLooseIsolationDiscr", HPSTauVLooseIsolationDiscr, b_HPSTauVLooseIsolationDiscr);
  ConnectVariable("HPSTauVtxDistXY", HPSTauVtxDistXY, b_HPSTauVtxDistXY);
  ConnectVariable("HPSTauVtxDistZ", HPSTauVtxDistZ, b_HPSTauVtxDistZ);
  
  // Muon
  ConnectVariable("MuonBackToBackCompatibility", MuonBackToBackCompatibility, b_MuonBackToBackCompatibility);
  ConnectVariable("MuonBeamSpotDXY", MuonBeamSpotDXY, b_MuonBeamSpotDXY);
  ConnectVariable("MuonBeamSpotDXYError", MuonBeamSpotDXYError, b_MuonBeamSpotDXYError);
  ConnectVariable("MuonBestTrackVtxDistXY", MuonBestTrackVtxDistXY, b_MuonBestTrackVtxDistXY);
  ConnectVariable("MuonBestTrackVtxDistZ", MuonBestTrackVtxDistZ, b_MuonBestTrackVtxDistZ);
  ConnectVariable("MuonCocktailEta", MuonCocktailEta, b_MuonCocktailEta);
  ConnectVariable("MuonCocktailEtaError", MuonCocktailEtaError, b_MuonCocktailEtaError);
  ConnectVariable("MuonCocktailGlobalChi2", MuonCocktailGlobalChi2, b_MuonCocktailGlobalChi2);
  ConnectVariable("MuonCocktailP", MuonCocktailP, b_MuonCocktailP);
  ConnectVariable("MuonCocktailPhi", MuonCocktailPhi, b_MuonCocktailPhi);
  ConnectVariable("MuonCocktailPhiError", MuonCocktailPhiError, b_MuonCocktailPhiError);
  ConnectVariable("MuonCocktailPt", MuonCocktailPt, b_MuonCocktailPt);
  ConnectVariable("MuonCocktailPtError", MuonCocktailPtError, b_MuonCocktailPtError);
  ConnectVariable("MuonCocktailQOverPError", MuonCocktailQOverPError, b_MuonCocktailQOverPError);
  ConnectVariable("MuonCocktailTrkD0", MuonCocktailTrkD0, b_MuonCocktailTrkD0);
  ConnectVariable("MuonCocktailTrkD0Error", MuonCocktailTrkD0Error, b_MuonCocktailTrkD0Error);
  ConnectVariable("MuonCocktailTrkDz", MuonCocktailTrkDz, b_MuonCocktailTrkDz);
  ConnectVariable("MuonCocktailTrkDzError", MuonCocktailTrkDzError, b_MuonCocktailTrkDzError);
  ConnectVariable("MuonCocktailTrkValidFractionOfHits", MuonCocktailTrkValidFractionOfHits, b_MuonCocktailTrkValidFractionOfHits);
  ConnectVariable("MuonCosmicCompatibility", MuonCosmicCompatibility, b_MuonCosmicCompatibility);
  
  // PF
  ConnectVariable("PFCandEnergyLeptLink", PFCandEnergyLeptLink, b_PFCandEnergyLeptLink);
  ConnectVariable("PFCandEtaLeptLink", PFCandEtaLeptLink, b_PFCandEtaLeptLink);
  ConnectVariable("PFCandPhiLeptLink", PFCandPhiLeptLink, b_PFCandPhiLeptLink);
  ConnectVariable("PFCandPtLeptLink", PFCandPtLeptLink, b_PFCandPtLeptLink);
  ConnectVariable("PFJetBestVertexTrackAssociationFactor", PFJetBestVertexTrackAssociationFactor, b_PFJetBestVertexTrackAssociationFactor);
  ConnectVariable("PFJetBeta", PFJetBeta, b_PFJetBeta);
  ConnectVariable("PFJetBetaClassic", PFJetBetaClassic, b_PFJetBetaClassic);
  ConnectVariable("PFJetBetaStar", PFJetBetaStar, b_PFJetBetaStar);
  ConnectVariable("PFJetBetaStarClassic", PFJetBetaStarClassic, b_PFJetBetaStarClassic);
  ConnectVariable("PFJetCombinedInclusiveSecondaryVertexBTag", PFJetCombinedInclusiveSecondaryVertexBTag, b_PFJetCombinedInclusiveSecondaryVertexBTag);
  ConnectVariable("PFJetCombinedMVABTag", PFJetCombinedMVABTag, b_PFJetCombinedMVABTag);
  ConnectVariable("PFJetCombinedSecondaryVertexMVABTag", PFJetCombinedSecondaryVertexMVABTag, b_PFJetCombinedSecondaryVertexMVABTag);
  ConnectVariable("PFJetL1FastJetJEC", PFJetL1FastJetJEC, b_PFJetL1FastJetJEC);
  ConnectVariable("PFJetL2L3ResJEC", PFJetL2L3ResJEC, b_PFJetL2L3ResJEC);
  ConnectVariable("PFJetL2RelJEC", PFJetL2RelJEC, b_PFJetL2RelJEC);
  ConnectVariable("PFJetL3AbsJEC", PFJetL3AbsJEC, b_PFJetL3AbsJEC);
  ConnectVariable("PFJetPtRaw", PFJetPtRaw, b_PFJetPtRaw);
  ConnectVariable("PFJetSimpleSecondaryVertexHighEffBTag", PFJetSimpleSecondaryVertexHighEffBTag, b_PFJetSimpleSecondaryVertexHighEffBTag);
  ConnectVariable("PFJetSimpleSecondaryVertexHighPurBTag", PFJetSimpleSecondaryVertexHighPurBTag, b_PFJetSimpleSecondaryVertexHighPurBTag);
  ConnectVariable("PFJetSoftElectronByIP3dBTag", PFJetSoftElectronByIP3dBTag, b_PFJetSoftElectronByIP3dBTag);
  ConnectVariable("PFJetSoftElectronByPtBTag", PFJetSoftElectronByPtBTag, b_PFJetSoftElectronByPtBTag);
  ConnectVariable("PFJetTrackCountingHighEffBTag", PFJetTrackCountingHighEffBTag, b_PFJetTrackCountingHighEffBTag);
  ConnectVariable("PFMET", PFMET, b_PFMET);

  /// Photon
  ConnectVariable("PhotonAlpha", PhotonAlpha, b_PhotonAlpha);
  ConnectVariable("PhotonChi2ConvPhot", PhotonChi2ConvPhot, b_PhotonChi2ConvPhot);
  ConnectVariable("PhotonDPhiTracksAtVtxConvPhot", PhotonDPhiTracksAtVtxConvPhot, b_PhotonDPhiTracksAtVtxConvPhot);
  ConnectVariable("PhotonDistOfMinApproachConvPhot", PhotonDistOfMinApproachConvPhot, b_PhotonDistOfMinApproachConvPhot);
  ConnectVariable("PhotonE2OverE9", PhotonE2OverE9, b_PhotonE2OverE9);
  ConnectVariable("PhotonE3x3", PhotonE3x3, b_PhotonE3x3);
  ConnectVariable("PhotonE4SwissCross", PhotonE4SwissCross, b_PhotonE4SwissCross);
  ConnectVariable("PhotonE5x5", PhotonE5x5, b_PhotonE5x5);
  ConnectVariable("PhotonEOverPConvPhot", PhotonEOverPConvPhot, b_PhotonEOverPConvPhot);
  ConnectVariable("PhotonEcalIsoDR03", PhotonEcalIsoDR03, b_PhotonEcalIsoDR03);
  ConnectVariable("PhotonEcalIsoDR04", PhotonEcalIsoDR04, b_PhotonEcalIsoDR04);
  ConnectVariable("PhotonEnergy", PhotonEnergy, b_PhotonEnergy);
  ConnectVariable("PhotonEta", PhotonEta, b_PhotonEta);
  ConnectVariable("PhotonHcalIsoDR03", PhotonHcalIsoDR03, b_PhotonHcalIsoDR03);
  ConnectVariable("PhotonHcalIsoDR03FullCone", PhotonHcalIsoDR03FullCone, b_PhotonHcalIsoDR03FullCone);
  ConnectVariable("PhotonHcalIsoDR04", PhotonHcalIsoDR04, b_PhotonHcalIsoDR04);
  ConnectVariable("PhotonHcalIsoDR04FullCone", PhotonHcalIsoDR04FullCone, b_PhotonHcalIsoDR04FullCone);
  ConnectVariable("PhotonHoE", PhotonHoE, b_PhotonHoE);
  ConnectVariable("PhotonNDofConvPhot", PhotonNDofConvPhot, b_PhotonNDofConvPhot);
  ConnectVariable("PhotonPairCotThetaSeparationConvPhot", PhotonPairCotThetaSeparationConvPhot, b_PhotonPairCotThetaSeparationConvPhot);
  ConnectVariable("PhotonPairInvariantMassConvPhot", PhotonPairInvariantMassConvPhot, b_PhotonPairInvariantMassConvPhot);
  ConnectVariable("PhotonPairMomentumxConvPhot", PhotonPairMomentumxConvPhot, b_PhotonPairMomentumxConvPhot);
  ConnectVariable("PhotonPairMomentumyConvPhot", PhotonPairMomentumyConvPhot, b_PhotonPairMomentumyConvPhot);
  ConnectVariable("PhotonPairMomentumzConvPhot", PhotonPairMomentumzConvPhot, b_PhotonPairMomentumzConvPhot);
  ConnectVariable("PhotonPhi", PhotonPhi, b_PhotonPhi);
  ConnectVariable("PhotonPt", PhotonPt, b_PhotonPt);
  ConnectVariable("PhotonSCenergy", PhotonSCenergy, b_PhotonSCenergy);
  ConnectVariable("PhotonSCeta", PhotonSCeta, b_PhotonSCeta);
  ConnectVariable("PhotonSCphi", PhotonSCphi, b_PhotonSCphi);
  ConnectVariable("PhotonSCseedEnergy", PhotonSCseedEnergy, b_PhotonSCseedEnergy);
  ConnectVariable("PhotonSEtaEta", PhotonSEtaEta, b_PhotonSEtaEta);
  ConnectVariable("PhotonSEtaPhi", PhotonSEtaPhi, b_PhotonSEtaPhi);
  ConnectVariable("PhotonSMajMaj", PhotonSMajMaj, b_PhotonSMajMaj);
  ConnectVariable("PhotonSMinMin", PhotonSMinMin, b_PhotonSMinMin);
  ConnectVariable("PhotonSPhiPhi", PhotonSPhiPhi, b_PhotonSPhiPhi);
  ConnectVariable("PhotonSigmaIEtaIEta", PhotonSigmaIEtaIEta, b_PhotonSigmaIEtaIEta);
  ConnectVariable("PhotonTimeSeed", PhotonTimeSeed, b_PhotonTimeSeed);
  ConnectVariable("PhotonTrkIsoHollowDR03", PhotonTrkIsoHollowDR03, b_PhotonTrkIsoHollowDR03);
  ConnectVariable("PhotonTrkIsoHollowDR04", PhotonTrkIsoHollowDR04, b_PhotonTrkIsoHollowDR04);
  ConnectVariable("PhotonTrkIsoSolidDR03", PhotonTrkIsoSolidDR03, b_PhotonTrkIsoSolidDR03);
  ConnectVariable("PhotonTrkIsoSolidDR04", PhotonTrkIsoSolidDR04, b_PhotonTrkIsoSolidDR04);
  ConnectVariable("PhotonXVtxConvPhot", PhotonXVtxConvPhot, b_PhotonXVtxConvPhot);
  ConnectVariable("PhotonYVtxConvPhot", PhotonYVtxConvPhot, b_PhotonYVtxConvPhot);
  ConnectVariable("PhotonZVtxConvPhot", PhotonZVtxConvPhot, b_PhotonZVtxConvPhot);
  ConnectVariable("TCMET", TCMET, b_TCMET);
  ConnectVariable("TCMETPhi", TCMETPhi, b_TCMETPhi);
  ConnectVariable("TCSumET", TCSumET, b_TCSumET);

  // Trigger
  ConnectVariable("HLTFilterObjEta", HLTFilterObjEta, b_HLTFilterObjEta);
  ConnectVariable("HLTFilterObjPhi", HLTFilterObjPhi, b_HLTFilterObjPhi);
  ConnectVariable("HLTFilterObjPt", HLTFilterObjPt, b_HLTFilterObjPt);
  
  // Truth
  
  ConnectVariable("GenWElectronMotherIndex", GenWElectronMotherIndex, b_GenWElectronMotherIndex);
  ConnectVariable("GenWElectronNumDaught", GenWElectronNumDaught, b_GenWElectronNumDaught);
  ConnectVariable("GenWElectronPdgId", GenWElectronPdgId, b_GenWElectronPdgId);
  ConnectVariable("GenWElectronStatus", GenWElectronStatus, b_GenWElectronStatus);
  ConnectVariable("GenWElectronTauDecayMode", GenWElectronTauDecayMode, b_GenWElectronTauDecayMode);
  ConnectVariable("GenZElectronMotherIndex", GenZElectronMotherIndex, b_GenZElectronMotherIndex);
  ConnectVariable("GenZElectronNumDaught", GenZElectronNumDaught, b_GenZElectronNumDaught);
  ConnectVariable("GenZElectronPdgId", GenZElectronPdgId, b_GenZElectronPdgId);
  ConnectVariable("GenZElectronStatus", GenZElectronStatus, b_GenZElectronStatus);
  ConnectVariable("GenZElectronTauDecayMode", GenZElectronTauDecayMode, b_GenZElectronTauDecayMode);
  ConnectVariable("PileUpInteractions", PileUpInteractions, b_PileUpInteractions);
  ConnectVariable("PileUpOriginBX", PileUpOriginBX, b_PileUpOriginBX);
  ConnectVariable("GenWMuMotherIndex", GenWMuMotherIndex, b_GenWMuMotherIndex);
  ConnectVariable("GenWMuNumDaught", GenWMuNumDaught, b_GenWMuNumDaught);
  ConnectVariable("GenWMuPdgId", GenWMuPdgId, b_GenWMuPdgId);
  ConnectVariable("GenWMuStatus", GenWMuStatus, b_GenWMuStatus);
  ConnectVariable("GenWMuTauDecayMode", GenWMuTauDecayMode, b_GenWMuTauDecayMode);
  ConnectVariable("GenZMuMotherIndex", GenZMuMotherIndex, b_GenZMuMotherIndex);
  ConnectVariable("GenZMuNumDaught", GenZMuNumDaught, b_GenZMuNumDaught);
  ConnectVariable("GenZMuPdgId", GenZMuPdgId, b_GenZMuPdgId);
  ConnectVariable("GenZMuStatus", GenZMuStatus, b_GenZMuStatus);
  ConnectVariable("GenZMuTauDecayMode", GenZMuTauDecayMode, b_GenZMuTauDecayMode);
  ConnectVariable("GenWTauMotherIndex", GenWTauMotherIndex, b_GenWTauMotherIndex);
  ConnectVariable("GenWTauNumDaught", GenWTauNumDaught, b_GenWTauNumDaught);
  ConnectVariable("GenWTauPdgId", GenWTauPdgId, b_GenWTauPdgId);
  ConnectVariable("GenWTauStatus", GenWTauStatus, b_GenWTauStatus);
  ConnectVariable("GenWTauTauDecayMode", GenWTauTauDecayMode, b_GenWTauTauDecayMode);
  ConnectVariable("GenZTauMotherIndex", GenZTauMotherIndex, b_GenZTauMotherIndex);
  ConnectVariable("GenZTauNumDaught", GenZTauNumDaught, b_GenZTauNumDaught);
  ConnectVariable("GenZTauPdgId", GenZTauPdgId, b_GenZTauPdgId);
  ConnectVariable("GenZTauStatus", GenZTauStatus, b_GenZTauStatus);
  ConnectVariable("GenZTauTauDecayMode", GenZTauTauDecayMode, b_GenZTauTauDecayMode);
  ConnectVariable("HPSTauDecayMode", HPSTauDecayMode, b_HPSTauDecayMode);
  ConnectVariable("HPSTauIsCaloTau", HPSTauIsCaloTau, b_HPSTauIsCaloTau);
  ConnectVariable("HPSTauVtxIndex", HPSTauVtxIndex, b_HPSTauVtxIndex);
  ConnectVariable("MuonBestTrackVtxIndex", MuonBestTrackVtxIndex, b_MuonBestTrackVtxIndex);
  ConnectVariable("MuonCocktailCharge", MuonCocktailCharge, b_MuonCocktailCharge);
  ConnectVariable("MuonCocktailRefitID", MuonCocktailRefitID, b_MuonCocktailRefitID);
  ConnectVariable("MuonCocktailTrkHits", MuonCocktailTrkHits, b_MuonCocktailTrkHits);
  ConnectVariable("PhotonNTracksConvPhot", PhotonNTracksConvPhot, b_PhotonNTracksConvPhot);

  // Event
  ConnectVariable("L1PhysBits", L1PhysBits, b_L1PhysBits);
  ConnectVariable("L1TechBits", L1TechBits, b_L1TechBits);
  ConnectVariable("VertexNTracksW05", VertexNTracksW05, b_VertexNTracksW05);
  ConnectVariable("HLTFilterObjId", HLTFilterObjId, b_HLTFilterObjId);
  ConnectVariable("bunch", bunch, b_bunch);
  ConnectVariable("ls", ls, b_ls); 
  ConnectVariable("orbit", orbit, b_orbit);                                                                                                    
  ConnectVariable("ProcessID", ProcessID, b_ProcessID);     


  return;
}



template< typename T >
bool Data::ConnectVariable( const char* branchName,
                                        T*& variable , TBranch* br){

  // Check if the branch actually exists:                                                                                                                                                                                                                                                             
  TBranch* branch_info;
  if( ! (branch_info = fChain->GetBranch( branchName ) ) ) {    
    return false;
  }
  
  //variable = new T();
  // The object pointers have to be initialised to zero before                                                                                                             
  // connecting them to the branches       
  variable = 0;
  fChain->SetBranchStatus(branchName,1);
  fChain->SetBranchAddress(branchName, &variable, &br);
  //br->SetAutoDelete(kTRUE);
  fChain->AddBranchToCache( branchName, kTRUE );
  
  return true;
}

template< typename T >
bool Data::ConnectVariable(  const char* branchName,
			     T& variable , TBranch* br){
  
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
