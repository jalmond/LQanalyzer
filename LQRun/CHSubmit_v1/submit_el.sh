
#!/bin/sh

rundata=false
rundataMu=false
runmc=false
runmcEl=true
runsig=false

if [[ $runsig  == "true" ]];
then
    #signal
    source functions.sh
    
#    cycle="CHEJ_bestfit_data"
#	cycle="CHEJ_Ana"
	cycle="CHEJ_bestfit"
#    cycle="CHElJets"
#	cycle="CHEltrain"
#	cycle="CHMuJets"
    skinput="True"
	useskim="NoCut"
#	useskim=""

    njobs=30
#	njobs=1
	data_lumi="AtoD"
#	data_lumi="A"
    loglevel="INFO"
	
    logstep=1000

#	nevents=1000
	nevents=-1

#	stream="singleelectron"
#    declare-1
#	declare -a input_samples=("Csbar100")
#	declare -a input_samples=("CH130PU")
	declare -a input_samples=("CH120PU" "CH90PU" "CH110PU" "CH140PU" "CH100PU" "CH150PU" )
#	declare -a input_samples=("CH120PU" "CH130PU" "CH90PU" "CH110PU" "CH140PU" "CH100PU" "CH150PU" )
#	declare -a input_samples=("ttbarMS")
#	declare -a input_samples=("A" "B" "C" "D")
#	declare -a input_samples=("stbar_sch")

#	outputdir=$LQANALYZER_DIR"/data/output/CHElJets/Sig/lowpt/"
	outputdir=$LQANALYZER_DIR"/data/output/CHEJ_087cut/highpt/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/Sig/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHMuJets/test/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHEltrain/"
	
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
fi



if [[ $runmc  == "true" ]];

then

    source functions.sh
    
#    cycle="CHMuJets"
    cycle="SMTopJetCorr_test"
#    cycle="TopCorr_L7_allmatch"
	skinput="True"
    useskim=""
    
    njobs=1
    data_lumi="AtoD"
    loglevel="INFO"
#    samples2016="True"
    loglevel="INFO"
    logstep=1000
    nevents=100
	
#	declare -a input_samples=("ttbar" "topLJ" "topHAD" "topDIL" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "Wjets" "DY50plus" "WW_py" "ZZ_py" "WZ_py" "QCD_20_30_EM" "QCD_30_80_EM" "QCD_80_170_EM" "QCD_170_250_EM" "QCD_250_350_EM" "QCD_350_EM" "QCD_20_30_BCtoE" "QCD_30_80_BCtoE" "QCD_80_170_BCtoE" "QCD_170_250_BCtoE" "QCD_350_BCtoE")
#		declare -a input_samples=("W1Jets" "W2Jets" "W3Jets" "W4Jets" "Z1Jets" "Z2Jets" "Z3Jets" "Z4Jets" "WZ_py")

		declare -a input_samples=("ttbarMS")
#	declare -a input_samples=("ttbarMS")
#	declare -a input_samples=("CH90PU" "CH100PU" "CH110PU" "CH120PU" "CH130PU" "CH140PU" "CH150PU")

	outputdir=$LQANALYZER_DIR"/data/output/SMTSCorr/test/"
	
	    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi

if [[ $runmcEl  == "true" ]];

then

    source functions.sh
    
    cycle="CHEJ_bestfit"
#	cycle="CHEJ_Ana"
#	cycle="CHEltrain"
    skinput="True"
    useskim=""
    
    njobs=60
    data_lumi="AtoD"
    loglevel="INFO"

    logstep=1000
#	nevents=10000
	
#	declare -a input_samples=("ttbarMS" "stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW" "Wjets" "DY50plus" "DY10to50" "WW_py" "ZZ_py" "WW_py" "ttW" "ttZ" "QCD_20_30_EM" "QCD_30_80_EM" "QCD_80_170_EM" "QCD_170_250_EM" "QCD_250_350_EM" "QCD_350_EM" "QCD_20_30_BCtoE" "QCD_30_80_BCtoE" "QCD_80_170_BCtoE" "QCD_170_250_BCtoE" "QCD_250_350_BCtoE" "QCD_350_BCtoE")

	declare -a input_samples=("ttbarMS")
#	declare -a input_samples=("Wjets" "DY50plus" "DY10to50")
#	declare -a input_samples=("ZZ_py" "WZ_py" "WW_py")
#	declare -a input_samples=("stbar_sch" "stbar_tch" "stbar_tW" "st_sch" "st_tch" "st_tW")
#	declare -a input_samples=("ttH" "ttZ" "ttW")
#	declare -a input_samples=("QCD_20_30_EM" "QCD_30_80_EM" "QCD_80_170_EM" "QCD_170_250_EM" "QCD_250_350_EM" "QCD_350_EM" "QCD_20_30_BCtoE" "QCD_30_80_BCtoE" "QCD_80_170_BCtoE" "QCD_170_250_BCtoE" "QCD_250_350_BCtoE" "QCD_350_BCtoE" "QCD_mumu")


	outputdir=$LQANALYZER_DIR"/data/output/CHEJ_oldjetcut/highpt/"
#	outputdir=$LQANALYZER_DIR"/data/output/CHEltrain/"

	    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

fi

if [[ $rundata  == "true" ]];
then

    source functions.sh

    cycle="CHEJ_bestfit"
#	cycle="CHEJ_Ana"
    skinput="True"
    useskim=""

    njobs=60
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000

    declare -a input_samples=( "A" "B" "C" "D")
#	declare -a input_samples=( "A" "B")
#		declare -a input_samples=( "C" "D")

    stream="singleelectron"

    outputdir=$LQANALYZER_DIR"/data/output/CHEJ_087cut/highpt/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1
#    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_data_5_3_14.root HNDiElectron_period*
fi



if [[ $rundataMu  == "true" ]];
then

    source functions.sh

    cycle="CHMJ_bestfit_data"
    skinput="True"
    useskim=""

    njobs=20
    data_lumi="AtoD"
    loglevel="INFO"

    loglevel="INFO"
    logstep=1000
	nevents=-1
	
    declare -a input_samples=("B" "C" "D")
#	declare -a input_samples=("A")

    stream="singlemuon"

    outputdir=$LQANALYZER_DIR"/data/output/CHMJ_accep_test/Sig_high/"
    ### submit this configured job (uses bin/submit.sh)
    source submit.sh $1

#    source hadd.sh ${LQANALYZER_DIR}/data/output/SSElectron/  HNDiElectron_data_5_3_14.root HNDiElectron_period*
fi



echo ""
echo "End of example_submit.sh script."
