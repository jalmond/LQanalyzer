#include "JetSelection.h"
#include <iostream>


using namespace snu;

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



void JetSelection::SelectJets(std::vector<KJet>& jetColl,  float ptcut, float etacut) {

  std::vector<KJet> alljets = k_lqevent.GetJets();
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pass_selection=true;
    if (!  jit->PassTightID()) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection )  jetColl.push_back(*jit);
  }


}


void JetSelection::SelectJets(std::vector<KJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl , float ptcut, float etacut) {
  std::vector<KJet> alljets = k_lqevent.GetJets();
  std::vector<KJet> pre_jetColl;

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pass_selection=true;
    if (!  jit->PassTightID()) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection ) pre_jetColl.push_back(*jit);
  }
  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.4) {
        jetIsOK = false;

        ilep = muonColl.size();
      }
    }/// End of muon loop                                                                                                                                                                                                                                                       
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.4 ) {
        jetIsOK = false;
        ilep = electronColl.size();
      }
    }/// End of electron loop                                                                                                                                                                                                                                                   

    if (jetIsOK) jetColl.push_back( pre_jetColl[ijet] );
  }/// End of Jet loop                                                                                                                                                                                                                                                          
}

void JetSelection::SelectJets(std::vector<KJet>& jetColl,  std::vector<KFatJet> fatjetColl,std::vector<KMuon> muonColl, std::vector<KElectron> electronColl , float ptcut, float etacut) {
  std::vector<KJet> alljets = k_lqevent.GetJets();
  std::vector<KJet> pre_jetColl;

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pass_selection=true;
    if (!  jit->PassTightID()) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection ) pre_jetColl.push_back(*jit);
  }
  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.4) {
        jetIsOK = false;

        ilep = muonColl.size();
      }
    }/// End of muon loop                                                                                                                                                                                
                                                                                                                                                                                                            
    for (UInt_t ilep = 0; ilep < electronColl.size(); ilep++) {
      if (electronColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.4 ) {
        jetIsOK = false;
        ilep = electronColl.size();
      }
    }/// End of electron loop                                                                                                                                                                            
                                                                                                                                                                                                            

    if (jetIsOK) jetColl.push_back( pre_jetColl[ijet] );
  }/// End of Jet loop                                                                                                                                                                                    
  
  return;
                                                                                                                                                                                                            
}


bool JetSelection::PassUserID (ID id, snu::KJet jet){
  if      ( id == PFJET_LOOSE  ) return PassUserID_PFJetLoose  (jet);
  else if ( id == PFJET_TIGHT  ) return PassUserID_PFJetTight  (jet);
  else return false;
}


bool JetSelection::PassUserID (snu::KJet jet,vector<pair<TString, TString> > vids){ 

  for(unsigned int idel =0; idel < vids.size(); idel++){
    if(vids[idel].second == "false") continue;
    if(vids[idel].first == "pileup") { 
      if (!jet.PassPileUpMVA(vids[idel].second)) return false;
    }
    if(vids[idel].first == "TightID") {
      if(!jet.PassTightID())  return false;
    }
    if(vids[idel].first == "TightIDLepVeto"){
      if(!jet.PassTightLepVetoID()) return false;
    }
  }

  return true;

}


bool JetSelection::PassUserID_PFJetLoose ( snu::KJet jet){
  
  return true;
}


bool JetSelection::PassUserID_PFJetTight ( snu::KJet jet)
{
  return jet.PassTightID();
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



