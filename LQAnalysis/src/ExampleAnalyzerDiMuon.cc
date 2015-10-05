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


   // To have the correct name in the log:                                                                                                                            
   SetLogName("ExampleAnalyzerDiMuon");

   Message("In ExampleAnalyzerDiMuon constructor", INFO);
   //
   // This function sets up Root files and histograms Needed in ExecuteEvents
   InitialiseAnalysis();
   MakeCleverHistograms(sighist_mm,"DiMuon");
   MakeCleverHistograms(sighist_mm,"SSMuon");
   MakeCleverHistograms(trilephist,"TriMuon");
   
 }


 void ExampleAnalyzerDiMuon::InitialiseAnalysis() throw( LQError ) {

   /// Initialise histograms
   MakeHistograms();  
   //
   // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
   // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
   //

    Message("Making clever hists for Z ->ll test code", INFO);

    return;
  }


void ExampleAnalyzerDiMuon::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
   FillCutFlow("NoCut", weight);
  
   ///#### CAT:::PassBasicEventCuts is updated: uses selections as described in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters: If you see this is out of date please comment
   
   if(!PassBasicEventCuts()) return;     /// Initial event cuts : 
   FillCutFlow("EventCut", weight);



   /// #### CAT::: triggers stored are all HLT_Ele/HLT_DoubleEle/HLT_Mu/HLT_TkMu

   std::vector<TString> triggerslist;
   triggerslist.push_back("HLT_IsoMu24_eta2p1_v");
   if(!PassTrigger(triggerslist, prescale)) return;
   FillCutFlow("TriggerCut", weight);

   /* // #### CAT::: trigger matching information is stored for muons and electrons for:
   ///HLT_IsoMu24_eta2p1_v
   ///HLT_Mu17_Mu8_DZ_v
   ///HLT_Mu17_TkMu8_DZ_v
   ///HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v
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

   /// List of preset muon collections
   std::vector<snu::KMuon> muonColl = GetMuons("NoCut");  /// No cuts applied
   std::vector<snu::KMuon> muonVetoColl = GetMuons("HNVeto");  // veto selection
   std::vector<snu::KMuon> muonLooseColl = GetMuons("HNLoose");  // loose selection
   std::vector<snu::KMuon> muonTightColl = GetMuons("HNTight"); // tight selection : NonPrompt MC lep removed
   

   for(std::vector<snu::KMuon>::iterator it = muonColl.begin(); it!= muonColl.end(); it++){
     //cout << "Muon pt = " << it->Pt() << endl;
     //cout << "Muon eta =" << it->Eta() << endl;
     //cout << "Muon match =" << it->TriggerMatched("HLT_IsoMu24_eta2p1") << endl;
   }
   
   
   /// List of preset jet collections
   std::vector<snu::KJet> jetColl             = GetJets("NoLeptonVeto"); // All jets
   std::vector<snu::KJet> jetColl_loose       = GetJets("Loose"); // pt > 10; eta < 5. ; PFlep veto
   std::vector<snu::KJet> jetColl_medium      = GetJets("Medium");// pt > 20 ; eta < 2.5; PFlep veto
   std::vector<snu::KJet> jetColl_hn          = GetJets("HNJets");// pt > 20 ; eta < 2.5; PFlep veto; pileup ID

   std::vector<snu::KElectron> electronColl        = GetElectrons("POGTight");          

   if(jetColl_hn.size() < 2) return;

   
   
   numberVertices = eventbase->GetEvent().nVertices();   
   
   
   
   float pileup_reweight=(1.0);
   if (!k_isdata) {
     /// Currently this is done using on the fly method: waiting for official method
     //pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue())); //* MCweight;
     pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().nVertices())); //* MCweight;
     //weight *= pileup_reweight;
   }
   //cout << "MCweight = " << MCweight << endl;


   if (Zcandidate(muonTightColl, 20., true)){
     ////Make NVTX plotsfor reweighting
     
     if(isData) FillHist("Nvtx_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
     else  FillHist("Nvtx_mc",  eventbase->GetEvent().nVertices() ,weight*pileup_reweight, 0. , 50., 50);
   }
   
   if(muonTightColl.size() ==2) {
     
     /// Method of plotting single histogram
     FillHist("zpeak_mumu_noPUrw", GetZMass(muonTightColl), weight*pileup_reweight, 0., 200.,400);
     FillHist("zpeak_mumu", GetZMass(muonTightColl), weight, 0., 200.,400);
     
     /// Standard set of histograms for muons/jets/electrons.. with no corrections
     FillCLHist(sighist_mm, "DiMuon", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight*pileup_reweight);
     if(SameCharge(muonTightColl))    FillCLHist(sighist_mm, "SSMuon", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight*pileup_reweight);
   }

   if(muonLooseColl.size() == 3) {
     if(eventbase->GetEvent().NoHFMET() > 30){
       if(jetColl_hn.size() > 1) FillCLHist(trilephist, "TriMuon", eventbase->GetEvent(), muonLooseColl,electronColl,jetColl_hn, weight*pileup_reweight);
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
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");

  
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



