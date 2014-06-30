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
  
  if(eventbase->GetEvent().EventNumber() == 28681993) cout << "JOHN : " << eventbase->GetEvent().LumiSection()  << endl;
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
  
  std::vector<snu::KMuon> muonVetoColl;
  eventbase->GetMuonSel()->HNVetoMuonSelection(muonVetoColl);

  std::vector<snu::KElectron> electronVetoColl;
  eventbase->GetElectronSel()->HNVetoElectronSelection(electronVetoColl);

  if(electronVetoColl.size() !=2) return;
  if(muonVetoColl.size() != 0) return;
  

 if(SameCharge(_electronTightColl)){
    int e1_type = _electronTightColl.at(0).GetType();
    int e2_type = _electronTightColl.at(1).GetType();
    if(!( e1_type == 1 || e1_type == 2 || e1_type == 3 || e1_type == 6 )
       && !( e2_type == 1 || e2_type == 2 || e2_type == 3 || e2_type == 6 ) )  FillHist("ss", 1, 1, 0, 1., 1);
  }

 
 if(_electronTightColl.size() ==2){
    
   std::vector<snu::KTruth> truthColl;
   eventbase->GetTruthSel()->Selection(truthColl);
    
    float eta1 =  _electronTightColl.at(0).Eta();
    float phi1 =  _electronTightColl.at(0).Phi();
    float eta2 =  _electronTightColl.at(1).Eta();
    float phi2 =  _electronTightColl.at(1).Phi();
    
    cout << "[Reco] Electron1 pt/eta/phi/charge = " << _electronTightColl.at(0).Pt() << " " << _electronTightColl.at(0).Eta() << " " << _electronTightColl.at(0).Phi() << " " << _electronTightColl.at(0).Charge() << endl;
    cout << "[Reco] Electron2 pt/eta/phi/charge = " << _electronTightColl.at(1).Pt() << " " << _electronTightColl.at(1).Eta() << " " << _electronTightColl.at(1).Phi() << " " << _electronTightColl.at(1).Charge() << endl;
    for(int i=0; i < eventbase->GetElectrons().size();i++){
      cout << "[nocut] Electron pt/eta/phi/charge = " << eventbase->GetElectrons().at(i).Pt() << " " <<  eventbase->GetElectrons().at(i).Eta() << " " << eventbase->GetElectrons().at(i).Phi() << " " << eventbase->GetElectrons().at(i).Charge() << endl;
    }
    

    cout << "\n --------" << endl;
    for(unsigned int g =0; g < truthColl.size(); g++){
      if(truthColl.at(g).PdgId() != 2212){
	double dr1 = sqrt( pow(fabs( eta1 - truthColl.at(g).Eta()),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( phi1 -truthColl.at(g).Phi())),2.0));
	double dr2 = sqrt( pow(fabs( eta2 - truthColl.at(g).Eta()),2.0) +  pow( fabs(TVector2::Phi_mpi_pi( phi2 -truthColl.at(g).Phi())),2.0));
	if(dr1 < 0.4){
	  m_logger << INFO << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID/NDaughters/TauDecay = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta() << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << "/" << truthColl.at(truthColl.at(g).IndexMother()).PdgId() << "/" <<  truthColl.at(g).NDaughter() << "/" << truthColl.at(g).TauDecayMode() << " Matched to el1" <<  LQLogger::endmsg; 
	}
	else 	if(dr2 < 0.4){
	  m_logger << INFO << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID/NDaughters/TauDecay = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta() << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << "/" << truthColl.at(truthColl.at(g).IndexMother()).PdgId() << "/" <<  truthColl.at(g).NDaughter() << "/" << truthColl.at(g).TauDecayMode() << " Matched to el2" <<  LQLogger::endmsg;
	}
	else {
	  m_logger << INFO << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID/NDaughters/TauDecay = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta() << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << "/" << truthColl.at(truthColl.at(g).IndexMother()).PdgId() << "/" <<  truthColl.at(g).NDaughter() << "/" << truthColl.at(g).TauDecayMode()  <<  LQLogger::endmsg;
	}
      }
    }
  }
  

  /*
  if(SameCharge(_electronTightColl)){
    cout << "SS DY event" << endl;
    cout << "Electron 1 type = " << _electronTightColl.at(0).GetType() << endl;
    cout << "Electron 2 type = " << _electronTightColl.at(1).GetType() << endl;
    snu::KParticle Z = _electronTightColl.at(0) + _electronTightColl.at(1);
    if(_electronTightColl.at(0).GetType() != 6 ){
      if(_electronTightColl.at(0).GetType() != 1 ){
	
	cout << "ENumber = " << eventbase->GetEvent().EventNumber() << endl;
	cout << "El pt/eta/phi/charge" << endl;
	cout <<  _electronTightColl.at(0).Pt() << " " <<  _electronTightColl.at(0).Eta() << " " << _electronTightColl.at(0).Phi() << " " <<  _electronTightColl.at(0).Charge()  << endl;
	cout << "Mass = " << Z.M() << endl;
	std::vector<snu::KTruth> truthColl;
	eventbase->GetTruthSel()->Selection(truthColl);
	
	for(unsigned int e=0; e < eventbase->GetElectrons().size(); e++){
	  cout << "Electron [ " << e+1 << "]  pt = " << eventbase->GetElectrons().at(e).Pt() << " eta= " <<  eventbase->GetElectrons().at(e).Eta() << " phi= " <<  eventbase->GetElectrons().at(e).Phi() << endl;
	}
	
	for(unsigned int g =0; g < truthColl.size(); g++){
	  m_logger << INFO << "Truth Matched to electron[GenParticle]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta() << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << LQLogger::endmsg;
	  
	}
      }
    }
    
    if(_electronTightColl.at(1).GetType() != 6 ){
      if(_electronTightColl.at(1).GetType() != 1 ){
	cout << "ENumber = " << eventbase->GetEvent().EventNumber() << endl;
	cout << "El pt/eta/phi/charge" << endl;
        cout <<  _electronTightColl.at(1).Pt() << " " <<  _electronTightColl.at(1).Eta() << " " << _electronTightColl.at(1).Phi() << " " << _electronTightColl.at(1).Charge() << endl;
	cout << "Mass = " << Z.M() << endl;
	std::vector<snu::KTruth> truthColl;
	eventbase->GetTruthSel()->Selection(truthColl);
	
	for(unsigned int e=0; e < eventbase->GetElectrons().size(); e++){
          cout << "Electron [ " << e+1 << "]  pt = " << eventbase->GetElectrons().at(e).Pt() << " eta= " <<  eventbase->GetElectrons().at(e).Eta() << " phi= " <<  eventbase->GetElectrons().at(e).Phi() << endl;
        }
	for(unsigned int g =0; g < truthColl.size(); g++){
	  
	  m_logger << INFO << "Truth Matched to electron[GenParticle]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta( \
) << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << LQLogger::endmsg;

	}
      }
      
    }
    
    if(_electronTightColl.at(0).GetType() ==  _electronTightColl.at(1).GetType()){
      cout << "ENumber = " << eventbase->GetEvent().EventNumber() << endl; 
      
      std::vector<snu::KTruth> truthColl;
      eventbase->GetTruthSel()->Selection(truthColl);
      
      cout << _electronTightColl.at(0).Pt() << " " << _electronTightColl.at(0).Eta() << " " << _electronTightColl.at(0).Phi() << endl;
      cout <<  _electronTightColl.at(0).Pt() << " "<< _electronTightColl.at(1).Eta() << " " << _electronTightColl.at(1).Phi() << endl;
      for(unsigned int g =0; g < truthColl.size(); g++){
	
	m_logger << INFO << "Truth Matched to electron[GenParticle]"  << "Pt/Eta/Phi/Status/PDGID/MOTHER PDGID = " << truthColl.at(g).Pt() << "/" << truthColl.at(g).Eta() << "/" << truthColl.at(g).Phi() << "/" <<  truthColl.at(g).GenStatus() << "/" << truthColl.at(g).PdgId() << LQLogger::endmsg;
	
      }
    }
  }
    
    if(_electronTightColl.size() ==2){
      Z_el_denom +=2;
      if(_electronTightColl.at(0).GetType() == 6) {
	Z_el_num +=1;
	cout << "TYPE 6 " << endl;
	}
	if(_electronTightColl.at(1).GetType() == 6) Z_el_num +=1;
	}
  
  */
  
  std::vector<snu::KElectron> electronTightColl =  GetTruePrompt(_electronTightColl);

  
  if(SameCharge(electronTightColl)){
    FillHist("ss2", 1, 1., 0, 1., 1);
  }


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

  
  if(SameCharge(electronTightColl)){
    snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
    
    FillHist("SS_Z", Z.M(), weight, 0, 150., 15);
    
  }
  if (electronTightColl.size()==2){
    if(electronTightColl.at(0).Charge() != electronTightColl.at(1).Charge() ){
      snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
      float cfweight = weight*( (CFRate(electronTightColl.at(0)) /(1-CFRate(electronTightColl.at(0)))) + (CFRate(electronTightColl.at(1)) / (1-CFRate(electronTightColl.at(1)))));
      FillHist("OS_Z", Z.M(), cfweight, 0, 150., 15);
      
    }
  }
  
  
  Float_t ptbins[6] = { 15.,20.,40.,60.,80.,200.};

  int cf_event=0;
  for(int iel = 0 ; iel < electronTightColl.size(); iel++){
    //if(electronTightColl.at(iel).Pt() < 20.) return;
    
    FillHist("CFDenominator", 1  , weight, 0.,1.,1);
    FillHist("CFDenominator_pt", electronTightColl.at(iel).Pt()  , weight, 0.,500.,100);
    FillHist("CFDenominator_eta", electronTightColl.at(iel).Eta()  , weight, -3.,3.,60);
    FillHist("CFDenominator_njet", jetColl_lepveto.size()  , weight, 0.,4.,4);
    
    if(fabs(electronTightColl.at(iel).Eta()) < 1.5)    FillHist("CFDenominator_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
    else    FillHist("CFDenominator_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
    
    snu::KParticle Z = electronTightColl.at(0) + electronTightColl.at(1);
    
    if(fabs(90. -Z.M()) < 10.){
      if(fabs(electronTightColl.at(iel).Eta()) < 1.5)    FillHist("CFDenominator_Zpeak_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
      else    FillHist("CFDenominator_Zpeak_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
    }
    
    
    if(electronTightColl.at(iel).GetType() == 4 || electronTightColl.at(iel).GetType() == 5) {
      cf_event++;
      if(cf_event > 1) cout << "2 CF in 1 event " << eventbase->GetEvent().EventNumber()<< endl;
      if(!SameCharge(electronTightColl)) cout << "Opposite sign event has chargeflip ? "<< eventbase->GetEvent().EventNumber()<< endl;
  
      FillHist("CFNumerator", 1  , weight, 0.,1.,1);
      FillHist("CFNumerator_pt", electronTightColl.at(iel).Pt()  , weight, 0.,500.,100);
      FillHist("CFNumerator_eta", electronTightColl.at(iel).Eta()  , weight, -3.,3.,60);
      FillHist("CFNumerator_njet", jetColl_lepveto.size()  , weight, 0.,4.,4);
      
      
      if(fabs(electronTightColl.at(iel).Eta()) < 1.5)    FillHist("CFNumerator_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
      else    FillHist("CFNumerator_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
      
      if(fabs(90. -Z.M())< 10.){
	if(fabs(electronTightColl.at(iel).Eta()) < 1.5)    FillHist("CFNumerator_Zpeak_pt_eta1", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
	else    FillHist("CFNumerator_Zpeak_pt_eta2", electronTightColl.at(iel).Pt()  , weight, ptbins, 5);
      }

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
  
  cout << "number of electrons in Z peak = " << Z_el_denom << endl;
  cout << "number of CF electrons= " << Z_el_num << endl;
  cout << "CF = " << Z_el_num/Z_el_denom << endl;
}



void ElectronCF::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "MyDataPileupHistogram.root").c_str());

  Z_el_denom=0;
  Z_el_num=0;
  
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


void ElectronCF::FillCutFlow(int cut, float w, TString tag){

  
  if(GetHist(("cutflow_" + tag).Data())) {
    
    if(cut ==0)  GetHist(("cutflow_" + tag).Data())->Fill("notfake",w);
    if(cut ==1)  GetHist(("cutflow_" + tag).Data())->Fill("jet",w);
    if(cut ==2)  GetHist(("cutflow_" + tag).Data())->Fill("cjet",w);
    if(cut ==3)  GetHist(("cutflow_" + tag).Data())->Fill("bjet",w);
    if(cut ==4)  GetHist(("cutflow_" + tag).Data())->Fill("chargemisid",w);
    if(cut ==5)  GetHist(("cutflow_" + tag).Data())->Fill("chargemisid_photonconv",w);
    if(cut ==6)  GetHist(("cutflow_" + tag).Data())->Fill("photonfake",w);
    if(cut ==7) GetHist(("cutflow_" + tag).Data())->Fill("nonfake_photonconv",w);
    if(cut ==8)  GetHist(("cutflow_" + tag).Data())->Fill("NOPARTICLE",w);
    if(cut ==9)  GetHist(("cutflow_" + tag).Data())->Fill("unknown",w);
    
    
  }
  else{
    AnalyzerCore::MakeHistograms((("cutflow_" + tag).Data()),10,0.,10.);
    
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(1,"notfake");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(2,"jet");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(3,"cjet");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(4,"bjet");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(5,"chargemisid");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(6,"chargemisid_photonconv");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(7,"photonfake");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(8,"nonfake_photonconv");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(9,"NOPARTICLE");
    GetHist(("cutflow_" + tag).Data())->GetXaxis()->SetBinLabel(10,"unknown");
    
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



