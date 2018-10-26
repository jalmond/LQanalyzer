 # $Id: Makefile
 ###########################################################################
 # @Project: LQAnalyzer - ROOT-based analysis framework for Korea CMS      #
 #                                                                         #
 # @author John Almond       jalmond@cern.ch>           - SNU              #
 # Top level Makefile for compiling all the LQAnalyer code                #
 #                                                                         #
 ###########################################################################

#all: tagcheck btag roch fakes Ntuplecore plotting selection analysis 
all: Ntuplecore
Ntuplecore::
	(cd LQCore/Ntuplecore; make)
	(python python/PCM.py -x LQCore/Ntuplecore/src/Ntuplecore_Dict_rdict.pcm)

roch::
	(bash bin/Make/make_rocher_lib.sh; cd ${LQANALYZER_DIR} )

plotting::
	(cd LQCore/Plotting; make)
	(python python/PCM.py -x /Plotting/src/Plotting_Dict_rdict.pcm)

selection::
	(cd LQCore/Selection; make)
	(python python/PCM.py -x LQCore/Selection/src/Selection_Dict_rdict.pcm)
analysis::
	(cd LQAnalysis/AnalyzerTools; make)
	(cd LQAnalysis/Analyzers; make)
	(cd LQAnalysis/SKTreeMaker; make)
	(cd LQAnalysis/Validation; make)
	(python python/PCM.py -x LQAnalysis/AnalyzerTools/src/AnalyzerTools_Dict_rdict.pcm)
	(python python/PCM.py -x LQAnalysis/Analyzers/src/LQAnalysis_Dict_rdict.pcm)
	(python python/PCM.py -x LQAnalysis/SKTreeMaker/src/SKTreeMaker_Dict_rdict.pcm)
	(python python/PCM.py -x LQAnalysis/Validation/src/Validation_Dict_rdict.pcm)

fakes::
	(cd ${LQANALYZER_DIR}/LQAnalysis/AnalyzerTools/HNCommonLeptonFakes/conf/; make -f Makefile.StandAlone; cd ${LQANALYZER_LIB_PATH} ;rm libHNCommonLeptonFakes.so ; cp ${LQANALYZER_DIR}/LQAnalysis/AnalyzerTools/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .; cd ${LQANALYZER_DIR} )


btag::  
	(bash bin/Make/make_btag_lib.sh; cd ${LQANALYZER_DIR} )	

tagcheck::
	(source bin/CheckNewTagCompiler.sh ${CHECKTAGFILE})

clean::
	(cd LQCore/Ntuplecore; make clean)
	(cd LQCore/Plotting; make clean)
	(cd LQCore/Selection; make clean)
	(cd LQAnalysis/AnalyzerTools; make clean)
	(cd LQAnalysis/Analyzers; make clean)
	(cd LQAnalysis/SKTreeMaker; make clean)
	(cd LQAnalysis/Validation; make clean)
	(bash bin/Clean/clean_fake.sh)
	(bash bin/Clean/clean_rochor.sh)
	(bash bin/Clean/clean_btag.sh)
	(rm ${LQANALYZER_LIB_PATH}/*.pcm)

distclean::
	(cd LQCore/Ntuplecore; make distclean)
	(cd LQCore/Plotting; make distclean)
	(cd LQCore/Selection; make distclean)
	(cd LQAnalysis/AnalyzerTools; make distclean)
	(cd LQAnalysis/Analyzers; make distclean)
	(cd LQAnalysis/SKTreeMaker; make distclean)
	(cd LQAnalysis/Validation; make distclean)

	(bash bin/Clean/clean_fake.sh)
	(bash bin/Clean/clean_rochor.sh)
	(bash bin/Clean/clean_btag.sh)
	(rm ${LQANALYZER_LIB_PATH}/*.pcm)

