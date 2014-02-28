#ifndef _SKTree_KEvent_H__
#define _SKTree_KEvent_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include "TObject.h"

namespace snu {
  
  class KEvent : public TObject{
  public:
    KEvent();
    
    ///Copy constructor
    KEvent(const KEvent& el);
    
    ///Destructor    
    ~KEvent() ;

    KEvent& operator= (const KEvent& obj);
    
    void SetMET(double met);
    void SetWeight(double weight);
    void SetMETphi(double metphi);
    void SetNVertices(int nvert);
    void SetVertexIndex(int ivertex);
    void SetVertexIsFake(bool isfakeV);
    void SetIsGoodEvent(bool isgood);
    void SetVertexX(double vX);
    void SetVertexY(double vY);
    void SetVertexZ(double vZ);    
    void SetJetRho(double jetrho);    
    void SetIsPrimaryVertex(bool isprimary);
    
    void SetEventNumber(int ev);
    void SetRunNumber(int rn);
    void SetIsData(bool isdata);
    void SetIsTrackingFailure(bool fail);
    void SetPassTrackingFailureFilter(bool pass) ;
    void SetPassBeamHaloFilterLoose(bool pass);
    void SetPassBeamHaloFilterTight(bool pass);
    void SetPassBadEESupercrystalFilter(bool pass);
    void SetPassEcalDeadCellBoundaryEnergyFilter(bool pass);
    void SetPassEcalDeadCellTriggerPrimitiveFilter(bool pass);
    void SetPassEcalLaserCorrFilter(bool pass);
    void SetPassHBHENoiseFilter(bool pass);
    void SetPassHcalLaserEventFilter(bool pass);
    void SetPileUpInteractionsTrue(double npu);
				   
    
    inline Double_t MET() const {return k_MET;}
    inline Double_t METphi() const {return k_METphi;}
    inline Double_t JetRho() const {return k_jetrho;}
    inline Double_t MCWeight() const{return k_mcweight;}
    inline Int_t nVertices()  const {return k_nvertices;}
    inline Int_t VertexIndex()  const {return k_ivertex;}
    inline Bool_t IsFakeVertex() const {return k_isfakeV;}
    inline Bool_t HasGoodPrimaryVertex() const {return k_isgoodevent;}
    
    inline Bool_t IsPrimaryVertex() const {return k_isprimaryvertex;}
    inline Double_t VertexX() const {return k_vertexX;}
    inline Double_t VertexY() const {return k_vertexY;}
    inline Double_t VertexZ() const {return k_vertexZ;}
    inline Int_t IsData() const {return k_isData;}
    inline Int_t EventNumber() const {return k_EventNumber;}
    inline Int_t RunNumber() const {return k_RunNumber;}
    inline Bool_t IsTrackingFailure() const {return k_isTrackingFailure ;}
    inline Bool_t   PassTrackingFailureFilter() const {return  k_passTrackingFailureFilter ;}
    inline Bool_t   PassBeamHaloFilterLoose() const {return   k_passBeamHaloFilterLoose;}
    inline Bool_t   PassBeamHaloFilterTight() const {return   k_passBeamHaloFilterTight;}
    inline Bool_t   PassBadEESupercrystalFilter() const {return  k_passBadEESupercrystalFilter ;}
    inline Bool_t   PassEcalDeadCellBoundaryEnergyFilter() const {return  k_passEcalDeadCellBoundaryEnergyFilter ;}
    inline Bool_t   PassEcalDeadCellTriggerPrimitiveFilter() const {return   k_passEcalDeadCellTriggerPrimitiveFilter;}
    inline Bool_t   PassEcalLaserCorrFilter() const {return    k_passEcalLaserCorrFilter;}
    inline Bool_t   PassHBHENoiseFilter() const {return  k_passHBHENoiseFilter ;}
    inline Bool_t   PassHcalLaserEventFilter() const {return  k_passHcalLaserEventFilter ;}
    inline Double_t PileUpInteractionsTrue() const{ return k_PileUpInteractionsTrue;}

				   
    virtual void Reset();    
  protected:
    /// Reset function.                                                                  
    
  private:
    /// decalre private functions
    
    Int_t k_EventNumber, k_RunNumber,k_nvertices, k_ivertex;
    Double_t k_MET, k_vertexX,k_vertexY,k_vertexZ, k_METphi, k_jetrho, k_mcweight;
    Bool_t k_isfakeV, k_isgoodevent,k_isData, k_isprimaryvertex;
    Bool_t k_isTrackingFailure, k_passTrackingFailureFilter, k_passBeamHaloFilterLoose,k_passBeamHaloFilterTight, k_passBadEESupercrystalFilter, k_passEcalDeadCellBoundaryEnergyFilter, k_passEcalDeadCellTriggerPrimitiveFilter, k_passEcalLaserCorrFilter, k_passHBHENoiseFilter, k_passHcalLaserEventFilter;
    Double_t  k_PileUpInteractionsTrue;
    

    ClassDef(KEvent,3)
  }; 
  
}//namespace snu

#endif
