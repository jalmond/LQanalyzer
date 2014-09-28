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

if [ $LQANALYZER_DIR ]; then
    echo LQANALYZER_DIR is already defined, use a clean shell
    return 1
fi

## variables that are specific to your machine: Change if noy listed
if [ "$HOSTNAME" = "cms2.snu.ac.kr" ] || [ "$HOSTNAME" = "cms1.snu.ac.kr" ]; then    
    export root_setup="/usr/local/bin/thisroot.sh"
else
    export root_setup=$HOME"/root/root/bin/thisroot.sh"
fi    

# speficy the LQANALYZER_DIR base directory, i.e., the directory in which this file lives
export LQANALYZER_DIR=${PWD}


export LQANALYZER_FILE_DIR="/data1/LQAnalyzer_rootfiles_for_analysis/Sep14/"

# Modify to describe your directory structure.
# all directories are below the LQAnalyser base directory specified above
### setup paths to be used in analysis code
export LQANALYZER_ANALYSIS_PATH=${LQANALYZER_DIR}/LQAnalysis/
export LQANALYZER_SRC_PATH=${LQANALYZER_DIR}/LQAnalysis/src/
export LQANALYZER_INCLUDE_PATH=${LQANALYZER_DIR}/LQAnalysis/include/
export LQANALYZER_CORE_PATH=${LQANALYZER_DIR}/LQCore/

if [[ "$HOSTNAME" == "cms1" ]]
then 
    export OBJ=obj/slc6_cms1
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/slc6_cms1
elif [[ "$HOSTNAME" == "cms5" || "$HOSTNAME" == "cms6" ]]
then
    export OBJ=obj/slc6
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/slc6/
elif [[ "$HOSTNAME" == "cms3" ]]
then
    export OBJ=obj/slc5_cms3
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/slc5_cms3/
else
    export OBJ=obj/slc5
    export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/slc5/
fi

export LQANALYZER_OLDLIB_PATH=${LQANALYZER_DIR}/LQLib/

export LQANALYZER_RUN_PATH=${LQANALYZER_DIR}/LQRun/
export LQANALYZER_BIN_PATH=${LQANALYZER_DIR}/bin/
### set SKTree path
export SKTREE_INCLUDE_PATH=${LQANALYZER_DIR}/LQCore/SKTree/include/
## setup directory to store analysis rootfiles
#export FILEDIR=${LQANALYZER_DIR}/data/rootfiles/
export FILEDIR="/data1/LQAnalyzer_rootfiles_for_analysis/Sep14/"



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
python ${LQANALYZER_BIN_PATH}/SetUpWorkSpace.py
export LQANALYZER_OUTPUT_PATH=${LQANALYZER_DIR}/data/output/
export LQANALYZER_LOG_PATH=${LQANALYZER_DIR}/data/logfiles/

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

python bin/local_check.py

echo "Running analysis from" $HOSTNAME " in directory: " 

#clean up all emacs tmp files
clean_emacs