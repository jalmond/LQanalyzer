#include "JetSelection.h"

using namespace snu;

JJ::JJ(LQEvent ev) {
  k_lqevent = ev;
}

JJ::~JJ() {}

//// This code is used to make selection cuts to vectors of KJets

void JJ::JetSelection(std::vector<KJet>& jetColl) {
  
  //// This is a basic set of cuts on jets
 
  std::vector<KJet> alljets = k_lqevent.GetBaseJets();
  
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    if ( jit->Pt() >= pt_cut_min && jit->Pt() < pt_cut_max && 
	 fabs(jit->Eta()) < eta_cut
	 && jit->PassLooseID()
	 && jit->NeutralHEF() < 0.99
	 && jit->NeutralEmEF() < 0.99
	 && jit->Nconstituents() > 1
	 && ( fabs( jit->Eta() ) > 2.4 || ( jit->ChargedHEF() > 0. && jit->ChargedMultiplicity() > 0. && jit->ChargedEmEF() < 0.99 ) ) ) { 
      
      jetColl.push_back(*jit);
    }
  }
}


void JJ::JetSelectionLeptonVeto(std::vector<KJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl) {
  
  //// This is a basic set of cuts on jets
  ///  + the jets are removed that are close to leptons
  
  std::vector<KJet> pre_jetColl;
  JetSelection(pre_jetColl);
  
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


