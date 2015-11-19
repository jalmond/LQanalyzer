import os,time

from functions import *

configfile=open('emailMC.txt','w')
configfile.write(makeEmail("Ferdinando",os.getenv("CATVERSION") , "MC"))
configfile.close()

GetEffectiveLumiIsRunning=True
While GetEffectiveLumiIsRunning:
    if (os.path.exists("/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/LQRun/txt/datasets_snu_CAT_mc_" + os.getenv("CATVERSION")+ ".txt")):
        GetEffectiveLumiIsRunning=False;
    else:
        time.sleep(30.)
                
    
