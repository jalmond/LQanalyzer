//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 26 07:34:50 2017 by ROOT version 5.34/32
// from TChain ntuple/event/
//////////////////////////////////////////////////////////

#ifndef t2_h
#define t2_h

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

class t2 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          lumi;
   UInt_t          event;
   Double_t        vertex_X;
   Double_t        vertex_Y;
   Double_t        vertex_Z;
   Double_t        met_muonEn_Px_up;
   Double_t        met_muonEn_Py_up;
   Double_t        met_muonEn_Px_down;
   Double_t        met_muonEn_Py_down;
   Double_t        met_electronEn_Px_up;
   Double_t        met_electronEn_Py_up;
   Double_t        met_electronEn_Px_down;
   Double_t        met_electronEn_Py_down;
   string          *CatVersion;
   Bool_t          IsData;
   Bool_t          HBHENoiseFilter;
   Bool_t          HBHENoiseIsoFilter;
   Bool_t          CSCTightHaloFilter;
   Bool_t          goodVertices;
   Bool_t          eeBadScFilter;
   Bool_t          EcalDeadCellTriggerPrimitiveFilter;
   Bool_t          Flag_globalTightHalo2016Filter;
   Float_t         genWeightQ;
   Float_t         genWeightX1;
   Float_t         genWeightX2;
   Int_t           genWeight_id1;
   Int_t           genWeight_id2;
   Float_t         genWeight;
   Float_t         lheWeight;
   vector<string>  *muon_trigmatch;
   vector<string>  *electron_trigmatch;
   vector<string>  *vtrignames;
   vector<bool>    *muon_isTracker;
   vector<bool>    *muon_isGlobal;
   vector<bool>    *muon_isLoose;
   vector<bool>    *muon_isMedium;
   vector<bool>    *muon_isTight;
   vector<bool>    *muon_isSoft;
   vector<bool>    *muon_matched;
   vector<bool>    *muon_isPF;
   vector<bool>    *electrons_electronID_loose;
   vector<bool>    *electrons_electronID_medium;
   vector<bool>    *electrons_electronID_tight;
   vector<bool>    *electrons_electronID_veto;
   vector<bool>    *electrons_electron_hlt;
   vector<bool>    *electrons_electronID_mva_zz;
   vector<bool>    *electrons_electronID_mva_medium;
   vector<bool>    *electrons_electronID_mva_tight;
   vector<bool>    *electrons_electronID_mva_trig_medium;
   vector<bool>    *electrons_electronID_mva_trig_tight;
   vector<bool>    *electrons_electronID_heep;
   vector<bool>    *electrons_mcMatched;
   vector<bool>    *electrons_isPF;
   vector<bool>    *electrons_passConversionVeto;
   vector<bool>    *electrons_isTrigMVAValid;
   vector<bool>    *jets_isLoose;
   vector<bool>    *jets_isTight;
   vector<bool>    *jets_isTightLepVetoJetID;
   vector<bool>    *fatjets_isLoose;
   vector<bool>    *fatjets_isTight;
   vector<bool>    *fatjets_isTightLepVetoJetID;
   vector<bool>    *gen_isprompt;
   vector<bool>    *gen_isdecayedleptonhadron;
   vector<bool>    *gen_istaudecayproduct;
   vector<bool>    *gen_isprompttaudecayproduct;
   vector<bool>    *gen_isdirecthadrondecayproduct;
   vector<bool>    *gen_ishardprocess;
   vector<bool>    *gen_fromhardprocess;
   vector<bool>    *gen_fromhardprocess_beforeFSR;
   vector<int>     *vtrigps;
   vector<int>     *muon_validhits;
   vector<int>     *muon_validmuonhits;
   vector<int>     *muon_matchedstations;
   vector<int>     *muon_validpixhits;
   vector<int>     *muon_trackerlayers;
   vector<int>     *muon_q;
   vector<int>     *electrons_electronID_snu;
   vector<int>     *electrons_q;
   vector<int>     *electrons_missinghits;
   vector<int>     *jets_partonFlavour;
   vector<int>     *jets_hadronFlavour;
   vector<int>     *jets_partonPdgId;
   vector<int>     *jets_vtxNtracks;
   vector<int>     *fatjets_partonFlavour;
   vector<int>     *fatjets_hadronFlavour;
   vector<int>     *fatjets_partonPdgId;
   vector<int>     *fatjets_vtxNtracks;
   vector<int>     *gen_status;
   vector<int>     *gen_pdgid;
   vector<int>     *gen_motherindex;
   vector<int>     *genjet_pdgid;
   vector<double>  *muon_x;
   vector<double>  *muon_y;
   vector<double>  *muon_z;
   vector<double>  *muon_pt;
   vector<double>  *muon_eta;
   vector<double>  *muon_phi;
   vector<double>  *muon_m;
   vector<double>  *muon_energy;
   vector<double>  *muon_roch_pt;
   vector<double>  *muon_roch_eta;
   vector<double>  *muon_roch_phi;
   vector<double>  *muon_roch_m;
   vector<double>  *muon_roch_energy;
   vector<double>  *muon_dxy;
   vector<double>  *muon_sigdxy;
   vector<double>  *muon_dz;
   vector<double>  *muon_normchi;
   vector<double>  *muon_relIso03;
   vector<double>  *muon_relIso04;
   vector<double>  *muon_minirelIso;
   vector<double>  *muon_shiftedEdown;
   vector<double>  *muon_shiftedEup;
   vector<double>  *electrons_x;
   vector<double>  *electrons_y;
   vector<double>  *electrons_z;
   vector<double>  *electrons_pt;
   vector<double>  *electrons_eta;
   vector<double>  *electrons_phi;
   vector<double>  *electrons_m;
   vector<double>  *electrons_energy;
   vector<double>  *electrons_relIso03;
   vector<double>  *electrons_relIso04;
   vector<double>  *electrons_minirelIso;
   vector<double>  *electrons_shiftedEnDown;
   vector<double>  *electrons_shiftedEnUp;
   vector<double>  *electrons_absIso03;
   vector<double>  *electrons_absIso04;
   vector<double>  *electrons_chIso03;
   vector<double>  *electrons_chIso04;
   vector<double>  *electrons_nhIso03;
   vector<double>  *electrons_nhIso04;
   vector<double>  *electrons_phIso03;
   vector<double>  *electrons_phIso04;
   vector<double>  *electrons_scEta;
   vector<double>  *electrons_dxy;
   vector<double>  *electrons_sigdxy;
   vector<double>  *electrons_dz;
   vector<double>  *electrons_isGsfCtfScPixChargeConsistent;
   vector<double>  *electrons_mva;
   vector<double>  *electrons_zzmva;
   vector<double>  *electrons_smearedScale;
   vector<double>  *electrons_puChIso03;
   vector<double>  *electrons_puChIso04;
   vector<double>  *jets_pt;
   vector<double>  *jets_eta;
   vector<double>  *jets_phi;
   vector<double>  *jets_m;
   vector<double>  *jets_energy;
   vector<double>  *jets_vtxMass;
   vector<double>  *jets_vtx3DVal;
   vector<double>  *jets_vtx3DSig;
   vector<double>  *jets_CSVInclV2;
   vector<double>  *jets_iCSVCvsL;
   vector<double>  *jets_CCvsLT;
   vector<double>  *jets_CCvsBT;
   vector<double>  *jets_JetProbBJet;
   vector<double>  *jets_CMVAV2;
   vector<double>  *jets_chargedEmEnergyFraction;
   vector<double>  *jets_shiftedEnDown;
   vector<double>  *jets_shiftedEnUp;
   vector<double>  *jets_smearedRes;
   vector<double>  *jets_smearedResDown;
   vector<double>  *jets_smearedResUp;
   vector<double>  *jets_PileupJetId;
   vector<double>  *jets_L2L3resJEC;
   vector<double>  *jets_L3absJEC;
   vector<double>  *jets_L2relJEC;
   vector<double>  *jets_L1fastjetJEC;
   vector<double>  *jets_Rho;
   vector<double>  *jets_JetArea;
   vector<double>  *jets_rawpt;
   vector<double>  *jets_rawenergy;
   vector<double>  *fatjets_pt;
   vector<double>  *fatjets_eta;
   vector<double>  *fatjets_phi;
   vector<double>  *fatjets_m;
   vector<double>  *fatjets_energy;
   vector<double>  *fatjets_vtxMass;
   vector<double>  *fatjets_vtx3DVal;
   vector<double>  *fatjets_vtx3DSig;
   vector<double>  *fatjets_CSVInclV2;
   vector<double>  *fatjets_iCSVCvsL;
   vector<double>  *fatjets_CCvsLT;
   vector<double>  *fatjets_CCvsBT;
   vector<double>  *fatjets_JetProbBJet;
   vector<double>  *fatjets_CMVAV2;
   vector<double>  *fatjets_chargedEmEnergyFraction;
   vector<double>  *fatjets_shiftedEnDown;
   vector<double>  *fatjets_shiftedEnUp;
   vector<double>  *fatjets_smearedRes;
   vector<double>  *fatjets_smearedResDown;
   vector<double>  *fatjets_smearedResUp;
   vector<double>  *fatjets_PileupJetId;
   vector<double>  *fatjets_L2L3resJEC;
   vector<double>  *fatjets_L3absJEC;
   vector<double>  *fatjets_L2relJEC;
   vector<double>  *fatjets_L1fastjetJEC;
   vector<double>  *fatjets_Rho;
   vector<double>  *fatjets_JetArea;
   vector<double>  *fatjets_tau1;
   vector<double>  *fatjets_tau2;
   vector<double>  *fatjets_tau3;
   vector<double>  *fatjets_prunedmass;
   vector<double>  *fatjets_softdropmass;
   vector<double>  *fatjets_puppi_pt;
   vector<double>  *fatjets_puppi_eta;
   vector<double>  *fatjets_puppi_phi;
   vector<double>  *fatjets_puppi_m;
   vector<double>  *fatjets_puppi_tau1;
   vector<double>  *fatjets_puppi_tau2;
   vector<double>  *fatjets_puppi_tau3;
   vector<float>   *gen_pt;
   vector<float>   *gen_eta;
   vector<float>   *gen_phi;
   vector<float>   *gen_energy;
   vector<float>   *genjet_pt;
   vector<float>   *genjet_eta;
   vector<float>   *genjet_phi;
   vector<float>   *genjet_energy;
   vector<float>   *genjet_emf;
   vector<float>   *genjet_hadf;
   vector<float>   *ScaleWeights;
   vector<float>   *PDFWeights;
   Bool_t          BadChargedCandidateFilter;
   Bool_t          BadPFMuonFilter;
   Int_t           nGoodPV;
   Int_t           nPV;
   Int_t           nTrueInteraction;
   Float_t         puWeightGold;
   Float_t         puWeightGoldB;
   Float_t         puWeightGoldC;
   Float_t         puWeightGoldD;
   Float_t         puWeightGoldDn;
   Float_t         puWeightGoldE;
   Float_t         puWeightGoldF;
   Float_t         puWeightGoldG;
   Float_t         puWeightGoldH;
   Float_t         puWeightGoldUp;
   vector<double>  *met_jetEn_Px_down;
   vector<double>  *met_jetEn_Px_up;
   vector<double>  *met_jetEn_Py_down;
   vector<double>  *met_jetEn_Py_up;
   vector<double>  *met_jetEn_SumEt_down;
   vector<double>  *met_jetEn_SumEt_up;
   vector<double>  *met_jetRes_Px_down;
   vector<double>  *met_jetRes_Px_up;
   vector<double>  *met_jetRes_Py_down;
   vector<double>  *met_jetRes_Py_up;
   vector<double>  *met_jetRes_SumEt_down;
   vector<double>  *met_jetRes_SumEt_up;
   vector<double>  *met_phi;
   vector<double>  *met_pt;
   vector<double>  *met_sumet;
   vector<double>  *met_unclusteredEn_Phi_down;
   vector<double>  *met_unclusteredEn_Phi_up;
   vector<double>  *met_unclusteredEn_Px_down;
   vector<double>  *met_unclusteredEn_Px_up;
   vector<double>  *met_unclusteredEn_Py_down;
   vector<double>  *met_unclusteredEn_Py_up;
   vector<double>  *met_unclusteredEn_SumEt_down;
   vector<double>  *met_unclusteredEn_SumEt_up;
   vector<double>  *met_xyshift_px;
   vector<double>  *met_xyshift_py;
   vector<double>  *met_xyshift_sumet;
   vector<double>  *photons_chargedHadronIso;
   vector<double>  *photons_energy;
   vector<double>  *photons_eta;
   vector<double>  *photons_hovere;
   vector<double>  *photons_neutralHadronIso;
   vector<double>  *photons_phi;
   vector<double>  *photons_photonIso;
   vector<double>  *photons_pt;
   vector<double>  *photons_puChargedHadronIso;
   vector<double>  *photons_r9;
   vector<double>  *photons_rhoIso;
   vector<double>  *photons_sceta;
   vector<double>  *photons_scphi;
   vector<double>  *photons_scpreshowerenergy;
   vector<double>  *photons_scrawenergy;
   vector<double>  *photons_sigmaietaieta;
   vector<bool>    *photons_haspixseed;
   vector<bool>    *photons_mcMatched;
   vector<bool>    *photons_passelectronveto;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_vertex_X;   //!
   TBranch        *b_vertex_Y;   //!
   TBranch        *b_vertex_Z;   //!
   TBranch        *b_met_muonEn_Px_up;   //!
   TBranch        *b_met_muonEn_Py_up;   //!
   TBranch        *b_met_muonEn_Px_down;   //!
   TBranch        *b_met_muonEn_Py_down;   //!
   TBranch        *b_met_electronEn_Px_up;   //!
   TBranch        *b_met_electronEn_Py_up;   //!
   TBranch        *b_met_electronEn_Px_down;   //!
   TBranch        *b_met_electronEn_Py_down;   //!
   TBranch        *b_CatVersion;   //!
   TBranch        *b_IsData;   //!
   TBranch        *b_HBHENoiseFilter;   //!
   TBranch        *b_HBHENoiseIsoFilter;   //!
   TBranch        *b_CSCTightHaloFilter;   //!
   TBranch        *b_goodVertices;   //!
   TBranch        *b_eeBadScFilter;   //!
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!
   TBranch        *b_Flag_globalTightHalo2016Filter;   //!
   TBranch        *b_genWeightQ;   //!
   TBranch        *b_genWeightX1;   //!
   TBranch        *b_genWeightX2;   //!
   TBranch        *b_genWeight_id1;   //!
   TBranch        *b_genWeight_id2;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_lheWeight;   //!
   TBranch        *b_muon_trigmatch;   //!
   TBranch        *b_electron_trigmatch;   //!
   TBranch        *b_vtrignames;   //!
   TBranch        *b_muon_isTracker;   //!
   TBranch        *b_muon_isGlobal;   //!
   TBranch        *b_muon_isLoose;   //!
   TBranch        *b_muon_isMedium;   //!
   TBranch        *b_muon_isTight;   //!
   TBranch        *b_muon_isSoft;   //!
   TBranch        *b_muon_matched;   //!
   TBranch        *b_muon_isPF;   //!
   TBranch        *b_electrons_electronID_loose;   //!
   TBranch        *b_electrons_electronID_medium;   //!
   TBranch        *b_electrons_electronID_tight;   //!
   TBranch        *b_electrons_electronID_veto;   //!
   TBranch        *b_electrons_electron_hlt;   //!
   TBranch        *b_electrons_electronID_mva_zz;   //!
   TBranch        *b_electrons_electronID_mva_medium;   //!
   TBranch        *b_electrons_electronID_mva_tight;   //!
   TBranch        *b_electrons_electronID_mva_trig_medium;   //!
   TBranch        *b_electrons_electronID_mva_trig_tight;   //!
   TBranch        *b_electrons_electronID_heep;   //!
   TBranch        *b_electrons_mcMatched;   //!
   TBranch        *b_electrons_isPF;   //!
   TBranch        *b_electrons_passConversionVeto;   //!
   TBranch        *b_electrons_isTrigMVAValid;   //!
   TBranch        *b_jets_isLoose;   //!
   TBranch        *b_jets_isTight;   //!
   TBranch        *b_jets_isTightLepVetoJetID;   //!
   TBranch        *b_fatjets_isLoose;   //!
   TBranch        *b_fatjets_isTight;   //!
   TBranch        *b_fatjets_isTightLepVetoJetID;   //!
   TBranch        *b_gen_isprompt;   //!
   TBranch        *b_gen_isdecayedleptonhadron;   //!
   TBranch        *b_gen_istaudecayproduct;   //!
   TBranch        *b_gen_isprompttaudecayproduct;   //!
   TBranch        *b_gen_isdirecthadrondecayproduct;   //!
   TBranch        *b_gen_ishardprocess;   //!
   TBranch        *b_gen_fromhardprocess;   //!
   TBranch        *b_gen_fromhardprocess_beforeFSR;   //!
   TBranch        *b_vtrigps;   //!
   TBranch        *b_muon_validhits;   //!
   TBranch        *b_muon_validmuonhits;   //!
   TBranch        *b_muon_matchedstations;   //!
   TBranch        *b_muon_validpixhits;   //!
   TBranch        *b_muon_trackerlayers;   //!
   TBranch        *b_muon_q;   //!
   TBranch        *b_electrons_electronID_snu;   //!
   TBranch        *b_electrons_q;   //!
   TBranch        *b_electrons_missinghits;   //!
   TBranch        *b_jets_partonFlavour;   //!
   TBranch        *b_jets_hadronFlavour;   //!
   TBranch        *b_jets_partonPdgId;   //!
   TBranch        *b_jets_vtxNtracks;   //!
   TBranch        *b_fatjets_partonFlavour;   //!
   TBranch        *b_fatjets_hadronFlavour;   //!
   TBranch        *b_fatjets_partonPdgId;   //!
   TBranch        *b_fatjets_vtxNtracks;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_pdgid;   //!
   TBranch        *b_gen_motherindex;   //!
   TBranch        *b_genjet_pdgid;   //!
   TBranch        *b_muon_x;   //!
   TBranch        *b_muon_y;   //!
   TBranch        *b_muon_z;   //!
   TBranch        *b_muon_pt;   //!
   TBranch        *b_muon_eta;   //!
   TBranch        *b_muon_phi;   //!
   TBranch        *b_muon_m;   //!
   TBranch        *b_muon_energy;   //!
   TBranch        *b_muon_roch_pt;   //!
   TBranch        *b_muon_roch_eta;   //!
   TBranch        *b_muon_roch_phi;   //!
   TBranch        *b_muon_roch_m;   //!
   TBranch        *b_muon_roch_energy;   //!
   TBranch        *b_muon_dxy;   //!
   TBranch        *b_muon_sigdxy;   //!
   TBranch        *b_muon_dz;   //!
   TBranch        *b_muon_normchi;   //!
   TBranch        *b_muon_relIso03;   //!
   TBranch        *b_muon_relIso04;   //!
   TBranch        *b_muon_minirelIso;   //!
   TBranch        *b_muon_shiftedEdown;   //!
   TBranch        *b_muon_shiftedEup;   //!
   TBranch        *b_electrons_x;   //!
   TBranch        *b_electrons_y;   //!
   TBranch        *b_electrons_z;   //!
   TBranch        *b_electrons_pt;   //!
   TBranch        *b_electrons_eta;   //!
   TBranch        *b_electrons_phi;   //!
   TBranch        *b_electrons_m;   //!
   TBranch        *b_electrons_energy;   //!
   TBranch        *b_electrons_relIso03;   //!
   TBranch        *b_electrons_relIso04;   //!
   TBranch        *b_electrons_minirelIso;   //!
   TBranch        *b_electrons_shiftedEnDown;   //!
   TBranch        *b_electrons_shiftedEnUp;   //!
   TBranch        *b_electrons_absIso03;   //!
   TBranch        *b_electrons_absIso04;   //!
   TBranch        *b_electrons_chIso03;   //!
   TBranch        *b_electrons_chIso04;   //!
   TBranch        *b_electrons_nhIso03;   //!
   TBranch        *b_electrons_nhIso04;   //!
   TBranch        *b_electrons_phIso03;   //!
   TBranch        *b_electrons_phIso04;   //!
   TBranch        *b_electrons_scEta;   //!
   TBranch        *b_electrons_dxy;   //!
   TBranch        *b_electrons_sigdxy;   //!
   TBranch        *b_electrons_dz;   //!
   TBranch        *b_electrons_isGsfCtfScPixChargeConsistent;   //!
   TBranch        *b_electrons_mva;   //!
   TBranch        *b_electrons_zzmva;   //!
   TBranch        *b_electrons_smearedScale;   //!
   TBranch        *b_electrons_puChIso03;   //!
   TBranch        *b_electrons_puChIso04;   //!
   TBranch        *b_jets_pt;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_phi;   //!
   TBranch        *b_jets_m;   //!
   TBranch        *b_jets_energy;   //!
   TBranch        *b_jets_vtxMass;   //!
   TBranch        *b_jets_vtx3DVal;   //!
   TBranch        *b_jets_vtx3DSig;   //!
   TBranch        *b_jets_CSVInclV2;   //!
   TBranch        *b_jets_iCSVCvsL;   //!
   TBranch        *b_jets_CCvsLT;   //!
   TBranch        *b_jets_CCvsBT;   //!
   TBranch        *b_jets_JetProbBJet;   //!
   TBranch        *b_jets_CMVAV2;   //!
   TBranch        *b_jets_chargedEmEnergyFraction;   //!
   TBranch        *b_jets_shiftedEnDown;   //!
   TBranch        *b_jets_shiftedEnUp;   //!
   TBranch        *b_jets_smearedRes;   //!
   TBranch        *b_jets_smearedResDown;   //!
   TBranch        *b_jets_smearedResUp;   //!
   TBranch        *b_jets_PileupJetId;   //!
   TBranch        *b_jets_L2L3resJEC;   //!
   TBranch        *b_jets_L3absJEC;   //!
   TBranch        *b_jets_L2relJEC;   //!
   TBranch        *b_jets_L1fastjetJEC;   //!
   TBranch        *b_jets_Rho;   //!
   TBranch        *b_jets_JetArea;   //!
   TBranch        *b_jets_rawpt;   //!
   TBranch        *b_jets_rawenergy;   //!
   TBranch        *b_fatjets_pt;   //!
   TBranch        *b_fatjets_eta;   //!
   TBranch        *b_fatjets_phi;   //!
   TBranch        *b_fatjets_m;   //!
   TBranch        *b_fatjets_energy;   //!
   TBranch        *b_fatjets_vtxMass;   //!
   TBranch        *b_fatjets_vtx3DVal;   //!
   TBranch        *b_fatjets_vtx3DSig;   //!
   TBranch        *b_fatjets_CSVInclV2;   //!
   TBranch        *b_fatjets_iCSVCvsL;   //!
   TBranch        *b_fatjets_CCvsLT;   //!
   TBranch        *b_fatjets_CCvsBT;   //!
   TBranch        *b_fatjets_JetProbBJet;   //!
   TBranch        *b_fatjets_CMVAV2;   //!
   TBranch        *b_fatjets_chargedEmEnergyFraction;   //!
   TBranch        *b_fatjets_shiftedEnDown;   //!
   TBranch        *b_fatjets_shiftedEnUp;   //!
   TBranch        *b_fatjets_smearedRes;   //!
   TBranch        *b_fatjets_smearedResDown;   //!
   TBranch        *b_fatjets_smearedResUp;   //!
   TBranch        *b_fatjets_PileupJetId;   //!
   TBranch        *b_fatjets_L2L3resJEC;   //!
   TBranch        *b_fatjets_L3absJEC;   //!
   TBranch        *b_fatjets_L2relJEC;   //!
   TBranch        *b_fatjets_L1fastjetJEC;   //!
   TBranch        *b_fatjets_Rho;   //!
   TBranch        *b_fatjets_JetArea;   //!
   TBranch        *b_fatjets_tau1;   //!
   TBranch        *b_fatjets_tau2;   //!
   TBranch        *b_fatjets_tau3;   //!
   TBranch        *b_fatjets_prunedmass;   //!
   TBranch        *b_fatjets_softdropmass;   //!
   TBranch        *b_fatjets_puppi_pt;   //!
   TBranch        *b_fatjets_puppi_eta;   //!
   TBranch        *b_fatjets_puppi_phi;   //!
   TBranch        *b_fatjets_puppi_m;   //!
   TBranch        *b_fatjets_puppi_tau1;   //!
   TBranch        *b_fatjets_puppi_tau2;   //!
   TBranch        *b_fatjets_puppi_tau3;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_energy;   //!
   TBranch        *b_genjet_pt;   //!
   TBranch        *b_genjet_eta;   //!
   TBranch        *b_genjet_phi;   //!
   TBranch        *b_genjet_energy;   //!
   TBranch        *b_genjet_emf;   //!
   TBranch        *b_genjet_hadf;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_PDFWeights;   //!
   TBranch        *b_BadChargedCandidateFilter;   //!
   TBranch        *b_BadPFMuonFilter;   //!
   TBranch        *b_nGoodPV;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_nTrueInteraction;   //!
   TBranch        *b_puWeightGold;   //!
   TBranch        *b_puWeightGoldB;   //!
   TBranch        *b_puWeightGoldC;   //!
   TBranch        *b_puWeightGoldD;   //!
   TBranch        *b_puWeightGoldDn;   //!
   TBranch        *b_puWeightGoldE;   //!
   TBranch        *b_puWeightGoldF;   //!
   TBranch        *b_puWeightGoldG;   //!
   TBranch        *b_puWeightGoldH;   //!
   TBranch        *b_puWeightGoldUp;   //!
   TBranch        *b_met_jetEn_Px_down;   //!
   TBranch        *b_met_jetEn_Px_up;   //!
   TBranch        *b_met_jetEn_Py_down;   //!
   TBranch        *b_met_jetEn_Py_up;   //!
   TBranch        *b_met_jetEn_SumEt_down;   //!
   TBranch        *b_met_jetEn_SumEt_up;   //!
   TBranch        *b_met_jetRes_Px_down;   //!
   TBranch        *b_met_jetRes_Px_up;   //!
   TBranch        *b_met_jetRes_Py_down;   //!
   TBranch        *b_met_jetRes_Py_up;   //!
   TBranch        *b_met_jetRes_SumEt_down;   //!
   TBranch        *b_met_jetRes_SumEt_up;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_met_pt;   //!
   TBranch        *b_met_sumet;   //!
   TBranch        *b_met_unclusteredEn_Phi_down;   //!
   TBranch        *b_met_unclusteredEn_Phi_up;   //!
   TBranch        *b_met_unclusteredEn_Px_down;   //!
   TBranch        *b_met_unclusteredEn_Px_up;   //!
   TBranch        *b_met_unclusteredEn_Py_down;   //!
   TBranch        *b_met_unclusteredEn_Py_up;   //!
   TBranch        *b_met_unclusteredEn_SumEt_down;   //!
   TBranch        *b_met_unclusteredEn_SumEt_up;   //!
   TBranch        *b_met_xyshift_px;   //!
   TBranch        *b_met_xyshift_py;   //!
   TBranch        *b_met_xyshift_sumet;   //!
   TBranch        *b_photons_chargedHadronIso;   //!
   TBranch        *b_photons_energy;   //!
   TBranch        *b_photons_eta;   //!
   TBranch        *b_photons_hovere;   //!
   TBranch        *b_photons_neutralHadronIso;   //!
   TBranch        *b_photons_phi;   //!
   TBranch        *b_photons_photonIso;   //!
   TBranch        *b_photons_pt;   //!
   TBranch        *b_photons_puChargedHadronIso;   //!
   TBranch        *b_photons_r9;   //!
   TBranch        *b_photons_rhoIso;   //!
   TBranch        *b_photons_sceta;   //!
   TBranch        *b_photons_scphi;   //!
   TBranch        *b_photons_scpreshowerenergy;   //!
   TBranch        *b_photons_scrawenergy;   //!
   TBranch        *b_photons_sigmaietaieta;   //!
   TBranch        *b_photons_haspixseed;   //!
   TBranch        *b_photons_mcMatched;   //!
   TBranch        *b_photons_passelectronveto;   //!

   t2(TTree *tree=0);
   virtual ~t2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef t2_cxx
