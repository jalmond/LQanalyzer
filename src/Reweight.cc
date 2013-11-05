#ifndef Reweight_h
#define Reweight_h

#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"

class ReweightPU {

  public:

    ReweightPU(TString filenameData) {

      fileData_ = 0;
      fileData_ = new TFile(filenameData, "READ");

      if (!fileData_) cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";

      h_Data_ = 0;

      h_Data_ = (TH1D*)fileData_->Get("pileup");      
      if (!h_Data_) cout << "Can't open PU data reweight histo";

      
      Double_t Summer2012_S10[60] = {
	2.560E-06,
	5.239E-06,
	1.420E-05,
	5.005E-05,
	1.001E-04,
	2.705E-04,
	1.999E-03,
	6.097E-03,
	1.046E-02,
	1.383E-02,
	1.685E-02,
	2.055E-02,
	2.572E-02,
	3.262E-02,
	4.121E-02,
	4.977E-02,
	5.539E-02,
	5.725E-02,
	5.607E-02,
	5.312E-02,
	5.008E-02,
	4.763E-02,
	4.558E-02,
	4.363E-02,
	4.159E-02,
	3.933E-02,
	3.681E-02,
	3.406E-02,
	3.116E-02,
	2.818E-02,
	2.519E-02,
	2.226E-02,
	1.946E-02,
	1.682E-02,
	1.437E-02,
	1.215E-02,
	1.016E-02,
	8.400E-03,
	6.873E-03,
	5.564E-03,
	4.457E-03,
	3.533E-03,
	2.772E-03,
	2.154E-03,
	1.656E-03,
	1.261E-03,
	9.513E-04,
	7.107E-04,
	5.259E-04,
	3.856E-04,
	2.801E-04,
	2.017E-04,
	1.439E-04,
	1.017E-04,
	7.126E-05,
	4.948E-05,
	3.405E-05,
	2.322E-05,
	1.570E-05,
	5.005E-06
      };
      
      
      h_MCmod_ = (TH1D*)h_Data_->Clone("h_MCmod_");
      for (Int_t i = 1; i < 61; i++) {
        h_MCmod_->SetBinContent(i, Summer2012_S10[i-1]);
      }

      double int_MC_ = h_MCmod_->Integral();
      double int_Data_ = h_Data_->Integral();
      
      h_Data_->Divide(h_MCmod_);
      h_Data_->Scale(int_MC_ / int_Data_);

    }

    ~ReweightPU() {
      delete fileData_;
      delete h_MCmod_;
      delete h_Data_;
    }

  double GetWeight(int nvtx) {
    return h_Data_->GetBinContent( nvtx + 1 );    
  }

  private:

    TFile* fileData_;

    TH1D* h_MCmod_;
    TH1D* h_Data_;

};

class Reweight {

