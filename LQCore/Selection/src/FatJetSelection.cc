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

void FatJetSelection::Selection(std::vector<KFatJet>& jetColl, bool isdata, bool smearjets){

  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();
  if(!isdata&&smearjets)SmearFatJets(alljets);

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

void FatJetSelection::Selection(std::vector<KFatJet>& jetColl, bool LepVeto, std::vector<KMuon>& muonColl, std::vector<KElectron>& electronColl, bool isdata, bool smearjets) {
 
  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();
  
  if(!isdata&&smearjets)SmearFatJets(alljets);
  std::vector<KFatJet> prejetColl; 

  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
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

void FatJetSelection::SelectFatJets(bool isdata, std::vector<KFatJet>& jetColl,  TString ID ,  float ptcut, float etacut, bool smearjets ) {

  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();

  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",ID);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",ID);

  if(!isdata&&smearjets)SmearFatJets(alljets);

  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pass_selection=true;
    if (!PassUserID(*jit,ID)) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection )  jetColl.push_back(*jit);
  }


} 


vector<TLorentzVector> FatJetSelection::MakeSmearedTLorentz(vector<snu::KFatJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KFatJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiE((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).E());
    tmp_j*= itj->SmearedRes();
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}

void FatJetSelection::SmearFatJets(vector<snu::KFatJet>& k_jets){

  vector<TLorentzVector> tlv_jets = MakeSmearedTLorentz(k_jets);
  int imu(0);
  for(std::vector<snu::KFatJet>::iterator it = k_jets.begin(); it != k_jets.end(); it++, imu++){
    
    it->SetPtEtaPhiE(tlv_jets[imu].Pt(), tlv_jets[imu].Eta(),tlv_jets[imu].Phi(),tlv_jets[imu].E());
  }
}

void FatJetSelection::SelectFatJets(bool isdata, std::vector<KFatJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl, TString ID ,  float ptcut, float etacut , bool smearjets) {
  
  std::vector<KFatJet> pre_jetColl; 
  std::vector<KFatJet> alljets = k_lqevent.GetFatJets();

  
  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",ID);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",ID);

  if(!isdata&&smearjets)SmearFatJets(alljets);  
  for (std::vector<KFatJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    bool pass_selection=true;
    if (!PassUserID(*jit,ID)) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection )  pre_jetColl.push_back(*jit);
  }
  //cout << "Number of loose jets = " << pre_jetColl.size() << endl;
  //cout << "Number of electrons = " << electronColl.size() << endl;
  //cout << "Number of muons = " << muonColl.size() << endl;



  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) {
    jetIsOK = true;
    for (UInt_t ilep = 0; ilep < muonColl.size(); ilep++) {
      if (muonColl[ilep].DeltaR( pre_jetColl[ijet] ) < 0.4) {
        jetIsOK = false;
	//cout << "Muon eta/phi = " << muonColl[ilep].Eta() << " " << muonColl[ilep].Phi() << endl;
        //cout << "FatJet eta/phi = " <<  pre_jetColl[ijet].Eta() << " " <<  pre_jetColl[ijet].Phi() << endl;

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
  }/// End of FatJet loop



  
}



bool FatJetSelection::PassUserID (ID id, snu::KFatJet jet){
  if      ( id == PFJET_LOOSE  ) return PassUserID_PFFatJetLoose  (jet);
  else if ( id == PFJET_TIGHT  ) return PassUserID_PFFatJetTight  (jet);
  else return false;
}


bool FatJetSelection::PassUserID (snu::KFatJet jet, TString id){ 

  
  bool checkpileupcut  = (CheckCutString("pileup",id));
  bool checkloosecut = (CheckCutString("LooseID",id));
  bool checktightid =  (CheckCutString("TightID",id));
  bool checktightlvid =  (CheckCutString("TightIDLepVeto",id));
  
  bool pass_selection=true;
  if (checkpileupcut && !jet.PileupJetIDLoose()) pass_selection=false;
  if(checkloosecut && !jet.PassLooseID()) pass_selection=false;
  if(checktightid&&!jet.PassTightID()) pass_selection=false;
  if(checktightlvid&&!jet.PassTightLepVetoID()) pass_selection=false;

  return pass_selection;

}


bool FatJetSelection::PassUserID_PFFatJetLoose ( snu::KFatJet jet){
  
  return jet.PassLooseID();
}


bool FatJetSelection::PassUserID_PFFatJetTight ( snu::KFatJet jet)
{
  return jet.PassTightID();
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



