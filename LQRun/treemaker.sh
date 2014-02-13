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

stream="egamma"
njobs=30
data_lumi="AtoD"
loglevel="INFO"
declare -a input_samples=("D" "DY10to50" "DY50plus")

### submit this configured job (uses bin/submit.sh)
source submit.sh
