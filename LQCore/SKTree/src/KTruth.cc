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

  k_gen_index=-999; 

  k_gen_pdgid=-999; 
  k_gen_status=-999;
  k_gen_indexmum=-999;
}

/**
 * Copy constructor.
 */
KTruth::KTruth(const KTruth& mc) :
    KParticle(mc)
{

  k_gen_index=int(mc.GetIndex());
  k_gen_pdgid=mc.PdgId(); 
  k_gen_status=mc.GenStatus();
  k_gen_indexmum=mc.IndexMother();
}


KTruth::~KTruth()
{
}

void KTruth::Reset()
{
  KParticle::Reset();
  k_gen_index=-999;
  k_gen_pdgid=-999;
  k_gen_status=-999;
  k_gen_indexmum=-999;
  
}



KTruth& KTruth::operator= (const KTruth& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_gen_index=int(p.GetIndex());
    k_gen_pdgid=p.PdgId(); 
    k_gen_status=p.GenStatus();
    k_gen_indexmum=p.IndexMother();
  }
  
  return *this;
}


//// SET CLASS VARIBALES

void KTruth::SetIndex(int index){
  k_gen_index = index;
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




