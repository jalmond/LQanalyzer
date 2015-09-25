#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleMuon=false

if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    cycle="ExampleAnalyzerDiMuon"
    skinput="No"
    useskim="NoCut"
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Muon/"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    nevents=100000
    declare -a input_samples=("WZ")
    source submit.sh $1
fi
    

################ DOUBLEMUON DATA
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh
    cycle="ExampleAnalyzerDiMuon"
    skinput="True"
    stream="muon"
    useskim="DiLep"
    outputdir=$LQANALYZER_DIR"/data/output/Muon/"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    nevents=100000
    declare -a input_samples=("A")
    source submit.sh $1
fi     





echo ""
echo "End of example_submit.sh script."