#include "SKTreeFiller.h"
#include <stdio.h>  

#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;


SKTreeFiller::SKTreeFiller() :Data() {
  
  TString fitParametersFile = "";
};


SKTreeFiller::~SKTreeFiller() {};


bool SKTreeFiller::SkipTrigger(TString tname){
  
  m_logger << DEBUG << "Trigger: " << tname << LQLogger::endmsg;  
  /// Remove extra unnecisary  triggers (from v7-6-4+ this will not be needed))
  if((tname.Contains("Jpsi")
       || tname.Contains("NoFilters")
       || tname.Contains("Upsilon")
       || tname.Contains("7p5")
       || tname.Contains("Save")
       || tname.Contains("R9Id")
       || tname.Contains("PFMET")
       || tname.Contains("PFHT")
       || tname.Contains("NoHE")
       || tname.Contains("HE10")
       || tname.Contains("PFJet50")
       || tname.Contains("Boost")
       || tname.Contains("LooseIso")
       || tname.Contains("MediumIso")
      || tname.Contains("Mass")
       || tname.Contains("Central")
       || tname.Contains("MW")
       || tname.Contains("EBOnly_VBF")
      || tname.Contains("dEta18"))) return true;
  
  return false;
}


snu::KTrigger SKTreeFiller::GetTriggerInfo(std::vector<TString> trignames){
  snu::KTrigger ktrigger;
  
  if(!LQinput){
    ktrigger = *k_inputtrigger;
    return ktrigger;
  }
  m_logger << DEBUG << "Filling trigger Info" << LQLogger::endmsg;


  std::vector<std::string> vHLTInsideDatasetTriggerNames;
  std::vector<bool> vHLTInsideDatasetTriggerDecisions;
  std::vector<int> vHLTInsideDatasetTriggerPrescales;
  

  /// trignames should only be empty id user is running on Catuples and not SKTreeMaker. In this case all triggers are used 
  if(trignames.size() == 0 ){
    for (UInt_t i=0; i< vtrignames->size(); i++) {
      std::string tgname = vtrignames->at(i);
      Int_t ps = vtrigps->at(i);
      vHLTInsideDatasetTriggerNames.push_back(tgname);
      if(ps > 0) vHLTInsideDatasetTriggerDecisions.push_back(true);
      else vHLTInsideDatasetTriggerDecisions.push_back(false);
      vHLTInsideDatasetTriggerPrescales.push_back(ps);
    }
  }

  
  /// vtrigname is vector of ALL triggers in Catuples
  for (UInt_t i=0 ; i< vtrignames->size(); i++) {
    // trignames is vector of trigger names that we want to store in SKTrees
    // trigname contains names substrings X (where X is for example "HLT_mu") and we store all triggers that start with X

    std::string tgname = vtrignames->at(i);
    if(TString(CatVersion).Contains("v7-6-2")) {
      if(SkipTrigger(TString(tgname)))continue;
    }

    Int_t ps = vtrigps->at(i);

    for (std::vector<TString>::reverse_iterator it (trignames.end());
	 it != std::vector<TString>::reverse_iterator (trignames.begin());
	 ++it) {

      TString tmpHLT = vtrignames->at(i);
      if ( tmpHLT.BeginsWith(*it)){
	
	vHLTInsideDatasetTriggerNames.push_back(tgname);
	if(ps > 0) vHLTInsideDatasetTriggerDecisions.push_back(true);
	else vHLTInsideDatasetTriggerDecisions.push_back(false);
	vHLTInsideDatasetTriggerPrescales.push_back(ps);
	
	// if trigger is accepted break from loop
	break;
      }
    } // end of trignames loop
  }// loop of all triggers  
  
  ktrigger.SetHLTInsideDatasetTriggerNames(vHLTInsideDatasetTriggerNames);
  ktrigger.SetHLTInsideDatasetTriggerDecisions(vHLTInsideDatasetTriggerDecisions);
  ktrigger.SetHLTInsideDatasetTriggerPrescales(vHLTInsideDatasetTriggerPrescales);
    
  return ktrigger;
  
}

