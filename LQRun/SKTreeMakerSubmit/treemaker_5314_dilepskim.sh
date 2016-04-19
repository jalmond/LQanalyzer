#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN

runMC=true
runDoubleMuon=true
runDoubleElectron=true
runElectronMuon=true
runSingleMuon=false
runSingleElectron=false

if [[ $1  == "ALL" ]];
then
    runMC=true
    runDoubleMuon=true
    runDoubleElectron=true
    runElectronMuon=true
    runSingleMuon=true
    runSingleElectron=true
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
    runDoubleElectron=true
    runElectronMuon=true
    runSingleMuon=false
    runSingleElectron=false
fi

if [[ $runMC  == "true" ]];
then
    source functions.sh
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"
   
    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

 declare -a input_samples=(  "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "ttbarMS" "DY10to50" "DY50plus" "Wjets" "Wbb" "Zbb" "W1Jets" "W2Jets" "W3Jets" "W4J
ets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "ttW" "ttZ" "WZ_py" "ZZ_py" "WW_py" "QCD_mumu" "ttbar_mass169" "ttbar_mass171" "ttbar_mass175" "ttbar_matchingdown" "ttbar_matchingup" "ttbar_pow" "ttbar_pow_her" "ttbar_scaledown" "ttbar_scaleup" "ttbar_width_x5" "TTH" "Wgamma" "ttbarMSchs" "SSWmWm" "SSWpWp" "WW_dp" "WWW" "TTWW" "TTG" "ZZZ" "WWZ" "WWG" "Wbb" "ggHtoZZ" "HtoZZ" "HtoTauTau" "HtoWW" "Zgamma" "WgammaMu" "WgammaE" "WgammaTau" "WW_mg" "WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "ZZtoeemm" "ZZtoeett" "ZZtommtt" "ZZtoeeee" "ZZtommmm" "ZZtotttt" "topDIL" "topHAD" "topLJ" "ttbar" "ttbar_mass173" "ttbar_CT10_pythia" "ttbar_CT10_herwig"  "QCD_1000_mu" "QCD_15-20_mu" "QCD_20-30_mu" "QCD_30-50_mu" "QCD_50-80_mu" "QCD_120-170_mu" "QCD_800-1000_mu" "QCD_170-300_mu" "QCD_300-470_mu" "QCD_470-600_mu" "QCD_600-800_mu" "QCD_80-120_mu"  "ttbar_pow" "ttbar_pow_her" "SKttbar_CT10_pythia" "ttbar_CT10_pythia" " TTH")


    source submit.sh
fi

################ DOUBLEELECTRON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDoubleElectron  == "true" ]];
then
    source functions.sh
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
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
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
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
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
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
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000

    stream="singleelectron"
    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh
fi


    
    
