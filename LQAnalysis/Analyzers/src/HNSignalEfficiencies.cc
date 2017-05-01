// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNSignalEfficiencies Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNSignalEfficiencies.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNSignalEfficiencies);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNSignalEfficiencies::HNSignalEfficiencies() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNSignalEfficiencies");

  Message("In HNSignalEfficiencies constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

}


void HNSignalEfficiencies::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist


   vector<TString> labels;
   labels.push_back("hn"); 
   //labels.push_back("medium");   // pog numbers
   labels.push_back("tight");    // pog numbers 
   
   for(unsigned int il = 0; il < labels.size(); il++){
     TString label = labels.at(il);
     continue;
     MakeCleverHistograms(sighist_ee,label + "_SSee_1jet");
     MakeCleverHistograms(sighist_ee,label + "_SSee_DiJet");
     MakeCleverHistograms(sighist_ee,label + "_SSPreselection");
     MakeCleverHistograms(sighist_ee,label + "_OSee_1jet");
     MakeCleverHistograms(sighist_ee,label + "_OSee_DiJet");
     MakeCleverHistograms(sighist_ee,label + "_OSPreselection");
     MakeCleverHistograms(sighist_ee,label + "_LowMass");
     MakeCleverHistograms(sighist_ee,label + "_MediumMass");
     MakeCleverHistograms(sighist_ee,label + "_HighMass");
     MakeCleverHistograms(sighist_ee,label + "_LowMassCR");
     MakeCleverHistograms(sighist_ee,label + "_MediumMassCR");
     MakeCleverHistograms(sighist_ee,label + "_HighMassCR");
   }
   
   

   /// Validation signalplots
   /*
   MakeCleverHistograms(sighist_ee, "SIGNALVALIDATION_EE" );
   MakeCleverHistograms(sighist_mm, "SIGNALVALIDATION_MM" );
   */

   return;
}


