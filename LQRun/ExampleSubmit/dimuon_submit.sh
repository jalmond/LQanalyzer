#!/bin/sh

###### SET WHAT JOBS TO RUN
runMC=true
runDoubleMuon=false


## RUN PARAMETERS
job_cycle="ExampleAnalyzerDiMuon"
job_data_lumi="CtoD"   ###  "C" = period C only   "ALL" or "CtoD"  = period C+D
job_stream="DoubleMuon" ### "egamma" for DoubleEG dataset "muon" for DoubleMuon dataset 
job_skinput="False" 

job_useskim="DiLep" ### "Lepton" for single lepton skim   "DiLep" for dilepton skim
job_logstep=1000
job_loglevel="DEBUG"
job_njobs=1

version_tag=${CATVERSION}

########################################################################


outputdir_cat=$LQANALYZER_DIR"/data/output/CAT/"
outputdir_muon=$LQANALYZER_DIR"/data/output/CAT/Muon/"
if [[ ! -d "${outputdir_cat}" ]]; then
    mkdir ${outputdir_cat}
    echo "Making " + ${outputdir_cat}
fi

if [[ ! -d "${outputdir_muon}" ]]; then
    mkdir ${outputdir_muon}
    echo "Making " + ${outputdir_muon}
fi

dir_tag="periodC/"
if [[ $job_data_lumi  == "ALL" ]];
    then 
    dir_tag="periodCtoD/"
fi

outputdir_mc=$LQANALYZER_DIR"/data/output/CAT/Muon/"$dir_tag
outputdir_data=$LQANALYZER_DIR"/data/output/CAT/Muon/"${dir_tag}$"/Data/"
echo $outputdir_data
echo ${outputdir_data}
output_datafile=$LQANALYZER_DIR"/data/output/CAT/Muon/"${dir_tag}$"/"$job_cycle"_data_cat"+${version_tag}+".root"
echo $output_datafile


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
    runDoubleMuon=false
fi

if [[ $1  == "DATA"  ]];
then
    runMC=false
    runDoubleMuon=true
fi

########################################################################


if [[ $runMC  == "true" ]]; 
then
    source functions.sh
    
    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput=${job_skinput}
    njobs=$job_njobs
    outputdir=${outputdir_mc}

    declare -a input_samples=("DY10to50" "DY50plus" "WJets" "TTJets_MG5" "WZ" "ZZ" "WW" "singletop_tbar" "singletop_t" "singletop_tbarW" "singletop_tW" "ttWJetsToLNu" "ttWJetsToQQ" "ttZToLLNuNu" "ttZToQQ")
    declare -a input_samples=("WZ")
    source submit.sh $1
fi


################ DOUBLEMUON DATA
if [[ $runDoubleMuon  == "true" ]];
then
    source functions.sh

    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput=${job_skinput}
    njobs=$job_njobs
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
	echo "source hadd.sh " ${outputdir_data} " " ${job_cycle} "_data_cat"${version_tag}".root "${job_cycle}"*"

        source hadd.sh ${outputdir_data} ${job_cycle}_data_cat${version_tag}.root ${outputdir_data}/${job_cycle}*
        echo ${outputdir_data}"/"${job_cycle}"_data_cat"${version_tag}".root "
        mv  ${outputdir_data}/${job_cycle}_data_cat${version_tag}.root  ${outputdir_mc}

    fi
fi




echo ""
echo "End of example_submit.sh script."