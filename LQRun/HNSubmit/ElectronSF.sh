#!/bin/sh

rundata=true
runmc=true

if [[ $1  == "DATA" ]];
    then

    rundata=true
    runmc=false
fi

if [[ $1  == "MC" ]];
    then
    rundata=false
    runmc=true
fi

if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="ElectronSF"
    skinput="True"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    declare -a input_samples=("DY50plus")

    outputdir=$LQANALYZER_DIR"/data/output/ElectronSF/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1


fi

if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="ElectronSF"
    skinput="True"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")

    stream="egamma"

    outputdir=$LQANALYZER_DIR"/data/output/ElectronSF/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/ElectronSF/ ElectronSF_data_5_3_14.root ElectronSF_period*
fi


echo ""
echo "End of example_submit.sh script."