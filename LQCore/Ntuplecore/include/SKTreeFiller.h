#ifndef SKTreeFiller_h
#define SKTreeFiller_h

#include <set>
#include "Data.h"

// SKTree
#include "KParticle.h"

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

  bool SkipTrigger(TString trigname);
  Int_t VertexN;
  Bool_t *goodVerticies;
  
  static bool isHigherPt(snu::KParticle p1, snu::KParticle p2){ return (p1 > p2);}

};



#endif
