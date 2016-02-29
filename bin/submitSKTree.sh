#!/bin/sh
### sets all configurable variables to defaul values


###### SET WHAT JOBS TO RUN
runMC=false
runDoubleMuon=false
runDoubleElectron=false
runSingleMuon=false
runElectronMuon=false
runSingleElectron=false
runSinglePhoton=false

## RUN PARAMETERS

job_data_lumi="CtoD"  ###  "C" = period C only   "ALL"  = period C+D
job_logstep=1000
job_loglevel="INFO"
job_njobs=30
job_skim="Lepton"

submit_skinput="true"
submit_version_tag=""
submit_file_tag=""
submit_file_list=""
submit_catversion=${CATVERSION}
submit_sampletag=""
submit_catvlist=""
submit_searchlist=""
submit_analyzer_name=""

### Get predefined lists
source ${LQANALYZER_DIR}/LQRun/txt/list_all_mc.sh
### setup list of samples and other useful functions
source submit_setup.sh

## RUN PARAMETERS
job_cycle="$submit_analyzer_name"
if [[ $submit_analyzer_name == "" ]];
    then
    echo "Need to set submit_analyzer_name: use -a CLASSNAME when submitting"
    exit 1
fi

#### HARDCODE the skinput for sktreemakers
if [[ $submit_analyzer_name == "SKTreeMaker" ]];
    then 
    submit_skinput="false"
    if [[ $submit_version_tag == "" ]];
	then 
	echo "When running SKTreeMaker you need to specify the catversion: -c "
	exit 1
    fi
fi
if [[ $submit_analyzer_name == "SKTreeMakerNoCut" ]];
    then
    submit_skinput="false"
    if [[ $submit_version_tag == "" ]];
        then
        echo "When running SKTreeMaker you need to specify the catversion: -c "
        exit 1
    fi
    
fi
if [[ $submit_analyzer_name == "SKTreeMakerDiLep" ]];
    then
    submit_skinput="true"
  if [[ $submit_version_tag == "" ]];
      then
      echo "When running SKTreeMaker you need to specify the catversion: -c "
      exit 1
  fi

fi


outputdir_cat=$LQANALYZER_DIR"/data/output/CAT/"
outputdir_analyzer=$LQANALYZER_DIR"/data/output/CAT/"$submit_analyzer_name
dir_tag="periodC/"

if [[  $job_cycle != "SKTreeMaker"* ]];
    then
    if [[ ! -d "${outputdir_cat}" ]]; then
	mkdir ${outputdir_cat}
	echo "Making " + ${outputdir_cat}
    fi
    if [[ ! -d "${outputdir_analyzer}" ]]; then
	mkdir ${outputdir_analyzer}
	echo "Making " + ${outputdir_analyzer}
    fi
    if [[ $job_data_lumi  == "CtoD" ]];
	then
	dir_tag="periodCtoD/"
    fi
fi

outputdir_mc=${outputdir_analyzer}"/"${dir_tag}
outputdir_data=${outputdir_mc}"/Data/"
echo $outputdir_data
output_datafile=${outputdir_mc}"/"$job_cycle"_data_cat"${submit_catversion}".root"
echo $output_datafile

if [[  $job_cycle != "SKTreeMaker"* ]];
    then

    if [[ ! -d "${outputdir_mc}" ]]; then
	mkdir ${outputdir_mc}
	echo "Making " + ${outputdir_mc}
    fi
    
    if [[ ! -d "${outputdir_data}" ]]; then
	mkdir ${outputdir_data}
	echo "Making " + ${outputdir_data}
    fi
fi

#function mergeData{
#    
#    if [[  $job_cycle != "SKTreeMaker"* ]];
#	then 
#	if [[  $job_data_lumi  != "C" ]];
#	    then
#	    source hadd.sh ${outputdir_data} ${job_cycle}_data_cat${submit_catversion}.root ${outputdir_data}/${job_cycle}*
#	    echo ${outputdir_data}"/"${job_cycle}"_data_cat"${submit_catversion}".root "
#	    mv  ${outputdir_data}/${job_cycle}_data_cat${submit_catversion}.root  ${outputdir_mc}
#	fi
#	if [[ $job_data_lumi  == "C" ]];
#	    then
#	    echo "Ran only period C"
#	    mv  ${outputdir_data}/*.root ${output_datafile}/${job_cycle}_data_cat${version_tag}.root
#	fi
#    fi
#    echo ""
#}



################ MUON DATA
### submit this configured job (uses bin/submit.sh)
if [[ $runDATA  == "true" ]];
    then
    ARG1=$submit_sampletag
    eval "streams=(\${$ARG1[@]})"
    for istream in ${streams[@]}: 
      do
      if [[ $istream == "" ]];
	  then
	  continue
      fi
      
      source functions.sh
      cycle=${job_cycle}
      skinput=${submit_skinput}
      useskim=${job_skim}
      njobs=$job_njobs
      data_lumi=$job_data_lumi
      loglevel=$job_loglevel
      logstep=$job_logstep
      stream=${istream}
      outputdir=${outputdir_data}
      catversion=${submit_version_tag}
    
      ARG=data_periods
      eval "input_samples=(\${$ARG[@]})"


      source submit.sh
      #mergeData
      
    done
fi


if [[ $runMC  == "true" ]];
    echo running mc
    echo submit_file_tag = $submit_file_tag
    echo submit_file_list = $submit_file_list
    then
    source functions.sh
    cycle=${job_cycle}
    skinput=${submit_skinput}
    useskim=${job_skim}
    njobs=$job_njobs
    data_lumi=$job_data_lumi
    loglevel=$job_loglevel
    logstep=$job_logstep
    outputdir=${outputdir_mc}
    catversion=${submit_version_tag}

    if [[ $submit_file_tag  != ""  ]];
        then
	
        declare -a input_samples=("${submit_file_tag}")
        echo $submit_file_tag running
	source submit.sh
    fi
        
    if [[ $submit_file_list  != ""  ]];
	then
	ARG=$submit_file_list
	eval "input_samples=(\${$ARG[@]})"
	source submit.sh
    fi
fi
