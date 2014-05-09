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
   MakeCleverHistograms(sighist,  "SSDiElectronTight");
   MakeCleverHistograms(sighist,  "SSDiElectronTight_DiJet");
   MakeCleverHistograms(sighist,  "SSSR0");
   
   MakeCleverHistograms(sighist,  "NoCut");
   MakeCleverHistograms(sighist,  "TriEl");
   MakeCleverHistograms(sighist,  "ZZ");

   MakeCleverHistograms(sighist,  "SSeeJJ");
   MakeCleverHistograms(sighist,  "SSeeJJnoph");
   MakeCleverHistograms(sighist,  "SSeeJJnoph_noZ");

   
   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){
  
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  FillCutFlow("NoCut", weight);
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  FillCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
    
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillCutFlow("VertexCut", weight);

  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;
  

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// ELECTRONS
  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);
 
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);

  std::vector<snu::KElectron> electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  
  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);
  
  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.4);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonTightColl, electronTightColl);
  eventbase->GetJetSel()->Selection(jetColl);

  m_logger << DEBUG << "filled vectors "<< LQLogger::endmsg;

  return;
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl_lepveto, weight);
  
  //if(electronTightColl.size() != 2 ) return;
  //if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge()) return;
  //if(jetColl.size() < 2) return;
  
  m_logger << DEBUG << "Filled SSeeJJ "<< LQLogger::endmsg;
  
  FillCLHist(sighist, "SSeeJJ", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  
  m_logger << INFO << "SSeeJJ event "<< LQLogger::endmsg;

  for(int ip=0; ip < PhotonEta->size() ; ip++){
    if(PhotonHasMatchedPromptEle->at(ip) ) {
      m_logger << INFO << "Failed PhotonHasMatchedPromptEle" << LQLogger::endmsg;
      continue;
    }
    if(PhotonHoE->at(ip) > 0.05) {
      m_logger << INFO << "Failed PhotonHoE " << LQLogger::endmsg;
      continue;
    }
    if(PhotonHasPixelSeed->at(ip)) {
      m_logger << INFO << "Failed PhotonHasPixelSeed"<< LQLogger::endmsg;
      continue;
    }
    if(PhotonSCeta->at(ip) < 1.479) {
      if(PhotonSigmaIEtaIEta->at(ip) > 0.011) {
	m_logger << INFO << "Failed PhotonSigmaIEtaIEta"<< LQLogger::endmsg;
	continue;
      }
      if(PhotonTrkIsoHollowDR04->at(ip) > (2. + 0.001*PhotonPt->at(ip) + 0.0167 *rhoJets)) {
	m_logger << INFO << "Failed  PhotonTrkIsoHollowDR04" << LQLogger::endmsg;
	continue;
      }
      if(PhotonEcalIsoDR04->at(ip) > (4.2 + 0.006*PhotonPt->at(ip) + 0.183*rhoJets)) {
	m_logger << INFO << "Failed  PhotonEcalIsoDR04" << LQLogger::endmsg;
	continue;
      }
      if(PhotonHcalIsoDR04->at(ip) > (2.2 + 0.0025*PhotonPt->at(ip) +0.062*rhoJets)){
	m_logger << INFO << "Failed  PhotonHcalIsoDR04" << LQLogger::endmsg;
	continue;
      }
    }
    else{
      if(PhotonSigmaIEtaIEta->at(ip) > 0.03) {
	m_logger << INFO << "Failed PhotonSigmaIEtaIEta"<< LQLogger::endmsg;
	continue;
      }
      if(PhotonTrkIsoHollowDR03->at(ip) > (2. + 0.001*PhotonPt->at(ip) + 0.032 *rhoJets)) {
	m_logger << INFO << "Failed  PhotonTrkIsoHollowDR04" << LQLogger::endmsg;
	continue;
      }
      if(PhotonEcalIsoDR04->at(ip) > (4.2 + 0.006*PhotonPt->at(ip) + 0.090*rhoJets)){
	m_logger << INFO << "Failed  PhotonEcalIsoDR04" << LQLogger::endmsg;
	continue;
      }
      if(PhotonHcalIsoDR04->at(ip) > (2.2 + 0.0025*PhotonPt->at(ip) +0.18*rhoJets)){
	m_logger << INFO << "Failed  PhotonHcalIsoDR04" << LQLogger::endmsg;
	continue;
     }
    }
    m_logger << INFO << "Event has Tight photon" << LQLogger::endmsg;
    return;
  }
  
  m_logger << DEBUG << "Filled SSeeJJnoph "<< LQLogger::endmsg;
  FillCLHist(sighist, "SSeeJJnoph", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  m_logger << DEBUG << "Making Z" << LQLogger::endmsg;
  snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
  if(fabs( Z.M() - 90.)  < 10.){
    m_logger << INFO << "Event has mass close to Z" << LQLogger::endmsg;
    return;
  }
  FillCLHist(sighist, "SSeeJJnoph_noZ", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
  
  
  bool prompt_prompt = false;
  bool prompt_nonprompt = false;
  bool nonprompt_nonprompt = false;
  bool prompt_chargeflip = false;

  m_logger << INFO << "Number of electrons == " << electronTightColl.size() << LQLogger::endmsg;
  
  for(int iel = 0; iel < electronTightColl.size(); iel++){
    m_logger << INFO << "El number:  " <<  iel+1  << LQLogger::endmsg;
    
    if(electronTightColl[iel].Charge() == -1){
      
      if(electronTightColl[iel].MatchedGenParticlePt() == -999)  m_logger << INFO << "El- pt/eta/phi = " << electronTightColl[iel].Pt() << " / " << electronTightColl[iel].Eta() << " / " << electronTightColl[iel].Phi() << LQLogger::endmsg;
      else m_logger << INFO << "El- pt/eta/phi = " << electronTightColl[iel].MatchedGenParticlePt() << " / " << electronTightColl[iel].MatchedGenParticleEta() << " / " <<electronTightColl[iel].MatchedGenParticlePhi() << LQLogger::endmsg;
    }
    else {
      if(electronTightColl[iel].MatchedGenParticlePt() == -999)  m_logger << INFO << "El+ pt/eta/phi = " << electronTightColl[iel].Pt() << " / " << electronTightColl[iel].Eta() << " / " << electronTightColl[iel].Phi() << LQLogger::endmsg;
      else m_logger << INFO << "El+ pt/eta/phi = " << electronTightColl[iel].MatchedGenParticlePt() << " / " << electronTightColl[iel].MatchedGenParticleEta() << " / " <<electronTightColl[iel].MatchedGenParticlePhi() << LQLogger::endmsg;
      
    }
    
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      if( electronTightColl[iel].DeltaR(eventbase->GetTruth().at(it)) < 0.2){
        if(eventbase->GetTruth().at(it).IndexMother()!= 1)  m_logger << INFO << "Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / "<< eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()   << " " << eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId() << LQLogger::endmsg;
      }
    }
    
    bool prompt = true;
    bool charge_flip = false;
    bool match_found=false;
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      
      if( electronTightColl[iel].DeltaR(eventbase->GetTruth().at(it)) < 0.2){
	m_logger << INFO << "Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / " << eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()    << LQLogger::endmsg;
	
	match_found=true;
	
	if(eventbase->GetTruth().at(it).GenStatus() == 1){
	  if(fabs(eventbase->GetTruth().at(it).PdgId()) == 11){
	    for(unsigned int it2 = 0; it2 < eventbase->GetTruth().size() ; it2++){
	      if(eventbase->GetTruth().at(it2).PdgId() == 2212) continue;
	      if(eventbase->GetTruth().at(it2).GenStatus() == 3){
		if(eventbase->GetTruth().at(it).DeltaR(eventbase->GetTruth().at(it2)) < 0.1) {
		  m_logger << "PDGID of particle close to status 1 electron = " << eventbase->GetTruth().at(it2).PdgId() << LQLogger::endmsg;
		  m_logger << "Mother of  particle close to status 1 electron = " << eventbase->GetTruth().at(eventbase->GetTruth().at(it2).IndexMother()).PdgId() << LQLogger::endmsg;
		  if(fabs(eventbase->GetTruth().at(it2).PdgId()) == 15){
		    m_logger << INFO << "Electron  from Tau decay" << LQLogger::endmsg;
		    
		    if(eventbase->GetTruth().at(it2).PdgId() * electronTightColl[iel].Charge() > 0.){
		      charge_flip= true;
		      prompt=true;
		      m_logger << INFO << "ELECTRON FROM CHARGELFIP" <<  LQLogger::endmsg;
		      break;
		      
		    }		  
		  }
		}
	      }
	    }
	  }
	}
	else if(eventbase->GetTruth().at(it).GenStatus() == 3){
	  
	  if(fabs(eventbase->GetTruth().at(it).PdgId()) == 11 && isPrompt(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId()))) prompt = true;
	  else prompt = false;
	  
	  if(electronTightColl[iel].Charge() * eventbase->GetTruth().at(it).PdgId() > 0.)  charge_flip= true;
	}
      }
      
    } 
    if(!match_found)  {
      m_logger << INFO << "NOOOOO MATCHED  TRUTH PARTICLE FOUND" << LQLogger::endmsg;
      for(unsigned int jit = 0; jit < eventbase->GetGenJets().size(); jit++){
	m_logger<< INFO << "Matched Gen jet id = " << jit+1 << " pt = " <<  eventbase->GetGenJets().at(jit).Pt() << " eta= " << eventbase->GetGenJets().at(jit).Eta() << " phi = " << eventbase->GetGenJets().at(jit).Phi() << LQLogger::endmsg;
      }
      
      for(int ip=0; ip < PhotonEta->size() ; ip++){
	if(!PhotonHasMatchedPromptEle)m_logger<< INFO << "Photon pt/eta/phi = " << PhotonPt->at(ip) << " / " <<  PhotonEta->at(ip) << " / " << PhotonPhi->at(ip) << LQLogger::endmsg;
      }
    }


    if(iel==0){
      if(!prompt) {
	prompt_nonprompt = true;
	nonprompt_nonprompt = true;
	prompt_prompt = false;
      }
      else{
	if(charge_flip)  prompt_chargeflip = true;
	prompt_prompt = true;
	prompt_nonprompt = false;
	nonprompt_nonprompt = false;
      }
    }
    if(iel==1){
      if(!prompt) {
	if(nonprompt_nonprompt)nonprompt_nonprompt = true;
	else nonprompt_nonprompt = false;
	if(prompt_nonprompt) prompt_nonprompt = false;
	else prompt_nonprompt = true;
	prompt_prompt =false;
      }
      else {
	if(charge_flip)  prompt_chargeflip = true;
	nonprompt_nonprompt = false;
	if(prompt_prompt) prompt_prompt = true;
	else prompt_prompt =false;
	if(prompt_nonprompt) prompt_nonprompt = true;
	else  prompt_nonprompt = false;
      }
    }
  }
  
  if(prompt_chargeflip)  m_logger << INFO << "EVENT HAS CHARGEFLIP   "<<  LQLogger::endmsg;
  else   if (prompt_prompt) {
    m_logger << INFO << "EVENT IS PROMPT-PROMPT "<<  LQLogger::endmsg;
    cout << "WTF" << endl;
    for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
      if(eventbase->GetTruth().at(it).PdgId() == 2212) continue;
      m_logger << INFO << "PP:Truth " << it << " Matched to reco:   pt/eta/phi/ pdgid/status = " << eventbase->GetTruth().at(it).Pt() << " / " << eventbase->GetTruth().at(it).Eta() << " / " <<eventbase->GetTruth().at(it).Phi() <<  " / " <<   eventbase->GetTruth().at(it).PdgId()    << " / " << eventbase->GetTruth().at(it).GenStatus()    << LQLogger::endmsg;
      if( eventbase->GetTruth().at(it).IndexMother() != -1)m_logger << INFO <<   eventbase->GetTruth().at( eventbase->GetTruth().at(it).IndexMother()).PdgId()    << LQLogger::endmsg;
    }
    
  }
  else if (prompt_nonprompt) m_logger << INFO << "EVENT IS PROMPT-NONPROMPT "<<  LQLogger::endmsg;
  else if (nonprompt_nonprompt) m_logger << INFO << "EVENT IS NONPROMPT-NONPROMPT "<<  LQLogger::endmsg;
  m_logger << INFO << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  
  
  /*
  if(electronMediumColl.size() ==2){
    if(electronMediumColl.at(0).Charge() == electronMediumColl.at(1).Charge()) {

      for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){
	
	if(eventbase->GetTruth().at(it).GenStatus() == 3 && eventbase->GetTruth().at(it).PdgId() == -11 && eventbase->GetTruth().at(eventbase->GetTruth().at(it).IndexMother()).PdgId() == -24 || 23) ;
	
      }
 
      bool closejet = false;
      for(unsigned int j = 0; j < electronMediumColl.size(); j++){
	bool prompt_e=false;
	
	m_logger << INFO << "\n-------------------------------------\n " << LQLogger::endmsg;
	m_logger << INFO << "Electron id = " << j << "  pt = " << electronMediumColl.at(j).Pt() << " eta = " << electronMediumColl.at(j).Eta() << " phi = " << electronMediumColl.at(j).Phi() << " energy = " << electronMediumColl.at(j).E() << LQLogger::endmsg;
	
	for(unsigned int it = 0; it < eventbase->GetTruth().size() ; it++){

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
	
	for(unsigned int it = 0; it < jetColl.size(); it++){
	  m_logger<< INFO << "Jet id = " << it+1 << " pt = " <<  jetColl.at(it).Pt() << " eta= " << jetColl.at(it).Eta() << " phi = " << jetColl.at(it).Phi() << LQLogger::endmsg;
	}
	for(unsigned int it = 0; it < eventbase->GetGenJets().size(); it++){
	  if(eventbase->GetGenJets().at(it).DeltaR(electronMediumColl.at(j)) < 0.4) {
	    m_logger<< INFO << "Matched Gen jet id = " << it+1 << " pt = " <<  eventbase->GetGenJets().at(it).Pt() << " eta= " << eventbase->GetGenJets().at(it).Eta() << " phi = " << eventbase->GetGenJets().at(it).Phi() << LQLogger::endmsg;   
	  }
	}

	if(prompt_e)m_logger<< INFO << "Electron is prompt" << LQLogger::endmsg;
	else  m_logger<< INFO << "Electron is NOT prompt" << LQLogger::endmsg;
	
	
	if(prompt_e){
	  for(unsigned int i = 0; i < jetColl.size(); i++){
	    
	    if( jetColl.at(i).DeltaR(electronMediumColl.at(j)) < 0.4) {
	      
	      m_logger << INFO << "Electron vertex index = " << electronMediumColl.at(j).VertexIndex()  << LQLogger::endmsg;
	      FillHist("prompt_e_closejet_dr", jetColl.at(i).DeltaR(electronMediumColl.at(j)), weight, 0.,0.2,1000);

	      FillHist("prompt_e_closejet_multiplicity",jetColl.at(i).ChargedMultiplicity(), weight, 0.,30.,30);
	      FillHist("prompt_e_closejet_chem_enfrac", jetColl.at(i).ChargedEMEnergyFraction(), weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_chhad_enfrac", jetColl.at(i).ChargedHadEnergyFraction() , weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_elfrac", jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_nem_frac", jetColl.at(i).NeutralEMEnergyFraction(), weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_nhad_frac", jetColl.at(i).NeutralHadEnergyFraction(), weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_phot_frac", jetColl.at(i).PhotonEnergyFraction()  , weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_muon_frac", jetColl.at(i).MuonEnergyFraction() , weight, 0., 1., 100);
	      FillHist("prompt_e_closejet_vert_index", jetColl.at(i).BestVertexTrackAssociationIndex() -  electronMediumColl.at(j).VertexIndex(), weight, -10., 10., 20);
	      FillHist("prompt_e_closejet_vert_frac", jetColl.at(i).BestVertexTrackAssociationFactor(), 0., 1., 100);
	      
	      
	      FillHist("prompt_e_closejet_had_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100, 0., 1., 100);
	      FillHist("prompt_e_closejet_hadphoton_frac_elfrac" , jetColl.at(i).ChargedHadEnergyFraction() + jetColl.at(i).NeutralHadEnergyFraction() + jetColl.at(i).PhotonEnergyFraction(), jetColl.at(i).ElectronEnergyFraction() , weight , 0., 1., 100, 0., 1., 100);
	      

	      float theta = 2.*atan( (exp(-1.*jetColl.at(i).Eta())));
	      float sintheta = sin(theta);
	      float Et = jetColl.at(i).E() * sintheta;

	      m_logger << INFO << "prompt Jet energy = " << jetColl.at(i).E() << LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et = " <<  Et<< LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et (1-el frac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) << LQLogger::endmsg;
	      m_logger << INFO << "prompt Jet Et (1-el- ph frac) =  " << (Et * (1. - jetColl.at(i).ElectronEnergyFraction()- jetColl.at(i).PhotonEnergyFraction())) << LQLogger::endmsg;
	      
	      FillHist("prompt_e_closejet_pt_corrEt", jetColl.at(i).Pt(), (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) , weight, 0., 200., 200, 0., 100., 100);

      
	      FillHist("prompt_e_closejet_Ecorr", (Et * (1. - jetColl.at(i).ElectronEnergyFraction()))  , weight, 0., 100., 50);
	      FillHist("prompt_e_closejet_Ecorr2", (Et * (1. - (jetColl.at(i).ElectronEnergyFraction() + jetColl.at(i).PhotonEnergyFraction()))  )  , weight, 0., 100., 50);
	      
	      
	      if((jetColl.at(i).Pt() * (1.- jetColl.at(i).ElectronEnergyFraction())) > 20.) closejet = true;

	      
	    }
	  }
	
	  FillHist("SSMediumElclosejet",0, weight, 0.,2.,2);
	  if(!closejet)FillHist("SSMediumElclosejet",1, weight, 0.,2.,2);
	}
	else{
	  for(unsigned int i = 0; i < jetColl.size(); i++){

            if( jetColl.at(i).DeltaR(electronMediumColl.at(j)) < 0.4) {
	      
	      FillHist("nonprompt_e_closejet_dr", jetColl.at(i).DeltaR(electronMediumColl.at(j)), weight, 0.,0.2,1000);
              m_logger << INFO << "Electron vertex index = " << electronMediumColl.at(j).VertexIndex()  << LQLogger::endmsg;
              FillHist("nonprompt_e_closejet_multiplicity",jetColl.at(i).ChargedMultiplicity(), weight, 0.,30.,30);
              FillHist("nonprompt_e_closejet_chem_enfrac", jetColl.at(i).ChargedEMEnergyFraction(), weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_chhad_enfrac", jetColl.at(i).ChargedHadEnergyFraction() , weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_elfrac", jetColl.at(i).ElectronEnergyFraction() , weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_nem_frac", jetColl.at(i).NeutralEMEnergyFraction(), weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_nhad_frac", jetColl.at(i).NeutralHadEnergyFraction(), weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_phot_frac", jetColl.at(i).PhotonEnergyFraction()  , weight, 0., 1., 100);
              FillHist("nonprompt_e_closejet_muon_frac", jetColl.at(i).MuonEnergyFraction() , weight, 0., 1., 100);
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
	      
	      FillHist("nonprompt_e_closejet_Ecorr", (Et * (1. - jetColl.at(i).ElectronEnergyFraction()))  , weight, 0., 100., 50);
              FillHist("nonprompt_e_closejet_Ecorr2", (Et * (1. - (jetColl.at(i).ElectronEnergyFraction() + jetColl.at(i).PhotonEnergyFraction()))  )  , weight, 0., 100., 50);

	      FillHist("nonprompt_e_closejet_pt_corrEt", jetColl.at(i).Pt(), (Et * (1. - jetColl.at(i).ElectronEnergyFraction())) , weight, 0., 200., 200, 0., 100., 100);
            }
          }
	}
      }
    }
  }
  */  
  
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto.size(); ij++){
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
  for(unsigned int ij=0; ij <jetColl.size(); ij++){
    for (unsigned int iel=0; iel < electronTightColl.size(); iel++){
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


  
  bool no_emuoverlap = true;

  for(int i=0; i < electronTightColl.size() ; i++){
    for(int j=0; j < muonTightColl.size() ; j++){
      float dR =  electronTightColl[i].DeltaR(muonTightColl[j]);
      if(dR < 0.1) no_emuoverlap= false;
    }
  }
  
  if (electronTightColl.size() == 2) {      

    if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge()){      
      
      FillCutFlow("SS_t",weight);
      FillCLHist(sighist, "SSDiElectronTight", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
      
      if(nloose_lep == 2 && no_emuoverlap){
	FillCutFlow("SS_lvt_t",weight);
      
	if(jetColl_lepveto.size() > 1){
	  FillCutFlow("SS_dijet_t",weight);
	  FillCLHist(sighist, "SSDiElectronTight_DiJet", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
	  
	  
	  if(SumPt(jetColl_lepveto)  > 80.){
	    if(! ( SumPt(jetColl_lepveto) < 500. && eventbase->GetEvent().PFMET() < 30.)){
	      FillCLHist(sighist, "SSSR0", eventbase->GetEvent(), muonTightColl,electronTightColl,jetColl_lepveto, weight);
	    }
	  }
	  
	    
	  
	  bool pass_same_vertex= (electronTightColl.at(0).VertexIndex() == electronTightColl.at(1).VertexIndex());
	  bool fail_conv = true;
	  bool fail_d0=false;
	  bool ecalseeded= true;
	  bool pass_charge_cons=true;
	  
	  for(unsigned int i= 0; i < electronTightColl.size(); i++){
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

    
  /*
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
  
  */
  
  
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



