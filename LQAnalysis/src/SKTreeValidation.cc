// $Id: SKTreeValidation.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQSKTreeValidation Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeValidation.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeValidation);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
SKTreeValidation::SKTreeValidation() :  AnalyzerCore(), out_muons(0)  {
  
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeValidation");
  
  Message("In SKTreeValidation constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

  if(0){
    std::vector<TString> dimuonIDs;
    //dimuonIDs.push_back("POGTight");
    dimuonIDs.push_back("POGTightroch_corrected");
    //dimuonIDs.push_back("HNTightroch_corrected");
    //dimuonIDs.push_back("POGTightroch_correctedtruthmatch");
    for(unsigned int i=0; i < dimuonIDs.size(); i++){
      MakeCleverHistograms(sighist_mm,"ZMuon"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"DiMuon"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"DiMuon_noW"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"DiMuon_IDW"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"DiMuon_puW"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"DiMuon_Trigger"+dimuonIDs.at(i));
      //MakeCleverHistograms(sighist_mm,"DiMuon_BB"+dimuonIDs.at(i));
      //MakeCleverHistograms(sighist_mm,"DiMuon_EE"+dimuonIDs.at(i));
      //MakeCleverHistograms(sighist_mm,"DiMuon_EB"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm, "DiMuon_dijet"+dimuonIDs.at(i));
      MakeCleverHistograms(sighist_mm, "DiMuon_SSPreselection"+dimuonIDs.at(i));
    }
    
    MakeCleverHistograms(muhist,"KMuonHists");
    MakeCleverHistograms(muhist,"KMuonHists_POGTIGHT");
    
    std::vector<TString> electronIDs;
    electronIDs.push_back("POGTight");
    electronIDs.push_back("POGTighttruthmatch");
    for(unsigned int i=0; i < electronIDs.size(); i++){
      MakeCleverHistograms(sighist_ee,"SingleElectron"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"SingleElectron_noW"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"SingleElectron_IDW"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"SingleElectron_puW"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"SingleElectron_Trigger"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"SingleElectron_Wregion"+electronIDs.at(i));
      MakeCleverHistograms(sighist_ee, "SingleElectron_dijet"+electronIDs.at(i));
    }
    
    std::vector<TString> dielectronIDs;
    dielectronIDs.push_back("POGTight");
    dielectronIDs.push_back("POGTighttruthmatch");
    
    for(unsigned int i=0; i < dielectronIDs.size(); i++){
      MakeCleverHistograms(sighist_ee,"ZElectron"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron_SSPreselection"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron_noW"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron_IDW"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron_puW"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee,"DiElectron_Trigger"+dielectronIDs.at(i));
      //MakeCleverHistograms(sighist_ee,"DiElectron_BB"+dielectronIDs.at(i));
      //MakeCleverHistograms(sighist_ee,"DiElectron_EE"+dielectronIDs.at(i));
      //MakeCleverHistograms(sighist_ee,"DiElectron_EB"+dielectronIDs.at(i));
      MakeCleverHistograms(sighist_ee, "DiElectron_dijet"+dielectronIDs.at(i));
    }
    MakeCleverHistograms(elhist,"KElectronHists");
    MakeCleverHistograms(elhist,"KElectronHists_POGTIGHT");
    
    std::vector<TString> muonIDs;
    muonIDs.push_back("POGTightroch_corrected");
    for(unsigned int i=0; i < muonIDs.size(); i++){
      MakeCleverHistograms(sighist_mm,"SingleMuon"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"SingleMuon_noW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"SingleMuon_IDW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"SingleMuon_puW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"SingleMuon_Trigger"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm,"SingleMuon_Wregion"+muonIDs.at(i));
      MakeCleverHistograms(sighist_mm, "SingleMuon_dijet"+muonIDs.at(i));
      
      MakeCleverHistograms(sighist_em,"EMuon"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em,"EMuon_noW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em,"EMuon_IDW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em,"EMuon_puW"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em,"EMuon_Trigger"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em, "EMuon_dijet"+muonIDs.at(i));
      MakeCleverHistograms(sighist_em,"EMuon_SSPreselection"+muonIDs.at(i));
      
    }
  }

}


void SKTreeValidation::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  Message("Making clever hists for Z ->ll test code", INFO);
  

  return;
}


void SKTreeValidation::ExecuteEvents()throw( LQError ){

  //ListTriggersAvailable();

  /// Apply the gen weight
  if(!isData) weight*=MCweight;
  /// Acts on data to remove bad reconstructed event 

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
  FillCutFlow("NoCut", weight);
  
  bool makePUFile=true;
  if(makePUFile){
    std::vector<snu::KMuon> muons = GetMuons(BaseSelection::MUON_POG_TIGHT);
    
    
    //if(PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", muons, prescale)){
    if(muons.size() ==2) {
      if(!SameCharge(muons)){
	if(muons.at(0).Pt() > 20. && muons.at(1).Pt() > 20.){
	  
	  if(GetDiLepMass(muons) < 120. && GetDiLepMass(muons)  > 60. ){
	      
	    if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 60., 60, "N_{vertex}");
	    else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 60., 60, "N_{vertex}");
	  }
	}
      }
    }
    return;
  }

  ///#### CAT:::PassBasicEventCuts is updated: uses selections as described in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters: If you <b>see this is out of date please comment


  
  if(!PassMETFilter()) return;     /// Initial event cuts : 
  FillCutFlow("EventCut", weight);
   
   /// #### CAT::: triggers stored are all HLT_Ele/HLT_DoubleEle/HLT_Mu/HLT_TkMu/HLT_Photon/HLT_DoublePhoton

  TString dimuon_trigmuon_trig1="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v";
  
  TString muon_trigmuon_trig1="HLT_IsoMu22_v";
  TString muon_trigmuon_trig2="HLT_IsoTkMu22_v";
  
  TString diel_trig="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
  
  TString em1_trig="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v";
  
  TString el_trig="HLT_Ele27_WPTight_Gsf_v";
  
  
  std::vector<TString> triggerslist_dimu;
  triggerslist_dimu.push_back(dimuon_trigmuon_trig1);
  
  std::vector<TString> triggerslist_mu;
  triggerslist_mu.push_back(muon_trigmuon_trig1);
  triggerslist_mu.push_back(muon_trigmuon_trig2);
  
  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back(diel_trig);
  
  std::vector<TString> triggerslist_el;
  triggerslist_el.push_back(el_trig);
  
  std::vector<TString> triggerslist_emu;
   triggerslist_emu.push_back(em1_trig);
   
   
   //   FillCutFlow("TriggerCut", weight);
   
   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

   FillCutFlow("VertexCut", weight);
   
   float pileup_reweight=(1.0);

   if (!k_isdata) {
     //pileup_reweight = TempPileupWeight();
     pileup_reweight= eventbase->GetEvent().PileUpWeight();
     FillHist("PUWeightvsNVertex",pileup_reweight, eventbase->GetEvent().nVertices(), weight, 0., 5., 500, 0., 60., 60, "N_{vertex}");
   }
   
   FillHist("PileupWeight" ,  pileup_reweight,weight,  0. , 50., 10, "pu weight");

   ///_______________________________________________________________________________________________________________________________________________________________________________________________________//
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   //// Electrons plots
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   MakeElectronValidationPlots(BaseSelection::ELECTRON_POG_TIGHT, weight, pileup_reweight,triggerslist_el, BaseSelection::MUON_POG_TIGHT,BaseSelection::JET_HN, "POGTight");
   //   MakeElectronValidationPlots(BaseSelection::ELECTRON_POG_TIGHT, weight, pileup_reweight,triggerslist_el, BaseSelection::MUON_POG_TIGHT,BaseSelection::JET_HN, "POGTighttruthmatch");
   FillCLHist(elhist,"KElectronHists", GetElectrons(BaseSelection::ELECTRON_NOCUT), weight);
   FillCLHist(elhist,"KElectronHists_POGTIGHT", GetElectrons(BaseSelection::ELECTRON_POG_TIGHT), weight);
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ///// DiElectron Validation plots
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   MakeDiElectronValidationPlots(BaseSelection::ELECTRON_POG_TIGHT, weight, pileup_reweight,triggerslist_diel, BaseSelection::MUON_POG_TIGHT,BaseSelection::JET_HN, "POGTight");
   //MakeDiElectronValidationPlots(BaseSelection::ELECTRON_POG_TIGHT, weight, pileup_reweight, triggerslist_diel, BaseSelection::MUON_POG_TIGHT,BaseSelection::JET_HN, "POGTighttruthmatch");
   ///_______________________________________________________________________________________________________________________________________________________________________________________________________//
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   /// Single Muon Validation plots
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   MakeMuonValidationPlots(BaseSelection::MUON_POG_TIGHT, weight, pileup_reweight,triggerslist_mu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "POGTightroch_corrected");
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   /// DiMuon Validation plots
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   //MakeDiMuonValidationPlots(BaseSelection::MUON_POG_TIGHT, weight, pileup_reweight,triggerslist_dimu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "POGTight");
   MakeDiMuonValidationPlots(BaseSelection::MUON_POG_TIGHT, weight, pileup_reweight, triggerslist_dimu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "POGTightroch_corrected");
   //MakeDiMuonValidationPlots(BaseSelection::MUON_POG_TIGHT, weight, pileup_reweight,triggerslist_dimu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "POGTightroch_correctedtruthmatch");
   //MakeDiMuonValidationPlots(BaseSelection::MUON_HN_TIGHT, weight, pileup_reweight, triggerslist_dimu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "HNTightroch_corrected");
   FillCLHist(muhist,"KMuonHists", GetMuons(BaseSelection::MUON_NOCUT), weight);
   FillCLHist(muhist,"KMuonHists_POGTIGHT", GetMuons(BaseSelection::MUON_POG_TIGHT), weight);
   ///_______________________________________________________________________________________________________________________________________________________________________________________________________//
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   // ElectronMuon Validation
   MakeElMuonValidationPlots(BaseSelection::MUON_POG_TIGHT, weight, pileup_reweight,triggerslist_emu, BaseSelection::ELECTRON_POG_TIGHT,BaseSelection::JET_HN, "POGTightroch_corrected");
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////!!!!!!////////
   ///_______________________________________________________________________________________________________________________________________________________________________________________________________//

   /*
   if(muonTightColl.size() == 2){
     bool pass=false;
     if(muonTightColl.at(0).MCTruthIndex() > 0  && muonTightColl.at(1).MCTruthIndex() > 0){
       if(eventbase->GetTruth().at(muonTightColl.at(0).MCTruthIndex()).ReadStatusFlag(2) == 0) pass=true;
       if(eventbase->GetTruth().at(muonTightColl.at(1).MCTruthIndex()).ReadStatusFlag(2) == 0) pass=true;
     }
     if(pass){
       //cout << "Z->mumu is not from hard process???? " << endl;
       //cout << "muonTightColl.at(0)/Pt/Eta/Phi = " << muonTightColl.at(0).Pt() << " " << muonTightColl.at(0).Eta() << " " << muonTightColl.at(0).Phi() << " conv = " << muonTightColl.at(0).MCIsFromConversion()<< endl;
       //cout << "muonTightColl.at(1)/Pt/Eta/Phi = " << muonTightColl.at(1).Pt() << " " << muonTightColl.at(1).Eta() << " " << muonTightColl.at(1).Phi() << " conv = " << muonTightColl.at(1).MCIsFromConversion()<< endl;
       for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
	 if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
	 if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;
	 if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 13 && eventbase->GetTruth().at(ig).GenStatus() == 1){
	   
	   int index_mum = ig;
	   
	   if(muonTightColl.at(0).MCMatched() &&muonTightColl.at(1).MCMatched()){
	     if(eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) == 0){
	       if(eventbase->GetTruth().at(eventbase->GetTruth().at(index_mum).IndexMother()).ReadStatusFlag(1) == 0) return;
	       if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(index_mum).IndexMother()).PdgId() ) == 15) return;
	       
	       cout << "Matched 000 " << endl;
	       
	       cout << "Macted 0 = " << muonTightColl.at(0).MCMatched() << endl;
	       cout << "Macted 1 = " << muonTightColl.at(1).MCMatched() << endl;
	       cout << eventbase->GetTruth().at(ig).PdgId() << " " << eventbase->GetTruth().at(ig).GenStatus() << " " << eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()<< " eta/pt/phi " << eventbase->GetTruth().at(ig).Eta() << "/" << eventbase->GetTruth().at(ig).Pt() << " " << eventbase->GetTruth().at(ig).Phi() <<  endl;
	       cout <<  "pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " status = " << eventbase->GetTruth().at(index_mum).GenStatus()  << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
	       cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
	       cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
	       cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
	       cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
	       cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
	       cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
	       cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
	       cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;

	       cout << "MOTHER" << endl;
	       while (fabs(eventbase->GetTruth().at(index_mum).PdgId()) == 13){
		 index_mum = eventbase->GetTruth().at(index_mum).IndexMother();
		 cout <<  "mother pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " status = " << eventbase->GetTruth().at(index_mum).GenStatus()  << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
		 cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
		 cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
		 cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
		 cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
		 cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
		 cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
		 cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
		 cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
	       }
	       for(unsigned int ig2=0; ig2 < eventbase->GetTruth().size(); ig2++){
		 if(eventbase->GetTruth().at(ig2).IndexMother() <= 0)continue;
		 if(eventbase->GetTruth().at(ig2).IndexMother() >= int(eventbase->GetTruth().size()))continue;
		 cout << eventbase->GetTruth().at(ig2).PdgId() << " status = " << eventbase->GetTruth().at(ig2).GenStatus()  << " eta = " << eventbase->GetTruth().at(ig2).Eta() << " phi = " << eventbase->GetTruth().at(ig2).Phi() << " pt = " << eventbase->GetTruth().at(ig2).Pt()<< " mother = " <<  eventbase->GetTruth().at(eventbase->GetTruth().at(ig2).IndexMother()).PdgId()<< " local " << eventbase->GetTruth().at(ig2).IndexMother()<<endl;
		 
	       }
	     }
	     if(eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) == 1) {
	       cout << "Matched and isdirecthadrondecayproduct " <<  endl;
	       cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
               cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
               cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
               cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
               cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
               cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
               cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
               cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
	       
	     }
	     if(eventbase->GetTruth().at(index_mum).StatusFlag() == 1){
	       if(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).StatusFlag() == 1){
		 cout << "Matchedand only isprompt " <<  endl;
		 cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
		 cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
		 cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
		 cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
		 cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
		 cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
		 cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
		 cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
		 

	       }	
	     }
	   }
	   if(eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) != 0)  return;
	   if(eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) != 0) return;
	   if(eventbase->GetTruth().at(index_mum).StatusFlag() == 1){
	     if(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).StatusFlag() == 1) return;
	   }

	   if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 15) continue;
	   cout << "Macted 0 = " << muonTightColl.at(0).MCMatched() << endl;
	   cout << "Macted 1 = " << muonTightColl.at(1).MCMatched() << endl;
	   cout << eventbase->GetTruth().at(ig).PdgId() << " " << eventbase->GetTruth().at(ig).GenStatus() << " " << eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()<< " eta/pt/phi " << eventbase->GetTruth().at(ig).Eta() << " " << eventbase->GetTruth().at(ig).Pt() << " " << eventbase->GetTruth().at(ig).Phi() <<  endl;
	   cout <<  "pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " status = " << eventbase->GetTruth().at(index_mum).GenStatus()  << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
	   cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
	   cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
	   cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
	   cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
	   cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
	   cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
	   cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
	   cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;

	   cout << "MOTHER" << endl;
	   while (fabs(eventbase->GetTruth().at(index_mum).PdgId()) == 13){
	     index_mum = eventbase->GetTruth().at(index_mum).IndexMother();
	     cout <<  "mother pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " status = " << eventbase->GetTruth().at(index_mum).GenStatus()  << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
	     cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
	     cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
	     cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
	     cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
	     cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
	     cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
	     cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
	     cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
	   }
	   cout << "\n" << endl;
	 }
       }
	   
     }
   }
   return;
   
   if(SameCharge(muonTightTruthMatchedColl)){
     if(muonTightTruthMatchedColl.at(0).MCIsFromConversion()) return;
     if(muonTightTruthMatchedColl.at(1).MCIsFromConversion()) return;

     
     //cout << "muonTightTruthMatchedColl.at(0)/Pt/Eta/Phi = " << muonTightTruthMatchedColl.at(0).Pt() << " " << muonTightTruthMatchedColl.at(0).Eta() << " " << muonTightTruthMatchedColl.at(0).Phi() << " conv = " << muonTightTruthMatchedColl.at(0).MCIsFromConversion()<< endl;
     //cout << "muonTightTruthMatchedColl.at(1)/Pt/Eta/Phi = " << muonTightTruthMatchedColl.at(1).Pt() << " " << muonTightTruthMatchedColl.at(1).Eta() << " " << muonTightTruthMatchedColl.at(1).Phi() << " conv = " << muonTightTruthMatchedColl.at(1).MCIsFromConversion()<< endl;
     
     for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
       if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
       if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;
       
       
       int index_mum = ig;
       while (fabs(eventbase->GetTruth().at(index_mum).PdgId()) == 13){
	 index_mum = eventbase->GetTruth().at(index_mum).IndexMother();
	 cout <<  "mother pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " status = " << eventbase->GetTruth().at(index_mum).GenStatus()  << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
	 cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
	 cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
	 cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
	 cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
	 cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
	 cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
	 cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
	 cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
       }
     }
   }


   if(muonTightTruthMatchedColl.size() == 1){
     cout << "muonTightTruthMatchedColl.at(0)/Pt/Eta/Phi = " << muonTightTruthMatchedColl.at(0).Pt() << " " << muonTightTruthMatchedColl.at(0).Eta() << " " << muonTightTruthMatchedColl.at(0).Phi() << endl;
     for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
       if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
       if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;

       if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 13 && eventbase->GetTruth().at(ig).GenStatus() == 1){
         cout << eventbase->GetTruth().at(ig).PdgId() << " " << eventbase->GetTruth().at(ig).GenStatus() << " " << eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()<< " eta/pt/phi " << eventbase->GetTruth().at(ig).Eta() << " " << eventbase->GetTruth().at(ig).Pt() << " " << eventbase->GetTruth().at(ig).Phi() <<  endl;

         int index_mum = ig;
         while (fabs(eventbase->GetTruth().at(index_mum).PdgId()) == 13){
           index_mum = eventbase->GetTruth().at(index_mum).IndexMother();
	   cout <<  "mother pdgid = " << eventbase->GetTruth().at(index_mum).PdgId() << " eta = " << eventbase->GetTruth().at(index_mum).Eta() << " phi = " << eventbase->GetTruth().at(index_mum).Phi() << " pt = " << eventbase->GetTruth().at(index_mum).Pt()<<  endl;
           cout << "StatusFlag : isprompt = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(7) << endl;
           cout << "StatusFlag : isdecayedleptonhadron = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(6) << endl;
           cout << "StatusFlag : istaudecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(5) << endl;
           cout << "StatusFlag : isprompttaudecayproduct = " <<   eventbase->GetTruth().at(index_mum).ReadStatusFlag(4) << endl;
           cout << "StatusFlag : isdirecthadrondecayproduct = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(3) << endl;
           cout << "StatusFlag : ishardprocess = " << eventbase->GetTruth().at(index_mum).ReadStatusFlag(2) << endl;
           cout << "StatusFlag : fromhardprocess = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(1) << endl;
           cout << "StatusFlag : fromhardprocess_beforeFSR = " <<  eventbase->GetTruth().at(index_mum).ReadStatusFlag(0) << endl;
         }
       }
     }
   }
   */
   
   return;
}// End of execute event loop
  


