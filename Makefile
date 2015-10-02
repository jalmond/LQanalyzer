 # $Id: Makefile
 ###########################################################################
 # @Project: LQAnalyzer - ROOT-based analysis framework for Korea CMS      #
 #                                                                         #
 # @author John Almond       jalmond@cern.ch>           - SNU              #
 # Top level Makefile for compiling all the LQAnalyzer code                #
 #                                                                         #
 ###########################################################################

all: fakes sktree AnalysisCore Ntuplecore plotting selection analysis 

sktree::
	(cd LQCore/SKTree; make)

Ntuplecore::
	(cd LQCore/Ntuplecore; make)

AnalysisCore::
	(cd LQCore/AnalysisCore; make)

plotting::
	(cd LQCore/Plotting; make)

selection::
	(cd LQCore/Selection; make)

analysis::
	(cd LQAnalysis; make)

fakes::
	(cd HNCommonLeptonFakes/conf/; make -f Makefile.StandAlone; cd ${LQANALYZER_LIB_PATH} ;rm libHNCommonLeptonFakes.so ; cp ${LQANALYZER_DIR}/HNCommonLeptonFakes/Root/libHNCommonLeptonFakes.so .; cd ${LQANALYZER_DIR} )



clean::
	(cd LQCore/SKTree; make clean)
	(cd LQCore/Ntuplecore; make clean)
	(cd LQCore/AnalysisCore; make clean)
	(cd LQCore/Plotting; make clean)
	(cd LQCore/Selection; make clean)
	(cd LQAnalysis; make clean)
	(cd HNCommonLeptonFakes/conf/; make clean -f Makefile.StandAlone; rm ${LQANALYZER_LIB_PATH}/libHNCommonLeptonFakes.so)

distclean::
	(cd LQCore/SKTree; make distclean)
	(cd LQCore/Ntuplecore; make distclean)
	(cd LQCore/AnalysisCore; make distclean)
	(cd LQCore/Plotting; make distclean)
	(cd LQCore/Selection; make distclean)
	(cd LQAnalysis; make distclean)	
