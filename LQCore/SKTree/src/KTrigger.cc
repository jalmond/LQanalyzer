#include "KTrigger.h"

#include <iomanip>
#include <iostream>

using namespace snu;

ClassImp(KTrigger)

/**
 *Default constructor.
 */
  

KTrigger::KTrigger() : KParticle(),
		       k_HLTInsideDatasetTriggerNames(0), k_HLTInsideDatasetTriggerDecisions(0), k_HLTInsideDatasetTriggerPrescales(0)    
{

}

/**
 * Copy constructor.
 */
KTrigger::KTrigger(const KTrigger& trig): 
  KParticle(trig),
  k_HLTInsideDatasetTriggerNames (trig.k_HLTInsideDatasetTriggerNames),
  k_HLTInsideDatasetTriggerDecisions(trig.k_HLTInsideDatasetTriggerDecisions),
  k_HLTInsideDatasetTriggerPrescales(trig.k_HLTInsideDatasetTriggerPrescales)
{
  
}


KTrigger::~KTrigger()
{
}

void KTrigger::Reset()
{
  KParticle::Reset();
  k_HLTInsideDatasetTriggerNames.clear();
  k_HLTInsideDatasetTriggerDecisions.clear();
  k_HLTInsideDatasetTriggerPrescales.clear();
    
}

KTrigger& KTrigger::operator= (const KTrigger& p)
{
    if (this != &p) {
      KParticle::operator=(p);
      k_HLTInsideDatasetTriggerNames = p.GetHLTInsideDatasetTriggerNames();
      k_HLTInsideDatasetTriggerDecisions = p.GetHLTInsideDatasetTriggerDecisions();
      k_HLTInsideDatasetTriggerPrescales = p.GetHLTInsideDatasetTriggerPrescales();
      
    }
    
    return *this;
}

void KTrigger::SetHLTInsideDatasetTriggerNames(std::vector<std::string> names){

  k_HLTInsideDatasetTriggerNames = names;
}

void KTrigger::SetHLTInsideDatasetTriggerDecisions(std::vector<bool>dec) {
  k_HLTInsideDatasetTriggerDecisions = dec;
}


void KTrigger::SetHLTInsideDatasetTriggerPrescales(std::vector<int> pre){

  k_HLTInsideDatasetTriggerPrescales = pre;
}




