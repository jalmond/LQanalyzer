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
   MakeCleverHistograms(sighist, "Zmuons");
   MakeCleverHistograms(sighist, "Zmuons_jlv");
   MakeCleverHistograms(sighist, "Zmuons_jlv_60");
   MakeCleverHistograms(sighist, "Zelectrons");
   MakeCleverHistograms(sighist, "Zelectrons_jlv");
   MakeCleverHistograms(sighist, "Zelectrons_jlv_60");
   MakeCleverHistograms(sighist, "Sigmuons");
   MakeCleverHistograms(sighist, "Sigelectrons");

   return;
 }


 void ExampleAnalyzer::ExecuteEvents()throw( LQError ){

   m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
   m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

   if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   /// Trigger List (specific to muons channel)
   std::vector<TString> triggerslist;
   triggerslist.push_back("HLT_Mu17_TkMu8_v");
   m_logger << DEBUG << "Trigger = " << PassTrigger(triggerslist, prescale) << LQLogger::endmsg;
   //  if(!PassTrigger(triggerslist, prescale)) return;
   /// Correct MC for pileup
   if (MC_pu&&!k_isdata)  weight = weight*reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
   numberVertices = eventbase->GetEvent().nVertices();
   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

   //////////////////////////////////////////////////////
   //////////// Select objetcs
   //////////////////////////////////////////////////////   

   std::vector<snu::KMuon> muonColl;
   eventbase->GetMuonSel()->SetPt(20); 
   eventbase->GetMuonSel()->SetEta(2.4);
   eventbase->GetMuonSel()->SetRelIso(0.12);
   eventbase->GetMuonSel()->SetChiNdof(10); 
   eventbase->GetMuonSel()->SetBSdxy(0.01);
   eventbase->GetMuonSel()->SetBSdz(0.10);
   eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
   eventbase->GetMuonSel()->Selection(muonColl);

   std::vector<snu::KElectron> electronColl;
   eventbase->GetElectronSel()->SetPt(10);
   eventbase->GetElectronSel()->SetEta(2.4);
   eventbase->GetElectronSel()->SetRelIso(0.1);
   eventbase->GetElectronSel()->SetBSdxy(0.02);
   eventbase->GetElectronSel()->SetBSdz(0.10);
   eventbase->GetElectronSel()->Selection(electronColl);

   std::vector<snu::KJet> jetColl;
   std::vector<snu::KJet> jetColl_lepveto;
   std::vector<snu::KJet> jetColl_lepveto_60;
   eventbase->GetJetSel()->SetPt(30.);
   eventbase->GetJetSel()->SetEta(2.4);
   eventbase->GetJetSel()->Selection(jetColl);
   eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonColl, electronColl);
   eventbase->GetJetSel()->SetPt(60.);
   eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto_60, muonColl, electronColl);
   
   ///// SOME STANDARD PLOTS /////
   ////  Z-> mumu            //////

   if (muonColl.size() == 2) {                   
    snu::KParticle Z = muonColl.at(0) + muonColl.at(1);
    if(muonColl.at(0).Charge() != muonColl.at(1).Charge()){      
      FillHist("zpeak_mumu", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(sighist, "Zmuons", eventbase->GetEvent(), muonColl,electronColl,jetColl, weight);
      FillCLHist(sighist, "Zmuons_jlv", eventbase->GetEvent(), muonColl,electronColl,jetColl_lepveto, weight);
      FillCLHist(sighist, "Zmuons_jlv_60", eventbase->GetEvent(), muonColl,electronColl,jetColl_lepveto_60, weight);
    } 
    else{
      FillCLHist(sighist, "Sigmuons", eventbase->GetEvent(), muonColl,electronColl,jetColl, weight);
    }
  }
  

  ///// SOME STANDARD PLOTS /////
  ////  Z-> ee              //////
  if (electronColl.size() == 2) {      
    snu::KParticle Z = electronColl.at(0) + electronColl.at(1);
    if(electronColl.at(0).Charge() != electronColl.at(1).Charge()){      

      FillHist("zpeak_ee", Z.M(), weight);	 /// Plots Z peak
      FillCLHist(sighist, "Zelectrons", eventbase->GetEvent(), muonColl,electronColl,jetColl, weight);
      FillCLHist(sighist, "Zelectrons_jlv", eventbase->GetEvent(), muonColl,electronColl,jetColl_lepveto, weight);
      FillCLHist(sighist, "Zelectrons_jlv_60", eventbase->GetEvent(), muonColl,electronColl,jetColl_lepveto_60, weight);
    } 
    else {
      FillCLHist(sighist, "Sigelectrons", eventbase->GetEvent(), muonColl,electronColl,jetColl, weight);
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



