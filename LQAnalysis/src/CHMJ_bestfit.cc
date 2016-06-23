

// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQCHMJ_bestfit Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "CHMJ_bestfit.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"
#include "TTFitter.h"

#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (CHMJ_bestfit);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
CHMJ_bestfit::CHMJ_bestfit() :  AnalyzerCore(),  out_electrons(0) {

	// To have the correct name in the log:
	
	SetLogName("CHMJ_bestfit");

	Message("In CHMJ_bestfit constructor", INFO);
	//
	// This function sets up Root files and histograms Needed in ExecuteEvents
	InitialiseAnalysis();
   
}

void CHMJ_bestfit::InitialiseAnalysis() throw( LQError ) {
  
	/// Initialise histograms
	MakeHistograms();  
	//
	// You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO(3)/DEBUG(2)/WARNING 
	// You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;

	return;
}

void CHMJ_bestfit::ExecuteEvents()throw( LQError ){


	m_logger << 2 << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
	m_logger << 2 << "isData = " << isData << LQLogger::endmsg;
  
	//// CHECK EFFICIENCY OF CUTS

	//	int evtn = eventbase->GetEvent().EventNumber();

	//if (evtn != 44 && evtn != 850 && evtn != 441)  return;

	FillCutFlow("NoCut", weight);
  
	if(!PassBasicTopEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
	FillCutFlow("EventCut", weight);
	/// Trigger List 
	std::vector<TString> triggerslistEl;

	triggerslistEl.push_back("HLT_IsoMu24_eta2p1_v");

	//// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
	if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
	FillCutFlow("VertexCut", weight);
  
	/// Correct MC for pileup     
	float pileup_up_sys_factor = 1.;
	float pileup_down_sys_factor = 1.;
  
	if (MC_pu&&!k_isdata) {
		weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;

		pileup_up_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
		pileup_down_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), -1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
	}

	m_logger << 2 << "reweighted pileup "<< LQLogger::endmsg;
	FillCutFlow("Pileup",weight);
	
	//////////////////////////////////////////////////////
	//////////// Select objetcs
	//////////////////////////////////////////////////////   

	Bool_t debug = false;
		
	/// ELECTRONS
	std::vector<snu::KElectron> electronTightColl;
	eventbase->GetElectronSel()->TopTightElectronSelection(electronTightColl,debug);
 
  	std::vector<snu::KElectron> electronLooseColl;   
    eventbase->GetElectronSel()->TopLooseElectronSelection(electronLooseColl,debug);

  	std::vector<snu::KElectron> electronVetoColl;   
    eventbase->GetElectronSel()->TopVetoElectronSelection(electronVetoColl,debug);

	/// MUONS
	std::vector<snu::KMuon> muonTightColl;
	eventbase->GetMuonSel()->TopTightMuonSelection(muonTightColl,debug);

	std::vector<snu::KMuon> muonLooseColl;     
    eventbase->GetMuonSel()->TopLooseMuonSelection(muonLooseColl,debug);                 

	std::vector<snu::KMuon> muonVetoColl;     
    eventbase->GetMuonSel()->TopVetoMuonSelection(muonVetoColl,debug);                 

	/// Jets
	std::vector<snu::KJet> jetColl;          
    eventbase->GetJetSel()->JetchsTopSelection(jetColl, muonTightColl, electronTightColl);  

	std::vector<snu::KJet> jetColl_UE;
    eventbase->GetJetSel()->JetchsTopUESelection(jetColl_UE, muonTightColl, electronTightColl); 

	
	snu::KEvent Evt = eventbase->GetEvent();
	double METv = Evt.PFMET();
	double METphi = Evt.PFMETphi();

	double METraw = Evt.PFMETRaw();
	double METrawphi = Evt.PFMETRawphi();

	int jetFlavour=0;


	std::vector<snu::KTruth> genBColl;
	eventbase->GetTruthSel()->Selection(genBColl);
	
	float toppt1=10000, toppt2=10000;
	bool found_top = false, found_atop = false;
	//snu::KParticle genP_topb, genP_atopb, genP_q1, genP_q2;
	//bool found_topb = false, found_atopb = false, found_q1 = false, found_q2 = false;
	
	// check four partons
	if (!k_isdata){
		if (debug) cout << " GEN Coll Size = " << genBColl.size() << endl;
		
		
		if (debug){
			cout << " Truth particle = " << genBColl.size() << endl;
			
			cout << "--------------------------------------------------" << endl;
			cout << "Index" << '\t' << "PdgID" << '\t' << "Status" << '\t' << "Mother" << '\t' << "Pt" << '\t' << "Eta" << '\t' << "Phi" <<  endl;
			cout << "--------------------------------------------------" << endl;
		}
		
		
		for (int i=0; i<(int)genBColl.size()-1; i++){
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
		
		
		// Only for ttbar events
		if (found_top && found_atop){
			if (toppt1 <= 400 && toppt2 <= 400){
				float corr_toppt1 = exp(0.159-0.00141*toppt1);
				float corr_toppt2 = exp(0.159-0.00141*toppt2);		
				
				weight *= sqrt(corr_toppt1*corr_toppt2);
				
				if (debug){
					cout << " " << endl;
					cout << "PT REWEIGHTING == " << toppt1 << " => " << corr_toppt1 << ", " << toppt2 << " => " << corr_toppt2 << endl;
					cout << " " << endl;
				}
			}
		}
	}

	FillCutFlow("TTReweight",weight);

	if(!PassTrigger(triggerslistEl, prescale))  throw LQError( "Fails Trigger cuts",  LQError::SkipEvent );

	if (debug){
		cout << " Pass Trigger Cut " << endl;
		cout << " Mu size = " << muonTightColl.size()<< endl;
	}

	FillCutFlow("TriggerCut",weight);
	if (debug) cout << " Trigger SF Weight " << endl;

	
	if (muonTightColl.size() != 1) throw LQError( "Fails Mu Cut",  LQError::SkipEvent );
	snu::KMuon Mu = muonTightColl.at(0);

	float TopMuTriggerSF_up_syst_factor = 1.0;
	float TopMuTriggerSF_down_syst_factor = 1.0;
	float TopMuIDSF_up_syst_factor = 1.0;
	float TopMuIDSF_down_syst_factor = 1.0;
	float TopMuIsoSF_up_syst_factor = 1.0;
	float TopMuIsoSF_down_syst_factor = 1.0;
	
	if (!k_isdata){

		float temp_tr = TopMuTriggerSF(Mu.Eta(), 0);
		weight *= temp_tr;

		TopMuTriggerSF_up_syst_factor = TopMuTriggerSF(Mu.Eta(), 1)/temp_tr;
		TopMuTriggerSF_down_syst_factor = TopMuTriggerSF(Mu.Eta(), -1)/temp_tr;
		
		// Get the muon ID scale factor
		float temp_muid = TopMuIDSF(Mu.Eta(), 0);
		weight *= temp_muid;
		
		TopMuIDSF_up_syst_factor = TopMuIDSF(Mu.Eta(), 1)/temp_muid;
		TopMuIDSF_down_syst_factor = TopMuIDSF(Mu.Eta(), -1)/temp_muid;
		
		// Get the muon ISO scale factor		
		float temp_muiso =TopMuIsoSF(Mu.Eta(), 0); 
		weight *= temp_muiso;

		TopMuIsoSF_up_syst_factor = TopMuIsoSF(Mu.Eta(), 1)/temp_muiso;
		TopMuIsoSF_down_syst_factor = TopMuIsoSF(Mu.Eta(), -1)/temp_muiso;
			
	}

	
	FillCutFlow("OneTightMu",weight);

	if (muonVetoColl.size() >1) throw LQError( "Fails electronLoose cuts",  LQError::SkipEvent );
		
	FillCutFlow("ExtraMuVeto",weight);

	if (electronVetoColl.size()>0)  throw LQError( "Fails muonLoose cuts",  LQError::SkipEvent );	

	FillCutFlow("ElVeto",weight);


	
	
	int const njets = (int)jetColl.size();
	int snjets = (int)jetColl_UE.size();

	if (debug) cout << " NJets = " << njets << " : soft jets " << snjets << endl;
	
	float jetPt[njets], jetEta[njets], jetFlav[njets];

	if (debug){
		cout << " Num jets : " << jetColl.size() << endl;
		cout << " Num soft jets : " << jetColl_UE.size() << endl;
	}
	
	FillHist("h_njets",(int)jetColl.size(),weight);
	FillHist("h_snjets",(int)jetColl_UE.size(),weight);

	
	int jidx[njets];
	int sjidx[snjets];
	
	for (int i=0; i<njets; i++){
		jidx[i] = i;
	}                    
	
	for (int i=0; i<snjets; i++){
		sjidx[i] = i;
	}
	
	// Check jet pt ordering
	mysort(jetColl,jidx);
	mysort(jetColl_UE,sjidx);
	
	
	if (jetColl.size()<4)  throw LQError( "Fails 4jets cuts",  LQError::SkipEvent );

	FillCutFlow("FourJets",weight);
	FillHist("h_mu_pt_4jets",Mu.Pt(),weight);
	FillHist("h_met_4jets",METv,weight);


	int nbtags_tot = 0;
	int nbtags_f = 0;

	TLorentzVector jets_f[4];
	int jetFlav_f[4] = {0,0,0,0};
	int btag_f[4] = {0,0,0,0};
	float jetPt_f[4];
	float jetEta_f[4];
	
	TLorentzVector jets_all[njets];
	int jetFlav_all[njets];
	int btag_all[njets];
	float jetPt_all[njets];
	float jetEta_all[njets];

	
	for (int i=0; i<njets; i++){

		int this_idx = jidx[i];
		if (debug) cout << " This index = " << this_idx << endl;
		
		TLorentzVector tempjet(0,0,0,0);		   
		tempjet.SetPtEtaPhiE(jetColl.at(this_idx).Pt(),jetColl.at(this_idx).Eta(),jetColl.at(this_idx).Phi(),jetColl.at(this_idx).E());
		int jetFlavour = jetColl.at(this_idx).PartonFlavour();	
		double jet_btag = jetColl.at(this_idx).CombinedSecVertexBtag();
	
		if (jet_btag>0.679){
			nbtags_tot++;
			btag_all[i] = 1;
			if (i<4){
				btag_f[i] = 1;
				nbtags_f++;
			}
		}
		else{
			btag_all[i] = 0;		       
		}

		jetFlav_all[i] = fabs(jetFlavour);
		jets_all[i] = tempjet;
		jetPt_all[i] = jetColl.at(this_idx).Pt();
		jetEta_all[i] = jetColl.at(this_idx).Eta();
		
		if (i<4){

			jetFlav_f[i] = fabs(jetFlavour);
			jets_f[i] = tempjet;
			std::cout << "tempjet pt = " <<  tempjet.Pt() << "  eta = " << tempjet.Eta() << endl;
			jetPt_f[i] = jetColl.at(this_idx).Pt();
			jetEta_f[i] = jetColl.at(this_idx).Eta();	   

		}

		
	}


	FillHist("h_nbjets_tot",nbtags_tot,weight);
	FillHist("h_nbjets_f",nbtags_f,weight);
	
	if (nbtags_tot>=2){
		FillCutFlow("2bJets",weight);
		FillHist("h_mu_pt_2b",Mu.Pt(),weight);
		FillHist("h_met_2b",METv,weight);
		FillHist("h_njets_2b",njets,weight);
		
		if (nbtags_tot>2){
			FillCutFlow("3bJets",weight);
			FillHist("h_mu_pt_3b",Mu.Pt(),weight);
			FillHist("h_met_3b",METv,weight);
			FillHist("h_njets_3b",njets,weight);
		}
	}

	if (nbtags_f>=2){
		FillCutFlow("2bJets_f",weight);
		FillHist("h_mu_pt_2b_f",Mu.Pt(),weight);
		FillHist("h_met_2b_f",METv,weight);
		FillHist("h_njets_2b_f",njets,weight);
		
		if (nbtags_f>2){
			FillCutFlow("3bJets_f",weight);
			FillHist("h_mu_pt_3b_f",Mu.Pt(),weight);
			FillHist("h_met_3b_f",METv,weight);
			FillHist("h_njets_3b_f",njets,weight);
		}
	}


	enum {def, ttbar, st, VV, VJ, ttx, QCD};
				
	float Bweight=1.0, BweightErr =1.0;
	float Bw_down_syst_factor = 1.0, Bw_up_syst_factor = 1.0;
	
	if (!k_isdata){
	  //fBTagSF->GetBTagEvtWeight(njets,jetPt_all,jetEta_all,jetFlav_all,btag_all,0,Bweight,BweightErr,ttbar);
		
	}

	weight*=Bweight;
	if (debug){
		cout << " Ntags = " << nbtags_tot << ", Btag Weight = " << Bweight << " +- " << BweightErr << endl;
	}


	FillHist("BW_nbjets_tot",nbtags_tot,weight);
	FillHist("BW_nbjets_f",nbtags_f,weight);
	
	if (nbtags_tot>=2){
		FillCutFlow("BW_2bJets",weight);
		FillHist("BW_mu_pt_2b",Mu.Pt(),weight);
		FillHist("BW_met_2b",METv,weight);
		FillHist("BW_njets_2b",njets,weight);
		
		if (nbtags_tot>2){
			FillCutFlow("BW_3bJets",weight);
			FillHist("BW_mu_pt_3b",Mu.Pt(),weight);
			FillHist("BW_met_3b",METv,weight);
			FillHist("BW_njets_3b",njets,weight);
		}
	}

	if (nbtags_f>=2){
		FillCutFlow("BW_2bJets_f",weight);
		FillHist("BW_mu_pt_2b_f",Mu.Pt(),weight);
		FillHist("BW_met_2b_f",METv,weight);
		FillHist("BW_njets_2b_f",njets,weight);
		
		if (nbtags_f>2){
			FillCutFlow("BW_3bJets_f",weight);
			FillHist("BW_mu_pt_3b_f",Mu.Pt(),weight);
			FillHist("BW_met_3b_f",METv,weight);
			FillHist("BW_njets_3b_f",njets,weight);
		}
	}

	
	if (METv<20)   throw LQError( "Fails MET cuts",  LQError::SkipEvent );
	FillCutFlow("met",weight);
	FillHist("h_njets_met",njets,weight);
	FillHist("h_nbjets_met",nbtags_tot,weight);
	FillHist("h_nbjets_met_f",nbtags_f,weight);
	FillHist("h_mu_pt_met",Mu.Pt(),weight);

	if (nbtags_f<2) throw LQError( "Fails nbtags cuts",  LQError::SkipEvent );

	if (nbtags_f == 2){
		FillCutFlow("met+2b_f",weight);
		FillHist("in_met_2b",METv,weight);
		FillHist("in_lep_2b",Mu.Pt(),weight);
		FillHist("in_lepeta_2b",Mu.Eta(),weight);
		FillHist("in_jet1pt_2b",jetPt_f[0],weight);
		FillHist("in_jet2pt_2b",jetPt_f[1],weight);
		FillHist("in_jet3pt_2b",jetPt_f[2],weight);
		FillHist("in_jet4pt_2b",jetPt_f[3],weight);
		FillHist("in_jet1eta_2b",jetEta_f[0],weight);
		FillHist("in_jet2eta_2b",jetEta_f[1],weight);
		FillHist("in_jet3eta_2b",jetEta_f[2],weight);
		FillHist("in_jet4eta_2b",jetEta_f[3],weight);
	}
	else{
		FillCutFlow("met+>=3b_f",weight);
		FillHist("in_met_3b",METv,weight);
		FillHist("in_lep_3b",Mu.Pt(),weight);
		FillHist("in_lepeta_3b",Mu.Eta(),weight);
		FillHist("in_jet1pt_3b",jetPt_f[0],weight);
		FillHist("in_jet2pt_3b",jetPt_f[1],weight);
		FillHist("in_jet3pt_3b",jetPt_f[2],weight);
		FillHist("in_jet4pt_3b",jetPt_f[3],weight);
		FillHist("in_jet1eta_3b",jetEta_f[0],weight);
		FillHist("in_jet2eta_3b",jetEta_f[1],weight);
		FillHist("in_jet3eta_3b",jetEta_f[2],weight);
		FillHist("in_jet4eta_3b",jetEta_f[3],weight);
	}

	
	TLorentzVector sum_jetraw(0,0,0,0);
	TLorentzVector addjets(0,0,0,0);

	for (int i=0; i<snjets; i++){
		int this_idx = sjidx[i];
		if (debug) cout << " Check order = " << i << " vs " << this_idx << "/" << snjets << endl; 
		
		TLorentzVector tempjet_raw(0,0,0,0);
		tempjet_raw.SetPtEtaPhiM(jetColl_UE.at(this_idx).RawPt(),jetColl_UE.at(this_idx).Eta(),jetColl_UE.at(this_idx).Phi(),0);
		sum_jetraw += tempjet_raw;

		TLorentzVector tempjet(0,0,0,0);
		tempjet.SetPtEtaPhiM(jetColl_UE.at(this_idx).Pt(),jetColl_UE.at(this_idx).Eta(),jetColl_UE.at(this_idx).Phi(),0);


		addjets+=tempjet;
		if (i<4)
			addjets-= jets_f[i];
	}
	
	TLorentzVector Mu_vec;
	Mu_vec.SetPtEtaPhiE(Mu.Pt(),Mu.Eta(),Mu.Phi(),Mu.E());
	std::cout << "Mu.Pt() = " << Mu.Pt() << " eta="  << Mu.Eta() << endl;
	float sigmalep = 0.5*fabs(Evt.PFMET_Muon_EnUp()-METv) + 0.5*fabs(Evt.PFMET_Muon_EnDown()-METv);
	if (fabs(Mu.Eta())>1.5) sigmalep =  (sigmalep > 0.015*Mu_vec.Pt() ) ? sigmalep : 0.015*Mu_vec.Pt() ;  // Et difference is too small, so assign 1% 
	else sigmalep =  (sigmalep > 0.01*Mu_vec.Pt() ) ? sigmalep : 0.01*Mu_vec.Pt() ;  // Et difference is too small, so assign 1% 
	
	TLorentzVector met;
	met.SetPxPyPzE(METv*cos(METphi),METv*sin(METphi),0,METv); 	   
	TLorentzVector metraw;
	metraw.SetPxPyPzE(METraw*cos(METrawphi),METraw*sin(METrawphi),0,METraw); 	   

	int ntype = 14;	
	bool highpt_fit = false;

	
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

	if (get_best>-1){
		//		FillCutFlow("Fit",weight);
		if (nbtags_f == 2) {
			FillCutFlow("Fit_2b",weight);
			FillHist("h_mh_2b",get_bestHmass,weight);
			FillHist("fit_met_2b",myfit->FittedNeu[get_best].Pt(),weight);
			FillHist("fit_lep_2b",myfit->FittedLep[get_best].Pt(),weight);
			FillHist("fit_jet1pt_2b",myfit->FittedJets[get_best][0].Pt(),weight);
			FillHist("fit_jet2pt_2b",myfit->FittedJets[get_best][1].Pt(),weight);
			FillHist("fit_jet3pt_2b",myfit->FittedJets[get_best][2].Pt(),weight);
			FillHist("fit_jet4pt_2b",myfit->FittedJets[get_best][3].Pt(),weight);
		}
		else{
			FillCutFlow("Fit_3b",weight);
			FillHist("h_mh_3b",get_bestHmass,weight);
			FillHist("fit_met_3b",myfit->FittedNeu[get_best].Pt(),weight);
			FillHist("fit_lep_3b",myfit->FittedLep[get_best].Pt(),weight);
			FillHist("fit_jet1pt_3b",myfit->FittedJets[get_best][0].Pt(),weight);
			FillHist("fit_jet2pt_3b",myfit->FittedJets[get_best][1].Pt(),weight);
			FillHist("fit_jet3pt_3b",myfit->FittedJets[get_best][2].Pt(),weight);
			FillHist("fit_jet4pt_3b",myfit->FittedJets[get_best][3].Pt(),weight);
		}
	}


	/*
	
		int jidx[njets];
		int sjidx[snjets];
		
		for (int i=0; i<njets; i++){
			jidx[i] = i;
		}                    
				
		for (int i=0; i<snjets; i++){
			sjidx[i] = i;
		}                    
		
		if (debug)  std::cout << " Call to sort ! " << std::endl;
		if (debug)  std::cout << " Number of jets " <<  njets << " ("<< snjets << ")" <<std::endl;

		// Check jet pt ordering
		mysort(jetColl_lepveto,jidx);
		mysort(jetColl_lepveto_uncor,sjidx);


		if (debug) cout << " MMMMMMising Et " << METv << endl;
					   
		if (METv<=20) throw LQError( "Fails MET cuts",  LQError::SkipEvent );
		FillCutFlow("MET>20",weight);

		
		int nbtags = 0;
		TLorentzVector jets_f[4];
		bool btag_f[4];
		//		double btag_cor[2][4];

		TLorentzVector jetraw_f[4];
		TLorentzVector sumjet_30GeV(0,0,0,0);
		TLorentzVector sumjet_uncorr(0,0,0,0);

		float HT=Mu.Pt()+METv;
		//		float HT_softjet=Mu.Pt()+METv;

		//		int partonCHECK = 0;
		float dr_min = 0.3;
		int index_tb = -1, index_atb = -1, index_q1 = -1, index_q2 = -1;
		TLorentzVector jet_tb(0,0,0,0), jet_atb(0,0,0,0), jet_q1(0,0,0,0), jet_q2(0,0,0,0);


		for (int i=0; i<snjets; i++){
			int this_idx = sjidx[i];
			if (debug) cout << " Check order = " << i << " vs " << this_idx << "/" << snjets << endl; 
			
			TLorentzVector tempjet_raw(0,0,0,0);
			tempjet_raw.SetPtEtaPhiM(jetColl_lepveto_uncor.at(this_idx).RawPt(),jetColl_lepveto_uncor.at(this_idx).Eta(),jetColl_lepveto_uncor.at(this_idx).Phi(),0);

			sumjet_uncorr +=tempjet_raw;


			if (debug ) cout << "Temporary all jets pt = " << tempjet_raw.Pt() << endl;
			if (i>3) continue;
			jetraw_f[i] = tempjet_raw; // Raw jet pT

		}

		if (debug) cout << " sum all jets = " << sumjet_uncorr.Pt() << endl;
		//		bool double_match = false;
		
		for (int i=0; i<njets; i++){
			//			int this_idx = index_4jets[i];
			int this_idx = jidx[i];
			if (debug) cout << " This index = " << this_idx << endl;

			TLorentzVector tempjet(0,0,0,0);		   
			tempjet.SetPtEtaPhiE(jetColl_lepveto.at(this_idx).Pt(),jetColl_lepveto.at(this_idx).Eta(),jetColl_lepveto.at(this_idx).Phi(),jetColl_lepveto.at(this_idx).E());

			
			sumjet_30GeV+=tempjet;

			HT+= tempjet.Pt();

			if (i>3) continue;

			jetFlavour = jetColl_lepveto.at(this_idx).PartonFlavour();			
			
			if (debug) cout << " Gen Jet matching " << this_idx << " & Flav = " << jetFlavour << " : pass pileup ? " << jetColl_lepveto.at(this_idx).PileupJetIDLoose() <<endl;	

			float tempdr = 0.3;

			if (genP_atopb.Pt()>0 && genP_atopb.DeltaR(tempjet) < tempdr){
				tempdr = genP_atopb.DeltaR(tempjet);				
				jet_atb = tempjet;
				if (debug) cout << " Found atop b jet " << this_idx << " : " << jet_atb.Pt() <<  " <- gen : " << genP_atopb.Pt() <<  " dR = " << genP_atopb.DeltaR(tempjet) << endl;
			}
			if (genP_q1.Pt()>0 && genP_q1.DeltaR(tempjet)  < tempdr){
				tempdr = genP_q1.DeltaR(tempjet);
				jet_q1 = tempjet;				
				if (debug) cout << " Found H+ b jet " <<  this_idx << " : " << jet_q1.Pt() <<  " <- gen : " << genP_q1.Pt() <<  " dR = " << genP_q1.DeltaR(tempjet) << endl;
			}
			if (genP_topb.Pt()>0 && genP_topb.DeltaR(tempjet) < tempdr){
				tempdr = genP_topb.DeltaR(tempjet);
				jet_tb = tempjet;
				if (debug) cout << " Found top b jet " << this_idx << " : " << jet_tb.Pt() << " <- gen : " << genP_topb.Pt() << " dR = " << genP_topb.DeltaR(tempjet) << endl;
			}
			if (genP_q2.Pt() > 0 && genP_q2.DeltaR(tempjet)<tempdr){
				tempdr = genP_q2.DeltaR(tempjet);
				jet_q2 = tempjet;
				if (debug) cout << " Found H+ c jet " << this_idx << " : " << jet_q2.Pt() << " <- gen : " << genP_q2.Pt() <<  " dR = " << genP_q2.DeltaR(tempjet) << endl;
			}

			double jet_btag = jetColl_lepveto.at(this_idx).CombinedSecVertexBtag();
			
			if (debug)
				cout << "csv = " << jet_btag << endl;
						
			jets_f[i] = tempjet;
			////jetColl_lepveto.at(this_idx).JECUncertainty();
			jetPt[i] = tempjet.Pt();
			jetEta[i] = tempjet.Eta();
			jetFlav[i] = jetFlavour;
			FillHist("h_csv",jet_btag,weight);
			
			if (jet_btag>0.679){
				btag_f[i] = true;
				nbtags++;
			}
			else btag_f[i] = false;			

			//			if (debug) cout << " Jet Uncertainty(" << i << ") = " << jetErr_f[i] << ", uncorrected Jet Pt = " << jets_f[i].Pt()/jetErr_f[i] << endl;
			if (debug) cout << " Jet raw pt(" << i<< ") : " << jetraw_f[i].Pt() << ", corr pT = " << jets_f[i].Pt() << endl;

		}

	   

		//		if (double_match) throw LQError( "Fails Single Gen Match",  LQError::SkipEvent );
		//		if (nbtags==0) throw LQError( "Fails due to Nbtags == 0",  LQError::SkipEvent );

		FillHist("h_nbjets",nbtags,weight);
		
		if (debug) cout << " sum 30GeV jets = " << sumjet_30GeV.Pt() << endl;

		bool genH_match =  (jet_q1.Pt()>0 && jet_q2.Pt()>0) ? true: false;
		bool genHt_match =  (genH_match && jet_tb.Pt()>0) ? true: false;
		bool genallj_match =  (genHt_match && jet_atb.Pt()>0) ? true: false;
	
		FillHist("h_pt_jet1",jetPt[0],weight);
		FillHist("h_pt_jet2",jetPt[1],weight);
		FillHist("h_pt_jet3",jetPt[2],weight);
		FillHist("h_pt_jet4",jetPt[3],weight);


		

		//		cout << "JES UNC GetJECUncertainty(FlavorPureBottom, 2.2, 100.,true) = " << GetJECUncertainty("FlavorPureQuark", 2.2, 100.,true) << endl;
		//cout << "JES UNC GetJECUncertainty(FlavorPureCharm, 2.2, 100.,true) = " << GetJECUncertainty("FlavorPureQuark", 2.2, 100.,true) << endl;
		//cout << "JES UNC GetJECUncertainty(FlavorPureQuark, 5.2, 1000.,true) = " << GetJECUncertainty("FlavorPureQuark", 5.2, 1000.,true) << endl;
		//cout << "JES UNC GetJECUncertainty(FlavorPureGluon, 0.1, 500.,true) = " << GetJECUncertainty("FlavorPureGluon", 0.1, 500.,true) << endl;


		
		// Check the Flavour JES correction


		if (debug){
			cout << " " << endl;
			cout << " Flavour uncertainty check == " << endl;
			cout << " " << endl;
		}

		bool bJES_up = false; // false for bJES_down
		string Flavor_temp;
		
		for (int i=0; i<4; i++){
			// Up Flavour
			float temp_weight = 0.;
			float bJES = 0.;
			float r_Up = 1.0;

			
			if (abs(jetFlav[i]) == 5){
				bJES = jetColl_lepveto.at(i).L5BottomJEC();
				Flavor_temp = "FlavorPureBottom";
			}
			else if (abs(jetFlav[i]) == 4){
				bJES = jetColl_lepveto.at(i).L5CharmJEC();
				Flavor_temp = "FlavorPureCharm";
			}
			else if  (abs(jetFlav[i])>0 && abs(jetFlav[i])<4){
				bJES = jetColl_lepveto.at(i).L5UDSJEC();
				Flavor_temp = "FlavorPureQuark";
			}
			else {
				bJES = jetColl_lepveto.at(i).L5GluonJEC();
				Flavor_temp = "FlavorPureGluon";
			}

			temp_weight = ( bJES_up == true) ? GetJECUncertainty(Flavor_temp.c_str(),jets_f[i].Eta(),jets_f[i].Pt(),true)
				: GetJECUncertainty(Flavor_temp.c_str(),jets_f[i].Eta(),jets_f[i].Pt(),false);

			if (debug)
				cout << " Comp weight = " <<  GetJECUncertainty(Flavor_temp.c_str(),jets_f[i].Eta(),jets_f[i].Pt(),true) << " vs. " 
					 << GetJECUncertainty(Flavor_temp.c_str(),jets_f[i].Eta(),jets_f[i].Pt(),false) << endl;
			
			r_Up = (bJES+temp_weight)/bJES;

			if (debug)
				cout << "Jet Pt before = " << jetPt[i];
					
			jetPt[i] = r_Up* jetPt[i];
			jets_f[i].SetPtEtaPhiM(jetPt[i],jets_f[i].Eta(),jets_f[i].Phi(),b_mass);
			
			if (debug)
				cout << " Flav = " << Flavor_temp << " : JEC " << bJES << " Uncer " << temp_weight <<  " = changed to " << jets_f[i].Pt() << endl;
			
		}

		
		  else if 
		  temp_weight_up = GetJECUncertainty("FlavorPureCharm",jets_f[i].Eta(),jets_f[i].Pt(),true);
		  temp_weight_down = GetJECUncertainty("FlavorPureCharmm",jets_f[i].Eta(),jets_f[i].Pt(),false);
		  weight_flav_up*=temp_weight_up;
		  weight_flav_down*=temp_weight_down;

		  if (debug)
		  cout << " c-quark : " << temp_weight_up << " vs " << temp_weight_down << endl;

		  }
		  else if
		  temp_weight_up = GetJECUncertainty("FlavorPureQuark",jets_f[i].Eta(),jets_f[i].Pt(),true);
		  temp_weight_down = GetJECUncertainty("FlavorPureQuark",jets_f[i].Eta(),jets_f[i].Pt(),false);
		  weight_flav_up*=temp_weight_up;
		  weight_flav_down*=temp_weight_down;

		  if (debug)
		  cout << " l-quark : " << temp_weight_up << " vs " << temp_weight_down << endl;

		  }
		  else if (jetFlav[i]==0 || jetFlav[i]==21){
		  temp_weight_up = GetJECUncertainty("FlavorPureGluon",jets_f[i].Eta(),jets_f[i].Pt(),true);
		  temp_weight_down = GetJECUncertainty("FlavorPureGluon",jets_f[i].Eta(),jets_f[i].Pt(),false);
		  weight_flav_up*=temp_weight_up;
		  weight_flav_down*=temp_weight_down;

		  if (debug)
		  cout << " gluon : " << temp_weight_up << " vs " << temp_weight_down << endl;

		  }



		// ==========================================================================
		if (btag_f[0]) FillHist("h_bpt_jet1",jetPt[0],weight);
		if (btag_f[1]) FillHist("h_bpt_jet2",jetPt[1],weight);
		if (btag_f[2]) FillHist("h_bpt_jet3",jetPt[2],weight);
		if (btag_f[3]) FillHist("h_bpt_jet4",jetPt[3],weight);
		


		float Bweight=1.0, BweightErr =1.0;

		if (!k_isdata)
			fBTagSF->GetBTagEvtWeight(4,jetPt,jetEta,jetFlav,btag_f,0,Bweight,BweightErr);
		
		weight*=Bweight;
		
		if (debug){
			cout << " Ntags = " << nbtags << ", Btag Weight = " << Bweight << " +- " << BweightErr << endl;
		}
		
	
		FillCutFlow("BtagWeight", weight);
		
		if (nbtags == 2){
			FillCutFlow("2Bjets", weight);
			FillHist("h_mu_pt_2btag",Mu.Pt(),weight);
			FillHist("h_met_2btag",METv,weight);
		}
		if (nbtags >=3){
			FillCutFlow(">=3Bjets", weight);
			FillHist("h_mu_pt_3btag",Mu.Pt(),weight);
			FillHist("h_met_3btag",METv,weight);
		}


		
		TLorentzVector Mu_vec;
		Mu_vec.SetPtEtaPhiE(Mu.Pt(),Mu.Eta(),Mu.Phi(),Mu.E());

		TLorentzVector met;
		met.SetPxPyPzE(METv*cos(METphi),METv*sin(METphi),0,METv); 	   

		
		FillHist("h_sumjets_pt",sumjet_30GeV.Pt(),weight);
		FillHist("h_HT",HT,weight);
		//FillHist("h_HTsoft",HT_softjet,weight);

		// Get tstype corrections
		int ntype = 14; 
		//myfit->GetTSCorr(jets_f, ntype, debug);

		//		DoFits(Mu_vec,met,sumjets,jets_f,nbtags,btag_f,debug);
		//
		
		float sigmalep = 0.5*(Evt.PFMET_Mu_EnUp()-METv) + 0.5*(Evt.PFMET_Mu_EnDown()-METv);
		sigmalep = 0.01*Mu_vec.Pt();  // Et difference is too small, so assign 1% 

		if (debug) cout << "::::::::: Sigmalep = " << sigmalep << endl;


		//		if (!genallj_match)  throw LQError( "Fails Higgs match",  LQError::SkipEvent );











		
		bool highpt_fit = true;
		myfit->Fit(Mu_vec,sigmalep,jets_f,jetraw_f,btag_f,sumjet_uncorr,met,0, ntype, debug);
		//myfit->Fit(Mu_vec,sigmalep,jets_f,jetraw_f,btag_f,sumjet_uncorr,met,0, ntype, debug, highpt_fit);

				
		if (genH_match){
			FillHist("h_MH_match",(jet_q1+jet_q2).M(),weight);
			if (genHt_match){
				FillHist("h_MT_match",(jet_q1+jet_q2+jet_tb).M(),weight);
			}
		}
		
		TLorentzVector jet_match[4];
		TLorentzVector jet_TS_q1, jet_TS_q2, jet_TS_tb;
			
		if (genallj_match){
			jet_match[0] = jet_atb;
			jet_match[1] = jet_tb;
			jet_match[2] = jet_q1;
			jet_match[3] = jet_q2;

			// Get TS corrections
			myfit->GetTSCorr(jet_match,ntype,false);
			TLorentzVector jet_TS_q1, jet_TS_q2, jet_TS_tb;
			
			// bjet corr
			jet_TS_q1.SetPtEtaPhiM(jet_match[2].Pt()*myfit->tsjetCorr[0][2],jet_match[2].Eta(),jet_match[2].Phi(),b_mass);
			// cjet corr
			jet_TS_q2.SetPtEtaPhiM(jet_match[3].Pt()*myfit->tsjetCorr[1][3],jet_match[3].Eta(),jet_match[3].Phi(),c_mass);
			// bjet corr
			jet_TS_tb.SetPtEtaPhiM(jet_match[1].Pt()*myfit->tsjetCorr[0][1],jet_match[1].Eta(),jet_match[1].Phi(),b_mass);

			FillHist("h_MH_matchTS",(jet_TS_q1+jet_TS_q2).M(),weight);
			FillHist("h_MT_matchTS",(jet_TS_q1+jet_TS_q2+jet_TS_tb).M(),weight);					 
		}
		
   		
		double chi2 = 10000;
		float mHiggs = 0;
		int bestidx = 0;

		double sum_invchi2 = 0;
		double invchi2[48]; std::fill_n(invchi2, 48, -1);
		double mh[48]; std::fill_n(mh, 48, -1);
		
		int get_best = -1;
		float get_best_chi2 = 9999;
		int get_secbest = -1;
		float get_secbest_chi2 = 9999;

		for (int i=0; i<48; i++){

			if (!myfit->tagconsistent[i]) continue;

			float thischi = myfit->Chi2[i];
			if (thischi < 20){
				invchi2[i] = 1/thischi;
				sum_invchi2 += invchi2[i];
				mh[i] = myfit->HMass[i];
			}			

			if (thischi<chi2){
				chi2 = thischi;
				mHiggs = myfit->HMass[i];				
				bestidx = i;
			}

			// Check another best combination

			// |jin pt - fit pt| < 20 GeV, works only for hadtop side
			bool tb_ptdiff = fabs(myfit->FittedJets[i][1].Pt()-myfit->jetsIN[i][1].Pt()) > 20. ? true:false;
			bool q1_ptdiff = fabs(myfit->FittedJets[i][2].Pt()-myfit->jetsIN[i][2].Pt()) > 20. ? true:false;
			bool q2_ptdiff = fabs(myfit->FittedJets[i][3].Pt()-myfit->jetsIN[i][3].Pt()) > 20. ? true:false;
			bool atb_ptdiff = fabs(myfit->FittedJets[i][0].Pt() - myfit->jetsIN[i][0].Pt())> 20. ? true:false;

			// Unfitted hadtop mass < 200 
			bool mbjj_jetsIN = ((myfit->jetsIN[i][1]+myfit->jetsIN[i][2]+myfit->jetsIN[i][3]).M() > 200. )? true: false; 

			//bool check_chi2 = (myfit->Chi2[i]> 10. ) ? true: false; 
			if (debug) cout << " ptdiff = " << tb_ptdiff << ", " << q1_ptdiff << ", " << q2_ptdiff << ", " << atb_ptdiff << ", " << mbjj_jetsIN << endl;

			if (!tb_ptdiff && !q1_ptdiff && !q2_ptdiff && !atb_ptdiff){
			  if (!mbjj_jetsIN){
			    if (thischi<  get_best_chi2){
			      get_best_chi2 = thischi;
			      get_best = i;
			    }
			  }
			}
			else{
			  if (!mbjj_jetsIN){
			    if (thischi< get_secbest_chi2){
			      get_secbest_chi2 = thischi;
			      get_secbest = i;

			    }
			  }
			}


			if (debug){ cout << "CHECKCHECKCHECK : " << i << ", chi2 = " << myfit->Chi2[i] << ", mH = " << myfit->HMass[i] << endl;
			}


			/*			if (genHt_match){
				if (myfit->FittedJets[i][1].DeltaR(jet_tb)<0.1 ){
					if  (myfit->FittedJets[i][2].DeltaR(jet_q1) < 0.1 && myfit->FittedJets[i][3].DeltaR(jet_q2)<0.1){
						// all corrections matched
						
						FillHist("h_wrongfit_goodTS",(myfit->FittedJets[i][2]+myfit->FittedJets[i][3]).M(),weight);
						FillHist("h_wrongfit_goodTS_chi2",myfit->Chi2[i],weight);
						
						if (debug){
							cout << " Corr Fits("<< i << ") : JetChi2 = " << myfit->JetChi[0][i] << ", " << myfit->JetChi[1][i] << ", " << myfit->JetChi[2][i] << ", " << myfit->JetChi[3][i] << " & " << myfit->HadTopChi[i] << endl;
							cout << " Angles : (tb,B) = " << jet_tb.DeltaR(jet_q1) << " vs (tb,C) " << jet_tb.DeltaR(jet_q2) << " vs (B,C) " << jet_q1.DeltaR(jet_q2) << " chi2 = " << myfit->Chi2[i] << endl;
						}
						
						FillHist("h_corrdR_jj",jet_q1.DeltaR(jet_q2),weight);
						FillHist("h_corrdR_vs_chi2",jet_q1.DeltaR(jet_q2),myfit->Chi2[i],weight,0,3.3,100,0,20,10);
						
					}
					
					//			if (debug) cout << " TEMP DR " << myfit->FittedJets[i][2].DeltaR(jet_q2) << endl;
					
					if (myfit->FittedJets[i][2].DeltaR(jet_q2) < 0.1 && myfit->FittedJets[i][3].DeltaR(jet_q1)<0.1){
						// wrong TS correction but still good for Higgs
						
						FillHist("h_wrongfit_badTS",(myfit->FittedJets[i][2]+myfit->FittedJets[i][3]).M(),weight);
						FillHist("h_wrongfit_badTS_chi2",myfit->Chi2[i],weight);
						
						if (debug){
							cout << " Bad Fits(" << i << ") : JetChi2 = " << myfit->JetChi[0][i] << ", " << myfit->JetChi[1][i] << ", " << myfit->JetChi[2][i] << ", " << myfit->JetChi[3][i] << " & " << myfit->HadTopChi[i] << endl;
						}
						
					}
				}
				}

		}

		if (get_best<0 ) throw LQError( "Fails Higgs match",  LQError::SkipEvent );;


		bestidx = get_best;
		chi2 = get_best_chi2;

		//		if (nbtags==3){
		//		  cout << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << " : mH = " << mHiggs << ", chi2 = " << chi2 << endl;
		  //}
		

		FillHist("h_met_nofit",METv,weight);
		FillHist("h_met_fitted",myfit->FittedNeu[bestidx].Pt(),weight);

		FillHist("h_leppt_nofit",Mu_vec.Pt(),weight);
		FillHist("h_leppt_fitted",myfit->FittedLep[bestidx].Pt(),weight);

		if (nbtags>2&& get_secbest>-1){
		  FillHist("h_mjj_secbestC",myfit->HMass[get_secbest],weight);
		  FillHist("h_chi2_secbestC",get_secbest_chi2,weight);
		}

		//if (chi2<10){		
		FillHist("h_minfit_chi2",chi2,weight);
		FillHist("h_minfit_mjj",mHiggs,weight);
		
		if (genH_match){
		  FillHist("h_minfit_chi2_match",chi2,weight);
		  FillHist("h_minfit_mjj_match",mHiggs,weight);
		}
			
			
		if (nbtags==2){
		  FillHist("h_minfit_mjj_2b",mHiggs,weight);
		  FillHist("h_minfit_chi2_2b",chi2,weight);
		  
		  if (genH_match){
		    FillHist("h_minfit_chi2_2b_match",chi2,weight);
		    FillHist("h_minfit_mjj_2b_match",mHiggs,weight);
		  }
		}
		else if (nbtags>=3){
		  FillHist("h_minfit_mjj_3b",mHiggs,weight);
		  FillHist("h_minfit_chi2_3b",chi2,weight);
		  
		  if (genH_match){
		    FillHist("h_minfit_chi2_3b_match",chi2,weight);
		    FillHist("h_minfit_mjj_3b_match",mHiggs,weight);
		  }
		  
		}

		TLorentzVector MH_raw, MT_raw, MH_tscorr, MT_tscorr, MH_fit, MT_fit, raw_tb, raw_atb, raw_q1, raw_q2;
		raw_tb = myfit->rawJets[bestidx][1];
		raw_atb=myfit->rawJets[bestidx][0];
		raw_q1=myfit->rawJets[bestidx][2];
		raw_q2=myfit->rawJets[bestidx][3];

		MH_raw = myfit->rawJets[bestidx][2]+myfit->rawJets[bestidx][3];
		MT_raw = myfit->rawJets[bestidx][1]+MH_raw;
		FillHist("h_MH_match_raw",MH_raw.M(),weight);
		FillHist("h_MT_match_raw",MT_raw.M(),weight);

		TLorentzVector jin_tb, jin_q1, jin_q2, jin_atb;

		jin_tb = myfit->jetsIN[bestidx][1];
		jin_atb = myfit->jetsIN[bestidx][0];
		jin_q1 = myfit->jetsIN[bestidx][2];
		jin_q2 = myfit->jetsIN[bestidx][3];
		
		MH_tscorr = jin_q1+jin_q2;
		MT_tscorr = jin_tb+MH_tscorr;
		FillHist("h_MH_match_tscorr",MH_tscorr.M(),weight);
		FillHist("h_MT_match_tscorr",MT_tscorr.M(),weight);
		
		TLorentzVector fit_q1, fit_q2, fit_tb, fit_atb;

		fit_q1 = myfit->FittedJets[bestidx][2];
		fit_q2 = myfit->FittedJets[bestidx][3];

		MH_fit = fit_q1+fit_q2;

		//		cout << " MH_fit " << fit_q
		fit_tb = myfit->FittedJets[bestidx][1];
		fit_atb = myfit->FittedJets[bestidx][0];
				 
		MT_fit = fit_tb+MH_fit;
		FillHist("h_MH_match_fit",MH_fit.M(),weight);
		FillHist("h_MT_match_fit",MT_fit.M(),weight);

		bool fitcorr = false;



		if ( genHt_match && ( (fit_q1.DeltaR(jet_q1)<0.1 && fit_q2.DeltaR(jet_q2)<0.1) ||
							  (fit_q1.DeltaR(jet_q2)<0.1 && fit_q2.DeltaR(jet_q1)<0.1) ) &&
			 myfit->FittedJets[bestidx][1].DeltaR(jet_tb)<0.1){


			fitcorr = true;					 

		}

		if (debug) cout << " Matched jets? " << fitcorr << endl;

		float jet_pt1=0, jet_pt2=0, jet_pt3=0;
		if (debug)
			cout << "Sort: Input pt = " << jin_tb.Pt() << ", " << jin_q1.Pt() << ", " <<  jin_q2.Pt() << endl;
		
		Sortout(jin_tb.Pt(),jin_q1.Pt(), jin_q2.Pt(),jet_pt1,jet_pt2,jet_pt3);		
		if (debug)
			cout << "Sort: Out pt = " << jet_pt1 << ", " << jet_pt2 << ", " << jet_pt3 << endl;

			
		float jet_angle1 = 0, jet_angle2=0, jet_angle3=0;
		float temp1 =0, temp2=0, temp3=0;

		temp1 = jin_tb.Angle(jin_q1.Vect());
		temp2 = jin_q1.Angle( jin_q2.Vect());
		temp3 =  jin_q2.Angle(jin_tb.Vect());

		if (debug)
			cout << "Sort: Input angle = " << temp1 << ", " << temp2 << ", " << temp3 << endl;

		Sortout(temp1,temp2,temp3,jet_angle1,jet_angle2,jet_angle3);
		if (debug)
			cout << "Sort: Out angle = " << jet_angle1 << ", " << jet_angle2 << ", " << jet_angle3 << endl;

		TLorentzVector ht_rest=jin_q1+jin_tb+ jin_q2;
		TVector3 boo = ht_rest.BoostVector();			

		TLorentzVector jin_tb_ = jin_tb;
		TLorentzVector jin_q1_ = jin_q1;
		TLorentzVector  jin_q2_ =  jin_q2;
		jin_tb_.Boost(-boo);
		jin_q1_.Boost(-boo);
		jin_q2_.Boost(-boo);
			
		float jet_angle1_r = 0, jet_angle2_r=0, jet_angle3_r = 0;
		temp1 = jin_tb_.Angle(jin_q1_.Vect());
		temp2 = jin_q1_.Angle( jin_q2_.Vect());
		temp3 =  jin_q2_.Angle(jin_tb_.Vect());

		if (debug)
			cout << "Sort: Input angle @ rest = " << temp1 << ", " << temp2 << ", " << temp3 << endl;

		Sortout(temp1,temp2,temp3,jet_angle1_r,jet_angle2_r,jet_angle3_r);

		if (debug)
			cout << "Sort: Out angle @ rest = " << jet_angle1_r << ", " << jet_angle2_r << ", " << jet_angle3_r << endl;

		float high_mjj = -100;
		if (fabs(jin_tb.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_q1+ jin_q2).M();
		}
		else if (fabs(jin_q1.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_tb+ jin_q2).M();
		}
		else if (fabs(jin_q2.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_tb+jin_q1).M();
		}
	*/	
	return;
	
}


void CHMJ_bestfit::EndCycle()throw( LQError ){
	
	Message("In EndCycle" , INFO);
}


void CHMJ_bestfit::BeginCycle() throw( LQError ){
  
	Message("In begin Cycle", INFO);
  
	string analysisdir = getenv("FILEDIR");  
  
	if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());
	if(!k_isdata)    fBTagSF = new BTagSFUtil("CSVM");
	myfit = new TTFitter();
	
	//	minuit = new TMinuit(nfit);
	//	const int nfit = 10;
	//
	//If you wish to output variables to output file use DeclareVariable
	// clear these variables in ::ClearOutputVectors function
	//DeclareVariable(obj, label, treename );
	//DeclareVariable(obj, label ); //-> will use default treename: LQTree
  

	return;
  
}

