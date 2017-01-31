//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 25 04:48:20 2015 by ROOT version 5.34/14
// from TChain ntuple/event/
//////////////////////////////////////////////////////////

#ifndef SkimFlatCat_data_h
#define SkimFlatCat_data_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class SkimFlatCat_data {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
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
   vector<string>  *vtrignames;
   vector<int>     *vtrigps;
   std::vector<std::string>  *muon_trigmatch;
   std::vector<std::string>  *electron_trigmatch;
   Bool_t          IsData;
   Bool_t          Flag_globalTightHalo2016Filter;
   Bool_t          HBHENoiseFilter;
   Bool_t          HBHENoiseIsoFilter;
   Bool_t          CSCTightHaloFilter;
   Bool_t          goodVertices;
   Bool_t          eeBadScFilter;
   Bool_t          EcalDeadCellTriggerPrimitiveFilter;
   Float_t         genWeightQ;
   Float_t         genWeightX1;
   Float_t         genWeightX2;
   Int_t           genWeight_id1;
   Int_t           genWeight_id2;
   Float_t         genWeight;
   Float_t         lheWeight;

   vector<bool>    *gen_isprompt;
   vector<bool>    *gen_isdecayedleptonhadron;
   vector<bool>    *gen_istaudecayproduct;
   vector<bool>    *gen_isprompttaudecayproduct;
   vector<bool>    *gen_isdirecthadrondecayproduct;
   vector<bool>    *gen_ishardprocess;
   vector<bool>    *gen_fromhardprocess;
   vector<bool>    *gen_fromhardprocess_beforeFSR;
   vector<float>   *gen_pt;
   vector<float>   *gen_eta;
   vector<float>   *gen_phi;
   vector<float>   *gen_energy;
   vector<int>     *gen_status;
   vector<int>     *gen_pdgid;
   vector<int>     *gen_motherindex;


   Int_t           nPV;
   Int_t         nGoodPV;
   Int_t           nTrueInteraction;


   vector<double>  *electrons_absIso03;
   vector<double>  *electrons_absIso04;
   vector<double>  *electrons_chIso03;
   vector<double>  *electrons_chIso04;
   vector<double>  *electrons_dxy;
   vector<double>  *electrons_sigdxy;
   vector<double>  *electrons_dz;
   vector<double>  *electrons_energy;
   vector<double>  *electrons_eta;
   vector<double>  *electrons_isGsfCtfScPixChargeConsistent;
   vector<double>  *electrons_m;
   vector<double>  *electrons_nhIso03;
   vector<double>  *electrons_nhIso04;
   vector<double>  *electrons_phIso03;
   vector<double>  *electrons_phIso04;
   vector<double>  *electrons_phi;
   vector<double>  *electrons_pt;
   vector<double>  *electrons_puChIso03;
   vector<double>  *electrons_puChIso04;
   vector<int>  *electrons_q;
   vector<double>  *electrons_relIso03;
   vector<double>  *electrons_relIso04;
   vector<double>  *electrons_scEta;
   vector<double>  *electrons_shiftedEnDown;
   vector<double>  *electrons_shiftedEnUp;
   vector<double>  *electrons_x;
   vector<double>  *electrons_y;
   vector<double>  *electrons_z;

   vector<double>  *jets_CMVAV2;
   vector<double>  *jets_CSVInclV2;
   vector<double>  *jets_JetProbBJet;
   vector<double>  *jets_iCSVCvsL;
   vector<double>  *jets_CCvsLT;
   vector<double>  *jets_CCvsBT;

   vector<double>  *jets_PileupJetId;
   vector<double>  *jets_chargedEmEnergyFraction;
   vector<double>  *jets_energy;
   vector<double>  *jets_eta;
   vector<double>  *jets_m;
   vector<double>  *jets_phi;
   vector<double>  *jets_pt;
   vector<double>  *jets_shiftedEnDown;
   vector<double>  *jets_shiftedEnUp;
   vector<double>  *jets_smearedRes;
   vector<double>  *jets_smearedResDown;
   vector<double>  *jets_smearedResUp;
   vector<double>  *jets_vtx3DSig;
   vector<double>  *jets_vtx3DVal;
   vector<double>  *jets_vtxMass;

   vector<int>     *fatjets_vtxNtracks;
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
   vector<double>  *fatjets_tau1;
   vector<double>  *fatjets_tau2;
   vector<double>  *fatjets_tau3;
   vector<double>  *fatjets_prunedmass;
   vector<double>  *fatjets_softdropmass;
   vector<double>  *fatjets_puppi_tau1;
   vector<double>  *fatjets_puppi_tau2;
   vector<double>  *fatjets_puppi_tau3;
   vector<double>  *fatjets_puppi_pt;
   vector<double>  *fatjets_puppi_eta;
   vector<double>  *fatjets_puppi_phi;
   vector<double>  *fatjets_puppi_m;



   vector<double>  *met_phi;
   vector<double>  *met_pt;
   vector<double>  *met_sumet;
   vector<double>  *metNoHF_phi;
   vector<double>  *metNoHF_pt;
   vector<double>  *metNoHF_sumet;

   vector<double>  *muon_roch_pt;
   vector<double>  *muon_roch_phi;
   vector<double>  *muon_roch_energy;
   vector<double>  *muon_roch_eta;
   vector<double>  *muon_roch_m;
   
   Double_t        met_muonEn_Px_up;
   Double_t        met_muonEn_Py_up;
   Double_t        met_muonEn_Px_down;
   Double_t        met_muonEn_Py_down;
   Double_t        met_electronEn_Px_up;
   Double_t        met_electronEn_Py_up;
   Double_t        met_electronEn_Px_down;
   Double_t        met_electronEn_Py_down;
   vector<double>          *met_unclusteredEn_Px_up;
   vector<double>          *met_unclusteredEn_Py_up;
   vector<double>          *met_unclusteredEn_Px_down;
   vector<double>          *met_unclusteredEn_Py_down;
   vector<double>          *met_unclusteredEn_SumEt_down;
   vector<double>          *met_unclusteredEn_SumEt_up;
   vector<double>          *met_jetEn_Px_up;
   vector<double>          *met_jetEn_Py_up;
   vector<double>          *met_jetEn_Px_down;
   vector<double>          *met_jetEn_Py_down;
   vector<double>          *met_jetEn_SumEt_up;
   vector<double>          *met_jetEn_SumEt_down;
   vector<double>          *met_jetRes_Px_up;
   vector<double>          *met_jetRes_Py_up;
   vector<double>          *met_jetRes_Px_down;
   vector<double>          *met_jetRes_Py_down;
   vector<double>          *met_jetRes_SumEt_up;
   vector<double>          *met_jetRes_SumEt_down;

   vector<double>  *muon_dxy;
   vector<double>  *muon_sigdxy;
   vector<double>  *muon_dz;
   vector<double>  *muon_energy;
   vector<double>  *muon_eta;
   vector<double>  *muon_m;
   vector<double>  *muon_normchi;
   vector<double>  *muon_phi;
   vector<double>  *muon_pt;
   vector<int>  *muon_q;
   vector<double>  *muon_relIso03;
   vector<double>  *muon_relIso04;
   vector<double>  *muon_shiftedEdown;
   vector<double>  *muon_shiftedEup;
   vector<double>  *muon_x;
   vector<double>  *muon_y;
   vector<double>  *muon_z;

   vector<bool>    *electrons_electronID_loose;
   vector<bool>    *electrons_electronID_medium;
   vector<bool>    *electrons_electronID_tight;
   vector<bool>    *electrons_electronID_veto;
   vector<bool>    *electrons_electronID_heep;
   vector<bool>    *electrons_electronID_mva_medium;
   vector<bool>    *electrons_electronID_mva_tight;
   vector<bool>    *electrons_electronID_mva_trig_medium;
   vector<bool>    *electrons_electronID_mva_trig_tight;
   vector<bool>    *electrons_isPF;
   vector<bool>    *electrons_mcMatched;
   vector<bool>    *electrons_passConversionVeto;
   vector<bool>    *electrons_isTrigMVAValid;

   vector<bool>    *jets_isLoose;
   vector<bool>    *jets_isTight;
   vector<bool>    *jets_isTightLepVetoJetID;

   vector<bool>    *muon_isGlobal;
   vector<bool>    *muon_isLoose;
   vector<bool>    *muon_isMedium;
   vector<bool>    *muon_isPF;
   vector<bool>    *muon_isSoft;
   vector<bool>    *muon_isTight;
   vector<bool>    *muon_isTracker;
   vector<bool>    *muon_matched;

   vector<int>     *electrons_electronID_snu;

   vector<int>     *jets_hadronFlavour;
   vector<int>     *jets_partonFlavour;
   vector<int>     *jets_partonPdgId;
   vector<int>     *jets_vtxNtracks;

   vector<int>     *muon_matchedstations;
   vector<int>     *muon_trackerlayers;
   vector<int>     *muon_validhits;
   vector<int>     *muon_validmuonhits;
   vector<int>     *muon_validpixhits;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_vtrignames;   //!
   TBranch        *b_vtrigps;   //!
   TBranch        *b_muon_trigmatch;   //!
   TBranch        *b_electron_trigmatch;   //!
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_energy;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_pdgid;   //!
   TBranch        *b_gen_motherindex;   //!
   TBranch        *b_CatVersion;   //!
   TBranch        *b_IsData;   //!
   TBranch        *b_Flag_globalTightHalo2016Filter;   //!                                                                                                                                                                                                              
   TBranch        *b_HBHENoiseFilter;   //!                                                                                                                                                                                                                             
   TBranch        *b_HBHENoiseIsoFilter;   //!   
   TBranch        *b_CSCTightHaloFilter;   //!                                  
   TBranch        *b_goodVertices;   //!                                        
   TBranch        *b_eeBadScFilter;   //!                                       
   TBranch        *b_EcalDeadCellTriggerPrimitiveFilter;   //!             
   TBranch        *b_goodVertices;   //!
   TBranch        *b_gen_isprompt;   //!
   TBranch        *b_gen_isdecayedleptonhadron;   //!
   TBranch        *b_gen_istaudecayproduct;   //!
   TBranch        *b_gen_isprompttaudecayproduct;   //!
   TBranch        *b_gen_isdirecthadrondecayproduct;   //!
   TBranch        *b_gen_ishardprocess;   //!
   TBranch        *b_gen_fromhardprocess;   //!
   TBranch        *b_gen_fromhardprocess_beforeFSR;   //!
   TBranch        *b_genWeight_id1;   //!
   TBranch        *b_genWeight_id2;   //!
   TBranch        *b_nGoodPV;   //!
   TBranch        *b_nPV;   //!
   TBranch        *b_nTrueInteraction;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_genWeightQ;   //!
   TBranch        *b_genWeightX1;   //!
   TBranch        *b_genWeightX2;   //!
   TBranch        *b_lheWeight;   //!

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
   TBranch        *b_jets_CMVAV2;   //!                                         
   TBranch        *b_jets_CSVInclV2;   //!                                      
   TBranch        *b_jets_JetProbBJet;   //!                                    
   TBranch        *b_jets_iCSVCvsL;   //!
   TBranch        *b_jets_CCvsLT;   //!
   TBranch        *b_jets_CCvsBT;   //!
   TBranch        *b_jets_PileupJetId;   //!                                    
   TBranch        *b_jets_chargedEmEnergyFraction;   //!                        
   TBranch        *b_jets_energy;   //!                                         
   TBranch        *b_jets_eta;   //!                                            
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


   TBranch        *b_fatjets_CSVInclV2;   //!                                                                                                                                          

   TBranch        *b_fatjets_JetProbBJet; //!                                                                                                                                          
   TBranch        *b_fatjets_CMVAV2; //!                                                                                                                                               
   TBranch        *b_fatjets_iCSVCvsL;   //!                                                                                                                                           
   TBranch        *b_fatjets_CCvsLT;   //!                                                                                                                                             
   TBranch        *b_fatjets_CCvsBT;   //!                                                                                                                                             

   TBranch        *b_fatjets_chargedEmEnergyFraction;   //!                                                                                                                            

   TBranch        *b_fatjets_energy;   //!                                                                                                                                             

   TBranch        *b_fatjets_eta;   //!                                                                                                                                                

   TBranch        *b_fatjets_PileupJetId;   //!                                                                                                                                        

   TBranch        *b_fatjets_m;   //!                                                                                                                                                  

   TBranch        *b_fatjets_phi;   //!                                                                                                                                                

   TBranch        *b_fatjets_pt;   //!                                                                                                                                                 

   TBranch        *b_fatjets_shiftedEnDown;   //!                                                                                                                                      

   TBranch        *b_fatjets_shiftedEnUp;   //!                                                                                                                                        

   TBranch        *b_fatjets_smearedRes;

   TBranch        *b_fatjets_smearedResUp;   //!                                                                                                                                      
                                                                                                                                                                                       
                                                                                                                                                                                      

   TBranch        *b_fatjets_smearedResDown;   //!                                                                                                                                     

   TBranch        *b_fatjets_vtx3DSig;   //!                                                                                                                                          
                                                                                                                                                                                       
   TBranch        *b_fatjets_vtx3DVal;   //!                                                                                                                                          
                                                                                                                         

   TBranch        *b_met_phi;   //!
   TBranch        *b_met_pt;   //!
   TBranch        *b_met_sumet;   //!
   TBranch        *b_metNoHF_phi;   //!
   TBranch        *b_metNoHF_pt;   //!
   TBranch        *b_metNoHF_sumet;   //!

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
   TBranch        *b_muon_roch_energy;   //!                                                                                                                                                                                                                                
   TBranch        *b_muon_roch_eta;   //!                                                                                                                                                                                                                                       
   TBranch        *b_muon_roch_phi;   //!                                                                                                                                                                                                                                       
   TBranch        *b_muon_roch_pt;   //!                                                                                                                                                                                                                                        
   TBranch        *b_muon_roch_m;   //!    
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

   TBranch        *b_electrons_electronID_loose;   //!
   TBranch        *b_electrons_electronID_medium;   //!
   TBranch        *b_electrons_electronID_tight;   //!
   TBranch        *b_electrons_electronID_veto;   //!
   TBranch        *b_electrons_electronID_heep;   //!
   TBranch        *b_electrons_electronID_mva_medium;   //!
   TBranch        *b_electrons_electronID_mva_tight;   //!
   TBranch        *b_electrons_electronID_mva_trig_medium;   //!
   TBranch        *b_electrons_electronID_mva_trig_tight;   //!
   
   TBranch        *b_electrons_isPF;   //!
   TBranch        *b_electrons_mcMatched;   //!
   TBranch        *b_electrons_passConversionVeto;   //!
   TBranch        *b_electrons_isTrigMVAValid;   //!                            

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
   TBranch        *b_jets_hadronFlavour;   //!
   TBranch        *b_jets_partonFlavour;   //!
   TBranch        *b_jets_partonPdgId;   //!
   TBranch        *b_jets_vtxNtracks;   //!
   TBranch        *b_muon_matchedstations;   //!
   TBranch        *b_muon_trackerlayers;   //!
   TBranch        *b_muon_validhits;   //!
   TBranch        *b_muon_validmuonhits;   //!
   TBranch        *b_muon_validpixhits;   //!

   SkimFlatCat_data(TTree *tree=0);
   virtual ~SkimFlatCat_data();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     SlimMuons();
   virtual void     SlimElectrons();
   virtual void     SlimJets();
   virtual void     SlimPuppiJets();
};

