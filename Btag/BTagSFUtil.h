/*************************************************************

Class Usage:

This class should only be used for upgrading and downgrading 
if a single operating point is used in an analysis. 

Based on the BTagSFUtil from Michael Segala



 - BTagSFUtil *BTagSF = new BTagSFUtil(BTagAlgorithm, DataPeriod)
   
      where: BTagAlgorithm is the btag algorithm you want to use, ex: "CSVM"
             DataPeriod can be "AB", "C", "D" or "ABCD" (default) for PromptReco data, "ABCD" for Winter13 rereco

 - When running over FastSim MC, the dataset has to be specified to retrive special correction factors:
  
      BTagSFUtil *BTagSF = new BTagSFUtil(BTagAlgorithm, DataPeriod, FastSimDataset)
 
         where the supported FastSim datasets are T1bbbb, T1tttt, T2, T2bb, T2bwm T2tt and T3w

      Note that according to POG prescriptions we are still using 2011 CFs with double uncertainties. 2012 CFs are
      waiting for additional cross checks 
   
 - For applying the SF to a jet:

      BTagSF->IsTagged(DiscriminatorValue, JetFlavor, JetPt, JetEta, SystematicFlag, FastSimSystematic)

         where: DiscriminatorValue is the value for the discrimnant of your choise for the jet to which the SF is applied
                SystematicFlag = 0, +1, -1 if you want to apply the central values of the SF, or the SF +/- 1 sigma respectively
                FastSimSystematic = same as for SystematicFlag, but for the CFs for the FastSim MC

*************************************************************/
 
#include <Riostream.h>
#include "TRandom3.h"
#include "TMath.h"
#include "TF1.h"

class BTagSFUtil{

 public:
    
  BTagSFUtil(TString BTagAlgorithm, TString DataPeriod = "ABCD", TString FastSimDataset = "", int Seed = 0);
  ~BTagSFUtil();

  float GetJetSF(int JetFlavor, float JetPt, float JetEta, int SystematicFlag, int FastSimSystematic = 0);
  bool IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta, int SystematicFlag, int FastSimSystematic = 0);
  void GetBTagEvtWeight(int NJets, float JetPt[], float JetEta[], float JetFlav[], bool isTag[], int syst, float &wbtag, float &wbtagErr);

 private:

  void GetBTagPayload(TString BTagAlgorithm, TString DataPeriod);
  void GetFastSimPayload(TString BTagAlgorithm, TString FastSimDataset);

  float ScaleFactorB(float JetPt, int SystematicFlag);
  float ScaleFactorLight(float JetPt, float JetEta, int SystematicFlag);
  float ScaleFactorJet(int JetFlavor, float JetPt, float JetEta, int SystematicFlag);

  float JetTagEfficiency(int JetFlavor, float JetPt, float JetEta);
  float TagEfficiencyB(float JetPt, float JetEta);
  float TagEfficiencyC(float JetPt, float JetEta);
  float TagEfficiencyLight(float JetPt, float JetEta);

  float FastSimCorrectionFactor(int JetFlavor, float JetPt, float JetEta, int FastSimSystematic);
  
  TRandom3* rand_;

  TString TaggerName;
  float TaggerCut;

  TF1 *funSFb, *funSFlight[4][3];

  int nBTagPtBins;
  float BTagPtBinEdge[50];
  float SFb_error[50];

  int nBTagEtaBins;
  float BTagEtaBinEdge[50];

  bool IsFastSimDataset;
  int nFastSimPtBins, nFastSimEtaBins[3];
  float FastSimPtBinEdge[50], FastSimEtaBinEdge[50][3];
  float FastSimCF[50][2][3];
  float FastSimCF_error[50][2][3];
    
};

