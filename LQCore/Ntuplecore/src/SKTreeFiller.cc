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

snu::KTrigger SKTreeFiller::GetTriggerInfo(std::vector<TString> trignames){
  snu::KTrigger ktrigger;

  
  if(!LQinput){
    ktrigger = *k_inputtrigger;
    return ktrigger;
  }

  std::vector<std::string> vHLTInsideDatasetTriggerNames;
  std::vector<bool> vHLTInsideDatasetTriggerDecisions;
  std::vector<int> vHLTInsideDatasetTriggerPrescales;
  
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
    
  for (std::vector<TString>::reverse_iterator it (trignames.end());
       it != std::vector<TString>::reverse_iterator (trignames.begin());
       ++it) {

    bool trigger_exists(false);
    for (UInt_t i=0; i< vtrignames->size(); i++) {
      
      std::string tgname = vtrignames->at(i);
      Int_t ps = vtrigps->at(i);

      TString tmpHLT = vtrignames->at(i);
      if ( tmpHLT.BeginsWith(*it)){

	trigger_exists = true;
	bool double_count_trig = false;
	for(std::vector<std::string>::iterator vit = vHLTInsideDatasetTriggerNames.begin(); vit != vHLTInsideDatasetTriggerNames.end(); vit++){
	  if(vit->compare(*it) == 0) double_count_trig = true;
	}
	if(!double_count_trig){
	  vHLTInsideDatasetTriggerNames.push_back(tgname);
	  if(ps > 0) vHLTInsideDatasetTriggerDecisions.push_back(true);
	  else vHLTInsideDatasetTriggerDecisions.push_back(false);
	  vHLTInsideDatasetTriggerPrescales.push_back(ps);
	}// double count check
      } // can use start of trig name to add many triggers
    } // loop over input triggers
    //if(!trigger_exists) m_logger << WARNING << "Trigger: " << *it << " does not exist" << LQLogger::endmsg;
  }// loop of selected triggers  
  
  ktrigger.SetHLTInsideDatasetTriggerNames(vHLTInsideDatasetTriggerNames);
  ktrigger.SetHLTInsideDatasetTriggerDecisions(vHLTInsideDatasetTriggerDecisions);
  ktrigger.SetHLTInsideDatasetTriggerPrescales(vHLTInsideDatasetTriggerPrescales);
    
  return ktrigger;
  
}

