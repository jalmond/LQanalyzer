#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleMuon=true

## RUN PARAMETERS
#logstep=1000
#loglevel="INFO"
#cycle="ExampleAnalyzerDiMuon"
data_lumi="ALL"
#    useskim="DiLep"
#    stream="muon"

if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    
    cycle="ExampleAnalyzerDiMuon"
    data_lumi="ALL"
    stream="muon"
    useskim="DiLep"
    skinput="True"
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Muon/periodCtoD/"
    njobs=30
    declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WZ" "ZZ" "WW" "singletop_tbar" "singletop_t" "singletop_tbarW" "singletop_tW" "ttWJetsToLNu" "ttWJetsToQQ" "ttZToLLNuNu" "ttZToQQ")

    source submit.sh $1
fi


################ DOUBLEMUON DATA
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh

    cycle="ExampleAnalyzerDiMuon"
    skinput="True"
    data_lumi="ALL"
    useskim="DiLep"
    stream="muon"
    njobs=30
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Muon/periodCtoD/Data/"
    #### JOB CONFIGURATION

    declare -a input_samples=("C" "D")


    source submit.sh $1
    source hadd.sh ${LQANALYZER_DIR}/data/output/CAT/Muon/periodCtoD/Data/  ExampleAnalyzerDiMuon_data_catv4_7_2.root ExampleAnalyzerDiMuon*
    mv  ${LQANALYZER_DIR}/data/output/CAT/Muon/periodCtoD/Data/ExampleAnalyzerDiMuon_data_catv4_7_2.root  ${LQANALYZER_DIR}/data/output/CAT/Muon/periodCtoD/

fi




echo ""
echo "End of example_submit.sh script."