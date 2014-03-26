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

njobs=30
loglevel="INFO"
logstep=1000
declare -a input_samples=("HNee100")

### submit this configured job (uses bin/submit.sh)
source submit.sh
