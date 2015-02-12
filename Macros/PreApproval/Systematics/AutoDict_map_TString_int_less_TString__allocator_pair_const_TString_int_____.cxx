#include "map"
#include "TString.h"
#include "TString.h"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class map<TString,int,less<TString>,allocator<pair<const TString,int> > >+;
#pragma link C++ class map<TString,int,less<TString>,allocator<pair<const TString,int> > >::*;
#pragma link C++ operators map<TString,int,less<TString>,allocator<pair<const TString,int> > >::iterator;
#pragma link C++ operators map<TString,int,less<TString>,allocator<pair<const TString,int> > >::const_iterator;
#pragma link C++ operators map<TString,int,less<TString>,allocator<pair<const TString,int> > >::reverse_iterator;
#endif
