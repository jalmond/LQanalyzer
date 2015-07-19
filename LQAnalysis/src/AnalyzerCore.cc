//$Id: AnalyzerCore.cc 1 2013-11-26 10:23:10 jalmond $
/***************************************************************************
 * @Project: LQAnalyzer Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes 
#include "AnalyzerCore.h"
#include "EventBase.h"

//Plotting                                                      
#include "MuonPlots.h"
#include "ElectronPlots.h"
#include "JetPlots.h"
#include "SignalPlots.h"


//ROOT includes
#include <TFile.h>


AnalyzerCore::AnalyzerCore() : LQCycleBase(), MCweight(-999.) {

  TH1::SetDefaultSumw2(true);  
  /// clear list of triggers stored in KTrigger
  triggerlist.clear();
  // If running on LQNtuples this is not important.
  // If creating an SKTree ntuple this controls what triggers are accessible
  
  // To have the correct name in the log:                                                                                                                            
  SetLogName("AnalyzerCore");

  Message("In AnalyzerCore constructor", INFO);
  
  TDirectory* origDir = gDirectory;
  /////////////////////////////////////////////////////////////////////// 
  //////// For HN analysis  /////////////////////////////////////////////  
  //////////////////////////////////////////////////////////////////////  
  //// FakeRate Input file           
  //////////////////////////////////////////////////////////////////////                                                                                                   
  string analysisdir = getenv("FILEDIR");

  TFile *infile_sf = TFile::Open((analysisdir+ "HMN_FinalSFNoJets.root").c_str());
  TDirectory* tempDir = getTemporaryDirectory();
  tempDir->cd();
 
  MuonSF =  dynamic_cast<TH2F*> (( infile_sf->Get("etavspt"))->Clone());
  infile_sf->Close();
  delete infile_sf;
  origDir->cd();
  
  string lqdir = getenv("LQANALYZER_DIR");

  m_fakeobj = new HNCommonLeptonFakes(lqdir+"/HNCommonLeptonFakes/share/");
  rmcor = new rochcor2012();

}

float AnalyzerCore::GetEEMass(std::vector<snu::KElectron> electrons){

  if(electrons.size() != 2) return 0.;
  snu::KParticle p = electrons.at(0) + electrons.at(1);
  return p.M();
}

void AnalyzerCore::FakeBkgBreakDown(std::vector<snu::KElectron> electrons, TString cut, float w){

  if(electrons.size() != 2) return;
  if(IsTight(electrons.at(0),  eventbase->GetEvent().JetRho()) &&  IsTight(electrons.at(1),  eventbase->GetEvent().JetRho())){
    FillHist(("FakeBkg/" + cut  + "_mass_TT").Data(),  GetEEMass(electrons), 1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_mass_TT_w").Data(),GetEEMass(electrons) , w,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_TT").Data(), electrons.at(1).Pt() , 1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_TT_w").Data(),electrons.at(1).Pt() , w,  0. , 100., 20);
  }
  if(IsTight(electrons.at(0),  eventbase->GetEvent().JetRho()) &&  !IsTight(electrons.at(1),eventbase->GetEvent().JetRho())){
    FillHist(("FakeBkg/" + cut  + "_mass_TL").Data(), GetEEMass(electrons) ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_mass_TL_w").Data(), GetEEMass(electrons) , w,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_TL").Data(), electrons.at(1).Pt() ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_TL_w").Data(), electrons.at(1).Pt() , w,  0. , 100., 20);
  }
  if(!IsTight(electrons.at(0),  eventbase->GetEvent().JetRho()) &&  IsTight(electrons.at(1),   eventbase->GetEvent().JetRho())){
    FillHist(("FakeBkg/" + cut  + "_mass_LT").Data(), GetEEMass(electrons) ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_mass_LT_w").Data(), GetEEMass(electrons) , w,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_LT").Data(), electrons.at(1).Pt() ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_LT_w").Data(), electrons.at(1).Pt() , w,  0. , 100., 20);
  }
  if(!IsTight(electrons.at(0),  eventbase->GetEvent().JetRho()) &&  !IsTight(electrons.at(1),  eventbase->GetEvent().JetRho())){
    FillHist(("FakeBkg/" + cut  + "_mass_LL").Data(),   GetEEMass(electrons) ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_mass_LL_w").Data() ,GetEEMass(electrons) , w,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_LL").Data(),   electrons.at(1).Pt() ,1.,  0. , 100., 20);
    FillHist(("FakeBkg/" + cut  + "_LL_w").Data(),electrons.at(1).Pt() , w,  0. , 100., 20);
  }
 

}


std::vector<snu::KJet> AnalyzerCore::GetJets(TString label){
  
  std::vector<snu::KJet> jetColl;
  if(label.Contains("NoLeptonVeto")){
    eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
    eventbase->GetJetSel()->SetPt(20.);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->Selection(jetColl);
  }
  else  if(label.Contains("loosest")){
    eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
    eventbase->GetJetSel()->SetPt(10.);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, GetMuons("veto"), GetElectrons(false,false, "veto"));
  }
  
  
  else  if(label.Contains("ApplyLeptonVeto")){
    eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
    eventbase->GetJetSel()->SetPt(20.);
    eventbase->GetJetSel()->SetEta(2.5);
    eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, GetMuons("veto"), GetElectrons(false,false, "veto"));
  }
  else if(label.Contains("ApplyPileUpID")){
    eventbase->GetJetSel()->JetHNSelection(jetColl,GetMuons("veto"), GetElectrons(false, false, "veto"));
    
  }
  
  return jetColl;
  
}


std::vector<snu::KMuon> AnalyzerCore::GetMuons(TString label){

  std::vector<snu::KMuon> muonColl;

  if(label.Contains("veto")){
    eventbase->GetMuonSel()->HNVetoMuonSelection(muonColl);
    return  GetTruePrompt(muonColl, true);
  }
  
  if(k_running_nonprompt) {
    if(label.Contains("tight_03")){
      eventbase->GetMuonSel()->HNLooseMuonSelection03(muonColl); 
    }
    else  if(label.Contains("tight_05")){
      eventbase->GetMuonSel()->HNLooseMuonSelection05(muonColl);
    }
    else 
      eventbase->GetMuonSel()->HNLooseMuonSelection(muonColl);

    return  muonColl;
  }

  if(label.Contains("tight")){
    eventbase->GetMuonSel()->HNTightMuonSelection(muonColl);
  }
  else if(label.Contains("NoCut")){
    eventbase->GetMuonSel()->Selection(muonColl);
  }
  

  return  GetTruePrompt(muonColl,  false);
  
}

std::vector<snu::KElectron> AnalyzerCore::GetElectrons(bool keepcf, bool keepfake, TString label){
  
  double dummy=1.;
  return GetElectrons(keepcf, keepfake, label, dummy);
}

std::vector<snu::KElectron> AnalyzerCore::GetElectrons(bool keepcf, bool keepfake, TString label, double& w){
  
  bool applyidsf= false;
  std::vector<snu::KElectron> electronColl;

  float dxy= 0.01; float biso= 0.09;    float eiso= 0.05;  bool usetight_id= true;

  int icoll(0);
  if(label.Contains("HNTight_loosereg2")){
    icoll++;
    applyidsf= true;
    /// This is the vector of electrons with optimie cuts
    std::vector<snu::KElectron> _electronColl;
    if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelection(_electronColl);
    else eventbase->GetElectronSel()->HNTightElectronSelection(_electronColl, false);
    electronColl =ShiftElectronEnergy(_electronColl, k_running_chargeflip);
  }

  else if(label.Contains("HNTight")){
    icoll++;
    applyidsf= true;
    /// This is the vector of electrons with optimie cuts
    std::vector<snu::KElectron> _electronColl;
    if(k_running_nonprompt) eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(_electronColl);
    else eventbase->GetElectronSel()->HNTightElectronSelection(_electronColl, false);

    electronColl =ShiftElectronEnergy(_electronColl, k_running_chargeflip);
  }
   
 
  /// Four loose samples 
  else if(label.Contains("loose_relaxipcut"))   {     icoll++; eventbase->GetElectronSel()->HNLooseElectronSelection(electronColl);}
  else if(label.Contains("loose_mediumID"))      {
    icoll++;
    std::vector<snu::KElectron> electronLooseColl;    
    eventbase->GetElectronSel()->HNLooseElectronSelection(false,false, 0.6, electronLooseColl);
    for(unsigned int ilooseel=0; ilooseel< electronLooseColl.size(); ilooseel++){
      if(fabs(electronLooseColl.at(ilooseel).dxy()) < 0.02) electronColl.push_back(electronLooseColl.at(ilooseel));
    }
  }
  else if(label.Contains("loose_susy")) {    icoll++;eventbase->GetElectronSel()->HNLooseElectronSelection(false, true, 0.6, electronColl);}
  else if(label.Contains("loose")){    icoll++; eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(electronColl);}

  // Veto cut
  else if(label.Contains("veto")){    icoll++; eventbase->GetElectronSel()->HNVetoElectronSelection(electronColl);}
  
  /// Standard pog ids or susy analysis id
  else if(label.Contains("id")){
    icoll++;
    applyidsf= true;
    if(label.Contains("medium")){biso = 0.10;   eiso = 0.10;    dxy= 0.02;      usetight_id = false;}
    if(label.Contains("tight")) {biso = 0.10;   eiso = 0.10;    dxy= 0.02;      usetight_id = true;}
    if(label.Contains("susy")) {biso = 0.09;    eiso = 0.09;    dxy= 0.01;      usetight_id = false;}
    
    std::vector<snu::KElectron> electronLooseColl;    
    eventbase->GetElectronSel()->HNLooseElectronSelection(usetight_id, false, 0.6,electronLooseColl);
    for(unsigned int ilooseel=0; ilooseel< electronLooseColl.size(); ilooseel++){
      if(!k_running_nonprompt){
	if(eventbase->GetElectronSel()->HNIsTight(electronLooseColl.at(ilooseel), eventbase->GetEvent().JetRho(), dxy, biso,eiso,  usetight_id)) electronColl.push_back(electronLooseColl.at(ilooseel));
      }
      else{
	if(eventbase->GetElectronSel()->HNIsTight(electronLooseColl.at(ilooseel), eventbase->GetEvent().JetRho(), dxy, 0.6,0.6, usetight_id)) electronColl.push_back(electronLooseColl.at(ilooseel));
      }
    }
  }
  

  else if(label.Contains("NoCutPtEta")){ 
    icoll++;
    eventbase->GetElectronSel()->SetPt(20.);
    eventbase->GetElectronSel()->SetEta(2.5);
    eventbase->GetElectronSel()->Selection(electronColl);
  }
  else if(label.Contains("NoCut")){     icoll++;eventbase->GetElectronSel()->Selection(electronColl);}
  
  else if(label.Contains("dxy")){
    icoll++;
    if(label.Contains("tight")) usetight_id = true;
    else usetight_id = false;
    TString looselabel = "loose_relaxipcut";
    if(!usetight_id) looselabel = "loose_medium_relaxipcut";
    std::vector<snu::KElectron> electronLooseColl = GetElectrons(keepcf, keepfake, looselabel);
    
    if(label.Contains("05"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.005; }
    if(label.Contains("10"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.010; }
    if(label.Contains("15"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.015; }
    if(label.Contains("20"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.020; }
    if(label.Contains("25"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.025; }
    if(label.Contains("30"))  {biso = 0.1;   eiso = 0.1;    dxy= 0.030; }
    
    for(unsigned int ilooseel=0; ilooseel< electronLooseColl.size(); ilooseel++){
      if(!k_running_nonprompt){
	if(eventbase->GetElectronSel()->HNIsTight(electronLooseColl.at(ilooseel), eventbase->GetEvent().JetRho(), dxy, biso, eiso, usetight_id)) electronColl.push_back(electronLooseColl.at(ilooseel));
      }
      else{
	electronColl.push_back(electronLooseColl.at(ilooseel));
      }
    }
  }

  else if(label.Contains("iso")){
    icoll++;
    if(label.Contains("tight")) usetight_id = true;
    else usetight_id = false;
    TString looselabel = "loose";
    if(!usetight_id) looselabel = "loose_medium";
    std::vector<snu::KElectron> electronLooseColl = GetElectrons(keepcf, keepfake, looselabel);
    
    dxy=0.01;
    if(label.Contains("iso_b150_e150")){biso = 0.150;  eiso = 0.150;      }
    if(label.Contains("iso_b150_e125")){biso = 0.150;  eiso = 0.125;      }
    if(label.Contains("iso_b150_e10")){biso = 0.15;    eiso = 0.10;      }    
    if(label.Contains("iso_b150_e09")){biso = 0.15;    eiso = 0.09;      }
    if(label.Contains("iso_b150_e08")){biso = 0.15;    eiso = 0.08;      }
    if(label.Contains("iso_b150_e07")){biso = 0.15;    eiso = 0.07;      }
    if(label.Contains("iso_b150_e06")){biso = 0.15;    eiso = 0.06;      }
    if(label.Contains("iso_b150_e05")){biso = 0.15;    eiso = 0.05;      }
    
    if(label.Contains("iso_b125_e125")){biso = 0.125;     eiso = 0.125;      }
    if(label.Contains("iso_b125_e10")) {biso = 0.125;     eiso = 0.10;      }
    if(label.Contains("iso_b125_e09")) {biso = 0.125;     eiso = 0.09;      }
    if(label.Contains("iso_b125_e08")) {biso = 0.125;     eiso = 0.08;      }
    if(label.Contains("iso_b125_e07")) {biso = 0.125;     eiso = 0.07;      }
    if(label.Contains("iso_b125_e06")) {biso = 0.125;     eiso = 0.06;      }
    if(label.Contains("iso_b125_e05")) {biso = 0.125;     eiso = 0.05;      }
    
    if(label.Contains("iso_b10_e125")){biso = 0.1;     eiso = 0.125;      }
    if(label.Contains("iso_b10_e10")) {biso = 0.1;     eiso = 0.10;      }
    if(label.Contains("iso_b10_e09")) {biso = 0.1;     eiso = 0.09;      }
    if(label.Contains("iso_b10_e08")) {biso = 0.1;     eiso = 0.08;      }
    if(label.Contains("iso_b10_e07")) {biso = 0.1;     eiso = 0.07;      }
    if(label.Contains("iso_b10_e06")) {biso = 0.1;     eiso = 0.06;      }
    if(label.Contains("iso_b10_e05")) {biso = 0.1;     eiso = 0.05;      }

    if(label.Contains("iso_b09_e125")){biso = 0.09;     eiso = 0.125;      }
    if(label.Contains("iso_b09_e10")) {biso = 0.09;     eiso = 0.10;      }
    if(label.Contains("iso_b09_e09")) {biso = 0.09;     eiso = 0.09;      }
    if(label.Contains("iso_b09_e08")) {biso = 0.09;     eiso = 0.08;      }
    if(label.Contains("iso_b09_e07")) {biso = 0.09;     eiso = 0.07;      }
    if(label.Contains("iso_b09_e06")) {biso = 0.09;     eiso = 0.06;      }
    if(label.Contains("iso_b09_e05")) {biso = 0.09;     eiso = 0.05;      }
    
    if(label.Contains("iso_b08_e125")){biso = 0.08;     eiso = 0.125;      }
    if(label.Contains("iso_b08_e10")) {biso = 0.08;     eiso = 0.10;      }
    if(label.Contains("iso_b08_e09")) {biso = 0.08;     eiso = 0.09;      }
    if(label.Contains("iso_b08_e08")) {biso = 0.08;     eiso = 0.08;      }
    if(label.Contains("iso_b08_e07")) {biso = 0.08;     eiso = 0.07;      }
    if(label.Contains("iso_b08_e06")) {biso = 0.08;     eiso = 0.06;      }
    if(label.Contains("iso_b08_e05")) {biso = 0.08;     eiso = 0.05;      }
    
    if(label.Contains("iso_b07_e125")){biso = 0.07;     eiso = 0.125;     }
    if(label.Contains("iso_b07_e10")) {biso = 0.07;     eiso = 0.10;      }
    if(label.Contains("iso_b07_e09")) {biso = 0.07;     eiso = 0.09;      }
    if(label.Contains("iso_b07_e08")) {biso = 0.07;     eiso = 0.08;      }
    if(label.Contains("iso_b07_e07")) {biso = 0.07;     eiso = 0.07;      }
    if(label.Contains("iso_b07_e06")) {biso = 0.07;     eiso = 0.06;      }
    if(label.Contains("iso_b07_e05")) {biso = 0.07;     eiso = 0.05;      }
    
    if(label.Contains("iso_b06_e125")){biso = 0.06;     eiso = 0.125;      }
    if(label.Contains("iso_b06_e10")) {biso = 0.06;     eiso = 0.10;      }
    if(label.Contains("iso_b06_e09")) {biso = 0.06;     eiso = 0.09;      }
    if(label.Contains("iso_b06_e08")) {biso = 0.06;     eiso = 0.08;      }
    if(label.Contains("iso_b06_e07")) {biso = 0.06;     eiso = 0.07;      }
    if(label.Contains("iso_b06_e06")) {biso = 0.06;     eiso = 0.06;      }
    if(label.Contains("iso_b06_e05")) {biso = 0.06;     eiso = 0.05;      }

    if(label.Contains("iso_b05_e125")){biso = 0.05;     eiso = 0.125;      }
    if(label.Contains("iso_b05_e10")) {biso = 0.05;     eiso = 0.10;      }
    if(label.Contains("iso_b05_e09")) {biso = 0.05;     eiso = 0.09;      }
    if(label.Contains("iso_b05_e08")) {biso = 0.05;     eiso = 0.08;      }
    if(label.Contains("iso_b05_e07")) {biso = 0.05;     eiso = 0.07;      }
    if(label.Contains("iso_b05_e06")) {biso = 0.05;     eiso = 0.06;      }
    if(label.Contains("iso_b05_e05")) {biso = 0.05;     eiso = 0.05;      }
    
    
    applyidsf= true;
    
    for(unsigned int ilooseel=0; ilooseel< electronLooseColl.size(); ilooseel++){
      if(!k_running_nonprompt){
	if(eventbase->GetElectronSel()->HNIsTight(electronLooseColl.at(ilooseel), eventbase->GetEvent().JetRho(), dxy, biso, eiso, usetight_id)) electronColl.push_back(electronLooseColl.at(ilooseel));
      }
      else{
	electronColl.push_back(electronLooseColl.at(ilooseel));
      }
    }
  }



  /*if(!isData){
    if(applyidsf){
      for(std::vector<snu::KElectron>::iterator it = electronColl.begin(); it != electronColl.end(); it++){
	w*= ElectronScaleFactor(it->Eta(), it->Pt(), usetight_id);
      }
    }
    }*/
  
  
  if(icoll != 1) {cout << "Error in GetElectrons " << endl; exit(0);}
  return  GetTruePrompt(electronColl, keepcf, keepfake); 
  
}


