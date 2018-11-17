#ifndef GenSelection_h
#define GenSelection_h

#include "BaseSelection.h"

/// SNU classes
#include "KTruth.h"


class GenSelection : public BaseSelection {

 public:
  GenSelection(LQEvent ev);
  GenSelection();
  ~GenSelection();

  GenSelection& operator= (const GenSelection& obj);
  GenSelection(const GenSelection& bs);
  
  void Selection(std::vector<snu::KTruth>& truthColl);
  
  
};
#endif
