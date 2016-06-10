#include "SKTreeFiller.h"
#include <stdio.h>  

#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;


SKTreeFiller::SKTreeFiller() :Data() {
  
  TString fitParametersFile = "";
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
  
  /// MET variables
  // PF met
  kevent.SetPFMET( PFMETType01XYCor->at(0));
  kevent.SetPFMETx( PFMETxType01XYCor->at(0));
  kevent.SetPFMETy( PFMETyType01XYCor->at(0));
  m_logger << DEBUG << "Filling Event 2" << LQLogger::endmsg;

  kevent.SetPFMETRaw( PFMET->at(0));
  kevent.SetPFMETxRaw( PFMETx->at(0));
  kevent.SetPFMETyRaw( PFMETy->at(0));

  kevent.SetPFMETType1( PFMETType1Cor->at(0));
  kevent.SetPFMETType01( PFMETType01Cor->at(0));
  kevent.SetPFMETphi( PFMETPhiType01XYCor->at(0));
  kevent.SetPFMETRawphi( PFMETPhi->at(0));
  kevent.SetPFMETType1phi( PFMETPhiType1Cor->at(0));
  
  kevent.SetPFMETType01phi( PFMETPhiType01Cor->at(0));
 
  kevent.SetPFSumET( PFSumETType01XYCor->at(0));
  

  kevent.SetProcessID(ProcessID);

  m_logger << DEBUG << "Filling Event 3" << LQLogger::endmsg;
  if(!isData){
    if(PDFCTEQWeights){
      /// This will have to take in a vector for any systematic studies
      if(PDFCTEQWeights->size() > 0){
	kevent.SetPDFCTEQWeight(*PDFCTEQWeights);
	kevent.SetPDFMSTWWeight(*PDFMSTWWeights);
	kevent.SetPDFNNPDFWeight(*PDFNNPDFWeights);
      }
    }
  }
  //// Filling vertex variables
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
  
  
  kevent.SetVertexIndex(VertexN); /// setting event vertex (chooses vertex that passes selection of a good vertex with sum pt of all tracks is greatest
  
  if(VertexN != -999){
    /// This is the X/Y/Z coordinate of the Primary vertex
    kevent.SetVertexX(VertexX->at(VertexN));
    kevent.SetVertexY(VertexY->at(VertexN));
    kevent.SetVertexZ(VertexZ->at(VertexN));  
    kevent.SetVertexIsFake(VertexIsFake->at(VertexN));
  }
  else VertexN = -1;


  /// Filling JetRho for PFisolation pile up corrections
  kevent.SetJetRho(rhoJets);

  /// Filling event variables
  kevent.SetIsData(isData);
  if(!isData)kevent.SetWeight(Weight);
  else kevent.SetWeight(0.);
  kevent.SetRunNumber(run);
  kevent.SetEventNumber(event);
  kevent.SetLumiSection(ls);
  
  /// MET filter cuts/checks
  kevent.SetIsTrackingFailure(isTrackingFailure);
  kevent.SetIsBeamScraping(isBeamScraping);
  kevent.SetPassTrackingFailureFilter(passTrackingFailureFilter);
  kevent.SetPassBeamHaloFilterLoose(passBeamHaloFilterLoose);
  if(passBeamHaloFilterTight)kevent.SetPassBeamHaloFilterTight(passBeamHaloFilterTight);
  kevent.SetPassBadEESupercrystalFilter(passBadEESupercrystalFilter);
  kevent.SetPassEcalDeadCellBoundaryEnergyFilter(passEcalDeadCellBoundaryEnergyFilter);
  kevent.SetPassEcalDeadCellTriggerPrimitiveFilter(passEcalDeadCellTriggerPrimitiveFilter);
  kevent.SetPassEcalLaserCorrFilter(passEcalLaserCorrFilter);
  kevent.SetPassHBHENoiseFilter(passHBHENoiseFilter);
  kevent.SetPassHcalLaserEventFilter(passHcalLaserEventFilter);

  /// 
  if(!isData)kevent.SetPileUpInteractionsTrue(PileUpInteractionsTrue->at(0));
  else kevent.SetPileUpInteractionsTrue(-999.);
  
  return kevent;
}


