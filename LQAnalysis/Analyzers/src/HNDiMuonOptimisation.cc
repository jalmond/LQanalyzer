// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQHNDiMuonOptimisation Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "HNDiMuonOptimisation.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (HNDiMuonOptimisation);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
HNDiMuonOptimisation::HNDiMuonOptimisation() :  AnalyzerCore(),  out_electrons(0) {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("HNDiMuonOptimisation");

  Message("In HNDiMuonOptimisation constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

}


void HNDiMuonOptimisation::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist



   return;
}


void HNDiMuonOptimisation::ExecuteEvents()throw( LQError ){
  
  m_logger << DEBUG << "RunNumber/Event Number = "  << eventbase->GetEvent().RunNumber() << " : " << eventbase->GetEvent().EventNumber() << LQLogger::endmsg;
  m_logger << DEBUG << "isData = " << isData << LQLogger::endmsg;


  if(!PassMETFilter()) return;

  if(!isData){
    weight*= MCweight;
    weight*=WeightByTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", TargetLumi);
  }

  if (!eventbase->GetEvent().HasGoodPrimaryVertex()) return; 


  /// Get Efficiency of signal + Bkg using multiple triggers                                                                                                                                                                                                                  


  /// Dimuon for mmu channel
  std::vector<TString> triggerlist;
  triggerlist.push_back("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v");
  triggerlist.push_back("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v");

  float trigger_ps_weight= WeightByTrigger(triggerlist, TargetLumi);
  
  bool _dimu =   isData ?  (k_channel.Contains("DoubleMuon")) : true ;
  
  if(PassTrigger(triggerlist[0]) || PassTrigger(triggerlist[1])) OptimiseID(true, true,  true, weight);
  
  std::vector<snu::KElectron> electronVetoColl=GetElectrons("ELECTRON_HN_VETO");
  std::vector<snu::KMuon> muonVetoColl=GetMuons("MUON_HN_VETO");

  if ((electronVetoColl.size() + muonVetoColl.size()) >2) return;
  
  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");
  std::vector<snu::KJet> jets = GetJets("JET_HN");
  FillHist("NFatJets", fatjetcoll.size(), weight, 0., 10., 10);
  FillHist("2DJets", fatjetcoll.size(), jets.size(),  weight, 0., 10., 10,  0., 10., 10);
  for(unsigned int ifjet=0; ifjet < fatjetcoll.size(); ifjet++){
    FillHist(("tau21"), fatjetcoll[ifjet].Tau2()/fatjetcoll[ifjet].Tau1(), weight, 0., 1., 100);
    FillHist(("PrunedMass"), fatjetcoll[ifjet].PrunedMass(),  weight, 0., 200., 100);
    FillHist(("SoftDropMass"), fatjetcoll[ifjet].SoftDropMass(),  weight, 0., 200., 100);
  }
  

}

