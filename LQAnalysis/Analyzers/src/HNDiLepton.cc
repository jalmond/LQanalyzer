// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiLepton Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNDiLepton.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to samevallow inheritance for use in LQCore/core classes
ClassImp (HNDiLepton);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiLepton::HNDiLepton() :  AnalyzerCore(),  out_electrons(0) {
  
  mapcounter.clear();

  _mm_channel=false;
  _ee_channel=false;


  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiLepton");

  Message("In HNDiLepton constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  //InitialiseAnalysis();
  
  
  k_met=0., k_met_st=0, k_mumumass=0., k_lljj_lowmass=0., k_l1jj_lowmass=0., k_l2jj_lowmass=0., k_llj_lowmass=0., k_jj_lowmass=0., k_lljj_highmass=0., k_l1jj_highmass=0., k_l2jj_highmass=0.,k_llj_highmass=0., k_jj_highmass=0.;
  k_st=0., k_ht=0.;
  k_weight=0.;
  k_mu1pt=0., k_mu2pt=0., k_j1pt=0.;
  k_contramass_lowmass=0., k_contramass_highmass=0.;
  k_lldr =0.;
  k_minljdR=0.;
  k_awayjetminDR=0.;
  k_mindRjj=0.;
  k_weight=0.;
  k_njets=0;
  k_nbjet_l=0;
  k_nbjet_m=0;
  k_nbjet_t=0;
  k_nfatjets=0;
  
}


void HNDiLepton::InitialiseAnalysis() throw( LQError ) {
  
  if(k_flags.size() > 0){

    if(k_flags[0] == "CutFlow")  functionality = HNDiLepton::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HNDiLepton::OPT;
    else functionality = HNDiLepton::ANALYSIS;
  }

  
  if(  functionality == HNDiLepton::ANALYSIS){
    /// Initialise histograms
    MakeHistograms();  

    //
    // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
    // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
    //
    
    Message("Making clever hists for Z ->ll test code", INFO);
    
    vector<TString> labels;
    labels.push_back("");
    
    for(unsigned int il = 0; il < labels.size(); il++){
      TString label = labels.at(il);
      MakeCleverHistograms(sighist_mmm,label+"WZMuon");
      MakeCleverHistograms(sighist_mmm,label+"ZZMuon1");
      MakeCleverHistograms(sighist_mmm,label+"ZZMuon2");
      MakeCleverHistograms(sighist_mm, label+"SSMM_Preselection");
      MakeCleverHistograms(sighist_mm, label+"SSPOGMM_Preselection");
      MakeCleverHistograms(sighist_mm, label+"SSMM_1Jet");
      MakeCleverHistograms(sighist_mm, label+"SSMM_1JetOpt");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiTJet");
      MakeCleverHistograms(sighist_mm, label+"SSMM_CR");
      MakeCleverHistograms(sighist_mm, label+"SSMM_LowMass");
      MakeCleverHistograms(sighist_mm, label+"SSMM_MidMass");
      MakeCleverHistograms(sighist_mm, label+"SSMM_HighMass");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_noB");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_FailnoB");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passMET");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passMETST");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passHT");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passDR");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passDR2");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passMT");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passLJ");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passLTHT");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passmll");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passpt2");
      MakeCleverHistograms(sighist_mm, label+"SSMM_DiJet_passpt2mll");
      
      MakeCleverHistograms(sighist_mm, label+"OSMM_Preselection");
      MakeCleverHistograms(sighist_mm, label+"OSMM_1Jet");
      MakeCleverHistograms(sighist_mm, label+"OSMM_DiJet");
      MakeCleverHistograms(sighist_mm, label+"OSMM_CR");
      MakeCleverHistograms(sighist_mm, label+"OSMM_LowMass");
      MakeCleverHistograms(sighist_mm, label+"OSMM_MidMass");
      MakeCleverHistograms(sighist_mm, label+"OSMM_HighMass");
    }
    
    MakeCleverHistograms(sighist_mm, "TriggerTop");
    MakeCleverHistograms(sighist_mm, "TriggerOSZMM");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerTop");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerOSZMM");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerOSMM");
    MakeCleverHistograms(sighist_mm, "DiJetTriggerOSMM");
    
    MakeCleverHistograms(sighist_mm, "TriggerTop_p1");
    MakeCleverHistograms(sighist_mm, "TriggerOSZMM_p1");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerTop_p1");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerOSZMM_p1");
    
    MakeCleverHistograms(sighist_mm, "TriggerTop_p2");
    MakeCleverHistograms(sighist_mm, "TriggerOSZMM_p2");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerTop_p2");
    MakeCleverHistograms(sighist_mm, "DiMuTriggerOSZMM_p2");
    
    MakeCleverHistograms(sighist_mm, "OSZMM");
    
  }
  
  return;
}

void HNDiLepton::DoCutFlow(float w){

  std::vector<snu::KElectron> electrons_veto = GetElectrons(false,false,"ELECTRON_HN_VETO");
  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> jets = GetJets("JET_HN");


  counter("1_NoCut",w);
  std::vector<snu::KMuon> muons = GetMuons("MUON_HN_TIGHT",false);
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :                                                                                                                                                                                                                    
  if((PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))){
    counter( "2_EventClean", w);

    if(muons.size()==2){
      if(muons[1].Pt() > 10){
	if(muons[0].Pt() > 20){
	  counter( "3_DiMu", w);

	  std::vector<snu::KMuon> muons_veto         = GetMuons("MUON_HN_VETO",false);
	  if(muons_veto.size()!=2) {

	    m_logger << INFO  << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
	  }
	    
          if(muons_veto.size() ==2){
            counter("4_MuVeto", w);
            if(electrons_veto.size() ==0){
              counter("5_ElVeto", w);
	      if(GetDiLepMass(muons) > 10.){
		counter("6_mll", w);
		if(jets.size() > 1){
		  counter("7_DiJet", w);
		  CorrectedMETRochester(muons,true);
		  if(eventbase->GetEvent().PFMET()  < 50.){
		    counter("8_MET", w);
		    
		    float dijetmass_tmp=999.;
		    float dijetmass=9990000.;
		    int m=-999;
		    int n=-999;
		    for(UInt_t emme=0; emme<jets.size(); emme++){
		      for(UInt_t enne=1; enne<jets.size(); enne++) {
			if(emme == enne) continue;
			dijetmass_tmp = (jets[emme]+jets[enne]).M();
			if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {
			  dijetmass = dijetmass_tmp;
			  m = emme;
			  n = enne;
			}
		      }
		    }
		    snu::KParticle jj = jets.at(m) + jets.at(n) ;
		    if(jj.M() < 200) {
		      counter("9_mjj", w);
		      
		      int nbjet = NBJet(jets);
		      if(nbjet ==0){
			counter("91_bjetv1", w);
			int nbjetv2 = NBJet(alljets);
			if(nbjetv2 ==0){
			  counter("92_bjetv2", w);
			}
		      }
		    }// mjj
		  }// MET
		}
	      }
	    }
	  }
	}
      }
    }
  }
  

}


