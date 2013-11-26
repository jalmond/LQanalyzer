// Local includes
#include "LQController.h"
#include "ILQCycleBase.h"
#include "LQLogWriter.h"
#include "LQConstants.h"


// System include(s):                                                           
#include <cxxabi.h>
#include <cstdlib>

// STL include(s):
#include <stdio.h>  
#include <stdlib.h>     /* getenv */
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT include(s): 
#include <TROOT.h>
#include <TClass.h>
#include <TStopwatch.h>
#include <TClass.h>
#include <TSystem.h>
#include <TChain.h>

LQController::LQController(): outputLevelString("INFO"), CycleName("Analyzer"), jobName("Test"), treeName("rootTupleTree/tree"),filelist(""), completename(""), m_logger( "LQCycleController"),   target_luminosity(1.),  sample_crosssection(-999.), effective_luminosity(1.), n_total_event(-1), file_version(0), nevents_to_process(-1), m_isInitialized( kFALSE ), entrieslimit(-1){
  v_libnames.clear();
}

LQController::~LQController(){

}

void LQController::AddLibraries(TString libname){
  v_libnames.push_back(libname);
  
}



void LQController::SetName(TString name, Int_t version, TString dir) {

  string out_dir = getenv("LQANALYZER_OUTPUT_PATH");
  if(!dir.Contains("NULL")) out_dir = dir;
  completename = TString(out_dir) + name + "_";
  completename += version;
  completename += ".root";

  return;
}


void LQController::SetTotalMCEvents(TString path){
  
  
}

void LQController::SetTotalMCEvents(int ev){
  n_total_event = ev;
}
  
void LQController::SetMCCrossSection(float xsec){
  m_logger << INFO << "Set cross section: This is be used to calculate event weights. WARNING be careful." << LQLogger::endmsg;
  m_logger << INFO << "Will use weight = (lumi *  cs(pb) * gen filter efficiency) / MCevents "  << LQLogger::endmsg;
  sample_crosssection = xsec;
}


void LQController::SetJobName(TString name){
  jobName = name;
}
  


void LQController::SetInputList(TString list){
  filelist = list;
}

void LQController::SetTreeName(TString treename){
  treeName = treename;
}

void LQController::SetCycleName(TString cyclename){
  CycleName= cyclename;

}

void LQController::SetLogLevel(TString  level){
  outputLevelString = level;
}

void LQController::SetNEventsToProcess(int nevents){

  nevents_to_process = nevents;
}

void LQController::SetTargetLuminosity(float target_lumi){

  target_luminosity= target_lumi;
}
  

void LQController::SetEffectiveLuminosity(float eff_lumi){

  effective_luminosity= eff_lumi;
}


void LQController::Initialize() throw( LQError ){
  
  m_logger << INFO << "Initializing" << LQLogger::endmsg;
  
  // Just for kicks, lets measure the time it needs to initialise the                                                      
  // analysis:    
  TStopwatch timer;
  timer.Start();

  
  ///// List of things that can be set to congigure cycle:
  /////
  /*
    1) CycleName (i.e HNCycle)
    2) OUT put log level (i.e, INFO)
    3) libraires to load
    4) Set jobName
  */
  
  LQMsgType type = INFO;
  if     ( outputLevelString == "VERBOSE" ) type = VERBOSE;
  else if( outputLevelString == "DEBUG" )   type = DEBUG;
  else if( outputLevelString == "INFO" )    type = INFO;
  else if( outputLevelString == "WARNING" ) type = WARNING;
  else if( outputLevelString == "ERROR" )   type = ERROR;
  else if( outputLevelString == "FATAL" )   type = FATAL;
  else if( outputLevelString == "ALWAYS" )  type = ALWAYS;
  else {
    m_logger << WARNING << "Message output level ("
	     << outputLevelString << ") not recognized"
	     << LQLogger::endmsg;
  }
  
  LQLogWriter::Instance()->SetMinType( type );
  
  
  ////// Either  use default OR use class specified by user
  try {
    for(std::vector<TString>::iterator lit = v_libnames.begin(); lit != v_libnames.end(); lit++){
      TString libraryName = *lit;
      REPORT_VERBOSE( "Trying to load library \"" << libraryName << "\"" );
      int ret = 0;
      if( ( ret = gSystem->Load( libraryName.Data() ) ) >= 0 ) {
	m_logger << INFO << "Library loaded: \"" << libraryName << "\""
		 << LQLogger::endmsg;
      } else {
	LQError error( LQError::StopExecution );
	error << "Library failed to load: \"" << libraryName
	<< "\"\nRet. Val.: " << ret;
	throw error;
      }
    }// lib loop
  }
  catch( const LQError& error ) {
    //                                                                                                              
    // This is where I catch "cycle level" problems:                                                                
    //                                                                                                              
    if( error.request() <= LQError::SkipCycle ) {
    //// If just this cycle has to be skipped:                                                                     
      REPORT_ERROR( "Message: " << error.what() );
      REPORT_ERROR( "--> Skipping cycle!" );
      
      return;
    } else {
      m_logger << INFO << "FAILED" << LQLogger::endmsg;
     // If this is more serious:                                                                                  
      throw;
    }
  }
  
  m_logger << INFO << "Job '" << jobName << "' configured" << LQLogger::endmsg;
  
  timer.Stop();
  m_logger << INFO << "Time needed for initialisation: " << std::setw( 6 )
	   << std::setprecision( 2 ) << timer.RealTime() << " s"
	   << LQLogger::endmsg;
  
  // Print memory consumption after initialising the analysis:                                                             
  ProcInfo_t procinfo;
  gSystem->GetProcInfo( &procinfo );
  m_logger << DEBUG << "Memory consumption after initialisation:" << LQLogger::endmsg;
  m_logger.setf( std::ios::fixed );
  m_logger << DEBUG << "  Resident mem.: " << std::setw( 7 ) << procinfo.fMemResident
	   << " kB; Virtual mem.: " << std::setw( 7 ) << procinfo.fMemVirtual
	   << " kB" << LQLogger::endmsg;
  
  // set object status to be ready                                                                                         
  m_isInitialized = kTRUE;
}