std::vector<KTau> SKTreeFiller::GetAllTaus(){
  
  std::vector<KTau> taus;
  if(!LQinput){
    
    return taus;
  }


  return taus;
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

  for (UInt_t iel=0; iel< ElectronLooseEta->size(); iel++) {
    KElectron el;
    
    /// Kinematic Variables
    el.SetPtEtaPhiE(ElectronLoosePt->at(iel),ElectronLooseEta->at(iel),ElectronLoosePhi->at(iel),ElectronLooseEnergy->at(iel));
    m_logger << DEBUG << "Filling ElectronLoose ID Bit "<< LQLogger::endmsg;
    el.SetPx(ElectronLoosePx->at(iel));
    el.SetPy(ElectronLoosePy->at(iel));
    el.SetisEB(ElectronLooseIsEB->at(iel));
    el.SetisEE(ElectronLooseIsEE->at(iel));

    el.SetSCEta(ElectronLooseSCEta->at(iel));
    el.SetSCPhi(ElectronLooseSCPhi->at(iel));
    el.SetSCPt(ElectronLooseSCPt->at(iel));
    el.SetRawEnergy(ElectronLooseSCRawEnergy->at(iel));
    
    m_logger << DEBUG << "Filling ElectronLoose ID Bit "<< LQLogger::endmsg;
    
    if(ElectronLoosemvatrigV0){
      el.SetElectronTrigMVA(ElectronLoosemvatrigV0->at(iel));
      el.SetElectronMVA(ElectronLoosemvaNontrigV0->at(iel));
    }
    

    m_logger << DEBUG << "Filling ElectronLoose ID variablest "<< LQLogger::endmsg;
    /// set ID variables
    
    el.SetTrackerDrivenSeed(ElectronLooseHasTrackerDrivenSeed->at(iel));
    el.SetEcalDrivenSeed(ElectronLooseHasEcalDrivenSeed->at(iel));
    el.SetDeltaEtaTrkSC(ElectronLooseDeltaEtaTrkSC->at(iel));
    el.SetDeltaPhiTrkSC(ElectronLooseDeltaPhiTrkSC->at(iel));
    el.SetSigmaIEtaIEta(ElectronLooseSigmaIEtaIEta->at(iel));
    el.SetHoE(ElectronLooseHoE->at(iel));
    el.SetcaloEnergy(ElectronLooseCaloEnergy->at(iel));
    el.SetESuperClusterOverP(ElectronLooseESuperClusterOverP->at(iel));

    m_logger << DEBUG << "Filling ElectronLoose vertex info "<< LQLogger::endmsg;
    //// distance of closest vertex to lepton
    el.SetVtxDistXY(ElectronLooseVtxDistXY->at(iel));
    el.SetVtxDistZ(ElectronLooseVtxDistZ->at(iel));
    el.SetLeadVtxDistXY(ElectronLooseLeadVtxDistXY->at(iel));
    el.SetLeadVtxDistZ(ElectronLooseLeadVtxDistZ->at(iel));
    
    el.SetVtxIndex(ElectronLooseVtxIndex->at(iel));
    el.SetPrimaryVertexDXY(ElectronLooseLeadVtxDistXY->at(iel));
    el.SetPrimaryVertexDXYError(ElectronLoosePrimaryVertexDXYError->at(iel));
    el.SetTrackPt(ElectronLooseTrackPt->at(iel));
    el.SetTrackValidFractionOfHits(ElectronLooseTrackValidFractionOfHits->at(iel));
    el.SetTrkVx(ElectronLooseTrackVx->at(iel));
    el.SetTrkVy(ElectronLooseTrackVy->at(iel));
    el.SetTrkVz(ElectronLooseTrackVz->at(iel));
    /// distance between lepton and PRIMARY analysis vertex
    

    

    //cout << "\n ----- " << endl;
    //cout << "Lead vertex dxy = " << ElectronLooseLeadVtxDistXY->at(iel) << endl;
    //cout << "Primary vertex dxy = " << ElectronLoosePrimaryVertexDXY->at(iel) << endl;
    //cout << "Closest vertex dxy = " << ElectronLooseVtxDistXY->at(iel) << endl;
  
    if(VertexN != -1){
      //cout << "Setting dz for electron, using method 1 : vertexN = " <<  VertexN << endl;
      //cout << "ElectronLooseTrackVz =  " << ElectronLooseTrackVz->at(iel)<< " : VertexZ = " << VertexZ->at(VertexN) << endl;
      el.Setdz( ElectronLooseTrackVz->at(iel) - VertexZ->at(VertexN));
      el.Setdxy( sqrt(pow(ElectronLooseTrackVx->at(iel)-VertexX->at(VertexN),2)+pow(ElectronLooseTrackVy->at(iel)-VertexY->at(VertexN),2)));
      if(VertexN != 0){
	//cout << "Setting dxy of electron " << ElectronLooseTrackVx->at(iel) <<  " " << VertexX->at(VertexN) << " " << ElectronLooseTrackVy->at(iel)<< " " << VertexY->at(VertexN) << endl;
	//cout << "vertex = " << VertexN << endl;
      }
      //cout << "electron vertex = " << ElectronLooseVtxIndex->at(iel) << " event vertex = " << VertexN << endl; 
      //cout << "event dxy = " << sqrt(pow(ElectronLooseTrackVx->at(iel)-VertexX->at(VertexN),2)+pow(ElectronLooseTrackVy->at(iel)-VertexY->at(VertexN),2)) << endl; 
      //cout << "event dxy (el vertex) = " << sqrt(pow(ElectronLooseTrackVx->at(iel)-VertexX->at(ElectronLooseVtxIndex->at(iel)),2)+pow(ElectronLooseTrackVy->at(iel)-VertexY->at(ElectronLooseVtxIndex->at(iel)),2)) << endl; 
    }
    else if (VertexN == -999.){

      snu::KEvent ev = SKTreeFiller::GetEventInfo();
      cout << "ElectronLooseTrackVz =  " << ElectronLooseTrackVz->at(iel) << " : VertexZ = " << VertexZ->at(ev.VertexIndex()) << " : VertexN = " << ev.VertexIndex() << endl;
      el.Setdz( ElectronLooseTrackVz->at(iel) - VertexZ->at(ev.VertexIndex()));
      el.Setdxy( sqrt(pow(ElectronLooseTrackVx->at(iel)-VertexX->at(ev.VertexIndex()),2)+pow(ElectronLooseTrackVy->at(iel)-VertexY->at(ev.VertexIndex()),2)));
    }
    else {
      el.Setdz( -999.);
      el.Setdxy( -999.);
    }

    m_logger << DEBUG << "Filling isolation variables " << LQLogger::endmsg;
    /// Set Isolation variables
    m_logger << DEBUG << ElectronLooseTrkIsoDR03 << " " << ElectronLooseEcalIsoDR03 << " " << ElectronLooseHcalIsoDR03 << LQLogger::endmsg;

    el.SetTrkIsoDR03(ElectronLooseTrkIsoDR03->at(iel));
    el.SetECalIsoDR03(ElectronLooseEcalIsoDR03->at(iel));
    el.SetHCalIsoDR03(ElectronLooseHcalIsoDR03->at(iel));
    if(ElectronLooseTrkIsoPAT){
      el.SetTrkIsoDR04(ElectronLooseTrkIsoPAT->at(iel));
      el.SetECalIsoDR04(ElectronLooseEcalIsoPAT->at(iel));
      el.SetHCalIsoDR04(ElectronLooseHcalIsoPAT->at(iel));
    }
    m_logger << DEBUG << "Filling PF03 isolation variables " << LQLogger::endmsg;
    
    el.SetPFChargedHadronIso03(ElectronLoosePFChargedHadronIso03->at(iel));
    el.SetPFPhotonIso03(ElectronLoosePFPhotonIso03->at(iel));
    el.SetPFNeutralHadronIso03(ElectronLoosePFNeutralHadronIso03->at(iel));

    m_logger << DEBUG << "Filling PF04 isolation variables " << LQLogger::endmsg;
    el.SetPFChargedHadronIso04(ElectronLoosePFChargedHadronIso04->at(iel));
    el.SetPFPhotonIso04(ElectronLoosePFPhotonIso04->at(iel));
    el.SetPFNeutralHadronIso04(ElectronLoosePFNeutralHadronIso04->at(iel));
    
    m_logger << DEBUG << "Filling electron charge variables " << LQLogger::endmsg;

    /// set Charge variables
    el.SetCharge(ElectronLooseCharge->at(iel));
    el.SetGsfCtfScPixCharge(ElectronLooseGsfCtfScPixCharge->at(iel));
    el.SetGsfScPixCharge(ElectronLooseGsfScPixCharge->at(iel));
    el.SetGsfCtfCharge(ElectronLooseGsfCtfCharge->at(iel));
    
    m_logger << DEBUG << "Filling electron conversion variables " << LQLogger::endmsg;

    /// set conversion variables
    el.SetMissingHits(ElectronLooseMissingHitsEG->at(iel));
    el.SetMissingLostHits(ElectronLooseMissingHits->at(iel));
    el.SetHasMatchedConvPhot(ElectronLooseHasMatchedConvPhot->at(iel));

    el.SetConvFitProb(ElectronLooseConvFitProb->at(iel));
    el.SetNBrems(ElectronLooseNumberOfBrems->at(iel));
    el.SetFBrem(ElectronLooseFbrem->at(iel));

    if(ElectronLooseshiftedEup){
      if(ElectronLooseshiftedEup->size() > 0) {
	if(ElectronLooseshiftedEup->size() == ElectronLooseHasMatchedConvPhot->size() ){
	  el.SetShiftedEUp(ElectronLooseshiftedEup->at(iel));
	  el.SetShiftedEDown(ElectronLooseshiftedEdown->at(iel));
          el.SetShiftedExUp(ElectronLooseshiftedExup->at(iel));
          el.SetShiftedExDown(ElectronLooseshiftedExdown->at(iel));
          el.SetShiftedEyUp(ElectronLooseshiftedEyup->at(iel));
          el.SetShiftedEyDown(ElectronLooseshiftedEydown->at(iel));
	}
      }
      else{
	el.SetShiftedEUp(0);
	el.SetShiftedEDown(0.);
      }
    }
    m_logger << DEBUG << "Filling electronElectronLooseDCotTheta  " << LQLogger::endmsg;

    if(ElectronLooseDCotTheta){
      el.SetCotTheta(ElectronLooseDCotTheta->at(iel));
      el.SetElDist(ElectronLooseDist->at(iel));
    }
    
    
    m_logger << DEBUG << "Filling trigmatch variable" << LQLogger::endmsg;

    el.SetHLTDoubleElMatched(ElectronLooseHLTDoubleEleMatched->at(iel));
    if(ElectronLooseHLTSingleEleMatched17)el.SetHLTSingleElMatched17(ElectronLooseHLTSingleEleMatched17->at(iel));
    if(ElectronLooseHLTSingleEleMatched8)el.SetHLTSingleElMatched8(ElectronLooseHLTSingleEleMatched8->at(iel));
    if(ElectronLooseHLTSingleEleMatched)el.SetHLTSingleElMatched8(ElectronLooseHLTSingleEleMatched->at(iel));
    el.SetHLTSingleElWP80Matched(ElectronLooseHLTSingleEleWP80Matched->at(iel));


    if(ElectronLooseHLTEMuMatched8)el.SetHLTEMuMatched8(ElectronLooseHLTEMuMatched8->at(iel));
    if(ElectronLooseHLTEMuMatched17)el.SetHLTEMuMatched17(ElectronLooseHLTEMuMatched17->at(iel));

    m_logger << DEBUG << "Filling El Truth variables " << LQLogger::endmsg;
    
    /*vector<int> numbers;
      
    numbers.push_back(99462);
    numbers.push_back(99616);
    numbers.push_back(99616);
    

    bool check_event=false;
    
    for(int i=0; i<numbers.size(); i++){
      
      if(numbers.at(i) == event) check_event=true;
    }
    if(!check_event) return electrons;
    
    cout << "Event = " << event << endl;
    */
    /// truth info
    if(!isData){
      el.SetElectronMatchedGenPt(ElectronLooseMatchedGenParticlePt->at(iel));
      el.SetElectronMatchedGenEta(ElectronLooseMatchedGenParticleEta->at(iel));
      el.SetElectronMatchedGenPhi(ElectronLooseMatchedGenParticlePhi->at(iel));
      
      
      bool matched_electron(false);
      int iMother(-999),nDaughter(-999), ipdgid(-999), trueel_index(-999);
      ///// ADD prompt definition for MC
      double truth_reco_dr(1000000.);
      
      double match_pt =0.;
      double match_eta =0.;
      double match_phi =0.;
      if(fabs(ElectronLooseMatchedGenParticlePt->at(iel)) != 999){
	match_pt = ElectronLooseMatchedGenParticlePt->at(iel);
	match_eta = ElectronLooseMatchedGenParticleEta->at(iel);
	match_phi = ElectronLooseMatchedGenParticlePhi->at(iel);
      }
      else{
	match_pt = ElectronLoosePt->at(iel);
	match_eta = ElectronLooseEta->at(iel);
	match_phi = ElectronLoosePhi->at(iel);
      }
      
      m_logger << DEBUG <<  "ElectronLoose Charge  = " << ElectronLooseCharge->at(iel) << LQLogger::endmsg;
      m_logger << DEBUG <<  "ElectronLoose Eta  = " << match_eta << LQLogger::endmsg;
      m_logger << DEBUG <<  "ElectronLoose Phi  = " << match_phi << LQLogger::endmsg;
      m_logger << DEBUG <<  "ElectronLoose Pt  = " <<  match_pt << LQLogger::endmsg;
      
      
      if(ElectronLoosePt->at(iel) > 10.) {
	int MotherPdgId(-999);
	int eltruth_index=0;
	bool photon_conv(false);
	//// Loop over main truth collection to search for matced truth particle
	for(unsigned int g =0; g < 25 ; g++, eltruth_index++){
	  /// If already matched no need to continue
	  if(matched_electron) continue;
	  float status_3_dr= 10000.;
	  // Check the truth particle is close in Eta-phi space
	  double dr = sqrt( pow(fabs( match_eta - GenParticleEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi -GenParticlePhi->at(g))),2.0));
	  
	  if(dr < 0.4){
	    m_logger << DEBUG << "Truth Matched to electron[GenParticle]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenParticlePt->at(g) << "/" << GenParticleEta->at(g) << "/" << GenParticlePhi->at(g) << "/" <<  GenParticleStatus->at(g) << "/" << GenParticlePdgId->at(g) << "/" << GenParticleMotherIndex->at(g) << LQLogger::endmsg; 

	    if(GenParticleMotherIndex->at(g) < 25) {
	      if(GenParticleMotherIndex->at(g) != -1)   m_logger << DEBUG << "Mother PDGID = " << GenParticlePdgId->at(GenParticleMotherIndex->at(g)) << " " << GenParticleStatus->at(GenParticleMotherIndex->at(g)) << LQLogger::endmsg;
	    }else iMother = 4;
	    /// First check status 3 particles (this is just a check and if status 1 particle is matched it will overright it)
	    if(GenParticleStatus->at(g) == 3 ){
	      /// MATCH STABLE STATUS 3 EL to RECO EL
              if(dr < status_3_dr){
		status_3_dr = dr;
		if(fabs(GenParticlePdgId->at(g)) != 11 ){
		  if(fabs(GenParticlePdgId->at(g)) != 23){
		    if(fabs(GenParticlePdgId->at(g)) != 24){
		      iMother = g;
		      nDaughter = 1;
		      ipdgid =  11;
		      trueel_index = g;
		      MotherPdgId = GenParticlePdgId->at(iMother);
		    }
		  }
		}
		else{
		  if(GenParticleMotherIndex->at(g) < 25) iMother = GenParticleMotherIndex->at(g);
                  nDaughter = GenParticleNumDaught->at(g);
                  ipdgid =  GenParticlePdgId->at(g);
                  trueel_index = g;
                  MotherPdgId = GenParticlePdgId->at(iMother);
		  
		}
	      }
	    }// stable electron
	      
	    /// Now check if status 1 electron is matched  
	    if(GenParticleStatus->at(g) == 1){
	      if(fabs(GenParticlePdgId->at(g)) == 11){
		bool close_to_tau=false;
		/// check if status 1 electron is matched to tau (as this could be from a tau decay)
		for(unsigned int g2 =0; g2 < 25; g2++){
		  if(GenParticlePdgId->at(g2) == 2212) continue;
		  if(GenParticleStatus->at(g2) == 3){
		    
		    if( sqrt( pow(fabs( GenParticleEta->at(g)  - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( GenParticlePhi->at(g)  -GenParticlePhi->at(g2))),2.0)) < 0.1){
		      if(fabs(GenParticlePdgId->at(g2)) == 15){
			close_to_tau=true;
			if(g2 < 25) iMother = g2;
			nDaughter = GenParticleNumDaught->at(g);
			ipdgid =  GenParticlePdgId->at(g);
			trueel_index = g;
			MotherPdgId = GenParticlePdgId->at(iMother);
			matched_electron=true;
		      }//closest truth match
		    }
		  }
		}
		if(!close_to_tau) {
		  
		  /// Check there is no "CLOSER" status 1 electron 
		  for(unsigned int g2 =g+1; g2 < 25; g2++){
		    if(GenParticleStatus->at(g2) == 1){
		      if(fabs(GenParticlePdgId->at(g2)) == 11){
			double dr_el2 = sqrt( pow(fabs( match_eta - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi -GenParticlePhi->at(g2))),2.0));
			
			if(dr_el2 < dr) {
			  g = g2;
			  break;
			}
		      }
		    }
		  }
		  /// This is a match for status 1 electron and reco electron
		  int mu_index = GenParticleMotherIndex->at(g);
		  bool matched_el=false;
		  while(!matched_el){
		    if(fabs(GenParticlePdgId->at(mu_index)) != 11) {
		      matched_el=true;
		      iMother= mu_index;
		    }
		    else  mu_index = GenParticleMotherIndex->at(mu_index);
		  }
		  
		  //// check there is no status 1 photon close by
		  
		  for(unsigned int g2 =0; g2 < 25; g2++){
		    if(GenParticlePdgId->at(g2) == 22){
		      if(GenParticleStatus->at(g) == 1){
			double dr_elph = sqrt( pow(fabs( GenParticleEta->at(g) - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( GenParticlePhi->at(g)   -GenParticlePhi->at(g2))),2.0));
			if(dr_elph < 0.1)  photon_conv = true;
		      }
		    }
		  }
		  
		  nDaughter = GenParticleNumDaught->at(g);
		  ipdgid =  GenParticlePdgId->at(g);
		  trueel_index = g;
		  MotherPdgId = GenParticlePdgId->at(iMother);
		  matched_electron=true;
		}
	      }
	    }
	    
	    if(fabs(GenParticlePdgId->at(g)) == 22){
	      //// if only match is to status 1 photon then assign photon as fake
	      nDaughter = GenParticleNumDaught->at(g);
	      ipdgid =  GenParticlePdgId->at(g);
	      trueel_index = g;
	      iMother=GenParticleMotherIndex->at(g);;
	      MotherPdgId = GenParticlePdgId->at(iMother);
	      
	    }
	  }
	}
	
	//// If only matched (status 1) gen particle to electron is photon we need to check the origin of this photon: Photons from an electron could be conversion photon-> chargeflip bkg
      
	if(ipdgid == 22){
	  
	  /*
	    bool not_phmatched=false;
	    
	    while(!not_phmatched){
	    /// Is mother an electron?
	    if(fabs(GenParticlePdgId->at(GenParticleMotherIndex->at(trueel_index))) == 11){
	    // Is electron mother a Z?
	    if(fabs(GenParticlePdgId->at(GenParticleMotherIndex->at(GenParticleMotherIndex->at(trueel_index)))) == 23){
	    not_phmatched=true;
	    nDaughter = GenParticleNumDaught->at(GenParticleMotherIndex->at(trueel_index));
	    ipdgid =  GenParticlePdgId->at(GenParticleMotherIndex->at(trueel_index));
	    trueel_index = GenParticleMotherIndex->at(trueel_index);
	    iMother=GenParticleMotherIndex->at(GenParticleMotherIndex->at(trueel_index));
	    MotherPdgId = GenParticlePdgId->at(iMother);
	    }
	    else trueel_index = GenParticleMotherIndex->at(trueel_index);
	    }
	    else not_phmatched=true;
	    }
	    
	    
	    
	    /// If photon is not from an electron then it is assigned as a fake (in less it matches to a status 3 electron ) 
	    if(ipdgid == 22){
	    for(unsigned int g =0; g < 25; g++){
	    if(GenParticleStatus->at(g) == 3){
	    if(fabs(GenParticlePdgId->at(g)) ==11){
	    
	    double dr = sqrt( pow(fabs( GenParticleEta->at(trueel_index) - GenParticleEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( GenParticlePhi->at(trueel_index) -GenParticlePhi->at(g))),2.0));
	    
	    if(dr < 0.1){
	    nDaughter = GenParticleNumDaught->at(g);
	    ipdgid =  GenParticlePdgId->at(g);
	    trueel_index = g;
	    iMother=g;
	    MotherPdgId = GenParticlePdgId->at(iMother);
	    }
	    }
	    }
	    }
	    }
	  */
	}
	
	if(ipdgid != -999) matched_electron=true;
	
	for(unsigned int g =0; g < GenZMuPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  
	  if((fabs(GenZMuPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenZMuEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenZMuPhi->at(g))),2.0) );
	    m_logger << DEBUG << "Truth Matched to electron[GenZMu]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZMuPt->at(g) << "/" << GenZMuEta->at(g) << "/" << GenZMuPhi->at(g) << "/" <<  GenZMuStatus->at(g) << "/" << GenZMuPdgId->at(g) << "/" << GenZMuMotherIndex->at(g) << LQLogger::endmsg;
	    if(dr < 0.2){
	      ipdgid =  GenZMuPdgId->at(g);
	      trueel_index = eltruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId = 23;
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenZTauPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  if((fabs(GenZTauPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenZTauEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenZTauPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenZTau]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZTauPt->at(g) << "/" << GenZTauEta->at(g) << "/" << GenZTauPhi->at(g) <<  "/" << GenZTauPhi->at(g) << "/" <<  GenZTauStatus->at(g) << "/" << GenZTauPdgId->at(g) << "/" << GenZTauMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenZTauPdgId->at(g);
	      trueel_index = eltruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId= 23;
	      for(unsigned int g2 =0; g2 < GenParticleP->size(); g2++){
		if(fabs(GenParticlePdgId->at(g2) == 15)) {
		  MotherPdgId= GenParticlePdgId->at(g2);
		  iMother = g2;
		}	   
	      }
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenZElectronPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  if((fabs(GenZElectronPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenZElectronEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenZElectronPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenZElectron]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZElectronPt->at(g) << "/" << GenZElectronEta->at(g) << "/" << GenZElectronPhi->at(g) << "/" <<  GenZElectronStatus->at(g) << "/" << GenZElectronPdgId->at(g) << "/" << GenZElectronMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenZElectronPdgId->at(g);
	      trueel_index = eltruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId= 23;
	    }
	  }
	} 
	
	for(unsigned int g =0; g < GenWMuPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  
	  if((fabs(GenWMuPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenWMuEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenWMuPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenWMu]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWMuPt->at(g) << "/" << GenWMuEta->at(g) << "/" << GenWMuPhi->at(g) <<  "/" <<  GenWMuStatus->at(g) << "/" << GenWMuPdgId->at(g) << "/" << GenWMuMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenWMuPdgId->at(g);
	      trueel_index = eltruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId = 24;
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenWTauPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  if((fabs(GenWTauPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenWTauEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenWTauPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenWTau]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWTauPt->at(g) << "/" << GenWTauEta->at(g) << "/" << GenWTauPhi->at(g) <<  "/" << GenWTauPhi->at(g) << "/" <<  GenWTauStatus->at(g) << "/" << GenWTauPdgId->at(g) << "/" << GenWTauMotherIndex->at(g) << LQLogger::endmsg;            
	      ipdgid =  GenWTauPdgId->at(g);
	      trueel_index = eltruth_index;
	      for(unsigned int g2 =0; g2 < GenParticleP->size(); g2++){
		if(fabs(GenParticlePdgId->at(g2) == 15)) {
		  MotherPdgId= GenParticlePdgId->at(g2);
		  iMother = g2;
		}
	      }   
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenWElectronPdgId->size(); g++){
	  if(matched_electron) continue;
	  eltruth_index++;
	  if((fabs(GenWElectronPdgId->at(g))==11)){
	    double dr = sqrt( pow(fabs(ElectronLooseEta->at(iel) - GenWElectronEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(ElectronLoosePhi ->at(iel) -GenWElectronPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenWElectron]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWElectronPt->at(g) << "/" << GenWElectronEta->at(g) << "/" << GenWElectronPhi->at(g) << "/" <<  GenWElectronStatus->at(g) << "/" << GenWElectronPdgId->at(g) << "/" << GenWElectronMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenWElectronPdgId->at(g);
	      trueel_index = eltruth_index;
	      MotherPdgId= 24;
	    }
	  }
	}
	
	
	if (isPrompt( MotherPdgId)){
	  //cout << "Is prompt (MotherPdgId = "  << MotherPdgId << ") "<< endl;
	  //if ( ElectronCharge->at(iel)* ipdgid  > 0) cout << "Is chargeflip" << endl; 
	  
	  if ( ElectronLooseCharge->at(iel)* ipdgid  > 0)   partType = KParticle::chargemisid;
	  else partType = KParticle::notfake;

	  if(fabs(MotherPdgId) ==15){
            partType = KParticle::fromtau;
          }
	  if(fabs(MotherPdgId) ==13){
            partType = KParticle::misidmuon;
          }

	}
	else {
	  //cout << "Not prompt (MotherPdgId = "  << MotherPdgId << ") "<< endl;
	  if ( nthdigit( abs(MotherPdgId ),0 ) == 5 || nthdigit( abs(MotherPdgId ),1 ) == 5 || nthdigit( abs(MotherPdgId     ),2 ) == 5) partType = KParticle::bjet;
	  else if ( nthdigit( abs(MotherPdgId ),0 ) == 4 || nthdigit( abs(MotherPdgId ),1 ) == 4 || nthdigit( abs(MotherPdgId ),2 ) == 4) partType = KParticle::cjet;
	  else if
	    (nthdigit( abs(MotherPdgId ),0 ) == 1 || nthdigit( abs(MotherPdgId ),1 ) == 1 || nthdigit( abs(MotherPdgId ), 2 ) == 1  || nthdigit( abs(MotherPdgId ),0 ) == 2 || nthdigit( abs(MotherPdgId ),1 ) == 2 || nthdigit( abs(MotherPdgId),2 ) == 2   || nthdigit( abs(MotherPdgId ),0 ) == 3 || nthdigit( abs(MotherPdgId ),1 ) == 3 || nthdigit( abs(MotherPdgId),2 ) == 3 )	    partType = KParticle::jet;
	  else if  ( nthdigit( abs(MotherPdgId ),0 ) == 6 || nthdigit( abs(MotherPdgId ),1 ) == 6 || nthdigit( abs(MotherPdgId ),2 ) == 6){
	    if(abs(ipdgid) ==  5)  partType = KParticle::bjet;
	    if(abs(ipdgid) ==  4)  partType = KParticle::cjet;
	    if(abs(ipdgid) == 24)  partType = KParticle::notfake;
	  }
	  
	  else {
	    partType = KParticle::unknown;
	  }
	}
	if(ipdgid == 22) partType = KParticle::photonfake;
	if(photon_conv){
	  if(partType== KParticle::chargemisid)  partType = KParticle::chargemisid_photonconv;
	  else partType = KParticle::nonfake_photonconv;
	}
	
	if(partType == KParticle::NOPARTICLE) cout << "Type = NOPARTICLE" << endl;
	if(iMother == 0 ) cout << "Mother has index == 0 " << endl;

	//cout << "partType = " << partType << endl;
	el.SetType(partType);
	el.SetTruthParticleIndex(trueel_index);
	el.SetMotherIndex(iMother);
	el.SetMotherPdgId(MotherPdgId);
	
      }// 10 GeV reco llop
    }/// MC loop
       
    
    /// Need to add filling code
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

  if(isData) return genjets;
  for (UInt_t ijet=0; ijet< GenJetEnergy->size(); ijet++) {
    KGenJet jet;
    jet.SetPtEtaPhiE(GenJetPt->at(ijet), GenJetEta->at(ijet), GenJetPhi->at(ijet), GenJetEnergy->at(ijet));
    jet.SetGenJetP(GenJetP->at(ijet));
    jet.SetGenJetEMF(GenJetEMF->at(ijet));
    jet.SetGenJetHADF(GenJetHADF->at(ijet));
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

  m_logger << DEBUG << "Filling PFJets" << LQLogger::endmsg;
 
  for (UInt_t ijet=0; ijet< PFJetEta->size(); ijet++) {
    KJet jet;
    m_logger << DEBUG << "PFJeta = " << PFJetEta->at(ijet) << LQLogger::endmsg;
    jet.SetPx(PFJetPx->at(ijet));
    jet.SetPy(PFJetPy->at(ijet));
    if(!(PFJetPt && PFJetEta && PFJetPhi && PFJetEnergy )) ERRORMessage("PFJetPtEtaPhi");
    else jet.SetPtEtaPhiE(PFJetPt->at(ijet), PFJetEta->at(ijet), PFJetPhi->at(ijet), PFJetEnergy->at(ijet));
    if(!PFJetEnergyRaw)ERRORMessage("PFJetEnergyRaw");
    else jet.SetJetRawEnergy(PFJetEnergyRaw->at(ijet));
    if(!PFJetEnergyRaw)ERRORMessage("PFJetEnergyRaw");
    else jet.SetJetRawPt(PFJetEnergyRaw->at(ijet));
    
    m_logger << DEBUG << "Filling JetID " << LQLogger::endmsg; 
    // ID cuts
    if(!(PFJetPassLooseID && PFJetPassTightID)) ERRORMessage("JetID");
    else{
      jet.SetJetPassLooseID(PFJetPassLooseID->at(ijet));    
      jet.SetJetPassTightID(PFJetPassTightID->at(ijet));    
    }

    m_logger << DEBUG << "Filling JetID WP " << LQLogger::endmsg; 

    if(PFJetPileupjetIDpassLooseWP){
      if(PFJetPileupjetIDpassLooseWP->size() > 0){
	jet.SetJetPileupIDLooseWP(PFJetPileupjetIDpassLooseWP->at(ijet));
	jet.SetJetPileupIDMediumWP(PFJetPileupjetIDpassMediumWP->at(ijet));
	jet.SetJetPileupIDTightWP(PFJetPileupjetIDpassTightWP->at(ijet));
	jet.SetJetPileupIDFlag(PFJetJetPileupIdflag->at(ijet));
	jet.SetJetPileupIDMVA(PFJetJetPileupMVA->at(ijet));
      }
    }
        
    m_logger << DEBUG << "Filling Jet Energy Fraction " << LQLogger::endmsg; 
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

    m_logger << DEBUG << "Filling Jet btag info " << LQLogger::endmsg; 
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

    m_logger << DEBUG << "Filling Jet multiplicities " << LQLogger::endmsg; 
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
    m_logger << DEBUG << "Filling Jet track info " << LQLogger::endmsg; 
    /// Tracking
    if(!(PFJetNConstituents&&PFJetBestVertexTrackAssociationIndex&&PFJetBestVertexTrackAssociationFactor))ERRORMessage("JetTrack");
    else{
      jet.SetJetNConstituents(PFJetNConstituents->at(ijet));
      jet.SetJetBestVertexTrackAssociationIndex(PFJetBestVertexTrackAssociationIndex->at(ijet));
      jet.SetJetBestVertexTrackAssociationFactor(PFJetBestVertexTrackAssociationFactor->at(ijet));
    }
    
    // flavour
    jet.SetJetPartonFlavour(PFJetPartonFlavour->at(ijet));

    m_logger << DEBUG << "Fill SKTree jetuncertainty" << LQLogger::endmsg;

    /// JEC and uncertainties
    jet.SetJetJECUnc(PFJetJECUnc->at(ijet));
    jet.SetJetL1FastJetJEC(PFJetL1FastJetJEC->at(ijet));
    jet.SetJetL2L3ResJEC(PFJetL2L3ResJEC->at(ijet));
    jet.SetJetL2RelJEC(PFJetL2RelJEC->at(ijet));
    jet.SetJetL3AbsJEC(PFJetL3AbsJEC->at(ijet));
    m_logger << DEBUG << "Fill SKTree2 jetuncertainty" << LQLogger::endmsg;

    if(PFJetL5BottomJEC){
      //jet.SetJetL5BottomJEC(PFJetL5BottomJEC->at(ijet));
      //jet.SetJetL5CharmJEC(PFJetL5CharmJEC->at(ijet));
      //jet.SetJetL5UDSJEC(PFJetL5UDSJEC->at(ijet));
      //jet.SetJetL5GluonJEC(PFJetL5GluonJEC->at(ijet));
    }
    m_logger << DEBUG << "Fill SKTree3 jetuncertainty" << LQLogger::endmsg;
    
    if(!isData){
      if(PFJetScaledDownEnergy&&PFJetScaledUpEnergy&&PFJetScaledDownPt&&PFJetScaledUpPt&&PFJetSmearedDownEnergy&&PFJetSmearedUpEnergy&&PFJetSmearedDownPt&&PFJetSmearedUpPt){
	if(PFJetScaledDownEnergy->size() > 0){
	  m_logger << DEBUG << "Fill SKTree4 jetuncertainty" << LQLogger::endmsg;
	  
	  jet.SetJetScaledDownEnergy(PFJetScaledDownEnergy->at(ijet));
	  m_logger << DEBUG << "Fill SKTree4 jetuncertainty" << LQLogger::endmsg;
	  
	  
	  jet.SetJetScaledDownPt(PFJetScaledDownPt->at(ijet));
	  jet.SetJetScaledDownPx(PFJetScaledDownPx->at(ijet));
	  jet.SetJetScaledDownPy(PFJetScaledDownPy->at(ijet));

	  jet.SetJetScaledUpEnergy(PFJetScaledUpEnergy->at(ijet));
	  m_logger << DEBUG << "Fill SKTree4 jetuncertainty" << LQLogger::endmsg;
	  
	  jet.SetJetScaledUpPt(PFJetScaledUpPt->at(ijet));
	  jet.SetJetScaledUpPx(PFJetScaledUpPx->at(ijet));
	  jet.SetJetScaledUpPy(PFJetScaledUpPy->at(ijet));
	  jet.SetJetSmearedDownEnergy(PFJetSmearedDownEnergy->at(ijet));
	  jet.SetJetSmearedUpEnergy(PFJetSmearedUpEnergy->at(ijet));
	  jet.SetJetSmearedDownPt(PFJetSmearedDownPt->at(ijet));
	  jet.SetJetSmearedDownPx(PFJetSmearedDownPx->at(ijet));
	  jet.SetJetSmearedDownPy(PFJetSmearedDownPy->at(ijet));
	  jet.SetJetSmearedUpPt(PFJetSmearedUpPt->at(ijet));
	  jet.SetJetSmearedUpPx(PFJetSmearedUpPx->at(ijet));
	  jet.SetJetSmearedUpPy(PFJetSmearedUpPy->at(ijet));
	}
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
    m_logger << DEBUG << "Fill PFJet vector for SKJet" << LQLogger::endmsg;
    jets.push_back(jet);
  }// end of jet 
  
  
  std::sort( jets.begin(), jets.end(), isHigherPt );
  
  m_logger << DEBUG << "PFJet size = " << jets.size() << LQLogger::endmsg;
  return jets;
}

std::vector<KJet> SKTreeFiller::GetAllCaloJets(){

  m_logger << DEBUG << "Filling Calo Jets" << LQLogger::endmsg;
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

  int ims=0;
  for (UInt_t ilep=0; ilep< MuonLooseEta->size(); ilep++) {
    KMuon muon;
    m_logger << DEBUG << "Filling global pt/eta ... " << LQLogger::endmsg;
    
    m_logger << DEBUG << MuonLooseIsPF << " " << MuonLooseIsGlobal << " " << MuonLooseIsTracker << LQLogger::endmsg;

    /// GENERAL
    muon.SetISPF(MuonLooseIsPF->at(ilep));
    muon.SetIsGlobal(MuonLooseIsGlobal->at(ilep));
    muon.SetIsTracker(MuonLooseIsTracker->at(ilep));

    if(MuonLooseshiftedEup){
      if(MuonLooseshiftedEup->size() > 0){
	if(MuonLooseEta->size() == MuonLooseshiftedEup->size()){
	  muon.SetShiftedEUp(MuonLooseshiftedEup->at(ilep));
	  muon.SetShiftedEDown(MuonLooseshiftedEdown->at(ilep));
	  muon.SetShiftedExUp(MuonLooseshiftedExup->at(ilep));
          muon.SetShiftedExDown(MuonLooseshiftedExdown->at(ilep));
	  muon.SetShiftedEyUp(MuonLooseshiftedEyup->at(ilep));
          muon.SetShiftedEyDown(MuonLooseshiftedEydown->at(ilep));
	}
      }
      else{
	muon.SetShiftedEUp(0.);
	muon.SetShiftedEDown(0.);
      }
    }

    muon.SetPx(MuonLoosePx->at(ilep));
    muon.SetPy(MuonLoosePy->at(ilep));
    if(!MuonLooseGlobalEta){
      muon.SetPtEtaPhiE(MuonLoosePt->at(ilep),MuonLooseEta->at(ilep),MuonLoosePhi->at(ilep),MuonLooseEnergy->at(ilep));
      muon.SetCharge(MuonLooseCharge->at(ilep));
    }else{
      if(MuonLooseIsGlobal->at(ilep)){
	muon.SetPtEtaPhiM(MuonLooseGlobalPt->at(ilep), MuonLooseGlobalEta->at(ilep),MuonLooseGlobalPhi->at(ilep), 0.105658367);            
	muon.SetCharge(MuonLooseGlobalCharge->at(ilep));
      }
    }
     
    m_logger << DEBUG << "Filling ms pt/eta ... " << LQLogger::endmsg;
    if(MuonLooseMuonSpecPt){
      
      if(MuonLooseMuonSpecCharge->at(ilep) !=-999. && MuonLooseMuonSpecCharge->at(ilep) !=0){
	muon.SetMuonMSPt(MuonLooseMuonSpecPt->at(ims));
	muon.SetMuonMSEta(MuonLooseMuonSpecEta->at(ims));
	muon.SetMuonMSPhi(MuonLooseMuonSpecPhi->at(ims));
	muon.SetMuonMSCharge(MuonLooseMuonSpecCharge->at(ims));
	ims++;
      }
      else{
	muon.SetMuonMSPt(-999.);
	muon.SetMuonMSE(-999.);
	muon.SetMuonMSEta(-999.);
	muon.SetMuonMSPhi(-999.);
	muon.SetMuonMSCharge(-999);
      }
    }
    m_logger << DEBUG << "Filling tracker ... " << LQLogger::endmsg;
    if(MuonLooseTrackerCharge){
      muon.SetMuonIDPt(MuonLoosePt->at(ilep));
      muon.SetMuonIDEta(MuonLooseEta->at(ilep));
      muon.SetMuonIDPhi(MuonLoosePhi->at(ilep));
      muon.SetMuonIDCharge(MuonLooseTrackerCharge->at(ilep));  
    }
    muon.SetPtErr(MuonLoosePtError->at(ilep));
    muon.SetEtaErr(MuonLooseEtaError->at(ilep));
   
    muon.SetMuonVtxIndex(MuonLooseBestTrackVtxIndex->at(ilep));    
    
    m_logger << DEBUG << "Filling isolation ... " << LQLogger::endmsg;
    /// Isolation
    muon.SetISOR03ChargedHad(MuonLoosePFIsoR03ChargedHadron->at(ilep));
    muon.SetISOR03NeutralHad(MuonLoosePFIsoR03NeutralHadron->at(ilep));
    muon.SetISOR03Photon(MuonLoosePFIsoR03Photon->at(ilep));       
    muon.SetISOR04ChargedHad(MuonLoosePFIsoR04ChargedHadron->at(ilep));
    muon.SetISOR04NeutralHad(MuonLoosePFIsoR04NeutralHadron->at(ilep));
    muon.SetISOR04Photon(MuonLoosePFIsoR04Photon->at(ilep)); 
    muon.SetIsolationEcalVeto(MuonLooseEcalVetoIso->at(ilep));
    muon.SetIsolationHcalVeto(MuonLooseHcalVetoIso->at(ilep));


    /// PU correction
    muon.SetPileUp_R03(MuonLoosePFIsoR03PU->at(ilep));
    muon.SetPileUp_R04(MuonLoosePFIsoR04PU->at(ilep));
    
    ////////// TRACK
    /// Imapct parameter 
    
    muon.SetTrackVx(MuonLooseTrkVx->at(ilep));
    muon.SetTrackVy(MuonLooseTrkVy->at(ilep));
    muon.SetTrackVz(MuonLooseTrkVz->at(ilep));
    muon.SetVertexDistXY(MuonLooseVtxDistXY->at(ilep));

    m_logger << DEBUG << "Filling IP  ... " << LQLogger::endmsg;

    muon.Setdz(MuonLooseBestTrackVtxDistZ->at(ilep)); 
    muon.Setdxy(MuonLooseBestTrackVtxDistXY->at(ilep));
    muon.Setdxy_pat(MuonLoosePrimaryVertexDXY->at(ilep));
    muon.Setdxyerr_pat(MuonLoosePrimaryVertexDXYError->at(ilep));
    muon.SetD0( MuonLooseTrkD0->at(ilep));
    muon.SetD0Error (MuonLooseTrkD0Error->at(ilep));
    //// chi2
    muon.SetGlobalchi2( MuonLooseGlobalChi2->at(ilep));
        
    /// hits
    muon.SetValidHits( MuonLooseGlobalTrkValidHits->at(ilep));
    muon.SetPixelValidHits(  MuonLooseTrkPixelHits->at(ilep));
    muon.SetValidStations( MuonLooseStationMatches->at(ilep));
    muon.SetLayersWithMeasurement ( MuonLooseTrackLayersWithMeasurement->at(ilep));

    /// TrigMatching
    if(MuonLooseHLTDoubleMuonMatched){
      muon.SetHLTDoubleMuMatched(MuonLooseHLTDoubleMuonMatched->at(ilep));
      
    }
    if(MuonLooseHLTSingleMuonMatched)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched->at(ilep));
    if(MuonLooseHLTSingleMuonMatched5)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched5->at(ilep));
    if(MuonLooseHLTSingleMuonMatched8)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched8->at(ilep));
    if(MuonLooseHLTSingleMuonMatched12)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched12->at(ilep));
    if(MuonLooseHLTSingleMuonMatched17)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched17->at(ilep));
    if(MuonLooseHLTSingleMuonMatched24)muon.SetHLTSingleMuMatched(MuonLooseHLTSingleMuonMatched24->at(ilep));

    if(MuonLooseHLTEMuMatched8)muon.SetHLTEMuMatched8(MuonLooseHLTEMuMatched8->at(ilep));
    if(MuonLooseHLTEMuMatched17)muon.SetHLTEMuMatched17(MuonLooseHLTEMuMatched17->at(ilep));
    
    
    if(MuonLooseHLTSingleIsoMuonMatched)muon.SetHLTSingleMuIsoMatched(MuonLooseHLTSingleIsoMuonMatched->at(ilep));
    
    muon.SetMuonCocktailPt(MuonLooseCocktailPt->at(ilep));
    muon.SetMuonCocktailEta(MuonLooseCocktailEta->at(ilep));
    muon.SetMuonCocktailPhi(MuonLooseCocktailPhi->at(ilep));
    muon.SetMuonCocktailGlobalChi2(MuonLooseCocktailGlobalChi2->at(ilep));
    muon.SetMuonCocktailTrkD0(MuonLooseCocktailTrkVtxDXY->at(ilep));
    muon.SetMuonCocktailTrkDz(MuonLooseCocktailTrkVtxDZ->at(ilep));
    muon.SetMuonCocktailCharge(MuonLooseCocktailCharge->at(ilep));


        
    m_logger << DEBUG << "Muon Truth " << LQLogger::endmsg;

    /// truth info
    if(!isData){
      muon.SetMuonMatchedGenParticleEta(MuonLooseMatchedGenParticleEta->at(ilep));
      muon.SetMuonMatchedGenParticlePhi(MuonLooseMatchedGenParticlePhi->at(ilep));
      muon.SetMuonMatchedGenParticlePt(MuonLooseMatchedGenParticlePt->at(ilep));
      
      bool matched_muon(false);
      int iMother(-999),nDaughter(-999), ipdgid(-999), truemu_index(-999);
      ///// ADD prompt definition for MC
      double truth_reco_dr(1000000.);
      
      double match_pt =0.;
      double match_eta =0.;
      double match_phi =0.;
      if(fabs(MuonLooseMatchedGenParticlePt->at(ilep)) != 999){
        match_pt = MuonLooseMatchedGenParticlePt->at(ilep);
        match_eta = MuonLooseMatchedGenParticleEta->at(ilep);
        match_phi = MuonLooseMatchedGenParticlePhi->at(ilep);
      }
      else{
        match_pt = MuonLoosePt->at(ilep);
        match_eta = MuonLooseEta->at(ilep);
        match_phi = MuonLoosePhi->at(ilep);
      }

      m_logger << DEBUG <<  "MuonLoose Charge  = " << MuonLooseCharge->at(ilep) << LQLogger::endmsg;
      m_logger << DEBUG <<  "MuonLoose Eta  = " << match_eta << LQLogger::endmsg;
      m_logger << DEBUG <<  "MuonLoose Phi  = " << match_phi << LQLogger::endmsg;
      m_logger << DEBUG <<  "MuonLoose Pt  = " <<  match_pt << LQLogger::endmsg;

      if(MuonLoosePt->at(ilep) > 10.) {
	int MotherPdgId(-999);
	int mutruth_index=0;
	bool photon_conv(false);
	for(unsigned int g =0; g < 25 ; g++, mutruth_index++){
	  if(matched_muon) continue;
	  
	  double dr = sqrt(pow(fabs( match_eta - GenParticleEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi -GenParticlePhi->at(g))),2.0));
	  
	  if(dr < 0.4){
	    
	    m_logger << DEBUG << "Truth Matched to muon[GenParticle]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenParticlePt->at(g) << "/" << GenParticleEta->at(g) << "/" << GenParticlePhi->at(g) << "/" <<  GenParticleStatus->at(g) << "/" << GenParticlePdgId->at(g) << "/" << GenParticleMotherIndex->at(g) << LQLogger::endmsg;
	    if(GenParticleMotherIndex->at(g) < 25){
	    
	    if(GenParticleMotherIndex->at(g) != -1)   m_logger << DEBUG << "Mother PDGID = " << GenParticlePdgId->at(GenParticleMotherIndex->at(g))  << LQLogger::endmsg;
	    } else iMother = 4;
	    if(GenParticleStatus->at(g) == 3 ){
	      
	      if(GenParticleMotherIndex->at(g) < 25) iMother = GenParticleMotherIndex->at(g);
	      nDaughter = GenParticleNumDaught->at(g);
	      ipdgid =  GenParticlePdgId->at(g);
	      mutruth_index = g;
	      MotherPdgId = GenParticlePdgId->at(iMother);
	    }
	    /// Now check if status 1 muon is matched
	    if(GenParticleStatus->at(g) == 1){
	      if(fabs(GenParticlePdgId->at(g)) == 13){
		bool close_to_tau=false;
		/// check if status 1 muon is matched to tau (as this could be from a tau decay)
		for(unsigned int g2 =0; g2 < 25; g2++){
		  if(GenParticlePdgId->at(g2) == 2212) continue;
		  if(GenParticleStatus->at(g2) == 3){
		    if( sqrt( pow(fabs( GenParticleEta->at(g)  - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( GenParticlePhi->at(g)  -GenParticlePhi->at(g2))),2.0)) < 0.1){
		      if(fabs(GenParticlePdgId->at(g2)) == 15){
			close_to_tau=true;
			if(g2 < 25) iMother = g2;
			nDaughter = GenParticleNumDaught->at(g);
			ipdgid =  GenParticlePdgId->at(g);
			mutruth_index = g;
			MotherPdgId = GenParticlePdgId->at(iMother);
			matched_muon=true;
		      }
		    }
		  }
		  if(!close_to_tau) {
		    /// Check there is no "CLOSER" status 1 muon
		    for(unsigned int g2 =g+1; g2 < 25; g2++){
		      if(GenParticleStatus->at(g2) == 1){
			if(fabs(GenParticlePdgId->at(g2)) == 13){
			  double dr_mu2 = sqrt( pow(fabs( match_eta - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi -GenParticlePhi->at(g2))),2.0));
			  if(dr_mu2 < dr) {
			    g = g2;
			    break;
			  }
			}
		      }
		    }
		    /// This is a match for status 1 muon and reco muon
		    int mu_index = GenParticleMotherIndex->at(g);
		    bool matched_mu=false;
		    while(!matched_mu){
		      if(fabs(GenParticlePdgId->at(mu_index)) != 13) {
			matched_mu=true;
			iMother= mu_index;
		      }
		      else  mu_index = GenParticleMotherIndex->at(mu_index);
		    }
		    
		    //// check there is no status 1 photon close by
		    
		    for(unsigned int g2 =0; g2 < 25; g2++){
		      if(GenParticlePdgId->at(g2) == 22){
			if(GenParticleStatus->at(g) == 1){
			  double dr_muph = sqrt( pow(fabs( GenParticleEta->at(g) - GenParticleEta->at(g2)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( GenParticlePhi->at(g)   -GenParticlePhi->at(g2))),2.0));
			  if(dr_muph < 0.1)  photon_conv = true;
			}
		      }
		    }
		    nDaughter = GenParticleNumDaught->at(g);
		    ipdgid =  GenParticlePdgId->at(g);
		    mutruth_index = g;
		    MotherPdgId = GenParticlePdgId->at(iMother);
		    matched_muon=true;
		  }
		}
	      }
	      if(fabs(GenParticlePdgId->at(g)) == 22){
		//// if only match is to status 1 photon then assign photon as fake
		nDaughter = GenParticleNumDaught->at(g);
		ipdgid =  GenParticlePdgId->at(g);
		mutruth_index = g;
		iMother=GenParticleMotherIndex->at(g);;
		MotherPdgId = GenParticlePdgId->at(iMother);
		
	      }
	    }
	  }
	}
	if(ipdgid!=-999) matched_muon= true;
	for(unsigned int g =0; g <GenZMuPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenZMuPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenZMuEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep) -GenZMuPhi->at(g))),2.0) );
	    m_logger << DEBUG << "Truth Matched to muon[GenZMu]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZMuPt->at(g) << "/" << GenZMuEta->at(g) << "/" << GenZMuPhi->at(g) << "/" <<  GenZMuStatus->at(g) << "/" << GenZMuPdgId->at(g) << "/" << GenZMuMotherIndex->at(g) << LQLogger::endmsg;
	    if(dr < 0.2){
	      ipdgid =  GenZMuPdgId->at(g);
	      truemu_index = mutruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId = 23;
	    }
	  }
	}
	for(unsigned int g =0; g < GenZTauPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenZTauPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenZTauEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep) -GenZTauPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to muon[GenZTau]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZTauPt->at(g) << "/" << GenZTauEta->at(g) << "/" << GenZTauPhi->at(g) <<  "/" << GenZTauPhi->at(g) << "/" <<  GenZTauStatus->at(g) << "/" << GenZTauPdgId->at(g) << "/"<< GenZTauMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenZTauPdgId->at(g);
	      truemu_index = mutruth_index;
	      truth_reco_dr = dr;
	      for(unsigned int g2 =0; g2 < GenParticleP->size(); g2++){
		if(fabs(GenParticlePdgId->at(g2) == 15)) {
		  MotherPdgId= GenParticlePdgId->at(g2);
		  iMother = g2;
		}
	      }
	    }
	  }
	}
	for(unsigned int g =0; g < GenZElectronPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenZElectronPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenZElectronEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep) -GenZElectronPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to muon[GenZElectron]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenZElectronPt->at(g) << "/" << GenZElectronEta->at(g) << "/" << GenZElectronPhi->at(g) << "/" <<  GenZElectronStatus->at(g) << "/" << GenZElectronPdgId->at(g) << "/" << GenZElectronMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenZElectronPdgId->at(g);
	      truemu_index = mutruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId= 23;
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenWMuPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenWMuPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenWMuEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep) -GenWMuPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to muon[GenWMu]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWMuPt->at(g) << "/" <<  GenWMuEta->at(g) << "/" << GenWMuPhi->at(g) <<  "/" <<  GenWMuStatus->at(g) << "/" << GenWMuPdgId->at(g) << "/" << GenWMuMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenWMuPdgId->at(g);
	      truemu_index = mutruth_index;
	      truth_reco_dr = dr;
	      MotherPdgId = 24;
	    }
	  }
	}
	
	for(unsigned int g =0; g < GenWTauPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenWTauPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenWTauEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep) -GenWTauPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to muon[GenWTau]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWTauPt->at(g) << "/" << GenWTauEta->at(g) << "/" << GenWTauPhi->at(g) <<  "/" << GenWTauPhi->at(g) << "/" <<  GenWTauStatus->at(g) << "/" << GenWTauPdgId->at(g) << "/" << GenWTauMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenWTauPdgId->at(g);
	      truemu_index = mutruth_index;
	      for(unsigned int g2 =0; g2 < GenParticleP->size(); g2++){
		if(fabs(GenParticlePdgId->at(g2) == 15)) {
		  MotherPdgId= GenParticlePdgId->at(g2);
		  iMother = g2;
		}
	      }
	    }
	  }
	}
	
	
	for(unsigned int g =0; g < GenWElectronPdgId->size(); g++){
	  if(matched_muon) continue;
	  mutruth_index++;
	  if((fabs(GenWElectronPdgId->at(g))==13)){
	    double dr = sqrt( pow(fabs(MuonLooseEta->at(ilep) - GenWElectronEta->at(g)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi(MuonLoosePhi ->at(ilep)-GenWElectronPhi->at(g))),2.0) );
	    if(dr < 0.2){
	      m_logger << DEBUG << "Truth Matched to electron[GenWElectron]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << GenWElectronPt->at(g) << "/" << GenWElectronEta->at(g) << "/" << GenWElectronPhi->at(g) << "/" <<  GenWElectronStatus->at(g) << "/" << GenWElectronPdgId->at(g) << "/" << GenWElectronMotherIndex->at(g) << LQLogger::endmsg;
	      ipdgid =  GenWElectronPdgId->at(g);
	      truemu_index = mutruth_index;
	      MotherPdgId= 24;
	    }
	  }
	}
	
	if (isPrompt( MotherPdgId)){
	  if ( MuonLooseCharge->at(ilep)* ipdgid  > 0)   partType = KParticle::chargemisid;
	  else partType = KParticle::notfake;
	}
	else {
	  if ( nthdigit( abs(MotherPdgId ),0 ) == 5 || nthdigit( abs(MotherPdgId ),1 ) == 5 || nthdigit( abs(MotherPdgId     ),2 ) == 5) partType  = KParticle::bjet;
	  else if ( nthdigit( abs(MotherPdgId ),0 ) == 4 || nthdigit( abs(MotherPdgId ),1 ) == 4 || nthdigit( abs(MotherPdgId ),2 ) == 4) partType = KParticle::cjet;
	  else if
	    (nthdigit( abs(MotherPdgId ),0 ) == 1 || nthdigit( abs(MotherPdgId ),1 ) == 1 || nthdigit( abs(MotherPdgId ), 2 ) == 1  || nthdigit( abs(MotherPdgId ),0 ) == 2 || nthdigit( abs(MotherPdgId ),1 ) == 2 || nthdigit( abs(MotherPdgId),2 ) == 2   || nthdigit( abs(MotherPdgId ),0 ) == 3 || nthdigit( abs(MotherPdgId ),1 ) == 3 || nthdigit( abs(MotherPdgId),2 ) == 3 )         partType = KParticle::jet;
	  
	  else if  ( nthdigit( abs(MotherPdgId ),0 ) == 6 || nthdigit( abs(MotherPdgId ),1 ) == 6 || nthdigit( abs(MotherPdgId ),2 ) == 6){
	    if(abs(ipdgid) ==  5)  partType = KParticle::bjet;
	    if(abs(ipdgid) ==  4)  partType = KParticle::cjet;
	    if(abs(ipdgid) == 24)  partType = KParticle::notfake;
	    if(abs(ipdgid) == 23)  partType = KParticle::notfake;
	  }
	  else partType = KParticle::unknown;
	}
	
	if(ipdgid == 22) partType = KParticle::photonfake;
	
	if(photon_conv){
	  if(partType== KParticle::chargemisid)  partType = KParticle::chargemisid_photonconv;
	  else partType = KParticle::nonfake_photonconv;
	}
	
	muon.SetType(partType);
	muon.SetTruthParticleIndex(truemu_index);
	muon.SetMotherIndex(iMother);
	muon.SetMotherPdgId(MotherPdgId);
	
      }/// 10 GeV reco cut
    }// MC loop
    
     
    m_logger << DEBUG << "Add muon to vector " << LQLogger::endmsg;
    /// Fill vector
    muons.push_back(muon);
  }
  
  std::sort( muons.begin(), muons.end(), isHigherPt );
  m_logger << DEBUG << "End of MuonLoose Filling" << LQLogger::endmsg;
  return muons;
  }

  

