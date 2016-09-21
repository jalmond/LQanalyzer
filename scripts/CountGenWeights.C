#include <map>

void CountGenWeights(std::string outdir, std::string filename, std::string  histfile);

void CountGenWeights(std::string outdir,std::string filename, std::string  histfile){

  TFile* file = TFile::Open(filename.c_str());

  TDirectory * dir = (TDirectory*)file->Get(TString(filename) + ":/ntuple");
  TTree * tree;
  dir->GetObject("event",tree);

  float genWeight=0;
  TBranch        *b_genWeight;

  tree->SetBranchAddress("genWeight", &genWeight, &b_genWeight);

  float sum_weight=0.;
  Long64_t nentries = tree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tree->LoadTree(jentry);
    nb = tree->GetEntry(jentry);
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
  cout << command3 << endl;
  system(command3.Data());

}


