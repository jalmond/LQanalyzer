#include "SKTreeFiller.h"
#include <stdio.h>  

#include <stdlib.h>
#include <iostream>

#include  <numeric>

/// local includes                                                                                                                                                           
#include "Reweight.h"


using namespace snu;
using namespace std;


SKTreeFiller::SKTreeFiller() :Data() {
  
  TString fitParametersFile = "";


  std::vector<double> pileupMC = GetWeights("2016_25ns_Moriond17MC") ;
  std::vector<double> pileupRD = GetWeights("Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON");
  std::vector<double> pileupUp = GetWeights("Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_Up");
  std::vector<double> pileupDn = GetWeights("Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_Dn");

  std::vector<float> pileupMCTmp;
  std::vector<float> pileupRDTmp;
  std::vector<float> pileupUpTmp, pileupDnTmp;


  const double sumWMC = std::accumulate(pileupMC.begin(), pileupMC.end(), 0.);
  const double sumWRD = std::accumulate(pileupRD.begin(), pileupRD.end(), 0.);
  const double sumWUp = std::accumulate(pileupUp.begin(), pileupUp.end(), 0.);
  const double sumWDn = std::accumulate(pileupDn.begin(), pileupDn.end(), 0.);


  for ( int i=0, n=min(pileupMC.size(), pileupRD.size()); i<n; ++i )
    {
      pileupMCTmp.push_back(pileupMC[i]/sumWMC);
      pileupRDTmp.push_back(pileupRD[i]/sumWRD);
      pileupUpTmp.push_back(pileupUp[i]/sumWUp);
      pileupDnTmp.push_back(pileupDn[i]/sumWDn);
    }


  reweightPU = new Reweight(pileupMCTmp, pileupRDTmp);
  reweightPU_up = new Reweight(pileupMCTmp, pileupUpTmp);
  reweightPU_down = new Reweight(pileupMCTmp, pileupDnTmp);

};


SKTreeFiller::~SKTreeFiller() {
  delete reweightPU;
  delete reweightPU_up;
  delete reweightPU_down;

};


bool SKTreeFiller::SkipTrigger(TString tname){
  
  m_logger << DEBUG << "Trigger: " << tname << LQLogger::endmsg;  
  /// Remove extra unnecisary  triggers (from v7-6-4+ this will not be needed))

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
  

  /// trignames should only be empty id user is running on SKFlat and not SKTreeMaker. In this case all triggers are used 
  if(trignames.size() == 0 ){
    for (UInt_t i=0; i< HLT_TriggerName->size(); i++) {
      std::string tgname = HLT_TriggerName->at(i);
      vHLTInsideDatasetTriggerNames.push_back(tgname);
    }
  }

  
  /// vtrigname is vector of ALL triggers in SKFlat
  for (UInt_t i=0 ; i< HLT_TriggerName->size(); i++) {
    // trignames is vector of trigger names that we want to store in SKTrees
    // trigname contains names substrings X (where X is for example "HLT_mu") and we store all triggers that start with X

    
    std::string tgname = HLT_TriggerName->at(i);


    for (std::vector<TString>::reverse_iterator it (trignames.end());
	 it != std::vector<TString>::reverse_iterator (trignames.begin());
	 ++it) {

      TString tmpHLT = HLT_TriggerName->at(i);
      if ( tmpHLT.BeginsWith(*it)){
	
	vHLTInsideDatasetTriggerNames.push_back(tgname);
	
	// if trigger is accepted break from loop
	break;
      }
    } // end of trignames loop
  }// loop of all triggers  
  
  ktrigger.SetHLTInsideDatasetTriggerNames(vHLTInsideDatasetTriggerNames);
    
  m_logger << DEBUG << "Filled  trigger Info" << LQLogger::endmsg;

  return ktrigger;
  
}

snu::KEvent SKTreeFiller::GetEventInfo(){
 
  snu::KEvent kevent;

  if(!LQinput){
    kevent = *k_inputevent;
    return kevent;
  }

  /// not added yet
  /*
    Int_t           nTotal;
  Int_t           PVtrackSize;
  Double_t        PVchi2;
  Double_t        PVndof;
  Double_t        PVnormalizedChi2;
  Double_t        genWeight_alphaQCD;
  Double_t        genWeight_alphaQED;
  
  */


  m_logger << DEBUG << "Filling Event Info" << LQLogger::endmsg;
  
  // New variable to set catversion. Add this to flat ntuples for next iteration

  /// type 1
  // type 1 + phi corrections
  double met_type1xy = pfMET_Type1_PhiCor_pt;
  double phi_type1xy =  pfMET_Type1_PhiCor_phi;
  
  
  /// Default MET is now xy shifted typ1
  if(IsData)  {
    kevent.SetMET(snu::KEvent::pfmet, met_type1xy, phi_type1xy, pfMET_Type1_PhiCor_SumEt);
    kevent.SetPFMETx(pfMET_Type1_PhiCor_pt * TMath::Cos(pfMET_Type1_PhiCor_phi));
    kevent.SetPFMETy(pfMET_Type1_PhiCor_pt* TMath::Sin(pfMET_Type1_PhiCor_phi));
    
    /// Also for completness store type1 without phi corrections
    kevent.SetPFMETType1x(pfMET_Type1_pt*TMath::Cos(pfMET_Type1_phi));
    kevent.SetPFMETType1y(pfMET_Type1_pt*TMath::Sin(pfMET_Type1_phi));
    kevent.SetPFMETType1SumEt(pfMET_Type1_SumEt);
    
  }
    /// set unsmeared met variables
  kevent.SetPFRawMETx(pfMET_pt * TMath::Cos(pfMET_phi));
  kevent.SetPFRawMETx(pfMET_pt*  TMath::Sin(pfMET_phi));

  kevent.SetPFMETType1Unsmearedx(pfMET_Type1_pt*TMath::Cos(pfMET_Type1_phi));
  kevent.SetPFMETType1Unsmearedy(pfMET_Type1_pt*TMath::Sin(pfMET_Type1_phi));
  kevent.SetPFMETType1xyUnsmearedx(pfMET_Type1_PhiCor_pt*TMath::Cos(pfMET_Type1_PhiCor_phi));;
  kevent.SetPFMETType1xyUnsmearedy(pfMET_Type1_PhiCor_pt*TMath::Sin(pfMET_Type1_PhiCor_phi));
    
  m_logger << DEBUG << "Filling Event Info [2]" << LQLogger::endmsg;
  /// Since some versions of catuples have no metNoHF due to bug in met code 
  
  if(PDFWeights_Error){
    if(PDFWeights_Error->size() > 0){
      std::vector<double>* w1= PDFWeights_Error;
      std::vector<double> w1store;

      for(unsigned int i=0; i < w1->size(); i++){
	w1store.push_back(w1->at(i));
      }
      kevent.SetPDFWeights(w1store);
    }
  }
  if(PDFWeights_Scale){
    if(PDFWeights_Scale->size() > 0){
      std::vector<double>* w1= PDFWeights_Scale;
      std::vector<double> w1store;

      for(unsigned int i=0; i < w1->size(); i++){
        w1store.push_back(w1->at(i));
      }

      kevent.SetScaleWeights(w1store);
    }
  }

  if(PDFWeights_AlphaS){
    if(PDFWeights_AlphaS->size() > 0){
      std::vector<double>* w1= PDFWeights_AlphaS;
      std::vector<double> w1store;

      for(unsigned int i=0; i < w1->size(); i++){
        w1store.push_back(w1->at(i));
      }

      kevent.SetAlphaSWeights(w1store);
    }
  }
  
  
  if(!IsData){
    float jpx(0.), jpy(0.), sjpx(0.), sjpy(0.), sjpxup(0.), sjpxdown(0.),sjpyup(0.), sjpydown(0.) ;
    
    /// only smear jets not close to leptons (use top projection id)
    for(unsigned int ij = 0 ; ij < jet_pt->size(); ij++){
      bool close_to_lepton(false);
      if(jet_pt->at(ij) < 10.) continue;
      for(unsigned int im=0; im < muon_pt->size(); im++){
	if(muon_pt->at(im) < 10.) continue;
	if(fabs(muon_eta->at(im)) > 2.5) continue;
	// find full definition for 13 TeV
        double dr = sqrt( pow(fabs( jet_eta->at(ij) - muon_eta->at(im)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( jet_phi->at(ij) - muon_phi->at(im))),2.0));
	if(dr < 0.4){
	  close_to_lepton=true;
	}
      }
      for(unsigned int iel=0; iel < electron_pt->size(); iel++){
	if(electron_pt->at(iel) < 10.) continue;
        if(fabs(electron_eta->at(iel)) > 2.5) continue;
        double dr = sqrt( pow(fabs( jet_eta->at(ij) - electron_eta->at(iel)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( jet_phi->at(ij) - electron_phi->at(iel))),2.0));
        if(dr < 0.4){
          close_to_lepton=true;
        }
      }
      
      if(close_to_lepton) continue;
      
      float jet_px = jet_pt->at(ij) *TMath::Cos(jet_phi->at(ij)); 
      float jet_py = jet_pt->at(ij) *TMath::Sin(jet_phi->at(ij));
      jpx +=  jet_px;
      jpy +=  jet_py;
      
      if(!IsData){
	sjpx +=  jet_smearedRes->at(ij) *jet_px;
	sjpy +=  jet_smearedRes->at(ij) *jet_py;
      }
      else{
	sjpx +=  jet_px;
        sjpy +=  jet_py;
      }
      sjpxup +=  jet_smearedResUp->at(ij) *jet_px;
      sjpyup +=  jet_smearedResUp->at(ij) *jet_py;
      
      sjpxdown +=  jet_smearedResDown->at(ij) *jet_px;
      sjpydown +=  jet_smearedResDown->at(ij) *jet_py;

    }

    // met_jetRes_Px_up ==met_Px since no smearing is applied in miniaods -> cattools
    float met_x  = pfMET_Type1_PhiCor_pt*TMath::Cos(pfMET_Type1_PhiCor_phi)  +  jpx - sjpx;
    float met_y  = pfMET_Type1_PhiCor_pt*TMath::Sin(pfMET_Type1_PhiCor_phi)  +  jpy - sjpy;
    float met_newpt = sqrt(met_x*met_x+ met_y*met_y);
    float met_newphi = TMath::ATan2(met_y,met_x);
    
    kevent.SetMET(snu::KEvent::pfmet,  met_newpt,met_newphi, pfMET_Type1_PhiCor_SumEt);  
    kevent.SetPFMETx(met_x);
    kevent.SetPFMETy(met_y);

    /// correct MET for jets smearing
    float type1_met_x  = pfMET_Type1_pt * TMath::Cos(pfMET_Type1_phi)  +  jpx - sjpx;
    float type1_met_y  = pfMET_Type1_pt * TMath::Sin(pfMET_Type1_phi)  +   jpy - sjpy;
    
    kevent.SetPFMETType1x(type1_met_x);
    kevent.SetPFMETType1y(type1_met_y);		  
    kevent.SetPFMETType1SumEt(pfMET_Type1_SumEt);           

    /// Fix met phi 
    float met_x_jer_up  = pfMET_Type1_PhiCor_pt*TMath::Cos(pfMET_Type1_PhiCor_phi) +  jpx - sjpxup;
    float met_y_jer_up   = pfMET_Type1_PhiCor_pt*TMath::Sin(pfMET_Type1_PhiCor_phi)  +  jpy - sjpyup;
    float met_newpt_jerup = sqrt(met_x_jer_up*met_x_jer_up+ met_y_jer_up*met_y_jer_up);

    float met_x_jer_down   = pfMET_Type1_PhiCor_pt*TMath::Cos(pfMET_Type1_PhiCor_phi)  +  jpx - sjpxdown;
    float met_y_jer_down  = pfMET_Type1_PhiCor_pt*TMath::Sin(pfMET_Type1_PhiCor_phi)    +  jpy -sjpydown;
    float met_newpt_jerdown = sqrt(met_x_jer_down*met_x_jer_down+ met_y_jer_down*met_y_jer_down);

      
    kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::JetRes,     met_newpt_jerup);
    kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::JetRes,     met_newpt_jerdown);
    
  }
  

  m_logger << DEBUG << "Filling Event Info [3]" << LQLogger::endmsg;
  

  /*

      // ---- members for MET corrections ----
      enum METUncertainty {
       JetResUp=0, JetResDown=1, JetEnUp=2, JetEnDown=3,
       MuonEnUp=4, MuonEnDown=5, ElectronEnUp=6, ElectronEnDown=7,
       TauEnUp=8, TauEnDown=9, UnclusteredEnUp=10, UnclusteredEnDown=11,
       PhotonEnUp=12, PhotonEnDown=13, NoShift=14, METUncertaintySize=15,
       JetResUpSmear=16, JetResDownSmear=17, METFullUncertaintySize=18
      };
  */
  
  kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::MuonEn,     pfMET_Type1_PhiCor_pt_shifts->at(4));
  kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::MuonEn,     pfMET_Type1_PhiCor_pt_shifts->at(5));
  kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::ElectronEn, pfMET_Type1_PhiCor_pt_shifts->at(6));
  kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::ElectronEn, pfMET_Type1_PhiCor_pt_shifts->at(7));
  kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::Unclustered, pfMET_Type1_PhiCor_pt_shifts->at(10));
  kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::Unclustered, pfMET_Type1_PhiCor_pt_shifts->at(11));
  kevent.SetPFSumETShift(snu::KEvent::up,     snu::KEvent::Unclustered, pfMET_Type1_PhiCor_SumEt_shifts->at(10));
  kevent.SetPFSumETShift(snu::KEvent::down,   snu::KEvent::Unclustered, pfMET_Type1_PhiCor_SumEt_shifts->at(11));
  kevent.SetPFMETShift  (snu::KEvent::up,     snu::KEvent::JetEn,    pfMET_Type1_PhiCor_pt_shifts->at(2));
																       								 
  kevent.SetPFMETShift  (snu::KEvent::down,   snu::KEvent::JetEn,    pfMET_Type1_PhiCor_pt_shifts->at(3));
  kevent.SetPFSumETShift(snu::KEvent::up,     snu::KEvent::JetEn,    pfMET_Type1_PhiCor_SumEt_shifts->at(2)); 
  kevent.SetPFSumETShift(snu::KEvent::down,   snu::KEvent::JetEn,     pfMET_Type1_PhiCor_SumEt_shifts->at(3));

  
  m_logger << DEBUG << "Filling Event Info [4]" << LQLogger::endmsg;
  
  /// Filling event variables
    
  kevent.SetIsData(IsData);
  kevent.SetRunNumber(run);
  kevent.SetEventNumber(event);
  kevent.SetLumiSection(lumi);
  kevent.SetRho(Rho);
  if(!IsData){
    double pu_weight = reweightPU->GetWeight(double(nPV));
    double pu_weight_up = reweightPU_up->GetWeight(double(nPV));
    double pu_weight_down = reweightPU_down->GetWeight(double(nPV));
    
    kevent.SetPUWeight(snu::KEvent::central,pu_weight); // JSKIM                                                                                                                                     
    kevent.SetPUWeight(snu::KEvent::down,pu_weight_down);
    kevent.SetPUWeight(snu::KEvent::up,  pu_weight_up);
  }


  kevent.SetGenId(genWeight_id1, genWeight_id2);
  kevent.SetGenX(genWeight_X1, genWeight_X2);
  kevent.SetGenQ(genWeight_Q);
  if(gen_weight > 0.) kevent.SetWeight(1.);
  else kevent.SetWeight(-1.);
  
  kevent.SetVertexInfo(vertex_X, vertex_Y, vertex_Z,0. );
  
  kevent.SetPileUpInteractionsTrue(nPileUp); 
  kevent.SetNVertices(nPV);
  kevent.SetIsGoodEvent(Flag_goodVertices);

  /// MET filter cuts/checks
  kevent.SetPassEcalDeadCellTriggerPrimitiveFilter(Flag_EcalDeadCellTriggerPrimitiveFilter);
  kevent.SetPassHBHENoiseFilter(Flag_HBHENoiseFilter);
  kevent.SetPassHBHENoiseIsoFilter(Flag_HBHENoiseIsoFilter);
  kevent.SetPassBadEESupercrystalFilter(Flag_eeBadScFilter);
  kevent.SetPassEEBadCalibFilterTight(Flag_ecalBadCalibFilter);
  kevent.SetPassSuperHalo2016Filter(Flag_globalSuperTightHalo2016Filter);
  kevent.SetPassBadChargedCandidateFilter(Flag_BadChargedCandidateFilter);
  kevent.SetPassBadPFMuonFilter(Flag_BadPFMuonFilter);
  


  return kevent;
}


