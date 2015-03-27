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
    
    declare -a input_samples=("HNee40" "HNee50" "HNee60" "HNee70" "HNee80" "HNee90" "HNee100" "HNee125" "HNee150" "HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300" "HNee325" "HNee350" "HNee375" "HNee400" "HNee500" )
     declare -a input_samples=("HNee500")
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