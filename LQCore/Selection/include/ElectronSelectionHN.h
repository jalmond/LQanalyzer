#ifndef ElectronSelectionHN_h
#define ElectronSelectionHN_h

#include "KElectron.h"

using namespace snu;

bool HNVetoElectronSelection(snu::KElectron el);
bool HNLooseElectronSelection( snu::KElectron el , bool usetight, bool loosend0, float isocut);
bool HNIsTight(snu::KElectron el);
bool HNIsTight(snu::KElectron el, double dxycut, double isocut,  bool usetight);
bool HNTightElectronSelection(snu::KElectron el );
bool PassUserID_FakeLoose (snu::KElectron el, bool usetight, bool loosend0,   float looseisocut);

#endif