void SKTreeValidation::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void SKTreeValidation::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

SKTreeValidation::~SKTreeValidation() {
  
  Message("In SKTreeValidation Destructor" , INFO);
  
}



void SKTreeValidation::MakeMuonValidationPlots(BaseSelection::ID muid, float w, float pu_reweight, std::vector<TString> trignames,BaseSelection::ID elid, BaseSelection::ID jetid, TString tag){

  Message("In MakeMuonValidationPlots " , DEBUG);

  std::vector<snu::KElectron> electrons =  GetElectrons(elid);
  std::vector<snu::KJet> jets =  GetJets(jetid);


  std::vector<snu::KMuon> muons;

  if(k_running_nonprompt){
    muons = GetMuons(BaseSelection::MUON_HN_FAKELOOSE,false);
  }
  else if(tag.Contains("truthmatch"))   muons = GetMuons(muid,false);
  else   muons = GetMuons(muid);

  if(tag.Contains("roch"))   CorrectMuonMomentum(muons);

  float trig_pass= PassTrigger("HLT_IsoMu22", muons, prescale);
  //bool trig_pass= PassTrigger(trignames, prescale);


  /// List of all corrections to be applied
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);

  float ev_weight(1.);

  if(!isData){
    //trigger_sf = TriggerScaleFactor(electrons,muons, trignames.at(0));
    id_iso_sf =   MuonScaleFactor(muid, muons,0);
    id_iso_sf *= MuonISOScaleFactor(muid, muons,0);

    /// Apply weight to MC to scale to luminosity
    trigger_ps= WeightByTrigger(trignames, TargetLumi)  ;

    ev_weight = w * trigger_sf * id_iso_sf * pu_reweight*trigger_ps;
  }
  if(k_running_nonprompt){
    ev_weight=1.; /// In case... should not be needed
    if(muid == BaseSelection::MUON_POG_TIGHT){
      ev_weight      *=  Get_DataDrivenWeight_M(muons,"POGTIGHT");
    }
    if(muid == BaseSelection::MUON_HN_TIGHT){
      ev_weight      *=  Get_DataDrivenWeight_M(muons,"HNTIGHT");
    }
  }

  if (trig_pass > 0.)  w*= trig_pass;


  if(muons.size() ==1){
    if(muons.at(0).Pt() > 25. ){
      FillCLHist(sighist_mm, "SingleMuon"+tag, eventbase->GetEvent(), muons,electrons,jets, weight);
      if(trig_pass > 0. ){
	FillHist("nvertex_mu" + tag + "_nopurw", eventbase->GetEvent().nVertices(),  w*trigger_sf*trigger_ps, 0., 40.,40, "N_{vertex}");
        FillCLHist(sighist_mm, "SingleMuon_Trigger"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_sf*trigger_ps);
	FillHist("nvertex_mu" + tag + "_purw", eventbase->GetEvent().nVertices()  ,  w*trigger_sf*trigger_ps*pu_reweight, 0., 40.,40, "N_{vertex}") ;
	
	FillCLHist(sighist_mm, "SingleMuon_puW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_ps*trigger_sf);

	FillCLHist(sighist_mm, "SingleMuon_IDW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*id_iso_sf*trigger_ps*trigger_sf);


	float METdphi = TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet));
	float MT=(2.* muons.at(0).Et()*eventbase->GetEvent().MET(snu::KEvent::pfmet) * (1 - cos( METdphi)));
	
	if(MT > 40. && eventbase->GetEvent().MET(snu::KEvent::pfmet) > 30.) FillCLHist(sighist_mm, "SingleMuon_Wregion"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  
	if(jets.size() >= 2)          FillCLHist(sighist_mm, "SingleMuon_dijet"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
      }
    }
  }
}


void SKTreeValidation::MakeDiMuonValidationPlots(BaseSelection::ID muid, float w, float pu_reweight,  std::vector<TString> trignames,BaseSelection::ID elid, BaseSelection::ID jetid, TString tag){

  Message("In MakeDiMuonValidationPlots " , DEBUG);

  
  std::vector<snu::KElectron> electrons =  GetElectrons(elid);
  std::vector<snu::KJet> jets =  GetJets(jetid);

  std::vector<snu::KMuon> muons;

  if(k_running_nonprompt){
    muons = GetMuons(BaseSelection::MUON_HN_FAKELOOSE,false);
  }
  else if(tag.Contains("truthmatch"))   muons = GetMuons(muid,false);
  else   muons = GetMuons(muid);
  
  if(tag.Contains("roch"))   CorrectMuonMomentum(muons);
  
  // returns 1. if event passes trigger bit in data or Eff of trigger Eff(pt_muon) if in MC
  //float trig_pass= PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", muons, prescale);
  /// returns bool if event passes trigger bit
  bool trig_pass= PassTrigger(trignames, prescale);
  
  /// List of all corrections to be applied
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float ev_weight(1.);
  float puweight(1.);

  if(!isData){
    //trigger_sf = TriggerScaleFactor(electrons,muons, trignames.at(0));
    id_iso_sf =   MuonScaleFactor(muid, muons,0);
    id_iso_sf *= MuonISOScaleFactor(muid, muons,0);
    
    //puweight=eventbase->GetEvent().PileUpWeight();
    puweight=TempPileupWeight();
    
    /// scale to lumi of trigger
    trigger_ps= WeightByTrigger(trignames, TargetLumi)  ;
    
    ev_weight = w * trigger_sf * id_iso_sf *  pu_reweight*trigger_ps;
  }
  //cout << trigger_ps << " " << w << " " << trigger_sf << " " << id_iso_sf << " " << pu_reweight << " " << trig_pass << endl;
  if(k_running_nonprompt){
    ev_weight=1.; /// In case... should not be needed
    if(muid == BaseSelection::MUON_HN_TIGHT){
      ev_weight      *=  Get_DataDrivenWeight_MM(muons,"HNTIGHT");
    }
    if(muid == BaseSelection::MUON_POG_TIGHT){
      
      ev_weight      *=  Get_DataDrivenWeight_MM(muons,"POGTIGHT");
    }

  }

  //if (trig_pass > 0.)  w*= trig_pass;
  cout << "jets.size = " << jets.size() << endl;
  if(muons.size() ==2) {
    if(!SameCharge(muons)){
      if(muons.at(0).Pt() > 20. && muons.at(1).Pt() > 20.){
	
	/// Z peak plots
	if(GetDiLepMass(muons) < 120. && GetDiLepMass(muons)  > 60. ){
	  FillHist("zpeak_mumu_notrig" + tag + "_nopurw", GetDiLepMass(muons), w, 0., 200.,400);
          FillHist("zpeak_mumu_notrigscaled" + tag + "_nopurw", GetDiLepMass(muons), w*trigger_sf, 0., 200.,400);	  
	  if(trig_pass){
	    FillHist("zpeak_mumu" + tag + "_nopurw", GetDiLepMass(muons), w*id_iso_sf*trigger_sf, 0., 200.,400, "m_Z [GeV])");
	    FillHist("zpeak_mumu" + tag + "_purw", GetDiLepMass(muons),    w*id_iso_sf*trigger_sf*pu_reweight, 0., 200.,400, "m_Z [GeV])");
	    FillHist("nvertex_mumu" + tag + "_nopurw", eventbase->GetEvent().nVertices(),  w*id_iso_sf*trigger_sf, 0., 40.,40, "n_{vertex}");
	    FillHist("nvertex_mumu" + tag + "_purw", eventbase->GetEvent().nVertices()  , w*id_iso_sf*trigger_sf*pu_reweight, 0., 40.,40, "n_{vertex}") ;
	    FillCLHist(sighist_mm, "ZMuon"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  }
	}


	if(trig_pass){
	  FillCLHist(sighist_mm, "DiMuon"+tag, eventbase->GetEvent(), muons,electrons,jets, w);
	  FillCLHist(sighist_mm, "DiMuon_Trigger"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_sf*trigger_ps);
	  FillCLHist(sighist_mm, "DiMuon_puW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_sf*trigger_ps);
	  FillCLHist(sighist_mm, "DiMuon_IDW"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  
	  FillHistPerLumi("DiMuon_llmass"+tag,GetDiLepMass(muons), ev_weight, 0., 200.,20, 10);
	  FillHistPerLumi("DiMuon_njet"+tag,jets.size(), ev_weight, 0., 10.,10, 10);
	  FillHistPerLumi("DiMuon_met"+tag,eventbase->GetEvent().MET(snu::KEvent::pfmet), ev_weight, 0., 200.,20, 10);
	  

	  //if(EtaRegion("BB",muons))  FillCLHist(sighist_mm, "DiMuon_BB"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  //if(EtaRegion("EB",muons))  FillCLHist(sighist_mm, "DiMuon_EB"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  //if(EtaRegion("EE",muons))  FillCLHist(sighist_mm, "DiMuon_EE"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  
	  if(jets.size() >= 2)          FillCLHist(sighist_mm, "DiMuon_dijet"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	}
      }
    }
    else{
      if(muons.at(0).Pt() > 20. && muons.at(1).Pt() > 20.){

        /// Z peak plots
        if(GetDiLepMass(muons)  > 15. ){
          if(trig_pass){
	    if(jets.size() >= 2)          FillCLHist(sighist_mm, "DiMuon_SSPreselection"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	    
	  }
	}
      }
    }
  }
}

void SKTreeValidation::MakeElMuonValidationPlots(BaseSelection::ID muid, float w, float pu_reweight,  std::vector<TString> trignames,BaseSelection::ID elid, BaseSelection::ID jetid, TString tag){

  Message("In MakeElMuonValidationPlots " , DEBUG);

  std::vector<snu::KElectron> electrons ;
  std::vector<snu::KMuon> muons;
  if(k_running_nonprompt){
    muons = GetMuons(BaseSelection::MUON_HN_FAKELOOSE,false);
    electrons             = GetElectrons(true, false,BaseSelection::ELECTRON_HN_FAKELOOSE_NOD0);
  }
  else if(tag.Contains("truthmatch")) {
    muons = GetMuons(muid,false);
    electrons = GetElectrons(true, false,elid);
  }
  else {
    muons = GetMuons(muid);
    electrons = GetElectrons(elid);
  }

  if(tag.Contains("roch")){
    CorrectMuonMomentum(muons);
  }

  std::vector<snu::KJet> jets =  GetJets(jetid);

  /// List of all corrections to be applied
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float ev_weight(1.);

  if(!isData){
    //trigger_sf = TriggerScaleFactor(electrons,muons, trignames.at(0));
    id_iso_sf =  MuonScaleFactor(muid, muons,0);
    id_iso_sf *= MuonISOScaleFactor(muid, muons,0);
    id_iso_sf *= ElectronScaleFactor(elid, electrons,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT
    id_iso_sf *= ElectronRecoScaleFactor(electrons);


    /// Tiny effect on unprescaled triggers
    trigger_ps= WeightByTrigger(trignames, TargetLumi)  ;
    ev_weight = w * trigger_sf * id_iso_sf * trigger_ps* pu_reweight;
  }

  float trig_pass= PassTrigger("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v",muons,electrons, prescale);
  ev_weight*= trig_pass;
  //bool trig_pass= PassTrigger(trignames, prescale);

  if(k_running_nonprompt){
    ev_weight=1.; /// In case... should not be needed
    if(muid == BaseSelection::MUON_HN_TIGHT){
      ev_weight      *=  Get_DataDrivenWeight_EM(muons,electrons,"HNTIGHT");
    }
    if(muid == BaseSelection::MUON_POG_TIGHT){
      ev_weight      *=  Get_DataDrivenWeight_EM(muons,electrons,"POGTIGHT");
    }
  }

  if (trig_pass > 0.)  w*= trig_pass;

  if(muons.size() ==1 && electrons.size() ==1) {
    if(muons.at(0).Charge() != electrons.at(0).Charge()){
      if(muons.at(0).Pt() > 20. && electrons.at(0).Pt() > 20.){

	if(trig_pass > 0.){
	  FillCLHist(sighist_em, "EMuon_Trigger"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_sf*trigger_ps);
	  snu::KParticle Z = muons.at(0) + electrons.at(0);
          if(Z.M() > 15.){
	    
	    FillCLHist(sighist_em, "EMuon"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_sf*trigger_ps);
	    FillCLHist(sighist_em, "EMuon_puW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_sf*trigger_ps);
	    FillCLHist(sighist_em, "EMuon_IDW"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  }
	}
      }
    }
    else{
      if(muons.at(0).Pt() > 20. && electrons.at(0).Pt() > 20.){
	if(trig_pass> 0.){
          snu::KParticle Z = muons.at(0) + electrons.at(0);
          if(Z.M() > 15.){
	    if(jets.size() >= 2)          FillCLHist(sighist_em, "EMuon_SSPreselection"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  }
	}
      }
    }
  }

  }
  


void SKTreeValidation::MakeElectronValidationPlots(BaseSelection::ID elid, float w, float pu_reweight,  std::vector<TString> trignames,BaseSelection::ID muid, BaseSelection::ID jetid, TString tag){

  Message("In MakeElectronValidationPlots " , DEBUG);

  std::vector<snu::KElectron> electrons ;
  if(k_running_nonprompt){
    electrons             = GetElectrons(true, false,BaseSelection::ELECTRON_HN_FAKELOOSE_NOD0);
  }
  else if(tag.Contains("truthmatch"))   electrons = GetElectrons(true, false,elid);
  else   electrons =  GetElectrons(elid);


  std::vector<snu::KElectron> electronVetoColl   = GetElectrons(BaseSelection::ELECTRON_HN_VETO);

  std::vector<snu::KMuon> muons =  GetMuons(muid);
  std::vector<snu::KJet> jets =  GetJets(jetid);

  //  bool trig_pass= PassTrigger(trignames, prescale);
  float trig_pass= PassTrigger(trignames, prescale);
  
  /// List of all corrections to be applied
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float reco_weight=1.;
  
  float ev_weight(1.); 
  if(!isData){
    trigger_sf = TriggerScaleFactor(electrons,muons, trignames.at(0));
    id_iso_sf=   ElectronScaleFactor(elid, electrons,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT
    reco_weight = ElectronRecoScaleFactor(electrons);
    /// Tiny effect on unprescaled triggers
    trigger_ps= WeightByTrigger(trignames, TargetLumi)  ;
    ev_weight = w * trigger_sf * id_iso_sf * reco_weight * pu_reweight*trigger_ps*trig_pass;
  }
  if(k_running_nonprompt){
    ev_weight=1.; /// In case... should not be needed
    ev_weight      *=  Get_DataDrivenWeight_E(electrons);
  }

  if (trig_pass > 0.)  w*= trig_pass;

  if(electrons.size() ==1){
    if(electrons.at(0).Pt() > 30. ){
      FillCLHist(sighist_ee, "SingleElectron"+tag, eventbase->GetEvent(), muons,electrons,jets, weight);
      if(trig_pass> 0.){
	FillCLHist(sighist_ee, "SingleElectron_Trigger"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_ps*trigger_sf);
	FillHist("nvertex_el" + tag + "_nopurw", eventbase->GetEvent().nVertices(),  w*trigger_ps*trigger_sf, 0., 40.,40);
	FillHist("nvertex_el" + tag + "_purw", eventbase->GetEvent().nVertices()  , w*trigger_ps*trigger_sf*pu_reweight, 0., 40.,40) ;
	
	FillCLHist(sighist_ee, "SingleElectron_puW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_ps*trigger_sf);
	
	FillCLHist(sighist_ee, "SingleElectron_IDW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_ps*trigger_sf*id_iso_sf);
	
	float METdphi = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet));
        float MT=(2.* electrons.at(0).Et()*eventbase->GetEvent().MET(snu::KEvent::pfmet) * (1 - cos( METdphi)));
	if(MT > 40. && eventbase->GetEvent().MET(snu::KEvent::pfmet) > 30.) FillCLHist(sighist_ee, "SingleElectron_Wregion"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
        if(jets.size() >= 2)          FillCLHist(sighist_ee, "SingleElectron_dijet"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	
      }
    }
  }
}


void SKTreeValidation::MakeDiElectronValidationPlots(BaseSelection::ID elid, float w, float pu_reweight,  std::vector<TString> trignames,BaseSelection::ID muid, BaseSelection::ID jetid, TString tag){

  Message("In MakeDiElectronValidationPlots" , DEBUG);

  std::vector<snu::KElectron> electrons ;
  if(k_running_nonprompt){
    electrons             = GetElectrons(true, false,BaseSelection::ELECTRON_HN_FAKELOOSE_NOD0);
  }
  else if(tag.Contains("truthmatch"))   electrons = GetElectrons(true, false,elid);
  else   electrons =  GetElectrons(elid);
  
  std::vector<snu::KElectron> electronVetoColl   = GetElectrons(BaseSelection::ELECTRON_HN_VETO);
  
  std::vector<snu::KMuon> muons =  GetMuons(muid);
  std::vector<snu::KJet> jets =  GetJets(jetid);
  
  float trig_pass= PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", electrons,  prescale);
  //bool trig_pass= PassTrigger(trignames, prescale);
  /// List of all corrections to be applied
  float trigger_sf(1.);
  float id_iso_sf(1.);
  float trigger_ps(1.);
  float reco_weight=1.;

  float ev_weight(1.);
  if(!isData){
    //trigger_sf = TriggerScaleFactor(electrons,muons, trignames.at(0)); /// 
    id_iso_sf=   ElectronScaleFactor(elid, electrons,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT
    reco_weight = ElectronRecoScaleFactor(electrons);
    /// Tiny effect on unprescaled triggers
    trigger_ps= WeightByTrigger(trignames, TargetLumi)  ;
    ev_weight = w * trigger_sf * id_iso_sf * reco_weight * pu_reweight*trigger_ps*trig_pass;
  }
  if(k_running_nonprompt){
    ev_weight=1.; /// In case... should not be needed
    ev_weight      *=  Get_DataDrivenWeight_EE(electrons);
  }

  if(electrons.size() ==2) {
    if(!SameCharge(electrons)){
      if(electrons.at(0).Pt() > 20. && electrons.at(1).Pt() > 20.){

	w*= trig_pass;
        /// Z peak plots
        if(GetDiLepMass(electrons) < 120. && GetDiLepMass(electrons)  > 60. ){
          if(trig_pass> 0.){
            FillHist("zpeak_ee" + tag + "_nopurw", GetDiLepMass(electrons), w*id_iso_sf*trigger_sf, 0., 200.,400);
            FillHist("zpeak_ee" + tag + "_purw", GetDiLepMass(electrons),    w*id_iso_sf*trigger_sf*pu_reweight, 0., 200.,400);
            FillHist("nvertex_ee" + tag + "_nopurw", eventbase->GetEvent().nVertices(),  w*id_iso_sf*trigger_sf, 0., 40.,40);
            FillHist("nvertex_ee" + tag + "_purw", eventbase->GetEvent().nVertices()  , w*id_iso_sf*trigger_sf*pu_reweight, 0., 40.,40) ;
            FillCLHist(sighist_ee, "ZElectron"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
          }
        }

        if(trig_pass> 0.){
	  FillCLHist(sighist_ee, "DiElectron"+tag, eventbase->GetEvent(), muons,electrons,jets, w);
	  FillCLHist(sighist_ee, "DiElectron_Trigger"+tag, eventbase->GetEvent(), muons,electrons,jets, w*trigger_sf*trigger_ps);

	  FillCLHist(sighist_ee, "DiElectron_puW"+tag, eventbase->GetEvent(), muons,electrons,jets, w*pu_reweight*trigger_sf*trigger_ps);
	  FillCLHist(sighist_ee, "DiElectron_IDW"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);


          //if(EtaRegion("BB",electrons))  FillCLHist(sighist_ee, "DiElectron_BB"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
          //if(EtaRegion("EB",electrons))  FillCLHist(sighist_ee, "DiElectron_EB"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
          //if(EtaRegion("EE",electrons))  FillCLHist(sighist_ee, "DiElectron_EE"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  
          if(jets.size() >= 2)          FillCLHist(sighist_ee, "DiElectron_dijet"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	  
	  FillHistPerLumi("DiElectron_llmass"+tag,GetDiLepMass(electrons), ev_weight, 0., 200.,20, 10);
          FillHistPerLumi("DiElectron_njet"+tag,jets.size(), ev_weight, 0., 10.,10, 10);
          FillHistPerLumi("DiElectron_met"+tag,eventbase->GetEvent().MET(snu::KEvent::pfmet), ev_weight, 0., 200.,20, 10);
	}
      }
    }
    else{
      
      if(electrons.at(0).Pt() > 20. && electrons.at(1).Pt() > 20.){
	cout << "SS: " << tag << endl;
	if(GetDiLepMass(electrons)  > 15. ){
	  if(trig_pass> 0.){
	    cout << "SS trigger: " <<  tag << endl;
	    if(jets.size() >= 2)   FillCLHist(sighist_ee, "DiElectron_SSPreselection"+tag, eventbase->GetEvent(), muons,electrons,jets, ev_weight);
	    
	  }
	}
      }
    }
  }
}
  
void SKTreeValidation::BeginEvent( )throw( LQError ){
  
  Message("In BeginEvent() " , DEBUG);

  return;
}



void SKTreeValidation::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this SKTreeValidationCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void SKTreeValidation::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