std::vector<snu::KTruth>   SKTreeFiller::GetTruthParticles(){
  
  m_logger << DEBUG << "Filling Truth" << LQLogger::endmsg;
  std::vector<snu::KTruth> vtruth;
  if(!LQinput){
    int itr(0);
    for(std::vector<KTruth>::iterator kit  = k_inputtruth->begin(); kit != k_inputtruth->end(); kit++, itr++){
      if(itr < 25.){
	vtruth.push_back(*kit);
      }
    }

    return vtruth;
  }
  
  if(isData) return vtruth;
  
  for (UInt_t it=0; it< GenParticlePt->size(); it++ ) {
    if(it > 24) continue;
    
    KTruth truthp;
    if(GenParticlePt->at(it)) truthp.SetPtEtaPhiE(GenParticlePt->at(it), GenParticleEta->at(it), GenParticlePhi->at(it), GenParticleEnergy->at(it));


    if(GenParticlePx->at(it)){
      
      truthp.SetParticlePx(GenParticlePx->at(it));
      truthp.SetParticlePy(GenParticlePy->at(it));

      truthp.SetParticlePz(GenParticlePz->at(it));
    }
    if(GenParticleVX){
      truthp.SetParticleVx(GenParticleVX->at(it));
      truthp.SetParticleVy(GenParticleVY->at(it));
      truthp.SetParticleVz(GenParticleVZ->at(it));
    }

    truthp.SetParticlePdgId(GenParticlePdgId->at(it));
    truthp.SetParticleStatus(GenParticleStatus->at(it));
   
    truthp.SetParticleNDaughter(GenParticleNumDaught->at(it));

    truthp.SetParticleIndexMother(GenParticleMotherIndex->at(it));
    truthp.SetTauDecayMode(GenParticleTauDecayMode->at(it));
    

    float charge_truth = -999.;
    if(fabs(GenParticlePdgId->at(it) )== 1 || fabs(GenParticlePdgId->at(it) )== 3 || fabs(GenParticlePdgId->at(it) )== 5) charge_truth = -1./3.;
    else if(fabs(GenParticlePdgId->at(it) )== 2 || fabs(GenParticlePdgId->at(it) )== 4 || fabs(GenParticlePdgId->at(it) )== 6) charge_truth = 2./3.;
    else if(fabs(GenParticlePdgId->at(it) )== 11 || fabs(GenParticlePdgId->at(it) )==13 || fabs(GenParticlePdgId->at(it) )==15) charge_truth = -1.;
    else if(fabs(GenParticlePdgId->at(it) )== 12 || fabs(GenParticlePdgId->at(it) )==14 || fabs(GenParticlePdgId->at(it) )==16) charge_truth = 0.;
    else if(fabs(GenParticlePdgId->at(it) )== 22 || fabs(GenParticlePdgId->at(it) )== 23) charge_truth = 0.;
    else if(fabs(GenParticlePdgId->at(it) )== 24) charge_truth =1.;
    else charge_truth = -999.;
    if(GenParticlePdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }/// end of filling loop

  m_logger << DEBUG << "Filling Truth  ZMu" << LQLogger::endmsg;

  for (UInt_t it=0; it< GenZMuEta->size(); it++) {
    
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZMuPt->at(it), GenZMuEta->at(it), GenZMuPhi->at(it), GenZMuEnergy->at(it));
    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenZMuPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }

    if (duplicate) continue;

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

    truthp.SetParticleNDaughter(GenZMuNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZMuMotherIndex->at(it));
    truthp.SetTauDecayMode(GenZMuTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenZMuPdgId->at(it)) == 1 || fabs(GenZMuPdgId->at(it)) == 3 || fabs(GenZMuPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenZMuPdgId->at(it)) == 2 || fabs(GenZMuPdgId->at(it)) == 4 || fabs(GenZMuPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenZMuPdgId->at(it)) == 11 || fabs(GenZMuPdgId->at(it)) ==13 || fabs(GenZMuPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenZMuPdgId->at(it)) == 12 || fabs(GenZMuPdgId->at(it)) ==14 || fabs(GenZMuPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenZMuPdgId->at(it)) == 22 || fabs(GenZMuPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenZMuPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;

    if(GenZMuPdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);    
  }
  
  m_logger << DEBUG << "Filling Truth ZTau" << LQLogger::endmsg;
  
  for (UInt_t it=0; it< GenZTauEta->size(); it++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZTauPt->at(it), GenZTauEta->at(it), GenZTauPhi->at(it), GenZTauEnergy->at(it));
    
    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenZTauPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }

    if (duplicate) continue;
    
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

    truthp.SetParticleNDaughter(GenZTauNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZTauMotherIndex->at(it));
    truthp.SetTauDecayMode(GenZTauTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenZTauPdgId->at(it)) == 1 || fabs(GenZTauPdgId->at(it)) == 3 || fabs(GenZTauPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenZTauPdgId->at(it)) == 2 || fabs(GenZTauPdgId->at(it)) == 4 || fabs(GenZTauPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenZTauPdgId->at(it)) == 11 || fabs(GenZTauPdgId->at(it)) ==13 || fabs(GenZTauPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenZTauPdgId->at(it)) == 12 || fabs(GenZTauPdgId->at(it)) ==14 || fabs(GenZTauPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenZTauPdgId->at(it)) == 22 || fabs(GenZTauPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenZTauPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;

    if(GenZTauPdgId->at(it) < 0) charge_truth *=-1.;

    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }
  

  m_logger << DEBUG << "Filling Truth ZElectron" << LQLogger::endmsg;

  for (UInt_t it=0; it< GenZElectronEta->size(); it++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenZElectronPt->at(it), GenZElectronEta->at(it), GenZElectronPhi->at(it), GenZElectronEnergy->at(it));
    
    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenZElectronPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }
    
    if (duplicate) continue;
    
    truthp.SetParticlePx(GenZElectronPx->at(it));
    truthp.SetParticlePy(GenZElectronPy->at(it));
    truthp.SetParticlePz(GenZElectronPz->at(it));
    if(GenZElectronVX){
      truthp.SetParticleVx(GenZElectronVX->at(it));
      truthp.SetParticleVy(GenZElectronVY->at(it));
      truthp.SetParticleVz(GenZElectronVZ->at(it));
    }
    truthp.SetParticlePdgId(GenZElectronPdgId->at(it));
    truthp.SetParticleStatus(GenZElectronStatus->at(it));
    
    truthp.SetParticleNDaughter(GenZElectronNumDaught->at(it));
    truthp.SetParticleIndexMother(GenZElectronMotherIndex->at(it));
    truthp.SetTauDecayMode(GenZElectronTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenZElectronPdgId->at(it)) == 1 || fabs(GenZElectronPdgId->at(it)) == 3 || fabs(GenZElectronPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenZElectronPdgId->at(it)) == 2 || fabs(GenZElectronPdgId->at(it)) == 4 || fabs(GenZElectronPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenZElectronPdgId->at(it)) == 11 || fabs(GenZElectronPdgId->at(it)) ==13 || fabs(GenZElectronPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenZElectronPdgId->at(it)) == 12 || fabs(GenZElectronPdgId->at(it)) ==14 || fabs(GenZElectronPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenZElectronPdgId->at(it)) == 22 || fabs(GenZElectronPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenZElectronPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;
    
    if(GenZElectronPdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }
  
  
  m_logger << DEBUG << "Filling Truth WMu" << LQLogger::endmsg;
  
  for (UInt_t it=0; it< GenWMuEta->size(); it++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenWMuPt->at(it), GenWMuEta->at(it), GenWMuPhi->at(it), GenWMuEnergy->at(it));

    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenWMuPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }
    
    if (duplicate) continue;
    
    truthp.SetParticlePx(GenWMuPx->at(it));
    truthp.SetParticlePy(GenWMuPy->at(it));
    truthp.SetParticlePz(GenWMuPz->at(it));
    if(GenWMuVX){
      truthp.SetParticleVx(GenWMuVX->at(it));
      truthp.SetParticleVy(GenWMuVY->at(it));
      truthp.SetParticleVz(GenWMuVZ->at(it));
    }
    truthp.SetParticlePdgId(GenWMuPdgId->at(it));
    truthp.SetParticleStatus(GenWMuStatus->at(it));
    
    truthp.SetParticleNDaughter(GenWMuNumDaught->at(it));
    truthp.SetParticleIndexMother(GenWMuMotherIndex->at(it));
    truthp.SetTauDecayMode(GenWMuTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenWMuPdgId->at(it)) == 1 || fabs(GenWMuPdgId->at(it)) == 3 || fabs(GenWMuPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenWMuPdgId->at(it)) == 2 || fabs(GenWMuPdgId->at(it)) == 4 || fabs(GenWMuPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenWMuPdgId->at(it)) == 11 || fabs(GenWMuPdgId->at(it)) ==13 || fabs(GenWMuPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenWMuPdgId->at(it)) == 12 || fabs(GenWMuPdgId->at(it)) ==14 || fabs(GenWMuPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenWMuPdgId->at(it)) == 22 || fabs(GenWMuPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenWMuPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;
    
    if(GenWMuPdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }
  
  m_logger << DEBUG << "Filling Truth WTau" << LQLogger::endmsg;

  for (UInt_t it=0; it< GenWTauEta->size(); it++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenWTauPt->at(it), GenWTauEta->at(it), GenWTauPhi->at(it), GenWTauEnergy->at(it));
    

    //cout << "GenWTauEta: PDGID/STATUS  = " << GenWTauPdgId->at(it) << " " << GenWTauStatus->at(it) <<  " " << GenWTauNumDaught->at(it) << " " <<  GenWTauTauDecayMode->at(it)<< " "   << GenWTauMotherIndex->at(it)   <<" Eta/phi "  <<  GenWTauEta->at(it) <<  " / "  <<  GenWTauPhi->at(it) << endl;
    
    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenWTauPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }
    
    if (duplicate) continue;
    
    truthp.SetParticlePx(GenWTauPx->at(it));
    truthp.SetParticlePy(GenWTauPy->at(it));
    truthp.SetParticlePz(GenWTauPz->at(it));
    if(GenWTauVX){
      truthp.SetParticleVx(GenWTauVX->at(it));
      truthp.SetParticleVy(GenWTauVY->at(it));
      truthp.SetParticleVz(GenWTauVZ->at(it));
    }
    truthp.SetParticlePdgId(GenWTauPdgId->at(it));
    truthp.SetParticleStatus(GenWTauStatus->at(it));
    
    truthp.SetParticleNDaughter(GenWTauNumDaught->at(it));
    truthp.SetParticleIndexMother(GenWTauMotherIndex->at(it));
    truthp.SetTauDecayMode(GenWTauTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenWTauPdgId->at(it)) == 1 || fabs(GenWTauPdgId->at(it)) == 3 || fabs(GenWTauPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenWTauPdgId->at(it)) == 2 || fabs(GenWTauPdgId->at(it)) == 4 || fabs(GenWTauPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenWTauPdgId->at(it)) == 11 || fabs(GenWTauPdgId->at(it)) ==13 || fabs(GenWTauPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenWTauPdgId->at(it)) == 12 || fabs(GenWTauPdgId->at(it)) ==14 || fabs(GenWTauPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenWTauPdgId->at(it)) == 22 || fabs(GenWTauPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenWTauPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;
    
    if(GenWTauPdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }
  
  
  m_logger << DEBUG << "Filling Truth WEl" << LQLogger::endmsg;
  
  for (UInt_t it=0; it< GenWElectronEta->size(); it++) {
    snu::KTruth truthp;
    truthp.SetPtEtaPhiE(GenWElectronPt->at(it), GenWElectronEta->at(it), GenWElectronPhi->at(it), GenWElectronEnergy->at(it));
    
    bool duplicate = false;
    for(unsigned int itr = 0; itr < vtruth.size() ; itr++){
      if( (GenWElectronPdgId->at(it) == vtruth.at(itr).PdgId()) && (truthp.DeltaR(vtruth.at(itr)) < 0.1)) duplicate = true;
    }
    //cout << "GenWElectronEta: PDGID/STATUS  = " << GenWElectronPdgId->at(it) << " " << GenWElectronStatus->at(it) <<  " " << GenWElectronNumDaught->at(it) << " " << GenWElectronTauDecayMode->at(it) << " " << GenWElectronMotherIndex->at(it)   <<" Eta/phi "  <<  GenWElectronEta->at(it) <<  " / "  <<  GenWElectronPhi->at(it) << endl;

    if (duplicate) continue;
    
    truthp.SetParticlePx(GenWElectronPx->at(it));
    truthp.SetParticlePy(GenWElectronPy->at(it));
    truthp.SetParticlePz(GenWElectronPz->at(it));
    if(GenWElectronVX){
      truthp.SetParticleVx(GenWElectronVX->at(it));
      truthp.SetParticleVy(GenWElectronVY->at(it));
      truthp.SetParticleVz(GenWElectronVZ->at(it));
    }
    truthp.SetParticlePdgId(GenWElectronPdgId->at(it));
    truthp.SetParticleStatus(GenWElectronStatus->at(it));
    
    truthp.SetParticleNDaughter(GenWElectronNumDaught->at(it));
    truthp.SetParticleIndexMother(GenWElectronMotherIndex->at(it));
    truthp.SetTauDecayMode(GenWElectronTauDecayMode->at(it));
    
    float charge_truth = -999.;
    if(fabs(GenWElectronPdgId->at(it)) == 1 || fabs(GenWElectronPdgId->at(it)) == 3 || fabs(GenWElectronPdgId->at(it)) == 5) charge_truth = -1./3.;
    else if(fabs(GenWElectronPdgId->at(it)) == 2 || fabs(GenWElectronPdgId->at(it)) == 4 || fabs(GenWElectronPdgId->at(it)) == 6) charge_truth = 2./3.;
    else if(fabs(GenWElectronPdgId->at(it)) == 11 || fabs(GenWElectronPdgId->at(it)) ==13 || fabs(GenWElectronPdgId->at(it)) ==15) charge_truth = -1.;
    else if(fabs(GenWElectronPdgId->at(it)) == 12 || fabs(GenWElectronPdgId->at(it)) ==14 || fabs(GenWElectronPdgId->at(it)) ==16) charge_truth = 0.;
    else if(fabs(GenWElectronPdgId->at(it)) == 22 || fabs(GenWElectronPdgId->at(it)) == 23) charge_truth = 0.;
    else if(fabs(GenWElectronPdgId->at(it)) == 24) charge_truth =1.;
    else charge_truth = -999.;
    
    if(GenWElectronPdgId->at(it) < 0) charge_truth *=-1.;
    
    truthp.SetCharge(int(charge_truth));
    vtruth.push_back(truthp);
  }
  

  
  return vtruth;
}
