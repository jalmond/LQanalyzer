// $Id: RExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
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
      //labels.push_back("DiMuon_SIP");
      labels.push_back("DiMuon_inclusive");
      labels.push_back("DiMuon_inclusive_OR");
      labels.push_back("DiMuon_jets_eta5");
      labels.push_back("DiMuon_jets_pt10_eta5");
      labels.push_back("DiMuon_jets_pt10");
      labels.push_back("DiMuon_8TeV");
      labels.push_back("DiMuon_FAT");
      labels.push_back("DiMuon_NoFAT");
      //      labels.push_back("DiMuon_lowjetpt");
      //      labels.push_back("DiMuon_tightveto");
      //labels.push_back("DiMuon_isomu");
    }
    //    labels.push_back("DiMuon_allFJ");

    
    vector<TString> labelsE;
    if(!k_isdata || (k_channel=="DoubleEG" ||  k_channel=="SingleElectron")){
      //  labelsE.push_back("DiEl");
      //labelsE.push_back("DiEl_singleEl");
    }
    
    for(unsigned int il = 0; il < labels.size(); il++){
      histtype llhist = sighist_mm;
      TString label = labels.at(il);
      MakeCleverHistograms(llhist, label + "SSLL_nolepveto");
      MakeCleverHistograms(llhist, label+"SSLL_Preselection");
      MakeCleverHistograms(llhist, label+"SSLL_DiJet");
      if(label.Contains("DiMuon_inclusive")){
	MakeCleverHistograms(llhist, label+"SSLL_1JetCR");
	MakeCleverHistograms(llhist, label+"SSLL_1JetSR");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR0");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_SR2");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_1Jet_SR");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_1Jet_SR0");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_CR");
	MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR2");
	MakeCleverHistograms(llhist, label+"SSLL_LowMass_8TeV");
	MakeCleverHistograms(llhist, label+"SSLL_HighMass_SR");
	MakeCleverHistograms(llhist, label+"SSLL_HighMass_CR");
	MakeCleverHistograms(llhist, label+"SSLL_DiJet_noB");
	MakeCleverHistograms(llhist, label+"SSLL_DiJet_FailnoB");
	MakeCleverHistograms(llhist, label+"SSLL_DiJet_passMET");
	MakeCleverHistograms(llhist, label+"SSLL_LT");
      }
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
  

  if(IsSignal())GetTriggEfficiency(5.,"_5");
  if(IsSignal())GetTriggEfficiency(10.,"_10");
  if(IsSignal())GetTriggEfficiency(15.,"_15");

  //bool SBt_JSf = CheckEventComparison("jalmond","SB_fake_mu22107_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FR_syst_cal_fix","jalmond","JS_fake_mu22108_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FRCalculator_Mu_dxysig_DILEP_fix",false);

  //for(unsigned int ipdf=0; ipdf < eventbase->GetEvent().PdfWeights().size() ; ipdf++){
  //cout << ipdf << " " << eventbase->GetEvent().PdfWeights().at(ipdf) << " " <<   eventbase->GetEvent().LHEWeight()<< " "<< eventbase->GetEvent().MCWeight() <<  endl;
    
  ///    }
  
    
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
      fake_hists["fr_muon_sip_central"] = std::make_pair(std::make_pair("Muon_Data_HighdXY_Large_FR.root","Muon_Data_HighdXY_Large_FR_Awayjet40")  , std::make_pair(70., "TH2D"));
      fake_hists["fr_muon_8TeV_central"] = std::make_pair(std::make_pair("Muon_Data_8TeV_FR.root","Muon_Data_8TeV_FR_Awayjet40")  , std::make_pair(70., "TH2D"));

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
  _m_channel =   isData ?  (k_channel.Contains("SingleMuon")) : false ;
  _ee_channel =   isData ?  (k_channel.Contains("DoubleEG")) : true ;
  _e_channel =   isData ?  (k_channel.Contains("SingleElectron")) : false ;
  _em_channel =   isData ?  (k_channel.Contains("MuonEG")) : true ;

  TString muid=_m_tightid;
  if(k_running_nonprompt) muid=_m_looseid;
  
  TString elid=_e_tightid;
  if(k_running_nonprompt) elid=_e_looseid;
  
  std::vector<snu::KMuon> muons_fake = GetMuons(muid,true);
  std::vector<snu::KMuon> muons = GetMuons(muid,true);

  TString muid_sip=_m_tightid;
  if(k_running_nonprompt) muid_sip="MUON_HN_Loose_HighdXY_Small";
  std::vector<snu::KMuon> muons_highDXY = GetMuons(muid_sip,false);
  

  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",true);

  if(isData&& !k_running_nonprompt){
    if(SameCharge(muons_veto)){
      if(PassID(muons_veto[0],muid) && muons_veto[0].Pt() > 20) {
	float mu_pt_corr = muons_veto.at(1).Pt()*(1+max(0.,(muons_veto.at(1).RelIso04()-0.07))) ; /// will need changing for systematics
	Float_t ptbins[11] = { 5., 12., 15.,20.,25.,30.,35.,45.,  60.,100., 200.};
	if(PassID(muons_veto[1],"MUON_HN_Loose_HighdXY")){
	  
	  FillHist("HighDXY_isopt",  mu_pt_corr,  muons_veto.at(1).RelIso04()*mu_pt_corr, 1., 0., 500., 100., 0., 100., 50);


	  FillHist("SS_auxFake_ptcone_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 ) 	FillHist("SS_auxFake_ptcone_bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  else   FillHist("SS_auxFake_ptcone_0bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(fabs(muons_veto[1].Eta())< 0.9)	FillHist("SS_auxFake_ptcone_IB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(muons_veto[1].Eta())< 1.5)	FillHist("SS_auxFake_ptcone_OB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(muons_veto[1].Eta())< 2.5)	FillHist("SS_auxFake_ptcone_EC_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(PassID(muons_veto[1],"MUON_HN_Tight_HighdXY")){
	    FillHist("SS_auxFake_ptcone_tight",mu_pt_corr, 1., ptbins, 10 );
	    if(fabs(muons_veto[1].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(muons_veto[1].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(muons_veto[1].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	    if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    else   FillHist("SS_auxFake_ptcone_0bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	  }
	}
      }
      if(PassID(muons_veto[1],muid) && muons_veto[1].Pt() > 20) {
	float mu_pt_corr = muons_veto.at(0).Pt()*(1+max(0.,(muons_veto.at(0).RelIso04()-0.07))) ; /// will need changing for systematics                                               
	Float_t ptbins[11] = { 5., 12., 15.,20.,25.,30.,35.,45.,  60.,100., 200.};
	if(PassID(muons_veto[0],"MUON_HN_Loose_HighdXY")){

          FillHist("HighDXY_isopt",  mu_pt_corr,  muons_veto.at(0).RelIso04()*mu_pt_corr, 1., 0., 500., 100., 0., 100., 50);

	  FillHist("SS_auxFake_ptcone_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(fabs(muons_veto[0].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(muons_veto[0].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(muons_veto[0].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  else   FillHist("SS_auxFake_ptcone_0bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  
	  if(PassID(muons_veto[0],"MUON_HN_Tight_HighdXY")){
	    FillHist("SS_auxFake_ptcone_tight",mu_pt_corr, 1., ptbins, 10 );
	    if(fabs(muons_veto[0].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(muons_veto[0].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(muons_veto[0].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	    if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    else   FillHist("SS_auxFake_ptcone_0bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	  }
	}
      }
    }
  }
  

  std::vector<snu::KMuon> muons8TeV = GetMuons("MUON_HN_TIGHT_8TeV",false);
  std::vector<snu::KMuon> muons_pogt = GetMuons("MUON_POG_TIGHT",false);
  std::vector<snu::KMuon> muons_pogm = GetMuons("MUON_POG_MEDIUM",false);
  
  CorrectedMETRochester(muons);
  //double  met = eventbase->GetEvent().PFMET();
  //double  met_phi = eventbase->GetEvent().PFMETPhi();  

  //CorrectedMETMuon(1, muons, met, met_phi);

  /// Set up electrons                                                                                                                                        
  std::vector<snu::KElectron> electrons = GetElectrons(elid);
  std::vector<snu::KElectron> electrons_veto = GetElectrons(true, true,"ELECTRON_HN_VETO");

  /*if(SameCharge(electrons)){
    std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
    if(IsExternalConversion(electrons[0]) || IsExternalConversion(electrons[1]) ){
      cout << "Electron : " <<  GetLeptonType(electrons[0], truthColl )  << " " <<  GetLeptonType(electrons[1], truthColl ) << endl;
      cout << "Electron : " << electrons[0].GetType() << " " << electrons[1].GetType() << endl;

      TruthPrintOut();                                                                  
    }                                                                                       
  }
  return;
  */

  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> alljets_10 = GetJetsWFT("JET_NOLEPTONVETO", "FATJET_HN_tau06",10., 2.5);
  std::vector<snu::KJet> alljets_10_eta5 = GetJetsWFT("JET_NOLEPTONVETO", "FATJET_HN_tau06",10., 5.);
  std::vector<snu::KJet> tchanjets = GetJetsWFT("JET_HN_TChannel","FATJET_HN_tau06",20., 5.);
  
  std::vector<snu::KJet>  jets_20 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",20., 2.5);
  std::vector<snu::KJet>  jets_all20 =  GetJets("JET_HN", 20., 2.5);
  std::vector<snu::KJet>  jets_all20_eta5 =  GetJets("JET_HN", 20., 5.);
  std::vector<snu::KJet>  jets_all15 =  GetJets("JET_HN", 15., 2.5);
  std::vector<snu::KJet>  jets_all15_eta5 =  GetJets("JET_HN", 15., 5.);

  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN_tau06");
  std::vector<snu::KFatJet> fatjetcoll_tau21_045 = GetFatJets("FATJET_HN_tau045");
  std::vector<snu::KFatJet> fatjetcoll_notau21 = GetFatJets("FATJET_HN");
  
  
  /// correct L1 JEC and apply JMR

  std::vector<snu::KFatJet> fatjetcoll_updated = GetCorrectedFatJet(fatjetcoll);
  std::vector<snu::KFatJet> fatjetcoll_tau21_045_updated = GetCorrectedFatJet(fatjetcoll_tau21_045);
  std::vector<snu::KFatJet> fatjetcoll_notau21_updated = GetCorrectedFatJet(fatjetcoll_notau21);
  CorrectedMETJMR(fatjetcoll_updated, jets_20);

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

    ///  No ak8 jet splitting       :   ak4 jets , pt > 20 , eta < 2.5  
    if(_mm_channel)RunMM(0,"DiMuon_inclusive",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    

    if(_m_channel) RunMM(0,"DiMuon_inclusive_OR",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon_singleLep ,26.      , 10.);
    if(_mm_channel) RunMM(0,"DiMuon_inclusive_OR",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,-999.      , -999.);
			 


    return;

///  No ak8 jet splitting       :   ak4 jets , pt > 20 , eta < 5.
    if(_mm_channel)RunMM(0,"DiMuon_jets_eta5",      muons,muons_veto,electrons_veto,alljets,   jets_all20_eta5, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    
    ///  No ak8 jet splitting       :   ak4 jets , pt > 15 , eta < 5.
    if(_mm_channel)RunMM(0,"DiMuon_jets_pt15_eta5",      muons,muons_veto,electrons_veto,alljets,   jets_all15_eta5, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    
    ///  No ak8 jet splitting       :   ak4 jets , pt > 15 , eta < 2.5
    if(_mm_channel)RunMM(0,"DiMuon_jets_pt15",      muons,muons_veto,electrons_veto,alljets,   jets_all15, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    

    if(_m_channel) RunMM(0,"DiMuon_inclusive_OR",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon_singleLep ,26.      , 5.);    
    if(_mm_channel)RunMM(0,"DiMuon_inclusive_OR",      muons,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,-999.      , -999.);    

    if(_mm_channel)RunMM(0,"DiMuon_fake",      muons_fake,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    
    
    if(_mm_channel)RunMM(0,"DiMuon_8TeV",      muons8TeV,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    if(_mm_channel)RunMM(0,"DiMuon_PogT",      muons_pogt,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    if(_mm_channel)RunMM(0,"DiMuon_PogM",      muons_pogm,muons_veto,electrons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);    

    if(_mm_channel)RunMM(1,"DiMuon_SIP",      muons_highDXY ,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    
    
    if(fatjetcoll_updated.size() > 0){
      if(fatjetcoll_updated.size() ==1){
	if(fatjetcoll_updated[0].Pt() > 200) RunMM(2,"DiMuon_FAT_200_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
	else RunMM(1,"DiMuon_NoFAT_200_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
	if(fatjetcoll_updated[0].Pt() >250) RunMM(2,"DiMuon_FAT_250_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
	else RunMM(1,"DiMuon_NoFAT_250_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.  , 10.);
	if(fatjetcoll_updated[0].Pt() >300) RunMM(2,"DiMuon_FAT_300_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
	else RunMM(1,"DiMuon_NoFAT_300_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.  , 10.);
      }
    }
    else{
      RunMM(1,"DiMuon_NoFAT_200_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
      RunMM(1,"DiMuon_NoFAT_250_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
      RunMM(1,"DiMuon_NoFAT_300_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.   , 10.);
    }

    if(fatjetcoll_tau21_045_updated.size() >0)RunMM(2,"DiMuon_FATTAU2_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_tau21_045_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    if(fatjetcoll_notau21_updated.size() >0)RunMM(2,"DiMuon_FATTAU3_TMP",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_notau21_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    
    if(fatjetcoll_updated.size() ==0) {
      if(_mm_channel)RunMM(1,"DiMuon_NoFAT",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    }
    else{
      if(_mm_channel)RunMM(2,"DiMuon_FAT",      muons,muons_veto,electrons_veto,alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  mm_weight, triggerlist_DiMuon ,20.      , 10.);
    }
    
  }
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


float HNDiLepton::MMWeight(std::vector<snu::KMuon> muons, TString id, bool passtrig){

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
  double trigger_eff_MC_OR = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 3, 1, 0);
  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  if(passtrig) mc_weight*= trigger_sf;
  
  
  return mc_weight;

}

void HNDiLepton::RunMM(int mode, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float mm_weight ,vector<TString> mm_trig, float pt1, float pt2){
  
  vector<snu::KElectron> el;
  RunLL(mode, "MM",label, muons, muons_veto, el, electrons,alljets, jets, fatjets, tjets, mm_weight,   mm_trig, pt1, pt2);
}
 
void HNDiLepton::RunEE(TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ee_weight ,vector<TString> ee_trig, float pt1, float pt2){

  vector<snu::KMuon> mu;
  RunLL(0,"EE",label, mu, muons, electrons, electrons_veto, alljets, jets, fatjets, tjets,ee_weight,  ee_trig, pt1, pt2);
}


void HNDiLepton::RunLL(int mode,TString channel , TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KElectron> electrons_veto, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ll_weight ,vector<TString> ll_trig, float pt1, float pt2){
  

  bool samecharge=true;
  bool FillAll=true;
  if (label.Contains("OS")) samecharge=false;
  if (!label.Contains("DiMuon_inclusive")) FillAll=false;
  
  /// mode 0 = no fat jet requirements
  /// mode 1 = n(AK8) ==0
  /// mode 2 = n(AK8) > 0
  
  if(mode==1 && fatjets.size() > 0) return;
  if(mode==2 && fatjets.size() == 0) return;


  /// muon collection can change if using 8 TeV or SIP fakes
  TString muid=_m_tightid;
  if(k_running_nonprompt) {
    muid=_m_looseid;
    if(label=="DiMuon_SIP") muid="MUON_HN_Loose_HighdXY_Small";
    if(label=="DiMuon_8TeV") muid="MUON_HN_LOOSE_8TeV";
  }
  
  /// Apply trigger to events
  bool cut2_trig = PassTriggerOR(ll_trig);

  if(!isData&& !ll_trig[0].Contains("HLT_Iso")){
    FillEventCutFlow(4,"NoCut",ll_weight*WeightByTrigger(ll_trig[0],TargetLumi),label );
    FillHist(label+"_StatBin", 1, 1, 0., 2, 2);
  }


  //// Fill set of plots for signal only
  if( mode==0 && IsSignal()){
    vector<int>  ijet_list =           FillTruthPlots(jets, muons, label);
    FillEfficiency(label, jets, fatjets, ll_weight*WeightByTrigger(ll_trig[0],TargetLumi));
  }


  ///// Apply vertex requirement
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :   
  
  if(!isData&& !ll_trig[0].Contains("HLT_Iso")){
    FillEventCutFlow(4,"EventCleaning",ll_weight*WeightByTrigger(ll_trig[0],TargetLumi),label );            
  }
  //// DIMUON 
  /// define event variables                                                                                                                                                  
  snu::KParticle ll; 
  if(muons.size() ==2) ll= muons[0] + muons[1];

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
  if(muons.size() ==2)ST= muons[0].Pt() + muons[1].Pt();
  float HT=0.;
  for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
  if(mode==2){
    for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
  }
  ST+=eventbase->GetEvent().PFMET();
  

  /// DIMUON --- MET
  
  //// MET is corrected already for rochester 
  float met = eventbase->GetEvent().PFMET();
  float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;
  
  

  bool ORtrigger=false;
  if( pt1 < 0 ){
    ORtrigger=true;
    pt1=20;
    pt2=10;
  }
  bool cut1_dilep =  (muons.size()==2 && (muons[1].Pt() > pt2 && muons[0].Pt() > pt1 ));
  if(k_running_nonprompt)cut1_dilep =  (muons.size()==2 && (muons[1].PTCone(0.4,0.07) > pt2 && muons[0].PTCone(0.4,0.07) > pt1 ));
  
  std::vector<snu::KElectron> electrons_tight= GetElectrons("ELECTRON_HN_TIGHTv4");
  
  if(muons.size() == 2 && electrons_tight.size() ==1){
    if(!SameCharge(muons)){
      if(met > 40){
	if(nbjet_m==0&&cut2_trig){
	  if(electrons_tight.at(0).Pt() > 10 && muons[0].Pt() > 20 && muons[1].Pt() > 15){
	    float dphi_1 = fabs(TVector2::Phi_mpi_pi(electrons_tight.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
	    float MT_1 = sqrt(2.* electrons_tight.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));
	    snu::KParticle m2 = muons[0]+muons[1];
	    
	    snu::KParticle m3 = muons[0]+muons[1]+electrons_tight[0];
	    if(fabs(m3.M()-90.1) > 15){
	      if(muons_veto.size() ==2){
		if(electrons_veto.size() ==1){
		  if(fabs(m2.M()-90.)< 15.){
		    FillHist(label+"Truth_WZ_Zmass",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
		    
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

 
  if(k_sample_name.Contains("ZG") || k_sample_name.Contains("DY")){
    std::vector<snu::KMuon>  muons_nocut =GetMuons("MUON_NOCUT",false, 5., 2.5);     

    if(SameCharge(muons)){
      std::vector<snu::KTruth> truthColl= eventbase->GetTruth();

      bool conv=false;
      if(GetLeptonType(muons[0],truthColl )== 4 ||  GetLeptonType(muons[0],truthColl )==  5) {
	int tr_index= muons[0].MCTruthIndex();
	while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
	  tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
	}
	if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
      }
      if(GetLeptonType(muons[1],truthColl )== 4 ||  GetLeptonType(muons[1],truthColl )==  5) {
        int tr_index= muons[1].MCTruthIndex();
        while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
          tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
	}
        if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
      }
      if(conv)              FillHist(label+"SS_ZG_conv_mass",GetDiLepMass(muons), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);   
      else FillHist(label+"SS_ZG_noconv_mass",GetDiLepMass(muons), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
    }
    if(muons_nocut.size() == 4){

      //TruthPrintOut();

      if(nbjet_m==0&&cut2_trig){
	std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
	vector<int> Zindex = GetVirtualMassIndex(1,13);
	vector<int> Gindex = GetVirtualMassIndex(2,13);
	cout << "ZG 4 muon check " << Zindex.size() << " " << Gindex.size() <<endl;
	if(Zindex.size() ==2 && Gindex.size() ==2){
	  cout << "list of index: " << Zindex[0] << " " << Zindex[1] << " non Z: " << Gindex[0] << " " << Gindex[1] << endl;

	  int ph_index=(0); 
	  for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
	    if(fabs(eventbase->GetTruth().at(ig).PdgId()) != 13){
	      int index_m=eventbase->GetTruth().at(ig).IndexMother() ;
	      if(index_m == eventbase->GetTruth().at(Zindex[0]).IndexMother())ph_index= ig;
	    }
	  }

	  if(Gindex[0] < eventbase->GetTruth().size() && Gindex[0] > 0 && Gindex[1] < eventbase->GetTruth().size() && Gindex[1] > 0 ){
	    cout << "Type " << muons_nocut[0].GetType() << " : " << muons_nocut[1].GetType() <<  " : " <<  muons_nocut[2].GetType() <<  " : " <<  muons_nocut[3].GetType() << endl;
	    cout << "Type2 " <<  GetLeptonType(muons_nocut[0],truthColl) << " : " <<  GetLeptonType(muons_nocut[1],truthColl)  << " : " <<  GetLeptonType(muons_nocut[2],truthColl) << " : " <<  GetLeptonType(muons_nocut[3],truthColl) << endl;
	    cout << "Mass of Z = " << (eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1])).M() << endl;
	    cout << "Mass of llph = " << (eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1]) + eventbase->GetTruth().at(ph_index)).M() << endl;
	    cout << "Mass of G = " << (eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M() << endl;
	    cout << "Mass of Zll = " <<  (eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1])+ eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M() << endl;
	    
	    cout << "G mothers = " << eventbase->GetTruth().at(eventbase->GetTruth().at(Gindex[0]).IndexMother()).PdgId()   << " : " << eventbase->GetTruth().at(eventbase->GetTruth().at(Gindex[1]).IndexMother()).PdgId() << endl;
	    cout << "G Gmother = " << eventbase->GetTruth().at(eventbase->GetTruth().at(eventbase->GetTruth().at(Gindex[0]).IndexMother()).IndexMother()).PdgId()   << " : " << eventbase->GetTruth().at(eventbase->GetTruth().at(eventbase->GetTruth().at(Gindex[1]).IndexMother()).IndexMother()).PdgId() << endl;
							      
	    
	    bool conv=false;
	    if(GetLeptonType(muons_nocut[0],truthColl )== 4 ||  GetLeptonType(muons_nocut[0],truthColl )==  5) {
	      int tr_index= muons_nocut[0].MCTruthIndex();
	      while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
		tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
	      }
	      if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
	    }
	    if(GetLeptonType(muons_nocut[1],truthColl )== 4 ||  GetLeptonType(muons_nocut[1],truthColl )==  5) {
	      int tr_index= muons_nocut[1].MCTruthIndex();
	      while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
		tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
	      }
	      if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
	    }
	    if(GetLeptonType(muons_nocut[2],truthColl )== 4 ||  GetLeptonType(muons_nocut[2],truthColl )==  5) {
              int tr_index= muons_nocut[2].MCTruthIndex();
              while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
                tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
              }
              if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
            }
	    if(GetLeptonType(muons_nocut[3],truthColl )== 4 ||  GetLeptonType(muons_nocut[3],truthColl )==  5) {
              int tr_index= muons_nocut[3].MCTruthIndex();
              while(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 13 || fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 22){
                tr_index = eventbase->GetTruth().at(tr_index).IndexMother();
              }
              if(fabs(eventbase->GetTruth().at(tr_index).PdgId()) == 23) conv=true;
            }
	  
	    if(conv){
	      FillHist(label+"Truth_ZG_conv_Gmass",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	      FillHist(label+"Truth_ZG_conv_G_pt",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).Pt(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	    }
	    else {
	      FillHist(label+"Truth_ZG_nonconv_Gmass",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	      FillHist(label+"Truth_ZG_nonconv_G_pt",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).Pt(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	    }
	    
	    
	    FillHist(label+"Truth_ZG_Zmass",(eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150); 
	    FillHist(label+"Truth_ZG_Gmass",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150); 
	    FillHist(label+"Truth_Z_lep1_pt",eventbase->GetTruth().at(Zindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50); 
	    FillHist(label+"Truth_Z_lep2_pt",eventbase->GetTruth().at(Zindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50); 
	    FillHist(label+"Truth_G_lep1_pt",eventbase->GetTruth().at(Gindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	    FillHist(label+"Truth_G_lep2_pt",eventbase->GetTruth().at(Gindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	    if(SameCharge(muons)){
	      FillHist(label+"Truth_SS_ZG_Zmass",(eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	      FillHist(label+"Truth_SS_ZG_Gmass",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi) , 0., 150., 150);
	      FillHist(label+"Truth_SS_Z_lep1_pt",eventbase->GetTruth().at(Zindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	      FillHist(label+"Truth_SS_Z_lep2_pt",eventbase->GetTruth().at(Zindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	      FillHist(label+"Truth_SS_G_lep1_pt",eventbase->GetTruth().at(Gindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	      FillHist(label+"Truth_SS_G_lep2_pt",eventbase->GetTruth().at(Gindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
	    }
	    
	    if(muons.size() == 3){
	      if(met < 60){
		snu::KParticle m3 = muons.at(0) + muons.at(1)+muons.at(2);
		
		if(fabs(m3.M()-90.1) < 15){
		  FillHist(label+"Truth_lll_ZG_Zmass",(eventbase->GetTruth().at(Zindex[0]) + eventbase->GetTruth().at(Zindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
		  
		  
		  FillHist(label+"Truth_lll_ZG_Gmass",(eventbase->GetTruth().at(Gindex[0]) + eventbase->GetTruth().at(Gindex[1])).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi) , 0., 150., 150);
		  
		  FillHist(label+"Truth_lll_Z_lep1_pt",eventbase->GetTruth().at(Zindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
		  FillHist(label+"Truth_lll_Z_lep2_pt",eventbase->GetTruth().at(Zindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
		  FillHist(label+"Truth_lll_G_lep1_pt",eventbase->GetTruth().at(Gindex[0]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
		  FillHist(label+"Truth_lll_G_lep2_pt",eventbase->GetTruth().at(Gindex[1]).Pt() ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 50);
		}
	      }
	    }
	  }
	}
	else {
	  cout << "No Z " << endl;
	  TruthPrintOut();

	}
      }
    }
  }
  

  if(label == ("DiMuon_inclusive")) {
    std::vector<snu::KMuon> muons_loose= GetMuons(_m_looseid,true);
    std::vector<snu::KMuon>  muons_nocut =GetMuons("MUON_NOCUT",true, 10., 2.5);
    std::vector<snu::KMuon>  muons_pog =GetMuons("MUON_POG_TIGHT",true, 10., 2.5);

    //if(muons_loose.size() == 4)  TruthPrintOut();

    if(muons_nocut.size() == 2 &&FillAll)FillCLHist(sighist_mm, label+"SSLL_NoCut", eventbase->GetEvent(),muons_nocut , electrons,jets, alljets, fatjets,  ll_weight);
    if(muons_nocut.size() == 3 &&FillAll)FillCLHist(sighist_mmm, label+"SSLLL_NoCut", eventbase->GetEvent(),muons_nocut , electrons,jets, alljets, fatjets,  ll_weight);
    std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
 
    for(unsigned int i=0 ;i < muons_pog.size() ; i++){
      FillHist("MC_pog_FR_type_mu_loose_"+label,  muons_pog.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
      FillHist("MC_pog_FR_type2_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
      FillHist("MC_pog_FR_2Dtype_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl) ,  muons_pog.at(i).GetType(),   ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),-10., 10.,20 , 0., 50.,50);
      if(muons_pog[i].MCIsFromConversion()) {
	FillHist("MC_pog_conv_FR_type_mu_loose_"+label,  muons_pog.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("MC_pog_conv_FR_type2_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
      }
      else{
	FillHist("MC_pog_nonconv_FR_type_mu_loose_"+label,  muons_pog.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("MC_pog_nonconv_FR_type2_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
      }
      if(SameCharge(muons_pog)){
	FillHist("MC_SSpog_FR_type_mu_loose_"+label,  muons_pog.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("MC_SSpog_FR_type2_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
	FillHist("MC_SSpog_FR_2Dtype_mu_loose_"+label,  GetLeptonType(muons_pog[i],truthColl) ,  muons_pog.at(i).GetType(),ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20 ,0., 50.,50);
      }
    }
    
    for(unsigned int i=0 ;i < muons_loose.size() ; i++){
      
      FillHist("MC_FR_type_mu_loose_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
      FillHist("MC_FR_type2_mu_loose_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
      FillHist("MC_dxy_mutype_"+label,fabs(muons_loose.at(i).dxy())  , muons_loose.at(i).GetType()  ,ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 0.5, 200., 0., 50., 50);
      FillHist("MC_dxy_mutype2_"+label,fabs(muons_loose.at(i).dxy())  , GetLeptonType(muons_loose[i],truthColl)  , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 0.5, 200., 0., 50., 50);
      
      if(fabs(muons_loose.at(i).dXYSig()) < 3.) {
	FillHist("MC_lowdxy_iso_mutype_"+label, muons_loose.at(i).RelIso04(), muons_loose.at(i).GetType()  ,  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 0.5, 100., 0., 50., 50);
	FillHist("MC_lowdxy_iso_mutype2_"+label, muons_loose.at(i).RelIso04(), GetLeptonType(muons_loose[i],truthColl) ,  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 0.5, 100., -10., 10., 20);
      }
      else{
	FillHist("MC_highdxy_iso_mutype_"+label,muons_loose.at(i).RelIso04(), muons_loose.at(i).GetType()  ,  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 0.5, 100., 0., 50., 50);
	FillHist("MC_highdxy_iso_mutype2_"+label,muons_loose.at(i).RelIso04(), GetLeptonType(muons_loose[i],truthColl) ,  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 0.5, 100., -10., 10., 20);
      }
      if(jets.size()>1){
	FillHist("MC_Jet_FR_type_mu_loose_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("MC_Jet_FR_type2_mu_loose_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
      }
      if(PassID(muons_loose[i], _m_tightid)) {
	FillHist("MC_FR_type_mu_tight_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("MC_FR_type2_mu_tight_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20); 
	if(jets.size()>1){
	  FillHist("MC_Jet_FR_type_mu_tight_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	  FillHist("MC_Jet_FR_type2_mu_tight_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
	  
	} 
      }
    }
    if(SameCharge(muons_loose)){
      
      for(unsigned int i=0 ;i < muons_loose.size() ; i++){
        FillHist("MC_SS_FR_2Dtype_mu_loose_"+label,  GetLeptonType(muons_loose[i],truthColl) ,  muons_loose.at(i).GetType(),ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20 ,0., 50.,50);

	FillHist("SSMC_FR_type_mu_loose_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	FillHist("SSMC_FR_type2_mu_loose_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
	if(jets.size()>1){
	  FillHist("SSMC_Jet_FR_type_mu_loose_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	  FillHist("SSMC_Jet_FR_type2_mu_loose_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),-10., 10.,20);
	  
	  
	} 
	if(PassID(muons_loose[i], _m_tightid)) {
	  FillHist("MC_SS_FR_2Dtype_mu_tight_"+label,  GetLeptonType(muons_loose[i],truthColl) ,  muons_loose.at(i).GetType(),ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20 ,0., 50.,50);
	  FillHist("SSMC_FR_type_mu_tight_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50,50.);
	  FillHist("SSMC_FR_type2_mu_tight_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
	  if(jets.size()>1){
	    FillHist("SSMC_Jet_FR_type_mu_tight_"+label,  muons_loose.at(i).GetType(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 50.,50);
	    FillHist("SSMC_Jet_FR_type2_mu_tight_"+label,  GetLeptonType(muons_loose[i],truthColl), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -10., 10.,20);
	    
	  }
	}
      } 
      
      
      float mu_pt_corr1 =  muons_loose.at(0).Pt()*(1+max(0.,(muons_loose.at(0).RelIso04()-0.07))) ; /// will need changing for systematics                                             
      float mu_pt_corr2 =  muons_loose.at(1).Pt()*(1+max(0.,(muons_loose.at(1).RelIso04()-0.07))) ; /// will need changing for systematics                                             
      FillHist("Fake_isopt_mu1_"+label,  mu_pt_corr1,  muons_loose.at(0).RelIso04()*mu_pt_corr1, 1., 0., 500., 100., 0., 100., 50);
      FillHist("Fake_isopt_mu2_"+label,  mu_pt_corr2,  muons_loose.at(1).RelIso04()*mu_pt_corr2, 1., 0., 500., 100., 0., 100., 50);

      if( (PassID(muons_loose[0], _m_tightid) && ! PassID(muons_loose[1],_m_tightid)) ||  (!PassID(muons_loose[0],_m_tightid) && PassID(muons_loose[1],_m_tightid))){	
	if(FillAll)FillCLHist(sighist_mm, label+"SSLL_TL", eventbase->GetEvent(), muons_loose, electrons,jets, alljets, fatjets,  ll_weight);
      }
    }
    if(!isData){
      for(unsigned int i=0 ;i < muons_loose.size() ; i++){
	float mu_pt_corr1 =  muons_loose.at(i).Pt()*(1+max(0.,(muons_loose.at(i).RelIso04()-0.07))) ; /// will need changing for systematics                                          
	
	if(!TruthMatched(muons_loose[i])) {
	  
	  FillHist("Fake_mc_isopt_mu_"+label,  mu_pt_corr1,  muons_loose.at(i).RelIso04(), 1., 0., 500., 100., 0., 1., 50);
	  FillHist("Fake_mc_isodxy_mu_"+label,fabs(muons_loose.at(i).dxy())  ,  muons_loose.at(i).RelIso04(), 1., 0., 0.5, 500., 0., 1., 50);
	  FillHist("Fake_mc_iso_type_mu_"+label,  muons_loose.at(i).GetType(),  muons_loose.at(i).RelIso04(), 1., 0., 50., 50., 0., 1., 50);
	}
	else 	  FillHist("NonFake_mc_iso_type_mu_"+label,  muons_loose.at(i).GetType(),  muons_loose.at(i).RelIso04(), 1., 0., 50., 50., 0., 1., 50);
      }
    }
  }

  if(cut1_dilep){

    TString elid=_e_tightid;
    if(k_running_nonprompt) elid=_e_looseid;
   
    /// weight CF events 

    ll_weight *= MMWeight(muons,muid,cut2_trig);
    if(!isData&&!ll_trig[0].Contains("HLT_Iso")){
      FillEventCutFlow(4,"DiLep",ll_weight*WeightByTrigger(ll_trig[0], TargetLumi) ,label);
    }
    if(ORtrigger){
      std::vector<TString> triggerlist_DiMuon;
      triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
      triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
      

      std::vector<TString> triggerlist_DiMuon_singleLep;
      triggerlist_DiMuon_singleLep.push_back("HLT_IsoMu24_v");
      triggerlist_DiMuon_singleLep.push_back("HLT_IsoTkMu24_v");
      
      /// Data DoubleMuon require double triggers
      if(isData){
	if(PassTriggerOR(triggerlist_DiMuon)) {
	  if(muons[0].Pt() < 20 || muons[1].Pt() < 10) return;
	}
	else return;
      }
      else{
	/// MC do OR + pt cuts
	if(PassTriggerOR(triggerlist_DiMuon)) {
	  if(muons[0].Pt() < 20 || muons[1].Pt() < 10) return;
	}
	else if(PassTriggerOR(triggerlist_DiMuon_singleLep)){
	  if(muons[0].Pt() < 26 || muons[1].Pt() < 10) return;
	}
	else return;
      }
    }
    else {

      ///  No OR

      /// If SingleMuon check !pass double and then pass single
      if(isData && ll_trig[0].Contains("HLT_Iso")){
	std::vector<TString> triggerlist_DiMuon;
	triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
	triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
	if(PassTriggerOR(triggerlist_DiMuon)) return;
      }

      FillHist(label+"_pass_HLTnoDZ_failDZ",0. , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,4,4, "dilep trigger result");
      if(cut2_trig)       FillHist(label+"_pass_HLTnoDZ_failDZ",1. , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,4,4, "dilep trigger result");
      else{
	std::vector<TString> triggerlist_DiMuonnoDZ;
	triggerlist_DiMuonnoDZ.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");
	triggerlist_DiMuonnoDZ.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");

	if(PassTriggerOR(triggerlist_DiMuonnoDZ)) {
	  FillHist(label+"_pass_HLTnoDZ_failDZ",2. , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,4,4, "dilep trigger result");
	  cout << "Pass noDZ trigger (fails DZ) " <<  endl;
	  for(unsigned int i=0; i < muons_veto.size(); i++){
	    cout << "Muon " << i << " pt = " << muons_veto[i].Pt() << " eta = " << muons_veto[i].Eta() << " dz=" << muons_veto[i].dz() << endl;
	  }
	  if(muons_veto.size()== 2)           FillHist(label+"_pass_HLTnoDZ_failDZ",3. , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,4,4, "dilep trigger result");


	}
      }

      if(!cut2_trig) return;

    }
  

    //// correct weight to include trigger lumi
    if(!isData)  ll_weight*= WeightByTrigger(ll_trig[0], TargetLumi) ;

    if(ll_trig[0].Contains("HLT_Iso")){
      FillEventCutFlow(4,"TriggerIso24",ll_weight,label);
    }
    else{
      FillEventCutFlow(4,"TriggerMu17",ll_weight,label);
    }
    FillEventCutFlow(4,"Trigger",ll_weight,label);
	
    counter("Trigger",ll_weight);
    

    bool cut3_lepveto = (electrons_veto.size()>0);
    
    if(cut3_lepveto) return;

    counter("LepVeto",ll_weight);
	
    FillEventCutFlow(4,"LepVeto",ll_weight,label);
	

    vector<int> ijets;  
    
    histtype llhist = sighist_mm;

    bool  cut4_ss = (SameCharge(muons));

    if((samecharge && cut4_ss) || (!samecharge&& !cut4_ss)){
      
      
      FillEventCutFlow(4,"SSLLLoose",ll_weight,label);
      
      bool cut5_mll (0);
      if(llmass  > _mm_mll_presel_cut) cut5_mll=true;
	
      
      if(cut5_mll){
	
	FillEventCutFlow(4,"MLL",ll_weight,label);

	//FillEventComparisonFile("test");
	float ll_weight_sf=ll_weight;
	float ll_weight_df=ll_weight;
	if(k_running_nonprompt){
	  
	  ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",0);
	  ll_weight_sf=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",1);
	  ll_weight_df=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_central",2);
	  if(label=="DiMuon_SIP")
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_sip_central",0);
	  
	  
	  if(label=="DiMuon_8TeV")
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, muons, _m_tightid, "ptcone", "fr_muon_8TeV_central",0);
	  
	  if(PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TT_Preselection", ll_weight);
	  if(PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TT_Preselection_now", 1.);
	  if(PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TL_Preselection", ll_weight);
	  if(PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_TL_Preselection_now", 1.);
	  if(!PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LT_Preselection", ll_weight);
	  if(!PassID(muons[0], "MUON_HN_TIGHT") && PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LT_Preselection_now", 1.);
	  if(!PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LL_Preselection", ll_weight);
	  if(!PassID(muons[0], "MUON_HN_TIGHT") && !PassID(muons[1] , "MUON_HN_TIGHT"))counter("SSLL_LL_Preselection_now", 1.);

	}	
	counter("SSLL_Preselection", ll_weight);


	if(FillAll)FillCLHist(llhist, label+"SSLL_nolepveto", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);

	vector<int> ti_jets;
	
	if(IsSignal()){
	  float lljj_lm = GetMasses("lljj",muons, jets,fatjets,ti_jets, true);
	  float l1jj_lm = GetMasses("l1jj",muons, jets,fatjets,ti_jets, true);
	  float l2jj_lm = GetMasses("l2jj",muons, jets,fatjets,ti_jets, true);
	  float lljj_hm = GetMasses("lljj",muons, jets,fatjets,ti_jets, false);
          float l1jj_hm = GetMasses("l1jj",muons, jets,fatjets,ti_jets, false);
          float l2jj_hm = GetMasses("l2jj",muons, jets,fatjets,ti_jets, false);
	  
	  float llfj = GetMasses("llfj",muons, jets,fatjets,ti_jets, false);
          float l1fj = GetMasses("l1fj",muons, jets,fatjets,ti_jets, false);
          float l2fj = GetMasses("l2fj",muons, jets,fatjets,ti_jets, false);
	  float fj = GetMasses("fj",muons, jets,fatjets,ti_jets, false);

	  float jj_lm = GetMasses("jj",muons, jets,fatjets,ti_jets, true);
	  float jj_hm = GetMasses("jj",muons, jets,fatjets,ti_jets, false);

	  float llj = GetMasses("llj",muons, jets,fatjets,ti_jets, true);
	  float l1j = GetMasses("l1j",muons, jets,fatjets,ti_jets, true);
	  float l2j = GetMasses("l2j",muons, jets,fatjets,ti_jets, true);
	  
	  if(jets.size() ==1){
	    FillHist(label+"llj",llj , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 500, "m_{llj} (GeV)");
	    FillHist(label+"l1j",l1j , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 500, "m_{l1j} (GeV)");
	    FillHist(label+"l2j",l2j , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 500, "m_{l2j} (GeV)");

	  }
	  
          if(jets.size() > 1 ){
	    FillHist(label+"jj_lm",jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 500., 250, "m_{jj} Low Mass (GeV)");
	    FillHist(label+"jj_hm",jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 500., 250, "m_{jj} High Mass (GeV)");
	    
	    FillHist(label+"lljj_LowMass",lljj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{lljj} Low Mass (GeV)");
	    FillHist(label+"l1jj_LowMass",l1jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l1jj} Low Mass (GeV)");
	    FillHist(label+"l2jj_LowMass",l2jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l2jj} Low Mass (GeV)");
	    
	    FillHist(label+"lljj_HighMass",lljj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{lljj} High Mass (GeV)");
	    FillHist(label+"l1jj_HighMass",l1jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{l1jj} High Mass (GeV)");
	    FillHist(label+"l2jj_HighMass",l2jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{l2jj} High Mass (GeV)");
	  }
	  if(fatjets.size()>0){
	    FillHist(label+"llfj",llfj , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{llj} ak8 (GeV)");
	    FillHist(label+"l1fj",l1fj , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l1j} ak8 (GeV)");
	    FillHist(label+"l2fj",l2fj , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l2j} ak8 (GeV)");
	    FillHist(label+"fj",fj , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{j} ak8 (GeV)");
	  }
	  
	  if(jets.size() > 1){
	    FillHist(label+"l1jj_l2jj_LowMass",l1jj_lm , l2jj_lm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300,  0., 1500., 300, "m_{l1jj}  (GeV)", "m_{l2jj}  (GeV)");
	    FillHist(label+"l1jj_lljj_LowMass",l1jj_lm , lljj_lm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, 0., 1500., 300, "m_{lljj} (GeV)","m_{lljj}  (GeV)");
	    FillHist(label+"l2jj_lljj_LowMass",l2jj_lm , lljj_lm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, 0., 1500., 300, "m_{l2jj} (GeV)","m_{lljj}  (GeV)");
	    
	    
	    FillHist(label+"l1jj_l2jj_HighMass",l1jj_hm , l2jj_hm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 2000., 500,  0., 2000., 500, "m_{l1jj} (GeV)","m_{l2jj} (GeV)");
	    FillHist(label+"l1jj_lljj_HighMass",l1jj_hm , lljj_hm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 2000., 500, 0., 2000., 500, "m_{l1jj} (GeV)","m_{lljj} (GeV)");
	    FillHist(label+"l2jj_lljj_HighMass",l2jj_hm , lljj_hm, ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 2000., 500, 0., 2000., 500, "m_{l2jj} (GeV)","m_{lljj} (GeV)");
	  }
	  
	  
	  vector<int>  ijet_list =          GetTruthJets(false);
	  
	  int matched_jets=MatchedLeptonJets(jets ,fatjets, muons, label, ijet_list);

	  if(jets.size() ==1){
	    if(matched_jets> 0 ){
	      FillHist(label+"ljj_matched_lm", (muons[0]+muons[1]+jets[0]).M(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 500., 250, "m_{llj} gen-matched (GeV)");
	    }
	  }

	  
	  if(matched_jets==1 || matched_jets==3){
	    FillHist(label+"jj_matched_lm",jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 500., 250, "m_{jj} gen-matched (GeV)");
	    FillHist(label+"lljj_matched_LowMass",lljj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{lljj} LM gen-matched  (GeV)");
	    FillHist(label+"l1jj_matched_LowMass",l1jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l1jj} LM gen-matched (GeV)");
	    FillHist(label+"l2jj_matched_LowMass",l2jj_lm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 1500., 300, "m_{l2jj} LM gen-matched (GeV)");
	  }
	  
	  if(matched_jets==2 || matched_jets==3){
	    FillHist(label+"jj_matched_hm",jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 500., 250, "m_{llj} (GeV)");
	    FillHist(label+"lljj_matched_HighMass",lljj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{lljj} HM gen-matched (GeV)");
	    FillHist(label+"l1jj_matched_HighMass",l1jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{l1jj} HM gen-matched (GeV)");
	    FillHist(label+"l2jj_matched_HighMass",l2jj_hm , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi),  0., 2000., 500, "m_{l2jj} HM gen-matched (GeV)");
	    
	  }
	}
	
	
	bool cut6_lepveto = (muons_veto.size()>2);
	
	//std::vector<snu::KTruth> truthColl2= eventbase->GetTruth();
	//cout << "Type " <<  muons[0].GetType() << " " <<  muons[1].GetType() <<  " mass = " << GetVirtualMass(13,false,false) <<  " " <<   GetLeptonType(muons_veto[0],truthColl2) << " " << GetLeptonType(muons_veto[1],truthColl2)  <<endl;
																									    
	FillHist(label+"Truth_WZ_SS_Zmass",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150, "m_{llj} (GeV)");

	for(unsigned int ig=0; ig < eventbase->GetTruth().size(); ig++){
	  
	  if(eventbase->GetTruth().at(ig).IndexMother() <= 0)continue;
	  if(eventbase->GetTruth().at(ig).IndexMother() >= int(eventbase->GetTruth().size()))continue;
	  if(fabs(eventbase->GetTruth().at(ig).PdgId()) == 13){
	    if(eventbase->GetTruth().at(ig).GenStatus() ==1){
	      if(muons[0].DeltaR(eventbase->GetTruth().at(ig)) > 0.4){
		if(muons[1].DeltaR(eventbase->GetTruth().at(ig)) > 0.4){
		  FillHist(label+"Truth_WZ_SS_Zmass_missing_lep",eventbase->GetTruth().at(ig).Pt(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 100, "p_{T} missing-lepton (GeV)");
		  if(!cut6_lepveto)                   FillHist(label+"Truth_WZ_SS_Zmass_missing_lep_afterveto",eventbase->GetTruth().at(ig).Pt(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 100., 100, "p_{T} missing-lepton (GeV)");
		  
		}
	      }
	    }
	  }
	}


	if(cut6_lepveto) return;

	if(!isData){
	  FillHist(label+"Truth_WZ_SS_Zmass_lepveto",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 150., 150);
	  if(GetVirtualMass(13,false,false) < 4.&&FillAll) FillCLHist(llhist, label+"SSLL_LowMassMll", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
							     
	  
	}


	if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	if(k_running_nonprompt){
	  if(FillAll){
	    if(muons[0].Pt() > pt1 &&  muons[1].Pt() > pt2) FillCLHist(llhist, label+"SSLL_Preselection_pt", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	  }
	  if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection_sf", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_sf);
	  if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection_df", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_df);
	}

	if(muons[1].Pt() > 15. && jets.size() > 1)        FillEventCutFlow(4, "Presel_8TeV", ll_weight,label);
	
	FillEventCutFlow(4, "Presel", ll_weight,label);

	if(fatjets.size() > 0)  FillEventCutFlow(4,"SSLL_FatJet",ll_weight,label);

	if(jets.size()==1 ){
	  if( (GetDiLepMass(muons) > 110)){
	    if(FillAll)FillCLHist(llhist, label+"SSLL_1JetCR", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	  }
	  if( (GetDiLepMass(muons) < 100)){
	    vector<int> ti_jets;
	    float l1j = GetMasses("l1j",muons, jets,fatjets,ti_jets, false);
	    float l2j = GetMasses("l2j",muons, jets,fatjets,ti_jets, false);
	    float llj = GetMasses("llj",muons, jets,fatjets,ti_jets, false);
	    if(l2j < 80 && l1j < 100 && llj < 150 &&GetDiLepMass(muons) > 15 && NBJet(alljets) ==0 && eventbase->GetEvent().PFMET() < 40){
	      if(FillAll)FillCLHist(llhist, label+"SSLL_1JetSR", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	      if( eventbase->GetEvent().PFMET() < 40){
		FillEventCutFlow(4,"SSLL_1Jet",ll_weight,label);
		if(NBJet(alljets) ==0)                 FillEventCutFlow(4,"SSLL_1Jet_noB",ll_weight,label);
	      } 
	    }
	  }
	}
	/// Fill signal region bins
	
	if(jets.size() > 1) {
	  FillEventCutFlow(4, "DiJet", ll_weight,label);
	}
	
	FillLowMassBins(FillAll, mode, label, muons,muons_veto, electrons_veto, alljets,jets, fatjets,nbjet_m, ll_weight);
	FillHighMassBins(FillAll,mode, label, muons,muons_veto, electrons_veto, alljets, jets, fatjets,nbjet_m, met2_st,ll_weight);
	
	if(label == "DiMuon_inclusive"){
	  CheckJetIDs(label+"_25", ll_weight,25.,ll_trig[0]);
	  CheckJetIDs(label+"_20", ll_weight,20.,ll_trig[0]);
	  CheckJetIDs(label+"_15", ll_weight,15.,ll_trig[0]);
	  CheckJetIDs(label+"_10", ll_weight,10.,ll_trig[0]);
	}	

	if(mode==0 && jets.size() > 1 ){
	  FillCLHist(llhist, label+"SSLL_DiJet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  if(nbjet_m ==0 && FillAll)FillCLHist(llhist, label+"SSLL_DiJet_noB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  else if(FillAll)FillCLHist(llhist, label+"SSLL_DiJet_FailnoB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  FillEventCutFlow(4,"SSLL_DiJet",ll_weight,label);
	  
	  if(nbjet_m ==0 ){
	    FillEventCutFlow(4,"SSLL_DiJet_noB",ll_weight,label);
	    if(eventbase->GetEvent().PFMET() < 80.) {
	      FillEventCutFlow(4,"SSLL_DiJet_passMET",ll_weight,label);
	    }
	  }
	}

	if(mode==1 && jets.size() > 1  &&  fatjets.size() == 0 ){
          if(FillAll)FillCLHist(llhist, label+"SSLL_DiJet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          if(nbjet_m ==0 && FillAll)FillCLHist(llhist, label+"SSLL_DiJet_noB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          else if(FillAll)FillCLHist(llhist, label+"SSLL_DiJet_FailnoB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          if(nbjet_m ==0 ){
            FillEventCutFlow(4,"SSLL_DiJet_noB",ll_weight,label);
            if(eventbase->GetEvent().PFMET() < 80.) {
              FillEventCutFlow(4,"SSLL_DiJet_passMET",ll_weight,label);
            }
          }
	}

	if(mode==2 && fatjets.size() > 0) {
	  if(FillAll)FillCLHist(llhist, label+"SSLL_FatJet", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  if(nbjet_m ==0 && FillAll) FillCLHist(llhist, label+"SSLL_FatJet_noB", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  else if(FillAll)FillCLHist(llhist, label+"SSLL_FatJet_B", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  if(nbjet_m ==0 ){
            FillEventCutFlow(4,"SSLL_FatJet_noB",ll_weight,label);
            if(eventbase->GetEvent().PFMET() < 80.) {
              FillEventCutFlow(4,"SSLL_FatJet_passMET",ll_weight,label);
            }
          }
	}

	

    	FillLowMass(FillAll, mode, label, muons,muons_veto, electrons_veto, alljets, jets, fatjets,nbjet_m, ll_weight, ll_trig[0]);
    	FillHighMass(FillAll, mode, label, muons,muons_veto, electrons_veto, alljets,jets, fatjets,nbjet_m, met2_st,ll_weight,ll_trig[0]);
      } //	 mll cut
	
    }// SS requirement
  }// dilepton
  
  return;
}


bool HNDiLepton::PassLowMassBin2(float pt1max, float pt2max, float mlljmax, float ml1jmax, float ml2jmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet){
	
  bool debug=false;

  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() != 1){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  
  snu::KParticle mm = muons.at(0) + muons.at(1);
  if(mm.M()  < mllmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > mllmax) {if(debug)cout << "Fail mee  " << endl; return false;}

  float met = eventbase->GetEvent().PFMET();
  if(met >  metmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  snu::KParticle llj = muons.at(0) + muons.at(1) + jets[0];
  snu::KParticle l1j = muons.at(0)  + jets[0];
  snu::KParticle l2j =  muons.at(1) + jets[0];
  if(llj.M() > 150) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > 60) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(met >  80) {if(debug)cout << "Fail mee  " << endl; return false;}

  if(llj.M() > mlljmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(l1j.M() > ml1jmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(l2j.M() > ml2jmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  
  return true;
}




bool HNDiLepton::PassHighMassBin1Window(float window, float mass, float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){

  bool both_mass=false;
  if(window < 0.){
    window = fabs(window);
    both_mass=true;
  }
  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.at(0).Pt() < pt1min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  vector<int> ijets;
  if(GetMasses("jj",muons, jets,fjets,ijets, false) > 150.)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("lljj",muons, jets,fjets,ijets, false) < mlljjmin)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) < ml2jjmin)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) > ml2jjmax)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("jj",muons, jets,fjets,ijets, false) < mjjmin)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("jj",muons, jets,fjets,ijets, false) > mjjmax)  {if(debug)cout << "Fail  " << endl; return false;}

  float window_low=mass*(1-window);
  float window_high=mass*(1+window);

  bool inwindow1=false;
  bool inwindow2=false;
  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) >  window_low){
    if(GetMasses("l2jj",muons, jets,fjets,ijets, false) <  window_high){
      inwindow2=true;
    }
  }
  if(GetMasses("l1jj",muons, jets,fjets,ijets, false) >  window_low){
    if(GetMasses("l1jj",muons, jets,fjets,ijets, false) <  window_high){
      inwindow1=true;
    }
  }
  if(both_mass){
    if(!inwindow2&& !inwindow1)  {if(debug)cout << "Fail  " << endl; return false;}
  }
  else{
    if(!inwindow2)  {if(debug)cout << "Fail  " << endl; return false;}
  }
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}



bool HNDiLepton::PassHighMassBin1(float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st, bool debug){


  if(nbjet>0 ) {if(debug)cout << "Fail bjet size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail mu size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail ak4 size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail ak8 size" << endl; return false ;}
  if(muons.at(0).Pt() < pt1min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  vector<int> ijets;
  if(GetMasses("jj",muons, jets,fjets,ijets, false) > 150.)  {if(debug)cout << "Fail jj  " << endl; return false;}
  if(GetMasses("lljj",muons, jets,fjets,ijets, false) < mlljjmin)  {if(debug)cout << "Fail lljj  " << endl; return false;}
  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) < ml2jjmin)  {if(debug)cout << "Fail  l2jj" << endl; return false;}
  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) > ml2jjmax)  {if(debug)cout << "Fail l2jjmax " << endl; return false;}
  if(GetMasses("jj",muons, jets,fjets,ijets, false) < mjjmin)  {if(debug)cout << "Fail jjmin " << endl; return false;}
  if(GetMasses("jj",muons, jets,fjets,ijets, false) > mjjmax)  {if(debug)cout << "Fail  jjmax" << endl; return false;}

  if(met2_st > met2st)   {if(debug)cout << "Fail  MET" << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}
 


bool HNDiLepton::PassHighMassBin2Window(float mass,float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
  
  
  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() == 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  vector<int> ijets;
  if(GetMasses("fj",muons, jets,fjets,ijets, false) > 150)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("llfj",muons, jets,fjets,ijets, false) < mllfjmin)  {if(debug)cout << "Fail  " << endl; return false;}

  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}

  float window_low=mass*(1-0.2);
  float window_high=mass*(1+0.2);

  bool inwindow1=false;
  bool inwindow2=false;

  if(GetMasses("l2jj",muons, jets,fjets,ijets, false) >  window_low){
    if(GetMasses("l2jj",muons, jets,fjets,ijets, false) <  window_high){
      inwindow2=true;
    }
  }
  if(GetMasses("l1jj",muons, jets,fjets,ijets, false) >  window_low){
    if(GetMasses("l1jj",muons, jets,fjets,ijets, false) <  window_high){
      inwindow1=true;
    }
  }
  if(!inwindow2&& !inwindow1)  {if(debug)cout << "Fail  " << endl; return false;}

  

  return true;
}


bool HNDiLepton::PassHighMassBin2(float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){

  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() == 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  
  vector<int> ijets;
  if(GetMasses("fj",muons, jets,fjets,ijets, false) > 150)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("llfj",muons, jets,fjets,ijets, false) < mllfjmin)  {if(debug)cout << "Fail  " << endl; return false;}

  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}
  
  return true;
}




bool HNDiLepton::PassLowMassBin1(float pt1max, float pt2max,float mjjmax, float mlljjmin,  float mlljjmax, float ml1jjmax, float ml2jjmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet){
  

  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(muons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(muons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  snu::KParticle mm = muons.at(0) + muons.at(1);
  if(mm.M()  < mllmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > mllmax) {if(debug)cout << "Fail mee  " << endl; return false;}

  float met = eventbase->GetEvent().PFMET();
  if(met >  metmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  vector<int > ijets;
  if(GetMasses("lljj",muons, jets,fjets,ijets, true) < mlljjmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("lljj",muons, jets,fjets,ijets, true) > mlljjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("l1jj",muons, jets,fjets,ijets, true) > ml1jjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("l2jj",muons, jets,fjets,ijets, true) > ml2jjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mjjmax != 999.){
    if(GetMasses("jj",muons, jets,fjets,ijets, true) > mjjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  }
  if(GetMasses("lljj",muons, jets,fjets,ijets, true) > 300) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(met >  80) {if(debug)cout << "Fail mee  " << endl; return false;}

  
  return true;
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

void HNDiLepton::CheckJetIDs(TString label, float ll_weight, float jetpt, TString trig){
  
  std::vector<snu::KJet>  jets_nocut = GetJetsWFT("JET_NOCUT", "FATJET_HN_tau06",jetpt, 5.);
  std::vector<snu::KJet>  jets_2p7 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",jetpt, 2.7);
  std::vector<snu::KJet>  jets = GetJetsWFT("JET_HN", "FATJET_HN_tau06",jetpt, 2.7);
  std::vector<snu::KJet>  jets_pu = GetJetsWFT("JET_HN_PU", "FATJET_HN_tau06",jetpt, 5.);
  std::vector<snu::KJet>  jets_tight = GetJetsWFT("JET_HN_TIGHT", "FATJET_HN_tau06",jetpt, 5.);
  std::vector<snu::KJet>  jets_tightlv = GetJetsWFT("JET_HN_TIGHTLV", "FATJET_HN_tau06",jetpt, 5.);
  

  if(jets.size() > 1) FillHist(label+"Jet_sel", 0., ll_weight, 0., 5., 5);
   if(jets_pu.size() > 1)FillHist(label+"Jet_sel", 1., ll_weight, 0., 5., 5);
   if(jets_tight.size() > 1)FillHist(label+"Jet_sel", 2., ll_weight, 0., 5., 5);
   if(jets_tightlv.size() >1 )FillHist(label+"Jet_sel", 3., ll_weight, 0., 5., 5);
   

   vector<int>  i_jets =          GetTruthJets(false);
   vector<int>  i_jets_t =          GetTruthJets(true);
   if(i_jets.size() != 2) {
     if(IsSignal())TruthPrintOut();
   }
   if(1){
     FillHist(label+"_Njet", jets_nocut.size(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 10., 10);

     for(unsigned int i=0 ; i < jets_nocut.size(); i++){
       FillHist(label+"_jet_pt_nc", jets_nocut[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
       FillHist(label+"_jet_eta_nc", jets_nocut[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
       if(IsSignal()) {
	 snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
	 snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
	 if(jets_nocut[i].DeltaR(j1) < 0.4 || jets_nocut[i].DeltaR(j2) < 0.4) {
	   FillHist(label+"_matched_jet_pt_nc", jets_nocut[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
	   FillHist(label+"_matched_jet_eta_nc", jets_nocut[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);

	 }
	 if(i_jets_t.size() > 0){
	   snu::KParticle j1= eventbase->GetTruth().at(i_jets_t[0]);
	   if(jets_nocut[i].DeltaR(j1) < 0.4 ){
	     FillHist(label+"_matched_tjet_pt_nc", jets_nocut[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
	     FillHist(label+"_matched_tjet_eta_nc", jets_nocut[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
	   }
	 }
       }
     }
     
     FillHist(label+"_Njet_pu", jets_pu.size(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 10., 10);
     for(unsigned int i=0 ; i < jets_pu.size(); i++){
       FillHist(label+"_jet_pt_pu", jets_pu[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
       FillHist(label+"_jet_eta_pu", jets_pu[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
       if(IsSignal()) {
	 snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
	 snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
	 if(jets_pu[i].DeltaR(j1) < 0.4 || jets_pu[i].DeltaR(j2) < 0.4) {
	   FillHist(label+"_matched_jet_pt_pu", jets_pu[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
	   FillHist(label+"_matched_jet_eta_pu", jets_pu[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
	 }
	 if(i_jets_t.size() > 0){
	   snu::KParticle j1= eventbase->GetTruth().at(i_jets_t[0]);
           if(jets_pu[i].DeltaR(j1) < 0.4 ){
             FillHist(label+"_matched_tjet_pt_pu", jets_pu[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
             FillHist(label+"_matched_tjet_eta_pu", jets_pu[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
           }
         }

       }
     }
     FillHist(label+"_Njet_tight", jets_tight.size(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 10., 10);

     for(unsigned int i=0 ; i < jets_tight.size(); i++){
       FillHist(label+"_jet_pt_tight", jets_tight[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
       FillHist(label+"_jet_eta_tight", jets_tight[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
       if(IsSignal()) {
	 snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
	 snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
	 if(jets_tight[i].DeltaR(j1) < 0.4 || jets_tight[i].DeltaR(j2) < 0.4) {
	   FillHist(label+"_matched_jet_pt_tight", jets_tight[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
	   FillHist(label+"_matched_jet_eta_tight", jets_tight[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
	 }
	 if(i_jets_t.size() > 0){
	   snu::KParticle j1= eventbase->GetTruth().at(i_jets_t[0]);
           if(jets_tight[i].DeltaR(j1) < 0.4 ){
             FillHist(label+"_matched_tjet_pt_tight", jets_tight[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
             FillHist(label+"_matched_tjet_eta_tight", jets_tight[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
           }
         }

       }
     }
     FillHist(label+"_Njet_tightlv", jets_tightlv.size(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 10., 10);
     for(unsigned int i=0 ; i < jets_tightlv.size(); i++){
       FillHist(label+"_jet_pt_tightlv", jets_tightlv[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
       FillHist(label+"_jet_eta_tightlv", jets_tightlv[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
       if(IsSignal()) {
	 snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
	 snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
	 
	 if(jets_tightlv[i].DeltaR(j1) < 0.4 || jets_tightlv[i].DeltaR(j2) < 0.4) {
	   FillHist(label+"_matched_jet_pt_tightlv", jets_tightlv[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
	   FillHist(label+"_matched_jet_eta_tightlv", jets_tightlv[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
	   
	 }
	 if(i_jets_t.size() > 0){
	   snu::KParticle j1= eventbase->GetTruth().at(i_jets_t[0]);
           if(jets_tightlv[i].DeltaR(j1) < 0.4 ){
             FillHist(label+"_matched_tjet_pt_tightlv", jets_tightlv[i].Pt(), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 100., 500);
             FillHist(label+"_matched_tjet_eta_tightlv", jets_tightlv[i].Eta(), ll_weight*WeightByTrigger(trig, TargetLumi), -5., 5., 50);
           }
         }

       }
     }
   }
   
   
 }



void HNDiLepton::FillHighMass(bool FillAll,int mode, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float met2_st,float ll_weight, TString trig){

  if((CheckSignalRegion(true,muons,electrons , jets, fatjets,alljets,"HighMM", ll_weight,mode)) ){
    if( (mode==0 && jets.size() > 1)  || (mode==1 &&jets.size() > 1 && fatjets.size() ==0) || (mode==2 && fatjets.size()>0)){
      FillEventCutFlow(4,"SSLL_HighMass_mlljj",ll_weight,label);

      if(nbjet_m==0){
	if(met2_st < 15) {
	  if(mode==1){
	    if(!PassHighMassBin1(0.,0.,0., 99999., 0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)){cout << "EVent HM miss match " << nbjet_m << " " << met2_st <<  endl;
	      bool check=PassHighMassBin1(0.,0.,0., 9999., 0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st,true);
	      vector<int> tmpv;
	      cout << GetMasses("jj",muons, jets,fatjets,tmpv, false) << endl;
	    }
	  }

	  if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  FillEventCutFlow(4,"SSLL_HighMass_SR",ll_weight,label);
	  if(muons[0].Pt() > 140 && muons[1].Pt() > 70)FillEventCutFlow(4,"SSLL_HighMass_SR2",ll_weight,label);
	  if(met2_st < 7){
	    if(mode==1) {
	      if(fatjets.size() ==0){
		vector<int > ijets;
		float mlljj = GetMasses("lljj",muons, jets,fatjets,ijets, true);
		float mjj = GetMasses("jj",muons, jets,fatjets,ijets, true);
		if(muons[0].Pt() >110 && muons[1].Pt() > 40 && mlljj > 800, mjj > 30 && mjj < 150)               if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	      }
	    }
	    if(mode==2) {
	      if(fatjets.size() >0){
		vector<int > ijets;
		float mllfj = GetMasses("llfj",muons, jets,fatjets,ijets, true);
		float mjj = fatjets[0].PrunedMass();
		if(muons[0].Pt() >140 && muons[1].Pt() > 70 && mllfj > 640, mjj > 30 && mjj < 150)               if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	      }
	    }

	    FillHist(label+"Truth_WZ_SS_HighMass_Zmass",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 150., 150);
	  }
	}
	if(mode ==0 ){
	  if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	}
	if(mode==1){
	  if(fatjets.size() ==0){
	    if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	  }
	}
	if(mode==2){
	  if(fatjets.size() >0){
	    if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	  }
	}

	if(mode==2){
	  if(fatjets.size() >0){
	    if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_mm, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	  }
	}
      }
    }
  }



}


void HNDiLepton::FillLowMass(bool FillAll, int mode, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, TString trig){

  float met = eventbase->GetEvent().PFMET();  
  if(CheckSignalRegion(true,muons,electrons, jets,fatjets, alljets,"LowMM", ll_weight, mode)){
    if(jets.size()==1) FillEventCutFlow(4,"SSLL_LowMass_1Jet_mlljj",ll_weight,label);
    if(jets.size()==2 )FillEventCutFlow(4,"SSLL_LowMass_mlljj",ll_weight,label);
    if(nbjet_m == 0){
      if(jets.size()==1 )FillEventCutFlow(4,"SSLL_LowMass_1Jet_0bjet",ll_weight,label);
      if(jets.size()==2 ) FillEventCutFlow(4,"SSLL_LowMass_0bjet",ll_weight,label);

  
      if(met < 80){
	if(FillAll){
	  if(jets.size() >1){
	    FillCLHist(sighist_mm, label+"SSLL_LowMass_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(muons[1].Pt() < 15. && met < 40){
	      if(muons[0].Pt() > 25. && GetDiLepMass(muons) < 40 && GetDiLepMass(muons) > 15 && muons[0].Pt() < 45. && jets[0].Pt() > 15.)FillCLHist(sighist_mm, label+"SSLL_LowMass_SR0", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	    }
	    if(muons[1].Pt() > 15. && met < 40 && GetDiLepMass(muons) < 40 && GetDiLepMass(muons) > 15 && muons[0].Pt() < 50. && jets[0].Pt() > 15.)                     FillCLHist(sighist_mm, label+"SSLL_LowMass_SR1", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);																						    
	    if(muons[1].Pt() > 15. && met < 40 && GetDiLepMass(muons) < 50 && GetDiLepMass(muons) > 15 && muons[0].Pt() < 50. && jets[0].Pt() > 15.&&  jets[1].Pt() > 15.)                     FillCLHist(sighist_mm, label+"SSLL_LowMass_SR1b", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

	  }
	  
	  if(jets.size()==1 ) {
	    FillCLHist(sighist_mm, label+"SSLL_LowMass_1Jet_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	    if(muons[1].Pt() < 15.&&met < 40)                        FillCLHist(sighist_mm, label+"SSLL_LowMass_1Jet_SR0", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
	  }
	}
	if(jets.size()> 1)FillEventCutFlow(4,"SSLL_LowMass_SR",ll_weight,label);

	if(met<40){
	  if(jets.size()> 1)FillEventCutFlow(4,"SSLL_LowMass_SR_pt2_5",ll_weight,label);
	  if(jets.size()> 1&& muons[1].Pt() > 10)FillEventCutFlow(4,"SSLL_LowMass_SR_pt2_10",ll_weight,label);
	  if(jets.size()> 1&& muons[1].Pt() > 15)FillEventCutFlow(4,"SSLL_LowMass_SR_pt2_15",ll_weight,label);
	}

	if(jets.size()==1 )FillEventCutFlow(4,"SSLL_LowMass_1Jet_SR",ll_weight,label);
	if(met<40){
	  if(jets.size()> 1&& muons[1].Pt() > 5)FillEventCutFlow(4,"SSLL_LowMass_1Jet_SR_pt2_5",ll_weight,label);

	  if(jets.size()==1 && muons[1].Pt() > 10)FillEventCutFlow(4,"SSLL_LowMass_1Jet_SR_pt2_10",ll_weight,label);
	  if(jets.size()==1 && muons[1].Pt() > 15)FillEventCutFlow(4,"SSLL_LowMass_1Jet_SR_pt2_15",ll_weight,label);
	}
	if(muons[1].Pt()>15 && muons[1].Pt() < 50.){
	  if(muons[0].Pt() < 80){
	    if(met < 40)FillHist(label+"Truth_WZ_SS_LowMass_Zmass",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 150., 150);
	  }
	}
      }

      vector<int > ijets;
      float mlljj = GetMasses("lljj",muons, jets,fatjets,ijets, true);
      float ml1jj = GetMasses("l1jj",muons, jets,fatjets,ijets, true);
      float ml2jj = GetMasses("l2jj",muons, jets,fatjets,ijets, true);

      if(muons[1].Pt()>15 && muons[1].Pt() < 50. && muons[0].Pt() < 80.&& mlljj < 250 && ml1jj < 200 && ml2jj< 150 && met < 40 && GetDiLepMass(electrons) < 100&& FillAll)FillCLHist(sighist_mm, label+"SSLL_LowMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
																						  
    }
  
    if(met > 100 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_mm, label+"SSLL_LowMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight); 
  }
  
}

void HNDiLepton::FillHighMassBins(bool FillAll, int mode, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float met2_st,float ll_weight){
  if(mode==2){
    if(jets.size() > 1&& fatjets.size() ==0) {
      if(PassHighMassBin1(0.,0.,99999., 0., 0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_inc",ll_weight,label);
    }
  }
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_inc",ll_weight,label);
  if(PassHighMassBin1(110.,0., 0., 9999.,  0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_pt1",ll_weight,label);
  if(PassHighMassBin1(0.,60., 0., 9999.,  0., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_pt2",ll_weight,label);
  if(PassHighMassBin1(0.,0.,0., 9999., 490., 0., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mlljj",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 30., 100000., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mjjmin",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 150., 1000.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mjjmax",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_met",ll_weight,label);

  if(PassHighMassBin1(25.,15., 50., 105., 90.,  30.,  150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_90",ll_weight,label);
  if(PassHighMassBin1(25.,15., 70., 115.,110., 30., 150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_100",ll_weight,label);
  if(PassHighMassBin1(25.,25., 90., 140., 140.,30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_125",ll_weight,label);
  if(PassHighMassBin1(35.,35., 100., 170., 150., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_150",ll_weight,label);
  if(PassHighMassBin1(50.,40., 160., 250., 250., 30.,150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_200",ll_weight,label);
  if(PassHighMassBin1(85.,45.,0., 99999., 310., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_250",ll_weight,label);
  if(PassHighMassBin1(100.,50.,0., 99999., 370., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_300",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 490., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_400",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 610., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_500",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 680., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_600",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_700",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_800",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_900",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1000",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1100",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1200",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1300",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1400",ll_weight,label);
  if(PassHighMassBin1(110.,60.,0., 99999., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1500",ll_weight,label);

  if(PassHighMassBin1Window(0.2,90., 25.,15.,90., 50., 105., 30.,  150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_90",ll_weight,label);
  if(PassHighMassBin1Window(0.2,100., 25.,15.,110., 70., 115., 30., 150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_100",ll_weight,label);
  if(PassHighMassBin1Window(0.2,125.,25.,25.,140., 90., 140., 30.,150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_125",ll_weight,label);
  if(PassHighMassBin1Window(0.2,150., 35.,35.,150., 100., 170., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_150",ll_weight,label);
  if(PassHighMassBin1Window(0.2,200., 50.,40.,250., 160., 250., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_200",ll_weight,label);
  if(PassHighMassBin1Window(0.2,250., 85.,45.,99999., 0., 310., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_250",ll_weight,label);
  if(PassHighMassBin1Window(0.2,300.,100.,50.,99999., 0., 370., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_300",ll_weight,label);
  if(PassHighMassBin1Window(0.2,400.,110.,60.,99999., 0., 490., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_400",ll_weight,label);
  if(PassHighMassBin1Window(0.2,500.,100.,60.,99999., 0., 610., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_500",ll_weight,label);
  if(PassHighMassBin1Window(0.2,600.,100.,40.,99999., 0., 680., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_600",ll_weight,label);
  if(PassHighMassBin1Window(0.2,700.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_700",ll_weight,label);
  if(PassHighMassBin1Window(0.2,800.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_800",ll_weight,label);
  if(PassHighMassBin1Window(0.2,900.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_900",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1000.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1000",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1100.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1100",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1200.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1200",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1300.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1300",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1400.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1400",ll_weight,label);
  if(PassHighMassBin1Window(0.2,1500.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(14,"HM_Window02_Bin1_1500",ll_weight,label);

  std::map<float, TString> masslist;

  masslist[40.] = "40";
  masslist[50.] = "50";
  masslist[60.] = "60";
  masslist[70.] = "70";
  masslist[80.] = "80";
  masslist[90.] = "90";
  masslist[100.] = "100";
  masslist[125.] = "125";
  masslist[150.] = "150";
  masslist[200.] = "200";
  masslist[250.] = "250";
  masslist[300.] = "300";
  masslist[400.] = "400";
  masslist[500.] = "500";
  masslist[600.] = "600";
  masslist[700.] = "700";
  masslist[800.] = "800";
  masslist[900.] = "900";
  masslist[1000.] = "1000";
  masslist[1200.] = "1200";
  masslist[1300.] = "1300";
  masslist[1400.] = "1400";
  masslist[1500.] = "1500";

  std::map<float,TString>::iterator mit;
  for( mit = masslist.begin(); mit !=masslist.end(); mit++){
    if(PassHighMassBin1Window(0.2,mit->first,  25.,15., mit->first, 0., 99999.,  30., 150  , 0.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_"+mit->second,ll_weight,label);
  }

  if(PassHighMassBin1Window(-0.2,90., 25.,15.,90., 50., 105., 30.,  150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_90",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,100., 25.,15.,110., 70., 115., 30., 150., 9.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_100",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,125.,25.,25.,140., 90., 140., 30.,150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_125",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,150., 35.,35.,150., 100., 170., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_150",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,200., 50.,40.,250., 160., 250., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_200",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,250., 85.,45.,99999., 0., 310., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_250",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,300.,100.,50.,99999., 0., 370., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_300",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,400.,110.,60.,99999., 0., 490., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_400",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,500.,100.,60.,99999., 0., 610., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_500",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,600.,100.,40.,99999., 0., 680., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_600",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,700.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_700",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,800.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_800",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,900.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_900",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1000.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1000",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1100.,110.,40.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1100",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1200.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1200",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1300.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1300",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1400.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1400",ll_weight,label);
  if(PassHighMassBin1Window(-0.2,1500.,110.,60.,99999., 0., 800., 30., 150., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(15,"HM_Window03_Bin1_1500",ll_weight,label);

  if(mode==2){

    if(fatjets.size() > 0){
      if(PassHighMassBin2(0.,0,0., 0.,  muons,jets,fatjets,nbjet_m,met2_st))
	FillEventCutFlow(11,"HM_Bin2_inc",ll_weight,label);
    }


    if(PassHighMassBin2(25.,15,190., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_90",ll_weight,label);
    if(PassHighMassBin2(25.,15,190., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_100",ll_weight,label);
    if(PassHighMassBin2(60.,15,270., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_125",ll_weight,label);
    if(PassHighMassBin2(70.,15,270., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_150",ll_weight,label);

    if(PassHighMassBin2(100.,20,280., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_200",ll_weight,label);
    if(PassHighMassBin2(140.,25,350., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_250",ll_weight,label);
    if(PassHighMassBin2(140.,40,380., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_300",ll_weight,label);
    if(PassHighMassBin2(140.,65,450., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_400",ll_weight,label);
    if(PassHighMassBin2(140.,65,550., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_500",ll_weight,label);
    if(PassHighMassBin2(140.,75,590., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_600",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_700",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_800",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_900",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1000",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1100",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1200",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1300",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1400",ll_weight,label);
    if(PassHighMassBin2(140.,75,640., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1500",ll_weight,label);


    if(PassHighMassBin2(0.,0,0., 0.,  muons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_inc",ll_weight,label);
    if(PassHighMassBin2(140.,0,0., 0.,  muons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_pt1",ll_weight,label);
    if(PassHighMassBin2(0.,65,0., 0.,  muons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_pt2",ll_weight,label);
    if(PassHighMassBin2(0.,0,450., 0.,  muons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_mlljj",ll_weight,label);


    if(PassHighMassBin2Window(90., 25.,15,190., 7.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_90",ll_weight,label);
    if(PassHighMassBin2Window(100.,25.,15,190., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_100",ll_weight,label);
    if(PassHighMassBin2Window(125.,60.,15,270., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_125",ll_weight,label);
    if(PassHighMassBin2Window(150.,70.,15,270., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_150",ll_weight,label);

    if(PassHighMassBin2Window(200.,100.,20,280., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_200",ll_weight,label);
    if(PassHighMassBin2Window(250.,140.,25,350., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_250",ll_weight,label);
    if(PassHighMassBin2Window(300.,140.,40,380., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_300",ll_weight,label);
    if(PassHighMassBin2Window(400.,140.,65,450., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_400",ll_weight,label);
    if(PassHighMassBin2Window(500.,140.,65,550., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_500",ll_weight,label);
    if(PassHighMassBin2Window(600.,140.,70,530., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_600",ll_weight,label);
    if(PassHighMassBin2Window(700,140.,70,550., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_700",ll_weight,label);
    if(PassHighMassBin2Window(800.,140.,70,590., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_800",ll_weight,label);
    if(PassHighMassBin2Window(900.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_900",ll_weight,label);
    if(PassHighMassBin2Window(1000.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1000",ll_weight,label);
    if(PassHighMassBin2Window(1100.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1100",ll_weight,label);
    if(PassHighMassBin2Window(1200.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1200",ll_weight,label);
    if(PassHighMassBin2Window(1300.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1300",ll_weight,label);
    if(PassHighMassBin2Window(1400.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1400",ll_weight,label);
    if(PassHighMassBin2Window(1500.,140.,70,540., 15.,  muons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(16,"HM_Window_Bin2_1500",ll_weight,label);

  }

}


void HNDiLepton::FillLowMassBins(bool FillAll,int mode, TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight){
  
  if(jets.size()==1){
    if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m)) FillEventCutFlow(5,"LM_Bin2_inc",ll_weight,label);
    if(PassLowMassBin2(80., 50., 100.,70., 70.,  40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_40",ll_weight,label);
    if(PassLowMassBin2(80., 50., 100.,70., 70., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_50",ll_weight,label);
    if(PassLowMassBin2(80., 50., 100.,70., 70., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_60",ll_weight,label);
    if(PassLowMassBin2(80., 50., 100.,70., 70., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_70",ll_weight,label);
    if(PassLowMassBin2(80., 50., 100.,70., 70., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80",ll_weight,label);
    /// alt bins                                                                                                                                                                                                                                              
    if(PassLowMassBin2(80., 50., 150.,70., 70., 40., 10., 100, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v2",ll_weight,label);
    if(PassLowMassBin2(80., 50., 150.,70., 70., 40., 10., 80, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v3",ll_weight,label);
    if(PassLowMassBin2(80., 50., 150.,70., 70., 40., 15., 80, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v4",ll_weight,label);
    if(PassLowMassBin2(80., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"1_Bin2_pt1max",ll_weight,label);
    if(PassLowMassBin2(100000.,50., 1100000., 10000., 10000.,10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"2_Bin2_pt2max",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 10000.,70., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_ml1j",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 10000.,10000., 70., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_ml2j",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,40., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"4_Bin2_met",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 20., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"5_Bin2_mllmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 0., 60., 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"6_Bin2_mllmax",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 0., 10000., 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"7_Bin2_ptmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m)) FillEventCutFlow(6,"0_Bin2_inc",ll_weight,label);
    if(PassLowMassBin2(80., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_1_Bin2_pt1max",ll_weight,label);
    if(PassLowMassBin2(80.,50., 1100000., 10000., 10000.,10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_2_Bin2_pt2max",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100.,10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100.,70., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100.,70., 70., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100.,70., 70., 40., 0., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_4_Bin2_met",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100.,70., 70., 40., 20., 10000, 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_5_Bin2_mllmin",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100., 70., 70.,40., 20., 60., 0., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_6_Bin2_mllmax",ll_weight,label);
    if(PassLowMassBin2(80.,50., 100., 70., 70.,40., 20., 60., 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_7_Bin2_ptmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 1100000., 10000., 10000., 10000., 0., 10000, 0., muons,jets,fatjets,nbjet_m))   FillEventCutFlow(7,"culm_0_Bin2_inc",ll_weight,label);

  }
  if(jets.size() > 1) {
    if(PassLowMassBin1(10000.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))
      FillEventCutFlow(5,"LM_Bin1_inc",ll_weight,label);

    if(PassLowMassBin1(10000., 10000., 120.,80., 200.,10000., 100000., 30., 15., 100000, 15., muons,jets,fatjets,nbjet_m)){
      FillEventCutFlow(5,"LM_Bin1_8TeV_40",ll_weight,label);
      if(FillAll)FillCLHist(sighist_mm, label+"SSLL_LowMass_8TeV", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
    }
    if(PassLowMassBin1(10000., 10000., 120.,90., 200.,10000., 100000., 30., 15., 100000, 15., muons,jets,fatjets,nbjet_m))          FillEventCutFlow(5,"LM_Bin1_8TeV_70",ll_weight,label);
																		     
    if(PassLowMassBin1(10000., 10000., 120.,100., 200.,10000., 100000., 30., 15., 100000, 15., muons,jets,fatjets,nbjet_m))          FillEventCutFlow(5,"LM_Bin1_8TeV_80",ll_weight,label);
																		      
    if(PassLowMassBin1(80.   , 50.   , 9999. , 0. ,160.  ,150.   , 150.    , 40. , 20.  , 60  , 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_40", ll_weight,label);
																			       
    if(PassLowMassBin1(80., 50., 9999.,0.,160.,150., 150., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_50",ll_weight,label);
    if(PassLowMassBin1(80., 50., 9999., 0.,160.,150., 150., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_60",ll_weight,label);
    if(PassLowMassBin1(80., 50., 9999.,0., 160.,150., 150., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_70",ll_weight,label);
    if(PassLowMassBin1(80., 50., 9999.,0.,160.,150., 150., 40., 20., 60, 15., muons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_80",ll_weight,label);


    if(PassLowMassBin1(80.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_1_Bin1_pt1max",ll_weight,label);

																		      
    if(PassLowMassBin1(80.,  50., 1100000., 0., 100000., 10000, 100000., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_2_Bin1_pt2max",ll_weight,label);
																		    
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 10000, 100000., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_3_Bin1_mlljj",ll_weight,label);
																	      
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 100000., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_4_Bin1_ml1jj",ll_weight,label);

																	    
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 150., 10000., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_5_Bin1_ml2jj",ll_weight,label);
																	 
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 150., 40., 0., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_6_Bin1_met",ll_weight,label);
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 150., 40., 20., 10000., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_7_Bin1_mllmin",ll_weight,label);
															
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 150., 40., 20., 60., 0,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_8_Bin1_mllmax",ll_weight,label);
    if(PassLowMassBin1(80.,  50., 9999., 0., 180., 150, 150., 40., 20., 60., 15,  muons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_9_Bin1_ptmin",ll_weight,label);

   
 
  }


		     

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

    if(GetHist(label+ "mm_eventcutflow_DoubleMuon")) {
      GetHist( label+"mm_eventcutflow_DoubleMuon")->Fill(cut,wt);

    }
    else{

      vector<TString> muonIDs;
      muonIDs.push_back("NoCut");
      muonIDs.push_back("MUON_HN_EFF_PT");
      muonIDs.push_back("MUON_HN_EFF_HLTMu17");
      muonIDs.push_back("MUON_HN_EFF_HLTMuISO");
      muonIDs.push_back("MUON_HN_EFF_PT15");
      muonIDs.push_back("MUON_HN_EFF_POG");
      muonIDs.push_back("MUON_HN_EFF_DXY");
      muonIDs.push_back("MUON_HN_EFF_DZ");
      muonIDs.push_back("MUON_HN_EFF_dxysig");
      muonIDs.push_back("MUON_HN_EFF_iso");
      muonIDs.push_back("MUON_HN_EFF_onlyiso");
      muonIDs.push_back("MUON_HN_EFF_8TeViso");
      muonIDs.push_back("MUON_HN_TIGHT");
      muonIDs.push_back("DiJet");
      muonIDs.push_back("Jet1");
      muonIDs.push_back("Jet2");
      muonIDs.push_back("Jet3");
      muonIDs.push_back("8TeV_LM");
      muonIDs.push_back("13TeV_LM");
      muonIDs.push_back("MUON_HN_TIGHT_8TeV"  );
      muonIDs.push_back("8TeV_OLDID_LM");
      muonIDs.push_back("13TeV_OLDID_LM");

      AnalyzerCore::MakeHistograms( label+"mm_eventcutflow_DoubleMuon",muonIDs.size(),0.,float(muonIDs.size()));

      for(unsigned int iid=0; iid < muonIDs.size(); iid++){

        TString elid = muonIDs[iid];
        GetHist(label+ "mm_eventcutflow_DoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( label+"mm_eventcutflow_DoubleMuon")->Fill(cut,wt);

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
    if(GetHist( label + "ll_lowmass_flow")) {
      GetHist( label + "ll_lowmass_flow")->Fill(cut,wt);
      counter(label+"_ll_lowmass_flow_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      if(label.Contains("FAT") && !label.Contains("NoFAT") ){
	IDs.push_back("NoCut");
	IDs.push_back("EventCleaning");
	IDs.push_back("DiLep");
	IDs.push_back("Trigger");
	IDs.push_back("TriggerMu17");
	IDs.push_back("TriggerIso24");
	IDs.push_back("LepVeto");
	IDs.push_back("SSLLLoose");
	IDs.push_back("MLL");
	IDs.push_back("Presel");
	IDs.push_back("SSLL_HighMass_SR");
	IDs.push_back("SSLL_HighMass_mlljj");

	IDs.push_back("SSLL_HighMass_SR2");

      }
      else{
	IDs.push_back("NoCut");
	IDs.push_back("EventCleaning");
	IDs.push_back("DiLep");
	IDs.push_back("Trigger");
	IDs.push_back("TriggerMu17");
	IDs.push_back("TriggerIso24");
	IDs.push_back("LepVeto");
	IDs.push_back("SSLLLoose");
	IDs.push_back("MLL");
	IDs.push_back("Presel");
	IDs.push_back("Presel_8TeV");
	IDs.push_back("SSLL_1Jet");
	IDs.push_back("SSLL_1Jet_noB");
	IDs.push_back("SSLL_DiJet");
	IDs.push_back("SSLL_DiJet_noB");
	IDs.push_back("SSLL_DiJet_passMET");
	IDs.push_back("SSLL_LowMass_mlljj");
	IDs.push_back("SSLL_LowMass_1Jet_mlljj");
	IDs.push_back("SSLL_LowMass_0bjet");
	IDs.push_back("SSLL_LowMass_1Jet_0bjet");
	IDs.push_back("SSLL_LowMass_SR");
	IDs.push_back("SSLL_LowMass_SR_pt2_5");
	IDs.push_back("SSLL_LowMass_SR_pt2_10");
	IDs.push_back("SSLL_LowMass_SR_pt2_15");
	IDs.push_back("SSLL_LowMass_1Jet_SR");
	IDs.push_back("SSLL_LowMass_1Jet_SR_pt2_5");
	IDs.push_back("SSLL_LowMass_1Jet_SR_pt2_10");
	IDs.push_back("SSLL_LowMass_1Jet_SR_pt2_15");
	IDs.push_back("SSLL_HighMass_mlljj");
	IDs.push_back("SSLL_HighMass_SR");
	IDs.push_back("SSLL_HighMass_SR2");

      }

      AnalyzerCore::MakeHistograms( label + "ll_lowmass_flow",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_lowmass_flow")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_lowmass_flow_"+cut ,wt);
      
      GetHist( label + "ll_lowmass_flow")->Fill(cut,wt);

    }
  }
  if(cf==5){
    if(GetHist( label + "ll_lowmasssig_bin1_2")) {
      GetHist( label + "ll_lowmasssig_bin1_2")->Fill(cut,wt);
      counter(label+"_ll_lowmasssig_bin1_2_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("LM_Bin1_inc");
      IDs.push_back("LM_Bin1_40");
      IDs.push_back("LM_Bin1_8TeV_40");
      IDs.push_back("LM_Bin1_8TeV_70");
      IDs.push_back("LM_Bin1_8TeV_80");
      IDs.push_back("LM_Bin1_50");
      IDs.push_back("LM_Bin1_60");
      IDs.push_back("LM_Bin1_70");
      IDs.push_back("LM_Bin1_80");
      IDs.push_back("LM_Bin2_inc");
      IDs.push_back("LM_Bin2_40");
      IDs.push_back("LM_Bin2_50");
      IDs.push_back("LM_Bin2_60");
      IDs.push_back("LM_Bin2_70");
      IDs.push_back("LM_Bin2_80");
      IDs.push_back("LM_Bin2_80v2");
      IDs.push_back("LM_Bin2_80v3");
      IDs.push_back("LM_Bin2_80v4");
      


      AnalyzerCore::MakeHistograms( label + "ll_lowmasssig_bin1_2",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_lowmasssig_bin1_2")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_lowmasssig_bin1_2_"+cut ,wt);

      GetHist( label + "ll_lowmasssig_bin1_2")->Fill(cut,wt);

    }
  }
  if(cf==6){
    if(GetHist( label + "ll_lowmasssig_bin2_breakdown")) {
      GetHist( label + "ll_lowmasssig_bin2_breakdown")->Fill(cut,wt);
      counter(label+"_ll_lowmasssig_bin2_breakdown_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("1_Bin2_pt1max");
      IDs.push_back("2_Bin2_pt2max");
      IDs.push_back("3_Bin2_mllj");
      IDs.push_back("3_Bin2_ml1j");
      IDs.push_back("3_Bin2_ml2j");
      IDs.push_back("4_Bin2_met");
      IDs.push_back("5_Bin2_mllmin");
      IDs.push_back("6_Bin2_mllmax");
      IDs.push_back("7_Bin2_ptmin");

      AnalyzerCore::MakeHistograms( label + "ll_lowmasssig_bin2_breakdown",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_lowmasssig_bin2_breakdown")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_lowmasssig_bin2_breakdown_"+cut ,wt);

      GetHist( label + "ll_lowmasssig_bin2_breakdown")->Fill(cut,wt);

    }
  }
  if(cf==7){
    if(GetHist( label + "ll_lowmasssig_bin2_culmbreakdown")) {
      GetHist( label + "ll_lowmasssig_bin2_culmbreakdown")->Fill(cut,wt);
      counter(label+"_ll_lowmasssig_bin2_culmbreakdown_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("culm_0_Bin2_inc");
      IDs.push_back("culm_1_Bin2_pt1max");
      IDs.push_back("culm_2_Bin2_pt2max");
      IDs.push_back("culm_3_Bin2_mllj");
      IDs.push_back("culm_3_Bin2_ml1j");
      IDs.push_back("culm_3_Bin2_ml2j");
      IDs.push_back("culm_4_Bin2_met");
      IDs.push_back("culm_5_Bin2_mllmin");
      IDs.push_back("culm_6_Bin2_mllmax");
      IDs.push_back("culm_7_Bin2_ptmin");

      AnalyzerCore::MakeHistograms( label + "ll_lowmasssig_bin2_culmbreakdown",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_lowmasssig_bin2_culmbreakdown")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_lowmasssig_bin2_culmbreakdown_"+cut ,wt);

      GetHist( label + "ll_lowmasssig_bin2_culmbreakdown")->Fill(cut,wt);

    }
  }

  if(cf==9){
    if(GetHist( label + "ll_lowmasssig_bin1_culmbreakdown")) {
      GetHist( label + "ll_lowmasssig_bin1_culmbreakdown")->Fill(cut,wt);
      counter(label+"_ll_lowmasssig_bin1_culmbreakdown_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("culm_1_Bin1_pt1max");
      IDs.push_back("culm_2_Bin1_pt2max");
      IDs.push_back("culm_3_Bin1_mlljj");
      IDs.push_back("culm_4_Bin1_ml1jj");
      IDs.push_back("culm_5_Bin1_ml2jj");
      IDs.push_back("culm_6_Bin1_met");
      IDs.push_back("culm_7_Bin1_mllmin");
      IDs.push_back("culm_8_Bin1_mllmax");
      IDs.push_back("culm_9_Bin1_ptmin");

      AnalyzerCore::MakeHistograms( label + "ll_lowmasssig_bin1_culmbreakdown",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

	TString elid = IDs[iid];
        GetHist( label + "ll_lowmasssig_bin1_culmbreakdown")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_lowmasssig_bin1_culmbreakdown_"+cut ,wt);

      GetHist( label + "ll_lowmasssig_bin1_culmbreakdown")->Fill(cut,wt);

    }
  }


  if(cf==10){
    if(GetHist( label + "ll_highmasssig_bin1")) {
      GetHist( label + "ll_highmasssig_bin1")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_bin1_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Bin1_inc");
      IDs.push_back("HM_Bin1_90");
      IDs.push_back("HM_Bin1_100");
      IDs.push_back("HM_Bin1_125");
      IDs.push_back("HM_Bin1_150");
      IDs.push_back("HM_Bin1_200");
      IDs.push_back("HM_Bin1_250");
      IDs.push_back("HM_Bin1_300");
      IDs.push_back("HM_Bin1_400");
      IDs.push_back("HM_Bin1_500");
      IDs.push_back("HM_Bin1_600");
      IDs.push_back("HM_Bin1_700");
      IDs.push_back("HM_Bin1_800");
      IDs.push_back("HM_Bin1_900");
      IDs.push_back("HM_Bin1_1000");
      IDs.push_back("HM_Bin1_1100");
      IDs.push_back("HM_Bin1_1200");
      IDs.push_back("HM_Bin1_1300");
      IDs.push_back("HM_Bin1_1400");
      IDs.push_back("HM_Bin1_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_bin1",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_bin1")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_bin1_"+cut ,wt);

      GetHist( label + "ll_highmasssig_bin1")->Fill(cut,wt);

    }
  }
  
  if(cf==14){
    if(GetHist( label + "ll_highmasssig_window02_bin1")) {
      GetHist( label + "ll_highmasssig_window02_bin1")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_window02_bin1_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Window02_Bin1_inc");
      IDs.push_back("HM_Window02_Bin1_90");
      IDs.push_back("HM_Window02_Bin1_100");
      IDs.push_back("HM_Window02_Bin1_125");
      IDs.push_back("HM_Window02_Bin1_150");
      IDs.push_back("HM_Window02_Bin1_200");
      IDs.push_back("HM_Window02_Bin1_250");
      IDs.push_back("HM_Window02_Bin1_300");
      IDs.push_back("HM_Window02_Bin1_400");
      IDs.push_back("HM_Window02_Bin1_500");
      IDs.push_back("HM_Window02_Bin1_600");
      IDs.push_back("HM_Window02_Bin1_700");
      IDs.push_back("HM_Window02_Bin1_800");
      IDs.push_back("HM_Window02_Bin1_900");
      IDs.push_back("HM_Window02_Bin1_1000");
      IDs.push_back("HM_Window02_Bin1_1100");
      IDs.push_back("HM_Window02_Bin1_1200");
      IDs.push_back("HM_Window02_Bin1_1300");
      IDs.push_back("HM_Window02_Bin1_1400");
      IDs.push_back("HM_Window02_Bin1_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_window02_bin1",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_window02_bin1")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_window02_bin1_"+cut ,wt);

      GetHist( label + "ll_highmasssig_window02_bin1")->Fill(cut,wt);

    }
  }

  if(cf==15){
    if(GetHist( label + "ll_highmasssig_window03_bin1")) {
      GetHist( label + "ll_highmasssig_window03_bin1")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_window03_bin1_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Window03_Bin1_inc");
      IDs.push_back("HM_Window03_Bin1_90");
      IDs.push_back("HM_Window03_Bin1_100");
      IDs.push_back("HM_Window03_Bin1_125");
      IDs.push_back("HM_Window03_Bin1_150");
      IDs.push_back("HM_Window03_Bin1_200");
      IDs.push_back("HM_Window03_Bin1_250");
      IDs.push_back("HM_Window03_Bin1_300");
      IDs.push_back("HM_Window03_Bin1_400");
      IDs.push_back("HM_Window03_Bin1_500");
      IDs.push_back("HM_Window03_Bin1_600");
      IDs.push_back("HM_Window03_Bin1_700");
      IDs.push_back("HM_Window03_Bin1_800");
      IDs.push_back("HM_Window03_Bin1_900");
      IDs.push_back("HM_Window03_Bin1_1000");
      IDs.push_back("HM_Window03_Bin1_1100");
      IDs.push_back("HM_Window03_Bin1_1200");
      IDs.push_back("HM_Window03_Bin1_1300");
      IDs.push_back("HM_Window03_Bin1_1400");
      IDs.push_back("HM_Window03_Bin1_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_window03_bin1",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_window03_bin1")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_window03_bin1_"+cut ,wt);

      GetHist( label + "ll_highmasssig_window03_bin1")->Fill(cut,wt);

    }
  }
  if(cf==17){
    if(GetHist( label + "ll_highmasssig_only_window02_bin1")) {
      GetHist( label + "ll_highmasssig_only_window02_bin1")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_only_window02_bin1_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Window02_Bin1_inc");
      IDs.push_back("HM_Window02_Bin1_90");
      IDs.push_back("HM_Window02_Bin1_100");
      IDs.push_back("HM_Window02_Bin1_125");
      IDs.push_back("HM_Window02_Bin1_150");
      IDs.push_back("HM_Window02_Bin1_200");
      IDs.push_back("HM_Window02_Bin1_250");
      IDs.push_back("HM_Window02_Bin1_300");
      IDs.push_back("HM_Window02_Bin1_400");
      IDs.push_back("HM_Window02_Bin1_500");
      IDs.push_back("HM_Window02_Bin1_600");
      IDs.push_back("HM_Window02_Bin1_700");
      IDs.push_back("HM_Window02_Bin1_800");
      IDs.push_back("HM_Window02_Bin1_900");
      IDs.push_back("HM_Window02_Bin1_1000");
      IDs.push_back("HM_Window02_Bin1_1100");
      IDs.push_back("HM_Window02_Bin1_1200");
      IDs.push_back("HM_Window02_Bin1_1300");
      IDs.push_back("HM_Window02_Bin1_1400");
      IDs.push_back("HM_Window02_Bin1_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_only_window02_bin1",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_only_window02_bin1")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_only_window02_bin1_"+cut ,wt);

      GetHist( label + "ll_highmasssig_only_window02_bin1")->Fill(cut,wt);

    }
  }



  if(cf==11){
    if(GetHist( label + "ll_highmasssig_bin2")) {
      GetHist( label + "ll_highmasssig_bin2")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_bin2_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Bin2_inc");
      IDs.push_back("HM_Bin2_90");
      IDs.push_back("HM_Bin2_100");
      IDs.push_back("HM_Bin2_125");
      IDs.push_back("HM_Bin2_150");
      IDs.push_back("HM_Bin2_200");
      IDs.push_back("HM_Bin2_250");
      IDs.push_back("HM_Bin2_300");
      IDs.push_back("HM_Bin2_400");
      IDs.push_back("HM_Bin2_500");
      IDs.push_back("HM_Bin2_600");
      IDs.push_back("HM_Bin2_700");
      IDs.push_back("HM_Bin2_800");
      IDs.push_back("HM_Bin2_900");
      IDs.push_back("HM_Bin2_1000");
      IDs.push_back("HM_Bin2_1100");
      IDs.push_back("HM_Bin2_1200");
      IDs.push_back("HM_Bin2_1300");
      IDs.push_back("HM_Bin2_1400");
      IDs.push_back("HM_Bin2_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_bin2",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

	TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_bin2")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_bin2_"+cut ,wt);

      GetHist( label + "ll_highmasssig_bin2")->Fill(cut,wt);

    }
  }


  if(cf==12){
    if(GetHist( label + "ll_highmasssig_bin1_breakdown")) {
      GetHist( label + "ll_highmasssig_bin1_breakdown")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_bin1_breakdown_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Bin1_400_inc");
      IDs.push_back("HM_Bin1_400_pt1");
      IDs.push_back("HM_Bin1_400_pt2");
      IDs.push_back("HM_Bin1_400_mlljj");
      IDs.push_back("HM_Bin1_400_mjjmin");
      IDs.push_back("HM_Bin1_400_mjjmax");
      IDs.push_back("HM_Bin1_400_met");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_bin1_breakdown",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_bin1_breakdown")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_bin1_breakdown_"+cut ,wt);

      GetHist( label + "ll_highmasssig_bin1_breakdown")->Fill(cut,wt);

    }
  }

  if(cf==13){
    if(GetHist( label + "ll_highmasssig_bin2_breakdown")) {
      GetHist( label + "ll_highmasssig_bin2_breakdown")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_bin2_breakdown_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Bin2_400_inc");
      IDs.push_back("HM_Bin2_400_pt1");
      IDs.push_back("HM_Bin2_400_pt2");
      IDs.push_back("HM_Bin2_400_mlljj");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_bin2_breakdown",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_bin2_breakdown")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_bin2_breakdown_"+cut ,wt);

      GetHist( label + "ll_highmasssig_bin2_breakdown")->Fill(cut,wt);

    }
  }

  if(cf==16){
    if(GetHist( label + "ll_highmasssig_window02_bin2")) {
      GetHist( label + "ll_highmasssig_window02_bin2")->Fill(cut,wt);
      counter(label+"_ll_highmasssig_window02_bin2_"+cut ,wt);
    }
    else{

      vector<TString> IDs;
      IDs.push_back("HM_Window_Bin2_inc");
      IDs.push_back("HM_Window_Bin2_90");
      IDs.push_back("HM_Window_Bin2_100");
      IDs.push_back("HM_Window_Bin2_125");
      IDs.push_back("HM_Window_Bin2_150");
      IDs.push_back("HM_Window_Bin2_200");
      IDs.push_back("HM_Window_Bin2_250");
      IDs.push_back("HM_Window_Bin2_300");
      IDs.push_back("HM_Window_Bin2_400");
      IDs.push_back("HM_Window_Bin2_500");
      IDs.push_back("HM_Window_Bin2_600");
      IDs.push_back("HM_Window_Bin2_700");
      IDs.push_back("HM_Window_Bin2_800");
      IDs.push_back("HM_Window_Bin2_900");
      IDs.push_back("HM_Window_Bin2_1000");
      IDs.push_back("HM_Window_Bin2_1100");
      IDs.push_back("HM_Window_Bin2_1200");
      IDs.push_back("HM_Window_Bin2_1300");
      IDs.push_back("HM_Window_Bin2_1400");
      IDs.push_back("HM_Window_Bin2_1500");

      AnalyzerCore::MakeHistograms( label + "ll_highmasssig_window02_bin2",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

        TString elid = IDs[iid];
        GetHist( label + "ll_highmasssig_window02_bin2")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      counter(label+"_ll_highmasssig_window02_bin2_"+cut ,wt);

      GetHist( label + "ll_highmasssig_window02_bin2")->Fill(cut,wt);

    }
  }





}

void  HNDiLepton::FillEfficiency(TString lab, vector<snu::KJet> jets,  vector<snu::KFatJet> fatjets,float w){

  if(!IsSignal())return;
  vector<TString> muonIDs;
  muonIDs.push_back("MUON_HN_EFF_PT");
  muonIDs.push_back("MUON_HN_EFF_POG");
  muonIDs.push_back("MUON_HN_EFF_DXY");
  muonIDs.push_back("MUON_HN_EFF_DZ");
  muonIDs.push_back("MUON_HN_EFF_dxysig");
  muonIDs.push_back("MUON_HN_EFF_iso");
  muonIDs.push_back("MUON_HN_EFF_onlyiso");
  muonIDs.push_back("MUON_HN_EFF_8TeViso");
  muonIDs.push_back("MUON_HN_EFF_dxysig");
  muonIDs.push_back(_m_tightid);
  muonIDs.push_back("MUON_HN_TIGHT_8TeV");

  FillEventCutFlow(2, "NoCut", w,lab);

  for(unsigned int iid=0; iid < muonIDs.size(); iid++){
    TString muid = muonIDs[iid];

    std::vector<snu::KMuon> muons_eff=GetMuons(muid,false);
   
    if(SameCharge(muons_eff)){

      if(muonIDs[iid] == "MUON_HN_EFF_onlyiso"){
	FillEventCutFlow(2, muid, w,lab);
	continue;
      }
      if(muonIDs[iid] != "MUON_HN_EFF_PT"){
	if(muons_eff[1].Pt() < 15) continue;
	
      }
      if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")) {
	if(muons_eff[0].Pt() < 20 || muons_eff[1].Pt() < 10) continue;
	if(muonIDs[iid] == "MUON_HN_EFF_PT"){
	  FillEventCutFlow(2, "MUON_HN_EFF_HLTMu17", w,lab);

	}
      }
      else{
	TString analysis_trigger_muon="HLT_IsoMu24_v";
	TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
	if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
	  if(muons_eff[0].Pt() < 25 || muons_eff[1].Pt() < 5) continue;
	  if(muonIDs[iid] == "MUON_HN_EFF_PT"){
	    FillEventCutFlow(2, "MUON_HN_EFF_HLTMuISO", w,lab);

	  }
	}
      }

      FillEventCutFlow(2, muid, w,lab);
      if(muonIDs[iid] == "MUON_HN_EFF_PT"){
	if(muons_eff[1].Pt() > 15){
	  FillEventCutFlow(2, "MUON_HN_EFF_PT15", w,lab);
	}
      }
      else if(muonIDs[iid] == _m_tightid) {
	
	if(muons_eff[1].Pt() > 15){
	  if(jets.size() > 1)           FillEventCutFlow(2, "DiJet", w,lab);
	  if(fatjets.size() == 0){
	    if(jets.size() > 1)           FillEventCutFlow(2, "Jet1", w,lab);
	    if(jets.size() == 1)           FillEventCutFlow(2, "Jet2", w,lab);
	  }
	  else  FillEventCutFlow(2, "Jet3", w,lab);
	  vector<int> ijet;
	  float lljj_lm = GetMasses("lljj",muons_eff, jets,fatjets,ijet, true);
	  float jj_lm = GetMasses("jj",muons_eff, jets,fatjets,ijet, true);
	  if(jets.size() > 1)     {
	    if( NBJet(jets) == 0){
	      if(eventbase->GetEvent().PFMET()< 30 && (GetDiLepMass(muons_eff) > 15.) && lljj_lm < 200 && jj_lm < 120) FillEventCutFlow(2, "8TeV_LM", w,lab);
	      if(eventbase->GetEvent().PFMET()< 80 && lljj_lm < 300) FillEventCutFlow(2, "13TeV_LM", w,lab);
	    }
	  }
	}
      }
      else if(muonIDs[iid] == "MUON_HN_TIGHT_8TeV"){
	if(muons_eff[1].Pt() > 15){
          vector<int> ijet;
          float lljj_lm = GetMasses("lljj",muons_eff, jets,fatjets,ijet, true);
          float jj_lm = GetMasses("jj",muons_eff, jets,fatjets,ijet, true);
          if(jets.size() > 1)     {
	    if( NBJet(jets) == 0){
	      if(eventbase->GetEvent().PFMET()< 30 && (GetDiLepMass(muons_eff) > 15.) && lljj_lm < 200 && jj_lm < 120) FillEventCutFlow(2, "8TeV_OLDID_LM", w,lab);
	      if(eventbase->GetEvent().PFMET()< 80 && lljj_lm < 300) FillEventCutFlow(2, "13TeV_OLDID_LM", w,lab);
	    }
	  }
        }

      }
    }
  }
  

}
vector<int>   HNDiLepton::GetTruthJets(bool t_chanel){
  vector<int> i_jets;

  std::vector<snu::KTruth> truthColl= eventbase->GetTruth();

  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {

      int mother_i = eventbase->GetTruth().at(i).IndexMother();

      while(fabs(eventbase->GetTruth().at(mother_i).PdgId()) ==24){
	mother_i = eventbase->GetTruth().at(mother_i).IndexMother();
      }

      if(fabs(eventbase->GetTruth().at(mother_i).PdgId()) == 9900012){
        i_jets.push_back(i);
      }
      if(fabs(eventbase->GetTruth().at(i).PdgId()) == 9900012){
        i_jets.push_back(i);
	
      }
    }
  }
  
  if(t_chanel){
    vector<int> i_jets_t;
    for(unsigned int i = 0; i < truthColl.size(); i++){
      if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {
	
	int mother_i = eventbase->GetTruth().at(i).IndexMother();

	bool Wjet=false;
	for(unsigned int ijet=0; ijet < i_jets.size(); ijet++){
	  if(i_jets[ijet] ==  i) Wjet=true;
	}
	if(Wjet) continue;

	if(eventbase->GetTruth().at(i).GenStatus() == 23) {
	  //TruthPrintOut();
	  i_jets_t.push_back(i);
	}
      }
    }
    return i_jets_t;

  }
  else   return i_jets;
}
vector<int>   HNDiLepton::FillTruthPlots(std::vector<snu::KJet> jets, std::vector<snu::KMuon> muons, TString label){
  
  vector<int> i_jets;

  if(isData) return i_jets;
  if(!label.Contains("inclusive")) return i_jets;
  std::vector<snu::KTruth> truthColl= eventbase->GetTruth();	

  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(eventbase->GetTruth().at(i).IndexMother() <= 0)continue;

    if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {

      int mother_i = eventbase->GetTruth().at(i).IndexMother();

      while(fabs(eventbase->GetTruth().at(mother_i).PdgId()) ==24){
        mother_i = eventbase->GetTruth().at(mother_i).IndexMother();
      }

      if(fabs(eventbase->GetTruth().at(mother_i).PdgId()) == 9900012){
        FillHist(label+"_Truth_Jets_FromW_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1000., 250,"Truth j_{W} P_{T} GeV");
        FillHist(label+"_Truth_Jets_FromW_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100, "Truth j_{W} #eta");
	if(eventbase->GetTruth().at(i).Pt() > 10)        FillHist(label+"_Truth_Jets_FromW_Eta_pt10", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100, "Truth j_{W} #eta");
	if(eventbase->GetTruth().at(i).Pt() > 20)        FillHist(label+"_Truth_Jets_FromW_Eta_pt20", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100, "Truth j_{W} #eta");

	snu::KParticle jtmp=eventbase->GetTruth().at(i);
        for(int ij = 0 ; ij < jets.size() ; ij++){
          if(jtmp.DeltaR(jets[ij]) < 0.1){
            FillHist(label+"_TruthvsReco_Jets_FromW_PtR_ptT", eventbase->GetTruth().at(i).Pt(), jets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 10., 100);
            FillHist(label+"_TruthvsReco_Jets_FromW_ratioPtR_ptT", eventbase->GetTruth().at(i).Pt(), jets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 10., 100);

          }
        }
	
        i_jets.push_back(i);
      }
    }
  }
  
  if(1){
    vector<int> i_jets_t;
    for(unsigned int i = 0; i < truthColl.size(); i++){
      if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {

        int mother_i = eventbase->GetTruth().at(i).IndexMother();

        bool Wjet=false;
        for(unsigned int ijet=0; ijet < i_jets.size(); ijet++){
          if(i_jets[ijet] ==  i) Wjet=true;
        }
        if(Wjet) continue;

        if(eventbase->GetTruth().at(i).GenStatus() == 23) {
	  FillHist(label+"_Truth_Jets_HS_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1000., 250,"Truth j P_{T} GeV");
	  FillHist(label+"_Truth_Jets_HS_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100, "Truth j #eta");

        }
      }
    }
  }


  float dRSum=1.;
  if(i_jets.size() ==2){
    dRSum=dRSum/eventbase->GetTruth().at(i_jets[0]).DeltaR(eventbase->GetTruth().at(i_jets[1]));
    FillHist("Truth_qq_fromW_dR", eventbase->GetTruth().at(i_jets[0]).DeltaR(eventbase->GetTruth().at(i_jets[1])),   1., 0., 5., 25, "Truth #Delta R(q,q)");
  }
  
  int N_vertex = 0;
  bool low_mass=false;
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(eventbase->GetTruth().at(i).IndexMother() <= 0)continue;

    if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) == 9900012){
      if(eventbase->GetTruth().at(i).GenStatus() ==22){
	int mother_i = eventbase->GetTruth().at(i).IndexMother();
	if(fabs(eventbase->GetTruth().at(mother_i).PdgId()) ==24){
	  N_vertex = i;
	  low_mass=true;
	  break;
	}
	else{
	  N_vertex = i;
	  low_mass=false;
          break;

	}
      }
    }
  }

  int index_mu1=-1;
  int index_mu2=-1;
  int n_matched_mu=0;
  bool lep1_fromN=true;
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(eventbase->GetTruth().at(i).IndexMother() <= 0)continue;

    if(fabs(eventbase->GetTruth().at(i).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i).PdgId()) == 13 ) {

      if(eventbase->GetTruth().at(i).GenStatus() ==23){
	if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) != 9900012 && fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) != 13){
	  FillHist(label+"_Truth_Lepton_FromW_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1500., 250,"Truth lep_{W} P_{T}");
	  FillHist(label+"_Truth_Lepton_FromW_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth lep_{W} P_{T}");
	  FillHist(label+"_Truth_Lepton_FromW_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W}  #eta");
	  if(eventbase->GetTruth().at(i).Pt() > 10)           FillHist(label+"_Truth_Lepton_FromW_Eta_pt10", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W}  #eta");
	  if(eventbase->GetTruth().at(i).Pt() > 15)           FillHist(label+"_Truth_Lepton_FromW_Eta_pt15", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W}  #eta");
	  
	  index_mu1=i;
	  float dR_genmu_reco_mu1 (999.);
	  float dR_genmu_reco_mu2 (999.);
	  if(muons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(muons[0]);
	  if(muons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(muons[1]);
	  
	  FillHist(label+"_Truth_Lepton_FromW_eff",0., 1., 0., 2., 2, "Efficiency for truth -> reco l_{W}");
	  if(dR_genmu_reco_mu1 < 0.4 || dR_genmu_reco_mu2 < 0.4) {
	    FillHist(label+"_Truth_Lepton_FromW_eff",1., 1., 0., 2., 2, "Efficiency for truth -> reco l_{W}");
	    n_matched_mu++;
	  }


	  int i_N(0);
	  for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	    if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 9900012 ) {i_N=i2; break;}
	  }
	  int i_l2(0);
	  for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	    if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i2).PdgId()) == 13 ) {
	      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i2).IndexMother()).PdgId()) == 9900012 ) {i_l2=i2; break;}
	    }
	  }

	  float dRl1N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_N).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_N).Phi()),2.));
																
	  FillHist(label+"_Truth_Lepton_FromW_dRN", dRl1N,   1., 0., 5., 25, "Truth #Delta R(lep_{W},N)");

	  float dRl1l2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_l2).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_l2).Phi()),2.));
	  dRSum=dRSum*dRl1l2;
	  FillHist(label+"_Truth_Lepton_FromW_dR_lep2", dRl1l2, 1., 0., 5., 25,"Truth #Delta R(lep_{W},lep_{N})");
	}
      }
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) ==24) {
	index_mu1=i;

	FillHist(label+"_Truth_Lepton_FromW_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1500., 250,"Truth lep_{W} P_{T}");
	FillHist(label+"_Truth_Lepton_FromW_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth lep_{W} P_{T}");
	FillHist(label+"_Truth_Lepton_FromW_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W} #eta");
	if(eventbase->GetTruth().at(i).Pt() > 10)         FillHist(label+"_Truth_Lepton_FromW_Eta_pt10", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W} #eta");
	if(eventbase->GetTruth().at(i).Pt() > 15)         FillHist(label+"_Truth_Lepton_FromW_Eta_pt15", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W} #eta");

	int i_N(0);
	for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	  if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 9900012 ) {i_N=i2; break;}
	}
	int i_l2(0);
	for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	  if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i2).PdgId()) == 13 ) {
	    if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i2).IndexMother()).PdgId()) == 9900012 ) {i_l2=i2; break;}
	  }
	}
	

	float dR_genmu_reco_mu1 (999.);
	float dR_genmu_reco_mu2 (999.);
	if(muons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(muons[0]);
	if(muons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(muons[1]);
	FillHist(label+"_Truth_Lepton_FromW_eff",0., 1., 0., 2., 2, "Efficiency for truth -> reco l_{W}");
	if(dR_genmu_reco_mu1 < 0.4 || dR_genmu_reco_mu2 < 0.4){
	  FillHist(label+"_Truth_Lepton_FromW_eff",1., 1., 0., 2., 2, "Efficiency for truth -> reco l_{W}");
	  n_matched_mu++;
	}
	float dRl1N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_N).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_N).Phi()),2.));
	
	
	FillHist(label+"_Truth_Lepton_FromW_dRN", dRl1N, 1., 0., 5., 25, "Truth #Delta R(lep_{W},N)");
	
	float dRl1l2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_l2).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_l2).Phi()),2.));
	
	dRSum=dRSum*dRl1l2;
	FillHist(label+"_Truth_Lepton_FromW_dR_lep2", dRl1l2, 1., 0., 5., 25, "Truth #Delta R(lep_{W},lep_{2})");
	
      }
    
      
      if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) == 9900012){
	index_mu2=i;

	FillHist(label+"_Truth_Lepton_FromN_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1500., 250,"Truth lep_{N} P_{T} (GeV) ");
	FillHist(label+"_Truth_Lepton_FromN_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100,"Truth lep_{N} P_{T} (GeV) ");
	FillHist(label+"_Truth_Lepton_FromN_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{N} #eta ");
	if(eventbase->GetTruth().at(i).Pt()> 10)        FillHist(label+"_Truth_Lepton_FromN_Eta_pt10", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{N} #eta ");
	if(eventbase->GetTruth().at(i).Pt()> 15)        FillHist(label+"_Truth_Lepton_FromN_Eta_pt15", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{N} #eta ");

	
	float dR_genmu_reco_mu1 (999.);
        float dR_genmu_reco_mu2 (999.);
        if(muons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(muons[0]);
        if(muons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(muons[1]);
        FillHist(label+"_Truth_Lepton_FromN_eff",0., 1., 0., 2., 2, "Efficiency for truth -> reco l_{N}");
        if(dR_genmu_reco_mu1 < 0.4 || dR_genmu_reco_mu2 < 0.4){
          FillHist(label+"_Truth_Lepton_FromN_eff",1., 1., 0., 2., 2, "Efficiency for truth -> reco l_{N}");
	  n_matched_mu++;
	}
	
	float dRl1_l_N = 999.;
	if(muons.size() > 0) dRl1_l_N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - muons[0].Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() -  muons[0].Phi()),2.) ); 
	float dRl2_l_N = 999.;
	if(muons.size() > 1) dRl2_l_N= sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - muons[1].Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() -  muons[1].Phi()),2.) ); 
	
	if(dRl1_l_N < dRl2_l_N) {
	  FillHist(label+"_Truth_Lepton_FromN_dR_recoLepton", dRl1_l_N, 1., 0., 5., 25,"#DeltaR(lep_{N},lep_{reco}) ");
	}
	else{
	  lep1_fromN=false;
	  FillHist(label+"_Truth_Lepton_FromN_dR_recoLepton", dRl2_l_N, 1., 0., 5., 25,"#DeltaR(lep_{N},lep_{reco}) ");
	  
	}
	
	float dRl2j1 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_jets[0]).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_jets[0]).Phi()),2.));
	
	float dRl2j2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_jets[1]).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_jets[1]).Phi()),2.));
	
	
	
	if(dRl2j1 < dRl2j2) FillHist(label+"_Truth_Lepton_FromN_dR_closest_q", dRl2j1, 1., 0., 5., 25,"Truth #DeltaR(lep_{N},q) ");
	if(dRl2j1 > dRl2j2) FillHist(label+"_Truth_Lepton_FromN_dR_closest_q", dRl2j2, 1., 0., 5., 25,"Truth #DeltaR(lep_{N},q) ");
	
	
      }/// end of N mother loop
      
    }// end of lepton loops
  }/// truth loop
  if(muons.size() ==2){
    if(jets.size()>1){
      FillHist(label+"_drX_muon",dRSum, 1., 0., 5., 25,"dR(X) (gen)");
      float drX = muons[0].DeltaR(muons[1])/ jets[0].DeltaR(jets[1]);
      FillHist(label+"_drX_reco_muon", drX, 1., 0., 4., 400,"dR(X) (reco)");

    }
    if(lep1_fromN) FillHist(label+"_Muon_From_N", 0,1.,0., 2., 2, "Reco_index lep_{N}"); 
    else FillHist(label+"_Muon_From_N", 1,1., 0., 2., 2, "Reco_index lep_{N}");
    FillHist(label+"_gen_matched_muon", n_matched_mu, 1., 0., 3., 3,"Number of gen matched muons" );
    FillHist(label+"_lep1_lep2_reco_dR", muons[0].DeltaR(muons[1]),  1., 0., 5., 25,"#DeltaR(lep_{N},lep_{W}) (reco)");
    if (index_mu1 > 0 && index_mu2>0)     FillHist(label+"_lep1_lep2_dR", eventbase->GetTruth().at(index_mu1).DeltaR(eventbase->GetTruth().at(index_mu2)) , 1., 0., 5., 25,"#DeltaR(lep_{N},lep_{W}) (gen)");
    FillHist(label+"_mll", (muons[0]+muons[1]).M() , 1., 0., 150., 150,"m_{ll} (GeV)");
    
    
  }
  return i_jets;
  }


int HNDiLepton::MatchedLeptonJets(std::vector<snu::KJet> jets,std::vector<snu::KFatJet> fatjets, std::vector<snu::KMuon> muons, TString label, vector<int> i_jets){
  
  if(jets.size() == 1 ) {

    snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
    snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
    int matched_index=-1;
    if(jets[0].DeltaR(j1) < 0.5) matched_index=0;
    if(jets[0].DeltaR(j2) < 0.5) matched_index=1;
    
    FillHist("Matched_J_truth_lowmass"+label, matched_index, 1., -1., 2., 3,"Is W*->q(q) reco/truth matched");
  }
  if(jets.size()>=2 &&  muons.size()==2){
    float dijetmass_tmp=999.;
    float dijetmass_tmpHigh=999.;
    float dijetmass=9990000.;
    float dijetmasshigh=9990000.;
    int m=-999;
    int n=-999;
    int mH=-999;
    int nH=-999;
    for(UInt_t emme=0; emme<jets.size(); emme++){
      for(UInt_t enne=1; enne<jets.size(); enne++) {
        if(emme == enne) continue;
        if(muons.size() ==2)dijetmass_tmp = (jets[emme]+jets[enne] + muons[0] + muons[1]).M();
        if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {

          dijetmass = dijetmass_tmp;
          m = emme;
          n = enne;
        }
      }
    }
    for(UInt_t emme=0; emme<jets.size(); emme++){
      for(UInt_t enne=1; enne<jets.size(); enne++) {
        if(emme == enne) continue;
        dijetmass_tmpHigh = (jets[emme]+jets[enne]).M();
        if ( fabs(dijetmass_tmpHigh-80.4) < fabs(dijetmasshigh-80.4) ) {

          dijetmasshigh = dijetmass_tmpHigh;
          mH = emme;
          nH = enne;
        }
      }
    }

    bool match=false;
    snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
    snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
    if(jets[m].DeltaR(j1) < 0.5){
      if(jets[n].DeltaR(j2) < 0.5){
        match=true;
      }
    }
    if(jets[m].DeltaR(j2) < 0.5){
      if(jets[n].DeltaR(j1) < 0.5){
        match=true;

      }
    }
    bool matchH=false;
    if(jets[mH].DeltaR(j1) < 0.5){
      if(jets[nH].DeltaR(j2) < 0.5){
        matchH=true;
      }
    }
    if(jets[mH].DeltaR(j2) < 0.5){
      if(jets[nH].DeltaR(j1) < 0.5){
        matchH=true;

      }
    }
    bool matchHak8=false;
    if(fatjets.size() == 1){
      if(fatjets[0].DeltaR(j1) < 0.8){
	if(fatjets[0].DeltaR(j2) < 0.8){
	  matchHak8=true;
	}
      }
    }
    else if(fatjets.size() == 2){
      if(fatjets[1].DeltaR(j1) < 0.8){
        if(fatjets[1].DeltaR(j2) < 0.8){
          matchHak8=true;
        }
      }
    }
    
    FillHist("Reco_mjj_Low"+label, (jets[m]+jets[n]).M(),  1., 0., 125., 250, "Reco M_{jj} low mass");
    FillHist("Reco_mjj_High"+label, (jets[mH]+jets[nH]).M(),  1., 0., 125., 250,"Reco M_{jj} high mass");
    if(match)  FillHist("Matched_JJ_truth_lowmass"+label, 1, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
    else  FillHist("Matched_JJ_truth_lowmass"+label,0, 1., 0., 2., 2,"Is W*->qq reco/truth matched");

    bool muon_Reco=false;
    if(muons.size() ==2){
      if(muons[0].Pt() > 20 && muons[1].Pt() > 10) muon_Reco=true; 
    }
    if(jets.size()> 1){
      if(match)  FillHist("Matched_recoJJ_truth_lowmass"+label, 1, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
      else   	FillHist("Matched_recoJJ_truth_lowmass"+label,0, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
    }

    if(matchH)  FillHist("Matched_JJ_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
    else  FillHist("Matched_JJ_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
    if(jets.size()> 1){
      if(matchH)  FillHist("Matched_recoJJ_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      else  FillHist("Matched_recoJJ_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
    }

    if(fatjets.size() ==  0){
      if(jets.size()> 1){
	if(matchH)  FillHist("Matched_JJ_ak8_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
	else  FillHist("Matched_JJ_ak8_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      }
    }
    else{
      if(matchHak8)  FillHist("Matched_JJ_ak8_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      else  FillHist("Matched_JJ_ak8_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
    }
    if(muon_Reco){
      if(jets.size()> 1){
	if(match)  FillHist("Matched_recomuon_recoJJ_truth_lowmass"+label, 1, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
	else      FillHist("Matched_recomuon_recoJJ_truth_lowmass"+label,0, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
      }   

      if(matchH)  FillHist("Matched_recomuon_JJ_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      else  FillHist("Matched_recomuon_JJ_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      if(jets.size()> 1){
	if(matchH)  FillHist("Matched_recomuon_recoJJ_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
	else  FillHist("Matched_recomuon_recoJJ_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      }

      if(fatjets.size() ==  0){
	if(jets.size()> 1){
	  if(matchH)  FillHist("Matched_recomuon_JJ_ak8_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
	  else  FillHist("Matched_recomuon_JJ_ak8_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
	}
      }
      else{
	if(matchHak8)  FillHist("Matched_recomuon_JJ_ak8_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
	else  FillHist("Matched_recomuon_JJ_ak8_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");
      }


    }
  

    if(match && matchH) return 3;
    if(match) return 1;
    if(matchH) return 2;
    
  }
  return -1;

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

void HNDiLepton::GetTriggEfficiency(float pt_cut, TString label){

  //ListTriggersAvailable();                                                              
  vector<int> pt1;
  
  /*pt1.push_back(18);
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
  pt1.push_back(25);*/
  pt1.push_back(20);
  pt1.push_back(20);
  pt1.push_back(20);
  pt1.push_back(50);
  pt1.push_back(25);
  pt1.push_back(25);
  vector<int>pt2;
/*  pt2.push_back(10);
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
  pt2.push_back(15);*/
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(5);
  pt2.push_back(5);
  pt2.push_back(5);

  std::vector<TString> lists_triggers;
  /*/  lists_triggers.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
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
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v1");*/

  lists_triggers.push_back("HLT_Mu17_Mu8_SameSign_DZ_v");
  lists_triggers.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  lists_triggers.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
  lists_triggers.push_back("HLT_Mu50_v");
  lists_triggers.push_back("HLT_IsoTkMu24_v");
  lists_triggers.push_back("HLT_IsoMu24_v");

  std::vector<TString> lists_triggers2;
  lists_triggers2.push_back("");
  lists_triggers2.push_back("HLT_Mu50_v");
  lists_triggers2.push_back("HLT_IsoMu24_v");

  std::vector<TString> lists_triggers3;
  lists_triggers3.push_back("HLT_Mu17_Mu8_SameSign_DZ_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
  lists_triggers3.push_back("HLT_Mu50_v");
  lists_triggers3.push_back("HLT_IsoTkMu24_v");
  lists_triggers3.push_back("HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_Mu17_Mu8_SameSign_DZ_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_Mu50_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_IsoTkMu24_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_IsoMu24_v_HLT_Mu50_v");
  lists_triggers3.push_back("HLT_Mu17_Mu8_SameSign_DZ_v_HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v_HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v_HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_Mu50_v_HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_IsoTkMu24_v_HLT_IsoMu24_v");
  lists_triggers3.push_back("HLT_IsoMu24_v_HLT_IsoMu24_v");

  for(unsigned int i=0; i < lists_triggers.size(); i++){
    for(unsigned int j=0; j < lists_triggers2.size(); j++){
      if(!lists_triggers2.at(j).Contains("HLT")) FillTriggerEfficiency(label,lists_triggers.at(i), weight, "denominator_nojet", lists_triggers3 );
      else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "denominator_nojet", lists_triggers3 );
      
    }
  }

  std::vector<snu::KJet> jets=GetJets("JET_HN");
  //std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_POG_TIGHT");
  std::vector<snu::KMuon> muons= GetMuons("MUON_HN_TIGHT");

  if(jets.size() > 0){
    
    for(unsigned int j=0; j < lists_triggers2.size(); j++){
      for(unsigned int i=0; i < lists_triggers.size(); i++){
	if(!lists_triggers2.at(j).Contains("HLT"))             FillTriggerEfficiency(label,lists_triggers.at(i), weight, "denominator", lists_triggers3 );
	else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "denominator", lists_triggers3 );

	if(muons.size() !=2)return;
	
	TString trig=lists_triggers.at(i);
	TString trig2=lists_triggers2.at(j);
	
	bool pass_trig = false;
	int pt_ind = i;
	
	if(j==0) pass_trig = PassTrigger(trig);
	else {
	  pass_trig = PassTrigger(trig) || PassTrigger(trig2);
	  if(PassTrigger(trig) && muons.at(0).Pt() > pt1.at(i) && muons.at(1).Pt() > pt2.at(i) && muons.at(1).Pt() >  pt_cut){
	    pt_ind = i;
	  }
	  else {
	    if(!PassTrigger(trig) && pass_trig&&j==1) pt_ind=3; 
	    if(!PassTrigger(trig) && pass_trig&&j==2) pt_ind=5; 
	  }
	}
	
	if(pass_trig){
	  if(!lists_triggers2.at(j).Contains("HLT"))  FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator",lists_triggers3 );
	  else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator",lists_triggers3 );
	  if(muons.size() ==2) {
	    
	    if(!lists_triggers2.at(j).Contains("HLT"))  FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator_dimuon",lists_triggers3 );
	    else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator_dimuon",lists_triggers3 );
	  
	    
	    if(muons.at(0).Pt() > pt1.at(pt_ind) && muons.at(1).Pt() > pt2.at(pt_ind) && muons.at(1).Pt() >  pt_cut)  {
	      if(!lists_triggers2.at(j).Contains("HLT"))FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator_dimuon_pt",lists_triggers3 );
	      else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator_dimuon_pt",lists_triggers3 );
	    }
		
	  }
	}
      }
    }
  }
}

void HNDiLepton::FillTriggerEfficiency(TString label2, TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label + label2)) {
    GetHist("TriggerEfficiency_"+label + label2)->Fill(cut,weight);

  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label + label2,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label + label2)->GetXaxis()->SetBinLabel(it+1,list.at(it));
    }
  }
  
}



bool HNDiLepton::CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KFatJet> fjets,   std::vector<snu::KJet> alljets, TString name, float w, int mode){

  bool debug=false;
  bool mm=false;
  bool ee=false;

  if(name.Contains("MM")){
    mm=true;
    if(el.size() > 0) return false ;
    if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}

    if(muons.at(0).Pt() < 20.) {if(debug)cout << "Fail pt1 " << endl; return false;}
    if(muons.at(1).Pt() < 5.)  {if(debug)cout << "Fail pt2  " << endl; return false;}
    
    if(isss&&!SameCharge(muons)) {if(debug)cout << "Fail ss " << endl; return false;}

    if(!isss&&SameCharge(muons)) {if(debug)cout << "Fail os  " << endl; return false;}
    snu::KParticle mm = muons.at(0) + muons.at(1);
    if(mm.M()  < _mm_mll_presel_cut) {if(debug)cout << "Fail mee  " << endl; return false;}
  }

  if(mode==0){
    if(jets.size() <2 ) return false;
    
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
    if(name.Contains("Low")){
      if((jets[m] + jets[n] + muons[0] + muons[1]).M() > 300.)  return false;
    }
    
    else{
      if(jj.M() > 150.) {if(debug)cout << "Fail mjj  " << endl; return false;}
      
    }
  }
  
  if(mode==1){
    if(fjets.size() > 0) return false;
    if(fjets.size()==0){
      if(jets.size() < 1) {if(debug)cout << "Fail jets " << endl; return false;}
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
      }
      else{
	
	snu::KParticle jj = jets.at(0);
	
	if(name.Contains("Low")){
	  if((jets[0] + muons[0] + muons[1]).M() > 300.)  return false;
	  if((muons[0] + muons[1]).M()  > 60)  return false;
	}
	
	else{
	  if(jj.M() > 150.) {if(debug)cout << "Fail mjj  " << endl; return false;}
	  
	}
      }
    }
  }
  if(mode==2){
    if(fjets.size() ==0) {if(debug)cout << "Fail mjj  " << endl; return false;}
    if(name.Contains("Low")){      
      return false;
    }
    else{
      if(fjets[0].PrunedMass() > 150.) {if(debug)cout << "Fail mjj  " << endl; return false;}
    }
  }
  
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



