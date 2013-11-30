#/bin/sh
# $Id: setup.sh 1
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
echo "Using root: " $root_setup

# speficy the LQANALYZER_DIR base directory, i.e., the directory in which this file lives
export LQANALYZER_DIR=${PWD}

# Modify to describe your directory structure.
# all directories are below the LQAnalyser base directory specified above
### setup paths to be used in analysis code
export LQANALYZER_SRC_PATH=${LQANALYZER_DIR}/LQCycle/src/
export LQANALYZER_INCLUDE_PATH=${LQANALYZER_DIR}/LQCycle/include/
export LQANALYZER_CORE_PATH=${LQANALYZER_DIR}/LQCore/
export LQANALYZER_LIB_PATH=${LQANALYZER_DIR}/LQLib/
export LQANALYZER_BIN_PATH=${LQANALYZER_DIR}/bin/
### set SKTree path
export SKTREE_INCLUDE_PATH=${LQANALYZER_DIR}/LQCore/SKTree/include/
## setup directory to store analysis rootfiles
export FILEDIR=${LQANALYZER_DIR}/data/rootfiles/
### Load useful functions
echo "Running analysis from" $HOSTNAME " in directory " $ANALYSISDIR
source ${LQANALYZER_BIN_PATH}/cleanup.sh 
### make directories that git does not allow to store
python ${LQANALYZER_BIN_PATH}/SetUpWorkSpace.py
export LQANALYZER_OUTPUT_PATH=${LQANALYZER_DIR}/data/output/


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


#clean up all emacs tmp files
clean_emacs