std::vector<KPhoton> SKTreeFiller::GetAllPhotons(){

  std::vector<KPhoton> photons;

  
  if(!LQinput){
    for(std::vector<KPhoton>::iterator kit  = k_inputphotons->begin(); kit != k_inputphotons->end(); kit++){
      photons.push_back(*kit);
    }
    return photons;
  }

  m_logger << DEBUG << "Filing photon Info " << LQLogger::endmsg;

  for (UInt_t iph=0; iph< photon_eta->size(); iph++) {
    if(photon_pt->at(iph) != photon_pt->at(iph)) continue;
    KPhoton ph;


    m_logger << DEBUG << "Filing photon Info " << photon_passLooseID->size() << LQLogger::endmsg;

    ph.SetPtEtaPhiM(photon_pt->at(iph),photon_eta->at(iph), photon_phi->at(iph),0.); // JSKIM 

    ph.SetIsLoose(photon_passLooseID->at(iph));
    ph.SetIsMedium(photon_passMediumID->at(iph));
    ph.SetIsTight(photon_passTightID->at(iph));
    ph.SetPassMVA80(photon_passMVAID_WP80->at(iph));
    ph.SetPassMVA90(photon_passMVAID_WP90->at(iph));
    ph.SetHasPixSeed(photon_hasPixelSeed->at(iph));
    ph.SetChargedHadIsoNoEA(photon_ChIso->at(iph));
    ph.SetNeutalHadIsoNoEA(photon_NhIso->at(iph));
    ph.SetPhotonIsoNoEA(photon_PhIso->at(iph));
    ph.SetChargedHadIso(photon_ChIsoWithEA->at(iph));
    ph.SetPhotonIso(photon_PhIsoWithEA->at(iph));
    ph.SetNeutalHadIso(photon_NhIsoWithEA->at(iph));
    ph.SetSigmaIetaIeta(photon_Full5x5_SigmaIEtaIEta->at(iph));
    ph.SetHoverE(photon_HoverE->at(iph));
    ph.SetSCEta(photon_scEta->at(iph));
    ph.SetSCPhi(photon_scPhi->at(iph));
    
    ph.SetPtUncorr(photon_ptUnCorr->at(iph));
    m_logger << DEBUG << "END"  << LQLogger::endmsg;

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

  m_logger << DEBUG << "Filling electron Info " << electron_eta->size() << LQLogger::endmsg;
  
  /*
   vector<double>  *electron_etaWidth;
   vector<double>  *electron_phiWidth;
   vector<double>  *electron_dEtaIn;
   vector<double>  *electron_sigmaIEtaIEta;
   vector<double>  *electron_fbrem;
   vector<double>  *electron_eOverP;
   
   vector<double>  *electron_r9;
   vector<double>  *electron_scEnergy;
   vector<double>  *electron_scPreEnergy;
   vector<double>  *electron_scRawEnergy;
   vector<double>  *electron_scEt;

   vector<double>  *electron_E15;
     vector<double>  *electron_E25;
   vector<double>  *electron_E55;

  vector<bool>    *electron_passMVAID_noIso_WP80;
   vector<bool>    *electron_passMVAID_noIso_WP90;
   vector<bool>    *electron_passMVAID_iso_WP80;
   vector<bool>    *electron_passMVAID_iso_WP90;*/


  vector<int> matched_truth;
  for (UInt_t iel=0; iel< electron_eta->size(); iel++) {
    
    if(electron_pt->at(iel) != electron_pt->at(iel))    continue;
    
    KElectron el;

    /// Kinematic Variables
    el.SetPtEtaPhiE(electron_pt->at(iel),electron_eta->at(iel), electron_phi->at(iel),electron_Energy->at(iel));

    el.SetElIDVariables(
			      electron_Full5x5_SigmaIEtaIEta->at(iel),
			      electron_dEtaInSeed->at(iel),
			      electron_dPhiIn->at(iel),
			      electron_HoverE->at(iel),
			      electron_InvEminusInvP->at(iel)
			      );


    //    el.SetGSF(electron_gsfpt->at(iel), electron_gsfeta->at(iel),electron_gsfphi->at(iel),electron_gsfm->at(iel));

    el.SetSCEta(electron_scEta->at(iel));
    el.SetSCPhi(electron_scPhi->at(iel));
   
    el.Setdz( electron_dz->at(iel));

    el.SetIP2D(electron_dxyVTX->at(iel));

    double dB3D  = electron_3DIPVTX->at(iel);
    double edB3D = electron_3DIPerrVTX->at(iel);
    double sip3D = edB3D>0?dB3D/edB3D:0.0;


    el.SetIP3D(dB3D);
    el.SetSIP3D(sip3D);

    
    el.SetMVAIso(electron_MVAIso->at(iel) );
    el.SetMVANonIso(electron_MVAIso->at(iel) );


    el.SetPFChargedHadronIso(0.3, electron_puChIso03->at(iel));
    el.SetPFPhotonIso(0.3,electron_phIso03->at(iel));
    el.SetPFNeutralHadronIso(0.3,electron_nhIso03->at(iel));
    el.SetPFRelIsoRho(0.3,electron_RelPFIso_Rho->at(iel));
    el.SetPFRelIsoBeta(0.3,electron_RelPFIso_dBeta->at(iel));



    m_logger << DEBUG << "Filling electron_minirelIso " << LQLogger::endmsg;

    
    el.SetPFRelMiniIso(      CalcMiniIso(electron_pt->at(iel),
					 electron_chMiniIso->at(iel),
				       electron_nhMiniIso->at(iel),
				       electron_phMiniIso->at(iel),
				       electron_puChMiniIso->at(iel),
				       Rho,
				       ElectronEA(electron_eta->at(iel))));


    
    m_logger << DEBUG << "Filling electron Info 2" << LQLogger::endmsg;
    

    /// set Charge variables
    el.SetCharge(electron_charge->at(iel));
    el.SetGsfCtfScPixCharge(electron_isGsfCtfScPixChargeConsistent->at(iel));
    el.SetGsfScPixCharge(electron_isGsfScPixChargeConsistent->at(iel));
    el.SetGsfCtfCharge(electron_isGsfCtfChargeConsistent->at(iel));


    m_logger << DEBUG << "Filling electron Info 3" << LQLogger::endmsg;
    /// set conversion variables
    
    

    el.SetScaleEUp(electron_Energy_Scale_Up->at(iel));;
    el.SetScaleEDown(electron_Energy_Scale_Down->at(iel));;
    el.SetSmearEUp(electron_Energy_Smear_Up->at(iel));;
    el.SetSmearEDown(electron_Energy_Smear_Down->at(iel));;


    el.SetEnUncorr(electron_EnergyUnCorr->at(iel));
    
    /*vector<double>  *electron_etaWidth;
    vector<double>  *electron_phiWidth;
    vector<double>  *electron_dEtaIn;
    vector<double>  *electron_dEtaInSeed;
    vector<double>  *electron_dPhiIn;
    vector<double>  *electron_sigmaIEtaIEta;
    vector<double>  *electron_Full5x5_SigmaIEtaIEta;
    vector<double>  *electron_HoverE;
    vector<double>  *electron_fbrem;
    vector<double>  *electron_eOverP;
    vector<double>  *electron_InvEminusInvP;*/

    el.SetIDBit(electron_IDBit->at(iel));



    el.SetHasMatchedConvPhot(electron_passConversionVeto->at(iel));

    m_logger << DEBUG << "Filling electron Info 4" << LQLogger::endmsg;    


    //// Set Is ChargeFlip
    bool isprompt= false;
    bool from_tau = false;
    
    int mother_index=-1;
    int mother_pdgid=-1;
    int matched_index=-1;
    int mc_pdgid=-1;
    bool matched_in_Dr=false;

    int           eltype=0;
    bool conv_veto=false;
    if(k_cat_version  > 0){
      
      if(gen_pt){
	// Default deltaR setting for matching
	float min_Dr=0.1;
	/// Loop over all gen particles
	for (UInt_t it=0; it< gen_pt->size(); it++ ){
	  
	  
	  /// Requirements to make sure no crash or warnings with pt=0
	if(gen_mother_index->at(it) <= 0)continue;
	if(gen_mother_index->at(it) >= int(gen_pt->size()))continue;
	if(gen_pt->at(it) < 0.001) continue;
	

	double match_eta =electron_eta->at(iel);
	double match_pt =electron_pt->at(iel);
	double match_phi =electron_phi->at(iel);
	double dr = sqrt( pow(fabs( match_eta - gen_eta->at(it)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi - gen_phi->at(it))),2.0));

	
	
	/// check for photon conversion veto in DY/ZG                                                                                                                               
	if(fabs(gen_PID->at(it)) ==22){
	  if(gen_pt->at(it) > 10.){	
	    if(dr < 0.3){
	      if(gen_isPrompt->at(it) && gen_status->at(it) ==1) {
		conv_veto=true;
		for (UInt_t it_ph=0; it_ph< gen_pt->size(); it_ph++ ){
		  if(it==it_ph) continue;

		  // check ph is matched to q or g from matrix element (st 23)
		  if(gen_status->at(it_ph) ==23){
		    if(fabs(gen_PID->at(it_ph)) < 7 || fabs(gen_PID->at(it_ph))==21){
		      double drph = sqrt( pow(fabs(gen_eta->at(it_ph) - gen_eta->at(it)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( gen_phi->at(it_ph) - gen_phi->at(it))),2.0));
		      if(drph < 0.05) conv_veto=false;
		    }
		  }
		}
	      }	      
	    }
	  }
	}

	/// Matching using instructions on
	/// https://indico.cern.ch/event/292928/contributions/1650088/attachments/547844/755123/talk_electron_contribution.pdf
	/// 

	/// Match required to status 1 electron
	if(gen_status->at(it) != 1) continue;
	if(fabs(gen_PID->at(it)) != 11) continue;
	if(gen_pt->at(it) < 5.) continue;

	/// Check status 1 electron is not matched already to areco electron
	bool already_matched=false;
	for(unsigned int im=0; im < matched_truth.size();im++){
          if(it == unsigned(matched_truth.at(im))) already_matched=true;
        }
        //if(already_matched) continue;
	  
	if(matched_in_Dr){
	  /// This is for multiple matched status 1 el.
	  /// In case multiple status 1 electrons are matched with same mother check pt
	  if(gen_mother_index->at(it) == gen_mother_index->at(matched_index)){
	    if (dr < 0.1){
	      // in case 2+ electrons from same mother electron (conversion) also match in pt
	      if( fabs(gen_pt->at(it)-electron_pt->at(iel)) < fabs(gen_pt->at(matched_index)-electron_pt->at(iel))) matched_index=it;
	    }
	  }
	  else if ((dr < min_Dr) ){
	    
	    /// find closest match in dR to status 1
            if( (fabs(match_pt - gen_pt->at(it))/gen_pt->at(it)) < 2.) {
	      
	      matched_in_Dr=true;
	      min_Dr= dr;
	      
	      /// set index of matched status 1 electron
	      matched_index=it;
	    }
	  }
	}
	else{
	  /// first match status 1 electron
	  if ((dr < min_Dr) ){
	    if( (fabs(match_pt - gen_pt->at(it))/gen_pt->at(it)) < 2.) {
	      
	      /// find closest match in dR to status 1
	      matched_in_Dr=true;
	      min_Dr= dr;
	      
	      /// set index of matched status 1 electron
	      matched_index=it;
	    }
	  }
	}
      }// end of gen loop to find status 1 electron
	
	//cout << iel << " " << electron_pt->at(iel) << " " << electron_eta->at(iel) << " " << electron_phi->at(iel) << " " << conv_veto << endl;
	
      ///// treat case where there is a matched status 1 electron:
      //// classify into prompt:Fake:FromTau

      if(matched_in_Dr){
	/// Find closest non electron ancesteror
	float pdgid = gen_PID->at(matched_index);

	// mc_pdgid = closest matched status 1 pdgid
	mc_pdgid= int(pdgid);

	// mindex = mother index: will loop to find first non el mother
	int mindex= matched_index;

	while ( (fabs(gen_PID->at(mindex)) == 11)) {
	  pdgid = gen_PID->at(mindex);
	  mindex=gen_mother_index->at(mindex);
	}

	/// pdgid is now of electron from non electron mother
	//  mindex = index for mother of non electron ancestor
	
	if( (fabs(gen_PID->at(mindex)) == 23) || (fabs(gen_PID->at(mindex)) == 24)) {
	  /// Check if el from Z/W is CF and if it is from a photon conversion
	  
	  eltype=1;
	  int n_el_from_el=0;
	  float charge_sum=0.;
	  /// Loop over electrons: Find mother of matched status 1 and see what other daughters there are:
	  /// In case of a conversion i.e  Z->ee->eephoton->eeee the status 23 electorn decays to 3 electrons e+e+e- or e-e-e+
	  bool isthirdel_fromconv(false);
	  for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
	    if(gen_mother_index->at(itx) <= 0)continue;
	    if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
	    if(gen_pt->at(itx) < 0.001) continue;
	    if(fabs(gen_PID->at(itx)) ==11) {
	      if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) { 
		charge_sum+= gen_PID->at(itx); n_el_from_el++;
		if(n_el_from_el==3){
		  if(itx == matched_index) isthirdel_fromconv=true;
		}
		if(n_el_from_el==5){
                  if(itx == matched_index) isthirdel_fromconv=true;
		}
	      }

	    }
	  }

	  /// Set if conversion i.ei e->eee
	  /// Two methods: 
	  /// 1) check pdgid of status 1 el vs mother. if < 0 it is a converison
	  /// 2) In case closest status 1 el is not opposite charge truth check number of electrons from mother if 3 it is a conversion
	  if((gen_PID->at(matched_index)  * pdgid) < 0 )  {el.SetIsPhotonConversion(true);           eltype=2;} 
	  else  el.SetIsPhotonConversion(false);
	  
	  
	  if(!isthirdel_fromconv){
	    if(n_el_from_el ==3&& (fabs(charge_sum) == 11)) { eltype=3; el.SetIsPhotonConversion(true); }
	    if(n_el_from_el ==5&& (fabs(charge_sum) == 11)) { eltype=3; el.SetIsPhotonConversion(true); }
	  }
	  else{
	    if(pdgid * electron_charge->at(iel) > 0 )  {
	      if(n_el_from_el ==3&& (fabs(charge_sum) == 11)) { eltype=3; el.SetIsPhotonConversion(true);}
	      if(n_el_from_el ==5&& (fabs(charge_sum) == 11)) { eltype=3; el.SetIsPhotonConversion(true);}
	    }
	  }

	  /// Check if it is a chargeflip.
	  /// Either from a conversion or just reconstructed charge is wrong
	  if(pdgid * electron_charge->at(iel) > 0 )    
	    { el.SetIsChargeFlip(true); 
	      if(eltype == 2 || eltype == 3){
		if(eltype == 2) eltype=4;
		if(eltype == 3) eltype=5;
	      }
	      else eltype=6;
	    }

	  else     el.SetIsChargeFlip(false);
	  
	  mother_index=mindex;
	  mother_pdgid=gen_PID->at(mindex);
	  isprompt=true; /// means is prompt
	  
	}/// end of Z/W
	else {
	  if(gen_status->at(mindex) == 2){
	    if(fabs(gen_PID->at(mindex)) > 50) {isprompt=false; mother_pdgid=gen_PID->at(mindex); mother_index=mindex; from_tau=false;
	      eltype=7;
	      
	      if(gen_isPrompt->at(matched_index)){
		cout << "matched FAKE, but isPrompt flag??" << endl;
		cout << "------------------CF "<< endl;
	      }
	      
	    }
	    else {
	      isprompt=true;
	      mother_pdgid=gen_PID->at(mindex); mother_index=mindex; from_tau=false;
	      eltype=8;
	      
	      
	      if(fabs(gen_PID->at(mindex)) == 22){
		if(fabs(gen_PID->at(gen_mother_index->at(mindex))) > 50){
		  eltype=9;
		}
		else {
		  eltype=10;
		}
	      }
	    }
	    
	    if(fabs(gen_PID->at(mindex)) == 15){
	      eltype=11;

	      isprompt=true; mother_pdgid=gen_PID->at(mindex);  mother_index=mindex; from_tau=true;
	      // Check if el from tau  is CF
	      
	      int n_el_from_el=0;
	      float charge_sum=0.;
	      for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
		if(itx == matched_index) continue;
		if(gen_mother_index->at(itx) <= 0)continue;
		if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
		if(gen_pt->at(itx) < 0.001) continue;
		if(fabs(gen_PID->at(itx)) ==11) {
		  if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) { charge_sum+= gen_PID->at(itx); n_el_from_el++;
		  }
		}
	      }// end of truth loop to check Conv
	      if((gen_PID->at(matched_index)  * pdgid) < 0 )  el.SetIsPhotonConversion(true);
	      else  el.SetIsPhotonConversion(false);
	      if(n_el_from_el ==3&& (fabs(charge_sum) == 11))  el.SetIsPhotonConversion(true);
	      if(n_el_from_el ==5&& (fabs(charge_sum) == 11))  el.SetIsPhotonConversion(true);

	      if(fabs(gen_PID->at(gen_mother_index->at(mother_index))) > 50) {isprompt=false; eltype=12;}
	      
	      if(pdgid * electron_charge->at(iel) > 0 )     {el.SetIsChargeFlip(true); eltype=13; }
	      else     el.SetIsChargeFlip(false);
	    }
	    
	  }/// end of status 2 check
	  else {
	    /// using new method for matching: These events are set as prompt 
	    isprompt=true;mother_pdgid=-99999; mother_index=mindex; from_tau=false; 
	    eltype=14;
	    int n_el_from_eg=0;  
	    vector<KTruth> vel_tmp;
	    bool isthirdel_fromconv(false);
	    bool neutrino_invertex(false);
	    for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
	      if(gen_mother_index->at(itx) <= 0)continue;
	      if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
	      if(gen_pt->at(itx) < 0.001) continue;
	      if(fabs(gen_PID->at(itx)) ==11) {
		if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) {  n_el_from_eg++;
		  if(n_el_from_eg==3){isthirdel_fromconv=true; }
		  if(n_el_from_eg==5){isthirdel_fromconv=true; }
		  if(gen_status->at(itx) ==1){
		    KTruth truthe;
		    truthe.SetPtEtaPhiM(gen_pt->at(itx), gen_eta->at(itx), gen_phi->at(itx), gen_mass->at(itx));
		    vel_tmp.push_back(truthe);
		  }
		}
	      }
	      
	      if(fabs(gen_PID->at(itx)) ==12) {

		int index_mother_nu=gen_mother_index->at(itx);
		while (fabs(index_mother_nu) ==12){
		  index_mother_nu=gen_mother_index->at(index_mother_nu);
		}
		
		if(index_mother_nu == mindex) {
		  neutrino_invertex=true;
		}
	      }
	    } // end of truth loop to check Conv
	    
	    if(neutrino_invertex) eltype=15;

	    if(vel_tmp.size() ==2) {
	      KParticle ll = vel_tmp[0] + vel_tmp[1];
	      if(fabs(ll.M()) < 5.) eltype=16;
	    }


	    if((gen_PID->at(matched_index)  * pdgid) < 0 )  {el.SetIsPhotonConversion(true);  eltype=17;}
	    else el.SetIsPhotonConversion(false);
	    
	    if(n_el_from_eg ==3&&!isthirdel_fromconv)  {el.SetIsPhotonConversion(true); eltype=18;}
	    if(isthirdel_fromconv&&n_el_from_eg ==3){
	      if(pdgid * electron_charge->at(iel) > 0 )   {
		el.SetIsPhotonConversion(true);
		eltype=18;
	      }
	    }
	    if(isthirdel_fromconv&&n_el_from_eg ==5){
              if(pdgid * electron_charge->at(iel) > 0 )   {
                el.SetIsPhotonConversion(true);
                eltype=18;
              }
            }

	    if(pdgid * electron_charge->at(iel) > 0 )  {
	      el.SetIsChargeFlip(true);
	      if(eltype==17  || eltype == 18){
		if(eltype==17 ) eltype=19;
		if(eltype==18 ) eltype=20;
	      }
	      else eltype=21;
	    }
	    else     el.SetIsChargeFlip(false);
	    
	    /// speacial treatment for signal 

	    if( fabs(gen_PID->at(mindex))>= 9900012 &&  fabs(gen_PID->at(mindex)) < 9900025 )mother_pdgid= gen_PID->at(mindex);
	    	    
	    
	  }  // not gen status 2
	} // not Z/W daughter
      }  /// In case no status 1 electron is found : classify electron fake
      else{
	if(gen_pt){
	  for (UInt_t it=0; it< gen_pt->size(); it++ ){
	    if(gen_mother_index->at(it) <= 0)continue;
	    if(gen_mother_index->at(it) >= int(gen_pt->size()))continue;
	    if(gen_pt->at(it) < 0.001) continue;
	    
	    double match_eta =electron_eta->at(iel);
	    double match_phi =electron_phi->at(iel);
	    double dr = sqrt( pow(fabs( match_eta - gen_eta->at(it)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi - gen_phi->at(it))),2.0));
	  
	    bool already_matched=false;
	    for(unsigned int im=0; im < matched_truth.size();im++){
	      if(it == unsigned(matched_truth.at(im))) already_matched=true;
	    }
	    
	    // in coversion case  2 matched electrons to one photon
	    if(fabs(gen_PID->at(it)) != 22 && already_matched) continue;
	    
	    if (dr <0.1){
	      matched_in_Dr=true;
	      int mindex= gen_mother_index->at(it);
	      float pdgid = gen_PID->at(it);

	      
	      /// Unlikely to have mother as electron but just in case
	      while ( (fabs(gen_PID->at((mindex))) == 11)) {
		mindex=gen_mother_index->at(mindex);
	      }
	      // isprompt = false since it failed status 1 matching
	      isprompt=false;
	      /// mother index of first non electron
	      int grandmother =0;
	      if(gen_mother_index->at(mindex) > 0)grandmother=gen_PID->at(gen_mother_index->at(mindex));
	      mother_pdgid=gen_PID->at(mindex);
	      mother_index=mindex;
	      matched_index = it;
	      mc_pdgid= int(gen_PID->at(it));
	      if(fabs(pdgid) == 22) {

		if(fabs(mother_pdgid) > 50) eltype=22;
		else eltype=23;		
		
		//// This case is not a conversion
		//el.SetIsPhotonConversion(true);
		
		//if(gen_PID->at(gen_mother_index->at(it)) * electron_q->at(iel) > 0 )     el.SetIsChargeFlip(true);
		//else     el.SetIsChargeFlip(false);
		
		from_tau=false;
		break;
	      }
	      
	      else if(fabs(pdgid) == 15){
		from_tau=true;
		if(fabs(mother_pdgid) > 50) eltype=24;
		else eltype=25;
		if(fabs(mother_pdgid)==15){
		  if(fabs(grandmother) > 50) eltype=-24;
		  else eltype=-25;
		}
	      }
	      else if(fabs(pdgid) == 1){
		eltype=26;
	      }
	      else if(fabs(pdgid) == 2){
                eltype=27;
              }
	      else if(fabs(pdgid) == 3){
                eltype=28;
              }
	      else if(fabs(pdgid) == 4){
                eltype=29;
              }
	      else if(fabs(pdgid) == 5){
                eltype=30;
              }
	      else if(fabs(pdgid) == 21){
                eltype=31;
              }
	      else if(fabs(pdgid) == 211){
		eltype=32;
              }
	      else if(fabs(pdgid) == 310){
		eltype=33;
              }
	      else if(fabs(pdgid) == 431){
		eltype=34;
              }
	      else if(fabs(pdgid) == 13){
		eltype=35;
              }
	      else if(fabs(pdgid) == 311){
                eltype=36;
              }
	      else if(fabs(pdgid) > 500 && fabs(pdgid) < 600){
                eltype=37;
              }
	      else eltype=38;
	      
	    }// dr req
	  }// loop over gen vector
	}// require gen info
      }// no status 1 match
      }/// END OF TRUTH MATCHING
      
      matched_truth.push_back(matched_index);
      ///matched_index is index which matches reco muon with smallest dR
    ///- If multiple status 1 muons are matched look at closest in pt
    ///- In no status 1 is matched set as not prompt butlook for closest particle in dR
    /// - In noparticles within dR < 0.1 matched_in_Dr= false
      
      el.SetType(eltype);
    if(!matched_in_Dr){
      el.SetIsMCMatched(false);
      el.SetIsFromTau(false);
      el.SetMCMatchedPdgId(-1);
      el.SetMotherPdgId(0);
      el.SetMotherTruthIndex(-1);
      el.SetMCTruthIndex(-1);
      el.SetIsMCExternalConversion(conv_veto);
      if(conv_veto)el.SetType(40);
    }
    else{
      
      if(!isprompt){
	if((gen_isPrompt->at(matched_index) ==1 )&& (gen_status->at(matched_index) == 1)){
	  
	  //cout << "gen_istaudecayproduct =  " << gen_istaudecayproduct->at(matched_index)  << endl;
	  //cout << "gen_isprompttaudecayproduct =  " <<  gen_isprompttaudecayproduct->at(matched_index)  << endl;
	}
      }
      
      //if(gen_isprompt->at(matched_index) 
      el.SetIsMCExternalConversion(conv_veto);
      el.SetIsMCMatched(isprompt);
      el.SetIsFromTau(from_tau);
      el.SetMotherPdgId(mother_pdgid);
      el.SetMCMatchedPdgId(mc_pdgid);
      el.SetMotherTruthIndex(mother_index);
      el.SetMCTruthIndex(matched_index);
      if(gen_status->at(matched_index)==1)el.SetIsPromptFlag(gen_isPrompt->at(matched_index));
      if(conv_veto)el.SetType(40);

    }
    }
    electrons.push_back(el);
  }
  m_logger << DEBUG << "END electrons " << LQLogger::endmsg;
  std::sort( electrons.begin(), electrons.end(), isHigherPt );
  
  return electrons;
}