void AnalyzerCore::MakeEMUTriLeptonPlots(std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons, std::vector<snu::KJet> jets, TString jetid, float w) {

  if(electrons.size() ==  2 && (muons.size()== 1)) {
    if(electrons.at(0).Charge() != electrons.at(1).Charge()){
      snu::KParticle osee = electrons.at(0) + electrons.at(1);
      if(fabs(osee.M() - 90.) < 10.) {

	if(jets.size() > 1){

	  if(eventbase->GetEvent().PFMET() > 30){

	    FillCLHist(sighist, "TriLepEECR" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
	    FillCLHist(sighist, "TriLepCR" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
	  }
	}
      }
    }
    
  }
  
  if(electrons.size() ==  1 && (muons.size()== 2)) {

    if(muons.at(0).Charge() != muons.at(1).Charge()){
      snu::KParticle osee = muons.at(0) + muons.at(1);
      if(fabs(osee.M() - 90.) < 10.) {

        if(jets.size() > 1){
          if(eventbase->GetEvent().PFMET() > 30){
            FillCLHist(sighist, "TriLepMMCR" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
            FillCLHist(sighist, "TriLepCR" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
          }
        }
      }
    }

  }

}


void AnalyzerCore::MakeTriLeptonPlots(std::vector<snu::KElectron> electrons, std::vector<snu::KMuon> muons, std::vector<snu::KJet> jets, TString jetid, float w) {

  if(electrons.size() ==  3 && (muons.size()== 0)) {
    
    float charge1 = electrons.at(0).Charge();
    float charge2 = electrons.at(1).Charge();
    float charge3 = electrons.at(2).Charge();

    /// Find os pair
    snu::KParticle osee;
    float osmassdiff (0.);
    if(charge1 != charge2) {
      osee= electrons.at(0) + electrons.at(1);
      osmassdiff = fabs(osee.M() - 90.);
    }
    if(charge1 != charge3) {
      osee= electrons.at(0) + electrons.at(2);
      if(fabs(osee.M() - 90.) < osmassdiff) osmassdiff = fabs(osee.M() - 90.);
    }
    if(charge2 != charge3) {
      osee= electrons.at(1) + electrons.at(2);
      if(fabs(osee.M() - 90.) <osmassdiff) osmassdiff = fabs(osee.M() - 90.);
    }

    if(jets.size() > 1){
      if(eventbase->GetEvent().PFMET() > 30){
	if(osmassdiff < 10.){
	  FillCLHist(sighist, "TriElCR_dijet_highmet_osZW" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
	}
      }
    }

    if(osmassdiff <10.){
      if(jets.size() > 1){
	if(eventbase->GetEvent().PFMET() > 30){
	  if( (fabs(electrons.at(0).Eta() ) < 2.4) &&  (fabs(electrons.at(1).Eta() ) < 2.4) && (fabs(electrons.at(2).Eta() ) < 2.4)){
	    FillCLHist(sighist, "TriElCR_jet_osZW" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
	  }
	}
      }	

    }

    FillCLHist(sighist, "TriElCR" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
    if(jets.size() > 0)
      FillCLHist(sighist, "TriElCR1Jet" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
    
    if(jets.size() > 1){
      if(eventbase->GetEvent().PFMET() > 30){
	FillCLHist(sighist, "TriElCR_dijet_highmet" + jetid, eventbase->GetEvent(), muons,electrons,jets, w);
      }
    }
  }

  if(electrons.size() ==  4 && (muons.size()== 0) && jets.size() > 1 )
    FillCLHist(sighist, "ZZ" + jetid, eventbase->GetEvent(), muons, electrons,jets, w);
  
  
}


bool AnalyzerCore::HasCloseLBJet(snu::KElectron el){

  std::vector<snu::KJet> alljets = GetJets("NoLeptonVeto");

  bool cl = false;
  for(unsigned int ij =0; ij < alljets.size(); ij++){
    if(el.DeltaR(alljets.at(ij)) < 0.5){
      if(alljets.at(ij).CombinedSecVertexBtag() > 0.244) cl = true;
    }
  }

  return cl;

}

bool AnalyzerCore::HasCloseBJet(snu::KElectron el){

  std::vector<snu::KJet> alljets = GetJets("NoLeptonVeto");
  
  bool cl = false;
  for(unsigned int ij =0; ij < alljets.size(); ij++){
    if(el.DeltaR(alljets.at(ij)) < 0.5){
      if(alljets.at(ij).CombinedSecVertexBtag() > 0.679) cl = true;
    }
  }

  return cl;

}

void AnalyzerCore::RunMCCLosureTestEMU(TString label, std::vector<snu::KJet> jets, TString cut, float w){
  
  w=1;

  if(jets.size() <  2 ) return;
  if(!isData){
    if(k_running_nonprompt){
      TString looseregion = label;
      label = "HNTight_loosereg2";
      


      std::vector<snu::KElectron> electronAnalysisColl_mcclosure =  GetElectrons(false, true, label); 
      std::vector<snu::KMuon> MuonAnalysisColl_mcclosure =  GetMuons("loose");

      if(MuonAnalysisColl_mcclosure.size() == 1){
	if(MuonAnalysisColl_mcclosure.at(0).GetType() == 1 || MuonAnalysisColl_mcclosure.at(0).GetType() ==  2 ||MuonAnalysisColl_mcclosure.at(0).GetType() ==  3) {
	  FillHist(("MCEMUSSclosure_muon_fake"), 0., w, 0. , 2., 2);
	  if( IsTight(MuonAnalysisColl_mcclosure.at(0)))FillHist(("MCEMUSSclosure_muon_fake"), 1., w, 0. , 2., 2);
	}
	else {
	  FillHist(("MCEMUSSclosure_muon_nonfake"), 0., w, 0. , 2., 2);
          if( IsTight(MuonAnalysisColl_mcclosure.at(0)))FillHist(("MCEMUSSclosure_muon_nonfake"), 1., w, 0. , 2., 2);
	}
      }
      if(electronAnalysisColl_mcclosure.size() == 1){
	if(electronAnalysisColl_mcclosure.at(0).GetType() == 1 || electronAnalysisColl_mcclosure.at(0).GetType() ==  2 ||electronAnalysisColl_mcclosure.at(0).GetType() ==  3) {
          FillHist(("MCEMUSSclosure_electron_fake"), 0., w, 0. , 2., 2);
          if( IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()))FillHist(("MCEMUSSclosure_electron_fake"), 1., w, 0. , 2., 2);
        }
	else {
          FillHist(("MCEMUSSclosure_electron_nonfake"), 0., w, 0. , 2., 2);
          if( IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()))FillHist(("MCEMUSSclosure_electron_nonfake"), 1., w, 0. , 2., 2);
        }
      }

      if(electronAnalysisColl_mcclosure.size() == 1 && MuonAnalysisColl_mcclosure.size() == 1){
	
        //if((MuonAnalysisColl_mcclosure.at(0).GetType() == 1 || MuonAnalysisColl_mcclosure.at(0).GetType() ==  2 ||MuonAnalysisColl_mcclosure.at(0).GetType() ==  3)) return;
	   
        float mcclosure_weight = w;
	//if(electronAnalysisColl_mcclosure.at(0).Charge() == MuonAnalysisColl_mcclosure.at(0).Charge()){
	if(k_sample_name.Contains("W")||  (k_sample_name.Contains("tt") && (electronAnalysisColl_mcclosure.at(0).Charge() == MuonAnalysisColl_mcclosure.at(0).Charge()))){
          //  if(true){
          if(electronAnalysisColl_mcclosure.at(0).Pt() > 20. && MuonAnalysisColl_mcclosure.at(0).Pt() > 20.){
	    

	    /// weights using pt eta binning onlyGet_DataDrivenWeight
	    float fake_weight20 = w* Get_DataDrivenWeightMC_EM(MuonAnalysisColl_mcclosure,electronAnalysisColl_mcclosure,   eventbase->GetEvent().JetRho(),"20");
	    float fake_weight40 = w* Get_DataDrivenWeightMC_EM(MuonAnalysisColl_mcclosure,electronAnalysisColl_mcclosure,  eventbase->GetEvent().JetRho(),"40");
	    float fake_weight60 = w* Get_DataDrivenWeightMC_EM(MuonAnalysisColl_mcclosure,electronAnalysisColl_mcclosure,  eventbase->GetEvent().JetRho(),"60");

	    if(IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && IsTight(MuonAnalysisColl_mcclosure.at(0))){
	      
              FillHist((label + "MCEMUSSclosure_fake_measured"), 0., mcclosure_weight, 0. , 1., 1);
	      

	      if(eventbase->GetEvent().PFMET() < 30 &&   (NBJet(jets) ==0))               FillHist((label + "MCEMUSSclosure_top_fake_measured"), 0., mcclosure_weight, 0. , 1., 1);
		 
	    }

	    if(IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && IsTight(MuonAnalysisColl_mcclosure.at(0)))               FillHist("MCEMUSSclosure_fake_elt_mut", 0,1, 0. , 1, 1.);
	    if(IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && !IsTight(MuonAnalysisColl_mcclosure.at(0)))               FillHist("MCEMUSSclosure_fake_elt_mul", 0,1, 0. , 1, 1.);
	    if(!IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && IsTight(MuonAnalysisColl_mcclosure.at(0)))               FillHist("MCEMUSSclosure_fake_ell_mut", 0,1, 0. , 1, 1.);
	    if(!IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && !IsTight(MuonAnalysisColl_mcclosure.at(0)))               FillHist("MCEMUSSclosure_fake_ell_mul", 0,1, 0. , 1, 1.);



	    FillHist((label + "MCEMUSSclosure_fake_predicted_20"), 0., fake_weight20, 0. , 1., 1);
	    FillHist((label + "MCEMUSSclosure_fake_predicted_40"), 0., fake_weight40, 0. , 1., 1);
	    FillHist((label + "MCEMUSSclosure_fake_predicted_60"), 0., fake_weight60, 0. , 1., 1);
	    
	    if(eventbase->GetEvent().PFMET() < 30 &&  (NBJet(jets) ==0)) {
	      FillHist((label + "MCEMUSSclosure_top_fake_predicted_20"), 0., fake_weight20, 0. , 1., 1);
	      FillHist((label + "MCEMUSSclosure_top_fake_predicted_40"), 0., fake_weight40, 0. , 1., 1);
	      FillHist((label + "MCEMUSSclosure_top_fake_predicted_60"), 0., fake_weight60, 0. , 1., 1);
	    }

	  }
	}
      }
    }
  }
}

void AnalyzerCore::RunMCCLosureTest(TString label, std::vector<snu::KJet> jets, TString cut, float w){
  
  if(jets.size() <  2 ) return;
  if(!isData){
    if(k_running_nonprompt){
      
      TString looseregion = label;
      if(label.Contains("loosereg2")) label = "HNTight_loosereg2";
      else label = "HNTight";
      
      std::vector<snu::KElectron> electronAnalysisColl_mcclosure =  GetElectrons(false, true, label); // removes CF and fake in mc
      
      label+= cut;
      if(electronAnalysisColl_mcclosure.size() == 2){
	float mcclosure_weight = w;

	
	if(k_sample_name.Contains("QCD") || k_sample_name.Contains("W")||  (k_sample_name.Contains("tt") && SameCharge(electronAnalysisColl_mcclosure))){
	  //  if(true){
	  if(electronAnalysisColl_mcclosure.at(1).Pt() > 15.){
	    
	    bool closejet_el1=false;
            bool closejet_el2=false;

	    std::vector<snu::KJet> alljets = GetJets("NoLeptonVeto");
            for(unsigned int ij =0; ij < alljets.size(); ij++){
              if(electronAnalysisColl_mcclosure.at(0).DeltaR(alljets.at(ij)) < 0.5){
                if(alljets.at(ij).CombinedSecVertexBtag() > 0.679) closejet_el1 = true;
              }
              if(electronAnalysisColl_mcclosure.at(1).DeltaR(alljets.at(ij)) < 0.5){
                if(alljets.at(ij).CombinedSecVertexBtag() > 0.679) closejet_el2 = true;
              }
            }
	    

	    //// 1: pt eta binning

	    /// weights using pt eta binning only
	    float fake_weight20 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,   eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+looseregion, 0);
	    float fake_weight40 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+looseregion, 0);
	    float fake_weight60 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+looseregion, 0);
	    float fake_weight30 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+looseregion, 0);
	    
	    
	    //// 2: pt eta binning + bjet/no bjet

	    TString frbjet="b";
	    if(NBJet(jets) ==0) frbjet="nob";
	    float fake_weight20b = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20" + frbjet + "_"+looseregion, 0);
            float fake_weight40b = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40" + frbjet + "_"+looseregion, 0);
            float fake_weight60b = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,jets,   eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60" + frbjet + "_"+looseregion, 0);
            float fake_weight30b = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,jets,   eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30" + frbjet + "_"+looseregion, 0);
	    
	    
	    /// 3: ht eta binning

	    float fake_weight20h = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,  jets ,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_ht_"+looseregion, 0);
            float fake_weight40h = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,  jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_ht_"+looseregion, 0);
            float fake_weight60h = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,  jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_ht_"+looseregion, 0);
            float fake_weight30h = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure,  jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_ht_"+looseregion, 0);

	    /// 4 :  pt eta binning + bjet : flavour dep

	    TString btlabel= "BT"+looseregion;
            if(closejet_el1 && closejet_el2) btlabel += "cl1_cl2";
            if(!closejet_el1 && closejet_el2) btlabel += "cl2";
            if(closejet_el1 && !closejet_el2) btlabel += "cl1";
            btlabel += frbjet;

            float fake_weight20bt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20" + btlabel + "_"+looseregion, 0);
            float fake_weight40bt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets, eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40" + btlabel + "_"+looseregion, 0 );
            float fake_weight60bt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets, eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60" + btlabel + "_"+looseregion, 0);
            float fake_weight30bt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets, eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30" + btlabel + "_"+looseregion, 0);


	    /// 5 : ht vs eta : flavour dep
	    
	    TString htlabel= "HT"+looseregion;
	    if(closejet_el1 && closejet_el2) htlabel += "cl1_cl2";
	    if(!closejet_el1 && closejet_el2) htlabel += "cl2";
	    if(closejet_el1 && !closejet_el2) htlabel += "cl1";
	    
	    if(IsTight(electronAnalysisColl_mcclosure.at(0), eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl_mcclosure.at(1), eventbase->GetEvent().JetRho())) {
	      if(closejet_el2)FillHist(label + "mcclosure_TL_cb", 1, 1., 0.,2.,2);
	      else FillHist(label + "mcclosure_TL_cb", 0, 1., 0.,2.,2);

	      FillHist(label + "mcclosure_TL_faketype", electronAnalysisColl_mcclosure.at(1).GetType(), 1., 0.,8.,8);
	    }
	    if(!IsTight(electronAnalysisColl_mcclosure.at(0), eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl_mcclosure.at(1), eventbase->GetEvent().JetRho())) {
              if(closejet_el1)FillHist(label + "mcclosure_TL_cb", 1, 1., 0.,2.,2);
              else FillHist(label + "mcclosure_TL_cb", 0, 1., 0.,2.,2);
	      FillHist(label + "mcclosure_TL_faketype", electronAnalysisColl_mcclosure.at(0).GetType(), 1., 0.,8.,8);
            }
	    
	    
	    float fake_weight20ht = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+htlabel, 0);
            float fake_weight40ht = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+ htlabel, 0);
            float fake_weight60ht = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+ htlabel, 0);
            float fake_weight30ht = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+ htlabel, 0);



	    // 6: pt vs eta : flavour dep
	    TString ptlabel= "PT"+looseregion;
            if(closejet_el1 && closejet_el2) ptlabel += "cl1_cl2";
            if(!closejet_el1 && closejet_el2) ptlabel += "cl2";
            if(closejet_el1 && !closejet_el2) ptlabel += "cl1";

            float fake_weight20pt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets ,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+ptlabel, 0);
            float fake_weight40pt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+ ptlabel, 0);
            float fake_weight60pt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+ ptlabel, 0);
            float fake_weight30pt = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+ ptlabel, 0);


	    // 7: pt vs eta vs ht vs nbjet : flavour dep 
	    TString stlabel= "ST"+looseregion;
            if(closejet_el1 && closejet_el2) stlabel += "cl1_cl2";
            if(!closejet_el1 && closejet_el2) stlabel += "cl2";
            if(closejet_el1 && !closejet_el2) stlabel += "cl1";
	    stlabel+=frbjet;
	    

	    float fake_weight20st = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+stlabel, 0);
            float fake_weight40st = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+ stlabel, 0);
            float fake_weight60st = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+ stlabel, 0);
            float fake_weight30st = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+ stlabel, 0);

	    
	    // 8:  pt vs eta vs ht : flavour dep
	    TString st2label= "ST"+looseregion;
            if(closejet_el1 && closejet_el2) st2label += "cl1_cl2";
            if(!closejet_el1 && closejet_el2) st2label += "cl2";
            if(closejet_el1 && !closejet_el2) st2label += "cl1";
	    
            if(SumPt(jets) < 100.) st2label +=  "ht1";
            else st2label +=  "ht3";

            float fake_weight20st2 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets ,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+st2label, 0);
            float fake_weight40st2 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+ st2label, 0);
            float fake_weight60st2 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+ st2label, 0);
            float fake_weight30st2 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+ st2label, 0);
	    
	    // 9:  pt vs eta vs ht 
            TString st3label= "";
            if(SumPt(jets) < 100.) st3label +=  "ht1_";
            else st3label +=  "ht3_";
	    st3label += looseregion;

            float fake_weight20st3 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets ,  eventbase->GetEvent().JetRho(), true, 0.01,0.09  ,0.05,  "mc_20_"+st3label, 0);
            float fake_weight40st3 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true, 0.01,0.09,0.05, "mc_40_"+ st3label, 0);
            float fake_weight60st3 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_60_"+ st3label, 0);
            float fake_weight30st3 = w* Get_DataDrivenWeight_EE(electronAnalysisColl_mcclosure, jets , eventbase->GetEvent().JetRho(), true,0.01,0.09,0.05,"mc_30_"+ st3label, 0);

	    bool el1_fake=false;
	    bool el2_fake=false;
	    if(electronAnalysisColl_mcclosure.at(0).GetType() == 1 || electronAnalysisColl_mcclosure.at(0).GetType() == 2 || electronAnalysisColl_mcclosure.at(0).GetType() == 3 || electronAnalysisColl_mcclosure.at(0).GetType() == 6 || electronAnalysisColl_mcclosure.at(0).GetType() ==8 ){
	      
	      if(IsTight(electronAnalysisColl_mcclosure.at(0), eventbase->GetEvent().JetRho())) FillHist(label + "mcclosure_el1_fake_checktight", 1, 1., 0.,2.,2);
              else FillHist(label + "mcclosure_el1_fake_checktight", 0, 1.,0.,2.,2);
	      
	      el1_fake= true;
	      if(closejet_el1)
		FillHist(label + "mcclosure_cbj_el", 1 , 1.,  0. , 2, 2);
	      else
		FillHist(label + "mcclosure_cbj_el", 0 , 1.,  0. , 2, 2);
	    }	    
	    if(electronAnalysisColl_mcclosure.at(1).GetType() == 1 || electronAnalysisColl_mcclosure.at(1).GetType() == 2 || electronAnalysisColl_mcclosure.at(1).GetType() == 3 || electronAnalysisColl_mcclosure.at(1).GetType() == 6 || electronAnalysisColl_mcclosure.at(0).GetType() ==8){
	      el2_fake= true;
	      if(IsTight(electronAnalysisColl_mcclosure.at(1), eventbase->GetEvent().JetRho())) FillHist(label + "mcclosure_el2_fake_checktight", 1, 1.,0.,2.,2);
              else FillHist(label + "mcclosure_el2_fake_checktight", 0, 1.,0.,2.,2);
	      
	      if(closejet_el2)
		FillHist(label + "mcclosure_cbj_el", 1 , 1.,  0. , 2, 2);
	      else
		FillHist(label + "mcclosure_cbj_el", 0 , 1.,  0. , 2, 2);
	    }
	    

	    if(el1_fake )   FillHist(label + "mcclosure_realevent_type", electronAnalysisColl_mcclosure.at(0).GetType() , 1., 0., 8., 8);	    
	    if(el2_fake)   FillHist(label + "mcclosure_realevent_type", electronAnalysisColl_mcclosure.at(1).GetType() , 1., 0., 8., 8);	    
	    
	    
	    if(el1_fake &&el2_fake)   FillHist(label + "mcclosure_trueevent_type", 0., 1., 0., 3., 3);
	    if(!el1_fake &&el2_fake)   FillHist(label + "mcclosure_trueevent_type", 1., 1., 0., 3., 3);
	    if(el1_fake &&!el2_fake)   FillHist(label + "mcclosure_trueevent_type", 1., 1., 0., 3., 3);
	    if(!el1_fake &&!el2_fake)   FillHist(label + "mcclosure_trueevent_type", 2., 1., 0., 3., 3);
	    
	    
	    FakeBkgBreakDown(electronAnalysisColl_mcclosure, "mcclosure",fake_weight60); 
	    
	    if(IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl_mcclosure.at(1),   eventbase->GetEvent().JetRho()) ){
	      
	      FillHist(label + "mcclosure_event_breakdown_tt", 0., 1., 0., 1., 1);
	      FillHist((label + "MCSSclosure_fake_pt_measured"), electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 400., 20);
	      FillHist((label + "MCSSclosure_fake_njet_measured"), jets.size(), mcclosure_weight, 0. , 10., 10);
	      FillHist((label + "MCSSclosure_fake_measured"), 0., mcclosure_weight, 0. , 1., 1);
	      FillHist((label + "MCSSclosure_fake_nbjet_measured"), NBJet(jets), mcclosure_weight, 0. , 4., 4);
	      FillHist((label + "MCSSclosure_fake_ht_measured"), SumPt(jets), mcclosure_weight, 0. , 1000., 40);
	      FillHist((label + "MCSSclosure_fake_eta_measured"), electronAnalysisColl_mcclosure.at(1).Eta(), mcclosure_weight, -2.5 , 2.5, 4);
	      FillHist((label + "MCSSclosure_fake_eta_measured"), electronAnalysisColl_mcclosure.at(0).Eta(), mcclosure_weight, -2.5 , 2.5, 4);

	      if(closejet_el1 || closejet_el2){
		FillHist((label + "MCSSclosure_fakecb_njet_measured"), jets.size(), mcclosure_weight, 0. , 10., 10);
		FillHist((label + "MCSSclosure_fakecb_ht_measured"), SumPt(jets), mcclosure_weight, 0. , 1000., 40);
		FillHist((label + "MCSSclosure_fakecb_measured"), 0., mcclosure_weight, 0. , 1., 1);
	      }
	      else{
                FillHist((label + "MCSSclosure_fakenocb_njet_measured"), jets.size(), mcclosure_weight, 0. , 10., 10);
                FillHist((label + "MCSSclosure_fakenocb_ht_measured"), SumPt(jets), mcclosure_weight, 0. , 1000., 40);
		FillHist((label + "MCSSclosure_fakenocb_nbjet_measured"), NBJet(jets), mcclosure_weight, 0. , 4., 4);
		FillHist((label + "MCSSclosure_fakenocb_pt_measured"),  electronAnalysisColl_mcclosure.at(1).Pt(), mcclosure_weight, 0. , 400., 20);
		FillHist((label + "MCSSclosure_fakenocb_measured"), 0., mcclosure_weight, 0. , 1., 1);
	      }
	      
	    }
	    
	    if(IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && !IsTight(electronAnalysisColl_mcclosure.at(1),   eventbase->GetEvent().JetRho()) ){
              FillHist((label + "MCSSclosure_mcclosure_Doubletosingle"), 0., mcclosure_weight, 0. , 1., 1);
	      FillHist(label + "mcclosure_event_breakdown_tl", 0., 1., 0., 1., 1);
	    }
	    if(!IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) && IsTight(electronAnalysisColl_mcclosure.at(1),   eventbase->GetEvent().JetRho()) ){
              FillHist((label + "MCSSclosure_mcclosure_Doubletosingle"), 0., mcclosure_weight, 0. , 1., 1);
	      FillHist(label + "mcclosure_event_breakdown_tl", 0., 1., 0., 1., 1);
            }
	    if(!IsTight(electronAnalysisColl_mcclosure.at(0),   eventbase->GetEvent().JetRho()) &&!IsTight(electronAnalysisColl_mcclosure.at(1),   eventbase->GetEvent().JetRho()) ){
	      //if(true){
	      
	      vector<TString> jetcut;
	      jetcut.push_back("20");
	      jetcut.push_back("30");
	      jetcut.push_back("40");
	      jetcut.push_back("60");
	      for(unsigned int ij=0; ij < jetcut.size() ; ij ++){
		float sd =    GetFakeRateByParam("pteta", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);      // pt vs eta
		float sd_b =  GetFakeRateByParam("bjet_pt_eta", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);      // pt vs eta
		float sd_h =  GetFakeRateByParam("ht_eta", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);      // pt vs eta
		float sd_ht = GetFakeRateByParam("HT", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2); // ht vs eta (cb or nocb)
		float sd_pt = GetFakeRateByParam("PT", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2); // ht vs eta (cb or nocb)
		float sd_bt = GetFakeRateByParam("BT", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);  // pt vs eta (0/non0 bjet) (cb or nocb)
		float sd_st = GetFakeRateByParam("ST1", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2); ; // pt vs eta vs ht ((0/non0 bjet) (cb or nocb)
		float sd_st2 = GetFakeRateByParam("ST2", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);  // pt vs eta vs ht (cb or nocb)
		float sd_st3 = GetFakeRateByParam("ST3", jetcut.at(ij), looseregion, electronAnalysisColl_mcclosure, jets,closejet_el1,closejet_el2);  // pt vs eta vs ht
		
		FillHist((label + "MCSSclosure_mcclosure" + jetcut.at(ij) + "_single"), 0., sd*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_b_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_b*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_h_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_h*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_ht_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_ht*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_pt_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_pt*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_bt_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_bt*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_st_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_st*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_st2_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_st2*mcclosure_weight, 0. , 1., 1);
		FillHist((label + "MCSSclosure_st3_mcclosure" + jetcut.at(ij) + "_single"), 0., sd_st3*mcclosure_weight, 0. , 1., 1);
	      }
	      
	      FillHist(label + "mcclosure_event_breakdown_ll", 0., 1., 0., 1., 1);

	      if(el1_fake &&el2_fake)                 FillHist(label + "MCSSclosure_mcclosure_ll_fakeevent_type", 0 , 1.,  0. , 3, 3);
              if(!el1_fake &&el2_fake)                FillHist(label + "MCSSclosure_mcclosure_ll_fakeevent_type", 1 , 1.,  0. , 3, 3);
              if(el1_fake &&!el2_fake)                FillHist(label + "MCSSclosure_mcclosure_ll_fakeevent_type", 2 , 1.,  0. , 3, 3);

	    }
	    /// prediction plots
	    MakeMCCloseplots("20", label,  "pteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20);
	    MakeMCCloseplots("40", label,  "pteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40);
	    MakeMCCloseplots("60", label,  "pteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60);
	    MakeMCCloseplots("30", label,  "pteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30);

	    MakeMCCloseplots("20",  label, "pteta_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20b);
            MakeMCCloseplots("40",  label, "pteta_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40b);
            MakeMCCloseplots("60",  label, "pteta_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60b);
            MakeMCCloseplots("30",  label, "pteta_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30b);
	    
	    MakeMCCloseplots("20",  label, "pteta_h", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20h);
            MakeMCCloseplots("40",  label, "pteta_h", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40h);
            MakeMCCloseplots("60",  label, "pteta_h", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60h);
            MakeMCCloseplots("30",  label, "pteta_h", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30h);

	    MakeMCCloseplots("20",  label, "hteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20ht);
	    MakeMCCloseplots("40",  label, "hteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40ht);
	    MakeMCCloseplots("60",  label, "hteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60ht);
	    MakeMCCloseplots("30",  label, "hteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30ht);
	    
            MakeMCCloseplots("20",  label, "bteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20bt);
            MakeMCCloseplots("40",  label, "bteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40bt);
            MakeMCCloseplots("60",  label, "bteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60bt);
            MakeMCCloseplots("30",  label, "bteta", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30bt);

	    MakeMCCloseplots("20",  label, "pteta_ht_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20st);
            MakeMCCloseplots("40",  label, "pteta_ht_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40st);
            MakeMCCloseplots("60",  label, "pteta_ht_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60st);
            MakeMCCloseplots("30",  label, "pteta_ht_b", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30st);

	    MakeMCCloseplots("20",  label, "pteta_ht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20st2);
            MakeMCCloseplots("40",  label, "pteta_ht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40st2);
            MakeMCCloseplots("60",  label, "pteta_ht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60st2);
            MakeMCCloseplots("30",  label, "pteta_ht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30st2);
	    
	    MakeMCCloseplots("20",  label, "pteta_pht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20st3);
            MakeMCCloseplots("40",  label, "pteta_pht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40st3);
            MakeMCCloseplots("60",  label, "pteta_pht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60st3);
            MakeMCCloseplots("30",  label, "pteta_pht", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30st3);

	    MakeMCCloseplots("20",  label, "pteta_cb", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight20pt);
            MakeMCCloseplots("40",  label, "pteta_cb", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight40pt);
            MakeMCCloseplots("60",  label, "pteta_cb", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight60pt);
            MakeMCCloseplots("30",  label, "pteta_cb", electronAnalysisColl_mcclosure , jets, (closejet_el1 || closejet_el2) , fake_weight30pt);
	    	    
	  }
        }
      }
    }
  }

  return;
}
  

double AnalyzerCore::GetFakeRateByParam(TString param, TString jetcut, TString looseregion, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets,  bool cl1, bool cl2){

  if(param.Contains("pteta")){
    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), "mc_" + jetcut +"_"+ looseregion);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), "mc_" + jetcut +"_"+ looseregion);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
  }

  if(param.Contains("ht_eta")){
    float f1 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), "mc_" + jetcut +"_ht_"+ looseregion);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), "mc_" + jetcut +"_ht_"+ looseregion);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
    
  }
  
  if(param.Contains("PT")){
    TString el_1_pt = "";
    TString el_2_pt = "";
    if(cl1) el_1_pt = "mc_"+ jetcut + "_cb_" + looseregion;
    else el_1_pt = "mc_"+jetcut+"_nocb_pt_" + looseregion;
    if(cl2) el_2_pt = "mc_"+ jetcut + "_cb_" + looseregion;
    else el_2_pt = "mc_"+ jetcut +"_nocb_pt_" + looseregion;
    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), el_1_pt);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), el_2_pt);
    if(cl1) f1 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), el_1_pt);
    if(cl2) f2 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), el_2_pt);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));

  }
  if(param.Contains("BT")){

    TString frbjet="b";
    if(NBJet(jets) ==0) frbjet="nob";

    TString el_1_bt = "";
    TString el_2_bt = "";
    if(cl1) el_1_bt = "mc_"+ jetcut + "_cb_" + looseregion;
    else    el_1_bt = "mc_" + jetcut  + frbjet + "_nocb_" + looseregion;
    if(cl2) el_2_bt = "mc_"+ jetcut + "_cb_" + looseregion;
    else el_2_bt =  "mc_" + jetcut + frbjet + "_nocb_" + looseregion;

    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), el_1_bt);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), el_2_bt);
    if(cl1) f1 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), el_1_bt);
    if(cl2) f2 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), el_2_bt);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
    
  }
  if(param.Contains("ST1")){
    TString el_1_st = "";
    TString el_2_st = "";
    if(cl1) el_1_st = "mc_"+jetcut+"_cb_" + looseregion;
    else {
      if( NBJet(jets) == 0 ) {
	if(SumPt(jets) < 100.)  el_1_st = "mc_"+jetcut+"_0bjet_ht1_nocb_" + looseregion;
	else el_1_st = "mc_"+jetcut+"_0bjet_ht3_nocb_" + looseregion;
      }
      else{
	if(SumPt(jets) < 100.)  el_1_st = "mc_"+jetcut+"_bjet_ht1_nocb_" + looseregion;
	else el_1_st = "mc_"+jetcut+"_bjet_ht3_nocb_" + looseregion;

      }
    }
    if(cl2) el_2_st = "mc_"+jetcut+"_cb_" + looseregion;
    else {
      if( NBJet(jets) == 0 ){
	if(SumPt(jets) < 100.)   el_2_st = "mc_"+jetcut+"_0bjet_ht1_nocb_" + looseregion;
	else  el_2_st = "mc_"+jetcut+"_0bjet_ht3_nocb_" + looseregion;
      }
      else{
	if(SumPt(jets) < 100.)   el_2_st = "mc_"+jetcut+"_bjet_ht1_nocb_" + looseregion;
	else  el_2_st = "mc_"+jetcut+"_bjet_ht3_nocb_" + looseregion;
      }
    }
    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), el_1_st);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), el_2_st);
    if(cl1) f1 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), el_1_st);
    if(cl2) f2 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), el_2_st);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
    
  }

  if(param.Contains("ST3")){

    TString st3label= "";
    if(SumPt(jets) < 100.) st3label +=  "ht1_";
    else st3label +=  "ht3_";
    st3label += looseregion;
    
    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), "mc_" + jetcut +"_" +  st3label );
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), "mc_" + jetcut +"_" +  st3label );
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));

  }
  if(param.Contains("ST2")){
    
    TString el_1_st2 = "";
    TString el_2_st2 = "";
    if(cl1) el_1_st2 = "mc_"+jetcut+"_cb_" + looseregion;
    else {
      if(SumPt(jets) < 100.)  el_1_st2 = "mc_"+jetcut+"_ht1_nocb_" + looseregion;
      else el_1_st2 = "mc_"+jetcut+"_ht3_nocb_" + looseregion;
    }
    if(cl2) el_2_st2 = "mc_"+jetcut+"_cb_" + looseregion;
    else {
      if(SumPt(jets) < 100.)   el_2_st2 = "mc_"+jetcut+"_ht1_nocb_" + looseregion;
      else  el_2_st2 = "mc_"+jetcut+"_ht3_nocb_" + looseregion;
    }

    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), el_1_st2);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), el_2_st2);
    if(cl1) f1 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), el_1_st2);
    if(cl2) f2 = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), el_2_st2);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
    
  }
  if(param.Contains("bjet_pt_eta")){

    TString frbjet="b";
    if(NBJet(jets) ==0) frbjet="nob";
    float f1 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(0).Pt(), fabs(electrons.at(0).Eta()), "mc_" + jetcut +"" + frbjet + "_"+looseregion);
    float f2 = m_fakeobj->getFakeRate_electronEta(0, electrons.at(1).Pt(), fabs(electrons.at(1).Eta()), "mc_" + jetcut +"" + frbjet + "_"+looseregion);
    return ( (f1 / (1.-f1))  + (f2 / (1.-f2)));
  }

  if(param.Contains("HT")){
    TString el_1_ht = "";
    TString el_2_ht = "";
    if(cl1) el_1_ht = "mc_"+ jetcut + "_cb_" + looseregion;
    else el_1_ht = "mc_"+ jetcut +"_nocb_" + looseregion;
    if(cl2) el_2_ht = "mc_"+ jetcut +"_cb_" + looseregion;
    else el_2_ht = "mc_"+ jetcut +"_nocb_" + looseregion;
    
    float f1_ht = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(0).Eta()), el_1_ht);
    float f2_ht = m_fakeobj->getFakeRate_electronEta(0, SumPt(jets), fabs(electrons.at(1).Eta()), el_2_ht);
    return ( (f1_ht / (1.-f1_ht))  + (f2_ht / (1.-f2_ht)));
  }
  return -9999999.;
}

