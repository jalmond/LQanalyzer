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
    void SetParticlePx(double px);
    void SetParticlePy(double py);
    void SetParticlePz(double pz);
    void SetParticleVx(double Vx);
    void SetParticleVy(double Vy);
    void SetParticleVz(double Vz);
    void SetParticlePdgId(double pdgid);
    void SetParticleStatus(double status);
    void SetParticleIndexMother(double index_mum);
    void SetParticleIndexDaughter(double index_dau);

    
    inline Double_t GetIndex() const {return k_gen_index;}
    inline Double_t GenPx() const {return k_gen_px;}
    inline Double_t GenPy() const {return k_gen_py;}
    inline Double_t GenPz() const {return k_gen_pz;}
    inline Double_t GenVx() const {return k_gen_vx;}
    inline Double_t GenVy() const {return k_gen_vy;}
    inline Double_t GenVz() const {return k_gen_vz;}
    inline Int_t PdgId() const {return k_gen_pdgid;}
    inline Int_t GenStatus() const {return k_gen_status;}
    inline Int_t IndexMother() const {return k_gen_indexmum;}
    inline Int_t IndexDaughter() const {return k_gen_indexdau;}
    
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
    
    Double_t k_gen_px, k_gen_py, k_gen_pz, k_gen_vx, k_gen_vy,k_gen_vz;
    Int_t k_gen_pdgid, k_gen_status, k_gen_indexmum, k_gen_indexdau, k_gen_index;

    ClassDef(KTruth,1)
  }; 
  
}//namespace snu

#endif
