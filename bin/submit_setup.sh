#!/bin/sh
### sets all configurable variables to defaul values

function usage
{

    echo "usage: sktree [-a analyzer] [-S samples] [-i input_file ]"
    echo "              [-s skim] [-list file_array] [-p data_period]"
    echo "              [-d debug_mode] [-c catversion] [-o outputdir] "
    echo "              [-h ][-l <args> ][-g <args>] [-A <args>]"
    
}



function rungroupedlist
{
    echo ""
    while read line
      do
      if [[ $line == *"declare"* ]];
	  then
	  sline=$(echo $line | cut -d "" -f2-)
	  echo ${sline}
	  echo ""
      fi
    done < ${LQANALYZER_DIR}/LQRun/txt/list_all_mc.sh
    
    echo ""
    echo "Arrays made by user"

    while read line
      do
      if [[ $line == *"declare"* ]];
          then
          sline=$(echo $line | cut -d "" -f2-)
          echo ${sline}
          echo ""
      fi
    done < ${LQANALYZER_DIR}/LQRun/txt/list_user_mc.sh

}

function getdatasetname
{
    
    while read line
      do
      if [[ $line == *"/data2/DATA/cattoflat/MC/"* ]];
          then

	  if [[ $line == *$submit_file_tag* ]];
	       then
	      sline=$(echo $line | head -n1 | awk '{print $6}')
	      echo ${sline}
	  fi
      fi
    done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${CATVERSION}.txt
    
}

function listavailable
{
    
    if [[ $submit_searchlist == *"v7"* ]];
        then
        tmp_submit_searchlist=$submit_catvlist
        tmp_submit_catvlist=$submit_searchlist
        submit_catvlist=$tmp_submit_catvlist
        submit_searchlist=$tmp_submit_searchlist
    fi
    if [[ $submit_catvlist != *"v7"* ]];
	then
	if [[ $submit_catvlist != "" ]];
	    then
	    tmp_submit_searchlist=$submit_catvlist
	    tmp_submit_catvlist=$submit_searchlist
	    submit_catvlist=$tmp_submit_catvlist
	    submit_searchlist=$tmp_submit_searchlist
	fi
    fi
    
    allowed_catversion=false
    for iac in  ${list_of_catversions[@]};
      do
      if [[ $iac == $submit_catvlist ]];
          then
          allowed_catversion=true
      fi
    done
    if [[ $allowed_catversion == "false" ]];
        then
        echo "Catversion " $submit_catvlist " is not allowed"
        exit 1
    fi


    specified_catversion=true
    if [[ $submit_catvlist  == "" ]];
        then
        submit_catvlist=${CATVERSION}
        specified_catversion=false
    fi
    
    echo ""
    echo "List of available samples at SNU. With catversion " ${submit_catvlist}
    echo ""
    echo "Samplename  --> datasetname"  
    while read line
      do
      if [[ $line == *"/data2/DATA/cattoflat/MC/"* ]];
	  then
	  if [[ $submit_searchlist == "" ]];
	      then
	      sline1=$(echo $line | head -n1 | awk '{print $1}')
	      sline2=$(echo $line | head -n1 | awk '{print $6}')
	      echo ${sline1} "--> "  ${sline2}
	  fi
	   if [[ $submit_searchlist != "" ]];
              then
	       if [[ $line == *${submit_searchlist}* ]];
		   then
		   sline1=$(echo $line | head -n1 | awk '{print $1}')
		   sline2=$(echo $line | head -n1 | awk '{print $6}')
		   echo ${sline1} "--> "  ${sline2}
	       fi
	   fi
      fi
    done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt
    echo ""
    echo ""
    echo ""
    echo "List of samples not available in latest available catversion are:"
    echo ""
    echo "Missing: since miniAOD not available"

    while read line
      do
      if [[ $line == *"Missing:"* ]];
	  then
	  sline=$(echo $line | head -n1 | awk '{print $2}')
	  if [[ $submit_searchlist == "" ]];
              then
	      echo ${sline}
	  fi
	  if [[ $submit_searchlist != "" ]];
	      then
	      if [[ $line == *${submit_searchlist}* ]];
		  then
		  echo ${sline}
	      fi
	  fi
      fi
    done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt
    echo ""
    echo ""
    echo ""
    echo "Catuples available at kisti: Can create flatcatuples->sktrees on request: type 'sktree -r datasetname' "

    while read line
      do
    if [[ $line == *"Available[not produced]"* ]];
	then
	sline=$(echo $line | head -n1 | awk '{print $3}')
	if [[ $submit_searchlist == "" ]];
	    then
	    echo ${sline}
	fi
	if [[ $submit_searchlist != "" ]];
	    then
	    if [[ $line == *${submit_searchlist}* ]];
		then
		echo ${sline}
	    fi
	fi
    fi
    done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt

    echo ""
    echo ""
    if [[ $specified_catversion == "true" ]];
	then
	echo "To check availability of SKTrees"
	echo "For No skim run 'sktree -L SKTree_NoSkim " ${submit_searchlist} ${submit_catvlist} "'" 
	echo "For Lepton skim run 'sktree -L SKTree_LeptonSkim " ${submit_searchlist} ${submit_catvlist} "'" 
	echo "For DiLepton skim run 'sktree -L SKTree_DiLepSkim " ${submit_searchlist} ${submit_catvlist} "'" 
	
    fi
    if [[ $specified_catversion != "true" ]];
        then
	echo "To check availability of SKTrees"
	echo "For No skim run 'sktree -L SKTree_NoSkim " ${submit_searchlist} "'"
	echo "For Lepton skim run 'sktree -L SKTree_LeptonSkim " ${submit_searchlist}  "'"
	echo "For DiLpton skim run 'sktree -L SKTree_DiLepSkim " ${submit_searchlist}  "'"
	
    fi

    
}




