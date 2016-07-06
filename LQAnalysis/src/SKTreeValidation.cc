// $Id: SKTreeValidation.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQSKTreeValidation Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "SKTreeValidation.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"


//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (SKTreeValidation);


 /**
  *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
  *
  */
SKTreeValidation::SKTreeValidation() :  AnalyzerCore(), out_muons(0)  {
  
  rmcor = new rochcor2015();
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("SKTreeValidation");
  
  Message("In SKTreeValidation constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  MakeCleverHistograms(sighist_mm,"DiMuon");
  MakeCleverHistograms(sighist_mm,"DiMuon_corr");
  MakeCleverHistograms(sighist_mm,"DiMuon_truthmatched");
  MakeCleverHistograms(sighist_ee,"DiElectron");
  MakeCleverHistograms(sighist_ee,"DiElectron_truthmatched");
  MakeCleverHistograms(sighist_em,"ElMuon");
  
  MakeCleverHistograms(jehist, "DiMuon_dijet");
  MakeCleverHistograms(jehist, "DiMuon_dijet_tchannel");
  MakeCleverHistograms(jehist, "EMuon_dijet");
  MakeCleverHistograms(jehist, "EMuon_dijet_tchannel");
  MakeCleverHistograms(jehist, "DiElectron_dijet");
  MakeCleverHistograms(jehist, "DiElectron_dijet_tchannel");
}


void SKTreeValidation::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  Message("Making clever hists for Z ->ll test code", INFO);
  
  /// only available in v7-6-X branch and newer
  //// default lumimask is silver ////
  //// In v7-6-2-(current) the default is changed to gold (since METNoHF bug)
  ///When METNoHF isfixed the default will be back to silver
  /// set to gold if you want to use gold json in analysis
  /// To set uncomment the line below:
  //ResetLumiMask(snu::KEvent::gold);


  return;
}


