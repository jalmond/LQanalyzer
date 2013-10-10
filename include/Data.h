//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 24 11:24:50 2012 by ROOT version 5.32/00
// from TTree tree/
// found on file: /mnt/hadoop/cms/store/user/fgior8/Summer12LJ/SingleMuB/RootTupleMakerV2_output_DATA_506_1_Y4H.root
//////////////////////////////////////////////////////////

#ifndef DATA_h
#define DATA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <string>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Data {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   Data();
   ~Data();

   Int_t    GetEntry(Long64_t entry);
   Int_t    Cut(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void Init(TTree *tree);
   Bool_t   Notify(); //remove if possible
   void     Show(Long64_t entry = -1); //remove if possible

   void setBranchStatus(void);
   
   Long64_t nentries;

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

};

#endif
