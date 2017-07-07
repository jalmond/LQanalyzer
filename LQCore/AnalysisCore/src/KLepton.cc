// LOCAL includes
#include "KLepton.h"

// STL
#include <sstream>

// ROOT

KLepton::KLepton() :
  KParticle(),
  k_flavour(KLepton::NOTSET),
  k_dz(0),
  k_dxy(0),
  k_dxy_sig(0),
  k_reliso(0),
  MuonPtr(NULL),
  ElectronPtr(NULL)
{

}

KLepton::KLepton(const KLepton& lep) :
  KParticle(lep),
  k_flavour(lep.LeptonFlavour()),
  k_dz(lep.dZ()),
  k_dxy(lep.dXY()),
  k_dxy_sig(lep.dXYSig()),
  k_reliso(lep.RelIso())
{
  if(k_flavour==KLepton::MUON) MuonPtr = lep.MuonPtr;
  if(k_flavour==KLepton::ELECTRON) ElectronPtr = lep.ElectronPtr;
}

KLepton::KLepton(const snu::KMuon& muon) :
  KParticle(muon),
  k_flavour(KLepton::MUON),
  k_dz(muon.dZ()),
  k_dxy(muon.dXY()),
  k_dxy_sig(muon.dXYSig()),
  k_reliso(muon.RelIso04()),
  MuonPtr(&muon),
  ElectronPtr(NULL)
{

}

KLepton::KLepton(const snu::KElectron& electron) :
  KParticle(electron),
  k_flavour(KLepton::ELECTRON),
  k_dz(electron.dz()),
  k_dxy(electron.dxy()),
  k_dxy_sig(electron.dxySig()),
  k_reliso(electron.PFRelIso(0.3)),
  MuonPtr(NULL),
  ElectronPtr(&electron)
{

}

KLepton::~KLepton(){

}

KLepton& KLepton::operator= (const KLepton& lep){

  if(this != &lep){
    KParticle::operator=(lep);
    k_flavour = lep.k_flavour;
    k_dz = lep.k_dz;
    k_dxy = lep.k_dxy;
    k_dxy_sig = lep.k_dxy_sig;
    k_reliso = lep.k_reliso;
    MuonPtr = lep.MuonPtr;
    ElectronPtr = lep.ElectronPtr;
  }  

  return *this;

}

KLepton& KLepton::operator= (const snu::KMuon& muon){

  KParticle::operator=(muon);
  k_flavour = KLepton::MUON;
  k_dz = muon.dZ();
  k_dxy = muon.dXY();
  k_dxy_sig = muon.dXYSig();
  k_reliso = muon.RelIso04();
  MuonPtr = &muon;
  ElectronPtr = NULL;

  return *this;

}

KLepton& KLepton::operator= (const snu::KElectron& electron){

  KParticle::operator=(electron);
  k_flavour = KLepton::ELECTRON;
  k_dz = electron.dz();
  k_dxy = electron.dxy();
  k_dxy_sig = electron.dxySig();
  k_reliso = electron.PFRelIso(0.3);
  MuonPtr = NULL;
  ElectronPtr = &electron;

  return *this;

}

//==== FIXME
/*
template <typename T>
T KLepton::GetLeptonPtr(){

  if(MuonPtr) return MuonPtr;
  if(ElectronPtr) return ElectronPtr;
  return NULL;

}
*/







