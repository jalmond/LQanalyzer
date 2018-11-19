// $Id: ExampleAnalyzer.cc 1 2013-11-26 10:23:10Z jalmond $
/***************************************************************************
 * @Project: LQGetSignalEff Frame - ROOT-based analysis framework for Korea SNU
 * @Package: LQCycles
 *
 * @author John Almond       <jalmond@cern.ch>           - SNU
 *d
 ***************************************************************************/

/// Local includes
#include "GetSignalEff.h"

//Core includes
#include "EventBase.h"                                                                                                                           
#include "BaseSelection.h"

//// Needed to allow inheritance for use in LQCore/core classes
ClassImp (GetSignalEff);


/**
 *   This is an Example Cycle. It inherits from AnalyzerCore. The code contains all the base class functions to run the analysis.
 *
 */
GetSignalEff::GetSignalEff() :  AnalyzerCore() {


  // To have the correct name in the log:                                                                                                                            
  SetLogName("GetSignalEff");

  Message("In GetSignalEff constructor", INFO);
  //
  // This function sets up Root files and histograms Needed in ExecuteEvents
  InitialiseAnalysis();

}


void GetSignalEff::InitialiseAnalysis() throw( LQError ) {
  
  /// Initialise histograms
  MakeHistograms();  
  //
  // You can out put messages simply with Message function. Message( "comment", output_level)   output_level can be VERBOSE/INFO/DEBUG/WARNING 
  // You can also use m_logger << level << "comment" << int/double  << LQLogger::endmsg;
  //

   Message("Making clever hists for Z ->ll test code", INFO);

   //// Initialise Plotting class functions
   /// MakeCleverHistograms ( type, "label")  type can be muhist/elhist/jethist/sighist

   FillHist("Truth_Jets_FromW_LowMass_Pt", -1., 1., 0., 1000., 250, "Truth j_{W} lowmass P_{T} GeV");
   FillHist("Truth_Jets_FromW_LowMass_Eta",-1.,  1., -5., 5., 100,"Truth j_{W} lowmass #eta");
   FillHist("Truth_FowardJets_Pt",  -1.,  1., 0., 500., 250,"Truth j_{forward} P_{T} GeV");
   FillHist("Truth_FowardJets_Eta",  -1., 1., -5., 5., 50,"Truth j_{forward}  #eta");
   FillHist("Truth_Lepton_FromW_HighMass_Pt", -1., 1., 0., 500., 250,"Truth #ell_{W} high mass P_{T}");
   FillHist("Truth_Lepton_FromW_HighMass_Pt_lowpt", -1., 1., 0., 100., 100, "Truth #ell_{W} high mass P_{T}");
   FillHist("Truth_Lepton_FromW_HighMass_Eta", -1., 1., -3., 3., 60,"Truth #ell_{W} high mass #eta");
   FillHist("Truth_RecoMatched_FowardJets_Pt",  -1., 1., 0., 500., 250,"Truth (reco matched) j_{forward} P_{T} GeV");
   FillHist("Truth_RecoMatched_FowardJets_Eta", -1., 1., -5., 5., 50,"Truth (reco matched) j_{forward} #eta");


   return;
}


