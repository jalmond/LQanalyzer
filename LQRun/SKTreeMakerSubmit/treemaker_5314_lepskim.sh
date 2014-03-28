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

#### JOB CONFIGURATION
njobs=30
data_lumi="AtoD"
loglevel="INFO"
logstep=1000

#declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar" "WZ" "ZZ" "WW" "Wjets" "QCD_mumu" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma" )
#declare input_samples=("WZ")

stream="egamma"
declare -a input_samples=("A")

### submit this configured job (uses bin/submit.sh)
source submit.sh

declare -a input_samples=("A")
stream="muon"
source submit.sh