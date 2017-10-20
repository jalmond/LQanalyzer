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
  _m_channel=false;
  _ee_channel=false;
  _e_channel=false;
  _em_channel=false;

  _mm_met_presel_cut=80.;
  _ee_met_presel_cut=80.;
  _em_met_presel_cut=80.;

  _mm_mll_presel_cut=10.;
  _ee_mll_presel_cut=10.;
  _em_mll_presel_cut=10.;

  _m_tightid = "MUON_HN_TIGHT";
  _e_tightid = "ELECTRON_HN_TIGHTv4";
  _m_looseid = "MUON_HN_LOOSEv7_SIP3";
  _e_looseid = "ELECTRON_HN_FAKELOOSEv7";



  configure_fakes=true;

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiLepton");

  Message("In HNDiLepton constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  //InitialiseAnalysis();
  
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
    if(!k_isdata || (k_channel=="DoubleMuon" || k_channel=="SingleMuon")){
      labels.push_back("DiMuon");
      labels.push_back("DiMuon_FAT");
      labels.push_back("DiMuon_FATTAU04");
      labels.push_back("DiMuon_NoFAT");
      labels.push_back("DiMuon_lowjetpt");
      //      labels.push_back("DiMuon_tightveto");
      //labels.push_back("DiMuon_isomu");
    }
    //    labels.push_back("DiMuon_allFJ");

    
    vector<TString> labelsE;
    if(!k_isdata || (k_channel=="DoubleEG" ||  k_channel=="SingleElectron")){
      labelsE.push_back("DiEl");
      labelsE.push_back("DiEl_singleEl");
    }
    
    for(unsigned int il = 0; il < labels.size(); il++){
      histtype llhist = sighist_mm;
      TString label = labels.at(il);
      MakeCleverHistograms(llhist, label + "SSLL_nolepveto");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_aj20");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_aj60");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_sf");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_df");
      MakeCleverHistograms(llhist, label+"SSLL_1JetCR");
      MakeCleverHistograms(llhist, label+"SSLL_1JetOpt");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_noW");
      MakeCleverHistograms(llhist, label+"SSLL_0Jet");
      MakeCleverHistograms(llhist, label+"SSLL_1Jet");
      MakeCleverHistograms(llhist, label+"SSLL_1JetOpt2");
      MakeCleverHistograms(llhist, label+"SSLL_1JetOpt_pt2");
      MakeCleverHistograms(llhist, label+"SSLL_1JetOpt2_pt2");
      MakeCleverHistograms(llhist, label+"SSLL_2Jet");
      MakeCleverHistograms(llhist, label+"SSLL_3Jet");
      MakeCleverHistograms(llhist, label+"SSLL_4Jet");
      MakeCleverHistograms(llhist, label+"SSLL_DiTJet");
      MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR");
      MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR2");
      MakeCleverHistograms(llhist, label+"SSLL_LowMass_CR");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR2");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR3");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR4"); 
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR5");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_CR");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_noB");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_j27");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_pujet");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_tightjet");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_tightjetlv");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_FailnoB");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passMET");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passHT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passDR");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passDR2");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passMT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passLJ");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passLTHT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passmll");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passpt2");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passpt2mll");

    }
    for(unsigned int il = 0; il < labelsE.size(); il++){
      histtype llhist = sighist_ee;
      TString label = labelsE.at(il);
      MakeCleverHistograms(llhist, label + "SSLL_nolepveto");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection");
      MakeCleverHistograms(llhist, label+"SSLL_PreselectionZ");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_aj20");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_aj60");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_sf");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection_df");
      MakeCleverHistograms(llhist, label+"SSLL_1JetCR");
      MakeCleverHistograms(llhist, label+"SSLL_1JetOpt");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_noW");
      MakeCleverHistograms(llhist, label+"SSLL_0Jet");
      MakeCleverHistograms(llhist, label+"SSLL_1Jet");
      MakeCleverHistograms(llhist, label+"SSLL_2Jet");
      MakeCleverHistograms(llhist, label+"SSLL_3Jet");
      MakeCleverHistograms(llhist, label+"SSLL_4Jet");
      MakeCleverHistograms(llhist, label+"SSLL_DiTJet");
      MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR");
      MakeCleverHistograms(llhist, label+"SSLL_LowMass_CR");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR");
      MakeCleverHistograms(llhist, label+"SSLL_HighMass_CR");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_noB");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_FailnoB");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passMET");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passHT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passDR");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passDR2");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passMT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passLJ");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passLTHT");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passmll");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passpt2");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet_passpt2mll");

    }
  }
  

  return;
}

