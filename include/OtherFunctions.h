#ifndef OtherFunctions_h
#define OtherFunctions_h

#include <iostream>
using namespace std;
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "Lepton.h"
#include "Data.h"

int nthdigit(int x, int n);

bool isPrompt(long pdgid);

void getFakerate(TH2F* h1, TH2F* h2, TH2F* out, int nbinX, int nbinY);

void getFakerate(TH1F* h1, TH1F* h2, TH1F* out, int nbinX);

double DoublebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep, Double_t *****fakeN, UInt_t &type, Double_t weight);

double SinglebackGround(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, Double_t ***fakeN, UInt_t &type, Double_t weight);

double DoubleTOSinglebkg(TH2F* fakerate, std::vector<Lepton>& leptonColl, UInt_t &ilep, UInt_t &jlep);

void DoubleANDSinglebkg(std::vector<Lepton>& leptonColli, UInt_t &ilep, std::vector<Lepton>& leptonCollj, UInt_t &jlep, Double_t *****fakeN, UInt_t &type);

void BackGroundEstimate(TH2F* fakerate,  Double_t ***fakeN1, Double_t *****prova, Double_t *****fakeN2, Double_t *singolo, Double_t *errsingolo, Double_t *doppio, Double_t *errdoppio, Double_t *singoloreale, Double_t *errsingoloreale, Double_t *doppioreale, Double_t *totale, Double_t *doubletosingle, Double_t *errdoubletosingle);

void WeigthedMean(std::vector<double>& value, std::vector<double>& error, double &mean, double &stddev);

//Double_t TriggerWeight(stringtobool* HLT_triggered);
/*
static const Double_t minbin = 35.0;
static const Double_t binwidh = 5.0;
double *arraypT;
static const Bool_t pT35 = true;
*/
static const double _arrayeta[] = {0.0,1.0,1.479,2.0,2.5};
static const double _arraypT [] = {10.,15.,20.,25.,30.,35.,45.,60.,80.,100.};
static const Int_t nintpT=7;
static const Int_t ninteta=4;
 
#endif