snu::KEvent SKTreeFiller::GetEventInfo(){
 
  snu::KEvent kevent;
  if(!LQinput){
    kevent = *k_inputevent;
    if(TString(CatVersion).Contains("v7-4")){
      if(!TString(kevent.CatVersion()).Contains("v7-4"))kevent.SetCatVersion(CatVersion);
    }
    return kevent;
  }

  m_logger << DEBUG << "Filling Event Info" << LQLogger::endmsg;
  
  // New variable to set catversion. Add this to flat ntuples for next iteration

  kevent.SetCatVersion(CatVersion);

  kevent.SetMET(snu::KEvent::pfmet,  met_pt->at(0), met_phi->at(0),  met_sumet->at(0));
  m_logger << DEBUG << "Filling Event Info [2]" << LQLogger::endmsg;
  if(metNoHF_pt){
    if(metNoHF_pt->size() > 0) kevent.SetMET(snu::KEvent::nohf, metNoHF_pt->at(0),  metNoHF_phi->at(0), metNoHF_sumet->at(0));
  }
  
  m_logger << DEBUG << "Filling Event Info [3]" << LQLogger::endmsg;
  if(met_unclusteredEn_Px_up){
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::MuonEn,     sqrt(met_muonEn_Px_up*met_muonEn_Px_up + met_muonEn_Py_up*met_muonEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::MuonEn,     sqrt(met_muonEn_Px_down*met_muonEn_Px_down + met_muonEn_Py_down*met_muonEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::ElectronEn, sqrt(met_electronEn_Px_up*met_electronEn_Px_up + met_electronEn_Py_up*met_electronEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::ElectronEn, sqrt(met_electronEn_Px_down*met_electronEn_Px_down + met_electronEn_Py_down*met_electronEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::Unclustered,sqrt(met_unclusteredEn_Px_up*met_unclusteredEn_Px_up + met_unclusteredEn_Py_up*met_unclusteredEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::Unclustered,sqrt(met_unclusteredEn_Px_down*met_unclusteredEn_Px_down + met_unclusteredEn_Py_down*met_unclusteredEn_Py_up));
    kevent.SetPFSumETShift(snu::KEvent::up,     snu::KEvent::Unclustered,met_unclusteredEn_SumEt_up);
    kevent.SetPFSumETShift(snu::KEvent::down,   snu::KEvent::Unclustered,met_unclusteredEn_SumEt_down);
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::JetEn,      sqrt(met_jetEn_Px_up*met_jetEn_Px_up + met_jetEn_Py_up*met_jetEn_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::JetEn,      sqrt(met_jetEn_Px_down*met_jetEn_Px_down + met_jetEn_Py_down*met_jetEn_Py_up));
    kevent.SetPFSumETShift(snu::KEvent::up,     snu::KEvent::JetEn,      met_jetEn_SumEt_up);
    kevent.SetPFSumETShift(snu::KEvent::down,   snu::KEvent::JetEn,      met_jetEn_SumEt_down);
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::JetRes,     sqrt(met_jetRes_Px_up*met_jetRes_Px_up + met_jetRes_Py_up*met_jetRes_Py_up));
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::JetRes,     sqrt(met_jetRes_Px_down*met_jetRes_Px_down + met_jetRes_Py_down*met_jetRes_Py_up));
    
    kevent.SetPFSumETShift(snu::KEvent::up,     snu::KEvent::JetRes,     met_jetRes_SumEt_up);
    kevent.SetPFSumETShift(snu::KEvent::down,   snu::KEvent::JetRes,     met_jetRes_SumEt_down);
  }
  m_logger << DEBUG << "Filling Event Info [4]" << LQLogger::endmsg;
  
  /// Filling event variables
    
  kevent.SetIsData(isData);

  if(!isData&&genWeight){
    if(genWeight > 0.) kevent.SetWeight(1.);
    else kevent.SetWeight(-1.);
  }
  kevent.SetRunNumber(run);
  kevent.SetEventNumber(event);
  kevent.SetLumiSection(lumi);
  
  if(puWeightSilver){
    kevent.SetPUWeight(snu::KEvent::silver,snu::KEvent::none,puWeightSilver);
    kevent.SetPUWeight(snu::KEvent::silver,snu::KEvent::down,puWeightSilverDn);
    kevent.SetPUWeight(snu::KEvent::silver,snu::KEvent::up,  puWeightSilverUp);
    kevent.SetPUWeight(snu::KEvent::gold,  snu::KEvent::none,puWeightGold);
    kevent.SetPUWeight(snu::KEvent::gold,  snu::KEvent::down,puWeightGoldDn);
    kevent.SetPUWeight(snu::KEvent::gold,  snu::KEvent::up,  puWeightGoldUp);
  }
  if(lumiMaskSilver){
    kevent.SetLumiMask(snu::KEvent::silver, lumiMaskSilver);
    kevent.SetLumiMask(snu::KEvent::gold,   lumiMaskGold);
  }

  kevent.SetGenId(genWeight_id1, genWeight_id2);

  kevent.SetLHEWeight(lheWeight);
  kevent.SetGenX(genWeightX1, genWeightX2);
  kevent.SetGenQ(genWeightQ);
  
  kevent.SetVertexInfo(vertex_X, vertex_Y, vertex_Z,0. );
  
  /// MET filter cuts/checks

  
  /// 
  if(!isData)kevent.SetPileUpInteractionsTrue(nTrueInteraction);
  else kevent.SetPileUpInteractionsTrue(-999.);
  
  kevent.SetNVertices(nPV);
  kevent.SetNGoodVertices(nGoodPV);
  
  kevent.SetIsGoodEvent(nGoodPV);

  /// MET filter cuts/checks

  kevent.SetPassEcalDeadCellTriggerPrimitiveFilter(ecalDCTRFilter);
  kevent.SetPassHBHENoiseFilter(HBHENoiseFilter);
  kevent.SetPassCSCHaloFilterTight(csctighthaloFilter);
  kevent.SetPassBadEESupercrystalFilter(eeBadScFilter);


  return kevent;
}


std::vector<KPhoton> SKTreeFiller::GetAllPhotons(){

  std::vector<KPhoton> photons;

  if(TString(CatVersion).Contains("v7-4")) return photons;
  

  if(!LQinput){
    for(std::vector<KPhoton>::iterator kit  = k_inputphotons->begin(); kit != k_inputphotons->end(); kit++){
      photons.push_back(*kit);
    }
    return photons;
  }
  for (UInt_t iph=0; iph< photons_eta->size(); iph++) {
    KPhoton ph;

    ph.SetPtEtaPhiE(photons_pt->at(iph),photons_eta->at(iph), photons_phi->at(iph),photons_energy->at(iph));

    ph.SetIsLoose(photons_photonID_loose->at(iph));
    ph.SetIsMedium(photons_photonID_medium->at(iph));
    ph.SetIsTight(photons_photonID_tight->at(iph));
    ph.SetPassMVA(photons_photonID_mva->at(iph));
    ph.SetMCMatched(photons_mcMatched->at(iph));
    ph.SetHasPixSeed(photons_haspixseed->at(iph));
    ph.SetPassElVeto(photons_passelectronveto->at(iph));

    ph.SetChargedHadIsoNoEA(photons_chargedHadronIso->at(iph));
    ph.SetpuChargedHadIsoNoEA(photons_puChargedHadronIso->at(iph));
    ph.SetNeutalHadIsoNoEA(photons_neutralHadronIso->at(iph));
    ph.SetPhotonIsoNoEA(photons_photonIso->at(iph));
    ph.SetRhoIso(photons_rhoIso->at(iph));
    ph.SetChargedHadIso(photons_chargedHadronIsoWithEA->at(iph));
    ph.SetPhotonIso(photons_photonIsoWithEA->at(iph));
    ph.SetNeutalHadIso(photons_neutralHadronIsoWithEA->at(iph));
    ph.SetSigmaIetaIeta(photons_sigmaietaieta->at(iph));
    ph.SetR9(photons_r9->at(iph));
    ph.SetHoverE(photons_hovere->at(iph));
    ph.SetSCEta(photons_sceta->at(iph));
    ph.SetSCPhi(photons_scphi->at(iph));
    ph.SetSCRawE(photons_scrawenergy->at(iph));
    ph.SetSCPreShowerE(photons_scpreshowerenergy->at(iph));
    
    photons.push_back(ph);
  }
  std::sort( photons.begin(), photons.end(), isHigherPt );

  return photons;

}

std::vector<KElectron> SKTreeFiller::GetAllElectrons(){

  std::vector<KElectron> electrons;
  if(!LQinput){
    for(std::vector<KElectron>::iterator kit  = k_inputelectrons->begin(); kit != k_inputelectrons->end(); kit++){
      electrons.push_back(*kit);
    }
    return electrons;
  }

  m_logger << DEBUG << "Filling electron Info" << LQLogger::endmsg;
  

  for (UInt_t iel=0; iel< electrons_eta->size(); iel++) {
    KElectron el;
    
    /// Kinematic Variables
    el.SetPtEtaPhiE(electrons_pt->at(iel),electrons_eta->at(iel), electrons_phi->at(iel),electrons_energy->at(iel));
    
    el.SetTrigMatch(electron_trigmatch->at(iel));
    el.SetSCEta(electrons_scEta->at(iel));
   
    el.Setdz( electrons_dz->at(iel));
    el.Setdxy(electrons_dxy->at(iel) );

    el.SetPFChargedHadronIso(0.3, electrons_puChIso03->at(iel));
    el.SetPFPhotonIso(0.3,electrons_phIso03->at(iel));
    el.SetPFNeutralHadronIso(0.3,electrons_nhIso03->at(iel));
    el.SetPFRelIso(0.3,electrons_relIso03->at(iel));
    
    
    el.SetPFChargedHadronIso(0.4,electrons_puChIso04->at(iel));
    el.SetPFPhotonIso(0.4,electrons_phIso04->at(iel));
    el.SetPFNeutralHadronIso(0.4,electrons_nhIso04->at(iel));
    el.SetPFRelIso(0.4,electrons_relIso04->at(iel));
    
    el.SetPFAbsIso(0.3,electrons_absIso03->at(iel));
    el.SetPFAbsIso(0.4,electrons_absIso04->at(iel));


    /// set Charge variables
    el.SetCharge(electrons_q->at(iel));
    el.SetGsfCtfScPixCharge(electrons_isGsfCtfScPixChargeConsistent->at(iel));
    
    
    /// set conversion variables
    
    if(electrons_shiftedEnDown){
      el.SetShiftedEUp(electrons_shiftedEnUp->at(iel));
      el.SetShiftedEDown(electrons_shiftedEnDown->at(iel));
    }
    
    el.SetSNUID(electrons_electronID_snu->at(iel));
    el.SetPassVeto(electrons_electronID_veto->at(iel));
    el.SetPassLoose(electrons_electronID_loose->at(iel));
    el.SetPassMedium(electrons_electronID_medium->at(iel));
    el.SetPassTight(electrons_electronID_tight->at(iel));
    
    /// HEEP
    el.SetPassHEEP(electrons_electronID_heep->at(iel));

    // MVA
    el.SetPassMVATrigMedium(electrons_electronID_mva_trig_medium->at(iel));
    el.SetPassMVATrigTight(electrons_electronID_mva_trig_tight->at(iel));
    el.SetPassMVANoTrigMedium(electrons_electronID_mva_medium->at(iel));
    el.SetPassMVANoTrigTight(electrons_electronID_mva_tight->at(iel));

    el.SetIsPF(electrons_isPF->at(iel));
    el.SetIsTrigMVAValid(electrons_isTrigMVAValid->at(iel));
    el.SetIsMCMatched(electrons_mcMatched->at(iel));
    el.SetHasMatchedConvPhot(electrons_passConversionVeto->at(iel));
    
    el.SetTrkVx(electrons_x->at(iel));
    el.SetTrkVy(electrons_y->at(iel));
    el.SetTrkVz(electrons_z->at(iel));

    electrons.push_back(el);
  }
  std::sort( electrons.begin(), electrons.end(), isHigherPt );
  
  return electrons;
}


void SKTreeFiller::ERRORMessage(TString comment){
  
  m_logger << ERROR << "SKTreeFiller had a probleming filling " << comment << ". This variable is not present in the current LQntuples." << LQLogger::endmsg;   
}



std::vector<KGenJet> SKTreeFiller::GetAllGenJets(){

  std::vector<KGenJet> genjets;
  if(!LQinput){
    if(k_inputgenjets){
      for(std::vector<KGenJet>::iterator kit  = k_inputgenjets->begin(); kit != k_inputgenjets->end(); kit++){
	genjets.push_back(*kit);
      }
    }
    return genjets;
  }

  m_logger << DEBUG << "Filling genevent Info" << LQLogger::endmsg;

  for (UInt_t ijet=0; ijet< genjet_pt->size(); ijet++) {
    KGenJet jet;
    jet.SetPtEtaPhiE(genjet_pt->at(ijet), genjet_eta->at(ijet), genjet_phi->at(ijet), genjet_energy->at(ijet));
    jet.SetGenJetEMF(genjet_emf->at(ijet));
    jet.SetGenJetHADF(genjet_hadf->at(ijet));
    jet.SetGenJetPDGID(int(genjet_hadf->at(ijet)));
    genjets.push_back(jet);
  }
  return genjets;
}


std::vector<KJet> SKTreeFiller::GetAllJets(){

  std::vector<KJet> jets;
  if(!LQinput){

    for(std::vector<KJet>::iterator kit  = k_inputjets->begin(); kit != k_inputjets->end(); kit++){
      jets.push_back(*kit);
    }
    return jets;
  }
  
  
  for (UInt_t ijet=0; ijet< jets_eta->size(); ijet++) {
    KJet jet;
    

    jet.SetPtEtaPhiE(jets_pt->at(ijet), jets_eta->at(ijet), jets_phi->at(ijet), jets_energy->at(ijet));
    jet.SetJetPassLooseID(jets_isLoose->at(ijet));
    jet.SetJetPassTightID(jets_isTight->at(ijet));
    jet.SetJetPassTightLepVetoID(jets_isTightLepVetoJetID->at(ijet));
    
    jet.SetJetPileupIDMVA(jets_PileupJetId->at(ijet));

    if(jets_PileupJetId){ 
      if(std::abs(jets_eta->at(ijet)) < 2.6){
	if(jets_PileupJetId->at(ijet) > 0.3) jet.SetJetPileupIDLooseWP(true);
	else jet.SetJetPileupIDLooseWP(false);
	if(jets_PileupJetId->at(ijet) > 0.7) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
	if(jets_PileupJetId->at(ijet) > 0.9)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
      else{
	if(jets_PileupJetId->at(ijet) > -0.55) jet.SetJetPileupIDLooseWP(true);
        else jet.SetJetPileupIDLooseWP(false);
        if(jets_PileupJetId->at(ijet) > -0.3) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
        if(jets_PileupJetId->at(ijet) > -0.1)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
    }
    
    
    /// BTAG variables
    if(jets_CSVInclV2) jet.SetBTagInfo(snu::KJet::CSVv2, jets_CSVInclV2->at(ijet));
    if(jets_CMVAV2)    jet.SetBTagInfo(snu::KJet::cMVAv2, jets_CMVAV2->at(ijet));
    if(jets_JetProbBJet)  jet.SetBTagInfo(snu::KJet::JETPROB, jets_JetProbBJet->at(ijet)); 

    jet.SetVtxMass(jets_vtxMass->at(ijet));
    jet.SetVtx3DVal(jets_vtx3DVal->at(ijet));
    jet.SetVtx3DSig(jets_vtx3DSig->at(ijet));
    jet.SetVtxNTracks(jets_vtxNtracks->at(ijet));
    
    // flavour
    jet.SetJetPartonFlavour(jets_partonFlavour->at(ijet));
    jet.SetJetHadronFlavour(jets_hadronFlavour->at(ijet));    
    jet.SetJetPartonPdgId(jets_partonPdgId->at(ijet));
    
    jet.SetJetChargedEmEF(jets_chargedEmEnergyFraction->at(ijet));
    /// JEC and uncertainties
    jet.SetJetScaledDownEnergy(jets_shiftedEnDown->at(ijet));
    jet.SetJetScaledUpEnergy(jets_shiftedEnUp->at(ijet));
    jet.SetJetSmearedDownEnergy(jets_smearedResDown->at(ijet));
    jet.SetJetSmearedUpEnergy(jets_smearedResUp->at(ijet));
    jet.SetJetSmearedEnergy(jets_smearedRes->at(ijet));
    
    jets.push_back(jet);
  }// end of jet 
  
  
  std::sort( jets.begin(), jets.end(), isHigherPt );
  
  m_logger << DEBUG << "PFJet size = " << jets.size() << LQLogger::endmsg;
  return jets;
}


std::vector<KMuon> SKTreeFiller::GetAllMuons(){

  std::vector<KMuon> muons ;
  
  if(!LQinput){
    for(std::vector<KMuon>::iterator kit  = k_inputmuons->begin(); kit != k_inputmuons->end(); kit++){
      muons.push_back(*kit);
    }  
    return muons;
  }

  m_logger << DEBUG << "Filling Muons" << LQLogger::endmsg;

  
  for (UInt_t ilep=0; ilep< muon_eta->size(); ilep++) {
    KMuon muon;
    m_logger << DEBUG << "Filling global pt/eta ... " << LQLogger::endmsg;
   
    muon.SetTrigMatch(muon_trigmatch->at(ilep));
      
    /// GENERAL
    
    muon.SetISPF(muon_isPF->at(ilep));
    muon.SetIsGlobal(muon_isGlobal->at(ilep));
    muon.SetIsTracker(muon_isTracker->at(ilep));
    muon.SetIsLoose(muon_isLoose->at(ilep));
    muon.SetIsMedium(muon_isMedium->at(ilep));
    muon.SetIsTight(muon_isTight->at(ilep));
    muon.SetIsSoft(muon_isSoft->at(ilep));

    if(muon_shiftedEup){
      muon.SetShiftedEUp(muon_shiftedEup->at(ilep));
      muon.SetShiftedEDown(muon_shiftedEdown->at(ilep));
    }
    
    
    muon.SetPtEtaPhiE(muon_pt->at(ilep), muon_eta->at(ilep),muon_phi->at(ilep), muon_energy->at(ilep));
    muon.SetCharge(muon_q->at(ilep));
     
    m_logger << DEBUG << "Filling ms pt/eta ... " << LQLogger::endmsg;
 
    muon.SetRelIso(0.3,muon_relIso03->at(ilep));
    muon.SetRelIso(0.4,muon_relIso04->at(ilep));

    muon.Setdz(muon_dz->at(ilep));
    muon.Setdxy(muon_dxy->at(ilep));
    //// chi2
    muon.SetGlobalchi2( muon_normchi->at(ilep));
        
    /// hits
    muon.SetValidHits( muon_validhits->at(ilep));
    muon.SetPixelValidHits( muon_validpixhits->at(ilep));
    muon.SetValidStations( muon_matchedstations->at(ilep));
    muon.SetLayersWithMeasurement ( muon_trackerlayers->at(ilep));
    
    muon.SetMCMatched(muon_matched->at(ilep));


    muon.SetTrackVx(muon_x->at(ilep));
    muon.SetTrackVy(muon_y->at(ilep));
    muon.SetTrackVz(muon_z->at(ilep));

    
    /// Fill vector
    muons.push_back(muon);
  }
  
  std::sort( muons.begin(), muons.end(), isHigherPt );
  m_logger << DEBUG << "End of Muon Filling" << LQLogger::endmsg;
  return muons;
}

  

std::vector<snu::KTruth>   SKTreeFiller::GetTruthParticles(int np){
  
  m_logger << DEBUG << "Filling Truth" << LQLogger::endmsg;
  std::vector<snu::KTruth> vtruth;

  int counter=0;

  if(!LQinput){

    for(std::vector<KTruth>::iterator kit  = k_inputtruth->begin(); kit != k_inputtruth->end(); kit++, counter++){
      if(counter == np)  break;
      vtruth.push_back(*kit);
    }
    return vtruth;
  }
  
  m_logger << DEBUG << "Filling truth Info" << LQLogger::endmsg;
  
  for (UInt_t it=0; it< gen_pt->size(); it++ , counter++) {
    
    if(counter == np)  break;
    KTruth truthp;
    truthp.SetPtEtaPhiE(gen_pt->at(it), gen_eta->at(it), gen_phi->at(it), gen_energy->at(it));
    truthp.SetParticlePdgId(gen_pdgid->at(it));
    truthp.SetParticleStatus(gen_status->at(it));
    truthp.SetParticleIndexMother(gen_motherindex->at(it));
    vtruth.push_back(truthp);  
  }
  
  return vtruth;
}
