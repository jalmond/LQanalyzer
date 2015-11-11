// $id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQFakeRateCalculator_El Frame - ROOT-based analysis framework for Korea SNU
OB * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/


/// Local includes
#include "FakeRateCalculator_El.h"

//Core includes
#include "Reweight.h"
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (FakeRateCalculator_El);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
FakeRateCalculator_El::FakeRateCalculator_El() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("FakeRateCalculator_El");

  Message("In FakeRateCalculator_El constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();
}


void FakeRateCalculator_El::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //
  
  MakeCleverHistograms(sighist_ee, "SingleLooseElJet");


  return;
}


void FakeRateCalculator_El::ExecuteEvents()throw( LQError ){
  
  if(!PassBasicEventCuts()) return;     /// Initial event cuts  
   
  std::vector<TString> triggerslist_12;
  triggerslist_12.push_back("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_v");
  
  std::vector<TString> triggerslist_17;
  triggerslist_17.push_back("HLT_Ele17_CaloIdL_TrackIdL_IsoVL_v");

  std::vector<TString> triggerslist_23;
  triggerslist_23.push_back("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v");

  std::vector<TString> triggerslist;
  triggerslist.push_back("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v");


  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; //// Make cut on event wrt vertex

  numberVertices = eventbase->GetEvent().nVertices();   
  
  if (MC_pu&&!k_isdata) {
    //weight  = weight * reweightPU->GetWeight( eventbase->GetEvent().nVertices(), k_mcperiod)*MCweight;
    weight = weight * MCweight * eventbase->GetEvent().PileUpWeight();
  }
  
  
  
  std::vector<snu::KElectron> electronLooseColl = GetElectrons("HNLoose");
  std::vector<snu::KElectron> electronTightColl = GetElectrons("POGTight");

  if(electronLooseColl.size()==0) return;
  
  
  if(!isData){
    for(std::vector<snu::KElectron>::iterator it = electronTightColl.begin(); it != electronTightColl.end(); it++){
      weight *=  ElectronScaleFactor(it->Eta(), it->Pt(), true);
    }
  }
  

  std::vector<snu::KJet> jetCollTight = GetJets("HNJets");
  std::vector<snu::KJet> jetColl           = GetJets("NoLeptonVeto");

  std::vector<snu::KMuon> muonColl = GetMuons("HNLoose");  // loose selection
 
  if(PassTrigger(triggerslist, prescale) ){
    if(electronTightColl.size() ==2) {
      if(electronTightColl.at(0).Pt() > 25. && electronTightColl.at(1).Pt() > 15. ){
	if(!isData) FillHist("zpeak_ee_noPUrw", GetZMass(electronTightColl), weight/eventbase->GetEvent().PileUpWeight(), 0., 200.,400);
	else FillHist("zpeak_ee_noPUrw", GetZMass(electronTightColl), weight, 0., 200.,400);
	FillHist("zpeak_ee", GetZMass(electronTightColl), weight, 0., 200.,400);
	FillCLHist(sighist_ee, "DiElectron", eventbase->GetEvent(), muonColl,electronTightColl,jetCollTight, weight);
      }
    }
  }

  float prescale_trigger =  GetPrescale(electronLooseColl, PassTrigger(triggerslist_12, prescale), PassTrigger(triggerslist_17, prescale), PassTrigger( triggerslist_23, prescale)); 

  if(electronLooseColl.at(0).Pt() >= 25.){
    if(!PassTrigger(triggerslist_23, prescale) ) return;
  }
  else  if(electronLooseColl.at(0).Pt() >= 20.){
    if(!PassTrigger(triggerslist_17, prescale) ) return;
  }
  else if(electronLooseColl.at(0).Pt() >= 15.){
    if(!PassTrigger(triggerslist_12, prescale) ) return;
  }

  
  if(isData) weight*= prescale_trigger;
  
  
  MakeFakeRatePlots("HNTight", electronTightColl, electronLooseColl,  jetCollTight, jetColl,  prescale_trigger, weight);  
  
  if(electronLooseColl.size() == 1){
    if(jetCollTight.size() >=1) {
      if(jetCollTight.at(0).Pt() > 40.){
	FillCLHist(sighist_ee, "SingleLooseElJet", eventbase->GetEvent(), muonColl,electronTightColl,jetCollTight, weight);
      }
    }
  }
    
  
  return;
}// End of execute event loop


