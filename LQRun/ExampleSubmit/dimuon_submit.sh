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
cycle="ExampleAnalyzerDiMuon"
skinput="True"
stream="muon"
##### CONFIGURE JOB
njobs=30
data_lumi="AtoD"
loglevel="INFO"
logstep=1000
outputdir="/home/jalmond/LQanalyzer/data/output/Muon/"

#### SET SAMPLES
declare -a input_samples=("A" "B" "C" "D"  "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW")

### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."