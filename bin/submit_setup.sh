#!/bin/sh
### sets all configurable variables to defaul values


function usage
{
    echo "usage: submitSKTree.sh [[[-a analyzer] [-S samples] [-f file_tag ] [-sktree usesktree ([-skim skim])] [-d debug_mode] [-c catversion] [-o outputdir] [-p data_period] ] | [-h][-l (catversion) (*search*)][-g (*search*)]]"
}

function rungroupedlist
{
    echo ""
    cat ${LQANALYZER_DIR}/LQRun/txt/list_all_mc.sh | while read line
      do
      if [[ $line == *"declare"* ]];
	  then
	  sline=$(echo $line | cut -d "" -f2-)
	  echo ${sline}
	  echo ""
      fi
    done
}

function runlist
{
    if [[ $submit_catvlist  == "" ]];
	then
	submit_catvlist=${CATVERSION}
    fi
    

    echo "Reading:" ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt 
    echo "Options for -s | --SampleTag are:"
    cat ${LQANALYZER_RUN_PATH}/txt/datasets_snu_CAT_mc_${submit_catvlist}.txt | while read line
      do
      if [[ $line == *"/data2/DATA/cattoflat/MC/"* ]];
	  then
	  sline=$(echo $line | head -n1 | awk '{print $1}')
	  if [[ $submit_searchlist == "" ]];
	      then
	      echo ${sline}
	  fi
	  if [[ $submit_searchlist != "" ]];
	      then
	      if [[ $sline == *${submit_searchlist}* ]];
		  then 
		  echo ${sline}
	      fi
	  fi
      fi
    done

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
        -f | --file_tag )       shift
                                submit_file_tag=$1
                                ;;
	-fl | --file_list )     shift
                                submit_file_list=$1
                                ;;
	
	-d | --debug_mode )     shift
	                        job_loglevel="$1"
                                ;;
        -p | --data_period )    shift
                                job_data_lumi="$1"
                                ;;
	-sktree | --usesktrees )shift
                                submit_skinput="$1"
                                ;;
        -s | --useskim )        shift
                                job_skim="$1"
                                ;;
	-n | --njobs )          shift
	                        job_njobs=$1
				;;
        
	-S | --SampleTag  )     shift
                                submit_sampletag=$1
                                ;;
	-c | --CatVersion)      shift
	                        submit_catversion=$1
				submit_version_tag=$1
				;;
	-l | --file_tag_list)   shift
	                        submit_catvlist=$1
				submit_searchlist=$2
	                        runlist
				exit 1
				;;
	-g | --file_tag_groups) shift
                                submit_catvlist=$1
                                submit_searchlist=$2
                                rungroupedlist
				exit 1
                                ;;

	-h | --help )           usage
	                        echo "Tag :   Options                                                                       | DEFAULT PARAMETER     | COMMENT           "
	                        echo "-a :    HNDiElectron/ExampleDiMuon                                                    | default = ''          | 'Name of analysis class'                "
	                        echo "-S :    ALL/DATA/MC/DoubleEG/DoubleMuon/MuonEG/SingeMuon/SinglePhoton/SingleElectron  | default = ''          | 'DATA runs ALL data. MC runs ALL MC (same as -fl all_mc''                "
                                echo "-sktree :   true/false or True/False                                                  | default=True          | 'Set False to run on CATuples, if True then also set -s/--useskim'               "
                                echo "-s :    NoCuts/Lepton/DiLepton                                                        | default=Lepton        | 'Set False to run on CATuples'               "
                                echo "-n :    #number of subjobs                                                            | default=30            | ''                "
				echo "-f :    file_tag (i.e., DY10to50_MCatNLO)                                             | default = ''          | 'For running single MC samples: For full list run bash script.sh  -l|--file_tag_list'"
				echo "-fl:    file_list (i.e., diboson_pythia,dy_mcatnlo)                                   | default = 'all_mc'    | 'For running on list of MC samples. For full list run bash script.sh  -g|--file_tag_groups'"
				echo "-c :    catversion of inputfile (only needed if not running default/latest)           | default = $CATVERSION |"
				echo "-d :    debug mode : INFO/DEBUG/WARNING                                               | default = INFO        |"
				echo "-p :    period to normalise to : C/D/CtoD(ALL)                                        | default = ALL         |"
				echo "-o :    setoutput directory. Does not work for SKTreeMaker Code.                      | default=$LQANALZER_DIR/data/output/CAT/{class}/periodX/  |"
				exit
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done


############################################################


declare -a streams=("")
declare -a mc_input=("")
declare -a data_periods=("")



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
    declare -a  streams=("DoubleMuon" "DoubleEG" "MuonEG" "SinglePhoton" "SingleElectron" "SingleMuon")
fi
if [[ $submit_sampletag  == "MC" ]];
    then
    runMC=true
    submit_file_list="all_mc"
    
fi

if [[ $submit_sampletag  == "DATA" ]];
    then
    runDATA=true
    declare -a  streams=("DoubleMuon" "DoubleEG" "MuonEG" "SinglePhoton" "SingleElectron" "SingleMuon")
fi    

if [[ $submit_sampletag  == "DoubleEG" ]];
    then
    runDATA=true
    declare -a streams=("DoubleEG")
fi

if [[ $submit_sampletag  == "DoubleMuon" ]];
    then
    runDATA=true
    declare -a streams=("DoubleMuon")
    
fi

if [[ $submit_sampletag  == "MuonEG" ]];
    then
    runDATA=true
    declare -a streams=("MuonEG")
    
fi

if [[ $submit_sampletag  == "SinglePhoton" ]];
    then
    runDATA=true
    declare -a streams=("SinglePhoton")
    
fi

if [[ $submit_sampletag  == "SingleElectron" ]];
    then
    runDATA=true
    declare -a streams=("SingleElectron")
fi

if [[ $submit_sampletag  == "SingleMuon" ]];
    then
    runDATA=true
    declare -a  streams=("SingleMuon")
fi



