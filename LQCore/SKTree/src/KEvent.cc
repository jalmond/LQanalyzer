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
  KParticle(),
  k_EventNumber(0),
  k_RunNumber(0),
  k_nvertices(0),
  k_ivertex(0),
  k_MET(0.), 
  k_vertexX(0.),
  k_vertexY(0.),
  k_vertexZ(0.), 
  k_METphi(0.), 
  k_jetrho(0.),
  k_mcweight(0.),
  k_isfakeV(false), 
  k_isgoodevent(false),
  k_isData(false), 
  k_isprimaryvertex(false),
  k_isTrackingFailure(false),
  k_passTrackingFailureFilter(false),
  k_passBeamHaloFilterLoose(false),
  k_passBadEESupercrystalFilter(false),
  k_passEcalDeadCellBoundaryEnergyFilter(false),
  k_passEcalDeadCellTriggerPrimitiveFilter(false),
  k_passEcalLaserCorrFilter(false),
  k_passHBHENoiseFilter(false),
  k_passHcalLaserEventFilter(false),
  k_PileUpInteractionsTrue(0.)
{

}

/**
 * Copy constructor.
 */
KEvent::KEvent(const KEvent& ev) :
  KParticle(ev),
  k_EventNumber(ev.k_EventNumber),
  k_RunNumber(ev.k_RunNumber),
  k_nvertices(ev.k_nvertices),
  k_ivertex(ev.k_ivertex),
  k_MET(ev.k_MET),
  k_vertexX(ev.k_vertexX),
  k_vertexY(ev.k_vertexY),
  k_vertexZ(ev.k_vertexZ),
  k_METphi(ev.k_METphi),
  k_jetrho(ev.k_jetrho),
  k_mcweight(ev.k_mcweight),
  k_isfakeV(ev.k_isfakeV),
  k_isgoodevent(ev.k_isgoodevent),
  k_isData(ev.k_isData),
  k_isprimaryvertex(ev.k_isprimaryvertex),
  k_isTrackingFailure(ev.k_isTrackingFailure),
  k_passTrackingFailureFilter(ev.k_passTrackingFailureFilter),
  k_passBeamHaloFilterLoose(ev.k_passBeamHaloFilterLoose),
  k_passBadEESupercrystalFilter(ev.k_passBadEESupercrystalFilter),
  k_passEcalDeadCellBoundaryEnergyFilter(ev.k_passEcalDeadCellBoundaryEnergyFilter),
  k_passEcalDeadCellTriggerPrimitiveFilter(ev.k_passEcalDeadCellTriggerPrimitiveFilter),
  k_passEcalLaserCorrFilter(ev.k_passEcalLaserCorrFilter),
  k_passHBHENoiseFilter(ev.k_passHBHENoiseFilter),
  k_passHcalLaserEventFilter(ev.k_passHcalLaserEventFilter),
  k_PileUpInteractionsTrue(ev.k_PileUpInteractionsTrue)
{
}


KEvent::~KEvent()
{
}

void KEvent::Reset()
{
  KParticle::Reset();
  k_isData=false;
  k_EventNumber= 0;
  k_RunNumber= 0;
  k_isprimaryvertex=0;
  k_MET=0.;
  k_METphi= 0.;
  k_vertexX=0.;
  k_vertexY=0.;
  k_vertexZ=0.;
  k_nvertices=0;
  k_jetrho=0.;
  k_isfakeV=false; 
  k_isgoodevent = false;
  k_mcweight= 0.;
}



KEvent& KEvent::operator= (const KEvent& p)
{
    if (this != &p) {
      KParticle::operator=(p);
      k_isData=p.IsData();
      k_EventNumber=p.EventNumber();
      k_RunNumber=p.RunNumber();
      k_isprimaryvertex=p.IsPrimaryVertex();
      k_MET= p.MET();
      k_METphi= p.METphi();
      k_vertexX=p.VertexX();
      k_vertexY=p.VertexY();
      k_vertexZ=p.VertexZ();
      k_nvertices= p.nVertices();
      k_isfakeV=p.IsFakeVertex(); 
      k_jetrho=p.JetRho();
      k_isgoodevent = p.HasGoodPrimaryVertex();
      k_mcweight = p.MCWeight();
      k_isTrackingFailure = p.IsTrackingFailure();
      k_passTrackingFailureFilter = p.PassTrackingFailureFilter();
      k_passBeamHaloFilterLoose = p.PassBeamHaloFilterLoose();
      k_passBadEESupercrystalFilter = p.PassBadEESupercrystalFilter();
      k_passEcalDeadCellBoundaryEnergyFilter = p.PassEcalDeadCellBoundaryEnergyFilter();
      k_passEcalDeadCellTriggerPrimitiveFilter = p.PassEcalDeadCellTriggerPrimitiveFilter();
      k_passEcalLaserCorrFilter = p.PassEcalLaserCorrFilter();
      k_passHBHENoiseFilter = p.PassHBHENoiseFilter();
      k_passHcalLaserEventFilter = p.PassHcalLaserEventFilter();
      k_PileUpInteractionsTrue = p.PileUpInteractionsTrue();
    }
    
    return *this;
}

//// SET CLASS VARIBALES
void KEvent::SetIsTrackingFailure(bool fail){
  k_isTrackingFailure = fail;
}

void KEvent::SetPassTrackingFailureFilter(bool pass){
  k_passTrackingFailureFilter= pass;
}

void KEvent::SetPassBeamHaloFilterLoose(bool pass){
  k_passBeamHaloFilterLoose = pass;
}


void KEvent::SetPassBadEESupercrystalFilter(bool pass){
  k_passBadEESupercrystalFilter = pass;
}

void KEvent::SetPassEcalDeadCellBoundaryEnergyFilter(bool pass){
  k_passEcalDeadCellBoundaryEnergyFilter = pass;
}

void KEvent::SetPassEcalDeadCellTriggerPrimitiveFilter(bool pass){
  k_passEcalDeadCellTriggerPrimitiveFilter = pass;
}

void KEvent::SetPassEcalLaserCorrFilter(bool pass){
  k_passEcalLaserCorrFilter= pass;
}

void KEvent::SetPassHBHENoiseFilter(bool pass){
  k_passHBHENoiseFilter= pass;
}
void KEvent::SetPassHcalLaserEventFilter(bool pass){

  k_passHcalLaserEventFilter = pass;
}

void KEvent::SetPileUpInteractionsTrue(double npu){
  k_PileUpInteractionsTrue = npu;
}

void KEvent::SetWeight(double mcweight){
  k_mcweight = mcweight;
}

void KEvent::SetJetRho(double jetrho){

  k_jetrho = jetrho;
}

void KEvent::SetIsPrimaryVertex(bool ispv){

  k_isprimaryvertex = ispv;
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

void KEvent::SetMET(double met){
  k_MET = met;
}

void KEvent::SetMETphi(double metphi){
  k_METphi = metphi;
}

void KEvent::SetNVertices(int nvert){
  k_nvertices = nvert;
}

void KEvent::SetVertexIndex(int ivertex){
  k_ivertex = ivertex;
}

void KEvent::SetVertexIsFake(bool isfakeV){
  k_isfakeV = isfakeV;
}

void KEvent::SetIsGoodEvent(bool isgood){
  k_isgoodevent = isgood;
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




