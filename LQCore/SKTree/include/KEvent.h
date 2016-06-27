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


    enum json{missing=0,
	      silver=1,
	      gold=2};

    enum met_syst{None=0,
		  MuonEn=1,
		  ElectronEn=2,
		  JetEn=3,
		  JetRes=4,
		  Unclustered=5};

    enum met_type{pfmet=0,
		  puppi=1,
		  nohf=2,
		  pfmva=3};
    
    enum syst_dir{central=0,
		  down=1,
		  up=2};

    KEvent();
    
    ///Copy constructor
    KEvent(const KEvent& el);
    
    ///Destructor    
    ~KEvent() ;

    KEvent& operator= (const KEvent& obj);
    
    /// MET variabkes
    void SetMET(met_type type, double met, double metphi, double sumet); ///defailt MET for analysis
    // MET systematics
    void SetPFMETShift(syst_dir dir, met_syst type, double val);
    void SetPFSumETShift(syst_dir dir, met_syst type, double val);

    
    /// PDF
    void SetPDFWeights(std::vector<float> pdfw);
    void SetScaleWeights(std::vector<float> pdfw);
    
    /// Process ID
    void SetLumiSection(int ls);
    /// Vertex
    void SetNVertices(int nvert);
    void SetNGoodVertices(int nvert);
    void SetIsGoodEvent(int isgood);
    void SetVertexInfo(double vX , double vY, double vZ, double ndof);
    
    /// Event
    void SetWeight(double weight);
    void SetGenId(int  id1, int  id2);
    void SetLHEWeight(double  lhe);
    void SetGenX(double  x1, double  x2);
    void SetGenQ(double  Q);

    void SetEventNumber(int ev);
    void SetRunNumber(int rn);
    void SetIsData(bool isdata);
    
    
    /// MET filters
    void SetPassCSCHaloFilterTight(bool pass);
    void SetPassEcalDeadCellTriggerPrimitiveFilter(bool pass);
    void SetPassHBHENoiseFilter(bool pass);
    void SetPassBadEESupercrystalFilter(bool pass);

    /// PileUp reweighting (only in MC)
    void SetPileUpInteractionsTrue(double npu);
    void SetPUWeight(json type, syst_dir sys, double puweight);
    void SetAltPUWeight(json type, syst_dir sys, double puweight);
    void SetLumiMask(json type, int mask);
    void SetJSON(json type);

    void SetCatVersion(std::string cat);
    
    /// New for CAT v7-4-6 (silver/gold json files)
    Bool_t LumiMask(json js);
    Double_t PileUpWeight(json js, syst_dir dir=central);
    Double_t AltPileUpWeight(json js, syst_dir dir=central);
    Double_t PFMETShifted (met_syst type,syst_dir dir) const;
    Double_t PFSumETShifted(met_syst type,syst_dir dir) const;
    Double_t MET(met_type type=pfmet) const;
    Double_t METPhi(met_type type=pfmet) const;
    Double_t SumET(met_type type=pfmet) const;


    // To make backward compatible
    inline Double_t PFMET() const {return MET(pfmet);}
    //// Functions to call in analysis code/selection code

    
    inline std::string CatVersion() const {return k_catversion;}

    inline json GetJSON() const {return k_lumimask;}
    
    /// Lumi
    inline Int_t LumiSection()  const {return k_lumisec;}
    inline Int_t LumiMaskSilver() const {return k_lumi_mask_silver;}
    inline Int_t LumiMaskGold() const {return k_lumi_mask_gold;}

    
    /// Event specific
    inline Double_t MCWeight() const{return k_mcweight;}
    inline Int_t IsData() const {return k_isData;}
    inline Int_t EventNumber() const {return k_EventNumber;}
    inline Int_t RunNumber() const {return k_RunNumber;}
    
    // Vertex
    inline Int_t nVertices()  const {return k_nvertices;}
    inline Int_t nGoodVertices()  const {return k_ngoodvertices;}

    inline Bool_t HasGoodPrimaryVertex() const {return k_isgoodevent;}
    inline Double_t VertexX() const {return k_vertexX;}
    inline Double_t VertexY() const {return k_vertexY;}
    inline Double_t VertexZ() const {return k_vertexZ;}
    inline Double_t VertexNDOF() const {return k_vertexNDOF;}

    
    
    /// MET filters
    inline Bool_t   PassCSCHaloFilterTight() const {return   k_passCSCHaloFilterTight;}
    inline Bool_t   PassEcalDeadCellTriggerPrimitiveFilter() const {return   k_passEcalDeadCellTriggerPrimitiveFilter;}
    inline Bool_t   PassHBHENoiseFilter() const {return  k_passHBHENoiseFilter ;}
    inline Bool_t   PassBadEESupercrystalFilter() const {return  k_passBadEESupercrystalFilter ;}

    //Pileup reweighting
    inline Double_t PileUpInteractionsTrue() const{ return k_PileUpInteractionsTrue;}


    inline Double_t PileUpWeight_Silver(syst_dir sys) const{
      if(sys == central)return k_pu_silver_weight;
      else if(sys == up)return k_pu_silver_p_weight;
      else if(sys == down)return k_pu_silver_m_weight;
      else return -999.;
    }
    inline Double_t PileUpWeight_Gold(syst_dir sys) const{
      if(sys == central)return k_pu_gold_weight;
      else if(sys == up)return k_pu_gold_p_weight;
      else if(sys == down)return k_pu_gold_m_weight;
      else return -999.;
    }
    
    inline Double_t AltPileUpWeight_Gold(syst_dir sys) const{
      if(sys == central)return k_pu_gold_xs71000_weight;
      else if(sys == up)return k_pu_gold_xs71000_p_weight;
      else if(sys == down)return k_pu_gold_xs71000_m_weight;
      else return -999.;
    }

    inline Double_t LHEWeight() const{return k_lheweight;}
    inline Int_t Id1() const {return k_pdf_id1;}
    inline Int_t Id2() const {return k_pdf_id2;}
    inline Double_t Q() const {return k_pdf_q;}
    inline Double_t x1() const {return k_pdf_x1;}
    inline Double_t x2() const {return k_pdf_x2;}
    
    inline std::vector<Float_t> PdfWeights() const {return k_pdf_weights;}
    inline std::vector<Float_t> ScaleWeights() const {return k_scale_weights;}
    
    virtual void Reset();    
  protected:
    /// Reset function.                                                                  
    
  private:
    /// decalre private functions
    
    Int_t    k_EventNumber, k_RunNumber,k_nvertices,  k_lumisec, k_ngoodvertices,k_pdf_id1, k_pdf_id2, k_lumi_mask_silver, k_lumi_mask_gold;
    std::vector<Float_t> k_pdf_weights, k_scale_weights;
    Double_t k_vertexX,k_vertexY,k_vertexZ, k_vertexNDOF,  k_mcweight, k_lheweight, k_pdf_q, k_pdf_x1, k_pdf_x2;

    Double_t k_PF_MET, k_PF_METphi, k_PF_SumET ;
    Double_t k_NoHF_MET, k_NoHF_METphi, k_NoHF_SumET ;
    Double_t k_PF_MET_MuonEn_up,k_PF_MET_MuonEn_down; 
    Double_t k_PF_MET_ElectronEn_up,k_PF_MET_ElectronEn_down; 
    Double_t k_PF_MET_JetEn_up,k_PF_MET_JetEn_down, k_PF_SumET_JetEn_up, k_PF_SumET_JetEn_down; 
    Double_t k_PF_MET_JetRes_up,k_PF_MET_JetRes_down, k_PF_SumET_JetRes_up, k_PF_SumET_JetRes_down; 
    Double_t k_PF_MET_unclusteredEn_up,k_PF_MET_unclusteredEn_down, k_PF_SumET_unclusteredEn_up, k_PF_SumET_unclusteredEn_down; 

    Bool_t k_isData, k_isgoodevent;
    Bool_t k_passBadEESupercrystalFilter,k_passCSCHaloFilterTight,k_passEcalDeadCellTriggerPrimitiveFilter,  k_passHBHENoiseFilter;
    Double_t  k_PileUpInteractionsTrue, k_pu_silver_weight, k_pu_silver_p_weight, k_pu_silver_m_weight,k_pu_gold_weight, k_pu_gold_p_weight, k_pu_gold_m_weight, k_pu_gold_xs71000_weight, k_pu_gold_xs71000_p_weight, k_pu_gold_xs71000_m_weight;
    
    std::string k_catversion;
    json k_lumimask;    



    ClassDef(KEvent,25);
  }; 
  
}//namespace snu

#endif
