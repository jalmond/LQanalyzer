#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN

runMC=true
runDoubleMuon=false
runDoubleElectron=false
runElectronMuon=false
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
    runDoubleMuon=false
    runDoubleElectron=true
    runElectronMuon=false
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
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "Wjets" "WZ_py" "ZZ_py" "WW_py" "Wjets" "QCD_mumu" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma" "SSWmWm" "SSWpWp" "WW_dp"" ttW" "ttZ" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "topDIL" "topHAD" "topLJ" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "Wbb" "Zbb" "DYee" "DYmm" "DYtt" "ggHtoZZ"  "Zgamma" "WgammaE" "WW_mg" "WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "ZZtoeemm" "ZZtoeett" "ZZtommtt" "ZZtommmm" "ZZtoeeee" "ZZtotttt" "QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE" "QCD_350_EM" "QCD_350_BCtoE" "TTWW" "TTG" "ZZZ" "WZZ" "WWZ" "HtoTauTau" "HtoWW" "WgammaMu" "WgammaTau" "WWW" "WWG" "HtoZZ" "HtoWW" "HtoTauTau")
    declare -a input_samples=("stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW"  "Wbb" "Zbb""QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE" "WZ_py" "ZZ_py" "WW_py")

    declare -a input_samples=("SSWmWm" "WZ_py" "ZZ_py" "WW_py" "SSWpWp" "WW_dp" "ttW" "ttZ" "TTWW" "TTG" "ZZZ" "WZZ" "WWZ" "HtoTauTau" "HtoWW"   "WWW" "WWG" "HtoZZ")

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
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
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
    ##### HERE WE CAN USE SKTREES AS INPUT IF THE LEPTON SKIMS ARE AVAILABLE
    skinput="true"
    useskim="Lepton"

    cycle="SKTreeMakerDiLep"
    #### JOB CONFIGURATION
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


    
    
