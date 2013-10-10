#include "include/SelectionFunctions.h"

Bool_t isGoodEvent(Int_t nVertex, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Double_t beamspot_x, Double_t beamspot_y, Bool_t *goodVerticies) {
  if (nVertex>0) { 
    if (nVertex>50) {
      //cout<<"nVertex "<<nVertex<<endl;
      nVertex=50;
    }
    for (Int_t i=0; i<nVertex; i++) {
      if ( Vertex_Ndof[i]>4 && fabs(Vertex_Z[i])<=24 && fabs(sqrt(pow(Vertex_X[i],2)+pow(Vertex_Y[i],2))-sqrt(pow(beamspot_x,2)+pow(beamspot_y,2)))<=2 ) {
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


Bool_t isGoodEvent(Int_t nVertex, std::vector<Bool_t> Vertex_Fake, std::vector<Double_t> Vertex_Ndof, std::vector<Double_t> Vertex_X,  std::vector<Double_t> Vertex_Y, std::vector<Double_t> Vertex_Z, Bool_t *goodVerticies) {
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


Bool_t Zselection(std::vector<Lepton>& leptonColl, Double_t MET) {
  Double_t mass=0;
  Double_t temp_mass=0;
  if (leptonColl.size()==2) {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++) {
        if ( leptonColl[i].charge() != leptonColl[j].charge() ) {
          temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
          if ( fabs(temp_mass-Mass_Z) < fabs(mass-Mass_Z) )
            mass=temp_mass;
        }
      }
    if ( MET < 20 && mass > (Mass_Z-20) && mass < (Mass_Z+20) )
      return true;
    else
      return false;
  }
  else
    return false;
}


Bool_t ZandWveto(std::vector<Lepton>& leptonColl, Double_t MET, Double_t METPhi) {
  Double_t mass=0;
  Double_t temp_mass=0;
  Double_t temp_MT=0;
  Double_t MT=0;
  for(UInt_t w=0; w<leptonColl.size(); w++) {
    temp_MT = sqrt(2.*leptonColl[w].lorentzVec().Et()*MET* (1 - cos(leptonColl[w].lorentzVec().Phi()-METPhi)) );
    if ( temp_MT > MT) 
      MT = temp_MT;
  }
  if (leptonColl.size()>=2) {
    for (UInt_t i=0; i<leptonColl.size()-1; i++)
      for(UInt_t j=i+1; j<leptonColl.size(); j++) {
	if ( leptonColl[i].charge() != leptonColl[j].charge() && leptonColl[i].lorentzVec().Pt()>20 && leptonColl[j].lorentzVec().Pt()>20) {
	  temp_mass = (leptonColl[i].lorentzVec() + leptonColl[j].lorentzVec()).M();
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



Bool_t TriggerSelector (std::vector<TString> triggernames, std::vector<string> inputtriggers, std::vector<Bool_t> triggerdecision, std::vector<Int_t> HLTPrescales, Int_t &prescaler) {
  for (std::vector<TString>::reverse_iterator it (triggernames.end()); 
        it != std::vector<TString>::reverse_iterator (triggernames.begin()); 
        ++it) {
    for (UInt_t i=0; i<inputtriggers.size(); i++) {
      TString tmpHLT = inputtriggers[i];
      if ( tmpHLT.BeginsWith(*it) && triggerdecision[i] ) {
        //cout<< inputtriggers[i] << " has fired"<<endl;
 	//cout<< "is prescaled by "<<HLTPrescales[i]<<endl<<endl;
        //prescaler=HLTPrescales[i]; 
        return true;
      }
    }
  }
/*
  for (UInt_t i=0; i<inputtriggers.size(); i++) {
    cout<<"inputtriggers "<<inputtriggers[i]<<endl;
    if ( triggerdecision[i] ) {
      TString tmpHLT = inputtriggers[i];
      cout<<"passed inputtriggers OK  "<<inputtriggers[i]<<endl;
      for (std::vector<TString>::iterator it=triggernames.begin(); it !=  triggernames.end(); ++it) 
	if ( tmpHLT.BeginsWith(*it) ) {
          cout<<"SELEZIONATO OK"<<endl<<endl<<endl;
	  return true;
        }
    }
  }
*/
  return false;
}