snu::KEvent SKTreeFiller::GetEventInfo(){
 
  snu::KEvent kevent;
  if(!LQinput){
    kevent = *k_inputevent;
    return kevent;
  }

  /// MET variables
  // PF met

  kevent.SetPFMET( met_pt->at(0));
  kevent.SetPFSumET( met_sumet->at(0));
  kevent.SetPFMETphi( met_phi->at(0));
  
  kevent.SetPuppiMET( metPuppi_pt->at(0));
  kevent.SetPuppiSumET( metPuppi_sumet->at(0));
  kevent.SetPuppiMETphi( metPuppi_phi->at(0));
  
  kevent.SetNoHFMET( metNoHF_pt->at(0));
  kevent.SetNoHFSumET( metNoHF_sumet->at(0));
  kevent.SetNoHFMETphi( metNoHF_phi->at(0));

  kevent.SetPfMvaMET( metPfMva_pt->at(0));
  kevent.SetPfMvaSumET( metPfMva_sumet->at(0));
  kevent.SetPfMvaMETphi( metPfMva_phi->at(0));

  

  /// Filling event variables


  kevent.SetIsData(isData);

  if(!isData&&genWeight){
    if(genWeight > 0.) kevent.SetWeight(1.);
    else kevent.SetWeight(-1.);
  }
  kevent.SetRunNumber(run);
  kevent.SetEventNumber(event);
  kevent.SetLumiSection(lumi);
  
  //  kevent.SetPUWeight(puWeight);
  //kevent.SetPUWeightPSigma(puWeightDn);
  //kevent.SetPUWeightMSigma(puWeightUp);

  kevent.SetGenId1(genWeight_id1);
  kevent.SetGenId2(genWeight_id2);

  kevent.SetLHEWeight(lheWeight);
  kevent.SetGenX1(genWeightX1);
  kevent.SetGenX2(genWeightX2);
  kevent.SetGenQ(genWeightQ);
  
  //  kevent.SetVertexX(vertices_x->at(0));
  //  kevent.SetVertexY(vertices_y->at(0));
  //  kevent.SetVertexZ(vertices_z->at(0));
  //  kevent.SetVertexNDOF(vertices_ndof->at(0));
  
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



std::vector<KElectron> SKTreeFiller::GetAllElectrons(){

  std::vector<KElectron> electrons;
  if(!LQinput){
    for(std::vector<KElectron>::iterator kit  = k_inputelectrons->begin(); kit != k_inputelectrons->end(); kit++){
      electrons.push_back(*kit);
    }
    return electrons;
  }
  

  for (UInt_t iel=0; iel< electrons_eta->size(); iel++) {
    KElectron el;
    
    /// Kinematic Variables
    el.SetPtEtaPhiE(electrons_pt->at(iel),electrons_eta->at(iel), electrons_phi->at(iel),electrons_energy->at(iel));
    
    el.SetTrigMatch(electron_trigmatch->at(iel));
    el.SetSCEta(electrons_scEta->at(iel));
   
    el.Setdz( electrons_dz->at(iel));
    el.Setdxy(electrons_dxy->at(iel) );

    el.SetPFChargedHadronIso03(electrons_puChIso03->at(iel));
    el.SetPFPhotonIso03(electrons_phIso03->at(iel));
    el.SetPFNeutralHadronIso03(electrons_nhIso03->at(iel));
    el.SetPFRelIso03(electrons_relIso03->at(iel));
    
    
    el.SetPFChargedHadronIso04(electrons_puChIso04->at(iel));
    el.SetPFPhotonIso04(electrons_phIso04->at(iel));
    el.SetPFNeutralHadronIso04(electrons_nhIso04->at(iel));
    el.SetPFRelIso04(electrons_relIso04->at(iel));
    
    el.SetPFAbsIso03(electrons_absIso03->at(iel));
    el.SetPFAbsIso04(electrons_absIso04->at(iel));


    /// set Charge variables
    el.SetCharge(int(electrons_q->at(iel)));
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
    el.SetIsPF(electrons_isPF->at(iel));
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


  for (UInt_t ijet=0; ijet< slimmedGenJets_pt->size(); ijet++) {
    KGenJet jet;
    jet.SetPtEtaPhiE(slimmedGenJets_pt->at(ijet), slimmedGenJets_eta->at(ijet), slimmedGenJets_phi->at(ijet), slimmedGenJets_energy->at(ijet));
    //jet.SetGenJetEMF(GenJetEMF->at(ijet));
    //jet.SetGenJetHADF(GenJetHADF->at(ijet));
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
    
    jet.SetJetPileupIDMVA(jets_isPFId->at(ijet));

    if(jets_isPFId){ 
      if(std::abs(jets_eta->at(ijet)) < 2.6){
	if(jets_isPFId->at(ijet) > 0.3) jet.SetJetPileupIDLooseWP(true);
	else jet.SetJetPileupIDLooseWP(false);
	if(jets_isPFId->at(ijet) > 0.7) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
	if(jets_isPFId->at(ijet) > 0.9)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
      else{
	if(jets_isPFId->at(ijet) > -0.55) jet.SetJetPileupIDLooseWP(true);
        else jet.SetJetPileupIDLooseWP(false);
        if(jets_isPFId->at(ijet) > -0.3) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
        if(jets_isPFId->at(ijet) > -0.1)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
    }
    
    
    /// BTAG variables
    jet.SetCVSInclV2(jets_CVSInclV2->at(ijet));
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
    muon.SetCharge(int(muon_q->at(ilep)));
     
    m_logger << DEBUG << "Filling ms pt/eta ... " << LQLogger::endmsg;
 
    muon.SetRelIso03(muon_relIso03->at(ilep));
    muon.SetRelIso04(muon_relIso04->at(ilep));

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

  

std::vector<snu::KTruth>   SKTreeFiller::GetTruthParticles(){
  
  m_logger << DEBUG << "Filling Truth" << LQLogger::endmsg;
  std::vector<snu::KTruth> vtruth;

  if(!LQinput){

    for(std::vector<KTruth>::iterator kit  = k_inputtruth->begin(); kit != k_inputtruth->end(); kit++){
      vtruth.push_back(*kit);
    }
    return vtruth;
  }
  
  for (UInt_t it=0; it< gen_pt->size(); it++ ) {
    
    KTruth truthp;
    truthp.SetPtEtaPhiE(gen_pt->at(it), gen_eta->at(it), gen_phi->at(it), gen_energy->at(it));
    /*truthp.SetParticlePx(GenParticlePx->at(it));
      truthp.SetParticlePy(GenParticlePy->at(it));
      truthp.SetParticlePz(GenParticlePz->at(it));
      if(GenParticleVX){
      truthp.SetParticleVx(GenParticleVX->at(it));
	truthp.SetParticleVy(GenParticleVY->at(it));
	truthp.SetParticleVz(GenParticleVZ->at(it));
	}*/
      truthp.SetParticlePdgId(gen_pdgid->at(it));
      truthp.SetParticleStatus(gen_status->at(it));
      
      //truthp.SetParticleNDaughter(GenParticleNumDaught->at(it));
      
      truthp.SetParticleIndexMother(gen_motherindex->at(it));
      vtruth.push_back(truthp);  
      
  }
  
  return vtruth;
}
