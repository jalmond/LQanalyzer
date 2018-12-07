// $id: RExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HN_pair_all.h"


//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to samevallow inheritance for use in LQCore/core classes
ClassImp (HN_pair_all);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HN_pair_all::HN_pair_all() :  AnalyzerCore() {
  
  mapcounter.clear();
  _mm_channel=false;
  _m_channel=false;
  _ee_channel=false;
  _e_channel=false;
  _em_channel=false;


  configure_fakes=true;

  // To have the correct name in the log:                                                                                                                            
  SetLogName("HN_pair_all");

  Message("In HN_pair_all constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  //InitialiseAnalysis();
  
}


void HN_pair_all::InitialiseAnalysis() throw( LQError ) {
  
  
  if(k_flags.size() > 0){

    if(k_flags[0] == "CutFlow")  functionality = HN_pair_all::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HN_pair_all::OPT;
    else functionality = HN_pair_all::ANALYSIS;
  }


  
  if(  functionality == HN_pair_all::ANALYSIS){
    /// Initialise histograms
    MakeHistograms();  
    MakeCleverHistograms(sighist_ee,"CR_Zmass_DiEle_central");
    MakeCleverHistograms(sighist_ee,"CR_ttbar1_DiEle_central");
    MakeCleverHistograms(sighist_ee,"CR_ttbar2_DiEle_central");
    MakeCleverHistograms(sighist_ee,"SR_DiEle_central");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_DiMu_central");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_hnss_DiMu_central");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_pog_DiMu_central");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_pog_DiMu_central_0jet");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_pog_DiMu_central_1jet");
    MakeCleverHistograms(sighist_mm,"CR_Zmass_pog_DiMu_central_2jet");
    MakeCleverHistograms(sighist_mm,"CR_ttbar1_DiMu_central");
    MakeCleverHistograms(sighist_mm,"CR_ttbar2_DiMu_central");
    MakeCleverHistograms(sighist_mm,"SR_DiMu_central");

    //
    // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
    // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
    //
    
    Message("Making clever hists for Z ->ll test code", INFO);
    
   
    
  }

  return;
}


void HN_pair_all::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  
  //// Set weight for MC (nevents / xsec (ish))
  if(!isData) weight*= MCweight;
  if(!isData)weight*= GetKFactor();
  if(!isData)weight*= MC_CR_Correction("HN_SS",0);


  // -- Set channel 
  _mm_channel =   isData ?  (k_channel.Contains("SingleMuon")) : true ;
  _ee_channel =   isData ?  (k_channel.Contains("DoubleEG")) : true ;

  
  // -- call truth particle
  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);
  
  //remove flavour mixing for signal samples
  if(RemoveFlavourMixing()) return;
  

  FillHist( "mZp_denom", 0., weight*WeightByTrigger("HLT_Mu50_v",TargetLumi),  0., 6000.,6000, "Z' Mass GeV");

  
  
  // ==== Define Systematic flag strings and order  
  const int N_systs = 16;
  
  TString syst_flags[N_systs] = {"ElEnUp", "ElEnDown","MuEnUp", "MuEnDown", "JESUp", "JESDown", "JERUp", "JERDown", "JMSUp", "JMSDown", "JMRUp","JMRDown", "ElResUp","ElResDown",  "MuResUp","MuResDown"}; 

  //// Default analysis cycle
  ExecuteEventFromSyst( "central", "" , "", "","");
  
  //// Default analysis cycle
  for(int i_syst = 0; i_syst < N_systs; i_syst++){
    if (syst_flags[i_syst].Contains("El")){
      ExecuteEventFromSyst( "Syst"+syst_flags[i_syst] , "Syst"+syst_flags[i_syst] , "", "","");
    }
    if (syst_flags[i_syst].Contains("Mu")){
      ExecuteEventFromSyst( "Syst"+syst_flags[i_syst] ,"", "Syst"+syst_flags[i_syst] , "", "");
    }
    if (syst_flags[i_syst].Contains("JE")){
      ExecuteEventFromSyst( "Syst"+ syst_flags[i_syst] ,"", "", "Syst"+ syst_flags[i_syst],syst_flags[i_syst] );
    }
  }
  
  //// Now add systematics that use central vectors
  ExecuteEventFromSyst( "PU_up", "" , "", "","");
  ExecuteEventFromSyst( "PU_down", "" , "", "","");

}

