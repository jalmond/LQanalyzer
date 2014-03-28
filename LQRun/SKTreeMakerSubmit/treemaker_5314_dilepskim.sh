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
skinput="true"
cycle="SKTreeMakerDiLep"
njobs=30
loglevel="INFO"
logstep=1000
declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma")
useskim="Lepton"

stream="egamma"
### submit this configured job (uses bin/submit.sh)
source submit.sh
