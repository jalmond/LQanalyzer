// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzer.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzer);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ExampleAnalyzer::ExampleAnalyzer() :  AnalyzerCore(), out_muons(0), out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzer");

  Message("In ExampleAnalyzer constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void ExampleAnalyzer::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   MakeCleverHistograms(sighist, "Zmuons_jlv");
   MakeCleverHistograms(sighist, "Zelectrons_jlv");
   MakeCleverHistograms(sighist, "Sigmuons");
   MakeCleverHistograms(sighist, "Sigelectrons");

   return;
 }


 void ExampleAnalyzer::ExecuteEvents()throw( LQError ){

   m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
   m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
   FillCutFlow("NoCut", weight);
   if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   
   FillCutFlow("EventCut", weight);
      
   /// Trigger List (specific to muons channel)
   std::vector<TString> triggerslist;
   //triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
   triggerslist.push_back("HLT_Mu17_TkMu8_v");

   if(!PassTrigger(triggerslist, prescale)) return;

   FillCutFlow("TriggerCut", weight);
   /// Correct MC for pileup
   m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
   
   numberVertices = eventbase->GetEvent().nVertices();   

   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

   FillCutFlow("VertexCut", weight);

   FillHist("h_nvtx_norw_ee", numberVertices, weight, 0., 60.,60); 
   
   if (MC_pu&&!k_isdata) {
     /// Here is an alternative method to Fill a histogram. 
     /// The histogram with name "h_nvtx_norw"/"h_nvtx_rw" were not declared in the MakeHistogram code. 
     /// To avoid adding this by hand we can just use FillHist() function with 3 additional inputs i.e., xmin, xmax and nbinsx          
     weight = weight*reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
   }

   FillHist("h_nvtx_rw_ee",numberVertices,weight, 0., 60.,60 );
   
   //////////////////////////////////////////////////////
   //////////// Select objetcs
   //////////////////////////////////////////////////////   


   //// We will speicfy the following collection of objects
   /// 1) Tight Muons
   /// 2) Loose Muons
   /// 3) LooseButNOTight Muons
   /// 4) Loose Muons for veto
   /// 5) TightElectrons
   /// 6) Jets(with lepton veto)
   
   /// 1) Tight Muons       
   std::vector<snu::KMuon> muonTightColl;
   eventbase->GetMuonSel()->SetPt(20.); 
   eventbase->GetElectronSel()->SetID(BaseSelection::MUON_TIGHT);
   eventbase->GetMuonSel()->SetEta(2.4);
   eventbase->GetMuonSel()->SetRelIso(0.1);
   eventbase->GetMuonSel()->SetChiNdof(10.); 
   eventbase->GetMuonSel()->SetBSdxy(0.005);
   eventbase->GetMuonSel()->SetBSdz(0.10);
   eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
   eventbase->GetMuonSel()->Selection(muonTightColl);
   
   /// 2) Loose Muons  
   std::vector<snu::KMuon> muonLooseColl;
   eventbase->GetMuonSel()->SetPt(20.);
   eventbase->GetMuonSel()->SetEta(2.4);
   eventbase->GetMuonSel()->SetRelIso(0.40);
   eventbase->GetMuonSel()->SetChiNdof(50.);
   eventbase->GetMuonSel()->SetBSdxy(0.20);
   eventbase->GetMuonSel()->SetBSdz(0.10);
   eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
   eventbase->GetMuonSel()->Selection(muonLooseColl);
   
   
   /// 3) LooseButNOTight Muons      
   std::vector<snu::KMuon> muonLooseButNOTightColl;
   eventbase->GetMuonSel()->SetPt(20.);
   eventbase->GetMuonSel()->SetEta(2.4);
   eventbase->GetMuonSel()->SetRelIso(0.1, 0.4);
   eventbase->GetMuonSel()->SetChiNdof(10.,50.);
   eventbase->GetMuonSel()->SetBSdxy(0.005,0.20);
   eventbase->GetMuonSel()->SetBSdz(0.10);
   eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
   eventbase->GetMuonSel()->Selection(muonLooseButNOTightColl);
   
   /// 4) Loose Muons for veto
   std::vector<snu::KMuon> muonVetoColl;
   eventbase->GetMuonSel()->SetPt(10.);
   eventbase->GetMuonSel()->SetEta(2.4);
   eventbase->GetMuonSel()->SetRelIso(0.20);
   eventbase->GetMuonSel()->SetChiNdof(500.);
   eventbase->GetMuonSel()->SetBSdxy(2000.);
   eventbase->GetMuonSel()->SetBSdz(100.00);
   eventbase->GetMuonSel()->SetDeposits(400.0,600.0);
   eventbase->GetMuonSel()->Selection(muonVetoColl);
   
   /// 5) TightElectrons                                                                                                                                                     
   std::vector<snu::KElectron> electronTightColl;
   eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_MEDIUM);
   eventbase->GetElectronSel()->SetPt(25);
   eventbase->GetElectronSel()->SetEta(2.5);
   eventbase->GetElectronSel()->SetRelIso(0.15);
   eventbase->GetElectronSel()->SetBSdxy(0.02);
   eventbase->GetElectronSel()->SetBSdz(0.10);
   eventbase->GetElectronSel()->SetCheckCharge(true);
   eventbase->GetElectronSel()->SetApplyConvVeto(true);
   eventbase->GetElectronSel()->Selection(electronTightColl);

  
   /// 6) Jets(with lepton veto) 
   std::vector<snu::KJet> jetColl_lepveto;
   eventbase->GetJetSel()->SetPt(20.);
   eventbase->GetJetSel()->SetEta(2.5);
   eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonTightColl, electronTightColl);
   
   ///// SOME STANDARD PLOTS /////
   ////  Z-> mumu            //////

   if (muonTightColl.size() == 2) {                   
     snu::KParticle Z = muonTightColl.at(0) + muonTightColl.at(1);
     if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){      
       FillHist("zpeak_mumu", Z.M(), weight, 0., 200.,400);
       FillCLHist(sighist, "Zmuons_jlv", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
     } 
     else{
       FillCLHist(sighist, "Sigmuons", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
    }
   }
   
   
   


  ///// SOME STANDARD PLOTS /////
  ////  Z-> ee              //////
   if (electronTightColl.size() == 2) {      
     
     if(!isData){
       weight *=  ElectronScaleFactor(electronTightColl.at(0).Eta(), electronTightColl.at(0).Pt());
       weight *=  ElectronScaleFactor(electronTightColl.at(1).Eta(), electronTightColl.at(1).Pt());
     }
       
     snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
     if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge()){      
       FillHist("h_nvtx_rw_tight_ee",numberVertices,weight, 0., 60.,60 );
       FillCutFlow("DiEl_tight",weight);
       FillHist("zpeak_ee", Z.M(), weight, 0., 200.,400);      
       FillCLHist(sighist, "Zelectrons_jlv", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
     } 
     else {
       FillCLHist(sighist, "Sigelectrons", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
     }
  }
  
  return;
}// End of execute event loop
  


void ExampleAnalyzer::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void ExampleAnalyzer::BeginCycle() throw( LQError ){
  
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

ExampleAnalyzer::~ExampleAnalyzer() {
  
  Message("In ExampleAnalyzer Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzer::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 5,0.,5.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"DiEl_tight");
   
    
  }
}


void ExampleAnalyzer::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ExampleAnalyzer::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzer::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



