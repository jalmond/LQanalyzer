#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleMuon=false
runDoubleElectron=false
runElectronMuon=false
runSingleMuon=false
runSingleElectron=false
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
    runDoubleMuon=true
    runDoubleElectron=false
    runElectronMuon=false
    runSingleMuon=false
    runSingleElectron=false
fi    


if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    #### JOB CONFIGURATION
    njobs=300
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
    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #usebatch="False"
     declare -a input_samples=( "DY10to50_pf" "DY50plus_pf"  "stbar_sch_pf" "stbar_tch_pf" "stbar_tW_pf" "st_sch_pf" "st_tch_pf" "st_tW_pf" "ttW_pf" "ttZ_pf" "WZ_py_pf"  "ZZ_py_pf" "WW_py_pf" "ttbar_mass169_pf" "ttbar_mass171_pf"  "ttbar_matchingdown_pf"  "ttbar_matchingup_pf" "ttbar_scaledown_pf" "ttbar_scaleup_pf"  "TTH_pf" "QCD_20_30_EM_pf" "QCD_20_30_BCtoE_pf" "QCD_30_80_EM_pf" "QCD_30_80_BCtoE_pf" "QCD_80_170_EM_pf" "QCD_80_170_BCtoE_pf" "QCD_170_250_EM_pf" "QCD_170_250_BCtoE_pf" "QCD_250_350_EM_pf" "QCD_250_350_BCtoE_pf" "QCD_350_EM_pf" "QCD_350_BCtoE_pf" "QCD_15_mu_pf")

     #declare -a input_samples=( "CH90PU_pf" "CH100PU_pf" "CH110PU_pf" "CH120PU_pf" "CH120mPU_pf" "CH130PU_pf" "CH140PU_pf" "CH150PU_pf" "CH110_mt171.5_pf" "CH110_mt173.5_pf")
      #declare -a input_samples=("CH120mPU_pf")

    source submit.sh

fi    
################ DOUBLEELECTRON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDoubleElectron  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=300
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
    njobs=300
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
    njobs=300
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
    njobs=500
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    stream="singleelectron"

    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh
fi


################ SINGLEMUON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runSingleMuon  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMaker"
    njobs=500
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

    stream="singlemuon_pf"
    declare -a input_samples=("A"  "B" "C" "D")
    source submit.sh
fi




