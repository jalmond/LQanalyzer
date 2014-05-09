#include "KTruth.h"

#include <iomanip>
#include <iostream>

using namespace std;
using namespace snu;

ClassImp(KTruth)

/**
 *Default constructor.
 */
KTruth::KTruth() :
KParticle()
{

  k_gen_index=0; 

  k_gen_py=0.; 
  k_gen_pz=0.;
  k_gen_vx=0.;
  k_gen_vy=0.;
  k_gen_vz=0.;
  
  k_gen_pdgid=0; 
  k_gen_status=0;
  k_gen_indexmum=0;
  k_gen_ndau=0;
  k_gen_tdm=0;
}

/**
 * Copy constructor.
 */
KTruth::KTruth(const KTruth& mc) :
    KParticle(mc)
{

  k_gen_index=int(mc.GetIndex());
  k_gen_px=mc.GenPx(); 
  k_gen_py=mc.GenPy(); 
  k_gen_pz=mc.GenPz();
  k_gen_vx=mc.GenVx();
  k_gen_vy=mc.GenVy();
  k_gen_vz=mc.GenVz();
  k_gen_pdgid=mc.PdgId(); 
  k_gen_status=mc.GenStatus();
  k_gen_indexmum=mc.IndexMother();
  k_gen_ndau=mc.NDaughter();
  k_gen_tdm=mc.TauDecayMode();
}


KTruth::~KTruth()
{
}

void KTruth::Reset()
{
  KParticle::Reset();
  k_gen_index=0;
  k_gen_px=0.;
  k_gen_py=0.;
  k_gen_pz=0.;
  k_gen_vx=0.;
  k_gen_vy=0.;
  k_gen_vz=0.;
  k_gen_pdgid=0;
  k_gen_status=0;
  k_gen_indexmum=0;
  k_gen_ndau=0;
  k_gen_tdm=0;
  
}



KTruth& KTruth::operator= (const KTruth& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_gen_index=int(p.GetIndex());
    k_gen_px=p.GenPx(); 
    k_gen_py=p.GenPy(); 
    k_gen_pz=p.GenPz();
    k_gen_vx=p.GenVx();
    k_gen_vy=p.GenVy();
    k_gen_vz=p.GenVz();
    k_gen_pdgid=p.PdgId(); 
    k_gen_status=p.GenStatus();
    k_gen_indexmum=p.IndexMother();
    k_gen_ndau=p.NDaughter();
    k_gen_tdm = p.TauDecayMode();
  }
  
  return *this;
}


//// SET CLASS VARIBALES

void KTruth::SetIndex(int index){
  k_gen_index = index;
}

void KTruth::SetTauDecayMode(int mode){
  k_gen_tdm = mode;
}

void KTruth::SetParticlePx(double px){
  k_gen_px = px;
}

void KTruth::SetParticlePy(double py){
  k_gen_py = py;
}

void KTruth::SetParticlePz(double pz){
  k_gen_pz = pz;
}
void KTruth::SetParticleVx(double Vx){
  k_gen_vx = Vx;
}

void KTruth::SetParticleVy(double Vy){
   k_gen_vy = Vy;
}

void KTruth::SetParticleVz(double Vz){
  k_gen_vz = Vz;
}

void KTruth::SetParticlePdgId(double pdgid){
  k_gen_pdgid = int(pdgid);
}

void KTruth::SetParticleStatus(double status){
  k_gen_status = int(status);
}

void KTruth::SetParticleIndexMother(double index_mum){
  k_gen_indexmum = int(index_mum);
}

void KTruth::SetParticleNDaughter(double n_dau){
  k_gen_ndau = int(n_dau);
}





