/// Local includes
#include "SelectionFunctions.h"


// STL inclues
#include <cmath>

// ROOT includes
#include <TString.h>
#include <string>

#include <iostream>

using namespace std;


SelectionFunctions::SelectionFunctions(){
}

SelectionFunctions::~SelectionFunctions(){
}

/// Code contains functions for Selecting Event


bool SelectionFunctions::isGoodEvent(Int_t nVertex, std::vector<Bool_t> Vertex_Fake, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Bool_t *goodVerticies) {

  /// Function checks if the event has a good vertex
  /// The vertices are ordered in terms of pt
  /// The array goodVertices is filled true for the highest energy good vertex
  
  if (nVertex>0) {
    for (Int_t i=0; i<nVertex; i++) {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 && sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))<=2 && !Vertex_Fake[i] ) {
        goodVerticies[i] = true;
	return true;
      }
      else {
        goodVerticies[i] = false;
      }
    }
    return false;
  }
  else
    return false;
}




bool SelectionFunctions::TriggerSelector(std::vector<TString> triggernames, std::vector<std::string> inputtriggers, std::vector<Bool_t> triggerdecision, std::vector<Int_t> HLTPrescales, Int_t &prescaler) {

  //// This function passes in a vector of trigger names
  //// The imput vector should be ordered in terms of trigger threshold (highest prescaled first)
  
  //// function will return true if one of the input trigger names has been passed for this event. 
  //// The input presaler is set to the lowest prescale for the event
  
  for (std::vector<TString>::reverse_iterator it (triggernames.end()); 
       it != std::vector<TString>::reverse_iterator (triggernames.begin()); 
       ++it) {
    for (UInt_t i=0; i<inputtriggers.size(); i++) {
      TString tmpHLT = inputtriggers[i];
      if ( tmpHLT.BeginsWith(*it) && triggerdecision[i] ) {
	//cout<< "is prescaled by "<<HLTPrescales[i]<<endl<<endl;
	prescaler=HLTPrescales[i]; 
        return true;
      }
    }
  }
  if(triggernames.size()== 0){
    for (UInt_t i=0; i<inputtriggers.size(); i++) {
      if (triggerdecision[i]) return true;
    }
  }
  
  return false;
}


// Energy resolution scale factors

double SelectionFunctions::EnergyResScaleFactor (float eta){ 
  double fabs_eta = fabs ( eta );
  if      ( fabs_eta > 0.0 && fabs_eta <= 0.5 ) return 1.052;
  else if ( fabs_eta > 0.5 && fabs_eta <= 1.1 ) return 1.057;
  else if ( fabs_eta > 1.1 && fabs_eta <= 1.7 ) return 1.096;
  else if ( fabs_eta > 1.7 && fabs_eta <= 2.3 ) return 1.134;
  else                                          return 1.288;
}

double SelectionFunctions::EnergyResScaleError  (float eta){ 
  double fabs_eta = fabs ( eta );
  if      ( fabs_eta > 0.0 && fabs_eta <= 0.5 ) return 0.063;
  else if ( fabs_eta > 0.5 && fabs_eta <= 1.1 ) return 0.057;
  else if ( fabs_eta > 1.1 && fabs_eta <= 1.7 ) return 0.065;
  else if ( fabs_eta > 1.7 && fabs_eta <= 2.3 ) return 0.094;
  else                                          return 0.200;
}
