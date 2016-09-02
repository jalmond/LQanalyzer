// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQCHElJets_v3_sig Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @Author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "CHElJets_v3_sig.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"
#include "BaseSelection.h"
#include "TTFitter.h"


#include <iostream>
#include <TROOT.h>
#include <TMinuit.h>


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (CHElJets_v3_sig);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
CHElJets_v3_sig::CHElJets_v3_sig() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:
 
  SetLogName("CHElJets_v3_sig");
  Message("In CHElJets_v3_sig constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();  
}


void CHElJets_v3_sig::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms("");  
  MakeHistograms("JESup");  
  MakeHistograms("JESdown");  
  MakeHistograms("JERup");  
  MakeHistograms("JERdown");  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO(3)/DEBUG(2)/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

  return;
}



void CHElJets_v3_sig::ExecuteEvents()throw( LQError ){

  float default_weight = weight;
  int keep_event= ExecuteSystematics(0, "");
  if(!k_running_chargeflip){
    weight=default_weight;
    keep_event+=    ExecuteSystematics(1, "JESup");
    weight=default_weight;
    keep_event+=    ExecuteSystematics(2, "JESdown");
    weight=default_weight;
    keep_event+=    ExecuteSystematics(3, "JERup");
    weight=default_weight;
    keep_event+=    ExecuteSystematics(4, "JERdown");
  }
  if(keep_event==0)throw LQError( "Fails basic cuts",  LQError::SkipEvent ); 
}

