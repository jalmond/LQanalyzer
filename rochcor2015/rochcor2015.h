#ifndef ROCHCOR2015_H
#define ROCHCOR2015_H

#include <iostream>
#include <map>
#include "TChain.h"
#include "TClonesArray.h"
#include "TString.h"

#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "RoccoR.h"

class rochcor2015 {
 public:
  rochcor2015();
  rochcor2015(int seed);
  ~rochcor2015();
  
  void momcor_mc(TLorentzVector&, float, int, float&);
  void momcor_data(TLorentzVector&, float, int, float&);
  
  int aetabin(double);
  int etabin(double);
  int phibin(double);
  
 private:
  
  TRandom3 eran;
  TRandom3 sran;
    
  //  static float netabin[9] = {-2.4,-2.1,-1.4,-0.7,0.0,0.7,1.4,2.1,2.4};
  static const double pi = 3.14159265358979323846;
  static const double netabin[25];
  static const double anetabin[13];
  
  static const double mu_mass = 0.105658;
  static const double genm_smr = 9.09923e+01; //gen mass peak with eta dependent gaussian smearing => better match in Z mass profile vs. eta/phi
  static const double genm = 91.06; //gen mass peak without smearing => Z mass profile vs. eta/phi in CMS note
  
  static const double mrecm = 9.08509e+01; //rec mass peak in MC 
  static const double drecm = 9.07902e+01; //rec mass peak in data 
  static const double mgscl_stat = 2.62939e-03 ; //stat. error of global factor for mass peak in MC 
  static const double mgscl_syst = 3.81651e-03; //syst. error of global factor for mass peak in MC  
  static const double dgscl_stat = 2.42830e-03; //stat. error of global factor for mass peak in data 
  static const double dgscl_syst = 0.0008; //syst. error of global factor for mass peak in data 
  static const double dgscl_iter = 1.00026; //one more iteration to fix offset
  static const double mgscl_iter = 1.00054; //one more iteration to fix offset
  //static const double sf[3];
  //static const double sfer[3];

  //---------------------------------------------------------------------------------------------
  /*
  static const double dcor_m[16][24];  
  static const double dcor_p[16][24];
  static const double mcor_m[16][24];
  static const double mcor_p[16][24];
  static const double dcor_mer[16][24];  
  static const double dcor_per[16][24];
  static const double mcor_mer[16][24];
  static const double mcor_per[16][24];
  */

  static const double dcor_bf[16][24];  
  static const double dcor_ma[16][24];
  static const double mcor_bf[16][24];
  static const double mcor_ma[16][24];
  static const double dcor_bfer[16][24];  
  static const double dcor_maer[16][24];
  static const double mcor_bfer[16][24];
  static const double mcor_maer[16][24];
  
  //=======================================================================================================
  
  static const double dmavg[16][24];  
  static const double dpavg[16][24];  
  static const double mmavg[16][24];  
  static const double mpavg[16][24];
  static const double dmavger[16][24];  
  static const double dpavger[16][24];  
  static const double mmavger[16][24];  
  static const double mpavger[16][24];

  static const double dd[12];
  static const double dder[12];
  static const double md[12];
  static const double mder[12];  

  static const double dscl[24];
  static const double mscl[24];
  //===============================================================================================

  double mptsys_mc_dm[16][24];
  double mptsys_mc_da[16][24];
  double mptsys_da_dm[16][24];
  double mptsys_da_da[16][24];

  double gscler_mc_dev;
  double gscler_da_dev;


};
  
#endif
