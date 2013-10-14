#ifndef SNUTreeFiller_h
#define SNUTreeFiller_h

#include <set>
#include "Data.h"

// SNUTree
#include "KMuon.h"
#include "KElectron.h"
#include "KJet.h"

class SNUTreeFiller : public Data {


 public:
  SNUTreeFiller();
  ~SNUTreeFiller();

std::vector<snu::KMuon> GetAllMuons(int ivertex);
std::vector<snu::KElectron> GetAllElectrons(int ivertex);
std::vector<snu::KJet> GetAllJets();



  
};

#endif