int CHElJets_v3_sig::ExecuteSystematics(int method, TString label)throw( LQError ){
  
    
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
  triggerslistMu.push_back("HLT_Ele27_WP80_v");

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


  Bool_t debug = false;
		
  /// ELECTRONS
  std::vector<snu::KElectron> electronTightColl;
  float iso_el = 1.0;
  eventbase->GetElectronSel()->TopTightElectronSelectionv1(electronTightColl,iso_el,debug);

  if (debug){
    if (electronTightColl.size()>0)
      cout << " iso el = " << iso_el << endl;
  }
  
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->TopVetoElectronSelectionv1(electronVetoColl,debug);

  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->TopVetoMuonSelection(muonVetoColl,debug);

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->TopTightMuonSelection(muonTightColl,debug);
 
  // JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_lepveto_soft;
  eventbase->GetJetSel()->JetchsTopSelectionv1(jetColl_lepveto, muonVetoColl, electronVetoColl, method);
  eventbase->GetJetSel()->JetchsTopUESelectionv1(jetColl_lepveto_soft, muonVetoColl, electronVetoColl,method);
    

  snu::KEvent Evt = eventbase->GetEvent();
    
  int jetFlavour=0;
    
  std::vector<snu::KTruth> genBColl;
  eventbase->GetTruthSel()->Selection(genBColl);
    
  float toppt1=10000, toppt2=10000;
  snu::KTruth vec_top1, vec_top2;

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

  bool  foundQ1 = false, foundQ2 = false;
  snu::KParticle genP_q1, genP_q2;

  if (!k_isdata){
    bool found_el = false;
    bool found_mu = false;
    bool found_tau = false;
	 int dilep = 0;	    
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

      int mother = 	  genBColl.at(i).IndexMother();
      if (abs(genBColl.at(i).PdgId()) > 10 && abs(genBColl.at(i).PdgId()) < 20  && genBColl.at(mother).GenStatus() == 3 && (abs( genBColl.at(mother).PdgId() ) == 24) ){
      dilep++;
    }
      if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == 6){
	toppt1 = genBColl.at(i).Pt();
	vec_top1=genBColl.at(i);
	found_top = true;
      }
      if (genBColl.at(i).GenStatus() == 3 && genBColl.at(i).PdgId() == -6){
	toppt2 = genBColl.at(i).Pt();
	vec_top2=genBColl.at(i);
	found_atop = true;
      }

      if (abs(genBColl.at(i).PdgId()) < 6 && genBColl.at(mother).GenStatus() == 3 && (abs( genBColl.at(mother).PdgId() ) == 24) ){
	if (!foundQ1 && abs(genBColl.at(i).PdgId())%2 != 0){
	  genP_q1 = genBColl.at(i);
	  foundQ1 = true;
	  if (debug){
	    cout << " Found Q1 ( " << genBColl.at(i).PdgId() << "), mother == " << genBColl.at(mother).PdgId() 
		 << ", pt = " << genBColl.at(i).Pt() << endl;
	  }
	}
	if (!foundQ2 && abs(genBColl.at(i).PdgId())%2 == 0){

	  genP_q2 = genBColl.at(i);
	  foundQ2 = true;
	  if (debug){
	    cout << " Found Q2 ( " << genBColl.at(i).PdgId() << "), mother == " << genBColl.at(mother).PdgId() 
		 << ", pt = " << genBColl.at(i).Pt() << endl;
	  }
	}

      }

      if (dilep>2 || (found_top && found_atop && foundQ1 && foundQ2)) break;
    }
    
    //	if (dilep>2) throw LQError( "Fails DiEl Gen Selection",  LQError::SkipEvent );
    
    if(found_el) FillHist(label,"Lep_flav",1,weight);
    if(found_mu) FillHist(label,"Lep_flav",2,weight);
    if(found_tau) FillHist(label,"Lep_flav",3,weight);
  }
  
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

  if (!(electronTightColl.size()==1 && muonTightColl.size()==0)) throw LQError( "Fails 1 Tight electron",  LQError::SkipEvent );


  FillCutFlow(label,"OneTightLep",weight);
  FillHist(label,"Cuts",6, weight);

  snu::KElectron El = electronTightColl.at(0);

  float eta_el = El.Eta();
    
  float jetPt[4], jetEta[4], jetFlav[4];
  
  float TopElIDIsoSF_up_syst_factor = 1.0;                                                                                    
  float TopElIDIsoSF_down_syst_factor = 1.0;                                                                                  
  float TopElTriggerSF_up_syst_factor = 1.0;                                                                      
  float TopElTriggerSF_down_syst_factor = 1.0;                                                                     

  // behavior of loose muon efficiency...
  // Since we only understand tight leptons( in terms of efficiencies ), we may be should not apply cuts based on loose leptons?

  if (muonVetoColl.size() >0 ) throw LQError( "Fails muonVeto cuts",  LQError::SkipEvent );
  if (electronVetoColl.size() >1)  throw LQError( "Fails electronLoose cuts",  LQError::SkipEvent );

  FillCutFlow(label,"OtherLepVeto",weight);
  FillHist(label,"Cuts",7, weight);
		
  if (!k_isdata){
    // Get the muon trigger scale factor
    float temp_tr = TopElTriggerScaleFactor(El.Pt(), El.Eta(), 0);
    weight *= temp_tr;
    TopElTriggerSF_up_syst_factor = TopElTriggerScaleFactor(El.Pt(), El.Eta(), 1)/temp_tr;
    TopElTriggerSF_down_syst_factor = TopElTriggerScaleFactor(El.Pt(), El.Eta(), -1)/temp_tr;
    // Get the muon ID scale factor

    float temp_id = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), 0);
    weight *= temp_id;
    TopElIDIsoSF_up_syst_factor = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), 1)/temp_id;
    TopElIDIsoSF_down_syst_factor = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), -1)/temp_id;
    // ID / Iso separate
    // Get the muon ISO scale factor		
  }

  FillCutFlow(label,"LepSF",weight);		
  FillHist(label,"Cuts",8, weight);

  int njets = (int)jetColl_lepveto.size();
  int snjets = (int)jetColl_lepveto_soft.size();
		
  FillHist(label,"h_njets",(int)jetColl_lepveto.size(),weight);

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
		
  for(unsigned int ij=0; ij < jetColl_lepveto.size(); ij++){
		
    int this_idx = ij;
		
    TLorentzVector tempjet;
		
    float jet_pt = jetColl_lepveto.at(this_idx).Pt();
    if(method == 1) jet_pt = jetColl_lepveto.at(this_idx).ScaledUpPt();
    if(method == 2) jet_pt = jetColl_lepveto.at(this_idx).ScaledDownPt();
    if(method == 3) jet_pt = jetColl_lepveto.at(this_idx).SmearedUpPt(); 
    if(method == 4) jet_pt = jetColl_lepveto.at(this_idx).SmearedDownPt(); 
		
    tempjet.SetPtEtaPhiE(jet_pt, jetColl_lepveto.at(this_idx).Eta(),jetColl_lepveto.at(this_idx).Phi(),jetColl_lepveto.at(this_idx).E());

			
    double jet_btag = jetColl_lepveto.at(this_idx).CombinedSecVertexBtag();

    jetFlavour = fabs(jetColl_lepveto.at(this_idx).PartonFlavour());
			
    if (jet_btag>0.679){
      nbtags_tot++;
      btag_all[ij] = 1;
    }
    else btag_all[ij] = 0;
			
    jetFlav_all[ij] = jetFlavour;
    jets_all[ij] = tempjet;
    jetPt_all[ij] = jet_pt;
    jetEta_all[ij] = jetColl_lepveto.at(this_idx).Eta();

    if (ij<4){
      jets_f[ij] = tempjet;
      jetErr_f[ij] = jetColl_lepveto.at(this_idx).JECUncertainty();
      jetPt[ij] = tempjet.Pt();
      jetEta[ij] = tempjet.Eta();
      jetFlav[ij] = jetFlavour;

      if (jet_btag>0.679){
	btag_f[ij] = 1;
	nbtags++;
      }
      else btag_f[ij] = 0;
    }


    if (debug)	cout << "csv = " << jet_btag << btag_f[ij]<< endl;
			
  }

    
	

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
    if(method == 1) jet_pt = jetColl_lepveto_soft.at(this_idx).ScaledUpPt(); 
    if(method == 2) jet_pt = jetColl_lepveto_soft.at(this_idx).ScaledDownPt(); 
    if(method == 3) jet_pt = jetColl_lepveto_soft.at(this_idx).SmearedUpPt(); 
    if(method == 4) jet_pt = jetColl_lepveto_soft.at(this_idx).SmearedDownPt(); 
		
    TLorentzVector tempjet(0,0,0,0);
    tempjet.SetPtEtaPhiM(jet_pt,jetColl_lepveto_soft.at(this_idx).Eta(),jetColl_lepveto_soft.at(this_idx).Phi(),0);

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
	

  if (method>0){
    if (METv<20) return 0;
    if(iso_el>=0.1) return 0;
  }

  if (METv>=20){
	  
    FillCutFlow(label,"MET>20",weight);
    FillHist(label,"Cuts",10, weight);
	  
  }
	
  if (nbtags<3)  return 0;//throw LQError( "Fails nbtag>0 cuts",  LQError::SkipEvent );
	

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
  // Inputs to the fitter
  //
	
  TLorentzVector El_vec;
	
  El_vec.SetPtEtaPhiE(El.Pt(),El.Eta(),El.Phi(),El.E());
	
	
  float sigmalep = 0.5*fabs(Evt.PFMET_El_EnUp()-METv) + 0.5*fabs(Evt.PFMET_El_EnDown()-METv);
	
  if (fabs(El.Eta())>1.5) sigmalep =  (sigmalep > 0.015*El_vec.Pt() ) ? sigmalep : 0.015*El_vec.Pt() ;  // Et difference is too small, so assign 1%
  else sigmalep =  (sigmalep > 0.01*El_vec.Pt() ) ? sigmalep : 0.01*El_vec.Pt() ;  // Et difference is too small, so assign 1%
	
         
  double METraw = Evt.PFMETRaw();
  double METrawphi = Evt.PFMETRawphi();
	
                                                    
  TLorentzVector met;
  met.SetPxPyPzE(METx,METy,0,METv); 	   
  TLorentzVector metraw;
  metraw.SetPxPyPzE(METraw*cos(METrawphi),METraw*sin(METrawphi),0,METraw); 	   

  int ntype = 14;	
  bool highpt_fit = false;

  myfit->Fit(El_vec,sigmalep,jets_f,btag_f,sum_jetraw,met,metraw, addjets,ntype, debug, highpt_fit);

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

  float comb_code = 0;

  if (get_best>-1){
    if ( ( genP_q1.DeltaR(fit_q1)<0.3 && genP_q2.DeltaR(fit_q2)<0.3 )|| (genP_q1.DeltaR(fit_q2)<0.3  && genP_q2.DeltaR(fit_q1)<0.3) )
      comb_code = 1;

    if (debug) cout << " Which combinations? " << comb_code << endl;
  }

  TLorentzVector rectt(0,0,0,0);
  rectt = myfit->FittedJets[get_best][0]+myfit->FittedJets[get_best][1]+ myfit->FittedJets[get_best][2]+myfit->FittedJets[get_best][3]+myfit->FittedNeu[get_best]+myfit->FittedLep[get_best];



  /////

  ////////
	
  if(method == 0){
    double vars[49];
    if (!k_isdata){
      vars[0] = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
      vars[1] = pileup_up_sys_factor;	
      vars[2] = pileup_down_sys_factor;
      vars[3] = pt_reweight;
      vars[4] = TopElTriggerScaleFactor(El.Pt(), El.Eta(), 0);
      vars[5] = TopElTriggerSF_up_syst_factor;
      vars[6] = TopElTriggerSF_down_syst_factor;
      vars[7] = TopElIDIsoScaleFactor(El.Pt(), El.Eta(), 0);
      vars[8] = TopElIDIsoSF_up_syst_factor;
      vars[9] = TopElIDIsoSF_down_syst_factor;
      vars[10] = 1.0;
      vars[11] = 1.0;
      vars[12] = 1.0;
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
    vars[23]=iso_el;
    vars[24]=eta_el;
    vars[25]=El.Pt();
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
    vars[46] = (vec_top1+vec_top2).Pt();
    vars[47] = rectt.Pt();
    vars[48] = comb_code;
    FillNtp("tuple_var",vars);
  }


  if(method>0){
    double vars_syst[6];  
    vars_syst[0] = METv;
    vars_syst[1] = nbtags;
    vars_syst[2] = iso_el;
    vars_syst[3] = get_bestHmass;
    vars_syst[4] = weight;
    vars_syst[5] = comb_code;
    
    FillNtp(label+"tuple_var",vars_syst);
  }

	
	
  return 1;
	
	
}// End of exeucte event loop



