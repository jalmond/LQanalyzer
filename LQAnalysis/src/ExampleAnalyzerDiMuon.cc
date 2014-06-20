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

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   MakeCleverHistograms(sighist, "DiMuon");
   MakeCleverHistograms(sighist, "DiMuonWPURW");
   MakeCleverHistograms(sighist, "DiMuonLooseVeto");

   return;
 }


void ExampleAnalyzerDiMuon::ExecuteEvents()throw( LQError ){

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
   /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
   /// The string cut must match a bin label in FillCutFlow function
   FillCutFlow("NoCut", weight);
   
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
     pileup_reweight = reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
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
   
   
   for(std::vector<snu::KMuon>::iterator it = muonTightColl.begin(); it!= muonTightColl.end(); it++){
     //cout << "Tight muon pt = " << it->Pt() << " " << it->Eta() << " " << it->Phi() << endl; 
   }
  
   CorrectMuonMomentum(muonTightColl);
   
   
   for(std::vector<snu::KMuon>::iterator it = muonTightColl.begin(); it!= muonTightColl.end();it++){
     //cout << "Tight corrrected muon pt = "<< it->Pt() << " " << it->Eta() << " " << it->Phi() << endl;
   }
   

   std::vector<snu::KMuon> muonLooseColl;
   eventbase->GetMuonSel()->HNLooseMuonSelection(muonLooseColl);
   if(muonLooseColl.size()==2){
    float mmweight = Get_DataDrivenWeight_MM(muonLooseColl);
   }
   
   
   ///////////////////////////////////////////////////////////////////////////////////////////
   /// 2) Loose Muons for veto
   ///////////////////////////////////////////////////////////////////////////////////////////

   std::vector<snu::KMuon> muonVetoColl;
   /// Lower pt cut to 10
   //eventbase->GetMuonSel()->SetPt(10.);
   //eventbase->GetMuonSel()->SetEta(2.4);
   // Use LOOSE definition from https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Loose_Muon
   //eventbase->GetMuonSel()->SetID(BaseSelection::MUON_LOOSE);
   // Use loose isolation https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId#Muon_Isolation_AN1
   // Note we use PF based isolation
   //(∑ET(chHad from PV)+∑ET(neutHad)+∑ET(photons))/pT
   // Default is 0.12 for Tight and 0.2 for loose.. However this is with 0.4 cone. We use 0.3 cone
   //eventbase->GetMuonSel()->SetRelIso(0.20);
   /// These following cuts are essentially large to be extremely loose
   //eventbase->GetMuonSel()->SetChiNdof(500.);
   //eventbase->GetMuonSel()->SetBSdxy(2000.);
   //eventbase->GetMuonSel()->SetBSdz(100.00);
   //eventbase->GetMuonSel()->SetDeposits(400.0,600.0);
   
   // New function applied all selection for veto muons
   eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);



   
   ///////////////////////////////////////////////////////////////////////////////////////////
   /// 3) Tight Electrons
   ///////////////////////////////////////////////////////////////////////////////////////////
   std::vector<snu::KElectron> electronTightColl;

   //// CHOICE OF ELECTRON ID /////////////////////
   /// Use MEDIUM definition from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipes#Cut_based_electron_Identificatio
   // This cuts on shower shape/ PF isoaltion/ tracker hits / Impact Parameter
   //eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_MEDIUM);

   /// Select pt of electrons
   //eventbase->GetElectronSel()->SetPt(20);

   // Use 2.5 eta cut. This is due to the acceptance of the tracker
   // Barrel |eta| <= 1.479
   // Endcap 1.479 < |eta| < 2.5
   // We actually cut on 1.4442<abeta<1.566 . This is due to gap region between barrel and endcap of the ECal
   //eventbase->GetElectronSel()->SetEta(2.5);

   /// A relative iso cut of 0.15 is already implemented in the EGAMMA_MEDIUM cut.
   /// Uses PF isolation. Corrected for Pile Up https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaEARhoCorrection
   /// Default cone size is 0.3.
   /// 0.15 is medium working point. 0.10 is Tight (recommended)
   /// Can apply tighter cut by uncommenting the line below and chaning the value
   //  eventbase->GetElectronSel()->SetRelIso(0.15);

   /// Some IP (dxy, dz) cuts are applied in the ID cut
   /// |d0| <  0.02 (200 micrometers) default
   /// |dZ| <  0.10  default
   /// Can apply tighter cuts using SetBSdxy/SetBSdz
   //eventbase->GetElectronSel()->SetBSdxy(0.02);
   //eventbase->GetElectronSel()->SetBSdz(0.10);

   // We can check the charge of the Super Cluster / Tracker / combined electron
   // SetCheckCharge(true) requires that all 3 are the same
   //eventbase->GetElectronSel()->SetCheckCharge(true);

   // Some cuts are applied in the ID MEDIUM/TIGHT to reduce conversion electrons
   // These cuts are on the vertex fit probabilty/missing hits in the tracker
   // https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaCutBasedIdentification#Conversion_Rejection
   // We can also cut on the presence of any matched conversion https://twiki.cern.ch/twiki/bin/viewauth/CMS/ConversionTools
   // To apply the passconversionveto use SetApplyConvVeto(true)
   //eventbase->GetElectronSel()->SetApplyConvVeto(true);

   /// Use the selection function to fill our empty vector with the cuts specified above
   
   /// New function applies all tight selection
   eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);

  
   /// 4) Jets(with lepton veto)
   std::vector<snu::KJet> jetColl_lepveto;
   /// We use PFJets : AKT jets with dR=0.5
   /// Select the ID choose for Jets https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID
   /// Cuts applied to 1) isolation 2) EM fraction 3) HPD noise rejection
   //eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
   // 20 GeV is very loose. Needed to keep soft signal muons form heavy neutrinos
   //eventbase->GetJetSel()->SetPt(20.);
   // As with electrons the eta cut is chosed to coincide with teh tracker acceptance
   //eventbase->GetJetSel()->SetEta(2.5);
   /// To select jets use predefined function
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



