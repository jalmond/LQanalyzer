// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQElectronSF Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ElectronSF.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ElectronSF);

/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ElectronSF::ElectronSF() :  AnalyzerCore(),  out_electrons(0) {

  // To have the correct name in the log:                                                                                                                            
  SetLogName("ElectronSF");

  Message("In ElectronSF constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
  
}


void ElectronSF::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   return;
}


void ElectronSF::ExecuteEvents()throw( LQError ){
  
  
  if(!PassBasicEventCuts())  throw LQError( "Fails basic cuts",  LQError::SkipEvent );
  

  std::vector<TString> triggerslist;  
  triggerslist.push_back("HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass50_v");
  triggerslist.push_back("HLT_Ele20_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC4_Mass50_v");

  if(!PassTrigger(triggerslist, prescale)) return;

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) throw LQError( "Fails basic cuts",  LQError::SkipEvent );

  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()), 0)* MCweight;
  }
  
  std::vector<snu::KElectron> electronNoCutColl      = GetElectrons(true, true, "NoCut");

  std::vector<snu::KElectron> allelectrons;
  for(unsigned int iel = 0 ; iel < electronNoCutColl.size(); iel++){
    if(electronNoCutColl.at(iel).Et() < 10.) continue;
    if(fabs(electronNoCutColl.at(iel).Eta()) > 2.5) continue;
    allelectrons.push_back(electronNoCutColl.at(iel));
  }

  std::vector<snu::KTruth> truthColl = eventbase->GetTruth();
  
  vector<snu::KElectron>  electrons_fromZ;
  for(unsigned int ite = 0; ite < allelectrons.size(); ite++){
    bool  pass_truthmatching = false;
    for(unsigned int itr =0 ; itr < truthColl.size(); itr++){
      if(truthColl.at(itr).GenStatus() == 1){
        if(fabs(truthColl.at(itr).PdgId()) == 11) {
          if(truthColl.at(itr).IndexMother()  < 0 ) break;

          if(truthColl.at(itr).DeltaR(allelectrons.at(ite)) < 0.2){
	    int mother_index = itr;
	    int mother_pdgid = 11;
	    while (mother_pdgid == 11){
	      mother_index = truthColl.at(mother_index).IndexMother();
	      mother_pdgid = fabs(truthColl.at(mother_index).PdgId());
	    }
	    if(mother_pdgid ==23 || mother_pdgid == 22 ) pass_truthmatching = true;
	  }
	}
      }
    }
    if(k_isdata || pass_truthmatching) electrons_fromZ.push_back(allelectrons.at(ite));
  }
  

  //// Require 2 or more probe electrons + truth matched 
  if(electrons_fromZ.size() >= 2){
    
    for(unsigned int i=0;i<electrons_fromZ.size()-1;i++){
      for(unsigned int j=i+1;j<electrons_fromZ.size();j++){

	vector<snu::KElectron>  electron_probe_pair;
	electron_probe_pair.push_back(electrons_fromZ.at(i));
	electron_probe_pair.push_back(electrons_fromZ.at(j));
	if(Zcandidate(electron_probe_pair, 30., true)){
	  // pair of probes is OS and  60 < m(ee)   < 120
	  if(electron_probe_pair.at(0).Et() > 25. && fabs(electron_probe_pair.at(0).SCEta()) < 2.5 && eventbase->GetElectronSel()->HNIsTight(electron_probe_pair.at(0), eventbase->GetEvent().JetRho(),false)) {
	    
	    /// probe el 1 is TAG 
	    if( eventbase->GetElectronSel()->HNIsTight(electron_probe_pair.at(1), eventbase->GetEvent().JetRho(),false)){
	      FillNumerator(electron_probe_pair.at(1),GetEEMass(electron_probe_pair), weight);
	      FillPass(electron_probe_pair.at(1),GetEEMass(electron_probe_pair), weight);
	      FillDenominator(electron_probe_pair.at(1),GetEEMass(electron_probe_pair), weight);
	    }
	    else           {
	      FillDenominator(electron_probe_pair.at(1),GetEEMass(electron_probe_pair), weight);;
	      FillFail(electron_probe_pair.at(1),GetEEMass(electron_probe_pair), weight);
	    }
	  }
	  
	  if(electron_probe_pair.at(1).Et() > 25. && fabs(electron_probe_pair.at(1).SCEta()) < 2.5 && eventbase->GetElectronSel()->HNIsTight(electron_probe_pair.at(1), eventbase->GetEvent().JetRho(),false)) {
	    /// probe el 2 is TAG
            if(eventbase->GetElectronSel()->HNIsTight(electron_probe_pair.at(0), eventbase->GetEvent().JetRho(),false)){
              FillNumerator(electron_probe_pair.at(0),GetEEMass(electron_probe_pair), weight);
	      FillDenominator(electron_probe_pair.at(0),GetEEMass(electron_probe_pair), weight);
	      FillPass(electron_probe_pair.at(0),GetEEMass(electron_probe_pair), weight);
            }
            else             {
	      FillDenominator(electron_probe_pair.at(0),GetEEMass(electron_probe_pair), weight);
	      FillFail(electron_probe_pair.at(0),GetEEMass(electron_probe_pair), weight);
	    }
	  }
	}
      }
    }
  }
  


  return;
}// End of execute event loop




