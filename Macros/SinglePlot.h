#ifndef SINGLEPLOT
#define SINGLEPLOT

#include <string>
#include "TFile.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

class SinglePlot {
  public:
    SinglePlot() {}
    SinglePlot(TString name, unsigned int rebin, bool log, bool normalize, bool normToFirst, double scaleXmax,
               bool overflow, bool stacked, TString title, TString Xtitle, TString Ytitle)
      : name_(name), rebin_(rebin), log_(log), normalize_(normalize), normToFirst_(normToFirst), scaleXmax_(scaleXmax),
      overflow_(overflow), stacked_(stacked), title_(title), Xtitle_(Xtitle), Ytitle_(Ytitle) {}
    ~SinglePlot() {}

    TString name() { return name_; }
    unsigned int rebin() { return rebin_; }
    bool log() { return log_; }
    bool normalize() { return normalize_; }
    bool normToFirst() { return normToFirst_; }
    double scaleXmax() { return scaleXmax_; }
    bool overflow() { return overflow_; }
    bool stack() { return stacked_; }
    TString title() { return title_; }
    TString Xtitle() { return Xtitle_; }
    TString Ytitle() { return Ytitle_; }

  private:
    TString name_;
    unsigned int rebin_;
    bool log_;
    bool normalize_;
    bool normToFirst_;
    double scaleXmax_;
    bool overflow_;
    bool stacked_;
    TString title_;
    TString Xtitle_;
    TString Ytitle_;

};


#endif
