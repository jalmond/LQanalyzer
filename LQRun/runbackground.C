//void runbackground(string inputfile, double targetlumi, double nevents){
{
  string maindir = getenv("LQANALYZER_DIR");
  string includedir = getenv("LQANALYZER_INCLUDE_PATH");
  string coreincludedir = getenv("LQANALYZER_CORE_PATH");
  string includedir_snu = getenv("SNUTREE_INCLUDE_PATH");

  gSystem->AddIncludePath(("-I" + includedir).c_str());
  gSystem->AddIncludePath(("-I" + includedir_snu).c_str());
  gSystem->AddIncludePath(("-I" + coreincludedir + "/Plotting/include/").c_str());
  gSystem->AddIncludePath(("-I" + coreincludedir + "/core/include/").c_str());
  gSystem->AddIncludePath(("-I" + coreincludedir + "/Selection/include/").c_str());

  gROOT->ProcessLine(".L ChainMaker.C+g");

  gSystem->Load("libSNUTree.so");
  gSystem->Load("libcore.so");
  gSystem->Load("libSelection.so");
  gSystem->Load("libPlotting.so");  
  //  gSystem->Load("libHist.so");

  gSystem->ChangeDirectory((maindir + "/LQCycle/src/").c_str());
  gROOT->ProcessLine(".L Analyzer.cc+g");
  //  gSystem->Load("libLQCycle.so");

  /// Selection Code compilation                                                                                                                              
  //////////////////////////////////////////////////////////
  //                          MC                          //
  //////////////////////////////////////////////////////////
  
/// Signal samples
  if (1) {
    
  // Create Chains
    //TChain* chain50 = ChainMaker("/data/HN_data/SampleList/Signal/signal_all.txt");
    TChain* chain50 = ChainMaker((maindir + "/LQRun/list.txt"));    
    
    Analyzer Pippo(Analyzer::ZTest); /// create analyzer class object    
    Pippo.Init(chain50);
    Pippo.SetName("Majorana_50",1);
    Pippo.SetTargetLumi(1.);
    Pippo.SetWeight(1., 1.);
    //    Pippo.NEvents(10000);
    Pippo.Run();

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
       
