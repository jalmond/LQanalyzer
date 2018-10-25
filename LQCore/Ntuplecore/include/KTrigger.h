#ifndef KTrigger_H
#define KTrigger_H

#include <string>
#include <vector>
#include "TObject.h"

namespace snu {
  
  class KTrigger  : public TObject {
  public:
    
    KTrigger();
    
    ///Copy constructor
    KTrigger(const KTrigger& trig);
    
    ///Destructor    
    ~KTrigger() ;
    
    KTrigger& operator= (const KTrigger& obj);

    void SetHLTInsideDatasetTriggerNames(std::vector<std::string> names);
    void SetHLTInsideDatasetTriggerDecisions(std::vector<bool>  dec);
    void SetHLTInsideDatasetTriggerPrescales(std::vector<int> pre);
    
    inline std::vector<std::string> GetHLTInsideDatasetTriggerNames() const {return k_HLTInsideDatasetTriggerNames;}
    inline std::vector<bool> GetHLTInsideDatasetTriggerDecisions() const {return k_HLTInsideDatasetTriggerDecisions ;}
    inline std::vector<int> GetHLTInsideDatasetTriggerPrescales() const {return k_HLTInsideDatasetTriggerPrescales;}
    /// Reset function.                                                                  
    virtual void Reset();

  private:
    /// decalre private functions
    
    std::vector<std::string> k_HLTInsideDatasetTriggerNames;
    std::vector<bool> k_HLTInsideDatasetTriggerDecisions;
    std::vector<int> k_HLTInsideDatasetTriggerPrescales;

    ClassDef(KTrigger,2)
  }; 
  
}//namespace snu

#endif
