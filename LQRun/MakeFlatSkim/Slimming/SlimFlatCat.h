//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 25 04:48:20 2015 by ROOT version 5.34/14
// from TChain ntuple/event/
//////////////////////////////////////////////////////////

#ifndef SlimFlatCat_h
#define SlimFlatCat_h

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

class SlimFlatCat {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           lumi;
   Int_t           event;
   vector<string>  *vtrignames;
   vector<int>     *vtrigps;
   vector<float>   *gen_pt;
   vector<float>   *gen_eta;
   vector<float>   *gen_phi;
   vector<float>   *gen_energy;
   vector<int>     *gen_status;
   vector<int>     *gen_pdgid;
   vector<int>     *gen_motherindex;
   Bool_t          HNHENoiseFilter;
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
   Float_t         puWeight;
   Float_t         puWeightDn;
   Float_t         puWeightUp;
   vector<float>   *pdfWeight;
   vector<double>  *electrons_absIso03;
   vector<double>  *electrons_absIso04;
   vector<double>  *electrons_chIso03;
   vector<double>  *electrons_chIso04;
   vector<double>  *electrons_dxy;
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
   vector<double>  *electrons_q;
   vector<double>  *electrons_relIso03;
   vector<double>  *electrons_relIso04;
   vector<double>  *electrons_scEta;
   vector<double>  *electrons_shiftedEnDown;
   vector<double>  *electrons_shiftedEnUp;
   vector<double>  *electrons_x;
   vector<double>  *electrons_y;
   vector<double>  *electrons_z;
   vector<double>  *jets_CVSInclV2;
   vector<double>  *jets_energy;
   vector<double>  *jets_eta;
   vector<double>  *jets_isPFId;
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
   vector<double>  *jetsPuppi_CVSInclV2;
   vector<double>  *jetsPuppi_eta;
   vector<double>  *jetsPuppi_hadronFlavour;
   vector<double>  *jetsPuppi_m;
   vector<double>  *jetsPuppi_partonFlavour;
   vector<double>  *jetsPuppi_phi;
   vector<double>  *jetsPuppi_pt;
   vector<double>  *jetsPuppi_vtx3DSig;
   vector<double>  *jetsPuppi_vtx3DVal;
   vector<double>  *jetsPuppi_vtxMass;
   vector<double>  *met_phi;
   vector<double>  *met_pt;
   vector<double>  *met_sumet;
   vector<double>  *metNoHF_phi;
   vector<double>  *metNoHF_pt;
   vector<double>  *metNoHF_sumet;
   vector<double>  *metPfMva_phi;
   vector<double>  *metPfMva_pt;
   vector<double>  *metPfMva_sumet;
   vector<double>  *metPuppi_phi;
   vector<double>  *metPuppi_pt;
   vector<double>  *metPuppi_sumet;
   vector<double>  *muon_dxy;
   vector<double>  *muon_dz;
   vector<double>  *muon_energy;
   vector<double>  *muon_eta;
   vector<double>  *muon_m;
   vector<double>  *muon_normchi;
   vector<double>  *muon_phi;
   vector<double>  *muon_pt;
   vector<double>  *muon_q;
   vector<double>  *muon_relIso03;
   vector<double>  *muon_relIso04;
   vector<double>  *muon_shiftedEdown;
   vector<double>  *muon_shiftedEup;
   vector<double>  *muon_x;
   vector<double>  *muon_y;
   vector<double>  *muon_z;
   vector<double>  *slimmedGenJets_energy;
   vector<double>  *slimmedGenJets_eta;
   vector<double>  *slimmedGenJets_m;
   vector<double>  *slimmedGenJets_phi;
   vector<double>  *slimmedGenJets_pt;
   vector<double>  *vertices_ndof;
   vector<double>  *vertices_x;
   vector<double>  *vertices_y;
   vector<double>  *vertices_z;
   vector<bool>    *electrons_electronID_loose;
   vector<bool>    *electrons_electronID_medium;
   vector<bool>    *electrons_electronID_tight;
   vector<bool>    *electrons_electronID_veto;
   vector<bool>    *electrons_isPF;
   vector<bool>    *electrons_mcMatched;
   vector<bool>    *electrons_passConversionVeto;
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
   TBranch        *b_gen_pt;   //!
   TBranch        *b_gen_eta;   //!
   TBranch        *b_gen_phi;   //!
   TBranch        *b_gen_energy;   //!
   TBranch        *b_gen_status;   //!
   TBranch        *b_gen_pdgid;   //!
   TBranch        *b_gen_motherindex;   //!
   TBranch        *b_HNHENoiseFilter;   //!
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
   TBranch        *b_puWeight;   //!
   TBranch        *b_puWeightDn;   //!
   TBranch        *b_puWeightUp;   //!
   TBranch        *b_pdfWeight;   //!
   TBranch        *b_electrons_absIso03;   //!
   TBranch        *b_electrons_absIso04;   //!
   TBranch        *b_electrons_chIso03;   //!
   TBranch        *b_electrons_chIso04;   //!
   TBranch        *b_electrons_dxy;   //!
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
   TBranch        *b_jets_CVSInclV2;   //!
   TBranch        *b_jets_energy;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_isPFId;   //!
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
   TBranch        *b_jetsPuppi_CVSInclV2;   //!
   TBranch        *b_jetsPuppi_eta;   //!
   TBranch        *b_jetsPuppi_hadronFlavour;   //!
   TBranch        *b_jetsPuppi_m;   //!
   TBranch        *b_jetsPuppi_partonFlavour;   //!
   TBranch        *b_jetsPuppi_phi;   //!
   TBranch        *b_jetsPuppi_pt;   //!
   TBranch        *b_jetsPuppi_vtx3DSig;   //!
   TBranch        *b_jetsPuppi_vtx3DVal;   //!
   TBranch        *b_jetsPuppi_vtxMass;   //!
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
   TBranch        *b_muon_dxy;   //!
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
   TBranch        *b_slimmedGenJets_energy;   //!
   TBranch        *b_slimmedGenJets_eta;   //!
   TBranch        *b_slimmedGenJets_m;   //!
   TBranch        *b_slimmedGenJets_phi;   //!
   TBranch        *b_slimmedGenJets_pt;   //!
   TBranch        *b_vertices_ndof;   //!
   TBranch        *b_vertices_x;   //!
   TBranch        *b_vertices_y;   //!
   TBranch        *b_vertices_z;   //!
   TBranch        *b_electrons_electronID_loose;   //!
   TBranch        *b_electrons_electronID_medium;   //!
   TBranch        *b_electrons_electronID_tight;   //!
   TBranch        *b_electrons_electronID_veto;   //!
   TBranch        *b_electrons_isPF;   //!
   TBranch        *b_electrons_mcMatched;   //!
   TBranch        *b_electrons_passConversionVeto;   //!
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

