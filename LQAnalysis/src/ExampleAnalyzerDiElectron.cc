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
   MakeCleverHistograms(sighist_ee, "DiElectron");
   MakeCleverHistograms(sighist_ee, "DiElectron_EE");
   MakeCleverHistograms(sighist_ee, "DiElectron_EB");
   MakeCleverHistograms(sighist_ee, "DiElectron_BB");
   MakeCleverHistograms(sighist_ee, "DiElectron_BJet");
   MakeCleverHistograms(sighist_ee, "SSElectron");
   MakeCleverHistograms(sighist_ee, "SSElectron_DiJet");
   MakeCleverHistograms(sighist_ee, "SSElectron_DiJet_ChargeConsistency");

   MakeCleverHistograms(trilephist,"TriElectron");
   MakeCleverHistograms(trilephist,"TriElectron_nomet");
   MakeCleverHistograms(trilephist,"TriElectron_noB");

   
   return;
}


void ExampleAnalyzerDiElectron::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  /// Apply MC weight for MCatnlo samples
  weight*= MCweight;


  /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
  /// The string cut must match a bin label in FillCutFlow function
  FillCutFlow("NoCut", weight);
  FillHist("GenWeight" , 1., MCweight,  0. , 2., 2);


  if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);


  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  vector<snu::KTruth> truth =  eventbase->GetTruth();
  
  int match_el(0), match_mu(0), match_t(0), match_q(0);
  for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
    
    if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
    if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;

    if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 11){
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 23) match_el++;
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 24) match_el++;
    }
    else if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 13){
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 23) match_mu++;
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 24) match_mu++;
    }
    else if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 15){
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 23) match_t++;
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 24) match_t++;
    }
    else if(fabs(eventbase->GetTruth().at(ig).PdgId()) != 23 && fabs(eventbase->GetTruth().at(ig).PdgId()) != 24){
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 23) match_q++;
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 24) match_q++;
    }
    
  }
  FillHist("Decay_WZ_el", match_el ,weight, 0. , 5., 5);
  FillHist("Decay_WZ_mu", match_mu ,weight, 0. , 5., 5);
  FillHist("Decay_WZ_t", match_t ,weight, 0. , 5., 5);
  FillHist("Decay_WZ_q", match_q ,weight, 0. , 5., 5);
  

  
  /// Trigger List 
  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  // This trigger will be  Unprescaled till L = 7E33 (may be used for this whole year) 
  // https://indico.cern.ch/event/370510/contribution/1/attachments/1161160/1671811/EleTriggers_Arun_28Sept_v1.pdf
  if(!PassTrigger(triggerslist, prescale)) return;
  

  FillCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;

  
  //ListTriggersAvailable(); // uncomment this line to list off available triggers in the same

  // Trigger matching is done using KElectron::TriggerMatched(TString) which returns a bool

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillCutFlow("VertexCut", weight);
  /// Has Good Primary vertex:
  /// if ( vtx.ndof() > 4 &&
  //   ( (maxAbsZ <=0 ) || std::abs(vtx.z()) <= 24 ) &&
  //( (maxd0 <=0 ) || std::abs(vtx.position().rho()) <= 2 ) &&
  //!(vtx.isFake() ) ){


  /// Use the number of vertices in the event to check effect of pileup reweighting
  numberVertices = eventbase->GetEvent().nVertices();   
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////

  
  // Get loose muons for veto: Can call  POGSoft/POGLoose/POGMedium/POGTight/HNVeto/HNLoose/HNMedium/HNTight
  std::vector<snu::KMuon> muonColl = GetMuons(BaseSelection::MUON_POG_LOOSE); // loose selection
  
  /// Get tight jets : Can call NoLeptonVeto/Loose/Medium/Tight/HNJets
  std::vector<snu::KJet> jetColl_hn  = GetJets(BaseSelection::JET_HN);// pt > 20 ; eta < 2.5; PFlep veto; NO pileup ID
  std::vector<snu::KJet> jetColl_nlv  = GetJets(BaseSelection::JET_NOLEPTONVETO);
  std::vector<snu::KJet> jetColl_loose  = GetJets(BaseSelection::JET_LOOSE);

  FillHist("Njets", jetColl_hn.size() ,weight, 0. , 5., 5);


  // Get POG electrons :  Can call POGVeto/POGLoose/POGMedium/POGTight/HNVeto/HNLoose/HNMedium/HNTight                                                                                              
  std::vector<snu::KElectron> electronLooseColl        = GetElectrons(BaseSelection::ELECTRON_POG_LOOSE);
  std::vector<snu::KElectron> electronColl             = GetElectrons(BaseSelection::ELECTRON_POG_TIGHT);

  // Sets weight to weight if not running chargeflip bkg estimate or events are S
  if(k_running_chargeflip) weight              *= WeightCFEvent(electronColl, k_running_chargeflip);
    
  for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
    if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
    if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;
    
    
    //    cout << "Particle pdgid = " << eventbase->GetTruth().at(ig).PdgId() << " status = " << eventbase->GetTruth().at(ig).GenStatus() << "  mother = " <<  eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId() << endl;
  }
  //  cout << "\n" << endl;
  
  if(electronLooseColl.size() ==3 ) {
    FillHist("Decay_WZ_el_threeloosereco", match_el ,weight, 0. , 5., 5);
    if(eventbase->GetEvent().PFMET() > 30){
      FillHist("Decay_WZ_el_threeloosereco_metcut", match_el ,weight, 0. , 5., 5);
    }
  }


  std::vector<snu::KElectron> electronHNLooseColl  = GetElectrons(BaseSelection::ELECTRON_HN_FAKELOOSE);
  std::vector<snu::KElectron> electronHNVetoColl   = GetElectrons(BaseSelection::ELECTRON_HN_VETO);
  std::vector<snu::KElectron> electronHNTightColl   = GetElectrons(BaseSelection::ELECTRON_HN_TIGHT);
  
  FillHist("NJets_nlv" , jetColl_nlv.size(), weight, 0., 5., 5);
  FillHist("NJets_loose" , jetColl_loose.size(), weight, 0., 5., 5);

  FillHist("NElectrons_hnloose" ,  electronHNLooseColl.size(), weight, 0., 5., 5);
  FillHist("NElectrons_hnveto" ,   electronHNVetoColl.size(), weight, 0., 5., 5);
  FillHist("NElectrons_hntight" ,  electronHNTightColl.size(), weight, 0., 5., 5);
  FillHist("NElectrons_pogloose" ,  electronLooseColl.size(), weight, 0., 5., 5);
  FillHist("NElectrons_pogtight" ,  electronColl.size(), weight, 0., 5., 5);

  
  //FillHist("Njets", jetColl_hn.size() ,weight, 0. , 5., 5);
  
  int njet = jetColl_hn.size();
  FillHist("GenWeight_NJet" , njet*MCweight + MCweight*0.1, 1., -6. , 6., 12);

  

  /// Correct MC for pileup   
  
  float pileup_reweight (1.);
  if (!k_isdata) {
    /// use silver or gold

    pileup_reweight = eventbase->GetEvent().PileUpWeight(snu::KEvent::silver);
  }
  
  if(!isData){
    for(unsigned int iel=0; iel < electronColl.size(); iel++){
      weight*= ElectronScaleFactor(BaseSelection::ELECTRON_POG_TIGHT, electronColl);
    }
  }

  if(electronColl.size() ==2) {
    if(electronColl.at(0).Pt() > 25. && electronColl.at(1).Pt() > 15. ){
      FillHist("Njets_dilepton", jetColl_hn.size() ,weight, 0. , 5., 5);
      FillCutFlow("DiEl_tight", weight);
      /// Method of plotting single histogram
      FillHist("zpeak_ee_noPUrw", GetDiLepMass(electronColl), weight, 0., 200.,400);
      FillHist("zpeak_ee", GetDiLepMass(electronColl), weight*pileup_reweight, 0., 200.,400);
      
      /// Standard set of histograms for muons/jets/electrons.. with no corrections
      FillCLHist(sighist_ee, "DiElectron", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
      
      if(electronColl.at(0).IsEEFiducial() && electronColl.at(1).IsEEFiducial()) 
	FillCLHist(sighist_ee, "DiElectron_EE", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
      
      if(electronColl.at(0).IsEBFiducial() && electronColl.at(1).IsEBFiducial())
        FillCLHist(sighist_ee, "DiElectron_BB", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
      
      if(electronColl.at(0).IsEBFiducial() && electronColl.at(1).IsEEFiducial())
        FillCLHist(sighist_ee, "DiElectron_EB", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
      if(electronColl.at(1).IsEBFiducial() && electronColl.at(0).IsEEFiducial())
        FillCLHist(sighist_ee, "DiElectron_EB", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);

           

      /// Count number of bjets (Medium WP in event)
      int nbjet=0;
      for(unsigned int i=0; i <jetColl_hn.size() ; i++){
	if(jetColl_hn.at(i).CSVInclV2() > 0.89) nbjet++;
      }
      
      /// OR use NBJet(jets) function
      if(njet > 2 && NBJet(jetColl_hn) > 0)      FillCLHist(sighist_ee, "DiElectron_BJet", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);


      
      if(SameCharge(electronColl, k_running_chargeflip))  {

	cout << "SS event " << endl;	
	cout << "Electron 1 eta/phi/pt =" <<  electronColl.at(0).Eta() << " / " << electronColl.at(0).Phi() << " / " << electronColl.at(0).Pt() << endl;
	cout << "Electron 2 eta/phi/pt =" <<  electronColl.at(1).Eta() << " / " << electronColl.at(1).Phi() << " / " << electronColl.at(1).Pt() << endl;
	for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
	  if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
	  if(eventbase->GetTruth().at(ig).IndexMother() >= eventbase->GetTruth().size())continue;
	  
	  if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 11){
	    cout << "eventbase->GetTruth().at(ig).Eta = " << eventbase->GetTruth().at(ig).Eta() << " eventbase->GetTruth().at(ig).Phi = " << eventbase->GetTruth().at(ig).Phi() << " eventbase->GetTruth().at(ig).Pt = " << eventbase->GetTruth().at(ig).Pt() << endl;
	    if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 23) cout << "matched to Z" << endl;
	    if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(ig).IndexMother()).PdgId()) == 24) cout << "matched to W" << endl;
	  }
	}
	

	FillCLHist(sighist_ee, "SSElectron", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
	
	if (njet >= 2) {
	  FillCLHist(sighist_ee, "SSElectron_DiJet", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
	  if(electronColl.at(0).GsfCtfScPixChargeConsistency() && electronColl.at(1).GsfCtfScPixChargeConsistency())
	    FillCLHist(sighist_ee, "SSElectron_DiJet_ChargeConsistency", eventbase->GetEvent(), muonColl,electronColl,jetColl_hn, weight*pileup_reweight);
	}
      }      
    }
  }
  
    
  if(electronLooseColl.size() == 3 && muonColl.size() == 0) {
    if(electronLooseColl.at(0).Pt() > 25. && electronLooseColl.at(2).Pt() > 25. ){
      FillHist("MET", eventbase->GetEvent().PFMET() ,weight, 0. , 100., 20);
      if( NBJet(jetColl_hn) == 0)FillCLHist(trilephist, "TriElectron_nomet", eventbase->GetEvent(), muonColl,electronLooseColl,jetColl_hn, weight*pileup_reweight);
      if(eventbase->GetEvent().PFMET() > 30){
	FillCLHist(trilephist, "TriElectron", eventbase->GetEvent(), muonColl,electronLooseColl,jetColl_hn, weight*pileup_reweight);
	if( NBJet(jetColl_hn) == 0)       FillCLHist(trilephist, "TriElectron_noB", eventbase->GetEvent(), muonColl,electronLooseColl,jetColl_hn, weight*pileup_reweight);
      }
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



