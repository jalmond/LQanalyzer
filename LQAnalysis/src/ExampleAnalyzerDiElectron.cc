// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzerDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzerDiElectron.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzerDiElectron);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ExampleAnalyzerDiElectron::ExampleAnalyzerDiElectron() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzerDiElectron");

  Message("In ExampleAnalyzerDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void ExampleAnalyzerDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   MakeCleverHistograms(sighist, "DiElectron");
   MakeCleverHistograms(sighist, "DiElectronWPURW");
   MakeCleverHistograms(sighist, "DiElectronWPURWID");
   MakeCleverHistograms(sighist, "DiElectronWPURWID_METGT45");

   MakeCleverHistograms(sighist, "DiElectron1bjet");
   MakeCleverHistograms(sighist, "DiElectron2bjet");
   MakeCleverHistograms(sighist, "DiElectronSameSign");
   
   return;
}


void ExampleAnalyzerDiElectron::ExecuteEvents()throw( LQError ){
  
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
  
  /// Trigger List 
  std::vector<TString> triggerslist;
  /// This is the analysis electron trigger 
  /// No Scale Factors are yet applied to correct MC
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
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
  /// Fill a hist with nVertices with no reweighting
  FillHist("h_nvtx_norw_ee", numberVertices, weight, 0., 60.,60); 
  
  /// Correct MC for pileup   
  
  float pileup_reweight (1.);
  if (!k_isdata) {
    pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  FillHist("h_nvtx_rw_ee",numberVertices,weight, 0., 60.,60 );
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// We want to select events with 2 medium electrons (we will also remove events with a looser third muon to show how it is done)
  /// We will use 4 different object collections
  /// 1) Tight Electrons  ||  eventbase->GetElectronSel()->HNTightElectronSelection
  /// 2) Loose Electrons for veto (can veto events with a third loose el)    || eventbase->GetElectronSel()->HNVetoElectronSelection
  /// 3) Tight Muons (for PFjet veto)  || eventbase->GetMuonSel()->HNTightMuonSelection
  /// 4) Jets(with lepton veto)
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) TightElectrons                                                                                                                                                     
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronTightColl;
  
  //// CHOICE OF ELECTRON ID /////////////////////
  /// Use MEDIUM definition from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipes#Cut_based_electron_Identificatio
  // This cuts on shower shape/ PF isoaltion/ tracker hits / Impact Parameter  
  //eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_TIGHT);
  
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

  ///New function that applies all tight selection

  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->Selection(jetColl);
  
  eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);
  m_logger << DEBUG << "Number of electrons  = " << electronTightColl.size() << LQLogger::endmsg; 
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 2) Loose Electrons
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronVetoColl;
  /// Use VETO definition from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipes#Cut_based_electron_Identificatio
  // This cuts on shower shape/ PF isoaltion/ tracker hits / Impact Parameter
  //eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_VETO);
  /// Lower pt for veto
  //eventbase->GetElectronSel()->SetPt(10.);
  //eventbase->GetElectronSel()->SetEta(2.5);
  //eventbase->GetElectronSel()->SetRelIso(0.15);

  /// new function that applies all vero selection  
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  m_logger << DEBUG << "Number of veto electrons  = " << electronVetoColl.size() << LQLogger::endmsg;
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 3) Tight Muons
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KMuon> muonTightColl;
  //eventbase->GetMuonSel()->SetPt(20.);
  /// ID are explained in https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideMuonId
  //eventbase->GetMuonSel()->SetID(BaseSelection::MUON_TIGHT);
  
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
  
  // New function that applies all tight muon selection
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);
  m_logger << DEBUG << "Number of muons  = " << muonTightColl.size() << LQLogger::endmsg;

  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 4) Jets(with lepton veto) 
  ///////////////////////////////////////////////////////////////////////////////////////////
  
  std::vector<snu::KJet> jetColl_lepveto;
  /// We use PFJets : AKT jets with dR=0.5
  /// Select the ID choose for Jets https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID
  /// Cuts applied to 1) isolation 2) EM fraction 3) HPD noise rejection
  //eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  
  // 20 GeV is very loose. Needed to keep soft signal muons form heavy neutrinos
  //eventbase->GetJetSel()->SetPt(20.);
  
  // As with electrons the eta cut is chosed to coincide with teh tracker acceptance
  //eventbase->GetJetSel()->SetEta(2.5);
  
  /// To select jets use predefined function in JetSel
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto, muonTightColl, electronTightColl);
  m_logger << DEBUG<< "Number of jets  = " << jetColl_lepveto.size() << LQLogger::endmsg;

  int nbjet=0;
   for(unsigned int i=0; i <jetColl_lepveto.size() ; i++){
    if(jetColl_lepveto.at(i).CVSInclV2() > 0.679) nbjet++;
   }

  ///// SOME STANDARD PLOTS /////
  ////  Z-> ee              //////
  if (electronTightColl.size() == 2) {      
    
    /// For MC reweight event to correct for ID efficiency in MC/DATA
    float id_scalefactor(1.);
    if(!isData){
      id_scalefactor *=  ElectronScaleFactor(electronTightColl.at(0).Eta(), electronTightColl.at(0).Pt(), true);
      id_scalefactor *=  ElectronScaleFactor(electronTightColl.at(1).Eta(), electronTightColl.at(1).Pt(), true);
    }
    
    // reconstruct dilepton system
    snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
    
    if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge()){      
    
      /// Fill Standard set of cuts for all objects with NO corrections    
      FillCLHist(sighist, "DiElectron", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
      FillCutFlow("DiEl_tight",weight); 

      /// Fill Standardset of cuts forall objects with pileup reweighting applied
      FillCLHist(sighist, "DiElectronWPURW", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight));

      /// Fill Standardset of cuts forall objects with pileup reweighting applied
      FillCLHist(sighist, "DiElectronWPURWID", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));
      
      if(eventbase->GetEvent().PFMET() > 45.) FillCLHist(sighist, "DiElectronWPURWID_METGT45", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));
      
      /// Select Top lise events
      if( (fabs(Z.M() - 90.) > 20.) && nbjet >0)
	{   	
 	 
	  if(nbjet > 1){
	    FillCLHist(sighist, "DiElectron2bjet", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));
	  }

	  FillCLHist(sighist, "DiElectron1bjet", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));

	}
    }// OS 
    else {
      FillCLHist(sighist, "DiElectronSameSign", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, (weight*pileup_reweight*id_scalefactor));
    }
    
  }
  
  return;
}// End of execute event loop
  


void ExampleAnalyzerDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

}


void ExampleAnalyzerDiElectron::BeginCycle() throw( LQError ){
  
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

ExampleAnalyzerDiElectron::~ExampleAnalyzerDiElectron() {
  
  Message("In ExampleAnalyzerDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzerDiElectron::FillCutFlow(TString cut, float weight){

  
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


void ExampleAnalyzerDiElectron::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ExampleAnalyzerDiElectron::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerDiElectronCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzerDiElectron::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