float FakeRateCalculator_El::GetPrescale( std::vector<snu::KElectron> electrons, bool passlow, bool passhigh, bool passhighest){
  
  float prescale_trigger= 1.;
  if(electrons.size() ==1){
    if(electrons.at(0).Pt() >= 25.){

      if(passhighest){
        prescale_trigger = (29.091) / 1280.231 ; //// 20 + GeV bins
      }
      else prescale_trigger = 0.;
    }
    else   if(electrons.at(0).Pt() >= 20.){

      if(passhigh){
	prescale_trigger = (45.24) / 1280.231 ; //// 20 + GeV bins
      }
      else prescale_trigger = 0.;
    }

    else{
      /// if single el event and low pt use 8 GeV trigger
      if(passlow){
        prescale_trigger = (29.091) / 1280.231;
      }
      else prescale_trigger = 0.;
    }
  }

  if(prescale_trigger == 0.) return 0.;
  if(k_isdata) return 1.;
  
  return prescale_trigger;
}


void FakeRateCalculator_El::MakeFakeRatePlots(TString label, std::vector<snu::KElectron> electrons_tight, std::vector<snu::KElectron> electrons,  std::vector<snu::KJet> jets, std::vector<snu::KJet> alljets, float prescale_w, float w){
  
  if(electrons.size() == 0 ) return;
  if(prescale_w==0.) return;
  
  bool useevent20 = UseEvent(electrons , jets, 20., prescale_w, w); 
  bool useevent30 = UseEvent(electrons , jets, 30., prescale_w, w); 
  bool useevent40 = UseEvent(electrons , jets, 40., prescale_w, w); 
  bool useevent60 = UseEvent(electrons , jets, 60., prescale_w, w); 

  bool truth_match= false;
  /// FOR FAKE RATE SUBTRACTION NEED ONLY PROMPT ELECTRONS
  if(!k_isdata) {
    if(electrons.size() > 0){
      /// ONLY INCLUDE ELECTRONS FROM W/Z
      if((electrons.at(0).MCMatched()))  truth_match=true;
    }
    else truth_match = true;
  }
  else truth_match=true;
  
  
  if(jets.size() >= 1){
    if(useevent20)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_20", (prescale_w * w));
    if(useevent30)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_30", (prescale_w * w));
    if(useevent40)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_40", (prescale_w * w));
    if(useevent60)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_allmc_60", (prescale_w * w));
  }

  if(truth_match){

    if(jets.size() >= 1){
      if(useevent20)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_20", (prescale_w * w));
      if(useevent30)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_30", (prescale_w * w));
      if(useevent40)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_40", (prescale_w * w));
      if(useevent60)GetFakeRates(electrons, electrons_tight, jets, alljets,  label+"_60", (prescale_w * w));
    }
  }
}

bool FakeRateCalculator_El::UseEvent(std::vector<snu::KElectron> electrons,  std::vector< snu::KJet> jets, float awayjetcut, float precale_weight, float wt){
  
  bool useevent = false;
  if(precale_weight != 0.){
    
    /// Z and W veto
    Double_t MT=0;
    Double_t METdphi=0;
    for(unsigned int w = 0; w < electrons.size();  w++){
      METdphi = TVector2::Phi_mpi_pi(electrons.at(w).Phi()- eventbase->GetEvent().NoHFMETphi());
      MT = sqrt(2.* electrons.at(w).Et()*eventbase->GetEvent().NoHFMET() * (1 - cos( METdphi)));
      
      if(( (eventbase->GetEvent().NoHFMET() < 20) && (MT < 25.)) ) {
	
        for (unsigned int ielT=0; ielT < electrons.size(); ielT++){
          for(unsigned int ij=0; ij < jets.size(); ij++){
            if(jets.at(ij).Pt() < awayjetcut) continue;
            float dphi =fabs(TVector2::Phi_mpi_pi(electrons.at(ielT).Phi()- jets.at(ij).Phi()));
            if( (jets.at(ij).ChargedEMEnergyFraction()) > 0.65)  continue;
	    if(dphi > 2.5) useevent = true;
          }
        }
      }
    }
  }
  return useevent;
}

