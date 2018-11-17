#ifndef KLepton_h
#define KLepton_h

/// c++ std libraries
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// ROOT include(s): 

/// SNU classes
#include "KParticle.h"
#include "KMuon.h"
#include "KElectron.h"

class KLepton: public snu::KParticle {

public:

  enum Flavour{NOTSET=0, MUON=1, ELECTRON=2};

  KLepton();
  KLepton(const KLepton& lep);
  KLepton(const snu::KMuon& muon);
  KLepton(const snu::KElectron& electron);
  ~KLepton();


  void SetdXY(double dXY, double dXYerr);
  inline double dXY() const {return k_dXY;}
  inline double dXYerr() const {return k_dXYerr;}

  void SetdZ(double dZ, double dZerr);
  inline double dZ() const {return k_dZ;}
  inline double dZerr() const {return k_dZerr;}

  void SetIP3D(double IP3D, double IP3Derr);
  inline double IP3D() const {return k_IP3D;}
  inline double IP3Derr() const {return k_IP3Derr;}

  //==== AbsIso will be set in Muon/Electron,
  //==== and use SetRelIso to save calculated RelIso
  void SetRelIso(double r);
  inline double RelIso() const {return k_RelIso;}

  //==== SUSY mini Iso has same formula for Muon and Electron
  void SetMiniIso(double ch, double nh, double ph, double pu, double rho, double EA);
  inline double MiniRelIso() const {return k_MiniRelIso;}


  inline Flavour LeptonFlavour() const {return k_flavour;}
  void SetLeptonFlavour(Flavour f);
  
  inline float miniIsoDr() const {
    float mindr = 0.05;
    float maxdr = 0.2;
    float kt_scale = 10.0;
    return std::max(mindr, std::min(maxdr, float(kt_scale/this->Pt())));
  }

  void SetPtCone(double f){ k_ptcone = f; }
  inline bool IsPtConeAvailable() const {
    if(k_ptcone<0) return false;
    else return true;
  }
  inline double PtCone() const {
    if(k_ptcone<0){
      cout << "[Lepton::PtCone] ptcone not set" << endl;
      exit(EXIT_FAILURE);
    }
    return k_ptcone;
  }
  inline double CalcPtCone(double this_reliso, double Tight_reliso){
    return ( this->Pt() ) * ( 1. + max(0., (this_reliso-Tight_reliso)) );
  }

  inline bool MCIsCF() const {return k_mciscf;}


  //  inline Double_t dXYSig2D() const {return k_dxy_sig2D;}
  //  inline Double_t dXYSig3D() const {return k_dxy_sig3D;}
  //  inline Double_t RelIso() const {return k_reliso;}
  //  inline Double_t miniRelIso() const {return k_minireliso;}


  inline const snu::KMuon* GetMuonPtr() const {return MuonPtr;}
  inline const snu::KElectron* GetElectronPtr() const {return ElectronPtr;}
    
  //==== FIXME
  //template <typename T>
  //  T GetLeptonPtr();

  KLepton& operator= (const KLepton& obj);
  KLepton& operator= (const snu::KMuon& obj);
  KLepton& operator= (const snu::KElectron& obj);

private:


  double k_dXY, k_dXYerr;
  double k_dZ, k_dZerr;
  double k_IP3D, k_IP3Derr;

  double k_RelIso, k_MiniRelIso;
  double k_ptcone;
  Flavour k_LeptonFlavour;

  bool k_mciscf;

  const snu::KMuon* MuonPtr;
  const snu::KElectron* ElectronPtr;

};

#endif
