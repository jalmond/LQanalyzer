//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 22 09:30:25 2013 by ROOT version 5.32/00
// from TTree tree/
// found on file: dcache:///pnfs/cms/WAX/11/store/user/fgior8/Summer12LQ_tag11/ttbar/RootTupleMakerV2_output_MC_31_1_lqn.root
//////////////////////////////////////////////////////////

#ifndef MyClass_del_h
#define MyClass_del_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <string>
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class MyClass_del {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   string          *HLTKey;
   vector<string>  *HLTInsideDatasetTriggerNames;
   vector<string>  *HLTOutsideDatasetTriggerNames;
   vector<string>  *HLTFilterName;
   Bool_t          isData;
   Bool_t          isBPTX0;
   Bool_t          isBSCBeamHalo;
   Bool_t          isBSCMinBias;
   Bool_t          isBeamScraping;
   Bool_t          isPhysDeclared;
   Bool_t          isPrimaryVertex;
   Bool_t          isTrackingFailure;
   Bool_t          passBadEESupercrystalFilter;
   Bool_t          passBeamHaloFilterLoose;
   Bool_t          passBeamHaloFilterTight;
   Bool_t          passCaloBoundaryDRFilter;
   Bool_t          passEcalDeadCellBoundaryEnergyFilter;
   Bool_t          passEcalDeadCellTriggerPrimitiveFilter;
   Bool_t          passEcalLaserCorrFilter;
   Bool_t          passEcalMaskedCellDRFilter;
   Bool_t          passHBHENoiseFilter;
   Bool_t          passLogErrorTooManyClusters;
   Bool_t          passManyStripClus53X;
   Bool_t          passTooManyStripClus53X;
   Bool_t          passTrackingFailureFilter;
   Bool_t          hasVeryForwardPFMuon;
   Bool_t          hasJetWithBadUnc;
   vector<bool>    *ElectronGsfCtfCharge;
   vector<bool>    *ElectronGsfCtfScPixCharge;
   vector<bool>    *ElectronGsfScPixCharge;
   vector<bool>    *ElectronHLTDoubleEleMatched;
   vector<bool>    *ElectronHLTSingleEleMatched;
   vector<bool>    *ElectronHLTSingleEleWP80Matched;
   vector<bool>    *ElectronHasEcalDrivenSeed;
   vector<bool>    *ElectronHasMatchedConvPhot;
   vector<bool>    *ElectronHasTrackerDrivenSeed;
   vector<bool>    *ElectronIsEB;
   vector<bool>    *ElectronIsEE;
   vector<bool>    *MuonHLTSingleIsoMuonMatched;
   vector<bool>    *MuonHLTSingleMuonMatched;
   vector<bool>    *PhotonHasMatchedConvPhot;
   vector<bool>    *PhotonHasMatchedPromptEle;
   vector<bool>    *PhotonHasPixelSeed;
   vector<bool>    *PhotonIsEBEEGap;
   vector<bool>    *PhotonIsEBGap;
   vector<bool>    *PhotonIsEEGap;
   vector<bool>    *HLTInsideDatasetTriggerDecisions;
   vector<bool>    *HLTOutsideDatasetTriggerDecisions;
   vector<bool>    *VertexIsFake;
   Double_t        rhoForHEEP;
   Double_t        rhoJets;
   Double_t        rhoJetsCCPU;
   Double_t        rhoJetsCN;
   Double_t        rhoJetsCNT;
   Double_t        time;
   Double_t        PtHat;
   Double_t        Weight;
   vector<double>  *CaloMET;
   vector<double>  *CaloMETPhi;
   vector<double>  *CaloMETPhiUncorr;
   vector<double>  *CaloMETUncorr;
   vector<double>  *CaloSumET;
   vector<double>  *CaloSumETUncorr;
   vector<double>  *CaloMETPhiType1Cor;
   vector<double>  *CaloMETPhiUncorrType1Cor;
   vector<double>  *CaloMETType1Cor;
   vector<double>  *CaloMETUncorrType1Cor;
   vector<double>  *CaloSumETType1Cor;
   vector<double>  *CaloSumETUncorrType1Cor;
   vector<double>  *ElectronBeamSpotDXY;
   vector<double>  *ElectronBeamSpotDXYError;
   vector<double>  *ElectronCaloEnergy;
   vector<double>  *ElectronConvFitProb;
   vector<double>  *ElectronDCotTheta;
   vector<double>  *ElectronDeltaEtaTrkSC;
   vector<double>  *ElectronDeltaPhiTrkSC;
   vector<double>  *ElectronDist;
   vector<double>  *ElectronE1x5OverE5x5;
   vector<double>  *ElectronE2x5OverE5x5;
   vector<double>  *ElectronESuperClusterOverP;
   vector<double>  *ElectronEcalIsoDR03;
   vector<double>  *ElectronEcalIsoPAT;
   vector<double>  *ElectronEnergy;
   vector<double>  *ElectronEta;
   vector<double>  *ElectronFbrem;
   vector<double>  *ElectronHLTDoubleEleMatchEta;
   vector<double>  *ElectronHLTDoubleEleMatchPhi;
   vector<double>  *ElectronHLTDoubleEleMatchPt;
   vector<double>  *ElectronHLTSingleEleMatchEta;
   vector<double>  *ElectronHLTSingleEleMatchPhi;
   vector<double>  *ElectronHLTSingleEleMatchPt;
   vector<double>  *ElectronHLTSingleEleWP80MatchEta;
   vector<double>  *ElectronHLTSingleEleWP80MatchPhi;
   vector<double>  *ElectronHLTSingleEleWP80MatchPt;
   vector<double>  *ElectronHcalIsoD1DR03;
   vector<double>  *ElectronHcalIsoD2DR03;
   vector<double>  *ElectronHcalIsoDR03;
   vector<double>  *ElectronHcalIsoDR03FullCone;
   vector<double>  *ElectronHcalIsoPAT;
   vector<double>  *ElectronHoE;
   vector<double>  *ElectronLeadVtxDistXY;
   vector<double>  *ElectronLeadVtxDistZ;
   vector<double>  *ElectronMatchedGenParticleEta;
   vector<double>  *ElectronMatchedGenParticlePhi;
   vector<double>  *ElectronMatchedGenParticlePt;
   vector<double>  *ElectronPFChargedHadronIso03;
   vector<double>  *ElectronPFChargedHadronIso04;
   vector<double>  *ElectronPFNeutralHadronIso03;
   vector<double>  *ElectronPFNeutralHadronIso04;
   vector<double>  *ElectronPFPhotonIso03;
   vector<double>  *ElectronPFPhotonIso04;
   vector<double>  *ElectronPhi;
   vector<double>  *ElectronPrimaryVertexDXY;
   vector<double>  *ElectronPrimaryVertexDXYError;
   vector<double>  *ElectronPt;
   vector<double>  *ElectronPtHeep;
   vector<double>  *ElectronRelIsoPAT;
   vector<double>  *ElectronSCEta;
   vector<double>  *ElectronSCPhi;
   vector<double>  *ElectronSCPt;
   vector<double>  *ElectronSCRawEnergy;
   vector<double>  *ElectronSigmaEtaEta;
   vector<double>  *ElectronSigmaIEtaIEta;
   vector<double>  *ElectronTrackPt;
   vector<double>  *ElectronTrackValidFractionOfHits;
   vector<double>  *ElectronTrackVx;
   vector<double>  *ElectronTrackVy;
   vector<double>  *ElectronTrackVz;
   vector<double>  *ElectronTrkIsoDR03;
   vector<double>  *ElectronTrkIsoPAT;
   vector<double>  *ElectronVtxDistXY;
   vector<double>  *ElectronVtxDistZ;
   vector<double>  *GenWElectronEnergy;
   vector<double>  *GenWElectronEta;
   vector<double>  *GenWElectronP;
   vector<double>  *GenWElectronPhi;
   vector<double>  *GenWElectronPt;
   vector<double>  *GenWElectronPx;
   vector<double>  *GenWElectronPy;
   vector<double>  *GenWElectronPz;
   vector<double>  *GenWElectronTauVisibleEta;
   vector<double>  *GenWElectronTauVisiblePhi;
   vector<double>  *GenWElectronTauVisiblePt;
   vector<double>  *GenWElectronVX;
   vector<double>  *GenWElectronVY;
   vector<double>  *GenWElectronVZ;
   vector<double>  *GenZElectronEnergy;
   vector<double>  *GenZElectronEta;
   vector<double>  *GenZElectronP;
   vector<double>  *GenZElectronPhi;
   vector<double>  *GenZElectronPt;
   vector<double>  *GenZElectronPx;
   vector<double>  *GenZElectronPy;
   vector<double>  *GenZElectronPz;
   vector<double>  *GenZElectronTauVisibleEta;
   vector<double>  *GenZElectronTauVisiblePhi;
   vector<double>  *GenZElectronTauVisiblePt;
   vector<double>  *GenZElectronVX;
   vector<double>  *GenZElectronVY;
   vector<double>  *GenZElectronVZ;
   vector<double>  *PDFCTEQWeights;
   vector<double>  *PDFMSTWWeights;
   vector<double>  *PDFNNPDFWeights;
   vector<double>  *GenJetEMF;
   vector<double>  *GenJetEnergy;
   vector<double>  *GenJetEta;
   vector<double>  *GenJetHADF;
   vector<double>  *GenJetP;
   vector<double>  *GenJetPhi;
   vector<double>  *GenJetPt;
   vector<double>  *GenMETCalo;
   vector<double>  *GenMETPhiCalo;
   vector<double>  *GenSumETCalo;
   vector<double>  *GenMETPhiTrue;
   vector<double>  *GenMETTrue;
   vector<double>  *GenSumETTrue;
   vector<double>  *GenWMuEnergy;
   vector<double>  *GenWMuEta;
   vector<double>  *GenWMuP;
   vector<double>  *GenWMuPhi;
   vector<double>  *GenWMuPt;
   vector<double>  *GenWMuPx;
   vector<double>  *GenWMuPy;
   vector<double>  *GenWMuPz;
   vector<double>  *GenWMuTauVisibleEta;
   vector<double>  *GenWMuTauVisiblePhi;
   vector<double>  *GenWMuTauVisiblePt;
   vector<double>  *GenWMuVX;
   vector<double>  *GenWMuVY;
   vector<double>  *GenWMuVZ;
   vector<double>  *GenZMuEnergy;
   vector<double>  *GenZMuEta;
   vector<double>  *GenZMuP;
   vector<double>  *GenZMuPhi;
   vector<double>  *GenZMuPt;
   vector<double>  *GenZMuPx;
   vector<double>  *GenZMuPy;
   vector<double>  *GenZMuPz;
   vector<double>  *GenZMuTauVisibleEta;
   vector<double>  *GenZMuTauVisiblePhi;
   vector<double>  *GenZMuTauVisiblePt;
   vector<double>  *GenZMuVX;
   vector<double>  *GenZMuVY;
   vector<double>  *GenZMuVZ;
   vector<double>  *GenParticleEnergy;
   vector<double>  *GenParticleEta;
   vector<double>  *GenParticleP;
   vector<double>  *GenParticlePhi;
   vector<double>  *GenParticlePt;
   vector<double>  *GenParticlePx;
   vector<double>  *GenParticlePy;
   vector<double>  *GenParticlePz;
   vector<double>  *GenParticleTauVisibleEta;
   vector<double>  *GenParticleTauVisiblePhi;
   vector<double>  *GenParticleTauVisiblePt;
   vector<double>  *GenParticleVX;
   vector<double>  *GenParticleVY;
   vector<double>  *GenParticleVZ;
   vector<double>  *GenWTauEnergy;
   vector<double>  *GenWTauEta;
   vector<double>  *GenWTauP;
   vector<double>  *GenWTauPhi;
   vector<double>  *GenWTauPt;
   vector<double>  *GenWTauPx;
   vector<double>  *GenWTauPy;
   vector<double>  *GenWTauPz;
   vector<double>  *GenWTauTauVisibleEta;
   vector<double>  *GenWTauTauVisiblePhi;
   vector<double>  *GenWTauTauVisiblePt;
   vector<double>  *GenWTauVX;
   vector<double>  *GenWTauVY;
   vector<double>  *GenWTauVZ;
   vector<double>  *GenZTauEnergy;
   vector<double>  *GenZTauEta;
   vector<double>  *GenZTauP;
   vector<double>  *GenZTauPhi;
   vector<double>  *GenZTauPt;
   vector<double>  *GenZTauPx;
   vector<double>  *GenZTauPy;
   vector<double>  *GenZTauPz;
   vector<double>  *GenZTauTauVisibleEta;
   vector<double>  *GenZTauTauVisiblePhi;
   vector<double>  *GenZTauTauVisiblePt;
   vector<double>  *GenZTauVX;
   vector<double>  *GenZTauVY;
   vector<double>  *GenZTauVZ;
   vector<double>  *HPSTauAgainstElectronDeadECALDiscr;
   vector<double>  *HPSTauAgainstElectronLooseDiscr;
   vector<double>  *HPSTauAgainstElectronLooseMVA2Discr;
   vector<double>  *HPSTauAgainstElectronLooseMVA3Discr;
   vector<double>  *HPSTauAgainstElectronMVA2categoryDiscr;
   vector<double>  *HPSTauAgainstElectronMVA2rawDiscr;
   vector<double>  *HPSTauAgainstElectronMVA3categoryDiscr;
   vector<double>  *HPSTauAgainstElectronMVA3rawDiscr;
   vector<double>  *HPSTauAgainstElectronMVADiscr;
   vector<double>  *HPSTauAgainstElectronMediumDiscr;
   vector<double>  *HPSTauAgainstElectronMediumMVA2Discr;
   vector<double>  *HPSTauAgainstElectronMediumMVA3Discr;
   vector<double>  *HPSTauAgainstElectronTightDiscr;
   vector<double>  *HPSTauAgainstElectronTightMVA2Discr;
   vector<double>  *HPSTauAgainstElectronTightMVA3Discr;
   vector<double>  *HPSTauAgainstElectronVLooseMVA2Discr;
   vector<double>  *HPSTauAgainstElectronVTightMVA3Discr;
   vector<double>  *HPSTauAgainstMuonLoose2Discr;
   vector<double>  *HPSTauAgainstMuonLooseDiscr;
   vector<double>  *HPSTauAgainstMuonMedium2Discr;
   vector<double>  *HPSTauAgainstMuonMediumDiscr;
   vector<double>  *HPSTauAgainstMuonTight2Discr;
   vector<double>  *HPSTauAgainstMuonTightDiscr;
   vector<double>  *HPSTauBremsRecoveryEOverPLead;
   vector<double>  *HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr;
   vector<double>  *HPSTauDecayModeFindingDiscr;
   vector<double>  *HPSTauEcalStripSumEOverPLead;
   vector<double>  *HPSTauEmFraction;
   vector<double>  *HPSTauEt;
   vector<double>  *HPSTauEta;
   vector<double>  *HPSTauEtaLeadCharged;
   vector<double>  *HPSTauEtaetaMoment;
   vector<double>  *HPSTauEtaphiMoment;
   vector<double>  *HPSTauHcal3x3OverPLead;
   vector<double>  *HPSTauHcalMaxOverPLead;
   vector<double>  *HPSTauHcalTotOverPLead;
   vector<double>  *HPSTauIsolationMVArawDiscr;
   vector<double>  *HPSTauIsolationPFChargedHadrCandsPtSum;
   vector<double>  *HPSTauIsolationPFGammaCandsEtSum;
   vector<double>  *HPSTauLeadPFChargedHadrCandsignedSipt;
   vector<double>  *HPSTauLeadVtxDistXY;
   vector<double>  *HPSTauLeadVtxDistZ;
   vector<double>  *HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr;
   vector<double>  *HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauLooseIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauLooseIsolationDiscr;
   vector<double>  *HPSTauLooseIsolationMVA2Discr;
   vector<double>  *HPSTauLooseIsolationMVADiscr;
   vector<double>  *HPSTauMatchedGenJetEta;
   vector<double>  *HPSTauMatchedGenJetPhi;
   vector<double>  *HPSTauMatchedGenJetPt;
   vector<double>  *HPSTauMatchedGenParticleEta;
   vector<double>  *HPSTauMatchedGenParticlePhi;
   vector<double>  *HPSTauMatchedGenParticlePt;
   vector<double>  *HPSTauMaximumHCALPFClusterEt;
   vector<double>  *HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr;
   vector<double>  *HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauMediumIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauMediumIsolationDiscr;
   vector<double>  *HPSTauMediumIsolationMVA2Discr;
   vector<double>  *HPSTauMediumIsolationMVADiscr;
   vector<double>  *HPSTauPhi;
   vector<double>  *HPSTauPhiLeadCharged;
   vector<double>  *HPSTauPhiphiMoment;
   vector<double>  *HPSTauPt;
   vector<double>  *HPSTauPtLeadCharged;
   vector<double>  *HPSTauSignalPFChargedHadrCandsCount;
   vector<double>  *HPSTauSignalPFChargedHadrCandsEta;
   vector<double>  *HPSTauSignalPFChargedHadrCandsPhi;
   vector<double>  *HPSTauSignalPFChargedHadrCandsPt;
   vector<double>  *HPSTauSignalPFGammaCandsCount;
   vector<double>  *HPSTauSignalPFGammaCandsEta;
   vector<double>  *HPSTauSignalPFGammaCandsPhi;
   vector<double>  *HPSTauSignalPFGammaCandsPt;
   vector<double>  *HPSTauSignalPFNeutrHadrCandsCount;
   vector<double>  *HPSTauSignalPFNeutrHadrCandsEta;
   vector<double>  *HPSTauSignalPFNeutrHadrCandsPhi;
   vector<double>  *HPSTauSignalPFNeutrHadrCandsPt;
   vector<double>  *HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr;
   vector<double>  *HPSTauTightCombinedIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauTightIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauTightIsolationDiscr;
   vector<double>  *HPSTauTightIsolationMVA2Discr;
   vector<double>  *HPSTauTightIsolationMVADiscr;
   vector<double>  *HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauVLooseIsolationDeltaBetaCorrDiscr;
   vector<double>  *HPSTauVLooseIsolationDiscr;
   vector<double>  *HPSTauVtxDistXY;
   vector<double>  *HPSTauVtxDistZ;
   vector<double>  *MuonBackToBackCompatibility;
   vector<double>  *MuonBeamSpotDXY;
   vector<double>  *MuonBeamSpotDXYError;
   vector<double>  *MuonBestTrackVtxDistXY;
   vector<double>  *MuonBestTrackVtxDistZ;
   vector<double>  *MuonCocktailEta;
   vector<double>  *MuonCocktailEtaError;
   vector<double>  *MuonCocktailGlobalChi2;
   vector<double>  *MuonCocktailP;
   vector<double>  *MuonCocktailPhi;
   vector<double>  *MuonCocktailPhiError;
   vector<double>  *MuonCocktailPt;
   vector<double>  *MuonCocktailPtError;
   vector<double>  *MuonCocktailQOverPError;
   vector<double>  *MuonCocktailTrkD0;
   vector<double>  *MuonCocktailTrkD0Error;
   vector<double>  *MuonCocktailTrkDz;
   vector<double>  *MuonCocktailTrkDzError;
   vector<double>  *MuonCocktailTrkValidFractionOfHits;
   vector<double>  *MuonCosmicCompatibility;
   vector<double>  *MuonEcalIso;
   vector<double>  *MuonEcalVetoIso;
   vector<double>  *MuonEnergy;
   vector<double>  *MuonEta;
   vector<double>  *MuonEtaError;
   vector<double>  *MuonGlobalChi2;
   vector<double>  *MuonHLTSingleIsoMuonMatchEta;
   vector<double>  *MuonHLTSingleIsoMuonMatchPhi;
   vector<double>  *MuonHLTSingleIsoMuonMatchPt;
   vector<double>  *MuonHLTSingleMuonMatchEta;
   vector<double>  *MuonHLTSingleMuonMatchPhi;
   vector<double>  *MuonHLTSingleMuonMatchPt;
   vector<double>  *MuonHOIso;
   vector<double>  *MuonHcalIso;
   vector<double>  *MuonHcalVetoIso;
   vector<double>  *MuonMatchedGenParticleEta;
   vector<double>  *MuonMatchedGenParticlePhi;
   vector<double>  *MuonMatchedGenParticlePt;
   vector<double>  *MuonOverlapCompatibility;
   vector<double>  *MuonP;
   vector<double>  *MuonPFIsoR03ChargedHadron;
   vector<double>  *MuonPFIsoR03ChargedParticle;
   vector<double>  *MuonPFIsoR03NeutralHadron;
   vector<double>  *MuonPFIsoR03NeutralHadronHT;
   vector<double>  *MuonPFIsoR03PU;
   vector<double>  *MuonPFIsoR03Photon;
   vector<double>  *MuonPFIsoR03PhotonHT;
   vector<double>  *MuonPFIsoR04ChargedHadron;
   vector<double>  *MuonPFIsoR04ChargedParticle;
   vector<double>  *MuonPFIsoR04NeutralHadron;
   vector<double>  *MuonPFIsoR04NeutralHadronHT;
   vector<double>  *MuonPFIsoR04PU;
   vector<double>  *MuonPFIsoR04Photon;
   vector<double>  *MuonPFIsoR04PhotonHT;
   vector<double>  *MuonPhi;
   vector<double>  *MuonPhiError;
   vector<double>  *MuonPrimaryVertexDXY;
   vector<double>  *MuonPrimaryVertexDXYError;
   vector<double>  *MuonPt;
   vector<double>  *MuonPtError;
   vector<double>  *MuonQOverPError;
   vector<double>  *MuonTimeCompatibility;
   vector<double>  *MuonTrackChi2;
   vector<double>  *MuonTrackerIsoSumPT;
   vector<double>  *MuonTrkD0;
   vector<double>  *MuonTrkD0Error;
   vector<double>  *MuonTrkDz;
   vector<double>  *MuonTrkDzError;
   vector<double>  *MuonTrkEta;
   vector<double>  *MuonTrkEtaError;
   vector<double>  *MuonTrkIso;
   vector<double>  *MuonTrkPhi;
   vector<double>  *MuonTrkPhiError;
   vector<double>  *MuonTrkPt;
   vector<double>  *MuonTrkPtError;
   vector<double>  *MuonTrkValidFractionOfHits;
   vector<double>  *MuonTrkVx;
   vector<double>  *MuonTrkVy;
   vector<double>  *MuonTrkVz;
   vector<double>  *MuonVtxDistXY;
   vector<double>  *MuonVtxDistZ;
   vector<double>  *PFCandEnergyLeptLink;
   vector<double>  *PFCandEtaLeptLink;
   vector<double>  *PFCandPhiLeptLink;
   vector<double>  *PFCandPtLeptLink;
   vector<double>  *PFJetBestVertexTrackAssociationFactor;
   vector<double>  *PFJetBeta;
   vector<double>  *PFJetBetaClassic;
   vector<double>  *PFJetBetaStar;
   vector<double>  *PFJetBetaStarClassic;
   vector<double>  *PFJetChargedEmEnergyFraction;
   vector<double>  *PFJetChargedHadronEnergyFraction;
   vector<double>  *PFJetChargedMuEnergyFraction;
   vector<double>  *PFJetClosestVertexWeighted3DSeparation;
   vector<double>  *PFJetClosestVertexWeightedXYSeparation;
   vector<double>  *PFJetClosestVertexWeightedZSeparation;
   vector<double>  *PFJetCombinedInclusiveSecondaryVertexBTag;
   vector<double>  *PFJetCombinedMVABTag;
   vector<double>  *PFJetCombinedSecondaryVertexBTag;
   vector<double>  *PFJetCombinedSecondaryVertexMVABTag;
   vector<double>  *PFJetElectronEnergyFraction;
   vector<double>  *PFJetEnergy;
   vector<double>  *PFJetEnergyRaw;
   vector<double>  *PFJetEta;
   vector<double>  *PFJetHFEMEnergyFraction;
   vector<double>  *PFJetHFHadronEnergyFraction;
   vector<double>  *PFJetJECUnc;
   vector<double>  *PFJetJetBProbabilityBTag;
   vector<double>  *PFJetJetProbabilityBTag;
   vector<double>  *PFJetL1FastJetJEC;
   vector<double>  *PFJetL1OffsetJEC;
   vector<double>  *PFJetL2L3ResJEC;
   vector<double>  *PFJetL2RelJEC;
   vector<double>  *PFJetL3AbsJEC;
   vector<double>  *PFJetMuonEnergyFraction;
   vector<double>  *PFJetNeutralEmEnergyFraction;
   vector<double>  *PFJetNeutralHadronEnergyFraction;
   vector<double>  *PFJetPhi;
   vector<double>  *PFJetPhotonEnergyFraction;
   vector<double>  *PFJetPt;
   vector<double>  *PFJetPtRaw;
   vector<double>  *PFJetSimpleSecondaryVertexHighEffBTag;
   vector<double>  *PFJetSimpleSecondaryVertexHighPurBTag;
   vector<double>  *PFJetSoftElectronByIP3dBTag;
   vector<double>  *PFJetSoftElectronByPtBTag;
   vector<double>  *PFJetSoftMuonBTag;
   vector<double>  *PFJetSoftMuonByIP3dBTag;
   vector<double>  *PFJetSoftMuonByPtBTag;
   vector<double>  *PFJetTrackCountingHighEffBTag;
   vector<double>  *PFJetTrackCountingHighPurBTag;
   vector<double>  *PFMET;
   vector<double>  *PFMETPhi;
   vector<double>  *PFMETSig;
   vector<double>  *PFMETSigMatrixDXX;
   vector<double>  *PFMETSigMatrixDXY;
   vector<double>  *PFMETSigMatrixDYX;
   vector<double>  *PFMETSigMatrixDYY;
   vector<double>  *PFSumET;
   vector<double>  *PFMETPhiType01Cor;
   vector<double>  *PFMETSigMatrixDXXType01Cor;
   vector<double>  *PFMETSigMatrixDXYType01Cor;
   vector<double>  *PFMETSigMatrixDYXType01Cor;
   vector<double>  *PFMETSigMatrixDYYType01Cor;
   vector<double>  *PFMETSigType01Cor;
   vector<double>  *PFMETType01Cor;
   vector<double>  *PFSumETType01Cor;
   vector<double>  *PFMETPhiType01XYCor;
   vector<double>  *PFMETSigMatrixDXXType01XYCor;
   vector<double>  *PFMETSigMatrixDXYType01XYCor;
   vector<double>  *PFMETSigMatrixDYXType01XYCor;
   vector<double>  *PFMETSigMatrixDYYType01XYCor;
   vector<double>  *PFMETSigType01XYCor;
   vector<double>  *PFMETType01XYCor;
   vector<double>  *PFSumETType01XYCor;
   vector<double>  *PFMETPhiType1Cor;
   vector<double>  *PFMETSigMatrixDXXType1Cor;
   vector<double>  *PFMETSigMatrixDXYType1Cor;
   vector<double>  *PFMETSigMatrixDYXType1Cor;
   vector<double>  *PFMETSigMatrixDYYType1Cor;
   vector<double>  *PFMETSigType1Cor;
   vector<double>  *PFMETType1Cor;
   vector<double>  *PFSumETType1Cor;
   vector<double>  *PhotonAlpha;
   vector<double>  *PhotonChi2ConvPhot;
   vector<double>  *PhotonDPhiTracksAtVtxConvPhot;
   vector<double>  *PhotonDistOfMinApproachConvPhot;
   vector<double>  *PhotonE2OverE9;
   vector<double>  *PhotonE3x3;
   vector<double>  *PhotonE4SwissCross;
   vector<double>  *PhotonE5x5;
   vector<double>  *PhotonEOverPConvPhot;
   vector<double>  *PhotonEcalIsoDR03;
   vector<double>  *PhotonEcalIsoDR04;
   vector<double>  *PhotonEnergy;
   vector<double>  *PhotonEta;
   vector<double>  *PhotonHcalIsoDR03;
   vector<double>  *PhotonHcalIsoDR03FullCone;
   vector<double>  *PhotonHcalIsoDR04;
   vector<double>  *PhotonHcalIsoDR04FullCone;
   vector<double>  *PhotonHoE;
   vector<double>  *PhotonNDofConvPhot;
   vector<double>  *PhotonPairCotThetaSeparationConvPhot;
   vector<double>  *PhotonPairInvariantMassConvPhot;
   vector<double>  *PhotonPairMomentumxConvPhot;
   vector<double>  *PhotonPairMomentumyConvPhot;
   vector<double>  *PhotonPairMomentumzConvPhot;
   vector<double>  *PhotonPhi;
   vector<double>  *PhotonPt;
   vector<double>  *PhotonSCenergy;
   vector<double>  *PhotonSCeta;
   vector<double>  *PhotonSCphi;
   vector<double>  *PhotonSCseedEnergy;
   vector<double>  *PhotonSEtaEta;
   vector<double>  *PhotonSEtaPhi;
   vector<double>  *PhotonSMajMaj;
   vector<double>  *PhotonSMinMin;
   vector<double>  *PhotonSPhiPhi;
   vector<double>  *PhotonSigmaIEtaIEta;
   vector<double>  *PhotonTimeSeed;
   vector<double>  *PhotonTrkIsoHollowDR03;
   vector<double>  *PhotonTrkIsoHollowDR04;
   vector<double>  *PhotonTrkIsoSolidDR03;
   vector<double>  *PhotonTrkIsoSolidDR04;
   vector<double>  *PhotonXVtxConvPhot;
   vector<double>  *PhotonYVtxConvPhot;
   vector<double>  *PhotonZVtxConvPhot;
   vector<double>  *TCMET;
   vector<double>  *TCMETPhi;
   vector<double>  *TCSumET;
   vector<double>  *VertexChi2;
   vector<double>  *VertexNDF;
   vector<double>  *VertexRho;
   vector<double>  *VertexX;
   vector<double>  *VertexXErr;
   vector<double>  *VertexY;
   vector<double>  *VertexYErr;
   vector<double>  *VertexZ;
   vector<double>  *VertexZErr;
   vector<float>   *PileUpInteractionsTrue;
   vector<vector<float> > *HLTFilterObjEta;
   vector<vector<float> > *HLTFilterObjPhi;
   vector<vector<float> > *HLTFilterObjPt;
   vector<int>     *ElectronCharge;
   vector<int>     *ElectronClassif;
   vector<int>     *ElectronMissingHits;
   vector<int>     *ElectronMissingHitsEG;
   vector<int>     *ElectronNumberOfBrems;
   vector<int>     *ElectronOverlaps;
   vector<int>     *ElectronPassEGammaIDEoP;
   vector<int>     *ElectronPassEGammaIDLoose;
   vector<int>     *ElectronPassEGammaIDMedium;
   vector<int>     *ElectronPassEGammaIDTight;
   vector<int>     *ElectronPassEGammaIDTrigTight;
   vector<int>     *ElectronPassEGammaIDTrigWP70;
   vector<int>     *ElectronPassEGammaIDVeto;
   vector<int>     *ElectronPassId;
   vector<int>     *ElectronPassIsoPAT;
   vector<int>     *ElectronVtxIndex;
   vector<int>     *GenWElectronMotherIndex;
   vector<int>     *GenWElectronNumDaught;
   vector<int>     *GenWElectronPdgId;
   vector<int>     *GenWElectronStatus;
   vector<int>     *GenWElectronTauDecayMode;
   vector<int>     *GenZElectronMotherIndex;
   vector<int>     *GenZElectronNumDaught;
   vector<int>     *GenZElectronPdgId;
   vector<int>     *GenZElectronStatus;
   vector<int>     *GenZElectronTauDecayMode;
   vector<int>     *PileUpInteractions;
   vector<int>     *PileUpOriginBX;
   vector<int>     *GenWMuMotherIndex;
   vector<int>     *GenWMuNumDaught;
   vector<int>     *GenWMuPdgId;
   vector<int>     *GenWMuStatus;
   vector<int>     *GenWMuTauDecayMode;
   vector<int>     *GenZMuMotherIndex;
   vector<int>     *GenZMuNumDaught;
   vector<int>     *GenZMuPdgId;
   vector<int>     *GenZMuStatus;
   vector<int>     *GenZMuTauDecayMode;
   vector<int>     *GenParticleMotherIndex;
   vector<int>     *GenParticleNumDaught;
   vector<int>     *GenParticlePdgId;
   vector<int>     *GenParticleStatus;
   vector<int>     *GenParticleTauDecayMode;
   vector<int>     *GenWTauMotherIndex;
   vector<int>     *GenWTauNumDaught;
   vector<int>     *GenWTauPdgId;
   vector<int>     *GenWTauStatus;
   vector<int>     *GenWTauTauDecayMode;
   vector<int>     *GenZTauMotherIndex;
   vector<int>     *GenZTauNumDaught;
   vector<int>     *GenZTauPdgId;
   vector<int>     *GenZTauStatus;
   vector<int>     *GenZTauTauDecayMode;
   vector<int>     *HPSTauCharge;
   vector<int>     *HPSTauDecayMode;
   vector<int>     *HPSTauIsCaloTau;
   vector<int>     *HPSTauIsPFTau;
   vector<int>     *HPSTauVtxIndex;
   vector<int>     *MuonBestTrackVtxIndex;
   vector<int>     *MuonCharge;
   vector<int>     *MuonCocktailCharge;
   vector<int>     *MuonCocktailRefitID;
   vector<int>     *MuonCocktailTrkHits;
   vector<int>     *MuonGlobalTrkValidHits;
   vector<int>     *MuonIsGlobal;
   vector<int>     *MuonIsPF;
   vector<int>     *MuonIsTracker;
   vector<int>     *MuonPassID;
   vector<int>     *MuonPixelHits;
   vector<int>     *MuonSegmentMatches;
   vector<int>     *MuonStationMatches;
   vector<int>     *MuonTrackLayersWithMeasurement;
   vector<int>     *MuonTrkHits;
   vector<int>     *MuonTrkHitsTrackerOnly;
   vector<int>     *MuonTrkPixelHits;
   vector<int>     *MuonVtxIndex;
   vector<int>     *PFCandChargeLeptLink;
   vector<int>     *PFJetBestVertexTrackAssociationIndex;
   vector<int>     *PFJetChargedHadronMultiplicity;
   vector<int>     *PFJetChargedMultiplicity;
   vector<int>     *PFJetClosestVertex3DIndex;
   vector<int>     *PFJetClosestVertexXYIndex;
   vector<int>     *PFJetClosestVertexZIndex;
   vector<int>     *PFJetElectronMultiplicity;
   vector<int>     *PFJetHFEMMultiplicity;
   vector<int>     *PFJetHFHadronMultiplicity;
   vector<int>     *PFJetMuonMultiplicity;
   vector<int>     *PFJetNConstituents;
   vector<int>     *PFJetNeutralHadronMultiplicity;
   vector<int>     *PFJetNeutralMultiplicity;
   vector<int>     *PFJetPartonFlavour;
   vector<int>     *PFJetPassLooseID;
   vector<int>     *PFJetPassTightID;
   vector<int>     *PFJetPhotonMultiplicity;
   vector<int>     *PhotonNTracksConvPhot;
   vector<int>     *HLTInsideDatasetTriggerPrescales;
   vector<int>     *HLTOutsideDatasetTriggerPrescales;
   vector<int>     *L1PhysBits;
   vector<int>     *L1TechBits;
   vector<int>     *VertexNTracks;
   vector<int>     *VertexNTracksW05;
   vector<vector<int> > *HLTFilterObjId;
   UInt_t          bunch;
   UInt_t          event;
   UInt_t          ls;
   UInt_t          orbit;
   UInt_t          run;
   UInt_t          ProcessID;

   // List of branches
   TBranch        *b_HLTKey;   //!
   TBranch        *b_HLTInsideDatasetTriggerNames;   //!
   TBranch        *b_HLTOutsideDatasetTriggerNames;   //!
   TBranch        *b_HLTFilterName;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_isBPTX0;   //!
   TBranch        *b_isBSCBeamHalo;   //!
   TBranch        *b_isBSCMinBias;   //!
   TBranch        *b_isBeamScraping;   //!
   TBranch        *b_isPhysDeclared;   //!
   TBranch        *b_isPrimaryVertex;   //!
   TBranch        *b_isTrackingFailure;   //!
   TBranch        *b_passBadEESupercrystalFilter;   //!
   TBranch        *b_passBeamHaloFilterLoose;   //!
   TBranch        *b_passBeamHaloFilterTight;   //!
   TBranch        *b_passCaloBoundaryDRFilter;   //!
   TBranch        *b_passEcalDeadCellBoundaryEnergyFilter;   //!
   TBranch        *b_passEcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_passEcalLaserCorrFilter;   //!
   TBranch        *b_passEcalMaskedCellDRFilter;   //!
   TBranch        *b_passHBHENoiseFilter;   //!
   TBranch        *b_passLogErrorTooManyClusters;   //!
   TBranch        *b_passManyStripClus53X;   //!
   TBranch        *b_passTooManyStripClus53X;   //!
   TBranch        *b_passTrackingFailureFilter;   //!
   TBranch        *b_hasVeryForwardPFMuon;   //!
   TBranch        *b_hasJetWithBadUnc;   //!
   TBranch        *b_ElectronGsfCtfCharge;   //!
   TBranch        *b_ElectronGsfCtfScPixCharge;   //!
   TBranch        *b_ElectronGsfScPixCharge;   //!
   TBranch        *b_ElectronHLTDoubleEleMatched;   //!
   TBranch        *b_ElectronHLTSingleEleMatched;   //!
   TBranch        *b_ElectronHLTSingleEleWP80Matched;   //!
   TBranch        *b_ElectronHasEcalDrivenSeed;   //!
   TBranch        *b_ElectronHasMatchedConvPhot;   //!
   TBranch        *b_ElectronHasTrackerDrivenSeed;   //!
   TBranch        *b_ElectronIsEB;   //!
   TBranch        *b_ElectronIsEE;   //!
   TBranch        *b_MuonHLTSingleIsoMuonMatched;   //!
   TBranch        *b_MuonHLTSingleMuonMatched;   //!
   TBranch        *b_PhotonHasMatchedConvPhot;   //!
   TBranch        *b_PhotonHasMatchedPromptEle;   //!
   TBranch        *b_PhotonHasPixelSeed;   //!
   TBranch        *b_PhotonIsEBEEGap;   //!
   TBranch        *b_PhotonIsEBGap;   //!
   TBranch        *b_PhotonIsEEGap;   //!
   TBranch        *b_HLTInsideDatasetTriggerDecisions;   //!
   TBranch        *b_HLTOutsideDatasetTriggerDecisions;   //!
   TBranch        *b_VertexIsFake;   //!
   TBranch        *b_rhoForHEEP;   //!
   TBranch        *b_rhoJets;   //!
   TBranch        *b_rhoJetsCCPU;   //!
   TBranch        *b_rhoJetsCN;   //!
   TBranch        *b_rhoJetsCNT;   //!
   TBranch        *b_time;   //!
   TBranch        *b_PtHat;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_CaloMET;   //!
   TBranch        *b_CaloMETPhi;   //!
   TBranch        *b_CaloMETPhiUncorr;   //!
   TBranch        *b_CaloMETUncorr;   //!
   TBranch        *b_CaloSumET;   //!
   TBranch        *b_CaloSumETUncorr;   //!
   TBranch        *b_CaloMETPhiType1Cor;   //!
   TBranch        *b_CaloMETPhiUncorrType1Cor;   //!
   TBranch        *b_CaloMETType1Cor;   //!
   TBranch        *b_CaloMETUncorrType1Cor;   //!
   TBranch        *b_CaloSumETType1Cor;   //!
   TBranch        *b_CaloSumETUncorrType1Cor;   //!
   TBranch        *b_ElectronBeamSpotDXY;   //!
   TBranch        *b_ElectronBeamSpotDXYError;   //!
   TBranch        *b_ElectronCaloEnergy;   //!
   TBranch        *b_ElectronConvFitProb;   //!
   TBranch        *b_ElectronDCotTheta;   //!
   TBranch        *b_ElectronDeltaEtaTrkSC;   //!
   TBranch        *b_ElectronDeltaPhiTrkSC;   //!
   TBranch        *b_ElectronDist;   //!
   TBranch        *b_ElectronE1x5OverE5x5;   //!
   TBranch        *b_ElectronE2x5OverE5x5;   //!
   TBranch        *b_ElectronESuperClusterOverP;   //!
   TBranch        *b_ElectronEcalIsoDR03;   //!
   TBranch        *b_ElectronEcalIsoPAT;   //!
   TBranch        *b_ElectronEnergy;   //!
   TBranch        *b_ElectronEta;   //!
   TBranch        *b_ElectronFbrem;   //!
   TBranch        *b_ElectronHLTDoubleEleMatchEta;   //!
   TBranch        *b_ElectronHLTDoubleEleMatchPhi;   //!
   TBranch        *b_ElectronHLTDoubleEleMatchPt;   //!
   TBranch        *b_ElectronHLTSingleEleMatchEta;   //!
   TBranch        *b_ElectronHLTSingleEleMatchPhi;   //!
   TBranch        *b_ElectronHLTSingleEleMatchPt;   //!
   TBranch        *b_ElectronHLTSingleEleWP80MatchEta;   //!
   TBranch        *b_ElectronHLTSingleEleWP80MatchPhi;   //!
   TBranch        *b_ElectronHLTSingleEleWP80MatchPt;   //!
   TBranch        *b_ElectronHcalIsoD1DR03;   //!
   TBranch        *b_ElectronHcalIsoD2DR03;   //!
   TBranch        *b_ElectronHcalIsoDR03;   //!
   TBranch        *b_ElectronHcalIsoDR03FullCone;   //!
   TBranch        *b_ElectronHcalIsoPAT;   //!
   TBranch        *b_ElectronHoE;   //!
   TBranch        *b_ElectronLeadVtxDistXY;   //!
   TBranch        *b_ElectronLeadVtxDistZ;   //!
   TBranch        *b_ElectronMatchedGenParticleEta;   //!
   TBranch        *b_ElectronMatchedGenParticlePhi;   //!
   TBranch        *b_ElectronMatchedGenParticlePt;   //!
   TBranch        *b_ElectronPFChargedHadronIso03;   //!
   TBranch        *b_ElectronPFChargedHadronIso04;   //!
   TBranch        *b_ElectronPFNeutralHadronIso03;   //!
   TBranch        *b_ElectronPFNeutralHadronIso04;   //!
   TBranch        *b_ElectronPFPhotonIso03;   //!
   TBranch        *b_ElectronPFPhotonIso04;   //!
   TBranch        *b_ElectronPhi;   //!
   TBranch        *b_ElectronPrimaryVertexDXY;   //!
   TBranch        *b_ElectronPrimaryVertexDXYError;   //!
   TBranch        *b_ElectronPt;   //!
   TBranch        *b_ElectronPtHeep;   //!
   TBranch        *b_ElectronRelIsoPAT;   //!
   TBranch        *b_ElectronSCEta;   //!
   TBranch        *b_ElectronSCPhi;   //!
   TBranch        *b_ElectronSCPt;   //!
   TBranch        *b_ElectronSCRawEnergy;   //!
   TBranch        *b_ElectronSigmaEtaEta;   //!
   TBranch        *b_ElectronSigmaIEtaIEta;   //!
   TBranch        *b_ElectronTrackPt;   //!
   TBranch        *b_ElectronTrackValidFractionOfHits;   //!
   TBranch        *b_ElectronTrackVx;   //!
   TBranch        *b_ElectronTrackVy;   //!
   TBranch        *b_ElectronTrackVz;   //!
   TBranch        *b_ElectronTrkIsoDR03;   //!
   TBranch        *b_ElectronTrkIsoPAT;   //!
   TBranch        *b_ElectronVtxDistXY;   //!
   TBranch        *b_ElectronVtxDistZ;   //!
   TBranch        *b_GenWElectronEnergy;   //!
   TBranch        *b_GenWElectronEta;   //!
   TBranch        *b_GenWElectronP;   //!
   TBranch        *b_GenWElectronPhi;   //!
   TBranch        *b_GenWElectronPt;   //!
   TBranch        *b_GenWElectronPx;   //!
   TBranch        *b_GenWElectronPy;   //!
   TBranch        *b_GenWElectronPz;   //!
   TBranch        *b_GenWElectronTauVisibleEta;   //!
   TBranch        *b_GenWElectronTauVisiblePhi;   //!
   TBranch        *b_GenWElectronTauVisiblePt;   //!
   TBranch        *b_GenWElectronVX;   //!
   TBranch        *b_GenWElectronVY;   //!
   TBranch        *b_GenWElectronVZ;   //!
   TBranch        *b_GenZElectronEnergy;   //!
   TBranch        *b_GenZElectronEta;   //!
   TBranch        *b_GenZElectronP;   //!
   TBranch        *b_GenZElectronPhi;   //!
   TBranch        *b_GenZElectronPt;   //!
   TBranch        *b_GenZElectronPx;   //!
   TBranch        *b_GenZElectronPy;   //!
   TBranch        *b_GenZElectronPz;   //!
   TBranch        *b_GenZElectronTauVisibleEta;   //!
   TBranch        *b_GenZElectronTauVisiblePhi;   //!
   TBranch        *b_GenZElectronTauVisiblePt;   //!
   TBranch        *b_GenZElectronVX;   //!
   TBranch        *b_GenZElectronVY;   //!
   TBranch        *b_GenZElectronVZ;   //!
   TBranch        *b_PDFCTEQWeights;   //!
   TBranch        *b_PDFMSTWWeights;   //!
   TBranch        *b_PDFNNPDFWeights;   //!
   TBranch        *b_GenJetEMF;   //!
   TBranch        *b_GenJetEnergy;   //!
   TBranch        *b_GenJetEta;   //!
   TBranch        *b_GenJetHADF;   //!
   TBranch        *b_GenJetP;   //!
   TBranch        *b_GenJetPhi;   //!
   TBranch        *b_GenJetPt;   //!
   TBranch        *b_GenMETCalo;   //!
   TBranch        *b_GenMETPhiCalo;   //!
   TBranch        *b_GenSumETCalo;   //!
   TBranch        *b_GenMETPhiTrue;   //!
   TBranch        *b_GenMETTrue;   //!
   TBranch        *b_GenSumETTrue;   //!
   TBranch        *b_GenWMuEnergy;   //!
   TBranch        *b_GenWMuEta;   //!
   TBranch        *b_GenWMuP;   //!
   TBranch        *b_GenWMuPhi;   //!
   TBranch        *b_GenWMuPt;   //!
   TBranch        *b_GenWMuPx;   //!
   TBranch        *b_GenWMuPy;   //!
   TBranch        *b_GenWMuPz;   //!
   TBranch        *b_GenWMuTauVisibleEta;   //!
   TBranch        *b_GenWMuTauVisiblePhi;   //!
   TBranch        *b_GenWMuTauVisiblePt;   //!
   TBranch        *b_GenWMuVX;   //!
   TBranch        *b_GenWMuVY;   //!
   TBranch        *b_GenWMuVZ;   //!
   TBranch        *b_GenZMuEnergy;   //!
   TBranch        *b_GenZMuEta;   //!
   TBranch        *b_GenZMuP;   //!
   TBranch        *b_GenZMuPhi;   //!
   TBranch        *b_GenZMuPt;   //!
   TBranch        *b_GenZMuPx;   //!
   TBranch        *b_GenZMuPy;   //!
   TBranch        *b_GenZMuPz;   //!
   TBranch        *b_GenZMuTauVisibleEta;   //!
   TBranch        *b_GenZMuTauVisiblePhi;   //!
   TBranch        *b_GenZMuTauVisiblePt;   //!
   TBranch        *b_GenZMuVX;   //!
   TBranch        *b_GenZMuVY;   //!
   TBranch        *b_GenZMuVZ;   //!
   TBranch        *b_GenParticleEnergy;   //!
   TBranch        *b_GenParticleEta;   //!
   TBranch        *b_GenParticleP;   //!
   TBranch        *b_GenParticlePhi;   //!
   TBranch        *b_GenParticlePt;   //!
   TBranch        *b_GenParticlePx;   //!
   TBranch        *b_GenParticlePy;   //!
   TBranch        *b_GenParticlePz;   //!
   TBranch        *b_GenParticleTauVisibleEta;   //!
   TBranch        *b_GenParticleTauVisiblePhi;   //!
   TBranch        *b_GenParticleTauVisiblePt;   //!
   TBranch        *b_GenParticleVX;   //!
   TBranch        *b_GenParticleVY;   //!
   TBranch        *b_GenParticleVZ;   //!
   TBranch        *b_GenWTauEnergy;   //!
   TBranch        *b_GenWTauEta;   //!
   TBranch        *b_GenWTauP;   //!
   TBranch        *b_GenWTauPhi;   //!
   TBranch        *b_GenWTauPt;   //!
   TBranch        *b_GenWTauPx;   //!
   TBranch        *b_GenWTauPy;   //!
   TBranch        *b_GenWTauPz;   //!
   TBranch        *b_GenWTauTauVisibleEta;   //!
   TBranch        *b_GenWTauTauVisiblePhi;   //!
   TBranch        *b_GenWTauTauVisiblePt;   //!
   TBranch        *b_GenWTauVX;   //!
   TBranch        *b_GenWTauVY;   //!
   TBranch        *b_GenWTauVZ;   //!
   TBranch        *b_GenZTauEnergy;   //!
   TBranch        *b_GenZTauEta;   //!
   TBranch        *b_GenZTauP;   //!
   TBranch        *b_GenZTauPhi;   //!
   TBranch        *b_GenZTauPt;   //!
   TBranch        *b_GenZTauPx;   //!
   TBranch        *b_GenZTauPy;   //!
   TBranch        *b_GenZTauPz;   //!
   TBranch        *b_GenZTauTauVisibleEta;   //!
   TBranch        *b_GenZTauTauVisiblePhi;   //!
   TBranch        *b_GenZTauTauVisiblePt;   //!
   TBranch        *b_GenZTauVX;   //!
   TBranch        *b_GenZTauVY;   //!
   TBranch        *b_GenZTauVZ;   //!
   TBranch        *b_HPSTauAgainstElectronDeadECALDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronLooseDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronLooseMVA2Discr;   //!
   TBranch        *b_HPSTauAgainstElectronLooseMVA3Discr;   //!
   TBranch        *b_HPSTauAgainstElectronMVA2categoryDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMVA2rawDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMVA3categoryDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMVA3rawDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMVADiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMediumDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronMediumMVA2Discr;   //!
   TBranch        *b_HPSTauAgainstElectronMediumMVA3Discr;   //!
   TBranch        *b_HPSTauAgainstElectronTightDiscr;   //!
   TBranch        *b_HPSTauAgainstElectronTightMVA2Discr;   //!
   TBranch        *b_HPSTauAgainstElectronTightMVA3Discr;   //!
   TBranch        *b_HPSTauAgainstElectronVLooseMVA2Discr;   //!
   TBranch        *b_HPSTauAgainstElectronVTightMVA3Discr;   //!
   TBranch        *b_HPSTauAgainstMuonLoose2Discr;   //!
   TBranch        *b_HPSTauAgainstMuonLooseDiscr;   //!
   TBranch        *b_HPSTauAgainstMuonMedium2Discr;   //!
   TBranch        *b_HPSTauAgainstMuonMediumDiscr;   //!
   TBranch        *b_HPSTauAgainstMuonTight2Discr;   //!
   TBranch        *b_HPSTauAgainstMuonTightDiscr;   //!
   TBranch        *b_HPSTauBremsRecoveryEOverPLead;   //!
   TBranch        *b_HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr;   //!
   TBranch        *b_HPSTauDecayModeFindingDiscr;   //!
   TBranch        *b_HPSTauEcalStripSumEOverPLead;   //!
   TBranch        *b_HPSTauEmFraction;   //!
   TBranch        *b_HPSTauEt;   //!
   TBranch        *b_HPSTauEta;   //!
   TBranch        *b_HPSTauEtaLeadCharged;   //!
   TBranch        *b_HPSTauEtaetaMoment;   //!
   TBranch        *b_HPSTauEtaphiMoment;   //!
   TBranch        *b_HPSTauHcal3x3OverPLead;   //!
   TBranch        *b_HPSTauHcalMaxOverPLead;   //!
   TBranch        *b_HPSTauHcalTotOverPLead;   //!
   TBranch        *b_HPSTauIsolationMVArawDiscr;   //!
   TBranch        *b_HPSTauIsolationPFChargedHadrCandsPtSum;   //!
   TBranch        *b_HPSTauIsolationPFGammaCandsEtSum;   //!
   TBranch        *b_HPSTauLeadPFChargedHadrCandsignedSipt;   //!
   TBranch        *b_HPSTauLeadVtxDistXY;   //!
   TBranch        *b_HPSTauLeadVtxDistZ;   //!
   TBranch        *b_HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr;   //!
   TBranch        *b_HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauLooseIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauLooseIsolationDiscr;   //!
   TBranch        *b_HPSTauLooseIsolationMVA2Discr;   //!
   TBranch        *b_HPSTauLooseIsolationMVADiscr;   //!
   TBranch        *b_HPSTauMatchedGenJetEta;   //!
   TBranch        *b_HPSTauMatchedGenJetPhi;   //!
   TBranch        *b_HPSTauMatchedGenJetPt;   //!
   TBranch        *b_HPSTauMatchedGenParticleEta;   //!
   TBranch        *b_HPSTauMatchedGenParticlePhi;   //!
   TBranch        *b_HPSTauMatchedGenParticlePt;   //!
   TBranch        *b_HPSTauMaximumHCALPFClusterEt;   //!
   TBranch        *b_HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr;   //!
   TBranch        *b_HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauMediumIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauMediumIsolationDiscr;   //!
   TBranch        *b_HPSTauMediumIsolationMVA2Discr;   //!
   TBranch        *b_HPSTauMediumIsolationMVADiscr;   //!
   TBranch        *b_HPSTauPhi;   //!
   TBranch        *b_HPSTauPhiLeadCharged;   //!
   TBranch        *b_HPSTauPhiphiMoment;   //!
   TBranch        *b_HPSTauPt;   //!
   TBranch        *b_HPSTauPtLeadCharged;   //!
   TBranch        *b_HPSTauSignalPFChargedHadrCandsCount;   //!
   TBranch        *b_HPSTauSignalPFChargedHadrCandsEta;   //!
   TBranch        *b_HPSTauSignalPFChargedHadrCandsPhi;   //!
   TBranch        *b_HPSTauSignalPFChargedHadrCandsPt;   //!
   TBranch        *b_HPSTauSignalPFGammaCandsCount;   //!
   TBranch        *b_HPSTauSignalPFGammaCandsEta;   //!
   TBranch        *b_HPSTauSignalPFGammaCandsPhi;   //!
   TBranch        *b_HPSTauSignalPFGammaCandsPt;   //!
   TBranch        *b_HPSTauSignalPFNeutrHadrCandsCount;   //!
   TBranch        *b_HPSTauSignalPFNeutrHadrCandsEta;   //!
   TBranch        *b_HPSTauSignalPFNeutrHadrCandsPhi;   //!
   TBranch        *b_HPSTauSignalPFNeutrHadrCandsPt;   //!
   TBranch        *b_HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr;   //!
   TBranch        *b_HPSTauTightCombinedIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauTightIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauTightIsolationDiscr;   //!
   TBranch        *b_HPSTauTightIsolationMVA2Discr;   //!
   TBranch        *b_HPSTauTightIsolationMVADiscr;   //!
   TBranch        *b_HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauVLooseIsolationDeltaBetaCorrDiscr;   //!
   TBranch        *b_HPSTauVLooseIsolationDiscr;   //!
   TBranch        *b_HPSTauVtxDistXY;   //!
   TBranch        *b_HPSTauVtxDistZ;   //!
   TBranch        *b_MuonBackToBackCompatibility;   //!
   TBranch        *b_MuonBeamSpotDXY;   //!
   TBranch        *b_MuonBeamSpotDXYError;   //!
   TBranch        *b_MuonBestTrackVtxDistXY;   //!
   TBranch        *b_MuonBestTrackVtxDistZ;   //!
   TBranch        *b_MuonCocktailEta;   //!
   TBranch        *b_MuonCocktailEtaError;   //!
   TBranch        *b_MuonCocktailGlobalChi2;   //!
   TBranch        *b_MuonCocktailP;   //!
   TBranch        *b_MuonCocktailPhi;   //!
   TBranch        *b_MuonCocktailPhiError;   //!
   TBranch        *b_MuonCocktailPt;   //!
   TBranch        *b_MuonCocktailPtError;   //!
   TBranch        *b_MuonCocktailQOverPError;   //!
   TBranch        *b_MuonCocktailTrkD0;   //!
   TBranch        *b_MuonCocktailTrkD0Error;   //!
   TBranch        *b_MuonCocktailTrkDz;   //!
   TBranch        *b_MuonCocktailTrkDzError;   //!
   TBranch        *b_MuonCocktailTrkValidFractionOfHits;   //!
   TBranch        *b_MuonCosmicCompatibility;   //!
   TBranch        *b_MuonEcalIso;   //!
   TBranch        *b_MuonEcalVetoIso;   //!
   TBranch        *b_MuonEnergy;   //!
   TBranch        *b_MuonEta;   //!
   TBranch        *b_MuonEtaError;   //!
   TBranch        *b_MuonGlobalChi2;   //!
   TBranch        *b_MuonHLTSingleIsoMuonMatchEta;   //!
   TBranch        *b_MuonHLTSingleIsoMuonMatchPhi;   //!
   TBranch        *b_MuonHLTSingleIsoMuonMatchPt;   //!
   TBranch        *b_MuonHLTSingleMuonMatchEta;   //!
   TBranch        *b_MuonHLTSingleMuonMatchPhi;   //!
   TBranch        *b_MuonHLTSingleMuonMatchPt;   //!
   TBranch        *b_MuonHOIso;   //!
   TBranch        *b_MuonHcalIso;   //!
   TBranch        *b_MuonHcalVetoIso;   //!
   TBranch        *b_MuonMatchedGenParticleEta;   //!
   TBranch        *b_MuonMatchedGenParticlePhi;   //!
   TBranch        *b_MuonMatchedGenParticlePt;   //!
   TBranch        *b_MuonOverlapCompatibility;   //!
   TBranch        *b_MuonP;   //!
   TBranch        *b_MuonPFIsoR03ChargedHadron;   //!
   TBranch        *b_MuonPFIsoR03ChargedParticle;   //!
   TBranch        *b_MuonPFIsoR03NeutralHadron;   //!
   TBranch        *b_MuonPFIsoR03NeutralHadronHT;   //!
   TBranch        *b_MuonPFIsoR03PU;   //!
   TBranch        *b_MuonPFIsoR03Photon;   //!
   TBranch        *b_MuonPFIsoR03PhotonHT;   //!
   TBranch        *b_MuonPFIsoR04ChargedHadron;   //!
   TBranch        *b_MuonPFIsoR04ChargedParticle;   //!
   TBranch        *b_MuonPFIsoR04NeutralHadron;   //!
   TBranch        *b_MuonPFIsoR04NeutralHadronHT;   //!
   TBranch        *b_MuonPFIsoR04PU;   //!
   TBranch        *b_MuonPFIsoR04Photon;   //!
   TBranch        *b_MuonPFIsoR04PhotonHT;   //!
   TBranch        *b_MuonPhi;   //!
   TBranch        *b_MuonPhiError;   //!
   TBranch        *b_MuonPrimaryVertexDXY;   //!
   TBranch        *b_MuonPrimaryVertexDXYError;   //!
   TBranch        *b_MuonPt;   //!
   TBranch        *b_MuonPtError;   //!
   TBranch        *b_MuonQOverPError;   //!
   TBranch        *b_MuonTimeCompatibility;   //!
   TBranch        *b_MuonTrackChi2;   //!
   TBranch        *b_MuonTrackerIsoSumPT;   //!
   TBranch        *b_MuonTrkD0;   //!
   TBranch        *b_MuonTrkD0Error;   //!
   TBranch        *b_MuonTrkDz;   //!
   TBranch        *b_MuonTrkDzError;   //!
   TBranch        *b_MuonTrkEta;   //!
   TBranch        *b_MuonTrkEtaError;   //!
   TBranch        *b_MuonTrkIso;   //!
   TBranch        *b_MuonTrkPhi;   //!
   TBranch        *b_MuonTrkPhiError;   //!
   TBranch        *b_MuonTrkPt;   //!
   TBranch        *b_MuonTrkPtError;   //!
   TBranch        *b_MuonTrkValidFractionOfHits;   //!
   TBranch        *b_MuonTrkVx;   //!
   TBranch        *b_MuonTrkVy;   //!
   TBranch        *b_MuonTrkVz;   //!
   TBranch        *b_MuonVtxDistXY;   //!
   TBranch        *b_MuonVtxDistZ;   //!
   TBranch        *b_PFCandEnergyLeptLink;   //!
   TBranch        *b_PFCandEtaLeptLink;   //!
   TBranch        *b_PFCandPhiLeptLink;   //!
   TBranch        *b_PFCandPtLeptLink;   //!
   TBranch        *b_PFJetBestVertexTrackAssociationFactor;   //!
   TBranch        *b_PFJetBeta;   //!
   TBranch        *b_PFJetBetaClassic;   //!
   TBranch        *b_PFJetBetaStar;   //!
   TBranch        *b_PFJetBetaStarClassic;   //!
   TBranch        *b_PFJetChargedEmEnergyFraction;   //!
   TBranch        *b_PFJetChargedHadronEnergyFraction;   //!
   TBranch        *b_PFJetChargedMuEnergyFraction;   //!
   TBranch        *b_PFJetClosestVertexWeighted3DSeparation;   //!
   TBranch        *b_PFJetClosestVertexWeightedXYSeparation;   //!
   TBranch        *b_PFJetClosestVertexWeightedZSeparation;   //!
   TBranch        *b_PFJetCombinedInclusiveSecondaryVertexBTag;   //!
   TBranch        *b_PFJetCombinedMVABTag;   //!
   TBranch        *b_PFJetCombinedSecondaryVertexBTag;   //!
   TBranch        *b_PFJetCombinedSecondaryVertexMVABTag;   //!
   TBranch        *b_PFJetElectronEnergyFraction;   //!
   TBranch        *b_PFJetEnergy;   //!
   TBranch        *b_PFJetEnergyRaw;   //!
   TBranch        *b_PFJetEta;   //!
   TBranch        *b_PFJetHFEMEnergyFraction;   //!
   TBranch        *b_PFJetHFHadronEnergyFraction;   //!
   TBranch        *b_PFJetJECUnc;   //!
   TBranch        *b_PFJetJetBProbabilityBTag;   //!
   TBranch        *b_PFJetJetProbabilityBTag;   //!
   TBranch        *b_PFJetL1FastJetJEC;   //!
   TBranch        *b_PFJetL1OffsetJEC;   //!
   TBranch        *b_PFJetL2L3ResJEC;   //!
   TBranch        *b_PFJetL2RelJEC;   //!
   TBranch        *b_PFJetL3AbsJEC;   //!
   TBranch        *b_PFJetMuonEnergyFraction;   //!
   TBranch        *b_PFJetNeutralEmEnergyFraction;   //!
   TBranch        *b_PFJetNeutralHadronEnergyFraction;   //!
   TBranch        *b_PFJetPhi;   //!
   TBranch        *b_PFJetPhotonEnergyFraction;   //!
   TBranch        *b_PFJetPt;   //!
   TBranch        *b_PFJetPtRaw;   //!
   TBranch        *b_PFJetSimpleSecondaryVertexHighEffBTag;   //!
   TBranch        *b_PFJetSimpleSecondaryVertexHighPurBTag;   //!
   TBranch        *b_PFJetSoftElectronByIP3dBTag;   //!
   TBranch        *b_PFJetSoftElectronByPtBTag;   //!
   TBranch        *b_PFJetSoftMuonBTag;   //!
   TBranch        *b_PFJetSoftMuonByIP3dBTag;   //!
   TBranch        *b_PFJetSoftMuonByPtBTag;   //!
   TBranch        *b_PFJetTrackCountingHighEffBTag;   //!
   TBranch        *b_PFJetTrackCountingHighPurBTag;   //!
   TBranch        *b_PFMET;   //!
   TBranch        *b_PFMETPhi;   //!
   TBranch        *b_PFMETSig;   //!
   TBranch        *b_PFMETSigMatrixDXX;   //!
   TBranch        *b_PFMETSigMatrixDXY;   //!
   TBranch        *b_PFMETSigMatrixDYX;   //!
   TBranch        *b_PFMETSigMatrixDYY;   //!
   TBranch        *b_PFSumET;   //!
   TBranch        *b_PFMETPhiType01Cor;   //!
   TBranch        *b_PFMETSigMatrixDXXType01Cor;   //!
   TBranch        *b_PFMETSigMatrixDXYType01Cor;   //!
   TBranch        *b_PFMETSigMatrixDYXType01Cor;   //!
   TBranch        *b_PFMETSigMatrixDYYType01Cor;   //!
   TBranch        *b_PFMETSigType01Cor;   //!
   TBranch        *b_PFMETType01Cor;   //!
   TBranch        *b_PFSumETType01Cor;   //!
   TBranch        *b_PFMETPhiType01XYCor;   //!
   TBranch        *b_PFMETSigMatrixDXXType01XYCor;   //!
   TBranch        *b_PFMETSigMatrixDXYType01XYCor;   //!
   TBranch        *b_PFMETSigMatrixDYXType01XYCor;   //!
   TBranch        *b_PFMETSigMatrixDYYType01XYCor;   //!
   TBranch        *b_PFMETSigType01XYCor;   //!
   TBranch        *b_PFMETType01XYCor;   //!
   TBranch        *b_PFSumETType01XYCor;   //!
   TBranch        *b_PFMETPhiType1Cor;   //!
   TBranch        *b_PFMETSigMatrixDXXType1Cor;   //!
   TBranch        *b_PFMETSigMatrixDXYType1Cor;   //!
   TBranch        *b_PFMETSigMatrixDYXType1Cor;   //!
   TBranch        *b_PFMETSigMatrixDYYType1Cor;   //!
   TBranch        *b_PFMETSigType1Cor;   //!
   TBranch        *b_PFMETType1Cor;   //!
   TBranch        *b_PFSumETType1Cor;   //!
   TBranch        *b_PhotonAlpha;   //!
   TBranch        *b_PhotonChi2ConvPhot;   //!
   TBranch        *b_PhotonDPhiTracksAtVtxConvPhot;   //!
   TBranch        *b_PhotonDistOfMinApproachConvPhot;   //!
   TBranch        *b_PhotonE2OverE9;   //!
   TBranch        *b_PhotonE3x3;   //!
   TBranch        *b_PhotonE4SwissCross;   //!
   TBranch        *b_PhotonE5x5;   //!
   TBranch        *b_PhotonEOverPConvPhot;   //!
   TBranch        *b_PhotonEcalIsoDR03;   //!
   TBranch        *b_PhotonEcalIsoDR04;   //!
   TBranch        *b_PhotonEnergy;   //!
   TBranch        *b_PhotonEta;   //!
   TBranch        *b_PhotonHcalIsoDR03;   //!
   TBranch        *b_PhotonHcalIsoDR03FullCone;   //!
   TBranch        *b_PhotonHcalIsoDR04;   //!
   TBranch        *b_PhotonHcalIsoDR04FullCone;   //!
   TBranch        *b_PhotonHoE;   //!
   TBranch        *b_PhotonNDofConvPhot;   //!
   TBranch        *b_PhotonPairCotThetaSeparationConvPhot;   //!
   TBranch        *b_PhotonPairInvariantMassConvPhot;   //!
   TBranch        *b_PhotonPairMomentumxConvPhot;   //!
   TBranch        *b_PhotonPairMomentumyConvPhot;   //!
   TBranch        *b_PhotonPairMomentumzConvPhot;   //!
   TBranch        *b_PhotonPhi;   //!
   TBranch        *b_PhotonPt;   //!
   TBranch        *b_PhotonSCenergy;   //!
   TBranch        *b_PhotonSCeta;   //!
   TBranch        *b_PhotonSCphi;   //!
   TBranch        *b_PhotonSCseedEnergy;   //!
   TBranch        *b_PhotonSEtaEta;   //!
   TBranch        *b_PhotonSEtaPhi;   //!
   TBranch        *b_PhotonSMajMaj;   //!
   TBranch        *b_PhotonSMinMin;   //!
   TBranch        *b_PhotonSPhiPhi;   //!
   TBranch        *b_PhotonSigmaIEtaIEta;   //!
   TBranch        *b_PhotonTimeSeed;   //!
   TBranch        *b_PhotonTrkIsoHollowDR03;   //!
   TBranch        *b_PhotonTrkIsoHollowDR04;   //!
   TBranch        *b_PhotonTrkIsoSolidDR03;   //!
   TBranch        *b_PhotonTrkIsoSolidDR04;   //!
   TBranch        *b_PhotonXVtxConvPhot;   //!
   TBranch        *b_PhotonYVtxConvPhot;   //!
   TBranch        *b_PhotonZVtxConvPhot;   //!
   TBranch        *b_TCMET;   //!
   TBranch        *b_TCMETPhi;   //!
   TBranch        *b_TCSumET;   //!
   TBranch        *b_VertexChi2;   //!
   TBranch        *b_VertexNDF;   //!
   TBranch        *b_VertexRho;   //!
   TBranch        *b_VertexX;   //!
   TBranch        *b_VertexXErr;   //!
   TBranch        *b_VertexY;   //!
   TBranch        *b_VertexYErr;   //!
   TBranch        *b_VertexZ;   //!
   TBranch        *b_VertexZErr;   //!
   TBranch        *b_PileUpInteractionsTrue;   //!
   TBranch        *b_HLTFilterObjEta;   //!
   TBranch        *b_HLTFilterObjPhi;   //!
   TBranch        *b_HLTFilterObjPt;   //!
   TBranch        *b_ElectronCharge;   //!
   TBranch        *b_ElectronClassif;   //!
   TBranch        *b_ElectronMissingHits;   //!
   TBranch        *b_ElectronMissingHitsEG;   //!
   TBranch        *b_ElectronNumberOfBrems;   //!
   TBranch        *b_ElectronOverlaps;   //!
   TBranch        *b_ElectronPassEGammaIDEoP;   //!
   TBranch        *b_ElectronPassEGammaIDLoose;   //!
   TBranch        *b_ElectronPassEGammaIDMedium;   //!
   TBranch        *b_ElectronPassEGammaIDTight;   //!
   TBranch        *b_ElectronPassEGammaIDTrigTight;   //!
   TBranch        *b_ElectronPassEGammaIDTrigWP70;   //!
   TBranch        *b_ElectronPassEGammaIDVeto;   //!
   TBranch        *b_ElectronPassId;   //!
   TBranch        *b_ElectronPassIsoPAT;   //!
   TBranch        *b_ElectronVtxIndex;   //!
   TBranch        *b_GenWElectronMotherIndex;   //!
   TBranch        *b_GenWElectronNumDaught;   //!
   TBranch        *b_GenWElectronPdgId;   //!
   TBranch        *b_GenWElectronStatus;   //!
   TBranch        *b_GenWElectronTauDecayMode;   //!
   TBranch        *b_GenZElectronMotherIndex;   //!
   TBranch        *b_GenZElectronNumDaught;   //!
   TBranch        *b_GenZElectronPdgId;   //!
   TBranch        *b_GenZElectronStatus;   //!
   TBranch        *b_GenZElectronTauDecayMode;   //!
   TBranch        *b_PileUpInteractions;   //!
   TBranch        *b_PileUpOriginBX;   //!
   TBranch        *b_GenWMuMotherIndex;   //!
   TBranch        *b_GenWMuNumDaught;   //!
   TBranch        *b_GenWMuPdgId;   //!
   TBranch        *b_GenWMuStatus;   //!
   TBranch        *b_GenWMuTauDecayMode;   //!
   TBranch        *b_GenZMuMotherIndex;   //!
   TBranch        *b_GenZMuNumDaught;   //!
   TBranch        *b_GenZMuPdgId;   //!
   TBranch        *b_GenZMuStatus;   //!
   TBranch        *b_GenZMuTauDecayMode;   //!
   TBranch        *b_GenParticleMotherIndex;   //!
   TBranch        *b_GenParticleNumDaught;   //!
   TBranch        *b_GenParticlePdgId;   //!
   TBranch        *b_GenParticleStatus;   //!
   TBranch        *b_GenParticleTauDecayMode;   //!
   TBranch        *b_GenWTauMotherIndex;   //!
   TBranch        *b_GenWTauNumDaught;   //!
   TBranch        *b_GenWTauPdgId;   //!
   TBranch        *b_GenWTauStatus;   //!
   TBranch        *b_GenWTauTauDecayMode;   //!
   TBranch        *b_GenZTauMotherIndex;   //!
   TBranch        *b_GenZTauNumDaught;   //!
   TBranch        *b_GenZTauPdgId;   //!
   TBranch        *b_GenZTauStatus;   //!
   TBranch        *b_GenZTauTauDecayMode;   //!
   TBranch        *b_HPSTauCharge;   //!
   TBranch        *b_HPSTauDecayMode;   //!
   TBranch        *b_HPSTauIsCaloTau;   //!
   TBranch        *b_HPSTauIsPFTau;   //!
   TBranch        *b_HPSTauVtxIndex;   //!
   TBranch        *b_MuonBestTrackVtxIndex;   //!
   TBranch        *b_MuonCharge;   //!
   TBranch        *b_MuonCocktailCharge;   //!
   TBranch        *b_MuonCocktailRefitID;   //!
   TBranch        *b_MuonCocktailTrkHits;   //!
   TBranch        *b_MuonGlobalTrkValidHits;   //!
   TBranch        *b_MuonIsGlobal;   //!
   TBranch        *b_MuonIsPF;   //!
   TBranch        *b_MuonIsTracker;   //!
   TBranch        *b_MuonPassID;   //!
   TBranch        *b_MuonPixelHits;   //!
   TBranch        *b_MuonSegmentMatches;   //!
   TBranch        *b_MuonStationMatches;   //!
   TBranch        *b_MuonTrackLayersWithMeasurement;   //!
   TBranch        *b_MuonTrkHits;   //!
   TBranch        *b_MuonTrkHitsTrackerOnly;   //!
   TBranch        *b_MuonTrkPixelHits;   //!
   TBranch        *b_MuonVtxIndex;   //!
   TBranch        *b_PFCandChargeLeptLink;   //!
   TBranch        *b_PFJetBestVertexTrackAssociationIndex;   //!
   TBranch        *b_PFJetChargedHadronMultiplicity;   //!
   TBranch        *b_PFJetChargedMultiplicity;   //!
   TBranch        *b_PFJetClosestVertex3DIndex;   //!
   TBranch        *b_PFJetClosestVertexXYIndex;   //!
   TBranch        *b_PFJetClosestVertexZIndex;   //!
   TBranch        *b_PFJetElectronMultiplicity;   //!
   TBranch        *b_PFJetHFEMMultiplicity;   //!
   TBranch        *b_PFJetHFHadronMultiplicity;   //!
   TBranch        *b_PFJetMuonMultiplicity;   //!
   TBranch        *b_PFJetNConstituents;   //!
   TBranch        *b_PFJetNeutralHadronMultiplicity;   //!
   TBranch        *b_PFJetNeutralMultiplicity;   //!
   TBranch        *b_PFJetPartonFlavour;   //!
   TBranch        *b_PFJetPassLooseID;   //!
   TBranch        *b_PFJetPassTightID;   //!
   TBranch        *b_PFJetPhotonMultiplicity;   //!
   TBranch        *b_PhotonNTracksConvPhot;   //!
   TBranch        *b_HLTInsideDatasetTriggerPrescales;   //!
   TBranch        *b_HLTOutsideDatasetTriggerPrescales;   //!
   TBranch        *b_L1PhysBits;   //!
   TBranch        *b_L1TechBits;   //!
   TBranch        *b_VertexNTracks;   //!
   TBranch        *b_VertexNTracksW05;   //!
   TBranch        *b_HLTFilterObjId;   //!
   TBranch        *b_bunch;   //!
   TBranch        *b_event;   //!
   TBranch        *b_ls;   //!
   TBranch        *b_orbit;   //!
   TBranch        *b_run;   //!
   TBranch        *b_ProcessID;   //!

   MyClass_del(TTree *tree=0);
   virtual ~MyClass_del();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyClass_del_cxx
MyClass_del::MyClass_del(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("dcache:///pnfs/cms/WAX/11/store/user/fgior8/Summer12LQ_tag11/ttbar/RootTupleMakerV2_output_MC_31_1_lqn.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("dcache:///pnfs/cms/WAX/11/store/user/fgior8/Summer12LQ_tag11/ttbar/RootTupleMakerV2_output_MC_31_1_lqn.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("dcache:///pnfs/cms/WAX/11/store/user/fgior8/Summer12LQ_tag11/ttbar/RootTupleMakerV2_output_MC_31_1_lqn.root:/rootTupleTree");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

MyClass_del::~MyClass_del()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass_del::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass_del::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyClass_del::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

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
   CaloMETPhiUncorr = 0;
   CaloMETUncorr = 0;
   CaloSumET = 0;
   CaloSumETUncorr = 0;
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
   PFJetL1OffsetJEC = 0;
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
   PFMETSig = 0;
   PFMETSigMatrixDXX = 0;
   PFMETSigMatrixDXY = 0;
   PFMETSigMatrixDYX = 0;
   PFMETSigMatrixDYY = 0;
   PFSumET = 0;
   PFMETPhiType01Cor = 0;
   PFMETSigMatrixDXXType01Cor = 0;
   PFMETSigMatrixDXYType01Cor = 0;
   PFMETSigMatrixDYXType01Cor = 0;
   PFMETSigMatrixDYYType01Cor = 0;
   PFMETSigType01Cor = 0;
   PFMETType01Cor = 0;
   PFSumETType01Cor = 0;
   PFMETPhiType01XYCor = 0;
   PFMETSigMatrixDXXType01XYCor = 0;
   PFMETSigMatrixDXYType01XYCor = 0;
   PFMETSigMatrixDYXType01XYCor = 0;
   PFMETSigMatrixDYYType01XYCor = 0;
   PFMETSigType01XYCor = 0;
   PFMETType01XYCor = 0;
   PFSumETType01XYCor = 0;
   PFMETPhiType1Cor = 0;
   PFMETSigMatrixDXXType1Cor = 0;
   PFMETSigMatrixDXYType1Cor = 0;
   PFMETSigMatrixDYXType1Cor = 0;
   PFMETSigMatrixDYYType1Cor = 0;
   PFMETSigType1Cor = 0;
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
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HLTKey", &HLTKey, &b_HLTKey);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerNames", &HLTInsideDatasetTriggerNames, &b_HLTInsideDatasetTriggerNames);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerNames", &HLTOutsideDatasetTriggerNames, &b_HLTOutsideDatasetTriggerNames);
   fChain->SetBranchAddress("HLTFilterName", &HLTFilterName, &b_HLTFilterName);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("isBPTX0", &isBPTX0, &b_isBPTX0);
   fChain->SetBranchAddress("isBSCBeamHalo", &isBSCBeamHalo, &b_isBSCBeamHalo);
   fChain->SetBranchAddress("isBSCMinBias", &isBSCMinBias, &b_isBSCMinBias);
   fChain->SetBranchAddress("isBeamScraping", &isBeamScraping, &b_isBeamScraping);
   fChain->SetBranchAddress("isPhysDeclared", &isPhysDeclared, &b_isPhysDeclared);
   fChain->SetBranchAddress("isPrimaryVertex", &isPrimaryVertex, &b_isPrimaryVertex);
   fChain->SetBranchAddress("isTrackingFailure", &isTrackingFailure, &b_isTrackingFailure);
   fChain->SetBranchAddress("passBadEESupercrystalFilter", &passBadEESupercrystalFilter, &b_passBadEESupercrystalFilter);
   fChain->SetBranchAddress("passBeamHaloFilterLoose", &passBeamHaloFilterLoose, &b_passBeamHaloFilterLoose);
   fChain->SetBranchAddress("passBeamHaloFilterTight", &passBeamHaloFilterTight, &b_passBeamHaloFilterTight);
   fChain->SetBranchAddress("passCaloBoundaryDRFilter", &passCaloBoundaryDRFilter, &b_passCaloBoundaryDRFilter);
   fChain->SetBranchAddress("passEcalDeadCellBoundaryEnergyFilter", &passEcalDeadCellBoundaryEnergyFilter, &b_passEcalDeadCellBoundaryEnergyFilter);
   fChain->SetBranchAddress("passEcalDeadCellTriggerPrimitiveFilter", &passEcalDeadCellTriggerPrimitiveFilter, &b_passEcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("passEcalLaserCorrFilter", &passEcalLaserCorrFilter, &b_passEcalLaserCorrFilter);
   fChain->SetBranchAddress("passEcalMaskedCellDRFilter", &passEcalMaskedCellDRFilter, &b_passEcalMaskedCellDRFilter);
   fChain->SetBranchAddress("passHBHENoiseFilter", &passHBHENoiseFilter, &b_passHBHENoiseFilter);
   fChain->SetBranchAddress("passLogErrorTooManyClusters", &passLogErrorTooManyClusters, &b_passLogErrorTooManyClusters);
   fChain->SetBranchAddress("passManyStripClus53X", &passManyStripClus53X, &b_passManyStripClus53X);
   fChain->SetBranchAddress("passTooManyStripClus53X", &passTooManyStripClus53X, &b_passTooManyStripClus53X);
   fChain->SetBranchAddress("passTrackingFailureFilter", &passTrackingFailureFilter, &b_passTrackingFailureFilter);
   fChain->SetBranchAddress("hasVeryForwardPFMuon", &hasVeryForwardPFMuon, &b_hasVeryForwardPFMuon);
   fChain->SetBranchAddress("hasJetWithBadUnc", &hasJetWithBadUnc, &b_hasJetWithBadUnc);
   fChain->SetBranchAddress("ElectronGsfCtfCharge", &ElectronGsfCtfCharge, &b_ElectronGsfCtfCharge);
   fChain->SetBranchAddress("ElectronGsfCtfScPixCharge", &ElectronGsfCtfScPixCharge, &b_ElectronGsfCtfScPixCharge);
   fChain->SetBranchAddress("ElectronGsfScPixCharge", &ElectronGsfScPixCharge, &b_ElectronGsfScPixCharge);
   fChain->SetBranchAddress("ElectronHLTDoubleEleMatched", &ElectronHLTDoubleEleMatched, &b_ElectronHLTDoubleEleMatched);
   fChain->SetBranchAddress("ElectronHLTSingleEleMatched", &ElectronHLTSingleEleMatched, &b_ElectronHLTSingleEleMatched);
   fChain->SetBranchAddress("ElectronHLTSingleEleWP80Matched", &ElectronHLTSingleEleWP80Matched, &b_ElectronHLTSingleEleWP80Matched);
   fChain->SetBranchAddress("ElectronHasEcalDrivenSeed", &ElectronHasEcalDrivenSeed, &b_ElectronHasEcalDrivenSeed);
   fChain->SetBranchAddress("ElectronHasMatchedConvPhot", &ElectronHasMatchedConvPhot, &b_ElectronHasMatchedConvPhot);
   fChain->SetBranchAddress("ElectronHasTrackerDrivenSeed", &ElectronHasTrackerDrivenSeed, &b_ElectronHasTrackerDrivenSeed);
   fChain->SetBranchAddress("ElectronIsEB", &ElectronIsEB, &b_ElectronIsEB);
   fChain->SetBranchAddress("ElectronIsEE", &ElectronIsEE, &b_ElectronIsEE);
   fChain->SetBranchAddress("MuonHLTSingleIsoMuonMatched", &MuonHLTSingleIsoMuonMatched, &b_MuonHLTSingleIsoMuonMatched);
   fChain->SetBranchAddress("MuonHLTSingleMuonMatched", &MuonHLTSingleMuonMatched, &b_MuonHLTSingleMuonMatched);
   fChain->SetBranchAddress("PhotonHasMatchedConvPhot", &PhotonHasMatchedConvPhot, &b_PhotonHasMatchedConvPhot);
   fChain->SetBranchAddress("PhotonHasMatchedPromptEle", &PhotonHasMatchedPromptEle, &b_PhotonHasMatchedPromptEle);
   fChain->SetBranchAddress("PhotonHasPixelSeed", &PhotonHasPixelSeed, &b_PhotonHasPixelSeed);
   fChain->SetBranchAddress("PhotonIsEBEEGap", &PhotonIsEBEEGap, &b_PhotonIsEBEEGap);
   fChain->SetBranchAddress("PhotonIsEBGap", &PhotonIsEBGap, &b_PhotonIsEBGap);
   fChain->SetBranchAddress("PhotonIsEEGap", &PhotonIsEEGap, &b_PhotonIsEEGap);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerDecisions", &HLTInsideDatasetTriggerDecisions, &b_HLTInsideDatasetTriggerDecisions);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerDecisions", &HLTOutsideDatasetTriggerDecisions, &b_HLTOutsideDatasetTriggerDecisions);
   fChain->SetBranchAddress("VertexIsFake", &VertexIsFake, &b_VertexIsFake);
   fChain->SetBranchAddress("rhoForHEEP", &rhoForHEEP, &b_rhoForHEEP);
   fChain->SetBranchAddress("rhoJets", &rhoJets, &b_rhoJets);
   fChain->SetBranchAddress("rhoJetsCCPU", &rhoJetsCCPU, &b_rhoJetsCCPU);
   fChain->SetBranchAddress("rhoJetsCN", &rhoJetsCN, &b_rhoJetsCN);
   fChain->SetBranchAddress("rhoJetsCNT", &rhoJetsCNT, &b_rhoJetsCNT);
   fChain->SetBranchAddress("time", &time, &b_time);
   fChain->SetBranchAddress("PtHat", &PtHat, &b_PtHat);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   fChain->SetBranchAddress("CaloMET", &CaloMET, &b_CaloMET);
   fChain->SetBranchAddress("CaloMETPhi", &CaloMETPhi, &b_CaloMETPhi);
   fChain->SetBranchAddress("CaloMETPhiUncorr", &CaloMETPhiUncorr, &b_CaloMETPhiUncorr);
   fChain->SetBranchAddress("CaloMETUncorr", &CaloMETUncorr, &b_CaloMETUncorr);
   fChain->SetBranchAddress("CaloSumET", &CaloSumET, &b_CaloSumET);
   fChain->SetBranchAddress("CaloSumETUncorr", &CaloSumETUncorr, &b_CaloSumETUncorr);
   fChain->SetBranchAddress("CaloMETPhiType1Cor", &CaloMETPhiType1Cor, &b_CaloMETPhiType1Cor);
   fChain->SetBranchAddress("CaloMETPhiUncorrType1Cor", &CaloMETPhiUncorrType1Cor, &b_CaloMETPhiUncorrType1Cor);
   fChain->SetBranchAddress("CaloMETType1Cor", &CaloMETType1Cor, &b_CaloMETType1Cor);
   fChain->SetBranchAddress("CaloMETUncorrType1Cor", &CaloMETUncorrType1Cor, &b_CaloMETUncorrType1Cor);
   fChain->SetBranchAddress("CaloSumETType1Cor", &CaloSumETType1Cor, &b_CaloSumETType1Cor);
   fChain->SetBranchAddress("CaloSumETUncorrType1Cor", &CaloSumETUncorrType1Cor, &b_CaloSumETUncorrType1Cor);
   fChain->SetBranchAddress("ElectronBeamSpotDXY", &ElectronBeamSpotDXY, &b_ElectronBeamSpotDXY);
   fChain->SetBranchAddress("ElectronBeamSpotDXYError", &ElectronBeamSpotDXYError, &b_ElectronBeamSpotDXYError);
   fChain->SetBranchAddress("ElectronCaloEnergy", &ElectronCaloEnergy, &b_ElectronCaloEnergy);
   fChain->SetBranchAddress("ElectronConvFitProb", &ElectronConvFitProb, &b_ElectronConvFitProb);
   fChain->SetBranchAddress("ElectronDCotTheta", &ElectronDCotTheta, &b_ElectronDCotTheta);
   fChain->SetBranchAddress("ElectronDeltaEtaTrkSC", &ElectronDeltaEtaTrkSC, &b_ElectronDeltaEtaTrkSC);
   fChain->SetBranchAddress("ElectronDeltaPhiTrkSC", &ElectronDeltaPhiTrkSC, &b_ElectronDeltaPhiTrkSC);
   fChain->SetBranchAddress("ElectronDist", &ElectronDist, &b_ElectronDist);
   fChain->SetBranchAddress("ElectronE1x5OverE5x5", &ElectronE1x5OverE5x5, &b_ElectronE1x5OverE5x5);
   fChain->SetBranchAddress("ElectronE2x5OverE5x5", &ElectronE2x5OverE5x5, &b_ElectronE2x5OverE5x5);
   fChain->SetBranchAddress("ElectronESuperClusterOverP", &ElectronESuperClusterOverP, &b_ElectronESuperClusterOverP);
   fChain->SetBranchAddress("ElectronEcalIsoDR03", &ElectronEcalIsoDR03, &b_ElectronEcalIsoDR03);
   fChain->SetBranchAddress("ElectronEcalIsoPAT", &ElectronEcalIsoPAT, &b_ElectronEcalIsoPAT);
   fChain->SetBranchAddress("ElectronEnergy", &ElectronEnergy, &b_ElectronEnergy);
   fChain->SetBranchAddress("ElectronEta", &ElectronEta, &b_ElectronEta);
   fChain->SetBranchAddress("ElectronFbrem", &ElectronFbrem, &b_ElectronFbrem);
   fChain->SetBranchAddress("ElectronHLTDoubleEleMatchEta", &ElectronHLTDoubleEleMatchEta, &b_ElectronHLTDoubleEleMatchEta);
   fChain->SetBranchAddress("ElectronHLTDoubleEleMatchPhi", &ElectronHLTDoubleEleMatchPhi, &b_ElectronHLTDoubleEleMatchPhi);
   fChain->SetBranchAddress("ElectronHLTDoubleEleMatchPt", &ElectronHLTDoubleEleMatchPt, &b_ElectronHLTDoubleEleMatchPt);
   fChain->SetBranchAddress("ElectronHLTSingleEleMatchEta", &ElectronHLTSingleEleMatchEta, &b_ElectronHLTSingleEleMatchEta);
   fChain->SetBranchAddress("ElectronHLTSingleEleMatchPhi", &ElectronHLTSingleEleMatchPhi, &b_ElectronHLTSingleEleMatchPhi);
   fChain->SetBranchAddress("ElectronHLTSingleEleMatchPt", &ElectronHLTSingleEleMatchPt, &b_ElectronHLTSingleEleMatchPt);
   fChain->SetBranchAddress("ElectronHLTSingleEleWP80MatchEta", &ElectronHLTSingleEleWP80MatchEta, &b_ElectronHLTSingleEleWP80MatchEta);
   fChain->SetBranchAddress("ElectronHLTSingleEleWP80MatchPhi", &ElectronHLTSingleEleWP80MatchPhi, &b_ElectronHLTSingleEleWP80MatchPhi);
   fChain->SetBranchAddress("ElectronHLTSingleEleWP80MatchPt", &ElectronHLTSingleEleWP80MatchPt, &b_ElectronHLTSingleEleWP80MatchPt);
   fChain->SetBranchAddress("ElectronHcalIsoD1DR03", &ElectronHcalIsoD1DR03, &b_ElectronHcalIsoD1DR03);
   fChain->SetBranchAddress("ElectronHcalIsoD2DR03", &ElectronHcalIsoD2DR03, &b_ElectronHcalIsoD2DR03);
   fChain->SetBranchAddress("ElectronHcalIsoDR03", &ElectronHcalIsoDR03, &b_ElectronHcalIsoDR03);
   fChain->SetBranchAddress("ElectronHcalIsoDR03FullCone", &ElectronHcalIsoDR03FullCone, &b_ElectronHcalIsoDR03FullCone);
   fChain->SetBranchAddress("ElectronHcalIsoPAT", &ElectronHcalIsoPAT, &b_ElectronHcalIsoPAT);
   fChain->SetBranchAddress("ElectronHoE", &ElectronHoE, &b_ElectronHoE);
   fChain->SetBranchAddress("ElectronLeadVtxDistXY", &ElectronLeadVtxDistXY, &b_ElectronLeadVtxDistXY);
   fChain->SetBranchAddress("ElectronLeadVtxDistZ", &ElectronLeadVtxDistZ, &b_ElectronLeadVtxDistZ);
   fChain->SetBranchAddress("ElectronMatchedGenParticleEta", &ElectronMatchedGenParticleEta, &b_ElectronMatchedGenParticleEta);
   fChain->SetBranchAddress("ElectronMatchedGenParticlePhi", &ElectronMatchedGenParticlePhi, &b_ElectronMatchedGenParticlePhi);
   fChain->SetBranchAddress("ElectronMatchedGenParticlePt", &ElectronMatchedGenParticlePt, &b_ElectronMatchedGenParticlePt);
   fChain->SetBranchAddress("ElectronPFChargedHadronIso03", &ElectronPFChargedHadronIso03, &b_ElectronPFChargedHadronIso03);
   fChain->SetBranchAddress("ElectronPFChargedHadronIso04", &ElectronPFChargedHadronIso04, &b_ElectronPFChargedHadronIso04);
   fChain->SetBranchAddress("ElectronPFNeutralHadronIso03", &ElectronPFNeutralHadronIso03, &b_ElectronPFNeutralHadronIso03);
   fChain->SetBranchAddress("ElectronPFNeutralHadronIso04", &ElectronPFNeutralHadronIso04, &b_ElectronPFNeutralHadronIso04);
   fChain->SetBranchAddress("ElectronPFPhotonIso03", &ElectronPFPhotonIso03, &b_ElectronPFPhotonIso03);
   fChain->SetBranchAddress("ElectronPFPhotonIso04", &ElectronPFPhotonIso04, &b_ElectronPFPhotonIso04);
   fChain->SetBranchAddress("ElectronPhi", &ElectronPhi, &b_ElectronPhi);
   fChain->SetBranchAddress("ElectronPrimaryVertexDXY", &ElectronPrimaryVertexDXY, &b_ElectronPrimaryVertexDXY);
   fChain->SetBranchAddress("ElectronPrimaryVertexDXYError", &ElectronPrimaryVertexDXYError, &b_ElectronPrimaryVertexDXYError);
   fChain->SetBranchAddress("ElectronPt", &ElectronPt, &b_ElectronPt);
   fChain->SetBranchAddress("ElectronPtHeep", &ElectronPtHeep, &b_ElectronPtHeep);
   fChain->SetBranchAddress("ElectronRelIsoPAT", &ElectronRelIsoPAT, &b_ElectronRelIsoPAT);
   fChain->SetBranchAddress("ElectronSCEta", &ElectronSCEta, &b_ElectronSCEta);
   fChain->SetBranchAddress("ElectronSCPhi", &ElectronSCPhi, &b_ElectronSCPhi);
   fChain->SetBranchAddress("ElectronSCPt", &ElectronSCPt, &b_ElectronSCPt);
   fChain->SetBranchAddress("ElectronSCRawEnergy", &ElectronSCRawEnergy, &b_ElectronSCRawEnergy);
   fChain->SetBranchAddress("ElectronSigmaEtaEta", &ElectronSigmaEtaEta, &b_ElectronSigmaEtaEta);
   fChain->SetBranchAddress("ElectronSigmaIEtaIEta", &ElectronSigmaIEtaIEta, &b_ElectronSigmaIEtaIEta);
   fChain->SetBranchAddress("ElectronTrackPt", &ElectronTrackPt, &b_ElectronTrackPt);
   fChain->SetBranchAddress("ElectronTrackValidFractionOfHits", &ElectronTrackValidFractionOfHits, &b_ElectronTrackValidFractionOfHits);
   fChain->SetBranchAddress("ElectronTrackVx", &ElectronTrackVx, &b_ElectronTrackVx);
   fChain->SetBranchAddress("ElectronTrackVy", &ElectronTrackVy, &b_ElectronTrackVy);
   fChain->SetBranchAddress("ElectronTrackVz", &ElectronTrackVz, &b_ElectronTrackVz);
   fChain->SetBranchAddress("ElectronTrkIsoDR03", &ElectronTrkIsoDR03, &b_ElectronTrkIsoDR03);
   fChain->SetBranchAddress("ElectronTrkIsoPAT", &ElectronTrkIsoPAT, &b_ElectronTrkIsoPAT);
   fChain->SetBranchAddress("ElectronVtxDistXY", &ElectronVtxDistXY, &b_ElectronVtxDistXY);
   fChain->SetBranchAddress("ElectronVtxDistZ", &ElectronVtxDistZ, &b_ElectronVtxDistZ);
   fChain->SetBranchAddress("GenWElectronEnergy", &GenWElectronEnergy, &b_GenWElectronEnergy);
   fChain->SetBranchAddress("GenWElectronEta", &GenWElectronEta, &b_GenWElectronEta);
   fChain->SetBranchAddress("GenWElectronP", &GenWElectronP, &b_GenWElectronP);
   fChain->SetBranchAddress("GenWElectronPhi", &GenWElectronPhi, &b_GenWElectronPhi);
   fChain->SetBranchAddress("GenWElectronPt", &GenWElectronPt, &b_GenWElectronPt);
   fChain->SetBranchAddress("GenWElectronPx", &GenWElectronPx, &b_GenWElectronPx);
   fChain->SetBranchAddress("GenWElectronPy", &GenWElectronPy, &b_GenWElectronPy);
   fChain->SetBranchAddress("GenWElectronPz", &GenWElectronPz, &b_GenWElectronPz);
   fChain->SetBranchAddress("GenWElectronTauVisibleEta", &GenWElectronTauVisibleEta, &b_GenWElectronTauVisibleEta);
   fChain->SetBranchAddress("GenWElectronTauVisiblePhi", &GenWElectronTauVisiblePhi, &b_GenWElectronTauVisiblePhi);
   fChain->SetBranchAddress("GenWElectronTauVisiblePt", &GenWElectronTauVisiblePt, &b_GenWElectronTauVisiblePt);
   fChain->SetBranchAddress("GenWElectronVX", &GenWElectronVX, &b_GenWElectronVX);
   fChain->SetBranchAddress("GenWElectronVY", &GenWElectronVY, &b_GenWElectronVY);
   fChain->SetBranchAddress("GenWElectronVZ", &GenWElectronVZ, &b_GenWElectronVZ);
   fChain->SetBranchAddress("GenZElectronEnergy", &GenZElectronEnergy, &b_GenZElectronEnergy);
   fChain->SetBranchAddress("GenZElectronEta", &GenZElectronEta, &b_GenZElectronEta);
   fChain->SetBranchAddress("GenZElectronP", &GenZElectronP, &b_GenZElectronP);
   fChain->SetBranchAddress("GenZElectronPhi", &GenZElectronPhi, &b_GenZElectronPhi);
   fChain->SetBranchAddress("GenZElectronPt", &GenZElectronPt, &b_GenZElectronPt);
   fChain->SetBranchAddress("GenZElectronPx", &GenZElectronPx, &b_GenZElectronPx);
   fChain->SetBranchAddress("GenZElectronPy", &GenZElectronPy, &b_GenZElectronPy);
   fChain->SetBranchAddress("GenZElectronPz", &GenZElectronPz, &b_GenZElectronPz);
   fChain->SetBranchAddress("GenZElectronTauVisibleEta", &GenZElectronTauVisibleEta, &b_GenZElectronTauVisibleEta);
   fChain->SetBranchAddress("GenZElectronTauVisiblePhi", &GenZElectronTauVisiblePhi, &b_GenZElectronTauVisiblePhi);
   fChain->SetBranchAddress("GenZElectronTauVisiblePt", &GenZElectronTauVisiblePt, &b_GenZElectronTauVisiblePt);
   fChain->SetBranchAddress("GenZElectronVX", &GenZElectronVX, &b_GenZElectronVX);
   fChain->SetBranchAddress("GenZElectronVY", &GenZElectronVY, &b_GenZElectronVY);
   fChain->SetBranchAddress("GenZElectronVZ", &GenZElectronVZ, &b_GenZElectronVZ);
   fChain->SetBranchAddress("PDFCTEQWeights", &PDFCTEQWeights, &b_PDFCTEQWeights);
   fChain->SetBranchAddress("PDFMSTWWeights", &PDFMSTWWeights, &b_PDFMSTWWeights);
   fChain->SetBranchAddress("PDFNNPDFWeights", &PDFNNPDFWeights, &b_PDFNNPDFWeights);
   fChain->SetBranchAddress("GenJetEMF", &GenJetEMF, &b_GenJetEMF);
   fChain->SetBranchAddress("GenJetEnergy", &GenJetEnergy, &b_GenJetEnergy);
   fChain->SetBranchAddress("GenJetEta", &GenJetEta, &b_GenJetEta);
   fChain->SetBranchAddress("GenJetHADF", &GenJetHADF, &b_GenJetHADF);
   fChain->SetBranchAddress("GenJetP", &GenJetP, &b_GenJetP);
   fChain->SetBranchAddress("GenJetPhi", &GenJetPhi, &b_GenJetPhi);
   fChain->SetBranchAddress("GenJetPt", &GenJetPt, &b_GenJetPt);
   fChain->SetBranchAddress("GenMETCalo", &GenMETCalo, &b_GenMETCalo);
   fChain->SetBranchAddress("GenMETPhiCalo", &GenMETPhiCalo, &b_GenMETPhiCalo);
   fChain->SetBranchAddress("GenSumETCalo", &GenSumETCalo, &b_GenSumETCalo);
   fChain->SetBranchAddress("GenMETPhiTrue", &GenMETPhiTrue, &b_GenMETPhiTrue);
   fChain->SetBranchAddress("GenMETTrue", &GenMETTrue, &b_GenMETTrue);
   fChain->SetBranchAddress("GenSumETTrue", &GenSumETTrue, &b_GenSumETTrue);
   fChain->SetBranchAddress("GenWMuEnergy", &GenWMuEnergy, &b_GenWMuEnergy);
   fChain->SetBranchAddress("GenWMuEta", &GenWMuEta, &b_GenWMuEta);
   fChain->SetBranchAddress("GenWMuP", &GenWMuP, &b_GenWMuP);
   fChain->SetBranchAddress("GenWMuPhi", &GenWMuPhi, &b_GenWMuPhi);
   fChain->SetBranchAddress("GenWMuPt", &GenWMuPt, &b_GenWMuPt);
   fChain->SetBranchAddress("GenWMuPx", &GenWMuPx, &b_GenWMuPx);
   fChain->SetBranchAddress("GenWMuPy", &GenWMuPy, &b_GenWMuPy);
   fChain->SetBranchAddress("GenWMuPz", &GenWMuPz, &b_GenWMuPz);
   fChain->SetBranchAddress("GenWMuTauVisibleEta", &GenWMuTauVisibleEta, &b_GenWMuTauVisibleEta);
   fChain->SetBranchAddress("GenWMuTauVisiblePhi", &GenWMuTauVisiblePhi, &b_GenWMuTauVisiblePhi);
   fChain->SetBranchAddress("GenWMuTauVisiblePt", &GenWMuTauVisiblePt, &b_GenWMuTauVisiblePt);
   fChain->SetBranchAddress("GenWMuVX", &GenWMuVX, &b_GenWMuVX);
   fChain->SetBranchAddress("GenWMuVY", &GenWMuVY, &b_GenWMuVY);
   fChain->SetBranchAddress("GenWMuVZ", &GenWMuVZ, &b_GenWMuVZ);
   fChain->SetBranchAddress("GenZMuEnergy", &GenZMuEnergy, &b_GenZMuEnergy);
   fChain->SetBranchAddress("GenZMuEta", &GenZMuEta, &b_GenZMuEta);
   fChain->SetBranchAddress("GenZMuP", &GenZMuP, &b_GenZMuP);
   fChain->SetBranchAddress("GenZMuPhi", &GenZMuPhi, &b_GenZMuPhi);
   fChain->SetBranchAddress("GenZMuPt", &GenZMuPt, &b_GenZMuPt);
   fChain->SetBranchAddress("GenZMuPx", &GenZMuPx, &b_GenZMuPx);
   fChain->SetBranchAddress("GenZMuPy", &GenZMuPy, &b_GenZMuPy);
   fChain->SetBranchAddress("GenZMuPz", &GenZMuPz, &b_GenZMuPz);
   fChain->SetBranchAddress("GenZMuTauVisibleEta", &GenZMuTauVisibleEta, &b_GenZMuTauVisibleEta);
   fChain->SetBranchAddress("GenZMuTauVisiblePhi", &GenZMuTauVisiblePhi, &b_GenZMuTauVisiblePhi);
   fChain->SetBranchAddress("GenZMuTauVisiblePt", &GenZMuTauVisiblePt, &b_GenZMuTauVisiblePt);
   fChain->SetBranchAddress("GenZMuVX", &GenZMuVX, &b_GenZMuVX);
   fChain->SetBranchAddress("GenZMuVY", &GenZMuVY, &b_GenZMuVY);
   fChain->SetBranchAddress("GenZMuVZ", &GenZMuVZ, &b_GenZMuVZ);
   fChain->SetBranchAddress("GenParticleEnergy", &GenParticleEnergy, &b_GenParticleEnergy);
   fChain->SetBranchAddress("GenParticleEta", &GenParticleEta, &b_GenParticleEta);
   fChain->SetBranchAddress("GenParticleP", &GenParticleP, &b_GenParticleP);
   fChain->SetBranchAddress("GenParticlePhi", &GenParticlePhi, &b_GenParticlePhi);
   fChain->SetBranchAddress("GenParticlePt", &GenParticlePt, &b_GenParticlePt);
   fChain->SetBranchAddress("GenParticlePx", &GenParticlePx, &b_GenParticlePx);
   fChain->SetBranchAddress("GenParticlePy", &GenParticlePy, &b_GenParticlePy);
   fChain->SetBranchAddress("GenParticlePz", &GenParticlePz, &b_GenParticlePz);
   fChain->SetBranchAddress("GenParticleTauVisibleEta", &GenParticleTauVisibleEta, &b_GenParticleTauVisibleEta);
   fChain->SetBranchAddress("GenParticleTauVisiblePhi", &GenParticleTauVisiblePhi, &b_GenParticleTauVisiblePhi);
   fChain->SetBranchAddress("GenParticleTauVisiblePt", &GenParticleTauVisiblePt, &b_GenParticleTauVisiblePt);
   fChain->SetBranchAddress("GenParticleVX", &GenParticleVX, &b_GenParticleVX);
   fChain->SetBranchAddress("GenParticleVY", &GenParticleVY, &b_GenParticleVY);
   fChain->SetBranchAddress("GenParticleVZ", &GenParticleVZ, &b_GenParticleVZ);
   fChain->SetBranchAddress("GenWTauEnergy", &GenWTauEnergy, &b_GenWTauEnergy);
   fChain->SetBranchAddress("GenWTauEta", &GenWTauEta, &b_GenWTauEta);
   fChain->SetBranchAddress("GenWTauP", &GenWTauP, &b_GenWTauP);
   fChain->SetBranchAddress("GenWTauPhi", &GenWTauPhi, &b_GenWTauPhi);
   fChain->SetBranchAddress("GenWTauPt", &GenWTauPt, &b_GenWTauPt);
   fChain->SetBranchAddress("GenWTauPx", &GenWTauPx, &b_GenWTauPx);
   fChain->SetBranchAddress("GenWTauPy", &GenWTauPy, &b_GenWTauPy);
   fChain->SetBranchAddress("GenWTauPz", &GenWTauPz, &b_GenWTauPz);
   fChain->SetBranchAddress("GenWTauTauVisibleEta", &GenWTauTauVisibleEta, &b_GenWTauTauVisibleEta);
   fChain->SetBranchAddress("GenWTauTauVisiblePhi", &GenWTauTauVisiblePhi, &b_GenWTauTauVisiblePhi);
   fChain->SetBranchAddress("GenWTauTauVisiblePt", &GenWTauTauVisiblePt, &b_GenWTauTauVisiblePt);
   fChain->SetBranchAddress("GenWTauVX", &GenWTauVX, &b_GenWTauVX);
   fChain->SetBranchAddress("GenWTauVY", &GenWTauVY, &b_GenWTauVY);
   fChain->SetBranchAddress("GenWTauVZ", &GenWTauVZ, &b_GenWTauVZ);
   fChain->SetBranchAddress("GenZTauEnergy", &GenZTauEnergy, &b_GenZTauEnergy);
   fChain->SetBranchAddress("GenZTauEta", &GenZTauEta, &b_GenZTauEta);
   fChain->SetBranchAddress("GenZTauP", &GenZTauP, &b_GenZTauP);
   fChain->SetBranchAddress("GenZTauPhi", &GenZTauPhi, &b_GenZTauPhi);
   fChain->SetBranchAddress("GenZTauPt", &GenZTauPt, &b_GenZTauPt);
   fChain->SetBranchAddress("GenZTauPx", &GenZTauPx, &b_GenZTauPx);
   fChain->SetBranchAddress("GenZTauPy", &GenZTauPy, &b_GenZTauPy);
   fChain->SetBranchAddress("GenZTauPz", &GenZTauPz, &b_GenZTauPz);
   fChain->SetBranchAddress("GenZTauTauVisibleEta", &GenZTauTauVisibleEta, &b_GenZTauTauVisibleEta);
   fChain->SetBranchAddress("GenZTauTauVisiblePhi", &GenZTauTauVisiblePhi, &b_GenZTauTauVisiblePhi);
   fChain->SetBranchAddress("GenZTauTauVisiblePt", &GenZTauTauVisiblePt, &b_GenZTauTauVisiblePt);
   fChain->SetBranchAddress("GenZTauVX", &GenZTauVX, &b_GenZTauVX);
   fChain->SetBranchAddress("GenZTauVY", &GenZTauVY, &b_GenZTauVY);
   fChain->SetBranchAddress("GenZTauVZ", &GenZTauVZ, &b_GenZTauVZ);
   fChain->SetBranchAddress("HPSTauAgainstElectronDeadECALDiscr", &HPSTauAgainstElectronDeadECALDiscr, &b_HPSTauAgainstElectronDeadECALDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronLooseDiscr", &HPSTauAgainstElectronLooseDiscr, &b_HPSTauAgainstElectronLooseDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronLooseMVA2Discr", &HPSTauAgainstElectronLooseMVA2Discr, &b_HPSTauAgainstElectronLooseMVA2Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronLooseMVA3Discr", &HPSTauAgainstElectronLooseMVA3Discr, &b_HPSTauAgainstElectronLooseMVA3Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMVA2categoryDiscr", &HPSTauAgainstElectronMVA2categoryDiscr, &b_HPSTauAgainstElectronMVA2categoryDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMVA2rawDiscr", &HPSTauAgainstElectronMVA2rawDiscr, &b_HPSTauAgainstElectronMVA2rawDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMVA3categoryDiscr", &HPSTauAgainstElectronMVA3categoryDiscr, &b_HPSTauAgainstElectronMVA3categoryDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMVA3rawDiscr", &HPSTauAgainstElectronMVA3rawDiscr, &b_HPSTauAgainstElectronMVA3rawDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMVADiscr", &HPSTauAgainstElectronMVADiscr, &b_HPSTauAgainstElectronMVADiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMediumDiscr", &HPSTauAgainstElectronMediumDiscr, &b_HPSTauAgainstElectronMediumDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMediumMVA2Discr", &HPSTauAgainstElectronMediumMVA2Discr, &b_HPSTauAgainstElectronMediumMVA2Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronMediumMVA3Discr", &HPSTauAgainstElectronMediumMVA3Discr, &b_HPSTauAgainstElectronMediumMVA3Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronTightDiscr", &HPSTauAgainstElectronTightDiscr, &b_HPSTauAgainstElectronTightDiscr);
   fChain->SetBranchAddress("HPSTauAgainstElectronTightMVA2Discr", &HPSTauAgainstElectronTightMVA2Discr, &b_HPSTauAgainstElectronTightMVA2Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronTightMVA3Discr", &HPSTauAgainstElectronTightMVA3Discr, &b_HPSTauAgainstElectronTightMVA3Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronVLooseMVA2Discr", &HPSTauAgainstElectronVLooseMVA2Discr, &b_HPSTauAgainstElectronVLooseMVA2Discr);
   fChain->SetBranchAddress("HPSTauAgainstElectronVTightMVA3Discr", &HPSTauAgainstElectronVTightMVA3Discr, &b_HPSTauAgainstElectronVTightMVA3Discr);
   fChain->SetBranchAddress("HPSTauAgainstMuonLoose2Discr", &HPSTauAgainstMuonLoose2Discr, &b_HPSTauAgainstMuonLoose2Discr);
   fChain->SetBranchAddress("HPSTauAgainstMuonLooseDiscr", &HPSTauAgainstMuonLooseDiscr, &b_HPSTauAgainstMuonLooseDiscr);
   fChain->SetBranchAddress("HPSTauAgainstMuonMedium2Discr", &HPSTauAgainstMuonMedium2Discr, &b_HPSTauAgainstMuonMedium2Discr);
   fChain->SetBranchAddress("HPSTauAgainstMuonMediumDiscr", &HPSTauAgainstMuonMediumDiscr, &b_HPSTauAgainstMuonMediumDiscr);
   fChain->SetBranchAddress("HPSTauAgainstMuonTight2Discr", &HPSTauAgainstMuonTight2Discr, &b_HPSTauAgainstMuonTight2Discr);
   fChain->SetBranchAddress("HPSTauAgainstMuonTightDiscr", &HPSTauAgainstMuonTightDiscr, &b_HPSTauAgainstMuonTightDiscr);
   fChain->SetBranchAddress("HPSTauBremsRecoveryEOverPLead", &HPSTauBremsRecoveryEOverPLead, &b_HPSTauBremsRecoveryEOverPLead);
   fChain->SetBranchAddress("HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr", &HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr, &b_HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr);
   fChain->SetBranchAddress("HPSTauDecayModeFindingDiscr", &HPSTauDecayModeFindingDiscr, &b_HPSTauDecayModeFindingDiscr);
   fChain->SetBranchAddress("HPSTauEcalStripSumEOverPLead", &HPSTauEcalStripSumEOverPLead, &b_HPSTauEcalStripSumEOverPLead);
   fChain->SetBranchAddress("HPSTauEmFraction", &HPSTauEmFraction, &b_HPSTauEmFraction);
   fChain->SetBranchAddress("HPSTauEt", &HPSTauEt, &b_HPSTauEt);
   fChain->SetBranchAddress("HPSTauEta", &HPSTauEta, &b_HPSTauEta);
   fChain->SetBranchAddress("HPSTauEtaLeadCharged", &HPSTauEtaLeadCharged, &b_HPSTauEtaLeadCharged);
   fChain->SetBranchAddress("HPSTauEtaetaMoment", &HPSTauEtaetaMoment, &b_HPSTauEtaetaMoment);
   fChain->SetBranchAddress("HPSTauEtaphiMoment", &HPSTauEtaphiMoment, &b_HPSTauEtaphiMoment);
   fChain->SetBranchAddress("HPSTauHcal3x3OverPLead", &HPSTauHcal3x3OverPLead, &b_HPSTauHcal3x3OverPLead);
   fChain->SetBranchAddress("HPSTauHcalMaxOverPLead", &HPSTauHcalMaxOverPLead, &b_HPSTauHcalMaxOverPLead);
   fChain->SetBranchAddress("HPSTauHcalTotOverPLead", &HPSTauHcalTotOverPLead, &b_HPSTauHcalTotOverPLead);
   fChain->SetBranchAddress("HPSTauIsolationMVArawDiscr", &HPSTauIsolationMVArawDiscr, &b_HPSTauIsolationMVArawDiscr);
   fChain->SetBranchAddress("HPSTauIsolationPFChargedHadrCandsPtSum", &HPSTauIsolationPFChargedHadrCandsPtSum, &b_HPSTauIsolationPFChargedHadrCandsPtSum);
   fChain->SetBranchAddress("HPSTauIsolationPFGammaCandsEtSum", &HPSTauIsolationPFGammaCandsEtSum, &b_HPSTauIsolationPFGammaCandsEtSum);
   fChain->SetBranchAddress("HPSTauLeadPFChargedHadrCandsignedSipt", &HPSTauLeadPFChargedHadrCandsignedSipt, &b_HPSTauLeadPFChargedHadrCandsignedSipt);
   fChain->SetBranchAddress("HPSTauLeadVtxDistXY", &HPSTauLeadVtxDistXY, &b_HPSTauLeadVtxDistXY);
   fChain->SetBranchAddress("HPSTauLeadVtxDistZ", &HPSTauLeadVtxDistZ, &b_HPSTauLeadVtxDistZ);
   fChain->SetBranchAddress("HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr", &HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr, &b_HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr);
   fChain->SetBranchAddress("HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr", &HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr, &b_HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauLooseIsolationDeltaBetaCorrDiscr", &HPSTauLooseIsolationDeltaBetaCorrDiscr, &b_HPSTauLooseIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauLooseIsolationDiscr", &HPSTauLooseIsolationDiscr, &b_HPSTauLooseIsolationDiscr);
   fChain->SetBranchAddress("HPSTauLooseIsolationMVA2Discr", &HPSTauLooseIsolationMVA2Discr, &b_HPSTauLooseIsolationMVA2Discr);
   fChain->SetBranchAddress("HPSTauLooseIsolationMVADiscr", &HPSTauLooseIsolationMVADiscr, &b_HPSTauLooseIsolationMVADiscr);
   fChain->SetBranchAddress("HPSTauMatchedGenJetEta", &HPSTauMatchedGenJetEta, &b_HPSTauMatchedGenJetEta);
   fChain->SetBranchAddress("HPSTauMatchedGenJetPhi", &HPSTauMatchedGenJetPhi, &b_HPSTauMatchedGenJetPhi);
   fChain->SetBranchAddress("HPSTauMatchedGenJetPt", &HPSTauMatchedGenJetPt, &b_HPSTauMatchedGenJetPt);
   fChain->SetBranchAddress("HPSTauMatchedGenParticleEta", &HPSTauMatchedGenParticleEta, &b_HPSTauMatchedGenParticleEta);
   fChain->SetBranchAddress("HPSTauMatchedGenParticlePhi", &HPSTauMatchedGenParticlePhi, &b_HPSTauMatchedGenParticlePhi);
   fChain->SetBranchAddress("HPSTauMatchedGenParticlePt", &HPSTauMatchedGenParticlePt, &b_HPSTauMatchedGenParticlePt);
   fChain->SetBranchAddress("HPSTauMaximumHCALPFClusterEt", &HPSTauMaximumHCALPFClusterEt, &b_HPSTauMaximumHCALPFClusterEt);
   fChain->SetBranchAddress("HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr", &HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr, &b_HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr);
   fChain->SetBranchAddress("HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr", &HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr, &b_HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauMediumIsolationDeltaBetaCorrDiscr", &HPSTauMediumIsolationDeltaBetaCorrDiscr, &b_HPSTauMediumIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauMediumIsolationDiscr", &HPSTauMediumIsolationDiscr, &b_HPSTauMediumIsolationDiscr);
   fChain->SetBranchAddress("HPSTauMediumIsolationMVA2Discr", &HPSTauMediumIsolationMVA2Discr, &b_HPSTauMediumIsolationMVA2Discr);
   fChain->SetBranchAddress("HPSTauMediumIsolationMVADiscr", &HPSTauMediumIsolationMVADiscr, &b_HPSTauMediumIsolationMVADiscr);
   fChain->SetBranchAddress("HPSTauPhi", &HPSTauPhi, &b_HPSTauPhi);
   fChain->SetBranchAddress("HPSTauPhiLeadCharged", &HPSTauPhiLeadCharged, &b_HPSTauPhiLeadCharged);
   fChain->SetBranchAddress("HPSTauPhiphiMoment", &HPSTauPhiphiMoment, &b_HPSTauPhiphiMoment);
   fChain->SetBranchAddress("HPSTauPt", &HPSTauPt, &b_HPSTauPt);
   fChain->SetBranchAddress("HPSTauPtLeadCharged", &HPSTauPtLeadCharged, &b_HPSTauPtLeadCharged);
   fChain->SetBranchAddress("HPSTauSignalPFChargedHadrCandsCount", &HPSTauSignalPFChargedHadrCandsCount, &b_HPSTauSignalPFChargedHadrCandsCount);
   fChain->SetBranchAddress("HPSTauSignalPFChargedHadrCandsEta", &HPSTauSignalPFChargedHadrCandsEta, &b_HPSTauSignalPFChargedHadrCandsEta);
   fChain->SetBranchAddress("HPSTauSignalPFChargedHadrCandsPhi", &HPSTauSignalPFChargedHadrCandsPhi, &b_HPSTauSignalPFChargedHadrCandsPhi);
   fChain->SetBranchAddress("HPSTauSignalPFChargedHadrCandsPt", &HPSTauSignalPFChargedHadrCandsPt, &b_HPSTauSignalPFChargedHadrCandsPt);
   fChain->SetBranchAddress("HPSTauSignalPFGammaCandsCount", &HPSTauSignalPFGammaCandsCount, &b_HPSTauSignalPFGammaCandsCount);
   fChain->SetBranchAddress("HPSTauSignalPFGammaCandsEta", &HPSTauSignalPFGammaCandsEta, &b_HPSTauSignalPFGammaCandsEta);
   fChain->SetBranchAddress("HPSTauSignalPFGammaCandsPhi", &HPSTauSignalPFGammaCandsPhi, &b_HPSTauSignalPFGammaCandsPhi);
   fChain->SetBranchAddress("HPSTauSignalPFGammaCandsPt", &HPSTauSignalPFGammaCandsPt, &b_HPSTauSignalPFGammaCandsPt);
   fChain->SetBranchAddress("HPSTauSignalPFNeutrHadrCandsCount", &HPSTauSignalPFNeutrHadrCandsCount, &b_HPSTauSignalPFNeutrHadrCandsCount);
   fChain->SetBranchAddress("HPSTauSignalPFNeutrHadrCandsEta", &HPSTauSignalPFNeutrHadrCandsEta, &b_HPSTauSignalPFNeutrHadrCandsEta);
   fChain->SetBranchAddress("HPSTauSignalPFNeutrHadrCandsPhi", &HPSTauSignalPFNeutrHadrCandsPhi, &b_HPSTauSignalPFNeutrHadrCandsPhi);
   fChain->SetBranchAddress("HPSTauSignalPFNeutrHadrCandsPt", &HPSTauSignalPFNeutrHadrCandsPt, &b_HPSTauSignalPFNeutrHadrCandsPt);
   fChain->SetBranchAddress("HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr", &HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr, &b_HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr);
   fChain->SetBranchAddress("HPSTauTightCombinedIsolationDeltaBetaCorrDiscr", &HPSTauTightCombinedIsolationDeltaBetaCorrDiscr, &b_HPSTauTightCombinedIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauTightIsolationDeltaBetaCorrDiscr", &HPSTauTightIsolationDeltaBetaCorrDiscr, &b_HPSTauTightIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauTightIsolationDiscr", &HPSTauTightIsolationDiscr, &b_HPSTauTightIsolationDiscr);
   fChain->SetBranchAddress("HPSTauTightIsolationMVA2Discr", &HPSTauTightIsolationMVA2Discr, &b_HPSTauTightIsolationMVA2Discr);
   fChain->SetBranchAddress("HPSTauTightIsolationMVADiscr", &HPSTauTightIsolationMVADiscr, &b_HPSTauTightIsolationMVADiscr);
   fChain->SetBranchAddress("HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr", &HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr, &b_HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauVLooseIsolationDeltaBetaCorrDiscr", &HPSTauVLooseIsolationDeltaBetaCorrDiscr, &b_HPSTauVLooseIsolationDeltaBetaCorrDiscr);
   fChain->SetBranchAddress("HPSTauVLooseIsolationDiscr", &HPSTauVLooseIsolationDiscr, &b_HPSTauVLooseIsolationDiscr);
   fChain->SetBranchAddress("HPSTauVtxDistXY", &HPSTauVtxDistXY, &b_HPSTauVtxDistXY);
   fChain->SetBranchAddress("HPSTauVtxDistZ", &HPSTauVtxDistZ, &b_HPSTauVtxDistZ);
   fChain->SetBranchAddress("MuonBackToBackCompatibility", &MuonBackToBackCompatibility, &b_MuonBackToBackCompatibility);
   fChain->SetBranchAddress("MuonBeamSpotDXY", &MuonBeamSpotDXY, &b_MuonBeamSpotDXY);
   fChain->SetBranchAddress("MuonBeamSpotDXYError", &MuonBeamSpotDXYError, &b_MuonBeamSpotDXYError);
   fChain->SetBranchAddress("MuonBestTrackVtxDistXY", &MuonBestTrackVtxDistXY, &b_MuonBestTrackVtxDistXY);
   fChain->SetBranchAddress("MuonBestTrackVtxDistZ", &MuonBestTrackVtxDistZ, &b_MuonBestTrackVtxDistZ);
   fChain->SetBranchAddress("MuonCocktailEta", &MuonCocktailEta, &b_MuonCocktailEta);
   fChain->SetBranchAddress("MuonCocktailEtaError", &MuonCocktailEtaError, &b_MuonCocktailEtaError);
   fChain->SetBranchAddress("MuonCocktailGlobalChi2", &MuonCocktailGlobalChi2, &b_MuonCocktailGlobalChi2);
   fChain->SetBranchAddress("MuonCocktailP", &MuonCocktailP, &b_MuonCocktailP);
   fChain->SetBranchAddress("MuonCocktailPhi", &MuonCocktailPhi, &b_MuonCocktailPhi);
   fChain->SetBranchAddress("MuonCocktailPhiError", &MuonCocktailPhiError, &b_MuonCocktailPhiError);
   fChain->SetBranchAddress("MuonCocktailPt", &MuonCocktailPt, &b_MuonCocktailPt);
   fChain->SetBranchAddress("MuonCocktailPtError", &MuonCocktailPtError, &b_MuonCocktailPtError);
   fChain->SetBranchAddress("MuonCocktailQOverPError", &MuonCocktailQOverPError, &b_MuonCocktailQOverPError);
   fChain->SetBranchAddress("MuonCocktailTrkD0", &MuonCocktailTrkD0, &b_MuonCocktailTrkD0);
   fChain->SetBranchAddress("MuonCocktailTrkD0Error", &MuonCocktailTrkD0Error, &b_MuonCocktailTrkD0Error);
   fChain->SetBranchAddress("MuonCocktailTrkDz", &MuonCocktailTrkDz, &b_MuonCocktailTrkDz);
   fChain->SetBranchAddress("MuonCocktailTrkDzError", &MuonCocktailTrkDzError, &b_MuonCocktailTrkDzError);
   fChain->SetBranchAddress("MuonCocktailTrkValidFractionOfHits", &MuonCocktailTrkValidFractionOfHits, &b_MuonCocktailTrkValidFractionOfHits);
   fChain->SetBranchAddress("MuonCosmicCompatibility", &MuonCosmicCompatibility, &b_MuonCosmicCompatibility);
   fChain->SetBranchAddress("MuonEcalIso", &MuonEcalIso, &b_MuonEcalIso);
   fChain->SetBranchAddress("MuonEcalVetoIso", &MuonEcalVetoIso, &b_MuonEcalVetoIso);
   fChain->SetBranchAddress("MuonEnergy", &MuonEnergy, &b_MuonEnergy);
   fChain->SetBranchAddress("MuonEta", &MuonEta, &b_MuonEta);
   fChain->SetBranchAddress("MuonEtaError", &MuonEtaError, &b_MuonEtaError);
   fChain->SetBranchAddress("MuonGlobalChi2", &MuonGlobalChi2, &b_MuonGlobalChi2);
   fChain->SetBranchAddress("MuonHLTSingleIsoMuonMatchEta", &MuonHLTSingleIsoMuonMatchEta, &b_MuonHLTSingleIsoMuonMatchEta);
   fChain->SetBranchAddress("MuonHLTSingleIsoMuonMatchPhi", &MuonHLTSingleIsoMuonMatchPhi, &b_MuonHLTSingleIsoMuonMatchPhi);
   fChain->SetBranchAddress("MuonHLTSingleIsoMuonMatchPt", &MuonHLTSingleIsoMuonMatchPt, &b_MuonHLTSingleIsoMuonMatchPt);
   fChain->SetBranchAddress("MuonHLTSingleMuonMatchEta", &MuonHLTSingleMuonMatchEta, &b_MuonHLTSingleMuonMatchEta);
   fChain->SetBranchAddress("MuonHLTSingleMuonMatchPhi", &MuonHLTSingleMuonMatchPhi, &b_MuonHLTSingleMuonMatchPhi);
   fChain->SetBranchAddress("MuonHLTSingleMuonMatchPt", &MuonHLTSingleMuonMatchPt, &b_MuonHLTSingleMuonMatchPt);
   fChain->SetBranchAddress("MuonHOIso", &MuonHOIso, &b_MuonHOIso);
   fChain->SetBranchAddress("MuonHcalIso", &MuonHcalIso, &b_MuonHcalIso);
   fChain->SetBranchAddress("MuonHcalVetoIso", &MuonHcalVetoIso, &b_MuonHcalVetoIso);
   fChain->SetBranchAddress("MuonMatchedGenParticleEta", &MuonMatchedGenParticleEta, &b_MuonMatchedGenParticleEta);
   fChain->SetBranchAddress("MuonMatchedGenParticlePhi", &MuonMatchedGenParticlePhi, &b_MuonMatchedGenParticlePhi);
   fChain->SetBranchAddress("MuonMatchedGenParticlePt", &MuonMatchedGenParticlePt, &b_MuonMatchedGenParticlePt);
   fChain->SetBranchAddress("MuonOverlapCompatibility", &MuonOverlapCompatibility, &b_MuonOverlapCompatibility);
   fChain->SetBranchAddress("MuonP", &MuonP, &b_MuonP);
   fChain->SetBranchAddress("MuonPFIsoR03ChargedHadron", &MuonPFIsoR03ChargedHadron, &b_MuonPFIsoR03ChargedHadron);
   fChain->SetBranchAddress("MuonPFIsoR03ChargedParticle", &MuonPFIsoR03ChargedParticle, &b_MuonPFIsoR03ChargedParticle);
   fChain->SetBranchAddress("MuonPFIsoR03NeutralHadron", &MuonPFIsoR03NeutralHadron, &b_MuonPFIsoR03NeutralHadron);
   fChain->SetBranchAddress("MuonPFIsoR03NeutralHadronHT", &MuonPFIsoR03NeutralHadronHT, &b_MuonPFIsoR03NeutralHadronHT);
   fChain->SetBranchAddress("MuonPFIsoR03PU", &MuonPFIsoR03PU, &b_MuonPFIsoR03PU);
   fChain->SetBranchAddress("MuonPFIsoR03Photon", &MuonPFIsoR03Photon, &b_MuonPFIsoR03Photon);
   fChain->SetBranchAddress("MuonPFIsoR03PhotonHT", &MuonPFIsoR03PhotonHT, &b_MuonPFIsoR03PhotonHT);
   fChain->SetBranchAddress("MuonPFIsoR04ChargedHadron", &MuonPFIsoR04ChargedHadron, &b_MuonPFIsoR04ChargedHadron);
   fChain->SetBranchAddress("MuonPFIsoR04ChargedParticle", &MuonPFIsoR04ChargedParticle, &b_MuonPFIsoR04ChargedParticle);
   fChain->SetBranchAddress("MuonPFIsoR04NeutralHadron", &MuonPFIsoR04NeutralHadron, &b_MuonPFIsoR04NeutralHadron);
   fChain->SetBranchAddress("MuonPFIsoR04NeutralHadronHT", &MuonPFIsoR04NeutralHadronHT, &b_MuonPFIsoR04NeutralHadronHT);
   fChain->SetBranchAddress("MuonPFIsoR04PU", &MuonPFIsoR04PU, &b_MuonPFIsoR04PU);
   fChain->SetBranchAddress("MuonPFIsoR04Photon", &MuonPFIsoR04Photon, &b_MuonPFIsoR04Photon);
   fChain->SetBranchAddress("MuonPFIsoR04PhotonHT", &MuonPFIsoR04PhotonHT, &b_MuonPFIsoR04PhotonHT);
   fChain->SetBranchAddress("MuonPhi", &MuonPhi, &b_MuonPhi);
   fChain->SetBranchAddress("MuonPhiError", &MuonPhiError, &b_MuonPhiError);
   fChain->SetBranchAddress("MuonPrimaryVertexDXY", &MuonPrimaryVertexDXY, &b_MuonPrimaryVertexDXY);
   fChain->SetBranchAddress("MuonPrimaryVertexDXYError", &MuonPrimaryVertexDXYError, &b_MuonPrimaryVertexDXYError);
   fChain->SetBranchAddress("MuonPt", &MuonPt, &b_MuonPt);
   fChain->SetBranchAddress("MuonPtError", &MuonPtError, &b_MuonPtError);
   fChain->SetBranchAddress("MuonQOverPError", &MuonQOverPError, &b_MuonQOverPError);
   fChain->SetBranchAddress("MuonTimeCompatibility", &MuonTimeCompatibility, &b_MuonTimeCompatibility);
   fChain->SetBranchAddress("MuonTrackChi2", &MuonTrackChi2, &b_MuonTrackChi2);
   fChain->SetBranchAddress("MuonTrackerIsoSumPT", &MuonTrackerIsoSumPT, &b_MuonTrackerIsoSumPT);
   fChain->SetBranchAddress("MuonTrkD0", &MuonTrkD0, &b_MuonTrkD0);
   fChain->SetBranchAddress("MuonTrkD0Error", &MuonTrkD0Error, &b_MuonTrkD0Error);
   fChain->SetBranchAddress("MuonTrkDz", &MuonTrkDz, &b_MuonTrkDz);
   fChain->SetBranchAddress("MuonTrkDzError", &MuonTrkDzError, &b_MuonTrkDzError);
   fChain->SetBranchAddress("MuonTrkEta", &MuonTrkEta, &b_MuonTrkEta);
   fChain->SetBranchAddress("MuonTrkEtaError", &MuonTrkEtaError, &b_MuonTrkEtaError);
   fChain->SetBranchAddress("MuonTrkIso", &MuonTrkIso, &b_MuonTrkIso);
   fChain->SetBranchAddress("MuonTrkPhi", &MuonTrkPhi, &b_MuonTrkPhi);
   fChain->SetBranchAddress("MuonTrkPhiError", &MuonTrkPhiError, &b_MuonTrkPhiError);
   fChain->SetBranchAddress("MuonTrkPt", &MuonTrkPt, &b_MuonTrkPt);
   fChain->SetBranchAddress("MuonTrkPtError", &MuonTrkPtError, &b_MuonTrkPtError);
   fChain->SetBranchAddress("MuonTrkValidFractionOfHits", &MuonTrkValidFractionOfHits, &b_MuonTrkValidFractionOfHits);
   fChain->SetBranchAddress("MuonTrkVx", &MuonTrkVx, &b_MuonTrkVx);
   fChain->SetBranchAddress("MuonTrkVy", &MuonTrkVy, &b_MuonTrkVy);
   fChain->SetBranchAddress("MuonTrkVz", &MuonTrkVz, &b_MuonTrkVz);
   fChain->SetBranchAddress("MuonVtxDistXY", &MuonVtxDistXY, &b_MuonVtxDistXY);
   fChain->SetBranchAddress("MuonVtxDistZ", &MuonVtxDistZ, &b_MuonVtxDistZ);
   fChain->SetBranchAddress("PFCandEnergyLeptLink", &PFCandEnergyLeptLink, &b_PFCandEnergyLeptLink);
   fChain->SetBranchAddress("PFCandEtaLeptLink", &PFCandEtaLeptLink, &b_PFCandEtaLeptLink);
   fChain->SetBranchAddress("PFCandPhiLeptLink", &PFCandPhiLeptLink, &b_PFCandPhiLeptLink);
   fChain->SetBranchAddress("PFCandPtLeptLink", &PFCandPtLeptLink, &b_PFCandPtLeptLink);
   fChain->SetBranchAddress("PFJetBestVertexTrackAssociationFactor", &PFJetBestVertexTrackAssociationFactor, &b_PFJetBestVertexTrackAssociationFactor);
   fChain->SetBranchAddress("PFJetBeta", &PFJetBeta, &b_PFJetBeta);
   fChain->SetBranchAddress("PFJetBetaClassic", &PFJetBetaClassic, &b_PFJetBetaClassic);
   fChain->SetBranchAddress("PFJetBetaStar", &PFJetBetaStar, &b_PFJetBetaStar);
   fChain->SetBranchAddress("PFJetBetaStarClassic", &PFJetBetaStarClassic, &b_PFJetBetaStarClassic);
   fChain->SetBranchAddress("PFJetChargedEmEnergyFraction", &PFJetChargedEmEnergyFraction, &b_PFJetChargedEmEnergyFraction);
   fChain->SetBranchAddress("PFJetChargedHadronEnergyFraction", &PFJetChargedHadronEnergyFraction, &b_PFJetChargedHadronEnergyFraction);
   fChain->SetBranchAddress("PFJetChargedMuEnergyFraction", &PFJetChargedMuEnergyFraction, &b_PFJetChargedMuEnergyFraction);
   fChain->SetBranchAddress("PFJetClosestVertexWeighted3DSeparation", &PFJetClosestVertexWeighted3DSeparation, &b_PFJetClosestVertexWeighted3DSeparation);
   fChain->SetBranchAddress("PFJetClosestVertexWeightedXYSeparation", &PFJetClosestVertexWeightedXYSeparation, &b_PFJetClosestVertexWeightedXYSeparation);
   fChain->SetBranchAddress("PFJetClosestVertexWeightedZSeparation", &PFJetClosestVertexWeightedZSeparation, &b_PFJetClosestVertexWeightedZSeparation);
   fChain->SetBranchAddress("PFJetCombinedInclusiveSecondaryVertexBTag", &PFJetCombinedInclusiveSecondaryVertexBTag, &b_PFJetCombinedInclusiveSecondaryVertexBTag);
   fChain->SetBranchAddress("PFJetCombinedMVABTag", &PFJetCombinedMVABTag, &b_PFJetCombinedMVABTag);
   fChain->SetBranchAddress("PFJetCombinedSecondaryVertexBTag", &PFJetCombinedSecondaryVertexBTag, &b_PFJetCombinedSecondaryVertexBTag);
   fChain->SetBranchAddress("PFJetCombinedSecondaryVertexMVABTag", &PFJetCombinedSecondaryVertexMVABTag, &b_PFJetCombinedSecondaryVertexMVABTag);
   fChain->SetBranchAddress("PFJetElectronEnergyFraction", &PFJetElectronEnergyFraction, &b_PFJetElectronEnergyFraction);
   fChain->SetBranchAddress("PFJetEnergy", &PFJetEnergy, &b_PFJetEnergy);
   fChain->SetBranchAddress("PFJetEnergyRaw", &PFJetEnergyRaw, &b_PFJetEnergyRaw);
   fChain->SetBranchAddress("PFJetEta", &PFJetEta, &b_PFJetEta);
   fChain->SetBranchAddress("PFJetHFEMEnergyFraction", &PFJetHFEMEnergyFraction, &b_PFJetHFEMEnergyFraction);
   fChain->SetBranchAddress("PFJetHFHadronEnergyFraction", &PFJetHFHadronEnergyFraction, &b_PFJetHFHadronEnergyFraction);
   fChain->SetBranchAddress("PFJetJECUnc", &PFJetJECUnc, &b_PFJetJECUnc);
   fChain->SetBranchAddress("PFJetJetBProbabilityBTag", &PFJetJetBProbabilityBTag, &b_PFJetJetBProbabilityBTag);
   fChain->SetBranchAddress("PFJetJetProbabilityBTag", &PFJetJetProbabilityBTag, &b_PFJetJetProbabilityBTag);
   fChain->SetBranchAddress("PFJetL1FastJetJEC", &PFJetL1FastJetJEC, &b_PFJetL1FastJetJEC);
   fChain->SetBranchAddress("PFJetL1OffsetJEC", &PFJetL1OffsetJEC, &b_PFJetL1OffsetJEC);
   fChain->SetBranchAddress("PFJetL2L3ResJEC", &PFJetL2L3ResJEC, &b_PFJetL2L3ResJEC);
   fChain->SetBranchAddress("PFJetL2RelJEC", &PFJetL2RelJEC, &b_PFJetL2RelJEC);
   fChain->SetBranchAddress("PFJetL3AbsJEC", &PFJetL3AbsJEC, &b_PFJetL3AbsJEC);
   fChain->SetBranchAddress("PFJetMuonEnergyFraction", &PFJetMuonEnergyFraction, &b_PFJetMuonEnergyFraction);
   fChain->SetBranchAddress("PFJetNeutralEmEnergyFraction", &PFJetNeutralEmEnergyFraction, &b_PFJetNeutralEmEnergyFraction);
   fChain->SetBranchAddress("PFJetNeutralHadronEnergyFraction", &PFJetNeutralHadronEnergyFraction, &b_PFJetNeutralHadronEnergyFraction);
   fChain->SetBranchAddress("PFJetPhi", &PFJetPhi, &b_PFJetPhi);
   fChain->SetBranchAddress("PFJetPhotonEnergyFraction", &PFJetPhotonEnergyFraction, &b_PFJetPhotonEnergyFraction);
   fChain->SetBranchAddress("PFJetPt", &PFJetPt, &b_PFJetPt);
   fChain->SetBranchAddress("PFJetPtRaw", &PFJetPtRaw, &b_PFJetPtRaw);
   fChain->SetBranchAddress("PFJetSimpleSecondaryVertexHighEffBTag", &PFJetSimpleSecondaryVertexHighEffBTag, &b_PFJetSimpleSecondaryVertexHighEffBTag);
   fChain->SetBranchAddress("PFJetSimpleSecondaryVertexHighPurBTag", &PFJetSimpleSecondaryVertexHighPurBTag, &b_PFJetSimpleSecondaryVertexHighPurBTag);
   fChain->SetBranchAddress("PFJetSoftElectronByIP3dBTag", &PFJetSoftElectronByIP3dBTag, &b_PFJetSoftElectronByIP3dBTag);
   fChain->SetBranchAddress("PFJetSoftElectronByPtBTag", &PFJetSoftElectronByPtBTag, &b_PFJetSoftElectronByPtBTag);
   fChain->SetBranchAddress("PFJetSoftMuonBTag", &PFJetSoftMuonBTag, &b_PFJetSoftMuonBTag);
   fChain->SetBranchAddress("PFJetSoftMuonByIP3dBTag", &PFJetSoftMuonByIP3dBTag, &b_PFJetSoftMuonByIP3dBTag);
   fChain->SetBranchAddress("PFJetSoftMuonByPtBTag", &PFJetSoftMuonByPtBTag, &b_PFJetSoftMuonByPtBTag);
   fChain->SetBranchAddress("PFJetTrackCountingHighEffBTag", &PFJetTrackCountingHighEffBTag, &b_PFJetTrackCountingHighEffBTag);
   fChain->SetBranchAddress("PFJetTrackCountingHighPurBTag", &PFJetTrackCountingHighPurBTag, &b_PFJetTrackCountingHighPurBTag);
   fChain->SetBranchAddress("PFMET", &PFMET, &b_PFMET);
   fChain->SetBranchAddress("PFMETPhi", &PFMETPhi, &b_PFMETPhi);
   fChain->SetBranchAddress("PFMETSig", &PFMETSig, &b_PFMETSig);
   fChain->SetBranchAddress("PFMETSigMatrixDXX", &PFMETSigMatrixDXX, &b_PFMETSigMatrixDXX);
   fChain->SetBranchAddress("PFMETSigMatrixDXY", &PFMETSigMatrixDXY, &b_PFMETSigMatrixDXY);
   fChain->SetBranchAddress("PFMETSigMatrixDYX", &PFMETSigMatrixDYX, &b_PFMETSigMatrixDYX);
   fChain->SetBranchAddress("PFMETSigMatrixDYY", &PFMETSigMatrixDYY, &b_PFMETSigMatrixDYY);
   fChain->SetBranchAddress("PFSumET", &PFSumET, &b_PFSumET);
   fChain->SetBranchAddress("PFMETPhiType01Cor", &PFMETPhiType01Cor, &b_PFMETPhiType01Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDXXType01Cor", &PFMETSigMatrixDXXType01Cor, &b_PFMETSigMatrixDXXType01Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDXYType01Cor", &PFMETSigMatrixDXYType01Cor, &b_PFMETSigMatrixDXYType01Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDYXType01Cor", &PFMETSigMatrixDYXType01Cor, &b_PFMETSigMatrixDYXType01Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDYYType01Cor", &PFMETSigMatrixDYYType01Cor, &b_PFMETSigMatrixDYYType01Cor);
   fChain->SetBranchAddress("PFMETSigType01Cor", &PFMETSigType01Cor, &b_PFMETSigType01Cor);
   fChain->SetBranchAddress("PFMETType01Cor", &PFMETType01Cor, &b_PFMETType01Cor);
   fChain->SetBranchAddress("PFSumETType01Cor", &PFSumETType01Cor, &b_PFSumETType01Cor);
   fChain->SetBranchAddress("PFMETPhiType01XYCor", &PFMETPhiType01XYCor, &b_PFMETPhiType01XYCor);
   fChain->SetBranchAddress("PFMETSigMatrixDXXType01XYCor", &PFMETSigMatrixDXXType01XYCor, &b_PFMETSigMatrixDXXType01XYCor);
   fChain->SetBranchAddress("PFMETSigMatrixDXYType01XYCor", &PFMETSigMatrixDXYType01XYCor, &b_PFMETSigMatrixDXYType01XYCor);
   fChain->SetBranchAddress("PFMETSigMatrixDYXType01XYCor", &PFMETSigMatrixDYXType01XYCor, &b_PFMETSigMatrixDYXType01XYCor);
   fChain->SetBranchAddress("PFMETSigMatrixDYYType01XYCor", &PFMETSigMatrixDYYType01XYCor, &b_PFMETSigMatrixDYYType01XYCor);
   fChain->SetBranchAddress("PFMETSigType01XYCor", &PFMETSigType01XYCor, &b_PFMETSigType01XYCor);
   fChain->SetBranchAddress("PFMETType01XYCor", &PFMETType01XYCor, &b_PFMETType01XYCor);
   fChain->SetBranchAddress("PFSumETType01XYCor", &PFSumETType01XYCor, &b_PFSumETType01XYCor);
   fChain->SetBranchAddress("PFMETPhiType1Cor", &PFMETPhiType1Cor, &b_PFMETPhiType1Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDXXType1Cor", &PFMETSigMatrixDXXType1Cor, &b_PFMETSigMatrixDXXType1Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDXYType1Cor", &PFMETSigMatrixDXYType1Cor, &b_PFMETSigMatrixDXYType1Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDYXType1Cor", &PFMETSigMatrixDYXType1Cor, &b_PFMETSigMatrixDYXType1Cor);
   fChain->SetBranchAddress("PFMETSigMatrixDYYType1Cor", &PFMETSigMatrixDYYType1Cor, &b_PFMETSigMatrixDYYType1Cor);
   fChain->SetBranchAddress("PFMETSigType1Cor", &PFMETSigType1Cor, &b_PFMETSigType1Cor);
   fChain->SetBranchAddress("PFMETType1Cor", &PFMETType1Cor, &b_PFMETType1Cor);
   fChain->SetBranchAddress("PFSumETType1Cor", &PFSumETType1Cor, &b_PFSumETType1Cor);
   fChain->SetBranchAddress("PhotonAlpha", &PhotonAlpha, &b_PhotonAlpha);
   fChain->SetBranchAddress("PhotonChi2ConvPhot", &PhotonChi2ConvPhot, &b_PhotonChi2ConvPhot);
   fChain->SetBranchAddress("PhotonDPhiTracksAtVtxConvPhot", &PhotonDPhiTracksAtVtxConvPhot, &b_PhotonDPhiTracksAtVtxConvPhot);
   fChain->SetBranchAddress("PhotonDistOfMinApproachConvPhot", &PhotonDistOfMinApproachConvPhot, &b_PhotonDistOfMinApproachConvPhot);
   fChain->SetBranchAddress("PhotonE2OverE9", &PhotonE2OverE9, &b_PhotonE2OverE9);
   fChain->SetBranchAddress("PhotonE3x3", &PhotonE3x3, &b_PhotonE3x3);
   fChain->SetBranchAddress("PhotonE4SwissCross", &PhotonE4SwissCross, &b_PhotonE4SwissCross);
   fChain->SetBranchAddress("PhotonE5x5", &PhotonE5x5, &b_PhotonE5x5);
   fChain->SetBranchAddress("PhotonEOverPConvPhot", &PhotonEOverPConvPhot, &b_PhotonEOverPConvPhot);
   fChain->SetBranchAddress("PhotonEcalIsoDR03", &PhotonEcalIsoDR03, &b_PhotonEcalIsoDR03);
   fChain->SetBranchAddress("PhotonEcalIsoDR04", &PhotonEcalIsoDR04, &b_PhotonEcalIsoDR04);
   fChain->SetBranchAddress("PhotonEnergy", &PhotonEnergy, &b_PhotonEnergy);
   fChain->SetBranchAddress("PhotonEta", &PhotonEta, &b_PhotonEta);
   fChain->SetBranchAddress("PhotonHcalIsoDR03", &PhotonHcalIsoDR03, &b_PhotonHcalIsoDR03);
   fChain->SetBranchAddress("PhotonHcalIsoDR03FullCone", &PhotonHcalIsoDR03FullCone, &b_PhotonHcalIsoDR03FullCone);
   fChain->SetBranchAddress("PhotonHcalIsoDR04", &PhotonHcalIsoDR04, &b_PhotonHcalIsoDR04);
   fChain->SetBranchAddress("PhotonHcalIsoDR04FullCone", &PhotonHcalIsoDR04FullCone, &b_PhotonHcalIsoDR04FullCone);
   fChain->SetBranchAddress("PhotonHoE", &PhotonHoE, &b_PhotonHoE);
   fChain->SetBranchAddress("PhotonNDofConvPhot", &PhotonNDofConvPhot, &b_PhotonNDofConvPhot);
   fChain->SetBranchAddress("PhotonPairCotThetaSeparationConvPhot", &PhotonPairCotThetaSeparationConvPhot, &b_PhotonPairCotThetaSeparationConvPhot);
   fChain->SetBranchAddress("PhotonPairInvariantMassConvPhot", &PhotonPairInvariantMassConvPhot, &b_PhotonPairInvariantMassConvPhot);
   fChain->SetBranchAddress("PhotonPairMomentumxConvPhot", &PhotonPairMomentumxConvPhot, &b_PhotonPairMomentumxConvPhot);
   fChain->SetBranchAddress("PhotonPairMomentumyConvPhot", &PhotonPairMomentumyConvPhot, &b_PhotonPairMomentumyConvPhot);
   fChain->SetBranchAddress("PhotonPairMomentumzConvPhot", &PhotonPairMomentumzConvPhot, &b_PhotonPairMomentumzConvPhot);
   fChain->SetBranchAddress("PhotonPhi", &PhotonPhi, &b_PhotonPhi);
   fChain->SetBranchAddress("PhotonPt", &PhotonPt, &b_PhotonPt);
   fChain->SetBranchAddress("PhotonSCenergy", &PhotonSCenergy, &b_PhotonSCenergy);
   fChain->SetBranchAddress("PhotonSCeta", &PhotonSCeta, &b_PhotonSCeta);
   fChain->SetBranchAddress("PhotonSCphi", &PhotonSCphi, &b_PhotonSCphi);
   fChain->SetBranchAddress("PhotonSCseedEnergy", &PhotonSCseedEnergy, &b_PhotonSCseedEnergy);
   fChain->SetBranchAddress("PhotonSEtaEta", &PhotonSEtaEta, &b_PhotonSEtaEta);
   fChain->SetBranchAddress("PhotonSEtaPhi", &PhotonSEtaPhi, &b_PhotonSEtaPhi);
   fChain->SetBranchAddress("PhotonSMajMaj", &PhotonSMajMaj, &b_PhotonSMajMaj);
   fChain->SetBranchAddress("PhotonSMinMin", &PhotonSMinMin, &b_PhotonSMinMin);
   fChain->SetBranchAddress("PhotonSPhiPhi", &PhotonSPhiPhi, &b_PhotonSPhiPhi);
   fChain->SetBranchAddress("PhotonSigmaIEtaIEta", &PhotonSigmaIEtaIEta, &b_PhotonSigmaIEtaIEta);
   fChain->SetBranchAddress("PhotonTimeSeed", &PhotonTimeSeed, &b_PhotonTimeSeed);
   fChain->SetBranchAddress("PhotonTrkIsoHollowDR03", &PhotonTrkIsoHollowDR03, &b_PhotonTrkIsoHollowDR03);
   fChain->SetBranchAddress("PhotonTrkIsoHollowDR04", &PhotonTrkIsoHollowDR04, &b_PhotonTrkIsoHollowDR04);
   fChain->SetBranchAddress("PhotonTrkIsoSolidDR03", &PhotonTrkIsoSolidDR03, &b_PhotonTrkIsoSolidDR03);
   fChain->SetBranchAddress("PhotonTrkIsoSolidDR04", &PhotonTrkIsoSolidDR04, &b_PhotonTrkIsoSolidDR04);
   fChain->SetBranchAddress("PhotonXVtxConvPhot", &PhotonXVtxConvPhot, &b_PhotonXVtxConvPhot);
   fChain->SetBranchAddress("PhotonYVtxConvPhot", &PhotonYVtxConvPhot, &b_PhotonYVtxConvPhot);
   fChain->SetBranchAddress("PhotonZVtxConvPhot", &PhotonZVtxConvPhot, &b_PhotonZVtxConvPhot);
   fChain->SetBranchAddress("TCMET", &TCMET, &b_TCMET);
   fChain->SetBranchAddress("TCMETPhi", &TCMETPhi, &b_TCMETPhi);
   fChain->SetBranchAddress("TCSumET", &TCSumET, &b_TCSumET);
   fChain->SetBranchAddress("VertexChi2", &VertexChi2, &b_VertexChi2);
   fChain->SetBranchAddress("VertexNDF", &VertexNDF, &b_VertexNDF);
   fChain->SetBranchAddress("VertexRho", &VertexRho, &b_VertexRho);
   fChain->SetBranchAddress("VertexX", &VertexX, &b_VertexX);
   fChain->SetBranchAddress("VertexXErr", &VertexXErr, &b_VertexXErr);
   fChain->SetBranchAddress("VertexY", &VertexY, &b_VertexY);
   fChain->SetBranchAddress("VertexYErr", &VertexYErr, &b_VertexYErr);
   fChain->SetBranchAddress("VertexZ", &VertexZ, &b_VertexZ);
   fChain->SetBranchAddress("VertexZErr", &VertexZErr, &b_VertexZErr);
   fChain->SetBranchAddress("PileUpInteractionsTrue", &PileUpInteractionsTrue, &b_PileUpInteractionsTrue);
   fChain->SetBranchAddress("HLTFilterObjEta", &HLTFilterObjEta, &b_HLTFilterObjEta);
   fChain->SetBranchAddress("HLTFilterObjPhi", &HLTFilterObjPhi, &b_HLTFilterObjPhi);
   fChain->SetBranchAddress("HLTFilterObjPt", &HLTFilterObjPt, &b_HLTFilterObjPt);
   fChain->SetBranchAddress("ElectronCharge", &ElectronCharge, &b_ElectronCharge);
   fChain->SetBranchAddress("ElectronClassif", &ElectronClassif, &b_ElectronClassif);
   fChain->SetBranchAddress("ElectronMissingHits", &ElectronMissingHits, &b_ElectronMissingHits);
   fChain->SetBranchAddress("ElectronMissingHitsEG", &ElectronMissingHitsEG, &b_ElectronMissingHitsEG);
   fChain->SetBranchAddress("ElectronNumberOfBrems", &ElectronNumberOfBrems, &b_ElectronNumberOfBrems);
   fChain->SetBranchAddress("ElectronOverlaps", &ElectronOverlaps, &b_ElectronOverlaps);
   fChain->SetBranchAddress("ElectronPassEGammaIDEoP", &ElectronPassEGammaIDEoP, &b_ElectronPassEGammaIDEoP);
   fChain->SetBranchAddress("ElectronPassEGammaIDLoose", &ElectronPassEGammaIDLoose, &b_ElectronPassEGammaIDLoose);
   fChain->SetBranchAddress("ElectronPassEGammaIDMedium", &ElectronPassEGammaIDMedium, &b_ElectronPassEGammaIDMedium);
   fChain->SetBranchAddress("ElectronPassEGammaIDTight", &ElectronPassEGammaIDTight, &b_ElectronPassEGammaIDTight);
   fChain->SetBranchAddress("ElectronPassEGammaIDTrigTight", &ElectronPassEGammaIDTrigTight, &b_ElectronPassEGammaIDTrigTight);
   fChain->SetBranchAddress("ElectronPassEGammaIDTrigWP70", &ElectronPassEGammaIDTrigWP70, &b_ElectronPassEGammaIDTrigWP70);
   fChain->SetBranchAddress("ElectronPassEGammaIDVeto", &ElectronPassEGammaIDVeto, &b_ElectronPassEGammaIDVeto);
   fChain->SetBranchAddress("ElectronPassId", &ElectronPassId, &b_ElectronPassId);
   fChain->SetBranchAddress("ElectronPassIsoPAT", &ElectronPassIsoPAT, &b_ElectronPassIsoPAT);
   fChain->SetBranchAddress("ElectronVtxIndex", &ElectronVtxIndex, &b_ElectronVtxIndex);
   fChain->SetBranchAddress("GenWElectronMotherIndex", &GenWElectronMotherIndex, &b_GenWElectronMotherIndex);
   fChain->SetBranchAddress("GenWElectronNumDaught", &GenWElectronNumDaught, &b_GenWElectronNumDaught);
   fChain->SetBranchAddress("GenWElectronPdgId", &GenWElectronPdgId, &b_GenWElectronPdgId);
   fChain->SetBranchAddress("GenWElectronStatus", &GenWElectronStatus, &b_GenWElectronStatus);
   fChain->SetBranchAddress("GenWElectronTauDecayMode", &GenWElectronTauDecayMode, &b_GenWElectronTauDecayMode);
   fChain->SetBranchAddress("GenZElectronMotherIndex", &GenZElectronMotherIndex, &b_GenZElectronMotherIndex);
   fChain->SetBranchAddress("GenZElectronNumDaught", &GenZElectronNumDaught, &b_GenZElectronNumDaught);
   fChain->SetBranchAddress("GenZElectronPdgId", &GenZElectronPdgId, &b_GenZElectronPdgId);
   fChain->SetBranchAddress("GenZElectronStatus", &GenZElectronStatus, &b_GenZElectronStatus);
   fChain->SetBranchAddress("GenZElectronTauDecayMode", &GenZElectronTauDecayMode, &b_GenZElectronTauDecayMode);
   fChain->SetBranchAddress("PileUpInteractions", &PileUpInteractions, &b_PileUpInteractions);
   fChain->SetBranchAddress("PileUpOriginBX", &PileUpOriginBX, &b_PileUpOriginBX);
   fChain->SetBranchAddress("GenWMuMotherIndex", &GenWMuMotherIndex, &b_GenWMuMotherIndex);
   fChain->SetBranchAddress("GenWMuNumDaught", &GenWMuNumDaught, &b_GenWMuNumDaught);
   fChain->SetBranchAddress("GenWMuPdgId", &GenWMuPdgId, &b_GenWMuPdgId);
   fChain->SetBranchAddress("GenWMuStatus", &GenWMuStatus, &b_GenWMuStatus);
   fChain->SetBranchAddress("GenWMuTauDecayMode", &GenWMuTauDecayMode, &b_GenWMuTauDecayMode);
   fChain->SetBranchAddress("GenZMuMotherIndex", &GenZMuMotherIndex, &b_GenZMuMotherIndex);
   fChain->SetBranchAddress("GenZMuNumDaught", &GenZMuNumDaught, &b_GenZMuNumDaught);
   fChain->SetBranchAddress("GenZMuPdgId", &GenZMuPdgId, &b_GenZMuPdgId);
   fChain->SetBranchAddress("GenZMuStatus", &GenZMuStatus, &b_GenZMuStatus);
   fChain->SetBranchAddress("GenZMuTauDecayMode", &GenZMuTauDecayMode, &b_GenZMuTauDecayMode);
   fChain->SetBranchAddress("GenParticleMotherIndex", &GenParticleMotherIndex, &b_GenParticleMotherIndex);
   fChain->SetBranchAddress("GenParticleNumDaught", &GenParticleNumDaught, &b_GenParticleNumDaught);
   fChain->SetBranchAddress("GenParticlePdgId", &GenParticlePdgId, &b_GenParticlePdgId);
   fChain->SetBranchAddress("GenParticleStatus", &GenParticleStatus, &b_GenParticleStatus);
   fChain->SetBranchAddress("GenParticleTauDecayMode", &GenParticleTauDecayMode, &b_GenParticleTauDecayMode);
   fChain->SetBranchAddress("GenWTauMotherIndex", &GenWTauMotherIndex, &b_GenWTauMotherIndex);
   fChain->SetBranchAddress("GenWTauNumDaught", &GenWTauNumDaught, &b_GenWTauNumDaught);
   fChain->SetBranchAddress("GenWTauPdgId", &GenWTauPdgId, &b_GenWTauPdgId);
   fChain->SetBranchAddress("GenWTauStatus", &GenWTauStatus, &b_GenWTauStatus);
   fChain->SetBranchAddress("GenWTauTauDecayMode", &GenWTauTauDecayMode, &b_GenWTauTauDecayMode);
   fChain->SetBranchAddress("GenZTauMotherIndex", &GenZTauMotherIndex, &b_GenZTauMotherIndex);
   fChain->SetBranchAddress("GenZTauNumDaught", &GenZTauNumDaught, &b_GenZTauNumDaught);
   fChain->SetBranchAddress("GenZTauPdgId", &GenZTauPdgId, &b_GenZTauPdgId);
   fChain->SetBranchAddress("GenZTauStatus", &GenZTauStatus, &b_GenZTauStatus);
   fChain->SetBranchAddress("GenZTauTauDecayMode", &GenZTauTauDecayMode, &b_GenZTauTauDecayMode);
   fChain->SetBranchAddress("HPSTauCharge", &HPSTauCharge, &b_HPSTauCharge);
   fChain->SetBranchAddress("HPSTauDecayMode", &HPSTauDecayMode, &b_HPSTauDecayMode);
   fChain->SetBranchAddress("HPSTauIsCaloTau", &HPSTauIsCaloTau, &b_HPSTauIsCaloTau);
   fChain->SetBranchAddress("HPSTauIsPFTau", &HPSTauIsPFTau, &b_HPSTauIsPFTau);
   fChain->SetBranchAddress("HPSTauVtxIndex", &HPSTauVtxIndex, &b_HPSTauVtxIndex);
   fChain->SetBranchAddress("MuonBestTrackVtxIndex", &MuonBestTrackVtxIndex, &b_MuonBestTrackVtxIndex);
   fChain->SetBranchAddress("MuonCharge", &MuonCharge, &b_MuonCharge);
   fChain->SetBranchAddress("MuonCocktailCharge", &MuonCocktailCharge, &b_MuonCocktailCharge);
   fChain->SetBranchAddress("MuonCocktailRefitID", &MuonCocktailRefitID, &b_MuonCocktailRefitID);
   fChain->SetBranchAddress("MuonCocktailTrkHits", &MuonCocktailTrkHits, &b_MuonCocktailTrkHits);
   fChain->SetBranchAddress("MuonGlobalTrkValidHits", &MuonGlobalTrkValidHits, &b_MuonGlobalTrkValidHits);
   fChain->SetBranchAddress("MuonIsGlobal", &MuonIsGlobal, &b_MuonIsGlobal);
   fChain->SetBranchAddress("MuonIsPF", &MuonIsPF, &b_MuonIsPF);
   fChain->SetBranchAddress("MuonIsTracker", &MuonIsTracker, &b_MuonIsTracker);
   fChain->SetBranchAddress("MuonPassID", &MuonPassID, &b_MuonPassID);
   fChain->SetBranchAddress("MuonPixelHits", &MuonPixelHits, &b_MuonPixelHits);
   fChain->SetBranchAddress("MuonSegmentMatches", &MuonSegmentMatches, &b_MuonSegmentMatches);
   fChain->SetBranchAddress("MuonStationMatches", &MuonStationMatches, &b_MuonStationMatches);
   fChain->SetBranchAddress("MuonTrackLayersWithMeasurement", &MuonTrackLayersWithMeasurement, &b_MuonTrackLayersWithMeasurement);
   fChain->SetBranchAddress("MuonTrkHits", &MuonTrkHits, &b_MuonTrkHits);
   fChain->SetBranchAddress("MuonTrkHitsTrackerOnly", &MuonTrkHitsTrackerOnly, &b_MuonTrkHitsTrackerOnly);
   fChain->SetBranchAddress("MuonTrkPixelHits", &MuonTrkPixelHits, &b_MuonTrkPixelHits);
   fChain->SetBranchAddress("MuonVtxIndex", &MuonVtxIndex, &b_MuonVtxIndex);
   fChain->SetBranchAddress("PFCandChargeLeptLink", &PFCandChargeLeptLink, &b_PFCandChargeLeptLink);
   fChain->SetBranchAddress("PFJetBestVertexTrackAssociationIndex", &PFJetBestVertexTrackAssociationIndex, &b_PFJetBestVertexTrackAssociationIndex);
   fChain->SetBranchAddress("PFJetChargedHadronMultiplicity", &PFJetChargedHadronMultiplicity, &b_PFJetChargedHadronMultiplicity);
   fChain->SetBranchAddress("PFJetChargedMultiplicity", &PFJetChargedMultiplicity, &b_PFJetChargedMultiplicity);
   fChain->SetBranchAddress("PFJetClosestVertex3DIndex", &PFJetClosestVertex3DIndex, &b_PFJetClosestVertex3DIndex);
   fChain->SetBranchAddress("PFJetClosestVertexXYIndex", &PFJetClosestVertexXYIndex, &b_PFJetClosestVertexXYIndex);
   fChain->SetBranchAddress("PFJetClosestVertexZIndex", &PFJetClosestVertexZIndex, &b_PFJetClosestVertexZIndex);
   fChain->SetBranchAddress("PFJetElectronMultiplicity", &PFJetElectronMultiplicity, &b_PFJetElectronMultiplicity);
   fChain->SetBranchAddress("PFJetHFEMMultiplicity", &PFJetHFEMMultiplicity, &b_PFJetHFEMMultiplicity);
   fChain->SetBranchAddress("PFJetHFHadronMultiplicity", &PFJetHFHadronMultiplicity, &b_PFJetHFHadronMultiplicity);
   fChain->SetBranchAddress("PFJetMuonMultiplicity", &PFJetMuonMultiplicity, &b_PFJetMuonMultiplicity);
   fChain->SetBranchAddress("PFJetNConstituents", &PFJetNConstituents, &b_PFJetNConstituents);
   fChain->SetBranchAddress("PFJetNeutralHadronMultiplicity", &PFJetNeutralHadronMultiplicity, &b_PFJetNeutralHadronMultiplicity);
   fChain->SetBranchAddress("PFJetNeutralMultiplicity", &PFJetNeutralMultiplicity, &b_PFJetNeutralMultiplicity);
   fChain->SetBranchAddress("PFJetPartonFlavour", &PFJetPartonFlavour, &b_PFJetPartonFlavour);
   fChain->SetBranchAddress("PFJetPassLooseID", &PFJetPassLooseID, &b_PFJetPassLooseID);
   fChain->SetBranchAddress("PFJetPassTightID", &PFJetPassTightID, &b_PFJetPassTightID);
   fChain->SetBranchAddress("PFJetPhotonMultiplicity", &PFJetPhotonMultiplicity, &b_PFJetPhotonMultiplicity);
   fChain->SetBranchAddress("PhotonNTracksConvPhot", &PhotonNTracksConvPhot, &b_PhotonNTracksConvPhot);
   fChain->SetBranchAddress("HLTInsideDatasetTriggerPrescales", &HLTInsideDatasetTriggerPrescales, &b_HLTInsideDatasetTriggerPrescales);
   fChain->SetBranchAddress("HLTOutsideDatasetTriggerPrescales", &HLTOutsideDatasetTriggerPrescales, &b_HLTOutsideDatasetTriggerPrescales);
   fChain->SetBranchAddress("L1PhysBits", &L1PhysBits, &b_L1PhysBits);
   fChain->SetBranchAddress("L1TechBits", &L1TechBits, &b_L1TechBits);
   fChain->SetBranchAddress("VertexNTracks", &VertexNTracks, &b_VertexNTracks);
   fChain->SetBranchAddress("VertexNTracksW05", &VertexNTracksW05, &b_VertexNTracksW05);
   fChain->SetBranchAddress("HLTFilterObjId", &HLTFilterObjId, &b_HLTFilterObjId);
   fChain->SetBranchAddress("bunch", &bunch, &b_bunch);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("ls", &ls, &b_ls);
   fChain->SetBranchAddress("orbit", &orbit, &b_orbit);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("ProcessID", &ProcessID, &b_ProcessID);
   Notify();
}

Bool_t MyClass_del::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass_del::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass_del::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_del_cxx
