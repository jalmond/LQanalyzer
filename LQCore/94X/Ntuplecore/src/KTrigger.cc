#include "KTrigger.h"

#include <iomanip>
#include <iostream>

using namespace snu;

ClassImp(KTrigger)

/**
 *Default constructor.
 */
  

KTrigger::KTrigger() : TObject(),
		       k_HLTInsideDatasetTriggerNames(0)
{

}

/**
 * Copy constructor.
 */
KTrigger::KTrigger(const KTrigger& trig): 
  TObject(),
  k_HLTInsideDatasetTriggerNames (trig.k_HLTInsideDatasetTriggerNames)
{
  
}


KTrigger::~KTrigger()
{
}

void KTrigger::Reset()
{
  k_HLTInsideDatasetTriggerNames.clear();
    
}

KTrigger& KTrigger::operator= (const KTrigger& p)
{
    if (this != &p) {
      k_HLTInsideDatasetTriggerNames = p.GetHLTInsideDatasetTriggerNames();
      
    }
    
    return *this;
}

void KTrigger::SetHLTInsideDatasetTriggerNames(std::vector<std::string> names){

  k_HLTInsideDatasetTriggerNames = names;
}



