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



bool SelectionFunctions::TriggerSelector(std::vector<std::string> j_HLT_TriggerName, std::vector<TString> trigs){

  //// This function passes in a vector of trigger names
  //// The imput vector should be ordered in terms of trigger threshold (highest prescaled first)
  
  //// function will return true if one of the input trigger names has been passed for this event. 
  //// The input presaler is set to the lowest prescale for the event


  for(unsigned int i=0; i<trigs.size(); i++){
    TString this_check_trig = trigs.at(i);

    //cout << this_check_trig << endl;
    for(unsigned int j=0; j<j_HLT_TriggerName.size(); j++){

      //cout << j_HLT_TriggerName.at(j) << endl;
      if( j_HLT_TriggerName.at(j).find(this_check_trig)!=std::string::npos ){
        return true;
      }
    }

  }
  return false;

  
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
