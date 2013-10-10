#ifndef SNUTreeMuonFiller_h
#define SNUTreeMuonFiller_h

#include "Data.h"

// SNUTree
#include "KMuon.h"

class SNUTreeMuonFiller : public Data {


 public:
  SNUTreeMuonFiller();
  ~SNUTreeMuonFiller();

  std::vector<snu::KMuon> GetAllMuons();
    
  
};

#endif