void LQController::ExecuteCycle() throw( LQError ) {
  
  if( ! m_isInitialized ) {
    throw LQError( "LQCycleController is not initialized",
    LQError::StopExecution );
  }

  m_logger << INFO << "Entering ExecuteCycles" << LQLogger::endmsg;


  //                                                                                                                       
  // Measure the total time needed for this cycle:                                                                         
  //                                                                                                                       
  TStopwatch timer;
  timer.Start();

  //                                                                                                                       
  // Access the current cycle:                                                                                             
  //
  ////// Either  use default OR use class specified by user                                                                                                       
  try {
    
    TClass* cycleClass  = gROOT->GetClass(CycleName.Data(), true);
    if( ! cycleClass){
      LQError error( LQError::SkipCycle );
      m_logger << INFO << "Failed to get class" <<  LQLogger::endmsg;
      throw error;
    }
    ILQCycleBase* cycle = reinterpret_cast<ILQCycleBase*> ( cycleClass->New());
    
    TString      cycleName = CycleName;
    m_logger << INFO << "Created cycle '" << cycleName << "'"
             << LQLogger::endmsg;
        
 
    // Number of processed events:                                                                                           
    Long64_t procev = 0;
    // Number of skipped events:                                                                                             
    Long64_t skipev = 0;
    
    ///// This executes code:
    
    //                                                                                                                       
    // The begin cycle function has to be called here by hand:                                                               
    //                                                                                                                       

    ///  Get Tree Name / input filename
    
    TChain* chain = new TChain( treeName );
    if(filelist.Contains("NULL")){
      throw LQError( "Filelist is null!!!",
		     LQError::StopExecution );
    }
    std::ifstream fin(filelist.Data());
    std::string word;
    if(!chain) {
      throw LQError( "Chain is null!!!",
		     LQError::StopExecution );
    }
    
    if(fin.is_open()){
      while(getline (fin,word)){      
	m_logger << "- " << word << LQLogger::endmsg;
	chain->Add(word.c_str());
      }
      fin.close();
    }
    
    //// Connect chain to Data class
    cycle->Init(chain);        
    cycle->BeginCycle(completename);
    cycle->BeginEvent(CalculateWeight());   
    
    Long64_t nentries = cycle->GetNEntries();

    for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {            
      cycle->SetUpEvent(jentry);
      cycle->ExecuteEvents();
      cycle->EndEvent();
    }
    
    cycle->EndCycle();
  }
  catch( const LQError& error ) {
    //                                                                                                                                                            
    // This is where I catch "cycle level" problems:                                                                                                              
    //                                                                                                                                                            
    if( error.request() <= LQError::SkipCycle ) {
      //If just this cycle has to be skipped:                                                                                                                    
      REPORT_ERROR( "Message: " << error.what() );
      REPORT_ERROR( "--> Skipping cycle!" );
      
      return;
    } else {
    //// If this is more serious:                                                                                                                                 
      throw;
    }
  }
}
 


float LQController::CalculateWeight(){
  
  if(sample_crosssection != 999.&& n_total_event != -1){
    return (target_luminosity* sample_crosssection / n_total_event);
  }
  
  return (target_luminosity/effective_luminosity);
}
