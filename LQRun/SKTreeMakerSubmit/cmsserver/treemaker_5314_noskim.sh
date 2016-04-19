#!/bin/sh
### sets all configurable variables to defaul values

runSignal=true
runMC=false

if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    
    declare -a input_samples=("ttbar_CT10_pythia" "ttbar_CT10_herwig" "CH90PU" "CH100PU" "CH110PU" "CH120PU" "CHm120PU" "CH130PU" "CH140PU" "CH150PU")

    source submit.sh
fi


if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="DEBUG"
    logstep=1000
    declare -a input_samples=("TestSample_chs")
    stream="muon"

    source submit.sh
fi