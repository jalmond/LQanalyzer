#include "LQCycleBaseBase.h"

ClassImp( LQCycleBaseBase );


LQCycleBaseBase::LQCycleBaseBase() : m_logger( "NameNotSet" ) {
  REPORT_VERBOSE( "LQCycleBaseBase constructed" );
}


void LQCycleBaseBase::SetLogName( const char* name ) {

  m_logger.SetSource( name );
  return;

}
