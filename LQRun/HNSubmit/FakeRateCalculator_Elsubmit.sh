#!/bin/sh

runData=true
runMC=true
runQCD=false


## RUN PARAMETERS
job_cycle="FakeRateCalculator_El"
job_data_lumi="ALL"   ###  "C" = period C only   "ALL"  = period C+D
job_stream="egamma" ### "egamma" for DoubleEG dataset "muon" for DoubleMuon dataset 
job_skinput="True" 

job_useskim="Lepton" ### "Lepton" for single lepton skim   "DiLep" for dilepton skim
job_logstep=1000
job_loglevel="INFO"
job_njobs=15

version_tag=${CATVERSION}

########################################################################


outputdir_cat=$LQANALYZER_DIR"/data/output/CAT/"
outputdir_fake=$LQANALYZER_DIR"/data/output/CAT/ElectronFake/"
if [[ ! -d "${outputdir_cat}" ]]; then
    mkdir ${outputdir_cat}
    echo "Making " + ${outputdir_cat}
fi

if [[ ! -d "${outputdir_fake}" ]]; then
    mkdir ${outputdir_fake}
    echo "Making " + ${outputdir_fake}
fi

dir_tag="periodC/"
if [[ $job_data_lumi  == "ALL" ]];
    then 
    dir_tag="periodCtoD/"
fi



outputdir_mc=$LQANALYZER_DIR"/data/output/CAT/ElectronFake/"$dir_tag
outputdir_data=$LQANALYZER_DIR"/data/output/CAT/ElectronFake/"${dir_tag}$"/Data/"
echo $outputdir_data
echo ${outputdir_data}
output_datafile=$LQANALYZER_DIR"/data/output/CAT/ElectronFake/"${dir_tag}$"/"$job_cycle"_data_cat"+${version_tag}+".root"
echo $output_datafile

#echo "source hadd.sh " ${outputdir_data} " " ${job_cycle} "_data_cat"+${version_tag}+".root "${job_cycle}"*" 

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
fi

if [[ $1  == "QCD"  ]];
then
    runQCD=true
fi

if [[ $1  == "DATA"  ]];
then

    runData=true
fi

if [[ $runMC  == "true" ]];
then
    source functions.sh
    
    cycle=$job_cycle
    data_lumi=$job_data_lumi
    stream=$job_stream
    useskim=$job_useskim
    skinput="True"
    njobs=$job_njobs
    outputdir=${outputdir_mc}

    declare -a input_samples=("DY10to50" "DY50plus" "TTJets_MG5" "WJets")

    source submit.sh  $1


fi



if [[ $runData  == "true" ]];
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
     echo "source hadd.sh " ${outputdir_data} " " ${job_cycle} "_data_cat"${version_tag}".root "${outputdir_data}"/"${job_cycle}"*"
     
     source hadd.sh ${outputdir_data} ${job_cycle}_data_cat${version_tag}.root ${outputdir_data}/${job_cycle}*
     echo ${outputdir_data}"/"${job_cycle}"_data_cat"${version_tag}".root "
     mv  ${outputdir_data}/${job_cycle}_data_cat${version_tag}.root  ${outputdir_mc}
 fi
fi
