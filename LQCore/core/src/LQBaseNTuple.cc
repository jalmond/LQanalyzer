/// ROOT includes
#include <TROOT.h>
#include "TTree.h"
#include "TDirectory.h"
#include "TFile.h"
#include <TSystem.h>

#include <iostream>

//local  includes
#include "include/LQBaseNTuple.h"

LQBaseNTuple::LQBaseNTuple(){

}


LQBaseNTuple::~LQBaseNTuple(){

}

void LQBaseNTuple::CreateOutputTrees(TFile* outputFile, TString name, TString title){
  
  // Clear the vector of output trees:
  m_outputTrees.clear();
  
  // Clear the vector of output variable pointers:                             
  m_outputVarPointers.clear();

  // Open output file / create output trees 
  gROOT->cd();

  // Create all the regular output trees, but don't create any branches in them
  // just yet.
  //
  
  const Int_t branchStyle = 1;
  const Int_t autoSave = 10000000;
  
  TTree* tree = new TTree(name,title);
  tree->SetAutoSave( autoSave );
  TTree::SetBranchStyle( branchStyle );
  
  m_outputTrees.push_back( tree );
  
  if( outputFile ) {
    tree->SetDirectory( outputFile );
  }
  
  return;
}

void LQBaseNTuple::MakeOutPutFile(TString outfile, TString treename){
    
  m_outputFile = TFile::Open(outfile, "RECREATE");
  CreateOutputTrees(m_outputFile, treename , "");
  
}

void LQBaseNTuple::FillOutTree(){

  int nbytes = 0;
  for( std::vector< TTree* >::iterator tree = m_outputTrees.begin();
       tree != m_outputTrees.end(); ++tree ) {
    nbytes = ( *tree )->Fill();
    if( nbytes < 0 ) {
      //REPORT_ERROR( "Write error occured in tree \""
      //	    << ( *tree )->GetName() << "\"" );
    } else if( nbytes == 0 ) {
      //m_logger << WARNING << "No data written to tree \""
      //<< ( *tree )->GetName() << "\"" << SLogger::endmsg;
    }
  }
  

}

void LQBaseNTuple::GetMemoryConsumption(){
  // Print memory consumption after initialising the analysis:
  ProcInfo_t procinfo;
  gSystem->GetProcInfo( &procinfo );
  //m_logger << DEBUG << "Memory consumption after initialisation:" << SLogger::endmsg;
  //m_logger.setf( std::ios::fixed );
  //m_logger << DEBUG << "  Resident mem.: " << std::setw( 7 ) << procinfo.fMemResident
  //<< " kB; Virtual mem.: " << std::setw( 7 ) << procinfo.fMemVirtual
  //<< " kB" << SLogger::endmsg;
  
}


void LQBaseNTuple::SaveOutputTrees( TDirectory* /*output*/ ) {

  // Remember which directory we were in:                                                                  
  TDirectory* savedir = gDirectory;

  // Save each regular output tree:                                                                        
  for( std::vector< TTree* >::iterator tree = m_outputTrees.begin();
       tree != m_outputTrees.end(); ++tree ) {
    TDirectory* dir = ( *tree )->GetDirectory();
    if( dir ) dir->cd();
    ( *tree )->Write();
    ( *tree )->AutoSave();
    ( *tree )->SetDirectory( 0 );
    delete ( *tree );
  }

  // Go back to the original directory:                                                                    
  gDirectory = savedir;

  return;
}

TTree* LQBaseNTuple::GetOutputTree( const char* treeName ) const{
  
  // Look for such output tree:                                                
  //                                                                           
  TString tname( treeName );
  for( std::vector< TTree* >::const_iterator it = m_outputTrees.begin();
       it != m_outputTrees.end(); ++it ) {
    if( *it ) {
      if( tname == ( *it )->GetName() ) {
	return *it;
      }
    }
  }
  return 0;
}


const char* LQBaseNTuple::RootType( const char* typeid_type ){

  switch( typeid_type[ 0 ] ) {

  case 'c':
    return "B";
    break;
  case 'h':
    return "b";
    break;
  case 's':
    return "S";
    break;
  case 't':
    return "s";
    break;
  case 'i':
    return "I";
    break;
  case 'j':
    return "i";
    break;
  case 'f':
    return "F";
    break;
  case 'd':
    return "D";
    break;
  case 'x':
    return "L";
    break;
  case 'y':
    return "l";
    break;
  case 'b':
    return "O";
    break;

  }

  return "";
}
