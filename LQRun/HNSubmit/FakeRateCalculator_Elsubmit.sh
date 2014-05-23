#!/bin/sh

runData=true
runMC=true

if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/"

    declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE" "WW_py" "WZ_py" "ZZ_py" "QCD_350_EM" "QCD_350_BCtoE" "stbar_sch" "stbar_tch" "stbar_tW"  "st_sch" "st_tch" "st_tW"  )
    
    source submit.sh
fi

if [[ $runData  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    stream="egamma"
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/"

    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh $1
fi

echo ""
echo "End of example_submit.sh script."