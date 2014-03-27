#!/bin/sh
source functions.sh 

###########################################################
## CONFIGURE JOB ####
###########################################################
#
#  THIS SECTION IS FOR USER:
#
############################################################
## What cycle do you want to run.  
## 
cycle="HNDiElectron"
skinput="True"
njobs=1
data_lumi="AtoD"

loglevel="INFO"
logstep=1000

declare -a input_samples=("HNmumu50" "HNmumu70" "HNmumu90" "HNmumu100" "HNmumu125" "HNmumu150" "HNmumu175" "HNmumu200" "HNmumu225" "HNmumu250" "HNmumu275" "HNmumu300" "HNmumu325" "HNmumu350" "HNmumu375" "HNmumu400" "HNmumu500" "HNmumu600" "HNmumu700"  "HNee50" "HNee70" "HNee90" "HNee100" "HNee125" "HNee150" "HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300"  "HNee325" "HNee350" "HNee375" "HNee400" "HNee500" "HNee600" "HNee700" )

stream="muon"


outputdir="/home/jalmond/LQanalyzer/data/output/SSElectron/"
useskim="NoCut"


### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."