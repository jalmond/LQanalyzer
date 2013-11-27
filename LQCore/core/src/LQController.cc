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
#include <TFile.h>
#include <TClass.h>
#include <TStopwatch.h>
#include <TClass.h>
#include <TSystem.h>
#include <TChain.h>

LQController::LQController(): inputType(NOTSET), outputLevelString("INFO"), CycleName("Analyzer"), jobName("Test"), treeName("rootTupleTree/tree"),filelist(""), fullfilelist(""), completename(""),  m_logger( "LQCycleController") , target_luminosity(1.),  sample_crosssection(-999.), effective_luminosity(1.), n_total_event(-1.), file_version(0),  nevents_to_process(-1), m_isInitialized( kFALSE ), entrieslimit(-1), n_ev_to_skip(0), v_libnames(0), list_to_run(0), total_events_beforeskim(0), total_events_afterskim(0){

}

LQController::~LQController(){

}

void LQController::AddLibraries(TString libname){
  v_libnames.push_back(libname);
  
}
void LQController::RunEvent(Long64_t pick_event){
  list_to_run.push_back(pick_event);
}
  



void LQController::SetName(TString name, Int_t version, TString dir) {

  string out_dir = getenv("LQANALYZER_OUTPUT_PATH");
  if(!dir.Contains("NULL")) out_dir = dir;
  completename = TString(out_dir) + name + "_";
  completename += version;
  completename += ".root";

  return;
}

void LQController::SkipEvents(int toskip){
  n_ev_to_skip = toskip;
}


void LQController::SetDataType(TString settype){
  
  if     ( settype == "Data" )    inputType = data;
  else if( settype == "data" )    inputType = data;
  else if( settype == "DATA" )    inputType = data;
  else if( settype == "MC" )      inputType = mc;
  else if( settype == "mc" )      inputType = mc;
  else                            inputType = NOTSET;
  
}

