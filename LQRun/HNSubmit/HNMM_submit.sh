#!/bin/sh

rundata=true
runmc=true
runmc_cl=false
runsig=false
runfakes=true
runflips=false

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

if [[ $1  == "CL" ]];
    then
    runfakes=false
    rundata=false
    runmc=false
    runmc_cl=true
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


if [[ $runsig  == "true" ]];
then
    #signal
    source functions.sh
    
    cycle="HNDiMuon"
    skinput="True"
    useskim="NoCut"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    
    declare -a input_samples=("HNemu40" "HNemu50" "HNemu60" "HNemu70" "HNemu80" "HNemu90" "HNemu100" "HNemu125" "HNemu150" "HNemu175" "HNemu200" "HNemu225" "HNemu250" "HNemu275" "HNemu300" "HNemu325" "HNemu350" "HNemu375" "HNemu400" "HNemu500" "HNmue40" "HNmue50" "HNmue60" "HNmue70" "HNmue80" "HNmue90" "HNmue100" "HNmue125" "HNmue150" "HNmue175" "HNmue200" "HNmue225" "HNmue250" "HNmue275" "HNmue300" "HNmue325" "HNmue350" "HNmue375" "HNmue400" "HNmue500")

        
    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi




if [[ $runmc_cl  == "true" ]];

then

    source functions.sh

    cycle="HNDiMuon"
    skinput="True"
    useskim="DiLep"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("WZ_py")
    runnp="True"
    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/MCcl/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi

if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="HNDiMuon"
    skinput="True"
    useskim="DiLep"
    
    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    declare -a input_samples=("SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ" "WWW" "TTWW" "TTG" "ZZZ" "WZZ" "WWZ" "WWG" "WW_py" "WZ_py" "ZZ_py" "HtoWW" "HtoTauTau" "ggHtoZZ" )

    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/MC/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSMuon/MC/  HNDiMuon_mc_5_3_14.root HNDiMuon_*

fi




if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="HNDiMuon"
    skinput="True"
    useskim="DiLep"

    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")
    

    stream="muon"

    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSMuon/  HNDiMuon_data_5_3_14.root HNDiMuon_period*
fi


if [[ $runfakes  == "true" ]];
    then
    source functions.sh
    
    ### FAKE
    cycle="HNDiMuon"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"

    njobs=300
    data_lumi="AtoD"

    loglevel="INFO"
    logstep=1000
    
    runnp="True"
    declare -a input_samples=("A" "B" "C" "D")

    stream="muon"

    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSMuon/  HNDiMuon_SKnonprompt_dilep_5_3_14.root HNDiMuon_nonprompt_period*
fi

if [[ $runflips  == "true" ]];
    then
    source functions.sh
    
    cycle="HNDiMuon"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"
    
    njobs=30
    data_lumi="AtoD"

    loglevel="INFO"
    logstep=1000

    runcf="True"
    declare -a input_samples=("A" "B" "C" "D" )
        
    stream="muon"
    outputdir=$LQANALYZER_DIR"/data/output/SSMuon/"
    
    
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSMuon/  HNDiMuon_SKchargeflip_dilep_5_3_14.root HNDiMuon_chargeflip_*
fi



echo ""
echo "End of example_submit.sh script."