function sendrequest
{
    source mail.sh $request_sample
    cat email.txt | mail -s "SKTree request" jalmond@cern.ch
    rm email.txt
}

function runlist
{
    
    if [[ $submit_searchlist == *"v7"* ]];
	then
	tmp_submit_searchlist=$submit_catvlist
	tmp_submit_catvlist=$submit_searchlist
	submit_catvlist=$tmp_submit_catvlist
	submit_searchlist=$tmp_submit_searchlist
    fi
    if [[ $submit_catvlist != *"v7"* ]];
	then
        if [[ $submit_catvlist != "" ]];
            then
            tmp_submit_searchlist=$submit_catvlist
            tmp_submit_catvlist=$submit_searchlist
            submit_catvlist=$tmp_submit_catvlist
            submit_searchlist=$tmp_submit_searchlist
        fi
    fi
    
    allowed_catversion=false
    for iac in  ${list_of_catversions[@]};
      do
      if [[ $iac == $submit_catvlist ]];
	  then
	  allowed_catversion=true
      fi
    done
    if [[ $allowed_catversion == "false" ]];
	then
	echo "Catversion " $submit_catvlist " is not allowed"
	exit 1
    fi
    specified_catversion=true
    if [[ $submit_catvlist  == "" ]];
	then
	submit_catvlist=${CATVERSION}
	specified_catversion=false
    fi
    
    check_path=""
    
    if [[ $submit_skim  == "" ]];
        then
	echo "sktree -L <skim>"
	echo "Need to set skim: Options are FLATCAT/SKTree_NoSkim/SKTree_LeptonSkim/SKTree_DiLepSkim"
	echo "Can also specify catversion AND/OR search filter list (after skim)"
	echo "example 1) sktree -L FLATCAT"
	echo "example 2) sktree -L FLATCAT v7-6-3"
	echo "example 3) sktree -L SKTree_LeptonSkim QCD v7-6-2"
	echo "example 4) sktree -L SKTree_DiLepSkim v7-6-3 DY"
	exit 1
    fi
    if [[ $submit_skim  == "FLATCAT" ]];
        then
        check_path="/data2/DATA/cattoflat/MC/"
    fi
    
    if [[ $submit_skim  == "SKTree_NoSkim" ]];
	then
        check_path="/data2/CatNtuples/"${submit_catvlist}"/SKTrees/MCNoCut/"
    fi
    if [[ $submit_skim  == "SKTree_LeptonSkim" ]];
	then
	check_path="/data2/CatNtuples/"${submit_catvlist}"/SKTrees/MC/"
    fi
    if [[ $submit_skim  == "SKTree_DiLepSkim" ]];
	then
	check_path="/data2/CatNtuples/"${submit_catvlist}"/SKTrees/MCDiLep/"
    fi
    
    if [[ $check_path == "" ]];
	then
	echo "Invalid option for ntuple version: "
	echo "sktree -L <skim>"
        echo "Need to set ntuple version: Options are FLATCAT/SKTree_NoSkim/SKTree_LeptonSkim/SKTree_DiLepSkim"
	exit 1
    fi
    

    echo "For <skim>= " $submit_skim " run jobs with command:"
    
    echo "'sktree -a <analyzer/classname> -s " $submit_skim "  -i <proccesnames>':"
    echo ""
    echo "List of samplenames for skim " $submit_skim " available in cattuple version " $submit_catvlist " is:"
    
    declare -a LISTOFSAMPLES=()
    declare -a UNPROCESSED=()
    
    while read line
      do
      if [[ $line == *${check_path}* ]];
	  then
	  sline=$(echo $line | head -n1 | awk '{print $1}')
	  sline2=$(echo $line | head -n1 | awk '{print $6}')

	  if [[ $submit_searchlist == "" ]];
	      then
	      prefix="SK"
	      suffix="_dilep"
	      if [[ $sline == *${prefix}* ]];
		  then
		  sline=${sline:2}		  
	      fi
	      if [[ $sline == *${suffix}* ]];
                  then
		  sline=${sline%$suffix}
	      fi
	      
	      if [[ ! -d "${sline2}" ]]; then
		  UNPROCESSED+=(${sline})
	      elif test "$(ls -A "$sline2")"; then
		  echo ${sline}
		  LISTOFSAMPLES+=(${sline})
	      else
		  UNPROCESSED+=(${sline})
	      fi
	  fi
	  
	  if [[ $submit_searchlist != "" ]];
	      then
	      if [[ $sline == *${submit_searchlist}* ]];
		  then 
		  prefix="SK"
		  suffix="_dilep"
		  if [[ $sline == *${prefix}* ]];
		      then
		      sline=${sline:2}
		  fi
		  if [[ $sline == *${suffix}* ]];
		      then
		      sline=${sline%$suffix}
		  fi

		  if [[ ! -d "${sline2}" ]]; then
		      UNPROCESSED+=(${sline})
		  elif test "$(ls -A "$sline2")"; then
		      echo ${sline}
		      LISTOFSAMPLES+=(${sline})
		  else
		      UNPROCESSED+=(${sline})
		  fi
	      fi
	  fi
      fi
      
    done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt
    echo ""
    if [[ $submit_skim  == "SKTree_NoSkim" ]];
        then
	echo "Samples that have local flat catuples but no lepton skim are:"
	for il in  ${UNPROCESSED[@]};
	  do
	  echo samplename = $il
	done
	echo ""
	echo "If you want this sktree run 'sktree -a SKTreeMakerNoCut -i <samplename>' "
	echo ""
    fi
    if [[ $submit_skim  == "SKTree_LeptonSkim" ]];
        then
        echo "Samples that have local flat catuples but no lepton skim are:"
        for il in  ${UNPROCESSED[@]};
          do
          echo samplename = $il
        done
	echo ""
        echo "If you want this sktree run 'sktree -a SKTreeMaker -i <samplename>' "
        echo ""
    fi

    if [[ $submit_skim  == "SKTree_DiLepSkim" ]];
        then
	echo "Samples that have local flat catuples but no dilepton skim are:"
        for il in  ${UNPROCESSED[@]};
          do
          echo samplename = $il

        done
	echo ""
	echo "If you want this sktree run 'sktree -a SKTreeMakerDiLep -i <samplename>' "
	echo ""
    fi
    
    


    if [[ $specified_catversion == "false" ]];
	then
	#Get number of catversions
	for ic in  ${list_of_catversions[@]};
	  do

	  if [[ $ic == $CATVERSION ]];
	      then continue;
	  fi
	  if [[ $ic == *"v7-4"* ]];
	      then
	      echo "For catversion "  $ic " the naming changed. Run 'sktree -L " $submit_skim " " $ic "'"
	      continue;
          fi

	  echo "Following samples are available in Catversion: " ${ic} " but not in: " $CATVERSION

	  if [[ $submit_skim  == "SKTree_NoSkim" ]];
	      then
	      check_path="/data2/CatNtuples/"${ic}"/SKTrees/MCNoCut/"
	  fi
	  if [[ $submit_skim  == "SKTree_LeptonSkim" ]];
	      then
              check_path="/data2/CatNtuples/"${ic}"/SKTrees/MC/"
          fi
	  if [[ $submit_skim  == "SKTree_DiLepSkim" ]];
	      then
	      check_path="/data2/CatNtuples/"${ic}"/SKTrees/MCDiLep/"
	  fi

	  while read line
	    do
	    if [[ $line == *${check_path}* ]];
		then
		sline=$(echo $line | head -n1 | awk '{print $1}')
		sline2=$(echo $line | head -n1 | awk '{print $6}')

		if [[ $submit_searchlist == "" ]];
		    then
		    isDuplicate=false
		    for il in  ${LISTOFSAMPLES[@]};
		      do

		      if [[ $sline == *${il}* ]];
			  then
			  isDuplicate=true
		      fi
		    done
		    if [[ $isDuplicate == "false" ]];
			then
			prefix="SK"
			suffix="_dilep"
			if [[ $sline == *${prefix}* ]];
			    then
			    sline=${sline:2}
			fi
			if [[ $sline == *${suffix}* ]];
			    then
			    sline=${sline%$suffix}
			fi
			
			if [[ -d "${sline2}" ]]; then
			    if test "$(ls -A "$sline2")"; then
				echo ${sline}
				LISTOFSAMPLES+=(${sline})
			    fi
			fi
		    fi
		fi
		if [[ $submit_searchlist != "" ]];
		    then
		    isDuplicate=false
		    if [[ $sline == *${submit_searchlist}* ]];
			then
			for il in  ${LISTOFSAMPLES[@]};
			  do
			  if [[ $sline == *${il}* ]];
			      then
			      isDuplicate=true
			  fi
			done
			if [[ $isDuplicate == "false" ]];
			    then
			    prefix="SK"
			    suffix="_dilep"
			    if [[ $sline == *${prefix}* ]];
				then
				sline=${sline:2}
			    fi
			    if [[ $sline == *${suffix}* ]];
				then
				sline=${sline%$suffix}
			    fi
			    if [[  -d "${sline2}" ]]; then
				
				if test "$(ls -A "$sline2")"; then
				    echo ${sline}
				    LISTOFSAMPLES+=(${sline})
				fi
			    fi
			fi
		    fi
		fi
	    fi
	  done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${ic}.txt
	done
      fi

}				
    

