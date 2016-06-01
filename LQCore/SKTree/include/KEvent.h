#ifndef _SKTree_KEvent_H__
#define _SKTree_KEvent_H__

/// Local includes
#include "KParticle.h"

#include <iosfwd>
#include <string>
#include <vector>
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
    void SetPFMETx(double met); ///defailt MET for analysis
    void SetPFMETy(double met); ///defailt MET for analysis
    void SetPFMETphi(double metphi);
    void SetPFMETRaw(double met); 
    void SetPFMETxRaw(double met); 
    void SetPFMETyRaw(double met); 
    void SetPFMETRawphi(double phi); 
    void SetPFMETType1(double met);
    void SetPFMETType1phi(double phi);
    void SetPFMETType01(double met); 
    void SetPFMETType01phi(double phi); 
    void SetPFSumET(double sumet);
    
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
    void SetPDFCTEQWeight( std::vector<double> pdf);
    void SetPDFMSTWWeight( std::vector<double> pdf);
    void SetPDFNNPDFWeight( std::vector<double> pdf);
    
    /// Process ID
    void SetProcessID(int id);
    void SetLumiSection(int ls);
    /// Vertex
    void SetNVertices(int nvert);
    void SetVertexIndex(int ivertex);
    void SetVertexIsFake(bool isfakeV);
    void SetIsGoodEvent(bool isgood);
    void SetVertexX(double vX);
    void SetVertexY(double vY);
    void SetVertexZ(double vZ);    

    /// Event
    void SetWeight(double weight);
    
    void SetEventNumber(int ev);
    void SetRunNumber(int rn);
    void SetIsData(bool isdata);
    
    // Jet rhos
    void SetJetRho(double jetrho);    
    
    /// MET filters
    void SetIsTrackingFailure(bool fail);
    void SetIsBeamScraping(bool fail);
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
    inline Double_t PFMETx() const {return k_PF_METx;}
    inline Double_t PFMETy() const {return k_PF_METy;}
    inline Double_t PFMETRaw() const {return k_PF_METraw;}
    inline Double_t PFMETxRaw() const {return k_PF_METxraw;}
    inline Double_t PFMETyRaw() const {return k_PF_METyraw;}
    inline Double_t PFMETType1() const {return k_PF_METtype1;}
    inline Double_t PFMETType01() const {return k_PF_METtype01;}

    inline Double_t PFMETphi() const {return k_PF_METphi;}
    inline Double_t PFMETRawphi() const {return k_PF_METrawphi;}
    inline Double_t PFMETType1phi() const {return k_PF_METtype1phi;}
    inline Double_t PFMETType01phi() const {return k_PF_METtype01phi;}

    inline Double_t PFSumET() const {return k_PF_SumET;}
    
    
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
    inline std::vector<Double_t> PDFCTEQWeight() const {return k_pdf_cteq;}
    inline std::vector<Double_t> PDFMSTWWeight() const {return k_pdf_mstw;}
    inline std::vector<Double_t> PDFNNPDFWeight() const {return k_pdf_nnpdf;}
    
    
    /// ProcessID
    inline Int_t ProcessID()  const {return k_process_id;}
    inline Int_t LumiSection()  const {return k_lumisec;}
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
    inline Bool_t   IsBeamScraping() const {return k_isbeamscrape;}
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
    
    Int_t    k_EventNumber, k_RunNumber,k_nvertices, k_ivertex, k_process_id, k_lumisec;
    Double_t k_vertexX,k_vertexY,k_vertexZ;
    Double_t k_jetrho,k_mcweight;
    std::vector<Double_t> k_pdf_cteq,k_pdf_mstw, k_pdf_nnpdf;
    Double_t k_genmettrue, k_genmetphitrue,k_gensumettrue, k_genmetcalo, k_genmetphicalo,k_gensumetcalo;
    Double_t k_PF_MET, k_PF_METx,k_PF_METy,k_PF_METphi, k_PF_SumET;
    Double_t k_PF_METraw,k_PF_METxraw,k_PF_METyraw, k_PF_METrawphi,k_PF_METtype1, k_PF_METtype1phi,k_PF_METtype01,k_PF_METtype01phi;

    Double_t k_PF_MET_el_enup,k_PF_MET_el_endown, k_PF_MET_jet_enup,k_PF_MET_jet_endown, k_PF_MET_jet_resup,k_PF_MET_jet_resdown, k_PF_MET_muon_enup,k_PF_MET_muon_endown, k_PF_MET_unclust_up,k_PF_MET_unclust_down;


    Bool_t k_isfakeV,k_isgoodevent,k_isData;
    
    Bool_t k_isTrackingFailure,k_isbeamscrape, k_passTrackingFailureFilter, k_passBeamHaloFilterLoose,k_passBeamHaloFilterTight, k_passBadEESupercrystalFilter, k_passEcalDeadCellBoundaryEnergyFilter, k_passEcalDeadCellTriggerPrimitiveFilter, k_passEcalLaserCorrFilter, k_passHBHENoiseFilter, k_passHcalLaserEventFilter;
    Double_t  k_PileUpInteractionsTrue;
    

    ClassDef(KEvent,16)
  }; 
  
}//namespace snu

#endif
