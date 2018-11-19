// LOCAL includes
#include "KLepton.h"

// STL
#include <sstream>

// ROOT

KLepton::KLepton() :
  KParticle(),
  k_dXY = -999.,
  k_dXYerr = -999.,
  k_dZ = -999.,
  k_dZerr = -999,
  k_IP3D = -999.,
  k_IP3Derr = -999.,
  k_RelIso = -999.,
  k_MiniRelIso = -999.,
  k_ptcone = -999.,
  k_LeptonFlavour = NONE,
  k_mciscf(false),
  MuonPtr(NULL),
  ElectronPtr(NULL)
{

}

KLepton::KLepton(const KLepton& lep) :
  KParticle(lep),
  k_flavour(lep.LeptonFlavour()).

  k_dXY(lep.dXY()),
  k_dXY(0.),
  k_dZ(lep.dZ()), 
  k_dZerr(0.), 
  k_IP3D(lep.IP3D()), 
  k_IP3Derr(0.),
  k_RelIso(lep.RelIso()),
  k_MiniRelIso(lep.MiniRelIso()),
  k_ptcone(lep.PtCone()),
  k_LeptonFlavour(lep.LeptonFlavour(),
  k_mciscf(lep.MCIsCF())
{
  if(k_flavour==KLepton::MUON) MuonPtr = lep.MuonPtr;
  if(k_flavour==KLepton::ELECTRON) ElectronPtr = lep.ElectronPtr;
}

KLepton::KLepton(const snu::KMuon& muon) :
  KParticle(muon),
  k_flavour(KLepton::MUON),
  k_dz(muon.dZ()),
  k_dxy(muon.dXY()),
  k_dxy_sig2D(muon.dXYSig2D()),
  k_dxy_sig3D(muon.dXYSig3D()),
  k_reliso(muon.RelIso04()),
  k_minireliso(muon.PFRelMiniIsoRho()),
  k_leptype(muon.GetType()),
  k_mciscf(muon.MCIsCF()),
  MuonPtr(&muon),
  ElectronPtr(NULL)
{

}

KLepton::KLepton(const snu::KElectron& electron) :
  KParticle(electron),
  k_flavour(KLepton::ELECTRON),
  k_dz(electron.dz()),
  k_dxy(electron.dxy()),
  k_dxy_sig2D(electron.dxySig2D()),
  k_dxy_sig3D(electron.dxySig3D()),
  k_reliso(electron.PFRelIso(0.3)),
  k_minireliso(electron.PFRelMiniIso(false)),
  k_leptype(electron.GetType()),
  k_mciscf(electron.MCIsCF()),
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
    k_dxy_sig2D = lep.k_dxy_sig2D;
    k_dxy_sig3D = lep.k_dxy_sig3D;
    k_reliso = lep.k_reliso;
    k_minireliso = lep.k_minireliso;
    k_leptype = lep.k_leptype;
    k_mciscf = lep.k_mciscf;
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
  k_dxy_sig2D = muon.dXYSig2D();
  k_dxy_sig3D = muon.dXYSig3D();
  k_reliso = muon.RelIso04();
  k_minireliso = muon.PFRelMiniIsoRho();
  k_leptype = muon.GetType();
  k_mciscf = muon.MCIsCF();
  MuonPtr = &muon;
  ElectronPtr = NULL;

  return *this;

}

KLepton& KLepton::operator= (const snu::KElectron& electron){

  KParticle::operator=(electron);
  k_flavour = KLepton::ELECTRON;
  k_dz = electron.dz();
  k_dxy = electron.dxy();
  k_dxy_sig2D = electron.dxySig2D();
  k_dxy_sig3D = electron.dxySig3D();
  k_reliso = electron.PFRelIso(0.3);
  k_minireliso = electron.PFRelMiniIso(false);
  k_leptype = electron.GetType();
  k_mciscf = electron.MCIsCF();
  MuonPtr = NULL;
  ElectronPtr = &electron;

  return *this;

}

void KLepton::SetdXY(double dXY, double dXYerr){
  k_dXY = dXY;
  k_dXYerr = dXYerr;
}

void KLepton::SetdZ(double dZ, double dZerr){
  k_dZ = dZ;
  k_dZerr = dZerr;
}

void KLepton::SetIP3D(double IP3D, double IP3Derr){
  k_IP3D = IP3D;
  k_IP3Derr = IP3Derr;
}

void KLepton::SetRelIso(double r){
  k_RelIso = r;
}

void KLepton::SetMiniIso(double ch, double nh, double ph, double pu, double rho, double EA){

  double r_mini = miniIsoDr();

  double correction = rho * EA * (r_mini/0.3) * (r_mini/0.3);
  double correctedIso = ch + std::max(0.0, nh + ph - correction);
  k_MiniRelIso = correctedIso/this->Pt();

}

void KLepton::SetKLeptonFlavour(Flavour f){
  k_KLeptonFlavour = f;
}


//==== FIXME
/*
template <typename T>
T KKLepton::GetKLeptonPtr(){

  if(MuonPtr) return MuonPtr;
  if(ElectronPtr) return ElectronPtr;
  return NULL;

}
*/







