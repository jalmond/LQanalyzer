// $Id: Dec2016_3l4j_SelFuncTest.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQDec2016_3l4j_SelFuncTest Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *
 ***************************************************************************/

/// Local includes
 #include "Dec2016_3l4j_SelFuncTest.h"

 //Core includes
 #include "Reweight.h"
 #include "EventBase.h"                                                                                                                           
 #include "BaseSelection.h"
 #include "AnalyzerCore.h"
 //// Needed to allow inheritance for use in LQCore/core classes
 ClassImp (Dec2016_3l4j_SelFuncTest);

 Dec2016_3l4j_SelFuncTest::Dec2016_3l4j_SelFuncTest() : AnalyzerCore(), out_muons(0) {

   SetLogName("Dec2016_3l4j_SelFuncTest");
   Message("In Dec2016_3l4j_SelFuncTest constructor", INFO);
   InitialiseAnalysis();
 }


 void Dec2016_3l4j_SelFuncTest::InitialiseAnalysis() throw( LQError ) {
   
   /// Initialise histograms
   MakeHistograms();  
   // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
   // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
   Message("Feb2016, HwA analysis", INFO);
   return;
 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Loop///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dec2016_3l4j_SelFuncTest::ExecuteEvents()throw( LQError ){

////Basic Infos///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Apply the gen weight  
   if(!isData) weight*=MCweight;
   FillHist("GenWeight", MCweight, 1, -10, 10, 1000);


  /// Acts on data to remove bad reconstructed event 
//  if(isData&& (! eventbase->GetEvent().LumiMask(lumimask))) return;

   m_logger<<DEBUG<<"RunNumber/Event Number = "<<eventbase->GetEvent().RunNumber()<<" : "<<eventbase->GetEvent().EventNumber()<<LQLogger::endmsg;
   m_logger<<DEBUG<<"isData = "<<isData<<LQLogger::endmsg;

   //Pileup Reweight
   float pileup_reweight=(1.0);//What is this part for? Is it necessary?

/* //Previous Version way of applying PU
   if (!k_isdata) {
     // check if catversion is empty. i.ie, v-7-4-X in which case use reweight class to get weight. In v-7-6-X+ pileupweight is stored in KEvent class, for silver/gold json
     if(eventbase->GetEvent().CatVersion().empty()) pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().nVertices()), k_mcperiod);
     else if(eventbase->GetEvent().CatVersion().find("v7-4") !=std::string::npos)  pileup_reweight = reweightPU->GetWeight(int(eventbase->GetEvent().nVertices()), k_mcperiod);
//     else   pileup_reweight = eventbase->GetEvent().PileUpWeight(lumimask,snu::KEvent::central);
     else   pileup_reweight = eventbase->GetEvent().AltPileUpWeight(lumimask,snu::KEvent::central);
     FillHist("PileupWeight" ,  pileup_reweight,weight,  0. , 50., 1000);

     if(k_sample_name.Contains('DY50plus')) weight*=(3.*1921./6024.);
   }
*/
/*
   if (!k_isdata) {
     // check if catversion is empty. i.ie, v-7-4-X in which case use reweight class to get weight. In v-7-6-X+ pileupweight is stored in KEvent class, for silver/gold json
     pileup_reweight = eventbase->GetEvent().PileUpWeight();

   }
   weight*=pileup_reweight;
*/

   //Total Event  
//   weight=1.;
   FillCutFlow("NoCut", weight);
   //Numbet of Vertex
   if(isData) FillHist("Nvtx_nocut_data", eventbase->GetEvent().nVertices(), weight, 0., 50., 50);
   else  FillHist("Nvtx_nocut_mc", eventbase->GetEvent().nVertices(), weight, 0., 50., 50);

   bool emumu_analysis=false, trimu_analysis=true;

   //Trigers
   std::vector<TString> triggerslist, triggerlist1, triggerlist2;//  ListTriggersAvailable();
   //Besteff: EMu:HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v//MuMu:HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v
   //Top Trig Recommend 
   //emu: HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL || HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL
   //mumu: HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ
   //ee : HLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ 
   // Or with single trig: mu: HLT_IsoMu20 || HLT_IsoTkMu20 //e: HLT_Ele27_eta2p1_WPLoose_Gsf //but e cond diff in 76X

   TString analysis_trigger, analysis_trigger2;
   if(emumu_analysis) {analysis_trigger="HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v";}
     //"HLT_DiMu9_Ele9_CaloIdL_TrackIdL"; analysis_trigger2="HLT_DiMu9_Ele9_CaloIdL_TrackIdL";}
   else if(trimu_analysis) analysis_trigger="HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v";
   triggerslist.push_back(analysis_trigger);//<- Used for DiMuon Sample

//   triggerslist.push_back("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL");
//   triggerslist.push_back("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL");
//   triggerslist.push_back("HLT_IsoMu20");
//   triggerslist.push_back("HLT_IsoTkMu20");
//   HLT_Ele23_WPLoose_Gsf_v // HLT_IsoMu18 // HLT_TripleMu_12_10_5 // HLT_DiMu9_Ele9_CaloIdL_TrackIdL
//   if(!PassTrigger(triggerslist, prescale)) return; //For TriggerCut
   //PassTrigger("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", muons, prescale);
//   if(!PassTrigger(vector<pair<TString,TString> > list)(
//   if(!PassTrigger(analysis_trigger)) return;

//   PassTrigger Uses BeginWith so don't stick to exact name
//   m_logger<<DEBUG<<"passedTrigger "<<LQLogger::endmsg;

   float trigger_ps_weight, weight_trigger_sf;
/*   std::vector<snu::KMuon> trigmuColl; std::vector<snu::KElectron> trigeColl;
     eventbase->GetMuonSel()->SetPt(20.);eventbase->GetMuonSel()->SetEta(2.4);eventbase->GetMuonSel()->SetRelIso(0.15);eventbase->GetMuonSel()->SetID(BaseSelection::MUON_POG_TIGHT);  eventbase->GetMuonSel()->Selection(trigmuColl);
     eventbase->GetElectronSel()->SetPt(20.);eventbase->GetElectronSel()->SetEta(2.4);eventbase->GetElectronSel()->SetID(BaseSelection::ELECTRON_POG_MEDIUM); eventbase->GetElectronSel()->Selection(trigeColl);*/

   trigger_ps_weight=WeightByTrigger(analysis_trigger, TargetLumi);
   weight_trigger_sf=1.;//TriggerScaleFactor(trigeColl, trigmuColl, analysis_trigger);

   FillHist("TriggerSFWeight" , weight_trigger_sf, 1., 0. , 2., 200); FillHist("TriggerPrescale", trigger_ps_weight, 1., 0., 500., 500);
   weight*=weight_trigger_sf*trigger_ps_weight;
   FillCutFlow("TriggerCut", weight); //;in trigger Cut mode
   FillHist("Basic_prescale", prescale, 1., 0., 2000., 2000);

   //Initial Event Cut : https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFilters
   if(!PassMETFilter()) return;  FillCutFlow("EventCut", weight);

   //Vertex Cut
   if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; FillCutFlow("VertexCut", weight);
   //Good Primary vtx def:(vtx.ndof()>4&&maxAbsZ<=0)||std::abs(vtx.z())<= 24)&&((maxd0 <=0)||std::abs(vtx.position().rho())<=2)&&!(vtx.isFake()))  



///////Objects in Analysis/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

   //Primary Object Collection
   std::vector<snu::KTruth> truthColl; eventbase->GetTruthSel()->Selection(truthColl);
   
//     eventbase->GetMuonSel()->SetPt(10.);eventbase->GetMuonSel()->SetEta(2.4);eventbase->GetMuonSel()->SetRelIso(0.25);eventbase->GetMuonSel()->SetID(BaseSelection::MUON_POG_LOOSE);
//   std::vector<snu::KMuon> muonLooseColl; eventbase->GetMuonSel()->Selection(muonLooseColl);
     eventbase->GetMuonSel()->SetID(BaseSelection::MUON_POG_LOOSE);
     eventbase->GetMuonSel()->SetPt(10.);
     eventbase->GetMuonSel()->SetEta(2.4);
     eventbase->GetMuonSel()->SetRelIsoType("PFRelIso03");
     eventbase->GetMuonSel()->SetBSdxy(0.005);
     eventbase->GetMuonSel()->SetBSdz(0.03);
     eventbase->GetMuonSel()->SetRelIso(0.07);
     eventbase->GetMuonSel()->SetChiNdof(3);
   std::vector<snu::KMuon> muonMyColl; eventbase->GetMuonSel()->Selection(muonMyColl);//pt>10/eta<2.4/RelIso03<0.2/MUON_LOOSE
   std::vector<snu::KMuon> muonColl; eventbase->GetMuonSel()->SelectMuons(muonColl, BaseSelection::MUON_POG_LOOSE, 10., 2.4);//pt>10/eta<2.4/RelIso03<0.2/MUON_LOOSE
     eventbase->GetElectronSel()->SetPt(20.);
     eventbase->GetElectronSel()->SetEta(2.5);
     eventbase->GetElectronSel()->SetBETrRegIncl(true);
     eventbase->GetElectronSel()->SetID(BaseSelection::ELECTRON_POG_TIGHT);
     eventbase->GetElectronSel()->SetRelIsoType("PFRelIso04");
     eventbase->GetElectronSel()->SetRelIsoBEMax(0.01, 0.03);
     eventbase->GetElectronSel()->SetdxyBEMax(0.005, 0.01);//,0.01
     eventbase->GetElectronSel()->SetdzBEMax(0.005, 0.01);//,0.01
   std::vector<snu::KElectron> electronMyColl; eventbase->GetElectronSel()->Selection(electronMyColl);//pt>10/eta<2.4(hole region ~1.4 excluded by default)/EGAMMA_LOOSE/NoExtIso*/
   std::vector<snu::KElectron> electronColl; eventbase->GetElectronSel()->SelectElectrons(electronColl, "TEST_TIGHT_1", 20., 2.4);//pt>10/eta<2.4/RelIso03<0.2/MUON_LOOSE
//   std::vector<snu::KElectron> electronColl2; eventbase->GetElectronSel()->SelectElectrons(electronColl2, "TEST_TIGHT_2", 20., 2.4);//pt>10/eta<2.4/RelIso03<0.2/MUON_LOOSE
//   std::vector<snu::KElectron> electronColl; eventbase->GetElectronSel()->SelectElectrons(electronColl, BaseSelection::ELECTRON_POG_TIGHT, 20., 2.4);//pt>10/eta<2.4/RelIso03<0.2/MUON_LOOSE

     eventbase->GetJetSel()->SetPt(20.);
     eventbase->GetJetSel()->SetEta(2.4);
     eventbase->GetJetSel()->SetID(BaseSelection::PFJET_TIGHT);
   std::vector<snu::KJet> jetMyColl;       eventbase->GetJetSel()->Selection(jetMyColl, isData, true);
     eventbase->GetJetSel()->SetPt(20.);
     eventbase->GetJetSel()->SetEta(2.4);
     eventbase->GetJetSel()->SetID(BaseSelection::PFJET_TIGHT);
     eventbase->GetJetSel()->SetUseJetPileUp(true);
     bool LeptonVeto=true;
   std::vector<snu::KJet> jetMyCollVetoed; eventbase->GetJetSel()->Selection(jetMyCollVetoed, LeptonVeto, muonColl, electronColl, isData, true);
   std::vector<snu::KJet> jetColl;         eventbase->GetJetSel()->SelectJets(isData, jetColl, muonColl, electronColl, "PFJET_TIGHT", 20., 2.4, true);
/* 

//   std::vector<int> bIdxColl=GetSFBJetIdx(jetColl,"Medium");
//   std::vector<int> ljIdxColl=GetSFLJetIdx(jetColl, bIdxColl, "Medium");

//   std::vector<snu::KJet> bjetColl; for(int i=0; i<bIdxColl.size(); i++){bjetColl.push_back(jetColl.at(bIdxColl.at(i)));}
//   std::vector<snu::KJet> ljetColl; for(int i=0; i<ljIdxColl.size(); i++){ljetColl.push_back(jetColl.at(ljIdxColl.at(i)));}

   std::vector<snu::KJet> bjetColl = SelBJets(jetColl, "Medium");
   std::vector<snu::KJet> ljetColl = SelLightJets(jetColl, "Medium");

   bool emumu=false, trimu=false;
   int mu1_Ai=-1, mu2_Ai=-1, mu_Wi=-1, j1_Wi=-1, j2_Wi=-1;
   int nbjets=bjetColl.size(); int njets=jetColl.size(); const int nljets=njets-nbjets;//number of light jets

   double met = eventbase->GetEvent().MET();
   double met_x = eventbase->GetEvent().MET()*TMath::Cos(eventbase->GetEvent().METPhi());
   double met_y = eventbase->GetEvent().MET()*TMath::Sin(eventbase->GetEvent().METPhi());
   double Pzv, Pzv_1=0, Pzv_2=0, Pzv_absS=0, Pzv_absL=0, Pzv_dRS=0, Pzv_dRL=0,Pzv_truth=0;
   double Pzv_1_truth=0, Pzv_2_truth=0, Pzv_absS_truth=0;
   snu::KParticle v; v.SetPxPyPzE(met_x, met_y, 0, sqrt(met_x*met_x+met_y*met_y));
   snu::KParticle v_absS, v_truth;
*/
/*
   //Scale Factors
   float id_weight=1., reco_weight=1., iso_weight=1.;
   if(!isData){
     id_weight *= ElectronScaleFactor(BaseSelection::ELECTRON_POG_TIGHT, electronColl);
     id_weight *= MuonScaleFactor(BaseSelection::MUON_POG_TIGHT, muonColl,0);
     iso_weight *= MuonISOScaleFactor(BaseSelection::MUON_POG_TIGHT, muonColl,0);
     reco_weight *= ElectronRecoScaleFactor(electronColl);
     weight*=id_weight*reco_weight*iso_weight;
   }
*/



   ///Basic Objects Distribution//
   //Compare Ne of my electron function and other function
//   FillHist("Ele_Ne_refT", electronColl.size(), 1, 0., 5., 5);
//   FillHist("Ele_Ne", electronMyColl.size(), 1, 0., 5., 5);
   if(electronColl.size()>0){
     if(fabs(electronColl.at(0).Eta())<1.479){
       FillHist("Ele_Iso03_B_refT", electronColl.at(0).PFRelIso(0.3), 1, 0., 0.1, 200);
       FillHist("Ele_Iso04_B_refT", electronColl.at(0).PFRelIso(0.4), 1, 0., 0.1, 200);
       FillHist("Ele_dxy_B_refT", electronColl.at(0).dxy(), 1, 0., 0.2, 200);
       FillHist("Ele_dz_B_refT",  electronColl.at(0).dz(), 1, 0., 0.2, 200);
     }
     else{
       FillHist("Ele_Iso03_E_refT", electronColl.at(0).PFRelIso(0.3), 1, 0., 0.1, 200);
       FillHist("Ele_Iso04_E_refT", electronColl.at(0).PFRelIso(0.4), 1, 0., 0.1, 200);
       FillHist("Ele_dxy_E_refT", electronColl.at(0).dxy(), 1, 0., 0.2, 200);
       FillHist("Ele_dz_E_refT",  electronColl.at(0).dz(), 1, 0., 0.2, 200);
     }    
   }

   if(electronMyColl.size()>0){
     if(fabs(electronMyColl.at(0).Eta())<1.479){
       FillHist("Ele_Iso03_B", electronMyColl.at(0).PFRelIso(0.3), 1, 0., 0.1, 200);
       FillHist("Ele_Iso04_B", electronMyColl.at(0).PFRelIso(0.4), 1, 0., 0.1, 200);
       FillHist("Ele_dxy_B", electronMyColl.at(0).dxy(), 1, -0.2, 0.2, 400);
       FillHist("Ele_dz_B",  electronMyColl.at(0).dz(), 1, -0.2, 0.2, 400);
     }
     else{
       FillHist("Ele_Iso03_E", electronMyColl.at(0).PFRelIso(0.3), 1, 0., 0.1, 200);
       FillHist("Ele_Iso04_E", electronMyColl.at(0).PFRelIso(0.4), 1, 0., 0.1, 200);
       FillHist("Ele_dxy_E", electronMyColl.at(0).dxy(), 1, -0.2, 0.2, 400);
       FillHist("Ele_dz_E",  electronMyColl.at(0).dz(), 1, -0.2, 0.2, 400);
     } 
   }

   if(muonColl.size()>0){
     FillHist("MuL_Iso03_ref", muonColl.at(0).RelIso03(), 1, 0., 0.1, 200);
     FillHist("MuL_Iso04_ref", muonColl.at(0).RelIso04(), 1, 0., 0.1, 200);
     FillHist("MuL_dxy_ref",   muonColl.at(0).dXY(), 1, -0.2, 0.2, 200);
     FillHist("MuL_dz_ref",    muonColl.at(0).dZ(), 1, -0.2, 0.2, 200);
     FillHist("MuL_chi2_ref",  muonColl.at(0).GlobalChi2(), 1, 0., 10., 10);
   }
   if(muonMyColl.size()>0){
     FillHist("MuL_Iso03", muonMyColl.at(0).RelIso03(), 1, 0., 0.1, 200);
     FillHist("MuL_Iso04", muonMyColl.at(0).RelIso04(), 1, 0., 0.1, 200);
     FillHist("MuL_dxy",   muonMyColl.at(0).dXY(), 1, -0.2, 0.2, 200);
     FillHist("MuL_dz",    muonMyColl.at(0).dZ(), 1, -0.2, 0.2, 200);
     FillHist("MuL_chi2",  muonMyColl.at(0).GlobalChi2(), 1, 0., 10., 10);
   }

   if(jetColl.size()>0){
     FillHist("JetT_NjT_ref", jetColl.size(), 1, 0., 10., 10);
     FillHist("JetT_PTj_ref", jetColl.at(0).Pt(), 1, 0., 300., 300);
     FillHist("JetT_Etaj_ref", jetColl.at(0).Eta(), 1, -5., 5., 100);
     if(muonColl.size()>0 && electronColl.size()==0){
       float tmp=0, dRmin=0;
       for(int i=0; i<jetColl.size(); i++){
         for(int j=0; j<muonColl.size(); j++){
           if(i==0 && j==0){ dRmin=jetColl.at(i).DeltaR(muonColl.at(j)); continue; }
           tmp=jetColl.at(i).DeltaR(muonColl.at(j));
           if(tmp<dRmin) dRmin=tmp;
         }
       }
       FillHist("JetT_dRjmumin_ref", dRmin, 1, 0., 5., 200);
     }
     int Nj_nopu=0;
     for(int i=0; i<jetColl.size();i++){
       if(!jetColl.at(i).PileupJetIDLoose()) Nj_nopu++;
     }
     FillHist("JetT_Nj_NotPU_ref", Nj_nopu, 1, 0., 10., 10);
   }
   if(jetMyColl.size()>0){

     FillHist("JetT_NjT_NoVeto", jetMyColl.size(), 1, 0., 10., 10);
     FillHist("JetT_PTj_NoVeto", jetMyColl.at(0).Pt(), 1, 0., 300., 300);
     FillHist("JetT_Etaj_NoVeto", jetMyColl.at(0).Eta(), 1, -5., 5., 100);
     if(muonColl.size()>0 && electronColl.size()==0){
       float tmp=0, dRmin=0;
       for(int i=0; i<jetMyColl.size(); i++){
         for(int j=0; j<muonColl.size(); j++){
           if(i==0 && j==0){ dRmin=jetMyColl.at(i).DeltaR(muonColl.at(j)); continue; }
           tmp=jetMyColl.at(i).DeltaR(muonColl.at(j));
           if(tmp<dRmin) dRmin=tmp;
         }
       }
       FillHist("JetT_dRjmumin_NoVeto", dRmin, 1, 0., 5., 200);
     }
     int Nj_nopu=0;
     for(int i=0; i<jetMyColl.size();i++){
       if(!jetMyColl.at(i).PileupJetIDLoose()) Nj_nopu++;
     }
     FillHist("JetT_Nj_NotPU_NoVeto", Nj_nopu, 1, 0., 10., 10);
   }
   if(jetMyCollVetoed.size()>0){
     FillHist("JetT_NjT_Vetoed", jetMyCollVetoed.size(), 1, 0., 10., 10);
     FillHist("JetT_PTj_Vetoed", jetMyCollVetoed.at(0).Pt(), 1, 0., 300., 300);
     FillHist("JetT_Etaj_Vetoed", jetMyCollVetoed.at(0).Eta(), 1, -5., 5., 100);
     if(muonColl.size()>0 && electronColl.size()==0){
       float tmp=0, dRmin=0;
       for(int i=0; i<jetMyCollVetoed.size(); i++){
         for(int j=0; j<muonColl.size(); j++){
           if(i==0 && j==0){ dRmin=jetMyCollVetoed.at(i).DeltaR(muonColl.at(j)); continue; }
           tmp=jetMyCollVetoed.at(i).DeltaR(muonColl.at(j));
           if(tmp<dRmin) dRmin=tmp;
         }
       }
       FillHist("JetT_dRjmumin_Vetoed", dRmin, 1, 0., 5., 200);
     }
     int Nj_nopu=0;
     for(int i=0; i<jetMyCollVetoed.size();i++){
       if(!jetMyCollVetoed.at(i).PileupJetIDLoose()) Nj_nopu++;
     }
     FillHist("JetT_Nj_NotPU_Vetoed", Nj_nopu, 1, 0., 10., 10);
   }

return;
}// End of execute event loop
  


