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
    
    declare -a input_samples=("HNemu40" "HNemu50" "HNemu60" "HNemu70" "HNemu80" "HNemu90" "HNemu100" "HNemu125" "HNemu150" "HNemu175" "HNemu200" "HNemu225" "HNemu250" "HNemu275" "HNemu300" "HNemu325" "HNemu350" "HNemu375" "HNemu400" "HNemu500" "HNemu600" "HNemu700" "HNmue40" "HNmue50" "HNmue60" "HNmue70" "HNmue80" "HNmue90" "HNmue100" "HNmue125" "HNmue150" "HNmue175" "HNmue200" "HNmue225" "HNmue250" "HNmue275" "HNmue300" "HNmue325" "HNmue350" "HNmue375" "HNmue400" "HNmue500" "HNmue600" "HNmue700")
    
    declare -a input_samples=("HNmue40")
    source submit.sh
fi


if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="SKTremuyMakerNoCut"
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