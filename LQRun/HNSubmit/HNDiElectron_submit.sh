#!/bin/sh

rundata=true
runmc=true
runsig=true
runfakes=true
runflips=true

if [[ $1  == "NP" ]];
    then
    runfakes=true
    rundata=false
    runmc=false
    runsig=false
    runflips=false
fi

if [[ $1  == "CF" ]];
    then
    runfakes=false
    rundata=false
    runmc=false
    runsig=false
    runflips=true
fi

if [[ $1  == "DATA" ]];
    then
    runfakes=false
    rundata=true
    runmc=false
    runsig=false
    runflips=false
fi

if [[ $1  == "MC" ]];
    then
    runfakes=false
    rundata=false
    runmc=true
    runsig=false
    runflips=false
fi


if [[ $1  == "SIG" ]];
    then
    runfakes=false
    rundata=false
    runmc=false
    runsig=true
    runflips=false
fi

if [[ $1  == "testMC" ]];
    then
    
    rundata=false
    runmc=false
    runsig=false
    runfakes=false
    runflips=false
    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=1
    data_lumi="AtoD"
   
    declare -a input_samples=("DY10to50")

    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    
    
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi



if [[ $1  == "testData" ]];
then
    source functions.sh
    rundata=false
    runmc=false
    runsig=false
    runfakes=false
    runflips=false
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"
    njobs=1
    data_lumi="AtoD"
    
    nevents=10000000
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

    rundata=false
    runmc=false
    runsig=false
    runfakes=false
    runflips=false
    
    cycle="HNDiElectron"
    skinput="True"
    useskim="DiLep"

    njobs=1
    data_lumi="AtoD"

    nevents=10000
    loglevel="INFO"
    runnp="True"
    declare -a input_samples=("A")

    stream="egamma"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"

    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi


if [[ $runsig  == "true" ]];
then

    source functions.sh

    cycle="HNDiElectron"
    skinput="True"
    useskim="NoCut"

    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("HNee100" "HNee500")


    outputdir=$LQANALYZER_DIR"/data/output/SSElectron/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi



if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="HNDiElectron"
    skinput="True"
    #useskim="DiLep"
    
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
    
    #declare -a input_samples=("WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ" "Wgamma" "HtoZZ" "Zgamma" "DY10to50" "DY50plus")
    declare -a input_samples=("QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE")
    
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
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_data_5_3_14.root HNDiElectron_period*
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
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_SKnonprompt_dilep_5_3_14.root HNDiElectron_nonprompt_periodA*
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
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_SKchargeflip_dilep_5_3_14.root HNDiElectron_chargeflip_SK*
fi






echo ""
echo "End of example_submit.sh script."