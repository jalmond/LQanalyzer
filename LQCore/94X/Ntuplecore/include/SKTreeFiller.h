#ifndef SKTreeFiller_h
#define SKTreeFiller_h

#include <set>
#include "Data.h"

// SKTree
#include "KParticle.h"

class Reweight;



//class KMuon;
#include "KMuon.h"
#include "KElectron.h"
#include "KPhoton.h"
#include "KJet.h"
#include "KFatJet.h"
#include "KGenJet.h"
#include "KEvent.h"
#include "KTruth.h"
#include "KTau.h"
#include "KTrigger.h"
#include "SelectionFunctions.h"
#include "AnalysisBase.h"

class SKTreeFiller : public Data, public AnalysisBase {

 public:
  SKTreeFiller();
  ~SKTreeFiller();

  std::vector<snu::KMuon> GetAllMuons();
  std::vector<snu::KElectron> GetAllElectrons();
  std::vector<snu::KPhoton> GetAllPhotons();
  std::vector<snu::KJet> GetAllJets();
  std::vector<snu::KFatJet> GetAllFatJets();
  std::vector<snu::KGenJet> GetAllGenJets();
  snu::KEvent GetEventInfo();
  snu::KTrigger GetTriggerInfo(std::vector<TString> triglist);
  std::vector<snu::KTruth>  GetTruthParticles(int np=30);
  void ERRORMessage(TString comment);
  snu::KParticle::PartType partType;


  std::vector<double>  GetWeights(TString tag);


  float miniIsoDr(double pt);
  double CalcMiniIso(double pt, double ch, double nh, double ph, double pu, double rho, double EA);
  double CalcPFIso(double j_PFCH04,double j_PFNH04, double j_PFPH04, double j_PU04);

  double EA(double eta);
  double ElectronEA(double eta);

  bool SkipTrigger(TString trigname);
  Int_t VertexN;
  Bool_t *goodVerticies;
  
  Reweight *reweightPU;
  Reweight *reweightPU_up;
  Reweight *reweightPU_down;
  static bool isHigherPt(snu::KParticle p1, snu::KParticle p2){ return (p1 > p2);}

};



#endif
