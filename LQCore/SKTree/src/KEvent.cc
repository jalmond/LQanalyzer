#include "KEvent.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KEvent)

/**
 *Default constructor.
 */
KEvent::KEvent() :
  TObject(),
  k_EventNumber(0),
  k_RunNumber(0),
  k_nvertices(0),
  k_lumisec(0),
  k_ngoodvertices(0),
  k_pdf_id1(0),
  k_pdf_id2(0),

  k_vertexX(0.),
  k_vertexY(0.),
  k_vertexZ(0.), 
  k_vertexNDOF(0.), 
  k_mcweight(0.),
  k_lheweight(0.),
  k_pdf_q(0.),
  k_pdf_x1(0.),
  k_pdf_x2(0.),

  k_PF_MET(0.), 
  k_PF_METphi(0.),
  k_PF_SumET(0.), 
  k_Puppi_MET(0.),
  k_Puppi_METphi(0.),
  k_Puppi_SumET(0.),
  k_NoHF_MET(0.),
  k_NoHF_METphi(0.),
  k_NoHF_SumET(0.),
  k_PfMva_MET(0.),
  k_PfMva_METphi(0.),
  k_PfMva_SumET(0.),
  
  k_isData(false), 
  k_isgoodevent(false),

  k_passBadEESupercrystalFilter(false),
  k_passCSCHaloFilterTight(false),
  k_passEcalDeadCellTriggerPrimitiveFilter(false),
  k_passHBHENoiseFilter(false),
  k_PileUpInteractionsTrue(0.),
  k_pu_weight(0.),
  k_pu_p_weight(0.),
  k_pu_m_weight(0.)
{

}

/**
 * Copy constructor.
 */
KEvent::KEvent(const KEvent& ev) :
  TObject(),
  k_EventNumber(ev.k_EventNumber),
  k_RunNumber(ev.k_RunNumber),
  k_nvertices(ev.k_nvertices),
  k_lumisec(ev.k_lumisec),
  k_ngoodvertices(ev.k_ngoodvertices),
  k_pdf_id1(ev.k_pdf_id1),
  k_pdf_id2(ev.k_pdf_id2),

  k_vertexX(ev.k_vertexX),
  k_vertexY(ev.k_vertexY),
  k_vertexZ(ev.k_vertexZ),
  k_vertexNDOF(ev.k_vertexNDOF),
  k_mcweight(ev.k_mcweight),
  k_lheweight(ev.k_lheweight),
  k_pdf_q(ev.k_pdf_q),
  k_pdf_x1(ev.k_pdf_x1),
  k_pdf_x2(ev.k_pdf_x2),

  k_PF_MET(ev.k_PF_MET),
  k_PF_METphi(ev.k_PF_METphi),
  k_PF_SumET(ev.k_PF_SumET),
  k_Puppi_MET(ev.k_Puppi_MET),
  k_Puppi_METphi(ev.k_Puppi_METphi),
  k_Puppi_SumET(ev.k_Puppi_SumET),
  k_NoHF_MET(ev.k_NoHF_MET),
  k_NoHF_METphi(ev.k_NoHF_METphi),
  k_NoHF_SumET(ev.k_NoHF_SumET),
  k_PfMva_MET(ev.k_PfMva_MET),
  k_PfMva_METphi(ev.k_PfMva_METphi),
  k_PfMva_SumET(ev.k_PfMva_SumET),

  k_isData(ev.k_isData),
  k_isgoodevent(ev.k_isgoodevent),

  k_passBadEESupercrystalFilter(ev.k_passBadEESupercrystalFilter),
  k_passCSCHaloFilterTight(ev.k_passCSCHaloFilterTight),
  k_passEcalDeadCellTriggerPrimitiveFilter(ev.k_passEcalDeadCellTriggerPrimitiveFilter),
  k_passHBHENoiseFilter(ev.k_passHBHENoiseFilter),
  k_PileUpInteractionsTrue(ev.k_PileUpInteractionsTrue),
  k_pu_weight(ev.k_pu_weight),
  k_pu_p_weight(ev.k_pu_p_weight),
  k_pu_m_weight(ev.k_pu_m_weight)
{
}


