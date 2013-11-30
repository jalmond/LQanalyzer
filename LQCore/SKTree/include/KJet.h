#ifndef _SKTree_KJet_H__
#define _SKTree_KJet_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TLorentzVector.h"

namespace snu {
  
  class KJet : public KParticle {
  public:
    KJet();
    
    ///Copy constructor
    KJet(const KJet& jet);
    
    ///Destructor    
    virtual ~KJet() ;

    ///Assignment operator                                                              
    KJet& operator= (const KJet& obj);
    
    void SetPassLooseID(int looseID);
    void SetNeutralEmEF(double neutEmEF);
    void SetNeutralHEF(double neutHEF);
    void SetChargedEmEF(double chargeEmEF);
    void SetChargedHEF(double chargeHEF);
    void SetChargedMult(int chargeMult);
    void SetJetNCon(int jetNconst);
    void SetJetSecVertBtag(double svbt);
    void SetPFJetTrackCountingHighPurBTag(double tchpt);
    void SetPFJetJetProbabilityBTag(double JP);
    
    void SetClosestVertW3DSep(double cv3ds);
    void SetPFJetClosestVertexWeightedXYSeparation(double cvxys);
    void SetPFJetClosestVertexWeightedZSeparation(double cvzs);

    
    inline Int_t PassLooseID() const {return k_passLooseID;}
    inline Double_t NeutralEmEF() const {return k_neutralEmEF;}
    inline Double_t NeutralHEF() const {return k_neutralHEF;}
    inline Double_t ChargedEmEF() const {return k_chargeEmEF;}
    inline Double_t ChargedHEF() const {return k_chargeHEF;}
    inline Int_t ChargedMultiplicity() const {return k_chargeMult;}
    inline Int_t Nconstituents() const {return k_jetNconst;}
    inline Double_t CombinedSecVertexBtag() const {return k_JetSecVertBtag;}
    inline Double_t PFJetTrackCountingHighPurBTag() const {return k_TCHPT;}
    inline Double_t JetRho() const {return k_closest3Dsep;}
    inline Double_t BtagProb() const {return k_JetProbBtag;}
    inline Double_t ClosestXYsep() const {return k_closestXYsep;}
    inline Double_t ClosestZsep() const {return k_closestZsep;}


  protected:
    /// Reset function.                                                                  
    virtual void Reset();    
    
  private:
    
    Double_t k_neutralEmEF ,k_neutralHEF , k_chargeEmEF ,k_chargeHEF,k_closest3Dsep ,k_JetSecVertBtag, k_TCHPT, k_JetProbBtag, k_closestXYsep, k_closestZsep  ;
    Int_t  k_passLooseID ,k_chargeMult,k_jetNconst;
                        
      
    

    ClassDef(KJet,1)
  }; 
  

}//namespace snu

#endif
