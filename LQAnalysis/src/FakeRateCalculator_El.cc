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

  std::vector<snu::KElectron> electronLooseColl;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl);

  std::vector<snu::KElectron> electronLooseColl_medium;
  eventbase->GetElectronSel()->HNLooseElectronSelection(electronLooseColl_medium, false); /// Sets medium WP cuts 
  
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronLooseColl.begin(); it != electronLooseColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt());
    }
  }


  std::vector<snu::KElectron> electronTightColl_dxy05;
  std::vector<snu::KElectron> electronTightColl_dxy10;
  std::vector<snu::KElectron> electronTightColl_dxy15;
  std::vector<snu::KElectron> electronTightColl_dxy20;
  std::vector<snu::KElectron> electronTightColl_dxy25;
  std::vector<snu::KElectron> electronTightColl_dxy30;
  
  std::vector<snu::KElectron> electronTightColl_medium;
  std::vector<snu::KElectron> electronTightColl_tight;

  std::vector<snu::KElectron> electronTightColl_dr03_150;
  std::vector<snu::KElectron> electronTightColl_dr03_125;
  std::vector<snu::KElectron> electronTightColl_dr03_100;
  std::vector<snu::KElectron> electronTightColl_dr03_090;
  std::vector<snu::KElectron> electronTightColl_dr03_080;
  std::vector<snu::KElectron> electronTightColl_dr03_070;
  std::vector<snu::KElectron> electronTightColl_dr03_060;
  std::vector<snu::KElectron> electronTightColl_dr03_050;

  std::vector<snu::KElectron> electronTightColl_dr04_150;
  std::vector<snu::KElectron> electronTightColl_dr04_125;
  std::vector<snu::KElectron> electronTightColl_dr04_100;
  std::vector<snu::KElectron> electronTightColl_dr04_090;
  std::vector<snu::KElectron> electronTightColl_dr04_080;
  std::vector<snu::KElectron> electronTightColl_dr04_070;
  std::vector<snu::KElectron> electronTightColl_dr04_060;
  std::vector<snu::KElectron> electronTightColl_dr04_050;
  
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b150_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b125_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b100_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b090_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b080_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e060;
  std::vector<snu::KElectron>  electronTightColl_dr03_b070_e050;

  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e125;
  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e100;
  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e090;
  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e080;
  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e070;
  std::vector<snu::KElectron>  electronTightColl_dr03_b050_e060;

  
  // add trkiso
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b150_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b125_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b100_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b090_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b080_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e060;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b070_e050;

  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e125;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e100;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e090;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e080;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e070;
  std::vector<snu::KElectron>  electronTightColl_NPFisodr03_b050_e060;

  for(unsigned int iel = 0; iel < electronLooseColl.size(); iel++){
    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    Double_t PHONH_04[7]          = {0.208, 0.209, 0.115, 0.143, 0.183, 0.194, 0.261};

    int ifid = 0;
    if (fabs(electronLooseColl.at(iel).SCEta()) < 1.0) ifid = 0;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479) ifid = 1;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.0) ifid = 2;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.2) ifid = 3;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.3) ifid = 4;
    else if (fabs(electronLooseColl.at(iel).SCEta()) < 2.4) ifid = 5;
    else ifid = 6;

    float LeptonRelIsoDR03(0.);
    float LeptonRelIsoDR04(0.);
    float trkiso = electronLooseColl.at(iel).TrkIsoDR03();
    float ecaliso = electronLooseColl.at(iel).ECalIsoDR03();
    float hcaliso = electronLooseColl.at(iel).HCalIsoDR03();
    float NPFiso = (trkiso + hcaliso + ecaliso)/electronLooseColl.at(iel).Pt();

    float ElectronIsoDR03 =  electronLooseColl.at(iel).PFChargedHadronIso03() + max( electronLooseColl.at(iel).PFNeutralHadronIso03() + electronLooseColl.at(iel).PFPhotonIso03() - eventbase->GetEvent().JetRho() * PHONH_03[ifid],  0.);
    float ElectronIsoDR04 =  electronLooseColl.at(iel).PFChargedHadronIso04() + max( electronLooseColl.at(iel).PFNeutralHadronIso04() + electronLooseColl.at(iel).PFPhotonIso04() - eventbase->GetEvent().JetRho() * PHONH_04[ifid],  0.);
    
    if(electronLooseColl.at(iel).Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  electronLooseColl.at(iel).Pt();
    if(electronLooseColl.at(iel).Pt() > 0.)  LeptonRelIsoDR04 = ElectronIsoDR04/  electronLooseColl.at(iel).Pt();
    
    
    if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479 ){
      if(LeptonRelIsoDR03 < 0.10){
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.005 )  electronTightColl_dxy05.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.010 )  electronTightColl_dxy10.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.015 )  electronTightColl_dxy15.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.020 )  electronTightColl_dxy20.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.025 )  electronTightColl_dxy25.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.030 )  electronTightColl_dxy30.push_back(electronLooseColl.at(iel));
      }
    }
    else{
      if(LeptonRelIsoDR03 < 0.07){
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.005 )  electronTightColl_dxy05.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.010 )  electronTightColl_dxy10.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.015 )  electronTightColl_dxy15.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.020 )  electronTightColl_dxy20.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.025 )  electronTightColl_dxy25.push_back(electronLooseColl.at(iel));
	if(fabs(electronLooseColl.at(iel).dxy()) < 0.030 )  electronTightColl_dxy30.push_back(electronLooseColl.at(iel));
      }
    }

    if(fabs(electronLooseColl.at(iel).dxy()) < 0.010){
      if(LeptonRelIsoDR03 < 0.15)  electronTightColl_dr03_150.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.125) electronTightColl_dr03_125.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.1)   electronTightColl_dr03_100.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.09)  electronTightColl_dr03_090.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.08)  electronTightColl_dr03_080.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.07)  electronTightColl_dr03_070.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.06)  electronTightColl_dr03_060.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR03 < 0.05)  electronTightColl_dr03_050.push_back(electronLooseColl.at(iel));

      if(LeptonRelIsoDR04 < 0.15)  electronTightColl_dr04_150.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.125) electronTightColl_dr04_125.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.1)   electronTightColl_dr04_100.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.09)  electronTightColl_dr04_090.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.08)  electronTightColl_dr04_080.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.07)  electronTightColl_dr04_070.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.06)  electronTightColl_dr04_060.push_back(electronLooseColl.at(iel));
      if(LeptonRelIsoDR04 < 0.05)  electronTightColl_dr04_050.push_back(electronLooseColl.at(iel));
      
      if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479 ){
        if(LeptonRelIsoDR03 < 0.15) {
          electronTightColl_dr03_b150_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b150_e050.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.125) {
          electronTightColl_dr03_b125_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e050.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.1) {
          electronTightColl_dr03_b100_e125.push_back(electronLooseColl.at(iel));
	  electronTightColl_dr03_b100_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e050.push_back(electronLooseColl.at(iel));
        }
	if(LeptonRelIsoDR03 < 0.09) {
          electronTightColl_dr03_b090_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e050.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.08) {
          electronTightColl_dr03_b080_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e050.push_back(electronLooseColl.at(iel));
        }

	if(LeptonRelIsoDR03 < 0.07) {
          electronTightColl_dr03_b070_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e050.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.05) {
          electronTightColl_dr03_b050_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e060.push_back(electronLooseColl.at(iel));
        }
      }
      else{
	if(LeptonRelIsoDR03 < 0.125) {
          electronTightColl_dr03_b150_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e125.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e125.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.100) {
          electronTightColl_dr03_b150_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e100.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e100.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.090) {
          electronTightColl_dr03_b150_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e090.push_back(electronLooseColl.at(iel));
	  electronTightColl_dr03_b080_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e090.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e090.push_back(electronLooseColl.at(iel));
        }
        if(LeptonRelIsoDR03 < 0.080) {
          electronTightColl_dr03_b150_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e080.push_back(electronLooseColl.at(iel));
	  electronTightColl_dr03_b070_e080.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e080.push_back(electronLooseColl.at(iel));
        }
	if(LeptonRelIsoDR03 < 0.070) {
          electronTightColl_dr03_b150_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e070.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e070.push_back(electronLooseColl.at(iel));
	  electronTightColl_dr03_b050_e070.push_back(electronLooseColl.at(iel));
        }

        if(LeptonRelIsoDR03 < 0.060) {
          electronTightColl_dr03_b150_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e060.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b050_e060.push_back(electronLooseColl.at(iel));
        }

        if(LeptonRelIsoDR03 < 0.050) {
          electronTightColl_dr03_b150_e050.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b125_e050.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b100_e050.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b090_e050.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b080_e050.push_back(electronLooseColl.at(iel));
          electronTightColl_dr03_b070_e050.push_back(electronLooseColl.at(iel));
        }
      }
      if(NPFiso < 0.25){
        if (fabs(electronLooseColl.at(iel).SCEta()) < 1.479 ){
          if(LeptonRelIsoDR03 < 0.15) {
            electronTightColl_NPFisodr03_b150_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b150_e050.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.125) {
            electronTightColl_NPFisodr03_b125_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e050.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.1) {
            electronTightColl_NPFisodr03_b100_e125.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b100_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e050.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.09) {
	    electronTightColl_NPFisodr03_b090_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e100.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b090_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e050.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.08) {
            electronTightColl_NPFisodr03_b080_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e090.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b080_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e050.push_back(electronLooseColl.at(iel));
          }

          if(LeptonRelIsoDR03 < 0.07) {
            electronTightColl_NPFisodr03_b070_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e080.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b070_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e050.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.05) {
	    electronTightColl_NPFisodr03_b050_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e060.push_back(electronLooseColl.at(iel));
          }
        }
        else{
          if(LeptonRelIsoDR03 < 0.125) {
            electronTightColl_NPFisodr03_b150_e125.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b100_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e125.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e125.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.100) {
            electronTightColl_NPFisodr03_b150_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e100.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b090_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e100.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e100.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.090) {
            electronTightColl_NPFisodr03_b150_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e090.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b080_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e090.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e090.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.080) {
	    electronTightColl_NPFisodr03_b150_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e080.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b070_e080.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e080.push_back(electronLooseColl.at(iel));
          }
          if(LeptonRelIsoDR03 < 0.070) {
            electronTightColl_NPFisodr03_b150_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e070.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e070.push_back(electronLooseColl.at(iel));
	    electronTightColl_NPFisodr03_b050_e070.push_back(electronLooseColl.at(iel));
          }

          if(LeptonRelIsoDR03 < 0.060) {
            electronTightColl_NPFisodr03_b150_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e060.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b050_e060.push_back(electronLooseColl.at(iel));
          }

          if(LeptonRelIsoDR03 < 0.050) {
	    electronTightColl_NPFisodr03_b150_e050.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b125_e050.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b100_e050.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b090_e050.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b080_e050.push_back(electronLooseColl.at(iel));
            electronTightColl_NPFisodr03_b070_e050.push_back(electronLooseColl.at(iel));
          }
        }
      }
    } /// dxy < 0.01
  }
  
  
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
                        if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
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
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(egamma_pfiso_03    <=  0.07){
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
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.1){
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
			if(fabs(electronNoCutColl.at(iel).dxy())  <= 0.01){
			  if(egamma_pfiso_03    <=  0.07){
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
  
  std::vector<snu::KMuon> muonLooseColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonLooseColl);

  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);

  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);


  std::vector<snu::KJet> jetColl_lepveto20;
  std::vector<snu::KJet> jetColl_lepveto40;
  std::vector<snu::KJet> jetColl_lepveto60;
  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetUseJetPileUp(true);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->Selection(jetColl);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto20, muonTightColl, electronLooseColl);
  eventbase->GetJetSel()->SetPt(40.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto40, muonTightColl, electronLooseColl);
  eventbase->GetJetSel()->SetPt(60.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto60, muonTightColl, electronLooseColl);
    

  if(!k_isdata&&electronLooseColl.size() >0){
    Float_t ptbins[8] = { 15.,20.,25.,30.,35.,40.,60.,100.};
    Float_t htbins[5] = { 0., 30., 50., 100., 200.};
    float el_pt = electronLooseColl.at(0).Pt();
    if(electronLooseColl.at(0).GetType() == 1 || electronLooseColl.at(0).GetType() == 2 || electronLooseColl.at(0).GetType() == 3 || electronLooseColl.at(0).GetType() == 6){
      if (electronLooseColl.size() == 1 ){
	FillHist("MCLooseEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	FillHist("MCLooseEl_pt",el_pt , weight, ptbins, 7);
	FillHist("MCLooseEl_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
	FillHist("MCLooseEl_ht", SumPt(jetColl_lepveto40), weight, htbins, 4);
	
	if(electronTightColl.size() == 1){
	  FillHist("MCTightEl_eta", electronLooseColl.at(0).Eta(), weight, -2.5, 2.5,50);
	  FillHist("MCTightEl_pt", el_pt, weight, ptbins, 7);
	  FillHist("MCTightEl_njets", jetColl_lepveto40.size(), weight, 0.,5.,5);
	  FillHist("MCTightEl_ht", SumPt(jetColl_lepveto40), weight, htbins, 4);
	}
      }
    }
  }
  
  
  m_logger << DEBUG << "Running real efficiency code" << LQLogger::endmsg;
  

  /// This code calculates the real efficiency
  if(PassTrigger(triggerslist_diel, prescale)){
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "", 0.01, 0.1,  0.07, true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 2.5, "TightWindow", 0.01, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 10., "LooseWindow",0.01, 0.1 , 0.07, true,false,true);

    /// Optimising
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "Tight", 0.02, 0.1, 0.07 , true,false,true);    
    GetRealEfficiency(electronLooseColl_medium, jetColl_lepveto20, muonLooseColl, weight, 5., "Medium", 0.02, 0.1, 0.07 , true,false,false);    

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy05", 0.005, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy10", 0.01, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy15", 0.015, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy20", 0.02, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy25", 0.025, 0.1, 0.07 , true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight, 5., "dxy30", 0.030, 0.1, 0.07 , true,false,true);
  
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E150_dr03", 0.01, 0.15,0.15,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E125_dr03", 0.01, 0.125,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E100_dr03", 0.01, 0.1,0.1,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E090_dr03", 0.01, 0.09,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E080_dr03", 0.01, 0.08,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E070_dr03", 0.01, 0.07,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B060_E060_dr03", 0.01, 0.06,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E050_dr03", 0.01, 0.05,0.05,true,false,true);
    
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E150_dr04", 0.01, 0.150,0.150,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E125_dr04", 0.01, 0.125,0.125,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E100_dr04", 0.01, 0.1,0.1,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E090_dr04", 0.01, 0.09,0.09,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E080_dr04", 0.01, 0.08,0.08,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E070_dr04", 0.01, 0.07,0.07,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B060_E060_dr04", 0.01, 0.06,0.06,false,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E050_dr04", 0.01, 0.05,0.05,false,false,true);

    /// B/E
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E125_dr03", 0.01, 0.15,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E100_dr03", 0.01, 0.15,0.100,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E090_dr03", 0.01, 0.15,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E080_dr03", 0.01, 0.15,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E070_dr03", 0.01, 0.15,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E060_dr03", 0.01, 0.15,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B150_E050_dr03", 0.01, 0.15,0.05,true,false,true);
    
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E100_dr03", 0.01, 0.125,0.100,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E090_dr03", 0.01, 0.125,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E080_dr03", 0.01, 0.125,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E070_dr03", 0.01, 0.125,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E060_dr03", 0.01, 0.125,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B125_E050_dr03", 0.01, 0.125,0.05,true,false,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E125_dr03", 0.01, 0.1,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E090_dr03", 0.01, 0.1,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E080_dr03", 0.01, 0.1,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E070_dr03", 0.01, 0.1,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E060_dr03", 0.01, 0.1,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B100_E050_dr03", 0.01, 0.1,0.05,true,false,true);
    
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E125_dr03", 0.01, 0.09,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E100_dr03", 0.01, 0.09,0.1,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E080_dr03", 0.01, 0.09,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E070_dr03", 0.01, 0.09,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E060_dr03", 0.01, 0.09,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B090_E050_dr03", 0.01, 0.09,0.05,true,false,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E125_dr03", 0.01, 0.08,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E100_dr03", 0.01, 0.08,0.1,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E090_dr03", 0.01, 0.08,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E070_dr03", 0.01, 0.08,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E060_dr03", 0.01, 0.08,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B080_E050_dr03", 0.01, 0.08,0.05,true,false,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E125_dr03", 0.01, 0.07,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E100_dr03", 0.01, 0.07,0.1,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E090_dr03", 0.01, 0.07,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E080_dr03", 0.01, 0.07,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E060_dr03", 0.01, 0.07,0.06,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B070_E050_dr03", 0.01, 0.07,0.05,true,false,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E125_dr03", 0.01, 0.05,0.125,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E100_dr03", 0.01, 0.05,0.1,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E090_dr03", 0.01, 0.05,0.09,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E080_dr03", 0.01, 0.05,0.08,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E070_dr03", 0.01, 0.05,0.07,true,false,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "iso_B050_E060_dr03", 0.01, 0.05,0.06,true,false,true);

    /// Include Trk iso
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E125_dr03", 0.01, 0.15,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E100_dr03", 0.01, 0.15,0.100,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E090_dr03", 0.01, 0.15,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E080_dr03", 0.01, 0.15,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E070_dr03", 0.01, 0.15,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E060_dr03", 0.01, 0.15,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B150_E050_dr03", 0.01, 0.15,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E100_dr03", 0.01, 0.125,0.100,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E090_dr03", 0.01, 0.125,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E080_dr03", 0.01, 0.125,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E070_dr03", 0.01, 0.125,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E060_dr03", 0.01, 0.125,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B125_E050_dr03", 0.01, 0.125,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E125_dr03", 0.01, 0.1,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E090_dr03", 0.01, 0.1,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E080_dr03", 0.01, 0.1,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E070_dr03", 0.01, 0.1,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E060_dr03", 0.01, 0.1,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B100_E050_dr03", 0.01, 0.1,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E125_dr03", 0.01, 0.09,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E100_dr03", 0.01, 0.09,0.1,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E080_dr03", 0.01, 0.09,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E070_dr03", 0.01, 0.09,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E060_dr03", 0.01, 0.09,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B090_E050_dr03", 0.01, 0.09,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E125_dr03", 0.01, 0.08,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E100_dr03", 0.01, 0.08,0.1,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E090_dr03", 0.01, 0.08,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E070_dr03", 0.01, 0.08,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E060_dr03", 0.01, 0.08,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B080_E050_dr03", 0.01, 0.08,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E125_dr03", 0.01, 0.07,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E100_dr03", 0.01, 0.07,0.1,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E090_dr03", 0.01, 0.07,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E080_dr03", 0.01, 0.07,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E060_dr03", 0.01, 0.07,0.06,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B070_E050_dr03", 0.01, 0.07,0.05,true,true,true);

    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E125_dr03", 0.01, 0.05,0.125,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E100_dr03", 0.01, 0.05,0.1,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E090_dr03", 0.01, 0.05,0.09,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E080_dr03", 0.01, 0.05,0.08,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E070_dr03", 0.01, 0.05,0.07,true,true,true);
    GetRealEfficiency(electronLooseColl, jetColl_lepveto20, muonLooseColl, weight,5., "NPFiso_B050_E060_dr03", 0.01, 0.05,0.06,true,true,true);
    

 }
  

  FillCLHist(sighist, "SingleEl_nocut", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  
  std::vector<TString> triggerslist17jet;
  triggerslist17jet.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");
  
  std::vector<TString> triggerslist8jet;
  triggerslist8jet.push_back("HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v");

  bool pass_eljettrig= false;
  
  /// Calcalate prescale weights
  float prescale_trigger = 0.;
  if(electronLooseColl.size() ==1){
    if(electronLooseColl.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
	prescale_trigger = (24.18) / 19789 ; //// 20 + GeV bins
	pass_eljettrig = true;
      }
      else prescale_trigger = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
	prescale_trigger = (4.85) / 19789 ;
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
  if(electronLooseColl_medium.size() ==1){
    if(electronLooseColl_medium.at(0).Pt() >= 20.){
      if(PassTrigger(triggerslist17jet, prescale)) {
        prescale_trigger_medium = (24.18) / 19789 ; //// 20 + GeV bins
        pass_eljettrig_medium = true;
      }
      else prescale_trigger_medium = 0.;
    }
    else{
      /// if single el event and low pt use 8 GeV trigger
      if(PassTrigger(triggerslist8jet, prescale)){
        prescale_trigger_medium = (4.85) / 19789 ;
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
      for(unsigned int w = 0; w < electronLooseColl_medium.size();  w++){
	METdphi_med = TVector2::Phi_mpi_pi(electronLooseColl_medium.at(w).Phi()- eventbase->GetEvent().PFMETphi());
	MT_med = sqrt(2.* electronLooseColl_medium.at(w).Et()*eventbase->GetEvent().PFMET() * (1 - cos( METdphi_med)));
      }
      

      bool truth_match_medium=false;
      
      /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
      if(!k_isdata) {
	if(electronLooseColl_medium.size() > 0){
	  /// ONLY INCLUDE ELECTRONS FROM W/Z
	  if((electronLooseColl_medium.at(0).GetType() == 0) || (electronLooseColl_medium.at(0).GetType() ==7))  truth_match_medium=true;
	}
	else truth_match_medium = true;
      }
      if(( (eventbase->GetEvent().PFMET() < 20) && (MT_med < 25.)) ) {
	
	bool useevent40_medium = false;
	for (unsigned int ielT=0; ielT < electronLooseColl_medium.size(); ielT++){
	  for(unsigned int ij=0; ij < jetColl_lepveto40.size(); ij++){

	    float dphi =TVector2::Phi_mpi_pi(electronLooseColl_medium.at(ielT).Phi()- jetColl_lepveto40.at(ij).Phi());
	    if( (jetColl_lepveto40.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto40.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	    
	    if(dphi > 2.5) useevent40_medium = true;
	  }
	}
	
	Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
	//Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
	//Float_t htbins[5] = { 0., 30., 50., 100., 200.};
	Float_t ebetabins[3] = { 0., 1.479, 2.5};

	if(useevent40_medium&&truth_match_medium){
	  float elm_pt = electronLooseColl_medium.at(0).Pt();
	  if(electronLooseColl_medium.at(0).Pt() > 100.) elm_pt = 99.;
	  float elm_eta = fabs(electronLooseColl_medium.at(0).Eta());
	  
	  if(jetColl_lepveto40.size() >= 1){
	    if( electronTightColl_medium.size()==1 )   FillHist("Tight_medium_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);
	    if( electronLooseColl_medium.size()==1 )   FillHist("LooseOpt_medium_pt_eta",elm_pt, elm_eta, weight_med,  ptbins, 8, ebetabins, 2);
	    
	  }
	}
      }
    }
  }
  
  
  
  weight = weight * prescale_trigger;
  /// prescale_trigger = 1 for data, 0 if failed trigger
  
  
  if(!pass_eljettrig) return;
  
  FillCLHist(sighist, "SingleEl_trigger", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  if(jetColl_lepveto20.size() >= 1 ) FillCLHist(sighist, "SingleEl_jet20", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto20, weight);
  if(jetColl_lepveto40.size() >= 1 ) FillCLHist(sighist, "SingleEl_jet40", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
  
  
  m_logger << DEBUG << "Running fake efficiency code" << LQLogger::endmsg;
  
  
  /// REMOVE Z like events
  if(electronVetoColl.size() == 2) {
    if(electronVetoColl.at(0).Charge() != electronVetoColl.at(1).Charge()){
      snu::KParticle Z = electronVetoColl.at(0) + electronVetoColl.at(1);
      if(Z.M() > 76. && Z.M() < 106.) return;
    }
  }
  
  /// Z and W veto
  Double_t MT=0;
  Double_t METdphi=0;
  m_logger << DEBUG << "Filling single lepton + 1 jet plots " << LQLogger::endmsg;
  if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
  if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  
  
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
  
  if(truth_match){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_tm", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_tm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  }
  
  
  m_logger << DEBUG << "making cuts to remove prompt leptons" << LQLogger::endmsg;
  m_logger << DEBUG << "Selecting region to calculate MC SFs " << LQLogger::endmsg;
  
  if(eventbase->GetEvent().PFMET() > 30 && (60. < MT)  &&(MT < 100.) &&truth_match){
    
    if(electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  }
  
  if(eventbase->GetEvent().PFMET() > 50 && (60. < MT)  &&(MT < 100.)&& truth_match){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_prompt", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
  }
  
  
  if( (eventbase->GetEvent().PFMET() < 20) && (MT < 20.) &&truth_match){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_tight", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_tight", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  }
  
  
  if( (eventbase->GetEvent().PFMET() < 25) && (MT < 25.) &&truth_match ){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_medium", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_medium", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  }
  
  
  if( (eventbase->GetEvent().PFMET() < 30) && MT < 30. &&truth_match){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_loose", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_loose", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    
  }
  
  if( (eventbase->GetEvent().PFMET() < 40) && MT < 40. &&truth_match){
    if (jetColl_lepveto40.size() >= 1 )FillCLHist(sighist, "SingleLooseElJet_metmt_vloose", eventbase->GetEvent(), muonLooseColl,electronLooseColl,jetColl_lepveto40, weight);
    if (electronTightColl.size() == 1&& jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "SingleTightElJet_metmt_vloose", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
  }
  
  
  if( !( (eventbase->GetEvent().PFMET() < 20) && (MT < 25.)) ) return;
  
  
  m_logger << DEBUG << "Making plots for fake rates with different jet cuts" << LQLogger::endmsg;
  
  bool useevent20= false;
  bool useevent40= false;
  bool useevent60= false;
  /// Fake Rates
  
  if ( jetColl_lepveto20.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto20.size(); ij++){
	
	float dphi = TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto20.at(ij).Phi());
	if( (jetColl_lepveto20.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto20.at(ij).ChargedEMEnergyFraction()) > 0.65) continue;
	
        if(dphi > 2.5) useevent20 = true;
      }
    }
  }
  
  if (jetColl_lepveto40.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto40.size(); ij++){
	
	float dphi =TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto40.at(ij).Phi());
        if( (jetColl_lepveto40.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto40.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	
	if(dphi > 2.5) useevent40 = true;
      }
    }
  }
  
  
  
  if (jetColl_lepveto60.size() >= 1){
    for (unsigned int ielT=0; ielT < electronLooseColl.size(); ielT++){
      for(unsigned int ij=0; ij < jetColl_lepveto60.size(); ij++){

	float dphi =TVector2::Phi_mpi_pi(electronLooseColl.at(ielT).Phi()- jetColl_lepveto60.at(ij).Phi());
        if( (jetColl_lepveto60.at(ij).NeutralEMEnergyFraction() +jetColl_lepveto60.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
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
  
 
  
  if(useevent40){
    if ( electronTightColl.size() == 1 && jetColl_lepveto40.size() >= 1)FillCLHist(sighist, "TightEl40_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    if (jetColl_lepveto40.size() >= 1) FillCLHist(sighist, "LooseEl40_notm", eventbase->GetEvent(), muonLooseColl,electronTightColl,jetColl_lepveto40, weight);
    
  }
  


  if(useevent40&&truth_match){
    if(jetColl_lepveto40.size() >= 1){
      if( electronLooseColl.size()==1 )   FillHist("LooseOpt_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy05.size()==1 )   FillHist("Tight_dxy05_El40_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy10.size()==1 )   FillHist("Tight_dxy10_El40_pt_eta",el_pt, el_eta,  weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy15.size()==1 )   FillHist("Tight_dxy15_El40_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy20.size()==1 )   FillHist("Tight_dxy20_El40_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy25.size()==1 )   FillHist("Tight_dxy25_El40_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_dxy30.size()==1 )   FillHist("Tight_dxy30_El40_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if( electronTightColl_tight.size()==1 )   FillHist("Tight_tight_pt_eta",el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

    
      if(electronTightColl_dr03_150.size()==1 )  FillHist("Tight_iso_dr3_b150_e150_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_125.size()==1 )  FillHist("Tight_iso_dr3_b125_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_100.size()==1 )  FillHist("Tight_iso_dr3_b100_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_090.size()==1 )  FillHist("Tight_iso_dr3_b090_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_080.size()==1 )  FillHist("Tight_iso_dr3_b080_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_070.size()==1 )  FillHist("Tight_iso_dr3_b070_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_060.size()==1 )  FillHist("Tight_iso_dr3_b060_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr03_050.size()==1 )  FillHist("Tight_iso_dr3_b050_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);      

      if(electronTightColl_dr04_150.size()==1 )  FillHist("Tight_iso_dr4_b150_e150_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_125.size()==1 )  FillHist("Tight_iso_dr4_b125_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_100.size()==1 )  FillHist("Tight_iso_dr4_b100_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_090.size()==1 )  FillHist("Tight_iso_dr4_b090_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_080.size()==1 )  FillHist("Tight_iso_dr4_b080_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_070.size()==1 )  FillHist("Tight_iso_dr4_b070_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_060.size()==1 )  FillHist("Tight_iso_dr4_b060_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_dr04_050.size()==1 )  FillHist("Tight_iso_dr4_b050_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      /// Get asymmetric fake rates for E/B
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

      /// Add trk iso
      if(electronTightColl_NPFisodr03_b150_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b150_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b150_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_NPFisodr03_b125_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b125_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b125_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b125_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b125_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b125_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b125_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_NPFisodr03_b100_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b100_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b100_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b100_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b100_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b100_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b100_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_NPFisodr03_b090_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b090_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b090_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b090_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b090_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b090_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b090_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_NPFisodr03_b080_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b080_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b080_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b080_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b080_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b080_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b080_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);


      if(electronTightColl_NPFisodr03_b070_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b070_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b070_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b070_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b070_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b070_e050.size()==1 ) FillHist("Tight_iso_NPFisodr3_b070_e050_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);

      if(electronTightColl_NPFisodr03_b050_e100.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e100_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b050_e090.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e090_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b050_e080.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e080_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b050_e070.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e070_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b050_e060.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e060_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
      if(electronTightColl_NPFisodr03_b050_e125.size()==1 ) FillHist("Tight_iso_NPFisodr3_b050_e125_pt_eta", el_pt, el_eta, weight,  ptbins, 8, ebetabins, 2);
    
    }
  }
  
  /// Gets Fake rates for events with away jet > 20/40/60 GeV 
  if(useevent20&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto20,  jetColl, "20");
  if(useevent40&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto40,  jetColl, "40");
  if(useevent60&&truth_match)   GetFakeRates(electronLooseColl, electronTightColl, jetColl_lepveto60,  jetColl, "60");

  
  
  return;
}// End of execute event loop



void FakeRateCalculator_El::GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets,  std::vector<snu::KJet>  alljets, TString tag){

  Float_t ptbins[9] = { 10.,15.,20.,25.,30.,35.,40.,60.,100.};
  Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
  Float_t htbins[5] = { 0., 30., 50., 100., 200.};

  std::vector<snu::KMuon> muons;
  if( tight_el.size() == 1 && jets.size() >= 1){
    float el_pt = tight_el.at(0).Pt();
    FillHist(("TightEl" + tag + "_eta").Data(), tight_el.at(0).Eta(), weight, -2.5, 2.5,50);
    FillHist(("TightEl" + tag + "_pt").Data(),el_pt, weight,  ptbins, 8);
    FillHist(("TightEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("TightEl" + tag + "_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
    FillHist(("TightEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 4);
    if(fabs( tight_el.at(0).Eta() < 0.8)) FillHist(("TightEl" + tag + "_pt_eta1").Data(),el_pt, weight, ptbins, 8);
    else if(fabs( tight_el.at(0).Eta() < 1.479))FillHist(("TightEl" + tag + "_pt_eta2").Data(),el_pt, weight, ptbins, 8);
    else if(fabs( tight_el.at(0).Eta() < 2.)) FillHist(("TightEl" + tag + "_pt_eta3").Data(),el_pt, weight, ptbins, 8);
    else if(fabs( tight_el.at(0).Eta() < 2.5))FillHist(("TightEl" + tag + "_pt_eta4").Data(),el_pt, weight, ptbins, 8);

    FillCLHist(sighist, ("TightEl" + tag + "").Data(), eventbase->GetEvent(), muons,tight_el,jets, weight);


    bool awaybjet=false;
    bool closebjet=false;
    bool closenoejet=false;
    bool closephjet=false;
    /// plot FR if away jet is btagged
    for(unsigned int ijet =0 ; ijet < alljets.size() ; ijet++){
      for(unsigned int iel=0 ; iel < tight_el.size() ; iel++){

	float dphi =TVector2::Phi_mpi_pi(tight_el.at(iel).Phi()- alljets.at(ijet).Phi());

	if( dphi > 2.5){
	  if(alljets.at(ijet).BtagProb() > 0.679) awaybjet=true;
	}
	if( dphi < 0.4){
	  if(alljets.at(ijet).BtagProb() > 0.679) closebjet=true;
	}

	if( tight_el[iel].DeltaR(alljets.at(ijet)) < 0.4){
	  if(alljets.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	  if(alljets.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	}
      }
    }
    if(awaybjet)FillHist(("TightEl" + tag + "_awaybjet_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
    if(closebjet)FillHist(("TightEl" + tag + "_closebjet_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
    if(closenoejet) FillHist(("TightEl" + tag + "_closejet_noe_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
    if(closephjet) FillHist(("TightEl" + tag + "_closejet_ph_eta_binned").Data(),fabs(tight_el.at(0).Eta()), weight, etabins, 4);
}


  if(jets.size() >= 1){
    float el_pt = loose_el.at(0).Pt();
    FillHist(("LooseEl" + tag + "_eta").Data(), loose_el.at(0).Eta(), weight, -2.5, 2.5,50);
    FillHist(("LooseEl" + tag + "_pt").Data(), el_pt, weight,  ptbins, 8);
    FillHist(("LooseEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("LooseEl" + tag + "_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);
    FillHist(("LooseEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 4);
    if(fabs( loose_el.at(0).Eta() < 0.8)) FillHist(("LooseEl" + tag + "_pt_eta1").Data(), el_pt, weight, ptbins, 8);
    else if(fabs( loose_el.at(0).Eta() < 1.479))FillHist(("LooseEl" + tag + "_pt_eta2").Data(), el_pt, weight, ptbins, 8);
    else if(fabs( loose_el.at(0).Eta() < 2.)) FillHist(("LooseEl" + tag + "_pt_eta3").Data(), el_pt, weight, ptbins, 8);
    else if(fabs( loose_el.at(0).Eta() < 2.5))FillHist(("LooseEl" + tag + "_pt_eta4").Data(), el_pt, weight, ptbins, 8);

    FillCLHist(sighist, ("LooseEl" + tag + "").Data(), eventbase->GetEvent(), muons,loose_el,jets, weight);


    bool awaybjet=false;
    bool closebjet=false;
    bool closenoejet=false;
    bool closephjet=false;
    /// plot FR if away jet is btagged
    for(unsigned int ijet =0 ; ijet < alljets.size() ; ijet++){
      for(unsigned int iel=0 ; iel < loose_el.size() ; iel++){

	float dphi =TVector2::Phi_mpi_pi(loose_el.at(iel).Phi()- alljets.at(ijet).Phi());
	if( dphi > 2.5){
	  if(alljets.at(ijet).BtagProb() > 0.679) awaybjet=true;
	}
	if( dphi < 0.4){
	  if(alljets.at(ijet).BtagProb() > 0.679) closebjet=true;
	}

	if( loose_el[iel].DeltaR(alljets.at(ijet)) < 0.4){
	  if(alljets.at(ijet).NeutralEMEnergyFraction() > 0.2) closephjet=true ;
	  if(alljets.at(ijet).ChargedEMEnergyFraction() < 0.2) closenoejet=true ;
	}
      }
    }
    if(awaybjet)FillHist(("LooseEl" + tag + "_awaybjet_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);
    if(closebjet)FillHist(("LooseEl" + tag + "_closebjet_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);
    if(closenoejet) FillHist(("LooseEl" + tag + "_closejet_noe_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);
    if(closephjet) FillHist(("LooseEl" + tag + "_closejet_ph_eta_binned").Data(),fabs(loose_el.at(0).Eta()), weight, etabins, 4);

  }
  return;
}



void FakeRateCalculator_El::GetRealEfficiency(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, std::vector<snu::KMuon> muons, double w, float interval,TString tag, double dxycut,  double  barreliso, double endcapiso, bool dr3, bool usetrkiso, bool usetight){
  
  Float_t ptbins[18] = {10.,12.5,15.,17.5, 20.,25.,30.,35.,40.,45.,50.,60., 70., 80., 100., 125., 150., 200.};
  Float_t etabins[5] = { 0., 0.8, 1.479, 2., 2.5};
  
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

        if(electrons.at(0).IsEBFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_barrel_pt").Data(), electrons.at(0).Pt(), w,ptbins,17);
        }
        else if(electrons.at(0).IsEEFiducial()){
          FillHist(("h_promptrate_" + tag +"_denom_endcap_pt").Data(), electrons.at(0).Pt(), w,ptbins,17);
        }

        //// Electron 1 is probe
        if(IsTight(electrons.at(0), eventbase->GetEvent().JetRho(), dxycut, barreliso, endcapiso,dr3, usetrkiso, usetight)){
          FillHist(("h_promptrate_" + tag +"_num_pt").Data(), electrons.at(0).Pt(), w, ptbins,17);
          FillHist(("h_promptrate_"+ tag+"_num_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 50.,50);
          FillHist(("h_promptrate_" + tag +"_num_eta").Data(), electrons.at(0).Eta(), w, -2.5, 2.5,50);
          FillHist(("h_promptrate_" + tag +"_num_njets").Data(), jets.size(), w, 0., 5.,5);
	  FillHist(("h_promptrate_" + tag +"_num_pt_eta").Data(), electrons.at(0).Pt(), electrons.at(0).Eta(), w, ptbins,17, etabins, 4);

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



