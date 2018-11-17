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
HN_pair_all::HN_pair_all() :  AnalyzerCore(),  out_electrons(0) {
  
  mapcounter.clear();



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

void HN_pair_all::DoCutFlow(float w){

}


void HN_pair_all::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  
  //// Set weight for MC (nevents / xsec (ish))
  if(!isData) weight*= MCweight;
  if(!isData)weight*= GetKFactor();
  if(!isData)weight*= MC_CR_Correction("HN_SS",0);
  

  if(k_flags.size() > 0){
    
    if(k_flags[0] == "CutFlow")  functionality = HN_pair_all::CUTFLOW;
    else if(k_flags[0] == "OPT")  functionality = HN_pair_all::OPT;
    else functionality = HN_pair_all::ANALYSIS;
  }

  
  if(functionality==HN_pair_all::CUTFLOW){
    DoCutFlow(1.); return;
  }
  

}


float HN_pair_all::EEWeight(std::vector<snu::KElectron> electrons,TString id){
  
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
  double trigger_eff_MC_OR = mcdata_correction->TriggerEfficiencyLegByLeg(el, "elid", muons, id, 3, 1, 0);
  float trigger_sf = trigger_eff_Data/trigger_eff_MC;
  if(passtrig) mc_weight*= trigger_sf;


  return mc_weight;

}

bool HN_pair_all::Preselection(TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> el_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets, float ll_weight, vector<TString> trigs, float pt1, float pt2){
			      
  

  return true;
}

  


void HN_pair_all::FillPreselection(int nfake, TString label, vector<snu::KElectron> electrons, vector<snu::KElectron> electrons_veto, vector<snu::KMuon> muons,vector<snu::KJet> alljets, vector<snu::KJet> jets, vector<snu::KFatJet> fatjets,  float ll_weight, vector<TString> trig, float pt1, float pt2){
				  

}


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



bool HN_pair_all::PassHighMassBin1Window(float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
					

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

bool HN_pair_all::PassHighMassBin1(float pt1min, float pt2min, float ml2jjmin, float ml2jjmax, float mlljjmin,  float mjjmin, float mjjmax, float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st, bool debug){


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
 


bool HN_pair_all::PassHighMassBin2Window(float pt1max, float pt2max, float mllfjmin,  float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
				  
  
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


bool HN_pair_all::PassHighMassBin2(float pt1max, float pt2max, float ml2fjmin, float ml2fjmax,   float met2st, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet, float met2_st){
				  

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




bool HN_pair_all::PassLowMassBin1(float pt1max, float pt2max,float mjjmax, float mlljjmin,  float mlljjmax, float ml1jjmax, float ml2jjmax, float metmax, float mllmin, float mllmax, float pt2min, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KFatJet> fjets, int nbjet){
  

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


float HN_pair_all::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip){
  
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


void HN_pair_all::FillEventCutFlow(int cf,TString cut,  float wt, TString label){
  
  if(cf==0){
    if(GetHist( label+"ll_eventcutflow")) {
      GetHist( label+"ll_eventcutflow")->Fill(cut,wt);
      
    }
    else{
      AnalyzerCore::MakeHistograms( label+"ll_eventcutflow",15,0.,15.);

      GetHist( label+"ll_eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");

    }
  }
  if(cf==1){
    if(GetHist( label+"cutflow_challenge")) {
      GetHist( label+"cutflow_challenge")->Fill(cut,wt);
      
    }
    else{
      AnalyzerCore::MakeHistograms( label+"cutflow_challenge",11,0.,11.);

      GetHist( label+"cutflow_challenge")->GetXaxis()->SetBinLabel(1,"1_NoCut");
      
    }
  }
  if(cf==-1){
    if(GetHist( label+"noWeightcutflow_challenge")) {
      GetHist( label+"noWeightcutflow_challenge")->Fill(cut,wt);

    }
    else{
      
      AnalyzerCore::MakeHistograms( label+"noWeightcutflow_challenge",11,0.,11.);      
      GetHist( label+"noWeightcutflow_challenge")->Fill(cut,wt);
      
    }
  }
  

}

void  HN_pair_all::FillEfficiency(TString lab, vector<snu::KJet> jets,  vector<snu::KFatJet> fatjets,float w){


}



    
  }
  return -1;

}


void HN_pair_all::FillEventCutFlow(TString cut, TString label, float weight){

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

void HN_pair_all::GetTriggEfficiency(float pt_cut, TString label){

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

void HN_pair_all::FillTriggerEfficiency(TString label2, TString cut, float weight, TString label, std::vector<TString> list){

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



bool HN_pair_all::CheckSignalRegion( bool isss,  std::vector<snu::KElectron> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KFatJet> fjets,   std::vector<snu::KJet> alljets, TString name, float w, int mode){

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




bool HN_pair_all::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool HN_pair_all::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  
  return true;

}


bool HN_pair_all::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
  
}

bool HN_pair_all::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
 
  return true;
}





void HN_pair_all::FillIDEff(snu::KElectron el, TString label){
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


bool HN_pair_all::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
}



w
void HN_pair_all::counter(TString cut, float w){

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
  out_muons.clear();
  out_electrons.clear();
}



