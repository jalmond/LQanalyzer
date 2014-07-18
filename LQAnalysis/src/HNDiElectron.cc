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
  
  MakeCleverHistograms(sighist,"NoCut");
  MakeCleverHistograms(sighist,"TriElCR");
  MakeCleverHistograms(sighist,"TriEl");
  MakeCleverHistograms(sighist,"TriEl_jetmva_inclusive");
  MakeCleverHistograms(sighist,"ZZ");
  MakeCleverHistograms(sighist,"OSee");
  MakeCleverHistograms(sighist,"SSloose");
  MakeCleverHistograms(sighist,"SSee");
  MakeCleverHistograms(sighist,"SSee_Z");
  MakeCleverHistograms(sighist,"SSee_0jet_Z");
  MakeCleverHistograms(sighist,"SSee_1jet_Z");
  MakeCleverHistograms(sighist,"SSee_gt0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet");
  MakeCleverHistograms(sighist,"SSee_DiJet");
  MakeCleverHistograms(sighist,"LowMassRegion");
  MakeCleverHistograms(sighist,"MediumMassRegion");
  MakeCleverHistograms(sighist,"SSee_noZ");
  MakeCleverHistograms(sighist,"SSee_0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet_noZ");
  MakeCleverHistograms(sighist,"HighMassRegion");
  MakeCleverHistograms(sighist,"LowMassRegion_mvajet");
  MakeCleverHistograms(sighist,"1JetCR");
  MakeCleverHistograms(sighist,"BJetCR");
  MakeCleverHistograms(sighist,"HighMETCR");
  MakeCleverHistograms(sighist,"SingleEl_CR");
  MakeCleverHistograms(sighist,"SingleEl_bjetCR");
  MakeCleverHistograms(sighist,"SingleElTight_CR");
  MakeCleverHistograms(sighist,"SingleElTight_bjetCR");
  MakeCleverHistograms(sighist,"SingleElLoose_CR");
  MakeCleverHistograms(sighist,"SingleElLoose_bjetCR");
  MakeCleverHistograms(sighist,"SingleEl_InclusiveCR");
  MakeCleverHistograms(sighist,"SingleEl_promptCR");
  MakeCleverHistograms(sighist,"SingleEl_promptbjetCR");
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
  
  FillEventCutFlow("NoCut", weight);

  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  //if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  //FillEventCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillEventCutFlow("VertexCut", weight);
  
  
  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// ELECTRONS
  std::vector<snu::KElectron> _electronAnalysisColl;
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronAnalysisColl);
  //if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelection(_electronAnalysisColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl, false);
  
  /// Get Prompt electrons/CF 
  std::vector<snu::KElectron> electronAnalysisColl_temp =  GetTruePrompt(_electronAnalysisColl, true, false); // removes CF and fake in mc
  std::vector<snu::KElectron> electronAnalysisColl =ShiftElectronEnergy(electronAnalysisColl_temp, k_running_chargeflip);
  
  
  /// Electrons used for veto (LOOSEST IN ANALYSIS)
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  
  std::vector<snu::KElectron> _electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronLooseColl, false);
  /// Loose electron sample (tight  - iso + looseiso) this removes fake el from jet/photon
  std::vector<snu::KElectron>  electronLooseColl = GetTruePrompt(_electronLooseColl, true, false);
  
  
  std::vector<snu::KElectron>  electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);

  
  if(SameCharge(electronNoCutColl)){

    if(!(electronNoCutColl.at(0).GetType()== 0 || electronNoCutColl.at(0).GetType()== 7 )) {
      if(electronNoCutColl.at(0).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()), weight  , 0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(0).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else {
      FillHist("W_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt())  ,weight  , 0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(0).dxy())  ,weight  ,0., 0.1, 100);
    }

    if(!(electronNoCutColl.at(1).GetType()== 0 || electronNoCutColl.at(1).GetType()==7 )) {
      if(electronNoCutColl.at(1).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else{
      FillHist("W_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
    }
  }



  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_lepveto_mva;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, muonNoCutColl, electronNoCutColl);
  // jetColl_lepveto have no pileup mva applied
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonVetoColl, electronLooseColl);
  /// Jets used in analysis
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto_mva, muonVetoColl, electronLooseColl);

  // TOP Control region os/SS
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }

  // Remove overlapping particles only need electron overlap in ee channel
  for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
    for(std::vector<snu::KElectron>::iterator it2 = it+1; it2 != electronLooseColl.end(); it2++){
      if(it->DeltaR(*it2) < 0.5) return;
    }
  }
  
  
  /// makes full set of plots for el/mu/jets/met with no cuts applied on objects 
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl, weight);
  
  /// Apply electron SFs for tight id
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }
  m_logger << DEBUG << "Analysis part: "<< LQLogger::endmsg;

      
  if(PassTrigger(triggerslist, prescale)){
    //// WZ/ZZ CR
    if(_electronAnalysisColl.size() ==  3 && (muonVetoColl.size()== 0)) {
      
      m_logger << DEBUG << "Number of jets in tri electron event = " << jetColl_lepveto_mva.size() << LQLogger::endmsg;
      
      float charge1 = _electronAnalysisColl.at(0).Charge();
      float charge2 = _electronAnalysisColl.at(1).Charge();
      float charge3 = _electronAnalysisColl.at(2).Charge();
      
      snu::KParticle osee;
      if(charge1 != charge2) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(1);
      if(charge1 != charge3) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(2);
      if(charge2 != charge3) osee= _electronAnalysisColl.at(1) + _electronAnalysisColl.at(2);
      
      if(jetColl_lepveto_mva.size() > 1){
	if(eventbase->GetEvent().PFMET() > 30){
	  if(fabs(osee.M() - 90.) < 10) FillCLHist(sighist, "TriElCR", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
      
      if(jetColl_lepveto_mva.size()!=0) FillCLHist(sighist, "TriEl_jetmva", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
      FillCLHist(sighist, "TriEl_jetmva_inclusive", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
      FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(_electronAnalysisColl.size() ==  4 && (muonVetoColl.size()== 0))FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
  }


  /// single lepton CR
  if(electronAnalysisColl.size() ==1){
    std::vector<TString> triggerslist17jet;
    triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");

    std::vector<TString> triggerslist8jet;
    triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
    
    bool pass_eljettrig= false;
    float prescale_trigger = 0.;
    if(electronAnalysisColl.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger = (24.18) / 19789 ; //// 20 + GeV bins
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger = (4.85) / 19789 ;
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    
    if(k_isdata) prescale_trigger=1.;

    bool Zveto=false;
    if(electronVetoColl.size() == 2) {
      if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
	snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
        if(Z.M() > 76. && Z.M() < 106.) Zveto=true;
      }
    }
    if(!Zveto && pass_eljettrig){
      Double_t MT=0;
      Double_t METdphi=0;
      for(unsigned int w = 0; w < electronAnalysisColl.size() ;  w++){
	METdphi = TVector2::Phi_mpi_pi(electronAnalysisColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
	MT = sqrt(2.* electronAnalysisColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
      }
      

      if(k_running_nonprompt){
	
	bool closebjet=false;
	bool closenoejet=false;
	bool closephjet=false;
	for(unsigned int ijet =0 ; ijet <jetColl.size() ; ijet++){
	  for(unsigned int iel=0 ; iel < electronAnalysisColl.size() ; iel++){

	    float dphi =fabs(TVector2::Phi_mpi_pi(electronAnalysisColl.at(iel).Phi()- jetColl.at(ijet).Phi()));
	    if( dphi < 0.4){
	      if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	    }
	    if( electronAnalysisColl[iel].DeltaR(jetColl.at(ijet)) < 0.4){
	      if(jetColl.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	      if(jetColl.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	    }
	  }
	}
	
	TString cut="";
	//if(!(closebjet || closenoejet || closephjet))cut = "noclose_40";
	//else cut = "close_40";
	if(!(closebjet || closenoejet || closephjet)){
	  if(nbjet ==0)cut = "noclose_20";
	  else cut ="noclose_bjet_20";
	  if(nbjet ==0) FillHist("numberclose_singleel",0 ,weight, 0.,3,.3);
	  else FillHist("numberclose_singleel",1 ,weight, 0.,3.,3);
	}
        else{
	  cut = "close_20";
	  FillHist("numberclose_singleel",2 ,weight, 0.,3.,3);
	}

	float ee_weight =  Get_DataDrivenWeight_E(electronAnalysisColl, jetColl_lepveto_mva, jetColl_lepveto_mva.size(),nbjet, eventbase->GetEvent().JetRho(),  0.01,0.09,0.09,true,false,true,cut);
	weight=ee_weight;
      }

      if(eventbase->GetEvent().PFMET() < 20.){
	if(jetColl_lepveto_mva.size() > 0){
	  FillCLHist(sighist, "SingleEl_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(nbjet > 0)  FillCLHist(sighist, "SingleEl_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho())) {
	    FillCLHist(sighist, "SingleElTight_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	    if(nbjet > 0)  FillCLHist(sighist, "SingleElTight_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	  else{
	    FillCLHist(sighist, "SingleElLoose_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
            if(nbjet > 0)  FillCLHist(sighist, "SingleElLoose_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	}/// NON INCLUSIVE JET
	FillCLHist(sighist, "SingleEl_InclusiveCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
      }/// LOW MET SCR

      if(eventbase->GetEvent().PFMET() > 30.){
	float dphiel = TVector2::Phi_mpi_pi(electronAnalysisColl.at(0).Phi()- eventbase->GetEvent().PFMETphi());
	float MTel = sqrt(2.* electronAnalysisColl.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphiel)));
	if((MTel < 100.) && (MTel  > 60.)){
	  FillCLHist(sighist, "SingleEl_promptCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(nbjet > 0)  FillCLHist(sighist, "SingleEl_promptbjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	}
      }
    }
  }

  if(!PassTrigger(triggerslist, prescale)) return;

  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale

  FillEventCutFlow("TriggerCut", weight);

  
  /// Require 2 analysis electrons (20/15) GeV
  if(electronAnalysisColl.size() != 2 ) return;
  if(electronAnalysisColl.at(0).Pt() < 20.) return;
  if(electronAnalysisColl.at(1).Pt() < 15.) return;

  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(ee.M()  < 10.) return;
  FillEventCutFlow("DiEl",weight);
  
  
  // TOP Control region os/SS    

  
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(electronAnalysisColl.size() ==2){
	if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  
  /// For CF use OS data and weight using CF rates from sunny
  if(k_running_chargeflip) {
    
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));

      weight *=  ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    else return;
  }// cf requirement
  else {
    if ((electronVetoColl.size() + muonVetoColl.size()) == 2){
      if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
  }
  


  
  ///// NOW OS event is weighted for CF sample

  FillEventCutFlow("SSDiEl",weight);
  
  FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
  FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);

  /// Remove events with 3 veto leptons
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;  
  if(muonVetoColl.size() !=0) return;
  
  if(muonTightColl.size() != 0) {
    cout << "Number of muons (tight = " << muonTightColl.size() << endl;
    cout << "Number of muons veto = " << muonVetoColl.size() << endl;
    cout << "Number of el veto = " << electronVetoColl.size() << endl;
    cout << "Number of el tight = " << electronAnalysisColl.size() << endl;
  }
  FillEventCutFlow("SS_lepveto",weight);
  
  FillCLHist(sighist, "SSloose", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  
  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt){
    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.09,true,false,true,"Loosedxy01_iso_b090_e090",nbjet, SumPt(jetColl_lepveto_mva));
        
    float ee_weight_08 = Get_DataDrivenWeight_r1_EE(electronAnalysisColl, jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.08,true,false,true,"Loosedxy01_iso_b090_e080", 0, false);
    float ee_weight_07 = Get_DataDrivenWeight_r1_EE(electronAnalysisColl, jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.07,true,false,true,"Loosedxy01_iso_b090_e070", 0, false);
    float ee_weight_06= Get_DataDrivenWeight_r1_EE(electronAnalysisColl, jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.06,true,false,true,"Loosedxy01_iso_b090_e060", 0, false);
    float ee_weight_05 = Get_DataDrivenWeight_r1_EE(electronAnalysisColl, jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.05,true,false,true,"Loosedxy01_iso_b090_e050", 0, false);

    weight*= ee_weight;
    if(SameCharge(electronAnalysisColl)){
      snu::KParticle ssee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
      FillHist("SSee_mass_09" ,ssee.M() , weight, 0., 200., 50);
      FillHist("SSee_mass_08" ,ssee.M() , ee_weight_08, 0., 200., 50);
      FillHist("SSee_mass_07" ,ssee.M() , ee_weight_07, 0., 200., 50);
      FillHist("SSee_mass_06" ,ssee.M() , ee_weight_06, 0., 200., 50);
      FillHist("SSee_mass_05" ,ssee.M() , ee_weight_05, 0., 200., 50);
      
    }/// END of NP bkg loop
    
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho())){
      FillCLHist(sighist, "SSloose_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
      FillCLHist(sighist, "SSloose_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho())){
      FillCLHist(sighist, "SSloose_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
      FillCLHist(sighist, "SSloose_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho())){
      FillCLHist(sighist, "SSloose_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
      FillCLHist(sighist, "SSloose_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho())){
      FillCLHist(sighist, "SSloose_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
      FillCLHist(sighist, "SSloose_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
    }

    
  }
  
  FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  else FillCLHist(sighist, "SSee_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

  if(jetColl_lepveto_mva.size() == 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_0jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  if(jetColl_lepveto_mva.size() == 1){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_1jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_1jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(jetColl_lepveto_mva.size() != 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_gt0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(jetColl_lepveto_mva.size() == 1) FillCLHist(sighist, "SSee_1jet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  if(jetColl_lepveto_mva.size() < 2) return;
  FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto, k_running_chargeflip) )FillCLHist(sighist, "LowMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) )FillCLHist(sighist, "MediumMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) )FillCLHist(sighist, "HighMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) )FillCLHist(sighist, "LowMassRegion_mvajet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "1JetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(jetColl_lepveto_mva.size() >= 1 && (nbjet!=0)) FillCLHist(sighist, "BJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(jetColl_lepveto_mva.size() >= 1 && (eventbase->GetEvent().PFMET() > 50.)) FillCLHist(sighist, "HighMETCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  
  
  bool no_emuoverlap= true;
  for(unsigned int i=0; i < electronAnalysisColl.size() ; i++){
    for(unsigned int j=0; j < muonTightColl.size() ; j++){
      float dR =  electronAnalysisColl[i].DeltaR(muonTightColl[j]);
      if(dR < 0.1) no_emuoverlap= false;
    }
  }
  
  
  
  return;
}// End of execute event loop

void HNDiElectron::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(electrons.size() != 2 ) return ;
  if(electrons.at(0).Pt() < 20.) return ;
  if(electrons.at(1).Pt() < 15.) return ;
  if(!SameCharge(electrons)) return ;
  if(jets.size() < 2) return ;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return ;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(eejj.M()  > 200.) return ;

  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return ;
  if(jj.M() < 40.) return ;

  if(ee.M() > 80.) return ;
  if(eventbase->GetEvent().PFMET() > 35.) return ;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return;

  if(name.Contains("iso_d0")) FillIsoCutFlow(name.Data(),w);
  else FillCutFlow(name.Data(),w);

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
  if(ee.M() > 80.) return false;
  
  
  snu::KParticle eej1 = electrons.at(0)+ jets.at(0) + jets.at(1) ; 
  if(eej1.M() > 160.) return false;
  
  snu::KParticle eej2 = electrons.at(1)+ jets.at(0) + jets.at(1) ; 
  if(eej2.M() > 120.) return false;;
  
  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ; 
  if(eejj.M()  > 200.) return false;
  
  
  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 100.) return false;
  if(jj.M() < 40.) return false;
  
  
  if(eventbase->GetEvent().PFSumET() < 200.) return false;;
  if(eventbase->GetEvent().PFSumET() > 1500.) return false;;
  
  //if(electrons.at(0).DeltaR(electrons.at(1)) < 0.6) return false;
  //if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;
  
  if(jets.at(0).DeltaR(jets.at(1)) > 3.5) return false;
  
  if(eventbase->GetEvent().PFMET() > 30.) return false;
  
  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));
  
  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > 50.) return false;
  if(MT2 > 50.) return false;
  
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

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
  if(ee.M()  < 15.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 300.) return false;;
  if(eventbase->GetEvent().PFSumET() > 2000.) return false;;


  snu::KParticle e2jj = electrons.at(1) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(e2jj.M() > 250.) return false;;
  
  
  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  if(electrons.at(0).DeltaR(electrons.at(1)) < 0.6) return false;
  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;

  if(jets.at(0).DeltaR(jets.at(1)) > 3.) return false;

  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));

  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > 100.) return false;
  if(MT2 > 100.) return false;

  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 50.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 400.) return false;;

  
  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  if(eventbase->GetEvent().PFMET() > 40.) return false;
  if(jets.at(0).DeltaR(jets.at(1)) > 2.5) return false;

  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



void HNDiElectron::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() == 2) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){


	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.4){
	      /// Jet usually vetoe
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);

	      
	    }
	    else{
	      FillHist(("awayjet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,   20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
              FillHist(("awayjet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);

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
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");
  
  
  
  return;
  
}

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     

void HNDiElectron::FillEventCutFlow(TString cut, float weight){


  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",6,0.,6.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"SS_lepveto");
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



