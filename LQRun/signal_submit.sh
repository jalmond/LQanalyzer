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
cycle="Analyzer"
## Which stream is being run egamma/muon
# This is for data (used to set input) / Not needed for MC
#stream="muon"
## How many cores should the job use
njobs=2
## How much data are you running/ for MC this sets target luminosity to weight the events
## can be A/B/C/D/AtoD
data_lumi="A"
### name output location : by default it is ${LQANALYZER_DIR}/data/output, but you can change it 
outputdir=${LQANALYZER_DIR}/data/output/
### OUTPUT LEVEL
loglevel="INFO"

### FOR TESTING
#remove_workspace="False"
## How many events between log messages (default = 10000)     
# logstep=1000 
# skipevent
# loglevel  /// VERBOSE/DEBUG/INFO/WARNING
# nevents   /// set number of events to process
#### WHAT SAMPLES TO RUN >> THIS SHOULD CORRESPOND TO FIRST COLUMN IN txt/datasets.txt#
#declare -a periods=( "HNmumu100" "HNmumu200")
declare -a periods=( "HNmumu100")

############################################################
################# Do not change anything after this line
############################################################

if [ -z ${LQANALYZER_DIR} ]
    then 
    setupLQANALYZER
fi

#### FULL LIST OF OPTIONS
stream=$(makeParseVariable 's' ${stream})
njobs=$(makeParseVariable 'j' ${njobs})
cycle=$(makeParseVariable 'c' ${cycle})
data_lumi=$(makeParseVariable 'd' ${data_lumi})
outputdir=$(makeParseVariable 'O' ${outputdir})
logstep=$(makeParseVariable 'o' ${logstep})
skipevent=$(makeParseVariable 'k' ${skipevent})
loglevel=$(makeParseVariable 'l' ${loglevel})
nevents=$(makeParseVariable 'n' ${nevents})
totalev=$(makeParseVariable 'e' ${totalev})
xsec=$(makeParseVariable 'x' ${xsec})
targetlumi=$(makeParseVariable 'T' ${targetlumi})
efflumi=$(makeParseVariable 'E' ${efflumi})
remove=$(makeParseVariable 'w' ${remove_workspace})

echo  ${loglevel}


################
#submit
for i in ${periods[@]}
  do
  outlog="/var/tmp/"${USER}"/log_"${i}".txt"
  #nohup python ${LQANALYZER_DIR}/python/localsubmit.py -p ${i} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} &> $outlog&
  python ${LQANALYZER_DIR}/python/localsubmit.py -p ${i} ${stream} ${njobs} ${cycle} ${logstep} ${data_lumi} ${outputdir} ${remove} ${loglevel} ${skipevent} ${nevents} ${totalev} ${xsec} ${targetlumi} ${efflumi} ${remove}
done

################
echo ""
echo "Done"