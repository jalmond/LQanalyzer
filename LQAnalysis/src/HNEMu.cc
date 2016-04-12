// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNEMu Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNEMu.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNEMu);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNEMu::HNEMu() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNEMu");

  Message("In HNEMu constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  
  k_met=0., k_emumass=0., k_emujjmass=0., k_l1jjmass=0., k_l2jjmass=0., k_njet=0;
  k_nbjet_m=-1;
  k_emujjmass_lowmass=0., k_l1jjmass_lowmass=0., k_l2jjmass_lowmass=0.;
  k_weight=0.;
  k_l1pt=0., k_l2pt=0., k_j1pt=0., k_jjmass=0., k_jjmass_lowmass=0.;
  k_l1eta=0., k_l2eta=0.;
  
  MakeCleverHistograms(sighist,"TriLepEECR");
  MakeCleverHistograms(sighist,"TriLepMMCR");
  MakeCleverHistograms(sighist,"TriLepCR");
  MakeCleverHistograms(sighist,"OS_2Jet");

  MakeCleverHistograms(sighist,"SS_1Jet");
  MakeCleverHistograms(sighist,"SS_0bjet");
  MakeCleverHistograms(sighist,"SS_bjet");
  MakeCleverHistograms(sighist,"SS_DiJet");
  MakeCleverHistograms(sighist,"SS_DiJet_iso1");
  MakeCleverHistograms(sighist,"SS_DiJet_iso2");
  MakeCleverHistograms(sighist,"SS_DiJet_up");
  MakeCleverHistograms(sighist,"SS_DiJet_down");
  MakeCleverHistograms(sighist,"SS_lowmass");
  MakeCleverHistograms(sighist,"SS_lowmass2");
  MakeCleverHistograms(sighist,"SS_lowmass3");
  MakeCleverHistograms(sighist,"SS_lowmass4");
  MakeCleverHistograms(sighist,"SS_lowmass_40");
  MakeCleverHistograms(sighist,"SS_lowmass_50");
  MakeCleverHistograms(sighist,"SS_lowmass_60");
  MakeCleverHistograms(sighist,"SS_lowmass_70");
  MakeCleverHistograms(sighist,"SS_lowmass_80");
  MakeCleverHistograms(sighist,"SS_lowmass_80_2");
  MakeCleverHistograms(sighist,"SS_lowmassCR");

  MakeCleverHistograms(sighist,"SS_highmass");
  MakeCleverHistograms(sighist,"SS_highmass1");
  MakeCleverHistograms(sighist,"SS_highmass1_90");
  MakeCleverHistograms(sighist,"SS_highmass_90");
  MakeCleverHistograms(sighist,"SS_highmass_90b");
  MakeCleverHistograms(sighist,"SS_highmass_90c");
  MakeCleverHistograms(sighist,"SS_highmass1_100");
  MakeCleverHistograms(sighist,"SS_highmass_100");
  MakeCleverHistograms(sighist,"SS_highmass_100b");
  MakeCleverHistograms(sighist,"SS_highmass_100c");
  MakeCleverHistograms(sighist,"SS_highmass_125");
  MakeCleverHistograms(sighist,"SS_highmass_125b");
  MakeCleverHistograms(sighist,"SS_highmass_125c");
  MakeCleverHistograms(sighist,"SS_highmass_150");
  MakeCleverHistograms(sighist,"SS_highmass_150b");
  MakeCleverHistograms(sighist,"SS_highmass_150c");
  MakeCleverHistograms(sighist,"SS_highmass_175");
  MakeCleverHistograms(sighist,"SS_highmass_200");
  MakeCleverHistograms(sighist,"SS_highmass_250");
  MakeCleverHistograms(sighist,"SS_highmass_300");
  MakeCleverHistograms(sighist,"SS_highmass_exc");
  MakeCleverHistograms(sighist,"SS_highmass_350");
  MakeCleverHistograms(sighist,"SS_highmass_400");
  MakeCleverHistograms(sighist,"SS_highmass_500");


  MakeCleverHistograms(sighist,"SS_highmassCR");


  MakeCleverHistograms(sighist,"SSemu_1Jet");
  MakeCleverHistograms(sighist,"SSemu_DiJet");
  MakeCleverHistograms(sighist,"SSemu_DiJet_up");
  MakeCleverHistograms(sighist,"SSemu_DiJet_down");
  MakeCleverHistograms(sighist,"SSmue_1Jet");
  MakeCleverHistograms(sighist,"SSmue_DiJet");
  MakeCleverHistograms(sighist,"SSmue_DiJet_up");
  MakeCleverHistograms(sighist,"SSmue_DiJet_down");

  MakeCleverHistograms(sighist,"SSmue_2Jet");
  MakeCleverHistograms(sighist,"SSmue_3Jet");
  MakeCleverHistograms(sighist,"SSmue_4Jet");
  MakeCleverHistograms(sighist,"SSmue_BJet");
  MakeCleverHistograms(sighist,"SSmue_0BJet");

  MakeCleverHistograms(sighist,"SSemu_2Jet");
  MakeCleverHistograms(sighist,"SSemu_3Jet");
  MakeCleverHistograms(sighist,"SSemu_4Jet");
  MakeCleverHistograms(sighist,"SSemu_BJet");
  MakeCleverHistograms(sighist,"SSemu_0BJet");

}