void AnalyzerCore::MakeMCCloseplots(TString ajpt, TString label,  TString method, std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool closebjet, float w1 ){
  
  FillHist((label + "MCSSclosure_fake_pt_predicted"+ajpt+method),  electrons.at(1).Pt(), w1, 0. , 400., 20);
  FillHist((label + "MCSSclosure_fake_eta_predicted"+ ajpt+method),  electrons.at(0).Eta(), w1, -2.5 , 2.5, 4);
  FillHist((label + "MCSSclosure_fake_eta_predicted"+ ajpt+method),  electrons.at(1).Eta(), w1, -2.5 , 2.5, 4);
  FillHist((label + "MCSSclosure_fake_nbjet_predicted"+ajpt+method),  NBJet(jets), w1, 0. , 4., 4);
  FillHist((label + "MCSSclosure_fake_ht_predicted"+ajpt+method), SumPt(jets), w1, 0. , 1000., 40);
  FillHist((label + "MCSSclosure_fake_njet_predicted"+ ajpt+method), jets.size(), w1, 0. , 10., 10);
  FillHist((label + "MCSSclosure_fake_predicted"+ ajpt+method), 0., w1, 0. , 1., 1);

  if(closebjet){
    FillHist((label + "MCSSclosure_fakecb_njet_predicted"+ ajpt+method), jets.size(), w1, 0. , 10., 10);
    FillHist((label + "MCSSclosure_fakecb_predicted"+ ajpt+method), 0., w1, 0. , 1., 1);
  }
  else{
    FillHist((label + "MCSSclosure_fakenocb_njet_predicted"+ajpt+method), jets.size(), w1, 0. , 10., 10);
    FillHist((label + "MCSSclosure_fakenocb_ht_predicted"+ajpt+method), SumPt(jets), w1, 0. , 1000., 40);
    FillHist((label + "MCSSclosure_fakenocb_nbjet_predicted"+ajpt+method),  NBJet(jets), w1, 0. , 4., 4);
    FillHist((label + "MCSSclosure_fakenocb_pt_predicted"+ajpt+method),  electrons.at(1).Pt(), w1, 0. , 400., 20);
    FillHist((label + "MCSSclosure_fakenocb_predicted"+ ajpt+method), 0., w1, 0. , 1., 1);
  }
  
 
}
  
