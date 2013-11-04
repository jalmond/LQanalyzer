#ifndef SNUTreeFiller_h
#define SNUTreeFiller_h

#include <set>
#include "Data.h"

// SNUTree
#include "KParticle.h"
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"
#include "KEvent.h"
#include "KTruth.h"
#include "KTau.h"
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
  snu::KEvent GetEventInfo();
  std::vector<snu::KTruth>  GetTruthParticles();

  snu::KParticle::PartType partType;
  
  Int_t VertexN;
  Bool_t *goodVerticies;

  
};

#endif
