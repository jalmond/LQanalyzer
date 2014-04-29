#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleElectron=true

if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    cycle="ExampleAnalyzerDiElectron"
    skinput="True"
    useskim="DiLep"
    outputdir=$LQANALYZER_DIR"/data/output/Electron/"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma")
    declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "WZ" "ZZ" "WW")
    
    source submit.sh $1
fi
    

################ DOUBLEELECTRON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDoubleElectron  == "true" ]];
then
    source functions.sh
    cycle="ExampleAnalyzerDiElectron"
    skinput="True"
    stream="egamma"
    useskim="DiLep"
    outputdir=$LQANALYZER_DIR"/data/output/Electron/"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh $1
fi     





echo ""
echo "End of example_submit.sh script."