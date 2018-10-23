#! /bin/sh
# $Id: setup.sh 1 01/12/2013 jalmond $
###################################################################################
# @Project: LQAnalyzer/SKTree - ROOT-based analysis framework for Korea CMS group #
#                                                                                 #
# @author John Almond       <jalmond@cern.ch>           - SNU                     #
#                                                                                 #
# Script that has to be sourced before compiling/running SFrame.                  #
#                                                                                 #
##################################################################################

# Greet the user

echo "Setting up environment for compiling/running CATAnalzer with SKTree"

setupok=False

function killbkg {
    python $LQANALYSER_DIR/python/killbkg.py -i $1
}


while read line
  do
  if [[ $line == *"LANG"* ]]; then
      setupok=True
  fi
done < ~/.bash_profile

if [[ $setupok == "False" ]]; then
    echo "Please add the following lines to ~/.bash_profile file:"
    echo 'LANG="en_US.utf-8"'
    echo 'LC_COLLATE="lt_LT.utf-8"'
    echo 'LC_TIME="en_DK.utf-8"'
    return 1
fi


if [[ $USER == "jalmond" ]]; then
    alias cat_path_analysis_ls='ll -rth /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/ '
    if [ $LQANALYZER_DIR ]; then
	echo "Running on batch"
    fi
    function cat_path_analysis_ls {
        ll -rth  /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/${1}
    }
    function cat_path_analysis {
	cd /data2/CAT_SKTreeOutput/JobOutPut/jalmond/LQanalyzer/data/output/CAT/HNDiLepton/periodBtoH/${1}
    }
fi



if [ $LQANALYZER_DIR ]; then
    echo LQANALYZER_DIR is already defined, use a clean shell
    return 1
fi


if [ $HOSTNAME == "ui10.sdfarm.kr" ];
then

    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%    Working on KISTI               %%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
    echo "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"


    export LQANALYZER_DIR=${PWD}

    export CMS_PATH=/cvmfs/cms.cern.ch
    source $CMS_PATH/cmsset_default.sh
    export SCRAM_ARCH=slc6_amd64_gcc630
    cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
    eval `scramv1 runtime -sh`
    echo " "
    echo "Working directory: "
    cd -
    source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh
    echo " "
    cd $LQANALYZER_DIR

else

    echo "Working on 42cluster"

    export CMS_PATH=/cvmfs/cms.cern.ch
    source $CMS_PATH/cmsset_default.sh
    export SCRAM_ARCH=slc6_amd64_gcc630
    cd /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/src/
    eval `scramv1 runtime -sh`
    cd -
    source /cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_9_4_4/external/slc6_amd64_gcc630/bin/thisroot.sh
    
fi    


# speficy the LQANALYZER_DIR base directory, i.e., the directory in which this file lives
export LQANALYZER_DIR=${PWD}


export LQANALYZER_MOD="/data1/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    export LQANALYZER_MOD="/data2/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
fi

if [ $HOSTNAME == "ui10.sdfarm.kr" ];
then
    export LQANALYZER_MOD="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATMOD/"
fi

