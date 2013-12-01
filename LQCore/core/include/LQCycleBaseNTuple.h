#ifndef LQCycleBaseNTuple_H
#define LQCycleBaseNTuple_H

class TTree;
class TFile;
class TString;
class TDirectory;
class TBranch;

#include <list>
#include "LQError.h"
#include "LQCycleBaseBase.h"

// forward declaration
class TH1F;

class LQCycleBaseNTuple :  public virtual LQCycleBaseBase{

public:
  LQCycleBaseNTuple();
  virtual ~LQCycleBaseNTuple();

  TFile*                m_outputFile;
  std::vector< TTree* > m_outputTrees;
  std::list< void* > m_outputVarPointers;  
  

  virtual void CreateOutputTrees(TFile* outputFile, TString name, TString title);
  virtual void FillOutTree();
  virtual void SaveOutputTrees( TDirectory* /*output*/ );
  virtual TTree* GetOutputTree( const char* treeName ) const;
  virtual void MakeOutPutFile(TString path, TString name= "NOTREE");
  
  void CloseFiles();
  void SetDataType(bool type);
  void SetNSampleEvents(double nev);
  void SetOutPutStep(int step);
  void SetNEventsToProcess(int nentries);
  void WriteCycleHists(TH1F* htime, TH1F* mem1, TH1F* mem2);
  
  /// Bool to tell if sample is data or MC in analysis code
  bool k_isdata;
  
  // How many entries in the fullsample
  double sample_entries;
  int output_interval;
  int events_to_process;
  /// Declare an output variable
  template< class T >
    TBranch* DeclareVariable( T& obj, const char* name,
			       const char* treeName = 0 ) throw( LQError );
 private:
  static const char* RootType( const char* typeid_type ) ;

  ClassDef( LQCycleBaseNTuple, 0 );
  
};

// Don't include the templated function(s) when we're generating
// a dictionary:
#ifndef __CINT__
#include "LQCycleBaseNTuple.icc"
#endif

#endif