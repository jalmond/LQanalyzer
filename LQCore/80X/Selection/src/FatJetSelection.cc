#include "FatJetSelection.h"
#include <iostream>


using namespace snu;

FatJetSelection::FatJetSelection(LQEvent ev) :BaseSelection() {
  k_lqevent = ev;
}

FatJetSelection::~FatJetSelection() {}

//// This code is used to make selection cuts to vectors of KFatJets


void FatJetSelection::BasicSelection(std::vector<KFatJet>& jetColl) {
  
  //// This is a basic set of cuts on jets

  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();

  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
  
    if ( (jit->Pt() >= pt_cut_min) &&  (fabs(jit->Eta()) < eta_cut)){
      if ( PassUserID(PFJET_LOOSE, *jit) &&    (jit->Pt() >= pt_cut_min) &&  (fabs(jit->Eta()) < eta_cut))  jetColl.push_back(*jit);
    }
       
  }
}

void FatJetSelection::Selection(std::vector<KFatJet>& jetColl){
  
  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();
  
  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pileupjet=false;
    if(applypileuptool) pileupjet =  ( !jit->PileupJetIDLoose());  ///---> CHECK THIS


    if(apply_ID) {
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
           fabs(jit->Eta()) < eta_cut
           &&PassUserID(k_id, *jit) && !pileupjet)  jetColl.push_back(*jit);
    }
    else{
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
           fabs(jit->Eta()) < eta_cut
           && PassUserID(PFJET_LOOSE, *jit)&& !pileupjet)  jetColl.push_back(*jit);
    }
  }

  BaseSelection::reset();
  return;

}  

void FatJetSelection::Selection(std::vector<KFatJet>& jetColl, bool LepVeto, std::vector<KMuon>& muonColl, std::vector<KElectron>& electronColl,TString Option) {
  
  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();
  
  std::vector<KFatJet> prejetColl; 

  int  SystDir=0;
  bool Syst_JES=false, Syst_JER=false;
  bool Syst_JMS=false, Syst_JMR=false;
  
  
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir= 1;
    else if(Option.Contains("Down")) SystDir=-1;
    if     (Option.Contains("JES"))  Syst_JES=true;
    if     (Option.Contains("JER"))  Syst_JER=true;
    if     (Option.Contains("JMS"))  Syst_JMS=true;
    if     (Option.Contains("JMR"))  Syst_JMR=true;
  }
  

  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    if(!Syst_JER){
      *jit *= jit->SmearedRes();
      cout << "jit->PrunedMass() = " << jit->PrunedMass() << endl;
      jit->SetPrunedMass(jit->PrunedMass()* jit->SmearedRes());
    }
    if     (Syst_JES && SystDir>0) {*jit *= jit->ScaledUpEnergy(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledUpEnergy());}
    else if(Syst_JES && SystDir<0) {*jit *= jit->ScaledDownEnergy(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledDownEnergy());}
    else if(Syst_JER && SystDir>0) {*jit *= jit->SmearedResUp();  jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedResUp());}
    else if(Syst_JER && SystDir<0) {*jit *= jit->SmearedResDown();   jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedResDown());}
    else if(Syst_JMR && SystDir>0) {*jit *= jit->SmearedMassResUp();  jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedMassResUp());}
    else if(Syst_JMR && SystDir<0) {*jit *= jit->SmearedMassResDown(); jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedMassResUp());}
    else if(Syst_JMS && SystDir>0) {*jit *= jit->ScaledMassUp(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledMassUp());}
    else if(Syst_JMS && SystDir<0) {*jit *= jit->ScaledMassDown(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledMassDown());}

    
  
    bool pileupjet=false;
    if(applypileuptool) pileupjet =  ( !jit->PileupJetIDLoose());  ///---> CHECK THIS


    if(apply_ID) {
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
	   fabs(jit->Eta()) < eta_cut
	   &&PassUserID(k_id, *jit) && !pileupjet)  prejetColl.push_back(*jit);
    }
    else{
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max && 
	   fabs(jit->Eta()) < eta_cut
	   && PassUserID(PFJET_LOOSE, *jit)&& !pileupjet)  prejetColl.push_back(*jit);
    }
  } 

  for (UInt_t ijet = 0; ijet < prejetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( prejetColl[ijet] ) < 1.) {
	jetIsOK = false;  ilep = muonColl.size();
      }
    }/// End of muon loop
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( prejetColl[ijet] ) < 1. ) {
	jetIsOK = false;  ilep = electronColl.size();
      }
    }/// End of electron loop
    
    if(LepVeto){
      if (jetIsOK) jetColl.push_back( prejetColl[ijet] );
    }
    else{
      jetColl.push_back( prejetColl[ijet] );
    }
  }
  
  
  BaseSelection::reset();
  return;
  
}


