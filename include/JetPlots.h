#ifndef JetPlots_h
#define JetPlots_h

#include "StdPlots.h"
#include "KJet.h"


class JetPlots : public StdPlots{
 public:

  JetPlots();

  // Constructor
  JetPlots(TString name);
  
  /// Destructor
  ~JetPlots();

  /// copy constructor
  JetPlots(const JetPlots& mp);  ///Copy constructor
  /// assigment operator
  JetPlots& operator=(const JetPlots& obj);

  /// Fill function
  void Fill(Double_t weight, std::vector<snu::KJet> jets);
  void Fill(TString name, double value, double weight);

  /// Get Map
  inline std::map<TString, TH1*> GetMap() const{return map_jet;}


  // Function that writes out hists
  void Write();
  
 private:
  std::map<TString, TH1*> map_jet; 

  
};

#endif

