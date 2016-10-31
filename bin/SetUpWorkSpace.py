import os,getpass
from GetAnalysisRootFiles import *
from CleanUp import *

LQANALYZER_DIR= str(os.getenv("LQANALYZER_DIR"))
LQANALYZER_LOG= str(os.getenv("LQANALYZER_LOG_PATH"))

if not LQANALYZER_DIR == "None" :
	datadir = LQANALYZER_DIR + "/data/"	
	if not (os.path.exists(datadir)):
		print "This is the first time running LQAnalyzer in this location"
		print "Making data directory in $LQANALYZER_DIR"
		os.system("mkdir " + datadir)
        
	rootfiledir= LQANALYZER_DIR +"/data/rootfiles/"
	if not (os.path.exists(rootfiledir)):
		os.system("mkdir " + rootfiledir)
		print "Making data/rootfiles directory in $LQANALYZER_DIR"
        
	outfiledir= LQANALYZER_DIR +"/data/output/"
	if not (os.path.exists(outfiledir)):
		os.system("mkdir " + outfiledir)
		print "Making data/output directory in $LQANALYZER_DIR"


	EightTeVdataOne="/data1/" + getpass.getuser() + "/LQ_SKTreeOutput/"
	EightTeVdataTwo="/data2/" + getpass.getuser() + "/LQ_SKTreeOutput/"
	 
	CleanUpLogs("/data1/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data2/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ getpass.getuser()+ "/")
	CleanUpJobLogs(LQANALYZER_LOG)
	CleanUpLogs(EightTeVdataOne)
	CleanUpLogs(EightTeVdataTwo)	
	GetFiles(rootfiledir)
	localfiledir = os.getenv("LQANALYZER_FILE_DIR")
	txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"
	cltxtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/Cluster/"
	#os.system("cp " + localfiledir + "/list_all_mc*.sh " + txtfiledir)
	os.system("cp " + localfiledir + "/triggers_catversion* " + rootfiledir)
	os.system("cp " + localfiledir + "/lumi_catversion* " + rootfiledir)

	os.system("source " +  os.getenv("LQANALYZER_DIR") + "/bin/IncludePrivateSamples.sh")
else:
	print "Area is not setup. Cannot make directories needed for analysis"

