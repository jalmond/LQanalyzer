{
  std::getchar();
  string maindir = getenv("LQANALYZER_DIR");
  string base_path = maindir + "/LQRun/base/";
  string run_path = getenv("PWD");
  //gSystem->ChangeDirectory(base_path.c_str());                               
  //gROOT->ProcessLine(".L ChainMaker.C+g");                                   
  //gSystem->ChangeDirectory(run_path.c_str());                                

  std::getchar();
  //### Load Libraries                                                         
  gSystem->Load("libSKTree.so");
  gSystem->Load("libcore.so");
  gSystem->Load("libHist.so");
  gSystem->Load("libAnalysisCore.so");
  gSystem->Load("libSelection.so");
  gSystem->Load("libPlotting.so");
  gSystem->Load("libLQCycle.so");
  gSystem->Load("libPyROOT.so");

  TString filename = "/var/tmp/jalmond/A_1122445/Job_1/A_1.txt";

  std::getchar();
  LQController analysis;
  analysis.SetJobName("Ztoll_ExampleCycle");
  analysis.SetInputList(TString(filename));
  analysis.SetFullInputList(TString(filename));
  analysis.SetTreeName("rootTupleTree/tree");
  analysis.SetCycleName("Analyzer");
  analysis.SetEffectiveLuminosity(1.);
  analysis.SetTargetLuminosity(1.);
  analysis.SetLogLevel("INFO");
  analysis.SetNEventsToProcess(20000);
  analysis.SetName("TEST",1,"/var/tmp/jalmond/A_1122445/output/");

  ///Other options : analysis.                                                 
  //RunEvent(i) --> only run this event: can do many times                     
  //SetOutPutStep(100) -->output every 100 events                              
  //SkipEvents                                                                 
  //SetDataType(data/mc)                                                       
  //SetChannel(mm/ee)                                                          
  //SetDataPeriod(A/B/C/D)                                                     
  //SetTotalMCEvents                                                           
  //SetMCCrossSection                                                          
  //SetNEventsToProcess                                                        
  //SetTargetLuminosity                                                        
  //SetEffectiveLuminosity                                                     


  std::getchar();
  analysis.Initialize();
  std::getchar();
  analysis.ExecuteCycle();


}
