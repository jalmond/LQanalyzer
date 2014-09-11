#ifndef Reweight_h
#define Reweight_h

class TFile;
class TH1D;
class TString;
class TH1F;
class TDirectory;

class Reweight {

 public:
  
  //// constructors
  Reweight(TString filename);
  ~Reweight();
  
  double GetWeight(int nvtx);
  double GetWeight(int nvtx, int sys);
  TDirectory* getTemporaryDirectory(void) const;

 private:

  TFile* fileData_;
  TFile* fileDataUP_;
  TFile* fileDataDOWN_;

  TH1D* h_MCmod_;
  TH1D* h_Data_;
  TH1D* h_Data_up_;
  TH1D* h_Data_down_;

};

#endif