void HN_pair_all::ExecuteEventFromSyst(TString syst_label,TString el_syst, TString mu_syst, TString ak4_syst,  TString ak8syst){ 
  
  syst_label = "_"+syst_label;
  float ev_weight = weight;
  counter("NoCut_"+syst_label, ev_weight);

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts : 

  counter("EventCut", ev_weight);


  /// Apply trigger decision
  TString mu50_trig1 = "HLT_Mu50_v";
  TString mu50_trig2 = "HLT_TkMu50_v";
  vector<TString> mu50_trignames;
  mu50_trignames.push_back(mu50_trig1);
  mu50_trignames.push_back(mu50_trig2);

  TString diele_trig1="HLT_DoublePhoton60_v";
  
  bool mu50_pass = PassTriggerOR(mu50_trignames); // for mumu and emu channel
  bool diele_pass = PassTrigger(diele_trig1); // for ee channel



  // -- Get Veto Electrons, and store number of them

  std::vector<snu::KElectron> electrons_veto   = GetElectrons(TString("EL_HN_NN_Loose"),el_syst,35., 2.5);
  std::vector<snu::KElectron> electrons        = GetElectrons(false,false,TString("EL_HN_NN_Tight"),el_syst,65., 2.5);
  std::vector<snu::KElectron> electrons_all    = GetElectrons(false,false,TString(""),el_syst,10., 2.5);

  int N_veto_el = electrons_veto.size();
  int N_el = electrons.size();
  
  // -- Get Veto Muons, return if there are not exactly two veto muons

  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_NN_HighPt", true, mu_syst+"roch",10., 2.5);
  std::vector<snu::KMuon> muons = GetMuons("MUON_HN_NN_HighPt_TrkIso", false, mu_syst+"roch",10., 2.5);
  

  if(k_flags[0] == "FakeMC"){

    std::vector<snu::KMuon> muons_fake = GetMuons("MUON_HN_NN_HighPt_TrkIso", true, mu_syst+"roch",10., 2.5);
    std::vector<snu::KMuon> muons_null;
    if(muons.size() < 2) {
      muons = muons_fake;
    }
    else muons = muons_null;

    std::vector<snu::KElectron> electrons_fake = GetElectrons(true,true,TString("EL_HN_NN_Tight"),el_syst,65., 2.5);
    std::vector<snu::KElectron> electrons_null;
    if(electrons.size() < 2) {
      electrons = electrons_fake;
    }
    else electrons = electrons_null;

  }

  

  std::vector<snu::KMuon> muons_pog = GetMuons("MUON_POG_TIGHT", false, mu_syst+"roch",10., 2.5);
  std::vector<snu::KMuon> muons_pog2 = GetMuons("MUON_POG_TIGHT", false, mu_syst,10., 2.5);
  
  std::vector<snu::KMuon> muons_hn = GetMuons("MUON_HN_TIGHT", false, mu_syst+"roch",10., 2.5);

  CorrectedMETRochester(muons_veto);

  int N_veto_muon = muons_veto.size();
  int N_muon = muons.size();

  
  /// GetJets

  // -- Get AK8 jets away from leptons bt dR 1.                                                                                                                                 
  std::vector<snu::KFatJet> fatjets     = GetFatJets("HN_NN_JET", muons_veto,electrons_veto,syst_label,300., 2.7);
  

  // -- Get AK4 jets away from leptons and fatjets dR 0.4
  std::vector<snu::KJet> jets           = GetJetsAwayFromFatJet("HN_NN_JET", fatjets, muons_veto, electrons_veto,syst_label,40., 5.);
  //  std::vector<snu::KJet> jets_unshifted           = GetJetsAwayFromFatJet("HN_NN_JET", fatjets, muons_veto, electrons_veto,"",40., 5.);

  std::vector<snu::KJet> alljets        = GetJets("JET_PTETA",syst_label,20., 5.);


  
  // -- Call MET after correcting JMR
  CorrectedMETJMR(fatjets, jets);


  /// Set MET wit systematics accounted for
  double MET = eventbase->GetEvent().PFMET();
  double  METphi = eventbase->GetEvent().METPhi();
  
  if (syst_label=="central") MET = eventbase->GetEvent().PFMET();
  if (syst_label=="JESUp")     MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::JetEn, snu::KEvent::up);
  if (syst_label=="JESDown")     MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::JetEn, snu::KEvent::down);
  if (syst_label=="JERUp")     MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::JetRes, snu::KEvent::up);
  if (syst_label=="JERDown")     MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::JetRes, snu::KEvent::down);
  if (syst_label=="UnclusteredUp") MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::Unclustered, snu::KEvent::up);
  if (syst_label=="UnclusteredDown") MET = eventbase->GetEvent().PFMETShifted(snu::KEvent::Unclustered, snu::KEvent::down);

  if (syst_label.Contains("ElEnUp")){
    std::vector<snu::KElectron> electrons_noshift        = GetElectrons(false,false,TString("EL_HN_NN_Tight"),TString(""),65., 2.5);
    CorrectedMETElectron(1, electrons_noshift, MET, METphi);
  }
  if (syst_label.Contains("ElEnDown")){
    std::vector<snu::KElectron> electrons_noshift        = GetElectrons(false,false,TString("EL_HN_NN_Tight"),TString(""),65., 2.5);
    CorrectedMETElectron(-1,  electrons_noshift , MET, METphi);
  }
  if (syst_label.Contains("ElResUp")){
    std::vector<snu::KElectron> electrons_noshift        = GetElectrons(false,false,TString("EL_HN_NN_Tight"),TString(""),65., 2.5);
    CorrectedMETElectron(1, electrons_noshift, MET, METphi);
  }
  if (syst_label.Contains("EnResDown")){
    std::vector<snu::KElectron> electrons_noshift        = GetElectrons(false,false,TString("EL_HN_NN_Tight"),TString(""),65., 2.5);
    CorrectedMETElectron(-1,  electrons_noshift , MET, METphi);
  }


  if (syst_label.Contains("MuEnUp")) {
    std::vector<snu::KMuon> muons_noshift = GetMuons("MUON_HN_NN_HighPt_TrkIso", false, TString(""),10., 2.5);
    CorrectedMETMuon(1, muons_noshift, MET, METphi);

  }
  if (syst_label.Contains("MuEnDown")){
    std::vector<snu::KMuon> muons_noshift = GetMuons("MUON_HN_NN_HighPt_TrkIso", false, TString(""),10., 2.5);
    CorrectedMETMuon(-1, muons_noshift, MET, METphi);
  }
  
  /// change weight to scale to trigger lumiOB                                                                                                                                                  

  /// Make all hist without filling -999 means only hist are made, not filled (useful for plotting code)

  float ee_weight = ev_weight;
  float mm_weight = ev_weight;
  TString channel = "";
  if(_ee_channel){
    channel = "DiEle"+syst_label;
    if(diele_pass){
      ee_weight = ee_weight*WeightByTrigger(diele_trig1,TargetLumi);
      counter("HLT_DoublePhoton60_v", ee_weight);
      
      
      std::vector<KLepton> Leptons_veto;
      std::vector<KLepton> Leptons;
      Leptons_veto.clear();
      Leptons.clear();
      for(unsigned int i = 0; i < electrons_veto.size(); i++)    Leptons_veto.push_back(electrons_veto.at(i));
      for(unsigned int i = 0; i < muons_veto.size(); i++)    Leptons_veto.push_back(muons_veto.at(i));
      for(unsigned int i = 0; i < electrons.size(); i++)    Leptons.push_back(electrons.at(i));
      for(unsigned int i = 0; i < muons.size(); i++)    Leptons.push_back(muons.at(i));
      
      
      // CR Z  ee
      if(N_veto_muon == 0 && N_veto_el == 2 && N_el == 2){
	ee_weight *= EEWeight(syst_label, electrons, "EL_HN_NN_Tight");	
	
	// -- Dielectron 
	counter("DiEl"+syst_label, ee_weight);
	
	// --Pt cut
	if(electrons[1].Pt() > 65){
	  snu::KParticle ll = electrons[0] + electrons[1];
	  vector<snu::KParticle> Ns = RecoPairN(Leptons, fatjets, jets);
	  
	  // -- OS for CR                                                                                                                                                                                  	
	  if(!SameCharge(electrons)){
	    
	    // -- CR Z peak
	    if(fabs(ll.M() - 90.1) < 10.){
	      TString Region_str = "CR_Zmass_";
              if(Ns.size() ==2){
		snu::KParticle Zp = Ns.at(0) + Ns.at(1);
		FillHist( "mZp_" + Region_str + channel, Zp.M(), ee_weight,  0., 6000.,6000, "Z' Mass GeV");
		FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), ee_weight,  0., 5000,5000., "mN GeV");
		FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), ee_weight,  0., 5000,5000.,  "mN GeV");
	      }
	      counter(Region_str + channel, ee_weight);
	      FillCLHist(sighist_ee, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
	    } // end Z CR
	    
	    // -- CR TT one
	    if(fabs(ll.M()) > 55.){
	      int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
	      float MET = eventbase->GetEvent().PFMET();
	      
	      TString Region_str = "CR_ttbar1_";
	      
	      if(nbjet > 0 && MET > 40){ 
		counter(Region_str + channel, ee_weight);
		if(Ns.size() ==2){
		  snu::KParticle Zp = Ns.at(0) + Ns.at(1);
		  FillHist( "mZp_" + Region_str + channel, Zp.M(), ee_weight,  0., 6000.,6000, "Z' Mass GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), ee_weight,  0., 5000,5000., "mN GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), ee_weight,  0., 5000,5000.,  "mN GeV");
		}
		FillCLHist(sighist_ee, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
	      }
	    } // end tt CR 1

	    // -- CR TT two                                                                                                                                                                                 
            if(fabs(ll.M()) > 150.){
              int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
              float MET = eventbase->GetEvent().PFMET();
	      
              TString Region_str = "CR_ttbar2_";
	      
              if(nbjet > 1){
                counter(Region_str + channel, ee_weight);
                if(Ns.size() ==2){
		  snu::KParticle Zp = Ns.at(0) + Ns.at(1);
                  FillHist( "mZp_" + Region_str + channel, Zp.M(), ee_weight,  0., 6000.,6000, "Z' Mass GeV");
                  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), ee_weight,  0., 5000,5000., "mN GeV");
                  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), ee_weight,  0., 5000,5000.,  "mN GeV");
                }
		FillCLHist(sighist_ee, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
              }
            }
	    
	  }// end -- OS for CR        
	  
	  /// == SR
	  if(ll.M() > 150) {
	    vector<snu::KParticle> Ns = RecoPairN(Leptons, fatjets, jets);
	    if(Ns.size() ==  2){
	      snu::KParticle Zp = Ns.at(0) + Ns.at(1);
	      if(Ns.at(0).M() > 80 && Ns.at(1).M() > 80){
		if(Zp.M() > 300) {
		  TString Region_str = "SR_";
		  FillHist( "mZp_" + Region_str + channel, Zp.M(), ee_weight,  0., 6000.,6000, "Z' Mass GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), ee_weight,  0., 5000,5000., "mN GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), ee_weight,  0., 5000,5000.,  "mN GeV");
		  counter(Region_str + channel, ee_weight);
		  FillCLHist(sighist_ee,Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
		}
	      }
	    }
	  }
	} // // --Pt cut 
      } // // -- Diel
    } // // -- trigger
  } // end ee channel
  
  if(_mm_channel){
    
    std::vector<TString> triggerlist_DiMuon;
    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");
    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v");
    triggerlist_DiMuon.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v");
    if(PassTriggerOR(triggerlist_DiMuon)){

      channel = "DiMu"+syst_label;
      if(muons_hn.size() == 2 && N_veto_muon == 2 && N_veto_el == 0){
        if(muons_hn[1].Pt() > 25){
	  snu::KParticle ll = muons_hn[0] + muons_hn[1];
	  
          // -- OS for CR POG                                                                                                                                                                               
          float mmweight_hn = mm_weight;
          mmweight_hn*=  MMWeight(syst_label,muons, "MUON_HN_TIGHT",true);
	  mmweight_hn*=  WeightByTrigger(mu50_trig1,TargetLumi);

          if(!SameCharge(muons_hn)){
	    
            if(fabs(ll.M() - 90.1) < 10.){
              TString Region_str = "CR_Zmass_hnss_";
              if(syst_label.Contains("central")){
                FillCLHist(sighist_mm, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mmweight_hn);

              }
            }
          }
        }
      }
    }
    
      
    

    if(mu50_pass){
      channel = "DiMu"+syst_label;
      
      //ev_weight = ev_weight * max(WeightByTrigger(mu50_trig1,TargetLumi), WeightByTrigger(mu50_trig2,TargetLumi));
      mm_weight *= WeightByTrigger(mu50_trig1,TargetLumi);
      counter("HLT_Mu50_v", mm_weight);
      
      std::vector<KLepton> Leptons_veto;
      std::vector<KLepton> Leptons;
      Leptons_veto.clear();
      Leptons.clear();
      for(unsigned int i = 0; i < electrons_veto.size(); i++)    Leptons_veto.push_back(electrons_veto.at(i));
      for(unsigned int i = 0; i < muons_veto.size(); i++)    Leptons_veto.push_back(muons_veto.at(i));
      for(unsigned int i = 0; i < electrons.size(); i++)    Leptons.push_back(electrons.at(i));
      for(unsigned int i = 0; i < muons.size(); i++)    Leptons.push_back(muons.at(i));
      


      if(muons_pog.size() == 2 && N_veto_muon == 2 && N_veto_el == 0){

	if(muons_pog[1].Pt() > 25){
	  snu::KParticle ll = muons_pog[0] + muons_pog[1];

          // -- OS for CR POG
	  float mmweight_pog = mm_weight;
	  mmweight_pog*=  MMWeight(syst_label,muons, "MUON_POG_TIGHT",true); 
          if(!SameCharge(muons_pog)){

            if(fabs(ll.M() - 90.1) < 10.){
              TString Region_str = "CR_Zmass_pog_";
              if(syst_label.Contains("central")){
                FillCLHist(sighist_mm, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mmweight_pog);
		if(jets.size() ==0 ) FillCLHist(sighist_mm, Region_str + channel+"_0jet", eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mmweight_pog);
		else if(jets.size() ==1 ) FillCLHist(sighist_mm, Region_str + channel+"_1jet", eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mmweight_pog);
		else FillCLHist(sighist_mm, Region_str + channel+"_2jet", eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mmweight_pog);

	      }
	    }
	  }
	}
      }

      // CR Z  mm                                                                                                                                                                           
      if(N_veto_el == 0 && N_veto_muon == 2 && N_muon == 2){
	

	mm_weight *=  MMWeight(syst_label,muons, "MUON_HN_NN_HighPt_TrkIso",true);
	
	// -- DiMuon
	
	counter("DiMu", mm_weight);
	
	// --Pt cut                                                                                                                                                                                   
	if(muons[1].Pt() > 65){
	  snu::KParticle ll = muons[0] + muons[1];
	  
          // -- OS for CR	
          if(!SameCharge(muons)){
	    
	    vector<snu::KParticle> Ns = RecoPairN(Leptons, fatjets, jets);

	    
	    if(fabs(ll.M() - 90.1) < 10.){
	      TString Region_str = "CR_Zmass_";
	      
	      counter(Region_str + channel, mm_weight);
	      FillCLHist(sighist_mm, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mm_weight);

	      if(Ns.size() ==2){
		snu::KParticle Zp = Ns.at(0) + Ns.at(1);	
		FillHist( "mZp_" + Region_str + channel, Zp.M(), mm_weight,  0., 6000.,6000, "Z' Mass GeV");
		FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), mm_weight,  0., 5000.,5000, "mN GeV");
		FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), mm_weight,  0., 5000.,5000,  "mN GeV");
	      }
	    }
	    // Z CR
	    
	    // -- CR ttbar 1
	    if(fabs(ll.M()) > 55.){
	      
	      int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
	      float MET = eventbase->GetEvent().PFMET();
	      TString Region_str = "CR_ttbar1_";
	      
	      if(nbjet > 0 && MET > 40){
		counter(Region_str + channel, mm_weight);
		
		if(Ns.size() ==2){
		  snu::KParticle Zp = Ns.at(0) + Ns.at(1);
		  
		  FillHist( "mZp_" + Region_str + channel, Zp.M(), mm_weight,  0., 6000.,6000, "Z' Mass GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), mm_weight,  0., 5000.,5000, "mN GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), mm_weight,  0., 5000.,5000,  "mN GeV");
		}
		if(syst_label.Contains("central")){
		  FillCLHist(sighist_mm, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mm_weight);
		}
	      }
	    }

	    // -- CR ttbar 2                                                                                                                                                                                
            if(fabs(ll.M()) > 150.){

              int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
              float MET = eventbase->GetEvent().PFMET();
              TString Region_str = "CR_ttbar2_";

              if(nbjet > 1){
                counter(Region_str + channel, mm_weight);

                if(Ns.size() ==2){
		  snu::KParticle Zp = Ns.at(0) + Ns.at(1);

                  FillHist( "mZp_" + Region_str + channel, Zp.M(), mm_weight,  0., 6000.,6000, "Z' Mass GeV");
                  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), mm_weight,  0., 5000.,5000, "mN GeV");
                  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), mm_weight,  0., 5000.,5000,  "mN GeV");
                }
		FillCLHist(sighist_mm, Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mm_weight);
              }
            }

	  } // // -- OS for CR  
	  
	    /// == SR                                                                                                                                                                                   
          if(ll.M() > 150) {
            vector<snu::KParticle> Ns = RecoPairN(Leptons, fatjets, jets);
            if(Ns.size() == 2){
	      snu::KParticle Zp = Ns.at(0) + Ns.at(1);
              if(Ns.at(0).M() > 80 && Ns.at(1).M() > 80){
                if(Zp.M() > 300) {
                  TString Region_str = "SR_";
                  FillHist( "mZp_" + Region_str + channel, Zp.M(), mm_weight,  0., 6000.,6000, "Z' Mass GeV");
                  FillHist( "mN_" + Region_str + channel, Ns.at(0).M(), mm_weight,  0., 5000.,5000, "mN GeV");
		  FillHist( "mN_" + Region_str + channel, Ns.at(1).M(), mm_weight,  0., 5000.,5000,  "mN GeV");
		  counter(Region_str + channel, mm_weight);
		  
		  FillCLHist(sighist_mm,Region_str + channel, eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, mm_weight);
                }
              }
            }
          } // // --mass ll
	  
	}// // --Pt cut                                                                                                                                                                              
      } // // -- Diel                                                                                                                                                                                 
    } // // -- trigger       
  }
  
  return;
  
}

