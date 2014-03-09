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
  k_genjet_p = 0.;
  k_genjet_emf = 0.;
  k_genjet_hadf = 0.;
  
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
}


KGenJet::~KGenJet()
{
}

void KGenJet::Reset()
{
  k_genjet_p = 0.;
  k_genjet_emf = 0. ;
  k_genjet_hadf = 0.; 

}



KGenJet& KGenJet::operator= (const KGenJet& p)
{
    if (this != &p) {
      k_genjet_p = p.P();
      k_genjet_emf = p.EMF() ;
      k_genjet_hadf = p.HADF();
    }
    
    return *this;
}

//// SET CLASS VARIBALES

void KGenJet::SetGenJetP(double p){
  k_genjet_p = p;
}

void KGenJet::SetGenJetEMF(double emf){
  k_genjet_emf = emf;  
}

void KGenJet::SetGenJetHADF(double hadf){
  k_genjet_hadf = hadf;
  
}


