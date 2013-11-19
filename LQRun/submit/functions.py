def makeConfigFile(job, input, sample, ver, output, nevents):

    config='{\n'
    config+='  string maindir = getenv("LQANALYZER_DIR");\n'   
    config+='  \n'   
    config+='  string base_path = maindir + "/LQRun/base/";\n'
    config+='  string run_path = getenv("PWD");\n'
    config+='  gSystem->ChangeDirectory(base_path.c_str());\n'
    config+='  gROOT->ProcessLine(".L ChainMaker.C+g");\n'
    config+='  gSystem->ChangeDirectory(run_path.c_str());\n'
    config+='  \n'
    config+='  //### Load Libraries\n'
    config+='  gSystem->Load("libSNUTree.so");\n'
    config+='  gSystem->Load("libcore.so");\n'
    config+='  gSystem->Load("libSelection.so");\n'
    config+='  gSystem->Load("libPlotting.so");\n'
    config+='  gSystem->Load("libHist.so");\n'
    config+='  gSystem->Load("libLQCycle.so");\n'
    config+='  \n'
    config+='  TChain* chain = ChainMaker("' + input + '");\n'
    config+='  \n'
    config+='  Analyzer SNUanal(Analyzer::'+ job +');\n'
    config+='  /// create analyzer class object\n'
    config+='  SNUanal.Init(chain);\n'
    config+='  SNUanal.SetName("'+ sample +'",'+ str(ver) +',"'+ output +'");\n'
    config+='  SNUanal.SetTargetLumi(1.);\n'
    config+='  SNUanal.SetWeight(1., 1.);\n'

    if not nevents ==-1 : 
        config+='  SNUanal.NEvents(' + str(nevents) + ');\n'
    config+='  SNUanal.Run();\n'
    config+='  \n}'

    return config

#Import date
def now():
    from datetime import datetime
    return str(datetime.now().month) + str(datetime.now().day)+ str(datetime.now().hour)+str(datetime.now().minute)
