// $Id: ExampleAnalyzerDiMuon.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzerDiMuon Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzerDiMuon.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzerDiMuon);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
ExampleAnalyzerDiMuon::ExampleAnalyzerDiMuon() :  AnalyzerCore(), out_muons(0)  {
  
  rmcor = new rochcor2015();
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzerDiMuon");
  
  Message("In ExampleAnalyzerDiMuon constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  MakeCleverHistograms(sighist_mm,"DiMuon");
  MakeCleverHistograms(sighist_mm,"DiMuon_BJet");
  MakeCleverHistograms(sighist_mm,"SSMuon");
  MakeCleverHistograms(trilephist,"TriMuon");
  MakeCleverHistograms(trilephist,"TriMuon_noB");
  MakeCleverHistograms(trilephist,"TriMuon_nomet");
  MakeCleverHistograms(trilephist,"TriMuonEl");

}


void ExampleAnalyzerDiMuon::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  Message("Making clever hists for Z ->ll test code", INFO);
  
  /// only available in v7-6-X branch and newer
  //// default lumimask is silver ////
  //// In v7-6-2-(current) the default is changed to gold (since METNoHF bug)
  ///When METNoHF isfixed the default will be back to silver
  /// set to gold if you want to use gold json in analysis
  /// To set uncomment the line below:
  //ResetLumiMask(snu::KEvent::gold);


  return;
}