void AnalyzerCore::PlotFakeLeptons( std::vector<snu::KJet> jets, float w){

  std::vector<snu::KMuon>  muons = GetMuons("veto");
  std::vector<snu::KElectron>  electronNoCutColl = GetElectrons( true, true,"NoCut");
  std::vector<snu::KElectron>  fakeElectronSample;
  if(SameCharge(electronNoCutColl)){
    if(!(electronNoCutColl.at(0).GetType()== 0 || electronNoCutColl.at(0).GetType()== 7 )) {
      if(isData) {
        if(electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(0));
      }
      else fakeElectronSample.push_back(electronNoCutColl.at(0));

      if(electronNoCutColl.at(0).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt()), w  , 0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(0).dxy()) , w  ,0., 0.1, 100);
      }
    }
    else {
      FillHist("W_el_iso",electronNoCutColl.at(0).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(0).Pt())  ,w  , 0., 0.6, 60);
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(0).dxy())  ,w  ,0., 0.1, 100);
    }

    if(!(electronNoCutColl.at(1).GetType()== 0 || electronNoCutColl.at(1).GetType()==7 )) {
      if(isData) {
        if(electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt()) > 0.5) fakeElectronSample.push_back(electronNoCutColl.at(1));
      }
      else fakeElectronSample.push_back(electronNoCutColl.at(1));
      if(electronNoCutColl.at(1).GetType()==6){
        FillHist("Wgamma_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , w  ,0., 0.6, 60);
        FillHist("Wgamma_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , w  ,0., 0.1, 100);
      }
    }
    else{
      FillHist("W_el_iso",electronNoCutColl.at(1).RelIso03(eventbase->GetEvent().JetRho() ,electronNoCutColl.at(1).Pt())  , w  ,0., 0.6, 60);
      
      FillHist("W_el_dxy",fabs(electronNoCutColl.at(1).dxy()) , w  ,0., 0.1, 100);
    }
  }
  FillCLHist(sighist, "Fake", eventbase->GetEvent(), muons, fakeElectronSample,jets, w);

}

