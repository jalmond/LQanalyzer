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

namespace snu{
  class KMuon;
  class KElectron;
  class KEvent;
  class KJet;
  class KGenJet;
  class KTrigger;
  class KTruth;
}



class Data : public LQCycleBaseNTuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain


   Long64_t GetNEntries();
   UInt_t GetEventNumber();
   TTree          *output_tree;

   Data();
   ~Data();

   void      GetEvent(Long64_t entry)throw( LQError );
   Int_t    GetEntry(Long64_t entry);
   Int_t    Cut(Long64_t entry);
   Long64_t LoadTree(Long64_t entry);
   void Init(TTree *tree);
   Bool_t   Notify(); //remove if possible
   void     Show(Long64_t entry = -1); //remove if possible
   TTree* GetInputTree();
   void setBranchStatus(void);
   void CheckCaching();

   /// Connect an input variable                                                
   template< typename T >
     bool ConnectVariable(  const char* branchName,
			    T& variable, TBranch* br);
   /// Specialisation for object pointers                                                                                                                                      
   template< typename T >
     bool ConnectVariable(const char* branchName,
			  T*& variable, TBranch* br);   

   void Reset();
   void ConnectVariables(Bool_t setall);

   void ConnectEvent();
   void ConnectMuons();
   void ConnectElectrons();
   void ConnectPFJets();
   void ConnectCaloJets();
   void ConnectPhotons();                                                                                                                                                           
   void ConnectTaus();
   void ConnectTruth();
   void ConnectTrigger();
   void ConnectAllBranches();
   void ConnectMET();
   void SetLQNtupleInputType(bool lq);
     

   bool LQinput;
   Long64_t nentries;

   // Declaration of leaf types
   std::string          *HLTKey;
   std::vector<std::string>  *HLTInsideDatasetTriggerNames;
   std::vector<std::string>  *HLTOutsideDatasetTriggerNames;
   std::vector<std::string>  *HLTFilterName;

   /// If needed (using SKTree input)
   std::vector<snu::KMuon>     *k_inputmuons;
   std::vector<snu::KElectron>     *k_inputelectrons;
   std::vector<snu::KJet>     *k_inputjets;
   std::vector<snu::KGenJet>     *k_inputgenjets;
   snu::KEvent     *k_inputevent;
   snu::KTrigger     *k_inputtrigger;
   std::vector<snu::KTruth>     *k_inputtruth;


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
   Bool_t          passHcalLaserEventFilter;
   Bool_t          passEcalMaskedCellDRFilter;
   Bool_t          passHBHENoiseFilter;
   Bool_t          passLogErrorTooManyClusters;
   Bool_t          passManyStripClus53X;
   Bool_t          passTooManyStripClus53X;
   Bool_t          passTrackingFailureFilter;
   Bool_t          hasVeryForwardPFMuon;
   Bool_t          hasJetWithBadUnc;
   std::vector<bool>    *ElectronLooseGsfCtfCharge;
   std::vector<bool>    *ElectronLooseGsfCtfScPixCharge;
   std::vector<bool>    *ElectronLooseGsfScPixCharge;
   std::vector<bool>    *ElectronLooseHLTDoubleEleMatched;
   std::vector<bool>    *ElectronLooseHLTSingleEleMatched;
   std::vector<bool>    *ElectronLooseHLTSingleEleMatched17;
   std::vector<bool>    *ElectronLooseHLTSingleEleMatched8;
   std::vector<bool>    *ElectronLooseHLTSingleEleWP80Matched;
   std::vector<bool>    *ElectronLooseHLTEMuMatched8;
   std::vector<bool>    *ElectronLooseHLTEMuMatched17;
   std::vector<bool>    *ElectronLooseHasEcalDrivenSeed;
   std::vector<bool>    *ElectronLooseHasMatchedConvPhot;
   std::vector<bool>    *ElectronLooseHasTrackerDrivenSeed;
   std::vector<bool>    *ElectronLooseIsEB;
   std::vector<bool>    *ElectronLooseIsEE;

   std::vector<bool>    *PFJetPileupjetIDpassLooseWP;
   std::vector<bool>    *PFJetPileupjetIDpassMediumWP;
   std::vector<bool>    *PFJetPileupjetIDpassTightWP;
   std::vector<int>     *PFJetJetPileupIdflag;
   std::vector<double>  *PFJetJetPileupMVA;
   
   std::vector<double>  *ElectronLoosemvatrigV0;
   std::vector<double>  *ElectronLoosemvaNontrigV0;

   std::vector<double>  *ElectronLooseshiftedEup;
   std::vector<double>  *ElectronLooseshiftedEdown;

   std::vector<double>  *ElectronLooseshiftedExup;
   std::vector<double>  *ElectronLooseshiftedExdown;

   std::vector<double>  *ElectronLooseshiftedEyup;
   std::vector<double>  *ElectronLooseshiftedEydown;

   std::vector<double>  *MuonLooseshiftedEup;
   std::vector<double>  *MuonLooseshiftedEdown;
   std::vector<double>  *MuonLooseshiftedExup;
   std::vector<double>  *MuonLooseshiftedExdown;
   std::vector<double>  *MuonLooseshiftedEyup;
   std::vector<double>  *MuonLooseshiftedEydown;

   
   std::vector<bool>    *MuonLooseHLTSingleIsoMuonMatched;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched5;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched8;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched12;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched17;
   std::vector<bool>    *MuonLooseHLTSingleMuonMatched24;
   std::vector<bool>    *MuonLooseHLTEMuMatched8;
   std::vector<bool>    *MuonLooseHLTEMuMatched17;

   std::vector<bool>    *MuonLooseHLTDoubleMuonMatched;
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
   std::vector<double>  *ElectronLooseBeamSpotDXY;
   std::vector<double>  *ElectronLooseBeamSpotDXYError;
   std::vector<double>  *ElectronLooseCaloEnergy;
   std::vector<double>  *ElectronLooseConvFitProb;
   std::vector<double>  *ElectronLooseDCotTheta;
   std::vector<double>  *ElectronLooseDeltaEtaTrkSC;
   std::vector<double>  *ElectronLooseDeltaPhiTrkSC;
   std::vector<double>  *ElectronLooseDist;
   std::vector<double>  *ElectronLooseE1x5OverE5x5;
   std::vector<double>  *ElectronLooseE2x5OverE5x5;
   std::vector<double>  *ElectronLooseESuperClusterOverP;
   std::vector<double>  *ElectronLooseEcalIsoDR03;
   std::vector<double>  *ElectronLooseEcalIsoPAT;
   std::vector<double>  *ElectronLooseEnergy;
   std::vector<double>  *ElectronLooseEta;
   std::vector<double>  *ElectronLooseFbrem;
   std::vector<double>  *ElectronLooseHLTDoubleEleMatchEta;
   std::vector<double>  *ElectronLooseHLTDoubleEleMatchPhi;
   std::vector<double>  *ElectronLooseHLTDoubleEleMatchPt;
   std::vector<double>  *ElectronLooseHLTSingleEleMatchEta;
   std::vector<double>  *ElectronLooseHLTSingleEleMatchPhi;
   std::vector<double>  *ElectronLooseHLTSingleEleMatchPt;
   std::vector<double>  *ElectronLooseHLTSingleEleWP80MatchEta;
   std::vector<double>  *ElectronLooseHLTSingleEleWP80MatchPhi;
   std::vector<double>  *ElectronLooseHLTSingleEleWP80MatchPt;
   std::vector<double>  *ElectronLooseHcalIsoD1DR03;
   std::vector<double>  *ElectronLooseHcalIsoD2DR03;
   std::vector<double>  *ElectronLooseHcalIsoDR03;
   std::vector<double>  *ElectronLooseHcalIsoDR03FullCone;
   std::vector<double>  *ElectronLooseHcalIsoPAT;
   std::vector<double>  *ElectronLooseHoE;
   std::vector<double>  *ElectronLooseLeadVtxDistXY;
   std::vector<double>  *ElectronLooseLeadVtxDistZ;
   std::vector<double>  *ElectronLooseMatchedGenParticleEta;
   std::vector<double>  *ElectronLooseMatchedGenParticlePhi;
   std::vector<double>  *ElectronLooseMatchedGenParticlePt;
   std::vector<double>  *ElectronLoosePFChargedHadronIso03;
   std::vector<double>  *ElectronLoosePFChargedHadronIso04;
   std::vector<double>  *ElectronLoosePFNeutralHadronIso03;
   std::vector<double>  *ElectronLoosePFNeutralHadronIso04;
   std::vector<double>  *ElectronLoosePFPhotonIso03;
   std::vector<double>  *ElectronLoosePFPhotonIso04;
   std::vector<double>  *ElectronLoosePhi;
   std::vector<double>  *ElectronLoosePrimaryVertexDXY;
   std::vector<double>  *ElectronLoosePrimaryVertexDXYError;
   std::vector<double>  *ElectronLoosePt;
   std::vector<double>  *ElectronLoosePx;
   std::vector<double>  *ElectronLoosePy;
   std::vector<double>  *ElectronLoosePtHeep;
   std::vector<double>  *ElectronLooseRelIsoPAT;
   std::vector<double>  *ElectronLooseSCEta;
   std::vector<double>  *ElectronLooseSCPhi;
   std::vector<double>  *ElectronLooseSCPt;
   std::vector<double>  *ElectronLooseSCRawEnergy;
   std::vector<double>  *ElectronLooseSigmaEtaEta;
   std::vector<double>  *ElectronLooseSigmaIEtaIEta;
   std::vector<double>  *ElectronLooseTrackPt;
   std::vector<double>  *ElectronLooseTrackValidFractionOfHits;
   std::vector<double>  *ElectronLooseTrackVx;
   std::vector<double>  *ElectronLooseTrackVy;
   std::vector<double>  *ElectronLooseTrackVz;
   std::vector<double>  *ElectronLooseTrkIsoDR03;
   std::vector<double>  *ElectronLooseTrkIsoPAT;
   std::vector<double>  *ElectronLooseVtxDistXY;
   std::vector<double>  *ElectronLooseVtxDistZ;
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
   std::vector<double>  *MuonLooseBackToBackCompatibility;
   std::vector<double>  *MuonLooseBeamSpotDXY;
   std::vector<double>  *MuonLooseBeamSpotDXYError;
   std::vector<double>  *MuonLooseBestTrackVtxDistXY;
   std::vector<double>  *MuonLooseBestTrackVtxDistZ;
   std::vector<double>  *MuonLooseCocktailEta;
   std::vector<double>  *MuonLooseCocktailEtaError;
   std::vector<double>  *MuonLooseCocktailGlobalChi2;
   std::vector<double>  *MuonLooseCocktailP;
   std::vector<double>  *MuonLooseCocktailPhi;
   std::vector<double>  *MuonLooseCocktailPhiError;
   std::vector<double>  *MuonLooseCocktailPt;
   std::vector<double>  *MuonLooseCocktailPtError;
   std::vector<double>  *MuonLooseCocktailQOverPError;
   std::vector<double>  *MuonLooseCocktailTrkD0;
   std::vector<double>  *MuonLooseCocktailTrkD0Error;
   std::vector<double>  *MuonLooseCocktailTrkDz;
   std::vector<double>  *MuonLooseCocktailTrkDzError;
   std::vector<double>  *MuonLooseCocktailTrkVtxDXY;
   std::vector<double>  *MuonLooseCocktailTrkVtxDZ;
   std::vector<double>  *MuonLooseCocktailTrkValidFractionOfHits;
   std::vector<double>  *MuonLooseCosmicCompatibility;
   std::vector<double>  *MuonLooseEcalIso;
   std::vector<double>  *MuonLooseEcalVetoIso;
   std::vector<double>  *MuonLooseEnergy;
   std::vector<double>  *MuonLooseEta;
   std::vector<double>  *MuonLooseEtaError;
   std::vector<double>  *MuonLooseGlobalChi2;
   std::vector<double>  *MuonLooseHLTSingleIsoMuonMatchEta;
   std::vector<double>  *MuonLooseHLTSingleIsoMuonMatchPhi;
   std::vector<double>  *MuonLooseHLTSingleIsoMuonMatchPt;
   std::vector<double>  *MuonLooseHLTSingleMuonMatchEta;
   std::vector<double>  *MuonLooseHLTSingleMuonMatchPhi;
   std::vector<double>  *MuonLooseHLTSingleMuonMatchPt;
   std::vector<double>  *MuonLooseHOIso;
   std::vector<double>  *MuonLooseHcalIso;
   std::vector<double>  *MuonLooseHcalVetoIso;
   std::vector<double>  *MuonLooseMatchedGenParticleEta;
   std::vector<double>  *MuonLooseMatchedGenParticlePhi;
   std::vector<double>  *MuonLooseMatchedGenParticlePt;
   std::vector<double>  *MuonLooseOverlapCompatibility;
   std::vector<double>  *MuonLooseP;
   std::vector<double>  *MuonLoosePFIsoR03ChargedHadron;
   std::vector<double>  *MuonLoosePFIsoR03ChargedParticle;
   std::vector<double>  *MuonLoosePFIsoR03NeutralHadron;
   std::vector<double>  *MuonLoosePFIsoR03NeutralHadronHT;
   std::vector<double>  *MuonLoosePFIsoR03PU;
   std::vector<double>  *MuonLoosePFIsoR03Photon;
   std::vector<double>  *MuonLoosePFIsoR03PhotonHT;
   std::vector<double>  *MuonLoosePFIsoR04ChargedHadron;
   std::vector<double>  *MuonLoosePFIsoR04ChargedParticle;
   std::vector<double>  *MuonLoosePFIsoR04NeutralHadron;
   std::vector<double>  *MuonLoosePFIsoR04NeutralHadronHT;
   std::vector<double>  *MuonLoosePFIsoR04PU;
   std::vector<double>  *MuonLoosePFIsoR04Photon;
   std::vector<double>  *MuonLoosePFIsoR04PhotonHT;
   std::vector<double>  *MuonLoosePhi;
   std::vector<double>  *MuonLoosePhiError;
   std::vector<double>  *MuonLoosePrimaryVertexDXY;
   std::vector<double>  *MuonLoosePrimaryVertexDXYError;
   std::vector<double>  *MuonLoosePt;
   std::vector<double>  *MuonLoosePx;
   std::vector<double>  *MuonLoosePy;
   std::vector<double>  *MuonLoosePtError;
   std::vector<double>  *MuonLooseQOverPError;
   std::vector<double>  *MuonLooseTimeCompatibility;
   std::vector<double>  *MuonLooseTrackChi2;
   std::vector<double>  *MuonLooseTrackerIsoSumPT;
   std::vector<double>  *MuonLooseTrkD0;
   std::vector<double>  *MuonLooseTrkD0Error;
   std::vector<double>  *MuonLooseTrkDz;
   std::vector<double>  *MuonLooseTrkDzError;
   std::vector<double>  *MuonLooseTrkEta;
   std::vector<double>  *MuonLooseTrkEtaError;
   std::vector<double>  *MuonLooseTrkIso;
   std::vector<double>  *MuonLooseTrkPhi;
   std::vector<double>  *MuonLooseTrkPhiError;
   std::vector<double>  *MuonLooseTrkPt;
   std::vector<double>  *MuonLooseTrkPtError;
   std::vector<double>  *MuonLooseTrkValidFractionOfHits;
   std::vector<double>  *MuonLooseTrkVx;
   std::vector<double>  *MuonLooseTrkVy;
   std::vector<double>  *MuonLooseTrkVz;
   std::vector<double>  *MuonLooseVtxDistXY;
   std::vector<double>  *MuonLooseVtxDistZ;
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
   std::vector<double>  *PFJetL5BottomJEC;
   std::vector<double>  *PFJetL5CharmJEC;
   std::vector<double>  *PFJetL5UDSJEC;
   std::vector<double>  *PFJetL5GluonJEC;
   std::vector<double>  *PFJetMuonEnergyFraction;
   std::vector<double>  *PFJetNeutralEmEnergyFraction;
   std::vector<double>  *PFJetNeutralHadronEnergyFraction;
   std::vector<double>  *PFJetPhi;
   std::vector<double>  *PFJetPhotonEnergyFraction;
   std::vector<double>  *PFJetPt;
   std::vector<double>  *PFJetPx;
   std::vector<double>  *PFJetPy;
   std::vector<double>  *PFJetPtRaw;
   std::vector<double>  *PFJetPxRaw;
   std::vector<double>  *PFJetPyRaw;
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
   std::vector<double>  *PFMETx;
   std::vector<double>  *PFMETy;
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
   std::vector<double>  *PFMETxType01XYCor;
   std::vector<double>  *PFMETyType01XYCor;
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
   std::vector<int>     *ElectronLooseCharge;
   std::vector<int>     *ElectronLooseClassif;
   std::vector<int>     *ElectronLooseMissingHits;
   std::vector<int>     *ElectronLooseMissingHitsEG;
   std::vector<int>     *ElectronLooseNumberOfBrems;
   std::vector<int>     *ElectronLooseOverlaps;
   std::vector<int>     *ElectronLoosePassEGammaIDEoP;
   std::vector<int>     *ElectronLoosePassEGammaIDLoose;
   std::vector<int>     *ElectronLoosePassEGammaIDMedium;
   std::vector<int>     *ElectronLoosePassEGammaIDTight;
   std::vector<int>     *ElectronLoosePassEGammaIDTrigTight;
   std::vector<int>     *ElectronLoosePassEGammaIDTrigWP70;
   std::vector<int>     *ElectronLoosePassEGammaIDVeto;
   std::vector<int>     *ElectronLoosePassId;
   std::vector<int>     *ElectronLoosePassIsoPAT;
   std::vector<int>     *ElectronLooseVtxIndex;
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
   std::vector<int>     *MuonLooseBestTrackVtxIndex;
   std::vector<int>     *MuonLooseCharge;
   std::vector<int>     *MuonLooseCocktailCharge;
   std::vector<int>     *MuonLooseCocktailRefitID;
   std::vector<int>     *MuonLooseCocktailTrkHits;
   std::vector<int>     *MuonLooseGlobalTrkValidHits;
   std::vector<int>     *MuonLooseIsGlobal;
   std::vector<int>     *MuonLooseIsPF;
   std::vector<int>     *MuonLooseIsTracker;
   std::vector<int>     *MuonLoosePassID;
   std::vector<int>     *MuonLoosePixelHits;
   std::vector<int>     *MuonLooseSegmentMatches;
   std::vector<int>     *MuonLooseStationMatches;
   std::vector<int>     *MuonLooseTrackLayersWithMeasurement;
   std::vector<int>     *MuonLooseTrkHits;
   std::vector<int>     *MuonLooseTrkHitsTrackerOnly;
   std::vector<int>     *MuonLooseTrkPixelHits;
   std::vector<int>     *MuonLooseVtxIndex;
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

   /// New Variabels 2013/12/02
   std::vector<double>  *CaloJetEnergy;
   std::vector<double>  *CaloJetEta;
   std::vector<double>  *CaloJetPt;
   std::vector<double>  *CaloJetPhi;
   std::vector<int>     *CaloJetPassLooseID;
   std::vector<int>     *CaloJetPassTightID;
   std::vector<double>  *MuonLooseGlobalE;
   std::vector<double>  *MuonLooseGlobalEta;
   std::vector<double>  *MuonLooseGlobalPhi;
   std::vector<double>  *MuonLooseGlobalPt;
   std::vector<double>  *MuonLooseMuonSpecE;
   std::vector<double>  *MuonLooseMuonSpecEta;
   std::vector<double>  *MuonLooseMuonSpecPhi;
   std::vector<double>  *MuonLooseMuonSpecPt;
   std::vector<double>  *PFJetScaledDownEnergy;
   std::vector<double>  *PFJetScaledDownPt;
   std::vector<double>  *PFJetScaledDownPx;
   std::vector<double>  *PFJetScaledDownPy;
   std::vector<double>  *PFJetScaledUpEnergy;
   std::vector<double>  *PFJetScaledUpPt;
   std::vector<double>  *PFJetScaledUpPx;
   std::vector<double>  *PFJetScaledUpPy;
   std::vector<double>  *PFJetSmearedDownEnergy;
   std::vector<double>  *PFJetSmearedDownPt;
   std::vector<double>  *PFJetSmearedDownPx;
   std::vector<double>  *PFJetSmearedDownPy;
   std::vector<double>  *PFJetSmearedUpEnergy;
   std::vector<double>  *PFJetSmearedUpPt;
   std::vector<double>  *PFJetSmearedUpPx;
   std::vector<double>  *PFJetSmearedUpPy;
   std::vector<double>  *PFMETType01XYCorUnclusteredUp;
   std::vector<double>  *PFMETType01XYCorUnclusteredDown;
   std::vector<double>  *PFMETxType01XYCorUnclusteredUp;
   std::vector<double>  *PFMETxType01XYCorUnclusteredDown;
   std::vector<double>  *PFMETyType01XYCorUnclusteredUp;
   std::vector<double>  *PFMETyType01XYCorUnclusteredDown;
   std::vector<int>     *MuonLooseGlobalCharge;
   std::vector<int>     *MuonLooseMuonSpecCharge;
   std::vector<int>     *MuonLooseTrackerCharge;

   
   
   UInt_t          bunch;
   UInt_t          event;
   UInt_t          ls;
   UInt_t          orbit;
   UInt_t          run;
   UInt_t          ProcessID;

   std::vector<TBranch*> m_inputbranches;
   // List of branches

   TBranch        *b_inputmuons;
   TBranch        *b_inputtrigger;
   TBranch        *b_inputtruth;
   TBranch        *b_inputjets;
   TBranch        *b_inputgenjets;
   TBranch        *b_inputevent;
   TBranch        *b_inputelectrons;
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
   TBranch        *b_passHcalLaserEventFilter;  //!
   TBranch        *b_passEcalMaskedCellDRFilter;   //!
   TBranch        *b_passHBHENoiseFilter;   //!
   TBranch        *b_passLogErrorTooManyClusters;   //!
   TBranch        *b_passManyStripClus53X;   //!
   TBranch        *b_passTooManyStripClus53X;   //!
   TBranch        *b_passTrackingFailureFilter;   //!
   TBranch        *b_hasVeryForwardPFMuon;   //!
   TBranch        *b_hasJetWithBadUnc;   //!
   TBranch        *b_ElectronLooseshiftedEup; //!
   TBranch        *b_ElectronLooseshiftedEdown; //!
   TBranch        *b_ElectronLooseshiftedExup; //!                                                                                                                                    
   TBranch        *b_ElectronLooseshiftedExdown; //!      

   TBranch        *b_ElectronLooseshiftedEyup; //!                                                                                                                                    
   TBranch        *b_ElectronLooseshiftedEydown; //!   

   TBranch        *b_ElectronLooseGsfCtfCharge;   //!
   TBranch        *b_ElectronLooseGsfCtfScPixCharge;   //!
   TBranch        *b_ElectronLooseGsfScPixCharge;   //!
   TBranch        *b_ElectronLooseHLTDoubleEleMatched;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatched;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatched8;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatched17;   //!
   TBranch        *b_ElectronLooseHLTSingleEleWP80Matched;   //!
   TBranch        *b_ElectronLooseHLTEMuMatched8;   //!
   TBranch        *b_ElectronLooseHLTEMuMatched17;   //!
   TBranch        *b_ElectronLooseHasEcalDrivenSeed;   //!
   TBranch        *b_ElectronLooseHasMatchedConvPhot;   //!
   TBranch        *b_ElectronLooseHasTrackerDrivenSeed;   //!
   TBranch        *b_ElectronLooseIsEB;   //!
   TBranch        *b_ElectronLooseIsEE;   //!
   TBranch        *b_ElectronLoosemvatrigV0;   //!
   TBranch        *b_ElectronLoosemvaNontrigV0;   //!
   TBranch        *b_PFJetPileupjetIDpassLooseWP; //!
   TBranch        *b_PFJetPileupjetIDpassMediumWP; //!
   TBranch        *b_PFJetPileupjetIDpassTightWP; //!
   TBranch        *b_PFJetJetPileupIdflag; //!
   TBranch        *b_PFJetJetPileupMVA; //!
   TBranch        *b_MuonLooseshiftedEup; //!
   TBranch        *b_MuonLooseshiftedEdown; //!
   TBranch        *b_MuonLooseshiftedExup; //!                                                                                                                                       
   TBranch        *b_MuonLooseshiftedExdown; //!  
   TBranch        *b_MuonLooseshiftedEyup; //!                                                                                                                                        
   TBranch        *b_MuonLooseshiftedEydown; //!  
   TBranch        *b_MuonLooseHLTSingleIsoMuonMatched;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched5;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched8;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched12;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched17;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatched24;   //!
   TBranch        *b_MuonLooseHLTDoubleMuonMatched;   //!
   TBranch        *b_MuonLooseHLTEMuMatched8;   //!
   TBranch        *b_MuonLooseHLTEMuMatched17;   //!
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
   TBranch        *b_ElectronLooseBeamSpotDXY;   //!
   TBranch        *b_ElectronLooseBeamSpotDXYError;   //!
   TBranch        *b_ElectronLooseCaloEnergy;   //!
   TBranch        *b_ElectronLooseConvFitProb;   //!
   TBranch        *b_ElectronLooseDCotTheta;   //!
   TBranch        *b_ElectronLooseDeltaEtaTrkSC;   //!
   TBranch        *b_ElectronLooseDeltaPhiTrkSC;   //!
   TBranch        *b_ElectronLooseDist;   //!
   TBranch        *b_ElectronLooseE1x5OverE5x5;   //!
   TBranch        *b_ElectronLooseE2x5OverE5x5;   //!
   TBranch        *b_ElectronLooseESuperClusterOverP;   //!
   TBranch        *b_ElectronLooseEcalIsoDR03;   //!
   TBranch        *b_ElectronLooseEcalIsoPAT;   //!
   TBranch        *b_ElectronLooseEnergy;   //!
   TBranch        *b_ElectronLooseEta;   //!
   TBranch        *b_ElectronLooseFbrem;   //!
   TBranch        *b_ElectronLooseHLTDoubleEleMatchEta;   //!
   TBranch        *b_ElectronLooseHLTDoubleEleMatchPhi;   //!
   TBranch        *b_ElectronLooseHLTDoubleEleMatchPt;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatchEta;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatchPhi;   //!
   TBranch        *b_ElectronLooseHLTSingleEleMatchPt;   //!
   TBranch        *b_ElectronLooseHLTSingleEleWP80MatchEta;   //!
   TBranch        *b_ElectronLooseHLTSingleEleWP80MatchPhi;   //!
   TBranch        *b_ElectronLooseHLTSingleEleWP80MatchPt;   //!
   TBranch        *b_ElectronLooseHcalIsoD1DR03;   //!
   TBranch        *b_ElectronLooseHcalIsoD2DR03;   //!
   TBranch        *b_ElectronLooseHcalIsoDR03;   //!
   TBranch        *b_ElectronLooseHcalIsoDR03FullCone;   //!
   TBranch        *b_ElectronLooseHcalIsoPAT;   //!
   TBranch        *b_ElectronLooseHoE;   //!
   TBranch        *b_ElectronLooseLeadVtxDistXY;   //!
   TBranch        *b_ElectronLooseLeadVtxDistZ;   //!
   TBranch        *b_ElectronLooseMatchedGenParticleEta;   //!
   TBranch        *b_ElectronLooseMatchedGenParticlePhi;   //!
   TBranch        *b_ElectronLooseMatchedGenParticlePt;   //!
   TBranch        *b_ElectronLoosePFChargedHadronIso03;   //!
   TBranch        *b_ElectronLoosePFChargedHadronIso04;   //!
   TBranch        *b_ElectronLoosePFNeutralHadronIso03;   //!
   TBranch        *b_ElectronLoosePFNeutralHadronIso04;   //!
   TBranch        *b_ElectronLoosePFPhotonIso03;   //!
   TBranch        *b_ElectronLoosePFPhotonIso04;   //!
   TBranch        *b_ElectronLoosePhi;   //!
   TBranch        *b_ElectronLoosePrimaryVertexDXY;   //!
   TBranch        *b_ElectronLoosePrimaryVertexDXYError;   //!
   TBranch        *b_ElectronLoosePt;   //!
   TBranch        *b_ElectronLoosePx;   //!
   TBranch        *b_ElectronLoosePy;   //!
   TBranch        *b_ElectronLoosePtHeep;   //!
   TBranch        *b_ElectronLooseRelIsoPAT;   //!
   TBranch        *b_ElectronLooseSCEta;   //!
   TBranch        *b_ElectronLooseSCPhi;   //!
   TBranch        *b_ElectronLooseSCPt;   //!
   TBranch        *b_ElectronLooseSCRawEnergy;   //!
   TBranch        *b_ElectronLooseSigmaEtaEta;   //!
   TBranch        *b_ElectronLooseSigmaIEtaIEta;   //!
   TBranch        *b_ElectronLooseTrackPt;   //!
   TBranch        *b_ElectronLooseTrackValidFractionOfHits;   //!
   TBranch        *b_ElectronLooseTrackVx;   //!
   TBranch        *b_ElectronLooseTrackVy;   //!
   TBranch        *b_ElectronLooseTrackVz;   //!
   TBranch        *b_ElectronLooseTrkIsoDR03;   //!
   TBranch        *b_ElectronLooseTrkIsoPAT;   //!
   TBranch        *b_ElectronLooseVtxDistXY;   //!
   TBranch        *b_ElectronLooseVtxDistZ;   //!
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
   TBranch        *b_MuonLooseBackToBackCompatibility;   //!
   TBranch        *b_MuonLooseBeamSpotDXY;   //!
   TBranch        *b_MuonLooseBeamSpotDXYError;   //!
   TBranch        *b_MuonLooseBestTrackVtxDistXY;   //!
   TBranch        *b_MuonLooseBestTrackVtxDistZ;   //!
   TBranch        *b_MuonLooseCocktailEta;   //!
   TBranch        *b_MuonLooseCocktailEtaError;   //!
   TBranch        *b_MuonLooseCocktailGlobalChi2;   //!
   TBranch        *b_MuonLooseCocktailP;   //!
   TBranch        *b_MuonLooseCocktailPhi;   //!
   TBranch        *b_MuonLooseCocktailPhiError;   //!
   TBranch        *b_MuonLooseCocktailPt;   //!
   TBranch        *b_MuonLooseCocktailPtError;   //!
   TBranch        *b_MuonLooseCocktailQOverPError;   //!
   TBranch        *b_MuonLooseCocktailTrkD0;   //!
   TBranch        *b_MuonLooseCocktailTrkD0Error;   //!
   TBranch        *b_MuonLooseCocktailTrkDz;   //!
   TBranch        *b_MuonLooseCocktailTrkVtxDXY;   //!
   TBranch        *b_MuonLooseCocktailTrkVtxDZ;   //!
   TBranch        *b_MuonLooseCocktailTrkDzError;   //!
   TBranch        *b_MuonLooseCocktailTrkValidFractionOfHits;   //!
   TBranch        *b_MuonLooseCosmicCompatibility;   //!
   TBranch        *b_MuonLooseEcalIso;   //!
   TBranch        *b_MuonLooseEcalVetoIso;   //!
   TBranch        *b_MuonLooseEnergy;   //!
   TBranch        *b_MuonLooseEta;   //!
   TBranch        *b_MuonLooseEtaError;   //!
   TBranch        *b_MuonLooseGlobalChi2;   //!
   TBranch        *b_MuonLooseHLTSingleIsoMuonMatchEta;   //!
   TBranch        *b_MuonLooseHLTSingleIsoMuonMatchPhi;   //!
   TBranch        *b_MuonLooseHLTSingleIsoMuonMatchPt;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatchEta;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatchPhi;   //!
   TBranch        *b_MuonLooseHLTSingleMuonMatchPt;   //!
   TBranch        *b_MuonLooseHOIso;   //!
   TBranch        *b_MuonLooseHcalIso;   //!
   TBranch        *b_MuonLooseHcalVetoIso;   //!
   TBranch        *b_MuonLooseMatchedGenParticleEta;   //!
   TBranch        *b_MuonLooseMatchedGenParticlePhi;   //!
   TBranch        *b_MuonLooseMatchedGenParticlePt;   //!
   TBranch        *b_MuonLooseOverlapCompatibility;   //!
   TBranch        *b_MuonLooseP;   //!
   TBranch        *b_MuonLoosePFIsoR03ChargedHadron;   //!
   TBranch        *b_MuonLoosePFIsoR03ChargedParticle;   //!
   TBranch        *b_MuonLoosePFIsoR03NeutralHadron;   //!
   TBranch        *b_MuonLoosePFIsoR03NeutralHadronHT;   //!
   TBranch        *b_MuonLoosePFIsoR03PU;   //!
   TBranch        *b_MuonLoosePFIsoR03Photon;   //!
   TBranch        *b_MuonLoosePFIsoR03PhotonHT;   //!
   TBranch        *b_MuonLoosePFIsoR04ChargedHadron;   //!
   TBranch        *b_MuonLoosePFIsoR04ChargedParticle;   //!
   TBranch        *b_MuonLoosePFIsoR04NeutralHadron;   //!
   TBranch        *b_MuonLoosePFIsoR04NeutralHadronHT;   //!
   TBranch        *b_MuonLoosePFIsoR04PU;   //!
   TBranch        *b_MuonLoosePFIsoR04Photon;   //!
   TBranch        *b_MuonLoosePFIsoR04PhotonHT;   //!
   TBranch        *b_MuonLoosePhi;   //!
   TBranch        *b_MuonLoosePhiError;   //!
   TBranch        *b_MuonLoosePrimaryVertexDXY;   //!
   TBranch        *b_MuonLoosePrimaryVertexDXYError;   //!
   TBranch        *b_MuonLoosePt;   //!
   TBranch        *b_MuonLoosePx;   //!
   TBranch        *b_MuonLoosePy;   //!
   TBranch        *b_MuonLoosePtError;   //!
   TBranch        *b_MuonLooseQOverPError;   //!
   TBranch        *b_MuonLooseTimeCompatibility;   //!
   TBranch        *b_MuonLooseTrackChi2;   //!
   TBranch        *b_MuonLooseTrackerIsoSumPT;   //!
   TBranch        *b_MuonLooseTrkD0;   //!
   TBranch        *b_MuonLooseTrkD0Error;   //!
   TBranch        *b_MuonLooseTrkDz;   //!
   TBranch        *b_MuonLooseTrkDzError;   //!
   TBranch        *b_MuonLooseTrkEta;   //!
   TBranch        *b_MuonLooseTrkEtaError;   //!
   TBranch        *b_MuonLooseTrkIso;   //!
   TBranch        *b_MuonLooseTrkPhi;   //!
   TBranch        *b_MuonLooseTrkPhiError;   //!
   TBranch        *b_MuonLooseTrkPt;   //!
   TBranch        *b_MuonLooseTrkPtError;   //!
   TBranch        *b_MuonLooseTrkValidFractionOfHits;   //!
   TBranch        *b_MuonLooseTrkVx;   //!
   TBranch        *b_MuonLooseTrkVy;   //!
   TBranch        *b_MuonLooseTrkVz;   //!
   TBranch        *b_MuonLooseVtxDistXY;   //!
   TBranch        *b_MuonLooseVtxDistZ;   //!
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
   TBranch        *b_PFJetL5BottomJEC;   //!
   TBranch        *b_PFJetL5CharmJEC;   //!
   TBranch        *b_PFJetL5UDSJEC;   //!
   TBranch        *b_PFJetL5GluonJEC;   //!
   TBranch        *b_PFJetMuonEnergyFraction;   //!
   TBranch        *b_PFJetNeutralEmEnergyFraction;   //!
   TBranch        *b_PFJetNeutralHadronEnergyFraction;   //!
   TBranch        *b_PFJetPhi;   //!
   TBranch        *b_PFJetPhotonEnergyFraction;   //!
   TBranch        *b_PFJetPt;   //!
   TBranch        *b_PFJetPx;   //!
   TBranch        *b_PFJetPy;   //!
   TBranch        *b_PFJetPtRaw;   //!

   TBranch        *b_PFJetPxRaw;   //!

   TBranch        *b_PFJetPyRaw;   //!
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
   TBranch        *b_PFMETx;   //!
   TBranch        *b_PFMETy;   //!
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
   TBranch        *b_PFMETxType01XYCor;   //!
   TBranch        *b_PFMETyType01XYCor;   //!
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
   TBranch        *b_ElectronLooseCharge;   //!
   TBranch        *b_ElectronLooseClassif;   //!
   TBranch        *b_ElectronLooseMissingHits;   //!
   TBranch        *b_ElectronLooseMissingHitsEG;   //!
   TBranch        *b_ElectronLooseNumberOfBrems;   //!
   TBranch        *b_ElectronLooseOverlaps;   //!
   TBranch        *b_ElectronLoosePassEGammaIDEoP;   //!
   TBranch        *b_ElectronLoosePassEGammaIDLoose;   //!
   TBranch        *b_ElectronLoosePassEGammaIDMedium;   //!
   TBranch        *b_ElectronLoosePassEGammaIDTight;   //!
   TBranch        *b_ElectronLoosePassEGammaIDTrigTight;   //!
   TBranch        *b_ElectronLoosePassEGammaIDTrigWP70;   //!
   TBranch        *b_ElectronLoosePassEGammaIDVeto;   //!
   TBranch        *b_ElectronLoosePassId;   //!
   TBranch        *b_ElectronLoosePassIsoPAT;   //!
   TBranch        *b_ElectronLooseVtxIndex;   //!
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
   TBranch        *b_MuonLooseBestTrackVtxIndex;   //!
   TBranch        *b_MuonLooseCharge;   //!
   TBranch        *b_MuonLooseCocktailCharge;   //!
   TBranch        *b_MuonLooseCocktailRefitID;   //!
   TBranch        *b_MuonLooseCocktailTrkHits;   //!
   TBranch        *b_MuonLooseGlobalTrkValidHits;   //!
   TBranch        *b_MuonLooseIsGlobal;   //!
   TBranch        *b_MuonLooseIsPF;   //!
   TBranch        *b_MuonLooseIsTracker;   //!
   TBranch        *b_MuonLoosePassID;   //!
   TBranch        *b_MuonLoosePixelHits;   //!
   TBranch        *b_MuonLooseSegmentMatches;   //!
   TBranch        *b_MuonLooseStationMatches;   //!
   TBranch        *b_MuonLooseTrackLayersWithMeasurement;   //!
   TBranch        *b_MuonLooseTrkHits;   //!
   TBranch        *b_MuonLooseTrkHitsTrackerOnly;   //!
   TBranch        *b_MuonLooseTrkPixelHits;   //!
   TBranch        *b_MuonLooseVtxIndex;   //!
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

   /// NEW branched 2013/12/02
   TBranch        *b_CaloJetEnergy;   //!       
   TBranch        *b_CaloJetEta;   //!    
   TBranch        *b_CaloJetPt;   //! 
   TBranch        *b_CaloJetPhi;   //! 
   TBranch        *b_CaloJetPassLooseID;   //!                                                                   
   TBranch        *b_CaloJetPassTightID;   //!   
   
   TBranch        *b_MuonLooseGlobalE;   //!
   TBranch        *b_MuonLooseGlobalEta;   //!
   TBranch        *b_MuonLooseGlobalPhi;   //!
   TBranch        *b_MuonLooseGlobalPt;   //!
   TBranch        *b_MuonLooseMuonSpecE;   //!
   TBranch        *b_MuonLooseMuonSpecEta;   //!
   TBranch        *b_MuonLooseMuonSpecPhi;   //!
   TBranch        *b_MuonLooseMuonSpecPt;   //!
   
   TBranch        *b_PFJetScaledDownEnergy;   //!
   TBranch        *b_PFJetScaledDownPt;   //!
   TBranch        *b_PFJetScaledDownPx;   //!
   TBranch        *b_PFJetScaledDownPy;   //!
   TBranch        *b_PFJetScaledUpEnergy;   //!
   TBranch        *b_PFJetScaledUpPt;   //!
   TBranch        *b_PFJetScaledUpPx;   //!
   TBranch        *b_PFJetScaledUpPy;   //!

   TBranch        *b_PFJetSmearedDownEnergy;   //!
   TBranch        *b_PFJetSmearedDownPt;   //!
   TBranch        *b_PFJetSmearedDownPx;   //!
   TBranch        *b_PFJetSmearedDownPy;   //!
   TBranch        *b_PFJetSmearedUpEnergy;   //!
   TBranch        *b_PFJetSmearedUpPt;   //!
   TBranch        *b_PFJetSmearedUpPx;   //!
   TBranch        *b_PFJetSmearedUpPy;   //!

   TBranch        *b_PFMETType01XYCorUnclusteredDown;   //!
   TBranch        *b_PFMETType01XYCorUnclusteredUp;   //!
   TBranch        *b_PFMETxType01XYCorUnclusteredDown;   //!                                                                                                                     
   TBranch        *b_PFMETxType01XYCorUnclusteredUp;   //!    
   TBranch        *b_PFMETyType01XYCorUnclusteredDown;   //!                                                                                                                     
   TBranch        *b_PFMETyType01XYCorUnclusteredUp;   //!    

   TBranch        *b_MuonLooseGlobalCharge;   //!
   TBranch        *b_MuonLooseMuonSpecCharge;   //!
   TBranch        *b_MuonLooseTrackerCharge;   //!
};

#endif
