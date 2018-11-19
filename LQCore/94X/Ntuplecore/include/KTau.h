#ifndef KTau_H__
#define KTau_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KTau : public KParticle {
  public:

    KTau();
    
    ///Copy constructor
    KTau(const KTau& muon);
    
    ///Destructor    
    virtual ~KTau() ;

    KTau& operator= (const KTau& obj);

    void SetIsPF(int ispf);
    
    inline Int_t IsPF() const {return k_ispf;}
    
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
    
    Int_t k_ispf;
    //Double_t k_pterror, k_etaerror , k_isor03ch, k_isor03n, k_isor03ph;


    ClassDef(KTau,1)
  }; 
  
}//namespace snu

#endif
