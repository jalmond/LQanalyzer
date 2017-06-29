// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiLepton Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNDiLepton.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to samevallow inheritance for use in LQCore/core classes
ClassImp (HNDiLepton);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiLepton::HNDiLepton() :  AnalyzerCore(),  out_electrons(0) {

  mapcounter.clear();

  _mm_channel=false;
  _ee_channel=false;

  functionality = HNDiLepton::VALIDATION;


  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiLepton");

  Message("In HNDiLepton constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

}


void HNDiLepton::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   MakeCleverHistograms(sighist_mmm,"WZMuon");
   MakeCleverHistograms(sighist_mmm,"ZZMuon1");
   MakeCleverHistograms(sighist_mmm,"ZZMuon2");
   MakeCleverHistograms(sighist_mm, "SSMMloose");
   MakeCleverHistograms(sighist_mm, "SSMM_1Jet");
   MakeCleverHistograms(sighist_mm, "SSMM_DiJet");
   MakeCleverHistograms(sighist_mm, "SSMM_CR");
   MakeCleverHistograms(sighist_mm, "SSMM_LowMass");
   MakeCleverHistograms(sighist_mm, "SSMM_MidMass");
   MakeCleverHistograms(sighist_mm, "SSMM_HighMass");

   MakeCleverHistograms(sighist_mm, "OSMMloose");
   MakeCleverHistograms(sighist_mm, "OSMM_1Jet");
   MakeCleverHistograms(sighist_mm, "OSMM_DiJet");
   MakeCleverHistograms(sighist_mm, "OSMM_CR");
   MakeCleverHistograms(sighist_mm, "OSMM_LowMass");
   MakeCleverHistograms(sighist_mm, "OSMM_MidMass");
   MakeCleverHistograms(sighist_mm, "OSMM_HighMass");

   return;
}


void HNDiLepton::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;

  if(!isData)weight*= MCweight;

  _mm_channel =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return;
  if(!PassMETFilter()) return;     /// Initial event cuts :                                                                                                                                
  
  if((PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") || PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")))  MakeControlPlots(1,"",weight);
  
  
  
}

void HNDiLepton::FillEventCutFlow(int cf,TString cut,  float weight){

  if(cf==0){
    if(GetHist( "mm_eventcutflow")) {
      GetHist( "mm_eventcutflow")->Fill(cut,weight);

    }
    else{
      AnalyzerCore::MakeHistograms( "mm_eventcutflow",15,0.,15.);

      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(2,"DiLooseMM");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(3,"ElVeto");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(4,"L1Pt");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(5,"L2Pt5");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(6,"L2Pt10");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(7,"L2Pt15");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(8,"L153");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(9,"L153L2");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(10,"SSMMLoose");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(11,"MLL");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(12,"mmdR");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(13,"DiJet");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(14,"DiNewJet");
      GetHist( "mm_eventcutflow")->GetXaxis()->SetBinLabel(15,"SSMMTight");
      
    }

  }
  

}