KEvent::~KEvent()
{
}

void KEvent::Reset()
{
  
  k_EventNumber= 0;
  k_RunNumber= 0;
  k_nvertices= 0;
  k_lumisec=0; 
  k_ngoodvertices= 0;
  k_pdf_id1=0;
  k_pdf_id2=0;

  k_vertexX= 0.;
  k_vertexY= 0.;
  k_vertexZ= 0.;
  k_vertexNDOF= 0.;
  k_mcweight= 0.;
  k_lheweight= 0.;
  k_pdf_q=0.;
  k_pdf_x1= 0.;
  k_pdf_x2=0.;

  k_PF_MET= 0.;
  k_PF_SumET= 0.;
  k_PF_METphi= 0.;
  k_Puppi_MET= 0; 
  k_Puppi_METphi= 0;
  k_Puppi_SumET= 0;
  k_NoHF_MET= 0;
  k_NoHF_METphi= 0;
  k_NoHF_SumET= 0;
  k_PfMva_MET= 0;
  k_PfMva_METphi= 0;
  k_PfMva_SumET= 0;


  k_isData= false;
  k_isgoodevent = false;

  k_passBadEESupercrystalFilter= false;
  k_passCSCHaloFilterTight= false;
  k_passEcalDeadCellTriggerPrimitiveFilter= false;
  k_passHBHENoiseFilter= false;
  k_PileUpInteractionsTrue = 0.;
  k_pu_weight = 0.;
  k_pu_p_weight=0.;
  k_pu_m_weight = 0.;


}



KEvent& KEvent::operator= (const KEvent& p)
{
    if (this != &p) {

      k_EventNumber=p.EventNumber();
      k_RunNumber=p.RunNumber();
      k_nvertices= p.nVertices();
      k_lumisec= p.LumiSection();
      k_ngoodvertices = p.nGoodVertices();
      k_pdf_id1 = p.Id1();
      k_pdf_id2 = p.Id2();
      
      k_vertexX=p.VertexX();
      k_vertexY=p.VertexY();
      k_vertexZ=p.VertexZ();
      k_vertexNDOF=p.VertexNDOF();
      k_mcweight = p.MCWeight();
      k_lheweight = p.LHEWeight();
      k_pdf_q = p.Q();
      k_pdf_x1 = p.x1();
      k_pdf_x2 = p.x2();
      
      
      k_PF_MET= p.PFMET();
      k_PF_METphi= p.PFMETphi();
      k_PF_SumET = p.PFSumET();
      k_Puppi_MET= p.PuppiMET();
      k_Puppi_METphi= p.PuppiMETphi();
      k_Puppi_SumET = p.PuppiSumET();
      k_NoHF_MET= p.NoHFMET();
      k_NoHF_METphi= p.NoHFMETphi();
      k_NoHF_SumET = p.NoHFSumET();
      k_PfMva_MET= p.PfMvaMET();
      k_PfMva_METphi= p.PfMvaMETphi();
      k_PfMva_SumET = p.PfMvaSumET();

      k_isData=p.IsData();
      k_isgoodevent= p.HasGoodPrimaryVertex();

      k_passBadEESupercrystalFilter = p.PassBadEESupercrystalFilter();
      k_passCSCHaloFilterTight = p.PassCSCHaloFilterTight();
      k_passEcalDeadCellTriggerPrimitiveFilter = p.PassEcalDeadCellTriggerPrimitiveFilter();
      k_passHBHENoiseFilter = p.PassHBHENoiseFilter();
      k_PileUpInteractionsTrue = p.PileUpInteractionsTrue();
      k_pu_weight = p.PileUpWeight();
      k_pu_p_weight= p.PileUpWeightUp();
      k_pu_m_weight= p.PileUpWeightDown();
    }
    
    return *this;
}