t2::t2(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("ntuple/event",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("ntuple/event","");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_1.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_2.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_3.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_4.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_5.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_6.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_7.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_8.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_9.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_10.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_11.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_12.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_13.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_14.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_15.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_16.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_17.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_18.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_19.root/ntuple/event");
      chain->Add("/data2/DATA/cattoflat/MC/v8-0-7/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/ntuple_20.root/ntuple/event");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

t2::~t2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t t2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t t2::LoadTree(Long64_t entry)
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

void t2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   CatVersion = 0;
   muon_trigmatch = 0;
   electron_trigmatch = 0;
   vtrignames = 0;
   muon_isTracker = 0;
   muon_isGlobal = 0;
   muon_isLoose = 0;
   muon_isMedium = 0;
   muon_isTight = 0;
   muon_isSoft = 0;
   muon_matched = 0;
   muon_isPF = 0;
   electrons_electronID_loose = 0;
   electrons_electronID_medium = 0;
   electrons_electronID_tight = 0;
   electrons_electronID_veto = 0;
   electrons_electron_hlt = 0;
   electrons_electronID_mva_zz = 0;
   electrons_electronID_mva_medium = 0;
   electrons_electronID_mva_tight = 0;
   electrons_electronID_mva_trig_medium = 0;
   electrons_electronID_mva_trig_tight = 0;
   electrons_electronID_heep = 0;
   electrons_mcMatched = 0;
   electrons_isPF = 0;
   electrons_passConversionVeto = 0;
   electrons_isTrigMVAValid = 0;
   jets_isLoose = 0;
   jets_isTight = 0;
   jets_isTightLepVetoJetID = 0;
   fatjets_isLoose = 0;
   fatjets_isTight = 0;
   fatjets_isTightLepVetoJetID = 0;
   gen_isprompt = 0;
   gen_isdecayedleptonhadron = 0;
   gen_istaudecayproduct = 0;
   gen_isprompttaudecayproduct = 0;
   gen_isdirecthadrondecayproduct = 0;
   gen_ishardprocess = 0;
   gen_fromhardprocess = 0;
   gen_fromhardprocess_beforeFSR = 0;
   vtrigps = 0;
   muon_validhits = 0;
   muon_validmuonhits = 0;
   muon_matchedstations = 0;
   muon_validpixhits = 0;
   muon_trackerlayers = 0;
   muon_q = 0;
   electrons_electronID_snu = 0;
   electrons_q = 0;
   electrons_missinghits = 0;
   jets_partonFlavour = 0;
   jets_hadronFlavour = 0;
   jets_partonPdgId = 0;
   jets_vtxNtracks = 0;
   fatjets_partonFlavour = 0;
   fatjets_hadronFlavour = 0;
   fatjets_partonPdgId = 0;
   fatjets_vtxNtracks = 0;
   gen_status = 0;
   gen_pdgid = 0;
   gen_motherindex = 0;
   genjet_pdgid = 0;
   muon_x = 0;
   muon_y = 0;
   muon_z = 0;
   muon_pt = 0;
   muon_eta = 0;
   muon_phi = 0;
   muon_m = 0;
   muon_energy = 0;
   muon_roch_pt = 0;
   muon_roch_eta = 0;
   muon_roch_phi = 0;
   muon_roch_m = 0;
   muon_roch_energy = 0;
   muon_dxy = 0;
   muon_sigdxy = 0;
   muon_dz = 0;
   muon_normchi = 0;
   muon_relIso03 = 0;
   muon_relIso04 = 0;
   muon_minirelIso = 0;
   muon_shiftedEdown = 0;
   muon_shiftedEup = 0;
   electrons_x = 0;
   electrons_y = 0;
   electrons_z = 0;
   electrons_pt = 0;
   electrons_eta = 0;
   electrons_phi = 0;
   electrons_m = 0;
   electrons_energy = 0;
   electrons_relIso03 = 0;
   electrons_relIso04 = 0;
   electrons_minirelIso = 0;
   electrons_shiftedEnDown = 0;
   electrons_shiftedEnUp = 0;
   electrons_absIso03 = 0;
   electrons_absIso04 = 0;
   electrons_chIso03 = 0;
   electrons_chIso04 = 0;
   electrons_nhIso03 = 0;
   electrons_nhIso04 = 0;
   electrons_phIso03 = 0;
   electrons_phIso04 = 0;
   electrons_scEta = 0;
   electrons_dxy = 0;
   electrons_sigdxy = 0;
   electrons_dz = 0;
   electrons_isGsfCtfScPixChargeConsistent = 0;
   electrons_mva = 0;
   electrons_zzmva = 0;
   electrons_smearedScale = 0;
   electrons_puChIso03 = 0;
   electrons_puChIso04 = 0;
   jets_pt = 0;
   jets_eta = 0;
   jets_phi = 0;
   jets_m = 0;
   jets_energy = 0;
   jets_vtxMass = 0;
   jets_vtx3DVal = 0;
   jets_vtx3DSig = 0;
   jets_CSVInclV2 = 0;
   jets_iCSVCvsL = 0;
   jets_CCvsLT = 0;
   jets_CCvsBT = 0;
   jets_JetProbBJet = 0;
   jets_CMVAV2 = 0;
   jets_chargedEmEnergyFraction = 0;
   jets_shiftedEnDown = 0;
   jets_shiftedEnUp = 0;
   jets_smearedRes = 0;
   jets_smearedResDown = 0;
   jets_smearedResUp = 0;
   jets_PileupJetId = 0;
   jets_L2L3resJEC = 0;
   jets_L3absJEC = 0;
   jets_L2relJEC = 0;
   jets_L1fastjetJEC = 0;
   jets_Rho = 0;
   jets_JetArea = 0;
   jets_rawpt = 0;
   jets_rawenergy = 0;
   fatjets_pt = 0;
   fatjets_eta = 0;
   fatjets_phi = 0;
   fatjets_m = 0;
   fatjets_energy = 0;
   fatjets_vtxMass = 0;
   fatjets_vtx3DVal = 0;
   fatjets_vtx3DSig = 0;
   fatjets_CSVInclV2 = 0;
   fatjets_iCSVCvsL = 0;
   fatjets_CCvsLT = 0;
   fatjets_CCvsBT = 0;
   fatjets_JetProbBJet = 0;
   fatjets_CMVAV2 = 0;
   fatjets_chargedEmEnergyFraction = 0;
   fatjets_shiftedEnDown = 0;
   fatjets_shiftedEnUp = 0;
   fatjets_smearedRes = 0;
   fatjets_smearedResDown = 0;
   fatjets_smearedResUp = 0;
   fatjets_PileupJetId = 0;
   fatjets_L2L3resJEC = 0;
   fatjets_L3absJEC = 0;
   fatjets_L2relJEC = 0;
   fatjets_L1fastjetJEC = 0;
   fatjets_Rho = 0;
   fatjets_JetArea = 0;
   fatjets_tau1 = 0;
   fatjets_tau2 = 0;
   fatjets_tau3 = 0;
   fatjets_prunedmass = 0;
   fatjets_softdropmass = 0;
   fatjets_puppi_pt = 0;
   fatjets_puppi_eta = 0;
   fatjets_puppi_phi = 0;
   fatjets_puppi_m = 0;
   fatjets_puppi_tau1 = 0;
   fatjets_puppi_tau2 = 0;
   fatjets_puppi_tau3 = 0;
   gen_pt = 0;
   gen_eta = 0;
   gen_phi = 0;
   gen_energy = 0;
   genjet_pt = 0;
   genjet_eta = 0;
   genjet_phi = 0;
   genjet_energy = 0;
   genjet_emf = 0;
   genjet_hadf = 0;
   ScaleWeights = 0;
   PDFWeights = 0;
   met_jetEn_Px_down = 0;
   met_jetEn_Px_up = 0;
   met_jetEn_Py_down = 0;
   met_jetEn_Py_up = 0;
   met_jetEn_SumEt_down = 0;
   met_jetEn_SumEt_up = 0;
   met_jetRes_Px_down = 0;
   met_jetRes_Px_up = 0;
   met_jetRes_Py_down = 0;
   met_jetRes_Py_up = 0;
   met_jetRes_SumEt_down = 0;
   met_jetRes_SumEt_up = 0;
   met_phi = 0;
   met_pt = 0;
   met_sumet = 0;
   met_unclusteredEn_Phi_down = 0;
   met_unclusteredEn_Phi_up = 0;
   met_unclusteredEn_Px_down = 0;
   met_unclusteredEn_Px_up = 0;
   met_unclusteredEn_Py_down = 0;
   met_unclusteredEn_Py_up = 0;
   met_unclusteredEn_SumEt_down = 0;
   met_unclusteredEn_SumEt_up = 0;
   met_xyshift_px = 0;
   met_xyshift_py = 0;
   met_xyshift_sumet = 0;
   photons_chargedHadronIso = 0;
   photons_energy = 0;
   photons_eta = 0;
   photons_hovere = 0;
   photons_neutralHadronIso = 0;
   photons_phi = 0;
   photons_photonIso = 0;
   photons_pt = 0;
   photons_puChargedHadronIso = 0;
   photons_r9 = 0;
   photons_rhoIso = 0;
   photons_sceta = 0;
   photons_scphi = 0;
   photons_scpreshowerenergy = 0;
   photons_scrawenergy = 0;
   photons_sigmaietaieta = 0;
   photons_haspixseed = 0;
   photons_mcMatched = 0;
   photons_passelectronveto = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("vertex_X", &vertex_X, &b_vertex_X);
   fChain->SetBranchAddress("vertex_Y", &vertex_Y, &b_vertex_Y);
   fChain->SetBranchAddress("vertex_Z", &vertex_Z, &b_vertex_Z);
   fChain->SetBranchAddress("met_muonEn_Px_up", &met_muonEn_Px_up, &b_met_muonEn_Px_up);
   fChain->SetBranchAddress("met_muonEn_Py_up", &met_muonEn_Py_up, &b_met_muonEn_Py_up);
   fChain->SetBranchAddress("met_muonEn_Px_down", &met_muonEn_Px_down, &b_met_muonEn_Px_down);
   fChain->SetBranchAddress("met_muonEn_Py_down", &met_muonEn_Py_down, &b_met_muonEn_Py_down);
   fChain->SetBranchAddress("met_electronEn_Px_up", &met_electronEn_Px_up, &b_met_electronEn_Px_up);
   fChain->SetBranchAddress("met_electronEn_Py_up", &met_electronEn_Py_up, &b_met_electronEn_Py_up);
   fChain->SetBranchAddress("met_electronEn_Px_down", &met_electronEn_Px_down, &b_met_electronEn_Px_down);
   fChain->SetBranchAddress("met_electronEn_Py_down", &met_electronEn_Py_down, &b_met_electronEn_Py_down);
   fChain->SetBranchAddress("CatVersion", &CatVersion, &b_CatVersion);
   fChain->SetBranchAddress("IsData", &IsData, &b_IsData);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HBHENoiseIsoFilter", &HBHENoiseIsoFilter, &b_HBHENoiseIsoFilter);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("goodVertices", &goodVertices, &b_goodVertices);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("Flag_globalTightHalo2016Filter", &Flag_globalTightHalo2016Filter, &b_Flag_globalTightHalo2016Filter);
   fChain->SetBranchAddress("genWeightQ", &genWeightQ, &b_genWeightQ);
   fChain->SetBranchAddress("genWeightX1", &genWeightX1, &b_genWeightX1);
   fChain->SetBranchAddress("genWeightX2", &genWeightX2, &b_genWeightX2);
   fChain->SetBranchAddress("genWeight_id1", &genWeight_id1, &b_genWeight_id1);
   fChain->SetBranchAddress("genWeight_id2", &genWeight_id2, &b_genWeight_id2);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("lheWeight", &lheWeight, &b_lheWeight);
   fChain->SetBranchAddress("muon_trigmatch", &muon_trigmatch, &b_muon_trigmatch);
   fChain->SetBranchAddress("electron_trigmatch", &electron_trigmatch, &b_electron_trigmatch);
   fChain->SetBranchAddress("vtrignames", &vtrignames, &b_vtrignames);
   fChain->SetBranchAddress("muon_isTracker", &muon_isTracker, &b_muon_isTracker);
   fChain->SetBranchAddress("muon_isGlobal", &muon_isGlobal, &b_muon_isGlobal);
   fChain->SetBranchAddress("muon_isLoose", &muon_isLoose, &b_muon_isLoose);
   fChain->SetBranchAddress("muon_isMedium", &muon_isMedium, &b_muon_isMedium);
   fChain->SetBranchAddress("muon_isTight", &muon_isTight, &b_muon_isTight);
   fChain->SetBranchAddress("muon_isSoft", &muon_isSoft, &b_muon_isSoft);
   fChain->SetBranchAddress("muon_matched", &muon_matched, &b_muon_matched);
   fChain->SetBranchAddress("muon_isPF", &muon_isPF, &b_muon_isPF);
   fChain->SetBranchAddress("electrons_electronID_loose", &electrons_electronID_loose, &b_electrons_electronID_loose);
   fChain->SetBranchAddress("electrons_electronID_medium", &electrons_electronID_medium, &b_electrons_electronID_medium);
   fChain->SetBranchAddress("electrons_electronID_tight", &electrons_electronID_tight, &b_electrons_electronID_tight);
   fChain->SetBranchAddress("electrons_electronID_veto", &electrons_electronID_veto, &b_electrons_electronID_veto);
   fChain->SetBranchAddress("electrons_electron_hlt", &electrons_electron_hlt, &b_electrons_electron_hlt);
   fChain->SetBranchAddress("electrons_electronID_mva_zz", &electrons_electronID_mva_zz, &b_electrons_electronID_mva_zz);
   fChain->SetBranchAddress("electrons_electronID_mva_medium", &electrons_electronID_mva_medium, &b_electrons_electronID_mva_medium);
   fChain->SetBranchAddress("electrons_electronID_mva_tight", &electrons_electronID_mva_tight, &b_electrons_electronID_mva_tight);
   fChain->SetBranchAddress("electrons_electronID_mva_trig_medium", &electrons_electronID_mva_trig_medium, &b_electrons_electronID_mva_trig_medium);
   fChain->SetBranchAddress("electrons_electronID_mva_trig_tight", &electrons_electronID_mva_trig_tight, &b_electrons_electronID_mva_trig_tight);
   fChain->SetBranchAddress("electrons_electronID_heep", &electrons_electronID_heep, &b_electrons_electronID_heep);
   fChain->SetBranchAddress("electrons_mcMatched", &electrons_mcMatched, &b_electrons_mcMatched);
   fChain->SetBranchAddress("electrons_isPF", &electrons_isPF, &b_electrons_isPF);
   fChain->SetBranchAddress("electrons_passConversionVeto", &electrons_passConversionVeto, &b_electrons_passConversionVeto);
   fChain->SetBranchAddress("electrons_isTrigMVAValid", &electrons_isTrigMVAValid, &b_electrons_isTrigMVAValid);
   fChain->SetBranchAddress("jets_isLoose", &jets_isLoose, &b_jets_isLoose);
   fChain->SetBranchAddress("jets_isTight", &jets_isTight, &b_jets_isTight);
   fChain->SetBranchAddress("jets_isTightLepVetoJetID", &jets_isTightLepVetoJetID, &b_jets_isTightLepVetoJetID);
   fChain->SetBranchAddress("fatjets_isLoose", &fatjets_isLoose, &b_fatjets_isLoose);
   fChain->SetBranchAddress("fatjets_isTight", &fatjets_isTight, &b_fatjets_isTight);
   fChain->SetBranchAddress("fatjets_isTightLepVetoJetID", &fatjets_isTightLepVetoJetID, &b_fatjets_isTightLepVetoJetID);
   fChain->SetBranchAddress("gen_isprompt", &gen_isprompt, &b_gen_isprompt);
   fChain->SetBranchAddress("gen_isdecayedleptonhadron", &gen_isdecayedleptonhadron, &b_gen_isdecayedleptonhadron);
   fChain->SetBranchAddress("gen_istaudecayproduct", &gen_istaudecayproduct, &b_gen_istaudecayproduct);
   fChain->SetBranchAddress("gen_isprompttaudecayproduct", &gen_isprompttaudecayproduct, &b_gen_isprompttaudecayproduct);
   fChain->SetBranchAddress("gen_isdirecthadrondecayproduct", &gen_isdirecthadrondecayproduct, &b_gen_isdirecthadrondecayproduct);
   fChain->SetBranchAddress("gen_ishardprocess", &gen_ishardprocess, &b_gen_ishardprocess);
   fChain->SetBranchAddress("gen_fromhardprocess", &gen_fromhardprocess, &b_gen_fromhardprocess);
   fChain->SetBranchAddress("gen_fromhardprocess_beforeFSR", &gen_fromhardprocess_beforeFSR, &b_gen_fromhardprocess_beforeFSR);
   fChain->SetBranchAddress("vtrigps", &vtrigps, &b_vtrigps);
   fChain->SetBranchAddress("muon_validhits", &muon_validhits, &b_muon_validhits);
   fChain->SetBranchAddress("muon_validmuonhits", &muon_validmuonhits, &b_muon_validmuonhits);
   fChain->SetBranchAddress("muon_matchedstations", &muon_matchedstations, &b_muon_matchedstations);
   fChain->SetBranchAddress("muon_validpixhits", &muon_validpixhits, &b_muon_validpixhits);
   fChain->SetBranchAddress("muon_trackerlayers", &muon_trackerlayers, &b_muon_trackerlayers);
   fChain->SetBranchAddress("muon_q", &muon_q, &b_muon_q);
   fChain->SetBranchAddress("electrons_electronID_snu", &electrons_electronID_snu, &b_electrons_electronID_snu);
   fChain->SetBranchAddress("electrons_q", &electrons_q, &b_electrons_q);
   fChain->SetBranchAddress("electrons_missinghits", &electrons_missinghits, &b_electrons_missinghits);
   fChain->SetBranchAddress("jets_partonFlavour", &jets_partonFlavour, &b_jets_partonFlavour);
   fChain->SetBranchAddress("jets_hadronFlavour", &jets_hadronFlavour, &b_jets_hadronFlavour);
   fChain->SetBranchAddress("jets_partonPdgId", &jets_partonPdgId, &b_jets_partonPdgId);
   fChain->SetBranchAddress("jets_vtxNtracks", &jets_vtxNtracks, &b_jets_vtxNtracks);
   fChain->SetBranchAddress("fatjets_partonFlavour", &fatjets_partonFlavour, &b_fatjets_partonFlavour);
   fChain->SetBranchAddress("fatjets_hadronFlavour", &fatjets_hadronFlavour, &b_fatjets_hadronFlavour);
   fChain->SetBranchAddress("fatjets_partonPdgId", &fatjets_partonPdgId, &b_fatjets_partonPdgId);
   fChain->SetBranchAddress("fatjets_vtxNtracks", &fatjets_vtxNtracks, &b_fatjets_vtxNtracks);
   fChain->SetBranchAddress("gen_status", &gen_status, &b_gen_status);
   fChain->SetBranchAddress("gen_pdgid", &gen_pdgid, &b_gen_pdgid);
   fChain->SetBranchAddress("gen_motherindex", &gen_motherindex, &b_gen_motherindex);
   fChain->SetBranchAddress("genjet_pdgid", &genjet_pdgid, &b_genjet_pdgid);
   fChain->SetBranchAddress("muon_x", &muon_x, &b_muon_x);
   fChain->SetBranchAddress("muon_y", &muon_y, &b_muon_y);
   fChain->SetBranchAddress("muon_z", &muon_z, &b_muon_z);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_m", &muon_m, &b_muon_m);
   fChain->SetBranchAddress("muon_energy", &muon_energy, &b_muon_energy);
   fChain->SetBranchAddress("muon_roch_pt", &muon_roch_pt, &b_muon_roch_pt);
   fChain->SetBranchAddress("muon_roch_eta", &muon_roch_eta, &b_muon_roch_eta);
   fChain->SetBranchAddress("muon_roch_phi", &muon_roch_phi, &b_muon_roch_phi);
   fChain->SetBranchAddress("muon_roch_m", &muon_roch_m, &b_muon_roch_m);
   fChain->SetBranchAddress("muon_roch_energy", &muon_roch_energy, &b_muon_roch_energy);
   fChain->SetBranchAddress("muon_dxy", &muon_dxy, &b_muon_dxy);
   fChain->SetBranchAddress("muon_sigdxy", &muon_sigdxy, &b_muon_sigdxy);
   fChain->SetBranchAddress("muon_dz", &muon_dz, &b_muon_dz);
   fChain->SetBranchAddress("muon_normchi", &muon_normchi, &b_muon_normchi);
   fChain->SetBranchAddress("muon_relIso03", &muon_relIso03, &b_muon_relIso03);
   fChain->SetBranchAddress("muon_relIso04", &muon_relIso04, &b_muon_relIso04);
   fChain->SetBranchAddress("muon_minirelIso", &muon_minirelIso, &b_muon_minirelIso);
   fChain->SetBranchAddress("muon_shiftedEdown", &muon_shiftedEdown, &b_muon_shiftedEdown);
   fChain->SetBranchAddress("muon_shiftedEup", &muon_shiftedEup, &b_muon_shiftedEup);
   fChain->SetBranchAddress("electrons_x", &electrons_x, &b_electrons_x);
   fChain->SetBranchAddress("electrons_y", &electrons_y, &b_electrons_y);
   fChain->SetBranchAddress("electrons_z", &electrons_z, &b_electrons_z);
   fChain->SetBranchAddress("electrons_pt", &electrons_pt, &b_electrons_pt);
   fChain->SetBranchAddress("electrons_eta", &electrons_eta, &b_electrons_eta);
   fChain->SetBranchAddress("electrons_phi", &electrons_phi, &b_electrons_phi);
   fChain->SetBranchAddress("electrons_m", &electrons_m, &b_electrons_m);
   fChain->SetBranchAddress("electrons_energy", &electrons_energy, &b_electrons_energy);
   fChain->SetBranchAddress("electrons_relIso03", &electrons_relIso03, &b_electrons_relIso03);
   fChain->SetBranchAddress("electrons_relIso04", &electrons_relIso04, &b_electrons_relIso04);
   fChain->SetBranchAddress("electrons_minirelIso", &electrons_minirelIso, &b_electrons_minirelIso);
   fChain->SetBranchAddress("electrons_shiftedEnDown", &electrons_shiftedEnDown, &b_electrons_shiftedEnDown);
   fChain->SetBranchAddress("electrons_shiftedEnUp", &electrons_shiftedEnUp, &b_electrons_shiftedEnUp);
   fChain->SetBranchAddress("electrons_absIso03", &electrons_absIso03, &b_electrons_absIso03);
   fChain->SetBranchAddress("electrons_absIso04", &electrons_absIso04, &b_electrons_absIso04);
   fChain->SetBranchAddress("electrons_chIso03", &electrons_chIso03, &b_electrons_chIso03);
   fChain->SetBranchAddress("electrons_chIso04", &electrons_chIso04, &b_electrons_chIso04);
   fChain->SetBranchAddress("electrons_nhIso03", &electrons_nhIso03, &b_electrons_nhIso03);
   fChain->SetBranchAddress("electrons_nhIso04", &electrons_nhIso04, &b_electrons_nhIso04);
   fChain->SetBranchAddress("electrons_phIso03", &electrons_phIso03, &b_electrons_phIso03);
   fChain->SetBranchAddress("electrons_phIso04", &electrons_phIso04, &b_electrons_phIso04);
   fChain->SetBranchAddress("electrons_scEta", &electrons_scEta, &b_electrons_scEta);
   fChain->SetBranchAddress("electrons_dxy", &electrons_dxy, &b_electrons_dxy);
   fChain->SetBranchAddress("electrons_sigdxy", &electrons_sigdxy, &b_electrons_sigdxy);
   fChain->SetBranchAddress("electrons_dz", &electrons_dz, &b_electrons_dz);
   fChain->SetBranchAddress("electrons_isGsfCtfScPixChargeConsistent", &electrons_isGsfCtfScPixChargeConsistent, &b_electrons_isGsfCtfScPixChargeConsistent);
   fChain->SetBranchAddress("electrons_mva", &electrons_mva, &b_electrons_mva);
   fChain->SetBranchAddress("electrons_zzmva", &electrons_zzmva, &b_electrons_zzmva);
   fChain->SetBranchAddress("electrons_smearedScale", &electrons_smearedScale, &b_electrons_smearedScale);
   fChain->SetBranchAddress("electrons_puChIso03", &electrons_puChIso03, &b_electrons_puChIso03);
   fChain->SetBranchAddress("electrons_puChIso04", &electrons_puChIso04, &b_electrons_puChIso04);
   fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets_m", &jets_m, &b_jets_m);
   fChain->SetBranchAddress("jets_energy", &jets_energy, &b_jets_energy);
   fChain->SetBranchAddress("jets_vtxMass", &jets_vtxMass, &b_jets_vtxMass);
   fChain->SetBranchAddress("jets_vtx3DVal", &jets_vtx3DVal, &b_jets_vtx3DVal);
   fChain->SetBranchAddress("jets_vtx3DSig", &jets_vtx3DSig, &b_jets_vtx3DSig);
   fChain->SetBranchAddress("jets_CSVInclV2", &jets_CSVInclV2, &b_jets_CSVInclV2);
   fChain->SetBranchAddress("jets_iCSVCvsL", &jets_iCSVCvsL, &b_jets_iCSVCvsL);
   fChain->SetBranchAddress("jets_CCvsLT", &jets_CCvsLT, &b_jets_CCvsLT);
   fChain->SetBranchAddress("jets_CCvsBT", &jets_CCvsBT, &b_jets_CCvsBT);
   fChain->SetBranchAddress("jets_JetProbBJet", &jets_JetProbBJet, &b_jets_JetProbBJet);
   fChain->SetBranchAddress("jets_CMVAV2", &jets_CMVAV2, &b_jets_CMVAV2);
   fChain->SetBranchAddress("jets_chargedEmEnergyFraction", &jets_chargedEmEnergyFraction, &b_jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("jets_shiftedEnDown", &jets_shiftedEnDown, &b_jets_shiftedEnDown);
   fChain->SetBranchAddress("jets_shiftedEnUp", &jets_shiftedEnUp, &b_jets_shiftedEnUp);
   fChain->SetBranchAddress("jets_smearedRes", &jets_smearedRes, &b_jets_smearedRes);
   fChain->SetBranchAddress("jets_smearedResDown", &jets_smearedResDown, &b_jets_smearedResDown);
   fChain->SetBranchAddress("jets_smearedResUp", &jets_smearedResUp, &b_jets_smearedResUp);
   fChain->SetBranchAddress("jets_PileupJetId", &jets_PileupJetId, &b_jets_PileupJetId);
   fChain->SetBranchAddress("jets_L2L3resJEC", &jets_L2L3resJEC, &b_jets_L2L3resJEC);
   fChain->SetBranchAddress("jets_L3absJEC", &jets_L3absJEC, &b_jets_L3absJEC);
   fChain->SetBranchAddress("jets_L2relJEC", &jets_L2relJEC, &b_jets_L2relJEC);
   fChain->SetBranchAddress("jets_L1fastjetJEC", &jets_L1fastjetJEC, &b_jets_L1fastjetJEC);
   fChain->SetBranchAddress("jets_Rho", &jets_Rho, &b_jets_Rho);
   fChain->SetBranchAddress("jets_JetArea", &jets_JetArea, &b_jets_JetArea);
   fChain->SetBranchAddress("jets_rawpt", &jets_rawpt, &b_jets_rawpt);
   fChain->SetBranchAddress("jets_rawenergy", &jets_rawenergy, &b_jets_rawenergy);
   fChain->SetBranchAddress("fatjets_pt", &fatjets_pt, &b_fatjets_pt);
   fChain->SetBranchAddress("fatjets_eta", &fatjets_eta, &b_fatjets_eta);
   fChain->SetBranchAddress("fatjets_phi", &fatjets_phi, &b_fatjets_phi);
   fChain->SetBranchAddress("fatjets_m", &fatjets_m, &b_fatjets_m);
   fChain->SetBranchAddress("fatjets_energy", &fatjets_energy, &b_fatjets_energy);
   fChain->SetBranchAddress("fatjets_vtxMass", &fatjets_vtxMass, &b_fatjets_vtxMass);
   fChain->SetBranchAddress("fatjets_vtx3DVal", &fatjets_vtx3DVal, &b_fatjets_vtx3DVal);
   fChain->SetBranchAddress("fatjets_vtx3DSig", &fatjets_vtx3DSig, &b_fatjets_vtx3DSig);
   fChain->SetBranchAddress("fatjets_CSVInclV2", &fatjets_CSVInclV2, &b_fatjets_CSVInclV2);
   fChain->SetBranchAddress("fatjets_iCSVCvsL", &fatjets_iCSVCvsL, &b_fatjets_iCSVCvsL);
   fChain->SetBranchAddress("fatjets_CCvsLT", &fatjets_CCvsLT, &b_fatjets_CCvsLT);
   fChain->SetBranchAddress("fatjets_CCvsBT", &fatjets_CCvsBT, &b_fatjets_CCvsBT);
   fChain->SetBranchAddress("fatjets_JetProbBJet", &fatjets_JetProbBJet, &b_fatjets_JetProbBJet);
   fChain->SetBranchAddress("fatjets_CMVAV2", &fatjets_CMVAV2, &b_fatjets_CMVAV2);
   fChain->SetBranchAddress("fatjets_chargedEmEnergyFraction", &fatjets_chargedEmEnergyFraction, &b_fatjets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("fatjets_shiftedEnDown", &fatjets_shiftedEnDown, &b_fatjets_shiftedEnDown);
   fChain->SetBranchAddress("fatjets_shiftedEnUp", &fatjets_shiftedEnUp, &b_fatjets_shiftedEnUp);
   fChain->SetBranchAddress("fatjets_smearedRes", &fatjets_smearedRes, &b_fatjets_smearedRes);
   fChain->SetBranchAddress("fatjets_smearedResDown", &fatjets_smearedResDown, &b_fatjets_smearedResDown);
   fChain->SetBranchAddress("fatjets_smearedResUp", &fatjets_smearedResUp, &b_fatjets_smearedResUp);
   fChain->SetBranchAddress("fatjets_PileupJetId", &fatjets_PileupJetId, &b_fatjets_PileupJetId);
   fChain->SetBranchAddress("fatjets_L2L3resJEC", &fatjets_L2L3resJEC, &b_fatjets_L2L3resJEC);
   fChain->SetBranchAddress("fatjets_L3absJEC", &fatjets_L3absJEC, &b_fatjets_L3absJEC);
   fChain->SetBranchAddress("fatjets_L2relJEC", &fatjets_L2relJEC, &b_fatjets_L2relJEC);
   fChain->SetBranchAddress("fatjets_L1fastjetJEC", &fatjets_L1fastjetJEC, &b_fatjets_L1fastjetJEC);
   fChain->SetBranchAddress("fatjets_Rho", &fatjets_Rho, &b_fatjets_Rho);
   fChain->SetBranchAddress("fatjets_JetArea", &fatjets_JetArea, &b_fatjets_JetArea);
   fChain->SetBranchAddress("fatjets_tau1", &fatjets_tau1, &b_fatjets_tau1);
   fChain->SetBranchAddress("fatjets_tau2", &fatjets_tau2, &b_fatjets_tau2);
   fChain->SetBranchAddress("fatjets_tau3", &fatjets_tau3, &b_fatjets_tau3);
   fChain->SetBranchAddress("fatjets_prunedmass", &fatjets_prunedmass, &b_fatjets_prunedmass);
   fChain->SetBranchAddress("fatjets_softdropmass", &fatjets_softdropmass, &b_fatjets_softdropmass);
   fChain->SetBranchAddress("fatjets_puppi_pt", &fatjets_puppi_pt, &b_fatjets_puppi_pt);
   fChain->SetBranchAddress("fatjets_puppi_eta", &fatjets_puppi_eta, &b_fatjets_puppi_eta);
   fChain->SetBranchAddress("fatjets_puppi_phi", &fatjets_puppi_phi, &b_fatjets_puppi_phi);
   fChain->SetBranchAddress("fatjets_puppi_m", &fatjets_puppi_m, &b_fatjets_puppi_m);
   fChain->SetBranchAddress("fatjets_puppi_tau1", &fatjets_puppi_tau1, &b_fatjets_puppi_tau1);
   fChain->SetBranchAddress("fatjets_puppi_tau2", &fatjets_puppi_tau2, &b_fatjets_puppi_tau2);
   fChain->SetBranchAddress("fatjets_puppi_tau3", &fatjets_puppi_tau3, &b_fatjets_puppi_tau3);
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_energy", &gen_energy, &b_gen_energy);
   fChain->SetBranchAddress("genjet_pt", &genjet_pt, &b_genjet_pt);
   fChain->SetBranchAddress("genjet_eta", &genjet_eta, &b_genjet_eta);
   fChain->SetBranchAddress("genjet_phi", &genjet_phi, &b_genjet_phi);
   fChain->SetBranchAddress("genjet_energy", &genjet_energy, &b_genjet_energy);
   fChain->SetBranchAddress("genjet_emf", &genjet_emf, &b_genjet_emf);
   fChain->SetBranchAddress("genjet_hadf", &genjet_hadf, &b_genjet_hadf);
   fChain->SetBranchAddress("ScaleWeights", &ScaleWeights, &b_ScaleWeights);
   fChain->SetBranchAddress("PDFWeights", &PDFWeights, &b_PDFWeights);
   fChain->SetBranchAddress("BadChargedCandidateFilter", &BadChargedCandidateFilter, &b_BadChargedCandidateFilter);
   fChain->SetBranchAddress("BadPFMuonFilter", &BadPFMuonFilter, &b_BadPFMuonFilter);
   fChain->SetBranchAddress("nGoodPV", &nGoodPV, &b_nGoodPV);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nTrueInteraction", &nTrueInteraction, &b_nTrueInteraction);
   fChain->SetBranchAddress("puWeightGold", &puWeightGold, &b_puWeightGold);
   fChain->SetBranchAddress("puWeightGoldB", &puWeightGoldB, &b_puWeightGoldB);
   fChain->SetBranchAddress("puWeightGoldC", &puWeightGoldC, &b_puWeightGoldC);
   fChain->SetBranchAddress("puWeightGoldD", &puWeightGoldD, &b_puWeightGoldD);
   fChain->SetBranchAddress("puWeightGoldDn", &puWeightGoldDn, &b_puWeightGoldDn);
   fChain->SetBranchAddress("puWeightGoldE", &puWeightGoldE, &b_puWeightGoldE);
   fChain->SetBranchAddress("puWeightGoldF", &puWeightGoldF, &b_puWeightGoldF);
   fChain->SetBranchAddress("puWeightGoldG", &puWeightGoldG, &b_puWeightGoldG);
   fChain->SetBranchAddress("puWeightGoldH", &puWeightGoldH, &b_puWeightGoldH);
   fChain->SetBranchAddress("puWeightGoldUp", &puWeightGoldUp, &b_puWeightGoldUp);
   fChain->SetBranchAddress("met_jetEn_Px_down", &met_jetEn_Px_down, &b_met_jetEn_Px_down);
   fChain->SetBranchAddress("met_jetEn_Px_up", &met_jetEn_Px_up, &b_met_jetEn_Px_up);
   fChain->SetBranchAddress("met_jetEn_Py_down", &met_jetEn_Py_down, &b_met_jetEn_Py_down);
   fChain->SetBranchAddress("met_jetEn_Py_up", &met_jetEn_Py_up, &b_met_jetEn_Py_up);
   fChain->SetBranchAddress("met_jetEn_SumEt_down", &met_jetEn_SumEt_down, &b_met_jetEn_SumEt_down);
   fChain->SetBranchAddress("met_jetEn_SumEt_up", &met_jetEn_SumEt_up, &b_met_jetEn_SumEt_up);
   fChain->SetBranchAddress("met_jetRes_Px_down", &met_jetRes_Px_down, &b_met_jetRes_Px_down);
   fChain->SetBranchAddress("met_jetRes_Px_up", &met_jetRes_Px_up, &b_met_jetRes_Px_up);
   fChain->SetBranchAddress("met_jetRes_Py_down", &met_jetRes_Py_down, &b_met_jetRes_Py_down);
   fChain->SetBranchAddress("met_jetRes_Py_up", &met_jetRes_Py_up, &b_met_jetRes_Py_up);
   fChain->SetBranchAddress("met_jetRes_SumEt_down", &met_jetRes_SumEt_down, &b_met_jetRes_SumEt_down);
   fChain->SetBranchAddress("met_jetRes_SumEt_up", &met_jetRes_SumEt_up, &b_met_jetRes_SumEt_up);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("met_unclusteredEn_Phi_down", &met_unclusteredEn_Phi_down, &b_met_unclusteredEn_Phi_down);
   fChain->SetBranchAddress("met_unclusteredEn_Phi_up", &met_unclusteredEn_Phi_up, &b_met_unclusteredEn_Phi_up);
   fChain->SetBranchAddress("met_unclusteredEn_Px_down", &met_unclusteredEn_Px_down, &b_met_unclusteredEn_Px_down);
   fChain->SetBranchAddress("met_unclusteredEn_Px_up", &met_unclusteredEn_Px_up, &b_met_unclusteredEn_Px_up);
   fChain->SetBranchAddress("met_unclusteredEn_Py_down", &met_unclusteredEn_Py_down, &b_met_unclusteredEn_Py_down);
   fChain->SetBranchAddress("met_unclusteredEn_Py_up", &met_unclusteredEn_Py_up, &b_met_unclusteredEn_Py_up);
   fChain->SetBranchAddress("met_unclusteredEn_SumEt_down", &met_unclusteredEn_SumEt_down, &b_met_unclusteredEn_SumEt_down);
   fChain->SetBranchAddress("met_unclusteredEn_SumEt_up", &met_unclusteredEn_SumEt_up, &b_met_unclusteredEn_SumEt_up);
   fChain->SetBranchAddress("met_xyshift_px", &met_xyshift_px, &b_met_xyshift_px);
   fChain->SetBranchAddress("met_xyshift_py", &met_xyshift_py, &b_met_xyshift_py);
   fChain->SetBranchAddress("met_xyshift_sumet", &met_xyshift_sumet, &b_met_xyshift_sumet);
   fChain->SetBranchAddress("photons_chargedHadronIso", &photons_chargedHadronIso, &b_photons_chargedHadronIso);
   fChain->SetBranchAddress("photons_energy", &photons_energy, &b_photons_energy);
   fChain->SetBranchAddress("photons_eta", &photons_eta, &b_photons_eta);
   fChain->SetBranchAddress("photons_hovere", &photons_hovere, &b_photons_hovere);
   fChain->SetBranchAddress("photons_neutralHadronIso", &photons_neutralHadronIso, &b_photons_neutralHadronIso);
   fChain->SetBranchAddress("photons_phi", &photons_phi, &b_photons_phi);
   fChain->SetBranchAddress("photons_photonIso", &photons_photonIso, &b_photons_photonIso);
   fChain->SetBranchAddress("photons_pt", &photons_pt, &b_photons_pt);
   fChain->SetBranchAddress("photons_puChargedHadronIso", &photons_puChargedHadronIso, &b_photons_puChargedHadronIso);
   fChain->SetBranchAddress("photons_r9", &photons_r9, &b_photons_r9);
   fChain->SetBranchAddress("photons_rhoIso", &photons_rhoIso, &b_photons_rhoIso);
   fChain->SetBranchAddress("photons_sceta", &photons_sceta, &b_photons_sceta);
   fChain->SetBranchAddress("photons_scphi", &photons_scphi, &b_photons_scphi);
   fChain->SetBranchAddress("photons_scpreshowerenergy", &photons_scpreshowerenergy, &b_photons_scpreshowerenergy);
   fChain->SetBranchAddress("photons_scrawenergy", &photons_scrawenergy, &b_photons_scrawenergy);
   fChain->SetBranchAddress("photons_sigmaietaieta", &photons_sigmaietaieta, &b_photons_sigmaietaieta);
   fChain->SetBranchAddress("photons_haspixseed", &photons_haspixseed, &b_photons_haspixseed);
   fChain->SetBranchAddress("photons_mcMatched", &photons_mcMatched, &b_photons_mcMatched);
   fChain->SetBranchAddress("photons_passelectronveto", &photons_passelectronveto, &b_photons_passelectronveto);
   Notify();
}

Bool_t t2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t t2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef t2_cxx
