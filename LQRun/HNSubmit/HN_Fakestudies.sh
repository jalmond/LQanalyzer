#!/bin/sh

rundata=false
runmc=false
runmc=false

if [[ $1  == "NP" ]];
    then
    runfakes=true
    rundata=false
    runmc=false
fi


if [[ $1  == "DATA" ]];
    then
    runfakes=false
    rundata=true
    runmc=false
fi

if [[ $1  == "MC" ]];
    then
    runfakes=false
    rundata=false
    runmc=true
fi

if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="HN_FakeStudies"
    skinput="True"
    useskim="DiLep"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
    declare -a input_samples=("WZ_py" "ZZ_py")
    
    outputdir=$LQANALYZER_DIR"/data/output/HNFake/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi
if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="HN_FakeStudies"
    skinput="True"
    useskim="DiLep"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")
    stream="emu"
    
    outputdir=$LQANALYZER_DIR"/data/output/HNFake/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/HNFake/  HN_FakeStudies_data_5_3_14.root HN_FakeStudies_period*
fi


if [[ $runfakes  == "true" ]];
    then
    source functions.sh
    
    cycle="HN_FakeStudies"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=30
    data_lumi="AtoD"
    
    loglevel="INFO"
    logstep=1000
    
    runnp="True"
    declare -a input_samples=("A" "B" "C" "D") 

    stream="emu"
    outputdir=$LQANALYZER_DIR"/data/output/HNFake/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/HNFake/  HN_FakeStudies_SKnonprompt_dilep_5_3_14.root HN_FakeStudies_nonprompt_period*
fi



echo ""
echo "End of example_submit.sh script."