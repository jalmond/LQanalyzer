#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN
runMC=false
runDoubleMuon=false
runDoubleElectron=false
runElectronMuon=false
runSingleMuon=true
runSingleElectron=true
runSignal=false

if [[ $1  == "ALL" ]]; 
then
    runMC=true
    runDoubleMuon=true
    runDoubleElectron=true
    runElectronMuon=true
    runSingleMuon=true
    runSingleElectron=true
fi

if [[ $1  == "HN" ]];
then
    runMC=true
    runDoubleMuon=true
    runDoubleElectron=true
    runElectronMuon=true
fi


if [[ $1  == "MC" ]];
then
    runMC=true
    runDoubleMuon=false
    runDoubleElectron=false
    runElectronMuon=false
    runSingleMuon=false
    runSingleElectron=false
fi

if [[ $1  == "DATA" ]];
then
    runMC=false
    runDoubleMuon=false
    runDoubleElectron=true
    runElectronMuon=false
    runSingleMuon=false
    runSingleElectron=false
fi    


if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("HNmumu50")

    source submit.sh
fi


if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    cycle="SKTreeMaker"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    
    declare -a input_samples=("ttbar_mass175" "ttbar_matchingdown" "ttbar_matchingup" "ttbar_scaledown" "ttbar_scaleup" "ttbar_width_x5" "ttbar_central")
    declare -a input_samples=("W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets"  "Z3Jets" "Z4Jets")
    declare -a input_samples=("ttbar_central")
    declare -a input_samples=("CH150PU")
    source submit.sh
fi    
################ DOUBLEELECTRON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDoubleElectron  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    stream="egamma"
    declare -a input_samples=("A" "B" "C" "D")

    source submit.sh
fi    

################ DOUBLEMUON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    stream="muon"
    declare -a input_samples=("A" "B" "C" "D" )
#"B" "C" "D")
    source submit.sh
fi
################ ELECTRONMUON DATA
### submit this configured job (uses bin/submit.sh)

if [[ $runElectronMuon  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    stream="emu"
    declare -a input_samples=("A" "B" "C" "D")

    source submit.sh
fi
################ SINGLEELECTRON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runSingleElectron  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    stream="singleelectron"
    declare -a input_samples=("C" "D")
    source submit.sh
fi


################ SINGLEMUON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runSingleMuon  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

    stream="singlemuon"
    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh
fi