void AnalyzerCore::GetIDEfficiency( std::vector<snu::KElectron> electronNoCutColl, std::vector<snu::KMuon> muons,  std::vector<snu::KJet> jets, float w){

  //// CHECK EFFICIENCY OF CUTS
  std::vector<snu::KElectron>  electronEtaCutColl;
  bool pteta=true;
  bool emuiso=true;
  if( electronNoCutColl.size() == 1 && muons.size() == 1){
    if(fabs(electronNoCutColl[0].Eta()) > 2.4) pteta = false;
    if(fabs(muons[0].Eta()) > 2.5) pteta= false;
    
    if(electronNoCutColl[0].Pt() > muons[0].Pt() ){
      if(electronNoCutColl[0].Pt() < 20.) pteta=false;
      if(muons[0].Pt() < 15.) pteta=false;
    }
    else{
      if(muons[0].Pt() < 20.) pteta=false;
      if(electronNoCutColl[0].Pt() < 15.) pteta=false;
    }
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid=0;
    if (fabs(electronNoCutColl.at(0).SCEta()) < 1.0) ifid = 0;
    else if (fabs(electronNoCutColl.at(0).SCEta()) < 1.479) ifid = 1;
    else if (fabs(electronNoCutColl.at(0).SCEta()) < 2.0) ifid = 2;
    else if (fabs(electronNoCutColl.at(0).SCEta()) < 2.2) ifid = 3;
    else if (fabs(electronNoCutColl.at(0).SCEta()) < 2.3) ifid = 4;
    else if (fabs(electronNoCutColl.at(0).SCEta()) < 2.4) ifid = 5;
    else ifid = 6;
    
    float LeptonRelIsoDR03(0.);
    float ElectronIsoDR03 =  electronNoCutColl.at(0).PFChargedHadronIso03() + max( electronNoCutColl.at(0).PFNeutralHadronIso03() + electronNoCutColl.at(0).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);
    
    if(electronNoCutColl.at(0).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(0).Pt();
    else LeptonRelIsoDR03 = -999.;
    
    if(fabs(electronNoCutColl[0].Eta()) < 1.5){
      if(LeptonRelIsoDR03 > 0.09) emuiso=false;
    }
    else  if(LeptonRelIsoDR03 > 0.05) emuiso=false; 
    
    float reliso=0.;
    if (muons[0].Pt() > 0.01)  reliso = (muons[0].SumIsoCHDR03() + std::max(0.0, muons[0].SumIsoNHDR03() + muons[0].SumIsoPHDR03() - 0.5* muons[0].SumPUIsoR03()))/muons[0].Pt() ;
    else reliso = 9999.;
    if (reliso<0) reliso=0.0001;
        
    if(( reliso >= 0.05))  emuiso=false;
       
    
    w=1;

    if(pteta)   FillHist("eff_emu_pteta", 1.,w, 0.,2.,2);
    if(emuiso)   FillHist("eff_emu_iso", 1.,w, 0.,2.,2);
    
    if(pteta&& IsTight(muons[0]) && IsTight(electronNoCutColl[0],eventbase->GetEvent().JetRho())){
      FillHist("eff_emu_dilep", 1.,w, 0.,2.,2);
      if(jets.size() >=  2)  FillHist("eff_emu_presel", 1.,w, 0.,2.,2);
    }
  }
  w= 1.;
  if(jets.size() >=  2)  FillHist("eff_emu_dijet", 1.,w, 0.,2.,2);
  FillHist("eff_emu_pteta_ref", 1.,w, 0.,2.,2);
}

void AnalyzerCore::GetIDEfficiency( std::vector<snu::KElectron> electronNoCutColl, std::vector<snu::KJet> jets, TString label, float w){

  //// CHECK EFFICIENCY OF CUTS
  std::vector<snu::KElectron>  electronEta24CutColl;
  std::vector<snu::KElectron>  electronEta25CutColl;

  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.5) continue;
   
    electronEta25CutColl.push_back(electronNoCutColl[iel]);

    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;
    electronEta24CutColl.push_back(electronNoCutColl[iel]);

  }

  std::vector<snu::KElectron>  electronPt10CutColl;
  std::vector<snu::KElectron>  electronPt15CutColl;

  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){
    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 10.) continue;
    }
    if(fabs(electronNoCutColl[iel].Eta()) > 2.5) continue;

    electronPt10CutColl.push_back(electronNoCutColl[iel]);

    if(iel ==0){
      if(electronNoCutColl[iel].Pt() < 20.) continue;
    }
    else{
      if(electronNoCutColl[iel].Pt() < 15.) continue;
    }
    
    electronPt15CutColl.push_back(electronNoCutColl[iel]);

  }

  
   /// Tight ID eff
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
  
  // oital efficiency + tight brekdownd
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

  std::vector<snu::KElectron>   electron_analysis_primarydxyCutColl;;
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
    if(fabs(electronNoCutColl[iel].Eta()) > 2.5) continue;
    
    

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
			  if(ecaliso > 0.25) passNPFiso = false;
			  if(hcaliso > 0.2)  passNPFiso = false;
			  
			  float isocut= 0.09;
			  if(fabs(electronNoCutColl.at(iel).Eta()) > 1.5)isocut = 0.05;
			  
			  if(LeptonRelIsoDR03 < isocut){
			    if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			      electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
			      if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
			    }
			    if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY ())  <= 0.01){
			      electron_analysis_primarydxyCutColl.push_back(electronNoCutColl.at(iel));
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
      if(fabs(electronNoCutColl[iel].Eta()) > 2.5) continue;

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
			  if(ecaliso > 0.25) passNPFiso = false;
			  if(hcaliso > 0.2)  passNPFiso = false;
			  
			  float isocut= 0.09;
			  if(fabs(electronNoCutColl.at(iel).Eta()) > 1.5)isocut = 0.05;
			  
			  if(LeptonRelIsoDR03 < isocut){
			    if(fabs(electronNoCutColl.at(iel).dxy ())  <= 0.01){
			      electron_analysisCutColl.push_back(electronNoCutColl.at(iel));
			      if(passNPFiso)       electron_analysisNPFCutColl.push_back(electronNoCutColl.at(iel));
                            }
			    if(fabs(electronNoCutColl.at(iel).LeadVtxDistXY ())  <= 0.01){
			      electron_analysis_primarydxyCutColl.push_back(electronNoCutColl.at(iel));
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
    float ElectronIsoDR03 =  electronNoCutColl.at(iel).PFChargedHadronIso03() + max( electronNoCutColl.at(iel).PFNeutralHadronIso03() + electronNoCutColl.at(iel).PFPhotonIso03()    - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);

    if(electronNoCutColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronNoCutColl.at(iel).Pt();
    else LeptonRelIsoDR03 = -999.;

    float trkiso =electronNoCutColl.at(iel).TrkIsoDR03()/electronNoCutColl.at(iel).Pt();
    float ecaliso =electronNoCutColl.at(iel).ECalIsoDR03()/electronNoCutColl.at(iel).Pt();
    float hcaliso =electronNoCutColl.at(iel).HCalIsoDR03()/electronNoCutColl.at(iel).Pt();
    bool passNPFiso = true;
    if(trkiso > 0.1) passNPFiso = false;
    if(ecaliso > 0.25) passNPFiso = false;
    if(hcaliso > 0.2)  passNPFiso = false;
    float isocut= 0.09;
    if(fabs(electronNoCutColl.at(iel).Eta()) > 1.5 )isocut = 0.05;

    if(LeptonRelIsoDR03 < isocut){
      electron_IsoCutColl.push_back(electronNoCutColl.at(iel));
      if(passNPFiso)       electron_NPFIsoCutColl.push_back(electronNoCutColl.at(iel));

    }
  }

  FillHist(label + "eff_electronRef", 1.,w, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl)) {
    FillHist(label + "eff_electron_vertexcheck", 1.,w, 0.,4.,4);
    if(electronNoCutColl.at(0).VertexIndex() == electronNoCutColl.at(1).VertexIndex())  {
      FillHist(label + "eff_electron_vertexcheck", 2.,w, 0.,4.,4);
      if(electronNoCutColl.at(0).VertexIndex() == eventbase->GetEvent().VertexIndex()){
	FillHist(label + "eff_electron_vertexcheck", 3.,w, 0.,4.,4);
      }
    }
  }
  if(SameCharge(electronPt10CutColl))   FillHist(label + "eff_electronPt10CutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electronPt15CutColl))   FillHist(label + "eff_electronPt15CutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electronEta24CutColl))   FillHist(label + "eff_electronEta24CutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electronEta25CutColl))   FillHist(label + "eff_electronEta25CutColl", 1.,w, 0.,2.,2);

  if(SameCharge(electronTight_NoIsoCutColl))   FillHist(label + "eff_electron_NoIsoCutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electron_IsoCutColl))   FillHist(label + "eff_electron_IsoCutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electron_NPFIsoCutColl))   FillHist(label + "eff_electron_NPFIsoCutColl", 1.,w, 0.,2.,2);
  if(SameCharge(electron_analysisCutColl))   FillHist(label + "eff_electron_analysisCutColll", 1.,w, 0.,2.,2);
  if(SameCharge(electron_analysis_primarydxyCutColl))   FillHist(label + "eff_electron_primarydxyanalysisCutColll", 1.,w, 0.,2.,2);
  if(SameCharge(electron_analysisNPFCutColl))   FillHist(label + "eff_electron_analysisNPFCutColll", 1.,w, 0.,2.,2);
  if(jets.size()  > 1) FillHist(label + "_JetSelection", 1.,w, 0.,2.,2);
  if(jets.size()  > 1 && NBJet(jets) == 0 ) FillHist(label + "_JetSelection_noB", 1.,w, 0.,2.,2);

  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");


  if(PassTrigger(triggerslist, prescale) &&  jets.size()  > 1) {
    
    float wmassjj=0.;
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

    
    int nlep = GetElectrons(false, false, "veto").size() + GetMuons(label + "_veto").size();

    snu::KParticle jj = jets.at(indexj1) + jets.at(indexj2);
    
    if((GetElectrons(false, false,"HNTight_loosereg2").size() == 2) && jets.size()  > 1) {

      float wa = w;
      wa*= WeightCFEvent(GetElectrons(false,false,"HNTight_loosereg2"), k_running_chargeflip, false);
      if(k_running_nonprompt) wa*=Get_DataDrivenWeight_EE(GetElectrons(false,false,"HNTight_loosereg2"),  jets,  eventbase->GetEvent().JetRho(),  true, 0.01, 0.09, 0.05, "method1_pt_eta_40_looseregion2", 0);

      snu::KParticle Z = GetElectrons(false, false,"HNTight_loosereg2").at(0) + GetElectrons(false, false,"HNTight_loosereg2").at(1);
      FillHist(label + "PreSelection", 1.,wa, 0.,2.,2);

      if(!Zcandidate(GetElectrons(false, false,"HNTight_loosereg2"), 10., false)) {
	FillHist(label + "PreSelection_noZ", 1.,wa, 0.,2.,2); 
	if(nlep == 2 && Z.M() > 10.){
	  FillHist(label + "PreSelection_veto", 1.,wa, 0.,2.,2);
	  if(GetElectrons(false, false,"HNTight_loosereg2").at(1).Pt() > 15.)  {
	    FillHist(label + "PreSelection_pt15", 1.,wa, 0.,2.,2); 
	    if(eventbase->GetEvent().PFMET() < 30){
	      FillHist(label + "PreSelection_met", 1.,wa, 0.,2.,2);
	      if(NBJet(jets) == 0 ){
		FillHist(label + "PreSelection_bjet", 1.,wa, 0.,2.,2);
		if(jj.M() < 120.){
		  FillHist(label + "PreSelection_jj", 1.,wa, 0.,2.,2);
		  
		  
		  snu::KParticle eejj = GetElectrons(false, false,"HNTight_loosereg2").at(0) + GetElectrons(false, false,"HNTight_loosereg2").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false, false,"HNTight_loosereg2").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200.  ) FillHist(label + "PreSelection_lowmass", 1.,wa, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200. && Z.M() < 60 ) FillHist(label + "PreSelection_lowmass2", 1.,wa, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 155. && Z.M() < 60 ) FillHist(label + "PreSelection_lowmass3", 1.,wa, 0.,2.,2);
		}
	      }
	    }
	    
	    if(eventbase->GetEvent().PFMET() < 35){
              FillHist(label + "PreSelection_high_met", 1.,wa, 0.,2.,2);
              if(NBJet(jets) == 0 ){
                FillHist(label + "PreSelection_high_bjet", 1.,wa, 0.,2.,2);
                if(jj.M() < 110.&& jj.M() > 50.){
                  FillHist(label + "PreSelection_high_jj", 1.,wa, 0.,2.,2);

		  
		  snu::KParticle eejj = GetElectrons(false, false,"HNTight_loosereg2").at(0) + GetElectrons(false, false,"HNTight_loosereg2").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false, false,"HNTight_loosereg2").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  float pt1 = GetElectrons(false, false,"HNTight_loosereg2").at(0).Pt();
		  float pt2 = GetElectrons(false, false,"HNTight_loosereg2").at(1).Pt();

                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 100 ) FillHist(label + "PreSelection_highmass", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 110 ) FillHist(label + "PreSelection_highmass2", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 120 ) FillHist(label + "PreSelection_highmass3", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 140 && pt1 > 25 && pt2 > 20) FillHist(label + "PreSelection_highmass4", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 160 && pt1 > 35 && pt2 > 25) FillHist(label + "PreSelection_highmass5", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 200 && pt1 > 45 && pt2 > 30) FillHist(label + "PreSelection_highmass6", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 220 && pt1 > 50 && pt2 > 35) FillHist(label + "PreSelection_highmass7", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 270 && pt1 > 70 && pt2 > 45) FillHist(label + "PreSelection_highmass8", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 290 && pt1 > 100 && pt2 > 45) FillHist(label + "PreSelection_highmass9", 1.,wa, 0.,2.,2);

		  
		  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 80  && e2jj.M() > 70. && e2jj.M() < 120. ) FillHist(label + "PreSelection_highmass10", 1.,wa, 0.,2.,2); // 80
		  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 110  && e2jj.M() > 80. && e2jj.M() < 120. ) FillHist(label + "PreSelection_highmass11", 1.,wa, 0.,2.,2); // 90-100
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 140 && pt1 > 25 && pt2 > 25  && e2jj.M() > 90. && e2jj.M() < 145.) FillHist(label + "PreSelection_highmass12", 1.,wa, 0.,2.,2); // 125
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 160 && pt1 > 35 && pt2 > 25 && e2jj.M() > 120. && e2jj.M() < 180.) FillHist(label + "PreSelection_highmass13", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 240 && pt1 > 45 && pt2 > 30  && e2jj.M() > 140. && e2jj.M() < 200.) FillHist(label + "PreSelection_highmass14", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 280 && pt1 > 65 && pt2 > 40  && e2jj.M() > 160. && e2jj.M() < 250.) FillHist(label + "PreSelection_highmass15", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 290 && pt1 > 70 && pt2 > 45 && e2jj.M() > 160. && e2jj.M() < 260.) FillHist(label + "PreSelection_highmass16", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 300 && pt1 > 70 && pt2 > 45 ) FillHist(label + "PreSelection_highmass17", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 320 && pt1 > 70 && pt2 > 45 ) FillHist(label + "PreSelection_highmass18", 1.,wa, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 350 && pt1 > 120 && pt2 > 25 ) FillHist(label + "PreSelection_highmass19", 1.,wa, 0.,2.,2);
		  
                }
              }
            }
	    
	  }
        }
      }
    }
    
    
    if((GetElectrons(false,false,"id_medium").size() == 2) && jets.size()  > 1) {
      
      snu::KParticle Z = GetElectrons(false,false,"id_medium").at(0) + GetElectrons(false,false,"id_medium").at(1);


      float wm = w;
      wm*= WeightCFEvent(GetElectrons(false,false,"id_medium"), k_running_chargeflip, false);
      if(k_running_nonprompt)wm  *= Get_DataDrivenWeight_EE(GetElectrons(false,false,"id_medium"),  jets,  eventbase->GetEvent().JetRho(),  false, 0.02, 0.1, 0.1, "medium_pog_40_pt_eta", 0);
      FillHist(label + "PreSelection_medium", 1.,wm, 0.,2.,2);

      if(!Zcandidate(GetElectrons(false,false,"id_medium"), 10., false)) {
	FillHist(label + "PreSelection_medium_noZ", 1.,wm, 0.,2.,2);
	if(nlep == 2 && Z.M() > 10.) {
	  FillHist(label + "PreSelection_medium_veto", 1.,wm, 0.,2.,2);
	  if(GetElectrons(false,false,"id_medium").at(1).Pt() > 15.)  {
	    FillHist(label + "PreSelection_medium_pt15", 1.,wm, 0.,2.,2);
	    if(eventbase->GetEvent().PFMET() < 30){
	      FillHist(label + "PreSelection_medium_met", 1.,wm, 0.,2.,2);
	      if(NBJet(jets) == 0 ){
		FillHist(label + "PreSelection_medium_bjet", 1.,wm, 0.,2.,2);
		if(jj.M() < 120.){
		  FillHist(label + "PreSelection_medium_jj", 1.,wm, 0.,2.,2);
		  
		  snu::KParticle eejj = GetElectrons(false,false,"id_medium").at(0) + GetElectrons(false,false,"id_medium").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false,false,"id_medium").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200.  ) FillHist(label + "PreSelection_medium_lowmass", 1.,wm, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200. && Z.M() < 60 ) FillHist(label + "PreSelection_medium_lowmass2", 1.,wm, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 155. && Z.M() < 60 ) FillHist(label + "PreSelection_medium_lowmass3", 1.,wm, 0.,2.,2);
		}
	      }
	    }

	  }
	}
      }
    }
    
    if((GetElectrons(false,false,"id_tight").size()==2) && jets.size()  > 1)  {

      snu::KParticle Z = GetElectrons(false,false,"id_tight").at(0) + GetElectrons(false,false,"id_tight").at(1);
      float wt = w;
      wt*= WeightCFEvent(GetElectrons(false,false,"id_tight"), k_running_chargeflip, false);

      if(k_running_nonprompt)wt *= Get_DataDrivenWeight_EE(GetElectrons(false,false,"id_tight"),  jets,  eventbase->GetEvent().JetRho(),  true, 0.02, 0.1, 0.1, "tight_pog_40_pt_eta", 0);

      FillHist(label + "PreSelection_tight", 1.,wt, 0.,2.,2);
      if(!Zcandidate(GetElectrons(false,false,"id_tight"), 10., false)) {
	FillHist(label + "PreSelection_tight_noZ", 1.,wt, 0.,2.,2);
	if(nlep == 2 && Z.M() > 10.) {
          FillHist(label + "PreSelection_tight_veto", 1.,wt, 0.,2.,2);
	  
	  if(GetElectrons(false,false,"id_tight").at(1).Pt() > 15.)     {
	    FillHist(label + "PreSelection_tight_pt15", 1.,wt, 0.,2.,2);
	    
	    if(eventbase->GetEvent().PFMET() < 30){
	      FillHist(label + "PreSelection_tight_met", 1.,wt, 0.,2.,2);
	      if(NBJet(jets) == 0 ){
		FillHist(label + "PreSelection_tight_bjet", 1.,wt, 0.,2.,2);
		if(jj.M() < 120.){
		  FillHist(label + "PreSelection_tight_jj", 1.,wt, 0.,2.,2);
		  
		  snu::KParticle eejj = GetElectrons(false,false,"id_tight").at(0) + GetElectrons(false,false,"id_tight").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false,false,"id_tight").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200.  ) FillHist(label + "PreSelection_tight_lowmass", 1.,wt, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200. && Z.M() < 60 ) FillHist(label + "PreSelection_tight_lowmass2", 1.,wt, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 155. && Z.M() < 60 ) FillHist(label + "PreSelection_tight_lowmass3", 1.,wt, 0.,2.,2);
		}
	      }
            }
	    if(eventbase->GetEvent().PFMET() < 35){
              FillHist(label + "PreSelection_tight_high_met", 1.,wt, 0.,2.,2);
              if(NBJet(jets) == 0 ){
                FillHist(label + "PreSelection_tight_high_bjet", 1.,wt, 0.,2.,2);
                if(jj.M() < 110.&& jj.M() > 50.){
                  FillHist(label + "PreSelection_tight_high_jj", 1.,wt, 0.,2.,2);


		  snu::KParticle eejj = GetElectrons(false, false,"id_tight").at(0) + GetElectrons(false, false,"id_tight").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false, false,"id_tight").at(1) + jets.at(indexj1) + jets.at(indexj2);
                  float pt1 = GetElectrons(false, false,"id_tight").at(0).Pt();
                  float pt2 = GetElectrons(false, false,"id_tight").at(1).Pt();

                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 100 ) FillHist(label + "PreSelection_tight_highmass", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 110 ) FillHist(label + "PreSelection_tight_highmass2", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 120 ) FillHist(label + "PreSelection_tight_highmass3", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 140 && pt1 > 25 && pt2 > 20) FillHist(label + "PreSelection_tight_highmass4", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 160 && pt1 > 35 && pt2 > 25) FillHist(label + "PreSelection_tight_highmass5", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 200 && pt1 > 45 && pt2 > 30) FillHist(label + "PreSelection_tight_highmass6", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 220 && pt1 > 50 && pt2 > 35) FillHist(label + "PreSelection_tight_highmass7", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 270 && pt1 > 70 && pt2 > 45) FillHist(label + "PreSelection_tight_highmass8", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 290 && pt1 > 100 && pt2 > 45) FillHist(label + "PreSelection_tight_highmass9", 1.,wt, 0.,2.,2);





		  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 80  && e2jj.M() > 70. && e2jj.M() < 120. ) FillHist(label + "PreSelection_tight_highmass10", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 110  && e2jj.M() > 80. && e2jj.M() < 120. ) FillHist(label + "PreSelection_tight_highmass11", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 140 && pt1 > 25 && pt2 > 25  && e2jj.M() > 90. && e2jj.M() < 145.) FillHist(label + "PreSelection_tight_highmass12", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 160 && pt1 > 35 && pt2 > 25 && e2jj.M() > 120. && e2jj.M() < 180.) FillHist(label + "PreSelection_tight_highmass13", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 240 && pt1 > 45 && pt2 > 30  && e2jj.M() > 140. && e2jj.M() < 200.) FillHist(label + "PreSelection_tight_highmass14", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 280 && pt1 > 65 && pt2 > 40  && e2jj.M() > 160. && e2jj.M() < 250.) FillHist(label + "PreSelection_tight_highmass15", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 290 && pt1 > 70 && pt2 > 45 && e2jj.M() > 160. && e2jj.M() < 260.) FillHist(label + "PreSelection_tight_highmass16", 1.,wt, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 300 && pt1 > 70 && pt2 > 45 ) FillHist(label + "PreSelection_tight_highmass17", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 320 && pt1 > 70 && pt2 > 45 ) FillHist(label + "PreSelection_tight_highmass18", 1.,wt, 0.,2.,2);
                  if(nlep == 2 && Z.M() > 15.&& eejj.M() > 350 && pt1 > 120 && pt2 > 25 ) FillHist(label + "PreSelection_tight_highmass19", 1.,wt, 0.,2.,2);
                }
              }
            }
	  }
        }
      }
    }

    if((GetElectrons(false,false,"tight_iso_b10_e10").size()==2)&& jets.size()  > 1)  {
      snu::KParticle Z = GetElectrons(false,false,"tight_iso_b10_e10").at(0) + GetElectrons(false,false,"tight_iso_b10_e10").at(1);

      float wt = w;
      wt*= WeightCFEvent(GetElectrons(false,false,"tight_iso_b10_e10"), k_running_chargeflip, false);
      if(k_running_nonprompt)wt *= Get_DataDrivenWeight_EE(GetElectrons(false,false,"tight_iso_b10_e10"),  jets,  eventbase->GetEvent().JetRho(), false, 0.01, 0.1, 0.1, "electronTightColl_dr03_b10_e10_40_pt_eta", 0);
      FillHist(label + "PreSelection_iso_10_10", 1.,wt, 0.,2.,2);
      if(!Zcandidate(GetElectrons(false,false,"tight_iso_b10_e10"), 10., false)){
	FillHist(label + "PreSelection_iso_10_10_noZ", 1.,wt, 0.,2.,2);
	if(nlep == 2 && Z.M() > 10.){
	  FillHist(label + "PreSelection_iso_b10_e10_veto", 1.,wt, 0.,2.,2);
	  
	  if(GetElectrons(false,false,"tight_iso_b10_e10").at(1).Pt() > 15.)     {
	    FillHist(label + "PreSelection_iso_10_10_pt15", 1.,wt, 0.,2.,2);
	    
	    if(eventbase->GetEvent().PFMET() < 30){
	      FillHist(label + "PreSelection_iso_b10_e10_met", 1.,wt, 0.,2.,2);
	      if(NBJet(jets) == 0 ){
		FillHist(label + "PreSelection_iso_b10_e10_bjet", 1.,wt, 0.,2.,2);
		if(jj.M() < 120.){
		  FillHist(label + "PreSelection_iso_b10_e10_jj", 1.,wt, 0.,2.,2);
		  
		  snu::KParticle eejj = GetElectrons(false,false,"tight_iso_b10_e10").at(0) + GetElectrons(false,false,"tight_iso_b10_e10").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  snu::KParticle e2jj = GetElectrons(false,false,"tight_iso_b10_e10").at(1) + jets.at(indexj1) + jets.at(indexj2);
		  
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200.  ) FillHist(label + "PreSelection_iso_b10_e10_lowmass", 1.,wt, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 200. && Z.M() < 60 ) FillHist(label + "PreSelection_iso_b10_e10_lowmass2", 1.,wt, 0.,2.,2);
		  if(nlep == 2 && Z.M() > 10.&& eejj.M() > 80&&eejj.M() < 155. && Z.M() < 60 ) FillHist(label + "PreSelection_iso_b10_e10_lowmass3", 1.,wt, 0.,2.,2);
		}
	      }
	    }
          }
        }
      }
    }
    
    
    
  }
    
  if(SameCharge(electronTight_tightref)){
    FillHist(label + "eff_electronTight_tightref", 1., w, 0.,2.,2);
    if(SameCharge(electronTight_DeltaEta))   FillHist(label + "eff_electron_DeltaEta", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_DeltaPhi))   FillHist(label + "eff_electron_DeltaPhi", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_SigmaIEta))   FillHist(label + "eff_electron_SigmaIEta", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_DZ))   FillHist(label + "eff_electron_DZ", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_HoverE))   FillHist(label + "eff_electron_HoverE", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_convfit))   FillHist(label + "eff_electron_convfit", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_ep))   FillHist(label + "eff_electron_ep", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_missinghit))   FillHist(label + "eff_electron_missinghit", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_convphoton))   FillHist(label + "eff_electron_convphoton", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_DXY))   FillHist(label + "eff_electron_DXY", 1.,w, 0.,2.,2);
    if(SameCharge(electronTight_chargeconst))   FillHist(label + "eff_electron_chargeconst", 1.,w, 0.,2.,2);
  }

}
float AnalyzerCore::WeightCFEvent(std::vector<snu::KElectron> electrons, bool runchargeflip, bool useoldrates){

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



TDirectory* AnalyzerCore::getTemporaryDirectory(void) const
{

  
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:               
    std::stringstream dirname;
    dirname << "AnalyzerCore_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                        
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;
}



double AnalyzerCore::MuonScaleFactor(double eta, double pt, int sys){
  
  double sf = 0.;
  if(fabs(eta) > 2.4) return 1.;
  if(pt < 15.) return 1.;
  int bin = MuonSF->FindBin(fabs(eta),pt);
  
  sf = MuonSF->GetBinContent(bin);

  if(sys==1) sf*= 1.02; 
  if(sys==-1) sf/= 1.02; 
  
  return sf;
  
}

double AnalyzerCore::TriggerScaleFactor( vector<snu::KElectron> el){
  if(isData) return 1.;
  if(el.size() != 2) return 1.;
  float pt = el.at(1).Pt();
  if( pt < 30.) return 0.92;
  else return 0.96;
  
}

double AnalyzerCore::TriggerScaleFactor( vector<snu::KMuon> mu){
  if(isData) return 1.;
  if(mu.size() != 2) return 1.;
  float eta = fabs(mu.at(1).Eta());
  if( eta < 1.) return 0.9;
  else return 0.81;

}
double AnalyzerCore::TriggerScaleFactorEMu( ){
  // numbers from AN2012_330_v11 
  return 0.93;
}



double AnalyzerCore::ElectronScaleFactor( double eta, double pt, bool tight_electron , int sys){
  
  ///https://twiki.cern.ch/twiki/bin/view/Main/EGammaScaleFactors2012
  double sf = 0.;
  
  /// tight working point


  bool medium_electron=!tight_electron;
  
  if(tight_electron){
    if(fabs(eta) < 0.8 ) {
      if( pt < 15.) sf = 0.969;
      else if( pt < 20.) sf = 0.969;
      else if( pt < 30.) sf = 0.958;
      else if( pt < 40.) sf = 0.966;
      else if( pt < 50.) sf = 0.973;
      else sf = 0.967;
    }
    else  if(fabs(eta) <  1.442){
      
      if( pt < 15.) sf = 0.957;
      else if( pt < 20.) sf = 0.957;
      else if( pt < 30.) sf = 0.908;
      else if( pt < 40.) sf = 0.920;
      else if( pt < 50.) sf = 0.949;
      else sf = 0.948;
    }
    else  if(fabs(eta) <1.556){
      if( pt < 15.) sf = 0.875;
      else if( pt < 20.) sf = 0.875;
      else if( pt < 30.) sf = 0.884;
      else if( pt < 40.) sf = 0.847;
      else if( pt < 50.) sf = 0.898;
      else sf = 0.910;
    }
    else if(fabs(eta) <2.0){
      
      if( pt < 15.) sf = 0.875;
      else if( pt < 20.) sf = 0.875;
      else if( pt < 30.) sf = 0.884;
      else if( pt < 40.) sf = 0.847;
      else if( pt < 50.) sf = 0.898;
      else sf = 0.91;
    }
    else{
      if( pt < 15.) sf = 0.8;
      else if( pt < 20.) sf = 0.8;
      else if( pt < 30.) sf = 0.872;
      else if( pt < 40.) sf = 0.895;
      else if( pt < 50.) sf = 0.936;
      else sf = 0.94;
    }
    float syst_err = 1.;
    
    if(sys == 0) return sf;
    
    if(fabs(eta) < 0.8 ) {
      if( pt < 15.) syst_err = 0.11;
      else if( pt < 20.) syst_err = 0.069;
      else if( pt < 30.) syst_err = 0.014;
      else if( pt < 40.) syst_err = 0.0028;
      else if( pt < 50.) syst_err = 0.0014;
      else syst_err = 0.0041;
    }
    else  if(fabs(eta) <  1.442){
      if( pt < 15.) syst_err = 0.11;
      else if( pt < 20.) syst_err = 0.069;
      else if( pt < 30.) syst_err = 0.014;
      else if( pt < 40.) syst_err = 0.0028;
      else if( pt < 50.) syst_err = 0.0014;
      else syst_err = 0.0041;
    }
    else  if(fabs(eta) <1.556){
      if( pt < 15.) syst_err = 0.11;
      else if( pt < 20.) syst_err = 0.083;
      else if( pt < 30.) syst_err = 0.057;
      else if( pt < 40.) syst_err = 0.024;
      else if( pt < 50.) syst_err = 0.0028;
      else syst_err = 0.0043;
    }
    else if(fabs(eta) <2.0){

      if( pt < 15.) syst_err = 0.12;
      else if( pt < 20.) syst_err = 0.04;
      else if( pt < 30.) syst_err = 0.022;
      else if( pt < 40.) syst_err = 0.0029;
      else if( pt < 50.) syst_err = 0.003;
      else syst_err = 0.0053;
    }
    else{
      if( pt < 15.) syst_err = 0.12;
      else if( pt < 20.) syst_err = 0.04;
      else if( pt < 30.) syst_err = 0.022;
      else if( pt < 40.) syst_err = 0.0059;
      else if( pt < 50.) syst_err = 0.003;
      else syst_err = 0.053;
    }
        
    if(sys == 1)  sf = sf *(1. +  syst_err);
    if(sys == -1) sf = sf *(1. -  syst_err);
    
    return sf;
  }
  if(medium_electron){
    /// medium working point
    if(fabs(eta) < 0.8 ) {
      if( pt < 15.) sf = 0.834;
      else if( pt < 20.) sf = 0.918;
      else if( pt < 30.) sf = 0.954;
      else if( pt < 40.) sf = 0.960;
      else if( pt < 50.) sf = 0.972;
      else sf = 0.969;
    }
    else  if(fabs(eta) <  1.442){
      
      if( pt < 15.) sf = 0.973;
      else if( pt < 20.) sf = 0.906;
      else if( pt < 30.) sf = 0.923;
      else if( pt < 40.) sf = 0.935;
      else if( pt < 50.) sf = 0.955;
      else sf = 0.956;
    }
    else  if(fabs(eta) <1.556){
      if( pt < 15.) sf = 0.954;
      else if( pt < 20.) sf = 0.909;
      else if( pt < 30.) sf = 0.921;
      else if( pt < 40.) sf = 0.924;
      else if( pt < 50.) sf = 0.950;
      else sf = 0.995;
    }
    else if(fabs(eta) <2.0){
      
      if( pt < 15.) sf = 0.954;
      else if( pt < 20.) sf = 0.909;
      else if( pt < 30.) sf = 0.921;
      else if( pt < 40.) sf = 0.924;
      else if( pt < 50.) sf = 0.950;
      else sf = 0.995;
    }
    else{
      if( pt < 15.) sf = 1.119;
      else if( pt < 20.) sf = 0.944;
      else if( pt < 30.) sf = 0.993;
      else if( pt < 40.) sf = 0.959;
      else if( pt < 50.) sf = 0.968;
      else sf = 0.969;
      
    }
    return sf;

  }
  return sf;
  /// From higgs note Z->llll
  /// reconstruction scale factors
  if(fabs(eta) < 0.8 ) {
    if( pt < 15.) sf *= 0.967;
    else if( pt < 20.) sf *= 0.997;
    else if( pt < 30.) sf *= 0.982;
    else if( pt < 40.) sf *= 0.988;
    else sf *= 0.990;
  }
  else if (fabs(eta) < 1.4442 ) {
    if( pt < 15.) sf *= 0.967;
    else if( pt < 20.) sf *= 0.997;
    else if( pt < 30.) sf *= 0.993;
    else if( pt < 40.) sf *= 0.993;
    else sf *= 0.992;
  }
  else if (fabs(eta) < 1.566 ) {
    if( pt < 15.) sf *= 1.126;
    else if( pt < 20.) sf *= 0.955;
    else if( pt < 30.) sf *= 1.015;
    else if( pt < 40.) sf *= 0.985;
    else sf *= 0.985;
  }
  else if (fabs(eta) < 2. ) {
    if( pt < 15.) sf *= 1.097;
    else if( pt < 20.) sf *= 1.012;
    else if( pt < 30.) sf *= 0.988;
    else if( pt < 40.) sf *= 0.992;
    else sf *= 0.991;
  }
  else{
    if( pt < 15.) sf *= 1.097;
    else if( pt < 20.) sf *= 1.012;
    else if( pt < 30.) sf *= 1.002;
    else if( pt < 40.) sf *= 1.004;
    else sf *= 1.004;
  }

    
}


double AnalyzerCore::TopElTriggerScaleFactor(float pt, float eta, int syst = 0){

	if(isData) return 1.;
	
	if (pt<30) return 1.;
	
	double SF = 1.;
	
	if(pt<40.){
		if (eta<0.8) SF = 0.987;
		else if (eta<1.478) SF = 0.964;
		else if (eta<2.5) SF = 1.004;

		if (syst>0){
			
			if (eta<0.8) SF = 0.987+0.012;
			else if (eta<1.478) SF = 0.964+0.002;
			else if (eta<2.5) SF = 1.004+0.006; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF = 0.987-0.017;
			else if (eta<1.478) SF = 0.964-0.001;
			else if (eta<2.5) SF = 1.004-0.006; 
			
		}
	}
	else if (pt<50){
		
		if (eta<0.8) SF = 0.997;
		else if (eta<1.478) SF = 0.98;
		else if (eta<2.5) SF = 1.033;
		
		if (syst>0){
			
			if (eta<0.8) SF = 0.997+0.001;
			else if (eta<1.478) SF = 0.98+0.001;
			else if (eta<2.5) SF = 1.033+0.007; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF = 0.997-0.001;
			else if (eta<1.478) SF = 0.98-0.001;
			else if (eta<2.5) SF = 1.033-0.007; 
			
		}
	}
	else if (pt<200){
		
		if (eta<0.8) SF = 0.998;
		else if (eta<1.478) SF = 0.988;
		else if (eta<2.5) SF = 0.976;
		
		if (syst>0){
			
			if (eta<0.8) SF = 0.998+0.002;
			else if (eta<1.478) SF = 0.988+0.002;
			else if (eta<2.5) SF = 0.976+0.015; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF = 0.998-0.002;
			else if (eta<1.478) SF = 0.988-0.002;
			else if (eta<2.5) SF = 0.976-0.012; 
			
		}
	}
	
	
	return SF;
	
}


double AnalyzerCore::TopElTriggerEff(float pt, float eta){

	// ID && Iso Efficiency
	//	if(!isData) return 1.;
	
	double Eff = 1.;
	if (pt<30.) return 1.;
	
	if(pt<40.){
		if (eta<0.8) Eff = Eff = 1/0.865;
		else if (eta<1.478) Eff = 1/0.876;
		else if (eta<2.5) Eff = 1/0.69;
	}
	else if (pt<50){
		
  	  if (eta<0.8) Eff = 1/0.895;
	  else if (eta<1.478) Eff = 1/0.91;
	  else if (eta<2.5) Eff = 1/0.738;

	}
	else if (pt<200){

  	  if (eta<0.8) Eff = 1/0.91;
	  else if (eta<1.478) Eff = 1/0.93;
	  else if (eta<2.5) Eff = 1/0.753;
	}

  return Eff;
  
}



double AnalyzerCore::TopElIDIsoScaleFactor(float pt, float eta, int syst = 0){
	//https://twiki.cern.ch/twili/bin/viewauth/CMS/KoPFAElectronTagAndProbe
	
	if(isData) return 1.;

	double SF = 1.;
	if (pt<30.) return 1.;
	
	if( pt<40.){
		if (eta<0.8) SF = 0.939;
		else if (eta<1.478) SF = 0.920;
		else if (eta<2.5) SF = 0.907;
		
		if (syst>0){
			
			if (eta<0.8) SF += 0.003;
			else if (eta<1.478) SF += 0.002;
			else if (eta<2.5) SF += 0.005; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF -= 0.003;
			else if (eta<1.478) SF -= 0.;
			else if (eta<2.5) SF -= 0.005; 			
		}
	}
	else if (pt<50){
		
		if (eta<0.8) SF = 0.950;
		else if (eta<1.478) SF = 0.949;
		else if (eta<2.5) SF = 0.937;
		
		if (syst>0){
			
			if (eta<0.8) SF +=0.001;
			else if (eta<1.478) SF += 0.002;
			else if (eta<2.6) SF += 0.008; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF -= 0.001;
			else if (eta<1.478) SF -= 0.002;
			else if (eta<2.6) SF -= 0.008; 
			
		}
	}
	else if (pt<200){
		
		if (eta<0.8) SF = 0.957;
		else if (eta<1.478) SF = 0.959;
		else if (eta<2.5) SF = 0.954;
		
		if (syst>0){
			
			if (eta<0.8) SF += 0.001;
			else if (eta<1.478) SF += 0.003;
			else if (eta<2.6) SF += 0.011; 
			
		}
		if (syst<0){
			
			if (eta<0.8) SF -= 0.001;
			else if (eta<1.478) SF -= 0.003;
			else if (eta<2.6) SF -= 0.01; 
			
		}
	}

	return SF;
  
}


double AnalyzerCore::TopElIDIsoEff(float pt, float eta){

	// ID && Iso Efficiency
	//	if(!isData) return 1.;

	
	double Eff = 1.;
	
	if( pt > 30. && pt<40.){
		if (eta<0.8) Eff = Eff = 1/0.834;
		else if (eta<1.478) Eff = 1/0.796;
		else if (eta<2.5) Eff = 1/0.739;
	}
	else if (pt<50){
		
  	  if (eta<0.8) Eff = 1/0.885;
	  else if (eta<1.478) Eff = 1/0.878;
	  else if (eta<2.5) Eff = 1/0.814;

	}
	else if (pt<200){

  	  if (eta<0.8) Eff = 1/0.908;
	  else if (eta<1.478) Eff = 1/0.906;
	  else if (eta<2.5) Eff = 1/0.873;
	}

  return Eff;
  
}


double AnalyzerCore::TopMuIDEff(float eta, int syst=0){

	//	if(!isData) return 1.;
   
	double Eff = 1.;
	
	
	if (eta<0.9){
		Eff = 0.9582;
		if (syst>0) Eff+=0.0001;
		if (syst<0) Eff-=0.0001;
	}
	else if (eta<1.2){
		Eff = 0.9612;
		if (syst>0) Eff+=0.0002;
		if (syst<0) Eff-=0.0002;
	}
	else if (eta<2.1){
		Eff = 0.9535;
		if (syst>0) Eff += 0.0002;
		if (syst<0) Eff -= 0.0002;		
	}
	else if (eta<2.4){
		Eff = 0.9495;
		if (syst>0) Eff += 0.0004;
		if (syst<0) Eff -=0.0004;
	}

	return Eff;
}


double AnalyzerCore::TopMuIDSF( float eta, int syst=0){

	if(isData) return 1.;
	//	if(mu.size() != 1) return 1.;
   
	double SF = 1.;
	
	//	if ( mu.at(0).Pt() < 20) return 1.;
	
	//	float eta = fabs(mu.at(0).Eta());
	
	if (eta<0.9){
		SF = 0.9930;
		if (syst>0) SF+=0.0002;
		if (syst<0) SF-=0.0002;
	}
	else if (eta<1.2){
		SF = 0.9942;
		if (syst>0) SF+=0.0003;
		if (syst<0) SF-=0.0003;
	}
	else if (eta<2.1){
		SF = 0.9968;
		if (syst>0) SF += 0.0002;
		if (syst<0) SF -= 0.0002;		
	}
	else if (eta<2.4){
		SF = 0.9963;
		if (syst>0) SF += 0.0006;
		if (syst<0) SF -=0.0006;
	}

	return SF;
}


double AnalyzerCore::TopMuIsoEff(float eta, int syst = 0){

	//if(!isData) return 1.;
	double Eff = 1.;
	
	
	if (eta<0.9){
		Eff = 0.9289;
		if (syst>0) Eff+=0.0001;
		if (syst<0) Eff-=0.0001;
	}
	else if (eta<1.2){
		Eff = 0.9444;
		if (syst>0) Eff+=0.0002;
		if (syst<0) Eff-=0.0002;
	}
	else if (eta<2.1){
		Eff = 0.9534;
		if (syst>0) Eff += 0.0001;
		if (syst<0) Eff -= 0.0001;		
	}
	else if (eta<2.4){
		Eff = 0.9342;
		if (syst>0) Eff += 0.0003;
		if (syst<0) Eff -=0.0003;
	}

	return Eff;
}

double AnalyzerCore::TopMuIsoSF( float eta, int syst = 0){

	if(isData) return 1.;
	//	if(mu.size() != 1) return 1.;
   
	double SF = 1.;
	
	//if ( mu.at(0).Pt() < 20) return 1.;
	
	//	float eta = fabs(mu.at(0).Eta());
	
	if (eta<0.9){
		SF = 0.9959;
		if (syst>0) SF+=0.0002;
		if (syst<0) SF-=0.0002;
	}
	else if (eta<1.2){
		SF = 1.0005;
		if (syst>0) SF+=0.0004;
		if (syst<0) SF-=0.0004;
	}
	else if (eta<2.1){
		SF = 1.0027;
		if (syst>0) SF += 0.0002;
		if (syst<0) SF -= 0.0002;		
	}
	else if (eta<2.4){
		SF = 1.0633;
		if (syst>0) SF += 0.0007;
		if (syst<0) SF -=0.0007;
	}

	return SF;
}


double AnalyzerCore::TopMuTriggerSF( float eta, int syst = 0){

	if(isData) return 1.;
	//  if(mu.size() != 1) return 1.;
	
	//  float eta = fabs(mu.at(0).Eta());
	
	double SF = 1.;
	
	if (eta<0.9){
		SF = 0.9837;
		if (syst>0) SF+=0.0002;
		if (syst<0) SF-=0.0002;
	}
	else if (eta<1.2){
		
		SF = 0.9656;
		if (syst>0) SF +=0.0007;
		if (syst<0) SF -=0.0007;
	}
	else if (eta<2.1){
		
		SF = 0.9962;
		if (syst>0) SF += 0.0005;
		if (syst<0) SF -= 0.0005;
	}
	
	return SF;
	
}

double AnalyzerCore::TopMuTriggerEff(float eta, int syst = 0){
	//  if(isData) return 1.;
  
  double Eff = 1.;

  if (eta<0.9){
	  Eff = 0.9377;
	  if (syst>0) Eff+=0.0001;
	  if (syst<0) Eff-=0.0001;
  }
  else if (eta<1.2){
	  Eff = 0.8397;
	  if (syst>0) Eff +=0.0003;
	  if (syst<0) Eff -=0.0003;
  }
  else if (eta<2.1){
	  Eff = 0.8179;
	  if (syst>0) Eff += 0.0002;
	  if (syst<0) Eff -= 0.0002;
  }

  return Eff;
  
}




void AnalyzerCore::AddTriggerToList(TString triggername){
  
  triggerlist.push_back(triggername);
}

AnalyzerCore::~AnalyzerCore(){
  
  Message("In AnalyzerCore Destructor" , INFO);
  if(FRHist) delete FRHist;

  for(map<TString, TH1*>::iterator it = maphist.begin(); it!= maphist.end(); it++){
    delete it->second;
  }
  maphist.clear();

  for(map<TString, TH2*>::iterator it = maphist2D.begin(); it!= maphist2D.end(); it++){
    delete it->second;
  }
  maphist2D.clear();



  for(map<TString, MuonPlots*>::iterator it = mapCLhistMu.begin(); it != mapCLhistMu.end(); it++){
    delete it->second;
  }
  mapCLhistMu.clear();
  

  for(map<TString, JetPlots*>::iterator it = mapCLhistJet.begin(); it != mapCLhistJet.end(); it++){
    delete it->second;
  }
  mapCLhistJet.clear();

  for(map<TString, ElectronPlots*>::iterator it = mapCLhistEl.begin(); it != mapCLhistEl.end(); it++){
    delete it->second;
  }
  mapCLhistEl.clear();

  for(map<TString, SignalPlots*>::iterator it = mapCLhistSig.begin(); it != mapCLhistSig.end(); it++){
    delete it->second;
  }
  mapCLhistSig.clear();
  
  }

//###
//###   IMPORTANT BASE FUNCTION: SETS UP EVENT FOR ALL CYCLES
//###

void AnalyzerCore::SetUpEvent(Long64_t entry, float ev_weight) throw( LQError ) {
  
  Message("In SetUpEvent(Long64_t entry) " , DEBUG);
  m_logger << DEBUG << "This is entry " << entry << LQLogger::endmsg;
  if (!fChain) throw LQError( "Chain is not initialized",  LQError::SkipCycle );     
  
  if(LQinput){
    m_logger << DEBUG << "k_isdata = " << k_isdata << " and isData = " << isData << LQLogger::endmsg;
    if(k_isdata != isData) throw LQError( "!!! Event is confused. It does not know if it is data or MC", LQError::SkipCycle );
  }
  else isData = k_isdata;
  
  if (!(entry % output_interval)) {
    m_logger << INFO <<  "Processing entry " << entry <<  "/" << nentries << LQLogger::endmsg;

  }

  snu::KEvent eventinfo = GetEventInfo();
  
  if(k_isdata){
    if(ev_weight!=1.) Message("ERROR in setting weights. This is Data...", INFO);
    MCweight=1.;
    weight = 1.;
  }
  else {
    MCweight = eventinfo.MCWeight(); //Get MC weight here FIX ME                                                              
    weight= ev_weight; 
  }
  
  //
  // creates object that stores all SKTree classes	
  //                                                                                                        

  snu::KTrigger triggerinfo = GetTriggerInfo(triggerlist);

  std::vector<snu::KJet> skjets= GetAllJets();
  std::vector<snu::KGenJet> skgenjets=GetAllGenJets();
  
  LQEvent lqevent(GetAllMuons(), GetAllElectrons(), GetAllTaus(), skjets, skgenjets,GetTruthParticles(), triggerinfo,eventinfo);
  
  //  eventbase is master class to use in analysis 
  //
  
  eventbase = new EventBase(lqevent);
  
}

float AnalyzerCore::SumPt( std::vector<snu::KJet> particles){

  float sumpt=0.;
  
  for(std::vector<snu::KJet>::iterator it = particles.begin(); it != particles.end(); it++){
    sumpt += it->Pt();
  }
  return sumpt;
}
  

std::vector<snu::KElectron> AnalyzerCore::ShiftElectronEnergy(std::vector<snu::KElectron> electrons, bool applyshift){
  
  std::vector<snu::KElectron> shiftedel;

  for(unsigned int iel=0; iel < electrons.size(); iel++){
    float scale =0.98;

    if(applyshift)electrons.at(iel).SetPtEtaPhiM(electrons.at(iel).Pt()*scale, electrons.at(iel).Eta(), electrons.at(iel).Phi(), 0.511e-3);
    shiftedel.push_back(electrons.at(iel));
  }    
  return shiftedel;
}

bool AnalyzerCore::isPrompt(long pdgid) {
  /// mother pdgid
  pdgid = abs(pdgid);
  if (pdgid == 24) return true; // Z
  else if (pdgid == 23) return true; // W
  else if (pdgid == 15) return true; // taus
  else if (pdgid == 90) return true; // N
  else return false;
}


float  AnalyzerCore::JetResCorr(snu::KJet jet, std::vector<KGenJet> genjets){
  
  /// This function is not needed when smeaing is already applied to LQNtuples in production stage
  return 1.;
  
  float genpt= -999.;
  for(std::vector<KGenJet>::iterator it = genjets.begin(); it != genjets.end(); it++){
    if(it->DeltaR(jet) < 0.3){
      genpt = it->Pt();
    }
  }
  
  double fabs_eta = fabs ( jet.Eta() );
  float c(0.);
  if      ( fabs_eta > 0.0 && fabs_eta <= 0.5 ) c= 1.052;
  else if ( fabs_eta > 0.5 && fabs_eta <= 1.1 ) c= 1.057;
  else if ( fabs_eta > 1.1 && fabs_eta <= 1.7 ) c= 1.096;
  else if ( fabs_eta > 1.7 && fabs_eta <= 2.3 ) c= 1.134;
  else                                          c= 1.288;
  
  float newpt = std::max(0., genpt + c*(jet.Pt() - genpt));
  if(genpt < 0.) newpt = jet.Pt();
  
  return newpt;
}

void AnalyzerCore::EndEvent()throw( LQError ){

  delete eventbase;                                                                                                            

}
  
void AnalyzerCore::CheckFile(TFile* file)throw( LQError ){

  if(file) m_logger << INFO << "Analyzer: File " << file->GetName() << " was found." << LQLogger::endmsg;
  else m_logger  << INFO <<"Analyzer  " << file->GetName()  << "  : ERROR Rootfile failed to open." << LQLogger::endmsg;

  if(!file)  throw LQError( "!!! File is not found", LQError::SkipCycle);
  return;
}

bool AnalyzerCore::PassTrigger(vector<TString> list, int& prescaler){
  
  return TriggerSelector(list, eventbase->GetTrigger().GetHLTInsideDatasetTriggerNames(), eventbase->GetTrigger().GetHLTInsideDatasetTriggerDecisions(), eventbase->GetTrigger().GetHLTInsideDatasetTriggerPrescales(), prescaler);

}

TDirectory* AnalyzerCore::GetTemporaryDirectory(void) const
{
  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:                                              
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                                                       
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}


void AnalyzerCore::Message(TString message, LQMsgType type){
  m_logger <<  type << message << LQLogger::endmsg;
}


void AnalyzerCore::MakeCleverHistograms(histtype type, TString clhistname ){
  
  //// ELECTRON PLOTs                                                                                          
  if(type==elhist) mapCLhistEl[clhistname] = new ElectronPlots(clhistname);
  //// MUON PLOTs                                                                                              
  if(type==muhist) mapCLhistMu[clhistname] = new MuonPlots(clhistname);
  /// JET PLOTs                                                                                                
  if(type==jethist) mapCLhistJet[clhistname] = new JetPlots(clhistname);
  /// Signal plots                                                                                             
  if(type==sighist)  mapCLhistSig[clhistname] = new SignalPlots(clhistname);
      
  return;
}

void AnalyzerCore::MakeHistograms(){
  //// Additional plots to make                                                                                
  maphist.clear();
  maphist2D.clear();

    
}

void AnalyzerCore::MakeHistograms(TString hname, int nbins, float xbins[]){
  maphist[hname] =  new TH1F(hname.Data(),hname.Data(),nbins,xbins);
}

void AnalyzerCore::MakeHistograms(TString hname, int nbins, float xmin, float xmax){

  maphist[hname] =  new TH1F(hname.Data(),hname.Data(),nbins,xmin,xmax);
}

void AnalyzerCore::MakeHistograms2D(TString hname, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax) {

  maphist2D[hname] =  new TH2F(hname.Data(),hname.Data(),nbinsx,xmin,xmax, nbinsy,ymin,ymax);
}

void AnalyzerCore::MakeHistograms2D(TString hname, int nbinsx,  float xbins[], int nbinsy,  float ybins[]) {

  maphist2D[hname] =  new TH2F(hname.Data(),hname.Data(),nbinsx , xbins, nbinsy,ybins);
}

bool AnalyzerCore::PassBasicEventCuts(){
  
  bool pass (true);
  
  ///https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
  /// The recommendations of the MET group regarding noise cleaning are summarized in the talk https://indico.cern.ch/getFile.py/access?subContId=1&contribId=4&resId=0&materialId=slides&confId=172431
  
  //CSC tight beam halo filter
  if (!eventbase->GetEvent().PassBeamHaloFilterTight()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassBeamHaloFilterTight " << LQLogger::endmsg;
  }
  //if (!eventbase->GetEvent().PassBeamHaloFilterLoose()) pass = false;
  //HBHE noise filter with isolated noise rejection
  if (!eventbase->GetEvent().PassHBHENoiseFilter()) {
    pass = false; 
    m_logger << DEBUG << "Event Fails PassHBHENoiseFilter " << LQLogger::endmsg;
  }
  //HCAL laser filter (post-ICHEP: updated to reduce over-tagging rate in channels with low Bias Voltage)
  
  //ECAL dead cell trigger primitive (TP) filter
  if(eventbase->GetEvent().PassEcalDeadCellTriggerPrimitiveFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalDeadCellTriggerPrimitiveFilter" << LQLogger::endmsg;
  }
  if(  eventbase->GetEvent().PassEcalDeadCellBoundaryEnergyFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalDeadCellBoundaryEnergyFilter" << LQLogger::endmsg;
  }
  //Tracking failure filter
  if (eventbase->GetEvent().IsTrackingFailure()) {
    pass = false;
    m_logger << DEBUG << "Event Fails IsTrackingFailure" << LQLogger::endmsg; 
  }
  //Bad EE Supercrystal filter (post-ICHEP: extend to include an additional problematic SC --only for 2012)
  if (eventbase->GetEvent().PassBadEESupercrystalFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassBadEESupercrystalFilter" << LQLogger::endmsg;
  }
  //ECAL Laser correction filter (only mandatory for 53X rereco of 2012A+B, i.e., Jul13 rereco; An optional filter for 2012C prompt reco Mandatory for Jan2013 ReReco)
  if(eventbase->GetEvent().PassEcalLaserCorrFilter()) {
    pass = false;
    m_logger << DEBUG << "Event Fails PassEcalLaserCorrFilter" << LQLogger::endmsg;
  }
  //Tracking POG filters (new. Only work on AOD >=53X)
  if(eventbase->GetEvent().PassTrackingFailureFilter()){
    m_logger << DEBUG << "Event Fails PassTrackingFailureFilter" << LQLogger::endmsg;
    pass = false;
  }
  return pass;
}



void AnalyzerCore::FillHist(TString histname, float value, float w, float xbins[], int nbins){
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  
  else{
    if (nbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms(histname, nbins, xbins);
    if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  }

}

void AnalyzerCore::FillHist(TString histname, float value, float w, float xmin, float xmax, int nbins){
  
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  
  else{
    if (nbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms(histname, nbins, xmin, xmax);
    if(GetHist(histname)) GetHist(histname)->Fill(value, w);
  }
  
}

void AnalyzerCore::FillHist(TString histname, float value1, float value2, float w, float xmin, float xmax, int nbinsx, float ymin, float ymax, int nbinsy){

  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist2D(histname)) GetHist2D(histname)->Fill(value1,value2, w);
  else{
    if (nbinsx < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms2D(histname, nbinsx, xmin, xmax,nbinsy, ymin, ymax );
    if(GetHist2D(histname)) GetHist2D(histname)->Fill(value1,value2, w);
  }

}

void AnalyzerCore::FillHist(TString histname, float valuex, float valuey, float w, float xbins[], int nxbins, float ybins[], int nybins){
  m_logger << DEBUG << "FillHist : " << histname << LQLogger::endmsg;
  if(GetHist2D(histname)) GetHist2D(histname)->Fill(valuex,valuey, w);

  else{
    if (nxbins < 0) {
      m_logger << ERROR << histname << " was NOT found. Nbins was not set also... please configure histogram maker correctly" << LQLogger::endmsg;
      exit(0);
    }
    m_logger << DEBUG << "Making the histogram" << LQLogger::endmsg;
    MakeHistograms2D(histname, nxbins, xbins, nybins, ybins );
    if(GetHist2D(histname)) GetHist2D(histname)->Fill(valuex, valuey, w);
  }

}



void AnalyzerCore::FillHist(TString histname, float value, float w){

  if(GetHist(histname)) GetHist(histname)->Fill(value, w);  /// Plots Z peak                                   
  else m_logger << INFO << histname << " was NOT found. Will add the histogram to the hist map on first event." << LQLogger::endmsg;
  
  
  return;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KMuon> muons, double w){

  if(type==muhist){
    map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.find(hist);
    if(mupit != mapCLhistMu.end()) mupit->second->Fill(w,muons);
    else m_logger << INFO  << hist << " not found in mapCLhistMu" << LQLogger::endmsg;
  }
  else  m_logger << INFO  << "Type not set to muhist, is this a mistake?" << LQLogger::endmsg;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KElectron> electrons, double rho, double w){

  if(type==elhist){
    map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.find(hist);
    if(elpit !=mapCLhistEl.end()) elpit->second->Fill(w,electrons,rho);
    else m_logger << INFO  << hist << " not found in mapCLhistEl" <<LQLogger::endmsg;
  }
  else  m_logger << INFO  << "Type not set to elhist, is this a mistake?" << LQLogger::endmsg;
}

void AnalyzerCore::FillCLHist(histtype type, TString hist, vector<snu::KJet> jets, double w){

  if(type==jethist){
    map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.find(hist);
    if(jetpit !=mapCLhistJet.end()) jetpit->second->Fill(w,jets);
    else m_logger << INFO  << hist << " not found in mapCLhistJet" <<LQLogger::endmsg;
  }
  else  m_logger << INFO  <<"Type not set to jethist, is this a mistake?" << LQLogger::endmsg;

}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){

    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, muons, electrons, jets,w, 0.);
    else {
      mapCLhistSig[hist] = new SignalPlots(hist);
      sigpit = mapCLhistSig.find(hist);
      sigpit->second->Fill(ev, muons, electrons, jets,w, 0.);
    }
  }
  else  m_logger << INFO  <<"Type not set to sighist, is this a mistake?" << LQLogger::endmsg;
}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KMuon> muons, vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w, Double_t weight_err){

  if(type==sighist){

    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, muons, electrons, jets,w);
    else {
      mapCLhistSig[hist] = new SignalPlots(hist);
      sigpit = mapCLhistSig.find(hist);
      sigpit->second->Fill(ev, muons, electrons, jets,w);
    }
  }
  else  m_logger << INFO  <<"Type not set to sighist, is this a mistake?" << LQLogger::endmsg;
}


