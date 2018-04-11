// $id: RExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNDiElectron.h"


//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to samevallow inheritance for use in LQCore/core classes
ClassImp (HNDiElectron);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiElectron::HNDiElectron() :  AnalyzerCore(),  out_electrons(0) {
  
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
  _m_looseid = "MUON_HN_LOOSEv7_SIP3p5";
  _e_looseid = "ELECTRON_HN_FAKELOOSEv7";



  configure_fakes=true;

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiElectron");

  Message("In HNDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  //InitialiseAnalysis();
  
}


void HNDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  
  if(k_flags.size() > 0){

    if(k_flags[0] == "CutFlow")  functionality = HNDiElectron::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HNDiElectron::OPT;
    else functionality = HNDiElectron::ANALYSIS;
  }


  
  if(  functionality == HNDiElectron::ANALYSIS){
    /// Initialise histograms
    MakeHistograms();  

    //
    // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
    // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
    //
    
    Message("Making clever hists for Z ->ll test code", INFO);
    
    
    vector<TString> labelsE;
    if(!k_isdata || (k_channel=="DoubleEG" ||  k_channel=="SingleElectron")){
      labelsE.push_back("DiEl");
      labelsE.push_back("DiEl_singleEl");
    }
    
  }

  return;
}

void HNDiElectron::DoCutFlow(float w){

}


