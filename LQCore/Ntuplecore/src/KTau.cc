#include "KTau.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KTau)

/**
 *Default constructor.
 */
KTau::KTau() :
KParticle()
{
  k_ispf=0;
}

/**
 * Copy constructor.
 */
KTau::KTau(const KTau& tau) :
    KParticle(tau)
{
  k_ispf=tau.IsPF();
}


KTau::~KTau()
{
}

void KTau::Reset()
{
  KParticle::Reset();
  k_ispf=0;
}



KTau& KTau::operator= (const KTau& p)
{
    if (this != &p) {
        KParticle::operator=(p);
	k_ispf=p.IsPF();
    }
    
    return *this;
}


//// SET CLASS VARIBALES



void KTau::SetIsPF(Int_t ispf){

  k_ispf = ispf;
}
