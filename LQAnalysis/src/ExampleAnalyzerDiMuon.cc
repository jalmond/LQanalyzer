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

  return;
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
   /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
   /// The string cut must match a bin label in FillCutFlow function
   FillCutFlow("NoCut", weight);
   

   std::vector<snu::KJet> jetColl             = GetJets("ApplyLeptonVeto");
   std::vector<snu::KMuon> muonNoCutColl = GetMuons("NoCut");

   if(jetColl.size() < 2) return;
   if(muonNoCutColl.size() !=2) return;
   
   float wmassjj=0.;
   int indexj1=0;
   int indexj2=0;
   for(unsigned int ij=0; ij < jetColl.size()-1; ij++){
     for(unsigned int ij2=ij+1; ij2 < jetColl.size(); ij2++){
       snu::KParticle jjtmp = jetColl.at(ij) + jetColl.at(ij2) ;
       if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	 wmassjj = fabs(jjtmp.M() - 80.4);
	 indexj1=ij;
	 indexj2=ij2;
       }
     }
   }

   float wmassjj_lm=0.;
   int indexj1_lm=0;
   int indexj2_lm=0;
   for(unsigned int ij=0; ij < jetColl.size()-1; ij++){
     for(unsigned int ij2=ij+1; ij2 < jetColl.size(); ij2++){
       snu::KParticle jjtmp = jetColl.at(ij) + jetColl.at(ij2) + muonNoCutColl.at(0)+ muonNoCutColl.at(1);
       if(fabs(jjtmp.M() - 80.4) < wmassjj) {
         wmassjj_lm = fabs(jjtmp.M() - 80.4);
         indexj1_lm=ij;
         indexj2_lm=ij2;
       }
     }
   }

   

   
   snu::KParticle N1 = muonNoCutColl.at(0) + jetColl.at(indexj1) + jetColl.at(indexj2); 
   snu::KParticle N2 = muonNoCutColl.at(1) + jetColl.at(indexj1) + jetColl.at(indexj2); 

   
   snu::KParticle N1_lm = muonNoCutColl.at(0) + jetColl.at(indexj1_lm) + jetColl.at(indexj2_lm);
   snu::KParticle N2_lm = muonNoCutColl.at(1) + jetColl.at(indexj1_lm) + jetColl.at(indexj2_lm);


   if( fabs(N1_lm.M() -50.) < fabs(N2_lm.M()-50.)) FillHist("NMass_50", N1.M(),1., 0.,1000.,1000);
   else FillHist("NMass_50", N2_lm.M(),1., 0.,1000.,5000);

   if( fabs(N1_lm.M() -60.) < fabs(N2_lm.M() -60.)) FillHist("NMass_60", N1.M(),1., 0.,1000.,1000);
   else FillHist("NMass_60", N2_lm.M(),1., 0.,1000.,5000);

   if( fabs(N1.M() -100.) < fabs(N2.M()-100.)) FillHist("NMass_100", N1.M(),1., 0.,1000.,1000);
   else FillHist("NMass_100", N2.M(),1., 0.,1000.,5000);

   if( fabs(N1.M() -300.) < fabs(N2.M() -300.)) FillHist("NMass_300", N1.M(),1., 0.,1000.,1000);
   else FillHist("NMass_300", N2.M(),1., 0.,1000.,5000);



   //low mass



   return;



   ///// Apply some general cuts on event to clean MET
   /// Taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
   /// These are applied in AnalyzerCore::PassBasicEventCuts
   if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   FillCutFlow("EventCut", weight);

   
   /// Trigger List (specific to muons channel)
   std::vector<TString> triggerslist;
   triggerslist.push_back("HLT_Mu17_TkMu8_v");
      
   if(!PassTrigger(triggerslist, prescale)) return;
   
   //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
   
   FillCutFlow("TriggerCut", weight);
   m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
   
   
   /// Check the event has a "Good" Primary vertex
   /// Good is taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TrackingPFGJob:
   /// defined as : !isFake && ndof > 4 && |z| <= 24 cm && position.Rho <= 2cm (rho = radius of vertex)
   /// Cut is coded in SKTreeFiller and stored in KEvent class as HasGoodPrimaryVertex()
   /// More info on primary vertex can be found https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideOfflinePrimaryVertexProduction (LQNtuples use offlinePrimaryVertices)
   // isFake is true if the vertex is based on the beam spot (as no reconstructed vertex is found

   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
   
   FillCutFlow("VertexCut", weight);
   
   /// Use the number of vertices in the event to check effect of pileup reweighting
   numberVertices = eventbase->GetEvent().nVertices();   
   
   float pileup_reweight=(1.0);
   if (!k_isdata) {
     /// Here is an alternative method to Fill a histogram. 
     /// The histogram with name "h_nvtx_norw"/"h_nvtx_rw" were not declared in the MakeHistogram code. 
     /// To avoid adding this by hand we can just use FillHist() function with 3 additional inputs i.e., xmin, xmax and nbinsx          
     pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
   }
   
   //////////////////////////////////////////////////////
   //////////// Select objetcs
   //////////////////////////////////////////////////////   


   /// 1) Tight Muons                       || eventbase->GetMuonSel()->HNTightMuonSelection
   /// 2) Loose Muons for veto              || eventbase->GetMuonSel()->HNVetoMuonSelection
   /// 3) TightElectrons (for jet veto)     || eventbase->GetElectronSel()->HNTightElectronSelection
   /// 4) Jets(with lepton veto)
   
   ///////////////////////////////////////////////////////////////////////////////////////////
   /// 1) Tight Muons       
   ///////////////////////////////////////////////////////////////////////////////////////////
   std::vector<snu::KMuon> muonTightColl;
   //eventbase->GetMuonSel()->SetPt(20.);
   /// ID are explained in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
   // eventbase->GetMuonSel()->SetID(BaseSelection::MUON_TIGHT);
      
   /// Standard cut of 2.4 which is the Muon Spectrometer coverage
   //eventbase->GetMuonSel()->SetEta(2.4);
   
   /// χ2/ndof of the global-muon track fit. To suppress hadronic punch-through and muons from decays in flight.
   /// TIGHT ID includes χ2/ndof < 10
   // To tighten or add use SetChiNdof(X);
   //eventbase->GetMuonSel()->SetChiNdof(10.);

   /// TIGHT ID includes dxy < 2 mm  amd dz < 5 mm
   /// FOr our analysis we tighten to 50 micrometers and 1 mm respectively
   //eventbase->GetMuonSel()->SetBSdxy(0.005);
   //eventbase->GetMuonSel()->SetBSdz(0.10);
   
   /// Use PF isolation DR=0.3
   /// (∑ET(chHad from PV)+∑ET(neutHad)+∑ET(photons))/pT < 0.1
   //eventbase->GetMuonSel()->SetRelIso(0.1);
   //eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
   
   /// New function applies all tight selection
   eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);
   
   std::vector<snu::KMuon> muonHighPtColl;
   eventbase->GetMuonSel()->HNTightHighPtMuonSelection(muonHighPtColl);
   
   for(std::vector<snu::KMuon>::iterator it = muonTightColl.begin(); it!= muonTightColl.end(); it++){
cout << "Weight = " << weight << endl;
     weight *= MuonScaleFactor(it->Eta(), it->Pt());
cout << "Weight = " << weight << endl;
    cout << "Tight muon pt = " << it->Pt() << " " << it->Eta() << " " << it->Phi() << endl; 
   }
   
   
   /// Example of how to get fake weight for dimuon channel
   std::vector<snu::KMuon> muonLooseColl;
   eventbase->GetMuonSel()->HNLooseMuonSelection(muonLooseColl);
   
   ///////////////////////////////////////////////////////////////////////////////////////////
   /// 2) Loose Muons for veto
   ///////////////////////////////////////////////////////////////////////////////////////////

   std::vector<snu::KMuon> muonVetoColl;
   eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);



   
   ///////////////////////////////////////////////////////////////////////////////////////////
   /// 3) Tight Electrons
   ///////////////////////////////////////////////////////////////////////////////////////////
   std::vector<snu::KElectron> electronTightColl;

   eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);

  
   /// 4) Jets(with lepton veto)
   std::vector<snu::KJet> jetColl_lepveto;
   eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto, muonTightColl, electronTightColl);

   ///// SOME STANDARD PLOTS /////
   ////  Z-> mumu            //////

   if (muonTightColl.size() == 2) {                   
     snu::KParticle Z = muonTightColl.at(0) + muonTightColl.at(1);
     if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){      
       
       /// Method of plotting single histogram
       FillHist("zpeak_mumu", Z.M(), weight, 0., 200.,400);

       /// Standard set of histograms for muons/jets/electrons.. with no corrections
       FillCLHist(sighist, "DiMuon", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);

       /// Standard set of histograms with pileup reweighting applied
       FillCLHist(sighist, "DiMuonWPURW", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight*pileup_reweight);
       
       if(muonVetoColl.size() ==2){
	 FillCLHist(sighist, "DiMuonLooseVeto", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight*pileup_reweight);
       }       
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



