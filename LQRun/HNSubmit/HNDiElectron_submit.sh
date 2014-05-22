#!/bin/sh

rundata=true
runmc=true
runfakes=true
runflips=true

if [[ $1  == "NP" ]];
    then
    runfakes=true
    rundata=false
    runmc=false
    runflips=false
fi

if [[ $1  == "CF" ]];
    then
    runfakes=false
    rundata=false
    runmc=false
    runflips=true
fi

if [[ $1  == "DATA" ]];
    then
    runfakes=false
    rundata=true
    runmc=false
    runflips=false
fi

if [[ $1  == "MC" ]];
    then
    runfakes=false
    rundata=false
    runmc=true
    runflips=false
fi


if [[ $1  == "testMC" ]];
    then
    
    rundata=false
    runmc=false
    runfakes=false
    runflips=false
    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=30
    data_lumi="AtoD"
   
    declare -a input_samples=("DY50plus")

    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    
    
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi


if [[ $1  == "testData" ]];
then
    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    njobs=1
    data_lumi="AtoD"
    
    nevents=100000
    loglevel="INFO"
    declare -a input_samples=("A")
    
    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    
fi

if [[ $1  == "testNP" ]];
then
    source functions.sh

    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"

    njobs=1
    data_lumi="AtoD"

    nevents=100000
    loglevel="INFO"
    runnp="True"
    declare -a input_samples=("A")

    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"

    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi

if [[ $runmc  == "true" ]];
then

    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
    
    declare -a input_samples=("DY10to50" "DY50plus" "ttbar")
# "Wjets" "WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ" "Wgamma" "HtoZZ" "Zgamma")
    
    
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi


if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")
    stream="egamma"
    
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi


if [[ $runfakes  == "true" ]];
    then
    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=30
    data_lumi="AtoD"
    
    loglevel="INFO"
    logstep=1000
    
    runnp="True"
    declare -a input_samples=("A" "B" "C" "D") 


    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi

if [[ $runflips  == "true" ]];
    then
    source functions.sh

    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=30
    data_lumi="AtoD"

    loglevel="INFO"
    logstep=1000

    runcf="True"
    #declare -a input_samples=("A" "B" "C" "D" "DY10to50" "DY50plus" "ttbar")
    declare -a input_samples=("DY10to50" "DY50plus" "ttbar")


    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi






echo ""
echo "End of example_submit.sh script."