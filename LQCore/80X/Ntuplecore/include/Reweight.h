#ifndef Reweight_h
#define Reweight_h

class TFile;
class TH1D;
class TH1F;
class TString;
class TDirectory;

#include <vector>
class Reweight {


 public:
  
  //// constructors
  Reweight(TString filename);
  Reweight(std::vector< float > MC_distr, std::vector< float > Lumi_distr);
  ~Reweight();
  
  double GetWeight(int nvtx);
  double GetUserWeight(int nvtx);
  
  TDirectory* getTemporaryDirectory(void) const;
  
 private:

  TFile* fileData_;
  TFile* fileMC_;

  TH1D* h_MCmod_;
  TH1D* h_Data_;

  TH1F*  MC_distr_;
  TH1F*  Data_distr_;
  TH1F*  weights_;
  TH1F* h_MCmodF_;
  TH1F* h_DataF_;


};

#endif

