#include "EfficiencyCalculator.h"

EffCalculator::EffCalculator() {

  Double_t arrayeta [] = {0.0,1.0,1.479,2.0,2.5};
  Double_t arraypT [] = {10.,15.,20.,25.,35.};

  h_MT = new TH1F ("h_MT", "Transverse mass", 100, 0.0, 100.0);

  h_nEvents = new TH2F ("h_nEvents", "Number of Events",ninteta,arrayeta,nintpT,arraypT);
  h_nEventsFO = new TH2F ("h_nEventsFO", "Number of Events FO",ninteta,arrayeta,nintpT,arraypT);
  h_FOrate = new TH2F ("h_FOrate", "FO rate",ninteta,arrayeta,nintpT,arraypT);

  h_TLnum = new MuonPlots("TL_numerator");
  h_TLden = new MuonPlots("TL_denominator");

}
EffCalculator::~EffCalculator() {}

void EffCalculator::LoopEff() {

  cout << "total number of entries " <<nentries<<endl;
 
  reweightPU = new ReweightPU("/uscms_data/d2/fgior8/LQntuple_09/CMSSW_5_3_4_LQ/src/code/MC_pu.root", "/uscms_data/d2/fgior8/LQntuple_09/CMSSW_5_3_4_LQ/src/code/MyDataPileupHistogram.root");

  if(!MCweight) MCweight=1;

  weight=MCweight;

  if (fChain == 0) 
    cout << "Ciao!" << endl;

//  cout << "Do you want limited events?" <<endl;
//  cin >> entrieslimit;
//  if (entrieslimit != -1)
//    nentries=entrieslimit;
  //entrieslimit = 10000;

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
    triggerslist.push_back("HLT_Mu17_TkMu8_v");

    if ( !TriggerSelector(triggerslist, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler) ) continue; 
/*
    /// ***PU reweghting*** ///
    //weight_ = noreweight_;// mc weight;
    h_nvtx_norw->Fill(PileUpInteractionsTrue->at(0), MCweight);
    weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;
    h_nvtx_rw->Fill(PileUpInteractionsTrue->at(0), weight);
*/
    numberVertices = VertexNDF->size();
    goodVerticiesB = new Bool_t [numberVertices];
    h_nVertex->Fill(numberVertices, weight);
    if ( !isGoodEvent(numberVertices, *VertexIsFake, *VertexNDF, *VertexX, *VertexY, *VertexZ, goodVerticiesB) ) continue;

    for(UInt_t vv=0; vv<VertexNDF->size(); vv++) {
      if(goodVerticiesB[vv]) {
        VertexN=vv;
        break;
      }
    } 

    if (debug) cout<< "good vertex found" <<endl;

    std::vector<Lepton> muonLooseColl;
    MuonLoose.SetPt(10); 
    MuonLoose.SetEta(2.4); 
    MuonLoose.SetRelIso(1.00); 
    MuonLoose.SetChiNdof(50); 
    MuonLoose.SetBSdxy(0.20); 
    MuonLoose.SetBSdz(0.10);
    MuonLoose.SetDeposits(4.0, 6.0);
    MuonLoose.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonGlobalTrkValidHits, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonLooseColl);

    if (debug) cout<< "Event number " <<jentry<<endl;
    
    std::vector<Lepton> muonTightColl;
    MuonTight.SetPt(10); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(0.12); 
    MuonTight.SetChiNdof(10); 
    MuonTight.SetBSdxy(0.02); 
    MuonTight.SetBSdz(0.10);
    MuonTight.SetDeposits(4.0,6.0);
    MuonTight.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonGlobalTrkValidHits, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonTightColl);

    std::vector<Lepton> muonProbeColl;
    Probe.SetPt(10);
    Probe.SetEta(2.4);
    Probe.SetRelIso(0.10);
    Probe.SetChiNdof(10);
    Probe.SetBSdxy(0.02);
    Probe.SetBSdz(0.10);
    Probe.SetDeposits(4.0,6.0);
    Probe.MuonSelection(*MuonIsPF, *MuonIsGlobal, *MuonEta, *MuonPhi, *MuonPt, *MuonPtError, *MuonEnergy, *MuonPFIsoR03ChargedHadron, *MuonPFIsoR03NeutralHadron, *MuonPFIsoR03Photon, *MuonEcalVetoIso, *MuonHcalVetoIso, *MuonCharge, *MuonGlobalTrkValidHits, *MuonTrkPixelHits, *MuonGlobalTrkValidHits, *MuonTrackLayersWithMeasurement, *MuonGlobalChi2, *MuonTrkVx, *MuonTrkVy, *MuonTrkVz, *MuonTrkD0, *MuonTrkD0Error, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), *MuonPFIsoR03PU, muonProbeColl);

    h_MET->Fill(PFMET->at(0), weight);

    if (muonTightColl.size()>0) {
      h_MT->Fill( sqrt(2.*muonTightColl[0].lorentzVec().Pt()*PFMET->at(0)* (1 - cos(muonTightColl[0].lorentzVec().Phi()-PFMETPhi->at(0))) ), weight);
    }
    if (muonTightColl.size()==2) {
      h_zpeak->Fill( ( muonTightColl[0].lorentzVec() + muonTightColl[1].lorentzVec() ).M(), weight);
    }

    std::vector<Lepton> electronTightColl;
    ElectronTight.SetPt(10); 
    ElectronTight.SetEta(2.4); 
    ElectronTight.SetRelIso(0.10); 
    ElectronTight.SetBSdxy(0.02); 
    ElectronTight.SetBSdz(0.10);
    ElectronTight.ElectronSelection(*ElectronIsEB, *ElectronIsEE, *ElectronHasTrackerDrivenSeed, *ElectronHasEcalDrivenSeed, *ElectronEta, *ElectronPhi, *ElectronPt, *ElectronEnergy, *ElectronTrkIsoDR03, *ElectronEcalIsoDR03, *ElectronHcalIsoDR03, *ElectronCharge, *ElectronGsfCtfScPixCharge, *ElectronMissingHitsEG, *ElectronHasMatchedConvPhot, *ElectronDeltaEtaTrkSC, *ElectronDeltaPhiTrkSC, *ElectronSigmaIEtaIEta, *ElectronHoE, *ElectronCaloEnergy, *ElectronESuperClusterOverP, *ElectronTrackVx, *ElectronTrackVy, *ElectronTrackVz, VertexX->at(VertexN), VertexY->at(VertexN), VertexZ->at(VertexN), rhoJets, electronTightColl);

    /*
    std::vector<Jet> jetColl;
    Jets.SetPt(5); Jets.SetEta(2.5);
    Jets.JetSelection(Njet, Jet_Id_loose, Jet_Pt, Jet_Px, Jet_Py, Jet_Pz, Jet_E, Jet_Eta, Jet_neutralHadronEnergyFraction, Jet_neutralEmEnergyFraction, Jet_chargedHadronEnergyFraction, Jet_chargedMultiplicity, Jet_chargedEmEnergyFraction, Jet_BTag_TCHE, jetColl);
    if (jetColl.size() >0 && muonLooseColl.size()==1) {
      for (UInt_t i=0; i<jetColl.size(); i++)
        for (UInt_t j=0; j<muonLooseColl.size(); j++) {
          if (jetColl[i].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) > 1.0 && jetColl[i].lorentzVec().Pt()>40)
            for (UInt_t m=0; m<jetColl.size(); m++) {
              if (jetColl[m].lorentzVec().DeltaR( muonLooseColl[j].lorentzVec() ) < 0.3) {
                index=jetColl[m].ijet();
                h_jets->Fill(1.0, (Int_t) jetColl.size(), Jet_Pt[index], Jet_Eta[index], Jet_Phi[index]);
                goto end;
              }
            }
        }
    }
    end:
    */
    std::vector<Jet> jetVetoColl;
    JetsVeto.SetPt(40); 
    JetsVeto.SetEta(2.4);
    JetsVeto.JetSelectionLeptonVeto(*PFJetPassLooseID, *PFJetEta, *PFJetPhi, *PFJetPt, *PFJetEnergy, *PFJetNeutralEmEnergyFraction, *PFJetNeutralHadronEnergyFraction, *PFJetChargedEmEnergyFraction, *PFJetChargedHadronEnergyFraction, *PFJetChargedMultiplicity, *PFJetNConstituents, *PFJetCombinedSecondaryVertexBTag, *PFJetClosestVertexWeighted3DSeparation, electronTightColl, muonTightColl, jetVetoColl);

    if (debug) cout<< "done selecting collections" <<endl;

    ///// SOME STANDARD PLOTS /////

    if (muonLooseColl.size() > 0) {
      for (UInt_t i=0; i<muonLooseColl.size(); i++) {
        index=muonLooseColl[i].ilepton();
        h_muonsLoose->Fill(weight, (Int_t) muonLooseColl.size(), muonLooseColl[i].lorentzVec().Pt(), muonLooseColl[i].eta(), muonLooseColl[i].lorentzVec().Phi(), muonLooseColl[i].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonLooseColl[i].chiNdof(), muonLooseColl[i].dxy_BS(), muonLooseColl[i].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
      }
    }

    if (muonTightColl.size() > 0) {
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

   if (jetVetoColl.size() > 0) {
      for (UInt_t i=0; i<jetVetoColl.size(); i++) {
        index=jetVetoColl[i].ijet();
        h_jets_veto->Fill( weight, (Int_t) jetVetoColl.size(), jetVetoColl[i].lorentzVec().Pt(), jetVetoColl[i].eta(), jetVetoColl[i].lorentzVec().Phi(), PFJetTrackCountingHighPurBTag->at(index), PFJetJetProbabilityBTag->at(index), jetVetoColl[i].btag_disc(), PFJetClosestVertexWeightedXYSeparation->at(index), PFJetClosestVertexWeightedZSeparation->at(index), PFJetClosestVertexWeighted3DSeparation->at(index) );
      }	 
    }  

    ///// END STANDARD PLOTS /////

//    if ( !Zselection(muonTightColl, PFMET->at(0)) ) continue;

    if (debug) cout<< "done with the plots starting TL" <<endl;

    if ( Zselection(muonTightColl, PFMET->at(0)) ) {
      h_nVertex1->Fill(numberVertices, weight);
      for (UInt_t iii=0; iii<muonTightColl.size(); iii++) {
        h_nEvents->Fill(fabs(muonTightColl[iii].eta()),muonTightColl[iii].lorentzVec().Pt(), weight);

        index=muonTightColl[iii].ilepton();
        h_TLnum->Fill(weight, (Int_t) muonTightColl.size(), muonTightColl[iii].lorentzVec().Pt(), muonTightColl[iii].eta(), muonTightColl[iii].lorentzVec().Phi(), muonTightColl[iii].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonTightColl[iii].chiNdof(), muonTightColl[iii].dxy_BS(), muonTightColl[iii].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
      }
    }
    if ( Zselection(muonLooseColl, PFMET->at(0)) ) {
      h_nVertex0->Fill(numberVertices, weight);
      for (UInt_t iii=0; iii<muonLooseColl.size(); iii++) {
        h_nEventsFO->Fill(fabs(muonLooseColl[iii].eta()),muonLooseColl[iii].lorentzVec().Pt(), weight);
        index=muonLooseColl[iii].ilepton();
        h_TLden->Fill(weight, (Int_t) muonLooseColl.size(), muonLooseColl[iii].lorentzVec().Pt(), muonLooseColl[iii].eta(), muonLooseColl[iii].lorentzVec().Phi(), muonLooseColl[iii].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonLooseColl[iii].chiNdof(), muonLooseColl[iii].dxy_BS(), muonLooseColl[iii].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
      }
    }

     
  } //loop on the entries
  
  if (debug) cout<< "out of the loop" <<endl;

  getFakerate(h_nEvents,h_nEventsFO,h_FOrate,ninteta,nintpT);
  getFakerate(h_nVertex1,h_nVertex0,h_nVertex2,50);

  outfile->cd();
  h_nvtx_norw->Write();
  h_nvtx_rw->Write();
  h_zpeak->Write();
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
  h_TLden->Write();
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
