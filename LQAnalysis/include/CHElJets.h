#ifndef CHElJets_h
#define CHElJets_h

#include "AnalyzerCore.h"

#include <iostream>
#include <TROOT.h>
#include <TMinuit.h>

class CHElJets : public AnalyzerCore{ 

 public:
	//// constructors                                                                                                                                                             
	CHElJets();
	~CHElJets();

	/// Functions from core
	virtual void BeginCycle() throw( LQError );
	virtual void BeginEvent()throw( LQError );
	virtual void ExecuteEvents()throw( LQError );
	virtual void EndCycle()throw( LQError );
	virtual void ClearOutputVectors()throw( LQError );

	void InitialiseAnalysis() throw( LQError );
	void MakeHistograms();
	void FillCutFlow(TString cut, float w);

 private:

	//
	// The output variables 
	//
	/// Vectors for output objetcs
	std::vector<snu::KMuon> out_muons;
	std::vector<snu::KElectron> out_electrons;

	void mysort(std::vector<snu::KJet> jetColl,int jidx[]);
	void Sortout(float in1, float in2, float in3, float& out1, float& out2, float& out3);

	
	ClassDef ( CHElJets, 1);
};
#endif