void Dec2016_3l4j_SelFuncTest::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);

}


void Dec2016_3l4j_SelFuncTest::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  
  string analysisdir = getenv("FILEDIR");  
//  if(!k_isdata) reweightPU = new Reweight((analysisdir + "SNUCAT_Pileup.root").c_str());

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
//  DeclareVariable(out_electrons, "Signal_Electrons", "LQTree");
//  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

Dec2016_3l4j_SelFuncTest::~Dec2016_3l4j_SelFuncTest() {
  
  Message("In Dec2016_3l4j_SelFuncTest Destructor" , INFO);
//  if(!k_isdata)delete reweightPU;
  
}


void Dec2016_3l4j_SelFuncTest::FillCutFlow(TString cut, float weight){
  
  if(GetHist("cutflow")) {
    GetHist("cutflow")->Fill(cut,weight);
  }
  else{
    AnalyzerCore::MakeHistograms("cutflow", 12, 0., 12.);
    GetHist("cutflow")->GetXaxis()->SetBinLabel(1,"NoCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(2,"TriggerCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(3,"EventCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(4,"VertexCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(5,"NlCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(6,"OSmuon");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(7,"NjCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(8,"NbCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(9,"NljCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(10,"lPtCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(11,"MjjCut");
    GetHist("cutflow")->GetXaxis()->SetBinLabel(12,"MmumuCut");
    
  }
}


void Dec2016_3l4j_SelFuncTest::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}



void Dec2016_3l4j_SelFuncTest::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  //Basic Hists/////////////////////////////////////////////////
  AnalyzerCore::MakeHistograms("Ele_Iso03_B_refT", 200, 0., 0.1);


  Message("Made histograms", INFO);
  // **
  // *  Remove//Overide this Dec2016_3l4j_SelFuncTestCore::MakeHistograms() to make new hists for your analysis
  // **
  
}


void Dec2016_3l4j_SelFuncTest::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}