void CHElJets_v3_sig::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}


void CHElJets_v3_sig::BeginCycle() throw( LQError ){
  
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

CHElJets_v3_sig::~CHElJets_v3_sig() {
  
  Message("In CHElJets_v3_sig Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  if(!k_isdata) delete fBTagSF;
  //	delete minuit;
}
         
void CHElJets_v3_sig::FillCutFlow(TString label,TString cut, float weight){
  
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
     
void CHElJets_v3_sig::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void CHElJets_v3_sig::MakeHistograms(TString label){
  //// Additional plots to make
    
  if(label == ""){
    maphist.clear();
    AnalyzerCore::MakeHistograms();
    MakeNtp(label+"tuple_var","PU:PU_up:PU_down:pt:Trig:Trig_up:Trig_down:Id:Id_up:Id_down:Iso:Iso_up:Iso_down:Bweight:Bweight_up:Bweight_down:Misweight_up:Misweight_down:weight:nVer:MET:nbtags:nbtags_tot:iso_mu:eta_mu:pt_mu:pt_1:eta_1:flav_1:pt_2:eta_2:flav_2:pt_3:eta_3:flav_3:pt_4:eta_4:flav_4:njets:toppt1:toppt2:btag_f1:btag_f2:btag_f3:btag_f4:hm:gen_tt:rec_tt:comb_code");
    
  }
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this CHElJets_v3_sigCore::MakeHistograms() to make new hists for your analysis
   **/
  
  if(label != "") MakeNtp(label+"tuple_var","MET:nbtags:iso_mu:hm:weight:comb_code");


  maphist["Cuts"+label] = new TH1F("Cuts"+label,"Cuts",40,0,40);  
  maphist["Lep_flav"+label] = new TH1F("Lep_flav"+label,"Lep_flav",5,0,5);
  maphist["h_njets"+label] = new TH1F("h_njets"+label,"#Jets with pT>30 GeV",10,0,10);
  
  maphist["gen_top_pt"+label] = new TH1F("gen_top_pt"+label,"gen_top_pt",80,0,400);
  maphist["gen_atop_pt"+label] = new TH1F("gen_atop_pt"+label,"gen_atop_pt",80,0,400);
  maphist["gen_top_pt_reweight"+label] = new TH1F("gen_top_pt_reweight"+label,"gen_top_pt_reweight",80,0,400);
  maphist["gen_atop_pt_reweight"+label] = new TH1F("gen_atop_pt_reweight"+label,"gen_atop_pt_reweight",80,0,400);
  

}


void CHElJets_v3_sig::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



void CHElJets_v3_sig::mysort(std::vector<snu::KJet> jetColl_lepveto, int jet_index[]){

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