void HNDiElectron::ExecuteEvents()throw( LQError ){
  

  if(IsSignal())GetTriggEfficiency(5.,"_5");
  if(IsSignal())GetTriggEfficiency(10.,"_10");
  if(IsSignal())GetTriggEfficiency(15.,"_15");

  //bool SBt_JSf = CheckEventComparison("jalmond","SB_fake_mu22107_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FR_syst_cal_fix","jalmond","JS_fake_mu22108_periodC_SKDoubleMuon_hnfake_cat_v8-0-7_FRCalculator_Mu_dxysig_DILEP_fix",false);


    
  if(k_running_nonprompt){
    while(!fake_configured){
      /// SET UP OWN FAKES HISTS --> KEY ////                                                                                                                                                                                                                                    
      std::map<TString, std::pair<std::pair<TString,TString>  ,std::pair<float,TString> > >fake_hists;
      /// ONLY double (TH2D*) are configured at the minute
      fake_hists["fr_electron_central_js"] = std::make_pair(std::make_pair("Electron_Data_v7_FR.root","Electron_Data_v7_FR_Awayjet40") , std::make_pair(70., "TH2D"));
      fake_hists["fr_electron_central"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_central_all_ELECTRON_HN_FAKELOOSEv7_Nvtx_reweight_events_pt_cone_vs_eta_F0") , std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_awayjet_pt_20"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_awayjet_pt_20_all_ELECTRON_HN_FAKELOOSEv7_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_awayjet_pt_30"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_awayjet_pt_30_all_ELECTRON_HN_FAKELOOSEv7_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_awayjet_pt_40"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_awayjet_pt_60_all_ELECTRON_HN_FAKELOOSEv7_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_SIP_12"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_SIP_12_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_SIP_14p5"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_SIP_4p5_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_SIP_8"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_SIP_8_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_dxy_p05"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_dxy_p05_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_dxy_p3"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_dxy_p3_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_dxy_p5"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_dxy_p5_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_dz_p08"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_dz_p08_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_dz_p12"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_dz_p12_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_iso_p5"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_iso_p5_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_iso_p7"] = std::make_pair(std::make_pair("Electron_Data_fake_Rate_syst.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_HN_FAKELOOSESTv7_iso_p7_Nvtx_reweight_events_pt_cone_vs_eta_F" ), std::make_pair(70., "TH2D"));

      fake_hists["FR_ptcone_id_dxy_01"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dxy01_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dxy_02"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dxy02_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dxy_03"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dxy03_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dxy_04"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dxy04_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dxy_05"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dxy05_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dz_04"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dz04_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dz_06"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dz06_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_dz_10"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_dz10_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso05"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso05_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso06"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso06_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso07"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso07_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso08"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso08_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso09"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso09_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_iso10"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_ELECTRON_MVA_TIGHT_iso10_Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_75"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_75__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_77"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_77__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_79"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_79__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_81"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_81__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_83"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_83__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_85"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_85__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_87"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_87__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_89"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_89__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_90"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_90__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_91"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_91__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_92"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_92__Nvtx_reweight_events_pt_cone_vs_eta_SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_75__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_93"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_93__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));
      fake_hists["FR_ptcone_id_mva_94"] = std::make_pair(std::make_pair("Data_driven_FR_syst_DoubleEG_John.root","SingleElectronTrigger_Dijet_Awayjet_40_all_MVA_94__Nvtx_reweight_events_pt_cone_vs_eta_F"), std::make_pair(70., "TH2D"));

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
    
    if(k_flags[0] == "CutFlow")  functionality = HNDiElectron::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HNDiElectron::OPT;
    else functionality = HNDiElectron::ANALYSIS;
  }

  
  if(functionality==HNDiElectron::CUTFLOW){
    DoCutFlow(1.); return;
  }
  
  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;
  _m_channel =   isData ?  (k_channel.Contains("SingleMuon")) : true ;
  _ee_channel =   isData ?  (k_channel.Contains("DoubleEG")) : true ;
  _e_channel =   isData ?  (k_channel.Contains("SingleElectron")) : true ;
  _em_channel =   isData ?  (k_channel.Contains("MuonEG")) : true ;

  TString elid=_e_tightid;
  if(k_running_nonprompt) elid=_e_looseid;
  

  std::vector<snu::KElectron> electrons_fake = GetElectrons(true, true, elid);
  std::vector<snu::KElectron> electrons_cf = GetElectrons(true, false, elid);

  for(unsigned int im=0; im< electrons_cf.size(); im++){
    if(ISCF(electrons_cf[im]) || MCIsCF(electrons_cf[im]) ){
      if(fabs(electrons_cf[im].Eta())< 0.8){

	std::vector<snu::KTruth> truthColl= eventbase->GetTruth();

	cout  <<  "CF el in barrel : " << MCIsCF(electrons_cf[im]) << " : "<<ISCF(electrons_cf[im]) << " " <<  electrons_cf[im].Pt()  << " " << electrons_cf[im].Eta() << electrons_cf[im].Phi() << "" << electrons_cf[im].Charge()<< " : " << electrons_cf[im].GetType() << " : JH " << GetLeptonType(electrons_cf[im], truthColl ) <<endl;
	TruthPrintOut();
	if(ISCF(electrons_cf[im]))FillHist("num_CF_B_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
	FillHist("den_CF_B_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
	
      }
      else{
	if(ISCF(electrons_cf[im]))FillHist("num_CF_E_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
        FillHist("den_CF_E_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);

      }
    }
  }

  if(SameCharge(electrons_cf)){
    if(GetDiLepMass(electrons_cf) < 101 && GetDiLepMass(electrons_cf) > 81.){
      
      if(ISCF(electrons_cf[0]))FillHist("SSZ_num_CF_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
      if(ISCF(electrons_cf[1]))FillHist("SSl_num_CF_pt", electrons_cf.at(1).Pt(), weight, 0., 200., 50);

      FillHist("SSZ_Den_CF_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
      FillHist("SSZ_Den_CF_pt", electrons_cf.at(1).Pt(), weight, 0., 200., 50);

      for(unsigned int im=0; im< electrons_cf.size(); im++){
	if(fabs(electrons_cf[im].Eta())< 0.8){
	  if(ISCF(electrons_cf[im]))FillHist("SSZ_num_CF_B_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
	  FillHist("SSZ_den_CF_B_pt", electrons_cf.at(0).Pt(), weight, 0., 200., 50);
	}
      }


      FillHist("SSEl_All", 1.,1., 0., 2., 2);
      FillHist("SSEl_All_tyoe", electrons_cf.at(0).GetType(), 1., 0., 50., 50);
      FillHist("SSEl_All_tyoe", electrons_cf.at(1).GetType(), 1., 0., 50., 50);
      
      std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
      
      FillHist("SSEl_All_type",GetLeptonType(electrons_cf[0], truthColl ), 1., -6., 16. , 12);
      FillHist("SSEl_All_type",GetLeptonType(electrons_cf[1], truthColl ), 1., -6., 16. , 12);
      if(electrons_cf[0].PassesConvVeto() ){
	FillHist("SSEl_ConVeto", 1., 1., 0., 2., 2);
	FillHist("SSEl_ConVeto_tyoe", electrons_cf.at(0).GetType(), 1., 0., 50., 50);
	FillHist("SSEl_All_type",GetLeptonType(electrons_cf[0], truthColl ), 1., -6., 16. , 12);
      }
      if(electrons_cf[1].PassesConvVeto()){
	FillHist("SSEl_ConVeto", 1., 1., 0., 2., 2);
	FillHist("SSEl_ConVeto_tyoe", electrons_cf.at(1).GetType(), 1., 0., 50., 50);
	FillHist("SSEl_ConvVeto_type",GetLeptonType(electrons_cf[1], truthColl ), 1., -6., 16. , 12);
	
      }
      if(electrons_cf[0].PassesConvVeto()  && electrons_cf[1].PassesConvVeto()){
	FillHist("SSDiEl_ConVeto", 1., 1., 0., 2., 2);
      }
    }
  }


  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",true);
  std::vector<snu::KElectron> electrons_veto = GetElectrons(true, true, "ELECTRON_HN_VETO");

  for(unsigned int im=0; im< electrons_cf.size(); im++){
    std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
    if(electrons_cf[im].MCTruthIndex() < 0) continue;

    if(fabs(electrons_cf[im].Eta())< 0.8){
      FillHist("CF_IB_Den", 1/electrons_cf[im].Pt(),1.,0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_IB_Num", 1/electrons_cf[im].Pt(),1.,0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      FillHist("CF_IBw_Den",  1/electrons_cf[im].Pt(), weight, 0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_IBw_Num",  1/electrons_cf[im].Pt(), weight, 0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");

      FillHist("CF_IB_truth_Den", 1/truthColl.at(electrons_cf[im].MCTruthIndex()).Pt(),1.,0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_IB_truth_Num", 1/truthColl.at(electrons_cf[im].MCTruthIndex()).Pt(),1.,0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      FillHist("CF_IB_truthw_Den",  1/truthColl.at(electrons_cf[im].MCTruthIndex()).Pt(), weight, 0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_IBw_truth_Num",  1/truthColl.at(electrons_cf[im].MCTruthIndex()).Pt(), weight, 0. , 0.05, 100, "IB 1/p_{T} GeV^{-1}");



    }
    else      if(fabs(electrons_cf[im].Eta())< 1.5){
      FillHist("CF_OB_Den",  1/electrons_cf[im].Pt(),  1., 0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_OB_Num",  1/electrons_cf[im].Pt(),  1.,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      FillHist("CF_OBw_Den",1/electrons_cf[im].Pt(),weight,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_OBw_Num",  1/electrons_cf[im].Pt(),weight,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");

      FillHist("CF_OB_truth_Den",  1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),  1., 0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_OB_truth_Num",  1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),  1.,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      FillHist("CF_OBw_truth_Den",1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),weight,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_OBw_truth_Num",  1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),weight,0. , 0.05, 100, "OB 1/p_{T} GeV^{-1}");

    }
    else{
      FillHist("CF_EC_Den", 1/electrons_cf[im].Pt(),1.,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_EC_Num",  1/electrons_cf[im].Pt(),1.,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      FillHist("CF_ECw_Den", 1/electrons_cf[im].Pt(),weight,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_ECw_Num",  1/electrons_cf[im].Pt(),weight,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      
      FillHist("CF_EC_truth_Den", 1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),1.,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_EC_truth_Num",  1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),1.,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      FillHist("CF_ECw_truth_Den", 1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),weight,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
      if(MCIsCF(electrons_cf[im]))      FillHist("CF_ECw_truth_Num",  1/(truthColl.at(electrons_cf[im].MCTruthIndex()).Pt()),weight,0. , 0.05, 100, "EC 1/p_{T} GeV^{-1}");
    }
    
  }
  return;
  
  std::vector<snu::KElectron> electrons;
  if(k_running_nonprompt){
    std::vector<snu::KElectron> electrons_tmp = GetElectrons(false,false,elid);
    std::vector<snu::KElectron> electrons_tmp_nosort;
    for(unsigned int im=0; im< electrons_tmp.size(); im++){
      snu::KElectron el = electrons_tmp[im];
      el.SetPtEtaPhiM(electrons_tmp[im].PTCone(0.3,0.08), electrons_tmp[im].Eta(), electrons_tmp[im].Phi(), electrons_tmp[im].M());
      electrons_tmp_nosort.push_back(el);
    }
    if(electrons_tmp_nosort.size() == 2){
      if(electrons_tmp_nosort[0].Pt() > electrons_tmp_nosort[1].Pt()){
        electrons.push_back(electrons_tmp_nosort[0]);
        electrons.push_back(electrons_tmp_nosort[1]);
      }
      else{
        electrons.push_back(electrons_tmp_nosort[1]);
        electrons.push_back(electrons_tmp_nosort[0]);
      }
    }
  }
  else electrons = GetElectrons(false,false,elid);

  

  if(isData&& !k_running_nonprompt){
    if(SameCharge(electrons_veto)){
      if(electrons_veto.at(0).PFRelIso(0.3) > 0.2){
	FillHist("SS_auxFake_highiso_dxy", electrons_veto.at(0).dxy(), 1., -1., 1., 1000, "dxy");
	FillHist("SS_auxFake_highiso_dz", electrons_veto.at(0).dz(), 1., -1., 1., 1000, "dz");
      }
      if(electrons_veto.at(1).PFRelIso(0.3) > 0.2){
        FillHist("SS_auxFake_highiso_dxy", electrons_veto.at(1).dxy(), 1., -1., 1., 1000, "dxy");
	FillHist("SS_auxFake_highiso_dz", electrons_veto.at(1).dz(), 1., -1., 1., 1000, "dz");
      }
      if(PassID(electrons_veto[0],elid) && electrons_veto[0].Pt() > 20) {
	float mu_pt_corr = electrons_veto.at(1).Pt()*(1+max(0.,(electrons_veto.at(1).PFRelIso(0.3)-0.08))) ; /// will need changing for systematics
	Float_t ptbins[11] = { 5., 12., 15.,20.,25.,30.,35.,45.,  60.,100., 200.};
	if(PassID(electrons_veto[1],"ELECTRON_HN_Loose_HighdXY")){
	  if(fabs(electrons_veto[1].Eta())< 0.9)         FillHist("SS_auxFake_highiso_MVA1", electrons_veto.at(1).MVA(), 1., -1., 1., 100, "MVA");
	  else if(fabs(electrons_veto[1].Eta())< 1.5)   FillHist("SS_auxFake_highiso_MVA2", electrons_veto.at(1).MVA(), 1., -1., 1., 100, "MVA");
	  else if(fabs(electrons_veto[1].Eta())< 2.5)  FillHist("SS_auxFake_highiso_MVA3", electrons_veto.at(1).MVA(), 1., -1., 1., 100, "MVA");
	  FillHist("SS_auxFake_ptcone_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 ) 	FillHist("SS_auxFake_ptcone_bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  else   FillHist("SS_auxFake_ptcone_0bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(fabs(electrons_veto[1].Eta())< 0.9)	FillHist("SS_auxFake_ptcone_IB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(electrons_veto[1].Eta())< 1.5)	FillHist("SS_auxFake_ptcone_OB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(electrons_veto[1].Eta())< 2.5)	FillHist("SS_auxFake_ptcone_EC_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(PassID(electrons_veto[1],"ELECTRON_HN_Loose_HighdXY")){
	    FillHist("SS_auxFake_ptcone_tight",mu_pt_corr, 1., ptbins, 10 );
	    if(fabs(electrons_veto[1].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(electrons_veto[1].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(electrons_veto[1].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	    if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    else   FillHist("SS_auxFake_ptcone_0bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	  }
	}
      }
      if(PassID(electrons_veto[1],elid) && electrons_veto[1].Pt() > 20) {
	float mu_pt_corr = electrons_veto.at(0).Pt()*(1+max(0.,(electrons_veto.at(0).PFRelIso(0.3)-0.08))) ; /// will need changing for systematics                                               
	Float_t ptbins[11] = { 5., 12., 15.,20.,25.,30.,35.,45.,  60.,100., 200.};
	if(PassID(electrons_veto[0],"ELECTRON_HN_Loose_HighdXY")){

          if(fabs(electrons_veto[0].Eta())< 0.9)         FillHist("SS_auxFake_highiso_MVA1", electrons_veto.at(0).MVA(), 1., -1., 1., 100, "MVA");
          else if(fabs(electrons_veto[0].Eta())< 1.5) FillHist("SS_auxFake_highiso_MVA2", electrons_veto.at(0).MVA(), 1., -1., 1., 100, "MVA");
          else if(fabs(electrons_veto[0].Eta())< 2.5)  FillHist("SS_auxFake_highiso_MVA3", electrons_veto.at(0).MVA(), 1., -1., 1., 100, "MVA");

	  FillHist("SS_auxFake_ptcone_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(fabs(electrons_veto[0].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(electrons_veto[0].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_loose",mu_pt_corr, 1., ptbins, 10 );
	  else if(fabs(electrons_veto[0].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_loose",mu_pt_corr, 1., ptbins, 10 );
	  if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  else   FillHist("SS_auxFake_ptcone_0bjet_loose",mu_pt_corr, 1., ptbins, 10 );
	  
	  if(PassID(electrons_veto[0],"ELECTRON_HN_Tight_HighdXY")){
	    FillHist("SS_auxFake_ptcone_tight",mu_pt_corr, 1., ptbins, 10 );
	    if(fabs(electrons_veto[0].Eta())< 0.9)     FillHist("SS_auxFake_ptcone_IB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(electrons_veto[0].Eta())< 1.5)        FillHist("SS_auxFake_ptcone_OB_tight",mu_pt_corr, 1., ptbins, 10 );
	    else if(fabs(electrons_veto[0].Eta())< 2.5)        FillHist("SS_auxFake_ptcone_EC_tight",mu_pt_corr, 1., ptbins, 10 );
	    
	    if(NBJet(GetJets("JET_NOLEPTONVETO", 0., 2.5)) > 0 )         FillHist("SS_auxFake_ptcone_bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	    else   FillHist("SS_auxFake_ptcone_0bjet_tight",mu_pt_corr, 1., ptbins, 10 );
	  }
	}
      }
      
    }
  }
  else{
    
    if(!SameCharge(electrons_veto) && electrons_veto.size() ==2){

      std::vector<double> CFrate, CFweight, sf;
      for(int i=0; i<electrons_veto.size(); i++){
	float rate = GetCFRates(electrons_veto.at(i).Pt(), electrons_veto.at(i).SCEta(), "ELECTRON_HN_TIGHTv4");
	CFweight.push_back( rate / (1.- rate));
      }
      bool apply_sf=1.;
      float syst=0.;

      double cfweight = 0.;
      for(int i=0; i<electrons_veto.size(); i++){
	if(fabs(electrons_veto[i].Eta()) < 1.5 )         cfweight += (1.15) * (CFweight.at(i));
	else  cfweight += (1.05) * (CFweight.at(i));
      }
      
      if(TruthMatched(electrons_veto[0],true) && TruthMatched(electrons_veto[1],true) ){
        if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
          FillHist("Checks_OS_BB_Mass_"  , GetDiLepMass(electrons_veto), cfweight, 0., 200., 200, "m_{ll} GeV");
        }
        if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_OS_EE_Mass_"  , GetDiLepMass(electrons_veto),cfweight, 0., 200., 200, "m_{ll} GeV");
        }
      } 
    }
  
    for(int i=0; i<electrons_veto.size(); i++){
      if(fabs(electrons_veto.at(i).Eta()) < 1.5){
	FillHist("MC_pog_BFR_type_el_loose_",  electrons_veto.at(i).GetType(), 1., 0., 50.,50);
	if(PassID(electrons_veto[i], _e_tightid)) {
	  FillHist("MC_pog_BFR_type_el_tight_",  electrons_veto.at(i).GetType(),  1., 0., 50.,50);
	}
      }
      else{
	FillHist("MC_pog_EFR_type_el_loose_",  electrons_veto.at(i).GetType(), 1., 0., 50.,50);
	if(PassID(electrons_veto[i], _e_tightid)) {
	  FillHist("MC_pog_EFR_type_el_tight_",  electrons_veto.at(i).GetType(),  1., 0., 50.,50);
	}

      }
    }
    
    if(SameCharge(electrons_veto))
      {
	std::vector<snu::KTruth> truthColl= eventbase->GetTruth();     
      for(int i=0; i<electrons_veto.size(); i++){
	if(fabs(electrons_veto.at(i).Eta()) < 1.5){
	  FillHist("SSMC_pog_BFR_type_el_loose_",  electrons_veto.at(i).GetType(), 1., 0., 50.,50);
	  if(PassID(electrons_veto[i], _e_tightid)) {
	    FillHist("SSMC_pog_BFR_type_el_tight_",  electrons_veto.at(i).GetType(),  1., 0., 50.,50);
	  }
	}
	else{
	  FillHist("SSMC_pog_EFR_type_el_loose_",  electrons_veto.at(i).GetType(), 1., 0., 50.,50);
          if(PassID(electrons_veto[i], _e_tightid)) {
            FillHist("SSMC_pog_EFR_type_el_tight_",  electrons_veto.at(i).GetType(),  1., 0., 50.,50);
          }

	}
	
      }
    
    

      if(TruthMatched(electrons_veto[0],true) && TruthMatched(electrons_veto[1],true) ){
	if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
	  FillHist("Checks_SS_BB_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  if(!(GetLeptonType(electrons_veto[0], truthColl ) > 3 || GetLeptonType(electrons_veto[1], truthColl ) > 3)){
	    FillHist("Checks_SS_BB_noIC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  }
	  if(!(electrons_veto[0].GetType() == 40 || electrons_veto[1].GetType() == 40)){
	    FillHist("Checks_SS_BB_noEC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  }
	  else             FillHist("Checks_SS_BB_EC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");

	}
	if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_SS_EE_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  if(!(GetLeptonType(electrons_veto[0], truthColl ) > 3 || GetLeptonType(electrons_veto[1], truthColl ) > 3)){
            FillHist("Checks_SS_EE_noIC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
          }
	  if(!(electrons_veto[0].GetType() == 40 || electrons_veto[1].GetType() == 40)){
	    FillHist("Checks_SS_EE_noEC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  }
	  else 	    FillHist("Checks_SS_EE_EC_Mass_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
        }
      }
      
      if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21 || electrons_veto[1].GetType() ==6 || electrons_veto[1].GetType() == 21){
	if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
	  FillHist("Checks_CF_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_BB_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (Barrel)");
	  if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_BB_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (Barrel)");
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_BB_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200, "MVA (Barrel)");
	  if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_BB_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200, "MVA (Barrel)");
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_BB_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (Barrel)");
	  if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_BB_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (Barrel)");
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_BB_misshit_"  , electrons_veto.at(0).MissingHits(), 	  weight,  0., 5., 5, "Higs_{miss} (Barrel)");
	  if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_BB_misshit_"  , electrons_veto.at(1).MissingHits(), 	  weight,  0., 5., 5, "Higs_{miss} (Barrel)");
	}

	if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_CF_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_EE_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100,  "I_{rel} (EC)");
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_EE_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (EC)");
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_EE_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200, "MVA (EC)");
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_EE_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200 , "MVA (EC)");
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_EE_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (EC)");
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_EE_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (EC)");
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_CF_EE_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5, "Higs_{miss} (EC)");
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_CF_EE_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5, "Higs_{miss} (EC)");
	}
      }
      
      if(electrons_veto[0].GetType() == 1 || electrons_veto[1].GetType() ==1){
	if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
          FillHist("Checks_Z_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  if(electrons_veto[0].GetType() == 1 ){
	    FillHist("Checks_Z_BB_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (Barrel)");
	    FillHist("Checks_Z_BB_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200, "MVA (Barrel)");
	    FillHist("Checks_Z_BB_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (Barrel)");
	    FillHist("Checks_Z_BB_misshit_"  , electrons_veto.at(0).MissingHits(),        weight,  0., 5., 5, "Higs_{miss} (Barrel)");
	  }
	  if(electrons_veto[1].GetType() == 1 ){
            FillHist("Checks_Z_BB_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (Barrel)");
            FillHist("Checks_Z_BB_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200, "MVA (Barrel)");
            FillHist("Checks_Z_BB_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (Barrel)");
            FillHist("Checks_Z_BB_misshit_"  , electrons_veto.at(1).MissingHits(),        weight,  0., 5., 5, "Higs_{miss} (Barrel)");
          }

	}
	  
        if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_Z_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
	  if(electrons_veto[0].GetType() == 1 ){
	    FillHist("Checks_Z_EE_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100,  "I_{rel} (EC)");
	    FillHist("Checks_Z_EE_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200, "MVA (EC)");
	    FillHist("Checks_Z_EE_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (EC)");
	    FillHist("Checks_Z_EE_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5, "Higs_{miss} (EC)");
	  }
	  if(electrons_veto[1].GetType() == 1 ){
            FillHist("Checks_Z_EE_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100, "I_{rel} (EC)");
            FillHist("Checks_Z_EE_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200 , "MVA (EC)");
            FillHist("Checks_Z_EE_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400, "d_{xy} (EC)");
            FillHist("Checks_Z_EE_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5, "Higs_{miss} (EC)");
          }
	}
      }

      if((electrons_veto[0].GetType() == 40 && GetLeptonType(electrons_veto[1], truthColl ) > 0 )|| (electrons_veto[1].GetType() ==40 && GetLeptonType(electrons_veto[0], truthColl ) > 0)){

	if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
          FillHist("Checks_ExC_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_BB_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_BB_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_BB_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_BB_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_BB_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_BB_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_BB_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_BB_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5);

	}
	
        if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_ExC_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
	  if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_EE_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_EE_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_EE_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_EE_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_EE_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_EE_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400);
          if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21)FillHist("Checks_ExC_EE_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5);
          if(electrons_veto[1].GetType() == 6 || electrons_veto[1].GetType() == 21)FillHist("Checks_ExC_EE_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5);

        }
      }
      
      if(GetLeptonType(electrons_veto[0], truthColl ) > 0 && GetLeptonType(electrons_veto[1], truthColl ) > 0 ){
	if(GetLeptonType(electrons_veto[0], truthColl ) > 3 || GetLeptonType(electrons_veto[1], truthColl ) > 3 ){
	  if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
	    FillHist("Checks_IcC_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_EE_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_EE_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_EE_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_EE_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_EE_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_EE_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_EE_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_EE_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5);
	  }

	  if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
	    FillHist("Checks_IcC_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_BB_iso_"   , electrons_veto.at(0).PFRelIso(0.3), weight, 0., 1., 100);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_BB_iso_"   , electrons_veto.at(1).PFRelIso(0.3), weight, 0., 1., 100);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_BB_mva_"   , electrons_veto.at(0).MVA() , weight, -1., 1., 200);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_BB_mva_"   , electrons_veto.at(1).MVA() , weight, -1., 1., 200);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_BB_dxy_"   , electrons_veto.at(0).dxy()  , weight, -0.2, 0.2, 400);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_BB_dxy_"   , electrons_veto.at(1).dxy()  , weight, -0.2, 0.2, 400);
	    if(GetLeptonType(electrons_veto[0], truthColl ) > 3)FillHist("Checks_IcC_BB_misshit_"  , electrons_veto.at(0).MissingHits(),         weight,  0., 5., 5);
	    if(GetLeptonType(electrons_veto[1], truthColl ) > 3)FillHist("Checks_IcC_BB_misshit_"  , electrons_veto.at(1).MissingHits(),         weight,  0., 5., 5);

	  }
	}
      }
      

    }
    else{
      if(electrons_veto.size() ==2){
	if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
	  FillHist("Checks_OS_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	}
	if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
          FillHist("Checks_OS_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
        }
	if(electrons_veto[0].GetType() == 6 || electrons_veto[0].GetType() == 21 || electrons_veto[1].GetType() ==6 || electrons_veto[1].GetType() == 21){
	  if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
	    FillHist("Checks_OSCF_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  }
	  if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
            FillHist("Checks_OSCF_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
	  }
	}
	if(electrons_veto[0].GetType() == 40 || electrons_veto[1].GetType() == 40 ){
	  if(fabs(electrons_veto[0].Eta()) < 1.5  && fabs(electrons_veto[1].Eta()) < 1.5){
            FillHist("Checks_OSExC_Mass_BB_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
          }
          if(fabs(electrons_veto[0].Eta()) > 1.5  && fabs(electrons_veto[1].Eta()) > 1.5){
            FillHist("Checks_OSExC_Mass_EE_"  , GetDiLepMass(electrons_veto), weight, 0., 200., 200, "m_{ll} GeV");
          }
	}

      }
    }
  }


  std::vector<snu::KElectron> electrons8TeV = GetElectrons(false, false, "ELECTRON_HN_TIGHT_8TeV",false);
  std::vector<snu::KElectron> electronsv2 = GetElectrons(false, false, "ELECTRON_HN_TIGHTv4_v2");
  std::vector<snu::KElectron> electronsv3 = GetElectrons(false, false, "ELECTRON_HN_TIGHTv4_v3");

  std::vector<snu::KElectron> electrons_notc =  GetElectrons(false, false, "ELECTRON_HN_TIGHT_NOTIGHTCHARGE",false);
  std::vector<snu::KElectron> electrons_noconv =  GetElectrons(false, false, "ELECTRON_HN_TIGHT_NOCONVVETO",false);
  std::vector<snu::KElectron> electrons_mvatight = GetElectrons(false, false, "ELECTRON_MVA_TIGHT",false);
  std::vector<snu::KElectron> electrons_pogtight = GetElectrons(false, false, "ELECTRON_POG_TIGHT",false);
  std::vector<snu::KElectron> electrons_pogmedium = GetElectrons(false, false, "ELECTRON_POG_MEDIUM",false);
  std::vector<snu::KElectron> electrons_pogmediumall = GetElectrons(true, false, "ELECTRON_NOCUT",false);
  std::vector<snu::KElectron> electrons_pogtight_cc = GetElectrons(false, false, "ELECTRON_POG_TIGHT_CC",false);
  std::vector<snu::KElectron> electrons_pogmedium_cc = GetElectrons(false, false, "ELECTRON_POG_MEDIUM_CC",false);
  std::vector<snu::KElectron> electrons_hn_looseip = GetElectrons(false, false, "ELECTRON_HN_TIGHT_LOOSEIP",false);
  std::vector<snu::KElectron> electrons_hn_looseiso = GetElectrons(false, false, "ELECTRON_HN_TIGHT_LOOSEISO",false);
  std::vector<snu::KElectron> electrons_hn_looseip2 = GetElectrons(false, false, "ELECTRON_HN_TIGHT_LOOSEIP2",false);
  std::vector<snu::KElectron> electrons_hn_loosemva = GetElectrons(false, false, "ELECTRON_HN_TIGHT_LOOSEMVA",false);

  /// Set up electrons                                                                                                                                        


  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO", 20., 2.5);
  std::vector<snu::KJet> alljets_10 = GetJetsWFT("JET_NOLEPTONVETO", "FATJET_HN_tau06",10., 2.5);
  std::vector<snu::KJet> tchanjets = GetJetsWFT("JET_HN_TChannel","FATJET_HN_tau06",20., 5.);
  
  std::vector<snu::KJet>  jets_20 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",20., 2.5);
  std::vector<snu::KJet>  jets_all20 =  GetJets("JET_HN", 20., 2.5);
  std::vector<snu::KJet>  jets_25 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",25., 2.7);
  std::vector<snu::KJet>  jets_30 = GetJetsWFT("JET_HN", "FATJET_HN_tau06",30., 2.7);
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN_tau06");
  std::vector<snu::KFatJet> fatjetcoll_tau21_045 = GetFatJets("FATJET_HN_tau045");
  std::vector<snu::KFatJet> fatjetcoll_notau21 = GetFatJets("FATJET_HN");
  
  
  /// correct L1 JEC and apply JMR

  std::vector<snu::KFatJet> fatjetcoll_updated = GetCorrectedFatJet(fatjetcoll);
  std::vector<snu::KFatJet> fatjetcoll_tau21_045_updated = GetCorrectedFatJet(fatjetcoll_tau21_045);
  std::vector<snu::KFatJet> fatjetcoll_notau21_updated = GetCorrectedFatJet(fatjetcoll_notau21);
  CorrectedMETJMR(fatjetcoll_updated, jets_20);

  vector<int> ijets;  
  
  if(functionality==HNDiElectron::OPT){
    return;
  }

  if(functionality==HNDiElectron::ANALYSIS){
    
    float mm_weight=weight;
    float ee_weight=weight;
    float em_weight=weight;
    
    std::vector<TString> triggerlist_DiElectron;
    std::vector<TString> triggerlist_DiMuon_singleLep, triggerlist_DiElectron_singleLep;

    triggerlist_DiElectron.clear();


    triggerlist_DiElectron.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
    triggerlist_DiElectron_singleLep.push_back("HLT_Ele27_WPTight_Gsf_v");

    int nbjet_m=0;
    for(unsigned int ij=0; ij <alljets.size(); ij++){
      if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium)) nbjet_m++;
    }


    FillEfficiency("DiElectron_hn", jets_all20,fatjetcoll_updated , ee_weight*WeightByTrigger(triggerlist_DiElectron[0],TargetLumi));
    if(_ee_channel)RunEE(0,"DiElectron_hn",   electrons, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    

    FillMCFakes("DiElectron_fake2l", muons_veto, alljets,   jets_all20, fatjetcoll_updated  , triggerlist_DiElectron ,PreselWeight(mm_weight,electrons_fake, "DiElectron_fake2l", PassTriggerOR(triggerlist_DiElectron)), "ELECTRON_HN_FAKELOOSEv7",_e_tightid);

    FillMCFakes("DiElectron_fake2l_8", muons_veto, alljets,   jets_all20, fatjetcoll_updated  , triggerlist_DiElectron ,PreselWeight(mm_weight,electrons_fake, "DiElectron_fake2l" , PassTriggerOR(triggerlist_DiElectron)), "ELECTRON_HN_LOOSE_8TeV","ELECTRON_HN_TIGHT_8TeV");

    
    FillMCFakes("DiElectron_fake2l_8v2", muons_veto, alljets,   jets_all20, fatjetcoll_updated  , triggerlist_DiElectron ,PreselWeight(mm_weight,electrons_fake, "DiElectron_fake2l" , PassTriggerOR(triggerlist_DiElectron)), "ELECTRON_HN_LOOSE2_8TeV","ELECTRON_HN_TIGHT2_8TeV");
																     

    return;
    //if(_ee_channel)RunEE(0,"DiElectron_hnv2",   electronsv2, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    //if(_ee_channel)RunEE(0,"DiElectron_hnv3",   electronsv3, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(SameCharge(electrons)){
      if(electrons[0].Charge() > 0) RunEE(0,"DiElectron_hn_pp",   electrons, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
      else RunEE(0,"DiElectron_hn_mm",   electrons, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    }
    //if(_ee_channel)RunEE(0,"DiElectron_hnor",   electrons, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    //if(_e_channel)RunEE(0,"DiElectron_hnor",   electrons, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron_singleLep ,30.      , 10.);    


    /*if(_ee_channel)RunEE(0,"DiElectron_hn_notightcharge",   electrons_notc, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_hn_noconvveto",   electrons_noconv, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_hn_looseiso",   electrons_hn_looseiso, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_hn_looseip",   electrons_hn_looseip, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_hn_looseip2",   electrons_hn_looseip2, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_hn_loosemva",   electrons_hn_loosemva, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_mvatight",   electrons_mvatight, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_pogtight",   electrons_pogtight, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_pogmedium",   electrons_pogmedium, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);    
    if(_ee_channel)RunEE(0,"DiElectron_pogtight_cc",   electrons_pogtight_cc, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    if(_ee_channel)RunEE(0,"DiElectron_pogtight_hn",   electronsv3, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    if(_ee_channel)RunEE(0,"DiElectron_pogmedium_cc",   electrons_pogmedium_cc, electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    if(_ee_channel)RunEE(0,"DiElectron_pogmedium_all_cc", electrons_pogmediumall , electrons_veto, muons_veto,alljets,   jets_all20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    */

    if(IsSignal()){
      vector<int>  ijet_list =           FillTruthPlots(jets_all20, electrons, "DiElectron_hn");
    }

    
    
    if(fatjetcoll_updated.size() ==0) {
      RunEE(1,"DiElectron_NoFAT",      electrons, electrons_veto,muons_veto, alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    }
    else{
      RunEE(2,"DiElectron_FAT",      electrons , electrons_veto,  muons_veto, alljets,   jets_20, fatjetcoll_updated     ,  tchanjets,  ee_weight, triggerlist_DiElectron ,25.      , 15.);
    }


    if(!isData){



      FillMCFakes("DiElectron_fake2l_8", muons_veto, alljets,   jets_all20, fatjetcoll_updated  , triggerlist_DiElectron ,PreselWeight(mm_weight,electrons_fake, "DiElectron_fake2l", PassTriggerOR(triggerlist_DiElectron)), "ELECTRON_HN_LOOSE_8TeV","ELECTRON_HN_TIGHT_8TeV");

    }
    FillPreselection(2,"DiElectron_fake2l",      electrons_fake,electrons_veto,muons_veto,alljets,   jets_all20, fatjetcoll_updated  ,  PreselWeight(mm_weight,electrons_fake, "DiElectron_fake2l",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron ,25.      , 15.);
    FillPreselection(1,"DiElectron_fake1l",      electrons_fake,electrons_veto,muons_veto,alljets,   jets_all20, fatjetcoll_updated  ,  PreselWeight(mm_weight,electrons_fake, "DiElectron_fake1l",PassTriggerOR(triggerlist_DiElectron)), triggerlist_DiElectron ,25.      , 15.);
    
    FillLowMassBins(false, 0, "DiElectron_HN",  electrons, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)	;
    

    if(electrons.size() ==2 ){
      if( (fabs(electrons[0].Eta()) < 1.5) && (fabs(electrons[1].Eta()) < 1.5)){
	FillLowMassBins(false, 0, "DiElectron_HN_BBEB",  electrons, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;
																			  
      }
      else{ 
	
	FillLowMassBins(false, 0, "DiElectron_HN_EE",  electrons, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;	
	
      }
    }


    if(electrons_hn_looseip.size() ==2 ){
      if( (fabs(electrons_hn_looseip[0].Eta()) < 1.5) && (fabs(electrons_hn_looseip[1].Eta()) < 1.5)){
        FillLowMassBins(false, 0, "DiElectron_HN_IP_BBEB",  electrons_hn_looseip, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons_hn_looseip, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;
	
      }
      else{
	
        FillLowMassBins(false, 0, "DiElectron_HN_IP_EE",  electrons_hn_looseip, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons_hn_looseip, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;
      }
    }

    if(electrons_hn_loosemva.size() ==2 ){
      if( (fabs(electrons_hn_loosemva[0].Eta()) < 1.5) && (fabs(electrons_hn_loosemva[1].Eta()) < 1.5)){
        FillLowMassBins(false, 0, "DiElectron_HN_MVA_BBEB",  electrons_hn_loosemva, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons_hn_loosemva, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;
			

      }
      else{
	
        FillLowMassBins(false, 0, "DiElectron_HN_MVA_EE",  electrons_hn_loosemva, electrons_veto ,muons_veto,  alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons_hn_loosemva, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15.)   ;
			
      }
    }    

    
    FillHighMassBins(false, 0, "DiElectron_HN",  electrons ,electrons_veto,muons_veto, alljets,jets_all20,  fatjetcoll_updated,nbjet_m, PreselWeight(mm_weight,electrons, "DiElectron_HN",PassTriggerOR(triggerlist_DiElectron)) , triggerlist_DiElectron, 25., 15. );

    //    GetOptimisationID(electrons_veto, muons_veto, alljets,jets_all20,  fatjetcoll_updated,nbjet_m, mm_weight,  triggerlist_DiElectron, 25, 15);
    

  }

}


float HNDiElectron::EEWeight(std::vector<snu::KElectron> electrons,TString id){
  
  if(isData) return 1.;
  
  double mc_weight = mcdata_correction->ElectronScaleFactor(id, electrons, 0);
  // For test
  // if(mc_weight< 0.8) mc_weight=0.8;
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

float HNDiElectron::EMWeight(std::vector<snu::KElectron> electrons,std::vector<snu::KMuon> muons,TString idel, TString idmu){
  
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


void HNDiElectron::RunEE(int mode , TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ee_weight ,vector<TString> ee_trig, float pt1, float pt2){

  vector<snu::KMuon> mu;
  RunLL(mode,"EE",label, mu, muons, electrons, electrons_veto, alljets, jets, fatjets, tjets,ee_weight,  ee_trig, pt1, pt2);
}


void HNDiElectron::RunLL(int mode,TString channel , TString label, vector<snu::KMuon> muons, vector<snu::KMuon> muons_veto, vector<snu::KElectron> electrons,vector<snu::KElectron> electrons_veto, vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<snu::KJet> tjets,float ll_weight ,vector<TString> ll_trig, float pt1, float pt2){
  

  bool samecharge=true;
  bool FillAll=true;
  if (label.Contains("OS")) samecharge=false;
  if (label.Contains("TMP")) FillAll=false;
  
  if(mode==1 && fatjets.size() > 0) return;
  if(mode==2 && fatjets.size() == 0) return;


  TString elid=_e_tightid;
  if(k_running_nonprompt) {
    elid=_e_looseid;
  }
  
  bool cut2_trig = PassTriggerOR(ll_trig);

  FillEventCutFlow(4,"NoCut",ll_weight*WeightByTrigger(ll_trig[0],TargetLumi),label );
  FillHist(label+"_StatBin", 1, 1, 0., 2, 2);

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :   

  FillEventCutFlow(4,"EventCleaning",ll_weight*WeightByTrigger(ll_trig[0],TargetLumi),label );            

  //// DIMUON 
  /// define event variables                                                                                                                                                  
  snu::KParticle ll; 
  if(electrons.size() ==2) ll= electrons[0] + electrons[1];

  float llmass=ll.M();
  //// DIELECTRON --- B JETS
  int nbjet_l=0;
  int nbjet_m=0;
  int nbjet_t=0;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Loose))  nbjet_l++;
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium)) nbjet_m++;
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Tight))  nbjet_t++;
  }


  /// DIELECTRON --- ST + HT
  float ST (0.);
  if(electrons.size() ==2)ST= electrons[0].Pt() + electrons[1].Pt();
  float HT=0.;
  for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
  if(mode==2){
    for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
  }
  ST+=eventbase->GetEvent().PFMET();
  

  /// DIELECTRON --- MET
  
  //// MET is corrected already for rochester 
  float met = eventbase->GetEvent().PFMET();
  float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;


  /// DIELECTRON ---   cut definitions
  
  bool cut1_dilep =  (electrons.size()==2 && (electrons[1].Pt() > pt2 && electrons[0].Pt() > pt1 ));
  if(k_running_nonprompt)cut1_dilep =  (electrons.size()==2 && (electrons[1].PTCone(0.3,0.08) > pt2 && electrons[0].PTCone(0.3,0.08) > pt1 ));
  

  if(!isData){
    std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
    if(SameCharge(electrons)){

      FillHist("MET_"  +label,0., ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 2., 2);
      if(eventbase->GetEvent().PFMET() < 30)   FillHist("MET_"  +label,1., ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 2., 2);

    for(unsigned int iel=0; iel < electrons.size(); iel++){
      
      if(GetLeptonType(electrons[iel], truthColl ) == 4 || GetLeptonType(electrons[iel], truthColl ) == 5){
	FillHist("ConvIc_missingHits_" +label,  electrons[iel].MissingHits()  , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 5.,5);
	FillHist("ConvIc_vertex_X_" +label,  electrons[iel].TrkVx() - eventbase->GetEvent().VertexX(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
	FillHist("ConvIc_vertex_Y_" +label,  electrons[iel].TrkVy() - eventbase->GetEvent().VertexY(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
	FillHist("ConvIc_vertex_Z_" +label,  electrons[iel].TrkVz() - eventbase->GetEvent().VertexZ(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
      }
      if(GetLeptonType(electrons[iel], truthColl ) == -5 || GetLeptonType(electrons[iel], truthColl ) == -6){
        FillHist("ConvEx_missingHits_" +label,  electrons[iel].MissingHits()  , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 5.,5);
        FillHist("ConvEx_vertex_X_" +label,  electrons[iel].TrkVx() - eventbase->GetEvent().VertexX(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
        FillHist("ConvEx_vertex_Y_" +label,  electrons[iel].TrkVy() - eventbase->GetEvent().VertexY(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
        FillHist("ConvEx_vertex_Z_" +label,  electrons[iel].TrkVz() - eventbase->GetEvent().VertexZ(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
      }

      if(electrons[iel].GetType()==22){
	FillHist("Type22_missingHits_" +label,  electrons[iel].MissingHits()  , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 5.,5);
	FillHist("Type22_vertex_X_" +label,  electrons[iel].TrkVx() - eventbase->GetEvent().VertexX(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
        FillHist("Type22_vertex_Y_" +label,  electrons[iel].TrkVy() - eventbase->GetEvent().VertexY(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
        FillHist("Type22_vertex_Z_" +label,  electrons[iel].TrkVz() - eventbase->GetEvent().VertexZ(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
      }
      if(electrons[iel].GetType()==7){
	FillHist("Type7_missingHits_" +label,  electrons[iel].MissingHits()  , ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0., 5.,5);
        FillHist("Type7_vertex_X_" +label,  electrons[iel].TrkVx() - eventbase->GetEvent().VertexX(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
	FillHist("Type7_vertex_Y_" +label,  electrons[iel].TrkVy() - eventbase->GetEvent().VertexY(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
        FillHist("Type7_vertex_Z_" +label,  electrons[iel].TrkVz() - eventbase->GetEvent().VertexZ(), ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -0.1, 0.1,100);
      }

      FillHist(label+"el_type2_loose",  GetLeptonType(electrons[iel], truthColl ) , 1., -6.,6.,12);
      FillHist(label+"el_type_loose", electrons[iel].GetType(), 1., 0., 40., 40);
      
      if(PassID(electrons[iel], _e_tightid)) {
	FillHist(label+"el_type2_tight",  GetLeptonType(electrons[iel], truthColl ) ,1., -6.,6.,12);
	FillHist(label+"el_type_tight", electrons[iel].GetType(), 1., 0., 40., 40);
      }
    }
    }
  }
  
  if(cut1_dilep){

    TString elid=_e_tightid;
    if(k_running_nonprompt) elid=_e_looseid;

   
    /// weight CF events 

    ll_weight *= EEWeight(electrons,elid);
    FillEventCutFlow(4,"DiLep",ll_weight*WeightByTrigger(ll_trig[0], TargetLumi) ,label);

    if(ll_trig[0].Contains("Gsf")){
      std::vector<TString> triggerlist_DiElectron;
      triggerlist_DiElectron.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
      if(PassTriggerOR(triggerlist_DiElectron)) return;
    }
    if(!cut2_trig) return;
    

    //// correct weight to include trigger lumi
    if(!isData)  ll_weight*= WeightByTrigger(ll_trig[0], TargetLumi) ;

    FillEventCutFlow(4,"Trigger",ll_weight,label);
    if(ll_trig[0].Contains("Gsf")){
      FillEventCutFlow(4,"TriggerEle27",ll_weight,label);
    }
    else{
      FillEventCutFlow(4,"TriggerEle23",ll_weight,label);
    }
    counter("Trigger",ll_weight);
    
    bool cut3_lepveto = (muons_veto.size()>0);
    
    if(cut3_lepveto) return;

    counter("LepVeto",ll_weight);
	
    FillEventCutFlow(4,"LepVeto",ll_weight,label);
	
    vector<int> ijets;  
    
    histtype llhist = sighist_ee;

    bool  cut4_ss = (SameCharge(electrons));
    /*    if(ichannel == 1) {
      ll_weight              *= WeightCFEvent(electrons, k_running_chargeflip);
      cut4_ss = (ll_weight !=  0.);
      }*/
    
    if(fabs(GetDiLepMass(electrons) - 90.) < 10.) {
      FillCLHist(llhist, label+"SSLL_Z", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);       

      if(IsExternalConversion(electrons[0]) || IsExternalConversion(electrons[1]) )
	FillCLHist(llhist, label+"SSLL_ExConvZ", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);

      if(IsInternalConversion(electrons[0]) ||IsInternalConversion(electrons[1]))
	FillCLHist(llhist, label+"SSLL_IntConvZ", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);

    }
    
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
	  
	  ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",0);
	  ll_weight_sf=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",1);
	  ll_weight_df=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",2);
	  if(label=="DiElectron_SIP")
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_sip_central",0);
	  
	  
	  if(label=="DiElectron_8TeV")
	    ll_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_8TeV_central",0);
	  
	  if(PassID(electrons[0], "ELECTRON_HN_TIGHT") && PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_TT_Preselection", ll_weight);
	  if(PassID(electrons[0], "ELECTRON_HN_TIGHT") && PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_TT_Preselection_now", 1.);
	  if(PassID(electrons[0], "ELECTRON_HN_TIGHT") && !PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_TL_Preselection", ll_weight);
	  if(PassID(electrons[0], "ELECTRON_HN_TIGHT") && !PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_TL_Preselection_now", 1.);
	  if(!PassID(electrons[0], "ELECTRON_HN_TIGHT") && PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_LT_Preselection", ll_weight);
	  if(!PassID(electrons[0], "ELECTRON_HN_TIGHT") && PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_LT_Preselection_now", 1.);
	  if(!PassID(electrons[0], "ELECTRON_HN_TIGHT") && !PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_LL_Preselection", ll_weight);
	  if(!PassID(electrons[0], "ELECTRON_HN_TIGHT") && !PassID(electrons[1] , "ELECTRON_HN_TIGHT"))counter("SSLL_LL_Preselection_now", 1.);

	  
	}	
	counter("SSLL_Preselection", ll_weight);
       
	if(jets.size() == 0){

	  if(electrons[0].DeltaR(electrons[1]) > 2.5){
	    FillCLHist(llhist, label+"SSLL_0JetdRll", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);                               
	    if(!(electrons[0].GetType() == 40 || electrons[1].GetType() == 40 )){
	      FillCLHist(llhist, label+"SSLL_0JetdRll_noExC", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	    }

	  }
	}

	///if(FillAll)FillCLHist(llhist, label+"SSLL_nolepveto", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);

	vector<int> ti_jets;
	
	/*if(IsSignal()){
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
	  
	  
	  vector<int>  ijet_list =          GetTruthJets();
	  
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
	*/
	
	bool cut6_lepveto = (electrons_veto.size()>2);


	if(cut6_lepveto) return;


	bool signal_like=false;
        if(jets.size() > 1){
	  if(!nbjet_m && eventbase->GetEvent().PFMET() < 50) signal_like=true;
	}
	else{
	  if(GetDiLepMass(electrons) < 80) signal_like=true;
	}
	if(!isData)signal_like=false;
	if(fabs(GetDiLepMass(electrons) - 90.) < 10.) {
	  FillHist(label+"_Zelectron_eta_presel", electrons[0].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30);
          FillHist(label+"_Zelectron_eta_presel", electrons[1].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30);
	  FillHist(label+"_Zelectron_pt_presel", electrons[0].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200);
	  FillHist(label+"_Zelectron_pt_presel", electrons[1].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200);

	}
	else{
	  if(!signal_like){
	    FillHist(label+"_electron_eta_presel", electrons[0].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30); 
	    FillHist(label+"_electron_eta_presel", electrons[1].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30); 
	    FillHist(label+"_electron_pt_presel", electrons[0].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200); 
	    FillHist(label+"_electron_pt_presel", electrons[1].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200); 
	    
	    
	    if(jets.size() > 1){
	      FillHist(label+"_electron_eta_jj_presel", electrons[0].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30);
	      FillHist(label+"_electron_eta_jj_presel", electrons[1].Eta(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), -3., 3., 30);
	      FillHist(label+"_electron_pt_jj_presel", electrons[0].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200);
	      FillHist(label+"_electron_pt_jj_presel", electrons[1].Pt(),  ll_weight*WeightByTrigger(ll_trig[0], TargetLumi), 0.,  1000.,200);
	      
	    }
	  }
	}
	

	if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	bool remove_etareg=false;
	bool remove_etareg_pt=false;
	bool remove_etareg_ptless50=false;
	if(electrons[1].Pt()<  20 && fabs(electrons[1].SCEta()) > 1.5) remove_etareg_pt=true;
	if((electrons[1].Pt()<  50 && fabs(electrons[1].SCEta()) > 1.5) || (electrons[0].Pt()<  50 && fabs(electrons[0].SCEta()) > 1.5)) remove_etareg_ptless50=true;

	if(fabs(electrons[1].SCEta())  > 1.5 || fabs(electrons[0].SCEta()) > 1.5 ) remove_etareg=true;
	if(!remove_etareg_pt)         FillEventCutFlow(4,"Presel_remove_etareg_pt", ll_weight,label);
	if(!remove_etareg)  FillEventCutFlow(4, "Presel_remove_etareg", ll_weight,label);
	if(!remove_etareg_ptless50) FillEventCutFlow(4, "Presel_remove_etareg_ptlow", ll_weight,label);
	

	if(k_running_nonprompt){
	  if(FillAll){
	    if(electrons[0].Pt() > pt1 &&  electrons[1].Pt() > pt2) FillCLHist(llhist, label+"SSLL_Preselection_pt", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	  }
	  if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection_sf", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_sf);
	  if(FillAll)FillCLHist(llhist, label+"SSLL_Preselection_df", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight_df);
	}

	if(electrons[1].Pt() > 15. && jets.size() > 1)        FillEventCutFlow(4, "Presel_8TeV", ll_weight,label);

	FillEventCutFlow(4, "Presel", ll_weight,label);

	if(fatjets.size() > 0 || jets.size() > 0)  FillEventCutFlow(4,"SSLL_Jet",ll_weight,label);

	if(fatjets.size() > 0)  FillEventCutFlow(4,"SSLL_FatJet",ll_weight,label);
	
	if(jets.size()==1 ){
	  if( (GetDiLepMass(electrons) > 110)){
	    if(FillAll)FillCLHist(llhist, label+"SSLL_1JetCR", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
	  }
	    if( (GetDiLepMass(electrons) < 100)){
	      vector<int> ti_jets;
	      float l1j = GetMasses("l1j",electrons, jets,fatjets,ti_jets, false);
	      float l2j = GetMasses("l2j",electrons, jets,fatjets,ti_jets, false);
	      float llj = GetMasses("llj",electrons, jets,fatjets,ti_jets, false);
	      if(l2j < 80 && l1j < 100 && llj < 150 &&GetDiLepMass(electrons) > 15){
		if(FillAll)FillCLHist(llhist, label+"SSLL_1JetSR", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
		
		FillEventCutFlow(4,"SSLL_1Jet",ll_weight,label);
		if(NBJet(alljets) ==0)                 FillEventCutFlow(4,"SSLL_1Jet_noB",ll_weight,label);

	      }
	    }
	    
	}
	
	if(jets.size() > 1) {
	  FillEventCutFlow(4, "DiJet", ll_weight,label);
	}
	
        FillLowMassBins(FillAll, mode, label, electrons,electrons_veto, muons_veto, alljets,jets, fatjets,nbjet_m, ll_weight,ll_trig,pt1,pt2  );
        FillHighMassBins(FillAll,mode, label, electrons,electrons_veto, muons_veto, alljets, jets, fatjets,nbjet_m, ll_weight,ll_trig, pt1, pt2);

	if(remove_etareg)        FillLowMassBins(FillAll, mode, label+"remove_etareg", electrons,electrons_veto, muons_veto, alljets,jets, fatjets,nbjet_m, ll_weight,ll_trig,pt1,pt2  );
	if(remove_etareg_pt)     FillLowMassBins(FillAll, mode, label+"remove_etareg_pt", electrons,electrons_veto, muons_veto, alljets,jets, fatjets,nbjet_m, ll_weight,ll_trig,pt1,pt2  );

	if(remove_etareg_ptless50)  FillLowMassBins(FillAll, mode, label+"remove_etareg_ptless50", electrons,electrons_veto, muons_veto, alljets,jets, fatjets,nbjet_m, ll_weight,ll_trig,pt1,pt2  );

	

      }/// mll
    } // ss
  }// dilep
  
  return;
}

void HNDiElectron::FillLowMassBins(bool FillAll,int mode, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight,std::vector<TString> trig, float pt1, float pt2){
				 

  if(mode==1 && fatjets.size() > 0) return;
  if(mode==2 && fatjets.size() == 0) return;

  if(!Preselection(label, electrons, electrons_veto, muons, alljets, jets, fatjets, ll_weight, trig, pt1 , pt2)) return;

  if(jets.size()==1){

    if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(5,"LM_Bin2_inc",ll_weight,label);
    if(PassLowMassBin2(70., 60., 100.,70., 70.,  40., 10., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_40",ll_weight,label);
    if(PassLowMassBin2(70., 60., 100.,70., 70., 40., 10., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_50",ll_weight,label);
    if(PassLowMassBin2(70., 60., 100.,70., 70., 40., 10., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_60",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,70., 70., 40., 10., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_70",ll_weight,label);
    if(PassLowMassBin2(70., 60., 100.,70., 70., 40., 10., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80",ll_weight,label);
    /// alt bins                                                                                                                                                                                                                                                                
    if(PassLowMassBin2(70., 60., 150.,70., 70., 40., 10., 100, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v2",ll_weight,label);
    if(PassLowMassBin2(70., 60., 150.,70., 70., 40., 10., 80, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v3",ll_weight,label);
    if(PassLowMassBin2(70., 60., 150.,70., 70., 40., 15., 80, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin2_80v4",ll_weight,label);
    if(PassLowMassBin2(70., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"1_Bin2_pt1max",ll_weight,label);
    if(PassLowMassBin2(100000.,60., 1100000., 10000., 10000.,10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"2_Bin2_pt2max",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 10000.,70., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_ml1j",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 10000.,10000., 70., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"3_Bin2_ml2j",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,40., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"4_Bin2_met",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 20., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"5_Bin2_mllmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 0., 60., 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"6_Bin2_mllmax",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 100000.,10000., 10000.,10000., 0., 10000., 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(6,"7_Bin2_ptmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(6,"0_Bin2_inc",ll_weight,label);

    if(PassLowMassBin2(70., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_1_Bin2_pt1max",ll_weight,label);
    if(PassLowMassBin2(70.,60., 1100000., 10000., 10000.,10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_2_Bin2_pt2max",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_mllj",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,70., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_ml1j",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,70., 70., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_3_Bin2_ml2j",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,70., 70., 40., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_4_Bin2_met",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100.,70., 70., 40., 20., 10000, 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_5_Bin2_mllmin",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100., 70., 70.,40., 20., 60., 0., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_6_Bin2_mllmax",ll_weight,label);
    if(PassLowMassBin2(70.,60., 100., 70., 70.,40., 20., 60., 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(7,"culm_7_Bin2_ptmin",ll_weight,label);
    if(PassLowMassBin2(10000., 10000., 1100000., 10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m))   FillEventCutFlow(7,"culm_0_Bin2_inc",ll_weight,label);

  }

  if(jets.size() > 1) {
    if(PassLowMassBin1(10000.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))
      FillEventCutFlow(5,"LM_Bin1_inc",ll_weight,label);

    if(PassLowMassBin1(10000., 10000., 120.,80., 200.,10000., 100000., 30., 15., 100000, 15., electrons,jets,fatjets,nbjet_m)){
      FillEventCutFlow(5,"LM_Bin1_8TeV_40",ll_weight,label);
      if(FillAll)FillCLHist(sighist_ee, label+"SSLL_LowMass_8TeV", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
    }
    if(PassLowMassBin1(10000., 10000., 120.,90., 200.,10000., 100000., 30., 15., 100000, 15., electrons,jets,fatjets,nbjet_m))          FillEventCutFlow(5,"LM_Bin1_8TeV_70",ll_weight,label);

    if(PassLowMassBin1(10000., 10000., 120.,100., 200.,10000., 100000., 30., 15., 100000, 15., electrons,jets,fatjets,nbjet_m))          FillEventCutFlow(5,"LM_Bin1_8TeV_80",ll_weight,label);

    if(PassLowMassBin1(70.   , 60.   , 9999. , 0. ,190.  ,160.   , 160.    , 40. , 20.  , 60  , 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_40", ll_weight,label);

    if(PassLowMassBin1(70., 60., 9999.,0.,190.,160., 160., 40., 20., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_50",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999., 0.,190.,160., 160., 40., 20., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_60",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 190.,160., 160., 40., 20., 60, 15., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(5,"LM_Bin1_70",ll_weight,label);

    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 40., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v1",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 40., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v2",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 40., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v3",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 40., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v4",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 40., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v5",ll_weight,label);

    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 38., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v6",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 38., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v7",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 38., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v8",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 38., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v9",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 38., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v10",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 36., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v11",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 36., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v12",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 36., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v13",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 36., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v14",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 36., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v15",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 34., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v16",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 34., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v17",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 34., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v18",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 34., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v19",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 34., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v20",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 32., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v21",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 32., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v22",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 32., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v23",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 32., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v24",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 160.,150., 150., 32., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v25",ll_weight,label);

    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 40., 20., 60, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v26",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 38., 20., 60, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v27",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 36., 20., 60, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v28",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 34., 20., 60, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v29",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 32., 20., 60, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v30",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 40., 10., 80, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v31",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 38., 10., 80, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v32",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 36., 10., 80, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v33",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 34., 10., 80, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v34",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 32., 10., 80, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v35",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 40., 15., 80, 10., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v36",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 38., 15., 80, 11., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v37",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 36., 15., 80, 12., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v38",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 34., 15., 80, 13., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v39",ll_weight,label);
    if(PassLowMassBin1(70., 60., 9999.,0., 170.,150., 150., 32., 15., 80, 14., electrons,jets,fatjets,nbjet_m))             FillEventCutFlow(25,"LM_Bin1_70v40",ll_weight,label);


    if(PassLowMassBin1(70.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_1_Bin1_pt1max",ll_weight,label);


    if(PassLowMassBin1(70.,  60., 1100000., 0., 100000., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_2_Bin1_pt2max",ll_weight,label);

    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_3_Bin1_mlljj",ll_weight,label);

    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_4_Bin1_ml1jj",ll_weight,label);


    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 150., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_5_Bin1_ml2jj",ll_weight,label);

    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 150., 40., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_6_Bin1_met",ll_weight,label);
    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 150., 40., 20., 10000., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_7_Bin1_mllmin",ll_weight,label);
    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 150., 40., 20., 60., 0,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_8_Bin1_mllmax",ll_weight,label);
    if(PassLowMassBin1(70.,  60., 9999., 0., 180., 150, 150., 40., 20., 60., 15,  electrons,jets,fatjets,nbjet_m))      FillEventCutFlow(9,"culm_9_Bin1_ptmin",ll_weight,label);

  }

}


void HNDiElectron::FillHighMassBins(bool FillAll, int mode, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, vector<TString> trig, float pt1, float pt2){
				  

  float ST (0.);
  if(muons.size() ==2)ST= muons[0].Pt() + muons[1].Pt();
  float HT=0.;
  for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
  for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
  ST+=eventbase->GetEvent().PFMET();
  float met = eventbase->GetEvent().PFMET();
  float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;


  if(mode==1 && fatjets.size() > 0) return;
  if(mode==2 && fatjets.size() == 0) return;


  if(!Preselection(label, electrons, electrons_veto, muons, alljets, jets, fatjets, ll_weight, trig, pt1, pt2)) return;

  if(mode==2){
    if(jets.size() > 1&& fatjets.size() ==0) {
      if(PassHighMassBin1(0.,0.,0., 99999., 0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_inc",ll_weight,label);
    }
  }
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_inc",ll_weight,label);
  if(PassHighMassBin1(110.,0., 0., 9999.,  0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_pt1",ll_weight,label);
  if(PassHighMassBin1(0.,60., 0., 9999.,  0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_pt2",ll_weight,label);
  if(PassHighMassBin1(0.,0.,0., 9999., 490., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mlljj",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 30., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mjjmin",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 150., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_mjjmax",ll_weight,label);
  if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(12,"HM_Bin1_400_met",ll_weight,label);

  if(PassHighMassBin1(25.,15., 50., 100., 100.,  30.,  150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_90",ll_weight,label);
  if(PassHighMassBin1(25.,15., 50., 120.,120., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_100",ll_weight,label);
  if(1){
    float min_ljet_Dr=10000.;
    float min_eleadawayjet_Dr=0.;
    for(UInt_t i=0; i<muons.size(); i++){
      for(UInt_t emme=0; emme<jets.size(); emme++){
        float dR =muons[i].DeltaR(jets[emme]);
        if(dR > 0.5) {
          if(dR > min_eleadawayjet_Dr) {
            min_eleadawayjet_Dr=  dR;
          }
        }
        if(dR< min_ljet_Dr) min_ljet_Dr=dR;

      }
    }
    if(PassHighMassBin1(25.,15., 70., 115.,110., 30., 150., 9.,  electrons,jets,fatjets,nbjet_m,met2_st)){
      if(jets[0].Pt() > 25){
        if(min_ljet_Dr<1.5){
          if(muons[0].DeltaR(muons[1]) < 3.4){
            FillEventCutFlow(10,"HM_Bin1_100v2",ll_weight,label);
          }
        }
      }
    }
    if(PassHighMassBin1(25.,15., 50., 105., 90.,  30.,  150., 9.,  electrons,jets,fatjets,nbjet_m,met2_st)) {
      if(jets[0].Pt() > 25){
        if(min_ljet_Dr<1.5){
          if(muons[0].DeltaR(muons[1]) < 3.4){
            FillEventCutFlow(10,"HM_Bin1_90v2",ll_weight,label);
          }
        }
      }
    }
    if(PassHighMassBin1(25.,25., 90., 140., 140.,30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) {
      if(jets[0].Pt() > 25){
        if(min_ljet_Dr<2.){
          if(muons[0].DeltaR(muons[1]) < 3.4){
            FillEventCutFlow(10,"HM_Bin1_125v2",ll_weight,label);
          }
	}
      }
    }
    if(PassHighMassBin1(25.,25., 90., 140., 140.,30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) {
      if(jets[0].Pt() > 25){
        if(min_ljet_Dr<1.7){
          if(muons[0].DeltaR(muons[1]) < 3.4){
            FillEventCutFlow(10,"HM_Bin1_150v2",ll_weight,label);
          }
        }
      }
    }

  }


  if(PassHighMassBin1(30.,25., 90., 140., 120.,30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_125",ll_weight,label);
  if(PassHighMassBin1(40.,25., 130., 160., 180., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_150",ll_weight,label);
  if(PassHighMassBin1(55.,40., 170., 225., 220., 30.,150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_200",ll_weight,label);
  if(PassHighMassBin1(70.,60.,220., 270., 310., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_250",ll_weight,label);
  if(PassHighMassBin1(80.,60.,235., 335., 370., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_300",ll_weight,label);
  if(PassHighMassBin1(100.,65.,350., 450., 450., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_400",ll_weight,label);
  if(PassHighMassBin1(125.,65.,400., 555., 560., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_500",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 690., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_600",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 955., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_700",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1130., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_800",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1300., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_900",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1490, 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1000",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1490., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1100",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1600., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1200",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1930., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1300",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400.,  1930., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1400",ll_weight,label);
  if(PassHighMassBin1(125.,80.,400., 1930., 760., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(10,"HM_Bin1_1500",ll_weight,label);



  if(PassHighMassBin1Window(25.,15., 50., 100., 100.,  30.,  150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_90",ll_weight,label);
  if(PassHighMassBin1Window(25.,15., 50., 120.,120., 30., 150., 9.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_100",ll_weight,label);  
  if(PassHighMassBin1Window(30.,25., 90., 140., 120.,30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_125",ll_weight,label);
  if(PassHighMassBin1Window(40.,25., 130., 160., 180., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_150",ll_weight,label);
  if(PassHighMassBin1Window(55.,40., 170., 225., 220., 30.,150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_200",ll_weight,label);
  if(PassHighMassBin1Window(70.,60.,220., 270., 310., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_250",ll_weight,label);
  if(PassHighMassBin1Window(80.,60.,235., 335., 370., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_300",ll_weight,label);
  if(PassHighMassBin1Window(100.,65.,350., 450., 450., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_400",ll_weight,label);
  if(PassHighMassBin1Window(125.,65.,400., 555., 560., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_500",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 690., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_600",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 955., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_700",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1130., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_800",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1300., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_900",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1490, 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1000",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1490., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1100",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1600., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1200",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1930., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1300",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400.,  1930., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1400",ll_weight,label);
  if(PassHighMassBin1Window(125.,80.,400., 1930., 760., 30., 150., 7.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(17,"HM_Window02_Bin1_1500",ll_weight,label);



  if(mode==2){

    if(fatjets.size() > 0){
      if(PassHighMassBin2(0.,0,0.,10000., 10000.,  electrons,jets,fatjets,nbjet_m,met2_st))
        FillEventCutFlow(11,"HM_Bin2_inc",ll_weight,label);
    }


    if(PassHighMassBin2(25.,15,90., 170., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_90",ll_weight,label);
    if(PassHighMassBin2(25.,15,100., 135., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_100",ll_weight,label);
    if(PassHighMassBin2(60.,15,100., 135., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_125",ll_weight,label);
    if(PassHighMassBin2(70.,15,145., 190., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_150",ll_weight,label);

    if(PassHighMassBin2(100.,20,195., 250., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_200",ll_weight,label);
    if(PassHighMassBin2(140.,25,220., 290., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_250",ll_weight,label);
    if(PassHighMassBin2(140.,40,265,355., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_300",ll_weight,label);
    if(PassHighMassBin2(140.,65,355.,465., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_400",ll_weight,label);
    if(PassHighMassBin2(140.,65,475.,610., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_500",ll_weight,label);
    if(PassHighMassBin2(140.,75,550., 720., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_600",ll_weight,label);
    if(PassHighMassBin2(140.,75,620.,930., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_700",ll_weight,label);
    if(PassHighMassBin2(140.,75,710., 1170., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_800",ll_weight,label);
    if(PassHighMassBin2(140.,75,750., 1165., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_900",ll_weight,label);
    if(PassHighMassBin2(140.,75,810., 1300., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1000",ll_weight,label);
    if(PassHighMassBin2(140.,75,810., 1410., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1100",ll_weight,label);
    if(PassHighMassBin2(140.,75,880., 1520., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1200",ll_weight,label);
    if(PassHighMassBin2(140.,75,980.,1620. , 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1300",ll_weight,label);
    if(PassHighMassBin2(140.,75,1070., 1730., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1400",ll_weight,label);
    if(PassHighMassBin2(140.,75,1160., 1840., 15.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(11,"HM_Bin2_1500",ll_weight,label);

    if(PassHighMassBin2(0.,0,0., 1000.,10000.,  electrons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_inc",ll_weight,label);
    if(PassHighMassBin2(140.,0,0.,  1000.,10000.,  electrons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_pt1",ll_weight,label);
    if(PassHighMassBin2(0.,65,0.,  1000.,10000. , electrons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_pt2",ll_weight,label);
    if(PassHighMassBin2(0.,0,450.,  1000.,10000.,  electrons,jets,fatjets,nbjet_m,met2_st))  FillEventCutFlow(13,"HM_Bin2_400_mlljj",ll_weight,label);


  }

}

void HNDiElectron::GetOptimisationID( vector<snu::KElectron> electron_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, std::vector<TString> trig, float pt1, float pt2){
  vector<TString> IDForOpt;
  IDForOpt.push_back("ELECTRON_POG_MEDIUM");
  IDForOpt.push_back("ELECTRON_POG_TIGHT");
  ///                                                                                                                                                                                                                                                                           
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso05");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso06");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso07");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso08");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso09");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso10");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_iso15");
  //                                                                                                                                                                                                                                                                            
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dz06");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dz10");
  //                                                                                                                                                                                                                                                                            
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dxy02");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dxy015");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dxy01");
  IDForOpt.push_back("ELECTRON_POG_TIGHT_dxy005");

  vector<TString> IDForOptloose;
  IDForOptloose.push_back("ELECTRON_POG_FAKEMEDIUM");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  IDForOptloose.push_back("ELECTRON_POG_FAKETIGHT");
  bool datadriven=true;
  if(k_running_nonprompt){
    for(unsigned int i=0 ; i < IDForOptloose.size(); i++){
      vector<snu::KElectron>  electrons =  GetElectrons(false,false,IDForOptloose[i],false);

      float ST (0.);
      if(electrons.size() ==2)ST= electrons[0].Pt() + electrons[1].Pt();
      float HT=0.;
      for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
      for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
      ST+=eventbase->GetEvent().PFMET();


      float met = eventbase->GetEvent().PFMET();
      float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;
      if(!isData)ll_weight *= PreselWeight(ll_weight, electrons, IDForOpt[i], PassTriggerOR(trig));
      else ll_weight = PreselWeight(ll_weight,electrons, IDForOpt[i], PassTriggerOR(trig));

      if(Preselection(IDForOpt[i], electrons, electron_veto, muons, alljets, jets, fatjets, PreselWeight(ll_weight,electrons, IDForOpt[i], PassTriggerOR(trig)),trig, pt1, pt2)){
        if(PassLowMassBin1(10000.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(20, IDForOpt[i],ll_weight,IDForOpt[i]);
        if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(21, IDForOpt[i],ll_weight,IDForOpt[i]);
        if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st))   FillEventCutFlow(22, IDForOpt[i],ll_weight,IDForOpt[i]);
        if(PassHighMassBin2(0.,0,0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(23, IDForOpt[i],ll_weight,IDForOpt[i]);
      }
    }
  }
  else{

    for(unsigned int i=0 ; i < IDForOpt.size(); i++){
      vector<snu::KElectron>  electrons =  GetElectrons(IDForOpt[i],false);

      float ST (0.);
      if(electrons.size() ==2)ST= electrons[0].Pt() + electrons[1].Pt();
      float HT=0.;
      for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
      for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
      ST+=eventbase->GetEvent().PFMET();

      float met = eventbase->GetEvent().PFMET();
      float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;
      if(!isData)ll_weight *= PreselWeight(ll_weight, electrons, IDForOpt[i], PassTriggerOR(trig));
      else ll_weight = PreselWeight(ll_weight,electrons, IDForOpt[i], PassTriggerOR(trig));

      if(Preselection(IDForOpt[i], electrons, electron_veto, muons, alljets, jets, fatjets, PreselWeight(ll_weight,electrons, IDForOpt[i], PassTriggerOR(trig)),trig, pt1, pt2)){
        if(PassLowMassBin1(10000.,  10000., 1100000.,0., 100000., 10000, 100000., 10000., 0., 10000., 0,  electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(20, IDForOpt[i],ll_weight,"");

        if(PassLowMassBin2(10000., 10000., 1100000.,10000., 10000., 10000., 0., 10000, 0., electrons,jets,fatjets,nbjet_m)) FillEventCutFlow(21, IDForOpt[i],ll_weight,IDForOpt[i]);
        if(PassHighMassBin1(0.,0., 0., 9999.,  0., 0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st))   FillEventCutFlow(22, IDForOpt[i],ll_weight,IDForOpt[i]);
        if(PassHighMassBin2(0.,0,0., 100000., 1000.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillEventCutFlow(23, IDForOpt[i],ll_weight,IDForOpt[i]);
      }
    }

  }
}


void HNDiElectron::FillHighMass(bool FillAll,int mode, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, int nbjet_m, float ll_weight, std::vector<TString> trig, float pt1, float pt2){
			      



  if(mode==1 && fatjets.size() > 0) return;
  if(mode==2 && fatjets.size() == 0) return;

  float ST (0.);
  if(muons.size() ==2)ST= muons[0].Pt() + muons[1].Pt();
  float HT=0.;
  for(unsigned int ij=0; ij <jets.size(); ij++){HT+= jets[ij].Pt();       ST+= jets[ij].Pt();}
  for(unsigned int ij=0; ij < fatjets.size(); ij++){ HT+= fatjets[ij].Pt(); ST+= fatjets[ij].Pt();}
  ST+=eventbase->GetEvent().PFMET();
  float met = eventbase->GetEvent().PFMET();
  float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;


  if(!Preselection(label, electrons, electrons_veto, muons, alljets, jets, fatjets, ll_weight, trig, pt1, pt2)) return;
  if((CheckSignalRegion(true,electrons,electrons , jets, fatjets,alljets,"HighMM", ll_weight,mode)) ){
    if( (mode==0 && jets.size() > 1)  || (mode==1 &&jets.size() > 1 && fatjets.size() ==0) || (mode==2 && fatjets.size()>0)){
      FillEventCutFlow(4,"SSLL_HighMass_mlljj",ll_weight,label);

      if(nbjet_m==0){
        if(met2_st < 15) {
          

          if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_SR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

          FillEventCutFlow(4,"SSLL_HighMass_SR",ll_weight,label);
          if(PassHighMassBin1(25.,15., 50., 100., 110.,  30.,  150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st))FillCLHist(sighist_ee, label+"SSLL_HighMass_bin1_90", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

          if(PassHighMassBin1(25.,15., 50., 110.,120., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st))FillCLHist(sighist_ee, label+"SSLL_HighMass_bin1_100", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          if(PassHighMassBin1(30.,25., 90., 140., 120.,30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillCLHist(sighist_ee, label+"SSLL_HighMass_bin1_125", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          if(PassHighMassBin1(35.,35., 130., 160., 180., 30., 150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st))FillCLHist(sighist_ee, label+"SSLL_HighMass_bin1_150", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
          if(PassHighMassBin1(50.,40., 170., 225., 220., 30.,150., 6.,  electrons,jets,fatjets,nbjet_m,met2_st)) FillCLHist(sighist_ee, label+"SSLL_HighMass_bin1_200", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);


          if(muons[0].Pt() > 140 && muons[1].Pt() > 70)FillEventCutFlow(4,"SSLL_HighMass_SR2",ll_weight,label);
          if(met2_st < 7){
            if(mode==1) {
              if(fatjets.size() ==0){
                vector<int > ijets;
                float mlljj = GetMasses("lljj",muons, jets,fatjets,ijets, true);
                float mjj = GetMasses("jj",muons, jets,fatjets,ijets, true);
                if(muons[0].Pt() >110 && muons[1].Pt() > 40 && mlljj > 800, mjj > 30 && mjj < 150)               if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
              }
            }
            if(mode==2) {
              if(fatjets.size() >0){
                vector<int > ijets;
                float mllfj = GetMasses("llfj",muons, jets,fatjets,ijets, true);
                float mjj = fatjets[0].PrunedMass();
                if(muons[0].Pt() >140 && muons[1].Pt() > 70 && mllfj > 640, mjj > 30 && mjj < 150)               if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_SR2", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

              }
            }

            FillHist(label+"Truth_WZ_SS_HighMass_Zmass",GetVirtualMass(13,false,false), ll_weight*WeightByTrigger(trig, TargetLumi), 0., 150., 150);
          }
        }
        if(mode ==0 ){
          if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
        }
        if(mode==1){
          if(fatjets.size() ==0){
            if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

          }
	}
        if(mode==2){
          if(fatjets.size() >0){
            if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

          }
        }

        if(mode==2){
          if(fatjets.size() >0){
            if(met2_st > 20 || nbjet_m > 0)if(FillAll)FillCLHist(sighist_ee, label+"SSLL_HighMass_CR", eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);

          }
        }
      }
    }
  }



}

float HNDiElectron::PreselWeight(float mcw, std::vector<snu::KElectron> electrons, TString id, bool passtrig){
  if(electrons.size() != 2) return mcw;

  if(k_running_nonprompt){
    if(electrons[1].Pt() < 15.) return 0.;

    //id=_m_looseid;                                                                                                                                                                                                                                                            
    //if(id=="DiElectron_SIP") id="ELECTRON_HN_Loose_HighdXY_Small";                                                                                                                                                                                                                    
    //if(id=="DiElectron_8TeV") id="ELECTRON_HN_LOOSE_8TeV";                                                                                                                                                                                                                            
    //if(id=="DiElectron_AUX") id="ELECTRON_HN_Loose_HighdXY_Small";                                                                                                                                                                                                                    


    float pre_weight (1.);
    pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_central",0);
    if(id=="DiElectron_SIP")      pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_sip_central",0);
    if(id=="DiElectron_AUX")pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, _e_tightid, "ptcone", "fr_electron_aux",0);

    if(id=="DiElectron_8TeV")  pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_HN_TIGHT_8TeV", "ptcone", "fr_electron_8TeV_central",0);
    if(id=="ELECTRON_POG_TIGHT")       pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT", "ptcone", "fr_electron_pogt",0);
    if(id=="ELECTRON_POG_MEDIUM")       pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_MEDIUM", "ptcone", "fr_electron_pogm",0);
    if(id=="ELECTRON_POG_TIGHT_iso05") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso05", "ptcone", "fr_electron_iso05",0);
    if(id=="ELECTRON_POG_TIGHT_iso06") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso06", "ptcone", "fr_electron_iso06",0);
    if(id=="ELECTRON_POG_TIGHT_iso07") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso07", "ptcone", "fr_electron_iso07",0);
    if(id=="ELECTRON_POG_TIGHT_iso08") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso08", "ptcone", "fr_electron_iso08",0);
    if(id=="ELECTRON_POG_TIGHT_iso09") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso09", "ptcone", "fr_electron_iso09",0);
    if(id=="ELECTRON_POG_TIGHT_iso10") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso10", "ptcone", "fr_electron_iso10",0);
    if(id=="ELECTRON_POG_TIGHT_iso15") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_iso15", "ptcone", "fr_electron_iso15",0);
    if(id=="ELECTRON_POG_TIGHT_dz06") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dz06","ptcone", "fr_electron_dz06",0);
    if(id=="ELECTRON_POG_TIGHT_dz10") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dz10","ptcone", "fr_electron_dz10",0);
    if(id=="ELECTRON_POG_TIGHT_dxy02") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dxy02","ptcone", "fr_electron_dxy02",0);
    if(id=="ELECTRON_POG_TIGHT_dxy015") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dxy015","ptcone", "fr_electron_dxy015",0);
    if(id=="ELECTRON_POG_TIGHT_dxy01") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dxy01","ptcone", "fr_electron_dxy01",0);
    if(id=="ELECTRON_POG_TIGHT_dxy005") pre_weight=m_datadriven_bkg->Get_DataDrivenWeight_EE(false, electrons, "ELECTRON_POG_TIGHT_dxy005","ptcone", "fr_electron_dxy005",0);




    return pre_weight;
  }

  if(isData) return 1.;

  float eeweight  = mcw*EEWeight(electrons, id);
  return eeweight;
}

float HNDiElectron::MMWeight(std::vector<snu::KMuon> muons, TString id, bool passtrig){

  if(isData) return 1.;
  float mc_weight=mcdata_correction->MuonTrackingEffScaleFactor(muons);

  float puweight=1.;
  //if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);                                                                                                                                                                                 
  //else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), jets.size());                                                                                                                                                                                     
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  mc_weight*= puweight;

  /// ID issue                                                                                                                                                                                                                                                                  
  return mc_weight;

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

bool HNDiElectron::Preselection(TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> el_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, float ll_weight, vector<TString> trigs, float pt1, float pt2){
			      
  
  if (label.Contains("fake1l")){
    if(electrons.size() == 2){
      if(!isData){
        int nF=0;
        if(!TruthMatched(electrons[0],false) ) nF++;
        if(!TruthMatched(electrons[1],false) ) nF++;
        if(nF != 1) return false;
      }
    }
  }

  if (label.Contains("fake2l")){
    if(electrons.size() == 2){
      if(!isData){
        int nF=0;
        if(!TruthMatched(electrons[0],false) ) nF++;
        if(!TruthMatched(electrons[1],false) ) nF++;
	if(nF != 2) return false;
      }
    }
  }

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return false;
  if(!PassMETFilter()) return false;     /// Initial event cuts :                                                                                                                                                                                                    


  bool cut1_dilep =  (electrons.size()==2 && (electrons[1].Pt() > pt2 && electrons[0].Pt() > pt1 ));
  // if(k_running_nonprompt)cut1_dilep =  (muons.size()==2 && (muons[1].PTCone(0.4,0.07) > pt2 && muons[0].PTCone(0.4,0.07) > pt1 ));                                                                                                                                           
  if(!cut1_dilep) return false;

  bool cut2_trig = PassTriggerOR(trigs);
  if(!cut2_trig) return false;

  bool cut3_lepveto = (muons.size()>0);
  if(cut3_lepveto) return false;
  if(el_veto.size() != 2) return false;

  if(!SameCharge(electrons)) return false;

  return true;
}

  


void HNDiElectron::FillPreselection(int nfake, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  float ll_weight, vector<TString> trig, float pt1, float pt2){
				  

  if(!Preselection(label, electrons, electrons_veto, muons, alljets, jets, fatjets, ll_weight, trig, pt1, pt2)) return;
  if(nfake == 0)FillCLHist(sighist_ee, label+"SSLL_Preselection",  eventbase->GetEvent(), muons, electrons,jets, alljets,  fatjets,ll_weight);
  if(nfake == 1)FillCLHist(sighist_ee, label+"SSLL_Preselection_sf", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
  if(nfake == 2)FillCLHist(sighist_ee, label+"SSLL_Preselection_df", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets,  ll_weight);
}



void HNDiElectron::FillMCFakes( TString label, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, vector<TString> ll_trig, float ll_weight, TString looseID, TString tightID){
  
  std::vector<snu::KElectron> electrons_loose= GetElectrons(true,true,looseID,true);

  if(electrons_loose.size() == 2)FillCLHist(sighist_ee, label+"SSLL_MCLoose", eventbase->GetEvent(), muons, electrons_loose , jets, alljets, fatjets,  ll_weight);

  std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
  
  for(unsigned int i=0 ;i < electrons_loose.size() ; i++){

    float el_pt_corr =  electrons_loose.at(0).Pt()*(1+max(0.,(electrons_loose.at(0).PFRelIso(0.3)-0.08))) ; 
    
    if(fabs(electrons_loose.at(i).Eta()) < 1.5){
      FillHist("MC_pog_BFR_type_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
      if(PassID(electrons_loose[i], _e_tightid)) {
	FillHist("MC_pog_BFR_type_el_tight_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
      }
    }
    else{
      FillHist("MC_pog_EFR_type_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
      if(PassID(electrons_loose[i], _e_tightid)) {
	FillHist("MC_pog_EFR_type_el_tight_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
      } 
    }
    if(electrons_loose.at(i).GetType()==7){
      if(fabs(electrons_loose.at(i).Eta()) < 1.5){
	FillHist("MC_pog_BFR_type7_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_BFR_type7_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
	FillHist("MC_pog_BFR_type7Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
	FillHist("MC_pog_BFR_type7Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_BFR_type7Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., -1., 1., 200);
        FillHist("MC_pog_BFR_type7_el_loose_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_BFR_type7_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
	}
      }
      else{
        FillHist("MC_pog_EFR_type7_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_EFR_type7_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_EFR_type7Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_EFR_type7Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_EFR_type7Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., -1., 1., 200);
        FillHist("MC_pog_EFR_type7_el_loose_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_EFR_type7_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
    }
    if(electrons_loose.at(i).GetType()==22){
      if(fabs(electrons_loose.at(i).Eta()) < 1.5){
        FillHist("MC_pog_BFR_type22_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_BFR_type22_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_BFR_type22Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_BFR_type22Fake_mc_isodxy_el_"+label,electrons_loose.at(i).dxy()  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_BFR_type22Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., -1., 1., 200);
	
	FillHist("MC_pog_BFR_type22_el_loose_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);
	
        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_BFR_type22_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
	  FillHist("MC_pog_BFR_type22_el_tight_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);

        }
      }
      else{
        FillHist("MC_pog_EFR_type22_el_loose_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);

        FillHist("MC_pog_EFR_type22_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_EFR_type22_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_EFR_type22Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_EFR_type22Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_EFR_type22Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_EFR_type22_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
	  FillHist("MC_pog_EFR_type22_el_tight_missingHits" +label,  electrons_loose[i].MissingHits()  , 1., 0., 5.,5);

        }
      }
    }
    if(electrons_loose.at(i).GetType()==26){
      if(fabs(electrons_loose.at(i).Eta()) < 1.5){
        FillHist("MC_pog_BFR_type26_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_BFR_type26_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_BFR_type26Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_BFR_type26Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_BFR_type26Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_BFR_type26_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
      else{
        FillHist("MC_pog_EFR_type26_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_EFR_type26_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_EFR_type26Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_EFR_type26Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_EFR_type26Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_EFR_type26_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
    }

    if(electrons_loose.at(i).GetType()==27){
      if(fabs(electrons_loose.at(i).Eta()) < 1.5){
        FillHist("MC_pog_BFR_type27_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_BFR_type27_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_BFR_type27Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_BFR_type27Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_BFR_type27Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_BFR_type27_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
      else{
        FillHist("MC_pog_EFR_type27_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_EFR_type27_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
	FillHist("MC_pog_EFR_type27Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_EFR_type27Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_EFR_type27Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_EFR_type27_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
    }

    if(electrons_loose.at(i).GetType()==28){
      if(fabs(electrons_loose.at(i).Eta()) < 1.5){
        FillHist("MC_pog_BFR_type28_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_BFR_type28_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_BFR_type28Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_BFR_type28Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_BFR_type28Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_BFR_type28_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
      else{
        FillHist("MC_pog_EFR_type28_el_loose_"+label,  electrons_loose.at(i).GetType(), 1., 0., 50.,50);
        FillHist("MC_pog_EFR_type28_el_loose_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        FillHist("MC_pog_EFR_type28Fake_mc_isopt_el_"+label,   electrons_loose.at(i).PFRelIso(0.3), 1., 0., 0.6, 60);
        FillHist("MC_pog_EFR_type28Fake_mc_isodxy_el_"+label,fabs(electrons_loose.at(i).dxy())  , 1., -0.2, 0.2, 40);
        FillHist("MC_pog_EFR_type28Fake_mc_MVA_el_"+label,fabs(electrons_loose.at(i).MVA())  , 1., 0., 1., 100);

        if(PassID(electrons_loose[i], _e_tightid)) {
          FillHist("MC_pog_EFR_type28_el_tight_pt"+label,el_pt_corr ,1., 0., 500., 100.);
        }
      }
    }
  }

}



bool HNDiElectron::PassLowMassBin2(float pt1max, float pt2max, float mlljmax, float ml1jmax, float ml2jmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet){
	
  bool debug=false;

  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() != 1){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  
  snu::KParticle mm = electrons.at(0) + electrons.at(1);
  if(mm.M()  < mllmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > mllmax) {if(debug)cout << "Fail mee  " << endl; return false;}

  float met = eventbase->GetEvent().PFMET();
  if(met >  metmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  snu::KParticle llj = electrons.at(0) + electrons.at(1) + jets[0];
  snu::KParticle l1j = electrons.at(0)  + jets[0];
  snu::KParticle l2j =  electrons.at(1) + jets[0];
  if(llj.M() > 150) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > 60) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(met >  80) {if(debug)cout << "Fail mee  " << endl; return false;}

  if(llj.M() > mlljmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(l1j.M() > ml1jmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(l2j.M() > ml2jmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  
  return true;
}



bool HNDiElectron::PassHighMassBin1Window(float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
					

  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.at(0).Pt() < pt1min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  vector<int> ijets;
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) > 150.)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("lljj",electrons, jets,fjets,ijets, false) < mlljjmin)  {if(debug)cout << "Fail  " << endl; return false;}
  //if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) < ml2jjmin)  {if(debug)cout << "Fail  " << endl; return false;}                                                              
  //if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) > ml2jjmax)  {if(debug)cout << "Fail  " << endl; return false;}                                                              
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) < mjjmin)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) > mjjmax)  {if(debug)cout << "Fail  " << endl; return false;}


  bool inwindow1=false;
  bool inwindow2=false;
  if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) >  ml2jjmin){
    if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) <  ml2jjmax){
      inwindow2=true;
    }
  }
  if(GetMasses("l1jj",electrons, jets,fjets,ijets, false) >  ml2jjmin){
    if(GetMasses("l1jj",electrons, jets,fjets,ijets, false) <  ml2jjmax){
      inwindow1=true;
    }
  }
  if(!inwindow2&& !inwindow1)  {if(debug)cout << "Fail  " << endl; return false;}
  //else{                                                                                                                                                                            
  //if(!inwindow2)  {if(debug)cout << "Fail  " << endl; return false;}                                                                                                               
  //  }                                                                                                                                                                              
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}

bool HNDiElectron::PassHighMassBin1(float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st, bool debug){


  if(nbjet>0 ) {if(debug)cout << "Fail bjet size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail mu size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail ak4 size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail ak8 size" << endl; return false ;}
  if(electrons.at(0).Pt() < pt1min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  vector<int> ijets;
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) > 150.)  {if(debug)cout << "Fail jj  " << endl; return false;}
  if(GetMasses("lljj",electrons, jets,fjets,ijets, false) < mlljjmin)  {if(debug)cout << "Fail lljj  " << endl; return false;}
  if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) < ml2jjmin)  {if(debug)cout << "Fail  l2jj" << endl; return false;}
  if(GetMasses("l2jj",electrons, jets,fjets,ijets, false) > ml2jjmax)  {if(debug)cout << "Fail l2jjmax " << endl; return false;}
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) < mjjmin)  {if(debug)cout << "Fail jjmin " << endl; return false;}
  if(GetMasses("jj",electrons, jets,fjets,ijets, false) > mjjmax)  {if(debug)cout << "Fail  jjmax" << endl; return false;}

  if(met2_st > met2st)   {if(debug)cout << "Fail  MET" << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}
 


bool HNDiElectron::PassHighMassBin2Window(float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
				  
  
  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() == 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  vector<int> ijets;
  if(GetMasses("fj",electrons, jets,fjets,ijets, false) > 150)  {if(debug)cout << "Fail  " << endl; return false;}
  if(GetMasses("llfj",electrons, jets,fjets,ijets, false) < mllfjmin)  {if(debug)cout << "Fail  " << endl; return false;}

  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}


bool HNDiElectron::PassHighMassBin2(float pt1max, float pt2max, float ml2fjmin, float ml2fjmax,   float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
				  

  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() == 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  vector<int> ijets;
  if(GetMasses("fj",electrons, jets,fjets,ijets, false) > 150)  {if(debug)cout << "Fail  " << endl; return false;}
  //if(GetMasses("l1fj",electrons, jets,fjets,ijets, false) < mllfjmin)  {if(debug)cout << "Fail  " << endl; return false;}                                                              
  //if(GetMasses("l2fj",electrons, jets,fjets,ijets, false) < mllfjmin)  {if(debug)cout << "Fail  " << endl; return false;}                                                              

  bool inwindow1=false;
  bool inwindow2=false;

  if(GetMasses("l2fj",electrons, jets,fjets,ijets, false) >  ml2fjmin){
    if(GetMasses("l2fj",electrons, jets,fjets,ijets, false) <  ml2fjmax){
      inwindow2=true;
    }
  }
  if(GetMasses("l1fj",electrons, jets,fjets,ijets, false) >  ml2fjmin){
    if(GetMasses("l1fj",electrons, jets,fjets,ijets, false) <  ml2fjmax){
      inwindow1=true;
    }
  }
  if(!inwindow2&& !inwindow1)  {if(debug)cout << "Fail  " << endl; return false;}




  if(met2_st > met2st)   {if(debug)cout << "Fail  " << endl; return false;}
  if(met2_st > 15)   {if(debug)cout << "Fail  " << endl; return false;}

  return true;
}




bool HNDiElectron::PassLowMassBin1(float pt1max, float pt2max,float mjjmax, float mlljjmin,  float mlljjmax, float ml1jjmax, float ml2jjmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet){
  

  bool debug=false;
  if(nbjet>0 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  if(jets.size() < 2){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(fjets.size() != 0){ if(debug)cout << "Fail el size" << endl; return false ;}
  if(electrons.at(1).Pt() < pt2min)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(0).Pt() > pt1max)  {if(debug)cout << "Fail pt2  " << endl; return false;}
  if(electrons.at(1).Pt() > pt2max)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  snu::KParticle mm = electrons.at(0) + electrons.at(1);
  if(mm.M()  < mllmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mm.M()  > mllmax) {if(debug)cout << "Fail mee  " << endl; return false;}

  float met = eventbase->GetEvent().PFMET();
  if(met >  metmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  vector<int > ijets;
  if(GetMasses("lljj",electrons, jets,fjets,ijets, true) < mlljjmin) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("lljj",electrons, jets,fjets,ijets, true) > mlljjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("l1jj",electrons, jets,fjets,ijets, true) > ml1jjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(GetMasses("l2jj",electrons, jets,fjets,ijets, true) > ml2jjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(mjjmax != 999.){
    if(GetMasses("jj",electrons, jets,fjets,ijets, true) > mjjmax) {if(debug)cout << "Fail mee  " << endl; return false;}
  }
  if(GetMasses("lljj",electrons, jets,fjets,ijets, true) > 300) {if(debug)cout << "Fail mee  " << endl; return false;}
  if(met >  80) {if(debug)cout << "Fail mee  " << endl; return false;}

  
  return true;
}


float HNDiElectron::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip){
  
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


void HNDiElectron::FillEventCutFlow(int cf,TString cut,  float wt, TString label){
  
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

    if(GetHist(label+ "mm_eventcutflow_DoubleEG")) {
      GetHist( label+"mm_eventcutflow_DoubleEG")->Fill(cut,wt);

    }
    else{

      vector<TString> electronIDs;
      electronIDs.push_back("NoCut");
      electronIDs.push_back("GEN_PTETA");
      electronIDs.push_back("ELECTRON_HN_EFF_PT");
      electronIDs.push_back("ELECTRON_HN_EFF_DXY");
      electronIDs.push_back("ELECTRON_HN_EFF_DZ");
      electronIDs.push_back("ELECTRON_HN_EFF_charge");
      electronIDs.push_back("ELECTRON_HN_EFF_conv");
      electronIDs.push_back("ELECTRON_HN_EFF_dxysig");
      electronIDs.push_back("ELECTRON_HN_EFF_iso");
      electronIDs.push_back("ELECTRON_HN_EFF_onlyiso");
      electronIDs.push_back("ELECTRON_HN_EFF_mva");
      electronIDs.push_back("ELECTRON_HN_EFF_pogmva");
      electronIDs.push_back(_e_tightid);
      electronIDs.push_back("DiJet");
      electronIDs.push_back("Jet");
      electronIDs.push_back("Jet1");
      electronIDs.push_back("Jet2");
      electronIDs.push_back("Jet3");
      electronIDs.push_back("8TeV_LM");
      electronIDs.push_back("13TeV_LM_SR1");
      electronIDs.push_back("13TeV_LM_SR2");
      electronIDs.push_back("13TeV_HM_SR1");
      electronIDs.push_back("13TeV_HM_SR2");

      electronIDs.push_back("ELECTRON_HN_TIGHT_8TeV"  );
      electronIDs.push_back("8TeV_OLDID_LM");
      electronIDs.push_back("13TeV_OLDID_LM");

      AnalyzerCore::MakeHistograms( label+"mm_eventcutflow_DoubleEG",electronIDs.size(),0.,float(electronIDs.size()));

      for(unsigned int iid=0; iid < electronIDs.size(); iid++){

        TString elid = electronIDs[iid];
        GetHist(label+ "mm_eventcutflow_DoubleEG")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( label+"mm_eventcutflow_DoubleEG")->Fill(cut,wt);

    }
    
    
  }
  
  if(cf==3){
    if(GetHist( label + "ll_eventcutflow_HighMassDoubleEG")) {
      GetHist( label + "ll_eventcutflow_HighMassDoubleEG")->Fill(cut,wt);

    }
    else{

      vector<TString> IDs;
      IDs.push_back("HighMassLL_HNTIGHT");
      IDs.push_back("HighMassLL_HNTIGHT2");
      IDs.push_back("HighMassLL_HNTIGHT3");
      IDs.push_back("HighMassLL_HNTIGHT4");
      IDs.push_back("HighMassLL_HNTIGHT5");
      IDs.push_back("HighMassLL_HNTIGHT6");
      AnalyzerCore::MakeHistograms( label + "ll_eventcutflow_HighMassDoubleEG",IDs.size(),0.,float(IDs.size()));

      for(unsigned int iid=0; iid < IDs.size(); iid++){

	TString elid = IDs[iid];
	GetHist( label + "ll_eventcutflow_HighMassDoubleEG")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( label + "ll_eventcutflow_HighMassDoubleEG")->Fill(cut,wt);

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
	IDs.push_back("TriggerEle27");
	IDs.push_back("TriggerEle23");
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
	IDs.push_back("TriggerEle27");
	IDs.push_back("TriggerEle23");
	IDs.push_back("Trigger");
	IDs.push_back("LepVeto");
	IDs.push_back("SSLLLoose");
	IDs.push_back("MLL");
	IDs.push_back("Presel");
	IDs.push_back("Presel_remove_etareg_ptlow");
	IDs.push_back("Presel_remove_etareg_pt");
	IDs.push_back("Presel_remove_etareg");
	IDs.push_back("Presel_8TeV");
	IDs.push_back("SSLL_Jet");
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

void  HNDiElectron::FillEfficiency(TString lab, vector<snu::KJet> jets,  vector<snu::KFatJet> fatjets,float w){


  vector<TString> electronIDs;
  electronIDs.push_back("ELECTRON_HN_EFF_PT");
  electronIDs.push_back("ELECTRON_HN_EFF_DXY");
  electronIDs.push_back("ELECTRON_HN_EFF_DZ");
  electronIDs.push_back("ELECTRON_HN_EFF_charge");
  electronIDs.push_back("ELECTRON_HN_EFF_conv");
  electronIDs.push_back("ELECTRON_HN_EFF_dxysig");
  electronIDs.push_back("ELECTRON_HN_EFF_iso");
  electronIDs.push_back("ELECTRON_HN_EFF_onlyiso");
  electronIDs.push_back("ELECTRON_HN_EFF_mva"); 
  electronIDs.push_back("ELECTRON_HN_EFF_pogmva");
  electronIDs.push_back(_e_tightid);
  electronIDs.push_back("ELECTRON_HN_TIGHT_8TeV");
  
  std::vector<snu::KTruth> truthColl= eventbase->GetTruth();
  
  int charge=0;

  bool passsel1=false;
  bool passsel2=false;
  int n_el=0;
  int ind_N=0;
  int ind_Nmother=0;
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(eventbase->GetTruth().at(i).IndexMother() <= 0)continue;
    if(fabs(eventbase->GetTruth().at(i).PdgId()) == 9900012){
      if(eventbase->GetTruth().at(i).GenStatus() ==22){
	ind_Nmother=eventbase->GetTruth().at(i).IndexMother();
	ind_N=i;
      }
      if(eventbase->GetTruth().at(i).GenStatus() < 65  && eventbase->GetTruth().at(i).GenStatus() > 50){
	ind_N=i;
        }
      
    }
  }
  
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(eventbase->GetTruth().at(i).IndexMother() <= 0)continue;
    
    if(fabs(eventbase->GetTruth().at(i).PdgId()) == 11 ){
      
      if(eventbase->GetTruth().at(i).IndexMother() == ind_N || eventbase->GetTruth().at(i).IndexMother() == ind_Nmother){
	if(eventbase->GetTruth().at(i).PdgId() < 0)charge++;
	else charge--;
	n_el++;
	if(!passsel1){
	  if(fabs(eventbase->GetTruth().at(i).Eta()) < 2.5 && eventbase->GetTruth().at(i).Pt() > 25.) {passsel1=true; continue;}
	}
	if(!passsel2){
	  if(fabs(eventbase->GetTruth().at(i).Eta()) < 2.5 && eventbase->GetTruth().at(i).Pt() > 15.) passsel2=true;
	}
      }
    }
  }

  if(charge !=0)FillEventCutFlow(2, "NoCut", w,lab);

  std::vector<snu::KElectron> electrons_veto = GetElectrons(true, true, "ELECTRON_HN_VETO");
  //  if(electrons_veto.size() > 2) return;


  //    cout << elid  << " " << electrons_eff.size() << " " << SameCharge(electrons_eff) << endl;
  for(unsigned int iid=0; iid < electronIDs.size(); iid++){
    TString elid = electronIDs[iid];
    std::vector<snu::KElectron> electrons_eff=GetElectrons(false,false,elid);

    if(!IsSignal()){
      if(iid < 10)continue;
    }  
    
    float ST (0.);
    if(electrons_eff.size() ==2)ST= electrons_eff[0].Pt() + electrons_eff[1].Pt();
    for(unsigned int ij=0; ij <jets.size(); ij++){ ST+= jets[ij].Pt();}
    for(unsigned int ij=0; ij < fatjets.size(); ij++){ST+= fatjets[ij].Pt();}
    ST+=eventbase->GetEvent().PFMET();
    
    if(SameCharge(electrons_eff) ){
      if(!(n_el==2 && passsel1 && passsel2)) continue;
      if(electronIDs[iid] == "ELECTRON_HN_EFF_PT")       FillEventCutFlow(2, "GEN_PTETA", w,lab);
      
      if(electrons_eff[0].Pt() < 25) continue;
      if(electrons_eff[1].Pt() < 15) continue;
      if(PassTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v")){
        if(electrons_eff[0].Pt() < 25 || electrons_eff[1].Pt() < 15) continue;
      }
      else continue;
      
      FillEventCutFlow(2, elid, w,lab);
      if(electronIDs[iid] == _e_tightid) {
	
	if(jets.size() > 0 || fatjets.size() > 0)           FillEventCutFlow(2, "Jet", w,lab);
	if(jets.size() > 1)  FillEventCutFlow(2, "DiJet", w,lab);
	if(fatjets.size() == 0){
	  if(jets.size() > 1)           FillEventCutFlow(2, "Jet1", w,lab);
	  if(jets.size() == 1)           FillEventCutFlow(2, "Jet2", w,lab);
	}
	else  FillEventCutFlow(2, "Jet3", w,lab);
	vector<int> ijet;
	float lljj_lm = GetMasses("lljj",electrons_eff, jets,fatjets,ijet, true);
	float jj_lm = GetMasses("jj",electrons_eff, jets,fatjets,ijet, true);
	float lljj_hm = GetMasses("lljj",electrons_eff, jets,fatjets,ijet, false);
        float jj_hm = GetMasses("jj",electrons_eff, jets,fatjets,ijet, false);
	
	
        float met2_st = pow(eventbase->GetEvent().PFMET(),2.)/ ST;
	
	if(jets.size() > 1)     {
	  
	  if( NBJet(jets) == 0){
	    if(eventbase->GetEvent().PFMET()< 30 && (GetDiLepMass(electrons_eff) > 10.) && lljj_lm < 200 && jj_lm < 120) FillEventCutFlow(2, "8TeV_LM", w,lab);
	    if(eventbase->GetEvent().PFMET()< 35 && (GetDiLepMass(electrons_eff) > 15.) && jj_hm > 50 && jj_hm < 110) FillEventCutFlow(2, "8TeV_HM", w,lab);
	    
	  }
	}
	
	if(fatjets.size() == 0){
	  
	  if(jets.size() > 1 ){
	    if( NBJet(jets) == 0){
	      if(eventbase->GetEvent().PFMET()< 80 && lljj_lm < 300) FillEventCutFlow(2, "13TeV_LM_SR1", w,lab);
	      if(met2_st < 15 && jj_hm < 150) FillEventCutFlow(2, "13TeV_HM_SR1", w,lab);
	    }
	  }
	}
	else{
	  if( NBJet(jets) == 0){
	    float j_hm = GetMasses("fj",electrons_eff, jets,fatjets,ijet, false);
	    
	    if(met2_st < 15 && j_hm < 150) FillEventCutFlow(2, "13TeV_HM_SR2", w,lab);
	  }
	  
	}
	if(fatjets.size() == 0){
	  
	  if(jets.size() == 1 ){
	    if( NBJet(jets) == 0){
	      float llj_lm = GetMasses("llj",electrons_eff, jets,fatjets,ijet, true);
	      if(eventbase->GetEvent().PFMET()< 80 && llj_lm < 300) FillEventCutFlow(2, "13TeV_LM_SR2", w,lab);
	    }
	  }
	}
      }
      if(electronIDs[iid] == "ELECTRON_HN_TIGHT_8TeV"){
	if(electrons_eff[1].Pt() > 15){
	  vector<int> ijet;
	  float lljj_lm = GetMasses("lljj",electrons_eff, jets,fatjets,ijet, true);
	  float jj_lm = GetMasses("jj",electrons_eff, jets,fatjets,ijet, true);
	  if(jets.size() > 1)     {
	    if( NBJet(jets) == 0){
	      if(eventbase->GetEvent().PFMET()< 30 && (GetDiLepMass(electrons_eff) > 15.) && lljj_lm < 200 && jj_lm < 120) FillEventCutFlow(2, "8TeV_OLDID_LM", w,lab);
	      if(eventbase->GetEvent().PFMET()< 80 && lljj_lm < 300) FillEventCutFlow(2, "13TeV_OLDID_LM", w,lab);
	    }
	  }
	  
	}
      }
    }
    
    
  } /// el IDs
}
vector<int>   HNDiElectron::GetTruthJets(){
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
  return i_jets;
}
vector<int>   HNDiElectron::FillTruthPlots(std::vector<snu::KJet> jets, std::vector<snu::KElectron> electrons, TString label){
  
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
	  FillHist(label+"_Truth_Lepton_FromW_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth lep_{W} P_{T}");
	  FillHist(label+"_Truth_Lepton_FromW_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth lep_{W} P_{T}");
	  FillHist(label+"_Truth_Lepton_FromW_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W}  #eta");
	  index_mu1=i;
	  float dR_genmu_reco_mu1 (999.);
	  float dR_genmu_reco_mu2 (999.);
	  if(electrons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(electrons[0]);
	  if(electrons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(electrons[1]);
	  
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

	FillHist(label+"_Truth_Lepton_FromW_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth lep_{W} P_{T}");
	FillHist(label+"_Truth_Lepton_FromW_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth lep_{W} P_{T}");
	FillHist(label+"_Truth_Lepton_FromW_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{W} #eta");
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
	if(electrons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(electrons[0]);
	if(electrons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(electrons[1]);
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

	FillHist(label+"_Truth_Lepton_FromN_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth lep_{N} P_{T} (GeV) ");
	FillHist(label+"_Truth_Lepton_FromN_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100,"Truth lep_{N} P_{T} (GeV) ");
	FillHist(label+"_Truth_Lepton_FromN_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth lep_{N} #eta ");
	
	
	float dR_genmu_reco_mu1 (999.);
        float dR_genmu_reco_mu2 (999.);
        if(electrons.size() > 0) dR_genmu_reco_mu1 = eventbase->GetTruth().at(i).DeltaR(electrons[0]);
        if(electrons.size() > 1) dR_genmu_reco_mu2 = eventbase->GetTruth().at(i).DeltaR(electrons[1]);
        FillHist(label+"_Truth_Lepton_FromN_eff",0., 1., 0., 2., 2, "Efficiency for truth -> reco l_{N}");
        if(dR_genmu_reco_mu1 < 0.4 || dR_genmu_reco_mu2 < 0.4){
          FillHist(label+"_Truth_Lepton_FromN_eff",1., 1., 0., 2., 2, "Efficiency for truth -> reco l_{N}");
	  n_matched_mu++;
	}
	
	float dRl1_l_N = 999.;
	if(electrons.size() > 0) dRl1_l_N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - electrons[0].Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() -  electrons[0].Phi()),2.) ); 
	float dRl2_l_N = 999.;
	if(electrons.size() > 1) dRl2_l_N= sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - electrons[1].Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() -  electrons[1].Phi()),2.) ); 
	
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
  if(electrons.size() ==2){
    if(jets.size()>1){
      FillHist(label+"_drX_electron",dRSum, 1., 0., 5., 25,"dR(X) (gen)");
      float drX = electrons[0].DeltaR(electrons[1])/ jets[0].DeltaR(jets[1]);
      FillHist(label+"_drX_reco_electron", drX, 1., 0., 4., 400,"dR(X) (reco)");

    }
    if(lep1_fromN) FillHist(label+"_Electron_From_N", 0,1.,0., 2., 2, "Reco_index lep_{N}"); 
    else FillHist(label+"_Electron_From_N", 1,1., 0., 2., 2, "Reco_index lep_{N}");
    FillHist(label+"_gen_matched_electron", n_matched_mu, 1., 0., 3., 3,"Number of gen matched electrons" );
    FillHist(label+"_lep1_lep2_reco_dR", electrons[0].DeltaR(electrons[1]),  1., 0., 5., 25,"#DeltaR(lep_{N},lep_{W}) (reco)");
    if (index_mu1 > 0 && index_mu2>0)     FillHist(label+"_lep1_lep2_dR", eventbase->GetTruth().at(index_mu1).DeltaR(eventbase->GetTruth().at(index_mu2)) , 1., 0., 5., 25,"#DeltaR(lep_{N},lep_{W}) (gen)");
    FillHist(label+"_mll", (electrons[0]+electrons[1]).M() , 1., 0., 150., 150,"m_{ll} (GeV)");
    
    
  }
  return i_jets;
}


int HNDiElectron::MatchedLeptonJets(std::vector<snu::KJet> jets,std::vector<snu::KFatJet> fatjets, std::vector<snu::KElectron> electrons, TString label, vector<int> i_jets){
  
  if(jets.size() == 1 ) {

    snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
    snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
    int matched_index=-1;
    if(jets[0].DeltaR(j1) < 0.5) matched_index=0;
    if(jets[0].DeltaR(j2) < 0.5) matched_index=1;
    
    FillHist("Matched_J_truth_lowmass"+label, matched_index, 1., -1., 2., 3,"Is W*->q(q) reco/truth matched");
  }
  if(jets.size()>=2 &&  electrons.size()==2){
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
        if(electrons.size() ==2)dijetmass_tmp = (jets[emme]+jets[enne] + electrons[0] + electrons[1]).M();
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

    if(jets.size()> 1){
      if(match)  FillHist("Matched_recoJJ_truth_lowmass"+label, 1, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
      else  FillHist("Matched_recoJJ_truth_lowmass"+label,0, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
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
  

    if(match && matchH) return 3;
    if(match) return 1;
    if(matchH) return 2;
    
  }
  return -1;

}


void HNDiElectron::FillEventCutFlow(TString cut, TString label, float weight){

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

void HNDiElectron::GetTriggEfficiency(float pt_cut, TString label){

  //ListTriggersAvailable();                                                              
  vector<int> pt1;
  pt1.push_back(25);
  pt1.push_back(20);
  pt1.push_back(120);
  pt1.push_back(28);
  pt1.push_back(30);

  vector<int>pt2;
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);


  std::vector<TString> lists_triggers;
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPTight_Gsf_v");

  
  std::vector<TString> lists_triggers2;
  lists_triggers2.push_back("");
  lists_triggers2.push_back("HLT_Ele27_eta2p1_WPTight_Gsf_v");

  std::vector<TString> lists_triggers3;
  lists_triggers3.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers3.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers3.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggers3.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
  lists_triggers3.push_back("HLT_Ele27_eta2p1_WPTight_Gsf_v");
  lists_triggers3.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v_HLT_Ele27_eta2p1_WPTight_Gsf_v");
  lists_triggers3.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_HLT_Ele27_eta2p1_WPTight_Gsf_v");
  lists_triggers3.push_back("HLT_Ele15_IsoVVVL_PFHT600_v_HLT_Ele27_eta2p1_WPTight_Gsf_v");
  lists_triggers3.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v_HLT_Ele27_eta2p1_WPTight_Gsf_v");
  lists_triggers3.push_back("HLT_Ele27_eta2p1_WPTight_Gsf_v_HLT_Ele27_eta2p1_WPTight_Gsf_v");



  for(unsigned int i=0; i < lists_triggers.size(); i++){
    for(unsigned int j=0; j < lists_triggers2.size(); j++){
      if(!lists_triggers2.at(j).Contains("HLT")) FillTriggerEfficiency(label,lists_triggers.at(i), weight, "denominator_nojet", lists_triggers3 );
      else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "denominator_nojet", lists_triggers3 );
      
    }
  }

  std::vector<snu::KJet> jets=GetJets("JET_HN");
  //std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_POG_TIGHT");
  std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_HN_TIGHTv4");

  if(jets.size() > 0){
    
    for(unsigned int j=0; j < lists_triggers2.size(); j++){
      for(unsigned int i=0; i < lists_triggers.size(); i++){
	if(!lists_triggers2.at(j).Contains("HLT"))             FillTriggerEfficiency(label,lists_triggers.at(i), weight, "denominator", lists_triggers3 );
	else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "denominator", lists_triggers3 );

	if(electrons.size() !=2)return;
	
	TString trig=lists_triggers.at(i);
	TString trig2=lists_triggers2.at(j);
	
	bool pass_trig = false;
	int pt_ind = i;
	
	if(j==0) pass_trig = PassTrigger(trig);
	else {
	  pass_trig = PassTrigger(trig) || PassTrigger(trig2);
	  if(PassTrigger(trig) && electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > pt2.at(i) && electrons.at(1).Pt() >  pt_cut){
	    pt_ind = i;
	  }
	  else {
	    if(!PassTrigger(trig) && pass_trig&&j==1) pt_ind=4; 
	  }
	}
	
	if(pass_trig){
	  if(!lists_triggers2.at(j).Contains("HLT"))  FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator",lists_triggers3 );
	  else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator",lists_triggers3 );
	  if(electrons.size() ==2) {
	    
	    if(!lists_triggers2.at(j).Contains("HLT"))  FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator_dielectron",lists_triggers3 );
	    else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator_dielectron",lists_triggers3 );
	  
	    
	    if(electrons.at(0).Pt() > pt1.at(pt_ind) && electrons.at(1).Pt() > pt2.at(pt_ind) && electrons.at(1).Pt() >  pt_cut)  {
	      if(!lists_triggers2.at(j).Contains("HLT"))FillTriggerEfficiency(label,lists_triggers.at(i), weight, "numerator_dielectron_pt",lists_triggers3 );
	      else FillTriggerEfficiency(label,lists_triggers.at(i)+"_"+lists_triggers2.at(j), weight, "numerator_dielectron_pt",lists_triggers3 );
	    }
		
	  }
	}
      }
    }
  }
}

void HNDiElectron::FillTriggerEfficiency(TString label2, TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label + label2)) {
    GetHist("TriggerEfficiency_"+label + label2)->Fill(cut,weight);    
  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label + label2,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label + label2)->GetXaxis()->SetBinLabel(it+1,list.at(it));
      GetHist("TriggerEfficiency_"+label + label2)->Fill(cut,weight);
    }
  }
  
}



bool HNDiElectron::CheckSignalRegion( bool isss,  std::vector<snu::KElectron> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KFatJet> fjets,   std::vector<snu::KJet> alljets, TString name, float w, int mode){

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
    if(mm.M()  < _ee_mll_presel_cut) {if(debug)cout << "Fail mee  " << endl; return false;}
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




bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool HNDiElectron::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  
  return true;

}


bool HNDiElectron::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
  
}

bool HNDiElectron::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
 
  return true;
}





void HNDiElectron::FillIDEff(snu::KElectron el, TString label){
  std::vector<snu::KElectron> electrons_tandp = GetElectrons(false, false, "ELECTRON_NOCUT");
  
  if(el.Pt() < 15.) return;
  if(fabs(el.Eta()) > 1.5){
    Float_t ptbins[11] = { 5., 12., 15.,20.,25.,30.,35.,45.,  60.,100., 200.};


    for(unsigned int i=0 ; i < 10; i++){
      FillHist("Electron_eff_dxy_all_"+label,0.01*float(i), 1.,-0.1, 0.1,10.,"eff_dxy");
      if(fabs(el.dxy()) < 0.01*float(i)){
	FillHist("Electron_eff_dxy_"+label, 0.01*float(i),1., -0.1, 0.1,10,"eff_dxy");
      }
    }
    for(unsigned int i=5 ; i < 10; i++){

      FillHist("Electron_eff_iso_all_"+label,0.01*float(i), 1.,0., 2.,20,"eff_iso");
      if(fabs(el.PFRelIso(0.3)) < 0.01*float(i)){
        FillHist("Electron_eff_iso_"+label, 0.01*float(i),1., 0., 2.,20,"eff_iso");
      }
    }


    if( fabs(el.Eta())< 1.479){


      FillHist(label+"_MVA1", el.MVA(), 1., -1., 1., 100, "MVA");
      for(unsigned int i=75 ; i < 100; i++){

	FillHist("Electron_eff_b_mva_all_"+label,0.01*float(i), 1.,0., 1.,100,"eff_mva");
	if(fabs(el.PFRelIso(0.3)) < 0.01*float(i)){
	  FillHist("Electron_eff_b_mva_"+label, 0.01*float(i),1., 0., 1.,100,"eff_mva");
	}
      }

      FillHist("Electron_b_probe"+label, el.Pt(),1., ptbins,10);
      if(PassID(el,"ELECTRON_MVA_TIGHT_mvaXX")){
        if( el.MVA()>0.76 ) FillHist("Electron_b_probe_pass_0.76"+label, el.Pt(),1., ptbins,10);
        if( el.MVA()>0.78 ) FillHist("Electron_b_probe_pass_0.78"+label, el.Pt(),1., ptbins,10);
        if( el.MVA()>0.80 ) FillHist("Electron_b_probe_pass_0.80"+label, el.Pt(),1., ptbins,10);
        if( el.MVA()>0.82 ) FillHist("Electron_b_probe_pass_0.82"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.84 ) FillHist("Electron_b_probe_pass_0.84"+label, el.Pt(),1., ptbins,10);
        if( el.MVA()>0.86 ) FillHist("Electron_b_probe_pass_0.86"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.88 ) FillHist("Electron_b_probe_pass_0.88"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.90 ) FillHist("Electron_b_probe_pass_0.90"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_POG_TIGHT")){
	FillHist("Electron_b_probe_pass_pogtight"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_MVA_TIGHT")){
	FillHist("Electron_b_probe_pass_mvatight"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_HN_TIGHT_LOOSEIP")){
	FillHist("Electron_b_probe_pass_hntight_looseip"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_HN_TIGHT_LOOSEIP2")){
	FillHist("Electron_b_probe_pass_hntight_looseip2"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_HN_TIGHT")){
        FillHist("Electron_b_probe_pass_hntight"+label, el.Pt(),1., ptbins,10);
      }
    }


    if( fabs(el.Eta())>1.479 ){
      FillHist(label+"_MVA2", el.MVA(), 1., -1., 1., 100, "MVA");
      for(unsigned int i=75 ; i < 100; i++){

        FillHist("Electron_eff_e_mva_all_"+label,0.01*float(i), 1.,0., 1.,100,"eff_mva");
        if(fabs(el.PFRelIso(0.3)) <0.01*float(i)){
          FillHist("Electron_eff_e_mva_"+label, 0.01*float(i),1., 0., 1.,100,"eff_mva");
        }
      }

      FillHist("Electron_probe"+label, el.Pt(),1., ptbins,10);
      if(PassID(el,"ELECTRON_MVA_TIGHT_mvaXX")){
	if( el.MVA()>0.76 ) FillHist("Electron_ec_probe_pass_0.76"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.78 ) FillHist("Electron_ec_probe_pass_0.78"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.80 ) FillHist("Electron_ec_probe_pass_0.80"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.82 ) FillHist("Electron_ec_probe_pass_0.82"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.84 ) FillHist("Electron_ec_probe_pass_0.84"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.86 ) FillHist("Electron_ec_probe_pass_0.86"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.88 ) FillHist("Electron_ec_probe_pass_0.88"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.90 ) FillHist("Electron_ec_probe_pass_0.90"+label, el.Pt(),1., ptbins,10);
      }

      if(PassID(el,"ELECTRON_POG_TIGHT")){
	FillHist("Electron_ec_probe_pass_pogtight"+label, el.Pt(),1., ptbins,10);
	}
      if(PassID(el,"ELECTRON_MVA_TIGHT")){
	FillHist("Electron_ec_probe_pass_mvatight"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_HN_TIGHT_LOOSEIP")){
	FillHist("Electron_ec_probe_pass_hntight_looseip"+label, el.Pt(),1., ptbins,10);
      }
      if(PassID(el,"ELECTRON_HN_TIGHT_LOOSEIP2")){
	FillHist("Electron_ec_probe_pass_hntight_looseip2"+label, el.Pt(),1., ptbins,10);
	}
      if(PassID(el,"ELECTRON_HN_TIGHT")){
	FillHist("Electron_ec_probe_pass_hntight"+label, el.Pt(),1., ptbins,10);
      }

      
      if(PassID(el,"ELECTRON_MVA_TIGHT_dxy2_mvaXX")){
	if( el.MVA()>0.76 ) FillHist("Electron_ec_probe_pass_dxy02_0.76"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.78 ) FillHist("Electron_ec_probe_pass_dxy02_0.78"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.80 ) FillHist("Electron_ec_probe_pass_dxy02_0.80"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.82 ) FillHist("Electron_ec_probe_pass_dxy02_0.82"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.84 ) FillHist("Electron_ec_probe_pass_dxy02_0.84"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.86 ) FillHist("Electron_ec_probe_pass_dxy02_0.86"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.88 ) FillHist("Electron_ec_probe_pass_dxy02_0.88"+label, el.Pt(),1., ptbins,10);
	if( el.MVA()>0.90 ) FillHist("Electron_ec_probe_pass_dxy02_0.90"+label, el.Pt(),1., ptbins,10);
	if(el.MissingHits()     ==0){
	  if( el.MVA()>0.76 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.76"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.78 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.78"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.80 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.80"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.82 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.82"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.84 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.84"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.86 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.86"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.88 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.88"+label, el.Pt(),1., ptbins,10);
	  if( el.MVA()>0.90 ) FillHist("Electron_ec_probe_pass_dxy02noMH_0.90"+label, el.Pt(),1., ptbins,10);
	  
	}
      }
    }
  }
}


bool HNDiElectron::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
}




void HNDiElectron::counter(TString cut, float w){

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


void HNDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

  for ( map<TString,float>::iterator itmapcounter = mapcounter.begin(); itmapcounter != mapcounter.end(); itmapcounter++){
    cout << itmapcounter->first << " has count "<< itmapcounter->second << endl;
  }

}


void HNDiElectron::BeginCycle() throw( LQError ){
  
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

HNDiElectron::~HNDiElectron() {
  
  Message("In HNDiElectron Destructor" , INFO);
  
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



