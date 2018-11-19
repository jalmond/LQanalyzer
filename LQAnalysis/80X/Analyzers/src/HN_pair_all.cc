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
  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;
  _ee_channel =   isData ?  (k_channel.Contains("DoubleEG")) : true ;

  
  // -- call truth particle
  std::vector<snu::KTruth> truthColl;
  eventbase->GetTruthSel()->Selection(truthColl);
  
  //remove flavour mixing for signal samples
  if(RemoveFlavourMixing()) return;
  
  
  
  // ==== Define Systematic flag strings and order  
  const int N_systs = 9;
  
  ExecuteEventFromSyst( "", "", "", "");

}

void HN_pair_all::ExecuteEventFromSyst(TString el_syst, TString mu_syst, TString ak4_syst,  TString ak8syst){ 

  float ev_weight = weight;
  counter("NoCut", ev_weight);

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
  std::vector<snu::KElectron> electrons        = GetElectrons(TString("EL_HN_NN_Tight"),el_syst,65., 2.5);
  std::vector<snu::KElectron> electrons_all    = GetElectrons(TString(""),el_syst,10., 2.5);

  int N_veto_el = electrons_veto.size();
  int N_el = electrons.size();
  
  // -- Get Veto Muons, return if there are not exactly two veto muons

  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_NN_HighPt", true, mu_syst,10., 2.5);
  std::vector<snu::KMuon> muons = GetMuons("MUON_HN_NN_HighPt_TrkIso", true, mu_syst,10., 2.5);
  CorrectedMETRochester(muons_veto);

  int N_veto_muon = muons_veto.size();
  int N_muon = muons.size();

  
  /// GetJets

  // -- Get AK8 jets away from leptons bt dR 1.                                                                                                                                 
  std::vector<snu::KFatJet> fatjets     = GetFatJets("HN_NN_JET", muons_veto,electrons_veto,"",300., 2.7);
  

  // -- Get AK4 jets away from leptons and fatjets dR 0.4
  std::vector<snu::KJet> jets           = GetJetsAwayFromFatJet("HN_NN_JET", fatjets, muons_veto, electrons_veto,"",40., 5.);

  std::vector<snu::KJet> alljets        = GetJets("JET_PTETA","",20., 5.);


  
  // -- Call MET after correcting JMR
  CorrectedMETJMR(fatjets, jets);
  float MET = eventbase->GetEvent().PFMET();
    


  /// change weight to scale to trigger lumiOB                                                                                                                                                  

  if(_ee_channel){
    if(diele_pass){
      ev_weight = ev_weight*WeightByTrigger(diele_trig1,TargetLumi);
      counter("HLT_DoublePhoton60_v", ev_weight);

  
      // CR Z  ee
      if(N_veto_muon == 0 && N_veto_el == 2 && N_el == 2){
	counter("DiEl", ev_weight);
	if(!SameCharge(electrons)){
	  if(electrons[1].Pt() > 65){
	    snu::KParticle ll = electrons[0] + electrons[1];
	    double M_ll = ll.M();
	    if(fabs(ll.M() - 90.1) < 10.){
	      float ee_weight = ev_weight* EEWeight(electrons, "EL_HN_NN_Tight");
	      counter("ZCR_HNPair", ev_weight);
	      
	      FillCLHist(sighist_ee, "ZCR_HNPair", eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
	      
	    }
	  }
	}
      }
      
      if(N_veto_muon == 0 && N_veto_el == 2 && N_el == 2){
	if(!SameCharge(electrons)){
	  if(electrons[1].Pt() > 65){
	    snu::KParticle ll = electrons[0] + electrons[1];
	    double M_ll = ll.M();
	    if(fabs(ll.M()) > 55.){
	      float ee_weight = ev_weight* EEWeight(electrons, "EL_HN_NN_Tight");
	      
	      int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
	      float MET = eventbase->GetEvent().PFMET();
	      
	      if(nbjet > 0 && MET > 40){ 
		counter("TTCR_HNPair", ev_weight);
		FillCLHist(sighist_ee, "TTCR_HNPair", eventbase->GetEvent(), muons_veto, electrons,jets, alljets, fatjets, ee_weight);
	      }
	    }
	  }
	}
      }
      
    }
  }
  
  if(_mm_channel){
    if(mu50_pass);

      ev_weight = ev_weight * max(WeightByTrigger(mu50_trig1,TargetLumi), WeightByTrigger(mu50_trig2,TargetLumi));

      counter("HLT_Mu50_v", ev_weight);


      // CR Z  mm                                                                                                                                                                           
      if(N_veto_el == 0 && N_veto_muon == 2 && N_muon == 2){
        counter("DiMu", ev_weight);
        if(!SameCharge(muons)){
          if(muons[1].Pt() > 65){
	    snu::KParticle ll = muons[0] + muons[1];
            double M_ll = ll.M();
            if(fabs(ll.M() - 90.1) < 10.){
              float ee_weight = ev_weight* MMWeight(muons, "EL_HN_NN_Tight");
              counter("ZCR_HNPair", ev_weight);

              FillCLHist(sighist_ee, "ZCR_HNPair", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets, ee_weight);

            }
          }
        }
      }

      if(N_veto_el == 0 && N_veto_muon == 2 && N_muon == 2){
        if(!SameCharge(muons)){
          if(muons[1].Pt() > 65){
	    snu::KParticle ll = muons[0] + muons[1];
            double M_ll = ll.M();
            if(fabs(ll.M()) > 55.){
              float ee_weight = ev_weight* MMWeight(muons, "EL_HN_NN_Tight");

              int nbjet=NBJet(GetJets("JET_PTETA","",20., 5.));
              float MET = eventbase->GetEvent().PFMET();

              if(nbjet > 0 && MET > 40){
                counter("TTCR_HNPair", ev_weight);
                FillCLHist(sighist_ee, "TTCR_HNPair", eventbase->GetEvent(), muons, electrons,jets, alljets, fatjets, ee_weight);
              }
            }
          }
        }
      }

    }
  }


  
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


float HN_pair_all::EEWeight(std::vector<snu::KElectron> electrons,TString id){
  
  if(isData) return 1.;
  
  double mc_weight = 1.;//;;mcdata_correction->ElectronScaleFactor(id, electrons, 0);
  // For test
  // if(mc_weight< 0.8) mc_weight=0.8;
  double electron_RecoSF =  mcdata_correction->ElectronRecoScaleFactor(electrons);
  mc_weight*= electron_RecoSF;

  float puweight=1.;
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  mc_weight*= puweight;
  
  //std::vector<snu::KMuon> muons;
  //double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 0, 0);
  //double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(electrons, id, muons, "muid", 1, 1, 0);
  //float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  //mc_weight*= trigger_sf;


  
  return mc_weight;
}

float HN_pair_all::EMWeight(std::vector<snu::KElectron> electrons,std::vector<snu::KMuon> muons,TString idel, TString idmu){
  
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


float HN_pair_all::MMWeight(std::vector<snu::KMuon> muons, TString id, bool passtrig){

  if(isData) return 1.;
  float mc_weight=mcdata_correction->MuonTrackingEffScaleFactor(muons);

  float puweight=1.;
  puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
  mc_weight*= puweight;

  /// ID issue                                                                                                                                                                                                                                                                  
  return mc_weight;

  double muon_id_iso_sf = mcdata_correction->MuonScaleFactor(id, muons, 0);
  mc_weight*= muon_id_iso_sf;

  std::vector<snu::KElectron> el;

  double trigger_eff_Data = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 0, 0, 0);
  double trigger_eff_MC = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 0, 1, 0);

  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  if(passtrig) mc_weight*= trigger_sf;


  return mc_weight;

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



