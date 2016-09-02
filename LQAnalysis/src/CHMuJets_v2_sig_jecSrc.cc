// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQCHMuJets_v2_sig Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @Author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "CHMuJets_v2_sig_jecSrc.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"
#include "BaseSelection.h"
#include "TTFitter.h"

#include <iostream>
#include <TROOT.h>
#include <TMinuit.h>


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (CHMuJets_v2_sig_jecSrc);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
CHMuJets_v2_sig_jecSrc::CHMuJets_v2_sig_jecSrc() :  AnalyzerCore(),  out_electrons(0) {

	// To have the correct name in the log:
 
	SetLogName("CHMuJets_v2_sig_jecSrc");
	Message("In CHMuJets_v2_sig_jecSrc constructor", INFO);
	//
	// This function sets up Root files and histograms Needed in ExecuteEvents
	InitialiseAnalysis();
	myfit = new TTFitter();
}


void CHMuJets_v2_sig_jecSrc::InitialiseAnalysis() throw( LQError ) {
  
	/// Initialise histograms
  //	MakeHistograms("");  
	MakeHistograms("AbsoluteUp");
	MakeHistograms("AbsoluteDown");  
	MakeHistograms("HighPtUp");
	MakeHistograms("HighPtDown");
	MakeHistograms("SinglePionUp");
	MakeHistograms("SinglePionDown");
	MakeHistograms("TimeUp");
	MakeHistograms("TimeDown");
	MakeHistograms("RelJERUp");
	MakeHistograms("RelJERDown");
	MakeHistograms("RelFSRUp");
	MakeHistograms("RelFSRDown");
	MakeHistograms("RelPtUp");
	MakeHistograms("RelPtDown");
	MakeHistograms("RelStatUp");
	MakeHistograms("RelStatDown");
	MakeHistograms("PUDataMCUp");
	MakeHistograms("PUDataMCDown");
	MakeHistograms("PUPtUp");
	MakeHistograms("PUPtDown");
	MakeHistograms("PUBiasUp");
	MakeHistograms("PUBiasDown");

	//
	// You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO(3)/DEBUG(2)/WARNING 
	// You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
	//

	return;
}