CHMJ_bestfit::~CHMJ_bestfit() {
  
	Message("In CHMJ_bestfit Destructor" , INFO);
	if(!k_isdata)delete reweightPU;
	if(!k_isdata) delete fBTagSF;
	delete myfit;
	//	delete minuit;
}
         
void CHMJ_bestfit::FillCutFlow(TString cut, float weight){
  
	if(GetHist("cutflow")) {
		GetHist("cutflow")->Fill(cut,weight);
	}
	else{
		AnalyzerCore::MakeHistograms("cutflow",23,0.,23.);
    
		GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"Pileup");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"TTReweight");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"TriggerCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"OneTightMu");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"ExtraMuVeto");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"ElVeto");		
		GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"FourJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"2bJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"3bJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(13,"2bJets_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(14,"3bJets_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(15,"BW_2bJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(16,"BW_3bJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(17,"BW_2bJets_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(18,"BW_3bJets_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(19,"met");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(20,"met+2b_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(21,"met+>=3b_f");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(22,"Fit_2b");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(23,"Fit_3b");
	}
}
     
void CHMJ_bestfit::BeginEvent( )throw( LQError ){

	Message("In BeginEvent() " , DEBUG);

	return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void CHMJ_bestfit::MakeHistograms(){
	//// Additional plots to make
    
	maphist.clear();
	AnalyzerCore::MakeHistograms();
	Message("Made histograms", INFO);

	maphist["h_njets"] = new TH1F("h_njets","# Jets with pT>30 GeV",10,0,10);
	maphist["h_snjets"] = new TH1F("h_snjets","# Jets with pT>10 GeV",20,0,20);

	maphist["h_mu_pt_4jets"] = new TH1F("h_mu_pt_4jets","Muon Pt, 4jets",40,0,200);
	maphist["h_met_4jets"] = new TH1F("h_met_4jets","MET, 4jets",40,0,200);

	maphist["h_nbjets_tot"] = new TH1F("h_nbjets_tot","# b-tagged Jets with pT>30 GeV",7,0,7);
	maphist["h_nbjets_f"] = new TH1F("h_nbjets_f","# b-tagged Jets among leading four jets",6,0,6);

	maphist["h_mu_pt_2b"] = new TH1F("h_mu_pt_2b","Electron Pt, 2btag",40,0,200);
	maphist["h_met_2b"] = new TH1F("h_met_2b","MET, 2btag",40,0,200);
	maphist["h_njets_2b"] = new TH1F("h_njets_2b","# Jets with pT>30 GeV, 2b",10,0,10);

	maphist["h_mu_pt_3b"] = new TH1F("h_mu_pt_3btag","Electron Pt, 3btag",40,0,200);
	maphist["h_met_3b"] = new TH1F("h_met_3btag","MET, 3btag",40,0,200);
	maphist["h_njets_3b"] = new TH1F("h_njets_3b","# Jets with pT>30 GeV, 3b",10,0,10);
	
	maphist["h_mu_pt_2b_f"] = new TH1F("h_mu_pt_2b_f","Electron Pt, 4j 2btag",40,0,200);
	maphist["h_met_2b_f"] = new TH1F("h_met_2b_f","MET, 4j 2btag",40,0,200);
	maphist["h_njets_2b_f"] = new TH1F("h_njets_2b_f","# Jets with pT>30 GeV, 4j 2b",10,0,10);

	maphist["h_mu_pt_3b_f"] = new TH1F("h_mu_pt_3b_f","Electron Pt, 4j 3btag",40,0,200);
	maphist["h_met_3b_f"] = new TH1F("h_met_3b_f","MET, 4j 3btag",40,0,200);
	maphist["h_njets_3b_f"] = new TH1F("h_njets_3b_f","# Jets with pT>30 GeV, 4j 3b",10,0,10);

	maphist["BW_nbjets_tot"] = new TH1F("BW_nbjets_tot","# b-tagged Jets with pT>30 GeV",7,0,7);
	maphist["BW_nbjets_f"] = new TH1F("BW_nbjets_f","# b-tagged Jets among leading four jets",6,0,6);

	maphist["BW_mu_pt_2b"] = new TH1F("BW_mu_pt_2b","Electron Pt, 2btag",40,0,200);
	maphist["BW_met_2b"] = new TH1F("BW_met_2b","MET, 2btag",40,0,200);
	maphist["BW_njets_2b"] = new TH1F("BW_njets_2b","# Jets with pT>30 GeV, 2b",10,0,10);

	maphist["BW_mu_pt_3b"] = new TH1F("BW_mu_pt_3b","Electron Pt, 3btag",40,0,200);
	maphist["BW_met_3b"] = new TH1F("BW_met_3b","MET, 3btag",40,0,200);
	maphist["BW_njets_3b"] = new TH1F("BW_njets_3b","# Jets with pT>30 GeV, 3b",10,0,10);
	
	maphist["BW_mu_pt_2b_f"] = new TH1F("BW_mu_pt_2b_f","Electron Pt, 4j 2btag",40,0,200);
	maphist["BW_met_2b_f"] = new TH1F("BW_met_2b_f","MET, 4j 2btag",40,0,200);
	maphist["BW_njets_2b_f"] = new TH1F("BW_njets_2b_f","# Jets with pT>30 GeV, 4j 2b",10,0,10);

	maphist["BW_mu_pt_3b_f"] = new TH1F("BW_mu_pt_3b_f","Electron Pt, 4j 3btag",40,0,200);
	maphist["BW_met_3b_f"] = new TH1F("BW_met_3b_f","MET, 4j 3btag",40,0,200);
	maphist["BW_njets_3b_f"] = new TH1F("BW_njets_3b_f","# Jets with pT>30 GeV, 4j 3b",10,0,10);

	maphist["h_njets_met"] = new TH1F("h_njets_met","# Jets with pT>30 GeV, metcut",10,0,10);
	maphist["h_mu_pt_met"] = new TH1F("h_mu_pt_met","Electron Pt, metcut",40,0,200);
	maphist["h_nbjets_met"] = new TH1F("h_nbjets_met","# b-tagged Jets with pT>30 GeV, metcut",7,0,7);
	maphist["h_nbjets_met_f"] = new TH1F("h_nbjets_met_f","# b-tagged Jets among leading four jets, metcut",6,0,6);

	maphist["h_mh_2b"] = new TH1F("h_mh_2b","mH+ 2b",30,0,180);
	maphist["h_mh_3b"] = new TH1F("h_mh_3b","mH+ 3b",30,0,180);

	
	maphist["in_met_2b"] = new TH1F("in_met_2b","In met, 2b",40,0,200);
	maphist["in_lep_2b"] = new TH1F("in_lep_2b","In lep, 2b",40,0,200);
	maphist["in_lepeta_2b"] = new TH1F("in_lepeta_2b","In lep, 2b",50,-2.5,2.5);
	maphist["in_jet1pt_2b"] = new TH1F("in_jet1pt_2b","In jet1pt, 2b",40,0,200);
	maphist["in_jet2pt_2b"] = new TH1F("in_jet2pt_2b","In jet2pt, 2b",40,0,200);
	maphist["in_jet3pt_2b"] = new TH1F("in_jet3pt_2b","In jet3pt, 2b",40,0,200);
	maphist["in_jet4pt_2b"] = new TH1F("in_jet4pt_2b","In jet4pt, 2b",40,0,200);
	maphist["in_jet1eta_2b"] = new TH1F("in_jet1eta_2b","In jet1eta, 2b",50,-2.5,2.5);
	maphist["in_jet2eta_2b"] = new TH1F("in_jet2eta_2b","In jet2eta, 2b",50,-2.5,2.5);
	maphist["in_jet3eta_2b"] = new TH1F("in_jet3eta_2b","In jet3eta, 2b",50,-2.5,2.5);
	maphist["in_jet4eta_2b"] = new TH1F("in_jet4eta_2b","In jet4eta, 2b",50,-2.5,2.5);
	
	maphist["in_met_3b"] = new TH1F("in_met_3b","In met, 3b",40,0,200);
	maphist["in_lep_3b"] = new TH1F("in_lep_3b","In lep, 3b",40,0,200);
	maphist["in_lepeta_3b"] = new TH1F("in_lepeta_3b","In lep, 3b",50,-2.5,2.5);
	maphist["in_jet1pt_3b"] = new TH1F("in_jet1pt_3b","In jet1pt, 3b",40,0,200);
	maphist["in_jet2pt_3b"] = new TH1F("in_jet2pt_3b","In jet2pt, 3b",40,0,200);
	maphist["in_jet3pt_3b"] = new TH1F("in_jet3pt_3b","In jet3pt, 3b",40,0,200);
	maphist["in_jet4pt_3b"] = new TH1F("in_jet4pt_3b","In jet4pt, 3b",40,0,200);
	maphist["in_jet1eta_3b"] = new TH1F("in_jet1eta_3b","In jet1eta, 3b",50,-2.5,2.5);
	maphist["in_jet2eta_3b"] = new TH1F("in_jet2eta_3b","In jet2eta, 3b",50,-2.5,2.5);
	maphist["in_jet3eta_3b"] = new TH1F("in_jet3eta_3b","In jet3eta, 3b",50,-2.5,2.5);
	maphist["in_jet4eta_3b"] = new TH1F("in_jet4eta_3b","In jet4eta, 3b",50,-2.5,2.5);

	maphist["fit_met_2b"] = new TH1F("fit_met_2b","Fit met, 2b",40,0,200);
	maphist["fit_lep_2b"] = new TH1F("fit_lep_2b","Fit lep, 2b",40,0,200);
	maphist["fit_jet1pt_2b"] = new TH1F("fit_jet1pt_2b","Fit jet1pt, 2b",40,0,200);
	maphist["fit_jet2pt_2b"] = new TH1F("fit_jet2pt_2b","Fit jet2pt, 2b",40,0,200);
	maphist["fit_jet3pt_2b"] = new TH1F("fit_jet3pt_2b","Fit jet3pt, 2b",40,0,200);
	maphist["fit_jet4pt_2b"] = new TH1F("fit_jet4pt_2b","Fit jet4pt, 2b",40,0,200);

	maphist["fit_met_3b"] = new TH1F("fit_met_3b","Fit met, 3b",40,0,200);
	maphist["fit_lep_3b"] = new TH1F("fit_lep_3b","Fit lep, 3b",40,0,200);
	maphist["fit_jet1pt_3b"] = new TH1F("fit_jet1pt_3b","Fit jet1pt, 3b",40,0,200);
	maphist["fit_jet2pt_3b"] = new TH1F("fit_jet2pt_3b","Fit jet2pt, 3b",40,0,200);
	maphist["fit_jet3pt_3b"] = new TH1F("fit_jet3pt_3b","Fit jet3pt, 3b",40,0,200);
	maphist["fit_jet4pt_3b"] = new TH1F("fit_jet4pt_3b","Fit jet4pt, 3b",40,0,200);


	
	
	
	/**
	 *  Remove//Overide this CHMJ_bestfitCore::MakeHistograms() to make new hists for your analysis
	 **/
	/*
	maphist["h_mu_pt"] = new TH1F("h_mu_pt","Electron Pt",50,0,200);
	maphist["h_met"] = new TH1F("h_met","MET",50,0,200);
	maphist["h_mu_pt_4jets"] = new TH1F("h_mu_pt_4jets","Electron Pt, 4jets",50,0,200);
	maphist["h_met_4jets"] = new TH1F("h_met_4jets","MET, 4jets",50,0,200);


	maphist["h_soft_jet_pt"] = new TH1F("h_soft_jet_pt","Soft jet pT",20,0,50);
	//	maphist["h_nbjets_CSVL"] = new TH1F("h_njets_CSVL","# Jets with pT>30 GeV & CSVL",10,0,10);
	//maphist["h_nbjets_CSVM"] = new TH1F("h_njets_CSVM","# Jets with pT>30 GeV & CSVM",10,0,10);
	maphist["h_csv"] = new TH1F("h_csv","CSV dist.",60,0,1);

	maphist["h_mh_comb"] = new TH1F("h_mh_comb","mH+ comb, inv chi2 weight",30,0,180);

	maphist["h_MH_match"] = new TH1F("h_MH_match","mH+ match ",50,0,200);
	maphist["h_MT_match"] = new TH1F("h_MT_match","mt match ",50,0,300);

	maphist["h_MH_matchTS"] = new TH1F("h_MH_matchTS","mH+ match TS",50,0,200);
	maphist["h_MT_matchTS"] = new TH1F("h_MT_matchTS","mt match TS",50,0,300);

	maphist["h_MH_match_raw"] = new TH1F("h_MH_match_raw","mH+ match, comb",50,0,200);
	maphist["h_MT_match_raw"] = new TH1F("h_MT_match_raw","mt match, comb ",50,0,300);
	
	maphist["h_MH_match_tscorr"] = new TH1F("h_MH_match_tscorr","mH+ match, comb tscorr ",50,0,200);
	maphist["h_MT_match_tscorr"] = new TH1F("h_MT_match_tscorr","mt match, comb tscorr ",50,0,300);

	maphist["h_MH_match_fit"] = new TH1F("h_MH_match_fit","mH+ match, fit",50,0,200);
	maphist["h_MT_match_fit"] = new TH1F("h_MT_match_fit","mt match, fit",50,0,300);
	
	maphist["h_chi2_corrfit"] = new TH1F("h_chi2_corrfit","Fitted chi2 match, corrfit",50,0,100);
	maphist["h_chi2_wrongfit"] = new TH1F("h_chi2_wrongfit","Fitted chi2 match, wrongfit",50,0,100);

	maphist["h_pt_jet1"] = new TH1F("h_pt_jet1","Leading jet PT",50,0,300);
	maphist["h_pt_jet2"] = new TH1F("h_pt_jet2","2nd jet PT",50,0,200);
	maphist["h_pt_jet3"] = new TH1F("h_pt_jet3","3rd jet PT",50,0,150);
	maphist["h_pt_jet4"] = new TH1F("h_pt_jet4","4th jet PT",50,0,100);

	maphist["h_bpt_jet1"] = new TH1F("h_bpt_jet1","Leading jet PT, b-tag",50,0,300);
	maphist["h_bpt_jet2"] = new TH1F("h_bpt_jet2","2nd jet PT, b-tag",50,0,200);
	maphist["h_bpt_jet3"] = new TH1F("h_bpt_jet3","3rd jet PT, b-tag",50,0,150);
	maphist["h_bpt_jet4"] = new TH1F("h_bpt_jet4","4th jet PT, b-tag",50,0,100);

	maphist["h_sumjets_pt"] = new TH1F("h_sumjets_pt","Pt of #Sigma loose jets, p_{T}(jet)>30GeV",50,0,500);
	//	maphist["h_sumjets_pt_soft"] = new TH1F("h_sumjets_pt_soft","Pt of sumjets, p_{T}(jet)>20GeV",50,0,500);
	maphist["h_HT"] = new TH1F("h_HT","HT with p_{T}>30GeV",50,0,2000);
	//	maphist["h_HTsoft"] = new TH1F("h_HTsoft","HT with p_{T}(jet)>20GeV",50,0,2000);

	maphist["h_minfit_chi2_match"] = new TH1F("h_minfit_chi2_match","chi2, match, minfit",50,0,100);
	maphist["h_minfit_chi2_2b_match"] = new TH1F("h_minfit_chi2_2b_match","chi2, 2btag, match, minfit",50,0,100);
	maphist["h_minfit_chi2_3b_match"] = new TH1F("h_minfit_chi2_3b_match","chi2, 3btag, match, minfit",50,0,100);
	maphist["h_minfit_mjj_match"] = new TH1F("h_minfit_mjj_match","M(jj), minuit fit",60,0,180);
	maphist["h_minfit_mjj_2b_match"] = new TH1F("h_minfit_mjj_2b_match","M(jj), minuit fit, nbtag=2",60,0,180);
	maphist["h_minfit_mjj_3b_match"] = new TH1F("h_minfit_mjj_3b_match","M(jj), minuit fit, nbtag>=3",60,0,180);

	maphist["h_minfit_chi2"] = new TH1F("h_minfit_chi2","chi2, minfit",50,0,100);
	maphist["h_minfit_chi2_2b"] = new TH1F("h_minfit_chi2_2b","chi2, 2btag, minfit",50,0,100);
	maphist["h_minfit_chi2_3b"] = new TH1F("h_minfit_chi2_3b","chi2, 3btag, minfit",50,0,100);

	maphist["h_minfit_mjj"] = new TH1F("h_minfit_mjj","M(jj), minuit fit",60,0,180);	
	maphist["h_minfit_mjj_2b"] = new TH1F("h_minfit_mjj_2b","M(jj), minuit fit, nbtag=2",60,0,180);
	maphist["h_minfit_mjj_3b"] = new TH1F("h_minfit_mjj_3b","M(jj), minuit fit, nbtag>=3",60,0,180);	


	maphist["h_jettbm_corr"] = new TH1F("h_jettbm_corr","jet mass tb, corr",50,0,100);
	maphist["h_jetatbm_corr"] = new TH1F("h_jetatbm_corr","jet mass atb, corr",50,0,100);
	maphist["h_jetq1m_corr"] = new TH1F("h_jetq1m_corr","jet mass q1, corr",50,0,100);
	maphist["h_jetq2m_corr"] = new TH1F("h_jetq2m_corr","jet mass q2, corr",50,0,100);

	maphist["h_jettbm_wrong"] = new TH1F("h_jettbm_wrong","jet mass tb, wrong",50,0,100);
	maphist["h_jetatbm_wrong"] = new TH1F("h_jetatbm_wrong","jet mass atb, wrong",50,0,100);
	maphist["h_jetq1m_wrong"] = new TH1F("h_jetq1m_wrong","jet mass q1, wrong",50,0,100);
	maphist["h_jetq2m_wrong"] = new TH1F("h_jetq2m_wrong","jet mass q2, wrong",50,0,100);

	maphist["h_jettbptdiff_corr"] = new TH1F("h_jettbptdiff_corr","jet ptdiff tb, corr",50,0,100);
	maphist["h_jetatbptdiff_corr"] = new TH1F("h_jetatbptdiff_corr","jet ptdiff atb, corr",50,0,100);
	maphist["h_jetq1ptdiff_corr"] = new TH1F("h_jetq1ptdiff_corr","jet ptdiff q1, corr",50,0,100);
	maphist["h_jetq2ptdiff_corr"] = new TH1F("h_jetq2ptdiff_corr","jet ptdiff q2, corr",50,0,100);

	maphist["h_jettbptdiff_wrong"] = new TH1F("h_jettbptdiff_wrong","jet ptdiff tb, wrong",50,0,100);
	maphist["h_jetatbptdiff_wrong"] = new TH1F("h_jetatbptdiff_wrong","jet ptdiff atb, wrong",50,0,100);
	maphist["h_jetq1ptdiff_wrong"] = new TH1F("h_jetq1ptdiff_wrong","jet ptdiff q1, wrong",50,0,100);
	maphist["h_jetq2ptdiff_wrong"] = new TH1F("h_jetq2ptdiff_wrong","jet ptdiff q2, wrong",50,0,100);


	maphist["h_mjj_secbestC"] = new TH1F("h_mjj_secbestC","secbest Criteria",30,0,180);
	maphist["h_chi2_secbestC"] = new TH1F("h_chi2_secbestC","chi2 secbest Criteria",50,0,50);

	MakeNtp("combo","fit_tb_pt:fit_tb_eta:fit_tb_phi:fit_chb_pt:fit_chb_eta:fit_chb_phi:fit_chc_pt:fit_chc_eta:fit_chc_phi:gen_tb_pt:gen_tb_eta:gen_tb_phi:gen_chb_pt:gen_chb_eta:gen_chb_phi:gen_chc_ps:gen_chc_eta:gen_chc_phi:jin_tb_pt:jin_tb_eta:jin_tb_phi:jin_chb_pt:jin_chb_eta:jin_chb_phi:jin_chc_pt:jin_chc_eta:jin_chc_phi:fitresult:chi2:btag_tb:btag_chb:btag_chc:nbtag:jin_atb_pt:jin_atb_eta:jin_atb_phi:lep_pt:lep_eta:lep_phi:met_x:met_y:gen_match:weight:mHiggs");

	//	MakeNtp("in","jet_pt1:jet_pt2:jet_pt3:angle1:angle2:angle3:nbtag:angle1r:angle2r:angle3r:mjj:hadtopin:leptopin:Fitmjj:weight");

	maphist["h_met_fitted"] = new TH1F("h_met_fitted","MET, fitted",50,0,200);
	maphist["h_met_nofit"] = new TH1F("h_met_nofit","MET, nofit",50,0,200);

	maphist["h_leppt_fitted"] = new TH1F("h_leppt_fitted","lep pT, fitted",50,0,200);
	maphist["h_leppt_nofit"] = new TH1F("h_leppt_nofit","lep pT, nofit",50,0,200);
	*/
}


void CHMJ_bestfit::ClearOutputVectors() throw(LQError) {

	// This function is called before every execute event (NO need to call this yourself.
  
	// Add any new output vector you create to this list. 
	// if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
	//
	// Reset all variables declared in Declare Variable
	//
	out_muons.clear();
	out_electrons.clear();
}

void CHMJ_bestfit::mysort(std::vector<snu::KJet> jetColl_lepveto, int jet_index[]){

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
				//if (jetColl_lepveto.at(jet_index[i]).CombinedSecVertexBtag() > jetColl_lepveto.at(temp_idx).CombinedSecVertexBtag() ){

				jet_index[k] = jet_index[i];
				jet_index[i] = temp_idx;
				continue;
			}			
		}			
	}
	return;

}

void CHMJ_bestfit::Sortout(float in1, float in2, float in3, float& out1, float& out2, float& out3){

	if (in1< in2 ){
		if (in1< in3){
			out1 = in1;
			if (in2< in3){
				out2 = in2;
				out3 = in3;
			}
			else{
				out2 = in3;
				out3 = in2;
			}
		}
		else{// tb.pt is not the smallest
			out1 = in3;
			out2 = in1;
			out3 = in2;
		}
	}
	else{ //q1.pt is smaller than tb.pt
		if (in2 < in3){
			out1 = in2;
			if (in1<in3){
				out2 = in1;
				out3 = in3;
			}
			else{
				out2 = in3;
				out3 = in1;
			}
		}
		else{
			out1 = in3;
			out2 = in2;
			out3 = in1;
		}			   
	}

	return;
}
