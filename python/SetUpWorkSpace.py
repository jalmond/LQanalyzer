import os,getpass
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
	lumifiledir= LQANALYZER_DIR +"/data/Luminosity/"
	if not os.path.exists(lumifiledir):
		os.system("mkdir " + lumifiledir)
	btagfiledir = LQANALYZER_DIR +"/data/BTag/"
	if not os.path.exists(btagfiledir):
		os.system("mkdir " + btagfiledir)

	if not (os.path.exists(outfiledir)):
		os.system("mkdir " + outfiledir)
		print "Making data/output directory in $LQANALYZER_DIR"


	EightTeVdataOne="/data1/" + getpass.getuser() + "/LQ_SKTreeOutput/"
	EightTeVdataTwo="/data2/" + getpass.getuser() + "/LQ_SKTreeOutput/"
	 
	if os.path.exists(os.getenv("LQANALYZER_DIR")+ "/nohup.out"):
		os.system("rm " +os.getenv("LQANALYZER_DIR")+ "/nohup.out")
	CleanUpLogs("/data1/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data2/CAT_SKTreeOutput/" + getpass.getuser()+ "/")
	CleanUpLogs("/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalyzerStatistics/"+ getpass.getuser()+ "/")
	CleanUpJobLogs(LQANALYZER_LOG)
	CleanUpLogs(EightTeVdataOne)
	CleanUpLogs(EightTeVdataTwo)	
	localfiledir = os.getenv("LQANALYZER_FILE_DIR")
	txtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/"
	cltxtfiledir = os.getenv("LQANALYZER_DIR")+ "/LQRun/txt/Cluster/"
	seldir =os.getenv("LQANALYZER_DIR")+  "/CATConfig/SelectionConfig/"
	os.system("cp " + localfiledir + "/Luminosity/triggers_catversion* " + lumifiledir)
	os.system("cp " + localfiledir + "/Luminosity/lumi_catversion* " + lumifiledir)
	os.system("cp  /data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles//list_all_mc_"+str(os.getenv("CATVERSION"))+".sh " + txtfiledir)
	os.system("cp " + localfiledir + "/Selection/*.sel " + seldir)
	#os.system("cp " + localfiledir + "/*.csv " + btagfiledir)
	#os.system("source " +  os.getenv("LQANALYZER_DIR") + "/bin/IncludePrivateSamples.sh")
else:
	print "Area is not setup. Cannot make directories needed for analysis"