void HNSignalEfficiencies::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  TruthPrintOut();
  return;
  
  
  counter("All",1.);
  //if(FailHNDataSetCheck()) return;

  if(!isData){
    weight*= MCweight;
    weight*=WeightByTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", TargetLumi);
  }
  
  vector<TString> ElTriggers = GetHNDiLepElTriggers();

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; 

  counter("Vertex",1.);


  TString eltag = "ELECTRON_NOCUT"; 
  if(isData)eltag = "ELECTRON_HN_HIGHDXY_FAKELOOSE";

  TString mutag = "MUON_NOCUT";
  if(isData)mutag="MUON_HN_TRI_HIGHDXY_LOOSE";

  std::vector<snu::KElectron> electrons_nc=GetElectrons(eltag);
  std::vector<snu::KMuon> muons_nc=GetMuons(mutag);
  
  std::vector<snu::KElectron> electrons_tm_nc=GetElectrons(false,false,"ELECTRON_NOCUT");
  std::vector<snu::KMuon> muons_tm_nc=GetMuons("MUON_NOCUT",false);

  for(unsigned int i=0; i < electrons_nc.size(); i++){
    //  cout << "el " << i+1 << electrons_nc[i].Pt() << " " << electrons_nc[i].Eta() << " " << electrons_nc[i].Phi() << " " << electrons_nc[i].MCMatched() << endl;
  }
  
  if(electrons_tm_nc.size() >=2)counter("NCDiEl",1.);


  //for(unsigned int i=0;i < muons_nc.size(); i++){
  //cout << "mu " << i+1 << muons_nc[i].Pt() << " " << muons_nc[i].Eta() << " " << muons_nc[i].Phi() << " " << muons_nc[i].MCMatched() << endl;
  //}

  TruthPrintOut();

  
  std::vector<snu::KJet> jets_nc = GetJets("JET_HN");  
  GetTriggEfficiency();

  std::vector<snu::KElectron>  hn_electrons=GetElectrons(false,false,"ELECTRON_HN_TIGHT");
  std::vector<snu::KElectron>  pog_electrons=GetElectrons(false,false,"ELECTRON_POG_TIGHT");

  std::vector<snu::KMuon>  hn_muons=GetMuons("MUON_HN_TIGHT",false);
  std::vector<snu::KMuon>  pog_muons=GetMuons("MUON_POG_TIGHT",false);


  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");
  std::vector<snu::KJet> jets = GetJets("JET_NOLEPTONVETO");
  std::vector<snu::KJet> hn04jets = GetJets("JET_HN");
  std::vector<snu::KJet> hnjets =  GetJetsWFT("JET_HN","FATJET_HN");
  


  FillCLHist(sighist_ee, "NoCut", eventbase->GetEvent(), muons_tm_nc,electrons_tm_nc,jets_nc, fatjetcoll,weight);
  
  

  if(hn_electrons.size() == 2){
    counter("DiEl",1.);
    if(SameCharge(hn_electrons))     counter("SSDiEl",1.);
    else counter("OSDiEl",1.);
  }
  else if(hn_electrons.size() == 3)  counter("TriEl",1.);
  else if(hn_electrons.size() == 1)  counter("SingleEl",1.);
  
  if(hn_muons.size() == 2){
    counter("DiMu",1.);
    if(SameCharge(hn_muons))     counter("SSDiMu",1.);
    else counter("OSDiMu",1.);
  }
  else if(hn_muons.size() == 3)  counter("TriMu",1.);
  else if(hn_muons.size() == 1)  counter("SingleMu",1.);

  
  int nmatched=0;
    
  for(unsigned int iel =0 ; iel < electrons_nc.size(); iel++){
    if(electrons_nc[iel].Pt() < 20.) continue;
    
      
    if((electrons_nc[iel].Eta()) < 1.5)FillHist("El_energy_b_reco", electrons_nc[iel].Energy(), weight,   0., 1000, 1000); 
    else  FillHist("El_energy_ec_reco", electrons_nc[iel].Energy(), weight,   0., 1000, 1000); 
    if(!isData)FillHist("El_energy_truth", GetTruthMatchedParticle(electrons_nc[iel]).E(), weight,   0., 1000, 1000);

    bool prompt = electrons_nc[iel].MCMatched();
    
    if(isData){
      prompt = PassID(electrons_nc[iel], "ELECTRON_HN_HIGHDXY_TIGHT");
    }
    
    if(prompt){
      nmatched++;
      FillHist("PromptElectron_iso_pt", electrons_nc[iel].Pt(),electrons_nc[iel].PFRelIso(0.3) ,weight,   0., 1000, 100, 0.,2., 200);
      FillHist("PromptElectron_pt", electrons_nc[iel].Pt() ,weight,  0., 1000, 1000);

      float massdrop=MassDrop(electrons_nc[iel], jets);
      float closejetpt= electrons_nc[iel].Pt()/ GetJetsCloseToLeptonPt(electrons_nc[iel], jets);
      float closejetrelpt= GetPtRelLepTJet(electrons_nc[iel], jets);
      
      if(electrons_nc[iel].Pt()> 50){
	FillHist("Prompt_massdrop", massdrop,  weight, 0., 1000, 1000);
	FillHist("Prompt_massdrop_ratio",closejetpt, massdrop,  weight, 0., 1000, 1000,  0., 2., 100);
	FillHist("Prompt_massdrop_rel",closejetrelpt, massdrop,  weight, 0., 1000, 1000,  0., 200, 200);
      }
      FillHist("Prompt_ratio" ,electrons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 2., 100);
      FillHist("Prompt_relpt" ,electrons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 200, 200); 

      if(electrons_nc[iel].PFRelIso(0.3) > 0.05){
	FillHist("NonIsoPromptElectron_pt", electrons_nc[iel].Pt() ,weight,  0., 1000, 1000);
	FillHist("NonIsoPrompt_massdrop", massdrop,  weight, 0., 1000, 1000);
	FillHist("NonIsoPrompt_massdrop_ratio",closejetpt, massdrop,  weight, 0., 1000, 1000,  0., 2., 100);
	FillHist("NonIsoPrompt_massdrop_rel",closejetrelpt, massdrop,  weight, 0., 1000, 1000,  0., 200, 200);
	FillHist("NonIsoPrompt_ratio_rel",closejetpt, closejetrelpt,  weight, 0., 2., 100,  0., 100, 100);
	
	if(closejetpt > 0.8 && closejetrelpt > 8){
	  FillHist("NonIsoFix1PromptElectron_pt", electrons_nc[iel].Pt() ,weight,  0., 1000, 1000);
	  FillHist("NonIsoFix1Prompt_massdrop", massdrop,  weight, 0., 1000, 1000);
	}
	if(massdrop > 10.){
	  FillHist("NonIsoFix2PromptElectron_pt", electrons_nc[iel].Pt() ,weight,  0., 1000, 1000);
	  FillHist("NonIsoFix2Prompt_ratio" ,electrons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 2., 100);
	  FillHist("NonIsoFix2Prompt_relpt" ,electrons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 200, 200);
	  FillHist("NonIsoFix2Prompt_ratio_rel",closejetpt, closejetrelpt,  weight, 0., 2., 100,  0., 100, 100);

	}
	FillHist("NonIsoPrompt_ratio" ,electrons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 2., 100);
	FillHist("NonIsoPrompt_relpt" ,electrons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 200, 200);
      }    
    }
    else{
      FillHist("NPromptElectron_iso_pt", electrons_nc[iel].Pt(),electrons_nc[iel].PFRelIso(0.3) ,weight,  0., 1000, 100, 0.,2., 200);
      FillHist("NPromptElectron_pt", electrons_nc[iel].Pt() ,weight,  0., 1000, 1000);

      float massdrop=MassDrop(electrons_nc[iel], jets);
      float closejetpt= electrons_nc[iel].Pt()/GetJetsCloseToLeptonPt(electrons_nc[iel], jets);
      float closejetrelpt= GetPtRelLepTJet(electrons_nc[iel], jets);
      FillHist("NPrompt_massdrop", massdrop,  weight, 0., 1000, 1000);
      FillHist("NPrompt_massdrop_ratio",closejetpt, massdrop,  weight, 0., 1000, 1000,  0., 2., 100);
      FillHist("NPrompt_massdrop_rel",closejetrelpt, massdrop,  weight, 0., 1000, 1000,  0., 200, 200);
      FillHist("NPrompt_ratio" ,electrons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 2., 100);
      FillHist("NPrompt_relpt" ,electrons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 100, 100);
    }
  }
  
    return;
  for(unsigned int iel =0 ; iel < muons_nc.size(); iel++){

    bool prompt = muons_nc[iel].MCMatched();

    if(isData){
      prompt = PassID(muons_nc[iel], "MUON_HN_TRI_HIGHDXY_TIGHT");
    }
    
    if(muons_nc[iel].MCMatched()){
      nmatched++;

      FillHist("PromptMuon_iso_pt", muons_nc[iel].Pt(),muons_nc[iel].RelIso04() ,weight,  0., 1000, 100, 0.,2., 200);
      float massdrop=MassDrop(muons_nc[iel], jets);
      float closejetpt=muons_nc[iel].Pt()/GetJetsCloseToLeptonPt(muons_nc[iel], jets);
      float closejetrelpt= GetPtRelLepTJet(muons_nc[iel], jets);
      FillHist("PromptMuon_pt", muons_nc[iel].Pt() ,weight,  0., 1000, 1000);
      FillHist("Prompt_massdrop", massdrop,  weight, 0., 1000, 1000);
      FillHist("Prompt_ratio" ,muons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 100, 100);
      FillHist("Prompt_relpt" ,muons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 100, 100);
      
      }
    else{
      FillHist("NPromptMuon_pt", muons_nc[iel].Pt() ,weight,  0., 1000, 1000);
      FillHist("NPromptMuon_iso_pt", muons_nc[iel].Pt(),muons_nc[iel].RelIso04() ,weight,  0., 1000, 100, 0.,2., 200);
      float massdrop=MassDrop(muons_nc[iel], jets);
      float closejetpt=muons_nc[iel].Pt()/GetJetsCloseToLeptonPt(muons_nc[iel], jets);
      float closejetrelpt= GetPtRelLepTJet(muons_nc[iel], jets);
      FillHist("NPrompt_massdrop", massdrop,  weight, 0., 1000, 1000);
      FillHist("NPrompt_ratio" ,muons_nc[iel].Pt(), closejetpt,  weight, 0., 1000, 100,  0., 100, 100);
      FillHist("NPrompt_relpt" ,muons_nc[iel].Pt(), closejetrelpt,  weight, 0., 1000, 100,  0., 100, 100);
    }
  }

  if(SameCharge(hn_electrons)) { 
    counter("SSHNee",1);
    FillCLHist(sighist_ee, "SSHNee", eventbase->GetEvent(), hn_muons,hn_electrons,hn04jets, fatjetcoll,weight);
  }
  if(SameCharge(pog_electrons)) {
    counter("SSPOGee",1);
    FillCLHist(sighist_ee, "SSPOGee", eventbase->GetEvent(), pog_muons,pog_electrons,hn04jets, fatjetcoll,weight);
  }
 
  if(SameCharge(hn_muons)) {
    counter("SSHNmm",1);
    FillCLHist(sighist_mm, "SSHNmm", eventbase->GetEvent(), hn_muons,hn_electrons,hn04jets, fatjetcoll,weight);
  }
  if(SameCharge(pog_muons)) {
    counter("SSPOGmm",1);
    FillCLHist(sighist_mm, "SSPOGmm", eventbase->GetEvent(), pog_muons,pog_electrons,hn04jets, fatjetcoll,weight);
  }
 
}


