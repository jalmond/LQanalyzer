B#!/bin/sh
#1;2c## sets all configurable variables to defaul values
source functions.sh
###
###########################################################
## CONFIGURE JOB ####
###########################################################
#
#  THIS SECTION IS FOR USER:
#
############################################################

cycle="SKTreeMaker"
stream="muon"
njobs=1
data_lumi="AtoD"
loglevel="DEBUG"
#declare -a periods=("A" "B" "C" "D" "DY10to50" "DY50plus")
#declare -a input_samples=("C" "D" "DY10to50" "DY50plus")  
declare -a input_samples=("A")


### submit this configured job (uses bin/submit.sh)
source submit.sh
