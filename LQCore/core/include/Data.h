//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 24 11:24:50 2012 by ROOT version 5.32/00
// from TTree tree/
// found on file: /mnt/hadoop/cms/store/user/fgior8/Summer12LJ/SingleMuB/RootTupleMakerV2_output_DATA_506_1_Y4H.root
//////////////////////////////////////////////////////////

#ifndef DATA_h
#define DATA_h

// STL include(s):
#include <string>
#include <vector>
#include <list>

#include <TROOT.h>


#include "LQCycleBaseNTuple.h"

// Forward declaration(s):
class TTree;
class TBranch;

class Data : public LQCycleBaseNTuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain


   Long64_t GetNEntries();

   TTree          *output_tree;

   Data();
   ~Data();

   Int_t    GetEntry(Long64_t entry);
   Int_t    Cut(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void Init(TTree *tree);
   Bool_t   Notify(); //remove if possible
   void     Show(Long64_t entry = -1); //remove if possible

   void setBranchStatus(void);


   /// Connect an input variable                                                
   template< typename T >
     bool ConnectVariable(  const char* branchName,
			    T& variable , TBranch* br);
   /// Specialisation for object pointers                                                                                                                                      
   template< typename T >
     bool ConnectVariable(const char* branchName,
			  T*& variable , TBranch* br);   

   void Reset();
   void ConnectVariables(Bool_t setall);

   void ConnectEvent();
   void ConnectMuons();
   void ConnectElectrons();
   void ConnectPFJets();
   void ConnectCaloJets();
   //ConnectPhotons();                                                                                                                                                           
   void ConnectTaus();
   void ConnectTruth();
   void ConnectTrigger();
   void ConnectAllBranches();
   void ConnectMET();

   Long64_t nentries;

   // Declaration of leaf types
   std::string          *HLTKey;
   std::vector<std::string>  *HLTInsideDatasetTriggerNames;
   std::vector<std::string>  *HLTOutsideDatasetTriggerNames;
   std::vector<std::string>  *HLTFilterName;
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
   std::vector<bool>    *ElectronGsfCtfCharge;
   std::vector<bool>    *ElectronGsfCtfScPixCharge;
   std::vector<bool>    *ElectronGsfScPixCharge;
   std::vector<bool>    *ElectronHLTDoubleEleMatched;
   std::vector<bool>    *ElectronHLTSingleEleMatched;
   std::vector<bool>    *ElectronHLTSingleEleWP80Matched;
   std::vector<bool>    *ElectronHasEcalDrivenSeed;
   std::vector<bool>    *ElectronHasMatchedConvPhot;
   std::vector<bool>    *ElectronHasTrackerDrivenSeed;
   std::vector<bool>    *ElectronIsEB;
   std::vector<bool>    *ElectronIsEE;
   std::vector<bool>    *MuonHLTSingleIsoMuonMatched;
   std::vector<bool>    *MuonHLTSingleMuonMatched;
   std::vector<bool>    *PhotonHasMatchedConvPhot;
   std::vector<bool>    *PhotonHasMatchedPromptEle;
   std::vector<bool>    *PhotonHasPixelSeed;
   std::vector<bool>    *PhotonIsEBEEGap;
   std::vector<bool>    *PhotonIsEBGap;
   std::vector<bool>    *PhotonIsEEGap;
   std::vector<bool>    *HLTInsideDatasetTriggerDecisions;
   std::vector<bool>    *HLTOutsideDatasetTriggerDecisions;
   std::vector<bool>    *VertexIsFake;
   Double_t        rhoForHEEP;
   Double_t        rhoJets;
   Double_t        rhoJetsCCPU;
   Double_t        rhoJetsCN;
   Double_t        rhoJetsCNT;
   Double_t        time;
   Double_t        PtHat;
   Double_t        Weight;
   std::vector<double>  *CaloMET;
   std::vector<double>  *CaloMETPhi;
   std::vector<double>  *CaloMETPhiUncorr;
   std::vector<double>  *CaloMETUncorr;
   std::vector<double>  *CaloSumET;
   std::vector<double>  *CaloSumETUncorr;
   std::vector<double>  *CaloMETPhiType1Cor;
   std::vector<double>  *CaloMETPhiUncorrType1Cor;
   std::vector<double>  *CaloMETType1Cor;
   std::vector<double>  *CaloMETUncorrType1Cor;
   std::vector<double>  *CaloSumETType1Cor;
   std::vector<double>  *CaloSumETUncorrType1Cor;
   std::vector<double>  *ElectronBeamSpotDXY;
   std::vector<double>  *ElectronBeamSpotDXYError;
   std::vector<double>  *ElectronCaloEnergy;
   std::vector<double>  *ElectronConvFitProb;
   std::vector<double>  *ElectronDCotTheta;
   std::vector<double>  *ElectronDeltaEtaTrkSC;
   std::vector<double>  *ElectronDeltaPhiTrkSC;
   std::vector<double>  *ElectronDist;
   std::vector<double>  *ElectronE1x5OverE5x5;
   std::vector<double>  *ElectronE2x5OverE5x5;
   std::vector<double>  *ElectronESuperClusterOverP;
   std::vector<double>  *ElectronEcalIsoDR03;
   std::vector<double>  *ElectronEcalIsoPAT;
   std::vector<double>  *ElectronEnergy;
   std::vector<double>  *ElectronEta;
   std::vector<double>  *ElectronFbrem;
   std::vector<double>  *ElectronHLTDoubleEleMatchEta;
   std::vector<double>  *ElectronHLTDoubleEleMatchPhi;
   std::vector<double>  *ElectronHLTDoubleEleMatchPt;
   std::vector<double>  *ElectronHLTSingleEleMatchEta;
   std::vector<double>  *ElectronHLTSingleEleMatchPhi;
   std::vector<double>  *ElectronHLTSingleEleMatchPt;
   std::vector<double>  *ElectronHLTSingleEleWP80MatchEta;
   std::vector<double>  *ElectronHLTSingleEleWP80MatchPhi;
   std::vector<double>  *ElectronHLTSingleEleWP80MatchPt;
   std::vector<double>  *ElectronHcalIsoD1DR03;
   std::vector<double>  *ElectronHcalIsoD2DR03;
   std::vector<double>  *ElectronHcalIsoDR03;
   std::vector<double>  *ElectronHcalIsoDR03FullCone;
   std::vector<double>  *ElectronHcalIsoPAT;
   std::vector<double>  *ElectronHoE;
   std::vector<double>  *ElectronLeadVtxDistXY;
   std::vector<double>  *ElectronLeadVtxDistZ;
   std::vector<double>  *ElectronMatchedGenParticleEta;
   std::vector<double>  *ElectronMatchedGenParticlePhi;
   std::vector<double>  *ElectronMatchedGenParticlePt;
   std::vector<double>  *ElectronPFChargedHadronIso03;
   std::vector<double>  *ElectronPFChargedHadronIso04;
   std::vector<double>  *ElectronPFNeutralHadronIso03;
   std::vector<double>  *ElectronPFNeutralHadronIso04;
   std::vector<double>  *ElectronPFPhotonIso03;
   std::vector<double>  *ElectronPFPhotonIso04;
   std::vector<double>  *ElectronPhi;
   std::vector<double>  *ElectronPrimaryVertexDXY;
   std::vector<double>  *ElectronPrimaryVertexDXYError;
   std::vector<double>  *ElectronPt;
   std::vector<double>  *ElectronPtHeep;
   std::vector<double>  *ElectronRelIsoPAT;
   std::vector<double>  *ElectronSCEta;
   std::vector<double>  *ElectronSCPhi;
   std::vector<double>  *ElectronSCPt;
   std::vector<double>  *ElectronSCRawEnergy;
   std::vector<double>  *ElectronSigmaEtaEta;
   std::vector<double>  *ElectronSigmaIEtaIEta;
   std::vector<double>  *ElectronTrackPt;
   std::vector<double>  *ElectronTrackValidFractionOfHits;
   std::vector<double>  *ElectronTrackVx;
   std::vector<double>  *ElectronTrackVy;
   std::vector<double>  *ElectronTrackVz;
   std::vector<double>  *ElectronTrkIsoDR03;
   std::vector<double>  *ElectronTrkIsoPAT;
   std::vector<double>  *ElectronVtxDistXY;
   std::vector<double>  *ElectronVtxDistZ;
   std::vector<double>  *GenWElectronEnergy;
   std::vector<double>  *GenWElectronEta;
   std::vector<double>  *GenWElectronP;
   std::vector<double>  *GenWElectronPhi;
   std::vector<double>  *GenWElectronPt;
   std::vector<double>  *GenWElectronPx;
   std::vector<double>  *GenWElectronPy;
   std::vector<double>  *GenWElectronPz;
   std::vector<double>  *GenWElectronTauVisibleEta;
   std::vector<double>  *GenWElectronTauVisiblePhi;
   std::vector<double>  *GenWElectronTauVisiblePt;
   std::vector<double>  *GenWElectronVX;
   std::vector<double>  *GenWElectronVY;
   std::vector<double>  *GenWElectronVZ;
   std::vector<double>  *GenZElectronEnergy;
   std::vector<double>  *GenZElectronEta;
   std::vector<double>  *GenZElectronP;
   std::vector<double>  *GenZElectronPhi;
   std::vector<double>  *GenZElectronPt;
   std::vector<double>  *GenZElectronPx;
   std::vector<double>  *GenZElectronPy;
   std::vector<double>  *GenZElectronPz;
   std::vector<double>  *GenZElectronTauVisibleEta;
   std::vector<double>  *GenZElectronTauVisiblePhi;
   std::vector<double>  *GenZElectronTauVisiblePt;
   std::vector<double>  *GenZElectronVX;
   std::vector<double>  *GenZElectronVY;
   std::vector<double>  *GenZElectronVZ;
   std::vector<double>  *PDFCTEQWeights;
   std::vector<double>  *PDFMSTWWeights;
   std::vector<double>  *PDFNNPDFWeights;
   std::vector<double>  *GenJetEMF;
   std::vector<double>  *GenJetEnergy;
   std::vector<double>  *GenJetEta;
   std::vector<double>  *GenJetHADF;
   std::vector<double>  *GenJetP;
   std::vector<double>  *GenJetPhi;
   std::vector<double>  *GenJetPt;
   std::vector<double>  *GenMETCalo;
   std::vector<double>  *GenMETPhiCalo;
   std::vector<double>  *GenSumETCalo;
   std::vector<double>  *GenMETPhiTrue;
   std::vector<double>  *GenMETTrue;
   std::vector<double>  *GenSumETTrue;
   std::vector<double>  *GenWMuEnergy;
   std::vector<double>  *GenWMuEta;
   std::vector<double>  *GenWMuP;
   std::vector<double>  *GenWMuPhi;
   std::vector<double>  *GenWMuPt;
   std::vector<double>  *GenWMuPx;
   std::vector<double>  *GenWMuPy;
   std::vector<double>  *GenWMuPz;
   std::vector<double>  *GenWMuTauVisibleEta;
   std::vector<double>  *GenWMuTauVisiblePhi;
   std::vector<double>  *GenWMuTauVisiblePt;
   std::vector<double>  *GenWMuVX;
   std::vector<double>  *GenWMuVY;
   std::vector<double>  *GenWMuVZ;
   std::vector<double>  *GenZMuEnergy;
   std::vector<double>  *GenZMuEta;
   std::vector<double>  *GenZMuP;
   std::vector<double>  *GenZMuPhi;
   std::vector<double>  *GenZMuPt;
   std::vector<double>  *GenZMuPx;
   std::vector<double>  *GenZMuPy;
   std::vector<double>  *GenZMuPz;
   std::vector<double>  *GenZMuTauVisibleEta;
   std::vector<double>  *GenZMuTauVisiblePhi;
   std::vector<double>  *GenZMuTauVisiblePt;
   std::vector<double>  *GenZMuVX;
   std::vector<double>  *GenZMuVY;
   std::vector<double>  *GenZMuVZ;
   std::vector<double>  *GenParticleEnergy;
   std::vector<double>  *GenParticleEta;
   std::vector<double>  *GenParticleP;
   std::vector<double>  *GenParticlePhi;
   std::vector<double>  *GenParticlePt;
   std::vector<double>  *GenParticlePx;
   std::vector<double>  *GenParticlePy;
   std::vector<double>  *GenParticlePz;
   std::vector<double>  *GenParticleTauVisibleEta;
   std::vector<double>  *GenParticleTauVisiblePhi;
   std::vector<double>  *GenParticleTauVisiblePt;
   std::vector<double>  *GenParticleVX;
   std::vector<double>  *GenParticleVY;
   std::vector<double>  *GenParticleVZ;
   std::vector<double>  *GenWTauEnergy;
   std::vector<double>  *GenWTauEta;
   std::vector<double>  *GenWTauP;
   std::vector<double>  *GenWTauPhi;
   std::vector<double>  *GenWTauPt;
   std::vector<double>  *GenWTauPx;
   std::vector<double>  *GenWTauPy;
   std::vector<double>  *GenWTauPz;
   std::vector<double>  *GenWTauTauVisibleEta;
   std::vector<double>  *GenWTauTauVisiblePhi;
   std::vector<double>  *GenWTauTauVisiblePt;
   std::vector<double>  *GenWTauVX;
   std::vector<double>  *GenWTauVY;
   std::vector<double>  *GenWTauVZ;
   std::vector<double>  *GenZTauEnergy;
   std::vector<double>  *GenZTauEta;
   std::vector<double>  *GenZTauP;
   std::vector<double>  *GenZTauPhi;
   std::vector<double>  *GenZTauPt;
   std::vector<double>  *GenZTauPx;
   std::vector<double>  *GenZTauPy;
   std::vector<double>  *GenZTauPz;
   std::vector<double>  *GenZTauTauVisibleEta;
   std::vector<double>  *GenZTauTauVisiblePhi;
   std::vector<double>  *GenZTauTauVisiblePt;
   std::vector<double>  *GenZTauVX;
   std::vector<double>  *GenZTauVY;
   std::vector<double>  *GenZTauVZ;
   std::vector<double>  *HPSTauAgainstElectronDeadECALDiscr;
   std::vector<double>  *HPSTauAgainstElectronLooseDiscr;
   std::vector<double>  *HPSTauAgainstElectronLooseMVA2Discr;
   std::vector<double>  *HPSTauAgainstElectronLooseMVA3Discr;
   std::vector<double>  *HPSTauAgainstElectronMVA2categoryDiscr;
   std::vector<double>  *HPSTauAgainstElectronMVA2rawDiscr;
   std::vector<double>  *HPSTauAgainstElectronMVA3categoryDiscr;
   std::vector<double>  *HPSTauAgainstElectronMVA3rawDiscr;
   std::vector<double>  *HPSTauAgainstElectronMVADiscr;
   std::vector<double>  *HPSTauAgainstElectronMediumDiscr;
   std::vector<double>  *HPSTauAgainstElectronMediumMVA2Discr;
   std::vector<double>  *HPSTauAgainstElectronMediumMVA3Discr;
   std::vector<double>  *HPSTauAgainstElectronTightDiscr;
   std::vector<double>  *HPSTauAgainstElectronTightMVA2Discr;
   std::vector<double>  *HPSTauAgainstElectronTightMVA3Discr;
   std::vector<double>  *HPSTauAgainstElectronVLooseMVA2Discr;
   std::vector<double>  *HPSTauAgainstElectronVTightMVA3Discr;
   std::vector<double>  *HPSTauAgainstMuonLoose2Discr;
   std::vector<double>  *HPSTauAgainstMuonLooseDiscr;
   std::vector<double>  *HPSTauAgainstMuonMedium2Discr;
   std::vector<double>  *HPSTauAgainstMuonMediumDiscr;
   std::vector<double>  *HPSTauAgainstMuonTight2Discr;
   std::vector<double>  *HPSTauAgainstMuonTightDiscr;
   std::vector<double>  *HPSTauBremsRecoveryEOverPLead;
   std::vector<double>  *HPSTauCombinedIsolationDeltaBetaCorr3HitsDiscr;
   std::vector<double>  *HPSTauDecayModeFindingDiscr;
   std::vector<double>  *HPSTauEcalStripSumEOverPLead;
   std::vector<double>  *HPSTauEmFraction;
   std::vector<double>  *HPSTauEt;
   std::vector<double>  *HPSTauEta;
   std::vector<double>  *HPSTauEtaLeadCharged;
   std::vector<double>  *HPSTauEtaetaMoment;
   std::vector<double>  *HPSTauEtaphiMoment;
   std::vector<double>  *HPSTauHcal3x3OverPLead;
   std::vector<double>  *HPSTauHcalMaxOverPLead;
   std::vector<double>  *HPSTauHcalTotOverPLead;
   std::vector<double>  *HPSTauIsolationMVArawDiscr;
   std::vector<double>  *HPSTauIsolationPFChargedHadrCandsPtSum;
   std::vector<double>  *HPSTauIsolationPFGammaCandsEtSum;
   std::vector<double>  *HPSTauLeadPFChargedHadrCandsignedSipt;
   std::vector<double>  *HPSTauLeadVtxDistXY;
   std::vector<double>  *HPSTauLeadVtxDistZ;
   std::vector<double>  *HPSTauLooseCombinedIsolationDeltaBetaCorr3HitsDiscr;
   std::vector<double>  *HPSTauLooseCombinedIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauLooseIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauLooseIsolationDiscr;
   std::vector<double>  *HPSTauLooseIsolationMVA2Discr;
   std::vector<double>  *HPSTauLooseIsolationMVADiscr;
   std::vector<double>  *HPSTauMatchedGenJetEta;
   std::vector<double>  *HPSTauMatchedGenJetPhi;
   std::vector<double>  *HPSTauMatchedGenJetPt;
   std::vector<double>  *HPSTauMatchedGenParticleEta;
   std::vector<double>  *HPSTauMatchedGenParticlePhi;
   std::vector<double>  *HPSTauMatchedGenParticlePt;
   std::vector<double>  *HPSTauMaximumHCALPFClusterEt;
   std::vector<double>  *HPSTauMediumCombinedIsolationDeltaBetaCorr3HitsDiscr;
   std::vector<double>  *HPSTauMediumCombinedIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauMediumIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauMediumIsolationDiscr;
   std::vector<double>  *HPSTauMediumIsolationMVA2Discr;
   std::vector<double>  *HPSTauMediumIsolationMVADiscr;
   std::vector<double>  *HPSTauPhi;
   std::vector<double>  *HPSTauPhiLeadCharged;
   std::vector<double>  *HPSTauPhiphiMoment;
   std::vector<double>  *HPSTauPt;
   std::vector<double>  *HPSTauPtLeadCharged;
   std::vector<double>  *HPSTauSignalPFChargedHadrCandsCount;
   std::vector<double>  *HPSTauSignalPFChargedHadrCandsEta;
   std::vector<double>  *HPSTauSignalPFChargedHadrCandsPhi;
   std::vector<double>  *HPSTauSignalPFChargedHadrCandsPt;
   std::vector<double>  *HPSTauSignalPFGammaCandsCount;
   std::vector<double>  *HPSTauSignalPFGammaCandsEta;
   std::vector<double>  *HPSTauSignalPFGammaCandsPhi;
   std::vector<double>  *HPSTauSignalPFGammaCandsPt;
   std::vector<double>  *HPSTauSignalPFNeutrHadrCandsCount;
   std::vector<double>  *HPSTauSignalPFNeutrHadrCandsEta;
   std::vector<double>  *HPSTauSignalPFNeutrHadrCandsPhi;
   std::vector<double>  *HPSTauSignalPFNeutrHadrCandsPt;
   std::vector<double>  *HPSTauTightCombinedIsolationDeltaBetaCorr3HitsDiscr;
   std::vector<double>  *HPSTauTightCombinedIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauTightIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauTightIsolationDiscr;
   std::vector<double>  *HPSTauTightIsolationMVA2Discr;
   std::vector<double>  *HPSTauTightIsolationMVADiscr;
   std::vector<double>  *HPSTauVLooseCombinedIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauVLooseIsolationDeltaBetaCorrDiscr;
   std::vector<double>  *HPSTauVLooseIsolationDiscr;
   std::vector<double>  *HPSTauVtxDistXY;
   std::vector<double>  *HPSTauVtxDistZ;
   std::vector<double>  *MuonBackToBackCompatibility;
   std::vector<double>  *MuonBeamSpotDXY;
   std::vector<double>  *MuonBeamSpotDXYError;
   std::vector<double>  *MuonBestTrackVtxDistXY;
   std::vector<double>  *MuonBestTrackVtxDistZ;
   std::vector<double>  *MuonCocktailEta;
   std::vector<double>  *MuonCocktailEtaError;
   std::vector<double>  *MuonCocktailGlobalChi2;
   std::vector<double>  *MuonCocktailP;
   std::vector<double>  *MuonCocktailPhi;
   std::vector<double>  *MuonCocktailPhiError;
   std::vector<double>  *MuonCocktailPt;
   std::vector<double>  *MuonCocktailPtError;
   std::vector<double>  *MuonCocktailQOverPError;
   std::vector<double>  *MuonCocktailTrkD0;
   std::vector<double>  *MuonCocktailTrkD0Error;
   std::vector<double>  *MuonCocktailTrkDz;
   std::vector<double>  *MuonCocktailTrkDzError;
   std::vector<double>  *MuonCocktailTrkValidFractionOfHits;
   std::vector<double>  *MuonCosmicCompatibility;
   std::vector<double>  *MuonEcalIso;
   std::vector<double>  *MuonEcalVetoIso;
   std::vector<double>  *MuonEnergy;
   std::vector<double>  *MuonEta;
   std::vector<double>  *MuonEtaError;
   std::vector<double>  *MuonGlobalChi2;
   std::vector<double>  *MuonHLTSingleIsoMuonMatchEta;
   std::vector<double>  *MuonHLTSingleIsoMuonMatchPhi;
   std::vector<double>  *MuonHLTSingleIsoMuonMatchPt;
   std::vector<double>  *MuonHLTSingleMuonMatchEta;
   std::vector<double>  *MuonHLTSingleMuonMatchPhi;
   std::vector<double>  *MuonHLTSingleMuonMatchPt;
   std::vector<double>  *MuonHOIso;
   std::vector<double>  *MuonHcalIso;
   std::vector<double>  *MuonHcalVetoIso;
   std::vector<double>  *MuonMatchedGenParticleEta;
   std::vector<double>  *MuonMatchedGenParticlePhi;
   std::vector<double>  *MuonMatchedGenParticlePt;
   std::vector<double>  *MuonOverlapCompatibility;
   std::vector<double>  *MuonP;
   std::vector<double>  *MuonPFIsoR03ChargedHadron;
   std::vector<double>  *MuonPFIsoR03ChargedParticle;
   std::vector<double>  *MuonPFIsoR03NeutralHadron;
   std::vector<double>  *MuonPFIsoR03NeutralHadronHT;
   std::vector<double>  *MuonPFIsoR03PU;
   std::vector<double>  *MuonPFIsoR03Photon;
   std::vector<double>  *MuonPFIsoR03PhotonHT;
   std::vector<double>  *MuonPFIsoR04ChargedHadron;
   std::vector<double>  *MuonPFIsoR04ChargedParticle;
   std::vector<double>  *MuonPFIsoR04NeutralHadron;
   std::vector<double>  *MuonPFIsoR04NeutralHadronHT;
   std::vector<double>  *MuonPFIsoR04PU;
   std::vector<double>  *MuonPFIsoR04Photon;
   std::vector<double>  *MuonPFIsoR04PhotonHT;
   std::vector<double>  *MuonPhi;
   std::vector<double>  *MuonPhiError;
   std::vector<double>  *MuonPrimaryVertexDXY;
   std::vector<double>  *MuonPrimaryVertexDXYError;
   std::vector<double>  *MuonPt;
   std::vector<double>  *MuonPtError;
   std::vector<double>  *MuonQOverPError;
   std::vector<double>  *MuonTimeCompatibility;
   std::vector<double>  *MuonTrackChi2;
   std::vector<double>  *MuonTrackerIsoSumPT;
   std::vector<double>  *MuonTrkD0;
   std::vector<double>  *MuonTrkD0Error;
   std::vector<double>  *MuonTrkDz;
   std::vector<double>  *MuonTrkDzError;
   std::vector<double>  *MuonTrkEta;
   std::vector<double>  *MuonTrkEtaError;
   std::vector<double>  *MuonTrkIso;
   std::vector<double>  *MuonTrkPhi;
   std::vector<double>  *MuonTrkPhiError;
   std::vector<double>  *MuonTrkPt;
   std::vector<double>  *MuonTrkPtError;
   std::vector<double>  *MuonTrkValidFractionOfHits;
   std::vector<double>  *MuonTrkVx;
   std::vector<double>  *MuonTrkVy;
   std::vector<double>  *MuonTrkVz;
   std::vector<double>  *MuonVtxDistXY;
   std::vector<double>  *MuonVtxDistZ;
   std::vector<double>  *PFCandEnergyLeptLink;
   std::vector<double>  *PFCandEtaLeptLink;
   std::vector<double>  *PFCandPhiLeptLink;
   std::vector<double>  *PFCandPtLeptLink;
   std::vector<double>  *PFJetBestVertexTrackAssociationFactor;
   std::vector<double>  *PFJetBeta;
   std::vector<double>  *PFJetBetaClassic;
   std::vector<double>  *PFJetBetaStar;
   std::vector<double>  *PFJetBetaStarClassic;
   std::vector<double>  *PFJetChargedEmEnergyFraction;
   std::vector<double>  *PFJetChargedHadronEnergyFraction;
   std::vector<double>  *PFJetChargedMuEnergyFraction;
   std::vector<double>  *PFJetClosestVertexWeighted3DSeparation;
   std::vector<double>  *PFJetClosestVertexWeightedXYSeparation;
   std::vector<double>  *PFJetClosestVertexWeightedZSeparation;
   std::vector<double>  *PFJetCombinedInclusiveSecondaryVertexBTag;
   std::vector<double>  *PFJetCombinedMVABTag;
   std::vector<double>  *PFJetCombinedSecondaryVertexBTag;
   std::vector<double>  *PFJetCombinedSecondaryVertexMVABTag;
   std::vector<double>  *PFJetElectronEnergyFraction;
   std::vector<double>  *PFJetEnergy;
   std::vector<double>  *PFJetEnergyRaw;
   std::vector<double>  *PFJetEta;
   std::vector<double>  *PFJetHFEMEnergyFraction;
   std::vector<double>  *PFJetHFHadronEnergyFraction;
   std::vector<double>  *PFJetJECUnc;
   std::vector<double>  *PFJetJetBProbabilityBTag;
   std::vector<double>  *PFJetJetProbabilityBTag;
   std::vector<double>  *PFJetL1FastJetJEC;
   std::vector<double>  *PFJetL1OffsetJEC;
   std::vector<double>  *PFJetL2L3ResJEC;
   std::vector<double>  *PFJetL2RelJEC;
   std::vector<double>  *PFJetL3AbsJEC;
   std::vector<double>  *PFJetMuonEnergyFraction;
   std::vector<double>  *PFJetNeutralEmEnergyFraction;
   std::vector<double>  *PFJetNeutralHadronEnergyFraction;
   std::vector<double>  *PFJetPhi;
   std::vector<double>  *PFJetPhotonEnergyFraction;
   std::vector<double>  *PFJetPt;
   std::vector<double>  *PFJetPtRaw;
   std::vector<double>  *PFJetSimpleSecondaryVertexHighEffBTag;
   std::vector<double>  *PFJetSimpleSecondaryVertexHighPurBTag;
   std::vector<double>  *PFJetSoftElectronByIP3dBTag;
   std::vector<double>  *PFJetSoftElectronByPtBTag;
   std::vector<double>  *PFJetSoftMuonBTag;
   std::vector<double>  *PFJetSoftMuonByIP3dBTag;
   std::vector<double>  *PFJetSoftMuonByPtBTag;
   std::vector<double>  *PFJetTrackCountingHighEffBTag;
   std::vector<double>  *PFJetTrackCountingHighPurBTag;
   std::vector<double>  *PFMET;
   std::vector<double>  *PFMETPhi;
   std::vector<double>  *PFMETSig;
   std::vector<double>  *PFMETSigMatrixDXX;
   std::vector<double>  *PFMETSigMatrixDXY;
   std::vector<double>  *PFMETSigMatrixDYX;
   std::vector<double>  *PFMETSigMatrixDYY;
   std::vector<double>  *PFSumET;
   std::vector<double>  *PFMETPhiType01Cor;
   std::vector<double>  *PFMETSigMatrixDXXType01Cor;
   std::vector<double>  *PFMETSigMatrixDXYType01Cor;
   std::vector<double>  *PFMETSigMatrixDYXType01Cor;
   std::vector<double>  *PFMETSigMatrixDYYType01Cor;
   std::vector<double>  *PFMETSigType01Cor;
   std::vector<double>  *PFMETType01Cor;
   std::vector<double>  *PFSumETType01Cor;
   std::vector<double>  *PFMETPhiType01XYCor;
   std::vector<double>  *PFMETSigMatrixDXXType01XYCor;
   std::vector<double>  *PFMETSigMatrixDXYType01XYCor;
   std::vector<double>  *PFMETSigMatrixDYXType01XYCor;
   std::vector<double>  *PFMETSigMatrixDYYType01XYCor;
   std::vector<double>  *PFMETSigType01XYCor;
   std::vector<double>  *PFMETType01XYCor;
   std::vector<double>  *PFSumETType01XYCor;
   std::vector<double>  *PFMETPhiType1Cor;
   std::vector<double>  *PFMETSigMatrixDXXType1Cor;
   std::vector<double>  *PFMETSigMatrixDXYType1Cor;
   std::vector<double>  *PFMETSigMatrixDYXType1Cor;
   std::vector<double>  *PFMETSigMatrixDYYType1Cor;
   std::vector<double>  *PFMETSigType1Cor;
   std::vector<double>  *PFMETType1Cor;
   std::vector<double>  *PFSumETType1Cor;
   std::vector<double>  *PhotonAlpha;
   std::vector<double>  *PhotonChi2ConvPhot;
   std::vector<double>  *PhotonDPhiTracksAtVtxConvPhot;
   std::vector<double>  *PhotonDistOfMinApproachConvPhot;
   std::vector<double>  *PhotonE2OverE9;
   std::vector<double>  *PhotonE3x3;
   std::vector<double>  *PhotonE4SwissCross;
   std::vector<double>  *PhotonE5x5;
   std::vector<double>  *PhotonEOverPConvPhot;
   std::vector<double>  *PhotonEcalIsoDR03;
   std::vector<double>  *PhotonEcalIsoDR04;
   std::vector<double>  *PhotonEnergy;
   std::vector<double>  *PhotonEta;
   std::vector<double>  *PhotonHcalIsoDR03;
   std::vector<double>  *PhotonHcalIsoDR03FullCone;
   std::vector<double>  *PhotonHcalIsoDR04;
   std::vector<double>  *PhotonHcalIsoDR04FullCone;
   std::vector<double>  *PhotonHoE;
   std::vector<double>  *PhotonNDofConvPhot;
   std::vector<double>  *PhotonPairCotThetaSeparationConvPhot;
   std::vector<double>  *PhotonPairInvariantMassConvPhot;
   std::vector<double>  *PhotonPairMomentumxConvPhot;
   std::vector<double>  *PhotonPairMomentumyConvPhot;
   std::vector<double>  *PhotonPairMomentumzConvPhot;
   std::vector<double>  *PhotonPhi;
   std::vector<double>  *PhotonPt;
   std::vector<double>  *PhotonSCenergy;
   std::vector<double>  *PhotonSCeta;
   std::vector<double>  *PhotonSCphi;
   std::vector<double>  *PhotonSCseedEnergy;
   std::vector<double>  *PhotonSEtaEta;
   std::vector<double>  *PhotonSEtaPhi;
   std::vector<double>  *PhotonSMajMaj;
   std::vector<double>  *PhotonSMinMin;
   std::vector<double>  *PhotonSPhiPhi;
   std::vector<double>  *PhotonSigmaIEtaIEta;
   std::vector<double>  *PhotonTimeSeed;
   std::vector<double>  *PhotonTrkIsoHollowDR03;
   std::vector<double>  *PhotonTrkIsoHollowDR04;
   std::vector<double>  *PhotonTrkIsoSolidDR03;
   std::vector<double>  *PhotonTrkIsoSolidDR04;
   std::vector<double>  *PhotonXVtxConvPhot;
   std::vector<double>  *PhotonYVtxConvPhot;
   std::vector<double>  *PhotonZVtxConvPhot;
   std::vector<double>  *TCMET;
   std::vector<double>  *TCMETPhi;
   std::vector<double>  *TCSumET;
   std::vector<double>  *VertexChi2;
   std::vector<double>  *VertexNDF;
   std::vector<double>  *VertexRho;
   std::vector<double>  *VertexX;
   std::vector<double>  *VertexXErr;
   std::vector<double>  *VertexY;
   std::vector<double>  *VertexYErr;
   std::vector<double>  *VertexZ;
   std::vector<double>  *VertexZErr;
   std::vector<float>   *PileUpInteractionsTrue;
   std::vector<std::vector<float> > *HLTFilterObjEta;
   std::vector<std::vector<float> > *HLTFilterObjPhi;
   std::vector<std::vector<float> > *HLTFilterObjPt;
   std::vector<int>     *ElectronCharge;
   std::vector<int>     *ElectronClassif;
   std::vector<int>     *ElectronMissingHits;
   std::vector<int>     *ElectronMissingHitsEG;
   std::vector<int>     *ElectronNumberOfBrems;
   std::vector<int>     *ElectronOverlaps;
   std::vector<int>     *ElectronPassEGammaIDEoP;
   std::vector<int>     *ElectronPassEGammaIDLoose;
   std::vector<int>     *ElectronPassEGammaIDMedium;
   std::vector<int>     *ElectronPassEGammaIDTight;
   std::vector<int>     *ElectronPassEGammaIDTrigTight;
   std::vector<int>     *ElectronPassEGammaIDTrigWP70;
   std::vector<int>     *ElectronPassEGammaIDVeto;
   std::vector<int>     *ElectronPassId;
   std::vector<int>     *ElectronPassIsoPAT;
   std::vector<int>     *ElectronVtxIndex;
   std::vector<int>     *GenWElectronMotherIndex;
   std::vector<int>     *GenWElectronNumDaught;
   std::vector<int>     *GenWElectronPdgId;
   std::vector<int>     *GenWElectronStatus;
   std::vector<int>     *GenWElectronTauDecayMode;
   std::vector<int>     *GenZElectronMotherIndex;
   std::vector<int>     *GenZElectronNumDaught;
   std::vector<int>     *GenZElectronPdgId;
   std::vector<int>     *GenZElectronStatus;
   std::vector<int>     *GenZElectronTauDecayMode;
   std::vector<int>     *PileUpInteractions;
   std::vector<int>     *PileUpOriginBX;
   std::vector<int>     *GenWMuMotherIndex;
   std::vector<int>     *GenWMuNumDaught;
   std::vector<int>     *GenWMuPdgId;
   std::vector<int>     *GenWMuStatus;
   std::vector<int>     *GenWMuTauDecayMode;
   std::vector<int>     *GenZMuMotherIndex;
   std::vector<int>     *GenZMuNumDaught;
   std::vector<int>     *GenZMuPdgId;
   std::vector<int>     *GenZMuStatus;
   std::vector<int>     *GenZMuTauDecayMode;
   std::vector<int>     *GenParticleMotherIndex;
   std::vector<int>     *GenParticleNumDaught;
   std::vector<int>     *GenParticlePdgId;
   std::vector<int>     *GenParticleStatus;
   std::vector<int>     *GenParticleTauDecayMode;
   std::vector<int>     *GenWTauMotherIndex;
   std::vector<int>     *GenWTauNumDaught;
   std::vector<int>     *GenWTauPdgId;
   std::vector<int>     *GenWTauStatus;
   std::vector<int>     *GenWTauTauDecayMode;
   std::vector<int>     *GenZTauMotherIndex;
   std::vector<int>     *GenZTauNumDaught;
   std::vector<int>     *GenZTauPdgId;
   std::vector<int>     *GenZTauStatus;
   std::vector<int>     *GenZTauTauDecayMode;
   std::vector<int>     *HPSTauCharge;
   std::vector<int>     *HPSTauDecayMode;
   std::vector<int>     *HPSTauIsCaloTau;
   std::vector<int>     *HPSTauIsPFTau;
   std::vector<int>     *HPSTauVtxIndex;
   std::vector<int>     *MuonBestTrackVtxIndex;
   std::vector<int>     *MuonCharge;
   std::vector<int>     *MuonCocktailCharge;
   std::vector<int>     *MuonCocktailRefitID;
   std::vector<int>     *MuonCocktailTrkHits;
   std::vector<int>     *MuonGlobalTrkValidHits;
   std::vector<int>     *MuonIsGlobal;
   std::vector<int>     *MuonIsPF;
   std::vector<int>     *MuonIsTracker;
   std::vector<int>     *MuonPassID;
   std::vector<int>     *MuonPixelHits;
   std::vector<int>     *MuonSegmentMatches;
   std::vector<int>     *MuonStationMatches;
   std::vector<int>     *MuonTrackLayersWithMeasurement;
   std::vector<int>     *MuonTrkHits;
   std::vector<int>     *MuonTrkHitsTrackerOnly;
   std::vector<int>     *MuonTrkPixelHits;
   std::vector<int>     *MuonVtxIndex;
   std::vector<int>     *PFCandChargeLeptLink;
   std::vector<int>     *PFJetBestVertexTrackAssociationIndex;
   std::vector<int>     *PFJetChargedHadronMultiplicity;
   std::vector<int>     *PFJetChargedMultiplicity;
   std::vector<int>     *PFJetClosestVertex3DIndex;
   std::vector<int>     *PFJetClosestVertexXYIndex;
   std::vector<int>     *PFJetClosestVertexZIndex;
   std::vector<int>     *PFJetElectronMultiplicity;
   std::vector<int>     *PFJetHFEMMultiplicity;
   std::vector<int>     *PFJetHFHadronMultiplicity;
   std::vector<int>     *PFJetMuonMultiplicity;
   std::vector<int>     *PFJetNConstituents;
   std::vector<int>     *PFJetNeutralHadronMultiplicity;
   std::vector<int>     *PFJetNeutralMultiplicity;
   std::vector<int>     *PFJetPartonFlavour;
   std::vector<int>     *PFJetPassLooseID;
   std::vector<int>     *PFJetPassTightID;
   std::vector<int>     *PFJetPhotonMultiplicity;
   std::vector<int>     *PhotonNTracksConvPhot;
   std::vector<int>     *HLTInsideDatasetTriggerPrescales;
   std::vector<int>     *HLTOutsideDatasetTriggerPrescales;
   std::vector<int>     *L1PhysBits;
   std::vector<int>     *L1TechBits;
   std::vector<int>     *VertexNTracks;
   std::vector<int>     *VertexNTracksW05;
   std::vector<std::vector<int> > *HLTFilterObjId;

   std::vector<double>  *CaloJetEnergy;
   std::vector<double>  *CaloJetEta;
   std::vector<double>  *CaloJetPt;
   std::vector<double>  *CaloJetPhi;
   std::vector<int>     *CaloJetPassLooseID;
   std::vector<int>     *CaloJetPassTightID;

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

   TBranch        *b_CaloJetEnergy;   //!       
   TBranch        *b_CaloJetEta;   //!    
   TBranch        *b_CaloJetPt;   //! 
   TBranch        *b_CaloJetPhi;   //! 
   TBranch        *b_CaloJetPassLooseID;   //!                                                                   
   TBranch        *b_CaloJetPassTightID;   //!   


   
};

#endif
