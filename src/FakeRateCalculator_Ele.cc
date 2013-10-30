#include "FakeRateCalculator_Ele.h"

FRCalculator_Ele::FRCalculator_Ele() {
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

  h_TLnum = new ElectronPlots("TL_numerator");
  h_TLden = new ElectronPlots("TL_denominator");

}
FRCalculator_Ele::~FRCalculator_Ele() {}

void FRCalculator_Ele::LoopFR() {

 weight= SetEventWeight();  

  string analysisdir = getenv("FILEDIR");
  if(!isData)reweightPU = new ReweightPU((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  if (fChain == 0) 
    cout << "Ciao!" << endl;

  std::set<int> runs;
  for (Long64_t jentry = 0; jentry < nentries; jentry++ ) {


    snu::KEvent event_info = SetUpEvent(jentry); 
    
    if(!PassBasicEventCuts()) continue;     /// Initial event cuts

    std::vector<TString> triggerslist;
    triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
    triggerslist.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    triggerslist.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");

    if ( !TriggerSelector(triggerslist, *HLTInsideDatasetTriggerNames, *HLTInsideDatasetTriggerDecisions, *HLTInsideDatasetTriggerPrescales, prescaler) ) continue;


    /// Correct MC for pileup
    if (MC_pu&&!isData)  weight = reweightPU->GetWeight(PileUpInteractionsTrue->at(0))*MCweight;

    
      /// Create vector of kmuon objects :
    vector<snu::KMuon> all_muons = GetAllMuons();    
    vector<snu::KElectron> all_electrons = GetAllElectrons();
    vector<snu::KJet> all_jets = GetAllJets();        
    vector<snu::KTau> all_taus = GetAllTaus();        
    
    numberVertices = event_info.nVertices();
    if (!event_info.HasGoodPrimaryVertex()) continue; //// Make cut on event wrt vertex
    ///  use selection code (which returns a similar class vector with selected cuts)


    std::vector<snu::KElectron> electronLooseColl;
    ElectronLoose.SetPt(20);
    ElectronLoose.SetEta(2.4);
    ElectronLoose.SetRelIso(0.40);
    ElectronLoose.SetBSdxy(0.20);
    ElectronLoose.SetBSdz(0.10);
    ElectronLoose.ElectronSelection(all_electrons,electronLooseColl);

    if (debug) cout<< "Event number " <<jentry<<endl;
    
    std::vector<snu::KMuon> muonTightColl;
    MuonTight.SetPt(20); 
    MuonTight.SetEta(2.4); 
    MuonTight.SetRelIso(0.12); 
    MuonTight.SetChiNdof(10); 
    MuonTight.SetBSdxy(0.005); 
    MuonTight.SetBSdz(0.10);
    MuonTight.SetDeposits(4.0,6.0);
    MuonTight.MuonSelection(all_muons, muonTightColl);

    std::vector<snu::KElectron> electronTightColl;
    ElectronTight.SetPt(20); 
    ElectronTight.SetEta(2.4); 
    ElectronTight.SetRelIso(0.15); 
    ElectronTight.SetBSdxy(0.01); 
    ElectronTight.SetBSdz(0.10);
    ElectronTight.ElectronSelection(all_electrons, electronTightColl);
    
    std::vector<snu::KJet> jetVetoColl;
    JetsVeto.SetPt(60); 
    JetsVeto.SetEta(2.4);
    JetsVeto.JetSelectionLeptonVeto(all_jets,jetVetoColl);

    if (debug) cout<< "done selecting collections" <<endl;

    ///// SOME STANDARD PLOTS /////

    if (electronLooseColl.size()>0 && jetVetoColl.size()>0) {

      if (electronTightColl.size()>0) {
        h_MET->Fill(PFMETType01XYCor->at(0), weight);
        h_MT->Fill( sqrt(2.*electronTightColl[0].lorentzVec().Pt()*PFMETType01XYCor->at(0)* (1 - cos(electronTightColl[0].lorentzVec().Phi()-PFMETPhiType01XYCor->at(0))) ), weight);
      }
      if (electronTightColl.size()>=2) {
        h_prova->Fill( ( electronTightColl[0].lorentzVec() + electronTightColl[1].lorentzVec() ).M(), weight);
      }
    }

    if (muonTightColl.size() > 0 && jetVetoColl.size()>0) {
      for (UInt_t i=0; i<muonTightColl.size(); i++) {
	index=muonTightColl[i].ilepton();
	h_muons->Fill(weight, (Int_t) muonTightColl.size(), muonTightColl[i].lorentzVec().Pt(), muonTightColl[i].eta(), muonTightColl[i].lorentzVec().Phi(), muonTightColl[i].charge(), MuonTrkIso->at(index), MuonEcalIso->at(index), MuonHcalIso->at(index), MuonEcalVetoIso->at(index), MuonHcalVetoIso->at(index), MuonPFIsoR03Photon->at(index), MuonPFIsoR03ChargedHadron->at(index), MuonPFIsoR03NeutralHadron->at(index), muonTightColl[i].chiNdof(), muonTightColl[i].dxy_BS(), muonTightColl[i].dz_BS(), MuonPFIsoR03PU->at(index), rhoJets);
	//	if (muonTightColl[i].fakeType() == Lepton::unknown && Muon_Gen_Mother[index]!=999) cout<<"SCONOSCIUTO!!!!!"<<" pdgID "<<Muon_Gen_Mother[index]<<endl;
      }	 
    }
    
    if (electronTightColl.size() > 0 && jetVetoColl.size()>0) {
      for (UInt_t i=0; i<electronTightColl.size(); i++) {
	index=electronTightColl[i].ilepton();
	h_electrons->Fill(weight, (Int_t) electronTightColl.size(), electronTightColl[i].lorentzVec().Pt(), electronTightColl[i].eta(), electronTightColl[i].lorentzVec().Phi(), electronTightColl[i].charge(), ElectronTrkIsoDR03->at(index), ElectronEcalIsoDR03->at(index), ElectronHcalIsoDR03->at(index), ElectronPFPhotonIso03->at(index), ElectronPFChargedHadronIso03->at(index), ElectronPFNeutralHadronIso03->at(index), electronTightColl[i].dxy_BS(), electronTightColl[i].dz_BS(), rhoJets);
      }	 
    }  

    if (electronLooseColl.size() > 0 && jetVetoColl.size()>0) {
      for (UInt_t i=0; i<electronLooseColl.size(); i++) {
        index=electronLooseColl[i].ilepton();
        h_electronsLoose->Fill(weight, (Int_t) electronLooseColl.size(), electronLooseColl[i].lorentzVec().Pt(), electronLooseColl[i].eta(), electronLooseColl[i].lorentzVec().Phi(), electronLooseColl[i].charge(), ElectronTrkIsoDR03->at(index), ElectronEcalIsoDR03->at(index), ElectronHcalIsoDR03->at(index), ElectronPFPhotonIso03->at(index), ElectronPFChargedHadronIso03->at(index), ElectronPFNeutralHadronIso03->at(index), electronLooseColl[i].dxy_BS(), electronLooseColl[i].dz_BS(), rhoJets);
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

    if ( ZandWveto(electronLooseColl, PFMETType01XYCor->at(0), PFMETPhiType01XYCor->at(0)) ) continue;


    ///// FAKE RATES /////

    dr=-999.9;
    
    if (electronLooseColl.size() == 1 && electronTightColl.size() == 1  && jetVetoColl.size() >= 1) {
      for (UInt_t iii=0; iii<electronTightColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetVetoColl.size(); yyy++) {
	 
	  dr = electronTightColl[iii].lorentzVec().DeltaR( jetVetoColl[yyy].lorentzVec() );
	  if (dr > 1.0) {
	    h_nEvents->Fill(fabs(electronTightColl[iii].eta()),electronTightColl[iii].lorentzVec().Pt(), weight);
 
            if (electronTightColl[iii].lorentzVec().Pt()<=35 || true) {
              h_nVertex1->Fill(numberVertices, weight);
              index=electronTightColl[iii].ilepton();
              h_TLnum->Fill(weight, (Int_t) electronTightColl.size(), electronTightColl[iii].lorentzVec().Pt(), electronTightColl[iii].eta(), electronTightColl[iii].lorentzVec().Phi(), electronTightColl[iii].charge(), ElectronTrkIsoDR03->at(index), ElectronEcalIsoDR03->at(index), ElectronHcalIsoDR03->at(index), ElectronPFPhotonIso03->at(index), ElectronPFChargedHadronIso03->at(index), ElectronPFNeutralHadronIso03->at(index), electronTightColl[iii].dxy_BS(), electronTightColl[iii].dz_BS(), rhoJets);
            }
	    
	    goto fine;
	  }
        }
      }
    }
    fine:
    
    if (debug) cout<< "denominator" <<endl;

    if (electronLooseColl.size() == 1 && jetVetoColl.size() >= 1) {
      for (UInt_t iii=0; iii<electronLooseColl.size(); iii++) {
	for (UInt_t yyy=0; yyy<jetVetoColl.size(); yyy++) {
	  
	  dr = electronLooseColl[iii].lorentzVec().DeltaR( jetVetoColl[yyy].lorentzVec() );
	  if (dr > 1.0) {
	    h_nEventsFO->Fill(fabs(electronLooseColl[iii].eta()),electronLooseColl[iii].lorentzVec().Pt(), weight);
    
            if (electronLooseColl[iii].lorentzVec().Pt()<=35 || true) {
              h_nVertex0->Fill(numberVertices, weight);
              index=electronLooseColl[iii].ilepton();
              h_TLden->Fill(weight, (Int_t) electronLooseColl.size(), electronLooseColl[iii].lorentzVec().Pt(), electronLooseColl[iii].eta(), electronLooseColl[iii].lorentzVec().Phi(), electronLooseColl[iii].charge(), ElectronTrkIsoDR03->at(index), ElectronEcalIsoDR03->at(index), ElectronHcalIsoDR03->at(index), ElectronPFPhotonIso03->at(index), ElectronPFChargedHadronIso03->at(index), ElectronPFNeutralHadronIso03->at(index), electronLooseColl[iii].dxy_BS(), electronLooseColl[iii].dz_BS(), rhoJets);
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
  outfile->cd();

  Dir = outfile->mkdir("Electrons");
  outfile->cd( Dir->GetName() );
  h_electrons->Write();
  h_electronsLoose->Write();
  h_TLden->Write();
  h_TLnum->Write();
  outfile->cd();  

  Dir = outfile->mkdir("Jets_with_veto");
  outfile->cd( Dir->GetName() );
  h_jets_veto->Write();
  outfile->cd();

  outfile->Close();

  
}
