#ifndef KGenJet_H__
#define KGenJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KGenJet : public KParticle {
  public:
    KGenJet();
    
    ///Copy constructor
    KGenJet(const KGenJet& jet);
    
    ///Destructor    
    virtual ~KGenJet() ;

    ///Assignment operator                                                              
    KGenJet& operator= (const KGenJet& obj);
    
    void SetGenJetP(float p);
    void SetGenJetEMF(float p);
    void SetGenJetHADF(float p);
    void SetGenJetPDGID(int p);
 
    inline Float_t P() const {return k_genjet_p;}
    inline Float_t EMF() const {return k_genjet_emf;}
    inline Float_t HADF() const {return k_genjet_hadf;}
    inline Int_t    PdgId() const {return k_genjet_pdgid;}
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    Float_t k_genjet_p, k_genjet_emf, k_genjet_hadf;
    Int_t k_genjet_pdgid;
    ClassDef(KGenJet,4)
  }; 
  

}//namespace snu

#endif