bool HN_pair_all::RemoveFlavourMixing(){
  //remove flavour mixing for signal samples                                                                                                                                                                                                  
  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);

  bool has_Nmix = false;
  int another_neutrino_1 = 9999999, another_neutrino_2 = 9999999;
  bool mumu_signal = std::find(k_flags.begin(), k_flags.end(), "hn_pair_mm") != k_flags.end();
  bool ee_signal = std::find(k_flags.begin(), k_flags.end(), "hn_pair_ee") != k_flags.end();
  bool tau_veto = std::find(k_flags.begin(), k_flags.end(), "tau_veto") != k_flags.end();
  if(mumu_signal){
    another_neutrino_1 = 9900016;
    another_neutrino_2 = 9900012;
  }
  if(ee_signal){
    another_neutrino_1 = 9900014;
    another_neutrino_2 = 9900016;
  }
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if( (abs(truthColl.at(i).PdgId()) == another_neutrino_1) || (abs(truthColl.at(i).PdgId()) == another_neutrino_2) ) has_Nmix = true;
  }
 
  return has_Nmix;
  
}


float HN_pair_all::EEWeight(TString syst_label, std::vector<snu::KElectron> electrons,TString id){
  
  if(isData) return 1.;
  
  double mc_weight = mcdata_correction->ElectronScaleFactor(id, electrons, 0);
  double electron_RecoSF =  mcdata_correction->ElectronRecoScaleFactor(electrons);
  mc_weight*= electron_RecoSF;


  float  puweight =1.;
  if(syst_label=="_PU_up"){
    puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),+1);
  }
  else if(syst_label=="_PU_down"){
    puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),-1);
  }
  else puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),-1);


  //puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);                                                                                                                                         
  mc_weight*= puweight;
  
  //std::vector<snu::KMuon> muons;
  //double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 0, 0);
  //double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 1, 0);
  //float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  //mc_weight*= trigger_sf;


  
  return mc_weight;
}