void SKTreeFiller::ERRORMessage(TString comment){
  
  m_logger << ERROR << "SKTreeFiller had a probleming filling " << comment << ". This variable is not present in the current SNUntuples." << LQLogger::endmsg;   
}



std::vector<KGenJet> SKTreeFiller::GetAllGenJets(){

  std::vector<KGenJet> genjets;
  if(IsData) return genjets;
  if(!LQinput){
    if(k_inputgenjets){
      for(std::vector<KGenJet>::iterator kit  = k_inputgenjets->begin(); kit != k_inputgenjets->end(); kit++){
	genjets.push_back(*kit);
      }
    }
    return genjets;
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

  m_logger << DEBUG << "Filling Jets "<< LQLogger::endmsg;


  // Not added yet
  /*vector<double>  *jet_charge;
  vector<double>  *jet_DeepFlavour_b;
  vector<double>  *jet_DeepFlavour_bb;
  vector<double>  *jet_DeepFlavour_lepb;
  vector<double>  *jet_DeepFlavour_c;
  vector<double>  *jet_DeepFlavour_uds;
  vector<double>  *jet_DeepFlavour_g;
  */


  for (UInt_t ijet=0; ijet< jet_eta->size(); ijet++) {
    KJet jet;
    if(jet_pt->at(ijet) != jet_pt->at(ijet)) continue;

    if(IsData){
      jet.SetPtEtaPhiE(jet_pt->at(ijet), jet_eta->at(ijet), jet_phi->at(ijet), jet_energy->at(ijet));
    }
    else{
      jet.SetPtEtaPhiE(jet_pt->at(ijet), jet_eta->at(ijet), jet_phi->at(ijet), jet_energy->at(ijet));

      // https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution      
      /// Measurements show that the jet energy resolution (JER) in data is worse than in the simulation and the jets in MC need to be smeared to describe the data.

      jet*= jet_smearedRes->at(ijet); // JSKIM
      jet.SetIsMCSmeared(true);
    }

    jet.SetJetPassTightID(jet_tightJetID->at(ijet));
    jet.SetJetPassTightLepVetoID(jet_tightLepVetoJetID->at(ijet));
    jet.SetJetPileupIDMVA(jet_PileupJetId->at(ijet));

    if(jet_PileupJetId){ 
      if(std::abs(jet_eta->at(ijet)) < 2.6){
	if(jet_PileupJetId->at(ijet) > 0.3) jet.SetJetPileupIDLooseWP(true);
	else jet.SetJetPileupIDLooseWP(false);
	if(jet_PileupJetId->at(ijet) > 0.7) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
	if(jet_PileupJetId->at(ijet) > 0.9)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
      else{
	if(jet_PileupJetId->at(ijet) > -0.55) jet.SetJetPileupIDLooseWP(true);
        else jet.SetJetPileupIDLooseWP(false);
        if(jet_PileupJetId->at(ijet) > -0.3) jet.SetJetPileupIDMediumWP(true);
	else jet.SetJetPileupIDMediumWP(false);
        if(jet_PileupJetId->at(ijet) > -0.1)jet.SetJetPileupIDTightWP(true);
	else jet.SetJetPileupIDTightWP(false);
      }
    }
    
    
    /// BTAG variables
    jet.SetBTagInfo(snu::KJet::CSVv2, jet_CSVv2->at(ijet));
    jet.SetBTagInfo(snu::KJet::DeepCSV, jet_DeepCSV->at(ijet));   
    jet.SetCTagInfo(snu::KJet::CCvsLT,jet_CvsL->at(ijet));
    jet.SetCTagInfo(snu::KJet::CCvsBT, jet_CvsB->at(ijet));
    jet.SetCTagInfo(snu::KJet::DeepCCvsLT,jet_DeepCvsL->at(ijet));
    jet.SetCTagInfo(snu::KJet::DeepCCvsBT, jet_DeepCvsB->at(ijet));

    
    // flavour
    jet.SetJetPartonFlavour(jet_partonFlavour->at(ijet));
    jet.SetJetHadronFlavour(jet_hadronFlavour->at(ijet));    
    jet.SetJetPartonPdgId(jet_partonPdgId->at(ijet));
    
    jet.SetJetChargedEmEF(jet_chargedEmEnergyFraction->at(ijet));
    jet.SetJetNeutralEmEF(jet_neutralEmEnergyFraction->at(ijet));
    jet.SetJetChargedHadEF(jet_chargedHadronEnergyFraction->at(ijet));
    jet.SetJetNeutralHadEF(jet_neutralHadronEnergyFraction->at(ijet));
    jet.SetJetChargedMultiplicity(jet_chargedMultiplicity->at(ijet));
    jet.SetJetNeutralMultiplicity(jet_neutralMultiplicity->at(ijet));

    m_logger << DEBUG << "Filling Jets 2"<< LQLogger::endmsg;


    /// JEC and uncertainties
    jet.SetJetScaledDownEnergy(jet_shiftedEnDown->at(ijet));
    jet.SetJetScaledUpEnergy(jet_shiftedEnUp->at(ijet));
    if(!IsData){
      jet.SetSmearedResDown(jet_smearedResDown->at(ijet));
      jet.SetSmearedResUp(jet_smearedResUp->at(ijet));
      jet.SetSmearedRes(jet_smearedRes->at(ijet));
    }
    jet.SetL1JetCorr(jet_JECL1FastJet->at(ijet));
    jet.SetFullJetCorr(jet_JECFull->at(ijet));

    m_logger << DEBUG << "Filling Jets 3"<< LQLogger::endmsg;

    jet.SetJetArea(jet_area->at(ijet));
    jet.SetJetMass(jet_m->at(ijet));

    jets.push_back(jet);
  }// end of jet 
  
  
  std::sort( jets.begin(), jets.end(), isHigherPt );
  
  m_logger << DEBUG << "PFJet size = " << jets.size() << LQLogger::endmsg;
  return jets;
}



std::vector<KFatJet> SKTreeFiller::GetAllFatJets(){

  std::vector<KFatJet> fatjets;

  if(!LQinput){

    for(std::vector<KFatJet>::iterator kit  = k_inputfatjets->begin(); kit != k_inputfatjets->end(); kit++){
      fatjets.push_back(*kit);
    }
    return fatjets;
  }

  /*
  vector<double>  *fatjet_charge;
  */


  m_logger << DEBUG << "PFFatJet" << LQLogger::endmsg;

  for (UInt_t ijet=0; ijet< fatjet_eta->size(); ijet++) {
    KFatJet jet;
    if(fatjet_pt->at(ijet) != fatjet_pt->at(ijet)) continue;
    jet.SetPtEtaPhiE(fatjet_pt->at(ijet), fatjet_eta->at(ijet), fatjet_phi->at(ijet), fatjet_energy->at(ijet));

    jet.SetJetPassTightID(fatjet_tightJetID->at(ijet));
    jet.SetJetPassTightLepVetoID(fatjet_tightLepVetoJetID->at(ijet));


    jet.SetBTagInfo(snu::KFatJet::CSVv2, fatjet_CSVv2->at(ijet));

    // flavour                                                                                                                                                                                                                                                                                                  
    jet.SetJetPartonFlavour(fatjet_partonFlavour->at(ijet));
    jet.SetJetHadronFlavour(fatjet_hadronFlavour->at(ijet));
    jet.SetJetPartonPdgId(fatjet_partonPdgId->at(ijet));

    jet.SetJetChargedEmEF(fatjet_chargedEmEnergyFraction->at(ijet));
    jet.SetJetNeutralEmEF(fatjet_neutralEmEnergyFraction->at(ijet));
    jet.SetJetChargedHadEF(fatjet_chargedHadronEnergyFraction->at(ijet));
    jet.SetJetNeutralHadEF(fatjet_neutralHadronEnergyFraction->at(ijet));
    jet.SetJetChargedMultiplicity(fatjet_chargedMultiplicity->at(ijet));
    jet.SetJetNeutralMultiplicity(fatjet_neutralMultiplicity->at(ijet));


    jet.SetJetScaledDownEnergy(fatjet_shiftedEnDown->at(ijet));
    jet.SetJetScaledUpEnergy(fatjet_shiftedEnUp->at(ijet));

    if(!IsData){
	jet.SetSmearedResDown(fatjet_smearedResDown->at(ijet));
	jet.SetSmearedResUp(fatjet_smearedResUp->at(ijet));
	jet.SetSmearedRes(fatjet_smearedRes->at(ijet));
      }

    jet.SetTau1(fatjet_puppi_tau1->at(ijet));
    jet.SetTau2(fatjet_puppi_tau2->at(ijet));
    jet.SetTau3(fatjet_puppi_tau3->at(ijet));
    jet.SetTau4(fatjet_puppi_tau4->at(ijet));

    jet.SetSoftDropMass(fatjet_softdropmass->at(ijet));    
    jet.SetJetArea(fatjet_area->at(ijet));

      
    jet.SetJetMass(fatjet_m->at(ijet));

    fatjets.push_back(jet);
  }// end of jet                                                   
  std::sort( fatjets.begin(), fatjets.end(), isHigherPt );

  m_logger << DEBUG << "PFJet size = " << fatjets.size() << LQLogger::endmsg;
  return fatjets;
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

  vector<int> matched_truth;
  for (UInt_t ilep=0; ilep< muon_eta->size(); ilep++) {
    KMuon muon;
    if(muon_pt->at(ilep) != muon_pt->at(ilep)) continue;
    m_logger << DEBUG << "Filling global pt/eta ... " << LQLogger::endmsg;

    
    muon.SetTypeBit(muon_TypeBit->at(ilep));
    muon.SetIDBit(muon_IDBit->at(ilep));
    
    
    muon.SetPtEtaPhiM(muon_pt->at(ilep), muon_eta->at(ilep),muon_phi->at(ilep), muon_mass->at(ilep));

    
    muon.SetRochPt(muon_pt->at(ilep)*muon_roch_sf->at(ilep));
    muon.SetRochSF(muon_roch_sf->at(ilep));
    muon.SetRochSFUp(muon_roch_sf_up->at(ilep));
    

    muon.SetCharge(muon_charge->at(ilep));
     
    m_logger << DEBUG << "Filling ms pt/eta ... " << LQLogger::endmsg;
 

    muon.SetTrkIso(muon_trkiso->at(ilep));
    muon.SetHCalIso(muon_hcaliso->at(ilep));
    muon.SetECalIso(muon_ecaliso->at(ilep));

    muon.SetRelIso(0.3,CalcPFIso(muon_PfChargedHadronIsoR03->at(ilep), muon_PfNeutralHadronIsoR03->at(ilep), muon_PfGammaIsoR03->at(ilep), muon_PFSumPUIsoR03->at(ilep))/muon_pt->at(ilep));
    muon.SetRelIso(0.4,CalcPFIso(muon_PfChargedHadronIsoR04->at(ilep), muon_PfNeutralHadronIsoR04->at(ilep), muon_PfGammaIsoR04->at(ilep), muon_PFSumPUIsoR04->at(ilep))/muon_pt->at(ilep));

    muon.SetRelMiniIso(      CalcMiniIso(muon_pt->at(ilep),
					 muon_PfChargedHadronMiniIso->at(ilep), 
					 muon_PfNeutralHadronMiniIso->at(ilep), 
					 muon_PfGammaMiniIso->at(ilep), 
					 muon_PFSumPUMiniIso->at(ilep),
					 Rho,
					 EA(muon_eta->at(ilep))));
    

    muon.SetMiniAODPt(muon_pt->at(ilep));
    muon.SetMiniAODRelIso(0.3,CalcPFIso(muon_PfChargedHadronIsoR03->at(ilep), muon_PfNeutralHadronIsoR03->at(ilep), muon_PfGammaIsoR03->at(ilep), muon_PFSumPUIsoR03->at(ilep))/muon_pt->at(ilep));
    muon.SetMiniAODRelIso(0.4,CalcPFIso(muon_PfChargedHadronIsoR04->at(ilep), muon_PfNeutralHadronIsoR04->at(ilep), muon_PfGammaIsoR04->at(ilep), muon_PFSumPUIsoR04->at(ilep))/muon_pt->at(ilep));
    muon.SetIsRochesterCorrected(false);
    
    muon.Setdz(muon_dzVTX->at(ilep));
    muon.SetIP2D(muon_dxyVTX->at(ilep));

    double dB3D  = muon_3DIPVTX->at(ilep);
    double edB3D = muon_3DIPerrVTX->at(ilep);
    double sip3D = edB3D>0?dB3D/edB3D:0.0; 

    muon.SetIP3D(dB3D);    
    muon.SetSIP3D(sip3D);


    //// chi2
    muon.SetGlobalchi2( muon_normchi->at(ilep));
        
    /// hits
    muon.SetValidHits( muon_validhits->at(ilep));
    muon.SetPixelValidHits( muon_pixelHits->at(ilep));
    muon.SetValidStations( muon_matchedstations->at(ilep));
    muon.SetLayersWithMeasurement ( muon_trackerLayers->at(ilep));
    
    //muon.SetMCMatched(muon_matched->at(ilep));


    muon.SetTrackVx(muon_vx->at(ilep));
    muon.SetTrackVy(muon_vy->at(ilep));
    muon.SetTrackVz(muon_vz->at(ilep));

    //// Set Is ChargeFlip
    bool isprompt= false;
    bool from_tau = false;

    int mother_index=-1;
    int mother_pdgid=-1;
    int matched_index=-1;
    int mc_pdgid=-1;
    bool matched_in_Dr=false;
    
    int          mutype=0;

    if(k_cat_version > 0){

    if(gen_pt){
      float min_Dr=0.1;

      for (UInt_t it=0; it< gen_pt->size(); it++ ){
        if(gen_mother_index->at(it) <= 0)continue;
        if(gen_mother_index->at(it) >= int(gen_pt->size()))continue;
	
	if(gen_pt->at(it) < 5.) continue;

	double match_pt =muon_pt->at(ilep);
	double match_eta =muon_eta->at(ilep);
	double match_phi =muon_phi->at(ilep);
	double dr = sqrt( pow(fabs( match_eta - gen_eta->at(it)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi - gen_phi->at(it))),2.0));
	/// Matching using instructions on
        /// https://indico.cern.ch/event/292928/contributions/1650088/attachments/547844/755123/talk_electron_contribution.pdf
        ///

	bool already_matched=false;
	for(unsigned int im=0; im < matched_truth.size();im++){
	  if(it == unsigned(matched_truth.at(im))) already_matched=true;
	}

	///	if(already_matched) continue;

        /// Match requires to status 1 muon
        if(gen_status->at(it) != 1) continue;
        if(fabs(gen_PID->at(it)) != 13) continue;
	
	if(matched_in_Dr){
	  if(gen_mother_index->at(it) == gen_mother_index->at(matched_index)){
	    if (dr < 0.1){
	      // in case 2+ electrons from same mother electron (conversion) also match in pt
	      if( fabs(gen_pt->at(it)-muon_pt->at(ilep)) < fabs(gen_pt->at(matched_index)-muon_pt->at(ilep))) matched_index=it;
	    }
	  }
	  else   if (dr < min_Dr){
	    /// find closest match in dR to status 1
	    if( (fabs(match_pt - gen_pt->at(it))/gen_pt->at(it)) < 2.) {
	      matched_in_Dr=true;
	      min_Dr= dr;
	      /// set index of matched status 1 muon
	      matched_index=it;
	    }
	  }
	}
	else if (dr < min_Dr){
	  if( (fabs(match_pt - gen_pt->at(it))/gen_pt->at(it)) < 2.) {
	    /// find closest match in dR to status 1
	    matched_in_Dr=true;
	    min_Dr= dr;
	    
	    /// set index of matched status 1 muon
	    matched_index=it;
	  }
	}
      }// end of gen loop to find status 1 muon

      ///// treat case where there is a matched status 1 muon:
      //// classify into prompt:Fake:FromTau

      
      if(matched_in_Dr){
        /// Find closest non muon ancesteror
        float pdgid = gen_PID->at(matched_index);

        // mc_pdgid = closest matched status 1 pdgid
        mc_pdgid= int(pdgid);

        // mindex = mother index: will loop to find first non el mother
        int mindex= matched_index;

        while ( (fabs(gen_PID->at(mindex)) == 13)) {
          pdgid = gen_PID->at(mindex);
          mindex=gen_mother_index->at(mindex);
        }
        /// pdgid is now of muon from non muon mother
        //  mindex = index for mother of non muon ancestor

        if( (fabs(gen_PID->at(mindex)) == 23) || (fabs(gen_PID->at(mindex)) == 24)) {
	  /// Check if it is a chargeflip.
          mutype=1;
	  
          if(pdgid * muon_charge->at(ilep) > 0 )     muon.SetIsChargeFlip(true);
          else     muon.SetIsChargeFlip(false);

	  int n_mu_from_mother=0;
	  for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
	    if(gen_mother_index->at(itx) <= 0)continue;
	    if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
	    if(gen_pt->at(itx) < 0.001) continue;
	    if(fabs(gen_PID->at(itx)) ==13) {
	      if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) n_mu_from_mother++;
	    }
	  }
	  if(n_mu_from_mother == 3)  muon.SetIsPhotonConversion(true);
	  if(n_mu_from_mother == 5)  muon.SetIsPhotonConversion(true);
          mother_index=mindex;
          mother_pdgid=gen_PID->at(mindex);
          isprompt=true; /// means is prompt
        }/// end of Z/W
        else {
          if(gen_status->at(mindex) == 2){
            if(fabs(gen_PID->at(mindex)) > 50) {isprompt=false; mother_pdgid=gen_PID->at(mindex); mother_index=mindex; from_tau=false;
	      mutype=2;
	    }
	    else {
	      isprompt=true;
	      mutype=3;

	      if(fabs(gen_PID->at(mindex)) == 22){
		if(fabs(gen_PID->at(gen_mother_index->at(mindex))) > 50){
                  mutype=4;
                }
		else                   mutype=5;
              } 
	    }
	    
            if(fabs(gen_PID->at(mindex)) == 15){
              isprompt=true; mother_pdgid=gen_PID->at(mindex);  mother_index=mindex; from_tau=true;
              // Check if el from tau  is CF
	      mutype=6;
	      if(pdgid * muon_charge->at(ilep) > 0 )     muon.SetIsChargeFlip(true);
              else     muon.SetIsChargeFlip(false);

	      int n_mu_from_mother=0;
	      for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
		if(gen_mother_index->at(itx) <= 0)continue;
		if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
		if(gen_pt->at(itx) < 0.001) continue;
		if(fabs(gen_PID->at(itx)) ==13) {
		  if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) n_mu_from_mother++;
		}
	      }
	      if(n_mu_from_mother == 3)  muon.SetIsPhotonConversion(true);
	      if(n_mu_from_mother == 5)  muon.SetIsPhotonConversion(true);
	     
	      if(fabs(gen_PID->at(gen_mother_index->at(mother_index))) > 50) {isprompt=false; mutype=7;}
            }
          }/// end of status 2 check
          else {
            /// using new method for matching: These events are set as prompt
            isprompt=true;mother_pdgid=-99999; mother_index=mindex; from_tau=false;
	    mutype=8;
            if(pdgid * muon_charge->at(ilep) > 0 )    muon.SetIsChargeFlip(true);
            else     muon.SetIsChargeFlip(false);
	    int n_mu_from_mother=0;
            vector<KTruth> vmu_tmp;
            bool neutrino_invertex(false);

	    for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
	      if(gen_mother_index->at(itx) <= 0)continue;
	      if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
	      if(gen_pt->at(itx) < 0.001) continue;
	      if(fabs(gen_PID->at(itx)) ==13) {
		if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) n_mu_from_mother++;
		if(gen_status->at(itx) ==1){
		  KTruth truthmu;
		  truthmu.SetPtEtaPhiM(gen_pt->at(itx), gen_eta->at(itx), gen_phi->at(itx), gen_mass->at(itx));
		  vmu_tmp.push_back(truthmu);
		}
	      }
	      if(fabs(gen_PID->at(itx)) ==14) {
		
		int index_mother_nu=gen_mother_index->at(itx);
		while (fabs(index_mother_nu) ==14){
		  index_mother_nu=gen_mother_index->at(index_mother_nu);
		}
		
		if(index_mother_nu == mindex) {
		  neutrino_invertex=true;
		}
	      }
	    } // end of truth loop to check Conv                                                                                                                                                                                                  
	    
	    if(neutrino_invertex) mutype=9;
	    
	    if(vmu_tmp.size() ==2) {
	      KParticle ll = vmu_tmp[0] + vmu_tmp[1];
	      if(fabs(ll.M()) < 5.) mutype=10;
	    }
	    
	    
	    
	    if(n_mu_from_mother == 3)  muon.SetIsPhotonConversion(true);
	    if(n_mu_from_mother == 5)  muon.SetIsPhotonConversion(true);

	    /// speacial treatment for signal                                                                                                                                                                                                                                   

            if( fabs(gen_PID->at(mindex))>= 9900012 &&  fabs(gen_PID->at(mindex) < 9900025 ))mother_pdgid= gen_PID->at(mindex);


          }
        }
      }      /// In case no status 1 muon is found : classify muon fake
      else{
	if(muon_charge->size() ==2){
	  for (UInt_t itxx=0; itxx< gen_pt->size(); itxx++ ){
            if(gen_mother_index->at(itxx) <= 0)continue;
            if(gen_mother_index->at(itxx) >= int(gen_pt->size()))continue;
            if(gen_pt->at(itxx) < 0.001) continue;
	    //cout << itxx << " " << gen_PID->at(itxx) << " " << gen_PID->at(gen_mother_index->at(itxx)) << " " << gen_eta->at(itxx) << " " << gen_phi->at(itxx) << endl;
	  }
	}
        if(gen_pt){
	  for (UInt_t it=0; it< gen_pt->size(); it++ ){
            if(gen_mother_index->at(it) <= 0)continue;
            if(gen_mother_index->at(it) >= int(gen_pt->size()))continue;
            if(gen_pt->at(it) < 0.001) continue;

	    bool already_matched=false;
	    for(unsigned int im=0; im < matched_truth.size();im++){
	      if(it == unsigned(matched_truth.at(im))) already_matched=true;
	    }
	    //if(already_matched) continue;

            double match_eta =muon_eta->at(ilep);
            double match_phi =muon_phi->at(ilep);
            double dr = sqrt( pow(fabs( match_eta - gen_eta->at(it)),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( match_phi - gen_phi->at(it))),2.0));

            if (dr <0.1){
              matched_in_Dr=true;
              int mindex= gen_mother_index->at(it);
              float pdgid = gen_PID->at(it);
	      
	      /// Unlikely to have mother as muon but just in case
              while ( (fabs(gen_PID->at(mindex)) == 13)) {
                mindex=gen_mother_index->at(mindex);
              }
              // isprompt = false since it failed status 1 matching
              isprompt=false;
              /// mother index of first non muon
              mother_pdgid=gen_PID->at(mindex);
              mother_index=mindex;
              matched_index = it;
	      mc_pdgid= int(pdgid);
              if(fabs(pdgid) == 22) {
		if(fabs(mother_pdgid) > 50) mutype=11;
                else mutype=12;
		
		from_tau=false;
                break;
              }

              int grandmother =0;
              if(gen_mother_index->at(mindex) > 0)grandmother=gen_PID->at(gen_mother_index->at(mindex));

              if(fabs(pdgid) == 15){
		from_tau=true;
		if(fabs(mother_pdgid) > 50) mutype=13;
		else mutype=14;
		if(fabs(mother_pdgid) ==15){
		  if(fabs(grandmother) > 50) mutype=-13;
		  else mutype=-14;

		}
	      }
	      if(fabs(gen_PID->at(gen_mother_index->at(it))) == 13){
		mutype=15;
		int n_mu_from_mother=0;
		for (UInt_t itx=0; itx< gen_pt->size(); itx++ ){
		  if(gen_mother_index->at(itx) <= 0)continue;
		  if(gen_mother_index->at(itx) >= int(gen_pt->size()))continue;
		  if(gen_pt->at(itx) < 0.001) continue;
		  if(fabs(gen_PID->at(itx)) ==13) {
		    if(gen_mother_index->at(itx) == gen_mother_index->at(matched_index)) n_mu_from_mother++;
		  }
		}
		if(n_mu_from_mother == 3)  muon.SetIsPhotonConversion(true);
		if(n_mu_from_mother == 5)  muon.SetIsPhotonConversion(true);
	      }else{
		muon.SetIsPhotonConversion(false);
	      }
	      
	      if(fabs(pdgid) == 1){
                mutype=16;
              }
              else if(fabs(pdgid) == 2){
                mutype=17;
              }
              else if(fabs(pdgid) == 3){
               mutype=18;
              }
              else if(fabs(pdgid) == 4){
                mutype=19;
              }
              else if(fabs(pdgid) == 5){
                mutype=20;
              }
              else if(fabs(pdgid) == 21){
                mutype=21;
              }
	      
	      else if(fabs(pdgid) == 211){
		mutype=22;
	      }
	      else if(fabs(pdgid) == 310){
		mutype=23;
	      }
	      else if(fabs(pdgid) == 431){
		mutype=24;
	    }
	      else if(fabs(pdgid) == 13){
		mutype=25;
	      }
	      else if(fabs(pdgid) == 311){
                mutype=26;
              }
	      else if(fabs(pdgid) > 500 && fabs(pdgid) < 600){
                mutype=27;
              }
	      else mutype=28;

	    }// dr req
          }// loop over gen vector
        }// require gen info
      }// no status 1 match
    }
    
    /// matched_index is index which matches reco muon with smallest dR
    /// - If multiple status 1 muons are matched look at closest in pt
    /// - In no status 1 is matched set as not prompt but look for closest particle in dR 
    /// - In no particles within dR < 0.1 matched_in_Dr = false
    matched_truth.push_back(matched_index);


    muon.SetType(mutype);

    if(!matched_in_Dr){
      muon.SetMCMatched(false);
      muon.SetIsFromTau(false);
      muon.SetMCMatchedPdgId(-1);
      muon.SetMotherPdgId(0);
      muon.SetMotherTruthIndex(-1);
      muon.SetMCTruthIndex(-1);
    }
    else{

      muon.SetMCMatched(isprompt);
      muon.SetIsFromTau(from_tau);
      muon.SetMotherPdgId(mother_pdgid);
      muon.SetMCMatchedPdgId(mc_pdgid);
      muon.SetMotherTruthIndex(mother_index);
      muon.SetMCTruthIndex(matched_index);
      if(gen_status->at(matched_index)==1)muon.SetIsPromptFlag(gen_isPrompt->at(matched_index));

    }
    }

    /// Fill vector
    muons.push_back(muon);
  }
  
  std::sort( muons.begin(), muons.end(), isHigherPt );
  m_logger << DEBUG << "End of Muon Filling" << LQLogger::endmsg;
  return muons;
}


