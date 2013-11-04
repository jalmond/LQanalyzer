#include "GenSelection.h"

GenSel::GenSel(){
}

GenSel::GenSel(LQEvent ev){
  k_lqevent = ev;  
};

GenSel::~GenSel() {};

void GenSel::GenSelection(std::vector<snu::KTruth>& truthColl) {

  std::vector<snu::KTruth> truth_particles = k_lqevent.GetBaseTruth();  
  
  for (std::vector<snu::KTruth>::iterator trit = truth_particles.begin(); trit!=truth_particles.end(); trit++){
    
    truthColl.push_back(*trit);
  }

  return;
}




GenSel& GenSel::operator= (const GenSel& ms) {
  if(this != &ms){    
    k_lqevent = ms.k_lqevent;  
  }
  return *this;
};

GenSel::GenSel(const GenSel& ms){
  k_lqevent = ms.k_lqevent;  
};