void GetSignalEff::ExecuteEvents()throw( LQError ){
  

  std::vector<snu::KJet> ALLjets =  GetJets("JET_NOCUT",0., 5.);
  std::vector<snu::KJet> HNjets10 =  GetJets("JET_HN",10., 2.5);
  std::vector<snu::KJet> HNjets20 =  GetJets("JET_HN",20., 2.5);
  
  std::vector<snu::KMuon> muons_all = GetMuons("MUON_PTETA", false, 0., 5.);
  std::vector<snu::KMuon> muons = GetMuons("MUON_HN_TIGHT", false, 10., 2.5);
  std::vector<snu::KElectron> electrons_all = GetElectrons(false,false, "ELECTRON_NOCUT",0., 5.);
  std::vector<snu::KElectron> electrons = GetElectrons(false,false, "ELECTRON_HN_TIGHT",15., 2.5);

  std::vector<snu::KFatJet> fatjetcoll = GetFatJets("FATJET_HN");

  
  FillHist("Reco_nmuon_nocut", muons_all.size(), weight, 0., 5., 5,"N_{#mu}");
  FillHist("Reco_nmuon_tight", muons.size(), weight, 0., 5., 5,"N_{#mu} (TIGHT)");
  FillHist("Reco_nelectron_nocut", muons_all.size(), weight, 0., 5., 5,"N_{#mu}");
  FillHist("Reco_nelectron_tight", muons.size(), weight, 0., 5., 5,"N_{#mu} (TIGHT)");

  FillHist("Reco_njets", ALLjets.size(), weight, 0., 10., 10,"N_{j}");
  FillHist("Reco_njets_10", HNjets10.size(), weight, 0., 10., 10,"N_{j} (pt> 10 GeV)");
  FillHist("Reco_njets_20", HNjets20.size(), weight, 0., 10., 10,"N_{j} (pt> 20 GeV)");
  
  FillHist("Reco_nfatjet", fatjetcoll.size(), weight, 0., 10., 10,"N_{fat_j}");

  int nfowardj(0);
  for(unsigned int ij2=0; ij2 <ALLjets.size(); ij2++){
    if(fabs(ALLjets[ij2].Eta()) > 2.5) nfowardj++;
  }
  FillHist("Reco_nfowardjet", nfowardj, weight, 0., 10., 10,"N_{foward_j}");
  // RECO PLOTS
  float ST=0.;
  for(int ij = 0 ; ij < muons_all.size() ; ij++){
    ST+= muons_all[ij].Pt();
    if(ij==0) FillHist(("Reco_muon_1_pt") , muons_all[ij].Pt(),weight, 0., 1000., 100,"#mu_{1} P_{t} GeV");
    if(ij==0) FillHist(("Reco_muon_1_eta") , muons_all[ij].Eta(),weight, -5., 5., 100,"#mu_{1} #eta");
    if(ij==1) FillHist(("Reco_muon_2_pt") , muons_all[ij].Pt(),weight, 0., 1000., 100,"#mu_{2} P_{t} GeV");
    if(ij==1) FillHist(("Reco_muon_2_eta"),  muons_all[ij].Eta(),weight, -5., 5., 100,"#mu_{2} #eta");
  }
  if( muons_all.size()==2) {
    FillHist(("Reco_mm_dR") , muons_all[0].DeltaR(muons_all[1]),weight, 0., 10., 100,"#DeltaR(#mu#mu)");
  }
  if( electrons_all.size()==2) {
    FillHist(("Reco_ee_dR") , electrons_all[0].DeltaR(electrons_all[1]),weight, 0., 10., 100,"#DeltaR(ee)");
  }
  
  float MuJmindR=9999.;
  for(unsigned int im=0; im <muons.size(); im++){
    for(unsigned int ij2=0; ij2 <HNjets20.size(); ij2++){
      if(muons.at(im).DeltaR(HNjets20.at(ij2)) <  MuJmindR){
	MuJmindR = muons.at(im).DeltaR(HNjets20.at(ij2));
      }
    }
  }
  FillHist(("Reco_muJ_dR") , MuJmindR, weight, 0., 10., 100,"#DeltaR(#muJ)");

  float EJmindR=9999.;
  for(unsigned int im=0; im <electrons.size(); im++){
    for(unsigned int ij2=0; ij2 <HNjets20.size(); ij2++){
      if(electrons.at(im).DeltaR(HNjets20.at(ij2)) <  EJmindR){
        EJmindR = electrons.at(im).DeltaR(HNjets20.at(ij2));
      }
    }
  }
  FillHist(("Reco_eJ_dR") , EJmindR, weight, 0., 10., 100,"#DeltaR(eJ)");

  for(int ij = 0 ; ij < electrons_all.size() ; ij++){
    ST+= electrons_all[ij].Pt();
    if(ij==0) FillHist(("Reco_electron_1_pt") ,  electrons_all[ij].Pt(),weight, 0., 1000., 100,"e_{1} P_{t} GeV");
    if(ij==0) FillHist(("Reco_electron_1_eta") , electrons_all[ij].Eta(), weight, -5., 5., 100,"e_{1} #eta");
    if(ij==1) FillHist(("Reco_electron_2_pt") ,  electrons_all[ij].Pt(),weight, 0., 1000., 100,"e_{2} P_{t} GeV");
    if(ij==1) FillHist(("Reco_electron_2_eta"),   electrons_all[ij].Eta(),weight, -5., 5., 100,"e_{2} #eta");
  }
  

  for(int ij = 0 ; ij < HNjets20.size() ; ij++){
    ST+= HNjets20[ij].Pt();
  }
  FillHist(("Reco_met") ,  eventbase->GetEvent().PFMET(),  weight, 0., 500., 100,"slash{E}_{T}^{miss} (GeV)");
  FillHist(("Reco_met2_st"), pow(eventbase->GetEvent().PFMET(),2.)/ ST,  weight, 0., 20., 100,"slash{E}^{2}_{T}^{miss}/S_{T}");

  for(int ij = 0 ; ij < ALLjets.size() ; ij++){
    
    if(ij==0){
      FillHist(("Reco_jet_1_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet1_pt");
      FillHist(("Reco_jet_1_eta"),  ALLjets[ij].Eta(), weight, -5., 5., 100,"Jet1_eta");
    }
    if(ij==1){
      FillHist(("Reco_jet_2_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet2_pt");
      FillHist(("Reco_jet_2_eta"),  ALLjets[ij].Eta(), weight, -5., 5., 100,"Jet2_eta");
    }
    if(ij==2){
      FillHist(("Reco_jet_3_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet3_pt");
      FillHist(("Reco_jet_3_eta"),  ALLjets[ij].Eta(), weight, -5., 5., 100,"Jet3_eta");
    }
    if(ij==3){
      FillHist(("Reco_jet_4_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet4_pt");
      FillHist(("Reco_jet_4_eta"),  ALLjets[ij].Eta(), weight, -5., 5., 100,"Jet4_eta");
    }
    if(fabs(ALLjets[ij].Eta()) < 2.5)       FillHist(("Reco_centraljet_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet(#eta < 2.5) pt");
    else FillHist(("Reco_fowardjet_pt"),  ALLjets[ij].Pt(), weight, 0., 400., 100,"Jet(#eta > 2.5) pt");
  }

  vector<int> i_jets;
  //TruthPrintOut();            
  std::vector<snu::KTruth> truthColl= eventbase->GetTruth();                                                                                                                                                                                                                    
  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {
      
      int mother_i = eventbase->GetTruth().at(i).IndexMother();
      
      while(fabs(eventbase->GetTruth().at(mother_i).PdgId()) ==24){
	mother_i = eventbase->GetTruth().at(mother_i).IndexMother();
      }
      if(fabs(eventbase->GetTruth().at(mother_i).PdgId()) == 9900012){
	FillHist("Truth_Jets_FromW_HighMass_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1000., 250,"Truth j_{W} highmass P_{T} GeV");
	FillHist("Truth_Jets_FromW_HighMass_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100, "Truth j_{W} highmass  #eta");
	
	

	snu::KParticle jtmp=eventbase->GetTruth().at(i);
        for(int ij = 0 ; ij < ALLjets.size() ; ij++){
          if(jtmp.DeltaR(ALLjets[ij]) < 0.1){
            FillHist("TruthvsReco_Jets_FromW_PtR_ptT", eventbase->GetTruth().at(i).Pt(), ALLjets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 10., 100);
	    FillHist("TruthvsReco_Jets_FromW_ratioPtR_ptT", eventbase->GetTruth().at(i).Pt(), ALLjets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 10., 100);

          }
        }

	i_jets.push_back(i);
      }
      if(fabs(eventbase->GetTruth().at(i).PdgId()) == 9900012){
	FillHist("Truth_Jets_FromW_LowMass_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 1000., 250, "Truth j_{W} lowmass P_{T} GeV");
        FillHist("Truth_Jets_FromW_LowMass_Eta", eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 100,"Truth j_{W} lowmass #eta");

	
	snu::KParticle jtmp=eventbase->GetTruth().at(i);
        for(int ij = 0 ; ij < ALLjets.size() ; ij++){
          if(jtmp.DeltaR(ALLjets[ij]) < 0.1){
            FillHist("TruthvsReco_Jets_FromW_ratioPtR_ptT", eventbase->GetTruth().at(i).Pt(), ALLjets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 10., 100);
	    FillHist("TruthvsReco_Jets_FromW_PtR_ptT", eventbase->GetTruth().at(i).Pt(), ALLjets[ij].Pt(), 1., 0., 200., 100, 0., 200., 100);
          }
        }

        i_jets.push_back(i);

      }
    }
  }

  for(unsigned int i = 0; i < truthColl.size(); i++){
    if(fabs(eventbase->GetTruth().at(i).PdgId()) < 6) {

      int mother_i = eventbase->GetTruth().at(i).IndexMother();
      
      bool Wjet=false;
      for(unsigned int ijet=0; ijet < i_jets.size(); ijet++){
	if(i_jets[ijet] ==  i) Wjet=true;
      }
      if(Wjet) continue;

      if(eventbase->GetTruth().at(i).GenStatus() == 23) {
	
	FillHist("Truth_FowardJets_Pt",  eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth j_{forward} P_{T} GeV");
	FillHist("Truth_FowardJets_Eta",  eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 50,"Truth j_{forward}  #eta");

	snu::KParticle jtmp=eventbase->GetTruth().at(i);
	for(int ij = 0 ; ij < ALLjets.size() ; ij++){
	  if(jtmp.DeltaR(ALLjets[ij]) < 0.1){

	    FillHist("Truth_RecoMatched_FowardJets_Pt",  eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth (reco matched) j_{forward} P_{T} GeV");
	    FillHist("Truth_RecoMatched_FowardJets_Eta",  eventbase->GetTruth().at(i).Eta(), 1., -5., 5., 50,"Truth (reco matched) j_{forward} #eta");
	    
	    FillHist("TruthResponnse_RecoMatched_FowardJets_Pt",   eventbase->GetTruth().at(i).Pt(), ALLjets[ij].Pt() / eventbase->GetTruth().at(i).Pt(), 1., 0., 200., 100, 0., 200., 400);
	  }
	  
	  //    cout << "non W jet " <<  fabs(eventbase->GetTruth().at(i).PdgId()) << " mother: " << eventbase->GetTruth().at(mother_i).PdgId() <<  " " << eventbase->GetTruth().at(i).Pt() << " " << eventbase->GetTruth().at(i).Eta() << " " <<  eventbase->GetTruth().at(i).Phi() << endl;
	  //	    cout << "Jet matched to non W q: " << ALLjets[ij].Pt() << " " << ALLjets[ij].Eta() << " " << ALLjets[ij].Phi() << endl;
	}
      }
    }
  }
  // i_jets = truth indices of quarks in W->qq'
      
  if(!isData){
    
    for(unsigned int i = 0; i < truthColl.size(); i++){
      if(fabs(eventbase->GetTruth().at(i).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i).PdgId()) == 13 ) {
	
	if(eventbase->GetTruth().at(i).GenStatus() ==23){
	  if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) != 9900012){
	    FillHist("Truth_Lepton_FromW_HighMass_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth #ell_{W} high mass P_{T}");
	    FillHist("Truth_Lepton_FromW_HighMass_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth #ell_{W} high mass P_{T}");
	    FillHist("Truth_Lepton_FromW_HighMass_Eta", eventbase->GetTruth().at(i).Eta(), 1., -3., 3., 60,"Truth #ell_{W} high mass #eta");
	    
	    int i_N(0);
	    for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	      if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 9900012 ) {i_N=i2; break;}
	    }
	    int i_l2(0);
            for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	      if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i2).PdgId()) == 13 ) {
		if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i2).IndexMother()).PdgId()) == 9900012 ) {i_l2=i2; break;}
	      }
	    }

	    float dRl1N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_N).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_N).Phi()),2.));
	    FillHist("Truth_Lepton_FromW_dRN", dRl1N,   1., 0., 5., 25, "Truth #Delta R(#ell_{W},N)");

	    float dRl1l2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_l2).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_l2).Phi()),2.));
															       
            FillHist("Truth_Lepton_FromW_dR_lep2", dRl1l2, 1., 0., 5., 25,"Truth #Delta R(#ell_{W},#ell_{N})");
	    
	  }	  
	}
	
	if(eventbase->GetTruth().at(i).GenStatus() ==1){
	  if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) ==24) {
	    FillHist("Truth_Lepton_FromW_LowMass_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth #ell_{W} P_{T}");
	    FillHist("Truth_Lepton_FromW_LowMass_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100, "Truth #ell_{W} P_{T}");
	    FillHist("Truth_Lepton_FromW_LowMass_Eta", eventbase->GetTruth().at(i).Eta(), 1., -3., 3., 60,"Truth #ell_{W} #eta");
	    int i_N(0);
            for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
              if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 9900012 ) {i_N=i2; break;}
            }
            int i_l2(0);
            for(unsigned int i2 = 0; i2 < truthColl.size(); i2++){
	      if(fabs(eventbase->GetTruth().at(i2).PdgId()) == 11 || fabs(eventbase->GetTruth().at(i2).PdgId()) == 13 ) {
                if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i2).IndexMother()).PdgId()) == 9900012 ) {i_l2=i2; break;}
              }
            }

            float dRl1N = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_N).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_N).Phi()),2.));
															      
            FillHist("Truth_Lepton_FromW_dRN", dRl1N, 1., 0., 5., 25, "Truth #Delta R(#ell_{W},N)");

            float dRl1l2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_l2).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_l2).Phi()),2.));
																 

            FillHist("Truth_Lepton_FromW_dR_lep2", dRl1l2, 1., 0., 5., 25, "Truth #Delta R(#ell_{W},#ell_{2})");

	  }
	  
	  if(fabs(eventbase->GetTruth().at(eventbase->GetTruth().at(i).IndexMother()).PdgId()) == 9900012){
	    FillHist("Truth_Lepton_FromN_Pt", eventbase->GetTruth().at(i).Pt(), 1., 0., 500., 250,"Truth #ell_{N} P_{T} (GeV) ");
	    FillHist("Truth_Lepton_FromN_Pt_lowpt", eventbase->GetTruth().at(i).Pt(), 1., 0., 100., 100,"Truth #ell_{N} P_{T} (GeV) ");
	    FillHist("Truth_Lepton_FromN_Eta", eventbase->GetTruth().at(i).Eta(), 1., -3., 3., 60,"Truth #ell_{N} #eta ");
	    
	    
	    float dRl2j1 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_jets[0]).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_jets[0]).Phi()),2.));
	    float dRl2j2 = sqrt (pow(fabs(eventbase->GetTruth().at(i).Eta() - eventbase->GetTruth().at(i_jets[1]).Eta()),2.) + pow( fabs(eventbase->GetTruth().at(i).Phi() - eventbase->GetTruth().at(i_jets[1]).Phi()),2.));
	    

	    if(dRl2j1 < dRl2j2) FillHist("Truth_Lepton_FromN_dR_closest_q", dRl2j1, 1., 0., 5., 25,"Truth #DeltaR(#ell_{N},q) ");
	    if(dRl2j1 > dRl2j2) FillHist("Truth_Lepton_FromN_dR_closest_q", dRl2j2, 1., 0., 5., 25,"Truth #DeltaR(#ell_{N},q) ");

	    
	  }
	}
	
      } // lepton loop
    }
    
    
    if(i_jets.size() ==2){
      snu::KParticle W = eventbase->GetTruth().at(i_jets[0])+  eventbase->GetTruth().at(i_jets[1]);
      FillHist("Truth_mjj", W.M(),  1., 0., 125., 250,"Truth M_{jj} GeV");
      //FillHist("Truth_mjjll", W.M(),  1., 0., 125., 250);
      std::vector<snu::KJet> jets = GetJets("JET_HN");
      std::vector<snu::KJet> HNjets10 =  GetJets("JET_HN",10., 2.5);
      std::vector<snu::KJet> HNjets10e27 =  GetJets("JET_HN",10., 2.7);
      std::vector<snu::KJet> HNjets20e27 =  GetJets("JET_HN",20., 2.7);

      std::vector<snu::KMuon> muons = GetMuons("MUON_HN_TIGHT");
      
      MatchedJets(jets, muons, electrons, i_jets, "");
      MatchedJets(HNjets10, muons, electrons,  i_jets,"pt10");
      MatchedJets(HNjets20e27, muons, electrons,i_jets, "pt20e27");
      MatchedJets(HNjets10e27, muons, electrons, i_jets,"pt10e27");
    }
  }


  vector<TString> muonIDs;
  muonIDs.push_back("MUON_HN_EFF_PT");
  muonIDs.push_back("MUON_HN_EFF_POG");
  muonIDs.push_back("MUON_HN_EFF_DXY");
  muonIDs.push_back("MUON_HN_EFF_DZ");
  muonIDs.push_back("MUON_HN_EFF_dxysig");
  muonIDs.push_back("MUON_HN_EFF_iso");
  muonIDs.push_back("MUON_HN_TIGHT");

  
  if(!isData)weight*= MCweight;
  weight*=WeightByTrigger("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", TargetLumi);

  FillEventCutFlow(0, "NoCut", weight);


  std::vector<snu::KFatJet> fatjets = GetFatJets("FATJET_HN");
  std::vector<snu::KJet> jets = GetJets("JET_HN");
  std::vector<snu::KJet> hnjets = GetJetsWFT("JET_HN","FATJET_HN");

  FillHist("2DJets", fatjets.size(), jets.size(),  weight, 0., 10., 10,  0., 10., 10);
  for(unsigned int ifjet=0; ifjet < fatjets.size(); ifjet++){
    FillHist(("tau21"), fatjets[ifjet].Tau2()/fatjets[ifjet].Tau1(), weight, 0., 1., 100,"tau21");
    FillHist(("PrunedMass"), fatjets[ifjet].PrunedMass(),  weight, 0., 200., 100,"M_{pruned} GeV");
    FillHist(("SoftDropMass"), fatjets[ifjet].SoftDropMass(),  weight, 0., 200., 100,"Soft Mass");
  }


  if(muons.size() !=2) return;
  bool passtrig(false);
  if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v"))   {
    if(muons[0].Pt() > 20 && muons[1].Pt() > 10){
      FillEventCutFlow(0, "HLT_Mu17_",weight);
      passtrig=true;
    }
    TString analysis_trigger_muon="HLT_IsoMu24_v";
    TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
    if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
      if(muons[0].Pt() > 25 && muons[1].Pt() > 5) {
	FillEventCutFlow(0, "HLT_IsoMu24",weight);
	passtrig=true;
      }
    }
  }
  else {
    TString analysis_trigger_muon="HLT_IsoMu24_v";
    TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
    if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
      if(muons[0].Pt() > 25 && muons[1].Pt() > 5) {
	FillEventCutFlow(0, "HLT_IsoMu24",weight);
	passtrig=true;
      }
    }
    else return;
  }
  if(!passtrig) return;

  std::vector<snu::KJet> alljets =  GetJets("JET_NOLEPTONVETO");

 
  std::vector<snu::KMuon> muons_veto = GetMuons("MUON_HN_VETO",false);
  std::vector<snu::KElectron> electrons_veto = GetElectrons(true,true,"ELECTRON_HN_VETO");

  if(muons_veto.size() == 2 && electrons_veto.size()==0){
    for(unsigned int iid=0; iid < muonIDs.size(); iid++){

      TString muid = muonIDs[iid];
      std::vector<snu::KMuon> muons_eff=GetMuons(muid);

      if(SameCharge(muons_eff)){

	
	if(PassTrigger("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v")) {
	  if(muons_eff[0].Pt() < 20 || muons_eff[1].Pt() < 10) continue;
	}
	else{
	  TString analysis_trigger_muon="HLT_IsoMu24_v";
	  TString analysis_trigger_tkmuon="HLT_IsoTkMu24_v";
	  if((PassTrigger(analysis_trigger_muon) || PassTrigger(analysis_trigger_tkmuon))){
	    if(muons_eff[0].Pt() < 25 || muons_eff[1].Pt() < 5) continue;
          }
	  
	}
	FillEventCutFlow(0, muid, weight);
        
	if(muonIDs[iid] == "MUON_HN_TIGHT"){
	  
	  if(jets.size() > 1) FillEventCutFlow(0, "DiJet", weight);
	  if((jets.size() > 1)|| (fatjets.size() > 0) )  FillEventCutFlow(0, "NewDiJet", weight);
	  
          if(CheckSignalRegion(true,muons_eff, electrons_veto,jets, alljets,"Low", weight)) FillEventCutFlow(0, "LowMass", weight);
          if(CheckSignalRegion(true,muons_eff,electrons_veto, jets, alljets,"", weight)) FillEventCutFlow(0, "MidMass", weight);
          if(CheckSignalRegion(true,muons_eff,electrons_veto, jets, alljets,"High", weight)) FillEventCutFlow(0, "HighMass", weight);
	}
	
      }
    }
    
  }
  
  

  return;
}// End of execute event loop
  



