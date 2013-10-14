#include "SNUTreeFiller.h"
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

using namespace snu;
using namespace std;

SNUTreeFiller::SNUTreeFiller() {};


SNUTreeFiller::~SNUTreeFiller() {};


std::vector<KElectron> SNUTreeFiller::GetAllElectrons(int nVertex){
  
  std::vector<KElectron> electrons;
  for (UInt_t iel=0; iel< ElectronEta->size(); iel++) {
    KElectron el;
    
    /// Need to add filling code
    electrons.push_back(el);
  }
  
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
  

  //std::sort( leptonColl.begin(), leptonColl.end(), LeptonPTSorter );
  return muons;
}

