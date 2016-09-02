#ifndef CHMuJets_v3_sig_h
#define CHMuJets_v3_sig_h

#include "AnalyzerCore.h"
//#include "BTagSFUtil.h"

#include <iostream>
#include <TROOT.h>
#include <TMinuit.h>

class CHMuJets_v3_sig : public AnalyzerCore{ 

 public:
	//// constructors                                                                                                                                                             
	CHMuJets_v3_sig();
	~CHMuJets_v3_sig();

	/// Functions from core
	virtual void BeginCycle() throw( LQError );
	virtual void BeginEvent()throw( LQError );
	virtual void ExecuteEvents()throw( LQError );
	virtual void EndCycle()throw( LQError );
	virtual void ClearOutputVectors()throw( LQError );
	int ExecuteSystematics(int mathod, TString label)throw( LQError ); 
	void FillCutFlow(TString label, TString cut, float w);           

	void InitialiseAnalysis() throw( LQError );
	void MakeHistograms();
		void MakeHistograms(TString label);
	void FillCutFlow(TString cut, float w);

 private:

	//
	// The output variables 
	//
	/// Vectors for output objetcs
	std::vector<snu::KMuon> out_muons;
	std::vector<snu::KElectron> out_electrons;

	void mysort(std::vector<snu::KJet> jetColl,int jidx[]);
	/*
	static void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);

	//internal to the fitter function
	static TLorentzVector fitneu;
	static TLorentzVector fitlep;
	static TLorentzVector fitjets[4];
	static TLorentzVector Wjj;
	static TLorentzVector hTop;
	static TLorentzVector Wlv;
	static TLorentzVector lTop;

	static TLorentzVector jetsIN[5][24][4];
	static TLorentzVector jetsRAW[5][24][4];
	static Double_t JetSigma[5][24][4];
	
	static TLorentzVector FittedJets[5][24][4];
	static TLorentzVector FittedLep[5][24];
	static TLorentzVector FittedNeu[5][24];
	
	static Double_t Mass[5][24];
	static Double_t HMass[5][24];
	static Double_t Chi2[5][24];
	static bool tagConstrained[5][24];
	static Int_t Nbtags[5][24];

	//internal fitter objects
	static TLorentzVector tjets[4];
	static Double_t tsigmajets[4];
	static TLorentzVector tlepton;
	static Double_t sigmalep;
	static TLorentzVector uncl;
	static Double_t sigmauncl;
	static TLorentzVector extraJets;

	static Double_t tsjetCorr[3][4];
	static Double_t sigmajets[3][4];
	*/
	
	ClassDef ( CHMuJets_v3_sig , 1);
};
#endif
