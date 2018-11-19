// LOCAL includes
#include "HNGenMatching.h"

// STL
#include <sstream>

// ROOT
#include "TDirectory.h"
#include "TROOT.h"

TDirectory* HNGenMatching::getTemporaryDirectory(void) const
{
  // Create a unique directory in memory to hold the histograms:
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:
    std::stringstream dirname;
    dirname << "HNGenMatching_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;
}

HNGenMatching::HNGenMatching() :
signalmass(-9999),
n_gen_pass(0), sol_sel_chi2_best(0), sol_sel_chi2_plus(0), sol_sel_chi2_minus(0), sol_sel_chi2_smaller(0), sol_sel_chi2_larger(0),
allgenfound(false),
DrawHist(false)
{

  maphist.clear();

}

HNGenMatching::~HNGenMatching(){

  for(std::map<TString, TH1D*>::iterator mit = maphist.begin(); mit != maphist.end() ; mit++){
    delete mit->second;
  }
  maphist.clear();

}

void HNGenMatching::SetHNpdgids(int i){

  HN_pdgid = i;

}

void HNGenMatching::SetAllGenParticles(std::vector<snu::KTruth> g){

  //==== Set genparticles
  AllGenParticles = g;

}

void HNGenMatching::FindGenParticles(bool debug){

  int truthmax = AllGenParticles.size();
  vector<int> gen_HN_indices, gen_W_sec_indices, gen_l_1_indices, gen_nu_indices, gen_l_3_indices, gen_l_2_indices;
  gen_HN_indices.clear();
  gen_W_sec_indices.clear();
  gen_l_1_indices.clear();
  gen_nu_indices.clear();
  gen_l_3_indices.clear();
  gen_l_2_indices.clear();

  bool isLowMass(true);

  //==== check if this is low/high mass region
  if(GetSignalMass() < 80) isLowMass = true;
  else isLowMass = false;

  //==== find HN index
  if(debug) cout << "[HNGenMatching::FindGenParticles] Trying to find HN" << endl;
  for(int i=2;i<truthmax;i++){
    if(abs(AllGenParticles.at(i).PdgId()) == HN_pdgid){
      gen_HN_indices.push_back(i);
      find_decay(AllGenParticles, i, gen_HN_indices);
      break;
    }
  }
  if(debug) print_all_indices("gen_HN", gen_HN_indices);
  if(gen_HN_indices.size() == 0){
    cout << "[HNGenMatching::FindGenParticles] HN not found" << endl;
    return;
  }
  int HN_motherindex = AllGenParticles.at( gen_HN_indices.at(0) ).IndexMother();
  FillHist("GEN_HN_mother_pdgid", abs(AllGenParticles.at(HN_motherindex).PdgId()), 1., 0., 30., 30);

  //======================
  //==== low mass region
  //======================
  if(isLowMass){
    if(debug) cout << "[HNGenMatching::FindGenParticles][LowMass] This is a low mass signal" << endl;
   //==== find l_1 at gen. level
    if(debug) cout << "[HNGenMatching::FindGenParticles][LowMass] Trying to find l_1" << endl;
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<1;j++){
        //==== 1) |PID| = 13
        //==== 2) Mother = Mother of HN.at(0) : becase they are generated at the same time.
        if(abs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == AllGenParticles.at(gen_HN_indices.at(j)).IndexMother()){
          gen_l_1_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_l_1_indices);
          break;
        }
      }
      if(gen_l_1_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_l_1", gen_l_1_indices);
    if(gen_l_1_indices.size() == 0){
      cout << "[HNGenMatching::FindGenParticles][LowMass] l_1 not found" << endl;
      return;
    }

    //==== As m(HN) goes closer to W mass, W_sec starting to appear in truth coll
    //==== if W_sec is virtual, it may not appear in the gen particle collections
    //==== check W_sec exists
    bool LowMass_Wsec(false), LowMass_Z(false);
    vector<int> gen_Z_indices;
    gen_Z_indices.clear();

    if(debug) cout << "[HNGenMatching::FindGenParticles][LowMass] Find W_sec" << endl;
    for(int i=2;i<truthmax;i++){
      //==== 1) |PID| = 24
      //==== 2) Mother's PID = HN_pdgid
      if( fabs(AllGenParticles.at(i).PdgId()) == 24 && (abs(AllGenParticles.at(AllGenParticles.at(i).IndexMother()).PdgId())) == HN_pdgid ){
        gen_W_sec_indices.push_back(i);
        find_decay(AllGenParticles, i, gen_W_sec_indices);
        LowMass_Wsec = true;
        break;
      }
    }
    if(debug) print_all_indices("gen_W_sec", gen_W_sec_indices);

    //==== For low mass, HN can also decays via virtual Z
    if(debug) cout << "[HNGenMatching::FindGenParticles]LowMass] Trying to find Z" << endl;
    for(int i=2;i<truthmax;i++){
      //==== 1) |PID| = 23
      //==== 2) Mother's PID = HN_pdgid
      if( fabs(AllGenParticles.at(i).PdgId()) == 23 && (abs(AllGenParticles.at(AllGenParticles.at(i).IndexMother()).PdgId())) == HN_pdgid ){
        gen_Z_indices.push_back(i);
        find_decay(AllGenParticles, i, gen_Z_indices);
        LowMass_Z = true;
        break;
      }
    }
    if(debug) print_all_indices("gen_Z", gen_Z_indices);

    //============================
    //==== 1) HN to three particles
    //============================

    if( (!LowMass_Wsec) && (!LowMass_Z) ){
      if(debug) cout << "[HNGenMatching::FindGenParticles]LowMass][1] This is a HN to three particle decay" << endl;
      //==== find nu at gen. level
      if(debug) cout << "[HNGenMatching::FindGenParticles]LowMass][1] Trying to find nu" << endl;
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_HN_indices.size();j++){
          //==== 1) PID = 14
          //==== 2) Mother = {HN}
          if(abs(AllGenParticles.at(i).PdgId()) == 14 && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
            gen_nu_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_nu_indices);
            break;
          }
        }
        if(gen_nu_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_nu", gen_nu_indices);
      if(gen_nu_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass] [LowMass][1] nu not found" << endl;
        return;
      }

      //==== Let l_1 and l_2 are SS (considering dilep channel :D)
      //==== find l_2 at gen. level
      if(debug) cout << "[HNGenMatching::FindGenParticles]LowMass][1] Trying to find l_2" << endl;
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_HN_indices.size();j++){
          //==== 1) PID = PID of l_1 (SS)
          //==== 2) Mother = {HN}
          if(AllGenParticles.at(i).PdgId() == AllGenParticles.at(gen_l_1_indices.at(0)).PdgId() && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
            gen_l_2_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_l_2_indices);
            break;
          }
        }
      }
      if(debug) print_all_indices("gen_l_2", gen_l_2_indices);
      if(gen_l_2_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass] [1] l_2 not found" << endl;
        return;
      }

      //==== Let l_1 and l_3 are OS
      //==== find l_3 at gen. level
      if(debug) cout << "[HNGenMatching::FindGenParticles]LowMass][1] Trying to find l_3" << endl;
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_HN_indices.size();j++){
          //==== 1) PID = - (PID of l_1) (OS)
          //==== 2) Mother = {HN}
          if(AllGenParticles.at(i).PdgId() == -AllGenParticles.at(gen_l_1_indices.at(0)).PdgId() && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
            gen_l_3_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_l_3_indices);
            break;
          }
        }
        if(gen_l_3_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_l_3", gen_l_3_indices);
      if(gen_l_3_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][1] l_3 not found" << endl;
        return;
      }
    }

    //=========================
    //==== 2) HN decays via Z
    //=========================

    if( LowMass_Z ){
      //==== find nu at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_HN_indices.size();j++){
          //==== 1) |PID| = 14
          //==== 2) Mother = {HN}
          if(abs(AllGenParticles.at(i).PdgId()) == 14 && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
            gen_nu_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_nu_indices);
            break;
          }
        }
        if(gen_nu_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_nu", gen_nu_indices);
      if(gen_nu_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][2] nu not found" << endl;
        return;
      }

      //==== Let l_1 and l_2 are SS (condiering dilep channel :D)
      //==== find l_2 at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_Z_indices.size();j++){
          //==== 1) PID = PID of l_1 (SS)
          //==== 2) Mother = {Z}
          if(AllGenParticles.at(i).PdgId() == AllGenParticles.at(gen_l_1_indices.at(0)).PdgId() && AllGenParticles.at(i).IndexMother() == gen_Z_indices.at(j) ){
            gen_l_2_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_l_2_indices);
            break;
          }
        }
      }
      if(debug) print_all_indices("gen_l_2", gen_l_2_indices);
      if(gen_l_2_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][2] l_2 not found" << endl;
        return;
      }

      //==== Let l_1 and l_3 are OS
      //==== find l_3 at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_Z_indices.size();j++){
          //==== 1) PID = - (PID of l_1) (OS)
          //==== 2) Mother = {Z}
          if(AllGenParticles.at(i).PdgId() == -AllGenParticles.at(gen_l_1_indices.at(0)).PdgId() && AllGenParticles.at(i).IndexMother() == gen_Z_indices.at(j) ){
            gen_l_3_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_l_3_indices);
            break;
          }
        }
        if(gen_l_3_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_l_3", gen_l_3_indices);
      if(gen_l_3_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][2] l_3 not found" << endl;
        return;
      }

    }

    //====================================
    //==== 3) HN decays in to on-shell W
    //====================================

    if(LowMass_Wsec){
      //==== find nu at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_W_sec_indices.size();j++){
          //==== 1) |PID| = 14
          //==== 2) Mother = {W_sec}
          if(abs(AllGenParticles.at(i).PdgId()) == 14 && AllGenParticles.at(i).IndexMother() == gen_W_sec_indices.at(j) ){
            gen_nu_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_nu_indices);
            break;
          }
        }
        if(gen_nu_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_nu", gen_nu_indices);
      if(gen_nu_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][3] nu not found" << endl;
        return;
      }

      //==== find l_3 at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_W_sec_indices.size();j++){
          //==== 1) |PID| = 13
          //==== 2) Mother = {W_sec}
          if(fabs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == gen_W_sec_indices.at(j) ){
            gen_l_3_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_nu_indices);
            break;
          }
        }
        if(gen_l_3_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_l_3", gen_l_3_indices);
      if(gen_l_3_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][3] l_3 not found" << endl;
        return;
      }

      //==== find l_2 at gen. level
      for(int i=2;i<truthmax;i++){
        for(unsigned int j=0;j<gen_HN_indices.size();j++){
          //==== 1) |PID| = 13
          //==== 2) Mother = {HN}
          if(fabs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
            gen_l_2_indices.push_back(i);
            find_decay(AllGenParticles, i, gen_l_2_indices);
            break;
          }
        }
        if(gen_l_2_indices.size() != 0) break;
      }
      if(debug) print_all_indices("gen_l_2", gen_l_2_indices);
      if(gen_l_2_indices.size() == 0){
        cout << "[HNGenMatching::FindGenParticles][LowMass][3] l_2 not found" << endl;
        return;
      }

    }

    gen_l_1 = AllGenParticles.at( gen_l_1_indices.back() );
    gen_l_2 = AllGenParticles.at( gen_l_2_indices.back() );
    gen_l_3 = AllGenParticles.at( gen_l_3_indices.back() );
    gen_nu = AllGenParticles.at( gen_nu_indices.back() );
    allgenfound = true;

  }

  //=======================
  //==== high mass region
  //=======================
  else{
    //==== find l_1 at gen. level
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<1;j++){
        //==== 1) |PID| = 13
        //==== 2) Mother = Mother of HN.at(0) : becase they are generated at the same time.
        if(abs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == AllGenParticles.at(gen_HN_indices.at(j)).IndexMother()){
          gen_l_1_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_l_1_indices);
          break;
        }
      }
      if(gen_l_1_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_l_1", gen_l_1_indices);
    if(gen_l_1_indices.size() == 0) return;

    //==== fine l_2 at gen. level
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<gen_HN_indices.size();j++){
      //==== 1) |PID| = 13
      //==== 2) Mother = {HN}
        if(abs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
          gen_l_2_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_l_2_indices);
          break;
        }
      }
      if(gen_l_2_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_l_2", gen_l_2_indices);    
    if(gen_l_2_indices.size() == 0) return;

    //==== find W_sec
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<gen_HN_indices.size();j++){
        //==== 1) |PID| = 24
        //==== 2) Mother = {HN}
        if(abs(AllGenParticles.at(i).PdgId()) == 24 && AllGenParticles.at(i).IndexMother() == gen_HN_indices.at(j) ){
          gen_W_sec_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_W_sec_indices);
          break;
        }
      }
      if(gen_W_sec_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_W_sec", gen_W_sec_indices);
    if(gen_W_sec_indices.size() == 0) return;

    //==== find nu at gen. level
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<gen_W_sec_indices.size();j++){
        //==== 1) |PID| = 14
        //==== 2) Mother = {W_sec}
        if(abs(AllGenParticles.at(i).PdgId()) == 14 && AllGenParticles.at(i).IndexMother() == gen_W_sec_indices.at(j) ){
          gen_nu_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_nu_indices);
          break;
        }
      }
      if(gen_nu_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_nu", gen_nu_indices);
    if(gen_nu_indices.size() == 0) return;

    //==== find l_3 at gen. level
    for(int i=2;i<truthmax;i++){
      for(unsigned int j=0;j<gen_W_sec_indices.size();j++){
        //==== 1) |PID| = 13
        //==== 2) Mother = {W_sec}
        if(abs(AllGenParticles.at(i).PdgId()) == 13 && AllGenParticles.at(i).IndexMother() == gen_W_sec_indices.at(j) ){
          gen_l_3_indices.push_back(i);
          find_decay(AllGenParticles, i, gen_l_3_indices);
          break;
        }
      }
      if(gen_l_3_indices.size() != 0) break;
    }
    if(debug) print_all_indices("gen_l_3", gen_l_3_indices);
    if(gen_l_3_indices.size() == 0) return;

    gen_l_1 = AllGenParticles.at( gen_l_1_indices.back() );
    gen_l_2 = AllGenParticles.at( gen_l_2_indices.back() );
    gen_W_sec = AllGenParticles.at( gen_W_sec_indices.back() );
    gen_l_3 = AllGenParticles.at( gen_l_3_indices.back() );
    gen_nu = AllGenParticles.at( gen_nu_indices.back() );
    allgenfound = true;

  }

}

