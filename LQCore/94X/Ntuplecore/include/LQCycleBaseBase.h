#ifndef LQCycleBaseBase_H
#define LQCycleBaseBase_H

// ROOT include(s):
#include <TObject.h>

// Local include(s):
#include "LQLogger.h"

class LQCycleBaseBase {
 public:
  LQCycleBaseBase();

  virtual ~LQCycleBaseBase(){}


 protected:
  /// Function used to set the name of the current cycle
  void SetLogName( const char* name );
  /// Function for accessing the logger object
  LQLogger& logger() const { return m_logger; }

  mutable LQLogger m_logger;

  ClassDef( LQCycleBaseBase, 0 );

};
#endif