void HNDiLepton::FillEventCutFlow(TString cut, TString label, float weight){


  if(GetHist(label + "_eventcutflow")) {
    GetHist(label + "_eventcutflow")->Fill(cut,weight);

  }
  else{
    AnalyzerCore::MakeHistograms(label + "_eventcutflow",10,0.,10.);

    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(1,"SSMM_loose");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(2,"SSMM_tightiso");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(3,"SSMM_tightiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(4,"SSMM_tightmdiso1");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(5,"SSMM_tightmdiso2");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(6,"SSMM_tightmdiso3");
    GetHist(label + "_eventcutflow")->GetXaxis()->SetBinLabel(7,"SSMM_tightmdiso4");
  }
  
}




void HNDiLepton::MakeControlPlots(int method, TString methodtag, float w)throw( LQError ){
  if(_mm_channel) MakeControlPlotsMM(method, methodtag, w);
  //if(_ee_channel) MakeControlPlotsEE(method, methodtag, w);
}

void HNDiLepton::MakeControlPlotsMM(int method, TString methodtag, float w)throw( LQError ){
  
  std::vector<snu::KMuon> muons_veto         = GetMuons("MUON_HN_VETO");
  std::vector<snu::KElectron> electrons_veto = GetElectrons("ELECTRON_HN_VETO");
  
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");
  std::vector<snu::KJet> alljets = GetJets("JET_NOLEPTONVETO");
  std::vector<snu::KJet> hnjets = GetJets("JET_HN");
  //std::vector<snu::KJet> hnjets =  hn04jets;
  //GetJetsWFT("JET_HN","FATJET_HN");
  
  float puweight = 1.;
  if(!isData){
    if(GetMCPeriodRandom() < 6) puweight=eventbase->GetEvent().PileUpWeight(snu::KEvent::down);
    else puweight= mcdata_correction->UserPileupWeight(eventbase->GetEvent(), hnjets.size());
    
    
    w      *= puweight;
    w      *= WeightByTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", TargetLumi)  ;
    w      *= mcdata_correction->TriggerEfficiencyLegByLeg(electrons_veto, muons_veto,  0 , isData, 0);
    
  }
  
  FillEventCutFlow(0,"NoCut",w);

  //// Trigger + MET cits applied already
  // veto el
  if(electrons_veto.size() > 0) return;

  FillEventCutFlow(0,"ElVeto",w);

  if(muons_veto.size()== 2){
    FillEventCutFlow(0,"DiLooseMM",w);

    if(muons_veto[0].Pt() >20.) {
      FillEventCutFlow(0,"L1Pt",w);
      
      if(muons_veto[1].Pt() > 5.) {
	FillEventCutFlow(0,"L2Pt5",w);
	if(muons_veto[1].Pt() > 10.) {
	  FillEventCutFlow(0,"L2Pt10",w);
	  if(muons_veto[1].Pt() < 15.) {
	  FillEventCutFlow(0,"L2Pt15",w);
	  }
	}
      }
    }
  }

  // Make CR plots
  if(SameCharge(muons_veto)) counter ("SSMM_loose",1);
  if(SameCharge(muons_veto))FillEventCutFlow(0,"SSMMLoose",w);
  
  
  std::vector<snu::KMuon>  hn_medium = GetMuons("MUON_HN_MEDIUM",false);

  std::vector<snu::KMuon>  hn_loose =  GetMuons("MUON_HN_LOOSE",false);
  std::vector<snu::KMuon>  hn_tight;
  if(k_running_nonprompt) hn_tight = GetMuons("MUON_HN_LOOSE",false);
  else hn_tight = GetMuons("MUON_HN_TIGHT",false);


  int nbjet = NBJet(hnjets);
  
  if(hn_tight.size() < 2) return;
  if(hn_tight[0].Pt() < 20 ) return;
  if(hn_tight[1].Pt() < 10 ) return;
			     
  if(SameCharge(hn_tight)){
    
    if((hn_tight[0] + hn_tight[1]).M()  > 10.) {
      FillEventCutFlow(0,"MLL",w);
      
      if((hn_tight[0].DeltaR(hn_tight[1])) > 0.4){
	FillEventCutFlow(0,"mmdR",w);
	
	if(muons_veto.size() ==2 && electrons_veto.size()==0){
	  if(hnjets.size() >= 2 )   FillEventCutFlow(0,"DiJet",w);
	  
	  //if((hn04jets.size() + fatjetcoll.size()) < 2) return;
	  FillEventCutFlow(0,"DiNewJet",w);
	  
	  
	  if(k_running_nonprompt){
	    float iso1=0.07;
	    float iso2=0.07;
	    if(fabs(hn_tight[0].Eta()) > 1.5)iso1=0.06;
	    if(fabs(hn_tight[1].Eta()) > 1.5)iso2=0.06;
	    
	    TString tag1 = "Tight0.07_0.005_3_0.04";
	    if(fabs(hn_tight[0].Eta()) > 1.5) tag1 = "Tight0.06_0.005_3_0.06";
	    TString tag2 = "Tight0.07_0.005_3_0.04";
	    if(fabs(hn_tight[1].Eta()) >1.5) tag2 = "Tight0.06_0.005_3_0.06";
	    
	    bool cb_1=false;
	    bool cb_2=false;
	    w=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, hn_tight, PassID(hn_tight[0],"MUON_HN_TIGHT"), PassID(hn_tight[1],"MUON_HN_TIGHT"), tag1, tag2,  cb_1, cb_2,"ptcorr_eta", iso1,iso2,false, false);
	    
	  }
	  if(hnjets.size()==1) FillCLHist(sighist_mm, "SSMM_1Jet", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets, fatjetcoll,  w);
	  if(hnjets.size() > 1)FillCLHist(sighist_mm, "SSMM_DiJet", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
	  if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"Low", w))FillCLHist(sighist_mm, "SSMM_LowMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
	  if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"", w))FillCLHist(sighist_mm, "SSMM_MidMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
	  if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"High", w))FillCLHist(sighist_mm, "SSMM_HighMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
	  if(eventbase->GetEvent().PFMET() > 50 || NBJet(hnjets) > 0) FillCLHist(sighist_mm, "SSMM_CR", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
	}
	
      }
    }
  }
  else if(hn_tight.size() ==2){

    if((hn_tight[0] + hn_tight[1]).M()  > 10.) {
      FillEventCutFlow(0,"osMLL",w);

      if((hn_tight[0].DeltaR(hn_tight[1])) > 0.4){
        FillEventCutFlow(0,"osmmdR",w);
	
	if(muons_veto.size() ==2 && electrons_veto.size()==0){
	  if(k_running_nonprompt){
            float iso1=0.07;
            float iso2=0.07;
            if(fabs(hn_tight[0].Eta()) > 1.5)iso1=0.06;
            if(fabs(hn_tight[1].Eta()) > 1.5)iso2=0.06;

            TString tag1 = "Tight0.07_0.005_3_0.04";
            if(fabs(hn_tight[0].Eta()) > 1.5) tag1 = "Tight0.06_0.005_3_0.06";
            TString tag2 = "Tight0.07_0.005_3_0.04";
            if(fabs(hn_tight[1].Eta()) >1.5) tag2 = "Tight0.06_0.005_3_0.06";

            bool cb_1=false;
            bool cb_2=false;
            w=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, hn_tight, PassID(hn_tight[0],"MUON_HN_TIGHT"), PassID(hn_tight[1],"MUON_HN_TIGHT"), tag1, tag2,  cb_1, cb_2,"ptcorr_eta", iso1,iso2,false, false);

          }
	  if(hnjets.size()==1) FillCLHist(sighist_mm, "OSMM_1Jet", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets, fatjetcoll,  w);
          if(hnjets.size() > 1)FillCLHist(sighist_mm, "OSMM_DiJet", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
          if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"Low", w))FillCLHist(sighist_mm, "OSMM_LowMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
          if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"", w))FillCLHist(sighist_mm, "OSMM_MidMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
          if(CheckSignalRegion(true,hn_tight,electrons_veto , hnjets, alljets,"High", w))FillCLHist(sighist_mm, "OSMM_HighMass", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
          if(eventbase->GetEvent().PFMET() > 50 || NBJet(hnjets) > 0) FillCLHist(sighist_mm, "OSMM_CR", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);

	}
      }
    }
  }

  if(SameCharge(hn_medium)){
    if(hnjets.size() > 1)FillCLHist(sighist_mm, "SSMM_med_DiJet", eventbase->GetEvent(), hn_medium, electrons_veto,hnjets, alljets,  fatjetcoll,w);
    
  }
  
  

  if(hn_tight.size() ==3){
    if((nbjet == 0) &&  hn_tight[2].Pt() > 10.){
      
      if(k_running_nonprompt){
	float iso1=0.07;
	float iso2=0.07;
	if(fabs(hn_tight[0].Eta()) > 1.5)iso1=0.06;
	if(fabs(hn_tight[1].Eta()) > 1.5)iso2=0.06;
	
	TString tag1 = "Tight0.07_0.005_3_0.04";
	if(fabs(hn_tight[0].Eta()) > 1.5) tag1 = "Tight0.06_0.005_3_0.06";
	TString tag2 = "Tight0.07_0.005_3_0.04";
	if(fabs(hn_tight[1].Eta()) >1.5) tag2 = "Tight0.06_0.005_3_0.06";
	
	bool cb_1=false;
	bool cb_2=false;
	w     = m_datadriven_bkg->Get_DataDrivenWeight(false,hn_tight, "MUON_HN_TIGHT", hn_tight.size(), electrons_veto,"", 0, "", "");
	
      }
      if(!(muons_veto.size() > 3 ||  electrons_veto.size() > 0)){
	snu::KParticle Z1 = hn_tight[0] + hn_tight[1];
	snu::KParticle Z2 = hn_tight[0] + hn_tight[2];
	snu::KParticle Z3 = hn_tight[1] + hn_tight[2];
	float diff1 = fabs(Z1.M() - 91.19) ;
	float diff2 = fabs(Z2.M() - 91.19) ;
	float diff3 = fabs(Z3.M() - 91.19) ;
	
	bool m_ll4=true;
	
	float diff = 999999999.;
	float el_zpt = 0.;
	float el_wpt = 0.;
	int iZ1(0);
	int iZ2(0);
	if(Z1.Charge() == 0){
	  diff = diff1;
	  el_zpt = hn_tight[0].Pt();
	  el_wpt = hn_tight[2].Pt();
	  iZ1=0;
	  iZ1=1;
	  if(Z1.M() < 4.) m_ll4=false;
	}
	if( (diff2 < diff) && (Z2.Charge() == 0)){
	  diff= diff2;
	  el_zpt= hn_tight[0].Pt();
	  el_wpt = hn_tight[1].Pt();
	  iZ1=0;
	  iZ1=2;
	  if(Z2.M() < 4.) m_ll4=false;
	}
	if( (diff3 < diff) && (Z3.Charge() == 0)){
	  diff= diff3;
	  el_zpt= hn_tight[1].Pt();
	  el_wpt = hn_tight[0].Pt();
	  iZ1=1;
	  iZ1=2;
	  if(Z3.M() < 4.) m_ll4=false;
	}
	
	if(diff < 10.){
	  if(el_zpt > 20.){
	    if(eventbase->GetEvent().MET(snu::KEvent::pfmet) > 30.){
	      if(el_wpt > 20.){
		snu::KParticle WZ = hn_tight[0] + hn_tight[1]+ hn_tight[2];
		if(WZ.M() > 100){
		  FillCLHist(sighist_mmm, methodtag+"WZMuon", eventbase->GetEvent(), hn_tight, electrons_veto,hnjets, alljets,  fatjetcoll,w);
		}
	      }
	    }
	  }
	}
      }
    }
  }
  
  std::vector<snu::KMuon>  hn_muonZZ;
  if(k_running_nonprompt) hn_muonZZ = GetMuons("MUON_HN_LOOSE",false);
  else hn_muonZZ = GetMuons("MUON_HN_TIGHT",false);

  if(hn_muonZZ.size() >=4){
    
    if(k_running_nonprompt){
      float iso1=0.07;
      float iso2=0.07;
      if(fabs(hn_muonZZ[0].Eta()) > 1.5)iso1=0.06;
      if(fabs(hn_muonZZ[1].Eta()) > 1.5)iso2=0.06;

      TString tag1 = "Tight0.07_0.005_3_0.04";
      if(fabs(hn_muonZZ[0].Eta()) > 1.5) tag1 = "Tight0.06_0.005_3_0.06";
      TString tag2 = "Tight0.07_0.005_3_0.04";
      if(fabs(hn_muonZZ[1].Eta()) >1.5) tag2 = "Tight0.06_0.005_3_0.06";
      
      bool cb_1=false;
      bool cb_2=false;
      w     = m_datadriven_bkg->Get_DataDrivenWeight(false,hn_tight, "MUON_HN_TIGHT", hn_tight.size(), electrons_veto,"", 0, "", "");

						  
    }
    
    if(!(electrons_veto.size() > 0 )){

      /// Check no OS pairs have m(ll) < 4. geV OR dR(l,l) < 0.02                                                                                                                                                                                                
      bool pass_zz_sel1=true;
      for(unsigned int iel=0; iel < hn_muonZZ.size() -1; iel++){
	for(unsigned int iel2= iel+1; iel2 < hn_muonZZ.size(); iel2++){
	  if( hn_muonZZ[iel].DeltaR(hn_muonZZ[iel2]) < 0.02) pass_zz_sel1=false;
	  snu::KParticle zee = hn_muonZZ[iel] + hn_muonZZ[iel2];
	  if((zee.Charge() == 0) && (zee.M() < 4.)) pass_zz_sel1=false;
	}
      }
      int ich(0);
      /// fill index of vector that has e+ and e- used for finding os pairs                                                                                                                                                                                      
      vector<int> plus_i;
      vector<int> minus_i;
      for(unsigned int iel=0; iel < hn_muonZZ.size(); iel++){
	ich += hn_muonZZ[iel].Charge();
	if(hn_muonZZ[iel].Charge() > 0) plus_i.push_back(iel);
	else minus_i.push_back(iel);
      }
      
      bool pass_zz_sel2(false);
      bool pass_zz_sel3(false); /// jaesungs 2 Z in Z peak (pt Zmu1 > 20. )                                                                                                                                                                                      

      if(ich == 0 && plus_i.size() == 2 && minus_i.size()==2){

	for(int izp = 0 ; izp< 1;izp++){
	  for(int izm = 0 ; izm < 2;izm++){

	    /// loop finds Z e+e- pairs                                                                                                                                                                                                                          
	    snu::KParticle Z1 = hn_muonZZ[plus_i[izp]] + hn_muonZZ[minus_i[izm]];

	    if(fabs(Z1.M() - 91.19) < 10.) {
	      /// Z1 is Zcandidate                                                                                                                                                                                                                               
	      /// now get second Z candidate indices                                                                                                                                                                                                             
	      int izp2 = izp;
	      if(izp2 ==1)izp2=0;
	      else izp2=1;
	      int izm2 = izm;
	      if(izm2 ==1)izm2=0;
	      else izm2=1;
	      // Z2 uses non z1 electrons                                                                                                                                                                                                                        
	      snu::KParticle Z2= hn_muonZZ[plus_i[izp2]] + hn_muonZZ[minus_i[izm2]];
	      if(fabs(Z2.M() - 91.19) <10.) {
		// this event has 2 Z candidates                                                                                                                                                                                                                 
		pass_zz_sel3=true;
		if( !( (hn_muonZZ[plus_i[izp]].Pt() > 20 ) || (hn_muonZZ[minus_i[izm]].Pt() > 20)) ) pass_zz_sel3=false;
		if( !( (hn_muonZZ[plus_i[izp2]].Pt() > 20 ) || (hn_muonZZ[minus_i[izm2]].Pt() > 20)) ) pass_zz_sel3=false;
		if(pass_zz_sel3) break;
	      }
	    }
	  }
	}
	snu::KParticle Z1cand1 = hn_muonZZ[plus_i[0]] + hn_muonZZ[minus_i[0]];
	snu::KParticle Z2cand1 = hn_muonZZ[plus_i[1]] + hn_muonZZ[minus_i[1]];

	bool cand_found=false;
	bool cand1=true;
	if(!(Z1cand1.M() > 4 && Z1cand1.M() < 120) ) cand1=false;
	if(!(Z2cand1.M() > 4 && Z2cand1.M() < 120) ) cand1=false;

	snu::KParticle Z1cand2 = hn_muonZZ[plus_i[0]] + hn_muonZZ[minus_i[1]];
	snu::KParticle Z2cand2 = hn_muonZZ[plus_i[1]] + hn_muonZZ[minus_i[0]];
	bool cand2=true;
	if(!(Z1cand2.M() > 4 && Z1cand2.M() < 120) ) cand2=false;
	if(!(Z2cand2.M() > 4 && Z2cand2.M() < 120) ) cand2=false;

	if(cand1 || cand1) cand_found=true;

	snu::KParticle Z1, Z2;
	float Zdiff_ev(0.);
	if(cand1){
	  float zcand1diff1 = fabs(Z1cand1.M() - 91.1);
	  float zcand1diff2 = fabs(Z2cand1.M() - 91.1);
	  if(zcand1diff1 < zcand1diff2) {Z1= Z1cand1; Z2=Z2cand1; Zdiff_ev = zcand1diff1;}
	  else  {Z1= Z2cand1; Z2=Z1cand1; Zdiff_ev = zcand1diff2;}
	}
	if(cand2){
	  float zcand2diff1 = fabs(Z1cand2.M() - 91.1);
	  float zcand2diff2 = fabs(Z2cand2.M() - 91.1);
	  if(zcand2diff1 < zcand2diff2) {
	    if(zcand2diff1 < Zdiff_ev) {Z1 = Z1cand2; Z2 = Z2cand2;}
	  }
	  else{
	    if(zcand2diff2 < Zdiff_ev) {Z1 = Z2cand2; Z1 = Z1cand2;}
	  }
	}

	// Z1 is closest to Z mass                                                                                                                                                                                                                               
	// Z2 is other os pair                                                                                                                                                                                                                                   
	if(cand_found&& Z1.M() > 40.) pass_zz_sel2=true;
	if(pass_zz_sel1&&pass_zz_sel3){
	  FillCLHist(sighist_mmmm, methodtag+"ZZMuon1", eventbase->GetEvent(), hn_muonZZ, electrons_veto,hnjets,alljets, w);

	}
	if(pass_zz_sel1&&pass_zz_sel2){
	  FillCLHist(sighist_mmmm, methodtag+"ZZMuon2", eventbase->GetEvent(), hn_muonZZ,electrons_veto,hnjets,alljets, w);
	  //if(Z1.M() > 60 && Z2.M() > 60) FillCLHist(sighist_eeee, "ZZElectron3", eventbase->GetEvent(), muonVetoColl,hn_muonZZ,jets, ev_weight);                                                                                                          
	}
      }
    }
  }// END ZZ CR 
  
  
}



