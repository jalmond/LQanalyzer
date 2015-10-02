#define SlimFlatCat_cxx
#include "SlimFlatCat.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void SlimFlatCat::Loop()
{

   if (fChain == 0) return;
   

   TFile *skimfile = new TFile("Skim.root","recreate"); 
   fChain->LoadTree(0); 
   
   TTree *newtree = fChain->CloneTree(0);
 
   
   Long64_t nentries = fChain->GetEntriesFast();
   Int_t nselected = 0;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     if(!(jentry%10000)) std::cout << jentry << " :  "<<  fChain->GetEntries() << std::endl; 
     Long64_t ientry = LoadTree(jentry);
   
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     
     nselected++;
     SlimMuons();
     SlimElectrons();
     SlimJets();
     SlimPuppiJets();
     
     newtree->Fill();
   }
   std::cout << "Selected " << nselected << " out of " << fChain->GetEntries() << std::endl; 
   newtree->Write();
   skimfile->Close();
}
