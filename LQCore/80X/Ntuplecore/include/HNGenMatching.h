#ifndef HNGenMatching_h
#define HNGenMatching_h

/// c++ std libraries
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// ROOT include(s): 
#include "TString.h"
#include "TH1D.h"

/// SNU classes
#include "KTruth.h"
#include "KMuon.h"

class HNGenMatching{

public:

  HNGenMatching();
  ~HNGenMatching();

  TDirectory* getTemporaryDirectory(void) const;

  void SetAllGenParticles(std::vector<snu::KTruth> g);
  void SetHNpdgids(int i);
  void FindGenParticles(bool debug=false);
  void SetSignalMass(int mass);
  int GetSignalMass();
  void SetMETInfo(double met, double metphi);

  void find_decay(std::vector<snu::KTruth> truthcoll, int target_index, std::vector<int>& indices);
  void print_all_indices(TString particle, std::vector<int> vec);

  void solution_selection_study(std::vector<snu::KMuon> recomuons);
  void PutNuPz(TLorentzVector *nu, double Pz);
  void PutNuPz(snu::KParticle *nu, double Pz);
  double solveqdeq(double W_mass, TLorentzVector l1l2l3, double MET, double METphi, TString pm);
  int find_mlmet_closest_to_W(snu::KParticle  lep[], snu::KParticle  MET, int n_lep=3);
  double MT(TLorentzVector a, TLorentzVector b);
  bool GenMatching(snu::KParticle gen, snu::KParticle reco, double maxDeltaR, double maxPtDiff);

  snu::KTruth gen_nu, gen_W_pri, gen_HN, gen_W_sec, gen_l_1, gen_l_2, gen_l_3;
  int n_gen_pass;
  double sol_sel_chi2_best, sol_sel_chi2_plus, sol_sel_chi2_minus, sol_sel_chi2_smaller, sol_sel_chi2_larger;
  bool allgenfound;

  //==== Histograms
  TH1D* GetHist(TString hname);
  void MakeHistograms(TString hname, int nbins, float xmin, float xmax);
  void FillHist(TString histname, float value, float w, float xmin, float xmax, int nbins);
  void WriteHNGenHists();
  void SetDrawHist(bool b);

private:

  std::vector<snu::KTruth> AllGenParticles;
  int HN_pdgid;
  int signalmass;
  double MET, METphi;
  bool DrawHist;

  //==== histograms;
  std::map<TString, TH1D*> maphist;

};

#endif
