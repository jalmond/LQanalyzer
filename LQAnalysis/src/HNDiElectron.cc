// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNDiElectron);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiElectron::HNDiElectron() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiElectron");

  Message("In HNDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  
  MakeCleverHistograms(sighist,"NoCut");
  MakeCleverHistograms(sighist,"NoCutPtEta");
  MakeCleverHistograms(sighist,"Fake");
  MakeCleverHistograms(sighist,"TriElCR");
  MakeCleverHistograms(sighist,"TriEl");
  MakeCleverHistograms(sighist,"TriEl_jetmva_inclusive");
  MakeCleverHistograms(sighist,"ZZ");
  MakeCleverHistograms(sighist,"OSee");
  MakeCleverHistograms(sighist,"SSloose");
  MakeCleverHistograms(sighist,"SSee");
  MakeCleverHistograms(sighist,"SSee_Z");
  MakeCleverHistograms(sighist,"SSee_0jet_Z");
  MakeCleverHistograms(sighist,"SSee_1jet_Z");
  MakeCleverHistograms(sighist,"SSee_gt0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet");
  MakeCleverHistograms(sighist,"SSee_DiJet");
  
  MakeCleverHistograms(sighist,"SSee_DiJet_20_nor");
  MakeCleverHistograms(sighist,"SSee_DiJet_40_nor");

  MakeCleverHistograms(sighist,"SSee_1jet_20_nor");
  MakeCleverHistograms(sighist,"SSee_1jet_40_nor");
  
  MakeCleverHistograms(sighist,"LowMassRegion");
  MakeCleverHistograms(sighist,"MediumMassRegion");
  MakeCleverHistograms(sighist,"HighMassRegion");
  MakeCleverHistograms(sighist,"LowMassRegion_0905");
  MakeCleverHistograms(sighist,"MediumMassRegion_0905");
  MakeCleverHistograms(sighist,"HighMassRegion_0905");
  MakeCleverHistograms(sighist,"SSee_noZ");
  MakeCleverHistograms(sighist,"SSee_0jet_noZ");
  MakeCleverHistograms(sighist,"SSee_1jet_noZ");

  MakeCleverHistograms(sighist,"BJetCR");
  MakeCleverHistograms(sighist,"BJetCR_20_nor");
  MakeCleverHistograms(sighist,"BJetCR_40_nor");
  
  MakeCleverHistograms(sighist,"HighMETCR");
  MakeCleverHistograms(sighist,"HighMETCR_20_nor");
  MakeCleverHistograms(sighist,"HighMETCR_40_nor");



  MakeCleverHistograms(sighist,"HighMETBJetCR");
  MakeCleverHistograms(sighist,"SingleEl_CR");
  MakeCleverHistograms(sighist,"SingleEl_bjetCR");
  MakeCleverHistograms(sighist,"SingleElTight_CR");
  MakeCleverHistograms(sighist,"SingleElTight_bjetCR");
  MakeCleverHistograms(sighist,"SingleElLoose_CR");
  MakeCleverHistograms(sighist,"SingleElLoose_bjetCR");
  MakeCleverHistograms(sighist,"SingleEl_promptCR");
  MakeCleverHistograms(sighist,"SingleEl_promptbjetCR");
}


void HNDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void HNDiElectron::ExecuteEvents()throw( LQError ){

  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  FillEventCutFlow("NoCut",1.);

  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  
  /// Trigger List 
  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  //if(!PassTrigger(triggerslist, prescale)) return;
  
  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale
  
  //FillEventCutFlow("TriggerCut", weight);
  m_logger << DEBUG << "passedTrigger "<< LQLogger::endmsg;
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillEventCutFlow("VertexCut", 1.);
  
  
  /// Correct MC for pileup   
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  m_logger << DEBUG << "reweighted pileup "<< LQLogger::endmsg;

  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   
  
  /// JETS
  // Jets needed now for electron loose and tight collection:
  /// veto electrons close to a bjet in loose+ tight samples
  /// 15-50 % of fake electrons in mc have close bjet while < 0.5 % of signal electrons do

  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->Selection(jetColl);
  

  /// ELECTRONS
  std::vector<snu::KElectron> _electronAnalysisColl;
  
  if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronAnalysisColl, jetColl);
  //if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelection(_electronAnalysisColl);
  else eventbase->GetElectronSel()->HNTightElectronSelection(_electronAnalysisColl, jetColl, false);
  
  /// Get Prompt electrons/CF 
  /// As of July 20:New cuts on tight electrons:
  //Remove electrons close to a jet that looks like a real jet.
  ///Use default isolation for 10-20 GeV electrons (0.07%)
  // Add non PF isolation (30% reduction in fakes: 3% reduction in signal)
  std::vector<snu::KElectron> electronAnalysisColl_temp =  GetTruePrompt(_electronAnalysisColl, false, false); // removes CF and fake in mc
  std::vector<snu::KElectron> electronAnalysisColl =ShiftElectronEnergy(electronAnalysisColl_temp, k_running_chargeflip);
  
  
  /// Electrons used for veto (LOOSEST IN ANALYSIS)
  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);
  
  std::vector<snu::KElectron> _electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronLooseColl, jetColl, false);
  /// Loose electron sample (tight  - iso + looseiso) this removes fake el from jet/photon
  std::vector<snu::KElectron>  electronLooseColl = GetTruePrompt(_electronLooseColl, false, false);
  
  
  std::vector<snu::KElectron>  electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  std::vector<snu::KElectron>  electronPtEtaNoCutColl;
  eventbase->GetElectronSel()->SetPt(20.);
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->Selection(electronPtEtaNoCutColl);


  /// MUONS
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl,false);
  std::vector<snu::KMuon> muonNoCutColl;
  eventbase->GetMuonSel()->Selection(muonNoCutColl);

  
  // Loos at d0 and isolation of electrons that are really photons mis reconstructed
  std::vector<snu::KElectron>  fakeElectronSample;
  if(SameCharge(electronNoCutColl)){
    if(!(electronNoCutColl.at(0).GetType()== 0 || electronNoCutColl.at(0).GetType()== 7 )) {
      if(isData) {
	if(electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(0));
      }
      else fakeElectronSample.push_back(electronNoCutColl.at(0));
      
      if(electronNoCutColl.at(0).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()), weight  , 0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(0).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else {
      FillHist("W_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt())  ,weight  , 0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(0).dxy())  ,weight  ,0., 0.1, 100);
    }

    if(!(electronNoCutColl.at(1).GetType()== 0 || electronNoCutColl.at(1).GetType()==7 )) {
      if(isData) {
        if(electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(1));
      } 
      else fakeElectronSample.push_back(electronNoCutColl.at(1));
      if(electronNoCutColl.at(1).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
      }
    }
    else{
      FillHist("W_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , weight  ,0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , weight  ,0., 0.1, 100);
    }
  }



  /// JETS
  std::vector<snu::KJet> jetColl_lepveto;
  std::vector<snu::KJet> jetColl_lepveto_mva;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, muonNoCutColl, electronNoCutColl);
  // jetColl_lepveto have no pileup mva applied
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonVetoColl, electronLooseColl);
  /// Jets used in analysis
  eventbase->GetJetSel()->JetHNSelection(jetColl_lepveto_mva, muonVetoColl, electronLooseColl);


  ///// count number of bjets in the event (using cvs medium WP)
  int nbjet=0;
  for(unsigned int ij=0; ij <jetColl_lepveto_mva.size(); ij++){
    if(jetColl_lepveto_mva.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }

  /// Check the jets close to the electrons we will use
  CheckJetsCloseToLeptons(electronVetoColl, jetColl, "vetoel");
  CheckJetsCloseToLeptons(electronLooseColl, jetColl, "looseel");
  CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "tightel");



  // Remove overlapping particles only need electron overlap in ee channel
  for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
    for(std::vector<snu::KElectron>::iterator it2 = it+1; it2 != electronLooseColl.end(); it2++){
      if(it->DeltaR(*it2) < 0.5) return;
    }
  }
  
  
  /// makes full set of plots for el/mu/jets/met with no cuts applied on objects 
  FillCLHist(sighist, "NoCut", eventbase->GetEvent(), muonNoCutColl,electronNoCutColl,jetColl, weight);
  FillCLHist(sighist, "NoCutPtEta",  eventbase->GetEvent(), muonNoCutColl, electronPtEtaNoCutColl,jetColl_lepveto_mva, weight);
  FillCLHist(sighist, "Fake", eventbase->GetEvent(), muonNoCutColl,fakeElectronSample,jetColl, weight);
  std::vector<snu::KElectron>  electronPtEtaCutColl;

  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;

    electronPtEtaCutColl.push_back(electronNoCutColl[iel]);
  }
  
  std::vector<snu::KElectron>  electronTight_NoIsoCutColl;

  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
                if( egamma_ep          <= 0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
                          if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                            electronTight_NoIsoCutColl.push_back(electronNoCutColl.at(iel));
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    else {
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
                if( egamma_ep          <=0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
                          if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                            electronTight_NoIsoCutColl.push_back(electronNoCutColl.at(iel));
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }


  std::vector<snu::KElectron>  electron_analysisCutColl;
  std::vector<snu::KElectron>  electron_analysisNPFCutColl;
  std::vector<snu::KElectron>   electronTight_DeltaEta;
  std::vector<snu::KElectron>   electronTight_DeltaPhi;
  std::vector<snu::KElectron>   electronTight_SigmaIEta;
  std::vector<snu::KElectron>   electronTight_DZ;
  std::vector<snu::KElectron>   electronTight_HoverE;
  std::vector<snu::KElectron>   electronTight_convfit;
  std::vector<snu::KElectron>   electronTight_ep;
  std::vector<snu::KElectron>   electronTight_missinghit;
  std::vector<snu::KElectron>   electronTight_convphoton;
  std::vector<snu::KElectron>   electronTight_DXY;
  std::vector<snu::KElectron>   electronTight_chargeconst;
  std::vector<snu::KElectron>   electronTight_tightref;
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;
    
    
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_tightref.push_back(electronNoCutColl.at(iel));
	if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
	  electronTight_DeltaEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
	  electronTight_DeltaPhi.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
	  electronTight_SigmaIEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	  electronTight_DZ.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
	  electronTight_HoverE.push_back(electronNoCutColl.at(iel));
	}
	if( egamma_ep          <= 0.05){
	  electronTight_ep.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
	  electronTight_convfit.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].MissingHits()    <=  0){
	  electronTight_missinghit.push_back(electronNoCutColl.at(iel));
	}
	if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
	  electronTight_convphoton.push_back(electronNoCutColl.at(iel));
	}
	
	if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
          electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
        }
      }
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_DXY.push_back(electronNoCutColl.at(iel));
      }	
      
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
                if( egamma_ep          <= 0.05){
		  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl[iel].MissingHits()    <=  0){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			    
			    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
			    int ifid=0;
			    if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
			    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
			    else ifid = 6;

			    float LeptonRelIsoDR03(0.);
			    float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);

			    if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
			    else LeptonRelIsoDR03 = -999.;

			    float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
			    float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
			    float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
			    bool passNPFiso = true;
			    if(trkiso > 0.1) passNPFiso = false;
			    if(ecaliso > 0.2) passNPFiso = false;
			    if(hcaliso > 0.1)  passNPFiso = false;

			    float isocut= 0.09;
			    if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
			    if(LeptonRelIsoDR03 < isocut){
			      electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
			      if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
    else {
      if(iel ==0){
	if(electronNoCutColl[iel].Pt() < 20.) continue;
      }
      else{
	if(electronNoCutColl[iel].Pt() < 15.) continue;
      }
      if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;

      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_tightref.push_back(electronNoCutColl.at(iel));

	if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	  electronTight_DeltaEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
	  electronTight_DeltaPhi.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
	  electronTight_SigmaIEta.push_back(electronNoCutColl.at(iel));
	}
	if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	  electronTight_DZ.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
	  electronTight_HoverE.push_back(electronNoCutColl.at(iel));
	}
	if( egamma_ep          <=0.05){
	  electronTight_ep.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
	  electronTight_convfit.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl[iel].MissingHits()    <=  0){
	  electronTight_missinghit.push_back(electronNoCutColl.at(iel));
	}
	if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
	  electronTight_convphoton.push_back(electronNoCutColl.at(iel));
	}
	if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
	  electronTight_chargeconst.push_back(electronNoCutColl.at(iel));
	}
      }
      if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
	electronTight_DXY.push_back(electronNoCutColl.at(iel));
      }

      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
                if( egamma_ep          <=0.05){
                  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl[iel].MissingHits()    <=  0){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){

                            Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
                            int ifid=0;
                            if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
                            else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
                            else ifid = 6;

                            float LeptonRelIsoDR03(0.);
                            float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);

                            if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
                            else LeptonRelIsoDR03 = -999.;

                            float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
                            float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
                            float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
                            bool passNPFiso = true;
                            if(trkiso > 0.1) passNPFiso = false;
                            if(ecaliso > 0.2) passNPFiso = false;
                            if(hcaliso > 0.1)  passNPFiso = false;

                            float isocut= 0.09;
                            if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
                            if(LeptonRelIsoDR03 < isocut){
                              electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
                              if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
                            }
                          }
			}
		      }
                    }
                  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  std::vector<snu::KElectron>  electron_IsoCutColl;
  std::vector<snu::KElectron>  electron_NPFIsoCutColl;
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid=0;
    if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.0) ifid = 0;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 1.479) ifid = 1;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.0) ifid = 2;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.2) ifid = 3;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.3) ifid = 4;
    else if (fabs(electronNoCutColl.at(iel).SCEta()) < 2.4) ifid = 5;
    else ifid = 6;

    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);
    
    if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
    else LeptonRelIsoDR03 = -999.;

    float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
    float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
    float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
    bool passNPFiso = true;
    if(trkiso > 0.1) passNPFiso = false;
    if(ecaliso > 0.2) passNPFiso = false;
    if(hcaliso > 0.1)  passNPFiso = false;
    
    float isocut= 0.09;
    if(electronNoCutColl.at(iel).Pt()< 20.) isocut=0.07;
    if(LeptonRelIsoDR03 < isocut){
      electron_IsoCutColl.push_back(electronNoCutColl.at(iel));
      if(passNPFiso)       electron_NPFIsoCutColl.push_back(electronNoCutColl.at(iel));
      
    }
  }
  
  FillHist("electronRef", 1.,weight, 0.,2.,2);
  if(SameCharge(electronPtEtaCutColl))   FillHist("electronPtEtaCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electronTight_NoIsoCutColl))   FillHist("electron_NoIsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_IsoCutColl))   FillHist("electron_IsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_NPFIsoCutColl))   FillHist("electron_NPFIsoCutColl", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl))   FillHist("electron_analysisCutColll", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisNPFCutColl))   FillHist("electron_analysisNPFCutColll", 1.,weight, 0.,2.,2);
  if(jetColl_lepveto_mva.size()  > 1) FillHist("JetSelection", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl) && jetColl_lepveto_mva.size()  > 1)  FillHist("PreSelection", 1.,weight, 0.,2.,2);
  if(SameCharge(electron_analysisNPFCutColl) && jetColl_lepveto_mva.size()  > 1)  FillHist("PreSelectionNPF", 1.,weight, 0.,2.,2);
  
  if(SameCharge(electronTight_tightref)){
    FillHist("electronTight_tightref", 1., weight, 0.,2.,2);
    if(SameCharge(electronTight_DeltaEta))   FillHist("electron_DeltaEta", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DeltaPhi))   FillHist("electron_DeltaPhi", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_SigmaIEta))   FillHist("electron_SigmaIEta", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DZ))   FillHist("electron_DZ", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_HoverE))   FillHist("electron_HoverE", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_convfit))   FillHist("electron_convfit", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_ep))   FillHist("electron_ep", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_missinghit))   FillHist("electron_missinghit", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_convphoton))   FillHist("electron_convphoton", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_DXY))   FillHist("electron_DXY", 1.,weight, 0.,2.,2);
    if(SameCharge(electronTight_chargeconst))   FillHist("electron_chargeconst", 1.,weight, 0.,2.,2);
  }


  /// Apply electron SFs for tight id
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronAnalysisColl.begin(); it != electronAnalysisColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }
  m_logger << DEBUG << "Analysis part: "<< LQLogger::endmsg;


  //// WZ/ZZ CR : validate our main prompt bkgs      
  if(PassTrigger(triggerslist, prescale)){
    ///_electronAnalysisColl  has no truth matching applied (since we have no fake bkg estimate for trilepton events)
    if(_electronAnalysisColl.size() ==  3 && (muonVetoColl.size()== 0)) {
      
      m_logger << DEBUG << "Number of jets in tri electron event = " << jetColl_lepveto_mva.size() << LQLogger::endmsg;
      
      float charge1 = _electronAnalysisColl.at(0).Charge();
      float charge2 = _electronAnalysisColl.at(1).Charge();
      float charge3 = _electronAnalysisColl.at(2).Charge();
      
      /// Find os pair
      snu::KParticle osee;
      if(charge1 != charge2) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(1);
      if(charge1 != charge3) osee= _electronAnalysisColl.at(0) + _electronAnalysisColl.at(2);
      if(charge2 != charge3) osee= _electronAnalysisColl.at(1) + _electronAnalysisColl.at(2);
      
      if(jetColl_lepveto_mva.size() > 1){
	if(eventbase->GetEvent().PFMET() > 30){
	  if(fabs(osee.M() - 90.) < 10) FillCLHist(sighist, "TriElCR", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
      
      if(fabs(osee.M() - 90.) < 10){
	FillCLHist(sighist, "TriEl", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      
      if(jetColl_lepveto_mva.size() > 1){
        if(eventbase->GetEvent().PFMET() > 30){
	  FillCLHist(sighist, "TriEl_jetmva_inclusive", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
	}
      }
    }
    if(_electronAnalysisColl.size() ==  4 && (muonVetoColl.size()== 0))FillCLHist(sighist, "ZZ", eventbase->GetEvent(), muonTightColl,_electronAnalysisColl,jetColl_lepveto_mva, weight);
  }

  
  /// single lepton CR
  if(electronAnalysisColl.size() ==1){
    std::vector<TString> triggerslist17jet;
    triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

    std::vector<TString> triggerslist8jet;
    triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
    
    bool pass_eljettrig= false;
    float prescale_trigger = 0.;
    if(electronAnalysisColl.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger = (16.95) / 19789 ; //// 20 + GeV bins
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger = (3.546650) / 19789 ;
        pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    
    if(k_isdata) prescale_trigger=1.;

    bool Zveto=false;
    if(electronVetoColl.size() == 2) {
      if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
	snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
        if(Z.M() > 76. && Z.M() < 106.) Zveto=true;
      }
    }
    if(!Zveto && pass_eljettrig){
      Double_t MT=0;
      Double_t METdphi=0;
      for(unsigned int w = 0; w < electronAnalysisColl.size() ;  w++){
	METdphi = TVector2::Phi_mpi_pi(electronAnalysisColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
	MT = sqrt(2.* electronAnalysisColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
      }
      
      float weight_pu=weight;
      if(k_running_nonprompt){
	
	bool closebjet=false;
	bool closenoejet=false;
	bool closephjet=false;
	for(unsigned int ijet =0 ; ijet <jetColl.size() ; ijet++){
	  for(unsigned int iel=0 ; iel < electronAnalysisColl.size() ; iel++){

	    float dphi =fabs(TVector2::Phi_mpi_pi(electronAnalysisColl.at(iel).Phi()- jetColl.at(ijet).Phi()));
	    if( dphi < 0.4){
	      if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	    }
	    if( electronAnalysisColl[iel].DeltaR(jetColl.at(ijet)) < 0.4){
	      if(jetColl.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	      if(jetColl.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	    }
	  }
	}
	
	TString cut="20";

	float ee_weight =  Get_DataDrivenWeight_E(electronAnalysisColl, jetColl,jetColl_lepveto_mva, jetColl_lepveto_mva.size(),nbjet, eventbase->GetEvent().JetRho(),  0.01,0.09,0.09,true,true,true,cut, false);
	float ee_weight_pucorr =  Get_DataDrivenWeight_E(electronAnalysisColl, jetColl, jetColl_lepveto_mva, jetColl_lepveto_mva.size(),nbjet, eventbase->GetEvent().JetRho(),  0.01,0.09,0.09,true,true,true,cut, true);
	weight=ee_weight;
	weight_pu = ee_weight_pucorr;
	
      }

      if(eventbase->GetEvent().PFMET() < 20.){
	if(jetColl_lepveto_mva.size() > 0){
	  FillCLHist(sighist, "SingleEl_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(nbjet > 0)  FillCLHist(sighist, "SingleEl_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  if(IsTight(electronAnalysisColl.at(0),  jetColl, eventbase->GetEvent().JetRho())) {
	    FillCLHist(sighist, "SingleElTight_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	    if(nbjet > 0)  FillCLHist(sighist, "SingleElTight_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	  else{
	    FillCLHist(sighist, "SingleElLoose_CR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
            if(nbjet > 0)  FillCLHist(sighist, "SingleElLoose_bjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger);
	  }
	}/// NON INCLUSIVE JET
      }/// LOW MET SCR
      
      if(jetColl_lepveto_mva.size() > 0){
	if(eventbase->GetEvent().PFMET() > 30.){
	  float dphiel = TVector2::Phi_mpi_pi(electronAnalysisColl.at(0).Phi()- eventbase->GetEvent().PFMETphi());
	  float MTel = sqrt(2.* electronAnalysisColl.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphiel)));
	  if((MTel < 100.) && (MTel  > 60.)){
	    FillCLHist(sighist, "SingleEl_promptCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	    if(nbjet > 0)  FillCLHist(sighist, "SingleEl_promptbjetCR", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, prescale_trigger*weight);
	  }
	}
      }
    }
  }

  // Require now dilepton trigger passed
  if(!PassTrigger(triggerslist, prescale)) return;

  //// if the trigger that fired the event is prescaled you can reweight the event accordingly using the variable prescale

  FillEventCutFlow("TriggerCut", 1.);
  
  if(jetColl_lepveto_mva.size() > 2){
    if(SameCharge(electron_analysisCutColl)) FillHist("TightSelection", 0 , weight, 0.,2.,2);
    if(SameCharge(electronAnalysisColl))  FillHist("TightSelection", 1 , weight, 0.,2.,2);
    
    if(LowMassCheckSignalRegion(electron_analysisCutColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionLM", 0 , weight, 0.,2.,2);
    if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ) FillHist("TightSelectionLM",1,  weight, 0.,2.,2);
  }

  /// Require 2 analysis electrons (20/15) GeV
  if(electronAnalysisColl.size() != 2 ) return;
  if(electronAnalysisColl.at(0).Pt() < 20.) return;
  if(electronAnalysisColl.at(1).Pt() < 15.) return;

  snu::KParticle ee = electronAnalysisColl.at(0) + electronAnalysisColl.at(1);
  if(ee.M()  < 10.) return;
  FillEventCutFlow("DiEl",1.);
  
 
  // TOP Control region os/SS    
  if(nbjet == 2){
    if(eventbase->GetEvent().PFMET() > 30.){
      if(electronAnalysisColl.size() ==2){
	if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()){
	  FillHist("OSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
	else{
	  FillHist("SSTopCR", jetColl_lepveto_mva.size(),weight, 0.,10.,10);
	}
      }
    }
  }
  
  /// For CF use OS data and weight using CF rates from sunny
  if(k_running_chargeflip) {
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) {
      float cf1=  CFRate(electronAnalysisColl.at(0));
      float cf2=  CFRate(electronAnalysisColl.at(1));

      weight *=  ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    else return;
  }// cf requirement
  else {
    if ((electronVetoColl.size() + muonVetoColl.size()) == 2){
      if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) FillCLHist(sighist, "OSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    }
    
    if(electronAnalysisColl.at(0).Charge() != electronAnalysisColl.at(1).Charge()) return;
  }
  


  
  ///// NOW OS event is weighted for CF sample

  FillEventCutFlow("SSDiEl",1.);
  FillHist("SSee_nloose_el",electronVetoColl.size()  , weight, 0.,5.,5);
  FillHist("SSee_nloose_mu",muonVetoColl.size()  , weight, 0.,5.,5);

  /// Remove events with 3 veto leptons
  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;  
  if(muonVetoColl.size() !=0) return;
  
  if(muonTightColl.size() != 0) {
    cout << "Number of muons (tight = " << muonTightColl.size() << endl;
    cout << "Number of muons veto = " << muonVetoColl.size() << endl;
    cout << "Number of el veto = " << electronVetoColl.size() << endl;
    cout << "Number of el tight = " << electronAnalysisColl.size() << endl;
  }
  FillEventCutFlow("SS_lepveto",1.);
  
  FillCLHist(sighist, "SSloose", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  float ee_weight_20_nor= weight;
  float ee_weight_40_nor= weight;
  
  float ee_weight_30_0905_nor= weight;

  /// before third lepton veto no fake estimate can be done.
  if(k_running_nonprompt){
    
    if(SameCharge(electronAnalysisColl)){
      if(nbjet==0){
	if(jetColl_lepveto_mva.size() > 1) {
	  for(unsigned int ilooseel=0; ilooseel < electronAnalysisColl.size(); ilooseel++){
	    bool awayjet=false;
	    bool closebjet =false;
	    if(!IsTight(electronAnalysisColl.at(ilooseel), jetColl, eventbase->GetEvent().JetRho())){
	      for(unsigned int ijet=0; ijet < jetColl.size(); ijet++){
		if( electronAnalysisColl.at(ilooseel).DeltaR(jetColl.at(ijet)) < 0.4){
		  /// Jet usually vetoe
		  FillHist(("closejet_looseobject_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet_looseobject_ptdiff"),(jetColl.at(ijet).Pt() - electronAnalysisColl.at(ilooseel).Pt())/ jetColl.at(ijet).Pt() , weight, -1.,1.,50);
		  
		}
		float dphielloose = TVector2::Phi_mpi_pi(electronAnalysisColl.at(0).Phi()- jetColl.at(ijet).Phi());
		if(fabs(dphielloose) > 2.5) {
		  if(!awayjet)  FillHist(("awayjet_looseobject_pt"),jetColl.at(ijet).Pt(),  weight, 0.,100.,20);
		  awayjet=true;
		}
		if( electronAnalysisColl.at(ilooseel).DeltaR(jetColl.at(ijet)) < 0.4){
		  if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
		}
	      }//jetcoll
	      if(closebjet)  FillHist(("closebjet_looseobject"), 1 ,  weight, 0.,2.,2);
	      else  FillHist(("closebjet_looseobject"), 0 ,  weight, 0.,2.,2);
	      if(!awayjet) FillHist(("awayjet_looseobject_pt"), 0. ,  weight, 0.,100.,20);
	    }//is loose
	  }// ell loose
	}
      }
    }
    
    
    ee_weight_20_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.09,true,false,true,"20",nbjet, SumPt(jetColl_lepveto_mva), false, false, false);
    
    float ee_weight = Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.09,true,false,true,"30",nbjet, SumPt(jetColl_lepveto_mva), false, false, false);

    ee_weight_40_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.09,true,false,true,"40",nbjet, SumPt(jetColl_lepveto_mva), false, false, false);

    ee_weight_30_0905_nor *= Get_DataDrivenWeight_EE(electronAnalysisColl, jetColl,jetColl_lepveto_mva.size(), eventbase->GetEvent().JetRho(), 0.01,0.09,0.09,true,false,true,"30_0905",nbjet, SumPt(jetColl_lepveto_mva), false, false, false);
    
    weight*= ee_weight;
    
    /// END of NP bkg loop
    if(jetColl_lepveto_mva.size() == 0){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
	FillCLHist(sighist, "SSloose0Jet_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
	FillCLHist(sighist, "SSloose0Jet_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    if(jetColl_lepveto_mva.size() == 1){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose1Jet_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose1Jet_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    if(jetColl_lepveto_mva.size() > 1){
      if(IsTight(electronAnalysisColl.at(0), jetColl, eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1), jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_TT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_TT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl ,eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_TL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_TL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0),jetColl,  eventbase->GetEvent().JetRho()) &&  IsTight(electronAnalysisColl.at(1),  jetColl, eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_LT", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_LT_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
      if(!IsTight(electronAnalysisColl.at(0), jetColl,  eventbase->GetEvent().JetRho()) &&  !IsTight(electronAnalysisColl.at(1), jetColl,  eventbase->GetEvent().JetRho())){
        FillCLHist(sighist, "SSloose_LL", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, 1);
        FillCLHist(sighist, "SSloose_LL_w", eventbase->GetEvent(), muonTightColl, electronAnalysisColl,jetColl_lepveto_mva, weight);
      }
    }
    
  }
    
  FillCLHist(sighist, "SSee", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  else FillCLHist(sighist, "SSee_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

  if(jetColl_lepveto_mva.size() == 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_0jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  if(jetColl_lepveto_mva.size() == 1){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_1jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    else FillCLHist(sighist, "SSee_1jet_Z", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(jetColl_lepveto_mva.size() != 0){
    if(!Zcandidate(electronAnalysisColl, 20., false)) FillCLHist(sighist, "SSee_gt0jet_noZ", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  }
  
  if(ee.M() > 100.){
    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);

    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet_20_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_20_nor);
    if(jetColl_lepveto_mva.size() ==1) FillCLHist(sighist, "SSee_1jet_40_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_40_nor);
  }
  
  if(jetColl_lepveto_mva.size() < 2) return;
  

  FillCLHist(sighist, "SSee_DiJet", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  FillCLHist(sighist, "SSee_DiJet_20_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_20_nor);
  FillCLHist(sighist, "SSee_DiJet_40_nor", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_40_nor);
  
  
  //// Low Mass Signal region
  if(LowMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto, k_running_chargeflip) ) {
    FillCLHist(sighist, "LowMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, weight);
    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso) FillCLHist(sighist, "LowMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto, ee_weight_30_0905_nor);
    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "lowmass");
  }
  
  if(MidMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    FillCLHist(sighist, "MediumMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    
    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso)  FillCLHist(sighist, "MediumMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, ee_weight_30_0905_nor);
    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "midmass");
  }
  if(HighMassCheckSignalRegion(electronAnalysisColl, jetColl_lepveto_mva, k_running_chargeflip) ){
    FillCLHist(sighist, "HighMassRegion", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    bool hasendcap_highiso=false;
    if(fabs(electronAnalysisColl.at(0).Eta() > 1.5)) {
      if(electronAnalysisColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(0).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(fabs(electronAnalysisColl.at(1).Eta() > 1.5)) {
      if(electronAnalysisColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronAnalysisColl.at(1).Pt())> 0.05)  hasendcap_highiso=true;
    }
    if(!hasendcap_highiso)FillCLHist(sighist, "HighMassRegion_0905", eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,ee_weight_30_0905_nor);

    CheckJetsCloseToLeptons(electronAnalysisColl, jetColl, "highmass");
  }
  
  
  if((nbjet!=0))   {
    FillCLHist(sighist, "BJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    FillCLHist(sighist, "BJetCR_20_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,  ee_weight_20_nor);
    FillCLHist(sighist, "BJetCR_40_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,  ee_weight_40_nor);
  }

  if((nbjet==0) && (eventbase->GetEvent().PFMET() > 50.)) {
    FillCLHist(sighist, "HighMETCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
    FillCLHist(sighist, "HighMETCR_20_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,   ee_weight_20_nor);
    FillCLHist(sighist, "HighMETCR_40_nor",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva,   ee_weight_40_nor);
  }

  if((nbjet!=0) || (eventbase->GetEvent().PFMET() > 50.)) FillCLHist(sighist, "HighMETBJetCR",eventbase->GetEvent(), muonTightColl,electronAnalysisColl,jetColl_lepveto_mva, weight);
  
  
  
  bool no_emuoverlap= true;
  for(unsigned int i=0; i < electronAnalysisColl.size() ; i++){
    for(unsigned int j=0; j < muonTightColl.size() ; j++){
      float dR =  electronAnalysisColl[i].DeltaR(muonTightColl[j]);
      if(dR < 0.1) no_emuoverlap= false;
    }
  }
  
  
  
  return;
}// End of execute event loop

void HNDiElectron::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(electrons.size() != 2 ) return ;
  if(electrons.at(0).Pt() < 20.) return ;
  if(electrons.at(1).Pt() < 15.) return ;
  if(!SameCharge(electrons)) return ;
  if(jets.size() < 2) return ;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return ;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(eejj.M()  > 200.) return ;

  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return ;
  if(jj.M() < 40.) return ;

  if(ee.M() > 80.) return ;
  if(eventbase->GetEvent().PFMET() > 35.) return ;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return;

  if(name.Contains("iso_d0")) FillIsoCutFlow(name.Data(),w);
  else FillCutFlow(name.Data(),w);

}


 bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip , float pt2, float pt1, float eemin, float eemax, float jjmin, float jjmax, float eejjmin, float eejjmax, float e1jjmin, float e1jjmax, float e2jjmin, float e2jjmax, float metmax, float mtmax, float stmin, float stmax, bool removeZ, bool removerej){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < pt1) return false;
  if(electrons.at(1).Pt() < pt2) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  if(mass < eemin) return false;
  if(mass > eemax) return false;
  if(removeZ) {
    if(fabs(mass-90.) < 10.) return false;
  }
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }

  // get dR el jet
  float drej1=1000.;
  float drej2=1000.;
  for(unsigned int ij=0; ij < jets.size(); ij++){
    if(jets.at(ij).DeltaR(electrons.at(0)) < drej1)  drej1 = jets.at(ij).DeltaR(electrons.at(0) );
    if(jets.at(ij).DeltaR(electrons.at(1)) < drej2)  drej2 = jets.at(ij).DeltaR(electrons.at(1) );
  }
  if(removerej){
    if(drej1 > 2.)return false;
    if(drej2 > 2.)return false;
  }

  float st=0.;
  for(unsigned int ij=0; ij < jets.size(); ij++){
    st+= jets.at(ij).Pt();
  }
  st+=electrons.at(0).Pt();
  st+=electrons.at(1).Pt();
  st+= eventbase->GetEvent().PFMET();

  if(st < stmin)  return false;
  if(st > stmax)  return false;

  
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > jjmax) return false;
  if(jj.M() < jjmin) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M()  > eejjmax) return false;
  if(eejj.M()  < eejjmin) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e1jj.M() > e1jjmax) return false;
  if(e1jj.M() < e1jjmin) return false;

  snu::KParticle e2jj = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e2jj.M() > e2jjmax) return false;;
  if(e2jj.M() < e2jjmin) return false;;
  
  if(eventbase->GetEvent().PFSumET() < 200.) return false;;
  if(eventbase->GetEvent().PFSumET() > 1500.) return false;;

  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;

  if(eventbase->GetEvent().PFMET() > metmax) return false;

  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));

  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > mtmax) return false;
  if(MT2 > mtmax) return false;


  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;

}

bool HNDiElectron::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(ee.M() > 150.) return false;
  
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
	wmassjj = fabs(jjtmp.M() - 80.4);
	indexj1=ij;
	indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 150.) return false;
  if(jj.M() < 40.) return false;
  
  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M()  > 200.) return false;

  snu::KParticle eej1 = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(eej1.M() > 160.) return false;

  snu::KParticle eej2 = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(eej2.M() > 120.) return false;;

  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;
  if(jets.at(0).DeltaR(jets.at(1)) > 3.5) return false;
  
  if(eventbase->GetEvent().PFMET() > 40.) return false;
  
  
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
  
}

bool HNDiElectron::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 15.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 300.) return false;;
  if(eventbase->GetEvent().PFSumET() > 2000.) return false;;


  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
	indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);

  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;


  snu::KParticle e2jj = electrons.at(1) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(e2jj.M() > 250.) return false;;
  
  


  if(electrons.at(0).DeltaR(electrons.at(1)) < 0.6) return false;
  if(electrons.at(0).DeltaR(electrons.at(1)) > 3.5) return false;

  if(jets.at(0).DeltaR(jets.at(1)) > 3.) return false;

  float dphi1 = TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().PFMETphi());
  float MT1 = sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi1)));

  float dphi2 = TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().PFMETphi());
  float MT2 = sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi2)));
  if(MT1 > 100.) return false;
  if(MT2 > 100.) return false;

  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 50.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(eventbase->GetEvent().PFSumET() < 400.) return false;;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij < jets.size(); ij++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 110.) return false;
  if(jj.M() < 50.) return false;

  if(eventbase->GetEvent().PFMET() > 40.) return false;
  if(jets.at(0).DeltaR(jets.at(1)) > 2.5) return false;

  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



void HNDiElectron::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() ==2  && jets.size() > 1) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){

	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.4){
	      FillHist(("closejet" + name + "_ptdiff").Data(), (jets.at(ijet).Pt() - electrons.at(iel).Pt()) /  jets.at(ijet).Pt(), weight, -1. , 1., 50);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet").Data(), 1, weight, 0., 2., 2);
	      else FillHist(("closejet" + name + "_bjet").Data(), 0, weight, 0., 2., 2);
	      /// Jet usually vetoe
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
	      FillHist(("closejet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);
	      FillHist(("closejet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
	      FillHist(("closejet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);

	      
	    }
	    else{
	      FillHist(("awayjet" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
              FillHist(("awayjet" + name + "_ChargedEMEnergyFraction_elpt").Data(),jets.at(ijet).ChargedEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,   20);
              FillHist(("awayjet" + name + "_ChargedHadEnergyFraction_elpt").Data(),jets.at(ijet).ChargedHadEnergyFraction()  , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200,  20);
              FillHist(("awayjet" + name + "_NeutralEMEnergyFraction_elpt").Data(),jets.at(ijet).NeutralEMEnergyFraction() , electrons[iel].Pt(),  weight, 0.,1.,20, 0.,200, 20);

	    }
	  }
	}
      }
    }
  }
  return;
}

void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void HNDiElectron::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");
  
  
  
  return;
  
}

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     

void HNDiElectron::FillEventCutFlow(TString cut, float weight){

  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",6,0.,6.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"SS_lepveto");
  }
  
}

     
void HNDiElectron::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",16,0.,16.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"SS_NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"SS_Tight");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"SS_Tight_convveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"SS_Tight_d0veto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"SS_Tight_reliso");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"SS_Medium_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"SS_Tight_chargeconst");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"SS_Tight_noclosejet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"SS_anal_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"Signal_anal");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"Signal_Tightlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"Signal_Mediumlooseiso_d0");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(13,"Signal_drcut1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(14,"Signal_drcut2");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(15,"Signal_anal_dr1");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(16,"Signal_anal_dr2");
  }
}
     
     
void HNDiElectron::FillIsoCutFlow(TString cut, float weight){
       
  
  if(GetHist("isocutflow")) {
    GetHist("isocutflow")->Fill(cut,weight);
    
  }
  else{
    AnalyzerCore::MakeHistograms("isocutflow",36,0.,36.);
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(1,"iso_d0_03_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(2,"iso_d0_03_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(3,"iso_d0_03_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(4,"iso_d0_03_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(5,"iso_d0_03_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(6,"iso_d0_03_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(7,"iso_d0_03_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(8,"iso_d0_03_iso3_075");
    
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(10,"iso_d0_02_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(11,"iso_d0_02_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(12,"iso_d0_02_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(13,"iso_d0_02_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(14,"iso_d0_02_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(15,"iso_d0_02_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(16,"iso_d0_02_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(17,"iso_d0_02_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(19,"iso_d0_01_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(20,"iso_d0_01_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(21,"iso_d0_01_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(22,"iso_d0_01_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(23,"iso_d0_01_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(24,"iso_d0_01_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(25,"iso_d0_01_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(26,"iso_d0_01_iso3_075");

    GetHist("isocutflow")->GetXaxis()->SetBinLabel(28,"iso_d0_005_iso3_60");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(29,"iso_d0_005_iso3_50");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(30,"iso_d0_005_iso3_40");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(31,"iso_d0_005_iso3_30");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(32,"iso_d0_005_iso3_20");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(33,"iso_d0_005_iso3_10");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(34,"iso_d0_005_iso3_09");
    GetHist("isocutflow")->GetXaxis()->SetBinLabel(35,"iso_d0_005_iso3_075");

    
    
  }
}


void HNDiElectron::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiElectron::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiElectronCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiElectron::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



