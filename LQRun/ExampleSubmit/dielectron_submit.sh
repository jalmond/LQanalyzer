#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=false
runDoubleElectron=true

if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    cycle="ExampleAnalyzerDiElectron"
    skinput="True"
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Electron/periodCtoD/"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="ALL"
    loglevel="INFO"
    logstep=1000
    useskim="DiLep"
    
    declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WZ" "ZZ" "WW" "singletop_tbar" "singletop_t" "singletop_tbarW" "singletop_tW" "ttWJetsToLNu" "ttWJetsToQQ" "ttZToLLNuNu" "ttZToQQ")
    

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
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Electron/periodCtoD/Data/"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="ALL"
    useskim="DiLep"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("C" "D")
    source submit.sh $1

    source hadd.sh ${LQANALYZER_DIR}/data/output/CAT/Electron/periodCtoD/Data/ExampleAnalyzerDiElectron_data_catv4_7_2.root ExampleAnalyzerDiElectron*
    mv  ${LQANALYZER_DIR}/data/output/CAT/Electron/periodCtoD/Data/ExampleAnalyzerDiElectron_data_catv4_7_2.root  ${LQANALYZER_DIR}/data/output/CAT/Electron/periodCtoD/
    #mv  ${LQANALYZER_DIR}/data/output/CAT/Electron/periodC/Data/*periodC* ${LQANALYZER_DIR}/data/output/CAT/Electron/periodC/ExampleAnalyzerDiElectron_data_catv4_7_2.root

fi     





echo ""
echo "End of example_submit.sh script."