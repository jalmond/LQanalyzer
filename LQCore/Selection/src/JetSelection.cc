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

  

void JetSelection::Selection(std::vector<KJet>& jetColl, bool isdata, bool smearjets) {
  
  //// This is a basic set of cuts on jets
 
  std::vector<KJet> alljets = k_lqevent.GetJets();
  
  //  if(!isdata&&smearjets)SmearJets(alljets);

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
    bool pileupjet=false;
    if(applypileuptool) pileupjet =  ( !jit->PileupJetIDLoose());  ///---> CHECK THIS
    pileupjet=false;


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

void JetSelection::SelectJets(bool isdata, std::vector<KJet>& jetColl,  TString ID ,  float ptcut, float etacut, bool smearjets ) {

  std::vector<KJet> alljets = k_lqevent.GetJets();

  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",ID);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",ID);

  //  if(!isdata&&smearjets)SmearJets(alljets);

  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){

    bool pass_selection=true;
    if (!PassUserID(*jit,ID)) pass_selection=false;
    if ( (jit->Pt() >= ptcut)  && fabs(jit->Eta()) < etacut && pass_selection )  jetColl.push_back(*jit);
  }


} 


vector<TLorentzVector> JetSelection::MakeSmearedTLorentz(vector<snu::KJet> j){

  vector<TLorentzVector> tl_jet;
  for(vector<KJet>::iterator itj=j.begin(); itj!=j.end(); ++itj) {
    TLorentzVector tmp_j;
    tmp_j.SetPtEtaPhiE((*itj).Pt(),(*itj).Eta(),(*itj).Phi(),(*itj).E());
    tmp_j*= itj->SmearedRes();
    tl_jet.push_back(tmp_j);
  }
  return tl_jet;
}

void JetSelection::SmearJets(vector<snu::KJet>& k_jets){

  vector<TLorentzVector> tlv_jets = MakeSmearedTLorentz(k_jets);
  int imu(0);
  for(std::vector<snu::KJet>::iterator it = k_jets.begin(); it != k_jets.end(); it++, imu++){
    
    it->SetPtEtaPhiE(tlv_jets[imu].Pt(), tlv_jets[imu].Eta(),tlv_jets[imu].Phi(),tlv_jets[imu].E());
  }
}

void JetSelection::SelectJets(bool isdata, std::vector<KJet>& jetColl, std::vector<KMuon> muonColl, std::vector<KElectron> electronColl, TString ID ,  float ptcut, float etacut , bool smearjets) {
  
  std::vector<KJet> pre_jetColl; 
  std::vector<KJet> alljets = k_lqevent.GetJets();

  
  if (ptcut == -999.) ptcut = AccessFloatMap("ptmin",ID);
  if (etacut == -999.) etacut = AccessFloatMap("|etamax|",ID);

  //if(!isdata&&smearjets)SmearJets(alljets);  
  for (std::vector<KJet>::iterator jit = alljets.begin(); jit!=alljets.end(); jit++){
    
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
        //cout << "Jet eta/phi = " <<  pre_jetColl[ijet].Eta() << " " <<  pre_jetColl[ijet].Phi() << endl;

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



bool JetSelection::PassUserID (ID id, snu::KJet jet){
  if      ( id == PFJET_LOOSE  ) return PassUserID_PFJetLoose  (jet);
  else if ( id == PFJET_TIGHT  ) return PassUserID_PFJetTight  (jet);
  else return false;
}


bool JetSelection::PassUserID (snu::KJet jet, TString id){ 

  
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


bool JetSelection::PassUserID_PFJetLoose ( snu::KJet jet){
  
  return jet.PassLooseID();
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



