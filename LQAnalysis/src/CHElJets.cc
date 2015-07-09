// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQCHElJets Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "CHElJets.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"
#include "TTFitter.h"

#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (CHElJets);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
CHElJets::CHElJets() :  AnalyzerCore(),  out_electrons(0) {

	// To have the correct name in the log:
	
	SetLogName("CHElJets");

	Message("In CHElJets constructor", INFO);
	//
	// This function sets up Root files and histograms Needed in ExecuteEvents
	InitialiseAnalysis();
   
}

void CHElJets::InitialiseAnalysis() throw( LQError ) {
  
	/// Initialise histograms
	MakeHistograms();  
	//
	// You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO(3)/DEBUG(2)/WARNING 
	// You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;

	return;
}

void CHElJets::ExecuteEvents()throw( LQError ){


	m_logger << 2 << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
	m_logger << 2 << "isData = " << isData << LQLogger::endmsg;
  
	//// CHECK EFFICIENCY OF CUTS
  
	FillCutFlow("NoCut", weight);
  
	if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
	FillCutFlow("EventCut", weight);
	/// Trigger List 
	std::vector<TString> triggerslistEl;

	triggerslistEl.push_back("HLT_Ele27_WP80_v");

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

	//////////////////////////////////////////////////////
	//////////// Select objetcs
	//////////////////////////////////////////////////////   

	Bool_t debug = false;
		
	/// ELECTRONS
	std::vector<snu::KElectron> electronTightColl;
	eventbase->GetElectronSel()->TopTightElectronSelection(electronTightColl,debug);
 
  
	std::vector<snu::KElectron> electronVetoColl;
	eventbase->GetElectronSel()->TopVetoElectronSelection(electronVetoColl,debug);


	std::vector<snu::KElectron> electronNoCutColl;
	eventbase->GetElectronSel()->Selection(electronNoCutColl,debug);

	/// MUONS
	std::vector<snu::KMuon> muonVetoColl;
	eventbase->GetMuonSel()->TopVetoMuonSelection(muonVetoColl,debug);

	std::vector<snu::KMuon> muonTightColl;
	eventbase->GetMuonSel()->TopTightMuonSelection(muonTightColl,debug);
  
	std::vector<snu::KMuon> muonNoCutColl;
	eventbase->GetMuonSel()->Selection(muonNoCutColl,debug);

	/// Jets
	
	std::vector<snu::KJet> jetColl_lepveto;
	eventbase->GetJetSel()->JetTopSelection(jetColl_lepveto, muonTightColl, electronTightColl);

	std::vector<snu::KJet> jetColl_lepveto_uncor;
	eventbase->GetJetSel()->JetTopUESelection(jetColl_lepveto_uncor, muonTightColl, electronTightColl);
	
	snu::KEvent Evt = eventbase->GetEvent();
	double METv = Evt.PFMET();
	double METphi = Evt.PFMETphi();

	int jetFlavour=0;


	std::vector<snu::KTruth> genBColl;
	std::vector<snu::KTruth> TruthP;
	eventbase->GetTruthSel()->Selection(genBColl);
	
	float toppt1=0, toppt2=0;
	snu::KParticle genP_topb, genP_atopb, genP_q1, genP_q2;
	bool found_topb = false, found_atopb = false, found_q1 = false, found_q2 = false;
	
	// check four partons 	
	if (debug) cout << " GEN Coll Size = " << genBColl.size() << endl;

		
	if (debug){
		cout << " Truth particle = " << genBColl.size() << endl;
		
		cout << "--------------------------------------------------" << endl;
		cout << "Index" << '\t' << "PdgID" << '\t' << "Status" << '\t' << "Mother" << '\t' << "Pt" << '\t' << "Eta" << '\t' << "Phi" <<  endl;
		cout << "--------------------------------------------------" << endl;
	}

	int dilep = 0;
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

		if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == 6)
			toppt1 = genBColl.at(i).Pt();
		if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == -6)
			toppt2 = genBColl.at(i).Pt();
	
		int mother = genBColl.at(i).IndexMother();
		int motherID = genBColl.at(mother).PdgId();

		if (genBColl.at(mother).GenStatus() == 3 && ( abs(motherID) == 24 || abs(motherID) == 37)){
			if (debug) cout << " mother : " << motherID << " thisp " << genBColl.at(i).PdgId() << endl;
			if ( abs(genBColl.at(i).PdgId())> 10){
				dilep++;
				continue;
			}
			
			if (!found_q1 && abs(genBColl.at(i).PdgId()%2 != 0 )){ // b quark
				genP_q1 = genBColl.at(i);
				found_q1 = true;
			}
			else if (!found_q2 && abs(genBColl.at(i).PdgId()%2 == 0)){ // c quark
				genP_q2 = genBColl.at(i);
				found_q2 = true;
			}			
		}
		if (!found_topb && motherID == 6 && genBColl.at(i).PdgId() == 5){
			genP_topb = genBColl.at(i);
			found_topb = true;
		}
		if (!found_atopb && motherID == -6 && genBColl.at(i).PdgId() == -5){
			genP_atopb = genBColl.at(i);
			found_atopb = true;
		}

		TruthP.push_back(genBColl.at(i));
		
		if (found_topb && found_atopb && found_q1 && found_q2)
			break;

		// Fot fitter development, select lj only
		//	if (dilep>2) break;
		if (i>=20) break;
	}

	//	if (dilep>2) throw LQError( "Fails DiEl Gen Selection",  LQError::SkipEvent );
		
	if (debug)
		cout << " Topb : " << genP_topb.Pt() <<  ", ATopb : " << genP_atopb.Pt() << ", b quark : " << genP_q1.Pt() << ", c quark : " << genP_q2.Pt() << endl;
	
	if (toppt1 <= 400 && toppt2 <= 400){
		float corr_toppt1 = exp(0.159-0.00141*toppt1);
		float corr_toppt2 = exp(0.159-0.00141*toppt2);		
		
		weight *= sqrt(corr_toppt1*corr_toppt2);
	
		if (debug)
			cout << "PT REWEIGHTING == " << toppt1 << " => " << corr_toppt1 << ", " << toppt2 << " => " << corr_toppt2 << endl;
	}
	

	float jetPt[4], jetEta[4], jetFlav[4];
	
	// step1 : Only one tight muon
	// 

	int leptype = 0; // 1 for muon, 2 for electron
	
	float TopElTriggerSF_up_syst_factor = 1.0;
	float TopElTriggerSF_down_syst_factor = 1.0;
	float TopElIDIsoSF_up_syst_factor = 1.0;
	float TopElIDIsoSF_down_syst_factor = 1.0;

	if (electronTightColl.size()==1 && muonTightColl.size()==0) {
		leptype = 2 ;

		FillCutFlow("OneTightLep",weight);
		snu::KElectron El = electronTightColl.at(0);
		
		if (electronVetoColl.size() >1 ){
			int vetomu = 0;
			for (int i=0; i<(int)electronVetoColl.size(); i++){
				if ( electronVetoColl.at(i).DeltaR(El) > 0.01){
					vetomu++;
				}
			}
			if (vetomu>0) throw LQError( "Fails electronVeto cuts",  LQError::SkipEvent );
			 
		}

		FillCutFlow("OtherLepVeto",weight);		
		
		if(!PassTrigger(triggerslistEl, prescale))  throw LQError( "Fails Trigger cuts",  LQError::SkipEvent );
		FillCutFlow("TriggerCut",weight);		
		if (debug) cout << " Pass Trigger Cut " << endl;
		
		if (!k_isdata){
			// Get the electron trigger scale factor

			weight *= TopElTriggerScaleFactor(El.Pt(), El.Eta(), 0);
			TopElTriggerSF_up_syst_factor = TopElTriggerScaleFactor(El.Pt(),El.Eta(), 1);
			TopElTriggerSF_down_syst_factor = TopElTriggerScaleFactor(El.Pt(),El.Eta(), -1);
			
			// Get the electron ID scale factor
			weight *= TopElIDIsoScaleFactor(El.Pt(), El.Eta(), 0);
			TopElIDIsoSF_up_syst_factor = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), 1);
			TopElIDIsoSF_down_syst_factor = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), -1);
		}
		if (debug) cout << " Get EL SF " << endl;
		
		FillCutFlow("LepSF",weight);		
		FillHist("h_el_pt",El.Pt(),weight);
		FillHist("h_met",METv,weight);

		int njets = (int)jetColl_lepveto.size();
		int snjets = (int)jetColl_lepveto_uncor.size();


		if (debug){
			cout << " Num jets : " << jetColl_lepveto.size() << endl;
			cout << " Num soft jets : " << jetColl_lepveto_uncor.size() << endl;
		}
		
		FillHist("h_njets",(int)jetColl_lepveto.size(),weight);
		FillHist("h_snjets",(int)jetColl_lepveto_uncor.size(),weight);
		
		if (jetColl_lepveto.size()<4)  throw LQError( "Fails 4jets cuts",  LQError::SkipEvent );
		FillCutFlow("FourJets",weight);
		FillHist("h_el_pt_4jets",El.Pt(),weight);
		FillHist("h_met_4jets",METv,weight);

		FillHist("h_soft_jet_pt",jetColl_lepveto_uncor.back().Pt(),weight);

		if (debug )
			cout << " The last jet pt " << jetColl_lepveto_uncor.back().RawPt() << " -> " << jetColl_lepveto_uncor.back().Pt() << endl;


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

		float HT=El.Pt()+METv;
		//		float HT_softjet=El.Pt()+METv;

		//		int partonCHECK = 0;
		float dr_min = 0.3;
		int index_tb = -1, index_atb = -1, index_q1 = -1, index_q2 = -1;
		TLorentzVector jet_tb(0,0,0,0), jet_atb(0,0,0,0), jet_q1(0,0,0,0), jet_q2(0,0,0,0);
		//
		//
		// Test for selecting b-jets by CSV probability
		//
		/*
		  vector<int> index_bjet;
		  vector<int> index_ljet;
		  int index_4jets[4] = {-1, -1, -1, -1};
		  int bjet_ij = 0;
		  int bjet_csvl = 0;
		  int ljet_ij = 0;
		  int count_ij = 0;
		
		  // Select b-tagged jets first 
		  for(unsigned int ij=0; ij < jetColl_lepveto.size(); ij++){

		  double jet_btag = jetColl_lepveto.at(ij).CombinedSecVertexBtag();

		  if (jet_btag> 0.244) bjet_csvl++;
		  if (jet_btag> 0.679){ // CSVL 0.244 & CSVM 0.679
		  index_bjet.push_back(ij);
		  bjet_ij++;
		  }
		  else{
		  index_ljet.push_back(ij);
		  ljet_ij++;
		  }

		
		  TLorentzVector tempjet;
		  tempjet.SetPtEtaPhiE(jetColl_lepveto.at(ij).Pt(),jetColl_lepveto.at(ij).Eta(),jetColl_lepveto.at(ij).Phi(),jetColl_lepveto.at(ij).E());
		  sumjet_30GeV+=tempjet;
		  HT+= tempjet.Pt();
		  }
		
		  //		FillHist("h_nbjets_CSVL",bjet_csvl,weight);
		  //FillHist("h_nbjets_CSVM",bjet_ij,weight);

		  //Four jets selection: CSVL jets + highest pT jets
		  for (int i=0; i<bjet_ij; i++){
		  index_4jets[i] = index_bjet[i];
		  count_ij++;
		  }
		  //		int const Nbjets = bjet_ij;
		  if (debug) cout << " bjets = " << bjet_ij  << "("<< index_bjet.size() << ")" << " LightJets = " << ljet_ij << "(" << index_ljet.size() << ")" <<
		  ", count jets == " << count_ij << endl;

		  if (count_ij < 4){
		  int count_lj = 0;
		  for (int i=bjet_ij; i<4; i++){
		  index_4jets[i] = index_ljet.at(count_lj);
		  count_ij++; count_lj++;
		  if (count_ij == 4) break;
		  }
		  }
		*/
		// Bjet weight with selected four jets
		//
		//
		//


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
		bool double_match = false;
		
		for (int i=0; i<njets; i++){
			//			int this_idx = index_4jets[i];
			int this_idx = jidx[i];
			if (debug) cout << " This index = " << this_idx << endl;

			TLorentzVector tempjet(0,0,0,0);		   
			tempjet.SetPtEtaPhiE(jetColl_lepveto.at(this_idx).Pt(),jetColl_lepveto.at(this_idx).Eta(),jetColl_lepveto.at(this_idx).Phi(),jetColl_lepveto.at(this_idx).E());

			
			sumjet_30GeV+=tempjet;

			HT+= tempjet.Pt();

			if (i>3) continue;

			int count_match = 0;
			int bestFL = -1;			
			for(unsigned int ig=2; ig < TruthP.size(); ig++){
			
				float tempdR = tempjet.DeltaR(TruthP.at(ig));
				int PID = fabs(TruthP.at(ig).PdgId());
				if (PID >= 6) continue;

				if(tempdR < 0.3 ){
					bestFL = PID;
					count_match++;
					//					break;
					if (debug) cout << " FFFFFFFFFFFFF Check jet Flavour!!! " << tempjet.DeltaR(TruthP.at(ig)) << " to Parton " << TruthP.at(ig).PdgId() << endl;
				}
				else{
					jetFlavour = 21;
				}
				

			}
			if (bestFL > 0) jetFlavour = bestFL;
			
			if (count_match>1){
				double_match= true;
				if (debug) cout << " DDDDDDDDDDDDDDD Check this event has duplicate match " << endl;
			}


			if (debug) cout << " Gen Jet matching " << this_idx << " & Flav = " << jetFlavour << endl;	
			
			//			double tempdR = 9999;

			if (found_topb && index_tb <0)
				if (genP_topb.DeltaR(tempjet)< dr_min){
					index_tb = this_idx;
					jet_tb = tempjet;
					if (debug) cout << " Found top b jet " << this_idx << " : " << jet_tb.Pt() << " <- gen : " << genP_topb.Pt() << " dR = " << genP_topb.DeltaR(tempjet) << endl;
				}
			if (found_atopb && index_atb < 0)
				if (genP_atopb.DeltaR(tempjet)< dr_min){
					index_atb = this_idx;
					jet_atb = tempjet;
					if (debug) cout << " Found atop b jet " << this_idx << " : " << jet_atb.Pt() <<  " <- gen : " << genP_atopb.Pt() <<  " dR = " << genP_atopb.DeltaR(tempjet) << endl;
				}
			if (found_q1 && index_q1 <0)
				if (genP_q1.DeltaR(tempjet)<dr_min){
					index_q1 = this_idx;
					jet_q1 = tempjet;
					if (debug) cout << " Found H+ b jet " <<  this_idx << " : " << jet_q1.Pt() <<  " <- gen : " << genP_q1.Pt() <<  " dR = " << genP_q1.DeltaR(tempjet) << endl;
				}
			if (found_q2 && index_q2 < 0)
				if (genP_q2.DeltaR(tempjet)<dr_min){
					index_q2 = this_idx;
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

	   

		if (double_match) throw LQError( "Fails Single Gen Match",  LQError::SkipEvent );
		if (nbtags==0) throw LQError( "Fails due to Nbtags == 0",  LQError::SkipEvent );

		
		if (debug) cout << " sum 30GeV jets = " << sumjet_30GeV.Pt() << endl;

		bool genH_match =  (jet_q1.Pt()>0 && jet_q2.Pt()>0) ? true: false;
		bool genHt_match =  (genH_match && jet_tb.Pt()>0) ? true: false;
		bool genallj_match =  (genHt_match && jet_atb.Pt()>0) ? true: false;
	
		
		FillHist("h_pt_jet1",jetPt[0],weight);
		FillHist("h_pt_jet2",jetPt[1],weight);
		FillHist("h_pt_jet3",jetPt[2],weight);
		FillHist("h_pt_jet4",jetPt[3],weight);

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
			FillHist("h_el_pt_2btag",El.Pt(),weight);
			FillHist("h_met_2btag",METv,weight);
		}
		if (nbtags >=3){
			FillCutFlow(">=3Bjets", weight);
			FillHist("h_el_pt_3btag",El.Pt(),weight);
			FillHist("h_met_3btag",METv,weight);
		}


		
		TLorentzVector El_vec;
		El_vec.SetPtEtaPhiE(El.Pt(),El.Eta(),El.Phi(),El.E());

		TLorentzVector met;
		met.SetPxPyPzE(METv*cos(METphi),METv*sin(METphi),0,0); 	   

		/*
		  TLorentzVector sumjets;
		  for (int ij=0; ij<njets; ij++){
		  TLorentzVector tempjet;
		  tempjet.SetPtEtaPhiE(jetColl_lepveto.at(ij).Pt(),jetColl_lepveto.at(ij).Eta(),jetColl_lepveto.at(ij).Phi(),jetColl_lepveto.at(ij).E());
		  sumjets += tempjet;
		  HT_softjet+= tempjet.Pt();
		  }
		*/

		
		FillHist("h_sumjets_pt",sumjet_30GeV.Pt(),weight);
		FillHist("h_HT",HT,weight);
		//FillHist("h_HTsoft",HT_softjet,weight);

		// Get tstype corrections
		int ntype = 14; 
		//myfit->GetTSCorr(jets_f, ntype, debug);

		//		DoFits(El_vec,met,sumjets,jets_f,nbtags,btag_f,debug);
		//
		
		float sigmalep = 0.5*(Evt.PFMET_El_EnUp()-METv) + 0.5*(Evt.PFMET_El_EnDown()-METv);
		sigmalep = 0.01*El_vec.Pt();  // Et difference is too small, so assign 1% 

		if (debug) cout << "::::::::: Sigmalep = " << sigmalep << endl;


		//		if (!genallj_match)  throw LQError( "Fails Higgs match",  LQError::SkipEvent );

		myfit->Fit(El_vec,sigmalep,jets_f,jetraw_f,btag_f,sumjet_uncorr,met,0, ntype, debug);

				
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
		double invchi2[24]; std::fill_n(invchi2, 24, -1);
		double mh[24]; std::fill_n(mh, 24, -1);
		
		for (int i=0; i<24; i++){

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


			if (debug) cout << "CHECKCHECKCHECK : " << i << ", chi2 = " << myfit->Chi2[i] << ", mH = " << myfit->HMass[i] << endl;

			if (genHt_match){
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

		if (debug){
			cout << " Myfit invchi2 ==========================" << endl;
			for (int k=0; k<24; k++){
				cout << " Chi2 && mh check : " << invchi2[k] << " && " << mh[k] <<  " > " << sum_invchi2 << " ==> prob " << invchi2[k]/sum_invchi2 << endl;

			}
			cout << " End invchi2 ==========================" << endl;
		}

		for (int i=0; i<24; i++){
			if (invchi2[i]>-1){
				FillHist("h_mh_comb",mh[i],weight*invchi2[i]/sum_invchi2);
			}
		}
		
		
		FillHist("h_met_nofit",METv,weight);
		FillHist("h_met_fitted",myfit->FittedNeu[bestidx].Pt(),weight);

		FillHist("h_leppt_nofit",El_vec.Pt(),weight);
		FillHist("h_leppt_fitted",myfit->FittedLep[bestidx].Pt(),weight);

		if (chi2<10){		
			FillHist("h_minfit_chi2",chi2,weight);
			FillHist("h_minfit_mjj",mHiggs,weight);
			
			if (genH_match){
				FillHist("h_minfit_chi2_match",chi2,weight);
				FillHist("h_minfit_mjj_match",mHiggs,weight);
			}
			
			
			if (nbtags>=2){
				FillHist("h_minfit_mjj_2b",mHiggs,weight);
				FillHist("h_minfit_chi2_2b",chi2,weight);
				
				if (genH_match){
					FillHist("h_minfit_chi2_2b_match",chi2,weight);
					FillHist("h_minfit_mjj_2b_match",mHiggs,weight);
				}
				
				if (nbtags>=3){
					FillHist("h_minfit_mjj_3b",mHiggs,weight);
					FillHist("h_minfit_chi2_3b",chi2,weight);
					
					if (genH_match){
						FillHist("h_minfit_chi2_3b_match",chi2,weight);
						FillHist("h_minfit_mjj_3b_match",mHiggs,weight);
					}
					
				}
			}
		}
		
		if (debug){
			if (myfit->FittedJets[bestidx][0].Pt()<20 || myfit->FittedJets[bestidx][1].Pt()<20 || myfit->FittedJets[bestidx][2].Pt()<20 || myfit->FittedJets[bestidx][3].Pt()<20) cout << " ????????????? Check This Events " << endl;
			cout << "    " << endl;
			cout << " Jet CHI " << myfit->JetChi[0][bestidx] << ", " <<  myfit->JetChi[1][bestidx] << ", " <<  myfit->JetChi[2][bestidx] << ", " <<  myfit->JetChi[3][bestidx] << endl;

		}

		// Check the jets
		FillHist("h_fitted_jet1",myfit->FittedJets[bestidx][0].Pt(),weight); // lepb jets
		FillHist("h_fitted_jet2",myfit->FittedJets[bestidx][1].Pt(),weight); // hadb jets
		FillHist("h_fitted_jet3",myfit->FittedJets[bestidx][2].Pt(),weight); // w jets
		FillHist("h_fitted_jet4",myfit->FittedJets[bestidx][3].Pt(),weight); // w jets

		FillHist("h_rawpt_jet1",myfit->rawJets[bestidx][0].Pt(),weight); // lepb jets
		FillHist("h_rawpt_jet2",myfit->rawJets[bestidx][1].Pt(),weight); // hadb jets
		FillHist("h_rawpt_jet3",myfit->rawJets[bestidx][2].Pt(),weight); // w jets
		FillHist("h_rawpt_jet4",myfit->rawJets[bestidx][3].Pt(),weight); // w jets

		FillHist("h_tscorrpt_jet1",myfit->jetsIN[bestidx][0].Pt(),weight); // lepb jets
		FillHist("h_tscorrpt_jet2",myfit->jetsIN[bestidx][1].Pt(),weight); // hadb jets
		FillHist("h_tscorrpt_jet3",myfit->jetsIN[bestidx][2].Pt(),weight); // w jets
		FillHist("h_tscorrpt_jet4",myfit->jetsIN[bestidx][3].Pt(),weight); // w jets	

		TLorentzVector MH_raw, MT_raw, MH_tscorr, MT_tscorr, MH_fit, MT_fit;
		MH_raw = myfit->rawJets[bestidx][2]+myfit->rawJets[bestidx][3];
		MT_raw = myfit->rawJets[bestidx][1]+MH_raw;
		FillHist("h_MH_match_raw",MH_raw.M(),weight);
		FillHist("h_MT_match_raw",MT_raw.M(),weight);

		FillHist("h_best_chi2",myfit->bestchi2,weight);
		FillHist("h_best_mjj",myfit->bestHmass,weight);
		FillHist("h_best_mt",myfit->bestmass,weight);		

		TLorentzVector jin_tb, jin_q1, jin_q2, jin_atb;

		jin_tb = myfit->jetsIN[bestidx][1];
		jin_atb = myfit->jetsIN[bestidx][0];
		jin_q1 = myfit->jetsIN[bestidx][2];
		jin_q2 = myfit->jetsIN[bestidx][3];
		
		MH_tscorr = jin_q1+jin_q2;
		MT_tscorr = jin_tb+MH_tscorr;
		FillHist("h_MH_match_tscorr",MH_tscorr.M(),weight);
		FillHist("h_MT_match_tscorr",MT_tscorr.M(),weight);
		
		TLorentzVector fit_q1, fit_q2, fit_tb;

		fit_q1 = myfit->FittedJets[bestidx][2];
		fit_q2 = myfit->FittedJets[bestidx][3];

		MH_fit = fit_q1+fit_q2;

		//		cout << " MH_fit " << fit_q
		fit_tb = myfit->FittedJets[bestidx][1];
				 
		MT_fit = fit_tb+MH_fit;
		FillHist("h_MH_match_fit",MH_fit.M(),weight);
		FillHist("h_MT_match_fit",MT_fit.M(),weight);

		if (debug){
			cout << " Selected Fits(" << bestidx << ") : JetChi2 = " << myfit->JetChi[0][bestidx] << ", " << myfit->JetChi[1][bestidx] << ", " << myfit->JetChi[2][bestidx] << ", " << myfit->JetChi[3][bestidx] << " & " << myfit->HadTopChi[bestidx] << endl;
			cout << " Angles : (tb,B) = " << fit_tb.DeltaR(fit_q1) << " vs (tb,C) " << fit_tb.DeltaR(fit_q2) << " vs (B,C) " << fit_q1.DeltaR(fit_q2) << endl;
			cout << " The best fit : " << chi2 << " mH = " << mHiggs << endl;
			cout << " Count Mass from fitter : " << myfit->Chi2[bestidx] << " mt = " << myfit->Mass[bestidx]<< endl;

		}


		bool fitcorr = false;

		if ( genHt_match && ( (fit_q1.DeltaR(jet_q1)<0.1 && fit_q2.DeltaR(jet_q2)<0.1) ||
							  (fit_q1.DeltaR(jet_q2)<0.1 && fit_q2.DeltaR(jet_q1)<0.1) ) &&
			 myfit->FittedJets[bestidx][1].DeltaR(jet_tb)<0.1){

			FillHist("h_MH_match_corrfit",MH_fit.M(),weight);
			FillHist("h_MT_match_corrfit",MT_fit.M(),weight);
			FillHist("h_chi2_corrfit",chi2,weight);

			FillHist("h_jet1_scale_corr",myfit->Scale[bestidx][0],weight);
			FillHist("h_jet2_scale_corr",myfit->Scale[bestidx][1],weight);
			FillHist("h_jet3_scale_corr",myfit->Scale[bestidx][2],weight);
			FillHist("h_jet4_scale_corr",myfit->Scale[bestidx][3],weight);

			FillHist("h_jet1_chi_corr",myfit->JetChi[0][bestidx],weight);
			FillHist("h_jet2_chi_corr",myfit->JetChi[1][bestidx],weight);
			FillHist("h_jet3_chi_corr",myfit->JetChi[2][bestidx],weight);
			FillHist("h_jet4_chi_corr",myfit->JetChi[3][bestidx],weight);

			FillHist("h_Wchi_corr",myfit->HadWChi[bestidx],weight);
			fitcorr = true;					 
			
		}
		else{

			FillHist("h_MH_match_wrongfit",MH_fit.M(),weight);
			FillHist("h_MT_match_wrongfit",MT_fit.M(),weight);			
			FillHist("h_chi2_wrongfit",chi2,weight);

			FillHist("h_MH_match_wrongfit_topbB",(fit_tb+fit_q1).M(),weight);
			FillHist("h_MH_match_wrongfit_topbC",(fit_tb+fit_q2).M(),weight);

			FillHist("h_jet1_scale_wron",myfit->Scale[bestidx][0],weight);
			FillHist("h_jet2_scale_wron",myfit->Scale[bestidx][1],weight);
			FillHist("h_jet3_scale_wron",myfit->Scale[bestidx][2],weight);
			FillHist("h_jet4_scale_wron",myfit->Scale[bestidx][3],weight);

			FillHist("h_jet1_chi_wron",myfit->JetChi[0][bestidx],weight);
			FillHist("h_jet2_chi_wron",myfit->JetChi[1][bestidx],weight);
			FillHist("h_jet3_chi_wron",myfit->JetChi[2][bestidx],weight);
			FillHist("h_jet4_chi_wron",myfit->JetChi[3][bestidx],weight);

			FillHist("h_Wchi_wron",myfit->HadWChi[bestidx],weight);

			FillHist("h_wrongdR_jj",fit_q1.DeltaR(fit_q2),weight);
			//			FillHist("h_wrongdR_vs_chi2",fit_q1.DeltaR(fit_q2),myfit->Chi2[bestidx],weight,0,3.3,100,0,20,10);
			FillHist("h_wrongdR_vs_chi2",fit_q1.DeltaR(fit_q2),myfit->Chi2[bestidx],weight,0,3.3,100,0,20,10);
		
		}

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

		float high_mjj;
		if (fabs(jin_tb.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_q1+ jin_q2).M();
		}
		else if (fabs(jin_q1.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_tb+ jin_q2).M();
		}
		else if (fabs(jin_q2.Pt() - jet_pt1)<0.1){
			high_mjj = (jin_tb+jin_q1).M();
		}

		FillHist("h_high_mjj",high_mjj,weight);			
			  			
		float in_list[11];
		float in_tag[10];

		in_list[6] = nbtags;
		in_list[0] = jet_pt1;
		in_list[1] = jet_pt2;
		in_list[2] = jet_pt3;
		in_list[3] = jet_angle1;
		in_list[4] = jet_angle2;
		in_list[5] = jet_angle3;
		in_list[7] = jet_angle1_r;
		in_list[8] = jet_angle2_r;
		in_list[9] = jet_angle3_r;
		in_list[10] = high_mjj;
		FillNtp("in",in_list);


		TLorentzVector gen_tb(-100,-100,-100,-100), gen_chb(-100,-100,-100,-100), gen_chc(-100,-100,-100,-100), gen_atb(-100,-100,-100,-100);
		int btag_tb=0, btag_chb=0, btag_chc=0;

		if (genallj_match){
			

			// check corresponding parton
			// gen particle LorentzVector: genP_topb, genP_atopb, genP_q1, genP_q2;
			TLorentzVector genARRAY[4] = {genP_atopb, genP_topb, genP_q1, genP_q2};
			if (debug) cout << " GEN MATCHING AGAIN " << genARRAY[0].Eta() << ", " << genARRAY[1].Eta() << ", " << genARRAY[2].Eta() << ", " << genARRAY[3].Eta() << endl;

			if (debug) cout << " FITTER RESULT " << fit_tb.Pt() << ", " << fit_q1.Pt() << ", " << fit_q2.Pt() << endl;
		

			for (int i=0; i<4; i++){

				float tempdR = fit_tb.DeltaR(genARRAY[i]);
				if (debug)			cout << " == tempdR = " << tempdR << endl;

				if (tempdR<0.3){
					gen_tb = genARRAY[i];
					if (debug) cout << " Found gen_tb to fit_tb : " << genARRAY[i].Pt() << " to " << fit_tb.Pt() << endl;
				}
				tempdR = fit_tb.DeltaR(jets_f[i]);
				if (tempdR<0.3){
					if (btag_f[i]) btag_tb++;
				}

			
				tempdR = fit_q1.DeltaR(genARRAY[i]);
				if (debug)			cout << " == tempdR = " << tempdR << endl;
			
				if (tempdR<0.3){
					gen_chb = genARRAY[i];
					if (debug) cout << " Found gen_chb to fit_chb : " << genARRAY[i].Pt() << " to " << fit_q1.Pt() << endl;
				}
				tempdR = fit_q1.DeltaR(jets_f[i]);
				if (tempdR<0.3){
					if (btag_f[i]) btag_chb++;
				}

				tempdR = fit_q2.DeltaR(genARRAY[i]);
				if (debug)			cout << " == tempdR = " << tempdR << endl;
			
				if (tempdR<0.3){
					gen_chc = genARRAY[i];
					if (debug) cout << " Found gen_chc to fit_chc : " << genARRAY[i].Pt() << " to " << fit_q2.Pt() << endl;
				}
				tempdR = fit_q2.DeltaR(jets_f[i]);
				if (tempdR<0.3){
					if (btag_f[i]) btag_chc++;
				}


			}
		}		
		
		float fitterStudy[41];
		//if (debug) cout << " Where1?" << endl;
		fitterStudy[0] = fit_tb.Pt();
		fitterStudy[1] = fit_tb.Eta();
		fitterStudy[2] = fit_tb.Phi();
		fitterStudy[3] = fit_q1.Pt();
		fitterStudy[4] = fit_q1.Eta();
		fitterStudy[5] = fit_q1.Phi();
		fitterStudy[6] = fit_q2.Pt();
		fitterStudy[7] = fit_q2.Eta();
		fitterStudy[8] = fit_q2.Phi();
		//if (debug) cout << " Where2?" << endl;
		fitterStudy[9] = gen_tb.Pt();
		fitterStudy[10] = gen_tb.Eta();
		fitterStudy[11] = gen_tb.Phi();		
		fitterStudy[12] = gen_chb.Pt();
		fitterStudy[13] = gen_chb.Eta();
		fitterStudy[14] = gen_chb.Phi();		
		fitterStudy[15] = gen_chc.Pt();
		fitterStudy[16] = gen_chc.Eta();
		fitterStudy[17] = gen_chc.Phi();		
		//if (debug) cout << " Where3?" << endl;
		fitterStudy[18] = jin_tb.Pt();
		fitterStudy[19] = jin_tb.Eta();
		fitterStudy[20] = jin_tb.Phi();		
		fitterStudy[21] = jin_q1.Pt();
		fitterStudy[22] = jin_q1.Eta();
		fitterStudy[23] = jin_q1.Phi();		
		fitterStudy[24] = jin_q2.Pt();
		fitterStudy[25] = jin_q2.Eta();
		fitterStudy[26] = jin_q2.Phi();
		//		if (debug) cout << " Where4?" << endl;
		fitterStudy[27] = fitcorr;
		fitterStudy[28] = chi2;

		fitterStudy[29] = btag_tb;
		fitterStudy[30] = btag_chb;
		fitterStudy[31] = btag_chc;
		fitterStudy[32] = nbtags;

		fitterStudy[33] = jin_atb.Pt();
		fitterStudy[34] = jin_atb.Eta();
		fitterStudy[35] = jin_atb.Phi();
		fitterStudy[36] = El_vec.Pt();
		fitterStudy[37] = El_vec.Eta();
		fitterStudy[38] = El_vec.Phi();
		fitterStudy[39] = met.X();
		fitterStudy[40] = met.Y();
		
		FillNtp("combo",fitterStudy);		
	}		
	
	
	return;
	
}


void CHElJets::EndCycle()throw( LQError ){
	
	Message("In EndCycle" , INFO);
}


void CHElJets::BeginCycle() throw( LQError ){
  
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

CHElJets::~CHElJets() {
  
	Message("In CHElJets Destructor" , INFO);
	if(!k_isdata)delete reweightPU;
	if(!k_isdata) delete fBTagSF;
	delete myfit;
	//	delete minuit;
}
         
void CHElJets::FillCutFlow(TString cut, float weight){
  
	if(GetHist("cutflow")) {
		GetHist("cutflow")->Fill(cut,weight);
	}
	else{
		AnalyzerCore::MakeHistograms("cutflow",11,0.,11.);
    
		GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"OneTightLep");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"OtherLepVeto");		
		GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"TriggerCut");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"LepSF");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"FourJets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"MET>20");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"2Bjets");
		GetHist("cutflow")->GetXaxis()->SetBinLabel(11,">=3Bjets");
	}
}
     