void AnalyzerCore::FillCLHist(histtype type, TString hist, snu::KEvent ev,vector<snu::KElectron> electrons, vector<snu::KJet> jets,double w){

  if(type==sighist){
    map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.find(hist);
    if(sigpit !=mapCLhistSig.end()) sigpit->second->Fill(ev, electrons, jets, w, 0.);
    else {
      mapCLhistSig[hist] = new SignalPlots(hist);
      sigpit = mapCLhistSig.find(hist);
      sigpit->second->Fill(ev, electrons, jets, w, 0.);
    }
  }
  else  m_logger << INFO  <<"Type not set to sighist, is this a mistake?" << LQLogger::endmsg;
}


void AnalyzerCore::WriteHistograms() throw (LQError){
  // This function is called after the cycle is ran. It wrues all histograms to the output file. This function is not used by user. But by the contrioller code.
  WriteHists();
  WriteCLHists();
}

  
void AnalyzerCore::WriteCLHists(){

  for(map<TString, MuonPlots*>::iterator mupit = mapCLhistMu.begin(); mupit != mapCLhistMu.end(); mupit++){

    Dir = m_outputFile->mkdir(mupit->first);
    m_outputFile->cd( Dir->GetName() );
    mupit->second->Write();
    m_outputFile->cd();
  }

  for(map<TString, ElectronPlots*>::iterator elpit = mapCLhistEl.begin(); elpit != mapCLhistEl.end(); elpit++)\
    {

      Dir = m_outputFile->mkdir(elpit->first);
      m_outputFile->cd( Dir->GetName() );
      elpit->second->Write();
      m_outputFile->cd();
    }

  for(map<TString, JetPlots*>::iterator jetpit = mapCLhistJet.begin(); jetpit != mapCLhistJet.end(); jetpit++)\
    {
      
      Dir = m_outputFile->mkdir(jetpit->first);
      m_outputFile->cd( Dir->GetName() );
      jetpit->second->Write();
      m_outputFile->cd();
    }
  for(map<TString, SignalPlots*>::iterator sigpit = mapCLhistSig.begin(); sigpit != mapCLhistSig.end(); sigpit++){
    
    Dir = m_outputFile->mkdir(sigpit->first);
    m_outputFile->cd( Dir->GetName() );
    sigpit->second->Write();
    m_outputFile->cd();
  }

  return;
}