void HNSignalEfficiencies::counter(TString cut, float w){

  map<TString,float>::iterator itmapcounter = mapcounter.find(cut) ;
  if (itmapcounter == mapcounter.end()){
    mapcounter[cut] = w;
  }
  else{
    float sum = itmapcounter->second;
    mapcounter[cut] = sum+w;
  }

  FillCutFlow(cut,w);
}


float HNSignalEfficiencies::MassDrop(snu::KElectron electron, std::vector<snu::KJet> jets){
  if(jets.size() == 0) return -999.;
  snu::KParticle closejet;
  float mindR=0.7;
  if(electron.Pt() < 20.) return -999.;

  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( electron.DeltaR(jets.at(ijet)) < mindR){
      closejet= jets.at(ijet);
      mindR=mindR;
    }
  }

  if(mindR >= 0.7)  return -999.;

  snu::KParticle lj = closejet+electron;
  
  return (lj.M() - closejet.M());
  

}

float HNSignalEfficiencies::MassDrop(snu::KMuon muon, std::vector<snu::KJet> jets){
  if(jets.size() == 0) return -999.;
  snu::KParticle closejet;
  float mindR=.7;
  
  if(muon.Pt() < 60.) return -999.;
  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( muon.DeltaR(jets.at(ijet)) < mindR){
      closejet= jets.at(ijet);
      mindR=mindR;
    }
  }
  if(mindR >= 0.7)  return -999.;
  
  snu::KParticle lj = closejet+muon;

  return (lj.M() - closejet.M());


}


