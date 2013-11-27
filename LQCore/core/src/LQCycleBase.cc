#include "LQCycleBase.h"

ClassImp( LQCycleBase );

LQCycleBase::LQCycleBase(){

  m_logger << VERBOSE << "SCycleBase constructed" << LQLogger::endmsg;

}

LQCycleBase::~LQCycleBase(){
  m_logger << VERBOSE << "SCycleBase destructed" << LQLogger::endmsg;
}
