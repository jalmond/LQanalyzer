#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleElectron=true
runCF=true

## RUN PARAMETERS
job_cycle="ExampleAnalyzerDiElectron"
job_useskim="DiLep" ### "Lepton" for single lepton skim   "DiLep" for dilepton skim
job_stream="egamma" ### "egamma" for DoubleEG dataset "muon" for DoubleMuon dataset
job_skinput="True"


job_data_lumi="ALL"  ###  "C" = period C only   "ALL"  = period C+D
job_logstep=1000
job_loglevel="INFO"
job_njobs=1

version_tag=${CATVERSION}



############################################################

outputdir_cat=$LQANALYZER_DIR"/data/output/CAT/"
outputdir_electron=$LQANALYZER_DIR"/data/output/CAT/Electron/"
if [[ ! -d "${outputdir_cat}" ]]; then
    mkdir ${outputdir_cat}
    echo "Making " + ${outputdir_cat}
fi

if [[ ! -d "${outputdir_electron}" ]]; then
    mkdir ${outputdir_electron}
    echo "Making " + ${outputdir_electron}
fi

dir_tag="periodC/"
if [[ $job_data_lumi  == "ALL" ]];
    then
    dir_tag="periodCtoD/"
fi

outputdir_mc=$LQANALYZER_DIR"/data/output/CAT/Electron/"$dir_tag
outputdir_data=$LQANALYZER_DIR"/data/output/CAT/Electron/"${dir_tag}$"/Data/"
echo $outputdir_data
echo ${outputdir_data}
output_datafile=$LQANALYZER_DIR"/data/output/CAT/Electron/"${dir_tag}$"/"$job_cycle"_data_cat"+${version_tag}+".root"
echo $output_datafile



if [[ $1  == "debug"  ]];
then
    job_njobs=1
    runMC=true
    runDoubleElectron=false
    runCF=false

    if [[ $2  == "DEBUG"  ]];
	then
	job_loglevel="DEBUG"
	
    fi
fi




if [[ ! -d "${outputdir_mc}" ]]; then
    mkdir ${outputdir_mc}
    echo "Making " + ${outputdir_mc}
fi

if [[ ! -d "${outputdir_data}" ]]; then
    mkdir ${outputdir_data}
    echo "Making " + ${outputdir_data}
fi



if [[ $1  == "MC"  ]];
then
    runMC=true
    runDoubleElectron=false
    runCF=false
fi

if [[ $1  == "DATA"  ]];
then
    runMC=false
    runDoubleElectron=true
    runCF=false
fi

if [[ $1  == "CF"  ]];
then
    runMC=false
    runDoubleElectron=false
    runCF=true
fi


########################################################################


if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    

    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput=$job_skinput
    njobs=$job_njobs
    outputdir=${outputdir_mc}

    if [[ $1  == "debug"  ]];
	then
	declare -a input_samples=("DY50plus")
	declare -a input_samples=("$2")
	source submit.sh $1

    fi
    if [[ $1  != "debug"  ]];
	then

	declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WJets" "WZ" "ZZ" "WW" "singletop_tbar" "singletop_t" "singletop_tbarW" "singletop_tW" "ttWJetsToLNu" "ttWJetsToQQ" "ttZToLLNuNu" "ttZToQQ")
	
	
	source submit.sh $1
    fi
fi


################ DOUBLEELECTRON DATA
if [[ $runDoubleElectron  == "true" ]];
then
    source functions.sh
    
    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput="True"
    njobs=$job_njobs
    
    skinput="True"
    
    outputdir=${outputdir_data}
    
    if [[ $job_data_lumi  == "ALL" ]];
        then
        declare -a input_samples=("C" "D1" "D2")
    fi

    if [[ $job_data_lumi  == "C" ]];
        then
        declare -a input_samples=("C")
    fi

    source submit.sh $1
    
    
    
    if [[ $job_data_lumi  == "C" ]];
        then
        echo "Ran only period C"
	
        mv  ${outputdir_data}/*.root ${output_datafile}
	
	
    fi
    if [[  $job_data_lumi  != "C" ]];
        then
        echo "source hadd.sh " ${outputdir_data} " " ${job_cycle}"_data_cat"${version_tag}".root "   ${outputdir_data}"/"${job_cycle}"*"${version_tag}".root"
	
        source hadd.sh ${outputdir_data} ${job_cycle}_data_cat${version_tag}.root ${outputdir_data}/${job_cycle}*${version_tag}.root
        echo ${outputdir_data}"/"${job_cycle}"_data_cat"${version_tag}".root "
        mv  ${outputdir_data}/${job_cycle}_data_cat${version_tag}.root  ${outputdir_mc}
    fi
    
fi



################ DOUBLEELECTRON DATA
if [[ $runCF  == "true" ]];
then
    source functions.sh

    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput="True"
    njobs=$job_njobs
    
    runcf="True"
    skinput="True"

    outputdir=${outputdir_data}

    if [[ $job_data_lumi  == "ALL" ]];
        then
        declare -a input_samples=("C" "D1" "D2")
    fi

    if [[ $job_data_lumi  == "C" ]];
        then
        declare -a input_samples=("C")
    fi

    source submit.sh $1



    if [[ $job_data_lumi  == "C" ]];
        then
        echo "Ran only period C"

        mv  ${outputdir_data}/*.root ${output_datafile}


    fi
    if [[  $job_data_lumi  != "C" ]];
        then
        echo "source hadd.sh " ${outputdir_data} " " ${job_cycle}"_data_cat"${version_tag}".root "   ${outputdir_data}"/"${job_cycle}"*"${version_tag}".root"

        source hadd.sh ${outputdir_data} ${job_cycle}_SKchargeflip_cat${version_tag}.root ${outputdir_data}/${job_cycle}_chargeflip*${version_tag}.root
        echo ${outputdir_data}"/"${job_cycle}"_SKchargeflip_cat"${version_tag}".root "
        mv  ${outputdir_data}/${job_cycle}_SKchargeflip_cat${version_tag}.root  ${outputdir_mc}
    fi

fi



echo ""
echo "End of example_submit.sh script."