float HN_pair_all::EMWeight(TString syst_label, std::vector<snu::KElectron> electrons,std::vector<snu::KMuon> muons,TString idel, TString idmu){
  
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


float HN_pair_all::MMWeight(TString syst_label, std::vector<snu::KMuon> muons, TString id, bool passtrig){

  if(isData) return 1.;
  float mc_weight=mcdata_correction->MuonTrackingEffScaleFactor(muons);

  float puweight=1.;
  
  if(syst_label=="_PU_up"){
    puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),+1);
    }
  else if(syst_label=="_PU_down"){
    puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),-1);
  }
  else puweight = mcdata_correction->CatPileupWeight(eventbase->GetEvent(),-1);
  

  mc_weight*= puweight;

  /// ID issue                                                                                                                                                                                               
  if(id == "MUON_HN_TIGHT"){

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
  else  if(id== "MUON_POG_TIGHT"){

    double muon_id_sf = mcdata_correction->MuonScaleFactor(id, muons, 0);
    double muon_iso_sf = mcdata_correction->MuonISOScaleFactor(id, muons, 0);
    mc_weight*= muon_id_sf;
    mc_weight*= muon_iso_sf;
    
    std::vector<snu::KElectron> el;

    if(passtrig) mc_weight*= mcdata_correction->TriggerScaleFactor( el, muons, "HLT_Mu50_v", 0);

    return mc_weight;

    
  }
  
  double muon_id_sf = mcdata_correction->MuonScaleFactor(id, muons, 0);
  double muon_iso_sf = mcdata_correction->MuonISOScaleFactor(id, muons, 0);
  mc_weight*= muon_id_sf;
  mc_weight*= muon_iso_sf;

  std::vector<snu::KElectron> el;

  if(passtrig) mc_weight*= mcdata_correction->TriggerScaleFactor( el, muons, "HLT_Mu50_v", 0);

  return mc_weight;

}

