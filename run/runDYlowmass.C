{
  string maindir = getenv("MAINDIR");
  string includedir = getenv("INCLUDEDIR");
  string includedir_snu = getenv("INCLUDEDIR_snu");
  gSystem->AddIncludePath(("-I" + includedir).c_str());
  gSystem->AddIncludePath(("-I" + includedir_snu).c_str());
  gSystem->ChangeDirectory((maindir + "/src/").c_str());
  gROOT->ProcessLine(".L Reweight.cc+g");
  gROOT->ProcessLine(".L Data.cc+g");
  gROOT->ProcessLine(".L OtherFunctions.cc+g");
  

  gSystem->ChangeDirectory((maindir+ "/SNUTree/src/").c_str());  
  gROOT->ProcessLine(".L KParticle.cc+g");
  gROOT->ProcessLine(".L KJet.cc+g");
  gROOT->ProcessLine(".L KMuon.cc+g");
  gROOT->ProcessLine(".L KElectron.cc+g");



  gSystem->ChangeDirectory((maindir + "/src/").c_str());
  gROOT->ProcessLine(".L SNUTreeFiller.cc+g");

  /// Selection Code compilation
  gSystem->ChangeDirectory((maindir+ "/Selection/").c_str());
  gROOT->ProcessLine(".L SelectionFunctions.cc+g");
  gROOT->ProcessLine(".L LeptonSelection.cc+g");
  gROOT->ProcessLine(".L ElectronSelection.cc+g");
  gROOT->ProcessLine(".L MuonSelection.cc+g");
  gROOT->ProcessLine(".L MuonSelectionProbe.cc+g");
  gROOT->ProcessLine(".L JetSelection.cc+g");
  gROOT->ProcessLine(".L GenSelection.cc+g");

  gSystem->ChangeDirectory((maindir +("/Plotting/")).c_str());
  /// Plotting code compilation
  gROOT->ProcessLine(".L StdPlots.cc+g");
  gROOT->ProcessLine(".L ElectronPlots.cc+g");
  gROOT->ProcessLine(".L MuonPlots.cc+g");
  gROOT->ProcessLine(".L JetPlots.cc+g");
  gROOT->ProcessLine(".L SignalPlots.cc+g");

  
  gSystem->ChangeDirectory((maindir + "/src/").c_str());
  gROOT->ProcessLine(".L Analyzer.cc+g");
  gROOT->ProcessLine(".L Analyzer_Ele.cc+g");
  gROOT->ProcessLine(".L FakeRateCalculator.cc+g");
  gROOT->ProcessLine(".L FakeRateCalculator_Ele.cc+g");
  gROOT->ProcessLine(".L EfficiencyCalculator.cc+g");
  gROOT->ProcessLine(".L ChainMaker.C+g");


  //////////////////////////////////////////////////////////
  //                          MC                          //
  //////////////////////////////////////////////////////////
  

  // example
  /*
    if(0/1){
                                                                                    
    TChain* chain = ChainMaker( "path/to/txtfile/with/input/paths");/
    Analyzer Pippo; /// create analyzer class object                            
    Pippo.Init(chain);                                                          
    Pippo.SetName("outputname",version);                                                
    Pippo.SetTargetLumi(TargetLuminosity);  == lumi of data
    Pippo.SetWeight(xesc, nevents); // Effective Lumi , nevents               
    or
    Pippo.SetEffectiveLumi(effLumi); effLumi = num/xsec
    // get these numbers from https://docs.google.com/spreadsheet/ccc?key=0Aq8wOqg_Kam2dE5GOWVMcVFfTGdDZVg1cDFVUzNWY3c&usp=sharing#gid=3
    Pippo.TestLoop();    
    
    }
  */
  
  /// Signal samples
  if (1) {
    TChain* chain = ChainMaker( "/data/HN_data/SampleList/MC/mc_DY10to50.txt");
    Analyzer Pippo; /// create analyzer class object    
    Pippo.Init(chain);
    Pippo.SetName("DYLowMass",1);
    Pippo.SetTargetLumi(887.5);
    Pippo.SetEffectiveLumi(3424.0);
    Pippo.NEents(1000000);
    Pippo.TestLoop();
  }
}
       
