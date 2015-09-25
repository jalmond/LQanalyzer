#!/bin/sh
### sets all configurable variables to defaul values

runSignal=false
runMC=true

if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    declare -a input_samples=("HNee40")
    source submit.sh
fi


if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
#    nevents=10000
    declare -a input_samples=("WZ" "ZZ" "WW")
    
    stream="muon"

    source submit.sh
fi