void ExampleAnalyzerDiMuon::ExecuteEvents()throw( LQError ){

  
  /// Apply the gen weight 
  if(!isData) weight*=MCweight;
  

  /// Acts on data to remove bad reconstructed event 
  if(isData&& (! eventbase->GetEvent().LumiMask(lumimask))) return;
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
  FillCutFlow("NoCut", weight);
  FillHist("GenWeight" , 1., MCweight,  0. , 2., 2);
  
  if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  
   ///#### CAT:::PassBasicEventCuts is updated: uses selections as described in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters: If you see this is out of date please comment
   
   if(!PassBasicEventCuts()) return;     /// Initial event cuts : 
   FillCutFlow("EventCut", weight);

   /// #### CAT::: triggers stored are all HLT_Ele/HLT_DoubleEle/HLT_Mu/HLT_TkMu/HLT_Photon/HLT_DoublePhoton

   std::vector<TString> triggerslist;
   triggerslist.push_back("HLT_IsoMu20_v2");
   if(PassTrigger(triggerslist, prescale))   FillHist("HLT_IsoMu20_v2", 1 , weight, 0. , 2., 2);

   std::vector<TString> triggerslist2;
   triggerslist2.push_back("HLT_IsoMu20_v3");
   if(PassTrigger(triggerslist2, prescale))   FillHist("HLT_IsoMu20_v3", 1 , weight, 0. , 2., 2);
   
  
   float trigger_ps_weight= ApplyPrescale("HLT_IsoMu20", TargetLumi,lumimask);
   
   if(!PassTrigger(triggerslist, prescale)) return;
   FillCutFlow("TriggerCut", weight);
   // Trigger matching is done using KMuon::TriggerMatched(TString) which returns a bool

   /* // #### CAT::: trigger matching information is stored for muons and electrons for:
   ///HLT_IsoMu24_eta2p1_v
   ///HLT_Mu17_Mu8_DZ_v
   ///HLT_Mu17_TkMu8_DZ_v
   ///HLT_IsoMu20
   ///HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v
   ///HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele12_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v
   ///HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_
   ///HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v
   ///HLT_Ele27_eta2p1_WPLoose_Gsf_TriCentralPFJet30_v
   */

   m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;


   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
   /// Has Good Primary vertex:
   /// if ( vtx.ndof() > 4 &&
   //   ( (maxAbsZ <=0 ) || std::abs(vtx.z()) <= 24 ) &&
   //( (maxd0 <=0 ) || std::abs(vtx.position().rho()) <= 2 ) &&
   //!(vtx.isFake() ) ){
   FillCutFlow("VertexCut", weight);
   

   /// List of preset muon collections : Can call also POGSoft/POGLoose/POGMedium/POGTight
   std::vector<snu::KMuon> muonColl = GetMuons(BaseSelection::MUON_NOCUT);  /// No cuts applied
   std::vector<snu::KMuon> muonVetoColl = GetMuons(BaseSelection::MUON_HN_VETO);  // veto selection
   std::vector<snu::KMuon> muonLooseColl = GetMuons(BaseSelection::MUON_HN_FAKELOOSE);  // loose selection
   std::vector<snu::KMuon> muonTightColl = GetMuons(BaseSelection::MUON_HN_TIGHT,false); // tight selection : NonPrompt MC lep removed
   
   CorrectMuonMomentum(muonTightColl);
   float muon_id_iso_sf= MuonScaleFactor(BaseSelection::MUON_POG_TIGHT, muonTightColl,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT

   
   /// List of preset jet collections : NoLeptonVeto/Loose/Medium/Tight/TightLepVeto/HNJets
   std::vector<snu::KJet> jetColl             = GetJets(BaseSelection::JET_NOLEPTONVETO); // All jets
   std::vector<snu::KJet> jetColl_loose       = GetJets(BaseSelection::JET_LOOSE); // pt > 10; eta < 5. ; PFlep veto
   std::vector<snu::KJet> jetColl_tight       = GetJets(BaseSelection::JET_TIGHT);// pt > 20 ; eta < 2.5; PFlep veto
   std::vector<snu::KJet> jetColl_hn          = GetJets(BaseSelection::JET_HN);// pt > 20 ; eta < 2.5; PFlep veto; pileup ID
   
   FillHist("Njets", jetColl_hn.size() ,weight, 0. , 5., 5);

   /// can call POGVeto/POGLoose/POGMedium/POGTight/ HNVeto/HNLoose/HNTight/NoCut/NoCutPtEta 
   std::vector<snu::KElectron> electronColl             = GetElectrons(BaseSelection::ELECTRON_POG_TIGHT);
   std::vector<snu::KElectron> electronLooseColl        = GetElectrons(BaseSelection::ELECTRON_POG_LOOSE);

   float weight_trigger_sf = TriggerScaleFactor(electronColl, muonTightColl, "HLT_IsoMu20");
   
   int njet = jetColl_hn.size();
   FillHist("GenWeight_NJet" , njet*MCweight + MCweight*0.1, 1., -6. , 6., 12);

   numberVertices = eventbase->GetEvent().nVertices();   
   
   float pileup_reweight=(1.0);
   if (!k_isdata) {
     // check if catversion is empty. i.ie, v-7-4-X in which case use reweight class to get weight. In v-7-6-X+ pileupweight is stored in KEvent class, for silver/gold json
     pileup_reweight = eventbase->GetEvent().PileUpWeight(lumimask);
     
   }
   
   FillHist("PileupWeight" ,  pileup_reweight,weight,  0. , 50., 10);

   
   if(!isData && !k_running_nonprompt){
     weight*=muon_id_iso_sf;
     weight*=pileup_reweight;
     weight*=weight_trigger_sf;
     weight*=trigger_ps_weight;
   }



   if (Zcandidate(muonTightColl, 20., true)){
     ////Make NVTX plotsfor reweighting
     
     if(isData) FillHist("Nvtx_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
     else  FillHist("Nvtx_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
   }
   
   if(muonTightColl.size() ==2) {
     if(muonTightColl.at(1).Pt() > 20.){
       FillCutFlow("DiMu_tight", weight);
       FillHist("Njets_dimuon", jetColl_hn.size() ,weight, 0. , 5., 5);
       
       /// Method of plotting single histogram
       FillHist("zpeak_mumu_noPUrw", GetDiLepMass(muonTightColl), weight, 0., 200.,400);
       FillHist("zpeak_mumu", GetDiLepMass(muonTightColl), weight, 0., 200.,400);
       
       
       /// Standard set of histograms for muons/jets/electrons.. with no corrections
       FillCLHist(sighist_mm, "DiMuon", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight);
       
       if(njet > 2 && NBJet(jetColl_hn) > 1)      FillCLHist(sighist_mm, "DiMuon_BJet", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight);
       
       if(SameCharge(muonTightColl))    FillCLHist(sighist_mm, "SSMuon", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight);
     }
   }

   if(muonLooseColl.size() == 3&&electronColl.size()==0) {
     if(muonLooseColl.at(2).Pt() > 25.){
       if( NBJet(jetColl_hn) == 0) FillCLHist(trilephist, "TriMuon_nomet", eventbase->GetEvent(), muonLooseColl,electronColl,jetColl_hn, weight);
       if(eventbase->GetEvent().PFMET() > 30){
	 FillCLHist(trilephist, "TriMuon", eventbase->GetEvent(), muonLooseColl,electronColl,jetColl_hn, weight);
	 if( NBJet(jetColl_hn) == 0) FillCLHist(trilephist, "TriMuon_noB", eventbase->GetEvent(), muonLooseColl,electronColl,jetColl_hn, weight);
       }
     }
   }
   if(muonLooseColl.size() == 2 && electronLooseColl.size() == 1){
     if(eventbase->GetEvent().PFMET() > 30){
       FillCLHist(trilephist, "TriMuonEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_hn, weight);
     }
   }
   
   return;
}// End of execute event loop
  


void ExampleAnalyzerDiMuon::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ExampleAnalyzerDiMuon::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "SNUCAT_Pileup.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

ExampleAnalyzerDiMuon::~ExampleAnalyzerDiMuon() {
  
  Message("In ExampleAnalyzerDiMuon Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzerDiMuon::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 5,0.,5.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"DiMu_tight");
   
    
  }
}


void ExampleAnalyzerDiMuon::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void ExampleAnalyzerDiMuon::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerDiMuonCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzerDiMuon::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



