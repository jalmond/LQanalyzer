// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQFakeRateCalculator_El Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "FakeRateCalculator_El.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (FakeRateCalculator_El);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
FakeRateCalculator_El::FakeRateCalculator_El() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("FakeRateCalculator_El");

  Message("In FakeRateCalculator_El constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void FakeRateCalculator_El::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  MakeCleverHistograms(sighist, "DiLooseEl");
  MakeCleverHistograms(sighist, "ZDiLooseEl");
  MakeCleverHistograms(sighist, "DiTightEl");
  MakeCleverHistograms(sighist, "SingleLooseEl");
  MakeCleverHistograms(sighist, "SingleTightEl");
  MakeCleverHistograms(sighist, "LooseEl");
  MakeCleverHistograms(sighist, "TightEl");
     
   return;
}


void FakeRateCalculator_El::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
    
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
  /// Single Trigger List 
  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  triggerslist.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");

  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(eventbase->GetEvent().PileUpInteractionsTrue())* MCweight;
  }
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_FAKELOOSE);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.4);
  eventbase->GetElectronSel()->Selection(electronLooseColl);
  
  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->SetID(BaseSelection::EGAMMA_TIGHT);
  eventbase->GetElectronSel()->SetPt(20);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronTightColl);

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
  

  if(muonTightColl.size() > 0) return;
  /// Get p rate
  
  if(PassTrigger(triggerslist_diel, prescale)){
    if(electronLooseColl.size() == 2){
      FillCLHist(sighist, "DiLooseEl", eventbase->GetEvent(), muonTightColl,electronLooseColl,jetColl_lepveto, weight);
      snu::KParticle Z = electronLooseColl.at(0) + electronLooseColl.at(1);
      
      if(Z.M() > 81. && Z.M() < 101.){
	FillCLHist(sighist, "ZDiLooseEl", eventbase->GetEvent(), muonTightColl,electronLooseColl,jetColl_lepveto, weight);
	
	
	//// Electron 1 IS TAG
	if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho())  ){
	  
	  FillHist("h_promptrate_denom_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  FillHist("h_promptrate_denom_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	  FillHist("h_promptrate_denom_njets", jetColl_lepveto.size(), weight, 0., 5.,5);
	  if(electronLooseColl.at(1).IsEBFiducial()){
	    FillHist("h_promptrate_denom_barrel_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  }
	  else if(electronLooseColl.at(1).IsEEFiducial()){
	    FillHist("h_promptrate_denom_endcap_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	  }
	  
	  /// Electron 2 is probe
	  if(IsTight(electronLooseColl.at(1), eventbase->GetEvent().JetRho()) ){
	    FillHist("h_promptrate_num_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    FillHist("h_promptrate_num_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	    FillHist("h_promptrate_num_njets", jetColl_lepveto.size(), weight, 0., 5.,5);
	    if(electronLooseColl.at(1).IsEBFiducial()){
	      FillHist("h_promptrate_num_barrel_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    }
	    else if(electronLooseColl.at(1).IsEEFiducial()){
	      FillHist("h_promptrate_num_endcap_pt", electronLooseColl.at(1).Pt(), weight, 0., 200.,40);
	    }
	  }
	}
	
	//// Electron 2 IS TAG
	if(IsTight(electronLooseColl.at(1), eventbase->GetEvent().JetRho())){
	  
          FillHist("h_promptrate_denom_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          FillHist("h_promptrate_denom_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	  FillHist("h_promptrate_denom_njets", jetColl_lepveto.size(), weight, 0., 5.,5);
	  if(electronLooseColl.at(0).IsEBFiducial()){
            FillHist("h_promptrate_denom_barrel_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          }
          else if(electronLooseColl.at(0).IsEEFiducial()){
            FillHist("h_promptrate_denom_endcap_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
          }
	  
	  //// Electron 1 is probe
          if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho())){
            FillHist("h_promptrate_num_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
            FillHist("h_promptrate_num_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	    FillHist("h_promptrate_num_njets", jetColl_lepveto.size(), weight, 0., 5.,5);
	    if(electronLooseColl.at(0).IsEBFiducial()){
	      FillHist("h_promptrate_num_barrel_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
	    }
	    else if(electronLooseColl.at(0).IsEEFiducial()){
	      FillHist("h_promptrate_num_endcap_pt", electronLooseColl.at(0).Pt(), weight, 0., 200.,40);
	    }

          }
	}      	
      }
    }
    if(electronTightColl.size() == 2.)FillCLHist(sighist, "DiTightEl", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  }
  
  if(!PassTrigger(triggerslist, prescale)) return;
  /// Z and W veto
  Double_t temp_MT=0;
  Double_t MT=0;

  if (electronLooseColl.size() == 1)FillCLHist(sighist, "SingleLooseEl", eventbase->GetEvent(), muonTightColl,electronLooseColl,jetColl_lepveto, weight); 
  if (electronLooseColl.size() == 1 && electronTightColl.size() == 1)FillCLHist(sighist, "SingleTightEl", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight); 
  
  
  for(unsigned int w = 0; w < electronLooseColl.size();  w++){
    
    temp_MT = sqrt(2.* electronLooseColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( electronLooseColl.at(w).Phi()- eventbase->GetEvent().PFMETphi())) );
    if ( temp_MT > MT) 
      MT = temp_MT;
  }
  
  
  if(! (eventbase->GetEvent().PFMET()  < 20. && MT < 20.)) return;
  
  bool useevent= false;
  /// Fake Rates

  if (electronLooseColl.size() == 1  && jetColl_lepveto.size() >= 1){
    
    for (int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for( int ij=0; ij < jetColl_lepveto.size(); ij++){
	
        float dr = electronLooseColl.at(ielT).DeltaR(jetColl_lepveto.at(ij));
        if(dr > 1.) useevent = true;
      }
    }
  }
  
  if(!useevent) return;

  
  if (electronLooseColl.size() == 1 && electronTightColl.size() == 1 && jetColl_lepveto.size() >= 1){
    
    FillHist("TightEl_eta", electronTightColl.at(0).Eta(), weight, -2.5, 2.5,50); 
    FillHist("TightEl_pt", electronTightColl.at(0).Pt(), weight, 0.,200.,50);     
    FillHist("TightEl_njets", jetColl_lepveto.size(), weight, 0.,5.,5); 
    
    FillCLHist(sighist, "TightEl", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  }

  if (electronLooseColl.size() == 1 &&jetColl_lepveto.size() >= 1){
    FillHist("LooseEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
    FillHist("LooseEl_pt", electronLooseColl.at(0).Pt(), weight, 0.,200.,50);
    FillHist("LooseEl_njets", jetColl_lepveto.size(), weight, 0.,5.,5); 
    FillCLHist(sighist, "LooseEl", eventbase->GetEvent(), muonTightColl,electronLooseColl,jetColl_lepveto, weight);
  }

  
  
  return;
}// End of execute event loop



void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}

bool FakeRateCalculator_El::IsTight(snu::KElectron el, double jetrho ){
  //----------------------------------------------------------------------
  // Barrel electron cut values
  //----------------------------------------------------------------------

  double l_b_dEtaIn  = 0.004;
  double l_b_dPhiIn  = 0.03;
  double l_b_sieie   = 0.01;
  double l_b_hoe     = 0.12;
  double l_b_d0      = 0.1;
  double l_b_dZ      = 0.1;
  double l_b_ep      = 0.05;
  double l_b_pfRelIso =0.1;
  double l_b_vtxProb = 1e-6;
  int    l_b_missHits = 0;
  //----------------------------------------------------------------------
  // Endcap electron cut values
  //----------------------------------------------------------------------

  double l_e_dEtaIn  = 0.005;
  double l_e_dPhiIn  = 0.02;
  double l_e_sieie   = 0.03;
  double l_e_hoe     = 0.10;
  double l_e_d0      = 0.02;
  double l_e_dZ      = 0.1;
  double l_e_ep      = 0.05;
  double l_e_vtxProb = 1e-6;
  int    l_e_missHits = 0;
  double l_e_pfRelIso = 0.1;
  //----------------------------------------------------------------------
  // Bools that depend on barrel vs. endcap
  //----------------------------------------------------------------------

  bool   pass_deltaEta      = false;
  bool   pass_deltaPhi      = false;
  bool   pass_sigmaIEtaIEta = false;
  bool   pass_hoe           = false;
  bool   pass_vtxDistXY     = false;
  bool   pass_vtxDistZ      = false;
  bool   pass_ep            = false;
  bool   pass_convFitProb   = false;
  bool   pass_missingHits   = false;
  bool   pass_pfIsolation   = false;



  //----------------------------------------------------------------------
  // Define EGamma ep parameter
  //----------------------------------------------------------------------

  double egamma_e  = el.CaloEnergy();
  double egamma_p  = el.CaloEnergy() / el.ESuperClusterOverP();
  double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

  //----------------------------------------------------------------------
  // Define PF Isolation
  //----------------------------------------------------------------------

  double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
  double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
  double effective_areas_03             [7] = { 0.100, 0.120, 0.085, 0.110, 0.120, 0.120, 0.130 };
  double effective_area_03  = 0.0;


  for (int i = 0; i < 7; ++i ){
    double bin_minimum = effective_area_eta_minimums[i];
    double bin_maximum = effective_area_eta_maximums[i];
    if ( fabs(el.SCEta()) >= bin_minimum && fabs(el.SCEta()) < bin_maximum ) {
      effective_area_03 = effective_areas_03 [i];
    }
  }

  double egamma_pfiso_03 = el.PFChargedHadronIso03() + std::max ( el.PFPhotonIso03() + el.PFNeutralHadronIso03() - ( jetrho * effective_area_03 ), 0.0 );


  egamma_pfiso_03 /= el.Pt();

  //----------------------------------------------------------------------
  // Barrel electron test
  //----------------------------------------------------------------------

  if ( fabs(el.SCEta()) < 1.479 ){

    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_b_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_b_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_b_sieie   );
    pass_hoe           = bool ( el.HoE            ()  <= l_b_hoe     );
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_b_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_b_dZ  );
    pass_ep            = bool ( egamma_ep          <= l_b_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_b_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_b_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_b_pfRelIso);
  }

  else if ( fabs(el.SCEta()) > 1.479 && fabs(el.SCEta()) < 2.5 ){
    pass_deltaEta      = bool ( fabs(el.DeltaEta())   <= l_e_dEtaIn);
    pass_deltaPhi      = bool ( fabs(el.DeltaPhi())   <= l_e_dPhiIn );
    pass_sigmaIEtaIEta = bool ( el.SigmaIEtaIEta()    <= l_e_sieie   );
    pass_hoe           = bool ( el.HoE            ()  <= l_e_hoe     );
    pass_vtxDistXY     = bool ( fabs(el.LeadVtxDistXY())  <= l_e_d0   );
    pass_vtxDistZ      = bool ( fabs(el.LeadVtxDistZ ())  <= l_e_dZ  );
    pass_ep            = bool ( egamma_ep          <= l_e_ep   );
    pass_convFitProb   = bool ( el.ConvFitProb  ()    <= l_e_vtxProb);
    pass_missingHits   = bool ( el.MissingHits()    <= l_e_missHits);
    pass_pfIsolation   = bool ( egamma_pfiso_03    <= l_e_pfRelIso);

  }  bool decision = (
                      pass_deltaEta      &&
		      pass_deltaPhi      &&
		      pass_sigmaIEtaIEta &&
		      pass_hoe           &&
		      pass_vtxDistXY     &&
		      pass_vtxDistZ      &&
                       pass_ep            &&
		      pass_pfIsolation   &&
		      pass_convFitProb   &&
		      pass_missingHits   ) ;
  
  return decision;
}



void FakeRateCalculator_El::BeginCycle() throw( LQError ){
  
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

FakeRateCalculator_El::~FakeRateCalculator_El() {
  
  Message("In FakeRateCalculator_El Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void FakeRateCalculator_El::FillCutFlow(TString cut, float weight){

  
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


void FakeRateCalculator_El::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void FakeRateCalculator_El::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this FakeRateCalculator_ElCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void FakeRateCalculator_El::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