void HNEMu::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HNEMu::ExecuteEvents()throw( LQError ){
    


  vector<int> run_num;
  vector<int> ev_num;

  run_num.push_back(191226);
  run_num.push_back(193336);


  ev_num.push_back(1261781261);
  ev_num.push_back(80512298);

  bool check_event=false;
  for(unsigned int iev =0; iev < ev_num.size() ; iev++){
    if(eventbase->GetEvent().RunNumber() == run_num.at(iev)){
      if(eventbase->GetEvent().EventNumber() == ev_num.at(iev))check_event = true;
    }
  }
  //if(!check_event) return;

  // m_logger << INFO << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;



  k_met=0., k_emumass=0., k_emujjmass=0., k_l1jjmass=0., k_l2jjmass=0., k_njet=0;
  k_emujjmass_lowmass=0., k_l1jjmass_lowmass=0., k_l2jjmass_lowmass=0.;

  k_nbjet_m=-1;
  k_weight=0.;
  k_l1pt=0., k_l2pt=0., k_j1pt=0., k_jjmass=0.,k_jjmass_lowmass=0.;
  k_l1eta=0., k_l2eta=0.;
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  /// Correct MC for pileup
  float pileup_up_sys_factor = 1.;
  float pileup_down_sys_factor = 1.;

  float tmp_weight = weight;
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;
    tmp_weight  = tmp_weight * reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;
    
    pileup_up_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
    pileup_down_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), -1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
    
    std::vector<TString> triggerslist2;
    triggerslist2.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    triggerslist2.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

    if(PassTrigger(triggerslist2, prescale)) tmp_weight *= TriggerScaleFactorEMu();
    if(!isData){
      TString fake_loose_label2 = "HNTight_loosereg2";

      std::vector<snu::KElectron> electronAnalysisColltmp = GetElectrons(true,  true, fake_loose_label2);

      std::vector<snu::KMuon> muonstmp = GetMuons("tight");
      
      for(std::vector<snu::KElectron>::iterator it = electronAnalysisColltmp.begin(); it != electronAnalysisColltmp.end(); it++){
	tmp_weight *= ElectronScaleFactor(it->Eta(), it->Pt(), true, 0);
      }

      for(std::vector<snu::KMuon>::iterator it = muonstmp.begin(); it != muonstmp.end(); it++){
	tmp_weight *= MuonScaleFactor(it->Eta(), it->Pt(), 0);
      }

    }
    
  }
  FillEventCutFlow("NoCut","", 1.);
  FillEventCutFlow("NoCut_w","", tmp_weight);
  
  GetIDEfficiency(GetElectrons(true, true, "NoCut"), GetMuons("NoCut"),GetJets("ApplyPileUpID"),  weight);


  if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FillEventCutFlow("EventCut", "",weight);
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  if(isData){
    if(!PassTrigger(triggerslist, prescale)) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }
  else weight*= TriggerScaleFactorEMu();

  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  FillEventCutFlow("VertexCut","", weight);
    
  TString fake_loose_region = "looseregion2";
  TString fake_loose_label = "HNTight_loosereg2";

  //// Get the collection of electrons
  std::vector<snu::KElectron> electronAnalysisColl = GetElectrons(true,  true, fake_loose_label , weight);
  //eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.6,electronAnalysisColl);
  //  std::vector<snu::KElectron> electronLooseColl_iso05,electronLooseColl_iso07;
  //eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.4,electronLooseColl_iso05);
  //eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.6,electronLooseColl_iso07);

  std::vector<snu::KMuon> muons = GetMuons("tight");
  
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *= ElectronScaleFactor(it->Eta(), it->Pt(), true, 0);
    }
    
    for(std::vector<snu::KMuon>::iterator it = muons.begin(); it != muons.end(); it++){
      weight *= MuonScaleFactor(it->Eta(), it->Pt(), 0);
    }
    
  }
  
  

  vector<snu::KTruth> truth =  eventbase->GetTruth();
  
  std::vector<snu::KElectron> electronVetoColl       = GetElectrons(false, false, "veto"); 
  std::vector<snu::KElectron> electronLooseColl      = GetElectrons(false, false, "loose"); 

  std::vector<snu::KMuon> muonVetoColl  = GetMuons("veto");

  FillHist("Nveto_electrons", electronVetoColl.size() ,1., 0. , 4.,4);
  FillHist("Nveto_muons", muonVetoColl.size() ,1., 0. , 4., 4);
  FillHist("Nveto_leptons", electronVetoColl.size() + muonVetoColl.size()  ,1., 0. , 4., 4);


  //m_logger << INFO << "Number of veto el = " << electronVetoColl.size() << LQLogger::endmsg;
  //m_logger << INFO << "Number of veto muons = " << muonVetoColl.size() << LQLogger::endmsg;

  /// JETS

  std::vector<snu::KJet> jetColl             = GetJets("NoLeptonVeto");
  std::vector<snu::KJet> jetColl_lepveto     = GetJets("ApplyLeptonVeto");
  std::vector<snu::KJet> jetColl_lepveto_mva = GetJets("ApplyPileUpID");

  //  m_logger << INFO << "Number of jets1  = " << jetColl.size() << LQLogger::endmsg;
  //m_logger << INFO << "Number of jets2  = " << jetColl_lepveto.size() << LQLogger::endmsg;

  //RunMCCLosureTestEMU("loosereg2", jetColl_lepveto_mva,"",weight);


  ///// count number of bjets in the event (using cvs medium WP)
  int nbjet_m=0;

  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet_m++;
  }
  int nbjet = nbjet_m;
  if( nbjet == 0 ){
    MakeEMUTriLeptonPlots(GetElectrons(true,true, "HNTight"), muons, jetColl_lepveto_mva, "",  weight);
  }

 
  float weight_up= weight;
  float weight_iso1= weight;
  float weight_iso2= weight;
  float weight_down= weight;
  TString reg = fake_loose_region;
  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt&&isData){
    
    weight      *= Get_DataDrivenWeight_EM(muons, electronAnalysisColl,   eventbase->GetEvent().JetRho());
    weight_up      *= Get_DataDrivenWeight_EM(muons, electronAnalysisColl,   eventbase->GetEvent().JetRho(),1);
    weight_iso1      *= Get_DataDrivenWeight_EM(muons, electronAnalysisColl,   eventbase->GetEvent().JetRho(),3);
    weight_iso2      *= Get_DataDrivenWeight_EM(muons, electronAnalysisColl,   eventbase->GetEvent().JetRho(),4);
    weight_down      *= Get_DataDrivenWeight_EM(muons, electronAnalysisColl,   eventbase->GetEvent().JetRho(),-1);
  }
  
  
  if(!(electronAnalysisColl.size() == 1 && muons.size() == 1)) throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  //m_logger << INFO << "Passes nlep req."<< LQLogger::endmsg;  
  //  cout << "weight = " << weight << " weight_iso1 = " << weight_iso1 << " weight_iso2= " << weight_iso2 << endl;
  if(! ((electronAnalysisColl.at(0).Pt() > 20. &&  muons.at(0).Pt() > 15.) || (electronAnalysisColl.at(0).Pt() > 15. && muons.at(0).Pt() > 20.))) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  snu::KParticle emu =  electronAnalysisColl.at(0) + muons.at(0);
  
  if(emu.M()  < 10.) throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  if ((electronVetoColl.size() + muonVetoColl.size()) ==2){
    if(electronAnalysisColl.at(0).Charge() != muons.at(0).Charge()){
      if(jetColl_lepveto_mva.size() > 1){
	FillCLHist(sighist, "OS_2Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
  }
  

  weight              *= WeightCFEvent(electronAnalysisColl,muons,  k_running_chargeflip);
  weight_up       *= WeightCFEvent(electronAnalysisColl,muons,  k_running_chargeflip);
  weight_iso1       *= WeightCFEvent(electronAnalysisColl,muons,  k_running_chargeflip);
  weight_iso2       *= WeightCFEvent(electronAnalysisColl,muons,  k_running_chargeflip);
  weight_down       *= WeightCFEvent(electronAnalysisColl,muons,  k_running_chargeflip);
  if(WeightCFEvent(electronAnalysisColl, muons,  k_running_chargeflip) == 0.) throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  ///// NOW OS event is weighted for CF sample
  //m_logger << INFO << "Passes SS req."<< LQLogger::endmsg;  
  
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) throw LQError( "Fails basic cuts",  LQError::SkipEvent );  
    

  //  m_logger << INFO << "Passes n veto lep req."<< LQLogger::endmsg;  

  if(electronAnalysisColl.at(0).Pt() > 20. || muons.at(0).Pt() > 20 ){
    
    //m_logger << INFO << "Passes pt req"<< LQLogger::endmsg;  
    //m_logger << INFO << "Number of jets  = " << jetColl_lepveto_mva.size() << LQLogger::endmsg;
    

    if(jetColl_lepveto_mva.size() > 1){
      
      if(nbjet_m == 0){
	//Fill opt variables
	k_nbjet_m = nbjet_m;
	if(electronAnalysisColl.at(0).Pt() > muons.at(0).Pt() ){
	  k_l1pt= electronAnalysisColl.at(0).Pt();
	  k_l2pt= muons.at(0).Pt();
	  k_l1eta= electronAnalysisColl.at(0).Eta();
	  k_l2eta= muons.at(0).Eta();
	  
	}
	else{
	  k_l2pt= electronAnalysisColl.at(0).Pt();
	  k_l1pt= muons.at(0).Pt();
	  k_l2eta= electronAnalysisColl.at(0).Eta();
	  k_l1eta= muons.at(0).Eta();
	  
	}
	k_emumass = emu.M();
	k_j1pt = jetColl_lepveto_mva.at(0).Pt();
	
	float wmassjj= 100000.;
	int indexj1=0;
	int indexj2=0;
	for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
	  for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	    snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2) ;
	    if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	      wmassjj = fabs(jjtmp.M() - 80.4);
	      indexj1=ij;
	      indexj2=ij2;
	    }
	  }
	}
	snu::KParticle jj = jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2);
	k_jjmass = jj.M();
	
	float wmassjj_lowmass= 100000.;
	int indexj1_lm=0;
	int indexj2_lm=0;
	for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
	  for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	    snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2) +  electronAnalysisColl.at(0) + muons.at(0) ;
	    if(fabs(jjtmp.M() - 80.4) < wmassjj_lowmass) {
	      wmassjj_lowmass = fabs(jjtmp.M() - 80.4);
	      indexj1_lm=ij;
	      indexj2_lm=ij2;
	    }
	  }
	}
	snu::KParticle jj_lm = jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm);
	k_jjmass_lowmass = jj_lm.M();

	
	snu::KParticle emujj = electronAnalysisColl.at(0) + muons.at(0)+ jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
	snu::KParticle emujj_lm = electronAnalysisColl.at(0) + muons.at(0)+ jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm) ;
	
	

	snu::KParticle l1jj;
	snu::KParticle l2jj;
	snu::KParticle l1jj_lm;
	snu::KParticle l2jj_lm;
	

	if(electronAnalysisColl.at(0).Pt() > muons.at(0).Pt() ){
	  l1jj = electronAnalysisColl.at(0) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
	  l2jj = electronAnalysisColl.at(0) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
	  l1jj_lm = electronAnalysisColl.at(0) + jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm) ;
	  l2jj_lm = electronAnalysisColl.at(0) + jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm) ;
	}
	else{
	  l1jj = muons.at(0) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
	  l2jj = muons.at(0) + jetColl_lepveto_mva.at(indexj1) + jetColl_lepveto_mva.at(indexj2) ;
	  l1jj_lm = muons.at(0) + jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm) ;
	  l2jj_lm = muons.at(0) + jetColl_lepveto_mva.at(indexj1_lm) + jetColl_lepveto_mva.at(indexj2_lm) ;
	  
	}
	k_emujjmass = emujj.M();
	k_emujjmass_lowmass = emujj_lm.M();
	k_l1jjmass = l1jj.M();
	k_l2jjmass = l2jj.M();
	k_l1jjmass_lowmass = l1jj_lm.M();
	k_l2jjmass_lowmass = l2jj_lm.M();
	
	k_njet=jetColl_lepveto_mva.size();
	

	k_met = eventbase->GetEvent().PFMET();
	k_weight = weight;
      }
    }
    //else  throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  
    if(jetColl_lepveto_mva.size() == 1&& emu.M() > 100.){
      if(muons.at(0).Pt() > 20. && electronAnalysisColl.at(0).Pt() > 20){
	FillCLHist(sighist, "SS_1Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    if(jetColl_lepveto_mva.size() > 1){

      if(IsTight(muons.at(0)) && IsTight(electronAnalysisColl.at(0), eventbase->GetEvent().JetRho())) 
	FillHist("TT_presel",1,weight, 0., 2., 2.);
      else if(!IsTight(muons.at(0)) && !IsTight(electronAnalysisColl.at(0), eventbase->GetEvent().JetRho()))
	FillHist("LL_presel",1,weight,0., 2.,2.);
      else FillHist("TL_presel",1,weight,0., 2.,2.);


      FillCLHist(sighist, "SS_DiJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      FillCLHist(sighist, "SS_DiJet_iso1", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_iso1);
      FillCLHist(sighist, "SS_DiJet_iso2", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_iso2);
      FillCLHist(sighist, "SS_DiJet_up", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_up);
      FillCLHist(sighist, "SS_DiJet_down", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_down);
      if(nbjet==0){
	FillCLHist(sighist, "SS_0bjet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      else{
	FillCLHist(sighist, "SS_bjet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
  }
  //else throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  

  //m_logger << INFO << "Number of jets  = " << jetColl_lepveto_mva.size() << LQLogger::endmsg;

  if(true){
    /// Low Mass
    int index_j1(0),index_j2(0);
    float wmassjj=1000000.;
    if(jetColl_lepveto_mva.size() > 1){
      
      for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
	for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	  snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2)   + electronAnalysisColl.at(0) + muons.at(0);
	  if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	    wmassjj = fabs(jjtmp.M() - 80.4);
	    index_j1=ij;
	    index_j2=ij2;
	  }
	}
      }
    } 
   
    //m_logger << INFO << "Number of jets  = " << jetColl_lepveto_mva.size() << LQLogger::endmsg;
 
    if(jetColl_lepveto_mva.size() > 1){
      snu::KParticle emujj = jetColl_lepveto_mva.at(index_j1) + jetColl_lepveto_mva.at(index_j2) + electronAnalysisColl.at(0) + muons.at(0) ;
      snu::KParticle jj = jetColl_lepveto_mva.at(index_j1) + jetColl_lepveto_mva.at(index_j2);
      snu::KParticle l2 = electronAnalysisColl.at(0);
      if(electronAnalysisColl.at(0).Pt() > muons.at(0).Pt()) l2 = muons.at(0);
      //m_logger << INFO << "Passes njet req."<< LQLogger::endmsg;
      
      ///m_logger << INFO << "emujj = " << emujj.M()  << " and emu = " << emu.M()<< LQLogger::endmsg;
      if(emujj.M() < 200. && emujj.M() > 80. && emu.M() > 10.){
	//m_logger << INFO << "Passes lowmass req."<< LQLogger::endmsg;  
	
	if(jj.M() < 120.){
	  //m_logger << INFO << "Passes lowmass2 req."<< LQLogger::endmsg;  
	  if(eventbase->GetEvent().PFMET() < 30. && nbjet ==0){

	    FillCLHist(sighist, "SS_lowmass", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(emujj.M() < 160. && emujj.M() > 80.)
              FillCLHist(sighist, "SS_lowmass2", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(emujj.M() < 170. && emujj.M() > 80.)
              FillCLHist(sighist, "SS_lowmass3", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(emujj.M() < 200. && emujj.M() > 80.)
              FillCLHist(sighist, "SS_lowmass4", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	    
	    if(emujj.M() < 150. && emujj.M() > 80.){
	      //m_logger << INFO << "Passes lowmass 4"<< LQLogger::endmsg;  
	      //m_logger << INFO << "Passes 40: RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;

	      FillCLHist(sighist, "SS_lowmass_40", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	      FillCLHist(sighist, "SS_lowmass_50", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	      FillCLHist(sighist, "SS_lowmass_60", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	      FillCLHist(sighist, "SS_lowmass_70", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	    }

	    if(emujj.M() < 200. && emujj.M() > 90.){
	      if((electronAnalysisColl.at(0).Pt() > 25. &&  muons.at(0).Pt() > 20.) || (electronAnalysisColl.at(0).Pt() > 20. && muons.at(0).Pt() > 25.)){
		FillCLHist(sighist, "SS_lowmass_80", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		if(emujj.M() < 180.)
		  FillCLHist(sighist, "SS_lowmass_80_2", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);

	      }
	    }
	  }
	  if((eventbase->GetEvent().PFMET() > 50 && nbjet == 0 ) || (eventbase->GetEvent().PFMET() < 30. && nbjet !=0)){
	    FillCLHist(sighist, "SS_lowmassCR", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	  }
	}
      }
    }
  }
  
  
  if(true){
    /// High Mass
      int index_j1(0),index_j2(0);
      if(jetColl_lepveto_mva.size() > 1){
	
	float wmassjj=1000000.;
	for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
	  for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	    snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2);
	    if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	      wmassjj = fabs(jjtmp.M() - 80.4);
	      index_j1=ij;
	      index_j2=ij2;
	    }
	  }
	}
      }
      if(jetColl_lepveto_mva.size() > 1){
	snu::KParticle l2 = electronAnalysisColl.at(0);
	if(electronAnalysisColl.at(0).Pt() > muons.at(0).Pt()) l2 = muons.at(0);

	snu::KParticle emujj = jetColl_lepveto_mva.at(index_j1) + jetColl_lepveto_mva.at(index_j2) + emu ;
	snu::KParticle l2jj = jetColl_lepveto_mva.at(index_j1) + jetColl_lepveto_mva.at(index_j2) + l2 ;
	snu::KParticle jj = jetColl_lepveto_mva.at(index_j1) + jetColl_lepveto_mva.at(index_j2)  ;
	
	float l2jjm = l2jj.M();

	if(emujj.M() > 80.){
	  if ((jj.M() < 110.) && (jj.M() > 50)) {
	    if(jetColl_lepveto_mva.at(0).Pt() > 30.){
	      if(emu.M() > 15){
		if(eventbase->GetEvent().PFMET() < 35. && nbjet ==0){
		  FillCLHist(sighist, "SS_highmass1", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		}
		if((eventbase->GetEvent().PFMET() > 50 && nbjet == 0 ) || (eventbase->GetEvent().PFMET() < 35. && nbjet !=0)){
                  FillCLHist(sighist, "SS_highmassCR", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
                }
		if(eventbase->GetEvent().PFMET() < 35. && nbjet ==0){
		  
                  if(emujj.M() > 120. && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 15)||  (electronAnalysisColl.at(0).Pt()> 15. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
                    FillCLHist(sighist, "SS_highmass1_90", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
                    //l2jj 130
                  }
		  if(emujj.M() > 130.  && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 20)||  (electronAnalysisColl.at(0).Pt()> 20. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
                    FillCLHist(sighist, "SS_highmass1_100", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
                    //l2jj 140
                  }
		}
	      }
	      
	      if(emu.M() > 45.){
		if(eventbase->GetEvent().PFMET() < 35. && nbjet ==0){
		    FillCLHist(sighist, "SS_highmass", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);


		  
		  if(emujj.M() > 120. && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 15)||  (electronAnalysisColl.at(0).Pt()> 15. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
		    FillCLHist(sighist, "SS_highmass_90b", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		    //l2jj 130
		  }
		  
		  if(l2jjm < 130.&& emujj.M() > 120. && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 15)||  (electronAnalysisColl.at(0).Pt()> 15. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
                    FillCLHist(sighist, "SS_highmass_90", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
                    //l2jj 130
                  }
		  
		  if(emujj.M() > 130.  && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 20)||  (electronAnalysisColl.at(0).Pt()> 20. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
		    FillCLHist(sighist, "SS_highmass_100b", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		    //l2jj 140
		  }		
		  
		  if(l2jjm < 135.&& emujj.M() > 130. && ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 20)||  (electronAnalysisColl.at(0).Pt()> 20. && muons.at(0).Pt() > 40)) && jetColl_lepveto_mva.at(0).Pt() > 30.){
                    FillCLHist(sighist, "SS_highmass_100", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
                    //l2jj 135
                  }

		  
		  if(emujj.M() > 140. &&  ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 30)||  (electronAnalysisColl.at(0).Pt()> 30. && muons.at(0).Pt() > 40)))
		    FillCLHist(sighist, "SS_highmass_125b", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		  //l2jj 160
		  
		  if(l2jjm < 160. && emujj.M() > 140. &&  ((electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 30)||  (electronAnalysisColl.at(0).Pt()> 30. && muons.at(0).Pt() > 40)))
                    FillCLHist(sighist, "SS_highmass_125", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);


		  if(emujj.M() > 150.  && ((electronAnalysisColl.at(0).Pt()> 45. && muons.at(0).Pt() > 30)||  (electronAnalysisColl.at(0).Pt()> 30. && muons.at(0).Pt() > 45)))
		    FillCLHist(sighist, "SS_highmass_150b", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		    //180

		  if(l2jjm < 180. && emujj.M() > 150.   && ((electronAnalysisColl.at(0).Pt()> 45. && muons.at(0).Pt() > 30)||  (electronAnalysisColl.at(0).Pt()> 30. && muons.at(0).Pt() > 45)))
                    FillCLHist(sighist, "SS_highmass_150", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);


		  if(l2jjm < 230. &&emujj.M() > 170. &&  ((electronAnalysisColl.at(0).Pt()> 60. && muons.at(0).Pt() > 35)||  (electronAnalysisColl.at(0).Pt()> 35. && muons.at(0).Pt() > 60)) && jetColl_lepveto_mva.at(0).Pt() > 35.)
                    FillCLHist(sighist, "SS_highmass_175", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);

		  if(l2jjm < 240. &&emujj.M() > 200. &&  ((electronAnalysisColl.at(0).Pt()> 75. && muons.at(0).Pt() > 35)||  (electronAnalysisColl.at(0).Pt()> 35. && muons.at(0).Pt() > 75))&& jetColl_lepveto_mva.at(0).Pt() > 35.)
		    FillCLHist(sighist, "SS_highmass_200", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);

		  if(l2jjm < 330. &&emujj.M() > 260. && ((electronAnalysisColl.at(0).Pt()> 80. && muons.at(0).Pt() > 40)||  (electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 80))&& jetColl_lepveto_mva.at(0).Pt() > 35.)
		    FillCLHist(sighist, "SS_highmass_250", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);


		  
                  if(emujj.M() > 440.)
                    FillCLHist(sighist, "SS_highmass_exc", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);

		  if(l2jjm < 490. &&emujj.M() > 310. && ((electronAnalysisColl.at(0).Pt()> 110. && muons.at(0).Pt() > 40)||  (electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 110))&&  jetColl_lepveto_mva.at(0).Pt() > 35.)
		    FillCLHist(sighist, "SS_highmass_300", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		  if(l2jjm < 590. &&emujj.M() > 370. && ((electronAnalysisColl.at(0).Pt()> 115. && muons.at(0).Pt() > 40)||  (electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 115))&&   jetColl_lepveto_mva.at(0).Pt() > 35.)
                    FillCLHist(sighist, "SS_highmass_350", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		  if(l2jjm < 800. &&emujj.M() > 380. && ((electronAnalysisColl.at(0).Pt()> 120. && muons.at(0).Pt() > 40)||  (electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 120))&&  jetColl_lepveto_mva.at(0).Pt() > 35.)
		    FillCLHist(sighist, "SS_highmass_400", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		  if(l2jjm < 1000. &&emujj.M() > 380. && ((electronAnalysisColl.at(0).Pt()> 120. && muons.at(0).Pt() > 40)||  (electronAnalysisColl.at(0).Pt()> 40. && muons.at(0).Pt() > 120))&&   jetColl_lepveto_mva.at(0).Pt() >35.)
		    FillCLHist(sighist, "SS_highmass_500", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
		}
		
	      }
	    }
	  }
	}
      }
  }


  if(electronAnalysisColl.at(0).Pt() > 20. && muons.at(0).Pt() > 15){
    if(electronAnalysisColl.at(0).Pt() > muons.at(0).Pt() ){
      if(jetColl_lepveto_mva.size() == 1&& emu.M() > 100.)  
	FillCLHist(sighist, "SSemu_1Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() > 1){
	FillCLHist(sighist, "SSemu_DiJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	FillCLHist(sighist, "SSemu_DiJet_up", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_up);
	FillCLHist(sighist, "SSemu_DiJet_down", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_down);
      }
      if(jetColl_lepveto_mva.size() == 2)
	FillCLHist(sighist, "SSemu_2Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() == 3)
	FillCLHist(sighist, "SSemu_3Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() > 3)
	FillCLHist(sighist, "SSemu_4Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      
      if(jetColl_lepveto_mva.size() > 1){
	if(nbjet == 0)
	  FillCLHist(sighist, "SSemu_0BJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	else
	  FillCLHist(sighist, "SSemu_BJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      
    }
  }
  
  if(electronAnalysisColl.at(0).Pt() > 15. && muons.at(0).Pt() > 20.){
    if(electronAnalysisColl.at(0).Pt() <  muons.at(0).Pt() ){
      if(jetColl_lepveto_mva.size() == 1&& emu.M() > 100.)
	FillCLHist(sighist, "SSmue_1Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() > 1){
	FillCLHist(sighist, "SSmue_DiJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	FillCLHist(sighist, "SSmue_DiJet_up", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_up);
	FillCLHist(sighist, "SSmue_DiJet_down", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight_down);
      }
      
      if(jetColl_lepveto_mva.size() == 2)
	FillCLHist(sighist, "SSmue_2Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() == 3)
	FillCLHist(sighist, "SSmue_3Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() > 3)
	FillCLHist(sighist, "SSmue_4Jet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      
      if(jetColl_lepveto_mva.size() > 1){
	if(nbjet == 0)
	  FillCLHist(sighist, "SSmue_0BJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
	else
	  FillCLHist(sighist, "SSmue_BJet", eventbase->GetEvent(), muons ,electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
  }
    
  }// End of exeucte event loop



float HNEMu::WeightCFEvent(std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons, bool runchargeflip, bool useoldrates){

  if(electrons.size()!=1) return 0.;
  if(muons.size()!=1) return 0.;
  
  if(runchargeflip) {
    if(electrons.at(0).Charge() != muons.at(0).Charge()) {
      float cf1=  CFRate(electrons.at(0), useoldrates);

      return  cf1;
    }// OS requirement
    else return 0.;
  }// cf requirement
  else {
    if(electrons.at(0).Charge() != muons.at(0).Charge()) return 0.;
  }
  
  return 1.;
  
}


void HNEMu::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void HNEMu::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  
  DeclareVariable(k_met, "met", "MyTree");
  DeclareVariable(k_emumass, "emu_mass", "MyTree");
  DeclareVariable(k_emujjmass, "emujj_mass", "MyTree");
  DeclareVariable(k_l1jjmass, "l1jj_mass", "MyTree");
  DeclareVariable(k_l2jjmass, "l2jj_mass", "MyTree");
  DeclareVariable(k_emujjmass_lowmass, "emujj_mass_lowmass", "MyTree");
  DeclareVariable(k_l1jjmass_lowmass, "l1jj_mass_lowmass", "MyTree");
  DeclareVariable(k_l2jjmass_lowmass, "l2jj_mass_lowmass", "MyTree");
  DeclareVariable(k_njet, "njet", "MyTree");
  DeclareVariable(k_nbjet_m , "nbjet_m",  "MyTree");
  DeclareVariable(k_jjmass, "jj_mass", "MyTree");
  DeclareVariable(k_jjmass_lowmass, "jj_mass_lowmass", "MyTree");
  DeclareVariable(k_l1pt, "l1_pt", "MyTree");
  DeclareVariable(k_l1eta, "l1_eta", "MyTree");
  DeclareVariable(k_l2eta, "l2_eta", "MyTree");
  DeclareVariable(k_l2pt, "l2_pt", "MyTree");

  DeclareVariable(k_j1pt, "jet1_pt", "MyTree");
  DeclareVariable(k_weight, "weight", "MyTree");

  return;
  
}

HNEMu::~HNEMu() {
  
  Message("In HNEMu Destructor" , INFO);
  if(!k_isdata)delete reweightPU;

 }
     

void HNEMu::FillEventCutFlow(TString cut, TString label , float weight){

  if(GetHist(label + "_eventcutflow")) {
    GetHist(label + "_eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms(label + "_eventcutflow",19,0.,19.);

    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(2,"NoCut_w");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(3,"eventcut");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(4,"TriggerCut");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(5,"VertexCut");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(6,"DiEl");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(7,"eedR");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(8,"SSDiEl");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(9,"SS_lepveto");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(10,"DiJet");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(11,"Presel");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(12,"Presel_noZ");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(13,"Presel_nobjet");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(14,"lowmass");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(15,"lowmassCR");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(16,"mediummass");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(17,"mediummassCR");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(18,"highmass");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(19,"highmassCR");
  }
  
}

     
void HNEMu::FillCutFlow(TString cut, float weight){
  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",16,0.,16.);
    
    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"SS_NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"SS_Tight");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"SS_Tight_convveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"SS_Tight_d0veto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"SS_Tight_reliso");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"SS_Medium_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"SS_Tight_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"SS_Tight_noclosejet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"SS_anal_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"Signal_anal");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"Signal_Tightlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"Signal_Mediumlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(13,"Signal_drcut1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(14,"Signal_drcut2");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(15,"Signal_anal_dr1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(16,"Signal_anal_dr2");
  }
}
     
     
void HNEMu::FillIsoCutFlow(TString cut, float weight){
       
  
  if(GetHist("isocutflow")) {
    GetHist("isocutflow")->Fill(cut,weight);
    
  }
  else{
    AnalyzerCore::MakeHistograms("isocutflow",36,0.,36.);
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(1,"iso_d0_03_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(2,"iso_d0_03_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(3,"iso_d0_03_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(4,"iso_d0_03_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(5,"iso_d0_03_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(6,"iso_d0_03_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(7,"iso_d0_03_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(8,"iso_d0_03_iso3_075");
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(10,"iso_d0_02_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(11,"iso_d0_02_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(12,"iso_d0_02_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(13,"iso_d0_02_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(14,"iso_d0_02_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(15,"iso_d0_02_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(16,"iso_d0_02_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(17,"iso_d0_02_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(19,"iso_d0_01_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(20,"iso_d0_01_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(21,"iso_d0_01_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(22,"iso_d0_01_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(23,"iso_d0_01_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(24,"iso_d0_01_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(25,"iso_d0_01_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(26,"iso_d0_01_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(28,"iso_d0_005_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(29,"iso_d0_005_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(30,"iso_d0_005_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(31,"iso_d0_005_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(32,"iso_d0_005_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(33,"iso_d0_005_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(34,"iso_d0_005_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(35,"iso_d0_005_iso3_075");

    
    
  }
}


void HNEMu::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNEMu::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNEMuCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNEMu::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}




//  LocalWords:  masscuts jetResdown
