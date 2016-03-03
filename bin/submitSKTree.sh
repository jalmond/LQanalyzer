#!/bin/sh
### sets all configurable variables to defaul values

declare -a list_of_catversions=("v7-6-3" "v7-6-2" "v7-4-5" "v7-4-4")



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
job_njobs=15
job_skim="SKTree_LeptonSkim"
changed_skim=false
job_output_dir=""

submit_skinput="true"
changed_skinput=false
submit_version_tag=""
submit_file_tag=""
submit_file_list=""
submit_catversion=${CATVERSION}
submit_sampletag=""
submit_catvlist=""
submit_searchlist=""
submit_analyzer_name=""
request_sample=""

### Get predefined lists
source ${LQANALYZER_DIR}/LQRun/txt/list_all_mc.sh
### setup list of samples and other useful functions
source submit_setup.sh



if [[ $submit_analyzer_name !=  "" ]];
    then
    analyzer_found=false
    while read line
      do
      if [[ $line == *"C++ class"* ]];
          then
          if [[ $line != *"AnalyzerCore"* ]];
              then
              sline=$(echo $line | head -n1 | awk '{print $5}')
              suffix="+;"
              sline=${sline%$suffix}
              if [[ $sline == $submit_analyzer_name ]];
		  then
		  analyzer_found=true
	      fi
          fi
      fi
    done < ${LQANALYZER_DIR}"/LQAnalysis/include/LQAnalysis_LinkDef.h"
    
    if [[ $analyzer_found == "false" ]];
	then 
	echo ""
	echo "LQanalyzer::sktree :: ERROR :: Analyzer is invalid: 'sktree -a <analyzer/class>'"
	echo "Allowed Analyzers are:"
	while read line
	  do
	  if [[ $line == *"C++ class"* ]];
	      then
	      if [[ $line != *"AnalyzerCore"* ]];
		  then
		  sline=$(echo $line | head -n1 | awk '{print $5}')
		  suffix="+;"
		  sline=${sline%$suffix}
		  echo $sline
	      fi
	  fi
	done < ${LQANALYZER_DIR}"/LQAnalysis/include/LQAnalysis_LinkDef.h"
	exit 1
    fi
fi



if [[ $submit_file_tag  != ""  ]];
    then
    ARG_SINGLE_FILE="FULLLISTOFSAMPLES"
    eval test_single_file=(\${$ARG_SINGLE_FILE[@]})
    file_tag_exists=false
    for all_files in ${test_single_file[@]};
      do
      if [[ $all_files == $submit_file_tag ]];
	  then
	  file_tag_exists=true
      fi
      done
    if [[ $file_tag_exists == "false" ]];
	then
	echo "Samplename is Invalid 'sktree -i <samplename>'"
	echo "Check options using 'sktree -l' "
	exit 1
    fi
    
    if [[ $submit_file_list  != ""  ]];
	then
	echo "Running with 'sktree -i and -list is not valid'"
	echo "Remove one of these options"
	exit 1
    fi
    if [[ $submit_sampletag != ""  ]];
	then
	echo "Running with 'sktree -i and -S is not valid'"
	 echo "Remove one of these options"
        exit 1
    fi
	
fi

if [[ $submit_file_tag  == ""  ]];
    then
    if [[ $submit_file_list  == ""  ]];
	then
	if [[ $submit_sampletag == ""  ]];
            then
            echo "No input files were specified"
	    echo "Use either:"
	    echo "sktree -S <SAMPLELIST>   : run 'sktree -h' for list of options"
	    echo "sktree -i <SAMPLENAME>     : run 'sktree -l' or 'sktree -L' for list of options "
	    echo "sktree -list <SAMPLEARRAY> : run 'sktree -g' for list of options  "
            exit 1
        fi

    fi