float HNSignalEfficiencies::GetPtRelLepTJetDot(snu::KElectron electron, std::vector<snu::KJet> jets){

  if(jets.size() == 0) return -999.;

  snu::KParticle closejet;
  float mindR=0.7;

  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( electron.DeltaR(jets.at(ijet)) < mindR){
      closejet= jets.at(ijet);
      mindR=mindR;
    }
  }

  TVector3 el3=  electron.Vect();
  TVector3 jet3= closejet.Vect();
  TVector3 lepjetrel = jet3-el3;

  
  float ptrel = (lepjetrel.Dot(el3))/ lepjetrel.Mag();

  return ptrel;
}



float HNSignalEfficiencies::GetPtRelLepTJet(snu::KElectron electron, std::vector<snu::KJet> jets){

  if(jets.size() == 0) return -999.;
  if(electron.Pt() < 25.) return -999.;
  snu::KParticle closejet;
  float mindR=0.7;

  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( electron.DeltaR(jets.at(ijet)) < mindR){
      closejet= jets.at(ijet);
      mindR=electron.DeltaR(jets.at(ijet));
    }
  }

  if(mindR==0.7) return 0.;

  FillHist(("ptrel_dr"),mindR, weight, 0., 4., 100);

  TVector3 el3=  electron.Vect();
  TVector3 jet3= closejet.Vect();
  TVector3 lepjetrel = jet3-el3;
  FillHist(("ptrel_lepjetmag"),lepjetrel.Mag(), weight, 0., 100., 100);
  FillHist(("ptrel_crosslepjetmag"), (lepjetrel.Cross(el3)).Mag(), weight, 0., 100., 100);
  float ptrel = (lepjetrel.Cross(el3)).Mag()/ lepjetrel.Mag();

  return ptrel;
}


float HNSignalEfficiencies::GetPtRelLepTJet(snu::KMuon muon, std::vector<snu::KJet> jets){
  
  if(jets.size() == 0) return -999.;
  if(muon.Pt() < 25.) return -999.;
  snu::KParticle closejet;
  float mindR=0.7;

  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( muon.DeltaR(jets.at(ijet)) < mindR){
      closejet= jets.at(ijet);
      mindR=muon.DeltaR(jets.at(ijet));
    }
  }
  
  if(mindR==0.7) return 0.;
  
  FillHist(("ptrel_dr"),mindR, weight, 0., 4., 100);
  
  TVector3 el3=  muon.Vect();
  TVector3 jet3= closejet.Vect();
  TVector3 lepjetrel = jet3-el3;
  FillHist(("ptrel_lepjetmag"),lepjetrel.Mag(), weight, 0., 100., 100);
  FillHist(("ptrel_crosslepjetmag"), (lepjetrel.Cross(el3)).Mag(), weight, 0., 100., 100);
  float ptrel = (lepjetrel.Cross(el3)).Mag()/ lepjetrel.Mag();
  
  return ptrel;
}

