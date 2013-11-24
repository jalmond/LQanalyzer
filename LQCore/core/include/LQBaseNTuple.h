#ifndef LQBaseNTuple_H
#define LQBaseNTuple_H

class TTree;
class TFile;
class TString;
class TDirectory;

#include <list>

class LQBaseNTuple {

public:
  LQBaseNTuple();
  virtual ~LQBaseNTuple();

  TFile*                m_outputFile;
  std::vector< TTree* > m_outputTrees;
  std::list< void* > m_outputVarPointers;  

  void CreateOutputTrees(TFile* outputFile, TString name, TString title);
  void FillOutTree();
  void GetMemoryConsumption();
  void SaveOutputTrees( TDirectory* /*output*/ );
  virtual TTree* GetOutputTree( const char* treeName ) const;
  void MakeOutPutFile(TString path, TString name);

  static const char* RootType( const char* typeid_type ) ;
  
};
#endif
