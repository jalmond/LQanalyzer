import os,sys
from functions import *

### dimuon
datasets = ["DoubleEG"]
cuts = ["DiElectron", "DiElectron_dijet","DiElectron_IDW","DiElectron_noW","DiElectron_puW","DiElectron_Trigger","DiElectron_SSPreselection","ZElectron"]
IDs = ["POGTight", "POGTighttruthmatch"]

for x in IDs:
    samples_os = ["top","wjets","dylow","dyhigh","qcd", "vv"]
    if "truthmatch" in x:
        samples_os = ["top","wjets","dylow","dyhigh","nonprompt_DoubleEG", "vv"]
                
    for d in datasets:
        
        runfile= open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/Plotting_PhaseSpaces_2016_BtoE/SKTreeValidationDir/run_" + x + "_"+d +".sh","w")
        runfile.write(MakeRunFile(d, cuts,x))
        
        for i in cuts:
            cutfile  = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/Plotting_PhaseSpaces_2016_BtoE/SKTreeValidationDir/SKTreeValidation"+d+"/dat/hn_cut_"+ x+"_"+ i + ".txt","w")
            cutfile.write(i + x + '\n')
            cutfile.write("END")       
            histfile  = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/Plotting_PhaseSpaces_2016_BtoE/SKTreeValidationDir/SKTreeValidation"+d+"/dat/hn_histfile.txt","w")
            histfile.write(MakeHistFile())
            configfile = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/Plotting_PhaseSpaces_2016_BtoE/SKTreeValidationDir/SKTreeValidation"+d+"/Config/hnplots_periodBtoE_"+x + "_"+i+".txt", "w")
            configfile.write(makeConfigFile("/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/SKTreeValidation/periodBtoE/", d ,"hn_histfile.txt","hn_cut_" + x + "_" +i + ".txt", "v8-0-1", samples_os, i+"_"+x))
            
    
