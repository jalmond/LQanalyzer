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

  k_gen_statusflag=-999.;
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

  k_gen_statusflag= mc.StatusFlag();
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
  k_gen_statusflag=-999.;
  k_gen_pdgid=-999;
  k_gen_status=-999;
  k_gen_indexmum=-999;
  
}



KTruth& KTruth::operator= (const KTruth& p)
{
  if (this != &p) {
    KParticle::operator=(p);
    k_gen_statusflag=p.StatusFlag();
    k_gen_pdgid=p.PdgId(); 
    k_gen_status=p.GenStatus();
    k_gen_indexmum=p.IndexMother();
  }
  
  return *this;
}


//// SET CLASS VARIBALES

void KTruth::SetParticlePdgId(int pdgid){
  k_gen_pdgid = pdgid;
}

void KTruth::SetParticleStatus(int status){
  k_gen_status = status;
}

void KTruth::SetParticleIndexMother(int index_mum){
  k_gen_indexmum = index_mum;
}

void KTruth::SetStatusFlag(double iflag){
  k_gen_statusflag = iflag;
}


Bool_t KTruth::ReadStatusFlag(int which_flag) const{
  
  double flag_checker = k_gen_statusflag;
  vector<int> v_flags;
  v_flags.push_back(7);// gen_fromhardprocess_beforeFSR
  v_flags.push_back(6);// gen_fromhardprocess
  v_flags.push_back(5);// gen_ishardprocess 
  v_flags.push_back(4);// gen_isdirecthadrondecayproduct
  v_flags.push_back(3);// gen_isprompttaudecayproduct 
  v_flags.push_back(2);// gen_istaudecayproduct
  v_flags.push_back(1);// gen_isdecayedleptonhadron
  v_flags.push_back(0);// gen_isprompt
  
  for(unsigned int i=0; i < v_flags.size(); i++){
    double i_mask = pow(10.,double(v_flags.at(i)));
    bool pass_flag(false);
    if(flag_checker >= i_mask) {pass_flag=true; flag_checker = flag_checker- i_mask;}
    else pass_flag=false;
    if(i == unsigned(which_flag)) return pass_flag;
  }
  return true;
}