std::pair<Double_t, Double_t>  LQController::GetTotalEvents() throw (LQError){
  
  TH1I* EventCounter = new TH1I("EventCounter","Event Counter",2,-0.5,1.5);

  if(fullfilelist.Contains("NULL")){
    return std::make_pair(0.,0.);
  }
  std::ifstream fin(fullfilelist.Data());
  std::string word;

  if(fin.is_open()){
    while(getline (fin,word)){
      TFile * file = TFile::Open(word.c_str());
      TH1I* EventCounter_tmp = dynamic_cast<TH1I*> ((file ->Get("LJFilter/EventCount/EventCount"))->Clone());

      if(!EventCounter_tmp) throw LQError( "LJFilter/EventCount/EventCount NOT found!!!",   LQError::StopExecution );
      
      EventCounter->Add(EventCounter_tmp);
      file->Close();
      delete file;
      delete EventCounter_tmp;
    }
    fin.close();
  }
  
  total_events_beforeskim = EventCounter->GetBinContent(1);
  total_events_afterskim = EventCounter->GetBinContent(2);
  
  delete EventCounter;
  
  return std::make_pair(total_events_beforeskim ,total_events_afterskim);
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

void LQController::SetFullInputList(TString list){
  fullfilelist = list;
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
      
      GetMemoryConsumption("Added library " + libraryName);
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

  GetMemoryConsumption("Start of ExecuteCycle");
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
        
    GetMemoryConsumption("Initialised cycle class: " + cycleName );
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
    GetMemoryConsumption("Created TChain");

    //// Connect chain to Data class
    cycle->Init(chain);        

    GetMemoryConsumption("Connected All Branches");
    
    /// We can now check 
    // a) is this Data?
    // b) how many events in sample

    /// tell base ntuple code if sample is data or MC 
    if(inputType!=NOTSET) {
      // This is if set by user:
      if(inputType == data) cycle->SetDataType(true);
      if(inputType == mc) cycle->SetDataType(false);
      throw LQError( "InputType is wrongly configured",LQError::SkipCycle);
    }
    else{

      /// Get answer from input ntuple
      cycle->GetInputTree()->GetEntry(1,0);/// Get first entry in ntuple
      bool alt_isdata =  cycle->isData;
      if(alt_isdata) inputType = data;
      else inputType = mc;
      cycle->SetDataType(alt_isdata);
      GetMemoryConsumption("Accessed branch to specify isData");
    }
    /// Call BeginCycle by hand
    cycle->BeginCycle(completename);
    GetMemoryConsumption("Ran Begin Cycle");


    Long64_t nentries = cycle->GetNEntries(); /// This is total number of events in Input list
    if(n_ev_to_skip > nentries) n_ev_to_skip =0;
    
    
    std::pair<double, double> SampleEvents = GetTotalEvents();
    double sample_entries =  SampleEvents.first;
    double sample_entries_afterskim =  SampleEvents.second;    
    
    if(sample_entries!=0){
      m_logger << INFO << "Input sample has: " << LQLogger::endmsg;    
      m_logger <<INFO << "Before Skim:"  << sample_entries << " entries"  << LQLogger::endmsg;
      m_logger <<INFO << "After Skim:"  << sample_entries_afterskim << " entries"  << LQLogger::endmsg;
      cycle->SetNSampleEvents(sample_entries_afterskim);

      if(n_total_event == -1.){
	/// This is incase effective luminosity of mc is not set
	n_total_event = sample_entries;
      }
      GetMemoryConsumption("Check Number of events in sample");    
      std::getchar();
    }
    
    // calculate weight from input 
    float ev_weight =  CalculateWeight();
    
    GetMemoryConsumption("Calculated Weight");
    // Set number of event
    if(nevents_to_process > nentries || (nevents_to_process == -1) ) nevents_to_process = nentries;
    else if( nevents_to_process <=0) throw LQError( "nevents_to_process  is wrongly configured",LQError::SkipCycle);
    else {
      ev_weight *= (nentries/nevents_to_process);
      if(inputType == mc) m_logger << INFO << "Weight is recalculated. Since user set a specific number of entries" << LQLogger::endmsg;
      if(inputType == data) m_logger << WARNING << "Weight is recalculated. Since user set a specific number of entries" << LQLogger::endmsg;
    }
    
    if(list_to_run.size()!=0){
      for(unsigned int list_entry = 0; list_entry < list_to_run.size(); list_entry++){
	cycle->SetUpEvent(list_entry);
	cycle->BeginEvent(ev_weight);
	cycle->ExecuteEvents();
	cycle->EndEvent();
      }/// list loop
    }/// check size of list loop
    else{
      for (Long64_t jentry = n_ev_to_skip; jentry < nevents_to_process; jentry++ ) {            
	
	/// This connects the correct entries for each active branch
	cycle->SetUpEvent(jentry);
	/// 
	cycle->BeginEvent(ev_weight);   
	/// executes analysis code
	cycle->ExecuteEvents();
	// cleans up any pointers etc.
	cycle->EndEvent();
      }
    }

    cycle->EndCycle();
    GetMemoryConsumption("Finished Running Cycle");
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
 


float LQController::CalculateWeight() throw(LQError) {
  
  // First check that sample is MC
  if(inputType == NOTSET){
    throw LQError( "inputType is failed to be set!!",   LQError::StopExecution );
    return 1.;
  }
  if(inputType == data) return 1.;
  
  //
  // Calculate weight for MC
  //
  if(target_luminosity != 1. || effective_luminosity != 1.){
    if(target_luminosity == 1. ) m_logger << WARNING << "Target_luminosity is set to 1. while effective_luminosity is not. Is this correct?" <<LQLogger::endmsg;
    if(effective_luminosity == 1. ) m_logger << WARNING <<"Effective_luminosity is set to 1. while target_luminosity is not. Is this correct?" <<LQLogger::endmsg;    
    return (target_luminosity/effective_luminosity);
  }
  
  
  if(n_total_event != 0){
    if(sample_crosssection  ==999.) m_logger << WARNING <<" SetTotalMCEvents was set but no xsec is given as input" <<LQLogger::endmsg;
  }
  else {
    m_logger << WARNING <<"Total number of sample events is being used to calculate MC event weight:"<<LQLogger::endmsg;
    m_logger << ERROR  <<"n_total_event is not configuured "<<LQLogger::endmsg;
    m_logger << WARNING <<"You can use SetFullInputFileList("") or SetTotalMCEvents(int) to configure this" <<LQLogger::endmsg;
  }
  
  if(sample_crosssection != 999.&& n_total_event != -1.){
    return (target_luminosity* sample_crosssection / n_total_event);
  }
  
  m_logger << INFO << "Weight is set to 1. by default. This is ONLY correct for data. " << LQLogger::endmsg;
  return 1.;
}


void LQController::GetMemoryConsumption(TString label){

  ProcInfo_t procinfo;
  gSystem->GetProcInfo( &procinfo );
  m_logger << DEBUG << "Memory consumption at: " << label << LQLogger::endmsg;
  m_logger.setf( std::ios::fixed );
  m_logger << DEBUG << "  Resident mem.: " << std::setw( 7 ) << procinfo.fMemResident
	   << " kB; Virtual mem.: " << std::setw( 7 ) << procinfo.fMemVirtual
	   << " kB" << LQLogger::endmsg;

}
