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
   

   if(!PassBasicEventCuts()) return;     /// Initial event cuts
   FillCutFlow("EventCut", weight);

   std::vector<TString> triggerslist;
   triggerslist.push_back("HLT_IsoMu24_eta2p1_v");
   if(!PassTrigger(triggerslist, prescale)) return;


   FillCutFlow("TriggerCut", weight);
   m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;


   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

   FillCutFlow("VertexCut", weight);


   std::vector<snu::KMuon> muonColl = GetMuons("NoCut");  /// No cuts applied
   std::vector<snu::KMuon> muonVetoColl = GetMuons("HNVeto");  // veto selection
   std::vector<snu::KMuon> muonLooseColl = GetMuons("HNLoose");  // loose selection
   std::vector<snu::KMuon> muonTightColl = GetMuons("HNTight"); // tight selection : NonPrompt MC lep removed
   

   for(std::vector<snu::KMuon>::iterator it = muonColl.begin(); it!= muonColl.end(); it++){
     //cout << "Muon pt = " << it->Pt() << endl;
     //cout << "Muon eta =" << it->Eta() << endl;
     //cout << "Muon match =" << it->TriggerMatched("HLT_IsoMu24_eta2p1") << endl;
   }
   

   std::vector<snu::KJet> jetColl             = GetJets("NoLeptonVeto"); // All jets
   std::vector<snu::KJet> jetColl_loose       = GetJets("Loose"); // pt > 10; eta < 5. ; PFlep veto
   std::vector<snu::KJet> jetColl_medium      = GetJets("Medium");// pt > 20 ; eta < 2.5; PFlep veto
   std::vector<snu::KJet> jetColl_hn          = GetJets("HNJets");// pt > 20 ; eta < 2.5; PFlep veto; pileup ID

   std::vector<snu::KElectron> electronColl        = GetElectrons("HNTight");          

   if(jetColl_hn.size() < 2) return;
   if(muonColl.size() !=2) return;
   

   numberVertices = eventbase->GetEvent().nVertices();   
   
   float pileup_reweight=(1.0);
   if (!k_isdata) {
     /// Here is an alternative method to Fill a histogram. 
     /// The histogram with name "h_nvtx_norw"/"h_nvtx_rw" were not declared in the MakeHistogram code. 
     /// To avoid adding this by hand we can just use FillHist() function with 3 additional inputs i.e., xmin, xmax and nbinsx          
     pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
   }
   
   
   if (muonTightColl.size() == 2) {                   
     snu::KParticle Z = muonTightColl.at(0) + muonTightColl.at(1);
     if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){      
       
       /// Method of plotting single histogram
       FillHist("zpeak_mumu", Z.M(), weight, 0., 200.,400);

       /// Standard set of histograms for muons/jets/electrons.. with no corrections
       FillCLHist(sighist, "DiMuon", eventbase->GetEvent(), muonTightColl,electronColl,jetColl_hn, weight);


     } /// OS muons
   }//// 2Muon (Tight) Loop
   
     
  return;
}// End of execute event loop
  


void ExampleAnalyzerDiMuon::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ExampleAnalyzerDiMuon::BeginCycle() throw( LQError ){
  
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



