#include "LQCycleBaseExec.h"

ClassImp( LQCycleBaseExec );

LQCycleBaseExec::LQCycleBaseExec() {

}

void LQCycleBaseExec::BeginCycle(TString filename)throw( LQError ){
  m_logger << INFO << "Default BeginCycle function with " << filename << LQLogger::endmsg;
}

void LQCycleBaseExec::BeginEvent(float weight)throw( LQError ){
  m_logger << INFO << "Default BeginEvent function with "  << weight << LQLogger::endmsg;
}

void LQCycleBaseExec::SetUpEvent(Long64_t jentry )throw( LQError ){
  m_logger << INFO << "Default SetUpEvent function with "  << jentry << LQLogger::endmsg;
}

void LQCycleBaseExec::ExecuteEvents()throw( LQError ){
  
}


void LQCycleBaseExec::EndEvent()throw( LQError ){

}

void LQCycleBaseExec::EndCycle()throw( LQError ){

}




