#define t2_cxx
#include "t2.h"
#include <TH2.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>

void t2::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L t.C
//      Root > t t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TCanvas* c1 = new TCanvas("Plot", "Plot", 800, 600);
   TH1D* hec = new TH1D("hel_en","hel_en",1000, 0., 1000.);
   TH1D* hb = new TH1D("hel_en2","hel_en2",1000, 0., 1000.);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      //if(1000%jentry) std::cout << "Processing " << jentry << std::endl;
      
      for(unsigned int i=0; i < electrons_energy->size(); i++){
	hb->Fill(electrons_energy->at(i));
	hec->Fill(electrons_energy->at(i)/electrons_smearedScale->at(i));
      }
   }
   hb->GetXaxis()->SetRangeUser(150.,250.);
   hb->Draw("hist");
   hec->SetLineColor(kRed);
   hec->Draw("histsame");
   
   c1->SaveAs("test.pdf ");
   
}
