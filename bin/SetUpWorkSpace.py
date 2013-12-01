import os
from GetAnalysisRootFiles import *


LQANALYZER_DIR= str(os.getenv("LQANALYZER_DIR"))

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

	GetFiles(rootfiledir)
	
else:
	print "Area is not setup. Cannot make directories needed for analysis"

