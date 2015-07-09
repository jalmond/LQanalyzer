 #!/bin/sh

rundata=false
rundataMu=true
runmc=true
runmcEl=false
runsig=true

if [[ $runsig  == "true" ]];
then
    #signal
    source functions.sh
    
	cycle="CHMuJets"
    skinput="True"
    useskim="NoCut"

    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
    
    declare -a input_samples=("CH120PU" "CH100PU" "CH90PU" "CH110PU" "CH130PU" "CH140PU" "CH150PU")

    #outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/CDFCor/Sig/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/MixCor/Sig/"
	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/NewCor/Sig/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi



if [[ $runmc  == "true" ]];

then

    source functions.sh
    
    cycle="CHMuJets"
    skinput="True"
    useskim=""
    
    njobs=30
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
	nevents=-1
	
	declare -a input_samples=("ttbar" "topLJ" "topHAD" "topDIL" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "Wjets" "DY50plus" "WW_py" "ZZ_py" "WZ_py" "QCD_20_30_EM" "QCD_30_80_EM" "QCD_80_170_EM" "QCD_170_250_EM" "QCD_250_350_EM" "QCD_350_EM" "QCD_20_30_BCtoE" "QCD_30_80_BCtoE" "QCD_80_170_BCtoE" "QCD_170_250_BCtoE" "QCD_350_BCtoE")
#		declare -a input_samples=("W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "WZ_py")
#				declare -a input_samples=("ttbar")

#	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/CDFCor/MC/"
#		outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/MixCor/MC/"
	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/NewCor/MC/"
	
	    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi

if [[ $runmcEl  == "true" ]];

then

    source functions.sh
    
    cycle="CHElJets"
    skinput="True"
    useskim=""
    
    njobs=20
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

#	declare -a input_samples=("ttbar" "topLJ" "topHAD" "topDIL" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "Wjets" "DY50plus" "WW_py" "ZZ_py" "WW_py" "QCD_20_30_EM" "QCD_30_80_EM" "QCD_80_170_EM" "QCD_170_250_EM" "QCD_250_350_EM" "QCD_350_EM" "QCD_20_30_BCtoE" "QCD_30_80_BCtoE" "QCD_80_170_BCtoE" "QCD_170_250_BCtoE" "QCD_350_BCtoE")
	declare -a input_samples=("WZ_py")

	outputdir=$LQANALYZER_DIR"/data/output/CHElJets/MC/"

	    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi

if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="CHElJets"
    skinput="True"
    useskim=""

    njobs=20
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")

    stream="singleelectron"

    outputdir=$LQANALYZER_DIR"/data/output/CHElJets/DATA/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
#    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_data_5_3_14.root HNDiElectron_period*
fi



if [[ $rundataMu  == "true" ]];
then

    source functions.sh

    cycle="CHMuJets"
    skinput="True"
    useskim=""

    njobs=50
    data_lumi="AtoD"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=("A" "B" "C" "D")
#	declare -a input_samples=("A")

    stream="singlemuon"

#    outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/CDFCor/DATA/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/MixCor/DATA/"
	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/NewCor/DATA/"

	    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

#    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_data_5_3_14.root HNDiElectron_period*
fi



echo ""
echo "End of example_submit.sh script."