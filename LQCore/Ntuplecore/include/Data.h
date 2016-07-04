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
   std::vector<snu::KGenJet>     *k_inputgenjets;
   snu::KEvent     *k_inputevent;
   snu::KTrigger     *k_inputtrigger;
   std::vector<snu::KTruth>     *k_inputtruth;

   int setting_ntuple_data;
   
   Bool_t          isData;
   Double_t        lumiSilver;
   Double_t        lumiGolden;

   std::vector<TBranch*> m_inputbranches;

   std::string CatVersion;
   float TargetLumi;
   std::vector<TString>  k_flags;
   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
   Int_t           lumiMaskGold;
   Int_t           lumiMaskSilver;


   std::vector<std::string>  *vtrignames;
   std::vector<int>     *vtrigps;
   std::vector<std::string>  *muon_trigmatch;
   std::vector<std::string>  *electron_trigmatch;
   std::vector<float>   *gen_pt;
   std::vector<float>   *gen_eta;
   std::vector<float>   *gen_phi;
   std::vector<float>   *gen_energy;
   std::vector<float>   *ScaleWeights;
   std::vector<float>   *PDFWeights;
   std::vector<float>   *genjet_pt;
   std::vector<float>   *genjet_eta;
   std::vector<float>   *genjet_phi;
   std::vector<float>   *genjet_energy;
   std::vector<float>   *genjet_emf;
   std::vector<float>   *genjet_hadf;
   std::vector<int>     *genjet_pdgid;
   std::vector<int>     *gen_status;
   std::vector<int>     *gen_pdgid;
   std::vector<int>     *gen_motherindex;

   Bool_t          HBHENoiseFilter;
   Bool_t          csctighthaloFilter;
   Bool_t          ecalDCTRFilter;
   Bool_t          eeBadScFilter;
   Bool_t          goodVertices;
   Int_t           GenTTCat;
   Int_t           genWeight_id1;
   Int_t           genWeight_id2;
   Int_t           hlt_2el33;
   Int_t           hlt_el12;
   Int_t           hlt_el16_el12_8;
   Int_t           hlt_el17;
   Int_t           hlt_el17_el12;
   Int_t           hlt_el23_el12;
   Int_t           hlt_el23_el12dz;
   Int_t           hlt_ele27eta2p1;
   Int_t           hlt_mu17_el12;
   Int_t           hlt_mu17_mu8;
   Int_t           hlt_mu17_tkmu8;
   Int_t           hlt_mu8_el17;
   Int_t           nGoodPV;
   Int_t           nPV;
   Int_t           nTrueInteraction;
   Float_t         genWeight;
   Float_t         genWeightQ;
   Float_t         genWeightX1;
   Float_t         genWeightX2;
   Float_t         lheWeight;
   Float_t         puWeightGold;
   Float_t         puWeightGoldDn;
   Float_t         puWeightGoldUp;
   Float_t         puWeightGoldDn_xs71000;
   Float_t         puWeightGoldUp_xs71000;
   Float_t         puWeightGold_xs71000;

   Float_t         puWeightSilver;
   Float_t         puWeightSilverDn;
   Float_t         puWeightSilverUp;
   

   std::vector<double>  *electrons_absIso03;
   std::vector<double>  *electrons_absIso04;
   std::vector<double>  *electrons_chIso03;
   std::vector<double>  *electrons_chIso04;
   std::vector<double>  *electrons_dxy;
   std::vector<double>  *electrons_sigdxy;
   std::vector<double>  *electrons_dz;
   std::vector<double>  *electrons_energy;
   std::vector<double>  *electrons_eta;
   std::vector<double>  *electrons_isGsfCtfScPixChargeConsistent;
   std::vector<double>  *electrons_m;
   std::vector<double>  *electrons_nhIso03;
   std::vector<double>  *electrons_nhIso04;
   std::vector<double>  *electrons_phIso03;
   std::vector<double>  *electrons_phIso04;
   std::vector<double>  *electrons_phi;
   std::vector<double>  *electrons_pt;
   std::vector<double>  *electrons_puChIso03;
   std::vector<double>  *electrons_puChIso04;

   std::vector<double>  *electrons_relIso03;
   std::vector<double>  *electrons_relIso04;
   std::vector<double>  *electrons_scEta;
   std::vector<double>  *electrons_shiftedEnDown;
   std::vector<double>  *electrons_shiftedEnUp;
   std::vector<double>  *electrons_x;
   std::vector<double>  *electrons_y;
   std::vector<double>  *electrons_z;
   std::vector<double>  *photons_chargedHadronIso;
   std::vector<double>  *photons_chargedHadronIsoWithEA;
   std::vector<double>  *photons_energy;
   std::vector<double>  *photons_eta;
   std::vector<double>  *photons_hovere;
   std::vector<double>  *photons_neutralHadronIso;
   std::vector<double>  *photons_neutralHadronIsoWithEA;
   std::vector<double>  *photons_phi;
   std::vector<double>  *photons_photonIso;
   std::vector<double>  *photons_photonIsoWithEA;
   std::vector<double>  *photons_pt;
   std::vector<double>  *photons_puChargedHadronIso;
   std::vector<double>  *photons_r9;
   std::vector<double>  *photons_rhoIso;
   std::vector<double>  *photons_sceta;
   std::vector<double>  *photons_scphi;
   std::vector<double>  *photons_scpreshowerenergy;
   std::vector<double>  *photons_scrawenergy;
   std::vector<double>  *photons_sigmaietaieta;
   std::vector<double>  *jets_CSVInclV2;
   std::vector<double>  *jets_JetProbBJet;
   std::vector<double>  *jets_CMVAV2;
    std::vector<double>        *jets_iCSVCvsL;   
    std::vector<double>        *jets_CCvsLT;   
    std::vector<double>        *jets_CCvsBT;
      std::vector<double>  *jets_chargedEmEnergyFraction;
   std::vector<double>  *jets_energy;
   std::vector<double>  *jets_eta;
   std::vector<double>  *jets_PileupJetId;
   std::vector<double>  *jets_m;
   std::vector<double>  *jets_phi;
   std::vector<double>  *jets_pt;
   std::vector<double>  *jets_shiftedEnDown;
   std::vector<double>  *jets_shiftedEnUp;
   std::vector<double>  *jets_smearedRes;
   std::vector<double>  *jets_smearedResDown;
   std::vector<double>  *jets_smearedResUp;
   std::vector<double>  *jets_vtx3DSig;
   std::vector<double>  *jets_vtx3DVal;
   std::vector<double>  *jets_vtxMass;
   std::vector<double>  *met_phi;
   std::vector<double>  *met_pt;
   std::vector<double>  *met_sumet;
   Double_t        met_muonEn_Px_up;
   Double_t        met_muonEn_Py_up;
   Double_t        met_muonEn_Px_down;
   Double_t        met_muonEn_Py_down;
   Double_t        met_electronEn_Px_up;
   Double_t        met_electronEn_Py_up;
   Double_t        met_electronEn_Px_down;
   Double_t        met_electronEn_Py_down;
   std::vector<double>        *met_unclusteredEn_Px_up;
   std::vector<double>        *met_unclusteredEn_Py_up;
   std::vector<double>        *met_unclusteredEn_Px_down;
   std::vector<double>        *met_unclusteredEn_Py_down;
   std::vector<double>        *met_unclusteredEn_SumEt_down;
   std::vector<double>        *met_unclusteredEn_SumEt_up;
   
   std::vector<double>        *met_jetEn_Px_up;
   std::vector<double>        *met_jetEn_Py_up;
   std::vector<double>        *met_jetEn_Px_down;
   std::vector<double>        *met_jetEn_Py_down;
   std::vector<double>        *met_jetEn_SumEt_up;
   std::vector<double>        *met_jetEn_SumEt_down;
   std::vector<double>        *met_jetRes_Px_up;
   std::vector<double>        *met_jetRes_Py_up;
   std::vector<double>        *met_jetRes_Px_down;
   std::vector<double>        *met_jetRes_Py_down;
   std::vector<double>        *met_jetRes_SumEt_up;
   std::vector<double>        *met_jetRes_SumEt_down;
   
   std::vector<double>  *metNoHF_phi;
   std::vector<double>  *metNoHF_pt;
   std::vector<double>  *metNoHF_sumet;
   std::vector<double>  *metPfMva_phi;
   std::vector<double>  *metPfMva_pt;
   std::vector<double>  *metPfMva_sumet;
   std::vector<double>  *metPuppi_phi;
   std::vector<double>  *metPuppi_pt;
   std::vector<double>  *metPuppi_sumet;
   std::vector<double>  *muon_dxy;
   std::vector<double>  *muon_sigdxy;
   std::vector<double>  *muon_dz;
   std::vector<double>  *muon_energy;
   std::vector<double>  *muon_eta;
   std::vector<double>  *muon_m;
   std::vector<double>  *muon_normchi;
   std::vector<double>  *muon_phi;
   std::vector<double>  *muon_pt;
   std::vector<double>  *muon_relIso03;
   std::vector<double>  *muon_relIso04;
   std::vector<double>  *muon_shiftedEdown;
   std::vector<double>  *muon_shiftedEup;
   std::vector<double>  *muon_x;
   std::vector<double>  *muon_y;
   std::vector<double>  *muon_z;

   std::vector<double>  *slimmedGenJets_energy;
   std::vector<double>  *slimmedGenJets_eta;
   std::vector<double>  *slimmedGenJets_phi;
   std::vector<double>  *slimmedGenJets_pt;
   Double_t        vertex_X;
   Double_t        vertex_Y;
   Double_t        vertex_Z;
   

   std::vector<int>  *electrons_q;
   std::vector<int>  *muon_q;

   
   std::vector<bool>    *gen_isprompt;
   std::vector<bool>    *gen_isdecayedleptonhadron;
   std::vector<bool>    *gen_istaudecayproduct;
   std::vector<bool>    *gen_isprompttaudecayproduct;
   std::vector<bool>    *gen_isdirecthadrondecayproduct;
   std::vector<bool>    *gen_ishardprocess;
   std::vector<bool>    *gen_fromhardprocess;
   std::vector<bool>    *gen_fromhardprocess_beforeFSR;

   std::vector<bool>    *electrons_electronID_loose;
   std::vector<bool>    *electrons_electronID_medium;
   std::vector<bool>    *electrons_electronID_tight;
   std::vector<bool>    *electrons_electronID_veto;
   std::vector<bool>    *electrons_isPF;
   std::vector<bool>    *electrons_isTrigMVAValid;
   std::vector<bool>    *electrons_mcMatched;
   std::vector<bool>    *electrons_passConversionVeto;
   std::vector<bool>    *electrons_electronID_heep;
   std::vector<bool>    *electrons_electronID_mva_medium;
   std::vector<bool>    *electrons_electronID_mva_tight;
   std::vector<bool>    *electrons_electronID_mva_trig_medium;
   std::vector<bool>    *electrons_electronID_mva_trig_tight;
   std::vector<bool>    *jets_isLoose;
   std::vector<bool>    *jets_isTight;
   std::vector<bool>    *jets_isTightLepVetoJetID;
   std::vector<bool>    *muon_isGlobal;
   std::vector<bool>    *muon_isLoose;
   std::vector<bool>    *muon_isMedium;
   std::vector<bool>    *muon_isPF;
   std::vector<bool>    *muon_isSoft;
   std::vector<bool>    *muon_isTight;
   std::vector<bool>    *muon_isTracker;
   std::vector<bool>    *muon_matched;
   std::vector<int>     *electrons_electronID_snu;
   std::vector<bool>    *photons_haspixseed;
   std::vector<bool>    *photons_mcMatched;
   std::vector<bool>    *photons_passelectronveto;
   std::vector<bool>    *photons_photonID_loose;
   std::vector<bool>    *photons_photonID_medium;
   std::vector<bool>    *photons_photonID_mva;
   std::vector<bool>    *photons_photonID_tight;
   std::vector<int>     *jets_hadronFlavour;
   std::vector<int>     *jets_partonFlavour;
   std::vector<int>     *jets_partonPdgId;
   std::vector<int>     *jets_vtxNtracks;
   std::vector<int>     *muon_matchedstations;
   std::vector<int>     *muon_trackerlayers;
   std::vector<int>     *muon_validhits;
   std::vector<int>     *muon_validmuonhits;
   std::vector<int>     *muon_validpixhits;

   // List of branches                                                                                                                                                                                                                                                       
   TBranch        *b_vtrignames;   //!                                                                                                                        
   TBranch        *b_vtrigps;   //!   

   TBranch        *b_gen_isprompt;   //!
   TBranch        *b_gen_isdecayedleptonhadron;   //!
   TBranch        *b_gen_istaudecayproduct;   //!
   TBranch        *b_gen_isprompttaudecayproduct;   //!
   TBranch        *b_gen_isdirecthadrondecayproduct;   //!
   TBranch        *b_gen_ishardprocess;   //!
   TBranch        *b_gen_fromhardprocess;   //!
   TBranch        *b_gen_fromhardprocess_beforeFSR;   //!
   TBranch        *b_ScaleWeights;   //!
   TBranch        *b_PDFWeights;   //!

   TBranch        *b_muon_trigmatch;   //!
   TBranch        *b_electron_trigmatch;   //!

   TBranch        *b_run;   //!                                                                                                                                                                                                                                             
   TBranch        *b_isData;   //!                                                                                                                                                                                                                                             
   TBranch        *b_lumiSilver;   //!                                                                                                                                                                                                                                             
   TBranch        *b_lumiGolden;   //!                                                                                                                                                                                                                                             
   TBranch        *b_CatVersion;   //!                                                                                                                                                                                                                                             
 
   TBranch        *b_lumi;   //!                                                                                                                                                                                                                                             
   TBranch        *b_lumiMaskGold;   //!                                                                                                                                                                                                                                             
   TBranch        *b_lumiMaskSilver;   //!                                                                                                                                                                                                                                             
   TBranch        *b_event;   //!                                                                                                                                                                                                                                            
   TBranch        *b_gen_pt;   //!                                                                                                                                                                                                                                           
   TBranch        *b_gen_eta;   //!                                                                                                                                                                                                                                          
   TBranch        *b_gen_phi;   //!                                                                                                                                                                                                                                          
   TBranch        *b_gen_energy;   //!                                                                                                                                                                                                                                       
   TBranch        *b_gen_status;   //!                                                                                                                                                                                                                                       
   TBranch        *b_gen_pdgid;   //!                                                                                                                                                                                                                                        
   TBranch        *b_gen_motherindex;   //!                                                                                                                                                                                                                                  
   TBranch        *b_HBHENoiseFilter;   //!                                                                                                                                                                                                                                  
   TBranch        *b_csctighthaloFilter;   //!                                                                                                                                                                                                                               
   TBranch        *b_ecalDCTRFilter;   //!                                                                                                                                                                                                                                   
   TBranch        *b_eeBadScFilter;   //!                                                                                                                                                                                                                                    
   TBranch        *b_goodVertices;   //!                                                                                                                                                                                                                                     
   TBranch        *b_GenTTCat;   //!                                                                                                                                                                                                                                         
   TBranch        *b_genWeight_id1;   //!                                                                                                                                                                                                                                    
   TBranch        *b_genWeight_id2;   //!                                                                                                                                                                                                                                    
   TBranch        *b_hlt_2el33;   //!                                                                                                                                                                                                                                        
   TBranch        *b_hlt_el12;   //!                                                                                                                                                                                                                                         
   TBranch        *b_hlt_el16_el12_8;   //!                                                                                                                                                                                                                                  
   TBranch        *b_hlt_el17;   //!                                                                                                                                                                                                                                         
   TBranch        *b_hlt_el17_el12;   //!                                                                                                                                                                                                                                    
   TBranch        *b_hlt_el23_el12;   //!                                                                                                                                                                                                                                    
   TBranch        *b_hlt_el23_el12dz;   //!                                                                                                                                                                                                                                  
   TBranch        *b_hlt_ele27eta2p1;   //!                                                                                                                                                                                                                                  
   TBranch        *b_hlt_mu17_el12;   //!                                                                                                                                                                                                                                    
   TBranch        *b_hlt_mu17_mu8;   //!                                                                                                                                                                                                                                     
   TBranch        *b_hlt_mu17_tkmu8;   //!                                                                                                                                                                                                                                   
   TBranch        *b_hlt_mu8_el17;   //!                                                                                                                                                                                                                                     
   TBranch        *b_nGoodPV;   //!                                                                                                                                                                                                                                          
   TBranch        *b_nPV;   //!                                                                                                                                                                                                                                              
   TBranch        *b_nTrueInteraction;   //!                                                                                                                                                                                                                                 
   TBranch        *b_genWeight;   //!                                                                                                                                                                                                                                        
   TBranch        *b_genWeightQ;   //!                                                                                                                                                                                                                                       
   TBranch        *b_genWeightX1;   //!                                                                                                                                                                                                                                      
   TBranch        *b_genWeightX2;   //!                                                                                                                                                                                                                                      
   TBranch        *b_lheWeight;   //!                                                                                                                                                                                                                                        
   TBranch        *b_puWeightGold;   //!                                                                                                                                                                                                                                         
   TBranch        *b_puWeightGoldDn;   //!                                                                                                                                                                                                                                       
   TBranch        *b_puWeightGoldUp;   //!                                                                                                                                                                                                                                       
   TBranch        *b_puWeightSilver;   //!			     
   TBranch        *b_puWeightSilverDn;   //!		
   TBranch        *b_puWeightSilverUp;   //!		
   TBranch        *b_puWeightGoldDn_xs71000;   //!
   TBranch        *b_puWeightGoldUp_xs71000;   //!
   TBranch        *b_puWeightGold_xs71000;   //!

   TBranch        *b_electrons_absIso03;   //!                                                                                                                                                                                                                               
   TBranch        *b_electrons_absIso04;   //!                                                                                                                                                                                                                               
   TBranch        *b_electrons_chIso03;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_chIso04;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_dxy;   //!                                                                                                                                                                                                                                    
   TBranch        *b_electrons_sigdxy;   //!                                                                                                                                                                                                                                    
   TBranch        *b_electrons_dz;   //!                                                                                                                                                                                                                                     
   TBranch        *b_electrons_energy;   //!                                                                                                                                                                                                                                 
   TBranch        *b_electrons_eta;   //!                                                                                                                                                                                                                                    
   TBranch        *b_electrons_isGsfCtfScPixChargeConsistent;   //!                                                                                                                                                                                                          
   TBranch        *b_electrons_m;   //!                                                                                                                                                                                                                                      
   TBranch        *b_electrons_nhIso03;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_nhIso04;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_phIso03;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_phIso04;   //!                                                                                                                                                                                                                                
   TBranch        *b_electrons_phi;   //!                                                                                                                                                                                                                                    
   TBranch        *b_electrons_pt;   //!                                                                                                                                                                                                                                     
   TBranch        *b_electrons_puChIso03;   //!                                                                                                                                                                                                                              
   TBranch        *b_electrons_puChIso04;   //!                                                                                                                                                                                                                              
   TBranch        *b_electrons_q;   //!                                                                                                                                                                                                                                      
   TBranch        *b_electrons_relIso03;   //!                                                                                                                                                                                                                               
   TBranch        *b_electrons_relIso04;   //!                                                                                                                                                                                                                               
   TBranch        *b_electrons_scEta;   //!                                                                                                                                                                                                                                  
   TBranch        *b_electrons_shiftedEnDown;   //!                                                                                                                                                                                                                          
   TBranch        *b_electrons_shiftedEnUp;   //!                                                                                                                                                                                                                            
   TBranch        *b_electrons_x;   //!                                                                                                                                                                                                                                      
   TBranch        *b_electrons_y;   //!                                                                                                                                                                                                                                      
   TBranch        *b_electrons_z;   //!                                                                                                                                                                                                                                      
   TBranch        *b_jets_CSVInclV2;   //!                                                                                                                                                                                                                                   
   TBranch        *b_jets_JetProbBJet; //!
   TBranch        *b_jets_CMVAV2; //!
   TBranch        *b_jets_iCSVCvsL;   //!
   TBranch        *b_jets_CCvsLT;   //!
   TBranch        *b_jets_CCvsBT;   //!

   TBranch        *b_jets_chargedEmEnergyFraction;   //!

   TBranch        *b_jets_energy;   //!                                                                                                                                                                                                                                      
   TBranch        *b_jets_eta;   //!                                                                                                                                                                                                                                         
   TBranch        *b_jets_PileupJetId;   //!                                                                                                                                                                                                                                      
   TBranch        *b_jets_m;   //!                                                                                                                                                                                                                                           
   TBranch        *b_jets_phi;   //!                                                                                                                                                                                                                                         
   TBranch        *b_jets_pt;   //!                                                                                                                                                                                                                                          
   TBranch        *b_jets_shiftedEnDown;   //!                                                                                                                                                                                                                               
   TBranch        *b_jets_shiftedEnUp;   //!                                                                                                                                                                                                                                 
   TBranch        *b_jets_smearedRes;   //!                                                                                                                                                                                                                                  
   TBranch        *b_jets_smearedResDown;   //!                                                                                                                                                                                                                              
   TBranch        *b_jets_smearedResUp;   //!                                                                                                                                                                                                                                
   TBranch        *b_jets_vtx3DSig;   //!                                                                                                                                                                                                                                    
   TBranch        *b_jets_vtx3DVal;   //!                                                                                                                                                                                                                                    
   TBranch        *b_jets_vtxMass;   //!                                                                                                                                                                                                                                     

   TBranch        *b_met_phi;   //!                                                                                                                                                                                                                                          
   TBranch        *b_met_pt;   //!                                                                                                                                                                                                                                           
   TBranch        *b_met_sumet;   //!                                                                                                                                                                                                                                        
   TBranch        *b_metNoHF_phi;   //!                                                                                                                                                                                                                                      
   TBranch        *b_metNoHF_pt;   //!                                                                                                                                                                                                                                       
   TBranch        *b_metNoHF_sumet;   //!                                                                                                                                                                                                                                    
   TBranch        *b_metPfMva_phi;   //!                                                                                                                                                                                                                                     
   TBranch        *b_metPfMva_pt;   //!                                                                                                                                                                                                                                      
   TBranch        *b_metPfMva_sumet;   //!                                                                                                                                                                                                                                   
   TBranch        *b_metPuppi_phi;   //!                                                                                                                                                                                                                                     
   TBranch        *b_metPuppi_pt;   //!                                                                                                                                                                                                                                      
   TBranch        *b_metPuppi_sumet;   //!                                                                                                                                                                                                                                   
   TBranch        *b_met_muonEn_Px_up;   //!
   TBranch        *b_met_muonEn_Py_up;   //!
   TBranch        *b_met_muonEn_Px_down;   //!
   TBranch        *b_met_muonEn_Py_down;   //!
   TBranch        *b_met_electronEn_Px_up;   //!
   TBranch        *b_met_electronEn_Py_up;   //!
   TBranch        *b_met_electronEn_Px_down;   //!
   TBranch        *b_met_electronEn_Py_down;   //!
   TBranch        *b_met_unclusteredEn_Px_up;   //!
   TBranch        *b_met_unclusteredEn_Py_up;   //!
   TBranch        *b_met_unclusteredEn_Px_down;   //!
   TBranch        *b_met_unclusteredEn_Py_down;   //!
   TBranch        *b_met_unclusteredEn_SumEt_down;   //!
   TBranch        *b_met_unclusteredEn_SumEt_up;   //!
   TBranch        *b_met_jetEn_Px_up;   //!
   TBranch        *b_met_jetEn_Py_up;   //!
   TBranch        *b_met_jetEn_Px_down;   //!
   TBranch        *b_met_jetEn_Py_down;   //!
   TBranch        *b_met_jetEn_SumEt_up;   //!
   TBranch        *b_met_jetEn_SumEt_down;   //!
   TBranch        *b_met_jetRes_Px_up;   //!
   TBranch        *b_met_jetRes_Py_up;   //!
   TBranch        *b_met_jetRes_Px_down;   //!
   TBranch        *b_met_jetRes_Py_down;   //!
   TBranch        *b_met_jetRes_SumEt_up;   //!
   TBranch        *b_met_jetRes_SumEt_down;   //!

   TBranch        *b_muon_dxy;   //!                                                                                                                                                                                                                                         
   TBranch        *b_muon_sigdxy;   //!                                                                                                                                                                                                                                         
   TBranch        *b_muon_dz;   //!                                                                                                                                                                                                                                          
   TBranch        *b_muon_energy;   //!                                                                                                                                                                                                                                      
   TBranch        *b_muon_eta;   //!                                                                                                                                                                                                                                         
   TBranch        *b_muon_m;   //!                                                                                                                                                                                                                                           
   TBranch        *b_muon_normchi;   //!                                                                                                                                                                                                                                     
   TBranch        *b_muon_phi;   //!                                                                                                                                                                                                                                         
   TBranch        *b_muon_pt;   //!                                                                                                                                                                                                                                          
   TBranch        *b_muon_q;   //!                                                                                                                                                                                                                                           
   TBranch        *b_muon_relIso03;   //!                                                                                                                                                                                                                                    
   TBranch        *b_muon_relIso04;   //!                                                                                                                                                                                                                                    
   TBranch        *b_muon_shiftedEdown;   //!                                                                                                                                                                                                                                
   TBranch        *b_muon_shiftedEup;   //!                                                                                                                                                                                                                                  
   TBranch        *b_muon_x;   //!                                                                                                                                                                                                                                           
   TBranch        *b_muon_y;   //!                                                                                                                                                                                                                                           
   TBranch        *b_muon_z;   //!                                                                                                                                                                                                                                           
   TBranch        *b_photons_chargedHadronIso;   //!
   TBranch        *b_photons_chargedHadronIsoWithEA;   //!
   TBranch        *b_photons_energy;   //!
   TBranch        *b_photons_eta;   //!
   TBranch        *b_photons_hovere;   //!
   TBranch        *b_photons_neutralHadronIso;   //!
   TBranch        *b_photons_neutralHadronIsoWithEA;   //!
   TBranch        *b_photons_phi;   //!
   TBranch        *b_photons_photonIso;   //!
   TBranch        *b_photons_photonIsoWithEA;   //!
   TBranch        *b_photons_pt;   //!
   TBranch        *b_photons_puChargedHadronIso;   //!
   TBranch        *b_photons_r9;   //!
   TBranch        *b_photons_rhoIso;   //!
   TBranch        *b_photons_sceta;   //!
   TBranch        *b_photons_scphi;   //!
   TBranch        *b_photons_scpreshowerenergy;   //!
   TBranch        *b_photons_scrawenergy;   //!
   TBranch        *b_photons_sigmaietaieta;   //!

   TBranch        *b_genjet_pt;   //!
   TBranch        *b_genjet_eta;   //!
   TBranch        *b_genjet_phi;   //!
   TBranch        *b_genjet_energy;   //!
   TBranch        *b_genjet_emf;   //!
   TBranch        *b_genjet_hadf;   //!
   TBranch        *b_genjet_pdgid;   //!
   TBranch        *b_slimmedGenJets_energy;   //!                                                                                                                                                                                                                            
   TBranch        *b_slimmedGenJets_eta;   //!                                                                                                                                                                                                                               
   TBranch        *b_slimmedGenJets_phi;   //!                                                                                                                                                                                                                               
   TBranch        *b_slimmedGenJets_pt;   //!    
   TBranch        *b_vertex_X;   //!                                                                                                                                                                                                                                       
   TBranch        *b_vertex_Y;   //!                                                                                                                                                                                                                                       
   TBranch        *b_vertex_Z;   //!                                                                                                                                                                                                                                       
   TBranch        *b_electrons_electronID_loose;   //!                                                                                                                                                                                                                       
   TBranch        *b_electrons_electronID_medium;   //!          
   TBranch        *b_electrons_electronID_tight;   //!                                                                                                                                                                                                                       
   TBranch        *b_electrons_electronID_veto;   //!                                                                                                                                                                                                                        
   TBranch        *b_electrons_isPF;   //!                                                                                                                                                                                                                                   
   TBranch        *b_electrons_isTrigMVAValid;   //!                                                                                                                                                                                                                                   
   TBranch        *b_electrons_mcMatched;   //!                                                                                                                                                                                                                              
   TBranch        *b_electrons_passConversionVeto;   //!                                                                                                                                                                                                                     
   TBranch        *b_electrons_electronID_heep;   //!
   
   TBranch        *b_electrons_electronID_mva_medium;   //!
   TBranch        *b_electrons_electronID_mva_tight;   //!
   TBranch        *b_electrons_electronID_mva_trig_medium;   //!
   TBranch        *b_electrons_electronID_mva_trig_tight;   //!


   TBranch        *b_jets_isLoose;   //!                                                                                                                                                                                                                                     
   TBranch        *b_jets_isTight;   //!                                                                                                                                                                                                                                     
   TBranch        *b_jets_isTightLepVetoJetID;   //!                                                                                                                                                                                                                         
   TBranch        *b_muon_isGlobal;   //!                                                                                                                                                                                                                                    
   TBranch        *b_muon_isLoose;   //!                                                                                                                                                                                                                                     
   TBranch        *b_muon_isMedium;   //!                                                                                                                                                                                                                                    
   TBranch        *b_muon_isPF;   //!                                                                                                                                                                                                                                        
   TBranch        *b_muon_isSoft;   //!                                                                                                                                                                                                                                      
   TBranch        *b_muon_isTight;   //!                                                                                                                                                                                                                                     
   TBranch        *b_muon_isTracker;   //!                                                                                                                                                                                                                                   
   TBranch        *b_muon_matched;   //!                                                                                                                                                                                                                                     
   TBranch        *b_electrons_electronID_snu;   //!                                                                                                                                                                                                                         
   TBranch        *b_photons_haspixseed;   //!
   TBranch        *b_photons_mcMatched;   //!
   TBranch        *b_photons_passelectronveto;   //!
   TBranch        *b_photons_photonID_loose;   //!
   TBranch        *b_photons_photonID_medium;   //!
   TBranch        *b_photons_photonID_mva;   //!
   TBranch        *b_photons_photonID_tight;   //!

   TBranch        *b_jets_hadronFlavour;   //!                                                                                                                                                                                                                               
   TBranch        *b_jets_partonFlavour;   //!                                                                                                                                                                                                                               
   TBranch        *b_jets_partonPdgId;   //!                                                                                                                                                                                                                                 
   TBranch        *b_jets_vtxNtracks;   //!                                                                                                                                                                                                                                  
   TBranch        *b_muon_matchedstations;   //!                                                                                                                                                                                                                             
   TBranch        *b_muon_trackerlayers;   //!                                                                                                                                                                                                                               
   TBranch        *b_muon_validhits;   //!                                                                                                                                                                                                                                   
   TBranch        *b_muon_validmuonhits;   //!                                                                                                                                                                                                                               
   TBranch        *b_muon_validpixhits;   //!     


   TBranch        *b_inputmuons;
   TBranch        *b_inputtrigger;
   TBranch        *b_inputtruth;
   TBranch        *b_inputjets;
   TBranch        *b_inputgenjets;
   TBranch        *b_inputevent;
   TBranch        *b_inputelectrons;
   TBranch        *b_inputphotons;



};

#endif
