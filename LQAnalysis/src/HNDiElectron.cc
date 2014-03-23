// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"

//Core includes
#include "Reweight.h"
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
   MakeCleverHistograms(sighist, "SSDiElectronMedium");
   MakeCleverHistograms(sighist, "SSDiElectronTight");
   MakeCleverHistograms(sighist, "SSDiElectronTight_DiJet");
   MakeCleverHistograms(sighist, "SSDiElectronTightNLV");
   MakeCleverHistograms(elhist,  "SSDiElectronMedium_Electrons");
   MakeCleverHistograms(sighist,  "NoCut");
   MakeCleverHistograms(sighist,  "TriEl");
   MakeCleverHistograms(sighist,  "ZZ");


   
   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
  /// The string cut must match a bin label in FillCutFlow function
  //FillCutFlow("NoCut", weight);
  
  ///// Apply some general cuts on event to clean MET
  /// Taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
  /// These are applied in AnalyzerCore::PassBasicEventCuts
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  //FillCutFlow("EventCut", weight);
  
  /// Trigger List 
  std::vector<TString> triggerslist;
  /// This is the analysis electron trigger 
  /// No Scale Factors are yet applied to correct MC
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  //if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  //FillCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
    
  /// Check the event has a "Good" Primary vertex
  /// Good is taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/TrackingPFGJob:
  /// defined as : !isFake && ndof > 4 && |z| <= 24 cm && position.Rho <= 2cm (rho = radius of vertex)
  /// Cut is coded in SKTreeFiller and stored in KEvent class as HasGoodPrimaryVertex()
  /// More info on primary vertex can be found https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideOfflinePrimaryVertexProduction (LQNtuples use offlinePrimaryVertices)
  // isFake is true if the vertex is based on the beam spot (as no reconstructed vertex is found
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  
  //FillCutFlow("VertexCut", weight);
  
  /// Use the number of vertices in the event to check effect of pileup reweighting
  numberVertices = eventbase->GetEvent().nVertices();   

  /// Correct MC for pileup   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
  }


  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) TightElectrons                                                                                                                                                     
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_TIGHT);
  eventbase->GetElectronSel()->SetPt(30);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronTightColl);
  
  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) MediumElectrons
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronMediumColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_MEDIUM);
  //  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(4.5);
  eventbase->GetElectronSel()->Selection(electronMediumColl);


  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) EGAMMA_TRIGTIGHT
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronTrigTightColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_TRIGTIGHT);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronTrigTightColl);


  ///////////////////////////////////////////////////////////////////////////////////////////                                                                                       
  /// 1) MVA
  ///////////////////////////////////////////////////////////////////////////////////////////                                                                                       

  std::vector<snu::KElectron> electronMVAColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::MVATrig);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronMVAColl);


  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) EGAMMA_TRIGWP70
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronTrigWP70Coll;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_TRIGWP70);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronTrigWP70Coll);


  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 1) EGAMMA_TRIGWP70
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronEOPColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_EOP);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronEOPColl);



  
  ///////////////////////////////////////////////////////////////////////////////////////////
  /// 2) Loose Electrons
  ///////////////////////////////////////////////////////////////////////////////////////////

  std::vector<snu::KElectron> electronVetoColl;
  /// Use VETO definition from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipes#Cut_based_electron_Identificatio
  // This cuts on shower shape/ PF isoaltion/ tracker hits / Impact Parameter
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_VETO);
  /// Lower pt for veto
  eventbase->GetElectronSel()->SetPt(10.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SetRelIso(0.15);
  eventbase->GetElectronSel()->Selection(electronVetoColl);
  
  std::vector<snu::KMuon> muonVetoColl;
  /// Lower pt cut to 10
  eventbase->GetMuonSel()->SetPt(10.);
  eventbase->GetMuonSel()->SetEta(2.4);
  eventbase->GetMuonSel()->SetID(BaseSelection::MUON_LOOSE);
  eventbase->GetMuonSel()->SetRelIso(0.20);
 eventbase->GetMuonSel()->SetChiNdof(500.);
 eventbase->GetMuonSel()->SetBSdxy(2000.);
 eventbase->GetMuonSel()->SetBSdz(100.00);
 eventbase->GetMuonSel()->SetDeposits(400.0,600.0);
 eventbase->GetMuonSel()->Selection(muonVetoColl);

 

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->SetPt(20.);
  eventbase->GetMuonSel()->SetID(BaseSelection::MUON_TIGHT);
  eventbase->GetMuonSel()->SetBSdxy(0.005);
  eventbase->GetMuonSel()->SetBSdz(0.10);
  eventbase->GetMuonSel()->SetEta(2.4);
  eventbase->GetMuonSel()->SetRelIso(0.1);
  eventbase->GetMuonSel()->SetDeposits(4.0,6.0);
  eventbase->GetMuonSel()->Selection(muonTightColl);
  

  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(30.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonTightColl, electronTightColl);
  eventbase->GetJetSel()->Selection(jetColl);

  
  if(electronMediumColl.size() ==2){
    if(electronMediumColl.at(0).Charge() == electronMediumColl.at(1).Charge()) {

      for(int it = 0; it < eventbase->GetTruth().size() ; it++){
	
	if(eventbase->GetTruth().at(it).GenStatus() == 3 && eventbase->GetTruth().at(it).PdgId() == -11 && eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId() == -24 || 23) ;
	
      }
 
      bool closejet = false;
      for(int j = 0; j < electronMediumColl.size(); j++){
	bool prompt_e=false;
	
	m_logger << INFO << "\n-------------------------------------\n " << LQLogger::endmsg;
	m_logger << INFO << "Electron id = " << j << "  pt = " << electronMediumColl.at(j).Pt() << " eta = " << electronMediumColl.at(j).Eta() << " phi = " << electronMediumColl.at(j).Phi() << " energy = " << electronMediumColl.at(j).E() << LQLogger::endmsg;
	
	for(int it = 0; it < eventbase->GetTruth().size() ; it++){

	  if(eventbase->GetTruth().at(it).GenStatus() == 3 && fabs(eventbase->GetTruth().at(it).PdgId()) == 11){
    
	    if(eventbase->GetTruth().at(it).PdgId() * electronMediumColl.at(j).Charge() < 0){
	      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId()) == 24 || fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId()) ==  23) {
		m_logger << "Truth el pt = " << eventbase->GetTruth().at(it).Pt() << " eta = " << eventbase->GetTruth().at(it).Eta() << " phi = " << eventbase->GetTruth().at(it).Phi() << LQLogger::endmsg;
		if(electronMediumColl.at(j).DeltaR(eventbase->GetTruth().at(it)) < 0.3) {
		  prompt_e=true; 
		}
	      }
	    }
	  }
	}
	
	for(int it = 0; it < jetColl.size(); it++){
	  m_logger<< INFO << "Jet id = " << it+1 << " pt = " <<  jetColl.at(it).Pt() << " eta= " << jetColl.at(it).Eta() << " phi = " << jetColl.at(it).Phi() << LQLogger::endmsg;
	}
	for(int it = 0; it < eventbase->GetGenJets().size(); it++){
	  if(eventbase->GetGenJets().at(it).DeltaR(electronMediumColl.at(j)) < 0.4) {
	    m_logger<< INFO << "Matched Gen jet id = " << it+1 << " pt = " <<  eventbase->GetGenJets().at(it).Pt() << " eta= " << eventbase->GetGenJets().at(it).Eta() << " phi = " << eventbase->GetGenJets().at(it).Phi() << LQLogger::endmsg;   
	  }
	}

	if(prompt_e)m_logger<< INFO << "Electron is prompt" << LQLogger::endmsg;
	else  m_logger<< INFO << "Electron is NOT prompt" << LQLogger::endmsg;
	
	
	if(prompt_e){
	  for(int i = 0; i < jetColl.size(); i++){
	    
	    if( jetColl.at(i).DeltaR(electronMediumColl.at(j)) < 0.4) {
	      
	      m_logger << INFO << "Electron vertex index = " << electronMediumColl.at(j).VertexIndex()  << LQLogger::endmsg;
	      FillHist("prompt_e_closejet_dr", jetColl.at(i).DeltaR(electronMediumColl.at(j)), weight, 0.,0.2,1000);

	      FillHist("prompt_e_closejet_multiplicity",jetColl.at(i).ChargedMultiplicity(), weight, 0.,30.,30);
	      FillHist("prompt_e_closejet_chem_enfrac", jetColl.at(i).ChargedEMEnergyFraction(), weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_chhad_enfrac", jetColl.at(i).ChargedHadEnergyFraction() , weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_elfrac", jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_nem_frac", jetColl.at(i).NeutralEMEnergyFraction(), weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_nhad_frac", jetColl.at(i).NeutralHadEnergyFraction(), weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_phot_frac", jetColl.at(i).PhotonEnergyFraction()  , weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_muon_frac", jetColl.at(i).MuonEnergyFraction() , weight, 0., 1., 100.);
	      FillHist("prompt_e_closejet_vert_index", jetColl.at(i).BestVertexTrackAssociationIndex() -  electronMediumColl.at(j).VertexIndex(), weight, -10., 10., 20);
	      FillHist("prompt_e_closejet_vert_frac", jetColl.at(i).BestVertexTrackAssociationFactor(), 0., 1., 100.);
	      
	      
	      FillHist("prompt_e_closejet_had_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100, 0., 1., 100);
	      FillHist("prompt_e_closejet_hadphoton_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction() + jetColl.at(i).PhotonEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() , weight , 0., 1., 100, 0., 1., 100);
	      

	      float theta = 2.*atan( (exp(-1.*jetColl.at(i).Eta())));
	      float sintheta = sin(theta);
	      float Et = jetColl.at(i).E() * sintheta;

	      m_logger << INFO << "prompt Jet energy = " << jetColl.at(i).E() << LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et = " <<  Et<< LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et (1-el frac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) << LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et (1-el- ph frac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction()- jetColl.at(i).PhotonEnergyFraction())) << LQLogger::endmsg;
	      
	      FillHist("prompt_e_closejet_pt_corrEt", jetColl.at(i).Pt(), (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) , weight, 0., 200., 200., 0., 100., 100.);

      
	      FillHist("prompt_e_closejet_Ecorr", (Et * (1. - jetColl.at(i).ElectronEnergyFraction()))  , weight, 0., 100., 50.);
	      FillHist("prompt_e_closejet_Ecorr2", (Et * (1. - (jetColl.at(i).ElectronEnergyFraction() + jetColl.at(i).PhotonEnergyFraction()))  )  , weight, 0., 100., 50.);
	      
	      
	      if((jetColl.at(i).Pt() * (1.- jetColl.at(i).ElectronEnergyFraction())) > 20.) closejet = true;

	      
	    }
	  }
	
	  FillHist("SSMediumElclosejet",0, weight, 0.,2.,2);
	  if(!closejet)FillHist("SSMediumElclosejet",1, weight, 0.,2.,2);
	}
	else{
	  for(int i = 0; i < jetColl.size(); i++){

            if( jetColl.at(i).DeltaR(electronMediumColl.at(j)) < 0.4) {
	      
	      FillHist("nonprompt_e_closejet_dr", jetColl.at(i).DeltaR(electronMediumColl.at(j)), weight, 0.,0.2,1000);
              m_logger << INFO << "Electron vertex index = " << electronMediumColl.at(j).VertexIndex()  << LQLogger::endmsg;
              FillHist("nonprompt_e_closejet_multiplicity",jetColl.at(i).ChargedMultiplicity(), weight, 0.,30.,30);
              FillHist("nonprompt_e_closejet_chem_enfrac", jetColl.at(i).ChargedEMEnergyFraction(), weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_chhad_enfrac", jetColl.at(i).ChargedHadEnergyFraction() , weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_elfrac", jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_nem_frac", jetColl.at(i).NeutralEMEnergyFraction(), weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_nhad_frac", jetColl.at(i).NeutralHadEnergyFraction(), weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_phot_frac", jetColl.at(i).PhotonEnergyFraction()  , weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_muon_frac", jetColl.at(i).MuonEnergyFraction() , weight, 0., 1., 100.);
              FillHist("nonprompt_e_closejet_vert_index", jetColl.at(i).BestVertexTrackAssociationIndex() -  electronMediumColl.at(j).VertexIndex(), weight, -10., 10., 20);
              FillHist("nonprompt_e_closejet_vert_frac", jetColl.at(i).BestVertexTrackAssociationFactor(), 0., 1., 100.);


	      
	      FillHist("nonprompt_e_closejet_had_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() ,weight, 0., 1., 100, 0., 1., 100);
              FillHist("nonprompt_e_closejet_hadphoton_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction() + jetColl.at(i).PhotonEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() ,weight, 0., 1., 100, 0., 1., 100);
	      
	      

	      float theta = 2.*atan( (exp(-1.*jetColl.at(i).Eta())));
	      float sintheta = sin(theta);
	      float Et = jetColl.at(i).E() * sintheta;
	      
	      m_logger << INFO << "non prompt Jet Et = " << Et << LQLogger::endmsg;
              m_logger << INFO << "non prompt Jet Et (1-elfrac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) << LQLogger::endmsg;
	      m_logger << INFO << "non prompt Jet Et (1-elfrac - phfrac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction() - jetColl.at(i).PhotonEnergyFraction() )) << LQLogger::endmsg;
	      
	      FillHist("nonprompt_e_closejet_Ecorr", (Et * (1. - jetColl.at(i).ElectronEnergyFraction()))  , weight, 0., 100., 50.);
              FillHist("nonprompt_e_closejet_Ecorr2", (Et * (1. - (jetColl.at(i).ElectronEnergyFraction() + jetColl.at(i).PhotonEnergyFraction()))  )  , weight, 0., 100., 50.);

	      FillHist("nonprompt_e_closejet_pt_corrEt", jetColl.at(i).Pt(), (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) , weight, 0., 200., 200., 0., 100., 100.);
            }
          }
	}
      }
    }
  }
    
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  
  int nbjet=0;
  for(int ij=0; ij <jetColl_lepveto.size(); ij++){
    if(jetColl_lepveto.at(ij).BtagProb() > 0.679) nbjet++;
  }
  
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(muonTightColl.size() ==2){
	if(muonTightColl.at(0).Charge() != muonTightColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  for(int ij=0; ij <jetColl.size(); ij++){
    for (int iel=0; iel < electronTightColl.size(); iel++){
      float dR = electronTightColl[iel].DeltaR(jetColl[ij]);
      if(dR< 0.4){
	//m_logger << INFO << " close jet to electron has pT diff = " << 100.*(electronTightColl[iel].Pt() - jetColl[ij].Pt()) / electronTightColl[iel].Pt() << LQLogger::endmsg;
	///m_logger << INFO << (electronTightColl.at(iel).PrimaryVertexDXY()/ electronTightColl.at(iel).PrimaryVertexDXYError())<< LQLogger::endmsg;
      }
    }    
  }
  /// count number of loose leptons
  int nloose_lep = muonVetoColl.size() + electronVetoColl.size();

  
  if(electronTightColl.size() ==  3) {
       m_logger << INFO << "Number of jets in tri electron event = " << jetColl_lepveto.size() << LQLogger::endmsg;
     
       FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
     }
  if(electronTightColl.size() ==  4)FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);


  
  if (electronTightColl.size() == 2) {      

    if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge()){      
      
      FillCutFlow("SS_t",weight);
      FillCLHist(sighist, "SSDiElectronTight", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
      
      if(nloose_lep == 2){
	FillCutFlow("SS_lvt_t",weight);
      
	if(jetColl_lepveto.size() > 1){
	  FillCutFlow("SS_dijet_t",weight);
	  FillCLHist(sighist, "SSDiElectronTight_DiJet", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);

	  bool pass_same_vertex= (electronTightColl.at(0).VertexIndex() == electronTightColl.at(1).VertexIndex());
	  bool fail_conv = true;
	  bool fail_d0=false;
	  bool ecalseeded= true;
	  bool pass_charge_cons=true;
	  
	  for(int i= 0; i < electronTightColl.size(); i++){
	    if(electronTightColl.at(i).MissingHits() == 0) fail_conv = false;
	    if(electronTightColl.at(i).HasMatchedConvPhot()) fail_conv = false; 
	    if((electronTightColl.at(i).PrimaryVertexDXY()/ electronTightColl.at(i).PrimaryVertexDXYError()) > 4.) {
	      fail_d0=true;
	    }
	    
	    if(!electronTightColl.at(i).EcalDrivenSeed()) ecalseeded = false;
	    if(!electronTightColl.at(i).GsfCtfScPixChargeConsistency()) pass_charge_cons=false;
	  }
	  
	  if(nbjet==0){
	    FillCutFlow("SS_0bj_t",weight);
	    if(pass_same_vertex) {
	      FillCutFlow("SS_sv_t",weight);
	      if(!fail_conv) {
		FillCutFlow("SS_noconv_t",weight);
		if(!fail_d0){
		  FillCutFlow("SS_d0_t",weight);
		  if(pass_charge_cons) FillCutFlow("SS_sc_t",weight);
		}
	      }
	    }
	  }
	}
      }
    }// SS 
  }

    

    /// Check all other el WPs
  if (electronMediumColl.size() == 2) {
    if(electronMediumColl.at(0).Charge() == electronMediumColl.at(1).Charge()){
      FillCLHist(sighist, "SSDiElectronMedium", eventbase->GetEvent(), muonTightColl,electronMediumColl,jetColl_lepveto, weight);    
      FillCLHist(elhist, "SSDiElectronMedium_Electrons", electronMediumColl, eventbase->GetEvent().JetRho(),weight);
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
	  FillCutFlow("SSDiEl_medium",weight);
        }
      } 
    }
  }

  if (electronMVAColl.size() == 2) {
    if(electronMVAColl.at(0).Charge() == electronMVAColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
	  FillCutFlow("SSDiEl_mva",weight);
	}
      }
    }
  }

      

  if (electronTrigTightColl.size() == 2) {
    if(electronTrigTightColl.at(0).Charge() == electronTrigTightColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
	if(nloose_lep == 2){
          FillCutFlow("SSDiEl_trigtight",weight);
        }
      }
    }
  }
  if (electronTrigWP70Coll.size() == 2) {
    if(electronTrigWP70Coll.at(0).Charge() == electronTrigWP70Coll.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
        if(nloose_lep == 2){
          FillCutFlow("SSDiEl_trigwp70",weight);
	}
      }
    }
  }
  
  if (electronEOPColl.size() == 2) {
    if(electronEOPColl.at(0).Charge() == electronEOPColl.at(1).Charge()){
      if(jetColl_lepveto.size() > 1){
        if(nloose_lep == 2){
          FillCutFlow("SSDiEl_eop",weight);
	}
      }
    }
  }
  

  
  
  return;
}// End of execute event loop

  
  
void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void HNDiElectron::BeginCycle() throw( LQError ){
  
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

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void HNDiElectron::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",13,0.,13.);


    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"SSDiEl_medium");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"SSDiEl_trigtight");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"SSDiEl_trigwp70");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"SSDiEl_eop");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"SS_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"SS_lv_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"SS_dijet_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"SS_0bj_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"SS_sv_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"SS_noconv_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"SS_d0_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"SS_sc_t");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(13,"SSDiEl_mva");
    
  }
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



