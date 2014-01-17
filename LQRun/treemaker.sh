#!/bin/sh
### sets all configurable variables to defaul values
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
stream="emu"
njobs=1
data_lumi="AtoD"
loglevel="INFO"
#declare -a periods=("A" "B" "C" "D" "DY10to50" "DY50plus")
#declare -a input_samples=("C" "D" "DY10to50" "DY50plus")  
declare -a input_samples=("A" "B" "C" "D" "WW" "Wjets")
#declare -a input_samples=("WW")

### submit this configured job (uses bin/submit.sh)
source submit.sh
