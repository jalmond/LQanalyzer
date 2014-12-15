#!/bin/sh

runData=false
runMC=false
runQCD=false
runQCD2=false


if [[ $1  == "MC"  ]];
then
    runMC=true
fi

if [[ $1  == "QCD"  ]];
then
    runQCD=true
fi


if [[ $1  == "QCD2"  ]];
then
    runQCD2=true
fi



if [[ $1  == "DATA"  ]];
then

    runData=true
fi


if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/"

    declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "Wgamma" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW"  )
    source submit.sh  
    source hadd.sh /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/  FakeRateCalculator_El_mc_5_3_14.root  FakeRateCalculator_El_SK*
    mv /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/MC/FakeRateCalculator_El_mc_5_3_14.root /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/

fi

if [[ $runQCD  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/QCD/"
    
    declare -a input_samples=("QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE" "QCD_350_EM" "QCD_350_BCtoE" )

    source submit.sh
    source hadd.sh /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/QCD/ FakeRateCalculator_El_SKQCD_5_3_14.root FakeRateCalculator_El_SKQCD*
    mv /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/QCD/FakeRateCalculator_El_SKQCD_5_3_14.root /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/
fi

if [[ $runQCD2  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/QCD2/"

    declare -a input_samples=( "QCD_30-40_EM2" "QCD_40_EM2")


    source submit.sh
    source hadd.sh /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/QCD2/ FakeRateCalculator_El_SKQCD_5_3_14.root FakeRateCalculator_El_SKQCD*

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
    outputdir="/home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/Data/"
    
    declare -a input_samples=("A" "B" "C" "D")

    source submit.sh $1

    source hadd.sh /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/Data/ FakeRateCalculator_El_data_5_3_14.root FakeRateCalculator_El_period*  
    mv /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/Data/FakeRateCalculator_El_data_5_3_14.root /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/
fi



echo ""
echo "End of example_submit.sh script."