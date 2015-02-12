#ifndef _SKTREE_KPARTICLE_H__
#define _SKTREE_KPARTICLE_H__

//#include <iosfwd>
#include <string>

#include "TLorentzVector.h"

namespace snu {
  
  /**
   * @brief Base class for 4-vector based particles.
   *
   * Includes functionality for sorting based on transverse momentum.  The charge
   * information is included to allow C++ vectors of particles (e.g. electrons and
   * muons) to be cast to KParticle.  i.e. vectors of KParticles can contain both
   * electrons and muons in a single list.
   */
  class KParticle : public TLorentzVector {
  public:
    
    enum PartType{notfake, jet, cjet, bjet, chargemisid, chargemisid_photonconv, photonfake, nonfake_photonconv,  NOPARTICLE, unknown, fromtau,misidmuon};
    enum LooseTight{Loose, Tight, Other};
    
    
    ///Default Constructor with a 0 4-vector.
    KParticle();
    
    ///TLorentzVector copy constructor.
    KParticle(const TLorentzVector& p);
    
    ///Copy constructor.
    KParticle(const KParticle& p);
    
    ///Construct from 4-vector components
    KParticle(Double_t px, Double_t py, Double_t pz, Double_t e);
  
    ///So far the destructor does nothing.
    virtual ~KParticle();
    
    ///Charge of the particle.
    Int_t Charge() const;    
    // Type of particle
    PartType GetType() const;
    
    // is particle loose or tight in definition
    LooseTight looseTight() const;
    
    // particle index
    int ParticleIndex() const; 

    // index of mother particle
    int MotherIndex() const;
    
    // index of daughter particle
    int NDaughter() const;
    
    int MotherPdgId() const;
  
  
    ///Set the class members of the particle.
    void SetCharge(Int_t c);        
    void SetLooseTight( LooseTight istight);
    void SetType(PartType partType);
    void SetTruthParticleIndex(int truemu_index);
    void SetMotherIndex(int iMother);
    void SetMotherPdgId(int MotherPDGID);
    void SetNDaughter(int iDaughter);
  
  
    ///So we know what type of particle this is at run time.
    virtual std::string Type() const;
  
    ///Works with operator<< to allow the printing of KParticle to screen.
    virtual std::ostream& PrintContent(std::ostream& o) const;
    
    ///Method for comparing objects based on transverse momentum.
    bool operator<(const KParticle& p) const;
    
    ///Method for comparing objects based on transverse momentum.
    bool operator>(const KParticle& p) const;
    
    ///In order to minimise temporaries in operator+
    KParticle& operator+=(const KParticle& p);
    
    ///Assignment operator uses KParticle copy constructor
    KParticle& operator=(const KParticle& p);
    
  
  protected:
    ///Function to reset any private members - overridden by derived class.
    virtual void Reset();
    
  private:
    
    PartType partType_;
    LooseTight looseTight_;    
    Int_t k_index, k_mindex, k_dindex, k_mother_pdgid;
    ///Private member variable to hold the charge.
    Int_t m_charge;
  
    
  ClassDef(KParticle,6);
  }; // class KParticle
  
} // namespace snu


std::ostream& operator<< (std::ostream& os, const snu::KParticle& o);

const snu::KParticle operator+ (const snu::KParticle& lhs,
        const snu::KParticle& rhs);

#endif
