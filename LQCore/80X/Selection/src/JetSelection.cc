#include "JetSelection.h"
#include <iostream>


using namespace snu;



////////////////////////////////////////////////                                                                         
////// FUNCTIONS FOR SKTREEMAKER                                                                                                                                                                           //////////////////////////////////////////////// 

JetSelection::JetSelection(LQEvent ev) :BaseSelection() {
  k_lqevent = ev;
}

JetSelection::~JetSelection() {}

//// This code is used to make selection cuts to vectors of KJets


void JetSelection::BasicSelection(std::vector<KJet>& jetColl) {
  
  //// This is a basic set of cuts on jets

  std::vector<KJet> alljets = k_lqevent.GetJets();

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
  
    if ( (jit->Pt() >= pt_cut_min) &&  (fabs(jit->Eta()) < eta_cut)){
      if ( PassUserID(PFJET_LOOSE, *jit) &&    (jit->Pt() >= pt_cut_min) &&  (fabs(jit->Eta()) < eta_cut))  jetColl.push_back(*jit);
    }
       
  }
}

void JetSelection::Selection(std::vector<KJet>& jetColl){

  std::vector<KJet> alljets = k_lqevent.GetJets();

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool IsNotPileUpJet = true;
    if(applypileuptool){
      IsNotPileUpJet = jit->PassPileUpMVA(PUJetIDWP);
    }


    if(apply_ID) {
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
           fabs(jit->Eta()) < eta_cut
           && PassUserID(k_id, *jit) && IsNotPileUpJet)  jetColl.push_back(*jit);
    }
    else{
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
           fabs(jit->Eta()) < eta_cut
           && PassUserID(PFJET_LOOSE, *jit)&& IsNotPileUpJet)  jetColl.push_back(*jit);
    }
  }

  BaseSelection::reset();
  return;

}  


////////////////////////////////////////////////                                                                                                                                                           
////// FUNCTIONS FOR ANALYSIS                                                                                                                                                                        
////////////////////////////////////////////////  

