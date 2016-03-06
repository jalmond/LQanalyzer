#ifndef _SKTree_KGenJet_H__
#define _SKTree_KGenJet_H__

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
    
    void SetGenJetP(double p);
    void SetGenJetEMF(double p);
    void SetGenJetHADF(double p);
    void SetGenJetPDGID(int p);
 
    inline Double_t P() const {return k_genjet_p;}
    inline Double_t EMF() const {return k_genjet_emf;}
    inline Double_t HADF() const {return k_genjet_hadf;}
    inline Int_t    PdgId() const {return k_genjet_pdgid;}
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    Double_t k_genjet_p, k_genjet_emf, k_genjet_hadf;
    Int_t k_genjet_pdgid;
    ClassDef(KGenJet,3)
  }; 
  

}//namespace snu

#endif
