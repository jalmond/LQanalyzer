#include <string>
#include "TFile.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TString.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>

#ifndef SINGLE2DPLOT
#define SINGLE2DPLOT

class Single2dPlot {
  public:
    Single2dPlot() {}
    Single2dPlot(std::string name, std::string title, std::string drawOption, unsigned int rebinX, unsigned int rebinY)
      : name_(name), title_(title), drawOption_(drawOption), rebinX_(rebinX), rebinY_(rebinY) {}
    ~Single2dPlot() {}

    std::string name() { return name_; }
    std::string title() { return title_; }
    std::string drawOption() { return drawOption_; }
    unsigned int rebinX() { return rebinX_; }
    unsigned int rebinY() { return rebinY_; }

  private:
    std::string name_;
    std::string title_;
    std::string drawOption_;
    unsigned int rebinX_;
    unsigned int rebinY_;
};

#endif
