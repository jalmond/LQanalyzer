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
echo "Setting up environment for compiling/running LQAnalzer with SKTree"


setupok=False

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



if [[ $PWD !=  *"/data4/LQAnalyzerCode/"* ]];
then
    if [ $HOSTNAME == "cmscluster.snu.ac.kr" ];
    then
        echo "Setup failed. LQanalyzer needs to be in /data4/LQAnalyzerCode/"$USER
        if [ ! -d /data4/LQAnalyzerCode/$USER ]; then
            mkdir /data4/LQAnalyzerCode/$USER
        fi
        echo "Move the current LQAnalyzer directory to "/data4/LQAnalyzerCode/$USER

        return
    fi
fi


if [ $LQANALYZER_DIR ]; then
    echo LQANALYZER_DIR is already defined, use a clean shell
    return 1
fi

## variables that are specific to your machine: Change if noy listed
if [ "$HOSTNAME" = "cms2.snu.ac.kr" ] || [ "$HOSTNAME" = "cms1.snu.ac.kr" ]; then    
    source /share/apps/root_v5-34-32/root/bin/thisroot.sh 
elif [ $HOSTNAME == "cmscluster.snu.ac.kr" ];
then
    source /share/apps/root_v5_34_32/root/bin/thisroot.sh
else
    source /share/apps/root_v5-34-32/root/bin/thisroot.sh
fi    



# speficy the LQANALYZER_DIR base directory, i.e., the directory in which this file lives
export LQANALYZER_DIR=${PWD}

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
source $LQANALYZER_DIR/scripts/setup/SetBrachAndTag.sh Tag

source $LQANALYZER_DIR/bin/CheckTag.sh

alias sktree="bash submitSKTree.sh"
alias sktree_bkg="bash submitSKTree.sh -b True "
alias new_git_tag="bash "$LQANALYZER_DIR"/scripts/setup/git_newtag.sh"
alias git_commit_lq="bash scripts/setup/git_commit.sh"
alias sktree_bkg_log="python python/PrintBkgJob.py"

export LQANALYZER_FILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATAnalysis2016/"
export LQANALYZER_LUMIFILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/DataSetLists/AnalysisFiles/"
export LQANALYZER_SKTreeLOG_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
export CATTAGDIR="/data1/LQAnalyzer_rootfiles_for_analysis/CATTag/"
if [ $HOSTNAME == "cmscluster.snu.ac.kr" ];
then
    export LQANALYZER_FILE_DIR="/data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATAnalysis/"
    export CATTAGDIR="/data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATTag/"
    export LQANALYZER_SKTreeLOG_DIR="/data4/LocalNtuples/LQAnalyzer_rootfiles_for_analysis/CATSKTreeMaker/"
fi



# Modify to describe your directory structure.
# all directories are below the LQAnalyser base directory specified above
### setup paths to be used in analysis code
export LQANALYZER_ANALYSIS_PATH=${LQANALYZER_DIR}/LQAnalysis/
export LQANALYZER_SRC_PATH=${LQANALYZER_DIR}/LQAnalysis/src/
export LQANALYZER_INCLUDE_PATH=${LQANALYZER_DIR}/LQAnalysis/include/
export LQANALYZER_CORE_PATH=${LQANALYZER_DIR}/LQCore/

export isSLC5="False"
export BTAGDIR=${LQANALYZER_DIR}/LQAnayzer/src/BTag/BTagC11/
if [[ "$HOSTNAME" == "cms.snu.ac.kr" ]];
then 
    export OBJ=obj/cms21
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cms21
    
elif [ $HOSTNAME == "cmscluster.snu.ac.kr" ];
    then
    export OBJ=obj/cluster/
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cluster/

elif [[ "$HOSTNAME" == "cms1" ]];
then
    export OBJ=obj/cms1
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/cms1/

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

if [ $HOSTNAME == "cmscluster.snu.ac.kr" ];
    then
    export LQANALYZER_OUTPUT_PATH=/data4/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/output/
    export LQANALYZER_LOG_PATH=/data4/CAT_SKTreeOutput/JobOutPut/${USER}/LQanalyzer/data/logfiles/
fi

python ${LQANALYZER_DIR}/python/SetUpWorkSpace.py
python ${LQANALYZER_DIR}/python/BackUpDirectory.py
python ${LQANALYZER_DIR}/python/SetupEmailList.py

# Setup root area and other paths
 
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

#clean up all emacs tmp files
#clean_emacs