  public:
    Reweight(TString filename) {
      file_ = new TFile(filename, "READ");
      if (!file_) {
        cout << "\n\nweight file not found!"<<endl<<endl;
      }

      h_weightBC_ = (TH1F*)file_->Get("hm_met_v_mt_BC_costheta0");
      if (!h_weightBC_) {
        cout << "\n\ncostheta weightBC histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBC_->Rebin(5);
        Double_t integral = h_weightBC_->Integral();
        if (integral > 0.000001)
          h_weightBC_->Scale(1./integral);
      }

      h_weightAD_ = (TH1F*)file_->Get("hm_met_v_mt_AD_costheta0");
      if (!h_weightAD_) {
        cout << "\n\ncostheta weightAD histogram not found!"<<endl<<endl;
      } else {
        h_weightAD_->Rebin(5);
        Double_t integral = h_weightAD_->Integral();
        if (integral > 0.000001)
          h_weightAD_->Scale(1./integral);
      }

      h_weightBCboost_ = (TH1F*)file_->Get("hm_BC_boost0");
      //h_weightBCboost2_ = (TH1F*)file2_->Get("hm_BC_boost0");
      if (!h_weightBCboost_){// || !h_weightBCboost2_) {
        cout << "\n\nweightBCboost histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBCboost_->Rebin(2);
        //h_weightBCboost2_->Rebin(2);
        Double_t integral = h_weightBCboost_->Integral();
        //Double_t integral2 = h_weightBCboost2_->Integral();
        if (integral > 0.000001) {
          h_weightBCboost_->Scale(1./integral);
          //h_weightBCboost2_->Scale(1./integral2);
        }
      }

      h_weightADboost_ = (TH1F*)file_->Get("hm_AD_boost0");
      if (!h_weightADboost_) {
        cout << "\n\nweightADboost histogram not found!"<<endl<<endl;
      } else {
        h_weightADboost_->Rebin(2);
        Double_t integral = h_weightADboost_->Integral();
        if (integral > 0.000001)
          h_weightADboost_->Scale(1./integral);
      }

      h_weightBCeta_ = (TH1F*)file_->Get("hm_BC_eta0");
      if (!h_weightBCeta_) {
        cout << "\n\nweightBCeta histogram not found!"<<endl<<endl;
      }
      else {
        h_weightBCeta_->Rebin(2);
        Double_t integral = h_weightBCeta_->Integral();
        if (integral > 0.000001)
          h_weightBCeta_->Scale(1./integral);
      }

      h_weightADeta_ = (TH1F*)file_->Get("hm_AD_eta0");
      if (!h_weightADeta_) {
        cout << "\n\nweightADeta histogram not found!"<<endl<<endl;
      } else {
        h_weightADeta_->Rebin(2);
        Double_t integral = h_weightADeta_->Integral();
        if (integral > 0.000001)
          h_weightADeta_->Scale(1./integral);
      }
    }
    ~Reweight(void) {
      //file_->Close();
      delete file_;
    }
/*    double GetWeight(double costheta) {
      Int_t bin = 10 * (costheta + 1.)/2.;
      if (!file_) {
        std::cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weight_) {
        std::cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weight_->GetBinContent(bin);
    }
*/
    double GetWeightBC(double costheta) {
      Int_t bin = int(10 * (costheta + 1.)/2. + 1);
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n"<<endl<<endl;
        return -1.;
      }
      if (!h_weightBC_) {
        cout << "\n\ncostheta weight histogram not found!"<<endl<<endl;
        return -1.;
      }
      return h_weightBC_->GetBinContent(bin);
    }

    double GetWeightAD(double costheta) {
      Int_t bin = int(10 * (costheta + 1.)/2. + 1);
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n"<<endl<<endl;
        return -1.;
      }
      if (!h_weightAD_) {
        cout << "\n\ncostheta weight histogram not found!"<<endl<<endl;
        return -1.;
      }
      return h_weightAD_->GetBinContent(bin);
    }

    double GetWeightBCboost(double boost) {
      Int_t bin = int(50. * (boost)/1.2 + 1);
      if (!file_) {
        std::cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightBCboost_) {
        std::cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightBCboost_->GetBinContent(bin);
    }

    double GetWeightADboost(double boost) {
      Int_t bin = int(50. * (boost)/1.2 + 1);
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightADboost_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightADboost_->GetBinContent(bin);
    }


    double GetWeightBCeta(double eta) {
      Int_t bin = int(20. * (eta)/4. + 1); // 40 bins rebinned down to 20 bins;
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightBCeta_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightBCeta_->GetBinContent(bin);
    }

    double GetWeightADeta(double eta) {
      Int_t bin = int(20. * (eta)/4. + 1); // 40 bins rebinned down to 20 bins
      if (!file_) {
        cout << "\n\ncostheta weight file not found!\n\n";
        return -1.;
      }
      if (!h_weightADeta_) {
        cout << "\n\ncostheta weight histogram not found!\n\n";
        return -1.;
      }
      return h_weightADeta_->GetBinContent(bin);
    }

  private:
    TFile* file_;
    TH1F* h_weightBC_;
    TH1F* h_weightAD_;
    TH1F* h_weightBCboost_;
    TH1F* h_weightADboost_;
    TH1F* h_weightBCeta_;
    TH1F* h_weightADeta_;
};

#endif