double SKTreeFiller::CalcPFIso(double j_PFCH04, double j_PFNH04, double j_PFPH04, double j_PU04){

  double absiso = j_PFCH04+std::max( 0., j_PFNH04 + j_PFPH04 - 0.5*j_PU04 );
  
  return absiso;
}



double SKTreeFiller::CalcMiniIso(double pt, double ch, double nh, double ph, double pu, double rho, double EA){

  double r_mini = miniIsoDr(pt);

  double correction = rho * EA * (r_mini/0.3) * (r_mini/0.3);
  double correctedIso = ch + std::max(0.0, nh + ph - correction);
  return correctedIso/pt;
}


float SKTreeFiller::miniIsoDr(double pt){
  float mindr = 0.05;
  float maxdr = 0.2;
  float kt_scale = 10.0;
  return std::max(mindr, std::min(maxdr, float(kt_scale/pt)));
}


double SKTreeFiller::ElectronEA(double eta){

  eta =fabs(eta);
  if     (eta<1.0000) return 0.1566;
  else if(eta<1.4790) return 0.1626;
  else if(eta<2.0000) return 0.1073;
  else if(eta<2.2000) return 0.0854;
  else if(eta<2.3000) return 0.1051;
  else if(eta<2.4000) return 0.1204;
  else if(eta<5.0000) return 0.1524;
  else return 0.1524;

}
double SKTreeFiller::EA(double eta){


  eta =fabs(eta);
  if     (eta<0.8000) return 0.0566;
  else if(eta<1.3000) return 0.0562;
  else if(eta<2.0000) return 0.0363;
  else if(eta<2.2000) return 0.0119;
  else if(eta<2.4000) return 0.0064;
  else return 0.0064;

}


  