void JetSelection::Selection(std::vector<KJet>& jetColl, bool LepVeto, std::vector<KMuon>& muonColl, std::vector<KElectron>& electronColl, TString Option){
 
  std::vector<KJet> alljets = k_lqevent.GetJets();
  
  std::vector<KJet> prejetColl; 
  int  SystDir=0;
  bool Syst_JES=false, Syst_JER=false;
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir= 1;
    else if(Option.Contains("Down")) SystDir=-1;
    if     (Option.Contains("JES"))  Syst_JES=true;
    if     (Option.Contains("JER"))  Syst_JER=true;
  }

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    if     (Syst_JES && SystDir>0) *jit *= jit->ScaledUpEnergy();
    else if(Syst_JES && SystDir<0) *jit *= jit->ScaledDownEnergy();
    if(jit->IsMCSmeared()){
      if(Syst_JER && SystDir>0) *jit *= (jit->SmearedResUp() /jit->SmearedRes());
      else if(Syst_JER && SystDir<0) *jit *= (jit->SmearedResDown()/jit->SmearedRes());
    }
    else{
      if(Syst_JER && SystDir>0) *jit *= jit->SmearedResUp();
      else if(Syst_JER && SystDir<0) *jit *= jit->SmearedResDown();

    }
    bool IsNotPileUpJet = true;
    if(applypileuptool) IsNotPileUpJet = jit->PassPileUpMVA(PUJetIDWP);
    if(apply_ID) {
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
	   fabs(jit->Eta()) < eta_cut
	   && PassUserID(k_id, *jit) && IsNotPileUpJet)  prejetColl.push_back(*jit);
    }
    else{
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max && 
	   fabs(jit->Eta()) < eta_cut
	   && PassUserID(PFJET_LOOSE, *jit) && IsNotPileUpJet)  prejetColl.push_back(*jit);
    }
  } 

  for (UInt_t ijet = 0; ijet < prejetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( prejetColl[ijet] ) < 0.4) {
	jetIsOK = false;  ilep = muonColl.size();
      }
    }/// End of muon loop
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( prejetColl[ijet] ) < 0.4 ) {
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



void JetSelection::SelectJets(std::vector<KJet>& jetColl,  TString jetid,std::vector<KMuon> muonColl,std::vector<KElectron> electronColl, TString Option, float ptcut, float etacut) {
  
  std::vector<snu::KFatJet> fatjets;
  return SelectJets(jetColl,jetid, fatjets, muonColl,electronColl, Option, ptcut , etacut);
}

void JetSelection::SelectJets(std::vector<KJet>& jetColl, TString jetid,  std::vector<snu::KFatJet> fatjets , std::vector<KMuon> muonColl,std::vector<KElectron> electronColl, TString Option, float ptcut, float etacut) {

  std::vector<KJet> pre_jetColl;
  std::vector<KJet> alljets = k_lqevent.GetJets();


  if (ptcut == -999.) ptcut = 20.;
  if (etacut == -999.) etacut = 2.5;


  std::vector<KJet> prejetColl;
  int  SystDir=0;
  bool Syst_JES=false, Syst_JER=false;
  if(Option.Contains("Syst")){
    if     (Option.Contains("Up"))   SystDir= 1;
    else if(Option.Contains("Down")) SystDir=-1;
    if     (Option.Contains("JES"))  Syst_JES=true;
    if     (Option.Contains("JER"))  Syst_JER=true;
  }

  /// https://indico.cern.ch/event/613931/contributions/2476973/attachments/1413452/2181248/update_WTagging_JMAR15022017_Simone.pdf
  /// see slides for delat R cuts between objetst
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    // -- Check if jets should be scaled for syst
    if     (Syst_JES && SystDir>0) *jit *= jit->ScaledUpEnergy();
    else if(Syst_JES && SystDir<0) *jit *= jit->ScaledDownEnergy();

    // -- Check if jets should be smeared for syst
    if(jit->IsMCSmeared()){
      if(Syst_JER && SystDir>0) *jit *= (jit->SmearedResUp() /jit->SmearedRes());
      else if(Syst_JER && SystDir<0) *jit *= (jit->SmearedResDown()/jit->SmearedRes());
    }
    else{
      if(Syst_JER && SystDir>0) *jit *= jit->SmearedResUp();
      else if(Syst_JER && SystDir<0) *jit *= jit->SmearedResDown();
    }    
    bool pass_selection=true;
    // -- apply custom ID
    if(!jit->PassCustomID(jetid)) pass_selection = false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection )  pre_jetColl.push_back(*jit);
  }
  

  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
  
    for (UInt_t ifjet = 0; ifjet < fatjets.size(); ifjet++) {
      if (fatjets[ifjet].DeltaR( pre_jetColl[ijet] ) < 0.8) {
        jetIsOK = false;

        ifjet = fatjets.size();
      }
    }/// End of fatjet loop     
    
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.3) {
        jetIsOK = false;

        ilep = muonColl.size();
      }
    }/// End of muon loop                                                                                                                                                    
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.3 ) {
        jetIsOK = false;
        ilep = electronColl.size();
      }
    }/// End of electron loop                                                                                                                                                

    if (jetIsOK) jetColl.push_back( pre_jetColl[ijet] );
  }/// End of Jet loop                                                                                                                                                       
}




bool JetSelection::PassUserID (ID id, snu::KJet jet){
  if      ( id == PFJET_LOOSE  ) return jet.PassLooseID();
  else if ( id == PFJET_TIGHT  ) return jet.PassTightID();
  else return false;
}




JetSelection& JetSelection::operator= (const JetSelection& ms) {
  if(this != &ms){    
    BaseSelection::operator = (ms);
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

JetSelection::JetSelection(const JetSelection& ms):
  BaseSelection(ms)
{
  k_lqevent = ms.k_lqevent;  
};



