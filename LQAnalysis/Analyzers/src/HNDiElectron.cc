// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"

//Core includes
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

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist

   bool runall=false;
   if (runall){
     MakeCleverHistograms(sighist_ee, "TChannel");
     MakeCleverHistograms(sighist_ee, "SIGNAL");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL");
     MakeCleverHistograms(sighist_ee, "SIGNAL_4J");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_4J");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_CC");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_noZ");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_BB");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_EE");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_BB_noB");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_EE_noB");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_BB_B");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_EE_B");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_LowPt");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_1Jet");
     MakeCleverHistograms(sighist_ee, "SS_SIGNAL_Presel");
     MakeCleverHistograms(sighist_ee, "OS_SIGNAL");
     MakeCleverHistograms(trilephist,"TriElectron");
     
     MakeCleverHistograms(trilephist,"TriMuon");
     MakeCleverHistograms(trilephist,"TriMuon_mass");
     MakeCleverHistograms(trilephist,"TriMuon_dr");
     MakeCleverHistograms(trilephist,"TriMuon_dr_nw_ttt");
     MakeCleverHistograms(trilephist,"TriMuon_dr_nw_ttl");
     MakeCleverHistograms(trilephist,"TriMuon_dr_nw_tll");
     MakeCleverHistograms(trilephist,"TriMuon_dr_nw_lll");
     
     MakeCleverHistograms(trilephist,"TriMuon_dr_ttl");
     MakeCleverHistograms(trilephist,"TriMuon_dr_tll");
     MakeCleverHistograms(trilephist,"TriMuon_dr_lll");
     MakeCleverHistograms(trilephist,"TriMuon_pt_dr");
     MakeCleverHistograms(trilephist,"TriMuon_bjet");
     MakeCleverHistograms(trilephist,"TriMuon_nobjet");
     
     MakeCleverHistograms(sighist_ee, "LowMassRegion");
     MakeCleverHistograms(sighist_ee, "LowMassRegionCR");
     MakeCleverHistograms(sighist_ee, "MediumMassRegion");
     MakeCleverHistograms(sighist_ee, "MediumMassRegionCR");
     MakeCleverHistograms(sighist_ee, "HighMassRegion");
     MakeCleverHistograms(sighist_ee, "40MassRegion");
     MakeCleverHistograms(sighist_ee, "100MassRegion");
     MakeCleverHistograms(sighist_ee, "500MassRegion");
     MakeCleverHistograms(sighist_ee, "1500MassRegion");
   /// only available in v7-6-X branch and newer
   }
   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){
  

  cout << "------------------------" << endl;
  cout << "UserPileupWeight = " << mcdata_correction->UserPileupWeight(eventbase->GetEvent()) << endl;
  cout << "PileupWeightByPeriod = " << mcdata_correction->PileupWeightByPeriod(eventbase->GetEvent()) << endl;
  cout << "CatPileupWeight = " << mcdata_correction->CatPileupWeight(eventbase->GetEvent(),0) <<  endl;


  if(GetMuons("MUON_POG_TIGHT").size() == 1){
    cout << "pt = " << GetMuons("MUON_POG_TIGHT").at(0).Pt() << " eta = " << GetMuons("MUON_POG_TIGHT").at(0).Eta() << endl;
    cout << "MuonTrackingEffScaleFactor = " << mcdata_correction->MuonTrackingEffScaleFactor(GetMuons("MUON_POG_TIGHT")) << endl;
    cout << "MuonISOScaleFactor = " << mcdata_correction->MuonISOScaleFactor("MUON_POG_TIGHT", GetMuons("MUON_POG_TIGHT"), 0) << endl;
    cout << "MuonScaleFactor = " << mcdata_correction->MuonScaleFactor("MUON_POG_TIGHT",  GetMuons("MUON_POG_TIGHT"),0) << endl;
    cout << "TriggerScaleFactor  = " << mcdata_correction->TriggerScaleFactor(GetElectrons("ELECTRON_POG_TIGHT"),  GetMuons("MUON_POG_TIGHT"), "HLT_IsoMu24",0) << endl;

  }
  if(GetElectrons("ELECTRON_POG_TIGHT").size() == 1){
    cout << "pt = " << GetElectrons("ELECTRON_POG_TIGHT").at(0).Pt()  << " eta = " <<  GetElectrons("ELECTRON_POG_TIGHT").at(0).Eta() << endl;
    cout << "ElectronScaleFactor = " << mcdata_correction->ElectronScaleFactor("ELECTRON_POG_TIGHT",GetElectrons("ELECTRON_POG_TIGHT"), 0) << endl;
    cout << "ElectronRecoScaleFactor= " <<mcdata_correction->ElectronRecoScaleFactor(GetElectrons("ELECTRON_POG_TIGHT")) << endl;
  }
    
  return;

  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  if (GetElectrons("ELECTRON_HN_TIGHT").size() > 1){
    if((fabs(GetElectrons("ELECTRON_HN_TIGHT").at(0).SCEta()) < 1.5)){
      if(GetElectrons("ELECTRON_HN_TIGHT").at(0).dxy() > 0.0111 ){
	cout << "GetElectrons(ELECTRON_HN_TIGHT).at(0).dxy() = " << GetElectrons("ELECTRON_HN_TIGHT").at(0).dxy() << endl;
      }
      if(GetElectrons("ELECTRON_HN_TIGHT").at(0).PFRelIso(0.3) > 0.0354) {
	cout << "GetElectrons(ELECTRON_HN_TIGHT).at(0).PFRelIso = " << GetElectrons("ELECTRON_HN_TIGHT").at(1).PFRelIso(0.3)  << endl;
      }
    }
    else{
      if(GetElectrons("ELECTRON_HN_TIGHT").at(0).dxy() > 0.0351 ){
        cout << "GetElectrons(ELECTRON_HN_TIGHT).at(0).dxy() = " << GetElectrons("ELECTRON_HN_TIGHT").at(0).dxy() << endl;
      }

    }
  }
  
  return;

  ///// SIGNAL PLOTS
  FillHist("NoCut" , 1., MCweight,  0. , 2., 2);

  if(!isData)weight*= MCweight;
  
  //vector<snu::KTruth> eventbaseGetTruth();
  /*  if(SameCharge(GetMuons(BaseSelection::MUON_HN_VETO))){
    cout << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCMatched() << "  " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCMatched() << endl;
    cout << "Muon 1 " << endl;
    cout << "isCF = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCIsCF() << endl;
    cout << "is conv = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCIsFromConversion() << endl;
    cout << "is from tau = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCFromTau() << endl;
    cout << "is prompt = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCIsPrompt() << endl;
    cout << "matched pdgid = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MCMatchedPdgId() << endl;
    cout << "mother pdgid = " << GetMuons(BaseSelection::MUON_HN_VETO).at(0).MotherPdgId() << endl;
    cout << "--------------------------------- " << endl;
    cout << "Muon 2 " << endl;
    cout << "isCF = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCIsCF() << endl;
    cout << "is conv = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCIsFromConversion() << endl;
    cout << "is from tau = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCFromTau() << endl;
    cout << "is prompt = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCIsPrompt() << endl;
    cout << "matched pdgid = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MCMatchedPdgId() << endl;
    cout << "mother pdgid = " << GetMuons(BaseSelection::MUON_HN_VETO).at(1).MotherPdgId() << endl;
    cout << "--------------------------------- " << endl;
    cout << "--------------------------------- " << endl;

    }*/
  if(IsSignal()){
    //ListTriggersAvailable();
    vector<int> pt1;
    pt1.push_back(35);
    pt1.push_back(25);
    pt1.push_back(25);
    pt1.push_back(25);
    pt1.push_back(30);
    pt1.push_back(30);
    pt1.push_back(20);
    pt1.push_back(25);
    pt1.push_back(30);
    pt1.push_back(120);
    pt1.push_back(20);
    pt1.push_back(25);
    vector<int>pt2;
    pt2.push_back(35);
    pt2.push_back(25);
    pt2.push_back(10);
    pt2.push_back(10);
    pt2.push_back(10);
    pt2.push_back(15);
    pt2.push_back(15);
    pt2.push_back(10);
    pt2.push_back(10);
    pt2.push_back(10);
    pt2.push_back(15);
    pt2.push_back(15);


    std::vector<TString> lists_triggers;
    lists_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
    lists_triggers.push_back("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v");
    lists_triggers.push_back("HLT_Ele22_eta2p1_WPLoose_Gsf_v");
    lists_triggers.push_back("HLT_Ele23_WPLoose_Gsf_v");
    lists_triggers.push_back("HLT_Ele27_WPLoose_Gsf_v");
    lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
    lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
    lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200");
    lists_triggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
    lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v1");
    for(unsigned int i=0; i < lists_triggers.size(); i++){
      FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator_nojet", lists_triggers );
    }
    if(GetJets("JET_HN").size() > 1){
      for(unsigned int i=0; i < lists_triggers.size(); i++){
	TString trig=lists_triggers.at(i);
	FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator", lists_triggers );
	if(PassTrigger(trig))  {
	  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator",lists_triggers );
	  
	  if(GetElectrons("ELECTRON_POG_TIGHT").size() ==2) {
	    
	    FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon",lists_triggers );
	    if(GetElectrons("ELECTRON_POG_TIGHT").at(0).Pt() > pt1.at(i) && GetElectrons("ELECTRON_POG_TIGHT").at(1).Pt() > pt2.at(i))  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt",lists_triggers );
	  }
	}
      }
    }
  }
  
  
  /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
  /// The string cut must match a bin label in FillCutFlow function
  FillHist("GenWeight" , 1., MCweight,  0. , 2., 2);
  
  if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  
  //if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  TString analysis_trigger="HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v";
  /// Trigger List (unprescaled)
  std::vector<TString> triggerslist;
  triggerslist.push_back(analysis_trigger);

  std::vector<snu::KMuon> muonColl = GetMuons("MUON_HN_VETO"); // loose selection                                                                                                                                                                              
  
  if(muonColl.size() == 3){
    if(muonColl.at(0).Pt() > 20){
      if(muonColl.at(1).Pt() > 10){
        if(muonColl.at(2).Pt() > 10){
	  
	  FillCLHist(trilephist, "TriMuon", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);

	  bool pass_cut1(true);
          bool pass_cut2(true);
          for(std::vector<snu::KMuon>::iterator it = muonColl.begin(); it != muonColl.end(); it++){
            for(std::vector<snu::KMuon>::iterator it2 = it+1; it2 != muonColl.end(); it2++){
              if(it->Charge() != it2->Charge()){
                if(it->DeltaR(*it2) < 0.5)  pass_cut1 = false;
                float mass_dilep = (*it+*it2).M();
                if(fabs(mass_dilep - 90.) < 10.)  pass_cut2 = false;

              }
            }
          }
          if(pass_cut2){
            FillCLHist(trilephist, "TriMuon_mass", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);
            if(pass_cut1)          {
              FillCLHist(trilephist, "TriMuon_dr", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);

              if(muonColl.at(2).Pt() > 15)            FillCLHist(trilephist, "TriMuon_pt_dr", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);
              if(NBJet(GetJets("JET_HN")) == 0){
                FillCLHist(trilephist, "TriMuon_nobjet", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);
              }
              if(NBJet(GetJets("JET_HN"))> 1) FillCLHist(trilephist, "TriMuon_bjet", eventbase->GetEvent(), muonColl, GetElectrons("ELECTRON_HN_VETO"),GetJets("JET_HN"), weight);
            }
          }
        }
      }
    }
  }

  //if(!PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", GetElectrons("ELECTRON_HN_VETO"), prescale)) return;

  //return;
    //if(!PassTrigger(triggerslist, prescale)) return;
  

  if(PassTrigger(analysis_trigger)){
    FillCutFlow("TriggerCut", weight);
  }
  
  /// trigger_weight is for MC only: retruns 1 if data.
  /// Checks the luminosity of the trigger and returns weight that applied to 'weight' will correct for difference in luinosity of json file used in data
  float trigger_ps_weight= WeightByTrigger(analysis_trigger, TargetLumi);

  FillHist("PSWeight" , trigger_ps_weight, 1., 0. , 2., 200);

  
  if(PassTrigger(analysis_trigger)){
    FillCutFlow("TriggerWeight", weight);
  }

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillCutFlow("VertexCut", weight);


  /// Use the number of vertices in the event to check effect of pileup reweighting
  numberVertices = eventbase->GetEvent().nVertices();   
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////

  
  // Get loose muons for veto: Can call  POGSoft/POGLoose/POGMedium/POGTight/HNVeto/HNLoose/HNMedium/HNTight
  //  std::vector<snu::KMuon> muonColl = GetMuons(BaseSelection::MUON_HN_VETO); // loose selection
  
  /// Get tight jets : Can call NoLeptonVeto/Loose/Medium/Tight/HNJets
  std::vector<snu::KJet> jetColl_hn  = GetJets("JET_HN");// pt > 20 ; eta < 2.5; PFlep veto; NO pileup ID
  std::vector<snu::KJet> jetColl_nlv  = GetJets("JET_NOLEPTONVETO");
  std::vector<snu::KJet> jetColl_loose  = GetJets("JET_HN");

  std::vector<snu::KJet> JET_HN_TChannel  = GetJets("JET_HN");

  FillHist("Njets", jetColl_hn.size() ,weight, 0. , 5., 5);

  

  TString elid = "ELECTRON_POG_TIGHT";
  if(k_running_nonprompt) elid="ELECTRON_HN_FAKELOOSE_NOD0";

  std::vector<snu::KElectron> electronColl             = GetElectrons(true, false,elid);
  
  float weight_trigger_sf =  mcdata_correction->TriggerScaleFactor(electronColl, muonColl, analysis_trigger);
  FillHist("TriggerSFWeight" , weight_trigger_sf, 1., 0. , 2., 200);
  
  // Sets weight to weight if not running chargeflip bkg estimate or events are S
  //if(k_running_chargeflip) weight              *= WeightCFEvent(electronColl, k_running_chargeflip);
  

  std::vector<snu::KElectron> electronHNVetoColl   = GetElectrons("ELECTRON_HN_VETO");
  
  

  /// Correct MC for pileup   
  
  float pileup_reweight (1.);
  if (!k_isdata) {
    /// use silver or gold
    pileup_reweight = eventbase->GetEvent().PileUpWeight();
  }
  FillHist("PileupWeight" , pileup_reweight, 1.,  0. , 2., 200);
  
  float id_weight=1.;
  float reco_weight=1.;
  
  if(!isData){
    for(unsigned int iel=0; iel < electronColl.size(); iel++){
      id_weight*= mcdata_correction->ElectronScaleFactor("ELECTRON_POG_TIGHT", electronColl);
      
    }
  }
  FillHist("IDWeight" ,  id_weight,1.,  0. , 2., 200);
  FillHist("RecoWeight" ,  reco_weight, 1., 0. , 2., 200);

  if(!isData && !k_running_nonprompt){
    weight*= id_weight;
    weight*=reco_weight;
    weight*=pileup_reweight;
    weight*=trigger_ps_weight;
  }

  if(muonColl.size() > 0) return;
  if(electronHNVetoColl.size() > 2) return;



  if(k_running_nonprompt){
    weight=1.; /// In case... should not be needed
    weight      *=  m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electronColl,"ELECTRON_POG_TIGHT", "dijet");
  } 

  int nbjet = NBJet(jetColl_hn, snu::KJet::CSVv2, snu::KJet::Medium);
  float event_met = eventbase->GetEvent().PFMET();

  if(electronColl.size() == 2 ) {
   
    if(electronColl.at(0).Pt() > 20. && electronColl.at(1).Pt() > 15. ){
      
      FillCLHist(sighist_ee, "SIGNAL", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
      
      if(jetColl_loose.size() > 3 ) {
	FillCLHist(sighist_ee, "SIGNAL_4J", eventbase->GetEvent(), muonColl,electronColl,jetColl_loose, weight);
      } 
      


      if(SameCharge(electronColl))  {
	FillCLHist(sighist_ee, "SS_SIGNAL", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	if(electronColl.at(0).GsfCtfScPixChargeConsistency() && electronColl.at(1).GsfCtfScPixChargeConsistency()){
	  if(electronColl.at(0).PassesConvVeto() && electronColl.at(1).PassesConvVeto()){
	    FillCLHist(sighist_ee, "SS_SIGNAL_CC", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	    if(!Zcandidate(electronColl, 20., false)){

	      if(jetColl_loose.size() > 3 ) {
		bool has_forward_jet(false), has_back_jet(false);
		for(unsigned int ij = 0 ; ij < jetColl_loose.size(); ij++){
		  if(jetColl_loose.at(ij).Eta() > 2.5) has_forward_jet=true;
		  if(jetColl_loose.at(ij).Eta() < -2.5) has_back_jet=true;
		}
		if(has_forward_jet && has_back_jet)
		  FillCLHist(sighist_ee, "SS_SIGNAL_4J", eventbase->GetEvent(), muonColl,electronColl,jetColl_loose, weight);
	      }
	      
	      FillCLHist(sighist_ee, "SS_SIGNAL_noZ", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);

	      if(electronColl.at(1).Pt() < 20.)  FillCLHist(sighist_ee, "SS_SIGNAL_LowPt", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);

	      if(electronColl.at(0).IsEBFiducial()   && electronColl.at(1).IsEBFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_BB", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	      if(electronColl.at(0).IsEEFiducial() && electronColl.at(1).IsEEFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_EE", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	      
	      if(jetColl_hn.size() == 1 && (GetDiLepMass(electronColl) > 100. )) FillCLHist(sighist_ee, "SS_SIGNAL_1Jet", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	      if(jetColl_hn.size() > 1 ) FillCLHist(sighist_ee, "SS_SIGNAL_Presel", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	      
	      if(jetColl_hn.size() > 3 ) {
		bool has_forward_jet(false), has_back_jet(false);
		for(unsigned int ij = 0 ; ij < jetColl_hn.size(); ij++){
		  if(jetColl_hn.at(ij).Eta() > 1.5) has_forward_jet=true;
		  if(jetColl_hn.at(ij).Eta() < -1.5) has_back_jet=true;
		  cout << "Passes selection ll jjjj " << endl;
		  for(unsigned int ij1=0; ij1 < jetColl_hn.size(); ij1++){
		    cout << jetColl_hn.at(ij1).Eta() << endl;
		  }
		}
		if(has_forward_jet && has_back_jet){
		  FillCLHist(sighist_ee, "TChannel", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
		  FillHist("SigTchannel" , 1., MCweight,  0. , 2., 2);
		}
		
	      }



	      if(NBJet(jetColl_hn, snu::KJet::CSVv2, snu::KJet::Medium) == 0){
		if(electronColl.at(0).IsEBFiducial()   && electronColl.at(1).IsEBFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_BB_noB", eventbase->GetEvent(),   muonColl,electronColl,jetColl_hn, weight);
		if(electronColl.at(0).IsEEFiducial() && electronColl.at(1).IsEEFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_EE_noB", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
	      }
	      else{
		if(electronColl.at(0).IsEBFiducial()   && electronColl.at(1).IsEBFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_BB_B", eventbase->GetEvent(),   muonColl,electronColl,jetColl_hn, weight);
                if(electronColl.at(0).IsEEFiducial() && electronColl.at(1).IsEEFiducial())       FillCLHist(sighist_ee, "SS_SIGNAL_EE_B", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
              }
	      
	      
	      if(LowMassCheckSignalRegion(electronColl, jetColl_hn, k_running_chargeflip) ) {
		if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 30.))){
		  FillCLHist(sighist_ee, "LowMassRegion", eventbase->GetEvent(), muonColl,   electronColl,jetColl_hn, weight);
		} 
		if ((nbjet!=0 && (eventbase->GetEvent().PFMET()  < 30.)) || ((nbjet == 0) && (eventbase->GetEvent().PFMET() > 50.))){
		  FillCLHist(sighist_ee, "LowMassRegionCR", eventbase->GetEvent(), muonColl,   electronColl,jetColl_hn, weight);
		  
		}
	      }
	      if(MidMassCheckSignalRegion(electronColl, jetColl_hn, k_running_chargeflip) ) {
                if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 30.))){
                  FillCLHist(sighist_ee, "MediumMassRegion", eventbase->GetEvent(), muonColl,   electronColl,jetColl_hn, weight);
                }
		if ((nbjet!=0 && (eventbase->GetEvent().PFMET()  < 30.)) || ((nbjet == 0) && (eventbase->GetEvent().PFMET() > 50.))){
                  FillCLHist(sighist_ee, "MediumMassRegionCR", eventbase->GetEvent(), muonColl,   electronColl,jetColl_hn, weight);
		}
	      } 
	      if(HighMassCheckSignalRegion(electronColl, jetColl_hn, k_running_chargeflip) ) {
		if((nbjet==0) && ( (eventbase->GetEvent().PFMET()  < 30.))){
                  FillCLHist(sighist_ee, "HighMassRegion", eventbase->GetEvent(), muonColl,   electronColl,jetColl_hn, weight);
                }
              }
	      
	        
	      std::vector<float> masscuts40;
	      masscuts40.push_back(20.);  masscuts40.push_back(15.);   /// pt1 / pt2
	      masscuts40.push_back(10.);  masscuts40.push_back(60.);   /// m(ee)
	      masscuts40.push_back(0.);   masscuts40.push_back(120.);  /// m(jj)
	      masscuts40.push_back(80.);  masscuts40.push_back(160.);  /// m(eejj)
	      masscuts40.push_back(30.);                               /// MET
	      masscuts40.push_back(20.);                               /// jet 1 pt
	      masscuts40.push_back(0.);  masscuts40.push_back(120.);  /// m(e2jj)

	      
	      std::vector<float> masscuts100;
	      masscuts100.push_back(20.);  masscuts100.push_back(15.);
	      masscuts100.push_back(15.);  masscuts100.push_back(10000.);
	      masscuts100.push_back(50.);  masscuts100.push_back(110.);
	      masscuts100.push_back(120.); masscuts100.push_back(10000.);
	      masscuts100.push_back(35.);
	      masscuts100.push_back(30.);
	      masscuts100.push_back(80.);  masscuts100.push_back(120.);


	      std::vector<float> masscuts500;
	      masscuts500.push_back(120);  masscuts500.push_back(40.);
	      masscuts500.push_back(15.);  masscuts500.push_back(10000.);
	      masscuts500.push_back(50.);  masscuts500.push_back(110.);
	      masscuts500.push_back(360.); masscuts500.push_back(10000.);
	      masscuts500.push_back(35.);
	      masscuts500.push_back(40.);
	      masscuts500.push_back(0.);  masscuts500.push_back(10000.);


	      std::vector<float> masscuts1500;
	      masscuts1500.push_back(120);  masscuts1500.push_back(40.);
	      masscuts1500.push_back(15.);  masscuts1500.push_back(10000.);
	      masscuts1500.push_back(50.);  masscuts1500.push_back(110.);
	      masscuts1500.push_back(360.); masscuts1500.push_back(10000.);
	      masscuts1500.push_back(35.);
	      masscuts1500.push_back(40.);
	      masscuts1500.push_back(0.);  masscuts1500.push_back(10000.);
	      
	      std::map<TString, std::vector<float> > sysymap;
	      sysymap["40"] =  masscuts40; 
	      sysymap["100"] =  masscuts100;
	      sysymap["500"] =  masscuts500;
	      sysymap["1500"] =  masscuts1500;
	      std::map<TString, TString > sysymap2;
	      sysymap2["_default"] = "default";



	      std::map< TString,  std::pair< std::vector<snu::KElectron> , float> > leptonmap;
	      leptonmap[""]  = make_pair(electronColl, weight);
  

	      for( std::map< TString,  std::pair< std::vector<snu::KElectron> , float> >::iterator lepmapit = leptonmap.begin(); lepmapit != leptonmap.end(); lepmapit++){
		for( std::map<TString, std::vector<float> >::iterator mapit = sysymap.begin(); mapit != sysymap.end(); mapit++){
		  for( std::map<TString, TString >::iterator mapit2 = sysymap2.begin(); mapit2 != sysymap2.end(); mapit2++){
		    TString label = lepmapit->first + mapit->first+ mapit2->first + "MassRegion_limithist";
		    TString jetlabel = "";
		    if(mapit->first.Contains("fg") && (mapit2->second != "default")) continue;

		    if(OptMassCheckSignalRegion(lepmapit->second.first, jetColl_hn,event_met, k_running_chargeflip , mapit->second, mapit2->second + jetlabel) ){
		      if(mapit2->second == "default"){
			if(!mapit->first.Contains("fg")){
			  FillCLHist(sighist_ee, (mapit->first + lepmapit->first+"MassRegion").Data(), eventbase->GetEvent(), muonColl,lepmapit->second.first,jetColl_hn, lepmapit->second.second);

			  
			}
		      }
		    }
		  }
		}
	      }

	      
	    }
	  }
	}
      }
      else     FillCLHist(sighist_ee, "OS_SIGNAL", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight);
    }
  }



    

  return;
}// End of execute event loop
  

void HNDiElectron::FillTriggerEfficiency(TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label)) {
    GetHist("TriggerEfficiency_"+label)->Fill(cut,weight);

  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label)->GetXaxis()->SetBinLabel(it+1,list.at(it));
    }
  }
  
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
  
  bool cut_on_ee=true;
  if(additional_option.Contains("noeeupper")) cut_on_ee= false;

  bool cut_on_eejj=true;
  if(additional_option.Contains("noeejjupper")) cut_on_eejj= false;

  bool cut_on_pt=true;
  if(additional_option.Contains("pt10")) cut_on_pt= false;

  
  int nbjet=0;
  snu::KJet::WORKING_POINT wp;
  if(btagwp==0) wp=snu::KJet::Loose;
  if(btagwp==1) wp=snu::KJet::Medium;
  if(btagwp==2) wp=snu::KJet::Tight;

  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).IsBTagged(snu::KJet::CSVv2, wp)) nbjet++;
  }

  if(additional_option.Contains("lowmass")) return (nbjet == 0 && (evmet < 30.) && LowMassCheckSignalRegion( electrons,  jets, runchargeflip));
  if(additional_option.Contains("midmass"))  return (nbjet == 0 && (evmet < 35.) && MidMassCheckSignalRegion( electrons,  jets, runchargeflip));
  if(additional_option.Contains("highmass")) return (nbjet == 0 && (evmet < 35.) && HighMassCheckSignalRegion( electrons,  jets, runchargeflip));
  

  if(additional_option.Contains("basic")){
    if(electrons.size() != 2) return false;
    if(electrons.at(0).Pt() < 20.) return false;
    if(electrons.at(1).Pt() < 15.) return false;
    if(jets.size() < 2) return false;
    if(jets.at(0).Pt() < cuts.at(9)) return false;
    if(!runchargeflip){
      if(!SameCharge(electrons)) return false;
    }
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
  
  if(electrons.size() != 2 ) return false;
  
  if(electrons.at(0).Pt() < cuts.at(0)) return false;
  if(!cut_on_pt){
    if(electrons.at(1).Pt() < 10.) return false;
  }
  else if(electrons.at(1).Pt() < cuts.at(1)) return false;
  
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  
  
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  
  if(mass < cuts.at(2)) return false;

  if(!cut_on_ee) {
    if(mass > 100000000.) return false;
  }
  else if(mass > cuts.at(3)) return false;
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

  if(!cut_on_eejj) {
    if(eejj.M()  > 200.) return false;
  }
  else  if(eejj.M()  > cuts.at(7)) return false;
  if(eejj.M()  < cuts.at(6)) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(e1jj.M() > cuts.at(13)) return false;
  //if(e1jj.M() < cuts.at(12)) return false;

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
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2);
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
  if(eejj.M() > 200.)return false;

  //if(eventbase->GetEvent().PFMET() > 30.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) nbjet++;
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
  if(ee.M()  < 15.) return false;
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
    if(jets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) nbjet++;
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
  if(ee.M()  < 15.) return false;
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
    if(jets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) nbjet++;
  }
  //  if(nbjet > 0) return false;

  return true;
}





void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

}


void HNDiElectron::BeginCycle() throw( LQError ){
  
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

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  
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



