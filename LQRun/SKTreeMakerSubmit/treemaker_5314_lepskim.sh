#!/bin/sh
### sets all configurable variables to defaul values

###### SET WHAT JOBS TO RUN
runMC=false
runDoubleMuon=true
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
    njobs=300
    data_lumi="AtoD"
    loglevel="INFO"
    logstep=1000
    
    #usebatch="False"
    declare -a input_samples=(  "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "ttbarMS" "DY10to50" "DY50plus" "Wjets" "Wbb" "Zbb" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "ttW" "ttZ" "WZ_py" "ZZ_py" "WW_py" "QCD_mumu" "QCD_20_30_EM" "QCD_20_30_BCtoE" "QCD_30_80_EM" "QCD_30_80_BCtoE" "QCD_80_170_EM" "QCD_80_170_BCtoE" "QCD_170_250_EM" "QCD_170_250_BCtoE" "QCD_250_350_EM" "QCD_250_350_BCtoE" "QCD_350_EM" "QCD_350_BCtoE" "ttbar_mass169" "ttbar_mass171" "ttbar_mass175" "ttbar_matchingdown" "ttbar_matchingup" "ttbar_pow" "ttbar_pow_her" "ttbar_scaledown" "ttbar_scaleup" "ttbar_width_x5" "TTH" "Wgamma" )

    declare -a input_samples=(  "ttbarMSchs" "SSWmWm" "SSWpWp" "WW_dp" "WWW" "TTWW" "TTG" "ZZZ" "WWZ" "WWG" "Wbb" "ggHtoZZ" "HtoZZ" "HtoTauTau" "HtoWW" "Zgamma" "WgammaMu" "WgammaE" "WgammaTau" "WW_mg" "WZtollqq_mg" "WZtoqqln_mg" "WZtollln_mg" "ZZtollnn_mg" "ZZtollqq_mg" "ZZtollll_mg" "ZZtoeemm" "ZZtoeett" "ZZtommtt" "ZZtoeeee" "ZZtommmm" "ZZtotttt" "topDIL" "topHAD" "topLJ"  "ttbar_mass173" "ttbar_CT10_pythia" "ttbar_CT10_herwig" "CH120PU" "CHm120PU" "CH110PU" "CH100PU" "CH90PU" "CH130PU" "CH140PU" "CH150PU" "QCD_1000_mu" "QCD_15-20_mu" "QCD_20-30_mu" "QCD_30-50_mu" "QCD_50-80_mu" "QCD_120-170_mu" "QCD_800-1000_mu" "QCD_170-300_mu" "QCD_300-470_mu" "QCD_470-600_mu" "QCD_600-800_mu" "QCD_80-120_mu" )
    input_samples=( "WZZ")

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
    
    stream="muon_lowpt"

    declare -a input_samples=("D")

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
    
    stream="singleelectron_chs"

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

    stream="singlemuon_chs"
    declare -a input_samples=("A" "B" "C" "D")
    source submit.sh
fi