#endif

#ifdef SkimFlatCat_data_cxx
SkimFlatCat_data::SkimFlatCat_data(TTree *tree) : fChain(0) 
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
      chain->Add("/data2/DATA/cattoflat/skim/slim/WZ_TuneCUETP8M1_13TeV-pythia8/Skim_1.root");

      tree = chain;
#endif // SINGLE_TREE
      
   } 
   Init(tree);
   Loop();//
}

SkimFlatCat_data::~SkimFlatCat_data()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SkimFlatCat_data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SkimFlatCat_data::LoadTree(Long64_t entry)
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

void SkimFlatCat_data::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   vtrignames = 0;
   vtrigps = 0;
   muon_trigmatch=0;
   electron_trigmatch=0;
   gen_pt = 0;
   gen_eta = 0;
   gen_phi = 0;
   gen_energy = 0;
   gen_status = 0;
   gen_pdgid = 0;
   gen_motherindex = 0;
   gen_isprompt = 0;
   gen_isdecayedleptonhadron = 0;
   gen_istaudecayproduct = 0;
   gen_isprompttaudecayproduct = 0;
   gen_isdirecthadrondecayproduct = 0;
   gen_ishardprocess = 0;
   gen_fromhardprocess = 0;
   gen_fromhardprocess_beforeFSR = 0;

   electrons_absIso03 = 0;
   electrons_absIso04 = 0;
   electrons_chIso03 = 0;
   electrons_chIso04 = 0;
   electrons_dxy = 0;
   electrons_sigdxy = 0;
   electrons_dz = 0;
   electrons_energy = 0;
   electrons_eta = 0;
   electrons_isGsfCtfScPixChargeConsistent = 0;
   electrons_m = 0;
   electrons_nhIso03 = 0;
   electrons_nhIso04 = 0;
   electrons_phIso03 = 0;
   electrons_phIso04 = 0;
   electrons_phi = 0;
   electrons_pt = 0;
   electrons_puChIso03 = 0;
   electrons_puChIso04 = 0;
   electrons_q = 0;
   electrons_relIso03 = 0;
   electrons_relIso04 = 0;
   electrons_scEta = 0;
   electrons_shiftedEnDown = 0;
   electrons_shiftedEnUp = 0;
   electrons_x = 0;
   electrons_y = 0;
   electrons_z = 0;
   jets_CMVAV2 = 0;
   jets_CSVInclV2 = 0;
   jets_iCSVCvsL = 0;
   jets_CCvsLT = 0;
   jets_CCvsBT = 0;
   jets_JetProbBJet = 0;
   jets_chargedEmEnergyFraction=0;
   jets_energy = 0;
   jets_eta = 0;
   jets_PileupJetId = 0;
   jets_m = 0;
   jets_phi = 0;
   jets_pt = 0;
   jets_shiftedEnDown = 0;
   jets_shiftedEnUp = 0;
   jets_smearedRes = 0;
   jets_smearedResDown = 0;
   jets_smearedResUp = 0;
   jets_vtx3DSig = 0;
   jets_vtx3DVal = 0;
   jets_vtxMass = 0;
   fatjets_vtxNtracks=0;
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
   fatjets_tau1=0;
   fatjets_tau2=0;
   fatjets_tau3=0;
   fatjets_prunedmass=0;
   fatjets_softdropmass=0;
   fatjets_puppi_tau1=0;
   fatjets_puppi_tau2=0;
   fatjets_puppi_tau3=0;
   fatjets_puppi_pt=0;
   fatjets_puppi_eta=0;
   fatjets_puppi_phi=0;
   fatjets_puppi_m=0;

   met_phi = 0;
   met_pt = 0;
   met_sumet = 0;
   metNoHF_phi = 0;
   metNoHF_pt = 0;
   metNoHF_sumet = 0;
   muon_roch_phi = 0;
   muon_roch_pt = 0;
   muon_roch_energy = 0;
   muon_roch_eta = 0;
   muon_roch_m = 0;
   muon_dxy = 0;
   muon_sigdxy = 0;
   muon_dz = 0;
   muon_energy = 0;
   muon_eta = 0;
   muon_m = 0;
   muon_normchi = 0;
   muon_phi = 0;
   muon_pt = 0;
   muon_q = 0;
   muon_relIso03 = 0;
   muon_relIso04 = 0;
   muon_shiftedEdown = 0;
   muon_shiftedEup = 0;
   muon_x = 0;
   muon_y = 0;
   muon_z = 0;
   electrons_electronID_loose = 0;
   electrons_electronID_medium = 0;
   electrons_electronID_tight = 0;
   electrons_electronID_heep = 0;
   electrons_electronID_veto = 0;
   electrons_electronID_mva_medium = 0;
   electrons_electronID_mva_tight = 0;
   electrons_electronID_mva_trig_medium = 0;
   electrons_electronID_mva_trig_tight = 0;
   electrons_isPF = 0;
   electrons_isTrigMVAValid = 0;
   electrons_mcMatched = 0;
   electrons_passConversionVeto = 0;
   jets_isLoose = 0;
   jets_isTight = 0;
   jets_isTightLepVetoJetID = 0;
   muon_isGlobal = 0;
   muon_isLoose = 0;
   muon_isMedium = 0;
   muon_isPF = 0;
   muon_isSoft = 0;
   muon_isTight = 0;
   muon_isTracker = 0;
   muon_matched = 0;
   electrons_electronID_snu = 0;
   jets_hadronFlavour = 0;
   jets_partonFlavour = 0;
   jets_partonPdgId = 0;
   jets_vtxNtracks = 0;
   muon_matchedstations = 0;
   muon_trackerlayers = 0;
   muon_validhits = 0;
   muon_validmuonhits = 0;
   muon_validpixhits = 0;
   
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("vtrignames", &vtrignames, &b_vtrignames);
   fChain->SetBranchAddress("vtrigps", &vtrigps, &b_vtrigps);
   fChain->SetBranchAddress("muon_trigmatch", &muon_trigmatch, &b_muon_trigmatch);
   fChain->SetBranchAddress("electron_trigmatch", &electron_trigmatch, &b_electron_trigmatch);
   fChain->SetBranchAddress("gen_isprompt", &gen_isprompt, &b_gen_isprompt);
   fChain->SetBranchAddress("gen_isdecayedleptonhadron", &gen_isdecayedleptonhadron, &b_gen_isdecayedleptonhadron);
   fChain->SetBranchAddress("gen_istaudecayproduct", &gen_istaudecayproduct, &b_gen_istaudecayproduct);
   fChain->SetBranchAddress("gen_isprompttaudecayproduct", &gen_isprompttaudecayproduct, &b_gen_isprompttaudecayproduct);
   fChain->SetBranchAddress("gen_isdirecthadrondecayproduct", &gen_isdirecthadrondecayproduct, &b_gen_isdirecthadrondecayproduct);
   fChain->SetBranchAddress("gen_ishardprocess", &gen_ishardprocess, &b_gen_ishardprocess);
   fChain->SetBranchAddress("gen_fromhardprocess", &gen_fromhardprocess, &b_gen_fromhardprocess);
   fChain->SetBranchAddress("gen_fromhardprocess_beforeFSR", &gen_fromhardprocess_beforeFSR, &b_gen_fromhardprocess_beforeFSR);
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_energy", &gen_energy, &b_gen_energy);
   fChain->SetBranchAddress("gen_status", &gen_status, &b_gen_status);
   fChain->SetBranchAddress("gen_pdgid", &gen_pdgid, &b_gen_pdgid);
   fChain->SetBranchAddress("gen_motherindex", &gen_motherindex, &b_gen_motherindex);
   fChain->SetBranchAddress("CatVersion", &CatVersion, &b_CatVersion);
   fChain->SetBranchAddress("IsData", &IsData, &b_IsData);
   fChain->SetBranchAddress("Flag_globalTightHalo2016Filter", &Flag_globalTightHalo2016Filter, &b_Flag_globalTightHalo2016Filter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter, &b_HBHENoiseFilter);
   fChain->SetBranchAddress("HBHENoiseIsoFilter", &HBHENoiseIsoFilter, &b_HBHENoiseIsoFilter);

   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter, &b_CSCTightHaloFilter);
   fChain->SetBranchAddress("goodVertices", &goodVertices, &b_goodVertices);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter, &b_EcalDeadCellTriggerPrimitiveFilter);

   fChain->SetBranchAddress("genWeight_id1", &genWeight_id1, &b_genWeight_id1);
   fChain->SetBranchAddress("genWeight_id2", &genWeight_id2, &b_genWeight_id2);
   fChain->SetBranchAddress("nGoodPV", &nGoodPV, &b_nGoodPV);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nTrueInteraction", &nTrueInteraction, &b_nTrueInteraction);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("genWeightQ", &genWeightQ, &b_genWeightQ);
   fChain->SetBranchAddress("genWeightX1", &genWeightX1, &b_genWeightX1);
   fChain->SetBranchAddress("genWeightX2", &genWeightX2, &b_genWeightX2);
   fChain->SetBranchAddress("lheWeight", &lheWeight, &b_lheWeight);


   fChain->SetBranchAddress("electrons_absIso03", &electrons_absIso03, &b_electrons_absIso03);
   fChain->SetBranchAddress("electrons_absIso04", &electrons_absIso04, &b_electrons_absIso04);
   fChain->SetBranchAddress("electrons_chIso03", &electrons_chIso03, &b_electrons_chIso03);
   fChain->SetBranchAddress("electrons_chIso04", &electrons_chIso04, &b_electrons_chIso04);
   fChain->SetBranchAddress("electrons_dxy", &electrons_dxy, &b_electrons_dxy);
   fChain->SetBranchAddress("electrons_sigdxy", &electrons_sigdxy, &b_electrons_sigdxy);
   fChain->SetBranchAddress("electrons_dz", &electrons_dz, &b_electrons_dz);
   fChain->SetBranchAddress("electrons_energy", &electrons_energy, &b_electrons_energy);
   fChain->SetBranchAddress("electrons_eta", &electrons_eta, &b_electrons_eta);
   fChain->SetBranchAddress("electrons_isGsfCtfScPixChargeConsistent", &electrons_isGsfCtfScPixChargeConsistent, &b_electrons_isGsfCtfScPixChargeConsistent);
   fChain->SetBranchAddress("electrons_m", &electrons_m, &b_electrons_m);
   fChain->SetBranchAddress("electrons_nhIso03", &electrons_nhIso03, &b_electrons_nhIso03);
   fChain->SetBranchAddress("electrons_nhIso04", &electrons_nhIso04, &b_electrons_nhIso04);
   fChain->SetBranchAddress("electrons_phIso03", &electrons_phIso03, &b_electrons_phIso03);
   fChain->SetBranchAddress("electrons_phIso04", &electrons_phIso04, &b_electrons_phIso04);
   fChain->SetBranchAddress("electrons_phi", &electrons_phi, &b_electrons_phi);
   fChain->SetBranchAddress("electrons_pt", &electrons_pt, &b_electrons_pt);
   fChain->SetBranchAddress("electrons_puChIso03", &electrons_puChIso03, &b_electrons_puChIso03);
   fChain->SetBranchAddress("electrons_puChIso04", &electrons_puChIso04, &b_electrons_puChIso04);
   fChain->SetBranchAddress("electrons_q", &electrons_q, &b_electrons_q);
   fChain->SetBranchAddress("electrons_relIso03", &electrons_relIso03, &b_electrons_relIso03);
   fChain->SetBranchAddress("electrons_relIso04", &electrons_relIso04, &b_electrons_relIso04);
   fChain->SetBranchAddress("electrons_scEta", &electrons_scEta, &b_electrons_scEta);
   fChain->SetBranchAddress("electrons_shiftedEnDown", &electrons_shiftedEnDown, &b_electrons_shiftedEnDown);
   fChain->SetBranchAddress("electrons_shiftedEnUp", &electrons_shiftedEnUp, &b_electrons_shiftedEnUp);
   fChain->SetBranchAddress("electrons_x", &electrons_x, &b_electrons_x);
   fChain->SetBranchAddress("electrons_y", &electrons_y, &b_electrons_y);
   fChain->SetBranchAddress("electrons_z", &electrons_z, &b_electrons_z);
   fChain->SetBranchAddress("jets_CMVAV2", &jets_CMVAV2, &b_jets_CMVAV2);
   fChain->SetBranchAddress("jets_CSVInclV2", &jets_CSVInclV2, &b_jets_CSVInclV2);
   fChain->SetBranchAddress("jets_JetProbBJet", &jets_JetProbBJet, &b_jets_JetProbBJet);
   fChain->SetBranchAddress("jets_iCSVCvsL", &jets_iCSVCvsL, &b_jets_iCSVCvsL);
   fChain->SetBranchAddress("jets_CCvsLT", &jets_CCvsLT, &b_jets_CCvsLT);
   fChain->SetBranchAddress("jets_CCvsBT", &jets_CCvsBT, &b_jets_CCvsBT);


   fChain->SetBranchAddress("jets_chargedEmEnergyFraction",&jets_chargedEmEnergyFraction, b_jets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("jets_energy", &jets_energy, &b_jets_energy);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_PileupJetId", &jets_PileupJetId, &b_jets_PileupJetId);
   fChain->SetBranchAddress("jets_m", &jets_m, &b_jets_m);
   fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets_shiftedEnDown", &jets_shiftedEnDown, &b_jets_shiftedEnDown);
   fChain->SetBranchAddress("jets_shiftedEnUp", &jets_shiftedEnUp, &b_jets_shiftedEnUp);
   fChain->SetBranchAddress("jets_smearedRes", &jets_smearedRes, &b_jets_smearedRes);
   fChain->SetBranchAddress("jets_smearedResDown", &jets_smearedResDown, &b_jets_smearedResDown);
   fChain->SetBranchAddress("jets_smearedResUp", &jets_smearedResUp, &b_jets_smearedResUp);
   fChain->SetBranchAddress("jets_vtx3DSig", &jets_vtx3DSig, &b_jets_vtx3DSig);
   fChain->SetBranchAddress("jets_vtx3DVal", &jets_vtx3DVal, &b_jets_vtx3DVal);
   fChain->SetBranchAddress("jets_vtxMass", &jets_vtxMass, &b_jets_vtxMass);


   fChain->SetBranchAddress("fatjets_CSVInclV2", &fatjets_CSVInclV2, b_&fatjets_CSVInclV2);
   fChain->SetBranchAddress("fatjets_CMVAV2", &fatjets_CMVAV2, b_&fatjets_CMVAV2);
   fChain->SetBranchAddress("fatjets_JetProbBJet", &fatjets_JetProbBJet, b_&fatjets_JetProbBJet);
   fChain->SetBranchAddress("fatjets_iCSVCvsL", &fatjets_iCSVCvsL, b_&fatjets_iCSVCvsL);
   fChain->SetBranchAddress("fatjets_CCvsLT", &fatjets_CCvsLT, b_&fatjets_CCvsLT);
   fChain->SetBranchAddress("fatjets_CCvsBT",&fatjets_CCvsBT,b_&fatjets_CCvsBT);
   fChain->SetBranchAddress("fatjets_chargedEmEnergyFraction",&fatjets_chargedEmEnergyFraction,b_&fatjets_chargedEmEnergyFraction);
   fChain->SetBranchAddress("fatjets_energy", &fatjets_energy, b_&fatjets_energy);
   fChain->SetBranchAddress("fatjets_eta",&fatjets_eta,b_&fatjets_eta);
   fChain->SetBranchAddress("fatjets_hadronFlavour",&fatjets_hadronFlavour,b_&fatjets_hadronFlavour);
   fChain->SetBranchAddress("fatjets_isLoose",&fatjets_isLoose,b_&fatjets_isLoose);
   fChain->SetBranchAddress("fatjets_PileupJetId",&fatjets_PileupJetId, b_&fatjets_PileupJetId);
   fChain->SetBranchAddress("fatjets_isTight",&fatjets_isTight,b_&fatjets_isTight);
   fChain->SetBranchAddress("fatjets_isTightLepVetoJetID",&fatjets_isTightLepVetoJetID,b_&fatjets_isTightLepVetoJetID);
   fChain->SetBranchAddress("fatjets_m",&fatjets_m,b_&fatjets_m);
   fChain->SetBranchAddress("fatjets_partonFlavour",&fatjets_partonFlavour,b_&fatjets_partonFlavour);
   fChain->SetBranchAddress("fatjets_partonPdgId",&fatjets_partonPdgId,b_&fatjets_partonPdgId);
   fChain->SetBranchAddress("fatjets_phi",&fatjets_phi,b_&fatjets_phi);
   fChain->SetBranchAddress("fatjets_pt",&fatjets_pt,b_&fatjets_pt);
   fChain->SetBranchAddress("fatjets_shiftedEnDown",&fatjets_shiftedEnDown,b_&fatjets_shiftedEnDown);
   fChain->SetBranchAddress("fatjets_shiftedEnUp",&fatjets_shiftedEnUp,b_&fatjets_shiftedEnUp);
   fChain->SetBranchAddress("fatjets_smearedRes",&fatjets_smearedRes,b_&fatjets_smearedRes);
   fChain->SetBranchAddress("fatjets_smearedResDown",&fatjets_smearedResDown,b_&fatjets_smearedResDown);
   fChain->SetBranchAddress("fatjets_smearedResUp",&fatjets_smearedResUp,b_&fatjets_smearedResUp);
   fChain->SetBranchAddress("fatjets_vtxMass",&fatjets_vtxMass,b_&fatjets_vtxMass);
   fChain->SetBranchAddress("fatjets_vtx3DVal", &fatjets_vtx3DVal, b_&fatjets_vtx3DVal);
   fChain->SetBranchAddress("fatjets_vtx3DSig", &fatjets_vtx3DSig, b_&fatjets_vtx3DSig);
   fChain->SetBranchAddress("fatjets_vtxNtracks", &fatjets_vtxNtracks, b_&fatjets_vtxNtracks);

   fChain->SetBranchAddress("fatjets_tau1",&fatjets_tau1,b_&fatjets_tau1);
   fChain->SetBranchAddress("fatjets_tau2",&fatjets_tau2,b_&fatjets_tau2);
   fChain->SetBranchAddress("fatjets_tau3",&fatjets_tau3,b_&fatjets_tau3);
   fChain->SetBranchAddress("fatjets_prunedmass",&fatjets_prunedmass,b_&fatjets_prunedmass);
   fChain->SetBranchAddress("fatjets_softdropmass",&fatjets_softdropmass,b_&fatjets_softdropmass);
   fChain->SetBranchAddress("fatjets_puppi_tau1",&fatjets_puppi_tau1,b_&fatjets_puppi_tau1);
   fChain->SetBranchAddress("fatjets_puppi_tau2",&fatjets_puppi_tau2,b_&fatjets_puppi_tau2);
   fChain->SetBranchAddress("fatjets_puppi_tau3",&fatjets_puppi_tau3,b_&fatjets_puppi_tau3);
   fChain->SetBranchAddress("fatjets_puppi_eta",&fatjets_puppi_eta,b_&fatjets_puppi_eta);
   fChain->SetBranchAddress("fatjets_puppi_m",&fatjets_puppi_m,b_&fatjets_puppi_m);
   fChain->SetBranchAddress("fatjets_puppi_phi",&fatjets_puppi_phi,b_&fatjets_puppi_phi);
   fChain->SetBranchAddress("fatjets_puppi_pt",&fatjets_puppi_pt,b_&fatjets_puppi_pt);
  

   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("metNoHF_phi", &metNoHF_phi, &b_metNoHF_phi);
   fChain->SetBranchAddress("metNoHF_pt", &metNoHF_pt, &b_metNoHF_pt);
   fChain->SetBranchAddress("metNoHF_sumet", &metNoHF_sumet, &b_metNoHF_sumet);
   fChain->SetBranchAddress("met_muonEn_Px_up", &met_muonEn_Px_up, &b_met_muonEn_Px_up);
   fChain->SetBranchAddress("met_muonEn_Py_up", &met_muonEn_Py_up, &b_met_muonEn_Py_up);
   fChain->SetBranchAddress("met_muonEn_Px_down", &met_muonEn_Px_down, &b_met_muonEn_Px_down);
   fChain->SetBranchAddress("met_muonEn_Py_down", &met_muonEn_Py_down, &b_met_muonEn_Py_down);
   fChain->SetBranchAddress("met_electronEn_Px_up", &met_electronEn_Px_up, &b_met_electronEn_Px_up);
   fChain->SetBranchAddress("met_electronEn_Py_up", &met_electronEn_Py_up, &b_met_electronEn_Py_up);
   fChain->SetBranchAddress("met_electronEn_Px_down", &met_electronEn_Px_down, &b_met_electronEn_Px_down);
   fChain->SetBranchAddress("met_electronEn_Py_down", &met_electronEn_Py_down, &b_met_electronEn_Py_down);
   fChain->SetBranchAddress("met_unclusteredEn_Px_up", &met_unclusteredEn_Px_up, &b_met_unclusteredEn_Px_up);
   fChain->SetBranchAddress("met_unclusteredEn_Py_up", &met_unclusteredEn_Py_up, &b_met_unclusteredEn_Py_up);
   fChain->SetBranchAddress("met_unclusteredEn_Px_down", &met_unclusteredEn_Px_down, &b_met_unclusteredEn_Px_down);
   fChain->SetBranchAddress("met_unclusteredEn_Py_down", &met_unclusteredEn_Py_down, &b_met_unclusteredEn_Py_down);
   fChain->SetBranchAddress("met_unclusteredEn_SumEt_down", &met_unclusteredEn_SumEt_down, &b_met_unclusteredEn_SumEt_down);
   fChain->SetBranchAddress("met_unclusteredEn_SumEt_up", &met_unclusteredEn_SumEt_up, &b_met_unclusteredEn_SumEt_up);
   fChain->SetBranchAddress("met_jetEn_Px_up", &met_jetEn_Px_up, &b_met_jetEn_Px_up);
   fChain->SetBranchAddress("met_jetEn_Py_up", &met_jetEn_Py_up, &b_met_jetEn_Py_up);
   fChain->SetBranchAddress("met_jetEn_Px_down", &met_jetEn_Px_down, &b_met_jetEn_Px_down);
   fChain->SetBranchAddress("met_jetEn_Py_down", &met_jetEn_Py_down, &b_met_jetEn_Py_down);
   fChain->SetBranchAddress("met_jetEn_SumEt_up", &met_jetEn_SumEt_up, &b_met_jetEn_SumEt_up);
   fChain->SetBranchAddress("met_jetEn_SumEt_down", &met_jetEn_SumEt_down, &b_met_jetEn_SumEt_down);
   fChain->SetBranchAddress("met_jetRes_Px_up", &met_jetRes_Px_up, &b_met_jetRes_Px_up);
   fChain->SetBranchAddress("met_jetRes_Py_up", &met_jetRes_Py_up, &b_met_jetRes_Py_up);
   fChain->SetBranchAddress("met_jetRes_Px_down", &met_jetRes_Px_down, &b_met_jetRes_Px_down);
   fChain->SetBranchAddress("met_jetRes_Py_down", &met_jetRes_Py_down, &b_met_jetRes_Py_down);
   fChain->SetBranchAddress("met_jetRes_SumEt_up", &met_jetRes_SumEt_up, &b_met_jetRes_SumEt_up);
   fChain->SetBranchAddress("met_jetRes_SumEt_down", &met_jetRes_SumEt_down, &b_met_jetRes_SumEt_down);

   fChain->SetBranchAddress("muon_roch_energy", &muon_roch_energy, &b_muon_roch_energy);
   fChain->SetBranchAddress("muon_roch_eta", &muon_roch_eta, &b_muon_roch_eta);
   fChain->SetBranchAddress("muon_roch_m", &muon_roch_m, &b_muon_roch_m);
   fChain->SetBranchAddress("muon_roch_phi", &muon_roch_phi, &b_muon_roch_phi);
   fChain->SetBranchAddress("muon_roch_pt", &muon_roch_pt, &b_muon_roch_pt);
   fChain->SetBranchAddress("muon_dxy", &muon_dxy, &b_muon_dxy);
   fChain->SetBranchAddress("muon_sigdxy", &muon_sigdxy, &b_muon_sigdxy);
   fChain->SetBranchAddress("muon_dz", &muon_dz, &b_muon_dz);
   fChain->SetBranchAddress("muon_energy", &muon_energy, &b_muon_energy);
   fChain->SetBranchAddress("muon_eta", &muon_eta, &b_muon_eta);
   fChain->SetBranchAddress("muon_m", &muon_m, &b_muon_m);
   fChain->SetBranchAddress("muon_normchi", &muon_normchi, &b_muon_normchi);
   fChain->SetBranchAddress("muon_phi", &muon_phi, &b_muon_phi);
   fChain->SetBranchAddress("muon_pt", &muon_pt, &b_muon_pt);
   fChain->SetBranchAddress("muon_q", &muon_q, &b_muon_q);
   fChain->SetBranchAddress("muon_relIso03", &muon_relIso03, &b_muon_relIso03);
   fChain->SetBranchAddress("muon_relIso04", &muon_relIso04, &b_muon_relIso04);
   fChain->SetBranchAddress("muon_shiftedEdown", &muon_shiftedEdown, &b_muon_shiftedEdown);
   fChain->SetBranchAddress("muon_shiftedEup", &muon_shiftedEup, &b_muon_shiftedEup);
   fChain->SetBranchAddress("muon_x", &muon_x, &b_muon_x);
   fChain->SetBranchAddress("muon_y", &muon_y, &b_muon_y);
   fChain->SetBranchAddress("muon_z", &muon_z, &b_muon_z);

   fChain->SetBranchAddress("electrons_electronID_loose", &electrons_electronID_loose, &b_electrons_electronID_loose);
   fChain->SetBranchAddress("electrons_electronID_medium", &electrons_electronID_medium, &b_electrons_electronID_medium);
   fChain->SetBranchAddress("electrons_electronID_tight", &electrons_electronID_tight, &b_electrons_electronID_tight);
   fChain->SetBranchAddress("electrons_electronID_veto", &electrons_electronID_veto, &b_electrons_electronID_veto);
   fChain->SetBranchAddress("electrons_electronID_heep", &electrons_electronID_heep, &b_electrons_electronID_heep);
   fChain->SetBranchAddress("electrons_electronID_mva_medium", &electrons_electronID_mva_medium, &b_electrons_electronID_mva_medium);
   fChain->SetBranchAddress("electrons_electronID_mva_tight", &electrons_electronID_mva_tight, &b_electrons_electronID_mva_tight);
   fChain->SetBranchAddress("electrons_electronID_mva_trig_medium", &electrons_electronID_mva_trig_medium, &b_electrons_electronID_mva_trig_medium);
   fChain->SetBranchAddress("electrons_electronID_mva_trig_tight", &electrons_electronID_mva_trig_tight, &b_electrons_electronID_mva_trig_tight);
   fChain->SetBranchAddress("electrons_isPF", &electrons_isPF, &b_electrons_isPF);
   fChain->SetBranchAddress("electrons_isTrigMVAValid", &electrons_isTrigMVAValid, &b_electrons_isTrigMVAValid);
   fChain->SetBranchAddress("electrons_mcMatched", &electrons_mcMatched, &b_electrons_mcMatched);
   fChain->SetBranchAddress("electrons_passConversionVeto", &electrons_passConversionVeto, &b_electrons_passConversionVeto);
   fChain->SetBranchAddress("jets_isLoose", &jets_isLoose, &b_jets_isLoose);
   fChain->SetBranchAddress("jets_isTight", &jets_isTight, &b_jets_isTight);
   fChain->SetBranchAddress("jets_isTightLepVetoJetID", &jets_isTightLepVetoJetID, &b_jets_isTightLepVetoJetID);
   fChain->SetBranchAddress("muon_isGlobal", &muon_isGlobal, &b_muon_isGlobal);
   fChain->SetBranchAddress("muon_isLoose", &muon_isLoose, &b_muon_isLoose);
   fChain->SetBranchAddress("muon_isMedium", &muon_isMedium, &b_muon_isMedium);
   fChain->SetBranchAddress("muon_isPF", &muon_isPF, &b_muon_isPF);
   fChain->SetBranchAddress("muon_isSoft", &muon_isSoft, &b_muon_isSoft);
   fChain->SetBranchAddress("muon_isTight", &muon_isTight, &b_muon_isTight);
   fChain->SetBranchAddress("muon_isTracker", &muon_isTracker, &b_muon_isTracker);
   fChain->SetBranchAddress("muon_matched", &muon_matched, &b_muon_matched);
   fChain->SetBranchAddress("electrons_electronID_snu", &electrons_electronID_snu, &b_electrons_electronID_snu);
   fChain->SetBranchAddress("jets_hadronFlavour", &jets_hadronFlavour, &b_jets_hadronFlavour);
   fChain->SetBranchAddress("jets_partonFlavour", &jets_partonFlavour, &b_jets_partonFlavour);
   fChain->SetBranchAddress("jets_partonPdgId", &jets_partonPdgId, &b_jets_partonPdgId);
   fChain->SetBranchAddress("jets_vtxNtracks", &jets_vtxNtracks, &b_jets_vtxNtracks);
   fChain->SetBranchAddress("muon_matchedstations", &muon_matchedstations, &b_muon_matchedstations);
   fChain->SetBranchAddress("muon_trackerlayers", &muon_trackerlayers, &b_muon_trackerlayers);
   fChain->SetBranchAddress("muon_validhits", &muon_validhits, &b_muon_validhits);
   fChain->SetBranchAddress("muon_validmuonhits", &muon_validmuonhits, &b_muon_validmuonhits);
   fChain->SetBranchAddress("muon_validpixhits", &muon_validpixhits, &b_muon_validpixhits);
   Notify();
}

