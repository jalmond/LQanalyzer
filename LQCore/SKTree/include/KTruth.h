#ifndef _SKTree_KTruth_H__
#define _SKTree_KTruth_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KTruth : public KParticle {
  public:
    KTruth();
    
    ///Copy constructor
    KTruth(const KTruth& el);
    
    ///Destructor    
    virtual ~KTruth() ;
  
    KTruth& operator= (const KTruth& obj);
    
    
    void SetIndex(int index);
    void SetParticlePdgId(double pdgid);
    void SetParticleStatus(double status);
    void SetParticleIndexMother(double index_mum);

    
    inline Double_t GetIndex() const {return k_gen_index;}
    inline Int_t PdgId() const {return k_gen_pdgid;}
    inline Int_t GenStatus() const {return k_gen_status;}
    inline Int_t IndexMother() const {return k_gen_indexmum;}
    
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
    
    Int_t k_gen_pdgid, k_gen_status, k_gen_indexmum,  k_gen_index;

    ClassDef(KTruth,7)
  }; 
  
}//namespace snu

#endif