python ${LQANALYZER_DIR}/scripts/CheckEmailIsSetup.py
cat_email="NULL"
while read line
do
    prefix="email = "
    if [[ $line == $prefix* ]];
    then
        line=${line:${#prefix}}
        cat_email=$line
    fi
done < ${LQANALYZER_DIR}/bin/catconfig
if [[ $cat_email  == "NULL" ]];
then
    echo "Email not setup. run setup.sh again"
    export LQANALYZER_DIR=""
    return 1
fi

##### Check that this is not the branch and a tag was checked out

export CHECKTAGFILE=$LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh
source $CHECKTAGFILE Tag

source $LQANALYZER_DIR/bin/CheckTag.sh


#### check for buggy tags 
buglist=/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/BuggyTag.txt
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    buglist=/data2/LQAnalyzer_rootfiles_for_analysis/CATTag/BuggyTag.txt
else
    buglist=/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATTag/BuggyTag.txt
fi

while read line
do
    if [[ $line == $CATTAG* ]];
    then
	echo "Current tag is buggy. Please update to newer tag."
        exit
    fi
done < $buglist


export LIBTAG=""
if [[ $1 != "" ]];then

    export CHECKTAGFILE=/data1/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
    then
	export CHECKTAGFILE=/data2/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    else
	export CHECKTAGFILE=/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/SetBrachAndTag_$1.sh
    fi
    if [[ ! -f $CHECKTAGFILE ]]; then
	export LQANALYZER_DIR=""
        echo $1 "is not allowed input. Use one of:"
	
	if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
	then
            source /data2/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh
	elif [ $HOSTNAME == "ui10.sdfarm.kr" ];
	then
	    source /cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh
	else
	    source /data1/LQAnalyzer_rootfiles_for_analysis/CattupleConfig/$CATVERSION.sh

	fi
        for ic in  ${list_of_catversions[@]};
        do
            echo $ic
	done
        return 1
    fi
    
    source $CHECKTAGFILE Tag
    export LIBTAG=$CATVERSION
fi

export yeartag="80X/"



### setup alias for using analyzer


alias cathistcounter="source scripts/Counter.sh "
alias catcutflowcounter="source scripts/CutFlow.sh "
alias sktree="bash submitSKTree.sh"
alias sktreemaker="bash submitSKTree.sh -M True "
alias sktree_val="bash submitSKTree.sh -V True "
alias sktree_bkg="nohup bash submitSKTree.sh -b True "
alias new_git_tag="bash "$LQANALYZER_DIR"/scripts/setup/git_newtag.sh"
alias git_commit_lq="bash scripts/setup/git_commit.sh"
alias sktree_bkg_log="python python/PrintBkgJob.py"

export LQANALYZER_FILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
export LQANALYZER_DATASETFILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
export LQANALYZER_DATASET_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/"
export LQANALYZER_SKTreeLOG_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
export CATTAGDIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/"
if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    export LQANALYZER_FILE_DIR="/data2/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
    export LQANALYZER_DATASETFILE_DIR="/data2/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
    export LQANALYZER_DATASET_DIR="/data2/LQAnalyzer_rootfiles_for_analysis/DataSetLists/"
    export LQANALYZER_SKTreeLOG_DIR="/data2/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
    export CATTAGDIR="/data2/LQAnalyzer_rootfiles_for_analysis/CATTag/"
else
    export LQANALYZER_FILE_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
    export LQANALYZER_DATASETFILE_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
    export LQANALYZER_DATASET_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/DataSetLists/"
    export LQANALYZER_SKTreeLOG_DIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
    export CATTAGDIR="/cms/scratch/SNU/CATAnalyzer/LQAnalyzer_rootfiles_for_analysis/CATTag/"
fi


export running2015=False

# Modify to describe your directory structure.
# all directories are below the LQAnalyser base directory specified above
### setup paths to be used in analysis code
export LQANALYZER_ANALYSIS_PATH=${LQANALYZER_DIR}/LQAnalysis/
export LQANALYZER_SRC_PATH=${LQANALYZER_DIR}/LQAnalysis/Analyzers/src/
export LQANALYZER_INCLUDE_PATH=${LQANALYZER_DIR}/LQAnalysis/Analyzersinclude/
export LQANALYZER_CORE_PATH=${LQANALYZER_DIR}/LQCore/

export isSLC5="False"
export BTAGDIR=${LQANALYZER_DIR}/LQAnalysis/AnalyzerTools/BTag/BTagC11/
export ROCHDIR=${LQANALYZER_DIR}/LQAnalysis/AnalyzerTools/rochcor2016/

if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    export OBJ=obj/cluster/
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cluster/

elif [ $HOSTNAME == "ui10.sdfarm.kr" ];
then
    export OBJ=obj/kisti$LIBTAG
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/kisti$LIBTAG/
    export LQANALYZER_BATCHLIB_PATH=${LQANALYZER_DIR}/LQLib/batch/
	    
else
    export OBJ=obj/cms2
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cms2/

fi


export LQANALYZER_OLDLIB_PATH=${LQANALYZER_DIR}/LQLib/
export LQANALYZER_RUN_PATH=${LQANALYZER_DIR}/LQRun/
export LQANALYZER_CLUSTER_TXT_PATH=${LQANALYZER_DIR}/LQRun/txt/Cluster/
export LQANALYZER_BIN_PATH=${LQANALYZER_DIR}/bin/
### set SKTree path
export SKTREE_INCLUDE_PATH=${LQANALYZER_DIR}/LQCore/SKTree/include/
## setup directory to store analysis rootfiles
export FILEDIR=${LQANALYZER_DIR}/data/rootfiles/
export IDFILEDIR=${LQANALYZER_DIR}/data/ID/80X/
export LUMIFILEDIR=${LQANALYZER_DIR}/data/Luminosity/80X/
export TRIGGERFILEDIR=${LQANALYZER_DIR}/data/Trigger/80X/
export BTAGFILEDIR=${LQANALYZER_DIR}/data/BTag/80X/
export PILEUPFILEDIR=${LQANALYZER_DIR}/data/Pileup/80X/



if [ ! -d ${LQANALYZER_OLDLIB_PATH} ]; then
    echo Directory ${LQANALYZER_OLDLIB_PATH} does not exist ... creating it
    mkdir ${LQANALYZER_OLDLIB_PATH}
fi

if [ ! -d ${LQANALYZER_LIB_PATH} ]; then
    echo Directory ${LQANALYZER_LIB_PATH} does not exist ... creating it
    mkdir ${LQANALYZER_LIB_PATH}
    file="${LQANALYZER_OLDLIB_PATH}/libAnalysisCore.so"
    if [ -f "$file" ]; then
	echo Old lib dir ${LQANALYZER_OLDLIB_PATH} is redundant. Will remove these library
	rm  ${LQANALYZER_OLDLIB_PATH}/*.so
	rm  ${LQANALYZER_OLDLIB_PATH}/*map
	rm  ${LQANALYZER_CORE_PATH}/*/obj/*.o
	rm -r ${LQANALYZER_CORE_PATH}/*/obj/dep/
	rm  ${LQANALYZER_ANALYSIS_PATH}/*/obj/*.o
	rm -r ${LQANALYZER_ANALYSIS_PATH}/*/obj/dep/
    fi
fi

### Load useful functions
source ${LQANALYZER_BIN_PATH}/cleanup.sh 
### make directories that git does not allow to store

export LQANALYZER_OUTPUT_PATH=/data2/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/

export LQANALYZER_LOG_PATH=/data2/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
export LQANALYZER_LOG_8TeV_PATH=${LQANALYZER_DIR}/data/logfiles/



if [ $HOSTNAME == "tamsa2.snu.ac.kr" ];
then
    export LQANALYZER_OUTPUT_PATH=/data4/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/
    export LQANALYZER_LOG_PATH=/data4/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
fi

if [ $HOSTNAME == "ui10.sdfarm.kr" ];
then
    export LQANALYZER_OUTPUT_PATH=/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/
    export LQANALYZER_LOG_PATH=/cms/scratch/SNU/CATAnalyzer/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
fi

python ${LQANALYZER_DIR}/python/SetUpWorkSpace.py
python ${LQANALYZER_DIR}/python/BackUpDirectory.py
python ${LQANALYZER_DIR}/python/SetupEmailList.py



# CHeck onroot area and other paths
 
if [[ `which root-config` == "" ]]; then
    echo "Warning: ROOT environment doesn't seem to be configured!"
    source $root_setup
    if [[ `which root-config` == "" ]]; then
	echo  "Error: ROOT environment cannot be configured!"
    else echo "Setup root enviroment " 
    fi
fi

if [ -z ${ROOTSYS} ] ; then
    echo "Warning: ROOT environment doesn't seem to be configured!"
    echo "Add these lines to your ~/.bashrc file to remove this warning in future."
    echo ""
    echo "source /usr/local/bin/thisroot.sh"
    echo ""
    export ROOTSYS=/usr/local
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib/root:
    if [ -z ${ROOTSYS} ] ; then
	echo "Error: ROOT environment cannot be configured!"
    else echo "Setup root enviroment for user."
    fi
fi


if [[ `root-config --platform` == "macosx" ]]; then

    # With Fink ROOT installations, DYLD_LIBRARY_PATH doesn't have
    # to be defined for ROOT to work. So let's leave the test for it...
    export DYLD_LIBRARY_PATH=${LQANALYZER_LIB_PATH}:${DYLD_LIBRARY_PATH}
    
else    
    
    if [ ! $LD_LIBRARY_PATH ]; then
        echo "Warning: so far you haven't setup your ROOT enviroment properly (no LD_LIBRARY_PATH): FrameWork will not work"
    fi
    export LD_TMP_LIBRARY_PATH=${LD_LIBRARY_PATH}
    export LD_LIBRARY_PATH=${LQANALYZER_LIB_PATH}:${LD_LIBRARY_PATH}

fi


export PATH=${LQANALYZER_BIN_PATH}:${PATH}
export PYTHONPATH=${LQANALYZER_DIR}/python:${PYTHONPATH}
export PAR_PATH=./:${LQANALYZER_LIB_PATH}

python ${LQANALYZER_DIR}/python/local_check.py

if [ ! -d ${LQANALYZER_LOG_PATH} ]; then
    echo Directory ${LQANALYZER_LOG_PATH} does not exist ... creating it
    mkdir ${LQANALYZER_LOG_PATH}
fi

echo "Running analysis from" $HOSTNAME " in directory: " $PWD