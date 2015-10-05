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
    outputdir=$LQANALYZER_DIR"/data/output/CAT/SKMuon/"
    njobs=30
    declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WZ" "ZZ" "WW" "QCD_mu20to30" "QCD_mu30to50" "QCD_mu50to80" "QCD_mu80to120" "QCD_mu120to170" "QCD_mu170to300" "QCD_mu300to470" "QCD_mu470to600" "QCD_mu600to800" "QCD_mu800to1000" "QCD_mu1000toINF"  "ttWJetsToLNu" "ttWJetsToQQ" "ttZToLL" "ttZToQQ")

    declare -a input_samples=("DY50plus")
    source submit.sh $1
fi

if [[ $runMC  == "true" ]];
then
    source functions.sh

    cycle="ExampleAnalyzerDiMuon"
    data_lumi="ALL"
    stream="muon"
    skinput="True"
    outputdir=$LQANALYZER_DIR"/data/output/CAT/SKMuon/"
    njobs=30
    declare -a input_samples=("DY50plus")
    source submit.sh $1
fi

    
if [[ $runMC  == "true" ]];
then
    source functions.sh

    cycle="ExampleAnalyzerDiMuon"
    data_lumi="ALL"
    stream="muon"
#    skinput="True"
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Muon/"
    njobs=30

    declare -a input_samples=("DY50plus")
    source submit.sh $1
fi


################ DOUBLEMUON DATA
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh

    cycle="ExampleAnalyzerDiMuon"
    skinput="True"
    data_lumi="ALL"
    stream="muon"
    njobs=30
    outputdir=$LQANALYZER_DIR"/data/output/CAT/SKMuon/"
    #### JOB CONFIGURATION

    declare -a input_samples=("C")

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
    outputdir=$LQANALYZER_DIR"/data/output/CAT/SKMuon/"
    #### JOB CONFIGURATION

    declare -a input_samples=("C")

    source submit.sh $1
fi


################ DOUBLEMUON DATA
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh

    cycle="ExampleAnalyzerDiMuon"
    data_lumi="ALL"
    stream="muon"
    njobs=30
    outputdir=$LQANALYZER_DIR"/data/output/CAT/Muon/"
    #### JOB CONFIGURATION

    declare -a input_samples=("C")

    source submit.sh $1
fi




echo ""
echo "End of example_submit.sh script."