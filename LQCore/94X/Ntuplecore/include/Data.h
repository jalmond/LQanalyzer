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

typedef std::vector<double> VDouble;

namespace snu{
  class KMuon;
  class KElectron;
  class KPhoton;
  class KEvent;
  class KJet;
  class KFatJet;
  class KGenJet;
  class KTrigger;
  class KTruth;
}



class Data : public LQCycleBaseNTuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   //static Int_t kMaxtriggers = 48;


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
   void ConnectVariables(Bool_t setall, int data_setting);

   void ConnectEvent(int data_setting);
   void ConnectMuons();
   void ConnectElectrons();
   void ConnectPhotons();
   void ConnectPFJets();
   void ConnectPFFatJets();

   void ConnectTruth(int data_setting);
   void ConnectTrigger();
   void ConnectAllBranches();
   void ConnectMET();
   void SetLQNtupleInputType(bool lq);
   void SetVersion(int ver);

   std::string GetCatVersion(bool runLQ);
   void SetCatVersion(std::string cv);
   void SetTargetLumi(float tlumi);

   void SetLQNtupleInputType(int dataflag);
   void SetFlags(std::vector<TString> v_flags);

   bool LQinput;
   Long64_t nentries;
   int k_cat_version;
   // Declaration of leaf types

   /// If needed (using SKTree input)
   std::vector<snu::KMuon>     *k_inputmuons;
   std::vector<snu::KElectron>     *k_inputelectrons;
   std::vector<snu::KPhoton>     *k_inputphotons;
   std::vector<snu::KJet>     *k_inputjets;
   std::vector<snu::KFatJet>     *k_inputfatjets;
   std::vector<snu::KGenJet>     *k_inputgenjets;
   snu::KEvent     *k_inputevent;
   snu::KTrigger     *k_inputtrigger;
   std::vector<snu::KTruth>     *k_inputtruth;

   int setting_ntuple_data;
   
   std::vector<TBranch*> m_inputbranches;

   std::string CatVersion;
   float TargetLumi;
   std::vector<TString>  k_flags;

   // Declaration of leaf types

   Bool_t          IsData;
   Int_t           nTotal;
   Int_t           run;
   ULong64_t       event;
   Int_t           lumi;
   Double_t        PUweight;
   Double_t        Rho;
   Int_t           nPV;
   Bool_t          Flag_goodVertices;
   Bool_t          Flag_globalSuperTightHalo2016Filter;
   Bool_t          Flag_HBHENoiseFilter;
   Bool_t          Flag_HBHENoiseIsoFilter;
   Bool_t          Flag_EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_BadPFMuonFilter;
   Bool_t          Flag_BadChargedCandidateFilter;
   Bool_t          Flag_eeBadScFilter;
   Bool_t          Flag_ecalBadCalibFilter;
   Int_t           PVtrackSize;
   Double_t        PVchi2;
   Double_t        PVndof;
   Double_t        PVnormalizedChi2;
   Double_t        vertex_X;
   Double_t        vertex_Y;
   Double_t        vertex_Z;
   std::vector<std::string>  *HLT_TriggerName;
   std::vector<double>  *jet_pt;
   std::vector<double>  *jet_eta;
   std::vector<double>  *jet_phi;
   std::vector<double>  *jet_charge;
   std::vector<double>  *jet_area;
   std::vector<int>     *jet_partonFlavour;
   std::vector<int>     *jet_hadronFlavour;
   std::vector<double>  *jet_CSVv2;
   std::vector<double>  *jet_DeepCSV;
   std::vector<double>  *jet_CvsL;
   std::vector<double>  *jet_CvsB;
   std::vector<double>  *jet_DeepFlavour_b;
   std::vector<double>  *jet_DeepFlavour_bb;
   std::vector<double>  *jet_DeepFlavour_lepb;
   std::vector<double>  *jet_DeepFlavour_c;
   std::vector<double>  *jet_DeepFlavour_uds;
   std::vector<double>  *jet_DeepFlavour_g;
   std::vector<double>  *jet_DeepCvsL;
   std::vector<double>  *jet_DeepCvsB;
   std::vector<double>  *jet_chargedHadronEnergyFraction;
   std::vector<double>  *jet_neutralHadronEnergyFraction;
   std::vector<double>  *jet_neutralEmEnergyFraction;
   std::vector<double>  *jet_chargedEmEnergyFraction;
   std::vector<int>     *jet_chargedMultiplicity;
   std::vector<int>     *jet_neutralMultiplicity;
   std::vector<bool>    *jet_tightJetID;
   std::vector<bool>    *jet_tightLepVetoJetID;
   std::vector<int>     *jet_partonPdgId;
   std::vector<double>  *jet_m;
   std::vector<double>  *jet_energy;
   std::vector<double>  *jet_PileupJetId;
   std::vector<double>  *jet_shiftedEnUp;
   std::vector<double>  *jet_shiftedEnDown;
   std::vector<double>  *jet_smearedRes;
   std::vector<double>  *jet_smearedResUp;
   std::vector<double>  *jet_smearedResDown;
   std::vector<double>  *jet_JECL1FastJet;
   std::vector<double>  *jet_JECFull;

   std::vector<double>  *fatjet_pt;
   std::vector<double>  *fatjet_eta;
   std::vector<double>  *fatjet_phi;
   std::vector<double>  *fatjet_charge;
   std::vector<double>  *fatjet_area;
   std::vector<double>  *fatjet_rho;
   std::vector<int>     *fatjet_partonFlavour;
   std::vector<int>     *fatjet_hadronFlavour;
   std::vector<double>  *fatjet_CSVv2;
   std::vector<bool>    *fatjet_tightJetID;
   std::vector<bool>    *fatjet_tightLepVetoJetID;
   std::vector<int>     *fatjet_partonPdgId;
   std::vector<double>  *fatjet_m;
   std::vector<double>  *fatjet_energy;
   std::vector<double>  *fatjet_puppi_tau1;
   std::vector<double>  *fatjet_puppi_tau2;
   std::vector<double>  *fatjet_puppi_tau3;
   std::vector<double>  *fatjet_puppi_tau4;
   std::vector<double>  *fatjet_softdropmass;

   std::vector<double>  *fatjet_chargedHadronEnergyFraction;
   std::vector<double>  *fatjet_neutralHadronEnergyFraction;
   std::vector<double>  *fatjet_neutralEmEnergyFraction;
   std::vector<double>  *fatjet_chargedEmEnergyFraction;
   std::vector<int>     *fatjet_chargedMultiplicity;
   std::vector<int>     *fatjet_neutralMultiplicity;
   std::vector<double>  *fatjet_shiftedEnUp;
   std::vector<double>  *fatjet_shiftedEnDown;
   std::vector<double>  *fatjet_smearedRes;
   std::vector<double>  *fatjet_smearedResUp;
   std::vector<double>  *fatjet_smearedResDown;

   std::vector<double>  *electron_MVAIso;
   std::vector<double>  *electron_MVANoIso;
   std::vector<double>  *electron_Energy;
   std::vector<double>  *electron_Energy_Scale_Up;
   std::vector<double>  *electron_Energy_Scale_Down;
   std::vector<double>  *electron_Energy_Smear_Up;
   std::vector<double>  *electron_Energy_Smear_Down;
   std::vector<double>  *electron_pt;
   std::vector<double>  *electron_pt_Scale_Up;
   std::vector<double>  *electron_pt_Scale_Down;
   std::vector<double>  *electron_pt_Smear_Up;
   std::vector<double>  *electron_pt_Smear_Down;
   std::vector<double>  *electron_eta;
   std::vector<double>  *electron_phi;
   std::vector<int>     *electron_charge;
   std::vector<double>  *electron_gsfpt;
   std::vector<double>  *electron_gsfEta;
   std::vector<double>  *electron_gsfPhi;
   std::vector<int>     *electron_gsfCharge;
   std::vector<double>  *electron_scEta;
   std::vector<double>  *electron_scPhi;
   std::vector<double>  *electron_etaWidth;
   std::vector<double>  *electron_phiWidth;
   std::vector<double>  *electron_dEtaIn;
   std::vector<double>  *electron_dEtaInSeed;
   std::vector<double>  *electron_dPhiIn;
   std::vector<double>  *electron_sigmaIEtaIEta;
   std::vector<double>  *electron_Full5x5_SigmaIEtaIEta;
   std::vector<double>  *electron_HoverE;
   std::vector<double>  *electron_fbrem;
   std::vector<double>  *electron_eOverP;
   std::vector<double>  *electron_InvEminusInvP;

   std::vector<double>  *electron_dxyVTX;
   std::vector<double>  *electron_dxyerrVTX;
   std::vector<double>  *electron_dzVTX;
   std::vector<double>  *electron_dzerrVTX;
   std::vector<double>  *electron_3DIPVTX;
   std::vector<double>  *electron_3DIPerrVTX;
   std::vector<double>  *electron_dxy;
   std::vector<double>  *electron_sigdxy;
   std::vector<double>  *electron_dz;
   std::vector<double>  *electron_dxyBS;
   std::vector<double>  *electron_dzBS;

   std::vector<double>  *electron_chIso03;
   std::vector<double>  *electron_nhIso03;
   std::vector<double>  *electron_phIso03;
   std::vector<double>  *electron_puChIso03;
   std::vector<bool>    *electron_passConversionVeto;
   std::vector<bool>    *electron_isGsfCtfScPixChargeConsistent;
   std::vector<bool>    *electron_isGsfScPixChargeConsistent;
   std::vector<bool>    *electron_isGsfCtfChargeConsistent;
   std::vector<int>     *electron_mHits;
   std::vector<int>     *electron_ecalDriven;
   std::vector<double>  *electron_r9;
   std::vector<double>  *electron_scEnergy;
   std::vector<double>  *electron_scPreEnergy;
   std::vector<double>  *electron_scRawEnergy;
   std::vector<double>  *electron_scEt;
   std::vector<double>  *electron_E15;
   std::vector<double>  *electron_E25;
   std::vector<double>  *electron_E55;

   std::vector<double>  *electron_RelPFIso_dBeta;
   std::vector<double>  *electron_RelPFIso_Rho;
   std::vector<int>     *electron_IDBit;
   std::vector<double>  *electron_EnergyUnCorr;
   std::vector<double>  *electron_chMiniIso;
   std::vector<double>  *electron_nhMiniIso;
   std::vector<double>  *electron_phMiniIso;
   std::vector<double>  *electron_puChMiniIso;
   std::vector<double>  *muon_PfChargedHadronIsoR04;
   std::vector<double>  *muon_PfNeutralHadronIsoR04;
   std::vector<double>  *muon_PfGammaIsoR04;
   std::vector<double>  *muon_PFSumPUIsoR04;
   std::vector<double>  *muon_PfChargedHadronIsoR03;
   std::vector<double>  *muon_PfNeutralHadronIsoR03;
   std::vector<double>  *muon_PfGammaIsoR03;
   std::vector<double>  *muon_PFSumPUIsoR03;
   std::vector<int> *muon_TypeBit;
   std::vector<int> *muon_IDBit;
   std::vector<double>  *muon_dB;
   std::vector<double>  *muon_phi;
   std::vector<double>  *muon_eta;
   std::vector<double>  *muon_pt;
   std::vector<double>  *muon_mass;
   std::vector<double>  *muon_sumtrkpt;
   std::vector<double>  *muon_trkiso;
   std::vector<double>  *muon_hcaliso;
   std::vector<double>  *muon_ecaliso;
   std::vector<double>  *muon_trkisoR05;
   std::vector<double>  *muon_hcalisoR05;
   std::vector<double>  *muon_ecalisoR05;
   std::vector<int>     *muon_charge;
   std::vector<int>     *muon_nChambers;
   std::vector<int>     *muon_matchedstations;
   std::vector<int>     *muon_stationMask;
   std::vector<int>     *muon_nSegments;
   std::vector<double>  *muon_normchi;
   std::vector<int>     *muon_validhits;
   std::vector<int>     *muon_trackerHits;
   std::vector<int>     *muon_pixelHits;
   std::vector<int>     *muon_validmuonhits;
   std::vector<int>     *muon_trackerLayers;
   std::vector<double>  *muon_qoverp;
   std::vector<double>  *muon_theta;
   std::vector<double>  *muon_lambda;
   std::vector<double>  *muon_dxy;
   std::vector<double>  *muon_d0;
   std::vector<double>  *muon_dsz;
   std::vector<double>  *muon_dz;
   std::vector<double>  *muon_dxyBS;
   std::vector<double>  *muon_dzBS;
   std::vector<double>  *muon_dszBS;
   std::vector<double>  *muon_dxyVTX;
   std::vector<double>  *muon_dxyerrVTX;
   std::vector<double>  *muon_dzVTX;
   std::vector<double>  *muon_dzerrVTX;
   std::vector<double>  *muon_3DIPVTX;
   std::vector<double>  *muon_3DIPerrVTX;
   std::vector<double>  *muon_dszVTX;
   std::vector<double>  *muon_dxycktVTX;
   std::vector<double>  *muon_dzcktVTX;
   std::vector<double>  *muon_dszcktVTX;

   std::vector<double>  *muon_vx;
   std::vector<double>  *muon_vy;
   std::vector<double>  *muon_vz;
   std::vector<double>  *muon_Best_pt;
   std::vector<double>  *muon_Best_ptError;
   std::vector<double>  *muon_Best_eta;
   std::vector<double>  *muon_Best_phi;
   std::vector<double>  *muon_Inner_pt;
   std::vector<double>  *muon_Inner_ptError;
   std::vector<double>  *muon_Inner_eta;
   std::vector<double>  *muon_Inner_phi;
   std::vector<double>  *muon_Outer_pt;
   std::vector<double>  *muon_Outer_ptError;
   std::vector<double>  *muon_Outer_eta;
   std::vector<double>  *muon_Outer_phi;
   std::vector<double>  *muon_GLB_pt;
   std::vector<double>  *muon_GLB_ptError;
   std::vector<double>  *muon_GLB_eta;
   std::vector<double>  *muon_GLB_phi;
   std::vector<double>  *muon_TuneP_pt;
   std::vector<double>  *muon_TuneP_ptError;
   std::vector<double>  *muon_TuneP_eta;
   std::vector<double>  *muon_TuneP_phi;
   std::vector<double>  *muon_roch_sf;
   std::vector<double>  *muon_roch_sf_up;
   std::vector<double>  *muon_PfChargedHadronMiniIso;
   std::vector<double>  *muon_PfNeutralHadronMiniIso;
   std::vector<double>  *muon_PfGammaMiniIso;
   std::vector<double>  *muon_PFSumPUMiniIso;

   std::vector<double>  *PDFWeights_Scale;
   std::vector<double>  *PDFWeights_Error;
   std::vector<double>  *PDFWeights_AlphaS;
   std::vector<double>  *gen_phi;
   std::vector<double>  *gen_eta;
   std::vector<double>  *gen_pt;
   std::vector<double>  *gen_mass;
   std::vector<int>     *gen_mother_PID;
   std::vector<double>  *gen_mother_pt;
   std::vector<int>     *gen_mother_index;
   std::vector<int>     *gen_charge;
   std::vector<int>     *gen_status;
   std::vector<int>     *gen_PID;
   std::vector<int>     *gen_isPrompt;
   std::vector<int>     *gen_isPromptFinalState;
   std::vector<int>     *gen_isTauDecayProduct;
   std::vector<int>     *gen_isPromptTauDecayProduct;
   std::vector<int>     *gen_isDirectPromptTauDecayProductFinalState;
   std::vector<int>     *gen_isHardProcess;
   std::vector<int>     *gen_isLastCopy;
   std::vector<int>     *gen_isLastCopyBeforeFSR;
   std::vector<int>     *gen_isPromptDecayed;
   std::vector<int>     *gen_isDecayedLeptonHadron;
   std::vector<int>     *gen_fromHardProcessBeforeFSR;
   std::vector<int>     *gen_fromHardProcessDecayed;
   std::vector<int>     *gen_fromHardProcessFinalState;
   std::vector<int>     *gen_isMostlyLikePythia6Status3;
   Double_t        gen_weight;
   Double_t        genWeight_Q;
   Double_t        genWeight_X1;
   Double_t        genWeight_X2;
   Int_t           genWeight_id1;
   Int_t           genWeight_id2;
   Double_t        genWeight_alphaQCD;
   Double_t        genWeight_alphaQED;
   std::vector<double>  *photon_pt;
   std::vector<double>  *photon_eta;
   std::vector<double>  *photon_phi;
   std::vector<double>  *photon_scEta;
   std::vector<double>  *photon_scPhi;
   std::vector<double>  *photon_HoverE;
   std::vector<int>     *photon_hasPixelSeed;
   std::vector<double>  *photon_Full5x5_SigmaIEtaIEta;
   std::vector<double>  *photon_ChIso;
   std::vector<double>  *photon_NhIso;
   std::vector<double>  *photon_PhIso;
   std::vector<double>  *photon_ChIsoWithEA;
   std::vector<double>  *photon_NhIsoWithEA;
   std::vector<double>  *photon_PhIsoWithEA;
   std::vector<bool>    *photon_passMVAID_WP80;
   std::vector<bool>    *photon_passMVAID_WP90;
   std::vector<bool>    *photon_passLooseID;
   std::vector<bool>    *photon_passMediumID;
   std::vector<bool>    *photon_passTightID;
   std::vector<double>  *photon_ptUnCorr;
   std::vector<double>  *photon_etaUnCorr;
   std::vector<double>  *photon_phiUnCorr;
   Int_t           nPileUp;
   Double_t        pileUpReweightIn;
   Double_t        pileUpReweight;
   Double_t        pileUpReweightPlus;
   Double_t        pileUpReweightMinus;
   Double_t        pileUpReweightInMuonPhys;
   Double_t        pileUpReweightMuonPhys;
   Double_t        pileUpReweightPlusMuonPhys;
   Double_t        pileUpReweightMinusMuonPhys;
   std::vector<double>  *pfMET_pt_shifts;
   std::vector<double>  *pfMET_phi_shifts;
   std::vector<double>  *pfMET_SumEt_shifts;
   std::vector<double>  *pfMET_Type1_pt_shifts;
   std::vector<double>  *pfMET_Type1_phi_shifts;
   std::vector<double>  *pfMET_Type1_SumEt_shifts;
   std::vector<double>  *pfMET_Type1_PhiCor_pt_shifts;
   std::vector<double>  *pfMET_Type1_PhiCor_phi_shifts;
   std::vector<double>  *pfMET_Type1_PhiCor_SumEt_shifts;

   Double_t        pfMET_pt;
   Double_t        pfMET_phi;
   Double_t        pfMET_SumEt;
   Double_t        pfMET_Type1_pt;
   Double_t        pfMET_Type1_phi;
   Double_t        pfMET_Type1_SumEt;
   Double_t        pfMET_Type1_PhiCor_pt;
   Double_t        pfMET_Type1_PhiCor_phi;
   Double_t        pfMET_Type1_PhiCor_SumEt;

   // List of branches                                                                                                                                                                                                                                                       


   TBranch        *b_IsData;   //!
   TBranch        *b_nTotal;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_evtNum;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_Rho;   //!                                                                                                                                                                             
   TBranch        *b_PUweight;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_Flag_goodVertices;   //!                                                                                                                                                               
   TBranch        *b_Flag_globalSuperTightHalo2016Filter;   //!                                                                                                                                                  
   TBranch        *b_Flag_HBHENoiseFilter;   //!                                                                                                                                                            
   TBranch        *b_Flag_HBHENoiseIsoFilter;   //!                                                                                                                                                         
   TBranch        *b_Flag_EcalDeadCellTriggerPrimitiveFilter;   //!                                                                                                                                         
   TBranch        *b_Flag_BadPFMuonFilter;   //!                                                                                                                                                            
   TBranch        *b_Flag_BadChargedCandidateFilter;   //!                                                                                                                                                  
   TBranch        *b_Flag_eeBadScFilter;   //!                                                                                                                                                              
   TBranch        *b_Flag_ecalBadCalibFilter;   //!                                                                                                                                                         
   TBranch        *b_PVtrackSize;   //!
   TBranch        *b_PVchi2;   //!
   TBranch        *b_PVndof;   //!
   TBranch        *b_PVnormalizedChi2;   //!
   TBranch        *b_PVx;   //!
   TBranch        *b_PVy;   //!
   TBranch        *b_PVz;   //!
   TBranch        *b_HLT_TriggerName;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_charge;   //!
   TBranch        *b_jet_area;   //!
   TBranch        *b_jet_partonFlavour;   //!
   TBranch        *b_jet_hadronFlavour;   //!
   TBranch        *b_jet_CSVv2;   //!
   TBranch        *b_jet_DeepCSV;   //!
   TBranch        *b_jet_DeepFlavour;   //!
   TBranch        *b_jet_CvsL;   //!
   TBranch        *b_jet_CvsB;   //!
   TBranch        *b_jet_DeepFlavour_b;   //!                                                                                                                                                               
   TBranch        *b_jet_DeepFlavour_bb;   //!                                                                                                                                                              
   TBranch        *b_jet_DeepFlavour_lepb;   //!                                                                                                                                                            
   TBranch        *b_jet_DeepFlavour_c;   //!                                                                                                                                                               
   TBranch        *b_jet_DeepFlavour_uds;   //!                                                                                                                                                             
   TBranch        *b_jet_DeepFlavour_g;   //!                                                                                                                                                               
   TBranch        *b_jet_DeepCvsL;   //!
   TBranch        *b_jet_DeepCvsB;   //!
   TBranch        *b_jet_chargedHadronEnergyFraction;   //!
   TBranch        *b_jet_neutralHadronEnergyFraction;   //!
   TBranch        *b_jet_neutralEmEnergyFraction;   //!
   TBranch        *b_jet_chargedEmEnergyFraction;   //!
   TBranch        *b_jet_chargedMultiplicity;   //!
   TBranch        *b_jet_neutralMultiplicity;   //!
   TBranch        *b_jet_tightJetID;   //!
   TBranch        *b_jet_tightLepVetoJetID;   //!
   TBranch        *b_jet_partonPdgId;   //!
   TBranch        *b_jet_m;   //!
   TBranch        *b_jet_energy;   //!
   TBranch        *b_jet_PileupJetId;   //!
   TBranch        *b_jet_shiftedEnUp;   //!
   TBranch        *b_jet_shiftedEnDown;   //!
   TBranch        *b_jet_smearedRes;   //!                                                                                                                                                                  
   TBranch        *b_jet_smearedResUp;   //!                                                                                                                                                                
   TBranch        *b_jet_smearedResDown;   //!                                                                                                                                                              
   TBranch        *b_jet_JECL1FastJet;   //!                                                                                                                                                                
   TBranch        *b_jet_JECFull;   //!                                                                                                                                                                     

   TBranch        *b_fatjet_pt;   //!
   TBranch        *b_fatjet_eta;   //!
   TBranch        *b_fatjet_phi;   //!
   TBranch        *b_fatjet_charge;   //!
   TBranch        *b_fatjet_area;   //!
   TBranch        *b_fatjet_partonFlavour;   //!
   TBranch        *b_fatjet_hadronFlavour;   //!
   TBranch        *b_fatjet_CSVv2;   //!
   TBranch        *b_fatjet_tightJetID;   //!
   TBranch        *b_fatjet_tightLepVetoJetID;   //!
   TBranch        *b_fatjet_partonPdgId;   //!
   TBranch        *b_fatjet_m;   //!
   TBranch        *b_fatjet_energy;   //!
   TBranch        *b_fatjet_puppi_tau1;   //!
   TBranch        *b_fatjet_puppi_tau2;   //!
   TBranch        *b_fatjet_puppi_tau3;   //!
   TBranch        *b_fatjet_puppi_tau4;   //!
   TBranch        *b_fatjet_softdropmass;   //!
   TBranch        *b_fatjet_chargedHadronEnergyFraction;   //!
   TBranch        *b_fatjet_neutralHadronEnergyFraction;   //!
   TBranch        *b_fatjet_neutralEmEnergyFraction;   //!
   TBranch        *b_fatjet_chargedEmEnergyFraction;   //!
   TBranch        *b_fatjet_chargedMultiplicity;   //!
   TBranch        *b_fatjet_neutralMultiplicity;   //!
   TBranch        *b_fatjet_shiftedEnUp;   //!
   TBranch        *b_fatjet_shiftedEnDown;   //!
   TBranch        *b_fatjet_smearedRes;   //!                                                                                                                                                               
   TBranch        *b_fatjet_smearedResUp;   //!                                                                                                                                                             
   TBranch        *b_fatjet_smearedResDown;   //!                                                                                                                                                           

   TBranch        *b_electron_MVAIso;   //!
   TBranch        *b_electron_MVANoIso;   //!
   TBranch        *b_electron_Energy;   //!
   TBranch        *b_electron_Energy_Scale_Up;   //!
   TBranch        *b_electron_Energy_Scale_Down;   //!
   TBranch        *b_electron_Energy_Smear_Up;   //!
   TBranch        *b_electron_Energy_Smear_Down;   //!
   TBranch        *b_electron_pt;   //!
   TBranch        *b_electron_pt_Scale_Up;   //!
   TBranch        *b_electron_pt_Scale_Down;   //!
   TBranch        *b_electron_pt_Smear_Up;   //!
   TBranch        *b_electron_pt_Smear_Down;   //!
   TBranch        *b_electron_eta;   //!
   TBranch        *b_electron_phi;   //!
   TBranch        *b_electron_charge;   //!
   TBranch        *b_electron_gsfpt;   //!
   TBranch        *b_electron_gsfEta;   //!
   TBranch        *b_electron_gsfPhi;   //!
   TBranch        *b_electron_gsfCharge;   //!
   TBranch        *b_electron_scEta;   //!
   TBranch        *b_electron_scPhi;   //!
   TBranch        *b_electron_etaWidth;   //!
   TBranch        *b_electron_phiWidth;   //!
   TBranch        *b_electron_dEtaIn;   //!
   TBranch        *b_electron_dEtaInSeed;   //!
   TBranch        *b_electron_dPhiIn;   //!
   TBranch        *b_electron_sigmaIEtaIEta;   //!
   TBranch        *b_electron_Full5x5_SigmaIEtaIEta;   //!
   TBranch        *b_electron_HoverE;   //!
   TBranch        *b_electron_fbrem;   //!
   TBranch        *b_electron_eOverP;   //!
   TBranch        *b_electron_InvEminusInvP; //!
   TBranch        *b_electron_dxyVTX;   //!                                                                                                                                                                 
   TBranch        *b_electron_dxyerrVTX;   //!                                                                                                                                                              
   TBranch        *b_electron_dzVTX;   //!                                                                                                                                                                  
   TBranch        *b_electron_dzerrVTX;   //!                                                                                                                                                               
   TBranch        *b_electron_3DIPVTX;   //!                                                                                                                                                                
   TBranch        *b_electron_3DIPerrVTX;   //!                                                                                                                                                             
   TBranch        *b_electron_dxy;   //!                                                                                                                                                                    
   TBranch        *b_electron_sigdxy;   //!                                                                                                                                                                 
   TBranch        *b_electron_dz;   //!                                                                                                                                                                     
   TBranch        *b_electron_dxyBS;   //!                                                                                                                                                                  
   TBranch        *b_electron_dzBS;   //!                                                                                                                                                                   

   TBranch        *b_electron_chIso03;   //!
   TBranch        *b_electron_nhIso03;   //!
   TBranch        *b_electron_phIso03;   //!
   TBranch        *b_electron_puChIso03;   //!                                                                                                                                                                                                                                 
 
   TBranch        *b_electron_passConversionVeto;   //!
   TBranch        *b_electron_isGsfCtfScPixChargeConsistent;   //!
   TBranch        *b_electron_isGsfScPixChargeConsistent;   //!                                                                                                                                             
   TBranch        *b_electron_isGsfCtfChargeConsistent;   //!                                                                                                                                               

   TBranch        *b_electron_mHits;   //!
   TBranch        *b_electron_ecalDriven;   //!
   TBranch        *b_electron_r9;   //!
   TBranch        *b_electron_scEnergy;   //!
   TBranch        *b_electron_scPreEnergy;   //!
   TBranch        *b_electron_scRawEnergy;   //!
   TBranch        *b_electron_scEt;   //!
   TBranch        *b_electron_E15;   //!
   TBranch        *b_electron_E25;   //!
   TBranch        *b_electron_E55;   //!
   TBranch        *b_electron_RelPFIso_dBeta;   //!
   TBranch        *b_electron_RelPFIso_Rho;   //!

   TBranch        *b_electron_IDBit; //!
   TBranch        *b_electron_ptUnCorr;   //!
   TBranch        *b_electron_etaUnCorr;   //!
   TBranch        *b_electron_phiUnCorr;   //!
   TBranch        *b_electron_EnergyUnCorr;   //!
   TBranch        *b_electron_chMiniIso;   //!                                                                                                                                                              
   TBranch        *b_electron_nhMiniIso;   //!                                                                                                                                                              
   TBranch        *b_electron_phMiniIso;   //!                                                                                                                                                              
   TBranch        *b_electron_puChMiniIso;   //!                                                                                                                                                            

   TBranch        *b_electron_scEnergyUnCorr;   //!
   TBranch        *b_muon_PfChargedHadronIsoR04;   //!
   TBranch        *b_muon_PfNeutralHadronIsoR04;   //!
   TBranch        *b_muon_PfGammaIsoR04;   //!
   TBranch        *b_muon_PFSumPUIsoR04;   //!
   TBranch        *b_muon_PfChargedHadronIsoR03;   //!
   TBranch        *b_muon_PfNeutralHadronIsoR03;   //!
   TBranch        *b_muon_PfGammaIsoR03;   //!
   TBranch        *b_muon_PFSumPUIsoR03;   //!
   TBranch        *b_muon_TypeBit;   //!
   TBranch        *b_muon_IDBit;   //!

   TBranch        *b_muon_dB;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_mass;   //!
   TBranch        *b_muon_sumtrkpt;   //!
   TBranch        *b_muon_trkiso;   //!
   TBranch        *b_muon_hcaliso;   //!
   TBranch        *b_muon_ecaliso;   //!
   TBranch        *b_muon_trkisoR05;   //!
   TBranch        *b_muon_hcalisoR05;   //!
   TBranch        *b_muon_ecalisoR05;   //!
   TBranch        *b_muon_charge;   //!
   TBranch        *b_muon_nChambers;   //!
   TBranch        *b_muon_matchedstations;   //!
   TBranch        *b_muon_stationMask;   //!

   TBranch        *b_muon_nSegments;   //!
   TBranch        *b_muon_normchi;   //!
   TBranch        *b_muon_validhits;   //!

   TBranch        *b_muon_trackerHits;   //!
   TBranch        *b_muon_pixelHits;   //!
   TBranch        *b_muon_validmuonhits;   //!
   TBranch        *b_muon_trackerLayers;   //!
   TBranch        *b_muon_qoverp;   //!
   TBranch        *b_muon_theta;   //!
   TBranch        *b_muon_lambda;   //!
   TBranch        *b_muon_dxy;   //!                                                                                                                                                                        
   TBranch        *b_muon_d0;   //!                                                                                                                                                                         
   TBranch        *b_muon_dsz;   //!                                                                                                                                                                        
   TBranch        *b_muon_dz;   //!                                                                                                                                                                         
   TBranch        *b_muon_dxyBS;   //!                                                                                                                                                                      
   TBranch        *b_muon_dzBS;   //!                                                                                                                                                                       
   TBranch        *b_muon_dszBS;   //!                                                                                                                                                                      
   TBranch        *b_muon_dxyVTX;   //!                                                                                                                                                                     
   TBranch        *b_muon_dxyerrVTX;   //!                                                                                                                                                                  
   TBranch        *b_muon_dzVTX;   //!                                                                                                                                                                      
   TBranch        *b_muon_dzerrVTX;   //!                                                                                                                                                                   
   TBranch        *b_muon_3DIPVTX;   //!                                                                                                                                                                    
   TBranch        *b_muon_3DIPerrVTX;   //!                                                                                                                                                                 
   TBranch        *b_muon_dszVTX;   //!                                                                                                                                                                     
   TBranch        *b_muon_dxycktVTX;   //!                                                                                                                                                                  
   TBranch        *b_muon_dzcktVTX;   //!                                                                                                                                                                   
   TBranch        *b_muon_dszcktVTX;   //!                                                                                                                                                                  

   TBranch        *b_muon_vx;   //!
   TBranch        *b_muon_vy;   //!
   TBranch        *b_muon_vz;   //!
   TBranch        *b_muon_Best_pt;   //!
   TBranch        *b_muon_Best_ptError;   //!
   TBranch        *b_muon_Best_eta;   //!
   TBranch        *b_muon_Best_phi;   //!
   TBranch        *b_muon_Inner_pt;   //!
   TBranch        *b_muon_Inner_ptError;   //!
   TBranch        *b_muon_Inner_eta;   //!
   TBranch        *b_muon_Inner_phi;   //!
   TBranch        *b_muon_Outer_pt;   //!
   TBranch        *b_muon_Outer_ptError;   //!
   TBranch        *b_muon_Outer_eta;   //!
   TBranch        *b_muon_Outer_phi;   //!
   TBranch        *b_muon_GLB_pt;   //!
   TBranch        *b_muon_GLB_ptError;   //!
   TBranch        *b_muon_GLB_eta;   //!
   TBranch        *b_muon_GLB_phi;   //!
   TBranch        *b_muon_TuneP_pt;   //!
   TBranch        *b_muon_TuneP_ptError;   //!
   TBranch        *b_muon_TuneP_eta;   //!
   TBranch        *b_muon_TuneP_phi;   //!
   TBranch        *b_muon_roch_sf;   //!
   TBranch        *b_muon_roch_sf_up;   //!
   TBranch        *b_muon_PfChargedHadronMiniIso;   //!                                                                                                                                                     
   TBranch        *b_muon_PfNeutralHadronMiniIso;   //!                                                                                                                                                     
   TBranch        *b_muon_PfGammaMiniIso;   //!                                                                                                                                                             
   TBranch        *b_muon_PFSumPUMiniIso;   //!                                                                                                                                                             

   TBranch        *b_PDFWeights_Scale;   //!
   TBranch        *b_PDFWeights_Error;   //!
   TBranch        *b_PDFWeights_AlphaS;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_mass;   //!
   TBranch        *b_gen_mother_PID;   //!
   TBranch        *b_gen_mother_pt;   //!
   TBranch        *b_gen_mother_index;   //!
   TBranch        *b_gen_charge;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_PID;   //!
   TBranch        *b_gen_isPrompt;   //!
   TBranch        *b_gen_isPromptFinalState;   //!
   TBranch        *b_gen_isTauDecayProduct;   //!
   TBranch        *b_gen_isPromptTauDecayProduct;   //!
   TBranch        *b_gen_isDirectPromptTauDecayProductFinalState;   //!
   TBranch        *b_gen_isHardProcess;   //!
   TBranch        *b_gen_isLastCopy;   //!
   TBranch        *b_gen_isLastCopyBeforeFSR;   //!
   TBranch        *b_gen_isPromptDecayed;   //!
   TBranch        *b_gen_isDecayedLeptonHadron;   //!
   TBranch        *b_gen_fromHardProcessBeforeFSR;   //!
   TBranch        *b_gen_fromHardProcessDecayed;   //!
   TBranch        *b_gen_fromHardProcessFinalState;   //!
   TBranch        *b_gen_isMostlyLikePythia6Status3;   //!
   TBranch        *b_gen_weight;   //!
   TBranch        *b_genWeight_Q;   //!
   TBranch        *b_genWeight_X1;   //!
   TBranch        *b_genWeight_X2;   //!
   TBranch        *b_genWeight_id1;   //!
   TBranch        *b_genWeight_id2;   //!
   TBranch        *b_genWeight_alphaQCD;   //!
   TBranch        *b_genWeight_alphaQED;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_scEta;   //!
   TBranch        *b_photon_scPhi;   //!
   TBranch        *b_photon_HoverE;   //!
   TBranch        *b_photon_hasPixelSeed;   //!
   TBranch        *b_photon_Full5x5_SigmaIEtaIEta;   //!
   TBranch        *b_photon_ChIso;   //!
   TBranch        *b_photon_NhIso;   //!
   TBranch        *b_photon_PhIso;   //!
   TBranch        *b_photon_ChIsoWithEA;   //!
   TBranch        *b_photon_NhIsoWithEA;   //!
   TBranch        *b_photon_PhIsoWithEA;   //!
   TBranch        *b_photon_passMVAID_WP80;   //!
   TBranch        *b_photon_passMVAID_WP90;   //!
   TBranch        *b_photon_passLooseID;   //!
   TBranch        *b_photon_passMediumID;   //!
   TBranch        *b_photon_passTightID;   //!
   TBranch        *b_photon_ptUnCorr;   //!
   TBranch        *b_photon_etaUnCorr;   //!
   TBranch        *b_photon_phiUnCorr;   //!
   TBranch        *b_nPileUp;   //!
   TBranch        *b_pileUpReweightIn;   //!
   TBranch        *b_pileUpReweight;   //!
   TBranch        *b_pileUpReweightPlus;   //!
   TBranch        *b_pileUpReweightMinus;   //!
   TBranch        *b_pileUpReweightInMuonPhys;   //!
   TBranch        *b_pileUpReweightMuonPhys;   //!
   TBranch        *b_pileUpReweightPlusMuonPhys;   //!
   TBranch        *b_pileUpReweightMinusMuonPhys;   //!
   TBranch        *b_pfMET_phi;   //!
   TBranch        *b_pfMET_pt;   //!
   TBranch        *b_pfMET_SumEt;   //!
   TBranch        *b_pfMET_Type1_pt;   //!
   TBranch        *b_pfMET_Type1_phi;   //!
   TBranch        *b_pfMET_Type1_SumEt;   //!
   TBranch        *b_pfMET_Type1_PhiCor_pt;   //!
   TBranch        *b_pfMET_Type1_PhiCor_phi;   //!
   TBranch        *b_pfMET_Type1_PhiCor_SumEt;   //!

   TBranch        *b_pfMET_pt_shifts;   //!                                                                                                                                                   
   TBranch        *b_pfMET_phi_shifts;   //!                                                                                                                                                  
   TBranch        *b_pfMET_SumEt_shifts;   //!                                                                                                                                                
   TBranch        *b_pfMET_Type1_pt_shifts;   //!                                                                                                                                             
   TBranch        *b_pfMET_Type1_phi_shifts;   //!                                                                                                                                            
   TBranch        *b_pfMET_Type1_SumEt_shifts;   //!                                                                                                                                          
   TBranch        *b_pfMET_Type1_PhiCor_pt_shifts;   //!                                                                                                                                      
   TBranch        *b_pfMET_Type1_PhiCor_phi_shifts;   //!                                                                                                                                     
   TBranch        *b_pfMET_Type1_PhiCor_SumEt_shifts;   //!                                                                                                                                   


   TBranch        *b_inputmuons;
   TBranch        *b_inputtrigger;
   TBranch        *b_inputtruth;
   TBranch        *b_inputjets;
   TBranch        *b_inputfatjets;
   TBranch        *b_inputgenjets;
   TBranch        *b_inputevent;
   TBranch        *b_inputelectrons;
   TBranch        *b_inputphotons;



};

#endif
