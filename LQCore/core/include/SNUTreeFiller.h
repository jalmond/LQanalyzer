#ifndef SNUTreeFiller_h
#define SNUTreeFiller_h

#include <set>
#include "Data.h"

// SNUTree
#include "KParticle.h"

//class KMuon;
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"
#include "KEvent.h"
#include "KTruth.h"
#include "KTau.h"
#include "KTrigger.h"
#include "SelectionFunctions.h"
#include "AnalysisBase.h"

class SNUTreeFiller : public Data, public AnalysisBase {

 public:
  SNUTreeFiller();
  ~SNUTreeFiller();

  std::vector<snu::KMuon> GetAllMuons();
  std::vector<snu::KTau> GetAllTaus();
  std::vector<snu::KElectron> GetAllElectrons();
  std::vector<snu::KJet> GetAllJets();
  std::vector<snu::KJet> GetAllCaloJets();
  snu::KEvent GetEventInfo();
  snu::KTrigger GetTriggerInfo(std::vector<TString> triglist);
  std::vector<snu::KTruth>  GetTruthParticles();

  snu::KParticle::PartType partType;
  
  Int_t VertexN;
  Bool_t *goodVerticies;
  
  static bool isHigherPt(snu::KParticle p1, snu::KParticle p2){ return (p1 < p2);}

};



#endif