void CHMuJets_v2_sig_jecSrc::ExecuteEvents()throw( LQError ){

  float default_weight = weight;

  int keep_event= ExecuteSystematics(9, "AbsoluteUp");
  weight = default_weight;
  keep_event= ExecuteSystematics(10, "AbsoluteDown");
  weight = default_weight;
  keep_event+=    ExecuteSystematics(11, "HighPtUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(12, "HighPtDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(13, "SinglePionUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(14, "SinglePionDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(15, "TimeUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(16, "TimeDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(17, "RelJERUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(18, "RelJERDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(19, "RelFSRUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(20, "RelFSRDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(21, "RelPtUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(22, "RelPtDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(23, "RelStatUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(24, "RelStatDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(25, "PUDataMCUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(26, "PUDataMCDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(27, "PUPtUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(28, "PUPtDown");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(29, "PUBiasUp");
  weight=default_weight;
  keep_event+=    ExecuteSystematics(30, "PUBiasDown");


  
  if(keep_event==0)throw LQError( "Fails basic cuts",  LQError::SkipEvent ); 
}

int CHMuJets_v2_sig_jecSrc::ExecuteSystematics(int method, TString label)throw( LQError ){
  
    
	m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
	m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
	//// CHECK EFFICIENCY OF CUTS

//	int run_number = eventbase->GetEvent().RunNumber();
//	int event_number = eventbase->GetEvent().EventNumber();

	//if (!(event_number ==23989066)){
		//throw LQError( "Fails basic cuts",  LQError::SkipEvent );		
		//coutjet << "run_n: " << run_number << ", event_n: " << event_number << endl;
	//} 

	//cout << "1" << endl;
  
	FillCutFlow(label,"NoCut", weight);
	FillHist(label,"Cuts",0,weight);
  
	// Beam Scraping Cut + HE/HB Cut
	if(!PassBasicTopEventCuts())  {
		throw LQError( "Fails basic cuts",  LQError::SkipEvent );
	}
	FillCutFlow(label,"EventCut", weight);
	FillHist(label,"Cuts",1,weight);
	
	// Vertex Cut
	if (!eventbase->GetEvent().HasGoodPrimaryVertex()) {
		throw LQError( "Fails Vertex Cut",  LQError::SkipEvent );
	}
	FillCutFlow(label,"VertexCut", weight);
	FillHist(label,"Cuts",2, weight);


	/// Trigger List 
	std::vector<TString> triggerslistMu;
	triggerslistMu.push_back("HLT_IsoMu24_eta2p1_v");

	if(!PassTrigger(triggerslistMu, prescale))  {
		throw LQError( "Fails Trigger cuts",  LQError::SkipEvent );
	}
	FillCutFlow(label,"TriggerCut",weight);
	FillHist(label,"Cuts",3, weight);

  
	/// Correct MC for pileup     
	float pileup_up_sys_factor = 1.;
	float pileup_down_sys_factor = 1.;
  
	if (MC_pu&&!k_isdata) {
		//cout << "weight: " << weight << ", PU_corr: " << reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0) << ", MCweight: " << MCweight << endl;
		weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;
		pileup_up_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
		pileup_down_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), -1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
	}
	m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

	FillHist(label,"Cuts",4,weight);
	FillCutFlow(label,"Pileup",weight);
	//////////////////////////////////////////////////////
	//////////// Select objetcs
	//////////////////////////////////////////////////////   


	Bool_t debug =false;
		
	/// ELECTRONS
	std::vector<snu::KElectron> electronTightColl;
	eventbase->GetElectronSel()->TopTightElectronSelection(electronTightColl,debug);
 
  
	std::vector<snu::KElectron> electronVetoColl;
	eventbase->GetElectronSel()->TopVetoElectronSelection(electronVetoColl,debug);

	/// MUONS
	std::vector<snu::KMuon> muonVetoColl;
	eventbase->GetMuonSel()->TopVetoMuonSelectionv1(muonVetoColl,debug);

	std::vector<snu::KMuon> muonTightColl;
	eventbase->GetMuonSel()->TopTightMuonSelectionv1(muonTightColl,debug);
 
	// JETS
	std::vector<snu::KJet> jetColl_lepveto;
	std::vector<snu::KJet> jetColl_lepveto_soft;
	
	if (method>4){
	  eventbase->GetJetSel()->SetPt(20.);
	  eventbase->GetJetSel()->SetEta(2.4);
	  eventbase->GetJetSel()->BasicSelection(jetColl_lepveto);
	  
	  eventbase->GetJetSel()->SetPt(5.);
	  eventbase->GetJetSel()->SetEta(2.5);
	  eventbase->GetJetSel()->BasicSelection(jetColl_lepveto_soft);
	}
	else{
	  eventbase->GetJetSel()->JetchsTopSelectionv1(jetColl_lepveto, muonVetoColl, electronVetoColl, method);
	  eventbase->GetJetSel()->JetchsTopUESelectionv1(jetColl_lepveto_soft, muonVetoColl, electronVetoColl,method);
	}
	
	
	snu::KEvent Evt = eventbase->GetEvent();
	
	int jetFlavour=0;
	
	std::vector<snu::KTruth> genBColl;
	eventbase->GetTruthSel()->Selection(genBColl);
	
	float toppt1=10000, toppt2=10000;
	bool found_top = false, found_atop = false;
	//snu::KParticle genP_topb, genP_atopb, genP_q1, genP_q2;
	//bool found_topb = false, found_atopb = false, found_q1 = false, found_q2 = false;
	
	// check four partons 	
	if (debug) cout << " GEN Coll Size = " << genBColl.size() << endl;
	
	
	if (debug){
	  cout << " Truth particle = " << genBColl.size() << endl;
	  
	  cout << "--------------------------------------------------" << endl;
	  cout << "Index" << '\t' << "PdgID" << '\t' << "Status" << '\t' << "Mother" << '\t' << "Pt" << '\t' << "Eta" << '\t' << "Phi" <<  endl;
	  cout << "--------------------------------------------------" << endl;
	}
	
	bool found_el = false;
	bool found_mu = false;
	bool found_tau = false;
	
	for (int i=0; i<(int)genBColl.size()-1; i++){
	  
	  if ( abs(genBColl.at(i).PdgId())==11 && genBColl.at(i).GenStatus() ==3 && abs(genBColl.at(genBColl.at(i).IndexMother()).PdgId()) == 24) found_el = true;
	  if ( abs(genBColl.at(i).PdgId())==13 && genBColl.at(i).GenStatus() ==3 && abs(genBColl.at(genBColl.at(i).IndexMother()).PdgId()) == 24) found_mu = true;
	  if ( abs(genBColl.at(i).PdgId())==15 && genBColl.at(i).GenStatus() ==3 && abs(genBColl.at(genBColl.at(i).IndexMother()).PdgId()) == 24) found_tau = true;
	  
	  if (debug){
	    cout << i << '\t' <<
	      genBColl.at(i).PdgId() << '\t' <<
	      genBColl.at(i).GenStatus() << '\t' <<
	      genBColl.at(i).IndexMother() << '\t' <<
				genBColl.at(i).Pt() << '\t' ;
	    if( i < 2 ){
	      cout << endl;
	      continue;
	    }
	    else{
	      cout << genBColl.at(i).Eta() << '\t' << 
		genBColl.at(i).Phi() << endl;
	    }		
	  }
	  else{
	    if( i < 2 ) continue;
		}
	  if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == 6){
	    toppt1 = genBColl.at(i).Pt();
	    found_top = true;
	  }
	  if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == -6){
	    toppt2 = genBColl.at(i).Pt();
	    found_atop = true;
	  }
	  
	  if (found_top && found_atop) break;
	}
	
	//	if (dilep>2) throw LQError( "Fails DiEl Gen Selection",  LQError::SkipEvent );

	if(found_el) FillHist(label,"Lep_flav",1,weight);
	if(found_mu) FillHist(label,"Lep_flav",2,weight);
	if(found_tau) FillHist(label,"Lep_flav",3,weight);
		
	float pt_reweight = 1.;
	// Only for ttbar events

	// print out warning for if we can't find top&atop in ttbar
	if (!k_isdata && found_top && found_atop){
		if (toppt1 <= 400 && toppt2 <= 400){
			float corr_toppt1 = exp(0.159-0.00141*toppt1);
			float corr_toppt2 = exp(0.159-0.00141*toppt2);		
			
			pt_reweight = sqrt(corr_toppt1*corr_toppt2);

			FillHist(label,"gen_top_pt",toppt1,weight);
			FillHist(label,"gen_atop_pt",toppt2,weight);
			FillHist(label,"gen_top_pt_reweight",toppt1,weight*pt_reweight);
			FillHist(label,"gen_atop_pt_reweight",toppt2,weight*pt_reweight);
			
			if (debug){
				cout << " " << endl;
				cout << "PT REWEIGHTING == " << toppt1 << " => " << corr_toppt1 << ", " << toppt2 << " => " << corr_toppt2 << endl;
				cout << " " << endl;
			}
		}
	}
	
	weight *= pt_reweight;	

	FillCutFlow(label,"TTReweight",weight);
	FillHist(label,"Cuts",5, weight);

	float jetPt[4], jetEta[4], jetFlav[4];

	float TopMuTriggerSF_up_syst_factor = 1.0;
	float TopMuTriggerSF_down_syst_factor = 1.0;
	float TopMuIDSF_up_syst_factor = 1.0;
	float TopMuIDSF_down_syst_factor = 1.0;
	float TopMuIsoSF_up_syst_factor = 1.0;
	float TopMuIsoSF_down_syst_factor = 1.0;

	if (!(muonTightColl.size()==1 && electronTightColl.size()==0)) throw LQError( "Fails 1 Tight muon",  LQError::SkipEvent );


	FillCutFlow(label,"OneTightLep",weight);
	FillHist(label,"Cuts",6, weight);
	snu::KMuon Mu = muonTightColl.at(0);
	float iso_mu = (Mu.SumIsoCHDR04() + std::max(0.0, Mu.SumIsoNHDR04() + Mu.SumIsoPHDR04() - 0.5* Mu.SumPUIsoR04()))/Mu.Pt();
	float eta_mu = Mu.Eta();
	if (iso_mu > 0.12) return 0;
	
	// behavior of loose muon efficiency...
	// Since we only understand tight leptons( in terms of efficiencies ), we may be should not apply cuts based on loose leptons?

	if (muonVetoColl.size() >1 ) throw LQError( "Fails muonVeto cuts",  LQError::SkipEvent );
	if (electronVetoColl.size() >0)  throw LQError( "Fails electronLoose cuts",  LQError::SkipEvent );


	FillCutFlow(label,"OtherLepVeto",weight);
	FillHist(label,"Cuts",7, weight);
		
	if (!k_isdata){
		// Get the muon trigger scale factor
		weight *= TopMuTriggerSF(Mu.Eta(), 0);
		TopMuTriggerSF_up_syst_factor = TopMuTriggerSF(Mu.Eta(), 1)/TopMuTriggerSF(Mu.Eta(), 0);
		TopMuTriggerSF_down_syst_factor = TopMuTriggerSF(Mu.Eta(), -1)/TopMuTriggerSF(Mu.Eta(), 0);			
		// Get the muon ID scale factor
		weight *= TopMuIDSF(Mu.Eta(), 0);
		TopMuIDSF_up_syst_factor = TopMuIDSF(Mu.Eta(), 1)/TopMuIDSF(Mu.Eta(), 0);
		TopMuIDSF_down_syst_factor = TopMuIDSF(Mu.Eta(), -1)/TopMuIDSF(Mu.Eta(), 0);			
		// ID / Iso separate
		// Get the muon ISO scale factor		
		weight *= TopMuIsoSF(Mu.Eta(), 0);
		TopMuIsoSF_up_syst_factor = TopMuIsoSF(Mu.Eta(), 1)/TopMuIsoSF(Mu.Eta(), 0);
		TopMuIsoSF_down_syst_factor = TopMuIsoSF(Mu.Eta(), -1)/TopMuIsoSF(Mu.Eta(), 0);	
	}

	FillCutFlow(label,"LepSF",weight);		
	FillHist(label,"Cuts",8, weight);

	int njets = (int)jetColl_lepveto.size();
	int snjets = (int)jetColl_lepveto_soft.size();
		

	/// Here set any variables to -999. that you do not want filling in ntuple... 
	/// 
	if (jetColl_lepveto.size()<4) return 0;//  throw LQError( "Fails 4jets cuts",  LQError::SkipEvent );
	
	FillCutFlow(label,"FourJets",weight);
	FillHist(label,"Cuts",9, weight);

	int nbtags = 0;
	int nbtags_tot = 0;
	TLorentzVector jets_f[4];
	float jetErr_f[4];
	int btag_f[4] = {0,0,0,0};
	//		double btag_cor[2][4];
	//		double detEta_f[4];
	//		double jetErr_f[4];
		
	TLorentzVector jets_all[njets];
	int jetFlav_all[njets];
	int btag_all[njets];
	float jetPt_all[njets];
	float jetEta_all[njets];

	int FourJ_count = 0;
	
	if (debug){

	  cout << " ===== Start checking L5uncertainty ===== " << endl;
	  cout << " Jet Pt B-up " << GetJECUncertainty("FlavorPureBottom",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),true) <<  " -> " << endl;
	  cout << " Jet Pt B-down " << GetJECUncertainty("FlavorPureBottom",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),false) <<  " -> " << endl;
	  cout << " Jet Pt C-up " << GetJECUncertainty("FlavorPureCharm",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),true) <<  " -> " << endl;
	  cout << " Jet Pt C-down " << GetJECUncertainty("FlavorPureCharm",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),false) <<  " -> " << endl;
	  cout << " Jet Pt G-up " << GetJECUncertainty("FlavorPureGluon",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),true) <<  " -> " << endl;
	  cout << " Jet Pt G-down " << GetJECUncertainty("FlavorPureGluon",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),false) <<  " -> " << endl;
	  cout << " Jet Pt UDS-up " << GetJECUncertainty("FlavorPureQuark",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),true) <<  " -> " << endl;
	  cout << " Jet Pt UDS-down " << GetJECUncertainty("FlavorPureQuark",jetColl_lepveto.at(0).Eta(),jetColl_lepveto.at(0).Pt(),false) <<  " -> " << endl;

	}

	double realshift = 0;
	for(unsigned int ij=0; ij < jetColl_lepveto.size(); ij++){
	  
	  int this_idx = ij;
	  // This part is modified for the flavour uncertainty

	  double jet_btag = jetColl_lepveto.at(this_idx).CombinedSecVertexBtag();
	  jetFlavour = fabs(jetColl_lepveto.at(this_idx).PartonFlavour());
	  
	  
	  float jet_pt = jetColl_lepveto.at(this_idx).Pt();
	  float jet_eta = jetColl_lepveto.at(this_idx).Eta();
	  
	  if (debug) cout << "  SOFT JETS? = " << jet_pt << "  & eta = " << jet_eta << endl;

	  if (jet_pt <5 || jet_pt>10000) continue;
	  if (fabs(jet_eta)>2.5) continue;
	  if (fabs(jet_eta)<0.001) jet_eta = 0.;

	  if (debug)		cout << " Jet Pt org " << jet_pt << endl;
	  if(method == 1) jet_pt = jetColl_lepveto.at(this_idx).ScaledUpPt();
	  if(method == 2) jet_pt = jetColl_lepveto.at(this_idx).ScaledDownPt();
	  if(method == 3) jet_pt = jetColl_lepveto.at(this_idx).SmearedUpPt(); 
	  if(method == 4) jet_pt = jetColl_lepveto.at(this_idx).SmearedDownPt(); 

	  if (method ==5 && (jetFlavour == 5)){// B-up
	    jet_pt *= (1+GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,true)) ;
	    if (debug)
	      cout << " Jet Pt B-up " << GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    
	  }
	  if (method == 6 && jetFlavour == 5){ // B-down
	    jet_pt *= (1-GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,false)) ;
	    if (debug)
	      cout << " Jet Pt B-down " << GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	  }
	  if (method==7 && jetFlavour != 5){// UDSCG-up
	    if (jetFlavour == 4){ // charm
	      jet_pt *= (1+GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jet Pt C-up " << GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	    else if (jetFlavour == 0 || jetFlavour >6){ // gluon
	      jet_pt *= (1+GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jet Pt G-up " << GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	    else{ // UDS
	      jet_pt *= (1+GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jet Pt UDS-up " << GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	  }
	  if (method==8){// UDSCG-down
	    if (jetFlavour == 4){ // charm
	      jet_pt *= (1-GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt C-down " << GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	    else if (jetFlavour == 0 || jetFlavour > 6){ // gluon
	      jet_pt *= (1-GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt G-up " << GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	    else{ // UDS
	      jet_pt *= (1-GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt UDS-up " << GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	  }
	  else if (method == 9){ //  Absolute Up
	    if (debug){
	      cout << " Abs Stat Up = " << GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,true) << endl;
	      cout << " Abs Scale Up = " << GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,true) << endl;
	      cout << " Abs Flav Up = " <<  GetJECUncertainty("AbsoluteFlavMap",jet_eta,jet_pt,true) << endl;
	      cout << " Abs MPF Up = " <<  GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));
	    realshift += fabs(tempUnc);

	    if(debug){
	      cout << " corrPt ABS Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 10){ // Absolute Down
	    if (debug){
	      cout << " Abs Stat Down = " << GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,false) << endl;
	      cout << " Abs Scale Down = " << GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,false) << endl;
	      cout << " Abs Flav Down = " <<  GetJECUncertainty("AbsoluteFlavMap",jet_eta,jet_pt,false) << endl;
	      cout << " Abs MPF Down = " <<  GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    
	    if (debug){
	      cout << " corrPt ABS Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 11){ // HighPt Up

	    float Unc =  GetJECUncertainty("HighPtExtra",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " High Pt Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 12){ // HighPt Down

	    float Unc =  GetJECUncertainty("HighPtExtra",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " High Pt Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 13){ // SinglePion Up

	    float Unc =  pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true), 2);
	    Unc += pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true), 2);
	      
	    if (debug){
	      cout << " SinglePionECAL Up = " << GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true)  <<  endl;
	      cout << " SinglePionHCAL Up = " << GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,true)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1+sqrt(Unc) ) ;
	    realshift += fabs(Unc);
	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 14){ // SinglePion Down

	    float Unc =  pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,false), 2);
	    Unc +=  pow(GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,false), 2);
	    
	      
	    if (debug){
	      cout << " SinglePionECAL Down = " << GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,false)  <<  endl;
	      cout << " SinglePionHCAL Down = " << GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,false)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1-sqrt(Unc) ) ;
	    realshift += fabs(Unc);	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 15){ // Time Up

	    float Unc =  GetJECUncertainty("Time",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " Time Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 16){ // Time Down

	    float Unc =  GetJECUncertainty("Time",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " Time Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 17){ //  RelJER Up
	    if (debug){
	      cout << " RelJEREC1 Up = " << GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,true) << endl;
	      cout << " RelJEREC2 Up = " << GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,true) << endl;
	      cout << " RelJERHF Up = " <<  GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if(debug){
	      cout << " corrPt RELJER Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 18){ // RelJER Down
	    if (debug){
	      cout << " RelJEREC1 Down = " << GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,false) << endl;
	      cout << " RelJEREC2 Down = " << GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,false) << endl;
	      cout << " RelJERHF Down = " <<  GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if (debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 19){ // RelFSR Up

	    float Unc =  GetJECUncertainty("RelativeFSR",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " RelFSR Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 20){ // RelFSR Down

	    float Unc =  GetJECUncertainty("RelativeFSR",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " RelFSR Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 21){ //  RelPt Up
	    if (debug){
	      cout << " RelPtBB Up = " << GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtEC1 Up = " << GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtEC2 Up = " << GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtHF Up = " <<  GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if(debug){
	      cout << " corrPt RELPt Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 22){ // RelPt Down
	    if (debug){
	      cout << " RelPtEC1 Up = " << GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,false) << endl;
	      cout << " RelPtEC2 Up = " << GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,false) << endl;
	      cout << " RelPtHF Up = " <<  GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,false) <<  endl;
	      cout << " RelPtBB Up = " <<  GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if (debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 23){ // RelStat Up

	    float Unc =  pow(GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,true), 2);
	    Unc += pow(GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,true), 2);
	      
	    if (debug){
	      cout << " RelativeStat EC2 Up = " << GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,true)  <<  endl;
	      cout << " RelativeStat HF Up = " << GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,true)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1+sqrt(Unc) ) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 24){ // RelStat Down

	    float Unc =  pow(GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,false), 2);
	    Unc +=  pow(GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,false), 2);
	    
	      
	    if (debug){
	      cout << " RelativeStat EC2 Down = " << GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,false)  <<  endl;
	      cout << " RelativeStat HF Down = " << GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,false)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1-sqrt(Unc) ) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 25){ // PU DataMC Up

	    float Unc =  GetJECUncertainty("PileUpDataMC",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " PileupDataMC Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 26){ // PU DataMC Down

	    float Unc =  GetJECUncertainty("PileUpDataMC",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " PileupDataMC Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 27){ // PUPt Up
	    if (debug){
	      cout << " PUPtBB Up = " << GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,true) << endl;
	      cout << " PUPtEC Up = " << GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,true) << endl;
	      cout << " PUPtHF Up = " <<  GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if(debug){
	      cout << " corrPt RELJER Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 28){ // PUPt Down
	    if (debug){
	      cout << " PUPtBB Down = " << GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,false) << endl;
	      cout << " PUPtEC Down = " << GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,false) << endl;
	      cout << " PUPtHF Down = " <<  GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));
	    realshift += fabs(tempUnc);
	    if(debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 29){ // PU Bias Up

	    float Unc =  GetJECUncertainty("PileUpBias",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " PileupBias Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 30){ // PU Bias Down

	    float Unc =  GetJECUncertainty("PileUpBias",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " PileupBias Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;
	    realshift += fabs(Unc);
	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }


	  
	  if (jet_pt<= 30 || fabs(jet_eta)>2.4) continue;
	  
	  
	  TLorentzVector tempjet;
	  tempjet.SetPtEtaPhiE(jet_pt,jet_eta,jetColl_lepveto.at(this_idx).Phi(),jetColl_lepveto.at(this_idx).E());		
			
		if (jet_btag>0.679){
			nbtags_tot++;
			btag_all[FourJ_count] = 1;
		}
		else btag_all[FourJ_count] = 0;
			
		jetFlav_all[FourJ_count] = jetFlavour;
		jets_all[FourJ_count] = tempjet;
		jetPt_all[FourJ_count] = jet_pt;
		jetEta_all[FourJ_count] = jet_eta;

		if (FourJ_count<4){
			jets_f[FourJ_count] = tempjet;
			jetErr_f[FourJ_count] = jetColl_lepveto.at(this_idx).JECUncertainty();
			jetPt[FourJ_count] = jet_pt;
			jetEta[FourJ_count] = jet_eta;
			jetFlav[FourJ_count] = jetFlavour;

			if (jet_btag>0.679){
				btag_f[FourJ_count] = 1;
				nbtags++;
			}
			else btag_f[FourJ_count] = 0;
		}


		if (debug){
		  cout << "csv = " << jet_btag << btag_f[ij]<< endl;
		  cout << " Four Jets count ? " << FourJ_count << " in " << ij << "-th jets" << endl;
		}
		FourJ_count++;			
	}

	

	FillHist(label,"h_njets",FourJ_count,weight);
	if (realshift == 0) return 0;
	if (FourJ_count<4) return 0;
	njets = FourJ_count;

	float Bweight=1.0, BweightErr =1.0, Bweight_up=1.0, Bweight_down=1.0, Misweight_up=1.0, Misweight_down=1.0;

		
	enum {def, ttbar, st, VV, VJ, ttx, QCD};		
	if (!k_isdata)	fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,0,0,Bweight,BweightErr,ttbar);
	
	weight *= Bweight;
	if (!k_isdata)	fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,1,0,Bweight_up,BweightErr,ttbar);
	if (!k_isdata)	fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,-1,0,Bweight_down,BweightErr,ttbar);
	if (!k_isdata)	fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,0,1,Misweight_up,BweightErr,ttbar);
	if (!k_isdata)	fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,0,-1,Misweight_down,BweightErr,ttbar);
       		    

	TLorentzVector sum_jetraw(0,0,0,0);
	TLorentzVector addjets(0,0,0,0);

	float pt_corr_for_metx = 0;
        float pt_corr_for_mety = 0;
	
                                          
	for (int i=0; i<snjets; i++){
	  int this_idx = i;
	  if (debug) cout << " Check order = " << i << " vs " << this_idx << "/" << snjets << endl; 
	  
	  TLorentzVector tempjet_raw(0,0,0,0);
	  
	  tempjet_raw.SetPtEtaPhiM(jetColl_lepveto_soft.at(this_idx).RawPt(),jetColl_lepveto_soft.at(this_idx).Eta(),jetColl_lepveto_soft.at(this_idx).Phi(),0);
	  sum_jetraw += tempjet_raw;
	  
	  
	  float jet_pt = jetColl_lepveto_soft.at(this_idx).Pt();
	  float jet_eta = jetColl_lepveto_soft.at(this_idx).Eta();
	  
	  if(method == 1) jet_pt = jetColl_lepveto_soft.at(this_idx).ScaledUpPt(); 
	  if(method == 2) jet_pt = jetColl_lepveto_soft.at(this_idx).ScaledDownPt(); 
	  if(method == 3) jet_pt = jetColl_lepveto_soft.at(this_idx).SmearedUpPt(); 
	  if(method == 4) jet_pt = jetColl_lepveto_soft.at(this_idx).SmearedDownPt(); 
	  if (method ==5 && (jetFlavour == 5)){// B-up
	    jet_pt *= (1+GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,true)) ;
	    if (debug)
	      cout << " Jet Pt B-up " << GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    
	  }
	  if (method == 6 && jetFlavour == 5){ // B-down
	    jet_pt *= (1-GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,false)) ;
	    if (debug)
	      cout << " Jet Pt B-down " << GetJECUncertainty("FlavorPureBottom",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	  }
	  if (method==7 && jetFlavour != 5){// UDSCG-up
	    if (jetFlavour == 4){ // charm
	      jet_pt *= (1+GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jets Pt C-up " << GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	    else if (jetFlavour == 0 || jetFlavour > 6){ // gluon
	      jet_pt *= (1+GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jet Pt G-up " << GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	    else{ // UDS
	      jet_pt *= (1+GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,true)) ;
	      if (debug)
		cout << " Jet Pt UDS-up " << GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,true) <<  " -> " << jet_pt << endl;
	    }
	  }
	  if (method==8){// UDSCG-down
	    if (jetFlavour == 4){ // charm
	      jet_pt *= (1-GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt C-up " << GetJECUncertainty("FlavorPureCharm",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	    else if (jetFlavour == 0 || jetFlavour > 6){ // gluon
	      jet_pt *= (1-GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt G-up " << GetJECUncertainty("FlavorPureGluon",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	    else{ // UDS
	      jet_pt *= (1-GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,false)) ;
	      if (debug)
		cout << " Jet Pt UDS-up " << GetJECUncertainty("FlavorPureQuark",jet_eta,jet_pt,false) <<  " -> " << jet_pt << endl;
	    }
	  }
	  else if (method == 9){ //  Absolute Up
	    if (debug){
	      cout << " Abs Stat Up = " << GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,true) << endl;
	      cout << " Abs Scale Up = " << GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,true) << endl;
	      cout << " Abs Flav Up = " <<  GetJECUncertainty("AbsoluteFlavMap",jet_eta,jet_pt,true) << endl;
	      cout << " Abs MPF Up = " <<  GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));


	    if(debug){
	      cout << " corrPt ABS Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 10){ // Absolute Down
	    if (debug){
	      cout << " Abs Stat Down = " << GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,false) << endl;
	      cout << " Abs Scale Down = " << GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,false) << endl;
	      cout << " Abs Flav Down = " <<  GetJECUncertainty("AbsoluteFlavMap",jet_eta,jet_pt,false) << endl;
	      cout << " Abs MPF Down = " <<  GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("AbsoluteStat",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteScale",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("AbsoluteMPFBias",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));

	    if (debug){
	      cout << " corrPt ABS Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 11){ // HighPt Up

	    float Unc =  GetJECUncertainty("HighPtExtra",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " High Pt Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 12){ // HighPt Down

	    float Unc =  GetJECUncertainty("HighPtExtra",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " High Pt Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 13){ // SinglePion Up

	    float Unc =  pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true), 2);
	    Unc += pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true), 2);
	      
	    if (debug){
	      cout << " SinglePionECAL Up = " << GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,true)  <<  endl;
	      cout << " SinglePionHCAL Up = " << GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,true)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1+sqrt(Unc) ) ;
	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 14){ // SinglePion Down

	    float Unc =  pow(GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,false), 2);
	    Unc +=  pow(GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,false), 2);
	    
	      
	    if (debug){
	      cout << " SinglePionECAL Down = " << GetJECUncertainty("SinglePionECAL",jet_eta,jet_pt,false)  <<  endl;
	      cout << " SinglePionHCAL Down = " << GetJECUncertainty("SinglePionHCAL",jet_eta,jet_pt,false)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1-sqrt(Unc) ) ;
	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 15){ // Time Up

	    float Unc =  GetJECUncertainty("Time",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " Time Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 16){ // Time Down

	    float Unc =  GetJECUncertainty("Time",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " Time Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 17){ //  RelJER Up
	    if (debug){
	      cout << " RelJEREC1 Up = " << GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,true) << endl;
	      cout << " RelJEREC2 Up = " << GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,true) << endl;
	      cout << " RelJERHF Up = " <<  GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));

	    if(debug){
	      cout << " corrPt RELJER Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 18){ // RelJER Down
	    if (debug){
	      cout << " RelJEREC1 Down = " << GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,false) << endl;
	      cout << " RelJEREC2 Down = " << GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,false) << endl;
	      cout << " RelJERHF Down = " <<  GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativeJEREC1",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJEREC2",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativeJERHF",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));

	    if (debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 19){ // RelFSR Up

	    float Unc =  GetJECUncertainty("RelativeFSR",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " RelFSR Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 20){ // RelFSR Down

	    float Unc =  GetJECUncertainty("RelativeFSR",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " RelFSR Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-Unc) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 21){ //  RelPt Up
	    if (debug){
	      cout << " RelPtBB Up = " << GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtEC1 Up = " << GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtEC2 Up = " << GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,true) << endl;
	      cout << " RelPtHF Up = " <<  GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));

	    if(debug){
	      cout << " corrPt RELPt Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 22){ // RelPt Down
	    if (debug){
	      cout << " RelPtEC1 Up = " << GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,false) << endl;
	      cout << " RelPtEC2 Up = " << GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,false) << endl;
	      cout << " RelPtHF Up = " <<  GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,false) <<  endl;
	      cout << " RelPtBB Up = " <<  GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("RelativePtEC1",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtEC2",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtHF",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("RelativePtBB",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));

	    if (debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 23){ // RelStat Up

	    float Unc =  pow(GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,true), 2);
	    Unc += pow(GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,true), 2);
	      
	    if (debug){
	      cout << " RelativeStat EC2 Up = " << GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,true)  <<  endl;
	      cout << " RelativeStat HF Up = " << GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,true)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1+sqrt(Unc) ) ;
	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 24){ // RelStat Down

	    float Unc =  pow(GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,false), 2);
	    Unc +=  pow(GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,false), 2);
	    
	      
	    if (debug){
	      cout << " RelativeStat EC2 Down = " << GetJECUncertainty("RelativeStatEC2",jet_eta,jet_pt,false)  <<  endl;
	      cout << " RelativeStat HF Down = " << GetJECUncertainty("RelativeStatHF",jet_eta,jet_pt,false)  <<  endl;
	      
	      cout << " Change pT : " << jet_pt ;
	    }	
	    
	    jet_pt *= (1-sqrt(Unc) ) ;
	    
	    if (debug)
	      cout << " to = " << jet_pt << endl;
		       
	  }
	  else if (method == 25){ // PU DataMC Up

	    float Unc =  GetJECUncertainty("PileUpDataMC",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " PileupDataMC Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 26){ // PU DataMC Down

	    float Unc =  GetJECUncertainty("PileUpDataMC",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " PileupDataMC Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 27){ // PUPt Up
	    if (debug){
	      cout << " PUPtBB Up = " << GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,true) << endl;
	      cout << " PUPtEC Up = " << GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,true) << endl;
	      cout << " PUPtHF Up = " <<  GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,true) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,true),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,true),2); 
	    
	    jet_pt *= (1+sqrt(tempUnc));

	    if(debug){
	      cout << " corrPt RELJER Up = " << jet_pt << endl;
	    }
	  }
	  else if (method == 28){ // PUPt Down
	    if (debug){
	      cout << " PUPtBB Down = " << GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,false) << endl;
	      cout << " PUPtEC Down = " << GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,false) << endl;
	      cout << " PUPtHF Down = " <<  GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,false) <<  endl;
	    }

	    float tempUnc =  pow(GetJECUncertainty("PileUpPtBB",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtEC",jet_eta,jet_pt,false),2);
	    tempUnc+= pow( GetJECUncertainty("PileUpPtHF",jet_eta,jet_pt,false),2); 
	    
	    jet_pt *= (1-sqrt(tempUnc));

	    if(debug){
	      cout << " corrPt RELJER Down = " << jet_pt << endl;
	    }
	  }
	  else if (method == 29){ // PU Bias Up

	    float Unc =  GetJECUncertainty("PileUpBias",jet_eta,jet_pt,true);
	    if (debug)
	      cout << " PileupBias Up = " << Unc  <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1+fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }
	  else if (method == 30){ // PU Bias Down

	    float Unc =  GetJECUncertainty("PileUpBias",jet_eta,jet_pt,false);
	    if (debug)
	      cout << " PileupBias Down = " << Unc <<  ": Pt Changes = " << jet_pt ;
	    
	    jet_pt *= (1-fabs(Unc)) ;

	    if (debug)
	      cout << ", to = " << jet_pt << endl;
		       
	  }

	  if (jet_pt<= 10) continue;
	  
	  TLorentzVector tempjet(0,0,0,0);
	  tempjet.SetPtEtaPhiM(jet_pt,jet_eta,jetColl_lepveto_soft.at(this_idx).Phi(),0);
	  
	  pt_corr_for_metx += (tempjet.Px() - jetColl_lepveto_soft.at(this_idx).Px() );
	  pt_corr_for_mety += (tempjet.Py() - jetColl_lepveto_soft.at(this_idx).Py() );          
	  
	  addjets+=tempjet;
	  if (i<4)
	    addjets-= jets_f[i];
	  
	}
	
	double METx = Evt.PFMETx() - pt_corr_for_metx;	
        double METy = Evt.PFMETy() - pt_corr_for_mety;
	
        //      double METphi = Evt.PFMETphi();
	
        double METv = sqrt(METx*METx+METy*METy);
	
	
	if (METv<20) return 0;
	
	FillCutFlow(label,"MET>20",weight);
	FillHist(label,"Cuts",10, weight);
	
	
	
	if (nbtags<2)  return 0;//throw LQError( "Fails nbtag>0 cuts",  LQError::SkipEvent );
	
	
	if (METv>=20){
	  
	  if (nbtags == 1){
	    
            FillCutFlow(label,"1Bjet",weight);
            FillHist(label,"Cuts",11, weight);
	    
	  }
	  
	  else if (nbtags == 2){
            FillCutFlow(label,"2Bjets",weight);
            FillHist(label,"Cuts",12, weight);
	  }
	  
	  else{
	    
            FillCutFlow(label,">=3Bjets",weight);	    
            FillHist(label,"Cuts",13, weight);
	    
	  }
	}
	
	//
	// Lepton flavor uncertainty
	//
	/*
	cout << "JES UNC GetJECUncertainty(FlavorPureBottom, 2.2, 100.,true) = " << GetJECUncertainty("FlavorPureQuark", 2.2, 100.,true) << endl;
        cout << "JES UNC GetJECUncertainty(FlavorPureCharm, 2.2, 100.,true) = " << GetJECUncertainty("FlavorPureQuark", 2.2, 100.,true) << endl;
        cout << "JES UNC GetJECUncertainty(FlavorPureQuark, 5.2, 1000.,true) = " << GetJECUncertainty("FlavorPureQuark", 5.2, 1000.,true) << endl;
        cout << "JES UNC GetJECUncertainty(FlavorPureGluon, 0.1, 500.,true) = " << GetJECUncertainty("FlavorPureGluon", 0.1, 500.,true) << ends;        
	*/
	
	//
	// Inputs to the fitter
	//
	
	TLorentzVector Mu_vec;
	
        Mu_vec.SetPtEtaPhiE(Mu.Pt(),Mu.Eta(),Mu.Phi(),Mu.E());
	
	
        float sigmalep = 0.5*fabs(Evt.PFMET_Muon_EnUp()-METv) + 0.5*fabs(Evt.PFMET_Muon_EnDown()-METv);
	
        if (fabs(Mu.Eta())>1.5) sigmalep =  (sigmalep > 0.015*Mu_vec.Pt() ) ? sigmalep : 0.015*Mu_vec.Pt() ;  // Et difference is too small, so assign 1%
        else sigmalep =  (sigmalep > 0.01*Mu_vec.Pt() ) ? sigmalep : 0.01*Mu_vec.Pt() ;  // Et difference is too small, so assign 1%
	
         
	double METraw = Evt.PFMETRaw();
        double METrawphi = Evt.PFMETRawphi();
	
                                                    
	TLorentzVector met;
	met.SetPxPyPzE(METx,METy,0,METv); 	   
	TLorentzVector metraw;
	metraw.SetPxPyPzE(METraw*cos(METrawphi),METraw*sin(METrawphi),0,METraw); 	   

	int ntype = 14;	
	bool highpt_fit = true;

	myfit->Fit(Mu_vec,sigmalep,jets_f,btag_f,sum_jetraw,met,metraw, addjets,ntype, debug, highpt_fit);

	float get_bestchi2 = 9999;
	float get_bestHmass = 9999;
	int get_best = -1;

	for (int i=0; i<48; i++){
		if (!myfit->tagconsistent[i]) continue;
		float thischi = myfit->Chi2[i];

		bool tb_ptdiff = fabs(myfit->FittedJets[i][1].Pt()-myfit->jetsIN[i][1].Pt()) > 20. ? true:false;
		bool q1_ptdiff = fabs(myfit->FittedJets[i][2].Pt()-myfit->jetsIN[i][2].Pt()) > 20. ? true:false;	
		bool q2_ptdiff = fabs(myfit->FittedJets[i][3].Pt()-myfit->jetsIN[i][3].Pt()) > 20. ? true:false;
		bool atb_ptdiff = fabs(myfit->FittedJets[i][0].Pt() - myfit->jetsIN[i][0].Pt())> 20. ? true:false;

		bool mbjj_jetsIN = ((myfit->jetsIN[i][1]+myfit->jetsIN[i][2]+myfit->jetsIN[i][3]).M() > 200. )? true: false; 		

		if (debug){
			cout << " Check fitter goodness cut ==== " << endl;
			cout << " ptdiff = " << tb_ptdiff << ", " << q1_ptdiff << ", " << q2_ptdiff << ", " << atb_ptdiff << ", " << mbjj_jetsIN << endl;
		}
			
		if (!tb_ptdiff && !q1_ptdiff && !q2_ptdiff && !atb_ptdiff){
			if (!mbjj_jetsIN){
			    if (thischi<  get_bestchi2){
					get_bestchi2 = thischi;
					get_best = i;
					get_bestHmass = myfit->HMass[i];
			    }
			}
		}

		if (debug){ cout << "CHECKCHECKCHECK : " << i << ", chi2 = " << myfit->Chi2[i] << ", mH = " << myfit->HMass[i] << endl;
		}

	}

	if (debug){
		cout << " " << endl;
		cout << " Fit Result = " << get_best << ", chi2 = " << get_bestchi2 << ", mH = " << get_bestHmass << endl;
		cout << " " << endl;
	}

	TLorentzVector fit_atb, fit_tb, fit_q1, fit_q2;
	

	fit_atb = myfit->FittedJets[get_best][0];
