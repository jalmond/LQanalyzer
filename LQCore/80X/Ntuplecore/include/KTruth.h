#ifndef KTruth_H__
#define KTruth_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KTruth : public KParticle {
  public:

    enum status_flag{isprompt=0,
		     isdecayedleptonhadron=1,
		     istaudecayproduct=2,
		     isprompttaudecayproduct=3,
		     isdirecthadrondecayproduct=4,
		     ishardprocess=5,
		     fromhardprocess=6,
		     fromhardprocess_beforeFSR=7};
      
    

    KTruth();
    
    ///Copy constructor
    KTruth(const KTruth& el);
    
    ///Destructor    
    virtual ~KTruth() ;
  
    KTruth& operator= (const KTruth& obj);
    
    void SetStatusFlag(double iflag);
    void SetParticlePdgId(int pdgid);
    void SetParticleStatus(int status);
    void SetParticleIndexMother(int index_mum);
    
    Bool_t ReadStatusFlag(int which_flag) const;

    inline Bool_t StatusFlag(KTruth::status_flag iflag) const {
      /// index for this->ReadStatusFlag = number of status_flag - enum<flag>
      /// Hard coded for now
      if(iflag==isprompt) return this->ReadStatusFlag(7);
      if(iflag==isdecayedleptonhadron) return this->ReadStatusFlag(6);
      if(iflag==istaudecayproduct) return this->ReadStatusFlag(5);
      if(iflag==isprompttaudecayproduct) return this->ReadStatusFlag(4);
      if(iflag==isdirecthadrondecayproduct) return this->ReadStatusFlag(3);
      if(iflag==ishardprocess) return this->ReadStatusFlag(2);
      if(iflag==fromhardprocess) return this->ReadStatusFlag(1);
      if(iflag==fromhardprocess_beforeFSR) return this->ReadStatusFlag(0);
      exit (1);
   }

    inline Double_t StatusFlag() const {return k_gen_statusflag;}
    inline Int_t PdgId() const {return k_gen_pdgid;}
    inline Int_t GenStatus() const {return k_gen_status;}
    inline Int_t IndexMother() const {return k_gen_indexmum;}
    
  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    /// decalre private functions
    
    Int_t k_gen_pdgid, k_gen_status, k_gen_indexmum,  k_gen_index;
    Double_t k_gen_statusflag;
    ClassDef(KTruth,10)
  }; 
  
}//namespace snu

#endif