//// SET CLASS VARIBALES

void KEvent::SetPassCSCHaloFilterTight(bool pass){
  k_passCSCHaloFilterTight = pass;
}

void KEvent::SetPassBadEESupercrystalFilter(bool pass){
  k_passBadEESupercrystalFilter = pass;
}


void KEvent::SetPassEcalDeadCellTriggerPrimitiveFilter(bool pass){
  k_passEcalDeadCellTriggerPrimitiveFilter = pass;
}

void KEvent::SetPassHBHENoiseFilter(bool pass){
  k_passHBHENoiseFilter= pass;
}

void KEvent::SetPileUpInteractionsTrue(double npu){
  k_PileUpInteractionsTrue = npu;
}

void KEvent::SetPUWeight(double puw){
  k_pu_weight = puw;
}

void KEvent::SetPUWeightMSigma(double puw){
  k_pu_m_weight = puw;
}

void KEvent::SetPUWeightPSigma(double puw){
  k_pu_p_weight = puw;
}



void KEvent::SetWeight(double mcweight){
  k_mcweight = mcweight;
}




void KEvent::SetEventNumber(int ev){
  k_EventNumber = ev;
}

void KEvent::SetRunNumber(int rn){
  k_RunNumber = rn;
}

void KEvent::SetIsData(bool isdata){
  k_isData = isdata;
}



//// Setting Missing ET variables
void KEvent::SetPFMET(double met){
  k_PF_MET = met;
}

void KEvent::SetPFMETphi(double metphi){
  k_PF_METphi = metphi;
}

void KEvent::SetPFSumET(double sumet){
  k_PF_SumET =sumet;
}

void KEvent::SetPuppiMET(double met){
  k_Puppi_MET = met;
}

void KEvent::SetPuppiMETphi(double metphi){
  k_Puppi_METphi = metphi;
}

void KEvent::SetPuppiSumET(double sumet){
  k_Puppi_SumET =sumet;
}

void KEvent::SetNoHFMET(double met){
  k_NoHF_MET = met;
}

void KEvent::SetNoHFMETphi(double metphi){
  k_NoHF_METphi = metphi;
}

void KEvent::SetNoHFSumET(double sumet){
  k_NoHF_SumET =sumet;
}


void KEvent::SetPfMvaMET(double met){
  k_PfMva_MET = met;
}

void KEvent::SetPfMvaMETphi(double metphi){
  k_PfMva_METphi = metphi;
}

void KEvent::SetPfMvaSumET(double sumet){
  k_PfMva_SumET =sumet;
}





/// Settizang Vertex Variables
void KEvent::SetNVertices(int nvert){
  k_nvertices = nvert;
}


void KEvent::SetLumiSection(int ls){
  k_lumisec = ls;
}



void KEvent::SetIsGoodEvent(int nvert){
  if(nvert > 0) k_isgoodevent = true;
  else k_isgoodevent = false;
}



/// Settizang Vertex Variables
void KEvent::SetNGoodVertices(int nvert){
  k_ngoodvertices = nvert;
}


void KEvent::SetVertexX(double vX){
  k_vertexX = vX;
}

void KEvent::SetVertexY(double vY){
  k_vertexY = vY;
}

void KEvent::SetVertexZ(double vZ){
  k_vertexZ = vZ;
}

void KEvent::SetVertexNDOF(double vNDOF){
  k_vertexNDOF = vNDOF;
}

void KEvent::SetGenId1(int id1){
  k_pdf_id1 = id1;
}

void KEvent::SetGenId2(int id2){
  k_pdf_id2 = id2;
}


void KEvent::SetGenQ(double q ){
  k_pdf_q = q;
}


void KEvent::SetGenX1(double x1){
  k_pdf_x1 = x1;
}


void KEvent::SetLHEWeight(double lw){
  k_lheweight = lw;
}

void KEvent::SetGenX2(double x2){
  k_pdf_x2 = x2;
}





