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
njobs=30
data_lumi="A"
loglevel="INFO"
logstep=1000
declare -a input_samples=("A" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW")
#declare -a input_samples=("A")
stream="muon"
outputdir="/home/jalmond/LQanalyzer/data/output/Muon/"
#LibList=("libMinuit.so") ### NO SPACES


### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."