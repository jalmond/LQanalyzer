 # $Id: Makefile
 ###########################################################################
 # @Project: LQAnalyzer - ROOT-based analysis framework for Korea CMS      #
 #                                                                         #
 # @author John Almond       jalmond@cern.ch>           - SNU              #
 # Top level Makefile for compiling all the LQAnalyzer code                #
 #                                                                         #
 ###########################################################################

all: snutree core plotting selection cycle 

snutree::
	(cd SNUTree; make)

core::
	(cd LQCore/core; make)

plotting::
	(cd LQCore/Plotting; make)

selection::
	(cd LQCore/Selection; make)

cycle::
	(cd LQCycle; make)

clean::
	(cd SNUTree; make clean)	
	(cd LQCore/core; make clean)
	(cd LQCore/Plotting; make clean)
	(cd LQCore/Selection; make clean)
	(cd LQCycle; make clean)

distclean::
	(cd SNUTree; make distclean)
	(cd LQCore/core; make distclean)
	(cd LQCore/Plotting; make distclean)
	(cd LQCore/Selection; make distclean)
	(cd LQCycle; make distclean)