import os,getpass,filecmp
from CleanUp import *

def MakeDirectory(dirpath):
    predir=dirpath
    predir=predir.replace(os.getenv("yeartag"),"")
    if not os.path.exists(predir):
        os.system("mkdir " + predir)
    if not os.path.exists(dirpath):
        os.system("mkdir " + dirpath)


path_jobpre="/data1/"

if  "ui"  in str(os.getenv("HOSTNAME")):
    path_jobpre="/cms/scratch/SNU/CATAnalyzer/"

LQANALYZER_DIR= str(os.getenv("LQANALYZER_DIR"))
LQANALYZER_LOG= str(os.getenv("LQANALYZER_LOG_PATH"))

if not LQANALYZER_DIR == "None" :
	datadir = LQANALYZER_DIR + "/data/"	
	if not (os.path.exists(datadir)):
            print "This is the first time running LQAnalyzer in this location"
            print "Making data directory in $LQANALYZER_DIR"
            os.system("mkdir " + datadir)
            
	outfiledir= LQANALYZER_DIR +"/data/output/"

        MakeDirectory(LQANALYZER_DIR +"/data/Luminosity/")
	lumifiledir= LQANALYZER_DIR +"/data/Luminosity/"+ str(os.getenv("yeartag"))
        MakeDirectory(lumifiledir)
        MakeDirectory(LQANALYZER_DIR +"/data/BTag/")
        MakeDirectory(LQANALYZER_DIR +"/data/BTag/"+ str(os.getenv("yeartag")))
        MakeDirectory(outfiledir)
        
	if os.path.exists(os.getenv("LQANALYZER_DIR")+ "/nohup.out"):
		os.system("rm " +os.getenv("LQANALYZER_DIR")+ "/nohup.out")


        CleanUpLogs(path_jobpre+"LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ getpass.getuser()+ "/")
        CleanUpJobLogs(LQANALYZER_LOG)
	if os.getenv("HOSTNAME") == "cms.snu.ac.kr":
            CleanUpLogs(path_jobpre+"CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data2/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data2/DATA/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data7/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data7/DATA/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data8/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data8/DATA/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs("/data7/DATA/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
        else:
            ## setup kisti clean
            CleanUpLogs(path_jobpre+"CAT_SKTreeOutput/" + getpass.getuser()+ "/")
            CleanUpLogs(os.getenv("LQANALYZER_BATCHLIB_PATH"))



        yeartags = ["80X", "94X"]

        for yt in yeartags:
            samples_version = str(os.getenv("CATVERSION"))
            localfiledir = os.getenv("LQANALYZER_FILE_DIR")
            datasetfiledir = os.getenv("LQANALYZER_DATASETFILE_DIR")
            if yt == "94X":
                localfiledir = os.getenv("LQANALYZER_FILE2017_DIR")
                datasetfiledir = os.getenv("LQANALYZER_DATASETFILE2017_DIR")
                samples_version = "v9-4-9v2"
            
            txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"
            os.system("cp " + localfiledir + "/Luminosity/triggers_catversion_"+str(os.getenv("CATVERSION"))+"* "  + lumifiledir)
            os.system("cp " + localfiledir + "/Luminosity/lumi_catversion_"+str(os.getenv("CATVERSION"))+".txt "  + lumifiledir)
            os.system("cp " + datasetfiledir + "/list_all_mc_"+samples_version+ ".sh " + txtfiledir)

        
else:
	print "Area is not setup. Cannot make directories needed for analysis"

