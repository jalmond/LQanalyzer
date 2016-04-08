// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQExampleAnalyzerDiElectron Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ExampleAnalyzerDiElectron.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ExampleAnalyzerDiElectron);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ExampleAnalyzerDiElectron::ExampleAnalyzerDiElectron() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("ExampleAnalyzerDiElectron");

  Message("In ExampleAnalyzerDiElectron constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void ExampleAnalyzerDiElectron::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist
   MakeCleverHistograms(sighist, "DiElectron");
   MakeCleverHistograms(sighist, "DiElectronWPURW");
   MakeCleverHistograms(sighist, "DiElectronWPURWID");
   MakeCleverHistograms(sighist, "DiElectronWPURWID_METGT45");

   MakeCleverHistograms(sighist, "DiElectron1bjet");
   MakeCleverHistograms(sighist, "DiElectron2bjet");
   MakeCleverHistograms(sighist, "DiElectronSameSign");
   
  
   n_0=0;
   n_1=0;
   n_2=0;
   n_3=0;
   n_4=0;
   n_5=0;
   n_6a=0;
   n_6b=0;
   n_6c=0;
   n_6d=0;
   n_7=0;
   return;
}


void ExampleAnalyzerDiElectron::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  n_0++;
  /// FillCutFlow(cut, weight) fills a basic TH1 called cutflow. It is used to check number of events passing different cuts
  /// The string cut must match a bin label in FillCutFlow function
  FillCutFlow("NoCut", weight);
  
  ///// Apply some general cuts on event to clean MET
  /// Taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
  /// These are applied in AnalyzerCore::PassBasicEventCuts
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  FillCutFlow("EventCut", weight);
  
  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex
  FillCutFlow("VertexCut", weight);
  
  n_1++;
  
  float pileup_reweight (1.);
  if (!k_isdata) {
    //    pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }
  
  std::vector<snu::KElectron> electronColl;
  eventbase->GetElectronSel()->SetEta(2.5);
  eventbase->GetElectronSel()->SetPt(20.);
  eventbase->GetElectronSel()->Selection(electronColl);
  
  std::vector<snu::KElectron> electronTightColl;
  bool has_conv=false;
  for(std::vector<snu::KElectron>::iterator el =electronColl.begin(); el!=electronColl.end(); el++){
    if(el->Pt() < 30.) continue;
    
    if(!(fabs(el->PrimaryVertexDXY())< 0.02 )) continue;
    if(el->HasMatchedConvPhot() ) has_conv=true;
    if((el->TrigMVA()< 0.5)) continue;
    if (el->MissingHits() != 0)  has_conv=true;

    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid=0;
    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;
    double rho =  eventbase->GetEvent().JetRho();
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
    float LeptonRelIsoDR03= 999.;;
    if(el->Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();
    
    if(!(LeptonRelIsoDR03 <  0.1)) continue;
    
    
    electronTightColl.push_back(*el);
  }

  std::vector<snu::KJet> jetColl;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);


  if(electronTightColl.size() != 1) return;
  FillCutFlow("Electron", weight);
  n_2++;

  std::vector<snu::KMuon> muonColl = eventbase->GetMuons(); 

  std::vector<snu::KMuon> vetomuons;

  for (std::vector<snu::KMuon>::iterator muit = muonColl.begin(); muit!=muonColl.end(); muit++){
    float LeptonRelIso = (muit->SumIsoCHDR04() + std::max(0.0, muit->SumIsoNHDR04() + muit->SumIsoPHDR04() - 0.5* muit->SumPUIsoR04()) )/muit->Pt() ;
    if(LeptonRelIso > 0.2) continue;
    if(muit->Pt() < 10.) continue;
    if(fabs(muit->Eta()) > 2.5) continue; 
    if(!(muit->IsPF() == 1)) continue;
    if(!(muit->IsGlobal()==1 || muit->IsTracker() == 1 ))  continue;
    vetomuons.push_back(*muit);
  }
  
  if(vetomuons.size() > 0) return;
  FillCutFlow("VetoMuon", weight);

  
  n_3++;
  std::vector<snu::KElectron> vetoelectron;
  for(std::vector<snu::KElectron>::iterator el =electronColl.begin(); el!=electronColl.end(); el++){
    if(!(el->TrigMVA()> 0.5))continue;

    Double_t PHONH_03[7]          = {0.13, 0.14, 0.07, 0.09, 0.11, 0.11, 0.14};
    int ifid;
    if (fabs(el->SCEta()) < 1.0) ifid = 0;
    else if (fabs(el->SCEta()) < 1.479) ifid = 1;
    else if (fabs(el->SCEta()) < 2.0) ifid = 2;
    else if (fabs(el->SCEta()) < 2.2) ifid = 3;
    else if (fabs(el->SCEta()) < 2.3) ifid = 4;
    else if (fabs(el->SCEta()) < 2.4) ifid = 5;
    else ifid = 6;
    double rho =  eventbase->GetEvent().JetRho();
    float ElectronIsoDR03 =  el->PFChargedHadronIso03() + max( el->PFNeutralHadronIso03() + el->PFPhotonIso03() - rho * PHONH_03[ifid],  0.);
    float LeptonRelIsoDR03=100000.;
    if(el->Pt() > 0.)  LeptonRelIsoDR03 = ElectronIsoDR03/  el->Pt();

    if(!(LeptonRelIsoDR03 <  0.15)) continue;
    
    vetoelectron.push_back(*el);
  }
  if(vetoelectron.size() > 1) return;
  FillCutFlow("VetoElectron", weight);

  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl, vetomuons, vetoelectron );

  n_4++;

  if(has_conv) return;

  n_5++;

  if(jetColl.size() ==  0) return;
  if(jetColl.at(0).Pt() < 55.)  return;
  n_6a++;
  
  if(jetColl.size() ==  1) return;
  if(jetColl.at(1).Pt() < 45.)  return;
  n_6b++;

  if(jetColl.size() ==  2) return;
  if(jetColl.at(2).Pt() < 35.)  return;
  n_6c++;

  if(jetColl.size() ==  3) return;
  if(jetColl.at(3).Pt() < 20.)  return;
  n_6d++;

  if(NBJet(jetColl) == 0) return;
  n_7++;
  

  return;

}// End of execute event loop
  


void ExampleAnalyzerDiElectron::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;


  m_logger << INFO << "Number of events processed " << n_0 <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 0= " << n_1 <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 1== " << n_2 <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 2== " << n_3 <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 3== " << n_4 <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 4== " << n_5 <<  LQLogger::endmsg;

  m_logger << INFO << "Number of events step 5a== " << n_6a <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 5b== " << n_6b <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 5c== " << n_6c <<  LQLogger::endmsg;
  m_logger << INFO << "Number of events step 5d== " << n_6d <<  LQLogger::endmsg;

  m_logger << INFO << "Number of events step 6== " << n_7 <<  LQLogger::endmsg;


}


void ExampleAnalyzerDiElectron::BeginCycle() throw( LQError ){
  
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

  
  return;
  
}

ExampleAnalyzerDiElectron::~ExampleAnalyzerDiElectron() {
  
  Message("In ExampleAnalyzerDiElectron Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ExampleAnalyzerDiElectron::FillCutFlow(TString cut, float weight){

  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
   
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 5,0.,5.);

    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"DiEl_tight");
   
    
  }
}


void ExampleAnalyzerDiElectron::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ExampleAnalyzerDiElectron::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ExampleAnalyzerDiElectronCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ExampleAnalyzerDiElectron::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



