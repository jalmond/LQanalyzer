{
  //### Run this eith root -l -q -b Example_root_submit.C
  // make sure you have setup enviroment and compiled all codes
  
  string maindir = getenv("LQANALYZER_DIR");
  string base_path = maindir + "/LQRun/base/";
  string run_path = getenv("PWD");
  gSystem->ChangeDirectory(base_path.c_str());
  gROOT->ProcessLine(".L ChainMaker.C+g");
  gSystem->ChangeDirectory(run_path.c_str());
  /// egamma data example list                                                                                                                               
  TChain* chain = ChainMaker("/var/tmp/SKTree/Example/exampleSmall.txt");
  
  //### Load Libraries                                                         
  gSystem->Load("libSKTree.so");
  gSystem->Load("libcore.so");
  gSystem->Load("libHist.so");
  gSystem->Load("libAnalysisCore.so");
  gSystem->Load("libSelection.so");
  gSystem->Load("libPlotting.so");
  gSystem->Load("libLQCycle.so");
  gSystem->Load("libPyROOT.so");

  
  LQController analysis;
  analysis.SetJobName("Ztoll_ExampleCycle");
  analysis.SetTreeName("rootTupleTree/tree");
  analysis.SetCycleName("SKTreeMaker");
  //analysis.SetCycleName("Analyzer");
  analysis.SetEffectiveLuminosity(1.);
  analysis.SetTargetLuminosity(1.);
  analysis.SetLogLevel("INFO");
  analysis.SetDataType("data");
  analysis.SetNEventsToProcess(400000);
  analysis.SetName("TEST",1,"./");
  analysis.SetLQInput(true);
  analysis.SetInputChain(chain);

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


  analysis.Initialize();
  analysis.ExecuteCycle();


}