Bool_t SkimFlatCat_data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SkimFlatCat_data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void SkimFlatCat_data::SlimElectrons()
{
  std::vector<int > remove_obj;
  for(unsigned int im =0; im < electrons_pt->size(); im++){
    bool rem =false;
    if( electrons_pt->at(im) < 10) rem = true;
    if( fabs(electrons_eta->at(im)) > 2.8 )rem = true;
    if(rem) remove_obj.push_back(im);
  }

  int nrm = 0;
  for(unsigned int im =0; im < remove_obj.size(); im++){
    electrons_absIso03->erase(electrons_absIso03->begin() + remove_obj.at(im) - nrm);
    electrons_absIso04->erase(electrons_absIso04->begin() + remove_obj.at(im) - nrm);
    electrons_chIso03->erase(electrons_chIso03->begin() + remove_obj.at(im) - nrm);
    electrons_chIso04->erase(electrons_chIso04->begin() + remove_obj.at(im) - nrm);
    electrons_dxy->erase(electrons_dxy->begin() + remove_obj.at(im) - nrm);
    electrons_sigdxy->erase(electrons_sigdxy->begin() + remove_obj.at(im) - nrm);
    electrons_dz->erase(electrons_dz->begin() + remove_obj.at(im) - nrm);
    electrons_energy->erase(electrons_energy->begin() + remove_obj.at(im) - nrm);
    electrons_eta->erase(electrons_eta->begin() + remove_obj.at(im) - nrm);
    electrons_isGsfCtfScPixChargeConsistent->erase(electrons_isGsfCtfScPixChargeConsistent->begin() + remove_obj.at(im) - nrm);
    electrons_m->erase(electrons_m->begin() + remove_obj.at(im) - nrm);
    electrons_nhIso03->erase(electrons_nhIso03->begin() + remove_obj.at(im) - nrm);
    electrons_nhIso04->erase(electrons_nhIso04->begin() + remove_obj.at(im) - nrm);
    electrons_phIso03->erase(electrons_phIso03->begin() + remove_obj.at(im) - nrm);
    electrons_phIso04->erase(electrons_phIso04->begin() + remove_obj.at(im) - nrm);
    electrons_phi->erase(electrons_phi->begin() + remove_obj.at(im) - nrm);
    electrons_pt->erase(electrons_pt->begin() + remove_obj.at(im) - nrm);
    electrons_puChIso03->erase(electrons_puChIso03->begin() + remove_obj.at(im) - nrm);
    electrons_puChIso04->erase(electrons_puChIso04->begin() + remove_obj.at(im) - nrm);
    electrons_q->erase(electrons_q->begin() + remove_obj.at(im) - nrm);
    electrons_relIso03->erase(electrons_relIso03->begin() + remove_obj.at(im) - nrm);
    electrons_relIso04->erase(electrons_relIso04->begin() + remove_obj.at(im) - nrm);
    electrons_scEta->erase(electrons_scEta->begin() + remove_obj.at(im) - nrm);
    electrons_shiftedEnDown->erase(electrons_shiftedEnDown->begin() + remove_obj.at(im) - nrm);
    electrons_shiftedEnUp->erase(electrons_shiftedEnUp->begin() + remove_obj.at(im) - nrm);
    electrons_x->erase(electrons_x->begin() + remove_obj.at(im) - nrm);
    electrons_y->erase(electrons_y->begin() + remove_obj.at(im) - nrm);
    electrons_z->erase(electrons_z->begin() + remove_obj.at(im) - nrm);
    electrons_electronID_snu->erase(electrons_electronID_snu->begin() + remove_obj.at(im) - nrm);

    nrm++;
  }
  SlimBool( electrons_electronID_loose, remove_obj);
  SlimBool( electrons_electronID_medium, remove_obj);
  SlimBool( electrons_electronID_tight, remove_obj);
  SlimBool( electrons_electronID_veto, remove_obj);
  SlimBool( electrons_isPF, remove_obj);
  SlimBool( electrons_mcMatched, remove_obj);
  SlimBool( electrons_passConversionVeto, remove_obj);
  SlimBool( electrons_electronID_heep, remove_obj);
  SlimBool( electrons_electronID_mva_medium, remove_obj);
  SlimBool( electrons_electronID_mva_tight, remove_obj);
  SlimBool( electrons_electronID_mva_trig_medium, remove_obj);
  SlimBool( electrons_electronID_mva_trig_tight, remove_obj);
  SlimBool( electrons_isTrigMVAValid, remove_obj);
}