void FakeRateCalculator_El::GetFakeRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString tag, double w){

  Float_t ptbins[10] = { 10., 15.,20.,25.,30.,35.,45.,60.,100., 200.};
  Float_t ptbinsb[8] = { 10., 15.,20.,30.,45.,60.,100., 200.};
  Float_t etabin[2] = { 0.,  2.5};
  Float_t etabins[3] = { 0., 1.479,  2.5};
  Float_t etabins2[5] = { 0.,0.8,  1.479, 2.,  2.5};
  Float_t htbins[6] = { 20., 40., 75., 100., 200., 400.};
  Float_t htbinscb[3] = { 20., 100., 400.};


  int nbjet(0);
  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
    if(jets.at(ij).CVSInclV2() > 0.89) nbjet++;
    if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  bool closebjet = false;
  float awayjetpt = 0.;
  for(unsigned int ij =0 ; ij < alljets.size() ; ij++){
    if(loose_el.at(0).DeltaR(alljets.at(ij)) < 0.5) {
      if(alljets.at(ij).CVSInclV2() > 0.89) closebjet = true;
    }     
    float dphi =fabs(TVector2::Phi_mpi_pi(loose_el.at(0).Phi()- alljets.at(ij).Phi()));
    if(dphi > 2.5) awayjetpt = alljets.at(ij).Pt();
    
  }
  
  if( tight_el.size() == 1 && jets.size() >= 1){
    float el_pt = tight_el.at(0).Pt();
    
    // 1D FakeRates
    FillHist(("TightEl" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
    FillHist(("TightEl" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
    if(fabs(tight_el.at(0).Eta()) < 1.5)     FillHist(("TightEl" + tag + "_pt_barrel").Data(),el_pt, w,  ptbins, 9);
    else FillHist(("TightEl" + tag + "_pt_endcap").Data(),el_pt, w,  ptbins, 9);
    
    FillHist(("TightEl" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
    FillHist(("TightEl" + tag + "_eta_binned").Data(),fabs(tight_el.at(0).Eta()), w, etabins, 2);
    FillHist(("TightEl" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    if(fabs(tight_el.at(0).Eta()) < 1.5) FillHist(("TightEl" + tag + "_barrel_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    else FillHist(("TightEl" + tag + "_endcap_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    FillHist(("TightEl" + tag + "_ht_morebins").Data(), SumPt(jets) - awayjetpt, w, 0., 1000., 50);
    FillHist(("TightEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 30., 30);
    FillHist(("TightEl" + tag + "_nbjet").Data(), nbjet, w, 0., 4.,4); 
    
    FillHist(("TightEl" + tag + "_ht_eta").Data(),  SumPt(jets) - awayjetpt,fabs(tight_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
    FillHist(("TightEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets) - awayjetpt, w, ptbins, 9 , htbins, 5);
    FillHist(("TightEl" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
    
    
    if(nbjet > 0){
      FillHist(("TightEl" + tag + "_bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("TightEl" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("TightEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbinsb, 7 , etabins, 2);
    }
    else{
      FillHist(("TightEl" + tag + "_0bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins,9);
      FillHist(("TightEl" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("TightEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);

    }
    
    if(!closebjet){
      if(nbjet > 0){
	FillHist(("TightEl_nocb" + tag + "_bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("TightEl_nocb" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("TightEl_nocb" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbinsb, 7 , etabins, 2);
      }
      else{
	FillHist(("TightEl_nocb" + tag + "_0bjet_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
	FillHist(("TightEl_nocb" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
	FillHist(("TightEl_nocb" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
	FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
	
      }
    }
    
    float ht = SumPt(jets) - awayjetpt;
    if(closebjet){
      FillHist(("TightEl_cb" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl_cb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("TightEl_cb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("TightEl_cb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("TightEl_cb" + tag + "_ht_eta").Data(),  SumPt(jets) - awayjetpt,fabs(tight_el.at(0).Eta()), w, htbinscb, 2 , etabins, 2);
      FillHist(("TightEl_cb" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    }
    else{
      FillHist(("TightEl_nocb" + tag + "_eta").Data(), tight_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("TightEl_nocb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("TightEl_nocb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("TightEl_nocb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("TightEl_nocb" + tag + "_ht_eta").Data(),SumPt(jets)-awayjetpt,fabs(tight_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
      FillHist(("TightEl_nocb" + tag + "_pt_eta").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      
      if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if(nbjet == 0){
	if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_0bjet_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins,2);
	if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
	if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      }
      else{
	if( ht > 20 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
	if( ht > 40 && ht < 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
	if( ht > 100. )    FillHist(("TightEl_nocb" + tag + "_bjet_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
	
      }
    }
    
    if( ht > 20 && ht < 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 40 && ht < 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 100. )    FillHist(("TightEl" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(tight_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    
  }
    
  if(jets.size() >= 1){
    float el_pt = loose_el.at(0).Pt();
    
    if(!isData){
      if(!IsTight(loose_el.at(0))){
for(unsigned int k = 0 ; k <  alljets.size(); k++){
  if(loose_el.at(0).DeltaR(alljets.at(k)) < 0.3){
    FillHist((("JetPt_fakeobject_fakerate" + tag).Data()), alljets.at(k).Pt(), w, 0.,200.,100);
  }
}
      }
      for(unsigned int k = 0 ; k <  alljets.size(); k++){
for(unsigned int k = 0 ; k <  alljets.size(); k++){
  if(loose_el.at(0).DeltaR(alljets.at(k)) < 0.3){
    FillHist((("JetPt_fakeobject_fakerate_all_" + tag).Data()), alljets.at(k).Pt(), w, 0.,200.,100);
  }
}
      }
    }
    
    if(!isData){
      if(!IsTight(loose_el.at(0))){
        for(unsigned int k = 0 ; k <  eventbase->GetGenJets().size(); k++){
          if(loose_el.at(0).DeltaR(eventbase->GetGenJets().at(k)) < 0.3){
            FillHist((("GenJetPt_fakeobject_fakerate" + tag).Data()), eventbase->GetGenJets().at(k).Pt(), w, 0.,200.,100);
          }
        }
      }
      for(unsigned int k = 0 ; k <  alljets.size(); k++){
for(unsigned int k = 0 ; k <  eventbase->GetGenJets().size(); k++){
  if(loose_el.at(0).DeltaR(eventbase->GetGenJets().at(k)) < 0.3){
    FillHist((("GenJetPt_fakeobject_fakerate_all_" + tag).Data()), eventbase->GetGenJets().at(k).Pt(), w, 0.,200.,100);
  }
}
      }
    }



    FillHist(("LooseEl" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
    FillHist(("LooseEl" + tag + "_pt").Data(), el_pt, w,  ptbins, 9);
    if(fabs(loose_el.at(0).Eta()) < 1.5)     FillHist(("LooseEl" + tag + "_pt_barrel").Data(),el_pt, w,  ptbins, 9);
    else FillHist(("LooseEl" + tag + "_pt_endcap").Data(),el_pt, w,  ptbins, 9);

    FillHist(("LooseEl" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
    FillHist(("LooseEl" + tag + "_eta_binned").Data(),fabs(loose_el.at(0).Eta()), w, etabins, 2);
    FillHist(("LooseEl" + tag + "_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
    FillHist(("LooseEl" + tag + "_ht_morebins").Data(), SumPt(jets) - awayjetpt, w, 0., 1000., 50);

    if(fabs(loose_el.at(0).Eta()) < 1.5) FillHist(("LooseEl" + tag + "_barrel_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
    else FillHist(("LooseEl" + tag + "_endcap_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);


    FillHist(("LooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), w, 0., 30., 30);
    FillHist(("LooseEl" + tag + "_nbjet").Data(), nbjet, w, 0., 4.,4);
    
    FillHist(("LooseEl" + tag + "_pt_ht").Data(), el_pt, SumPt(jets)-awayjetpt, w, ptbins, 9 , htbins, 5);
    FillHist(("LooseEl" + tag + "_ht_eta").Data(), SumPt(jets) - awayjetpt,fabs(loose_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
    FillHist(("LooseEl" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);

    if( ( SumPt(jets)-awayjetpt ) < 0. ) cout << "ht is = " << ( SumPt(jets)-awayjetpt ) << endl;

    if(nbjet > 0){
      FillHist(("LooseEl" + tag + "_bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("LooseEl" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbinsb,7 , etabins, 2);
    }
    else{
      FillHist(("LooseEl" + tag + "_0bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
      FillHist(("LooseEl" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
    }
    
    if(!closebjet){
      if(nbjet > 0){
FillHist(("LooseEl_nocb" + tag + "_bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
FillHist(("LooseEl_nocb" + tag + "_bjet_pt").Data(), el_pt, w,  ptbins, 9);
FillHist(("LooseEl_nocb" + tag + "_bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbinsb,7 , etabins, 2);
      }
      else{
FillHist(("LooseEl_nocb" + tag + "_0bjet_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
FillHist(("LooseEl_nocb" + tag + "_0bjet_pt").Data(), el_pt, w,  ptbins, 9);
FillHist(("LooseEl_nocb" + tag + "_0bjet_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins2, 4);
      }
    }

    float ht = SumPt(jets) - awayjetpt;
    if(closebjet){
      FillHist(("LooseEl_cb" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl_cb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("LooseEl_cb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("LooseEl_cb" + tag + "_ht").Data(), SumPt(jets) - awayjetpt, w, htbins, 5);
      FillHist(("LooseEl_cb" + tag + "_ht_eta").Data(),  SumPt(jets)-awayjetpt,fabs(loose_el.at(0).Eta()), w, htbinscb, 2 , etabins, 2);
      FillHist(("LooseEl_cb" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    }
    else{
      FillHist(("LooseEl_nocb" + tag + "_eta").Data(), loose_el.at(0).Eta(), w, -2.5, 2.5,50);
      FillHist(("LooseEl_nocb" + tag + "_pt").Data(),el_pt, w,  ptbins, 9);
      FillHist(("LooseEl_nocb" + tag + "_njets").Data(), jets.size(), w, 0.,5.,5);
      FillHist(("LooseEl_nocb" + tag + "_ht").Data(), SumPt(jets)-awayjetpt, w, htbins, 5);
      FillHist(("LooseEl_nocb" + tag + "_ht_eta").Data(), SumPt(jets)-awayjetpt,fabs(loose_el.at(0).Eta()), w, htbins, 5 , etabins, 2);
      FillHist(("LooseEl_nocb" + tag + "_pt_eta").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);


      if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9, etabins, 2);
      if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);

      if(nbjet == 0){
if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins,9 , etabins, 2);
        if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_0bjet_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
      } 
      else{
if( ht > 20 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
        if( ht > 40 && ht < 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);
        if( ht > 100. )    FillHist(("LooseEl_nocb" + tag + "_bjet_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabin, 1);

      } 
    }
    
    if( ht > 20 && ht < 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht1").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 40 && ht < 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht2").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9 , etabins, 2);
    if( ht > 100. )    FillHist(("LooseEl" + tag + "_pt_eta_ht3").Data(), el_pt, fabs(loose_el.at(0).Eta()),  w, ptbins, 9, etabins, 2);



  }
  
  
  return;
  
}



void FakeRateCalculator_El::GetHSTRates(std::vector<snu::KElectron> loose_el, std::vector<snu::KElectron> tight_el, std::vector<snu::KJet> jets, TString tag){

  Float_t htbins[14] = { 20.,22.5, 25.,27.5, 30.,35.,40.,45.,50.,60.,80.,100.,200., 1000.};

  float tmp_deltaR=1000.;
  for(unsigned int ij =0 ; ij < jets.size() ; ij++){
      if(loose_el.at(0).DeltaR(jets.at(ij)) < tmp_deltaR) tmp_deltaR = loose_el.at(0).DeltaR(jets.at(ij));
  }
  
  if( tight_el.size() == 1 && jets.size() >= 1){
    FillHist(("MeasuredEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("MeasuredEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("MeasuredEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("MeasuredEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);
  }
  
  if( loose_el.size() == 1 && jets.size() >= 1){
    FillHist(("HSTLooseEl" + tag + "_njets").Data(), jets.size(), weight, 0.,5.,5);
    FillHist(("HSTLooseEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), weight, 0., 30., 30);
    FillHist(("HSTLooseEl" + tag + "_ht").Data(), SumPt(jets), weight, htbins, 13);
    FillHist(("HSTLooseEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);    
    
    float hstweight= m_fakeobj->getFakeRate_electronEta(0, loose_el.at(0).Pt(),loose_el.at(0).Eta(), tag);
    FillHist(("PredictedEl" + tag + "_njets").Data(), jets.size(), hstweight, 0.,5.,5);
    FillHist(("PredictedEl" + tag + "_nvertices").Data(), eventbase->GetEvent().nVertices(), hstweight, 0., 30., 30);
    FillHist(("PredictedEl" + tag + "_ht").Data(), SumPt(jets), hstweight, htbins, 13);
    FillHist(("PredictedEl" + tag + "ejetdr").Data(), tmp_deltaR, weight , 0., 5., 50);

  }  
}




void FakeRateCalculator_El::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger<< INFO << "Number of events that pass 17 GeV trigger = " << n_17_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV + jet trigger = " << n_17_jet_pass  << LQLogger::endmsg;
  m_logger<< INFO << "Number of events that pass 17 GeV || jet trigger = " << n_17_17_jet_pass  << LQLogger::endmsg;

}

void FakeRateCalculator_El::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
  if(!k_isdata) reweightPU = new Reweight((analysisdir + "SNUCAT_Pileup.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
  DeclareVariable(out_muons, "Signal_Muons");

  n_17_jet_pass=0;
  n_17_17_jet_pass=0;
  n_17_pass=0;

  
  return;
  
}

FakeRateCalculator_El::~FakeRateCalculator_El() {
  
  Message("In FakeRateCalculator_El Destructor" , INFO);
  if(!k_isdata)delete reweightPU;
  
}



void FakeRateCalculator_El::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void FakeRateCalculator_El::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this FakeRateCalculator_ElCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void FakeRateCalculator_El::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}


