def CopySKTrees(channel,sample,mc):

    import os
    filename = 'txt/datasets_cms21.txt'
    tmpxsec=0
    inputdir=""
    if not mc:
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    if channel ==entries[0] and sample == entries[1]:
                        inputdir = entries[2]
                        print inputdir 
    else:
        for line in open(filename, 'r'):
            if not line.startswith("#"):
                entries = line.split()
                if len(entries)==3:
                    tmpxsec=entries[1]
                    if sample == entries[0]:
                        inputdir = entries[2]

    sample_dir = os.getenv("LQANALYZER_DIR")+ "/data/input/"
    if not os.path.exists(sample_dir):                
        os.system("mkdir " + sample_dir)
    if not mc:
        sample_dir+= "data/"
        if not os.path.exists(sample_dir):
            os.system("mkdir " + sample_dir)
        sample_dir += channel+sample
        if not os.path.exists(sample_dir):
                os.system("mkdir " + sample_dir)
    else: 
        sample_dir += "mc/"    
        if not os.path.exists(sample_dir):  
            os.system("mkdir " + sample_dir)
        sample_dir += sample
        if not os.path.exists(sample_dir):
            os.system("mkdir " + sample_dir)     

    user = raw_input("Please enter username of cms21 account")    
    run = "scp " + str(user) + "@147.47.242.42:" + inputdir + "/*.root " + sample_dir
    print run
    os.system(run)
    
    with open('txt/datasets_mac.txt', 'a') as file:
        if not mc:
            towrite = channel + " " + sample + " " + inputdir
        else:
            towrite = sample + " " + tmpxsec + " " + inputdir
        file.write(towrite)

def makeConfigFile(log,sample, input, tree, cycle, ver, output_tmp, output, nevents, outstep, skipev, datatype, channel, period, totalmcevents, xsec, tar_lumi, eff_lumi, useSKinput, runevent):

    config='{\n'
    config+='    gEnv->SetValue("TFile.AsyncPrefetching", 1);\n'

    config+='   //### Load Libraries\n'
    config+='   gSystem->Load("libSKTree.so");\n'
    config+='   gSystem->Load("libHist.so");\n'
    config+='   gSystem->Load("libAnalysisCore.so");\n'
    config+='   gSystem->Load("libNtuplecore.so");\n'
    config+='   gSystem->Load("libSelection.so");\n'
    config+='   gSystem->Load("libPlotting.so");\n'
    config+='   gSystem->Load("libLQCycle.so");\n'
    config+='   gSystem->Load("libPyROOT.so");\n'
    config+='   \n'
    config+='   TString filename = "' + input + '";\n'
    config+='   LQController analysis;\n'
    if useSKinput == "True":        
        config+='   analysis.SetLQInput(false);\n'
    elif useSKinput == "true":
        config+='   analysis.SetLQInput(false);\n'
    else :
        config+='   analysis.SetLQInput(true);\n'
    config+='   analysis.SetJobName("' + sample + "_" + cycle+'");\n'
    config+='   analysis.SetInputList(TString(filename));\n'
    config+='   analysis.SetTreeName("'+ tree +'");\n'
    config+='   analysis.SetCycleName("' + cycle + '");\n'
    config+='   analysis.SetName("' + sample + '",'+ str(ver) +',"'+ output_tmp +'");\n'                        
    config+='   analysis.SetLogLevel("'+ log +'");\n'
    
    if not eff_lumi == -1.:
        config+='   analysis.SetEffectiveLuminosity(' + str(eff_lumi)+');\n'
    if not runevent ==-1:
        config+='   analysis.RunEvent(' + str(runevent)+');\n'
    if not tar_lumi ==-1.:    
        config+='   analysis.SetTargetLuminosity('+ str(tar_lumi) +');\n'
    if not nevents ==-1:
        config+='   analysis.SetNEventsToProcess(' + str(nevents) + ');\n'
    if not skipev ==-1:
        config+='   analysis.SkipEvents(' + str(skipev) + ');\n'
    if not outstep ==-1 :
        config+='   analysis.SetOutPutStep(' + str(outstep) + ');\n'
    if not period  =="":
        config+='   analysis.SetDataPeriod("' + period + '");\n'
    if not datatype =="":
        config+='   analysis.SetDataType("' + datatype + '");\n'
    if not totalmcevents == -1 :
        config+='   analysis.SetTotalMCEvents(' + str(totalmcevents) +');\n'
    if not xsec == -1.:
        config+='   analysis.SetMCCrossSection(' + str(xsec) +');\n'
        
    config+='   analysis.Initialize();\n'
    config+='   analysis.ExecuteCycle();\n'

    config+='   gSystem->Exec("mv ' + output_tmp + sample + '_' + str(ver) + '.root ' + output + '");\n'
    config+='  \n}'

    return config

#Import date
def now():
    from datetime import datetime
    return str(datetime.now().month) + str(datetime.now().day)+ str(datetime.now().hour)+str(datetime.now().minute)