fi


    
if [[ $submit_file_list  != ""  ]];
    then

    ARGTEST=$submit_file_list
    eval test_array=(\${$ARGTEST[@]})
    array_exists=false
    counter=${#test_array[@]}
	if [[ $counter -eq 0 ]];
            then
	    echo "Input list is invalid: 'sktree -list list'"
	    echo "Check lists using 'sktree -g'"
	    exit 1
	fi

	if [[ $submit_file_tag  != ""  ]];
	    then
	    echo "Running with 'sktree -i and -list is not valid'"
	    echo "Remove one of these options"
	    exit 1
	fi
	if [[ $submit_sampletag != ""  ]];
	    then
	    echo "Running with 'sktree -list and -S is not valid'"
	    echo "Remove one of these options"
	    exit 1
	fi
	
fi

if [[ $submit_sampletag  != ""  ]];
    then
    ARGTEST2=$submit_sampletag
    eval teststreams=(\${$ARGTEST2[@]})
    
    counter=${#teststreams[@]} 
	if [[ $counter -eq 0 ]];
	    then
	    echo "Input list is invalid: 'sktree -S samples'"
	    echo "run 'sktree -h' for options"
	    exit 1
    fi
	
	if [[ $submit_file_tag  != ""  ]];
            then
            echo "Running with 'sktree -i and -S is not valid'"
            echo "Remove one of these options"
            exit 1
        fi
        if [[ $submit_file_list != ""  ]];
            then
            echo "Running with 'sktree -list and -S is not valid'"
            echo "Remove one of these options"
            exit 1
        fi

fi


## RUN PARAMETERS
job_cycle="$submit_analyzer_name"

if [[ $submit_analyzer_name == "" ]];
    then
    echo "Need to set submit_analyzer_name: use 'sktree -a <analyzer/classname>' when submitting"
    exit 1
fi



#### HARDCODE the skinput for sktreemakers
if [[ $submit_analyzer_name == "SKTreeMaker" ]];
    then 
    submit_skinput="false"
    job_skim="FLATCAT"
    
    job_njobs=30
    if [[ $submit_version_tag == "" ]];
	then 
	echo "When running SKTreeMaker you need to specify the catversion: -c "
	echo "Options are: "
	for ic in  ${list_of_catversions[@]};
	  do
	  echo $ic
	done
	exit 1
    fi
fi
if [[ $submit_analyzer_name == "SKTreeMakerNoCut" ]];
    then
    submit_skinput="false"
    job_skim="FLATCAT"
    
    job_njobs=30
    if [[ $submit_version_tag == "" ]];
        then
        echo "When running SKTreeMaker you need to specify the catversion: -c "
	echo "Options are: "
	for ic in  ${list_of_catversions[@]};
          do
          echo $ic
        done

        exit 1
    fi
    
fi

if [[ $submit_analyzer_name == "SKTreeMakerDiLep" ]];
    then
    submit_skinput="true"
    job_skim="SKTree_LeptonSkim"
    job_njobs=30
  if [[ $submit_version_tag == "" ]];
      then
      echo "When running SKTreeMaker you need to specify the catversion: -c "
      echo "Options are: "
      for ic in  ${list_of_catversions[@]};
	do
	echo $ic
      done
      
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
    fi
    if [[ ! -d "${outputdir_analyzer}" ]]; then
	mkdir ${outputdir_analyzer}
    fi
    if [[ $job_data_lumi  == "CtoD" ]];
	then
	dir_tag="periodCtoD/"
    fi
fi

outputdir_mc=${outputdir_analyzer}"/"${dir_tag}
outputdir_data=${outputdir_mc}"/Data/"

if [[ $job_output_dir == "" ]]
    then
    if [[ $runDATA  == "true" ]];
	then
	job_output_dir=$outputdir_data
    fi
    if [[ $runMC  == "true" ]];
	then
	job_output_dir=$outputdir_mc
    fi
fi
output_datafile=${outputdir_mc}"/"$job_cycle"_data_cat"${submit_catversion}".root"

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
     if [[ ! -d "${job_output_dir}" ]]; then
	 mkdir ${job_output_dir}
	 echo "Making " + ${job_output_dir}
    fi

fi


if [[ $runDATA  == "true" ]];
    then
    ARGPERIOD=data_periods
    eval array_dataperiods=(\${$ARGPERIOD[@]})
    counter=${#array_dataperiods[@]}
	if [[ $counter -eq 0 ]];
            then
	    echo "Number of periods == 0"
	    echo "Problem with initialising 'sktree -p'" 
            exit 1
        fi
	if [[ $counter -gt 2 ]];
            then
	    echo "Number of periods > 2"
            echo "Problem with initialising 'sktree -p'"
            exit 1
        fi
	
fi

if [[ $changed_skim == "true" ]];
    then
    
    if [[ $changed_skinput  == "true" ]];
	then
	
	if [[ $submit_skinput == "false" ]];
	    then
	    if [[ $job_skim != *"CAT"* ]];
		then 
		echo "LQanalyzer::sktree :: ERROR :: Invalid skim -s <skim> is set when -sktree <false> is also set. run 'sktree -h' for options "
		exit 1
	    fi
	else
	    if [[ $job_skim == *"CAT"* ]];
		then
		echo "LQanalyzer::sktree :: ERROR :: Invalid skim -s <skim> is set when -sktree <true> is also set. run 'sktree -h' for options "
		exit 1
	    fi
	    
	fi
	
    fi
    if [[ $changed_skinput  != "true" ]];
	then
	if [[ $job_skim == "FLATCAT" ]];
	    then
	    submit_skinput=false
	else
	    submit_skinput=true
	fi
    fi
    
fi

if [[ $changed_skim != "true" ]];
    then
    if [[ $changed_skinput  == "true" ]];
	then
	if [[ $submit_skinput == "false" ]];
	    then
	    job_skim="FLATCAT"
	fi
    fi
fi


if [[ $job_skim == "FLATCAT" ]];
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to " $job_skim
    if [[ $submit_skinput == "true" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set to FLATCAT: Yet you set -sktree <true>"
	echo "Fix submission"
	exit 1
    fi
    
elif [[ $job_skim == "SKTree_NoSkim" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to " $job_skim
    if [[ $submit_skinput == "false" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to SKTree_NoSkim: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
elif [[ $job_skim == "SKTree_LeptonSkim" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to " $job_skim
    if [[ $submit_skinput == "false" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to SKTree_LeptonSkim: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
elif [[ $job_skim == "SKTree_DiLepSkim" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to " $job_skim
    if [[ $submit_skinput == "false" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to SKTree_DiLepSkim: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
elif [[ $job_skim == "NoCut" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to "$job_skim
    if [[ $submit_skinput == "false" ]];
                then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to NoCut: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
	
elif [[ $job_skim == "Lepton" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to "$job_skim
    if [[ $submit_skinput == "false" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to Lepton: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
    elif [[ $job_skim == "DiLep" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: Skim set to "$job_skim
    if [[ $submit_skinput == "false" ]];
	then
	echo "LQanalyzer::sktree :: ERROR :: skim set  to DiLep: Yet you set -sktree <false>"
	echo "Fix submission"
	exit 1
    fi
    
else
    echo "LQanalyzer::sktree :: ERROR :: Invalid skim is set. run 'sktree -h' for options "
    exit 1
fi
    
if [[ $runMC  == "true" ]];
    then
    if [[ $job_data_lumi == "C" ]];
	then
	if [[ $job_cycle != *"SKTreeMaker"* ]];
	    then
	    echo "LQanalyzer::sktree :: INFO :: Running on MC: target lumi set to 13 TeV periods  "  $job_data_lumi
	fi
    elif [[ $job_data_lumi == "D" ]]
	then
	if [[ $job_cycle != *"SKTreeMaker"* ]];
	    then
            echo "LQanalyzer::sktree :: INFO :: Running on MC: target lumi set to 13 TeV periods  "  $job_data_lumi
        fi
	
    elif [[ $job_data_lumi == "CtoD" ]]
	then
	if [[ $job_cycle != *"SKTreeMaker"* ]];
	    then
            echo "LQanalyzer::sktree :: INFO :: Running on MC: target lumi set to 13 TeV periods  "  $job_data_lumi
        fi
	
    elif [[ $job_data_lumi == "ALL" ]]
	then
	if [[ $job_cycle != *"SKTreeMaker"* ]];
	    then
            echo "LQanalyzer::sktree :: INFO :: Running on MC: target lumi set to 13 TeV periods  "  $job_data_lumi
        fi
    else
	echo "LQanalyzer::sktree :: ERROR :: Invalid setting for data lumi: sktree -p"
        exit 1
    fi
fi

if [[ $submit_skinput == "true" ]];
    then
    echo "LQanalyzer::sktree :: INFO :: SKTree input set to " $submit_skinput
    
elif [[ $submit_skinput == "True" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: SKTree input set to "  $submit_skinput
elif [[ $submit_skinput == "false" ]]
        then
    echo "LQanalyzer::sktree :: INFO :: SKTree input set to " $submit_skinput
elif [[ $submit_skinput == "False" ]]
    then
    echo "LQanalyzer::sktree :: INFO :: SKTree input set to " $submit_skinput
else
    echo "LQanalyzer::sktree :: ERROR :: Invalid setting for sktree_input: sktree -sktree (run 'sktree -h' for options)"
    exit 1
fi

if [[ $job_loglevel != "ERROR" ]]
    then
    if [[ $job_loglevel != "WARNING" ]]
	then
	if [[ $job_loglevel != "INFO" ]]
	    then
	    echo "LQanalyzer::sktree :: ERROR :: loglevel = " $job_loglevel
	    echo "This is invalid"
	    exit 1
	fi
    fi
fi
if [[ $runDATA  == "true" ]];
    then
    if [[ $submit_file_list  != ""  ]];
	then
	echo "Running on data"
	echo "ARRAY of files specified with sktree -list: This is not allowed for data"
	exit 1
    fi
fi

echo "LQanalyzer::sktree :: INFO :: Analyzer = " $job_cycle
echo "LQanalyzer::sktree :: INFO :: Number of subjobs = " $job_njobs  
echo "LQanalyzer::sktree :: INFO :: loglevel = " $job_loglevel

if [[ $submit_version_tag == *"v7"* ]];
    then
    if [[ $submit_skinput == "true" ]];
	then

        echo "Catversion for sktrees = " $submit_version_tag
    elif [[ $submit_skinput == "false" ]]
        then
        echo "LQanalyzer::sktree :: INFO :: Catversion for flat catuples  = " $submit_version_tag
    fi
else
    if [[ $submit_version_tag != ""  ]];
        then
	echo "LQanalyzer::sktree :: ERROR :: Invalid entry for catversion"
	exit 1
    fi
fi

if [[ $runMC  == "true" ]];
    then

    if [[ $submit_file_tag  != ""  ]];
      then
        echo "LQanalyzer::sktree :: INFO :: Single File to process = " $submit_file_tag  
    fi
    if [[ $submit_file_list  != ""  ]];
	then
        ARGOUT=$submit_file_list
        eval out_input_samples=(\${$ARGOUT[@]})
	 echo "LQanalyzer::sktree :: INFO :: ARRAY of samples  to process = " ${out_input_samples[*]}
    fi
    
fi

if [[ $runDATA  == "true" ]];
    then
    if [[ $submit_sampletag  != ""  ]];
	then
	ARGDATA=$submit_sampletag
	eval out_streams=(\${$ARGDATA[@]})
	echo "LQanalyzer::sktree :: INFO :: ARRAY of samples  to process = " ${out_streams[*]}
    fi
    
    ARGPERIOD=data_periods
    eval array_dataperiods=(\${$ARGPERIOD[@]})
    echo "LQanalyzer::sktree :: INFO :: Periods to be processed = " ${array_dataperiods[*]}
	
fi


echo "LQanalyzer::sktree :: INFO :: output directory = " ${job_output_dir}


################  DATA################################################
### submit this configured job (uses bin/submit.sh)
######################################################################
if [[ $runDATA  == "true" ]];
    then
        

    ARG1=$submit_sampletag
    eval streams=(\${$ARG1[@]})
    for istream in ${streams[@]};
      do
      echo "LQanalyzer::sktree :: INFO :: stream = " $istream

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
      outputdir=${job_output_dir}
      catversion=${submit_version_tag}
    
      ARG=data_periods
      eval input_samples=(\${$ARG[@]})

      
      source submit.sh
      mergeoutput
      
    done
fi


if [[ $runMC  == "true" ]];

    then
    source functions.sh
    cycle=${job_cycle}
    skinput=${submit_skinput}
    useskim=${job_skim}
    njobs=$job_njobs
    data_lumi=$job_data_lumi
    loglevel=$job_loglevel
    logstep=$job_logstep
    outputdir=${job_output_dir}
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
	eval input_samples=(\${$ARG[@]})
	source submit.sh
    fi
fi

function mergeoutput
{
    if [[ $job_cycle == *"SKTreeMaker"* ]];
	then
	
	if [[ $job_data_lumi  == "C" ]];
	    then
            mv  ${outputdir_data}/*.root ${output_datafile}/${job_cycle}_data_cat${version_tag}.root
	    
	    
	elif [[ $job_data_lumi  == "D" ]];
	    then
	    mv  ${outputdir_data}/*.root ${output_datafile}/${job_cycle}_data_cat${version_tag}.root
	    
	else
            echo "source hadd.sh " ${outputdir_data} " " ${job_cycle} "_data_cat"${submit_catversion}".root "${outputdir_data}"/"${job_cycle}"*"
            source hadd.sh ${outputdir_data} ${job_cycle}_data_cat${submit_catversion}.root ${outputdir_data}/${job_cycle}*
            echo ${outputdir_data}"/"${job_cycle}"_data_cat"${submit_catversion}".root "
            mv  ${outputdir_data}/${job_cycle}_data_cat${submit_catversion}.root  ${outputdir_mc}
	    echo ""
	fi
    fi
    
}


