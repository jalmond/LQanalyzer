import os,sys
from functions import *

### dimuon
datasets = ["DoubleMuon"]
cuts = ["DiMuon",  "DiMuon_dijet","DiMuon_noW","DiMuon_puW","DiMuon_Trigger","DiMuon_SSPreselection","ZMuon"]
IDs = ["POGTightroch_corrected"]


for x in IDs:
    samples_os = ["top","wjets","dylow","dyhigh", "vv"]
    if "truthmatch" in x:
        samples_os = ["top","wjets","dylow","dyhigh","nonprompt_DoubleMuon", "vv"]
                
    for d in datasets:
        
        runfile= open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/13TeV/2016/Plotting_PhaseSpaces_2016_BtoG/SKTreeValidationDir/run_" + x + "_"+d +".sh","w")
        runfile.write(MakeRunFile(d, cuts,x))
        
        for i in cuts:
            cutfile  = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/13TeV/2016/Plotting_PhaseSpaces_2016_BtoG/SKTreeValidationDir/SKTreeValidation"+d+"/dat/hn_cut_"+ x+"_"+ i + ".txt","w")
            cutfile.write(i + x + '\n')
            cutfile.write("END")       
            histfile  = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/13TeV/2016/Plotting_PhaseSpaces_2016_BtoG/SKTreeValidationDir/SKTreeValidation"+d+"/dat/hn_histfile.txt","w")
            histfile.write(MakeHistFile())
            configfile = open("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/Macros/Plotting/13TeV/2016/Plotting_PhaseSpaces_2016_BtoG/SKTreeValidationDir/SKTreeValidation"+d+"/Config/hnplots_periodCtoD_"+x + "_"+i+".txt", "w")
            configfile.write(makeConfigFile("/data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer//data/output/CAT/SKTreeValidation/periodBtoG/", d ,"hn_histfile.txt","hn_cut_" + x + "_" +i + ".txt", "v8-0-2", samples_os, i+"_"+x))
            
    