void GetSignalEff::MatchedJets(std::vector<snu::KJet> jets, std::vector<snu::KMuon> muons, std::vector<snu::KElectron> electrons, vector<int> i_jets, TString label){

  if(jets.size()>=2 && (electrons.size() == 2 || muons.size()==2)){
    
    float dijetmass_tmp=999.;
    float dijetmass_tmpHigh=999.;
    float dijetmass=9990000.;
    float dijetmasshigh=9990000.;
    int m=-999;
    int n=-999;
    int mH=-999;
    int nH=-999;
    for(UInt_t emme=0; emme<jets.size(); emme++){
      for(UInt_t enne=1; enne<jets.size(); enne++) {
	if(emme == enne) continue;
	if(muons.size() ==2)dijetmass_tmp = (jets[emme]+jets[enne] + muons[0] + muons[1]).M();
	if(electrons.size() ==2)dijetmass_tmp = (jets[emme]+jets[enne] + electrons[0] + electrons[1]).M();
	if ( fabs(dijetmass_tmp-80.4) < fabs(dijetmass-80.4) ) {

	  dijetmass = dijetmass_tmp;
	  m = emme;
	  n = enne;
	}
      }
    }
    for(UInt_t emme=0; emme<jets.size(); emme++){
      for(UInt_t enne=1; enne<jets.size(); enne++) {
	if(emme == enne) continue;
	dijetmass_tmpHigh = (jets[emme]+jets[enne]).M();
	if ( fabs(dijetmass_tmpHigh-80.4) < fabs(dijetmasshigh-80.4) ) {

	  dijetmasshigh = dijetmass_tmpHigh;
	  mH = emme;
	  nH = enne;
	}
      }
    }


    bool match=false;
    snu::KParticle j1= eventbase->GetTruth().at(i_jets[0]);
    snu::KParticle j2= eventbase->GetTruth().at(i_jets[1]);
    if(jets[m].DeltaR(j1) < 0.5){
      if(jets[n].DeltaR(j2) < 0.5){
	match=true;
      }
    }
    if(jets[m].DeltaR(j2) < 0.5){
      if(jets[n].DeltaR(j1) < 0.5){
	match=true;

      }
    }
    bool matchH=false;
    if(jets[mH].DeltaR(j1) < 0.5){
      if(jets[nH].DeltaR(j2) < 0.5){
	matchH=true;
      }
    }
    if(jets[mH].DeltaR(j2) < 0.5){
      if(jets[nH].DeltaR(j1) < 0.5){
	matchH=true;

      }
    }


    FillHist("Reco_mjj_Low"+label, (jets[m]+jets[n]).M(),  1., 0., 125., 250, "Reco M_{jj} low mass");
    FillHist("Reco_mjj_High"+label, (jets[mH]+jets[nH]).M(),  1., 0., 125., 250,"Reco M_{jj} high mass");
    if(match)  FillHist("Matched_JJ_truth_lowmass"+label, 1, 1., 0., 2., 2,"Is W*->qq reco/truth matched");
    else  FillHist("Matched_JJ_truth_lowmass"+label,0, 1., 0., 2., 2,"Is W*->qq reco/truth matched");

    if(matchH)  FillHist("Matched_JJ_truth_highmass"+label, 1, 1., 0., 2., 2,"Is W->qq reco/truth matched");
    else  FillHist("Matched_JJ_truth_highmass"+label,0, 1., 0., 2., 2,"Is W->qq reco/truth matched");



  }

}