void HNDiLepton::MakeControlPlotsEE(int method, TString methodtag, float w)throw( LQError ){

   return;
}


 

void HNDiLepton::GetOSSignalEfficiency(float w){
  
}
										   
								   



void HNDiLepton::RunAnalysis(TString plottag, TString tightelid, TString vetoelid, TString looseelid){

  
    

  return;
}// End of execute event loop
  

void HNDiLepton::SignalValidation(){
  
  // Check jet properties                                                                                                                                                                                                                                                                                                   

}
 

void HNDiLepton::GetTriggEfficiency(){
  //ListTriggersAvailable();                                                                                                                                                                                                                                                                                                                                                      
  vector<int> pt1;
  pt1.push_back(18);
  pt1.push_back(35);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(30);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(30);
  pt1.push_back(120);
  pt1.push_back(20);
  pt1.push_back(25);
  pt1.push_back(25);
  vector<int>pt2;
  pt2.push_back(10);
  pt2.push_back(35);
  pt2.push_back(25);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(10);
  pt2.push_back(10);
  pt2.push_back(15);
  pt2.push_back(15);
  pt2.push_back(15);


  std::vector<TString> lists_triggers;
  lists_triggers.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");
  lists_triggers.push_back("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL_v");
  lists_triggers.push_back("HLT_DoubleEle24_22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele22_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele23_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  lists_triggers.push_back("HLT_Ele27_eta2p1_WPLoose_Gsf_HT200");
  lists_triggers.push_back("HLT_Ele115_CaloIdVT_GsfTrkIdT_v");
  lists_triggers.push_back("HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v");
  lists_triggers.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_L1JetTauSeeded_v1");
  for(unsigned int i=0; i < lists_triggers.size(); i++){
    FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator_nojet", lists_triggers );
  }

  std::vector<snu::KJet> jets=GetJets("JET_HN");
  std::vector<snu::KElectron> electrons= GetElectrons("ELECTRON_POG_TIGHT");
  if(jets.size() > 1){
    for(unsigned int i=0; i < lists_triggers.size(); i++){
      TString trig=lists_triggers.at(i);
      FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator", lists_triggers );
      if(PassTrigger(trig))  {
	FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator",lists_triggers );
	
	if(electrons.size() ==2) {
	  
	  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon",lists_triggers );
	  if(electrons.at(0).Pt() > pt1.at(i) && electrons.at(1).Pt() > pt2.at(i))  FillTriggerEfficiency(lists_triggers.at(i), weight, "numerator_dimuon_pt",lists_triggers );
	}
      }
    }
  }
}

void HNDiLepton::FillTriggerEfficiency(TString cut, float weight, TString label, std::vector<TString> list){

  if(GetHist("TriggerEfficiency_" + label)) {
    GetHist("TriggerEfficiency_"+label)->Fill(cut,weight);

  }
  else{
    int ntrig = list.size();
    AnalyzerCore::MakeHistograms("TriggerEfficiency_"+label,ntrig,0.,float(ntrig));

    for(unsigned int it=0; it < list.size(); it++){
      GetHist("TriggerEfficiency_"+label)->GetXaxis()->SetBinLabel(it+1,list.at(it));
    }
  }
  
}


bool HNDiLepton::CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString name, float w){

  bool debug=false;


  if(el.size() > 0) return false ;
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
  // Set by trigger                                                                                                                                                                                                                                                
  if(muons.at(0).Pt() < 20.) {if(debug)cout << "Fail pt1 " << endl; return false;}
  if(muons.at(1).Pt() < 10.)  {if(debug)cout << "Fail pt2  " << endl; return false;}

  if(isss&&!SameCharge(muons)) {if(debug)cout << "Fail ss " << endl; return false;}

  if(!isss&&SameCharge(muons)) {if(debug)cout << "Fail os  " << endl; return false;}
  if(jets.size() < 2) {if(debug)cout << "Fail jets " << endl; return false;}

  snu::KParticle mm = muons.at(0) + muons.at(1);
  if(mm.M()  < 10.) {if(debug)cout << "Fail mee  " << endl; return false;}

  if(name.Contains("Low")){
    if(mm.M()  > 70.) {if(debug)cout << "Fail mee  " << endl; return false;}
  }
  
  float dijetmass_tmp=999.;
  float dijetmass=9990000.;
  int m=-999;
  int n=-999;
  for(UInt_t emme=0; emme<jets.size(); emme++){
    for(UInt_t enne=1; enne<jets.size(); enne++) {
      if(emme == enne) continue;
      dijetmass_tmp = (jets[emme]+jets[enne]).M();
      if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {
        dijetmass = dijetmass_tmp;
        m = emme;
        n = enne;
      }
    }
  }
  snu::KParticle jj = jets.at(m) + jets.at(n) ;

  float dPhi = fabs(TVector2::Phi_mpi_pi(jets[m].Phi() - jets[n].Phi()));
  float contramass=2*jets[m].Pt()*jets[n].Pt()*(1+cos(dPhi));
  contramass=sqrt(contramass);

  if(name.Contains("Low")){
    if(contramass > 100) return false;
    if((jets[0]+jets[1]).M() > 200.) return false;
    if((jets[0] + muons[0] + muons[1]).M() > 250.)  return false;
  }
  else{
    if(jj.M() > 120.) {if(debug)cout << "Fail mjj  " << endl; return false;}
    if(jj.M() < 50.) {if(debug)cout << "Fail mjj  " << endl; return false;}

  }

  if(name.Contains("Low")){
    if(muons.at(0).DeltaR(muons.at(1)) > 3.5) {if(debug)cout << "Fail dr  " << endl; return false;}
  }


  float ST = muons[0].Pt() + muons[1].Pt();
  float looseST = muons[0].Pt() + muons[1].Pt();

  std::vector<snu::KJet> loosejets=GetJets("JET_NOCUT");


  float HT=0.;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    ST+= alljets[ij].Pt();

  }
  for(unsigned int ij=0; ij <jets.size(); ij++){

    HT+= jets[ij].Pt();

  }

  float LT = muons[0].Pt() + muons[1].Pt();
  if(name.Contains("Low")){
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 15.) {if(debug)cout << "Fail met  " << endl; return false;}
    if(eventbase->GetEvent().PFMET() > 80) return false;
  }
  else if(name.Contains("High")){
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 8.) {if(debug)cout << "Fail met  " << endl; return false;}
  }
  else{
    if((pow(eventbase->GetEvent().PFMET(),2.)/ ST) > 12.5) {if(debug)cout << "Fail met  " << endl; return false;}
    if(eventbase->GetEvent().PFMET() > 80) return false;

  }


  float dphi_1 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_1 = sqrt(2.* muons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));

  float dphi_2 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_2 = sqrt(2.* muons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_2)));

  if(name.Contains("Low")){
    if(MT_1 > 100.) return false;
    if(MT_2 > 100.) return false;
    if(ST > 450.)  return false;
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);
    //if(lljj.M() > 300.) return false;                                                                                                                                                                                                                            

  }
  else   if(name.Contains("High")){
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);

    if(ST < 400.)  return false;
    if(lljj.M() < 200.) return false;
    if(muons.at(0).Pt() < 50.) return false;
    if(muons.at(1).Pt() < 25.) return false;
  }
  else{


    if(LT/HT < 0.2)  return false;
    if(LT < 35)  return false;
    if(HT < 35)  return false;

    float dRmj=-999.;
    float ratiomj=0.;
    for(unsigned int im=0; im <muons.size(); im++){
      for(unsigned int ij2=0; ij2 <jets.size(); ij2++){
        if(muons.at(im).DeltaR(jets.at(ij2)) >  0.5){
          if(muons.at(im).DeltaR(jets.at(ij2)) > dRmj){
            dRmj=muons.at(im).DeltaR(jets.at(ij2)) ;
            if(im==0) ratiomj = jets.at(ij2).Pt() / muons[im].Pt();
          }
        }
      }
    }
    if(ratiomj > 3.) return false;
    if(dRmj > 4.5) return false;

    if(muons[0].DeltaR(muons[1]) > 4.) return false;

  }
  if(name.Contains("High")){
    if((muons.at(0).Pt() + muons.at(1).Pt() ) < 50.) return false;
    if (ST < 400. ) return false;

    float mindRjj=999.;
    for(unsigned int ij=0; ij <jets.size()-1; ij++){
      for(unsigned int ij2=ij+1; ij2 <jets.size(); ij2++){
        if(jets.at(ij).DeltaR(jets.at(ij2)) < mindRjj) mindRjj=jets.at(ij).DeltaR(jets.at(ij2)) ;
      }
    }
    //if(mindRjj > 1.5) {if(debug)cout << "Fail dr  " << endl; return false;}                                                                                                                                                                                      
  }

  int nbjet=0;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet++;
  }
  if(nbjet > 0) {if(debug)cout << "Fail nbjet  " << endl; return false;}


  if(debug)cout << "PASSES ID" << endl;
  return true;
}




