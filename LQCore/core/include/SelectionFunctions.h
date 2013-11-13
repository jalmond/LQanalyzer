#ifndef SelectionFunctions_h
#define SelectionFunctions_h

#include <iostream>
using namespace std;

#include "KParticle.h"
#include <vector>

static const Double_t Mass_Z = 91.1876;
static const Double_t Mass_W = 80.398;

class SelectionFunctions {

 public:
  
  //// constructors
  SelectionFunctions();
  ~SelectionFunctions();
  
  Bool_t isGoodEvent(Int_t nVertex, std::vector<Bool_t> Vertex_Fake, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Bool_t *goodVerticies);
  
  Bool_t ZandWveto(std::vector<snu::KParticle>& leptonColl, Double_t MET, Double_t METPhi);
  
  Bool_t Zselection(std::vector<snu::KParticle>& leptonColl, Double_t MET);
  
  Bool_t TriggerSelector (std::vector<TString> triggernames, std::vector<string> inputtriggers, std::vector<Bool_t> triggerdecision, std::vector<Int_t> HLTPrescales, Int_t &prescaler);
};

#endif

