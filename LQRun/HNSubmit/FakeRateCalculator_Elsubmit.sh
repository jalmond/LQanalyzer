#!/bin/sh

runData=true
runMC=true
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
    data_lumi="C"
    loglevel="INFO"
    logstep=1000
    outputdir="/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/data/output/CAT/ElectronFakes/Data/"

    declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WJets")

    source submit.sh  


fi



if [[ $runData  == "true" ]];
then
    source functions.sh
    cycle="FakeRateCalculator_El"
    skinput="True"

    njobs=30
    data_lumi="C"
    loglevel="INFO"
    logstep=1000
    stream="egamma"
    outputdir="/home/jalmond/HeavyNeutrino/13TeV/LQAnalyzer_cat/LQanalyzer/data/output/CAT/ElectronFakes/Data/"
    
    declare -a input_samples=("C")

    source submit.sh $1

#    source hadd.sh /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/Data/ FakeRateCalculator_El_data_5_3_14.root FakeRateCalculator_El_period*  
#    mv /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/Data/FakeRateCalculator_El_data_5_3_14.root /home/jalmond/Analysis/LQanalyzer/data/output/ElectronFakes/
fi
