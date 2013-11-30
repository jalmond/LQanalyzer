#include "KJet.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KJet)

/**
 *Default constructor.
 */
KJet::KJet() :
KParticle()
{
  k_passLooseID=0;
  k_neutralEmEF=0;
  k_neutralHEF=0;
  k_chargeEmEF=0;
  k_chargeHEF=0;
  k_chargeMult=0;
  k_jetNconst=0;
  k_JetSecVertBtag=0;
  k_TCHPT=0;
  k_closest3Dsep=0;
  k_closestXYsep=0;
  k_closestZsep=0;
  k_JetProbBtag =0;

}

/**
 * Copy constructor.
 */
KJet::KJet(const KJet& jet) :
    KParticle(jet)
{
  k_passLooseID = jet.PassLooseID();
  k_neutralEmEF = jet.NeutralEmEF();
  k_neutralHEF = jet.NeutralEmEF();
  k_chargeEmEF  =jet.ChargedEmEF();
  k_chargeHEF = jet.ChargedHEF();
  k_chargeMult = jet.ChargedMultiplicity();
  k_jetNconst = jet.Nconstituents();
  k_JetSecVertBtag = jet.CombinedSecVertexBtag();
  k_closest3Dsep = jet.JetRho();
  k_TCHPT = jet.PFJetTrackCountingHighPurBTag();
  k_closestZsep = jet.ClosestZsep();
  k_closestXYsep= jet.ClosestXYsep();
  k_JetProbBtag = jet.BtagProb();
}


KJet::~KJet()
{
}

void KJet::Reset()
{
    KParticle::Reset();
    k_passLooseID = 0;
    k_neutralEmEF = 0;
    k_neutralHEF = 0;
    k_chargeEmEF = 0;
    k_chargeHEF = 0;
    k_chargeMult = 0;
    k_jetNconst = 0;
    k_JetSecVertBtag = 0;
    k_closest3Dsep = 0;
    k_TCHPT=0;
    k_closestZsep = 0;
    k_closestXYsep= 0;
    k_JetProbBtag = 0;

}


//Int_t KJet::GetFlavourTruthLabel() const {
///return m_flavor_truth_label;
//}



KJet& KJet::operator= (const KJet& p)
{
    if (this != &p) {
        KParticle::operator=(p);
	k_passLooseID = p.PassLooseID();
	k_TCHPT = p.PFJetTrackCountingHighPurBTag();
	k_neutralEmEF = p.NeutralEmEF();
	k_neutralHEF = p.NeutralEmEF();
	k_chargeEmEF  =p.ChargedEmEF();
	k_chargeHEF = p.ChargedHEF();
	k_chargeMult = p.ChargedMultiplicity();
	k_jetNconst = p.Nconstituents();
	k_JetSecVertBtag = p.CombinedSecVertexBtag();
	k_closest3Dsep = p.JetRho();
	k_closestZsep = p.ClosestZsep();
	k_closestXYsep= p.ClosestXYsep();
	k_JetProbBtag = p.BtagProb();
    }

    return *this;
}


void KJet::SetPassLooseID(int looseID){

  k_passLooseID = looseID;
}


void KJet::SetPFJetTrackCountingHighPurBTag(double TCHPT){

  k_TCHPT = TCHPT;
}

void KJet::SetPFJetJetProbabilityBTag(double JP){

  k_JetProbBtag = JP;
}

void KJet::SetPFJetClosestVertexWeightedXYSeparation(double cvxys){

  k_closestXYsep = cvxys;
}

void KJet::SetPFJetClosestVertexWeightedZSeparation(double cvzs){

  k_closestZsep = cvzs;
}


void KJet::SetNeutralEmEF(double neutEmEF){
  
  k_neutralEmEF = neutEmEF;
}

void KJet::SetNeutralHEF(double neutHEF){
  k_neutralHEF = neutHEF;
}

void KJet::SetChargedEmEF(double chargeEmEF){
  k_chargeEmEF = chargeEmEF;
}

void KJet::SetChargedHEF(double chargeHEF){
  k_chargeHEF = chargeHEF;
}

void KJet::SetChargedMult(int chargeMult){
  k_chargeMult = chargeMult;
}

void KJet::SetJetNCon(int jetNconst){
  k_jetNconst = jetNconst;
}

void KJet::SetJetSecVertBtag(double svbt){
  k_JetSecVertBtag = svbt;
}

void KJet::SetClosestVertW3DSep(double cv3ds){
  k_closest3Dsep = cv3ds;
}
