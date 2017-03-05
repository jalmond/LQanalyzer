// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagCalibration
#include "BTagSFUtil.h"
#include "BTagCalibrationStandalone.cc"
#include "BTagEfficienciesTTbarMoriond17.C" // Change this to your sample efficiency  
#include "FastSimCorrectionFactorsSummer12.C" // Change this to your sample efficiency NOT UPDATED

BTagSFUtil::BTagSFUtil(string MeasurementType, string BTagAlgorithm, TString OperatingPoint, int SystematicIndex, TString FastSimDataset, int Seed) {

  rand_ = new TRandom3(Seed);
  string lqdir = getenv("LQANALYZER_DIR");
  
  string CSVFileName = (lqdir + "/data/BTag/"+getenv("yeartag") + "/"+ BTagAlgorithm + ".csv").c_str();
  BTagCalibration calib(BTagAlgorithm, CSVFileName);

  string SystematicFlagBC = "central";
  string SystematicFlagL  = "central";
  if (abs(SystematicIndex)<10) {
    if (SystematicIndex==-1 || SystematicIndex==-2) SystematicFlagBC = "down";
    if (SystematicIndex==+1 || SystematicIndex==+2) SystematicFlagBC = "up";
    if (SystematicIndex==-3) SystematicFlagL = "down";
    if (SystematicIndex==+3) SystematicFlagL = "up";
  }

  TaggerCut = -1;
  if (TString(BTagAlgorithm).Contains("CSVv2")) TaggerName="CSVv2";
  if (TString(BTagAlgorithm).Contains("cMVAv2")) TaggerName="cMVAv2";
  
  TaggerOP = TaggerName;

  if (OperatingPoint=="Loose") {
    TaggerOP += "L";
    if (TaggerName=="CSVv2") TaggerCut = 0.5426;
    if (TaggerName=="cMVAv2") TaggerCut =-0.5884;
    reader_bc = new BTagCalibrationReader(&calib, BTagEntry::OP_LOOSE, MeasurementType, SystematicFlagBC);
    reader_l  = new BTagCalibrationReader(&calib, BTagEntry::OP_LOOSE, MeasurementType, SystematicFlagL);
  } else if (OperatingPoint=="Medium") {
    TaggerOP += "M";
    if (TaggerName=="CSVv2") TaggerCut = 0.8484;
    if (TaggerName=="cMVAv2") TaggerCut =0.4432;
    reader_bc = new BTagCalibrationReader(&calib, BTagEntry::OP_MEDIUM, MeasurementType, SystematicFlagBC);
    reader_l  = new BTagCalibrationReader(&calib, BTagEntry::OP_MEDIUM, MeasurementType, SystematicFlagL);
  } else if (OperatingPoint=="Tight") {
    TaggerOP += "T";
    if (TaggerName=="CSVv2") TaggerCut = 0.9535;
    if (TaggerName=="cMVAv2") TaggerCut =0.9432;
    reader_bc = new BTagCalibrationReader(&calib, BTagEntry::OP_TIGHT, MeasurementType, SystematicFlagBC);
    reader_l  = new BTagCalibrationReader(&calib, BTagEntry::OP_TIGHT, MeasurementType, SystematicFlagL);
  } 

  if (TaggerCut==-1) 
    cout << " " << TaggerName << " not supported for " << OperatingPoint << " WP" << endl;

  FastSimSystematic = 0;
  if (abs(SystematicIndex)>10) FastSimSystematic = SystematicIndex%10;
  GetFastSimPayload(BTagAlgorithm, FastSimDataset);

  if (TaggerCut==-1) 
    cout << "BTagSFUtil: " << BTagAlgorithm << " not a supported b-tagging algorithm" << endl;

}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;

}

