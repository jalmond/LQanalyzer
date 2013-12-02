{
  //### Run this eith root -l -q -b Example_root_submit.C
  // make sure you have setup enviroment and compiled all codes
  
  //### Load Libraries                                                         
  gSystem->Load("libSKTree.so");
  gSystem->Load("libcore.so");
  gSystem->Load("libHist.so");
  gSystem->Load("libAnalysisCore.so");
  gSystem->Load("libSelection.so");
  gSystem->Load("libPlotting.so");
  gSystem->Load("libLQCycle.so");
  gSystem->Load("libPyROOT.so");

  /// egamma data example list
  TString filename = "/var/tmp/SKTree/Example/exampleSmall.txt";

  LQController analysis;
  analysis.SetJobName("Ztoll_ExampleCycle");
  analysis.SetInputList(TString(filename));
  analysis.SetFullInputList(TString(filename));
  analysis.SetTreeName("rootTupleTree/tree");
  analysis.SetCycleName("Analyzer");
  analysis.SetEffectiveLuminosity(1.);
  analysis.SetTargetLuminosity(1.);
  analysis.SetLogLevel("INFO");
  analysis.SetDataType("data");
  analysis.SetNEventsToProcess(400000);
  analysis.SetName("TEST",1,"./");

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
