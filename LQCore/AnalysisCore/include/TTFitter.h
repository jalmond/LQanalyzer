#ifndef TTFitter_h
#define TTFitter_h

//#include "TMinuit.h"
#include "TLorentzVector.h"


static Double_t Wmass = 80.398;
static Double_t Wwidth = 2.141;
static Double_t Topwidth = 1.5;
static Double_t Topmass = 172.5;
static float b_mass = 4.8;
static float c_mass = 1.27;

class TTFitter {

 public:
  TTFitter();
  ~TTFitter();


  //things i send back from the fitter
  static Double_t Mass[24];
  static Double_t HMass[24];
  static Double_t Chi2[24];
  static Double_t Error[24][9];
  static Double_t mtop_error_p[24];
  static Double_t mtop_error_m[24];
  static Double_t bestchi2;
  static Double_t bestmass;
  static Double_t bestHmass;
  static bool tagconsistent[24];
  static Int_t sol;
  static Int_t combos[24][4];
  static Double_t neupzin[24];
  static TLorentzVector rawJets[24][4];
  static TLorentzVector jetsIN[24][4];

  static bool imaginary[24];
  
  static TLorentzVector FittedJets[24][4];
  static Double_t JetSigma[24][4];
  static TLorentzVector FittedLep[24];
  static TLorentzVector FittedNeu[24];


  //things i've added

  static Double_t LeptonSigma;
  static Double_t LeptonChi[24];

  static Double_t UnclXChi[24];
  static Double_t UnclYChi[24];
  static Double_t JetChi[4][24];
  static Double_t LepWChi[24];
  static Double_t HadTopChi[24];
  static Double_t LepTopChi[24];
  static Double_t HadWChi[24];
  static TLorentzVector unclustered;

  static Double_t Out[24][10];
  static Double_t Scale[24][7];

  static void Fit(TLorentzVector Lepton, float sigmalep, TLorentzVector jets[], TLorentzVector jetraw[], bool btag[], TLorentzVector sumjets, TLorentzVector met, int ntupletype, Int_t tstype, bool debug);
  
  static void GetTSCorr(TLorentzVector jets_f[4], Int_t tstype, Bool_t debug);
  static Double_t tsjetCorr[3][4];
  static Double_t sigmajets[3][4];
  
  
 private:
  
  //chi squared function
  
  static void fcn(Int_t &npar,Double_t *gin,Double_t &f,Double_t *par,Int_t iflag);
  
  
  //internal fitter objects
  static TLorentzVector tjets[4];
  static Double_t tsigmajets[4];
  static TLorentzVector tlepton;
  static Double_t sigmalep;
  static TLorentzVector uncl;
  static Double_t sigmauncl;

  static Double_t tleptonchi;
  static Double_t tunclxchi;
  static Double_t tunclychi;
  static Double_t tlepwchi;
  static Double_t tleptopchi;
  static Double_t thadtopchi;
  static Double_t thadwchi;
  static Double_t tjet0chi;
  static Double_t tjet1chi;
  static Double_t tjet2chi;
  static Double_t tjet3chi;


  //internal to the fitter function
  static TLorentzVector fitneu;
  static TLorentzVector fitlep;
  static TLorentzVector fitjets[4];
  static TLorentzVector Wjj;
  static TLorentzVector hTop;
  static TLorentzVector Wlv;
  static TLorentzVector lTop;



  //  ClassDef (TTFitter, 1);
};

#endif