while [ "$1" == "" ]; do
    usage
    exit
done

while [ "$1" != "" ]; do
    
    case $1 in
        -a | --analysis_name )  shift
                                submit_analyzer_name=$1
				;;
        -i | --input )          shift
                                submit_file_tag=$1
                                ;;
	-list | --inputlist )   shift
                                submit_file_list=$1
                                ;;
	
	-d | --debug_mode )     shift
	                        job_loglevel="$1"
				changed_job_loglevel=true
                                ;;
        -p | --data_period )    shift
                                job_data_lumi="$1"
				changed_job_data_lumi=true
                                ;;
#	-sktree | --usesktrees )shift
#                                submit_skinput="$1"
#				changed_skinput=true
#                                ;;
        -s | --useskim )        shift
                                job_skim="$1"
				changed_skim=true
                                ;;
	-n | --njobs )          shift
	                        job_njobs=$1
				changed_job_njobs=true
				;;
        -r | --requestSKtree )  shift
	                        request_sample=$1
	                        sendrequest
				exit 1
                                ;;        
	-S | --SampleTag  )     shift
                                submit_sampletag=$1
                                ;;
	-c | --CatVersion)      shift
				submit_version_tag="$1"
				;;
	-l | --file_tag_list)   shift
				submit_skim="FLATCAT"
				submit_searchlist=$1
				submit_catvlist=$2
	                        runlist
				exit 1
				;;
        -L | --sktree_tag_list) shift
                                submit_skim=$1
                                submit_searchlist=$2
				submit_catvlist=$3
                                runlist
                                exit 1
                                ;;

        -A | --AvailableCatuples) shift
	                        submit_catvlist=$1
				submit_searchlist=$2
				listavailable
                                exit 1
                                ;;


	-dataset | --GetDataSetName)  shift
                            	submit_file_tag=$1
				getdatasetname
				exit 1
				;;
        -o | --output)          shift
	                        job_output_dir=$1
				changed_job_output_dir=true
                                ;;


	-g | --file_tag_groups) shift
                                submit_catvlist=$1
                                submit_searchlist=$2
                                rungroupedlist
				exit 1
                                ;;

	-h | --help )        	shift
	                        usage
                         	other_commands=$1 
				if [[ $other_commands == "" ]];
				    then
				    echo "###########################Running command##################################################################################"
				    echo "Tag    |   Options                                            | DEFAULT PARAMETER   | COMMENT                             | "
				    echo "__________________________________________________________________________________________________________________________|"
				    echo "       |                                                      |                     |                                     |"
				    echo "-a     |   HNDiElectron/ExampleDiMuon/etc                     | default = ''        | Name of analysis class              |"
				    echo "       |   'sktree -a' lists options                          |                     |                                     |"
				    echo "       |                                                      |                     |                                     |"
				    echo "-S     |   ALL/DATA/MC/DoubleEG/DoubleMuon/                   | default = ''        | 'DATA' runs every data dataset.     |"
				    echo "       |   MuonEG/SingeMuon/SinglePhoton/SingleElectron       |                     | 'MC' runs every MC sample           |"
				    echo "       |                                                      |                     |                                     |"
				    echo "-s     |   SKTree_NoSkim/SKTree_LeptonSkim/SKTree_DiLepSkim   | default='Lepton'    | Sets skim to use:                   | "
				    echo "       |   FLATCAT sets input to flatcatuple not sktee        |                     | NoCuts/Lepton/DiLeptonstill work    | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-n     |   #number of subjobs  (any number < 15)              | default=15          | default is 5 is -sktree=False       | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-i     |   (i.e., DY10to50_MCatNLO) run 'sktree -L' for more  | default = ''        | For running single MC samples:      | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-list  |   (i.e., diboson_pythia) run 'sktree -g' for more    | default = ''        | For running on list of MC samples.  | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-c     |   catversion of inputfile atest)                     | default = ${CATVERSION}    | (only needed if not running         | "
				    echo "       |                                                      |                     | default/latest)                     | " 
				    echo "-d     |   debug mode : INFO/DEBUG/WARNING                    | default = INFO      |                                     | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-p     |   period to run in data/normalise inMC: C/D/CtoD(ALL)| default = CtoD      | Only change if you wish to run      | "
				    echo "       |                                                      |                     | on a single data period             | "
				    echo "       |                                                      |                     |                                     |"
				    echo "-o     |   setoutput directory.                               | default= ''         | Does not work for SKTreeMaker Code. |"
				    echo ""
				    echo "Run 'sktree -h all' for more commands"
				fi

				if [[ $other_commands == "all" ]];
	  			    then
				    echo "###########################Other command#####################################################################################"
				    echo "Tag    |   Options                                            | DEFAULT PARAMETER   | COMMENT                             | "
				    
				    echo "__________________________________________________________________________________________________________________________|"
				    echo "-l       | (can give search/catversion as an option )         | default = ''        | returns a list of available         | "
				    echo "         | i.e.  sktree -l QCD  OR  sktree -l DY v7-6-3       |                     | datasets in each catversion         |"
				    echo "-L       | can give search/skim/catversion as on option)      | default = ''        | returns a list of available         | "
				    echo "         | use like 'sktree -L DiLep QCD                      |                     | sktrees  in each catversion         |" 
				    echo "         |                                                    |                     |                                     |"
				    echo "-g       |                                                    | default = ''        | returns a list of available input   |"
				    echo "         |                                                    |                     | arrays to input with:               |"
				    echo "         |                                                    |                     | sktree -list command                |" 
				    echo "-dataset | file_tag (i.e., DY10to50_MCatNLO)                  | default = ''        | returns datasetname.                |"
				    echo "         |                                                    |                     | Only available from v7-6-3          |"  
				    echo "-r       | sktree -A to see possible samples                  | default = ''        | sends email request to make sktree  |"
				    echo "         |                                                    |                     | that is not current available at snu|"
				    echo "         |                                                    |                     |                                     |"
				    echo "-A       | can speficy catversion and search                  | default = ${CATVERSION}    | lists missing samples due to no     |"
				    echo "         |                                                    |                     | MiniAOD and available samples       |"
				    echo "         |                                                    |                     | that can be processed               |"        
				    
				fi
				exit
                                ;;
        * )                     usage
	exit 1
    esac
    shift
