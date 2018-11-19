#include "StdPlots.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

StdPlots::StdPlots():  Mass_W(80.398) {  
}

StdPlots::StdPlots(TString name): Mass_W(80.398) {  
  std::cout << name << std::endl;

}

StdPlots::StdPlots(const StdPlots& s): Mass_W(80.398){
  
}

StdPlots& StdPlots::operator= (const StdPlots& p)
{
  if (this != &p) {
  }
  return *this;
}

StdPlots::~StdPlots() {

}

void StdPlots::Fill(){

}

void StdPlots::Write() {

}


