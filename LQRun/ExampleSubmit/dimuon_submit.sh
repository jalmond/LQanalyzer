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
njobs=1
data_lumi="AtoD"
loglevel="INFO"
logstep=1000
#declare -a input_samples=("A" "B" "C" "D"  "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW")
declare -a input_samples=("HNee100" "HNee100v2")
nevents=100
stream="muon"

use5314ntuples="True"
outputdir="/home/jalmond/LQanalyzer/data/output/Muon/"
#LibList=("libMinuit.so") ### NO SPACES


### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."