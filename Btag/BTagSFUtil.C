#include "BTagSFUtil.h"
//#include "BTagSFPayloadMoriond13.C"
#include "BTagSFPayloadWinter13.C"
//#include "BTagSFPayloadWinter13NoTTbar.C"
#include "BTagEfficienciesTTbarSummer12.C"
//#include "FastSimCorrectionFactors2011.C"
#include "FastSimCorrectionFactorsSummer12.C"

BTagSFUtil::BTagSFUtil(TString BTagAlgorithm, TString DataPeriod, TString FastSimDataset, int Seed) {

  rand_ = new TRandom3(Seed);

  GetBTagPayload(BTagAlgorithm, DataPeriod);

  GetFastSimPayload(BTagAlgorithm, FastSimDataset);

  if (TaggerCut<0.) 
    cout << "BTagSFUtil: " << BTagAlgorithm << " not a supported b-tagging algorithm" << endl;

}

BTagSFUtil::~BTagSFUtil() {

  delete rand_;

}

float BTagSFUtil::ScaleFactorB(float JetPt, int SystematicFlag) {
   
  if (JetPt<BTagPtBinEdge[0]) { cout << "SFb is not available for jet pt<20 GeV" << endl; return -1.; }

  float x = JetPt;
  if (JetPt>BTagPtBinEdge[nBTagPtBins]) x = BTagPtBinEdge[nBTagPtBins];
 
  int JetPtBin = -1;
  for (int ptbtagbin = 0; ptbtagbin<nBTagPtBins; ptbtagbin++) 
    if (x>=BTagPtBinEdge[ptbtagbin]) JetPtBin++;
  
  if (JetPt>x) SystematicFlag *= 2;

  float SFb = funSFb->Eval(x) + SystematicFlag*SFb_error[JetPtBin];

  return SFb;

}

float BTagSFUtil::ScaleFactorLight(float JetPt, float JetEta, int SystematicFlag) {
 
  if (JetPt<BTagPtBinEdge[0]) { cout << "SFlight is not available for jet pt<20 GeV" << endl; return -1.; }
 
  int JetEtaBin = -1;
  for (int etabtagbin = 0; etabtagbin<nBTagEtaBins; etabtagbin++) 
    if (fabs(JetEta)>=BTagEtaBinEdge[etabtagbin]) JetEtaBin++;

  float MaxJetPtLight = funSFlight[JetEtaBin][SystematicFlag+1]->GetMaximumX();

  float x = JetPt;
  if (JetPt>MaxJetPtLight) x = MaxJetPtLight;

  return funSFlight[JetEtaBin][SystematicFlag+1]->Eval(x);

}

float BTagSFUtil::ScaleFactorJet(int JetFlavor, float JetPt, float JetEta, int SystematicFlag) {
  
  float SF = -1.;
 
  if (JetPt<BTagPtBinEdge[0]) { cout << "SF is not available for jet pt<20 GeV" << endl; return -1.; }
  if (fabs(JetEta)>2.4) { cout << "SF is not available for jet |eta|>2.4" << endl; return -1.; }

  if (abs(JetFlavor)==5) SF = ScaleFactorB(JetPt, SystematicFlag);
  else if (abs(JetFlavor)==4) SF = ScaleFactorB(JetPt, 2*SystematicFlag);
  else SF = ScaleFactorLight(JetPt, JetEta, SystematicFlag);

  if (SF==-1.) cout << "Jet parameter out of BTV prescriptions" << endl;

  return SF;

}

float BTagSFUtil::FastSimCorrectionFactor(int JetFlavor, float JetPt, float JetEta, int FastSimSystematic) {

  float CF = 1.;
 
  if (JetPt<FastSimPtBinEdge[0]) { cout << "CF is not available for jet pt<" << FastSimPtBinEdge[0] << " GeV" << endl; return -1.; }
  if (fabs(JetEta)>2.4) { cout << "CF is not available for jet |eta|>2.4" << endl; return -1.; }

  int JetFlavorFlag = 2;
  if (abs(JetFlavor)==4) JetFlavorFlag = 1;
  else if (abs(JetFlavor)==5) JetFlavorFlag = 0;
 
  int JetPtBin = -1;
  for (int ptbin = 0; ptbin<nFastSimPtBins; ptbin++) 
    if (JetPt>=FastSimPtBinEdge[ptbin]) JetPtBin++;

  if (JetPt>=FastSimPtBinEdge[nFastSimPtBins]) FastSimSystematic *= 2;

  int JetEtaBin = -1;  
  for (int etabin = 0; etabin<nFastSimEtaBins[JetFlavorFlag]; etabin++) 
    if (fabs(JetEta)>=FastSimEtaBinEdge[etabin][JetFlavorFlag]) JetEtaBin++;
    
  CF = FastSimCF[JetPtBin][JetEtaBin][JetFlavorFlag] + FastSimSystematic*FastSimCF_error[JetPtBin][JetEtaBin][JetFlavorFlag];

  if (CF<0.) CF = 0.; // Effect of large uncertainties on light CFs!

  return CF;

}

