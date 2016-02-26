#include "LQCycleBaseExec.h"

ClassImp( LQCycleBaseExec );

LQCycleBaseExec::LQCycleBaseExec() {

}

void LQCycleBaseExec::BeginCycle()throw( LQError ){
}

void LQCycleBaseExec::BeginEvent()throw( LQError ){

}

void LQCycleBaseExec::SetUpEvent(Long64_t jentry , float weight, TString per)throw( LQError ){
  m_logger << INFO << "Default SetUpEvent function with "  << jentry << " and weight "<< weight << " and period "<< per << LQLogger::endmsg;
}

void LQCycleBaseExec::ExecuteEvents()throw( LQError ){
  
}


void LQCycleBaseExec::EndEvent()throw( LQError ){

}

void LQCycleBaseExec::EndCycle()throw( LQError ){

}


void LQCycleBaseExec::ClearOutputVectors() throw( LQError ){

}

void LQCycleBaseExec::WriteHistograms() throw( LQError ){

}


