#!/bin/sh
### sets all configurable variables to defaul values

runSignal=true
runMC=false

if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #declare -a input_samples=("HNmumu40" "HNmumu50" "HNmumu60" "HNmumu70" "HNmumu80" "HNmumu90" "HNmumu100" "HNmumu125" "HNmumu150" HNmumu175" "HNmumu200" "HNmumu225" "HNmumu250" "HNmumu275" "HNmumu300" "HNmumu325" "HNmumu350" "HNmumu375" "HNmumu400" "HNmumu500" "HNmumu600" "HNmumu700" "HNee40" "HNee50" "HNee60" "HNee70" "HNee80" "HNee90" "HNee100" "HNee125" "HNee150" HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300" "HNee325" "HNee350" "HNee375" "HNee400" "HNee500" "HNee600" "HNee700")
    declare -a input_samples=("HNee300")
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