float HNSignalEfficiencies::GetJetsCloseToLeptonPt(snu::KElectron electron, std::vector<snu::KJet> jets){

  float mindR=.7;
  float jetpT=-999.;

  if(electron.Pt() < 20.) return 0.;
  
  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( electron.DeltaR(jets.at(ijet)) < mindR){
      mindR=electron.DeltaR(jets.at(ijet));
      jetpT=jets.at(ijet).Pt();
    }
  }

  return jetpT;
}



float HNSignalEfficiencies::GetJetsCloseToLeptonPt(snu::KMuon muon, std::vector<snu::KJet> jets){
  float mindR=.7;
  float jetpT=-999.;
  
  if(muon.Pt() < 20.) return 0.;

  for(unsigned int ijet=0; ijet < jets.size(); ijet++){
    if( muon.DeltaR(jets.at(ijet)) < mindR){
      mindR=muon.DeltaR(jets.at(ijet));
      jetpT=jets.at(ijet).Pt();
    }
  }
  return jetpT;
}


 

void HNSignalEfficiencies::GetTriggEfficiency(){
  //ListTriggersAvailable();                                                                                                                                                                                                                                                                                                                                                      
  vector<int> pt1;
  pt1.push_back(18);
  pt1.push_back(35);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(30);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(120);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(35);
  pt1.push_back(28);
  vector<int>pt2;
  pt2.push_back(10);
  pt2.push_back(35);
  pt2.push_back(25);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);



  std::vector<TString> lists_triggers;
  lists_triggers.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
  lists_triggers.push_back("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele23_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200");
  lists_triggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v1");
  
  lists_triggers.push_back("HLT_Ele27_WPTight_Gsf_v");
  lists_triggers.push_back("HLT_Ele32_eta2p1_WPTight_Gsf_v");
  lists_triggers.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");

  std::vector<TString> lists_triggerORs;
  lists_triggerORs.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggerORs.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");
  lists_triggerORs.push_back("HLT_Ele27_WPTight_Gsf_v");
  lists_triggerORs.push_back("HLT_Ele32_eta2p1_WPTight_Gsf");

  for(unsigned int i=0; i < lists_triggers.size(); i++){
    FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator_nojet", lists_triggers );
  }

  std::vector<snu::KJet> jets=GetJets("JET_HN");
  std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_POG_TIGHT");
  if(jets.size() > 1){
    for(unsigned int i=0; i < lists_triggers.size(); i++){
      TString trig=lists_triggers.at(i);
      FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator", lists_triggers );
      if(PassTrigger(trig))  {
	
	FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator",lists_triggers );
	
	if(electrons.size() ==2) {
	  
	  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon",lists_triggers );
	  if(electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > pt2.at(i))  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt",lists_triggers );
	}
      }
      for(int itor = 0; itor < lists_triggerORs.size(); itor++){

	if(PassTrigger(trig) || PassTrigger(lists_triggerORs.at(itor))){
	  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_"+lists_triggerORs.at(itor),lists_triggers );
	  if(electrons.size() ==2) {
	    
	    FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_"+lists_triggerORs.at(itor),lists_triggers );
	    if(electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > 5.)  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt5_"+lists_triggerORs.at(itor),lists_triggers );
	    if(electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > 10.)  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt10_"+lists_triggerORs.at(itor),lists_triggers );
	  }
	}
      }
    }
  }
}

void HNSignalEfficiencies::FillTriggerEfficiency(TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label)) {
    GetHist("TriggerEfficiency_"+label)->Fill(cut,weight);

  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label)->GetXaxis()->SetBinLabel(it+1,list.at(it));
    }
  }
  
}


void HNSignalEfficiencies::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;


  for ( map<TString,float>::iterator itmapcounter = mapcounter.begin(); itmapcounter != mapcounter.end(); itmapcounter++){
    cout << itmapcounter->first << " has count "<< itmapcounter->second << endl;
  }

}



void HNSignalEfficiencies::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

HNSignalEfficiencies::~HNSignalEfficiencies() {
  
  Message("In HNSignalEfficiencies Destructor" , INFO);
  
}



void HNSignalEfficiencies::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNSignalEfficiencies::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNSignalEfficienciesCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNSignalEfficiencies::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



