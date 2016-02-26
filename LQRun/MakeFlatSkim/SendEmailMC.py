import os,time

catversion=os.getenv("CATVERSION")

from functions import *

configfile=open('emailMC.txt','w')
configfile.write(makeEmail("Ferdinando",catversion , "MC"))
configfile.close()

GetEffectiveLumiIsRunning=True
while GetEffectiveLumiIsRunning:
    if (os.path.exists("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_" + catversion+ ".txt")):
        GetEffectiveLumiIsRunning=False;
    else:
        time.sleep(30.)
                
    
