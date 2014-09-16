// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQFakeRateCalculator_El Frame - ROOT-based analysis framework for Korea SNU
OB * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "FakeRateCalculator_El.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (FakeRateCalculator_El);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
FakeRateCalculator_El::FakeRateCalculator_El() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("FakeRateCalculator_El");

  Message("In FakeRateCalculator_El constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void FakeRateCalculator_El::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  return;
}


void FakeRateCalculator_El::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   
  std::vector<TString> triggerslist_diel;
  triggerslist_diel.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   


  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->Selection(jetColl);
  /// With IP cut and Tight
  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithIPCut(electronLooseColl); 

  /// No IP  and Tight
  std::vector<snu::KElectron> electronLooseColl_tight_noipcut;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl_tight_noipcut);
  
  // No IP and Medium
  std::vector<snu::KElectron> electronLooseColl_medium_noipcut;
  
  std::vector<snu::KElectron> electronLooseColl_iso05,electronLooseColl_iso07;
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.5,electronLooseColl_iso05);
  eventbase->GetElectronSel()->HNLooseElectronSelectionWithDiffISO(0.7,electronLooseColl_iso07);
  

  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }
  
  
  std::vector<snu::KElectron> electronTightColl_dxy05, electronTightColl_dxy10, electronTightColl_dxy15,
    electronTightColl_dxy20,  electronTightColl_dxy25,  electronTightColl_dxy30, electronTightColl_medium, electronTightColl_tight,
    
    electronTightColl_dr03_150, electronTightColl_dr03_125, electronTightColl_dr03_100,  electronTightColl_dr03_090,
    electronTightColl_dr03_100_detiso,electronTightColl_dr03_090_detiso,
    electronTightColl_dr03_080, electronTightColl_dr03_070, electronTightColl_dr03_060, electronTightColl_dr03_050,
  
    electronTightColl_dr04_150, electronTightColl_dr04_125, electronTightColl_dr04_100,
    electronTightColl_dr04_090,  electronTightColl_dr04_080,  electronTightColl_dr04_070,
    electronTightColl_dr04_060,   electronTightColl_dr04_050,
  
    electronTightColl_dr03_b150_e125,  electronTightColl_dr03_b150_e100,
    electronTightColl_dr03_b150_e090,  electronTightColl_dr03_b150_e080,
    electronTightColl_dr03_b150_e070,  electronTightColl_dr03_b150_e060,
    electronTightColl_dr03_b150_e050,
    
    electronTightColl_dr03_b125_e100,   electronTightColl_dr03_b125_e090,
    electronTightColl_dr03_b125_e080,   electronTightColl_dr03_b125_e070,
    electronTightColl_dr03_b125_e060,   electronTightColl_dr03_b125_e050,
    
    electronTightColl_dr03_b100_e125,   electronTightColl_dr03_b100_e090,
    electronTightColl_dr03_b100_e080,   electronTightColl_dr03_b100_e070,
    electronTightColl_dr03_b100_e060,   electronTightColl_dr03_b100_e050,

    electronTightColl_dr03_b090_e125,    electronTightColl_dr03_b090_e100,
    electronTightColl_dr03_b090_e080,    electronTightColl_dr03_b090_e070,
    electronTightColl_dr03_b090_e060,    electronTightColl_dr03_b090_e050,
    electronTightColl_dr03_b090_e050_detiso,

    electronTightColl_dr03_b080_e125,    electronTightColl_dr03_b080_e100,
    electronTightColl_dr03_b080_e090,    electronTightColl_dr03_b080_e070,
    electronTightColl_dr03_b080_e060,    electronTightColl_dr03_b080_e050,

    electronTightColl_dr03_b070_e125,    electronTightColl_dr03_b070_e100,    electronTightColl_dr03_b070_e090,
    electronTightColl_dr03_b070_e080,    electronTightColl_dr03_b070_e060,
    electronTightColl_dr03_b070_e050,
    electronTightColl_dr03_b050_e125,    electronTightColl_dr03_b050_e100,    electronTightColl_dr03_b050_e090,
    electronTightColl_dr03_b050_e080,    electronTightColl_dr03_b050_e070,
    electronTightColl_dr03_b050_e060,   electronLooseColl_dxy20;

  //// electronLooseColl : iso < 0.6, dxy < 100.; 
  for(unsigned int iel = 0; iel < electronLooseColl_tight_noipcut.size(); iel++){
    
    if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.020 )  electronLooseColl_dxy20.push_back(electronLooseColl_tight_noipcut.at(iel));
    
    float LeptonRelIsoDR03 = electronLooseColl_tight_noipcut.at(iel).RelIso03(eventbase->GetEvent().JetRho() , electronLooseColl_tight_noipcut.at(iel).Pt());
    float LeptonRelIsoDR04 = electronLooseColl_tight_noipcut.at(iel).RelIso04(eventbase->GetEvent().JetRho() , electronLooseColl_tight_noipcut.at(iel).Pt());

    float trkiso =  electronLooseColl_tight_noipcut.at(iel).TrkIsoDR03()/ electronLooseColl_tight_noipcut.at(iel).Pt();
    float ecaliso = electronLooseColl_tight_noipcut.at(iel).ECalIsoDR03()/electronLooseColl_tight_noipcut.at(iel).Pt();
    float hcaliso = electronLooseColl_tight_noipcut.at(iel).HCalIsoDR03()/electronLooseColl_tight_noipcut.at(iel).Pt();
    
    
    bool passNPFiso = true;
    if(trkiso > 0.1) passNPFiso = false;
    if(ecaliso > 0.25) passNPFiso = false;
    if(hcaliso > 0.2)  passNPFiso = false;
    
    
    if (fabs(electronLooseColl_tight_noipcut.at(iel).SCEta()) < 1.479 ){
      if(LeptonRelIsoDR03 < 0.10){
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.005 )  electronTightColl_dxy05.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.010 )  electronTightColl_dxy10.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.015 )  electronTightColl_dxy15.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.020 )  electronTightColl_dxy20.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.025 )  electronTightColl_dxy25.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.030 )  electronTightColl_dxy30.push_back(electronLooseColl_tight_noipcut.at(iel));
      }
    }
    else{
      if(LeptonRelIsoDR03 < 0.10){
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.005 )  electronTightColl_dxy05.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.010 )  electronTightColl_dxy10.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.015 )  electronTightColl_dxy15.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.020 )  electronTightColl_dxy20.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.025 )  electronTightColl_dxy25.push_back(electronLooseColl_tight_noipcut.at(iel));
	if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.030 )  electronTightColl_dxy30.push_back(electronLooseColl_tight_noipcut.at(iel));
      }
    }

    if(fabs(electronLooseColl_tight_noipcut.at(iel).dxy()) < 0.010){
      if(LeptonRelIsoDR03 < 0.15)  electronTightColl_dr03_150.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.125) electronTightColl_dr03_125.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.1)   electronTightColl_dr03_100.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.1 && passNPFiso)   electronTightColl_dr03_100_detiso.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.09)  electronTightColl_dr03_090.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.09 && passNPFiso)   electronTightColl_dr03_090_detiso.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.08)  electronTightColl_dr03_080.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.07)  electronTightColl_dr03_070.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.06)  electronTightColl_dr03_060.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR03 < 0.05)  electronTightColl_dr03_050.push_back(electronLooseColl_tight_noipcut.at(iel));

      if(LeptonRelIsoDR04 < 0.15)  electronTightColl_dr04_150.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.125) electronTightColl_dr04_125.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.1)   electronTightColl_dr04_100.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.09)  electronTightColl_dr04_090.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.08)  electronTightColl_dr04_080.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.07)  electronTightColl_dr04_070.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.06)  electronTightColl_dr04_060.push_back(electronLooseColl_tight_noipcut.at(iel));
      if(LeptonRelIsoDR04 < 0.05)  electronTightColl_dr04_050.push_back(electronLooseColl_tight_noipcut.at(iel));
      
      if (fabs(electronLooseColl_tight_noipcut.at(iel).SCEta()) < 1.479 ){
        if(LeptonRelIsoDR03 < 0.15) {
          electronTightColl_dr03_b150_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b150_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.125) {
          electronTightColl_dr03_b125_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.1) {
          electronTightColl_dr03_b100_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
	  electronTightColl_dr03_b100_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
	if(LeptonRelIsoDR03 < 0.09) {
          electronTightColl_dr03_b090_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
	  if(passNPFiso)   electronTightColl_dr03_b090_e050_detiso.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.08) {
          electronTightColl_dr03_b080_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }

	if(LeptonRelIsoDR03 < 0.07) {
          electronTightColl_dr03_b070_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.05) {
          electronTightColl_dr03_b050_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
      }
      else{
	if(LeptonRelIsoDR03 < 0.125) {
          electronTightColl_dr03_b150_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e125.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.100) {
          electronTightColl_dr03_b150_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e100.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.090) {
          electronTightColl_dr03_b150_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
	  electronTightColl_dr03_b080_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e090.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.080) {
          electronTightColl_dr03_b150_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
	  electronTightColl_dr03_b070_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e080.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
	if(LeptonRelIsoDR03 < 0.070) {
          electronTightColl_dr03_b150_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
	  electronTightColl_dr03_b050_e070.push_back(electronLooseColl_tight_noipcut.at(iel));
        }

        if(LeptonRelIsoDR03 < 0.060) {
          electronTightColl_dr03_b150_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b050_e060.push_back(electronLooseColl_tight_noipcut.at(iel));
        }

        if(LeptonRelIsoDR03 < 0.050) {
          electronTightColl_dr03_b150_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b125_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b100_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b090_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
	  if(passNPFiso)   electronTightColl_dr03_b090_e050_detiso.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b080_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
          electronTightColl_dr03_b070_e050.push_back(electronLooseColl_tight_noipcut.at(iel));
        }
      }
    }
  }
  
  /// Fill Medium/Tight ID vectors
  std::vector<snu::KElectron> electronNoCutColl;
  eventbase->GetElectronSel()->Selection(electronNoCutColl);
  
  for(unsigned int iel = 0; iel < electronNoCutColl.size(); iel++){

    if(electronNoCutColl[iel].Pt() < 15.) continue;
    if(fabs(electronNoCutColl[iel].Eta()) > 2.4) continue;
    
    double effective_area_eta_minimums    [7] = { 0.000, 1.000, 1.479, 2.000, 2.200, 2.300, 2.400 };
    double effective_area_eta_maximums    [7] = { 1.000, 1.479, 2.000, 2.200, 2.300, 2.400, 999.0 };
    double effective_areas_03             [7] = { 0.130, 0.140, 0.07, 0.09, 0.110, 0.110, 0.140 };
    double effective_area_03  = 0.0;

    for (int i = 0; i < 7; ++i ){
      double bin_minimum = effective_area_eta_minimums[i];
      double bin_maximum = effective_area_eta_maximums[i];
      if ( fabs(electronNoCutColl[iel].SCEta()) >= bin_minimum && fabs(electronNoCutColl[iel].SCEta()) < bin_maximum ) {
        effective_area_03 = effective_areas_03 [i];
      }
    }

    double egamma_pfiso_03 = electronNoCutColl[iel].PFChargedHadronIso03() + std::max ( electronNoCutColl[iel].PFPhotonIso03() + electronNoCutColl[iel].PFNeutralHadronIso03() - ( eventbase->GetEvent().JetRho() * effective_area_03 ), 0.0 );
    egamma_pfiso_03 /= electronNoCutColl[iel].Pt();
    
    double egamma_e  = electronNoCutColl.at(iel).CaloEnergy();
    double egamma_p  = electronNoCutColl.at(iel).CaloEnergy() / electronNoCutColl.at(iel).ESuperClusterOverP();
    double egamma_ep = fabs ( ( 1.0 / egamma_e ) - ( 1.0 / egamma_p ) );

    /// dEtaIn     cut
    if ( fabs(electronNoCutColl.at(iel).SCEta()) < 1.479 ){
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.004) {
        if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.06){
          if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.01){
            if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ()) < 0.1){
              if(electronNoCutColl.at(iel).HoE            ()  <= 0.12){
                if( egamma_ep          <= 0.05){
                  if(electronNoCutColl.at(iel).ConvFitProb  ()    <=  1e-6){
                    if(electronNoCutColl.at(iel).MissingHits()    <=  1){
                      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.02){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			    electronLooseColl_medium_noipcut.push_back(electronNoCutColl.at(iel));
			  }
                          if(egamma_pfiso_03    <=  0.1){
                            if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                              electronTightColl_medium.push_back(electronNoCutColl.at(iel));
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
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.007){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.03) {
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
	    if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
		if( egamma_ep          <=0.05){
		  if(electronNoCutColl.at(iel).ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl.at(iel).MissingHits()    <=  1){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.02){
			  if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
                            electronLooseColl_medium_noipcut.push_back(electronNoCutColl.at(iel));
                          }
			  if(egamma_pfiso_03    <=  0.1){
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			      electronTightColl_medium.push_back(electronNoCutColl.at(iel));
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
    
    /// TIGHT
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
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.02){
			  if(egamma_pfiso_03    <=  0.1){
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			      electronTightColl_tight.push_back(electronNoCutColl.at(iel));
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
      if(fabs(electronNoCutColl.at(iel).DeltaEta())   <= 0.005){
	if(fabs(electronNoCutColl.at(iel).DeltaPhi())   <= 0.02) {
	  if(electronNoCutColl.at(iel).SigmaIEtaIEta()    <= 0.03){
	    if(fabs(electronNoCutColl.at(iel).LeadVtxDistZ ())< 0.1){
	      if(electronNoCutColl.at(iel).HoE            ()  <= 0.10){
		if( egamma_ep          <=0.05){
		  if(electronNoCutColl[iel].ConvFitProb  ()    <=  1e-6){
		    if(electronNoCutColl[iel].MissingHits()    <=  0){
		      if(!electronNoCutColl.at(iel).HasMatchedConvPhot()){
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.02){
			  if(egamma_pfiso_03    <=  0.1){
			    if(electronNoCutColl.at(iel).GsfCtfScPixChargeConsistency()){
			      electronTightColl_tight.push_back(electronNoCutColl.at(iel));
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
      
  /// Event contains at least one loose electron
  std::vector<snu::KElectron> electronTightColl;
  eventbase->GetElectronSel()->HNTightElectronSelection(electronTightColl);
  if(!isData){
    if(electronTightColl.size() > 0){
      if(electronTightColl.at(0).Pt() < 15.) weight/= 0.496799;
      else if(electronTightColl.at(0).Pt() < 20.) weight/= 1.13124;
      else if(electronTightColl.at(0).Pt() < 25.) weight/= 1.0217;
      else if(electronTightColl.at(0).Pt() < 30.) weight/=  1.06533;
      else if(electronTightColl.at(0).Pt() < 35.) weight/=  1.05734;
      else if(electronTightColl.at(0).Pt() < 40.) weight/= 1.34635;
      else if(electronTightColl.at(0).Pt() < 45.) weight/=  1.26799;
      else if(electronTightColl.at(0).Pt() < 50.) weight/=  1.15155;
      else if(electronTightColl.at(0).Pt() < 55.) weight/=  1.23619;
      else if(electronTightColl.at(0).Pt() < 60.) weight/= 1.00562;
      else if(electronTightColl.at(0).Pt() < 65.) weight/= 0.927055;
      else if(electronTightColl.at(0).Pt() < 70.) weight/= 1.05704;
      else if(electronTightColl.at(0).Pt() < 75.) weight/= 1.07512;
      else if(electronTightColl.at(0).Pt() < 80.) weight/=  0.915664;
      else if(electronTightColl.at(0).Pt() < 85.) weight/=  1.46619;
      else if(electronTightColl.at(0).Pt() < 90.) weight/=  0.910909;
    }
  }
  std::vector<snu::KMuon> muonLooseColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonLooseColl);

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);

  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);

  std::vector<snu::KJet> jetColl_lepveto20;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetUseJetPileUp(true);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto20, muonTightColl, electronLooseColl);
  
  if(!k_isdata&&electronLooseColl.size() >0){
    Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
    Float_t htbins[6] = { 0., 30., 50., 100., 200., 400.};
    Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
    
    int nbjetmc(0);
    for(unsigned int ij =0 ; ij < jetColl_lepveto20.size() ; ij++){
      if(jetColl_lepveto20.at(ij).CombinedSecVertexBtag() > 0.679) nbjetmc++;
    }
    
    if(electronLooseColl.size()==1){
      if(eventbase->GetEvent().PFMET() < 30.){
	if(electronLooseColl.at(0).GetType() == 1 || electronLooseColl.at(0).GetType() == 2 || electronLooseColl.at(0).GetType() == 3 || electronLooseColl.at(0).GetType() == 4 || electronLooseColl.at(0).GetType() == 5 || electronLooseColl.at(0).GetType() == 6 ){
	  
	  bool use20=false;
	  for(unsigned int ijet = 0; ijet < jetColl_lepveto20.size(); ijet++){
	    float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(0).Phi()- jetColl_lepveto20.at(ijet).Phi()));
	    if(dphi > 2.5) use20=true;
	  }
	  bool use30=false;
          for(unsigned int ijet = 0; ijet < jetColl_lepveto20.size(); ijet++){
            if(jetColl_lepveto20.at(ijet).Pt() < 30.) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(0).Phi()- jetColl_lepveto20.at(ijet).Phi()));
            if(dphi > 2.5) use30=true;
          }

	  bool use40=false;
          for(unsigned int ijet = 0; ijet < jetColl_lepveto20.size(); ijet++){
            if(jetColl_lepveto20.at(ijet).Pt() < 40.) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(0).Phi()- jetColl_lepveto20.at(ijet).Phi()));
            if(dphi > 2.5) use40=true;
          }
	  bool use60=false;
          for(unsigned int ijet = 0; ijet < jetColl_lepveto20.size(); ijet++){
            if(jetColl_lepveto20.at(ijet).Pt() < 60.) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(0).Phi()- jetColl_lepveto20.at(ijet).Phi()));
            if(dphi > 2.5) use60=true;
          }
	  
	  if(use20){
	    FillHist("MCLooseEl_20_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
	    if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
	      FillHist("MCTightEl_20_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
	    }
	  }
	  if(use30){
            FillHist("MCLooseEl_30_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
              FillHist("MCTightEl_30_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            }
          }
	  if(use40){
            FillHist("MCLooseEl_40_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
              FillHist("MCTightEl_40_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            }
          }
	  if(use60){
            FillHist("MCLooseEl_60_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
              FillHist("MCTightEl_60_pt_eta", electronLooseColl.at(0).Pt(), fabs(electronLooseColl.at(0).Eta()), weight,  ptbins, 8, etabins, 4);
            }
          }
	  
	}
      }
    }
	  
    float el_pt = electronLooseColl.at(0).Pt();
    if(electronLooseColl.at(0).GetType() == 1 || electronLooseColl.at(0).GetType() == 2 || electronLooseColl.at(0).GetType() == 3 ){

      if(jetColl_lepveto20.size() > 0){
	if(electronLooseColl.at(0).Pt() > 15.){
	  bool awayjet=false;
	  bool closebjet=false;
	  bool closejet=false;
	  bool closenoejet=false;
	  bool closephjet=false;
	  float ptclosejet(0.);
	  float ptawayjet(0.);
	  /// plot FR if away jet is btagged
	  for(unsigned int ijet =0 ; ijet < jetColl.size() ; ijet++){
	    
	    float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(0).Phi()- jetColl.at(ijet).Phi()));
	    
	    if( dphi > 2.5){
	      if(!awayjet) ptawayjet=jetColl.at(ijet).Pt();
	      awayjet=true;
	    }
	    if( dphi < 0.4){
	      if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	    }
	    
	    if( electronLooseColl.at(0).DeltaR(jetColl.at(ijet)) < 0.4){
	      closejet=true;
	      ptclosejet=jetColl.at(ijet).Pt();
	      if(jetColl.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	      if(jetColl.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	      FillHist(("closejet/closejet_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	      FillHist(("closejet/closejet_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/closejet_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/closejet_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/closejet_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	      FillHist(("closejet/closejet_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
	      FillHist(("closejet/closejet_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200, 20);
	      FillHist(("closejet/closejet_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0.,200,  20);
	      FillHist(("closejet/closejet_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200,  20);
	      FillHist("closejet/closejet_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(0).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50); 
	      if(jetColl.at(ijet).CombinedSecVertexBtag() < 0.679) {
		
		FillHist(("closejet/closejet_notb_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		FillHist(("closejet/closejet_notb_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_notb_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_notb_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_notb_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_notb_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
		FillHist(("closejet/closejet_notb_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200, 20);
		FillHist(("closejet/closejet_notb_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0.,200,  20);
		FillHist(("closejet/closejet_notb_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200,  20);
		FillHist("closejet/closejet_notb_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(0).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
		
	      }
	      else{
		FillHist(("closejet/closejet_b_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		FillHist(("closejet/closejet_b_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_b_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_b_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_b_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_b_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
		FillHist(("closejet/closejet_b_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200, 20);
		FillHist(("closejet/closejet_b_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0.,200,  20);
		FillHist(("closejet/closejet_b_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200,  20);
		FillHist("closejet/closejet_b_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(0).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
		
	      }
	    }
	  }
	  FillHist("MCLooseEl_closebjet",   closebjet, weight, 0.,2., 2);
	  FillHist("MCLooseEl_closenoejet", closenoejet, weight, 0.,2., 2);
	  FillHist("MCLooseEl_closephjet",   closephjet, weight, 0.,2., 2);
	  FillHist("MCLooseEl_awayjet_pt", ptawayjet, weight, 0., 100., 20);
	  
	  if(!(closebjet || closenoejet || closenoejet ))   {
	    FillHist("MCLooseEl_closejet",   0, weight, 0.,2., 2);
	    FillHist("MCLooseEl_noclosejet_nbjet", nbjetmc, weight, 0.,4.,4);
	  }
	  else FillHist("MCLooseEl_closejet",   1, weight, 0.,2., 2);
	  
	  
	  FillHist("MCLooseEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	  FillHist("MCLooseEl_pt",el_pt , weight, ptbins, 8);
	  FillHist("MCLooseEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
	  FillHist("MCLooseEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
	  FillHist("MCLooseEl_nbjet", nbjetmc, weight, 0.,4.,4);
	  
	  if(IsTight(electronLooseColl.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
	    FillHist("MCTightEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	    FillHist("MCTightEl_pt", el_pt, weight, ptbins, 8);
	    FillHist("MCTightEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
	    FillHist("MCTightEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
	    FillHist("MCTightEl_nbjet", nbjetmc, weight, 0.,4.,4);
	  }
	}
      }
    }
    
    if(electronLooseColl.at(0).GetType() == 0 || electronLooseColl.at(0).GetType() == 7){
      
      /// plot FR if away jet is btagged
      for(unsigned int ijet =0 ; ijet < jetColl.size() ; ijet++){
	
	if( electronLooseColl.at(0).DeltaR(jetColl.at(ijet)) < 0.4){
	  FillHist(("closejet/closejet_nonfakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	  FillHist(("closejet/closejet_nonfakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	  FillHist(("closejet/closejet_nonfakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	  FillHist(("closejet/closejet_nonfakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	  FillHist(("closejet/closejet_nonfakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	  FillHist(("closejet/closejet_nonfakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
	  FillHist(("closejet/closejet_nonfakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200, 20);
	  FillHist(("closejet/closejet_nonfakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0.,200,  20);
	  FillHist(("closejet/closejet_nonfakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(0).Pt(),  weight, 0.,1.,20, 0., 200,  20);
	  FillHist("closejet/closejet_nonfake_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(0).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
	}
      }
    }
    
      
    if(electronLooseColl.size() >1){
      
      if(electronLooseColl.at(1).GetType() == 0 || electronLooseColl.at(1).GetType() == 7){
	
	/// plot FR if away jet is btagged
	for(unsigned int ijet =0 ; ijet < jetColl.size() ; ijet++){
	  
	  if( electronLooseColl.at(1).DeltaR(jetColl.at(ijet)) < 0.4){
	    
	    FillHist(("closejet/closejet_nonfakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
	    FillHist(("closejet/closejet_nonfakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
	    FillHist(("closejet/closejet_nonfakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
	    FillHist(("closejet/closejet_nonfakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
	    FillHist(("closejet/closejet_nonfakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
	    FillHist(("closejet/closejet_nonfakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
	    FillHist(("closejet/closejet_nonfakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200, 20);
	    FillHist(("closejet/closejet_nonfakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0.,200,  20);
	    FillHist(("closejet/closejet_nonfakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200,  20);
	    FillHist("closejet/closejet_nonfake_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(1).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
	  }
	}
      }
      
      if(electronLooseColl.at(1).GetType() == 1 || electronLooseColl.at(1).GetType() == 2 || electronLooseColl.at(1).GetType() == 3 ){
	
	if(jetColl_lepveto20.size() > 0){
	  if(electronLooseColl.at(1).Pt() > 15.){
	    bool awayjet=false;
	    bool closebjet=false;
	    bool closejet=false;
	    bool closenoejet=false;
	    bool closephjet=false;
	    float ptclosejet(0.);
	    float ptawayjet(0.);
	    /// plot FR if away jet is btagged
	    for(unsigned int ijet =0 ; ijet < jetColl.size() ; ijet++){
	      
	      float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(1).Phi()- jetColl.at(ijet).Phi()));
	      
	      if( dphi > 2.5){
		if(!awayjet) ptawayjet=jetColl.at(ijet).Pt();
		awayjet=true;
	      }
	      if( dphi < 0.4){
		if(jetColl.at(ijet).CombinedSecVertexBtag() > 0.679) closebjet=true;
	      }
	      
	      if( electronLooseColl.at(1).DeltaR(jetColl.at(ijet)) < 0.4){
		closejet=true;
		ptclosejet=jetColl.at(ijet).Pt();
		if(jetColl.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
		if(jetColl.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
		FillHist(("closejet/closejet_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		FillHist(("closejet/closejet_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		FillHist(("closejet/closejet_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
		FillHist(("closejet/closejet_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200, 20);
		FillHist(("closejet/closejet_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0.,200,  20);
		FillHist(("closejet/closejet_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200,  20);
		FillHist("closejet/closejet_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(1).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
		
		if(jetColl.at(ijet).CombinedSecVertexBtag() < 0.679) {
		  
		  FillHist(("closejet/closejet_notb_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_notb_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_notb_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_notb_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_notb_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_notb_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
		  FillHist(("closejet/closejet_notb_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200, 20);
		  FillHist(("closejet/closejet_notb_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0.,200,  20);
		  FillHist(("closejet/closejet_notb_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200,  20);
		  FillHist("closejet/closejet_notb_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(1).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
		  
		}
		else{
		  FillHist(("closejet/closejet_b_fakemcel_NeutralEMEnergyFraction"),jetColl.at(ijet).NeutralEMEnergyFraction()  , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_b_fakemcel_NeutralHadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_b_fakemcel_ChargedEMEnergyFraction"),jetColl.at(ijet).ChargedEMEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_b_fakemcel_ChargedHadEnergyFraction"),jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_b_fakemcel_ElectronEnergyFraction"),jetColl.at(ijet).ElectronEnergyFraction() , weight, 0.,1.,20);
		  FillHist(("closejet/closejet_b_fakemcel_HadEnergyFraction"),jetColl.at(ijet).NeutralHadEnergyFraction()+ jetColl.at(ijet).ChargedHadEnergyFraction() , weight, 0., 1.,200);
		  FillHist(("closejet/closejet_b_fakemcel_ChargedEMEnergyFraction_elpt"),jetColl.at(ijet).ChargedEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200, 20);
		  FillHist(("closejet/closejet_b_fakemcel_ChargedHadEnergyFraction_elpt"),jetColl.at(ijet).ChargedHadEnergyFraction()  ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0.,200,  20);
		  FillHist(("closejet/closejet_b_fakemcel_NeutralEMEnergyFraction_elpt"),jetColl.at(ijet).NeutralEMEnergyFraction() ,electronLooseColl.at(1).Pt(),  weight, 0.,1.,20, 0., 200,  20);
		  FillHist("closejet/closejet_b_ptdiff_el", (jetColl.at(ijet).Pt() -  electronLooseColl.at(1).Pt()) / jetColl.at(ijet).Pt() , weight, -1., 1., 50);
		}
	      }
	    }
	    FillHist("MCLooseEl_closebjet",   closebjet, weight, 0.,2., 2);
	    FillHist("MCLooseEl_closenoejet", closenoejet, weight, 0.,2., 2);
	    FillHist("MCLooseEl_closephjet",   closephjet, weight, 0.,2., 2);
	    FillHist("MCLooseEl_awayjet_pt", ptawayjet, weight, 0., 100., 20);
	    
	    if(!(closebjet || closenoejet || closenoejet )) {
	      FillHist("MCLooseEl_closejet",   0, weight, 0.,2., 2);
	      FillHist("MCLooseEl_noclosejet_nbjet", nbjetmc, weight, 0.,4.,4);
	    }
	    else FillHist("MCLooseEl_closejet",   1, weight, 0.,2., 2);
	    
	    
	    FillHist("MCLooseEl_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	    FillHist("MCLooseEl_pt",el_pt , weight, ptbins, 8);
	    FillHist("MCLooseEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
	    FillHist("MCLooseEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
	    FillHist("MCLooseEl_nbjet", nbjetmc, weight, 0.,4.,4);
	    if(IsTight(electronLooseColl.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
	      FillHist("MCTightEl_eta", electronLooseColl.at(1).Eta(), weight, -2.5, 2.5,50);
	      FillHist("MCTightEl_pt", el_pt, weight, ptbins, 8);
	      FillHist("MCTightEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
	      FillHist("MCTightEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
	      FillHist("MCTightEl_nbjet", nbjetmc, weight, 0.,4.,4);
	    }
	  }
	}
      }
    }
  }
  
  if(!k_isdata&&electronLooseColl_tight_noipcut.size() >0){
    Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
    Float_t htbins[6] = { 0., 30., 50., 100., 200., 400.};
    
    int nbjetmc(0);
    for(unsigned int ij =0 ; ij < jetColl_lepveto20.size() ; ij++){
      if(jetColl_lepveto20.at(ij).CombinedSecVertexBtag() > 0.679) nbjetmc++;
    }
    
    float el_pt = electronLooseColl_tight_noipcut.at(0).Pt();
    if(electronLooseColl_tight_noipcut.at(0).GetType() == 1 || electronLooseColl_tight_noipcut.at(0).GetType() == 2 || electronLooseColl_tight_noipcut.at(0).GetType() == 3 ){
      FillHist("MCNoIPCUTLooseEl_eta", electronLooseColl_tight_noipcut.at(0).Eta(), weight, -2.5, 2.5,50);
      FillHist("MCNoIPCUTLooseEl_pt",el_pt , weight, ptbins, 8);
      FillHist("MCNoIPCUTLooseEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
      FillHist("MCNoIPCUTLooseEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
      FillHist("MCNoIPCUTLooseEl_nbjet", nbjetmc, weight, 0.,4.,4);
      if(IsTight(electronLooseColl_tight_noipcut.at(0), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
        FillHist("MCNoIPCUTTightEl_eta", electronLooseColl_tight_noipcut.at(0).Eta(), weight, -2.5, 2.5,50);
        FillHist("MCNoIPCUTTightEl_pt", el_pt, weight, ptbins, 8);
        FillHist("MCNoIPCUTTightEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
        FillHist("MCNoIPCUTTightEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
        FillHist("MCNoIPCUTTightEl_nbjet", nbjetmc, weight, 0.,4.,4);
      }
    }

    if(electronLooseColl_tight_noipcut.size() >1){
      if(electronLooseColl_tight_noipcut.at(1).GetType() == 1 || electronLooseColl_tight_noipcut.at(1).GetType() == 2 || electronLooseColl_tight_noipcut.at(1).GetType() == 3 ){
        FillHist("MCNoIPCUTLooseEl_eta", electronLooseColl_tight_noipcut.at(1).Eta(), weight, -2.5, 2.5,50);
        FillHist("MCNoIPCUTLooseEl_pt",el_pt , weight, ptbins, 8);
        FillHist("MCNoIPCUTLooseEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
        FillHist("MCNoIPCUTLooseEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
        FillHist("MCNoIPCUTLooseEl_nbjet", nbjetmc, weight, 0.,4.,4);
        if(IsTight(electronLooseColl_tight_noipcut.at(1), eventbase->GetEvent().JetRho(), 0.01,0.09, 0.05,true, false, true)){
          FillHist("MCNoIPCUTTightEl_eta", electronLooseColl_tight_noipcut.at(1).Eta(), weight, -2.5, 2.5,50);
          FillHist("MCNoIPCUTTightEl_pt", el_pt, weight, ptbins, 8);
          FillHist("MCNoIPCUTTightEl_njets", jetColl_lepveto20.size(), weight, 0.,5.,5);
          FillHist("MCNoIPCUTTightEl_ht", SumPt(jetColl_lepveto20), weight, htbins, 5);
          FillHist("MCNoIPCUTTightEl_nbjet", nbjetmc, weight, 0.,4.,4);
        }
      }
    }
  }

  
  // Dilepton CR
  if(PassTrigger(triggerslist_diel, prescale)){
    if(electronLooseColl.size() ==2){
      if(jetColl_lepveto20.size() > 0){
	if(jetColl_lepveto20.at(0).Pt() > 30.){
	  FillCLHist(sighist, "DoubleEl", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
	}
      }
    }
    
  }
  

  if(muonLooseColl.size() > 0) return;

  FillCLHist(sighist, "SingleEl_nocut", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  
  std::vector<TString> triggerslist17jet;
  triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  std::vector<TString> triggerslist8jet;
  triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

  bool pass_eljettrig= false;
  
  /// Calcalate prescale weights
  float prescale_trigger = 0.;
  if(electronLooseColl.size() ==1){
    if(electronLooseColl.at(0).Pt() >= 20.){
      
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
  }

  
  if(k_isdata) prescale_trigger=1.;
  
  /// for loose_medium sample
  bool pass_eljettrig_medium= false;
  
  /// Calcalate prescale weights
  float prescale_trigger_medium = 0.;
  if(electronLooseColl_medium_noipcut.size() ==1){
    if(electronLooseColl_medium_noipcut.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger_medium = (16.953032) / 19789 ; //// 20 + GeV bins
        pass_eljettrig_medium = true;
      }
      else prescale_trigger_medium = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger_medium = (3.546650) / 19789 ;
        pass_eljettrig_medium = true;
      }
      else prescale_trigger_medium = 0.;
    }
  }
  
  if(k_isdata) prescale_trigger_medium=1.;

  /// Fill _medium plots here
  bool usemedium=true;
  if(usemedium&&pass_eljettrig_medium){
    float weight_med = weight* prescale_trigger_medium;
    /// REMOVE Z like events
    bool Zveto=false;
    if(electronVetoColl.size() == 2) {
      if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
	snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
	if(Z.M() > 76. && Z.M() < 106.) Zveto=true;
      }
    }
    if(!Zveto){
      /// Z and W veto
      Double_t MT_med=0;
      Double_t METdphi_med=0;
      for(unsigned int w = 0; w < electronLooseColl_medium_noipcut.size();  w++){
	METdphi_med = TVector2::Phi_mpi_pi(electronLooseColl_medium_noipcut.at(w).Phi()- eventbase->GetEvent().PFMETphi());
	MT_med = sqrt(2.* electronLooseColl_medium_noipcut.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi_med)));
      }
      

      bool truth_match_medium=false;
      
      /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
      if(!k_isdata) {
	if(electronLooseColl_medium_noipcut.size() > 0){
	  /// ONLY INCLUDE ELECTRONS FROM W/Z
	  if((electronLooseColl_medium_noipcut.at(0).GetType() == 0) || (electronLooseColl_medium_noipcut.at(0).GetType() ==7))  truth_match_medium=true;
	}
	else truth_match_medium = true;
      }
      else truth_match_medium=true;

      if(( (eventbase->GetEvent().PFMET() < 20) && (MT_med < 25.)) ) {
	
	bool useevent40_medium = false;
	for (unsigned int ielT=0; ielT < electronLooseColl_medium_noipcut.size(); ielT++){
	  for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	    if(jetColl_lepveto20.at(ij).Pt() < 40.) continue;
	    float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl_medium_noipcut.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
	    if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	    
	    if(dphi > 2.5) useevent40_medium = true;
	  }
	}
	
	Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
	//Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
	//Float_t htbins[5] = { 0., 30., 50., 100., 200.};
	Float_t ebetabins[3] = { 0., 1.479, 2.5};

	if(useevent40_medium&&truth_match_medium){
	  float elm_pt = electronLooseColl_medium_noipcut.at(0).Pt();
	  if(electronLooseColl_medium_noipcut.at(0).Pt() > 100.) elm_pt = 99.;
	  float elm_eta = fabs(electronLooseColl_medium_noipcut.at(0).Eta());
	  
	  if(jetColl_lepveto20.size() >= 1){
	    if( electronTightColl_medium.size()==1 )   FillHist("Tight_medium_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);
	    if( electronLooseColl_medium_noipcut.size()==1 )   FillHist("LooseOpt_medium_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);
	    
	    if( electronTightColl_tight.size()==1 )   FillHist("Tight_tight_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);
            if( electronLooseColl_dxy20.size()==1 )   FillHist("LooseOpt_tight_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);

	  }
	}
      }
    }
  }


  //// Different isolations
  bool pass_eljettrig_iso07= false;

  float prescale_trigger_iso07 = 0.;
  if(electronLooseColl_iso07.size() ==1){
    if(electronLooseColl_iso07.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger_iso07 = (16.953032) / 19789 ; //// 20 + GeV bins
        pass_eljettrig_iso07 = true;
      }
      else prescale_trigger_iso07 = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger_iso07 = (3.546650) / 19789 ;
        pass_eljettrig_iso07 = true;
      }
      else prescale_trigger_iso07 = 0.;
    }
  }

  if(k_isdata) prescale_trigger_iso07=1.;

  /// Fill _iso07 plots here
  bool useiso07=true;
  if(useiso07&&pass_eljettrig_iso07){
    float weight_iso07 = weight* prescale_trigger_iso07;
    /// REMOVE Z like events
    bool Zveto=false;
    if(electronVetoColl.size() == 2) {
      if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
	snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
        if(Z.M() > 76. && Z.M() < 106.) Zveto=true;
      }
    }
    if(!Zveto){
      /// Z and W veto
      Double_t MT_iso07=0;
      Double_t METdphi_iso07=0;
      for(unsigned int w = 0; w < electronLooseColl_iso07.size();  w++){
        METdphi_iso07 = TVector2::Phi_mpi_pi(electronLooseColl_iso07.at(w).Phi()- eventbase->GetEvent().PFMETphi());
        MT_iso07 = sqrt(2.* electronLooseColl_iso07.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi_iso07)));
      }


      bool truth_match_iso07=false;

      /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
      if(!k_isdata) {
        if(electronLooseColl_iso07.size() > 0){
          /// ONLY INCLUDE ELECTRONS FROM W/Z
          if((electronLooseColl_iso07.at(0).GetType() == 0) || (electronLooseColl_iso07.at(0).GetType() ==7))  truth_match_iso07=true;
        }
        else truth_match_iso07 = true;
      }
      else truth_match_iso07=true;

      if(( (eventbase->GetEvent().PFMET() < 20) && (MT_iso07 < 25.)) ) {

        bool useevent40_iso07 = false;
        for (unsigned int ielT=0; ielT < electronLooseColl_iso07.size(); ielT++){
          for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
            if(jetColl_lepveto20.at(ij).Pt() < 40.) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl_iso07.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
            if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;

            if(dphi > 2.5) useevent40_iso07 = true;
          }
        }

        Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
        //Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
        //Float_t htbins[5] = { 0., 30., 50., 100., 200.};
        Float_t ebetabins[3] = { 0., 1.479, 2.5};

        if(useevent40_iso07&&truth_match_iso07){
          float elm_pt = electronLooseColl_iso07.at(0).Pt();
          if(electronLooseColl_iso07.at(0).Pt() > 100.) elm_pt = 99.;
          float elm_eta = fabs(electronLooseColl_iso07.at(0).Eta());

          if(jetColl_lepveto20.size() >= 1){
            if( electronTightColl.size()==1 )   FillHist("Tight_iso07_pt_eta",elm_pt, elm_eta, weight_iso07,  ptbins, 8, ebetabins, 2);
            if( electronLooseColl_iso07.size()==1 )   FillHist("LooseOpt_iso07_pt_eta",elm_pt, elm_eta, weight_iso07,  ptbins, 8, ebetabins, 2);
	    if( electronLooseColl_iso05.size()==1 )   FillHist("LooseOpt_iso05_pt_eta",elm_pt, elm_eta, weight_iso07,  ptbins, 8, ebetabins, 2);

          }
        }
      }
    }
  }


  
  weight = weight * prescale_trigger;
  /// prescale_trigger = 1 for data, 0 if failed trigger

  if(jetColl_lepveto20.size() > 0 ) {
    if(electronTightColl_dr03_b090_e050.size() ==1 ){
      
      float tmpMETdphi = TVector2::Phi_mpi_pi(electronTightColl_dr03_b090_e050.at(0).Phi()- eventbase->GetEvent().PFMETphi());
      float tmpMT = sqrt(2.* electronTightColl_dr03_b090_e050.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( tmpMETdphi)));
      if(tmpMT < 25.){
	if(eventbase->GetEvent().PFMET() < 20.){
	  FillCLHist(sighist, "SingleEl_nodetiso", eventbase->GetEvent(), muonLooseColl,electronTightColl_dr03_b090_e050, jetColl_lepveto20, weight);
	}
      }
    }
  }

  
  if(electronLooseColl.size() ==0) return;
 
  if(!pass_eljettrig) return;
  
  FillCLHist(sighist, "SingleEl_trigger", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  if(jetColl_lepveto20.size() >= 1 ) FillCLHist(sighist, "SingleEl_jet20", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  
  m_logger << DEBUG << "Running fake efficiency code" << LQLogger::endmsg;
  
  
  /// REMOVE Z like events
  if(electronVetoColl.size() == 2) {
    if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
      snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
      if(Z.M() > 76. && Z.M() < 106.) return;
    }
  }
  if(electronVetoColl.size() > 1) return;
  

  /// Z and W veto
  Double_t MT=0;
  Double_t METdphi=0;
  m_logger << DEBUG << "Filling single lepton + 1 jet plots " << LQLogger::endmsg;
  
  if (jetColl_lepveto20.size() >= 1 ) {
    if(jetColl_lepveto20.at(0).Pt() > 30.){
      FillCLHist(sighist, "SingleLooseElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      if (electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "SingleTightElJet", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    }
  }
  
  for(unsigned int w = 0; w < electronLooseColl.size();  w++){
    METdphi = TVector2::Phi_mpi_pi(electronLooseColl.at(w).Phi()- eventbase->GetEvent().PFMETphi());
    MT = sqrt(2.* electronLooseColl.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi)));
  }
  
  bool truth_match=false;
  
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    if(electronLooseColl.size() > 0){
      /// ONLY INCLUDE ELECTRONS FROM W/Z
      if((electronLooseColl.at(0).GetType() == 0) || (electronLooseColl.at(0).GetType() ==7))  truth_match=true;
    }
    else truth_match = true;
  }
  else truth_match=true;
  
  if(truth_match){
    if (jetColl_lepveto20.size() >= 1 ){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
	FillCLHist(sighist, "SingleLooseElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      }
    }
    
    if (electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
	FillCLHist(sighist, "SingleTightElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      }
    }
  }
  
  m_logger << DEBUG << "making cuts to remove prompt leptons" << LQLogger::endmsg;
  m_logger << DEBUG << "Selecting region to calculate MC SFs " << LQLogger::endmsg;
  
  if(eventbase->GetEvent().PFMET() > 40 && (60. < MT)  &&(MT < 100.) &&truth_match){
    
    if(electronTightColl.size() == 1&& jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
	FillCLHist(sighist, "SingleTightElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      }
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
	FillCLHist(sighist, "SingleTightElJet40_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      }
    }
    if(jetColl_lepveto20.size() >= 1){
      if(jetColl_lepveto20.at(0).Pt() > 30.) {
        FillCLHist(sighist, "SingleLooseElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
      }
      if(jetColl_lepveto20.at(0).Pt() > 40.) {
        FillCLHist(sighist, "SingleLooseElJet40_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
      }
    }
  }
  
  if( !( (eventbase->GetEvent().PFMET() < 20) && (MT < 25.)) ) return;
  
  m_logger << DEBUG << "Making plots for fake rates with different jet cuts" << LQLogger::endmsg;
  
  bool useevent20= false;
  bool useevent30= false;
  bool useevent40= false;
  bool useevent60= false;
  bool useevent40_loosedxy01 = false;
  /// Fake Rates
  
  if ( jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	
	float dphi = fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
	if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65) continue;
        if(dphi > 2.5) useevent20 = true;
      }
    }
  }
  
  if ( jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	if(jetColl_lepveto20.at(ij).Pt() < 30.) continue;
	float dphi = fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
        if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65) continue;
	if(dphi > 2.5) useevent30 = true;
      }
    }
  }


  if (jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	if(jetColl_lepveto20.at(ij).Pt() < 40.) continue;
	float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
        if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	
	if(dphi > 2.5) useevent40 = true;
      }
    }
  }

  if (jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	if(jetColl_lepveto20.at(ij).Pt() < 40.) continue;
        float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
        if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
        if(dphi > 2.5) useevent40_loosedxy01 = true;
      }
    }
  }

  
  
  if (jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	if(jetColl_lepveto20.at(ij).Pt() < 60.) continue;
	
	float dphi =fabs(TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi()));
        if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	if(dphi > 2.5) useevent60 = true;
      }
    }
  }
  
  Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
  //Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
  //Float_t htbins[5] = { 0., 30., 50., 100., 200.};
  Float_t ebetabins[3] = { 0., 1.479, 2.5};


  if(electronLooseColl.size() ==0) return;

  float el_pt = electronLooseColl.at(0).Pt();
  if(electronLooseColl.at(0).Pt() > 100.) el_pt = 99.;
  float el_eta = fabs(electronLooseColl.at(0).Eta());
  
 
  
  if(useevent30){
    if ( electronTightColl.size() == 1 && jetColl_lepveto20.size() >= 1)FillCLHist(sighist, "TightEl30_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto20, weight);
    if (jetColl_lepveto20.size() >= 1) FillCLHist(sighist, "LooseEl30_notm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
    
  }
    
  if(useevent40_loosedxy01&&truth_match){
    if(jetColl_lepveto20.size() >= 1){
      if( electronLooseColl.size()==1 )   FillHist("Loosedxy01_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
    }
  }
  
  if(useevent40&&truth_match){
    if(jetColl_lepveto20.size() >= 1){
      if( electronLooseColl.size()==1 )   FillHist("LooseOpt_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronLooseColl_dxy20.size() ==1) FillHist("LooseOpt_dxy20_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_150.size()==1 )  FillHist("Tight_iso_dr3_b150_e150_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_125.size()==1 )  FillHist("Tight_iso_dr3_b125_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_100.size()==1 )  FillHist("Tight_iso_dr3_b100_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_090.size()==1 )  FillHist("Tight_iso_dr3_b090_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_080.size()==1 )  FillHist("Tight_iso_dr3_b080_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_070.size()==1 )  FillHist("Tight_iso_dr3_b070_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_060.size()==1 )  FillHist("Tight_iso_dr3_b060_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_050.size()==1 )  FillHist("Tight_iso_dr3_b050_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);      

      if(electronTightColl_dr03_b150_e125.size()==1 ) FillHist("Tight_iso_dr3_b150_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e100.size()==1 ) FillHist("Tight_iso_dr3_b150_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e090.size()==1 ) FillHist("Tight_iso_dr3_b150_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e080.size()==1 ) FillHist("Tight_iso_dr3_b150_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e070.size()==1 ) FillHist("Tight_iso_dr3_b150_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e060.size()==1 ) FillHist("Tight_iso_dr3_b150_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b150_e050.size()==1 ) FillHist("Tight_iso_dr3_b150_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      
      if(electronTightColl_dr03_b125_e100.size()==1 ) FillHist("Tight_iso_dr3_b125_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b125_e090.size()==1 ) FillHist("Tight_iso_dr3_b125_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b125_e080.size()==1 ) FillHist("Tight_iso_dr3_b125_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b125_e070.size()==1 ) FillHist("Tight_iso_dr3_b125_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b125_e060.size()==1 ) FillHist("Tight_iso_dr3_b125_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b125_e050.size()==1 ) FillHist("Tight_iso_dr3_b125_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_b100_e125.size()==1 ) FillHist("Tight_iso_dr3_b100_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b100_e090.size()==1 ) FillHist("Tight_iso_dr3_b100_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b100_e080.size()==1 ) FillHist("Tight_iso_dr3_b100_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b100_e070.size()==1 ) FillHist("Tight_iso_dr3_b100_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b100_e060.size()==1 ) FillHist("Tight_iso_dr3_b100_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b100_e050.size()==1 ) FillHist("Tight_iso_dr3_b100_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_b090_e100.size()==1 ) FillHist("Tight_iso_dr3_b090_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e125.size()==1 ) FillHist("Tight_iso_dr3_b090_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e080.size()==1 ) FillHist("Tight_iso_dr3_b090_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e070.size()==1 ) FillHist("Tight_iso_dr3_b090_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e060.size()==1 ) FillHist("Tight_iso_dr3_b090_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e050.size()==1 ) FillHist("Tight_iso_dr3_b090_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_b080_e100.size()==1 ) FillHist("Tight_iso_dr3_b080_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b080_e090.size()==1 ) FillHist("Tight_iso_dr3_b080_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b080_e125.size()==1 ) FillHist("Tight_iso_dr3_b080_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b080_e070.size()==1 ) FillHist("Tight_iso_dr3_b080_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b080_e060.size()==1 ) FillHist("Tight_iso_dr3_b080_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b080_e050.size()==1 ) FillHist("Tight_iso_dr3_b080_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_b070_e100.size()==1 ) FillHist("Tight_iso_dr3_b070_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b070_e090.size()==1 ) FillHist("Tight_iso_dr3_b070_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b070_e080.size()==1 ) FillHist("Tight_iso_dr3_b070_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b070_e125.size()==1 ) FillHist("Tight_iso_dr3_b070_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b070_e060.size()==1 ) FillHist("Tight_iso_dr3_b070_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b070_e050.size()==1 ) FillHist("Tight_iso_dr3_b070_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_b050_e100.size()==1 ) FillHist("Tight_iso_dr3_b050_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b050_e090.size()==1 ) FillHist("Tight_iso_dr3_b050_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b050_e080.size()==1 ) FillHist("Tight_iso_dr3_b050_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b050_e070.size()==1 ) FillHist("Tight_iso_dr3_b050_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b050_e060.size()==1 ) FillHist("Tight_iso_dr3_b050_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b050_e125.size()==1 ) FillHist("Tight_iso_dr3_b050_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_dr03_100_detiso.size() ==1) FillHist("Tight_iso_dr3_100_detiso_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_090_detiso.size() ==1) FillHist("Tight_iso_dr3_090_detiso_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_b090_e050_detiso.size() ==1) FillHist("Tight_iso_dr3_b090_e050_detiso_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

    }
  }
  
    
  /// Gets Fake rates for events with away jet > 20/40/60 GeV 

  if(truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,   "NoJetReq");
  if(truth_match&&(jetColl_lepveto20.size() > 0))   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,   "NoAwayJetReq");
  
  cout << "size of collections = electronTightColl_dr03_b090_e050  " << electronTightColl_dr03_b090_e050.size() << endl;
  cout << "size of collections = electronLooseColl = " << electronLooseColl.size() << endl;
  cout << "sizeof collections = electronTightColl = " << electronTightColl.size() << endl;
  
  
  if(useevent20&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,  "20");
  if(useevent30&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,  "30");
  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,  "40");
  if(useevent60&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,  "60");

  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl_dr03_090_detiso, jetColl_lepveto20,  "40_090_090_detiso");
  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl_dr03_100_detiso, jetColl_lepveto20,  "40_100_100_detiso");

  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl_dr03_090, jetColl_lepveto20,  "40_090_090");
  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl_dr03_100, jetColl_lepveto20,  "40_100_100");
  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl_dr03_b090_e050, jetColl_lepveto20,  "40_090_050");


  
  return;
}// End of execute event loop


void FakeRateCalculator_El::GetHSTRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag){

  Float_t htbins[14] = { 20.,22.5, 25.,27.5, 30.,35.,40.,45.,50.,60.,80.,100.,200., 1000.};

  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
      if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  if( tight_el.size() == 1 && jets.size() >= 1){
    FillHist(("MeasuredEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("MeasuredEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("MeasuredEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("MeasuredEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);
  }
  
  if( loose_el.size() == 1 && jets.size() >= 1){
    FillHist(("HSTLooseEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("HSTLooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("HSTLooseEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("HSTLooseEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);    
    
    float hstweight= m_fakeobj->getFakeRate_electronEta(0, loose_el.at(0).Pt(),loose_el.at(0).Eta(), tag);
    FillHist(("PredictedEl" + tag + "_njets").Data(), jets.size(), hstweight, 0.,5.,5);
    FillHist(("PredictedEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), hstweight, 0., 30., 30);
    FillHist(("PredictedEl" + tag + "_ht").Data(), SumPt(jets), hstweight, htbins, 13);
    FillHist(("PredictedEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);

    
  }  
}


void FakeRateCalculator_El::GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets,  TString tag){

  Float_t ptbins_ht[9] = { 10.,15.,20.,22.5,25.,27.5,35.,40., 60};
  Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
  
  Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
  Float_t htbins_pt[9] = { 20.,25.,30.,35.,40.,50.,60.,80.,200.};
  Float_t htbins[14] = { 20.,22.5, 25.,27.5, 30.,35.,40.,45.,50.,60.,80.,100.,200., 1000.};

  int nbjet(0);
  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) nbjet++;
    if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  cout << tight_el.size()  << " " << jets.size() << " " << tag << endl;
  if( tight_el.size() == 1 && jets.size() >= 1){
    float el_pt = tight_el.at(0).Pt();
    float el_eta = tight_el.at(0).Eta();
    
    // 1D FakeRates
    FillHist(("TightEl" + tag + "_eta").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    FillHist(("TightEl" + tag + "_pt").Data(),el_pt, weight,  ptbins, 8);
    FillHist(("TightEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("TightEl" + tag + "_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
    FillHist(("TightEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("TightEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("TightEl" + tag + "_nbjet").Data(), nbjet, weight, 0., 4.,4); 
    
    FillHist(("TightEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
    FillHist(("TightEl" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    if(nbjet==0)    FillHist(("TightEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    else FillHist(("TightEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);

    if(jets.size() == 1)     FillHist(("TightEl" + tag + "_1jet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    if(jets.size() == 2)     FillHist(("TightEl" + tag + "_2jet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    if(jets.size() > 2)     FillHist(("TightEl" + tag + "_3jet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    
    if(jets.size() > 2) {
      FillHist(("TightEl" + tag + "_eljetdr").Data(), tmp_deltaR, weight, 0., 5., 50);
      if(SumPt(jets) < 50.)     FillHist(("TightEl" + tag + "_pt_dijet_ht50").Data(),el_pt, weight,  ptbins, 8);
      else if(SumPt(jets) < 60.)     FillHist(("TightEl" + tag + "_pt_dijet_ht60").Data(),el_pt, weight,  ptbins, 8);
      else if(SumPt(jets) < 80.)     FillHist(("TightEl" + tag + "_pt_dijet_ht80").Data(),el_pt, weight,  ptbins, 8);
      else     FillHist(("TightEl" + tag + "_pt_dijet_ht200").Data(),el_pt, weight,  ptbins, 8);
   
    }

      
    if(nbjet==1){      
      if(SumPt(jets) < 40.)  FillHist(("TightEl" + tag + "_pt_ht1").Data(), el_pt, weight, ptbins, 8 );
      else FillHist(("TightEl" + tag + "_pt_ht2").Data(), el_pt, weight, ptbins, 8 );      
      FillHist(("TightEl" + tag + "_pt_1bjet").Data(), el_pt, weight, ptbins, 8 );
    }
    if(nbjet==2){
      FillHist(("TightEl" + tag + "_pt_2bjet").Data(), el_pt, weight, ptbins, 8 );
    }
    
    
    if(tight_el.at(0).Pt() < 15.)  FillHist(("TightEl" + tag + "_eta_pt1").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(tight_el.at(0).Pt() < 20.)  FillHist(("TightEl" + tag + "_eta_pt2").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(tight_el.at(0).Pt() < 30.)  FillHist(("TightEl" + tag + "_eta_pt3").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(tight_el.at(0).Pt() < 40.)  FillHist(("TightEl" + tag + "_eta_pt4").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(tight_el.at(0).Pt() < 50.)  FillHist(("TightEl" + tag + "_eta_pt5").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(tight_el.at(0).Pt() < 60.)  FillHist(("TightEl" + tag + "_eta_pt6").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else   FillHist(("TightEl" + tag + "_eta_pt7").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);

    if(SumPt(jets) < 30.)  FillHist(("TightEl" + tag + "_eta_ht1").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 50.)  FillHist(("TightEl" + tag + "_eta_ht2").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 60.)  FillHist(("TightEl" + tag + "_eta_ht3").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 80.)  FillHist(("TightEl" + tag + "_eta_ht4").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else  FillHist(("TightEl" + tag + "_eta_ht5").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    
    if(jets.size()==1) FillHist(("TightEl" + tag + "_pt_eta_nj1").Data(), el_pt, fabs(tight_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    if(jets.size()==2) FillHist(("TightEl" + tag + "_pt_eta_nj2").Data(), el_pt, fabs(tight_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    if(jets.size()>2) FillHist(("TightEl" + tag + "_pt_eta_nj3").Data(), el_pt, fabs(tight_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    

    if(fabs( tight_el.at(0).Eta() < 1.5)) {
      FillHist(("TightEl" + tag + "_ptbarrel_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
      FillHist(("TightEl" + tag + "_ptbarrel").Data(),el_pt, weight,  ptbins, 8);
    }
    else{
      FillHist(("TightEl" + tag + "_ptendcap_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
      FillHist(("TightEl" + tag + "_ptendcap").Data(),el_pt, weight,  ptbins, 8);
    }
    
    //FillCLHist(sighist, ("TightEl" + tag + "").Data(), eventbase->GetEvent(), muons,tight_el,jets, weight);

    
    if(jets.size() > 1)     FillHist(("TightEl" + tag + "_ht_dijet").Data(), SumPt(jets) , weight, htbins, 13);
    if(jets.size() > 1)  {
      FillHist(("TightEl" + tag + "_nbjet_dijet").Data(), nbjet, weight, 0., 4.,4);
    }
  }
  

  if(jets.size() >= 1){
    float el_pt = loose_el.at(0).Pt();
    FillHist(("LooseEl" + tag + "_eta").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    FillHist(("LooseEl" + tag + "_pt").Data(), el_pt, weight,  ptbins, 8);
    FillHist(("LooseEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("LooseEl" + tag + "_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);
    FillHist(("LooseEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("LooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("LooseEl" + tag + "_nbjet").Data(), nbjet, weight, 0., 4.,4);
    
    FillHist(("LooseEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
    FillHist(("LooseEl" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    if(nbjet==0)    FillHist(("LooseEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    else FillHist(("LooseEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    
    if(jets.size() == 1)     FillHist(("LooseEl" + tag + "_1jet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    if(jets.size() == 2)     FillHist(("LooseEl" + tag + "_2jet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);
    if(jets.size() > 2)     FillHist(("LooseEl" + tag + "_3jet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  weight, ptbins, 8 , etabins, 4);

    if(jets.size() > 2) {
      FillHist(("LooseEl" + tag + "_eljetdr").Data(), tmp_deltaR, weight, 0., 5., 50);
      if(SumPt(jets) < 50.)     FillHist(("LooseEl" + tag + "_pt_dijet_ht50").Data(),el_pt, weight,  ptbins, 8);
      else if(SumPt(jets) < 60.)     FillHist(("LooseEl" + tag + "_pt_dijet_ht60").Data(),el_pt, weight,  ptbins, 8);
      else if(SumPt(jets) < 80.)     FillHist(("LooseEl" + tag + "_pt_dijet_ht80").Data(),el_pt, weight,  ptbins, 8);
      else     FillHist(("LooseEl" + tag + "_pt_dijet_ht200").Data(),el_pt, weight,  ptbins, 8);

    }

    if(nbjet==1){
      if(SumPt(jets) < 40.)  FillHist(("LooseEl" + tag + "_pt_ht1").Data(), el_pt, weight, ptbins, 8 );
      else FillHist(("LooseEl" + tag + "_pt_ht2").Data(), el_pt, weight, ptbins, 8 );
      FillHist(("LooseEl" + tag + "_pt_1bjet").Data(), el_pt, weight, ptbins, 8 );
    }
    if(nbjet==2){
      FillHist(("LooseEl" + tag + "_pt_2bjet").Data(), el_pt, weight, ptbins, 8 );
    }


    if(loose_el.at(0).Pt() < 15.)  FillHist(("LooseEl" + tag + "_eta_pt1").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(loose_el.at(0).Pt() < 20.)  FillHist(("LooseEl" + tag + "_eta_pt2").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(loose_el.at(0).Pt() < 30.)  FillHist(("LooseEl" + tag + "_eta_pt3").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(loose_el.at(0).Pt() < 40.)  FillHist(("LooseEl" + tag + "_eta_pt4").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(loose_el.at(0).Pt() < 50.)  FillHist(("LooseEl" + tag + "_eta_pt5").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(loose_el.at(0).Pt() < 60.)  FillHist(("LooseEl" + tag + "_eta_pt6").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else   FillHist(("LooseEl" + tag + "_eta_pt7").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);

    if(SumPt(jets) < 30.)  FillHist(("LooseEl" + tag + "_eta_ht1").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 50.)  FillHist(("LooseEl" + tag + "_eta_ht2").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 60.)  FillHist(("LooseEl" + tag + "_eta_ht3").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else if(SumPt(jets) < 80.)  FillHist(("LooseEl" + tag + "_eta_ht4").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    else  FillHist(("LooseEl" + tag + "_eta_ht5").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);

    if(jets.size()==1) FillHist(("LooseEl" + tag + "_pt_eta_nj1").Data(), el_pt, fabs(loose_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    if(jets.size()==2) FillHist(("LooseEl" + tag + "_pt_eta_nj2").Data(), el_pt, fabs(loose_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);
    if(jets.size()>2) FillHist(("LooseEl" + tag + "_pt_eta_nj3").Data(), el_pt, fabs(loose_el.at(0).Eta()), weight, ptbins, 8 , etabins, 4);

    //FillHist(("LooseEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets), weight, ptbins, 8 , htbins, 11);

    if(fabs( loose_el.at(0).Eta() < 1.5)) {
      FillHist(("LooseEl" + tag + "_ptbarrel_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
      FillHist(("LooseEl" + tag + "_ptbarrel").Data(),el_pt, weight,  ptbins, 8);
    }
    else{
      FillHist(("LooseEl" + tag + "_ptendcap_ht").Data(), el_pt, SumPt(jets), weight, ptbins_ht, 8 , htbins_pt, 8);
      FillHist(("LooseEl" + tag + "_ptendcap").Data(),el_pt, weight,  ptbins, 8);
    }
    
    if(jets.size() > 1)     FillHist(("LooseEl" + tag + "_ht_dijet").Data(), SumPt(jets) , weight, htbins, 13);
    if(jets.size() > 1) {
      FillHist(("LooseEl" + tag + "_nbjet_dijet").Data(), nbjet, weight, 0., 4.,4);
    }   
  }

  return;
}



void FakeRateCalculator_El::GetRealEfficiency(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, std::vector<snu::KMuon> muons, double w, float interval,TString tag, double dxycut,  double  barreliso, double endcapiso, bool dr3, bool usetrkiso, bool usetight){
  
  Float_t ptbins[18] = {10.,12.5,15.,17.5, 20.,25.,30.,35.,40.,45.,50.,60., 70., 80., 100., 125., 150., 200.};
  Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
  
  int numbjet(0);
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CombinedSecVertexBtag() > 0.679) numbjet++;
  }


  if(electrons.size() == 2){
    //FillCLHist(sighist, ("DiLooseEl_" + tag).Data() , eventbase->GetEvent(), muons, electrons,jets, w);
    if(Zcandidate(electrons, interval)){
      //FillCLHist(sighist, ("ZDiLooseEl_"+tag).Data(), eventbase->GetEvent(), muons,electrons,jets, w);

      //// Electron 1 IS TAG
      if(IsTight(electrons.at(0), eventbase->GetEvent().JetRho(), dxycut,barreliso, endcapiso,dr3, usetrkiso, usetight)  ){
        
	FillHist(("h_promptrate_"+ tag+"_denom_pt").Data(), electrons.at(1).Pt(), w, ptbins,17);
        FillHist(("h_promptrate_"+ tag+"_denom_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 50.,50);
        FillHist(("h_promptrate_" + tag +"_denom_eta").Data(), electrons.at(1).Eta(), w, -2.5, 2.5,50);
        FillHist(("h_promptrate_" + tag +"_denom_njets").Data(), jets.size(), w, 0., 5.,5);
	FillHist(("h_promptrate_" + tag +"_denom_pt_eta").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() == 0)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_0jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() == 1)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_1jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() >= 2)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_2jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);

	

	if(numbjet > 0){
	  FillHist(("h_promptrate_bjet_" + tag +"_denom_pt_eta").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	}
	
        if(electrons.at(1).IsEBFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_barrel_pt").Data(), electrons.at(1).Pt(), w,  ptbins,17);
        }
        else if(electrons.at(1).IsEEFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_endcap_pt").Data(), electrons.at(1).Pt(), w,  ptbins,17);
        }

        /// Electron 2 is probe
        if(IsTight(electrons.at(1), eventbase->GetEvent().JetRho(), dxycut, barreliso, endcapiso,dr3, usetrkiso, usetight)){
          FillHist(("h_promptrate_" + tag +"_num_pt").Data(), electrons.at(1).Pt(), w,  ptbins,17);
          FillHist(("h_promptrate_"+  tag +"_num_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 50.,50);
          FillHist(("h_promptrate_" + tag +"_num_eta").Data(), electrons.at(1).Eta(), w, -2.5, 2.5,50);
          FillHist(("h_promptrate_" + tag +"_num_njets").Data(), jets.size(), w, 0., 5.,5);
	  FillHist(("h_promptrate_" + tag +"_num_pt_eta").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() == 0)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_0jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() == 1)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_1jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() >= 2)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_2jet").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);

	  
	  if(numbjet > 0){
	    FillHist(("h_promptrate_bjet_" + tag +"_num_pt_eta").Data(), electrons.at(1).Pt(), electrons.at(1).Eta(), w, ptbins,17, etabins, 4);
	  }

          if(electrons.at(1).IsEBFiducial()){
            FillHist(("h_promptrate_" + tag +"_num_barrel_pt").Data(), electrons.at(1).Pt(), w, ptbins,17);
          }
          else if(electrons.at(1).IsEEFiducial()){
            FillHist(("h_promptrate_" + tag +"_num_endcap_pt").Data(), electrons.at(1).Pt(), w, ptbins,17);
          }
        }
      }

      //// Electron 2 IS TAG
      if(IsTight(electrons.at(1), eventbase->GetEvent().JetRho(),  dxycut, barreliso, endcapiso,dr3, usetrkiso, usetight)){

        FillHist(("h_promptrate_" + tag +"_denom_pt").Data(), electrons.at(0).Pt(), w, ptbins,17);
        FillHist(("h_promptrate_"+ tag+"_denom_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 50.,50);
        FillHist(("h_promptrate_" + tag +"_denom_eta").Data(), electrons.at(0).Eta(), w, -2.5, 2.5,50);
        FillHist(("h_promptrate_" + tag +"_denom_njets").Data(), jets.size(), w, 0., 5.,5);
	FillHist(("h_promptrate_" + tag +"_denom_pt_eta").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() == 0)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_0jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() == 1)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_1jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	if(jets.size() >= 2)         FillHist(("h_promptrate_" + tag +"_denom_pt_eta_2jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);


	if(numbjet > 0){
          FillHist(("h_promptrate_bjet_" + tag +"_denom_pt_eta").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	}
        if(electrons.at(0).IsEBFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_barrel_pt").Data(), electrons.at(0).Pt(), w,ptbins,17);
        }
        else if(electrons.at(0).IsEEFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_endcap_pt").Data(), electrons.at(0).Pt(), w,ptbins,17);
        }

        //// Electron 1 is probe
        if(IsTight(electrons.at(0),eventbase->GetEvent().JetRho(), dxycut, barreliso, endcapiso,dr3, usetrkiso, usetight)){
          FillHist(("h_promptrate_" + tag +"_num_pt").Data(), electrons.at(0).Pt(), w, ptbins,17);
          FillHist(("h_promptrate_"+ tag+"_num_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 50.,50);
          FillHist(("h_promptrate_" + tag +"_num_eta").Data(), electrons.at(0).Eta(), w, -2.5, 2.5,50);
          FillHist(("h_promptrate_" + tag +"_num_njets").Data(), jets.size(), w, 0., 5.,5);
	  FillHist(("h_promptrate_" + tag +"_num_pt_eta").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() == 0)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_0jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() == 1)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_1jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	  if(jets.size() >= 2)         FillHist(("h_promptrate_" + tag +"_num_pt_eta_2jet").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);

	  
	  if(numbjet > 0){
	    FillHist(("h_promptrate_bjet_" + tag +"_num_pt_eta").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);
	  }
          if(electrons.at(0).IsEBFiducial()){
            FillHist(("h_promptrate_" + tag +"_num_barrel_pt").Data(), electrons.at(0).Pt(), w,ptbins,17);
          }
          else if(electrons.at(0).IsEEFiducial()){
            FillHist(("h_promptrate_" + tag +"_num_endcap_pt").Data(), electrons.at(0).Pt(), w, ptbins,17);
          }
        }
      }
    }
  }
  return;
}





void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger<< INFO << "Number of events that pass 17 GeV trigger = " << n_17_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV + jet trigger = " << n_17_jet_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV || jet trigger = " << n_17_17_jet_pass  << LQLogger::endmsg;

}

bool FakeRateCalculator_El::IsTight(snu::KElectron el, double jetrho , double dxy, double biso, double eiso, bool usedr3, bool usetrkiso, bool usetight){
  
  return eventbase->GetElectronSel()->HNIsTight(el, jetrho, dxy, biso, eiso, usedr3, usetrkiso, usetight, false);

}



void FakeRateCalculator_El::BeginCycle() throw( LQError ){
  
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

  n_17_jet_pass=0;
  n_17_17_jet_pass=0;
  n_17_pass=0;

  
  return;
  
}

FakeRateCalculator_El::~FakeRateCalculator_El() {
  
  Message("In FakeRateCalculator_El Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void FakeRateCalculator_El::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow",10,0.,10.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"Trigger_Ele17");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"Trigger_Ele17Jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"Ele17_single_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"Ele17Jet_single_el");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"Ele17_gt1jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"Ele17Jet_gt1jet");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"Ele17_muonveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"Ele17Jet_muonveto");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"Ele17_Zveto");	
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"Ele17Jet_Zveto");
  }
}


void FakeRateCalculator_El::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void FakeRateCalculator_El::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this FakeRateCalculator_ElCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void FakeRateCalculator_El::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