void CHElJets::BeginEvent( )throw( LQError ){

	Message("In BeginEvent() " , DEBUG);

	return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void CHElJets::MakeHistograms(){
	//// Additional plots to make
    
	maphist.clear();
	AnalyzerCore::MakeHistograms();
	Message("Made histograms", INFO);
	/**
	 *  Remove//Overide this CHElJetsCore::MakeHistograms() to make new hists for your analysis
	 **/

	maphist["h_el_pt"] = new TH1F("h_el_pt","Electron Pt",50,0,200);
	maphist["h_met"] = new TH1F("h_met","MET",50,0,200);
	maphist["h_el_pt_4jets"] = new TH1F("h_el_pt_4jets","Electron Pt, 4jets",50,0,200);
	maphist["h_met_4jets"] = new TH1F("h_met_4jets","MET, 4jets",50,0,200);
	maphist["h_el_pt_2btag"] = new TH1F("h_el_pt_2btag","Electron Pt, 4j 2btag",50,0,200);
	maphist["h_met_2btag"] = new TH1F("h_met_2btag","MET, 4j 2btag",50,0,200);
	maphist["h_el_pt_3btag"] = new TH1F("h_el_pt_3btag","Electron Pt, 4j 3btag",50,0,200);
	maphist["h_met_3btag"] = new TH1F("h_met_3btag","MET, 4j 3btag",50,0,200);

	maphist["h_njets"] = new TH1F("h_njets","# Jets with pT>30 GeV",10,0,10);
	maphist["h_snjets"] = new TH1F("h_snjets","# Jets with pT>10 GeV",20,0,20);
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

	maphist["h_MH_match_corrfit"] = new TH1F("h_MH_match_corrfit","mH+ match, corrfit",50,0,200);
	maphist["h_MT_match_corrfit"] = new TH1F("h_MT_match_corrfit","mt match, corrfit",50,0,300);
	maphist["h_MH_match_wrongfit"] = new TH1F("h_MH_match_wrongfit","mH+ match, wrongfit",50,0,200);
	maphist["h_MT_match_wrongfit"] = new TH1F("h_MT_match_wrongfit","mt match, wrongfit",50,0,300);

	maphist["h_MH_match_wrongfit_topbC"] = new TH1F("h_MH_match_wrongfit_topbC","mH+ match, wrongfit, topb & C",50,0,200);
	maphist["h_MH_match_wrongfit_topbB"] = new TH1F("h_MH_match_wrongfit_topbB","mH+ match, wrongfit, topb & B",50,0,200);

	maphist["h_wrongfit_goodTS"] = new TH1F("h_wrongfit_goodTS","mH+ TS good match, wrongfit sel",50,0,200);
	maphist["h_wrongfit_badTS"] = new TH1F("h_wrongfit_badTS","mH+ TS bad match, wrongfit sel",50,0,200);

	//	maphist["h_wrongfit_goodTS"] = new TH1F("h_wrongfit_goodTS","mH+ TS good match, wrongfit sel",50,0,200);
	//	maphist["h_wrongfit_badTS"] = new TH1F("h_wrongfit_badTS","mH+ TS bad match, wrongfit sel",50,0,200);

	maphist["h_wrongfit_goodTS_chi2"] = new TH1F("h_wrongfit_goodTS_chi2","mH+ TS good match, wrongfit sel, chi2",50,0,100);
	maphist["h_wrongfit_badTS_chi2"] = new TH1F("h_wrongfit_badTS_chi2","mH+ TS bad match, wrongfit chi2",50,0,100);
	
	
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

	maphist["h_best_chi2"] = new TH1F("h_best_chi2","bestchi2, minfit",50,0,100);
	maphist["h_best_mjj"] = new TH1F("h_best_mjj","M(jj), minfit",60,0,180);
	maphist["h_best_mt"] = new TH1F("h_best_mt","M(t), minfit",60,0,180);
	
	maphist["h_minfit_raw_mjj"] = new TH1F("h_minfit_raw_mjj","M(jj), RAW jets",60,0,180);
	maphist["h_minfit_tscorr_mjj"] = new TH1F("h_minfit_tscorr_mjj","M(jj), ts corr",60,0,180);
	maphist["h_chi2"] = new TH1F("h_chi2","Mass const. only #chi^{2}",50,0,100);
	//	maphist["h_minfit_chi2"] = new TH1F("h_minfit_chi2","Minuit #chi^{2}",50,0,100);

	//	MakeNtp("myntp","minfit_mjj:minfit_chi2:minfit_raw_mjj:minfit_tscorr_mjj:fit_mjj:fit_chi2:weight:nbtag");

	//	MakeNtp("fitinfo","jet0_pt:jet0_eta:jet0_phi:jet0_bcorr:jet0_ccorr:jet0_lcorr:jet0_berr:jet0_cerr:jet0_lerr:jet0_btag:jet1_pt:jet1_eta:jet1_phi:jet1_bcorr:jet1_ccorr:jet1_lcorr:jet1_berr:jet1_cerr:jet1_lerr:jet1_btag:jet2_pt:jet2_eta:jet2_phi:jet2_bcorr:jet2_ccorr:jet2_lcorr:jet2_berr:jet2_cerr:jet2_lerr:jet2_btag:jet3_pt:jet3_eta:jet3_phi:jet3_bcorr:jet3_ccorr:jet3_lcorr:jet3_berr:jet3_cerr:jet3_lerr:jet3_btag:extraj_px:extraj_py:extraj_pz:extraj_e:sigmauncl:lep_pt:lep_eta:lep_phi:lep_e:sigmalep:met_px:met_py:met_pz0:met_pz1:tstype:weight");

	MakeNtp("combo","fit_tb_pt:fit_tb_eta:fit_tb_phi:fit_chb_pt:fit_chb_eta:fit_chb_phi:fit_chc_pt:fit_chc_eta:fit_chc_phi:gen_tb_pt:gen_tb_eta:gen_tb_phi:gen_chb_pt:gen_chb_eta:gen_chb_phi:gen_chc_ps:gen_chc_eta:gen_chc_phi:jin_tb_pt:jin_tb_eta:jin_tb_phi:jin_chb_pt:jin_chb_eta:jin_chb_phi:jin_chc_pt:jin_chc_eta:jin_chc_phi:fitresult:chi2:btag_tb:btag_chb:btag_chc:nbtag:jin_atb_pt:jin_atb_eta:jin_atb_phi:lep_pt:lep_eta:lep_phi:met_x:met_y");

	MakeNtp("in","jet_pt1:jet_pt2:jet_pt3:angle1:angle2:angle3:nbtag:angle1r:angle2r:angle3r:mjj");

	maphist["h_met_fitted"] = new TH1F("h_met_fitted","MET, fitted",50,0,200);
	maphist["h_met_nofit"] = new TH1F("h_met_nofit","MET, nofit",50,0,200);

	maphist["h_leppt_fitted"] = new TH1F("h_leppt_fitted","lep pT, fitted",50,0,200);
	maphist["h_leppt_nofit"] = new TH1F("h_leppt_nofit","lep pT, nofit",50,0,200);

	maphist["h_tscorrpt_jet1"] = new TH1F("h_tscorrpt_jet1","Leading jetsIN PT",50,0,300);
	maphist["h_tscorrpt_jet2"] = new TH1F("h_tscorrpt_jet2","2nd jetsIN PT",50,0,200);
	maphist["h_tscorrpt_jet3"] = new TH1F("h_tscorrpt_jet3","3rd jetsIN PT",50,0,150);
	maphist["h_tscorrpt_jet4"] = new TH1F("h_tscorrpt_jet4","4th jetsIN PT",50,0,100);

	maphist["h_fitted_jet1"] = new TH1F("h_fitted_jet1","Leading fitted PT",50,0,300);
	maphist["h_fitted_jet2"] = new TH1F("h_fitted_jet2","2nd fitted PT",50,0,200);
	maphist["h_fitted_jet3"] = new TH1F("h_fitted_jet3","3rd fitted PT",50,0,150);
	maphist["h_fitted_jet4"] = new TH1F("h_fitted_jet4","4th fitted PT",50,0,100);

	maphist["h_rawpt_jet1"] = new TH1F("h_rawpt_jet1","Leading jetsRAW PT",50,0,300);
	maphist["h_rawpt_jet2"] = new TH1F("h_rawpt_jet2","2nd jetsRAW PT",50,0,200);
	maphist["h_rawpt_jet3"] = new TH1F("h_rawpt_jet3","3rd jetsRAW PT",50,0,150);
	maphist["h_rawpt_jet4"] = new TH1F("h_rawpt_jet4","4th jetsRAW PT",50,0,100);

	maphist["h_jet1_scale_corr"] = new TH1F("h_jet1_scale_corr","Jet1 Scale, cor fit",100,-5,5);
	maphist["h_jet2_scale_corr"] = new TH1F("h_jet2_scale_corr","Jet2 Scale, cor fit",100,-5,5);
	maphist["h_jet3_scale_corr"] = new TH1F("h_jet3_scale_corr","Jet3 Scale, cor fit",100,-5,5);
	maphist["h_jet4_scale_corr"] = new TH1F("h_jet4_scale_corr","Jet4 Scale, cor fit",100,-5,5);

	maphist["h_jet1_chi_corr"] = new TH1F("h_jet1_chi_corr","Jet1 Chi, cor fit",100,-10,10);
	maphist["h_jet2_chi_corr"] = new TH1F("h_jet2_chi_corr","Jet2 Chi, cor fit",100,-10,10);
	maphist["h_jet3_chi_corr"] = new TH1F("h_jet3_chi_corr","Jet3 Chi, cor fit",100,-10,10);
	maphist["h_jet4_chi_corr"] = new TH1F("h_jet4_chi_corr","Jet4 Chi, cor fit",100,-10,10);

	maphist["h_Wchi_corr"] = new TH1F("h_Wchi_corr","Whad Chi, cor fit",100,-10,10);


	maphist["h_jet1_scale_wron"] = new TH1F("h_jet1_scale_wron","Jet1 Scale, wro fit",100,-5,5);
	maphist["h_jet2_scale_wron"] = new TH1F("h_jet2_scale_wron","Jet2 Scale, wro fit",100,-5,5);
	maphist["h_jet3_scale_wron"] = new TH1F("h_jet3_scale_wron","Jet3 Scale, wro fit",100,-5,5);
	maphist["h_jet4_scale_wron"] = new TH1F("h_jet4_scale_wron","Jet4 Scale, wro fit",100,-5,5);

	maphist["h_jet1_chi_wron"] = new TH1F("h_jet1_chi_wron","Jet1 Chi, wro fit",100,-10,10);
	maphist["h_jet2_chi_wron"] = new TH1F("h_jet2_chi_wron","Jet2 Chi, wro fit",100,-10,10);
	maphist["h_jet3_chi_wron"] = new TH1F("h_jet3_chi_wron","Jet3 Chi, wro fit",100,-10,10);
	maphist["h_jet4_chi_wron"] = new TH1F("h_jet4_chi_wron","Jet4 Chi, wro fit",100,-10,10);

	maphist["h_Wchi_wron"] = new TH1F("h_Wchi_wron","Whad Chi, wro fit",100,-10,10);

	maphist["h_corrdR_jj"] = new TH1F("h_corrdR_jj","corrdR(jj)",30,0,3.3);
	maphist["h_wrongdR_jj"] = new TH1F("h_wrongdR_jj","wrongdR(jj), selected",30,0,3.3);

	maphist2D["h_corrdR_vs_chi2"] = new TH2F("h_corrdR_vs_chi2","corrdR(jj) vs chi2",100,0,3.3,10,0,20);
	maphist2D["h_wrongdR_vs_chi2"] = new TH2F("h_wrongdR_vs_chi2","wrongdR(jj) vs chi2, selected",100,0,3.3,10,0,20);
	maphist["h_high_mjj"] = new TH1F("h_high_mjj","M(jj) highest pt jet",30,0,180);

}


void CHElJets::ClearOutputVectors() throw(LQError) {

	// This function is called before every execute event (NO need to call this yourself.
  
	// Add any new output vector you create to this list. 
	// if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
	//
	// Reset all variables declared in Declare Variable
	//
	out_muons.clear();
	out_electrons.clear();
}

void CHElJets::mysort(std::vector<snu::KJet> jetColl_lepveto, int jet_index[]){

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

void CHElJets::Sortout(float in1, float in2, float in3, float& out1, float& out2, float& out3){

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
