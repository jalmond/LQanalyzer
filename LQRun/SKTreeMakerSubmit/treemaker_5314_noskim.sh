#!/bin/sh
### sets all configurable variables to defaul values

runSignal=false
runMC=true

if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    declare -a input_samples=("HNee40" "HNee50" "HNee60" "HNee70" "HNee80" "HNee90" "HNee100" "HNee125" "HNee150" "HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300" "HNee325" "HNee350" "HNee375" "HNee400" "HNee500" "HNee600" "HNee700")
    
    source submit.sh
fi


if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    nevents=10000
    declare -a input_samples=("DY50plus")
    
    stream="muon"

    source submit.sh
fi