void AnalyzerCore::WriteHists(){

  /// Open Output rootfile
  m_outputFile->cd();

  for(map<TString, TH1*>::iterator mapit = maphist.begin(); mapit != maphist.end(); mapit++){
    
    
    
    if(mapit->first.Contains("closejet")){
      if(!m_outputFile->GetDirectory( "closejet" )){
	Dir = m_outputFile->mkdir("closejet");
	m_outputFile->cd( Dir->GetName() );
      }
      else  m_outputFile->cd("closejet");
      mapit->second->Write();
      m_outputFile->cd();
    }

    else if (mapit->first.Contains("awayjet")){
      if(!m_outputFile->GetDirectory("awayjet")){
        Dir = m_outputFile->mkdir("awayjet");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("awayjet");
      mapit->second->Write();
      m_outputFile->cd();
    }

    else if (mapit->first.Contains("MCSSclo")){
      if(!m_outputFile->GetDirectory("MCclosure")){
	Dir = m_outputFile->mkdir("MCclosure");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("MCclosure");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("mcclosure")){
      if(!m_outputFile->GetDirectory("MCclosure")){
        Dir = m_outputFile->mkdir("MCclosure");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("MCclosure");
      mapit->second->Write();
      m_outputFile->cd();
    }

    else if (mapit->first.Contains("FakeBkg")){
      if(!m_outputFile->GetDirectory("FakeBkg")){
	Dir = m_outputFile->mkdir("FakeBkg");
	m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("FakeBkg");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("susyid")){
      if(!m_outputFile->GetDirectory("susyid")){
        Dir = m_outputFile->mkdir("susyid");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("susyid");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("medium")){
      if(!m_outputFile->GetDirectory("medium")){
        Dir = m_outputFile->mkdir("medium");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("medium");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("tight")){
      if(!m_outputFile->GetDirectory("tight")){
        Dir = m_outputFile->mkdir("tight");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("tight");
      mapit->second->Write();
      m_outputFile->cd();
    }
    
    else if (mapit->first.Contains("limithist")){
      
      if(!m_outputFile->GetDirectory("limithist")){
        Dir = m_outputFile->mkdir("limithist");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("limithist");
      mapit->second->Write();
      m_outputFile->cd();

    }
    
    else if (mapit->first.Contains("eventcutflow")){
      if(!m_outputFile->GetDirectory("CutFlow")){
        Dir = m_outputFile->mkdir("CutFlow");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("CutFlow");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("eff_electron")){
      if(!m_outputFile->GetDirectory("Efficiency")){
        Dir = m_outputFile->mkdir("Efficiency");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("Efficiency");
      mapit->second->Write();
      m_outputFile->cd();
    }
    
    else if (mapit->first.Contains("sigeff")){
      if(!m_outputFile->GetDirectory("Efficiency")){
        Dir = m_outputFile->mkdir("Efficiency");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("Efficiency");
      mapit->second->Write();
      m_outputFile->cd();
    }
    else if (mapit->first.Contains("Selection")){
      if(!m_outputFile->GetDirectory("Efficiency")){
        Dir = m_outputFile->mkdir("Efficiency");
        m_outputFile->cd(Dir->GetName() );
      }
      else m_outputFile->cd("Efficiency");
      mapit->second->Write();
      m_outputFile->cd();
    }



    
    else {
      mapit->second->Write();
    }
  }

  for(map<TString, TH2*>::iterator mapit = maphist2D.begin(); mapit != maphist2D.end(); mapit++){
    mapit->second->Write();
  }


  return;
}

TH1* AnalyzerCore::GetHist(TString hname){

  TH1* h = NULL;
  std::map<TString, TH1*>::iterator mapit = maphist.find(hname);
  if(mapit != maphist.end()) return mapit->second;
  else m_logger << DEBUG  << hname << " was not found in map" << LQLogger::endmsg;

  return h;
}



TH2* AnalyzerCore::GetHist2D(TString hname){

  TH2* h = NULL;
  std::map<TString, TH2*>::iterator mapit = maphist2D.find(hname);
  if(mapit != maphist2D.end()) return mapit->second;
  else m_logger << DEBUG  << hname << " was not found in map" << LQLogger::endmsg;

  return h;
}


bool AnalyzerCore::Zcandidate(std::vector<snu::KElectron> electrons, float interval, bool require_os){
  
  if(electrons.size()!=2) return false;
  if(require_os&&SameCharge(electrons)) return false;
  
  KParticle Z = electrons.at(0) + electrons.at(1);
  if(fabs(Z.M() - 90.) <  interval) return true;
  else return false;
  
}
  
bool AnalyzerCore::SameCharge(std::vector<snu::KElectron> electrons){
  
  if(electrons.size()!=2) return false;
  if(electrons.at(0).Charge() == electrons.at(1).Charge()) return true;
  return false;
}

int AnalyzerCore::NBJet(std::vector<snu::KJet> jets){
  
  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
  }
  return nbjet;
}


double AnalyzerCore::MuonDYMassCorrection(std::vector<snu::KMuon> mu, double w){
  
  if(mu.size()< 2) return 0.;
  snu::KParticle Z = mu.at(0) + mu.at(1);
  
  double factor (1.);
  if(Z.M() > 90.){
    factor = 8.37401e-01 + 1.61277e-03*Z.M();
  }
  return w*factor;
}

float AnalyzerCore::CFRate(snu::KElectron el, bool use_oldrates){
  
  Double_t frac = 0. ;
  float pt = el.Pt();
  Double_t p0 = 0. ;
  Double_t p1 = 0. ;

  Double_t scale_factor_EE = 1. ;
  Double_t scale_factor_BB = 1. ;

  float eta = el.Eta();
  
  //--root fitting
  if( fabs(eta) <= 0.9 ) { // inner BB region

    scale_factor_BB = 1.22 ; // BB

    p0 = 3.31e-05 ; p1 = -6.5e-04 ; // root fit
    // p0 = 2.8e-05 ; p1 = 0. ;// UK eye fit

    frac = p0 + p1*(1./pt) ;
    if( 1./pt < 0.017 ){
      p0 = 1.92e-04 ; p1 = -0.011 ;
      frac = max(p0 + p1*(1./pt), frac);
    }
    frac = max(frac,0.);
    frac *=scale_factor_BB ;

  }else if( fabs(eta) > 0.9 && fabs(eta) <= 1.4442 ){ // outer BB region
    scale_factor_BB = 1.22 ; // BB
    p0 = 2.21e-04 ; p1 = -5.1e-03 ; // root fit
    //    p0 = 1.2e-04 ; p1 = 0. ; // UK eye fit
    frac = p0 + p1*(1./pt) ;
    if( 1./pt < 0.02 ){
      p0 = 6.35e-04 ; p1 = -0.027 ;
      frac = max(p0 + p1*(1./pt), frac);
    }
    frac = max(frac,0.);
    frac *=scale_factor_BB ;
    
  } else {  // fabs(eta) > 1.4
    
    
    scale_factor_EE = 1.40 ; //
    if(use_oldrates)scale_factor_EE = 1.32;
    //--region:  1/pt > 0.02
    p0 = 4.91e-04 ; p1 = -0.952e-02 ;
    if(use_oldrates){
      p0 = 5.41e-04 ; p1 = -1.10e-02 ;
    }
    frac = p0 + p1*(1./pt) ;

    if( (1./pt) <= 0.02 ){
      p0 = 2.70e-03 ;  p1 = -1.21e-01 ;
      if(use_oldrates){
	p0 = 2.95e-03 ;  p1 = -1.32e-01 ;
      }
      frac = max(p0 + p1*(1./pt), frac) ;
    }
    frac *= scale_factor_EE ;
  }
  
  return float(frac) ;
}

bool AnalyzerCore::IsTight(snu::KMuon muon){
  /// ADD TIGHT MUON REQUIREMENT
  float reliso=0.;
  if (muon.Pt() > 0.01)  reliso = (muon.SumIsoCHDR03() + std::max(0.0, muon.SumIsoNHDR03() + muon.SumIsoPHDR03() - 0.5* muon.SumPUIsoR03()))/muon.Pt() ;
  else reliso = 9999.;
  if (reliso<0) reliso=0.0001;
  
  
  if(( reliso >= 0.05)) return false;
  if(( muon.GlobalChi2() >= 10.)) return false;
 
  if(fabs(muon.dXY()) >= 0.005) return false; 
  return true;
}


bool AnalyzerCore::IsTight(snu::KElectron el, double jetrho , double dxy, double biso, double eiso, bool usetight){
  
  return eventbase->GetElectronSel()->HNIsTight(el, jetrho, dxy, biso, eiso, usetight, false);

}
  

bool AnalyzerCore::IsTight(snu::KElectron electron, double rho){

  return eventbase->GetElectronSel()->HNIsTight(electron, rho, false);
}

vector<snu::KElectron> AnalyzerCore::GetTruePrompt(vector<snu::KElectron> electrons, bool keep_chargeflip, bool keepfake){
  
  vector<int> toremove;
  if(!keepfake){
    toremove.push_back(1);
    toremove.push_back(2);
    toremove.push_back(3);
  }
  if(!keep_chargeflip){
    toremove.push_back(6);
    toremove.push_back(4);
    toremove.push_back(5);
  }

  toremove.push_back(10);
  toremove.push_back(11);
  toremove.push_back(8);
  toremove.push_back(9);
  
  vector<snu::KElectron> prompt_electrons;
  for(unsigned int i = 0; i < electrons.size(); i++){
    if(!isData){  
      bool remove_el=false;
      for(unsigned int j=0; j < toremove.size(); j++){
	if(electrons.at(i).GetType() == toremove.at(j)) remove_el=true;
      }
      if(!remove_el) {
	prompt_electrons.push_back(electrons.at(i));
      }
    }
    else prompt_electrons.push_back(electrons.at(i));
  }/// loop
  

  return prompt_electrons;
}

vector<snu::KMuon> AnalyzerCore::GetTruePrompt(vector<snu::KMuon> muons, bool keepfake){

  vector<int> toremove;
  if(!keepfake){
    toremove.push_back(1);
    toremove.push_back(2);
    toremove.push_back(3);
  }

  vector<snu::KMuon> prompt_muons;
  for(unsigned int i = 0; i < muons.size(); i++){
    if(!k_isdata){
      bool remove_el=false;
      for(unsigned int j=0; j < toremove.size(); j++){
        if(muons.at(i).GetType() == toremove.at(j)) remove_el=true;
      }
      if(!remove_el) prompt_muons.push_back(muons.at(i));
    }// Data
    else prompt_muons.push_back(muons.at(i));
  }/// loop

  return prompt_muons;
}




void AnalyzerCore::CorrectMuonMomentum(vector<snu::KMuon>& k_muons){
  
  vector<TLorentzVector> tlv_muons = MakeTLorentz(k_muons);
  int imu(0);
  for(std::vector<snu::KMuon>::iterator it = k_muons.begin(); it != k_muons.end(); it++, imu++){
    float qter =1.; /// uncertainty
    if(k_isdata)rmcor->momcor_data(tlv_muons[imu], float(it->Charge()), 0, qter);
    else rmcor->momcor_mc(tlv_muons[imu], float(it->Charge()), 0, qter);
    it->SetPtEtaPhiM(tlv_muons[imu].Pt(),tlv_muons[imu].Eta(), tlv_muons[imu].Phi(), tlv_muons[imu].M());
  }
}

 float AnalyzerCore::Get_DataDrivenWeightMC_EM(vector<snu::KMuon> k_muons, vector<snu::KElectron> k_electrons, double rho, TString tag){

   float em_weight = 0.;
   if(k_muons.size()==1 && k_electrons.size()==1){

     bool is_mu1_tight    = IsTight(k_muons.at(0));
     bool is_el1_tight    = IsTight(k_electrons.at(0),rho);


     vector<TLorentzVector> muons=MakeTLorentz(k_muons);
     vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);

     em_weight =m_fakeobj->get_dilepton_em_mceventweight(muons,electrons, is_mu1_tight,is_el1_tight, NBJet( GetJets("ApplyPileUpID")), tag);
     
     
   }
   return em_weight;

 }


float AnalyzerCore::Get_DataDrivenWeight_EM(vector<snu::KMuon> k_muons, vector<snu::KElectron> k_electrons, double rho, int syst){

  float em_weight = 0.;
  if(k_muons.size()==1 && k_electrons.size()==1){

    bool is_mu1_tight    = IsTight(k_muons.at(0));
    bool is_el1_tight    = IsTight(k_electrons.at(0),rho);

    
    vector<TLorentzVector> muons=MakeTLorentz(k_muons);
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    
    em_weight =m_fakeobj->get_dilepton_em_eventweight(muons,electrons, is_mu1_tight,is_el1_tight, NBJet( GetJets("ApplyPileUpID")), syst);
    
    if(muons.at(0).Pt() < 20.) em_weight*= 1.4;

  }
  
  return em_weight;
}

float AnalyzerCore::Get_DataDrivenWeight_MM(vector<snu::KMuon> k_muons){

  float mm_weight = 0.;
  if(k_muons.size()==2){
    
    bool is_mu1_tight    = IsTight(k_muons.at(0));
    bool is_mu2_tight    = IsTight(k_muons.at(1));

    vector<TLorentzVector> muons=MakeTLorentz(k_muons);

    mm_weight =m_fakeobj->get_dilepton_mm_eventweight(muons,  is_mu1_tight,is_mu2_tight);
  }

  return mm_weight;
}




float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons,  double rho){
  
  return Get_DataDrivenWeight_EE(k_electrons, rho, 0.01, 0.09, 0.05, "40", 0); /// dxy cut ,  biso, eciso, awayjet pt
}



float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons ,  double rho, bool usetight,  double dxy, double biso, double eiso,TString cut){
  return Get_DataDrivenWeight_EE(k_electrons, rho, usetight, dxy, biso, eiso, cut, 0);
}


float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons , std::vector<snu::KJet> jets,  double rho,  bool usetight,  double dxy, double biso, double eiso, TString cut, int type){
  float ee_weight = 0.;
  if(k_electrons.size()==2){

    bool is_el1_tight    = IsTight(k_electrons.at(0),  rho, dxy, biso, eiso, usetight);
    bool is_el2_tight    = IsTight(k_electrons.at(1),  rho, dxy, biso, eiso, usetight);
    
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, SumPt(jets), is_el1_tight,is_el2_tight, cut, type, NBJet( GetJets("ApplyPileUpID")));

  }
  return ee_weight;
}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons ,  double rho,  bool usetight,  double dxy, double biso, double eiso, TString cut, int type){

  float ee_weight = 0.;
  if(k_electrons.size()==2){
    
    bool is_el1_tight    = IsTight(k_electrons.at(0),  rho, dxy, biso, eiso, usetight);
    bool is_el2_tight    = IsTight(k_electrons.at(1),  rho, dxy, biso, eiso, usetight);

    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, is_el1_tight,is_el2_tight, cut, type, NBJet( GetJets("ApplyPileUpID")));
        
  }
  return ee_weight;

}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons, double rho, double dxy, double biso, double eiso, TString cut){
  return Get_DataDrivenWeight_EE(k_electrons, rho, dxy, biso, eiso, cut, 0);
}

float AnalyzerCore::Get_DataDrivenWeight_EE(vector<snu::KElectron> k_electrons, double rho, double dxy, double biso, double eiso, TString cut, int type){
  
  float ee_weight = 0.;
  if(k_electrons.size()==2){
    
    bool is_el1_tight    = IsTight(k_electrons.at(0),  rho, dxy, biso, eiso, true);
    bool is_el2_tight    = IsTight(k_electrons.at(1),  rho, dxy, biso, eiso, true);
    
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    ee_weight =m_fakeobj->get_dilepton_ee_eventweight(electrons, is_el1_tight,is_el2_tight, cut, type, NBJet( GetJets("ApplyPileUpID")));
    
  }
  return ee_weight;
}



float  AnalyzerCore::Get_DataDrivenWeight_E(vector<snu::KElectron> k_electrons, int njets, int nbjets, double rho, double dxy, double biso, double eiso, bool    usetight,TString cut, bool applypucorr){
  
  if(k_electrons.size()==1){
    bool is_el1_tight    = IsTight(k_electrons.at(0), rho, dxy, biso, eiso,  usetight);
    vector<TLorentzVector> electrons=MakeTLorentz(k_electrons);
    
    TString rcut = cut;
    
    float r = 1.;


    float f = m_fakeobj->getFakeRate_electronEta(0, k_electrons.at(0).Pt(), fabs(k_electrons.at(0).Eta()), cut);
    
    float w = m_fakeobj->lepton_weight(!is_el1_tight, r,f);
    return w;
  }
  return 0.;
}
    


vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KElectron> el){

  vector<TLorentzVector> tl_el;
  for(vector<KElectron>::iterator itel=el.begin(); itel!=el.end(); ++itel) {
    TLorentzVector tmp_em;
    tmp_em.SetPtEtaPhiM((*itel).Pt(),(*itel).Eta(),(*itel).Phi(),(*itel).M());
    tl_el.push_back(tmp_em);
  }
  return tl_el;
}

vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KMuon> mu){
  
  vector<TLorentzVector> tl_mu;
  for(vector<KMuon>::iterator itmu=mu.begin(); itmu!=mu.end(); ++itmu) {
    TLorentzVector tmp_mu;
    tmp_mu.SetPtEtaPhiM((*itmu).Pt(),(*itmu).Eta(),(*itmu).Phi(),(*itmu).M());
    tl_mu.push_back(tmp_mu);
  }
  return tl_mu;
}


vector<TLorentzVector> AnalyzerCore::MakeTLorentz(vector<snu::KJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiM((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).M());
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}





