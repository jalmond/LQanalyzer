// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNDiElectron);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiElectron::HNDiElectron() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiElectron");

  Message("In HNDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  
  
  // Signal plots
  MakeCleverHistograms(sighist,"NoCut");
  MakeCleverHistograms(sighist,"NoCutPtEta");
  MakeCleverHistograms(sighist,"Fake");
    
  MakeCleverHistograms(sighist,"OSee");
  MakeCleverHistograms(sighist,"OSee_nojetpumva");
  MakeCleverHistograms(sighist,"Top");
  MakeCleverHistograms(sighist,"SSee_gt1jet_noZ");
  MakeCleverHistograms(sighist,"SSee_gt1jet_Z");
  MakeCleverHistograms(sighist,"SSee_gt1jet_lowZ");
  MakeCleverHistograms(sighist,"SSee_gt1jet_lowZ_met");
  MakeCleverHistograms(sighist,"SSee_gt1jet_lowZ_met2");
  MakeCleverHistograms(sighist,"SSee_gt1jet_lowZhighW");
  MakeCleverHistograms(sighist,"SSee_gt1jet_2jet");
  MakeCleverHistograms(sighist,"SSee_gt1jet_3jet");
  MakeCleverHistograms(sighist,"SSee_gt1jet_4jet");
  MakeCleverHistograms(sighist,"SSee_gt1jet_5jet");
  
  MakeCleverHistograms(sighist,"TriElCR_dijet_highmet_osZW_mva");
  MakeCleverHistograms(sighist,"TriElCR_jet_osZW_mva");
  MakeCleverHistograms(sighist,"TriElCR_mva");
  MakeCleverHistograms(sighist,"TriElCR1Jet_mva");
  MakeCleverHistograms(sighist,"TriElCR_dijet_highmet_mva");
  MakeCleverHistograms(sighist,"ZZ_mva");

  MakeCleverHistograms(sighist,"SSee_1jet_m1_40");
  MakeCleverHistograms(sighist,"SSee_1jet_m4_40");

  MakeCleverHistograms(sighist,"SSee_1jet_m1_30");
  MakeCleverHistograms(sighist,"SSee_1jet_m4_30");

  MakeCleverHistograms(sighist,"BJetCR_m1_40");
  MakeCleverHistograms(sighist,"BJetCR_m4_40");

  MakeCleverHistograms(sighist,"BJetCR_m1_30");
  MakeCleverHistograms(sighist,"BJetCR_m4_30");

  MakeCleverHistograms(sighist,"HighMETCR_m1_40");
  MakeCleverHistograms(sighist,"HighMETCR_m4_40");

  MakeCleverHistograms(sighist,"HighMETCR_m1_30");
  MakeCleverHistograms(sighist,"HighMETCR_m4_30");

  MakeCleverHistograms(sighist,"SSee_DiJet");

  MakeCleverHistograms(sighist,"Preselection_m1_40");
  MakeCleverHistograms(sighist,"Preselection_m4_40");

  MakeCleverHistograms(sighist,"Preselection_m1_30");
  MakeCleverHistograms(sighist,"Preselection_m4_30");
 
  MakeCleverHistograms(sighist,"Preselection_up");
  MakeCleverHistograms(sighist,"Preselection_down");
  
  MakeCleverHistograms(sighist,"LowMassRegion");
  MakeCleverHistograms(sighist,"MediumMassRegion");
  MakeCleverHistograms(sighist,"HighMassRegion");

  MakeCleverHistograms(sighist,"40MassRegion");
  MakeCleverHistograms(sighist,"50MassRegion");
  MakeCleverHistograms(sighist,"60MassRegion");
  MakeCleverHistograms(sighist,"70MassRegion");
  MakeCleverHistograms(sighist,"80MassRegion");
  MakeCleverHistograms(sighist,"90MassRegion");
  MakeCleverHistograms(sighist,"100MassRegion");
  MakeCleverHistograms(sighist,"125MassRegion");
  MakeCleverHistograms(sighist,"150MassRegion");
  MakeCleverHistograms(sighist,"175MassRegion");
  MakeCleverHistograms(sighist,"200MassRegion");
  MakeCleverHistograms(sighist,"225MassRegion");
  MakeCleverHistograms(sighist,"250MassRegion");
  MakeCleverHistograms(sighist,"275MassRegion");
  MakeCleverHistograms(sighist,"300MassRegion");
  MakeCleverHistograms(sighist,"325MassRegion");
  MakeCleverHistograms(sighist,"350MassRegion");
  MakeCleverHistograms(sighist,"375MassRegion");
  MakeCleverHistograms(sighist,"400MassRegion");
  MakeCleverHistograms(sighist,"500MassRegion");
  MakeCleverHistograms(sighist,"600MassRegion");
  MakeCleverHistograms(sighist,"700MassRegion");


  MakeCleverHistograms(sighist,"HighMETBJetCR");

  MakeCleverHistograms(sighist,"HighMETBJetCR_LowMassRegion");
  MakeCleverHistograms(sighist,"HighMETBJetCR_MediumMassRegion");
  MakeCleverHistograms(sighist,"HighMETBJetCR_HighMassRegion");
  

  MakeCleverHistograms(sighist,"HighMETBJetCR_LowMassRegion_m1_40");
  MakeCleverHistograms(sighist,"HighMETBJetCR_LowMassRegion_m4_40");

  MakeCleverHistograms(sighist,"HighMETBJetCR_MediumMassRegion_m1_40");
  MakeCleverHistograms(sighist,"HighMETBJetCR_MediumMassRegion_m4_40");

}


void HNDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){
  
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  Double_t weight_err = 1.;
  
  FillEventCutFlow("NoCut_w",weight);
  FillEventCutFlow("NoCut",1.);
  
  if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FillEventCutFlow("EventCut", weight);
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  FillEventCutFlow("VertexCut", weight);
  
  /// Correct MC for pileup     
  float pileup_up_sys_factor = 1.;
  float pileup_down_sys_factor = 1.;
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;
    pileup_up_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
    pileup_down_sys_factor = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), -1) / reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0);
  }
  

  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  std::vector<snu::KElectron> test_elcoll                   = GetElectrons(false, false, "HNTight_loosereg2");
  TString fake_loose_region = "";
  TString fake_loose_label = "";
  if(Zcandidate(test_elcoll, 20., false)) {
    fake_loose_region = "looseregion1";
    fake_loose_label = "HNTight";
  }
  else  {
    fake_loose_region = "looseregion2";
    fake_loose_label = "HNTight_loosereg2";
  }

  //// Get the collection of electrons
  std::vector<snu::KElectron> electronAnalysisColl                   = GetElectrons(true,  false, fake_loose_label , weight);
  std::vector<snu::KElectron> electronAnalysisColl_withfakes         = GetElectrons(false, true, fake_loose_label);
  
  vector<snu::KTruth> truth =  eventbase->GetTruth();
  

  std::vector<snu::KElectron> electronVetoColl       = GetElectrons(false, false, "veto"); 
  std::vector<snu::KElectron> electronLooseColl      = GetElectrons(false, false, "loose"); 
  std::vector<snu::KElectron> electronNoCutColl      = GetElectrons(true, true, "NoCut");
  std::vector<snu::KElectron> electronPtEtaNoCutColl = GetElectrons(true, true, "NoCutPtEta");

  m_logger << DEBUG << "Filled Electrons "<< LQLogger::endmsg;
  
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl  = GetMuons("veto");
  std::vector<snu::KMuon> muonNoCutColl = GetMuons("NoCut");

  /// JETS
  std::vector<snu::KJet> jetColl             = GetJets("NoLeptonVeto");
  std::vector<snu::KJet> jetColl_lepveto     = GetJets("ApplyLeptonVeto");
  std::vector<snu::KJet> jetColl_lepveto_mva = GetJets("ApplyPileUpID");

  /// Set weight for DD matrix method NP bkg

  m_logger << DEBUG << "Filled Jets "<< LQLogger::endmsg;


  /// Plot leptons not matched to W/Z
  PlotFakeLeptons(jetColl_lepveto_mva,weight);

  
  m_logger << DEBUG << "Made some Fake Plots "<< LQLogger::endmsg;

  ///// count number of bjets in the event (using cvs medium WP)
  int nbjet_l=0;
  int nbjet_m=0;
  int nbjet_t=0;
  
  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.898) nbjet_t++;
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet_m++;
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.244) nbjet_l++;
  }
  int nbjet = nbjet_m;
  
  /// Check the jets close to the electrons we will use
  CheckJetsCloseToLeptons(electronVetoColl, jetColl, "vetoel");
  CheckJetsCloseToLeptons(electronLooseColl, jetColl, "looseel");
  if(jetColl_lepveto_mva.size()==2)CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel");


  
  //// CHECK EFFICIENCY OF CUTS
  GetIDEfficiency(electronNoCutColl, jetColl_lepveto_mva);


  // Require now dilepton trigger passed
  if(!PassTrigger(triggerslist, prescale))  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale

  if(!isData)weight*= TriggerScaleFactor( electronAnalysisColl);

  FillEventCutFlow("TriggerCut", weight);

  if(nbjet == 0 ){
    if(PassTrigger(triggerslist, prescale))
      MakeTriLeptonPlots(GetElectrons(true,true, "HNTight"), muonVetoColl, jetColl_lepveto_mva, "_mva",  weight);
  }

  /// for systematics
  float ee_weight_method_pteta_20= weight;
  float ee_weight_method_pteta_30= weight;
  float ee_weight_method_pteta_40= weight;
  float ee_weight_method_pteta_60= weight;
  
  float ee_weight_method_ptetacb_20= weight;
  float ee_weight_method_ptetacb_30= weight;
  float ee_weight_method_ptetacb_40= weight;
  float ee_weight_method_ptetacb_60= weight;

  
  // split fakes into single and double fake bkgs
  float weight_sf= weight; 
  float weight_df= weight; 
  float ee_weight_down = weight;
  float ee_weight_up = weight;
  
  
  TString reg = fake_loose_region;
  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt){
    
    weight      *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true, 0.01, 0.09, 0.05, "method4_pt_eta_40_" + reg,0); 
    weight_err      *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true, 0.01, 0.09, 0.05, "method4_pt_eta_40_" + reg,3); 

    
    weight_sf   *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true,0.01, 0.09, 0.05,  "method4_pt_eta_40_" + reg, 1);
    weight_df   *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true,0.01, 0.09, 0.05,  "method4_pt_eta_40_" + reg, 2);
    ee_weight_up      *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true, 0.01, 0.09, 0.05, "method1_pt_eta_60_" + reg,0); 
    ee_weight_down      *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(),  true, 0.01, 0.09, 0.05, "method1_pt_eta_20_" + reg,0); 

    ee_weight_up = weight + sqrt((weight - ee_weight_up)*(weight-ee_weight_up) + weight_err*weight_err);
    ee_weight_down = weight + sqrt((weight - ee_weight_down)*(weight-ee_weight_down) + weight_err*weight_err);

    ee_weight_method_pteta_20  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method1_pt_eta_20_" + reg, 0);
    ee_weight_method_pteta_30  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method1_pt_eta_30_" + reg, 0);
    ee_weight_method_pteta_40  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method1_pt_eta_40_" + reg, 0);
    ee_weight_method_pteta_60  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method1_pt_eta_60_" + reg, 0);

    
    TString cl1 ="";
    TString cl2 ="";
    if(electronAnalysisColl.size() > 1){
      bool clb1 = HasCloseBJet(electronAnalysisColl.at(0)); 
      bool clb2 = HasCloseBJet(electronAnalysisColl.at(1)); 
      if(clb1) cl1 = "cl1";
      if(clb2) cl2 = "cl2";
    }
    ee_weight_method_ptetacb_20  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method4_pt_eta_20_" + cl1 + cl2 + reg, 0);
    ee_weight_method_ptetacb_30  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method4_pt_eta_30_" + cl1 + cl2 + reg, 0);
    ee_weight_method_ptetacb_40  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method4_pt_eta_40_" + cl1 + cl2 + reg, 0);
    ee_weight_method_ptetacb_60  *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva,  eventbase->GetEvent().JetRho(), true, 0.01, 0.09, 0.05, "method4_pt_eta_60_" + cl1 + cl2 + reg, 0);

    if(SameCharge(electronAnalysisColl) && jetColl_lepveto_mva.size() > 1){
      FakeBkgBreakDown(electronAnalysisColl, "SSee_fake_breakdown", weight);
      CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_fake_breakdown");

    }
  }


  
  /// in IsDiLep: weight is set to 0 if event does not contain 2 elecrons 20/15 gev cuts
  bool dilep_event = false;
  weight         *= IsDiLep(electronAnalysisColl);
  ee_weight_up   *= IsDiLep(electronAnalysisColl);
  ee_weight_down *= IsDiLep(electronAnalysisColl);

  ee_weight_method_pteta_20 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_pteta_30 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_pteta_40 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_pteta_60 *= IsDiLep(electronAnalysisColl);

  ee_weight_method_ptetacb_20 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_ptetacb_30 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_ptetacb_40 *= IsDiLep(electronAnalysisColl);
  ee_weight_method_ptetacb_60 *= IsDiLep(electronAnalysisColl);
  
  float combined_weight = weight; 
  /// return if there are not 2 el in the event
  if(combined_weight ==0.)  throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  if(IsDiLep(electronAnalysisColl) != 0.) dilep_event = true; 

  snu::KParticle ee;
  if(dilep_event) ee= electronAnalysisColl.at(0) + electronAnalysisColl.at(1);

  /// passevcut it bool for Default analysis id cuts for PRESELECTION
  bool pass_presel_cut (true);
  if(!dilep_event) pass_presel_cut = false;
  if(ee.M()  < 15.) pass_presel_cut = false;
  if(pass_presel_cut) FillEventCutFlow("DiEl",weight);

  
  if(dilep_event){
    // Remove overlapping particles only need electron overlap in ee channel                                                                                     
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      for(std::vector<snu::KElectron>::iterator it2 = it+1; it2 != electronAnalysisColl.end(); it2++){
	if(it->DeltaR(*it2) < 0.5)  pass_presel_cut = false;
      }
    }
    if(pass_presel_cut) FillEventCutFlow("eedR", weight);
  }
  
  // TOP Control region os/SS    
  if(dilep_event && nbjet >= 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(electronAnalysisColl.size() ==2){
	if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	  FillCLHist(sighist, "Top", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  
  
  if(electronAnalysisColl.size() == 2){
    if(electronAnalysisColl.at(0).Charge() !=  electronAnalysisColl.at(1).Charge()){
      FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FillCLHist(sighist, "OSee_nojetpumva", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto, weight, weight_err);
    }
  }
  
  /// For CF use OS data and weight using CF rates from sunny // WeightCFEvent sets weight to 0 if OS and not running CF, sets weight to 0 is SS and running
  weight              *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  weight_df           *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  weight_sf           *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);

  if(WeightCFEvent(electronAnalysisColl, k_running_chargeflip) == 0.) pass_presel_cut = false;

  ee_weight_up        *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_down      *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);

  ee_weight_method_pteta_20  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_pteta_30  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_pteta_40  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_pteta_60  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);

  ee_weight_method_ptetacb_20  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_ptetacb_30  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_ptetacb_40  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);
  ee_weight_method_ptetacb_60  *= WeightCFEvent(electronAnalysisColl, k_running_chargeflip);

   
  float cf_combined_weight= weight;
  /// return if there are not 2 el in the event
  if(cf_combined_weight ==0.)  throw LQError( "Fails basic cuts",  LQError::SkipEvent );


  ///// NOW OS event is weighted for CF sample
  
  if(pass_presel_cut){
    FillEventCutFlow("SSDiEl",weight);
    FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
    FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);
  }
  
  /// Remove events with 3 veto leptons
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) throw LQError( "Fails basic cuts",  LQError::SkipEvent );  
  if(muonVetoColl.size() !=0) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  if(jetColl_lepveto_mva.size() > 2)
    FillHist("Number_of_Loose" , electronAnalysisColl.size() , 1., 0., 5., 5);
  
  if(pass_presel_cut)FillEventCutFlow("SS_lepveto",weight);
  
  m_logger << DEBUG << "Making lepton veto cut "<< LQLogger::endmsg;

  if(pass_presel_cut) {
    if(electronAnalysisColl.at(0).VertexIndex() != electronAnalysisColl.at(1).VertexIndex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }
  /// before third lepton veto no fake estimate can be done.
  if(dilep_event&& pass_presel_cut){
    /// END of NP bkg loop
    if(jetColl_lepveto_mva.size() == 0){
      FakeBkgBreakDown(electronAnalysisColl, "SSee_0jet",weight);
    }
    if(jetColl_lepveto_mva.size() == 1){
      FakeBkgBreakDown(electronAnalysisColl, "SSee_1jet",weight);
    }
    if(jetColl_lepveto_mva.size() > 1){
      FakeBkgBreakDown(electronAnalysisColl, "SSee_2jet",weight);
      CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_dijet_fake_breakdown");
      if(NBJet(jetColl_lepveto_mva) == 0){
	FakeBkgBreakDown(electronAnalysisColl, "SSee_2jet_0bjet",weight);
	CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_dijet_0bjet_fake_breakdown");
	if(eventbase->GetEvent().PFMET() < 30.){
	  FakeBkgBreakDown(electronAnalysisColl, "SSee_2jet_MET",weight);
	  CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_dijet_MET_fake_breakdown");
	}
      }
    }
  }
  m_logger << DEBUG << "Making SS Plots "<< LQLogger::endmsg;
  
  
  if(pass_presel_cut){
    if(jetColl_lepveto_mva.size() > 1){
      
      if(!Zcandidate(electronAnalysisColl, 20., false)) 
	FillCLHist(sighist, "SSee_gt1jet_noZ", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      else 
	FillCLHist(sighist, "SSee_gt1jet_Z", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      
      if(true){
	int ij1(0),ij2(0);
	float wmassjj=0.;
	for(unsigned int ij=0; ij < jetColl_lepveto_mva.size()-1; ij++){
	  for(unsigned int ij2=ij+1; ij2 < jetColl_lepveto_mva.size(); ij2++){
	    snu::KParticle jjtmp = jetColl_lepveto_mva.at(ij) + jetColl_lepveto_mva.at(ij2) ;
	    if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	      wmassjj = fabs(jjtmp.M() - 80.4);
	      ij1=ij;
	      ij2=ij2;
	    }
	  }
	}
	
	snu::KParticle eejjtmp = ee  + jetColl_lepveto_mva.at(ij1) + jetColl_lepveto_mva.at(ij2) ;
	
	if(ee.M() < 40. && eejjtmp.M() > 350) 
	  FillCLHist(sighist, "SSee_gt1jet_lowZhighW", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
	
	cout << "ee.M() = " << ee.M() << " weight= " << weight << endl;
	if(ee.M() < 35. && ee.M() > 25.&&jetColl_lepveto_mva.size() == 2){
	  FillCLHist(sighist, "SSee_gt1jet_lowZ", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	  if(eventbase->GetEvent().PFMET() > 20. && eventbase->GetEvent().PFMET() < 30.)         FillCLHist(sighist, "SSee_gt1jet_lowZ_met", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	  else  FillCLHist(sighist, "SSee_gt1jet_lowZ_met2", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	}
	if(nbjet == 0 )
	  FillCLHist(sighist, "SSee_gt1jet_0bjet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	
	if(jetColl_lepveto_mva.size() == 2 && !Zcandidate(electronAnalysisColl, 20., false))
	  FillCLHist(sighist, "SSee_gt1jet_2jet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	if(jetColl_lepveto_mva.size() == 3)
	  FillCLHist(sighist, "SSee_gt1jet_3jet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	if(jetColl_lepveto_mva.size() == 4)
	  FillCLHist(sighist, "SSee_gt1jet_4jet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
	if(jetColl_lepveto_mva.size() > 5)
	  FillCLHist(sighist, "SSee_gt1jet_5jet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      }
    }
    if(ee.M() > 100.){
      if(jetColl_lepveto_mva.size() ==1){
	
	FillCLHist(sighist, "SSee_1jet_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
	FillCLHist(sighist, "SSee_1jet_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);
	
	FillCLHist(sighist, "SSee_1jet_m1_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_30);
	FillCLHist(sighist, "SSee_1jet_m4_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_30);

	FillHist("SSee_1jet_m_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
	FillHist("SSee_1jet_m_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);
	FillHist("SSee_1jet_m_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
	FillHist("SSee_1jet_m_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);

	FillHist("SSee_1jet_m_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
	FillHist("SSee_1jet_m_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);

	FillHist("SSee_1jet_m_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
	FillHist("SSee_1jet_m_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

      }
    }
  }
  

  if(jetColl_lepveto_mva.size() >= 2 && pass_presel_cut ){
    FillEventCutFlow("DiJet",weight);
  }
 

  if(jetColl_lepveto_mva.size() < 2) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  FakeBkgBreakDown(electronAnalysisColl , "Presel_fakes", weight);
  
  if(electronAnalysisColl.size() == 2 )FillHist("Presel_elecoll_comp" , 0 ,weight, 0.,9.,9 );
  
  //// Check punzi using different electron IDs
  if(CheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, "", weight)) FillHist("ID_punzi_check", 0., weight, 0., 7., 7);



  if(pass_presel_cut){
    FillEventCutFlow("Presel",weight);
    FillHist("Presel_fakecomp", 0, weight , 0., 3.,3);    
    FillHist("Presel_fakecomp", 1, weight_sf , 0., 3.,3);    
    FillHist("Presel_fakecomp", 2, weight_df , 0., 3.,3);    
    if(!Zcandidate(electronAnalysisColl, 20., false)){
      FillEventCutFlow("Presel_noZ",weight);
      if(nbjet==0)   FillEventCutFlow("Presel_nobjet",weight);
    }
  }
  
  /// btag SF
  int jetFlavour=-999999;
  bool b_found = false;
  bool b_foundEffDown(false), b_foundEffUp(false) ,b_foundMissDown(false), b_foundMissUp(false);
  std::vector<snu::KTruth> genBColl;
  for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
    if(eventbase->GetTruth().at(ig).Pt() < 10.) continue;
    if(fabs(eventbase->GetTruth().at(ig).Eta()) > 3.) continue;
    genBColl.push_back(eventbase->GetTruth().at(ig));
  }

  for(unsigned int ij=0; ij < jetColl_lepveto_mva.size(); ij++){
    for(unsigned int ig=0; ig < genBColl.size(); ig++){
      if(jetColl_lepveto_mva.at(ij).DeltaR(genBColl.at(ig)) < 0.3 ){
        jetFlavour = int(fabs(genBColl[ig].PdgId()));
        break;
      }
      else{
	jetFlavour = 21;
      }
    }
    if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour, jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) ){
      b_found = true;
    }

    if (jetFlavour==4 || jetFlavour==5) {
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), -1) )
        b_foundEffDown = true;
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), +1) )
	b_foundEffUp = true;
    }
    else
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) ) {
        b_foundEffDown = true;
        b_foundEffUp = true;
      }

    if (jetFlavour==1 || jetFlavour==2 || jetFlavour==3 || jetFlavour==21) {
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), -1) )
        b_foundMissDown = true;
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), +1) )
        b_foundMissUp = true;
    }
    else
      if ( fBTagSF->IsTagged(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag(), jetFlavour,jetColl_lepveto_mva.at(ij).Pt(), jetColl_lepveto_mva.at(ij).Eta(), 0) ) {
        b_foundMissDown = true;
        b_foundMissUp = true;
      }
  }



  

  if(pass_presel_cut){
    
    FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
    
    if(!Zcandidate(electronAnalysisColl, 10., false)){
      
      FillCLHist(sighist, "Preselection", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FillCLHist(sighist, "Preselection_up", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_up);
      FillCLHist(sighist, "Preselection_down", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_down);

      FillCLHist(sighist, "Preselection_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
      FillCLHist(sighist, "Preselection_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);
      FillCLHist(sighist, "Preselection_m1_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_30);
      FillCLHist(sighist, "Preselection_m4_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_30);

      FillHist("Presel_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
      FillHist("Presel_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);
      FillHist("Presel_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
      FillHist("Presel_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);
      
      FillHist("Presel_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
      FillHist("Presel_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);
      
      FillHist("Presel_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
      FillHist("Presel_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

    }
  }
  else{
    throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  }
  
  float event_met = eventbase->GetEvent().PFMET();
  float event_met_jesup = eventbase->GetEvent().PFMET_Jet_EnUp() ;
  float event_met_jesdown = eventbase->GetEvent().PFMET_Jet_EnDown() ;
  float event_met_jresup = eventbase->GetEvent().PFMET_Jet_ResUp();
  float event_met_jresdown = eventbase->GetEvent().PFMET_Jet_ResDown();
  float event_met_unclustup = eventbase->GetEvent().PFMET_Unclust_Up();
  float event_met_unclustdown = eventbase->GetEvent().PFMET_Unclust_Down();
  std::vector<snu::KJet> jetColl_jetE_up;
  std::vector<snu::KJet> jetColl_jetE_down;
  std::vector<snu::KJet> jetColl_jetRes_up;
  std::vector<snu::KJet> jetColl_jetRes_down;
  
  for(unsigned int ij=0; ij < jetColl_lepveto_mva.size(); ij++){
    snu::KJet jetEup = jetColl_lepveto_mva.at(ij);
    snu::KJet jetEdown = jetColl_lepveto_mva.at(ij);
    snu::KJet jetResup = jetColl_lepveto_mva.at(ij);
    snu::KJet jetResdown = jetColl_lepveto_mva.at(ij);
    if(jetEup.ScaledUpPt() > 20. )jetEup.SetPtEtaPhiE(jetEup.ScaledUpPt(), jetEup.Eta(), jetEup.Phi(), jetEup.ScaledUpEnergy());
    if(jetEdown.ScaledDownPt() > 20. ) jetEdown.SetPtEtaPhiE(jetEdown.ScaledDownPt(), jetEdown.Eta(), jetEdown.Phi(), jetEdown.ScaledDownEnergy());
    if(jetResup.SmearedUpPt() > 20. ) jetResup.SetPtEtaPhiE(jetResup.SmearedUpPt(), jetResup.Eta(), jetResup.Phi(), jetResup.SmearedUpEnergy());
    if(jetResdown.SmearedDownPt() > 20. )  jetResdown.SetPtEtaPhiE(jetResdown.SmearedDownPt(), jetResdown.Eta(), jetResdown.Phi(), jetResdown.SmearedDownEnergy());
    
    if(jetEup.ScaledUpPt() > 20. )jetColl_jetE_up.push_back(jetEup);
    if(jetEdown.ScaledDownPt() > 20. ) jetColl_jetE_down.push_back(jetEdown);
    if(jetResup.SmearedUpPt() > 20. )jetColl_jetRes_up.push_back(jetResup);
    if(jetResdown.SmearedDownPt() > 20. ) jetColl_jetRes_down.push_back(jetResdown);
  }
 
  std::vector<float> masscuts40;
  masscuts40.push_back(20.);  masscuts40.push_back(15.);   /// pt1 / pt2
  masscuts40.push_back(15.);  masscuts40.push_back(60.);   /// m(ee)
  masscuts40.push_back(0.);   masscuts40.push_back(120.);  /// m(jj)
  masscuts40.push_back(80.);  masscuts40.push_back(155.);  /// m(eejj)
  masscuts40.push_back(30.);                               /// MET
  masscuts40.push_back(20.);                               /// jet 1 pt
  masscuts40.push_back(0.);  masscuts40.push_back(120.);  /// m(e2jj)
  masscuts40.push_back(60.);  masscuts40.push_back(130.);  /// m(e2jj)

  std::vector<float> masscuts50;
  masscuts50.push_back(20.);  masscuts50.push_back(15.);
  masscuts50.push_back(15.);  masscuts50.push_back(60.);
  masscuts50.push_back(0.);   masscuts50.push_back(120.);
  masscuts50.push_back(80.);  masscuts50.push_back(155.);
  masscuts50.push_back(30.);
  masscuts50.push_back(20.);
  masscuts50.push_back(0.);  masscuts50.push_back(120.);
  masscuts50.push_back(60.);  masscuts50.push_back(130.);  /// m(e1jj)

  std::vector<float> masscuts60;
  masscuts60.push_back(20.);  masscuts60.push_back(15.);
  masscuts60.push_back(15.);  masscuts60.push_back(60.);
  masscuts60.push_back(0.);   masscuts60.push_back(120.);
  masscuts60.push_back(80.);  masscuts60.push_back(165.);
  masscuts60.push_back(30.);
  masscuts60.push_back(20.);
  masscuts60.push_back(0.);  masscuts60.push_back(120.);
  masscuts60.push_back(60.);  masscuts60.push_back(130.);

  std::vector<float> masscuts70;
  masscuts70.push_back(20.);  masscuts70.push_back(15.);
  masscuts70.push_back(15.);  masscuts70.push_back(60.);
  masscuts70.push_back(0.);   masscuts70.push_back(120.);
  masscuts70.push_back(80.);  masscuts70.push_back(165.);
  masscuts70.push_back(30.);
  masscuts70.push_back(20.);
  masscuts70.push_back(0.);  masscuts70.push_back(120.);
  masscuts70.push_back(70.);  masscuts70.push_back(160.);


  std::vector<float> masscuts80;
  masscuts80.push_back(20.);  masscuts80.push_back(15.);
  masscuts80.push_back(15.);  masscuts80.push_back(70.);
  masscuts80.push_back(0.);   masscuts80.push_back(120.);
  masscuts80.push_back(80.);  masscuts80.push_back(220.);
  masscuts80.push_back(30.);
  masscuts80.push_back(20.);
  masscuts80.push_back(60.);  masscuts80.push_back(120.);
  masscuts80.push_back(70.);  masscuts80.push_back(180.);

  std::vector<float> masscuts90l;

  masscuts90l.push_back(20.);  masscuts90l.push_back(15.);
  masscuts90l.push_back(15.);  masscuts90l.push_back(100000.);
  masscuts90l.push_back(0.);   masscuts90l.push_back(120.);
  masscuts90l.push_back(80.);  masscuts90l.push_back(220.);
  masscuts90l.push_back(30.);
  masscuts90l.push_back(20.);
  masscuts90l.push_back(80.);  masscuts90l.push_back(120.);
  masscuts90l.push_back(70.);  masscuts90l.push_back(190.);

  vector<int> btagsyst;
  if(!b_foundMissDown) btagsyst.push_back(8);
  if(!b_foundMissUp) btagsyst.push_back(9);
  if(!b_foundEffDown) btagsyst.push_back(10);
  if(!b_foundEffUp) btagsyst.push_back(11);



  std::vector<float> masscuts80m;
  masscuts80m.push_back(20.);  masscuts80m.push_back(15.);
  masscuts80m.push_back(30.);  masscuts80m.push_back(10000.);
  masscuts80m.push_back(50.);   masscuts80m.push_back(110.);
  masscuts80m.push_back(80.);  masscuts80m.push_back(20000.);
  masscuts80m.push_back(35.);
  masscuts80m.push_back(30.);
  masscuts80m.push_back(70.);  masscuts80m.push_back(120.);
  masscuts80m.push_back(0.);  masscuts80m.push_back(100000.);

  std::vector<float> masscuts90;
  masscuts90.push_back(20.);  masscuts90.push_back(15.);
  masscuts90.push_back(30.);  masscuts90.push_back(10000.);
  masscuts90.push_back(50.);   masscuts90.push_back(110.);
  masscuts90.push_back(90.);  masscuts90.push_back(20000.);
  masscuts90.push_back(35.);
  masscuts90.push_back(30.);
  masscuts90.push_back(70.);  masscuts90.push_back(120.);
  masscuts90.push_back(0.);  masscuts90.push_back(100000.);

  std::vector<float> masscuts100;
  masscuts100.push_back(20.);  masscuts100.push_back(15.);
  masscuts100.push_back(30.);  masscuts100.push_back(10000.);
  masscuts100.push_back(50.);  masscuts100.push_back(110.);
  masscuts100.push_back(100.); masscuts100.push_back(10000.);
  masscuts100.push_back(35.);
  masscuts100.push_back(30.);
  masscuts100.push_back(80.);  masscuts100.push_back(120.);
  masscuts100.push_back(0.);  masscuts100.push_back(10000.);




  std::vector<float> masscuts125;
  masscuts125.push_back(30.);  masscuts125.push_back(20.);
  masscuts125.push_back(30.);  masscuts125.push_back(10000.);
  masscuts125.push_back(50.);  masscuts125.push_back(110.);
  masscuts125.push_back(140.); masscuts125.push_back(10000.);
  masscuts125.push_back(35.);
  masscuts125.push_back(30.);
  masscuts125.push_back(90.);  masscuts125.push_back(145.);
  masscuts125.push_back(0.);  masscuts125.push_back(10000.);

  std::vector<float> masscuts150;
  masscuts150.push_back(35.);  masscuts150.push_back(25.);
  masscuts150.push_back(30.);  masscuts150.push_back(10000.);
  masscuts150.push_back(50.);  masscuts150.push_back(110.);
  masscuts150.push_back(160.); masscuts150.push_back(10000.);
  masscuts150.push_back(35.);
  masscuts150.push_back(30.);
  masscuts150.push_back(120.);  masscuts150.push_back(180.);
  masscuts150.push_back(0.);  masscuts150.push_back(10000.);

  std::vector<float> masscuts175;
  masscuts175.push_back(45.);  masscuts175.push_back(30.);
  masscuts175.push_back(30.);  masscuts175.push_back(10000.);
  masscuts175.push_back(50.);  masscuts175.push_back(110.);
  masscuts175.push_back(240.); masscuts175.push_back(10000.);
  masscuts175.push_back(35.);
  masscuts175.push_back(30.);
  masscuts175.push_back(140.);  masscuts175.push_back(200.);
  masscuts175.push_back(0.);  masscuts175.push_back(20000.);

  std::vector<float> masscuts200;
  masscuts200.push_back(65.);  masscuts200.push_back(40.);
  masscuts200.push_back(30.);  masscuts200.push_back(10000.);
  masscuts200.push_back(50.);  masscuts200.push_back(110.);
  masscuts200.push_back(280.); masscuts200.push_back(10000.);
  masscuts200.push_back(35.);
  masscuts200.push_back(30.);
  masscuts200.push_back(160.);  masscuts200.push_back(250.);
  masscuts200.push_back(0.);  masscuts200.push_back(25000.);

  std::vector<float> masscuts225;
  masscuts225.push_back(70.);  masscuts225.push_back(40.);
  masscuts225.push_back(30.);  masscuts225.push_back(10000.);
  masscuts225.push_back(50.);  masscuts225.push_back(110.);
  masscuts225.push_back(290.); masscuts225.push_back(10000.);
  masscuts225.push_back(35.);
  masscuts225.push_back(30.);
  masscuts225.push_back(160.);  masscuts225.push_back(260.);
  masscuts225.push_back(1.);  masscuts225.push_back(26000.);

  
  std::vector<float> masscuts250;
  masscuts250.push_back(70.);  masscuts250.push_back(45.);
  masscuts250.push_back(30.);  masscuts250.push_back(10000.);
  masscuts250.push_back(50.);  masscuts250.push_back(110.);
  masscuts250.push_back(300.); masscuts250.push_back(10000.);
  masscuts250.push_back(35.);
  masscuts250.push_back(40.);
  masscuts250.push_back(0.);  masscuts250.push_back(10000.);
  masscuts250.push_back(0.);  masscuts250.push_back(10000.);

  std::vector<float> masscuts275;
  masscuts275.push_back(70.);  masscuts275.push_back(45.);
  masscuts275.push_back(30.);  masscuts275.push_back(10000.);
  masscuts275.push_back(50.);  masscuts275.push_back(110.);
  masscuts275.push_back(320.); masscuts275.push_back(10000.);
  masscuts275.push_back(35.);
  masscuts275.push_back(40.);
  masscuts275.push_back(0.);  masscuts275.push_back(10000.);
  masscuts275.push_back(0.);  masscuts275.push_back(10000.);

  std::vector<float> masscuts300;
  masscuts300.push_back(120);  masscuts300.push_back(25.);
  masscuts300.push_back(30.);  masscuts300.push_back(10000.);
  masscuts300.push_back(50.);  masscuts300.push_back(110.);
  masscuts300.push_back(350.); masscuts300.push_back(10000.);
  masscuts300.push_back(35.);
  masscuts300.push_back(40.);
  masscuts300.push_back(0.);  masscuts300.push_back(10000.);
  masscuts300.push_back(0.);  masscuts300.push_back(10000.);

  std::vector<float> masscuts325;
  masscuts325.push_back(120);  masscuts325.push_back(25.);
  masscuts325.push_back(30.);  masscuts325.push_back(10000.);
  masscuts325.push_back(50.);  masscuts325.push_back(110.);
  masscuts325.push_back(350.); masscuts325.push_back(10000.);
  masscuts325.push_back(35.);
  masscuts325.push_back(40.);
  masscuts325.push_back(0.);  masscuts325.push_back(10000.);
  masscuts325.push_back(0.);  masscuts325.push_back(10000.);



  std::vector<float> masscuts350;
  masscuts350.push_back(120);  masscuts350.push_back(25.);
  masscuts350.push_back(30.);  masscuts350.push_back(10000.);
  masscuts350.push_back(50.);  masscuts350.push_back(110.);
  masscuts350.push_back(350.); masscuts350.push_back(10000.);
  masscuts350.push_back(35.);
  masscuts350.push_back(40.);
  masscuts350.push_back(0.);  masscuts350.push_back(10000.);
  masscuts350.push_back(0.);  masscuts350.push_back(10000.);



  std::vector<float> masscuts375;
  masscuts375.push_back(120);  masscuts375.push_back(25.);
  masscuts375.push_back(30.);  masscuts375.push_back(10000.);
  masscuts375.push_back(50.);  masscuts375.push_back(110.);
  masscuts375.push_back(350.); masscuts375.push_back(10000.);
  masscuts375.push_back(35.);
  masscuts375.push_back(40.);
  masscuts375.push_back(0.);  masscuts375.push_back(10000.);
  masscuts375.push_back(0.);  masscuts375.push_back(10000.);

  std::vector<float> masscuts400;
  masscuts400.push_back(125);  masscuts400.push_back(25.);
  masscuts400.push_back(30.);  masscuts400.push_back(10000.);
  masscuts400.push_back(50.);  masscuts400.push_back(110.);
  masscuts400.push_back(350.); masscuts400.push_back(10000.);
  masscuts400.push_back(35.);
  masscuts400.push_back(40.);
  masscuts400.push_back(0.);  masscuts400.push_back(10000.);
  masscuts400.push_back(0.);  masscuts400.push_back(10000.);

  std::vector<float> masscuts500;
  masscuts500.push_back(130);  masscuts500.push_back(25.);
  masscuts500.push_back(30.);  masscuts500.push_back(10000.);
  masscuts500.push_back(50.);  masscuts500.push_back(110.);
  masscuts500.push_back(350.); masscuts500.push_back(10000.);
  masscuts500.push_back(35.);
  masscuts500.push_back(40.);
  masscuts500.push_back(0.);  masscuts500.push_back(10000.);
  masscuts500.push_back(0.);  masscuts500.push_back(10000.);

  std::vector<float> masscuts600;
  masscuts600.push_back(125);  masscuts600.push_back(25.);
  masscuts600.push_back(30.);  masscuts600.push_back(10000.);
  masscuts600.push_back(50.);  masscuts600.push_back(110.);
  masscuts600.push_back(350.); masscuts600.push_back(10000.);
  masscuts600.push_back(35.);
  masscuts600.push_back(40.);
  masscuts600.push_back(0.);  masscuts600.push_back(10000.);
  masscuts600.push_back(0.);  masscuts600.push_back(10000.);
  std::vector<float> masscuts700;
  masscuts700.push_back(125);  masscuts700.push_back(25.);
  masscuts700.push_back(30.);  masscuts700.push_back(10000.);
  masscuts700.push_back(50.);  masscuts700.push_back(110.);
  masscuts700.push_back(350.); masscuts700.push_back(10000.);
  masscuts700.push_back(35.);
  masscuts700.push_back(40.);
  masscuts700.push_back(0.);  masscuts700.push_back(10000.);
  masscuts700.push_back(0.);  masscuts700.push_back(10000.);




  /// Map for masspoint and list of cuts (fully optimised)
  std::map< TString,  std::pair< std::vector<snu::KElectron> , float> > leptonmap;
  leptonmap[""]  = make_pair(electronAnalysisColl, weight);

  
  std::map<TString, std::vector<float> > sysymap;
  sysymap["40"] =  masscuts40;  sysymap["50"] =  masscuts50;
  sysymap["60"] =  masscuts60;  sysymap["70"] =  masscuts70;
  sysymap["80"] =  masscuts80;  sysymap["90"] =  masscuts90;
  sysymap["100"] =  masscuts100; sysymap["125"] =  masscuts125;
  sysymap["150"] =  masscuts150; sysymap["175"] =  masscuts175;
  sysymap["200"] =  masscuts200;  sysymap["225"] =  masscuts225;
  sysymap["250"] =  masscuts250;  sysymap["275"] =  masscuts275;
  sysymap["300"] =  masscuts300;  sysymap["325"] =  masscuts325;
  sysymap["350"] =  masscuts350;  sysymap["375"] =  masscuts375;
  sysymap["400"] =  masscuts400;  sysymap["500"] =  masscuts500;
  sysymap["600"] =  masscuts700;  sysymap["700"] =  masscuts700;
  
  // Add addition criteris .. i.e, remove me2jj cut 
  std::map<TString, TString > sysymap2;
  sysymap2["_default"] = "default";
  sysymap2[""] = "basic";
  sysymap2["_noMe2jj"] = "noMe2jj";
  sysymap2["_closejet"] = "closejet";

  for( std::map< TString,  std::pair< std::vector<snu::KElectron> , float> >::iterator lepmapit = leptonmap.begin(); lepmapit != leptonmap.end(); lepmapit++){
    for( std::map<TString, std::vector<float> >::iterator mapit = sysymap.begin(); mapit != sysymap.end(); mapit++){
      for( std::map<TString, TString >::iterator mapit2 = sysymap2.begin(); mapit2 != sysymap2.end(); mapit2++){
	TString label = lepmapit->first + mapit->first+ mapit2->first + "MassRegion_limithist";	

	if(lepmapit->first.Contains("iso") && (mapit2->second != "default")) continue;
	if(lepmapit->first.Contains("tight") && (mapit2->second != "default")) continue;
	if(lepmapit->first.Contains("medium") && (mapit2->second != "default")) continue;
	if(lepmapit->first.Contains("susy") && (mapit2->second != "default")) continue;
	
	/// ANALYSIS FINAL SELECTION HISTS
	/// Low Mass                       pt2, pt1  ,eemin, max, jjmin,max, eejjmin,max, STmin,max, j1  , e2jjmin, ej22max, njet
	
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva,event_met, k_running_chargeflip , mapit->second, mapit2->second) ){
	  if(mapit2->second == "default"){
	    if(!lepmapit->first.Contains("iso"))
	      if(!lepmapit->first.Contains("medium"))
		if(!lepmapit->first.Contains("tight"))
		  if(!lepmapit->first.Contains("susy")){
		    FillCLHist(sighist, (mapit->first + lepmapit->first+"MassRegion").Data(), eventbase->GetEvent(), muonVetoColl,lepmapit->second.first,jetColl_lepveto_mva, lepmapit->second.second);
		    cout << "lepmapit->first = " << lepmapit->first << endl;
		    cout << " mapit->first = " << mapit->first << endl;
		    cout << " mapit2->first : " << mapit2->first << endl;
		    cout << " mapit2->second : " << mapit2->second << endl;
		    
	            CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, label);
		  }
	  }
	  FillHist(label.Data(), 0, 1. , 0., 16.,16);
	  FillHist(label.Data(), 1, lepmapit->second.second , 0., 16.,16);
	  
	  FakeBkgBreakDown(lepmapit->second.first,label,lepmapit->second.second);
	}       
	
	/// SYSTEMATCICS
	/// JET SYST
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_jetE_up ,event_met_jesup, k_running_chargeflip , mapit->second, mapit2->second))
	  FillHist(label.Data(), 2, lepmapit->second.second , 0., 16.,16);
	
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_jetE_down ,event_met_jesdown, k_running_chargeflip , mapit->second, mapit2->second))
	  FillHist(label.Data(), 3, lepmapit->second.second , 0., 16.,16);
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_jetRes_up ,event_met_jresup, k_running_chargeflip , mapit->second, mapit2->second))
	  FillHist(label.Data(), 4 , lepmapit->second.second , 0., 16.,16);
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_jetRes_down ,event_met_jresdown, k_running_chargeflip ,  mapit->second, mapit2->second))
	  FillHist(label.Data(), 5  , lepmapit->second.second , 0., 16.,16);
	
	/// MET
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustup, k_running_chargeflip ,  mapit->second, mapit2->second))
	  FillHist(label.Data(), 6,  lepmapit->second.second , 0., 16.,16);
	
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second, mapit2->second))
	  FillHist(label.Data(), 7,  lepmapit->second.second , 0., 16.,16);
	
	///Btag syst : 8 -11
	for(unsigned int ib = 0; ib < btagsyst.size(); ib++){
	  if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva,event_met, k_running_chargeflip ,  mapit->second, mapit2->second))
	    FillHist(label.Data(),btagsyst.at(ib), lepmapit->second.second , 0., 16.,16);
	}
	
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second, mapit2->second))
          FillHist(label.Data(), 12,  ee_weight_up , 0., 16.,16);
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second, mapit2->second))
          FillHist(label.Data(), 13,  ee_weight_down , 0., 16.,16);

	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second, mapit2->second))
          FillHist(label.Data(), 14, (lepmapit->second.second*pileup_up_sys_factor)  , 0., 16.,16);
	if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_lepveto_mva ,event_met_unclustdown, k_running_chargeflip ,  mapit->second, mapit2->second))
	  FillHist(label.Data(), 15, (lepmapit->second.second*pileup_down_sys_factor)  , 0., 16.,16);

	
      }// additional requirements
    }// lepton map : checks limits with different lepton collections (fakes needed in fake code)
    
  }
  /// END OF MAP LOOP
  
  
  //// Low Mass Signal region
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) {
    if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 30.))){
      CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_lowmass_fake_breakdown");
      FillHist("LowMass_fakecomp", 0, weight , 0., 3.,3);
      FillHist("LowMass_fakecomp", 1, weight_sf , 0., 3.,3);
      FillHist("LowMass_fakecomp", 2, weight_df , 0., 3.,3);
      
      
      FillEventCutFlow("lowmass",weight);
      FillCLHist(sighist, "LowMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FakeBkgBreakDown(electronAnalysisColl, "LowMass",weight);
    }
    
    if((nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)) {
      FillCLHist(sighist, "HighMETBJetCR_LowMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FillEventCutFlow("lowmassCR",weight);
      FillCLHist(sighist, "HighMETBJetCR_LowMassRegion_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
      FillCLHist(sighist, "HighMETBJetCR_LowMassRegion_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);

      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);

      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);
      
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
      FillHist("HighMETBJetCR_LowMassRegion_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

    }
  }
  
  if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 35.))){
      FillHist("MediumMass_fakecomp", 0, weight , 0., 3.,3);
      FillHist("MediumMass_fakecomp", 1, weight_sf , 0., 3.,3);
      FillHist("MediumMass_fakecomp", 2, weight_df , 0., 3.,3);
      FillCLHist(sighist, "MediumMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FakeBkgBreakDown(electronAnalysisColl, "MediumMass",weight);
      FillEventCutFlow("mediummass",weight);
      CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_mediummass_fake_breakdown");

    }
    if((nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)){
      FillCLHist(sighist, "HighMETBJetCR_MediumMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FillEventCutFlow("mediummassCR",weight);
      FillCLHist(sighist, "HighMETBJetCR_MediumMassRegion_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
      FillCLHist(sighist, "HighMETBJetCR_MediumMassRegion_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);

      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);

      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);

      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);
      
      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
      FillHist("HighMETBJetCR_MediumMassRegion_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

    }
  }
  if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 35.))){
      FillHist("HighMass_fakecomp", 0, weight , 0., 3.,3);
      FillHist("HighMass_fakecomp", 1, weight_sf , 0., 3.,3);
      FillHist("HighMass_fakecomp", 2, weight_df , 0., 3.,3);
      FillCLHist(sighist, "HighMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FakeBkgBreakDown(electronAnalysisColl, "HighMass",weight);
      CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel_highmass_fake_breakdown");
      FillEventCutFlow("highmass",weight);
    }
    if((nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)){
      FillCLHist(sighist, "HighMETBJetCR_HighMassRegion", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
      FillEventCutFlow("highmassCR",weight);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);

      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);
      
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
      FillHist("HighMETBJetCR_HighMassRegion_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

    }
  }
    
  if(pass_presel_cut&& (nbjet!=0))   {

    FillCLHist(sighist, "BJetCR_alljets", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl, weight);


    FillCLHist(sighist, "BJetCR_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
    FillCLHist(sighist, "BJetCR_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);


    FillCLHist(sighist, "BJetCR_m1_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_30);
    FillCLHist(sighist, "BJetCR_m4_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_30);


    FillHist("BJetCR_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
    FillHist("BJetCR_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);

    FillHist("BJetCR_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
    FillHist("BJetCR_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);

    FillHist("BJetCR_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
    FillHist("BJetCR_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);

    FillHist("BJetCR_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
    FillHist("BJetCR_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);

  }

  if(pass_presel_cut&& (nbjet==0) && (eventbase->GetEvent().PFMET() > 50.)) {

    FillHist("HighMETCR_fakeparam_20", 0, ee_weight_method_pteta_20  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_20", 3, ee_weight_method_ptetacb_20  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_30", 0, ee_weight_method_pteta_30  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_30", 3, ee_weight_method_ptetacb_30  , 0., 9., 9);

    FillHist("HighMETCR_fakeparam_40", 0, ee_weight_method_pteta_40  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_40", 3, ee_weight_method_ptetacb_40  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_60", 0, ee_weight_method_pteta_60  , 0., 9., 9);
    FillHist("HighMETCR_fakeparam_60", 3, ee_weight_method_ptetacb_60  , 0., 9., 9);
    
    FillCLHist(sighist, "HighMETCR_m1_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_40);
    FillCLHist(sighist, "HighMETCR_m4_40", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_40);

    FillCLHist(sighist, "HighMETCR_m1_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_pteta_30);
    FillCLHist(sighist, "HighMETCR_m4_30", eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_method_ptetacb_30);
  }

  if(pass_presel_cut&& (nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)) 
    FillCLHist(sighist, "HighMETBJetCR",eventbase->GetEvent(), muonVetoColl,electronAnalysisColl,jetColl_lepveto_mva, weight, weight_err);
  
  
  return;
}// End of execute event loop



float HNDiElectron::IsDiLep(std::vector<snu::KElectron> electrons){

  if(electrons.size() == 2 ){
    if(electrons.at(0).Pt() > 20.){
      if(electrons.at(1).Pt() > 15.){
	return 1.;
      }
    }
  }
  return 0.;
}

float HNDiElectron::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip, bool useoldrates){

  if(electrons.size()!=2) return 0.;
  if(runchargeflip) {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()) {
      float cf1=  CFRate(electrons.at(0), useoldrates);
      float cf2=  CFRate(electrons.at(1),useoldrates);
      return ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    else return 0.;
  }// cf requirement
  else {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()) return 0.;
  }
  
  return 1.;
  
}

bool HNDiElectron::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(electrons.size() != 2 ) return false ;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!SameCharge(electrons)) return false;
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(eejj.M()  > 200.) return false;

  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return false;
  if(jj.M() < 40.) return false;

  if(ee.M() > 80.) return false;
  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  

  if(additional_option.Contains("btag_t")) btagwp = 2; 
  if(additional_option.Contains("btag_l")) btagwp = 0; 

  bool removeclosejet = false;
  if(additional_option.Contains("closejet")) removeclosejet = true;
  
  bool cut_on_me2jj=true;
  if(additional_option.Contains("noMe2jj")) cut_on_me2jj= false;
  
  if(additional_option.Contains("basic")){
    if(electrons.size() != 2) return false;
    if(electrons.at(0).Pt() < 20.) return false;
    if(electrons.at(1).Pt() < 15.) return false;
    if(jets.size() < 2) return false;
    if(jets.at(0).Pt() < cuts.at(9)) return false;

    float wmassjj= 100000.;
    int indexj1=0;
    int indexj2=0;

    for(unsigned int ij=0; ij < jets.size()-1; ij++){
      for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
	snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
	if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	  wmassjj = fabs(jjtmp.M() - 80.4);
	  indexj1=ij;
	  indexj2=ij2;
	}
      }
    }

    snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
    if(jj.M() > 110.) return false;
    if(jj.M() < 50.) return false;
    if(evmet > 35.) return false;
    
    return true;
  }
  
  cout << "additional_option = " << additional_option << endl;
  if(electrons.size() != 2 ) return false;
  cout << "Pt 1 = " << cuts.at(0) << endl;
  cout << "Pt 2 = " << cuts.at(1) << endl;

  if(electrons.at(0).Pt() < cuts.at(0)) return false;
  if(electrons.at(1).Pt() < cuts.at(1)) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;

  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  if(mass < cuts.at(2)) return false;
  if(mass > cuts.at(3)) return false;
  if(fabs(mass-90.) < 10.) return false;

  if(jets.at(0).Pt() < cuts.at(9)) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;

  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }


  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > cuts.at(5)) return false;
  if(jj.M() < cuts.at(4)) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;

  if(eejj.M()  > cuts.at(7)) return false;
  if(eejj.M()  < cuts.at(6)) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e1jj.M() > cuts.at(13)) return false;
  if(e1jj.M() < cuts.at(12)) return false;

  snu::KParticle e2jj = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  
  if(cut_on_me2jj){
    if(e2jj.M() > cuts.at(11)) return false;
    if(e2jj.M() < cuts.at(10)) return false;
  }

  if(removeclosejet){
    if(HasCloseBJet( electrons.at(0)) ) return false;
    if(HasCloseBJet( electrons.at(1)) ) return false;
  }

  if(evmet > cuts.at(8)) return false;

  int nbjet=0;
  float btagcut= 0.;
  if(btagwp==0) btagcut = 0.244;
  if(btagwp==1) btagcut = 0.679;
  if(btagwp==2) btagcut = 0.898;

  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > btagcut) nbjet++;
  }

  if(nbjet > 0) return false;

  return true;

}

bool HNDiElectron::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 120.) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M() > 220.)return false;

  //if(eventbase->GetEvent().PFMET() > 30.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //if(nbjet > 0) return false;

  return true;
  
}

