 # $Id: Makefile
 ###########################################################################
 # @Project: LQAnalyzer - ROOT-based analysis framework for Korea CMS      #
 #                                                                         #
 # @author John Almond       jalmond@cern.ch>           - SNU              #
 # Top level Makefile for compiling all the LQAnalyzer code                #
 #                                                                         #
 ###########################################################################

all: tagcheck btag roch fakes sktree AnalysisCore Ntuplecore plotting selection analysis 

sktree::
	(cd LQCore/SKTree; make)

Ntuplecore::
	(cd LQCore/Ntuplecore; make)

roch::
	(bash bin/Make/make_rocher_lib.sh; cd ${LQANALYZER_DIR} )

AnalysisCore::
	(cd LQCore/AnalysisCore; make)

plotting::
	(cd LQCore/Plotting; make)

selection::
	(cd LQCore/Selection; make)

analysis::
	(cd LQAnalysis/Helpers; make)
	(cd LQAnalysis/Analyzers; make)
	(cd LQAnalysis/SKTreeMaker; make)
	(cd LQAnalysis/Validation; make)


fakes::
	(cd ${LQANALYZER_DIR}/LQAnalysis/Helpers/HNCommonLeptonFakes/conf/; make -f Makefile.StandAlone; cd ${LQANALYZER_LIB_PATH} ;rm libHNCommonLeptonFakes.so ; cp ${LQANALYZER_DIR}/LQAnalysis/Helpers/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .; cd ${LQANALYZER_DIR} )

btag::  
	(bash bin/Make/make_btag_lib.sh; cd ${LQANALYZER_DIR} )	

tagcheck::
	(source bin/CheckNewTagCompiler.sh ${CHECKTAGFILE})

clean::
	(cd LQCore/SKTree; make clean)
	(cd LQCore/Ntuplecore; make clean)
	(cd LQCore/AnalysisCore; make clean)
	(cd LQCore/Plotting; make clean)
	(cd LQCore/Selection; make clean)
	(cd LQAnalysis/Helpers; make clean)
	(cd LQAnalysis/Analyzers; make clean)
	(cd LQAnalysis/SKTreeMaker; make clean)
	(cd LQAnalysis/Validation; make clean)
	(bash bin/Clean/clean_fake.sh)
	(bash bin/Clean/clean_rochor.sh)
	(bash bin/Clean/clean_btag.sh)

distclean::
	(cd LQCore/SKTree; make distclean)
	(cd LQCore/Ntuplecore; make distclean)
	(cd LQCore/AnalysisCore; make distclean)
	(cd LQCore/Plotting; make distclean)
	(cd LQCore/Selection; make distclean)
	(cd LQAnalysis/Helpers; make distclean)
	(cd LQAnalysis/Analyzers; make distclean)
	(cd LQAnalysis/SKTreeMaker; make distclean)
	(cd LQAnalysis/Validation; make distclean)


	(bash bin/Clean/clean_fake.sh)
	(bash bin/Clean/clean_rochor.sh)
	(bash bin/Clean/clean_btag.sh)