//cout << " 3.1 "<< endl;
	fit_tb = myfit->FittedJets[get_best][1];
//cout << " 3.2 "<< endl;
	fit_q1 = myfit->FittedJets[get_best][2];
//cout << " 3.3 "<< endl;

	fit_q2 = myfit->FittedJets[get_best][3];
//cout << " 3.4 "<< endl;
//}	


/////

////////
	
	if(method == 0){
	  double vars[46];
	  if (!k_isdata){
	    vars[0] = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
	    vars[1] = pileup_up_sys_factor;	
	    vars[2] = pileup_down_sys_factor;
	    vars[3] = pt_reweight;
	    vars[4] = TopMuTriggerSF(eta_mu, 0);
	    vars[5] = TopMuTriggerSF_up_syst_factor;
	    vars[6] = TopMuTriggerSF_down_syst_factor;
	    vars[7] = TopMuIDSF(Mu.Eta(), 0);
	    vars[8] = TopMuIDSF_up_syst_factor;
	    vars[9] = TopMuIDSF_down_syst_factor;
	    vars[10] = TopMuIsoSF(Mu.Eta(), 0);
	    vars[11] = TopMuIsoSF_up_syst_factor;
	    vars[12] = TopMuIsoSF_down_syst_factor;
	    vars[13] = Bweight;
	    vars[14] = Bweight_up/Bweight;
	    vars[15] = Bweight_down/Bweight;
	    vars[16] = Misweight_up/Bweight;
	    vars[17] = Misweight_down/Bweight;
	  }
	  vars[18]=weight;	
	  vars[19]=Evt.nVertices();
	  vars[20]=METv;
	  vars[21]=nbtags;
	  vars[22]=nbtags_tot;
	  vars[23]=iso_mu;
	  vars[24]=eta_mu;
	  vars[25]=Mu.Pt();
	  vars[26]=jetPt[0];
	  vars[27]=jetEta[0];
	  vars[28]=jetFlav[0];
	  vars[29]=jetPt[1];
	  vars[30]=jetEta[1];
	  vars[31]=jetFlav[1];
	  vars[32]=jetPt[2];
	  vars[33]=jetEta[2];
	  vars[34]=jetFlav[2];
	  vars[35]=jetPt[3];
	  vars[36]=jetEta[3];
	  vars[37]=jetFlav[3];
	  vars[38]=njets;
	  vars[39]=toppt1;
	  vars[40]=toppt2;	  
	  vars[41]=btag_f[0];
	  vars[42]=btag_f[1];
	  vars[43]=btag_f[2];
	  vars[44]=btag_f[3];
	  vars[45] = get_bestHmass;

	  FillNtp("tuple_var",vars);
	}

	if(method>0){
	  double vars_syst[5];  
		vars_syst[0] = METv;
		vars_syst[1] = nbtags;
		vars_syst[2] = iso_mu;
		vars_syst[3] = get_bestHmass;
		vars_syst[4] = weight;
	  
	  FillNtp(label+"tuple_var",vars_syst);
	}

	
	
	return 1;
	
	
}// End of exeucte event loop