   SlimFlatCat(TTree *tree=0);
   virtual ~SlimFlatCat();
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

#ifdef SlimFlatCat_cxx
SlimFlatCat::SlimFlatCat(TTree *tree) : fChain(0) 
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
      chain->Add("/data2/DATA/cattoflat/MC/DoubleMuon/ntuple1.root/ntuple/event");

      tree = chain;
#endif // SINGLE_TREE
      
   } 
   Init(tree);
   Loop();//
}

SlimFlatCat::~SlimFlatCat()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SlimFlatCat::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SlimFlatCat::LoadTree(Long64_t entry)
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

void SlimFlatCat::Init(TTree *tree)
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
   gen_pt = 0;
   gen_eta = 0;
   gen_phi = 0;
   gen_energy = 0;
   gen_status = 0;
   gen_pdgid = 0;
   gen_motherindex = 0;
   pdfWeight = 0;
   electrons_absIso03 = 0;
   electrons_absIso04 = 0;
   electrons_chIso03 = 0;
   electrons_chIso04 = 0;
   electrons_dxy = 0;
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
   jets_CVSInclV2 = 0;
   jets_energy = 0;
   jets_eta = 0;
   jets_isPFId = 0;
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
   jetsPuppi_CVSInclV2 = 0;
   jetsPuppi_eta = 0;
   jetsPuppi_hadronFlavour = 0;
   jetsPuppi_m = 0;
   jetsPuppi_partonFlavour = 0;
   jetsPuppi_phi = 0;
   jetsPuppi_pt = 0;
   jetsPuppi_vtx3DSig = 0;
   jetsPuppi_vtx3DVal = 0;
   jetsPuppi_vtxMass = 0;
   met_phi = 0;
   met_pt = 0;
   met_sumet = 0;
   metNoHF_phi = 0;
   metNoHF_pt = 0;
   metNoHF_sumet = 0;
   metPfMva_phi = 0;
   metPfMva_pt = 0;
   metPfMva_sumet = 0;
   metPuppi_phi = 0;
   metPuppi_pt = 0;
   metPuppi_sumet = 0;
   muon_dxy = 0;
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
   slimmedGenJets_energy = 0;
   slimmedGenJets_eta = 0;
   slimmedGenJets_m = 0;
   slimmedGenJets_phi = 0;
   slimmedGenJets_pt = 0;
   vertices_ndof = 0;
   vertices_x = 0;
   vertices_y = 0;
   vertices_z = 0;
   electrons_electronID_loose = 0;
   electrons_electronID_medium = 0;
   electrons_electronID_tight = 0;
   electrons_electronID_veto = 0;
   electrons_isPF = 0;
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
   fChain->SetBranchAddress("gen_pt", &gen_pt, &b_gen_pt);
   fChain->SetBranchAddress("gen_eta", &gen_eta, &b_gen_eta);
   fChain->SetBranchAddress("gen_phi", &gen_phi, &b_gen_phi);
   fChain->SetBranchAddress("gen_energy", &gen_energy, &b_gen_energy);
   fChain->SetBranchAddress("gen_status", &gen_status, &b_gen_status);
   fChain->SetBranchAddress("gen_pdgid", &gen_pdgid, &b_gen_pdgid);
   fChain->SetBranchAddress("gen_motherindex", &gen_motherindex, &b_gen_motherindex);
   fChain->SetBranchAddress("HNHENoiseFilter", &HNHENoiseFilter, &b_HNHENoiseFilter);
   fChain->SetBranchAddress("csctighthaloFilter", &csctighthaloFilter, &b_csctighthaloFilter);
   fChain->SetBranchAddress("ecalDCTRFilter", &ecalDCTRFilter, &b_ecalDCTRFilter);
   fChain->SetBranchAddress("eeBadScFilter", &eeBadScFilter, &b_eeBadScFilter);
   fChain->SetBranchAddress("goodVertices", &goodVertices, &b_goodVertices);
   fChain->SetBranchAddress("GenTTCat", &GenTTCat, &b_GenTTCat);
   fChain->SetBranchAddress("genWeight_id1", &genWeight_id1, &b_genWeight_id1);
   fChain->SetBranchAddress("genWeight_id2", &genWeight_id2, &b_genWeight_id2);
   fChain->SetBranchAddress("hlt_2el33", &hlt_2el33, &b_hlt_2el33);
   fChain->SetBranchAddress("hlt_el12", &hlt_el12, &b_hlt_el12);
   fChain->SetBranchAddress("hlt_el16_el12_8", &hlt_el16_el12_8, &b_hlt_el16_el12_8);
   fChain->SetBranchAddress("hlt_el17", &hlt_el17, &b_hlt_el17);
   fChain->SetBranchAddress("hlt_el17_el12", &hlt_el17_el12, &b_hlt_el17_el12);
   fChain->SetBranchAddress("hlt_el23_el12", &hlt_el23_el12, &b_hlt_el23_el12);
   fChain->SetBranchAddress("hlt_el23_el12dz", &hlt_el23_el12dz, &b_hlt_el23_el12dz);
   fChain->SetBranchAddress("hlt_ele27eta2p1", &hlt_ele27eta2p1, &b_hlt_ele27eta2p1);
   fChain->SetBranchAddress("hlt_mu17_el12", &hlt_mu17_el12, &b_hlt_mu17_el12);
   fChain->SetBranchAddress("hlt_mu17_mu8", &hlt_mu17_mu8, &b_hlt_mu17_mu8);
   fChain->SetBranchAddress("hlt_mu17_tkmu8", &hlt_mu17_tkmu8, &b_hlt_mu17_tkmu8);
   fChain->SetBranchAddress("hlt_mu8_el17", &hlt_mu8_el17, &b_hlt_mu8_el17);
   fChain->SetBranchAddress("nGoodPV", &nGoodPV, &b_nGoodPV);
   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);
   fChain->SetBranchAddress("nTrueInteraction", &nTrueInteraction, &b_nTrueInteraction);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("genWeightQ", &genWeightQ, &b_genWeightQ);
   fChain->SetBranchAddress("genWeightX1", &genWeightX1, &b_genWeightX1);
   fChain->SetBranchAddress("genWeightX2", &genWeightX2, &b_genWeightX2);
   fChain->SetBranchAddress("lheWeight", &lheWeight, &b_lheWeight);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("puWeightDn", &puWeightDn, &b_puWeightDn);
   fChain->SetBranchAddress("puWeightUp", &puWeightUp, &b_puWeightUp);
   fChain->SetBranchAddress("pdfWeight", &pdfWeight, &b_pdfWeight);
   fChain->SetBranchAddress("electrons_absIso03", &electrons_absIso03, &b_electrons_absIso03);
   fChain->SetBranchAddress("electrons_absIso04", &electrons_absIso04, &b_electrons_absIso04);
   fChain->SetBranchAddress("electrons_chIso03", &electrons_chIso03, &b_electrons_chIso03);
   fChain->SetBranchAddress("electrons_chIso04", &electrons_chIso04, &b_electrons_chIso04);
   fChain->SetBranchAddress("electrons_dxy", &electrons_dxy, &b_electrons_dxy);
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
   fChain->SetBranchAddress("jets_CVSInclV2", &jets_CVSInclV2, &b_jets_CVSInclV2);
   fChain->SetBranchAddress("jets_energy", &jets_energy, &b_jets_energy);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_isPFId", &jets_isPFId, &b_jets_isPFId);
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
   fChain->SetBranchAddress("jetsPuppi_CVSInclV2", &jetsPuppi_CVSInclV2, &b_jetsPuppi_CVSInclV2);
   fChain->SetBranchAddress("jetsPuppi_eta", &jetsPuppi_eta, &b_jetsPuppi_eta);
   fChain->SetBranchAddress("jetsPuppi_hadronFlavour", &jetsPuppi_hadronFlavour, &b_jetsPuppi_hadronFlavour);
   fChain->SetBranchAddress("jetsPuppi_m", &jetsPuppi_m, &b_jetsPuppi_m);
   fChain->SetBranchAddress("jetsPuppi_partonFlavour", &jetsPuppi_partonFlavour, &b_jetsPuppi_partonFlavour);
   fChain->SetBranchAddress("jetsPuppi_phi", &jetsPuppi_phi, &b_jetsPuppi_phi);
   fChain->SetBranchAddress("jetsPuppi_pt", &jetsPuppi_pt, &b_jetsPuppi_pt);
   fChain->SetBranchAddress("jetsPuppi_vtx3DSig", &jetsPuppi_vtx3DSig, &b_jetsPuppi_vtx3DSig);
   fChain->SetBranchAddress("jetsPuppi_vtx3DVal", &jetsPuppi_vtx3DVal, &b_jetsPuppi_vtx3DVal);
   fChain->SetBranchAddress("jetsPuppi_vtxMass", &jetsPuppi_vtxMass, &b_jetsPuppi_vtxMass);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_pt", &met_pt, &b_met_pt);
   fChain->SetBranchAddress("met_sumet", &met_sumet, &b_met_sumet);
   fChain->SetBranchAddress("metNoHF_phi", &metNoHF_phi, &b_metNoHF_phi);
   fChain->SetBranchAddress("metNoHF_pt", &metNoHF_pt, &b_metNoHF_pt);
   fChain->SetBranchAddress("metNoHF_sumet", &metNoHF_sumet, &b_metNoHF_sumet);
   fChain->SetBranchAddress("metPfMva_phi", &metPfMva_phi, &b_metPfMva_phi);
   fChain->SetBranchAddress("metPfMva_pt", &metPfMva_pt, &b_metPfMva_pt);
   fChain->SetBranchAddress("metPfMva_sumet", &metPfMva_sumet, &b_metPfMva_sumet);
   fChain->SetBranchAddress("metPuppi_phi", &metPuppi_phi, &b_metPuppi_phi);
   fChain->SetBranchAddress("metPuppi_pt", &metPuppi_pt, &b_metPuppi_pt);
   fChain->SetBranchAddress("metPuppi_sumet", &metPuppi_sumet, &b_metPuppi_sumet);
   fChain->SetBranchAddress("muon_dxy", &muon_dxy, &b_muon_dxy);
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
   fChain->SetBranchAddress("slimmedGenJets_energy", &slimmedGenJets_energy, &b_slimmedGenJets_energy);
   fChain->SetBranchAddress("slimmedGenJets_eta", &slimmedGenJets_eta, &b_slimmedGenJets_eta);
   fChain->SetBranchAddress("slimmedGenJets_m", &slimmedGenJets_m, &b_slimmedGenJets_m);
   fChain->SetBranchAddress("slimmedGenJets_phi", &slimmedGenJets_phi, &b_slimmedGenJets_phi);
   fChain->SetBranchAddress("slimmedGenJets_pt", &slimmedGenJets_pt, &b_slimmedGenJets_pt);
   fChain->SetBranchAddress("vertices_ndof", &vertices_ndof, &b_vertices_ndof);
   fChain->SetBranchAddress("vertices_x", &vertices_x, &b_vertices_x);
   fChain->SetBranchAddress("vertices_y", &vertices_y, &b_vertices_y);
   fChain->SetBranchAddress("vertices_z", &vertices_z, &b_vertices_z);
   fChain->SetBranchAddress("electrons_electronID_loose", &electrons_electronID_loose, &b_electrons_electronID_loose);
   fChain->SetBranchAddress("electrons_electronID_medium", &electrons_electronID_medium, &b_electrons_electronID_medium);
   fChain->SetBranchAddress("electrons_electronID_tight", &electrons_electronID_tight, &b_electrons_electronID_tight);
   fChain->SetBranchAddress("electrons_electronID_veto", &electrons_electronID_veto, &b_electrons_electronID_veto);
   fChain->SetBranchAddress("electrons_isPF", &electrons_isPF, &b_electrons_isPF);
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