void ElectronSF::FillPass(snu::KElectron el, float mass, float w){

  Float_t ptbins[8] = { 0., 10., 15., 20., 30., 40., 50., 100.};
  float pt = el.Pt();
  if(pt > 100. && pt < 200.) pt = 99.;

  if(fabs(el.SCEta()) < 0.8)
    FillHist("Pass_eta1_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 1.4442)
    FillHist("Pass_eta2_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.)
    FillHist("Pass_eta3_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.5)
    FillHist("Pass_eta4_pt",pt,w,ptbins, 7);


  if(fabs(el.SCEta()) < 0.8){

    if(el.Pt() < 15.)  FillHist("Pass_eta1_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Pass_eta1_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Pass_eta1_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Pass_eta1_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Pass_eta1_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Pass_eta1_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) < 1.4442){

    if(el.Pt() < 15.)  FillHist("Pass_eta2_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Pass_eta2_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Pass_eta2_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Pass_eta2_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Pass_eta2_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Pass_eta2_pt6_mass", mass, w,  60.,120., 120);
  }
  
  else if(fabs(el.SCEta()) < 1.556){

    if(el.Pt() < 15.)  FillHist("Pass_eta3_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Pass_eta3_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Pass_eta3_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Pass_eta3_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Pass_eta3_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Pass_eta3_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) <2.){

    if(el.Pt() < 15.)  FillHist("Pass_eta4_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Pass_eta4_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Pass_eta4_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Pass_eta4_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Pass_eta4_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Pass_eta4_pt6_mass", mass, w,  60.,120., 120);
  }

  else if(fabs(el.SCEta()) < 2.5){

    if(el.Pt() < 15.)  FillHist("Pass_eta5_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Pass_eta5_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Pass_eta5_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Pass_eta5_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Pass_eta5_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Pass_eta5_pt6_mass", mass, w,  60.,120., 120);
  }

  return;

}

void ElectronSF::FillFail(snu::KElectron el, float mass, float w){

  Float_t ptbins[8] = { 0., 10., 15., 20., 30., 40., 50., 100.};
  float pt = el.Pt();
  if(pt > 100. && pt < 200.) pt = 99.;

  if(fabs(el.SCEta()) < 0.8)
    FillHist("Fail_eta1_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 1.4442)
    FillHist("Fail_eta2_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.)
    FillHist("Fail_eta3_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.5)
    FillHist("Fail_eta4_pt",pt,w,ptbins, 7);


  if(fabs(el.SCEta()) < 0.8){

    if(el.Pt() < 15.)  FillHist("Fail_eta1_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Fail_eta1_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Fail_eta1_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Fail_eta1_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Fail_eta1_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Fail_eta1_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) < 1.4442){

    if(el.Pt() < 15.)  FillHist("Fail_eta2_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Fail_eta2_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Fail_eta2_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Fail_eta2_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Fail_eta2_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Fail_eta2_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) < 1.556){

    if(el.Pt() < 15.)  FillHist("Fail_eta3_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Fail_eta3_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Fail_eta3_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Fail_eta3_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Fail_eta3_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Fail_eta3_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) <2.){

    if(el.Pt() < 15.)  FillHist("Fail_eta4_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Fail_eta4_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Fail_eta4_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Fail_eta4_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Fail_eta4_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Fail_eta4_pt6_mass", mass, w,  60.,120., 120);
  }
  
  else if(fabs(el.SCEta()) < 2.5){
    
    if(el.Pt() < 15.)  FillHist("Fail_eta5_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Fail_eta5_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Fail_eta5_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Fail_eta5_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Fail_eta5_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Fail_eta5_pt6_mass", mass, w,  60.,120., 120);
  }


  return;
}


void ElectronSF::FillDenominator(snu::KElectron el, float mass, float w){

  
  Float_t ptbins[8] = { 0., 10., 15., 20., 30., 40., 50., 100.};
  float pt = el.Pt();
  if(pt > 100. && pt < 200.) pt = 99.;
  
  if(fabs(el.SCEta()) < 0.8)
    FillHist("Den_eta1_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 1.4442) 
    FillHist("Den_eta2_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.)
    FillHist("Den_eta3_pt",pt,w,ptbins, 7);
  else if(fabs(el.SCEta()) < 2.5)
    FillHist("Den_eta4_pt",pt,w,ptbins, 7);
  

  if(fabs(el.SCEta()) < 0.8){

    if(el.Pt() < 15.)  FillHist("Den_eta1_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Den_eta1_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Den_eta1_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Den_eta1_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Den_eta1_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Den_eta1_pt6_mass", mass, w,  60.,120., 120);
  }
  else if(fabs(el.SCEta()) < 1.4442){

    if(el.Pt() < 15.)  FillHist("Den_eta2_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Den_eta2_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Den_eta2_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Den_eta2_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Den_eta2_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Den_eta2_pt6_mass", mass, w,  60.,120., 120);
  }
  
  else if(fabs(el.SCEta()) < 1.556){
    
    if(el.Pt() < 15.)  FillHist("Den_eta3_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Den_eta3_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Den_eta3_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Den_eta3_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Den_eta3_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Den_eta3_pt6_mass", mass, w,  60.,120., 120);
  }


  else if(fabs(el.SCEta()) <2.){

    if(el.Pt() < 15.)  FillHist("Den_eta4_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Den_eta4_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Den_eta4_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Den_eta4_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Den_eta4_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Den_eta4_pt6_mass", mass, w,  60.,120., 120);
  }
  
  else if(fabs(el.SCEta()) < 2.5){

    if(el.Pt() < 15.)  FillHist("Den_eta5_pt1_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 20.)  FillHist("Den_eta5_pt2_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 30.)  FillHist("Den_eta5_pt3_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 40.)  FillHist("Den_eta5_pt4_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 50.)  FillHist("Den_eta5_pt5_mass", mass, w,  60.,120., 120);
    else if(el.Pt() < 200.)  FillHist("Den_eta5_pt6_mass", mass, w,  60.,120., 120);
  }


  
}

void ElectronSF::FillNumerator(snu::KElectron el, float mass,  float w){
  
  Float_t ptbins[8] = { 0., 10., 15., 20., 30., 40., 50., 100.};
  float pt = el.Pt(); 
  if(pt> 100. && pt < 200.) pt= 99.;
  
 if(fabs(el.SCEta()) < 0.8)
   FillHist("Num_eta1_pt",pt,w,ptbins, 7);
 else if(fabs(el.SCEta()) < 1.4442)
   FillHist("Num_eta2_pt",pt,w,ptbins, 7);
 else if(fabs(el.SCEta()) < 1.556)
   FillHist("Num_eta3_pt",pt,w,ptbins, 7);
 else if(fabs(el.SCEta()) < 2.)
   FillHist("Num_eta4_pt",pt,w,ptbins, 7);
 else if(fabs(el.SCEta()) < 2.5)
   FillHist("Num_eta5_pt",pt,w,ptbins, 7);
 
 
 if(fabs(el.SCEta()) < 0.8){

   if(el.Pt() < 15.)  FillHist("Num_eta1_pt1_mass", mass, w, 60.,120., 120);
   else if(el.Pt() < 20.)  FillHist("Num_eta1_pt2_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 30.)  FillHist("Num_eta1_pt3_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 40.)  FillHist("Num_eta1_pt4_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 50.)  FillHist("Num_eta1_pt5_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 200.)  FillHist("Num_eta1_pt6_mass", mass, w,  60.,120., 120);
 }
 else if(fabs(el.SCEta()) < 1.4442){

   if(el.Pt() < 15.)  FillHist("Num_eta2_pt1_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 20.)  FillHist("Num_eta2_pt2_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 30.)  FillHist("Num_eta2_pt3_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 40.)  FillHist("Num_eta2_pt4_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 50.)  FillHist("Num_eta2_pt5_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 200.)  FillHist("Num_eta2_pt6_mass", mass, w,  60.,120., 120);
 }
 else if(fabs(el.SCEta()) < 1.556){

   if(el.Pt() < 15.)  FillHist("Num_eta3_pt1_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 20.)  FillHist("Num_eta3_pt2_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 30.)  FillHist("Num_eta3_pt3_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 40.)  FillHist("Num_eta3_pt4_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 50.)  FillHist("Num_eta3_pt5_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 200.)  FillHist("Num_eta3_pt6_mass", mass, w,  60.,120., 120);
 }

 else if(fabs(el.SCEta()) <2.){

   if(el.Pt() < 15.)  FillHist("Num_eta4_pt1_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 20.)  FillHist("Num_eta4_pt2_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 30.)  FillHist("Num_eta4_pt3_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 40.)  FillHist("Num_eta4_pt4_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 50.)  FillHist("Num_eta4_pt5_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 200.)  FillHist("Num_eta4_pt6_mass", mass, w,  60.,120., 120);
 }

 else if(fabs(el.SCEta()) < 2.5){
   
   if(el.Pt() < 15.)  FillHist("Num_eta5_pt1_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 20.)  FillHist("Num_eta5_pt2_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 30.)  FillHist("Num_eta5_pt3_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 40.)  FillHist("Num_eta5_pt4_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 50.)  FillHist("Num_eta5_pt5_mass", mass, w,  60.,120., 120);
   else if(el.Pt() < 200.)  FillHist("Num_eta5_pt6_mass", mass, w,  60.,120., 120);
 }


}


float ElectronSF::IsDiLep(std::vector<snu::KElectron> electrons){

  if(electrons.size() == 2 ){
    if(electrons.at(0).Pt() > 20.){
      if(electrons.at(1).Pt() > 15.){
	return 1.;
      }
    }
  }
  return 0.;
}

float ElectronSF::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip, bool useoldrates){

  if(electrons.size()!=2) return 0.;
  if(runchargeflip) {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()) {
      float cf1=  CFRate(electrons.at(0), useoldrates);
      float cf2=  CFRate(electrons.at(1),useoldrates);
      return ((cf1/(1.-cf1)) + (cf2/(1.-cf2)));
    }// OS requirement
    else return 0.;
  }// cf requirement
  else {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()) return 0.;
  }
  
  return 1.;
  
}

bool ElectronSF::CheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, TString name, float w){
  if(name.Contains("testetst") )w=1.; 
  if(electrons.size() != 2 ) return false ;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!SameCharge(electrons)) return false;
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(0) + jets.at(1) ;
  if(eejj.M()  > 200.) return false;

  snu::KParticle jj = jets.at(0) + jets.at(1) ;
  if(jj.M() > 120.) return false;
  if(jj.M() < 40.) return false;

  if(ee.M() > 80.) return false;
  if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  if(nbjet > 0) return false;

  return true;
}



bool ElectronSF::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool ElectronSF::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  

  if(additional_option.Contains("btag_t")) btagwp = 2; 
  if(additional_option.Contains("btag_l")) btagwp = 0; 
  bool cut_on_me2jj=true;
  if(additional_option.Contains("noMe2jj")) cut_on_me2jj= false;
  
  if(additional_option.Contains("basic")){
    if(electrons.size() != 2) return false;
    if(electrons.at(0).Pt() < 20.) return false;
    if(electrons.at(1).Pt() < 15.) return false;
    if(jets.size() < 2) return false;
    if(jets.at(0).Pt() < cuts.at(9)) return false;

    float wmassjj= 100000.;
    int indexj1=0;
    int indexj2=0;

    for(unsigned int ij=0; ij < jets.size()-1; ij++){
      for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
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
    if(evmet > 35.) return false;
    
    return true;
  }
  
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < cuts.at(0)) return false;
  if(electrons.at(1).Pt() < cuts.at(1)) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;

  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  float mass=ee.M();
  if(mass < cuts.at(2)) return false;
  if(mass > cuts.at(3)) return false;
  if(fabs(mass-90.) < 10.) return false;

  if(jets.at(0).Pt() < cuts.at(9)) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;

  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }


  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > cuts.at(5)) return false;
  if(jj.M() < cuts.at(4)) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;

  if(eejj.M()  > cuts.at(7)) return false;
  if(eejj.M()  < cuts.at(6)) return false;

  snu::KParticle e1jj = electrons.at(0)+ jets.at(indexj1) + jets.at(indexj2) ;
  //if(e1jj.M() > e1jjmax) return false;
  //if(e1jj.M() < e1jjmin) return false;

  snu::KParticle e2jj = electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  
  if(cut_on_me2jj){
    if(e2jj.M() > cuts.at(11)) return false;
    if(e2jj.M() < cuts.at(10)) return false;
  }

  if(evmet > cuts.at(8)) return false;

  int nbjet=0;
  float btagcut= 0.;
  if(btagwp==0) btagcut = 0.244;
  if(btagwp==1) btagcut = 0.679;
  if(btagwp==2) btagcut = 0.898;

  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > btagcut) nbjet++;
  }

  if(nbjet > 0) return false;

  return true;

}

bool ElectronSF::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 10.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;
  
  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
      snu::KParticle jjtmp = jets.at(ij) + jets.at(ij2) ;
      if(fabs(jjtmp.M() - 80.4) < wmassjj) {
        wmassjj = fabs(jjtmp.M() - 80.4);
        indexj1=ij;
        indexj2=ij2;
      }
    }
  }
  snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
  if(jj.M() > 120.) return false;

  snu::KParticle eejj = electrons.at(0) + electrons.at(1)+ jets.at(indexj1) + jets.at(indexj2) ;
  if(eejj.M() > 220.)return false;

  //if(eventbase->GetEvent().PFMET() > 30.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //if(nbjet > 0) return false;

  return true;
  
}

bool ElectronSF::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 30.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  if(jets.at(0).Pt() < 30.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
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

  
  //if(eventbase->GetEvent().PFMET() > 35.) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //if(nbjet > 0) return false;

  return true;
}


bool ElectronSF::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  if(electrons.size() != 2 ) return false;
  if(electrons.at(0).Pt() < 20.) return false;
  if(electrons.at(1).Pt() < 15.) return false;
  if(!runchargeflip){
    if(!SameCharge(electrons)) return false;
  }
  if(jets.size() < 2) return false;
  snu::KParticle ee = electrons.at(0) + electrons.at(1);
  if(ee.M()  < 40.) return false;
  if(fabs(ee.M()-90.)  < 10.) return false;

  float wmassjj= 100000.;
  int indexj1=0;
  int indexj2=0;
  for(unsigned int ij=0; ij < jets.size()-1; ij++){
    for(unsigned int ij2=ij+1; ij2 < jets.size(); ij2++){
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

  //  if(eventbase->GetEvent().PFMET() > 35.) return false;
  if(jets.at(0).Pt() < 40.) return false;
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  //  if(nbjet > 0) return false;

  return true;
}



void ElectronSF::CheckJetsCloseToLeptons(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  TString name){
  if(electrons.size() ==2  && jets.size() > 1) {
    if(SameCharge(electrons)) {
      snu::KParticle looseee = electrons.at(0) + electrons.at(1);
      if(fabs(looseee.M() - 90.) > 20. ){

	for(unsigned int ijet=0; ijet < jets.size(); ijet++){
	  for(unsigned int iel=0; iel < electrons.size(); iel++){
	    if( electrons[iel].DeltaR(jets.at(ijet)) < 0.5){
	      FillHist(("closejet" + name + "_ptdiff").Data(), (jets.at(ijet).Pt() - electrons.at(iel).Pt()) /  jets.at(ijet).Pt(), weight, -1. , 1., 50);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet").Data(), 1, weight, 0., 2., 2);
	      else FillHist(("closejet" + name + "_bjet").Data(), 0, weight, 0., 2., 2);
	      if(jets.at(ijet).CombinedSecVertexBtag() > 0.679) FillHist(("closejet" + name + "_bjet_nw").Data(), 1, 1., 0., 2., 2);
              else FillHist(("closejet" + name + "_bjet_nw").Data(), 0, 1., 0., 2., 2);
	      /// Jet usually vetoe
	      FillHist(("closejet/" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);
	      
	    }
	    else{
	      FillHist(("awayjet/" + name + "_NeutralEMEnergyFraction").Data(),jets.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_NeutralHadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ChargedEMEnergyFraction").Data(),jets.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ChargedHadEnergyFraction").Data(),jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_ElectronEnergyFraction").Data(),jets.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
              FillHist(("awayjet/" + name + "_HadEnergyFraction").Data(),jets.at(ijet).NeutralHadEnergyFraction()+ jets.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,200);

	    }
	  }
	}
      }
    }
  }
  return;
}


void ElectronSF::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << INFO << "Number of os mc events = " << m_os_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of os mc events (weighted) = " << m_os_Z  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events = " << m_ss_Z_nw  << LQLogger::endmsg; 
  m_logger << INFO << "Number of ss mc events (weighted)= " << m_ss_Z  << LQLogger::endmsg; 
}


void ElectronSF::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram_69400.root").c_str());
  
  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  
  DeclareVariable(k_met, "met", "MyTree");
  DeclareVariable(k_eemass, "ee_mass", "MyTree");
  DeclareVariable(k_eejjmass, "eejj_mass", "MyTree");
  DeclareVariable(k_e1jjmass, "e1jj_mass", "MyTree");
  DeclareVariable(k_e2jjmass, "e2jj_mass", "MyTree");
  DeclareVariable(k_njet, "njet", "MyTree");
  DeclareVariable(k_nbjet_l , "nbjet_l",  "MyTree");
  DeclareVariable(k_nbjet_m , "nbjet_m",  "MyTree");
  DeclareVariable(k_nbjet_t , "nbjet_t",  "MyTree");
  DeclareVariable(k_jjmass, "jj_mass", "MyTree");
  DeclareVariable(k_st, "st", "MyTree");
  DeclareVariable(k_ht, "ht", "MyTree");
  DeclareVariable(k_el1pt, "el1_pt", "MyTree");
  DeclareVariable(k_el2pt, "el2_pt", "MyTree");
  DeclareVariable(k_j1pt, "jet1_pt", "MyTree");
  DeclareVariable(k_weight, "weight", "MyTree");
  return;
  
}

ElectronSF::~ElectronSF() {
  
  Message("In ElectronSF Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
 }
     

void ElectronSF::FillEventCutFlow(TString cut, float weight){

  if(GetHist("eventcutflow")) {
    GetHist("eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms("eventcutflow",19,0.,19.);

    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(2,"NoCut_w");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(3,"EventCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(4,"TriggerCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(5,"VertexCut");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(6,"DiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(7,"eedR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(8,"SSDiEl");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(9,"SS_lepveto");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(10,"DiJet");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(11,"Presel");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(12,"Presel_noZ");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(13,"Presel_nobjet");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(14,"lowmass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(15,"lowmassCR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(16,"mediummass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(17,"mediummassCR");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(18,"highmass");
    GetHist("eventcutflow")->GetXaxis()->SetBinLabel(19,"highmassCR");
  }
  
}

     
void ElectronSF::FillCutFlow(TString cut, float weight){

  
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
     
     
void ElectronSF::FillIsoCutFlow(TString cut, float weight){
       
  
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


void ElectronSF::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ElectronSF::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ElectronSFCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ElectronSF::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}




//  LocalWords:  masscuts jetResdown