float BTagSFUtil::FastSimCorrectionFactor(int JetFlavor, float JetPt, float JetEta) {

  float CF = 1.;
 
  if (JetPt<FastSimPtBinEdge[0]) { cout << "CF is not available for jet pt<" << FastSimPtBinEdge[0] << " GeV" << endl; return -1.; }
  if (fabs(JetEta)>2.4) { cout << "CF is not available for jet |eta|>2.4" << endl; return -1.; }

  int JetFlavorFlag = 2;
  if (abs(JetFlavor)==4) JetFlavorFlag = 1;
  else if (abs(JetFlavor)==5) JetFlavorFlag = 0;

  int ThisFastSimSystematic = 0;
  if (abs(FastSimSystematic)==JetFlavorFlag+1) 
    ThisFastSimSystematic = FastSimSystematic/abs(FastSimSystematic);
 
  int JetPtBin = -1;
  for (int ptbin = 0; ptbin<nFastSimPtBins; ptbin++) 
    if (JetPt>=FastSimPtBinEdge[ptbin]) JetPtBin++;

  if (JetPt>=FastSimPtBinEdge[nFastSimPtBins]) ThisFastSimSystematic *= 2;

  int JetEtaBin = -1;  
  for (int etabin = 0; etabin<nFastSimEtaBins[JetFlavorFlag]; etabin++) 
    if (fabs(JetEta)>=FastSimEtaBinEdge[etabin][JetFlavorFlag]) JetEtaBin++;
    
  CF = FastSimCF[JetPtBin][JetEtaBin][JetFlavorFlag] + ThisFastSimSystematic*FastSimCF_error[JetPtBin][JetEtaBin][JetFlavorFlag];

  if (CF<0.) CF = 0.; // Effect of large uncertainties on light CFs!

  return CF;

}

float BTagSFUtil::JetTagEfficiency(int JetFlavor, float JetPt, float JetEta) {

  if (abs(JetFlavor)==5) return TagEfficiencyB(JetPt, JetEta);
  else if (abs(JetFlavor)==4) return TagEfficiencyC(JetPt, JetEta);
  else return TagEfficiencyLight(JetPt, JetEta);

}

float BTagSFUtil::GetJetSF(int JetFlavor, float JetPt, float JetEta) {


  /// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco for pt range and systematic correlations
  float Btag_SF;

  float ThisJetPt = JetPt;
  if(TaggerName.Contains("cMVAv2")){
    if(abs(JetFlavor)==4 || abs(JetFlavor)==5){
      if     (JetPt > 599.99)             ThisJetPt = 599.99;
      else if(JetPt < 30. && JetPt > 20.) ThisJetPt = 30.01;
      else                                return 1.;
    }
    else{
      if     (JetPt > 999.99) ThisJetPt = 999.99;
      else if(JetPt < 20.)    return 1.; 
    }
  }
  else if(TaggerName.Contains("CSVv2")){
    if     (JetPt > 999.99) ThisJetPt = 999.99;
    else if(JetPt < 20.   ) return 1.; 
  }
  else return 1.; //For safety.


  if (abs(JetFlavor)==5) 
    Btag_SF = reader_bc->eval(BTagEntry::FLAV_B, JetEta, ThisJetPt);
  else if (abs(JetFlavor)==4) 
    Btag_SF = reader_bc->eval(BTagEntry::FLAV_C, JetEta, ThisJetPt);
  else Btag_SF = reader_l->eval(BTagEntry::FLAV_UDSG, JetEta, ThisJetPt);
  
  if (IsFastSimDataset)
    Btag_SF *= FastSimCorrectionFactor(JetFlavor, JetPt, JetEta);
  
  return Btag_SF;

}

bool BTagSFUtil::IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta) {
  
  bool isBTagged = JetDiscriminant>TaggerCut;

  if (JetFlavor==-999999) return isBTagged; // Data: no correction needed

  bool newBTag = isBTagged;

  float Btag_SF = GetJetSF(JetFlavor, JetPt, JetEta);
  
  if (Btag_SF == 1) return newBTag; //no correction needed 

  //throw die
  float coin = rand_->Uniform(1.);    
 
  if(Btag_SF > 1){  // use this if SF>1

    if( !isBTagged ) {

      float Btag_eff = JetTagEfficiency(JetFlavor, JetPt, fabs(JetEta));

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1./Btag_eff) );
      
      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;

}