void GetSignalEff::EndCycle()throw( LQError ){
  
  Message("In EndCycle" , INFO);
  m_logger << DEBUG << "END OF CYCLE: isdata=" << isData <<  LQLogger::endmsg;

}


void GetSignalEff::BeginCycle() throw( LQError ){
  
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




bool GetSignalEff::CheckSignalRegion( bool isss,  std::vector<snu::KMuon> muons, std::vector<snu::KElectron> el,  std::vector<snu::KJet> jets,  std::vector<snu::KJet> alljets, TString name, float w){
				    
  
  bool debug=false;


  if(el.size() > 0) return false ;
  if(muons.size() != 2 ) {if(debug)cout << "Fail el size" << endl; return false ;}
                                                                                                                                                                                 
  if(muons.at(0).Pt() < 20.) {if(debug)cout << "Fail pt1 " << endl; return false;}
  if(muons.at(1).Pt() < 5.)  {if(debug)cout << "Fail pt2  " << endl; return false;}

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
    if((jets[0]+jets[1]).M() > 200.) return false;
    if((jets[0] + muons[0] + muons[1]).M() > 250.)  return false;
  }
  else{
    if(jj.M() > 120.) {if(debug)cout << "Fail mjj  " << endl; return false;}
    if(jj.M() < 50.) {if(debug)cout << "Fail mjj  " << endl; return false;}

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
  }


  int nbjet=0;
  for(unsigned int ij=0; ij <alljets.size(); ij++){
    if( alljets[ij].IsBTagged(  snu::KJet::CSVv2, snu::KJet::Medium))  nbjet++;
  }
  if(nbjet > 0) {if(debug)cout << "Fail nbjet  " << endl; return false;}


  if(debug)cout << "PASSES ID" << endl;
  return true;
}


