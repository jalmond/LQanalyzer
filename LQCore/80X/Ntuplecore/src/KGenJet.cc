#include "KGenJet.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KGenJet)

/**
 *Default constructor.
 */
KGenJet::KGenJet() :
  KParticle()  
{
  k_genjet_p = -999.;
  k_genjet_emf = -999.;
  k_genjet_hadf = -999.;
  k_genjet_pdgid =-999;
}

/**
 * Copy constructor.
 */
KGenJet::KGenJet(const KGenJet& gjet) :
  KParticle(gjet)
{
  k_genjet_p = gjet.P();
  k_genjet_emf = gjet.EMF() ;
  k_genjet_hadf = gjet.HADF();
  k_genjet_pdgid = gjet.PdgId();
}


KGenJet::~KGenJet()
{
}

void KGenJet::Reset()
{
  k_genjet_p = -999.;
  k_genjet_emf = -999. ;
  k_genjet_hadf = -999.; 
  k_genjet_pdgid=-999;

}



KGenJet& KGenJet::operator= (const KGenJet& p)
{
    if (this != &p) {
      k_genjet_p = p.P();
      k_genjet_emf = p.EMF() ;
      k_genjet_hadf = p.HADF();
      k_genjet_pdgid = p.PdgId();
    }
    
    return *this;
}

//// SET CLASS VARIBALES

void KGenJet::SetGenJetPDGID(int p){
  k_genjet_pdgid = p;
}

void KGenJet::SetGenJetP(float p){
  k_genjet_p = p;
}

void KGenJet::SetGenJetEMF(float emf){
  k_genjet_emf = emf;  
}

void KGenJet::SetGenJetHADF(float hadf){
  k_genjet_hadf = hadf;
  
}


