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
  
/// Signal samples
  if (1) {
    
  // Create Chains
    TChain* chain50 = ChainMaker("/data/HN_data/SampleList/Signal/signal_all.txt");
    //TChain* chain50 = ChainMaker((maindir + "/scripts/filelist.txt"));
    //  TChain* chain200 = ChainMaker("/data/HN_data/SampleList/Signal/signal_mn_200_mm.txt");
    //   TChain* chain700 = ChainMaker("/data/HN_data/SampleList/Signal/signal_mn_700_mm.txt");
    
    
    Analyzer Pippo; /// create analyzer class object
    
    Pippo.Init(chain50);
    Pippo.SetName("Majorana_50",1);
    Pippo.SetWeight(1071.1, 49994);
    std::cout << "Majorana50\n";
    Pippo.Loop();
	/*
        Pippo.Init(chain100);
        Pippo.SetName("Majorana_100",1);
        Pippo.SetWeight(3.5618, 49996);
        std::cout << "Majorana100\n";  Pippo.Loop();
    
        Pippo.Init(chain200);
        Pippo.SetName("Majorana_200",1);
        Pippo.SetWeight(0.13127, 49994);
        std::cout << "Majorana200\n";
        Pippo.Loop();


        Pippo.Init(chain700);
        Pippo.SetName("Majorana_700",1);
        Pippo.SetWeight(0.00038312, 49996);
        std::cout << "Majorana700\n";  Pippo.Loop();*/
  }
        
    

////     Electro Weak samples

    
    if (0) {
        TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_zz.txt");
        Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ZZ_inclusive",11); Pippo.SetWeight(17.654, 9799908);
        std::cout << "ZZ\n";  Pippo.Loop();

        TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_wz.txt");
        Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WZ_inclusive_mio",7); Pippo.SetWeight(33.21, 10000283);
        std::cout << "WZ\n";  Pippo.Loop();

        TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_ssWpWp.txt");
        Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WpWp",77);
        Pippo.SetWeight(0.2482, 99985);
        std::cout << "WpWp\n";  Pippo.Loop();
    
        TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_ssWmWm.txt");
        Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WmWm",77);
        Pippo.SetWeight(0.08888, 96392);
        std::cout << "WmWm\n";  Pippo.Loop();
    }
    
/// QCD samples
    
  if (0) {
     TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_qcd_muon.txt");
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("QCD_mumu",31); 
     //Pippo.SetWeight(154.0, 3701947);
     std::cout << "QCD_mumu\n";  Pippo.Loop();
  }

    
///  top samples
  if (0) {
     TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_ttbar.txt");
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ttbar_del",31); 
     //Pippo.SetWeight(154.0, 3701947);
     std::cout << "ttbar\n";  Pippo.Loop();
  }


if (0) {
     TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_www.txt");
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("WWW",77);
     Pippo.SetWeight(0.08217, 220549);
     std::cout << "WWW\n";  Pippo.Loop();
  }

  if (0) {
     TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_ttw.txt");
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ttW",77); 
     Pippo.SetWeight(0.232, 196046);
     std::cout << "ttW\n";  Pippo.Loop();
  }

  if (0) {
     TChain* chain = ChainMaker("/data/HN_data/SampleList/MC/mc_ttz.txt");
     Analyzer Pippo; Pippo.Init(chain); Pippo.SetName("ttZ",77); 
     Pippo.SetWeight(0.1743, 210160);
     std::cout << "ttZ\n";  Pippo.Loop();
  }



  //////////////////////////////////////////////////////////
  //                        Data                          //
  //////////////////////////////////////////////////////////


  if (0) {
      TChain* chain = ChainMaker("/data/HN_data/SampleList/Data/data_muon_periodA.txt");
      //887.501 (pb)^-1
      Analyzer Pippo;
      Pippo.Init(chain);
      Pippo.SetName("DoubleMu_periodA",1);
      Pippo.NEvents(100000);
      Pippo.Loop();
  }

    if (0) {
        TChain* chain = ChainMaker("/data/HN_data/SampleList/Data/data_egamma_periodA.txt");
        //887.501 (pb)^-1
        Analyzer Pippo;
        Pippo.Init(chain);
        Pippo.SetName("DoubleEm_periodA",1);
        Pippo.Loop();
    }

    
}
       
