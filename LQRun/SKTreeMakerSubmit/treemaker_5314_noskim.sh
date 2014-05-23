#!/bin/sh
### sets all configurable variables to defaul values

runSignal=false
runMC=true

if [[ $runSignal  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #declare -a input_samples=("HNmumu50" "HNmumu70" "HNmumu90" "HNmumu100" "HNmumu125" "HNmumu150" HNmumu175" "HNmumu200" "HNmumu225" "HNmumu250" "HNmumu275" "HNmumu300" "HNmumu325" "HNmumu350" "HNmumu375" "HNmumu400" "HNmumu500" "HNmumu600" "HNmumu700" "HNee50" "HNee70" "HNee90" "HNee100" "HNee125" "HNee150" HNee175" "HNee200" "HNee225" "HNee250" "HNee275" "HNee300" "HNee325" "HNee350" "HNee375" "HNee400" "HNee500" "HNee600" "HNee700")
    
    declare -a input_samples=("Wjets")
    source submit.sh
fi

if [[ $runMC  == "true" ]];
then
    source functions.sh
    cycle="SKTreeMakerNoCut"
    #### JOB CONFIGURATION
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    nevents=10000 
    
    #declare -a input_samples=("DY10to50" "DY50plus" "ttbar" "WZ" "ZZ" "WW" "Wjets" "QCD_mumu" "QCD_30-40_EM2" "QCD_40_EM2" "Wgamma" "SSWmWm" "SSWpWp" "WW_dp" "ttW" "ttZ" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "topDIL" "topHAD" "topLJ" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets")
    declare -a input_samples=("ttW")
    stream="muon"
    source submit.sh
fi