bool HNDiLepton::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, float evmet, bool runchargeflip , std::vector<float> cuts , TString additional_option){
  
  return OptMassCheckSignalRegion(electrons, jets, 1, evmet, runchargeflip, cuts, additional_option);
}

bool HNDiLepton::OptMassCheckSignalRegion(std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, int btagwp,  float evmet, bool runchargeflip , std::vector<float> cuts, TString additional_option){
  
  return true;

}


bool HNDiLepton::LowMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
  
}

bool HNDiLepton::MidMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
  
 
  return true;
}



	
	

bool HNDiLepton::HighMassCheckSignalRegion(  std::vector<snu::KElectron> electrons, std::vector<snu::KJet> jets, bool runchargeflip){
 

  return true;
}




void HNDiLepton::counter(TString cut, float w){

  map<TString,float>::iterator itmapcounter = mapcounter.find(cut) ;
  if (itmapcounter == mapcounter.end()){
    mapcounter[cut] = w;
  }
  else{
    float sum = itmapcounter->second;
    mapcounter[cut] = sum+w;
  }
  FillEventCutFlow(cut,"",w);

}


void HNDiLepton::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

  for ( map<TString,float>::iterator itmapcounter = mapcounter.begin(); itmapcounter != mapcounter.end(); itmapcounter++){
    cout << itmapcounter->first << " has count "<< itmapcounter->second << endl;
  }

}


void HNDiLepton::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

HNDiLepton::~HNDiLepton() {
  
  Message("In HNDiLepton Destructor" , INFO);
  
}



void HNDiLepton::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiLepton::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiLeptonCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiLepton::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