std::vector<snu::KTruth>   SKTreeFiller::GetTruthParticles(int np){
  
  m_logger << DEBUG << "Filling Truth" << LQLogger::endmsg;
  std::vector<snu::KTruth> vtruth;

  if(IsData) return vtruth;

  int counter=0;

  //vector<int>     *gen_mother_PID;
  //vector<double>  *gen_mother_pt;


  if(!LQinput){

    for(std::vector<KTruth>::iterator kit  = k_inputtruth->begin(); kit != k_inputtruth->end(); kit++, counter++){
      if(counter == np)  break;
      vtruth.push_back(*kit);
    }
    return vtruth;
  }
  
  m_logger << DEBUG << "Filling truth Info: " << gen_pt->size() << LQLogger::endmsg;

  for (UInt_t it=0; it< gen_pt->size(); it++ , counter++) {
    
    if(counter == np)  break;
    KTruth truthp;
    truthp.SetPtEtaPhiM(double(gen_pt->at(it)), double(gen_eta->at(it)), double(gen_phi->at(it)), double(gen_mass->at(it)));
    truthp.SetParticlePdgId(gen_PID->at(it));
    truthp.SetParticleStatus(gen_status->at(it));
    truthp.SetParticleIndexMother(gen_mother_index->at(it));
    

    m_logger << DEBUG << "Filling Truth  1" << LQLogger::endmsg;

    if(k_cat_version > 0){
      // To save space set a single int as the flag. 
      // 
      m_logger << DEBUG << "Filling Truth  2" << LQLogger::endmsg;
      int truth_flag = 0;
      if(gen_isPrompt->at(it))                         truth_flag+=1;
      if(gen_isPromptFinalState->at(it))               truth_flag+=10;
      if(gen_isDecayedLeptonHadron->at(it))            truth_flag+=100;
      if(gen_isTauDecayProduct->at(it))                truth_flag+=1000;
      m_logger << DEBUG << "Filling Truth  3" << LQLogger::endmsg;
      if(gen_isPromptTauDecayProduct->at(it))          truth_flag+=10000;
      if(gen_isDirectPromptTauDecayProductFinalState->at(it)) truth_flag+=100000;
      if(gen_isHardProcess->at(it))                           truth_flag+=1000000;
      if(gen_fromHardProcessDecayed->at(it))                  truth_flag+=10000000;
      m_logger << DEBUG << "Filling Truth  4" << LQLogger::endmsg;
      if(gen_fromHardProcessBeforeFSR->at(it))                truth_flag+=100000000;
      if(gen_fromHardProcessFinalState->at(it))               truth_flag+=1000000000;
      if(gen_isMostlyLikePythia6Status3->at(it))              truth_flag+=10000000000;
      if(gen_isLastCopy->at(it))                              truth_flag+=100000000000;
      m_logger << DEBUG << "Filling Truth 51" << LQLogger::endmsg;
      if(gen_isLastCopyBeforeFSR->at(it))                     truth_flag+=1000000000000;
      if(gen_isPromptDecayed->at(it))                         truth_flag+=10000000000000;
      truthp.SetStatusFlag(truth_flag);
    }
    
    vtruth.push_back(truthp);  
  }
  
  return vtruth;
}



