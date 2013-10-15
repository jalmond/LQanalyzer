#include "SNUTreeFiller.h"
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;

SNUTreeFiller::SNUTreeFiller() {};


SNUTreeFiller::~SNUTreeFiller() {};

KEvent SNUTreeFiller::GetEventInfo(){
  
  snu::KEvent kevent;
  kevent.SetMET( PFMETType01XYCor->at(0));
  int nVertices = VertexNDF->size();
  kevent.SetNVertices(nVertices);
  goodVerticies = new Bool_t [nVertices];
  
  if ( !isGoodEvent(nVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticies) ) kevent.SetIsGoodEvent(false);
  else  kevent.SetIsGoodEvent(true);
  
  for(UInt_t vv=0; vv<VertexNDF->size(); vv++) {
    if(goodVerticies[vv]) {
      VertexN=vv;
      break;
    }
  }
    
  kevent.SetVertexX(VertexX->at(VertexN));
  kevent.SetVertexY(VertexY->at(VertexN));
  kevent.SetVertexZ(VertexZ->at(VertexN));  
  kevent.SetVertexIsFake(VertexIsFake->at(VertexN));
  
  return kevent;
}

std::vector<KElectron> SNUTreeFiller::GetAllElectrons(){
  
  std::vector<KElectron> electrons;
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
    el.SuperClusterOverP(ElectronESuperClusterOverP->at(iel));
    el.Trkdx(ElectronTrackVx->at(iel));
    el.Trkdy(ElectronTrackVy->at(iel));
    el.Trkdz(ElectronTrackVz->at(iel));

    /// Need to add filling code
    electrons.push_back(el);
  }
  
  std::sort( electrons.begin(), electrons.end(), isHigherPt );


  return electrons;
}

std::vector<KJet> SNUTreeFiller::GetAllJets(){
  std::vector<KJet> jets;
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


std::vector<KMuon> SNUTreeFiller::GetAllMuons(int iVertex){
  
  std::vector<KMuon> muons;
  for (UInt_t ilep=0; ilep< MuonEta->size(); ilep++) {
    KMuon muon;

    muon.SetPtEtaPhiE(MuonPt->at(ilep),MuonEta->at(ilep),MuonPhi->at(ilep),MuonEnergy->at(ilep));
    muon.SetPtErr(MuonPtError->at(ilep));
    muon.SetEtaErr(MuonEtaError->at(ilep));
    
    
    /// Isolation
    muon.SetISOR03ChargedHad(MuonPFIsoR03ChargedHadron->at(ilep));
    muon.SetISOR03NeutralHad(MuonPFIsoR03NeutralHadron->at(ilep));
    muon.SetISOR03Photon(MuonPFIsoR03Photon->at(ilep));       
    muon.SetIsolationEcalVeto(MuonEcalVetoIso->at(ilep));
    muon.SetIsolationHcalVeto(MuonHcalVetoIso->at(ilep));

    //// what charge is this????
    muon.SetCharge(MuonCharge->at(ilep));


    /// PU correction
    muon.SetPileUp_R03(MuonPFIsoR03PU->at(ilep));

    ////////// TRACK
    /// Imapct parameter 
    
    muon.SetTrackVx(MuonTrkVx->at(ilep));
    muon.SetTrackVy(MuonTrkVy->at(ilep));
    muon.SetTrackVz(MuonTrkVz->at(ilep));
    muon.Setdz( MuonTrkVz->at(ilep) - VertexZ->at(iVertex));
    muon.Setdxy( sqrt(pow(MuonTrkVx->at(ilep)-VertexX->at(iVertex),2)+pow(MuonTrkVy->at(ilep)-VertexY->at(iVertex),2)));
    muon.SetD0( MuonTrkD0->at(ilep));
    muon.SetD0Error (MuonTrkD0Error->at(ilep));
    
    //// chi2
    muon.SetGlobalchi2( MuonGlobalChi2->at(ilep));
        
    /// hits
    muon.SetValidHits( MuonGlobalTrkValidHits->at(ilep));
    muon.SetPixelValidHits(  MuonTrkPixelHits->at(ilep));
    muon.SetValidStations( MuonStationMatches->at(ilep));
    muon.SetLayersWithMeasurement ( MuonTrackLayersWithMeasurement->at(ilep));
    

    //fakeType = Lepton::unknown;
    //looseTight = Lepton::Other;
    //leptonType = Lepton::Muon;
  

    
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

