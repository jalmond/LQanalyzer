#include "SKTreeFiller.h"
#include <stdio.h>  

#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;


SKTreeFiller::SKTreeFiller() :Data() {
  VertexN = -999; //// set event vertex to dummy number 
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

  for (std::vector<TString>::reverse_iterator it (trignames.end());
       it != std::vector<TString>::reverse_iterator (trignames.begin());
       ++it) {

    bool trigger_exists(false);
    for (UInt_t i=0; i< HLTInsideDatasetTriggerNames->size(); i++) {

      TString tmpHLT = HLTInsideDatasetTriggerNames->at(i);
      if ( tmpHLT.BeginsWith(*it)){
	trigger_exists = true;
	bool double_count_trig = false;
	for(std::vector<std::string>::iterator vit = vHLTInsideDatasetTriggerNames.begin(); vit != vHLTInsideDatasetTriggerNames.end(); vit++){
	  if(vit->compare(*it) == 0) double_count_trig = true;
	}
	if(!double_count_trig){
	  vHLTInsideDatasetTriggerNames.push_back(HLTInsideDatasetTriggerNames->at(i));	
	  vHLTInsideDatasetTriggerDecisions.push_back(HLTInsideDatasetTriggerDecisions->at(i));
	  vHLTInsideDatasetTriggerPrescales.push_back(HLTInsideDatasetTriggerPrescales->at(i));
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
 
  m_logger << DEBUG << "Filling Event" << LQLogger::endmsg;
  snu::KEvent kevent;
  if(!LQinput){
    kevent = *k_inputevent;
    return kevent;
  }
 
  VertexN = -999; 
  kevent.SetMET( PFMETType01XYCor->at(0));

  int nVertices = VertexNDF->size();
  kevent.SetNVertices(nVertices);
  goodVerticies = new Bool_t [nVertices];
  /// delete
  
  if ( !isGoodEvent(nVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticies) ) kevent.SetIsGoodEvent(false);
  else  kevent.SetIsGoodEvent(true);
  
  
  for(UInt_t vv=0; vv<VertexNDF->size(); vv++) {
    if(goodVerticies[vv]) {
      VertexN=vv;
      break;
    }
  }


  
  kevent.SetVertexIndex(VertexN); /// setting event vertex
  kevent.SetIsData(isData);
  if(!isData)kevent.SetWeight(Weight);  
  else kevent.SetWeight(0.);  
  kevent.SetRunNumber(run);
  kevent.SetEventNumber(event);
  kevent.SetIsPrimaryVertex(isPrimaryVertex);

  if(VertexN != -999){
    kevent.SetVertexX(VertexX->at(VertexN));
    kevent.SetVertexY(VertexY->at(VertexN));
    kevent.SetVertexZ(VertexZ->at(VertexN));  
    kevent.SetVertexIsFake(VertexIsFake->at(VertexN));
  }
  else VertexN = -1;
  kevent.SetJetRho(rhoJets);
  
  kevent.SetIsTrackingFailure(isTrackingFailure);
  kevent.SetPassTrackingFailureFilter(passTrackingFailureFilter);
  kevent.SetPassBeamHaloFilterLoose(passBeamHaloFilterLoose);
  kevent.SetPassBadEESupercrystalFilter(passBadEESupercrystalFilter);
  kevent.SetPassEcalDeadCellBoundaryEnergyFilter(passEcalDeadCellBoundaryEnergyFilter);
  kevent.SetPassEcalDeadCellTriggerPrimitiveFilter(passEcalDeadCellTriggerPrimitiveFilter);
  kevent.SetPassEcalLaserCorrFilter(passEcalLaserCorrFilter);
  kevent.SetPassHBHENoiseFilter(passHBHENoiseFilter);
  kevent.SetPassHcalLaserEventFilter(passHcalLaserEventFilter);

  if(!isData)kevent.SetPileUpInteractionsTrue(PileUpInteractionsTrue->at(0));
  else kevent.SetPileUpInteractionsTrue(-999.);
  
  return kevent;
}


std::vector<KTau> SKTreeFiller::GetAllTaus(){
  
  std::vector<KTau> taus;
  if(!LQinput){
    
    return taus;
  }

  m_logger << DEBUG << "Filling Tau" << LQLogger::endmsg;
  for(UInt_t itau = 0; itau < HPSTauPhi->size(); itau++){

    KTau tau;
    tau.SetCharge(HPSTauCharge->at(itau));
    tau.SetPtEtaPhiE(HPSTauPt->at(itau),HPSTauEta->at(itau), HPSTauPhi->at(itau), (HPSTauEt->at(itau)));
    tau.SetIsPF(HPSTauIsPFTau->at(itau));

    taus.push_back(tau);
  }
  
  return taus;
}

std::vector<KElectron> SKTreeFiller::GetAllElectrons(){

  std::vector<KElectron> electrons;
  if(!LQinput){
    for(std::vector<KElectron>::iterator kit  = k_inputelectrons->begin(); kit != k_inputelectrons->end(); kit++){
      electrons.push_back(*kit);
    }
    return electrons;
  }

  
  m_logger << DEBUG << "Filling Electron" << LQLogger::endmsg;

  for (UInt_t iel=0; iel< ElectronEta->size(); iel++) {
    KElectron el;
    
    el.SetisEB(ElectronIsEB->at(iel));
    el.SetisEE(ElectronIsEE->at(iel));

    if(ElectronPassIsoPAT){
      el.SetElectronPassId(ElectronPassIsoPAT->at(iel));
    }
    else{
      el.SetElectronPassId(-999);
    }
    el.SetTrackerDrivenSeed(ElectronHasTrackerDrivenSeed->at(iel));
    el.SetEcalDrivenSeed(ElectronHasEcalDrivenSeed->at(iel));
    el.SetPtEtaPhiE(ElectronPt->at(iel),ElectronEta->at(iel),ElectronPhi->at(iel),ElectronEnergy->at(iel));
    el.SetTrkIso(ElectronPFPhotonIso03->at(iel));
    el.SetECalIso(ElectronPFNeutralHadronIso03->at(iel));
    el.SetHCalIso(ElectronPFChargedHadronIso03->at(iel));
    el.SetCharge(ElectronCharge->at(iel));
    el.SetChargeConsistency(ElectronGsfCtfScPixCharge->at(iel));
    el.SetMissingHits(ElectronMissingHitsEG->at(iel));
    el.SetHasMatchedConvPhot(ElectronHasMatchedConvPhot->at(iel));
    el.SetDeltaEtaTrkSC(ElectronDeltaEtaTrkSC->at(iel));
    el.SetDeltaPhiTrkSC(ElectronDeltaPhiTrkSC->at(iel));
    el.SetSigmaIEtaIEta(ElectronSigmaIEtaIEta->at(iel));
    el.SetHoE(ElectronHoE->at(iel));
    el.SetcaloEnergy(ElectronCaloEnergy->at(iel));
    el.SetSuperClusterOverP(ElectronESuperClusterOverP->at(iel));
    el.SetTrkVx(ElectronTrackVx->at(iel));
    el.SetTrkVy(ElectronTrackVy->at(iel));
    el.SetTrkVz(ElectronTrackVz->at(iel));
        
    if(VertexN != -1){
      el.Setdz( ElectronTrackVz->at(iel) - VertexZ->at(VertexN));
      el.Setdxy( sqrt(pow(ElectronTrackVx->at(iel)-VertexX->at(VertexN),2)+pow(ElectronTrackVy->at(iel)-VertexY->at(VertexN),2)));

    }
    else if (VertexN == -999.){
      snu::KEvent ev = SKTreeFiller::GetEventInfo();
      el.Setdz( ElectronTrackVz->at(iel) - VertexZ->at(ev.VertexIndex()));
      el.Setdxy( sqrt(pow(ElectronTrackVx->at(iel)-VertexX->at(ev.VertexIndex()),2)+pow(ElectronTrackVy->at(iel)-VertexY->at(ev.VertexIndex()),2)));
    }
    else {
      el.Setdz( -999.);
      el.Setdxy( -999.);
    }


    /// Need to add filling code
    electrons.push_back(el);
  }
  
  std::sort( electrons.begin(), electrons.end(), isHigherPt );


  return electrons;
}


void SKTreeFiller::ERRORMessage(TString comment){
  
  m_logger << ERROR << "SKTreeFiller had a probleming filling " << comment << ". This variable is not present in the current LQntuples." << LQLogger::endmsg;   
}

std::vector<KJet> SKTreeFiller::GetAllJets(){

  std::vector<KJet> jets;
  if(!LQinput){

    for(std::vector<KJet>::iterator kit  = k_inputjets->begin(); kit != k_inputjets->end(); kit++){
      jets.push_back(*kit);
    }
    return jets;
  }

  m_logger << DEBUG << "Filling PFJets" << LQLogger::endmsg;
 
  for (UInt_t ijet=0; ijet< PFJetEta->size(); ijet++) {
    KJet jet;
    
    if(!(PFJetPt && PFJetEta && PFJetPhi && PFJetEnergy )) ERRORMessage("PFJetPtEtaPhi");
    else jet.SetPtEtaPhiE(PFJetPt->at(ijet), PFJetEta->at(ijet), PFJetPhi->at(ijet), PFJetEnergy->at(ijet));
    if(!PFJetEnergyRaw)ERRORMessage("PFJetEnergyRaw");
    else jet.SetJetRawEnergy(PFJetEnergyRaw->at(ijet));
    if(!PFJetEnergyRaw)ERRORMessage("PFJetEnergyRaw");
    else jet.SetJetRawPt(PFJetEnergyRaw->at(ijet));

    // ID cuts
    if(!(PFJetPassLooseID && PFJetPassTightID)) ERRORMessage("JetID");
    else{
      jet.SetJetPassLooseID(PFJetPassLooseID->at(ijet));    
      jet.SetJetPassTightID(PFJetPassTightID->at(ijet));    
    }
        
    /// Jet energy fractions   
    if(!(PFJetNeutralEmEnergyFraction&&PFJetNeutralHadronEnergyFraction&&PFJetChargedEmEnergyFraction&&PFJetChargedHadronEnergyFraction&&PFJetHFEMEnergyFraction&&PFJetMuonEnergyFraction&&PFJetElectronEnergyFraction&&PFJetChargedMuEnergyFraction&&PFJetPhotonEnergyFraction)) ERRORMessage("JetEnergyFraction");
    else{
      jet.SetJetNeutralEmEF(PFJetNeutralEmEnergyFraction->at(ijet));
      jet.SetJetNeutralHEF(PFJetNeutralHadronEnergyFraction->at(ijet));
      jet.SetJetChargedEmEF(PFJetChargedEmEnergyFraction->at(ijet));
      jet.SetJetChargedHEF(PFJetChargedHadronEnergyFraction->at(ijet));
      // NEW
      jet.SetJetHFEMEnergyFraction(PFJetHFEMEnergyFraction->at(ijet));
      jet.SetJetHFHadronEnergyFraction(PFJetHFHadronEnergyFraction->at(ijet));
      jet.SetJetMuonEnergyFraction(PFJetMuonEnergyFraction->at(ijet));
      jet.SetJetElectronEnergyFraction(PFJetElectronEnergyFraction->at(ijet));
      jet.SetJetChargedMuEnergyFraction(PFJetChargedMuEnergyFraction->at(ijet));
      jet.SetJetPhotonEnergyFraction(PFJetPhotonEnergyFraction->at(ijet));
    }
    /// BTAG variables
    if(!(PFJetTrackCountingHighPurBTag&&PFJetCombinedSecondaryVertexBTag&&PFJetJetProbabilityBTag&&PFJetClosestVertexWeighted3DSeparation&&PFJetClosestVertexWeightedXYSeparation&&PFJetClosestVertexWeightedZSeparation))ERRORMessage("JetBtag");
    else{
      jet.SetJetTrackCountingHighPurBTag(PFJetTrackCountingHighPurBTag->at(ijet));
      jet.SetJetSecVertBtag(PFJetCombinedSecondaryVertexBTag->at(ijet));
      jet.SetJetJetProbabilityBTag(PFJetJetProbabilityBTag->at(ijet));
      //jet.SetPFJetJetBProbabilityBTag(PFJetJetBProbabilityBTag->at(ijet)); >>> WHAT IS THIS?
      //jet.SetPFJetSoftMuonBTag(PFJetSoftMuonBTag->at(ijet));
      //jet.SetPFJetSoftMuonByIP3dBTag(PFJetSoftMuonByIP3dBTag->at(ijet));  
      //jet.SetPFJetSoftMuonByPtBTag(PFJetSoftMuonByPtBTag->at(ijet));    
      //jet.PFJetTrackCountingHighPurBTag(PFJetTrackCountingHighPurBTag->at(ijet));  
      
      /// jet tracking/vertex variables
      jet.SetJetClosestVertW3DSep(PFJetClosestVertexWeighted3DSeparation->at(ijet));
      jet.SetJetClosestVertexWeightedXYSeparation(PFJetClosestVertexWeightedXYSeparation->at(ijet));
      jet.SetJetClosestVertexWeightedZSeparation(PFJetClosestVertexWeightedZSeparation->at(ijet));
    }
    /// Multiplicities
    if(!(PFJetChargedMultiplicity&&PFJetNeutralMultiplicity&&PFJetChargedHadronMultiplicity&&PFJetElectronMultiplicity&&PFJetHFEMMultiplicity&&PFJetHFHadronMultiplicity&&PFJetMuonMultiplicity&&PFJetNeutralHadronMultiplicity&&PFJetPhotonMultiplicity))ERRORMessage("JetMultiplicity");
    else{
      jet.SetJetChargedMultiplicity(PFJetChargedMultiplicity->at(ijet));
      jet.SetJetNeutralMultiplicity(PFJetNeutralMultiplicity->at(ijet));
      jet.SetJetChargedHadronMultiplicity(PFJetChargedHadronMultiplicity->at(ijet));
      jet.SetJetElectronMultiplicity(PFJetElectronMultiplicity->at(ijet));
      jet.SetJetHFEMMultiplicity(PFJetHFEMMultiplicity->at(ijet));
      jet.SetJetHFHadronMultiplicity(PFJetHFHadronMultiplicity->at(ijet));
      jet.SetJetMuonMultiplicity(PFJetMuonMultiplicity->at(ijet));
      jet.SetJetNeutralHadronMultiplicity(PFJetNeutralHadronMultiplicity->at(ijet));
      jet.SetJetPhotonMultiplicity(PFJetPhotonMultiplicity->at(ijet));
    }
    /// Tracking
    if(!(PFJetNConstituents&&PFJetBestVertexTrackAssociationIndex&&PFJetBestVertexTrackAssociationFactor))ERRORMessage("JetTrack");
    else{
      jet.SetJetNConstituents(PFJetNConstituents->at(ijet));
      jet.SetJetBestVertexTrackAssociationIndex(PFJetBestVertexTrackAssociationIndex->at(ijet));
      jet.SetJetBestVertexTrackAssociationFactor(PFJetBestVertexTrackAssociationFactor->at(ijet));
    }
    
    // flavour
    jet.SetJetPartonFlavour(PFJetPartonFlavour->at(ijet));

    /// JEC and uncertainties
    jet.SetJetJECUnc(PFJetJECUnc->at(ijet));
    jet.SetJetL1FastJetJEC(PFJetL1FastJetJEC->at(ijet));
    jet.SetJetL2L3ResJEC(PFJetL2L3ResJEC->at(ijet));
    jet.SetJetL2RelJEC(PFJetL2RelJEC->at(ijet));
    jet.SetJetL3AbsJEC(PFJetL3AbsJEC->at(ijet));
    
    if(PFJetScaledDownEnergy&&PFJetScaledUpEnergy&&PFJetScaledDownPt&&PFJetScaledUpPt&&PFJetSmearedDownEnergy&&PFJetSmearedUpEnergy&&PFJetSmearedDownPt&&PFJetSmearedUpPt){
      jet.SetJetScaledDownEnergy(PFJetScaledDownEnergy->at(ijet));
      jet.SetJetScaledUpEnergy(PFJetScaledUpEnergy->at(ijet));
      jet.SetJetScaledDownPt(PFJetScaledDownPt->at(ijet));
      jet.SetJetScaledUpPt(PFJetScaledUpPt->at(ijet));
      jet.SetJetSmearedDownEnergy(PFJetSmearedDownEnergy->at(ijet));
      jet.SetJetSmearedUpEnergy(PFJetSmearedUpEnergy->at(ijet));
      jet.SetJetSmearedDownPt(PFJetSmearedDownPt->at(ijet));
      jet.SetJetSmearedUpPt(PFJetSmearedUpPt->at(ijet));
    }
    else{
      jet.SetJetScaledDownEnergy(-999.);
      jet.SetJetScaledUpEnergy(-999.);
      jet.SetJetScaledDownPt(-999.);
      jet.SetJetScaledUpPt(-999.);
      jet.SetJetSmearedDownEnergy(-999.);
      jet.SetJetSmearedUpEnergy(-999.);
      jet.SetJetSmearedDownPt(-999.);
      jet.SetJetSmearedUpPt(-999.);
    }
    jets.push_back(jet);
  }// end of jet 
  
  std::sort( jets.begin(), jets.end(), isHigherPt );
  return jets;
}

std::vector<KJet> SKTreeFiller::GetAllCaloJets(){

  m_logger << DEBUG << "Filling Cal Jets" << LQLogger::endmsg;
  std::vector<KJet> jets;

  if(!LQinput){

    return jets;
  }
  for (UInt_t ijet=0; ijet< CaloJetEta->size(); ijet++) {
    KJet jet;
    jet.SetPtEtaPhiE(CaloJetPt->at(ijet), CaloJetEta->at(ijet), CaloJetPhi->at(ijet), CaloJetEnergy->at(ijet));
    jet.SetJetPassLooseID(CaloJetPassLooseID->at(ijet));
    jet.SetJetPassTightID(CaloJetPassTightID->at(ijet));    
    
    jets.push_back(jet);
  }
  std::sort( jets.begin(), jets.end(), isHigherPt );
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

  int iglobal=0;
  int ims=0;

  for (UInt_t ilep=0; ilep< MuonEta->size(); ilep++) {
    KMuon muon;
    m_logger << DEBUG << "Filling global pt/eta ... " << LQLogger::endmsg;
    if(!MuonGlobalEta){
      muon.SetPtEtaPhiE(MuonPt->at(ilep),MuonEta->at(ilep),MuonPhi->at(ilep),MuonEnergy->at(ilep));
      muon.SetCharge(MuonCharge->at(ilep));
    }else{
      if(MuonIsGlobal->at(ilep)){
	muon.SetPtEtaPhiM(MuonGlobalPt->at(iglobal), MuonGlobalEta->at(iglobal),MuonGlobalPhi->at(iglobal), 0.105658367);            
	muon.SetCharge(MuonGlobalCharge->at(iglobal));
	iglobal++;
      }
    }

    m_logger << DEBUG << "Filling ms pt/eta ... " << LQLogger::endmsg;
    if(MuonMuonSpecPt){

      if(MuonMuonSpecCharge->at(ilep) !=-999. && MuonMuonSpecCharge->at(ilep) !=0){
	muon.SetMuonMSPt(MuonMuonSpecPt->at(ims));
	muon.SetMuonMSEta(MuonMuonSpecEta->at(ims));
	muon.SetMuonMSPhi(MuonMuonSpecPhi->at(ims));
	muon.SetMuonMSCharge(MuonMuonSpecCharge->at(ims));
	ims++;
      }
      else{
	muon.SetMuonMSPt(-999.);
	muon.SetMuonMSEta(-999.);
	muon.SetMuonMSPhi(-999.);
	muon.SetMuonMSCharge(-999);
      }
    }
    m_logger << DEBUG << "Filling tracker ... " << LQLogger::endmsg;
    if(MuonTrackerCharge){
      muon.SetMuonIDPt(MuonPt->at(ilep));
      muon.SetMuonIDEta(MuonEta->at(ilep));
      muon.SetMuonIDPhi(MuonPhi->at(ilep));
      muon.SetMuonIDCharge(MuonTrackerCharge->at(ilep));  
    }
    muon.SetPtErr(MuonPtError->at(ilep));
    muon.SetEtaErr(MuonEtaError->at(ilep));
   
    muon.SetMuonVtxIndex(MuonVtxIndex->at(ilep));    
    
    m_logger << DEBUG << "Filling isolation ... " << LQLogger::endmsg;
    /// Isolation
    muon.SetISOR03ChargedHad(MuonPFIsoR03ChargedHadron->at(ilep));
    muon.SetISOR03NeutralHad(MuonPFIsoR03NeutralHadron->at(ilep));
    muon.SetISOR03Photon(MuonPFIsoR03Photon->at(ilep));       
    muon.SetIsolationEcalVeto(MuonEcalVetoIso->at(ilep));
    muon.SetIsolationHcalVeto(MuonHcalVetoIso->at(ilep));


    /// PU correction
    muon.SetPileUp_R03(MuonPFIsoR03PU->at(ilep));

    ////////// TRACK
    /// Imapct parameter 
    
    muon.SetTrackVx(MuonTrkVx->at(ilep));
    muon.SetTrackVy(MuonTrkVy->at(ilep));
    muon.SetTrackVz(MuonTrkVz->at(ilep));
    muon.SetVertexDistXY(MuonVtxDistXY->at(ilep));

    m_logger << DEBUG << "Filling IP  ... " << LQLogger::endmsg;
    if(VertexN != -1){
      muon.Setdz( MuonTrkVz->at(ilep) - VertexZ->at(VertexN));
      muon.Setdxy( sqrt(pow(MuonTrkVx->at(ilep)-VertexX->at(VertexN),2)+pow(MuonTrkVy->at(ilep)-VertexY->at(VertexN),2)));
      muon.Setdxy_pat( MuonPrimaryVertexDXY->at(ilep));
      muon.Setdxyerr_pat( MuonPrimaryVertexDXYError->at(ilep));
    }
    else if (VertexN == -999){
      m_logger << WARNING << "WARNING creating vector of KMuon or KElectrons without setting up KEvent " << LQLogger::endmsg;
      snu::KEvent ev = SKTreeFiller::GetEventInfo();
      muon.Setdz( MuonTrkVz->at(ilep) - VertexZ->at(ev.VertexIndex()));
      muon.Setdxy( sqrt(pow(MuonTrkVx->at(ilep)-VertexX->at(ev.VertexIndex()),2)+pow(MuonTrkVy->at(ilep)-VertexY->at(ev.VertexIndex()),2)));      
    }
    else {
      muon.Setdz(  -999.);
      muon.Setdxy(  -999.);
    }
    muon.SetD0( MuonTrkD0->at(ilep));
    muon.SetD0Error (MuonTrkD0Error->at(ilep));
    //// chi2
    muon.SetGlobalchi2( MuonGlobalChi2->at(ilep));
        
    /// hits
    muon.SetValidHits( MuonGlobalTrkValidHits->at(ilep));
    muon.SetPixelValidHits(  MuonTrkPixelHits->at(ilep));
    muon.SetValidStations( MuonStationMatches->at(ilep));
    muon.SetLayersWithMeasurement ( MuonTrackLayersWithMeasurement->at(ilep));

    m_logger << DEBUG << "Muon Truth " << LQLogger::endmsg;

    /// truth info
    if(!isData){
      muon.SetMuonMatchedGenParticleEta(MuonMatchedGenParticleEta->at(ilep));
      muon.SetMuonMatchedGenParticlePhi(MuonMatchedGenParticlePhi->at(ilep));
      muon.SetMuonMatchedGenParticlePt(MuonMatchedGenParticlePt->at(ilep));
      
      bool matched_muon(false);
      int iMother(-999),iDaughter(-999), ipdgid(-999), truemu_index(-999);
      ///// ADD prompt definition for MC
      double truth_reco_dr(1000000.);
      
      m_logger << DEBUG <<  "Muon Eta  = " << MuonEta->at(ilep) << LQLogger::endmsg;
      m_logger << DEBUG <<  "Muon Phi  = " << MuonPhi->at(ilep) << LQLogger::endmsg;
      m_logger << DEBUG <<  "Muon Pt  = " << MuonPt->at(ilep) << LQLogger::endmsg;
      
      for(unsigned int g =0; g < GenParticleP->size(); g++){
	m_logger << DEBUG <<  g << " " <<  GenParticleStatus->size() << " " << GenParticlePdgId->size() << LQLogger::endmsg;
	m_logger << DEBUG << GenParticleStatus->at(g) << " " << GenParticlePdgId->at(g) << LQLogger::endmsg;
	
	if((fabs(MuonEta->at(ilep) - GenParticleEta->at(g)) < 0.1) && (fabs(TVector2::Phi_mpi_pi(MuonPhi->at(ilep) -GenParticlePhi->at(g))) < 0.1)) {
	  /// This is the case when no truth particle is matched to the reco muon in the LeptoQuark Ntuple making. 
	  // This happens when two reco muons are on top of each other (one MS muon and one CB muon). The MS muon is matched to the truth. Only one reco muon is matched and so the CB muon is not assigned a truth particle.
	  if( (GenParticleStatus->at(g) == 3) && fabs(GenParticlePdgId->at(g))==13){
	    double dr = sqrt( pow(fabs(MuonEta->at(ilep) - GenParticleEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonPhi->at(ilep) -GenParticlePhi->at(g))),2.0));
	    
	    /// if this is the closest matching muon then assign it as matched truth                                                                                      
	    if(dr < truth_reco_dr){
	      iMother = GenParticleMotherIndex->at(g);
	      iDaughter = GenParticleNumDaught->at(g);
	      ipdgid =  GenParticlePdgId->at(g);
	      truemu_index = g;
	      matched_muon = true;
	      truth_reco_dr = dr;
	    }//closest truth match
	  }/// stable muon
	}// end of else if
	
	int MotherPdgId(-999);
	if(matched_muon){
	  MotherPdgId =  GenParticlePdgId->at(iMother);
	}
	
	if (isPrompt( MotherPdgId)){
	  if ( MuonCharge->at(ilep)* GenParticlePdgId->at(ilep)   > 0)   partType = KParticle::chargemisid;
	  else partType = KParticle::notfake;
	}
	else {
	  if ( nthdigit( abs(MotherPdgId ),0 ) == 5 || nthdigit( abs(MotherPdgId ),1 ) == 5 || nthdigit( abs(MotherPdgId ),2 ) == 5) partType = KParticle::bjet;    
	  else if ( nthdigit( abs(MotherPdgId ),0 ) == 4 || nthdigit( abs(MotherPdgId ),1 ) == 4 || nthdigit( abs(MotherPdgId ),2 ) == 4) partType = KParticle::cjet;
	  else if
	    (nthdigit( abs(MotherPdgId ),0 ) == 1 || nthdigit( abs(MotherPdgId ),1 ) == 1 || nthdigit( abs(MotherPdgId ),2 ) == 1
	     || nthdigit( abs(MotherPdgId ),0 ) == 2 || nthdigit( abs(MotherPdgId ),1 ) == 2 || nthdigit( abs(MotherPdgId ),2 ) == 2
	     || nthdigit( abs(MotherPdgId ),0 ) == 3 || nthdigit( abs(MotherPdgId ),1 ) == 3 || nthdigit( abs(MotherPdgId ),2 ) == 3 )	
	    partType = KParticle::jet;
	}
	
	muon.SetType(partType);
	muon.SetTruthParticleIndex(truemu_index);      
	muon.SetMotherIndex(iMother);
	muon.SetDaughterIndex(iDaughter);
      }
      
      truth_reco_dr=100000.;
      for(unsigned int g =0; g < GenZMuP->size(); g++){
	if((fabs(GenZMuPdgId->at(g))==13)){ 
	  double dr = sqrt( pow(fabs(MuonEta->at(ilep) - GenZMuEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonPhi->at(ilep) -GenZMuPhi->at(g))),2.0) );	  
	  if(dr < truth_reco_dr){
	    ipdgid =  GenZMuPdgId->at(g);
	    truemu_index = g;
	    truth_reco_dr = dr;
	  }
	}
	muon.SetType(partType);
        muon.SetTruthParticleIndex(truemu_index);
      }
    }	


    double reliso = (MuonPFIsoR03ChargedHadron->at(ilep) + std::max(0.0, MuonPFIsoR03NeutralHadron->at(ilep) + MuonPFIsoR03Photon->at(ilep) - 0.5*MuonPFIsoR03PU->at(ilep)))/MuonPt->at(ilep);
    if(reliso < 0) reliso = 0.0001;
    muon.SetRelIso(reliso);
    
    /// GENERAL
    muon.SetISPF(MuonIsPF->at(ilep));
    muon.SetIsGlobal(MuonIsGlobal->at(ilep));
    m_logger << DEBUG << "Add muon to vector " << LQLogger::endmsg;
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

    return vtruth;
  }

  int itruth(0);
  for (UInt_t it=0; it< GenParticleEta->size(); it++, itruth++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenParticlePt->at(it), GenParticleEta->at(it), GenParticlePhi->at(it), GenParticleEnergy->at(it));
    truthp.SetParticlePx(GenParticlePx->at(it));
    truthp.SetParticlePy(GenParticlePy->at(it));
    truthp.SetParticlePz(GenParticlePz->at(it));
    if(GenParticleVX){
      truthp.SetParticleVx(GenParticleVX->at(it));
      truthp.SetParticleVy(GenParticleVY->at(it));
      truthp.SetParticleVz(GenParticleVZ->at(it));
    }
    truthp.SetParticlePdgId(GenParticlePdgId->at(it));
    truthp.SetParticleStatus(GenParticleStatus->at(it));

    truthp.SetParticleIndexDaughter(GenParticleNumDaught->at(it));
    truthp.SetParticleIndexMother(GenParticleMotherIndex->at(it));
    
    float charge_truth = -999.;
    if(GenParticlePdgId->at(it) == 1 || GenParticlePdgId->at(it) == 3 || GenParticlePdgId->at(it) == 5) charge_truth = -1./3.;
    else if(GenParticlePdgId->at(it) == 2 || GenParticlePdgId->at(it) == 4 || GenParticlePdgId->at(it) == 6) charge_truth = 2./3.;
    else if(GenParticlePdgId->at(it) == 11 || GenParticlePdgId->at(it) ==13 || GenParticlePdgId->at(it) ==15) charge_truth = -1.;
    else if(GenParticlePdgId->at(it) == 12 || GenParticlePdgId->at(it) ==14 || GenParticlePdgId->at(it) ==16) charge_truth = 0.;
    else if(GenParticlePdgId->at(it) == 22 || GenParticlePdgId->at(it) == 23) charge_truth = 0.;
    else if(GenParticlePdgId->at(it) == 24) charge_truth =1.;
    else charge_truth = -999.;
    
    if(GenParticlePdgId->at(it) < 0) charge_truth *=-1.;

    truthp.SetIndex(itruth);
    vtruth.push_back(truthp);
  }/// end of filling loop

  for (UInt_t it=0; it< GenZMuEta->size(); it++, itruth++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZMuPt->at(it), GenZMuEta->at(it), GenZMuPhi->at(it), GenZMuEnergy->at(it));
    truthp.SetParticlePx(GenZMuPx->at(it));
    truthp.SetParticlePy(GenZMuPy->at(it));
    truthp.SetParticlePz(GenZMuPz->at(it));
    if(GenZMuVX){
      truthp.SetParticleVx(GenZMuVX->at(it));
      truthp.SetParticleVy(GenZMuVY->at(it));
      truthp.SetParticleVz(GenZMuVZ->at(it));
    }
    truthp.SetParticlePdgId(GenZMuPdgId->at(it));
    truthp.SetParticleStatus(GenZMuStatus->at(it));

    truthp.SetParticleIndexDaughter(GenZMuNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZMuMotherIndex->at(it));

    float charge_truth = -999.;
    if(GenZMuPdgId->at(it) == 1 || GenZMuPdgId->at(it) == 3 || GenZMuPdgId->at(it) == 5) charge_truth = -1./3.;
    else if(GenZMuPdgId->at(it) == 2 || GenZMuPdgId->at(it) == 4 || GenZMuPdgId->at(it) == 6) charge_truth = 2./3.;
    else if(GenZMuPdgId->at(it) == 11 || GenZMuPdgId->at(it) ==13 || GenZMuPdgId->at(it) ==15) charge_truth = -1.;
    else if(GenZMuPdgId->at(it) == 12 || GenZMuPdgId->at(it) ==14 || GenZMuPdgId->at(it) ==16) charge_truth = 0.;
    else if(GenZMuPdgId->at(it) == 22 || GenZMuPdgId->at(it) == 23) charge_truth = 0.;
    else if(GenZMuPdgId->at(it) == 24) charge_truth =1.;
    else charge_truth = -999.;

    if(GenZMuPdgId->at(it) < 0) charge_truth *=-1.;

    truthp.SetIndex(itruth);
    vtruth.push_back(truthp);    
  }
  
  for (UInt_t it=0; it< GenZTauEta->size(); it++, itruth++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZTauPt->at(it), GenZTauEta->at(it), GenZTauPhi->at(it), GenZTauEnergy->at(it));
    truthp.SetParticlePx(GenZTauPx->at(it));
    truthp.SetParticlePy(GenZTauPy->at(it));
    truthp.SetParticlePz(GenZTauPz->at(it));
    if(GenZTauVX){
      truthp.SetParticleVx(GenZTauVX->at(it));
      truthp.SetParticleVy(GenZTauVY->at(it));
      truthp.SetParticleVz(GenZTauVZ->at(it));
    }
    truthp.SetParticlePdgId(GenZTauPdgId->at(it));
    truthp.SetParticleStatus(GenZTauStatus->at(it));

    truthp.SetParticleIndexDaughter(GenZTauNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZTauMotherIndex->at(it));

    float charge_truth = -999.;
    if(GenZTauPdgId->at(it) == 1 || GenZTauPdgId->at(it) == 3 || GenZTauPdgId->at(it) == 5) charge_truth = -1./3.;
    else if(GenZTauPdgId->at(it) == 2 || GenZTauPdgId->at(it) == 4 || GenZTauPdgId->at(it) == 6) charge_truth = 2./3.;
    else if(GenZTauPdgId->at(it) == 11 || GenZTauPdgId->at(it) ==13 || GenZTauPdgId->at(it) ==15) charge_truth = -1.;
    else if(GenZTauPdgId->at(it) == 12 || GenZTauPdgId->at(it) ==14 || GenZTauPdgId->at(it) ==16) charge_truth = 0.;
    else if(GenZTauPdgId->at(it) == 22 || GenZTauPdgId->at(it) == 23) charge_truth = 0.;
    else if(GenZTauPdgId->at(it) == 24) charge_truth =1.;
    else charge_truth = -999.;

    if(GenZTauPdgId->at(it) < 0) charge_truth *=-1.;

    truthp.SetIndex(itruth);
    vtruth.push_back(truthp);
  }


  for (UInt_t it=0; it< GenZMuEta->size(); it++, itruth++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZMuPt->at(it), GenZMuEta->at(it), GenZMuPhi->at(it), GenZMuEnergy->at(it));
    truthp.SetParticlePx(GenZMuPx->at(it));
    truthp.SetParticlePy(GenZMuPy->at(it));
    truthp.SetParticlePz(GenZMuPz->at(it));
    if(GenZMuVX){
      truthp.SetParticleVx(GenZMuVX->at(it));
      truthp.SetParticleVy(GenZMuVY->at(it));
      truthp.SetParticleVz(GenZMuVZ->at(it));
    }
    truthp.SetParticlePdgId(GenZMuPdgId->at(it));
    truthp.SetParticleStatus(GenZMuStatus->at(it));

    truthp.SetParticleIndexDaughter(GenZMuNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZMuMotherIndex->at(it));

    float charge_truth = -999.;
    if(GenZMuPdgId->at(it) == 1 || GenZMuPdgId->at(it) == 3 || GenZMuPdgId->at(it) == 5) charge_truth = -1./3.;
    else if(GenZMuPdgId->at(it) == 2 || GenZMuPdgId->at(it) == 4 || GenZMuPdgId->at(it) == 6) charge_truth = 2./3.;
    else if(GenZMuPdgId->at(it) == 11 || GenZMuPdgId->at(it) ==13 || GenZMuPdgId->at(it) ==15) charge_truth = -1.;
    else if(GenZMuPdgId->at(it) == 12 || GenZMuPdgId->at(it) ==14 || GenZMuPdgId->at(it) ==16) charge_truth = 0.;
    else if(GenZMuPdgId->at(it) == 22 || GenZMuPdgId->at(it) == 23) charge_truth = 0.;
    else if(GenZMuPdgId->at(it) == 24) charge_truth =1.;
    else charge_truth = -999.;

    if(GenZMuPdgId->at(it) < 0) charge_truth *=-1.;

    truthp.SetIndex(itruth);
    vtruth.push_back(truthp);
  }



  return vtruth;
}



 
