#ifndef JetPlots_h
#define JetPlots_h

#include "StdPlots.h"
#include "KJet.h"
/// Root includes                                                                                                                                                                                                                                                                                                                                                         
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"



class JetPlots : public StdPlots{

  Double_t dijetmass_tmp, dijetmass;

 public:

  JetPlots();

  // Main constructor                                                                                                                                                                                                                                                                                                                                                     
  JetPlots(TString name);

  // Destructor                                                                                                                                                                                                                                                                                                                                                           
  ~JetPlots();


  /// Get Map                                                                                                                                                                                                                                                                                                                                                             
  inline std::map<TString, TH1*> GetMap() const{return map_sig;}

  /// copy constructor                                                                                                                                                                                                                                                                                                                                                    
  JetPlots(const JetPlots& sp);  ///Copy constructor                                                                                                                                                                                                                                                                                                            
  /// assigment operator                                                                                                                                                                                                                                                                                                                                                  
  JetPlots& operator=(const JetPlots& obj);
  float GetElectronISOEA(float eta);

  /// fill functions                                                                                                                                                                                                                                                                                                                                                      
  void Fill(Double_t weight, std::vector<snu::KJet> jets);
  void Fill(TString name, double value, double weight);

  /// function to write out hists                                                                                                                                                                                                                                                                                                                                         
  void Write();

 private:
  std::map<TString, TH1*> map_sig;


  
};

#endif

