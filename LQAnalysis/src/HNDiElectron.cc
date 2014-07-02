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
  if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  FillEventCutFlow("TriggerCut", weight);
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
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelection(_electronAnalysisColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl, false);

  /// Get Prompt electrons/CF
  std::vector<snu::KElectron> electronAnalysisColl =GetTruePrompt(_electronAnalysisColl, true); // removes CF and fake in mc
  
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  
  std::vector<snu::KElectron> _electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelection(_electronLooseColl, false);
  std::vector<snu::KElectron>  electronLooseColl = GetTruePrompt(_electronLooseColl, true);
  
  std::vector<snu::KElectron>  electronLooseColl2;
  std::vector<snu::KElectron>  electronLooseColl3;
  std::vector<snu::KElectron>  electronLooseColl4;
  
  for(unsigned int iel=0; iel< electronLooseColl.size() ; iel++){
    if(fabs(electronLooseColl.at(iel).dxy()) < 0.01 ) electronLooseColl2.push_back(electronLooseColl.at(iel));
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid = 0;
    if (fabs(electronLooseColl.at(iel).SCEta()) < 1.0) ifid = 0;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479) ifid = 1;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.0) ifid = 2;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.2) ifid = 3;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.3) ifid = 4;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.4) ifid = 5;
    else ifid = 6;

    float LeptonRelIsoDR03(0.);

    float ElectronIsoDR03 =  electronLooseColl.at(iel).PFChargedHadronIso03() + max( electronLooseColl.at(iel).PFNeutralHadronIso03() + electronLooseColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);
    if(electronLooseColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronLooseColl.at(iel).Pt();

    if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479 ){
      if(LeptonRelIsoDR03 < 0.09){
	electronLooseColl3.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.01 )         electronLooseColl4.push_back(electronLooseColl.at(iel));
      }
    }
    else{
      if(LeptonRelIsoDR03 < 0.07){
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.01 )         electronLooseColl4.push_back(electronLooseColl.at(iel));
	electronLooseColl3.push_back(electronLooseColl.at(iel));
      }
    }
  }

  std::vector<snu::KElectron>  electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
 
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);
  
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);

  

  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_lepveto_mva;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, muonNoCutColl, electronNoCutColl);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonVetoColl, electronLooseColl);
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto_mva, muonVetoColl, electronLooseColl);
  
  /// makes full set of plots for el/mu/jets/met with no cuts applied on objects 
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl, weight);
  
  /// Apply electron SFs for tight id
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }

  if ((electronVetoColl.size() + muonVetoColl.size()) != 2) return;
  
  if(Zcandidate(electronAnalysisColl, 10., false)) {
    if(!SameCharge(electronAnalysisColl))FillHist("Zcandidate_check", 0.,weight, 0.,10.,10);
    else FillHist("Zcandidate_check", 1.,weight, 0.,10.,10);
  }
  if(Zcandidate(electronLooseColl, 10., false)) {
    if(!SameCharge(electronLooseColl))FillHist("Zcandidate_check", 2.,weight, 0.,10.,10);
    else  FillHist("Zcandidate_check", 3.,weight, 0.,10.,10);
  }
  if(Zcandidate(electronLooseColl2, 10., false)) {
    if(!SameCharge(electronLooseColl2))FillHist("Zcandidate_check", 4.,weight, 0.,10.,10);
    else  FillHist("Zcandidate_check", 5.,weight, 0.,10.,10);
  }

  if(Zcandidate(electronLooseColl3, 10., false)) {
    if(!SameCharge(electronLooseColl3))FillHist("Zcandidate_check", 6.,weight, 0.,10.,10);
    else  FillHist("Zcandidate_check", 7.,weight, 0.,10.,10);
  }
  
  if(Zcandidate(electronLooseColl4, 10., false)) {
    if(!SameCharge(electronLooseColl4))FillHist("Zcandidate_check", 8.,weight, 0.,10.,10);
    else  FillHist("Zcandidate_check", 9.,weight, 0.,10.,10);
  }

  //// WZ/ZZ CR
  if(_electronAnalysisColl.size() ==  3 && (muonVetoColl.size()== 0)) {
    
    m_logger << DEBUG << "Number of jets in tri electron event = " << jetColl_lepveto.size() << LQLogger::endmsg;
    
    float charge1 = _electronAnalysisColl.at(0).Charge();
    float charge2 = _electronAnalysisColl.at(1).Charge();
    float charge3 = _electronAnalysisColl.at(2).Charge();
    
    snu::KParticle osee;
    if(charge1 != charge2) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(1);
    if(charge1 != charge3) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(2);
    if(charge2 != charge3) osee= _electronAnalysisColl.at(1) + _electronAnalysisColl.at(2);
    
    if(eventbase->GetEvent().PFMET() > 30){
      if(fabs(osee.M() - 90.) < 10) FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto, weight);
    }

    FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto, weight);
  }
  if(electronAnalysisColl.size() ==  4 && (muonVetoColl.size()== 0))FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto, weight);

  

  
  if(electronAnalysisColl.size() != 2 ) return;
  if(electronAnalysisColl.at(0).Pt() < 20.) return;
  if(electronAnalysisColl.at(1).Pt() < 15.) return;
  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(ee.M()  < 10.) return;
  FillEventCutFlow("DiEl",weight);
  
  
  // TOP Control region     
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto.size(); ij++){
    if(jetColl_lepveto.at(ij).BtagProb() > 0.679) nbjet++;
  }
  
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(muonTightColl.size() ==2){
	if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  
       
  if(k_running_chargeflip) {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));

      weight *=  ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }
    else return;
  }
  else {
    if ((electronVetoColl.size() + muonVetoColl.size()) == 2){
      if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
      
      if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
    }
  }
  
  if ((electronVetoColl.size() + muonVetoColl.size()) != 2) return;
  FillEventCutFlow("SSDiEl",weight);
  
  FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
  FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;  
  FillEventCutFlow("SS_lepveto",weight);
  
  FillCLHist(sighist, "SSloose", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto, weight);
  
  
  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt){
    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl_lepveto.size(), eventbase->GetEvent().JetRho());
    weight*= ee_weight;

    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()){
      if(jetColl_lepveto.size() == 0){
	if(Zcandidate(electronAnalysisColl, 5., false))  FillCLHist(sighist, "OSZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
	snu::KParticle eeloose = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
	bool Zloose=false;
	if(fabs(eeloose.M()- 90) < 5. ) Zloose=true;
	if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
	  if(Zloose)FillHist("Zos_loose_breakdown",1  , 1., 0.,4.,4);
	  else FillHist("NonZos_loose_breakdown",1  , 1., 0.,4.,4);
	}
	if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
	  if(Zloose)FillHist("Zos_loose_breakdown",2  , 1., 0.,4.,4);
	  else FillHist("NonZos_loose_breakdown",2  , 1., 0.,4.,4);
	}
	if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
	  if(Zloose)FillHist("Zos_loose_breakdown",3  , 1., 0.,4.,4);
	  else FillHist("NonZos_loose_breakdown",3  , 1., 0.,4.,4);
	}
	if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
	  if(Zloose)FillHist("Zos_loose_breakdown",4  , 1., 0.,4.,4);
	  else FillHist("NonZos_loose_breakdown",4  , 1., 0.,4.,4);
	}

      }  
    }
    if(electronAnalysisColl.size() == 2){
      snu::KParticle eeloose = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
      bool Zloose=false;
      if(fabs(eeloose.M()- 90) < 10. ) Zloose=true;
      if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
	if(Zloose)FillHist("Z_loose_breakdown",1  , 1., 0.,4.,4);
	else FillHist("NonZ_loose_breakdown",1  , 1., 0.,4.,4);
      }
      if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
        if(Zloose)FillHist("Z_loose_breakdown",2  , 1., 0.,4.,4);
	else FillHist("NonZ_loose_breakdown",2  , 1., 0.,4.,4);
      }
      if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
        if(Zloose)FillHist("Z_loose_breakdown",3  , 1., 0.,4.,4);
	else FillHist("NonZ_loose_breakdown",3  , 1., 0.,4.,4);
      }
      if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
        if(Zloose)FillHist("Z_loose_breakdown",4  , 1., 0.,4.,4);
	else FillHist("NonZ_loose_breakdown",4  , 1., 0.,4.,4);
      }
    }
  }
  
  FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(jetColl_lepveto.size() == 0){
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_0jet_loose_breakdown",0  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_0jet_TT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_0jet_loose_breakdown",1  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_0jet_TL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_0jet_loose_breakdown",2  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_0jet_LT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_0jet_loose_breakdown",3  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_0jet_LL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
  }
  
  if(jetColl_lepveto.size() == 1){
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_1jet_loose_breakdown",0  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_1jet_TT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }   
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_1jet_loose_breakdown",1  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_1jet_TL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }   
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_1jet_loose_breakdown",2  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_1jet_LT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_1jet_loose_breakdown",3  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_1jet_LL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
  }
  if(jetColl_lepveto.size() > 1){
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_2jet_loose_breakdown",0  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_2jet_TT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }   
    if(IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_2jet_loose_breakdown",1  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_2jet_TL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }   
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_2jet_loose_breakdown",2  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_2jet_LT", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
    if(!IsTight(electronAnalysisColl.at(0),  eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl.at(1),  eventbase->GetEvent().JetRho()) ){
      FillHist("SS_2jet_loose_breakdown",3  , 1., 0.,4.,4);
      FillCLHist(sighist, "SSee_2jet_LL", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    }
  }
  
  return;
  
  if(jetColl_lepveto.size() == 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    else FillCLHist(sighist, "SSee_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  }
  if(jetColl_lepveto.size() != 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_gt0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  }
  

  if(jetColl_lepveto.size() == 1) FillCLHist(sighist, "SSee_1jet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(jetColl_lepveto.size() < 2) return;
  FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto) )FillCLHist(sighist, "LowMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto) )FillCLHist(sighist, "MediumMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto) )FillCLHist(sighist, "HighMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva) )FillCLHist(sighist, "LowMassRegion_mvajet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  if(jetColl_lepveto.size() ==1) FillCLHist(sighist, "1JetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  if(jetColl_lepveto.size() >= 1 && (nbjet!=0)) FillCLHist(sighist, "BJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  if(jetColl_lepveto.size() >= 1 && (eventbase->GetEvent().PFMET() > 50.)) FillCLHist(sighist, "HighMETCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
  
  
  
  bool no_emuoverlap= true;
  for(int i=0; i < electronAnalysisColl.size() ; i++){
    for(int j=0; j < muonTightColl.size() ; j++){
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

  if(ee.M() > 80.) return ;
  if(eventbase->GetEvent().PFMET() > 35.) return ;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
  }
  if(nbjet > 0) return;

  if(name.Contains("iso_d0")) FillIsoCutFlow(name.Data(),w);
  else FillCutFlow(name.Data(),w);

}



bool HNDiElectron::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!SameCharge(electrons)) return false;
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(ee.M() > 80.) return false;
  
  
  snu::KParticle eej1 = electrons.at(0)+ jets.at(0) + jets.at(1) ; 
  if(eej1.M() > 160.) return false;
  if(eej1.M() < 40.) return false;;
  
  snu::KParticle eej2 = electrons.at(1)+ jets.at(0) + jets.at(1) ; 
  if(eej2.M() > 120.) return false;;
  if(eej2.M() < 50.) return false;;
  
  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ; 
  if(eejj.M()  > 180.) return false;
  if(eejj.M()  < 50.) return false;
  
  
  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 100.) return false;
  if(jj.M() < 40.) return false;
  
  
  if(eventbase->GetEvent().PFSumET() < 200.) return false;;
  if(eventbase->GetEvent().PFSumET() > 1500.) return false;;
  
  if(electrons.at(0).DeltaR(electrons.at(1)) < 0.6) return false;
  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;
  
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
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
  
}

bool HNDiElectron::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!SameCharge(electrons)) return false;
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
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 50.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!SameCharge(electrons)) return false;
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
    if(jets.at(ij).BtagProb() > 0.679) nbjet++;
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



