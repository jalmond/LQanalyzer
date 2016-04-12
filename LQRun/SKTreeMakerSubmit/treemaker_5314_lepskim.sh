#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN
runMC=true
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
    runSingleMuon=true
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
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    
    declare -a input_samples=(  "stbar_sch_looseskim" "stbar_tch_looseskim" "stbar_tW_looseskim" "st_sch_looseskim" "st_tch_looseskim" "st_tW_looseskim" "ttbarMS_looseskim" "DY10to50_looseskim" "DY50plus_looseskim" "Wjets_looseskim" "Wbb_looseskim" "Zbb_looseskim" "W1Jets_looseskim" "W2Jets_looseskim" "W3Jets_looseskim" "W4Jets_looseskim" "Z1Jets_looseskim" "Z2Jets_looseskim" "Z3Jets_looseskim" "Z4Jets_looseskim" "ttW_looseskim" "ttZ_looseskim" "WZ_py_looseskim" "ZZ_py_looseskim" "WW_py_looseskim" "QCD_mumu_looseskim" "QCD_20_30_EM_looseskim" "QCD_20_30_BCtoE_looseskim" "QCD_30_80_EM_looseskim" "QCD_30_80_BCtoE_looseskim" "QCD_80_170_EM_looseskim" "QCD_80_170_BCtoE_looseskim" "QCD_170_250_EM_looseskim" "QCD_170_250_BCtoE_looseskim" "QCD_250_350_EM_looseskim" "QCD_250_350_BCtoE_looseskim" "QCD_350_EM_looseskim" "QCD_350_BCtoE_looseskim" "ttbar_mass169_looseskim" "ttbar_mass171_looseskim" "ttbar_mass175_looseskim" "ttbar_matchingdown_looseskim" "ttbar_matchingup_looseskim" "ttbar_pow_looseskim" "ttbar_pow_her_looseskim" "ttbar_scaledown_looseskim" "ttbar_scaleup_looseskim" "ttbar_width_x5_looseskim" "TTH_looseskim" "Wgamma_looseskim" )

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

    declare -a input_samples=("A" "B" "C" "D")

    source submit.sh
fi
################ ELECTRONMUON DATA
### submit this configured job (uses bin/submit.sh)

if [[ $runElectronMuon  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=30
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
    
    stream="singleelectron_looseskim"
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

    stream="singlemuon_looseskim"
    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh
fi




