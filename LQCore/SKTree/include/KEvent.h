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
    
    /// MET variabkes
    void SetPFMET(double met); ///defailt MET for analysis
    void SetPFMETphi(double metphi);
    void SetPFMETRaw(double met); 
    void SetPFMETRawphi(double phi); 
    void SetPFMETType1(double met);
    void SetPFMETType1phi(double phi);
    void SetPFMETType01(double met); 
    void SetPFMETType01phi(double phi); 
    void SetPFSumET(double sumet);
    
    void SetTCMET(double met); 
    void SetTCMETphi(double metphi);
    void SetTCSumET(double sumet);
    
    void SetCaloMET(double met);
    void SetCaloMETphi(double metphi);
    void SetCaloSumET(double sumet);
    
    /// systematics PF
    void SetPFMETElectronEnDown (double met_elen_down);
    void SetPFMETElectronEnUp (double met_elen_up);
    void SetPFMETJetEnDown (double met_jetem_down);
    void SetPFMETJetEnUp (double met_jetem_up);
    void SetPFMETJetResDown (double  met_jetres_down);
    void SetPFMETJetResUp (double  met_jetres_up);
    void SetPFMETMuonEnDown (double met_muonen_down);    
    void SetPFMETMuonEnUp (double met_muonen_up);    
    void SetPFMETUnclusteredDown  (double met_unclust_down);
    void SetPFMETUnclusteredUp  (double met_unclust_up);
    
    /// GENMET
    void SetGenMETTrue( double genmettrue);
    void SetGenMETPhiTrue( double genmetphitrue);
    void SetGenSumEtTrue( double gensumettrue);
    void SetGenMETCalo( double genmetcalo);
    void SetGenMETPhiCalo( double genmetphicalo);
    void SetGenSumEtCalo( double gensumetcalo);

    
    /// PDF
    void SetPDFCTEQWeight( double pdf);
    void SetPDFMSTWWeight( double pdf);
    void SetPDFNNPDFWeight( double pdf);
    
    /// Process ID
    void SetProcessID(int id);
    
    /// Vertex
    void SetNVertices(int nvert);
    void SetVertexIndex(int ivertex);
    void SetVertexIsFake(bool isfakeV);
    void SetIsGoodEvent(bool isgood);
    void SetVertexX(double vX);
    void SetVertexY(double vY);
    void SetVertexZ(double vZ);    
    void SetIsPrimaryVertex(bool isprimary);

    /// Event
    void SetWeight(double weight);
    
    void SetEventNumber(int ev);
    void SetRunNumber(int rn);
    void SetIsData(bool isdata);
    
    // Jet rhos
    void SetJetRho(double jetrho);    
    
    /// MET filters
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

    /// PileUp reweighting (only in MC)
    void SetPileUpInteractionsTrue(double npu);
				   
    
    //// Functions to call in analysis code/selection code
    
    /// MET variables
    inline Double_t PFMET() const {return k_PF_MET;}
    inline Double_t PFMETRaw() const {return k_PF_METraw;}
    inline Double_t PFMETType1() const {return k_PF_METtype1;}
    inline Double_t PFMETType01() const {return k_PF_METtype01;}

    inline Double_t PFMETphi() const {return k_PF_METphi;}
    inline Double_t PFMETRawphi() const {return k_PF_METrawphi;}
    inline Double_t PFMETType1phi() const {return k_PF_METtype1phi;}
    inline Double_t PFMETType01phi() const {return k_PF_METtype01phi;}

    inline Double_t PFSumET() const {return k_PF_SumET;}
    
    inline Double_t TCMET() const {return k_tc_MET;}
    inline Double_t TCMETphi() const {return k_tc_METphi;}
    inline Double_t TCSumET() const {return k_tc_SumET;}

    inline Double_t CaloMET() const {return k_calo_MET;}
    inline Double_t CaloMETphi() const {return k_calo_METphi;}
    inline Double_t CaloSumET() const {return k_calo_SumET;}
    
    inline Double_t PFMET_El_EnUp() const {return k_PF_MET_el_enup;}
    inline Double_t PFMET_El_EnDown() const {return k_PF_MET_el_endown;}
    inline Double_t PFMET_Jet_EnUp() const {return k_PF_MET_jet_enup;}
    inline Double_t PFMET_Jet_EnDown() const {return k_PF_MET_jet_endown;}
    inline Double_t PFMET_Jet_ResUp() const {return k_PF_MET_jet_resup;}
    inline Double_t PFMET_Jet_ResDown() const {return k_PF_MET_jet_resdown;}
    inline Double_t PFMET_Muon_EnUp() const {return k_PF_MET_muon_enup;}
    inline Double_t PFMET_Muon_EnDown() const {return k_PF_MET_muon_endown;}
    inline Double_t PFMET_Unclust_Up() const {return k_PF_MET_unclust_up;}
    inline Double_t PFMET_Unclust_Down() const {return k_PF_MET_unclust_down;}
    
    /// PDF 
    inline Double_t PDFCTEQWeight() const {return k_pdf_cteq;}
    inline Double_t PDFMSTWWeight() const {return k_pdf_mstw;}
    inline Double_t PDFNNPDFWeight() const {return k_pdf_nnpdf;}
    
    
    /// ProcessID
    inline Int_t ProcessID()  const {return k_process_id;}
    /// Jet rho
    inline Double_t JetRho() const {return k_jetrho;}

    /// Event specific
    inline Double_t MCWeight() const{return k_mcweight;}
    inline Int_t IsData() const {return k_isData;}
    inline Int_t EventNumber() const {return k_EventNumber;}
    inline Int_t RunNumber() const {return k_RunNumber;}
    
    // Vertex
    inline Int_t nVertices()  const {return k_nvertices;}
    inline Int_t VertexIndex()  const {return k_ivertex;}
    inline Bool_t IsFakeVertex() const {return k_isfakeV;}
    inline Bool_t HasGoodPrimaryVertex() const {return k_isgoodevent;}
    inline Bool_t IsPrimaryVertex() const {return k_isprimaryvertex;}
    inline Double_t VertexX() const {return k_vertexX;}
    inline Double_t VertexY() const {return k_vertexY;}
    inline Double_t VertexZ() const {return k_vertexZ;}

    inline Double_t GenMETTrue() const {return k_genmettrue;}
    inline Double_t GenMETPhiTrue() const {return k_genmetphitrue;}
    inline Double_t GenSumEtTrue() const {return k_gensumettrue;}
    inline Double_t GenMETCalo() const {return k_genmetcalo;}
    inline Double_t GenMETPhiCalo() const {return k_genmetphicalo;}
    inline Double_t GenSumEtCalo() const {return k_gensumetcalo;}
    
    /// MET filters
    inline Bool_t   IsTrackingFailure() const {return k_isTrackingFailure ;}
    inline Bool_t   PassTrackingFailureFilter() const {return  k_passTrackingFailureFilter ;}
    inline Bool_t   PassBeamHaloFilterLoose() const {return   k_passBeamHaloFilterLoose;}
    inline Bool_t   PassBeamHaloFilterTight() const {return   k_passBeamHaloFilterTight;}
    inline Bool_t   PassBadEESupercrystalFilter() const {return  k_passBadEESupercrystalFilter ;}
    inline Bool_t   PassEcalDeadCellBoundaryEnergyFilter() const {return  k_passEcalDeadCellBoundaryEnergyFilter ;}
    inline Bool_t   PassEcalDeadCellTriggerPrimitiveFilter() const {return   k_passEcalDeadCellTriggerPrimitiveFilter;}
    inline Bool_t   PassEcalLaserCorrFilter() const {return    k_passEcalLaserCorrFilter;}
    inline Bool_t   PassHBHENoiseFilter() const {return  k_passHBHENoiseFilter ;}
    inline Bool_t   PassHcalLaserEventFilter() const {return  k_passHcalLaserEventFilter ;}

    //Pileup reweighting
    inline Double_t PileUpInteractionsTrue() const{ return k_PileUpInteractionsTrue;}
    
    
    virtual void Reset();    
  protected:
    /// Reset function.                                                                  
    
  private:
    /// decalre private functions
    
    Int_t    k_EventNumber, k_RunNumber,k_nvertices, k_ivertex, k_process_id;
    Double_t k_vertexX,k_vertexY,k_vertexZ,  k_jetrho, k_mcweight;
    Double_t k_pdf_cteq,k_pdf_mstw, k_pdf_nnpdf;
    Double_t k_genmettrue, k_genmetphitrue,k_gensumettrue, k_genmetcalo, k_genmetphicalo,k_gensumetcalo;
    Double_t k_PF_MET, k_PF_METphi, k_PF_SumET;
    Double_t k_PF_METraw, k_PF_METtype1, k_PF_METtype01;
    Double_t k_PF_METrawphi, k_PF_METtype1phi, k_PF_METtype01phi;
    Double_t k_tc_MET, k_tc_METphi, k_tc_SumET;
    Double_t k_calo_MET, k_calo_METphi, k_calo_SumET;
    Double_t k_PF_MET_el_enup,k_PF_MET_el_endown, k_PF_MET_jet_enup,k_PF_MET_jet_endown, k_PF_MET_jet_resup,k_PF_MET_jet_resdown, k_PF_MET_muon_enup,k_PF_MET_muon_endown, k_PF_MET_unclust_up,k_PF_MET_unclust_down;
    
    Bool_t k_isfakeV;
    Bool_t k_isgoodevent,k_isData, k_isprimaryvertex;
    Bool_t k_isTrackingFailure, k_passTrackingFailureFilter, k_passBeamHaloFilterLoose,k_passBeamHaloFilterTight, k_passBadEESupercrystalFilter, k_passEcalDeadCellBoundaryEnergyFilter, k_passEcalDeadCellTriggerPrimitiveFilter, k_passEcalLaserCorrFilter, k_passHBHENoiseFilter, k_passHcalLaserEventFilter;
    Double_t  k_PileUpInteractionsTrue;
    

    ClassDef(KEvent,9)
  }; 
  
}//namespace snu

#endif
