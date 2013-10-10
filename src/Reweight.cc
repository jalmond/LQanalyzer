#ifndef Reweight_h
#define Reweight_h

#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"

class ReweightPU {

  public:

    ReweightPU(TString filenameMC, TString filenameData) {

      fileMC_ = 0;
      fileData_ = 0;

      fileMC_   = new TFile(filenameMC, "READ");
      fileData_ = new TFile(filenameData, "READ");

      if (!fileMC_ || !fileData_) {
        cout << "\n\nAt least one of the Nvtx reweighting files could not be opened!\n\n";
      }

      h_MC_ = 0;
      h_Data_ = 0;

      //h_MC_ = (TH1F*)fileMC_->Get("h_nvtx_norw");
      h_Data_ = (TH1D*)fileData_->Get("pileup");

      //if (!h_MC_) cout << "Can't open PU mc reweight histo";
      if (!h_Data_) cout << "Can't open PU data reweight histo";

// Distribution used for Summer2012 MC.

  Double_t Summer2012[60] = {
    2.344E-05,
    2.344E-05,
    2.344E-05,
    2.344E-05,
    4.687E-04,
    4.687E-04,
    7.032E-04,
    9.414E-04,
    1.234E-03,
    1.603E-03,
    2.464E-03,
    3.250E-03,
    5.021E-03,
    6.644E-03,
    8.502E-03,
    1.121E-02,
    1.518E-02,
    2.033E-02,
    2.608E-02,
    3.171E-02,
    3.667E-02,
    4.060E-02,
    4.338E-02,
    4.520E-02,
    4.641E-02,
    4.735E-02,
    4.816E-02,
    4.881E-02,
    4.917E-02,
    4.909E-02,
    4.842E-02,
    4.707E-02,
    4.501E-02,
    4.228E-02,
    3.896E-02,
    3.521E-02,
    3.118E-02,
    2.702E-02,
    2.287E-02,
    1.885E-02,
    1.508E-02,
    1.166E-02,
    8.673E-03,
    6.190E-03,
    4.222E-03,
    2.746E-03,
    1.698E-03,
    9.971E-04,
    5.549E-04,
    2.924E-04,
    1.457E-04,
    6.864E-05,
    3.054E-05,
    1.282E-05,
    5.081E-06,
    1.898E-06,
    6.688E-07,
    2.221E-07,
    6.947E-08,
    2.047E-08
   };  

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
                         5.005E-06};

      h_MCmod_ = (TH1D*)h_Data_->Clone("h_MCmod_");
      for (Int_t i = 1; i < 61; i++) {
        //h_MCmod_->SetBinContent(i, PoissonOneXDist[i-1]);
        h_MCmod_->SetBinContent(i, Summer2012_S10[i-1]);
        //h_MCmod_->SetBinContent(i, h_MC_->GetBinContent(i));
//        cout << h_MCmod_->GetBinContent(i) <<endl;
      }

      double int_MC_ = h_MCmod_->Integral();
      double int_Data_ = h_Data_->Integral();

      h_Data_->Divide(h_MCmod_);
      h_Data_->Scale(int_MC_ / int_Data_);
/*
      cout << endl;
      for (Int_t i = 1; i < 61; i++)
        cout << h_Data_->GetBinContent(i) <<endl;
*/
    }

    ~ReweightPU() {
      delete fileMC_;
      delete fileData_;
      delete h_MC_;
      delete h_MCmod_;
      delete h_Data_;
    }

    double GetWeight(int nvtx) {

      return h_Data_->GetBinContent( nvtx + 1 );

    }

  private:

    TFile* fileMC_;
    TFile* fileData_;

    TH1F* h_MC_;
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
      Int_t bin = 10 * (costheta + 1.)/2. + 1;
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
      Int_t bin = 10 * (costheta + 1.)/2. + 1;
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
      Int_t bin = 50. * (boost)/1.2 + 1;
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
      Int_t bin = 50. * (boost)/1.2 + 1;
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
      Int_t bin = 20. * (eta)/4. + 1; // 40 bins rebinned down to 20 bins;
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
      Int_t bin = 20. * (eta)/4. + 1; // 40 bins rebinned down to 20 bins
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
