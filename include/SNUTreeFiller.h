#ifndef SNUTreeFiller_h
#define SNUTreeFiller_h

#include <set>
#include "Data.h"

// SNUTree
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"
#include "KEvent.h"
#include "SelectionFunctions.h"

class SNUTreeFiller : public Data {


 public:
  SNUTreeFiller();
  ~SNUTreeFiller();

  std::vector<snu::KMuon> GetAllMuons(int ivertex);
  std::vector<snu::KElectron> GetAllElectrons();
  std::vector<snu::KJet> GetAllJets();
  snu::KEvent GetEventInfo();
 

 UInt_t VertexN;
 Bool_t *goodVerticies;


  
};

#endif