bool HNDiElectron::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 30.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(jets.at(0).Pt() < 30.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
	indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  
  //if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //if(nbjet > 0) return false;

  return true;
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  //  if(eventbase->GetEvent().PFMET() > 35.) return false;
  if(jets.at(0).Pt() < 40.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //  if(nbjet > 0) return false;

  return true;
}



void HNDiElectron::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() ==2  && jets.size() > 1) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){

	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.5){
	      FillHist(("closejet" + name + "_ptdiff").Data(), (jets.at(ijet).Pt() - electrons.at(iel).Pt()) /  jets.at(ijet).Pt(), weight, -1. , 1., 50);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet").Data(), 1, weight, 0., 2., 2);
	      else FillHist(("closejet" + name + "_bjet").Data(), 0, weight, 0., 2., 2);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet_nw").Data(), 1, 1., 0., 2., 2);
              else FillHist(("closejet" + name + "_bjet_nw").Data(), 0, 1., 0., 2., 2);
	      /// Jet usually vetoe
	      FillHist(("closejet/" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
	      
	    }
	    else{
	      FillHist(("awayjet/" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);

	    }
	  }
	}
      }
    }
  }
  return;
}


void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void HNDiElectron::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());
  if(!k_isdata)    fBTagSF = new BTagSFUtil("CSVM");

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  

  return;
  
}

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  if(!k_isdata) delete fBTagSF;

 }
     

void HNDiElectron::FillEventCutFlow(TString cut, float weight){

  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",19,0.,19.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"NoCut_w");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"EventCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(7,"eedR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(8,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(9,"SS_lepveto");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(10,"DiJet");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(11,"Presel");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(12,"Presel_noZ");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(13,"Presel_nobjet");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(14,"lowmass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(15,"lowmassCR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(16,"mediummass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(17,"mediummassCR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(18,"highmass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(19,"highmassCR");
  }
  
}

     
void HNDiElectron::FillCutFlow(TString cut, float weight){

  
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
     
     
void HNDiElectron::FillIsoCutFlow(TString cut, float weight){
       
  
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


void HNDiElectron::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiElectron::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiElectronCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiElectron::ClearOutputVectors() throw(LQError) {

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
