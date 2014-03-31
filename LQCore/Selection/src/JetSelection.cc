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

  

void JetSelection::Selection(std::vector<KJet>& jetColl) {
  
  //// This is a basic set of cuts on jets
 
  std::vector<KJet> alljets = k_lqevent.GetJets();
  
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    if(apply_ID) {
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max &&
	   fabs(jit->Eta()) < eta_cut
	   && PassUserID(k_id, *jit))  jetColl.push_back(*jit);
    }
    else{
      if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max && 
	   fabs(jit->Eta()) < eta_cut
	   && PassUserID(PFJET_LOOSE, *jit))  jetColl.push_back(*jit);
    }
  }
  BaseSelection::reset();
  return;
  
}


void JetSelection::JetHNSelection(std::vector<KJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl) {
  
  std::vector<KJet> pre_jetColl; 
  std::vector<KJet> alljets = k_lqevent.GetJets();
  
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    if ( jit->Pt() >= 30. && fabs(jit->Eta()) < 2.5   && PassUserID(PFJET_LOOSE, *jit))  pre_jetColl.push_back(*jit);
    
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

void JetSelection::JetSelectionLeptonVeto(std::vector<KJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl) {
  
  //// This is a basic set of cuts on jets
  ///  + the jets are removed that are close to leptons
  
  std::vector<KJet> pre_jetColl;
  Selection(pre_jetColl);
  
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
  } /// End of Jet loop
  
}


bool JetSelection::PassUserID (ID id, snu::KJet jet){ 
  if      ( id == PFJET_LOOSE  ) return PassUserID_PFJetLoose  (jet);
  else if ( id == PFJET_MEDIUM ) return PassUserID_PFJetMedium (jet);
  else if ( id == PFJET_TIGHT  ) return PassUserID_PFJetTight  (jet);
  else return false;
}

bool JetSelection::PassUserID_PFJetLoose ( snu::KJet jet){
  
  bool pass_chargedHadFraction_central  = true;
  bool pass_chargedEMFraction_central   = true;
  bool pass_chargedMultiplicity_central = true;
  bool pass_neutralhadFraction          = bool ( jet.NeutralHadEnergyFraction () < 0.99 );
  bool pass_neutralEMFraction           = bool ( jet.NeutralEMEnergyFraction     () < 0.99 );
  bool pass_nConstituents               = bool ( jet.Nconstituents               () > 1    );


  if ( fabs ( jet.Eta() ) < 2.4 ) {
    pass_chargedHadFraction_central = bool ( jet.ChargedHadEnergyFraction() > 0.0  );
    pass_chargedMultiplicity_central= bool ( jet.ChargedMultiplicity        () > 0    );
    pass_chargedEMFraction_central  = bool ( jet.ChargedEMEnergyFraction    () < 0.99 );
  }
  
  bool decision = ( pass_chargedHadFraction_central  && 
		        pass_chargedEMFraction_central   && 
		        pass_chargedMultiplicity_central && 
		        pass_neutralhadFraction          && 
		        pass_neutralEMFraction           && 
		    pass_nConstituents                );
  
  return decision;
  
}



bool JetSelection::PassUserID_PFJetMedium( snu::KJet jet ){
  
  bool pass_chargedHadFraction_central  = true;
  bool pass_chargedEMFraction_central   = true;
  bool pass_chargedMultiplicity_central = true;
  bool pass_neutralhadFraction          = bool ( jet.NeutralHadEnergyFraction () < 0.95 );
  bool pass_neutralEMFraction           = bool ( jet.NeutralEMEnergyFraction     () < 0.95 );
  bool pass_nConstituents               = bool ( jet.Nconstituents               () > 1    );
  
  if ( fabs ( jet.Eta() ) < 2.4 ) {
    pass_chargedHadFraction_central = bool ( jet.ChargedHadEnergyFraction() > 0.0  );
    pass_chargedMultiplicity_central= bool ( jet.ChargedMultiplicity        () > 0    );
    pass_chargedEMFraction_central  = bool ( jet.ChargedEMEnergyFraction    () < 0.99 );
  }
  
  bool decision = ( pass_chargedHadFraction_central  && 
		        pass_chargedEMFraction_central   && 
		        pass_chargedMultiplicity_central && 
		        pass_neutralhadFraction          && 
		        pass_neutralEMFraction           && 
		    pass_nConstituents                );

  return decision;

}

bool JetSelection::PassUserID_PFJetTight ( snu::KJet jet ){
  
  bool pass_chargedHadFraction_central  = true;
  bool pass_chargedEMFraction_central   = true;
  bool pass_chargedMultiplicity_central = true;
  bool pass_neutralhadFraction          = bool ( jet.NeutralHadEnergyFraction () < 0.90 );
  bool pass_neutralEMFraction           = bool ( jet.NeutralEMEnergyFraction     () < 0.90 );
  bool pass_nConstituents               = bool ( jet.Nconstituents               () > 1    );
  
  if ( fabs ( jet.Eta() ) < 2.4 ) {
    pass_chargedHadFraction_central = bool ( jet.ChargedHadEnergyFraction() > 0.0  );
    pass_chargedMultiplicity_central= bool ( jet.ChargedMultiplicity        () > 0    );
    pass_chargedEMFraction_central  = bool ( jet.ChargedEMEnergyFraction    () < 0.99 );
  }
  
  bool decision = ( pass_chargedHadFraction_central  && 
		        pass_chargedEMFraction_central   && 
		        pass_chargedMultiplicity_central && 
		        pass_neutralhadFraction          && 
		        pass_neutralEMFraction           && 
		    pass_nConstituents                );

  return decision;

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