done


############################################################


if [[ $submit_analyzer_name ==  "" ]];
    then
    echo "No analyzer set: set with -a"
    echo "List of Classes are:"
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


#declare -a streams=("")
declare -a data_periods=("")
declare -a ALL=("DoubleMuon" "DoubleEG" "MuonEG" "SinglePhoton" "SingleElectron" "SingleMuon")


if [[ $job_data_lumi == "ALL" ]];
    then
    declare -a data_periods=("C" "D")
fi
if [[ $job_data_lumi == "CtoD" ]];
    then
    declare -a data_periods=("C" "D")
fi
if [[ $job_data_lumi == "C" ]];
    then
    declare -a data_periods=("C")
fi
if [[ $job_data_lumi == "D" ]];
    then
    declare -a data_periods=("D")
fi


if [[ $submit_file_tag  != "" ]];
    then
    runMC=true
fi


if [[ $submit_file_list  != "" ]];
    then
    runMC=true
fi


if [[ $submit_sampletag  == "ALL" ]];
    then
    runMC=true
    submit_file_list="all_mc"
    runDATA=true
fi
if [[ $submit_sampletag  == "MC" ]];
    then
    runMC=true
    submit_file_list="all_mc"

fi

declare -a  DATA=("DoubleMuon" "DoubleEG" "MuonEG" "SinglePhoton" "SingleElectron" "SingleMuon")
if [[ $submit_sampletag  == "DATA" ]];
    then
    runDATA=true