void FatJetSelection::SelectFatJets(std::vector<KFatJet>& jetColl, TString jetid, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl, TString Option, float ptcut , float etacut ) {

  
  std::vector<KFatJet> pre_jetColl; 

  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();


  int  SystDir=0;
  bool Syst_JES=false, Syst_JER=false;
  bool Syst_JMS=false, Syst_JMR=false;


  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir= 1;
    else if(Option.Contains("Down")) SystDir=-1;
    if     (Option.Contains("JES"))  Syst_JES=true;
    if     (Option.Contains("JER"))  Syst_JER=true;
    if     (Option.Contains("JMS"))  Syst_JMS=true;
    if     (Option.Contains("JMR"))  Syst_JMR=true;
  }


  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    if(!Syst_JER){
      *jit *= jit->SmearedRes();
      jit->SetPrunedMass(jit->PrunedMass()* jit->SmearedRes());
    }
    if     (Syst_JES && SystDir>0) {*jit *= jit->ScaledUpEnergy(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledUpEnergy());}
    else if(Syst_JES && SystDir<0) {*jit *= jit->ScaledDownEnergy(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledDownEnergy());}
    else if(Syst_JER && SystDir>0) {*jit *= jit->SmearedResUp();  jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedResUp());}
    else if(Syst_JER && SystDir<0) {*jit *= jit->SmearedResDown();   jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedResDown());}
    else if(Syst_JMR && SystDir>0) {*jit *= jit->SmearedMassResUp();  jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedMassResUp());}
    else if(Syst_JMR && SystDir<0) {*jit *= jit->SmearedMassResDown(); jit->SetPrunedMass(jit->PrunedMass()*jit->SmearedMassResUp());}
    else if(Syst_JMS && SystDir>0) {*jit *= jit->ScaledMassUp(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledMassUp());}
    else if(Syst_JMS && SystDir<0) {*jit *= jit->ScaledMassDown(); jit->SetPrunedMass(jit->PrunedMass()*jit->ScaledMassDown());}

    bool pass_selection= true;
    if(!jit->PassCustomID(jetid)) pass_selection = false;
    if((jit->Pt() < ptcut))   pass_selection = false;
    if(!jit->AbsEta() > etacut)  pass_selection = false; 
    if(pass_selection) pre_jetColl.push_back(*jit);
    
  }


  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( pre_jetColl[ijet] ) < 1.) {
        jetIsOK = false;
	//cout << "Muon eta/phi = " << muonColl[ilep].Eta() << " " << muonColl[ilep].Phi() << endl;
        //cout << "FatJet eta/phi = " <<  pre_jetColl[ijet].Eta() << " " <<  pre_jetColl[ijet].Phi() << endl;

	ilep = muonColl.size();
      }
    }/// End of muon loop
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( pre_jetColl[ijet] ) < 1. ) {
        jetIsOK = false;
        ilep = electronColl.size();
      }
    }/// End of electron loop
    
    if (jetIsOK) jetColl.push_back( pre_jetColl[ijet] );
  }/// End of FatJet loop
  
}



bool FatJetSelection::PassUserID (ID id, snu::KFatJet jet){
  if      ( id == PFJET_LOOSE  ) return jet.PassLooseID();
  else if ( id == PFJET_TIGHT  ) return jet.PassTightID();
  else return false;
}


FatJetSelection& FatJetSelection::operator= (const FatJetSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms);
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

FatJetSelection::FatJetSelection(const FatJetSelection& ms):
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;  
};