void SkimFlatCat_data::SlimMuons()
{
  std::vector<int > remove_obj;
  for(unsigned int im =0; im < muon_pt->size(); im++){
    bool rem =false;
    if( muon_pt->at(im) < 10) rem = true;
    if( fabs(muon_eta->at(im)) > 2.8 )rem = true;
    if(rem) remove_obj.push_back(im);
  }
  
  int nrm = 0;
  for(unsigned int im =0; im < remove_obj.size(); im++){
    muon_roch_pt->erase(muon_roch_pt->begin() + remove_obj.at(im) - nrm);
    muon_roch_eta->erase(muon_roch_eta->begin() + remove_obj.at(im) - nrm);
    muon_roch_energy->erase(muon_roch_energy->begin() + remove_obj.at(im) - nrm);
    muon_roch_m->erase(muon_roch_m->begin() + remove_obj.at(im) - nrm);
    muon_roch_phi->erase(muon_roch_phi->begin() + remove_obj.at(im) - nrm);

    muon_pt->erase(muon_pt->begin() + remove_obj.at(im) - nrm);
    muon_eta->erase(muon_eta->begin() + remove_obj.at(im) - nrm);
    muon_dxy->erase(muon_dxy->begin() + remove_obj.at(im) - nrm);
    muon_sigdxy->erase(muon_sigdxy->begin() + remove_obj.at(im) - nrm);
    muon_dz->erase(muon_dz->begin() + remove_obj.at(im) - nrm);
    muon_energy->erase(muon_energy->begin() + remove_obj.at(im) - nrm);
    muon_m->erase(muon_m->begin() + remove_obj.at(im) - nrm);
    muon_normchi->erase(muon_normchi->begin() + remove_obj.at(im) - nrm);
    muon_phi->erase(muon_phi->begin() + remove_obj.at(im) - nrm);
    muon_q->erase(muon_q->begin() + remove_obj.at(im) - nrm);
    muon_relIso03->erase(muon_relIso03->begin() + remove_obj.at(im) - nrm);
    muon_relIso04->erase(muon_relIso04->begin() + remove_obj.at(im) - nrm);
    muon_shiftedEdown->erase(muon_shiftedEdown->begin() + remove_obj.at(im) - nrm);
    muon_shiftedEup->erase(muon_shiftedEup->begin() + remove_obj.at(im) - nrm);
    muon_x->erase(muon_x->begin() + remove_obj.at(im) - nrm);
    muon_y->erase(muon_y->begin() + remove_obj.at(im) - nrm);
    muon_z->erase(muon_z->begin() + remove_obj.at(im) - nrm);
    muon_matchedstations->erase(muon_matchedstations->begin() + remove_obj.at(im) - nrm);
    muon_trackerlayers->erase(muon_trackerlayers->begin() + remove_obj.at(im) - nrm);
    muon_validhits->erase(muon_validhits->begin() + remove_obj.at(im) - nrm);
    muon_validmuonhits->erase(muon_validmuonhits->begin() + remove_obj.at(im) - nrm);
    muon_validpixhits->erase(muon_validpixhits->begin() + remove_obj.at(im) - nrm);
    
    nrm++;
  }
  SlimBool( muon_isGlobal, remove_obj);
  SlimBool( muon_isLoose,remove_obj);
  SlimBool( muon_isMedium,remove_obj);
  SlimBool( muon_isPF,remove_obj);
  SlimBool( muon_isSoft,remove_obj);
  SlimBool( muon_isTight,remove_obj);
  SlimBool( muon_isTracker,remove_obj);
  SlimBool( muon_matched,remove_obj);
}
void  SkimFlatCat_data::SlimBool(std::vector<bool>* vbool, std::vector<int> torm){
  vector<bool> test;
  for(unsigned int i =0 ; i < vbool->size(); i++){
    test.push_back(vbool->at(i));
  }
  
  vbool->clear();
  bool keep = true;
  for(unsigned int i =0 ; i <test.size(); i++){
    for(unsigned int k = 0; k < torm.size(); k++){
      if(i == torm.at(k)) keep = false;
    }
    if(keep){
      vbool->push_back(test.at(i));
    }
  }
  
}