GetSignalEff::~GetSignalEff() {
  
  Message("In GetSignalEff Destructor" , INFO);
  
}


void GetSignalEff::FillEventCutFlow(int cf,TString cut,  float weight){

  if(cf==0){
    if(GetHist( "mm_eventcutflow_DoubleMuon")) {
      GetHist( "mm_eventcutflow_DoubleMuon")->Fill(cut,weight);

    }
    else{

      vector<TString> muonIDs;
      muonIDs.push_back("NoCut");
      muonIDs.push_back("HLT_Mu17_");      muonIDs.push_back("HLT_IsoMu24");
      muonIDs.push_back("MUON_HN_EFF_PT");
      muonIDs.push_back("MUON_HN_EFF_POG");
      muonIDs.push_back("MUON_HN_EFF_DXY");
      muonIDs.push_back("MUON_HN_EFF_DZ");
      muonIDs.push_back("MUON_HN_EFF_dxysig");
      muonIDs.push_back("MUON_HN_EFF_iso");
      muonIDs.push_back("MUON_HN_TIGHT");

      muonIDs.push_back("DiJet");
      muonIDs.push_back("NewDiJet");
      muonIDs.push_back("LowMass");
      muonIDs.push_back("MidMass");
      muonIDs.push_back("HighMass");
      AnalyzerCore::MakeHistograms( "mm_eventcutflow_DoubleMuon",muonIDs.size(),0.,float(muonIDs.size()));

      for(unsigned int iid=0; iid < muonIDs.size(); iid++){

        TString elid = muonIDs[iid];
        GetHist( "mm_eventcutflow_DoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
      }
      GetHist( "mm_eventcutflow_DoubleMuon")->Fill(cut,weight);
      
    }
  }
  
  if(cf==2){
    if(GetHist( "mm_eventcutflow_LowMass_DoubleMuon")) {
      GetHist( "mm_eventcutflow_LowMass_DoubleMuon")->Fill(cut,weight);
    }
  else{

    vector<TString> IDs;
    IDs.push_back("LowMass_POGMEDIUM");
    IDs.push_back("LowMass_POGTIGHT");
    IDs.push_back("LowMass_GENT");
    IDs.push_back("LowMass_HN");
    IDs.push_back("LowMass_HN_MEDIUM");
    IDs.push_back("LowMass_HN_ISO");
    IDs.push_back("LowMass_HN_DXY");



    AnalyzerCore::MakeHistograms( "mm_eventcutflow_LowMass_DoubleMuon",IDs.size(),0.,float(IDs.size()));

    for(unsigned int iid=0; iid < IDs.size(); iid++){

      TString elid = IDs[iid];
      GetHist( "mm_eventcutflow_LowMass_DoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
    }
    GetHist( "mm_eventcutflow_LowMass_DoubleMuon")->Fill(cut,weight);

  }
 }

if(cf==4){
  if(GetHist( "mm_eventcutflow_HighMass_DoubleMuon")) {
    GetHist( "mm_eventcutflow_HighMass_DoubleMuon")->Fill(cut,weight);

  }
  else{

    vector<TString> IDs;
    IDs.push_back("HighMass_POGMEDIUM");
    IDs.push_back("HighMass_POGTIGHT");
    IDs.push_back("HighMass_GENT");
    IDs.push_back("HighMass_HN");
    IDs.push_back("HighMass_HN_MEDIUM");
    IDs.push_back("HighMass_HN_ISO");
    IDs.push_back("HighMass_HN_DXY");


    AnalyzerCore::MakeHistograms( "mm_eventcutflow_HighMass_DoubleMuon",IDs.size(),0.,float(IDs.size()));

    for(unsigned int iid=0; iid < IDs.size(); iid++){

      TString elid = IDs[iid];
      GetHist( "mm_eventcutflow_HighMass_DoubleMuon")->GetXaxis()->SetBinLabel(1+iid,elid);
    }
    GetHist( "mm_eventcutflow_HighMass_DoubleMuon")->Fill(cut,weight);

  }
 }

}





void GetSignalEff::BeginEvent( )throw( LQError ){

  Message("In BeginEvent() " , DEBUG);

  return;
}


///############### THESE ARE FUNCTIONS SPECIFIC TO THIS CYCLE

void GetSignalEff::MakeHistograms(){
  //// Additional plots to make
    
  maphist.clear();
  AnalyzerCore::MakeHistograms();
  Message("Made histograms", INFO);
  /**
   *  Remove//Overide this GetSignalEffCore::MakeHistograms() to make new hists for your analysis
   **/
  
}


void GetSignalEff::ClearOutputVectors() throw(LQError) {

  // This function is called before every execute event (NO need to call this yourself.
  
  // Add any new output vector you create to this list. 
  // if you do not the vector will keep keep getting larger when it is filled in ExecuteEvents and will use excessive amoun of memory
  //
  // Reset all variables declared in Declare Variable
  //
}



