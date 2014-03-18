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
#declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "W-W-" "W+W+" "Wgamma")
#declare -a input_samples=("A" "DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "W-W-" "W+W+" "Wgamma")
declare -a input_samples=("HNee100")
#use5314ntuples="True"
remove="False"


stream="muon"
outputdir="/home/jalmond/LQanalyzer/data/output/SSElectron/"



### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."