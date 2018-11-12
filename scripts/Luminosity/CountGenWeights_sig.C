#include <map>

void CountGenWeights_sig(std::string outdir, TString filename, int nfile, std::string  histfile);

void CountGenWeights_sig(std::string outdir,TString filename, int nfile,std::string  histfile){


  // Traverse through all words 

  TChain chain("ntuple/event");

  for(int i = 0; i < nfile; i++)
    {
      TString treename = TString::Format(filename+"/ntuple_%d.root",i);
      if(i < 10) treename = TString::Format(filename+"/ntuple_00%d.root",i);
      else if(i < 100) treename = TString::Format(filename+"/ntuple_0%d.root",i);

      chain.Add(TString(treename));
    }
  

  float genWeight=0;
  TBranch        *b_genWeight;

  chain.SetBranchAddress("genWeight", &genWeight, &b_genWeight);
  //tree->SetBranchAddress("genWeight"

  float sum_weight=0.;
  Int_t nentries = chain.GetEntries();
  Long64_t nbytes = 0, nb = 0;

  for (Int_t jentry=0; jentry<nentries;jentry++) {
    chain.GetEvent(jentry);
    //nb = chain.GetEntry(jentry);
    sum_weight += genWeight;
  }



  std::string outputname = outdir + "/" + histfile ;
  TFile *skimfile = new TFile(outputname.c_str(),"recreate");
  TH1F* h = new TH1F ("sumweight", "sumweight", 2, 0., 2.);
  h->Fill(1., sum_weight);
  skimfile->Write();
  skimfile->Close();
  cout << "sum_weight = " << sum_weight << endl;
  TString outputdir2 = TString(outdir) + "/output/";
  TString command3 = "mv "  + TString(outputname) + " " + outputdir2;
  system(command3.Data());

}