void HNDiLepton::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  
  //// Set weight for MC (nevents / xsec (ish))
  if(!isData)weight*= MCweight;


  if(k_flags.size() > 0){
    
    if(k_flags[0] == "CutFlow")  functionality = HNDiLepton::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HNDiLepton::OPT;
    else functionality = HNDiLepton::ANALYSIS;
  }

    
  if(functionality==HNDiLepton::OPT){
    k_met=0., k_met_st=0, k_mumumass=0., k_lljj_lowmass=0., k_l1jj_lowmass=0., k_l2jj_lowmass=0., k_llj_lowmass=0., k_jj_lowmass=0., k_lljj_highmass=0., k_l1jj_highmass=0., k_l2jj_highmass=0.,k_llj_highmass=0., k_jj_highmass=0.;
    k_st=0., k_ht=0.;
    k_weight=0.;
    k_mu1pt=0., k_mu2pt=0., k_j1pt=0.;
    k_contramass_lowmass=0., k_contramass_highmass=0.;
    k_lldr =0.;
    k_minljdR=0.;
    k_awayjetminDR=0.;
    k_mindRjj=0.;
    k_weight=0.;
    k_njets=0;
    k_nbjet_l=0;
    k_nbjet_m=0;
    k_nbjet_t=0;
    k_nfatjets=0;

  }

  
  if(functionality==HNDiLepton::CUTFLOW){
    DoCutFlow(1.); return;
  }
  
  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;
  bool _m_channel =   isData ?  (k_channel.Contains("SingleMuon")) : true ;


  TString id="MUON_HN_TIGHT";
  if(k_running_nonprompt) id="MUON_HN_LOOSE";
  
  
  std::vector<snu::KMuon> muons_test = GetMuons(id,true);
  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",true);
  CorrectedMETRochester(muons_test,true);
  

  /// Set up electrons                                                                                                                                        
  std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
  
  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> tchanjets = GetJets("JET_HN_TChannel");
  
  std::vector<snu::KJet>  jets = GetJetsWFT("JET_HN", "FATJET_HN");
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");
  

  vector<int> ijets;  

  if(functionality==HNDiLepton::OPT){
    
    if(!isData){
      float mc_weight= weight;
      mc_weight*= WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) ;
      
      mc_weight*= mcdata_correction->MuonTrackingEffScaleFactor(muons_test);
      
      float puweight=1.;
      if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
      else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), jets.size());
      mc_weight*= puweight;
      
      double muon_id_iso_sf = mcdata_correction->MuonScaleFactor("MUON_HN_TIGHT", muons_test, 0);
      mc_weight*= muon_id_iso_sf;
      
      double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "elid", muons_test, "MUON_HN_TIGHT", 0, 0, 0);
      double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "elid", muons_test, "MUON_HN_TIGHT", 0, 1, 0);
      float trigger_sf = trigger_eff_Data/trigger_eff_MC;
      mc_weight*= trigger_sf;
      
      weight=mc_weight;

    }

    FillHist("NEvents",1,1., 0., 2., 2);
    FillHist("NEvents_weighted",1, weight, 0., 2., 2);

    if(muons_veto.size() > 2) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    if(!SameCharge(muons_test))     throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    if(jets.size()  < 1 && fatjetcoll.size() ==0 )  throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    if(!PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))  throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    if(electrons_veto.size()>0) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    if(eventbase->GetEvent().PFMET() > 80) throw LQError( "Not Lepton Event",  LQError::SkipEvent );
    

    /// define event variables                                                                                                                                                                                                                              
    snu::KParticle mm = muons_test[0] + muons_test[1];
    
    int nbjet_l=0;
    int nbjet_m=0;
    int nbjet_t=0;
    float ST = muons_test[0].Pt() + muons_test[1].Pt();
    for(unsigned int ij=0; ij <alljets.size(); ij++){
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Loose))  nbjet_l++;
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet_m++;
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Tight))  nbjet_t++;
    }

    if(nbjet_t > 0)     throw LQError( "Not Lepton Event",  LQError::SkipEvent );

    float HT=0.;
    for(unsigned int ij=0; ij <jets.size(); ij++){      ST+= jets[ij].Pt(); HT+= jets[ij].Pt();}
    for(unsigned int ij=0; ij < fatjetcoll.size(); ij++){       ST+=fatjetcoll[ij].Pt();  HT+= fatjetcoll[ij].Pt();}
    ST+=eventbase->GetEvent().PFMET();
    

    bool closejet=false;
    bool closejet2=false;
    float mindR=9999.;
    for(unsigned int im=0; im <muons_test.size(); im++){
      for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
	if(muons_test.at(im).DeltaR(jets.at(ij2)) <  0.5) closejet=true;
	if(muons_test.at(im).DeltaR(jets.at(ij2)) <  mindR){
	  mindR = muons_test.at(im).DeltaR(jets.at(ij2));
	}
      }
    }

    float min_eleadawayjet_Dr= -10000.;
    for(UInt_t i=0; i<muons_test.size(); i++){
      for(UInt_t emme=0; emme<jets.size(); emme++){
	float dR =muons_test[i].DeltaR(jets[emme]);
	if(dR > 0.5) {
	  if(dR > min_eleadawayjet_Dr) {
	    min_eleadawayjet_Dr=  dR;
	    
	  }
	}
      }
    }
    
    float mindRjj=999.;
    
    if(jets.size() > 1){
      for(unsigned int ij=0; ij <jets.size()-1; ij++){
	for(unsigned int ij2=ij+1; ij2 <jets.size(); ij2++){
	  if(jets.at(ij).DeltaR(jets.at(ij2)) < mindRjj) mindRjj=jets.at(ij).DeltaR(jets.at(ij2)) ;
	}
      }
    }
      
    
    k_mu1pt=muons_test[0].Pt();
    k_mu2pt=muons_test[1].Pt();
    if(jets.size() > 0) k_j1pt = jets[0].Pt();

    k_mumumass = mm.M();
    
    k_lljj_lowmass= GetMasses("lljj", muons_test, jets, ijets,true) ;
    k_l1jj_lowmass= GetMasses("l1jj", muons_test, jets, ijets,true) ;
    k_l2jj_lowmass= GetMasses("l2jj", muons_test, jets, ijets,true) ;
    k_llj_lowmass= GetMasses("llj", muons_test, jets, ijets, true) ;
    k_jj_lowmass=GetMasses("jj", muons_test, jets, ijets,true) ;
    k_contramass_lowmass=GetMasses("contMT", muons_test, jets,ijets, true) ;

    
    k_lljj_highmass= GetMasses("lljj", muons_test, jets, ijets,false) ;
    k_l1jj_highmass= GetMasses("l1jj", muons_test, jets, ijets,false) ;
    k_l2jj_highmass= GetMasses("l2jj", muons_test, jets, ijets,false) ;
    k_llj_highmass= GetMasses("llj", muons_test, jets, ijets, false) ;
    k_jj_highmass=GetMasses("jj", muons_test, jets, ijets,false) ;
    k_contramass_highmass=GetMasses("contMT", muons_test, jets,ijets, false) ;


    
    k_st=ST;
    k_met_st= pow(eventbase->GetEvent().PFMET(),2)/ ST;
    k_ht = HT;
    k_met = eventbase->GetEvent().PFMET();
    k_lldr = muons_test[0].DeltaR(muons_test[1]);
    k_minljdR=mindR;
    k_awayjetminDR=min_eleadawayjet_Dr;
    k_mindRjj=mindRjj;
    k_weight=weight;
    k_njets = jets.size();
    k_nfatjets = fatjetcoll.size();
    k_nbjet_l = nbjet_l;
    k_nbjet_m = nbjet_m;
    k_nbjet_t = nbjet_t;
    return;
  }



  if(functionality==HNDiLepton::ANALYSIS){

    
    FillEventCutFlow(0,"NoCut",weight*WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) );
    FillEventCutFlow(4,"NoCut",weight*WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) );


      /// efine event variables                                                                                                                                                  
    snu::KParticle mm;
    if(muons_test.size() ==2) mm= muons_test[0] + muons_test[1];
    int nbjet_l=0;
    int nbjet_m=0;
    int nbjet_t=0;
    float ST (0.);
    if(muons_test.size() ==2)ST= muons_test[0].Pt() + muons_test[1].Pt();
    for(unsigned int ij=0; ij <alljets.size(); ij++){
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Loose))  nbjet_l++;
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet_m++;
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Tight))  nbjet_t++;

    }
    float HT=0.;
    for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
    for(unsigned int ij=0; ij < fatjetcoll.size(); ij++){ HT+= fatjetcoll[ij].Pt(); ST+= fatjetcoll[ij].Pt();}
    ST+=eventbase->GetEvent().PFMET();
   
    
    bool closejet=false;
    bool closejet2=false;
    float mindR=9999.;
    for(unsigned int im=0; im <muons_test.size(); im++){
      for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
	if(muons_test.at(im).DeltaR(jets.at(ij2)) <  0.5) closejet=true;
	if(muons_test.at(im).DeltaR(jets.at(ij2)) <  mindR){
	  mindR = muons_test.at(im).DeltaR(jets.at(ij2));
	}
      }
    }
    float min_eleadawayjet_Dr= -10000.;
    for(UInt_t i=0; i<muons_test.size(); i++){
      for(UInt_t emme=0; emme<jets.size(); emme++){
	float dR =muons_test[i].DeltaR(jets[emme]);
	if(dR > 0.5) {
	  if(dR > min_eleadawayjet_Dr) {
	    min_eleadawayjet_Dr=  dR;

	  }
	}
      }
    }

    float mindRjj=999.;
    if(jets.size() > 1){
      for(unsigned int ij=0; ij <jets.size()-1; ij++){
	for(unsigned int ij2=ij+1; ij2 <jets.size(); ij2++){
	  if(jets.at(ij).DeltaR(jets.at(ij2)) < mindRjj) mindRjj=jets.at(ij).DeltaR(jets.at(ij2)) ;
	}
      }
    }

    
    if(muons_test.size()==2){
      if(muons_test[1].Pt() > 10 && muons_test[0].Pt() > 20 ){

	if(!PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))  return;
	FillEventCutFlow(4,"Trigger",weight*WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) );
	
	counter("Trigger",weight);
	
	if(electrons_veto.size()>0) return;
	
	counter("ElVeto",weight);
	
	FillEventCutFlow(4,"ElVeto",weight*WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) );
	
	/// Apply weights to MC
	
	if(!isData){
	  float mc_weight= weight;
	  mc_weight*= WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi) ;
	  
	  mc_weight*= mcdata_correction->MuonTrackingEffScaleFactor(muons_test);
	  
	  float puweight=1.;
	  if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
	  else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), jets.size());
	  mc_weight*= puweight;
	  
	  double muon_id_iso_sf = mcdata_correction->MuonScaleFactor("MUON_HN_TIGHT", muons_test, 0);
	  mc_weight*= muon_id_iso_sf;
	  
	  double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "elid", muons_test, "MUON_HN_TIGHT", 0, 0, 0);
	  double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "elid", muons_test, "MUON_HN_TIGHT", 0, 1, 0);
	  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
	  mc_weight*= trigger_sf;
	  
	  weight=mc_weight;
	}
	
	
	FillEventCutFlow(4,"DiLooseMM",weight);	
	
	//// weight is now corrected for trigger and ID
	

	if(SameCharge(muons_test)){

	  
	  FillEventCutFlow(4,"SSMMLoose",weight);
	  
	  if((muons_test[0] + muons_test[1]).M()  > 10.) {
	    FillEventCutFlow(4,"MLL",weight);

	    if((muons_test[0].DeltaR(muons_test[1])) > 0.4){
	      FillEventCutFlow(4,"mmdR",weight);

	      if(muons_veto.size() ==2 && electrons_veto.size()==0){
		if(jets.size() >= 2 )   FillEventCutFlow(0,"DiJet",weight);

		//if((hn04jets.size() + fatjetcoll.size()) < 2) return;                                                                                                                                                                                                               
		FillEventCutFlow(4,"LepVeto",weight);


		if(k_running_nonprompt){
		  float iso1=0.07;
		  float iso2=0.07;
		  TString tag1 = "Tight0.07_0.005_3_0.04";
		  TString tag2 = "Tight0.07_0.005_3_0.04";

		  bool cb_1=false;
		  bool cb_2=false;
		  weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons_test, PassID(muons_test[0],"MUON_HN_TIGHT"), PassID(muons_test[1],"MUON_HN_TIGHT"), tag1, tag2,  cb_1, cb_2,"ptcorr_eta", iso1,iso2,false, false);

		}

		FillCLHist(sighist_mm, "SSMM_Preselection", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
		if(jets.size()==1) {
		  FillCLHist(sighist_mm, "SSMM_1Jet", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
		  FillEventCutFlow(4,"SSMM_1Jet",weight);
		  if(GetDiLepMass(muons_test) < 110){
		    if(GetDiLepMass(muons_test) > 15){
		      if(eventbase->GetEvent().PFMET() < 60.) {
			if(NBJet(alljets) ==0){
			  
			
			  if(muons_test[0].DeltaR(muons_test[1])  < 3.4) {
			    if( (GetLT(muons_test)/(SumPt(jets)+SumPt(fatjetcoll)) ) > 0.8){
			      FillEventCutFlow(4,"SSMM_1JetOpt",weight);
			      FillCLHist(sighist_mm, "SSMM_1JetOpt", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
			      if(GetDiLepMass(muons_test) < 60){
				FillCLHist(sighist_mm, "SSMM_1JetOpt2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
				FillEventCutFlow(4,"SSMM_1JetOpt2",weight);
			      }
			      if(muons_test[1].Pt() > 15){
				FillCLHist(sighist_mm, "SSMM_1JetOpt_pt2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
				if(GetDiLepMass(muons_test) < 60)FillCLHist(sighist_mm, "SSMM_1JetOpt2_pt2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
				FillEventCutFlow(4,"SSMM_1JetOpt_pt2",weight);
				if(GetDiLepMass(muons_test) < 60)FillEventCutFlow(4,"SSMM_1JetOpt2_pt2",weight);

			      }
			      
			    }
			  }
			}
		      }
		    }
		  }
		}
		if(jets.size() > 1){
		  FillCLHist(sighist_mm, "SSMM_DiJet", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		  FillEventCutFlow(4,"SSMM_DiJet",weight);
		  
		  if(NBJet(alljets) ==0)                   FillCLHist(sighist_mm, "SSMM_DiJet_noB", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		  else FillCLHist(sighist_mm, "SSMM_DiJet_FailnoB", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		  if(NBJet(alljets) ==0)   {
		    FillEventCutFlow(4,"SSMM_DiJet_noB",weight);



		    if(eventbase->GetEvent().PFMET() < 60.) {
		      FillCLHist(sighist_mm, "SSMM_DiJet_passMET", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);

		    }
		    
		    if((eventbase->GetEvent().PFMET() < 45.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET45",weight);
		    if((eventbase->GetEvent().PFMET() < 50.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET50",weight);
		    if((eventbase->GetEvent().PFMET() < 55.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET55",weight);
		    if((eventbase->GetEvent().PFMET() < 60)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET60",weight);
		    if((eventbase->GetEvent().PFMET() < 65.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET65",weight);
		    if((eventbase->GetEvent().PFMET() < 70.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET70",weight);
		    if((eventbase->GetEvent().PFMET() < 80.)) 		    FillEventCutFlow(4,"SSMM_DiJet_passMET80",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 20.) FillEventCutFlow(4,"SSMM_DiJet_passMETST20",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 15.) FillEventCutFlow(4,"SSMM_DiJet_passMETST15",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 12.5) FillEventCutFlow(4,"SSMM_DiJet_passMETST12_5",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 10.) FillEventCutFlow(4,"SSMM_DiJet_passMETST10",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 7.5) FillEventCutFlow(4,"SSMM_DiJet_passMETST7_5",weight);
		    if(pow(eventbase->GetEvent().PFMET(),2)/(ST) < 17.5) FillEventCutFlow(4,"SSMM_DiJet_passMETST17_5",weight);
		    if((eventbase->GetEvent().PFMET() < 60.)) {
		      FillCLHist(sighist_mm, "SSMM_DiJet_passMETST", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		      if(HT < 300){
			if(HT < 280)FillEventCutFlow(4,"SSMM_DiJet_passHT280",weight);
			if(HT < 260)FillEventCutFlow(4,"SSMM_DiJet_passHT260",weight);
			if(HT < 240)FillEventCutFlow(4,"SSMM_DiJet_passHT240",weight);
			FillEventCutFlow(4,"SSMM_DiJet_passHT300",weight);
			FillCLHist(sighist_mm, "SSMM_DiJet_passHT300", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
			bool closejet=false;
			bool closejet2=false;
			float mindR=9999.;
			for(unsigned int im=0; im <muons_test.size(); im++){
			  for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
			    if(muons_test.at(im).DeltaR(jets.at(ij2)) <  0.5) closejet=true;
			    if(muons_test.at(im).DeltaR(jets.at(ij2)) <  mindR){
			      mindR = muons_test.at(im).DeltaR(jets.at(ij2));
			    }
			  }
			}
			if(mindR > 3.5) closejet2=true;
			if(!closejet){
			  
			  if(muons_test[0].DeltaR(muons_test[1])  < 4.) FillCLHist(sighist_mm, "SSMM_DiJet_passDR", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
			  if(muons_test[0].DeltaR(muons_test[1])  < 3.4) {
			    FillEventCutFlow(4,"SSMM_DiJet_passDR2",weight);

			    FillCLHist(sighist_mm, "SSMM_DiJet_passDR2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);

			    float dphi_1 = fabs(TVector2::Phi_mpi_pi(muons_test.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
			    float MT_1 = sqrt(2.* muons_test.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));

			    float dphi_2 = fabs(TVector2::Phi_mpi_pi(muons_test.at(1).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
			    float MT_2 = sqrt(2.* muons_test.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_2)));

			    //if( ( (muons_test[0].Pt() + muons_test[1].Pt()) / HT ) > 0.25){
			    //FillCLHist(sighist_mm, "SSMM_DiJet_passLTHT", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
			      
			    if(!closejet2){
			      FillEventCutFlow(4,"SSMM_DiJet_passLJ",weight);

			      FillCLHist(sighist_mm, "SSMM_DiJet_passLJ", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
			      if(MT_1 < 100 && MT_2 < 100)                                 FillEventCutFlow(4,"SSMM_DiJet_passMT100",weight);
			      if(MT_1 < 90 && MT_2 < 90)                                 FillEventCutFlow(4,"SSMM_DiJet_passMT90",weight);
			      
			      if(MT_1 < 80 || MT_2 < 80){
				FillEventCutFlow(4,"SSMM_DiJet_passMT80",weight);

				FillCLHist(sighist_mm, "SSMM_DiJet_passMT", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
				if(muons_test[1].Pt() > 15) {
				  FillEventCutFlow(4,"SSMM_DiJet_passpt2",weight);

				  FillCLHist(sighist_mm, "SSMM_DiJet_passpt2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
				}

				int s_awayjetdr(0), s_mll(0), s_pt(0), s_mllj(0), s_met(0), s_l2jj(0), s_lljj(0), s_contraMass(0), s_st(0);
				int nsig_reg=0;
				if(GetDiLepMass(muons_test) < 70) s_mll=1;
				else s_mll=2;
				
				if(muons_test[1].Pt() < 15) s_pt=1;
				else s_pt=2;
				
				if((muons_test[0]+muons_test[1]+jets[0]).M() < 100) s_mllj=1;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 150)  s_mllj=2;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 175)  s_mllj=3;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 200)  s_mllj=4;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 225)s_mllj=5;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 250)s_mllj=6;
				else if((muons_test[0]+muons_test[1]+jets[0]).M() < 300)s_mllj=7;

				if(eventbase->GetEvent().PFMET() < 20)    s_met=1;
				else if(eventbase->GetEvent().PFMET() < 40)    s_met=2;
				else if(eventbase->GetEvent().PFMET() < 60)    s_met=3;
				
				if(ST < 150) s_st=1;
				else if(ST < 175) s_st=2;
				else if(ST < 200) s_st=3;
				else if(ST < 250) s_st=4;
				else s_st=5;
				
				if(GetMasses("l2jj", muons_test, jets, ijets, true) < 80) s_l2jj=1;
				else if(GetMasses("l2jj", muons_test, jets, ijets, true) < 120) s_l2jj=2;
				else if(GetMasses("l2jj", muons_test, jets,  ijets,true) < 200) s_l2jj=3;
				else if(GetMasses("l2jj", muons_test, jets, ijets, true) < 300) s_l2jj=4;
				
				if(GetMasses("lljj", muons_test, jets,  ijets,true) < 100) s_lljj=1;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 150) s_lljj=2;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 175) s_lljj=3;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 200) s_lljj=4;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 250) s_lljj=5;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 300) s_lljj=6;
				else if(GetMasses("lljj", muons_test, jets,  ijets,true) < 400) s_lljj=7;
				
				if(GetMasses("contMT", muons_test, jets,  ijets,true) < 25) s_contraMass=1;
				else 				if(GetMasses("contMT", muons_test, jets,  ijets,true) < 50) s_contraMass=2;
				else 				if(GetMasses("contMT", muons_test, jets,  ijets,true) < 100) s_contraMass=3;

				
				float min_eleadawayjet_Dr= -10000.;
				for(UInt_t i=0; i<muons_test.size(); i++){
				  for(UInt_t emme=0; emme<jets.size(); emme++){
				    float dR =muons_test[i].DeltaR(jets[emme]);
				    if(dR > 0.5) {
				      if(dR > min_eleadawayjet_Dr) {
					min_eleadawayjet_Dr=  dR;
					
				      }
				    }
				  }
				}
				
				if(min_eleadawayjet_Dr < 3.5)  s_awayjetdr=1;
				else  s_awayjetdr=2;
				

				for(unsigned int ipt =1; ipt < 3; ipt++){
                                  for(unsigned int imll =1; imll < 3; imll++){
				    for(unsigned int  illjj =1; illjj < 8; illjj++){
				      for(unsigned int imet=1; imet< 4; imet++,nsig_reg++){
					if(s_mll ==imll){
					  if(s_pt==ipt){
					    if(s_lljj==illjj){
					      if(s_met==imet){
						FillHist("Sig_Regions1",nsig_reg, weight, 0., 90., 90);
					      }
					    }
					  }
					}
				      }
				    }
				  }
				}

				nsig_reg=0;
				for(unsigned int ipt =1; ipt < 3; ipt++){
                                  for(unsigned int imll =1; imll < 3; imll++){
				    for(unsigned int i_cm=1; i_cm < 4; i_cm++){
				      for(unsigned int i_st=1; i_st < 6; i_st++,nsig_reg++){
					if(s_mll ==imll){
                                          if(s_pt==ipt){
					    if(s_st==i_st){
					      if(s_contraMass==i_cm){
                                                FillHist("Sig_Regions2",nsig_reg, weight, 0., 90., 90);
					      }
					    }
					  }
					}
				      }
				    }
				  }
				}
				nsig_reg=0;
                                for(unsigned int ipt =1; ipt < 3; ipt++){
                                  for(unsigned int imll =1; imll < 3; imll++){
				    for(unsigned int iaj =1; iaj < 3; iaj++){
				      for(unsigned int imet=1; imet< 4; imet++, nsig_reg++){
					for(unsigned int i_cm=1; i_cm < 4; i_cm++){
					  
					  //for(unsigned int i_llj=0; i_llj < 4; i_llj++, nsig_reg++){
					  if(s_mll ==imll){
					    if(s_awayjetdr==iaj){
					      if(s_pt==ipt){
						if(s_met==imet){
						  if(s_contraMass==i_cm){
						    
						    FillHist("Sig_Regions3",nsig_reg, weight, 0., 90., 90);
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
				
				if(GetDiLepMass(muons_test) < 70){
				  FillEventCutFlow(4,"SSMM_DiJet_passmll",weight);
				  
				  FillCLHist(sighist_mm, "SSMM_DiJet_passmll", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);   
				  if(muons_test[1].Pt() > 15) {
				    FillEventCutFlow(4,"SSMM_DiJet_passpt2mll",weight);
				    
				    FillCLHist(sighist_mm, "SSMM_DiJet_passpt2mll", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
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
		
		
		
		if(tchanjets.size()> 1)FillCLHist(sighist_mm, "SSMM_DiTJet", eventbase->GetEvent(), muons_test, electrons_veto,tchanjets, alljets,  fatjetcoll,weight);
		
		if(CheckSignalRegion(true,muons_test,electrons_veto , jets, alljets,"Low", weight))FillCLHist(sighist_mm, "SSMM_LowMass", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		if(CheckSignalRegion(true,muons_test,electrons_veto , jets, alljets,"", weight))FillCLHist(sighist_mm, "SSMM_MidMass", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		if(CheckSignalRegion(true,muons_test,electrons_veto , jets, alljets,"High", weight))FillCLHist(sighist_mm, "SSMM_HighMass", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
		if(eventbase->GetEvent().PFMET() > 50 || NBJet(jets) > 0) FillCLHist(sighist_mm, "SSMM_CR", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets,  fatjetcoll,weight);
	      }
	    }
	  }
	}
	else{
	  if(muons_test[1].Pt() > 20 && muons_test[0].Pt() > 25 ){
	    
	    if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")) {
	      if(_mm_channel){
		FillCLHist(sighist_mm,"DiMuTriggerOSMM", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
		if(jets.size() > 1) 		FillCLHist(sighist_mm,"DiJetTriggerOSMM", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
	      }

	    }


	    if(GetDiLepMass(muons_test)< 100. && GetDiLepMass(muons_test) > 80.) {
	      FillCLHist(sighist_mm, "OSZMM", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  weight);
	      TString analysis_trigger_muon="HLT_IsoMu24_v";
	      TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
	      if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
		float trigw=1.;
		if(!isData) trigw= mcdata_correction->TriggerScaleFactor(electrons_veto, muons_test, "HLT_IsoMu24_v", 0);
		if(_m_channel){
		  FillCLHist(sighist_mm,"TriggerOSZMM", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		  if(AllPrompt(muons_test,0))FillCLHist(sighist_mm,"TriggerOSZMM_p1", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		  if(AllPrompt(muons_test,1))FillCLHist(sighist_mm,"TriggerOSZMM_p2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		}
	      }
	      if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")) {
		if(_mm_channel){
		  FillCLHist(sighist_mm,"DiMuTriggerOSZMM", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
		  if(AllPrompt(muons_test,0)) FillCLHist(sighist_mm,"DiMuTriggerOSZMM_p1", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
		  if(AllPrompt(muons_test,1)) FillCLHist(sighist_mm,"DiMuTriggerOSZMM_p2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
		}	    
		
	      }
	    }
	    else{
	      if(jets.size() > 3){
		if(NBJet(jets) > 1){
		  
		  TString analysis_trigger_muon="HLT_IsoMu24_v";
		  TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
		  if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
		    float trigw=1.;
		    if(!isData) trigw = mcdata_correction->TriggerScaleFactor(electrons_veto, muons_test, "HLT_IsoMu24_v", 0);
		    if(_m_channel){
		      FillCLHist(sighist_mm, "TriggerTop", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		      if(AllPrompt(muons_test,0) )                 FillCLHist(sighist_mm, "TriggerTop_p1", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		      if(AllPrompt(muons_test,1))                  FillCLHist(sighist_mm, "TriggerTop_p2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll,  trigw*weight);
		      
		    }
		  }
		  if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")) {
		    if(_mm_channel){
		      if(muons_test[1].Pt() > 20 && muons_test[0].Pt() > 40 ){
			
			FillCLHist(sighist_mm, "DiMuTriggerTop", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
			if(AllPrompt(muons_test,0)) 		FillCLHist(sighist_mm, "DiMuTriggerTop_p1", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
			if(AllPrompt(muons_test,1) )		FillCLHist(sighist_mm, "DiMuTriggerTop_p2", eventbase->GetEvent(), muons_test, electrons_veto,jets, alljets, fatjetcoll, weight);
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
  
  return;

  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;


  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :                                                                                                                                
  
  
  MakeControlPlots(0,"NoTrigger",weight);


  
  if((PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))){
    
    std::vector<snu::KMuon> muons = GetMuons("MUON_HN_TIGHT",true);

    std::vector<snu::KMuon> muon_07dz04;
    std::vector<snu::KMuon> muon_06;
    std::vector<snu::KMuon> muon_06dz04;
    std::vector<snu::KMuon> muon_0706;
    std::vector<snu::KMuon> muon_0706dz04;

    std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
    std::vector<snu::KJet> jets = GetJets("JET_HN");

    std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
    if(CheckSignalRegion(true,muons, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT", weight);
    if(CheckSignalRegion(true,muons, electrons_veto , jets, alljets,"High", weight))        FillEventCutFlow(3, "HighMassMM_HNTIGHT", weight);
    for(unsigned int im = 0 ; im < muons.size(); im++){
      if(fabs(muons[im].dZ()) < 0.04)           muon_07dz04.push_back(muons[im]);

      if(muons[im].RelIso04() < 0.06){
	muon_06.push_back(muons[im]);
	if(fabs(muons[im].dZ()) < 0.04)           muon_06dz04.push_back(muons[im]);
      }




      if(fabs(muons[im].Eta()) > 1.5){
	if(muons[im].RelIso04() < 0.06){
	  muon_0706.push_back(muons[im]);
	  if(fabs(muons[im].dZ()) < 0.04)           muon_0706dz04.push_back(muons[im]);
	}
      }
      else{
	muon_0706.push_back(muons[im]);
	muon_0706dz04.push_back(muons[im]);
      }
    }
    
    if(CheckSignalRegion(true,muon_07dz04, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT2", weight);
    if(CheckSignalRegion(true,muon_06, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT3", weight);
    if(CheckSignalRegion(true,muon_06dz04, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT4", weight);
    if(CheckSignalRegion(true,muon_0706, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT5", weight);
    if(CheckSignalRegion(true,muon_0706dz04, electrons_veto , jets, alljets,"Low", weight))        FillEventCutFlow(2, "LowMassMM_HNTIGHT6", weight);


    if(CheckSignalRegion(true,muon_07dz04, electrons_veto , jets, alljets,"high", weight))        FillEventCutFlow(3, "highMassMM_HNTIGHT2", weight);
    if(CheckSignalRegion(true,muon_06, electrons_veto , jets, alljets,"high", weight))        FillEventCutFlow(3, "highMassMM_HNTIGHT3", weight);
    if(CheckSignalRegion(true,muon_06dz04, electrons_veto , jets, alljets,"high", weight))        FillEventCutFlow(3, "highMassMM_HNTIGHT4", weight);
    if(CheckSignalRegion(true,muon_0706, electrons_veto , jets, alljets,"high", weight))        FillEventCutFlow(3, "highMassMM_HNTIGHT5", weight);
    if(CheckSignalRegion(true,muon_0706dz04, electrons_veto , jets, alljets,"high", weight))        FillEventCutFlow(3, "highMassMM_HNTIGHT6", weight);

    

  }
  }

  void HNDiLepton::FillEventCutFlow(int cf,TString cut,  float weight){

  if(cf==0){
    if(GetHist( "mm_eventcutflow")) {
      GetHist( "mm_eventcutflow")->Fill(cut,weight);

    }
    else{
      AnalyzerCore::MakeHistograms( "mm_eventcutflow",15,0.,15.);

      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(2,"DiLooseMM");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(3,"ElVeto");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(4,"L1Pt");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(5,"L2Pt5");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(6,"L2Pt10");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(7,"L2Pt15");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(8,"L153");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(9,"L153L2");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(10,"SSMMLoose");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(11,"MLL");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(12,"mmdR");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(13,"DiJet");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(14,"DiNewJet");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(15,"SSMMTight");
      GetHist( "mm_eventcutflow")->Fill(cut,weight);

    }
  }
  if(cf==1){
    if(GetHist( "cutflow_challenge")) {
      GetHist( "cutflow_challenge")->Fill(cut,weight);
      
    }
    else{
      AnalyzerCore::MakeHistograms( "cutflow_challenge",11,0.,11.);

      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(1,"1_NoCut");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(2,"2_EventClean");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(3,"3_DiMu");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(4,"4_MuVeto");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(5,"5_ElVeto");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(6,"6_mll");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(7,"7_DiJet");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(8,"8_MET");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(9,"9_mjj");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(10,"91_bjetv1");
      GetHist( "cutflow_challenge")->GetXaxis()->SetBinLabel(11,"92_bjetv2");

      GetHist( "cutflow_challenge")->Fill(cut,weight);
      
    }
  }
  if(cf==-1){
    if(GetHist( "noWeightcutflow_challenge")) {
      GetHist( "noWeightcutflow_challenge")->Fill(cut,weight);

    }
    else{
      
      AnalyzerCore::MakeHistograms( "noWeightcutflow_challenge",11,0.,11.);

      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(1,"NoWeight_1_NoCut");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(2,"NoWeight_2_EventClean");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(3,"NoWeight_3_DiMu");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(4,"NoWeight_4_MuVeto");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(5,"NoWeight_5_ElVeto");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(6,"NoWeight_6_mll");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(7,"NoWeight_7_DiJet");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(8,"NoWeight_8_MET");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(9,"NoWeight_9_mjj");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(10,"NoWeight_10_bjetv1");
      GetHist( "noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(11,"NoWeight_11_bjetv2");
      
      
      GetHist( "noWeightcutflow_challenge")->Fill(cut,weight);
      
    }
  }
  
  if(cf==2){
    if(GetHist( "mm_eventcutflow_LowMassDoubleMuon")) {
      GetHist( "mm_eventcutflow_LowMassDoubleMuon")->Fill(cut,weight);

    }
    else{
      
      vector<TString> IDs;
      IDs.push_back("LowMassMM_HNTIGHT");
      IDs.push_back("LowMassMM_HNTIGHT2");
      IDs.push_back("LowMassMM_HNTIGHT3");
      IDs.push_back("LowMassMM_HNTIGHT4");
      IDs.push_back("LowMassMM_HNTIGHT5");
      IDs.push_back("LowMassMM_HNTIGHT6");
      AnalyzerCore::MakeHistograms( "mm_eventcutflow_LowMassDoubleMuon",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( "mm_eventcutflow_LowMassDoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( "mm_eventcutflow_LowMassDoubleMuon")->Fill(cut,weight);

    }
  }
  
  if(cf==3){
    if(GetHist( "mm_eventcutflow_HighMassDoubleMuon")) {
      GetHist( "mm_eventcutflow_HighMassDoubleMuon")->Fill(cut,weight);

    }
    else{

      vector<TString> IDs;
      IDs.push_back("HighMassMM_HNTIGHT");
      IDs.push_back("HighMassMM_HNTIGHT2");
      IDs.push_back("HighMassMM_HNTIGHT3");
      IDs.push_back("HighMassMM_HNTIGHT4");
      IDs.push_back("HighMassMM_HNTIGHT5");
      IDs.push_back("HighMassMM_HNTIGHT6");
      AnalyzerCore::MakeHistograms( "mm_eventcutflow_HighMassDoubleMuon",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

	TString elid = IDs[iid];
	GetHist( "mm_eventcutflow_HighMassDoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( "mm_eventcutflow_HighMassDoubleMuon")->Fill(cut,weight);

    }
  }
  if(cf==4){
    if(GetHist( "mm_lowmassopt")) {
      GetHist( "mm_lowmassopt")->Fill(cut,weight);

    }
    else{

      vector<TString> IDs;
      IDs.push_back("NoCut");
      IDs.push_back("ElVeto");
      IDs.push_back("DiLooseMM");
      IDs.push_back("SSMMLoose");
      IDs.push_back("MLL");
      IDs.push_back("mmdR");
      IDs.push_back("LepVeto");
      IDs.push_back("SSMM_DiJet_noB");
      IDs.push_back("SSMM_1Jet");
      IDs.push_back("SSMM_1JetOpt");
      IDs.push_back("SSMM_1JetOpt2");
      IDs.push_back("SSMM_1JetOpt_pt2");
      IDs.push_back("SSMM_1JetOpt2_pt2");
      IDs.push_back("SSMM_DiJet");      
      IDs.push_back("SSMM_DiJet_passMET45");
      IDs.push_back("SSMM_DiJet_passMET50");
      IDs.push_back("SSMM_DiJet_passMET55");
      IDs.push_back("SSMM_DiJet_passMET60");
      IDs.push_back("SSMM_DiJet_passMET65");
      IDs.push_back("SSMM_DiJet_passMET70");
      IDs.push_back("SSMM_DiJet_passMET80");
      IDs.push_back("SSMM_DiJet_passMETST7_5");
      IDs.push_back("SSMM_DiJet_passMETST10");
      IDs.push_back("SSMM_DiJet_passMETST12_5");
      IDs.push_back("SSMM_DiJet_passMETST15");
      IDs.push_back("SSMM_DiJet_passMETST17_5");
      IDs.push_back("SSMM_DiJet_passMETST20");
      IDs.push_back("SSMM_DiJet_passHT240");
      IDs.push_back("SSMM_DiJet_passHT260");
      IDs.push_back("SSMM_DiJet_passHT280");
      IDs.push_back("SSMM_DiJet_passHT300");
      IDs.push_back("SSMM_DiJet_passDR2");
      IDs.push_back("SSMM_DiJet_passMT80");
      IDs.push_back("SSMM_DiJet_passMT90");
      IDs.push_back("SSMM_DiJet_passMT100");
      IDs.push_back("SSMM_DiJet_passLJ");
      IDs.push_back("SSMM_DiJet_passmll");
      IDs.push_back("SSMM_DiJet_passpt2");
      IDs.push_back("SSMM_DiJet_passpt2mll");


      AnalyzerCore::MakeHistograms( "mm_lowmassopt",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( "mm_lowmassopt")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( "mm_lowmassopt")->Fill(cut,weight);

    }
  }




}

void HNDiLepton::FillEventCutFlow(TString cut, TString label, float weight){

  if(GetHist(label + "_eventcutflow")) {
    GetHist(label + "_eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms(label + "_eventcutflow",10,0.,10.);

    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(1,"SSMM_loose");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(2,"SSMM_tightiso");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(3,"SSMM_tightiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(4,"SSMM_tightmdiso1");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(5,"SSMM_tightmdiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(6,"SSMM_tightmdiso3");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(7,"SSMM_tightmdiso4");
  }
  
}




void HNDiLepton::MakeControlPlots(int method, TString methodtag, float w)throw( LQError ){
  if(_mm_channel) MakeControlPlotsMM(method, methodtag, w);
  //if(_ee_channel) MakeControlPlotsEE(method, methodtag, w);
}

void HNDiLepton::MakeControlPlotsMM(int method, TString methodtag, float w)throw( LQError ){
  
  std::vector<snu::KMuon> muons_veto         = GetMuons("MUON_HN_VETO");
  std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
  
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");
  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> hnjets = GetJets("JET_HN");
  //std::vector<snu::KJet> hnjets =  hn04jets;
  //GetJetsWFT("JET_HN","FATJET_HN");
  
  float puweight = 1.;
  if(!isData){
    if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
    else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), hnjets.size());
    
    
    w      *= puweight;
    if(!methodtag.Contains("Trigger")) w      *= WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi)  ;
    w      *= mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "ELECTRON_HN_TIGHTv4", muons_veto,  "MUON_HN_TIGHT", 0 , isData, 0);
    
    w      *= mcdata_correction->MuonTrackingEffScaleFactor(muons_veto);
    w      *=   mcdata_correction->MuonScaleFactor("MUON_HN_TRI_TIGHT", muons_veto, 0);
    FillHist("EffPUweight", puweight, w, -1., 5., 600);
    FillHist("EffLumi", WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi)  , w, 0., 50000., 50000);
    FillHist("EffTrigger", mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, "ELECTRON_HN_TIGHTv4", muons_veto, "MUON_HN_TIGHT", 0 , isData, 0),  w, 0., 2., 200);
    FillHist("EffTrk",mcdata_correction->MuonTrackingEffScaleFactor(muons_veto) , w, 0., 2., 200);
    FillHist("EffID", mcdata_correction->MuonScaleFactor("MUON_HN_TRI_TIGHT", muons_veto, 0), w, 0., 2., 200);
  }
  
  

  bool keep_fake=false;
  if(method==2) keep_fake=true;
    
  std::vector<snu::KMuon>  hn_loose =  GetMuons("MUON_HN_LOOSE",keep_fake);
  std::vector<snu::KMuon>  hn_tight;
  if(k_running_nonprompt) hn_tight = GetMuons("MUON_HN_LOOSE",keep_fake);
  else hn_tight = GetMuons("MUON_HN_TIGHT",keep_fake);



  int nbjet = NBJet(hnjets);
  
  if(hn_tight.size() < 2) return;
  if(hn_tight[0].Pt() < 20 ) return;
  if(hn_tight[1].Pt() < 10 ) return;
			     

  if(hn_tight.size() ==3){
    if((nbjet == 0) &&  hn_tight[2].Pt() > 10.){
      
      if(k_running_nonprompt){
	float iso1=0.07;
	float iso2=0.07;
	if(fabs(hn_tight[0].Eta()) > 1.5)iso1=0.06;
	if(fabs(hn_tight[1].Eta()) > 1.5)iso2=0.06;
	
	TString tag1 = "Tight0.07_0.005_3_0.04";
	TString tag2 = "Tight0.07_0.005_3_0.04";
	
	bool cb_1=false;
	bool cb_2=false;
	w     = m_datadriven_bkg->Get_DataDrivenWeight(false,hn_tight, "MUON_HN_TIGHT", hn_tight.size(), electrons_veto,"", 0, "", "");
	
      }
      if(!(muons_veto.size() > 3 ||  electrons_veto.size() > 0)){
	snu::KParticle Z1 = hn_tight[0] + hn_tight[1];
	snu::KParticle Z2 = hn_tight[0] + hn_tight[2];
	snu::KParticle Z3 = hn_tight[1] + hn_tight[2];
	float diff1 = fabs(Z1.M() - 91.19) ;
	float diff2 = fabs(Z2.M() - 91.19) ;
	float diff3 = fabs(Z3.M() - 91.19) ;
	
	bool m_ll4=true;
	
	float diff = 999999999.;
	float el_zpt = 0.;
	float el_wpt = 0.;
	int iZ1(0);
	int iZ2(0);
	if(Z1.Charge() == 0){
	  diff = diff1;
	  el_zpt = hn_tight[0].Pt();
	  el_wpt = hn_tight[2].Pt();
	  iZ1=0;
	  iZ1=1;
	  if(Z1.M() < 4.) m_ll4=false;
	}
	if( (diff2 < diff) && (Z2.Charge() == 0)){
	  diff= diff2;
	  el_zpt= hn_tight[0].Pt();
	  el_wpt = hn_tight[1].Pt();
	  iZ1=0;
	  iZ1=2;
	  if(Z2.M() < 4.) m_ll4=false;
	}
	if( (diff3 < diff) && (Z3.Charge() == 0)){
	  diff= diff3;
	  el_zpt= hn_tight[1].Pt();
	  el_wpt = hn_tight[0].Pt();
	  iZ1=1;
	  iZ1=2;
	  if(Z3.M() < 4.) m_ll4=false;
	}
	
	if(diff < 10.){
	  if(el_zpt > 20.){
	    if(eventbase->GetEvent().MET(snu::KEvent::pfmet) > 30.){
	      if(el_wpt > 20.){
		snu::KParticle WZ = hn_tight[0] + hn_tight[1]+ hn_tight[2];
		if(WZ.M() > 100){
		  FillCLHist(sighist_mmm, methodtag+"WZMuon", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
  std::vector<snu::KMuon>  hn_muonZZ;
  if(k_running_nonprompt) hn_muonZZ = GetMuons("MUON_HN_LOOSE",false);
  else hn_muonZZ = GetMuons("MUON_HN_TIGHT",false);

  if(hn_muonZZ.size() >=4){
    
    if(k_running_nonprompt){
      float iso1=0.07;
      float iso2=0.07;
      if(fabs(hn_muonZZ[0].Eta()) > 1.5)iso1=0.06;
      if(fabs(hn_muonZZ[1].Eta()) > 1.5)iso2=0.06;

      TString tag1 = "Tight0.07_0.005_3_0.04";
      TString tag2 = "Tight0.07_0.005_3_0.04";
      
      bool cb_1=false;
      bool cb_2=false;
      w     = m_datadriven_bkg->Get_DataDrivenWeight(false,hn_tight, "MUON_HN_TIGHT", hn_tight.size(), electrons_veto,"", 0, "", "");

						  
    }
    
    if(!(electrons_veto.size() > 0 )){

      /// Check no OS pairs have m(ll) < 4. geV OR dR(l,l) < 0.02                                                                                                                                                                                                
      bool pass_zz_sel1=true;
      for(unsigned int iel=0; iel < hn_muonZZ.size() -1; iel++){
	for(unsigned int iel2= iel+1; iel2 < hn_muonZZ.size(); iel2++){
	  if( hn_muonZZ[iel].DeltaR(hn_muonZZ[iel2]) < 0.02) pass_zz_sel1=false;
	  snu::KParticle zee = hn_muonZZ[iel] + hn_muonZZ[iel2];
	  if((zee.Charge() == 0) && (zee.M() < 4.)) pass_zz_sel1=false;
	}
      }
      int ich(0);
      /// fill index of vector that has e+ and e- used for finding os pairs                                                                                                                                                                                      
      vector<int> plus_i;
      vector<int> minus_i;
      for(unsigned int iel=0; iel < hn_muonZZ.size(); iel++){
	ich += hn_muonZZ[iel].Charge();
	if(hn_muonZZ[iel].Charge() > 0) plus_i.push_back(iel);
	else minus_i.push_back(iel);
      }
      
      bool pass_zz_sel2(false);
      bool pass_zz_sel3(false); /// jaesungs 2 Z in Z peak (pt Zmu1 > 20. )                                                                                                                                                                                      

      if(ich == 0 && plus_i.size() == 2 && minus_i.size()==2){

	for(int izp = 0 ; izp< 1;izp++){
	  for(int izm = 0 ; izm < 2;izm++){

	    /// loop finds Z e+e- pairs                                                                                                                                                                                                                          
	    snu::KParticle Z1 = hn_muonZZ[plus_i[izp]] + hn_muonZZ[minus_i[izm]];

	    if(fabs(Z1.M() - 91.19) < 10.) {
	      /// Z1 is Zcandidate                                                                                                                                                                                                                               
	      /// now get second Z candidate indices                                                                                                                                                                                                             
	      int izp2 = izp;
	      if(izp2 ==1)izp2=0;
	      else izp2=1;
	      int izm2 = izm;
	      if(izm2 ==1)izm2=0;
	      else izm2=1;
	      // Z2 uses non z1 electrons                                                                                                                                                                                                                        
	      snu::KParticle Z2= hn_muonZZ[plus_i[izp2]] + hn_muonZZ[minus_i[izm2]];
	      if(fabs(Z2.M() - 91.19) <10.) {
		// this event has 2 Z candidates                                                                                                                                                                                                                 
		pass_zz_sel3=true;
		if( !( (hn_muonZZ[plus_i[izp]].Pt() > 20 ) || (hn_muonZZ[minus_i[izm]].Pt() > 20)) ) pass_zz_sel3=false;
		if( !( (hn_muonZZ[plus_i[izp2]].Pt() > 20 ) || (hn_muonZZ[minus_i[izm2]].Pt() > 20)) ) pass_zz_sel3=false;
		if(pass_zz_sel3) break;
	      }
	    }
	  }
	}
	snu::KParticle Z1cand1 = hn_muonZZ[plus_i[0]] + hn_muonZZ[minus_i[0]];
	snu::KParticle Z2cand1 = hn_muonZZ[plus_i[1]] + hn_muonZZ[minus_i[1]];

	bool cand_found=false;
	bool cand1=true;
	if(!(Z1cand1.M() > 4 && Z1cand1.M() < 120) ) cand1=false;
	if(!(Z2cand1.M() > 4 && Z2cand1.M() < 120) ) cand1=false;

	snu::KParticle Z1cand2 = hn_muonZZ[plus_i[0]] + hn_muonZZ[minus_i[1]];
	snu::KParticle Z2cand2 = hn_muonZZ[plus_i[1]] + hn_muonZZ[minus_i[0]];
	bool cand2=true;
	if(!(Z1cand2.M() > 4 && Z1cand2.M() < 120) ) cand2=false;
	if(!(Z2cand2.M() > 4 && Z2cand2.M() < 120) ) cand2=false;

	if(cand1 || cand1) cand_found=true;

	snu::KParticle Z1, Z2;
	float Zdiff_ev(0.);
	if(cand1){
	  float zcand1diff1 = fabs(Z1cand1.M() - 91.1);
	  float zcand1diff2 = fabs(Z2cand1.M() - 91.1);
	  if(zcand1diff1 < zcand1diff2) {Z1= Z1cand1; Z2=Z2cand1; Zdiff_ev = zcand1diff1;}
	  else  {Z1= Z2cand1; Z2=Z1cand1; Zdiff_ev = zcand1diff2;}
	}
	if(cand2){
	  float zcand2diff1 = fabs(Z1cand2.M() - 91.1);
	  float zcand2diff2 = fabs(Z2cand2.M() - 91.1);
	  if(zcand2diff1 < zcand2diff2) {
	    if(zcand2diff1 < Zdiff_ev) {Z1 = Z1cand2; Z2 = Z2cand2;}
	  }
	  else{
	    if(zcand2diff2 < Zdiff_ev) {Z1 = Z2cand2; Z1 = Z1cand2;}
	  }
	}

	// Z1 is closest to Z mass                                                                                                                                                                                                                               
	// Z2 is other os pair                                                                                                                                                                                                                                   
	if(cand_found&& Z1.M() > 40.) pass_zz_sel2=true;
	if(pass_zz_sel1&&pass_zz_sel3){
	  FillCLHist(sighist_mmmm, methodtag+"ZZMuon1", eventbase->GetEvent(), hn_muonZZ, electrons_veto,hnjets,alljets, w);

	}
	if(pass_zz_sel1&&pass_zz_sel2){
	  FillCLHist(sighist_mmmm, methodtag+"ZZMuon2", eventbase->GetEvent(), hn_muonZZ,electrons_veto,hnjets,alljets, w);
	  //if(Z1.M() > 60 && Z2.M() > 60) FillCLHist(sighist_eeee, "ZZElectron3", eventbase->GetEvent(), muonVetoColl,hn_muonZZ,jets, ev_weight);                                                                                                          
	}
      }
    }
  }// END ZZ CR 
  
  
}



void HNDiLepton::MakeControlPlotsEE(int method, TString methodtag, float w)throw( LQError ){

   return;
}


 

void HNDiLepton::GetOSSignalEfficiency(float w){
  
}
										   
								   



void HNDiLepton::RunAnalysis(TString plottag, TString tightelid, TString vetoelid, TString looseelid){

  
    

  return;
}// End of execute event loop
  

void HNDiLepton::SignalValidation(){
  
  // Check jet properties                                                                                                                                                                                                                                                                                                   

}
 

void HNDiLepton::GetTriggEfficiency(){
  //ListTriggersAvailable();                                                                                                                                                                                                                                                                                                                                                      
  vector<int> pt1;
  pt1.push_back(18);
  pt1.push_back(35);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(30);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(120);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(25);
  vector<int>pt2;
  pt2.push_back(10);
  pt2.push_back(35);
  pt2.push_back(25);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(15);


  std::vector<TString> lists_triggers;
  lists_triggers.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
  lists_triggers.push_back("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele23_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200");
  lists_triggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v1");
  for(unsigned int i=0; i < lists_triggers.size(); i++){
    FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator_nojet", lists_triggers );
  }

  std::vector<snu::KJet> jets=GetJets("JET_HN");
  std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_POG_TIGHT");
  if(jets.size() > 1){
    for(unsigned int i=0; i < lists_triggers.size(); i++){
      TString trig=lists_triggers.at(i);
      FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator", lists_triggers );
      if(PassTrigger(trig))  {
	FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator",lists_triggers );
	
	if(electrons.size() ==2) {
	  
	  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon",lists_triggers );
	  if(electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > pt2.at(i))  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt",lists_triggers );
	}
      }
    }
  }
}

void HNDiLepton::FillTriggerEfficiency(TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label)) {
    GetHist("TriggerEfficiency_"+label)->Fill(cut,weight);

  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label)->GetXaxis()->SetBinLabel(it+1,list.at(it));
    }
  }
  
}


bool HNDiLepton::CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString name, float w){

  bool debug=false;


  if(el.size() > 0) return false ;
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  // Set by trigger                                                                                                                                                                                                                                                
  if(muons.at(0).Pt() < 20.) {if(debug)cout << "Fail pt1 " << endl; return false;}
  if(muons.at(1).Pt() < 10.)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  if(isss&&!SameCharge(muons)) {if(debug)cout << "Fail ss " << endl; return false;}

  if(!isss&&SameCharge(muons)) {if(debug)cout << "Fail os  " << endl; return false;}
  if(jets.size() < 2) {if(debug)cout << "Fail jets " << endl; return false;}

  snu::KParticle mm = muons.at(0) + muons.at(1);
  if(mm.M()  < 10.) {if(debug)cout << "Fail mee  " << endl; return false;}

  // 80 GeV ??? 
  //if(name.Contains("Low")){
  //if(mm.M()  > 70.) {if(debug)cout << "Fail mee  " << endl; return false;}
  //}
  
  float dijetmass_tmp=999.;
  float dijetmass=9990000.;
  int m=-999;
  int n=-999;
  for(UInt_t emme=0; emme<jets.size(); emme++){
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      if(name.Contains("Low")){
	dijetmass_tmp = (jets[emme]+jets[enne]+muons[0] + muons[1]).M();
      }
      else  dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {
        dijetmass = dijetmass_tmp;
        m = emme;
        n = enne;
      }
    }
  }
  

  snu::KParticle jj = jets.at(m) + jets.at(n) ;

  float dPhi = fabs(TVector2::Phi_mpi_pi(jets[m].Phi() - jets[n].Phi()));
  float contramass=2*jets[m].Pt()*jets[n].Pt()*(1+cos(dPhi));
  contramass=sqrt(contramass);

  if(name.Contains("Low")){
    if(contramass > 100) return false;
    if((jets[0]+jets[1]).M() > 250.) return false;
    if((jets[0] + muons[0] + muons[1]).M() > 250.)  return false;
  }
  else{
    if(jj.M() > 120.) {if(debug)cout << "Fail mjj  " << endl; return false;}
    if(jj.M() < 50.) {if(debug)cout << "Fail mjj  " << endl; return false;}

  }

  if(name.Contains("Low")){
    if(muons.at(0).DeltaR(muons.at(1)) > 3.5) {if(debug)cout << "Fail dr  " << endl; return false;}
  }


  float ST = muons[0].Pt() + muons[1].Pt();

  std::vector<snu::KJet> loosejets=GetJets("JET_NOCUT");

  float HT=0.;

  for(unsigned int ij=0; ij <jets.size(); ij++){
    ST+= alljets[ij].Pt();
    HT+= jets[ij].Pt();

  }

  float LT = muons[0].Pt() + muons[1].Pt();
  if(name.Contains("Low")){
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 15.) {if(debug)cout << "Fail met  " << endl; return false;}
    if(eventbase->GetEvent().PFMET() > 80) return false;
  }
  else if(name.Contains("High")){
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 8.) {if(debug)cout << "Fail met  " << endl; return false;}
  }
  else{
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 12.5) {if(debug)cout << "Fail met  " << endl; return false;}
    if(eventbase->GetEvent().PFMET() > 80) return false;

  }


  float dphi_1 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_1 = sqrt(2.* muons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));

  float dphi_2 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_2 = sqrt(2.* muons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_2)));

  if(name.Contains("Low")){
    if(MT_1 > 100.) return false;
    if(MT_2 > 100.) return false;
    if(ST > 450.)  return false;
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);
    //if(lljj.M() > 300.) return false;                                                                                                                                                                                                                            

  }
  else   if(name.Contains("High")){
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);

    if(ST < 400.)  return false;
    if(lljj.M() < 200.) return false;
    if(muons.at(0).Pt() < 50.) return false;
    if(muons.at(1).Pt() < 25.) return false;
  }
  else{


    if(LT/HT < 0.2)  return false;
    if(LT < 35)  return false;
    if(HT < 35)  return false;

    float dRmj=-999.;
    float ratiomj=0.;
    for(unsigned int im=0; im <muons.size(); im++){
      for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
        if(muons.at(im).DeltaR(jets.at(ij2)) >  0.5){
          if(muons.at(im).DeltaR(jets.at(ij2)) > dRmj){
            dRmj=muons.at(im).DeltaR(jets.at(ij2)) ;
            if(im==0) ratiomj = jets.at(ij2).Pt() / muons[im].Pt();
          }
        }
      }
    }
    if(ratiomj > 3.) return false;
    if(dRmj > 4.5) return false;

    if(muons[0].DeltaR(muons[1]) > 4.) return false;

  }
  if(name.Contains("High")){
    if((muons.at(0).Pt() + muons.at(1).Pt() ) < 50.) return false;
    if (ST < 400. ) return false;

    float mindRjj=999.;
    for(unsigned int ij=0; ij <jets.size()-1; ij++){
      for(unsigned int ij2=ij+1; ij2 <jets.size(); ij2++){
        if(jets.at(ij).DeltaR(jets.at(ij2)) < mindRjj) mindRjj=jets.at(ij).DeltaR(jets.at(ij2)) ;
      }
    }
    //if(mindRjj > 1.5) {if(debug)cout << "Fail dr  " << endl; return false;}                                                                                                                                                                                      
  }

  int nbjet=0;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet++;
  }
  if(nbjet > 0) {if(debug)cout << "Fail nbjet  " << endl; return false;}


  if(debug)cout << "PASSES ID" << endl;
  return true;
}




bool HNDiLepton::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool HNDiLepton::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  
  return true;

}


bool HNDiLepton::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
  
}

bool HNDiLepton::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
 
  return true;
}



	
	

bool HNDiLepton::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
}




void HNDiLepton::counter(TString cut, float w){

  map<TString,float>::iterator itmapcounter = mapcounter.find(cut) ;
  if (itmapcounter == mapcounter.end()){
    mapcounter[cut] = w;
  }
  else{
    float sum = itmapcounter->second;
    mapcounter[cut] = sum+w;
  }
  FillEventCutFlow(1,cut,w);
  //FillEventCutFlow(-1,cut,1);

}


void HNDiLepton::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

  for ( map<TString,float>::iterator itmapcounter = mapcounter.begin(); itmapcounter != mapcounter.end(); itmapcounter++){
    cout << itmapcounter->first << " has count "<< itmapcounter->second << endl;
  }

}


void HNDiLepton::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  InitialiseAnalysis();

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");
  
  if(functionality==HNDiLepton::OPT){
    DeclareVariable(k_met , "k_met");
    DeclareVariable(k_met_st,"k_met_st");
    DeclareVariable(k_mumumass,"k_mumumass");
    DeclareVariable(k_lljj_lowmass,"k_lljj_lowmass");
    DeclareVariable(k_l1jj_lowmass,"k_l1jj_lowmass");
    DeclareVariable(k_l2jj_lowmass,"k_l2jj_lowmass");
    DeclareVariable(k_llj_lowmass,"k_llj_lowmass");
    DeclareVariable(k_jj_lowmass,"k_jj_lowmass");
    DeclareVariable(k_lljj_highmass,"k_lljj_highmass"); 
    DeclareVariable(k_l1jj_highmass,"k_l1jj_highmass");
    DeclareVariable(k_l2jj_highmass,"k_l2jj_highmass");
    DeclareVariable(k_llj_highmass,"k_llj_highmass");
    DeclareVariable(k_jj_highmass,"k_jj_highmass");
    DeclareVariable(k_st,"k_st");
    DeclareVariable(k_ht,"k_ht");;
    DeclareVariable(k_weight,"k_weight");
    DeclareVariable(k_mu1pt,"k_mu1pt"); 
    DeclareVariable(k_mu2pt,"k_mu2pt");
    DeclareVariable(k_j1pt,"k_j1pt");
    DeclareVariable(k_contramass_lowmass,"k_contramass_lowmass");
    DeclareVariable(k_contramass_highmass,"k_contramass_highmass");;
    DeclareVariable(k_lldr ,"k_lldr");
    DeclareVariable(k_minljdR,"k_minljdR");
    DeclareVariable(k_awayjetminDR,"k_awayjetminDR");
    DeclareVariable(k_mindRjj,"k_mindRjj");
    DeclareVariable(k_njets,"k_njets");
    DeclareVariable(k_nbjet_l,"k_nbjet_l");
    DeclareVariable(k_nbjet_m,"k_nbjet_m");
    DeclareVariable(k_nbjet_t,"k_nbjet_t");
    DeclareVariable(k_nfatjets,"k_nfatjets");
  }
  
  return;
  
}

HNDiLepton::~HNDiLepton() {
  
  Message("In HNDiLepton Destructor" , INFO);
  
}



void HNDiLepton::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiLepton::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiLeptonCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiLepton::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