vector<snu::KParticle> HN_pair_all::RecoPairN(std::vector<KLepton> lepptrs, vector<snu::KFatJet> fatjets, vector<snu::KJet> jets){

  vector<snu::KParticle> out;
  out.clear();

  
  if(fatjets.size()==0 && jets.size()>3 && lepptrs.size() == 2){

    snu::KParticle Dummy_AllJets = jets.at(0)+jets.at(1)+jets.at(2)+jets.at(3);

    double mindM = 999999999;
    snu::KParticle temp_N[2];

    for(int i=1; i<=3; i++){

      snu::KParticle TwoJet[2];
      TwoJet[0] = jets.at(0)+jets.at(i);
      TwoJet[1] = Dummy_AllJets-TwoJet[0];

      snu::KParticle N_00 = lepptrs.at(0)+TwoJet[0];
      snu::KParticle N_11 = lepptrs.at(1)+TwoJet[1];
      if( fabs(N_00.M()-N_11.M()) < mindM ){
        mindM = fabs(N_00.M()-N_11.M());
	temp_N[0] = N_00;
        temp_N[1] = N_11;
      }

      snu::KParticle N_01 = lepptrs.at(0)+TwoJet[1];
      snu::KParticle N_10 = lepptrs.at(1)+TwoJet[0];
      if( fabs(N_01.M()-N_10.M()) < mindM ){
	mindM = fabs(N_01.M()-N_10.M());
        temp_N[0] = N_01;
	temp_N[1] = N_10;
      }

    }

    out.push_back(temp_N[0]);
    out.push_back(temp_N[1]);

  }
  else if(fatjets.size()==1 && jets.size() > 1){

    if(lepptrs.size() == 1){

      snu::KParticle temp_N[2];

      snu::KFatJet fatjet = fatjets.at(0);
      temp_N[0] = fatjet;
      temp_N[1] = lepptrs.at(0) + jets.at(0) + jets.at(1);

      if(fatjet.DeltaR( lepptrs.at(0)) > 1.1) {
        out.push_back(temp_N[0]);
        out.push_back(temp_N[1]);
      }

    }

    if(lepptrs.size() == 2){
      snu::KParticle temp_N[2];

      snu::KFatJet fatjet = fatjets.at(0);
      if(fatjet.DeltaR( lepptrs.at(0) ) < fatjet.DeltaR( lepptrs.at(1) )){
        temp_N[0] = AddFatJetAndLepton(fatjet, lepptrs.at(0));
        temp_N[1] = lepptrs.at(1) + jets.at(0) + jets.at(1);
      }
      else{
        temp_N[0] = AddFatJetAndLepton(fatjet, lepptrs.at(1));
        temp_N[1] = lepptrs.at(0) + jets.at(0) + jets.at(1);
      }

      out.push_back(temp_N[0]);
      out.push_back(temp_N[1]);

    }


  }
  else if(fatjets.size()>1){

    if(lepptrs.size() == 0){
      snu::KParticle temp_N[2];

      temp_N[0] = fatjets.at(0);
      temp_N[1] = fatjets.at(1);

      out.push_back(temp_N[0]);
      out.push_back(temp_N[1]);
    }
    if(lepptrs.size() == 1){

      snu::KFatJet fatjet = fatjets.at(0);
      snu::KParticle temp_N[2];
      if(fatjet.DeltaR( lepptrs.at(0) ) < fatjet.DeltaR( lepptrs.at(0) )){
	temp_N[0] = AddFatJetAndLepton(fatjet, lepptrs.at(0));
        temp_N[1] = fatjets.at(1);
      }
      else{
        temp_N[0] = fatjet;
        temp_N[1] = AddFatJetAndLepton(fatjets.at(1), lepptrs.at(0));
      }
    }
    if(lepptrs.size() == 2){

      snu::KParticle temp_N[2];

      snu::KFatJet fatjet = fatjets.at(0); // Leading FatJet this time                                                                                                                                                                                                                                                                                                            

      if(fatjet.DeltaR( lepptrs.at(0) ) < fatjet.DeltaR( lepptrs.at(1) )){
        temp_N[0] = AddFatJetAndLepton(fatjet,        lepptrs.at(0));
        temp_N[1] = AddFatJetAndLepton(fatjets.at(1), lepptrs.at(1));
      }
      else{
        temp_N[0] = AddFatJetAndLepton(fatjets.at(1), lepptrs.at(0));
        temp_N[1] = AddFatJetAndLepton(fatjet,        lepptrs.at(1));
      }

      out.push_back(temp_N[0]);
      out.push_back(temp_N[1]);

    }


  }
  else{

  }
  
  return out;
  
  
  
}
 
 

void HN_pair_all::counter(TString cut, float w){

  map<TString,float>::iterator itmapcounter = mapcounter.find(cut) ;
  if (itmapcounter == mapcounter.end()){
    mapcounter[cut] = w;
  }
  else{
    float sum = itmapcounter->second;
    mapcounter[cut] = sum+w;
  }
  FillCutFlow(cut,w);
  //FillEventCutFlow(-1,cut,1);

}


void HN_pair_all::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

  for ( map<TString,float>::iterator itmapcounter = mapcounter.begin(); itmapcounter != mapcounter.end(); itmapcounter++){
    cout << itmapcounter->first << " has count "<< itmapcounter->second << endl;
  }

}


void HN_pair_all::BeginCycle() throw( LQError ){
  
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

HN_pair_all::~HN_pair_all() {
  
  Message("In HN_pair_all Destructor" , INFO);
  
}



void HN_pair_all::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HN_pair_all::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HN_pair_allCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HN_pair_all::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
}



