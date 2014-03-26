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
cycle="ExampleAnalyzer"
skinput="True"
njobs=1
data_lumi="A"
loglevel="INFO"
logstep=1000
#declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "W-W-" "W+W+" "Wgamma")
declare -a input_samples=("W-W-")
stream="muon"
#use5312ntuples="True"

#declare -a input_samples=('DY50plus:runevent:57156031:remove:true') #'B' 'C' 'D')
#declare -a input_samples=('DY50plus:remove:false') #'B' 'C' 'D')

### submit this configured job (uses bin/submit.sh)
source submit.sh $1

echo ""
echo "End of example_submit.sh script."