std::vector<double>  SKTreeFiller::GetWeights(TString tag){

  std::vector<double> weights_pileup;

  if(tag=="2016_25ns_Moriond17MC"){

    // from SimGeneral/MixingModule/python/mix_2016_25ns_Moriond17MC_PoissonOOTPU_cfi.py                                                                                                                                                                   

    weights_pileup.push_back(1.78653e-05);
    weights_pileup.push_back(2.56602e-05);
    weights_pileup.push_back(5.27857e-05);
    weights_pileup.push_back(8.88954e-05);
    weights_pileup.push_back(0.000109362);
    weights_pileup.push_back(0.000140973);
    weights_pileup.push_back(0.000240998);
    weights_pileup.push_back(0.00071209 );
    weights_pileup.push_back(0.00130121 );
    weights_pileup.push_back(0.00245255 );
    weights_pileup.push_back(0.00502589 );
    weights_pileup.push_back(0.00919534 );
    weights_pileup.push_back(0.0146697  );
    weights_pileup.push_back(0.0204126  );
    weights_pileup.push_back(0.0267586  );
    weights_pileup.push_back(0.0337697  );
    weights_pileup.push_back(0.0401478  );
    weights_pileup.push_back(0.0450159  );
    weights_pileup.push_back(0.0490577  );
    weights_pileup.push_back(0.0524855  );
    weights_pileup.push_back(0.0548159  );
    weights_pileup.push_back(0.0559937  );
    weights_pileup.push_back(0.0554468  );
    weights_pileup.push_back(0.0537687  );
    weights_pileup.push_back(0.0512055  );
    weights_pileup.push_back(0.0476713 );
    weights_pileup.push_back(0.0435312 );
    weights_pileup.push_back(0.0393107  );
    weights_pileup.push_back(0.0349812  );
    weights_pileup.push_back(0.0307413  );
    weights_pileup.push_back(0.0272425  );
    weights_pileup.push_back(0.0237115  );
    weights_pileup.push_back(0.0208329  );
    weights_pileup.push_back(0.0182459  );
    weights_pileup.push_back(0.0160712  );
    weights_pileup.push_back(0.0142498 );
    weights_pileup.push_back(0.012804   );
    weights_pileup.push_back(0.011571   );
    weights_pileup.push_back(0.010547   );
    weights_pileup.push_back(0.00959489 );
    weights_pileup.push_back(0.00891718 );
    weights_pileup.push_back(0.00829292 );
    weights_pileup.push_back(0.0076195  );
    weights_pileup.push_back(0.0069806  );
    weights_pileup.push_back(0.0062025  );
    weights_pileup.push_back(0.00546581 );
    weights_pileup.push_back(0.00484127 );
    weights_pileup.push_back(0.00407168 );
    weights_pileup.push_back(0.00337681 );
    weights_pileup.push_back(0.00269893 );
    weights_pileup.push_back(0.00212473 );
    weights_pileup.push_back(0.00160208 );
    weights_pileup.push_back(0.00117884 );
    weights_pileup.push_back(0.000859662);
    weights_pileup.push_back(0.000569085);
    weights_pileup.push_back(0.000365431);
    weights_pileup.push_back(0.000243565);
    weights_pileup.push_back(0.00015688 );
    weights_pileup.push_back(9.88128e-05);
    weights_pileup.push_back(6.53783e-05);
    weights_pileup.push_back(3.73924e-05);
    weights_pileup.push_back(2.61382e-05);
    weights_pileup.push_back(2.0307e-05 );
    weights_pileup.push_back(1.73032e-05);
    weights_pileup.push_back(1.435e-05  );
    weights_pileup.push_back( 1.36486e-05);
    weights_pileup.push_back(1.35555e-05);
    weights_pileup.push_back(1.37491e-05);
    weights_pileup.push_back(1.34255e-05);
    weights_pileup.push_back(1.33987e-05);
    weights_pileup.push_back(1.34061e-05);
    weights_pileup.push_back(1.34211e-05);
    weights_pileup.push_back(1.34177e-05);
    weights_pileup.push_back(1.32959e-05);
    weights_pileup.push_back(1.33287e-05);
    return  weights_pileup;

  }

  if(tag=="Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON"){


    //#pileupCalc.py -i /CATTools/CatProducer/data/LumiMask/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /CATTools/CatProducer/data/LumiMask/pileup_latest.txt --minBiasXsec 69200 --calcMode true --maxPileupBin 75 --numPileupBins 75 PileUpData.root                                                                                                                                                                                                                            

  weights_pileup.push_back(2.387970e+05);
 weights_pileup.push_back(8.375429e+05);
 weights_pileup.push_back(2.308427e+06);
 weights_pileup.push_back(3.124754e+06);
 weights_pileup.push_back(4.476191e+06);
 weights_pileup.push_back(5.995911e+06);
 weights_pileup.push_back(7.000896e+06);
 weights_pileup.push_back(1.289165e+07);
 weights_pileup.push_back(3.526173e+07);
 weights_pileup.push_back(7.870123e+07);
 weights_pileup.push_back(1.769458e+08);
 weights_pileup.push_back(3.600895e+08);
 weights_pileup.push_back(6.027665e+08);
 weights_pileup.push_back(8.765194e+08);
 weights_pileup.push_back(1.174474e+09);
 weights_pileup.push_back(1.489059e+09);
 weights_pileup.push_back(1.759352e+09);
 weights_pileup.push_back(1.943926e+09);
 weights_pileup.push_back(2.049172e+09);
 weights_pileup.push_back(2.101582e+09);
 weights_pileup.push_back(2.132787e+09);
 weights_pileup.push_back(2.149099e+09);
 weights_pileup.push_back(2.128986e+09);
 weights_pileup.push_back(2.062649e+09);
 weights_pileup.push_back(1.962884e+09);
 weights_pileup.push_back(1.841872e+09);
 weights_pileup.push_back(1.704136e+09);
 weights_pileup.push_back(1.554523e+09);
 weights_pileup.push_back(1.399489e+09);
 weights_pileup.push_back(1.243533e+09);
 weights_pileup.push_back(1.088821e+09);
 weights_pileup.push_back(9.373048e+08);
 weights_pileup.push_back(7.920441e+08);
 weights_pileup.push_back(6.567177e+08);
 weights_pileup.push_back(5.344668e+08);
 weights_pileup.push_back(4.271268e+08);
 weights_pileup.push_back(3.351056e+08);
 weights_pileup.push_back(2.577246e+08);
 weights_pileup.push_back(1.937514e+08);
 weights_pileup.push_back(1.418309e+08);
 weights_pileup.push_back(1.006714e+08);
 weights_pileup.push_back(6.901386e+07);
 weights_pileup.push_back(4.554008e+07);
 weights_pileup.push_back(2.884748e+07);
 weights_pileup.push_back(1.750632e+07);
 weights_pileup.push_back(1.016264e+07);
 weights_pileup.push_back(5.637781e+06);
 weights_pileup.push_back(2.987282e+06);
 weights_pileup.push_back(1.512002e+06);
 weights_pileup.push_back(7.318454e+05);
 weights_pileup.push_back(3.398220e+05);
 weights_pileup.push_back(1.525454e+05);
 weights_pileup.push_back(6.740482e+04);
 weights_pileup.push_back(3.048969e+04);
 weights_pileup.push_back(1.515211e+04);
 weights_pileup.push_back(8.975911e+03);
 weights_pileup.push_back(6.496155e+03);
 weights_pileup.push_back(5.434805e+03);
 weights_pileup.push_back(4.889958e+03);
 weights_pileup.push_back(4.521716e+03);
 weights_pileup.push_back(4.208464e+03);
 weights_pileup.push_back(3.909763e+03);
 weights_pileup.push_back(3.614274e+03);
 weights_pileup.push_back(3.320722e+03);
 weights_pileup.push_back(3.031096e+03);
 weights_pileup.push_back(2.748237e+03);
 weights_pileup.push_back(2.474977e+03);
 weights_pileup.push_back(2.213817e+03);
 weights_pileup.push_back(1.966815e+03);
 weights_pileup.push_back(1.735546e+03);
 weights_pileup.push_back(1.521109e+03);
 weights_pileup.push_back(1.324149e+03);
 weights_pileup.push_back(1.144898e+03);
 weights_pileup.push_back(9.832202e+02);
 weights_pileup.push_back(8.386676e+02);

 return  weights_pileup;

  }

  if(tag=="Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_Up"){

    //#pileupCalc.py -i /CATTools/CatProducer/data/LumiMask/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /CATTools/CatProducer/data/LumiMask/pileup_latest.txt --minBiasXsec 72383 --calcMode true --maxPileupBin 75 --numPileupBins 75 PileUpData_Up.root                                                                                                                                                                                                                         

  weights_pileup.push_back(2.387970e+05);
 weights_pileup.push_back(8.375429e+05);
 weights_pileup.push_back(2.308427e+06);
 weights_pileup.push_back(3.124754e+06);
 weights_pileup.push_back(4.476191e+06);
 weights_pileup.push_back(5.995911e+06);
 weights_pileup.push_back(7.000896e+06);
 weights_pileup.push_back(1.289165e+07);
 weights_pileup.push_back(3.526173e+07);
 weights_pileup.push_back(7.870123e+07);
 weights_pileup.push_back(1.769458e+08);
 weights_pileup.push_back(3.600895e+08);
 weights_pileup.push_back(6.027665e+08);
 weights_pileup.push_back(8.765194e+08);
 weights_pileup.push_back(1.174474e+09);
 weights_pileup.push_back(1.489059e+09);
 weights_pileup.push_back(1.759352e+09);
 weights_pileup.push_back(1.943926e+09);
 weights_pileup.push_back(2.049172e+09);
 weights_pileup.push_back(2.101582e+09);
 weights_pileup.push_back(2.132787e+09);
 weights_pileup.push_back(2.149099e+09);
 weights_pileup.push_back(2.128986e+09);
 weights_pileup.push_back(2.062649e+09);
 weights_pileup.push_back(1.962884e+09);
 weights_pileup.push_back(1.841872e+09);
 weights_pileup.push_back(1.704136e+09);
 weights_pileup.push_back(1.554523e+09);
 weights_pileup.push_back(1.399489e+09);
 weights_pileup.push_back(1.243533e+09);
 weights_pileup.push_back(1.088821e+09);
 weights_pileup.push_back(9.373048e+08);
 weights_pileup.push_back(7.920441e+08);
 weights_pileup.push_back(6.567177e+08);
 weights_pileup.push_back(5.344668e+08);
 weights_pileup.push_back(4.271268e+08);
 weights_pileup.push_back(3.351056e+08 );
 weights_pileup.push_back(2.577246e+08);
 weights_pileup.push_back(1.937514e+08);
 weights_pileup.push_back(1.418309e+08);
 weights_pileup.push_back(1.006714e+08);
 weights_pileup.push_back(6.901386e+07);
 weights_pileup.push_back(4.554008e+07);
 weights_pileup.push_back(2.884748e+07);
 weights_pileup.push_back(1.750632e+07);
 weights_pileup.push_back(1.016264e+07);
 weights_pileup.push_back(5.637781e+06);
 weights_pileup.push_back(2.987282e+06);
 weights_pileup.push_back(1.512002e+06);
 weights_pileup.push_back(7.318454e+05);
 weights_pileup.push_back(3.398220e+05);
 weights_pileup.push_back(1.525454e+05);
 weights_pileup.push_back(6.740482e+04);
 weights_pileup.push_back(3.048969e+04);
 weights_pileup.push_back(1.515211e+04);
 weights_pileup.push_back(8.975911e+03);
 weights_pileup.push_back(6.496155e+03);
 weights_pileup.push_back(5.434805e+03);
 weights_pileup.push_back(4.889958e+03);
 weights_pileup.push_back(4.521716e+03);
 weights_pileup.push_back(4.208464e+03);
 weights_pileup.push_back(3.909763e+03);
 weights_pileup.push_back(3.614274e+03);
 weights_pileup.push_back(3.320722e+03);
 weights_pileup.push_back(3.031096e+03);
 weights_pileup.push_back(2.748237e+03);
 weights_pileup.push_back(2.474977e+03);
 weights_pileup.push_back(2.213817e+03);
 weights_pileup.push_back(1.966815e+03);
 weights_pileup.push_back(1.735546e+03);
 weights_pileup.push_back(1.521109e+03);
 weights_pileup.push_back(1.324149e+03);
 weights_pileup.push_back(1.144898e+03);
 weights_pileup.push_back(9.832202e+02);
 weights_pileup.push_back(8.386676e+02);

 return  weights_pileup;

  }

  if(tag=="Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_Up"){

    //#pileupCalc.py -i /CATTools/CatProducer/data/LumiMask/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /CATTools/CatProducer/data/LumiMask/pileup_latest.txt --minBiasXsec 72383 --calcMode true --maxPileupBin 75 --numPileupBins 75 PileUpData_Up.root                                                                                                                                                                                                                         

  weights_pileup.push_back(2.387970e+05);
 weights_pileup.push_back(8.375429e+05);
 weights_pileup.push_back(2.308427e+06);
 weights_pileup.push_back(3.124754e+06);
 weights_pileup.push_back(4.476191e+06);
 weights_pileup.push_back(5.995911e+06);
 weights_pileup.push_back(7.000896e+06);
 weights_pileup.push_back(1.289165e+07);
 weights_pileup.push_back(3.526173e+07);
 weights_pileup.push_back(7.870123e+07);
 weights_pileup.push_back(1.769458e+08);
 weights_pileup.push_back(3.600895e+08);
 weights_pileup.push_back(6.027665e+08);
 weights_pileup.push_back(8.765194e+08);
 weights_pileup.push_back(1.174474e+09);
 weights_pileup.push_back(1.489059e+09);
 weights_pileup.push_back(1.759352e+09);
 weights_pileup.push_back(1.943926e+09);
 weights_pileup.push_back(2.049172e+09);
 weights_pileup.push_back(2.101582e+09);
 weights_pileup.push_back(2.132787e+09);
 weights_pileup.push_back(2.149099e+09);
 weights_pileup.push_back(2.128986e+09);
 weights_pileup.push_back(2.062649e+09);
 weights_pileup.push_back(1.962884e+09);
 weights_pileup.push_back(1.841872e+09);
 weights_pileup.push_back(1.704136e+09);
 weights_pileup.push_back(1.554523e+09);
 weights_pileup.push_back(1.399489e+09);
 weights_pileup.push_back(1.243533e+09);
 weights_pileup.push_back(1.088821e+09);
 weights_pileup.push_back(9.373048e+08);
 weights_pileup.push_back(7.920441e+08);
 weights_pileup.push_back(6.567177e+08);
 weights_pileup.push_back(5.344668e+08);
 weights_pileup.push_back(4.271268e+08);
 weights_pileup.push_back(3.351056e+08 );
 weights_pileup.push_back(2.577246e+08);
 weights_pileup.push_back(1.937514e+08);
 weights_pileup.push_back(1.418309e+08);
 weights_pileup.push_back(1.006714e+08);
 weights_pileup.push_back(6.901386e+07);
 weights_pileup.push_back(4.554008e+07);
 weights_pileup.push_back(2.884748e+07);
 weights_pileup.push_back(1.750632e+07);
 weights_pileup.push_back(1.016264e+07);
 weights_pileup.push_back(5.637781e+06);
 weights_pileup.push_back(2.987282e+06);
 weights_pileup.push_back(1.512002e+06);
 weights_pileup.push_back(7.318454e+05);
 weights_pileup.push_back(3.398220e+05);
 weights_pileup.push_back(1.525454e+05);
 weights_pileup.push_back(6.740482e+04);
 weights_pileup.push_back(3.048969e+04);
 weights_pileup.push_back(1.515211e+04);
 weights_pileup.push_back(8.975911e+03);
 weights_pileup.push_back(6.496155e+03);
 weights_pileup.push_back(5.434805e+03);
 weights_pileup.push_back(4.889958e+03);
 weights_pileup.push_back(4.521716e+03);
 weights_pileup.push_back(4.208464e+03 );
 weights_pileup.push_back(3.909763e+03);
 weights_pileup.push_back(3.614274e+03);
 weights_pileup.push_back(3.320722e+03);
 weights_pileup.push_back(3.031096e+03);
 weights_pileup.push_back(2.748237e+03);
 weights_pileup.push_back(2.474977e+03);
 weights_pileup.push_back(2.213817e+03);
 weights_pileup.push_back(1.966815e+03);
 weights_pileup.push_back(1.735546e+03);
 weights_pileup.push_back(1.521109e+03);
 weights_pileup.push_back(1.324149e+03);
 weights_pileup.push_back(1.144898e+03);
 weights_pileup.push_back(9.832202e+02);
 weights_pileup.push_back(8.386676e+02);

 return  weights_pileup;

  }
  if(tag=="Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_Dn"){

    //#pileupCalc.py -i /CATTools/CatProducer/data/LumiMask/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt --inputLumiJSON /CATTools/CatProducer/data/LumiMask/pileup_latest.txt --minBiasXsec 66016 --calcMode true --maxPileupBin 75 --numPileupBins 75 PileUpData_Dn.root                                                                                                                                                                                                                         

  weights_pileup.push_back(2.474113e+05);
 weights_pileup.push_back(1.069278e+06);
 weights_pileup.push_back(2.428277e+06);
 weights_pileup.push_back(3.566992e+06);
 weights_pileup.push_back(4.991832e+06);
 weights_pileup.push_back(6.593141e+06);
 weights_pileup.push_back(8.097305e+06);
 weights_pileup.push_back(1.996320e+07);
 weights_pileup.push_back(5.191520e+07);
 weights_pileup.push_back(1.197807e+08);
 weights_pileup.push_back(2.727752e+08);
 weights_pileup.push_back(5.131701e+08);
 weights_pileup.push_back(8.023341e+08);
 weights_pileup.push_back(1.118763e+09);
 weights_pileup.push_back(1.462995e+09);
 weights_pileup.push_back(1.780219e+09);
 weights_pileup.push_back(2.005191e+09);
 weights_pileup.push_back(2.135073e+09);
 weights_pileup.push_back(2.198487e+09);
 weights_pileup.push_back(2.233964e+09);
 weights_pileup.push_back(2.252561e+09);
 weights_pileup.push_back(2.229714e+09);
 weights_pileup.push_back(2.154206e+09);
 weights_pileup.push_back(2.041681e+09);
 weights_pileup.push_back(1.905607e+09);
 weights_pileup.push_back(1.751084e+09);
 weights_pileup.push_back(1.584596e+09);
 weights_pileup.push_back(1.413602e+09);
 weights_pileup.push_back(1.242528e+09);
 weights_pileup.push_back(1.073635e+09);
 weights_pileup.push_back(9.097710e+08);
 weights_pileup.push_back(7.551027e+08);
 weights_pileup.push_back(6.138886e+08);
 weights_pileup.push_back(4.891245e+08);
 weights_pileup.push_back(3.819822e+08);
 weights_pileup.push_back(2.920568e+08);
 weights_pileup.push_back(2.180117e+08);
 weights_pileup.push_back(1.582197e+08);
 weights_pileup.push_back(1.111016e+08);
 weights_pileup.push_back(7.513638e+07);
 weights_pileup.push_back(4.874432e+07);
 weights_pileup.push_back(3.023911e+07);
 weights_pileup.push_back(1.789611e+07);
 weights_pileup.push_back(1.008679e+07);
 weights_pileup.push_back(5.408384e+06);
 weights_pileup.push_back(2.757256e+06);
 weights_pileup.push_back(1.336896e+06);
 weights_pileup.push_back(6.175226e+05);
 weights_pileup.push_back(2.730083e+05); weights_pileup.push_back(1.168838e+05); weights_pileup.push_back(4.983506e+04); weights_pileup.push_back(2.245556e+04); weights_pileup.push_back(1.173965e+04); weights_pileup.push_back(7.637138e+03); weights_pileup.push_back(6.017980e+03); weights_pileup.push_back(5.280664e+03); weights_pileup.push_back(4.837353e+03); weights_pileup.push_back(4.483816e+03); weights_pileup.push_back(4.153851e+03); weights_pileup.push_back(3.828857e+03); weights_pileup.push_back(3.506027e+03); weights_pileup.push_back(3.187482e+03); weights_pileup.push_back(2.876619e+03); weights_pileup.push_back(2.576851e+03); weights_pileup.push_back(2.291178e+03); weights_pileup.push_back(2.022034e+03); weights_pileup.push_back(1.771241e+03); weights_pileup.push_back(1.540024e+03); weights_pileup.push_back(1.329043e+03); weights_pileup.push_back(1.138448e+03); weights_pileup.push_back(9.679458e+02); weights_pileup.push_back(8.168710e+02); weights_pileup.push_back(6.842602e+02); weights_pileup.push_back(5.689249e+02); weights_pileup.push_back(4.695210e+02);																																																																																																																																																		       

 
 return  weights_pileup;

  }
  return  weights_pileup;


}

