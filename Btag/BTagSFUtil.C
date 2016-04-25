#include "BTagSFUtil.h"
//#include "BTagSFPayloadMoriond13.C"
#include "BTagSFPayloadWinter13.C"
//#include "BTagSFPayloadWinter13NoTTbar.C"
#include "BTagEfficienciesTTbarSummer12.C"
//#include "FastSimCorrectionFactors2011.C"
#include "FastSimCorrectionFactorsSummer12.C"

#include "TestEff_ttbar.C"
#include "TestEff_st.C"
#include "TestEff_ttX.C"
#include "TestEff_VJ.C"
#include "TestEff_VV.C"
#include "TestEff_QCD.C"


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

float BTagSFUtil::JetTagEfficiency(int JetFlavor, float JetPt, float JetEta, int what_mc) {

	switch(what_mc){

	case 1: // ttbar
		if (abs(JetFlavor)==5) return TagEfficiencyB_tt(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_tt(JetPt, JetEta);
		else return TagEfficiencyLight_tt(JetPt, JetEta);
    
		break;

	case 2: // st
		if (abs(JetFlavor)==5) return TagEfficiencyB_st(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_st(JetPt, JetEta);
		else return TagEfficiencyLight_st(JetPt, JetEta);

		break;

	case 3: // VV
		if (abs(JetFlavor)==5) return TagEfficiencyB_VV(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_VV(JetPt, JetEta);
		else return TagEfficiencyLight_VV(JetPt, JetEta);

		break;

	case 4: // VJ
		if (abs(JetFlavor)==5) return TagEfficiencyB_VJ(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_VJ(JetPt, JetEta);
		else return TagEfficiencyLight_VJ(JetPt, JetEta);

		break;

	case 5: // ttx
		if (abs(JetFlavor)==5) return TagEfficiencyB_ttx(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_ttx(JetPt, JetEta);
		else return TagEfficiencyLight_ttx(JetPt, JetEta);

		break;

	case 6: // QCD
		if (abs(JetFlavor)==5) return TagEfficiencyB_QCD(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC_QCD(JetPt, JetEta);
		else return TagEfficiencyLight_QCD(JetPt, JetEta);
    
		break;
    
	default:
		if (abs(JetFlavor)==5) return TagEfficiencyB(JetPt, JetEta);
		else if (abs(JetFlavor)==4) return TagEfficiencyC(JetPt, JetEta);
		else return TagEfficiencyLight(JetPt, JetEta);

		break;
	}
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

      float Btag_eff = JetTagEfficiency(JetFlavor, JetPt, fabs(JetEta), 0);

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

void BTagSFUtil::GetBTagEvtWeight(int NJets, float JetPt[], float JetEta[], int JetFlav[], int isTag[], int syst, float &wbtag, float &wbtagErr, int what_mc){
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
		//if( partonFlavor==0 ) continue; //for jets with flavor 0, we ignore. 

		float eff = JetTagEfficiency(partonFlavor, x, eta, what_mc);
		bool istag = (isTag[nj] > 0) ? true: false;

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
		  }  
		  else if(eta>1.6 && eta<=2.4){
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

	return;

}


void BTagSFUtil::GetBTagEvtWeightSF(int NJets, float JetPt[], float JetEta[], float JetFlav[], bool isTag[], int syst, float &wbtag, float &wbtagErr ){
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
		//if( partonFlavor==0 ) continue; //for jets with flavor 0, we ignore. 

		//float eff = JetTagEfficiency(partonFlavor, x, eta);
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
			}  
			else if(eta>1.6 && eta<=2.4){
				SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
				max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
				min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
			}

			SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
			SF += syst*SFerr;
			
			
		}
		    		
		if(istag){
			//mcTag *= eff; 
			dataTag *= SF; 

			if(partonFlavor==5 || partonFlavor ==4)  err1 += SFerr/SF; ///correlated for b/c
			else err3 += SFerr/SF; //correlated for light
      
		}else{
			//mcNoTag *= (1- eff); 
			//dataNoTag *= (1- SF); 
      
			//if(partonFlavor==5 || partonFlavor ==4 ) err2 += (-eff*SFerr)/(1-eff*SF); /// /correlated for b/c
			//else err4 +=  (-eff*SFerr)/(1-eff*SF);  ////correlated for light
      
		}

		//std::cout << " For Jet " << nj << ", flav = " <<  partonFlavor << " eff = " << eff << ", istag " << istag << std::endl;
		
    
	}

	
  
	wbtag = (dataNoTag * dataTag ); 
	
	wbtagErr = sqrt( pow(err1+err2,2) + pow( err3 + err4,2)) * wbtag;  ///un-correlated for b/c and light

	//	std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;

	return;

}


void BTagSFUtil::GetMisTagEvtWeight(int NJets, float JetPt[], float JetEta[], float JetFlav[], int syst, float &wbtag, float &wbtagErr, int NBjets){
    //
    // Get mistag btag weight
    // One event can contribute to multiple b-tagging category
    //

    float dataTag = 1.;
    float dataNoTag = 1.;
    float errTag = 0.;
    float errNoTag = 0.;
    
    float err3 = 0;
    float err4 = 0;
    
    
    
    //cout << " == MisTag Weight Called == " << endl;
    
    float SF_Array[NJets];
    float SFerr_Array[NJets];
    float eff_Array[NJets];
    
    for(int nj=0; nj<NJets ;nj++){ //Here we loop over all selected jets ( for our case, pt>30, PF loose ID, etc )
        
        //cout << " == MisTag Weight Called 1== " << endl;
        int partonFlavor = abs(JetFlav[nj]);
        float eta = fabs(JetEta[nj]);
        float x = JetPt[nj];
        
        float eff = JetTagEfficiency(partonFlavor, x, eta, 0);
        
        float SF = 0.;
        float SFerr = 0.;
        
        SF_Array[nj] = SF;
				SFerr_Array[nj] = SFerr;
				eff_Array[nj] = eff;
        
        //if( partonFlavor==0 || partonFlavor==4 || partonFlavor == 5) continue; //for jets with flavor 0, and heavy flavor jets we ignore.
        
        //cout << " == MisTag Weight Called == 2" << endl;

        
        if(x<20) x=20;
        if(x>800) x=800;
        
        float max;
        float min;
        //cout << " == MisTag Weight Called == 3" << endl;
        if(eta<=0.8){
            SF = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
            max = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
            min = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
        }
        else if(eta<=1.6){
            SF = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
            max = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
            min = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
        }
        else if(eta>1.6 && eta<=2.4){
            SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
            max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
            min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
        }
       // cout << " == MisTag Weight Called == 4" << endl;
        SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
        SF += syst*SFerr;
        
        SF_Array[nj] = SF;
        SFerr_Array[nj] = SFerr;
        eff_Array[nj] = eff;
        
    }
    //cout << " == MisTag Weight Called == 5" << endl;
    
    if (NBjets == 0){ // all jets not tagged
        for (int i=0; i<NJets; i++){
            dataNoTag *= (1-eff_Array[i]*SF_Array[i]); // count the tagging probability in data
            err4 += (-eff_Array[i]*SFerr_Array[i])/(1-eff_Array[i]*SF_Array[i]);
        }
        wbtag = dataNoTag;
        wbtagErr = fabs(err4*wbtag);
        
    }
    
    else if (NBjets == 1){ // 1 jets tagged only
        
        float prob[NJets];
        float proberr[NJets];
        
        for (int i=0; i<NJets; i++){
            prob[i] = 1.0;
            proberr[i] = 0.;
        }
        
        for (int i=0; i<NJets; i++){
            for (int k=0; k<NJets; k++){
                if (i==k){
                    prob[i] *= eff_Array[k]*SF_Array[k];
                    proberr[i] += SFerr_Array[k]/SF_Array[k];
                }
                else{
                    prob[i] *= (1-eff_Array[k]*SF_Array[k]);
                    proberr[i] += (-eff_Array[k]*SFerr_Array[k])/(1-eff_Array[k]*SF_Array[k]);
                }
                
                
            }
        }
        
        float wbtagErr2 = 0;
        wbtag = 0 ;
        for (int i=0; i<NJets; i++){
            wbtag += prob[i];
            wbtagErr2 += proberr[i]*proberr[i]*prob[i]*prob[i];
        }
        wbtagErr = sqrt(wbtagErr2);
        
    }
    
    else if (NBjets == 2){ // 2 jets tagged only
        
        
        float prob=0;
        float prob_temp=0;
        
        float proberr=0;
        float proberr_temp=0;
        
        for(int i=0; i<NJets-1; i++){
            for(int j=i+1; j<NJets; j++){ // i, j -th jets are tagged
                
                prob_temp=eff_Array[i]*SF_Array[i]*eff_Array[j]*SF_Array[j];
                proberr_temp=SFerr_Array[i]/SF_Array[i]+SFerr_Array[j]/SF_Array[j];
                
                for(int k=0; k<NJets; k++){
                    if (k!=i && k!=j){
                        prob_temp*=(1-eff_Array[k]*SF_Array[k]);
                        proberr_temp+=(-eff_Array[k]*SFerr_Array[k])/(1-eff_Array[k]*SF_Array[k]);
                    }
                }
                
                prob+=prob_temp;
                proberr+=proberr_temp*proberr_temp*prob_temp*prob_temp;
            }// this for*for loop runs NJets*(NJets-1)/2 times total.
        }
        wbtag = prob;
        wbtagErr = sqrt(proberr);
        
        
    }
    else if (NBjets == 4 && NJets == 4){
        for (int i=0; i<NJets; i++){
            dataTag *= eff_Array[i]*SF_Array[i];
            err3 += SFerr_Array[i]/SF_Array[i];
        }
        wbtag = dataTag;
        wbtagErr = fabs(err3*wbtag);
    }
    //	std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;
    
    return;
    
}


void BTagSFUtil::GetMisTagEvtWeight_Y(int NJets, float JetPt[], float JetEta[], float JetFlav[], int syst, float &wbtag, float &wbtagErr, int NBjets,bool combo[], float &weight_case){
    //
    // Get mistag btag weight
    // One event can contribute to multiple b-tagging category
    //
    //added by YJ
    //bool combo[] : boolean info for mistagged b-jet. ex) {1,1,0,0} -> want to make 0-th and 1-th jets mistagged
    //weight_case. mistag rate for the specific mistagging assign.
    
    float dataTag = 1.;
    float dataNoTag = 1.;
    float errTag = 0.;
    float errNoTag = 0.;
    
    float err3 = 0;
    float err4 = 0;
    
    //cout << " == MisTag Weight Called == " << endl;
    
    float SF_Array[NJets];
    float SFerr_Array[NJets];
    float eff_Array[NJets];
    
    for(int nj=0; nj<NJets ;nj++){ //Here we loop over all selected jets ( for our case, pt>30, PF loose ID, etc )
        
      //  cout << " == MisTag Weight Called 1== " << endl;
        int partonFlavor = abs(JetFlav[nj]);
        float eta = fabs(JetEta[nj]);
        float x = JetPt[nj];
        
        float eff = JetTagEfficiency(partonFlavor, x, eta, 0);
        
        float SF = 0.;
        float SFerr = 0.;
        
        SF_Array[nj] = SF;
		SFerr_Array[nj] = SFerr;
		eff_Array[nj] = eff;
        
       // if( partonFlavor==0 || partonFlavor==4 || partonFlavor == 5) continue; //for jets with flavor 0, and heavy flavor jets we ignore.
        
      //  cout << " == MisTag Weight Called == 2" << endl;
        
        
        if(x<20) x=20;
        if(x>800) x=800;
        
        float max;
        float min;
     //   cout << " == MisTag Weight Called == 3" << endl;
        if(eta<=0.8){
            SF = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
            max = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
            min = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
        }
        else if(eta<=1.6){
            SF = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
            max = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
            min = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
        }
        else if(eta>1.6 && eta<=2.4){
            SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
            max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
            min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
        }
     //   cout << " == MisTag Weight Called == 4" << endl;
        SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
        SF += syst*SFerr;
        
        SF_Array[nj] = SF;
        SFerr_Array[nj] = SFerr;
        eff_Array[nj] = eff;
        
    }
   // cout << " == MisTag Weight Called == 5" << endl;
    cout << "sf*eff[0] : " << SF_Array[0]*eff_Array[0] <<" sf*eff[1] : " <<SF_Array[1]*eff_Array[1]<<" sf*eff[2] : " <<SF_Array[2]*eff_Array[2]<<" sf*eff[3] : " << SF_Array[3]*eff_Array[3] <<endl;
    
    if (NBjets == 0){ // all jets not tagged
        for (int i=0; i<NJets; i++){
            dataNoTag *= (1-eff_Array[i]*SF_Array[i]); // count the tagging probability in data
            err4 += (-eff_Array[i]*SFerr_Array[i])/(1-eff_Array[i]*SF_Array[i]);
        }
        wbtag = dataNoTag;
        wbtagErr = fabs(err4*wbtag);
        
    }
    
    else if (NBjets == 1){ // 1 jets tagged only
        
        float prob[NJets];
        float proberr[NJets];
        
        for (int i=0; i<NJets; i++){
            prob[i] = 1.0;
            proberr[i] = 0.;
        }
        
        for (int i=0; i<NJets; i++){
            for (int k=0; k<NJets; k++){
                if (i==k){
                    prob[i] *= eff_Array[k]*SF_Array[k];
                    proberr[i] += SFerr_Array[k]/SF_Array[k];
                }
                else{
                    prob[i] *= (1-eff_Array[k]*SF_Array[k]);
                    proberr[i] += (-eff_Array[k]*SFerr_Array[k])/(1-eff_Array[k]*SF_Array[k]);
                }
                
                
            }
        }
        
        float wbtagErr2 = 0;
        wbtag = 0 ;
        for (int i=0; i<NJets; i++){
            wbtag += prob[i]; 
            wbtagErr2 += proberr[i]*proberr[i]*prob[i]*prob[i];			
        }
        wbtagErr = sqrt(wbtagErr2);
        
    }
    
    else if (NBjets == 2){ // 2 jets tagged only
        
        
        float prob=0;
        float prob_temp=0;
        
        float proberr=0;
        float proberr_temp=0;
        
        for(int i=0; i<NJets-1; i++){
            for(int j=i+1; j<NJets; j++){ // i, j -th jets are tagged
                
                prob_temp=eff_Array[i]*SF_Array[i]*eff_Array[j]*SF_Array[j];
                proberr_temp=SFerr_Array[i]/SF_Array[i]+SFerr_Array[j]/SF_Array[j];
                
                for(int k=0; k<NJets; k++){
                    if (k!=i && k!=j){
                        prob_temp*=(1-eff_Array[k]*SF_Array[k]);
                        proberr_temp+=(-eff_Array[k]*SFerr_Array[k])/(1-eff_Array[k]*SF_Array[k]);
                    }
                }
                
                prob+=prob_temp;
                proberr+=proberr_temp*proberr_temp*prob_temp*prob_temp;
            }// this for*for loop runs NJets*(NJets-1)/2 times total.
        }
        wbtag = prob;
        wbtagErr = sqrt(proberr);
        
        
    }
    else if (NBjets == 4 && NJets == 4){
        for (int i=0; i<NJets; i++){
            dataTag *= eff_Array[i]*SF_Array[i];
            err3 += SFerr_Array[i]/SF_Array[i];
        }
        wbtag = dataTag;
        wbtagErr = fabs(err3*wbtag);
    }
    //for lightjets
    weight_case = 1.;
    for (int i= 0; i<NJets; i++){
        if (combo[i]==true){
            weight_case *= eff_Array[i]*SF_Array[i];
        }
        else {
            weight_case *= (1 - eff_Array[i]*SF_Array[i]);
        }
    }
    //	std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;
    
    return;
    
}


void BTagSFUtil::GetMisTagEvtWeightVbb(int NJets, float JetPt[], float JetEta[], bool btag_f[], int mtag, int syst, float &wbtag, float &wbtagErr, int NBjets){
    //
    // with double tags estimate 3tag contribution
    // 
    //

    float dataTag = 1.;
    float dataNoTag = 1.;
    float errTag = 0.;
    float errNoTag = 0.;
    
    float err3 = 0;
    float err4 = 0;
    
    //cout << " == MisTag Weight Called == " << endl;
    
    float SF_Array[NJets];
    float SFerr_Array[NJets];
    float eff_Array[NJets];
    
    for(int nj=0; nj<NJets ;nj++){ //Here we loop over all selected jets ( for our case, pt>30, PF loose ID, etc )
        
        //cout << " == MisTag Weight Called 1== " << endl;
        int partonFlavor = 0;
        float eta = fabs(JetEta[nj]);
        float x = JetPt[nj];
        
        float eff = JetTagEfficiency(partonFlavor, x, eta, 0);
        
        float SF = 0.;
        float SFerr = 0.;
        
        SF_Array[nj] = SF;
				SFerr_Array[nj] = SFerr;
				eff_Array[nj] = eff;
        
        //cout << " == MisTag Weight Called == 2" << endl;
        
        if(x<20) x=20;
        if(x>800) x=800;
        
        float max;
        float min;
        //cout << " == MisTag Weight Called == 3" << endl;
        if(eta<=0.8){
            SF = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
            max = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
            min = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
        }
        else if(eta<=1.6){
            SF = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
            max = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
            min = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
        }
        else if(eta>1.6 && eta<=2.4){
            SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
            max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
            min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
        }
       // cout << " == MisTag Weight Called == 4" << endl;
        SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
        SF += syst*SFerr;
        
        SF_Array[nj] = SF;
        SFerr_Array[nj] = SFerr;
        eff_Array[nj] = eff;
        
    	}
    //cout << " == MisTag Weight Called == 5" << endl;
    
    	if (NBjets==3){
    		
    		for(int j=0;j<NJets;j++){
    			if(!btag_f[j]) {
    				if(j==mtag) dataTag*=(SF_Array[j]*eff_Array[j]); //want to apply mistag rate for mtag index  				
    				else dataTag*=(1-SF_Array[j]*eff_Array[j]);    			
    			}//if
    		}//for
    	}//if
    	
    	if(NBjets==4){
    	
    		for(int j=0;j<NJets;j++){
    			if(!btag_f[j]) {
    				dataTag*=(SF_Array[j]*eff_Array[j]);   			
    			}
    		}
    	
    	}
    	
    	wbtag=dataTag;
    
    
    //std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;
   
    return;
    
}


void BTagSFUtil::GetMisTagEvtWeightVHF(int NJets, float JetPt[], float JetEta[], bool btag_f[], int mtag, int syst, float &wbtag, float &wbtagErr, int NBjets){
    //
    // with double tags estimate 3tag contribution
    // 
    //

    float dataTag = 1.;
    float dataNoTag = 1.;
    float errTag = 0.;
    float errNoTag = 0.;
    
    float err3 = 0;
    float err4 = 0;
    
    //cout << " == MisTag Weight Called == " << endl;
    
    float SF_Array[NJets];
    float SFerr_Array[NJets];
    float eff_Array[NJets];
    
    for(int nj=0; nj<NJets ;nj++){ //Here we loop over all selected jets ( for our case, pt>30, PF loose ID, etc )
        
        //cout << " == MisTag Weight Called 1== " << endl;
        int partonFlavor = 0;
        float eta = fabs(JetEta[nj]);
        float x = JetPt[nj];
        
        float eff = JetTagEfficiency(partonFlavor, x, eta, 0);
        
        float SF = 0.;
        float SFerr = 0.;
        
        SF_Array[nj] = SF;
				SFerr_Array[nj] = SFerr;
				eff_Array[nj] = eff;
        
        //cout << " == MisTag Weight Called == 2" << endl;
        
        if(x<20) x=20;
        if(x>800) x=800;
        
        float max;
        float min;
        //cout << " == MisTag Weight Called == 3" << endl;
        if(eta<=0.8){
            SF = ((1.07541+(0.00231827*x))+(-4.74249e-06*(x*x)))+(2.70862e-09*(x*(x*x)));
            max = ((1.18638+(0.00314148*x))+(-6.68993e-06*(x*x)))+(3.89288e-09*(x*(x*x)));
            min = ((0.964527+(0.00149055*x))+(-2.78338e-06*(x*x)))+(1.51771e-09*(x*(x*x)));
        }
        else if(eta<=1.6){
            SF = ((1.05613+(0.00114031*x))+(-2.56066e-06*(x*x)))+(1.67792e-09*(x*(x*x)));
            max = ((1.16624+(0.00151884*x))+(-3.59041e-06*(x*x)))+(2.38681e-09*(x*(x*x)));
            min = ((0.946051+(0.000759584*x))+(-1.52491e-06*(x*x)))+(9.65822e-10*(x*(x*x)));
        }
        else if(eta>1.6 && eta<=2.4){
            SF = ((1.05625+(0.000487231*x))+(-2.22792e-06*(x*x)))+(1.70262e-09*(x*(x*x)));
            max = ((1.15575+(0.000693344*x))+(-3.02661e-06*(x*x)))+(2.39752e-09*(x*(x*x)));
            min = ((0.956736+(0.000280197*x))+(-1.42739e-06*(x*x)))+(1.0085e-09*(x*(x*x)));
        }
       // cout << " == MisTag Weight Called == 4" << endl;
        SFerr = fabs(max-SF)>fabs(min-SF)? fabs(max-SF):fabs(min-SF);
        SF += syst*SFerr;
        
        SF_Array[nj] = SF;
        SFerr_Array[nj] = SFerr;
        eff_Array[nj] = eff;
        
    	}
    //cout << " == MisTag Weight Called == 5" << endl;
    cout << "sf*eff[0] : " << SF_Array[0]*eff_Array[0] <<" sf*eff[1] : " <<SF_Array[1]*eff_Array[1]<<" sf*eff[2] : " <<SF_Array[2]*eff_Array[2]<<" sf*eff[3] : " << SF_Array[3]*eff_Array[3] <<endl;
    	if (NBjets==2){
    		
    		for(int j=0;j<NJets;j++){
    		
    			cout<<"dataTag:  "<<dataTag<<endl;
    			if(!btag_f[j]) {
    				if(j==mtag) dataTag*=(SF_Array[j]*eff_Array[j]); //want to apply mistag rate for mtag index  				
    				else dataTag*=(1-SF_Array[j]*eff_Array[j]);    
    				
    				
    							
    			}//if
    		}//for
    	}//if
    
    
    	if (NBjets==3){
    		
    		for(int j=0;j<NJets;j++){
    			if(!btag_f[j]) {
    				if(j!=mtag) dataTag*=(SF_Array[j]*eff_Array[j]); //want to apply mistag rate for mtag index  				
    				else dataTag*=(1-SF_Array[j]*eff_Array[j]);    			
    			}//if
    		}//for
    	}//if
    	
    	if(NBjets==4){
    	
    		for(int j=0;j<NJets;j++){
    			if(!btag_f[j]) {
    				dataTag*=(SF_Array[j]*eff_Array[j]);   			
    			}
    		}
    	
    	}
    	
    	wbtag=dataTag;
    
    
    //std::cout << " Event Weights =  " << wbtag << " +- " << wbtagErr << std::endl;
   
    return;
    
}