fi    
declare -a  DATADILEP=("DoubleMuon" "DoubleEG" "MuonEG")
if [[ $submit_sampletag  == "DATADILEP" ]];
    then
    runDATA=true
fi



declare -a DoubleEG=("DoubleEG")

if [[ $submit_sampletag  == "DoubleEG" ]];
    then
    runDATA=true
fi

declare -a DoubleMuon=("DoubleMuon")
if [[ $submit_sampletag  == "DoubleMuon" ]];
    then
    runDATA=true
fi

declare -a MuonEG=("MuonEG")
if [[ $submit_sampletag  == "MuonEG" ]];
    then
    runDATA=true
    
fi

declare -a SinglePhoton=("SinglePhoton")
if [[ $submit_sampletag  == "SinglePhoton" ]];
    then
    runDATA=true
fi

declare -a SingleElectron=("SingleElectron")

if [[ $submit_sampletag  == "SingleElectron" ]];
    then
    runDATA=true
fi

declare -a SingleMuon=("SingleMuon")

if [[ $submit_sampletag  == "SingleMuon" ]];
    then
    runDATA=true
fi


declare -a FULLLISTOFSAMPLES=()

for iclist in  ${list_of_catversions[@]};
  do
  
  if [[ $iclist == *"v7-4"* ]];
      then
      continue;
  fi
  
  while read line
    do
    if [[ $line == *"/data2/DATA/cattoflat/MC/"* ]];
	then
	sline=$(echo $line | head -n1 | awk '{print $1}')
	
	isDuplicate=false
	for il in  ${FULLLISTOFSAMPLES[@]};
	  do
	  if [[ $sline == $il ]];
	      then
	      isDuplicate=true
	  fi
	done
	if [[ $isDuplicate == "false" ]];
	    then
	    FULLLISTOFSAMPLES+=(${sline})
	fi
    fi
  done < ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${iclist}.txt

done