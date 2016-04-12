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
	EightTeVdataTwo="/data4/" + getpass.getuser() + "/LQ_SKTreeOutput/"
        CleanUpLogs("/data1/LQ_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data2/LQ_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data4/LQ_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpJobLogs(LQANALYZER_LOG)
	CleanUpLogs(EightTeVdataOne)
	CleanUpLogs(EightTeVdataTwo)
	GetFiles(rootfiledir)
	
else:
	print "Area is not setup. Cannot make directories needed for analysis"

