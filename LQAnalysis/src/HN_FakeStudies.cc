// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHN_FakeStudies Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HN_FakeStudies.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HN_FakeStudies);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HN_FakeStudies::HN_FakeStudies() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HN_FakeStudies");

  Message("In HN_FakeStudies constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  
  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_njet=0, k_ht=0.;
  k_nbjet_l=-1;
  k_nbjet_m=-1;
  k_nbjet_t=-1;
  k_weight=0.;
  k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  
  
  // Signal plots
  //  MakeCleverHistograms(sighist,"TriElCR_dijet_highmet_osZW");
  

}


void HN_FakeStudies::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HN_FakeStudies::ExecuteEvents()throw( LQError ){
  
  k_met=0., k_eemass=0., k_eejjmass=0., k_e1jjmass=0., k_e2jjmass=0.,  k_st=0., k_njet=0, k_ht=0.;
  k_weight=0.;
  k_el1pt=0., k_el2pt=0., k_j1pt=0., k_jjmass=0.;
  k_nbjet_l=-1,k_nbjet_m=-1,k_nbjet_t=-1;
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  triggerslist.push_back("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  if(!PassTrigger(triggerslist, prescale))  throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  /// now has emu event  
  
  if (MC_pu&&!k_isdata) 
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;

 

  /// ELECTRONS
  //GetElectrons(                                                                                            keepCF, keepNP applyIDSF )

  //// Get the collection of electrons
  std::vector<snu::KElectron> electronAnalysisColl                   = GetElectrons(false, true, "Analysis_loosereg1" , weight);
  std::vector<snu::KElectron> electronVetoColl       = GetElectrons(false, false, "veto"); 
  
  
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl  = GetMuons("veto");
  std::vector<snu::KMuon> muonTightColl  = GetMuons("tight");

  /// JETS
  std::vector<snu::KJet> jetColl_lepveto_mva = GetJets("ApplyPileUpID");


  if(NBJet(jetColl_lepveto_mva) == 0){
    
    if(muonTightColl.size()==1&&muonVetoColl.size()==1){

      Double_t METdphi_muon= TVector2::Phi_mpi_pi(muonTightColl.at(0).Phi()- eventbase->GetEvent().PFMETphi());
      Double_t MT_muon = sqrt(2.* muonTightColl.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi_muon)));

      if(MT_muon > 60. && MT_muon < 100){
	
	if(electronAnalysisColl.size() == 1 && electronVetoColl.size()==1){
	  if(electronAnalysisColl.at(0).Charge() == muonTightColl.at(0).Charge()){
	    if(k_running_nonprompt){
	      float f = m_fakeobj->getFakeRate_electronEta(0, electronAnalysisColl.at(0).Pt(), fabs(electronAnalysisColl.at(0).Eta()), "40");
	      weight  *= f;
	    }
	    if(jetColl_lepveto_mva.size() ==1)FillCLHist(sighist, "EMU_1jet", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(jetColl_lepveto_mva.size() ==2)FillCLHist(sighist, "EMU_2jet", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(jetColl_lepveto_mva.size() ==0)FillCLHist(sighist, "EMU_0jet", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
	    if(jetColl_lepveto_mva.size() ==1)FillCLHist(sighist, "EMU_1jet_now", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, 1.);
            if(jetColl_lepveto_mva.size() ==2)FillCLHist(sighist, "EMU_2jet_now", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, 1.);
            if(jetColl_lepveto_mva.size() ==0)FillCLHist(sighist, "EMU_0jet_now", eventbase->GetEvent(), muonVetoColl, electronAnalysisColl,jetColl_lepveto_mva, 1.);
	  }
	}
      }
    }
  }
  
  
  return;
}// End of execute event loop



void HN_FakeStudies::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void HN_FakeStudies::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  
  DeclareVariable(k_met, "met", "MyTree");
  DeclareVariable(k_eemass, "ee_mass", "MyTree");
  DeclareVariable(k_eejjmass, "eejj_mass", "MyTree");
  DeclareVariable(k_e1jjmass, "e1jj_mass", "MyTree");
  DeclareVariable(k_e2jjmass, "e2jj_mass", "MyTree");
  DeclareVariable(k_njet, "njet", "MyTree");
  DeclareVariable(k_nbjet_l , "nbjet_l",  "MyTree");
  DeclareVariable(k_nbjet_m , "nbjet_m",  "MyTree");
  DeclareVariable(k_nbjet_t , "nbjet_t",  "MyTree");
  DeclareVariable(k_jjmass, "jj_mass", "MyTree");
  DeclareVariable(k_st, "st", "MyTree");
  DeclareVariable(k_ht, "ht", "MyTree");
  DeclareVariable(k_el1pt, "el1_pt", "MyTree");
  DeclareVariable(k_el2pt, "el2_pt", "MyTree");
  DeclareVariable(k_j1pt, "jet1_pt", "MyTree");
  DeclareVariable(k_weight, "weight", "MyTree");
  return;
  
}

HN_FakeStudies::~HN_FakeStudies() {
  
  Message("In HN_FakeStudies Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     



void HN_FakeStudies::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HN_FakeStudies::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HN_FakeStudiesCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HN_FakeStudies::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}




//  LocalWords:  masscuts jetResdown
