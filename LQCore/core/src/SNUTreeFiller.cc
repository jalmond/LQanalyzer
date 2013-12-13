#include "SNUTreeFiller.h"
#include <stdio.h>  

#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;


SNUTreeFiller::SNUTreeFiller() :Data() {
  VertexN = -999; //// set event vertex to dummy number 
};


SNUTreeFiller::~SNUTreeFiller() {};

snu::KTrigger SNUTreeFiller::GetTriggerInfo(std::vector<TString> trignames){
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

snu::KEvent SNUTreeFiller::GetEventInfo(){
 
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


std::vector<KTau> SNUTreeFiller::GetAllTaus(){
  
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

std::vector<KElectron> SNUTreeFiller::GetAllElectrons(){

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
      snu::KEvent ev = SNUTreeFiller::GetEventInfo();
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

std::vector<KJet> SNUTreeFiller::GetAllJets(){

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

    jet.SetPtEtaPhiE(PFJetPt->at(ijet), PFJetEta->at(ijet), PFJetPhi->at(ijet), PFJetEnergy->at(ijet));
    jet.SetPassLooseID(PFJetPassLooseID->at(ijet));    
    jet.SetNeutralEmEF(PFJetNeutralEmEnergyFraction->at(ijet));
    jet.SetNeutralHEF(PFJetNeutralHadronEnergyFraction->at(ijet));
    jet.SetChargedEmEF(PFJetChargedEmEnergyFraction->at(ijet));
    jet.SetChargedHEF(PFJetChargedHadronEnergyFraction->at(ijet));
    jet.SetChargedMult(PFJetChargedMultiplicity->at(ijet));
    jet.SetJetNCon(PFJetNConstituents->at(ijet));
    jet.SetJetSecVertBtag(PFJetCombinedSecondaryVertexBTag->at(ijet));
    jet.SetClosestVertW3DSep(PFJetClosestVertexWeighted3DSeparation->at(ijet));
    jet.SetPFJetTrackCountingHighPurBTag(PFJetTrackCountingHighPurBTag->at(ijet));
    jet.SetPFJetJetProbabilityBTag(PFJetJetProbabilityBTag->at(ijet));
    jet.SetPFJetClosestVertexWeightedXYSeparation(PFJetClosestVertexWeightedXYSeparation->at(ijet));
    jet.SetPFJetClosestVertexWeightedZSeparation(PFJetClosestVertexWeightedZSeparation->at(ijet));
       
    jets.push_back(jet);
  }// end of jet 
  
  std::sort( jets.begin(), jets.end(), isHigherPt );
  return jets;
}

std::vector<KJet> SNUTreeFiller::GetAllCaloJets(){

  m_logger << DEBUG << "Filling Cal Jets" << LQLogger::endmsg;
  std::vector<KJet> jets;

  if(!LQinput){

    return jets;
  }
  for (UInt_t ijet=0; ijet< CaloJetEta->size(); ijet++) {
    KJet jet;
    jet.SetPtEtaPhiE(CaloJetPt->at(ijet), CaloJetEta->at(ijet), CaloJetPhi->at(ijet), CaloJetEnergy->at(ijet));
    jet.SetPassLooseID(CaloJetPassLooseID->at(ijet));
    jet.SetPassTightID(CaloJetPassTightID->at(ijet));    
    
    jets.push_back(jet);
  }
  std::sort( jets.begin(), jets.end(), isHigherPt );
  return jets;
}

std::vector<KMuon> SNUTreeFiller::GetAllMuons(){

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
    if(MuonMuonSpecPt){
      if(MuonMuonSpecCharge->at(ilep) !=0.){
	muon.SetMuonMSPt(MuonMuonSpecPt->at(ims));
	muon.SetMuonMSEta(MuonMuonSpecEta->at(ims));
	muon.SetMuonMSPhi(MuonMuonSpecPhi->at(ims));
	muon.SetMuonMSCharge(MuonMuonSpecCharge->at(ims));
	ims++;
      }
      else{
	muon.SetMuonMSPt(0.);
	muon.SetMuonMSEta(0.);
	muon.SetMuonMSPhi(0.);
	muon.SetMuonMSCharge(0);
      }
    }
    if(MuonTrackerCharge){
      muon.SetMuonIDPt(MuonPt->at(ilep));
      muon.SetMuonIDEta(MuonEta->at(ilep));
      muon.SetMuonIDPhi(MuonPhi->at(ilep));
      muon.SetMuonIDCharge(MuonTrackerCharge->at(ilep));  
    }
    muon.SetPtErr(MuonPtError->at(ilep));
    muon.SetEtaErr(MuonEtaError->at(ilep));
   
    muon.SetMuonVtxIndex(MuonVtxIndex->at(ilep));    
    
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

    if(VertexN != -1){
      muon.Setdz( MuonTrkVz->at(ilep) - VertexZ->at(VertexN));
      muon.Setdxy( sqrt(pow(MuonTrkVx->at(ilep)-VertexX->at(VertexN),2)+pow(MuonTrkVy->at(ilep)-VertexY->at(VertexN),2)));
      muon.Setdxy_pat( MuonPrimaryVertexDXY->at(ilep));
      muon.Setdxyerr_pat( MuonPrimaryVertexDXYError->at(ilep));
    }
    else if (VertexN == -999){
      m_logger << WARNING << "WARNING creating vector of KMuon or KElectrons without setting up KEvent " << LQLogger::endmsg;
      snu::KEvent ev = SNUTreeFiller::GetEventInfo();
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
      for(unsigned int g =0; g < GenParticleP->size(); g++){
	m_logger << DEBUG <<  g << GenParticleStatus->size() << " " << GenParticlePdgId->size() << LQLogger::endmsg;
	m_logger << DEBUG << GenParticleStatus->at(g) << " " << GenParticlePdgId->at(g) << LQLogger::endmsg;
	if((GenParticleStatus->at(g) == 3) &&fabs(GenParticlePdgId->at(g))==13){
	  if( muon.MuonMatchedGenParticleEta() != -999){	   
	    if((fabs(muon.MuonMatchedGenParticleEta() - GenParticleEta->at(g)) < 0.2) && (fabs(muon.MuonMatchedGenParticlePhi() -GenParticlePhi->at(g)) < 0.2)) {	      
	      if( (GenParticleStatus->at(g) == 3) && fabs(GenParticlePdgId->at(g))==13){
		iMother = GenParticleMotherIndex->at(g);
		iDaughter = GenParticleNumDaught->at(g);
		ipdgid =  GenParticlePdgId->at(g);	
		truemu_index = g;
		matched_muon = true;
	      }
	    }
	  }
	  else {
	    iMother = -999;
	    iDaughter = -999;
	    ipdgid = -999;
	    truemu_index = -999;
	  }
	}      
      }/// end gen loop    
      
      int MotherPdgId(-999);
      if(matched_muon){
	MotherPdgId =  GenParticlePdgId->at(iMother);
      }
      
      if (isPrompt( MotherPdgId)){
	if ( MuonCharge->at(ilep)*MotherPdgId  == -24 || MuonCharge->at(ilep)*MotherPdgId  == 15 )
	  partType = KParticle::chargemisid;
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

    double reliso = (MuonPFIsoR03ChargedHadron->at(ilep) + std::max(0.0, MuonPFIsoR03NeutralHadron->at(ilep) + MuonPFIsoR03Photon->at(ilep) - 0.5*MuonPFIsoR03PU->at(ilep)))/MuonPt->at(ilep);
    if(reliso < 0) reliso = 0.0001;
    muon.SetRelIso(reliso);
         
    /// GENERAL
    muon.SetISPF(MuonIsPF->at(ilep));
    muon.SetIsGlobal(MuonIsGlobal->at(ilep));
    
    /// Fill vector
    muons.push_back(muon);
  }
  
  std::sort( muons.begin(), muons.end(), isHigherPt );

  return muons;
}



std::vector<snu::KTruth>   SNUTreeFiller::GetTruthParticles(){

  m_logger << DEBUG << "Filling Truth" << LQLogger::endmsg;
  std::vector<snu::KTruth> vtruth;
  if(!LQinput){

    return vtruth;
  }

  int itruth(0);
  for (UInt_t it=0; it< GenParticleEta->size(); it++, itruth++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenParticlePt->at(it), GenParticleEta->at(it), GenParticlePhi->at(0), GenParticleEnergy->at(it));
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
    
    if(GenParticlePdgId->at(it) < 0) charge_truth *=1.;

    truthp.SetIndex(itruth);
    vtruth.push_back(truthp);
  }/// end of filling loop
  
  return vtruth;
}



 