void SKTreeValidation::ExecuteEvents()throw( LQError ){

  /// Apply the gen weight 
  if(!isData) weight*=MCweight;
  
  /// Acts on data to remove bad reconstructed event 
  if(isData&& (! eventbase->GetEvent().LumiMask(lumimask))) return;
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
   
  FillCutFlow("NoCut", weight);
  FillHist("GenWeight" , 1., MCweight,  0. , 2., 2);
  
  if(isData) FillHist("Nvtx_nocut_data",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  else  FillHist("Nvtx_nocut_mc",  eventbase->GetEvent().nVertices() ,weight, 0. , 50., 50);
  
   ///#### CAT:::PassBasicEventCuts is updated: uses selections as described in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters: If you see this is out of date please comment
   
   if(!PassBasicEventCuts()) return;     /// Initial event cuts : 
   FillCutFlow("EventCut", weight);

   /// #### CAT::: triggers stored are all HLT_Ele/HLT_DoubleEle/HLT_Mu/HLT_TkMu/HLT_Photon/HLT_DoublePhoton

   std::vector<TString> triggerslist_mu;
   triggerslist_mu.push_back("HLT_IsoMu20_v");
   std::vector<TString> triggerslist_el;
   triggerslist_el.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
   std::vector<TString> triggerslist_emu;
   triggerslist_emu.push_back("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v");
   triggerslist_emu.push_back("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v");
   
   float mu_trigger_ps_weight= ApplyPrescale("HLT_IsoMu20", TargetLumi,lumimask);
   float el_trigger_ps_weight= ApplyPrescale("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", TargetLumi,lumimask);
   float emu_trigger_ps_weight= ApplyPrescale("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v", TargetLumi,lumimask);
   
   
   bool mu_pass= PassTrigger(triggerslist_mu, prescale);
   bool el_pass= PassTrigger(triggerslist_el, prescale);
   bool emu_pass= PassTrigger(triggerslist_emu, prescale);
   

   FillCutFlow("TriggerCut", weight);
   // Trigger matching is done using KMuon::TriggerMatched(TString) which returns a bool

   /* // #### CAT::: trigger matching information is stored for muons and electrons for:
  ///HLT_IsoMu24_eta2p1_v
  ///HLT_Mu17_Mu8_DZ_v
  ///HLT_Mu17_TkMu8_DZ_v
   //HLT_IsoMu20
   ///HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v
   ///HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele12_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v
   ///HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v
   ///HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_
   ///HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v
   ///HLT_Ele27_eta2p1_WPLoose_Gsf_TriCentralPFJet30_v
   */

   m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;


   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
   /// Has Good Primary vertex:
   /// if ( vtx.ndof() > 4 &&
   //   ( (maxAbsZ <=0 ) || std::abs(vtx.z()) <= 24 ) &&
   //( (maxd0 <=0 ) || std::abs(vtx.position().rho()) <= 2 ) &&
   //!(vtx.isFake() ) ){
   FillCutFlow("VertexCut", weight);
   

   /// List of preset muon collections : Can call also POGSoft/POGLoose/POGMedium/POGTight
   std::vector<snu::KMuon> muonVetoColl = GetMuons(BaseSelection::MUON_HN_VETO);  // veto selection
   std::vector<snu::KMuon> muonLooseColl = GetMuons(BaseSelection::MUON_HN_FAKELOOSE);  // loose selection
   std::vector<snu::KMuon> muonTightColl = GetMuons(BaseSelection::MUON_POG_TIGHT); // tight selection : NonPrompt MC lep removed
   std::vector<snu::KMuon> muonTightCorrColl = GetMuons(BaseSelection::MUON_POG_TIGHT); // tight selection : NonPrompt MC lep removed
   std::vector<snu::KMuon> muonTightTruthMatchedColl = GetMuons(BaseSelection::MUON_POG_TIGHT,false); // tight selection : NonPrompt MC lep removed
   
   CorrectMuonMomentum(muonTightCorrColl);
   
   /// List of preset jet collections : NoLeptonVeto/Loose/Medium/Tight/TightLepVeto/HNJets
   std::vector<snu::KJet> jetColl             = GetJets(BaseSelection::JET_NOLEPTONVETO); // All jets
   std::vector<snu::KJet> jetColl_hn          = GetJets(BaseSelection::JET_HN);// pt > 20 ; eta < 2.5; PFlep veto; pileup ID
   std::vector<snu::KJet> jetColl_hn_t          = GetJets(BaseSelection::JET_HN_TChannel);

   FillHist("Njets", jetColl_hn.size() ,weight, 0. , 5., 5);

   /// can call POGVeto/POGLoose/POGMedium/POGTight/ HNVeto/HNLoose/HNTight/NoCut/NoCutPtEta 
   std::vector<snu::KElectron> electronTightColl             = GetElectrons(BaseSelection::ELECTRON_POG_TIGHT);
   std::vector<snu::KElectron> electronTightTruthMatchedColl             = GetElectrons(false,false,BaseSelection::ELECTRON_POG_TIGHT);
   std::vector<snu::KElectron> electronLooseColl        = GetElectrons(BaseSelection::ELECTRON_POG_LOOSE);

   
   float mu_weight_trigger_sf = TriggerScaleFactor(electronTightColl, muonTightColl, "HLT_IsoMu20");
   float el_weight_trigger_sf = TriggerScaleFactor(electronTightColl, muonTightColl, "HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
   float emu_weight_trigger_sf = TriggerScaleFactor(electronTightColl, muonTightColl, "HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

   float muon_id_iso_sf= MuonScaleFactor(BaseSelection::MUON_POG_TIGHT, muonTightColl,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT
   float el_id_iso_sf= ElectronScaleFactor(BaseSelection::ELECTRON_POG_TIGHT, electronTightColl);
   float elmuon_id_iso_sf= MuonScaleFactor(BaseSelection::MUON_POG_TIGHT, muonTightColl,0); ///MUON_POG_TIGHT == MUON_HN_TIGHT
   elmuon_id_iso_sf *= ElectronScaleFactor(BaseSelection::ELECTRON_POG_TIGHT, electronTightColl);
   
   int njet = jetColl_hn.size();
   FillHist("GenWeight_NJet" , njet*MCweight + MCweight*0.1, 1., -6. , 6., 12);

   numberVertices = eventbase->GetEvent().nVertices();   
   
   float pileup_reweight_69=(1.0);
   float pileup_reweight_71=(1.0);
   if (!k_isdata) {
     // check if catversion is empty. i.ie, v-7-4-X in which case use reweight class to get weight. In v-7-6-X+ pileupweight is stored in KEvent class, for silver/gold json
     pileup_reweight_69 = eventbase->GetEvent().PileUpWeight(lumimask);
     pileup_reweight_71 = eventbase->GetEvent().AltPileUpWeight(lumimask);
     
   }
   
   FillHist("PileupWeight_69" ,  pileup_reweight_69,weight,  0. , 50., 10);
   FillHist("PileupWeight_71" ,  pileup_reweight_71,weight,  0. , 50., 10);

   float mu_weight=1.;
   float el_weight=1.;
   float emu_weight=1.;
   if(!isData && !k_running_nonprompt){
     mu_weight*=muon_id_iso_sf;
     mu_weight*=mu_weight_trigger_sf;
     mu_weight*=mu_trigger_ps_weight;
   }
   if(!isData && !k_running_nonprompt){
     el_weight*=el_id_iso_sf;
     el_weight*=el_weight_trigger_sf;
     el_weight*=el_trigger_ps_weight;
   }
   if(!isData && !k_running_nonprompt){
     emu_weight*=elmuon_id_iso_sf;
     emu_weight*=emu_weight_trigger_sf;
     emu_weight*=emu_trigger_ps_weight;
   }

   if(mu_pass&&muonTightColl.size() ==2) {
     if(!SameCharge(muonTightColl)){
       if(muonTightColl.at(1).Pt() > 20.){
	 if(GetDiLepMass(muonTightColl) < 120. && GetDiLepMass(muonTightColl)  > 60. ){
	   FillHist("zpeak_mumu_nopurw", GetDiLepMass(muonTightColl), weight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 200.,400);
	   FillHist("zpeak_mumu_purw", GetDiLepMass(muonTightColl), weight*pileup_reweight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 200.,400);
	   FillHist("zpeak_mumu_altpurw", GetDiLepMass(muonTightColl), weight*altpileup_reweight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 200.,400);
	   FillHist("nvertex_mumu_nopurw", eventbase->GetEvent().nVertices(),  weight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 40.,40);
	   FillHist("nvertex_mumu_purw", eventbase->GetEvent().nVertices()  , pileup_reweight*weight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 40.,40) ;
	   FillHist("nvertex_mumu_altpurw", eventbase->GetEvent().nVertices(),  altpileup_reweight*weight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight, 0., 40.,40);
	   
	 }
	 float ev_weight = weight*altpileup_reweight*mu_trigger_ps_weight*mu_weight_trigger_sf*mu_id_weight*mu_reco_weight;
	 FillCLHist(sighist_mm, "DiMuon", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_hn, ev_weight);
	 FillCLHist(sighist_mm, "DiMuon_corr", eventbase->GetEvent(), muonTightCorrColl,electronTightColl,jetColl_hn, ev_weight);
	 
	 if(jetColl_hn.size() == 2)          FillCLHist(jethist, "DiMuon_dijet", jetColl_hn, ev_weight);
	 if(jetColl_hn_t.size() == 2)          FillCLHist(jethist, "DiMuon_dijet_tchannel", jetColl_hn_t, ev_weight);
	 
	 
	 if(muonTightTruthMatchedColl.size() == 2)         FillCLHist(sighist_mm, "DiMuon_truthmatched", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_hn, ev_weight);
	 
       }
     }
   }

   if(el_pass&&electronTightColl.size() ==2) {
     if(!SameCharge(electronTightColl)){
       if(electronTightColl.at(1).Pt() > 20.){
	 /// Method of plotting single histogram
	 if(GetDiLepMass(electronTightColl) < 120. && GetDiLepMass(electronTightColl)  > 60. ){
	   FillHist("zpeak_ee_nopurw", GetDiLepMass(muonTightColl), weight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 200.,400);
	   FillHist("zpeak_ee_purw", GetDiLepMass(muonTightColl), weight*pileup_reweight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 200.,400);
	   FillHist("zpeak_ee_altpurw", GetDiLepMass(muonTightColl), weight*altpileup_reweight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 200.,400);
	   FillHist("nvertex_ee_nopurw", eventbase->GetEvent().nVertices(),  weight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 40.,40);
	   FillHist("nvertex_ee_purw", eventbase->GetEvent().nVertices()  , pileup_reweight*weight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 40.,40) ;
	   FillHist("nvertex_ee_altpurw", eventbase->GetEvent().nVertices(),  altpileup_reweight*weight*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight, 0., 40.,40);
	 }
	 if(electronTightTruthMatchedColl.size() ==2)            FillCLHist(sighist_ee, "DiElectron_truthmatched", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_hn, weight*el_weight*pileup_reweight_71*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight);
	 
	 FillCLHist(sighist_ee, "DiElectron", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_hn, weight*pileup_reweight_71*el_trigger_ps_weight*el_weight_trigger_sf*el_id_weight*el_reco_weight);

	 if(jetColl_hn.size() == 2)          FillCLHist(jethist, "DiElectron_dijet", jetColl_hn, ev_weight);
         if(jetColl_hn_t.size() == 2)          FillCLHist(jethist, "DiElectron_dijet_tchannel", jetColl_hn_t, ev_weight);
       }
     }
   }
   
   if(emu_pass&&(electronTightColl.size() == 1)&& (muonTightColl.size() ==1)) {
     if(electronTightColl.at(0).Charge() != muonTightColl.at(0).Charge()){
       if((muonTightColl.at(0).Pt() > 20. )&&( electronTightColl.at(0).Pt() < 20.)){
	 /// Method of plotting single histogram

	 FillHist("zpeak_emu_nopurw", GetDiLepMass(muonTightColl), weight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight, 0., 200.,400);
	 FillHist("zpeak_emu_purw", GetDiLepMass(muonTightColl), weight*pileup_reweight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight, 0., 200.,400);
	 FillHist("zpeak_emu_altpurw", GetDiLepMass(muonTightColl), weight*altpileup_reweight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight,0., 200.,400);
	 FillHist("nvertex_emu_nopurw", eventbase->GetEvent().nVertices(),  weight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight, 0., 40.,40);
	 FillHist("nvertex_emu_purw", eventbase->GetEvent().nVertices()  , pileup_reweight*weight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight, 0., 40.,40) ;
	 FillHist("nvertex_emu_altpurw", eventbase->GetEvent().nVertices(),  altpileup_reweight*weight*emu_trigger_ps_weight*emu_weight_trigger_sf*emu_id_weight*emu_reco_weight, 0., 40.,40);
	 
	 FillCLHist(sighist_em, "EMuon", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_hn, weight*emu_weight*pileup_reweight_71);
	 if(jetColl_hn.size() == 2)          FillCLHist(jethist, "EMuon_dijet", jetColl_hn, ev_weight);
         if(jetColl_hn_t.size() == 2)          FillCLHist(jethist, "EMuon_dijet_tchannel", jetColl_hn_t, ev_weight);

       }
     }
   }
   
   return;
}// End of execute event loop
  


void SKTreeValidation::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void SKTreeValidation::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "SNUCAT_Pileup.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

SKTreeValidation::~SKTreeValidation() {
  
  Message("In SKTreeValidation Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void SKTreeValidation::FillCutFlow(TString cut, float weight){

  
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


void SKTreeValidation::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void SKTreeValidation::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this SKTreeValidationCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void SKTreeValidation::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



