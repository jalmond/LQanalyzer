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
cycle="ExampleAnalyzerDiElectron"
skinput="True"
njobs=1
data_lumi="AtoD"
loglevel="INFO"
logstep=1000

##### LIST OF JOBS
#declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma")
#declare -a input_samples=("HNee100" "HNee100BF")
#declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW") 
stream="egamma"
outputdir="/home/jalmond/LQanalyzer/data/output/Electron/"
declare -a input_samples=("A")


### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."