void HNDiMuonOptimisation::OptimiseID(bool isss, bool dilep, bool removed0, float w){
  
  if (!isData) {
    w*= eventbase->GetEvent().PileUpWeight();
  }
  
  if(1){  
    std::vector<snu::KMuon> snu_loose  = GetMuons("MUON_HN_Tight_FAKELOOSEST",false);
    std::vector<snu::KElectron> el = GetElectrons("ELECTRON_HN_VETO");


    vector<float> vcut_dxy_b;
    vector<TString> vcut_dxy_b_s;

    for(unsigned int dxy_b=0;dxy_b < 10; dxy_b++){
      float cut_dxy_b =  float(dxy_b)*0.005 + 0.01;
      vcut_dxy_b.push_back(cut_dxy_b);
      stringstream ss;
      ss <<cut_dxy_b;
      vcut_dxy_b_s.push_back(TString(ss.str()));
    }
    vector<float> vcut_dxysig_b;
    vcut_dxysig_b.push_back(3.);
    vcut_dxysig_b.push_back(4.);
    vector<TString> vcut_dxysig_b_s;
    vcut_dxysig_b_s.push_back("3");
    vcut_dxysig_b_s.push_back("4");

    vector<float> vcut_dz_b;
    vector<TString> vcut_dz_b_s;

    for(unsigned int dz_b=0;dz_b < 4; dz_b++){
      float cut_dz_b =  float(dz_b)*0.02 + 0.04;
      vcut_dz_b.push_back(cut_dz_b);
      stringstream ss;
      ss <<cut_dz_b;
      vcut_dz_b_s.push_back(TString(ss.str()));
    }

    vector<float> vcut_iso_b;
    vector<TString> vcut_iso_b_s;
    for(unsigned int iso_b=0;iso_b < 5; iso_b++){
      float cut_iso_b = float(iso_b)*0.01 + 0.05;
      vcut_iso_b.push_back(cut_iso_b);
      stringstream ss;
      ss <<cut_iso_b;
      vcut_iso_b_s.push_back(TString(ss.str()));
    }

    int ncut=0;
    //// Loop over cuts and fill loose and tight el and get fake rates for ID                                                                    
    for(unsigned int dxy_b=0; dxy_b < vcut_dxy_b.size(); dxy_b++){
      for(unsigned int dxysig_b=0; dxysig_b < vcut_dxysig_b.size(); dxysig_b++){
        for(unsigned int dz_b=0; dz_b < vcut_dz_b.size(); dz_b++){
          for(unsigned int iso_b=0; iso_b < vcut_iso_b.size(); iso_b++, ncut++){

	    std::vector<snu::KMuon> loose_mu;
	    std::vector<snu::KMuon> tight_mu;
	    bool tight1=false;
	    bool tight2=false;
	      
            for(unsigned int imu=0; imu<snu_loose.size(); imu++){
              float reliso = snu_loose[imu].RelIso04();

              if(fabs(snu_loose[imu].dZ()) > vcut_dz_b[dz_b]) continue;

              loose_mu.push_back(snu_loose[imu]);
              if(fabs(snu_loose[imu].dXYSig()) > vcut_dxysig_b[dxysig_b]) continue;
              if(snu_loose[imu].GlobalChi2()  > 10.) continue;
              if(fabs(snu_loose[imu].dXY()) > vcut_dxy_b[dxy_b]) continue;
              if(reliso > vcut_iso_b[iso_b]) continue;
	      if(imu==0) tight1=true;
	      if(imu==1) tight2=true;
              tight_mu.push_back(snu_loose[imu]);
            }
	    
	    bool cb_1(false);
	    bool cb_2(false);
	    std::vector<snu::KJet> alljets           = GetJets("JET_NOLEPTONVETO");
	    std::vector<snu::KJet> jets           = GetJets("JET_HN");

	    
	    if(loose_mu.size()==2){
	      for(unsigned int ij =0 ; ij < alljets.size() ; ij++){
		if(loose_mu.at(0).DeltaR(alljets.at(ij)) < 0.5) {
		  if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_1=true;
		}
		if(loose_mu.at(1).DeltaR(alljets.at(ij)) < 0.5) {
                  if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_1=true;
                }
	      }
	    }


	    if(!k_running_nonprompt){
	      FillHist("IDREFSNU" ,1,w, 0.,2., 2);
	      if(CheckSignalRegion(true,tight_mu,el, jets,alljets,"Low", w))FillHist(("LowIDREFSNU") ,ncut,w, 0., 500., 500);
	      if(CheckSignalRegion(true,tight_mu,el, jets,alljets,"", w))FillHist(("MediumIDREFSNU") ,ncut,w, 0., 500., 500);
	      if(CheckSignalRegion(true,tight_mu,el, jets,alljets,"High", w))FillHist(("HighIDREFSNU"),ncut ,w, 0., 500., 500);
	    }
	    else{
	      float ev_weight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, loose_mu, tight1, tight2,vcut_iso_b_s[iso_b]+"_"+vcut_dxy_b_s[dxy_b]+"_"+vcut_dxysig_b_s[dxysig_b]+"_"+vcut_dz_b_s[dz_b],cb_1,cb_2 ,"ptcorr_eta", vcut_iso_b[iso_b],false);
	      if(CheckSignalRegion(true,loose_mu,el, jets,alljets,"Low", ev_weight))FillHist(("LowIDREFSNU"),ncut ,ev_weight, 0., 500., 500);
	      if(CheckSignalRegion(true,loose_mu,el, jets,alljets,"", ev_weight))FillHist(("MediumIDREFSNU") ,ncut,ev_weight, 0., 500., 500);
	      if(CheckSignalRegion(true,loose_mu,el, jets,alljets,"High", ev_weight))FillHist(("HighIDREFSNU"),ncut ,ev_weight, 0., 500., 500);

	    }
	  }
	}
      } 
    }
  }
  if(1){
    std::vector<snu::KJet> jets           = GetJets("JET_HN");
    std::vector<snu::KJet> alljets           = GetJets("JET_NOLEPTONVETO");


    std::vector<snu::KMuon> pogmedium_loose  = GetMuons("MUON_HN_LOOSE",false);
    std::vector<snu::KElectron> el = GetElectrons("ELECTRON_HN_VETO");
    std::vector<snu::KMuon> pogmedium_tight  = GetMuons("MUON_POG_MEDIUM",false);
    std::vector<snu::KMuon> pogtight_tight  = GetMuons("MUON_POG_TIGHT",false);
    
    std::vector<snu::KMuon> gent_loose =  GetMuons("MUON_HNGENT_LOOSE",false);
    std::vector<snu::KMuon> gent_tight= GetMuons("MUON_HNGENT_TIGHT",false);
    
    cout << "gent_loose = " << gent_loose.size() << " " << " pogmedium_loose= " << pogmedium_loose.size() <<  endl;
    
    
    FillHist("POGIDREFSNU", 1,w, 0.,2., 2);

    if(!k_running_nonprompt){
      if(CheckSignalRegion(true,pogmedium_tight,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGMEDIUM") ,0,w, 0., 3., 3);
      if(CheckSignalRegion(true,pogmedium_tight,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGMEDIUM") ,0,w, 0.,3., 3);
      if(CheckSignalRegion(true,pogmedium_tight,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGMEDIUM") ,0,w, 0., 3.,3);
      if(CheckSignalRegion(true,pogtight_tight,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGTIGHT") ,1,w, 0., 3., 3);
      if(CheckSignalRegion(true,pogtight_tight,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGTIGHT") ,1,w, 0.,3., 3);
      if(CheckSignalRegion(true,pogtight_tight,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGTIGHT") ,1,w, 0., 3.,3);
      if(CheckSignalRegion(true,gent_tight,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGTIGHT") ,2,w, 0., 3., 3);
      if(CheckSignalRegion(true,gent_tight,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGTIGHT") ,2,w, 0.,3., 3);
      if(CheckSignalRegion(true,gent_tight,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGTIGHT") ,2,w, 0., 3.,3);


    }
    else{
      
      if(pogmedium_loose.size()==2){
	bool cb_1(false);
	bool cb_2(false);

	for(unsigned int ij =0 ; ij < alljets.size() ; ij++){
	  if(pogmedium_loose.at(0).DeltaR(alljets.at(ij)) < 0.5) {
	    if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_1=true;
	    }
	    if(pogmedium_loose.at(1).DeltaR(alljets.at(ij)) < 0.5) {
	      if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_2=true;
	    }
	}
	
	float ev_weight_med=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, pogmedium_loose, PassID(pogmedium_loose[0],"MUON_POG_MEDIUM"),  PassID(pogmedium_loose[1],"MUON_POG_MEDIUM"), "pogmedium", cb_1, cb_2,"ptcorr_eta",0.25,false);
	float ev_weight_tight=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, pogmedium_loose, PassID(pogmedium_loose[0],"MUON_POG_TIGHT"),  PassID(pogmedium_loose[1],"MUON_POG_TIGHT"), "pogtight",cb_1, cb_2, "ptcorr_eta",0.15,false);

	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGMEDIUM"),0 ,ev_weight_med, 0., 3., 3);
	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGMEDIUM"),0 ,ev_weight_med, 0.,3., 3);
	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGMEDIUM") ,0,ev_weight_med, 0., 3.,3);
	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGTIGHT"),1 ,ev_weight_tight, 0., 3., 3);
	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGTIGHT"),1 ,ev_weight_tight, 0.,3., 3);
	if(CheckSignalRegion(true,pogmedium_loose,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGTIGHT") ,1,ev_weight_tight, 0., 3.,3);
      }

      if(gent_loose.size()==2){

	bool cb_1(false);
        bool cb_2(false);
	std::vector<snu::KJet> alljets           = GetJets("JET_NOLEPTONVETO");

        for(unsigned int ij =0 ; ij < alljets.size() ; ij++){
          if(gent_loose.at(0).DeltaR(alljets.at(ij)) < 0.5) {
            if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_1=true;
	  }
	  if(gent_loose.at(1).DeltaR(alljets.at(ij)) < 0.5) {
	    if(alljets.at(ij).IsBTagged(snu::KJet::CSVv2, snu::KJet::Medium)) cb_2=true;
	  }
        }


	float ev_weight_gent=m_datadriven_bkg->Get_DataDrivenWeight_MM(false, gent_loose, PassID(gent_loose[0],"MUON_HNGENT_TIGHT"),  PassID(gent_loose[1],"MUON_HNGENT_TIGHT"), "gent",cb_1, cb_2, "ptcorr_eta",0.1,false);  
	if(CheckSignalRegion(true,gent_loose,el, jets,alljets,"Low", w))FillHist(("LowIDREFPOGTIGHT") ,2,ev_weight_gent, 0., 3., 3);
        if(CheckSignalRegion(true,gent_loose,el, jets,alljets,"", w))FillHist(("MediumIDREFPOGTIGHT") ,2,ev_weight_gent, 0.,3., 3);
        if(CheckSignalRegion(true,gent_loose,el, jets,alljets,"High", w))FillHist(("HighIDREFPOGTIGHT") ,2,ev_weight_gent, 0., 3.,3);

      }
    }
  }
  


  
}


void HNDiMuonOptimisation::GetTriggEfficiency(){
  //ListTriggersAvailable();                                                                                                                                                                                                                                                                                                                                                      
  vector<int> pt1;

  vector<int>pt2;


  std::vector<TString> lists_triggers;
  //lists_triggers.push_back("HLT_Ele25_eta2p1_WPTight_Gsf_v");

  std::vector<TString> lists_triggerORs;
  //lists_triggerORs.push_back("HLT_Ele15_IsoVVVL_PFHT600_v");

  for(unsigned int i=0; i < lists_triggers.size(); i++){
    FillTriggerEfficiency(lists_triggers.at(i), weight, "denominator_nojet", lists_triggers );
  }

}

void HNDiMuonOptimisation::FillTriggerEfficiency(TString cut, float weight, TString label, std::vector<TString> list){

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


bool HNDiMuonOptimisation::CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString name, float w){

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

  if(name.Contains("Low")){
    if(jj.M() > 150.) {if(debug)cout << "Fail mjj  " << endl; return false;}
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
  for(unsigned int ij=0; ij <jets.size(); ij++){
    ST+= jets[ij].Pt();
    HT+= jets[ij].Pt();

  }
  for(unsigned int ij=0; ij <loosejets.size(); ij++){
    looseST+= loosejets[ij].Pt();
  }

  if(!name.Contains("Low")){
    
    if((pow(eventbase->GetEvent().PFMET(),2.)/ looseST) > 10.) {if(debug)cout << "Fail met  " << endl; return false;}
  }
  else{
    if(eventbase->GetEvent().PFMET() > 60) return false;
  }

  if(name.Contains("Low")){
    if(HT >  200.) return false;
  }
  float dphi_1 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_1 = sqrt(2.* muons.at(0).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_1)));

  float dphi_2 = fabs(TVector2::Phi_mpi_pi(muons.at(0).Phi()- eventbase->GetEvent().METPhi(snu::KEvent::pfmet)));
  float MT_2 = sqrt(2.* muons.at(1).Et()*eventbase->GetEvent().PFMET() * (1 - cos( dphi_2)));

  if(name.Contains("Low")){
    if(MT_1 > 100.) return false;
    if(MT_2 > 80.) return false;
    if(ST > 350.)  return false;
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);
    if(lljj.M() > 300.) return false;

  }
  else{
    snu::KParticle lljj = jets.at(m) + jets.at(n) + muons.at(0) + muons.at(1);
    if(jets.size() > 3){
      snu::KParticle lljjjj = jets.at(0) + jets.at(1) + jets.at(2)+jets.at(3) + muons.at(0) + muons.at(1);
      if (lljjjj.M() > 1000.) return false;
    }
    if(ST < 200.)  return false;
    if(lljj.M() < 200.) return false;
    if(muons.at(0).Pt() < 50.) return false;
    if(muons.at(1).Pt() < 25.) return false;
    if((muons.at(0).Pt() + muons.at(1).Pt() ) < 100.) return false;

  }

  if(name.Contains("High")){
    if((muons.at(0).Pt() + muons.at(1).Pt() ) < 150.) return false;
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

bool HNDiMuonOptimisation::CheckSignalRegionNN( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KJet> jets, TString name, float w){

  if(muons.size() != 2 ) return false ;
  // Set by trigger                                                                                                                                                             
  if(muons.at(0).Pt() < 25.) return false;
  if(muons.at(1).Pt() < 15.) return false;
  if(isss&&!SameCharge(muons)) return false;

  if(!isss&&SameCharge(muons)) return false;
  if(jets.size() < 4) return false;
  snu::KParticle ee = muons.at(0) + muons.at(1);
  if(ee.M()  < 10.) return false;

  if((ee.M() > 80.) && (ee.M() < 100.) ) return false;

  int nbjet=0;
  for(unsigned int ij=0; ij <jets.size(); ij++){
    if( jets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet++;

  }
  if(nbjet > 0) return false;

  return true;

}




void HNDiMuonOptimisation::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

}


void HNDiMuonOptimisation::BeginCycle() throw( LQError ){
  
  Message("In begin Cycle", INFO);
  

  //
  //If you wish to output variables to output file use DeclareVariable
  // clear these variables in ::ClearOutputVectors function
  //DeclareVariable(obj, label, treename );
  //DeclareVariable(obj, label ); //-> will use default treename: LQTree
  //  DeclareVariable(out_electrons, "Signal_Muons", "LQTree");
  //  DeclareVariable(out_muons, "Signal_Muons");

  
  return;
  
}

HNDiMuonOptimisation::~HNDiMuonOptimisation() {
  
  Message("In HNDiMuonOptimisation Destructor" , INFO);
  
}



void HNDiMuonOptimisation::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void HNDiMuonOptimisation::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this HNDiMuonOptimisationCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void HNDiMuonOptimisation::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
  out_muons.clear();
  out_electrons.clear();
}



