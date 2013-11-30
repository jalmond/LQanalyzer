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
KParticle()
{
  k_isData=0;
  k_EventNumber=0;
  k_RunNumber=0;
  k_MET=0.;
  k_METphi=0.;
  k_isprimaryvertex=0;
  k_vertexX=0.;
  k_vertexY=0.;
  k_vertexZ=0.;
  k_nvertices=0;
  k_jetrho=0.;
  k_isfakeV=false; 
  k_isgoodevent = false;
}

/**
 * Copy constructor.
 */
KEvent::KEvent(const KEvent& ev) :
    KParticle(ev)
{
  k_isData=ev.IsData();
  k_EventNumber=ev.EventNumber();
  k_RunNumber=ev.RunNumber();
  k_MET= ev.MET();
  k_METphi= ev.METphi();
  k_isprimaryvertex=ev.IsPrimaryVertex();
  k_vertexX=ev.VertexX();
  k_vertexY=ev.VertexY();
  k_vertexZ=ev.VertexZ();
  k_nvertices= ev.nVertices();
  k_isfakeV=ev.IsFakeVertex(); 
  k_jetrho=ev.JetRho();
  k_isgoodevent = ev.HasGoodPrimaryVertex();
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
    }
    
    return *this;
}


//// SET CLASS VARIBALES

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




