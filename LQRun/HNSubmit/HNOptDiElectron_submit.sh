#!/bin/sh

rundata=true
runmc=true
runsig=true
runcf=true
runfakes=true


if [[ $1  == "NP" ]];
    then
    runfakes=true
    rundata=false
    runmc=false
    runcf=false
    runsig=false
fi

if [[ $1  == "CF" ]];
    then
    runfakes=false
    runcf=true
    rundata=false
    runmc=false
    runsig=false
fi



if [[ $1  == "DATA" ]];
    then
    runfakes=false
    rundata=true
    runmc=false
    runsig=false
    runcf=false
fi

if [[ $1  == "MC" ]];
    then
    runfakes=false
    rundata=false
    runmc=true
    runsig=false
    runcf=false
fi


if [[ $1  == "SIG" ]];
    then
    runfakes=false
    rundata=false
    runmc=false
    runsig=true
    runcf=false
fi



if [[ $runsig  == "true" ]];
then

    source functions.sh

    cycle="HNElectronOptimisation"
    skinput="True"
    useskim="NoCut"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("HNee40" "HNee50" "HNee60" "HNee70" "HNee80" "HNee90" "HNee100" "HNee125" "HNee150" "HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300" "HNee325" "HNee350" "HNee375" "HNee400 ""HNee500" "HNee600" "HNee700")
    
    
    outputdir=$LQANALYZER_DIR"/data/output/ElectronOpt/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi



if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="HNElectronOptimisation"
    skinput="True"
    useskim="DiLep"
    
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
    
    declare -a input_samples=( "WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ")
    
    outputdir=$LQANALYZER_DIR"/data/output/ElectronOpt/MC/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/ElectronOpt/MC/  HNElectronOptimisation_mc_dilep_5_3_14.root HNElectronOptimisation_SK*

fi

if [[ $runcf  == "true" ]];

then

    source functions.sh

    cycle="HNElectronOptimisation"
    skinput="True"
    useskim="DiLep"


    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "DY10to50" "DY50plus" "ttbar")

    outputdir=$LQANALYZER_DIR"/data/output/ElectronOpt/CF/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/ElectronOpt/CF/  HNElectronOptimisation_cf_dilep_5_3_14.root HNElectronOptimisation_SK*

    
fi



if [[ $rundata  == "true" ]];
    then
    
    source functions.sh

    cycle="HNElectronOptimisation"
    skinput="True"
    useskim="DiLep"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")
    stream="egamma"
    
    outputdir=$LQANALYZER_DIR"/data/output/Electronopt/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNElectronOptimisation_data_5_3_14.root HNElectronOptimisation_period*
fi


if [[ $runfakes  == "true" ]];
    then
    source functions.sh
    
    cycle="HNElectronOptimisation"
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
    outputdir=$LQANALYZER_DIR"/data/output/ElectronOpt/NP/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/ElectronOpt/NP/  HNElectronOptimisation_SKnonprompt_dilep_5_3_14.root HNElectronOptimisation_nonprompt_period*
fi




echo ""
echo "End of example_submit.sh script."