#ifndef AnalysisBase_h
#define AnalysisBase_h

#include <iostream>
using namespace std;
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Data.h"
#include "KParticle.h"
#include "SelectionFunctions.h"

class AnalysisBase : public SelectionFunctions {
  
 public: 

  AnalysisBase();
  ~AnalysisBase();

  //static const Double_t integratedlumi = 1.927196301; //HLT_Mu5,8
  //static const Double_t integratedlumi =  1.483873; //HLT_Mu12  
  //  static const Double_t integratedlumi = 22.945019; //HLT_Mu17
  //static const Double_t integratedlumi = 83.483;// HLT_Mu24
  //static const Double_t integratedlumi = 123.9391;

  const Double_t Mass_Z;
  const Double_t Mass_W;

  int nthdigit(int x, int n);
  bool isPrompt(long pdgid);
  void getFakerate(TH2F* h1, TH2F* h2, TH2F* out, int nbinX, int nbinY);
  void getFakerate(TH1F* h1, TH1F* h2, TH1F* out, int nbinX);
  
  double DoublebackGround(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t *****fakeN, UInt_t &type, Double_t weight);
  double SinglebackGround(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, Double_t ***fakeN, UInt_t &type, Double_t weight);
  double DoubleTOSinglebkg(TH2F* fakerate, std::vector<snu::KParticle>& leptonColl, UInt_t &ilep, UInt_t &jlep);
  void DoubleANDSinglebkg(std::vector<snu::KParticle>& leptonColli, UInt_t &ilep, std::vector<snu::KParticle>& leptonCollj, UInt_t &jlep, Double_t *****fakeN, UInt_t &type);
  
  void BackGroundEstimate(TH2F* fakerate,  Double_t ***fakeN1, Double_t *****prova, Double_t *****fakeN2, Double_t *singolo, Double_t *errsingolo, Double_t *doppio, Double_t *errdoppio, Double_t *singoloreale, Double_t *errsingoloreale, Double_t *doppioreale, Double_t *totale, Double_t *doubletosingle, Double_t *errdoubletosingle);
  
  void WeigthedMean(std::vector<double>& value, std::vector<double>& error, double &mean, double &stddev);
  
};
#endif
