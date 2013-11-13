#include "SelectionFunctions.h"


SelectionFunctions::SelectionFunctions(){
}

SelectionFunctions::~SelectionFunctions(){
}

/// Code contains functions for Selecting Event


Bool_t SelectionFunctions::isGoodEvent(Int_t nVertex, std::vector<Bool_t> Vertex_Fake, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Bool_t *goodVerticies) {

  /// Function checks if the event has a good vertex
  /// The vertices are ordered in terms of pt
  /// The array goodVertices is filled true for the highest energy good vertex
  
  if (nVertex>0) {
    for (Int_t i=0; i<nVertex; i++) {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 && sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))<=2 && !Vertex_Fake[i] ) {
        goodVerticies[i] = true;
	//if(i!=0 ) cout << "GOOD VERTEX NOT 0 vertex" << endl;
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


Bool_t SelectionFunctions::Zselection(std::vector<snu::KParticle>& leptonColl, Double_t MET) {

  /// Input a vector of KElectrons,Muons or KTaus and this function returns true if they pass 
  /// Z->ll selection
  
  Double_t mass=0;
  Double_t temp_mass=0;
  if (leptonColl.size()==2) {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++) {
        if ( leptonColl[i].Charge() != leptonColl[j].Charge() ) {
          temp_mass = (leptonColl[i] + leptonColl[j]).M();
          if ( fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z) )
            mass=temp_mass;
        }
      }
    if ( MET < 20 && mass > (Mass_Z-20) && mass < (Mass_Z+20) )
      return true;
    else return false;
  }/// Check size of lepton collection
  else  return false;
}


Bool_t SelectionFunctions::ZandWveto(std::vector<snu::KParticle>& leptonColl, Double_t MET, Double_t METPhi) {

  Double_t mass=0;
  Double_t temp_mass=0;
  Double_t temp_MT=0;
  Double_t MT=0;
  for(UInt_t w=0; w<leptonColl.size(); w++) {
    temp_MT = sqrt(2.*leptonColl[w].Et()*MET* (1 - cos(leptonColl[w].Phi()-METPhi)) );
    if ( temp_MT > MT) 
      MT = temp_MT;
  }
  if (leptonColl.size()>=2) {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++) {
	if ( leptonColl[i].Charge() != leptonColl[j].Charge() && leptonColl[i].Pt()>20 && leptonColl[j].Pt()>20) {
	  temp_mass = (leptonColl[i] + leptonColl[j]).M();
	  if ( fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z) ) 
	    mass=temp_mass;
	}
      }
  } 
  if ( MET < 20 && MT < 20 && (mass < (Mass_Z-20) || mass > (Mass_Z+20) ) )
    return false;
  else
    return true;
}



Bool_t SelectionFunctions::TriggerSelector(std::vector<TString> triggernames, std::vector<string> inputtriggers, std::vector<Bool_t> triggerdecision, std::vector<Int_t> HLTPrescales, Int_t &prescaler) {

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
	//cout<< inputtriggers[i] << " has fired"<<endl;
	//cout<< "is prescaled by "<<HLTPrescales[i]<<endl<<endl;
	prescaler=HLTPrescales[i]; 
        return true;
      }
    }
  }
  
  return false;
}
