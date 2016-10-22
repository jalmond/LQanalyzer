//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 25 04:48:20 2015 by ROOT version 5.34/14
// from TChain ntuple/event/
//////////////////////////////////////////////////////////

#ifndef SkimFlatCat_h
#define SkimFlatCat_h

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

class SkimFlatCat {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         genWeight;
   Int_t           event;

   TBranch        *b_genWeight;   //!
   TBranch        *b_event;   //!


   SkimFlatCat(TTree *tree=0);
   virtual ~SkimFlatCat();
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

#ifdef SkimFlatCat_cxx
SkimFlatCat::SkimFlatCat(TTree *tree) : fChain(0) 
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

SkimFlatCat::~SkimFlatCat()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SkimFlatCat::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SkimFlatCat::LoadTree(Long64_t entry)
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

void SkimFlatCat::Init(TTree *tree)
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

   met_phi = 0;
   met_pt = 0;
   met_sumet = 0;
   metNoHF_phi = 0;
   metNoHF_pt = 0;
   metNoHF_sumet = 0;
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

   muon_roch_phi = 0;
   muon_roch_pt = 0;
   muon_roch_energy = 0;
   muon_roch_eta = 0;
   muon_roch_m = 0;

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
   
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchAddress("event", &event, &b_event);

   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchStatus("genWeight",1);
   Notify();
}

Bool_t SkimFlatCat::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SkimFlatCat::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}


void SkimFlatCat::SlimElectrons()
{

}

void SkimFlatCat::SlimMuons()
{

}
void  SkimFlatCat::SlimBool(std::vector<bool>* vbool, std::vector<int> torm){
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

void SkimFlatCat::SlimJets()
{


}

void SkimFlatCat::SlimPuppiJets()
{
  
  
}


Int_t SkimFlatCat::Cut(Long64_t entry)
{
  return 1;
}
#endif // #ifdef SkimFlatCat_cxx
