def makeConfigFile(log,sample, input, fullinput, tree, cycle, ver, output, nevents, outstep, skipev, datatype, channel, period, totalmcevents, xsec, tar_lumi, eff_lumi):

    config='{\n'
    config+='  //### Load Libraries\n'
    config+='  gSystem->Load("libSKTree.so");\n'
    config+='  gSystem->Load("libHist.so");\n'
    config+='  gSystem->Load("libAnalysisCore.so");\n'
    config+='  gSystem->Load("libcore.so");\n'
    config+='  gSystem->Load("libSelection.so");\n'
    config+='  gSystem->Load("libPlotting.so");\n'
    config+='  gSystem->Load("libLQCycle.so");\n'
    config+='  gSystem->Load("libPyROOT.so");\n'
    config+='  \n'
    config+='  TString filename = "' + input + '";\n'
    config+='  TString fullfilename = "' + fullinput + '";\n'
    config+='  LQController analysis;\n'
    config+='  analysis.SetJobName("' + sample + "_" + cycle+'");\n'
    config+='  analysis.SetInputList(TString(filename));\n'
    config+='  analysis.SetFullInputList(TString(fullfilename));\n'
    config+='  analysis.SetTreeName("'+ tree +'");\n'
    config+='  analysis.SetCycleName("' + cycle + '");\n'
    config+='  analysis.SetName("' + sample + ' ", '+ str(ver) +',"'+ output +'");\n'                        
    config+='  analysis.SetLogLevel("'+ log +'");\n'
    
    
    if not eff_lumi == -1.:
        print "WTF" + str(eff_lumi)
        config+='  analysis.SetEffectiveLuminosity(' + str(eff_lumi)+');\n'
    if not tar_lumi ==-1. :    
        config+='  analysis.SetTargetLuminosity('+ str(tar_lumi) +');\n'
    if not nevents ==-1 :
        config+='  analysis.SetNEventsToProcess(' + str(nevents) + ');\n'
    if not skipev ==-1 :
        config+='  analysis.SkipEvents(' + str(skipev) + ');\n'
    if not outstep ==-1 :
        config+='  analysis.SetOutPutStep(' + str(outstep) + ');\n'
    if not period  =="":
        config+='  analysis.SetDataPeriod("' + period + '");\n'
    if not datatype =="":
        config+='  analysis.SetDataType( ' + datatype + ');\n'
    if not channel == "" :
        config+='  analysis.SetChannel( "' + channel +'");\n'
    if not totalmcevents == -1 :
        config+='  analysis.SetTotalMCEvents( ' + totalmcevents +');\n'
    if not xsec == -1.:
        config+='  analysis.SetMCCrossSection( ' + xsec +');\n'
        
    config+='  analysis.Initialize();\n'
    config+='  analysis.ExecuteCycle();\n'
    config+='  \n}'

    return config

#Import date
def now():
    from datetime import datetime
    return str(datetime.now().month) + str(datetime.now().day)+ str(datetime.now().hour)+str(datetime.now().minute)
