#include "include/FakeRateCalculator.h"

FRCalculator::FRCalculator() {
/*  
  arraypT = new Double_t [nintpT+1];
  arraypT[0] = 10.;
  arraypT[1] = 15.;
  arraypT[2] = 20.;
  arraypT[3] = 25.;
  arraypT[4] = 30.;
  arraypT[5] = minbin;

  for (UInt_t i=0; i+6<nintpT+1; i++) {
    //arraypT[i+6] = minbin + binwidh * exp (i);
    arraypT[i+6] = minbin + binwidh * (i+1);
    cout << arraypT[i+6] <<endl;
  }
*/  
  Double_t arrayeta [] = {0.0,1.0,1.479,2.0,2.5};
  Double_t arraypT [] = {10.,15.,20.,25.,30.,35.,45.,60.,80.,100.};

  h_MT = new TH1F ("h_MT", "Transverse mass", 100, 0.0, 100.0);
  h_HT = new TH1F ("h_HT", "Sum p_{T} of the jets", 100,  0.0, 500.0);
  h_nEvents = new TH2F ("h_nEvents", "Number of Events",ninteta,arrayeta,nintpT,arraypT);
  h_nEventsFO = new TH2F ("h_nEventsFO", "Number of Events FO",ninteta,arrayeta,nintpT,arraypT);
  h_FOrate = new TH2F ("h_FOrate", "FO rate",ninteta,arrayeta,nintpT,arraypT);

  h_TLnum = new MuonPlots("TL_numerator");
  h_TLden = new MuonPlots("TL_denominator");

}
FRCalculator::~FRCalculator() {}

