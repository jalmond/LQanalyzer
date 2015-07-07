#!/bin/sh

rundata=true
runmc=true
runmc_cl=false
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
    
    cycle="HNEMu"
    skinput="True"
    useskim="NoCut"

    njobs=2
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    
    declare -a input_samples=("HNemu40" "HNemu50" "HNemu60" "HNemu70" "HNemu80" "HNemu90" "HNemu100" "HNemu125" "HNemu150" "HNemu175" "HNemu200" "HNemu225" "HNemu250" "HNemu275" "HNemu300" "HNemu325" "HNemu350" "HNemu375" "HNemu400" "HNemu500" "HNmue40" "HNmue50" "HNmue60" "HNmue70" "HNmue80" "HNmue90" "HNmue100" "HNmue125" "HNmue150" "HNmue175" "HNmue200" "HNmue225" "HNmue250" "HNmue275" "HNmue300" "HNmue325" "HNmue350" "HNmue375" "HNmue400" "HNmue500")

     declare -a input_samples=("HNemu300"  "HNemu350" "HNemu400" "HNemu500" "HNmue300" "HNmue350" "HNmue400" "HNmue500")
    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi




if [[ $runmc_cl  == "true" ]];

then

    source functions.sh

    cycle="HNEMu"
    skinput="True"
    useskim="DiLep"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("WZ_py")
    runnp="True"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/MCcl/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi

if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="HNEMu"
    skinput="True"
    useskim="DiLep"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    declare -a input_samples=("SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ" "WWW" "TTWW" "TTG" "ZZZ" "WZZ" "WWZ" "WWG" "WW_py" "WZ_py" "ZZ_py" "HtoWW" "HtoTauTau" "ggHtoZZ" "DY10to50" "DY50plus")
    declare -a input_samples=("WZ_py")
    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/MC/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectronMuon/MC/  HNEMu_mc_5_3_14.root HNEMu_*

fi




if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="HNEMu"
    skinput="True"
    useskim="DiLep"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")


    stream="emu"

    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectronMuon/  HNEMu_data_5_3_14.root HNEMu_period*
fi


if [[ $runfakes  == "true" ]];
    then
    source functions.sh
    
    ### FAKE
    cycle="HNEMu"
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
    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/"


    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectronMuon/  HNEMu_SKnonprompt_dilep_5_3_14.root HNEMu_nonprompt_period*
fi

if [[ $runflips  == "true" ]];
    then
    source functions.sh
    
    cycle="HNEMu"
    skinput="True"
    useskim="DiLep"
    loglevel="INFO"
    
    njobs=30
    data_lumi="AtoD"

    loglevel="INFO"
    logstep=1000

    runcf="True"
    declare -a input_samples=("A" "B" "C" "D" )
        
    stream="emu"
    outputdir=$LQANALYZER_DIR"/data/output/SSElectronMuon/"
    
    
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectronMuon/  HNEMu_SKchargeflip_dilep_5_3_14.root HNEMu_chargeflip_*
fi



echo ""
echo "End of example_submit.sh script."