void HNDiLepton::DoCutFlow(float w){

  std::vector<snu::KElectron> electrons_veto = GetElectrons(true,true,"ELECTRON_HN_VETO");
  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 0., 2.5);
  std::vector<snu::KJet> jets = GetJets("JET_HN");


  counter("1_NoCut",w);
  std::vector<snu::KMuon> muons = GetMuons(_m_tightid,false);
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :                                                                                                                                                                                                                    
  if((PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))){
    counter( "2_EventClean", w);

    if(muons.size()==2){
      if(muons[1].Pt() > 10){
	if(muons[0].Pt() > 20){
	  counter( "3_DiMu", w);

	  std::vector<snu::KMuon> muons_veto         = GetMuons("MUON_HN_VETO",true);
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
		  CorrectedMETRochester(muons);
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
  

  bool SBt_JSf = CheckEventComparison("jalmond","SB_fake_mu22107_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FR_syst_cal_fix","jalmond","JS_fake_mu22108_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FRCalculator_Mu_dxysig_DILEP_fix",false);

  if(!SBt_JSf) cout << "AAHAHAHAH " << endl;

  /*
  for(unsigned int ipdf=0; ipdf < eventbase->GetEvent().PdfWeights().size() ; ipdf++){
    cout << ipdf << " " << eventbase->GetEvent().PdfWeights().at(ipdf) << " " <<   eventbase->GetEvent().LHEWeight()<< " "<< eventbase->GetEvent().MCWeight() <<  endl;
    
    }*/
  
  
  
  if(k_running_nonprompt){
    while(!fake_configured){
      /// SET UP OWN FAKES HISTS --> KEY ////                                                                                                                                                                                                                                    
      std::map<TString, std::pair<std::pair<TString,TString>  ,std::pair<float,TString> > >fake_hists;
      /// ONLY double (TH2D*) are configured at the minute
      fake_hists["fr_muon_central"] = std::make_pair(std::make_pair("Muon_Data_v7_SIP3_FR.root","Muon_Data_v7_SIP3_FR_Awayjet40"), std::make_pair(70., "TH2D"));
      fake_hists["fr_muon_awayjet20"] = std::make_pair(std::make_pair("Muon_Data_v7_SIP3_FR.root","Muon_Data_v7_SIP3_FR_Awayjet20"), std::make_pair(70., "TH2D"));
      fake_hists["fr_muon_awayjet30"] = std::make_pair(std::make_pair("Muon_Data_v7_SIP3_FR.root","Muon_Data_v7_SIP3_FR_Awayjet30"), std::make_pair(70., "TH2D"));
      fake_hists["fr_muon_awayjet60"] = std::make_pair(std::make_pair("Muon_Data_v7_SIP3_FR.root","Muon_Data_v7_SIP3_FR_Awayjet60"), std::make_pair(70., "TH2D"));
      fake_hists["fr_electron_central"] = std::make_pair(std::make_pair("Electron_Data_v7_FR.root","Electron_Data_v7_FR_Awayjet40") , std::make_pair(70., "TH2D"));
      fake_hists["fr_electron_awayjet20"] = std::make_pair(std::make_pair("Electron_Data_v7_FR.root","Electron_Data_v7_FR_Awayjet20") , std::make_pair(70., "TH2D"));
      fake_hists["fr_electron_awayjet30"] = std::make_pair(std::make_pair("Electron_Data_v7_FR.root","Electron_Data_v7_FR_Awayjet30") , std::make_pair(70., "TH2D"));
      fake_hists["fr_electron_awayjet60"] = std::make_pair(std::make_pair("Electron_Data_v7_FR.root","Electron_Data_v7_FR_Awayjet60") , std::make_pair(70., "TH2D"));
      /// END SET UP OWN FAKE HISTS ////                                                                                                                                                                                                                                           
      ConfigureFakeHists("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/Fake/DiLep/", fake_hists);
    }
  }


  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  
  //// Set weight for MC (nevents / xsec (ish))
  if(!isData){
    weight*= MCweight;

  }
  if(!isData)weight*= GetKFactor();
  if(!isData)weight*= MC_CR_Correction(0);
  

  if(k_flags.size() > 0){
    
    if(k_flags[0] == "CutFlow")  functionality = HNDiLepton::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HNDiLepton::OPT;
    else functionality = HNDiLepton::ANALYSIS;
  }

  
  if(functionality==HNDiLepton::CUTFLOW){
    DoCutFlow(1.); return;
  }
  
  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;
  _m_channel =   isData ?  (k_channel.Contains("SingleMuon")) : true ;
  _ee_channel =   isData ?  (k_channel.Contains("DoubleEG")) : true ;
  _e_channel =   isData ?  (k_channel.Contains("SingleElectron")) : true ;
  _em_channel =   isData ?  (k_channel.Contains("MuonEG")) : true ;

  TString muid=_m_tightid;
  if(k_running_nonprompt) muid=_m_looseid;
  
  TString elid=_e_tightid;
  if(k_running_nonprompt) elid=_e_looseid;

  
  std::vector<snu::KMuon> muons = GetMuons(muid,true);
  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",true);
  CorrectedMETRochester(muons);
  //double  met = eventbase->GetEvent().PFMET();
  //double  met_phi = eventbase->GetEvent().PFMETPhi();  

  //CorrectedMETMuon(1, muons, met, met_phi);

  /// Set up electrons                                                                                                                                        
  std::vector<snu::KElectron> electrons = GetElectrons(elid);
  std::vector<snu::KElectron> electrons_veto = GetElectrons(true, true,"ELECTRON_HN_VETO");

  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> alljets_10 = GetJetsWFT("JET_NOLEPTONVETO", "FATJET_HN_tau06",10., 2.5);
  std::vector<snu::KJet> tchanjets = GetJetsWFT("JET_HN_TChannel","FATJET_HN_tau06",20., 5.);
  
  std::vector<snu::KJet>  jets_20 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",20., 2.5);
  std::vector<snu::KJet>  jets_all20 =  GetJets("JET_HN", 20., 2.5);
  std::vector<snu::KJet>  jets_10 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",10., 2.7);
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN_tau06");

  /// correct L1 JEC and apply JMR
  std::vector<snu::KFatJet> fatjetcoll_updated = GetCorrectedFatJet(fatjetcoll);
  CorrectedMETJMR(fatjetcoll_updated);

  if(fatjetcoll.size() > 0)       {
    
    fatjetcoll[0] *= fatjetcoll[0].SmearedRes();
    fatjetcoll[0].SetPrunedMass(fatjetcoll[0].PrunedMass()*fatjetcoll[0].SmearedRes());
    snu::KFatJet  fj(fatjetcoll[0]);
    cout << "HN2 jit->PrunedMass() = " << fj.PrunedMass() << " " << fatjetcoll[0].PrunedMass()<< " "<< fatjetcoll[0].Pt() << " " << fj.Pt() <<endl;
    
    std::vector<snu::KFatJet> fatjetcoll_updated = GetCorrectedFatJet(fatjetcoll);
    cout << "HN3 jit->PrunedMass() = " << fatjetcoll_updated[0].PrunedMass() << " " << fatjetcoll_updated[0].Pt() << endl;
  }
  cout << "TEST" << endl;
  std::vector<snu::KFatJet> fatjetcoll2 = GetFatJets("FATJET_HN_tau045");
  
  vector<int> ijets;  
  
  
  
  if(functionality==HNDiLepton::OPT){
    return;
  }

  if(functionality==HNDiLepton::ANALYSIS){
    
    float mm_weight=weight;
    float ee_weight=weight;
    float em_weight=weight;
    
    std::vector<TString> triggerlist_DiMuon, triggerlist_DiElectron;
    std::vector<TString> triggerlist_DiMuon_singleLep, triggerlist_DiElectron_singleLep;

    std::vector<TString> triggerlist_EMu, triggerlist_EMu_PeriodBtoG, triggerlist_EMu_PeriodH, triggerlist_EMu_Mu8Ele23, triggerlist_EMu_Mu23Ele8;
    triggerlist_DiMuon.clear();
    triggerlist_DiElectron.clear();
    triggerlist_EMu.clear();

    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

    triggerlist_DiMuon_singleLep.push_back("HLT_IsoMu24_v");
    triggerlist_DiMuon_singleLep.push_back("HLT_IsoTkMu24_v");

    triggerlist_DiElectron.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_DiElectron_singleLep.push_back("HLT_Ele27_WPTight_Gsf_v");

    triggerlist_EMu.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_EMu.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_EMu.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_EMu.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_EMu_PeriodBtoG.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_EMu_PeriodBtoG.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");

    triggerlist_EMu_PeriodH.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_EMu_PeriodH.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_EMu_Mu8Ele23.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_EMu_Mu8Ele23.push_back("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v");

    triggerlist_EMu_Mu23Ele8.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v");
    triggerlist_EMu_Mu23Ele8.push_back("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ_v");

    

    if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
    if(!PassMETFilter()) return;     /// Initial event cuts :                                                                                                                                                                                                                    
    
    /*for(unsigned int ifj=0; ifj <fatjetcoll.size(); ifj++){
      cout << fatjetcoll[ifj].Pt() << " " << fatjetcoll[ifj].L1JetCorr() 
	   << " " << fatjetcoll[ifj].L2JetCorr()
	   << " " <<fatjetcoll[ifj].L3JetCorr()
	   << " " <<fatjetcoll[ifj].L2L3ResJetCorr() 
	   << " " <<fatjetcoll[ifj].JetArea()
	   << " " <<fatjetcoll[ifj].JECUncertainty()
	   << " " <<fatjetcoll[ifj].ScaledDownEnergy()
	   << " " <<fatjetcoll[ifj].ScaledUpEnergy()
	   << " " <<fatjetcoll[ifj].SmearedResDown()	
	   << " " <<fatjetcoll[ifj].SmearedResUp()
	   << " " <<fatjetcoll[ifj].SmearedRes()
	   << " " <<fatjetcoll[ifj].RawPt()
	   << " " <<fatjetcoll[ifj].RawE()  << endl;
	

	   }*/
    
    // if(_m_channel) RunMM("DiMuon_isomu", muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon_singleLep      ,25., 5.);
    //if(_mm_channel)RunMM("DiMuon_isomu", muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon      ,20., 10.);

    
    //if(_mm_channel)RunMM("DiMuon_tightveto",      muons,muons,electrons,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon           ,20., 10.);

    cout << "TEST 2" << endl;
    if(_mm_channel)RunMM("DiMuon",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    return;
    if(_mm_channel)RunMM("DiMuon_all",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    if(fatjetcoll.size() ==0) {
      if(_mm_channel)RunMM("DiMuon_NoFAT",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    }
    else{
      if(_mm_channel)RunMM("DiMuon_FAT",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    }

    if(fatjetcoll2.size() >0) {
      if(_mm_channel)RunMM("DiMuon_FATTAU04",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll2     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);

    }
    if(jets_10.size() > 0){
      if(jets_10[0].Pt() > 15.){
	if(_mm_channel)RunMM("DiMuon_lowjetpt",      muons,muons_veto,electrons_veto,alljets_10,   jets_10, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
      }
    }
    else       if(_mm_channel)RunMM("DiMuon_lowjetpt",      muons,muons_veto,electrons_veto,alljets_10,   jets_10, fatjetcoll     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
			 



    if(_ee_channel)RunEE("DiEl", electrons, electrons_veto, muons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets, ee_weight, triggerlist_DiElectron           ,25., 15.);
    if(_e_channel)RunEE("DiEl_singleEl", electrons,electrons_veto, muons_veto,alljets,   jets_20, fatjetcoll     ,  tchanjets,  ee_weight, triggerlist_DiElectron           ,25., 10.);
    //    RunEM();
  }
  //cout << "PT cone " << muons_test[0].PTCone(0.4,eventbase->GetMuonSel()->IsoCutValue(muons_test[0],"MUON_HN_TIGHT")) << " " << muons_test.at(0).Pt()*(1+max(0.,(muons_test.at(0).RelIso04()-0.07))) << endl;
}


float HNDiLepton::EEWeight(std::vector<snu::KElectron> electrons,TString id){
  
  if(isData) return 1.;
  
  double mc_weight = mcdata_correction->ElectronScaleFactor(id, electrons, 0);
  double electron_RecoSF =  mcdata_correction->ElectronRecoScaleFactor(electrons);
  mc_weight*= electron_RecoSF;

  float puweight=1.;
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  mc_weight*= puweight;

  std::vector<snu::KMuon> muons;
  double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 0, 0);
  double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 1, 0);
  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  mc_weight*= trigger_sf;


  
  return mc_weight;
}
float HNDiLepton::EMWeight(std::vector<snu::KElectron> electrons,std::vector<snu::KMuon> muons,TString idel, TString idmu){
  
  if(isData) return 1.;
  double mc_weight = mcdata_correction->ElectronScaleFactor(idel, electrons, 0);
  double electron_RecoSF =  mcdata_correction->ElectronRecoScaleFactor(electrons);
  mc_weight*= electron_RecoSF;

  float puweight=1.;
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  mc_weight*= puweight;
  mc_weight*= mcdata_correction->MuonTrackingEffScaleFactor(muons);
  mc_weight*= mcdata_correction->MuonScaleFactor(idel, muons, 0);
  return mc_weight;
}


float HNDiLepton::MMWeight(std::vector<snu::KMuon> muons, TString id){

  if(isData) return 1.;
  
  float mc_weight=mcdata_correction->MuonTrackingEffScaleFactor(muons);

  float puweight=1.;
  //if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  //else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), jets.size());
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);                                                                                      
  mc_weight*= puweight;

  double muon_id_iso_sf = mcdata_correction->MuonScaleFactor(id, muons, 0);
  mc_weight*= muon_id_iso_sf;
  
  std::vector<snu::KElectron> el;
  double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 0, 0, 0);
  double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 0, 1, 0);
  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  mc_weight*= trigger_sf;
  
  return mc_weight;

}

void HNDiLepton::RunMM(TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float mm_weight ,vector<TString> mm_trig, float pt1, float pt2){
  
  vector<snu::KElectron> el;
  RunLL("MM",label, muons, muons_veto, el, electrons,alljets, jets, fatjets, tjets, mm_weight,   mm_trig, pt1, pt2);
}

void HNDiLepton::RunEE(TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ee_weight ,vector<TString> ee_trig, float pt1, float pt2){

  vector<snu::KMuon> mu;
  RunLL("EE",label, mu, muons, electrons, electrons_veto, alljets, jets, fatjets, tjets,ee_weight,  ee_trig, pt1, pt2);
}


void HNDiLepton::RunLL(TString channel , TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KElectron> electrons_veto, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ll_weight ,vector<TString> ll_trig, float pt1, float pt2){
  
  cout << label << endl;

  int ichannel = 0;
  if (channel=="EE") ichannel=1;
  if (channel=="EMU") ichannel=2;
  
  FillEventCutFlow(4,"NoCut",ll_weight*WeightByTrigger(ll_trig[0],TargetLumi),label );

  //// DIMUON 
  /// define event variables                                                                                                                                                  
  snu::KParticle ll;
  if(ichannel==0){
    if(muons.size() ==2) ll= muons[0] + muons[1];
  }
  else  if(ichannel==1){
    if(electrons.size() ==2) ll= electrons[0] + electrons[1];
  }

  float llmass=ll.M();
  //// DIMUON --- B JETS
  int nbjet_l=0;
  int nbjet_m=0;
  int nbjet_t=0;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Loose))  nbjet_l++;
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium)) nbjet_m++;
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Tight))  nbjet_t++;
  }


  /// DIMUON --- ST + HT
  float ST (0.);
  if(ichannel==0&&muons.size() ==2)ST= muons[0].Pt() + muons[1].Pt();
  if(ichannel==1&&electrons.size() ==2)ST= electrons[0].Pt() + electrons[1].Pt();
  float HT=0.;
  for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
  for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
  ST+=eventbase->GetEvent().PFMET();
  

  /// DIMUON --- MET
  
  //// MET is corrected already for rochester 
  float met = eventbase->GetEvent().PFMET();
  float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;


  /// DIMUON --- dR leps,jets
  bool closejet=false;
  bool closejet2=false;
  float mindR=9999.;
  for(unsigned int ij2=0; ij2 <alljets.size(); ij2++){
    if (ichannel==0){
      for(unsigned int im=0; im <muons.size(); im++){
	if(muons.at(im).DeltaR(alljets.at(ij2)) <  0.5) closejet=true;
	else{
	  if(muons.at(im).DeltaR(alljets.at(ij2)) <  mindR){
	    mindR = muons.at(im).DeltaR(alljets.at(ij2));
	  }
	}
      }
    }
    else if (ichannel==1){
      for(unsigned int im=0; im <electrons.size(); im++){
        if(electrons.at(im).DeltaR(alljets.at(ij2)) <  0.5) closejet=true;
        else{
          if(electrons.at(im).DeltaR(alljets.at(ij2)) <  mindR){
            mindR = electrons.at(im).DeltaR(alljets.at(ij2));
          }
        }
      }
    }

  }

  float min_eleadawayjet_Dr= -10000.;
  
  for(UInt_t emme=0; emme<jets.size(); emme++){
    if (ichannel==0){
      for(UInt_t i=0; i<muons.size(); i++){  
	float dR =muons[i].DeltaR(jets[emme]);
	if(dR > 0.5) {
	  if(dR > min_eleadawayjet_Dr) {
	    min_eleadawayjet_Dr=  dR;
	    
	  }
	}
      }
    }
    else  if (ichannel==1){
      for(UInt_t i=0; i<electrons.size(); i++){
        float dR =electrons[i].DeltaR(jets[emme]);
        if(dR > 0.5) {
          if(dR > min_eleadawayjet_Dr) {
            min_eleadawayjet_Dr=  dR;

          }
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


  /// DIMUON ---   cut definitions

  bool cut1_dilep (0);
  if(ichannel==0) cut1_dilep =  (muons.size()==2 && (muons[1].Pt() > pt2 && muons[0].Pt() > pt1 ));
  if(ichannel==1) cut1_dilep =  (electrons.size()==2 && (electrons[1].Pt() > pt2 && electrons[0].Pt() > pt1 ));


  //if(muons.size()  > 2 && muons[2].Pt() > 10.) return;
  
  if(cut1_dilep){

    TString muid=_m_tightid;
    if(k_running_nonprompt) muid=_m_looseid;
    TString elid=_e_tightid;
    if(k_running_nonprompt) elid=_e_looseid;

    
    /// weight CF events 

    if(ichannel == 0) ll_weight *= MMWeight(muons,muid);
    if(ichannel == 1) ll_weight *= EEWeight(electrons,elid);
    FillEventCutFlow(4,"DiLep",ll_weight*WeightByTrigger(ll_trig[0], TargetLumi) ,label);
    FillHist("Nveto_1",(muons_veto.size() +electrons_veto.size()), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 5., 5);
    
    bool cut2_trig = PassTriggerOR(ll_trig);
    if(ll_trig[0].Contains("HLT_Iso")){
      std::vector<TString> triggerlist_DiMuon;
      triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      if(PassTriggerOR(triggerlist_DiMuon)) return;
    }
    if(!cut2_trig) return;
    

    //// correct weight to include trigger lumi
    if(!isData)  ll_weight*= WeightByTrigger(ll_trig[0], TargetLumi) ;

    FillHist("Nveto_2",(muons_veto.size() +electrons_veto.size()), ll_weight, 0., 5., 5);
    FillEventCutFlow(4,"Trigger",ll_weight,label);
	
    counter("Trigger",ll_weight);
    
    bool cut3_lepveto (0);
    if(ichannel == 0) cut3_lepveto = (electrons_veto.size()>0);
    if(ichannel == 1) cut3_lepveto = (muons_veto.size()>0);
    
    if(cut3_lepveto) return;

    counter("LepVeto",ll_weight);
	
    FillEventCutFlow(4,"LepVeto",ll_weight,label);
	
    vector<int> ijets;  
    
    histtype llhist = sighist_mm;
    if(ichannel==1) llhist = sighist_ee;


    bool cut4_ss(0);
    if(ichannel == 0) cut4_ss = (SameCharge(muons));
    if(ichannel == 1) {
      ll_weight              *= WeightCFEvent(electrons, k_running_chargeflip);
      cut4_ss = (ll_weight !=  0.);
    }
    if(cut4_ss){
      
      FillHist("Nveto_3",(muons_veto.size() +electrons_veto.size()), ll_weight, 0., 5., 5);
      
      FillEventCutFlow(4,"SSLLLoose",ll_weight,label);
      
      bool cut5_mll (0);
      if( ichannel==0 && llmass  > _mm_mll_presel_cut) cut5_mll=true;
      if( ichannel==1 && llmass  > _ee_mll_presel_cut) cut5_mll=true;
	
      if(cut5_mll){
	FillHist("Nveto_4",(muons_veto.size() +electrons_veto.size()), ll_weight, 0., 5., 5);
	

	FillEventCutFlow(4,"MLL",ll_weight,label);

	//FillEventComparisonFile("test");
	
	float ll_weight_fix=ll_weight;
	float ll_weight_sf=ll_weight;
	float ll_weight_df=ll_weight;
	float ll_weight_awayjet60=ll_weight;
	float ll_weight_awayjet20=ll_weight;
	if(k_running_nonprompt){
	  
	  if(ichannel==0){
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",0);
	    ll_weight_awayjet20=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_awayjet20");
	    ll_weight_awayjet60=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_awayjet60");
	    ll_weight_sf=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",1);
	    ll_weight_df=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",2);
	    if(PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TT_Preselection", ll_weight);
	    if(PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TT_Preselection_now", 1.);
	    if(PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TL_Preselection", ll_weight);
	    if(PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TL_Preselection_now", 1.);
	    if(!PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LT_Preselection", ll_weight);
	    if(!PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LT_Preselection_now", 1.);
	    if(!PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LL_Preselection", ll_weight);
	    if(!PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LL_Preselection_now", 1.);
	    
	  }
	  if(ichannel==1){
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",0);
	    ll_weight_awayjet20=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_awayjet20");
	    ll_weight_awayjet60=m_datadriven_bkg->Get_DataDrivenWeight_EE(false,electrons, _e_tightid, "ptcone", "fr_electron_awayjet60");
	    ll_weight_sf=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",1);
	    ll_weight_df=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",2);
	  }
	  
	  counter("SSLL_Preselection_sf", ll_weight_sf);
	  counter("SSLL_Preselection_df", ll_weight_df);
	  
	}
	
	counter("SSLL_Preselection", ll_weight);
	
	
	FillCLHist(llhist, label+"SSLL_nolepveto", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);


	bool cut6_lepveto (0);
	if(ichannel == 1) cut6_lepveto = (electrons_veto.size()> 2);
	if(ichannel == 0) cut6_lepveto = (muons_veto.size()>2);

	if(cut6_lepveto) return;


	if(ichannel==1){
	  
	  if(fabs(llmass - 91.) < 10.) {
	    FillCLHist(llhist, label+"SSLL_PreselectionZ", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	    return;
	  }
	}

	FillCLHist(llhist, label+"SSLL_Preselection", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	FillCLHist(llhist, label+"SSLL_Preselection_aj60", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_awayjet60);
	FillCLHist(llhist, label+"SSLL_Preselection_aj20", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_awayjet20);
	FillCLHist(llhist, label+"SSLL_Preselection_sf",  eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets, ll_weight_sf);
	FillCLHist(llhist, label+"SSLL_Preselection_df",  eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets, ll_weight_df);
	
	if(ichannel==0){
	  if((muons[0].DeltaR(muons[1])) > 0.4){
	    FillEventCutFlow(4,"lldR",ll_weight,label);
	  }  
	}
	if(ichannel==1){
	  if((electrons[0].DeltaR(electrons[1])) > 0.4){
	    FillEventCutFlow(4,"lldR",ll_weight,label);
	  }
	}
	
	FillHist("Nveto_5",(muons_veto.size() +electrons_veto.size()), ll_weight, 0., 5., 5);

		
	if(jets.size()==1) {
	  if( ( ichannel==0 && GetDiLepMass(muons) > 110) || (ichannel==1 && GetDiLepMass(electrons) > 110)){
	    FillCLHist(llhist, label+"SSLL_1JetCR", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	    FillEventCutFlow(4,"SSLL_1Jet",ll_weight,label);
	  }
	  else{
	    if(( ichannel==0 && GetDiLepMass(muons) > 15) || (ichannel==1 && GetDiLepMass(electrons) > 15)){
	      if(eventbase->GetEvent().PFMET() < 60.) {
		if(NBJet(alljets) ==0){
		  if(( ichannel==0 &&  (muons[0].DeltaR(muons[1])  < 3.4)) || (ichannel==1 &&  (electrons[0].DeltaR(electrons[1])  < 3.4))) {
		    if(( ichannel==0 && (GetLT(muons)/(SumPt(jets)+SumPt(fatjets)) ) > 0.8) || (ichannel==1 && (GetLT(electrons)/(SumPt(jets)+SumPt(fatjets)))  > 0.8)){
		      FillEventCutFlow(4,"SSLL_1JetOpt",ll_weight,label);
		      FillCLHist(llhist, label+"SSLL_1JetOpt", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
		      if((ichannel==0 && GetDiLepMass(muons) < 60) || (ichannel==1 && GetDiLepMass(electrons) < 60)){
			FillCLHist(llhist, label+"SSLL_1JetOpt2", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
			FillEventCutFlow(4,"SSLL_1JetOpt2",ll_weight,label);
		      }
		      if(( ichannel == 0 && muons[1].Pt() > 15) || (ichannel == 1 && electrons[1].Pt() > 20)){
			FillCLHist(llhist, label+"SSLL_1JetOpt_pt2", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
			if((ichannel==0 && GetDiLepMass(muons) < 60) || (ichannel==1 && GetDiLepMass(electrons) < 60)) FillCLHist(llhist, label+"SSLL_1JetOpt2_pt2", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
			FillEventCutFlow(4,"SSLL_1JetOpt_pt2",ll_weight,label);
			if((ichannel==0 && GetDiLepMass(muons) < 60) || (ichannel==1 && GetDiLepMass(electrons) < 60))FillEventCutFlow(4,"SSLL_1JetOpt2_pt2",ll_weight);
			if(eventbase->GetEvent().PFMET() < 60.) {
			  if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 1,ll_weight,  0., 22., 22);
			  if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 2,ll_weight,  0., 22., 22);
			  if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 3,ll_weight,  0., 22., 22);
			}
			if(eventbase->GetEvent().PFMET() < 50.) {
                          if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 4,ll_weight,  0., 22., 22);
                          if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 5,ll_weight,  0., 22., 22);
                          if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 6,ll_weight,  0., 22., 22);
                        }
			if(eventbase->GetEvent().PFMET() < 40.) {
                          if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 7,ll_weight,  0., 22., 22);
                          if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 8,ll_weight,  0., 22., 22);
                          if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 9,ll_weight,  0., 22., 22);
                        }
		      
			float dphi_1 (0.);
			if(ichannel==0) dphi_1= fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
			if(ichannel==1) dphi_1= fabs(TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));

			float MT_1 (0.);
			if(ichannel==0) MT_1= sqrt(2.* muons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
			if(ichannel==1) MT_1= sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));


			float dphi_2 (0.);
			if(ichannel==0) dphi_2= fabs(TVector2::Phi_mpi_pi(muons.at(1).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
			if(ichannel==1) dphi_2= fabs(TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
			float MT_2 (0.);
			if(ichannel==0) MT_2= sqrt(2.* muons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
			if(ichannel==1) MT_2= sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
			
			if(MT_1 < 80 && MT_2 < 80){
			  if(eventbase->GetEvent().PFMET() < 60.) {
			    if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 10,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 11,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 12,ll_weight,  0., 22., 22);
			  }
			  if(eventbase->GetEvent().PFMET() < 50.) {
			    if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 13,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 14,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 15,ll_weight,  0., 22., 22);
			  }
			  if(eventbase->GetEvent().PFMET() < 40.) {
			    if(ichannel==0 && GetDiLepMass(muons) < 70)  FillHist(label+"LowMassSIG1Jet", 16,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 60)  FillHist(label+"LowMassSIG1Jet", 17,ll_weight,  0., 22., 22);
			    if(ichannel==0 && GetDiLepMass(muons) < 50)  FillHist(label+"LowMassSIG1Jet", 18,ll_weight,  0., 22., 22);
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

	if(jets.size() == 0)                   FillCLHist(llhist, label+"SSLL_0Jet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	if(jets.size() == 1)                   FillCLHist(llhist, label+"SSLL_1Jet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	if(jets.size() == 2)                   FillCLHist(llhist, label+"SSLL_2Jet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	if(jets.size() == 3)                   FillCLHist(llhist, label+"SSLL_3Jet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	if(jets.size() >= 4)                   FillCLHist(llhist, label+"SSLL_4Jet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	
	
	float jetpt=20.;
	if(label.Contains("lowjetp")) jetpt=10.;
	std::vector<snu::KJet>  jets_2p7 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",jetpt, 2.7);
	std::vector<snu::KJet>  jets_pu = GetJetsWFT("JET_HN_PU", "FATJET_HN_tau06",jetpt, 2.5);
	std::vector<snu::KJet>  jets_tight = GetJetsWFT("JET_HN_TIGHT", "FATJET_HN_tau06",jetpt, 2.5);
	std::vector<snu::KJet>  jets_tightlv = GetJetsWFT("JET_HN_TIGHTLV", "FATJET_HN_tau06",jetpt, 2.5);
	std::vector<snu::KFatJet> fatjetcoll_all = GetFatJets("FATJET_NOCUT");
	
	
	if(jets_2p7.size() > 1)FillCLHist(llhist, label+"SSLL_DiJet_j27", eventbase->GetEvent(), muons, electrons,jets_2p7, alljets, fatjets,ll_weight);
	if(jets_pu.size() > 1)FillCLHist(llhist, label+"SSLL_DiJet_pujet",eventbase->GetEvent(), muons, electrons,jets_pu, alljets, fatjets,ll_weight);
	if(jets_tight.size() > 1)FillCLHist(llhist, label+"SSLL_DiJet_tightjet",  eventbase->GetEvent(), muons, electrons,jets_tight, alljets, fatjets,ll_weight);
	if(jets_tightlv.size() >1 )FillCLHist(llhist, label+"SSLL_DiJet_tightjetlv",  eventbase->GetEvent(), muons, electrons,jets_tightlv, alljets, fatjets,ll_weight);
	  

	if(jets.size() > 1){
	  FillHist("Nveto_6",(muons_veto.size() +electrons_veto.size()), ll_weight, 0., 5., 5);

	  FillEventCutFlow(4,"SSLL_DiJet",ll_weight,label);
	  FillCLHist(llhist, label+"SSLL_DiJet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  FillCLHist(llhist, label+"SSLL_DiJet_noW", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,WeightByTrigger(ll_trig[0],TargetLumi)* GetKFactor()*weight);
	  if(NBJet(alljets) ==0)                   FillCLHist(llhist, label+"SSLL_DiJet_noB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  else FillCLHist(llhist, label+"SSLL_DiJet_FailnoB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  
	  if(NBJet(alljets) ==0)   {
	    FillEventCutFlow(4,"SSLL_DiJet_noB",ll_weight,label);
	    if(eventbase->GetEvent().PFMET() < 80.) {
	      FillCLHist(llhist, label+"SSLL_DiJet_passMET", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    }
	    
	    if((eventbase->GetEvent().PFMET() < 60.)) {
	      if(HT < 200){
		FillEventCutFlow(4,"SSLL_DiJet_passHT300",ll_weight,label);
		FillCLHist(llhist, label+"SSLL_DiJet_passHT3", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
		bool closejet=false;
		bool closejet2=false;
		float mindR=9999.;
		if(ichannel==0){
		  for(unsigned int im=0; im <muons.size(); im++){
		    for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
		      if(muons.at(im).DeltaR(jets.at(ij2)) <  0.5) closejet=true;
		      if(muons.at(im).DeltaR(jets.at(ij2)) <  mindR){
			mindR = muons.at(im).DeltaR(jets.at(ij2));
		      }
		    }
		  }
		}
		if(ichannel==1){
		  for(unsigned int im=0; im <electrons.size(); im++){
		    for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
		      if(electrons.at(im).DeltaR(jets.at(ij2)) <  0.5) closejet=true;
		      if(electrons.at(im).DeltaR(jets.at(ij2)) <  mindR){
			mindR = electrons.at(im).DeltaR(jets.at(ij2));
		      }
		    }
		  }
		}
		
		if(mindR > 3.2) closejet2=true;
		if(!closejet){
		  
		  if(ichannel== 0 && muons[0].DeltaR(muons[1])  < 4.) FillCLHist(llhist, label+"SSLL_DiJet_passDR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
		  if(ichannel== 1 && electrons[0].DeltaR(electrons[1])  < 4.) FillCLHist(llhist, label+"SSLL_DiJet_passDR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

		  if((ichannel==0 && muons[0].DeltaR(muons[1])  < 3.4) || (ichannel== 1 && electrons[0].DeltaR(electrons[1])  < 3.4)) {
		    FillEventCutFlow(4,"SSLL_DiJet_passDR2",ll_weight,label);
		    
		    FillCLHist(llhist, label+"SSLL_DiJet_passDR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
		    

		    float dphi_1 (0.);
		    if(ichannel==0) dphi_1= fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
		    if(ichannel==1) dphi_1= fabs(TVector2::Phi_mpi_pi(electrons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));

		    float MT_1 (0.);
		    if(ichannel==0) MT_1= sqrt(2.* muons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
		    if(ichannel==1) MT_1= sqrt(2.* electrons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));

		    
		    float dphi_2 (0.);
		    if(ichannel==0) dphi_2= fabs(TVector2::Phi_mpi_pi(muons.at(1).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
		    if(ichannel==1) dphi_2= fabs(TVector2::Phi_mpi_pi(electrons.at(1).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
		    float MT_2 (0.);
		    if(ichannel==0) MT_2= sqrt(2.* muons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
		    if(ichannel==1) MT_2= sqrt(2.* electrons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
		    

		    if(!closejet2){
		      FillEventCutFlow(4,"SSLL_DiJet_passLJ",ll_weight,label);
		      
		      FillCLHist(llhist, label+"SSLL_DiJet_passLJ", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
		      if(MT_1 < 100 && MT_2 < 100)                                 FillEventCutFlow(4,"SSLL_DiJet_passMT100",ll_weight,label);
		      if(MT_1 < 90 && MT_2 < 90)                                 FillEventCutFlow(4,"SSLL_DiJet_passMT90",ll_weight,label);
		      
		      if(MT_1 < 80 || MT_2 < 80){
			FillEventCutFlow(4,"SSLL_DiJet_passMT80",ll_weight,label);
			
			FillCLHist(llhist, label+"SSLL_DiJet_passMT", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
			if( (ichannel ==0 && muons[1].Pt() > 15) || (ichannel ==1 && electrons[1].Pt() > 20.)) {
			  FillEventCutFlow(4,"SSLL_DiJet_passpt2",ll_weight,label);
			  
			  FillCLHist(llhist, label+"SSLL_DiJet_passpt2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
			}
			
			int s_awayjetdr(0), s_mll(0), s_pt(0), s_mllj(0), s_met(0), s_l2jj(0), s_lljj(0), s_contraMass(0), s_st(0);
			int nsig_reg=0;
			if((ichannel==0 && GetDiLepMass(muons) < 70) || (ichannel==1 && GetDiLepMass(electrons) < 70))s_mll=1;
			else s_mll=2;
			

			if(ichannel==0){
			  if(muons[1].Pt() < 15) s_pt=1;
			  else s_pt=2;
			  
			  if((muons[0]+muons[1]+jets[0]).M() < 100) s_mllj=1;
			  else if((muons[0]+muons[1]+jets[0]).M() < 150)  s_mllj=2;
			  else if((muons[0]+muons[1]+jets[0]).M() < 175)  s_mllj=3;
			  else if((muons[0]+muons[1]+jets[0]).M() < 200)  s_mllj=4;
			  else if((muons[0]+muons[1]+jets[0]).M() < 225)s_mllj=5;
			  else if((muons[0]+muons[1]+jets[0]).M() < 250)s_mllj=6;
			  else if((muons[0]+muons[1]+jets[0]).M() < 300)s_mllj=7;
			  
			  if(eventbase->GetEvent().PFMET() < 20)    s_met=1;
			  else if(eventbase->GetEvent().PFMET() < 40)    s_met=2;
			  else if(eventbase->GetEvent().PFMET() < 60)    s_met=3;
			  
			  if(ST < 150) s_st=1;
			  else if(ST < 175) s_st=2;
			  else if(ST < 200) s_st=3;
			  else if(ST < 250) s_st=4;
			  else s_st=5;
			  
			  if(GetMasses("l2jj", muons, jets, ijets, true) < 80) s_l2jj=1;
			  else if(GetMasses("l2jj", muons, jets, ijets, true) < 120) s_l2jj=2;
			  else if(GetMasses("l2jj", muons, jets,  ijets,true) < 200) s_l2jj=3;
			  else if(GetMasses("l2jj", muons, jets, ijets, true) < 300) s_l2jj=4;
			  
			  if(GetMasses("lljj", muons, jets,  ijets,true) < 100) s_lljj=1;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 150) s_lljj=2;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 175) s_lljj=3;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 200) s_lljj=4;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 250) s_lljj=5;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 300) s_lljj=6;
			  else if(GetMasses("lljj", muons, jets,  ijets,true) < 400) s_lljj=7;
			  
			  if(GetMasses("contMT", muons, jets,  ijets,true) < 25) s_contraMass=1;
			  else 				if(GetMasses("contMT", muons, jets,  ijets,true) < 50) s_contraMass=2;
			  else 				if(GetMasses("contMT", muons, jets,  ijets,true) < 100) s_contraMass=3;
			  
			  
			  float min_eleadawayjet_Dr= -10000.;
			  for(UInt_t i=0; i<muons.size(); i++){
			    for(UInt_t emme=0; emme<jets.size(); emme++){
			      float dR =muons[i].DeltaR(jets[emme]);
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
					  FillHist(label+"Sig_Regions1",nsig_reg, ll_weight, 0., 90., 90);
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
					  FillHist(label+"Sig_Regions2",nsig_reg, ll_weight, 0., 90., 90);
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
					      
					      FillHist(label+"Sig_Regions3",nsig_reg, ll_weight, 0., 90., 90);
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
			
			  if(ichannel==1 && GetDiLepMass(muons) < 70){
			    FillEventCutFlow(4,"SSLL_DiJet_passmll",ll_weight,label);
			    
			    if(muons[1].Pt() < 40. && muons[0].Pt() < 60. )FillCLHist(llhist, label+"SSLL_DiJet_passmll", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);   
			    if(muons[1].Pt() > 15) {
			      FillEventCutFlow(4,"SSLL_DiJet_passpt2mll",ll_weight,label);
			      
			      if(muons[1].Pt() < 40. && muons[0].Pt() < 60. )FillCLHist(llhist, label+"SSLL_DiJet_passpt2mll", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
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
      

	
	int nf(0);
	if(jets.size() > 2){
	  for(unsigned int ij = 0 ; ij < tjets.size(); ij++){
	    if(fabs(tjets[ij].Eta()) > 2.)nf++;
	  }
	  
	  if(nf>0)FillCLHist(llhist, label+"SSLL_DiTJet", eventbase->GetEvent(), muons, electrons,tjets, alljets,  fatjets,ll_weight);
	}
	  

	
	if( (ichannel==0 && CheckSignalRegion(true,muons,electrons_veto , jets, alljets,"LowMM", ll_weight)) || (ichannel==1 && CheckSignalRegion(true,muons_veto,electrons , jets, alljets,"LowEE", ll_weight))){
	  if(nbjet_m==0){
	    if(met < 80){
	      FillCLHist(llhist, label+"SSLL_LowMass_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    }
	    
	    if(met < 60 && GetDiLepMass(electrons) < 70&& ichannel==1)FillCLHist(llhist, label+"SSLL_LowMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(met < 60 && GetDiLepMass(muons) < 70&& ichannel==0)FillCLHist(llhist, label+"SSLL_LowMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(met < 60 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 1,ll_weight,  0., 22., 22);
	    if(met < 60 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 2,ll_weight,  0., 22., 22);
	    if(met < 60 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 3,ll_weight,  0., 22., 22);
	    if(GetDiLepMass(muons) > 15.){
	      if(met < 60 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 4,ll_weight,  0., 22., 22);
	      if(met < 60 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 5,ll_weight,  0., 22., 22);
	      if(met < 60 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 6,ll_weight,  0., 22., 22);
	    }
	    if(GetDiLepMass(muons) > 20.){
	      if(met < 60 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 7,ll_weight,  0., 22., 22);
              if(met < 60 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 8,ll_weight,  0., 22., 22);
              if(met < 60 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 9,ll_weight,  0., 22., 22);
	    }   
	    if(GetDiLepMass(muons) > 25.){
	      if(met < 50 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 10,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 11,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 12,ll_weight,  0., 22., 22);
	    }   
	    if(GetDiLepMass(muons) > 15.){
              if(met < 50 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 13,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 14,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 15,ll_weight,  0., 22., 22);
            }
            if(GetDiLepMass(muons) > 20.){
              if(met < 50 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 16,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 17,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 18,ll_weight,  0., 22., 22);
            }
            if(GetDiLepMass(muons) > 25.){
              if(met < 50 && GetDiLepMass(muons) < 70&& ichannel==0)FillHist(label+"LowMassSIG", 19,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 110&& ichannel==0)FillHist(label+"LowMassSIG", 20,ll_weight,  0., 22., 22);
              if(met < 50 && GetDiLepMass(muons) < 60&& ichannel==0)FillHist(label+"LowMassSIG", 21,ll_weight,  0., 22., 22);
            }

	    
	  }
	  if(met > 100 || nbjet_m > 0)FillCLHist(llhist, label+"SSLL_LowMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	}
	
	if((ichannel==0 && CheckSignalRegion(true,muons,electrons_veto , jets, alljets,"HighMM", ll_weight)) ){
	  if(nbjet_m==0){
	    if(met2_st < 15) FillCLHist(llhist, label+"SSLL_HighMass_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(met2_st < 10&& muons[1].Pt() > 20&&jets[0].Pt() > 25.) FillCLHist(llhist, label+"SSLL_HighMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(met2_st < 10&& muons[1].Pt() > 40&&jets[0].Pt() > 25.) FillCLHist(llhist, label+"SSLL_HighMass_SR3", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    int nc(0);
	    for(unsigned int ij=0; ij < jets.size(); ij++){
	      if(fabs(jets[ij].Eta()) < 1.5) nc++;
	    }
	    
	    if(met2_st < 15 && nc < 2) FillCLHist(llhist, label+"SSLL_HighMass_SR4", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(met2_st < 15 && nc >= 2) FillCLHist(llhist, label+"SSLL_HighMass_SR5", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	   
	  }
	  if(met2_st > 20 || nbjet_m > 0)FillCLHist(llhist, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	}
      }
    }
  }
  
  
  
  return;
}


float HNDiLepton::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip){
  
  if(electrons.size()!=2) return 0.;
  if(runchargeflip) {
    
    TString el_ID = "ELECTRON_HN_TIGHTv4";

    if(el_ID != "ELECTRON_HN_TIGHTv4") return 0.;
    if(electrons.size() > 2) return 0.;

    std::vector<snu::KElectron> lep;
    for(int i=0; i<electrons.size(); i++){
      lep.push_back(electrons.at(i));
    }

    if(lep.size()==2){
      if(lep.at(0).Charge() == lep.at(1).Charge()) return 0.;
    }

    std::vector<double> CFrate, CFweight, sf;
    for(int i=0; i<lep.size(); i++){
      CFrate.push_back(GetCFRates(lep.at(i).Pt(), lep.at(i).SCEta(), el_ID));
      CFweight.push_back( (CFrate.at(i)/(1-CFrate.at(i))) );
    }
    bool apply_sf=1.;
    float syst=0.;
    for(int i=0; i<lep.size(); i++){
      if(apply_sf){
	if(fabs(lep.at(i).SCEta()) < 1.4442){
	  sf.push_back(0.691722 + (syst*0.691722*0.13));
	}
	else{
	  sf.push_back(0.68301 + (syst*0.68301*0.09));
	}
      }
      else{
	sf.push_back( 1 );
      }
    }

    double cfweight = 0.;
    for(int i=0; i<lep.size(); i++){
      cfweight += (sf.at(i)) * (CFweight.at(i));
    }
    return cfweight;
  }// cf requirement
  else {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()) return 0.;
  }
  
  return 1.;
  
}


void HNDiLepton::FillEventCutFlow(int cf,TString cut,  float wt, TString label){
  
  if(cf==0){
    if(GetHist( label+"ll_eventcutflow")) {
      GetHist( label+"ll_eventcutflow")->Fill(cut,wt);
      
    }
    else{
      AnalyzerCore::MakeHistograms( label+"ll_eventcutflow",15,0.,15.);

      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(2,"DiLooseLL");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(3,"LepVeto");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(4,"L1Pt");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(5,"L2Pt5");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(6,"L2Pt10");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(7,"L2Pt15");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(8,"L153");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(9,"L153L2");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(10,"SSLLLoose");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(11,"MLL");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(12,"mmdR");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(13,"DiJet");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(14,"DiNewJet");
      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(15,"SSLLTight");
      GetHist( label+"ll_eventcutflow")->Fill(cut,wt);

    }
  }
  if(cf==1){
    if(GetHist( label+"cutflow_challenge")) {
      GetHist( label+"cutflow_challenge")->Fill(cut,wt);
      
    }
    else{
      AnalyzerCore::MakeHistograms( label+"cutflow_challenge",11,0.,11.);

      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(1,"1_NoCut");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(2,"2_EventClean");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(3,"3_DiMu");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(4,"4_MuVeto");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(5,"5_ElVeto");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(6,"6_mll");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(7,"7_DiJet");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(8,"8_MET");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(9,"9_mjj");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(10,"91_bjetv1");
      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(11,"92_bjetv2");

      GetHist( label+"cutflow_challenge")->Fill(cut,wt);
      
    }
  }
  if(cf==-1){
    if(GetHist( label+"noWeightcutflow_challenge")) {
      GetHist( label+"noWeightcutflow_challenge")->Fill(cut,wt);

    }
    else{
      
      AnalyzerCore::MakeHistograms( label+"noWeightcutflow_challenge",11,0.,11.);

      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(1,"NoWeight_1_NoCut");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(2,"NoWeight_2_EventClean");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(3,"NoWeight_3_DiMu");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(4,"NoWeight_4_MuVeto");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(5,"NoWeight_5_ElVeto");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(6,"NoWeight_6_mll");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(7,"NoWeight_7_DiJet");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(8,"NoWeight_8_MET");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(9,"NoWeight_9_mjj");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(10,"NoWeight_10_bjetv1");
      GetHist( label+"noWeightcutflow_challenge")->GetXaxis()->SetBinLabel(11,"NoWeight_11_bjetv2");
      
      
      GetHist( label+"noWeightcutflow_challenge")->Fill(cut,wt);
      
    }
  }
  
  if(cf==2){
    if(GetHist(label +  "ll_eventcutflow_LowMassDoubleMuon")) {
      GetHist(label +  "ll_eventcutflow_LowMassDoubleMuon")->Fill(cut,wt);

    }
    else{
      
      vector<TString> IDs;
      IDs.push_back("LowMassLL_HNTIGHT");
      IDs.push_back("LowMassLL_HNTIGHT2");
      IDs.push_back("LowMassLL_HNTIGHT3");
      IDs.push_back("LowMassLL_HNTIGHT4");
      IDs.push_back("LowMassLL_HNTIGHT5");
      IDs.push_back("LowMassLL_HNTIGHT6");
      AnalyzerCore::MakeHistograms(label +  "ll_eventcutflow_LowMassDoubleMuon",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist(label +  "ll_eventcutflow_LowMassDoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist(label +  "ll_eventcutflow_LowMassDoubleMuon")->Fill(cut,wt);

    }
  }
  
  if(cf==3){
    if(GetHist( label + "ll_eventcutflow_HighMassDoubleMuon")) {
      GetHist( label + "ll_eventcutflow_HighMassDoubleMuon")->Fill(cut,wt);

    }
    else{

      vector<TString> IDs;
      IDs.push_back("HighMassLL_HNTIGHT");
      IDs.push_back("HighMassLL_HNTIGHT2");
      IDs.push_back("HighMassLL_HNTIGHT3");
      IDs.push_back("HighMassLL_HNTIGHT4");
      IDs.push_back("HighMassLL_HNTIGHT5");
      IDs.push_back("HighMassLL_HNTIGHT6");
      AnalyzerCore::MakeHistograms( label + "ll_eventcutflow_HighMassDoubleMuon",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

	TString elid = IDs[iid];
	GetHist( label + "ll_eventcutflow_HighMassDoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( label + "ll_eventcutflow_HighMassDoubleMuon")->Fill(cut,wt);

    }
  }
  if(cf==4){
    if(GetHist( label + "ll_lowmassopt_cutflow")) {
      GetHist( label + "ll_lowmassopt_cutflow")->Fill(cut,wt);
      counter(label+"_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("NoCut");
      IDs.push_back("DiLep");
      IDs.push_back("Trigger");
      IDs.push_back("LepVeto");
      IDs.push_back("SSLLLoose");
      IDs.push_back("MLL");
      IDs.push_back("lldR");
      IDs.push_back("SSLL_DiJet_noB");
      IDs.push_back("SSLL_FatJet");
      IDs.push_back("SSLL_NoFatJet");
      IDs.push_back("SSLL_1Jet");
      IDs.push_back("SSLL_1JetOpt");
      IDs.push_back("SSLL_1JetOpt2");
      IDs.push_back("SSLL_1JetOpt_pt2");
      IDs.push_back("SSLL_1JetOpt2_pt2");
      IDs.push_back("SSLL_DiJet");      
      IDs.push_back("SSLL_DiJet_passHT300");
      IDs.push_back("SSLL_DiJet_passDR2");
      IDs.push_back("SSLL_DiJet_passMT80");
      IDs.push_back("SSLL_DiJet_passMT90");
      IDs.push_back("SSLL_DiJet_passMT100");
      IDs.push_back("SSLL_DiJet_passLJ");
      IDs.push_back("SSLL_DiJet_passmll");
      IDs.push_back("SSLL_DiJet_passpt2");
      IDs.push_back("SSLL_DiJet_passpt2mll");


      AnalyzerCore::MakeHistograms( label + "ll_lowmassopt_cutflow",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_lowmassopt_cutflow")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_"+cut ,wt);
      
      GetHist( label + "ll_lowmassopt_cutflow")->Fill(cut,wt);

    }
  }




}

void HNDiLepton::FillEventCutFlow(TString cut, TString label, float weight){

  if(GetHist(label + "_eventcutflow")) {
    GetHist(label + "_eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms(label + "_eventcutflow",10,0.,10.);

    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(1,"SSLL_loose");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(2,"SSLL_tightiso");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(3,"SSLL_tightiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(4,"SSLL_tightmdiso1");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(5,"SSLL_tightmdiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(6,"SSLL_tightmdiso3");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(7,"SSLL_tightmdiso4");
  }
  
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
  bool mm=false;
  bool ee=false;
  if(name.Contains("MM")){
    mm=true;
    if(el.size() > 0) return false ;
    if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
    // Set by trigger                                                                                                                                                                                                                                                
    if(muons.at(0).Pt() < 20.) {if(debug)cout << "Fail pt1 " << endl; return false;}
    if(muons.at(1).Pt() < 5.)  {if(debug)cout << "Fail pt2  " << endl; return false;}
    
    if(isss&&!SameCharge(muons)) {if(debug)cout << "Fail ss " << endl; return false;}

    if(!isss&&SameCharge(muons)) {if(debug)cout << "Fail os  " << endl; return false;}
    snu::KParticle mm = muons.at(0) + muons.at(1);
    if(mm.M()  < _mm_mll_presel_cut) {if(debug)cout << "Fail mee  " << endl; return false;}
  }
  if(name.Contains("EE")){
    ee=true;
    if(muons.size() > 0) return false ;
    if(el.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
    // Set by trigger                                                                                                                                                                                                                                                           
    if(el.at(0).Pt() < 25.) {if(debug)cout << "Fail pt1 " << endl; return false;}
    if(el.at(1).Pt() < 5.)  {if(debug)cout << "Fail pt2  " << endl; return false;}

    if(isss&&!SameCharge(el)) {if(debug)cout << "Fail ss " << endl; return false;}

    if(!isss&&SameCharge(el)) {if(debug)cout << "Fail os  " << endl; return false;}
    snu::KParticle ee = el.at(0) + el.at(1);
    if(fabs(ee.M() - 90.) < 10.) return false;
    if(ee.M()  < _ee_mll_presel_cut) {if(debug)cout << "Fail mee  " << endl; return false;}
  }

  if(name.Contains("High")){
    if(name.Contains("MM")){
      if(muons.at(0).Pt() < 20.) return false;
    }
  }
  else{
    float met = eventbase->GetEvent().PFMET();
  }
  if(jets.size() < 2) {if(debug)cout << "Fail jets " << endl; return false;}
  

  if(jets.size() > 1) {
    float dijetmass_tmp=999.;
    float dijetmass=9990000.;
    int m=-999;
    int n=-999;
    for(UInt_t emme=0; emme<jets.size(); emme++){
      for(UInt_t enne=1; enne<jets.size(); enne++) {
	if(emme == enne) continue;
	if(name.Contains("Low")){
	  if(mm)dijetmass_tmp = (jets[emme]+jets[enne]+muons[0] + muons[1]).M();
	  if(ee)dijetmass_tmp = (jets[emme]+jets[enne]+el[0] + el[1]).M();
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
      if(mm){
	if((jets[m] + jets[n] + muons[0] + muons[1]).M() > 300.)  return false;
      }
      if(ee){
	if((jets[m] + jets[n] + el[0] + el[1]).M() > 300.)  return false;
      }
    }
    else{
      if(jj.M() > 150.) {if(debug)cout << "Fail mjj  " << endl; return false;}
      
    }
    if(debug)cout << "PASSES ID" << endl;
  }
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
  //FillEventCutFlow(1,cut,w);
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
  
  /// If ConfigureFake is used then no fake histograms are setup in HNCommonFake code so you MUST setup in your anlayis code if you wish to use this code

  if(configure_fakes)ConfigureFake();
  

  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");
  
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