void FRCalculator::LoopFR() {

  cout << "total number of entries " <<nentries<<endl;

  reweightPU = new ReweightPU("/uscms_data/d2/fgior8/LQntuple_09/CMSSW_5_3_4_LQ/src/code/MC_pu.root", "/uscms_data/d2/fgior8/LQntuple_11/CMSSW_5_3_8_LQ/src/code/MyDataPileupHistogram.root");
 
  if(!MCweight) MCweight=1;

  weight=MCweight;

  if (fChain == 0) 
    cout << "Ciao!" << endl;

//  cout << "Do you want limited events?" <<endl;
//  cin >> entrieslimit;
//  if (entrieslimit != -1)
//    nentries=entrieslimit;
//  nentries = 1000;

  if (debug) cout<< "at the loop" <<endl;

  std::set<int> runs;
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {

    if (!(jentry % 1000))
      cout << jentry <<endl;
    /*
    if ( runs.find(EventAux_run) == runs.end() ) {
      cout << EventAux_run <<endl;
      runs.insert(EventAux_run);
    }
    */
    fChain->GetEntry(jentry);

    if (isTrackingFailure || passTrackingFailureFilter) continue;

    if (!passBeamHaloFilterLoose) continue;

    if (passBadEESupercrystalFilter || passEcalDeadCellBoundaryEnergyFilter || passEcalDeadCellTriggerPrimitiveFilter || passEcalLaserCorrFilter) continue;

    if (!passHBHENoiseFilter) continue; // || passHcalLaserEventFilter) continue;

    std::vector<TString> triggerslist;
    triggerslist.push_back("HLT_Mu5_v");
    triggerslist.push_back("HLT_Mu8_v");
    triggerslist.push_back("HLT_Mu12_v");
    triggerslist.push_back("HLT_Mu17_v");
    triggerslist.push_back("HLT_Mu24_v");

    if ( !TriggerSelector(triggerslist, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler) ) continue;

    if (MC_pu) {
      /// ***PU reweghting*** ///
      //weight_ = noreweight_;// mc weight;
      h_nvtx_norw->Fill(PileUpInteractionsTrue->at(0), MCweight);
      weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;
      h_nvtx_rw->Fill(PileUpInteractionsTrue->at(0), weight);
    }

    numberVertices = VertexNDF->size();
    goodVerticies = new Bool_t [numberVertices];
    h_nVertex->Fill(numberVertices, weight);
    if ( !isGoodEvent(numberVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticies) ) continue;

    for(UInt_t vv=0; vv<VertexNDF->size(); vv++) {
      if(goodVerticies[vv]) {
        VertexN=vv;
        break;
      }
    } 

    if (debug) cout<< "good vertex found" <<endl;

    std::vector<Lepton> muonLooseColl;
    MuonLoose.SetPt(20);
    MuonLoose.SetEta(2.4); 
    MuonLoose.SetRelIso(0.50); 
    MuonLoose.SetChiNdof(50); 
    MuonLoose.SetBSdxy(0.20);
    MuonLoose.SetBSdz(0.10); 
    MuonLoose.SetDeposits(4.0, 6.0);
    MuonLoose.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonLooseColl);

    if (debug) cout<< "Event number " <<jentry<<endl;
    
    std::vector<Lepton> muonTightColl;
    MuonTight.SetPt(20); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(0.05); 
    MuonTight.SetChiNdof(10); 
    MuonTight.SetBSdxy(0.005); 
    MuonTight.SetBSdz(0.10);
    MuonTight.SetDeposits(4.0,6.0);
    MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonStationMatches, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonTightColl);

    std::vector<Lepton> electronTightColl;
    ElectronTight.SetPt(20); 
    ElectronTight.SetEta(2.4); 
    ElectronTight.SetRelIso(0.15); 
    ElectronTight.SetBSdxy(0.01); 
    ElectronTight.SetBSdz(0.10);
    ElectronTight.ElectronSelection(*ElectronIsEB, *ElectronIsEE, *ElectronHasTrackerDrivenSeed, *ElectronHasEcalDrivenSeed, *ElectronEta, *ElectronPhi, *ElectronPt, *ElectronEnergy, *ElectronPFPhotonIso03, *ElectronPFNeutralHadronIso03, *ElectronPFChargedHadronIso03, *ElectronCharge, *ElectronGsfCtfScPixCharge, *ElectronMissingHitsEG, *ElectronHasMatchedConvPhot, *ElectronDeltaEtaTrkSC, *ElectronDeltaPhiTrkSC, *ElectronSigmaIEtaIEta, *ElectronHoE, *ElectronCaloEnergy, *ElectronESuperClusterOverP, *ElectronTrackVx, *ElectronTrackVy, *ElectronTrackVz, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), rhoJets, electronTightColl);
    
    std::vector<Jet> jetVetoColl;
    JetsVeto.SetPt(60);
    JetsVeto.SetEta(2.4);
    JetsVeto.JetSelectionLeptonVeto(*PFJetPassLooseID, *PFJetEta, *PFJetPhi, *PFJetPt, *PFJetEnergy, *PFJetNeutralEmEnergyFraction, *PFJetNeutralHadronEnergyFraction, *PFJetChargedEmEnergyFraction, *PFJetChargedHadronEnergyFraction, *PFJetChargedMultiplicity, *PFJetNConstituents, *PFJetCombinedSecondaryVertexBTag, *PFJetClosestVertexWeighted3DSeparation, electronTightColl, muonTightColl, jetVetoColl);

    if (debug) cout<< "done selecting collections" <<endl;

    ///// SOME STANDARD PLOTS /////

    if (muonLooseColl.size()>0 && jetVetoColl.size()>0) {

      if (muonTightColl.size()>0) {
        h_MET->Fill(PFMETType01XYCor->at(0), weight);
        h_MT->Fill( sqrt(2.*muonTightColl[0].lorentzVec().Pt()*PFMETType01XYCor->at(0)* (1 - cos(muonTightColl[0].lorentzVec().Phi()-PFMETPhiType01XYCor->at(0))) ), weight);
      }
      if (muonTightColl.size()>=2) {
        h_prova->Fill( ( muonTightColl[0].lorentzVec() + muonTightColl[1].lorentzVec() ).M(), weight);
      }
    }

    if (muonLooseColl.size() > 0 && jetVetoColl.size()>0) {
      for (UInt_t i=0; i<muonLooseColl.size(); i++) {
        index=muonLooseColl[i].ilepton();
        h_muonsLoose->Fill(weight, (Int_t) muonLooseColl.size(), muonLooseColl[i].lorentzVec().Pt(), muonLooseColl[i].eta(), muonLooseColl[i].lorentzVec().Phi(), muonLooseColl[i].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonLooseColl[i].chiNdof(), muonLooseColl[i].dxy_BS(), muonLooseColl[i].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
      }
    }

    if (muonTightColl.size() > 0 && jetVetoColl.size()>0) {
      for (UInt_t i=0; i<muonTightColl.size(); i++) {
	index=muonTightColl[i].ilepton();
	h_muons->Fill(weight, (Int_t) muonTightColl.size(), muonTightColl[i].lorentzVec().Pt(), muonTightColl[i].eta(), muonTightColl[i].lorentzVec().Phi(), muonTightColl[i].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonTightColl[i].chiNdof(), muonTightColl[i].dxy_BS(), muonTightColl[i].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
	//	if (muonTightColl[i].fakeType() == Lepton::unknown && Muon_Gen_Mother[index]!=999) cout<<"SCONOSCIUTO!!!!!"<<" pdgID "<<Muon_Gen_Mother[index]<<endl;
      }	 
    }
    
    if (electronTightColl.size() > 0) {
      for (UInt_t i=0; i<electronTightColl.size(); i++) {
	index=electronTightColl[i].ilepton();
	h_electrons->Fill(weight, (Int_t) electronTightColl.size(), electronTightColl[i].lorentzVec().Pt(), electronTightColl[i].eta(), electronTightColl[i].lorentzVec().Phi(), electronTightColl[i].charge(), ElectronTrkIsoDR03->at(index), ElectronEcalIsoDR03->at(index), ElectronHcalIsoDR03->at(index), ElectronPFPhotonIso03->at(index), ElectronPFChargedHadronIso03->at(index), ElectronPFNeutralHadronIso03->at(index), electronTightColl[i].dxy_BS(), electronTightColl[i].dz_BS(), rhoJets);
      }	 
    }  

    HT = 0.;
    if (jetVetoColl.size() > 0) {
      for (UInt_t i=0; i<jetVetoColl.size(); i++) {
        HT += jetVetoColl[i].lorentzVec().Pt();
        index=jetVetoColl[i].ijet();
        h_jets_veto->Fill( weight, (Int_t) jetVetoColl.size(), jetVetoColl[i].lorentzVec().Pt(), jetVetoColl[i].eta(), jetVetoColl[i].lorentzVec().Phi(), PFJetTrackCountingHighPurBTag->at(index), PFJetJetProbabilityBTag->at(index), jetVetoColl[i].btag_disc(), PFJetClosestVertexWeightedXYSeparation->at(index), PFJetClosestVertexWeightedZSeparation->at(index), PFJetClosestVertexWeighted3DSeparation->at(index) );
      }	 
    }  

    if (HT > 0)
      h_HT->Fill(HT, weight);

    ///// END STANDARD PLOTS /////

    if (debug) cout<< "done with the plots starting TL" <<endl;

    if ( ZandWveto(muonLooseColl, PFMETType01XYCor->at(0), PFMETPhiType01XYCor->at(0)) ) continue;


    ///// FAKE RATES /////

    dr=-999.9;
    
    if (muonLooseColl.size() == 1 && muonTightColl.size() == 1  && jetVetoColl.size() >= 1) {
      for (UInt_t iii=0; iii<muonTightColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetVetoColl.size(); yyy++) {
	 
	  dr = muonTightColl[iii].lorentzVec().DeltaR( jetVetoColl[yyy].lorentzVec() );
	  if (dr > 1.0) {
	    h_nEvents->Fill(fabs(muonTightColl[iii].eta()),muonTightColl[iii].lorentzVec().Pt(), weight);
 
            if (muonTightColl[iii].lorentzVec().Pt()<=35 || true) {
              h_nVertex1->Fill(numberVertices, weight);
              index=muonTightColl[iii].ilepton();
              h_TLnum->Fill(weight, (Int_t) muonTightColl.size(), muonTightColl[iii].lorentzVec().Pt(), muonTightColl[iii].eta(), muonTightColl[iii].lorentzVec().Phi(), muonTightColl[iii].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonTightColl[iii].chiNdof(), muonTightColl[iii].dxy_BS(), muonTightColl[iii].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
            }
	    
	    goto fine;
	  }
        }
      }
    }
    fine:
    
    if (debug) cout<< "denominator" <<endl;

    if (muonLooseColl.size() == 1 && jetVetoColl.size() >= 1) {
      for (UInt_t iii=0; iii<muonLooseColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetVetoColl.size(); yyy++) {
	  
	  dr = muonLooseColl[iii].lorentzVec().DeltaR( jetVetoColl[yyy].lorentzVec() );
	  if (dr > 1.0) {
	    h_nEventsFO->Fill(fabs(muonLooseColl[iii].eta()),muonLooseColl[iii].lorentzVec().Pt(), weight);
    
            if (muonLooseColl[iii].lorentzVec().Pt()<=35 || true) {
              h_nVertex0->Fill(numberVertices, weight);
              index=muonLooseColl[iii].ilepton();
              h_TLden->Fill(weight, (Int_t) muonLooseColl.size(), muonLooseColl[iii].lorentzVec().Pt(), muonLooseColl[iii].eta(), muonLooseColl[iii].lorentzVec().Phi(), muonLooseColl[iii].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonLooseColl[iii].chiNdof(), muonLooseColl[iii].dxy_BS(), muonLooseColl[iii].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
            }
	    
	    goto fineFO;
	  }
	}
      }
    }
    fineFO:
    ; 
  } //loop on the entries
  
  if (debug) cout<< "out of the loop" <<endl;

  getFakerate(h_nEvents,h_nEventsFO,h_FOrate,ninteta,nintpT);
  getFakerate(h_nVertex1,h_nVertex0,h_nVertex2,50);

  outfile->cd();
  h_nvtx_norw->Write();
  h_nvtx_rw->Write();
  h_prova->Write();
  h_HT->Write();
  h_MT->Write();
  h_MET->Write();
  h_METsign->Write();
  h_nVertex->Write();
  h_nVertex0->Write();
  h_nVertex1->Write();
  h_nVertex2->Write();
  h_nEvents->Write();
  h_nEventsFO->Write();
  h_FOrate->Write();

  Dir = outfile->mkdir("Muons");
  outfile->cd( Dir->GetName() );
  h_muons->Write();
  h_muonsLoose->Write();
  h_TLden->Write();
  h_TLnum->Write();
  outfile->cd();

  Dir = outfile->mkdir("Electrons");
  outfile->cd( Dir->GetName() );
  h_electrons->Write();
  outfile->cd();  

  Dir = outfile->mkdir("Jets_with_veto");
  outfile->cd( Dir->GetName() );
  h_jets_veto->Write();
  outfile->cd();

  outfile->Close();

  
}