float BTagSFUtil::JetTagEfficiency(int JetFlavor, float JetPt, float JetEta) {

  if (abs(JetFlavor)==5) return TagEfficiencyB(JetPt, JetEta);
  else if (abs(JetFlavor)==4) return TagEfficiencyC(JetPt, JetEta);
  else return TagEfficiencyLight(JetPt, JetEta);

}

float BTagSFUtil::GetJetSF(int JetFlavor, float JetPt, float JetEta, int SystematicFlag, int FastSimSystematic) {

  float Btag_SF = ScaleFactorJet(JetFlavor, JetPt, JetEta, SystematicFlag);
  
  if (IsFastSimDataset)
    Btag_SF *= FastSimCorrectionFactor(JetFlavor, JetPt, JetEta, FastSimSystematic);

  return Btag_SF;

}

bool BTagSFUtil::IsTagged(float JetDiscriminant, int JetFlavor, float JetPt, float JetEta, int SystematicFlag, int FastSimSystematic) {
  
  bool isBTagged = JetDiscriminant>TaggerCut;

  if (JetFlavor==-999999) return isBTagged; // Data: no correction needed

  bool newBTag = isBTagged;

  float Btag_SF = GetJetSF(JetFlavor, JetPt, JetEta, SystematicFlag, FastSimSystematic);
  
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


void BTagSFUtil::GetBTagEvtWeight(int NJets, float JetPt[], float JetEta[], float JetFlav[], bool isTag[], int syst, float &wbtag, float &wbtagErr ){
	// 
	// Get Event-by-Event btag weight
	//
	
	float mcTag = 1.;
	float mcNoTag = 1.;
	float dataTag = 1.;
	float dataNoTag = 1.;
	float errTag = 0.;
	float errNoTag = 0.;

	float err1 = 0; 
	float err2 = 0; 
	float err3 = 0; 
	float err4 = 0; 

	//	std::cout << " == BTag Weight Called == " << endl;
	
	for(int nj=0; nj<NJets ;nj++){ //Here we loop over all selected jets ( for our case, pt>30, PF loose ID, etc ) 

		int partonFlavor = abs(JetFlav[nj]);
		float eta = fabs(JetEta[nj]);
		float x = JetPt[nj];
		if( partonFlavor==0 ) continue; //for jets with flavor 0, we ignore. 

		float eff = JetTagEfficiency(partonFlavor, x, eta);
		bool istag = isTag[nj];

		float SF = 0.;
		float SFerr = 0.;

		if(x<20) x=20; 
		if(x>800) x=800;
		

		if(partonFlavor==5 || partonFlavor == 4){ //for b or c. flavJet[indj] refers to the MC-true flavor of the jet

			int JetPtBin = -1;
			for (int ptbtagbin = 0; ptbtagbin<nBTagPtBins; ptbtagbin++) 
				if (x>=BTagPtBinEdge[ptbtagbin]) JetPtBin++;
			
			SFerr = SFb_error[JetPtBin];
			SF  = (0.938887+(0.00017124*x))+(-2.76366e-07*(x*x)) + syst*SFerr;
			
			if(partonFlavor == 4 ) SFerr *= 2; 
		}
		else{
			
			float max;
			float min;
			if(eta<=0.8){
				SF = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
				max = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
				min = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
			}
			else if(eta<=1.6){
				SF = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
				max = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
				min = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
			}  else if(eta>1.6 && eta<=2.4){
				SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
				max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
				min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
			}

			SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
			SF += syst*SFerr;
		}
		    		
		if(istag){
			mcTag *= eff; 
			dataTag *= eff*SF; 

			if(partonFlavor==5 || partonFlavor ==4)  err1 += SFerr/SF; ///correlated for b/c
			else err3 += SFerr/SF; //correlated for light
      
		}else{
			mcNoTag *= (1- eff); 
			dataNoTag *= (1- eff*SF); 
      
			if(partonFlavor==5 || partonFlavor ==4 ) err2 += (-eff*SFerr)/(1-eff*SF); /// /correlated for b/c
			else err4 +=  (-eff*SFerr)/(1-eff*SF);  ////correlated for light
      
		}

		//		std::cout << " For Jet " << nj << ", flav = " <<  partonFlavor << " eff = " << eff << ", istag " << istag << std::endl;
		
    
	}


  
	wbtag = (dataNoTag * dataTag ) / ( mcNoTag * mcTag ); 
	wbtagErr = sqrt( pow(err1+err2,2) + pow( err3 + err4,2)) * wbtag;  ///un-correlated for b/c and light

	//	std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;
}