void HNGenMatching::SetSignalMass(int mass){

  signalmass = mass;

}

int HNGenMatching::GetSignalMass(){

  if(signalmass<0){
    cout << "[HNGenMatching::GetSignalMass] Signal mass is not initialized" << endl;
  }
  return signalmass;

}

void HNGenMatching::SetMETInfo(double met, double metphi){
  MET = met;
  METphi = metphi;
}

void HNGenMatching::find_decay(std::vector<snu::KTruth> truthcoll, int target_index, std::vector<int>& indices){

  for(unsigned int i=target_index+1; i<truthcoll.size(); i++){
    if( truthcoll.at(i).IndexMother() == target_index && truthcoll.at(i).PdgId() == truthcoll.at(target_index).PdgId() ){
      indices.push_back(i);
      find_decay(truthcoll, i, indices);
    }
  }

}

void HNGenMatching::print_all_indices(TString particle, std::vector<int> vec){

  if(vec.size()==0) cout << "No "+particle+" found" << endl;
  cout << particle+" indices" << endl;
  for(unsigned int i=0; i<vec.size(); i++) cout << " " << vec.at(i) << endl;
  cout << "==END==" << endl;

}

void HNGenMatching::solution_selection_study(std::vector<snu::KMuon> recomuons){

  double GENMatchingdR = 0.1;
  double GENMatchingdPt = 0.05;

  snu::KParticle reco_lep[3];
  for(int i=0;i<3;i++){
    reco_lep[i] = recomuons.at(i);
  }

  int OppSign, SameSign[2]; // SameSign[0].Pt() > SameSign[1].Pt()
  if(reco_lep[0].Charge() * reco_lep[1].Charge() > 0){ // Q(0) = Q(1)
    if(reco_lep[1].Charge() * reco_lep[2].Charge() < 0){ // Q(1) != Q(2)
      OppSign = 2;
      SameSign[0] = 0;
      SameSign[1] = 1;
    }
    else return; // veto Q(0) = Q(1) = Q(2)
  }
  else{ // Q(0) != Q(1)
    if(reco_lep[0].Charge() * reco_lep[2].Charge() > 0){ // Q(0) = Q(2)
      OppSign = 1;
      SameSign[0] = 0;
      SameSign[1] = 2;
    }
    else if(reco_lep[1].Charge() * reco_lep[2].Charge() > 0){ // Q(1) = Q(2)
      OppSign = 0;
      SameSign[0] = 1;
      SameSign[1] = 2;
    }
  } // Find l2 and assign l1&l3 in ptorder

  snu::KParticle reco_MET;
  reco_MET.SetPxPyPzE(MET*TMath::Cos(METphi), MET*TMath::Sin(METphi), 0, MET);

  //==== W_pri : first W
  //==== l_1 : lepton from first W
  //==== l_2 : lepton from HN
  //==== W_sec : W from HN
  //==== l_3 : lepton from second W
 
  bool isLowMass = false;
  if(GetSignalMass() < 80) isLowMass = true;

  //======================
  //==== low mass region
  //======================
  if(isLowMass){

    //==== solution selection
    double pz_sol_lowmass[2];
    pz_sol_lowmass[0] = solveqdeq(80.385, reco_lep[0]+reco_lep[1]+reco_lep[2], MET, METphi, "m"); // 0 = minus
    pz_sol_lowmass[1] = solveqdeq(80.385, reco_lep[0]+reco_lep[1]+reco_lep[2], MET, METphi, "p"); // 1 = plus
    if( pz_sol_lowmass[0] != pz_sol_lowmass[1] ){
      n_gen_pass++;
      int best_sel = fabs(pz_sol_lowmass[0]-gen_nu.Pz()) < fabs(pz_sol_lowmass[1]-gen_nu.Pz()) ? 0 : 1;
      int smaller = fabs(pz_sol_lowmass[0]) < fabs(pz_sol_lowmass[1]) ? 0 : 1;
      int larger = smaller == 0 ? 1 : 0;

      //=================
      //==== Chi2 study
      //=================

      FillHist("GEN_solsel_chi2_best", pow( (gen_nu.Pz() - pz_sol_lowmass[best_sel])/gen_nu.Pz() , 2), 1., 0., 10000., 10000);
      FillHist("GEN_solsel_chi2_plus", pow( (gen_nu.Pz() - pz_sol_lowmass[1])/gen_nu.Pz() , 2), 1., 0., 10000., 10000);
      FillHist("GEN_solsel_chi2_minus", pow( (gen_nu.Pz() - pz_sol_lowmass[0])/gen_nu.Pz() , 2), 1., 0., 10000., 10000);
      FillHist("GEN_solsel_chi2_smaller", pow( (gen_nu.Pz() - pz_sol_lowmass[smaller])/gen_nu.Pz() , 2), 1., 0., 10000., 10000);
      FillHist("GEN_solsel_chi2_larger", pow( (gen_nu.Pz() - pz_sol_lowmass[larger])/gen_nu.Pz() , 2), 1., 0., 10000., 10000);

      if(best_sel == 0){
        FillHist("GEN_solsel_chi2_minus_0_plus_1", 0, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_solsel_chi2_minus_0_plus_1", 1, 1., 0., 2., 2);
      }
      if(best_sel == smaller){
        FillHist("GEN_solsel_chi2_smaller_0_larger_1", 0, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_solsel_chi2_smaller_0_larger_1", 1, 1., 0., 2., 2);
      }

      sol_sel_chi2_best += pow( (gen_nu.Pz() - pz_sol_lowmass[best_sel])/gen_nu.Pz() , 2);
      sol_sel_chi2_plus += pow( (gen_nu.Pz() - pz_sol_lowmass[1])/gen_nu.Pz() , 2);
      sol_sel_chi2_minus += pow( (gen_nu.Pz() - pz_sol_lowmass[0])/gen_nu.Pz() , 2);
      sol_sel_chi2_smaller += pow( (gen_nu.Pz() - pz_sol_lowmass[smaller])/gen_nu.Pz() , 2);
      sol_sel_chi2_larger += pow( (gen_nu.Pz() - pz_sol_lowmass[larger])/gen_nu.Pz() , 2);

      //===================
      //==== deltaR study
      //===================

      PutNuPz(&reco_MET, pz_sol_lowmass[best_sel]);
      FillHist("GEN_solsel_dR_best", gen_nu.DeltaR( reco_MET  ), 1., 0., 5., 50);
      PutNuPz(&reco_MET, pz_sol_lowmass[1]);
      FillHist("GEN_solsel_dR_plus", gen_nu.DeltaR( reco_MET  ), 1., 0., 5., 50);
      PutNuPz(&reco_MET, pz_sol_lowmass[0]);
      FillHist("GEN_solsel_dR_minus", gen_nu.DeltaR( reco_MET  ), 1., 0., 5., 50);
      PutNuPz(&reco_MET, pz_sol_lowmass[smaller]);
      FillHist("GEN_solsel_dR_smaller", gen_nu.DeltaR( reco_MET  ), 1., 0., 5., 50);
      PutNuPz(&reco_MET, pz_sol_lowmass[larger]);
      FillHist("GEN_solsel_dR_larger", gen_nu.DeltaR( reco_MET  ), 1., 0., 5., 50);

    }


  }

  //=======================
  //==== high mass region
  //=======================
  else{

    snu::KParticle reco_lep_tlv[3];
    for(int i=0; i<3; i++) reco_lep_tlv[i] = reco_lep[i];
    int l_3_cand = find_mlmet_closest_to_W(reco_lep_tlv, reco_MET);

    FillHist("GEN_highmass_reco_MET", reco_MET.Pt(), 1., 0., 120., 120);
    FillHist("GEN_highmass_MT_gen_l_1_MET", (gen_l_1 + reco_MET).M() - 80.385, 1., -60., 60., 120);
    FillHist("GEN_highmass_MT_gen_l_2_MET", (gen_l_2 + reco_MET).M() - 80.385, 1., -60., 60., 120);
    FillHist("GEN_highmass_MT_gen_l_3_MET", (gen_l_3 + reco_MET).M() - 80.385, 1., -60., 60., 120);
    FillHist("GEN_highmass_l_3_cand", l_3_cand, 1., 0., 3., 3);
    FillHist("GEN_highmass_gen_W_sec_pt", gen_W_sec.Pt(), 1., 0., 1000., 1000);
    FillHist("GEN_highmass_dR_gen_l_1_gen_nu", gen_l_1.DeltaR(gen_nu), 1., 0., 5., 50);
    FillHist("GEN_highmass_dR_gen_l_2_gen_nu", gen_l_2.DeltaR(gen_nu), 1., 0., 5., 50);
    FillHist("GEN_highmass_dR_gen_l_3_gen_nu", gen_l_3.DeltaR(gen_nu), 1., 0., 5., 50);

    //==== 1) l_1 first by pt ordering
    //==== signal_class = 3 : gen_l_1 is leading SS
    //==== signal_class = 4 : gen_l_1 is subleading SS (m > 1000 GeV)
    
    int l_1_cand = SameSign[0], l_SS_rem = SameSign[1];
    int signal_class = 3;
    //==== pt ordering reversed for m(HN) > 1000 GeV
    if( GetSignalMass() > 1000 ){ //FIXME study signal class
      signal_class = 4;
      l_1_cand = SameSign[1];
      l_SS_rem = SameSign[0];
    }
    //if( reco_lep[l_1_cand].DeltaR(gen_l_1) < 0.1 ){
    if( GenMatching(gen_l_1, reco_lep[l_1_cand], GENMatchingdR, GENMatchingdPt) ){
      FillHist("GEN_highmass_gen_l_1_first", 1, 1., 0., 2., 2);

      int l_2_cand_m1, l_3_cand_m1;
      //if( fabs( (reco_lep[OppSign]+reco_MET).M() - 80.385 ) < fabs( (reco_lep[l_SS_rem]+reco_MET).M() - 80.385 ) ){
      if( fabs( MT(reco_lep[OppSign], reco_MET) - 80.385 ) < fabs( MT(reco_lep[l_SS_rem], reco_MET) - 80.385 ) ){ 
        l_3_cand_m1 = OppSign;
        l_2_cand_m1 = l_SS_rem;
      }
      else{
        l_3_cand_m1 = l_SS_rem;
        l_2_cand_m1 = OppSign;
      }
      //if( gen_l_2.DeltaR( reco_lep[l_2_cand_m1] ) < 0.1 && gen_l_3.DeltaR( reco_lep[l_3_cand_m1] ) < 0.1 ) FillHist("GEN_pt_order_first_mlmet_next", 1, 1., 0., 2., 2);
      if( GenMatching(gen_l_2, reco_lep[l_2_cand_m1], GENMatchingdR, GENMatchingdPt) && GenMatching(gen_l_3, reco_lep[l_3_cand_m1], GENMatchingdR, GENMatchingdPt) ){
        FillHist("GEN_highmass_gen_l_1_first_mlmet_next", 1, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_highmass_gen_l_1_first_mlmet_next", 0, 1., 0., 2., 2);
      }

    }
    else{
      FillHist("GEN_highmass_gen_l_1_first", 0, 1., 0., 2., 2);
    }

    //==== 2) gen_l_3 first by mlmet
    
    //if( gen_l_3.DeltaR(reco_lep[l_3_cand]) < 0.1 ){
    if( GenMatching(gen_l_3, reco_lep[l_3_cand], GENMatchingdR, GENMatchingdPt) ){
      FillHist("GEN_highmass_gen_l_3_first", 1, 1., 0., 2., 2);

      vector<snu::KParticle> lep_rem;
      for(unsigned int i=0; i<3; i++){
        if(i!=l_3_cand) lep_rem.push_back( reco_lep[i] );
      }

      //==== 2-1) Leading goes to l_1
      if( GenMatching(gen_l_1, lep_rem[0], GENMatchingdR, GENMatchingdPt) ){
        FillHist("GEN_highmass_gen_l_3_first_gen_l_1_leading_next", 1, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_highmass_gen_l_3_first_gen_l_1_leading_next", 0, 1., 0., 2., 2);
      }
      //==== 2-2) Leading goes to l_2
      if( GenMatching(gen_l_2, lep_rem[0], GENMatchingdR, GENMatchingdPt) ){
        FillHist("GEN_highmass_gen_l_3_first_gen_l_2_leading_next", 1, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_highmass_gen_l_3_first_gen_l_2_leading_next", 0, 1., 0., 2., 2);
      }

      //==== Combination
      int l_1_cand_m2, l_2_cand_m2;
      //==== if l_3 is OS : then, use pt ordering
      if( l_3_cand == OppSign ){
        //==== m(HN) : 90 ~ 200 GeV
        if( signal_class == 3){
          l_1_cand_m2 = SameSign[0];
          l_2_cand_m2 = SameSign[1];
        }
        //==== m(HN) : 300 ~ 1000 GeV
        else{
          l_1_cand_m2 = SameSign[1];
          l_2_cand_m2 = SameSign[0];
        }
      }
      //==== if l_3 is SS : then, remaing SS should be l_1
      else{
        l_2_cand_m2 = OppSign;
        if( l_3_cand == SameSign[0] ) l_1_cand_m2 = SameSign[1];
        else l_1_cand_m2 = SameSign[0];
      }

      //if( gen_l_1.DeltaR( reco_lep[l_1_cand_m2] ) < 0.1 && gen_l_2.DeltaR( reco_lep[l_2_cand_m2] ) < 0.1 ) FillHist("GEN_mlmet_first_pt_order_next", 1, 1., 0., 2., 2);
      if( GenMatching(gen_l_1, reco_lep[l_1_cand_m2], GENMatchingdR, GENMatchingdPt) && GenMatching(gen_l_2, reco_lep[l_2_cand_m2], GENMatchingdR, GENMatchingdPt) ){
        FillHist("GEN_highmass_gen_l_3_first_pt_order_next", 1, 1., 0., 2., 2);
      }
      else{
        FillHist("GEN_highmass_gen_l_3_first_pt_order_next", 0, 1., 0., 2., 2);
      }

    }
    else{
      FillHist("GEN_highmass_gen_l_3_first", 0, 1., 0., 2., 2);
    }


  }

  //==== histograms
 
  FillHist("GEN_matching_validation_W_pri", (gen_l_1+gen_l_2+gen_l_3+gen_nu).M(), 1., 0., 1100., 1100);
  FillHist("GEN_matching_validation_HN", (gen_l_2+gen_l_3+gen_nu).M(), 1., 0., 1100., 1100);
  FillHist("GEN_matching_validation_W_sec", (gen_l_3+gen_nu).M(), 1., 0., 100., 1000);

  FillHist("GEN_gen_l_1_Pt", gen_l_1.Pt(), 1., 0., 1500., 1500);
  FillHist("GEN_gen_l_2_Pt", gen_l_2.Pt(), 1., 0., 1500., 1500);
  FillHist("GEN_gen_l_3_Pt", gen_l_3.Pt(), 1., 0., 1500., 1500);
  FillHist("GEN_gen_nu_Pt", gen_nu.Pt(), 1., 0., 1500., 1500);
 
  snu::KParticle gen_l_SS;
  if( gen_l_1.PdgId() == gen_l_2.PdgId() ) gen_l_SS = gen_l_2;
  else gen_l_SS = gen_l_3;
  FillHist("GEN_gen_SS_Pt", gen_l_SS.Pt(), 1., 0., 1500., 1500);

  //==== gen_l_1 : leadingSS
  if( gen_l_1.Pt() > gen_l_SS.Pt() ){
    FillHist("GEN_gen_l_1_leadingSS", 1, 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_gen_l_1_leadingSS", 0, 1., 0., 2., 2);
  }
  //==== gen_l_1 : leading
  if( gen_l_1.Pt() > gen_l_2.Pt() && gen_l_1.Pt() > gen_l_3.Pt() ){
    FillHist("GEN_gen_l_1_leading", 1., 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_gen_l_1_leading", 0., 1., 0., 2., 2);
  }
  //==== gen_l_2 : leading
  if( gen_l_2.Pt() > gen_l_1.Pt() && gen_l_2.Pt() > gen_l_3.Pt() ){
    FillHist("GEN_gen_l_2_leading", 1., 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_gen_l_2_leading", 0., 1., 0., 2., 2);
  }

  //if( reco_lep[SameSign[0]].DeltaR(gen_l_1) < 0.1 ){
  if( GenMatching(gen_l_1, reco_lep[SameSign[0]], GENMatchingdR, GENMatchingdPt) ){
    FillHist("GEN_reco_leading_SS_match_gen_l_1", 1, 1., 0., 2., 2);
    //cout << "=======================================" << endl;
    //cout << "== gen_l_1 is matched to leading SS  ==" << endl;
    //cout << gen_l_1.Pt() << '\t' << gen_l_1.PdgId()/-13 << endl;
    //cout << gen_l_2.Pt() << '\t' << gen_l_2.PdgId()/-13 << endl;
    //cout << gen_l_3.Pt() << '\t' << gen_l_3.PdgId()/-13 << endl;
    //cout << reco_lep[SameSign[0]].Pt() << '\t' << reco_lep[SameSign[0]].Charge() << endl;
    //cout << reco_lep[SameSign[1]].Pt() << '\t' << reco_lep[SameSign[0]].Charge() << endl;
  }
  else{
    FillHist("GEN_reco_leading_SS_match_gen_l_1", 0, 1., 0., 2., 2); 
  }

  //if( reco_lep[SameSign[1]].DeltaR(gen_l_1) < 0.1 ){
  if( GenMatching(gen_l_1, reco_lep[SameSign[1]], GENMatchingdR, GENMatchingdPt) ){
    FillHist("GEN_reco_subleading_SS_match_gen_l_1", 1, 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_reco_subleading_SS_match_gen_l_1", 0, 1., 0., 2., 2);
  }

  //if( reco_lep[0].DeltaR(gen_l_1) < 0.1 ){
  if( GenMatching(gen_l_1, reco_lep[0], GENMatchingdR, GENMatchingdPt) ){
    FillHist("GEN_reco_leading_match_gen_l_1", 1, 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_reco_leading_match_gen_l_1", 0, 1., 0., 2., 2);
  }

  //if( reco_lep[0].DeltaR(gen_l_2) < 0.1 ){
  if( GenMatching(gen_l_2, reco_lep[0], GENMatchingdR, GENMatchingdPt) ){
    FillHist("GEN_reco_leading_match_gen_l_2", 1, 1., 0., 2., 2);
  }
  else{
    FillHist("GEN_reco_leading_match_gen_l_2", 0, 1., 0., 2., 2);
  }

}

void HNGenMatching::PutNuPz(TLorentzVector *nu, double Pz){
  double Px, Py;
  Px = nu->Px();
  Py = nu->Py();
  nu->SetPxPyPzE(Px, Py, Pz, TMath::Sqrt(Px*Px+Py*Py+Pz*Pz));
}

void HNGenMatching::PutNuPz(snu::KParticle *nu, double Pz){
  double Px, Py;
  Px = nu->Px();
  Py = nu->Py();
  nu->SetPxPyPzE(Px, Py, Pz, TMath::Sqrt(Px*Px+Py*Py+Pz*Pz));
}

double HNGenMatching::solveqdeq(double W_mass, TLorentzVector l1l2l3, double MET, double METphi, TString pm){
  TLorentzVector met;
  met.SetPxPyPzE(MET*cos(METphi),
                 MET*sin(METphi),
                 0,
                 MET);

  Double_t d = (W_mass*W_mass)-(l1l2l3.M())*(l1l2l3.M())+2.0*l1l2l3.Px()*met.Px()+2.0*l1l2l3.Py()*met.Py();
  Double_t a = l1l2l3.E()*l1l2l3.E() - l1l2l3.Pz()*l1l2l3.Pz();
  Double_t b = d*l1l2l3.Pz();
  Double_t c = l1l2l3.E()*l1l2l3.E()*met.E()*met.E()-d*d/4.0;
  if(b*b-4*a*c<0){
    return b/(2*a);
  }
  else{
    if(pm=="p") return (b+TMath::Sqrt(b*b-4*a*c))/(2*a);
    else if(pm=="m")  return (b-TMath::Sqrt(b*b-4*a*c))/(2*a);
    else return 0;
  }
}

int HNGenMatching::find_mlmet_closest_to_W(snu::KParticle lep[], snu::KParticle MET, int n_lep){
  double m_diff[n_lep];
  double m_diff_min = 999999999.;
  int outindex = 0;
  for(int i=0; i<n_lep; i++){
    double dphi = lep[i].DeltaPhi(MET);
    double mt2 = 2.*lep[i].Pt()*MET.Pt()*(1.-TMath::Cos(dphi));
    m_diff[i] = fabs( sqrt(mt2) - 80.385 );
    if( m_diff[i] < m_diff_min ){
      m_diff_min = m_diff[i];
      outindex = i;
    }
  }
  return outindex;

}

double HNGenMatching::MT(TLorentzVector a, TLorentzVector b){

  double dphi = a.DeltaPhi(b);
  return TMath::Sqrt( 2.*a.Pt()*b.Pt()*(1.- TMath::Cos(dphi) ) );

}

bool HNGenMatching::GenMatching(snu::KParticle gen, snu::KParticle reco, double maxDeltaR, double maxPtDiff){

  bool matched = true;
  if(reco.Pt() > 200.) maxPtDiff = 0.1;

  if( gen.DeltaR(reco) >= maxDeltaR ) matched = false;
  if( fabs(gen.Pt() - reco.Pt()) / reco.Pt() >= maxPtDiff ) matched = false;

  return matched;

}

//==== Histograms
TH1D* HNGenMatching::GetHist(TString hname){

  TH1D* h = NULL;
  std::map<TString, TH1D*>::iterator mapit = maphist.find(hname);
  if(mapit != maphist.end()) return mapit->second;
  else cout << "[HNGenMatching::GetHist] "<< hname << " was not found in map" << endl;

  return h;
}

void HNGenMatching::MakeHistograms(TString hname, int nbins, float xmin, float xmax){

  TDirectory* origDir = gDirectory;

  TDirectory* tempDir1 = getTemporaryDirectory();
  tempDir1->cd();
  maphist[hname] =  new TH1D(hname.Data(),hname.Data(),nbins,xmin,xmax);

  origDir->cd();

}


void HNGenMatching::FillHist(TString histname, float value, float w, float xmin, float xmax, int nbins){

  if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  else{
    if(nbins < 0) {
      cout << "[HNGenMatching::FillHist] "<< histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << endl;
      exit(0);
    }
    MakeHistograms(histname, nbins, xmin, xmax);
    if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  }

}
void HNGenMatching::WriteHNGenHists(){

  if(!DrawHist) return;
  cout << "[HNGenMatching::WriteHNGenHists] Writing HNGenMatching histograms" << endl;
  for(std::map<TString, TH1D*>::iterator mit = maphist.begin(); mit != maphist.end() ; mit++){
    mit->second->Write();
  }

}

void HNGenMatching::SetDrawHist(bool b){
  DrawHist = b;
}