Bool_t SlimFlatCat::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SlimFlatCat::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void SlimFlatCat::SlimElectrons()
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


}

void SlimFlatCat::SlimMuons()
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
    muon_pt->erase(muon_pt->begin() + remove_obj.at(im) - nrm);
    muon_eta->erase(muon_eta->begin() + remove_obj.at(im) - nrm);
    muon_dxy->erase(muon_dxy->begin() + remove_obj.at(im) - nrm);
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
void  SlimFlatCat::SlimBool(std::vector<bool>* vbool, std::vector<int> torm){
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

void SlimFlatCat::SlimJets()
{
  std::vector<int > remove_obj;
  for(unsigned int im =0; im < jets_pt->size(); im++){
    bool rem =false;
    if( jets_pt->at(im) < 10) rem = true;
    if(rem) remove_obj.push_back(im);
  }
  
  int nrm = 0;
  for(unsigned int im =0; im < remove_obj.size(); im++){
    jets_CVSInclV2->erase(jets_CVSInclV2->begin() + remove_obj.at(im) - nrm);
    jets_energy->erase(jets_energy->begin() + remove_obj.at(im) - nrm);
    jets_eta->erase(jets_eta->begin() + remove_obj.at(im) - nrm);
    jets_isPFId->erase(jets_isPFId->begin() + remove_obj.at(im) - nrm);
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

void SlimFlatCat::SlimPuppiJets()
{
  std::vector<int > remove_obj;
  for(unsigned int im =0; im < jetsPuppi_pt->size(); im++){
    bool rem =false;
    if( jetsPuppi_pt->at(im) < 10) rem = true;
    if(rem) remove_obj.push_back(im);
  }

  int nrm = 0;
  for(unsigned int im =0; im < remove_obj.size(); im++){
    jetsPuppi_CVSInclV2->erase(jetsPuppi_CVSInclV2->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_eta->erase(jetsPuppi_eta->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_m->erase(jetsPuppi_m->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_phi->erase(jetsPuppi_phi->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_pt->erase(jetsPuppi_pt->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_vtx3DSig->erase(jetsPuppi_vtx3DSig->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_vtxMass->erase(jetsPuppi_vtxMass->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_vtx3DVal->erase(jetsPuppi_vtx3DVal->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_hadronFlavour->erase(jetsPuppi_hadronFlavour->begin() + remove_obj.at(im) - nrm);
    jetsPuppi_partonFlavour->erase(jetsPuppi_partonFlavour->begin() + remove_obj.at(im) - nrm);

    nrm++;
  }


}


Int_t SlimFlatCat::Cut(Long64_t entry)
{

  bool pass_lep_pt = false;
  for(unsigned int im=0; im < muon_pt->size(); im++){
    if(muon_pt->at(im) > 15) pass_lep_pt = true;
  }
  for(unsigned int im=0; im < electrons_pt->size(); im++){
    if(electrons_pt->at(im) > 15) pass_lep_pt = true;
  }
  if(pass_lep_pt) return 1;
  
  return -1;
}
#endif // #ifdef SlimFlatCat_cxx
