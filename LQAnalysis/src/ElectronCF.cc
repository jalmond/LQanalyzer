// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQElectronCF Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
#include "ElectronCF.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (ElectronCF);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
ElectronCF::ElectronCF() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("ElectronCF");

  Message("In ElectronCF constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void ElectronCF::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  return;
}


void ElectronCF::ExecuteEvents()throw( LQError ){
  

  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  if (MC_pu&&!k_isdata) {
    weight  = weight* reweightPU->GetWeight(int(eventbase->GetEvent().PileUpInteractionsTrue()))* MCweight;
  }

  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
  if(!PassTrigger(triggerslist, prescale)) return;
  
  
  //////////////////////////////////////////////////////
  //////////// Select objetcs
  //////////////////////////////////////////////////////   

  std::vector<snu::KElectron> _electronTightColl;
  eventbase->GetElectronSel()->HNTightElectronSelection(_electronTightColl);
  
  std::vector<snu::KElectron> electronTightColl =  GetTruePrompt(_electronTightColl);
  if(electronTightColl.size()!=2) return;
  
  std::vector<snu::KMuon> muonTightColl;
  eventbase->GetMuonSel()->HNTightMuonSelection(muonTightColl);
  
  std::vector<snu::KJet> jetColl_lepveto;
  eventbase->GetJetSel()->SetID(BaseSelection::PFJET_LOOSE);
  eventbase->GetJetSel()->SetEta(2.5);
  eventbase->GetJetSel()->SetPt(20.);
  eventbase->GetJetSel()->JetSelectionLeptonVeto(jetColl_lepveto, muonTightColl, electronTightColl);
  
  
  bool el1_barr = (fabs(electronTightColl.at(0).Eta()) < 1.47);
  bool el2_barr = (fabs(electronTightColl.at(1).Eta()) < 1.47);

  if(el1_barr&&el2_barr) {
    if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge())   FillHist("BarrBarr_ss", 1, weight, 0, 1., 1);
    else FillHist("BarrBarr_os", 1, weight, 0, 1., 1);
  }

  if( (el1_barr&&!el2_barr) || (!el1_barr&&el2_barr)) {
    if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge())   FillHist("BarrEnd_ss", 1, weight, 0, 1., 1);
    else FillHist("BarrEnd_os", 1, weight, 0, 1., 1);
  }
  if(el1_barr&&!el2_barr) {
    if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge())   FillHist("EndEnd_ss", 1, weight, 0, 1., 1);
    else FillHist("EndEnd_os", 1, weight, 0, 1., 1);
  }

  
  Float_t ptbins[7] = { 20.,30.,40.,50.,60.,80.,200.};
 
  
  for(int iel = 0 ; iel < electronTightColl.size(); iel++){
    FillHist("CFDenominatort", 1  , weight, 0.,1.,1);
    FillHist("CFDenominator_pt", electronTightColl.at(iel).Pt()  , weight, 0.,500.,100);
    FillHist("CFDenominator_eta", electronTightColl.at(iel).Eta()  , weight, -3.,3.,60);
    
    if(electronTightColl.at(iel).Eta() < -1.6)    FillHist("CFDenominator_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    else if(electronTightColl.at(iel).Eta() < -1.)    FillHist("CFDenominator_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    else if(electronTightColl.at(iel).Eta() < 0.)    FillHist("CFDenominator_pt_eta3", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    else if(electronTightColl.at(iel).Eta() < 1.)    FillHist("CFDenominator_pt_eta4", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    else if(electronTightColl.at(iel).Eta() < 1.6)    FillHist("CFDenominator_pt_eta5", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    else if(electronTightColl.at(iel).Eta() < 2.5)    FillHist("CFDenominator_pt_eta6", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    
    
    if(electronTightColl.at(iel).GetType() == 6) {
      FillHist("CFNumerator", 1  , weight, 0.,1.,1);
      FillHist("CFNumerator_pt", electronTightColl.at(iel).Pt()  , weight, 0.,500.,100);
      FillHist("CFNumerator_eta", electronTightColl.at(iel).Eta()  , weight, -3.,3.,60);
      
      if(electronTightColl.at(iel).Eta() < -1.6)    FillHist("CFNumerator_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
      else if(electronTightColl.at(iel).Eta() < -1.)    FillHist("CFNumerator_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
      else if(electronTightColl.at(iel).Eta() < 0.)    FillHist("CFNumerator_pt_eta3", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
      else if(electronTightColl.at(iel).Eta() < 1.)    FillHist("CFNumerator_pt_eta4", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
      else if(electronTightColl.at(iel).Eta() < 1.6)    FillHist("CFNumerator_pt_eta5", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
      else if(electronTightColl.at(iel).Eta() < 2.5)    FillHist("CFNumerator_pt_eta6", electronTightColl.at(iel).Pt()  , weight, ptbins, 6);
    }    
  }

  if(electronTightColl.at(0).Charge() == electronTightColl.at(1).Charge()){
    cout << "\n -----------" << endl;
    cout << electronTightColl.at(0).GetType() << "   " << electronTightColl.at(1).GetType()   << endl;
  }
  
  
  return;
}// End of execute event loop



void ElectronCF::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
}



void ElectronCF::BeginCycle() throw( LQError ){
  
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

ElectronCF::~ElectronCF() {
  
  Message("In ElectronCF Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}


void ElectronCF::FillCutFlow(TString cut, float weight){

  
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


void ElectronCF::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void ElectronCF::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this ElectronCFCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void ElectronCF::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



