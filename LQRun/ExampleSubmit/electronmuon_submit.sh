#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=false
runElectronMuon=true

if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    cycle="ExampleAnalyzerElectronMuon"
    skinput="True"
    useskim="DiLep"
    outputdir=$LQANALYZER_DIR"/data/output/ElectronMuon/"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "WZ" "ZZ" "WW" )
    
    source submit.sh $1
fi
    

################ DOUBLEMUON DATA
if [[ $runElectronMuon  == "true" ]];
then
    source functions.sh
    cycle="ExampleAnalyzerElectronMuon"
    skinput="True"
    stream="emu"
    useskim="DiLep"
    outputdir=$LQANALYZER_DIR"/data/output/ElectronMuon/"
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