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

stream="muon"
njobs=30
data_lumi="AtoD"
loglevel="INFO"
#declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "W-W-" "W+W+" "Wgamma")

declare -a input_samples=("A") 

### submit this configured job (uses bin/submit.sh)
source submit.sh