void CHMuJets_v2_sig_jecSrc::EndCycle()throw( LQError ){
  
	Message("In EndCycle" , INFO);
}


void CHMuJets_v2_sig_jecSrc::BeginCycle() throw( LQError ){
  
	Message("In begin Cycle", INFO);
  
	string analysisdir = getenv("FILEDIR");  
  
	if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());
	if(!k_isdata)    fBTagSF = new BTagSFUtil("CSVM");
	//	minuit = new TMinuit(nfit);
	//	const int nfit = 10;
	//
	//If you wish to output variables to output file use DeclareVariable
	// clear these variables in ::ClearOutputVectors function
	//DeclareVariable(obj, label, treename );
	//DeclareVariable(obj, label ); //-> will use default treename: LQTree
  

	return;
  
}

CHMuJets_v2_sig_jecSrc::~CHMuJets_v2_sig_jecSrc() {
  
	Message("In CHMuJets_v2_sig_jecSrc Destructor" , INFO);
	if(!k_isdata)delete reweightPU;
	if(!k_isdata) delete fBTagSF;
	//	delete minuit;
}
         
void CHMuJets_v2_sig_jecSrc::FillCutFlow(TString label,TString cut, float weight){
  
  TString cfname = "cutflow" + label;
	if(GetHist(cfname)) {
		GetHist(cfname)->Fill(cut,weight);
	}
	else{
		AnalyzerCore::MakeHistograms(cfname,14,0.,14.);
    
        GetHist(cfname)->GetXaxis()->SetBinLabel(1,"NoCut");
        GetHist(cfname)->GetXaxis()->SetBinLabel(2,"EventCut");
        GetHist(cfname)->GetXaxis()->SetBinLabel(3,"VertexCut");
        GetHist(cfname)->GetXaxis()->SetBinLabel(4,"TriggerCut");
        GetHist(cfname)->GetXaxis()->SetBinLabel(5,"Pileup");
        GetHist(cfname)->GetXaxis()->SetBinLabel(6,"TTReweight");
        
        GetHist(cfname)->GetXaxis()->SetBinLabel(7,"OneTightLep");
        GetHist(cfname)->GetXaxis()->SetBinLabel(8,"OtherLepVeto");
        GetHist(cfname)->GetXaxis()->SetBinLabel(9,"LepSF");
        GetHist(cfname)->GetXaxis()->SetBinLabel(10,"FourJets");
        GetHist(cfname)->GetXaxis()->SetBinLabel(11,"MET>20");
        GetHist(cfname)->GetXaxis()->SetBinLabel(12,"1Bjet");
        GetHist(cfname)->GetXaxis()->SetBinLabel(13,"2Bjets");
        GetHist(cfname)->GetXaxis()->SetBinLabel(14,">=3Bjets");
	}
}
     
