#include <string.h>
#include "TFile.h"
#include "TH2.h"
#include <iostream>
#include "TString.h"
#include <sstream>
#include <iostream>
#include <fstream>


void BTagEff(){


  /*
    KEY: TH2Dh2_BTaggingEff_CSVv2L_Denom_b;1h2_BTaggingEff_CSVv2L_Denom_b
    KEY: TH2Dh2_BTaggingEff_CSVv2L_Num_b;1h2_BTaggingEff_CSVv2L_Num_b
    KEY: TH2Dh2_BTaggingEff_CSVv2M_Denom_b;1h2_BTaggingEff_CSVv2M_Denom_b
    KEY: TH2Dh2_BTaggingEff_CSVv2M_Num_b;1h2_BTaggingEff_CSVv2M_Num_b
    KEY: TH2Dh2_BTaggingEff_CSVv2T_Denom_b;1h2_BTaggingEff_CSVv2T_Denom_b
    KEY: TH2Dh2_BTaggingEff_CSVv2T_Num_b;1h2_BTaggingEff_CSVv2T_Num_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2L_Denom_b;1h2_BTaggingEff_cMVAv2L_Denom_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2L_Num_b;1h2_BTaggingEff_cMVAv2L_Num_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2M_Denom_b;1h2_BTaggingEff_cMVAv2M_Denom_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2M_Num_b;1h2_BTaggingEff_cMVAv2M_Num_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2T_Denom_b;1h2_BTaggingEff_cMVAv2T_Denom_b
    KEY: TH2Dh2_BTaggingEff_cMVAv2T_Num_b;1h2_BTaggingEff_cMVAv2T_Num_b
    
    same for _c and _udsg
  */
  
  TString path= "HNDiElectron_SKTTJets_aMC_cat_v8-0-4.root";

  TFile * f = new TFile(path );

  ofstream lumi_file;
  string lfile =  "BTagEfficienciesTTbarMoriond17.C";
  
  lumi_file.open(lfile.c_str());
  lumi_file.setf(ios::fixed,ios::floatfield);
  
  lumi_file.precision(5);
  lumi_file <<  "/* These Efficiencies have been derived for Summer15ttbar events and should " << endl;
  lumi_file <<  "be used only for the same MC samples or for events with similar topology */  " << endl;

  lumi_file <<  "\n" << endl;

  vector <TString> flavour;
  flavour.push_back("B");
  flavour.push_back("C");
  flavour.push_back("Light");

  vector <TString> fileflavour;
  fileflavour.push_back("b");
  fileflavour.push_back("c");
  fileflavour.push_back("udsg");
  
  for(unsigned int _a = 0; _a < fileflavour.size(); _a++){

    TH2D* numerator  = (TH2D*)f->Get(("h2_BTaggingEff_CSVv2M_Num_"+fileflavour.at(_a)).Data());
    TH2D* denominator  = (TH2D*)f->Get(("h2_BTaggingEff_CSVv2M_Denom_"+fileflavour.at(_a)).Data());
    
    numerator->Divide(denominator);
    
    lumi_file <<  "float BTagSFUtil::TagEfficiency"<< flavour.at(_a)<<"(float JetPt, float JetEta) {" <<endl;
    lumi_file <<  "\n" <<endl;

    vector <TString> taggers;
    taggers.push_back("CSVv2M");
    taggers.push_back("CSVv2T");
    
    for(unsigned int it = 0 ; it < taggers.size() ; it++){
      lumi_file <<  "if (TaggerOP=='"<<taggers.at(it)<<"') { " <<endl;


      std::vector<float> jpt1;
      jpt1.push_back(20.);
      jpt1.push_back(40.);
      jpt1.push_back(60.);
      jpt1.push_back(80.);
      jpt1.push_back(100.);
      jpt1.push_back(120.);
      std::vector<float> jpt2;
      jpt2.push_back(40.);
      jpt2.push_back(60.);
      jpt2.push_back(80.);
      jpt2.push_back(100.);
      jpt2.push_back(120.);
      jpt2.push_back(3000.);
     
      std::vector<float> jeta1;
      jeta1.push_back(0.);
      jeta1.push_back(0.6);
      jeta1.push_back(1.2);
      jeta1.push_back(1.8);
      std::vector<float> jeta2;
      jeta2.push_back(0.6);
      jeta2.push_back(1.2);
      jeta2.push_back(1.8);
      jeta2.push_back(2.4);
      
      for(unsigned int x = 0; x < jpt1.size(); x++){
	if(x == 0)
	  lumi_file <<  "   if (JetPt > "<< jpt1.at(x)<<" && JetPt <= "<<  jpt2.at(x) <<"){  " << endl;
	else
	  lumi_file <<  "   else if (JetPt > "<< jpt1.at(x)<<" && JetPt <= "<<  jpt2.at(x) <<"){  " << endl;

	for(unsigned int y = 0; y < jeta1.size(); y++){
	  if(y == 0)
	    lumi_file <<  "     if      (fabs(JetEta) > " <<jeta1.at(y) <<"   && fabs(JetEta) <= "<<  jeta2.at(y) << ") return " << numerator->GetBinContent(x+1,y+1)<< " ;  " << endl;
	  else
	    lumi_file <<  "     else if (fabs(JetEta) > " <<jeta1.at(y) <<" && fabs(JetEta) <= "<<  jeta2.at(y) << ") return " << numerator->GetBinContent(x+1,y+1)<< ";  " << endl;
	}
	lumi_file <<  "  } " << endl;
      }
      lumi_file <<  " } " << endl;
      
    }
  }
}
