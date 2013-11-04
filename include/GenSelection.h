#ifndef GenSelection_h
#define GenSelection_h

#include "BaseSelection.h"

/// SNU classes
#include "KTruth.h"


class GenSel : public BaseSel {

 public:
  GenSel(LQEvent ev);
  GenSel();
  ~GenSel();

  GenSel& operator= (const GenSel& obj);
  GenSel(const GenSel& bs);
  
  void GenSelection(std::vector<snu::KTruth>& truthColl);
  
  
};
#endif