void CHMuJets_v2_sig_jecSrc::BeginEvent( )throw( LQError ){

	Message("In BeginEvent() " , DEBUG);

	return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void CHMuJets_v2_sig_jecSrc::MakeHistograms(TString label){
	//// Additional plots to make
    
  if(label == ""){
    maphist.clear();
    AnalyzerCore::MakeHistograms();
    MakeNtp(label+"tuple_var","PU:PU_up:PU_down:pt:Trig:Trig_up:Trig_down:Id:Id_up:Id_down:Iso:Iso_up:Iso_down:Bweight:Bweight_up:Bweight_down:Misweight_up:Misweight_down:weight:nVer:MET:nbtags:nbtags_tot:iso_mu:eta_mu:pt_mu:pt_1:eta_1:flav_1:pt_2:eta_2:flav_2:pt_3:eta_3:flav_3:pt_4:eta_4:flav_4:njets:toppt1:toppt2:btag_f1:btag_f2:btag_f3:btag_f4:hm");
    
  }
  Message("Made histograms", INFO);
	/**
	 *  Remove//Overide this CHMuJets_v2_sig_jecSrcCore::MakeHistograms() to make new hists for your analysis
	 **/
  
  if(label != "") MakeNtp(label+"tuple_var","MET:nbtags:iso_mu:hm:weight");


  maphist["Cuts"+label] = new TH1F("Cuts"+label,"Cuts",40,0,40);  
  maphist["Lep_flav"+label] = new TH1F("Lep_flav"+label,"Lep_flav",5,0,5);
  maphist["h_njets"+label] = new TH1F("h_njets"+label,"#Jets with pT>30 GeV",10,0,10);
  
  maphist["gen_top_pt"+label] = new TH1F("gen_top_pt"+label,"gen_top_pt",80,0,400);
  maphist["gen_atop_pt"+label] = new TH1F("gen_atop_pt"+label,"gen_atop_pt",80,0,400);
  maphist["gen_top_pt_reweight"+label] = new TH1F("gen_top_pt_reweight"+label,"gen_top_pt_reweight",80,0,400);
  maphist["gen_atop_pt_reweight"+label] = new TH1F("gen_atop_pt_reweight"+label,"gen_atop_pt_reweight",80,0,400);
  

}


void CHMuJets_v2_sig_jecSrc::ClearOutputVectors() throw(LQError) {

	// This function is called before every execute event (NO need to call this yourself.
  
	// Add any new output vector you create to this list. 
	// if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
	//
	// Reset all variables declared in Declare Variable
	//
	out_muons.clear();
	out_electrons.clear();
}



void CHMuJets_v2_sig_jecSrc::mysort(std::vector<snu::KJet> jetColl_lepveto, int jet_index[]){

	/*	
	  cout << " ============= " << endl;
	  cout << " Inside mysort " << endl;
	  cout << " ============= " << endl;
	*/	
	int jsize = (int)jetColl_lepveto.size();
	
	//cout << " Jet Size = " << jsize << endl;

	for(int i=1; i<jsize; i++){

		for (int k=0; k<i; k++){
			int temp_idx = jet_index[k];
			
			if (jetColl_lepveto.at(jet_index[i]).Pt() > jetColl_lepveto.at(temp_idx).Pt() ){

				jet_index[k] = jet_index[i];
				jet_index[i] = temp_idx;
				continue;
			}			
		}			
	}
	return;

}



 

//  LocalWords:  masscuts jetResdown
