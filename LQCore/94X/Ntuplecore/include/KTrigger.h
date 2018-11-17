#ifndef KTrigger_H__
#define KTrigger_H__

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
    
    inline std::vector<std::string> GetHLTInsideDatasetTriggerNames() const {return k_HLTInsideDatasetTriggerNames;}
    /// Reset function.                                                                  
    virtual void Reset();

  private:
    /// decalre private functions
    
    std::vector<std::string> k_HLTInsideDatasetTriggerNames;


    ClassDef(KTrigger,2)
  }; 
  
}//namespace snu

#endif