void SkimFlatCat_data::SlimJets()
{
  std::vector<int > remove_obj;
  for(unsigned int im =0; im < jets_pt->size(); im++){
    bool rem =false;
    if( jets_pt->at(im) < 20) rem = true;
    if(rem) remove_obj.push_back(im);
  }
  
  int nrm = 0;
  for(unsigned int im =0; im < remove_obj.size(); im++){
    jets_chargedEmEnergyFraction->erase(jets_chargedEmEnergyFraction->begin() + remove_obj.at(im) - nrm);

    jets_CMVAV2->erase(jets_CMVAV2->begin() + remove_obj.at(im) - nrm);
    jets_CSVInclV2->erase(jets_CSVInclV2->begin() + remove_obj.at(im) - nrm);
    jets_JetProbBJet->erase(jets_JetProbBJet->begin() + remove_obj.at(im) - nrm);

    jets_energy->erase(jets_energy->begin() + remove_obj.at(im) - nrm);
    jets_eta->erase(jets_eta->begin() + remove_obj.at(im) - nrm);
    jets_PileupJetId->erase(jets_PileupJetId->begin() + remove_obj.at(im) - nrm);
    jets_m->erase(jets_m->begin() + remove_obj.at(im) - nrm);
    jets_phi->erase(jets_phi->begin() + remove_obj.at(im) - nrm);
    jets_pt->erase(jets_pt->begin() + remove_obj.at(im) - nrm);
    jets_shiftedEnDown->erase(jets_shiftedEnDown->begin() + remove_obj.at(im) - nrm);
    jets_shiftedEnUp->erase(jets_shiftedEnUp->begin() + remove_obj.at(im) - nrm);
    jets_smearedRes->erase(jets_smearedRes->begin() + remove_obj.at(im) - nrm);
    jets_smearedResDown->erase(jets_smearedResDown->begin() + remove_obj.at(im) - nrm);
    jets_smearedResUp->erase(jets_smearedResUp->begin() + remove_obj.at(im) - nrm);
    jets_vtx3DSig->erase(jets_vtx3DSig->begin() + remove_obj.at(im) - nrm);
    jets_vtxMass->erase(jets_vtxMass->begin() + remove_obj.at(im) - nrm);
    jets_vtx3DVal->erase(jets_vtx3DVal->begin() + remove_obj.at(im) - nrm);
    jets_hadronFlavour->erase(jets_hadronFlavour->begin() + remove_obj.at(im) - nrm);
    jets_partonFlavour->erase(jets_partonFlavour->begin() + remove_obj.at(im) - nrm);
    jets_partonPdgId->erase(jets_partonPdgId->begin() + remove_obj.at(im) - nrm);
    jets_vtxNtracks->erase(jets_vtxNtracks->begin() + remove_obj.at(im) - nrm);

    nrm++;
  }

  SlimBool( jets_isLoose, remove_obj);
  SlimBool( jets_isTight, remove_obj);
  SlimBool( jets_isTightLepVetoJetID, remove_obj);

}

void SkimFlatCat_data::SlimPuppiJets()
{
  
  
}


Int_t SkimFlatCat_data::Cut(Long64_t entry)
{

  bool pass_lep_pt = false;
  
  for(unsigned int im=0; im < muon_pt->size(); im++){
    if(muon_pt->at(im) > 10) pass_lep_pt = true;
  }
  for(unsigned int im=0; im < electrons_pt->size(); im++){
    if(electrons_pt->at(im) > 10) pass_lep_pt = true;
  }
  if(pass_lep_pt) return 1;
  
  return -1;
}
#endif // #ifdef SkimFlatCat_data_cxx
